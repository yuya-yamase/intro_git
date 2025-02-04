/*
    Copyright (C) 2013 By eSOL Co.,Ltd. Tokyo, Japan

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
[mcos_syssrv.h] - MCOS system server static definition
****************************************************************************/
#ifndef MCOS_SYSSRV_H
#define MCOS_SYSSRV_H

#include <mcos/mcos_hwcl.cfg>
#include <mcos/mcos_syssrv.cfg>

/* All TID below are relative TIDs (from 0 to TCB_CNT-1) */
#define TIMESRV_TID_BASE        (0)
#define LFS_TID_BASE            (TIMESRV_TID_BASE + 1)
#define NS_TID_BASE             (LFS_TID_BASE + 1)

#define TIMESRV_TID             (HWCL_BASE_TID + (MCOS_CFG_TIMESRV_LCID - MCOS_BASE_LCID)*MCOS_CFG_GLB_THR_PER_CORE_MAX + TIMESRV_TID_BASE)
#define LFS_TID(hwclid)          (((hwclid) - 1)*MCOS_TID_HWCL + 1 + (MCOS_CFG_LFSSRV_LCID - MCOS_BASE_LCID)*MCOS_CFG_GLB_THR_PER_CORE_MAX + LFS_TID_BASE)

#endif /* #ifndef MCOS_SYSSRV_H */
