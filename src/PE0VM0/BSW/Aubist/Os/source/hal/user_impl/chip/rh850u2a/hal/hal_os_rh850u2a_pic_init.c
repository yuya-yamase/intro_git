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
[ hal_os_rh850u2a_pic_init.c ] - eMCOS interrupt control
****************************************************************************/

#include <hal/hal.h>
#include <hal/chip/rh850u2a/hal/hal_rh850u2a_impl.h>
#include <hal/chip/rh850u2a/haldata_rh850u2a.h>

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

/* initialize pic (internal implementation function) */
void
hal_pic_initialize_impl(void)
{
    /*
     * Resetting interrupt factors is user responsibility.
     * It is assumed that eMCOS assumes the state at reset.
     */
}

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

