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

typedef struct _JacModule JacModule;


struct _JacModule {
    void (*m_finalize)(void);   /* 程序正常结束时调用 */
    int (*m_accept)(SphSocket *socket); /* 接受到客户端连接时的回调函数，返回0表示成功接收 */
    int (*m_recv)(SphSocket *socket, const uint8_t *pdata, unsigned int len);
    void *user_data;
};

#define XSTRINGIFY(s) STRINGIFY(s)
#define STRINGIFY(s) #s
#define JACQUES_MODULE_NAME __jacques_module__
#define JACQUES_MODULE_STRING   XSTRINGIFY(JACQUES_MODULE_NAME)
#define JACQUES_MODULE(mod) JacModule *JACQUES_MODULE_NAME=&mod

typedef JacModule* (*JacInit)(void);

/* 从指定文件载入模块，失败返回NULL */
JacModule *jac_module_load(const char *dir, const char *name);

#endif
