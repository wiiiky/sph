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


#include "loop.h"
#include "utils.h"
#include <stdlib.h>


struct ev_loop *default_loop=NULL;

/* 返回全局的ev_loop对象 */
struct ev_loop *get_default_evloop(void){
    if(UNLIKELY(default_loop==NULL)){
        default_loop = ev_default_loop(0);
    }
    return default_loop;
}

/* 启动主循环 */
void run_evloop(void){
    ev_run(get_default_evloop(), 0);
}
