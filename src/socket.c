/*
 * Copyright (C) 2015 Wiky L
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.";
 */

#include "socket.h"
#include "loop.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* 释放套接字所有资源，包括文件描述符和内存 */
static inline void sph_socket_release(SphSocket *socket) {
    if(socket->release) {
        socket->release(socket);
    }
    if(socket->loop) {
        ev_io_stop(socket->loop, (ev_io*)socket);
    }
    close(socket->fd);
    sph_buffer_free(socket->wbuf);
    sph_buffer_free(socket->rbuf);
    free(socket);
}

void sph_socket_ref(SphSocket *socket) {
    socket->ref+=1;
}

void sph_socket_unref(SphSocket *socket) {
    if((--socket->ref)<=0) {
        sph_socket_release(socket);
    }
}


/* 创建一个套接字 */
SphSocket *sph_socket_new(void) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd<0) {
        return NULL;
    }
    return sph_socket_new_from_fd(fd);
}


/* 从现有的文件描述符创建一个套接字对象 */
SphSocket *sph_socket_new_from_fd(int fd) {
    SphSocket *socket=(SphSocket*)malloc(sizeof(SphSocket));
    sph_socket_init_from_fd(socket, fd);

    return socket;
}

void sph_socket_init(SphSocket *s) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd<0) {
        return;
    }
    sph_socket_init_from_fd(s, fd);
}

void sph_socket_init_from_fd(SphSocket *socket, int fd) {
    socket->loop=NULL;
    socket->fd=fd;
    socket->ref=1;
    socket->user_data=NULL;
    socket->rbuf=sph_buffer_new();
    socket->wbuf=sph_buffer_new();
}

/*
 * 绑定地址，可以是IPv6或者IPv4
 * 成功返回 1，失败返回 0
 */
int sph_socket_bind(SphSocket *socket, const char *ip, unsigned short port) {
    struct sockaddr_storage addr;
    socklen_t addrlen;
    struct sockaddr_in *addr4 = (struct sockaddr_in*)&addr;
    struct sockaddr_in6 *addr6 = (struct sockaddr_in6*)&addr;

    if(inet_pton(AF_INET,ip, &addr4->sin_addr.s_addr)) {
        addr4->sin_family=AF_INET;
        addr4->sin_port=htons(port);
        addrlen = sizeof(*addr4);
    } else if(inet_pton(AF_INET6, ip, &addr6->sin6_addr.s6_addr)) {
        addr6->sin6_family=AF_INET6;
        addr6->sin6_port=htons(port);
        addrlen=sizeof(*addr6);
    } else {
        return 0;
    }
    return bind(socket->fd, (struct sockaddr*)&addr, addrlen)==0;
}

/* 被动套接字 */
int sph_socket_listen(SphSocket *socket,int backlog) {
    return listen(socket->fd, backlog)==0;
}

/* reuse地址和端口 */
int sph_socket_reuse_addr(SphSocket *socket, int addr) {
#if defined(SO_REUSEADDR)
    return setsockopt(socket->fd, SOL_SOCKET, SO_REUSEADDR, &addr, sizeof(addr))==0;
#else
    return 0;
#endif
}

int sph_socket_reuse_port(SphSocket *socket, int port) {
#if defined(SO_REUSEPORT)
    return setsockopt(socket->fd, SOL_SOCKET, SO_REUSEPORT, &port, sizeof(port))==0;
#else
    return 0;
#endif
}


/* 接收和发送数据的包裹，非阻塞 */
int sph_socket_recv(SphSocket *socket, void *buf, unsigned int len, int flags) {
    return recv(socket->fd, buf, len, flags);
}

int sph_socket_send(SphSocket *socket, const void *buf, unsigned int len, int flags) {
    return send(socket->fd, buf, len, flags);
}

/* 准备发送数据，将在下一次可发送时发送 */
void sph_socket_prepare_data(SphSocket *socket, const void *buf, unsigned int len) {
    if(socket->prepare) {
        socket->prepare(socket, buf, len);
    }
}

/* accepts a connection and returns the file descriptor */
int sph_socket_accept(SphSocket *socket) {
    return accept(socket->fd, NULL, NULL);
}

/*
 * 套接字进入事件回调
 * 在调用此函数之前必须已经给SphSocket设置了loop
 */
/*
 * 套接字进入事件回调
 */
void sph_socket_start(SphSocket *socket, struct ev_loop *loop,
                      void (*callback)(struct ev_loop*, ev_io *, int)) {
    if(UNLIKELY(callback==NULL)) {
        return;
    }
    if(loop==NULL) {
        loop=get_default_evloop();
    }
    socket->loop=loop;
    ev_io_init((ev_io*)socket, callback, socket->fd, EV_READ|EV_WRITE);
    ev_io_start(loop, (ev_io*)socket);
}

/* 结束监听套接字事件 */
void sph_socket_stop(SphSocket *socket) {
    if(UNLIKELY(socket->loop==NULL)) {
        return;
    }
    ev_io_stop(socket->loop, (ev_io*)socket);
    socket->loop = NULL;
}
