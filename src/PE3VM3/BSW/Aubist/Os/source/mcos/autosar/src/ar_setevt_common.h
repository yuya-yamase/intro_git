/*
    Copyright (C) 2016 By eSOL Co.,Ltd. Tokyo, Japan

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
[ar_setevt_common.h] - set event common functions
****************************************************************************/

#ifndef AR_SETEVT_COMMON_H
#define AR_SETEVT_COMMON_H

#include "ar_kernel_impl.h"
#include "ar_task.h"

LOCAL_INLINE StatusType ar_set_event_current_core(clscb_t * const clscb, const EventMaskType event,
    const tcb_t * const p_mtcb, ar_tcb_t * const p_atcb, const mcos_id_t tid,
    const ar_osap_config_t * const p_osapconfig);

/*---------------------------------------------------------------------------
  ar_set_event_current_core

  Input     :   clscb
            :   event
            :   p_mtcb
            :   p_atcb
            :   tid
            :   p_osapconfig
  Output    :   none
  Return    :
  Note  :   called in exclusive area
 ---------------------------------------------------------------------------*/
LOCAL_INLINE StatusType ar_set_event_current_core(
    clscb_t * const clscb,
    const EventMaskType event,
    const tcb_t * const p_mtcb,
    ar_tcb_t * const p_atcb,
    const mcos_id_t tid,
    const ar_osap_config_t * const p_osapconfig)
{
    StatusType      status;
    ar_critical_section_t   cs;
    EventMaskType   cev;

    status = E_OK;

    cs = ar_critical_section_enter_core(clscb);

#if (AR_OS_USE_EXTENDEDSTATUS == STD_ON)
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
    if (AR_IS_NOT_ACC_ACTIVE(p_atcb->p_config->p_osapconfig, p_osapconfig))
    {
        status = E_OS_ACCESS;
    }
    else
#else  /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)    */
    (void)p_osapconfig;
#endif  /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)    */
    if (((uint32)p_mtcb->migratable.attr_state.state == (uint32)MCOS_THR_STATE_DORMANT))
    {
        status = E_OS_STATE;
    }
    else
#endif  /* (AR_OS_USE_EXTENDEDSTATUS == STD_ON) */
    {
        cev = p_atcb->current_event | event;
        p_atcb->current_event = cev;
        if ((cev & p_atcb->wait_event) != AR_EVENT_MASK_NONE)
        {
            tcb_t       *running;

            p_atcb->wait_event = AR_EVENT_MASK_NONE;
            mcos_do_wakeup(clscb, tid);

            running = mcos_get_running(clscb);
            if ((running != clscb->ready) && ((uint32)clscb->ctx == (uint32)CTX_NONE))
            {
                ar_dispatch_task_core(clscb, running);
            }
            else
            {
                /* Nothing to do */
            }
        }
        else
        {
            /* Nothing to do */
        }
    }

    ar_critical_section_leave_core(clscb, cs);

    return status;
}

#if (AR_OS_USE_MULTICORE == STD_ON)

LOCAL_INLINE StatusType ar_set_event_internal_intercore(
    const TaskType task_id,
    const EventMaskType event,
    const ar_osap_config_t * const p_osapconfig);

/*---------------------------------------------------------------------------
  ar_set_event_internal_intercore

  Input     :   task_id
            :   event
            :   omit_dispatch
  Output    :   none
  Return    :
  Note  :   none
 ---------------------------------------------------------------------------*/
LOCAL_INLINE StatusType ar_set_event_internal_intercore(
    const TaskType task_id,
    const EventMaskType event,
    const ar_osap_config_t * const p_osapconfig)
{
    StatusType      status;
    const mkcb_t    *mkcb;
    clscb_t         *clscb;
    mcos_id_t       tid;
    mcos_id_t       current_lcid;
    mcos_id_t       target_lcid;

    mkcb = (const mkcb_t *)mcos_mkcc_get_current_control_block();
    clscb = mcos_mkcc_get_clscb(mkcb);
    tid = ar_get_tid_by_task_id(task_id);
    current_lcid    = mcos_mkcc_get_lcid(mkcb);
    target_lcid     = mcos_util_get_afinity_lcid(tid);
    if ((sint32)current_lcid != (sint32)target_lcid)
    {
        ar_api_request_t        *p_req;
        ar_api_return_t         *p_ret;
        ar_critical_section_t   cs;

        cs = ar_critical_section_enter();
        ar_get_message_buffers_on(current_lcid, clscb, &p_req, &p_ret);

        p_req->head.reqid = AR_SET_EVENT_REQID;
        p_req->head.caller.tid = 0;
        p_req->head.caller.lcid = current_lcid;
        p_req->data.set_event.task_id = task_id;
        p_req->data.set_event.event = event;
        p_req->data.set_event.p_osapconfig = p_osapconfig;

        status = ar_api_call(clscb, target_lcid, p_req, p_ret);

        ar_release_message_buffers_on(current_lcid, clscb, p_req, p_ret);
        ar_critical_section_leave(cs);
    }
    else
    {
        tcb_t const *p_mtcb;
        ar_tcb_t    *p_atcb;
        p_mtcb = ar_get_mcos_tcb(task_id);
        p_atcb = ar_get_ar_tcb(p_mtcb);

        status = ar_set_event_current_core(clscb, event, p_mtcb, p_atcb, tid, p_osapconfig);
    }

    return status;
}

#else /* (AR_OS_USE_MULTICORE == STD_ON) */

LOCAL_INLINE StatusType ar_set_event_internal_singlecore(
    const TaskType task_id,
    const EventMaskType event,
    const ar_osap_config_t * const p_osapconfig);

/*---------------------------------------------------------------------------
  ar_set_event_internal_singlecore

  Input     :   task_id
            :   event
            :   p_osapconfig
  Output    :   none
  Return    :
  Note  :   none
 ---------------------------------------------------------------------------*/
LOCAL_INLINE StatusType ar_set_event_internal_singlecore(
    const TaskType task_id,
    const EventMaskType event,
    const ar_osap_config_t * const p_osapconfig)
{
    StatusType      status;
    const mkcb_t    *mkcb;
    clscb_t         *clscb;
    mcos_id_t       tid;
    tcb_t const     *p_mtcb;
    ar_tcb_t        *p_atcb;

    mkcb = (const mkcb_t *)mcos_mkcc_get_current_control_block();
    clscb = mcos_mkcc_get_clscb(mkcb);
    tid = ar_get_tid_by_task_id(task_id);
    p_mtcb = ar_get_mcos_tcb(task_id);
    p_atcb = ar_get_ar_tcb(p_mtcb);

    status = ar_set_event_current_core(clscb, event, p_mtcb, p_atcb, tid, p_osapconfig);

    return status;
}

#endif /* (AR_OS_USE_MULTICORE == STD_ON) */

LOCAL_INLINE void ar_set_event_call_errorhook(
    StatusType  status,
    clscb_t     *clscb,
    TaskType task_id,
    EventMaskType event,
    const OSServiceIdType svcid);

/*
 * a part of SetEvent
 */
LOCAL_INLINE void ar_set_event_call_errorhook(
    StatusType  status,
    clscb_t     *clscb,
    TaskType task_id,
    EventMaskType event,
    const OSServiceIdType svcid)
{
#if (AR_OS_USE_ERRORHOOK == STD_ON)
    ar_critical_section_t   cs;
    ar_errhk_param_t errhk_param[AR_ERRHK_PARAM_NUM];
    uint32 idx;

    if (AR_IS_ENABLED_ERRORHOOK())
    {
        for(idx = 0U; idx < AR_ERRHK_PARAM_NUM; idx++)
        {
            errhk_param[idx].d_uint32 = 0U;
        }

        if (USER_CFG_STD_ON_USE_PARAMETERACCESS() != (uint32)0)
        {
            errhk_param[AR_SetEvent_TaskID_ERROR_PARAM_NO].d_task = task_id;
            errhk_param[AR_SetEvent_Mask_ERROR_PARAM_NO].d_eventmask = event;
        }
        else
        {
            /* Nothing to do */
        }

        cs = ar_critical_section_enter_core(clscb);
        AR_SVC_SUBSTANCE(ar_errorhook_call)(status, svcid, errhk_param);
        ar_critical_section_leave_core(clscb, cs);
    }
    else
    {
        /* Nothing to do */
    }
#endif /* (AR_OS_USE_ERRORHOOK == STD_ON) */
}

#endif /* AR_SETEVT_COMMON_H */
