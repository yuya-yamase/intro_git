/*
    Copyright (C) 2013 eSOL Co.,Ltd. Tokyo, Japan

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
[ mcos_util.h ] - MCOS utility header
****************************************************************************/
#ifndef MCOS_UTIL_H
#define MCOS_UTIL_H

#if !MCOS_AUTOSAR

#include "mcos_basic.h"

typedef uint32_t mcos_bitmap_t;

#define MCOS_BITMAP_ARRAYSIZE(n) \
    (((n) + ((sizeof(mcos_bitmap_t) * 8) - 1)) / (sizeof(mcos_bitmap_t) * 8))

/* get highest bit */
uint32_t mcos_util_getHighestBit(uint32_t mk);

/* get lowest bit */
uint32_t mcos_util_getLowestBit(uint32_t mk);

/*
 * Convert thread id (based on MCOS_CFG_GLB_THR_PER_CORE_MAX*MCOS_CFG_GLB_CORE_PER_HWCL_MAX)
 * to thread index in tables, starting from 0 (based on TCB_CNT*MP_CONTROL_CORE_COUNT).
 * Valid only for migratable threads.
 */
MCOS_INLINE mcos_id_t mcos_util_tid_to_tindex(
    mcos_id_t tid)
{
    mcos_id_t lcid;

    tid = (mcos_id_t)((int32_t)tid - (int32_t)HWCL_BASE_MTID + (int32_t)1);
    lcid = (mcos_id_t)((((uint32_t)tid - (uint32_t)1) / (uint32_t)MCOS_CFG_GLB_THR_PER_CORE_MAX) + (uint32_t)1);

    return (mcos_id_t)((int32_t)tid
        + (((int32_t)lcid - (int32_t)1) * ((int32_t)MCOS_CFG_THR_MAX - (int32_t)MCOS_CFG_GLB_THR_PER_CORE_MAX))
        - (int32_t)1);
}

/* bitmap */
/* set value to bitmap */
MCOS_INLINE void
mcos_util_bitmap_set(
    /* bitmap data set */
    mcos_bitmap_t *bitmap,
    /* set index */
    uint32_t index)
{
    uint32_t ia, ib;

    ia = index / 32;
    ib = index % 32;
    bitmap[ia] = (bitmap[ia] | ((mcos_bitmap_t)0x01U << ib));
}

/* clear value from bitmap */
MCOS_INLINE void
mcos_util_bitmap_clear(
    /* bitmap data set */
    mcos_bitmap_t *bitmap,
    /* set index */
    uint32_t index)
{
    uint32_t ia, ib;

    ia = index / 32;
    ib = index % 32;
    bitmap[ia] = (bitmap[ia] & ~((mcos_bitmap_t)0x01U << ib));
}

/* get value from bitmap */
/* returns 0 or non-zero */
MCOS_INLINE uint32_t
mcos_util_bitmap_get(
    /* bitmap data set */
    const mcos_bitmap_t *bitmap,
    /* get index */
    uint32_t index)
{
    uint32_t ia, ib;

    ia = index / 32;
    ib = index % 32;
    return (bitmap[ia] & ((mcos_bitmap_t)0x01U << ib));
}

/* search '0' position from bitmap */
/* returns max(not found) or index */
MCOS_INLINE uint32_t
mcos_util_bitmap_search0(
    /* bitmap data set */
    const mcos_bitmap_t *bitmap,
    /* maximum number of index */
    uint32_t max)
{
    const mcos_bitmap_t *bm;
    uint32_t index;
    uint32_t offset;

    index = 0;
    bm = bitmap;
    while (index < max)
    {
        offset = mcos_util_getLowestBit(~(*bm));
        index += offset;
        if (offset != 32)
        {
            break;
        }
        ++bm;
    }

    return index;
}

/* search '1' position from bitmap */
/* returns max(not found) or index */
MCOS_INLINE uint32_t
mcos_util_bitmap_search1(
    /* bitmap data set */
    const mcos_bitmap_t *bitmap,
    /* maximum number of index */
    uint32_t max)
{
    const mcos_bitmap_t *bm;
    uint32_t index;
    uint32_t offset;

    index = 0;
    bm = bitmap;
    while (index < max)
    {
        offset = mcos_util_getLowestBit(*bm);
        index += offset;
        if (offset != 32)
        {
            break;
        }
        ++bm;
    }

    return index;
}

#if MCOS_HWCL
/*
 *  convert TID to HWCLID
 */
MCOS_INLINE mcos_id_t mcos_util_tid_to_hwclid(mcos_id_t tid)
{
   return (tid - 1) / MCOS_TID_HWCL + 1;
}
#endif /* MCOS_HWCL */

#endif /* #if !MCOS_AUTOSAR */

#endif /* #ifndef MCOS_UTIL_H */
