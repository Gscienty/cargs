#include "cargs_rbtree.h"
#include <malloc.h>

/**
 * create rbtree
 * @return rbnode root
 * 
 */
struct cargs_rbroot *rbtree_root_ctor()
{
    struct cargs_rbroot *root =
        (struct cargs_rbroot *) malloc(sizeof(struct cargs_rbroot));
    if (root == NULL) {
        return NULL;
    }

    root->nil.color  = CARGS_RBTREE_COLOR_BLACK;
    root->nil.left   = &root->nil;
    root->nil.right  = &root->nil;
    root->nil.parent = &root->nil;
    root->root       = &root->nil;

    return root;
}

/**
 * create a rbtree node
 * @param root: rbtree root node
 * @param size: rbtree size
 * @return: rbtree node
 * 
 */
struct cargs_rbnode *rbtree_node_ctor(const struct cargs_rbroot * const root,
                                      const size_t size)
{
    struct cargs_rbnode *node =
        (struct cargs_rbnode *) malloc(size);
    if (node == NULL) {
        return NULL;
    }

    node->color = CARGS_RBTREE_COLOR_RED;
    node->left = (struct cargs_rbnode *) &root->nil;
    node->right = (struct cargs_rbnode *) &root->nil;
    node->parent = (struct cargs_rbnode *) &root->nil;

    return node;
}

inline static void __left_rotate(struct cargs_rbroot * const root,
                                 struct cargs_rbnode * const node)
{
    struct cargs_rbnode *right = node->right;
    node->right = right->left;
    if (right->left != &root->nil) {
        right->left->parent = node;
    }
    right->parent = node->parent;
    if (node->parent == &root->nil) {
        root->root = right;
    }
    else if (node == node->parent->left) {
        node->parent->left = right;
    }
    else {
        node->parent->right = right;
    }
    right->left = node;
    node->parent = right;
}

inline static void __right_rotate(struct cargs_rbroot * const root,
                                  struct cargs_rbnode * const node)
{
    struct cargs_rbnode *left = node->left;
    node->left = left->right;
    if (left->right != &root->nil) {
        left->right->parent = node;
    }
    left->parent = node->parent;
    if (node->parent == &root->nil) {
        root->root = left;
    }
    else if (node == node->parent->left) {
        node->parent->left = left;
    }
    else {
        node->parent->right = left;
    }
    left->right = node;
    node->parent = left;
}

/**
 * fix newly rbtree node
 * @param root: rbtree root
 * @param node: newly rbtree node
 * 
 */
void cargs_rbtree_fixup(struct cargs_rbroot * const root,
                        struct cargs_rbnode * node)
{
    struct cargs_rbnode *uncle;

    while (node->parent->color == CARGS_RBTREE_COLOR_RED) {
        if (node->parent == node->parent->parent->left) {
            uncle = node->parent->parent->right;
            if (uncle->color == CARGS_RBTREE_COLOR_RED) {
                node->parent->color = CARGS_RBTREE_COLOR_BLACK;
                uncle->color = CARGS_RBTREE_COLOR_BLACK;
                node->parent->parent->color = CARGS_RBTREE_COLOR_RED;
                node = node->parent->parent;
            }
            else {
                if (node == node->parent->right) {
                    node = node->parent;
                    __left_rotate(root, node);
                }
                node->parent->color = CARGS_RBTREE_COLOR_BLACK;
                node->parent->parent->color = CARGS_RBTREE_COLOR_RED;
                __right_rotate(root, node->parent->parent);
            }
        }
        else {
            uncle = node->parent->parent->left;
            if (uncle->color == CARGS_RBTREE_COLOR_RED) {
                node->parent->color = CARGS_RBTREE_COLOR_BLACK;
                uncle->color = CARGS_RBTREE_COLOR_BLACK;
                node->parent->parent->color = CARGS_RBTREE_COLOR_RED;
                node = node->parent->parent;
            }
            else {
                if (node == node->parent->left) {
                    node = node->parent;
                    __right_rotate(root, node);
                }
                node->parent->color = CARGS_RBTREE_COLOR_BLACK;
                node->parent->parent->color = CARGS_RBTREE_COLOR_RED;
                __left_rotate(root, node->parent->parent);
            }
        }
    }

    root->root->color = CARGS_RBTREE_COLOR_BLACK;
}

/**
 * link
 * @param parent: rbtree parent node
 * @param child_ptr: rbtree parent node's child ptr var
 * @param child: rbtree newly node
 * 
 */
void cargs_rbtree_link(struct cargs_rbnode * const parent,
                       struct cargs_rbnode ** const child_ptr,
                       struct cargs_rbnode * const child)
{
    child->parent = parent;
    *child_ptr = child;
}
