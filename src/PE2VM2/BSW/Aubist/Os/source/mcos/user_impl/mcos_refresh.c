/*
    Copyright (C) 2016 By eSOL Co.,Ltd. Tokyo, Japan

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
[sample_mcos_refresh.c] - MCOS user register refresh hook (sample)
****************************************************************************/

#include "mcos/mcos_ar.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

mcos_refresh_err_t mcos_refresh_register_values_hook(const CoreIdType coreid, boolean should_fix)
{
    (void)coreid;
    (void)should_fix;
    return MCOS_E_REFRESH_OK;
}

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"
