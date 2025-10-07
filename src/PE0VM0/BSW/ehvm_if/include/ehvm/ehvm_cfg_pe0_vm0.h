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
 [ ehvm_cfg_pe0_vm0.h ] - EHVM module's configuration data file
****************************************************************************/

#ifndef EHVM_CFG_PE0_VM0_H
#define EHVM_CFG_PE0_VM0_H

#include "ehvm_types.h"

/****************************************************************************
    macro definitions
****************************************************************************/
/* ContextID for MasterVM */
#define EHVM_CONTEXTID_PE0_VM0 (EHVM_CONTEXT_ID_PE0_VM0)
#define EHVM_CONTEXTID_PE0_HV  (EHVM_CONTEXT_ID_PE0_HV)
#define EHVM_CONTEXTID_PE1_VM0 (EHVM_CONTEXT_ID_PE1_VM0)
#define EHVM_CONTEXTID_PE1_HV  (EHVM_CONTEXT_ID_PE1_HV)
#define EHVM_CONTEXTID_PE2_VM0 (EHVM_CONTEXT_ID_PE2_VM0)
#define EHVM_CONTEXTID_PE2_HV  (EHVM_CONTEXT_ID_PE2_HV)
#define EHVM_CONTEXTID_PE3_VM0 (EHVM_CONTEXT_ID_PE3_VM0)
#define EHVM_CONTEXTID_PE3_HV  (EHVM_CONTEXT_ID_PE3_HV)
#define EHVM_CONTEXTID_ALL     ((ehvm_uint8_t)0xFFU)

/* ehvm_em_err_msg_receive */
#define EHVM_CONTEXTID_PE0_VM0_EM_RX_DATAS_SIZE_MAX ((ehvm_uint32_t)0x00000020U)
#define EHVM_CONTEXTID_PE1_VM0_EM_RX_DATAS_SIZE_MAX ((ehvm_uint32_t)0x00000020U)
#define EHVM_CONTEXTID_PE2_VM0_EM_RX_DATAS_SIZE_MAX ((ehvm_uint32_t)0x00000020U)
#define EHVM_CONTEXTID_PE3_VM0_EM_RX_DATAS_SIZE_MAX ((ehvm_uint32_t)0x00000020U)

/* ehvm_sch_set_schedule_table */
#define EHVM_COREID_0_SCHEDULINGID_0 ((ehvm_uint8_t)0U)
#define EHVM_COREID_1_SCHEDULINGID_0 ((ehvm_uint8_t)0U)
#define EHVM_COREID_2_SCHEDULINGID_0 ((ehvm_uint8_t)0U)
#define EHVM_COREID_3_SCHEDULINGID_0 ((ehvm_uint8_t)0U)

/* ehvm_vcc_transmit */
#define EHVM_TX_VCCID_VCCBUFFER_0_SLEEPREQUEST_MASTER_TOSLAVE ((ehvm_uint32_t)0U)
#define EHVM_TX_VCCID_VCCBUFFER_4_VM0_TOOTHERS ((ehvm_uint32_t)4U)
#define EHVM_TX_VCCID_VCCBUFFER_8_VM0_TOOTHERVM ((ehvm_uint32_t)8U)
#define EHVM_TX_VCCID_VCCBUFFER_12_VM0_TOOTHERVM ((ehvm_uint32_t)12U)
#define EHVM_TX_VCCID_VCC_SHARED_TX_VM0 ((ehvm_uint32_t)16U)
#define EHVM_TX_VCCID_VCC_IOHWAD_DATA_TX_VM0 ((ehvm_uint32_t)20U)

#define EHVM_TX_VCCID_VCCBUFFER_0_SLEEPREQUEST_MASTER_TOSLAVE_MAX ((ehvm_uint32_t)0x00000004U)
#define EHVM_TX_VCCID_VCCBUFFER_4_VM0_TOOTHERS_MAX ((ehvm_uint32_t)0x00000048U)
#define EHVM_TX_VCCID_VCCBUFFER_8_VM0_TOOTHERVM_MAX ((ehvm_uint32_t)0x00000004U)
#define EHVM_TX_VCCID_VCCBUFFER_12_VM0_TOOTHERVM_MAX ((ehvm_uint32_t)0x00000004U)
#define EHVM_TX_VCCID_VCC_SHARED_TX_VM0_MAX ((ehvm_uint32_t)0x00000100U)
#define EHVM_TX_VCCID_VCC_IOHWAD_DATA_TX_VM0_MAX ((ehvm_uint32_t)0x00000040U)

/* ehvm_vcc_receive */
#define EHVM_RX_VCCID_VCCBUFFER_1_SLEEPSTATUS_VM1_TOMASTER ((ehvm_uint32_t)1U)
#define EHVM_RX_VCCID_VCCBUFFER_2_SLEEPSTATUS_VM2_TOMASTER ((ehvm_uint32_t)2U)
#define EHVM_RX_VCCID_VCCBUFFER_3_SLEEPSTATUS_VM3_TOMASTER ((ehvm_uint32_t)3U)
#define EHVM_RX_VCCID_VCCBUFFER_5_VM1_TOOTHERS ((ehvm_uint32_t)5U)
#define EHVM_RX_VCCID_VCCBUFFER_6_VM2_TOOTHERS ((ehvm_uint32_t)6U)
#define EHVM_RX_VCCID_VCCBUFFER_7_VM3_TOOTHERS ((ehvm_uint32_t)7U)
#define EHVM_RX_VCCID_VCCBUFFER_9_VM1_TOOTHERVM ((ehvm_uint32_t)9U)
#define EHVM_RX_VCCID_VCCBUFFER_10_VM2_TOOTHERVM ((ehvm_uint32_t)10U)
#define EHVM_RX_VCCID_VCCBUFFER_11_VM3_TOOTHERVM ((ehvm_uint32_t)11U)
#define EHVM_RX_VCCID_VCC_SHARED_TX_VM1 ((ehvm_uint32_t)17U)
#define EHVM_RX_VCCID_VCC_SHARED_TX_VM2 ((ehvm_uint32_t)18U)
#define EHVM_RX_VCCID_VCC_SHARED_TX_VM3 ((ehvm_uint32_t)19U)

#define EHVM_RX_VCCID_VCCBUFFER_1_SLEEPSTATUS_VM1_TOMASTER_MAX ((ehvm_uint32_t)0x00000004U)
#define EHVM_RX_VCCID_VCCBUFFER_2_SLEEPSTATUS_VM2_TOMASTER_MAX ((ehvm_uint32_t)0x00000004U)
#define EHVM_RX_VCCID_VCCBUFFER_3_SLEEPSTATUS_VM3_TOMASTER_MAX ((ehvm_uint32_t)0x00000004U)
#define EHVM_RX_VCCID_VCCBUFFER_5_VM1_TOOTHERS_MAX ((ehvm_uint32_t)0x00000048U)
#define EHVM_RX_VCCID_VCCBUFFER_6_VM2_TOOTHERS_MAX ((ehvm_uint32_t)0x00000048U)
#define EHVM_RX_VCCID_VCCBUFFER_7_VM3_TOOTHERS_MAX ((ehvm_uint32_t)0x00000048U)
#define EHVM_RX_VCCID_VCCBUFFER_9_VM1_TOOTHERVM_MAX ((ehvm_uint32_t)0x00000004U)
#define EHVM_RX_VCCID_VCCBUFFER_10_VM2_TOOTHERVM_MAX ((ehvm_uint32_t)0x00000004U)
#define EHVM_RX_VCCID_VCCBUFFER_11_VM3_TOOTHERVM_MAX ((ehvm_uint32_t)0x00000004U)
#define EHVM_RX_VCCID_VCC_SHARED_TX_VM1_MAX ((ehvm_uint32_t)0x00000100U)
#define EHVM_RX_VCCID_VCC_SHARED_TX_VM2_MAX ((ehvm_uint32_t)0x00000100U)
#define EHVM_RX_VCCID_VCC_SHARED_TX_VM3_MAX ((ehvm_uint32_t)0x00000100U)

/* ehvm_vmm_clear_wakeup_factor,ehvm_vmm_enable_wakeup_factor,ehvm_vmm_disable_wakeup_factor */
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_0  ((ehvm_uint32_t)0U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_1  ((ehvm_uint32_t)1U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_2  ((ehvm_uint32_t)2U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_3  ((ehvm_uint32_t)3U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_4  ((ehvm_uint32_t)4U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_5  ((ehvm_uint32_t)5U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_6  ((ehvm_uint32_t)6U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_7  ((ehvm_uint32_t)7U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_8  ((ehvm_uint32_t)8U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_9  ((ehvm_uint32_t)9U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_10  ((ehvm_uint32_t)10U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_11  ((ehvm_uint32_t)11U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_12  ((ehvm_uint32_t)12U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_13  ((ehvm_uint32_t)13U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_14  ((ehvm_uint32_t)14U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_15  ((ehvm_uint32_t)15U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_16  ((ehvm_uint32_t)16U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_17  ((ehvm_uint32_t)17U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_18  ((ehvm_uint32_t)18U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_19  ((ehvm_uint32_t)19U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_20  ((ehvm_uint32_t)20U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_21  ((ehvm_uint32_t)21U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_22  ((ehvm_uint32_t)22U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_23  ((ehvm_uint32_t)23U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_24  ((ehvm_uint32_t)24U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_25  ((ehvm_uint32_t)25U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_26  ((ehvm_uint32_t)26U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_27  ((ehvm_uint32_t)27U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_28  ((ehvm_uint32_t)28U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_29  ((ehvm_uint32_t)29U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_30  ((ehvm_uint32_t)30U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A0_BIT_NUM_31  ((ehvm_uint32_t)31U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_0  ((ehvm_uint32_t)0U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_1  ((ehvm_uint32_t)1U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_2  ((ehvm_uint32_t)2U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_3  ((ehvm_uint32_t)3U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_4  ((ehvm_uint32_t)4U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_5  ((ehvm_uint32_t)5U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_6  ((ehvm_uint32_t)6U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_7  ((ehvm_uint32_t)7U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_8  ((ehvm_uint32_t)8U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_9  ((ehvm_uint32_t)9U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_10  ((ehvm_uint32_t)10U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_11  ((ehvm_uint32_t)11U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_12  ((ehvm_uint32_t)12U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_13  ((ehvm_uint32_t)13U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_14  ((ehvm_uint32_t)14U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_15  ((ehvm_uint32_t)15U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_16  ((ehvm_uint32_t)16U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_17  ((ehvm_uint32_t)17U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_18  ((ehvm_uint32_t)18U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_19  ((ehvm_uint32_t)19U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_20  ((ehvm_uint32_t)20U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_21  ((ehvm_uint32_t)21U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_22  ((ehvm_uint32_t)22U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_23  ((ehvm_uint32_t)23U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_24  ((ehvm_uint32_t)24U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_25  ((ehvm_uint32_t)25U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_26  ((ehvm_uint32_t)26U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_27  ((ehvm_uint32_t)27U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_28  ((ehvm_uint32_t)28U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_29  ((ehvm_uint32_t)29U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_30  ((ehvm_uint32_t)30U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A1_BIT_NUM_31  ((ehvm_uint32_t)31U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_0  ((ehvm_uint32_t)0U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_1  ((ehvm_uint32_t)1U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_2  ((ehvm_uint32_t)2U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_3  ((ehvm_uint32_t)3U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_4  ((ehvm_uint32_t)4U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_5  ((ehvm_uint32_t)5U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_6  ((ehvm_uint32_t)6U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_7  ((ehvm_uint32_t)7U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_8  ((ehvm_uint32_t)8U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_9  ((ehvm_uint32_t)9U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_10  ((ehvm_uint32_t)10U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_11  ((ehvm_uint32_t)11U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_12  ((ehvm_uint32_t)12U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_13  ((ehvm_uint32_t)13U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_14  ((ehvm_uint32_t)14U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_15  ((ehvm_uint32_t)15U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_16  ((ehvm_uint32_t)16U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_17  ((ehvm_uint32_t)17U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_18  ((ehvm_uint32_t)18U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_19  ((ehvm_uint32_t)19U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_20  ((ehvm_uint32_t)20U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_21  ((ehvm_uint32_t)21U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_22  ((ehvm_uint32_t)22U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_23  ((ehvm_uint32_t)23U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_24  ((ehvm_uint32_t)24U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_25  ((ehvm_uint32_t)25U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_26  ((ehvm_uint32_t)26U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_27  ((ehvm_uint32_t)27U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_28  ((ehvm_uint32_t)28U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_29  ((ehvm_uint32_t)29U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_30  ((ehvm_uint32_t)30U)
#define EHVM_PE0_VM0_CTL_WAKEUP_FACTOR_A2_BIT_NUM_31  ((ehvm_uint32_t)31U)

/* ehvm_vwdt_set_mode,ehvm_vwdt_set_trigger_condition */

/* ehvm_vwdt_set_trigger_condition */

#endif /* EHVM_CFG_PE0_VM0_H */

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-2-0-z0001                                        */
/****************************************************************************/

