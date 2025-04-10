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
[ar_resource_local.h] - Resource local header
****************************************************************************/

#ifndef AR_RESOURECE_LOCAL_H
#define AR_RESOURECE_LOCAL_H

#include "ar_resource.h"

#ifdef OS_CFG_H
#if (AR_OS_EXIST_RESOURCE == STD_ON)

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const ar_resource_config_t   ar_resource_configs[AR_OS_NUM_RESOURCES];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern ar_resourcecb_t * const      ar_resourcecb_ptr_table[AR_OS_NUM_RESOURCES];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#endif /* #if (AR_OS_EXIST_RESOURCE == STD_ON) */
#else /* #ifdef OS_CFG_H */

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const ar_resource_config_t   ar_resource_configs[];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern ar_resourcecb_t * const      ar_resourcecb_ptr_table[];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#endif /* #ifdef OS_CFG_H */
#endif /* #ifndef AR_RESOURECE_LOCAL_H */
