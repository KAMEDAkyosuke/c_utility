#include "bufferlist.h"

#include <string.h>
#include <stdlib.h>

bufferlist_t* bufferlist_append(bufferlist_t* list, uint8_t* buf, ssize_t len)
{
    bufferlist_t* new_item = (bufferlist_t*) malloc(sizeof(bufferlist_t));
    new_item->next = NULL;
    new_item->len = len;
    new_item->buffer = (uint8_t*) malloc(sizeof(uint8_t) * len);
    memcpy(new_item->buffer, buf, len);

    if(list == NULL){
        return new_item;
    }
    else{
        bufferlist_t* last = list;
        while(last->next != NULL){
            last = last->next;
        }
        last->next = new_item;
        return list;
    }
}

void bufferlist_free(bufferlist_t* list)
{
    bufferlist_t *current = list;
    while(current != NULL){
        bufferlist_t* tmp = current;
        current = current->next;
        free(tmp->buffer);
        tmp->buffer = NULL;
        free(tmp);
        tmp = NULL;
    }
}
