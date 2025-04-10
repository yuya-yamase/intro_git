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
[ mcos_mk_cls.h ] - eMCOS/MK core local scheduler local header
****************************************************************************/
#ifndef MCOS_MK_CLS_H
#define MCOS_MK_CLS_H

#include <mcos/system.cfg>
#include <mcos/mcos_hwcl.cfg>
#include "mcos_mk.h"

#if !MCOS_AUTOSAR

/* waiting resolve information */
typedef struct wri_st wri_t;

struct wri_st
{
    int32_t tid;        /* destination thread id */
    msg_t *pend;        /* pending messages */
    wri_t *next;        /* queue */
};

/* control block */
struct msgmcb_st
{
    wri_t *wait;                /* waiting resolve info */
    wri_t *freewri;             /* free info */
    uint16_t mrc[TCB_MAX];      /* message resolver cache (key:tid, value:lcid) */
#if MCOS_HWCL
    uint32_t mrc_hwcl_data[MCOS_CFG_GLB_HWCL_MAX];
    uint32_t mrc_hwcl_index;
#endif /* MCOS_HWCL */
    wri_t ibuf[MCOS_CFG_MSG_RESOLVE_COUNT_MAX];   /* info buffer */
#if MCOS_MSGPROF
    mcos_id_t lts_tid;          /* leaf thread scheduler's thread id */
#endif /* MCOS_MSGPROF */
};

#endif /*#if !MCOS_AUTOSAR */

#if !MCOS_AUTOSAR
MCOS_INLINE void dispatch_disable(clscb_t *clscb);
MCOS_INLINE void dispatch_enable(clscb_t *clscb);
MCOS_INLINE uint8_t dispatch_lock(clscb_t *clscb);
MCOS_INLINE void dispatch_unlock(clscb_t *clscb, uint8_t dsp);
#endif /* !MCOS_AUTOSAR */

void mcos_cls_init(const mkcb_t * const mkcb);
#if !MCOS_AUTOSAR
mcos_uintptr_t mcos_cls_interrupt_enter(const mkcb_t *mkcb, mcos_id_t iid, mcos_uintptr_t sp);
MCOS_INLINE uint8_t mcos_cls_dispatch_lock(const mkcb_t * const mkcb);
MCOS_INLINE void mcos_cls_dispatch_unlock(const mkcb_t * const mkcb, uint8_t dsp);
#endif /* !MCOS_AUTOSAR */
void mcos_cls_dispatch_thread(clscb_t * const clscb);
#if !MCOS_AUTOSAR
void mcos_cls_dispatch_int(const mkcb_t * const mkcb);
#endif /* !MCOS_AUTOSAR */
MCOS_INLINE void mcos_cls_dispatch(const mkcb_t * const mkcb);
mcos_uintptr_t mcos_cls_dispatch_preprocessing(
    const mkcb_t * const mkcb,
    const mcos_bool_t hasRequest,
    const uint32_t type);

#if MCOS_AUTOSAR
void mcos_hwl_call_change_mk_stack(mcos_uintptr_t arg1, mcos_uintptr_t arg2,
    void (*entry)(mcos_uintptr_t param1, mcos_uintptr_t param2));
void mcos_hwl_call_change_mk_stack_for_prohk(mcos_uintptr_t arg1, mcos_uintptr_t arg2,
    ProtectionReturnType (*entry)(mcos_uintptr_t param1, mcos_uintptr_t param2));
#else /* MCOS_AUTOSAR */
void mcos_hwl_call_change_stack(mcos_uintptr_t arg1, mcos_uintptr_t arg2, void *entry, void *sp);
#endif /* !MCOS_AUTOSAR */
MCOS_INLINE void mcos_cls_callfunc_with_stack(
    mcos_uintptr_t arg1,
    mcos_uintptr_t arg2,
    void *entry,
    void *sp
    );

#if !MCOS_AUTOSAR
mcos_id_t mcos_cls_get_currenttid_noblk(const mkcb_t *mkcb);
mcos_id_t mcos_cls_get_currenttpri_noblk(const mkcb_t *mkcb);
#endif /* !MCOS_AUTOSAR */
void mcos_cls_mkmsg_callback (
    const mkcb_t * const mkcb,
    volatile const void * const request,
    const uint32_t request_size);
#if !MCOS_AUTOSAR
void mcos_cls_check_stack (
    const mkcb_t * const mkcb,
    const mcos_uintptr_t sp);
void *mcos_cls_get_errno_addr(const mkcb_t *mkcb);
#endif /* !MCOS_AUTOSAR */
#if MCOS_USE_PROCESS_MODEL
void * mcos_cls_get_extcb(const tcb_t *tcb);
#endif /* #if MCOS_USE_PROCESS_MODEL */
#if !MCOS_AUTOSAR
uint8_t mcos_cls_is_thread_context(void);

mcos_id_t mcos_cls_get_self_id_name(uint32_t *dst);
mcos_char_t *mcos_cls_get_thread_name(tcb_t *tcb);
uint32_t mcos_cls_get_currentattr(void);
void mcos_cls_add_pending_fmsg(const mkcb_t *mkcb, mcos_id_t tid, msg_t *msg);
#endif /* !MCOS_AUTOSAR */

#if MCOS_AUTOSAR && (AR_OS_USE_STACKMONITORING == STD_ON)
void mcos_check_running_thread_stack(mkcb_t *mkcb, mcos_uintptr_t sp);
#endif /* #if MCOS_AUTOSAR && (AR_OS_USE_STACKMONITORING == STD_ON) */


void mcos_cls_context_switch_int(
    const mkcb_t * const mkcb
#if MCOS_AUTOSAR
    , uint32_t type
#endif
);

#if !MCOS_AUTOSAR
/* message manager interface functions */
void mcos_msgm_init(const mkcb_t * mkcb);

/* micro-kernel utility functions */
void mcos_util_pend_copy(msg_t *msg, uint32_t *msgdata, uint32_t msgsz);


mcos_erid_t mcos_thread_create_internal(const mcos_thr_attr_t *attr, void (*entry)(uint32_t stacd, mcos_uintptr_t exinf), mcos_uintptr_t exinf);
mcos_er_t mcos_thread_exit_internal(uint8_t mode);
mcos_er_t mcos_thread_sleep_internal(void);
mcos_er_t mcos_thread_delay_internal(mcos_reltime_t delay_time);

mcos_er_t mcos_rrmessage_send_internal(
    mcos_id_t tid,
    uint64_t requestinf,
    const void *request,
    uint32_t requestsz,
    uint64_t *replyinf,
    void *reply,
    uint32_t replysz);
mcos_er_t mcos_rrmessage_receive_internal(mcos_rrmsg_recv_t *recv);
mcos_er_t mcos_rrmessage_reply_internal(
    uint64_t replyinf,
    uint32_t replysz,
    const mcos_rrmsg_recv_t *recv);

mcos_er_t mcos_core_get_info_internal(mcos_id_t lcid, mcos_core_info_t *core_info);

mcos_er_t mcos_thread_get_name_internal(mcos_id_t tid, mcos_char_t *name, int32_t len);
mcos_er_t mcos_thread_get_info_internal(mcos_id_t tid, mcos_thr_info_t *thread_info);
#if MCOS_USE_PROCESS_MODEL
mcos_er_t mcos_thread_get_info_ex_internal(mcos_id_t tid, mcos_thr_info_ex_t *thread_info);
#endif /* #if MCOS_USE_PROCESS_MODEL */
mcos_er_t mcos_thread_wakeup_internal(const mcos_id_t tid);

mcos_er_t mcos_message_control_internal(const mcos_id_t tid, const uint32_t command);

#endif /* #if !MCOS_AUTOSAR */

 /*---------------------------------------------------------------------------
  mcos_cls_dispatch
     Call dispatcher and dispatch a thread.
  Input     :   mkcb   microkernel control block
  Output    :   none
  Return    :   none
  Note      :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE void mcos_cls_dispatch(
    const mkcb_t * const mkcb)
{
    clscb_t *clscb;

    clscb = mcos_mkcc_get_clscb(mkcb);

    mcos_cls_dispatch_thread(clscb);
}

#if !MCOS_AUTOSAR
/*
 * Disable dispatch.
 */
MCOS_INLINE void dispatch_disable(
    clscb_t *clscb)
{
    clscb->ctx |= (uint8_t)CTX_DISDSP;
}

/*
 * Enable dispatch.
 */
MCOS_INLINE void dispatch_enable(
    clscb_t *clscb)
{
    clscb->ctx &= (uint8_t)~CTX_DISDSP;
}

/*
 * Lock dispatch.
 */
MCOS_INLINE uint8_t dispatch_lock(
    clscb_t *clscb)
{
    uint8_t dsp;

    dsp = clscb->ctx & (uint8_t)CTX_DISDSP;
    if (dsp == (uint8_t)0)
    {
        dispatch_disable(clscb);
    }
    return dsp;
}

/*
 * Unlock dispatch.
 */
MCOS_INLINE void dispatch_unlock(
    clscb_t *clscb,
    uint8_t dsp)
{
    if (dsp == (uint8_t)0)
    {
        dispatch_enable(clscb);
    }
}

 /*---------------------------------------------------------------------------
  mcos_cls_dispatch_lock
     Lock dispatch.
  Input     :   mkcb        Microkernel control block
  Output    :   none
  Return    :   0     : Locked successfully.
                other : Lock failed.
  Note      :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE uint8_t mcos_cls_dispatch_lock(
    const mkcb_t * const mkcb)
{
    uint8_t dsp;
    clscb_t *clscb;

    clscb = mcos_mkcc_get_clscb(mkcb);

    dsp = dispatch_lock(clscb);

    return dsp;
}

 /*---------------------------------------------------------------------------
  mcos_cls_dispatch_unlock
     Unlock dispatch if dsp == 0.
  Input     :   mkcb        Microkernel control block
                dsp         Lock info
  Output    :   none
  Return    :   none
  Note      :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE void mcos_cls_dispatch_unlock(
    const mkcb_t * const mkcb,
    uint8_t dsp)
{
    clscb_t *clscb;

    clscb = mcos_mkcc_get_clscb(mkcb);

    dispatch_unlock(clscb, dsp);
}

 /*---------------------------------------------------------------------------
  mcos_cls_callfunc_with_stack
     Call the function 'entry' on the stack specified by 'sp'.
  Input     :   arg1    1st argument for the function 'entry'.
                arg2    2nd argument for the function 'entry'.
                entry   Entry address of the function to call.
                sp      Pointer to the stack the function 'entry' runs on.
  Output    :   none
  Return    :   none
  Note      :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE void mcos_cls_callfunc_with_stack(
    mcos_uintptr_t arg1,
    mcos_uintptr_t arg2,
    void *entry,
    void *sp
    )
{
    mcos_hwl_call_change_stack(
        (mcos_uintptr_t)arg1, (mcos_uintptr_t)arg2, (void *)entry, (void *)sp);
}
#endif /* !MCOS_AUTOSAR */

#endif /* #ifndef MCOS_MK_CLS_H */
