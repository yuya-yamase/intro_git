/**
 * file mcos.h
 * brief MCOS interface header
 * date 2011
 * copyright eSOL Co.,Ltd. Tokyo, Japan
 *
 * This software is protected by the law and the agreement concerning
 * a Japanese country copyright method, an international agreement,
 * and other intellectual property right and may be used and copied
 * only in accordance with the terms of such license and with the inclusion
 * of the above copyright notice.
 *
 * This software or any other copies thereof may not be provided
 * or otherwise made available to any other person.  No title to
 * and ownership of the software is hereby transferred.
 *
 * The information in this software is subject to change without
 * notice and should not be construed as a commitment by eSOL Co.,Ltd.
 */

/****************************************************************************
[mcos.h] - MCOS interface header
****************************************************************************/
#ifndef MCOS_H
#define MCOS_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include "mcos_hook_code.h"

#include "mp.cfg"
#include "mcos/mcos_hwcl.cfg"

#ifdef __cplusplus
extern "C"
{
#endif

/* eMCOS Version number */
#define MCOS_VERSION                            0x1115          /**< Version number of the eMCOS specification (ver1.1 rev21) */

/* Error code */
#define MCOS_EOK                                (0)             /**< Success with no error. The system call operated normally. */
#define MCOS_EPAR                               (-1)            /**< Invalid parameter. */
#define MCOS_ENOMEM                             (-2)            /**< Failed due to insufficient memory. */
#define MCOS_ENOEXS                             (-3)            /**< The target object does not exist. */
#define MCOS_EOBJ                               (-4)            /**< The state or attribute of the target object is invalid. */
#define MCOS_ENOMSG                             (-5)            /**< The message does not exist. */
#define MCOS_ELIMIT                             (-6)            /**< The system limit is exceeded. */
#define MCOS_ENOBUF                             (-7)            /**< Failed due to insufficient buffer. */
#define MCOS_ENOSPT                             (-8)            /**< The feature is not supported. */
#define MCOS_ECTX                               (-9)            /**< The context of the invoker is invalid. */
#define MCOS_EMACV                              (-10)           /**< Invalid memory address. */
#define MCOS_EINTR                              (-11)           /**< The system call is interrupted. */
#define MCOS_ESYS                               (-21)           /**< Error due to system abnormality. */

/* mcos_message_send() flags - synchronous */
#define MCOS_MSG_SEND_ASYNC                     (0x00000000U)   /**< Asynchronous communication. It sends a message and exits. */
#define MCOS_MSG_SEND_SYNC                      (0x00010000U)   /**< Synchronous communication. It sends a message and waits for reception. */

/* mcos_message_receive() flags - synchronous */
#define MCOS_MSG_RECV_ASYNC                     (0x00000000U)   /**< Asynchronous communication. It returns with MCOS_ENOMSG if a message was not sent. */
#define MCOS_MSG_RECV_SYNC                      (0x00010000U)   /**< Synchronous communication. It waits for a message to be sent. */

/* mcos_message_send()/mcos_message_receive() flags - message mask */
#define MCOS_MSG_MASK_REQUEST                   (0x00000001U)   /**< Request. Starts thread priority inheritance. */
#define MCOS_MSG_MASK_REPLY                     (0x00000002U)   /**< Reply. Ends thread priority inheritance. */
#define MCOS_MSG_MASK_FROM_ISR                  (0x00000004U)   /**< Free use. It is recommended for use in transmission from the ISR. */
#define MCOS_MSG_MASK_USER1                     (0x00000008U)   /**< Free use. */
#define MCOS_MSG_MASK_USER2                     (0x00000010U)   /**< Free use. */
#define MCOS_MSG_MASK_USER3                     (0x00000020U)   /**< Free use. */
#define MCOS_MSG_MASK_USER4                     (0x00000040U)   /**< Free use. */

/* mcos_message_send() flags - message priority */
#define MCOS_MSG_SEND_MPRI_URGENT               (0x00020000U)   /**< Highest priority. */

/* mcos_message_control() commands */
#define MCOS_MSG_CTL_RELWAI                     (0x01U)         /**< It forcibly releases the messaging wait. */

/* mcos_fmessage_send() flags - synchronous */
#define MCOS_FMSG_SEND_ASYNC                    (0x00000000U)   /**< Asynchronous communication. It sends a message and exits. */
#define MCOS_FMSG_SEND_SYNC                     (0x80000000U)   /**< Synchronous communication. It sends a message and waits for reception. */

/* mcos_fmessage_send() - send to ISR */
#define MCOS_FMSG_SEND_ISR_LCID(lcid)           (mcos_id_t)((uint16_t)(lcid) | 0x8000)  /**< Specify the logical core ID the target ISR implemented. */
#define MCOS_FMSG_SEND_ISR_IID(iid)             (uint32_t)((uint16_t)(iid) | 0x8000)    /**< Specify the interrupt ID of the target ISR. */

/* mcos_fmessage_receive() flags - synchronous */
#define MCOS_FMSG_RECV_ASYNC                    (0x00000000U)   /**< Asynchronous communication. It returns with MCOS_ENOMSG if a message was not sent. */
#define MCOS_FMSG_RECV_SYNC                     (0x80000000U)   /**< Synchronous communication. It waits for a message to be sent. */

/* mcos_fmessage_send()/mcos_message_receive() flags - message mask */
#define MCOS_FMSG_MASK_REQUEST                  (0x00010000U)   /**< Request. Starts thread priority inheritance. */
#define MCOS_FMSG_MASK_REPLY                    (0x00020000U)   /**< Reply. Ends thread priority inheritance. */
#define MCOS_FMSG_MASK_FROM_ISR                 (0x00040000U)   /**< Free use. It is recommended for use in transmission from the ISR. */
#define MCOS_FMSG_MASK_USER1                    (0x00080000U)   /**< Free use. */
#define MCOS_FMSG_MASK_USER2                    (0x00100000U)   /**< Free use. */
#define MCOS_FMSG_MASK_USER3                    (0x00200000U)   /**< Free use. */
#define MCOS_FMSG_MASK_USER4                    (0x00400000U)   /**< Free use. */

/* mcos_thread_exit() modes */
#define MCOS_THR_EXIT_DORMANT                   (0x00U)         /**< Exit and turn the thread DORMANT */
#define MCOS_THR_EXIT_DELETE                    (0x01U)         /**< Exit and delete the thread */

/* mcos_thread_create() lcid */
#define MCOS_LCID_SELF                          (0)             /**< Indicates the core which uses this value. */
#define MCOS_LCID_ANY                           (-1)            /**< Indicates a core in the same cluster as the core which uses this value. */
#define MCOS_LCID_INHERIT                       (-2)            /**< Used only in creating a thread, for a newly-created thread to inherit the LCID
                                                                 * (including MCOS_LCID_ANY and MCOS_LCID_SELF) from the creator thread. */
#define MCOS_LCID_INVALID                       (-3)            /**< Invalid core. */

/* mcos_threadpool_create() priority */
#define MCOS_THRPRI_INHERIT                     (0)             /**< The priority of the thread that invoked this system call is specified. */

/* mcos thread max name length */
#define MCOS_THR_NAME_MAX                       (16U)            /**< mcos thread max name length. */

/* mcos_threadpool_create() attr */
#define MCOS_TPOOL_CRE_NORMAL                   ((uint8_t)0x00U)    /**< A normal thread pool.  */
#define MCOS_TPOOL_CRE_ENABLE_RET               ((uint8_t)0x02U)    /**< Specify this when the return value of the request execution result is necessary
                                                                     * or to manage multiple thread pools in one thread. */

/* mcos_threadpool_execute() mode */
#define MCOS_TPOOL_EXE_ASYNC                    (0)             /**< The system call returns without waiting for completion of the requests.
                                                                 * Completion of request execution may be waited for by mcos_threadpool_wait().
                                                                 * Request IDs are given to the requests. The request IDs are stored in req->reqid.
                                                                 * 0, which means unfinished, is stored in req->finished. */
#define MCOS_TPOOL_EXE_SYNC                     (1)             /**< The system call waits for completion of all requests and then returns.
                                                                 * Request IDs are given to the requests. The request IDs are stored in req->reqid.
                                                                 * 1, which means finished, is stored in req->finished.
                                                                 * If MCOS_TPOOL_CRE_ENABLE_RET is specified to attr for mcos_threadpool_create(),
                                                                 * a return value of each request's function is stored in ret of req. */
#define MCOS_TPOOL_EXE_ASYNC_NOREPLY            (2)             /**< The system call returns without waiting for completion of the requests.
                                                                 * Request IDs are given to the requests. The request IDs are stored in req->reqid.
                                                                 * 1, which means finished, is stored in req->finished. */

/* mcos_threadpool_wait() mode */
#define MCOS_TPOOL_WAIT_SYNC                    (0)             /**<  the system call waits for completion of all requests and then returns.
                                                                 * 1 is stored in all of req->finished.
                                                                 * If this system call is executed normally, it returns 0. */
#define MCOS_TPOOL_WAIT_ASYNC                   (1)             /**<  the system call gets the execution results of the requests that are finished at the time of invocation,
                                                                 * and returns without waiting for completion of the specified requests.
                                                                 * If this system call is executed normally, it returns the number of unfinished requests among the specified requests.
                                                                 * Which requests were finished cannot be acquired from req->finished. */

/* mcos_server_register() register request/reply code. */
#define MCOS_MSG_REQID_SERVER_REGISTER          (-2)            /**< mcos_server_register() register request/reply code.
                                                                 * note servers must not use this value for requestinf in RR messages and request id in standard messages. */
/* mcos_server_unregister() unregister request/reply code. */
#define MCOS_MSG_REQID_SERVER_UNREGISTER        (-1)            /**< mcos_server_unregister() unregister request/reply code.
                                                                 * note servers must not use this value for requestinf in RR messages and request id in standard messages. */

#define MCOS_THR_STATE_NONEXIST                 0x00U
/* mcos_thread_get_info() thread state */
#define MCOS_THR_STATE_DORMANT                  0x01U           /**< Thread state: DORMANT */
#define MCOS_THR_STATE_WAIT                     0x02U           /**< Thread state: WAIT */
#define MCOS_THR_STATE_READY                    0x03U           /**< Thread state: READY */
#define MCOS_THR_STATE_RUNNING                  0x04U           /**< Thread state: RUNNING */

/* mcos_thread_get_info() waitcause */
#define MCOS_THR_WAITCAUSE_THRSLP               0x01            /**< Thread WAIT state: Wait for wakeup */
#define MCOS_THR_WAITCAUSE_MSGRCV               0x02            /**< Thread WAIT state: Wait for message reception (standard message) */
#define MCOS_THR_WAITCAUSE_MSGSND               0x03            /**< Thread WAIT state: Wait for completion of synchronous transmission (standard message) */
#define MCOS_THR_WAITCAUSE_RRMSGRCV             0x04            /**< Thread WAIT state: Wait for message reception (request-reply model message) */
#define MCOS_THR_WAITCAUSE_RRMSGSND             0x05            /**< Thread WAIT state: Wait for completion of synchronous transmission (request-reply model message) */
#define MCOS_THR_WAITCAUSE_SYSCALL              0x06            /**< Thread WAIT state: Wait for reply against system call to a different core */
#define MCOS_THR_WAITCAUSE_THRCRE_REPLY         0x00010006      /**< Thread WAIT state: Wait for requests at the system server */
#define MCOS_THR_WAITCAUSE_THRSTA_REPLY         0x00020006      /**< Thread WAIT state: Wait for a thread create reply */
#define MCOS_THR_WAITCAUSE_THRWUP_REPLY         0x00030006      /**< Thread WAIT state: Wait for a thread start reply */
#define MCOS_THR_WAITCAUSE_THRDEL_REPLY         0x00040006      /**< Thread WAIT state: Wait for a thread wakeup reply */
#define MCOS_THR_WAITCAUSE_THRGETNAME_REPLY     0x00050006      /**< Thread WAIT state: Wait for a thread name get reply */
#define MCOS_THR_WAITCAUSE_TPOOLACT_REPLY       0x00060006      /**< Thread WAIT state: Wait for a thread pool request reciept reply */
#define MCOS_THR_WAITCAUSE_SRVDEL_REPLY         0x00070006      /**< Thread WAIT state: Wait for a server delete reply */
#define MCOS_THR_WAITCAUSE_COREINFO_REPLY       0x00080006      /**< Thread WAIT state: Wait for a core information get reply */
#define MCOS_THR_WAITCAUSE_THRINFO_REPLY        0x00090006      /**< Thread WAIT state: Wait for a thread information get reply */
#define MCOS_THR_WAITCAUSE_TKAPI_REPLY          0x000a0006      /**< Thread WAIT state: Wait for a T-Kernel API reply */
#define MCOS_THR_WAITCAUSE_PTAPI_REPLY          0x000b0006      /**< Thread WAIT state: Wait for a pthread API reply */
#define MCOS_THR_WAITCAUSE_THRSTK_INFO_REPLY    0x000c0006      /**< Thread WAIT state: Wait for a thread stack information get reply */
#define MCOS_THR_WAITCAUSE_CSRCREDEL_REPLY      0x000d0006      /**< Thread WAIT state: Wait for a CSR create/delete reply */
#define MCOS_THR_WAITCAUSE_SRVREG_REPLY         0x000e0006      /**< Thread WAIT state: Wait for a server register/unregister reply */
#define MCOS_THR_WAITCAUSE_SMSGTXOPN_REPLY      0x000f0006      /**< Thread WAIT state: Wait for a sender session open reply */
#define MCOS_THR_WAITCAUSE_SMSGTXCLS_REPLY      0x00100006      /**< Thread WAIT state: Wait for a sender session close reply */
#define MCOS_THR_WAITCAUSE_SMSGTXALC_REPLY      0x00110006      /**< Thread WAIT state: Wait for a send buffer acquire reply */
#define MCOS_THR_WAITCAUSE_SMSGTXSND_REPLY      0x00120006      /**< Thread WAIT state: Wait for a sender session send reply */
#define MCOS_THR_WAITCAUSE_SMSGRXOPN_REPLY      0x00130006      /**< Thread WAIT state: Wait for a receiver session open reply */
#define MCOS_THR_WAITCAUSE_SMSGRXCLS_REPLY      0x00140006      /**< Thread WAIT state: Wait for a receiver session close reply */
#define MCOS_THR_WAITCAUSE_SMSGRXRCV_REPLY      0x00150006      /**< Thread WAIT state: Wait for a receiver session receive reply */
#define MCOS_THR_WAITCAUSE_DSMCREATE_REPLY      0x00160006      /**< Thread WAIT state: Wait for a dsm create reply */
#define MCOS_THR_WAITCAUSE_DSMDELETE_REPLY      0x00170006      /**< Thread WAIT state: Wait for a dsm delete reply */
#define MCOS_THR_WAITCAUSE_DSMATTACH_REPLY      0x00180006      /**< Thread WAIT state: Wait for a dsm attach reply */
#define MCOS_THR_WAITCAUSE_DSMREATTACH_REPLY    0x00190006      /**< Thread WAIT state: Wait for a dsm reattach reply */
#define MCOS_THR_WAITCAUSE_DSMDETACH_REPLY      0x001a0006      /**< Thread WAIT state: Wait for a dsm detach reply */
#define MCOS_THR_WAITCAUSE_DSMGETINFO_REPLY     0x001b0006      /**< Thread WAIT state: Wait for a dsm get info reply */
#define MCOS_THR_WAITCAUSE_DSMATTWAIT_REPLY     0x001c0006      /**< Thread WAIT state: Wait for a dsm attach wait reply */




#define MCOS_THR_WAITCAUSE_SYSSRV               0x07            /**< Thread WAIT state: Wait for requests at the system server */

/* mcos_memory_check_by_tid() type */
#define MCOS_MEMTYPE_ACCREAD                    0x01U           /**< Read access */
#define MCOS_MEMTYPE_ACCWRITE                   0x02U           /**< Write access */
#define MCOS_MEMTYPE_ACCEXECUTE                 0x04U           /**< Execution */

/* mcos_smessage_tx_allocate() flags */
#define MCOS_SMSG_ALLOC_ASYNC                   (0x00000000U)   /**< Asynchronous mode. Returns immediately if the receiver thread has the access right to the receive buffer. */
#define MCOS_SMSG_ALLOC_SYNC                    (0x00000001U)   /**< Synchronous mode. Transits to WAIT if the receiver thread has the access right to the receive buffer,
                                                                 * and waits for the release of the right by the receiver thread. */

/* mcos_smessage_tx_send() flags */
#define MCOS_SMSG_SEND_ASYNC                    (0x00000000U)   /**< Asynchronous mode. Send message and complete operation without waiting. */
#define MCOS_SMSG_SEND_SYNC                     (0x00000001U)   /**< Synchronous mode. Send message and wait for the receiver thread receive the message by transiting to WAIT. */

/* mcos_smessage_rx_receive() flags */
#define MCOS_SMSG_RECV_ASYNC                    (0x00000000U)   /**< Asynchronous mode. Return immediately with error code MCOS_ENOMSG if no message has been sent yet. */
#define MCOS_SMSG_RECV_SYNC                     (0x00000001U)   /**< Synchronous mode. Wait for the message send by transiting to WAIT if no message has been sent yet. */

/* mcos_smessage_get_info() direction */
#define MCOS_SMSG_DIR_RECV                      0x00U           /**< Session-based  message role of current thread: Receiver */
#define MCOS_SMSG_DIR_SEND                      0x01U           /**< Session-based  message role of current thread: Sender */

/* mcos_smessage_get_info() stat */
#define MCOS_SMSG_STAT_DISCON                   0x00U           /**< After the completion of mcos_smessage_rx_close(). */
#define MCOS_SMSG_STAT_BUF_FREE                 0x01U           /**< From the completion of mcos_smessage_tx_open() to the call of mcos_smessage_tx_allocate(),
                                                                 * or from the completion of mcos_smessage_rx_free() to the call of mcos_smessage_tx_allocate(). */
#define MCOS_SMSG_STAT_BUF_TX                   0x02U           /**< From the completion of mcos_smessage_tx_allocate() to the call of mcos_smessage_tx_send(). */
#define MCOS_SMSG_STAT_BUF_RX                   0x03U           /**< From the completion of mcos_smessage_tx_send() to the call of mcos_smessage_rx_free(). */

/* Definitions related to hardware clusters */
#define STR__(s)                                STF__(s)                /**< Convert value s to string */
#define STF__(s)                                #s                      /**< Get value s in string */
#define MCOS_HWCL_ID_STR                        STR__(MCOS_CFG_HWCL_ID) /**< Get MCOS_CFG_HWCL_ID in string */

/* LCID from core index in local cluster */
/** Returns the LCID of the logical core that specified by index in the self cluster with no parameter check. */
#define MCOS_INDEX2LCID_NC(index)               ((((int32_t)(MCOS_CFG_HWCL_ID) - (int32_t)1) * (int32_t)MCOS_CFG_GLB_CORE_PER_HWCL_MAX) + (int32_t)(index) + (int32_t)1)
/** Returns the LCID of the logical core that specified by index in the self cluster. */
#define MCOS_INDEX2LCID(index)                  mcos_cnv_index_to_lcid(index)

/** Returns the LCID of the logical core that specified by index in the self cluster without parameter checking.
 * note This macro has been obsoleted */
#define MCOS_RCIDX2LCID_NC(rcidx)               MCOS_INDEX2LCID_NC(rcidx)
/** Returns the LCID of the logical core that specified by index in the self cluster.
 * note This macro has been obsoleted */
#define MCOS_RCIDX2LCID(rcidx)                  MCOS_INDEX2LCID(rcidx)

/*
 * LCID from remote HWCLID and core index in remote cluster.
 * May return LCID for nonexistent cores as remote HWCL configuration is unknown.
 */
/** Returns the LCID of the logical core that specified by index in the cluster specified by hwclid  without parameter checking. */
#define MCOS_HWCL_INDEX2LCID_NC(hwclid, index)  ((((int32_t)(hwclid) - (int32_t)1) * (int32_t)MCOS_CFG_GLB_CORE_PER_HWCL_MAX) + (int32_t)(index) + (int32_t)1)
/** Returns the LCID of the logical core that specified by index in the cluster specified by hwclid */
#define MCOS_HWCL_INDEX2LCID(hwclid, index)     mcos_cnv_hwcl_index_to_lcid(hwclid, index)

/** Returns the LCID of the logical core that specified by index in the cluster specified by hwclid  without parameter checking.
 * note This macro has been obsoleted */
#define MCOS_HWCL_RCIDX2LCID_NC(hwclid, rcidx)  MCOS_HWCL_INDEX2LCID_NC(hwclid, rcidx)
/** Returns the LCID of the logical core that specified by index in the cluster specified by hwclid
 * note This macro has been obsoleted */
#define MCOS_HWCL_RCIDX2LCID(hwclid, rcidx)     MCOS_HWCL_INDEX2LCID(hwclid, rcidx)

/* Attribute for the only Global name server */
#define MCOS_NS_ATTR_GLOBAL                     1               /**< Attribute for the only Global name server */

/* Default name server */
#define MCOS_NSID_DEFAULT                       0               /**< Default name server */

/* Type definitions for boolean */
typedef uint8_t mcos_bool_t;                                    /**< The eMCOS Boolean type. Use mcos_false to represent false and mcos_true to represent true. */
#define mcos_false  0                                           /**< Return mcos_bool_t FALSE value */
#define mcos_true   1                                           /**< Return mcos_bool_t TRUE value */

/* Type definitions for ID and error code */
typedef int16_t mcos_id_t;                                      /**< The eMCOS type to indicate an ID such as a thread ID or a logical core ID. */
typedef int16_t mcos_erid_t;                                    /**< The eMCOS type to indicate both an error code and an ID. */
typedef int16_t mcos_er_t;                                      /**< The eMCOS type to indicate an error code. */
typedef int16_t mcos_generic_id_t;                              /**< The eMCOS generic type to indicate an ID and is used as a type to indicate an object ID for a Name Service system call.
                                                                 * The size of this type may be modified for system requirements (16/32/64-bit integer or pointer).
                                                                 * It is implemented as a 16-bit signed integer by default. */

/** System time is shown in a signed 64-bit integer with upper and lower combined. The unit is in milliseconds.
 * The system time represents the number of milliseconds accumulated since 0:00:00 UTC, January 1st, 1970.
 * If system time reaches the maximum value (upper=0x7fffffff, lower=0xffffffff), the time is reset to the minimum value (upper=0x80000000, lower=0)
 * by the next tick to continue counting.
 */
typedef struct
{
    int32_t         upper;                                      /**< Upper 32 bits of system time */
    uint32_t        lower;                                      /**< Lower 32 bits of system time */
} mcos_systime_t;

/** mcos_reltime_t presents relative time in milliseconds.
 * Relative time is used for specifying a relative value from the time that the system call is invoked. */
typedef uint32_t    mcos_reltime_t;

/* Type definitions for char */
typedef uint8_t mcos_char_t;                                    /**< The eMCOS char type */

/** interrupt service parameter */
typedef struct
{
    void            (*entry)(mcos_id_t iid, mcos_uintptr_t param);   /**< Entry function */
    mcos_uintptr_t       param;                                      /**< Argument to pass to the entry function */
} mcos_int_def_t;

/** Thread attribute structure */
typedef struct
{
    uint32_t        attrs[2];                                   /**< Attributes */
    void            *attrp;                                     /**< Pointer to attributes */
    mcos_char_t     name[MCOS_THR_NAME_MAX];                    /**< thread name(optional) */
    uint32_t        attrs2[2];                                  /**< 2nd attributes (only when using the process model) */
    void*           attrp2;                                     /**< 2nd pointer to attributes (only when using the process model) */
} mcos_thr_attr_t;

/** Thread information structure */
typedef struct
{
    void            (*entry)(uint32_t stacd, mcos_uintptr_t exinf); /**< Address of the entry function */
    uint8_t         wupcnt;                                     /**< Wakeup counter */
#if !MCOS_AUTOSAR
    uint8_t         suscnt;                                     /**< Suspend count */
#endif
    uint8_t         state;                                      /**< Thread state */
    uint8_t         migratable;                                 /**< Whether the thread migratable */
    uint8_t         base_priority;                              /**< Base priority */
    uint8_t         current_priority;                           /**< Current priority */
    uint8_t         maxact;                                     /**< Max activation count (used only in eMCOS AUTOSAR) */
    uint8_t         actcnt;                                     /**< Queued activation count (used only in eMCOS AUTOSAR) */
    mcos_uintptr_t       *stackaddr;                                 /**< Start address of the stack */
    uint32_t        stacksize;                                  /**< Stack size */
    mcos_id_t       lcid;                                       /**< Currently assigned logical core ID */
    mcos_uintptr_t       exinf;                                      /**< Extended information */
    mcos_uintptr_t       sp;                                         /**< Current stack pointer */
    uint32_t        sentmsgcnt;                                 /**< The number of messages that are not yet received */
    uint32_t        waitcause;                                  /**< Wait cause of a wait */
} mcos_thr_info_t;

/** Parameter for mcos_cyclic_create() */
typedef struct
{
    void            (*entry)(mcos_id_t csrid, mcos_uintptr_t param); /**< Entry function */
    mcos_reltime_t  cycle;                                      /**< Activation cycle in milliseconds */
    mcos_id_t       lcid;                                       /**< Logical core that the CSR runs on */
    size_t          stacksize;                                  /**< Stack size of the CSR in bytes */
    mcos_uintptr_t       param;                                      /**< Argument to pass to the entry function */
} mcos_cyc_cre_t;

/** Threadpool request data */
typedef struct
{
    mcos_id_t       reqid;                                      /**< Request ID */
    uint8_t         finished;                                   /**< Request finish flag finished: 1 not finished yet: 0 */
    int32_t         (*entry)(mcos_uintptr_t param);                  /**< Entry function of the request */
    mcos_uintptr_t       param;                                      /**< Parameter for the entry function of the request */
    int32_t         ret;                                        /**< Return value of the entry function of the request */
} mcos_tpool_req_t;

/** Request reply message information */
typedef struct
{
    mcos_id_t tid;                                              /**< Thread ID of a request sender */
    uint64_t requestinf;                                        /**< Request extended information */
    const void *request;                                        /**< Request */
    uint32_t requestsz;                                         /**< Request size (in bytes) */
    void *reply;                                                /**< reply message buffer address */
    uint32_t replysz;                                           /**< reply message buffer size (in bytes) */
    uint32_t internal;                                          /**< MCOS internal data for message management */
} mcos_rrmsg_recv_t;

/** Individual heap memory region information */
typedef struct mcos_heap_mem_info mcos_heap_mem_info_t;
struct mcos_heap_mem_info
{
    size_t freesz;                                              /**< Total size of free space (in bytes) */
    uint32_t blkcnt;                                            /**< Maximum free space size (in bytes) */
    size_t maxblksz;                                            /**< Number of segmented blocks */
};

/** Whole heap memory region information */
typedef struct mcos_heap_info mcos_heap_info_t;
struct mcos_heap_info
{
    size_t freesz;                                              /**< Total size of free space (in bytes) */
    size_t maxblksz;                                            /**< Maximum free space size (in bytes) */
    mcos_heap_mem_info_t mk;                                    /**< Information about the heap memory managed by a Microkernel */
    mcos_heap_mem_info_t srv;                                   /**< Information about the heap memory managed by a server */
};

/** Common server register standard message request data. *
 * note
 *  - Field reqid should be MCOS_MSG_REQID_SERVER_REGISTER.
 *  - Field caller should be positive caller TID.
 *  - Server should be able to recognize it no matter what is its native message format.
 *  - Servers must not use value -2 for their reqids.
 */
typedef struct mcos_srvreg_req mcos_srvreg_req_t;
struct mcos_srvreg_req
{
    uint32_t  reqid;                                            /**< Request ID */
    mcos_id_t caller;                                           /**< Thread ID of caller */
    mcos_char_t name[MCOS_THR_NAME_MAX];                        /**< Service name */
};

/** Common server unregister standard message request data. *
 * note
 *  - Field reqid should be MCOS_MSG_REQID_SERVER_UNREGISTER.
 *  - Field caller should be positive caller TID.
 *  - Server should be able to recognize it no matter what is its native message format.
 *  - Servers must not use value -1 for their reqids.
 */
#if !MCOS_AUTOSAR
typedef struct mcos_srvunr_req mcos_srvunr_req_t;
struct mcos_srvunr_req
{
    uint32_t  reqid;                                            /**< Request ID */
    mcos_id_t caller;                                           /**< Thread ID of caller */
    mcos_char_t name[MCOS_THR_NAME_MAX];                        /**< Service name */
};
#endif /* !MCOS_AUTOSAR */
/** Core information */
typedef struct
{
    int32_t tcnt;                                               /**< Number of registered threads */
    mcos_id_t running_tid;                                      /**< ID of the RUNNING thread -1: There is no RUNNING thread */
    mcos_bool_t migration;                                      /**< Whether the core is in migration process or not.
                                                                    mcos_true: Migrating
                                                                    mcos_false: Not migrating */
} mcos_core_info_t;

/** Session-based message session information */
typedef struct
{
    mcos_id_t dest_tid;                                         /**< Thread ID of session connecting destination */
    uint8_t direction;                                          /**< Role of current thread MCOS_SMSG_DIR_RECV (0x00:Receiver) MCOS_SMSG_DIR_SEND (0x01:Sender) */
    uint8_t stat;                                               /**< Current status
                                                                    MCOS_SMSG_STAT_DISCON (0x00: The connection destination session is closed)
                                                                    MCOS_SMSG_STAT_BUF_FREE (0x01: Sender can allocate the send buffer)
                                                                    MCOS_SMSG_STAT_BUF_TX (0x02: Sender has acquired an access right to the send buffer)
                                                                    MCOS_SMSG_STAT_BUF_RX (0x03: Receiver has acquired an access right to the receive buffer) */
} mcos_smsg_info_t;

/** Implemented process of MCOS_INDEX2LCID() */
static inline mcos_id_t mcos_cnv_index_to_lcid(const mcos_id_t index);
/** Implemented process of MCOS_HWCL_INDEX2LCID() */
static inline mcos_id_t mcos_cnv_hwcl_index_to_lcid(const mcos_id_t hwclid, const mcos_id_t index);

static inline mcos_id_t mcos_cnv_index_to_lcid(
    const mcos_id_t index)
{
    return (mcos_id_t)((((int32_t)(index) < (int32_t)0) || ((int32_t)(index) >= (int32_t)MP_CONTROL_CORE_COUNT))
        ? ((int32_t)(MCOS_LCID_INVALID)) : ((int32_t)(MCOS_INDEX2LCID_NC(index))));
}

static inline mcos_id_t mcos_cnv_hwcl_index_to_lcid(
    const mcos_id_t hwclid,
    const mcos_id_t index)
{
    return (mcos_id_t)((((int32_t)index < (int32_t)0) || ((int32_t)index >= (int32_t)MCOS_CFG_GLB_CORE_PER_HWCL_MAX))
        ? (int32_t)(MCOS_LCID_INVALID) : (int32_t)MCOS_HWCL_INDEX2LCID_NC(hwclid, index));
}

/* API functions */

/* Thread attributes */

#if !MCOS_AUTOSAR
/**
 * brief <mcos/mcos.h>
 * param[in]   attr    Pointer to a thread attribute structure
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   attr is NULL.
 * Specification
 * Initializes a thread attribute structure passed by attr.
 */
mcos_er_t mcos_threadattr_init(mcos_thr_attr_t *attr);

/**
 * brief <mcos/mcos.h>
 * param[in]   attr    Pointer to a thread attribute structure
 * param[out]  lcid    Pointer to a destination to store the operation core ID
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   attr is NULL.
                       attr to be set is invalid.
                       Pointer of lcid is NULL.
 * Specification
 * Gets a value of the operation core ID that is set to a thread attribute structure passed by attr.
 * The acquired result is stored at an address indicated by lcid.
 */
mcos_er_t mcos_threadattr_getlcid(const mcos_thr_attr_t *attr, mcos_id_t *lcid);

/**
 * brief <mcos/mcos.h>
 * param[in]   attr    Pointer to a thread attribute structure
 * param[in]   lcid    Operation core ID
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   attr is NULL.
                       lcid to be set is invalid.
 * Specification
 * Sets a value of the operation core ID indicated by lcid to a thread attribute structure passed by attr.
 */
mcos_er_t mcos_threadattr_setlcid(mcos_thr_attr_t *attr, mcos_id_t lcid);

/**
 * brief <mcos/mcos.h>
 * param[in]   attr    Pointer to a thread attribute structure
 * param[out]  pri     Pointer to a destination to store the priority
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   attr is NULL.
                       Pointer of pri is NULL.
 * Specification
 * Gets a priority value that is set to a thread attribute structure passed by attr.
 * The acquired result is stored at an address indicated by pri.
 */
mcos_er_t mcos_threadattr_getpriority(const mcos_thr_attr_t *attr, uint8_t *pri);

/**
 * brief <mcos/mcos.h>
 * param[in]   attr    Pointer to a thread attribute structure
 * param[in]   pri     Priority
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   attr is NULL.
                       attr to be set is invalid.
                       pri to be set is invalid.
 * Specification
 * Sets a priority of the operation core ID indicated by pri to a thread attribute structure passed by attr.
 */
mcos_er_t mcos_threadattr_setpriority(mcos_thr_attr_t *attr, uint8_t pri);

/**
 * brief <mcos/mcos.h>
 * param[in]   attr        Pointer to a thread attribute structure
 * param[out]  stacksize   Pointer to a destination to store the stack size
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   attr is NULL.
                       Pointer of stacksize is NULL.
 * Specification
 * Gets the value of the stack size that is set to a thread attribute structure passed by attr.
 * The acquired result is stored at an address indicated by stacksize.
 */
mcos_er_t mcos_threadattr_getstacksize(const mcos_thr_attr_t *attr, uint32_t *stacksize);

/**
 * brief <mcos/mcos.h>
 * param[in]   attr        Pointer to a thread attribute structure
 * param[in]   stacksize   Stack size
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   attr is NULL.
                       attr to be set is invalid.
                       stacksize to be set is invalid.
 * Specification
 * Sets the value of the stack size indicated by stacksize to a thread attribute structure passed by attr.
 */
mcos_er_t mcos_threadattr_setstacksize(mcos_thr_attr_t *attr, uint32_t stacksize);

/**
 * brief <mcos/mcos.h>
 * param[in]   attr        Pointer to a thread attribute structure
 * param[out]  stackaddr   Pointer to a destination to store the stack area start address
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   attr is NULL.
                       stackaddr is NULL.
 * Specification
 * Gets the value of the stack area top address that is set to a thread attribute structure passed by attr.
 * The acquired result is stored at an address indicated by stackaddr.
 */
mcos_er_t mcos_threadattr_getstackaddr(const mcos_thr_attr_t *attr, void **stackaddr);

/**
 * brief <mcos/mcos.h>
 * param[in]   attr        Pointer to a thread attribute structure
 * param[in]   stackaddr   Stack area start address
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   attr is NULL.
                       attr to be set is invalid.
 * Specification
 * Sets the value of the stack area top address indicated by stackaddr to a thread attribute structure passed by attr.
 */
mcos_er_t mcos_threadattr_setstackaddr(mcos_thr_attr_t *attr, void *stackaddr);

/**
 * brief <mcos/mcos.h>
 * param[in]   attr    Pointer to a thread attribute structure
 * param[out]  name    Pointer to a destination to store the thread name
 * param[in]   len     Size of name
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   attr is NULL.
                       name is NULL.
                       len is 0 or smaller.
 * Specification
 * Gets the thread name that is set to a thread attribute structure passed by attr.
 * The acquired result is stored at an address indicated by name.
 */
mcos_er_t mcos_threadattr_getname(const mcos_thr_attr_t *attr, mcos_char_t *name, int32_t len);

/**
 * brief <mcos/mcos.h>
 * param[in]   attr    Pointer to a thread attribute structure
 * param[in]   name    Thread name
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   attr is NULL.
                       attr to be set is invalid.
                       name is an empty string
                       name contains an invalid character.
 * Specification
 * Sets the thread name indicated by name to a thread attribute structure passed by attr.
 * The names should fit the following conditions.
 *  - The characters in the name string should be alphabetic, numeric, or ".", "_", "-".
 *  - The length should be from 1 to 16 (without NULL terminator).
 */
mcos_er_t mcos_threadattr_setname(mcos_thr_attr_t *attr, const mcos_char_t *name);

/**
 * brief <mcos/mcos.h>
 * param[in]   attr    Pointer to a thread attribute structure
 * param[out]  stdmsg  Pointer to a destination to store the messaging method attribute
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   attr is NULL.
                       Pointer of stdmsg is NULL.
 * Specification
 * Gets the value of the messaging method attribute that is set to a thread attribute structure passed by attr.
 * The acquired result is stored at an address indicated by stdmsg.
 */
mcos_er_t mcos_threadattr_getstdmsg(const mcos_thr_attr_t *attr, mcos_bool_t *std);

/**
 * brief <mcos/mcos.h>
 * param[in]   attr    Pointer to a thread attribute structure
 * param[in]   stdmsg  Messaging method attribute
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   attr is NULL.
                       attr to be set is invalid.
                       name is an empty string
                       name contains an invalid character.
 * Specification
 * Sets the value of the messaging method attribute indicated by stdmsg to a thread attribute structure passed by attr.
 */
mcos_er_t mcos_threadattr_setstdmsg(mcos_thr_attr_t *attr, mcos_bool_t std);

/**
 * brief <mcos/mcos.h>
 * param[in]   attr    Pointer to a thread attribute structure
 * param[out]  inherit Pointer to a destination to store the priority inheritance attribute
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   attr is NULL.
                       Pointer of inherit is NULL.
 * Specification
 * Gets the value of the priority inheritance attribute that is set to a thread attribute structure passed by attr.
 * The acquired result is stored at an address indicated by inherit.
 */
mcos_er_t mcos_threadattr_getpriorityinheritance(const mcos_thr_attr_t *attr, mcos_bool_t *inherit);

/**
 * brief <mcos/mcos.h>
 * param[in]   attr    Pointer to a thread attribute structure
 * param[in]   inherit Priority inheritance attribute
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   attr is NULL.
                       attr to be set is invalid.
 * Specification
 * Sets the value of the priority inheritance attribute indicated by inherit to a thread attribute structure passed by attr.
 */
mcos_er_t mcos_threadattr_setpriorityinheritance(mcos_thr_attr_t *attr, mcos_bool_t inherit);

/**
 * brief <mcos/mcos.h>
 * param[in]   attr    Pointer to a thread attribute structure
 * param[out]  lsid    Pointer to logical space id
 * param[out]  uatb    Pointer to user space page table
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   attr is NULL.
                       Pointer of uatb is NULL.
 * Specification
 * Gets space thread creation attribute.
 */
mcos_er_t mcos_threadattr_getspace(const mcos_thr_attr_t* attr, uint32_t *lsid, void** uatb);

/**
 * brief <mcos/mcos.h>
 * param[in]   attr    Pointer to a thread attribute structure
 * param[in]   lsid    Logical space id
 * param[in]   uatb    User space page table
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   attr is NULL.
                       attr to be set is invalid.
 * Specification
 * Sets space thread creation attribute.
 */
mcos_er_t mcos_threadattr_setspace(mcos_thr_attr_t* attr, uint32_t lsid, void* uatb);

/* Thread management */

/**
 * brief <mcos/mcos.h>
 * param[in]   attr    Thread attribute
 * param[in]   entry   Pointer to the entry function of the thread
 * param[in]   exinf   Extended information of the thread
 * return  When thread creation was successful, a thread ID that is unique in the system is returned.
            If an error occurs, error codes shown below returns.
 * retval  MCOS_EPAR   Contents of attr are invalid.
 * retval  MCOS_EOBJ   A thread with the same name is already created.
 * retval  MCOS_ELIMIT Attempted to create more than the maximum registration number of the Global Name Server.
                       Attempted to create more than the number of threads that may be created.
 * retval  MCOS_ENOMEM Unable to allocate a stack area of the specified size.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Creates a thread according to the specified parameters.
 * The created thread is in the DORMANT state.
 */
mcos_erid_t mcos_thread_create(const mcos_thr_attr_t *attr, void (*entry)(uint32_t stacd, mcos_uintptr_t exinf), mcos_uintptr_t exinf);

/**
 * brief <mcos/mcos.h>
 * param[in]   tid         Thread ID
 * param[in]   start_code  Argument to pass to the thread's entry function
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   tid is invalid as a thread ID.
 * retval  MCOS_ENOEXS The target thread does not exist.
 * retval  MCOS_EOBJ   The target thread is not DORMANT.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Starts a thread specified by tid. When the thread is successfully started, the thread becomes READY.
 * The thread to be started needs be in the DORMANT state.
 */
mcos_er_t mcos_thread_start(mcos_id_t tid, uint32_t start_code);
/**
 * brief <mcos/mcos.h>
 * param[in]   mode    Exit mode
 * return  When the thread is exited successfully, the thread will not be restored from this system call.
            If an error occurs, error codes shown below returns.
 * retval  MCOS_EPAR   mode is invalid.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Exits the thread that called this system call (an invoking thread).
 */
mcos_er_t mcos_thread_exit(uint8_t mode);

/**
 * brief <mcos/mcos.h>
 * param   None
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Makes the thread that called this system call (an invoking thread) sleep.
 * When the invoking thread sleeps, it turns from READY to WAIT.
 * When the sleeping thread is awakened by mcos_thread_wakeup(), it becomes READY again.
 */
mcos_er_t mcos_thread_sleep(void);

/**
 * brief <mcos/mcos.h>
 * param[in]   tid     Thread ID
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   tid is invalid.
 * retval  MCOS_ELIMIT The value of the wakeup counter reached the upper limit.
 * retval  MCOS_ENOEXS The target thread does not exist.
 * retval  MCOS_EOBJ   The target thread is DORMANT.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Wakes up the thread specified by tid.
 * If the target thread is sleeping by invocation of mcos_thread_sleep() and in the WAIT state, the WAIT is canceled and the thread is awakened.
 */
mcos_er_t mcos_thread_wakeup(mcos_id_t tid);

/**
 * brief <mcos/mcos.h>
 * param   None
 * return  The thread ID of the thread that called this system call returns.
            If an error occurs, error code shown below returns.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Returns the ID of the thread that called this system call (the invoking thread).
 */
mcos_erid_t mcos_thread_getid(void);

/**
 * brief <mcos/mcos.h>
 * param[in]   time    Wait time (in milliseconds)
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Waits for the thread that invoked this system call (the invoking thread) for the time specified by time.
 * After the invoking thread waits for the specified time, it turns from READY to WAIT.
 * When the time specified by time has passed, the WAIT thread becomes READY again.
 * Whether the specified time has passed or not is judged by the first time tick after the system time at invocation plus (the value of time + time ticks) has passed.
 */
mcos_er_t mcos_thread_delay(mcos_reltime_t reltime);

/**
 * brief <mcos/mcos.h>
 * param[in]   tid     Thread ID
 * param[out]  name    Buffer to store a thread name
 * param[in]   len     Size of the buffer to store a thread name
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   tid is invalid.
                       name is NULL.
                       len is less than or equal to 0.
 * retval  MCOS_ENOEXS The target thread does not exist.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Gets the name of the thread specified by tid.
 */
mcos_er_t mcos_thread_get_name(mcos_id_t tid, mcos_char_t *name, int32_t len);

/**
 * brief <mcos/mcos.h>
 * param[in]   name    Thread name
 * return  When a matching thread is found on the Global Name Server, the thread ID is returned.
            If an error occurs, error codes shown below returns.
 * retval  MCOS_EPAR   name is NULL.
                       name is  an empty string.
                       name  contains an invalid character.
 * retval  MCOS_ENOEXS The target thread does not exist.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Gets the ID of the thread that has the name specified by name.
 */
mcos_erid_t mcos_thread_getid_by_name(const mcos_char_t *name);

/**
 * brief <mcos/mcos.h>
 * param[in]   tid     Thread ID
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR
 * retval  MCOS_ENOEXS
 * retval  MCOS_ELIMIT
 * Specification
 * Suspend thread
 */
mcos_er_t mcos_thread_suspend(mcos_id_t tid);

/**
 * brief <mcos/mcos.h>
 * param[in]   tid     Thread ID
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR
 * retval  MCOS_ENOEXS
 * retval  MCOS_ELIMIT
 * Specification
 * Resume thread
 */
mcos_er_t mcos_thread_resume(mcos_id_t tid);

/**
 * brief <mcos/mcos.h>
 * param[in]   tid     Thread ID
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR
 * retval  MCOS_ENOEXS
 * retval  MCOS_ELIMIT
 * Specification
 * Forced resume thread
 */
mcos_er_t mcos_thread_fresume(mcos_id_t tid);

/* Time management */

/**
 * brief <mcos/mcos.h>
 * param[in]   currenttime Time to set
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   currenttime is NULL.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Sets the time specified by currenttime to the system's current time.
 * Changing the system's current time with this system call does not affect the elapsed time of the waiting thread due to mcos_thread_delay() or the start time of a CSR.
 * When this system call is issued in an environment where multiple hardware clusters exist, all hardware clusters in the system are set to the same time.
 */
mcos_er_t mcos_time_set(const mcos_systime_t *currenttime);

/**
 * brief <mcos/mcos.h>
 * param[in]   currenttime Time to set
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   currenttime is NULL.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Returns the system's current time to an area passed to currenttime.
 */
mcos_er_t mcos_time_get(mcos_systime_t *currenttime);

/**
 * brief <mcos/mcos.h>
 * param[in]   ccp     Parameter to create a CSR
 * return  The CSR ID returns when the CSR was created.
            If an error occurs, error codes shown below returns.
 * retval  MCOS_EPAR   ccp is NULL.
                       ccp->cycle is 0.
                       ccp->lcid is out of the valid range.
                       ccp->lcid is not the invoking hardware cluster.
 * retval  MCOS_ENOMEM Failed to allocate a stack area from the heap due to insufficient memory.
 * retval  MCOS_ELIMIT Exceeded the number of CSRs that may be created.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Creates a CSR according to the specified parameter.
 */
mcos_erid_t mcos_cyclic_create(const mcos_cyc_cre_t *ccp);

/**
 * brief <mcos/mcos.h>
 * param[in]   csrid   CSR ID
 * return  The CSR ID returns when the CSR was created.
            If an error occurs, error codes shown below returns.
 * retval  MCOS_EOK    The target CSR was successfully deleted.
 * retval  MCOS_EPAR   csrid is out of valid range.
 * retval  MCOS_ENOEXS The target CSR does not exist.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Deletes a CSR (cyclic service routine) specified by csrid.
 */
mcos_er_t mcos_cyclic_delete(mcos_id_t csid);

/* Standard message */

/**
 * brief <mcos/mcos.h>
 * param[in]   tid     Thread ID of the destination thread
 * param[in]   data    Start address of data to be sent
 * param[in]   size    Size of data to be sent (bytes)
 * param[in]   flags   Send mode
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   tid is invalid.
                       flags is invalid.
                       data is NULL when size is not 0.
                       Asynchronous transmission with a message size larger than MCOS_CFG_MSG_SIZE_MAX.
                       Synchronous transmission to the thread itself.
 * retval  MCOS_ENOEXS The target thread does not exist (only for synchronous communication).
 * retval  MCOS_ENOMEM The message management area of the destination is insufficient (only for synchronous communication).
 * retval  MCOS_EOBJ   The target thread is DORMANT (only for synchronous communication).
 * retval  MCOS_ECTX   flags is MCOS_MSG_SEND_SYNC and called from a non-thread context.
 * Specification
 * Sends a standard message to the thread specified by tid.
 */
mcos_er_t mcos_message_send(mcos_id_t tid, const void *data, uint32_t size, uint32_t flags);

/**
 * brief <mcos/mcos.h>
 * param[in]       data    Start address of buffer that stores a received data
 * param[inout]    size    (in)Size of buffer (bytes)
                            (out)Size of received data (bytes)
 * param[in]       flags   Receive mode
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   flags is invalid.
                       size is NULL.
                       data is NULL when *size is not 0.
 * retval  MCOS_ENOMSG MCOS_MSG_RECV_ASYNC was specified and there was no message sent.
 * retval  MCOS_ENOBUF The buffer to store received data passed by size is insufficient.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Receives a standard message that is sent to the thread that invoked this system call (invoking thread).
 */
mcos_er_t mcos_message_receive(void *data, uint32_t *size, uint32_t flags);

/**
 * brief <mcos/mcos.h>
 * param[in]   tid     Thread ID of a destination
 * param[in]   command Command
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   tid is invalid.
                       command is invalid.
 * retval  MCOS_ENOEXS The target thread does not exist.
 * Specification
 * Sends a command to the thread specified by tid. This system call can be called by an ISR.
 * When MCOS_MSG_CTL_RELWAI is specified to command, this system call forcibly releases the wait by the following system calls.
 *  - mcos_rrmessage_send()
 *  - mcos_rrmessage_receive()
 */
mcos_er_t mcos_message_control(mcos_id_t tid, uint32_t command);

/* Fast message */

/**
 * brief <mcos/mcos.h>
 * param[in]   tid     Thread ID of the destination thread
 * param[in]   data    Start address of data to be sent
 * param[in]   size    Size of data to be sent in bytes
 * param[in]   flags   Transmission mode
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   tid is invalid.
                       flags is invalid.
                       size is invalid.
                       data is NULL when size is not 0.
                       data is not aligned in words.
                       size is not aligned in words.
                       size is larger than MCOS_CFG_MSG_SIZE_MAX.
                       Logical core ID is specified and the interrupt ID is not specified.
                       Logical core ID is not specified and the interrupt ID is specified.
                       A thread that runs in a different cluster is specified to tid (dependent on each BSP).
 * retval  MCOS_ENOMEM Insufficient message management area.
 * retval  MCOS_EOBJ   The target thread is a migratable thread.
 * retval  MCOS_ECTX   Invoked from an invalid context.
 * Specification
 * Sends a fast message to the thread specified by tid.
 * The sent message is received when the destination thread invokes mcos_fmessage_receive().
 */
mcos_er_t mcos_fmessage_send(mcos_id_t tid, const void *data, uint32_t size, uint32_t flags);

/**
 * brief <mcos/mcos.h>
 * param[in]       data    Start address of buffer that stores a received data
 * param[inout]    size    (in)Size of buffer (bytes)
                            (out)Size of received data (bytes)
 * param[in]       flags   Receive mode
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   tid is invalid.
                       flags is invalid.
                       size is NULL.
                       data is NULL when *size is not 0.
                       data is not aligned in words.
                       *size is not aligned in words.
 * retval  MCOS_ENOMSG MCOS_FMSG_RECV_ASYNC was specified and there was no sent message.
 * retval  MCOS_ENOBUF Invoked from migratable thread.
 * retval  MCOS_ECTX   The size of buffer to store the reception data is insufficient.
 * Specification
 * Receives a message that is sent by mcos_fmessage_send() to the thread that invoked this system call (invoking thread).
 */
mcos_er_t mcos_fmessage_receive(void *data, uint32_t *size, uint32_t flags);

/* Interrupt management */

/**
 * brief <mcos/mcos.h>
 * param[in]   iid     Interrupt ID
 * param[in]   idp     Parameter to create an ISR
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   An interrupt number used by the Microkernel was specified.
                       An interrupt number not supported by the BSP was specified.
                       idp is NULL.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Registers an entry function specified by idp (a parameter for ISR creation) to an interrupt specified by iid.
 * The function is created as an ISR.
 */
mcos_er_t mcos_interrupt_define(mcos_id_t iid, const mcos_int_def_t *idp);

/**
 * brief <mcos/mcos.h>
 * param[in]   iid     Interrupt ID
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   An interrupt ID that is not supported by the BSP was specified to iid.
 * retval  MCOS_ENOSPT An interrupt ID that cannot be disabled was specified to iid.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Disables the interrupt specified by iid on the self core.
 */
mcos_er_t mcos_interrupt_disable(mcos_id_t iid);

/**
 * brief <mcos/mcos.h>
 * param[in]   iid     Interrupt ID
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   An interrupt ID that is not supported by the BSP was specified to iid.
 * retval  MCOS_ENOSPT An interrupt ID that cannot be enabled was specified to iid.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Enables the interrupt specified by iid on the self core.
 */
mcos_er_t mcos_interrupt_enable(mcos_id_t iid);

/**
 * brief <mcos/mcos.h>
 * param[in]   iid     Interrupt ID
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   An interrupt ID that is not supported by the BSP was specified to iid.
 * retval  MCOS_ENOSPT An interrupt ID that cannot be enabled was specified to iid.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Clears the requests of the interrupt specified by iid on the self core.
 */
mcos_er_t mcos_interrupt_clear(mcos_id_t iid);

/* Server management */

/**
 * brief <mcos/mcos.h>
 * param[in]   name    Server name
 * param[in]   tid     Server thread ID
 * param[in]   nsid    Name Server ID
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   name is NULL.
                       name is an empty string.
                       name contains an invalid character.
                       tid is invalid or the ID of the thread itself.
                       nsid is invalid.
 * retval  MCOS_ENOEXS The server thread does not exist.
 * retval  MCOS_EOBJ   A server with the same name is already created.
                       The server thread that is specified by tid is in the DORMANT state.
 * retval  MCOS_ELIMIT Attempted to create more than the maximum registration number of the master Name Cache.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Associates the server that has the service name that is specified by name with the server thread that is specified by tid.
 * It also registers the service name and server thread ID to the Name Server that is specified by nsid.
 * The server name must meet the following criteria:
 *  - Composed of alphanumeric characters, ".", "_", and "-"
 *  - 1 to 16 characters long
 */
mcos_er_t mcos_server_register(const mcos_char_t *name, mcos_id_t tid, mcos_id_t nsid);

/**
 * brief <mcos/mcos.h>
 * param[in]   name    Service name
 * param[in]   nsid    Name Server ID
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   name is NULL.
                       name is an empty string.
                       name contains an invalid character.
                       nsid is invalid.
                       Invoked from the server thread.
 * retval  MCOS_ENOEXS The server with the specified name does not exist.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Deletes the server specified by name and releases the association of the server thread.
 * Also, it unregisters the service name and the server thread ID from the Name Server that is specified by nsid.
 */
mcos_er_t mcos_server_unregister(const mcos_char_t *name, mcos_id_t nsid);

/**
 * brief <mcos/mcos.h>
 * param[in]   rtid    Caller's thread ID
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   rtid is invalid.
 * retval  MCOS_EOBJ   rtid is set to the self thread ID.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Responds to a server generation request or a delete request.
 */
mcos_er_t mcos_server_reply(mcos_id_t rtid);

/**
 * brief <mcos/mcos.h>
 * param[in]   name    Service name
 * param[in]   nsid    Name Server ID
 * return  The thread ID of the server specified by name returns.
            If an error occurs, error codes shown below returns.
 * retval  MCOS_EPAR   name is NULL.
                       name is an empty string.
                       contains an invalid character.
                       nsid is invalid.
 * retval  MCOS_ENOEXS The server with the specified name does not exist.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Gets the server thread ID of the server specified by name.
 */
mcos_erid_t mcos_server_getid(const mcos_char_t *name, mcos_id_t nsid);

/* Name service */

/**
 * brief <mcos/mcos.h>
 * param[in]   name    Object name
 * param[in]   id      Object ID
 * param[in]   nsid    Name Server ID
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   name is NULL.
                       name is an empty string.
                       contains an invalid character.
                       nsid is invalid.
                       id is 0 or less.
 * retval  MCOS_ELIMIT The number of registrations in the Name Server reached the limit.
 * retval  MCOS_EOBJ   An object with the same name is already registered.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Registers the name and id as the associated objects to the Name Server that specifies nsid.
 */
mcos_er_t mcos_name_register(const mcos_char_t *name, mcos_generic_id_t id, mcos_id_t nsid);

/**
 * brief <mcos/mcos.h>
 * param[in]   name    Object name
 * param[in]   nsid    Name Server ID
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   name is NULL.
                       name is an empty string.
                       contains an invalid character.
                       nsid is invalid.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Deletes an object name and its ID from the Name Server that specifies nsid.
 */
mcos_er_t mcos_name_unregister(const mcos_char_t *name, mcos_id_t nsid);

/**
 * brief <mcos/mcos.h>
 * param[in]   name    Object name
 * param[in]   nsid    Name Server ID
 * return  When the same name as the string specified to name is registered, its ID is returned.
            If an error occurs, error code shown below returns.
 * retval  MCOS_EPAR   name is NULL.
                       name is an empty string.
                       contains an invalid character.
                       nsid is invalid.
 * retval  MCOS_ENOEXS name is not registered to the Name Server.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Searches for a name registered to the Name Server and returns the name's ID.
 */
mcos_generic_id_t mcos_name_lookup(const mcos_char_t *name, mcos_id_t nsid);

/* Thread pool management */

/**
 * brief <mcos/mcos.h>
 * param[in]   tcnt    Number of threads
 * param[in]   tppri   Thread priority
 * param[in]   attr    Attribute
 * return  When thread pool creation was successful, a thread pool ID that is unique in the system is returned.
            If an error occurs, error codes shown below returns.
 * retval  MCOS_EPAR   tcnt is invalid.
                       tppri is invalid.
                       attr is invalid.
 * retval  MCOS_EOBJ   A thread pool with the same thread pool owner is already created.
 * retval  MCOS_ELIMIT Attempted to create more than the number of thread pools that may be created.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Creates a thread pool that has request execution threads of the number specified by tcnt.
 * The request execution threads will run with a priority specified by tppri.
 */
mcos_erid_t mcos_threadpool_create(uint32_t tcnt, uint8_t tppri, uint8_t attr);

/**
 * brief <mcos/mcos.h>
 * param[in]   tpid    Thread pool ID
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   tpid is invalid.
 * retval  MCOS_EOBJ   Not all request execution results were received.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Deletes the thread pool specified by tpid.
 */
mcos_er_t mcos_threadpool_delete(mcos_id_t tpid);

/**
 * brief <mcos/mcos.h>
 * param[in]       tpid    Thread pool ID
 * param[in]       mode    Mode
 * param[in]       reqcnt  Number of requests
 * param[inout]    req     Array of a request structure
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   tpid is invalid.
                       mode is invalid.
                       reqcnt is 0.
                       req is NULL.
 * retval  MCOS_EOBJ   The thread pool state is invalid.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Issues a request to the thread pool specified by tpid.
 */
mcos_er_t mcos_threadpool_execute(mcos_id_t tpid, uint8_t mode, uint8_t reqcnt, mcos_tpool_req_t *req);

/**
 * brief <mcos/mcos.h>
 * param[in]       tpid    Thread pool ID
 * param[in]       mode    Mode
 * param[in]       reqcnt  Number of requests
 * param[inout]    req     Array of a request structure
 * return  When this system call is executed normally, it returns the number of unfinished requests among the specified requests.
            If an error occurs, error codes shown below returns.
 * retval  MCOS_EPAR   tpid is invalid.
                       mode is invalid.
                       reqcnt is 0.
                       req is NULL.
 * retval  MCOS_EOBJ   The thread pool state is invalid.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Waits for execution completion of the requests, specified by req, that are issued to the thread pool specified by tpid.
 */
mcos_erid_t mcos_threadpool_wait(mcos_id_t tpid, uint8_t mode, uint8_t reqcnt, mcos_tpool_req_t *req);

/**
 * brief <mcos/mcos.h>
 * param[in]   tpid    Thread pool ID
 * return  When this system call is executed normally, it returns the number of assigned request execution threads.
            If an error occurs, error codes shown below returns.
 * retval  MCOS_EPAR   tpid is invalid.
 * retval  MCOS_EOBJ   The thread pool state is invalid.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Assigns a request execution thread to the thread pool specified by tpid to get ready to receive a request.
 * A request execution thread is assigned from a cluster to which the operation core of an owner thread belongs.
 */
mcos_erid_t mcos_threadpool_activate(mcos_id_t tpid);

/**
 * brief <mcos/mcos.h>
 * param[in]   tpid    Thread pool ID
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   tpid is invalid.
 * retval  MCOS_EOBJ   The thread pool state is invalid.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Deactivates the thread pool specified by tpid to become unable to receive a request.
 */
mcos_er_t mcos_threadpool_deactivate(mcos_id_t tpid);

/* Request-reply model message */

/**
 * brief <mcos/mcos.h>
 * param[in]   tid         Thread ID of a destination
 * param[in]   requestinf  Request message extended information
 * param[in]   request     Start address of request message storage area
 * param[in]   requestsz   Request message size (in bytes)
 * param[out]  replyinf    Reply message extended information storage area
 * param[out]  reply       Start address of reply message storage area
 * param[in]   replysz     Reply message storage area size (in bytes)
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   tid is invalid.
                       request is NULL when requestsz is not 0.
                       reply is NULL when replysz is not 0.
                       Synchronous transmission to the thread itself.
 * retval  MCOS_ENOEXS The target thread does not exist.
 * retval  MCOS_EOBJ   The target thread is DORMANT or exits before sending a reply.
 * retval  MCOS_EINTR  The system call is interrupted.
 * retval  MCOS_ELIMIT requestsz is too large in the asynchronous transmission of a request.
 * retval  MCOS_ENOMEM Failed to send the request due to insufficient memory.
 * retval  MCOS_ECTX   Invoked from an invalid context.
 * Specification
 * Sends a request to the thread specified by tid (a receiver thread, hereafter).
 * It waits to receive a reply from the receiver thread after sending the request.
 * If 0 is specified to replysz and NULL is specified to replyinf, this system call returns immediately after sending the request, without waiting for a reply from the receiver thread.
 */
mcos_er_t mcos_rrmessage_send(
    mcos_id_t tid,
    uint64_t requestinf,
    const void *request,
    uint32_t requestsz,
    uint64_t *replyinf,
    void * reply,
    uint32_t replysz);

/**
 * brief <mcos/mcos.h>
 * param[out]  recv    Request management information storage area
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   recv is NULL.
 * retval  MCOS_EINTR  The system call is interrupted.
 * retval  MCOS_ECTX   Invoked from an invalid context.
 * Specification
 * Waits for the reception of a request that is sent by mcos_rrmessage_send().
 * After the request is received, this system call returns to the invoker.
 */
mcos_er_t mcos_rrmessage_receive(mcos_rrmsg_recv_t *recv);

/**
 * brief <mcos/mcos.h>
 * param[in]   replyinf    Reply message extended information
 * param[in]   replysz     Reply message size (in bytes)
 * param[in]   recv        Request management information
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   recv is NULL.
                       replysz is greater than recv->replysz.
 * retval  MCOS_ENOMEM Failed to send the reply due to insufficient memory.
 * retval  MCOS_ECTX   Invoked from an invalid context.
 * Specification
 * Sends a reply to a request received by mcos_rrmessage_receive().
 * This system call needs to be invoked for a request received by mcos_rrmessage_receive().
 */
mcos_er_t mcos_rrmessage_reply(uint64_t replyinf, uint32_t replysz, const mcos_rrmsg_recv_t *recv);

/**
 * brief <mcos/mcos.h>
          <mcos/mcos_heap_id.h>
 * param[in]   heapid  Heap ID
 * param[in]   size    Memory size to be allocated (in bytes)
 * param[out]  addr    Pointer to an area to return a start address of an allocated memory
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   addr is NULL.
                       size is 0.
                       A heap that cannot be allocated from the self core is specified.
 * retval  MCOS_ENOEXS A non-existent heap ID is specified.
 * retval  MCOS_ENOMEM Unable to allocate requested memory.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Allocates an area of size from memory or a memory group specified by heapid.
 */
mcos_er_t mcos_heap_allocate (
    mcos_id_t heapid,
    size_t size,
    void ** addr);

/**
 * brief <mcos/mcos.h>
 * param[in]   addr    Start address of memory to be returned
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Returns a memory area specified by addr.
 * addr needs to be specified with an address of the memory allocated by mcos_heap_allocate().
 */
mcos_er_t mcos_heap_free (
    void * addr);

/**
 * brief <mcos/mcos.h>
          <mcos/mcos_heap_id.h>
 * param[in]   heapid  Heap ID
 * param[in]   nblk    Number of memory blocks to be allocated
 * param[out]  addr    Pointer to an area to return a start address of an allocated memory
 * return  When heap memory allocation was successful, a heap ID of the allocated memory is returned.
            If an error occurs, error codes shown below returns.
 * retval  MCOS_EPAR   addr is NULL.
                       nblk is 0.
 * retval  MCOS_ENOEXS A non-existent heap ID is specified.
 * retval  MCOS_ENOMEM Unable to allocate requested memory.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 *  Allocates an area of nblk blocks from a heap specified by heapid.
 * For cluster local memory or global local memory, memory is requested to the heap management server directly without going through the Microkernel.
 * For core local memory, memory is requested to the Microkernel.
 * The default size of 1 block is different by each BSP. The size can be specified by the configuration MCOS_CFG_HEAP_BLOCKSIZE.
 * The address of an allocated memory area is stored in an area specified by addr, and the heap ID of the allocated memory is returned.
 */
mcos_erid_t mcos_heap_allocate_block (
    mcos_id_t heapid,
    uint32_t nblk,
    void ** addr);

/**
 * brief <mcos/mcos.h>
          <mcos/mcos_heap_id.h>
 * param[in]   heapid  Heap ID
 * param[in]   addr    Start address of the memory block to be returned
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   addr is invalid.
 * retval  MCOS_ENOEXS A non-existent heap ID is specified.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Returns the memory area at the address addr in the memory specified by heapid.
 * Generally, the heapid value is obtained from the return value of mcos_heap_allocate_block().
 */
mcos_er_t mcos_heap_free_block (
    mcos_id_t heapid,
    void * addr);

/**
 * brief <mcos/mcos.h>
          <mcos/mcos_heap_id.h>
 * param[in]   heapid      Heap ID
 * param[out]  heap_info   Pointer to a structure for return a heap status
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   heap_info is NULL.
                       A heap that cannot be allocated from the self core was specified.
 * retval  MCOS_ENOEXS A non-existent heap ID is specified.
 * retval  MCOS_ENOSPT A heap that cannot be accessed from the self core was specified by the heap ID.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * References the status of memory specified by heapid, and returns information such as total size of free space in heap memory in heap_info.
 * Information about the heap that is managed by the Microkernel or the server includes the total size of free spaces, the size of the largest free space, and the number of fragmented blocks.
 */
mcos_er_t mcos_heap_get_info (
    mcos_id_t heapid,
    mcos_heap_info_t * heap_info);

/* Core management */

/**
 * brief <mcos/mcos.h>
 * param[in]   lcid        Logical core ID
 * param[out]  core_info   Pointer to core reference information
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   lcid is invalid.
                       core_info  is NULL.
 * retval  MCOS_ENOEXS The target core does not exist.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * References the state of the core specified by lcid and returns information such as the number of registered threads to core_info.
 */
mcos_er_t mcos_core_get_info(
    mcos_id_t lcid,
    mcos_core_info_t *core_info);

/* Thread management */

/**
 * brief <mcos/mcos.h>
 * param[in]   tid         Thread ID
 * param[out]  thread_info Pointer to thread reference information
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   tid is invalid.
                       thread_info is NULL.
 * retval  MCOS_ENOEXS The target thread does not exist.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Gets information about the thread specified by tid. An area indicated by thread_info needs to be allocated by the invoker of this system call.
 */
mcos_er_t mcos_thread_get_info(mcos_id_t tid, mcos_thr_info_t *thread_info);

/* Partition management */

/**
 * brief <mcos/mcos.h>
 * param[in]   partid      Thread ID
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   partid is invalid.
 * retval  MCOS_ENOSPT Not supported.
 * Specification
 * Makes the partition designated by partid reboot.
 * This system call does not wait for the completion of the reboot operation.
 * After the reboot starts, the function immediately returns.
 * Because of that, MCOS_EOK will be returned even if an error occurs during the reboot process.
 */
mcos_er_t mcos_partition_reboot(mcos_id_t partid);

/* Memory check */

/**
 * brief <mcos/mcos.h>
          <mcos/mcos_heap_id.h>
 * param[in]   tid     Thread ID
 * param[in]   type    Access type
 * param[in]   addr    Memory address to be checked
 * param[in]   size    Memory size to be checked
 * retval  MCOS_EOK    The memory space can be accessed from the thread.
 * retval  MCOS_EPAR   tid is invalid.
                       type is invalid.
                       addr is 0.
 * retval  MCOS_ENOEXS The target thread does not exist.
 * retval  MCOS_EMACV  The memory space cannot be accessed from the thread.
                       tid is for a thread that is in a remote hardware cluster.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Checks if the memory space specified by addr and size can be accessed from the thread of tid.
 * If it is accessible, MCOS_EOK will return, otherwise MCOS_EMACV will return.
 */
mcos_er_t mcos_memory_check_by_tid(
    mcos_id_t tid,
    uint8_t type,
    void *addr,
    uint32_t size);

/* Session-based message */

/**
 * brief <mcos/mcos.h>
 * param[in]   tid     Receiver thread ID
 * param[in]   buffer  Send buffer address
 * param[in]   size    Send buffer size (in bytes)
 * return  When the session open succeeds, this system call returns a session ID.
            If an error occurs, error codes shown below returns.
 * retval  MCOS_EPAR   tid is invalid as a thread ID.
                       buffer is NULL.
                       size is 0.
 * retval  MCOS_ENOEXS The target thread does not exist.
 * retval  MCOS_ELIMIT The number of open sessions per thread reached the maximum number.
                       Hardware resources for the session cannot be secured.
 * retval  MCOS_ENOMEM Memory for the receiver side is short.
 * retval  MCOS_ENOBUF size is larger than the size specified by the receiver side.
 * retval  MCOS_EOBJ   The target thread is DORMANT.
                       The target thread is the invoking thread.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Opens a session between the tid thread and the caller thread, and enables sending session-based messages.
 * The caller thread transits to the WAIT state until the session is opened at the receiver side.
 */
mcos_erid_t mcos_smessage_tx_open(mcos_id_t tid, const void *buffer, uint32_t size);

/**
 * brief <mcos/mcos.h>
 * param[in]   ssid    Session ID
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   ssid is invalid as a session ID.
 * retval  MCOS_EOBJ   Caller does not have an access right to the send buffer.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Closes a session of ssid.
 * This system call does not wait for the session close on the receiver side.
 * This system call may be invoked while the invoking thread has an access right to the send buffer, or after the receiver thread closes the session.
 * The period when the sender thread has the access right to the buffer is from completion of mcos_smessage_tx_allocate() to the call of mcos_smessage_tx_send().
 */
mcos_er_t mcos_smessage_tx_close(mcos_id_t ssid);

/**
 * brief <mcos/mcos.h>
 * param[in]   ssid    Session ID
 * param[in]   flags   Allocation mode
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_ENOMSG The receiver thread has the access right to the receive buffer (only for asynchronous mode).
 * retval  MCOS_EPAR   ssid is invalid as a session ID.
                       flags is invalid.
 * retval  MCOS_EOBJ   The session has already been closed.
                       Caller already has the access right to the send buffer.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Acquires an access right to the send buffer of the session specified by ssid.
 * This system call needs to be invoked before the sender thread can write data to the buffer.
 * The sender thread may not modify data in the buffer unless by the invocation of this system call.
 * The data transferred would be unstable if the sender thread modifies the data without the access right.
 */
mcos_er_t mcos_smessage_tx_allocate(mcos_id_t ssid, uint32_t flags);

/**
 * brief <mcos/mcos.h>
 * param[in]   ssid    Session ID
 * param[in]   flags   Allocation mode
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   ssid is invalid as a session ID.
                       flags is invalid.
 * retval  MCOS_EOBJ   The session has already been closed.
                       Caller already has the access right to the send buffer.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Sends the data in the send buffer of the session specified by ssid as a session-based message.
 * Before this system call is invoked, acquisition of the access right to the send buffer by calling mcos_smessage_tx_allocate() is required.
 */
mcos_er_t mcos_smessage_tx_send(mcos_id_t ssid, uint32_t flags);

/**
 * brief <mcos/mcos.h>
 * param[out]      buffer  Receive buffer address
 * param[inout]    size    Receive buffer size (in bytes)
 * return  When the session open succeeds, this system call returns a session ID.
            If an error occurs, error codes shown below returns.
 * retval  MCOS_EPAR   buffer is NULL.
                       size is NULL.
                       *size is 0.
 * retval  MCOS_ENOEXS The target thread does not exist.
 * retval  MCOS_ELIMIT A value of the session open counter reaches the upper limit.
                       Hardware resources for the session cannot be secured.
 * retval  MCOS_ENOMEM Memory for the receive buffer is short (depending on BSP).
 * retval  MCOS_ENOBUF size is smaller than the size which is specified by sender.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Opens a session for the receiver side and enables receiving session-based messages.
 * This system call turns the invoking thread to WAIT until one of the sender threads calls mcos_smessage_tx_open() and a session is estimated.
 */
mcos_erid_t mcos_smessage_rx_open(void **buffer, uint32_t *size);

/**
 * brief <mcos/mcos.h>
 * param[in]   ssid    Session ID
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   ssid is invalid as a session ID.
 * retval  MCOS_EOBJ   Caller does not have an access right to the receive buffer.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Closes the receiver side session specified by ssid.
 * This system call doesn't wait for the closing session of the sender side.
 * This system call may be invoked while the invoking thread has an access right to the receive buffer, or after the sender thread closes the session.
 * The period when the invoking thread has the access right is from completion of mcos_smessage_rx_receive() to the call of mcos_smessage_rx_free().
 */
mcos_er_t mcos_smessage_rx_close(mcos_id_t ssid);

/**
 * brief <mcos/mcos.h>
 * param[in]   ssid    Session ID
 * param[in]   flags   Receipt mode
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   ssid is invalid as a session ID.
                       flags is invalid.
 * retval  MCOS_ENOMSG No session-based message has been sent yet (only for asynchronous mode).
 * retval  MCOS_EOBJ   The session has already been closed.
                       Caller has not released the access right to the receive buffer.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Receives the session-based-message of the session specified by ssid and acquire an access right to the receive buffer.
 * The caller does not need to secure the storing buffer for received data, as the data is stored in the receive buffer designated in mcos_smessage_rx_open() automatically.
 * The data in the receive buffer may only be referred in the period
 * between the receipt of the message and the release of the access right to the receive buffer by calling mcos_smessage_rx_free().
 * If the buffer is referred out of the period, the data acquired would be unstable.
 */
mcos_er_t mcos_smessage_rx_receive(mcos_id_t ssid, uint32_t flags);

/**
 * brief <mcos/mcos.h>
 * param[in]   ssid    Session ID
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   ssid is invalid as a session ID.
 * retval  MCOS_EOBJ   The session has already been closed.
                       Caller has not received a message in the session.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Releases an access right to the receive buffer of the session specified by ssid.
 * When receiving a session-based message in mcos_smessage_rx_receive(), this system call needs to be invoked if the receiver thread complete the referring to the data in the receive buffer.
 * Modification of data in the send buffer, sending, and receipt of a new message may not be executed until this system call is called.
 * The receiver thread may not refer data in the receive buffer after the invocation of this system call.
 * In such a case, the data acquired would be unstable.
 */
mcos_er_t mcos_smessage_rx_free(mcos_id_t ssid);

/**
 * brief <mcos/mcos.h>
 * param[in]   ssid        Session ID
 * param[out]  smsg_info   Session-based message information
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   ssid is invalid as a session ID.
                       smsg_info is NULL.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Acquires information of the session specified by ssid.
 * This system call may be invoked only by the thread which called mcos_smessage_tx_open() or mcos_smessage_rx_open() of the session ssid.
 */
mcos_er_t mcos_smessage_get_info(mcos_id_t ssid, mcos_smsg_info_t *smsg_info);
#endif /* #if !MCOS_AUTOSAR */

/* Distributed Shared Memory */

typedef uint32_t mcos_dsm_create_attr_t;                        /**< DSM creation attribute type */
typedef uint32_t mcos_dsm_attach_mode_t;                        /**< DSM section attach mode type */

/** DSM creation parameter structure */
typedef struct {
    uint32_t size;                                              /**< size */
    mcos_dsm_create_attr_t attr;                                /**< DSM creation attribute */
} mcos_dsm_create_t;

/** DSM section attach parameter structure */
typedef struct {
    uint32_t offset;                                            /**< offset */
    uint32_t size;                                              /**< size */
    mcos_dsm_attach_mode_t mode;                                /**< DSM section attach mode */
} mcos_dsm_attach_t;

/** DSM information structure */
typedef struct {
    uint32_t size;                                              /**< size */
    mcos_dsm_create_attr_t attr;                                /**< DSM creation attribute */
} mcos_dsm_info_t;

/* DSM creation attribute */
#define MCOS_DSM_CREATE_ATTR_NONE       0x00000000              /**< attribute: none */

/* DSM attach mode */
#define MCOS_DSM_ATTACH_ACM_READ        0x00000001              /**< access mode: read */
#define MCOS_DSM_ATTACH_ACM_WRITE       0x00000002              /**< access mode: write */
#define MCOS_DSM_ATTACH_ACM_UPDATE      0x00000003              /**< access mode: update (read and write) */
#define MCOS_DSM_ATTACH_BLM_NONBLOCK    0x00000000              /**< blocking mode: non-blocking */
#define MCOS_DSM_ATTACH_BLM_BLOCK       0x00000004              /**< blocking mode: blocking */

#if !MCOS_AUTOSAR
/**
 * brief <mcos/mcos.h>
 * param[in]   create  Pointer to a DSM creation structure
 * return  When DSM creation was successful, a DSM ID that is unique in the system is returned.
            If an error occurs, error codes shown below returns.
 * retval  MCOS_EPAR   Contents of attr are invalid.
 * retval  MCOS_ELIMIT Attempted to create more than the number of DSMs that may be created.
 * retval  MCOS_ENOMEM Unable to allocate a DSM area of the specified size.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Creates a DSM according to the specified parameters.
 */
mcos_erid_t mcos_dsm_create(const mcos_dsm_create_t *create);

/**
 * brief <mcos/mcos.h>
 * param[in]   dsmid   DSM ID
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   dsmid is out of valid range.
 * retval  MCOS_ENOEXS The target DSM does not exist.
 * retval  MCOS_EOBJ   The target DSM is attached.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Deletes a DSM specified by dsmid.
 */
mcos_er_t mcos_dsm_delete(mcos_id_t dsmid);

/**
 * brief <mcos/mcos.h>
 * param[in]   dsmid   DSM ID
 * param[in]   attach  The parameters for attaching the DSM section
 * param[out]  ptr     top address of the attached DSM section
 * return  When the DSM section was successfully attached, a DSM section ID that is unique in the system is returned.
           If an error occurs, error codes shown below returns.
 * retval  MCOS_EPAR   dsmid is out of valid range. Contents of attach are invalid. ptr is NULL.
 * retval  MCOS_ELIMIT Attempted to attach more than the number of DSM Sections that may be attached. Corresponds to BSP-dependent limitations.
 * retval  MCOS_ENOMEM Unable to allocate a DSM Section area of the specified size.
 * retval  MCOS_ENOEXS The target DSM does not exist.
 * retval  MCOS_EOBJ   The access mode is in conflict.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Attaches a specified area in the DSM as a DSM section.
 */
mcos_erid_t mcos_dsm_attach(mcos_id_t dsmid, const mcos_dsm_attach_t *attach, void **ptr);

/**
 * brief <mcos/mcos.h>
 * param[in]   dsmscid DSM section ID
 * param[in]   offset  Offset position from the top of the DSM
 * param[inout]    ptr     top address of the attached DSM section
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   dsmscid is out of valid range. offset is invalid. ptr is NULL.
 * retval  MCOS_ENOEXS The target DSM does not exist.
 * retval  MCOS_EOBJ   The access mode is in conflict.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Changes offset of an attached DSM section.
 */
mcos_er_t mcos_dsm_reattach(mcos_id_t dsmscid, uint32_t offset, void **ptr);

/**
 * brief <mcos/mcos.h>
 * param[in]   dsmscid DSM section ID
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   dsmscid is out of valid range.
 * retval  MCOS_ENOEXS The target DSM does not exist.
 * retval  MCOS_EOBJ   The target DSM is not attached.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Detaches a specified DSM section.
 */
mcos_er_t mcos_dsm_detach(mcos_id_t dsmscid);

/**
 * brief <mcos/mcos.h>
 * param[in]   dsmid   DSM ID
 * param[out]  info    DSM information
 * retval  MCOS_EOK    Normal completion.
 * retval  MCOS_EPAR   dsmid is out of valid range.
 * retval  MCOS_ENOEXS The target DSM does not exist.
 * retval  MCOS_ECTX   Called from a non-thread context.
 * Specification
 * Gets the information of a specified DSM.
 */
mcos_er_t mcos_dsm_get_info(mcos_id_t dsmid, mcos_dsm_info_t *info);

/* lmalloc */

/**
 * brief <mcos/mcos.h>
 * param[in]   size    Size to allocate
 * retval  "!= 0"  Start address of allocated memory.
 * retval  0       Error
 * Specification
 * Allocates the size amount of core local memory.
 * It is the same as mcos_heap_allocate() with HEAP_LMALLOC specified to heapid.
 */
void * lmalloc (size_t size);

/* lfree */

/**
 * brief <mcos/mcos.h>
 * param[in]   ptr     Start address of memory to be returned
 * return  None.
 * Specification
 * Returns the memory area specified by ptr. ptr needs to be specified with the address acquired by lmalloc().
 * If ptr is NULL, nothing will be executed.
 */
void lfree (void * addr);

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

/**
 * brief <mcos/mcos.h>
 * param[in]   attr    Pointer to attributes struct
 * param[in]   basic   Pointer to boolean storage
 * return  Error code
 * Specification
 * Gets priority thread creation attribute.
 * note
 * Available in eMCOS AUTOSAR only.
 */
mcos_er_t mcos_threadattr_getbasicthread(const mcos_thr_attr_t *attr, mcos_bool_t *basic);

/**
 * brief <mcos/mcos.h>
 * param[in]   attr    Pointer to attributes struct
 * param[in]   basic   Boolean value (true means basic thread, else extended)
 * return  Error code
 * Specification
 * Sets std delete msg server thread creation attribute.
 * note
 * Available in eMCOS AUTOSAR only.
 */
mcos_er_t mcos_threadattr_setbasicthread(mcos_thr_attr_t *attr, mcos_bool_t basic);

/**
 * brief <mcos/mcos.h>
 * param[in]   attr    Pointer to attributes struct
 * param[in]   shared  Pointer to boolean storage
 * return  Error code
 * Specification
 * Gets priority thread creation attribute.
 * note
 * Available in eMCOS AUTOSAR only.
 */
mcos_er_t mcos_threadattr_getsharedstack(const mcos_thr_attr_t *attr, mcos_bool_t *shared);

/**
 * brief <mcos/mcos.h>
 * param[in]   attr    Pointer to attributes struct
 * param[in]   shared  Boolean value (true means shared stack, else private)
 * return  Error code
 * Specification
 * Sets std delete msg server thread creation attribute.
 * note
 * Available in eMCOS AUTOSAR only.
 */
mcos_er_t mcos_threadattr_setsharedstack(mcos_thr_attr_t *attr, mcos_bool_t shared);

/**
 * brief <mcos/mcos.h>
 * param[in]   attr    Pointer to attributes struct
 * param[in]   maxact  Pointer to max act count storage
 * return  Error code
 * Specification
 * Gets maxactcount thread creation attribute.
 * note
 * Available in eMCOS AUTOSAR only.
 */
mcos_er_t mcos_threadattr_getmaxactcount(const mcos_thr_attr_t *attr, uint8_t *maxact);

/**
 * brief <mcos/mcos.h>
 * param[in]   attr    Pointer to attributes struct
 * param[in]   maxact  Max act count value (0 means default max act count)
 * return  Error code
 * Specification
 * Sets maxactcount thread creation attribute.
 * note
 * Available in eMCOS AUTOSAR only.
 */
mcos_er_t mcos_threadattr_setmaxactcount(mcos_thr_attr_t *attr, uint8_t maxact);

/**
 * brief <mcos/mcos.h>
 * param[in]   attr    Pointer to attributes struct
 * param[in]   autosar Pointer to boolean storage
 * return  Error code
 * Specification
 * -
 * note
 * Available in eMCOS AUTOSAR only.
 */
mcos_er_t mcos_threadattr_getautosarthread(const mcos_thr_attr_t *attr, mcos_bool_t *autosar);

/**
 * brief <mcos/mcos.h>
 * param[in]   attr    Pointer to attributes struct
 * param[in]   autosar Boolean value (true means AUTOSAR thread)
 * return  Error code
 * Specification
 * -
 * note
 * Available in eMCOS AUTOSAR only.
 */
mcos_er_t mcos_threadattr_setautosarthread(mcos_thr_attr_t *attr, mcos_bool_t autosar);
#endif /* #if !MCOS_AUTOSAR */

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* #ifndef MCOS_H */
