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
[ar_interrupt.h] - support function for interrupt
****************************************************************************/

#ifndef AR_INTERRUPT_H
#define AR_INTERRUPT_H

#include "ar_kernel_impl.h"
#include "ar_task.h"

struct ar_int_config_st {
    ar_funcp_t          entry;
    ar_intno_t          intno;
    ar_pri_t            pri;
    ar_atr_t            atr;
};

struct ar_cat1_int_config_st {
    ar_funcp_t          entry;
    ar_intno_t          intno;
    ar_pri_t            pri;
    mcos_id_t           lcid;
    ar_atr_t            atr;
};

#define AR_ENABLE       (0x01U)
#define AR_DISABLE      (0x00U)

#define AR_PRI_MINISR   (-1)     /* lowest interrupt priroity */

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

extern void ar_cat1_interrupt_init(void);
extern void ar_interrupt_init(void);
extern void ar_force_enabled_interrupts(const OSServiceIdType serviceId);
extern void ar_isr_wrapper(boolean is_protected, boolean is_trusted,
               uint32 option, ar_funcp_t entry, mcos_uintptr_t *p_osap_sp);

extern void ar_interrupt_bind(void);

extern uint32_t * ar_cat2_isr_entry(const mcos_uintptr_t iid, uint32_t * sp,
    const mkcb_t * const mkcb, void * const p_isrcb, const int32_t bpri
#if MCOS_CFG_DS_TRACE_LOG_INT
    ,void * const retadr
#endif /* #if MCOS_CFG_DS_TRACE_LOG_INT */
    );

#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
extern AccessType ar_check_isr_memory(
        ISRType ISRID, ConstMemoryStartAddressType start, MemorySizeType size);
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

extern mcos_id_t ar_cat2_get_iid(
    ISRType ISRID);
extern const ar_cat1_int_config_t *ar_get_cat1_int_config(
    ISRType cat1isr);
extern ar_isrcb_t *ar_get_isrcb(
    ISRType cat2isr);
extern const ar_isr_config_t *ar_get_isr_config(
    ISRType cat2isr);

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

AR_LOCAL_FORCE_INLINE void ar_suspend_all_interrupt_impl(clscb_t * const clscb,
    ar_intcb_t * const ar_intcb);
AR_LOCAL_FORCE_INLINE void ar_resume_all_interrupt_impl(clscb_t * const clscb,
    ar_intcb_t * const ar_intcb);
AR_LOCAL_FORCE_INLINE void ar_resume_all_interrupt_spinlock_impl(clscb_t * const clscb,
    ar_intcb_t * const ar_intcb);
AR_LOCAL_FORCE_INLINE void ar_suspend_os_interrupt_impl(clscb_t * const clscb,
    ar_intcb_t * const ar_intcb);
AR_LOCAL_FORCE_INLINE void ar_suspend_os_interrupt_spinlock_impl(clscb_t * const clscb,
    ar_intcb_t * const ar_intcb);
AR_LOCAL_FORCE_INLINE void ar_resume_os_interrupt_impl(clscb_t * const clscb,
    ar_intcb_t * const ar_intcb);
AR_LOCAL_FORCE_INLINE void ar_resume_os_interrupt_spinlock_impl(clscb_t * const clscb,
    ar_intcb_t * const ar_intcb);

/*
 * called from,
 *   - SuspendAllInterrupts API (not in CS)
 *   - Get/TryToGetSpinlock with LOCK_ALL_INTERRUPTS (in CS)
 */
AR_LOCAL_FORCE_INLINE void ar_suspend_all_interrupt_impl(
    clscb_t * const clscb,
    ar_intcb_t * const ar_intcb)
{
    uint8_t         nestcnt_susallints;
    int32_t         sr;

    sr = mcos_hwl_cpu_lockAllInt();

    nestcnt_susallints = ar_intcb->nestcnt_susallints;
    ar_intcb->nestcnt_susallints = nestcnt_susallints;
    ar_intcb->nestcnt_susallints++;

    if ((uint32)nestcnt_susallints == (uint32)0U)
    {
        ar_intcb->saved_lockall_by_sus_all = sr;
        AR_CALL_LEVEL_ENTER(clscb, AR_INTSTS_SUSPENDALLINTERRUPTS);
    }
    else
    {
        /* Nothing to do */
    }
}


/*
 * called from,
 *  - ResumeAllInterrupts API (not in CS)
 */
AR_LOCAL_FORCE_INLINE void ar_resume_all_interrupt_impl(
    clscb_t * const clscb,
    ar_intcb_t * const ar_intcb)
{
    uint8_t         nestcnt_susallints;

    /* now lockAll state */

    nestcnt_susallints = ar_intcb->nestcnt_susallints;
    nestcnt_susallints--;
    ar_intcb->nestcnt_susallints = nestcnt_susallints;

    if ((uint32)nestcnt_susallints == (uint32)0U)
    {
        uint16      call_level;

        /*
         * for performance, instead of ...
         * AR_CALL_LEVEL_EXIT(clscb, AR_INTSTS_SUSPENDALLINTERRUPTS);
         */
        call_level = (uint16)((uint32)clscb->aroscb.call_level
            & (~(uint32)AR_INTSTS_SUSPENDALLINTERRUPTS));
        clscb->aroscb.call_level = call_level;
#if (AR_OS_USE_MULTICORE == STD_ON)
        if ((((uint32)(clscb->ctx) & (uint32)CTX_DISDSP) == (uint32)CTX_NONE)
              && (((uint32)call_level & (uint32)AR_CL_MASK) == (uint32)AR_CL_TASK))
        {
            const int32_t pri = mcos_hwl_cpu_getIntPriority();
            if (MCOS_INTM_BPRI_TO_APRI(pri) >= USER_CFG_AR_HIGHEST_C2ISR_PRIORITY())
            {
                ar_critical_section_t cs;
                boolean lock;
                /*
                 * enter critical section
                 */
                cs = ar_critical_section_enter_core(clscb);
                /* restore previous lock */
                mcos_hwl_cpu_unlockAllInt(ar_intcb->saved_lockall_by_sus_all);
                lock = mcos_hwl_cpu_is_lockAllInt();
                if ((uint32)lock == (uint32)FALSE)
                {
                    tcb_t                   *running;
                    running = mcos_get_running(clscb);
                    if (running != clscb->ready)
                    {
                        ar_dispatch_task_core(clscb, running);
                    }
                    else
                    {
                        /* Nothing to do */
                    }
                }
                else
                {
                    /* Nothing to do */
                }
                /*
                 * leave critical section
                 */
                ar_critical_section_leave_core(clscb, cs);
            }
            else
            {
                /* restore previous lock */
                mcos_hwl_cpu_unlockAllInt(ar_intcb->saved_lockall_by_sus_all);
            }
        }
        else
        {
            /* restore previous lock */
            mcos_hwl_cpu_unlockAllInt(ar_intcb->saved_lockall_by_sus_all);
        }
#else /* (AR_OS_USE_MULTICORE == STD_ON) */
            /* restore previous lock */
            mcos_hwl_cpu_unlockAllInt(ar_intcb->saved_lockall_by_sus_all);
#endif /* (AR_OS_USE_MULTICORE == STD_ON) */
    }
    else
    {
        /* Nothing to do */
    }
}


/*
 * called from,
 *  - ReleaseSpinlock with LOCK_ALL_INTERRUPTS (in CS)
 *  - ar_spinlock_force_release with LOCK_ALL_INTERRUPTS (in CS)
 */
AR_LOCAL_FORCE_INLINE void ar_resume_all_interrupt_spinlock_impl(
    clscb_t * const clscb,
    ar_intcb_t * const ar_intcb)
{
    uint8_t         nestcnt_susallints;

    /* now lockAll state */

    nestcnt_susallints = ar_intcb->nestcnt_susallints;
    nestcnt_susallints--;
    ar_intcb->nestcnt_susallints = nestcnt_susallints;

    if ((uint32)nestcnt_susallints == (uint32)0U)
    {
        AR_CALL_LEVEL_EXIT(clscb, AR_INTSTS_SUSPENDALLINTERRUPTS);

        /* restore previous lock */
        mcos_hwl_cpu_unlockAllInt(ar_intcb->saved_lockall_by_sus_all);
    }
    else
    {
        /* Nothing to do */
    }
}


/*
 * called from,
 *  - SuspendOSInterrupts API (not in CS)
 */
AR_LOCAL_FORCE_INLINE void ar_suspend_os_interrupt_impl(
    clscb_t * const clscb,
    ar_intcb_t * const ar_intcb)
{
    int32_t         cbpri;
    uint8_t         nestcnt_susosints;
    int32_t         sr;

    sr = mcos_hwl_cpu_lockAllInt();

    nestcnt_susosints = ar_intcb->nestcnt_susosints;

    if ((uint32)nestcnt_susosints == (uint32)0U)
    {
        AR_CALL_LEVEL_ENTER(clscb, AR_INTSTS_SUSPENDOSINTERRUPTS);

        /* save current interrupt priority */
        cbpri = mcos_hwl_cpu_getIntPriority();
        ar_intcb->saved_intbpri_by_sus_os = cbpri;

        if ((MCOS_INTM_BPRI_TO_APRI(cbpri) >= USER_CFG_AR_HIGHEST_C2ISR_PRIORITY()))
        {
            /* Called from Task/C2ISR  */
#if (AR_OS_USE_MULTICORE == STD_ON)
            /* disable dispatch from mkmsg */
            clscb->ctx = (uint8_t)((uint32)clscb->ctx | (uint32)CTX_DISDSP);
#endif /* (AR_OS_USE_MULTICORE == STD_ON) */

            /* set C2ISR disable interrupt priority */
            mcos_hwl_cpu_setIntPriority(MCOS_INTM_APRI_TO_BPRI(USER_CFG_AR_HIGHEST_C2ISR_PRIORITY()));
        }
        else
        {
            /* Nothing to do */
        }
    }
    else
    {
        /* Nothing to do */
    }

    ar_intcb->nestcnt_susosints = nestcnt_susosints;
    ar_intcb->nestcnt_susosints++;

    mcos_hwl_cpu_unlockAllInt(sr);
}


/*
 * called from,
 *   - Get/TryToGetSpinlock with LOCK_CAT2_INTERRUPTS (in CS, no C1ISR)
 */
AR_LOCAL_FORCE_INLINE void ar_suspend_os_interrupt_spinlock_impl(
    clscb_t * const clscb,
    ar_intcb_t * const ar_intcb)
{
    int32_t         cbpri;
    uint8_t         nestcnt_susosints;
    int32_t         sr;

    sr = mcos_hwl_cpu_lockAllInt();

    nestcnt_susosints = ar_intcb->nestcnt_susosints;

    if ((uint32)nestcnt_susosints == (uint32)0U)
    {
        AR_CALL_LEVEL_ENTER(clscb, AR_INTSTS_SUSPENDOSINTERRUPTS);

        if ((uint32)ar_intcb->nested_lock_os_int_cnt == AR_NESTED_LOCK_OS_INT_CNT_1)
        {
            cbpri = ar_intcb->saved_intbpri;

            /* save current interrupt priority */
            ar_intcb->saved_intbpri_by_sus_os = cbpri;
            if ((MCOS_INTM_BPRI_TO_APRI(cbpri) >= USER_CFG_AR_HIGHEST_C2ISR_PRIORITY()))
            {
                /* Called from Task/C2ISR  */
#if (AR_OS_USE_MULTICORE == STD_ON)
                /* disable dispatch from mkmsg */
                clscb->ctx = (uint8_t)((uint32)clscb->ctx | (uint32)CTX_DISDSP);
#endif /* (AR_OS_USE_MULTICORE == STD_ON) */

                /* set C2ISR disable interrupt priority */
                ar_intcb->saved_intbpri = MCOS_INTM_APRI_TO_BPRI(USER_CFG_AR_HIGHEST_C2ISR_PRIORITY());
            }
            else
            {
                /* Nothing to do */
            }
        }
        else
        {
            /* ar_intcb->nested_lock_os_int_cnt > 1 */

            /* save current interrupt priority */
            ar_intcb->saved_intbpri_by_sus_os = MCOS_INTM_APRI_TO_BPRI(USER_CFG_AR_OS_EXEC_PRIORITY());
        }
    }
    else
    {
        /* Nothing to do */
    }

    ar_intcb->nestcnt_susosints = nestcnt_susosints;
    ar_intcb->nestcnt_susosints++;

    mcos_hwl_cpu_unlockAllInt(sr);
}


/*
 * called from,
 *  - ResumeOSInterrupts API (not in CS)
 */
AR_LOCAL_FORCE_INLINE void ar_resume_os_interrupt_impl(
    clscb_t * const clscb,
    ar_intcb_t * const ar_intcb)
{
    int32_t         cbpri;
    uint8_t         nestcnt_susosints;
    int32_t         sr;
#if (AR_OS_USE_MULTICORE == STD_ON)
    mcos_bool_t     is_cpulock = mcos_hwl_cpu_is_lockAllInt();
#endif /* (AR_OS_USE_MULTICORE == STD_ON) */

    sr = mcos_hwl_cpu_lockAllInt();

    nestcnt_susosints = ar_intcb->nestcnt_susosints;
    nestcnt_susosints--;
    ar_intcb->nestcnt_susosints = nestcnt_susosints;

    if ((uint32)nestcnt_susosints == (uint32)0U)
    {
        uint16      call_level;

        /*
         * for performance, instead of ...
         * AR_CALL_LEVEL_EXIT(clscb, AR_INTSTS_SUSPENDOSINTERRUPTS);
         */
        call_level = (uint16)((uint32)clscb->aroscb.call_level & (~(uint32)AR_INTSTS_SUSPENDOSINTERRUPTS));
        clscb->aroscb.call_level = call_level;

        cbpri = ar_intcb->saved_intbpri_by_sus_os;

        if ((MCOS_INTM_BPRI_TO_APRI(cbpri) >= USER_CFG_AR_HIGHEST_C2ISR_PRIORITY()))
        {
            /* Called from Task/C2ISR */

            /* restore interrupt priority */
            mcos_hwl_cpu_setIntPriority(cbpri);

#if (AR_OS_USE_MULTICORE == STD_ON)

            /* enable dispatch */
            clscb->ctx = (uint8_t)((uint32)clscb->ctx & ~(uint32)CTX_DISDSP);
            if ((is_cpulock == (mcos_bool_t)mcos_false)
                    && (((uint32)call_level & (uint32)AR_CL_MASK) == (uint32)AR_CL_TASK) )
            {
                tcb_t       *running;
                running = mcos_get_running(clscb);
                if (running != clscb->ready)
                {
                    ar_critical_section_t   cs;
                    cs = ar_critical_section_enter_core(clscb);
                    mcos_hwl_cpu_unlockAllInt(sr);
                    ar_dispatch_task_core(clscb, running);
                    /* omit mcos_hwl_cpu_lockAllInt() */
                    ar_critical_section_leave_core(clscb, cs);
                }
                else
                {
                    /* Nothing to do */
                }
            }
            else
            {
                /* Nothing to do */
            }

#endif /* (AR_OS_USE_MULTICORE == STD_ON) */
        }
        else
        {
            /* Nothing to do */
        }
    }
    else
    {
        /* Nothing to do */
    }
    mcos_hwl_cpu_unlockAllInt(sr);
}


/*
 * called from,
 *   - ReleaseSpinlock with LOCK_CAT2_INTERRUPTS (in CS, no C1ISR)
 *   - ar_spinlock_force_release with LOCK_CAT2_INTERRUPTS (in CS, no C1ISR)
 */
AR_LOCAL_FORCE_INLINE void ar_resume_os_interrupt_spinlock_impl(
    clscb_t * const clscb,
    ar_intcb_t * const ar_intcb)
{
    int32_t         cbpri;
    uint8_t         nestcnt_susosints;
    int32_t         sr;

    sr = mcos_hwl_cpu_lockAllInt();

    nestcnt_susosints =ar_intcb->nestcnt_susosints;
    nestcnt_susosints--;
    ar_intcb->nestcnt_susosints = nestcnt_susosints;

    if ((uint32)nestcnt_susosints == (uint32)0U)
    {
        AR_CALL_LEVEL_EXIT(clscb, AR_INTSTS_SUSPENDOSINTERRUPTS);

        cbpri = ar_intcb->saved_intbpri_by_sus_os;

        if ((MCOS_INTM_BPRI_TO_APRI(cbpri) >= USER_CFG_AR_HIGHEST_C2ISR_PRIORITY()))
        {
            /* Called from Task/C2ISR */

            /* restore interrupt priority */
            ar_intcb->saved_intbpri = cbpri;

#if (AR_OS_USE_MULTICORE == STD_ON)
            /* enable dispatch */
            clscb->ctx = (uint8_t)((uint32)clscb->ctx & ~(uint32)CTX_DISDSP);
#endif /* (AR_OS_USE_MULTICORE == STD_ON) */
        }
        else
        {
            /* Nothing to do */
        }
    }
    else
    {
        /* Nothing to do */
    }
    mcos_hwl_cpu_unlockAllInt(sr);
}

#endif /* AR_INTERRUPT_H */
