#include "cargs_linked_list.h"

/**
 * init linked list head
 * @param head: linked list head
 * 
 */
void cargs_ll_head_init(struct cargs_llnode * const head)
{
    head->next = head;
    head->prev = head;
}

/**
 * check linked list is empty
 * @param head: linked list head
 * @return is empty
 *
 */
bool cargs_ll_empty(const struct cargs_llnode * const head)
{
    return head->next == head;
}

/**
 * insert entity before
 * @param place: inserted place
 * @param newly: newly node
 * 
 */
void cargs_ll_insert_before(struct cargs_llnode * const place,
                            struct cargs_llnode * const newly)
{
    newly->prev = place->prev;
    newly->next = place;

    place->prev->next = newly;
    place->prev = newly;
}
