#ifndef _CARGS_ARG_H
#define _CARGS_ARG_H

#include <stdbool.h>
#include <stddef.h>
#include "cargs_rbtree.h"
#include "cargs_linked_list.h"

enum cargs_arg_type {
    arg_type_null = 0x00,
    arg_type_byte,
    arg_type_short,
    arg_type_int,
    arg_type_string,
};

struct __cargs_arg {
    const struct __cargs_arg *prerequisite;
    char * titles[16];
    bool enable;
    const enum cargs_arg_type args_type[16];
    char *params[16];

    unsigned int magic;
};

#define CARGS_ARG_SECTION \
    __attribute__((used, aligned(1), section(".args")))
#define CARGS_ARG_STRUCT_NAME(n) __cargs_arg_name_##n
#define CARGS_ARG_MAGIC 0xca294a29

#define __$inner_flag(n) \
    static struct __cargs_arg CARGS_ARG_STRUCT_NAME(n) \
        CARGS_ARG_SECTION = { \
            .prerequisite = NULL, \
            .titles       = { NULL }, \
            .enable       = false, \
            .args_type    = { arg_type_null }, \
            .params       = { NULL }, \
            .magic        = CARGS_ARG_MAGIC \
        }

#define __SET__(...) { __VA_ARGS__ }

#define cargs_flag(n, ts) \
    static struct __cargs_arg CARGS_ARG_STRUCT_NAME(n) \
        CARGS_ARG_SECTION = { \
            .prerequisite = NULL, \
            .titles       = ts, \
            .enable       = false, \
            .args_type    = { arg_type_null }, \
            .params       = { NULL }, \
            .magic        = CARGS_ARG_MAGIC \
        }

#define cargs_subflag(p, n, ts) \
    static struct __cargs_arg CARGS_ARG_STRUCT_NAME(n) \
        CARGS_ARG_SECTION = { \
            .prerequisite = &CARGS_ARG_STRUCT_NAME(n), \
            .titles       = ts, \
            .enable       = false, \
            .args_type    = { }, \
            .params       = { }, \
            .magic        = CARGS_ARG_MAGIC \
        }

struct __cargs_arg_rbnode {
    struct cargs_rbnode node;
    struct cargs_llnode args;
    const char *title;
};

struct __cargs_arg_llnode {
    struct cargs_llnode node;
    struct __cargs_arg *arg;
};

/**
 * init args (ctor args tree)
 *
 */
void cargs_args_init();

/**
 * get args
 * @param title: arg title
 * @return: args linked list
 */
struct cargs_llnode *cargs_args_find(const char * const title);

#endif
