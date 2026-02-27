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
[ar_osap.h] - OSApplication Information
****************************************************************************/

#ifndef AR_OSAP_H
#define AR_OSAP_H

#include "ar_mcos_local.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

extern void ar_osap_call_errorhook(
    const StatusType status,
    const OSServiceIdType svcid);
extern int32_t ar_osap_call_startuphook(
    int32_t     sr,
    CoreIdType  my_core_id);
extern void ar_osap_call_shutdownhook(
    const StatusType  status);

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) || (AR_OS_USE_MULTICORE == STD_ON)
struct ar_osapcb_st {
    const ar_osap_config_t *p_config;
    mcos_uintptr_t               osap_sp;
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
    ApplicationStateType    osap_state;
#if (AR_OS_HAS_OSAPCB_ARCHCB == STD_ON)
    ar_archcb_t             archcb;
#endif
#endif /* #if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)*/
};

extern void ar_osap_init(void);
extern void ar_osap_errorhook_wrapper(boolean is_protected, uint32 option,
                                    osap_error_hook_func_t entry, StatusType arg, const void *p_osap_sp);
extern void ar_osap_startup_hook_wrapper(boolean is_protected, uint32 option,
                                    osap_startup_hook_func_t entry, StatusType ignored_arg, const void *p_osap_sp,
                                    const ar_osap_config_t  *ignored_before_osap,
                                    const ar_osap_config_t  *after_osap);
extern void ar_osap_shutdown_hook_wrapper(boolean is_protected, uint32 option,
                                    osap_shutdown_hook_func_t entry, StatusType arg, const void *p_osap_sp,
                                    const ar_osap_config_t  *before_osap,
                                    const ar_osap_config_t  *after_osap);


#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)

typedef void (*TrustedFunctionRefType)(TrustedFunctionIndexType FunctionIndex,
                                             TrustedFunctionParameterRefType FunctionParams);

struct ar_tfn_config_st {
    TrustedFunctionRefType  tf_addr;    /* Trusted function address */
    const ar_osap_config_t *tf_osap;    /* Trusted function application */
#if (AR_OS_USE_MULTICORE == STD_ON)
    mcos_id_t               tf_lcid;    /* Core to execute on */
#endif /* (AR_OS_USE_MULTICORE == STD_ON) */
};

#include "ar_osap_local.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

extern StatusType ar_get_application_state_impl(
        ApplicationType appl_id, ApplicationStateRefType p_state);

extern void ar_sc3_tf_wrapper(boolean is_protected, uint32 option,
                              TrustedFunctionRefType entry, TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams);

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

typedef void (*error_hook_func_t)(StatusType Error);
typedef void (*posttask_hook_func_t)(void);
typedef void (*pretask_hook_func_t)(void);
typedef ProtectionReturnType (*protection_hook_func_t)(StatusType FatalError);
typedef void (*shutdown_hook_func_t)(StatusType Error);
typedef void (*startup_hook_func_t)(void);
typedef void (*receiver_pullcb_func_t)(void);


/*
* parameter symbols for hook wrapper
*/
#define IGNORED_IS_PROTECTED    ((boolean)FALSE)
#define IGNORED_OPTION          ((uint32)0)
#define IGNORED_ARG             ((StatusType)0)
#define IGNORED_BEFORE_OSAP     ((const ar_osap_config_t *)NULL)

#endif /* #if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) || (AR_OS_USE_MULTICORE == STD_ON) */


#define OS_START_SEC_CODE
#include "Os_MemMap.h"

extern StatusType ar_chk_isr_owner(ISRType ISRID, const clscb_t *clscb);

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"


#endif /* AR_OSAP_H_ */
