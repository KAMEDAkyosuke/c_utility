#ifndef INTLIST_H
#define INTLIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef enum {
    SOCKETLIST_OPENED = 0,
    SOCKETLIST_CAN_CLOSE,
    SOCKETLIST_CLOSED,
} soketlist_status;

typedef struct socketlist{
    struct socketlist* next;
    int socket;
    soketlist_status status;
    void* data;
    void(*data_destructor)(void* data);
} socketlist_t;

socketlist_t* socketlist_append(socketlist_t* list, int socket, void(*data_destructor)(void*));
void socketlist_free(socketlist_t* list);
socketlist_t* socketlist_delete_can_close_sockets(socketlist_t* list);

#ifdef __cplusplus
}
#endif

#endif
