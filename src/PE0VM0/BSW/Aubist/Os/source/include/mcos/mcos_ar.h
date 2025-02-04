/*
    Copyright (C) 2011 By eSOL Co.,Ltd. Tokyo, Japan

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
[mcos_ar.h] - MCOS interface header
****************************************************************************/
#ifndef MCOS_AR_H
#define MCOS_AR_H

#include "Os_internal.h"

#include "hal/hal_cache.h"
#include "hal/hal_mb_impl.h"
#include "mcos_refresh.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

extern void mcos_initialize(void);
extern void mcos_slave_initialize(const CoreIdType coreid);
extern void mcos_slave_wait_for_start(const CoreIdType coreid);

extern mcos_refresh_err_t mcos_refresh_register_values_hook(const CoreIdType coreid, boolean should_fix);

extern void mcos_ar_hook_call_pre_biosinit(void);
extern void mcos_ar_hook_call_pre_biosinit_slave(const CoreIdType coreid);
extern void mcos_ar_bios_instance_initialize(void);
extern void mcos_ar_bios_instance_initialize_slave(const CoreIdType coreid);
extern void mcos_ar_bios_hw_initialize(void);
extern void mcos_ar_bios_hw_initialize_slave(const CoreIdType coreid);

extern void mcos_ar_ecum_initialize1(void);
extern void mcos_slave_ar_ecum_initialize1(const CoreIdType coreid);

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"


#ifdef __cplusplus
}
#endif

#endif /* #ifndef MCOS_AR_H */
