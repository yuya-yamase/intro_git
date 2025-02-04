/*
    Copyright(C) 2022 eSOL Co., Ltd. All rights reserved.

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
[ mcos_os_v850_impl.h ] - eMCOS V850 implementation header
****************************************************************************/
#ifndef MCOS_OS_V850_IMPL_H
#define MCOS_OS_V850_IMPL_H

#include <stdint.h>

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

extern void mcos_v850_setup_interrupt(uint32_t pcid);

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#endif /* #ifndef MCOS_OS_V850_IMPL_H */
