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
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

/* 释放套接字所有资源，包括文件描述符和内存 */
static inline void sph_socket_release(SphSocket *socket){
    if(socket->onreleased){
        socket->onreleased(socket);
    }
    if(socket->loop){
        ev_io_stop(socket->loop, (ev_io*)socket);
    }
    close(socket->fd);
    free(socket);
}

void sph_socket_ref(SphSocket *socket){
    socket->ref+=1;
}

void sph_socket_unref(SphSocket *socket){
    if((--socket->ref)<=0){
        sph_socket_release(socket);
    }
}


/* 创建一个套接字 */
SphSocket *sph_socket_new(void){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0){
        return NULL;
    }
    return sph_socket_new_from_fd(sockfd);
}

/* 从现有的文件描述符创建一个套接字对象 */
SphSocket *sph_socket_new_from_fd(int fd){
    SphSocket *socket=(SphSocket*)malloc(sizeof(SphSocket));
    socket->loop=NULL;
    socket->fd=fd;
    socket->ref=1;
    socket->onreleased=NULL;
    
    return socket;
}

/* 接收和发送数据的包裹，非阻塞 */
int sph_socket_recv(SphSocket *socket, void *buf, unsigned int len, int flags){
    return recv(socket->fd, buf, len, flags|MSG_DONTWAIT);
}

int sph_socket_send(SphSocket *socket, const void *buf, unsigned int len, int flags){
    return send(socket->fd, buf, len, flags|MSG_DONTWAIT);
}

/* 
 * 套接字进入事件回调
 * 在调用此函数之前必须已经给SphSocket设置了loop
 */
/* 
 * 套接字进入事件回调
 */
void sph_socket_start(SphSocket *socket, struct ev_loop *loop,
                      void (*callback)(struct ev_loop*, ev_io *, int)){
    if(loop==NULL||callback==NULL){
      return;
    }
    socket->loop=loop;
    ev_io_init((ev_io*)socket, callback, socket->fd, EV_READ|EV_WRITE);
    ev_io_start(loop, (ev_io*)socket);
}
