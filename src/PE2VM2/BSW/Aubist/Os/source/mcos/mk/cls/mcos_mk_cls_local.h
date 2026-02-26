/*
    Copyright (C) 2015 eSOL Co.,Ltd. Tokyo, Japan

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
[ mcos_mk_cls_local.h ] - eMCOS/MK core local scheduler local header
****************************************************************************/
#ifndef MCOS_MK_CLS_LOCAL_H
#define MCOS_MK_CLS_LOCAL_H

#include "mcos_mk_local.h"

#if !MCOS_AUTOSAR
#include <string.h>
#endif /* !MCOS_AUTOSAR */

MCOS_INLINE mcos_bool_t migration_has_request(const clscb_t * const clscb);
#if !MCOS_AUTOSAR
MCOS_INLINE void migration_init(clscb_t *clscb);
#endif /* #if !MCOS_AUTOSAR */
MCOS_INLINE void set_running(clscb_t * const clscb, tcb_t * const running);
MCOS_INLINE tcb_t * get_running(const clscb_t * const clscb);
MCOS_INLINE mcos_uintptr_t get_thread_name(const tcb_t * const tcb);
MCOS_INLINE void call_userhook_enter_idle(const tcb_t * const running, const tcb_t * const ready);
MCOS_INLINE void call_userhook_leave_idle(const tcb_t * const running, const tcb_t * const ready);

#if MCOS_CFG_PARAM_CHECK || (MCOS_AUTOSAR && (AR_OS_USE_STACKMONITORING == STD_ON))
void check_stack_overflow(const tcb_t * const tcb, mcos_uintptr_t sp);
#endif /* #if MCOS_CFG_PARAM_CHECK || (MCOS_AUTOSAR && (AR_OS_USE_STACKMONITORING == STD_ON)) */

#if !MCOS_AUTOSAR
void do_migration_send(const mkcb_t *mkcb, msg_tmig_snd_t *req);
#endif /* !MCOS_AUTOSAR */

void mcos_hwl_ctx_switch(mcos_uintptr_t *poldsp, mcos_bool_t hasRequest, uint32_t type);
#if MCOS_AUTOSAR
void mcos_hwl_ctx_switch_noreturn(mcos_bool_t hasRequest, uint32_t type);
#endif  /* MCOS_AUTOSAR */

#define TCB_THREAD_NAME(tcb)    get_thread_name(tcb)

tcb_t** find_tcb(tcb_t **p, const mcos_id_t tid);
tcb_t** find_live_tcb(clscb_t * const clscb, const mcos_id_t tid);

#define CLS_DISP_TYPE_THREAD    0
#define CLS_DISP_TYPE_INT       1

/*
 * internal definitions for request reply message
 */

#define RRM_INTERNAL_REQ_MASK   (0x03)
#define RRM_INTERNAL_REP_MASK   (0x0c)

#define RRM_INTERNAL_REQ_ADDR   (0x00)
#define RRM_INTERNAL_REQ_TEMP   (0x01)
#define RRM_INTERNAL_REQ_HEAP   (0x02)

#define RRM_INTERNAL_REP_ADDR   (0x00)
#define RRM_INTERNAL_REP_NONE   (0x04)
#define RRM_INTERNAL_REP_TEMP   (0x08)

#define RRM_INTERNAL_MSND_MODE  (0x10)

#define MCOS_CLS_NULL           ((void *)0)

/*
 * check migration request
 */
MCOS_INLINE mcos_bool_t migration_has_request(
    const clscb_t * const clscb)
{
#if !MCOS_AUTOSAR
    return (mcos_bool_t)((clscb->mig != 0) ? mcos_true : mcos_false);
#else /* #if !MCOS_AUTOSAR */
    (void)clscb;
    return (mcos_bool_t)mcos_false;
#endif /* #if !MCOS_AUTOSAR */
}

/*
 * initialize migration pending
 */
#if !MCOS_AUTOSAR
MCOS_INLINE void migration_init(
    clscb_t *clscb)
{
    clscb->mig = 0;
}
#endif

MCOS_INLINE mcos_uintptr_t get_thread_name(
    const tcb_t * const tcb)
{
#if !MCOS_USE_PROCESS_MODEL
    mcos_uintptr_t addr = (mcos_uintptr_t)(tcb)->migratable.stkaddr + (tcb)->migratable.stksz;
    addr -= (mcos_uintptr_t)(MCOS_THR_NAME_MAX + WORD_SIZE_MASK) & ((mcos_uintptr_t)~((mcos_uintptr_t)WORD_SIZE_MASK));
    return addr;
#else   /* #if !MCOS_USE_PROCESS_MODEL */
    static _Bool is_first = true;
    static uint32_t adj = 0; /* byte size */
    uint32_t        size;    /* byte size */
    mcos_uintptr_t       top;

    if (tcb->migratable.process.ulstack.stksz != 0)
    {
        top = (mcos_uintptr_t)tcb->migratable.process.ulstack.stkaddr;
        size= tcb->migratable.process.ulstack.stksz;
    }
    else
    {
        top = (mcos_uintptr_t)tcb->migratable.stkaddr;
        size= tcb->migratable.stksz;
    }
    adj = get_name_size();

    return (top + size - adj);
#endif /* #if !MCOS_USE_PROCESS_MODEL */
}

 /*---------------------------------------------------------------------------
  set_running
     set running TCB to clscb
  Input     :   clscb   pointer to clscb
            :   running tcb in running state
  Output    :   none
  Return    :   none
  Note  :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE void set_running (
    clscb_t * const clscb,
    tcb_t * const running)
{
    clscb->running = running;
}

 /*---------------------------------------------------------------------------
  get_running
     return running TCB
  Input     :   clscb   pointer to clscb
  Output    :   none
  Return    :   running TCB
  Note  :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE tcb_t * get_running (
    const clscb_t * const clscb)
{
    return clscb->running;
}

/*
 * call mcos_ds_userhook_enter_idle
 */
extern void mcos_call_userhook_enter_idle_internal(mcos_uintptr_t param1, mcos_uintptr_t param2);

/*
 * call mcos_ds_userhook_enter_idle
 */
MCOS_INLINE void call_userhook_enter_idle(
    const tcb_t * const running,
    const tcb_t * const ready)
{
#if MCOS_CFG_DS_USERHOOK
    if ((running != MCOS_CLS_NULL) && (ready == MCOS_CLS_NULL))
    {
        mcos_hwl_call_change_mk_stack((mcos_uintptr_t)0L, (mcos_uintptr_t)0U, &mcos_call_userhook_enter_idle_internal);
    }
#endif
}

extern void mcos_call_userhook_leave_idle_internal(mcos_uintptr_t param1, mcos_uintptr_t param2);

/*
 * call mcos_ds_userhook_leave_idle
 */
MCOS_INLINE void call_userhook_leave_idle(
    const tcb_t * const running,
    const tcb_t * const ready)
{
#if MCOS_CFG_DS_USERHOOK
    if ((running == MCOS_CLS_NULL) && (ready != MCOS_CLS_NULL))
    {
        mcos_hwl_call_change_mk_stack((mcos_uintptr_t)ready->tid, (mcos_uintptr_t)0U, &mcos_call_userhook_leave_idle_internal);
    }
#endif
}

/*
 * Check if dispatch is disabled
 */
MCOS_INLINE mcos_bool_t dispatch_isDisabled(const clscb_t * const clscb);
MCOS_INLINE mcos_bool_t dispatch_isDisabled(
    const clscb_t * const clscb)
{
    return (mcos_bool_t)(((uint32_t)clscb->ctx != (uint32_t)CTX_NONE) ? (uint32_t)mcos_true : (uint32_t)mcos_false);
}

#endif /* #ifndef MCOS_MK_CLS_LOCAL_H */
