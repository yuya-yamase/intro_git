/*
    Copyright (C) 2018 eSOL Co.,Ltd. Tokyo, Japan

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
[ mcos_mk_data.h ] - eMCOS Microkernel AUTOSAR Data
****************************************************************************/
#ifndef MCOS_MK_DATA_H
#define MCOS_MK_DATA_H

#if MCOS_AUTOSAR

#include "mcos_basic.h"
#include "mcos_cls.h"

#if !BUILD_LIB
#define CONTROL_CORE_COUNT  MP_CONTROL_CORE_COUNT
#else /* #if !BUILD_LIB */
#define CONTROL_CORE_COUNT
#endif /* #if !BUILD_LIB */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"
/*
 * Micro-Kernel control block
 */
extern mkcb_t * const mcos_mkcb_ptr_table[CONTROL_CORE_COUNT];
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"
/*
 * System Stack
 */
extern const void * const mcos_mksysstack_bottom_addr_table[CONTROL_CORE_COUNT];
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"
extern const void * const mcos_mksysstack_top_addr_table[CONTROL_CORE_COUNT];
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"
/*
 * tcb
 */
extern tcb_t * const mcos_tcb_ptr_table[CONTROL_CORE_COUNT];
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"
/*
 * actcb
 */
extern actcb_t * const mcos_actcb_ptr_table[CONTROL_CORE_COUNT];

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
extern mcos_uintptr_t xmcos_ar_mk_stack_top(uint32_t rcidx);
extern mcos_uintptr_t xmcos_ar_mk_stack_bottom(uint32_t rcidx);
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#endif /* #if MCOS_AUTOSAR */

#endif /* #if MCOS_MK_DATA_H */
