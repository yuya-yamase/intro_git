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
[ mcos_mk_mkcc.h ] - eMCOS/MK micro-kernel core component local header
****************************************************************************/
#ifndef MCOS_MK_MKCC_H
#define MCOS_MK_MKCC_H

#include <mcos/system.cfg>
#include "mcos_mk.h"

/* Cluster Manager Control Block */
typedef struct clstmcb_st clstmcb_t;

/* Hardware layer Control Block */
typedef struct hwlcb_st hwlcb_t;

/* Interrupt Manager Control Block */
typedef struct intmcb_st intmcb_t;

/* Distributed Shared Memory Control Block */
typedef struct dsmcb_st dsmcb_t;

#if !MCOS_AUTOSAR
/* Memory Manager Control Block */
typedef struct memmcb_st memmcb_t;
#endif /* #if !MCOS_AUTOSAR */

/* Message Manager Control Block */
typedef struct msgmcb_st msgmcb_t;

/* Local Time Manager Control Block */
typedef struct ltmcb_st ltmcb_t;

/* Thread-pool control block */
typedef struct tpmcb_st tpmcb_t;

/* Local Debug Support Control Block */
typedef struct dscb_local dscb_local_t;

/* Heap Manager  Control Block */
typedef struct heapcb_st heapcb_t;


/* Pointer table to Micro Kernel Control Blocks  */
typedef struct mkcb_ptbl
{
    /* hardware layer */
    hwlcb_t * hwl;
#if !MCOS_AUTOSAR
    /* interrupt manager */
    intmcb_t * intm;
    /* distributed shared memory */
    dsmcb_t * dsm;
    /* memory manager */
    memmcb_t * memm;
    /* cluster manager */
    clstmcb_t * clstm;
    /* message manager */
    msgmcb_t * msgm;
    /* local time manager */
    ltmcb_t * ltm;
    /* thread-pool control */
    tpmcb_t * tpm;
    /* heap manager */
    heapcb_t * heap;
#endif /* #if !MCOS_AUTOSAR */
    /* local debug support */
    dscb_local_t * ds_local;
    /* shared debug support */
    dscb_shared_t * ds_shared;
} mkcb_ptbl_t;

/* Micro Kernel Control Blocks common */
typedef struct mkcb_mk_cmn
{
    /* Micro Kernel Control Blocks common */
    mkcb_cmn_t cmn;
    /* Pointer table */
    mkcb_ptbl_t ptbl;
} mkcb_mk_cmn_t;

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

/* micro-kernel core component interface functions */
const mkcb_t * mcos_mkcc_init(
    const mcos_id_t lcid,
    void * const ptr);

#if !MCOS_AUTOSAR
void mcos_mkcc_thread_return(void);

int32_t mcos_mkcc_get_control_block_size(void);
mcos_bool_t mcos_mkcc_boot_system_threads(const mkcb_t * mkcb);
void mcos_mkcc_boot_init_thread(mcos_id_t lcid);
mcos_id_t mcos_mkcc_threadpool_srvr_tid(mcos_id_t lcid);
#endif /* #if !MCOS_AUTOSAR */

#if MCOS_PT_API || MCOS_USE_PROCESS_MODEL
void mcos_mkcc_initialize_dbgmkcb(const mkcb_t *mkcb);
#endif /* MCOS_PT_API || MCOS_USE_PROCESS_MODEL */

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

MCOS_INLINE hwlcb_t * mcos_mkcc_get_hwlcb(const mkcb_t * const mkcb);
#if !MCOS_AUTOSAR
MCOS_INLINE intmcb_t * mcos_mkcc_get_intmcb(const mkcb_t * const mkcb);
MCOS_INLINE dsmcb_t * mcos_mkcc_get_dsmcb(const mkcb_t * const mkcb);
#endif /* #if !MCOS_AUTOSAR */
MCOS_INLINE dscb_local_t * mcos_mkcc_get_dscb_local(const mkcb_t * const mkcb);
MCOS_INLINE dscb_shared_t * mcos_mkcc_get_dscb_shared(const mkcb_t * const mkcb);

/* Get pointer to hardware layer control block */
MCOS_INLINE hwlcb_t * mcos_mkcc_get_hwlcb(
    const mkcb_t * const mkcb)
{
    /*
     * In order to avoid casting between different pointers, it uses a variable
     * of void pointer.(MISRA rule)
     * Because mkcb_mk_cmn_t is the header of mkcb_t, it is possible to refer
     * to cast value each other.
     */

    const void * const p_mkcb_mk_cmn = (const void *)mkcb;

    return ((const mkcb_mk_cmn_t *)p_mkcb_mk_cmn)->ptbl.hwl;
}

/* Get pointer to local debug support control block */
MCOS_INLINE dscb_local_t * mcos_mkcc_get_dscb_local(
    const mkcb_t * const mkcb)
{
    /*
     * In order to avoid casting between different pointers, it uses a variable
     * of void pointer.(MISRA rule)
     * Because mkcb_mk_cmn_t is the header of mkcb_t, it is possible to refer
     * to cast value each other.
     */

    const void * const p_mkcb_mk_cmn = (const void *)mkcb;

    return ((const mkcb_mk_cmn_t *)p_mkcb_mk_cmn)->ptbl.ds_local;
}

/* Get pointer to shared debug support control block */
MCOS_INLINE dscb_shared_t * mcos_mkcc_get_dscb_shared(
    const mkcb_t * const mkcb)
{
    /*
     * In order to avoid casting between different pointers, it uses a variable
     * of void pointer.(MISRA rule)
     * Because mkcb_mk_cmn_t is the header of mkcb_t, it is possible to refer
     * to cast value each other.
     */

    const void * const p_mkcb_mk_cmn = (const void *)mkcb;

    return ((const mkcb_mk_cmn_t *)p_mkcb_mk_cmn)->ptbl.ds_shared;
}

#if !MCOS_AUTOSAR
/* Get pointer to interrupt manager control block */
MCOS_INLINE intmcb_t * mcos_mkcc_get_intmcb(
    const mkcb_t * const mkcb)
{
    /*
     * In order to avoid casting between different pointers, it uses a variable
     * of void pointer.(MISRA rule)
     * Because mkcb_mk_cmn_t is the header of mkcb_t, it is possible to refer
     * to cast value each other.
     */

    const void * const p_mkcb_mk_cmn = (const void *)mkcb;

    return ((const mkcb_mk_cmn_t *)p_mkcb_mk_cmn)->ptbl.intm;
}

/* Get pointer to distributed shared memory control block */
MCOS_INLINE dsmcb_t * mcos_mkcc_get_dsmcb(
    const mkcb_t * const mkcb)
{
    /*
     * In order to avoid casting between different pointers, it uses a variable
     * of void pointer.(MISRA rule)
     * Because mkcb_mk_cmn_t is the header of mkcb_t, it is possible to refer
     * to cast value each other.
     */

    const void * const p_mkcb_mk_cmn = (const void *)mkcb;

    return ((const mkcb_mk_cmn_t *)p_mkcb_mk_cmn)->ptbl.dsm;
}

/* Get pointer to memory manager control block */
MCOS_INLINE memmcb_t * mcos_mkcc_get_memmcb (
    const mkcb_t * mkcb)
{
    /*
     * In order to avoid casting between different pointers, it uses a variable
     * of void pointer.(MISRA rule)
     * Because mkcb_mk_cmn_t is the header of mkcb_t, it is possible to refer
     * to cast value each other.
     */

    const void * p_mkcb_mk_cmn;

    p_mkcb_mk_cmn = (const void *)mkcb;

    return ((const mkcb_mk_cmn_t *)p_mkcb_mk_cmn)->ptbl.memm;
}

/* Get pointer to cluster manager control block */
MCOS_INLINE clstmcb_t * mcos_mkcc_get_clstmcb (
    const mkcb_t * mkcb)
{
    /*
     * In order to avoid casting between different pointers, it uses a variable
     * of void pointer.(MISRA rule)
     * Because mkcb_mk_cmn_t is the header of mkcb_t, it is possible to refer
     * to cast value each other.
     */

    const void * p_mkcb_mk_cmn;

    p_mkcb_mk_cmn = (const void *)mkcb;

    return ((const mkcb_mk_cmn_t *)p_mkcb_mk_cmn)->ptbl.clstm;
}

/* Get pointer to message manager control block */
MCOS_INLINE msgmcb_t * mcos_mkcc_get_msgmcb (
    const mkcb_t * mkcb)
{
    /*
     * In order to avoid casting between different pointers, it uses a variable
     * of void pointer.(MISRA rule)
     * Because mkcb_mk_cmn_t is the header of mkcb_t, it is possible to refer
     * to cast value each other.
     */

    const void * p_mkcb_mk_cmn;

    p_mkcb_mk_cmn = (const void *)mkcb;

    return ((const mkcb_mk_cmn_t *)p_mkcb_mk_cmn)->ptbl.msgm;
}

/* Get pointer to local time manager control block */
MCOS_INLINE ltmcb_t * mcos_mkcc_get_ltmcb (
    const mkcb_t * mkcb)
{
    /*
     * In order to avoid casting between different pointers, it uses a variable
     * of void pointer.(MISRA rule)
     * Because mkcb_mk_cmn_t is the header of mkcb_t, it is possible to refer
     * to cast value each other.
     */

    const void * p_mkcb_mk_cmn;

    p_mkcb_mk_cmn = (const void *)mkcb;

    return ((const mkcb_mk_cmn_t *)p_mkcb_mk_cmn)->ptbl.ltm;
}

/* Get pointer to thread-pool control block */
MCOS_INLINE tpmcb_t * mcos_mkcc_get_tpmcb (
    const mkcb_t * mkcb)
{
    /*
     * In order to avoid casting between different pointers, it uses a variable
     * of void pointer.(MISRA rule)
     * Because mkcb_mk_cmn_t is the header of mkcb_t, it is possible to refer
     * to cast value each other.
     */

    const void * p_mkcb_mk_cmn;

    p_mkcb_mk_cmn = (const void *)mkcb;

    return ((const mkcb_mk_cmn_t *)p_mkcb_mk_cmn)->ptbl.tpm;
}

/* Get pointer to heap manager control block */
MCOS_INLINE heapcb_t * mcos_mkcc_get_heapcb (
    const mkcb_t * mkcb)
{
    /*
     * In order to avoid casting between different pointers, it uses a variable
     * of void pointer.(MISRA rule)
     * Because mkcb_mk_cmn_t is the header of mkcb_t, it is possible to refer
     * to cast value each other.
     */

    const void * p_mkcb_mk_cmn;

    p_mkcb_mk_cmn = (const void *)mkcb;

    return ((const mkcb_mk_cmn_t *)p_mkcb_mk_cmn)->ptbl.heap;
}
#endif /* #if !MCOS_AUTOSAR */

/* The following functions are implemented by hardware layer */

void mcos_mkcc_set_current_control_block(const mkcb_t *mkcb);

#ifdef MCOS_USE_PTAPI
void  mcos_mkcc_set_current_ext_control_block(const void *extcb);
void *mcos_mkcc_get_current_ext_control_block(void);
#endif /* #ifdef MCOS_USE_PTAPI */

#endif /* #ifndef MCOS_MK_MKCC_H */
