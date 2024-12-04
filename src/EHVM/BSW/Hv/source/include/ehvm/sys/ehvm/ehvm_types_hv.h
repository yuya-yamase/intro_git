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
 [ ehvm_types_hv.h ] - EHVM API for Hv internal use header
****************************************************************************/

#ifndef EHVM_TYPES_HV_H
#define EHVM_TYPES_HV_H

#if defined (EHVM_TYPES_HV_C) || defined (EHVM_TYPES_HV_ASM) /* define groups used in assembler or C language files */
#define EHVM_HVM_INVALID_CONTEXTID (0xFFU)
#endif /* EHVM_TYPES_HV_C || EHVM_TYPES_HV_ASM */

#if defined (EHVM_TYPES_HV_C)

#include "ehvm_types_stdint.h"
#include "ehvm_types_cfg_hv.h"

/****************************************************************************
    macro definitions
****************************************************************************/
/* EHVM */

#define E_EHVM_TRANSMIT_QUEUE_FULL      (0x02U)
#define E_EHVM_RECEIVE_QUEUE_EMPTY      (0x03U)
#define E_EHVM_RECEIVE_OVERWRITE_OCCURS (0x04U)
#define E_EHVM_OVERWRITE_DATA_EXIST     (0x05U)
#define E_EHVM_OVERWRITE_DATA_NOT_EXIST (0x06U)

#define E_EHVM_LIMIT                    (0x07U)
#define E_EHVM_NO_TIME                  (0x08U)
#define E_EHVM_TIMEOUT_OCCURS           (0x09U)

#define E_EHVM_HVC_ACC_DENY          ((ehvm_std_return_t)0x10U)
#define E_EHVM_MM_ACC_NG             ((ehvm_std_return_t)0x20U)
#define E_EHVM_VMM_MULTIPLE_REQUESTS ((ehvm_std_return_t)0x30U)
#define E_EHVM_VMM_UNACCEPTABLE_STATE ((ehvm_std_return_t)0x40U)

#define NULL_PTR                     ((void*)0x0)

#define LOCAL_INLINE                 static inline

#define PEID_CONTROL_NUM             1

#define EHVM_HOST_MODE               ((ehvm_op_mode_t) 0U)
#define EHVM_GUEST_MODE              ((ehvm_op_mode_t) 1U)

/* VCC */
#define E_VCC_BIT_IS_ZERO               (0x00U)
#define E_VCC_BIT_IS_ONE                (0x01U)

#define VCC_START                       ((ehvm_vcc_status_t)0x01U)
#define VCC_STOP                        ((ehvm_vcc_status_t)0x00U)

/* MM */
#define SIZE_OF_POINTER                 (0x04U)

/****************************************************************************
    type definitions
****************************************************************************/
typedef ehvm_uint8_t      ehvm_status_t;

typedef ehvm_uint32_t     ehvm_pe_mode_t;
typedef ehvm_uint32_t     ehvm_standby_transition_t;
typedef ehvm_uint32_t     ehvm_op_mode_t;
typedef ehvm_uint8_t      ehvm_em_status_t;
typedef ehvm_uint8_t      ehvm_vcc_status_t;
typedef ehvm_uint8_t      ehvm_contextId_t;

typedef ehvm_uint32_t     ehvm_retry_count_t;
typedef ehvm_uint32_t     ehvm_reset_flag_t;
typedef ehvm_uint32_t     ehvm_system_reset_t;

typedef ehvm_uint8_t      ehvm_sch_scheduling_id_t;
typedef ehvm_uint16_t      ehvm_sch_disable_count_t;
typedef ehvm_uint16_t      ehvm_sch_timeout_status_t;

typedef struct ehvm_hv_status_st{
    ehvm_pe_mode_t            pe_mode[PEID_NUM];
    ehvm_standby_transition_t standby_transition;
}ehvm_hv_status_t;

#endif /* EHVM_TYPES_HV_C */

#undef EHVM_TYPES_HV_C
#undef EHVM_TYPES_HV_ASM

#endif  /* EHVM_TYPES_HV_H */
