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
[ mcos_mk_intm.h ] - eMCOS/MK interrupt manager local header
****************************************************************************/
#ifndef MCOS_MK_INTM_H
#define MCOS_MK_INTM_H

#include "mcos_mk.h"

#if MCOS_AUTOSAR
#include "Os_internal.h"
#endif /* MCOS_AUTOSAR */

/* interrupt manager control block */
struct intmcb_st
{
    /* iid min */
    int32_t iidmin;
    /* iid min */
    int32_t iidmax;
    /* ptr to mcos_int_def_t */
    mcos_int_def_t *idp;
};

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

#if !MCOS_AUTOSAR
/* interrupt manager interface functions */
uint8_t * mcos_intm_init(const mkcb_t * mkcb, uint8_t * end);
#endif /* #if !MCOS_AUTOSAR */

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#if MCOS_CFG_PARAM_CHECK
mcos_er_t mcos_interrupt_clear_internal(mcos_id_t iid);
#else /* #if MCOS_CFG_PARAM_CHECK */
MCOS_INLINE mcos_er_t
mcos_interrupt_clear_internal(mcos_id_t iid)
{
    bios_pic_clearInt((bios_int_t)iid);
    return MCOS_EOK;
}
#endif /* #if MCOS_CFG_PARAM_CHECK */


#endif /* #ifndef MCOS_MK_INTM_H */
