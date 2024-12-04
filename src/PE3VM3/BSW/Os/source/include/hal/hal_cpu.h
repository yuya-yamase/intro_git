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
[ hal_cpu.h ] - HAL CPU interfaces
****************************************************************************/
#ifndef HAL_CPU_H
#define HAL_CPU_H

/* If the number of BSP increase, it is a need to consider using a macro. */
#if defined __ghs__
#if defined __V850__
#include "cpu/v850/hal_v850_cpu.h"
#elif defined __Tricore /* #if defined __V850__ */
#include "cpu/tc162/hal_tc162_cpu.h"
#elif defined __ARM__ /* #elif defined __Tricore */
#include "cpu/armv7m/hal_armv7m_cpu.h"
#endif /* #elif defined __ARM__ */
#elif defined __GNUC__ && !defined __ARMCC_VERSION /* define __ghs__ */
#if defined __V850__
#include "cpu/v850/hal_v850_cpu.h"
#elif defined __tile__ /* #if defined __V850__ */
#include "tile/hal_tile_cpu.h"
#elif defined __K1__ /* #elif defined __tile__ */
#include "kalray1/hal_kalray1_cpu.h"
#elif defined __MICROBLAZE__ /* #elif defined __K1__ */
#include "microblaze/hal_microblaze_cpu.h"
#elif defined __arm__ /* #elif defined __MICROBLAZE__ */
#include "arm/hal_arm_cpu.h"
#else /* #elif defined __arm__ */
#endif /* #else */
#elif defined __ARMCC_VERSION /* define __GNUC__ && !defined __ARMCC_VERSION */
#include "cpu/armv8r/hal_armv8r_cpu.h"
#endif

#endif /* #ifndef HAL_CPU_H */
