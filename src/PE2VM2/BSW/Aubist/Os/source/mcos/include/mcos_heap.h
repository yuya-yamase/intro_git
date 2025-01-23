/*
    Copyright (C) 2013 eSOL Co.,Ltd. Tokyo, Japan

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
[ mcos_heap.h ] - MCOS heap manager header
****************************************************************************/
#ifndef MCOS_HEAP_H
#define MCOS_HEAP_H

#include "mcos_cmn.h"
#include "mcos_heap_cfg.h"

/* allocate from core local memory */
mcos_er_t heap_allocate_corelm (
    const mkcb_t * mkcb,
    size_t size,
    void ** addr);

/* Release the memory allocated by heap_allocate_corelm() */
mcos_er_t heap_free_corelm (
    const mkcb_t * mkcb,
    void * addr);

/* allocate from cluster local memory */
void * heap_allocate_clusterlm (
    size_t size);

/* Release the memory allocated by heap_free_****   */
void  heap_free_anylm (
    void * addr);

/* debug */
mcos_er_t mcos_heap_debug (
    mcos_id_t heapid);


#endif /* #ifndef MCOS_HEAP_H */

