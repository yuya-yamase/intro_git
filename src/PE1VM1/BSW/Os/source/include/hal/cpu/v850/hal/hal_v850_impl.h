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
[ hal_v850_impl.h ] - HAL v850 implementation header
****************************************************************************/

#ifndef HAL_V850_IMPL_H
#define HAL_V850_IMPL_H

#include "hal/hal.h"
#include "hal/hal_cpu_impl.h"
#include "hal/cpu/v850/v850.h"

HAL_INLINE void hal_v850_sync_exec_8(volatile hal_uint8_t *dmyread_addr);
HAL_INLINE void
hal_v850_sync_exec_8(
    volatile hal_uint8_t *dmyread_addr)
{
#pragma ghs nowarning 1546
    __asm__ volatile
    (
        "ld.bu 0[%0],%0\n"
        "syncp\n"
        :"=r"(dmyread_addr)
        :"0"(dmyread_addr)
    );
#pragma ghs endnowarning
}

#include <hal/hal_impl.h>


#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"


#endif /* #ifndef HAL_V850_IMPL_H */
