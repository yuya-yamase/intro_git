/*
    Copyright (C) 2018 eSOL Co.,Ltd. Tokyo, Japan

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
[ mcos_mk_config.h ] - eMCOS Microkernel AUTOSAR Data
****************************************************************************/
#ifndef MCOS_MK_CONFIG_H
#define MCOS_MK_CONFIG_H

/*
 * MKCONFIG data
 */
typedef struct
{
    mcos_id_t   control_core_count;     /* mp.cfg: MP_CONTROL_CORE_COUNT */
    mcos_id_t   core_count;             /* mp.cfg: MP_CCORE_COUNT */
    mcos_id_t   master_coreno;          /* mp.cfg: MP_MASTER_CORENO */
    mcos_id_t   min_coreno;             /* mp.cfg: MP_MIN_CORENO */
    mcos_id_t   max_coreno;             /* mcos.cfg: MP_MAX_CORENO */
    mcos_id_t   thr_max;                /* mcos.cfg: MCOS_CFG_THR_MAX */
    uint16_t    thr_act_max;            /* mcos.cfg: MCOS_CFG_THR_ACT_MAX */
    uint32_t    sys_stacksize;          /* mcos.cfg: MCOS_CFG_SYS_STACKSIZE */
} mkconfig_t;

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"
extern const mkconfig_t  mcos_mkconfig;
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#endif /* #if MCOS_MK_CONFIG_H */
