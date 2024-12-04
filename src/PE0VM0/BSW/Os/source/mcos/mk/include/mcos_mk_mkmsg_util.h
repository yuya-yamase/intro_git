/*
    Copyright (C) 2018 eSOL Co.,Ltd. Tokyo, Japan

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
[ mcos_mk_mkmsg_util.h ] - eMCOS mkmsg implementation utility
****************************************************************************/
#ifndef MCOS_MK_MKMSG_UTIL_H
#define MCOS_MK_MKMSG_UTIL_H

#include "mcos_mk_local.h"

#if MCOS_AUTOSAR
#include <ar_kernel_impl.h>
#endif /* #if MCOS_AUTOSAR */

/*
 * This file is mkmsg utility library.
 * Contains implementation fragment of dependency part for standard environment.
 * This file may or may not be used when implementing dependencies.
 *
 * In this file, standard environment is ...
 * - There is shared memory between the cores. (UMA or NUMA)
 * - It is possible to access memory by standard load/store instructions.
 * - mcos_mkmsg_if_spinlock_XXX() allows exclusive access to memory.
 *
 * This file provides following compatible functions.
 * Provided function's prefix is mcos_mkmsg_util_*.
 * - mcos_mkmsg_request_send
 * - mcos_mkmsg_reply_receive
 * - mcos_mkmsg_request_reply_receive
 * - mcos_mkmsg_request_receive
 * - mcos_mkmsg_request_send_async
 * - mcos_mkmsg_request_send_async_multi
 */

/*
 * ATTENTION!
 *
 * Please define the followings before including this file.
 *
 * macro
 * - MCOS_MKMSG_SYNC_IS_ENABLED
 * - MCOS_MKMSG_ASYNC_IS_ENABLED
 * - MCOS_MKMSG_ASYNC_MULTI_IS_ENABLED
 * - MCOS_RINGBUF_VREQUEST_MAX_SIZE
 * - MCOS_RINGBUF_ROUNDUP()
 * - MCOS_MKMSG_SYNC_BUF_SIZE
 * - MCOS_MKMSG_ASYNC_BUF_SIZE
 * - MCOS_MKMSG_MATYPE
 * - MCOS_MKMSG_MATYPE_UMA
 * - MCOS_MKMSG_MATYPE_NUMA
 *
 * type (and structure member)
 * - mcos_ringbuf_uint_t
 * - mcos_ringbuf_index_t
 * - mcos_ringbuf_vunit_t
 * - mcos_ringbuf_t
 *      volatile mcos_ringbuf_index_t   .read
 *      volatile mcos_ringbuf_index_t   .size
 * - mkmsg_buf_t
 *
 * type (and structure member) for MCOS_MKMSG_SYNC_IS_ENABLED
 * - mkmsg_replycb_t
 *      volatile mcos_ringbuf_uint_t    .reply_state
 *      mcos_ringbuf_vunit_t []         .reply_data     (numa)
 * - mcos_ringbuf_funit_t
 *      const void *                    .request        (uma)
 *      void *                          .reply          (uma)
 *      mcos_ringbuf_vunit_t []         .request        (numa)
 *      mkmsg_replycb_t *               .replycb
 *
 * Please implements the following functions.
 *
 * - mcos_mkmsg_if_buf_get_by_lcid
 * - mcos_mkmsg_if_buf_get_current
 * - mcos_mkmsg_if_memory_copy
 * - mcos_mkmsg_if_memory_copy_aligned
 * - mcos_mkmsg_if_memory_barrier (sync)
 * - mcos_mkmsg_if_interrupt_send
 * - mcos_mkmsg_if_spinlock_get
 * - mcos_mkmsg_if_spinlock_release
 * - mcos_mkmsg_if_sync_get_head (sync)
 * - mcos_mkmsg_if_sync_get_data (sync)
 * - mcos_mkmsg_if_sync_get_replycb (sync)
 * - mcos_mkmsg_if_sync_get_replycb_state_addr (sync)
 * - mcos_mkmsg_if_async_get_head (async)
 * - mcos_mkmsg_if_async_get_data (async)
 */

#if (MCOS_MKMSG_MATYPE != MCOS_MKMSG_MATYPE_UMA) && (MCOS_MKMSG_MATYPE != MCOS_MKMSG_MATYPE_NUMA)
#error Unknown MCOS_MKMSG_MATYPE
#endif /* #if (MCOS_MKMSG_MATYPE != MCOS_MKMSG_MATYPE_UMA) && (MCOS_MKMSG_MATYPE != MCOS_MKMSG_MATYPE_NUMA) */

#if (MCOS_MKMSG_ASYNC_MULTI_IS_ENABLED && !MCOS_MKMSG_ASYNC_IS_ENABLED)
#error Invalid configuration MCOS_MKMSG_ASYNC_MULTI_IS_ENABLED
#endif /* #if (MCOS_MKMSG_ASYNC_MULTI_IS_ENABLED && !MCOS_MKMSG_ASYNC_IS_ENABLED) */

#define MKMSG_OK                1U
#define MKMSG_NG                0U

#define RINGBUF_DECREMENT_1     1U

/*
 *   packet header utility
 */
#define MKMSG_PACKETHEADER_AUTHO_SHIFT                  (((uint32_t)(((uint32_t)sizeof(mcos_ringbuf_vunit_t)) << 3U)) - 1U)
#define MKMSG_PACKETHEADER_AUTHO_USER                   ((mcos_ringbuf_vunit_t)(0UL << MKMSG_PACKETHEADER_AUTHO_SHIFT))
#define MKMSG_PACKETHEADER_AUTHO_SYSTEM                 ((mcos_ringbuf_vunit_t)(1UL << MKMSG_PACKETHEADER_AUTHO_SHIFT))
#define MKMSG_PACKETHEADER_AUTHO_MASK                   ((mcos_ringbuf_vunit_t)(1UL << MKMSG_PACKETHEADER_AUTHO_SHIFT))
#define MKMSG_PACKETHEADER_GET_MSGSIZE(packetheader)    ((packetheader) & ((mcos_ringbuf_vunit_t)(~MKMSG_PACKETHEADER_AUTHO_MASK)))
#define MKMSG_PACKETHEADER_GET_AUTHO(packetheader)      ((packetheader) & MKMSG_PACKETHEADER_AUTHO_MASK)

/*
 *   ring buffer threshold
 */
#define MKMSG_ASYNC_SYSTEM_MSG_SIZE_MAX ((uint32_t)MCOS_CFG_SYSTEM_MSG_COUNT_MAX * (uint32_t)MCOS_RINGBUF_VREQUEST_MAX_SIZE)
#define MKMSG_ASYNC_USER_MSG_SIZE_MAX   ((mcos_ringbuf_uint_t)MCOS_MKMSG_ASYNC_BUF_SIZE - (mcos_ringbuf_uint_t)MKMSG_ASYNC_SYSTEM_MSG_SIZE_MAX)

/*
 *   check if user message or not
 */
#define MKMSG_IS_USERMSG(msg_header)    ((((const msg_id_t *)(msg_header))->id.type & MSG_AUTHO_MASK) == MSG_AUTHO_USER)

/*
 * architecture dependent (user implementation)
 */

#if (MCOS_MKMSG_SYNC_IS_ENABLED || MCOS_MKMSG_ASYNC_IS_ENABLED)

MCOS_INLINE mkmsg_buf_t * mcos_mkmsg_if_buf_get_by_lcid(
    const mkcb_t * const mkcb,
    const mcos_id_t dest_lcid);
MCOS_INLINE mkmsg_buf_t * mcos_mkmsg_if_buf_get_current(
    const mkcb_t * const mkcb);
MCOS_INLINE void mcos_mkmsg_if_memory_copy(
    volatile void * const dst,
    const void * const src,
    const mcos_ringbuf_uint_t size);
MCOS_INLINE void mcos_mkmsg_if_memory_copy_aligned(
    volatile void * const dst,
    volatile const void * const src,
    const mcos_ringbuf_uint_t size);
MCOS_INLINE void mcos_mkmsg_if_interrupt_send(
    const mcos_id_t dest_lcid);
MCOS_INLINE void mcos_mkmsg_if_spinlock_get(
    mcos_ringbuf_t * const ringbuf);
MCOS_INLINE void mcos_mkmsg_if_spinlock_release(
    mcos_ringbuf_t * const ringbuf);

#endif /* #if (MCOS_MKMSG_SYNC_IS_ENABLED || MCOS_MKMSG_ASYNC_IS_ENABLED) */


#if MCOS_MKMSG_SYNC_IS_ENABLED

MCOS_INLINE void mcos_mkmsg_if_memory_barrier(
    void);
MCOS_INLINE mcos_ringbuf_t * mcos_mkmsg_if_sync_get_head(
    mkmsg_buf_t * const mkmsg);
MCOS_INLINE volatile mcos_ringbuf_funit_t * mcos_mkmsg_if_sync_get_data(
    const mkmsg_buf_t * const mkmsg);
MCOS_INLINE mkmsg_replycb_t * mcos_mkmsg_if_sync_get_replycb(
    mkmsg_buf_t * const mkmsg);
MCOS_INLINE volatile mcos_ringbuf_uint_t * mcos_mkmsg_if_sync_get_replycb_state_addr(
    mkmsg_buf_t * const mkmsg);

#endif /* #if MCOS_MKMSG_SYNC_IS_ENABLED */


#if MCOS_MKMSG_ASYNC_IS_ENABLED

MCOS_INLINE mcos_ringbuf_t * mcos_mkmsg_if_async_get_head(
    mkmsg_buf_t * const mkmsg);
MCOS_INLINE volatile mcos_ringbuf_uint8_t * mcos_mkmsg_if_async_get_data(
    const mkmsg_buf_t * const mkmsg);

#endif /* #if MCOS_MKMSG_ASYNC_IS_ENABLED */



/*
 * internal funcitons
 */

#if (MCOS_MKMSG_SYNC_IS_ENABLED || MCOS_MKMSG_ASYNC_IS_ENABLED)

MCOS_INLINE mcos_ringbuf_uint_t mcos_mkmsg_util_ringbuf_decrement_internal(
    mcos_ringbuf_t * const ringbuf,
    const mcos_ringbuf_uint_t read,
    const mcos_ringbuf_uint_t dec,
    mcos_ringbuf_vunit_t authority);

/*
 * Decrement ring buffer size
 *  Return  : ring buffer new size (items/bytes)
 *  Note    : no dependent
 */
MCOS_INLINE mcos_ringbuf_uint_t
mcos_mkmsg_util_ringbuf_decrement_internal(
    /* ring buffer control block */
    mcos_ringbuf_t * const ringbuf,
    /* new read */
    const mcos_ringbuf_uint_t read,
    /* decrement size */
    const mcos_ringbuf_uint_t dec,
    /* user message or not */
    mcos_ringbuf_vunit_t authority)
{
    mcos_ringbuf_uint_t size;

    mcos_mkmsg_if_spinlock_get(ringbuf);
    {
        size = (mcos_ringbuf_uint_t)ringbuf->size - dec;
        ringbuf->read = (mcos_ringbuf_index_t)read;
        ringbuf->size = (mcos_ringbuf_index_t)size;
        if (authority == MKMSG_PACKETHEADER_AUTHO_USER)
        {
            mcos_ringbuf_uint_t size_usermsg;
            size_usermsg = (mcos_ringbuf_uint_t)ringbuf->size_usermsg - dec;
            ringbuf->size_usermsg = (mcos_ringbuf_index_t)size_usermsg;
        }
    }
    mcos_mkmsg_if_spinlock_release(ringbuf);

    return size;
}

#endif /* #if (MCOS_MKMSG_SYNC_IS_ENABLED || MCOS_MKMSG_ASYNC_IS_ENABLED) */


#if MCOS_MKMSG_SYNC_IS_ENABLED

MCOS_INLINE uint32_t mcos_mkmsg_util_sync_reply_receive_internal(
    mkmsg_replycb_t * const replycb,
    void * const reply);
MCOS_INLINE mcos_ringbuf_uint_t mcos_mkmsg_util_sync_request_receive_internal(
    const mkcb_t * const mkcb,
    volatile const mcos_ringbuf_funit_t * const bufdata,
    const mcos_ringbuf_uint_t bufsize,
    const mcos_ringbuf_uint_t read);
MCOS_INLINE void mcos_mkmsg_util_sync_request_send_internal(
    volatile mcos_ringbuf_funit_t * const pdata,
    const void * const request,
    void * const reply,
    mkmsg_replycb_t * const replycb);

/*
 * Receive sync reply.
 *  Return  : success(=!0) or no message(=0)
 *  Note    : memory shared type dependent
 */
MCOS_INLINE uint32_t
mcos_mkmsg_util_sync_reply_receive_internal(
    /* local reply control block */
    mkmsg_replycb_t * const replycb,
    /* reply data buffer */
    void * const reply)
{
    /* return value */
    mcos_ringbuf_uint_t ret;

    ret = replycb->reply_state;
    if (ret != MKMSG_NG)
    {
#if IS_DS_SYSLOG_MKMSG
        mcos_log_hwl("mkmsg sync recv reply (received) in\n");
#endif /* IS_DS_SYSLOG_MKMSG */

#if MCOS_MKMSG_MATYPE == MCOS_MKMSG_MATYPE_NUMA
        mcos_mkmsg_if_memory_copy(reply, replycb->reply_data, MCOS_MKMSG_SYNC_REPLY_SIZE);
#else /* #if MCOS_MKMSG_MATYPE == MCOS_MKMSG_MATYPE_NUMA */
        (void)reply;
#endif /* #if MCOS_MKMSG_MATYPE == MCOS_MKMSG_MATYPE_NUMA */
        replycb->reply_state = MKMSG_NG;

#if IS_DS_SYSLOG_MKMSG
        mcos_log_hwl("mkmsg sync recv reply (received) out\n");
#endif /* IS_DS_SYSLOG_MKMSG */
    }
    else
    {
        /* do nothing */
    }
    return (uint32_t)ret;
}

/*
 * Receive sync request.
 *  Return  : new read index (items)
 *  Note    : memory shared type dependent
 */
MCOS_INLINE mcos_ringbuf_uint_t
mcos_mkmsg_util_sync_request_receive_internal(
    /* local mkcb */
    const mkcb_t * const mkcb,
    /* ring buffer data area */
    volatile const mcos_ringbuf_funit_t * const bufdata,
    /* ring buffer size (items) */
    const mcos_ringbuf_uint_t bufsize,
    /* ring buffer read index (items) */
    const mcos_ringbuf_uint_t read)
{
    /* received packet */
    volatile const mcos_ringbuf_funit_t *pdata;
    /* ring buffer read index after request consumed (items) */
    mcos_ringbuf_uint_t new_read;
#if MCOS_MKMSG_MATYPE == MCOS_MKMSG_MATYPE_UMA
    void *pdata_reply;
#endif
    /* callback */
    pdata = &bufdata[read];
#if MCOS_MKMSG_MATYPE == MCOS_MKMSG_MATYPE_UMA
    pdata_reply = pdata->reply;
    ar_mkmsg_callback(mkcb, pdata->request, pdata_reply);
#elif MCOS_MKMSG_MATYPE == MCOS_MKMSG_MATYPE_NUMA
    {
        /* temporary received request message buffer */
        mcos_ringbuf_vunit_t request[MCOS_MKMSG_SYNC_REQUEST_SIZE / sizeof(mcos_ringbuf_vunit_t)];
        /* temporary reply message buffer */
        mcos_ringbuf_vunit_t reply[MCOS_MKMSG_SYNC_REPLY_SIZE / sizeof(mcos_ringbuf_vunit_t)];

        mcos_mkmsg_if_memory_copy(request, pdata->request, MCOS_MKMSG_SYNC_REQUEST_SIZE);
        ar_mkmsg_callback(mkcb, request, reply);
        mcos_mkmsg_if_memory_copy(pdata->replycb->reply_data, reply, MCOS_MKMSG_SYNC_REPLY_SIZE);
    }
#endif /* #if MCOS_MKMSG_MATYPE == MCOS_MKMSG_MATYPE_NUMA */

    /* wait to write reply data */
    mcos_mkmsg_if_memory_barrier();

    /* notify sender */
    pdata->replycb->reply_state = MKMSG_OK;

    /* update read index */
    new_read = read;
    new_read++;
    if (new_read == bufsize)
    {
        new_read = 0U;
    }
    else
    {
        /* do nothing */
    }

    return new_read;
}

/*
 * Send sync request.
 *  Return  : none
 *  Note    : memory shared type dependent
 */
MCOS_INLINE void
mcos_mkmsg_util_sync_request_send_internal(
    /* packet write pointer */
    volatile mcos_ringbuf_funit_t * const pdata,
    /* request data */
    const void * const request,
    /* reply data buffer */
    void * const reply,
    /* local reply control block */
    mkmsg_replycb_t * const replycb)
{
#if MCOS_MKMSG_MATYPE == MCOS_MKMSG_MATYPE_UMA
    pdata->request = request;
    pdata->reply = reply;
    pdata->replycb = replycb;
#elif MCOS_MKMSG_MATYPE == MCOS_MKMSG_MATYPE_NUMA /* #if MCOS_MKMSG_MATYPE == MCOS_MKMSG_MATYPE_UMA */
    mcos_mkmsg_if_memory_copy(pdata->request, request, MCOS_MKMSG_SYNC_REQUEST_SIZE);
    pdata->replycb = replycb;
#endif /* #if MCOS_MKMSG_MATYPE == MCOS_MKMSG_MATYPE_UMA */
}

#endif /* #if MCOS_MKMSG_SYNC_IS_ENABLED */


#if MCOS_MKMSG_ASYNC_IS_ENABLED

MCOS_INLINE mcos_ringbuf_uint_t mcos_mkmsg_util_async_request_receive_internal(
    const mkcb_t * const mkcb,
    volatile const uint8_t * const bufdata,
    const mcos_ringbuf_uint_t bufsize,
    const mcos_ringbuf_uint_t read,
    const mcos_ringbuf_uint_t msgsz);

/*
 * Receive async request.
 *  Return  : new read index (bytes)
 *  Note    : memory shared type dependent
 */
MCOS_INLINE mcos_ringbuf_uint_t
mcos_mkmsg_util_async_request_receive_internal(
    /* local mkcb */
    const mkcb_t * const mkcb,
    /* ring buffer data area */
    volatile const uint8_t * const bufdata,
    /* ring buffer size (bytes) */
    const mcos_ringbuf_uint_t bufsize,
    /* ring buffer read index, top of request data, no lap around (bytes) */
    const mcos_ringbuf_uint_t read,
    /* request message size in ring buffer (bytes) */
    const mcos_ringbuf_uint_t msgsz)
{
    /* ring buffer read index after request consumed (bytes) */
    mcos_ringbuf_uint_t new_read;

    new_read = read + msgsz;

#if MCOS_MKMSG_MATYPE == MCOS_MKMSG_MATYPE_UMA
    {
        if (new_read < bufsize)
        {
            /* no lap around and not reached to buffer end */
            mcos_cls_mkmsg_callback(mkcb, &bufdata[read], (uint32_t)msgsz);
        }
        else if (new_read == bufsize)
        {
            /* no lap around and reached to buffer end */
            mcos_cls_mkmsg_callback(mkcb, &bufdata[read], (uint32_t)msgsz);
            new_read = 0U;
        }
        else if (read == bufsize)
        {
            /* lap around header only */
            mcos_cls_mkmsg_callback(mkcb, bufdata, (uint32_t)msgsz);
            new_read = msgsz;
        }
        else
        {
            /* lap around */

            /* message size before lap around (bytes) */
            mcos_ringbuf_uint_t half1;
            /* message size after lap around (bytes) */
            mcos_ringbuf_uint_t half2;
            /* temporary received message buffer */
            volatile mcos_ringbuf_uint8_t request[MCOS_RINGBUF_VREQUEST_MAX_SIZE];

            half1 = bufsize - read;
            half2 = msgsz - half1;
            mcos_mkmsg_if_memory_copy_aligned(request, &bufdata[read], half1);
            mcos_mkmsg_if_memory_copy_aligned(&request[half1], bufdata, half2);
            mcos_cls_mkmsg_callback(mkcb, request, (uint32_t)msgsz);
            new_read = half2;
        }
    }
#elif MCOS_MKMSG_MATYPE == MCOS_MKMSG_MATYPE_NUMA /* #if MCOS_MKMSG_MATYPE == MCOS_MKMSG_MATYPE_UMA */
    {
        /* temporary received message buffer */
        volatile mcos_ringbuf_vunit_t request[MCOS_RINGBUF_VREQUEST_MAX_SIZE / sizeof(mcos_ringbuf_vunit_t)];

        if (new_read < bufsize)
        {
            /* no lap around and not reached to buffer end */
            mcos_mkmsg_if_memory_copy_aligned(request, &bufdata[read], msgsz);
        }
        else if (new_read == bufsize)
        {
            /* no lap around and reached to buffer end */
            mcos_mkmsg_if_memory_copy_aligned(request, &bufdata[read], msgsz);
            new_read = 0U;
        }
        else if (read == bufsize)
        {
            /* lap around header only */
            mcos_mkmsg_if_memory_copy_aligned(request, bufdata, msgsz);
            new_read = msgsz;
        }
        else
        {
            /* lap around */

            /* message size before lap around (bytes) */
            mcos_ringbuf_uint_t half1;
            /* message size after lap around (bytes) */
            mcos_ringbuf_uint_t half2;

            half1 = bufsize - read;
            half2 = msgsz - half1;
            mcos_mkmsg_if_memory_copy_aligned(request, &bufdata[read], half1);
            mcos_mkmsg_if_memory_copy_aligned(&((uint8_t *)request)[half1], bufdata, half2);
            new_read = half2;
        }
        mcos_cls_mkmsg_callback(mkcb, request, (uint32_t)msgsz);
    }
#endif /* #if MCOS_MKMSG_MATYPE == MCOS_MKMSG_MATYPE_UMA */

    return new_read;
}

#endif /* #if MCOS_MKMSG_ASYNC_IS_ENABLED */



/*
 * external utility
 */

#if MCOS_MKMSG_SYNC_IS_ENABLED

MCOS_INLINE uint32_t mcos_mkmsg_util_req_send(
    const mkcb_t * const mkcb,
    const mcos_id_t dest_lcid,
    const void * const request,
    void * const reply);
MCOS_INLINE uint32_t mcos_mkmsg_util_reply_receive(
    const mkcb_t * const mkcb,
    void * const reply);
MCOS_INLINE uint32_t mcos_mkmsg_util_req_reply_receive(
    const mkcb_t * const mkcb,
    void * const reply);

/*
 * Send sync request.
 *  Return  : success(=!0) or fail(=0)
 *  Note    : no dependent
 */
MCOS_INLINE uint32_t
mcos_mkmsg_util_req_send(
    /* local mkcb */
    const mkcb_t * const mkcb,
    /* destination lcid */
    const mcos_id_t dest_lcid,
    /* request data */
    const void * const request,
    /* reply data buffer */
    void * const reply)
{
    /* local mkmsg */
    mkmsg_buf_t *mkmsg;
    /* destination mkmsg */
    mkmsg_buf_t *dest_mkmsg;
    /* destination ring buffer */
    mcos_ringbuf_t *ringbuf;
    /* destination ring buffer size (items) */
    mcos_ringbuf_uint_t bufsize;
    /* local reply control block */
    mkmsg_replycb_t *replycb;

#if IS_DS_SYSLOG_MKMSG
    mcos_log_hwl("mkmsg sync send request in  %d\n", (uint32_t)dest_lcid);
#endif /* IS_DS_SYSLOG_MKMSG */

    mkmsg = mcos_mkmsg_if_buf_get_current(mkcb);
    dest_mkmsg = mcos_mkmsg_if_buf_get_by_lcid(mkcb, dest_lcid);
    ringbuf = mcos_mkmsg_if_sync_get_head(dest_mkmsg);
    bufsize = (mcos_ringbuf_uint_t)MCOS_MKMSG_SYNC_BUF_SIZE;
    replycb = mcos_mkmsg_if_sync_get_replycb(mkmsg);

    mcos_mkmsg_if_spinlock_get(ringbuf);
    {
        /* ring buffer read index (items) */
        mcos_ringbuf_uint_t read;
        /* ring buffer written size (items) */
        mcos_ringbuf_uint_t size;
        /* ring buffer write index (items) */
        mcos_ringbuf_uint_t write;
        /* packet write pointer */
        volatile mcos_ringbuf_funit_t *pdata;
        mcos_ringbuf_index_t tmp_size;

        /* notify receiver and increment ring buffer written size */
        size = (mcos_ringbuf_uint_t)ringbuf->size;
        if (size == 0U)
        {
            mcos_mkmsg_if_interrupt_send(dest_lcid);
        }
        else
        {
            /* do nothing */
        }
        tmp_size = (mcos_ringbuf_index_t)size;
        tmp_size++;
        ringbuf->size = tmp_size;

        /* get push address */
        read = (mcos_ringbuf_uint_t)ringbuf->read;
        write = read + size;
        if (write >= bufsize)
        {
            write -= bufsize;
        }
        else
        {
            /* do nothing */
        }
        pdata = (volatile mcos_ringbuf_funit_t *)&mcos_mkmsg_if_sync_get_data(dest_mkmsg)[write];

        /* push packet */
        mcos_mkmsg_util_sync_request_send_internal(pdata, request, reply, replycb);
    }
    mcos_mkmsg_if_spinlock_release(ringbuf);

#if IS_DS_SYSLOG_MKMSG
    mcos_log_hwl("mkmsg sync send request out %d\n", (uint32_t)dest_lcid);
#endif /* IS_DS_SYSLOG_MKMSG */

    return MKMSG_OK;
}

/*
 * Receive sync reply.
 *  Return  : success(=!0) or no message(=0)
 *  Note    : no dependent
 */
MCOS_INLINE uint32_t
mcos_mkmsg_util_reply_receive(
    /* local mkcb */
    const mkcb_t * const mkcb,
    /* reply data buffer */
    void * const reply)
{
    /* local mkmsg */
    mkmsg_buf_t *mkmsg;
    /* return value */
    mcos_ringbuf_uint_t ret;

    mkmsg = mcos_mkmsg_if_buf_get_current(mkcb);
    ret = mcos_mkmsg_util_sync_reply_receive_internal(
            mcos_mkmsg_if_sync_get_replycb(mkmsg), reply);

    return (uint32_t)ret;
}

/*
 * Receive sync reply and receive requests.
 *  Return  : success(=!0) or no message(=0)
 *  Note    : no dependent
 */
MCOS_INLINE uint32_t
mcos_mkmsg_util_req_reply_receive(
    /* local mkcb */
    const mkcb_t * const mkcb,
    /* reply data buffer */
    void * const reply)
{
    /* local mkmsg */
    mkmsg_buf_t *mkmsg;
    /* return value */
    mcos_ringbuf_uint_t ret;
    volatile mcos_ringbuf_uint_t const *p_reply_state;

    mkmsg = mcos_mkmsg_if_buf_get_current(mkcb);
    p_reply_state = mcos_mkmsg_if_sync_get_replycb_state_addr(mkmsg);

    /* receive sync request */
    {
        /* sync request ring buffer */
        mcos_ringbuf_t *ringbuf;
        /* ring buffer read index (items) */
        mcos_ringbuf_uint_t read;
        /* ring buffer written size (items) */
        mcos_ringbuf_uint_t size;
        /* ring buffer size (items) */
        mcos_ringbuf_uint_t bufsize;

        ringbuf = mcos_mkmsg_if_sync_get_head(mkmsg);
        bufsize = (mcos_ringbuf_uint_t)MCOS_MKMSG_SYNC_BUF_SIZE;
        mcos_mkmsg_if_spinlock_get(ringbuf);
        {
            read = (mcos_ringbuf_uint_t)ringbuf->read;
            size = (mcos_ringbuf_uint_t)ringbuf->size;
        }
        mcos_mkmsg_if_spinlock_release(ringbuf);

        while ((size > 0U) && (*p_reply_state == MKMSG_NG))
        {
#if IS_DS_SYSLOG_MKMSG
            mcos_log_hwl("mkmsg sync recv request (received) in\n");
#endif /* IS_DS_SYSLOG_MKMSG */

            read = mcos_mkmsg_util_sync_request_receive_internal(mkcb,
                        (volatile mcos_ringbuf_funit_t *)mcos_mkmsg_if_sync_get_data(mkmsg),
                        bufsize, read);
            size = mcos_mkmsg_util_ringbuf_decrement_internal(ringbuf, read, RINGBUF_DECREMENT_1, (mcos_ringbuf_vunit_t)mcos_false);

#if IS_DS_SYSLOG_MKMSG
            mcos_log_hwl("mkmsg sync recv request (received) out\n");
#endif /* IS_DS_SYSLOG_MKMSG */
        }
    }

    /* receive async request */
#if MCOS_MKMSG_ASYNC_IS_ENABLED
    {
        /* async request ring buffer */
        mcos_ringbuf_t *ringbuf;
        /* ring buffer read index (bytes) */
        mcos_ringbuf_uint_t read;
        /* ring buffer written size (bytes) */
        mcos_ringbuf_uint_t size;
        /* ring buffer size (bytes) */
        mcos_ringbuf_uint_t bufsize;
        /* ring buffer data area */
        volatile uint8_t const *bufdata;

        
        ringbuf = mcos_mkmsg_if_async_get_head(mkmsg);
        bufdata = (volatile uint8_t const *)mcos_mkmsg_if_async_get_data(mkmsg);
        bufsize = (mcos_ringbuf_uint_t)MCOS_MKMSG_ASYNC_BUF_SIZE;
        mcos_mkmsg_if_spinlock_get(ringbuf);
        {
            read = (mcos_ringbuf_uint_t)ringbuf->read;
            size = (mcos_ringbuf_uint_t)ringbuf->size;
        }
        mcos_mkmsg_if_spinlock_release(ringbuf);

        while ((size > 0U) && (*p_reply_state == MKMSG_NG))
        {
            /* packet data size (no header) (bytes) */
            mcos_ringbuf_uint_t msgsz;
            mcos_ringbuf_uint_t rcvsz;
            mcos_ringbuf_vunit_t packetheader;
            mcos_ringbuf_vunit_t authority;

#if IS_DS_SYSLOG_MKMSG
            mcos_log_hwl("mkmsg async recv in\n");
#endif /* IS_DS_SYSLOG_MKMSG */

#if defined __BIG_ENDIAN__
            packetheader = (uint32_t)( (uint32_t)bufdata[read + 3U] |
                                      ((uint32_t)bufdata[read + 2U] <<  8U) |
                                      ((uint32_t)bufdata[read + 1U] << 16U) |
                                      ((uint32_t)bufdata[read]      << 24U) );
#else
            packetheader = (uint32_t)( ((uint32_t)bufdata[read + 3U] << 24U) |
                                       ((uint32_t)bufdata[read + 2U] << 16U) |
                                       ((uint32_t)bufdata[read + 1U] <<  8U) |
                                        (uint32_t)bufdata[read] );
#endif

            msgsz = MKMSG_PACKETHEADER_GET_MSGSIZE(packetheader);
            authority = MKMSG_PACKETHEADER_GET_AUTHO(packetheader);

            rcvsz = msgsz + (mcos_ringbuf_uint_t)sizeof(mcos_ringbuf_vunit_t);
            read = mcos_mkmsg_util_async_request_receive_internal(mkcb, bufdata, bufsize,
                        read + (mcos_ringbuf_uint_t)sizeof(mcos_ringbuf_vunit_t), msgsz);
            size = mcos_mkmsg_util_ringbuf_decrement_internal(ringbuf, read, rcvsz, authority);

#if IS_DS_SYSLOG_MKMSG
            mcos_log_hwl("mkmsg async recv out\n");
#endif /* IS_DS_SYSLOG_MKMSG */
        }
    }
#endif /* #if MCOS_MKMSG_ASYNC_IS_ENABLED */

    /* receive reply */
    ret = mcos_mkmsg_util_sync_reply_receive_internal(
            mcos_mkmsg_if_sync_get_replycb(mkmsg), reply);

    return (uint32_t)ret;
}
#endif /* #if MCOS_MKMSG_SYNC_IS_ENABLED */

#if MCOS_MKMSG_SYNC_IS_ENABLED || MCOS_MKMSG_ASYNC_IS_ENABLED

MCOS_INLINE void mcos_mkmsg_util_req_receive(
    const mkcb_t * const mkcb);

/*
 * Receive requests.
 *  Return  : none
 *  Note    : no dependent
 */
MCOS_INLINE void
mcos_mkmsg_util_req_receive(
    /* local mkcb */
    const mkcb_t * const mkcb)
{
    /* local mkmsg */
    mkmsg_buf_t *mkmsg;

    mkmsg = mcos_mkmsg_if_buf_get_current(mkcb);

#if MCOS_MKMSG_SYNC_IS_ENABLED
    {
        /* sync request ring buffer */
        mcos_ringbuf_t *ringbuf;
        /* ring buffer read index (items) */
        mcos_ringbuf_uint_t read;
        /* ring buffer written size (items) */
        mcos_ringbuf_uint_t size;
        /* ring buffer size (items) */
        mcos_ringbuf_uint_t bufsize;

        ringbuf = mcos_mkmsg_if_sync_get_head(mkmsg);
        bufsize = (mcos_ringbuf_uint_t)MCOS_MKMSG_SYNC_BUF_SIZE;
        mcos_mkmsg_if_spinlock_get(ringbuf);
        {
            read = (mcos_ringbuf_uint_t)ringbuf->read;
            size = (mcos_ringbuf_uint_t)ringbuf->size;
        }
        mcos_mkmsg_if_spinlock_release(ringbuf);

        while (size > 0U)
        {
#if IS_DS_SYSLOG_MKMSG
            mcos_log_hwl("mkmsg sync recv request in\n");
#endif /* IS_DS_SYSLOG_MKMSG */

            read = mcos_mkmsg_util_sync_request_receive_internal(mkcb,
                        (volatile mcos_ringbuf_funit_t *)mcos_mkmsg_if_sync_get_data(mkmsg),
                        bufsize, read);
            size = mcos_mkmsg_util_ringbuf_decrement_internal(ringbuf, read, RINGBUF_DECREMENT_1, (mcos_ringbuf_vunit_t)mcos_false);

#if IS_DS_SYSLOG_MKMSG
            mcos_log_hwl("mkmsg sync recv request out\n");
#endif /* IS_DS_SYSLOG_MKMSG */
        }
    }
#endif /* #if MCOS_MKMSG_SYNC_IS_ENABLED */

#if MCOS_MKMSG_ASYNC_IS_ENABLED
    {
        /* async request ring buffer */
        mcos_ringbuf_t *ringbuf;
        /* ring buffer read index (bytes) */
        mcos_ringbuf_uint_t read;
        /* ring buffer written size (bytes) */
        mcos_ringbuf_uint_t size;
        /* ring buffer size (bytes) */
        mcos_ringbuf_uint_t bufsize;
        /* ring buffer data area */
        volatile uint8_t const *bufdata;

        ringbuf = mcos_mkmsg_if_async_get_head(mkmsg);
        bufdata = (volatile uint8_t const *)mcos_mkmsg_if_async_get_data(mkmsg);
        bufsize = (mcos_ringbuf_uint_t)MCOS_MKMSG_ASYNC_BUF_SIZE;
        mcos_mkmsg_if_spinlock_get(ringbuf);
        {
            read = (mcos_ringbuf_uint_t)ringbuf->read;
            size = (mcos_ringbuf_uint_t)ringbuf->size;
        }
        mcos_mkmsg_if_spinlock_release(ringbuf);

        while (size > 0U)
        {
            /* packet data size (no header) (bytes) */
            mcos_ringbuf_uint_t msgsz;
            mcos_ringbuf_uint_t rcvsz;
            mcos_ringbuf_vunit_t packetheader;
            mcos_ringbuf_vunit_t authority;

#if IS_DS_SYSLOG_MKMSG
            mcos_log_hwl("mkmsg async recv in\n");
#endif /* IS_DS_SYSLOG_MKMSG */

#if defined __BIG_ENDIAN__
            packetheader = (uint32_t)( (uint32_t)bufdata[read + 3U] |
                                      ((uint32_t)bufdata[read + 2U] <<  8U) |
                                      ((uint32_t)bufdata[read + 1U] << 16U) |
                                      ((uint32_t)bufdata[read]      << 24U) );
#else
            packetheader = (uint32_t)( ((uint32_t)bufdata[read + 3U] << 24U) |
                                       ((uint32_t)bufdata[read + 2U] << 16U) |
                                       ((uint32_t)bufdata[read + 1U] <<  8U) |
                                       (uint32_t)bufdata[read] );
#endif
            msgsz = MKMSG_PACKETHEADER_GET_MSGSIZE(packetheader);
            authority = MKMSG_PACKETHEADER_GET_AUTHO(packetheader);

            rcvsz = msgsz + (mcos_ringbuf_uint_t)sizeof(mcos_ringbuf_vunit_t);
            read = mcos_mkmsg_util_async_request_receive_internal(mkcb, bufdata, bufsize,
                        read + (mcos_ringbuf_uint_t)sizeof(mcos_ringbuf_vunit_t), msgsz);
            size = mcos_mkmsg_util_ringbuf_decrement_internal(ringbuf, read, rcvsz, authority);

#if IS_DS_SYSLOG_MKMSG
            mcos_log_hwl("mkmsg async recv out\n");
#endif /* IS_DS_SYSLOG_MKMSG */
        }
    }
#endif /* #if MCOS_MKMSG_ASYNC_IS_ENABLED */
}
#endif /* #if MCOS_MKMSG_SYNC_IS_ENABLED || MCOS_MKMSG_ASYNC_IS_ENABLED */

#if MCOS_MKMSG_ASYNC_IS_ENABLED

MCOS_INLINE uint32_t mcos_mkmsg_util_req_send_async(
    const mkcb_t * const mkcb,
    const mcos_id_t dest_lcid,
    const void * const request,
    const uint32_t request_size);

/*
 * Send async request.
 *  Return  : success(=!0) or fail(=0)
 *  Note    : no dependent
 */
MCOS_INLINE uint32_t
mcos_mkmsg_util_req_send_async(
    /* local mkcb */
    const mkcb_t * const mkcb,
    /* destination lcid */
    const mcos_id_t dest_lcid,
    /* request data */
    const void * const request,
    /* request size (bytes) */
    const uint32_t request_size)
{
    /* destination mkmsg */
    mkmsg_buf_t *dest_mkmsg;
    /* destination ring buffer */
    mcos_ringbuf_t *ringbuf;
    /* round up request size (bytes) */
    mcos_ringbuf_uint_t msgsz;
    /* push size to ring buffer (packet data + header) (bytes) */
    mcos_ringbuf_uint_t pushsz;
    /* ring buffer size (bytes) */
    mcos_ringbuf_uint_t bufsize;
    /* ring buffer data area */
    volatile uint8_t *bufdata;
    /* return value */
    uint32_t ret;

#if IS_DS_SYSLOG_MKMSG
    mcos_log_hwl("mkmsg async send in  %d\n", dest_lcid);
#endif /* IS_DS_SYSLOG_MKMSG */

    dest_mkmsg = mcos_mkmsg_if_buf_get_by_lcid(mkcb, dest_lcid);
    ringbuf = mcos_mkmsg_if_async_get_head(dest_mkmsg);
    bufdata = (volatile uint8_t *)mcos_mkmsg_if_async_get_data(dest_mkmsg);
    bufsize = (mcos_ringbuf_uint_t)MCOS_MKMSG_ASYNC_BUF_SIZE;
    ret = MKMSG_OK;

    msgsz = (mcos_ringbuf_uint_t)MCOS_RINGBUF_ROUNDUP(request_size);
    pushsz = msgsz + (mcos_ringbuf_uint_t)sizeof(mcos_ringbuf_vunit_t);

    /* push packet */
    mcos_mkmsg_if_spinlock_get(ringbuf);
    {
        /* ring buffer written size (bytes) */
        mcos_ringbuf_uint_t size;
        /* ring buffer new written size after push message (bytes) */
        mcos_ringbuf_uint_t new_size;
        /* ring buffer new written size of user message after push message (bytes) */
        mcos_ringbuf_uint_t new_size_usermsg = 0U;
        /* user message or not. */
        mcos_ringbuf_vunit_t authority;

        authority = MKMSG_IS_USERMSG(request) ? MKMSG_PACKETHEADER_AUTHO_USER : MKMSG_PACKETHEADER_AUTHO_SYSTEM;
        size = (mcos_ringbuf_uint_t)ringbuf->size;
        new_size = size + pushsz;
        if (authority == MKMSG_PACKETHEADER_AUTHO_USER)
        {
            new_size_usermsg = ringbuf->size_usermsg + pushsz;
        }
        if (((authority == MKMSG_PACKETHEADER_AUTHO_USER) && (new_size_usermsg > MKMSG_ASYNC_USER_MSG_SIZE_MAX))
            || (new_size > bufsize))
        {
            /* buffer full */
            ret = MKMSG_NG;
        }
        else
        {
            /* enough buffer */

            /* ring buffer write index (bytes) */
            mcos_ringbuf_uint_t write;

            /* notify target core */
            if (size == 0U)
            {
                mcos_mkmsg_if_interrupt_send(dest_lcid);
            }
            else
            {
                /* do nothing */
            }

            /* get write pointer */
            write = (mcos_ringbuf_uint_t)ringbuf->read + size;
            if (write >= bufsize)
            {
                /* written data is lap arounded */
                write -= bufsize;
            }
            else
            {
                /* do nothing */
            }

            /* update ring buffer state */
            ringbuf->size = (mcos_ringbuf_index_t)new_size;

            /* if written message is user message, it update ring buffer used size of user message. */
            if (authority == MKMSG_PACKETHEADER_AUTHO_USER)
            {
                ringbuf->size_usermsg = (mcos_ringbuf_index_t)new_size_usermsg;
            }

            /* push message size */
#if defined __BIG_ENDIAN__
            bufdata[write]      = (uint8_t)(((msgsz | authority) & 0xFF000000U) >> 24U);
            bufdata[write + 1U] = (uint8_t)(((msgsz | authority) & 0x00FF0000U) >> 16U);
            bufdata[write + 2U] = (uint8_t)(((msgsz | authority) & 0x0000FF00U) >>  8U);
            bufdata[write + 3U] = (uint8_t) ((msgsz | authority) & 0x000000FFU);
#else
            bufdata[write]      = (uint8_t) ((msgsz | authority) & 0x000000FFU);
            bufdata[write + 1U] = (uint8_t)(((msgsz | authority) & 0x0000FF00U) >>  8U);
            bufdata[write + 2U] = (uint8_t)(((msgsz | authority) & 0x00FF0000U) >> 16U);
            bufdata[write + 3U] = (uint8_t)(((msgsz | authority) & 0xFF000000U) >> 24U);
#endif

            write += (mcos_ringbuf_uint_t)sizeof(mcos_ringbuf_vunit_t);

            /* push message */
            if ((write + msgsz) <= bufsize)
            {
                /* no lap around */
                mcos_mkmsg_if_memory_copy(&bufdata[write], request, request_size);
            }
            else if (write == bufsize)
            {
                /* lap around header only */
                mcos_mkmsg_if_memory_copy(bufdata, request, request_size);
            }
            else
            {
                /* lap around */

                /* message size before lap around (bytes) */
                mcos_ringbuf_uint_t half1;
                /* message size after lap around (bytes) */
                mcos_ringbuf_uint_t half2;

                half1 = bufsize - write;
                half2 = (mcos_ringbuf_uint_t)request_size - half1;
                mcos_mkmsg_if_memory_copy(&bufdata[write], request, half1);
                mcos_mkmsg_if_memory_copy(bufdata, &((const uint8_t *)request)[half1], half2);
            }
        }
    }
    mcos_mkmsg_if_spinlock_release(ringbuf);

#if IS_DS_SYSLOG_MKMSG
    mcos_log_hwl("mkmsg async send out %d %d\n", dest_lcid, ret);
#endif /* IS_DS_SYSLOG_MKMSG */

    return ret;
}
#endif /* #if MCOS_MKMSG_ASYNC_IS_ENABLED */

#if MCOS_MKMSG_ASYNC_MULTI_IS_ENABLED

MCOS_INLINE uint32_t mcos_mkmsg_util_req_send_async_multi(
    const mkcb_t * const mkcb,
    const mcos_id_t dest_lcid,
    const void * const * const requests,
    const uint32_t * const requests_sizes);

/*
 * Send async non-contiguous area request.
 *  Return  : success(=!0) or fail(=0)
 *  Note    : no dependent
 */
MCOS_INLINE uint32_t
mcos_mkmsg_util_req_send_async_multi(
    /* local mkcb */
    const mkcb_t * const mkcb,
    /* destination lcid */
    const mcos_id_t dest_lcid,
    /* request data fragments address list */
    const void * const * const requests,
    /* request data fragments size list */
    const uint32_t * const requests_sizes)
{
    /* destination mkmsg */
    mkmsg_buf_t *dest_mkmsg;
    /* destination ring buffer */
    mcos_ringbuf_t *ringbuf;
    /* round up total request size (bytes) */
    mcos_ringbuf_uint_t msgsz;
    /* total push size to ring buffer (packet data + header) (bytes) */
    mcos_ringbuf_uint_t pushsz;
    /* ring buffer size (bytes) */
    mcos_ringbuf_uint_t bufsize;
    /* ring buffer data area */
    volatile uint8_t *bufdata;
    /* return value */
    uint32_t ret;
    /* fragment size (no round up) (bytes) */
    uint32_t fragment_size;
    /* fragment size (round up) (bytes) */
    mcos_ringbuf_uint_t fragsz;
    /* request array elements */
    uint32_t    elm_size;
    uint32_t    elm_fgmt;

#if IS_DS_SYSLOG_MKMSG
    mcos_log_hwl("mkmsg async send multi in  %d\n", dest_lcid);
#endif /* IS_DS_SYSLOG_MKMSG */

    dest_mkmsg = mcos_mkmsg_if_buf_get_by_lcid(mkcb, dest_lcid);
    ringbuf = mcos_mkmsg_if_async_get_head(dest_mkmsg);
    bufdata = (volatile uint8_t *)mcos_mkmsg_if_async_get_data(dest_mkmsg);
    bufsize = (mcos_ringbuf_uint_t)MCOS_MKMSG_ASYNC_BUF_SIZE;
    ret = MKMSG_OK;

    /* get total packet size */
    msgsz = 0U;
    elm_size = 0U;
    fragment_size = requests_sizes[0];
    do
    {
        fragsz = (mcos_ringbuf_uint_t)MCOS_RINGBUF_ROUNDUP(fragment_size);
        msgsz += fragsz;
        elm_size++;
        fragment_size = requests_sizes[elm_size];
    } while (fragment_size != 0U);
    pushsz = msgsz + (mcos_ringbuf_uint_t)sizeof(mcos_ringbuf_vunit_t);

    /* 1st fragment settings */
    elm_fgmt = 0U;
    elm_size = 0U;
    fragment_size = requests_sizes[0];

    /* push packet */
    mcos_mkmsg_if_spinlock_get(ringbuf);
    {
        /* ring buffer written size (bytes) */
        mcos_ringbuf_uint_t size;
        /* ring buffer new written size after push message (bytes) */
        mcos_ringbuf_uint_t new_size;
        /* ring buffer new written size of user message after push message (bytes) */
        mcos_ringbuf_uint_t new_size_usermsg = 0U;
        /* user message or not. */
        mcos_ringbuf_vunit_t authority;

        size = (mcos_ringbuf_uint_t)ringbuf->size;
        new_size = size + pushsz;
        authority = MKMSG_IS_USERMSG(requests[elm_fgmt]) ? MKMSG_PACKETHEADER_AUTHO_USER : MKMSG_PACKETHEADER_AUTHO_SYSTEM;
        if (authority == MKMSG_PACKETHEADER_AUTHO_USER)
        {
            new_size_usermsg = ringbuf->size_usermsg + pushsz;
        }
        if (((authority == MKMSG_PACKETHEADER_AUTHO_USER) && (new_size_usermsg > MKMSG_ASYNC_USER_MSG_SIZE_MAX))
            || (new_size > bufsize))
        {
            /* buffer full */
            ret = MKMSG_NG;
        }
        else
        {
            /* enough buffer */

            /* ring buffer write index (bytes) */
            mcos_ringbuf_uint_t write;

            /* notify target core */
            if (size == 0U)
            {
                mcos_mkmsg_if_interrupt_send(dest_lcid);
            }
            else
            {
                /* do nothing */
            }

            /* get write pointer */
            write = (mcos_ringbuf_uint_t)ringbuf->read + size;
            if (write >= bufsize)
            {
                /* written data is lap arounded */
                write -= bufsize;
            }
            else
            {
                /* do nothing */
            }

            /* update ring buffer state */
            ringbuf->size = (mcos_ringbuf_index_t)new_size;

            /* if written message is user message, it update ring buffer used size of user message. */
            if (authority == MKMSG_PACKETHEADER_AUTHO_USER)
            {
                ringbuf->size_usermsg = (mcos_ringbuf_index_t)new_size_usermsg;
            }

            /* push message size */
#if defined __BIG_ENDIAN__
            bufdata[write]      = (uint8_t)(((msgsz | authority) & 0xFF000000U) >> 24U);
            bufdata[write + 1U] = (uint8_t)(((msgsz | authority) & 0x00FF0000U) >> 16U);
            bufdata[write + 2U] = (uint8_t)(((msgsz | authority) & 0x0000FF00U) >>  8U);
            bufdata[write + 3U] = (uint8_t) ((msgsz | authority) & 0x000000FFU);
#else
            bufdata[write]      = (uint8_t) ((msgsz | authority) & 0x000000FFU);
            bufdata[write + 1U] = (uint8_t)(((msgsz | authority) & 0x0000FF00U) >>  8U);
            bufdata[write + 2U] = (uint8_t)(((msgsz | authority) & 0x00FF0000U) >> 16U);
            bufdata[write + 3U] = (uint8_t)(((msgsz | authority) & 0xFF000000U) >> 24U);
#endif

            write += (mcos_ringbuf_uint_t)sizeof(mcos_ringbuf_vunit_t);

            /* push message */
            do
            {
                /* ring buffer new write index after push fragment (bytes) */
                mcos_ringbuf_uint_t new_write;

                fragsz = (mcos_ringbuf_uint_t)MCOS_RINGBUF_ROUNDUP(fragment_size);
                new_write = write + fragsz;

                if (new_write <= bufsize)
                {
                    /* no lap around */
                    mcos_mkmsg_if_memory_copy(&bufdata[write], requests[elm_fgmt], fragment_size);
                    write = new_write;
                }
                else if (write == bufsize)
                {
                    /* just lap around */
                    mcos_mkmsg_if_memory_copy(bufdata, requests[elm_fgmt], fragment_size);
                    write = fragsz;
                }
                else
                {
                    /* lap around */

                    /* fragment size before lap around (bytes) */
                    mcos_ringbuf_uint_t half1;
                    /* fragment size after lap around (bytes) */
                    mcos_ringbuf_uint_t half2;

                    half1 = bufsize - write;
                    half2 = (mcos_ringbuf_uint_t)fragment_size - half1;
                    mcos_mkmsg_if_memory_copy(&bufdata[write], requests[elm_fgmt], half1);
                    mcos_mkmsg_if_memory_copy(bufdata, &((const uint8_t *)requests[elm_fgmt])[half1], half2);
                    write = fragsz - half1;
                }
                elm_fgmt++;
                elm_size++;
                fragment_size = requests_sizes[elm_size];
            } while (fragment_size != 0U);
        }
    }
    mcos_mkmsg_if_spinlock_release(ringbuf);

#if IS_DS_SYSLOG_MKMSG
    mcos_log_hwl("mkmsg async send multi out %d %d\n", dest_lcid, ret);
#endif /* IS_DS_SYSLOG_MKMSG */

    return ret;
}
#endif /* #if MCOS_MKMSG_ASYNC_MULTI_IS_ENABLED */

#endif /* #ifndef MCOS_MK_MKMSG_UTIL_H */
