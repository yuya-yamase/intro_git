/*
    Copyright (C) 2013 By eSOL Co.,Ltd. Tokyo, Japan

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
[ar_mcos_local.h] - MCOS AUTOSAR Layer internal interface
****************************************************************************/
#ifndef AR_MCOS_LOCAL_H
#define AR_MCOS_LOCAL_H

#include <mcos_mk.h>

/* include ar_util_<arch>_<compiler>.h */
#if defined __ghs__
#if defined __V850__
#include "v850/ar_util_v850_ghs.h"
#include "v850/ar_kernel_v850.h"
#elif defined __Tricore /* #if defined __V850__ */
#include "tc162/ar_util_tc162_ghs.h"
#elif defined __ARM__ /* #elif defined __Tricore */
#include "armv7m/ar_util_armv7m_ghs.h"
#include "armv7m/ar_kernel_armv7m.h"
#endif /* #elif defined __Tricore */
#elif defined __GNUC__ && !defined __ARMCC_VERSION  /* #if defined __ghs__ */
#if defined __V850__
#include "v850/ar_util_v850_gcc.h"
#include "v850/ar_kernel_v850.h"
#endif /* #if defined __V850__ */

#elif defined __ARMCC_VERSION  /* #if defined __GNUC__ && !defined __ARMCC_VERSION */
#if defined __arm__
#if __ARMCC_VERSION >= 6000000U
#include "armv8r/ar_util_armv8r_armclang.h"
#include "armv8r/ar_kernel_armv8r.h"
#else /* #if __ARMCC_VERSION >= 6000000U */
#include "arm/ar_util_arm_armct.h"
#endif /* #if __ARMCC_VERSION >= 6000000U */
#endif /* #if defined __arm__ */

#else /* #elif definede __ARMCC_VERSION */
    #error This compiler is not supported.
#endif /* #elif definede __ghs__ */


#ifdef __cplusplus
extern "C" {
#endif

#include "Os_internal.h"

typedef uint32  ar_intno_t;
typedef uint32  ar_atr_t;
typedef sint32  ar_pri_t;
typedef int     ar_critical_section_t;

typedef struct ar_cat1_int_config_st ar_cat1_int_config_t;
typedef struct ar_counter_config_st ar_counter_config_t;
typedef struct ar_countercb_st ar_countercb_t;
typedef struct ar_alarm_config_st ar_alarm_config_t;
typedef struct ar_alarmcb_st ar_alarmcb_t;
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
typedef struct ar_tfn_config_st ar_tfn_config_t;
#endif  /* #if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

AR_LOCAL_FORCE_INLINE void ar_memcpy(void * const dst, const void * const src, const uint32 sz);

/*---------------------------------------------------------------------------
  ar_memcpy

  Input     :   dst
            :   src
            :   sz
  Output    :   none
  Return    :   none
  Note  :   none
 ---------------------------------------------------------------------------*/
AR_LOCAL_FORCE_INLINE void ar_memcpy(
    void * const dst,
    const void * const src,
    const uint32 sz)
{
    uint8       * const tmp_dst = (uint8 *) dst;
    const uint8 * const tmp_src = (const uint8 *) src;
    uint32      i;

    for (i = 0U; i < sz; i++)
    {
        tmp_dst[i] = tmp_src[i];
    }
}


#ifdef __cplusplus
}
#endif

#endif /* AR_MCOS_LOCAL_H */

