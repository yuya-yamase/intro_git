/*
    Copyright (C) 2013 eSOL Co.,Ltd. Tokyo, Japan

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
[ xmcos.h ] - MCOS external (board-porting) interfaces
****************************************************************************/
#ifndef XMCOS_H
#define XMCOS_H

#include "mcos/mcos.h"
#include <mcos/mcos_syssrv.cfg>

#ifdef __cplusplus
extern "C"
{
#endif

/* xmcos version ver1.0 rev1 */
#define XMCOS_VERSION 1001

#define MCOS_CLMM_MODEL_INTERRUPT   0
#define MCOS_CLMM_MODEL_POLLING     1

#define MCOS_CLMM_ENABLE_LOG        0

/* memory  */
typedef struct xmcos_memory
{
    void * addr;
    uint32_t size;
} xmcos_memory_t;

/* memory infomation */
typedef struct xmcos_memory_info
{
    const xmcos_memory_t * global;
    void * ramend;
} xmcos_memory_info_t;

#if !MCOS_AUTOSAR
/* Get memory infomation */
const xmcos_memory_info_t * xmcos_get_memory_info (void);
#endif /* #if !MCOS_AUTOSAR */

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

/* interrupt initialization */
void xmcos_interrupt_init(void);

/* Interrupt is assigned to self core. */
void xmcos_interrupt_assign(
    const int32_t iid);

#if !MCOS_AUTOSAR
/* Interrupt is unassigned from self core. */
void xmcos_interrupt_unassign(
    const int32_t iid);
#endif /* #if !MCOS_AUTOSAR */

/* Bind interrupt to specific core */
void xmcos_interrupt_bind(
    const uint32_t pcid,
    const int32_t iid);

/* hardware initialization */
void xmcos_hw_init(void);

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#if !MCOS_AUTOSAR
/* DS timer get time (nano sec) */
uint64_t xmcos_ds_timer_get(void);


/* start performance measurement */
void xmcos_ds_prfm_start(void);

/* stop performance measurement counter */
void xmcos_ds_prfm_stop(void);

/* end performance measurement */
uint32_t xmcos_ds_prfm_end(void);
#endif /* #if !MCOS_AUTOSAR */


/* system timer info */
struct xmcos_timer_info {
    uint32_t    clock;
    uint16_t    intno;
    uint32_t    interval_max;
    uint64_t    counter_max;
};

typedef struct xmcos_timer_info xmcos_timer_info_t;

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

const xmcos_timer_info_t * xmcos_timer_get_about(
    const uint32_t pcid);

void xmcos_timer_init(
    const uint32_t pcid);

void xmcos_timer_open(
    const uint32_t pcid);

void xmcos_timer_close(
    const uint32_t pcid);

void xmcos_timer_set_interval(
    const uint32_t pcid,
    const uint64_t interval);

void xmcos_slave_start(uint32_t pcid);

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* #ifndef XMCOS_H */
