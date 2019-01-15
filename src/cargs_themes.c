#include "cargs_themes.h"
#include <stddef.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static struct __cargs_theme *__theme_start = NULL;
static struct __cargs_theme *__theme_end   = NULL;
static struct cargs_rbroot *__themes_set   = NULL;

cargs_process($__theme_flag$, __SET__()) { }

static void __init_start()
{
    struct __cargs_theme *p;
    __theme_start = &CARGS_THEME_STRUCT_NAME($__theme_flag$);
    while (1) {
        p = __theme_start - 1;    
        if (p->magic != CARGS_THEME_MAGIC) {
            break;
        }
        __theme_start--;
    }
}

static void __init_end()
{
    struct __cargs_theme *p;
    __theme_end = &CARGS_THEME_STRUCT_NAME($__theme_flag$);
    while (1) {
        p = __theme_end + 1;
        if (p->magic != CARGS_THEME_MAGIC) {
            break;
        }
        __theme_end++;
    }
    __theme_end++;
}

static int __rbcmp(struct cargs_rbnode * const a, struct cargs_rbnode * const b)
{
    return strcmp(rb_entry(a, struct __cargs_theme_rbnode, node)->tptr->name,
                  rb_entry(b, struct __cargs_theme_rbnode, node)->tptr->name);
}

static bool __insert_rbt(struct cargs_rbnode *node)
{
    struct cargs_rbnode **place = &__themes_set->root;
    struct cargs_rbnode *parent = &__themes_set->nil;
    int cmpret;

    if (__themes_set->root == &__themes_set->nil) {
        __themes_set->root = node;
    }
    else {
        while (*place != &__themes_set->nil) {
            parent = *place;
            cmpret = __rbcmp(node, parent);
            if (cmpret == 0) {
                return false;
            }
            else if (cmpret < 0) {
                place = &parent->left;
            }
            else {
                place = &parent->right;
            }
        }
        cargs_rbtree_link(parent, place, node);
    }

    cargs_rbtree_fixup(__themes_set, node);
    return true;
}

static bool __insert_themes_set(const struct __cargs_theme *theme)
{
    struct cargs_rbnode *node =
        cargs_rbtree_node_ctor(__themes_set,
                               sizeof(struct __cargs_theme_rbnode));
    if (node == NULL) {
        return false;
    }

    rb_entry(node, struct __cargs_theme_rbnode, node)->tptr = theme;

    return __insert_rbt(node);
}

static void __init_set()
{
    struct __cargs_theme *p;

    __themes_set = cargs_rbtree_root_ctor();
    if (__themes_set == NULL) {
        exit(-1);
    }

    for (p = __theme_start; p != __theme_end; p++) {
        if (p == &CARGS_THEME_STRUCT_NAME($__theme_flag$)) {
            continue;
        }
        if (!__insert_themes_set(p)) {
            exit(-1);
        }
    }
}

/**
 * init processes
 * 
 */
void cargs_processes_init()
{
    __init_start();
    __init_end();

    __init_set();
}

static int __rbcmp_str(const char * const a, struct cargs_rbnode * const b)
{
    return strcmp(a, rb_entry(b, struct __cargs_theme_rbnode, node)
                  ->tptr->name);
}

/**
 * find special process
 * @param name: process name
 * @return: process struct ptr
 * 
 */
const void *cargs_find_process(const char * const fname)
{
    struct cargs_rbnode *node = __themes_set->root;
    int cmpret;

    while (node != &__themes_set->nil) {
        cmpret = __rbcmp_str(fname, node);
        if (cmpret == 0) {
            return rb_entry(node, struct __cargs_theme_rbnode, node)
                ->tptr->fptr;
        }
        else if (cmpret < 0) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }

    return NULL;
}

static bool __satisfy(struct __cargs_theme * const p)
{
    int i;
    if (!p->args[0].arg) {
        return false;
    }
    
    for (i = 0;
         !p->args[i].arg && i < CARGS_THEME_ARGS_MAX;
         i++) {
        if (p->args[i].required && !p->args[i].arg->enable) {
            return false;
        }
    }

    return true;
}

/**
 * satisfy process
 * 
 */
const struct __cargs_theme *cargs_satisfy_process()
{
    struct __cargs_theme *p;
    
    for (p = __theme_start; p != __theme_end; p++) {
        if (p == &CARGS_THEME_STRUCT_NAME($__theme_flag$)) {
            continue;
        }
        if (__satisfy(p)) {
            return p;
        }
    }

    return NULL;
}

/**
 * process args size
 * @return: args size
 * 
 */
size_t cargs_process_args_size(const struct __cargs_theme * const process)
{
    size_t ret = 0;
    int i;

    for (i = 0;
         i < CARGS_THEME_ARGS_MAX
         && process->args[i].arg;
         i++) {
        ret += cargs_arg_size(process->args[i].arg);
    }

    return ret;
}

/**
 * process args count
 * @return args count
 *
 */
int cargs_process_args_count(const struct __cargs_theme * const process)
{
    int i;
    int ret = 0;

    for (i = 0;
         i < CARGS_THEME_ARGS_MAX
         && process->args[i].arg;
         i++) {
        ret += cargs_arg_count(process->args[i].arg);
    }


    return ret;
}
