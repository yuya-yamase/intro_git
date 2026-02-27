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
[Os.h] - Os module header
****************************************************************************/

#ifndef OS_H
#define OS_H

#include "Os_internal1.h"

#include "Os_Cfg.h"

#include "Os_internal2.h"

#include "Rte_Type.h"

#include <mcos/mcos.cfg>

#if (AR_OS_USE_ERRORHOOK == STD_ON)

#if (AR_OS_USE_GETSERVICEID == STD_ON)
#define OSErrorGetServiceId()           ar_get_errhk_svcid()
#endif /* (AR_OS_USE_GETSERVICEID == STD_ON) */

#if (AR_OS_USE_PARAMETERACCESS == STD_ON)

LOCAL_INLINE ar_errhk_param_t ar_get_errhk_param_wrapper(uint8 par_num);

LOCAL_INLINE ar_errhk_param_t ar_get_errhk_param_wrapper(uint8 par_num)
{
    ar_errhk_param_t retval;
    retval.d_uint32 = ar_get_errhk_param(par_num);
    return retval;
}

#define OSError_ActivateTask_TaskID()                   ((TaskType)ar_get_errhk_param_wrapper(0U).d_task)
#define OSError_ActivateTaskAsyn_TaskID()               ((TaskType)ar_get_errhk_param_wrapper(0U).d_task)
#define OSError_ChainTask_TaskID()                      ((TaskType)ar_get_errhk_param_wrapper(0U).d_task)
#define OSError_GetTaskID_TaskID()                      ((TaskRefType)ar_get_errhk_param_wrapper(0U).d_taskref)
#define OSError_GetTaskState_TaskID()                   ((TaskType)ar_get_errhk_param_wrapper(0U).d_task)
#define OSError_GetTaskState_State()                    ((TaskStateRefType)ar_get_errhk_param_wrapper(1U).d_taskstateref)
#define OSError_DisableInterruptSource_DisableISR()     ((ISRType)ar_get_errhk_param_wrapper(0U).d_isr)
#define OSError_EnableInterruptSource_EnableISR()       ((ISRType)ar_get_errhk_param_wrapper(0U).d_isr)
#define OSError_EnableInterruptSource_ClearPending()    ((ISRType)ar_get_errhk_param_wrapper(1U).d_clearpending)
#define OSError_ClearPendingInterrupt_ISRID()           ((ISRType)ar_get_errhk_param_wrapper(0U).d_isr)
#define OSError_GetResource_ResID()                     ((ResourceType)ar_get_errhk_param_wrapper(0U).d_resource)
#define OSError_ReleaseResource_ResID()                 ((ResourceType)ar_get_errhk_param_wrapper(0U).d_resource)
#define OSError_SetEvent_TaskID()                       ((TaskType)ar_get_errhk_param_wrapper(0U).d_task)
#define OSError_SetEvent_Mask()                         ((EventMaskType)ar_get_errhk_param_wrapper(1U).d_eventmask)
#define OSError_SetEventAsyn_TaskID()                   ((TaskType)ar_get_errhk_param_wrapper(0U).d_task)
#define OSError_SetEventAsyn_Mask()                     ((EventMaskType)ar_get_errhk_param_wrapper(1U).d_eventmask)
#define OSError_ClearEvent_Mask()                       ((EventMaskType)ar_get_errhk_param_wrapper(0U).d_eventmask)
#define OSError_GetEvent_TaskID()                       ((TaskType)ar_get_errhk_param_wrapper(0U).d_task)
#define OSError_GetEvent_Event()                        ((EventMaskRefType)ar_get_errhk_param_wrapper(1U).d_eventmaskref)
#define OSError_WaitEvent_Mask()                        ((EventMaskType)ar_get_errhk_param_wrapper(0U).d_eventmask)
#define OSError_GetAlarmBase_AlarmID()                  ((AlarmType)ar_get_errhk_param_wrapper(0U).d_alarm)
#define OSError_GetAlarmBase_Info()                     ((AlarmBaseRefType)ar_get_errhk_param_wrapper(1U).d_alarmbaseref)
#define OSError_GetAlarm_AlarmID()                      ((AlarmType)ar_get_errhk_param_wrapper(0U).d_alarm)
#define OSError_GetAlarm_Tick()                         ((TickRefType)ar_get_errhk_param_wrapper(1U).d_tickref)
#define OSError_SetRelAlarm_AlarmID()                   ((AlarmType)ar_get_errhk_param_wrapper(0U).d_alarm)
#define OSError_SetRelAlarm_increment()                 ((TickType)ar_get_errhk_param_wrapper(1U).d_tick)
#define OSError_SetRelAlarm_cycle()                     ((TickType)ar_get_errhk_param_wrapper(2U).d_tick)
#define OSError_SetAbsAlarm_AlarmID()                   ((AlarmType)ar_get_errhk_param_wrapper(0U).d_alarm)
#define OSError_SetAbsAlarm_start()                     ((TickType)ar_get_errhk_param_wrapper(1U).d_tick)
#define OSError_SetAbsAlarm_cycle()                     ((TickType)ar_get_errhk_param_wrapper(2U).d_tick)
#define OSError_CancelAlarm_AlarmID()                   ((AlarmType)ar_get_errhk_param_wrapper(0U).d_alarm)
#define OSError_StartOS_Mode()                          ((AppModeType)ar_get_errhk_param_wrapper(0U).d_appmode)
#define OSError_ShutdownOS_Error()                      ((StatusType)ar_get_errhk_param_wrapper(0U).d_status)
#define OSError_CallTrustedFunction_FunctionIndex()     ((TrustedFunctionIndexType)ar_get_errhk_param_wrapper(0U).d_trustedfunctionindex)
#define OSError_CallTrustedFunction_FunctionParams()    ((TrustedFunctionParameterRefType)ar_get_errhk_param_wrapper(1U).d_trustedfunctionparameterref)
#define OSError_CallFastTrustedFunction_FunctionIndex() ((TrustedFunctionIndexType)ar_get_errhk_param_wrapper(0U).d_trustedfunctionindex)
#define OSError_CallFastTrustedFunction_FunctionParams() ((TrustedFunctionParameterRefType)ar_get_errhk_param_wrapper(1U).d_trustedfunctionparameterref)
#define OSError_CheckObjectAccess_ApplID()              ((ApplicationType)ar_get_errhk_param_wrapper(0U).d_application)
#define OSError_CheckObjectAccess_ObjectType()          ((ObjectTypeType)ar_get_errhk_param_wrapper(1U).d_objecttype)
#define OSError_CheckObjectAccess_ObjectID()            ((uint32)ar_get_errhk_param_wrapper(2U).d_uint32)
#define OSError_CheckObjectOwnership_ObjectType()       ((ObjectTypeType)ar_get_errhk_param_wrapper(0U).d_objecttype)
#define OSError_CheckObjectOwnership_ObjectID()         ((uint32)ar_get_errhk_param_wrapper(1U).d_uint32)
#define OSError_IncrementCounter_CounterID()            ((CounterType)ar_get_errhk_param_wrapper(0U).d_counter)
#define OSError_GetCounterValue_CounterID()             ((CounterType)ar_get_errhk_param_wrapper(0U).d_counter)
#define OSError_GetCounterValue_Value()                 ((TickRefType)ar_get_errhk_param_wrapper(1U).d_tickref)
#define OSError_GetElapsedValue_CounterID()             ((CounterType)ar_get_errhk_param_wrapper(0U).d_counter)
#define OSError_GetElapsedValue_Value()                 ((TickRefType)ar_get_errhk_param_wrapper(1U).d_tickref)
#define OSError_GetElapsedValue_ElapsedValue()          ((TickRefType)ar_get_errhk_param_wrapper(2U).d_tickref)
#define OSError_GetApplicationState_Application()       ((ApplicationType)ar_get_errhk_param_wrapper(0U).d_application)
#define OSError_GetApplicationState_Value()             ((ApplicationStateRefType)ar_get_errhk_param_wrapper(1U).d_applicationstateref)
#define OSError_ControlIdle_CoreID()                    ((CoreIdType)ar_get_errhk_param_wrapper(0U).d_coreid)
#define OSError_ControlIdle_IdleMode()                  ((IdleModeType)ar_get_errhk_param_wrapper(1U).d_idlemode)
#define OSError_IocSend_IocId()                         ((IocType)ar_get_errhk_param_wrapper(0U).d_ioc)
#define OSError_IocSend_SenderId()                      ((IocType)ar_get_errhk_param_wrapper(1U).d_ioc)
#define OSError_IocWrite_IocId()                        ((IocType)ar_get_errhk_param_wrapper(0U).d_ioc)
#define OSError_IocWrite_SenderId()                     ((IocType)ar_get_errhk_param_wrapper(1U).d_ioc)
#define OSError_IocSendGroup_IocId()                    ((IocType)ar_get_errhk_param_wrapper(0U).d_ioc)
#define OSError_IocSendGroup_SenderId()                 ((IocType)ar_get_errhk_param_wrapper(1U).d_ioc)
#define OSError_IocWriteGroup_IocId()                   ((IocType)ar_get_errhk_param_wrapper(0U).d_ioc)
#define OSError_IocWriteGroup_SenderId()                ((IocType)ar_get_errhk_param_wrapper(1U).d_ioc)
#define OSError_IocReceive_IocId()                      ((IocType)ar_get_errhk_param_wrapper(0U).d_ioc)
#define OSError_IocRead_IocId()                         ((IocType)ar_get_errhk_param_wrapper(0U).d_ioc)
#define OSError_IocReceiveGroup_IocId()                 ((IocType)ar_get_errhk_param_wrapper(0U).d_ioc)
#define OSError_IocReadGroup_IocId()                    ((IocType)ar_get_errhk_param_wrapper(0U).d_ioc)
#define OSError_IocEmptyQueue_IocId()                   ((IocType)ar_get_errhk_param_wrapper(0U).d_ioc)
#define OSError_StartCore_CoreID()                      ((CoreIdType)ar_get_errhk_param_wrapper(0U).d_coreid)
#define OSError_StartCore_Status()                      ((StatusType *)ar_get_errhk_param_wrapper(1U).d_statusref)
#define OSError_StartNonAutosarCore_CoreID()            ((CoreIdType)ar_get_errhk_param_wrapper(0U).d_coreid)
#define OSError_StartNonAutosarCore_Status()            ((StatusType *)ar_get_errhk_param_wrapper(1U).d_statusref)
#define OSError_GetSpinlock_SpinlockId()                ((SpinlockIdType)ar_get_errhk_param_wrapper(0U).d_spinlockid)
#define OSError_ReleaseSpinlock_SpinlockId()            ((SpinlockIdType)ar_get_errhk_param_wrapper(0U).d_spinlockid)
#define OSError_TryToGetSpinlock_SpinlockId()           ((SpinlockIdType)ar_get_errhk_param_wrapper(0U).d_spinlockid)
#define OSError_TryToGetSpinlock_Success()              ((TryToGetSpinlockType *)ar_get_errhk_param_wrapper(1U).d_trytogetspinlockref)
#define OSError_ShutdownAllCores_Error()                ((StatusType)ar_get_errhk_param_wrapper(0U).d_status)
#define OSError_RaiseInterCoreInterrupt_CoreID()        ((CoreIdType)ar_get_errhk_param_wrapper(0U).d_coreid)
#define OSError_CheckTaskMemoryAccess_TaskID()          ((TaskType)ar_get_errhk_param_wrapper(0U).d_task)
#define OSError_CheckTaskMemoryAccess_Address()         ((MemoryStartAddressType)ar_get_errhk_param_wrapper(1U).d_memorystartaddress)
#define OSError_CheckTaskMemoryAccess_Size()            ((MemorySizeType)ar_get_errhk_param_wrapper(2U).d_memorysize)
#define OSError_CheckISRMemoryAccess_ISRID()            ((ISRType)ar_get_errhk_param_wrapper(0U).d_isr)
#define OSError_CheckISRMemoryAccess_Address()          ((MemoryStartAddressType)ar_get_errhk_param_wrapper(1U).d_memorystartaddress)
#define OSError_CheckISRMemoryAccess_Size()             ((MemorySizeType)ar_get_errhk_param_wrapper(2U).d_memorysize)
#define OSError_ReadPeripheralX_AreaID()                ((AreaIdType)ar_get_errhk_param_wrapper(0U).d_areaid)
#define OSError_ReadPeripheralX_Address()               ((uint32 const *)ar_get_errhk_param_wrapper(1U).d_address)
#define OSError_ReadPeripheralX_ReadValue()             ((uint32*)ar_get_errhk_param_wrapper(2U).d_readvalue)
#define OSError_WritePeripheralX_AreaID()               ((AreaIdType)ar_get_errhk_param_wrapper(0U).d_areaid)
#define OSError_WritePeripheralX_Address()              ((uint32 const *)ar_get_errhk_param_wrapper(1U).d_address)
#define OSError_WritePeripheralX_Value()                ((uint32)ar_get_errhk_param_wrapper(2U).d_value)
#define OSError_ModifyPeripheralX_AreaID()              ((AreaIdType)ar_get_errhk_param_wrapper(0U).d_areaid)
#define OSError_ModifyPeripheralX_Address()             ((uint32 const *)ar_get_errhk_param_wrapper(1U).d_address)
#define OSError_ModifyPeripheralX_Clearmask()           ((uint32)ar_get_errhk_param_wrapper(2U).d_clearmask)
#define OSError_ModifyPeripheralX_Setmask()             ((uint32)ar_get_errhk_param_wrapper(2U).d_setmask)


#endif /* (AR_OS_USE_PARAMETERACCESS == STD_ON) */

#endif /* (AR_OS_USE_ERRORHOOK == STD_ON) */

#if (MCOS_CFG_THR_MAX < AR_OS_NUM_TASKS_PER_CORE_MAX)
#error Decrease the number of Tasks per core or increase MCOS_CFG_THR_MAX.
#endif /* (MCOS_CFG_THR_MAX < AR_OS_NUM_TASKS_PER_CORE_MAX) */

#if (MCOS_CFG_THR_ACT_MAX < AR_OS_ACT_COUNT_PER_CORE_MAX)
/* warning:  Depending on the count of activations of Task, it may not be possible to execute normally. Decrease the sum of OsTaskActivation value per core or increase MCOS_CFG_THR_ACT_MAX. */
#endif /* (MCOS_CFG_THR_ACT_MAX < AR_OS_ACT_COUNT_PER_CORE_MAX) */

#endif /* OS_H */
