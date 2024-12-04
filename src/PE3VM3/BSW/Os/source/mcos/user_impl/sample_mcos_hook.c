/*
    Copyright (C) 2013 eSOL Co.,Ltd. Tokyo, Japan

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
[ sample_mcos_hook.c ] - MCOS hook sample
****************************************************************************/

#include "mcos/mcos.h"
#include "mcos/mcos_hook_code.h"
#include "mcos/mcos_hook.h"

#if MCOS_AUTOSAR
#include "mcos/mcos_ar_hook_code.h"
#endif  /* #if MCOS_AUTOSAR */

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

/* pre system initialization hook */
void mcos_hook_pre_sysinit (void)
{
    /* to be to be implemented by user */
    ;
}

/* pre BIOS initialization hook */
void mcos_hook_pre_biosinit (
    mcos_id_t lcid)
{
    /* to be implemented by user */
    (void)lcid;
    ;
}


/* pre core initialization hook */
void mcos_hook_pre_coreinit (
    mcos_id_t lcid)
{
    /* to be implemented by user */
    (void)lcid;
    ;
}

#if !MCOS_AUTOSAR
/* post micro-kernel initialization hook */
void mcos_hook_post_mkinit (
    mcos_id_t lcid)
{
    /* to be implemented by user */
    (void)lcid;
    ;
}

#endif /* !MCOS_AUTOSAR */

/* kernel panic hook */
void mcos_hook_panic (uint32_t err)
{
    (void)err;
    /* to be implemented by user */
    for (;;)
    {
        ;
    }
}

/* kernel shutdown hook */
void mcos_hook_shutdown (void)
{
    /* to be implemented by user */
    for (;;)
    {
        ;
    }
}

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

