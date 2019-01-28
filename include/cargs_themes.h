#ifndef _CARGS_THEMES_H
#define _CARGS_THEMES_H

#include "cargs_set_define.h"
#include "cargs_rbtree.h"
#include "cargs_arg.h"

#define CARGS_THEME_ARGS_MAX 16

#define CARGS_THEME_SECTION \
    __attribute__((used, aligned(1), section(".cargs_theme")))
#define CARGS_THEME_STRUCT_NAME(n) __cargs_theme_struct_name_##n
#define CARGS_THEME_FUNCTION_NAME(n) __cargs_theme_function_name_##n
#define CARGS_THEME_MAGIC 0xca2d27ae

struct __cargs_theme {
    const char *name;
    struct __cargs_theme_arg args[CARGS_THEME_ARGS_MAX];
    void *fptr;
    unsigned int magic;
};

#define cargs_process(fname, _args, ...)                       \
    void CARGS_THEME_FUNCTION_NAME(fname)(__VA_ARGS__);        \
    static struct __cargs_theme CARGS_THEME_STRUCT_NAME(fname) \
    CARGS_THEME_SECTION = {                                    \
        .name  = #fname,                                       \
        .args  = _args,                                        \
        .fptr  = (void *) CARGS_THEME_FUNCTION_NAME(fname),    \
        .magic = CARGS_THEME_MAGIC                             \
    };                                                         \
    void CARGS_THEME_FUNCTION_NAME(fname)(__VA_ARGS__)

struct __cargs_theme_rbnode {
    struct cargs_rbnode node;
    const struct __cargs_theme *tptr;
};

/**
 * init processes
 * 
 */
void cargs_processes_init();

/**
 * find special process
 * @param name: process name
 * @return: process struct ptr
 * 
 */
const void *cargs_find_process(const char * const fname);

/**
 * satisfy process
 * @return: satisfy process
 * 
 */
const struct __cargs_theme *cargs_satisfy_process();

/**
 * process args size
 * @return: args size
 * 
 */
size_t cargs_process_args_size(const struct __cargs_theme * const process);

/**
 * process args count
 * @return args count
 *
 */
int cargs_process_args_count(const struct __cargs_theme * const process);

#endif
