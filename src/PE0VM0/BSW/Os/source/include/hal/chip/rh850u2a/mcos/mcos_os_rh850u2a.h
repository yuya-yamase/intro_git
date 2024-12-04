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
[ mcos_os_rh850u2a.h ] - RH850U2A header file
****************************************************************************/
#ifndef MCOS_OS_RH850U2A_H
#define MCOS_OS_RH850U2A_H

/*
 * RH850U2A:
 *  Implementions
 */
#include <hal/hal_impl.h>
#include <hal/cpu/v850/hal/hal_v850_cpp_impl.h>
#include <hal/cpu/v850/hal/hal_v850_impl.h>
#include <hal/chip/rh850u2a/hal/hal_rh850u2a_impl.h>
#include <hal/chip/rh850u2a/haldata_rh850u2a.h>

#include <stdint.h>

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern const xmcos_timer_info_t haldata_mcos_rh850u2a_ostm_info[MP_CONTROL_CORE_COUNT];

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

extern uint32_t haldata_mcos_rh850u2a_ostm_interval[MP_CONTROL_CORE_COUNT];

#define OS_STOP_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

#endif /* #ifndef MCOS_OS_RH850U2A_H */
