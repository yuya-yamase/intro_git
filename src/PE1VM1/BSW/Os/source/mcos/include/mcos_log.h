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
[mcos_log.h] - MCOS logging functions header
****************************************************************************/
#ifndef MCOS_LOG_H
#define MCOS_LOG_H

#include "mcos_mkcc.h"
#include "mcos_ds_impl.h"

#if IS_DS_SYSLOG_ERROR

void mcos_log_fatal(const mcos_char_t *fmt, ... );
void mcos_log_dump_stack_all(mcos_uintptr_t sp);

#else /* IS_DS_SYSLOG_ERROR */

#define mcos_log_dump_stack_all(x)

#endif /* IS_DS_SYSLOG_ERROR */


#if IS_DS_SYSLOG_API

void mcos_log_api_call(const mcos_char_t *api, int32_t dst);
void mcos_log_api_return(const mcos_char_t *api, mcos_er_t ret);

#else /* IS_DS_SYSLOG_API */

#define mcos_log_api_call(x, y)
#define mcos_log_api_return(x, y)

#endif /* IS_DS_SYSLOG_API */


#if IS_DS_SYSLOG_THREAD||IS_DS_SYSLOG_SERVER||IS_DS_SYSLOG_BOOT||IS_DS_SYSLOG_MSG

void mcos_log_kernel(const mcos_char_t *fmt, ... );

#endif /* IS_DS_SYSLOG_THREAD||IS_DS_SYSLOG_SERVER||IS_DS_SYSLOG_BOOT */

#if IS_DS_SYSLOG_MSG

void mcos_log_message(const mcos_char_t *s, const uint32_t *msgdata, uint32_t msgsz);

#else /* IS_DS_SYSLOG_MSG */

#define mcos_log_message(x, y, z)

#endif /* IS_DS_SYSLOG_MSG */

#if IS_DS_SYSLOG_THREAD_QUEUE

void mcos_log_dump_thread_queue(const clscb_t *clscb);

#else /* IS_DS_SYSLOG_THREAD_QUEUE */

#define mcos_log_dump_thread_queue(x)

#endif /* IS_DS_SYSLOG_THREAD_QUEUE */

#if IS_DS_SYSLOG_HWL||IS_DS_SYSLOG_MKMSG

void mcos_log_hwl(const mcos_char_t *fmt, ... );

#endif /* IS_DS_SYSLOG_HWL||IS_DS_SYSLOG_MKMSG */

#endif /* #ifndef MCOS_LOG_H */
