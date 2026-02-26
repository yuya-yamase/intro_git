/*
    Copyright (C) 2016 By eSOL Co.,Ltd. Tokyo, Japan

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
[ar_ioc_send_common.h] - IocSend common function
****************************************************************************/

#ifndef AR_IOC_SEND_COMMON_H
#define AR_IOC_SEND_COMMON_H

#include "ar_kernel_impl.h"
#include "ar_ioc_local.h"

AR_LOCAL_FORCE_INLINE void ar_ioc_push_data(const ar_ioc_config_t * const p_config,
    const ar_ioc_receiver_config_t * const p_receiver_config, ar_ioccb_t * const p_ioccb,
    const void * const in);

/*---------------------------------------------------------------------------
  ar_ioc_push_data

  Input     :   p_config
            :   p_receiver_config
            :   p_ioccb
            :   in
  Output    :   none
  Return    :
  Note  :   none
 ---------------------------------------------------------------------------*/
AR_LOCAL_FORCE_INLINE void ar_ioc_push_data(
    const ar_ioc_config_t * const p_config,
    const ar_ioc_receiver_config_t * const p_receiver_config,
    ar_ioccb_t * const p_ioccb,
    const void * const in)
{
    ar_memcpy((void *) ((mcos_uintptr_t) p_receiver_config->p_iocmb + ((p_config->size) * (p_ioccb->last))),
            in, p_config->size);
    p_ioccb->queuesz++;
    p_ioccb->last++;
    if (p_ioccb->last >= p_config->queuesz_limit)
    {
        p_ioccb->last = 0U;
    }
    else
    {
        /* Nothing to do */
    }
}

#endif /* #ifndef AR_IOC_SEND_COMMON_H */
