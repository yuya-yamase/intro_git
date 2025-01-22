/*
    Copyright (C) 2017 By eSOL Co.,Ltd. Tokyo, Japan

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
[mcos_mk_ar.h] - MCOS micro-kernel AUTOSAR common interfaces
****************************************************************************/
#ifndef MCOS_MK_AR_H
#define MCOS_MK_AR_H

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

#if MCOS_AUTOSAR

extern void ar_nonos_exc_handler(mcos_uintptr_t info);

#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)

extern void mcos_ar_systemcall_init(void);
extern void mcos_ar_systemcall_init_impl(void);

#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

#endif /* #if MCOS_AUTOSAR */

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#endif /* #ifndef MCOS_MK_AR_H */
