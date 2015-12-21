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
#include "mod.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dlfcn.h>


/* 从指定文件载入模块，失败返回NULL */
JacModule *jac_module_load(const char *dir, const char *name) {
    char buf[4096];
    void *handle;
    JacModule *mod = NULL;

    snprintf(buf, sizeof(buf), "%s/%s", dir, name);
    if((handle = dlopen(buf, RTLD_NOW|RTLD_NODELETE))==NULL) {
        snprintf(buf, sizeof(buf), "%s/%s.so", dir, name);
        if((handle = dlopen(buf, RTLD_NOW|RTLD_NODELETE))==NULL) {
            return NULL;
        }
    }

    snprintf(buf, sizeof(buf), "JacInit_%s", name);
    void *ptr=dlsym(handle, buf);
    if(!ptr) {
        goto CLOSE;
    }
    mod = ((JacInit)ptr)();
CLOSE:
    dlclose(handle);
    return mod;
}

