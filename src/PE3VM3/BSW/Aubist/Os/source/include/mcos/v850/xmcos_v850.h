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
[ xmcos_v850.h ] - MCOS/v850 internal header
****************************************************************************/
#ifndef XMCOS_V850_H
#define XMCOS_V850_H

#include <mcos/xmcos.h>

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

/* system counter ISR */
void xmcos_v850_timer_isr(void);


mcos_bool_t xmcos_v850_mkmsg_check(const uint32_t pcid);
mcos_bool_t xmcos_v850_ici_check(const uint32_t pcid);
void xmcos_v850_mkmsg_send(const uint32_t target_pcid);
void xmcos_v850_ici_init(const uint32_t pcid);
void xmcos_v850_ici_send(const uint32_t target_pcid);
void xmcos_v850_mkmsg_init(const uint32_t pcid);


#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#endif /* #ifndef XMCOS_V850_H */
