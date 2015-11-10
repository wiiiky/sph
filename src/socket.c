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
#include <sys/types.h>
#include <sys/socket.h>


/* 创建一个套接字 */
SphSocket *sph_socket_new(void){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0){
        return NULL;
    }
    SphSocket *socket=(SphSocket*)malloc(sizeof(SphSocket));
    socket->fd=sockfd;
    return socket;
}
