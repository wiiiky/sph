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

#ifndef __SPH_MOD_H__
#define __SPH_MOD_H__

#include "socket.h"


typedef struct {
    int (*m_init)(void);    /* 模块初始化函数，在模块载入时调用，返回0表示初始化成功 */
    int (*m_accept)(SphSocket *socket); /* 接受到客户端连接时的回调函数，返回0表示成功 */
} JacModule;


#endif
