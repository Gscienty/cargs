#include "cargs_arg_type.h"
#include <stdlib.h>

__$inner_arg_type_flag($__arg_type_flag$);
static struct __cargs_arg_type *__args_type_start = NULL;
static struct __cargs_arg_type *__args_type_end   = NULL;
static struct cargs_rbroot *__args_type_code      = NULL;

static bool __insert_type_rbt(struct __cargs_arg_type *val)
{
    struct cargs_rbnode **place = &__args_type_code->root;
    struct cargs_rbnode *parent = &__args_type_code->nil;
    int cmpret;
    struct cargs_rbnode *node =
        cargs_rbtree_node_ctor(__args_type_code,
                               sizeof(struct __cargs_arg_type_rbt));
    if (node == NULL) {
        return false;
    }
    rb_entry(node, struct __cargs_arg_type_rbt, node)->type = val;

    if (__args_type_code->root == &__args_type_code->nil) {
        __args_type_code->root = node;
    }
    else {
        while (*place != &__args_type_code->nil) {
            parent = *place;
            cmpret = val->type_code
                - rb_entry(parent, struct __cargs_arg_type_rbt, node)
                ->type->type_code;
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

    cargs_rbtree_fixup(__args_type_code, node);
    return true;
}

static void __init_arg_type_code()
{
    struct __cargs_arg_type *p;

    __args_type_code = cargs_rbtree_root_ctor();
    if (__args_type_code == NULL) {
        exit(-1);
    }

    for (p = __args_type_start; p != __args_type_end; p++) {
        if (p == &CARGS_ARG_TYPE_NAME($__arg_type_flag$)) {
            continue;
        }

        if (!__insert_type_rbt(p)) {
            exit(-1);
        }
    }
}

static void __init_type_start()
{
    struct __cargs_arg_type *p;
    __args_type_start = &CARGS_ARG_TYPE_NAME($__arg_type_flag$);
    while (1) {
        p = __args_type_start - 1;    
        if (p->magic != CARGS_ARG_TYPE_MAGIC) {
            break;
        }
        __args_type_start--;
    }
}

static void __init_type_end()
{
    struct __cargs_arg_type *p;
    __args_type_end = &CARGS_ARG_TYPE_NAME($__arg_type_flag$);
    while (1) {
        p = __args_type_end + 1;
        if (p->magic != CARGS_ARG_TYPE_MAGIC) {
            break;
        }
        __args_type_end++;
    }
    __args_type_end++;
}

/**
 * init
 * 
 */
void cargs_arg_type_init()
{
    __init_type_start();
    __init_type_end();

    __init_arg_type_code();
}

static bool __default_examiner(const char * const arg)
{
    (void) arg;
    return false;
}

static struct __cargs_arg_type *__find(int type_code)
{
    int cmp;
    struct cargs_rbnode *node = __args_type_code->root;

    while (node != &__args_type_code->nil) {
        cmp = type_code
            - rb_entry(node, struct __cargs_arg_type_rbt, node)
            ->type->type_code;
        if (cmp == 0) {
            return rb_entry(node, struct __cargs_arg_type_rbt, node)
                ->type;
        }
        else if (cmp < 0) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }

    return NULL;
}

/**
 * find arg type examiner
 * @param type_code: type code
 * @return: examiner
 * 
 */
arg_type_examiner cargs_find_arg_type_examiner(int type_code)
{
    struct __cargs_arg_type *type = __find(type_code);
    if (type == NULL) {
        return __default_examiner;
    }

    return type->examiner;
}

void __default_transfer(char * const buf,
                        const char * const arg)
{
    (void) buf;
    (void) arg;
}

/**
 * find arg type transfer
 * @param type_code: type code
 * @return transfer
 * 
 */
arg_type_transfer cargs_find_arg_type_transfer(int type_code)
{
    struct __cargs_arg_type *type = __find(type_code);
    if (type == NULL) {
        return __default_transfer;
    }

    return type->transfer;
}

/**
 * find arg type
 * @param type_code: type code
 * @return type
 * 
 */
struct __cargs_arg_type *cargs_find_arg_type(int type_code)
{
    return __find(type_code);
}
