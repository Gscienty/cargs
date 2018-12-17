#ifndef _CARGS_ARG_TYPE_H
#define _CARGS_ARG_TYPE_H

#include "cargs_rbtree.h"
#include <stdbool.h>

enum cargs_arg_type {
    arg_type_null = 0x00,
    arg_type_byte,
    arg_type_short,
    arg_type_int,
    arg_type_string,

    __arg_type_std_max
};

typedef bool (*arg_type_examiner) (const char * const);

struct __cargs_arg_type_examiner {
    int type_code;
    arg_type_examiner fptr;
    unsigned int magic;    
};

#define CARGS_ARG_TYPE_EXAMINER_SECTION \
    __attribute__((used, aligned(1), section(".arg_type_examiner")))
#define CARGS_ARG_TYPE_EXAMINER_NAME(n) __cargs_arg_type_examiner_name_##n
#define CARGS_ARG_TYPE_EXAMINER_FUNCTION_NAME(n) __cargs_arg_type_examiner_function_name_##n
#define CARGS_ARG_TYPE_EXAMINER_MAGIC 0xa29758ee

#define __$inner_arg_examiner_flag(n) \
    static struct __cargs_arg_type_examiner CARGS_ARG_TYPE_EXAMINER_NAME(n) \
        CARGS_ARG_TYPE_EXAMINER_SECTION = { \
            .type_code = 0, \
            .fptr = NULL, \
            .magic = CARGS_ARG_TYPE_EXAMINER_MAGIC \
        }

#define cargs_arg_type(c, fn, arg) \
    bool CARGS_ARG_TYPE_EXAMINER_FUNCTION_NAME(fn) (const char * const); \
    static struct __cargs_arg_type_examiner CARGS_ARG_TYPE_EXAMINER_NAME(fn) \
        CARGS_ARG_TYPE_EXAMINER_SECTION = { \
            .type_code = c, \
            .fptr = CARGS_ARG_TYPE_EXAMINER_FUNCTION_NAME(fn), \
            .magic = CARGS_ARG_TYPE_EXAMINER_MAGIC \
        }; \
    bool CARGS_ARG_TYPE_EXAMINER_FUNCTION_NAME(fn) (const char * const arg)


struct __cargs_arg_type_rbt {
    struct cargs_rbnode node;
    struct __cargs_arg_type_examiner *examiner;
};

/**
 * init
 * 
 */
void cargs_arg_type_init();

/**
 * find arg type examiner
 * @param type_code: type code
 * @return: examiner
 * 
 */
arg_type_examiner cargs_find_arg_type_examiner(int type_code);

#endif
