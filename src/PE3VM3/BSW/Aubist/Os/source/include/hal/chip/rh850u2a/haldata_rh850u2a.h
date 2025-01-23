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
[ haldata_rh850u2a.h ] - RH850U2A HAL-Data header file
****************************************************************************/
#ifndef HALDATA_RH850U2A_H
#define HALDATA_RH850U2A_H

#include <stdint.h>

typedef struct
{
    uint32_t    ostm_freq_hz;   /* RH850U3A_OSTM_FREQ_HZ  */
    uint32_t    uart_base;      /* RLIN3_BASE  */
} haldata_rh850u2a_t;

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const haldata_rh850u2a_t haldata_rh850u2a;

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"


#endif /* #ifndef HALDATA_RH850U2A_H */
