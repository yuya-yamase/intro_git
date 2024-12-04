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
[ mcos_mkmsg.h ] - eMCOS mkmsg interface header
****************************************************************************/
#ifndef MCOS_MKMSG_H
#define MCOS_MKMSG_H

#include "mcos_cmn.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

/* ring buffer unsigned char */
typedef uint8_t  mcos_ringbuf_uint8_t;

/* variable length data unit */
typedef uint32_t mcos_ringbuf_vunit_t;

/* initialize mkmsg  */
void mcos_mkmsg_init (
    const mkcb_t * const mkcb);

/* send request sync */
uint32_t mcos_mkmsg_request_send (
    const mkcb_t * const mkcb,
    const mcos_id_t dest_lcid,
    const void * const request,
    void * const reply);

/* receive reply */
uint32_t mcos_mkmsg_reply_receive (
    const mkcb_t * const mkcb,
    void * const reply);

/* receive reply and requests */
uint32_t mcos_mkmsg_request_reply_receive (
    const mkcb_t * const mkcb,
    void * const reply);

/* raise request notify */
void mcos_mkmsg_request_raise (
    const mcos_id_t dest_lcid);

/* receive requests */
void mcos_mkmsg_request_receive (
    const mkcb_t * const mkcb);

/* send request async */
uint32_t mcos_mkmsg_request_send_async (
    const mkcb_t * const mkcb,
    const mcos_id_t dest_lcid,
    const void * const request,
    const uint32_t request_size);

#if !MCOS_AUTOSAR

/* send request async multi */
uint32_t mcos_mkmsg_request_send_async_multi (
    const mkcb_t * const mkcb,
    const mcos_id_t dest_lcid,
    const void * const * const requests,
    const uint32_t * const requests_sizes);
#endif  /* #if !MCOS_AUTOSAR */

#if (MCOS_HWCL) && (MCOS_CFG_GLB_CLMM_ENABLE)
/* receive requests from inter-cluster communication */
void mcos_mkmsg_request_receive_icc (
    const mkcb_t * const mkcb);

/* receive cluster synchronization data */
void mcos_mkmsg_cluster_sync_receive(void);
#endif /* (MCOS_HWCL) && (MCOS_CFG_GLB_CLMM_ENABLE) */

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#endif /* #ifndef MCOS_MKMSG_H */

