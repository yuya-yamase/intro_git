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
[ hal_v850_cpp_impl.h ] - HAL v850 implementation header
****************************************************************************/
#ifndef HAL_V850_CPP_IMPL_H
#define HAL_V850_CPP_IMPL_H

#include "Os_internal.h"

#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

extern void ar_cpu_initialize_mpu(CoreIdType coreid);

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

#endif /* #ifndef HAL_V850_CPP_IMPL_H */
