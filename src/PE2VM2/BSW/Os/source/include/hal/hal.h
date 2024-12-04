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
[ hal.h ] - HAL interfaces
****************************************************************************/
#ifndef HAL_H
#define HAL_H

#if defined __cplusplus
extern "C"
{
#endif /* #if defined __cplusplus */

#include <hal/hal_basic.h>
#include <hal/hal_cpu.h>
#include <ar_sys/stdlib.h>
#include <hal/hal_cache.h>

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

extern void hal_hw_initializeMaster(void);
extern void hal_hw_initializeSlave(hal_int_t coreid);

extern hal_int_t hal_cpu_getCoreNumber(void);
extern void hal_cpu_loop(hal_uint_t count);
/* hal_cpu_xxx() should be declared in hal_<arch>_cpu.h */

extern hal_error_t hal_pic_disableInt(const hal_int_t intno);
extern hal_error_t hal_pic_enableInt(const hal_int_t intno);
extern hal_error_t hal_pic_clearInt(const hal_int_t intno);
extern hal_error_t hal_pic_clearPendingInt(const hal_int_t intno);
extern hal_error_t hal_pic_setIntPriority(hal_int_t intno, hal_int_t priority);
extern hal_error_t hal_pic_isIntEnabled(hal_int_t intno, hal_bool_t *enabled);
extern void hal_pic_getInfo(hal_pic_info_t *info);

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"


/* BIOS compatibility definitions for eMCOS codes */
#define bios_int_t                      hal_int_t
#define bios_uint_t                     hal_uint_t
#define bios_pic_info_t                 hal_pic_info_t
#define bios_addr_t                     hal_uint_t

#define bios_mp_getCurrent()            hal_cpu_getCoreNumber()
#define bios_cpu_loop(count)            hal_cpu_loop(count)
#define bios_cpu_lockInt()              hal_cpu_lockInt()
#define bios_cpu_unlockInt(sr)          hal_cpu_unlockInt(sr)
#define bios_cpu_getIntPriority(pri)    hal_cpu_getIntPriority(pri)
#define bios_cpu_setIntPriority(pri)    hal_cpu_setIntPriority(pri)
#define bios_cpu_enableAllInt()         hal_cpu_enableAllInt()
#define bios_cpu_disableAllInt()        hal_cpu_disableAllInt()
#define bios_cpu_lockAllInt()           hal_cpu_lockAllInt()
#define bios_cpu_unlockAllInt(sr)       hal_cpu_unlockAllInt(sr)
#define bios_cpu_is_lockAllInt()        hal_cpu_is_lockAllInt()
#define bios_cpu_getCurrentIntPriority() \
                                        hal_cpu_getCurrentIntPriority()
#define bios_pic_disableInt(info)       hal_pic_disableInt(info)
#define bios_pic_enableInt(info)        hal_pic_enableInt(info)
#define bios_pic_clearInt(info)         hal_pic_clearInt(info)
#define bios_pic_setIntPriority(intno, pri) \
                                        hal_pic_setIntPriority(intno, pri)
#define bios_pic_isIntEnabled(intno, enabled) \
                                        hal_pic_isIntEnabled(intno, enabled)
#define bios_pic_about(info)            hal_pic_getInfo(info)
#define bios_cache_purge(addr, size)    hal_cache_purge(addr, size)

#if defined __cplusplus
} /* extern "C" */
#endif /* #if defined __cplusplus */

#endif /* #define HAL_H */
