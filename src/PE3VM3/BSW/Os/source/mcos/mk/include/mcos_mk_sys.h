/*
    Copyright (C) 2013 By eSOL Co.,Ltd. Tokyo, Japan

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
[mcos_mk_sys.h] - MCOS micro-kernel hardware-layer common interfaces
****************************************************************************/
#ifndef MCOS_MK_SYS_H
#define MCOS_MK_SYS_H

#include <mcos/system.cfg>
#include "mcos_mk.h"

#if MCOS_AUTOSAR
#include "Os_internal.h"
#endif /* MCOS_AUTOSAR */

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

/* hardware layer interface functions */
void mcos_hwl_init(const mkcb_t * const mkcb, void ** const start, void ** const end);
#if !MCOS_AUTOSAR
void *mcos_hwl_get_errno_addr(void *stack, size_t stacksize);
#endif /* #if !MCOS_AUTOSAR */
#if MCOS_AUTOSAR && (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
mcos_uintptr_t mcos_hwl_init_stack(
    const void * const stack,
    const uint32_t stacksize,
    void (*entry)(const uint32_t stacd, void (*exinf)(void)),
    const uint32_t param,
    void (*exinf)(void),
    const uint32_t um,
    const uint32_t option);
#else /* MCOS_AUTOSAR && (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
#if !MCOS_USE_PROCESS_MODEL
mcos_uintptr_t mcos_hwl_init_stack(
    const void * const stack,
    const uint32_t stacksize,
    void (*entry)(const uint32_t stacd, void (*exinf)(void)),
    const uint32_t param,
    void (*exinf)(void));
#else   /* #if !MCOS_USE_PROCESS_MODEL */
uint32_t mcos_hwl_get_tsd_size(void);
mcos_uintptr_t mcos_hwl_init_stack(
    void * const ssp, 
    void * const usp, 
    void (*entry)(const uint32_t stacd, void (*exinf)(void)), 
    const uint32_t param, 
    void (*exinf)(void));
mcos_bool_t mcos_hwl_check_localspace(void *addr, size_t size);
unsigned int mcos_hwl_get_lsid(void);
void *mcos_hwl_get_uatb(void);
void *mcos_hwl_get_satb(void);
void mcos_hwl_setup_user_mode(void);
#endif /* #if !MCOS_USE_PROCESS_MODEL */
#endif /* MCOS_AUTOSAR && (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
#if !MCOS_AUTOSAR
mcos_er_t mcos_hwl_fmsg_send(mcos_id_t lcid, const fmsg_header_t *header, const uint32_t *pmsg);
mcos_er_t mcos_hwl_fmsg_recv(const mkcb_t *mkcb, fmsg_header_t *header, uint32_t *pmsg);
void mcos_hwl_fmsg_recv_wait(void);
void mcos_hwl_memcpy(void *dst, const void *src, uint32_t size);
#endif /* #if !MCOS_AUTOSAR */
void mcos_hwl_halt(void);
void *mcos_hwl_memarea_lock(const void *addr, uint32_t size);
#if !MCOS_AUTOSAR
void *mcos_hwl_memarea_unlock(void *addr, uint32_t size);
void *mcos_hwl_memarea_get_unlockaddr(void *addr);
#endif /* #if !MCOS_AUTOSAR */

#if (MCOS_CFG_SMSG_SESSION_COUNT_MAX != 0U)
void mcos_hwl_session_init(void);
mcos_erid_t mcos_hwl_session_send_alloc(mcos_id_t tid, mcos_id_t dest_tid, const void *buffer, uint32_t size);
void mcos_hwl_session_send_free(mcos_id_t chid);
void mcos_hwl_session_send_setup(mcos_id_t ssid, scb_t *scb);
void mcos_hwl_session_send_execute(mcos_id_t ssid, scb_t *scb);
mcos_erid_t mcos_hwl_session_receive_alloc(const void *buffer, uint32_t size);
void mcos_hwl_session_receive_free(mcos_id_t chid, scb_t *scb);
void mcos_hwl_session_receive_setup(mcos_id_t ssid, scb_t *scb);
void mcos_hwl_session_receive_get(mcos_id_t ssid, scb_t *scb);
#endif /* #if (MCOS_CFG_SMSG_SESSION_COUNT_MAX != 0U) */
#if MCOS_CFG_DSM_MAX > 0U
#if !MCOS_AUTOSAR
void mcos_hwl_dsm_init(void);
mcos_id_t mcos_hwl_dsm_receive_alloc(void *area, uint32_t size);
void mcos_hwl_dsm_receive_reconf(mcos_id_t chid, void *area, uint32_t size);
void mcos_hwl_dsm_receive_free(mcos_id_t chid, void *area, uint32_t size);
void mcos_hwl_dsm_receive_wait(mcos_id_t chid, void *area, uint32_t size);
void mcos_hwl_dsm_send(mcos_id_t dest_hwclid, mcos_id_t dest_chid, void *area, uint32_t size);
mcos_bool_t mcos_hwl_dsm_is_zerocopy(mcos_id_t hwclid);
void mcos_hwl_dsm_memory_barrier(void);
#endif /* #if !MCOS_AUTOSAR */
#endif /* MCOS_CFG_DSM_MAX > 0U */

#if MCOS_HWCL
void mcos_hwl_shared_isr_assign_init(void);
#endif /* MCOS_HWCL */
#if MCOS_AUTOSAR
mcos_uintptr_t mcos_hwl_ctx_get_sp_of_idle(clscb_t *clscb);
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
void mcos_hwl_call_thread_entry(
    mcos_uintptr_t arg1, 
    void (*arg2)(void), 
    void (*entry)(const uint32_t stacd, void (*exinf)(void)), 
    void *sp, 
    mcos_uintptr_t stksz, 
    uint32_t type, 
    uint32_t um, 
    uint32_t option, 
    const void *p_prev_runosap);
#else /* #if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
void mcos_hwl_call_thread_entry(
    mcos_uintptr_t arg1, 
    void (*arg2)(void), 
    void (*entry)(const uint32_t stacd, void (*exinf)(void)), 
    void *sp, 
    mcos_uintptr_t stksz, 
    uint32_t type);
#endif /* #if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
#endif /* #if MCOS_AUTOSAR */
#if MCOS_CFG_PARAM_CHECK || (MCOS_AUTOSAR && (AR_OS_USE_STACKMONITORING == STD_ON))
void mcos_hwl_get_stack_info(mcos_uintptr_t stkaddr, uint32_t stksize, mcos_uintptr_t *sta, mcos_uintptr_t *end);
#endif /* MCOS_CFG_PARAM_CHECK || (MCOS_AUTOSAR && (AR_OS_USE_STACKMONITORING == STD_ON)) */
#if !MCOS_AUTOSAR
uint32_t mcos_hwl_atomic_cmpset(uint32_t *p, uint32_t c, uint32_t t);
uint32_t mcos_hwl_atomic_add(uint32_t *p, uint32_t t);
void mcos_hwl_mw_init(mcos_id_t lcid);
#endif /* #if !MCOS_AUTOSAR */

#ifdef MCOS_USE_PTAPI
void mcos_hwl_get_register(const void *sp, const void *ssp, posix_debug_cpu_reg_t *reg);
void mcos_hwl_set_register(void *sp, void *ssp, const posix_debug_cpu_reg_t *reg);
#endif /* #ifdef MCOS_USE_PTAPI */

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#endif /* #ifndef MCOS_MK_SYS_H */
