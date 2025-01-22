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
[ haldata_mcos_v850.c ] - V850 HAL-Data
****************************************************************************/
#include <mcos/xmcos.h>
#include "hal/cpu/v850/mcos/haldata_mcos_v850.h"
#include <mp.cfg>
#include <hal/cpu/v850/hal/hal_v850_cfg.h>
#include <hal/cpu/v850/mcos/mcos_v850.cfg>
#include <hal/cpu/v850/mcos/mcos_v850_fpu.cfg>

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/* mcos_v850_entry_address_table[] */
const uint32_t mcos_v850_entry_address_table[MP_CONTROL_CORE_COUNT] =
{
#if MP_CONTROL_CORE_COUNT >= 1U
        (uint32_t)&mcos_v850_ebase_0,
#endif /* #if MP_CONTROL_CORE_COUNT >= 1U */
#if MP_CONTROL_CORE_COUNT >= 2U
        (uint32_t)&mcos_v850_ebase_1,
#endif /* #if MP_CONTROL_CORE_COUNT >= 2U */
#if MP_CONTROL_CORE_COUNT >= 3U
        (uint32_t)&mcos_v850_ebase_2,
#endif /* #if MP_CONTROL_CORE_COUNT >= 3U */
#if MP_CONTROL_CORE_COUNT >= 4U
        (uint32_t)&mcos_v850_ebase_3,
#endif /* #if MP_CONTROL_CORE_COUNT >= 4U */
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/* mcos_v850_mkmsg_iid_table[] */
#if MP_CONTROL_CORE_COUNT > 1U

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

const mcos_id_t mcos_v850_mkmsg_iid_table[MP_CONTROL_CORE_COUNT] =
{
    MCOS_V850_MKMSG_INTERRUPT_NUMBER,
#if (MP_CONTROL_CORE_COUNT >= 2U)
    MCOS_V850_MKMSG_INTERRUPT_NUMBER,
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 2U) */
#if (MP_CONTROL_CORE_COUNT >= 3U)
    MCOS_V850_MKMSG_INTERRUPT_NUMBER,
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 3U) */
#if (MP_CONTROL_CORE_COUNT >= 4U)
    MCOS_V850_MKMSG_INTERRUPT_NUMBER,
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 4U) */
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#endif /* #if MP_CONTROL_CORE_COUNT > 1U*/

/* mcos_v850_mkmsg_iid_table[] */
#if MP_CONTROL_CORE_COUNT > 1U

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

const int32_t mcos_v850_mkmsg_bpri_table[MP_CONTROL_CORE_COUNT] =
{
    MCOS_V850_MKMSG_INTERRUPT_PRIORITY,
#if (MP_CONTROL_CORE_COUNT >= 2U)
    MCOS_V850_MKMSG_INTERRUPT_PRIORITY,
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 2U) */
#if (MP_CONTROL_CORE_COUNT >= 3U)
    MCOS_V850_MKMSG_INTERRUPT_PRIORITY,
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 3U) */
#if (MP_CONTROL_CORE_COUNT >= 4U)
    MCOS_V850_MKMSG_INTERRUPT_PRIORITY,
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 4U) */
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#endif /* #if MP_CONTROL_CORE_COUNT > 1U*/

/* mcos_v850_ici_iid_table[] */
#if MP_CONTROL_CORE_COUNT > 1U

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

const mcos_id_t mcos_v850_ici_iid_table[MP_CONTROL_CORE_COUNT] =
{
    MCOS_V850_ICI_INTERRUPT_NUMBER,
#if (MP_CONTROL_CORE_COUNT >= 2U)
    MCOS_V850_ICI_INTERRUPT_NUMBER,
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 2U) */
#if (MP_CONTROL_CORE_COUNT >= 3U)
    MCOS_V850_ICI_INTERRUPT_NUMBER,
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 3U) */
#if (MP_CONTROL_CORE_COUNT >= 4U)
    MCOS_V850_ICI_INTERRUPT_NUMBER,
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 4U) */
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#endif /* #if MP_CONTROL_CORE_COUNT > 1U*/


#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

const haldata_mcos_v850_t haldata_mcos_v850 = {
    (uint32_t)HAL_V850_CPULOCK_MASK,
    (uint32_t)HAL_V850_PRIORITY_MASK,
#ifdef AR_OS_USE_HYPERVISOR
    (uint32_t)0x00000001UL,
#else
    (uint32_t)0x00000000UL,
#endif /* #ifdef AR_OS_USE_HYPERVISOR */
    (uint32_t)0x00010000,
    (uint32_t)MCOS_V850_FPSR_INIVAL
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"
