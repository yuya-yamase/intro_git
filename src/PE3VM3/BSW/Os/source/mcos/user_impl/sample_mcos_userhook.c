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
[sample_mcos_userhook.c] - MCOS user hook (sample)
****************************************************************************/

#include "mcos/mcos.h"
#include "mcos/mcos_ds.cfg"
#include "mcos/mcos_ds.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

void mcos_ds_userhook_ar_target_exit(void)
{
    /* to be implemented by user */
    ;
}

void mcos_ds_userhook_enter_isr(mcos_id_t iid)
{
    /* to be implemented by user */
    (void)iid;
    ;
}

void mcos_ds_userhook_enter_exc(void)
{
    /* to be implemented by user */
    ;
}
void mcos_ds_userhook_enter_idle(void)
{
    /* to be implemented by user */
    ;
}
void mcos_ds_userhook_leave_idle(mcos_id_t tid)
{
    /* to be implemented by user */
    (void)tid;
    ;
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"
