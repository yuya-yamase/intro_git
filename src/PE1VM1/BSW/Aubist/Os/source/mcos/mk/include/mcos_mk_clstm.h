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
[ mcos_mk_clstm.h ] - eMCOS/MK cluster manager local header
****************************************************************************/
#ifndef MCOS_MK_CLSTM_H
#define MCOS_MK_CLSTM_H

#include "mcos_mk.h"

/* cluster manager control block */
struct clstmcb_st
{
    mcos_id_t ltslcid;       /* leaf thread scheduler core id */
};

/* entry function */
typedef void (*init_t)(void);

/* cluster manager interface functions */
#if MCOS_CFG_SCCL_NUM > 1U
void mcos_clstm_init(const mkcb_t * mkcb);
mcos_id_t mcos_clstm_get_ltslcid(const mkcb_t * mkcb);
mcos_id_t mcos_clstm_get_scid(mcos_id_t lcid);
#if !MCOS_AUTOSAR
mcos_id_t mcos_clstm_get_lcid(const mcos_id_t scid, const int32_t idx);
#endif /* !MCOS_AUTOSAR */
uint32_t mcos_clstm_get_ccnt(mcos_id_t scid);
#else
#define mcos_clstm_init(x)
#define mcos_clstm_get_ltslcid(x)        ((mcos_id_t)(MCOS_CFG_TSSRV_LCID))
#define mcos_clstm_get_scid(x)          ((mcos_id_t)1)
#define mcos_clstm_get_ccnt(x)          ((uint32_t)MP_CONTROL_CORE_COUNT)

#if !MCOS_AUTOSAR
MCOS_INLINE mcos_id_t mcos_clstm_get_lcid(const mcos_id_t scid, const int32_t idx);

MCOS_INLINE mcos_id_t mcos_clstm_get_lcid(
    const mcos_id_t scid,
    const int32_t idx)
{
    (void)scid; /* 'scid' is not used in this function when MCOS_CFG_SCCL_NUM is lower than 2. */
    return (mcos_id_t)((idx == (int32_t)MP_CONTROL_CORE_COUNT)
        ? (int32_t)LCID_NONE : ((int32_t)MCOS_BASE_LCID + (idx)));
}
#endif /* !MCOS_AUTOSAR */

#endif
#if !MCOS_AUTOSAR
init_t mcos_clstm_get_init(mcos_id_t scid);
#endif /* !MCOS_AUTOSAR */


#endif /* #ifndef MCOS_MK_CLSTM_H */
