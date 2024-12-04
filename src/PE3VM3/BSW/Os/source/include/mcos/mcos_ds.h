/*
    Copyright (C) 2011 By eSOL Co.,Ltd. Tokyo, Japan

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
[mcos_ds.h] - MCOS Debug Support API interface header
****************************************************************************/
#ifndef MCOS_DS_H
#define MCOS_DS_H

#include <inttypes.h>
#include <stdbool.h>
#include "mcos/mcos.h"

#include <mcos/system.cfg>
#include <mcos/mcos_ds.cfg>

#ifdef __cplusplus
extern "C"
{
#endif

/* user specified syslog bit */
/* fatal error and MCOS API error message */
#define MCOS_CFG_DS_SYSLOG_BIT_ERROR       0x1UL
/* MCOS API calling message */
#define MCOS_CFG_DS_SYSLOG_BIT_API         0x2UL
/* thread operation message */
#define MCOS_CFG_DS_SYSLOG_BIT_THREAD      0x4UL
/* server thread operation message */
#define MCOS_CFG_DS_SYSLOG_BIT_SERVER      0x8UL
/* message operation message */
#define MCOS_CFG_DS_SYSLOG_BIT_MSG         0x10UL
/* boot sequence message */
#define MCOS_CFG_DS_SYSLOG_BIT_BOOT        0x20UL
/* Hardware layer log message */
#define MCOS_CFG_DS_SYSLOG_BIT_HWL         0x40UL
/* Inter-MK message log message */
#define MCOS_CFG_DS_SYSLOG_BIT_MKMSG       0x80UL
/* core local scheduler thread queue dump */
#define MCOS_CFG_DS_SYSLOG_BIT_THREAD_QUEUE 0x100UL

/* convert syslog level to bit vector */
#if MCOS_CFG_DS_SYSLOG_LEVEL == 0U
#define MCOS_CFG_DS_SYSLOG_BITS_BY_LEVEL    0UL
#elif MCOS_CFG_DS_SYSLOG_LEVEL == 1U
#define MCOS_CFG_DS_SYSLOG_BITS_BY_LEVEL    (MCOS_CFG_DS_SYSLOG_BIT_ERROR)
#elif MCOS_CFG_DS_SYSLOG_LEVEL == 2U
#define MCOS_CFG_DS_SYSLOG_BITS_BY_LEVEL    (MCOS_CFG_DS_SYSLOG_BIT_ERROR|\
                                             MCOS_CFG_DS_SYSLOG_BIT_API)
#elif MCOS_CFG_DS_SYSLOG_LEVEL == 3U
#define MCOS_CFG_DS_SYSLOG_BITS_BY_LEVEL    (MCOS_CFG_DS_SYSLOG_BIT_ERROR|\
  MCOS_CFG_DS_SYSLOG_BIT_API|\
  MCOS_CFG_DS_SYSLOG_BIT_THREAD|\
  MCOS_CFG_DS_SYSLOG_BIT_SERVER|\
  MCOS_CFG_DS_SYSLOG_BIT_MSG|\
  MCOS_CFG_DS_SYSLOG_BIT_BOOT|\
  MCOS_CFG_DS_SYSLOG_BIT_THREAD_QUEUE)
#elif MCOS_CFG_DS_SYSLOG_LEVEL == 4U
#define MCOS_CFG_DS_SYSLOG_BITS_BY_LEVEL    (MCOS_CFG_DS_SYSLOG_BIT_ERROR|\
  MCOS_CFG_DS_SYSLOG_BIT_API|\
  MCOS_CFG_DS_SYSLOG_BIT_THREAD|\
  MCOS_CFG_DS_SYSLOG_BIT_SERVER|\
  MCOS_CFG_DS_SYSLOG_BIT_MSG|\
  MCOS_CFG_DS_SYSLOG_BIT_BOOT|\
  MCOS_CFG_DS_SYSLOG_BIT_THREAD_QUEUE|\
  MCOS_CFG_DS_SYSLOG_BIT_HWL|\
  MCOS_CFG_DS_SYSLOG_BIT_MKMSG)
#endif /* MCOS_CFG_DS_SYSLOG_LEVEL == 0U */

/* define syslog bit vector by level bits and user specified bits */
#define MCOS_CFG_DS_SYSLOG_BITS1     (MCOS_CFG_DS_SYSLOG_BITS_BY_LEVEL|\
  ((MCOS_CFG_DS_SYSLOG_TYPE_ERROR!=0U) ? MCOS_CFG_DS_SYSLOG_BIT_ERROR : 0UL)|\
  ((MCOS_CFG_DS_SYSLOG_TYPE_API!=0U)   ? MCOS_CFG_DS_SYSLOG_BIT_API   : 0UL)|\
  ((MCOS_CFG_DS_SYSLOG_TYPE_THREAD!=0U)? MCOS_CFG_DS_SYSLOG_BIT_THREAD: 0UL)|\
  ((MCOS_CFG_DS_SYSLOG_TYPE_SERVER!=0U)? MCOS_CFG_DS_SYSLOG_BIT_SERVER: 0UL)|\
  ((MCOS_CFG_DS_SYSLOG_TYPE_MSG!=0U)   ? MCOS_CFG_DS_SYSLOG_BIT_MSG   : 0UL))

#define MCOS_CFG_DS_SYSLOG_BITS     (MCOS_CFG_DS_SYSLOG_BITS1|\
  ((MCOS_CFG_DS_SYSLOG_TYPE_BOOT!=0U)  ? MCOS_CFG_DS_SYSLOG_BIT_BOOT  : 0UL)|\
  ((MCOS_CFG_DS_SYSLOG_TYPE_HWL!=0U)   ? MCOS_CFG_DS_SYSLOG_BIT_HWL   : 0UL)|\
  ((MCOS_CFG_DS_SYSLOG_TYPE_MKMSG!=0U) ? MCOS_CFG_DS_SYSLOG_BIT_MKMSG : 0UL)|\
  ((MCOS_CFG_DS_SYSLOG_TYPE_THREAD_QUEUE!=0U) ? MCOS_CFG_DS_SYSLOG_BIT_THREAD_QUEUE : 0UL))

#define IS_DS_SYSLOG_ERROR         ((MCOS_CFG_DS_SYSLOG_ENABLE !=0U) && ((MCOS_CFG_DS_SYSLOG_BITS & MCOS_CFG_DS_SYSLOG_BIT_ERROR) != 0UL))
#define IS_DS_SYSLOG_API           ((MCOS_CFG_DS_SYSLOG_ENABLE !=0U) && ((MCOS_CFG_DS_SYSLOG_BITS & MCOS_CFG_DS_SYSLOG_BIT_API)   != 0UL))
#define IS_DS_SYSLOG_THREAD        ((MCOS_CFG_DS_SYSLOG_ENABLE !=0U) && ((MCOS_CFG_DS_SYSLOG_BITS & MCOS_CFG_DS_SYSLOG_BIT_THREAD)!= 0UL))
#define IS_DS_SYSLOG_SERVER        ((MCOS_CFG_DS_SYSLOG_ENABLE !=0U) && ((MCOS_CFG_DS_SYSLOG_BITS & MCOS_CFG_DS_SYSLOG_BIT_SERVER)!= 0UL))
#define IS_DS_SYSLOG_MSG           ((MCOS_CFG_DS_SYSLOG_ENABLE !=0U) && ((MCOS_CFG_DS_SYSLOG_BITS & MCOS_CFG_DS_SYSLOG_BIT_MSG)   != 0UL))
#define IS_DS_SYSLOG_BOOT          ((MCOS_CFG_DS_SYSLOG_ENABLE !=0U) && ((MCOS_CFG_DS_SYSLOG_BITS & MCOS_CFG_DS_SYSLOG_BIT_BOOT)  != 0UL))
#define IS_DS_SYSLOG_HWL           ((MCOS_CFG_DS_SYSLOG_ENABLE !=0U) && ((MCOS_CFG_DS_SYSLOG_BITS & MCOS_CFG_DS_SYSLOG_BIT_HWL)   != 0UL))
#define IS_DS_SYSLOG_MKMSG         ((MCOS_CFG_DS_SYSLOG_ENABLE !=0U) && ((MCOS_CFG_DS_SYSLOG_BITS & MCOS_CFG_DS_SYSLOG_BIT_MKMSG) != 0UL))
#define IS_DS_SYSLOG_THREAD_QUEUE  ((MCOS_CFG_DS_SYSLOG_ENABLE !=0U) && ((MCOS_CFG_DS_SYSLOG_BITS & MCOS_CFG_DS_SYSLOG_BIT_THREAD_QUEUE) != 0UL))
#define IS_DS_SYSLOG_ANY           ((MCOS_CFG_DS_SYSLOG_ENABLE !=0U) && (MCOS_CFG_DS_SYSLOG_BITS != 0UL))

typedef const unsigned char * mcos_ds_str_t;

#if MCOS_AUTOSAR
#define OS_START_SEC_CODE
#include "Os_MemMap.h"
#endif /* MCOS_AUTOSAR */

void mcos_debug_printf(mcos_ds_str_t fmt, ... );

void mcos_debug_break(void);

#if !MCOS_AUTOSAR
uint64_t mcos_debug_time_get(void);
void mcos_debug_elapse_start(void);
void mcos_debug_elapse_end(void);
void mcos_debug_workload_start(void);
void mcos_debug_workload_end(void);

void mcos_debug_prfm_start(void);
uint32_t mcos_debug_prfm_end(void);
void mcos_debug_prfm_hook(void);
uint8_t mcos_debug_prfm_num(void);
uint32_t mcos_debug_prfm_read(uint32_t idx);
#endif /* #if !MCOS_AUTOSAR */

#if MCOS_USE_PROCESS_MODEL
/* Get current thread ID */
mcos_id_t mcos_debug_thread_getid(void);
/* Get current process ID */
mcos_id_t mcos_debug_process_getid(void);
/* Get current process ID that specified thread belongs to */
mcos_id_t mcos_debug_process_getid_by_tid(mcos_id_t tid);
/* Get system operating time (up time) */
uint64_t mcos_debug_trace_time_get(uint64_t *remainder);
/* Get operation clock of system timer */
uint64_t mcos_debug_trace_time_clock_get(void);
#endif /* MCOS_USE_PROCESS_MODEL */

#if MCOS_AUTOSAR
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"
#endif /* MCOS_AUTOSAR */

/* API trace definition */
typedef void (*syscall_enter_t)(uint16_t fncd, uint16_t objid, const void *pc, const void *ssp);
typedef void (*syscall_leave_t)(uint16_t fncd, mcos_uintptr_t ret, const void *ssp);
typedef struct mcos_ds_trace_hook_syscall   mcos_ds_trace_hook_syscall_t;
struct mcos_ds_trace_hook_syscall
{
    syscall_enter_t     enter;      /* Hook routine before calling SVC */
    syscall_leave_t     leave;      /* Hook routine after calling SVC */
};

/* Interrupt trace definition */
typedef void (*interrupt_enter_t)(mcos_id_t intno, const void *epc, const void *ssp);
typedef void (*interrupt_leave_t)(mcos_id_t intno, const void *epc, const void *ssp);
typedef struct mcos_ds_trace_hook_interrupt mcos_ds_trace_hook_interrupt_t;
struct mcos_ds_trace_hook_interrupt
{
    interrupt_enter_t   enter;      /* Hook routine before calling handler */
    interrupt_leave_t   leave;      /* Hook routine after calling handler */
};

/* Exception trace definition */
typedef void (*exception_enter_t)(mcos_id_t excno, const void *epc, const void *ssp);
typedef void (*exception_leave_t)(mcos_id_t excno, const void *epc, const void *ssp);
typedef struct mcos_ds_trace_hook_exception mcos_ds_trace_hook_exception_t;
struct mcos_ds_trace_hook_exception
{
    exception_enter_t   enter;      /* Hook routine before calling handler */
    exception_leave_t   leave;      /* Hook routine after calling handler */
};

/* Thread trace definition */
typedef void (*thread_enter_t)(mcos_id_t tid, const void *entry, mcos_uintptr_t arg, const void *sp);
typedef void (*thread_leave_t)(mcos_id_t tid, const void *sp);
typedef struct mcos_ds_trace_hook_thread    mcos_ds_trace_hook_thread_t;
struct mcos_ds_trace_hook_thread
{
    thread_enter_t      enter;      /* Hook routine at thread start */
    thread_leave_t      leave;      /* Hook routine at thread exit */
};

/* Thread dispatch trace definition */
typedef void (*dispatch_t)(mcos_id_t new_tid, mcos_id_t old_tid, uint8_t new_prio, uint8_t old_prio,
                           mcos_char_t *new_name, mcos_char_t *old_name, uint32_t old_state, const void *sp);
typedef struct mcos_ds_trace_hook_dispatch  mcos_ds_trace_hook_dispatch_t;
struct mcos_ds_trace_hook_dispatch
{
    dispatch_t          dispatch;   /* Hook routine at dispatching */
};

/* Thread migration trace definition */
typedef void (*migration_t)(mcos_id_t tid, mcos_id_t new_coreid, mcos_id_t old_coreid, uint8_t prio, mcos_char_t *name);
typedef struct mcos_ds_trace_hook_migration mcos_ds_trace_hook_migration_t;
struct mcos_ds_trace_hook_migration
{
    migration_t         migration;  /* Hook routine at migration */
};

typedef struct mcos_ds_trace_hook mcos_ds_trace_hook_t;
struct mcos_ds_trace_hook
{
    mcos_ds_trace_hook_syscall_t    syscall;
    mcos_ds_trace_hook_interrupt_t  interrupt;
    mcos_ds_trace_hook_exception_t  exception;
    mcos_ds_trace_hook_thread_t     thread;
    mcos_ds_trace_hook_dispatch_t   dispatch;
#if !MCOS_AUTOSAR
    mcos_ds_trace_hook_migration_t  migration;
#endif /* #if !MCOS_AUTOSAR */
};

#if MCOS_AUTOSAR
#define OS_START_SEC_CODE
#include "Os_MemMap.h"
#endif /* MCOS_AUTOSAR */

#if !MCOS_AUTOSAR
/* Registration trace */
mcos_er_t mcos_debug_trace_hook_syscall_register(mcos_ds_trace_hook_syscall_t *hook);
mcos_er_t mcos_debug_trace_hook_interrupt_register(mcos_ds_trace_hook_interrupt_t *hook);
mcos_er_t mcos_debug_trace_hook_exception_register(mcos_ds_trace_hook_exception_t *hook);
mcos_er_t mcos_debug_trace_hook_thread_register(mcos_ds_trace_hook_thread_t *hook);
mcos_er_t mcos_debug_trace_hook_dispatch_register(mcos_ds_trace_hook_dispatch_t *hook);
mcos_er_t mcos_debug_trace_hook_migration_register(mcos_ds_trace_hook_migration_t *hook);
mcos_er_t mcos_debug_trace_hook_register(mcos_ds_trace_hook_t *hooks);
#endif /* #if !MCOS_AUTOSAR */

/* Hook point */
void mcos_ds_trace_hook_apiEntry(uint16_t fncd, uint16_t objid, const void *pc, const void *sp);
void mcos_ds_trace_hook_apiExit(uint16_t fncd, mcos_uintptr_t ret, const void *sp);
void mcos_ds_trace_hook_interruptEntry(mcos_id_t intno, const void *epc, const void *ssp);
void mcos_ds_trace_hook_interruptExit(mcos_id_t intno, const void *epc, const void *ssp);
void mcos_ds_trace_hook_exceptionEntry(mcos_id_t excno, const void *epc, const void *ssp);
void mcos_ds_trace_hook_exceptionExit(mcos_id_t excno, const void *epc, const void *ssp);
void mcos_ds_trace_hook_threadEntry(mcos_id_t tid, const void *entry, mcos_uintptr_t arg, const void *sp);
void mcos_ds_trace_hook_threadExit(mcos_id_t tid, const void *sp);
void mcos_ds_trace_hook_threadSwitch(mcos_id_t new_tid, mcos_id_t old_tid, uint8_t new_prio, uint8_t old_prio,
                                     mcos_char_t *new_name, mcos_char_t *old_name, uint32_t old_state, const void *sp);
void mcos_ds_trace_hook_threadMigration(mcos_id_t tid, mcos_id_t new_coreid, mcos_id_t old_coreid,
                                        uint8_t prio, mcos_char_t *name);

#if !MCOS_AUTOSAR
/* Hook point utility */
uint16_t mcos_ds_trace_hook_api_objid_get(uint16_t fncd, mcos_intptr_t key);
#endif /* #if !MCOS_AUTOSAR */

#if MCOS_AUTOSAR
/* user implementation hook */
void mcos_debug_trace_hook_initialization(void);
void mcos_debug_trace_hook_finalization(void);
void mcos_debug_trace_hook_start(void);
void mcos_debug_trace_hook_stop(void);
void mcos_debug_trace_hook_set_info(uint32_t *p_info1, int64_t *p_info2);
#endif /* MCOS_AUTOSAR */

#if MCOS_AUTOSAR
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"
#endif /* MCOS_AUTOSAR */

/* Trace */
/* upper 3bit is project no. */
/*    0 : native             */
/*    1 : POSIX              */
/*    2 : USER trace         */
/*    3 : eMCOS AUTOSAR      */
#define MCOS_TRACE_OBJID_NONE                       (0x0)
#define MCOS_TRACE_OBJID_CORE                       (0x1)
#define MCOS_TRACE_OBJID_THREAD                     (0x2)
#define MCOS_TRACE_OBJID_MESSAGE                    (0x3)
#define MCOS_TRACE_OBJID_CYCLIC                     (0x4)
#define MCOS_TRACE_OBJID_INTERRUPT                  (0x5)
#define MCOS_TRACE_OBJID_SERVER                     (0x6)
#define MCOS_TRACE_OBJID_HEAP                       (0x7)
#define MCOS_TRACE_OBJID_GENERIC                    (0x8)
#define MCOS_TRACE_OBJID_THREADPOOL                 (0x9)
#define MCOS_TRACE_OBJID_MEMORY                     (0xa)
#define MCOS_TRACE_OBJID_PARTITION                  (0xb)
#define MCOS_TRACE_OBJID_DSM                        (0xc)
#define MCOS_TRACE_OBJID_USER                       (0x40)
#define MCOS_TRACE_OBJID_POSIX                      (0x20)
#define MCOS_TRACE_OBJID_POSIX_MCOS                 (0x20) /* SVC ver. */
#define MCOS_TRACE_OBJID_POSIX_LFS                  (0x21)
#define MCOS_TRACE_OBJID_POSIX_PTHREAD_THREAD       (0x22)
#define MCOS_TRACE_OBJID_POSIX_PTHREAD_MUTEX        (0x23)
#define MCOS_TRACE_OBJID_POSIX_PTHREAD_RWLOCK       (0x24)
#define MCOS_TRACE_OBJID_POSIX_PTHREAD_COND         (0x25)
#define MCOS_TRACE_OBJID_POSIX_PTHREAD_BARRIER      (0x26)
#define MCOS_TRACE_OBJID_POSIX_PROCESS              (0x27)
#define MCOS_TRACE_OBJID_POSIX_MMAP                 (0x28)
#define MCOS_TRACE_OBJID_POSIX_TIME                 (0x29)
#define MCOS_TRACE_OBJID_POSIX_SEM                  (0x2a)
#define MCOS_TRACE_OBJID_POSIX_SIGNAL               (0x2b)
#define MCOS_TRACE_OBJID_POSIX_PIPE                 (0x2c)
#define MCOS_TRACE_OBJID_POSIX_SOCKET               (0x2d)
#define MCOS_TRACE_OBJID_POSIX_MQ                   (0x2e)
#define MCOS_TRACE_OBJID_POSIX_TIMER                (0x2f)
#define MCOS_TRACE_OBJID_POSIX_AIO                  (0x30)
#define MCOS_TRACE_OBJID_AUTOSAR_OS                 (0x60)
#define MCOS_TRACE_OBJID_AUTOSAR_CORE               (0x61)
#define MCOS_TRACE_OBJID_AUTOSAR_OSAPPLICATION      (0x62)
#define MCOS_TRACE_OBJID_AUTOSAR_INTERRUPT          (0x63)
#define MCOS_TRACE_OBJID_AUTOSAR_TASK               (0x64)
#define MCOS_TRACE_OBJID_AUTOSAR_EVENT              (0x65)
#define MCOS_TRACE_OBJID_AUTOSAR_RESOURCE           (0x66)
#define MCOS_TRACE_OBJID_AUTOSAR_COUNTER            (0x67)
#define MCOS_TRACE_OBJID_AUTOSAR_ALARM              (0x68)
#define MCOS_TRACE_OBJID_AUTOSAR_IOC                (0x69)
#define MCOS_TRACE_OBJID_AUTOSAR_SPINLOCK           (0x6a)
#define MCOS_TRACE_OBJID_AUTOSAR_OBJECTACCESS       (0x6b)
#define MCOS_TRACE_OBJID_AUTOSAR_TRUSTEDFUNCTION    (0x6c)

#define MCOS_TRACE_OBJID_GET(funcno)                (((funcno) >> 8) & 0xff)
#define MCOS_TRACE_FUNCNO2SVCFN(funcno)             ((funcno) & (uint16_t)~MCOS_TRACE_OBJID_POSIX)
#define MCOS_TRACE_SVCFN2FUNCNO(svcfn)              ((svcfn) | (uint16_t)(MCOS_TRACE_OBJID_POSIX << 8))

#define MCOS_TRACE_FUNCNO_TIME_SET                  ((uint16_t)(MCOS_TRACE_OBJID_NONE   << 8) | 0x01)
#define MCOS_TRACE_FUNCNO_TIME_GET                  ((uint16_t)(MCOS_TRACE_OBJID_NONE   << 8) | 0x02)
#define MCOS_TRACE_FUNCNO_ALL_INTERRUPT_DISABLE     ((uint16_t)(MCOS_TRACE_OBJID_NONE   << 8) | 0x03)
#define MCOS_TRACE_FUNCNO_ALL_INTERRUPT_ENABLE      ((uint16_t)(MCOS_TRACE_OBJID_NONE   << 8) | 0x04)

#define MCOS_TRACE_FUNCNO_CORE_GET_INFO             ((uint16_t)(MCOS_TRACE_OBJID_CORE   << 8) | 0x01)
#define MCOS_TRACE_FUNCNO_THREAD_CREATE             ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x01)
#define MCOS_TRACE_FUNCNO_THREAD_DELETE             ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x02)
#define MCOS_TRACE_FUNCNO_THREAD_START              ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x03)
#define MCOS_TRACE_FUNCNO_THREAD_EXIT               ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x04)
#define MCOS_TRACE_FUNCNO_THREAD_GETID              ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x05)
#define MCOS_TRACE_FUNCNO_THREAD_MIGRATE            ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x06)
#define MCOS_TRACE_FUNCNO_THREAD_SLEEP              ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x07)
#define MCOS_TRACE_FUNCNO_THREAD_WAKEUP             ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x08)
#define MCOS_TRACE_FUNCNO_THREAD_DELAY              ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x09)
#define MCOS_TRACE_FUNCNO_THREAD_GET_NAME           ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x0a)
#define MCOS_TRACE_FUNCNO_THREAD_GET_ID_BY_NAME     ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x0b)
#define MCOS_TRACE_FUNCNO_THREAD_GET_INFO           ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x0c)
#define MCOS_TRACE_FUNCNO_MESSAGE_SEND              ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x0d)
#define MCOS_TRACE_FUNCNO_MESSAGE_RECEIVE           ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x0e)
#define MCOS_TRACE_FUNCNO_RRMESSAGE_SEND            ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x0f)
#define MCOS_TRACE_FUNCNO_RRMESSAGE_RECEIVE         ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x10)
#define MCOS_TRACE_FUNCNO_RRMESSAGE_REPLY           ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x11)
#define MCOS_TRACE_FUNCNO_FMESSAGE_SEND             ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x12)
#define MCOS_TRACE_FUNCNO_FMESSAGE_RECEIVE          ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x13)
#define MCOS_TRACE_FUNCNO_MESSAGE_CONTROL           ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x14)
#define MCOS_TRACE_FUNCNO_THREADATTR_INIT           ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x15)
#define MCOS_TRACE_FUNCNO_THREADATTR_GETLCID        ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x16)
#define MCOS_TRACE_FUNCNO_THREADATTR_SETLCID        ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x17)
#define MCOS_TRACE_FUNCNO_THREADATTR_GETPRIORITY    ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x18)
#define MCOS_TRACE_FUNCNO_THREADATTR_SETPRIORITY    ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x19)
#define MCOS_TRACE_FUNCNO_THREADATTR_GETDELETE      ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x1a)
#define MCOS_TRACE_FUNCNO_THREADATTR_SETDELETE      ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x1b)
#define MCOS_TRACE_FUNCNO_THREADATTR_GETSTDMSG      ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x1c)
#define MCOS_TRACE_FUNCNO_THREADATTR_SETSTDMSG      ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x1d)
#define MCOS_TRACE_FUNCNO_THREADATTR_GETPRIORITYINHERITANCE ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x1e)
#define MCOS_TRACE_FUNCNO_THREADATTR_SETPRIORITYINHERITANCE ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x1f)
#define MCOS_TRACE_FUNCNO_THREADATTR_GETSTACKSIZE   ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x20)
#define MCOS_TRACE_FUNCNO_THREADATTR_SETSTACKSIZE   ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x21)
#define MCOS_TRACE_FUNCNO_THREADATTR_GETSTACKADDR   ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x22)
#define MCOS_TRACE_FUNCNO_THREADATTR_SETSTACKADDR   ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x23)
#define MCOS_TRACE_FUNCNO_THREADATTR_GETNAME        ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x24)
#define MCOS_TRACE_FUNCNO_THREADATTR_SETNAME        ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x25)
#define MCOS_TRACE_FUNCNO_THREAD_SUSPEND            ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x26)
#define MCOS_TRACE_FUNCNO_THREAD_RESUME             ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x27)

/* AUTOSAR only TRACE */
#define MCOS_TRACE_FUNCNO_THREADATTR_GETBASICTHREAD ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x28)
#define MCOS_TRACE_FUNCNO_THREADATTR_SETBASICTHREAD ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x29)
#define MCOS_TRACE_FUNCNO_THREADATTR_GETSHAREDSTACK ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x2a)
#define MCOS_TRACE_FUNCNO_THREADATTR_SETSHAREDSTACK ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x2b)
#define MCOS_TRACE_FUNCNO_THREADATTR_GETMAXACTCOUNT ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x2c)
#define MCOS_TRACE_FUNCNO_THREADATTR_SETMAXACTCOUNT ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x2d)
#define MCOS_TRACE_FUNCNO_THREADATTR_GETAUTOSARTHREAD ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x2e)
#define MCOS_TRACE_FUNCNO_THREADATTR_SETAUTOSARTHREAD ((uint16_t)(MCOS_TRACE_OBJID_THREAD << 8) | 0x2f)

/* kpof TRACE */
#define MCOS_TRACE_FUNCNO_KPROFTHRSTK_GETINFO       ((uint16_t)(MCOS_TRACE_OBJID_THREAD  << 8) | 0x30)

#define MCOS_TRACE_FUNCNO_SMESSAGE_TX_OPEN          ((uint16_t)(MCOS_TRACE_OBJID_THREAD  << 8) | 0x31)
#define MCOS_TRACE_FUNCNO_SMESSAGE_RX_OPEN          ((uint16_t)(MCOS_TRACE_OBJID_THREAD  << 8) | 0x32)

#define MCOS_TRACE_FUNCNO_SMESSAGE_TX_CLOSE         ((uint16_t)(MCOS_TRACE_OBJID_MESSAGE << 8) | 0x01)
#define MCOS_TRACE_FUNCNO_SMESSAGE_TX_ALLOCATE      ((uint16_t)(MCOS_TRACE_OBJID_MESSAGE << 8) | 0x02)
#define MCOS_TRACE_FUNCNO_SMESSAGE_TX_SEND          ((uint16_t)(MCOS_TRACE_OBJID_MESSAGE << 8) | 0x03)
#define MCOS_TRACE_FUNCNO_SMESSAGE_RX_CLOSE         ((uint16_t)(MCOS_TRACE_OBJID_MESSAGE << 8) | 0x04)
#define MCOS_TRACE_FUNCNO_SMESSAGE_RX_RECEIVE       ((uint16_t)(MCOS_TRACE_OBJID_MESSAGE << 8) | 0x05)
#define MCOS_TRACE_FUNCNO_SMESSAGE_RX_FREE          ((uint16_t)(MCOS_TRACE_OBJID_MESSAGE << 8) | 0x06)
#define MCOS_TRACE_FUNCNO_SMESSAGE_GET_INFO         ((uint16_t)(MCOS_TRACE_OBJID_MESSAGE << 8) | 0x07)

#define MCOS_TRACE_FUNCNO_CYCLIC_CREATE             ((uint16_t)(MCOS_TRACE_OBJID_CYCLIC << 8) | 0x01)
#define MCOS_TRACE_FUNCNO_CYCLIC_DELETE             ((uint16_t)(MCOS_TRACE_OBJID_CYCLIC << 8) | 0x02)

#define MCOS_TRACE_FUNCNO_INTERRUPT_DEFINE          ((uint16_t)(MCOS_TRACE_OBJID_INTERRUPT << 8) | 0x01)
#define MCOS_TRACE_FUNCNO_INTERRUPT_DISABLE         ((uint16_t)(MCOS_TRACE_OBJID_INTERRUPT << 8) | 0x02)
#define MCOS_TRACE_FUNCNO_INTERRUPT_ENABLE          ((uint16_t)(MCOS_TRACE_OBJID_INTERRUPT << 8) | 0x03)
#define MCOS_TRACE_FUNCNO_INTERRUPT_CLEAR           ((uint16_t)(MCOS_TRACE_OBJID_INTERRUPT << 8) | 0x04)

#define MCOS_TRACE_FUNCNO_SERVER_REGISTER           ((uint16_t)(MCOS_TRACE_OBJID_SERVER << 8) | 0x01)
#define MCOS_TRACE_FUNCNO_SERVER_UNREGISTER         ((uint16_t)(MCOS_TRACE_OBJID_SERVER << 8) | 0x02)
#define MCOS_TRACE_FUNCNO_SERVER_GETID              ((uint16_t)(MCOS_TRACE_OBJID_SERVER << 8) | 0x03)
#define MCOS_TRACE_FUNCNO_SERVER_GETNSID            ((uint16_t)(MCOS_TRACE_OBJID_SERVER << 8) | 0x04)
#define MCOS_TRACE_FUNCNO_SERVER_REPLY              ((uint16_t)(MCOS_TRACE_OBJID_SERVER << 8) | 0x05)

#define MCOS_TRACE_FUNCNO_HEAP_ALLOCATE             ((uint16_t)(MCOS_TRACE_OBJID_HEAP << 8) | 0x01)
#define MCOS_TRACE_FUNCNO_HEAP_FREE                 ((uint16_t)(MCOS_TRACE_OBJID_HEAP << 8) | 0x02)
#define MCOS_TRACE_FUNCNO_HEAP_ALLOCATE_BLOCK       ((uint16_t)(MCOS_TRACE_OBJID_HEAP << 8) | 0x03)
#define MCOS_TRACE_FUNCNO_HEAP_FREE_BLOCK           ((uint16_t)(MCOS_TRACE_OBJID_HEAP << 8) | 0x04)
#define MCOS_TRACE_FUNCNO_HEAP_GET_INFO             ((uint16_t)(MCOS_TRACE_OBJID_HEAP << 8) | 0x05)

#define MCOS_TRACE_FUNCNO_NAME_REGISTER             ((uint16_t)(MCOS_TRACE_OBJID_GENERIC << 8) | 0x01)
#define MCOS_TRACE_FUNCNO_NAME_UNREGISTER           ((uint16_t)(MCOS_TRACE_OBJID_GENERIC << 8) | 0x02)
#define MCOS_TRACE_FUNCNO_NAME_LOOKUP               ((uint16_t)(MCOS_TRACE_OBJID_GENERIC << 8) | 0x03)

#define MCOS_TRACE_FUNCNO_THREADPOOL_CREATE         ((uint16_t)(MCOS_TRACE_OBJID_THREADPOOL << 8) | 0x01)
#define MCOS_TRACE_FUNCNO_THREADPOOL_DELETE         ((uint16_t)(MCOS_TRACE_OBJID_THREADPOOL << 8) | 0x02)
#define MCOS_TRACE_FUNCNO_THREADPOOL_EXECUTE        ((uint16_t)(MCOS_TRACE_OBJID_THREADPOOL << 8) | 0x03)
#define MCOS_TRACE_FUNCNO_THREADPOOL_WAIT           ((uint16_t)(MCOS_TRACE_OBJID_THREADPOOL << 8) | 0x04)
#define MCOS_TRACE_FUNCNO_THREADPOOL_ACTIVATE       ((uint16_t)(MCOS_TRACE_OBJID_THREADPOOL << 8) | 0x05)
#define MCOS_TRACE_FUNCNO_THREADPOOL_DEACTIVATE     ((uint16_t)(MCOS_TRACE_OBJID_THREADPOOL << 8) | 0x06)

#define MCOS_TRACE_FUNCNO_DSM_CREATE                ((uint16_t)(MCOS_TRACE_OBJID_DSM << 8) | 0x01)
#define MCOS_TRACE_FUNCNO_DSM_DELETE                ((uint16_t)(MCOS_TRACE_OBJID_DSM << 8) | 0x02)
#define MCOS_TRACE_FUNCNO_DSM_ATTACH                ((uint16_t)(MCOS_TRACE_OBJID_DSM << 8) | 0x03)
#define MCOS_TRACE_FUNCNO_DSM_REATTACH              ((uint16_t)(MCOS_TRACE_OBJID_DSM << 8) | 0x04)
#define MCOS_TRACE_FUNCNO_DSM_DETACH                ((uint16_t)(MCOS_TRACE_OBJID_DSM << 8) | 0x05)
#define MCOS_TRACE_FUNCNO_DSM_GET_INFO              ((uint16_t)(MCOS_TRACE_OBJID_DSM << 8) | 0x06)

#define MCOS_TRACE_FUNCNO_MEMORY_CHECK_BY_TID       ((uint16_t)(MCOS_TRACE_OBJID_MEMORY << 8) | 0x01)

#define MCOS_TRACE_FUNCNO_PARTITION_REBOOT          ((uint16_t)(MCOS_TRACE_OBJID_PARTITION << 8) | 0x01)

#ifdef MCOS_USE_PTAPI
#include <mcos/posix/mcos_ds_posix.h>
#endif /* MCOS_USE_PTAPI */

#define MCOS_TRACE_STOPCOND_NONE                        (0)
#define MCOS_TRACE_STOPCOND_BUFFER_FULL                 (1)

#if MCOS_AUTOSAR
#define OS_START_SEC_CODE
#include "Os_MemMap.h"
#endif /* MCOS_AUTOSAR */

mcos_er_t mcos_debug_trace_start(uint8_t stopcond);
void mcos_debug_trace_stop(void);
mcos_er_t mcos_debug_trace_user_event(int32_t value1, int32_t value2);

#if MCOS_AUTOSAR
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"
#endif /* MCOS_AUTOSAR */

#if MCOS_CFG_DS_MSGPROF_ENABLE

/* message direction */
typedef uint8_t mcos_msgprof_message_direction_t;
#define MCOS_MSGPROF_MESSAGE_DIRECTION_SEND         (0)
#define MCOS_MSGPROF_MESSAGE_DIRECTION_RECV         (1)

/* message information */
typedef struct {
    mcos_msgprof_message_direction_t direction;
    size_t size;
    mcos_id_t src_lcid;
    mcos_id_t src_tid;
    mcos_id_t dst_lcid;
    mcos_id_t dst_tid;
} mcos_msgprof_message_info_t;

/* callback function type for messaging */
typedef void (*mcos_msgprof_message_callback_t)(const mcos_msgprof_message_info_t* message_info);

/* callback function type for creating thread */
typedef void (*mcos_msgprof_create_thread_callback_t)(mcos_id_t tid, const mcos_char_t* name);

/* register callback function for messaging */
mcos_er_t
mcos_msgprof_register_message_callback(
    mcos_msgprof_message_callback_t callback);

/* unregister callback function for messaging */
void
mcos_msgprof_unregister_message_callback(void);

/* register callback function for creating thread */
mcos_er_t
mcos_msgprof_register_create_thread_callback(
    mcos_msgprof_create_thread_callback_t callback);

/* unregister callback function for creating thread */
void
mcos_msgprof_unregister_create_thread_callback(void);

/* workaround: eMCOS has no function for getting cluster information */
mcos_id_t mcos_msgprof_get_base_lcid(void);
mcos_id_t mcos_msgprof_get_base_tid(void);
mcos_id_t mcos_msgprof_get_migratable_base_tid(void);
mcos_id_t mcos_msgprof_get_end_tid(void);
mcos_bool_t mcos_msgprof_thread_is_affinity(mcos_id_t tid);

#endif /* MCOS_CFG_DS_MSGPROF_ENABLE */

#if !MCOS_AUTOSAR
mcos_uintptr_t mcos_debug_exception_get_esp(void);
#endif /* #if !MCOS_AUTOSAR */

#if MCOS_AUTOSAR
void mcos_ds_userhook_ar_target_exit(void);
#endif /* MCOS_AUTOSAR */
void mcos_ds_userhook_enter_isr(mcos_id_t iid);
void mcos_ds_userhook_enter_exc(void);
void mcos_ds_userhook_enter_idle(void);
void mcos_ds_userhook_leave_idle(mcos_id_t tid);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef MCOS_DS_H */
