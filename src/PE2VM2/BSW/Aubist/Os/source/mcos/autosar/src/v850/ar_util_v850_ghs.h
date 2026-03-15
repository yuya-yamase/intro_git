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
/***************************************************************************
[ ar_util_v850_ghs.h ] - AUTOSAR utilities architecture/compiler dependency header file
****************************************************************************/

#ifndef AR_UTIL_V850_GHS_H_
#define AR_UTIL_V850_GHS_H_

#include "mcos/v850/xmcos_v850.h"

AR_LOCAL_FORCE_INLINE void SYSTEM_COUNTER_ISR(CounterType counter_id);

AR_LOCAL_FORCE_INLINE void SYSTEM_COUNTER_ISR(CounterType counter_id)
{
    xmcos_v850_timer_isr();
    /* [SCR_161001] This return value is being ignored due to the design */
    (void)IncrementCounter(counter_id);
}

#endif /* AR_UTIL_V850_GHS_H_ */
