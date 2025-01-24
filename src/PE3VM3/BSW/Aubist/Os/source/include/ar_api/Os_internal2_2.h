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
[Os_internal2_2.h] - Os module header
****************************************************************************/

#ifndef OS_INTERNAL2_2_H
#define OS_INTERNAL2_2_H

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

extern void AR_FNC(DisableAllInterrupts)(void);
extern void AR_FNC(EnableAllInterrupts)(void);
extern void AR_FNC(SuspendAllInterrupts)(void);
extern void AR_FNC(ResumeAllInterrupts)(void);
extern void AR_FNC(SuspendOSInterrupts)(void);
extern void AR_FNC(ResumeOSInterrupts)(void);
extern StatusType AR_FNC(DisableInterruptSource)(ISRType ISRID);
extern StatusType AR_FNC(EnableInterruptSource)(ISRType ISRID, boolean ClearPending);
extern StatusType AR_FNC(ClearPendingInterrupt)(ISRType ISRID);
extern AccessType AR_FNC(CheckTaskMemoryAccess)(TaskType TaskID, MemoryStartAddressType Address, MemorySizeType Size);
extern AccessType AR_FNC(CheckISRMemoryAccess)(ISRType ISRID, MemoryStartAddressType Address, MemorySizeType Size);
extern ObjectAccessType AR_FNC(CheckObjectAccess)(ApplicationType ApplID, ObjectTypeType ObjectType, uint32 ObjectID);
extern ApplicationType AR_FNC(CheckObjectOwnership)(ObjectTypeType object_type, uint32 object_id);

/* --- StartScheduleTableRel --- */
/* --- StartScheduleTableAbs --- */
/* --- StopScheduleTable --- */
/* --- NextScheduleTable --- */
/* --- StartScheduleTableSynchron --- */
/* --- SyncScheduleTable --- */
/* --- GetScheduleTableStatus --- */
/* --- SetScheduleTableAsync --- */

extern AppModeType AR_FNC(GetActiveApplicationMode)(void);
extern StatusType AR_FNC(ControlIdle)(CoreIdType core_id, IdleModeType idle_mode);
extern StatusType AR_FNC(GetApplicationState)(ApplicationType Application, ApplicationStateRefType Value);

/* --- TerminateApplication --- */
/* --- AllowAccess --- */

extern OSServiceIdType AR_FNC(ar_get_errhk_svcid)(void);
extern uint32 AR_FNC(ar_get_errhk_param)(uint8 par_num);
extern void AR_FNC(ShutdownOS)(StatusType Error);
extern void AR_FNC(ShutdownAllCores)(StatusType Error);
extern uint32 AR_FNC(GetNumberOfActivatedCores)(void);
extern StatusType AR_FNC(ActivateTask)(TaskType TaskID);
extern void AR_FNC(ActivateTaskAsyn)(TaskType TaskID);
extern StatusType AR_FNC(TerminateTask)(void);
extern StatusType AR_FNC(ChainTask)(TaskType TaskID);
extern StatusType AR_FNC(Schedule)(void);
extern StatusType AR_FNC(GetTaskState)(TaskType TaskID, TaskStateRefType State);
extern void AR_FNC(SetEventAsyn)(TaskType task_id, EventMaskType event);
extern StatusType AR_FNC(SetEvent)(TaskType task_id, EventMaskType event);
extern StatusType AR_FNC(ClearEvent)(EventMaskType event);
extern StatusType AR_FNC(GetEvent)(TaskType task_id, EventMaskRefType p_event);
extern StatusType AR_FNC(WaitEvent)(EventMaskType event);
extern StatusType AR_FNC(GetResource)(ResourceType resource_id);
extern StatusType AR_FNC(ReleaseResource)(ResourceType resource_id);
extern StatusType AR_FNC(IncrementCounter)(CounterType counter_id);
extern StatusType AR_FNC(GetCounterValue)(CounterType counter_id, TickRefType p_value);
extern StatusType AR_FNC(GetElapsedValue)(CounterType counter_id, TickRefType p_value, TickRefType p_elapsed_value);
extern StatusType AR_FNC(GetAlarmBase)(AlarmType alarm_id, AlarmBaseRefType p_info);
extern StatusType AR_FNC(GetAlarm)(AlarmType alarm_id, TickRefType p_tick);
extern StatusType AR_FNC(SetRelAlarm)(AlarmType alarm_id, TickType increment, TickType cycle);
extern StatusType AR_FNC(SetAbsAlarm)(AlarmType alarm_id, TickType start, TickType cycle);
extern StatusType AR_FNC(CancelAlarm)(AlarmType alarm_id);
extern StatusType AR_FNC(CallTrustedFunction)(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams);
extern StatusType AR_FNC(CallFastTrustedFunction)(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams);
extern Std_ReturnType AR_FNC(ar_ioc_send)(IocType ioc_sender_id, void *in);
extern Std_ReturnType AR_FNC(ar_ioc_write)(IocType ioc_sender_id, void *in);
extern Std_ReturnType AR_FNC(ar_ioc_receive)(IocType receiver_id, void *out);
extern Std_ReturnType AR_FNC(ar_ioc_read)(IocType receiver_id, void *out);
extern Std_ReturnType AR_FNC(ar_ioc_empty_queue)(IocType receiver_id);
extern StatusType AR_FNC(GetSpinlock)(SpinlockIdType spinlock_id);
extern StatusType AR_FNC(GetSpinlockSkipErrorChk)(SpinlockIdType spinlock_id);
extern StatusType AR_FNC(ReleaseSpinlock)(SpinlockIdType spinlock_id);
extern StatusType AR_FNC(ReleaseSpinlockSkipErrorChk)(SpinlockIdType spinlock_id);
extern StatusType AR_FNC(TryToGetSpinlock)(SpinlockIdType spinlock_id, TryToGetSpinlockType *p_success);
extern StatusType AR_FNC(TryToGetSpinlockSkipErrorChk)(SpinlockIdType spinlock_id, TryToGetSpinlockType *p_success);
extern StatusType AR_FNC(RaiseInterCoreInterrupt)(CoreIdType CoreID);
extern void AR_FNC(ar_illegal_exit_task)(void);
extern StatusType AR_FNC(ar_no_support_service)(void);
extern StatusType AR_FNC(ReadPeripheral8)(AreaIdType Area, const uint8* Address, uint8* ReadValue);
extern StatusType AR_FNC(ReadPeripheral16)(AreaIdType Area, const uint16* Address, uint16* ReadValue);
extern StatusType AR_FNC(ReadPeripheral32)(AreaIdType Area, const uint32* Address, uint32* ReadValue);
extern StatusType AR_FNC(WritePeripheral8)(AreaIdType Area, uint8* Address, uint8 WriteValue);
extern StatusType AR_FNC(WritePeripheral16)(AreaIdType Area, uint16* Address, uint16 WriteValue);
extern StatusType AR_FNC(WritePeripheral32)(AreaIdType Area, uint32* Address, uint32 WriteValue);
extern StatusType AR_FNC(ModifyPeripheral8)(AreaIdType Area, uint8* Address, uint8 Clearmask, uint8 Setmask);
extern StatusType AR_FNC(ModifyPeripheral16)(AreaIdType Area, uint16* Address, uint16 Clearmask, uint16 Setmask);
extern StatusType AR_FNC(ModifyPeripheral32)(AreaIdType Area, uint32* Address, uint32 Clearmask, uint32 Setmask);

#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)

#define OS_STOP_SEC_CODE_SHARED
#include "Os_MemMap.h"

#else /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

#endif /* OS_INTERNAL2_2_H */
