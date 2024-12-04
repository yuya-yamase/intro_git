/*
    Copyright (C) 2022 By eSOL Co.,Ltd. Tokyo, Japan

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
[Os_internal2_1.h] - Os module header
****************************************************************************/

#ifndef OS_INTERNAL2_1_H
#define OS_INTERNAL2_1_H

/*
 * followings use Configuration Information
 *
 */
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)

#define OS_START_SEC_CODE_SHARED
#include "Os_MemMap.h"

#else /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

extern StatusType ActivateTask(TaskType TaskID);
extern void ActivateTaskAsyn(TaskType TaskID);
extern StatusType TerminateTask(void);
extern StatusType ChainTask(TaskType TaskID);
extern StatusType Schedule(void);
extern StatusType GetTaskState(TaskType TaskID, TaskStateRefType State);
extern void ar_illegal_exit_task(void);

extern void DisableAllInterrupts(void);
extern void EnableAllInterrupts(void);
extern void SuspendAllInterrupts(void);
extern void ResumeAllInterrupts(void);
extern void SuspendOSInterrupts(void);
extern void ResumeOSInterrupts(void);
extern StatusType DisableInterruptSource(ISRType ISRID);
extern StatusType EnableInterruptSource(ISRType ISRID, boolean ClearPending);
extern StatusType ClearPendingInterrupt(ISRType ISRID);

extern StatusType GetResource(ResourceType resource_id);
extern StatusType ReleaseResource(ResourceType resource_id);

extern StatusType SetEvent(TaskType task_id, EventMaskType event);
extern void SetEventAsyn(TaskType task_id, EventMaskType event);
extern StatusType ClearEvent(EventMaskType event);
extern StatusType GetEvent(TaskType task_id, EventMaskRefType p_event);
extern StatusType WaitEvent(EventMaskType event);

extern StatusType GetAlarmBase(AlarmType alarm_id, AlarmBaseRefType p_info);
extern StatusType GetAlarm(AlarmType alarm_id, TickRefType p_tick);
extern StatusType SetRelAlarm(AlarmType alarm_id, TickType increment, TickType cycle);
extern StatusType SetAbsAlarm(AlarmType alarm_id, TickType start, TickType cycle);
extern StatusType CancelAlarm(AlarmType alarm_id);

extern AppModeType GetActiveApplicationMode(void);
extern void ShutdownOS(StatusType Error);

extern StatusType CallTrustedFunction(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams);
extern StatusType CallFastTrustedFunction(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams);
extern AccessType CheckISRMemoryAccess(ISRType ISRID, MemoryStartAddressType Address, MemorySizeType Size);
extern AccessType CheckTaskMemoryAccess( TaskType TaskID, MemoryStartAddressType Address, MemorySizeType Size);
extern ObjectAccessType CheckObjectAccess(ApplicationType ApplID, ObjectTypeType ObjectType, uint32 ObjectID);
extern ApplicationType CheckObjectOwnership(ObjectTypeType object_type, uint32 object_id);

/* --- StartScheduleTableRel --- */
/* --- StartScheduleTableAbs --- */
/* --- StopScheduleTable --- */
/* --- NextScheduleTable --- */
/* --- StartScheduleTableSynchron --- */
/* --- SyncScheduleTable --- */
/* --- GetScheduleTableStatus --- */
/* --- SetScheduleTableAsync --- */

extern StatusType IncrementCounter(CounterType counter_id);
extern StatusType GetCounterValue(CounterType counter_id, TickRefType p_value);
extern StatusType GetElapsedValue(CounterType counter_id, TickRefType p_value, TickRefType p_elapsed_value);

/* --- TerminateApplication --- */
/* --- AllowAccess --- */

extern StatusType GetApplicationState(ApplicationType Application, ApplicationStateRefType Value);
extern StatusType ControlIdle(CoreIdType core_id, IdleModeType idle_mode);

extern uint32 GetNumberOfActivatedCores(void);
extern StatusType GetSpinlock(SpinlockIdType spinlock_id);
extern StatusType GetSpinlockSkipErrorChk(SpinlockIdType spinlock_id);
extern StatusType ReleaseSpinlock(SpinlockIdType spinlock_id);
extern StatusType ReleaseSpinlockSkipErrorChk(SpinlockIdType spinlock_id);
extern StatusType TryToGetSpinlock(SpinlockIdType spinlock_id, TryToGetSpinlockType *p_success);
extern StatusType TryToGetSpinlockSkipErrorChk(SpinlockIdType spinlock_id, TryToGetSpinlockType *p_success);
extern void ShutdownAllCores(StatusType Error);

extern StatusType RaiseInterCoreInterrupt(CoreIdType CoreID);

extern OSServiceIdType ar_get_errhk_svcid(void);
extern uint32 ar_get_errhk_param(uint8 par_num);

extern Std_ReturnType ar_ioc_send(IocType ioc_sender_id, void *in);
extern Std_ReturnType ar_ioc_write(IocType ioc_sender_id, void *in);
extern Std_ReturnType ar_ioc_receive(IocType receiver_id, void *out);
extern Std_ReturnType ar_ioc_read(IocType receiver_id, void *out);
extern Std_ReturnType ar_ioc_empty_queue(IocType receiver_id);

extern StatusType ReadPeripheral8(AreaIdType Area, const uint8* Address, uint8* ReadValue);
extern StatusType ReadPeripheral16(AreaIdType Area, const uint16* Address, uint16* ReadValue);
extern StatusType ReadPeripheral32(AreaIdType Area, const uint32* Address, uint32* ReadValue);
extern StatusType WritePeripheral8(AreaIdType Area, uint8* Address, uint8 WriteValue);
extern StatusType WritePeripheral16(AreaIdType Area, uint16* Address, uint16 WriteValue);
extern StatusType WritePeripheral32(AreaIdType Area, uint32* Address, uint32 WriteValue);
extern StatusType ModifyPeripheral8(AreaIdType Area, uint8* Address, uint8 Clearmask, uint8 Setmask);
extern StatusType ModifyPeripheral16(AreaIdType Area, uint16* Address, uint16 Clearmask, uint16 Setmask);
extern StatusType ModifyPeripheral32(AreaIdType Area, uint32* Address, uint32 Clearmask, uint32 Setmask);

#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)

#define OS_STOP_SEC_CODE_SHARED
#include "Os_MemMap.h"

#else /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */


#endif /* OS_INTERNAL2_1_H */
