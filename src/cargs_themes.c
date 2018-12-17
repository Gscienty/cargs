#include "cargs_themes.h"
#include <stddef.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <stdio.h>

static struct __cargs_theme *__theme_start = NULL;
static struct __cargs_theme *__theme_end   = NULL;
static struct cargs_rbroot *__themes_set   = NULL;

cargs_process($__theme_flag$) { }

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
const struct __cargs_theme *cargs_find_process(const char * const fname)
{
    struct cargs_rbnode *node = __themes_set->root;
    int cmpret;

    while (node != &__themes_set->nil) {
        cmpret = __rbcmp_str(fname, node);
        if (cmpret == 0) {
            return rb_entry(node, struct __cargs_theme_rbnode, node)->tptr;
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
