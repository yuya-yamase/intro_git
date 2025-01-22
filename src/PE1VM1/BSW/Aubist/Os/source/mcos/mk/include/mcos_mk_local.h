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
[ mcos_mk_local.h ] - eMCOS/MK local header
****************************************************************************/
#ifndef MCOS_MK_LOCAL_H
#define MCOS_MK_LOCAL_H

#if !MCOS_AUTOSAR
#include <bios/bios.h>
#else /* !MCOS_AUTOSAR */
#include <hal/hal.h>
#endif /* !MCOS_AUTOSAR */

#include "mcos_mk.h"

#include "mcos_hook_local.h"
#include "mcos_mk_mkcc.h"
#include "mcos_mk_cls.h"
#include "mcos_mk_clstm.h"
#include "mcos_mk_ds.h"
#include "mcos_mk_fmsg.h"
#include "mcos_mk_heap.h"
#include "mcos_mk_intm.h"
#include "mcos_mk_dsm.h"
#include "mcos_mk_ltm.h"
#include "mcos_mk_memm.h"
#include "mcos_mk_ns.h"
#include "mcos_mk_srvm.h"
#include "mcos_mk_sys.h"
#include "mcos_mk_tpm.h"
#include "mcos_mk_ts.h"
#include "mcos_mk_msgmgr.h"

#define MSG_FLAGS_MASK_PUBLIC       (MCOS_MSG_MASK_REQUEST | MCOS_MSG_MASK_REPLY | MCOS_MSG_MASK_FROM_ISR | MCOS_MSG_MASK_USER1 | MCOS_MSG_MASK_USER2 | MCOS_MSG_MASK_USER3 | MCOS_MSG_MASK_USER4)
#define MSG_FLAGS_MASK_PRIVATE      (MCOS_MSG_MASK_SYS_TK | MCOS_MSG_MASK_SYS_PT | MCOS_MSG_MASK_SYS_TIMER | MCOS_MSG_MASK_SYS_HEAP | MCOS_MSG_MASK_SYS_RRMSG | MCOS_MSG_MASK_SYS_SRVM)
#define MSG_FLAGS_MASK              (MSG_FLAGS_MASK_PUBLIC | MSG_FLAGS_MASK_PRIVATE)

#if !MCOS_AUTOSAR
#if MCOS_CFG_PARAM_CHECK
MCOS_INLINE mcos_bool_t is_valid_tid(const mcos_id_t tid);
#if MCOS_HWCL
MCOS_INLINE mcos_bool_t is_valid_hwcl_tid(mcos_id_t tid);
#endif /* MCOS_HWCL */
MCOS_INLINE mcos_bool_t is_valid_self_hwcl_tid(mcos_id_t tid);
MCOS_INLINE mcos_bool_t is_valid_lcid(const mcos_id_t lcid);
MCOS_INLINE mcos_bool_t is_valid_lcid_on_self_hwcl(const mcos_id_t lcid);
MCOS_INLINE mcos_bool_t is_valid_iid(const mcos_id_t iid);
#endif /* #if MCOS_CFG_PARAM_CHECK */
MCOS_INLINE void init_rep(msg_rep_t * const rep, const uint32_t type);
#endif /* !MCOS_AUTOSAR */

#if !MCOS_AUTOSAR
#if MCOS_CFG_PARAM_CHECK
/*---------------------------------------------------------------------------
  is_valid_tid
     Specified thread id is valid  or not (system-wide)
  Input     :   tid     thread id
  Output    :   none
  Return    :   0       is not valid
            :   !0      is valid
  Note  :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE mcos_bool_t is_valid_tid(
    const mcos_id_t tid)
{
    return (mcos_bool_t)((((int32_t)tid > (int32_t)0)
        && ((int32_t)tid <= ((int32_t)MCOS_CFG_GLB_HWCL_MAX * (int32_t)MCOS_TID_HWCL))) ?
            mcos_true : mcos_false);
}

/*---------------------------------------------------------------------------
  is_valid_hwcl_tid
     Specified thread id is valid or not (on the current HW cluster)
  Input     :   tid     thread id
  Output    :   none
  Return    :   0       is not valid
            :   !0      is valid
  Note  :   none
 ---------------------------------------------------------------------------*/
#if MCOS_HWCL
MCOS_INLINE mcos_bool_t
is_valid_hwcl_tid(mcos_id_t tid)
{
    return ((tid >= HWCL_BASE_TID) && (tid <= HWCL_END_MTID)
            && ((tid - 1) % MCOS_CFG_GLB_THR_PER_CORE_MAX < TCB_CNT));
}
#endif /* MCOS_HWCL */

/* is_valid_self_hwcl_tid */
MCOS_INLINE mcos_bool_t
is_valid_self_hwcl_tid(mcos_id_t tid)
{
    return (mcos_bool_t)(((((tid >= HWCL_BASE_TID_SELF) && (tid <= HWCL_END_TID_SELF))
            || ((tid >= HWCL_BASE_MTID_SELF) && (tid <= HWCL_END_MTID_SELF)))
            && ((tid - 1) % MCOS_CFG_GLB_THR_PER_CORE_MAX < TCB_CNT)) ?
                mcos_true : mcos_false);
}

/*---------------------------------------------------------------------------
  is_valid_lcid
     Specified logical core id is valid or not (system-wide)
  Input     :   lcid    logical core id
  Output    :   none
  Return    :   0       is not valid
            :   !0      is valid
  Note  :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE mcos_bool_t is_valid_lcid(
    const mcos_id_t lcid)
{
    return (mcos_bool_t)((((int32_t)lcid > (int32_t)0)
        && ((int32_t)lcid <= ((int32_t)MCOS_CFG_GLB_HWCL_MAX * (int32_t)MCOS_CFG_GLB_CORE_PER_HWCL_MAX))) ?
            mcos_true : mcos_false);
}

MCOS_INLINE mcos_bool_t is_valid_lcid_on_self_hwcl(
    const mcos_id_t lcid)
{
    return (mcos_bool_t)((((int32_t)lcid >= (int32_t)HWCL_BASE_LCID)
        && ((int32_t)lcid <= (int32_t)HWCL_END_LCID)) ?
            mcos_true : mcos_false);
}


MCOS_INLINE mcos_bool_t is_valid_iid(
    const mcos_id_t iid)
{
    bios_pic_info_t info;

    (void)bios_pic_about(&info);  /* Do not use the return value of this process. */
    return (mcos_bool_t)((((int32_t)iid >= (int32_t)info.minIntno) && ((int32_t)iid <= (int32_t)info.maxIntno)) ?
        mcos_true : mcos_false);
}

/* validate thread creation attributes */
mcos_bool_t mcos_threadattr_valid(
    const thread_attr_t *atr);

/* validate object name */
mcos_bool_t mcos_name_valid(
    const uint8_t *name);

mcos_bool_t mcos_name_thread_create_valid(
    const uint8_t *name);

#endif /* #if MCOS_CFG_PARAM_CHECK */
#endif /* !MCOS_AUTOSAR */

/* smallest plausible thread stack size */
#define THRD_STACK_MIN  (MCOS_CFG_THR_DEFAULT_STACKSIZE / 4)

#if !MCOS_AUTOSAR
/*
 * initialize reply
 * Input     :   rep         reply
 *           :   type        type
 * Output    :   none
 * Return    :   none
 * Note  :   none
 */
MCOS_INLINE void init_rep(
    msg_rep_t * const rep,
    const uint32_t type)
{
    mcos_util_set_type(rep, type);
    rep->id.tid = TID_SELF;
    rep->ret.ret = MCOS_EOK;
}

/* Utility routine to clear thread name */
void clear_name(
    uint32_t *ptr);

/* Utility macro to copy thread name */
void copy_name(
    uint32_t *dst,
    uint32_t *src);
#endif /* !MCOS_AUTOSAR */

/* master control block */
typedef struct mkcb_st
{
    /*
     * common
     *
     * Since mkcb_t* may be cast into mkcb_cmn_t *,
     * this member needs to assign to the top of mkcb.
     */
    mkcb_mk_cmn_t mk_cmn;
    /* control block size */
    uint32_t size;
    /* core local scheduler */
    clscb_t cls;
#if !MCOS_AUTOSAR
    /* interrupt manager */
    intmcb_t intm;
    /* distributed shared memory manager */
    dsmcb_t dsm;
    /* memory manager */
    memmcb_t memm;
    /* cluster manager */
    clstmcb_t clstm;
    /* message manager */
    msgmcb_t msgm;
    /* local time manager */
    ltmcb_t ltm;
    /* thread-pool control */
    tpmcb_t tpm;
#endif /* #if !MCOS_AUTOSAR */
    /* local debug support */
    dscb_local_t ds_local;
} mkcb_st_t;
#endif /* #ifndef MCOS_MK_LOCAL_H */
