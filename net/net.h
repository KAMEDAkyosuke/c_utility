#ifndef NET_H
#define NET_H

#include <stdint.h>
#include <arpa/inet.h>
#include <sys/time.h>

typedef enum {
    NET_RESULT_OK = 0,
    NET_RESULT_TIMEOUT,
    NET_RESULT_ERR_SOCKET,
    NET_RESULT_ERR_FCNTL,
    NET_RESULT_ERR_SELECT,
    NET_RESULT_ERR_CONNECT,
    NET_RESULT_ERR_SET_SOCK_OPT,
    NET_RESULT_ERR_BIND,
    NET_RESULT_ERR_LISTEN,
} net_result_code;

typedef struct {
    int code;
} net_result_t;

void net_connect(int *fd, uint16_t port, in_addr_t in_addr, struct timeval timeout, net_result_t* res);
void net_listen(int *fd, uint16_t port, int backlog, net_result_t* res);

#endif
