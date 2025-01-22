/*
    Copyright (C) 2018 By eSOL Co.,Ltd. Tokyo, Japan

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
[mcos_cls_buildchk.h] - MCOS core local scheduler header (Build check)
****************************************************************************/
#ifndef MCOS_CLS_BUILDCHK_H
#define MCOS_CLS_BUILDCHK_H

#include "mcos_cls.h"

/* check defined value */
#if ((MCOS_CFG_THR_MAX * MP_CONTROL_CORE_COUNT) > USHORT_MAX)
#error (MCOS_CFG_THR_MAX * MP_CONTROL_CORE_COUNT) is too large.
#endif /* #if ((MCOS_CFG_THR_MAX * MP_CONTROL_CORE_COUNT) > USHORT_MAX) */

#endif /* MCOS_CLS_BUILDCHK_H */
