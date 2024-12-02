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
[ar_mcos.h] - MCOS AUTOSAR interface
****************************************************************************/
#ifndef AR_MCOS_H
#define AR_MCOS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Os_internal.h"
#include "mcos/mcos_ar_ds.h"
#include "mcos_ds_impl.h"

#if defined __V850__

#include "arch/v850/mcos_ar_v850.h"
#include "arch/v850/mcos_ds_v850.h"

#elif defined __Tricore /* #if defined __V850__ */

#if defined __ghs__
#include "arch/tc162/mcos_ar_tc162.h"
#include "arch/tc162/mcos_ds_tc162.h"
#endif /* #if defined __ghs__ */

#elif defined __ARM__ /* #elif defined __Tricore */

#include "arch/armv7m/mcos_ar_armv7m.h"
#include "arch/armv7m/mcos_ds_armv7m.h"

#elif defined __ARMCC_VERSION /* #elif defined __ARM__ */

#include "arch/armv8r/mcos_ar_armv8r.h"
#include "arch/armv8r/mcos_ds_armv8r.h"

#endif /* #elif defined __ARM__ */

/*
 * CALL LEVEL
 */
#define AR_CL_NONE          ((uint32) 0x0000U)
#define AR_CL_TASK          ((uint32) 0x0001U)
#define AR_CL_C2ISR         ((uint32) 0x0002U)
#define AR_CL_HK_STARTUP    ((uint32) 0x0004U)
#define AR_CL_HK_SHUTDOWN   ((uint32) 0x0008U)
#define AR_CL_HK_ERROR      ((uint32) 0x0010U)
#define AR_CL_HK_PROT       ((uint32) 0x0020U)
#define AR_CL_HK_PREPOST    ((uint32) 0x0040U)
#define AR_CL_ALRMCB        ((uint32) 0x0080U)
#define AR_CL_RCVPLCB       ((uint32) 0x0100U)
#define AR_CL_FASTTF        ((uint32) 0x0200U)
#define AR_CL_SYS_HK_BIT    ((uint32) 0x0400U)
#define AR_CL_MASK          ((uint32) 0x0fffU)

typedef void (*ar_funcp_t)(void);
typedef struct ar_oscb_st ar_oscb_t;

typedef struct ar_osap_config_st ar_osap_config_t;
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) || (AR_OS_USE_MULTICORE == STD_ON)
typedef struct ar_osapcb_st ar_osapcb_t;
#endif  /* #if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) || (AR_OS_USE_MULTICORE == STD_ON) */

typedef struct ar_isr_config_st ar_isr_config_t;
typedef struct ar_int_config_st ar_int_config_t;

typedef struct ar_task_config_st ar_task_config_t;
typedef struct ar_tcb_st ar_tcb_t;
typedef struct ar_resource_config_st ar_resource_config_t;
typedef struct ar_resourcecb_st ar_resourcecb_t;

typedef struct ar_spinlock_config_st ar_spinlock_config_t;
typedef struct ar_spinlockcb_st ar_spinlockcb_t;
typedef struct ar_context_spinlockcbs_st ar_context_spinlockcbs_t;

#define AR_ERRHK_PARAM_NUM  ((uint32) 4U)

struct ar_context_spinlockcbs_st
{
    ar_spinlockcb_t         *p_last_spinlockcb;
    ar_spinlockcb_t         *p_wait_spinlockcb;
};

struct ar_oscb_st {
    boolean             is_booted;
    uint16              call_level;
    OSServiceIdType     _errhk_svcid;
    ar_errhk_param_t    _errhk_param[AR_ERRHK_PARAM_NUM];
    ar_errhk_param_t    errhk_param[AR_ERRHK_PARAM_NUM];

    const ar_osap_config_t *p_runosap;          /* USED ASSEMBLER */
    const ar_osap_config_t *p_currentosap;      /* USED ASSEMBLER */

    ar_context_spinlockcbs_t       context_spinlockcbs;
    mcos_uintptr_t      idle_sp;             /* idle sp: Usage is target-dependent (USED ASSEMBLER!) */
    ar_osarchcb_t       osarchcb;            /* USED ASSEMBLER */
    boolean             in_errorhook;
    boolean             in_rcvplcb;
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
    const ar_osap_config_t *p_wait_for_response;
    ar_tcb_t            *restart_task_atcb;
    boolean             wait_in_chaintask;
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
};

struct ar_isr_config_st {
    const ar_int_config_t   *p_config;
#if (AR_OS_USE_STACKMONITORING == STD_ON)
    const uint32            stack_size;
#endif /* (AR_OS_USE_STACKMONITORING == STD_ON) */
    const ar_osap_config_t  *p_osapconfig;
};

struct ar_isrcb_st {
    const ar_isr_config_t   *p_config;
    ar_resourcecb_t         *p_last_resourcecb;
    ar_context_spinlockcbs_t       context_spinlockcbs;
};

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

extern void ar_set_mastercore_booted(void);
extern void ar_initialize_osap(ApplicationType osap_id);

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"


#ifdef __cplusplus
}
#endif

#endif /* AR_MCOS_H */

