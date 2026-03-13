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
[mcos_cls.h] - MCOS core local scheduler header
****************************************************************************/
#ifndef MCOS_CLS_H
#define MCOS_CLS_H

#include <mcos/system.cfg>
#include "mcos_cmn.h"
#if MCOS_AUTOSAR
#include "ar_user_cfg_def.h"
#endif /* #if MCOS_AUTOSAR */

/* scheduler internal flags */
#define CTX_NONE        (0x00U) /* normal */
#define CTX_INTH        (0x01U) /* during interrupt handler */
#define CTX_DISDSP      (0x02U) /* disable dispatch */

/* scheduler internal const values */
#define WUPCNT_MAX      (255U)   /* wakeup count max */
#define LDPRI_BASE      (256U)   /* load information piriority base value */

/* tcb attributes (user specified) */
#define TCB_ATTR_STDMSG         (0x01U)     /* std msg delete, else rr msg */
#define TCB_ATTR_INHERIT        (0x02U)     /* it is priority inheritance */
#if MCOS_AUTOSAR
#define TCB_ATTR_BASICTHREAD    (0x04U)     /* it is a basic thread */
#define TCB_ATTR_AUTOSARTHREAD  (0x08U)     /* it is a autosar thread */

/* tcb flags (system maintained) */
#define TCB_FLAGS_NEWACTIVE     (0x01U)     /* newly activated basic thread */
#endif

/* tcb attributes (system specified) */
#define TCB_ATTR_LOCKEDSTACK    (0x20U)     /* stack area is locked */
#define TCB_ATTR_USERSTACK      (0x40U)     /* stack area is allocated by user */
#define TCB_ATTR_AFFINITY       (0x80U)     /* core affinity thread */

/* session state */
#define SCB_STAT_DIR_SEND       0x01U       /* sender(=1) or receiver(=0) */

#define SCB_STAT_DISCON_TX      0x02U       /* disconnected at sender */
#define SCB_STAT_DISCON_RX      0x04U       /* disconnected at receiver */

#define SCB_STAT_BUF_FREE       0x08U       /* buffer is free (sender) */
#define SCB_STAT_BUF_TX         0x10U       /* buffer owner is sender (sender) */
#define SCB_STAT_WAIT_ALLOC     0x20U       /* waiting at allocation (sender) */
#define SCB_STAT_WAIT_SEND      0x40U       /* waiting at sending (sender) */

#define SCB_STAT_SENT           0x08U       /* message is sent (receiver) */
#define SCB_STAT_BUF_RX         0x10U       /* buffer owner is receiver (receiver) */
#define SCB_STAT_WAIT_RECV      0x20U       /* waiting at receiving (receiver) */

/* session control block bitmap index count */
#define SCBBM_CNT               MCOS_BITMAP_ARRAYSIZE(MCOS_CFG_SMSG_SESSION_COUNT_MAX)

/* DSM specific error code (for internal use only) */
#define DSM_ERR_BLOCKED         (-32767)

/* DMA transfer channel id */
#define CHID_ZEROCOPY       (0)             /* zerocopy flag */
#define CHID_INVALID        (-1)            /* invalid value flag */

/* tcb count per core */
#define TCB_CNT         MCOS_CFG_THR_MAX

#if !(BUILD_LIB || USE_OSLIB)
#define NUM_TCB_CNT                 TCB_CNT
#else /* #if !(BUILD_LIB || USE_OSLIB) */
#define NUM_TCB_CNT                 (mcos_mkconfig.thr_max)
#endif /* #if !(BUILD_LIB || USE_OSLIB) */

#if !MCOS_AUTOSAR

#define NUM_GLB_THR_PER_CORE_MAX    MCOS_CFG_GLB_THR_PER_CORE_MAX

#else /* #if !MCOS_AUTOSAR */
/* eMCOS AUTOSAR does not support HWCL.
 * The definition of MCOS_CFG_GLB_THR_PER_CORE_MAX is forcibly replaced by MCOS_CFG_THR_MAX.
 * Note, MCOS_CFG_GLB_THR_PER_CORE_MAX is used only in mcos_cls_init().
 */
#if !(BUILD_LIB || USE_OSLIB)
#define NUM_GLB_THR_PER_CORE_MAX    MCOS_CFG_THR_MAX
#else /* #if !(BUILD_LIB || USE_OSLIB) */
#define NUM_GLB_THR_PER_CORE_MAX    (mcos_mkconfig.thr_max)
#endif /* #if !(BUILD_LIB || USE_OSLIB) */

#endif /* #if !MCOS_AUTOSAR */

/* maximum number of thread control block */
#define TCB_MAX         (TCB_CNT * MP_CONTROL_CORE_COUNT)

/* check defined value */
#if !BUILD_LIB
#include "mcos_cls_buildchk.h"
#endif /* #if !BUILD_LIB */

/* tcb attributes and states */
typedef struct
{
    uint32_t state      :   2;  /* state */
#if !MCOS_AUTOSAR
    uint32_t suscnt     :   3;  /* suspended count */
    uint32_t flags      :   3;  /* (reserved) */
#else /* !MCOS_AUTOSAR */
    uint32_t flags      :   6;  /* (reserved) */
#endif /* !MCOS_AUTOSAR */
    uint32_t attr       :   8;  /* attribute */
    uint32_t wupcnt     :   8;  /* wakeup count (invalid field if it is dormant) */
    uint32_t prinest    :   8;  /* priority inherit nest count */
} tcb_attr_state_t;

#if MCOS_USE_PROCESS_MODEL
/* thread space information */
typedef struct {
    void        *ssp;       /* saved stack pointer */
    uint32_t    lsid;       /* logical space ID (Process ID) */
    void        *uatb;      /* user space page table */
} space_t;

/* stack in user local space */
typedef struct {
    mcos_uintptr_t   *stkaddr;   /* user local stack address */
    uint32_t    stksz;      /* user local stack size (word) */
} ulstack_t;

typedef struct {
    space_t     space;      /* thread space information */
    ulstack_t   ulstack;    /* stack in user local space */
    uint32_t    pid;        /* process ID (maybe different from lsid) */
    uint16_t    funcno;     /* calling function number via SVC */
} process_t;
#endif

/* session transfer control block */
typedef struct scb_st
{
    mcos_id_t dest_ssid;    /* destination session id */
    mcos_id_t dest_tid;     /* destination thread id */
    mcos_id_t chid;         /* current channel id */
    mcos_id_t dest_chid;    /* destination channel id */
    uint8_t stat;           /* current state */
    uint8_t sub_ssid;       /* sub session id */
    int8_t send_cnt;        /* send count (++:send, --:recv) */
    uint32_t bufsize;       /* buffer size (bytes) */
    const void *bufaddr;    /* buffer address */
} scb_t;

/*
 * thread control block (migratable members)
 */
typedef struct
{
    tcb_attr_state_t attr_state;    /* attributes and states */
    uint8_t bpri;           /* base priority */
    uint8_t cpri;           /* current priority */
#if MCOS_AUTOSAR
    uint8_t actcnt;         /* current basic thread activation count */
    uint8_t maxact;         /* basic thread max activation count */
#endif
#if (!MCOS_AUTOSAR) && (MCOS_CFG_SMSG_SESSION_COUNT_MAX > 0U)
    uint8_t sub_ssid_base;  /* base number of sub ssid (sender) */
#endif /* #if (!MCOS_AUTOSAR) && (MCOS_CFG_SMSG_SESSION_COUNT_MAX > 0U) */
    void (*entry)(const uint32_t stacd, void (*exinf)(void)); /* entry address */
    mcos_uintptr_t *stkaddr;     /* stack address */
    uint32_t stksz;         /* stack size (word) */
#if MCOS_USE_PROCESS_MODEL
    process_t process;
#endif
#if (!MCOS_AUTOSAR) && (MCOS_CFG_SMSG_SESSION_COUNT_MAX > 0U)
    scb_t scb[MCOS_CFG_SMSG_SESSION_COUNT_MAX];
                                            /* memory area for scb */
    mcos_bitmap_t scbbm[SCBBM_CNT];         /* scb bitmap */
#endif /* #if (!MCOS_AUTOSAR) && (MCOS_CFG_SMSG_SESSION_COUNT_MAX > 0U) */
    void *rep;                              /* waiting message reply buffer, 0 means no wait */
                                            /* (invalid field if it is dormant) */
    mcos_uintptr_t exinf;        /* extended info on creation */
} migratable_tcb_t;

/* thread control block */
typedef struct tcb_st tcb_t;

struct tcb_st
{
    mcos_id_t tid;          /* thread id */
    mcos_id_t tid_af;       /* affinity thread's thread id */
    void *stack;            /* internal allocated local memory stack, 0 means it is not allocated */
#if !MCOS_AUTOSAR
    msg_t *sent;                            /* for mcos_message_send() */
                                            /* sent messages before mcos_message_receive() is called */
                                            /* (invalid field if it is dormant) */
    msg_t *req;                             /* for mcos_rrmessage_send() */
                                            /* sent request messages before mcos_rrmessage_receive() is called */
                                            /* (invalid field if it is dormant) */
    msg_t *div;                             /* for mcos_message_send() */
                                            /* sent divided messages before mcos_message_receive() is called */
                                            /* (invalid field if it is dormant) */
#if MCOS_CFG_SMSG_SESSION_COUNT_MAX > 0U
    msg_t *sent_sopen;                      /* for mcos_smessage_send_open() */
                                            /* sent session open messages before mcos_smessage_receive_open() is called */
                                            /* (invalid field if it is dormant) */
#endif /* #if MCOS_CFG_SMSG_SESSION_COUNT_MAX > 0U */
    msg_t *fmsg;                            /* for mcos_fmessage_send() */
                                            /* sent messages before mcos_fmessage_receive() is called */
                                            /* (invalid field if it is dormant) */
    void *errno_addr;       /* ptr to POSIX errno */
#endif
    tcb_t *next;                            /* next thread of queue */
    migratable_tcb_t migratable;  /* members which are copied on migration. */
    mcos_uintptr_t sp;           /* suspended sp (invalid field if it is dormant) */
};

/* migration request */
typedef msg_t * migreq_t;

#if MCOS_AUTOSAR
#include "Os_internal.h"
#include "ar_mcos.h"
#endif /* MCOS_AUTOSAR */

/* activate request */
typedef struct actcb_st actcb_t;

struct actcb_st
{
    tcb_t *tcb;             /* tcb */
    actcb_t *next;          /* next */
};

#if MCOS_AUTOSAR
/* Autosar ISR Control Block */
typedef struct ar_isrcb_st ar_isrcb_t;

struct ar_intcb_st
{
    ar_isrcb_t *p_running_isr;
    uint8_t nestcnt_susallints;
    uint8_t nestcnt_susosints;
    uint8_t nestcnt_susallints_spinlock;
    uint8_t nestcnt_susosints_spinlock;
    int32_t saved_intbpri;
    int32_t saved_intbpri_by_sus_os;
    int32_t saved_lockall_by_dis_all;
    int32_t saved_lockall_by_sus_all;
    uint8_t nested_lock_os_int_cnt;
};

#define AR_NESTED_LOCK_OS_INT_CNT_1 1UL
#endif /* #if MCOS_AUTOSAR */


/* core local scheduler control block */
struct clscb_st
{
    tcb_t *running;             /* running threads */
    tcb_t *ready;               /* running and ready threads */
    tcb_t *wait;                /* wait threads */
    tcb_t *dormant;             /* dormant threads */
    tcb_t *nonexist;            /* free tcbs */
#if !MCOS_AUTOSAR
    tcb_t *suspended;           /* suspended threads */
#endif /* !MCOS_AUTOSAR */
    mcos_uintptr_t sp;               /* micro-kernel suspended sp */
#if MCOS_AUTOSAR
    mcos_id_t mintid;           /* minimum core affinity thread id */
#endif /* #if MCOS_AUTOSAR */
#if MCOS_USE_PROCESS_MODEL
    mcos_uintptr_t esp;              /* last exception sp */
#endif /* MCOS_USE_PROCESS_MODEL */
    volatile mcos_id_t iid;     /* current iid (invalid field if it is not ISR) */
    volatile uint8_t ctx;       /* current context type */
#if MCOS_AUTOSAR
    mcos_bool_t terminated_running; /* indicate whether running task is terminated or not. (USED ASSEMBLER!) */
    actcb_t     *actreq;        /* activate requests */
    actcb_t     **actreq_end;   /* end of activate requests */
    actcb_t     *free_actreq;   /* unused activate requests */
    ar_oscb_t   aroscb;         /* AUTOSAR service control block */
    actcb_t     *actcb;         /* address for actcb memory area */
    ar_intcb_t  arintcb;        /* AUTOSAR interrupt control block */
    tcb_t       *tcb;           /* address for tcb memory area */
    void        *exc_info;     /* information for AUTOSAR ProtectionHook */
    tcb_t       *chain_restart; /* chain restart threads */
#else /* #if MCOS_AUTOSAR */
    tcb_t *lts;                 /* leaf thread scheduler */
    tcb_t *tpre;                /* thread-pool request execution thread */
    tcb_t *reserved;            /* reserved tcb for migration */
    msg_t *clsreq;              /* pending request to cls */
    msg_t *fmsg_isr;            /* pending fmsg to isr */
    migreq_t mig;               /* pending migration request */
    tcb_t tcb[TCB_CNT];         /* memory area for tcb */
#endif /* #if MCOS_AUTOSAR */
};

/* Actual thread creation attributes */
typedef struct
{
    mcos_id_t       lcid;       /* logical core ID */
    uint8_t         priority;   /* thread priority */
    uint8_t         flags;      /* thread flags */
#if MCOS_AUTOSAR
 /* Highest 8-bit are used for max activation count */
#define THR_ATTR_MAXACT_SHIFT         24U
#define THR_ATTR_STKSIZE_MASK   0xffffffU
#endif /* MCOS_AUTOSAR */
    uint32_t        stacksize;  /* thread stack size (in bytes) */
    void            *stackaddr; /* thread stack area address */
    int8_t          name[MCOS_THR_NAME_MAX];  /* optional thread name */
    /* The followings have an effect
     * only when using the process model */
    uint32_t        lsid;       /* logical space id */
    uint32_t        boundary;   /* (boundary for uatb pointer) */
    void            *uatb;      /* user space page table */
} thread_attr_t;

typedef void (*mcos_isr_entry_t)(mcos_id_t iid, mcos_uintptr_t param);

#if MCOS_AUTOSAR
typedef void (*osap_startup_hook_func_t)    (void);
typedef void (*osap_shutdown_hook_func_t)   (StatusType Fatalerror);
typedef void (*osap_error_hook_func_t)      (StatusType Error);

struct ar_osap_config_st {
    osap_startup_hook_func_t    startup_hook;
    osap_shutdown_hook_func_t   shutdown_hook;
    osap_error_hook_func_t      error_hook;
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
    ar_tcb_t        *p_restart_tcb;       /* Task to activate at OSAP restart */
    uint32          osap_bitmask;         /* Bitmask of this OSAP if protected */
    boolean         osap_trusted;         /* True if this OSAP is a trusted one */
    boolean         osap_protected;       /* True if this OSAP is a memory protected one */
    boolean         osap_terminatable;    /* True if this OSAP is terminatable */
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) || (AR_OS_USE_MULTICORE == STD_ON)
    ar_osapcb_t     *p_osapcb;            /* pointer to ar_osapcb_t */
#endif /* #if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) || (AR_OS_USE_MULTICORE == STD_ON) */
    ApplicationType osap_id;              /* My OsApplication ID */
    mcos_id_t lcid;
};

struct ar_task_config_st {
    ar_funcp_t              entry;
    uint32                  stack_size;
    uint8                   base_tpri;      /* initial thread priority */
    uint8                   exec_tpri;      /* execution thread priority */
    uint8                   max_act_count;
    uint32                  auto_act_mode;
    void                    *stack_ptr;
    const ar_osap_config_t  *p_osapconfig;
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
    const uint32            *osap_allowedmap;   /* Access allowed OSAP bitmap */
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
};

struct ar_resourcecb_st {
    const ar_resource_config_t      *p_config;
    ar_resourcecb_t                 *p_prevcb;
    sint32                          prev_pri;
    boolean                         is_locked;
};

#include "mcos_spinlock_obj.h"

struct ar_spinlock_config_st {
    const ar_spinlock_config_t *p_nextcb;
    SpinlockIdType  spinlock_id;    /* My Spinlock ID */
    SpinlockIdType  nestcb_index;   /* Index of the nested spinlock controll block */
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
    const uint32            *osap_allowedmap;   /* Access allowed OSAP bitmap */
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
    uint8                   lock_method;
};

struct ar_spinlockcb_st {
    const ar_spinlock_config_t      *p_config;  /* +0 */
    mcos_id_t                       lcid;       /* *4 */
    void                            *p_ownercb; /* +8 */
    ar_spinlockcb_t                 *p_prevcb;  /* +C */

#if defined(AR_SPINLOCK_PADDING1_N)
#if (AR_SPINLOCK_PADDING1_N > 0U)
    volatile uint32                 padding1[AR_SPINLOCK_PADDING1_N];
#endif /* #if defined(AR_SPINLOCK_PADDING1_N) */
#endif /* #if (AR_SPINLOCK_PADDING1_N > 0U) */
    mcos_spinlock_obj_t    mcos_spinlock;
    /* hw dependency spinlock object padding */
#if defined(AR_SPINLOCK_PADDING2_N)
#if (AR_SPINLOCK_PADDING2_N > 0U)
    volatile uint32                 padding2[AR_SPINLOCK_PADDING2_N];
#endif /* #if (AR_SPINLOCK_PADDING2_N > 0U) */
#endif /* #if defined(AR_SPINLOCK_PADDING2_N) */
};

struct ar_tcb_st {
    const ar_task_config_t  *p_config;
    mcos_id_t               thread_id;      /* thread id */
    sint32                  current_xpri;   /* thread or interrupt priority */
    EventMaskType           current_event;
    EventMaskType           wait_event;
    ar_resourcecb_t         *p_last_resourcecb;
    tcb_t                   *p_mcos_tcb;
    const ar_osap_config_t  *p_save_osapconfig; /* save current application config when dispathing */
    ar_context_spinlockcbs_t       context_spinlockcbs;
};

#include "mcos/xmcos_ar.h"
#endif /* #if MCOS_AUTOSAR */

/* core local scheduler interface functions */
#if (AR_OS_USE_MULTICORE == STD_ON)
mcos_id_t mcos_cls_get_currenttid(void);
#endif  /* (AR_OS_USE_MULTICORE == STD_ON) */
#if !MCOS_AUTOSAR
void mcos_cls_accept_message(const mkcb_t *mkcb, void *msgdata, uint32_t msgsz, void *rep);
void mcos_cls_call(void *req, uint32_t reqsz, void *rep); /* api call */
void mcos_cls_call_self(void *req, uint32_t reqsz, void *rep); /* api call */
void mcos_cls_deliver(void *req, int32_t reqsz);
msg_t *mcos_cls_get_server_request(const mkcb_t *mkcb); /* for server */
mcos_uintptr_t mcos_cls_get_epc(mcos_uintptr_t sp);
mcos_bool_t mcos_cls_route_to_clmm(void *msgdata);

void * mcos_cls_send_message(const mkcb_t * mkcb, void *msgdata, uint32_t msgsz, void *rep);
void mcos_cls_consume_pending_messages(const mkcb_t * mkcb);

#if MCOS_CFG_SMSG_SESSION_COUNT_MAX > 0U
mcos_er_t mcos_cls_sms_open(mcos_id_t tid, const void *buffer, uint32_t size, mcos_id_t *p_ssid, mcos_id_t *p_chid, uint8_t *p_sub_ssid);
mcos_er_t mcos_cls_sms_close(mcos_id_t ssid, mcos_id_t *p_dest_tid, mcos_id_t *p_dest_ssid);
void mcos_cls_sms_open_cancel(mcos_id_t ssid, mcos_id_t chid);
mcos_er_t mcos_cls_sms_send(mcos_id_t ssid, mcos_id_t *p_dest_tid, mcos_id_t *p_dest_ssid);
mcos_er_t mcos_cls_sms_allocate(mcos_id_t ssid, mcos_id_t *p_dest_ssid);
mcos_er_t mcos_cls_smr_open(mcos_id_t *p_ssid);
void mcos_cls_smr_open_finalize(msg_smropen_r_t *rep);
mcos_er_t mcos_cls_smr_close(mcos_id_t ssid, mcos_id_t *p_dest_tid, mcos_id_t *p_dest_ssid, const void **p_recvalloc);
mcos_er_t mcos_cls_smr_receive(mcos_id_t ssid, mcos_id_t *p_dest_tid, mcos_id_t *p_dest_ssid, uint8_t *p_sub_ssid);
void mcos_cls_smr_receive_finalize(mcos_id_t ssid);
mcos_er_t mcos_cls_smr_free(mcos_id_t ssid, mcos_id_t *p_dest_tid, mcos_id_t *p_dest_ssid);
mcos_er_t mcos_cls_sm_get_info(mcos_id_t ssid, mcos_smsg_info_t *info);
#endif /* #if MCOS_CFG_SMSG_SESSION_COUNT_MAX > 0U */

#if MCOS_TK_API || MCOS_PT_API
void mcos_cls_pri_inh_up(const mkcb_t *mkcb, tcb_t *tcb, uint8_t pri);
void mcos_cls_pri_inh_down(const mkcb_t *mkcb, tcb_t *tcb);
void mcos_cls_pri_change(const mkcb_t *mkcb, tcb_t *tcb, uint8_t pri);
#endif
#endif /* #if !MCOS_AUTOSAR */

#if MCOS_USE_PROCESS_MODEL
mcos_er_t mcos_cls_get_current_space(space_t *space);
mcos_er_t mcos_cls_get_thread_space(mcos_id_t tid, space_t *space);
mcos_er_t mcos_cls_set_thread_space(mcos_id_t tid, const space_t *space);
#endif  /* #if MCOS_USE_PROCESS_MODEL */

#if !MCOS_AUTOSAR
void mcos_cls_send_to_clmm(const mkcb_t *mkcb, uint32_t *msgdata, uint32_t msgsz);
#endif /* #if !MCOS_AUTOSAR */

/* mcos_message_send()/mcos_message_receive() flags - message mask (internal) */
#define MCOS_MSG_MASK_SYS_TK             (0x00000100U)
#define MCOS_MSG_MASK_SYS_PT             (0x00000200U)
#define MCOS_MSG_MASK_SYS_TIMER          (0x00000400U)
#define MCOS_MSG_MASK_SYS_HEAP           (0x00000800U)
#define MCOS_MSG_MASK_SYS_RRMSG          (0x00001000U)
#define MCOS_MSG_MASK_SYS_SRVM           (0x00002000U)


#if MCOS_AUTOSAR
#define AR_EVENT_MASK_NONE      ((EventMaskType) 0)
#endif /* #if MCOS_AUTOSAR */

#if !MCOS_AUTOSAR
mcos_erid_t mcos_cls_thread_create_with_tid(const mcos_thr_attr_t *attr, void (*entry)(uint32_t stacd, mcos_uintptr_t exinf), mcos_uintptr_t exinf, mcos_id_t tid);

void mcos_intm_call(const mkcb_t *mkcb, mcos_id_t iid);

mcos_er_t mcos_thread_start_internal(const mcos_id_t tid, const uint32_t start_code);
mcos_id_t mcos_thread_getid_internal(void);

mcos_er_t mcos_thread_suspend_internal(mcos_id_t tid, mcos_bool_t async);
mcos_er_t mcos_thread_resume_internal(mcos_id_t tid, mcos_bool_t async, mcos_bool_t forced);
#endif /* !MCOS_AUTOSAR */

#if MCOS_AUTOSAR
mcos_er_t mcos_do_start(clscb_t * const clscb, const mcos_id_t tid, const mcos_uintptr_t param);
void mcos_do_wakeup(clscb_t * const clscb, const mcos_id_t tid);
void mcos_dispatch_context(clscb_t * const clscb, tcb_t * const running);
void mcos_dispatch_context_noreturn(const clscb_t * const clscb, const tcb_t * const running);
void mcos_do_sleep(clscb_t * const clscb, msg_repself_t * const rep);
tcb_t * mcos_do_create(const mkcb_t * const mkcb, const msg_tcre_t * const req, msg_rep_t * const rep);
void mcos_do_exit(clscb_t * const clscb);
#if (AR_ENABLE_CHAIN_TASK != 0U)
mcos_er_t mcos_do_chain(const mkcb_t * const mkcb, const mcos_id_t tid, const mcos_id_t caller, const mcos_uintptr_t param);
#if (AR_OS_USE_MULTICORE == STD_ON)
void mcos_do_chain_exit(clscb_t * const clscb, const mcos_id_t tid);
#endif  /* (AR_OS_USE_MULTICORE == STD_ON) */
#endif  /* #if (AR_ENABLE_CHAIN_TASK != 0U) */
void mcos_add_pri_changed_tcb_to_ready(clscb_t * const clscb, tcb_t * const tcb);
#if !MCOS_AUTOSAR
void mcos_intm_set_idp(const mkcb_t *mkcb, mcos_id_t iid, mcos_isr_entry_t entry, mcos_uintptr_t param);
#endif /* !MCOS_AUTOSAR */

void ar_oscb_init(const mkcb_t * const mkcb, ar_oscb_t * const aroscb);
void ar_intcb_init(ar_intcb_t * const ar_intcb);
void ar_osarchcb_init(const mkcb_t * const mkcb, ar_oscb_t * const aroscb);

extern void ar_posttaskhook_call(void);
extern void ar_pretaskhook_call_internal(const mcos_uintptr_t not_use1, const mcos_uintptr_t not_use2);

#if ( (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) || (AR_OS_USE_STACKMONITORING == STD_ON) )
extern void ar_protectionhook_call(const StatusType status);
#endif /* #if (AR_OS_USE_STACKMONITORING == STD_ON) */

#endif /* #if MCOS_AUTOSAR */

#if !MCOS_AUTOSAR
mcos_er_t mcos_message_send_internal(const mcos_id_t tid, const void * const data, const uint32_t size, const uint32_t flags);
mcos_er_t mcos_message_receive_internal(void * const data, uint32_t * const size, const uint32_t flags);
#if MCOS_HWCL && MCOS_CFG_GLB_CLMM_ENABLE
void mcos_cls_delete_to_ts(mcos_id_t tid, uint8_t tpri);
#endif /* #if MCOS_HWCL && MCOS_CFG_GLB_CLMM_ENABLE */
#endif /* !MCOS_AUTOSAR */

#if MCOS_AUTOSAR
MCOS_INLINE tcb_t * mcos_get_running(const clscb_t * const clscb);
#endif /* #if MCOS_AUTOSAR */

#if !MCOS_AUTOSAR
MCOS_INLINE mcos_bool_t mcos_util_is_affinity(const mcos_id_t tid);
#endif /* !MCOS_AUTOSAR */
MCOS_INLINE mcos_id_t mcos_util_get_afinity_lcid(const mcos_id_t tid);
#if !MCOS_AUTOSAR
MCOS_INLINE mcos_id_t mcos_util_get_lcid(const mcos_id_t tid);
MCOS_INLINE uint32_t mcos_util_get_type(const void * const msgdata);
#endif /* #if MCOS_AUTOSAR */
MCOS_INLINE void mcos_util_set_type(void * const msgdata, const uint32_t type);
#if MCOS_HWCL
MCOS_INLINE uint32_t mcos_util_get_clmm(const void * const msgdata);
MCOS_INLINE void mcos_util_set_clmm( void * const msgdata, const uint32_t clmm_type);
#endif /* #if MCOS_HWCL */
#if MCOS_PT_API
MCOS_INLINE tcb_t *mcos_cls_get_running(const mkcb_t * const mkcb);
#endif /* #if MCOS_PT_API */
#if MCOS_TK_API || MCOS_PT_API
MCOS_INLINE tcb_t *mcos_cls_get_running_none_or_disdsp(const mkcb_t * const mkcb);
#endif /* #if MCOS_TK_API || MCOS_PT_API */
#if MCOS_PT_API
MCOS_INLINE uint8_t mcos_cls_get_base_priority(const tcb_t * const tcb);
#endif /* #if MCOS_PT_API */
#if MCOS_TK_API || MCOS_PT_API
MCOS_INLINE tcb_t *mcos_cls_search_thread_in_waiting(const mkcb_t * const mkcb, const mcos_id_t tid);
MCOS_INLINE tcb_t *mcos_cls_search_thread_in_ready(const mkcb_t * const mkcb, const mcos_id_t tid);
#endif /* #if MCOS_TK_API || MCOS_PT_API */
#if MCOS_USE_PROCESS_MODEL
MCOS_INLINE tcb_t *mcos_cls_search_thread_in_dormant(const mkcb_t * const mkcb, const mcos_id_t tid);
#endif /* MCOS_USE_PROCESS_MODEL */
#if MCOS_TK_API || MCOS_PT_API
MCOS_INLINE void *mcos_cls_get_thread_entry(tcb_t * const tcb);
#endif /* #if MCOS_TK_API || MCOS_PT_API */
#if MCOS_PT_API
MCOS_INLINE tcb_t *mcos_cls_get_next_tcb(tcb_t * const tcb);
#endif /* #if MCOS_PT_API */
#if MCOS_TK_API
MCOS_INLINE mcos_bool_t mcos_cls_is_running(const mkcb_t * const mkcb, const tcb_t * const tcb);
#endif /* #if MCOS_TK_API */

#if MCOS_AUTOSAR
MCOS_INLINE ar_intcb_t * mcos_cls_get_arintcb(clscb_t * const clscb);
static AR_FORCE_INLINE ar_tcb_t* ar_get_ar_tcb(const tcb_t * const p_mtcb);
static AR_FORCE_INLINE void ar_task_pre_exit(clscb_t * const clscb, const tcb_t * const p_mtcb);
static AR_FORCE_INLINE void ar_task_post_start_mksp(clscb_t * const clscb, tcb_t * const tcb);
#endif /* #if MCOS_AUTOSAR */

#if MCOS_AUTOSAR
/* get running thread tcb (for AUTOSAR) */
MCOS_INLINE tcb_t * mcos_get_running(
    const clscb_t * const clscb)
{
    return clscb->running;
}
#endif /* #if MCOS_AUTOSAR */

#if !MCOS_AUTOSAR
/* is affinity ? */
MCOS_INLINE mcos_bool_t mcos_util_is_affinity(
    const mcos_id_t tid)
{
   return (mcos_bool_t)((((uint32_t)tid - (uint32_t)1) % (uint32_t)MCOS_TID_HWCL)
        < (uint32_t)MCOS_TCB_HWCL);
}
#endif /* !MCOS_AUTOSAR */

/*
 * get core id from afinity thread id
 * Input     :   tid     afinity thread ID
 * Output    :   none
 * Return    :   core ID
 * Note  :   none
 */
MCOS_INLINE mcos_id_t mcos_util_get_afinity_lcid(
    const mcos_id_t tid)
{
    uint32_t coreid = (((uint32_t)tid - (uint32_t)HWCL_BASE_TID)
        / (uint32_t)MCOS_CFG_GLB_THR_PER_CORE_MAX) + (uint32_t)MCOS_BASE_LCID;
    return (mcos_id_t)coreid;
}

#if !MCOS_AUTOSAR
/*
 * get core id from thread id
 * Input     :   tid     thread ID
 * Output    :   none
 * Return    :   core ID
 * Note  :   none
 */
MCOS_INLINE mcos_id_t mcos_util_get_lcid(
    const mcos_id_t tid)
{
    const mcos_bool_t is_affinity = mcos_util_is_affinity(tid);
    return (mcos_id_t)(is_affinity ? (int32_t)mcos_util_get_afinity_lcid(tid) : (int32_t)(LCID_UNCERTAIN));
}

/*
 *  get message type
 * Input     :   msgdata     message data
 * Output    :   none
 * Return    :   message type
 * Note  :   none
 */
MCOS_INLINE uint32_t mcos_util_get_type(
    const void * const msgdata)
{
    return (uint32_t)((msg_id_t *)msgdata)->id.type;
}
#endif    /* #if !MCOS_AUTOSAR   */

/*
 *  set message type
 * Input     :   msgdata     message data
 *           :   message type
 * Output    :   none
 * Return    :   none
 * Note  :   none
 */
MCOS_INLINE void mcos_util_set_type(
    void * const msgdata,
    const uint32_t type)
{
    ((msg_id_t *)msgdata)->idall = MSG_ID_DEFAULT;
    ((msg_id_t *)msgdata)->id.type = (msg_generic_id_t)type;
}

#if MCOS_HWCL
MCOS_INLINE uint32_t mcos_util_get_clmm(
    const void * const msgdata)
{
    return (uint32_t)((const msg_id_t *)msgdata)->id.clmm;
}

MCOS_INLINE void mcos_util_set_clmm(
    void * const msgdata,
    const uint32_t clmm_type)
{
    ((msg_id_t *)msgdata)->id.clmm = clmm_type;
}
#endif /* #if MCOS_HWCL */

#if MCOS_PT_API
/*
 * get running
 */
MCOS_INLINE tcb_t *mcos_cls_get_running(
    const mkcb_t * const mkcb)
{
    clscb_t * const clscb = mcos_mkcc_get_clscb(mkcb);

    return clscb->ready;
}

/*
 * get running (including previous running e.g. )
 */
MCOS_INLINE tcb_t *mcos_cls_get_running_previous(
    const mkcb_t * const mkcb)
{
    clscb_t * const clscb = mcos_mkcc_get_clscb(mkcb);

    return clscb->running;
}
#endif /* #if MCOS_PT_API */

#if MCOS_TK_API || MCOS_PT_API
/*
 * get running with CTX_NONE or CTX_DISDSP
 */
MCOS_INLINE tcb_t *mcos_cls_get_running_none_or_disdsp(
    const mkcb_t * const mkcb)
{
    clscb_t * const clscb = mcos_mkcc_get_clscb(mkcb);

    return ( ((uint32_t)clscb->ctx == (uint32_t)CTX_NONE)
            || ((uint32_t)clscb->ctx == (uint32_t)CTX_DISDSP))
                ? clscb->ready : NULL;
}
#endif /* #if MCOS_TK_API || MCOS_PT_API */

#if MCOS_PT_API
/*
 * get current priority
 */
MCOS_INLINE uint8_t mcos_cls_get_base_priority(
    const tcb_t * const tcb)
{
    return tcb->migratable.bpri;
}
#endif /* #if MCOS_PT_API */

#if MCOS_TK_API || MCOS_PT_API

/*
 * get thread control block in waiting queue
 */
MCOS_INLINE tcb_t *mcos_cls_search_thread_in_waiting(
    const mkcb_t * const mkcb,
    const mcos_id_t tid)
{
    clscb_t * const clscb = mcos_mkcc_get_clscb(mkcb);
    tcb_t *stcb = NULL;
    tcb_t *tcb;
    mcos_bool_t loop;

    loop = mcos_true;
    tcb = clscb->wait;

    while ((uint32_t)loop != (uint32_t)mcos_false)
    {
        if (tcb == NULL)
        {
            loop = (mcos_bool_t)mcos_false;
        }
        else
        {
            if ((int32_t)tcb->tid == (int32_t)tid)
            {
                stcb = tcb;
                loop = (mcos_bool_t)mcos_false;
            }
            else
            {
                tcb = tcb->next;
            }
        }
    }

    return stcb;
}

/*
 * get thread control block in ready queue
 */
MCOS_INLINE tcb_t *mcos_cls_search_thread_in_ready(
    const mkcb_t * const mkcb,
    const mcos_id_t tid)
{
    clscb_t * const clscb = mcos_mkcc_get_clscb(mkcb);
    tcb_t *stcb = NULL;
    tcb_t *tcb;
    mcos_bool_t loop;

    loop = mcos_true;
    tcb = clscb->ready;

    while ((uint32_t)loop != (uint32_t)mcos_false)
    {
        if (tcb == NULL)
        {
            loop = (mcos_bool_t)mcos_false;
        }
        else
        {
            if ((int32_t)tcb->tid == (int32_t)tid)
            {
                stcb = tcb;
                loop = (mcos_bool_t)mcos_false;
            }
            else
            {
                tcb = tcb->next;
            }
        }
    }

    return stcb;
}
#endif /* #if MCOS_TK_API || MCOS_PT_API */

#if MCOS_USE_PROCESS_MODEL
/*
 * get thread control block in dormant queue
 */
MCOS_INLINE tcb_t *mcos_cls_search_thread_in_dormant(
    const mkcb_t * const mkcb,
    const mcos_id_t tid)
{
    clscb_t const * const clscb = mcos_mkcc_get_clscb(mkcb);
    tcb_t *stcb = NULL;
    tcb_t *tcb;
    mcos_bool_t loop;

    loop = (mcos_bool_t)mcos_true;
    tcb = clscb->dormant;

    while ((uint32_t)loop != (uint32_t)mcos_false)
    {
        if (tcb == NULL)
        {
            loop = (mcos_bool_t)mcos_false;
        }
        else
        {
            if ((int32_t)tcb->tid == (int32_t)tid)
            {
                stcb = tcb;
                loop = (mcos_bool_t)mcos_false;
            }
            else
            {
                tcb = tcb->next;
            }
        }
    }

    return stcb;
}
#endif /* MCOS_USE_PROCESS_MODEL */

#if !MCOS_AUTOSAR
/*
 * get thread control block in suspended queue
 */
MCOS_INLINE tcb_t* mcos_cls_search_thread_in_suspended(
    const mkcb_t *mkcb,
    mcos_id_t tid)
{
    clscb_t *clscb = mcos_mkcc_get_clscb(mkcb);
    tcb_t* stcb = 0;
    tcb_t* tcb;
    _Bool loop;

    loop = true;
    tcb = clscb->suspended;

    while (loop != false)
    {
        if (tcb == 0)
        {
            loop = false;
        }
        else
        {
            if (tcb->tid == tid)
            {
                stcb = tcb;
                loop = false;
            }
            else
            {
                tcb = tcb->next;
            }
        }
    }

    return stcb;
}
#endif /* !MCOS_AUTOSAR */

#if MCOS_TK_API || MCOS_PT_API
/*
 * get thread entry
 */
MCOS_INLINE void *mcos_cls_get_thread_entry(
    tcb_t * const tcb)
{
    return tcb->migratable.entry;
}
#endif /* #if MCOS_TK_API || MCOS_PT_API */

#if MCOS_PT_API
/*
 * Get next tcb
 */
MCOS_INLINE tcb_t *mcos_cls_get_next_tcb(
    tcb_t * const tcb)
{
    return tcb->next;
}
#endif /* #if MCOS_PT_API */

#if MCOS_TK_API
/*
 * same entry ?
 */
MCOS_INLINE mcos_bool_t mcos_cls_is_running(
    const mkcb_t * const mkcb,
    const tcb_t * const tcb)
{
    clscb_t * const clscb = mcos_mkcc_get_clscb(mkcb);

    return (tcb == clscb->running) ? mcos_true : mcos_false;
}
#endif /* #if MCOS_TK_API */

#if !MCOS_AUTOSAR
/*
 * rotate ready queue
 */
void mcos_cls_rotate_readyqueue (
    uint8_t pri,
    mcos_bool_t isHighest);

mcos_er_t mcos_interrupt_define_internal(mcos_id_t iid, const mcos_int_def_t *idp);
#endif    /* #if !MCOS_AUTOSAR   */

#if MCOS_CFG_PARAM_CHECK
mcos_er_t mcos_interrupt_disable_internal(mcos_id_t iid);
mcos_er_t mcos_interrupt_enable_internal(mcos_id_t iid);
#else /* #if MCOS_CFG_PARAM_CHECK */
MCOS_INLINE mcos_er_t
mcos_interrupt_disable_internal(mcos_id_t iid)
{
    bios_pic_disableInt((bios_int_t)iid);
    return MCOS_EOK;
}

MCOS_INLINE mcos_er_t
mcos_interrupt_enable_internal(mcos_id_t iid)
{
    bios_pic_enableInt((bios_int_t)iid);
    return MCOS_EOK;
}
#endif /* #if MCOS_CFG_PARAM_CHECK */

#if MCOS_AUTOSAR
/* Get pointer to interrupt manager control block */
MCOS_INLINE ar_intcb_t * mcos_cls_get_arintcb (
    clscb_t * const clscb)
{
    return &clscb->arintcb;
}

static AR_FORCE_INLINE ar_tcb_t* ar_get_ar_tcb(
    const tcb_t * const p_mtcb)
{
    return (ar_tcb_t *)p_mtcb->migratable.exinf;
}

static AR_FORCE_INLINE void ar_task_pre_exit(
    clscb_t * const clscb,
    const tcb_t * const p_mtcb)
{
    if (p_mtcb != NULL)
    {
        if (USER_CFG_STD_ON_USE_POSTTASKHOOK() != (uint32)0)
        {
            ar_posttaskhook_call();
        }
        /*
         * post process
         */
        if (USER_CFG_STD_ON_EXIST_OSAP() != (uint32)0)
        {
            ar_tcb_t *p_atcb;
            p_atcb = ar_get_ar_tcb(p_mtcb);
            if (clscb->terminated_running == (mcos_bool_t)mcos_false)
            {
                /* preempted or yielded */
                p_atcb->p_save_osapconfig = clscb->aroscb.p_currentosap;    /* push p_currentosap */
            }
            else
            {
                /* terminated */
                p_atcb->p_save_osapconfig = clscb->aroscb.p_runosap;        /* push p_runosap */
            }
        }
        else
        {
            /* Nothing to do */
        }
    }
    else
    {
        /* Nothing to do */
    }
}

static AR_FORCE_INLINE void ar_task_post_start_mksp(
    clscb_t * const clscb,
    tcb_t * const tcb)
{
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
    const ar_osap_config_t  *p_currentosap = NULL;
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

    /*
     * called in critical section, and used micro-kernel stack
     */
    if (tcb != NULL)
    {
        ar_tcb_t *p_atcb;

        p_atcb = (ar_tcb_t*)tcb->migratable.exinf;
        /* current_xpri is a task priority, not interrupt priority when context switch */
        if (p_atcb->current_xpri < (sint32)p_atcb->p_config->exec_tpri)
        {
            /* priority inherited */
            tcb->migratable.cpri = (uint8_t)p_atcb->current_xpri;
        }
        else
        {
            p_atcb->current_xpri = (sint32)p_atcb->p_config->exec_tpri;
            tcb->migratable.cpri = p_atcb->p_config->exec_tpri;
        }

        if (USER_CFG_STD_ON_EXIST_OSAP() != (uint32)0)
        {
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
            p_currentosap = clscb->aroscb.p_currentosap;
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
            clscb->aroscb.p_runosap = p_atcb->p_config->p_osapconfig;
            clscb->aroscb.p_currentosap = p_atcb->p_save_osapconfig;    /* pop p_currentosap */
        }
        else
        {
            /* Nothing to do */
        }

        if (USER_CFG_STD_ON_USE_PRETASKHOOK() != (uint32)0)
        {
            ar_pretaskhook_call_internal((mcos_uintptr_t)0U, (mcos_uintptr_t)0U);
        }

#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)

        if (p_currentosap != clscb->aroscb.p_currentosap)
        {
            /* Change MPU settings */
            if (clscb->aroscb.p_currentosap->osap_protected != (boolean)FALSE)
            {
                xmcos_ar_set_mpu_regions(clscb->aroscb.p_currentosap->osap_id);
            }
            else
            {
                /* Nothing to do */
            }
#if (XMCOS_AR_USE_APPLICATION_CHANGED == STD_ON)
            xmcos_ar_application_changed(clscb->aroscb.p_currentosap->osap_id);
#endif /* #if (XMCOS_AR_USE_APPLICATION_CHANGED == STD_ON) */
        }
        else
        {
            /* Nothing to do */
        }

        /* The stack setting is also used to obtain the stack area of the context  */
        xmcos_ar_set_mpu_region_task_stack(clscb,
            tcb->migratable.stkaddr, tcb->migratable.stksz, p_atcb);

#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

    }
    else
    {
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
        clscb->aroscb.p_runosap = NULL;
        clscb->aroscb.p_currentosap = NULL;
#if (XMCOS_AR_USE_APPLICATION_CHANGED == STD_ON)
        xmcos_ar_application_changed(INVALID_OSAPPLICATION);
#endif /* #if (XMCOS_AR_USE_APPLICATION_CHANGED == STD_ON) */

#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
    }
}
#endif /* #if MCOS_AUTOSAR */

#if MCOS_USE_PROCESS_MODEL
/*
 * get process ID that the thread belongs to
 */
MCOS_INLINE unsigned int mcos_cls_get_pid(
    tcb_t *tcb)
{
    return tcb->migratable.process.pid;
}

/*
 * get logical space ID that the thread belongs to
 */
MCOS_INLINE unsigned int mcos_cls_get_lsid(
    tcb_t *tcb)
{
    return tcb->migratable.process.space.lsid;
}

/*
 * get thread local space page table
 */
MCOS_INLINE void* mcos_cls_get_uatb(
    tcb_t *tcb)
{
    return tcb->migratable.process.space.uatb;
}

/*
 * set process ID that the thread belongs to
 */
MCOS_INLINE void mcos_cls_set_pid(
    tcb_t *tcb, unsigned int pid)
{
    tcb->migratable.process.pid = pid;
}

/*
 * set logical space ID that the thread belongs to
 */
MCOS_INLINE void mcos_cls_set_lsid(
    tcb_t *tcb, unsigned int lsid)
{
    tcb->migratable.process.space.lsid = lsid;
    return;
}

/*
 * set thread local space page table
 */
MCOS_INLINE void mcos_cls_set_uatb(
    tcb_t *tcb, void *uatb)
{
    tcb->migratable.process.space.uatb = uatb;
    return;
}

/*
 * check if this thread belongs to a process
 */
MCOS_INLINE unsigned int mcos_cls_is_process_thread(
    tcb_t *tcb)
{
    return (tcb->migratable.process.ulstack.stksz != 0) ? (unsigned int)mcos_true : (unsigned int)mcos_false;
}

/* Get saved stack frame pointer */
MCOS_INLINE void* mcos_cls_get_ssp(
    const mkcb_t *mkcb, mcos_id_t tid)
{
    void    *ssp;

    ssp = 0;
    if (tid == 0)
    {
        clscb_t *clscb;
        clscb = mcos_mkcc_get_clscb(mkcb);
        if (clscb->running != 0)
        {
            ssp = clscb->running->migratable.process.space.ssp;
        }
    }
    else
    {
        tcb_t   *tcb;
        tcb = mcos_cls_search_thread_in_ready(mkcb, tid);
        if (tcb == 0)
        {
            tcb = mcos_cls_search_thread_in_waiting(mkcb, tid);
            if (tcb == 0)
            {
                tcb = mcos_cls_search_thread_in_suspended(mkcb, tid);
            }
        }
        if (tcb != 0)
        {
            ssp = tcb->migratable.process.space.ssp;
        }
    }

    return ssp;
}

/* Set saved stack frame pointer
 * Note: This routine should be used from the non-thread context. */
MCOS_INLINE void mcos_cls_set_ssp(
    const mkcb_t *mkcb, mcos_id_t tid, void *set, void *prev)
{
    void    **ssp;

    if (tid == 0)
    {
        clscb_t *clscb;
        clscb = mcos_mkcc_get_clscb(mkcb);
        if (clscb->running != 0)
        {
            ssp = &clscb->running->migratable.process.space.ssp;
            if (*ssp == prev)
            {
                *ssp = set;
            }
        }
    }
    else
    {
        tcb_t   *tcb;
        tcb = mcos_cls_search_thread_in_ready(mkcb, tid);
        if (tcb != 0)
        {
            ssp = &tcb->migratable.process.space.ssp;
            if (*ssp == prev)
            {
                *ssp = set;
            }
        }
    }
}

MCOS_INLINE mcos_uintptr_t mcos_cls_set_esp(
    const mkcb_t *mkcb, mcos_uintptr_t sp)
{
    mcos_uintptr_t   esp; /* Save last SP */
    clscb_t     *clscb;

    clscb = mcos_mkcc_get_clscb(mkcb);
    esp = clscb->esp;
    clscb->esp = sp;

    return esp;
}

MCOS_INLINE mcos_uintptr_t mcos_cls_get_esp(
    const mkcb_t *mkcb)
{
    clscb_t     *clscb;

    clscb = mcos_mkcc_get_clscb(mkcb);

    return clscb->esp;
}
#endif  /* MCOS_USE_PROCESS_MODEL */

#endif /* MCOS_CLS_H */
