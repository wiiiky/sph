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
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>



/* 结构的构造和释放函数 */
static inline CfgValue *cfg_value_alloc(CfgType type);
static inline void cfg_value_free(CfgValue *val);
static inline CfgSetting *cfg_setting_alloc(const char *key, const char *tag);
static inline void cfg_setting_free(CfgSetting *st);

/* 设置错误信息
 * 该函数总是返回0
 */
static inline void cfg_parser_set_error(CfgParser *p, const char *path,
                                        uint64_t line, const char *msg);

CfgParser *cfg_parser_new(void) {
    CfgParser *p=(CfgParser*)calloc(1, sizeof(CfgParser));
    p->root = cfg_value_alloc(CFG_TYPE_GROUP);
    return p;
}

void cfg_parser_free(CfgParser *p) {
    free(p->err_path);
    free(p->err_msg);
    cfg_value_unref(p->root);
    free(p);
}


/*
 * 解析{}指定的配置组
 * @val CFG_TYPE_GROUP类型的CfgValue
 * @data 字符串格式的配置
 * @len 字符串长度
 * @is_root 该组是否是root组，root组没有{}
 *
 * @return 成功返回解析调的字节数，否则返回-1
 */
static int cfg_parse_group(CfgValue *val, char *data, int len, int is_root);
/*
 * 解析设置名， 配置名格式符合一般C语言的变量名格式。
 * @val 用于返回设置名，需要释放
 * @data 字符串格式的配置
 * @len 字符串长度
 */
static int cfg_parse_key(char **val, char *data, int len);

/* 载入配置文件，解析成功返回1，失败返回0 */
int cfg_parser_loads(CfgParser *p,const char *path) {
    int fd = -1;
    struct stat sb;
    char *data;
    int result=-1;

    if((fd = open(path, O_RDONLY))<0
            ||fstat(fd, &sb)
            ||(data = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0))==MAP_FAILED) {
        /* 文件打开失败、或者内存影射失败 */
        cfg_parser_set_error(p, path, 0, strerror(errno));
        goto OUT;
    }
    result = cfg_parse_group(p->root, data, sb.st_size, 1);
    munmap(data, sb.st_size);
OUT:
    close(fd);
    return result>=0;
}


typedef enum {
    GROUP_START_BRACKET,
    GROUP_KEY,
    GROUP_VALUE,
    GROUP_END_BRACKET,
} GroupState;

/* 解析{}指定的Object结构 */
static int cfg_parse_group(CfgValue *val, char *data, int len, int is_root) {
    GroupState state = GROUP_END_BRACKET;
    if(is_root) {
        state=GROUP_KEY;
    }
    return 1;
}

static int cfg_parse_key(char **val, char *data, int len) {
    return 1;
}

/* 增加CfgSetting的引用计数 */
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

/* 设置错误信息 */
static inline void cfg_parser_set_error(CfgParser *p, const char *path,
                                        uint64_t line, const char *msg) {
    free(p->err_path);
    free(p->err_msg);
    p->err_path = strdup(path);
    p->err_line = line;
    p->err_msg = strdup(msg);
}
