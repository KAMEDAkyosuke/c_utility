#include "socketlist.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>


static void socket_close(socketlist_t* list);
static socketlist_t* socketlist_delete(socketlist_t* list, socketlist_t* target);

socketlist_t* socketlist_append(socketlist_t* list, int socket, void(*data_destructor)(void*))
{
    socketlist_t* new_item = (socketlist_t*) malloc(sizeof(socketlist_t));
    new_item->next = NULL;
    new_item->socket = socket;
    new_item->status = SOCKETLIST_OPENED;
    new_item->data = NULL;
    new_item->data_destructor = data_destructor;

    if(list == NULL){
        return new_item;
    }
    else{
        socketlist_t* last = list;
        while(last->next != NULL){
            last = last->next;
        }
        last->next = new_item;
        return list;
    }
}

void socketlist_free(socketlist_t* list)
{
    socketlist_t *current = list;
    while(current != NULL){
        socket_close(current);
        if(current->data_destructor != NULL){
            current->data_destructor(current->data);
        }
        socketlist_t* tmp = current;
        current = current->next;
        free(tmp);
        tmp = NULL;
    }
}

socketlist_t* socketlist_delete_can_close_sockets(socketlist_t* list)
{
    socketlist_t* root = list;
    socketlist_t* p = list;
    while(p != NULL){
        socketlist_t* next = p->next;
        if(p->status == SOCKETLIST_CAN_CLOSE){
            socket_close(p);
            root = socketlist_delete(root, p);
        }
        p = next;
    }
    
    return root;
}

static void socket_close(socketlist_t* list)
{
    if(list->status == SOCKETLIST_OPENED
       || list->status == SOCKETLIST_CAN_CLOSE){
    retry:
        if(close(list->socket) != 0){
            int err = errno;
            perror("close failed");
            switch(err){
            case EINTR:
                goto retry;
                break;
            default:
                exit(EXIT_FAILURE);
            }
        }
        printf("SOCKET %d CLOSED\n", list->socket);
        list->status = SOCKETLIST_CLOSED;
    }
}

static socketlist_t* socketlist_delete(socketlist_t* list, socketlist_t* target)
{
    if(list == target){
        socket_close(target);
        if(target->data_destructor != NULL){
            target->data_destructor(target->data);
        }
        socketlist_t* next = list->next;
        free(target);
        return next;
    }

    socketlist_t* tmp = list;
    while(tmp != NULL && tmp->next != target){
        tmp = tmp->next;
    }
    if(tmp == NULL){    /* NOT FOUND */
        return list;
    }

    socketlist_t* next = target->next;
    socket_close(target);
    if(target->data_destructor != NULL){
        target->data_destructor(target->data);
    }
    free(target);
    tmp->next = next;
    return list;
}
