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
[ar_interrupt_local.h] - Interrupt local header
****************************************************************************/

#ifndef AR_INTERRUPT_LOCAL_H
#define AR_INTERRUPT_LOCAL_H

#include "ar_interrupt.h"

#ifdef OS_CFG_H

#if (AR_OS_EXIST_C2ISR == STD_ON)

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"
extern const ar_int_config_t        ar_int_configs[AR_OS_NUM_C2ISRS];
#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"
extern const ar_isr_config_t        ar_isr_configs[AR_OS_NUM_C2ISRS];
#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"
extern ar_isrcb_t * const           ar_isrcb_ptr_table[AR_OS_NUM_C2ISRS];
#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#else  /* #if (AR_OS_EXIST_C2ISR == STD_ON) */

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"
extern const ar_int_config_t        ar_int_configs[1];
#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"
extern const ar_isr_config_t        ar_isr_configs[1];
#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"
extern ar_isrcb_t * const           ar_isrcb_ptr_table[1];
#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#endif /* #if (AR_OS_EXIST_C2ISR == STD_ON) */

#if (AR_OS_EXIST_C1ISR == STD_ON)
#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"
extern const ar_cat1_int_config_t   ar_cat1_int_configs[AR_OS_NUM_C1ISRS];
#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"
#endif /* #if (AR_OS_EXIST_C1ISR == STD_ON) */

#else /* #ifdef OS_CFG_H */

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"
extern const ar_int_config_t        ar_int_configs[];
#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"
extern const ar_isr_config_t        ar_isr_configs[];
#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"
extern ar_isrcb_t * const           ar_isrcb_ptr_table[];
#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"
extern const ar_cat1_int_config_t   ar_cat1_int_configs[];
#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#endif /* #ifdef OS_CFG_H */

#endif /* AR_INTERRUPT_LOCAL_H */
