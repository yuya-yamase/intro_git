/*
    Copyright (C) 2016 By eSOL Co.,Ltd. Tokyo, Japan

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
[ar_resource.h] - Resource Information
****************************************************************************/

#ifndef AR_RESOURECE_H
#define AR_RESOURECE_H

struct ar_resource_config_st {
    sint32          ceilpri;        /* ceiling priority (thread or interrupt) */
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
    const uint32    *osap_allowedmap;   /* Access allowed OSAP bitmap */
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
    mcos_id_t       lcid;
};

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
extern void ar_resource_init(void);
extern void ar_task_force_release_resources(ar_tcb_t * const p_atcb);
extern void ar_c2isr_force_release_resources(ar_isrcb_t * const p_isrcb);
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"


#endif /* AR_RESOURECE_H */
