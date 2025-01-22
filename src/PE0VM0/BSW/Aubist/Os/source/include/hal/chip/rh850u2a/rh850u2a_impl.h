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
[ rh850u2a_impl.h ] - RH850U2A implementation header file
****************************************************************************/
#ifndef RH850U2A_IMPL_H
#define RH850U2A_IMPL_H

#include <hal/chip/rh850u2a/rh850u2a.h>
#include <hal/cpu/v850/v850.h>

/*-------------------------------------------------------------------------
 UART(RLIN3n)
-------------------------------------------------------------------------*/
#define RH850U2A_RLIN3N_BASE(n) ((uint32_t)0xFFD28000UL + ((uint32_t)(n) * (uint32_t)0x200UL))

/*-------------------------------------------------------------------------
 PORT
-------------------------------------------------------------------------*/
#define RH850U2A_PORT_BASE      (0xFFD90000UL)

/*-------------------------------------------------------------------------
 OSTM
-------------------------------------------------------------------------*/
#define RH850U2A_OSTM_BASE        (0xFFBF0000UL)  /* OSTM0 Base Address */

#define RH850U2A_OSTMn_BASE(n)      ((uint32_t)RH850U2A_OSTM_BASE + ((uint32_t)(n) * (uint32_t)0x0100UL))

/*-------------------------------------------------------------------------
 Interrupt controller
-------------------------------------------------------------------------*/
#define RH850U2A_INTC_BASE      (0xFFFC0000UL)
#define RH850U2A_INTC_BASE32    (0xFFF80000UL)

#define RH850U2A_INTC1_INTNO_MIN    ((uint32_t)0)
#define RH850U2A_INTC1_INTNO_MAX    ((uint32_t)31)
#define RH850U2A_INTC1_NUM          ((uint32_t)32)  /* 0..31 */
#define RH850U2A_INTC2_INTNO_MIN    ((uint32_t)32)
#define RH850U2A_INTC2_INTNO_MAX    ((uint32_t)767)
#define RH850U2A_INTC2_NUM          ((uint32_t)RH850U2A_INTC2_INTNO_MAX - (uint32_t)RH850U2A_INTC1_INTNO_MAX)  /* 32..767 */

/*-------------------------------------------------------------------------
 Clock controller
-------------------------------------------------------------------------*/
#define RH850U2A_CLKCTL_ISO_BASE    (0xFF980000UL)
#define RH850U2A_CLKCTL_AWO_BASE    (0xFF988000UL)

/*-------------------------------------------------------------------------
 Very-Low-Voltage Detection
-------------------------------------------------------------------------*/
#define RH850U2A_VLVDC_BASE     (0xFFF80980UL)

/*-------------------------------------------------------------------------
 Register protection
-------------------------------------------------------------------------*/
/*** Register protection ***/

/* module; CLKAn */
#define RH850U2A_PROT_CLKKCPROT1    (0xFF980700UL)

/* modue: PORT0 */
#define RH850U2A_PROT_JPPCMD0       (0xFFC204C0UL)
#define RH850U2A_PROT_PPCMD0        (0xFFC14C00UL)
#define RH850U2A_PROT_PPCMD1        (0xFFC14C04UL)
#define RH850U2A_PROT_PPCMD2        (0xFFC14C08UL)
#define RH850U2A_PROT_PPCMD3        (0xFFC14C0CUL)
#define RH850U2A_PROT_PPCMD8        (0xFFC14C20UL)
#define RH850U2A_PROT_JPPS0         (0xFFC204B0UL)
#define RH850U2A_PROT_PPS0          (0xFFC14B00UL)
#define RH850U2A_PROT_PPS1          (0xFFC14B04UL)
#define RH850U2A_PROT_PPS2          (0xFFC14B08UL)
#define RH850U2A_PROT_PPS3          (0xFFC14B0CUL)
#define RH850U2A_PROT_PPS8          (0xFFC14B20UL)

/* modue: PORT1 */
#define RH850U2A_PROT_PPCMD9        (0xFFC14C24UL)
#define RH850U2A_PROT_PPCMD10       (0xFFC14C28UL)
#define RH850U2A_PROT_PPCMD11       (0xFFC14C2CUL)
#define RH850U2A_PROT_PPCMD12       (0xFFC14C30UL)
#define RH850U2A_PROT_PPCMD13       (0xFFC14C34UL)
#define RH850U2A_PROT_PPCMD18       (0xFFC14C48UL)
#define RH850U2A_PROT_PPCMD19       (0xFFC14C4CUL)
#define RH850U2A_PROT_PPCMD20       (0xFFC14C50UL)
#define RH850U2A_PROT_PPCMD21       (0xFFC14C54UL)
#define RH850U2A_PROT_PPCMD22       (0xFFC14C58UL)
#define RH850U2A_PROT_PPS9          (0xFFC14B24UL)
#define RH850U2A_PROT_PPS10         (0xFFC14B28UL)
#define RH850U2A_PROT_PPS11         (0xFFC14B2CUL)
#define RH850U2A_PROT_PPS12         (0xFFC14B30UL)
#define RH850U2A_PROT_PPS13         (0xFFC14B34UL)
#define RH850U2A_PROT_PPS18         (0xFFC14B48UL)
#define RH850U2A_PROT_PPS19         (0xFFC14B4CUL)
#define RH850U2A_PROT_PPS20         (0xFFC14B50UL)
#define RH850U2A_PROT_PPS21         (0xFFC14B54UL)
#define RH850U2A_PROT_PPS22         (0xFFC14B58UL)

/* modue: SVM */
#define RH850U2A_PROT_PROT_CMDCVM   (0xFFF83200UL)
#define RH850U2A_PROT_PROT_SCVM     (0xFFF83204UL)

/* module: FLMD */
#define RH850U2A_PROT_FLMDPCMD      (0xFFA00004UL)
#define RH850U2A_PROT_FLMDPS        (0xFFA00008UL)


#endif /* #ifndef RH850U2A_IMPL_H */
