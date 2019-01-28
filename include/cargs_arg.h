#ifndef _CARGS_ARG_H
#define _CARGS_ARG_H

#include <stdbool.h>
#include <stddef.h>
#include "cargs_set_define.h"
#include "cargs_rbtree.h"
#include "cargs_linked_list.h"
#include "cargs_arg_type.h"

#define CARGS_ARG_TITLE_MAX 16
#define CARGS_ARG_TYPE_MAX 16
#define CARGS_ARG_PARAMS_MAX 16

struct __cargs_arg {
    char *_inner_name;
    const struct __cargs_arg *prerequisite;
    char *titles[CARGS_ARG_TITLE_MAX];
    bool enable;
    const enum cargs_arg_type args_type[CARGS_ARG_TYPE_MAX];
    char *params[CARGS_ARG_PARAMS_MAX];

    int params_count_cache;

    unsigned int magic;
};

#define CARGS_ARG_SECTION \
    __attribute__((used, aligned(1), section(".args")))
#define CARGS_ARG_STRUCT_NAME(n) __cargs_arg_name_##n
#define CARGS_ARG_MAGIC 0xca294a29

#define __$inner_arg_flag(n)                           \
    static struct __cargs_arg CARGS_ARG_STRUCT_NAME(n) \
        CARGS_ARG_SECTION = {                          \
            ._inner_name        = #n,                  \
            .prerequisite       = NULL,                \
            .titles             = { NULL },            \
            .enable             = false,               \
            .args_type          = { arg_type_null },   \
            .params             = { NULL },            \
            .params_count_cache = -1,                  \
            .magic              = CARGS_ARG_MAGIC      \
        }

#define cargs_flag(n, ts)                              \
    static struct __cargs_arg CARGS_ARG_STRUCT_NAME(n) \
        CARGS_ARG_SECTION = {                          \
            ._inner_name        = #n,                  \
            .prerequisite       = NULL,                \
            .titles             = ts,                  \
            .enable             = false,               \
            .args_type          = { arg_type_null },   \
            .params             = { NULL },            \
            .params_count_cache = -1,                  \
            .magic              = CARGS_ARG_MAGIC      \
        }

#define cargs_subflag(p, n, ts)                              \
    static struct __cargs_arg CARGS_ARG_STRUCT_NAME(n)       \
        CARGS_ARG_SECTION = {                                \
            ._inner_name        = #n,                        \
            .prerequisite       = &CARGS_ARG_STRUCT_NAME(p), \
            .titles             = ts,                        \
            .enable             = false,                     \
            .args_type          = { arg_type_null },         \
            .params             = { NULL },                  \
            .params_count_cache = -1,                        \
            .magic              = CARGS_ARG_MAGIC            \
        }

#define cargs_arg(n, ts, pts)                          \
    static struct __cargs_arg CARGS_ARG_STRUCT_NAME(n) \
        CARGS_ARG_SECTION = {                          \
            ._inner_name        = #n,                  \
            .prerequisite       = NULL,                \
            .titles             = ts,                  \
            .enable             = false,               \
            .args_type          = pts,                 \
            .params             = { NULL },            \
            .params_count_cache = -1,                  \
            .magic              = CARGS_ARG_MAGIC      \
        }

#define cargs_subarg(p, n, ts, pts)                          \
    static struct __cargs_arg CARGS_ARG_STRUCT_NAME(n)       \
        CARGS_ARG_SECTION = {                                \
            ._inner_name        = #n,                        \
            .prerequisite       = &CARGS_ARG_STRUCT_NAME(p), \
            .titles             = ts,                        \
            .enable             = false,                     \
            .args_type          = pts,                       \
            .params             = { NULL },                  \
            .params_count_cache = -1,                        \
            .magic              = CARGS_ARG_MAGIC            \
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

struct __cargs_theme_arg {
    bool required;
    const struct __cargs_arg * const arg;
};

#define cargs_theme_arg(_arg, _required) {  \
        .required = _required,              \
        .arg = &CARGS_ARG_STRUCT_NAME(_arg) \
    }

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

/**
 * transfer command line args
 * @param argc: argc
 * @param argv: argv
 * 
 */
bool cargs_transfer(int argc, char **argv);

/**
 * get args size
 * @param arg
 * @return args size
 * 
 */
size_t cargs_arg_size(const struct __cargs_arg * const arg);

/**
 * get args count
 * @param arg
 * @return arg size
 * 
 */
int cargs_arg_count(const struct __cargs_arg * const arg);

#endif
