/*
    Copyright (C) 2013 eSOL Co.,Ltd. Tokyo, Japan

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
[ mcos_mkcc.h ] - MCOS micro kernel core component header
****************************************************************************/
#ifndef MCOS_MKCC_H
#define MCOS_MKCC_H

#include <mcos/mcos_syssrv.cfg>
#include "mcos_basic.h"

#if !BUILD_LIB
#define CONTROL_CORE_COUNT  MP_CONTROL_CORE_COUNT
#else /* #if !BUILD_LIB */
#define CONTROL_CORE_COUNT
#endif /* #if !BUILD_LIB */

/* Micro Kernel Control Block */
typedef struct mkcb_st mkcb_t;

/* Core Local Scheduler Control Block */
typedef struct clscb_st clscb_t;

/* autosar interrrupt Control Block */
typedef struct ar_intcb_st ar_intcb_t;

/* Shared Debug Support Control Block */
typedef struct dscb_shared dscb_shared_t;

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

#if (MCOS_CFG_DS_USED_MEMORY_ENABLE || !MCOS_AUTOSAR)
/* get pointer to micro-kernel control block by lcid */
const mkcb_t * mcos_mkcc_get_control_block (
    mcos_id_t lcid);
#endif /* (MCOS_CFG_DS_USED_MEMORY_ENABLE || !MCOS_AUTOSAR) */

/* Get the local RAM size which is used by kernel */
uint32_t mcos_mkcc_get_used_lmemsize(void);


#if !MCOS_AUTOSAR
/* get heap server thread ID */
mcos_id_t mcos_mkcc_heap_srvr_tid(
    int32_t index);

/* get name server thread ID */
mcos_id_t mcos_mkcc_ns_srvr_tid(
    int32_t index);
#endif /* #if !MCOS_AUTOSAR */

#if (MCOS_HWCL != 0U)
#if MCOS_CFG_GLB_CLMM_ENABLE
/* get CLMM server thread ID */
mcos_id_t mcos_mkcc_clmm_srvr_tid(
    mcos_id_t lcid);
#endif /* #if MCOS_CFG_GLB_CLMM_ENABLE */
#endif /* #if (MCOS_HWCL != 0U) */

#if !MCOS_AUTOSAR
/* get TS thread ID */
mcos_id_t mcos_mkcc_ts_tid(
    const mkcb_t *mkcb);

/* get initial thread thread ID */
mcos_id_t mcos_mkcc_initial_tid(
    const mkcb_t *mkcb);
#endif /* #if !MCOS_AUTOSAR */

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

/* Micro Kernel Control Blocks common */
typedef struct mkcb_cmn_st
{
    /*
     *  Because it is also used on the assembler code,
     *    be careful about changing the offset
     */

    /* pointer of micro kernel sp */
    mcos_uintptr_t *psp;
    /* interrupt nest count */
    uint16_t inest;
    /* current core id */
    mcos_id_t lcid;
    /* core local scheduler */
    clscb_t * cls;

    mcos_uintptr_t  stack_top;       /* USED ASSEMBLER */
    mcos_uintptr_t  stack_bottom;    /* USED ASSEMBLER */

} mkcb_cmn_t;

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/*
* Micro-Kernel control block(common area)
 */
extern mkcb_cmn_t * const mcos_mkcb_cmn_ptr_table[CONTROL_CORE_COUNT];

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

MCOS_INLINE mcos_uintptr_t * mcos_mkcc_psp_get (const mkcb_t * const mkcb);
MCOS_INLINE void mcos_mkcc_inest_increment(const mkcb_t * const mkcb_writable);
MCOS_INLINE uint16_t mcos_mkcc_inest_get(const mkcb_t * const mkcb);
MCOS_INLINE void mcos_mkcc_inest_set(const mkcb_t * const mkcb_writable,const uint16_t count);
MCOS_INLINE mcos_id_t mcos_mkcc_get_lcid(const mkcb_t * const mkcb);
MCOS_INLINE clscb_t * mcos_mkcc_get_clscb(const mkcb_t * const mkcb);
MCOS_INLINE mcos_uintptr_t mcos_mkcc_get_stack_top(const mkcb_t * const mkcb);
MCOS_INLINE mcos_uintptr_t mcos_mkcc_get_stack_bottom(const mkcb_t * const mkcb);


/* get pointer of micro kernel sp */
MCOS_INLINE mcos_uintptr_t * mcos_mkcc_psp_get (
    const mkcb_t * const mkcb)
{
    const hal_uint_t cpuno = (hal_uint_t)hal_cpu_getCoreNumber();
    const mkcb_cmn_t * const mkcb_cmn = mcos_mkcb_cmn_ptr_table[cpuno];
    (void)mkcb;
    return mkcb_cmn->psp; 
}

/* increment interrupt nest count */
MCOS_INLINE void mcos_mkcc_inest_increment (
    const mkcb_t * const mkcb_writable)
{
    const hal_uint_t cpuno = (hal_uint_t)hal_cpu_getCoreNumber();
    mkcb_cmn_t * const mkcb_cmn = mcos_mkcb_cmn_ptr_table[cpuno];
    (void)mkcb_writable;
    mkcb_cmn->inest = (uint16_t)((uint32_t)mkcb_cmn->inest + (uint32_t)1);
}

/* get interrupt nest count */
MCOS_INLINE uint16_t mcos_mkcc_inest_get (
    const mkcb_t * const mkcb)
{
    const hal_uint_t cpuno = (hal_uint_t)hal_cpu_getCoreNumber();
    const mkcb_cmn_t * const mkcb_cmn = mcos_mkcb_cmn_ptr_table[cpuno];
    (void)mkcb;
    return mkcb_cmn->inest;
}

/* set interrupt nest count */
MCOS_INLINE void mcos_mkcc_inest_set (
    const mkcb_t * const mkcb_writable,
    const uint16_t count)
{
    const hal_uint_t cpuno = (hal_uint_t)hal_cpu_getCoreNumber();
    mkcb_cmn_t * const mkcb_cmn = mcos_mkcb_cmn_ptr_table[cpuno];
    (void)mkcb_writable;
    mkcb_cmn->inest = count;
}

/* Get core id */
MCOS_INLINE mcos_id_t mcos_mkcc_get_lcid (
    const mkcb_t * const mkcb)
{
    const hal_uint_t cpuno = (hal_uint_t)hal_cpu_getCoreNumber();
    (void)mkcb;
    return (mcos_id_t)CPUNO2LCID(cpuno);
}

/* Get pointer to core local scheduler control block */
MCOS_INLINE clscb_t * mcos_mkcc_get_clscb (
    const mkcb_t * const mkcb)
{
    const hal_uint_t cpuno = (hal_uint_t)hal_cpu_getCoreNumber();
    const mkcb_cmn_t * const mkcb_cmn = mcos_mkcb_cmn_ptr_table[cpuno];
    (void)mkcb;
    return mkcb_cmn->cls;
}

/* Get stack top */
MCOS_INLINE mcos_uintptr_t mcos_mkcc_get_stack_top (
    const mkcb_t * const mkcb)
{
    const hal_uint_t cpuno = (hal_uint_t)hal_cpu_getCoreNumber();
    const mkcb_cmn_t * const mkcb_cmn = mcos_mkcb_cmn_ptr_table[cpuno];
    (void)mkcb;
    return mkcb_cmn->stack_top;
}

/* Get stack bottom */
MCOS_INLINE mcos_uintptr_t mcos_mkcc_get_stack_bottom (
    const mkcb_t * const mkcb)
{
    const hal_uint_t cpuno = (hal_uint_t)hal_cpu_getCoreNumber();
    const mkcb_cmn_t * const mkcb_cmn = mcos_mkcb_cmn_ptr_table[cpuno];
    (void)mkcb;
    return mkcb_cmn->stack_bottom;
}

#endif /* #ifndef MCOS_MKCC_H */
