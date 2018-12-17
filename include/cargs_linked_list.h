#ifndef _CARGS_LINKED_LIST_H
#define _CARGS_LINKED_LIST_H

#include <stdbool.h>

struct cargs_llnode {
    struct cargs_llnode *prev;
    struct cargs_llnode *next;
};

#define ll_entry(ptr, type, member) \
    ((type *) ((void *) ptr - (void *) (&((type *) 0)->member - 0)))

/**
 * init linked list head
 * @param head: linked list head
 * 
 */
void cargs_ll_head_init(struct cargs_llnode * const head);

/**
 * check linked list is empty
 * @param head: linked list head
 * @return is empty
 *
 */
bool cargs_ll_empty(const struct cargs_llnode * const head);

/**
 * insert entity before
 * @param place: inserted place
 * @param newly: newly node
 * 
 */
void cargs_ll_insert_before(struct cargs_llnode * const place,
                            struct cargs_llnode * const newly);

#endif
