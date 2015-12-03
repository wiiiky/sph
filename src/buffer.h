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
#ifndef __SPH_BUFFER_H__
#define __SPH_BUFFER_H__

#include <inttypes.h>


typedef struct {
    unsigned int total;     /* 缓冲区总长度 */
    unsigned int start;     /* 当前缓冲数据起始位置 */
    unsigned int length;    /* 缓冲区现有长度 */
    uint8_t *data;             /* 缓冲区指针 */
} SphBuffer;

#define sph_buffer_get_length(buf)  ((buf)->length)
#define sph_buffer_get_data(buf)    ((buf)->data+(buf)->start)

SphBuffer *sph_buffer_new(void);
SphBuffer *sph_buffer_new_with_length(unsigned int len);
void sph_buffer_free(SphBuffer *buf);

/* 清空缓冲区 */
void sph_buffer_clear(SphBuffer *buf);

/* 在缓冲区添加数据 */
void sph_buffer_append(SphBuffer *buf, void *data, unsigned int len);
/* 删除缓冲区首部len个字节 */
void sph_buffer_pop(SphBuffer *buf, unsigned int len);
/* 删除缓冲区的数据 */
void sph_buffer_erase(SphBuffer *buf, unsigned int start, unsigned int len);



#endif
