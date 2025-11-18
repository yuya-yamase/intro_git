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
 [ ehvm_types_cfg_hv.h ] - HV's configuration types header
****************************************************************************/

#ifndef EHVM_TYPES_CFG_HV_H
#define EHVM_TYPES_CFG_HV_H

#define PEID_0                         ((ehvm_peid_t)0x00000000U)
#define PEID_1                         ((ehvm_peid_t)0x00000001U)
#if (EHVM_CORE_NUM == EHVM_CORE_NUM_2)
#define PEID_NUM                       ((ehvm_peid_t)0x00000002U)
#elif (EHVM_CORE_NUM == EHVM_CORE_NUM_4)
#define PEID_2                         ((ehvm_peid_t)0x00000002U)
#define PEID_3                         ((ehvm_peid_t)0x00000003U)
#define PEID_NUM                       ((ehvm_peid_t)0x00000004U)
#endif /* (EHVM_CORE_NUM == EHVM_CORE_NUM_2) */

#define GPID_VM0                       (0U)
#define GPID_VM1                       (1U)
#define GPID_VM2                       (2U)
#define GPID_VM3                       (3U)
#define GPID_VM4                       (4U)
#define GPID_VM5                       (5U)
#define GPID_VM6                       (6U)
#define GPID_VM7                       (7U)

/* Scheduler */
#define DEFAULT_INIT                   (0x00000000U)
#define DEFAULT_SPIDLIST               (0xFFFFFFFFU)

/* Port Level */
#define EHVM_PORT_LEVEL_ON                              ((bios_reg16_t)0x0U)
#define EHVM_PORT_LEVEL_OFF                             ((bios_reg16_t)0x1U)

/* Power Status Bit definition */
#define EHVM_SYSTEM_WAKEUP_FACTOR1_BIT_NONE              ((ehvm_wakeup_factor_bit_t)0x00000000U)
#define EHVM_SYSTEM_WAKEUP_FACTOR2_BIT_NONE              ((ehvm_wakeup_factor_bit_t)0x00000000U)
#define EHVM_SYSTEM_WAKEUP_FACTOR3_BIT_NONE              ((ehvm_wakeup_factor_bit_t)0x00000000U)

#define EHVM_SYSTEM_WAKEUP_FACTOR1                       ((ehvm_wakeup_factor_num_t)0x00000000U)
#define EHVM_SYSTEM_WAKEUP_FACTOR2                       ((ehvm_wakeup_factor_num_t)0x00000001U)
#define EHVM_SYSTEM_WAKEUP_FACTOR3                       ((ehvm_wakeup_factor_num_t)0x00000002U)

/* VM Management */
#define VM_SYSTEM_CONTROL_POWER_RANGE1              (0U)
#define VM_SYSTEM_CONTROL_POWER_RANGE2              (1U)
#define VM_SYSTEM_CONTROL_POWER_RANGE3              (2U)
#define VM_SYSTEM_CONTROL_POWER_RANGE_NUM           (3U)

#define EHVM_VMM_ENABLE_CLEAR_INT_FLAG              ((ehvm_uint8_t)0x01U)
#define EHVM_VMM_DISABLE_CLEAR_INT_FLAG             ((ehvm_uint8_t)0x00U)

#define NOUSE_VMM_INTERRUPT                         (0xFFFFFFFFU)

/* VCC */
#define VCC_MAX_VALUE_OF_SPID                       (0x20U)
#define VCC_MAX_NUM_OF_VCCID                        (0xFFFFU)
#define VCC_MESSAGE_ALIGN                           (0x04U)

/* EM */
#define EM_MESSAGE_ALIGN                           (0x04U)
#define EM_MAX_VALUE_OF_SPID                       (0x20U)

/* VWDT */
#define VWDT_ENABLE                                 (1U)
#define VWDT_DISABLE                                (0U)

#define VWDT_FAST_MODE                              (ehvm_vwdt_mode_t)(1U)
#define VWDT_0PER_WINDOW                            (0U)
#define VWDT_25PER_WINDOW                           (1U)
#define VWDT_50PER_WINDOW                           (2U)
#define VWDT_75PER_WINDOW                           (3U)
#define VWDT_100PER_WINDOW                          (4U)

#define EHVM_ENABLE     (1U)
#define EHVM_DISABLE    (0U)
#define EHVM_STBC       EHVM_DISABLE

/* MPU */
#define MPU_NUM_OF_ENTRY                            0x20U
#define MPU_MPCFG_HBE_SHIFT                         0x08U

/* Timeout */
#define EHVM_LOCK_TIMEOUT_LOOP_CNT_INVALID                          ((ehvm_uint32_t)0xFFFFFFFFU)
#define EHVM_PSM_DEEPSTOP_PE_STOP_WAIT_TIMEOUT_LOOP_COUNT_INVALID   ((ehvm_uint32_t)0xFFFFFFFFU)

#ifndef NULL_PTR
#define NULL_PTR                    ((void*)0x0)
#endif
typedef ehvm_uint8_t      ehvm_core_id_t;
typedef ehvm_uint8_t      ehvm_context_id_t;
typedef ehvm_uint32_t     ehvm_peid_t;
typedef ehvm_uint32_t     ehvm_gpid_t;
typedef ehvm_uint32_t     ehvm_spid_t;
typedef ehvm_uint8_t      ehvm_vm_status_t;
typedef ehvm_uint32_t     ehvm_vm_control_t;
typedef ehvm_uint32_t     ehvm_reset_source_t;
typedef ehvm_uint32_t     ehvm_wakeup_factor_bit_t;
typedef ehvm_uint32_t     ehvm_wakeup_factor_num_t;
typedef ehvm_uint32_t     ehvm_reset_category_t;
typedef ehvm_uint32_t     ehvm_vwdt_mode_t;
typedef ehvm_uint32_t     ehvm_em_id_t;
typedef ehvm_uint8_t      ehvm_user_func_id_t;

typedef unsigned long     ehvm_resetype_t;

typedef unsigned long     ehvm_wakeup_factor_size_t;

#endif  /* EHVM_TYPES_CFG_HV_H */
