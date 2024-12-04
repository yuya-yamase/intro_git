/*
    Copyright (C) 2013 eSOL Co.,Ltd. Tokyo, Japan

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
[ mcos_memm.h ] - MCOS message memory manager internal header
****************************************************************************/
#ifndef MCOS_MEMM_H
#define MCOS_MEMM_H

#include "mcos_cmn.h"

/* message memory manager interface functions */
msg_t *mcos_memm_alloc_message(const mkcb_t * mkcb, uint32_t msgsz, uint32_t authority);
void mcos_memm_release_message(const mkcb_t * mkcb, msg_t *msg);
void mcos_memm_release_message_head(const mkcb_t *mkcb, msg_t *msg);
void mcos_memm_release_message_body(const mkcb_t *mkcb, uint32_t *msgbody);


#endif /* #ifndef MCOS_MEMM_H */
