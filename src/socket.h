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

#ifndef __SPH_SOCKET_H__
#define __SPH_SOCKET_H__

#include <ev.h>
#include "buffer.h"

typedef struct _SphSocket SphSocket;


struct _SphSocket {
    ev_io parent;
    struct ev_loop *loop;
    int fd;
    SphBuffer *rbuf;
    SphBuffer *wbuf;
    void *user_data;

    int ref;    /* 引用计数 */
    void (*release)(void *self);
    void (*prepare)(SphSocket *socket, const void *data, unsigned int len);
};

#define sph_socket_get_fd(s)    ((s)->fd)
#define sph_socket_get_evloop(s)    ((s)->loop)
#define sph_socket_get_wbuf(s)  ((s)->wbuf)
#define sph_socket_get_rbuf(s)  ((s)->rbuf)
#define sph_socket_get_user_data(s) ((s)->user_data)
#define sph_socket_set_user_data(s, d)  ((s)->user_data)=(d)

/* 增加和减少引用计数 */
void sph_socket_ref(SphSocket *socket);
void sph_socket_unref(SphSocket *socket);

/* 创建一个套接字 */
SphSocket *sph_socket_new(void);
SphSocket *sph_socket_new_from_fd(int fd);

void sph_socket_init(SphSocket *socket);
void sph_socket_init_from_fd(SphSocket *socket, int fd);

/*
 * 绑定地址，可以是IPv6或者IPv4
 * 成功返回 1，失败返回 0
 */
int sph_socket_bind(SphSocket *socket, const char *ip, unsigned short port);
/* 被动套接字 */
int sph_socket_listen(SphSocket *socket,int backlog);
/* reuse地址和端口 */
int sph_socket_reuse_addr(SphSocket *socket, int addr);
int sph_socket_reuse_port(SphSocket *socket, int port);

/* 接收和发送数据的包裹，非阻塞 */
int sph_socket_recv(SphSocket *socket, void *buf, unsigned int len, int flags);
int sph_socket_send(SphSocket *socket, const void *buf, unsigned int len, int flags);

/* 准备发送数据，将在下一次可发送时发送 */
void sph_socket_prepare_data(SphSocket *socket, const void *buf, unsigned int len);

/* accepts a connection and returns the file descriptor */
int sph_socket_accept(SphSocket *socket);

/*
 * 套接字进入事件回调
 * loop如果为NULL，则使用默认的全局ev_loop
 */
void sph_socket_start(SphSocket *socket, struct ev_loop *loop,
                      void (*callback)(struct ev_loop*, ev_io *, int));
/* 结束监听套接字事件 */
void sph_socket_stop(SphSocket *socket);


#endif
