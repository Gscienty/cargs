#ifndef _CARGS_ARG_TYPE_H
#define _CARGS_ARG_TYPE_H

#include "cargs_rbtree.h"
#include <stdbool.h>
#include <stddef.h>

enum cargs_arg_type {
    arg_type_null = 0x00,
    arg_type_byte,
    arg_type_short,
    arg_type_int,
    arg_type_string,

    __arg_type_std_max
};

typedef bool (*arg_type_examiner) (const char * const);
typedef void (*arg_type_transfer) (char * const, const char * const);

struct __cargs_arg_type {
    int type_code;
    size_t value_size;
    arg_type_examiner examiner;
    arg_type_transfer transfer;
    unsigned int magic;    
};

#define CARGS_ARG_TYPE_SECTION \
    __attribute__((used, aligned(1), section(".arg_type_examiner")))
#define CARGS_ARG_TYPE_NAME(n) __cargs_arg_type_name_##n
#define CARGS_ARG_TYPE_FUNCTION_NAME(n) __cargs_arg_type_function_name_##n
#define CARGS_ARG_TYPE_MAGIC 0xa29758ee

#define __$inner_arg_type_flag(n) \
    static struct __cargs_arg_type CARGS_ARG_TYPE_NAME(n) \
        CARGS_ARG_TYPE_SECTION = { \
            .type_code  = 0, \
            .value_size = 0, \
            .examiner   = NULL, \
            .transfer   = NULL, \
            .magic      = CARGS_ARG_TYPE_MAGIC \
        }

#define cargs_arg_type(c, s, e, t) \
    static struct __cargs_arg_type CARGS_ARG_TYPE_NAME(c) \
        CARGS_ARG_TYPE_SECTION = { \
            .type_code  = c, \
            .value_size = s, \
            .examiner   = e, \
            .transfer   = t, \
            .magic      = CARGS_ARG_TYPE_MAGIC \
        };


struct __cargs_arg_type_rbt {
    struct cargs_rbnode node;
    struct __cargs_arg_type *type;
};

/**
 * init
 * 
 */
void cargs_arg_type_init();

/**
 * find arg type
 * @param type_code: type code
 * @return type
 * 
 */
struct __cargs_arg_type *cargs_find_arg_type(int type_code);

/**
 * find arg type examiner
 * @param type_code: type code
 * @return: examiner
 * 
 */
arg_type_examiner cargs_find_arg_type_examiner(int type_code);

/**
 * find arg type transfer
 * @param type_code: type code
 * @return transfer
 * 
 */
arg_type_transfer cargs_find_arg_type_transfer(int type_code);

#endif
