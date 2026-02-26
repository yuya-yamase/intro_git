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
[ar_task.h] - Task Information
****************************************************************************/

#ifndef AR_TASK_H
#define AR_TASK_H

#define AR_AUTO                 (0x00)

#define AR_MIN_TPRI             (0)
#define AR_MAX_TPRI             (31)

#define AR_NUM_TPRI             ((AR_MAX_TPRI - AR_MIN_TPRI) + 1)
#define AR_PRI_MIN_TASK         ((ar_pri_t) (AR_NUM_TPRI - 1))
#define AR_PRI_MAX_TASK         ((ar_pri_t) (0))
#define MCOS_TPRI_OFFSET        (0x80 )
#define AR_MCOS_TPRI(tpri)      ( AR_NUM_TPRI - (tpri) - 1 + MCOS_TPRI_OFFSET )
#define AR_MCOS_TPRI_HIGHEST    ( (0) + MCOS_TPRI_OFFSET )


#ifdef OS_CFG_H

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const ar_task_config_t   ar_task_configs[AR_OS_NUM_TASKS];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern ar_tcb_t * const ar_tcb_ptr_table[AR_OS_NUM_TASKS];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#else /* #ifdef OS_CFG_H */

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const ar_task_config_t   ar_task_configs[];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern ar_tcb_t * const ar_tcb_ptr_table[];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#endif /* #ifdef OS_CFG_H */


#ifdef OS_CFG_H

#define OS_START_SEC_VAR_GLOBAL_NO_INIT_16
#include "Os_MemMap.h"

extern mcos_id_t ar_task2thread_table[AR_OS_NUM_TASKS];

#define OS_STOP_SEC_VAR_GLOBAL_NO_INIT_16
#include "Os_MemMap.h"

#else /* #ifdef OS_CFG_H */

#define OS_START_SEC_VAR_GLOBAL_NO_INIT_16
#include "Os_MemMap.h"

extern mcos_id_t ar_task2thread_table[];

#define OS_STOP_SEC_VAR_GLOBAL_NO_INIT_16
#include "Os_MemMap.h"

#endif /* #ifdef OS_CFG_H */

#if (MCOS_CFG_DS_TRACE_ENABLE || (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON))
#ifdef OS_CFG_H

#define OS_START_SEC_VAR_GLOBAL_NO_INIT_16
#include "Os_MemMap.h"

extern TaskType ar_thread2task_table[MCOS_CFG_THR_MAX*MP_CONTROL_CORE_COUNT];

#define OS_STOP_SEC_VAR_GLOBAL_NO_INIT_16
#include "Os_MemMap.h"

#else /* #ifdef OS_CFG_H */

#define OS_START_SEC_VAR_GLOBAL_NO_INIT_16
#include "Os_MemMap.h"

extern TaskType ar_thread2task_table[];

#define OS_STOP_SEC_VAR_GLOBAL_NO_INIT_16
#include "Os_MemMap.h"

#endif /* #ifdef OS_CFG_H */
#endif /* #if (MCOS_CFG_DS_TRACE_ENABLE || (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)) */

#define AR_GET_TASKCONFIG(id)   (&ar_task_configs[(id)])

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

extern StatusType ar_task_init(void);
extern StatusType ar_act_activatetask(const TaskType task_id, const ar_osap_config_t * const p_osapconfig);
extern StatusType ar_act_setevent(const TaskType task_id,
        const EventMaskType event,const ar_osap_config_t * const p_osapconfig
);
extern StatusType ar_activate_task_impl(clscb_t * const clscb, const TaskType task_id, const ar_osap_config_t * const p_osapconfig);
extern StatusType ar_get_task_state_impl(const mkcb_t * const mkcb, const TaskType task_id,
        const TaskStateRefType p_state, const ar_osap_config_t * const p_osapconfig);
extern StatusType ar_set_event_impl(clscb_t * const clscb, const TaskType task_id,
        const EventMaskType event, const ar_osap_config_t * const p_osapconfig);
extern StatusType ar_get_event_impl(
#if (AR_OS_USE_EXTENDEDSTATUS == STD_ON)
        clscb_t * const clscb,
#endif
        const TaskType task_id, const EventMaskRefType p_event, const ar_osap_config_t * const p_osapconfig);

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

AR_LOCAL_FORCE_INLINE void ar_dispatch_task_core(clscb_t * const clscb, tcb_t * const running);
AR_LOCAL_FORCE_INLINE void ar_dispatch_task_core_noreturn(const clscb_t * const clscb, const tcb_t * const running);
AR_LOCAL_FORCE_INLINE void ar_do_dispatch_task(clscb_t * const clscb);
AR_LOCAL_FORCE_INLINE void ar_dispatch_task(void);
AR_LOCAL_FORCE_INLINE mcos_id_t ar_get_tid_by_task_id(const TaskType task_id);
AR_LOCAL_FORCE_INLINE TaskType ar_get_task_id_by_ar_tcb(const ar_tcb_t * const p_atcb);
AR_LOCAL_FORCE_INLINE tcb_t* ar_get_mcos_tcb(const TaskType task_id);


AR_LOCAL_FORCE_INLINE void ar_dispatch_task_core(
    clscb_t * const clscb,
    tcb_t * const running)
{
    /* context switch */
    mcos_dispatch_context(clscb, running);
}

AR_LOCAL_FORCE_INLINE void ar_dispatch_task_core_noreturn(
    const clscb_t * const clscb,
    const tcb_t * const running)
{
    /* context switch */
    mcos_dispatch_context_noreturn(clscb, running);
}

AR_LOCAL_FORCE_INLINE void ar_do_dispatch_task(
    clscb_t * const clscb)
{
    tcb_t           *running;

    running = clscb->running;
    if (running != clscb->ready)
    {
        ar_dispatch_task_core(clscb, running);
    }
    else
    {
        /* Nothing to do */
    }
}

AR_LOCAL_FORCE_INLINE void ar_dispatch_task(void)
{
    const mkcb_t    *mkcb;
    clscb_t         *clscb;

    mkcb = (const mkcb_t *)mcos_mkcc_get_current_control_block();
    clscb = mcos_mkcc_get_clscb(mkcb);

    if ((uint32)clscb->ctx == (uint32)CTX_NONE)
    {
        ar_do_dispatch_task(clscb);
    }
    else
    {
        /* Nothing to do */
    }
}


AR_LOCAL_FORCE_INLINE mcos_id_t ar_get_tid_by_task_id(
    const TaskType task_id)
{
    return ar_task2thread_table[task_id];
}

AR_LOCAL_FORCE_INLINE TaskType ar_get_task_id_by_ar_tcb(
    const ar_tcb_t * const p_atcb)
{
    return (TaskType)(((uint32_t)((p_atcb)->p_config) - (uint32_t)ar_task_configs) / sizeof(ar_task_config_t));
}

AR_LOCAL_FORCE_INLINE tcb_t* ar_get_mcos_tcb(
    const TaskType task_id)
{
    return (ar_tcb_ptr_table[task_id]->p_mcos_tcb);
}


#endif /* AR_TASK_H_ */
