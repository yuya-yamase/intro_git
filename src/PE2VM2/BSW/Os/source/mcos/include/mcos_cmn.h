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
[ mcos_cmn.h ] - MCOS common header
****************************************************************************/
#ifndef MCOS_CMN_H
#define MCOS_CMN_H

#include "mcos_basic.h"

#if !MCOS_AUTOSAR
#include "mcos_queue.h"
#endif /* !MCOS_AUTOSAR */

#include "mcos_spinlock.h"

#if !MCOS_AUTOSAR
#include "mcos_util.h"
#endif

#include "mcos_ds_impl.h"
#include "mcos_mkcc.h"
#include "mcos_log.h"

#endif /* #ifndef MCOS_CMN_H */
