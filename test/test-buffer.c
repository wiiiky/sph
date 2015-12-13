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
#include <sph.h>

#define sph_buffer_check_length(buf, len) \
            do{ \
                if(buf->length!=len){ \
                    return 1; \
                } \
            }while(0)
#define sph_buffer_check_total(buf, len) \
            do{ \
                if(buf->total!=len){ \
                    return 2; \
                } \
            }while(0);
#define sph_buffer_check_start(buf, s) \
            do{ \
                if(buf->start!=s){ \
                    return 3; \
                } \
            }while(0);

int main(int argc, char *argv[]) {
    char data[4096];
    SphBuffer *buf=sph_buffer_new_with_length(12);
    sph_buffer_check_length(buf, 0);
    sph_buffer_check_total(buf, 12);
    sph_buffer_check_start(buf, 0);

    sph_buffer_append(buf, data, 3);
    sph_buffer_check_length(buf, 3);
    sph_buffer_check_total(buf, 12);
    sph_buffer_check_start(buf, 0);

    sph_buffer_append(buf, data, 9);
    sph_buffer_check_length(buf, 12);
    sph_buffer_check_total(buf, 12);
    sph_buffer_check_start(buf, 0);

    sph_buffer_append(buf, data, 9);
    sph_buffer_check_length(buf, 21);
    sph_buffer_check_total(buf, 24);
    sph_buffer_check_start(buf, 0);

    sph_buffer_pop(buf, 10);
    sph_buffer_check_length(buf, 11);
    sph_buffer_check_total(buf, 24);
    sph_buffer_check_start(buf, 10);

    sph_buffer_append(buf, data, 13);
    sph_buffer_check_length(buf, 24);
    sph_buffer_check_total(buf, 24);
    sph_buffer_check_start(buf, 0);

    sph_buffer_append(buf, data, 10);
    sph_buffer_check_length(buf, 34);
    sph_buffer_check_total(buf, 48);
    sph_buffer_check_start(buf, 0);

    sph_buffer_pop(buf, 30);
    sph_buffer_check_length(buf, 4);
    sph_buffer_check_total(buf, 48);
    sph_buffer_check_start(buf, 30);

    return 0;
}
