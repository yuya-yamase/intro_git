/*
    Copyright (C) 2014 eSOL Co.,Ltd. Tokyo, Japan

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
[ mcos_ltm.h ] - MCOS local time manager
****************************************************************************/
#ifndef MCOS_LTM_H
#define MCOS_LTM_H

#if !MCOS_AUTOSAR

#include "mcos_basic.h"

/* macro */
#define MCOS_UTIL_KTIME_ZERO    (0)

/* datatype */
typedef int64_t kernel_time_t;

/* function proto type */
MCOS_INLINE void mcos_util_ktime_to_stime(const kernel_time_t ktime, mcos_systime_t * const stime);
MCOS_INLINE kernel_time_t mcos_util_stime_to_ktime(const mcos_systime_t * const stime);
MCOS_INLINE kernel_time_t mcos_util_ktime_add_lower(const kernel_time_t a, const uint32_t lower);
MCOS_INLINE kernel_time_t mcos_util_ktime_add(const kernel_time_t a, const kernel_time_t b);
MCOS_INLINE kernel_time_t mcos_util_ktime_sub(const kernel_time_t a, const kernel_time_t b);
MCOS_INLINE int32_t mcos_util_ktime_compare(const kernel_time_t a, const kernel_time_t b);

/* function */
 /*---------------------------------------------------------------------------
  mcos_util_ktime_to_stime
     convert kernel_time_t to mcos_systime_t
  Input     :   ktime       input time (datatype is kernel_time_t)
  Output    :   stime       converted time (datatype is mcos_systime_t)
  Return    :   none
  Note  :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE void mcos_util_ktime_to_stime(
    const kernel_time_t ktime,
    mcos_systime_t * const stime)
{
    stime->upper = (int32_t)(((uint64_t)ktime) >> (uint64_t)32);
    stime->lower = (uint32_t)ktime;
}

 /*---------------------------------------------------------------------------
  mcos_util_stime_to_ktime
     convert mcos_systime_t to kernel_time_t
  Input     :   stime       input time (datatype is mcos_systime_t)
  Return    :   converted time (datatype is kernel_time_t)
  Note  :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE kernel_time_t mcos_util_stime_to_ktime(
    const mcos_systime_t * const stime)
{
    return (kernel_time_t)(((uint64_t)stime->upper << (uint64_t)32) | ((uint64_t)stime->lower));
}

 /*---------------------------------------------------------------------------
  mcos_util_ktime_add_lower
     time of a + b
  Input     :   a           input time a
  Input     :   lower       input time lower
  Return    :   result of a + lower
  Note  :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE kernel_time_t mcos_util_ktime_add_lower(
    const kernel_time_t a,
    const uint32_t lower)
{
    return a + (kernel_time_t)lower;
}

 /*---------------------------------------------------------------------------
  mcos_util_ktime_add
     time of a + b
  Input     :   a           input time a
  Input     :   b           input time b
  Return    :   result of a + b
  Note  :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE kernel_time_t mcos_util_ktime_add(
    const kernel_time_t a,
    const kernel_time_t b)
{
    return a + b;
}

 /*---------------------------------------------------------------------------
  mcos_util_ktime_sub
     time of a - b
  Input     :   a           input time a
  Input     :   b           input time b
  Return    :   result of a - b
  Note  :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE kernel_time_t mcos_util_ktime_sub(
    const kernel_time_t a,
    const kernel_time_t b)
{
    return a - b;
}

 /*---------------------------------------------------------------------------
  mcos_util_ktime_compare
     compare a and b
  Input     :   a           input time a
  Input     :   b           input time b
  Return    :   -1: (a < b), 0: (a == b), 1: (a > b)
  Note  :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE int32_t mcos_util_ktime_compare(
    const kernel_time_t a,
    const kernel_time_t b)
{
    const kernel_time_t sub = a - b;

    return (sub < (int64_t)0) ? (int32_t)-1 : ((sub > (int64_t)0) ? (int32_t)1 : (int32_t)0);
}

#endif /* #if !MCOS_AUTOSAR */

#endif /* #ifndef MCOS_LTM_H */
