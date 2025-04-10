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
[ mcos_mk_fmsg.h ] - eMCOS/MK fast message local header
****************************************************************************/
#ifndef MCOS_MK_FMSG_H
#define MCOS_MK_FMSG_H

#include "mcos_mk.h"

#define MCOS_FMSG_MASK_SYS_TPOOL_REQUEST    (0x00800000U)
#define MCOS_FMSG_MASK_SYS_TPOOL_REPLY      (0x01000000U)

#if !MCOS_AUTOSAR
mcos_er_t mcos_fmessage_send_internal(mcos_id_t tid, const void *data, uint32_t size, uint32_t flags);
mcos_er_t mcos_fmessage_receive_internal(void *data, uint32_t *size, uint32_t flags);
#endif /* #if !MCOS_AUTOSAR */

#endif /* #ifndef MCOS_MK_FMSG_H */
