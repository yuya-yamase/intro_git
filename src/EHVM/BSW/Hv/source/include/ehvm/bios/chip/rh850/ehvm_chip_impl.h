/*
    Copyright (C) 2022 eSOL Co.,Ltd. All rights reserved.

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
[ ehvm_chip_impl.h ] - RH850U2A implementation header file
****************************************************************************/
#ifndef EHVM_CHIP_IMPL_H
#define EHVM_CHIP_IMPL_H

#include <bios/ehvm_bios_basic_impl.h>
#include <bios/chip/rh850/ehvm_chip.h>
#include <bios/cpu/g4mh/ehvm_cpu_local.h>

/*-------------------------------------------------------------------------
 PORT
-------------------------------------------------------------------------*/
#define RH850U2A_PORT_BASE      (0xFFD90000U)

/*-------------------------------------------------------------------------
 Interrupt controller
-------------------------------------------------------------------------*/
#define RH850U2A_INTC_BASE      (0xFFFC0000U)
#define RH850U2A_INTC_BASE32    (0xFFF80000U)

#define RH850U2A_INTC1_INTNO_MIN    ((ehvm_uint32_t)RH850U2A_INTNO_0)
#define RH850U2A_INTC1_INTNO_MAX    ((ehvm_uint32_t)RH850U2A_INTNO_31)
#define RH850U2A_INTC1_NUM          ((ehvm_uint32_t)RH850U2A_INTC1_INTNO_MAX - (ehvm_uint32_t)RH850U2A_INTC1_INTNO_MIN + (ehvm_uint32_t)1U)
#define RH850U2A_INTC2_INTNO_MIN    ((ehvm_uint32_t)RH850U2A_INTNO_32)
#define RH850U2A_INTC2_INTNO_MAX    ((ehvm_uint32_t)RH850U2A_INTNO_MAX)
#define RH850U2A_INTC2_NUM          ((ehvm_uint32_t)RH850U2A_INTC2_INTNO_MAX - (ehvm_uint32_t)RH850U2A_INTC2_INTNO_MIN + (ehvm_uint32_t)1U)

/*-------------------------------------------------------------------------
 Clock controller
-------------------------------------------------------------------------*/
#define RH850U2A_CLKCTL_AWO_BASE    (0xFF988000U)

/*-------------------------------------------------------------------------
 Very-Low-Voltage Detection
-------------------------------------------------------------------------*/
#define RH850U2A_VLVDC_BASE     (0xFFF80980U)

/*-------------------------------------------------------------------------
 Register protection
-------------------------------------------------------------------------*/
/*** Register protection ***/

/* module; CLKAn */
#define RH850U2A_PROT_CLKKCPROT1    (0xFF980700U)

/* modue: PORT0 */
#define RH850U2A_PROT_JPPCMD0       (0xFFC204C0U)
#define RH850U2A_PROT_PPCMD0        (0xFFC14C00U)
#define RH850U2A_PROT_PPCMD1        (0xFFC14C04U)
#define RH850U2A_PROT_PPCMD2        (0xFFC14C08U)
#define RH850U2A_PROT_PPCMD3        (0xFFC14C0CU)
#define RH850U2A_PROT_PPCMD8        (0xFFC14C20U)
#define RH850U2A_PROT_JPPS0         (0xFFC204B0U)
#define RH850U2A_PROT_PPS0          (0xFFC14B00U)
#define RH850U2A_PROT_PPS1          (0xFFC14B04U)
#define RH850U2A_PROT_PPS2          (0xFFC14B08U)
#define RH850U2A_PROT_PPS3          (0xFFC14B0CU)
#define RH850U2A_PROT_PPS8          (0xFFC14B20U)

/* modue: PORT1 */
#define RH850U2A_PROT_PPCMD9        (0xFFC14C24U)
#define RH850U2A_PROT_PPCMD10       (0xFFC14C28U)
#define RH850U2A_PROT_PPCMD11       (0xFFC14C2CU)
#define RH850U2A_PROT_PPCMD12       (0xFFC14C30U)
#define RH850U2A_PROT_PPCMD13       (0xFFC14C34U)
#define RH850U2A_PROT_PPCMD18       (0xFFC14C48U)
#define RH850U2A_PROT_PPCMD19       (0xFFC14C4CU)
#define RH850U2A_PROT_PPCMD20       (0xFFC14C50U)
#define RH850U2A_PROT_PPCMD21       (0xFFC14C54U)
#define RH850U2A_PROT_PPCMD22       (0xFFC14C58U)
#define RH850U2A_PROT_PPS9          (0xFFC14B24U)
#define RH850U2A_PROT_PPS10         (0xFFC14B28U)
#define RH850U2A_PROT_PPS11         (0xFFC14B2CU)
#define RH850U2A_PROT_PPS12         (0xFFC14B30U)
#define RH850U2A_PROT_PPS13         (0xFFC14B34U)
#define RH850U2A_PROT_PPS18         (0xFFC14B48U)
#define RH850U2A_PROT_PPS19         (0xFFC14B4CU)
#define RH850U2A_PROT_PPS20         (0xFFC14B50U)
#define RH850U2A_PROT_PPS21         (0xFFC14B54U)
#define RH850U2A_PROT_PPS22         (0xFFC14B58U)

/* modue: SVM */
#define RH850U2A_PROT_PROT_CMDCVM   (0xFFF83200U)
#define RH850U2A_PROT_PROT_SCVM     (0xFFF83204U)

/* module: FLMD */
#define RH850U2A_PROT_FLMDPCMD      (0xFFA00004U)
#define RH850U2A_PROT_FLMDPS        (0xFFA00008U)

/*-------------------------------------------------------------------------
 Reset Controller
-------------------------------------------------------------------------*/
#define BOOT_CONTROL_BASE           (0xFFFB2000U)

#endif /* #ifndef EHVM_CHIP_IMPL_H */
