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
[ar_counter.h] - Counter Information
****************************************************************************/

#ifndef AR_COUNTER_H
#define AR_COUNTER_H

#include <mcos_mk.h>

#define TICK_1          (1U)

#define IDX_LIMIT       (0)
#define IDX_LIMIT2      (1)
#define IDX_LIMIT_NUM   (2)

struct ar_counter_config_st {
    uint64_t        nanoseconds_per_tick;
    TickType        base;
    TickType        min_cycle;
    TickType        limit[IDX_LIMIT_NUM];
    const ar_osap_config_t  *p_osapconfig;
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
    const uint32    *osap_allowedmap;   /* Access allowed OSAP bitmap */
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
};

/***********************************************************************
 * ar_counter_target_t
 ***********************************************************************/
typedef union {
    /* alarm */
    ar_alarmcb_t                *alarmcb;

    /* other implementation */

} ar_counter_target_t;

/***********************************************************************
 * ar_counter_expire_info_t
 ***********************************************************************/
typedef struct ar_counter_expire_info_st ar_counter_expire_info_t;

typedef void (*ar_expire_func)(ar_counter_expire_info_t * const p_counter_info,
            const ar_countercb_t * const p_countercb);
            
struct ar_counter_expire_info_st {
    ar_counter_expire_info_t    *p_next;
    ar_counter_expire_info_t    *p_prev;
    ar_counter_target_t         target;
    TickType                    expire_tick;
    ar_expire_func              expire_func;
    uint32                      expire_pri;
};


/***********************************************************************
 * ar_countercb_st
 ***********************************************************************/
struct ar_countercb_st {
    ar_counter_expire_info_t    info;       /* only use p_next and p_prev */
    const ar_counter_config_t * p_config;
    TickType                    current_value;
    boolean                     is_busy;
};

#define AR_ALARM_ACTIVATETASK     (0x01U)
#define AR_ALARM_SETEVENT         (0x02U)
#define AR_ALARM_CALLBACK         (0x04U)
#define AR_ALARM_INCREMENTCOUNTER (0x08U)

#define AR_ALARM_ABSOLUTE         (0x10U)
#define AR_ALARM_RELATIVE         (0x20U)

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

extern TickType ar_counter_tick_rel(const ar_countercb_t * const p_countercb, const TickType relval);
extern TickType ar_counter_tick_abs(const ar_countercb_t * const p_countercb, const TickType absval);
extern void ar_counter_init(void);
extern void ar_counter_expire(const ar_countercb_t * const p_countercb, const CounterType cntid);

extern StatusType ar_act_incrementcounter(const CounterType counter_id,
    const ar_osap_config_t * const p_osapconfig);

extern StatusType ar_get_counter_value_impl(const CounterType counter_id,
        const TickRefType p_value, const ar_osap_config_t * const p_osapconfig);
extern StatusType ar_get_elapsed_value_impl(const CounterType counter_id,
        const TickRefType p_value, const TickRefType p_elapsed_value, const ar_osap_config_t * const p_osapconfig);

extern void ar_system_counter_start(void);
extern void ar_system_counter_stop(void);

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define AR_NXTVAL(info) (((ar_counter_expire_info_t *)(info))->expire_tick)
#define AR_EXPPRI(info) (((ar_counter_expire_info_t *)(info))->expire_pri)

AR_LOCAL_FORCE_INLINE void ar_counter_insert(ar_counter_expire_info_t * const p_counter_info, const ar_countercb_t * const p_countercb);
AR_LOCAL_FORCE_INLINE TickType ar_sum_ticks(const TickType tick1,
    const TickType tick2, const TickType limit);
AR_LOCAL_FORCE_INLINE TickType ar_sub_ticks(const TickType tick1,
    const TickType tick2, const TickType limit);
AR_LOCAL_FORCE_INLINE TickType ar_get_curval(
    const ar_countercb_t * const p_countercb);

AR_LOCAL_FORCE_INLINE void ar_counter_queue_init(ar_counter_expire_info_t * const info);
AR_LOCAL_FORCE_INLINE ar_counter_expire_info_t * ar_counter_queue_next(ar_counter_expire_info_t const * const info);
AR_LOCAL_FORCE_INLINE sint32 ar_counter_queue_size(ar_counter_expire_info_t const * const info);
AR_LOCAL_FORCE_INLINE void ar_counter_queue_insert(
    ar_counter_expire_info_t * const ins,
    ar_counter_expire_info_t * const next);
AR_LOCAL_FORCE_INLINE void ar_counter_queue_remove(ar_counter_expire_info_t * const unlink);

AR_LOCAL_FORCE_INLINE void ar_counter_insert(
    ar_counter_expire_info_t * const p_counter_info,
    const ar_countercb_t * const p_countercb)
{
    TickType    enqval, curval;
    const ar_counter_expire_info_t *head = &(p_countercb->info);
    ar_counter_expire_info_t *next;

    enqval = p_counter_info->expire_tick;
    curval = p_countercb->current_value;

    next = ar_counter_queue_next(head);

    /*
     * Search insert position
     *  queue is sorted by expire_tick, first is next expired item.
     */
    if (curval <= enqval)
    {
        /*
         * no overflow (current <= enq)
         *  current < next < enq  :   check next
         *  current = next < enq  :   check next
         *  current < next = enq  :   insert by pri
         *  current = next = enq  :   insert by pri
         *  current < enq  < next :   insert
         *  current = enq  < next :   insert
         *  next < current < enq  :   insert
         *  next < current = enq  :   insert
         */
        while ((next != head)
                && (((curval <= AR_NXTVAL(next)) && (AR_NXTVAL(next) < enqval))
                    || ((AR_NXTVAL(next) == enqval) && (AR_EXPPRI(p_counter_info) < AR_EXPPRI(next)))))
        {
            next = ar_counter_queue_next(next);
        }
    }
    else
    {
        /*
         * overflow (enq < current)
         *  enq < current < next  :   check next
         *  enq < current = next  :   check next
         *  enq < next < current  :   insert
         *  enq = next < current  :   insert by pri
         *  next < enq < current  :   check next
         */
        while ((next != head)
                && ((curval <= AR_NXTVAL(next))
                    || (AR_NXTVAL(next) < enqval)
                    || ((AR_NXTVAL(next) == enqval) && (AR_EXPPRI(p_counter_info) < AR_EXPPRI(next)))))
        {
            next = ar_counter_queue_next(next);
        }
    }

    ar_counter_queue_insert(p_counter_info, next);
}

AR_LOCAL_FORCE_INLINE TickType ar_sum_ticks(
    const TickType tick1,
    const TickType tick2,
    const TickType limit)
{
    TickType result;
    if (tick2 <= (limit - tick1))
    {
        result = tick1 + tick2;
    }
    else
    {
        result = (tick1 + tick2) - limit;
        result--;
    }
    return result;
}

AR_LOCAL_FORCE_INLINE TickType ar_sub_ticks(
    const TickType tick1,
    const TickType tick2,
    const TickType limit)
{
    TickType result;

    if (tick1 >= tick2)
    {
        result = tick1 - tick2;
    }
    else
    {
        result = (tick1 - tick2) + limit;
        result++;
    }
    return result;
}

AR_LOCAL_FORCE_INLINE TickType ar_get_curval(
    const ar_countercb_t * const p_countercb)
{
    TickType curval;

    curval = p_countercb->current_value;

    return curval;
}



AR_LOCAL_FORCE_INLINE void ar_counter_queue_init(ar_counter_expire_info_t * const info)
{
    info->p_next = info;
    info->p_prev = info;
}

AR_LOCAL_FORCE_INLINE ar_counter_expire_info_t * ar_counter_queue_next(ar_counter_expire_info_t const * const info)
{
    return info->p_next;
}

AR_LOCAL_FORCE_INLINE sint32 ar_counter_queue_size(ar_counter_expire_info_t const * const info)
{
    sint32 count;
    ar_counter_expire_info_t const *ptr;

    ptr = info->p_next;
    count = 0;
    while(ptr != info)
    {
        count++;
        ptr = ptr->p_next;
    }

    return count;
}

AR_LOCAL_FORCE_INLINE void ar_counter_queue_insert(
    ar_counter_expire_info_t * const ins,
    ar_counter_expire_info_t * const next)
{
    ins->p_next = next;
    ins->p_prev = next->p_prev;
    next->p_prev->p_next = ins;
    next->p_prev = ins;
}

AR_LOCAL_FORCE_INLINE void ar_counter_queue_remove(ar_counter_expire_info_t * const unlink)
{
    unlink->p_prev->p_next = unlink->p_next;
    unlink->p_next->p_prev = unlink->p_prev;
    unlink->p_next = unlink;
    unlink->p_prev = unlink;
}

#endif /* AR_COUNTER_H */
