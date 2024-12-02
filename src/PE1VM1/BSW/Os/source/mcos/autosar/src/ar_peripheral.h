/*
    Copyright (C) 2021 By eSOL Co.,Ltd. Tokyo, Japan

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
[ar_peripheral.h] - Hardware peripheral access
****************************************************************************/

#ifndef AR_PERIPHERAL_H
#define AR_PERIPHERAL_H

/* Hardware Area Information */

#define RANGE_1BYTE  0UL
#define RANGE_2BYTES 1UL
#define RANGE_4BYTES 3UL

struct ar_peripheral_area_config_st {
    const mcos_uintptr_t  start_addr;
    const mcos_uintptr_t  end_addr;
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
    const uint32     *osap_allowedmap;   /* Access allowed OSAP bitmap */
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
};

typedef struct ar_peripheral_area_config_st ar_peripheral_area_config_t;


#ifdef OS_CFG_H
#if (AR_OS_EXIST_PERIPHERAL_AREA == STD_ON)

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const ar_peripheral_area_config_t ar_peripheral_area_configs[AR_OS_NUM_PERIPHERAL_AREAS];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#endif /* #if (AR_OS_EXIST_PERIPHERAL_AREA == STD_ON) */
#else /* #ifdef OS_CFG_H */

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const ar_peripheral_area_config_t ar_peripheral_area_configs[];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#endif /* #ifdef OS_CFG_H */


#define OS_START_SEC_CODE
#include "Os_MemMap.h"

extern StatusType ar_peripheral_chk_address(const clscb_t* clscb, AreaIdType Area, const void* Address, uint32 Range);

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"


#endif /* AR_PERIPHERAL_H */
