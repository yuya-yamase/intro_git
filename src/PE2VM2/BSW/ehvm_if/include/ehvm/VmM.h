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
[VmM.h] - VmM module's header
****************************************************************************/

#ifndef VMM_H
#define VMM_H

#include "ehvm_types.h"

typedef ehvm_uint32_t ehvm_exit_factor_t;
typedef ehvm_uint32_t ehvm_vm_action_t;
typedef ehvm_uint32_t ehvm_status_check_t;

typedef ehvm_uint32_t ehvm_reset_category_t;
typedef ehvm_uint32_t ehvm_reset_source_t;

typedef ehvm_uint32_t ehvm_wakeup_factor_size_t;
typedef ehvm_uint32_t ehvm_wakeup_factor_num_t;
typedef ehvm_uint32_t ehvm_wakeup_factor_bit_t;
typedef ehvm_uint8_t  ehvm_vm_status_t;
typedef ehvm_uint32_t ehvm_resetype_t;
typedef ehvm_uint8_t  ehvm_contextId_t;
typedef ehvm_uint32_t ehvm_system_reset_t;

typedef struct ehvm_wakeup_factor_st{
    ehvm_wakeup_factor_bit_t      st1;
    ehvm_wakeup_factor_bit_t      st2;
    ehvm_wakeup_factor_bit_t      st3;
}ehvm_wakeup_factor_t;

typedef struct ehvm_reset_factor_st{
    ehvm_reset_category_t   category;
    ehvm_reset_source_t     source;
}ehvm_reset_factor_t;

#define EHVM_EXIT_FACTOR_HV               ((ehvm_exit_factor_t)0x00000000U)
#define EHVM_EXIT_FACTOR_NO_AWAKE         ((ehvm_exit_factor_t)0x00000001U)
#define EHVM_EXIT_FACTOR_VM_FAIL          ((ehvm_exit_factor_t)0x00000002U)

#define EHVM_VM_ACTION_SLEEP              ((ehvm_vm_action_t)0x00000000U)
#define EHVM_VM_ACTION_RESET              ((ehvm_vm_action_t)0x00000001U)

#define EHVM_VMM_STATUS_ALL_VM_STOP       ((ehvm_status_check_t)0x00000001U)
#define EHVM_VMM_STATUS_VM_RUN            ((ehvm_status_check_t)0x00000000U)

#define EHVM_WAKEUP_FACTOR_SIZE_96                       ((ehvm_wakeup_factor_size_t)0x00000002U)

#define EHVM_VM_STATUS_START           ((ehvm_vm_status_t)0x00000000U)
#define EHVM_VM_STATUS_STOP            ((ehvm_vm_status_t)0x00000001U)
#define EHVM_VM_STATUS_STOP_REQUEST    ((ehvm_vm_status_t)0x00000002U)

/* Power Status Bit definition */
#define EHVM_SYSTEM_WAKEUP_FACTOR1_BIT_NONE              ((ehvm_wakeup_factor_bit_t)0x00000000U)
#define EHVM_SYSTEM_WAKEUP_FACTOR2_BIT_NONE              ((ehvm_wakeup_factor_bit_t)0x00000000U)
#define EHVM_SYSTEM_WAKEUP_FACTOR3_BIT_NONE              ((ehvm_wakeup_factor_bit_t)0x00000000U)

#define EHVM_SYSTEM_WAKEUP_FACTOR1_BIT_BATTERY           ((ehvm_wakeup_factor_bit_t)0x00000002U)
#define EHVM_SYSTEM_WAKEUP_FACTOR1_BIT_CAN_RX0P          ((ehvm_wakeup_factor_bit_t)0x00000040U)
#define EHVM_SYSTEM_WAKEUP_FACTOR1_BIT_CAN_RX8P          ((ehvm_wakeup_factor_bit_t)0x00004000U)

#define EHVM_SYSTEM_WAKEUP_FACTOR2_BIT_IGNITION          ((ehvm_wakeup_factor_bit_t)0x00000010U)
#define EHVM_SYSTEM_WAKEUP_FACTOR2_BIT_WUF1              ((ehvm_wakeup_factor_bit_t)0x00000200U)

#define EHVM_SYSTEM_RESET_SOON                          ((ehvm_resetype_t)0x00000001U)
#define EHVM_SYSTEM_RESET_REQUEST                       ((ehvm_resetype_t)0x00000002U)

#define EHVM_SYSTEM_RESET_NONE                          ((ehvm_system_reset_t)0x00000000U)
#define EHVM_SYSTEM_RESET_HV                            ((ehvm_system_reset_t)0x00000001U)
#define EHVM_SYSTEM_RESET_VM                            ((ehvm_system_reset_t)0x00000002U)
#define EHVM_SYSTEM_RESET_SW_ECM                        ((ehvm_system_reset_t)0x00000004U)
#define EHVM_SYSTEM_RESET_WDT                           ((ehvm_system_reset_t)0x00000008U)


/* reset factor */
#define EHVM_RESET_FACTOR_CATEGORY_NONE                 ((ehvm_reset_category_t)0x00000000U)
#define EHVM_RESET_FACTOR_CATEGORY_POWER_ON_RESET       ((ehvm_reset_category_t)0x00000001U)
#define EHVM_RESET_FACTOR_CATEGORY_SW_SYS_RESET         ((ehvm_reset_category_t)0x00000010U)
#define EHVM_RESET_FACTOR_CATEGORY_DEEP_STOP            ((ehvm_reset_category_t)0x00008000U)
#define EHVM_RESET_FACTOR_CATEGORY_VIRTUAL_DEEP_STOP    ((ehvm_reset_category_t)0x00100000U)
#if defined(EHVM_TARGET_S4)
#define EHVM_RESET_FACTOR_CATEGORY_APPDOM_SP_RESET      ((ehvm_reset_category_t)0x01000000U)
#define EHVM_RESET_FACTOR_CATEGORY_APPDOM_SYS_WDT_RESET ((ehvm_reset_category_t)0x02000000U)
#define EHVM_RESET_FACTOR_CATEGORY_APPDOM_RWDT_RESET    ((ehvm_reset_category_t)0x04000000U)
#endif /* defined(EHVM_TARGET_S4) */

#define EHVM_RESET_FACTOR_SOURCE_SW_SYS_RESET_NONE        ((ehvm_reset_source_t)0x00000000U)
#define EHVM_RESET_FACTOR_SOURCE_SW_SYS_RESET_HV          ((ehvm_reset_source_t)0x00000001U)
#define EHVM_RESET_FACTOR_SOURCE_SW_SYS_RESET_VM          ((ehvm_reset_source_t)0x00000002U)
#define EHVM_RESET_FACTOR_SOURCE_SW_SYS_RESET_SW_ECM      ((ehvm_reset_source_t)0x00000004U)
#define EHVM_RESET_FACTOR_SOURCE_SW_SYS_RESET_WDT         ((ehvm_reset_source_t)0x00000008U)

#define EHVM_WAKEUP_FACTOR_A0            (0x00U)
#define EHVM_WAKEUP_FACTOR_A1            (0x01U)
#define EHVM_WAKEUP_FACTOR_A2            (0x02U)

#define EHVM_SET_WAKEUP_FACTOR_A0_BIT_NUM_1     (1U)
#define EHVM_SET_WAKEUP_FACTOR_A0_BIT_NUM_2     (2U)
#define EHVM_SET_WAKEUP_FACTOR_A0_BIT_NUM_3     (3U)
#define EHVM_SET_WAKEUP_FACTOR_A0_BIT_NUM_4     (4U)
#define EHVM_SET_WAKEUP_FACTOR_A0_BIT_NUM_22    (22U)
#define EHVM_SET_WAKEUP_FACTOR_A0_BIT_NUM_23    (23U)
#define EHVM_SET_WAKEUP_FACTOR_A0_BIT_NUM_24    (24U)
#define EHVM_SET_WAKEUP_FACTOR_A0_BIT_NUM_25    (25U)
#define EHVM_SET_WAKEUP_FACTOR_A0_BIT_NUM_26    (26U)
#define EHVM_SET_WAKEUP_FACTOR_A0_BIT_NUM_27    (27U)
#define EHVM_SET_WAKEUP_FACTOR_A0_BIT_NUM_28    (28U)
#define EHVM_SET_WAKEUP_FACTOR_A0_BIT_NUM_29    (29U)
#define EHVM_SET_WAKEUP_FACTOR_A0_BIT_NUM_30    (30U)
#define EHVM_SET_WAKEUP_FACTOR_A0_BIT_NUM_31    (31U)
#define EHVM_SET_WAKEUP_FACTOR_A1_BIT_NUM_24    (24U)
#define EHVM_SET_WAKEUP_FACTOR_A1_BIT_NUM_25    (25U)
#define EHVM_SET_WAKEUP_FACTOR_A1_BIT_NUM_26    (26U)
#define EHVM_SET_WAKEUP_FACTOR_A1_BIT_NUM_27    (27U)
#define EHVM_SET_WAKEUP_FACTOR_A1_BIT_NUM_28    (28U)
#define EHVM_SET_WAKEUP_FACTOR_A1_BIT_NUM_29    (29U)
#define EHVM_SET_WAKEUP_FACTOR_A1_BIT_NUM_30    (30U)
#define EHVM_SET_WAKEUP_FACTOR_A1_BIT_NUM_31    (31U)
#if defined(EHVM_TARGET_S4)
#define EHVM_SET_WAKEUP_FACTOR_A2_BIT_NUM_0     (0U)
#define EHVM_SET_WAKEUP_FACTOR_A2_BIT_NUM_1     (1U)
#define EHVM_SET_WAKEUP_FACTOR_A2_BIT_NUM_3     (3U)
#define EHVM_SET_WAKEUP_FACTOR_A2_BIT_NUM_4     (4U)
#define EHVM_SET_WAKEUP_FACTOR_A2_BIT_NUM_5     (5U)
#define EHVM_SET_WAKEUP_FACTOR_A2_BIT_NUM_6     (6U)
#define EHVM_SET_WAKEUP_FACTOR_A2_BIT_NUM_14    (14U)
#define EHVM_SET_WAKEUP_FACTOR_A2_BIT_NUM_15    (15U)
#define EHVM_SET_WAKEUP_FACTOR_A2_BIT_NUM_16    (16U)
#define EHVM_SET_WAKEUP_FACTOR_A2_BIT_NUM_17    (17U)
#define EHVM_SET_WAKEUP_FACTOR_A2_BIT_NUM_18    (18U)
#endif /* defined(EHVM_TARGET_S4) */
#define EHVM_SET_WAKEUP_FACTOR_A2_BIT_NUM_19    (19U)
#define EHVM_SET_WAKEUP_FACTOR_A2_BIT_NUM_20    (20U)
#define EHVM_SET_WAKEUP_FACTOR_A2_BIT_NUM_21    (21U)
#define EHVM_SET_WAKEUP_FACTOR_A2_BIT_NUM_22    (22U)
#define EHVM_SET_WAKEUP_FACTOR_A2_BIT_NUM_23    (23U)
#define EHVM_SET_WAKEUP_FACTOR_A2_BIT_NUM_24    (24U)
#define EHVM_SET_WAKEUP_FACTOR_A2_BIT_NUM_25    (25U)
#define EHVM_SET_WAKEUP_FACTOR_A2_BIT_NUM_26    (26U)
#define EHVM_SET_WAKEUP_FACTOR_A2_BIT_NUM_27    (27U)
#define EHVM_SET_WAKEUP_FACTOR_A2_BIT_NUM_28    (28U)
#define EHVM_SET_WAKEUP_FACTOR_A2_BIT_NUM_29    (29U)
#define EHVM_SET_WAKEUP_FACTOR_A2_BIT_NUM_30    (30U)
#define EHVM_SET_WAKEUP_FACTOR_A2_BIT_NUM_31    (31U)

extern ehvm_std_return_t ehvm_vmm_exit(ehvm_exit_factor_t vm_exit_factor, ehvm_vm_action_t vm_action);
extern ehvm_std_return_t ehvm_vmm_get_reset_factor(ehvm_reset_factor_t * reset_factor);

extern ehvm_std_return_t ehvm_vmm_get_vm_status_table(ehvm_vm_status_t * EhvmConstR vm_current_status );
extern ehvm_std_return_t ehvm_vmm_reset_vm(EhvmConstR ehvm_resetype_t resettype, EhvmConstR ehvm_contextId_t contextId, EhvmConstR ehvm_exit_factor_t vm_exit_factor,  EhvmConstR ehvm_vm_action_t vm_action);

extern ehvm_std_return_t ehvm_vmm_enable_suppression(void);
extern ehvm_std_return_t ehvm_vmm_disable_suppression(void);
extern ehvm_std_return_t ehvm_vmm_get_all_other_vm_status(ehvm_status_check_t * EhvmConstR vm_status_check);
extern ehvm_std_return_t ehvm_vmm_get_wakeup_factor(EhvmConstR ehvm_wakeup_factor_size_t wakeup_factor_size, ehvm_wakeup_factor_t * EhvmConstR wakeup_factor_status);
extern ehvm_std_return_t ehvm_vmm_set_wakeup_factor(EhvmConstR ehvm_wakeup_factor_num_t wakeup_factor_num, EhvmConstR ehvm_wakeup_factor_bit_t set_bit_num);
extern ehvm_std_return_t ehvm_vmm_clear_wakeup_factor(EhvmConstR ehvm_wakeup_factor_num_t wakeup_factor_num, EhvmConstR ehvm_wakeup_factor_bit_t clear_bit_num);
extern ehvm_std_return_t ehvm_vmm_enable_wakeup_factor(EhvmConstR ehvm_wakeup_factor_num_t wakeup_factor_mask_num, EhvmConstR ehvm_wakeup_factor_bit_t enable_bit_num);
extern ehvm_std_return_t ehvm_vmm_disable_wakeup_factor(EhvmConstR ehvm_wakeup_factor_num_t wakeup_factor_mask_num, EhvmConstR ehvm_wakeup_factor_bit_t disable_bit_num);

#endif /* VMM_H */
