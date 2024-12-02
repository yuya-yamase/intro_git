/*
    Copyright(C) 2021 eSOL Co., Ltd. All rights reserved.

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
[mcos_v850_local.h] - MCOS hardware layer internal header for v850
****************************************************************************/
#ifndef MCOS_V850_LOCAL_H
#define MCOS_V850_LOCAL_H

#include <mcos_mk_local.h>
#include <mcos/v850/xmcos_v850.h>

#include <hal/cpu/v850/mcos/mcos_v850.cfg>

#include "mcos_v850_mkmsg.h"
#include "mcos_v850_cpp_local.h"

#include <mcos/v850/mcos_v850_hook_code.h>


#define OS_START_SEC_CODE_SHARED
#include "Os_MemMap.h"

/* assembly functions */
extern void mcos_hwl_thread_start(void);

#define OS_STOP_SEC_CODE_SHARED
#include "Os_MemMap.h"

/*
 *  conversion macros
 */
#define LCID2PCID(lcid) ((uint32_t)(lcid) - (uint32_t)MCOS_BASE_LCID_U)
#define PCID2LCID(pcid) ((pcid) + (uint32_t)MCOS_BASE_LCID)

/*
 * HWLCB
 */
/* micro kernel core control block */
struct hwlcb_st
{
    /* mkmsg */
    mkmsg_t mkmsg;
};

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern hwlcb_t * const mcos_v850_hwlcb_table[];

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

MCOS_INLINE hwlcb_t * get_hwlcb(const mcos_id_t lcid);


/*
 * get pointer to hwlcb_t
 */
MCOS_INLINE hwlcb_t * get_hwlcb(
    const mcos_id_t lcid)
{
    return (hwlcb_t*)mcos_v850_hwlcb_table[LCID2RCIDX_NC(lcid)];
}


#define OS_START_SEC_CODE
#include "Os_MemMap.h"

extern void mcos_v850_ar_nonos_exc_handler(void);

#if !MCOS_AUTOSAR
void mcos_hwl_spin_init(void);
#endif /* #if !MCOS_AUTOSAR */

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#endif /* #ifndef MCOS_V850_LOCAL_H */
