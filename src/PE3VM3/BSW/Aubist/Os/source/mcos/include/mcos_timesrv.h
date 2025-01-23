/*
    Copyright (C) 2012 By eSOL Co.,Ltd. Tokyo, Japan

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
[mcos_timesrv.h] - MCOS system time server header
****************************************************************************/
#ifndef MCOS_TIMESRV_H
#define MCOS_TIMESRV_H

#include "mcos_cmn.h"

/*****************************/
/* Definitions for messages  */
/*****************************/

/* message ID */
#define TIMESRV_MSGID_TDLY          (1)     /* mcos_thread_delay request */
#define TIMESRV_MSGID_TDLY_R        (2)     /* mcos_thread_delay reply */
#define TIMESRV_MSGID_TIME_SET      (3)     /* mcos_time_set request */
#define TIMESRV_MSGID_TIME_SET_R    (4)     /* mcos_time_set reply */
#define TIMESRV_MSGID_TIME_GET      (5)     /* mcos_time_get request */
#define TIMESRV_MSGID_TIME_GET_R    (6)     /* mcos_time_get reply */
#define TIMESRV_MSGID_TDLY_FINISH   (7)     /* need to be finishing for */
                                            /* mcos_thread_delay */
#if MCOS_PT_API
#define TIMESRV_MSGID_TDLYABS       (14)    /* mcos_thread_absdelay request */
#endif /* MCOS_PT_API */
#if MCOS_HWCL
#define TIMESRV_MSGID_SRVREG        (15)    /* register Cluster Time Server */
#endif /* MCOS_HWCL */


/*****************************/
/* Message packet structures */
/*****************************/

/* basic message packet of request */
typedef union timesrv_req
{
    int32_t         id32;
    struct
    {
        mcos_id_t   id;             /* message id */
        mcos_id_t   tid;            /* caller thread id */
    } id16;
} timesrv_req_t;

/* basic message packet of reply */
typedef union timesrv_rep
{
    int32_t id32;
    struct
    {
        mcos_id_t   id;             /* message id */
        mcos_erid_t ret;            /* return value */
    } id16;
} timesrv_rep_t;

/* TIMESRV_MSGID_TDLY */
typedef struct
{
    timesrv_req_t   req;
    mcos_reltime_t  time;           /* delayed time */
} msg_tdly_t;

#if MCOS_PT_API
/* TIMESRV_MSGID_TDLYABS */
typedef struct
{
    timesrv_req_t   req;
    mcos_systime_t  time;           /* abs delayed time */
} msg_tdlyabs_t;
#endif /* MCOS_PT_API */

#if MCOS_CFG_HWCL_ID
typedef struct
{
    timesrv_req_t   req;            /* server registration */
} msg_tsrvreg_t;
#endif /* MCOS_CFG_HWCL_ID */

/* TIMESRV_MSGID_TDLY_R */
typedef struct
{
    timesrv_rep_t   rep;
} msg_tdly_r_t;

/* TIMESRV_MSGID_TIME_SET */
typedef struct
{
    timesrv_req_t   req;
    mcos_systime_t  time;           /* time to be set */
} msg_timeset_t;

/* TIMESRV_MSGID_TIME_SET_R */
typedef struct
{
    timesrv_rep_t   rep;
} msg_timeset_r_t;

/* TIMESRV_MSGID_TIME_GET */
typedef struct
{
    timesrv_req_t   req;
} msg_timeget_t;

/* TIMESRV_MSGID_TIME_GET_R */
typedef struct
{
    timesrv_rep_t   rep;
    mcos_systime_t  time;           /* current time */
} msg_timeget_r_t;

/* TIMESRV_MSGID_TDLY_FINISH */
typedef struct
{
    timesrv_req_t   req;
} msg_tdly_finish_t;


/*****************************/
/* interface functions       */
/*****************************/

extern mcos_er_t mcos_timesrv_create_timer_server(const mkcb_t *mkcb);
extern mcos_id_t mcos_timesrv_get_server_tid(void);
extern mcos_er_t mcos_timesrv_send_request(int id, size_t size, timesrv_req_t* req);
extern mcos_er_t mcos_timesrv_receive_reply(int id, size_t size, timesrv_rep_t* rep);

#if MCOS_HWCL
extern mcos_id_t mcos_timesrv_get_master_tid(void);
#endif /* MCOS_HWCL */

/*****************************/
/* Message max size check.   */
/*****************************/
/*
 * Note :
 *  This type is used to compare message size only.
 *  Do not use in the execution code.
 */
typedef union
{
    msg_tdly_r_t                msg_tdly_r;
    msg_timeset_r_t             msg_timeset_r;
    msg_timeget_r_t             msg_timeget_r;
    msg_tdly_finish_t           msg_tdly_finish;
    msg_tdly_t                  msg_tdly;
    msg_timeset_t               msg_timeset;
#if MCOS_CFG_HWCL_ID
    msg_tsrvreg_t               msg_tsrvreg;
#endif /* MCOS_CFG_HWCL_ID */
#if MCOS_PT_API
    msg_tdlyabs_t               msg_tdlyabs;
#endif /* MCOS_PT_API */
} time_msg_size_check_t;

COMPILETIME_SIZECHECK_GE(msg_size, ((uint64_t)MCOS_CFG_MSG_SIZE_MAX), ((uint64_t)sizeof(time_msg_size_check_t)));

#endif /* #ifndef MCOS_TIMESRV_H */
