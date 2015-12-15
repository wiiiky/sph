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
#include "list.h"
#include <stdlib.h>

static inline SphList *sph_list_alloc(void *data);

SphList *sph_list_last(SphList *l) {
    if(l==NULL) {
        return NULL;
    }
    while(sph_list_next(l)!=NULL) {
        l=sph_list_next(l);
    }
    return l;
}

SphList *sph_list_append(SphList *l, void *data) {
    SphList *e = sph_list_alloc(data);
    if(l==NULL) {
        return e;
    }
    SphList *last=sph_list_last(l);
    last->next=e;
    e->prev=last;
    return l;
}

void sph_list_free(SphList *l, void (*destroy)(void *data)) {
    while(l) {
        SphList *next=sph_list_next(l);
        if(destroy) {
            destroy(sph_list_data(l));
        }
        free(l);
        l = next;
    }
}


static inline SphList *sph_list_alloc(void *data) {
    SphList *l = (SphList*)malloc(sizeof(SphList));
    l->data = data;
    l->prev=NULL;
    l->next=NULL;
    return l;
}
