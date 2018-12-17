#include "cargs_arg.h"
#include <stdlib.h>
#include <string.h>

__$inner_flag($__arg_flag$);

static struct __cargs_arg *__args_start = NULL;
static struct __cargs_arg *__args_end   = NULL;
static struct cargs_rbroot *__args_set = NULL;

static void __init_start()
{
    struct __cargs_arg *p;
    __args_start = &CARGS_ARG_STRUCT_NAME($__arg_flag$);
    while (1) {
        p = __args_start - 1;    
        if (p->magic != CARGS_ARG_MAGIC) {
            break;
        }
        __args_start--;
    }
}

static void __init_end()
{
    struct __cargs_arg *p;
    __args_end = &CARGS_ARG_STRUCT_NAME($__arg_flag$);
    while (1) {
        p = __args_end + 1;
        if (p->magic != CARGS_ARG_MAGIC) {
            break;
        }
        __args_end++;
    }
    __args_end++;
}

inline static int
__rbcmp(const char * const a, struct cargs_rbnode * const node)
{
    return strcmp(a, rb_entry(node, struct __cargs_arg_rbnode, node)->title);
}

inline static struct cargs_rbnode *__rbnode_ctor(const char * const title)
{
    struct cargs_rbnode *node =
        cargs_rbtree_node_ctor(__args_set, sizeof(struct __cargs_arg_rbnode));
    if (node == NULL) {
        return NULL;
    }

    rb_entry(node, struct __cargs_arg_rbnode, node)->title = title;

    cargs_ll_head_init(&rb_entry(node, struct __cargs_arg_rbnode, node)->args);
    return node;
}

inline static struct __cargs_arg_llnode *
__llnode_ctor(struct __cargs_arg * const arg)
{
    struct __cargs_arg_llnode *node = malloc(sizeof(struct __cargs_arg_llnode));
    if (node == NULL) {
        return NULL;
    }
    node->arg = arg;

    return node;
}

static bool __insert_rbt(const char * const title,
                         struct __cargs_arg * const arg)
{
    struct cargs_rbnode **place = &__args_set->root;
    struct cargs_rbnode *parent = &__args_set->nil;
    struct __cargs_arg_llnode *val;
    struct cargs_rbnode *newly = __args_set->root;
    int cmpret;

    val = __llnode_ctor(arg);
    if (val == NULL) {
        return false;
    }

    if (__args_set->root == &__args_set->nil) {
        __args_set->root = __rbnode_ctor(title);
        if (__args_set->root == NULL) {
            return false;
        }
        cargs_ll_insert_before(&rb_entry(__args_set->root,
                                         struct __cargs_arg_rbnode,
                                         node)->args,
                               &val->node);
    }
    else {
        while (*place != &__args_set->nil) {
            parent = *place;
            cmpret = __rbcmp(title, parent);
            if (cmpret == 0) {
                cargs_ll_insert_before(&rb_entry(parent,
                                                 struct __cargs_arg_rbnode,
                                                 node)->args,
                                       &val->node);
                return true;
            }
            else if (cmpret < 0) {
                place = &parent->left;
            }
            else {
                place = &parent->right;
            }
        }
        newly = __rbnode_ctor(title);
        if (newly == NULL) {
            return false;
        }
        cargs_ll_insert_before(&rb_entry(newly,
                                         struct __cargs_arg_rbnode,
                                         node)->args,
                               &val->node);
        cargs_rbtree_link(parent, place, newly);
    }

    cargs_rbtree_fixup(__args_set, newly);
    return true;
}

static void __init_set()
{
    struct __cargs_arg *p;
    char **title;

    __args_set = cargs_rbtree_root_ctor();
    if (__args_set == NULL) {
        exit(-1);
    }

    for (p = __args_start; p != __args_end; p++) {
        if (p == &CARGS_ARG_STRUCT_NAME($__arg_flag$)) {
            continue;
        }
        for (title = (char **) p->titles; *title != NULL; title++) {
            if(!__insert_rbt(*title, p)) {
                exit(-1);
            }
        }
    }
}

/**
 * init args (ctor args tree)
 *
 */
void cargs_args_init()
{
    __init_start();
    __init_end();

    __init_set();
}

/**
 * get args
 * @param title: arg title
 * @return: args linked list
 */
struct cargs_llnode *cargs_args_find(const char * const title)
{
    struct cargs_rbnode *node = __args_set->root;
    int cmpret;

    while (node != &__args_set->nil) {
        cmpret = __rbcmp(title, node);
        if (cmpret == 0) {
            return &rb_entry(node, struct __cargs_arg_rbnode, node)->args;
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
