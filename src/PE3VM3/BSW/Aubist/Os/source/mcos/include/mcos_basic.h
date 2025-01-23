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
[ mcos_basic.h ] - MCOS local common basic header
****************************************************************************/
#ifndef MCOS_BASIC_H
#define MCOS_BASIC_H

#if MCOS_AUTOSAR
#include "hal/hal_impl.h"
#else /* #if MCOS_AUTOSAR */
#include "bios/bios_impl.h"
#endif /* #else */

#include "mcos/xmcos.h"
#include "mcos_def.h"
#include "mcos_msg.h"
#include "mcos_syssrv.h"
#include "mcos/mcos_hook.h"

#define MCOS_INLINE HAL_INLINE

/* BIOS cpu number to eMCOS logical core ID */
#define CPUNO2LCID(n)           ((int32_t)(n) + (int32_t)MCOS_BASE_LCID)
/* eMCOS logical core ID to BIOS cpu number */
#define LCID2CPUNO(n)           ((int32_t)(n) - (int32_t)MCOS_BASE_LCID)

/* LCID to relative core index in local hardware cluster */
MCOS_INLINE mcos_id_t mcos_cnv_lcid_to_rcidx(const mcos_id_t lcid);

#define LCID2RCIDX_NC(lcid)     ((int32_t)(lcid) - MCOS_BASE_LCID)
#if !MCOS_AUTOSAR
#define LCID2RCIDX(lcid)        mcos_cnv_lcid_to_rcidx(lcid)
#endif  /* !MCOS_AUTOSAR */

/* LCID to hardware cluster ID */
#if !MCOS_AUTOSAR
MCOS_INLINE mcos_id_t mcos_cnv_lcid_to_hwclid(const mcos_id_t lcid);
#endif /* !MCOS_AUTOSAR */

#define LCID2HWCLID_NC(lcid)    ((((uint32_t)(lcid) - (uint32_t)1) / (uint32_t)MCOS_CFG_GLB_CORE_PER_HWCL_MAX) + (uint32_t)1)
#if !MCOS_AUTOSAR
#define LCID2HWCLID(lcid)       mcos_cnv_lcid_to_hwclid(lcid)
#endif /* !MCOS_AUTOSAR */

#if !MCOS_AUTOSAR
MCOS_INLINE mcos_id_t mcos_cnv_lcid_to_rcidx(
    const mcos_id_t lcid)
{
    return (mcos_id_t)((((int32_t)(lcid) < MCOS_BASE_LCID) || ((int32_t)(lcid) >= (MCOS_BASE_LCID + (int32_t)MP_CONTROL_CORE_COUNT)))
        ? (int32_t)(MCOS_LCID_INVALID) : (int32_t)LCID2RCIDX_NC(lcid));
}
#endif /* !MCOS_AUTOSAR */

#if !MCOS_AUTOSAR
MCOS_INLINE mcos_id_t mcos_cnv_lcid_to_hwclid(
    const mcos_id_t lcid)
{
    uint32_t condition = LCID2HWCLID_NC(lcid);
    return (mcos_id_t)((((int32_t)lcid <= (int32_t)0) || ((int32_t)lcid > ((int32_t)MCOS_CFG_GLB_HWCL_MAX * (int32_t)MCOS_CFG_GLB_CORE_PER_HWCL_MAX)))
        ? (int32_t)(MCOS_LCID_INVALID) : (int32_t)condition);
}
#endif /* !MCOS_AUTOSAR */

MCOS_INLINE mcos_id_t mcos_get_lcid(void);

/* get LCID */
MCOS_INLINE mcos_id_t mcos_get_lcid(void)
{
    bios_uint_t cpuno;

    cpuno = (bios_uint_t)bios_mp_getCurrent();
    return (mcos_id_t)CPUNO2LCID(cpuno);
}

#if !MCOS_AUTOSAR

MCOS_INLINE mcos_bool_t mcos_is_validlcid(mcos_id_t const lcid);

/*---------------------------------------------------------------------------
  mcos_is_validlcid
     Specified logical core id is valid or not (on the current HW cluster only)
  Input     :   lcid    logical core id
  Output    :   none
  Return    :   0       is not valid
            :   !0      is valid
  Note  :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE mcos_bool_t mcos_is_validlcid(
    const mcos_id_t lcid)
{
    return ( ((int32_t)lcid >= (int32_t)MCOS_BASE_LCID)
              && ((int32_t)lcid < ((int32_t)MCOS_BASE_LCID + (int32_t)MP_CONTROL_CORE_COUNT)));
}
#endif /* #if !MCOS_AUTOSAR */


#endif /* #ifndef MCOS_BASIC_H */
