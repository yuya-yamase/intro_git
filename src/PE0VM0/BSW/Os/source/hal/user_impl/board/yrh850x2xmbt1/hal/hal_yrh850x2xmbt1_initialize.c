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
[ hal_yrh850x2xmbt1_initialize.c ] - HAL initialization
****************************************************************************/

#include <hal/hal_impl.h>

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

/* initialize HAL hardware resources for master core */
void hal_hw_initializeMaster(void)
{
    hal_pic_initialize_impl();
}

/* initialize HAL hardware resources for slave core */
void hal_hw_initializeSlave(hal_int_t coreid)
{
    (void)coreid; /* 'coreid' is not used in this function. */
}

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"
