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
[ar_func_table_local.h] - Function table local header
****************************************************************************/
#ifndef AR_FUNC_TABLE_LOCAL_H
#define AR_FUNC_TABLE_LOCAL_H

#include "Os.h"
#include "ar_kernel_impl.h"
#include "ar_svc_id.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern const AR_SVC_ENTITY_CallFastTrustedFunction ar_svc_call_fast_trusted_function;

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#endif /* #ifndef AR_FUNC_TABLE_LOCAL_H */
