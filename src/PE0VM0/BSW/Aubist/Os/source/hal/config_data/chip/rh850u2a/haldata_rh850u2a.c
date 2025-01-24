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
[ haldata_rh850u2a.c ] - RH850U2A HAL-Data
****************************************************************************/
#include <mp.cfg>
#include <mcos/mcos.cfg>
#include <hal/cpu/v850/hal/hal_v850_cfg.h>
#include <hal/cpu/v850/mcos/mcos_v850.cfg>
#include <hal/hal.h>
#include "hal/chip/rh850u2a/haldata_rh850u2a.h"
#include <hal/chip/rh850u2a/rh850u2a.cfg>
#include "hal/chip/rh850u2a/mcos/mcos_os_rh850u2a.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

const haldata_rh850u2a_t haldata_rh850u2a = {
    (uint32_t)RH850U2A_OSTM_FREQ_HZ,
    (uint32_t)RH850U2A_RLIN3_BASE,
};

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"


/****************************************************************************
 * const
****************************************************************************/
#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/*
 * haldata_mcos_rh850u2a_ostm_info[]
 */
const xmcos_timer_info_t haldata_mcos_rh850u2a_ostm_info[MP_CONTROL_CORE_COUNT] = {
#if MP_CONTROL_CORE_COUNT >= 1U
    {
        (uint32_t)RH850U2A_OSTM_FREQ_HZ,    /* 160MHz */
        (uint16_t)199,                      /* OSTM0 */
        (uint32_t)(0UL),                    /* Not Used */
        (uint64_t)(0x100000000ULL)          /* 32bit width */
    },
#endif /* #if MP_CONTROL_CORE_COUNT >= 1U */
#if MP_CONTROL_CORE_COUNT >= 2U
    {
        (uint32_t)RH850U2A_OSTM_FREQ_HZ,    /* 160MHz */
        (uint16_t)200,                      /* OSTM1*/
        (uint32_t)(0UL),                    /* Not Used */
        (uint64_t)(0x100000000ULL)          /* 32bit width */
    },
#endif /* #if MP_CONTROL_CORE_COUNT >=2U */
#if MP_CONTROL_CORE_COUNT >= 3U
    {
        (uint32_t)RH850U2A_OSTM_FREQ_HZ,    /* 160MHz */
        (uint16_t)201,                      /* OSTM2*/
        (uint32_t)(0UL),                    /* Not Used */
        (uint64_t)(0x100000000ULL)          /* 32bit width */
    },
#endif /* #if MP_CONTROL_CORE_COUNT >= 3U */
#if MP_CONTROL_CORE_COUNT >= 4U
    {
        (uint32_t)RH850U2A_OSTM_FREQ_HZ,    /* 160MHz */
        (uint16_t)202,                      /* OSTM3 */
        (uint32_t)(0UL),                    /* Not Used */
        (uint64_t)(0x100000000ULL)          /* 32bit width */
    }
#endif /* #if MP_CONTROL_CORE_COUNT >= 4U */
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/****************************************************************************
 * variables
****************************************************************************/
#define OS_START_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

/*
 * haldata_mcos_rh850u2a_ostm_interval[]
 */
uint32_t haldata_mcos_rh850u2a_ostm_interval[MP_CONTROL_CORE_COUNT];

#define OS_STOP_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"
