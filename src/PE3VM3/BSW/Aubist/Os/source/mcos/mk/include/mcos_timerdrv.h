/*
    Copyright (C) 2014 By eSOL Co.,Ltd. Tokyo, Japan

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
[mcos_timerdrv.h] - MCOS timer driver common interfaces
****************************************************************************/
#ifndef MCOS_TIMERDRV_H
#define MCOS_TIMERDRV_H

#if !MCOS_AUTOSAR

#include "mcos_mk.h"

/*** domain public macro ***/
#define MCOS_TIMERDRV_INTERVAL_MAX      (0)

/*** domain public datatype ***/
/* callback function */
typedef void (*timerdrv_callback_t)(uint32_t interval);

/* timer driver control block */
typedef struct tmdrvcb
{
    timerdrv_callback_t callback;   /* callback */
    uint32_t interval;              /* timer interval (msec) */
} tmdrvcb_t;

/*** domain public function ***/
extern mcos_er_t mcos_timerdrv_init(tmdrvcb_t *tmdrvcb);
extern mcos_er_t mcos_timerdrv_start(tmdrvcb_t *tmdrvcb);
extern mcos_er_t mcos_timerdrv_stop(tmdrvcb_t *tmdrvcb);

extern void mcos_timerdrv_set_callback(tmdrvcb_t *tmdrvcb, const timerdrv_callback_t callback);
extern void mcos_timerdrv_set_interval(tmdrvcb_t *tmdrvcb, uint32_t interval);

extern uint32_t mcos_timerdrv_get_offsettime(tmdrvcb_t *tmdrvcb);
extern uint64_t mcos_timerdrv_get_offsettime_nsec(tmdrvcb_t *tmdrvcb);
extern void mcos_timerdrv_clear_offsettime(tmdrvcb_t *tmdrvcb);

extern int32_t mcos_timerdrv_get_int_count(mcos_id_t lcid);

#endif /* !MCOS_AUTOSAR */

#endif /* MCOS_TIMERDRV_H */

