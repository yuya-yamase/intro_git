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
[ mcos_ds_impl.h ] - MCOS debug support header
****************************************************************************/
#ifndef MCOS_DS_IMPL_H
#define MCOS_DS_IMPL_H

#include "mcos/mcos_ds.h"
#include "mcos_basic.h"

#define MCOS_TEST_DS_PRFM_MODE_NONE         0U
#define MCOS_TEST_DS_PRFM_MODE_STANDARD     1U
#define MCOS_TEST_DS_PRFM_MODE_DETAILED     2U

/* set dependency value */
#if MCOS_CFG_DS_PRINT_ENABLE       || \
    MCOS_CFG_DS_SYSLOG_ENABLE      || \
    MCOS_CFG_DS_TRACE_ENABLE       || \
    MCOS_CFG_DS_USED_MEMORY_ENABLE || \
    MCOS_CFG_DS_TIME_ENABLE        || \
    MCOS_CFG_DS_LOADPERF_ENABLE
#define MCOS_DS_ENABLE                      1U
#else /* MCOS_CFG_DS_*_ENABLE */
#define MCOS_DS_ENABLE                      0U
#endif /* MCOS_CFG_DS_*_ENABLE */

#if !MCOS_CFG_DS_PRINT_ENABLE
#undef MCOS_CFG_DS_SYSLOG_ENABLE
#define MCOS_CFG_DS_SYSLOG_ENABLE           0U
#endif /* !MCOS_CFG_DS_PRINT_ENABLE */

#if !MCOS_CFG_DS_SYSLOG_ENABLE
#undef MCOS_CFG_DS_SYSLOG_LEVEL
#define MCOS_CFG_DS_SYSLOG_LEVEL            0U
#endif /* !MCOS_CFG_DS_SYSLOG_ENABLE */

#if !MCOS_CFG_DS_TRACE_ENABLE
#undef MCOS_CFG_DS_TRACE_LEVEL
#define MCOS_CFG_DS_TRACE_LEVEL             0U
#endif /* !MCOS_CFG_DS_TRACE_ENABLE */

#if !MCOS_CFG_DS_TIME_ENABLE
#undef MCOS_CFG_DS_LOADPERF_ENABLE
#define MCOS_CFG_DS_LOADPERF_ENABLE         0U
#undef MCOS_TEST_DS_PRFM
#define MCOS_TEST_DS_PRFM                   MCOS_TEST_DS_PRFM_MODE_NONE
#else /* !MCOS_CFG_DS_TIME_ENABLE */
    #if ((MCOS_TEST_DS_PRFM != MCOS_TEST_DS_PRFM_MODE_NONE) && (MCOS_TEST_DS_PRFM != MCOS_TEST_DS_PRFM_MODE_STANDARD) && (MCOS_TEST_DS_PRFM != MCOS_TEST_DS_PRFM_MODE_DETAILED))
    #error Invalid MCOS_TEST_DS_PRFM.
    #endif
#endif /* !MCOS_CFG_DS_TIME_ENABLE */

#if !MCOS_CFG_DS_TRACE_ENABLE
#undef MCOS_CFG_DS_TRACE_LOG_API
#undef MCOS_CFG_DS_TRACE_LOG_INT
#undef MCOS_CFG_DS_TRACE_LOG_EXC
#undef MCOS_CFG_DS_TRACE_LOG_THR
#undef MCOS_CFG_DS_TRACE_LOG_THRSWT
#undef MCOS_CFG_DS_TRACE_LOG_THRMGR
#define MCOS_CFG_DS_TRACE_LOG_API           0U
#define MCOS_CFG_DS_TRACE_LOG_INT           0U
#define MCOS_CFG_DS_TRACE_LOG_EXC           0U
#define MCOS_CFG_DS_TRACE_LOG_THR           0U
#define MCOS_CFG_DS_TRACE_LOG_THRSWT        0U
#define MCOS_CFG_DS_TRACE_LOG_THRMGR        0U
#endif /* !MCOS_CFG_DS_TRACE_ENABLE */

/* Check specified value */
#if MCOS_CFG_DS_TRACE_COUNT_DEFAULT <= 0U
#error The value of MCOS_CFG_DS_TRACE_COUNT_DEFAULT is out of range.
#endif /* MCOS_CFG_DS_TRACE_COUNT_DEFAULT */

#if ((MCOS_CFG_DS_TRACE_BUFFER_USE_CORELM < 0U) || \
    (MCOS_CFG_DS_TRACE_BUFFER_USE_CORELM > 1U))
#error The value of MCOS_CFG_DS_TRACE_BUFFER_USE_CORELM is out of range.
#endif /* MCOS_CFG_DS_TRACE_BUFFER_USE_CORELM */


#if defined __GNUC__
#if defined __V850__
#include "arch/v850/mcos_ds_v850.h"
#elif defined __tile__ /* #if defined __V850__ */
#include "arch/tile/mcos_ds_tile.h"
#elif defined __K1__ /* #elif defined __tile__ */
#include "arch/kalray1/mcos_ds_kalray1.h"
#elif defined __MICROBLAZE__ /* #elif defined __K1__ */
#include "arch/microblaze/mcos_ds_microblaze.h"
#elif defined __ARMCC_VERSION /* #elif defined __arm__ */
#include  "arch/armv8r/mcos_ds_armv8r.h" /* for armclang */
#elif defined __arm__ /* #elif defined __MICROBLAZE__ */
#include "arch/arm/mcos_ds_arm.h" /* for arm-gcc */
#elif defined __Tricore /* #if defined __ARMCC_VERSION */
#include "arch/tc162/mcos_ds_tc162.h"
#endif /* #else */
#elif defined __ghs__  /* #if defined __GNUC__ */
#if defined __V850__
#include "arch/v850/mcos_ds_v850.h"
#elif defined __Tricore /* #if defined __V850__ */
#include "arch/tc162/mcos_ds_tc162.h"
#elif defined __ARM__ /* #if defined __V850__ */
#include "arch/armv7m/mcos_ds_armv7m.h"
#endif /* #elif defined __ARM__ */
#endif /* #elif definede __ghs__ */

#if (!MCOS_AUTOSAR || MCOS_CFG_DS_TRACE_ENABLE)
#if MCOS_CFG_DS_INTERNAL_TRACE_ENABLE
/* debug support functions */
void mcos_ds_trace_apiEntry(uint8_t partID, int8_t objectKind, int16_t functionCode, int16_t objectID, mcos_uintptr_t pc);
void mcos_ds_trace_apiExit(uint8_t partID, int16_t functionCode, int16_t returnValue);
void mcos_ds_trace_interruptEntry(int16_t interruptNo, unsigned long epc);
void mcos_ds_trace_interruptExit(int16_t interruptNo);
void mcos_ds_trace_exceptionEntry(int16_t exceptionNo, unsigned long epc);
void mcos_ds_trace_exceptionExit(int16_t exceptionNo);
void mcos_ds_trace_threadEntry(int16_t threadID, mcos_uintptr_t pc);
void mcos_ds_trace_threadExit(int16_t threadID);
void mcos_ds_trace_threadSwitch(int16_t newThreadID, int16_t oldThreadID,
        uint8_t newPrio, uint8_t oldPrio, mcos_char_t* newName, mcos_char_t* oldName, uint32_t oldState);
void mcos_ds_trace_threadMigration(int16_t threadID, int16_t newCoreID, int16_t oldCoreID, uint8_t prio, mcos_char_t* name);
#endif /* #if MCOS_CFG_DS_INTERNAL_TRACE_ENABLE */
#endif /* #if (!MCOS_AUTOSAR || MCOS_CFG_DS_TRACE_ENABLE) */

#if IS_DS_SYSLOG_BOOT
void mcos_ds_print_types(void);
#else /* IS_DS_SYSLOG_BOOT */
#define mcos_ds_print_types()
#endif /* IS_DS_SYSLOG_BOOT */

/* user hook */
#if MCOS_CFG_DS_USERHOOK

#if MCOS_AUTOSAR
#define OS_START_SEC_CODE
#include "Os_MemMap.h"
#endif /* MCOS_AUTOSAR */

#if MCOS_AUTOSAR
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"
#endif /* MCOS_AUTOSAR */

#endif  /* #if MCOS_CFG_DS_USERHOOK */


#endif /* #ifndef MCOS_DS_IMPL_H */
