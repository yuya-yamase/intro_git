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
[ar_counter_local.h] - Counter local header
****************************************************************************/

#ifndef AR_COUNTER_LOCAL_H
#define AR_COUNTER_LOCAL_H

#include "ar_counter.h"

#ifdef OS_CFG_H
#if (AR_OS_EXIST_COUNTER == STD_ON)

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const ar_counter_config_t    ar_counter_configs[AR_OS_NUM_COUNTERS];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern ar_countercb_t * const       ar_countercb_ptr_table[AR_OS_NUM_COUNTERS];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const CounterType ar_system_counter_list[AR_OS_NUM_CORES];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#endif /* #if (AR_OS_EXIST_COUNTER == STD_ON) */
#else /* #ifdef OS_CFG_H */

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const ar_counter_config_t    ar_counter_configs[];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern ar_countercb_t * const       ar_countercb_ptr_table[];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const CounterType ar_system_counter_list[];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define AR_COUNTER_LOCAL_ENABLE

#endif /* #ifdef OS_CFG_H */


#ifdef AR_COUNTER_LOCAL_ENABLE

LOCAL_INLINE mcos_id_t ar_get_counter_lcid(const CounterType counter_id);

LOCAL_INLINE mcos_id_t ar_get_counter_lcid(
    const CounterType counter_id)
{
    mcos_id_t lcid;

    lcid = ar_counter_configs[counter_id].p_osapconfig->lcid;

    return lcid;
}

#endif /* #ifdef AR_COUNTER_LOCAL_ENABLE */

#endif /* AR_COUNTER_LOCAL_H */
