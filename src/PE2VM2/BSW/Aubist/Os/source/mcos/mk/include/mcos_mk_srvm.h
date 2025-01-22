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
[ mcos_mk_srvm.h ] - eMCOS/MK server manager local header
****************************************************************************/
#ifndef MCOS_MK_SRVM_H
#define MCOS_MK_SRVM_H

#if !MCOS_AUTOSAR

#include "mcos_mk.h"

mcos_er_t mcos_server_register_internal(const mcos_char_t *name, mcos_id_t tid, mcos_id_t nsid);
mcos_er_t mcos_server_unregister_internal(const mcos_char_t *name, mcos_id_t nsid);
mcos_erid_t mcos_server_getid_internal(const mcos_char_t *name, mcos_id_t nsid);
mcos_er_t mcos_server_reply_internal(mcos_id_t rtid);

#endif /* !MCOS_AUTOSAR */

#endif /* #ifndef MCOS_MK_SRVM_H */
