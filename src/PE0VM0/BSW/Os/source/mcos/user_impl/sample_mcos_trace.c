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
[sample_mcos_trace.c] - MCOS user trace hook (sample)
****************************************************************************/

#include <stdint.h>
#include "mcos/mcos_ar.h"
#include "mcos/mcos_ds.h"

#if MCOS_AUTOSAR
#define OS_START_SEC_CODE
#include "Os_MemMap.h"

void mcos_debug_trace_hook_initialization(void);
void mcos_debug_trace_hook_initialization(void)
{
    /* to be implemented by user */
    ;
}

void mcos_debug_trace_hook_finalization(void);
void mcos_debug_trace_hook_finalization(void)
{
    /* to be implemented by user */
    ;
}

void mcos_debug_trace_hook_start(void);
void mcos_debug_trace_hook_start(void)
{
    /* to be implemented by user */
    ;
}

void mcos_debug_trace_hook_stop(void);
void mcos_debug_trace_hook_stop(void)
{
    /* to be implemented by user */
    ;
}

void mcos_debug_trace_hook_set_info(uint32_t *p_info1, int64_t *p_info2);
void mcos_debug_trace_hook_set_info(uint32_t *p_info1, int64_t *p_info2)
{
    /* to be implemented by user */
    *p_info1 = 0U;
    *p_info2 = 0;
}

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"
#endif /* MCOS_AUTOSAR */
