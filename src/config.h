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

#ifndef __SPH_CONFIG_H__
#define __SPH_CONFIG_H__

/*
 * 配置文件格式如下
 * log_path: "/tmp/"
 *
 * server A: {
 *     port: 23123;
 *     modules: ["mod/test.so", ""]
 *     log: {
 *          path: "debug.log"
 *          level: "debug"
 *     }
 *     @include: ["conf/a.conf"];
 *     timeout: 123.3
 * }
 *
 * @include: "conf/all.conf"
 *
 */

#include "list.h"
#include <inttypes.h>

typedef struct _CfgRef CfgRef;
typedef struct _CfgParser CfgParser;
typedef struct _CfgValue CfgValue;
typedef struct _CfgSetting CfgSetting;

struct _CfgParser {

};

struct _CfgSetting {
    char *key;
    char *tag;
    CfgValue *val;
    int ref;
};
CfgSetting *cfg_setting_ref(CfgSetting *st);
CfgSetting *cfg_setting_unref(CfgSetting *st);

typedef enum {
    CFG_TYPE_INTEGER,
    CFG_TYPE_FLOAT,
    CFG_TYPE_STRING,
    CFG_TYPE_ARRAY,
    CFG_TYPE_GROUP,
} CfgType;

struct _CfgValue {
    CfgType type;
    union {
        int64_t integer;
        double floating;
        char *string;
        SphList *array; /* CfgValue* */
        SphList *group; /* CfgSetting* */
    } value;
    int ref;
};
#define v_int   value.integer
#define v_float value.floating
#define v_str   value.string
#define v_array value.array
#define v_group value.group

CfgValue *cfg_value_ref(CfgValue *val);
CfgValue *cfg_value_unref(CfgValue *val);



#endif
