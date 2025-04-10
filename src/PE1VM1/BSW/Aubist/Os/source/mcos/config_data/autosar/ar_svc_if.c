/*
    Copyright (C) 2017 By eSOL Co.,Ltd. Tokyo, Japan

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
[ar_svc_if.c] - Supervisor call I/F for AUTOSAR OS
****************************************************************************/

#include "Os.h"
#include "ar_kernel_impl.h"
#include "ar_task.h"
#include "ar_ioc.h"
#include "ar_mcos.h"
#include "ar_svc_id.h"
#include "Os_internal2.h"

#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)

#define AR_CLEAR_PENDING0      0
#define AR_CLEAR_PENDING1      1
#if (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U)
#define AR_SERVICE_CALL_D_DDD0 0
#endif /*#if (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U) */

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

/*---------------------------------------------------------------------------
  ar_system_call_error
 ---------------------------------------------------------------------------*/
void
ar_system_call_error(void)
{
    mcos_hook_panic(MCOS_HOOK_AR_SYSCALL_ERROR);
    /* never reached */
}

/*---------------------------------------------------------------------------
  ar_no_support_service
 ---------------------------------------------------------------------------*/
StatusType
ar_no_support_service(void)
{

    StatusType      status;

    status  = (StatusType)E_OS_SERVICEID;

#if (AR_OS_USE_ERRORHOOK == STD_ON)
    {
        const mkcb_t    *mkcb;
        clscb_t         *clscb;
        ar_critical_section_t   cs;

        mkcb = (const mkcb_t *)mcos_mkcc_get_current_control_block();
        clscb = mcos_mkcc_get_clscb(mkcb);

        cs = ar_critical_section_enter_core(clscb);

        AR_SVC_SUBSTANCE(ar_errorhook_call)(status, OSSVCID_INVALID, NULL);

        ar_critical_section_leave_core(clscb, cs);
    }
#endif /* (AR_OS_USE_ERRORHOOK == STD_ON) */

    return status;
}

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE_SHARED
#include "Os_MemMap.h"


/*---------------------------------------------------------------------------
  AR_FNC(ar_no_support_service)
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
AR_FNC(ar_no_support_service)(void)
{
    StatusType          status;
    ar_kmode_state_t    prev;

    prev = ar_enter_kernel();
    status = ar_no_support_service();
    ar_leave_kernel(prev);

    return status;
}

/*---------------------------------------------------------------------------
  EnableAllInterrupts
    service call I/F function
 ---------------------------------------------------------------------------*/
void
EnableAllInterrupts(void)
{
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_ENABLE_ALL_INTERRUPTS == STD_ON)
        AR_FNC(EnableAllInterrupts)();
#else
        (void)AR_FNC(ar_no_support_service)();  /* Do not use the return value of this process. */
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        ar_service_call_0_0((sint32)AR_SVCID_ENABLEALLINTERRUPTS);
    }
}


/*---------------------------------------------------------------------------
  DisableAllInterrupts
    service call I/F function
 ---------------------------------------------------------------------------*/
void
DisableAllInterrupts(void)
{
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_DISABLE_ALL_INTERRUPTS == STD_ON)
        AR_FNC(DisableAllInterrupts)();
#else
        (void)AR_FNC(ar_no_support_service)();  /* Do not use the return value of this process. */
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        ar_service_call_0_0((sint32)AR_SVCID_DISABLEALLINTERRUPTS);
    }
}


/*---------------------------------------------------------------------------
  ResumeAllInterrupts
    service call I/F function
 ---------------------------------------------------------------------------*/
void
ResumeAllInterrupts(void)
{
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_RESUME_ALL_INTERRUPTS == STD_ON)
        AR_FNC(ResumeAllInterrupts)();
#else
        (void)AR_FNC(ar_no_support_service)();  /* Do not use the return value of this process. */
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        ar_service_call_0_0((sint32)AR_SVCID_RESUMEALLINTERRUPTS);
    }
}


/*---------------------------------------------------------------------------
  SuspendAllInterrupts
    service call I/F function
 ---------------------------------------------------------------------------*/
void
SuspendAllInterrupts(void)
{
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_SUSPEND_ALL_INTERRUPTS == STD_ON)
        AR_FNC(SuspendAllInterrupts)();
#else
        (void)AR_FNC(ar_no_support_service)();  /* Do not use the return value of this process. */
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        ar_service_call_0_0((sint32)AR_SVCID_SUSPENDALLINTERRUPTS);
    }
}


/*---------------------------------------------------------------------------
  ResumeOSInterrupts
    service call I/F function
 ---------------------------------------------------------------------------*/
void
ResumeOSInterrupts(void)
{
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_RESUME_OSINTERRUPTS == STD_ON)
        AR_FNC(ResumeOSInterrupts)();
#else
        (void)AR_FNC(ar_no_support_service)();  /* Do not use the return value of this process. */
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        ar_service_call_0_0((sint32)AR_SVCID_RESUMEOSINTERRUPTS);
    }
}


/*---------------------------------------------------------------------------
  SuspendOSInterrupts
    service call I/F function
 ---------------------------------------------------------------------------*/
void
SuspendOSInterrupts(void)
{
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_SUSPEND_OSINTERRUPTS == STD_ON)
        AR_FNC(SuspendOSInterrupts)();
#else
        (void)AR_FNC(ar_no_support_service)();  /* Do not use the return value of this process. */
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        ar_service_call_0_0((sint32)AR_SVCID_SUSPENDOSINTERRUPTS);
    }
}


/*---------------------------------------------------------------------------
  DisableInterruptSource
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
DisableInterruptSource(ISRType ISRID)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if ((AR_OS_EXIST_C2ISR == STD_ON) && (AR_OS_USE_DISABLE_INTERRUPT_SOURCE == STD_ON))
        status = AR_FNC(DisableInterruptSource)(ISRID);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_d(
                  (sint32)ISRID, (sint32)AR_SVCID_DISABLEINTERRUPTSOURCE);
    }
    return status;
}


/*---------------------------------------------------------------------------
  EnableInterruptSource
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
EnableInterruptSource(ISRType ISRID, boolean ClearPending)
{
    StatusType status;
    sint32     tempClearPending;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if ((AR_OS_EXIST_C2ISR == STD_ON) && (AR_OS_USE_ENABLE_INTERRUPT_SOURCE == STD_ON))
        status = AR_FNC(EnableInterruptSource)(ISRID, ClearPending);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        tempClearPending = ((ClearPending == (boolean)FALSE) ? (sint32)AR_CLEAR_PENDING0 : (sint32)AR_CLEAR_PENDING1);
        status = (StatusType)ar_service_call_d_dd(
                  (sint32)ISRID, tempClearPending, (sint32)AR_SVCID_ENABLEINTERRUPTSOURCE);
    }
    return status;
}


/*---------------------------------------------------------------------------
  ClearPendingInterrupt
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
ClearPendingInterrupt(ISRType ISRID)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if ((AR_OS_EXIST_C2ISR == STD_ON) && (AR_OS_USE_CLEAR_PENDING_INTERRUPT == STD_ON))
        status = AR_FNC(ClearPendingInterrupt)(ISRID);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_d(
                  (sint32)ISRID, (sint32)AR_SVCID_CLEARPENDINGINTERRUPT);
    }
    return status;
}

#if (AR_ENABLE_CHECK_TASK_MEMORY_ACCESS != 0U)

/*---------------------------------------------------------------------------
  CheckTaskMemoryAccess
    service call I/F function
 ---------------------------------------------------------------------------*/
AccessType
CheckTaskMemoryAccess(TaskType TaskID, MemoryStartAddressType Address, MemorySizeType Size)
{
    AccessType access;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_CHECK_TASK_MEMORY_ACCESS == STD_ON)
        access = AR_FNC(CheckTaskMemoryAccess)(TaskID, Address, Size);
#else
        access = (AccessType)AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        access = (AccessType)ar_service_call_d_dpd(
                (sint32)TaskID, (const void *)Address, (sint32)Size, (sint32)AR_SVCID_CHECKTASKMEMORYACCESS);
    }
    return access;
}

#endif /* #if (AR_ENABLE_CHECK_TASK_MEMORY_ACCESS != 0U) */

#if (AR_ENABLE_CHECK_ISR_MEMORY_ACCESS != 0U)

/*---------------------------------------------------------------------------
  CheckISRMemoryAccess
    service call I/F function
 ---------------------------------------------------------------------------*/
AccessType
CheckISRMemoryAccess(ISRType ISRID, MemoryStartAddressType Address, MemorySizeType Size)
{
    AccessType access;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_CHECK_ISR_MEMORY_ACCESS == STD_ON)
        access = AR_FNC(CheckISRMemoryAccess)(ISRID, Address, Size);
#else
        access = (AccessType)AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        access = (AccessType)ar_service_call_d_dpd(
                  (sint32)ISRID, (const void *)Address, (sint32)Size, (sint32)AR_SVCID_CHECKISRMEMORYACCESS);
    }
    return access;
}

#endif /* #if (AR_ENABLE_CHECK_ISR_MEMORY_ACCESS != 0U) */

#if (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U)

/*---------------------------------------------------------------------------
  CheckObjectAccess
    service call I/F function
 ---------------------------------------------------------------------------*/
ObjectAccessType
CheckObjectAccess(ApplicationType ApplID, ObjectTypeType ObjectType, uint32 ObjectID)
{
    ObjectAccessType oa;
    sint32 ret;

#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;
#if (AR_OS_USE_CHECK_OBJECT_ACCESS != STD_ON)
    StatusType status;
#endif

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_CHECK_OBJECT_ACCESS == STD_ON)
        oa = AR_FNC(CheckObjectAccess)(ApplID, ObjectType, ObjectID);
#else
        status = AR_FNC(ar_no_support_service)();
        oa = (ObjectAccessType)((status == IGNORED_ARG) ? FALSE : TRUE);

#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        ret = ar_service_call_d_ddd(
              (sint32)ApplID, (sint32)ObjectType, (sint32)ObjectID, (sint32)AR_SVCID_CHECKOBJECTACCESS);
        oa = (ObjectAccessType)((ret == (sint32)AR_SERVICE_CALL_D_DDD0) ? FALSE : TRUE);
    }
    return oa;
}

#endif /*#if (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U) */

#if (AR_ENABLE_CHECK_OBJECT_OWNERSHIP != 0U)

/*---------------------------------------------------------------------------
  CheckObjectOwnership
    service call I/F function
 ---------------------------------------------------------------------------*/
ApplicationType
CheckObjectOwnership(ObjectTypeType object_type, uint32 object_id)
{
    ApplicationType app;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_CHECK_OBJECT_OWNERSHIP == STD_ON)
        app = AR_FNC(CheckObjectOwnership)(object_type, object_id);
#else
        app = (ApplicationType)AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        app = (ApplicationType)ar_service_call_d_dd(
                (sint32)object_type, (sint32)object_id, (sint32)AR_SVCID_CHECKOBJECTOWNERSHIP);
    }
    return app;
}
#endif /* #if (AR_ENABLE_CHECK_OBJECT_OWNERSHIP != 0U) */

/*---------------------------------------------------------------------------
  ControlIdle
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
ControlIdle(CoreIdType core_id, IdleModeType idle_mode)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_CONTROL_IDLE == STD_ON)
        status = AR_FNC(ControlIdle)(core_id, idle_mode);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_dd(
                  (sint32)core_id, (sint32)idle_mode, (sint32)AR_SVCID_CONTROLIDLE);
    }
    return status;
}


/*---------------------------------------------------------------------------
  GetApplicationState
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
GetApplicationState(ApplicationType Application, ApplicationStateRefType Value)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_GET_APPLICATION_STATE == STD_ON)
        status = AR_FNC(GetApplicationState)(Application, Value);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        AR_CHECK_MEMWRITE_APLSTATETYPE(Value);

        status = (StatusType)ar_service_call_d_dp(
                  (sint32)Application, (void *)Value, (sint32)AR_SVCID_GETAPPLICATIONSTATE);
    }
    return status;
}


/*---------------------------------------------------------------------------
  GetActiveApplicationMode
    service call I/F function
 ---------------------------------------------------------------------------*/
AppModeType
GetActiveApplicationMode(void)
{
    AppModeType appmode;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_GET_ACTIVE_APPLICATION_MODE == STD_ON)
        appmode = AR_FNC(GetActiveApplicationMode)();
#else
        appmode = (AppModeType)AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        appmode = (AppModeType)ar_service_call_d_0((sint32)AR_SVCID_GETACTIVEAPPLICATIONMODE);
    }
    return appmode;
}


/*---------------------------------------------------------------------------
  ar_get_errhk_svcid
    service call I/F function
 ---------------------------------------------------------------------------*/
OSServiceIdType
ar_get_errhk_svcid(void)
{
    OSServiceIdType ossrvid;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_ERRORHOOK == STD_ON) && (AR_OS_USE_GETSERVICEID == STD_ON)
        ossrvid = AR_FNC(ar_get_errhk_svcid)();
#else
        ossrvid = (OSServiceIdType)AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        ossrvid = (OSServiceIdType)ar_service_call_d_0((sint32)AR_SVCID_AR_GET_ERRHK_SVCID);
    }
    return ossrvid;
}


/*---------------------------------------------------------------------------
  ar_get_errhk_param
    service call I/F function
 ---------------------------------------------------------------------------*/
uint32
ar_get_errhk_param(uint8 par_num)
{
    uint32 u32;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_ERRORHOOK == STD_ON) && (AR_OS_USE_PARAMETERACCESS == STD_ON)
        u32 = AR_FNC(ar_get_errhk_param)(par_num);
#else
        u32 = (uint32)AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        u32 = (uint32)ar_service_call_d_d(
              (sint32)par_num, (sint32)AR_SVCID_AR_GET_ERRHK_PARAM);
    }
    return u32;
}


/*---------------------------------------------------------------------------
  ShutdownOS
    service call I/F function
 ---------------------------------------------------------------------------*/
void
ShutdownOS(StatusType Error)
{
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_MULTICORE != STD_ON) && (AR_OS_USE_SHUTDOWN_OS == STD_ON)
        AR_FNC(ShutdownOS)(Error);
#else
        (void)AR_FNC(ar_no_support_service)();  /* Do not use the return value of this process. */
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        ar_service_call_0_d(
            (sint32)Error, (sint32)AR_SVCID_SHUTDOWNOS);
    }
}


/*---------------------------------------------------------------------------
  ShutdownAllCores
    service call I/F function
 ---------------------------------------------------------------------------*/
void
ShutdownAllCores(StatusType Error)
{
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_MULTICORE == STD_ON) && (AR_OS_USE_SHUTDOWN_ALL_CORES == STD_ON)
        AR_FNC(ShutdownAllCores)(Error);
#else
        (void)AR_FNC(ar_no_support_service)();  /* Do not use the return value of this process. */
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        ar_service_call_0_d(
            (sint32)Error, (sint32)AR_SVCID_SHUTDOWNALLCORES);
    }
}


/*---------------------------------------------------------------------------
  GetNumberOfActivatedCores
    service call I/F function
 ---------------------------------------------------------------------------*/
uint32
GetNumberOfActivatedCores(void)
{
    uint32 u32;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_MULTICORE == STD_ON) && (AR_OS_USE_GET_NUMBER_OF_ACTIVATED_CORES == STD_ON)
        u32 = AR_FNC(GetNumberOfActivatedCores)();
#else
        u32 = (uint32)AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        u32 = (uint32)ar_service_call_d_0((sint32)AR_SVCID_GETNUMBEROFACTIVATEDCORES);
    }
    return u32;
}


/*---------------------------------------------------------------------------
  ActivateTask
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
ActivateTask(TaskType TaskID)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_TASK == STD_ON) && (AR_OS_USE_ACTIVATE_TASK == STD_ON)
        status = AR_FNC(ActivateTask)(TaskID);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_d((sint32)TaskID,
                                        (sint32)AR_SVCID_ACTIVATETASK);
    }
    return status;
}


/*---------------------------------------------------------------------------
  ActivateTask
    service call I/F function
 ---------------------------------------------------------------------------*/
#if (AR_OS_USE_MULTICORE == STD_ON)
void
ActivateTaskAsyn(TaskType TaskID)
{
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_TASK == STD_ON) && (AR_OS_USE_ACTIVATE_TASK_ASYN == STD_ON)
        AR_FNC(ActivateTaskAsyn)(TaskID);
#else
        (void)AR_FNC(ar_no_support_service)();  /* Do not use the return value of this process. */
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        ar_service_call_0_d((sint32)TaskID,
                                        (sint32)AR_SVCID_ACTIVATETASKASYN);
    }
}
#endif /* (AR_OS_USE_MULTICORE == STD_ON) */

/*---------------------------------------------------------------------------
  TerminateTask
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
TerminateTask(void)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_TASK == STD_ON) && (AR_OS_USE_TERMINATE_TASK == STD_ON)
        status = AR_FNC(TerminateTask)();
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_0((sint32)AR_SVCID_TERMINATETASK);
    }
    return status;
}

#if (AR_ENABLE_CHAIN_TASK != 0U)

/*---------------------------------------------------------------------------
  ChainTask
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
ChainTask(TaskType TaskID)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_TASK == STD_ON) && (AR_OS_USE_CHAIN_TASK == STD_ON)
        status = AR_FNC(ChainTask)(TaskID);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_d(
            (sint32)TaskID, (sint32)AR_SVCID_CHAINTASK);
    }

    return status;
}
#endif /* #if (AR_ENABLE_CHAIN_TASK != 0U) */

/*---------------------------------------------------------------------------
  Schedule
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
Schedule(void)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_TASK == STD_ON) && (AR_OS_USE_SCHEDULE == STD_ON)
        status = AR_FNC(Schedule)();
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_0((sint32)AR_SVCID_SCHEDULE);
    }

    return status;
}

/*---------------------------------------------------------------------------
  GetTaskState
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
GetTaskState(TaskType TaskID, TaskStateRefType State)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_TASK == STD_ON) && (AR_OS_USE_GET_TASK_STATE == STD_ON)
        status = AR_FNC(GetTaskState)(TaskID, State);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        AR_CHECK_MEMWRITE_TASKSTATETYPE(State);

        status = (StatusType)ar_service_call_d_dp(
                (sint32)TaskID, (void *)State, (sint32)AR_SVCID_GETTASKSTATE);
    }

    return status;
}

/*---------------------------------------------------------------------------
  ar_illegal_exit_task
    service call I/F function
 ---------------------------------------------------------------------------*/
void
ar_illegal_exit_task(void)
{
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_TASK == STD_ON)
        AR_FNC(ar_illegal_exit_task)();
#else
        (void)AR_FNC(ar_no_support_service)();  /* Do not use the return value of this process. */
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        ar_service_call_0_0((sint32)AR_SVCID_AR_ILLEGAL_EXIT_TASK);
    }
}


/*---------------------------------------------------------------------------
  SetEvent
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
SetEvent(TaskType task_id, EventMaskType event)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_EXTEND_TASK == STD_ON) && (AR_OS_USE_SET_EVENT == STD_ON)
        status = AR_FNC(SetEvent)(task_id, event);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_dd(
            (sint32)task_id, (sint32)event, (sint32)AR_SVCID_SETEVENT);
    }
    return status;
}

/*---------------------------------------------------------------------------
  SetEventAsyn
    service call I/F function
 ---------------------------------------------------------------------------*/
#if (AR_OS_USE_MULTICORE == STD_ON)
void
SetEventAsyn(TaskType task_id, EventMaskType event)
{
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_EXTEND_TASK == STD_ON) && (AR_OS_USE_SET_EVENT_ASYN == STD_ON)
        AR_FNC(SetEventAsyn)(task_id, event);
#else
        (void)AR_FNC(ar_no_support_service)();  /* Do not use the return value of this process. */
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        ar_service_call_0_dd(
            (sint32)task_id, (sint32)event, (sint32)AR_SVCID_SETEVENTASYN);
    }
}
#endif /* (AR_OS_USE_MULTICORE == STD_ON) */

/*---------------------------------------------------------------------------
  ClearEvent
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
ClearEvent(EventMaskType event)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_EXTEND_TASK == STD_ON) && (AR_OS_USE_CLEAR_EVENT == STD_ON)
        status = AR_FNC(ClearEvent)(event);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_d(
                 (sint32)event, (sint32)AR_SVCID_CLEAREVENT);
    }
    return status;
}


/*---------------------------------------------------------------------------
  GetEvent
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
GetEvent(TaskType task_id, EventMaskRefType p_event)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_EXTEND_TASK == STD_ON) && (AR_OS_USE_GET_EVENT == STD_ON)
        status = AR_FNC(GetEvent)(task_id, p_event);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        AR_CHECK_MEMWRITE_EVENTMASKTYPE(p_event);

        status = (StatusType)ar_service_call_d_dp(
                  (sint32)task_id, (void *)p_event, (sint32)AR_SVCID_GETEVENT);
    }
    return status;
}


/*---------------------------------------------------------------------------
  WaitEvent
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
WaitEvent(EventMaskType event)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_EXTEND_TASK == STD_ON) && (AR_OS_USE_WAIT_EVENT == STD_ON)
        status = AR_FNC(WaitEvent)(event);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_d(
                  (sint32)event, (sint32)AR_SVCID_WAITEVENT);
    }
    return status;
}

/*---------------------------------------------------------------------------
  GetResource
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
GetResource(ResourceType resource_id)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_RESOURCE == STD_ON) && (AR_OS_USE_GET_RESOURCE == STD_ON)
        status = AR_FNC(GetResource)(resource_id);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_d(
                  (sint32)resource_id, (sint32)AR_SVCID_GETRESOURCE);
    }
    return status;
}


/*---------------------------------------------------------------------------
  ReleaseResource
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
ReleaseResource(ResourceType resource_id)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_RESOURCE == STD_ON) && (AR_OS_USE_RELEASE_RESOURCE == STD_ON)
        status = AR_FNC(ReleaseResource)(resource_id);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_d(
            (sint32)resource_id, (sint32)AR_SVCID_RELEASERESOURCE);
    }
    return status;
}


/*---------------------------------------------------------------------------
  IncrementCounter
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
IncrementCounter(CounterType counter_id)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_COUNTER == STD_ON) && (AR_OS_USE_INCREMENT_COUNTER == STD_ON)
        status = AR_FNC(IncrementCounter)(counter_id);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_d(
                  (sint32)counter_id, (sint32)AR_SVCID_INCREMENTCOUNTER);
    }
    return status;
}


/*---------------------------------------------------------------------------
  GetCounterValue
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
GetCounterValue(CounterType counter_id, TickRefType p_value)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_COUNTER == STD_ON) && (AR_OS_USE_GET_COUNTER_VALUE == STD_ON)
        status = AR_FNC(GetCounterValue)(counter_id, p_value);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        AR_CHECK_MEMWRITE_TICKTYPE(p_value);

        status = (StatusType)ar_service_call_d_dp(
                  (sint32)counter_id, (void *)p_value, (sint32)AR_SVCID_GETCOUNTERVALUE);
    }
    return status;
}


/*---------------------------------------------------------------------------
  GetElapsedValue
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
GetElapsedValue(CounterType counter_id, TickRefType p_value, TickRefType p_elapsed_value)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_COUNTER == STD_ON) && (AR_OS_USE_GET_ELAPSED_VALUE == STD_ON)
        status = AR_FNC(GetElapsedValue)(counter_id, p_value, p_elapsed_value);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        AR_CHECK_MEMWRITE_TICKTYPE(p_elapsed_value);
        AR_CHECK_MEMREADWRITE_TICKTYPE(p_value);

        status = (StatusType)ar_service_call_d_dpp(
                  (sint32)counter_id, (void *)p_value, (void *)p_elapsed_value, (sint32)AR_SVCID_GETELAPSEDVALUE);
    }
    return status;
}


/*---------------------------------------------------------------------------
  GetAlarmBase
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
GetAlarmBase(AlarmType alarm_id, AlarmBaseRefType p_info)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_ALARM == STD_ON) && (AR_OS_USE_GET_ALARM_BASE == STD_ON)
        status = AR_FNC(GetAlarmBase)(alarm_id, p_info);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        AR_CHECK_MEMWRITE_TICKTYPE(&p_info->maxallowedvalue);
        AR_CHECK_MEMWRITE_TICKTYPE(&p_info->ticksperbase);
        AR_CHECK_MEMWRITE_TICKTYPE(&p_info->mincycle);

        status = (StatusType)ar_service_call_d_dp(
                  (sint32)alarm_id, (void *)p_info, (sint32)AR_SVCID_GETALARMBASE);
    }
    return status;
}


/*---------------------------------------------------------------------------
  GetAlarm
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
GetAlarm(AlarmType alarm_id, TickRefType p_tick)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_ALARM == STD_ON) && (AR_OS_USE_GET_ALARM == STD_ON)
        status = AR_FNC(GetAlarm)(alarm_id, p_tick);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        AR_CHECK_MEMWRITE_TICKTYPE(p_tick);

        status = (StatusType)ar_service_call_d_dp(
                  (sint32)alarm_id, (void *)p_tick, (sint32)AR_SVCID_GETALARM);
    }
    return status;
}


/*---------------------------------------------------------------------------
  SetRelAlarm
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
SetRelAlarm(AlarmType alarm_id, TickType increment, TickType cycle)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_ALARM == STD_ON) && (AR_OS_USE_SET_REL_ALARM == STD_ON)
        status = AR_FNC(SetRelAlarm)(alarm_id, increment, cycle);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_ddd(
                  (sint32)alarm_id, (sint32)increment, (sint32)cycle, (sint32)AR_SVCID_SETRELALARM);
    }
    return status;
}


/*---------------------------------------------------------------------------
  SetAbsAlarm
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
SetAbsAlarm(AlarmType alarm_id, TickType start, TickType cycle)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_ALARM == STD_ON) && (AR_OS_USE_SET_ABS_ALARM == STD_ON)
        status = AR_FNC(SetAbsAlarm)(alarm_id, start, cycle);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_ddd(
                  (sint32)alarm_id, (sint32)start, (sint32)cycle, (sint32)AR_SVCID_SETABSALARM);
    }
    return status;
}


/*---------------------------------------------------------------------------
  CancelAlarm
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
CancelAlarm(AlarmType alarm_id)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_ALARM == STD_ON) && (AR_OS_USE_CANCEL_ALARM == STD_ON)
        status = AR_FNC(CancelAlarm)(alarm_id);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_d(
                  (sint32)alarm_id, (sint32)AR_SVCID_CANCELALARM);
    }
    return status;
}


/*---------------------------------------------------------------------------
  CallTrustedFunction
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
CallTrustedFunction(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_TRUSTED_FUNCTION == STD_ON)
        status = AR_FNC(CallTrustedFunction)(FunctionIndex, FunctionParams);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_dp(
            (sint32)FunctionIndex, (void *)FunctionParams, (sint32)AR_SVCID_CALLTRUSTEDFUNCTION);
    }
    return status;
}


/*---------------------------------------------------------------------------
  CallFastTrustedFunction
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
CallFastTrustedFunction(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_TRUSTED_FUNCTION == STD_ON) && (AR_OS_USE_CALL_FAST_TRUSTED_FUNCTION == STD_ON)
        status = AR_FNC(CallFastTrustedFunction)(FunctionIndex, FunctionParams);
#else
        status = (StatusType)AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_fast_trusted_function((sint32)FunctionIndex, (void *)FunctionParams);
    }
    return status;
}


/*---------------------------------------------------------------------------
  ar_ioc_send
    service call I/F function
 ---------------------------------------------------------------------------*/
Std_ReturnType
ar_ioc_send(IocType ioc_sender_id, void *in)
{
    Std_ReturnType ret;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_IOC == STD_ON) && (AR_OS_EXIST_QUEUED_IOC == STD_ON)
        ret = AR_FNC(ar_ioc_send)(ioc_sender_id, in);
#else
        ret = (Std_ReturnType)AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        ret = (Std_ReturnType)ar_service_call_d_dp(
            (sint32)ioc_sender_id, (void *)in, (sint32)AR_SVCID_AR_IOC_SEND);
    }
    return ret;
}


/*---------------------------------------------------------------------------
  ar_ioc_write
    service call I/F function
 ---------------------------------------------------------------------------*/
Std_ReturnType
ar_ioc_write(IocType ioc_sender_id, void *in)
{
    Std_ReturnType ret;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_IOC == STD_ON) && (AR_OS_EXIST_UNQUEUED_IOC == STD_ON)
        ret = AR_FNC(ar_ioc_write)(ioc_sender_id, in);
#else
        ret = (Std_ReturnType)AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        ret = (Std_ReturnType)ar_service_call_d_dp(
            (sint32)ioc_sender_id, (void *)in, (sint32)AR_SVCID_AR_IOC_WRITE);
    }
    return ret;
}


/*---------------------------------------------------------------------------
  ar_ioc_receive
    service call I/F function
 ---------------------------------------------------------------------------*/
Std_ReturnType
ar_ioc_receive(IocType receiver_id, void *out)
{
    Std_ReturnType ret;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_IOC == STD_ON) && (AR_OS_EXIST_QUEUED_IOC == STD_ON)
        ret = AR_FNC(ar_ioc_receive)(receiver_id, out);
#else
        ret = (Std_ReturnType)AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        ret = (Std_ReturnType)ar_service_call_d_dp(
                (sint32)receiver_id, (void *)out, (sint32)AR_SVCID_AR_IOC_RECEIVE);
    }
    return ret;
}


/*---------------------------------------------------------------------------
  ar_ioc_read
    service call I/F function
 ---------------------------------------------------------------------------*/
Std_ReturnType
ar_ioc_read(IocType receiver_id, void *out)
{
    Std_ReturnType ret;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_IOC == STD_ON) && (AR_OS_EXIST_UNQUEUED_IOC == STD_ON)
        ret = AR_FNC(ar_ioc_read)(receiver_id, out);
#else
        ret = (Std_ReturnType)AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        ret = (Std_ReturnType)ar_service_call_d_dp(
            (sint32)receiver_id, (void *)out, (sint32)AR_SVCID_AR_IOC_READ);
    }
    return ret;
}


/*---------------------------------------------------------------------------
  ar_ioc_empty_queue
    service call I/F function
 ---------------------------------------------------------------------------*/
Std_ReturnType
ar_ioc_empty_queue(IocType receiver_id)
{
    Std_ReturnType ret;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_IOC == STD_ON) && (AR_OS_EXIST_QUEUED_IOC == STD_ON)
        ret = AR_FNC(ar_ioc_empty_queue)(receiver_id);
#else
        ret = (Std_ReturnType)AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        ret = (Std_ReturnType)ar_service_call_d_d(
              (sint32)receiver_id, (sint32)AR_SVCID_AR_IOC_EMPTY_QUEUE);
    }
    return ret;
}


/*---------------------------------------------------------------------------
  GetSpinlock
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
GetSpinlock(SpinlockIdType spinlock_id)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_SPINLOCK == STD_ON) && (AR_OS_USE_GET_SPINLOCK == STD_ON)
        status = AR_FNC(GetSpinlock)(spinlock_id);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_d(
            (sint32)spinlock_id, (sint32)AR_SVCID_GETSPINLOCK);
    }
    return status;
}

/*---------------------------------------------------------------------------
  GetSpinlockSkipErrorChk
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
GetSpinlockSkipErrorChk(SpinlockIdType spinlock_id)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_SPINLOCK == STD_ON) && (AR_OS_USE_GET_SPINLOCK_SKIP_ERROR_CHK == STD_ON)
        status = AR_FNC(GetSpinlockSkipErrorChk)(spinlock_id);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_d(
            (sint32)spinlock_id, (sint32)AR_SVCID_GETSPINLOCKSKIPERRORCHK);
    }
    return status;
}


/*---------------------------------------------------------------------------
  ReleaseSpinlock
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
ReleaseSpinlock(SpinlockIdType spinlock_id)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_SPINLOCK == STD_ON) && (AR_OS_USE_RELEASE_SPINLOCK == STD_ON)
        status = AR_FNC(ReleaseSpinlock)(spinlock_id);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_d(
                  (sint32)spinlock_id, (sint32)AR_SVCID_RELEASESPINLOCK);
    }
    return status;
}


/*---------------------------------------------------------------------------
  ReleaseSpinlockSkipErrorChk
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
ReleaseSpinlockSkipErrorChk(SpinlockIdType spinlock_id)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_SPINLOCK == STD_ON) && (AR_OS_USE_RELEASE_SPINLOCK_SKIP_ERROR_CHK == STD_ON)
        status = AR_FNC(ReleaseSpinlockSkipErrorChk)(spinlock_id);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_d(
                  (sint32)spinlock_id, (sint32)AR_SVCID_RELEASESPINLOCKSKIPERRORCHK);
    }
    return status;
}


/*---------------------------------------------------------------------------
  TryToGetSpinlock
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
TryToGetSpinlock(SpinlockIdType spinlock_id, TryToGetSpinlockType *p_success)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_SPINLOCK == STD_ON) && (AR_OS_USE_TRY_TO_GET_SPINLOCK == STD_ON)
        status = AR_FNC(TryToGetSpinlock)(spinlock_id, p_success);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        AR_CHECK_MEMWRITE_TRYTOGETSTYPE(p_success);

        status = (StatusType)ar_service_call_d_dp(
                  (sint32)spinlock_id, (void *)p_success, (sint32)AR_SVCID_TRYTOGETSPINLOCK);
    }
    return status;
}


/*---------------------------------------------------------------------------
  TryToGetSpinlockSkipErrorChk
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
TryToGetSpinlockSkipErrorChk(SpinlockIdType spinlock_id, TryToGetSpinlockType *p_success)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_EXIST_SPINLOCK == STD_ON) && (AR_OS_USE_TRY_TO_GET_SPINLOCK_SKIP_ERROR_CHK == STD_ON)
        status = AR_FNC(TryToGetSpinlockSkipErrorChk)(spinlock_id, p_success);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        AR_CHECK_MEMWRITE_TRYTOGETSTYPE(p_success);

        status = (StatusType)ar_service_call_d_dp(
                  (sint32)spinlock_id, (void *)p_success, (sint32)AR_SVCID_TRYTOGETSPINLOCKSKIPERRORCHK);
    }
    return status;
}


/*---------------------------------------------------------------------------
  RaiseInterCoreInterrupt
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
RaiseInterCoreInterrupt(CoreIdType CoreID)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_MULTICORE == STD_ON)
        status = AR_FNC(RaiseInterCoreInterrupt)(CoreID);
#else
        status = AR_FNC(ar_no_support_service)();
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_d(
                  (sint32)CoreID, (sint32)AR_SVCID_RAISEINTERCOREINTERRUPT);
    }
    return status;
}


/*---------------------------------------------------------------------------
  ar_errorhook_call
    service call I/F function
 ---------------------------------------------------------------------------*/
void
ar_errorhook_call(const StatusType status, const OSServiceIdType svcid,
    const ar_errhk_param_t errhk_param[AR_ERRHK_PARAM_NUM])
{
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_ERRORHOOK == STD_ON)
        uint32 idx;
        ar_errhk_param_t rec_errhk_param[AR_ERRHK_PARAM_NUM];

        if (errhk_param != NULL)
        {
            for (idx = 0U; idx < AR_ERRHK_PARAM_NUM; idx++)
            {
                rec_errhk_param[idx] = errhk_param[idx];
            }

            AR_SVC_SUBSTANCE(ar_errorhook_call)(status, svcid, rec_errhk_param);
        }
        else
        {
            AR_SVC_SUBSTANCE(ar_errorhook_call)(status, svcid, NULL);
        }
#else
        (void)AR_FNC(ar_no_support_service)();  /* Do not use the return value of this process. */
#endif
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        ar_service_call_0_ddp_notrace(
            (sint32)status, (sint32)svcid, (const void*)errhk_param, (sint32)AR_SVCID_AR_ERRORHOOK_CALL);
    }
}


/*---------------------------------------------------------------------------
  ReadPeripheral8
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
ReadPeripheral8(AreaIdType Area, const uint8* Address, uint8* ReadValue)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_READ_PERIPHERAL8 == STD_ON)
        status = AR_FNC(ReadPeripheral8)(Area, Address, ReadValue);
#else /* (AR_OS_USE_READ_PERIPHERAL8 == STD_ON) */
        status = AR_FNC(ar_no_support_service)();
#endif /* (AR_OS_USE_READ_PERIPHERAL8 == STD_ON) */
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        AR_CHECK_MEMWRITE_UINT8(ReadValue);
        status = (StatusType)ar_service_call_d_dpp_notrace(
                  (sint32)Area, (const void *)Address, (void *)ReadValue, (sint32)AR_SVCID_READPERIPHERAL8);
    }
    return status;
}


/*---------------------------------------------------------------------------
  ReadPeripheral16
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
ReadPeripheral16(AreaIdType Area, const uint16* Address, uint16* ReadValue)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_READ_PERIPHERAL16 == STD_ON)
        status = AR_FNC(ReadPeripheral16)(Area, Address, ReadValue);
#else /* (AR_OS_USE_READ_PERIPHERAL16 == STD_ON) */
        status = AR_FNC(ar_no_support_service)();
#endif /* (AR_OS_USE_READ_PERIPHERAL16 == STD_ON) */
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        AR_CHECK_MEMWRITE_UINT16(ReadValue);
        status = (StatusType)ar_service_call_d_dpp_notrace(
                  (sint32)Area, (const void *)Address, (void *)ReadValue, (sint32)AR_SVCID_READPERIPHERAL16);
    }
    return status;
}


/*---------------------------------------------------------------------------
  ReadPeripheral32
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
ReadPeripheral32(AreaIdType Area, const uint32* Address, uint32* ReadValue)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_READ_PERIPHERAL32 == STD_ON)
        status = AR_FNC(ReadPeripheral32)(Area, Address, ReadValue);
#else /* (AR_OS_USE_READ_PERIPHERAL32 == STD_ON) */
        status = AR_FNC(ar_no_support_service)();
#endif /* (AR_OS_USE_READ_PERIPHERAL32 == STD_ON) */
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        AR_CHECK_MEMWRITE_UINT32(ReadValue);
        status = (StatusType)ar_service_call_d_dpp_notrace(
                  (sint32)Area, (const void *)Address, (void *)ReadValue, (sint32)AR_SVCID_READPERIPHERAL32);
    }
    return status;
}


/*---------------------------------------------------------------------------
  WritePeripheral8
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
WritePeripheral8(AreaIdType Area, uint8* Address, uint8 WriteValue)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_WRITE_PERIPHERAL8 == STD_ON)
        status = AR_FNC(WritePeripheral8)(Area, Address, WriteValue);
#else /* (AR_OS_USE_WRITE_PERIPHERAL8 == STD_ON) */
        status = AR_FNC(ar_no_support_service)();
#endif /* (AR_OS_USE_WRITE_PERIPHERAL8 == STD_ON) */
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_dpd_notrace(
                  (sint32)Area, (void *)Address, (sint32)WriteValue, (sint32)AR_SVCID_WRITEPERIPHERAL8);
    }
    return status;
}


/*---------------------------------------------------------------------------
  WritePeripheral16
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
WritePeripheral16(AreaIdType Area, uint16* Address, uint16 WriteValue)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_WRITE_PERIPHERAL16 == STD_ON)
        status = AR_FNC(WritePeripheral16)(Area, Address, WriteValue);
#else /* (AR_OS_USE_WRITE_PERIPHERAL16 == STD_ON) */
        status = AR_FNC(ar_no_support_service)();
#endif /* (AR_OS_USE_WRITE_PERIPHERAL16 == STD_ON) */
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_dpd_notrace(
                  (sint32)Area, (void *)Address, (sint32)WriteValue, (sint32)AR_SVCID_WRITEPERIPHERAL16);
    }
    return status;
}


/*---------------------------------------------------------------------------
  WritePeripheral32
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
WritePeripheral32(AreaIdType Area, uint32* Address, uint32 WriteValue)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_WRITE_PERIPHERAL32 == STD_ON)
        status = AR_FNC(WritePeripheral32)(Area, Address, WriteValue);
#else /* (AR_OS_USE_WRITE_PERIPHERAL32 == STD_ON) */
        status = AR_FNC(ar_no_support_service)();
#endif /* (AR_OS_USE_WRITE_PERIPHERAL32 == STD_ON) */
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_dpd_notrace(
                  (sint32)Area, (void *)Address, (sint32)WriteValue, (sint32)AR_SVCID_WRITEPERIPHERAL32);
    }
    return status;
}


/*---------------------------------------------------------------------------
  ModifyPeripheral8
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
ModifyPeripheral8(AreaIdType Area, uint8* Address, uint8 Clearmask, uint8 Setmask)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_MODIFY_PERIPHERAL8 == STD_ON)
        status = AR_FNC(ModifyPeripheral8)(Area, Address, Clearmask, Setmask);
#else /* (AR_OS_USE_MODIFY_PERIPHERAL8 == STD_ON) */
        status = AR_FNC(ar_no_support_service)();
#endif /* (AR_OS_USE_MODIFY_PERIPHERAL8 == STD_ON) */
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_dpdd_notrace(
                  (sint32)Area, (void *)Address, (sint32)Clearmask, (sint32)Setmask, (sint32)AR_SVCID_MODIFYPERIPHERAL8);
    }
    return status;
}


/*---------------------------------------------------------------------------
  ModifyPeripheral16
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
ModifyPeripheral16(AreaIdType Area, uint16* Address, uint16 Clearmask, uint16 Setmask)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_MODIFY_PERIPHERAL16 == STD_ON)
        status = AR_FNC(ModifyPeripheral16)(Area, Address, Clearmask, Setmask);
#else /* (AR_OS_USE_MODIFY_PERIPHERAL16 == STD_ON) */
        status = AR_FNC(ar_no_support_service)();
#endif /* (AR_OS_USE_MODIFY_PERIPHERAL16 == STD_ON) */
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_dpdd_notrace(
                  (sint32)Area, (void *)Address, (sint32)Clearmask, (sint32)Setmask, (sint32)AR_SVCID_MODIFYPERIPHERAL16);
    }
    return status;
}


/*---------------------------------------------------------------------------
  ModifyPeripheral32
    service call I/F function
 ---------------------------------------------------------------------------*/
StatusType
ModifyPeripheral32(AreaIdType Area, uint32* Address, uint32 Clearmask, uint32 Setmask)
{
    StatusType status;
#if XMCOS_AR_USE_SVC_THUNK == STD_ON
    boolean result;

    result = xmcos_ar_can_call_fnc_service();
    if (result != (boolean)FALSE)
    {
#if (AR_OS_USE_MODIFY_PERIPHERAL32 == STD_ON)
        status = AR_FNC(ModifyPeripheral32)(Area, Address, Clearmask, Setmask);
#else /* (AR_OS_USE_MODIFY_PERIPHERAL32 == STD_ON) */
        status = AR_FNC(ar_no_support_service)();
#endif /* (AR_OS_USE_MODIFY_PERIPHERAL32 == STD_ON) */
    }
    else
#endif /* XMCOS_AR_USE_SVC_THUNK == STD_ON */

    {
        status = (StatusType)ar_service_call_d_dpdd_notrace(
                  (sint32)Area, (void *)Address, (sint32)Clearmask, (sint32)Setmask, (sint32)AR_SVCID_MODIFYPERIPHERAL32);
    }
    return status;
}


#define OS_STOP_SEC_CODE_SHARED
#include "Os_MemMap.h"

#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
