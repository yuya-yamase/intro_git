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
[inttypes.h] - AUTOSAR inttypes header
****************************************************************************/
#ifndef INTTYPES_H_AUTOSAR
#define INTTYPES_H_AUTOSAR

#if defined __ghs__
    #if defined __V850__
        #include "arch/v850/inttypes_v850_ghs.h"
    #elif defined __Tricore /* #if defined __V850__ */
        #include "arch/tc162/inttypes_tc162_ghs.h"
    #elif defined __ARM__ /* #elif defined __Tricore */
        #include "arch/armv7m/inttypes_armv7m_ghs.h"
    #else /* #elif defined __ARM__ */
        #error This archtecture is not supported for GHS.
    #endif /* #if defined __V850__ */

#elif defined __GNUC__ && !defined __ARMCC_VERSION  /* #if defined __ghs__ */
    #if defined __V850__
        #include "arch/v850/inttypes_v850_gcc.h"
    #else /* #elif defined __V850__ */
        #error This archtecture is not supported for GNUC.
    #endif /* #if defined __V850__ */

#elif defined __ARMCC_VERSION  /* #if defined defined __GNUC__ && !defined __ARMCC_VERSION */
    #if defined __arm__
        #if __ARMCC_VERSION >= 6000000U
            #include "arch/armv8r/inttypes_armv8r_armclang.h"
        #else /* #if __ARMCC_VERSION >= 6000000U */
            #include "arch/arm/inttypes_arm_armct.h"
        #endif /* #if __ARMCC_VERSION >= 6000000U */
    #elif defined __aarch64__
        #if __ARMCC_VERSION >= 6000000U
            #include "arch/arm/stdint_arm_armclang.h"
        #else /* #if __ARMCC_VERSION >= 6000000U */
            #include "arch/arm/stdint_arm_armct.h"
        #endif /* #if __ARMCC_VERSION >= 6000000U */
    #else /* #elif defined __aarch64__ */
        #error This archtecture is not supported for ARMCC.
    #endif /* #if defined __arm__ */

#else /* #elif definede __ARMCC_VERSION */
    #error This compiler is not supported.
#endif /* #else */


#endif  /* INTTYPES_H_AUTOSAR */
