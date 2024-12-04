/*
    Copyright (C) 2016 By eSOL Co.,Ltd. Tokyo, Japan

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
[mcos_msgprof.h] - eMCOS Message Profiler header
****************************************************************************/

#ifndef MCOS_MSGPROF_H
#define MCOS_MSGPROF_H

#include <mcos/mcos.h>
#include <mcos/mcos_ds.h>

#if MCOS_CFG_DS_MSGPROF_ENABLE

/* callback for messaging */
void
mcos_msgprof_callback_message(
    const mcos_msgprof_message_info_t* message_info);

/* callback for creating new thread */
void
mcos_msgprof_callback_create_thread(
    mcos_id_t tid,
    const char* name);

#endif /* MCOS_CFG_DS_MSGPROF_ENABLE */

/* register thread name to Message Profiler */
void mcos_msgprof_register_new_thread(int16_t tid, const char* tname);

#endif /* MCOS_MSGPROF_H */
