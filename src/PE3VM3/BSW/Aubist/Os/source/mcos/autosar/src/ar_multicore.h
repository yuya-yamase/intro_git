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
[ ar_multicore.h ] - MCOS AUTOSAR multicore implementation header
****************************************************************************/

#ifndef AR_MULTICORE_H
#define AR_MULTICORE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ar_mkmsg.h"

/* sync phase number */
#define AR_PHASE_INIT_FIRST                 (0x01U)
#define AR_PHASE_INIT_OBJECTS               (0x02U)
#define AR_PHASE_INIT_LAST                  (0x03U)
#define AR_PHASE_SHUTDOWN                   (0x04U)

#ifdef OS_CFG_H
#if (AR_OS_USE_MULTICORE == STD_ON)

#define OS_START_SEC_VAR_CLEARED_32
#include "Os_MemMap.h"

extern volatile uint32 ar_core_state_table[AR_OS_NUM_CORES + AR_OS_NUM_NON_AUTOSAR_CORES];

#define OS_STOP_SEC_VAR_CLEARED_32
#include "Os_MemMap.h"

#endif /* #if (AR_OS_USE_MULTICORE == STD_ON) */
#else /* #ifdef OS_CFG_H */

#define OS_START_SEC_VAR_CLEARED_32
#include "Os_MemMap.h"

extern volatile uint32 ar_core_state_table[];

#define OS_STOP_SEC_VAR_CLEARED_32
#include "Os_MemMap.h"

#endif /* #ifdef OS_CFG_H */

#define OS_START_SEC_VAR_CLEARED_32
#include "Os_MemMap.h"

extern volatile uint32     ar_activated_slave_corecnt;

#define OS_STOP_SEC_VAR_CLEARED_32
#include "Os_MemMap.h"

#ifdef OS_CFG_H

#define OS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Os_MemMap.h"

extern AppModeType  ar_appmode_core_saved[AR_OS_NUM_CORES];

#define OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Os_MemMap.h"

#else /* #ifdef OS_CFG_H */

#define OS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Os_MemMap.h"

extern AppModeType  ar_appmode_core_saved[];

#define OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Os_MemMap.h"

#endif /* #ifdef OS_CFG_H */

#ifdef OS_CFG_H

#define OS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Os_MemMap.h"

extern AppModeType  ar_appmode_core[AR_OS_NUM_CORES];

#define OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Os_MemMap.h"

#else /* #ifdef OS_CFG_H */

#define OS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Os_MemMap.h"

extern AppModeType  ar_appmode_core[];

#define OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Os_MemMap.h"

#endif /* #ifdef OS_CFG_H */

#ifdef OS_CFG_H

#define OS_START_SEC_VAR_CLEARED_BOOLEAN
#include "Os_MemMap.h"

extern volatile boolean ar_is_autosar_core[AR_OS_NUM_CORES];

#define OS_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Os_MemMap.h"

#else /* #ifdef OS_CFG_H */

#define OS_START_SEC_VAR_CLEARED_BOOLEAN
#include "Os_MemMap.h"

extern volatile boolean ar_is_autosar_core[];

#define OS_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Os_MemMap.h"

#endif /* #ifdef OS_CFG_H */

#if (AR_OS_USE_MULTICORE == STD_ON)
#ifdef OS_CFG_H

#define OS_START_SEC_VAR_CLEARED_8
#include "Os_MemMap.h"

extern volatile uint8   ar_core_phases[AR_OS_NUM_CORES];

#define OS_STOP_SEC_VAR_CLEARED_8
#include "Os_MemMap.h"

#else /* #ifdef OS_CFG_H */

#define OS_START_SEC_VAR_CLEARED_8
#include "Os_MemMap.h"

extern volatile uint8   ar_core_phases[];
#define OS_STOP_SEC_VAR_CLEARED_8
#include "Os_MemMap.h"

#endif /* #ifdef OS_CFG_H */

#define OS_START_SEC_VAR_CLEARED_8
#include "Os_MemMap.h"

extern volatile uint8   ar_master_phase;

#define OS_STOP_SEC_VAR_CLEARED_8
#include "Os_MemMap.h"
#endif /* #if (AR_OS_USE_MULTICORE == STD_ON) */

#if ((!defined(OS_CFG_H)) || (AR_OS_USE_MULTICORE == STD_ON))

#define OS_START_SEC_VAR_CLEARED_BOOLEAN
#include "Os_MemMap.h"

extern volatile boolean    ar_is_shutdown_accepted;

#define OS_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Os_MemMap.h"

#endif /* #if ((!defined(OS_CFG_H)) || (AR_OS_USE_MULTICORE == STD_ON)) */

#if ((!defined(OS_CFG_H)) || (AR_OS_USE_MULTICORE == STD_ON))

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const ar_api_request_t  ar_shutdown_msg;

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#endif /* #if ((!defined(OS_CFG_H)) || (AR_OS_USE_MULTICORE == STD_ON)) */

#ifdef OS_CFG_H

#if (AR_OS_USE_MULTICORE == STD_ON)

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern ar_api_request_t * const ar_mkmsg_request_buffer_table[MP_CONTROL_CORE_COUNT];

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern ar_api_return_t * const ar_mkmsg_return_buffer_table[MP_CONTROL_CORE_COUNT];

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#endif /* (AR_OS_USE_MULTICORE == STD_ON) */

#else /* #ifdef OS_CFG_H */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern ar_api_request_t * const ar_mkmsg_request_buffer_table[];

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern ar_api_return_t * const ar_mkmsg_return_buffer_table[];

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#endif /* #ifdef OS_CFG_H */

#if (!defined(OS_CFG_H) || (AR_OS_USE_MULTICORE == STD_ON))

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

extern void ar_multicore_init(void);
extern void ar_set_sync_phase(uint8 phase);
extern void ar_sync_cores(const uint8 phase, const boolean check_shutdown);

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

AR_LOCAL_FORCE_INLINE void ar_dispatch_request_send_self(void);

/*---------------------------------------------------------------------------
  ar_dispatch_request_self

  Input     :   none
  Output    :   none
  Return    :   none
  Note  :   none
 ---------------------------------------------------------------------------*/
AR_LOCAL_FORCE_INLINE void ar_dispatch_request_send_self(void)
{
    mcos_mkmsg_request_raise(mcos_get_lcid());
    return ;
}
#if (AR_ENABLE_CHAIN_TASK != 0U)
AR_LOCAL_FORCE_INLINE StatusType ar_api_call_chain(
    clscb_t *clscb,
    const mcos_id_t dest_lcid,
    const ar_api_request_t * const p_req, ar_api_return_t * const p_ret);
#endif /* #if (AR_ENABLE_CHAIN_TASK != 0U) */

AR_LOCAL_FORCE_INLINE StatusType ar_api_call(
    clscb_t *clscb,
    const mcos_id_t dest_lcid,
    const ar_api_request_t * const p_req, ar_api_return_t * const p_ret);
AR_LOCAL_FORCE_INLINE StatusType ar_api_call_async(
    const mcos_id_t dest_lcid,
    const ar_api_request_t * const p_req);
AR_LOCAL_FORCE_INLINE boolean ar_is_master_core(void);
AR_LOCAL_FORCE_INLINE CoreIdType ar_get_core_id(void);
AR_LOCAL_FORCE_INLINE boolean ar_start_core(const CoreIdType core_id);
AR_LOCAL_FORCE_INLINE boolean ar_is_core_deactivated(const CoreIdType core_id);

AR_LOCAL_FORCE_INLINE void ar_get_message_buffers_on(mcos_id_t lcid, clscb_t const *clscb, ar_api_request_t **p_req, ar_api_return_t **p_ret);
AR_LOCAL_FORCE_INLINE void ar_release_message_buffers_on(mcos_id_t lcid, clscb_t const *clscb, ar_api_request_t const *p_req, ar_api_return_t const *p_ret);

AR_LOCAL_FORCE_INLINE void ar_get_message_buffers_on(mcos_id_t lcid, clscb_t const *clscb,
    ar_api_request_t **p_req, ar_api_return_t **p_ret)
{
    /* [PRQA_4393] Countermeasure for PRQA warning. */
    int32_t             cpuno = LCID2CPUNO(lcid);
    ar_api_request_t    *req_buffer = (ar_api_request_t *)ar_mkmsg_request_buffer_table[cpuno];
    ar_api_return_t     *ret_buffer = (ar_api_return_t *)ar_mkmsg_return_buffer_table[cpuno];

    if (((uint32)clscb->aroscb.call_level & AR_CL_HK_PROT) == (uint32)0x0)
    {
        *p_req = &req_buffer[0x0U];
        *p_ret = &ret_buffer[0x0U];
    }
    else
    {
        /* in protection hook */
        *p_req = &req_buffer[0x1U];
        *p_ret = &ret_buffer[0x1U];
    }
}

AR_LOCAL_FORCE_INLINE void ar_release_message_buffers_on(mcos_id_t lcid, clscb_t const *clscb,
    ar_api_request_t const *p_req, ar_api_return_t const *p_ret)
{
    /* Nothing to do */
    (void)lcid;
    (void)clscb;
    (void)p_req;
    (void)p_ret;
}

#if (AR_ENABLE_CHAIN_TASK != 0U)
/*
 * This function is special version of ar_api_call() for ChainTask.
 * - The reply is given priority over requests.
 */
AR_LOCAL_FORCE_INLINE StatusType ar_api_call_chain(
    clscb_t *clscb,
    const mcos_id_t dest_lcid,
    const ar_api_request_t * const p_req,
    ar_api_return_t * const p_ret)
{
    StatusType      status;
    uint32_t        sent;
    const mkcb_t    *mkcb;

    mkcb = (const mkcb_t *)mcos_mkcc_get_current_control_block();

    status = (StatusType)E_OS_SYSTEM;

    sent = mcos_mkmsg_request_send(mkcb, dest_lcid, p_req, p_ret);
    if (sent != 0U)
    {
        uint32_t    is_received;

        /*
         * wait for response
         */
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
        clscb->aroscb.wait_in_chaintask = (boolean)TRUE;
#else /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
        (void)clscb;
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
        do
        {
            is_received = mcos_mkmsg_request_reply_receive(mkcb, p_ret);
        } while (is_received == 0U);
        status = p_ret->head.status;
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
        clscb->aroscb.wait_in_chaintask = (boolean)FALSE;
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
    }
    else
    {
        /* Nothing to do */
    }
    return status;
}
#endif /* #if (AR_ENABLE_CHAIN_TASK != 0U) */

/*
 * ar_api_call
 *  called in critical sction
 */
AR_LOCAL_FORCE_INLINE StatusType ar_api_call(
    clscb_t *clscb,
    const mcos_id_t dest_lcid,
    const ar_api_request_t * const p_req,
    ar_api_return_t * const p_ret)
{
    StatusType      status;
    uint32_t        is_received;
    uint32_t        sent;
    const mkcb_t    *mkcb;

    mkcb = (const mkcb_t *)mcos_mkcc_get_current_control_block();

#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 != STD_ON)
    (void)clscb;
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 != STD_ON) */

    status = (StatusType)E_OS_SYSTEM;
    sent = mcos_mkmsg_request_send(mkcb, dest_lcid, p_req, p_ret);
    if (sent != 0U)
    {
        /*
         * wait for response
         */
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
        clscb->aroscb.p_wait_for_response = clscb->aroscb.p_runosap;
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

        is_received = mcos_mkmsg_reply_receive(mkcb, p_ret);
        while (is_received == 0U)
        {
            mcos_mkmsg_request_receive(mkcb);
            is_received = mcos_mkmsg_reply_receive(mkcb, p_ret);
        }

        status = p_ret->head.status;
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
        clscb->aroscb.p_wait_for_response = NULL;
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
    }
    else
    {
        /* fatal error */
            status = (StatusType)E_OS_SYSTEM;
    }
    return status;
}

/*
 * ar_api_call_async
 *  called in critical sction
 */
AR_LOCAL_FORCE_INLINE StatusType ar_api_call_async(
    const mcos_id_t dest_lcid,
    const ar_api_request_t * const p_req)
{
    StatusType  status;
    uint32_t    sent;
    const mkcb_t    *mkcb;

    mkcb = (const mkcb_t *)mcos_mkcc_get_current_control_block();

    sent = mcos_mkmsg_request_send_async(mkcb, dest_lcid, p_req, sizeof(ar_api_request_t));

    if (sent != 0U)
    {
        status = E_OK;
    }
    else
    {
        status = (StatusType)E_OS_SYSTEM;
    }
    return status;
}

AR_LOCAL_FORCE_INLINE boolean ar_is_master_core(void)
{
    const mcos_id_t core_id = mcos_get_lcid();
    return (boolean)(((int32_t)core_id == BOOT_CORE_LCID) ? TRUE : FALSE);
}


AR_LOCAL_FORCE_INLINE CoreIdType ar_get_core_id(void)
{
    int32_t target_cpuno = LCID2CPUNO(mcos_get_lcid());
    CoreIdType target_coreid = (CoreIdType)target_cpuno;

    return target_coreid;
}

AR_LOCAL_FORCE_INLINE boolean ar_start_core(
    const CoreIdType core_id)
{
    boolean valid_core;

    if ((uint32)core_id < ((uint32)USER_CFG_AR_OS_NUM_CORES() + (uint32)USER_CFG_AR_OS_NUM_NON_AUTOSAR_CORES()))
    {
        xmcos_slave_start((uint32_t)core_id);
        ar_core_state_table[core_id] = (uint32)0x01234567U;
        mcos_hwl_memory_barrier();
        valid_core = (boolean)TRUE;
    }
    else {
        valid_core = (boolean)FALSE;
    }
    return valid_core;
}

AR_LOCAL_FORCE_INLINE boolean ar_is_core_deactivated(
    const CoreIdType core_id)
{
    return (boolean)((ar_core_state_table[core_id] == (uint32)0U) ? TRUE : FALSE);
}

#endif /* #if (!defined(OS_CFG_H) || (AR_OS_USE_MULTICORE == STD_ON)) */

#ifdef __cplusplus
}
#endif

#endif /* AR_MULTICORE_H */
