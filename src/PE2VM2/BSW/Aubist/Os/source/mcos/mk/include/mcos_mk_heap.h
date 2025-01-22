/*
    Copyright (C) 2016 eSOL Co.,Ltd. Tokyo, Japan

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
[ mcos_mk_heap.h ] - eMCOS/MK heap local header
****************************************************************************/
#ifndef MCOS_MK_HEAP_H
#define MCOS_MK_HEAP_H

#if !MCOS_AUTOSAR

#include "mcos_mk.h"
#include "mcos/mcos_heap_id.h"

typedef struct heap_obj heap_obj_t;

/* heap  virtual method table (micro kernel memory allocator) */
typedef struct heap_vtbl_st heap_vtbl_t;

#if MCOS_CFG_HEAPSRV_ENABLE != 0U
/* heap server request */
typedef struct heapsrv heapsrv_t;
struct heapsrv
{
    /* server id */
    mcos_id_t servid;
};
#endif /* #if MCOS_CFG_HEAPSRV_ENABLE != 0U */

/* heap  control block */
struct heapcb_st
{
    uint8_t mkmemobjid[MCOS_HEAP_LAYER_MAX];
#if MCOS_CFG_HEAPSRV_ENABLE != 0U
    heapsrv_t heapsrv[MCOS_HEAP_SERVER_NUM];
#endif /* #if MCOS_CFG_HEAPSRV_ENABLE != 0U */
    const heap_vtbl_t * vtbl;
    heap_obj_t * heap_obj;
};

/* Get allocator vtbl */
const heap_vtbl_t * mcos_heap_get_allocator (void);

#if MCOS_CFG_HEAPSRV_ENABLE == 0U

/* heap method table (client request) */
typedef struct
{
    /* function to initialize heap */
    void (* initialize)(heap_obj_t * heap_obj, void * addr, size_t size);

    /* function to regist heap on mkcb */
    void (* regist)(heap_obj_t * heap_obj, void * addr, size_t size);

    /* function to finalize heap */
    void (* finalize)(heap_obj_t * heap_obj);

    /* Get heap object control block size */
    uint32_t (* getObjCBSize) (void);

    /* function to add memory to heap object */
    void * (* add)(heap_obj_t * heap_obj, void * addr, size_t size);

    /* function to allcate from heap */
    void * (* allocate)(heap_obj_t * heap_obj, size_t size, size_t * allocated);

    /* function to free to heap */
    void (* free)(heap_obj_t * heap_obj, void * addr);

    /* function to reference heap */
    mcos_er_t (* reference)(heap_obj_t * heap_obj, mcos_heap_mem_info_t * mem_ref);

    /* function to debug heap */
    void (* debug)(heap_obj_t * heap_obj);
} heap_allocator_request_t;

/* get request vtbl */
const heap_allocator_request_t * mcos_heap_get_request(void);

#if MCOS_CFG_HEAPSRV_ENABLE == 0U
/* initialize heap table */
void mcos_heap_allocator_initialize(void);
#endif /* #if MCOS_CFG_HEAPSRV_ENABLE == 0U */

#endif /* #if MCOS_CFG_HEAPSRV_ENABLE == 0U */


/* heap initialization*/
uint8_t * mcos_heap_init (
    const mkcb_t * mkcb,
    uint8_t * end);

/*
 * Allocate the core local memory from micro kernel internal
 *
 * When there are no memories in a microkernel, a microkernel doesn't get
 * a memory from the heap server.
 */
mcos_er_t heap_allocate_corelm_internal (
    const mkcb_t * mkcb,
    size_t size,
    void ** addr);

#endif /* !MCOS_AUTOSAR */

#endif /* #ifndef MCOS_MK_HEAP_H */
