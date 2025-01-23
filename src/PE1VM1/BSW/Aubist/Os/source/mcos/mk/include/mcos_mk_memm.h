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
[ mcos_mk_memm.h ] - eMCOS/MK message memory manager local header
****************************************************************************/
#ifndef MCOS_MK_MEMM_H
#define MCOS_MK_MEMM_H

#include "mcos_mk.h"

#if !MCOS_AUTOSAR
/* max count of pending user message */
#define MEMM_USER_MSG_PENDING_COUNT_MAX (MCOS_CFG_MSG_PENDING_COUNT_MAX - MCOS_CFG_SYSTEM_MSG_COUNT_MAX)

/* message memory manager control block */
struct memmcb_st
{
    msg_t *freemsg;                                             /* free messages */
    msg_t *freehmsg;                                            /* free header messages */
    uint32_t count_usermsg;                                     /* user messages count */
    msg_t msg[MCOS_CFG_MSG_PENDING_COUNT_MAX];    /* memory area for pending message */
    uint32_t msgbuf[(MSG_MAX_SIZE / sizeof(uint32_t)) * (uint32_t)MCOS_CFG_MSG_PENDING_COUNT_MAX];   /* message data buffer */
};

void mcos_memm_init(const mkcb_t * mkcb);
#endif /* #if !MCOS_AUTOSAR */

#endif /* #ifndef MCOS_MK_MEMM_H */
