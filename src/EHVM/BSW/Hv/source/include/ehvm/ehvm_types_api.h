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
 [ ehvm_types_api.h ] - EHVM API types header
****************************************************************************/

#ifndef EHVM_TYPES_API_H
#define EHVM_TYPES_API_H

#include "ehvm_types_api_em.h"

/* VM Management */
#define EHVM_RESET_FACTOR_CATEGORY_NONE                   ((ehvm_reset_category_t)0x00000000U)
#define EHVM_RESET_FACTOR_CATEGORY_POWER_ON_RESET         ((ehvm_reset_category_t)0x00000001U)
#define EHVM_RESET_FACTOR_CATEGORY_SW_SYS_RESET           ((ehvm_reset_category_t)0x00000010U)
#define EHVM_RESET_FACTOR_CATEGORY_DEEP_STOP              ((ehvm_reset_category_t)0x00008000U)
#define EHVM_RESET_FACTOR_CATEGORY_VIRTUAL_DEEP_STOP      ((ehvm_reset_category_t)0x00100000U)
#if defined (EHVM_TARGET_S4)
#define EHVM_RESET_FACTOR_CATEGORY_APPDOM_SP_RESET        ((ehvm_reset_category_t)0x01000000U)
#define EHVM_RESET_FACTOR_CATEGORY_APPDOM_SYS_WDT_RESET   ((ehvm_reset_category_t)0x02000000U)
#define EHVM_RESET_FACTOR_CATEGORY_APPDOM_RWDT_RESET      ((ehvm_reset_category_t)0x04000000U)
#endif /* #if defined (EHVM_TARGET_S4) */

#define EHVM_RESET_FACTOR_SOURCE_SW_SYS_RESET_NONE        ((ehvm_reset_source_t)0x00000000U)
#define EHVM_RESET_FACTOR_SOURCE_SW_SYS_RESET_HV          ((ehvm_reset_source_t)0x00000001U)
#define EHVM_RESET_FACTOR_SOURCE_SW_SYS_RESET_VM          ((ehvm_reset_source_t)0x00000002U)
#define EHVM_RESET_FACTOR_SOURCE_SW_SYS_RESET_SW_ECM      ((ehvm_reset_source_t)0x00000004U)
#define EHVM_RESET_FACTOR_SOURCE_SW_SYS_RESET_WDT         ((ehvm_reset_source_t)0x00000008U)

#define EHVM_HVC_FUNC_ID_VCC_TRANSMIT                     ((ehvm_uint32_t)0U)
#define EHVM_HVC_FUNC_ID_VCC_RECEIVE                      ((ehvm_uint32_t)1U)
#define EHVM_HVC_FUNC_ID_VWDT_WDG_SETMODE                 ((ehvm_uint32_t)2U)
#define EHVM_HVC_FUNC_ID_VWDT_SETTRIGGERCONDITION         ((ehvm_uint32_t)3U)
#define EHVM_HVC_FUNC_ID_VMM_VM_EXIT                      ((ehvm_uint32_t)4U)
#define EHVM_HVC_FUNC_ID_VMM_GET_RESET_FACTOR             ((ehvm_uint32_t)5U)
#define EHVM_HVC_FUNC_ID_EM_RECEIVE_MESSAGE               ((ehvm_uint32_t)6U)
#define EHVM_HVC_FUNC_ID_VCC_CLEAR                        ((ehvm_uint32_t)7U)
#define EHVM_HVC_FUNC_ID_VCC_GET_OVERWRITE_STATUS         ((ehvm_uint32_t)8U)
#define EHVM_HVC_FUNC_ID_HVCM_SET_ACCESS_DENY_LIST        ((ehvm_uint32_t)9U)
#define EHVM_HVC_FUNC_ID_HVCM_GET_ACCESS_DENY_LIST        ((ehvm_uint32_t)10U)
#define EHVM_HVC_FUNC_ID_SCH_SET_SCHEDULE_TABLE           ((ehvm_uint32_t)11U)
#define EHVM_HVC_FUNC_ID_SCH_GET_SCHEDULE_TABLE           ((ehvm_uint32_t)12U)
#define EHVM_HVC_FUNC_ID_VMM_ENABLE_SUPPRESSION           ((ehvm_uint32_t)13U)
#define EHVM_HVC_FUNC_ID_VMM_DISABLE_SUPPRESSION          ((ehvm_uint32_t)14U)
#define EHVM_HVC_FUNC_ID_VMM_GET_VM_STATUS_TABLE          ((ehvm_uint32_t)15U)
#define EHVM_HVC_FUNC_ID_VMM_RESET_VM                     ((ehvm_uint32_t)16U)
#define EHVM_HVC_FUNC_ID_VCC_CLEAR_CHANNEL                ((ehvm_uint32_t)17U)
#define EHVM_HVC_FUNC_ID_VMM_GET_WAKEUP_FACTOR            ((ehvm_uint32_t)18U)
#define EHVM_HVC_FUNC_ID_VMM_SET_WAKEUP_FACTOR            ((ehvm_uint32_t)19U)
#define EHVM_HVC_FUNC_ID_VMM_CLEAR_WAKEUP_FACTOR          ((ehvm_uint32_t)20U)
#define EHVM_HVC_FUNC_ID_VMM_ENABLE_WAKEUP_FACTOR         ((ehvm_uint32_t)21U)
#define EHVM_HVC_FUNC_ID_VMM_DISABLE_WAKEUP_FACTOR        ((ehvm_uint32_t)22U)
#define EHVM_HVC_FUNC_ID_VMM_GET_ALL_OTHER_VM_STATUS      ((ehvm_uint32_t)23U)
#define EHVM_HVC_FUNC_ID_SCH_DISABLE_VM_SWITCH            ((ehvm_uint32_t)24U)
#define EHVM_HVC_FUNC_ID_SCH_ENABLE_VM_SWITCH             ((ehvm_uint32_t)25U)
#define EHVM_HVC_FUNC_ID_UC_CALL_FUNCTION                 ((ehvm_uint32_t)26U)

#ifndef E_OK
#define E_OK                        ((ehvm_std_return_t)0x00U)
#endif
#ifndef E_NOT_OK
#define E_NOT_OK                    ((ehvm_std_return_t)0x01U)
#endif

typedef ehvm_uint32_t     ehvm_exit_factor_t;
typedef ehvm_uint32_t     ehvm_vm_action_t;
typedef ehvm_uint32_t     ehvm_all_context_flag_t;

typedef ehvm_uint32_t     ehvm_suppress_vm_normal_t;
typedef ehvm_uint32_t     ehvm_status_check_t;


/* wakeup factor */
typedef struct ehvm_wakeup_factor_st{
    ehvm_wakeup_factor_bit_t      st1;
    ehvm_wakeup_factor_bit_t      st2;
    ehvm_wakeup_factor_bit_t      st3;
}ehvm_wakeup_factor_t;

typedef struct ehvm_reset_factor_st{
    ehvm_reset_category_t   category;
    ehvm_reset_source_t     source;
}ehvm_reset_factor_t;

/* VM reset request table by CORE */
typedef struct ehvm_vm_reset_st{
    ehvm_resetype_t            resettype;
    ehvm_exit_factor_t         vm_exit_factor;
    ehvm_vm_action_t           vm_action;
    ehvm_all_context_flag_t    specify_all_vm_flag;
}ehvm_vm_reset_t;

typedef ehvm_uint8_t      ehvm_std_return_t;

#endif /* EHVM_TYPES_API_H */
