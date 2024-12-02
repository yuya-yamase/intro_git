/*
    Copyright (C) 2015 eSOL Co.,Ltd. Tokyo, Japan

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
[ ar_debug_trace.h ] - eMCOS trace for AUTOSAR header
****************************************************************************/

#ifndef AR_DEBUG_TRACE_H
#define AR_DEBUG_TRACE_H

#if MCOS_CFG_DS_TRACE_ENABLE

#include "mcos_mk_mkcc.h"

#ifdef OS_CFG_H

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const ds_trace_data_t *mcos_trace_buf_ptr[MP_CONTROL_CORE_COUNT];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#else /* #ifdef OS_CFG_H*/

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const ds_trace_data_t *mcos_trace_buf_ptr[];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#endif /* #ifdef OS_CFG_H */

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const uint32 mcos_trace_buffer_count;

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern uint32_t mcos_ds_control_block_sz;

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#endif /* #if MCOS_CFG_DS_TRACE_ENABLE */

#if (MCOS_AUTOSAR && MCOS_CFG_DS_TRACE_ENABLE)

#define OS_START_SEC_VAR_CLEARED_16
#include "Os_MemMap.h"

extern TaskType ar_thread2task_table[];

#define OS_STOP_SEC_VAR_CLEARED_16
#include "Os_MemMap.h"

#endif /* #if (MCOS_AUTOSAR && MCOS_CFG_DS_TRACE_ENABLE) */

#define OS_START_SEC_VAR_GLOBAL_CLEARED_32
#include "Os_MemMap.h"

extern dscb_local_t* mcos_ds_control_block[];

#define OS_STOP_SEC_VAR_GLOBAL_CLEARED_32
#include "Os_MemMap.h"


#endif /* AR_DEBUG_TRACE_H */
