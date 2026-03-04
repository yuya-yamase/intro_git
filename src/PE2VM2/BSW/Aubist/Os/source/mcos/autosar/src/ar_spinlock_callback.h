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
[ar_spinlock_callback.h] - Callback from HAL
****************************************************************************/

#ifndef AR_SPINLOCK_CALLBACK_H
#define AR_SPINLOCK_CALLBACK_H

#include "ar_kernel_impl.h"
#include "ar_spinlock_local.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

/*---------------------------------------------------------------------------
  ar_spinlock_enaint
    callback from mcos_spinlock_get_enaint()
  Input     :   none
  Output    :   none
  Return    :
  Note  :   mcos_spinlock_get_enaint() should declare "extern" to call this function.
 ---------------------------------------------------------------------------*/
AR_LOCAL_FORCE_INLINE void ar_spinlock_enaint(void);
AR_LOCAL_FORCE_INLINE void ar_spinlock_enaint(void)
{
    ar_critical_section_enaint();
}

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#endif /* AR_SPINLOCK_CALLBACK_H */
