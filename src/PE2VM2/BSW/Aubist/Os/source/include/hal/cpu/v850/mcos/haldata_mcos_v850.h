/*
    Copyright(C) 2019 eSOL Co., Ltd. All rights reserved.

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
[ haldata_mcos_v850.h ] - V850 HAL-Data header file
****************************************************************************/
#ifndef HALDATA_MCOS_V850_H
#define HALDATA_MCOS_V850_H

#include <stdint.h>
#include <mcos/xmcos.h>
#include <hal/cpu/v850/hal/hal_v850_cfg.h>

typedef struct
{
    uint32_t    cpulock_mask;               /* HAL_V850_CPULOCK_MASK */
    uint32_t    plmr_mask;                  /* HAL_V850_PRIORITY_MASK */
    uint32_t    hv_en;                      /* Use Hypervisor ? */
    uint32_t    ini_psw_cu;                 /* PSW.CUx[18:16] */
    uint32_t    ini_fpsr;                   /* MCOS_V850_FPSR_INIVAL */
} haldata_mcos_v850_t;


#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern const haldata_mcos_v850_t haldata_mcos_v850;

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"


#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern const uint32_t mcos_v850_ebase_0;

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern const uint32_t mcos_v850_ebase_1;

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern const uint32_t mcos_v850_ebase_2;

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern const uint32_t mcos_v850_ebase_3;

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"


#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern const uint32_t mcos_v850_entry_address_table[MP_CONTROL_CORE_COUNT];

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"


#if MP_CONTROL_CORE_COUNT > 1U

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern const mcos_id_t mcos_v850_mkmsg_iid_table[MP_CONTROL_CORE_COUNT];

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern const mcos_id_t mcos_v850_ici_iid_table[MP_CONTROL_CORE_COUNT];

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern const int32_t mcos_v850_mkmsg_bpri_table[MP_CONTROL_CORE_COUNT];

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#endif /* MP_CONTROL_CORE_COUNT > 1U */

#endif /* #ifndef HALDATA_MCOS_V850_H */
