/*
    Copyright (C) 2019 By eSOL Co.,Ltd. Tokyo, Japan

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
[ar_data_local.h] - eMCOS AUTOSAR data local header
****************************************************************************/
#ifndef AR_DATA_LOCAL_H
#define AR_DATA_LOCAL_H

#include "Os.h"
#include "ar_kernel_impl.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern const uint8 * const * const ar_libchk;

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern const uint8 * const ar_libchk_data;     /* implemented in chip-dependent portion */

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#endif /* #ifndef AR_DATA_LOCAL_H */
