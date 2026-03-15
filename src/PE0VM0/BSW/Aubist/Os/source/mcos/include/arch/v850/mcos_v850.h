/*
    Copyright(C) 2019 eSOL Co., Ltd. All rights reserved.

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
[ mcos_v850.h ] - MCOS ARCH for V850
****************************************************************************/
#ifndef MCOS_V850_H
#define MCOS_V850_H

#include <hal/hal.h>
#include "mcos_cmn.h"
#include "ar_mkmsg.h"
#include "mcos_mk_data.h"

/* stack size */
typedef unsigned int                        mcos_stack_t;

#define MCOS_STACK_SIZE(nbytes)                 ( (((8U + (uint32_t)(nbytes) - 1U) / 8U) * 8U) / sizeof(mcos_stack_t) )  /* 8 byte alignment */
#define MCOS_STACK_SIZE_IN_BYTES(nbytes)        ( (MCOS_STACK_SIZE(nbytes)) * sizeof(mcos_stack_t) )
#define MCOS_STACK_SIZE_WORDS_TO_BYTES(nwords)  ( (nwords) * sizeof(mcos_stack_t) )
#define MCOS_STACK_BOTTOM_PADDING               ( 0U )
#define MCOS_STACK_CUSHION_FOR_MPU              ( 48U )
#define MCOS_HEAP_ALIGN MCOS_HEAP_ALIGN4

/* highest BIOS cpu priority */
#define MCOS_INTM_BPRI_MAX      0x0U
/* lowest BIOS cpu priority */
#define MCOS_INTM_BPRI_MIN      0x3FU

#define MCOS_INTM_BPRI_SHIFT    0x0U

#if MCOS_AUTOSAR

/* mkmsg sync request size (bytes) */
#define MCOS_MKMSG_SYNC_REQUEST_SIZE    sizeof(ar_api_request_t)
/* mkmsg sync reply size (bytes) */
#define MCOS_MKMSG_SYNC_REPLY_SIZE      sizeof(ar_api_reply_t)

#else /* #if MCOS_AUTOSAR */

/* mkmsg sync request size (bytes) */
#define MCOS_MKMSG_SYNC_REQUEST_SIZE    0
/* mkmsg sync reply size (bytes) */
#define MCOS_MKMSG_SYNC_REPLY_SIZE      0

#endif /* #if MCOS_AUTOSAR */

MCOS_INLINE uint32_t mcos_hwl_coherent_load32(const volatile uint32_t * const addr);
MCOS_INLINE void mcos_hwl_coherent_store32(volatile uint32_t * const addr, const uint32_t value);
#if !MCOS_AUTOSAR
MCOS_INLINE mcos_uintptr_t mcos_hwl_coherent_loadptr(const mcos_uintptr_t * const addr);
#endif /* !MCOS_AUTOSAR */
MCOS_INLINE void mcos_hwl_coherent_storeptr(mcos_uintptr_t * const addr, const mcos_uintptr_t value);
MCOS_INLINE mkcb_t * mcos_mkcc_get_current_control_block(void);
MCOS_INLINE void mcos_hwl_cpu_enableAllInt(void);
MCOS_INLINE void mcos_hwl_cpu_disableAllInt(void);
MCOS_INLINE int32_t mcos_hwl_cpu_lockAllInt(void);
MCOS_INLINE void mcos_hwl_cpu_unlockAllInt(int32_t sr);
MCOS_INLINE mcos_bool_t mcos_hwl_cpu_is_lockAllInt(void);
MCOS_INLINE int32_t mcos_hwl_cpu_getCurrentIntPriority(void);
MCOS_INLINE int32_t mcos_hwl_cpu_getIntPriority(void);
MCOS_INLINE void mcos_hwl_cpu_setIntPriority(int32_t bpri);
MCOS_INLINE mcos_uintptr_t mcos_hwl_get_sp(void);
MCOS_INLINE void mcos_hwl_memory_barrier(void);

/* load 32 */
MCOS_INLINE uint32_t mcos_hwl_coherent_load32(
    const volatile uint32_t * const addr)
{
    return *addr;
}

/* store 32 */
MCOS_INLINE void mcos_hwl_coherent_store32(
    volatile uint32_t * const addr,
    const uint32_t value)
{
    *addr = value;
#pragma ghs nowarning 1546
    /*
     * confirmed that intended assembler codes are generated.
     */
    __asm__ volatile
    (
        "syncm\n"
    );
#pragma ghs endnowarning
}

#if !MCOS_AUTOSAR
/* load pointer */
MCOS_INLINE mcos_uintptr_t mcos_hwl_coherent_loadptr(
    const mcos_uintptr_t * const addr)
{
    return (mcos_uintptr_t)*addr;
}
#endif /* !MCOS_AUTOSAR */

/* store pointer */
MCOS_INLINE void mcos_hwl_coherent_storeptr(
    mcos_uintptr_t * const addr,
    const mcos_uintptr_t value)
{
    *addr = value;
#pragma ghs nowarning 1546
    /*
     * confirmed that intended assembler codes are generated.
     */
    __asm__ volatile
    (
        "syncm\n"
    );
#pragma ghs endnowarning
}

MCOS_INLINE mkcb_t * mcos_mkcc_get_current_control_block(void)
{
    void *mkcb;
    mcos_id_t lcid;

    lcid = mcos_get_lcid();
    mkcb = mcos_mkcb_ptr_table[(uint32_t)LCID2RCIDX_NC(lcid)];

    return (mkcb_t *)mkcb;
}


MCOS_INLINE mcos_uintptr_t mcos_hwl_get_sp(
    void)
{
    uint32_t stack_pointer;

#pragma ghs nowarning 1546
    /*
     * confirmed that intended assembler codes are generated.
     */
    __asm__ volatile
    (
        "mov     sp, %0"
        : "=&r"(stack_pointer)
        :
        : "cc", "memory"
    );
#pragma ghs endnowarning

    return (mcos_uintptr_t)stack_pointer;
}


/* inline bios_cpu_getIntPriority */
MCOS_INLINE int32_t mcos_hwl_cpu_getIntPriority(void)
{
    uint32_t bpri;

#pragma ghs nowarning 1546
    /*
     * confirmed that intended assembler codes are generated.
     */
    __asm__ volatile
    (
        "stsr    14, %0, 2\n    /* PMCTRL2 */"
        : "=&r"(bpri)
        :
        : "cc", "memory"
    );
#pragma ghs endnowarning

    return (int32_t)bpri;
}

/* inline bios_cpu_setIntPriority */
MCOS_INLINE void mcos_hwl_cpu_setIntPriority(int32_t bpri)
{
    uint32_t sr;

#pragma ghs nowarning 1546
    /*
     * confirmed that intended assembler codes are generated.
     */
    __asm__ volatile
    (
        "stsr    psw, %0, 0\n"
        "di\n"
        "ldsr    %1, 14, 2    /* PLMR */\n"
        "ldsr    %0, psw, 0\n"
        : "=&r"(sr)
        : "r"(bpri)
        : "cc", "memory"
    );
#pragma ghs endnowarning
}

#if MCOS_AUTOSAR

/* inline bios_cpu_enableAllInt */
MCOS_INLINE void mcos_hwl_cpu_enableAllInt(
    void)
{
    bios_cpu_enableAllInt();
}

/* inline bios_cpu_disableAllInt */
MCOS_INLINE void mcos_hwl_cpu_disableAllInt(
    void)
{
    bios_cpu_disableAllInt();
}

/* inline bios_cpu_lockAllInt */
MCOS_INLINE int32_t
mcos_hwl_cpu_lockAllInt(void)
{
    return bios_cpu_lockAllInt();
}

/* inline bios_cpu_unlockAllInt */
MCOS_INLINE void mcos_hwl_cpu_unlockAllInt(
    int32_t sr)
{
    bios_cpu_unlockAllInt(sr);
}

/* inline bios_cpu_is_lockAllInt */
MCOS_INLINE mcos_bool_t mcos_hwl_cpu_is_lockAllInt(
    void)
{
    hal_bool_t  lock = bios_cpu_is_lockAllInt();

    return (mcos_bool_t)((lock != hal_FALSE) ? mcos_true : mcos_false);
}

/* inline bios_cpu_getCurrentIntPriority */
MCOS_INLINE int32_t mcos_hwl_cpu_getCurrentIntPriority(
    void)
{
    uint32_t bpri;

#pragma ghs nowarning 1546
    /*
     * confirmed that intended assembler codes are generated.
     */
    __asm__ volatile
    (
        "stsr    psw, %0, 0\n"
        "shr     0x14, %0\n"
        "andi    0x3f, %0, %0\n"    /* EIMASK[5:0] */
        : "=&r"(bpri)
        :
        : "cc", "memory"
    );
#pragma ghs endnowarning

    return (int32_t)bpri;
}

#pragma ghs nowarning 1546

MCOS_INLINE  void mcos_hwl_memory_barrier(void) __attribute__((unused));
MCOS_INLINE  void mcos_hwl_memory_barrier(void)
{
#pragma ghs nowarning 1546
    /*
     * confirmed that intended assembler codes are generated.
     */
    __asm__ volatile
    (
        "syncm\n"
    );
#pragma ghs endnowarning
}
#pragma ghs endnowarning

#endif /* MCOS_AUTOSAR */

#endif /* #ifndef MCOS_V850_H */
