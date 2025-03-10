/*
    Copyright (C) 2022 eSOL Co.,Ltd. Tokyo, Japan

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
[ sample_v850_nonos_exc_handler.c] - Sample exception handler for C1ISR
****************************************************************************/
#include "mcos/v850/mcos_v850_callout.h"

#define OS_START_SEC_CALLOUT_CODE
#include "Os_MemMap.h"

 /*---------------------------------------------------------------------------
  mcos_v850_ar_nonos_exc_handler
      This function is called from OS, when an OS-managed exception occurs in C1ISRs.
 ---------------------------------------------------------------------------*/
void mcos_v850_ar_nonos_exc_handler(void)
{
    /* to be implemented by user */
    while (1)
    {
        /* Nothing to do */
    }
}

#define OS_STOP_SEC_CALLOUT_CODE
#include "Os_MemMap.h"
 