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
#include "config.h"
#include <stdlib.h>
#include <string.h>


static inline CfgValue *cfg_value_alloc(CfgType type);
static inline void cfg_value_free(CfgValue *val);

static inline CfgSetting *cfg_setting_alloc(const char *key, const char *tag);
static inline void cfg_setting_free(CfgSetting *st);

CfgSetting *cfg_setting_ref(CfgSetting *st) {
    st->ref++;
    return st;
}

CfgSetting *cfg_setting_unref(CfgSetting *st) {
    if((--st->ref)<=0) {
        cfg_setting_free(st);
        return NULL;
    }
    return st;
}

CfgValue *cfg_value_ref(CfgValue *val) {
    val->ref++;
    return val;
}

CfgValue *cfg_value_unref(CfgValue *val) {
    if((--val->ref)<=0) {
        cfg_value_free(val);
        return NULL;
    }
    return val;
}


static inline CfgValue *cfg_value_alloc(CfgType type) {
    CfgValue *val=(CfgValue*)calloc(1, sizeof(CfgValue*));
    val->type = type;
    cfg_value_ref(val);
    return val;
}

static inline void cfg_value_free(CfgValue *val) {
    if(val->type==CFG_TYPE_STRING) {
        free(val->v_str);
    } else if(val->type==CFG_TYPE_ARRAY) {
        sph_list_free(val->v_array, (SphListDestroy)cfg_value_unref);
    } else if(val->type==CFG_TYPE_GROUP) {
        sph_list_free(val->v_group, (SphListDestroy)cfg_setting_free);
    }
    free(val);
}

static inline CfgSetting *cfg_setting_alloc(const char *key, const char *tag) {
    CfgSetting *st=(CfgSetting*)calloc(1, sizeof(CfgSetting));
    st->key=strdup(key);
    st->tag=strdup(tag);
    return st;
}

static inline void cfg_setting_free(CfgSetting *st) {
    free(st->key);
    free(st->tag);
    if(st->val) {
        cfg_value_unref(st->val);
    }
    free(st);
}
