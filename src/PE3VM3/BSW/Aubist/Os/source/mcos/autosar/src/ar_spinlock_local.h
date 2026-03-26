/*
    Copyright (C) 2018 By eSOL Co.,Ltd. Tokyo, Japan

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
[ar_spinlock_local.h] - Spinlock local header
****************************************************************************/

#ifndef AR_SPINLOCK_LOCAL_H
#define AR_SPINLOCK_LOCAL_H

#include <mcos_mk.h>
#include "Os_internal.h"
#include "ar_interrupt.h"

#include "ar_spinlock.h"

#ifdef OS_CFG_H

#if (AR_OS_EXIST_SPINLOCK == STD_ON)

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"
extern const ar_spinlock_config_t       ar_spinlock_configs[AR_OS_NUM_SPINLOCKS];
#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"
extern const ar_spinlock_config_t ** const ar_spinlock_nestcb_table[AR_OS_NUM_CORES];
#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#endif /* #if (AR_OS_EXIST_SPINLOCK == STD_ON) */

#else /* #ifdef OS_CFG_H */

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"
extern const ar_spinlock_config_t       ar_spinlock_configs[];
#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"
#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"
extern const ar_spinlock_config_t ** const ar_spinlock_nestcb_table[];
#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"


#define AR_SPINLOCK_LOCAL_ENABLE

#endif /* #ifdef OS_CFG_H */

#define AR_LOCK_NONE                    0U
#define AR_LOCK_CAT2_INTERRUPTS         1U
#define AR_LOCK_ALL_INTERRUPTS          2U

#ifdef AR_SPINLOCK_LOCAL_ENABLE

AR_LOCAL_FORCE_INLINE void ar_spinlock_get(
    ar_spinlockcb_t * const p_spinlockcb,
    ar_spinlockcb_t ** const pp_wait_spinlockcb);
AR_LOCAL_FORCE_INLINE void ar_spinlock_release(
    ar_spinlockcb_t * const p_spinlockcb);
AR_LOCAL_FORCE_INLINE boolean ar_spinlock_try_to_get(
    ar_spinlockcb_t * const p_spinlockcb);
AR_LOCAL_FORCE_INLINE boolean ar_check_nest_spn_order(
    const ar_spinlock_config_t * const p_get_spnconfig,
    const ar_spinlockcb_t * const p_last_spinlockcb);
AR_LOCAL_FORCE_INLINE ar_context_spinlockcbs_t *ar_spinlock_get_contextcb(
    clscb_t * const clscb,
    ar_intcb_t * const ar_intcb,
    void ** const pp_ownercb);
AR_LOCAL_FORCE_INLINE StatusType ar_spinlock_hold(
    ar_spinlockcb_t * const p_spinlockcb,
    const ar_spinlock_config_t * const p_config,
    const mcos_id_t lcid,
    void * const p_ownercb,
    ar_spinlockcb_t ** const pp_last_spinlockcb);
AR_LOCAL_FORCE_INLINE void ar_spinlock_pre_release(
    const ar_spinlock_config_t * const p_rel_spnconfig,
    const ar_spinlockcb_t * const p_last_spinlockcb);

AR_LOCAL_FORCE_INLINE void ar_resume_interrupts(const ar_spinlock_config_t *p_config, clscb_t *clscb);

/*---------------------------------------------------------------------------
  ar_spinlock_get

  Input     :   p_spinlockcb
            :   pp_wait_spinlockcb
  Output    :   none
  Return    :   none
  Note  :   Called in the critical section.
 ---------------------------------------------------------------------------*/
AR_LOCAL_FORCE_INLINE void ar_spinlock_get(
    ar_spinlockcb_t * const p_spinlockcb,
    ar_spinlockcb_t ** const pp_wait_spinlockcb)
{
#if (AR_OS_USE_MULTICORE == STD_ON)
    /* set pp_wait_spinlockcb */
    *pp_wait_spinlockcb = p_spinlockcb;

    /* get spinlock (enable interrupts)*/
    mcos_spinlock_get_enaint(&(p_spinlockcb->mcos_spinlock));

    /* clear pp_wait_spinlockcb */
    *pp_wait_spinlockcb = (ar_spinlockcb_t *)NULL;
#else /* (AR_OS_USE_MULTICORE == STD_ON) */
    (void)p_spinlockcb;
    (void)pp_wait_spinlockcb;
#endif /* (AR_OS_USE_MULTICORE == STD_ON) */
}

/*---------------------------------------------------------------------------
  ar_spinlock_release

  Input     :   p_spinlockcb
  Output    :   none
  Return    :   none
  Note  :   none
 ---------------------------------------------------------------------------*/
AR_LOCAL_FORCE_INLINE void ar_spinlock_release(
    ar_spinlockcb_t * const p_spinlockcb)
{
#if (AR_OS_USE_MULTICORE == STD_ON)
    mcos_spinlock_release(&(p_spinlockcb->mcos_spinlock));
#else /* (AR_OS_USE_MULTICORE == STD_ON) */
    (void)p_spinlockcb;
#endif /* (AR_OS_USE_MULTICORE == STD_ON) */
}

/*---------------------------------------------------------------------------
  ar_spinlock_try_to_get

  Input     :   p_spinlockcb
  Output    :   none
  Return    :   none
  Note  :   none
 ---------------------------------------------------------------------------*/
AR_LOCAL_FORCE_INLINE boolean ar_spinlock_try_to_get(
    ar_spinlockcb_t * const p_spinlockcb)
{
    boolean lock;

#if (AR_OS_USE_MULTICORE == STD_ON)
    mcos_bool_t templock;
    templock = mcos_spinlock_try_to_get(&(p_spinlockcb->mcos_spinlock));
    lock = (boolean)((templock == (mcos_bool_t)mcos_false) ? FALSE : TRUE);
#else /*(AR_OS_USE_MULTICORE == STD_ON) */
    (void)p_spinlockcb;
    lock = (boolean)TRUE;
#endif /*(AR_OS_USE_MULTICORE == STD_ON) */
    return (boolean)lock;
}

/*---------------------------------------------------------------------------
  ar_check_nest_spn_order

  Input     :   p_get_spnconfig
            :   p_last_spinlockcb
  Output    :   none
  Return    :
  Note  :   none
 ---------------------------------------------------------------------------*/
AR_LOCAL_FORCE_INLINE boolean ar_check_nest_spn_order(
    const ar_spinlock_config_t * const p_get_spnconfig,
    const ar_spinlockcb_t * const p_last_spinlockcb)
{
    boolean         nest_flag;
    const ar_spinlock_config_t   *p_config;
    ar_spinlock_config_t const * const *nestcb;

    if (p_last_spinlockcb != NULL)
    {
        /* check in context */
        nest_flag = (boolean)FALSE;
        p_config = p_last_spinlockcb->p_config;
        while (p_config->p_nextcb != NULL)
        {
            p_config = p_config->p_nextcb;
            if (p_config == p_get_spnconfig) {
                nest_flag = (boolean)TRUE;
                break;
            }
            else
            {
                /* Nothing to do */
            }
        }
    }
    else
    {
        const ar_spinlock_config_t*  p_front_config;

#if (AR_OS_USE_MULTICORE == STD_ON)
        /* check in core */
        nestcb = ar_spinlock_nestcb_table[ar_get_core_id()];
#else /* (AR_OS_USE_MULTICORE == STD_ON) */
        nestcb = ar_spinlock_nestcb_table[0];
#endif /* (AR_OS_USE_MULTICORE == STD_ON) */

        /* Is this nested spinlock? */
        if (p_get_spnconfig->nestcb_index < USER_CFG_AR_OS_NUM_SPINLOCK_NESTCBS())
        {
            p_front_config = nestcb[p_get_spnconfig->nestcb_index];
            if (p_front_config != NULL)
            {
                /* already acquired nested locks in this core */
                nest_flag = (boolean)FALSE;
                p_config = p_get_spnconfig->p_nextcb;
                while (p_config != NULL)
                {
                    if (p_config == p_front_config) {
                        /* This spinlock is prior to the lock being acquired */
                        nest_flag = (boolean)TRUE;
                        break;
                    }
                    else
                    {
                        /* Nothing to do */
                    }
                    p_config = p_config->p_nextcb;
                }
            }
            else
            {
                /* no acquired nested locks in this core */
                nest_flag = (boolean)TRUE;
            }
        }
        else
        {
            /* not nested spinlock */
            nest_flag = (boolean)TRUE;
        }
    }

    return nest_flag;
}

/*
 * a part of TryToGetSpinlock, GetSpinlock
 */
AR_LOCAL_FORCE_INLINE ar_context_spinlockcbs_t *ar_spinlock_get_contextcb(
    clscb_t * const clscb,
    ar_intcb_t * const ar_intcb,
    void ** const pp_ownercb)
{
    ar_context_spinlockcbs_t *p_context_spinlockcbs;

    if (((uint32)clscb->aroscb.call_level & (uint32)AR_CL_HK_PROT) != (uint32)0U)
    {
        p_context_spinlockcbs = (&(clscb->aroscb.context_spinlockcbs));
        *pp_ownercb = (void *) &(clscb->aroscb.context_spinlockcbs);
    }
    else if (ar_intcb->p_running_isr != NULL)
    {
        p_context_spinlockcbs = (&(ar_intcb->p_running_isr->context_spinlockcbs));
        *pp_ownercb = (void *) (ar_intcb->p_running_isr);
    }
    else
    {
        tcb_t const     *p_mtcb;
        ar_tcb_t        *p_atcb;

        p_mtcb = mcos_get_running(clscb);
        p_atcb = ar_get_ar_tcb(p_mtcb);
        p_context_spinlockcbs = (&(p_atcb->context_spinlockcbs));
        *pp_ownercb = (void *)p_atcb;
    }

    return p_context_spinlockcbs;
}

/*
 * a part of TryToGetSpinlock, GetSpinlock
 */
AR_LOCAL_FORCE_INLINE StatusType ar_spinlock_hold(
    ar_spinlockcb_t * const p_spinlockcb,
    const ar_spinlock_config_t * const p_config,
    const mcos_id_t lcid,
    void * const p_ownercb,
    ar_spinlockcb_t ** const pp_last_spinlockcb)
{
    StatusType      status;
    const mkcb_t    *mkcb;
    clscb_t         *clscb;
    ar_intcb_t      *ar_intcb;

    status = E_OK;

    mkcb = (const mkcb_t *)mcos_mkcc_get_current_control_block();
    clscb = mcos_mkcc_get_clscb(mkcb);
    ar_intcb = mcos_cls_get_arintcb(clscb);

    if (p_config->lock_method == (uint8)AR_LOCK_ALL_INTERRUPTS)
    {
        if ((uint32)ar_intcb->nestcnt_susallints == (uint32)UINT8_INVALID)
        {
            status = E_OS_LIMIT;
        }
        else
        {
            ar_suspend_all_interrupt_impl(clscb, ar_intcb);

            ar_intcb->nestcnt_susallints_spinlock++;
        }
    }
    else if (p_config->lock_method == (uint8)AR_LOCK_CAT2_INTERRUPTS)
    {
        if ((uint32)ar_intcb->nestcnt_susosints == (uint32)UINT8_INVALID)
        {
            status = E_OS_LIMIT;
        }
        else
        {
            ar_suspend_os_interrupt_spinlock_impl(clscb, ar_intcb);
            ar_intcb->nestcnt_susosints_spinlock++;
        }
    }
    else
    {
        /* Nothing to do */
    }

    if (status == (StatusType)E_OK)
    {
        p_spinlockcb->lcid = lcid;
        p_spinlockcb->p_ownercb = p_ownercb;
        p_spinlockcb->p_prevcb = *pp_last_spinlockcb;
#if (AR_OS_USE_EXTENDEDSTATUS == STD_ON)
        if ( (p_config->nestcb_index < USER_CFG_AR_OS_NUM_SPINLOCK_NESTCBS()) && (*pp_last_spinlockcb == NULL) )
        {
            const ar_spinlock_config_t **nestcb;

            /* update nested spinlock information in this core */
#if (AR_OS_USE_MULTICORE == STD_ON)
            /* check in core */
            nestcb = ar_spinlock_nestcb_table[ar_get_core_id()];
#else /* (AR_OS_USE_MULTICORE == STD_ON) */
            nestcb = ar_spinlock_nestcb_table[0];
#endif /* (AR_OS_USE_MULTICORE == STD_ON) */

            nestcb[p_config->nestcb_index] = p_config;
        }
#endif /* (AR_OS_USE_EXTENDEDSTATUS == STD_ON) */
        *pp_last_spinlockcb = p_spinlockcb;
    }
    else
    {
        ar_spinlock_release(p_spinlockcb);
    }

    return status;
}

/*
 * a part of ReleaseGetSpinlock, ar_spinlock_force_release
 */
AR_LOCAL_FORCE_INLINE void ar_spinlock_pre_release(
    const ar_spinlock_config_t * const p_rel_spnconfig,
    const ar_spinlockcb_t * const p_last_spinlockcb)
{
    ar_spinlockcb_t const       *p_spinlockcb;
    const ar_spinlock_config_t  *p_config;
    const ar_spinlock_config_t  **nestcb;

    if ( (p_rel_spnconfig->nestcb_index < USER_CFG_AR_OS_NUM_SPINLOCK_NESTCBS()) && (p_last_spinlockcb == NULL) )
    {
        /* update nested spinlock information in this core */
#if (AR_OS_USE_MULTICORE == STD_ON)
        /* check in core */
        nestcb = ar_spinlock_nestcb_table[ar_get_core_id()];
#else /* (AR_OS_USE_MULTICORE == STD_ON) */
        nestcb = ar_spinlock_nestcb_table[0];
#endif /* (AR_OS_USE_MULTICORE == STD_ON) */
        if (nestcb[p_rel_spnconfig->nestcb_index] == p_rel_spnconfig)
        {
            const mcos_id_t lcid = mcos_get_lcid();
            /* find a front spinlock that acquired lock in this core */
            p_config = p_rel_spnconfig->p_nextcb;
            while (p_config != NULL)
            {
                p_spinlockcb = &ar_spinlockcb_table[p_config->spinlock_id];
                if (p_spinlockcb->lcid == lcid) {
                    break;
                }
                else
                {
                    /* Nothing to do */
                }
                p_config = p_config->p_nextcb;
            }
            nestcb[p_rel_spnconfig->nestcb_index] = p_config;
        }
        else
        {
            /* Nothing to do */
        }
    }
}

/*
 * a part of ReleaseGetSpinlock, ReleaseGetSpinlockSkipErrorChk
 */
AR_LOCAL_FORCE_INLINE void ar_resume_interrupts(const ar_spinlock_config_t *p_config, clscb_t *clscb)
{
    ar_intcb_t      *ar_intcb;

    ar_intcb = mcos_cls_get_arintcb(clscb);

    if (p_config->lock_method == (uint8)AR_LOCK_ALL_INTERRUPTS)
    {
        ar_intcb->nestcnt_susallints_spinlock--;

        ar_resume_all_interrupt_spinlock_impl(clscb, ar_intcb);
    }
    else if (p_config->lock_method == (uint8)AR_LOCK_CAT2_INTERRUPTS)
    {
        ar_intcb->nestcnt_susosints_spinlock--;

        ar_resume_os_interrupt_spinlock_impl(clscb, ar_intcb);
    }
    else
    {
        /* Nothing to do */
    }

    if ((p_config->lock_method == (uint8)AR_LOCK_ALL_INTERRUPTS)
        || (p_config->lock_method == (uint8)AR_LOCK_CAT2_INTERRUPTS) )
    {
        if ((((uint32)clscb->aroscb.call_level & (uint32)AR_CL_MASK) == (uint32)AR_CL_TASK)
                && (((uint32)(clscb->ctx) & (uint32)CTX_DISDSP) == (uint32)CTX_NONE))
        {
            const  mcos_bool_t is_lock = mcos_hwl_cpu_is_lockAllInt();
            if (is_lock == (mcos_bool_t)mcos_false)
            {
                ar_do_dispatch_task(clscb);
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
    }
    else
    {
        /* Nothing to do */
    }
}

#endif /* #ifdef AR_SPINLOCK_LOCAL_ENABLE */

#endif /* AR_SPINLOCK_LOCAL_H */
