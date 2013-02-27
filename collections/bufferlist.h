#ifndef BUFFERLIST_H
#define BUFFERLIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <unistd.h>

typedef struct bufferlist_t{
    struct bufferlist_t* next;
    ssize_t len;
    uint8_t* buffer;
} bufferlist_t;

bufferlist_t* bufferlist_append(bufferlist_t* list, uint8_t* buf, ssize_t len);
void bufferlist_free(bufferlist_t* list);

ssize_t bufferlist_len(bufferlist_t* list);
uint8_t* bufferlist_concat(bufferlist_t* list);
void bufferlist_concat_free(uint8_t* buf);

#ifdef __cplusplus
}
#endif


#endif
