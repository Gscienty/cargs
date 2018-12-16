#ifndef _CARGS_RBTREE_H
#define _CARGS_RBTREE_H

#include <stddef.h>

enum cargs_rbtree_color {
    CARGS_RBTREE_COLOR_RED,
    CARGS_RBTREE_COLOR_BLACK
};

struct cargs_rbnode {
    enum cargs_rbtree_color color;
    struct cargs_rbnode *parent;
    struct cargs_rbnode *left;
    struct cargs_rbnode *right;
};

struct cargs_rbroot {
    struct cargs_rbnode nil;
    struct cargs_rbnode *root;
};

/**
 * create rbtree
 * @return rbnode root
 * 
 */
struct cargs_rbroot *rbtree_root_ctor();

/**
 * create a rbtree node
 * @param root: rbtree root node
 * @param size: rbtree size
 * @return: rbtree node
 * 
 */
struct cargs_rbnode *rbtree_node_ctor(const struct cargs_rbroot * const root,
                                      const size_t size);

/**
 * fix newly rbtree node
 * @param root: rbtree root
 * @param node: newly rbtree node
 * 
 */
void cargs_rbtree_fixup(struct cargs_rbroot * const root,
                        struct cargs_rbnode * node);

/**
 * link
 * @param parent: rbtree parent node
 * @param child_ptr: rbtree parent node's child ptr var
 * @param child: rbtree newly node
 * 
 */
void cargs_rbtree_link(struct cargs_rbnode * const parent,
                       struct cargs_rbnode ** const child_ptr,
                       struct cargs_rbnode * const child);

#endif
