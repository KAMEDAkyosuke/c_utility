#include "net.h"

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#ifndef NET_WAIT_TIME_MAX_INTERVAL
#define NET_WAIT_TIME_MAX_INTERVAL(name)          \
    struct timeval name;                          \
    name.tv_sec = 65;                             \
    name.tv_usec = 536 * 1000;
#endif

static void create_socket(int *fd, net_result_t* res);

void net_connect(int *fd, uint16_t port, in_addr_t in_addr, struct timeval timeout, net_result_t* res)
{
    create_socket(fd, res);
    if(res->code != NET_RESULT_OK){
        return;
    }

    // connect
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = in_addr;

    NET_WAIT_TIME_MAX_INTERVAL(wait_max_interval);

    struct timeval wait;
    wait.tv_sec = 0;
    wait.tv_usec = 1000;

    struct timeval rest = timeout;

 reconnect:
    if((connect(*fd, (struct sockaddr *) &addr, sizeof(addr))) < 0){
        int err = errno;
        perror("connect error, check errno");
        switch(err){
        case EISCONN:
            puts("connected");
            break;
        case EALREADY:
        case EINTR:
        case EINPROGRESS:
            puts("wait");
            if(select(0, NULL, NULL, NULL, &wait) == -1){
                perror("select fail");
                res->code = NET_RESULT_ERR_SELECT;
                return;
            }
            
            if(timercmp(&rest, &wait, <)){
                puts("connection timeout");
                res->code = NET_RESULT_TIMEOUT;
                return;
            }
            
            timersub(&rest, &wait, &rest);
            timeradd(&wait, &wait, &wait);    // wait += wait;
            if(timercmp(&wait, &wait_max_interval, >)){
                wait = wait_max_interval;
            }
            puts("re connect");
            goto reconnect;
            break;
        default:
            puts("connect error. unexpected errno");
            res->code = NET_RESULT_ERR_CONNECT;
            return;
        }
    }
}

void net_listen(int *fd, uint16_t port, int backlog, net_result_t* res)
{
    create_socket(fd, res);
    if(res->code != NET_RESULT_OK){
        return;
    }
    
    int on = 1;
    if(setsockopt(*fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1){
        perror("setsockopt fail");
        res->code = NET_RESULT_ERR_SET_SOCK_OPT;
        return;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(*fd, (struct sockaddr*) &addr, sizeof(addr)) == -1){
        perror("bind fail");
        res->code = NET_RESULT_ERR_BIND;
        return;
    }

    if(listen(*fd, backlog) != 0){
        perror("listen fail");
        res->code = NET_RESULT_ERR_LISTEN;
        return;
    }
}

static void create_socket(int *fd, net_result_t* res)
{
    // create socket
    if((*fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1){
        perror("socket fail");
        res->code = NET_RESULT_ERR_SOCKET;
        return;
    }

    // set non-blocking
    int flags;
    if((flags = fcntl(*fd, F_GETFL, 0)) < 0){
        perror("fcntl fail");
        res->code = NET_RESULT_ERR_FCNTL;
        return;
    }
    if (fcntl(*fd, F_SETFL, flags | O_NONBLOCK) < 0) {
        perror("fcntl fail");
        res->code = NET_RESULT_ERR_FCNTL;
        return;
    }
}
