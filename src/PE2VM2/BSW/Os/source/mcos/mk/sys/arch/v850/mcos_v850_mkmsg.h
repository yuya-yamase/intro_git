/*
    Copyright(C) 2021 eSOL Co., Ltd. All rights reserved.

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
[mcos_v850_mkmsg.h] - eMCOS mkmsg internal header for v850
****************************************************************************/
#ifndef MCOS_V850_MKMSG_H
#define MCOS_V850_MKMSG_H

#if !MCOS_AUTOSAR
#error "Non-autosar is not supported."
#else /* #if !MCOS_AUTOSAR */

#include <mcos_mk_local.h>

#include "mcos_mk_data.h"
/*
 * assertion check of mkmsg
 *  defined     : no check
 *  no defined  : check assertion
 */
#define MCOS_MKMSG_NDEBUG   1

/*
 * memory architecture
 *  MCOS_MKMSG_MATYPE_UMA   : uniformed memory architecture
 *  MCOS_MKMSG_MATYPE_NUMA  : non-uniformed memory architecture
 *  MCOS_MKMSG_MATYPE       : current type is uma or numa
 */
#define MCOS_MKMSG_MATYPE_UMA   1U
#define MCOS_MKMSG_MATYPE_NUMA  2U
#define MCOS_MKMSG_MATYPE       MCOS_MKMSG_MATYPE_UMA

/*
 * MCOS_MKMSG_SYNC_IS_ENABLED
 *  sync communication is enabled or not
 *      1 : enable
 *      0 : disable
 */
#define MCOS_MKMSG_SYNC_IS_ENABLED          1U   /* run-time evaluation */

/*
 * MCOS_MKMSG_ASYNC_IS_ENABLED
 *  async communication is enabled or not
 *      1 : enable
 *      0 : disable
 * MCOS_MKMSG_ASYNC_MULTI_IS_ENABLED
 *  mcos_mkmsg_request_send_async_multi() is disable already
 */
#define MCOS_MKMSG_ASYNC_IS_ENABLED         1U   /* run-time evaluation */
#define MCOS_MKMSG_ASYNC_MULTI_IS_ENABLED   1U   /* run-time evaluation */

/* ring buffer unsigned int */
typedef uint32_t mcos_ringbuf_uint_t;

/* ring buffer size/offset */
typedef uint16_t mcos_ringbuf_index_t;


/* reply control block */
typedef struct
{
    /* reply state of sender */
    volatile mcos_ringbuf_uint_t    reply_state;
} mkmsg_replycb_t;

/* fixed length data unit */
typedef struct
{
    /* request */
    const void *request;
    /* reply */
    void *reply;
    /* reply control block of sender */
    mkmsg_replycb_t *replycb;
} mcos_ringbuf_funit_t;

/* variable length request max size (mcos_ringbuf_vunit_t count) */
#define MCOS_RINGBUF_VREQUEST_MAX_SIZE  (sizeof(ar_api_request_t) / sizeof(mcos_ringbuf_vunit_t))

/* size round up for alignment */
#define MCOS_RINGBUF_ROUNDUP_BIT    2U  /* 2^2 = 4 */
#define MCOS_RINGBUF_ROUNDUP_UNIT   (uint8_t)(1U << MCOS_RINGBUF_ROUNDUP_BIT)
#define MCOS_RINGBUF_ROUNDUP(x)     (uint32_t)((uint32_t)((uint32_t)((x)+(MCOS_RINGBUF_ROUNDUP_UNIT-(uint8_t)1)) >> MCOS_RINGBUF_ROUNDUP_BIT) << MCOS_RINGBUF_ROUNDUP_BIT)

/* ring buffer control block */
typedef struct
{
    /* spinlock object */
    uint32                          padding1[7];    /* see R01UH0864EJ0100 Rev.1.00 Table 3.157 Link Loss Conditions */
    mcos_spinlock_obj_t             lock;
    uint32                          padding2[7];
    /* read offset (items/bytes) */
    volatile mcos_ringbuf_index_t   read;
    /* written size (items/bytes) */
    volatile mcos_ringbuf_index_t   size;
#if MCOS_MKMSG_ASYNC_IS_ENABLED
    /* user message written size(bytes). this only uses in async communication */
    volatile mcos_ringbuf_index_t   size_usermsg;
#endif /* #if MCOS_MKMSG_ASYNC_IS_ENABLED */
} mcos_ringbuf_t;

/*
 * mkmsg sync buffer
 *   MCOS_MKMSG_SYNC_BUF_SIZE     sync buffer size (items)
 */
#define MCOS_MKMSG_SYNC_BUF_SIZE            ((uint32_t)mcos_mkconfig.control_core_count - 1U)

/*
 * mkmsg async buffer
 *   MCOS_MKMSG_ASYNC_BUF_SIZE          async buffer size (bytes)
 */
#if (MP_CONTROL_CORE_COUNT > 1U)
/* eMCOS AUTOSAR multicore */
#define MCOS_MKMSG_ASYNC_BUF_SIZE           (mcos_ringbuf_vunit_t)(sizeof(ar_api_request_t) + sizeof(mcos_ringbuf_vunit_t))
#else /* #if (MP_CONTROL_CORE_COUNT > 1U) */
/* others */
#define MCOS_MKMSG_ASYNC_BUF_SIZE           0U
#endif /* #if (MP_CONTROL_CORE_COUNT > 1U) */

/* mkmsg communication buffer */
typedef struct
{
#if MCOS_MKMSG_SYNC_IS_ENABLED
    /* sync communication control block */
    mcos_ringbuf_t                  sync;
    /* sync communication buffer for received request */
    volatile mcos_ringbuf_funit_t   *sync_data;
    /* sync communication received reply control block */
    mkmsg_replycb_t                 sync_reply;
#endif /* #if MCOS_MKMSG_SYNC_IS_ENABLED */
#if MCOS_MKMSG_ASYNC_IS_ENABLED
    /* async communication control block */
    mcos_ringbuf_t                  async;
    /* async communication buffer for received request */
    volatile mcos_ringbuf_uint8_t   *async_data;
#endif /* #if MCOS_MKMSG_ASYNC_IS_ENABLED */
#if ((!MCOS_MKMSG_SYNC_IS_ENABLED) && (!MCOS_MKMSG_ASYNC_IS_ENABLED))
    /* dummy data */
    mcos_ringbuf_uint_t    dummy;
#endif /* #if ((!MCOS_MKMSG_SYNC_IS_ENABLED) && (!MCOS_MKMSG_ASYNC_IS_ENABLED)) */
} mkmsg_buf_t;

/* mkmsg control block */
typedef mkmsg_buf_t mkmsg_t;


#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern volatile mcos_ringbuf_funit_t * const mcos_v850_sync_data_table[MP_CONTROL_CORE_COUNT];

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern volatile mcos_ringbuf_uint8_t * const mcos_v850_async_data_table[MP_CONTROL_CORE_COUNT];

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#endif /* !MCOS_AUTOSAR */

#endif /* #ifndef MCOS_V850_MKMSG_H */

