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
[mcos_msg.h] - MCOS micro-kernel message header
****************************************************************************/
#ifndef MCOS_MSG_H
#define MCOS_MSG_H

#include <mcos/system.cfg>
#include "mcos/mcos.h"
#include "mcos/mcos_ds.h"
#include "mcos_def.h"

/* message generic id */
typedef uint16_t msg_generic_id_t;

/* message id */
typedef struct
{
    /*
     * message authority            : 1
     * reserved                     : 2
     * accept module                : 1
     * specified id type            : 2
     * request or reply             : 1
     * wait current thread or not   : 1
     * kind                         : 8
     */
    msg_generic_id_t type;

    uint16_t ack            :   1;  /* ack, nack */
    uint16_t resender_lcid  :   10; /* re-sender core id */
    uint16_t clmm           :   3;  /* pass message to CLMM */

#if MCOS_MSGPROF
    uint16_t hwcl           :   1;  /* from/to external cluster */
    uint16_t padding        :   1;  /* padding */
#else /* MCOS_MSGPROF */
    uint16_t padding        :   2;  /* padding */
#endif /* MCOS_MSGPROF */
} msg_idf_t;

typedef union
{
    msg_idf_t id;               /* id */
    uint32_t idall;             /* id all field (for initialize) */
} msg_id_t;


#define MSG_AUTHO_SIZE          (1U)
#define MSG_RSVD_SIZE           (2U)
#define MSG_MOD_SIZE            (1U)
#define MSG_SPEC_SIZE           (2U)
#define MSG_CLAS_SIZE           (1U)
#define MSG_WAIT_SIZE           (1U)
#define MSG_KIND_SIZE           (8U)
#define MSG_TYPE_SIZE           (MSG_KIND_SIZE + MSG_WAIT_SIZE + MSG_CLAS_SIZE + MSG_SPEC_SIZE + MSG_MOD_SIZE + MSG_RSVD_SIZE + MSG_AUTHO_SIZE)

#define MSG_ACK_SIZE            (1U)
#define MSG_RESND_LCID_SIZE     (10U)
#define MSG_CLMM_SIZE           (3U)
#if MCOS_MSGPROF
#define MSG_HWCL_SIZE           (1U)
#define MSG_PAD_SIZE            (1U)
#else /* MCOS_MSGPROF */
#define MSG_HWCL_SIZE           (0U)
#define MSG_PAD_SIZE            (2U)
#endif /* MCOS_MSGPROF */

#define MSG_TYPE_SHIFT          (MSG_ACK_SIZE + MSG_RESND_LCID_SIZE + MSG_CLMM_SIZE + MSG_HWCL_SIZE + MSG_PAD_SIZE)
#define MSG_ACK_SHIFT           (MSG_RESND_LCID_SIZE + MSG_CLMM_SIZE + MSG_HWCL_SIZE + MSG_PAD_SIZE)
#define MSG_RESND_SHIFT         (MSG_CLMM_SIZE + MSG_HWCL_SIZE + MSG_PAD_SIZE)
#define MSG_CLMM_SHIFT          (MSG_HWCL_SIZE + MSG_PAD_SIZE)
#define MSG_HWCL_SHIFT          (MSG_PAD_SIZE)

#define MSG_TYPE_DEFAULT        (0x00UL << MSG_TYPE_SHIFT)
#define MSG_ACK_DEFAULT         (0x00UL << MSG_ACK_SHIFT)
#define MSG_RESND_LCID_DEFAULT  (0x00UL << MSG_RESND_SHIFT)
#define MSG_CLMM_DEFAULT        (0x00UL << MSG_CLMM_SHIFT)
#define MSG_HWCL_DEFAULT        (0x00UL << MSG_HWCL_SHIFT)

#define MSG_ID_DEFAULT          (MSG_TYPE_DEFAULT | MSG_ACK_DEFAULT | MSG_RESND_LCID_DEFAULT | MSG_CLMM_DEFAULT | MSG_HWCL_DEFAULT)

#define NUM_RCIDX_1             (1)

/* message id ack */
#define MSG_ACK_NONE            (0x0U)                          /* normal */
#define MSG_ACK_NACK            (0x1U)                          /* nack */

/* message id type-authority */
#define MSG_AUTHO_SHIFT         (MSG_KIND_SIZE + MSG_WAIT_SIZE + MSG_CLAS_SIZE + MSG_SPEC_SIZE + MSG_MOD_SIZE + MSG_RSVD_SIZE) /* module bit shift */
#define MSG_AUTHO_FLAG_USER     (0x00UL)                        /* user message flag */
#define MSG_AUTHO_FLAG_SYSTEM   (0x01UL)                        /* system message flag */
#define MSG_AUTHO_FLAG_MASK     (0x01UL)                        /* authority flag mask */
#define MSG_AUTHO_USER          (MSG_AUTHO_FLAG_USER << MSG_AUTHO_SHIFT)    /* user message */
#define MSG_AUTHO_SYSTEM        (MSG_AUTHO_FLAG_SYSTEM << MSG_AUTHO_SHIFT)  /* system message */
#define MSG_AUTHO_MASK          (MSG_AUTHO_FLAG_MASK << MSG_AUTHO_SHIFT)    /* authority message */

/* message id type-module */
#define MSG_MOD_SHIFT           (MSG_KIND_SIZE + MSG_WAIT_SIZE + MSG_CLAS_SIZE + MSG_SPEC_SIZE) /* module bit shift */
#define MSG_MOD_MASK            (0x01UL << MSG_MOD_SHIFT)       /* module mask */
#define MSG_MOD_CLS             (0x00UL << MSG_MOD_SHIFT)       /* send to core local scheduler */
#define MSG_MOD_MSGM            (0x01UL << MSG_MOD_SHIFT)       /* send to message manager */

/* message id type-specified */
#define MSG_SPEC_SHIFT          (MSG_KIND_SIZE + MSG_WAIT_SIZE + MSG_CLAS_SIZE) /* specified bit shift */
#define MSG_SPEC_MASK           (0x03UL << MSG_SPEC_SHIFT)      /* specified mask */
#define MSG_SPEC_TID            (0x00UL << MSG_SPEC_SHIFT)      /* receiver is specified by thread id */
#define MSG_SPEC_LCID           (0x01UL << MSG_SPEC_SHIFT)      /* receiver is specified by core id */
#define MSG_SPEC_SID            (0x02UL << MSG_SPEC_SHIFT)      /* receiver is specified by server id */
#define MSG_SPEC_NONE           (0x03UL << MSG_SPEC_SHIFT)      /* receiver is not specified (self) */

/* message id type-class */
#define MSG_CLAS_SHIFT          (MSG_KIND_SIZE + MSG_WAIT_SIZE) /* class bit shift */
#define MSG_CLAS_MASK           (0x01UL << MSG_CLAS_SHIFT)      /* class mask */
#define MSG_CLAS_REQ            (0x00UL << MSG_CLAS_SHIFT)      /* request */
#define MSG_CLAS_REP            (0x01UL << MSG_CLAS_SHIFT)      /* reply */

/* message id type-wait */
#define MSG_WAIT_SHIFT          (MSG_KIND_SIZE)                 /* wait bit shift */
#define MSG_WAIT_MASK           (0x01UL << MSG_WAIT_SHIFT)      /* wait mask */
#define MSG_WAIT_NONE           (0x00UL << MSG_WAIT_SHIFT)      /* no wait */
#define MSG_WAIT_WAIT           (0x01UL << MSG_WAIT_SHIFT)      /* set current thread to wait for replying */

/* message id type-kind */
#define MSG_KIND_SHIFT          (0)                             /* kind bit shift */
#define MSG_KIND_MASK           (0xffUL << MSG_KIND_SHIFT)      /* kind mask */

/* message id type */

/* MSG_CAT_CREQ */
#define MSG_TCRE                (0x00UL | MSG_MOD_CLS | MSG_SPEC_LCID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)      /* mcos_thread_create (thread scheduler passed) */
#define MSG_TMIG_RSV            (0x01UL | MSG_MOD_CLS | MSG_SPEC_LCID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)    /* thread_migrate reserve resource */
#define MSG_TMIG_URSV           (0x02UL | MSG_MOD_CLS | MSG_SPEC_LCID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)    /* thread_migrate unresrve resource */
#define MSG_TMIG_SND            (0x03UL | MSG_MOD_CLS | MSG_SPEC_LCID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)    /* thread_migrate send thread */
#define MSG_TMIG_RCV            (0x04UL | MSG_MOD_CLS | MSG_SPEC_LCID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)    /* thread_migrate receive thread */
#define MSG_LDI                 (0x05UL | MSG_MOD_CLS | MSG_SPEC_LCID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)    /* measuring load information */
#define MSG_TCRED               (0x06UL | MSG_MOD_CLS | MSG_SPEC_LCID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)      /* mcos_thread_create (thread scheduler is not passed) */
#define MSG_TPRE_ACT            (0x07UL | MSG_MOD_CLS | MSG_SPEC_LCID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)    /* activate thread-pool request execution thread */
#define MSG_HFRE                (0x08UL | MSG_MOD_CLS | MSG_SPEC_LCID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)    /* free heap mempry to another core */
#define MSG_RSLVC_TS            (0x09UL | MSG_MOD_CLS | MSG_SPEC_LCID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)    /* resolve lcid */
#define MSG_LTMUPD              (0x0aUL | MSG_MOD_CLS | MSG_SPEC_LCID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)    /* update local time */
#define MSG_LTMTICK             (0x0bUL | MSG_MOD_CLS | MSG_SPEC_LCID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)      /* tick of local time */
#define MSG_REF_CLS             (0x0cUL | MSG_MOD_CLS | MSG_SPEC_LCID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)      /* get cls reference */
#define MSG_CSRCRE              (0x0dUL | MSG_MOD_CLS | MSG_SPEC_LCID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)      /* mcos_cyclic_create */
#define MSG_CSRDEL              (0x0eUL | MSG_MOD_CLS | MSG_SPEC_LCID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)      /* mcos_cyclic_delete */
#define MSG_RSLVC_R             (0x0fUL | MSG_MOD_CLS | MSG_SPEC_LCID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)    /* resolve lcid return */
#define MSG_TRACE_HOOK          (0x10UL | MSG_MOD_CLS | MSG_SPEC_LCID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)      /* trace hook register */
#define MSG_DSMCRE              (0x11UL | MSG_MOD_CLS | MSG_SPEC_LCID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)      /* mcos_dsm_create */
#define MSG_DSMDEL              (0x12UL | MSG_MOD_CLS | MSG_SPEC_LCID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)      /* mcos_dsm_delete */
#define MSG_DSMATT              (0x13UL | MSG_MOD_CLS | MSG_SPEC_LCID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)      /* mcos_dsm_attach */
#define MSG_DSMRAT              (0x14UL | MSG_MOD_CLS | MSG_SPEC_LCID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)      /* mcos_dsm_reattach */
#define MSG_DSMDET              (0x15UL | MSG_MOD_CLS | MSG_SPEC_LCID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)      /* mcos_dsm_detach */
#define MSG_DSMINF              (0x16UL | MSG_MOD_CLS | MSG_SPEC_LCID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)      /* mcos_dsm_get_info */

/* MSG_CAT_TREQ */
#define MSG_TSTA                (0x00UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* mcos_thread_start */
#define MSG_TWUP                (0x01UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* mcos_thread_wakeup */
#define MSG_MSNDS               (0x02UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* mcos_message_send (sync, not call) */
#define MSG_MSNDSC              (0x03UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* mcos_message_send (sync call) */
#define MSG_MSNDA               (0x04UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)       /* mcos_message_send (async, not call) */
#define MSG_MSNDAC              (0x05UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)       /* mcos_message_send (async call) */
#define MSG_RRMSNDS             (0x06UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* mcos_rrmessage_send (sync, not call) */
#define MSG_RRMSNDSC            (0x07UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* mcos_rrmessage_send (sync) */
#define MSG_RRMSNDSF            (0x08UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* mcos_rrmessage_send (sync, shared memory) */
#define MSG_RRMSNDA             (0x09UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)       /* mcos_rrmessage_send (async, not call) */
#define MSG_RRMSNDAC            (0x0aUL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)       /* mcos_rrmessage_send (async) */
#define MSG_TGETN               (0x0bUL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* mcos_thread_get_name */
#define MSG_TDELD               (0x0cUL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* delete dormant thread */
#define MSG_REF_THREAD          (0x0dUL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* thread reference */
#define MSG_MSNDSL              (0x0eUL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* mcos_message_send (sync, large) */
#define MSG_MSNDSLP             (0x0fUL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)       /* mcos_message_send (sync, a part of large) */
#define MSG_MSNDSLPC            (0x10UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)       /* mcos_message_send (sync, a part of large, call) */
#define MSG_MSNDSLPM            (0x11UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* mcos_message_send (sync, a part of large, milestone) */
#define MSG_MSNDSLPMC           (0x12UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* mcos_message_send (sync, a part of large, milestone) */
#define MSG_RRMSNDM             (0x13UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* mcos_rrmessage_send (mcos_message_send mode) */
#define MSG_RELWAI              (0x14UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)       /* mcos_message_control */
#define MSG_RELRRMSND           (0x15UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)       /* mcos_message_control cancel sending */
#define MSG_SRVCTRL             (0x16UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* mcos_server_register/mcos_server_unregister */
#define MSG_SMSOPEN             (0x17UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* mcos_smessage_tx_open */
#define MSG_SMSCLOSE            (0x18UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* mcos_smessage_tx_close */
#define MSG_SMSEXEC             (0x19UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)       /* mcos_smessage_tx_send */
#define MSG_SMRCLOSE            (0x1aUL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* mcos_smessage_rx_close */
#define MSG_SMRREL              (0x1bUL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)       /* mcos_smessage_rx_free */
#define MSG_SMRWAIT_END         (0x1cUL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* mcos_smessage_tx_send reply */
#define MSG_KPROF_GETTHRSTK     (0x1dUL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* mcos_kprof_threadstack_get_info */
#define MSG_DSMWAIT_END         (0x1eUL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)       /* mcos_dsm_attach/reatach release waiting */

#if MCOS_TK_API
#define MSG_TKAPIS              (0x1fUL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* TK APIs handled by CLS (sync, not call) */
#define MSG_TKAPIA              (0x20UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)       /* TK APIs handled by CLS (async, not call) */
#endif /* MCOS_TK_API */

#if MCOS_PT_API
#define MSG_PTAPIS              (0x21UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* PT APIs handled by CLS (sync, not call) */
#define MSG_PTAPIA              (0x22UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)       /* PT APIs handled by CLS (async, not call) */
#endif /* MCOS_PT_API */

#if MCOS_AUTOSAR
#define MSG_TCHAIN              (0x23UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* mcos_thread_chain */
#define MSG_TCHAIN_EXT          (0x24UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)       /* mcos_thread_chain reply (exit) */
#endif /* MCOS_AUTOSAR */

#if !MCOS_AUTOSAR
#define MSG_TSUSP               (0x25UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* mcos_thread_suspend */
#define MSG_TRESU               (0x26UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* mcos_thread_resume */
#define MSG_TRESF               (0x27UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* mcos_thread_resume (forced) */
#define MSG_TSUSP2              (0x28UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* mcos_thread_suspend_async */
#define MSG_TRESU2              (0x29UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* mcos_thread_resume_async */
#define MSG_TRESF2              (0x2aUL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* mcos_thread_resume_async (forced) */
#endif /* !MCOS_AUTOSAR */

#if MCOS_PT_API
#define MSG_TSETREG             (0x2bUL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* posix_debug_thread_set_registers */
#define MSG_TGETREG             (0x2cUL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* posix_debug_thread_get_registers */
#endif

/* MSG_CAT_TREP */
#define MSG_TCRE_R              (0x00UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* mcos_thread_create return */
#define MSG_TSTA_R              (0x01UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* mcos_thread_start return */
#define MSG_TWUP_R              (0x02UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* mcos_thread_wakeup return */
#define MSG_MSND_R              (0x03UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* mcos_message_send return */
#define MSG_TMIG_R              (0x04UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* thread_migrate return */
#define MSG_TPACT_R             (0x05UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* thread-pool activate return */
#define MSG_RRMSND_R            (0x06UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* mcos_rrmessage_send return */
#define MSG_TDELD_R             (0x07UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* thread delete return */
#define MSG_TGETN_R             (0x08UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* mcos_thread_get_name return */
#define MSG_REF_THREAD_R        (0x09UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* get_thread_reference   return */
#define MSG_REF_CLS_R           (0x0aUL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* get_cls return */
#define MSG_CSRCREDEL_R         (0x0bUL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* mcos_cyclic_create/delete return */
#define MSG_RRMREP              (0x0cUL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_USER)       /* mcos_rrmessage_reply (not call) */
#define MSG_RRMREPC             (0x0dUL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_USER)       /* mcos_rrmessage_reply */
#define MSG_SRVCTRL_R           (0x0eUL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* mcos_server_register/mcos_server_unregister reply */
#define MSG_SMSOPEN_R           (0x0fUL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* mcos_smessage_tx_open reply */
#define MSG_SMSCLOSE_R          (0x10UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* mcos_smessage_tx_close reply */
#define MSG_SMRCLOSE_R          (0x11UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* receive session close reply */
#define MSG_DSMCRE_R            (0x12UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* mcos_dsm_create reply */
#define MSG_DSMDEL_R            (0x13UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* mcos_dsm_delete reply */
#define MSG_DSMATT_R            (0x14UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* mcos_dsm_attach reply */
#define MSG_DSMRAT_R            (0x15UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* mcos_dsm_reattach reply */
#define MSG_DSMDET_R            (0x16UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* mcos_dsm_detach reply */
#define MSG_DSMINF_R            (0x17UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* mcos_dsm_get_info reply */
#define MSG_KPROF_GETTHRSTK_R   (0x18UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* mcos_kprof_threadstack_get_info reply */

#if MCOS_TK_API
#define MSG_TKAPI_R             (0x19UL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* TK API handled by CLS reply */
#endif /* MCOS_TK_API */

#if MCOS_PT_API
#define MSG_PTAPI_R             (0x1aUL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* PT API handled by CLS reply */
#endif /* MCOS_PT_API */

#if !MCOS_AUTOSAR
#define MSG_TSUSP_R             (0x1bUL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* mcos_thread_suspend return */
#define MSG_TRESU_R             (0x1cUL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* mcos_thread_resume return */
#endif /* !MCOS_AUTOSAR */

#if MCOS_PT_API
#define MSG_TSETREG_R           (0x1dUL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* posix_debug_thread_set_registers return */
#define MSG_TGETREG_R           (0x1eUL | MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* posix_debug_thread_get_registers return */
#endif

/* MSG_CAT_NREQ */
#define MSG_SRVR                (0x00UL | MSG_MOD_CLS | MSG_SPEC_NONE | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)    /* dummy */
#define MSG_TEXT_SELF           (0x01UL | MSG_MOD_CLS | MSG_SPEC_NONE | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)      /* mcos_thread_exit (exit) */
#define MSG_TEXD_SELF           (0x02UL | MSG_MOD_CLS | MSG_SPEC_NONE | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)      /* mcos_thread_exit (exit and delete) */
#define MSG_TSLP_SELF           (0x03UL | MSG_MOD_CLS | MSG_SPEC_NONE | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)      /* mcos_thread_sleep */
#define MSG_MRCVA_SELF          (0x04UL | MSG_MOD_CLS | MSG_SPEC_NONE | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)      /* mcos_message_receive (async) */
#define MSG_MRCVS_SELF          (0x05UL | MSG_MOD_CLS | MSG_SPEC_NONE | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)      /* mcos_message_receive (sync) */
#define MSG_ROTRDQ_SELF         (0x06UL | MSG_MOD_CLS | MSG_SPEC_NONE | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)      /* mcos_thread_delay (time == 0) */
#define MSG_RRMRCV_SELF         (0x07UL | MSG_MOD_CLS | MSG_SPEC_NONE | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)      /* mcos_rrmessage_receive */
#define MSG_DPRII_SELF          (0x08UL | MSG_MOD_CLS | MSG_SPEC_NONE | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)      /* disable priority inheritance */
#define MSG_SMSWAIT_SELF        (0x09UL | MSG_MOD_CLS | MSG_SPEC_NONE | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)      /* mcos_smessage_tx_send wait */
#define MSG_SMROPEN_SELF        (0x0aUL | MSG_MOD_CLS | MSG_SPEC_NONE | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)      /* mcos_smessage_rx_open */
#define MSG_SMRGET_SELF         (0x0bUL | MSG_MOD_CLS | MSG_SPEC_NONE | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)      /* mcos_smessage_rx_receive */
#define MSG_SMSALLOC_SELF       (0x0cUL | MSG_MOD_CLS | MSG_SPEC_NONE | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)      /* mcos_smessage_tx_allocate */

/* MSG_MOD_CLS | MSG_SPEC_NONE | MSG_CLAS_REP */
#define MSG_TSLP_R              (0x00UL | MSG_MOD_CLS | MSG_SPEC_NONE | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_USER)      /* mcos_thread_sleep return */
#define MSG_MRCV_R              (0x01UL | MSG_MOD_CLS | MSG_SPEC_NONE | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_USER)      /* mcos_message_receive return */
#define MSG_RRMRCV_R            (0x02UL | MSG_MOD_CLS | MSG_SPEC_NONE | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_USER)      /* mcos_rrmessage_receive return */
#define MSG_SMSWAIT_R           (0x03UL | MSG_MOD_CLS | MSG_SPEC_NONE | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_USER)      /* mcos_smessage_tx_send wait return */
#define MSG_SMSALLOC_R          (0x04UL | MSG_MOD_CLS | MSG_SPEC_NONE | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_USER)      /* mcos_smessage_tx_allocate return */
#define MSG_SMROPEN_R           (0x05UL | MSG_MOD_CLS | MSG_SPEC_NONE | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_USER)      /* mcos_smessage_rx_open return */
#define MSG_SMRGET_R            (0x06UL | MSG_MOD_CLS | MSG_SPEC_NONE | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_USER)      /* mcos_smessage_rx_receive return */
#define MSG_DSMWAIT_R           (0x07UL | MSG_MOD_CLS | MSG_SPEC_NONE | MSG_CLAS_REP | MSG_WAIT_NONE | MSG_AUTHO_USER)      /* mcos_dsm_attach/reatach wait return */

/* MSG_CAT_SREQ */
#define MSG_TCRE_TS             (0x00UL | MSG_MOD_CLS | MSG_SPEC_SID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_SYSTEM)     /* mcos_thread_create (caller -> ts) */
#define MSG_TMIG_TS             (0x01UL | MSG_MOD_CLS | MSG_SPEC_SID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_SYSTEM)     /* thread_migrate (caller -> ts) */
#define MSG_UTMCD_TS            (0x02UL | MSG_MOD_CLS | MSG_SPEC_SID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* update thread map (created) */
#define MSG_UTMCF_TS            (0x03UL | MSG_MOD_CLS | MSG_SPEC_SID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* update thread map (failed to create) */
#define MSG_UTMDD_TS            (0x04UL | MSG_MOD_CLS | MSG_SPEC_SID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* update thread map (deleted) */
#define MSG_TMIG_RSV_R          (0x05UL | MSG_MOD_CLS | MSG_SPEC_SID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* thread_migrate reserve resource return */
#define MSG_TMIG_SND_R          (0x06UL | MSG_MOD_CLS | MSG_SPEC_SID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* thread_migrate send thread return */
#define MSG_LDI_TRG_TS          (0x07UL | MSG_MOD_CLS | MSG_SPEC_SID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* measuring load information trigger (timer -> ts) */
#define MSG_LDI_R_TS            (0x08UL | MSG_MOD_CLS | MSG_SPEC_SID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_SYSTEM)     /* notify load information (core -> ts) */
#define MSG_TPACT_TS            (0x09UL | MSG_MOD_CLS | MSG_SPEC_SID | MSG_CLAS_REQ | MSG_WAIT_WAIT | MSG_AUTHO_USER)       /* thread-pool activate (caller -> ts) */
#define MSG_TPDEACT_TS          (0x0aUL | MSG_MOD_CLS | MSG_SPEC_SID | MSG_CLAS_REQ | MSG_WAIT_NONE | MSG_AUTHO_USER)       /* thread-pool activate (caller -> ts) */

#define MSG_CLMM_SYNC_SHIFT     1
#define MSG_CLMM_NORMAL         (0x01U)
#define MSG_CLMM_SYNC_SND       (0x01UL << MSG_CLMM_SYNC_SHIFT)
#define MSG_CLMM_SYNC_REPLY     (0x02UL << MSG_CLMM_SYNC_SHIFT)

/* utility define */
#define MSG_CAT_MASK            (MSG_MOD_MASK | MSG_SPEC_MASK | MSG_CLAS_MASK)
#define MSG_CAT_SHIFT           MSG_CLAS_SHIFT

#define MSG_CAT_TREQ            (MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ)
#define MSG_CAT_TREP            (MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP)
#define MSG_CAT_CREQ            (MSG_MOD_CLS | MSG_SPEC_LCID | MSG_CLAS_REQ)
#define MSG_CAT_NREQ            (MSG_MOD_CLS | MSG_SPEC_NONE | MSG_CLAS_REQ)
#define MSG_CAT_SREQ            (MSG_MOD_CLS | MSG_SPEC_SID | MSG_CLAS_REQ)

/* invalid define */
#define MSG_INVALID             0xFFFFFFFFUL

/* common header for MSG_SPEC_TID */
typedef struct
{
    msg_id_t id;            /* id */
    mcos_id_t tid;          /* receiver thread id */
    mcos_id_t reserved;     /* reserved */
#if MCOS_MSGPROF
    mcos_id_t sender_tid;   /* sender thread id */
    mcos_id_t sender_lcid;  /* sender core id */
#endif /* MCOS_MSGPROF */
} msg_tid_t;

/*
 * common header for MSG_SPEC_LCID
 * MSG_LDI
 */
typedef struct
{
    msg_id_t id;            /* id */
    mcos_id_t lcid;         /* receiver core id */
    mcos_id_t reserved;     /* reserved */
#if MCOS_MSGPROF
    mcos_id_t sender_tid;   /* sender thread id */
    mcos_id_t sender_lcid;  /* sender core id */
#endif /* MCOS_MSGPROF */
} msg_lcid_t;

/* common header for MSG_WAIT_WAIT | MSG_CAT_TREQ */
typedef struct
{
    msg_id_t id;            /* id */
    mcos_id_t reserved;     /* reserved */
    mcos_id_t caller;       /* caller thread id (0 means no reply or from server) */
#if MCOS_MSGPROF
    mcos_id_t sender_tid;   /* sender thread id */
    mcos_id_t sender_lcid;  /* sender core id */
#endif /* MCOS_MSGPROF */
} msg_caller_t;

/*
 * common header for MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REQ
 * MSG_TWUP, MSG_TDELD, MSG_TGETN, MSG_RELWAI, MSG_RELRRMSND, MSG_TCHAIN_EXT
 */
typedef union
{
    msg_tid_t id;           /* id */
    msg_caller_t caller;    /* caller */
} msg_req_t;

/*
 * common header for MSG_MOD_CLS | MSG_SPEC_TID | MSG_CLAS_REP
 * MSG_TCRE_R, MSG_TSTA_R, MSG_TWUP_R, MSG_MSND_R, MSG_TMIG_R, TDELD_R, TDELS_R
 */
typedef struct
{
    msg_id_t id;            /* id */
    mcos_id_t reserved;     /* reserved */
    mcos_erid_t ret;        /* return value */
#if MCOS_MSGPROF
    mcos_id_t sender_tid;   /* sender thread id */
    mcos_id_t sender_lcid;  /* sender core id */
#endif /* MCOS_MSGPROF */
} msg_rep_ret_t;

typedef union
{
    msg_tid_t id;           /* id */
    msg_rep_ret_t ret;      /* ret */
} msg_rep_t;

/*
 * common header for MSG_MOD_CLS | MSG_SPEC_NONE | MSG_CLAS_REQ
 * MSG_SRVR, MSG_TSLP_SELF, MSG_TEXT_SELF, MSG_TEXD_SELF, MSG_MRCVS_SELF, MSG_MRCVA_SELF
 */
typedef struct
{
    msg_id_t id;            /* id */
} msg_reqself_t;

/*
 * common header for MSG_MOD_CLS | MSG_SPEC_NONE | MSG_CLAS_REP
 * MSG_TSLP_R
 */
typedef struct
{
    msg_id_t id;            /* id */
    mcos_erid_t ret;        /* return value */
} msg_repself_t;

/* common header for destination tid */
typedef struct
{
    msg_id_t id;            /* id */
    mcos_id_t reserved;     /* reserved */
    mcos_id_t tid;          /* destination tid */
#if MCOS_MSGPROF
    mcos_id_t sender_tid;   /* sender thread id */
    mcos_id_t sender_lcid;  /* sender core id */
#endif /* MCOS_MSGPROF */
} msg_dest_tid_t;

#if MCOS_USE_PROCESS_MODEL
/* user space information for a process thread */
typedef struct
{
    uint32_t    lsid;       /* logical space ID (Process ID) */
    void        *uatb;      /* user space page table */
} msg_space_t;

/* user space local stack for a process thread */
typedef struct
{
    void *stackaddr;        /* stack address */
    uint32_t stacksize;     /* stack size (word) */
} msg_ulstack_t;

/* user space local stack for a process thread */
typedef struct
{
    msg_space_t   space;    /* user space information */
    msg_ulstack_t ulstack;  /* user space local stack */
} msg_process_t;
#endif  /* MCOS_USE_PROCESS_MODEL */

/* MSG_TCRE, MSG_TCRED */
typedef union
{
    msg_lcid_t id;          /* id */
    msg_caller_t caller;    /* caller thread id */
} msg_tcre_head_t;

typedef struct
{
    msg_tcre_head_t head;   /* header */
    mcos_id_t tid;          /* assigned thread id (0 means core affinity) */
    uint8_t priority;       /* priority */
    uint8_t flags;          /* thread flags */
    uint32_t stacksize;     /* stack size (word) */
    void (*entry)(const uint32_t stacd, void (*exinf)(void)); /* entry address */
    void *stackaddr;        /* stack address (0 means core local memory) */
    mcos_uintptr_t exinf;        /* extended info */
#if MCOS_USE_PROCESS_MODEL
    msg_process_t process;  /* process info */
#endif  /* MCOS_USE_PROCESS_MODEL */
    mcos_char_t name[MCOS_THR_NAME_MAX];   /* thread name */
} msg_tcre_t;

/* MSG_TCRE_TS */
typedef struct
{
    msg_id_t id;            /* id */
    uint8_t priority;       /* priority */
    uint8_t flags;          /* thread flags */
    mcos_id_t reserved;     /* reserved */
} msg_tcre_ts_flags_t;

typedef union
{
    msg_tcre_ts_flags_t flags;  /* thread flags */
    msg_caller_t caller;    /* caller */
} msg_tcre_ts_head_t;

typedef struct
{
    msg_tcre_ts_head_t head; /* header*/
    uint32_t stacksize;     /* stack size (word) */
    void (*entry)(const uint32_t stacd, const mcos_uintptr_t exinf); /* entry address */
    void *stackaddr;        /* stack address */
    mcos_uintptr_t exinf;        /* extended info */
#if MCOS_USE_PROCESS_MODEL
    msg_process_t process;  /* process info */
#endif  /* MCOS_USE_PROCESS_MODEL */
    mcos_char_t name[MCOS_THR_NAME_MAX];   /* thread name */
} msg_tcre_ts_t;

/* MSG_TSTA, MSG_TCHAIN */
typedef struct
{
    msg_req_t req;          /* id and destination */
    mcos_uintptr_t param;        /* parameter to thread entry */
} msg_tsta_t;

/* MSG_TGETN_R */
typedef struct
{
    msg_rep_t head;         /* common header */
    mcos_char_t name[MCOS_THR_NAME_MAX];   /* thread name */
} msg_tgetn_r_t;


/* MSG_SRVCTRL */
typedef struct
{
    msg_req_t req;              /* id and destination */
    int16_t  reqid;             /* request id */
    uint8_t tpri;               /* caller thread priority */
    mcos_char_t name[MCOS_THR_NAME_MAX];              /* server name */
} msg_srvctrl_t;

/* mcos_server_reply */
#define MCOS_MSG_REQID_SERVER_REPLY (0xFFFDU)
typedef struct
{
    uint16_t  repid;           /* above reply id */
    mcos_er_t error;           /* error code */
} msg_srvrep_t;


/* Internal macro to exit CSM DEV/PFS server thread */
#define LFS_CSM_REQID_EXIT          (0xFFFFFFFFFFFFFFFFULL)

/*
 * data address is next one of this header
 * MSG_MSNDS, MSG_MSNDA
 *
 * This structure's size must be a multiple of pointer size.
 * (For example : 8 byte for 64 bit CPU)
 * In case changing the members, adjust the total size.
 * And you must check mcos_util_pend_copy() and do_send()'s third argument(data pointer).
 *
 * If it is attr == 0, tpri is ignored.
 * So, TK/PT set attr = 0 and do not set tpri for performance.
 */
typedef struct
{
    msg_req_t req;          /* common header */
    uint32_t size;          /* message size (byte) */
    uint32_t tpri : 8;      /* sender thread priority */
    uint32_t flags : 24;    /* message flags */
    mcos_uintptr_t : 0;          /* paddiing(for 4or8Byte align) */
} msg_msnd_t;

/*
 * call only
 * MSG_MSNDSC, MSG_MSNDAC
 */
typedef struct
{
    msg_msnd_t req;         /* main header */
    const void *data;       /* message data buffer */
} msg_msndc_t;

/* MSG_MRCV_R */
typedef struct
{
    msg_repself_t rep;      /* common header */
    uint32_t size;          /* message size (byte) */
    uint32_t flags;         /* flags */
    void *data;             /* message data buffer */
    uint32_t no;            /* next acceptable divided message number */
    uint32_t rest;          /* rest divided message size (byte) (non-zero means divided message waiting mode) */
} msg_mrcv_r_t;

/* MSG_UTMCD_TS, MSG_UTMCF_TS, MSG_UTMDD_TS */
typedef struct
{
    msg_id_t id;            /* id */
    mcos_id_t tid;          /* changed thread id */
    mcos_id_t lcid;         /* changed core id */
#if MCOS_MSGPROF
    mcos_id_t sender_tid;   /* sender thread id */
    mcos_id_t sender_lcid;  /* sender core id */
#endif
    uint8_t tpri;           /* changed thread priority */
} msg_utm_t;

/* MSG_RSLVC_TS */
typedef union
{
    msg_lcid_t id;          /* id */
    msg_dest_tid_t tid;     /* thread id to resolve */
} msg_rslvc_head_t;

typedef struct
{
    msg_rslvc_head_t head;  /* header */
    mcos_id_t caller;       /* caller core id */
} msg_rslvc_t;

/* MSG_RSLVC_R */
typedef union
{
    msg_lcid_t id;          /* id */
    msg_dest_tid_t tid;     /* thread id to resolve */
} msg_rslvc_r_head_t;

typedef struct
{
    msg_rslvc_r_head_t head;    /* header */
    mcos_id_t lcid;         /* thread's core id (0 means non-exist) */
} msg_rslvc_r_t;

/* MSG_TRACE_HOOK */
typedef struct
{
    msg_lcid_t id;              /* id */
    mcos_ds_trace_hook_t hook;  /* trace routines */
} msg_trace_hook_t;
#if !MCOS_AUTOSAR
/* MSG_TMIG_TS */
typedef union
{
    msg_tid_t tid;          /* migration thread id */
    msg_caller_t caller;    /* caller thread id */
} msg_tmig_ts_head_t;

typedef struct
{
    msg_tmig_ts_head_t head;    /* header */
    mcos_id_t lcid;         /* migration receiver core id */
} msg_tmig_ts_t;
#endif /* !MCOS_AUTOSAR */
/* MSG_TMIG_RSV, MSG_TMIG_URSV */
typedef union
{
    msg_lcid_t id;          /* id and destination */
    msg_dest_tid_t tid;     /* migration thread id */
} msg_tmig_rsv_t;

/* MSG_TMIG_RSV_R, MSG_TMIG_SND_R */
typedef struct
{
    msg_id_t id;            /* id */
    mcos_id_t tid;          /* migration thread id */
    mcos_er_t ret;          /* succeeded or failed */
#if MCOS_MSGPROF
    mcos_id_t sender_tid;   /* sender thread id */
    mcos_id_t sender_lcid;  /* sender core id */
#endif /* MCOS_MSGPROF */
} msg_tmig_rsv_r_t;

/* MSG_TMIG_SND */
typedef union
{
    msg_lcid_t id;          /* id and destination */
    msg_dest_tid_t tid;     /* migration thread id */
} msg_tmig_snd_head_t;

typedef struct
{
    msg_tmig_snd_head_t head;   /* header */
    mcos_id_t lcid;         /* migration receiver core id */
} msg_tmig_snd_t;

/* MSG_TMIG_RCV */
typedef union
{
    msg_lcid_t id;          /* id and destination */
    msg_dest_tid_t tid;     /* migration thread id */
} msg_tmig_rcv_head_t;

typedef struct
{
    msg_tmig_rcv_head_t head;   /* header */
    mcos_uintptr_t sp;           /* migration thread's suspended sp */
} msg_tmig_rcv_t;
#if !MCOS_AUTOSAR
/* MSG_ROTRDQ_SELF */
typedef struct
{
    msg_id_t id;            /* id */
} msg_tdly_rotrdq_t;

/* MSG_LDI_TRG_TS */
typedef struct
{
    msg_id_t id;            /* id */
#if MCOS_MSGPROF
    mcos_id_t dummy1;       /* padding */
    mcos_id_t dummy2;       /* padding */
    mcos_id_t sender_tid;   /* sender thread id */
    mcos_id_t sender_lcid;  /* sender core id */
#endif /* MCOS_MSGPROF */
} msg_ldi_trg_t;
#endif /* !MCOS_AUTOSAR */
/* MSG_LDI_R_TS */
typedef struct
{
    msg_id_t id;            /* id */
    mcos_id_t lcid;         /* sender core id */
    mcos_id_t nmigtid;      /* nomination of migration thread id */
#if MCOS_MSGPROF
    mcos_id_t sender_tid;   /* sender thread id */
    mcos_id_t sender_lcid;  /* sender core id */
#endif /* MCOS_MSGPROF */
    int32_t nmigtload;      /* nomination of migration thread load */
    int32_t load;           /* load information */
    uint8_t hpri;           /* most high priority ready thread's priority */
} msg_ldi_r_t;
#if !MCOS_AUTOSAR
/* MSG_TPACT_TS */
typedef struct
{
    msg_id_t id;            /* id */
    int16_t tcnt;           /* max request thread count */
    mcos_id_t reserved;     /* reserved */
} msg_tpact_ts_tcnt_t;

typedef union
{
    msg_tpact_ts_tcnt_t tcnt;   /* max request thread count */
    msg_caller_t caller;    /* caller thread id */
} msg_tpact_ts_head_t;

typedef struct
{
    msg_tpact_ts_head_t head;   /* header */
    uint8_t tpri;           /* request thread priority */
} msg_tpact_ts_t;

/* MSG_TPDEACT_TS */
typedef struct
{
    msg_id_t id;            /* id */
#if MCOS_MSGPROF
    mcos_id_t dummy1;       /* padding */
    mcos_id_t dummy2;       /* padding */
    mcos_id_t sender_tid;   /* sender thread id */
    mcos_id_t sender_lcid;  /* sender core id */
#endif /* MCOS_MSGPROF */
    uint32_t rcidxes[(MCOS_CFG_GLB_CORE_PER_HWCL_MAX + 31) / 32];
                            /* assigned core indexes */

} msg_tpdeact_ts_t;
#endif /* !MCOS_AUTOSAR */
/* MSG_TPRE_ACT */
typedef struct
{
    msg_id_t id;            /* id */
    mcos_id_t reserved;     /* reserved */
    uint8_t tpri;           /* new thread priority */
} msg_tpre_act_tpri_t;

typedef union
{
    msg_lcid_t id;          /* id and destination */
    msg_tpre_act_tpri_t tpri;   /* new thread priority */
} msg_tpre_act_t;

/* MSG_TPACT_R */
typedef struct
{
    msg_rep_t rep;          /* common reply header */
#if !MCOS_AUTOSAR
    uint32_t rcidxes[(MCOS_CFG_GLB_CORE_PER_HWCL_MAX + 31) / 32];
                            /* assigned core indexes */
#endif /* #if !MCOS_AUTOSAR */
} msg_tpact_r_t;

/* MSG_HFRE */
typedef struct
{
    msg_lcid_t id;          /* id and destination */
    void * addr;            /* address to free */
} msg_hfre_t;

/* MSG_LTMUPD */
typedef struct
{
    msg_lcid_t id;          /* id */
    mcos_systime_t current; /* current time */
} msg_ltmupd_t;

/* MSG_LTMTICK */
typedef struct
{
    msg_lcid_t id;          /* id */
    uint16_t passtime;      /* passed time */
} msg_ltmtick_t;

/* MSG_INFO_THREAD */
typedef struct
{
    msg_req_t req;
    void*     buf;          /* buffer */
} msg_info_thread_t;

/* message */
typedef struct msg_st msg_t;

struct msg_st
{
    uint32_t pri:8;         /* message priority */
    int32_t size:23;        /* message size (word) */
    uint32_t authority:1;    /* message authority(0 or 1) */
    uint32_t *data;         /* message data */
    msg_t *next;            /* queue */
};

/* request message */
typedef struct
{
    uint32_t type;          /* message type */
    void *data;             /* message data */
    int32_t size;           /* message size (bytes) */
#if MCOS_MSGPROF
    mcos_id_t stid;         /* source tid or 0 if MK or -1 if isr */
    mcos_id_t slcid;        /* source lcid or 0 if external hwcl*/
    mcos_id_t dtid;         /* dest tid or 0 if MK */
    mcos_id_t dlcid;        /* dest lcid or 0 if external hwcl */
#endif /* MCOS_MSGPROF */
} reqm_t;

/* fast message header */
typedef union
{
    struct
    {
        /* sync or async */
        uint32_t sync       :   1;
        /* message size (word) */
        uint32_t size       :   6;
        /*
         * sender flags bits
         *  mask                : 9
         *  to isr or thread    : 1
         *  receiver iid or tid : 15
         */
        uint32_t flags      :   25;
        /* padding */
        uint32_t            :   0;
        /* sender thread id */
        uint32_t stid       :   16;
#if MCOS_MSGPROF
        /* sender lcid - MCOS_BASE_LCID */
        uint32_t lcid       :   15;
#endif /* MCOS_MSGPROF */
        /* padding */
        uint32_t            :   0;
    } fields;
    uint64_t value;
} fmsg_header_t;

/*
 * data address is next one of this header
 * MSG_RRMSNDS, MSG_RRMSNDA
 * request-reply message send
 */
typedef struct
{
    /* common header */
    msg_req_t req;
    /* message priority */
    uint8_t pri;
    /* sender thread priority */
    uint8_t tpri;
    /* request extention information */
    uint64_t reqinf;
    /* request size (in bytes) */
    uint32_t reqsz;
    /* reply size (in bytes) */
    uint32_t repsz;
    /* reply */
    void *rep;
} msg_rrmsnd_t;

/*
 * MSG_RRMSNDSC, MSG_RRMSNDAC, MSG_RRMSNDSF
 * request-reply message send
 */
typedef struct
{
    msg_rrmsnd_t rrmsnd;
    /* request */
    void *req;
} msg_rrmsndc_t;

/*
 * MSG_RRMSND_R
 */
typedef struct
{
    /* common header */
    msg_rep_t rep;
    /* receiver thread id */
    mcos_id_t tid;
    /* valid reply size (in bytes) */
    uint32_t repsz;
    /* reply extention information */
    uint64_t repinf;
    /* reply */
    void* repdata;
} msg_rrmsnd_r_t;

/*
 * data address is next one of this header
 * MSG_RRMREP, MSG_RRMREPC
 */
typedef struct
{
    /* common header */
    msg_rep_t rep;
    /* valid reply size (in bytes) */
    uint32_t repsz;
    /* reply extention information */
    uint64_t repinf;
} msg_rrmrep_t;

/* MSG_RRMRCV_R */
typedef struct
{
    msg_repself_t rep;
    mcos_rrmsg_recv_t *info;
    uint32_t req[(uint32_t)MCOS_CFG_RRMSG_BUFSIZE / (uint32_t)WORD_SIZE];
} msg_rrmrcv_r_t;

/* MSG_REF_CLS */
typedef union
{
    /* id and destination */
    msg_lcid_t id;
    /* caller thread id */
    msg_caller_t caller;
} msg_ref_cls_head_t;

typedef struct
{
    /* header */
    msg_ref_cls_head_t head;
    /* buffer */
    void *buf;
}msg_ref_cls_t;

/* MSG_MSNDSLP, MSG_MSNDSLPM */
typedef struct
{
    msg_req_t req;          /* common header */
    uint32_t no;            /* divided message number */
    uint16_t size;          /* message size (byte) */
    mcos_uintptr_t : 0;          /* paddiing(for 4or8Byte align) */
} msg_msndlp_t;

/*
 * call only
 * MSG_MSNDSLPC, MSG_MSNDSLPMC
 */
typedef struct
{
    msg_msndlp_t  req;      /* main header */
    const uint8_t *data;    /* message data buffer */
} msg_msndlpc_t;

#if MCOS_HWCL
/*
 * Note : This type is used to set MSG_MSG_MAX_SIZE.
 */
typedef union
{
    msg_msnd_t      normal;     /* normal message header */
    msg_msndlp_t    divided;    /* divided message header */
} msg_msnd_size_t;
#endif /* #if MCOS_HWCL */

/* MSG_CSRCRE */
typedef union
{
    msg_lcid_t id;          /* id */
    msg_caller_t caller;    /* caller thread id */
} msg_csrcre_head_t;

typedef struct
{
    void* entry;            /* entry address of cyclic service function */
    mcos_uintptr_t param;        /* parameter for CSR entry */
    void* stackaddr;        /* stack address */
    mcos_reltime_t cycle;   /* cycle time */
    size_t stacksize;       /* stack size [byte] */
    uint32_t flag;          /* mode flag */
} msg_csrcre_body_t;

typedef struct
{
    msg_csrcre_head_t head; /* header */
    msg_csrcre_body_t body; /* body */
} msg_csrcre_t;

/* MSG_CSRDEL */
typedef union
{
    msg_lcid_t id;          /* id */
    msg_caller_t caller;    /* caller thread id */
} msg_csrdel_head_t;

typedef struct
{
    mcos_id_t csrid;        /* csr ID */
} msg_csrdel_body_t;

typedef struct
{
    msg_csrdel_head_t head; /* header */
    msg_csrdel_body_t body; /* body */
} msg_csrdel_t;

/* MSG_CSRCREDEL_R */
typedef struct
{
    msg_rep_t rep;          /* common header */
    void      *rel_stack;   /* stack address to release */
} msg_csrcredel_r_t;

#if MCOS_USE_PROCESS_MODEL
typedef struct
{
    /* base members */
    mcos_thr_info_t     base;
    /* additional members for the process model */
    struct {
        uint32_t        pid;        /* Process ID */
        struct {
            uint32_t    lsid;       /* logical space ID */
            void        *uatb;      /* user space page table */
        } space;
        struct {
            mcos_uintptr_t   *stkaddr;   /* user local stack address */
            uint32_t    stksz;      /* user local stack size (word) */
        } ulstack;
    } process;
} mcos_thr_info_ex_t;
#endif /* MCOS_USE_PROCESS_MODEL */

/* MSG_THREAD_INFORMATION */
typedef struct
{
    msg_rep_t rep;
#if MCOS_USE_PROCESS_MODEL
    mcos_thr_info_ex_t thread_info;
#else  /* MCOS_USE_PROCESS_MODEL */
    mcos_thr_info_t thread_info;
#endif /* MCOS_USE_PROCESS_MODEL */
} msg_thinfo_r_t;

/* MSG_CORE_INFORMATION */
typedef struct
{
    msg_rep_t rep;
    mcos_core_info_t core_info;
} msg_coreinfo_r_t;

/* MSG_KPROF_GETTHRSTK */
typedef struct
{
    msg_req_t req;
} msg_kprof_thrstk_info_t;


typedef struct
{
    msg_rep_t rep;
    uint32_t  max_used_stksz;
} msg_kprof_thrstk_info_r_t;

/* MSG_SMSOPEN */
typedef struct
{
    msg_req_t req;          /* common header */
    const void *bufaddr;    /* buffer address */
    uint32_t bufsize;       /* buffer size */
    mcos_id_t ssid;         /* session id */
    mcos_id_t chid;         /* transfer channel id */
    uint8_t sub_ssid;       /* sub ssid */
} msg_smsopen_t;

/* MSG_SMSOPEN_R */
typedef struct
{
    msg_rep_t rep;          /* common header */
    mcos_id_t dest_chid;    /* destination channel id */

    /* these parameters are set by sender thread */
    mcos_id_t scbinit_dest_tid;     /* destination tid */
    mcos_id_t scbinit_ssid;         /* session id */
    mcos_id_t scbinit_chid;         /* channel id */
    mcos_id_t scbinit_sub_ssid;     /* sub session id */
    uint32_t scbinit_bufsize;       /* buffer size */
    const void *scbinit_bufaddr;    /* buffer address */
} msg_smsopen_r_t;

/* MSG_SMSCLOSE */
typedef struct
{
    msg_req_t req;          /* common header */
    mcos_id_t ssid;         /* session id */
} msg_smsclose_t;

/* MSG_SMSEXEC */
typedef struct
{
    msg_req_t req;          /* common header */
    mcos_id_t ssid;         /* session id */
} msg_smsexec_t;

/* MSG_SMSWAIT */
typedef struct
{
    msg_req_t req;          /* common header */
    mcos_id_t ssid;         /* session id */
} msg_smswait_t;

/* MSG_SMSALLOC_SELF */
typedef struct
{
    msg_req_t req;          /* common header */
    mcos_id_t ssid;         /* session id */
} msg_smsalloc_t;

/* MSG_SMROPEN */
typedef struct
{
    msg_req_t req;          /* common header */
} msg_smropen_t;

/* MSG_SMROPEN_R */
typedef struct
{
    msg_rep_t rep;          /* common header */
    mcos_id_t dest_tid;     /* destination tid */
    mcos_id_t dest_chid;    /* destination transfer channel id */
    uint32_t dest_bufsize;  /* destination buffer size */
    const void *bufaddr;    /* buffer address */
    uint8_t sub_ssid;       /* sub ssid */

    /* these parameters are set by sender thread */
    mcos_er_t scbinit_ret;          /* return code */
    mcos_id_t scbinit_ssid;         /* session id */
    mcos_id_t scbinit_chid;         /* channel id */
    const void *scbinit_bufaddr;    /* buffer address */
} msg_smropen_r_t;

/* MSG_SMRCLOSE */
typedef struct
{
    msg_req_t req;          /* common header */
    mcos_id_t ssid;         /* session id */
} msg_smrclose_t;

/* MSG_SMRCLOSE_R */
typedef struct
{
    msg_rep_t rep;          /* common header */
} msg_smrclose_r_t;

/* MSG_SMRGET */
typedef struct
{
    msg_req_t req;          /* common header */
    mcos_id_t ssid;         /* session id */
    uint32_t flags;         /* flags */
} msg_smrget_t;

/* MSG_SMRREL */
typedef struct
{
    msg_req_t req;          /* common header */
    mcos_id_t ssid;         /* session id */
} msg_smrrel_t;

/* MSG_SMRWAIT_END */
typedef struct
{
    msg_req_t req;          /* common header */
    mcos_id_t ssid;         /* session id */
    uint8_t sub_ssid;       /* sub session id */
} msg_smrwait_end_t;

#if MCOS_PT_API
#include <posix/posix_debug.h>

/* MSG_TSETREG */
typedef struct
{
    msg_req_t               req;
    posix_debug_cpu_reg_t   regs;
} msg_thread_set_reg_t;

/* MSG_TSETREG_R */
typedef struct
{
    msg_rep_t               rep;
} msg_thread_set_reg_r_t;

/* MSG_TGETREG */
typedef struct
{
    msg_req_t               req;
    posix_debug_cpu_reg_t   *regs;
} msg_thread_get_reg_t;

/* MSG_TGETREG_R */
typedef struct
{
    msg_rep_t               rep;
    posix_debug_cpu_reg_t   regs;
} msg_thread_get_reg_r_t;
#endif

/* DSM message header */
typedef union
{
    msg_lcid_t id;          /* id */
    msg_caller_t caller;    /* caller thread id */
} msg_dsm_head_t;

/* DSM section information */
typedef struct
{
    void *area;             /* DSM section area */
    uint32_t size;          /* DSM section size */
    mcos_dsm_attach_mode_t mode;    /* DSM attach mode */
    mcos_id_t owner_chid;   /* owner channel id */
    mcos_id_t client_chid;  /* client channel id */
} msg_dsm_section_info_t;

/* MSG_DSMCRE */
typedef struct
{
    msg_dsm_head_t head;    /* DSM request header */
    uint32_t size;          /* size */
    mcos_dsm_create_attr_t attr;    /* attribute */
    void *buffer;           /* buffer */
} msg_dsmcre_t;

/* MSG_DSMCRE_R */
typedef struct
{
    msg_rep_t rep;          /* common reply header */
} msg_dsmcre_r_t;

/* MSG_DSMDEL */
typedef struct
{
    msg_dsm_head_t head;    /* DSM request header */
    mcos_id_t dindex;       /* DSM index */
} msg_dsmdel_t;

/* MSG_DSMDEL_R */
typedef struct
{
    msg_rep_t rep;          /* common reply header */
    void *buffer;           /* buffer */
} msg_dsmdel_r_t;

/* MSG_DSMATT */
typedef struct
{
    msg_dsm_head_t head;    /* DSM request header */
    void *area;             /* DSM section area */
    mcos_dsm_attach_t attach;   /* DSM section attach parameter */
    mcos_id_t dindex;       /* DSM index */
    mcos_id_t client_chid;  /* client channel id */
} msg_dsmatt_t;

/* MSG_DSMATT_R */
typedef struct
{
    msg_rep_t rep;          /* common reply header */
    void *area;             /* DSM section area */
} msg_dsmatt_r_t;

/* MSG_DSMRAT */
typedef struct
{
    msg_dsm_head_t head;    /* DSM request header */
    uint32_t offset;        /* offset */
    mcos_id_t sindex;       /* DSM section index */
} msg_dsmrat_t;

/* MSG_DSMRAT_R */
typedef struct
{
    msg_rep_t rep;          /* common reply header */
    msg_dsm_section_info_t sinfo;   /* DSM section information */
} msg_dsmrat_r_t;

/* MSG_DSMDET */
typedef struct
{
    msg_dsm_head_t head;    /* DSM request header */
    mcos_id_t sindex;       /* DSM section index */
} msg_dsmdet_t;

/* MSG_DSMDET_R */
typedef struct
{
    msg_rep_t rep;          /* common reply header */
    msg_dsm_section_info_t sinfo;   /* DSM section information */
} msg_dsmdet_r_t;

/* MSG_DSMINF */
typedef struct
{
    msg_dsm_head_t head;    /* DSM request header */
    mcos_id_t dindex;       /* DSM index */
} msg_dsminf_t;

/* MSG_DSMINF_R */
typedef struct
{
    msg_rep_t rep;          /* common reply header */
    mcos_dsm_info_t dinfo;  /* DSM information */
} msg_dsminf_r_t;

/* MSG_DSMWAIT_END */
typedef struct
{
    msg_req_t req;          /* common header */
    mcos_id_t sindex;       /* DSM section index */
} msg_dsmwait_end_t;

/*****************************/
/* Message max size check.   */
/*****************************/
COMPILETIME_SIZECHECK_GE(msg_size, ((uint64_t)MCOS_CFG_MSG_SIZE_MAX), ((uint64_t)sizeof(msg_srvrep_t)));

#endif /* #ifndef MCOS_MSG_H */
