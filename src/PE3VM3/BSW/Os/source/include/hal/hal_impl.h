/*
    Copyright (C) 2018 By eSOL Co.,Ltd. Tokyo, Japan

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
[ hal_impl.h ] - HAL common definitions for implementations
****************************************************************************/
#ifndef HAL_IMPL_H
#define HAL_IMPL_H

#include <parts.cfg>
#include <hal/hal.h>
#include <hal/hal_basic_impl.h>
#include <hal/hal_cpu_impl.h>

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

extern void hal_pic_initialize_impl(void);

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#endif /* #ifndef HAL_IMPL_H */
