/*
    Copyright (C) 2016 eSOL Co.,Ltd. Tokyo, Japan

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
[ mcos_mk_ds.h ] - eMCOS/MK debug supoort local header
****************************************************************************/
#ifndef MCOS_MK_DS_H
#define MCOS_MK_DS_H

#include "mcos_mk.h"

/* Null */
#define MCOS_TRACE_NULL ((void*)0)

/* Flags for trace. */
#define MCOS_TRACE_IS_READY             ((uint32_t)0x00000001U)
#define MCOS_TRACE_IS_LOCKED            ((uint32_t)0x00000002U)
#define MCOS_TRACE_IS_STARTING          ((uint32_t)0x00000004U)
#define MCOS_TRACE_IS_STARTED           ((uint32_t)0x00000008U)
#define MCOS_TRACE_IS_STOP_FULL         ((uint32_t)0x00000010U)

#define MCOS_TRACE_STOPCOND_MASK        ((uint32_t)0x00000010U)

/* Length of stacked contexts. */
#define MCOS_TRACE_CONTEXT_LENGTH   (16)

/* Boolean. */
typedef uint8_t trace_bool_t;
#define TRACE_FALSE                     (0)
#define TRACE_TRUE                      (1)

/* Event IDs. */
typedef uint8_t trace_eventid_t;
#define TRACE_EVENT_ID_ANY              (0)     /* 0    : Any                       */
#define TRACE_EVENT_ID_API_ENTRY        (1)     /* 1    : API entry                 */
#define TRACE_EVENT_ID_API_EXIT         (2)     /* 2    : API exit                  */
#define TRACE_EVENT_ID_INTERRUPT_ENTRY  (3)     /* 3    : Interrupt entry           */
#define TRACE_EVENT_ID_INTERRUPT_EXIT   (4)     /* 4    : Interrupt exit            */
#define TRACE_EVENT_ID_EXCEPTION_ENTRY  (5)     /* 5    : Exception entry           */
#define TRACE_EVENT_ID_EXCEPTION_EXIT   (6)     /* 6    : Exception exit            */
#define TRACE_EVENT_ID_THREAD_ENTRY     (7)     /* 7    : Thread entry              */
#define TRACE_EVENT_ID_THREAD_EXIT      (8)     /* 8    : Thread exit               */
#define TRACE_EVENT_ID_THREAD_SWITCH    (9)     /* 9    : Thread switch             */
#define TRACE_EVENT_ID_THREAD_MIGRATION (10)    /* 10   : Thread migration          */
#define TRACE_EVENT_ID_USER             (11)    /* 11   : User                      */

/* Context kinds. */
#define TRACE_CONTEXT_KIND_ANY          (0)    /* 0    : Any                       */
#define TRACE_CONTEXT_KIND_INTERRUPT    (1)    /* 1    : Interrupt                 */
#define TRACE_CONTEXT_KIND_EXCEPTION    (2)    /* 2    : Exception                 */
#define TRACE_CONTEXT_KIND_THREAD       (3)    /* 3    : Thread                    */

/* Information. */
typedef struct {
    uint16_t        upper;
    uint16_t        lower;
} word_half_t;

union trace_word
{
    uint32_t        word;
    word_half_t     half;
};
typedef union trace_word trace_word_t;

struct ds_trace_data
{
    /* event ID */
    uint8_t         eventID;
    /* part ID (always 0) */
    uint8_t         partID;
    /* reserved */
    uint16_t        rfu;
    /* event data 0 */
    trace_word_t    word0;
    /* event data 1 */
    trace_word_t    word1;
    /* event data 2 */
    trace_word_t    word2;
    /* event data 3 */
    trace_word_t    word3;
    /* event data 4 */
    unsigned long   word4;
    /* SP */
    unsigned long   sp;
    /* time of event occur [less than ms] */
    uint32_t        remaind_val;
    /* time of event occur [ms] */
    int64_t         miliTime;
#if !MCOS_AUTOSAR
    /* thread name 1 */
    mcos_char_t     name1[MCOS_THR_NAME_MAX];
    /* thread name 2 */
    mcos_char_t     name2[MCOS_THR_NAME_MAX];
#endif /* #if !MCOS_AUTOSAR */
};
typedef struct ds_trace_data ds_trace_data_t;

struct trace
{
    uint16_t            used_length;    /* used buffer size */
    uint16_t            total_length;   /* total buffer size */
    ds_trace_data_t*    read;           /* read pointer */
    ds_trace_data_t*    write;          /* write pointer */
    ds_trace_data_t*    origin;         /* origin of buffer */
    mcos_char_t         magic[8];       /* magic number */
};
typedef struct trace    trace_t;

/* Context. */
struct mcos_trace_context
{
    uint8_t             kind;           /* context kind (thread / interrupt) */
    uint16_t            task_id;        /* thread id */
};
typedef struct mcos_trace_context   mcos_trace_context_t;

/* Context stack. */
struct trace_stack
{
    uint16_t                size;           /* stacked context size */
    mcos_trace_context_t    contexts[MCOS_TRACE_CONTEXT_LENGTH];    /* stacked context */
};
typedef struct trace_stack trace_stack_t;

/* local debug support control block */
struct dscb_local
{
#if MCOS_CFG_DS_TRACE_ENABLE
    mcos_ds_trace_hook_t    trace_hook;             /* trace hook callback routines */
#if MCOS_CFG_DS_INTERNAL_TRACE_ENABLE
    trace_t                 trace;                  /* trace internal control data */
    trace_stack_t           nests;                  /* nest count of interrupt/exceptions */
#endif /* MCOS_CFG_DS_INTERNAL_TRACE_ENABLE */
#else /* MCOS_CFG_DS_TRACE_ENABLE */
    /*
     * Support for empty structs in C are an extension in GCC.
     * But, empty structs is violation. So, add dummy member.
     */
    volatile unsigned long  dummy;
#endif /* MCOS_CFG_DS_TRACE_ENABLE */
};

#if !MCOS_CFG_DS_TRACE_BUFFER_USE_CORELM
/* trace buffer management structure */
typedef struct
{
    void *addr;
    int count;
} trace_buffer_t;
#endif /* MCOS_CFG_DS_TRACE_BUFFER_USE_CORELM */

/* shared debug support control block */
struct dscb_shared
{
#if (MCOS_AUTOSAR || MCOS_CFG_DS_PRINT_ENABLE)
    mcos_spinlock_obj_t print_lock;              /* lock object for mcos_debug_printf */
    mcos_spinlock_obj_t vsnprint_lock;           /* lock object for vsnprintf */
#endif /* (MCOS_AUTOSAR || MCOS_CFG_DS_PRINT_ENABLE) */
    volatile uint64_t elapsed_start;                /* 2 point elapsed time */
    volatile uint64_t upper_time;                   /* current time upper bit */
#if MCOS_CFG_DS_LOADPERF_ENABLE
    volatile uint64_t workload_start;               /* work load start */
    volatile uint64_t workload_last[MP_CONTROL_CORE_COUNT];    /* work load last time */
    volatile uint64_t workload_halt[MP_CONTROL_CORE_COUNT];    /* work load total halt time */
    mcos_spinlock_obj_t time_lock[MP_CONTROL_CORE_COUNT];   /* lock object for workload time */
#endif /* MCOS_CFG_DS_LOADPERF_ENABLE */
#if MCOS_CFG_DS_TRACE_ENABLE
    volatile uint32_t trace_flags;                  /* state flag (init/stat/stop etc.) */
#if MCOS_CFG_DS_INTERNAL_TRACE_ENABLE
#if !MCOS_CFG_DS_TRACE_BUFFER_USE_CORELM
    /* trace buffers for all cores */
    volatile trace_buffer_t trace_buffers[MP_CONTROL_CORE_COUNT];
#endif /* MCOS_CFG_DS_TRACE_BUFFER_USE_CORELM */
#endif /* MCOS_CFG_DS_INTERNAL_TRACE_ENABLE */
#endif /* MCOS_CFG_DS_TRACE_ENABLE */
};

#if MCOS_AUTOSAR
#define OS_START_SEC_CODE
#include "Os_MemMap.h"
#endif /* MCOS_AUTOSAR */

void mcos_ds_hwl_init(const mkcb_t * mkcb, dscb_shared_t ** const ds_shared);

void mcos_ds_init(const mkcb_t * const mkcb, dscb_shared_t ** const ds_shared);

#if !MCOS_AUTOSAR
void mcos_ds_trace_hook_initialize(const mkcb_t *mkcb);
void mcos_ds_trace_hook_register(const mkcb_t *mkcb, mcos_ds_trace_hook_t *hook);
#else /* !MCOS_AUTOSAR */
void mcos_ds_trace_hook_register(const mkcb_t *mkcb, const mcos_ds_trace_hook_t *hook);
#endif /* !MCOS_AUTOSAR */

#if MCOS_CFG_DS_TRACE_ENABLE
void mcos_ds_trace_init(const mkcb_t *mkcb);

#if MCOS_CFG_DS_INTERNAL_TRACE_ENABLE
#if MCOS_CFG_DS_TRACE_BUFFER_USE_CORELM
void mcos_ds_trace_alloc(const mkcb_t *mkcb);
#endif /* MCOS_CFG_DS_TRACE_BUFFER_USE_CORELM */
#else /* MCOS_CFG_DS_INTERNAL_TRACE_ENABLE */
#define mcos_ds_trace_alloc(mkcb)
#endif /* MCOS_CFG_DS_INTERNAL_TRACE_ENABLE */
#else /* !MCOS_CFG_DS_TRACE_ENABLE */
#define mcos_ds_trace_init(mkcb)
#define mcos_ds_trace_alloc(mkcb)
#endif /* #if !MCOS_CFG_DS_TRACE_ENABLE */

#if MCOS_AUTOSAR
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"
#endif /* MCOS_AUTOSAR */

#if (MCOS_TEST_DS_PRFM == MCOS_TEST_DS_PRFM_MODE_DETAILED)
void mcos_hwl_ds_prfm_init_hook(void);
uint8_t mcos_hwl_ds_prfm_get_hookcnt(void);
uint32_t mcos_hwl_ds_prfm_read_hook(uint8_t idx);
#endif /* (MCOS_TEST_DS_PRFM == MCOS_TEST_DS_PRFM_MODE_DETAILED) */

#if MCOS_CFG_DS_LOADPERF_ENABLE
extern void mcos_ds_halt_with_timecount(mcos_id_t lcid);
#else /* MCOS_CFG_DS_LOADPERF_ENABLE */
#define mcos_ds_halt_with_timecount(x) mcos_hwl_halt()
#endif /* MCOS_CFG_DS_LOADPERF_ENABLE */

#if MCOS_CFG_DS_USED_MEMORY_ENABLE
extern void mcos_ds_print_used_memory(void);
#else /* MCOS_CFG_DS_USED_MEMORY_ENABLE */
#define mcos_ds_print_used_memory()
#endif /* MCOS_CFG_DS_USED_MEMORY_ENABLE */

#if MCOS_PT_API || MCOS_USE_PROCESS_MODEL
void mcos_debug_initialize_dbgmkcb(mcos_id_t lcid, const mkcb_t *mkcb);
#endif /* MCOS_PT_API || MCOS_USE_PROCESS_MODEL */

#endif /* #ifndef MCOS_MK_DS_H */
