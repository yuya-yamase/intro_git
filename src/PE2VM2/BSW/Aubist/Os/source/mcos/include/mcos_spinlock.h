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
[mcos_spinlock.h] - MCOS spinlock common interfaces
****************************************************************************/
#ifndef MCOS_SPINLOCK_H
#define MCOS_SPINLOCK_H

#if !MCOS_AUTOSAR
#error "Non-autosar is not supported."
#else /* #if !MCOS_AUTOSAR */

#include "mcos_basic.h"
#include "Os_internal.h"

/* spinlock object */
struct mcos_spinlock_obj_st;
typedef struct mcos_spinlock_obj_st mcos_spinlock_obj_t;


#if AR_OS_USE_MULTICORE == STD_ON

/* initialize spinlock */
void mcos_spinlock_init(
    mcos_spinlock_obj_t * const lockobj);

#if !MCOS_AUTOSAR
/* get spinlock */
void mcos_spinlock_get(
    mcos_spinlock_obj_t * const lockobj);
#endif /* #if !MCOS_AUTOSAR */

/* release spinlock */
void mcos_spinlock_release(
    mcos_spinlock_obj_t * const lockobj);

/* try to get spinlock */
mcos_bool_t mcos_spinlock_try_to_get(
    mcos_spinlock_obj_t * const lockobj);

/* get spinlock, enable interrupts while spin-wait (only for AUTOSAR) */
void mcos_spinlock_get_enaint(
    mcos_spinlock_obj_t * const lockobj);

#else /* AR_OS_USE_MULTICORE == STD_ON */
MCOS_INLINE void mcos_spinlock_init(const mcos_spinlock_obj_t * const lockobj);
#if !MCOS_AUTOSAR
MCOS_INLINE void mcos_spinlock_get(mcos_spinlock_obj_t * const lockobj);
#endif /* #if !MCOS_AUTOSAR */
MCOS_INLINE void mcos_spinlock_release(const mcos_spinlock_obj_t * const lockobj);
MCOS_INLINE mcos_bool_t mcos_spinlock_try_to_get(const mcos_spinlock_obj_t * const lockobj);
MCOS_INLINE void mcos_spinlock_get_enaint(const mcos_spinlock_obj_t * const lockobj);

/* initialize spinlock */
MCOS_INLINE void mcos_spinlock_init(
    const mcos_spinlock_obj_t * const lockobj)
{
    (void)lockobj; /* 'lockobj' is not used in this function. */
}

#if !MCOS_AUTOSAR
/* get spinlock */
MCOS_INLINE void mcos_spinlock_get(
    mcos_spinlock_obj_t * const lockobj)
{
    (void)lockobj; /* 'lockobj' is not used in this function. */
}
#endif /* #if !MCOS_AUTOSAR */

/* release spinlock */
MCOS_INLINE void mcos_spinlock_release(
    const mcos_spinlock_obj_t * const lockobj)
{
    (void)lockobj; /* 'lockobj' is not used in this function. */
}

/* try to get spinlock */
MCOS_INLINE mcos_bool_t mcos_spinlock_try_to_get(
    const mcos_spinlock_obj_t * const lockobj)
{
    (void)lockobj; /* 'lockobj' is not used in this function. */
    return ((mcos_bool_t)mcos_true);
}

/* get spinlock, enable interrupts while spin-wait */
MCOS_INLINE void mcos_spinlock_get_enaint(
    const mcos_spinlock_obj_t * const lockobj)
{
    (void)lockobj; /* 'lockobj' is not used in this function. */
}

#endif /* #if AR_OS_USE_MULTICORE == STD_ON */

#endif /* #if !MCOS_AUTOSAR */

#endif /* #ifndef MCOS_SPINLOCK_H */
