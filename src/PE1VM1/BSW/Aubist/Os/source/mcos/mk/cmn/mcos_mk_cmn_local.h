/*
    Copyright (C) 2015 eSOL Co.,Ltd. Tokyo, Japan

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
[ mcos_mk_cmn_local.h ] - eMCOS/MK cmn local header
****************************************************************************/
#ifndef MCOS_MK_CMN_LOCAL_H
#define MCOS_MK_CMN_LOCAL_H

#include "mcos_mk_local.h"

#if !MCOS_AUTOSAR

extern void mcos_hwl_barrier(mcos_id_t lcid);

#endif /* !MCOS_AUTOSAR */


#endif /* #ifndef MCOS_MK_CMN_LOCAL_H */
