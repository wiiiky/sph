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
#include "buffer.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>


/* 保证缓冲区添加了len个字节后长度依然足够 */
static inline int sph_buffer_ensure_mem(SphBuffer *buf, unsigned int len);


SphBuffer *sph_buffer_new(void) {
    return sph_buffer_new_with_length(2048);
}

SphBuffer *sph_buffer_new_with_length(unsigned int len) {
    SphBuffer *buf=(SphBuffer*)malloc(sizeof(SphBuffer));
    buf->total=len;
    buf->length=0;
    buf->data=(uint8_t*)malloc(sizeof(uint8_t)*buf->total);
    return buf;
}

/* 清空缓冲区 */
void sph_buffer_clear(SphBuffer *buf) {
    buf->length=0;
    buf->data[0]=0;
}

/* 在缓冲区添加数据 */
void sph_buffer_append(SphBuffer *buf, void *data, unsigned int len) {
    if(UNLIKELY(len==0||sph_buffer_ensure_mem(buf, len))) {
        return;
    }
    memcpy(buf->data+buf->length, data, len);
    buf->length+=len;
}


/* 保证缓冲区添加了len个字节后长度依然足够 */
static inline int sph_buffer_ensure_mem(SphBuffer *buf, unsigned int len) {
    while(UNLIKELY(buf->length+len>buf->total)) {
        buf->total<<=1;
        uint8_t *data=(uint8_t*)realloc(buf->data, sizeof(uint8_t)*buf->total);
        if(UNLIKELY(data==NULL)) {
            return 1;
        }
        buf->data=data;
    }
    return 0;
}
