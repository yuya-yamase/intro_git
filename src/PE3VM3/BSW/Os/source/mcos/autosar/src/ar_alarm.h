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
[ar_alarm.h] - Alarm Information
****************************************************************************/

#ifndef AR_ALARM_H
#define AR_ALARM_H

#include "ar_counter.h"

struct ar_alarm_config_st {
    ar_countercb_t          *p_countercb;
    uint32                  autostart_appmodes;
    ar_atr_t                atr;
    TickType                val;
    TickType                cycle;
    ar_funcp_t              act_func;
    uint32                  act_pri;    /* alarm action priority (large value is high) */
    const ar_osap_config_t  *p_osapconfig;
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
    const uint32            *osap_allowedmap;   /* Access allowed OSAP bitmap */
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
};

struct ar_alarmcb_st {
    ar_counter_expire_info_t    info;
    const ar_alarm_config_t     *p_config;
    TickType                    cycle;
};

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

extern void ar_alarm_init(void);

extern StatusType ar_get_alarm_base_impl(
    const AlarmType alarm_id,
    const AlarmBaseRefType p_info,
    const ar_osap_config_t * const p_osapconfig);
extern StatusType ar_get_alarm_impl(
    const AlarmType alarm_id,
    const TickRefType p_tick,
    const ar_osap_config_t * const p_osapconfig);

extern StatusType ar_set_rel_alarm_impl(
    const mkcb_t * const mkcb,
    const AlarmType alarm_id,
    const TickType increment,
    const TickType cycle,
    const ar_osap_config_t * const p_osapconfig);

extern StatusType ar_set_abs_alarm_impl(
    const AlarmType alarm_id,
    const TickType start,
    const TickType cycle,
    const ar_osap_config_t * const p_osapconfig);

extern StatusType ar_cancel_alarm_impl(
    const mkcb_t * const mkcb,
    const AlarmType alarm_id,
    const ar_osap_config_t * const p_osapconfig);

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#endif /* AR_ALARM_H */
