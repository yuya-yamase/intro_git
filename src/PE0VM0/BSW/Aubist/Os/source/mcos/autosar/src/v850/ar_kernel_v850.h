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
[ ar_kernel_v850.h ] - MCOS AUTOSAR ARCH for V850
****************************************************************************/
#ifndef AR_KERNEL_V850_H
#define AR_KERNEL_V850_H

typedef uint32 ar_kmode_state_t;

/*---------------------------------------------------------------------------
  ar_read_mpm

  Input     :
  Output    :
  Return    : MPM value
  Note  :   read MPM register
 ---------------------------------------------------------------------------*/
MCOS_INLINE uint32 ar_read_mpm(void);
MCOS_INLINE uint32 ar_read_mpm(void){
    uint32   mpm;

#pragma ghs nowarning 1546
    __asm__ volatile
    (
        "\nstsr   mpm, %0, 5"
        : "=r"(mpm)
        :
        : "cc", "memory"
    );
#pragma ghs endnowarning

    return(mpm);
}

/*---------------------------------------------------------------------------
  ar_write_mpm

  Input     : MPM value
  Output    :
  Return    : none
  Note  :   write MPM register
 ---------------------------------------------------------------------------*/
MCOS_INLINE void ar_write_mpm(uint32 mpm);
MCOS_INLINE void ar_write_mpm(uint32 mpm){
#pragma ghs nowarning 1546
    __asm__ volatile
    (
        "\nldsr   r0, svlock, 1"
        "\nsynci"
        "\nldsr   %0, mpm, 5"
        "\nsynci"
        "\nmov    1, r12"
        "\nldsr   r12, svlock, 1"
        "\nsynci"
        : "+r"(mpm)
        :
        : "cc", "memory", "r12"
    );
#pragma ghs endnowarning

    return;
}

/*---------------------------------------------------------------------------
  ar_enter_kernel

  Input     :
  Output    :
  Return    : previus mode
  Note  :   change os mode
 ---------------------------------------------------------------------------*/
MCOS_INLINE ar_kmode_state_t ar_enter_kernel(void) __attribute__((unused));
MCOS_INLINE ar_kmode_state_t ar_enter_kernel(void)
{
    ar_kmode_state_t  prev;
    uint32            sp;
    uint32            lower;
    uint32            upper;
    const mkcb_t      *mkcb;
    clscb_t const     *clscb;
    uint32   mpm;

    prev = (ar_kmode_state_t)ar_read_mpm();
    if ( ((uint32)prev & (uint32)MPU_MPM_MPE_MASK) != (uint32)0 )
    {
        /* disable MPE */
        mpm = (uint32)prev & (MPU_MPM_MPE_MASK ^ 0xFFFFFFFFU);
        ar_write_mpm( mpm );
    }
    else
    {
        /* Nothing to do */
    }

    /* sp check */
    mkcb = (const mkcb_t *)mcos_mkcc_get_current_control_block();
    clscb = mcos_mkcc_get_clscb(mkcb);

    lower = clscb->aroscb.osarchcb.check_stack_addr;
    upper = lower + clscb->aroscb.osarchcb.check_stack_size;
    lower += USER_CFG_MCOS_CFG_AR_SYSCALL_STACKSIZE();
    sp = (uint32)mcos_hwl_get_sp();
    if ( (lower >= sp) || (sp > upper) )
    {
        mcos_hwl_mk_sp_error();
        /* NEVER RETURN */
    }

    return prev;
}

/*---------------------------------------------------------------------------
  ar_leave_kernel

  Input     : prev  preious mode
  Output    :
  Return    :
  Note  : restore MPE
 ---------------------------------------------------------------------------*/
MCOS_INLINE void ar_leave_kernel(ar_kmode_state_t prev) __attribute__((unused));
MCOS_INLINE void ar_leave_kernel(ar_kmode_state_t prev)
{
    uint32   mpm;

    if ( ((uint32)prev & (uint32)MPU_MPM_MPE_MASK) != (uint32)0 )
    {
        /* enable MPE */
        mpm = ar_read_mpm();
        mpm |= (uint32)MPU_MPM_MPE_MASK;
        ar_write_mpm( mpm );
    }
    else
    {
        /* Nothing to do */
    }

}

#ifdef OS_CFG_H

#if (AR_OS_EXIST_SPINLOCK == STD_ON)

#define OS_START_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_256
#include "Os_MemMap.h"
extern ar_spinlockcb_t                  ar_spinlockcb_table[AR_OS_NUM_SPINLOCKS];
#define OS_STOP_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_256
#include "Os_MemMap.h"

#endif /* #if (AR_OS_EXIST_SPINLOCK == STD_ON) */

#else /* #ifdef OS_CFG_H */

#define OS_START_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_256
#include "Os_MemMap.h"
extern ar_spinlockcb_t                  ar_spinlockcb_table[];
#define OS_STOP_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_256
#include "Os_MemMap.h"

#endif /* #ifdef OS_CFG_H */


typedef struct
{
#if (AR_IOC_SPINLOCK_PADDING1_N > 0U)
    volatile uint32                 padding1[(uint32)AR_IOC_SPINLOCK_PADDING1_N];
#endif /* #if (AR_IOC_SPINLOCK_PADDING1_N > 0U) */
    mcos_spinlock_obj_t    mcos_spinlock;
    /* hw dependency spinlock object padding */
#if (AR_IOC_SPINLOCK_PADDING2_N > 0U)
    volatile uint32                 padding2[(uint32)AR_IOC_SPINLOCK_PADDING2_N];
#endif /* #if (AR_IOC_SPINLOCK_PADDING2_N > 0U) */
} ar_ioc_lock_t;


#ifdef OS_CFG_H

#if ((AR_OS_USE_MULTICORE == STD_ON) && (AR_OS_EXIST_IOC == STD_ON))

#define OS_START_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_256
#include "Os_MemMap.h"

extern ar_ioc_lock_t                    ar_ioc_lock[AR_OS_NUM_IOC_COMMUNICATIONS];

#define OS_STOP_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_256
#include "Os_MemMap.h"

#endif /* #if ((AR_OS_USE_MULTICORE == STD_ON) && (AR_OS_EXIST_IOC == STD_ON)) */

#else /* #ifdef OS_CFG_H */

#define OS_START_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_256
#include "Os_MemMap.h"

extern ar_ioc_lock_t                    ar_ioc_lock[];

#define OS_STOP_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_256
#include "Os_MemMap.h"

#endif /* #ifdef OS_CFG_H */

#endif /* #ifndef AR_KERNEL_V850_H */
