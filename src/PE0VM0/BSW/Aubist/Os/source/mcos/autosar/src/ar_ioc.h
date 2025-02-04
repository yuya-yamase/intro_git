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
[ar_ioc.h] - IOC Information
****************************************************************************/

#ifndef AR_IOC_H
#define AR_IOC_H

#include "ar_osap.h"

typedef struct ar_ioc_config_st {
    const IocType   *receiver_id_list;
    uint32          queuesz_limit;
    uint32          size;
    uint16          receivers;
    boolean         is_group;
    boolean         is_intercore;
} ar_ioc_config_t;

typedef struct ar_ioc_receiver_config_st {
    const ar_ioc_config_t   *p_config;
    const ar_osap_config_t  *p_osapconfig;
    void                    *p_iocmb;
    void                    (*receiver_pullcb)(void);
} ar_ioc_receiver_config_t;


typedef struct ar_ioc_sender_config_st {
    const ar_ioc_config_t   *p_config;
    const ar_osap_config_t  *p_sndosapconfig;
} ar_ioc_sender_config_t;


typedef struct ar_ioccb_st {
    uint32  top;
    uint32  last;
    uint32  queuesz;
    boolean is_lost;
} ar_ioccb_t;

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

extern Std_ReturnType ar_ioc_send_impl(const mkcb_t * const mkcb,
        const IocType receiver_id, const void * const in);
extern void ar_ioc_write_impl(const mkcb_t * const mkcb,
        const IocType receiver_id, const void * const in);
extern void ar_ioc_init(void);
extern void ar_ioc_init_queued(
    IocType     ioc_id);
extern void ar_ioc_init_unqueued(
    IocType     ioc_id,
    const ar_ioc_config_t * const p_config,
    const ar_ioc_receiver_config_t  *p_receiver_config);

extern void ar_ioc_lock_get(const ar_ioc_config_t * const p_config);
extern void ar_ioc_lock_release(const ar_ioc_config_t * const p_config);

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#endif /* AR_IOC_H */
