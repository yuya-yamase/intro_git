/*
    Copyright(C) 2021 eSOL Co., Ltd. All rights reserved.

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
[mcos_v850_spinlock.h] - eMCOS v850 spinlock implementation
****************************************************************************/
#ifndef MCOS_V850_SPINLOCK_H
#define MCOS_V850_SPINLOCK_H

#if !MCOS_AUTOSAR
#error "Non-autosar is not supported."
#else /* #if !MCOS_AUTOSAR */

#include <mcos_mk_local.h>
#include "mcos_v850_local.h"

#include <hal/hal_cpu_impl.h>
#include "ar_spinlock_callback.h"


MCOS_INLINE void mcos_spinlock_init_inline(
    mcos_spinlock_obj_t * const lockobj);

MCOS_INLINE void mcos_spinlock_get_enaint_inline(
    mcos_spinlock_obj_t * const lockobj);

MCOS_INLINE void mcos_spinlock_get_inline(
    mcos_spinlock_obj_t * const lockobj);

MCOS_INLINE void mcos_spinlock_release_inline(
    mcos_spinlock_obj_t * const lockobj);
MCOS_INLINE mcos_bool_t mcos_spinlock_try_to_get_inline(
    mcos_spinlock_obj_t * const lockobj);

MCOS_INLINE uint32_t mcos_spinlock_searchnext(
    uint32_t next_ticket, uint32_t my_coreno);

#define CHECK_BIT(next_ticket, bit) \
    (((uint32_t)(next_ticket)) & ((uint32_t)((uint32_t)1U << (bit))))

#define CLR_BIT(next_ticket, bit) \
    ((uint16_t)(((uint32_t)(next_ticket)) & (~((uint32_t)1U << (bit)))))

#define BITOFFSET_NEXT_TICKET   16U

/* functions in mcos_v850_spinlock_ghs.850 */
extern uint32_t    mcos_spinlock_compare_and_swap(mcos_spinlock_ticket_t *spinlock, uint32_t new_value, uint32_t old_value );
extern uint32_t    mcos_spinlock_atomic_bitset(mcos_spinlock_ticket_t *lockobj, uint32_t or_pattern);
extern void        mcos_spinlock_atomic_write_now_serving(mcos_spinlock_ticket_t *lockobj, uint32_t value);
extern mcos_bool_t mcos_spinlock_conditional_write(mcos_spinlock_ticket_t *lockobj, uint32_t value);

 /*---------------------------------------------------------------------------
  mcos_spinlock_init_inline
     Initialize shared flags for spin lock
  Input     :   lockobj    pointer to lock object
  Output    :   none
  Return    :   none
  Note  :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE void
mcos_spinlock_init_inline(
    mcos_spinlock_obj_t * const lockobj)
{
    lockobj->ticket.spinlock = 0U;
}

 /*---------------------------------------------------------------------------
  mcos_spinlock_get_enaint_inline
     spin lock, enable interrupts while spin-wait
  Input     :   lockobj    pointer to lock object
  Output    :   none
  Return    :   none
  Note  :   none
 ---------------------------------------------------------------------------*/

MCOS_INLINE void
mcos_spinlock_get_enaint_inline(
    mcos_spinlock_obj_t * const lockobj)
{
    uint32_t    my_coreno;
    uint32_t    read_spinlock;
    mcos_spinlock_ticket_t cur_ticket;
    mcos_bool_t  retry;

    my_coreno = (uint32_t)(hal_cpu_getCoreNumber());

    /* RETRY loop */
    do {
        retry = (mcos_bool_t)mcos_false;

        /* set my ticket */
        read_spinlock = mcos_spinlock_atomic_bitset(&lockobj->ticket, (uint32_t)((uint32_t)1U << (my_coreno + BITOFFSET_NEXT_TICKET)));

        if (read_spinlock == (uint32_t)0)
        {
         /* Now my core locks this spinlock. */
            mcos_spinlock_atomic_write_now_serving(&lockobj->ticket, (uint32_t)CPUNO2LCID(my_coreno));
        }
        else
        {
            /* spin-wait */
            while(retry == (mcos_bool_t)mcos_false)
            {
                mcos_hwl_memory_barrier();

                cur_ticket.spinlock = lockobj->ticket.spinlock;

                if ((uint32_t)(cur_ticket.tickets.now_serving) == (uint32_t)CPUNO2LCID(my_coreno))
                {
                    break;
                }
                else
                {
                    /* Nothing to do */
                }

                /* enable interrupt */
                ar_spinlock_enaint();

                if( CHECK_BIT((uint32_t)(lockobj->ticket.tickets.next_ticket), my_coreno) == (uint32_t)0)
                {
                    /* continue RETRY loop; */
                    retry = (mcos_bool_t)mcos_true;
                }
                else
                {
                    /* Nothing to do */
                }
            }
        }
    } while(retry != (mcos_bool_t)mcos_false);
}


 /*---------------------------------------------------------------------------
  mcos_spinlock_get_inline

  Input     :   lockobj    pointer to lock object
  Output    :   none
  Return    :   none
  Note  :   none
 ---------------------------------------------------------------------------*/

MCOS_INLINE void
mcos_spinlock_get_inline(
    mcos_spinlock_obj_t * const lockobj)
{
    uint32_t    my_coreno;
    uint32_t    read_spinlock;
    mcos_spinlock_ticket_t cur_ticket;
    mcos_bool_t  retry;

    my_coreno = (uint32_t)(hal_cpu_getCoreNumber());

    /* RETRY loop */
    do {
        retry = (mcos_bool_t)mcos_false;

        /* set my ticket */
        read_spinlock = mcos_spinlock_atomic_bitset(&lockobj->ticket, (uint32_t)((uint32_t)1U << (my_coreno + BITOFFSET_NEXT_TICKET)));

        if (read_spinlock == (uint32_t)0)
        {
         /* Now my core locks this spinlock. */
            mcos_spinlock_atomic_write_now_serving(&lockobj->ticket, (uint32_t)CPUNO2LCID(my_coreno));
        }
        else
        {
            /* spin-wait */
            while(retry == (mcos_bool_t)mcos_false)
            {
                mcos_hwl_memory_barrier();

                cur_ticket.spinlock = lockobj->ticket.spinlock;

                if ((uint32_t)(cur_ticket.tickets.now_serving) == (uint32_t)CPUNO2LCID(my_coreno))
                {
                    break;
                }
                else
                {
                    /* Nothing to do */
                }

                if( CHECK_BIT((uint32_t)(lockobj->ticket.tickets.next_ticket), my_coreno) == (uint32_t)0)
                {
                    /* continue RETRY loop; */
                    retry = (mcos_bool_t)mcos_true;
                }
                else
                {
                    /* Nothing to do */
                }
            }
        }
    } while(retry != (mcos_bool_t)mcos_false);
}


 /*---------------------------------------------------------------------------
  mcos_spinlock_release_inline
     spin unlock
  Input     :   lockobj    pointer to lock object
  Output    :   none
  Return    :   none
  Note  :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE void
mcos_spinlock_release_inline(
    mcos_spinlock_obj_t * const lockobj)
{
    mcos_spinlock_ticket_t old_ticket, new_ticket;
    uint32_t    read_spinlock, new_spinlock, old_spinlock;
    uint32_t    my_coreno;
    uint32_t    next_coreno;
    int32_t     lcid;

    my_coreno = (uint32_t)(hal_cpu_getCoreNumber());

    /*
     * After the data written in the spinlock section is reflected in the memory,
     * the spinlock is released.
     */
    mcos_hwl_memory_barrier();

    do
    {
        old_ticket.spinlock = lockobj->ticket.spinlock;
        new_ticket = old_ticket;
        new_ticket.tickets.next_ticket = CLR_BIT(old_ticket.tickets.next_ticket, my_coreno);

        if ((uint32_t)(new_ticket.tickets.next_ticket) != (uint32_t)0)
        {
            /* allocate to next core */
            next_coreno = mcos_spinlock_searchnext((uint32_t)new_ticket.tickets.next_ticket, my_coreno);
            /* [PRQA_4393] Countermeasure for PRQA warning. */
            lcid = CPUNO2LCID(next_coreno);
            new_ticket.tickets.now_serving = (uint16_t)lcid;
        }
        else
        {
            new_ticket.spinlock = 0U;
        }
        new_spinlock = new_ticket.spinlock;
        old_spinlock = old_ticket.spinlock;

        read_spinlock = mcos_spinlock_compare_and_swap(&lockobj->ticket, new_spinlock, old_spinlock);
    }
    while (read_spinlock != old_spinlock);
}

 /*--------------------------------------------------------------------------
  mcos_spinlock_try_to_get_inline
    try to get spinlock
  Input     :   lockobj    pointer to lock object
  Output    :   none
  Return    :   mcos_true on success, mcos_false on failure
  Note  :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE mcos_bool_t
mcos_spinlock_try_to_get_inline(
    mcos_spinlock_obj_t * const lockobj)
{
    uint32_t    my_coreno;
    int32_t     lcid;
    mcos_bool_t ret;

    my_coreno = (uint32_t)(hal_cpu_getCoreNumber());
    /* [PRQA_4393] Countermeasure for PRQA warning. */
    lcid = CPUNO2LCID(my_coreno);

    /* update ticket if spinlock is 0 */
    ret = mcos_spinlock_conditional_write(&lockobj->ticket, ((uint32_t)lcid | (1UL << (my_coreno + BITOFFSET_NEXT_TICKET))));

    return ret;
}


 /*---------------------------------------------------------------------------
  mcos_spinlock_searchnext
     Search next core in next_ticket
  Input     :   next_ticket
            :   my_coreno
  Output    :   none
  Return    :   found core bit number
  Note  :   next_ticket must not be 0.
 ---------------------------------------------------------------------------*/
MCOS_INLINE uint32_t mcos_spinlock_searchnext(
    uint32_t next_ticket, uint32_t my_coreno)
{
    uint32_t    found_coreno;

    if (next_ticket > ((uint32_t)1U << my_coreno))
    {
        next_ticket = (next_ticket >> (my_coreno + (uint32_t)1U));
        found_coreno = my_coreno + (uint32_t)1U;
    }
    else
    {
        found_coreno = 0U;
    }

    while(1)
    {
        if ((next_ticket & (uint32_t)0x00000001) != 0U)
        {
            break;
        }
        else
        {
            /* Nothing to do */
        }
        next_ticket = (next_ticket >> 1U);
        found_coreno++;
    }
    return found_coreno;
}

#endif /* MCOS_AUTOSAR */

#endif /* #ifndef MCOS_V850_SPINLOCK_H */
