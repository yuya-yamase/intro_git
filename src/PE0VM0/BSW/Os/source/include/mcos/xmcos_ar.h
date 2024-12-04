/*
    Copyright (C) 2011 By eSOL Co.,Ltd. Tokyo, Japan

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
[xmcos_ar.h] - MCOS interface header
****************************************************************************/
#ifndef XMCOS_AR_H
#define XMCOS_AR_H

#include "mcos/mcos_refresh.h"

#if defined __ghs__
#if defined __Tricore

#define XMCOS_AR_USE_APPLICATION_CHANGED    STD_OFF
#define XMCOS_AR_BIND_INT_IN_EACH_CORE      STD_ON
#define XMCOS_AR_USE_SVC_THUNK              STD_OFF
#include "tc162/xmcos_ar_tc162.h"

#elif defined __ARM__

#define XMCOS_AR_USE_APPLICATION_CHANGED    STD_ON
#define XMCOS_AR_BIND_INT_IN_EACH_CORE      STD_ON
#define XMCOS_AR_USE_SVC_THUNK              STD_ON

#include "armv7m/xmcos_ar_armv7m.h"
#include "armv7m/xmcos_ar_cyt2b.h"

#elif defined __V850__
#define XMCOS_AR_USE_APPLICATION_CHANGED    STD_OFF
#define XMCOS_AR_BIND_INT_IN_EACH_CORE      STD_ON
#define XMCOS_AR_USE_SVC_THUNK              STD_OFF

#include "v850/xmcos_ar_v850.h"

#endif /* defined __V850__ */

#elif defined __ARMCC_VERSION /* defined __ghs__ */
#if (__ARM_ARCH == 8U) && (__ARM_ARCH_PROFILE == 'R')
#include "armv8r/xmcos_ar_armv8r.h"
#define XMCOS_AR_USE_APPLICATION_CHANGED    STD_OFF
#define XMCOS_AR_BIND_INT_IN_EACH_CORE      STD_OFF
#define XMCOS_AR_USE_SVC_THUNK              STD_OFF

#else
#error Unknown target ARM architecture
#endif

#else
#error Unknown compiler
#endif /* defined __ARMCC_VERSION */

#ifdef __cplusplus
extern "C"
{
#endif

extern mcos_refresh_err_t xmcos_ar_refresh_registers_others(
    mcos_id_t mycore_lcid, boolean should_fix);

#if (AR_OS_USE_MULTICORE == STD_ON)
extern mcos_refresh_err_t xmcos_ar_refresh_registers_osisr(
    mcos_id_t mycore_lcid, boolean should_fix);

#endif /* (AR_OS_USE_MULTICORE == STD_ON) */

extern mcos_refresh_err_t xmcos_ar_refresh_registers_isr(mcos_id_t mycore_lcid,
    mcos_id_t target_lcid, uint32_t int_no, int32_t int_priority, boolean should_fix);
extern void xmcos_ar_ici_init(mcos_id_t lcid);
extern void xmcos_ar_ici_raise(mcos_id_t lcid);



#ifdef __cplusplus
}
#endif

#endif /* #ifndef XMCOS_AR_H */
