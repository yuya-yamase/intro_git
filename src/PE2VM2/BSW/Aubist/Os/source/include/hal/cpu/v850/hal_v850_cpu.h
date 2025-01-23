/*
    Copyright(C) 2019 eSOL Co., Ltd. All rights reserved.

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
[ hal_v850_cpu.h ] - HAL for v850 public interfaces for cpu
****************************************************************************/
#ifndef HAL_V850_CPU_H
#define HAL_V850_CPU_H

#include <stdint.h>
#include <hal/hal_impl.h>
#include <hal/cpu/v850/v850_cpp_impl.h>
#include <hal/cpu/v850/mcos/haldata_mcos_v850.h>

/*
 * Declare common HAL API functions
 */
extern hal_int_t hal_cpu_lockInt(void);
extern void hal_cpu_unlockInt(hal_int_t swbpri);
extern void hal_cpu_enableAllInt(void);
extern void hal_cpu_disableAllInt(void);
extern int32_t hal_cpu_lockAllInt(void);
extern void hal_cpu_unlockAllInt(int32_t locked);
extern hal_bool_t hal_cpu_is_lockAllInt(void);
extern int32_t hal_cpu_getCurrentIntPriority(void);
extern uint32_t hal_cpu_getIntPriority(void);
extern void hal_cpu_setIntPriority(uint32_t bpri);

#endif /* HAL_V850_CPU_H */
