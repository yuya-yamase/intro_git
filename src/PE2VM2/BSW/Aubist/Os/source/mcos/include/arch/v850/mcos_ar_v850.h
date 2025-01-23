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
[ mcos_ar_v850.h ] - MCOS AUTOSAR ARCH for V850
****************************************************************************/
#ifndef MCOS_AR_V850_H
#define MCOS_AR_V850_H

#include "hal/cpu/v850/v850_cpp_impl.h"
#include "hal/cpu/v850/hal/hal_v850_impl.h"
#include <mcos/mcos_ar_switch.h>

struct hal_v850_exc_frame_st
{
    uint32  plmr;
    uint32  ctpsw;
    uint32  ctpc;
    uint32  fpsr;
    uint32  eipsw;
    uint32  eipc;
    uint32  r19;
    uint32  r18;
    uint32  r17;
    uint32  r16;
    uint32  r15;
    uint32  r14;
    uint32  r13;
    uint32  r12;
    uint32  r11;
    uint32  r10;
    uint32  r9;
    uint32  r8;
    uint32  r7;
    uint32  r6;
    uint32  lp;
    uint32  r30;
    uint32  r1;
};

typedef struct hal_v850_exc_frame_st hal_v850_exc_frame_t;

struct hal_v850_exc_info_st
{
    hal_v850_exc_frame_t  stackframe;
};

typedef struct hal_v850_exc_info_st hal_v850_exc_info_t;

#define AR_OS_HAS_OSAPCB_ARCHCB  STD_OFF

typedef struct {
    uint32_t    check_stack_addr;       /* stack lower address for sp check (USED ASSEMBLER!) */
    uint32_t    check_stack_size;       /* stack size for sp check (USED ASSEMBLER!) */
    uint32_t    interrupt_management_counter; /* interrupt management (nest) counter (USED ASSEMBLER!) */
} ar_osarchcb_t;


/*---------------------------------------------------------------------------
  ar_service_call_fast_trusted_function

  Input     :   arg1    first data argument of SVC
            :   p_arg2  second pointer argument of SVC
  Output    :   return value of SVC
  Return    :
  Note      :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE sint32 ar_service_call_fast_trusted_function(sint32 arg1, void *p_arg2) __attribute__((unused));
MCOS_INLINE sint32 ar_service_call_fast_trusted_function(sint32 arg1, void *p_arg2)
{
#pragma ghs nowarning 1546
    /*
     * confirmed that intended assembler codes are generated.
     */
    sint32 ret;

    __asm__ volatile
    (
        "\n\tmov  %1, r6"
        "\n\tmov  %2, r7"
#if MCOS_CFG_DS_TRACE_ENABLE
        "\n\tmov  lp, r8"
#endif
        "\n\tsyscall 2"
        "\n\tmov  r10, %0"
        :"=r"(ret)
        :"r"(arg1),"r"(p_arg2)
        :"cc", "memory", "r1", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15", "r16", "ep", "lp"
    );
#pragma ghs endnowarning

    return ret;

}


/*---------------------------------------------------------------------------
  ar_service_call_d_0
    run syscall with no arguments
  Input     :   svc_id  SVC ID
  Output    :   return value of SVC
  Return    :
  Note      :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE sint32 ar_service_call_d_0(sint32 svc_id) __attribute__((unused));
MCOS_INLINE sint32 ar_service_call_d_0(sint32 svc_id)
{
#pragma ghs nowarning 1546
    /*
     * confirmed that intended assembler codes are generated.
     */
    sint32 ret;

    __asm__ volatile
    (
        "\n\tmov  %1, r10"
#if MCOS_CFG_DS_TRACE_ENABLE
        "\n\tmov  lp, r6"
#endif
        "\n\tsyscall 1"
        "\n\tmov  r10, %0"
        :"=r"(ret)
        :"r"(svc_id)
        :"cc", "memory", "r1", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15", "r16", "r17", "r18", "ep", "lp"
    );
#pragma ghs endnowarning

    return ret;
}


/*---------------------------------------------------------------------------
  ar_service_call_d_d
    run syscall with 1 argument
  Input     :   arg1    first data arguments of SVC
            :   svc_id  SVC ID
  Output    :   return value of SVC
  Return    :
  Note      :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE sint32 ar_service_call_d_d(sint32 arg1, sint32 svc_id) __attribute__((unused));
MCOS_INLINE sint32 ar_service_call_d_d(sint32 arg1, sint32 svc_id)
{
#pragma ghs nowarning 1546
    /*
     * confirmed that intended assembler codes are generated.
     */
    sint32 ret;

    __asm__ volatile
    (
        "\n\tmov  %1, r10"
        "\n\tmov  %2, r6"
#if MCOS_CFG_DS_TRACE_ENABLE
        "\n\tmov  lp, r7"
#endif
        "\n\tsyscall 1"
        "\n\tmov  r10, %0"
        :"=r"(ret)
        :"r"(svc_id),"r"(arg1)
        :"cc", "memory", "r1", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15", "r16", "r17", "ep", "lp"
    );
#pragma ghs endnowarning

    return ret;
}


/*---------------------------------------------------------------------------
  ar_service_call_d_dd
    run syscall with 2 arguments
  Input     :   arg1    first data arguments of SVC
            :   arg2    second data argument of SVC
            :   svc_id  SVC ID
  Output    :   return value of SVC
  Return    :
  Note      :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE sint32 ar_service_call_d_dd(sint32 arg1, sint32 arg2, sint32 svc_id) __attribute__((unused));
MCOS_INLINE sint32 ar_service_call_d_dd(sint32 arg1, sint32 arg2, sint32 svc_id)
{
#pragma ghs nowarning 1546
    /*
     * confirmed that intended assembler codes are generated.
     */
    sint32 ret;

    __asm__ volatile
    (
        "\n\tmov  %1, r10"
        "\n\tmov  %2, r6"
        "\n\tmov  %3, r7"
#if MCOS_CFG_DS_TRACE_ENABLE
        "\n\tmov  lp, r8"
#endif
        "\n\tsyscall 1"
        "\n\tmov  r10, %0"
        :"=r"(ret)
        :"r"(svc_id),"r"(arg1),"r"(arg2)
        :"cc", "memory", "r1", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15", "r16", "ep", "lp"
    );
#pragma ghs endnowarning

    return ret;
}


/*---------------------------------------------------------------------------
  ar_service_call_d_dp
    run syscall with 2 arguments
  Input     :   arg1    first data arguments of SVC
            :   p_arg2  second pointer argument of SVC
            :   svc_id  SVC ID
  Output    :   return value of SVC
  Return    :
  Note      :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE sint32 ar_service_call_d_dp(sint32 arg1, void *p_arg2, sint32 svc_id) __attribute__((unused));
MCOS_INLINE sint32 ar_service_call_d_dp(sint32 arg1, void *p_arg2, sint32 svc_id)
{
#pragma ghs nowarning 1546
    /*
     * confirmed that intended assembler codes are generated.
     */
    sint32 ret;

    __asm__ volatile
    (
        "\n\tmov  %1, r10"
        "\n\tmov  %2, r6"
        "\n\tmov  %3, r7"
#if MCOS_CFG_DS_TRACE_ENABLE
        "\n\tmov  lp, r8"
#endif
        "\n\tsyscall 1"
        "\n\tmov  r10, %0"
        :"=r"(ret)
        :"r"(svc_id),"r"(arg1),"r"(p_arg2)
        :"cc", "memory", "r1", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15", "r16", "ep", "lp"
    );
#pragma ghs endnowarning

    return ret;
}


/*---------------------------------------------------------------------------
  ar_service_call_d_ddd
    run syscall with 3 arguments
  Input     :   arg1    first data arguments of SVC
            :   arg2    second data argument of SVC
            :   arg3    third data argument of SVC
            :   svc_id  SVC ID
  Output    :   return value of SVC
  Return    :
  Note      :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE sint32 ar_service_call_d_ddd(sint32 arg1, sint32 arg2, sint32 arg3, sint32 svc_id) __attribute__((unused));
MCOS_INLINE sint32 ar_service_call_d_ddd(sint32 arg1, sint32 arg2, sint32 arg3, sint32 svc_id)
{
#pragma ghs nowarning 1546
    /*
     * confirmed that intended assembler codes are generated.
     */
    sint32 ret;

    __asm__ volatile
    (
        "\n\tmov  %1, r10"
        "\n\tmov  %2, r6"
        "\n\tmov  %3, r7"
        "\n\tmov  %4, r8"
#if MCOS_CFG_DS_TRACE_ENABLE
        "\n\tmov  lp, r9"
#endif
        "\n\tsyscall 1"
        "\n\tmov  r10, %0"
        :"=r"(ret)
        :"r"(svc_id),"r"(arg1),"r"(arg2),"r"(arg3)
        :"cc", "memory", "r1", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15", "ep", "lp"
    );
#pragma ghs endnowarning

    return ret;
}


/*---------------------------------------------------------------------------
  ar_service_call_0_ddp_notrace
    run syscall with 3 arguments
  Input     :   arg1    first data arguments of SVC
            :   arg2    second data argument of SVC
            :   p_arg3  third pointer argument of SVC
            :   svc_id  SVC ID
  Output    :   none
  Return    :   none
  Note      :   no trace for ar_errorhook_call
 ---------------------------------------------------------------------------*/
MCOS_INLINE void ar_service_call_0_ddp_notrace(sint32 arg1, sint32 arg2, const void *p_arg3, sint32 svc_id) __attribute__((unused));
MCOS_INLINE void ar_service_call_0_ddp_notrace(sint32 arg1, sint32 arg2, const void *p_arg3, sint32 svc_id)
{
#pragma ghs nowarning 1546
    /*
     * confirmed that intended assembler codes are generated.
     */

    __asm__ volatile
    (
        "\n\tmov  %0, r10"
        "\n\tmov  %1, r6"
        "\n\tmov  %2, r7"
        "\n\tmov  %3, r8"
        "\n\tsyscall 1"
        :
        :"r"(svc_id),"r"(arg1),"r"(arg2),"r"(p_arg3)
        :"cc", "memory", "r1", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15", "ep", "lp"
    );
#pragma ghs endnowarning

    return;
}

#if (AR_ENABLE_CHECK_TASK_MEMORY_ACCESS != 0U) || (AR_ENABLE_CHECK_ISR_MEMORY_ACCESS != 0U)

/*---------------------------------------------------------------------------
  ar_service_call_d_dpd
    run syscall with 3 arguments
  Input     :   arg1    first data arguments of SVC
            :   p_arg2  second pointer argument of SVC
            :   arg3    third data argument of SVC
            :   svc_id  SVC ID
  Output    :   return value of SVC
  Return    :
  Note      :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE sint32 ar_service_call_d_dpd(sint32 arg1, const void *p_arg2, sint32 arg3, sint32 svc_id) __attribute__((unused));
MCOS_INLINE sint32 ar_service_call_d_dpd(sint32 arg1, const void *p_arg2, sint32 arg3, sint32 svc_id)
{
#pragma ghs nowarning 1546
    /*
     * confirmed that intended assembler codes are generated.
     */
    sint32 ret;

    __asm__ volatile
    (
        "\n\tmov  %1, r10"
        "\n\tmov  %2, r6"
        "\n\tmov  %3, r7"
        "\n\tmov  %4, r8"
#if MCOS_CFG_DS_TRACE_ENABLE
        "\n\tmov  lp, r9"
#endif
        "\n\tsyscall 1"
        "\n\tmov  r10, %0"
        :"=r"(ret)
        :"r"(svc_id),"r"(arg1),"r"(p_arg2),"r"(arg3)
        :"cc", "memory", "r1", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15", "ep", "lp"
    );
#pragma ghs endnowarning

    return ret;
}

#endif /* #if (AR_ENABLE_CHECK_TASK_MEMORY_ACCESS != 0U) || (AR_ENABLE_CHECK_ISR_MEMORY_ACCESS != 0U) */

MCOS_INLINE sint32 ar_service_call_d_dpd_notrace(sint32 arg1, void *p_arg2, sint32 arg3, sint32 svc_id) __attribute__((unused));
MCOS_INLINE sint32 ar_service_call_d_dpd_notrace(sint32 arg1, void *p_arg2, sint32 arg3, sint32 svc_id)
{
#pragma ghs nowarning 1546
    /*
     * confirmed that intended assembler codes are generated.
     */
    sint32 ret;

    __asm__ volatile
    (
        "\n\tmov  %1, r10"
        "\n\tmov  %2, r6"
        "\n\tmov  %3, r7"
        "\n\tmov  %4, r8"
        "\n\tsyscall 1"
        "\n\tmov  r10, %0"
        :"=r"(ret)
        :"r"(svc_id),"r"(arg1),"r"(p_arg2),"r"(arg3)
        :"cc", "memory", "r1", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15", "ep", "lp"
    );
#pragma ghs endnowarning

    return ret;
}

/*---------------------------------------------------------------------------
  ar_service_call_d_dpdd_notrace
    run syscall with 4 arguments
  Input     :   arg1    first data arguments of SVC
            :   p_arg2  second pointer argument of SVC
            :   arg3    third data argument of SVC
            :   arg4    forth data argument of SVC
            :   svc_id  SVC ID
  Output    :   return value of SVC
  Return    :
  Note      :   none
 ---------------------------------------------------------------------------*/

extern sint32 ar_service_call_d_dpdd_notrace(sint32 arg1, void *p_arg2, sint32 arg3, sint32 arg4, sint32 svc_id);


/*---------------------------------------------------------------------------
  ar_service_call_d_dpp
    run syscall with 3 arguments
  Input     :   arg1    first data arguments of SVC
            :   p_arg2  second pointer argument of SVC
            :   p_arg3  third pointer argument of SVC
            :   svc_id  SVC ID
  Output    :   return value of SVC
  Return    :
  Note      :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE sint32 ar_service_call_d_dpp(sint32 arg1, void *p_arg2, void *p_arg3, sint32 svc_id) __attribute__((unused));
MCOS_INLINE sint32 ar_service_call_d_dpp(sint32 arg1, void *p_arg2, void *p_arg3, sint32 svc_id)
{
#pragma ghs nowarning 1546
    /*
     * confirmed that intended assembler codes are generated.
     */
    sint32 ret;

    __asm__ volatile
    (
        "\n\tmov  %1, r10"
        "\n\tmov  %2, r6"
        "\n\tmov  %3, r7"
        "\n\tmov  %4, r8"
#if MCOS_CFG_DS_TRACE_ENABLE
        "\n\tmov  lp, r9"
#endif
        "\n\tsyscall 1"
        "\n\tmov  r10, %0"
        :"=r"(ret)
        :"r"(svc_id),"r"(arg1),"r"(p_arg2),"r"(p_arg3)
        :"cc", "memory", "r1", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15", "ep", "lp"
    );
#pragma ghs endnowarning

    return ret;
}

MCOS_INLINE sint32 ar_service_call_d_dpp_notrace(sint32 arg1, const void *p_arg2, void *p_arg3, sint32 svc_id) __attribute__((unused));
MCOS_INLINE sint32 ar_service_call_d_dpp_notrace(sint32 arg1, const void *p_arg2, void *p_arg3, sint32 svc_id)
{
#pragma ghs nowarning 1546
    /*
     * confirmed that intended assembler codes are generated.
     */
    sint32 ret;

    __asm__ volatile
    (
        "\n\tmov  %1, r10"
        "\n\tmov  %2, r6"
        "\n\tmov  %3, r7"
        "\n\tmov  %4, r8"
        "\n\tsyscall 1"
        "\n\tmov  r10, %0"
        :"=r"(ret)
        :"r"(svc_id),"r"(arg1),"r"(p_arg2),"r"(p_arg3)
        :"cc", "memory", "r1", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15", "ep", "lp"
    );
#pragma ghs endnowarning

    return ret;
}

/*---------------------------------------------------------------------------
  ar_service_call_0_0
    run syscall with no arguments, and no return value
  Input     :   svc_id  SVC ID
  Output    :   none
  Return    :
  Note      :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE void ar_service_call_0_0(sint32 svc_id) __attribute__((unused));
MCOS_INLINE void ar_service_call_0_0(sint32 svc_id)
{
#pragma ghs nowarning 1546
    /*
     * confirmed that intended assembler codes are generated.
     */

    __asm__ volatile
    (
        "\n\tmov  %0, r10"
#if MCOS_CFG_DS_TRACE_ENABLE
        "\n\tmov  lp, r6"
#endif
        "\n\tsyscall 1"
        :
        :"r"(svc_id)
        :"cc", "memory", "r1", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15", "r16", "r17", "r18", "ep", "lp"
    );
#pragma ghs endnowarning
}


/*---------------------------------------------------------------------------
  ar_service_call_0_d
    run syscall with 1 data argument, and no return value
  Input     :   arg1    first data argument of SVC
            :   svc_id  SVC ID
  Output    :   none
  Return    :
  Note      :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE void ar_service_call_0_d(sint32 arg1, sint32 svc_id) __attribute__((unused));
MCOS_INLINE void ar_service_call_0_d(sint32 arg1, sint32 svc_id)
{
#pragma ghs nowarning 1546
    /*
     * confirmed that intended assembler codes are generated.
     */

    __asm__ volatile
    (
        "\n\tmov  %0, r10"
        "\n\tmov  %1, r6"
#if MCOS_CFG_DS_TRACE_ENABLE
        "\n\tmov  lp, r7"
#endif
        "\n\tsyscall 1"
        :
        :"r"(svc_id),"r"(arg1)
        :"cc", "memory", "r1", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15", "r16", "r17", "ep", "lp"
    );
#pragma ghs endnowarning
}

/*---------------------------------------------------------------------------
  ar_service_call_0_dd
    run syscall with 2 arguments, and no return value
  Input     :   arg1    first argument of SVC
            :   arg2    second argument of SVC
            :   svc_id  SVC ID
  Output    :   none
  Return    :
  Note      :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE void ar_service_call_0_dd(sint32 arg1, sint32 arg2, sint32 svc_id)__attribute__((unused));
MCOS_INLINE void ar_service_call_0_dd(sint32 arg1, sint32 arg2, sint32 svc_id)
{
#pragma ghs nowarning 1546
    /*
     * confirmed that intended assembler codes are generated.
     */

    __asm__ volatile
    (
        "\n\tmov  %0, r10"
        "\n\tmov  %1, r6"
        "\n\tmov  %2, r7"
#if MCOS_CFG_DS_TRACE_ENABLE
        "\n\tmov  lp, r8"
#endif
        "\n\tsyscall 1"
        :
        :"r"(svc_id),"r"(arg1),"r"(arg2)
        :"cc", "memory", "r1", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15", "r16", "ep", "lp"
    );
#pragma ghs endnowarning
}

#endif /* #ifndef MCOS_AR_V850_H */
