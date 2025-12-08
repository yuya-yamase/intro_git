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
 [ ehvm_types.h ] - EHVM API use types header
****************************************************************************/

#ifndef EHVM_TYPES_H
#define EHVM_TYPES_H

/****************************************************************************
    type definitions
****************************************************************************/
typedef unsigned char                   ehvm_uint8_t;
typedef unsigned short                  ehvm_uint16_t;
typedef unsigned long                   ehvm_uint32_t;
typedef unsigned char                   ehvm_std_return_t;
typedef unsigned char                   ehvm_context_id_t;

/****************************************************************************
    macro definitions
****************************************************************************/
/* EHVM */
#define E_EHVM_OK                        ((ehvm_std_return_t)0x00U)
#define E_EHVM_NOT_OK                    ((ehvm_std_return_t)0x01U)
#define E_EHVM_TRANSMIT_QUEUE_FULL       ((ehvm_std_return_t)0x02U)
#define E_EHVM_RECEIVE_QUEUE_EMPTY       ((ehvm_std_return_t)0x03U)
#define E_EHVM_RECEIVE_OVERWRITE_OCCURS  ((ehvm_std_return_t)0x04U)
#define E_EHVM_OVERWRITE_DATA_EXIST      ((ehvm_std_return_t)0x05U)
#define E_EHVM_OVERWRITE_DATA_NOT_EXIST  ((ehvm_std_return_t)0x06U)
#define E_EHVM_LIMIT                     ((ehvm_std_return_t)0x07U)
#define E_EHVM_NO_TIME                   ((ehvm_std_return_t)0x08U)
#define E_EHVM_TIMEOUT_OCCURS            ((ehvm_std_return_t)0x09U)
#define E_EHVM_HVC_ACC_DENY              ((ehvm_std_return_t)0x10U)
#define E_EHVM_MM_ACC_NG                 ((ehvm_std_return_t)0x20U)
#define E_EHVM_VMM_MULTIPLE_REQUESTS     ((ehvm_std_return_t)0x30U)
#define E_EHVM_VMM_UNACCEPTABLE_STATE    ((ehvm_std_return_t)0x40U)
#define E_EHVM_GET_LOCK_FAILED           ((ehvm_std_return_t)0x50U)

#define EHVM_CORE_ID_0             (0x00U)
#define EHVM_CORE_ID_1             (0x01U)
#if (EHVM_CORE_NUM > EHVM_CORE_NUM_2)
#define EHVM_CORE_ID_2             (0x02U)
#define EHVM_CORE_ID_3             (0x03U)
#endif /* (EHVM_CORE_NUM > EHVM_CORE_NUM_2) */

#define EHVM_VM_ID_0             (0x00U)
#define EHVM_VM_ID_1             (0x01U)
#define EHVM_VM_ID_2             (0x02U)
#define EHVM_VM_ID_3             (0x03U)
#define EHVM_VM_ID_4             (0x04U)
#define EHVM_VM_ID_5             (0x05U)
#define EHVM_VM_ID_6             (0x06U)
#define EHVM_VM_ID_7             (0x07U)

#define EHVM_CONTEXT_ID_PE0_VM0             ((ehvm_context_id_t)0x00U)
#define EHVM_CONTEXT_ID_PE0_VM1             ((ehvm_context_id_t)0x01U)
#define EHVM_CONTEXT_ID_PE0_VM2             ((ehvm_context_id_t)0x02U)
#define EHVM_CONTEXT_ID_PE0_VM3             ((ehvm_context_id_t)0x03U)
#define EHVM_CONTEXT_ID_PE0_VM4             ((ehvm_context_id_t)0x04U)
#define EHVM_CONTEXT_ID_PE0_VM5             ((ehvm_context_id_t)0x05U)
#define EHVM_CONTEXT_ID_PE0_VM6             ((ehvm_context_id_t)0x06U)
#define EHVM_CONTEXT_ID_PE0_VM7             ((ehvm_context_id_t)0x07U)
#define EHVM_CONTEXT_ID_PE0_HV              ((ehvm_context_id_t)0x08U)
#define EHVM_CONTEXT_ID_PE1_VM0             ((ehvm_context_id_t)0x10U)
#define EHVM_CONTEXT_ID_PE1_VM1             ((ehvm_context_id_t)0x11U)
#define EHVM_CONTEXT_ID_PE1_VM2             ((ehvm_context_id_t)0x12U)
#define EHVM_CONTEXT_ID_PE1_VM3             ((ehvm_context_id_t)0x13U)
#define EHVM_CONTEXT_ID_PE1_VM4             ((ehvm_context_id_t)0x14U)
#define EHVM_CONTEXT_ID_PE1_VM5             ((ehvm_context_id_t)0x15U)
#define EHVM_CONTEXT_ID_PE1_VM6             ((ehvm_context_id_t)0x16U)
#define EHVM_CONTEXT_ID_PE1_VM7             ((ehvm_context_id_t)0x17U)
#define EHVM_CONTEXT_ID_PE1_HV              ((ehvm_context_id_t)0x18U)
#if (EHVM_CORE_NUM > EHVM_CORE_NUM_2)
#define EHVM_CONTEXT_ID_PE2_VM0             ((ehvm_context_id_t)0x20U)
#define EHVM_CONTEXT_ID_PE2_VM1             ((ehvm_context_id_t)0x21U)
#define EHVM_CONTEXT_ID_PE2_VM2             ((ehvm_context_id_t)0x22U)
#define EHVM_CONTEXT_ID_PE2_VM3             ((ehvm_context_id_t)0x23U)
#define EHVM_CONTEXT_ID_PE2_VM4             ((ehvm_context_id_t)0x24U)
#define EHVM_CONTEXT_ID_PE2_VM5             ((ehvm_context_id_t)0x25U)
#define EHVM_CONTEXT_ID_PE2_VM6             ((ehvm_context_id_t)0x26U)
#define EHVM_CONTEXT_ID_PE2_VM7             ((ehvm_context_id_t)0x27U)
#define EHVM_CONTEXT_ID_PE2_HV              ((ehvm_context_id_t)0x28U)
#define EHVM_CONTEXT_ID_PE3_VM0             ((ehvm_context_id_t)0x30U)
#define EHVM_CONTEXT_ID_PE3_VM1             ((ehvm_context_id_t)0x31U)
#define EHVM_CONTEXT_ID_PE3_VM2             ((ehvm_context_id_t)0x32U)
#define EHVM_CONTEXT_ID_PE3_VM3             ((ehvm_context_id_t)0x33U)
#define EHVM_CONTEXT_ID_PE3_VM4             ((ehvm_context_id_t)0x34U)
#define EHVM_CONTEXT_ID_PE3_VM5             ((ehvm_context_id_t)0x35U)
#define EHVM_CONTEXT_ID_PE3_VM6             ((ehvm_context_id_t)0x36U)
#define EHVM_CONTEXT_ID_PE3_VM7             ((ehvm_context_id_t)0x37U)
#define EHVM_CONTEXT_ID_PE3_HV              ((ehvm_context_id_t)0x38U)
#endif /* (EHVM_CORE_NUM > EHVM_CORE_NUM_2) */

#define EhvmConstR                        const

#endif  /* EHVM_TYPES_H */
