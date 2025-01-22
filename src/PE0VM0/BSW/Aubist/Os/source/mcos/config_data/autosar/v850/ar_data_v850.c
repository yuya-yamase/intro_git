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
[ar_data_v850.c] -  eMCOS AUTOSAR data for RH850G4MH
****************************************************************************/

#include "ar_chklib_v850.h"
#include "ar_data_local.h"
#include "ar_ioc_local.h"

/****************************************************************************
 * Check library
 ****************************************************************************/

/*sc1.mc.notrace library */
#if ((AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_OFF) \
  && (AR_OS_USE_MULTICORE == STD_ON) \
  && (MCOS_CFG_DS_TRACE_ENABLE == 0))

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

const uint8 * const ar_libchk_data= &ar_chklib_sc1_mc_notrace_v850;

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/* sc1.mc.trace._v850.a */
#elif ((AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_OFF) \
  && (AR_OS_USE_MULTICORE == STD_ON) \
  && (MCOS_CFG_DS_TRACE_ENABLE == 1))

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

const uint8 * const ar_libchk_data= &ar_chklib_sc1_mc_trace_v850;

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/*sc1.sc.notrace library */
#elif ((AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_OFF) \
  && (AR_OS_USE_MULTICORE == STD_OFF) \
  && (MCOS_CFG_DS_TRACE_ENABLE == 0))

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

const uint8 * const ar_libchk_data= &ar_chklib_sc1_sc_notrace_v850;

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/* sc1.sc.trace library */
#elif ((AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_OFF) \
  && (AR_OS_USE_MULTICORE == STD_OFF) \
  && (MCOS_CFG_DS_TRACE_ENABLE == 1))

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

const uint8 * const ar_libchk_data= &ar_chklib_sc1_sc_trace_v850;

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/*sc3.mc.nostkmon.notrace library */
#elif ((AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) \
  && (AR_OS_USE_MULTICORE == STD_ON) \
  && (AR_OS_USE_STACKMONITORING == STD_OFF) \
  && (MCOS_CFG_DS_TRACE_ENABLE == 0))

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

const uint8 * const ar_libchk_data= &ar_chklib_sc3_mc_nostkmon_notrace_v850;

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/* sc3.mc.nostkmon.trace library */
#elif ((AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) \
  && (AR_OS_USE_MULTICORE == STD_ON) \
  && (AR_OS_USE_STACKMONITORING == STD_OFF) \
  && (MCOS_CFG_DS_TRACE_ENABLE == 1))

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

const uint8 * const ar_libchk_data= &ar_chklib_sc3_mc_nostkmon_trace_v850;

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/*sc3.mc.stkmon.notrace library */
#elif ((AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) \
  && (AR_OS_USE_MULTICORE == STD_ON) \
  && (AR_OS_USE_STACKMONITORING == STD_ON) \
  && (MCOS_CFG_DS_TRACE_ENABLE == 0))

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

const uint8 * const ar_libchk_data= &ar_chklib_sc3_mc_stkmon_notrace_v850;

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/* sc3.mc.stkmon.trace library */
#elif ((AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) \
  && (AR_OS_USE_MULTICORE == STD_ON) \
  && (AR_OS_USE_STACKMONITORING == STD_ON) \
  && (MCOS_CFG_DS_TRACE_ENABLE == 1))

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

const uint8 * const ar_libchk_data= &ar_chklib_sc3_mc_stkmon_trace_v850;

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/*sc3.sc.nostkmon.notrace library */
#elif ((AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) \
  && (AR_OS_USE_MULTICORE == STD_OFF) \
  && (AR_OS_USE_STACKMONITORING == STD_OFF) \
  && (MCOS_CFG_DS_TRACE_ENABLE == 0))

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

const uint8 * const ar_libchk_data= &ar_chklib_sc3_sc_nostkmon_notrace_v850;

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/* sc3.sc.nostkmon.trace library */
#elif ((AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) \
  && (AR_OS_USE_MULTICORE == STD_OFF) \
  && (AR_OS_USE_STACKMONITORING == STD_OFF) \
  && (MCOS_CFG_DS_TRACE_ENABLE == 1))

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

const uint8 * const ar_libchk_data= &ar_chklib_sc3_sc_nostkmon_trace_v850;

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/* sc3.sc.stkmon.notrace library */
#elif ((AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) \
  && (AR_OS_USE_MULTICORE == STD_OFF) \
  && (AR_OS_USE_STACKMONITORING == STD_ON) \
  && (MCOS_CFG_DS_TRACE_ENABLE == 0))

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

const uint8 * const ar_libchk_data= &ar_chklib_sc3_sc_stkmon_notrace_v850;

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/* sc3.sc.stkmon.trace library */
#elif ((AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) \
  && (AR_OS_USE_MULTICORE == STD_OFF) \
  && (AR_OS_USE_STACKMONITORING == STD_ON) \
  && (MCOS_CFG_DS_TRACE_ENABLE == 1))

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

const uint8 * const ar_libchk_data= &ar_chklib_sc3_sc_stkmon_trace_v850;

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#endif


#if (AR_OS_EXIST_IOC == STD_ON)
#if (AR_OS_USE_MULTICORE == STD_ON)

#define OS_START_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_256
#include "Os_MemMap.h"

ar_ioc_lock_t ar_ioc_lock[AR_OS_NUM_IOC_COMMUNICATIONS];

#define OS_STOP_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_256
#include "Os_MemMap.h"

#else /* #if (AR_OS_USE_MULTICORE == STD_ON) */

#define NUM_AR_IOC_LOCK_1  1U

#define OS_START_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_256
#include "Os_MemMap.h"

ar_ioc_lock_t ar_ioc_lock[NUM_AR_IOC_LOCK_1];

#define OS_STOP_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_256
#include "Os_MemMap.h"

#endif /* #if (AR_OS_USE_MULTICORE == STD_ON) */
#endif /* #if (AR_OS_EXIST_IOC == STD_ON) */
