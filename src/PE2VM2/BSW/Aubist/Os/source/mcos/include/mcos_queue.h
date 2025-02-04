/*
    Copyright (C) 2012 By eSOL Co.,Ltd. Tokyo, Japan

    This software is protected by the law and the agreement concerning
    a Japanese country copyright method, an international agreement,
    and other intellectual property right and may be used and copied
    only in accordance with the terms of such license and with the inclusion
    of the above copyright notice.

    This software or any other copies thereof may not be provided
    or otherwise made available to any other person.  No title to
    and ownership of the software is hereby transferred.

    The information in this software is subject to change without
    notice and should not be construed as a commitment by eSOL Co.,Ltd.
*/

/****************************************************************************
[mcos_queue.h] - MCOS queue operations
****************************************************************************/
#ifndef MCOS_QUEUE_H
#define MCOS_QUEUE_H

#include "mcos_basic.h"

#if !MCOS_AUTOSAR

/* singly-linked list */
typedef struct mcos_slink mcos_slink_t;

struct mcos_slink
{
    /* next link */
    mcos_slink_t * snext;
};

struct mcos_squeue
{
    /* both link (super) */
    mcos_slink_t slink;
};
typedef struct mcos_squeue mcos_squeue_t;


MCOS_INLINE void mcos_slink_initialize(mcos_slink_t * const slink);
MCOS_INLINE void mcos_slink_finalize(mcos_slink_t * const slink);
MCOS_INLINE mcos_slink_t * mcos_slink_next(const mcos_slink_t * const slink);
MCOS_INLINE mcos_bool_t mcos_slink_is_enqueued(const mcos_slink_t * const slink);
MCOS_INLINE void mcos_squeue_initialize(mcos_squeue_t * const squeue);
MCOS_INLINE void mcos_squeue_finalize(mcos_squeue_t * const squeue);
MCOS_INLINE mcos_slink_t * mcos_squeue_first(const mcos_squeue_t * const squeue);
MCOS_INLINE mcos_bool_t mcos_squeue_equals(const mcos_squeue_t * const squeue, const mcos_slink_t * const slink);
MCOS_INLINE void mcos_squeue_insert(mcos_squeue_t * const squeue, mcos_slink_t * const slink);
MCOS_INLINE mcos_slink_t * mcos_squeue_remove(mcos_squeue_t * const squeue);


/* initialize the link */
MCOS_INLINE void mcos_slink_initialize(
    mcos_slink_t * const slink)
{
    slink->snext = slink;
}

/* finalize the link */
MCOS_INLINE void mcos_slink_finalize(
    mcos_slink_t * const slink)
{
    slink->snext = NULL;
}

/* get the next link */
MCOS_INLINE mcos_slink_t * mcos_slink_next(
    const mcos_slink_t * const slink)
{
    return slink->snext;
}

/* test the link is enqueued or not */
MCOS_INLINE mcos_bool_t mcos_slink_is_enqueued(
    const mcos_slink_t * const slink)
{
    return (slink->snext != slink) ? mcos_true : mcos_false;
}


/* initialize the queue */
MCOS_INLINE void mcos_squeue_initialize(
    mcos_squeue_t * const squeue)
{
    mcos_slink_initialize(&squeue->slink);
}

/* finalize the queue */
MCOS_INLINE void mcos_squeue_finalize(
    mcos_squeue_t * const squeue)
{
    mcos_slink_finalize(&squeue->slink);
}

/* get the first link in the queue */
MCOS_INLINE mcos_slink_t * mcos_squeue_first(
    const mcos_squeue_t * const squeue)
{
    return mcos_slink_next(&squeue->slink);
}

/* does the link equal to the queue */
MCOS_INLINE mcos_bool_t mcos_squeue_equals(
    const mcos_squeue_t * const squeue,
    const mcos_slink_t * const slink)
{
    return (&squeue->slink == slink) ? mcos_true : mcos_false;
}

/* insert the link before the next link in the queue */
MCOS_INLINE void mcos_squeue_insert(
    mcos_squeue_t * const squeue,
    mcos_slink_t * const slink)
{
    slink->snext = squeue->slink.snext;
    squeue->slink.snext = slink;
}

/* remove the link from the queue first */
MCOS_INLINE mcos_slink_t * mcos_squeue_remove(
    mcos_squeue_t * const squeue)
{
    mcos_slink_t * snext;

    snext = squeue->slink.snext;
    squeue->slink.snext = snext->snext;
    snext->snext = snext;

    return snext;
}

#endif /* #if !MCOS_AUTOSAR */

/* -------- */

/* Node in a doubly-linked list */
typedef struct mcos_link mcos_link_t;

struct mcos_link
{
    /* next link */
    mcos_link_t * next;
    /* back link */
    mcos_link_t * back;
};

struct mcos_queue
{
    /* both link (super) */
    mcos_link_t link;
};
typedef struct mcos_queue mcos_queue_t;

/* NOTE: the implementation below is for a circular doubly-linked list, not an opened one */

MCOS_INLINE void mcos_link_initialize(mcos_link_t * const link);
MCOS_INLINE mcos_link_t * mcos_link_next(const mcos_link_t * const link);
MCOS_INLINE void mcos_queue_initialize(mcos_queue_t * const queue);
MCOS_INLINE mcos_link_t * mcos_queue_first(const mcos_queue_t * const queue);
MCOS_INLINE int32_t mcos_queue_size(const mcos_queue_t * const queue);
MCOS_INLINE void mcos_queue_insert(mcos_link_t * const link, mcos_link_t * const next);
MCOS_INLINE void mcos_queue_remove(mcos_link_t * const link);

#if !MCOS_AUTOSAR
MCOS_INLINE void mcos_link_finalize(mcos_link_t * const link);
MCOS_INLINE mcos_link_t * mcos_link_back(const mcos_link_t * const link);
MCOS_INLINE mcos_bool_t mcos_link_is_enqueued(const mcos_link_t * const link);
MCOS_INLINE void mcos_queue_finalize(mcos_queue_t * const queue);
MCOS_INLINE mcos_bool_t mcos_queue_equals(const mcos_queue_t * const queue, const mcos_link_t * const link);
MCOS_INLINE void mcos_queue_push(mcos_queue_t * const queue, mcos_link_t * const link);
MCOS_INLINE mcos_link_t * mcos_queue_pop(const mcos_queue_t * const queue);
#endif /* #if !MCOS_AUTOSAR */

/* initialize the link */
MCOS_INLINE void mcos_link_initialize(
    mcos_link_t * const link)
{
    link->next = link;
    link->back = link;
}

#if !MCOS_AUTOSAR
/* finalize the link */
MCOS_INLINE void mcos_link_finalize(
    mcos_link_t * const link)
{
    link->back = NULL;
    link->next = NULL;
}
#endif /* #if !MCOS_AUTOSAR */

/* get the next link */
MCOS_INLINE mcos_link_t * mcos_link_next(
    const mcos_link_t * const link)
{
    return link->next;
}

#if !MCOS_AUTOSAR
/* get the back link */
MCOS_INLINE mcos_link_t * mcos_link_back(
    const mcos_link_t * const link)
{
    return link->back;
}

/* test the link is enqueued or not */
MCOS_INLINE mcos_bool_t mcos_link_is_enqueued(
    const mcos_link_t * const link)
{
    return (link->next != link) ? mcos_true : mcos_false;
}

#endif /* #if !MCOS_AUTOSAR */

/* initialize the queue */
MCOS_INLINE void mcos_queue_initialize(
    mcos_queue_t * const queue)
{
    mcos_link_initialize(&queue->link);
}

#if !MCOS_AUTOSAR
/* finalize the queue */
MCOS_INLINE void mcos_queue_finalize(
    mcos_queue_t * const queue)
{
    mcos_link_finalize(&queue->link);
}
#endif /* #if !MCOS_AUTOSAR */

/* get the first link in the queue */
MCOS_INLINE mcos_link_t * mcos_queue_first(
    const mcos_queue_t * const queue)
{
    return mcos_link_next(&queue->link);
}

#if !MCOS_AUTOSAR
/* does the link equal to the queue */
MCOS_INLINE mcos_bool_t mcos_queue_equals(
    const mcos_queue_t * const queue,
    const mcos_link_t * const link)
{
    return (&queue->link == link) ? mcos_true : mcos_false;
}
#endif /* #if !MCOS_AUTOSAR */

/* size of the queue */
MCOS_INLINE int32_t mcos_queue_size(
    const mcos_queue_t * const queue)
{
    int32_t count;
    mcos_link_t * link;

    link = queue->link.next;
    count = 0;
    while(link != &queue->link)
    {
        count++;
        link = link->next;
    }

    return count;
}

/* insert the link before the next link in the queue */
MCOS_INLINE void mcos_queue_insert(
    mcos_link_t * const link,
    mcos_link_t * const next)
{
    link->next = next;
    link->back = next->back;
    next->back->next = link;
    next->back = link;
}

/* remove the link from the queue */
MCOS_INLINE void mcos_queue_remove(
    mcos_link_t * const link)
{
    link->back->next = link->next;
    link->next->back = link->back;
    link->next = link;
    link->back = link;
}

#if !MCOS_AUTOSAR
/* push the link to the queue */
MCOS_INLINE void mcos_queue_push(
    mcos_queue_t * const queue,
    mcos_link_t * const link)
{
    mcos_queue_insert(link, &queue->link);
} /* MCOS_INLINE void mcos_queue_push( */

/* pop the link from the queue */
MCOS_INLINE mcos_link_t * mcos_queue_pop(
    const mcos_queue_t * const queue)
{
    mcos_link_t * link;

    link = mcos_queue_first(queue);
    mcos_queue_remove(link);
    return link;
}
#endif /* #if !MCOS_AUTOSAR */

#endif /* #ifndef MCOS_QUEUE_H */

