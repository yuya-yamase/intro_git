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
[ar_acttsk_common.h] - activate task common functions
****************************************************************************/

#ifndef AR_ACTTSK_COMMON_H
#define AR_ACTTSK_COMMON_H

#include "ar_kernel_impl.h"
#include "ar_task.h"

LOCAL_INLINE StatusType
ar_activate_task_current_core(clscb_t * const clscb, const TaskType task_id,
    const mcos_id_t tid, const ar_osap_config_t * const p_osapconfig);

/*---------------------------------------------------------------------------
  ar_activate_task_current_core

  Input     :   clscb
            :   task_id
            :   tid
  Output    :   none
  Return    :
  Note  :   none
 ---------------------------------------------------------------------------*/
LOCAL_INLINE StatusType ar_activate_task_current_core(
    clscb_t * const clscb,
    const TaskType task_id,
    const mcos_id_t tid,
    const ar_osap_config_t * const p_osapconfig)
{
    StatusType  status;
    tcb_t       *running;
    ar_critical_section_t  cs;
    mcos_er_t   ret;

#if !((AR_OS_USE_EXTENDEDSTATUS == STD_ON) && (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON))
    (void)p_osapconfig;     /* not use */
#endif /* #if !((AR_OS_USE_EXTENDEDSTATUS == STD_ON) && (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)) */

    status = E_OK;
    running = mcos_get_running(clscb);

    cs = ar_critical_section_enter_core(clscb);

#if ((AR_OS_USE_EXTENDEDSTATUS == STD_ON) && (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON))
    if (AR_IS_NOT_ACC_ACTIVE(ar_task_configs[task_id].p_osapconfig, p_osapconfig))
    {
        status = E_OS_ACCESS;
    }
    else
#endif  /* ((AR_OS_USE_EXTENDEDSTATUS == STD_ON) && (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON))  */
    {
        /* start eMCOS thread */
        ret = mcos_do_start(clscb, tid, (uint32)task_id);
        if ((sint32)ret != (sint32)MCOS_EOK)
        {
            status = (StatusType)E_OS_LIMIT;
        }
        else
        {
            if ((running != clscb->ready) && ((uint32)clscb->ctx == (uint32)CTX_NONE))
            {
                ar_dispatch_task_core(clscb, running);
            }
            else
            {
                /* Nothing to do */
            }
        }
    }

    ar_critical_section_leave_core(clscb, cs);

    return status;
}



#if (AR_OS_USE_MULTICORE == STD_ON)

LOCAL_INLINE StatusType ar_activate_task_internal_intercore(
    const mkcb_t * const mkcb,
    clscb_t * const clscb,
    const TaskType task_id,
    const ar_osap_config_t * const p_osapconfig);

/*---------------------------------------------------------------------------
  ar_activate_task_internal_intercore

  Input     :   mkcb
            :   task_id
            :   p_osapconfig
  Output    :   none
  Return    :
  Note  :   none
 ---------------------------------------------------------------------------*/
LOCAL_INLINE StatusType ar_activate_task_internal_intercore(
    const mkcb_t * const mkcb,
    clscb_t * const clscb,
    const TaskType task_id,
    const ar_osap_config_t * const p_osapconfig)
{
    StatusType      status;
    mcos_id_t       tid;
    mcos_id_t       current_lcid;
    mcos_id_t       target_lcid;

    current_lcid    = mcos_mkcc_get_lcid(mkcb);

#if ((AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) && (AR_OS_USE_EXTENDEDSTATUS == STD_ON))
    if (AR_IS_NOT_ACC_RIGHTS(clscb,
            ar_task_configs[task_id].osap_allowedmap[(uint32_t)LCID2CPUNO(current_lcid)]))
    {
        status = E_OS_ACCESS;
    }
    else
#endif  /* ((AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) && (AR_OS_USE_EXTENDEDSTATUS == STD_ON))  */
    {
        tid = ar_get_tid_by_task_id(task_id);
        target_lcid     = mcos_util_get_afinity_lcid(tid);
        if ((sint32)current_lcid != (sint32)target_lcid)
        {
            ar_api_request_t        *p_req;
            ar_api_return_t         *p_ret;
            ar_critical_section_t   cs;

            cs = ar_critical_section_enter();
            ar_get_message_buffers_on(current_lcid, clscb, &p_req, &p_ret);

            p_req->head.reqid = AR_ACTIVATE_TASK_REQID;
            p_req->head.caller.tid = 0; /* not used */
            p_req->head.caller.lcid = current_lcid;
            p_req->data.activate_task.task_id = task_id;
            p_req->data.activate_task.p_osapconfig = p_osapconfig;
            status = ar_api_call(clscb, target_lcid, p_req, p_ret);

            ar_release_message_buffers_on(current_lcid, clscb, p_req, p_ret);
            ar_critical_section_leave(cs);
        }
        else
        {
            status = ar_activate_task_current_core(clscb, task_id, tid, p_osapconfig);
        }
    }

    return status;
}

#else

LOCAL_INLINE StatusType ar_activate_task_internal_singlecore(
    const mkcb_t * const mkcb,
    clscb_t * const clscb,
    const TaskType task_id,
    const ar_osap_config_t * const p_osapconfig);

/*---------------------------------------------------------------------------
  ar_activate_task_internal_singlecore

  Input     :   mkcb
            :   task_id
            :   p_osapconfig
  Output    :   none
  Return    :
  Note  :   none
 ---------------------------------------------------------------------------*/
LOCAL_INLINE StatusType ar_activate_task_internal_singlecore(
    const mkcb_t * const mkcb,
    clscb_t * const clscb,
    const TaskType task_id,
    const ar_osap_config_t * const p_osapconfig)
{
    StatusType      status;
    mcos_id_t       tid;
    (void)mkcb;

#if ((AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) && (AR_OS_USE_EXTENDEDSTATUS == STD_ON))
    if (AR_IS_NOT_ACC_RIGHTS(clscb,
            ar_task_configs[task_id].osap_allowedmap[0]))
    {
        status = E_OS_ACCESS;
    }
    else
#endif  /* ((AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) && (AR_OS_USE_EXTENDEDSTATUS == STD_ON))  */
    {
        tid = ar_get_tid_by_task_id(task_id);

        status = ar_activate_task_current_core(clscb, task_id, tid, p_osapconfig);
    }

    return status;
}

#endif /* (AR_OS_USE_MULTICORE == STD_ON) */


LOCAL_INLINE void ar_activate_task_call_errorhook(
    StatusType  status,
    clscb_t     *clscb,
    TaskType    TaskID,
    const OSServiceIdType svcid);

/*
 * a part of ActivateTask
 */
LOCAL_INLINE void ar_activate_task_call_errorhook(
    StatusType  status,
    clscb_t     *clscb,
    TaskType    TaskID,
    const OSServiceIdType svcid)
{
#if (AR_OS_USE_ERRORHOOK == STD_ON)
    ar_critical_section_t   cs;
    ar_errhk_param_t        errhk_param[AR_ERRHK_PARAM_NUM];
    uint32                  idx;

    if (AR_IS_ENABLED_ERRORHOOK())
    {
        for(idx = 0U; idx < AR_ERRHK_PARAM_NUM; idx++)
        {
            errhk_param[idx].d_uint32 = 0U;
        }

        if (USER_CFG_STD_ON_USE_PARAMETERACCESS() != (uint32)0)
        {
            errhk_param[AR_ActivateTask_TaskID_ERROR_PARAM_NO].d_task = TaskID;
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


#endif /* AR_ACTTSK_COMMON_H */
