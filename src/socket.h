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

typedef struct _SphSocket SphSocket;


struct _SphSocket {
    ev_io parent;
    struct ev_loop *loop;
    int fd;
    int ref;    /* 引用计数 */
    
    void (*onreleased)(SphSocket *self);
};

#define sph_socket_get_fd(s)    ((s)->fd)
#define sph_socket_get_evloop(s)    ((s)->loop)

/* 增加和减少引用计数 */
void sph_socket_ref(SphSocket *socket);
void sph_socket_unref(SphSocket *socket);

/* 创建一个套接字 */
SphSocket *sph_socket_new(void);
SphSocket *sph_socket_new_from_fd(int fd);

/* 接收和发送数据的包裹，非阻塞 */
int sph_socket_recv(SphSocket *socket, void *buf, unsigned int len, int flags);
int sph_socket_send(SphSocket *socket, const void *buf, unsigned int len, int flags);

/* 
 * 套接字进入事件回调
 * loop如果为NULL，则使用默认的全局ev_loop
 */
void sph_socket_start(SphSocket *socket, struct ev_loop *loop,
                      void (*callback)(struct ev_loop*, ev_io *, int));


#endif
