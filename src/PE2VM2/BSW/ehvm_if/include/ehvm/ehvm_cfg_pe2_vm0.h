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
 [ ehvm_cfg_pe2_vm0.h ] - EHVM module's configuration data file
****************************************************************************/

#ifndef EHVM_CFG_PE2_VM0_H
#define EHVM_CFG_PE2_VM0_H

#include "ehvm_types.h"

/****************************************************************************
    macro definitions
****************************************************************************/

/* ehvm_vcc_transmit */
#define EHVM_TX_VCCID_VCCBUFFER_2_SLEEPSTATUS_VM2_TOMASTER ((ehvm_uint32_t)2U)
#define EHVM_TX_VCCID_VCCBUFFER_6_VM2_TOOTHERS ((ehvm_uint32_t)6U)
#define EHVM_TX_VCCID_VCCBUFFER_10_VM2_TOOTHERVM ((ehvm_uint32_t)10U)
#define EHVM_TX_VCCID_VCCBUFFER_14_VM2_TOVM3 ((ehvm_uint32_t)14U)
#define EHVM_TX_VCCID_VCC_SHARED_TX_VM2 ((ehvm_uint32_t)18U)

#define EHVM_TX_VCCID_VCCBUFFER_2_SLEEPSTATUS_VM2_TOMASTER_MAX ((ehvm_uint32_t)0x00000004U)
#define EHVM_TX_VCCID_VCCBUFFER_6_VM2_TOOTHERS_MAX ((ehvm_uint32_t)0x00000048U)
#define EHVM_TX_VCCID_VCCBUFFER_10_VM2_TOOTHERVM_MAX ((ehvm_uint32_t)0x00000004U)
#define EHVM_TX_VCCID_VCCBUFFER_14_VM2_TOVM3_MAX ((ehvm_uint32_t)0x00000004U)
#define EHVM_TX_VCCID_VCC_SHARED_TX_VM2_MAX ((ehvm_uint32_t)0x00000100U)

/* ehvm_vcc_receive */
#define EHVM_RX_VCCID_VCCBUFFER_0_SLEEPREQUEST_MASTER_TOSLAVE ((ehvm_uint32_t)0U)
#define EHVM_RX_VCCID_VCCBUFFER_4_VM0_TOOTHERS ((ehvm_uint32_t)4U)
#define EHVM_RX_VCCID_VCCBUFFER_5_VM1_TOOTHERS ((ehvm_uint32_t)5U)
#define EHVM_RX_VCCID_VCCBUFFER_7_VM3_TOOTHERS ((ehvm_uint32_t)7U)
#define EHVM_RX_VCCID_VCCBUFFER_8_VM0_TOOTHERVM ((ehvm_uint32_t)8U)
#define EHVM_RX_VCCID_VCCBUFFER_9_VM1_TOOTHERVM ((ehvm_uint32_t)9U)
#define EHVM_RX_VCCID_VCCBUFFER_11_VM3_TOOTHERVM ((ehvm_uint32_t)11U)
#define EHVM_RX_VCCID_VCCBUFFER_12_VM0_TOOTHERVM ((ehvm_uint32_t)12U)
#define EHVM_RX_VCCID_VCCBUFFER_15_VM3_TOVM1_2 ((ehvm_uint32_t)15U)
#define EHVM_RX_VCCID_VCC_SHARED_TX_VM0 ((ehvm_uint32_t)16U)
#define EHVM_RX_VCCID_VCC_SHARED_TX_VM1 ((ehvm_uint32_t)17U)
#define EHVM_RX_VCCID_VCC_SHARED_TX_VM3 ((ehvm_uint32_t)19U)
#define EHVM_RX_VCCID_VCC_IOHWAD_DATA_TX_VM0 ((ehvm_uint32_t)20U)

#define EHVM_RX_VCCID_VCCBUFFER_0_SLEEPREQUEST_MASTER_TOSLAVE_MAX ((ehvm_uint32_t)0x00000004U)
#define EHVM_RX_VCCID_VCCBUFFER_4_VM0_TOOTHERS_MAX ((ehvm_uint32_t)0x00000048U)
#define EHVM_RX_VCCID_VCCBUFFER_5_VM1_TOOTHERS_MAX ((ehvm_uint32_t)0x00000048U)
#define EHVM_RX_VCCID_VCCBUFFER_7_VM3_TOOTHERS_MAX ((ehvm_uint32_t)0x00000048U)
#define EHVM_RX_VCCID_VCCBUFFER_8_VM0_TOOTHERVM_MAX ((ehvm_uint32_t)0x00000004U)
#define EHVM_RX_VCCID_VCCBUFFER_9_VM1_TOOTHERVM_MAX ((ehvm_uint32_t)0x00000004U)
#define EHVM_RX_VCCID_VCCBUFFER_11_VM3_TOOTHERVM_MAX ((ehvm_uint32_t)0x00000004U)
#define EHVM_RX_VCCID_VCCBUFFER_12_VM0_TOOTHERVM_MAX ((ehvm_uint32_t)0x00000004U)
#define EHVM_RX_VCCID_VCCBUFFER_15_VM3_TOVM1_2_MAX ((ehvm_uint32_t)0x00000004U)
#define EHVM_RX_VCCID_VCC_SHARED_TX_VM0_MAX ((ehvm_uint32_t)0x00000100U)
#define EHVM_RX_VCCID_VCC_SHARED_TX_VM1_MAX ((ehvm_uint32_t)0x00000100U)
#define EHVM_RX_VCCID_VCC_SHARED_TX_VM3_MAX ((ehvm_uint32_t)0x00000100U)
#define EHVM_RX_VCCID_VCC_IOHWAD_DATA_TX_VM0_MAX ((ehvm_uint32_t)0x00000040U)

/* ehvm_vmm_clear_wakeup_factor,ehvm_vmm_enable_wakeup_factor,ehvm_vmm_disable_wakeup_factor */
#define EHVM_PE2_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_3  ((ehvm_uint32_t)3U)
#define EHVM_PE2_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_30  ((ehvm_uint32_t)30U)

/* ehvm_vwdt_set_mode,ehvm_vwdt_set_trigger_condition */

/* ehvm_vwdt_set_trigger_condition */

#endif /* EHVM_CFG_PE2_VM0_H */

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-2-0-z0001                                        */
/****************************************************************************/

