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
[ ar_kernel_impl.h ] - MCOS AUTOSAR kernel implementation header
****************************************************************************/

#ifndef AR_KERNEL_IMPL_H
#define AR_KERNEL_IMPL_H

#include <mcos/mcos_ar_switch.h>
#include <mcos/mcos.h>
#include <mcos_mk.h>
#include "Os_internal.h"
#include "ar_mcos_local.h"
#include <mcos/mcos_ar_hook_code.h>
#include "ar_user_cfg_def.h"

#ifdef __cplusplus
extern "C" {
#endif

#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)

#define AR_SVC_ENTITY(name) name ## Entity
#define AR_SVC_SUBSTANCE(name) name ## Entity
#define AR_SVC_FUNC extern

#else /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

#if MCOS_CFG_DS_TRACE_LOG_API
#define AR_SVC_ENTITY(name) name ## Entity
#define AR_SVC_FUNC AR_LOCAL_FORCE_INLINE
#else /* MCOS_CFG_DS_TRACE_LOG_API */
#define AR_SVC_ENTITY(name) name
#define AR_SVC_FUNC
#endif /* MCOS_CFG_DS_TRACE_LOG_API */

#define AR_SVC_SUBSTANCE(name) name

#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */


#if ((AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) || MCOS_CFG_DS_TRACE_LOG_API)

#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
#define OS_START_SEC_CODE_SHARED
#include "Os_MemMap.h"
#else /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
#define OS_START_SEC_CODE
#include "Os_MemMap.h"
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
extern void ar_errorhook_call(const StatusType status, const OSServiceIdType svcid, const ar_errhk_param_t errhk_param[AR_ERRHK_PARAM_NUM]);
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
#define OS_STOP_SEC_CODE_SHARED
#include "Os_MemMap.h"
#else /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

#endif /* ((AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) || MCOS_CFG_DS_TRACE_LOG_API) */

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

/*
 * Prototypes of Service Call Entities
 */
extern void AR_SVC_SUBSTANCE(ar_errorhook_call)(const StatusType status, const OSServiceIdType svcid, const ar_errhk_param_t errhk_param[AR_ERRHK_PARAM_NUM]);

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#if ((AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) || MCOS_CFG_DS_TRACE_LOG_API)

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

/*
 * Prototypes of Service Call Entities
 */
AR_SVC_FUNC void AR_SVC_ENTITY(EnableAllInterrupts)(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC void AR_SVC_ENTITY(DisableAllInterrupts)(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC void AR_SVC_ENTITY(ResumeAllInterrupts)(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC void AR_SVC_ENTITY(SuspendAllInterrupts)(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC void AR_SVC_ENTITY(ResumeOSInterrupts)(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC void AR_SVC_ENTITY(SuspendOSInterrupts)(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(DisableInterruptSource)(ISRType ISRID
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(EnableInterruptSource)(ISRType ISRID, boolean ClearPending
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(ClearPendingInterrupt)(ISRType ISRID
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
#if (AR_ENABLE_CHECK_TASK_MEMORY_ACCESS != 0U)
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
AR_SVC_FUNC AccessType AR_SVC_ENTITY(CheckTaskMemoryAccess)(TaskType TaskID, MemoryStartAddressType Address, MemorySizeType Size
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
#endif /* #if (AR_ENABLE_CHECK_TASK_MEMORY_ACCESS != 0U) */
#if (AR_ENABLE_CHECK_ISR_MEMORY_ACCESS != 0U)
AR_SVC_FUNC AccessType AR_SVC_ENTITY(CheckISRMemoryAccess)(ISRType ISRID, MemoryStartAddressType Address, MemorySizeType Size
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
#endif /* #if (AR_ENABLE_CHECK_ISR_MEMORY_ACCESS != 0U) */
#if (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U)
AR_SVC_FUNC ObjectAccessType AR_SVC_ENTITY(CheckObjectAccess)(ApplicationType ApplID, ObjectTypeType ObjectType, uint32 ObjectID
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
#endif /* #if (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U) */
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
#if (AR_ENABLE_CHECK_OBJECT_OWNERSHIP != 0U)
AR_SVC_FUNC ApplicationType AR_SVC_ENTITY(CheckObjectOwnership)(ObjectTypeType object_type, uint32 object_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
#endif /* #if (AR_ENABLE_CHECK_OBJECT_OWNERSHIP != 0U) */
AR_SVC_FUNC StatusType AR_SVC_ENTITY(ControlIdle)(CoreIdType core_id, IdleModeType idle_mode
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC ApplicationType AR_SVC_ENTITY(GetApplicationID)(void);
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
AR_SVC_FUNC StatusType AR_SVC_ENTITY(GetApplicationState)(ApplicationType Application, ApplicationStateRefType Value
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
AR_SVC_FUNC AppModeType AR_SVC_ENTITY(GetActiveApplicationMode)(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );

AR_SVC_FUNC OSServiceIdType AR_SVC_ENTITY(ar_get_errhk_svcid)(void);

AR_SVC_FUNC uint32 AR_SVC_ENTITY(ar_get_errhk_param)(uint8 par_num);
AR_SVC_FUNC void AR_SVC_ENTITY(ShutdownOS)(StatusType Error
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC void AR_SVC_ENTITY(ShutdownAllCores)(StatusType Error
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC uint32 AR_SVC_ENTITY(GetNumberOfActivatedCores)(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(ActivateTask)(TaskType TaskID
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC void AR_SVC_ENTITY(ActivateTaskAsyn)(TaskType TaskID
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );

AR_SVC_FUNC StatusType AR_SVC_ENTITY(TerminateTask)(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
#if (AR_ENABLE_CHAIN_TASK != 0U)
AR_SVC_FUNC StatusType AR_SVC_ENTITY(ChainTask)(TaskType TaskID
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
#endif /* #if (AR_ENABLE_CHAIN_TASK != 0U) */
AR_SVC_FUNC StatusType AR_SVC_ENTITY(Schedule)(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(GetTaskState)(TaskType TaskID, TaskStateRefType State
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC void AR_SVC_ENTITY(ar_illegal_exit_task)(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(SetEvent)(TaskType task_id, EventMaskType event
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC void AR_SVC_ENTITY(SetEventAsyn)(TaskType task_id, EventMaskType event
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(ClearEvent)(EventMaskType event
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(GetEvent)(TaskType task_id, EventMaskRefType p_event
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(WaitEvent)(EventMaskType event
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(GetResource)(ResourceType resource_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(ReleaseResource)(ResourceType resource_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(IncrementCounter)(CounterType counter_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(GetCounterValue)(CounterType counter_id, TickRefType p_value
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(GetElapsedValue)(CounterType counter_id, TickRefType p_value, TickRefType p_elapsed_value
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(GetAlarmBase)(AlarmType alarm_id, AlarmBaseRefType p_info
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(GetAlarm)(AlarmType alarm_id, TickRefType p_tick
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(SetRelAlarm)(AlarmType alarm_id, TickType increment, TickType cycle
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(SetAbsAlarm)(AlarmType alarm_id, TickType start, TickType cycle
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(CancelAlarm)(AlarmType alarm_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
AR_SVC_FUNC StatusType AR_SVC_ENTITY(CallTrustedFunction)(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(CallFastTrustedFunction)(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
AR_SVC_FUNC Std_ReturnType AR_SVC_ENTITY(ar_ioc_send)(IocType ioc_sender_id, void *in
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC Std_ReturnType AR_SVC_ENTITY(ar_ioc_write)(IocType ioc_sender_id, void *in
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC Std_ReturnType AR_SVC_ENTITY(ar_ioc_receive)(IocType receiver_id, void *out
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC Std_ReturnType AR_SVC_ENTITY(ar_ioc_read)(IocType receiver_id, void *out
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC Std_ReturnType AR_SVC_ENTITY(ar_ioc_empty_queue)(IocType receiver_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(GetSpinlock)(SpinlockIdType spinlock_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(GetSpinlockSkipErrorChk)(SpinlockIdType spinlock_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(ReleaseSpinlock)(SpinlockIdType spinlock_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(ReleaseSpinlockSkipErrorChk)(SpinlockIdType spinlock_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(TryToGetSpinlock)(SpinlockIdType spinlock_id, TryToGetSpinlockType *p_success
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(TryToGetSpinlockSkipErrorChk)(SpinlockIdType spinlock_id, TryToGetSpinlockType *p_success
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(RaiseInterCoreInterrupt)(CoreIdType CoreID
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(ReadPeripheral8)(AreaIdType Area, const uint8* Address, uint8* ReadValue
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(ReadPeripheral16)(AreaIdType Area, const uint16* Address, uint16* ReadValue
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(ReadPeripheral32)(AreaIdType Area, const uint32* Address, uint32* ReadValue
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(WritePeripheral8)(AreaIdType Area, uint8* Address, uint8 WriteValue
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(WritePeripheral16)(AreaIdType Area, uint16* Address, uint16 WriteValue
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(WritePeripheral32)(AreaIdType Area, uint32* Address, uint32 WriteValue
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(ModifyPeripheral8)(AreaIdType Area, uint8* Address, uint8 Clearmask, uint8 Setmask
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(ModifyPeripheral16)(AreaIdType Area, uint16* Address, uint16 Clearmask, uint16 Setmask
    );
AR_SVC_FUNC StatusType AR_SVC_ENTITY(ModifyPeripheral32)(AreaIdType Area, uint32* Address, uint32 Clearmask, uint32 Setmask
    );


#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#endif /* ((AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) || MCOS_CFG_DS_TRACE_LOG_API) */

#if (AR_ENABLE_CHECK_OBJECT_OWNERSHIP != 0U) || (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U)
/*
 * Prototypes
 */
#define OS_START_SEC_CODE
#include "Os_MemMap.h"

#if (AR_ENABLE_CHECK_OBJECT_OWNERSHIP != 0U)
extern ApplicationType ar_CheckTaskOwnership(uint32 object_id);
extern ApplicationType ar_CheckISROwnership(uint32 object_id);
extern ApplicationType ar_CheckAlarmOwnership(uint32 object_id);
extern ApplicationType ar_CheckCounterOwnership(uint32 object_id);
#endif /* #if (AR_ENABLE_CHECK_OBJECT_OWNERSHIP != 0U) */

#if (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U)
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
extern ObjectAccessType ar_CheckTaskAccess(ApplicationType ApplID, TaskType TaskID);
extern ObjectAccessType ar_CheckISRAccess(ApplicationType ApplID, ISRType ISRID);
extern ObjectAccessType ar_CheckAlarmAccess(ApplicationType ApplID, AlarmType alarm_id);
extern ObjectAccessType ar_CheckCounterAccess(ApplicationType ApplID, CounterType CounterID);
extern ObjectAccessType ar_CheckResourceAccess(ApplicationType ApplID, ResourceType ResourceID);
extern ObjectAccessType ar_CheckSpinlockAccess(ApplicationType ApplID, SpinlockIdType spinlock_id);
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
#endif /* #if (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U) */

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#endif /* #if (AR_ENABLE_CHECK_OBJECT_OWNERSHIP != 0U) || (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U) */

#define GENNAME_TASK(TaskName)  ar_task_entry_ ## TaskName
#define GENNAME_ISR(ISRName)    ar_isr_entry_  ## ISRName
#define GENNAME_ALARMCALLBACK(AlarmCallBackName) \
    ar_alarm_entry_ ## AlarmCallBackName
#define GENNAME_C1ISR(ISRName)  ar_c1isr_entry_  ## ISRName
#define GENNAME_TRUSTEDFUNC(TrustedFunctionName) \
    ar_tfn_entry_ ## TrustedFunctionName

/*
 * Application Mode
 */
#define AR_APPMODE_NONE     ((AppModeType) 0)

#define AR_INTSTS_NULL                 ((uint32) 0x0000U)
#define AR_INTSTS_DISABLEALLINTERUPTS  ((uint32) 0x2000U)
#define AR_INTSTS_SUSPENDALLINTERRUPTS ((uint32) 0x4000U)
#define AR_INTSTS_SUSPENDOSINTERRUPTS  ((uint32) 0x8000U)
#define AR_INTSTS_MASK                 ((uint32) 0xf000U)

AR_LOCAL_FORCE_INLINE void AR_CALL_LEVEL_ENTER(clscb_t * const clscb, uint32 bit);
AR_LOCAL_FORCE_INLINE void AR_CALL_LEVEL_ENTER(clscb_t * const clscb, uint32 bit)
{
    clscb_t * const clscb_tmp = (clscb);
    (clscb_tmp)->aroscb.call_level = (uint16)((uint32)((clscb_tmp)->aroscb.call_level) | (uint32)(bit));
}

AR_LOCAL_FORCE_INLINE void AR_CALL_LEVEL_EXIT(clscb_t * const clscb, uint32 bit);
AR_LOCAL_FORCE_INLINE void AR_CALL_LEVEL_EXIT(clscb_t * const clscb, uint32 bit)
{
    clscb_t * const clscb_tmp = (clscb);
    (clscb_tmp)->aroscb.call_level = (uint16)((uint32)((clscb_tmp)->aroscb.call_level) &  ~(uint32)(bit));
}

#define AR_CALL_LEVEL_ACTIVATETASK          (AR_CL_TASK | AR_CL_C2ISR)
#define AR_CALL_LEVEL_TERMINATETASK         (AR_CL_TASK)
#define AR_CALL_LEVEL_CHAINTASK             (AR_CL_TASK)
#define AR_CALL_LEVEL_SCHEDULE              (AR_CL_TASK)
#define AR_CALL_LEVEL_GETTASKID \
    (AR_INTSTS_DISABLEALLINTERUPTS | AR_INTSTS_SUSPENDALLINTERRUPTS | AR_INTSTS_SUSPENDOSINTERRUPTS | \
    AR_CL_TASK | AR_CL_C2ISR | AR_CL_HK_ERROR | AR_CL_HK_PREPOST | AR_CL_HK_PROT | AR_CL_SYS_HK_BIT)
#define AR_CALL_LEVEL_GETTASKSTATE \
    (AR_CL_TASK | AR_CL_C2ISR | AR_CL_HK_ERROR | AR_CL_HK_PREPOST | AR_CL_SYS_HK_BIT)
#define AR_CALL_LEVEL_GETRESOURCE           (AR_CL_TASK | AR_CL_C2ISR)
#define AR_CALL_LEVEL_RELEASERESOURCE       (AR_CL_TASK | AR_CL_C2ISR)
#define AR_CALL_LEVEL_SETEVENT              (AR_CL_TASK | AR_CL_C2ISR)
#define AR_CALL_LEVEL_CLEAREVENT            (AR_CL_TASK)
#define AR_CALL_LEVEL_GETEVENT \
    (AR_CL_TASK | AR_CL_C2ISR | AR_CL_HK_ERROR | AR_CL_HK_PREPOST | AR_CL_SYS_HK_BIT)
#define AR_CALL_LEVEL_WAITEVENT             (AR_CL_TASK)
#define AR_CALL_LEVEL_GETALARMBASE \
    (AR_CL_TASK | AR_CL_C2ISR | AR_CL_HK_ERROR | AR_CL_HK_PREPOST | AR_CL_SYS_HK_BIT)
#define AR_CALL_LEVEL_GETALARM \
    (AR_CL_TASK | AR_CL_C2ISR | AR_CL_HK_ERROR | AR_CL_HK_PREPOST | AR_CL_SYS_HK_BIT)
#define AR_CALL_LEVEL_SETRELALARM           (AR_CL_TASK | AR_CL_C2ISR)
#define AR_CALL_LEVEL_SETABSALARM           (AR_CL_TASK | AR_CL_C2ISR)
#define AR_CALL_LEVEL_CANCELALARM           (AR_CL_TASK | AR_CL_C2ISR)
#define AR_CALL_LEVEL_GETACTIVEAPPMODE \
    (AR_CL_TASK | AR_CL_C2ISR | AR_CL_HK_ERROR | \
    AR_CL_HK_PREPOST | AR_CL_HK_STARTUP | AR_CL_HK_SHUTDOWN | AR_CL_SYS_HK_BIT)
#define AR_CALL_LEVEL_SHUTDOWNOS \
    (AR_CL_TASK | AR_CL_C2ISR | AR_CL_HK_ERROR | AR_CL_HK_STARTUP | AR_CL_SYS_HK_BIT)
#define AR_CALL_LEVEL_GETISRID \
    (AR_INTSTS_DISABLEALLINTERUPTS | AR_INTSTS_SUSPENDALLINTERRUPTS | \
    AR_INTSTS_SUSPENDOSINTERRUPTS | AR_CL_TASK | AR_CL_C2ISR | AR_CL_HK_ERROR | AR_CL_HK_PROT | AR_CL_SYS_HK_BIT)
#define AR_CALL_LEVEL_INCREMENTCOUNTER      (AR_CL_TASK | AR_CL_C2ISR)
#define AR_CALL_LEVEL_GETCOUNTERVALUE       (AR_CL_TASK | AR_CL_C2ISR)
#define AR_CALL_LEVEL_GETELAPSEDVALUE       (AR_CL_TASK | AR_CL_C2ISR)
#define AR_CALL_LEVEL_GETAPPLICATIONID      (AR_INTSTS_DISABLEALLINTERUPTS | AR_INTSTS_SUSPENDALLINTERRUPTS | \
            AR_INTSTS_SUSPENDOSINTERRUPTS | AR_CL_TASK | AR_CL_C2ISR | AR_CL_HK_ERROR | \
        AR_CL_HK_PREPOST | AR_CL_HK_STARTUP | AR_CL_HK_SHUTDOWN | AR_CL_HK_PROT | AR_CL_SYS_HK_BIT)
#define AR_CALL_LEVEL_CHECKOBJECTOWNERSHIP \
    (AR_CL_TASK | AR_CL_C2ISR | AR_CL_HK_ERROR | AR_CL_HK_PROT | AR_CL_SYS_HK_BIT)
#define AR_CALL_LEVEL_CHECKOBJECTACCESS \
    (AR_CL_TASK | AR_CL_C2ISR | AR_CL_HK_ERROR | AR_CL_HK_PROT | AR_CL_SYS_HK_BIT)
#define AR_CALL_LEVEL_GETSPINLOCK \
    (AR_CL_TASK | AR_CL_C2ISR | AR_CL_HK_PROT | AR_INTSTS_SUSPENDALLINTERRUPTS | AR_INTSTS_SUSPENDOSINTERRUPTS | AR_CL_SYS_HK_BIT)
#define AR_CALL_LEVEL_RELEASESPINLOCK \
    (AR_CL_TASK | AR_CL_C2ISR | AR_CL_HK_PROT | AR_INTSTS_SUSPENDALLINTERRUPTS | AR_INTSTS_SUSPENDOSINTERRUPTS | AR_CL_SYS_HK_BIT)
#define AR_CALL_LEVEL_TRYTOGETSPINLOCK \
    (AR_CL_TASK | AR_CL_C2ISR | AR_CL_HK_PROT | AR_INTSTS_SUSPENDALLINTERRUPTS | AR_INTSTS_SUSPENDOSINTERRUPTS | AR_CL_SYS_HK_BIT)
#define AR_CALL_LEVEL_SHUTDOWNALLCORES \
    (AR_CL_TASK | AR_CL_C2ISR | AR_CL_HK_ERROR | AR_CL_HK_STARTUP | AR_CL_SYS_HK_BIT)
#define AR_CALL_LEVEL_DISABLEINTERRUPTSOURCE (AR_CL_TASK | AR_CL_C2ISR | AR_INTSTS_DISABLEALLINTERUPTS | AR_INTSTS_SUSPENDALLINTERRUPTS | AR_INTSTS_SUSPENDOSINTERRUPTS)
#define AR_CALL_LEVEL_ENABLEINTERRUPTSOURCE  (AR_CL_TASK | AR_CL_C2ISR | AR_INTSTS_DISABLEALLINTERUPTS | AR_INTSTS_SUSPENDALLINTERRUPTS | AR_INTSTS_SUSPENDOSINTERRUPTS)
#define AR_CALL_LEVEL_CLEARPENDINGINTERRUPT  (AR_CL_TASK | AR_CL_C2ISR | AR_INTSTS_DISABLEALLINTERUPTS | AR_INTSTS_SUSPENDALLINTERRUPTS | AR_INTSTS_SUSPENDOSINTERRUPTS)

#define AR_CALL_LEVEL_IOCSEND               (AR_CL_TASK | AR_CL_C2ISR)
#define AR_CALL_LEVEL_IOCWRITE              (AR_CL_TASK | AR_CL_C2ISR)
#define AR_CALL_LEVEL_IOCRECEIVE            (AR_CL_TASK | AR_CL_C2ISR | AR_CL_RCVPLCB)
#define AR_CALL_LEVEL_IOCREAD               (AR_CL_TASK | AR_CL_C2ISR | AR_CL_RCVPLCB)
#define AR_CALL_LEVEL_IOCEMPTYQUEUE         (AR_CL_TASK | AR_CL_C2ISR | AR_CL_RCVPLCB)
#define AR_CALL_LEVEL_GETAPPLICATIONSTATE   (AR_CL_TASK | AR_CL_C2ISR | AR_CL_HK_ERROR | AR_CL_HK_PREPOST | AR_CL_HK_STARTUP | \
    AR_CL_HK_SHUTDOWN | AR_CL_HK_PROT | AR_CL_SYS_HK_BIT)
#define AR_CALL_LEVEL_CALLTRUSTEDFUNCTION   (AR_CL_TASK | AR_CL_C2ISR)
#define AR_CALL_LEVEL_CHECKISRMEMORYACCESS  (AR_CL_TASK | AR_CL_C2ISR | AR_CL_HK_ERROR | AR_CL_HK_PROT | AR_CL_SYS_HK_BIT)
#define AR_CALL_LEVEL_CHECKTASKMEMORYACCESS (AR_CL_TASK | AR_CL_C2ISR | AR_CL_HK_ERROR | AR_CL_HK_PROT | AR_CL_SYS_HK_BIT)
#define AR_CALL_LEVEL_GETCURRENTAPPLICATIONID (AR_INTSTS_DISABLEALLINTERUPTS | AR_INTSTS_SUSPENDALLINTERRUPTS | AR_INTSTS_SUSPENDOSINTERRUPTS | \
                                               AR_CL_TASK | AR_CL_C2ISR | AR_CL_HK_ERROR | AR_CL_HK_PREPOST | \
                                               AR_CL_HK_STARTUP | AR_CL_HK_SHUTDOWN | AR_CL_HK_PROT | AR_CL_SYS_HK_BIT)
#define AR_CALL_LEVEL_CONTROLIDLE           (AR_CL_TASK | AR_CL_C2ISR)
#define AR_CALL_LEVEL_GETFAULTYCONTEXT      (AR_CL_HK_PROT | AR_CL_SYS_HK_BIT)
#define AR_CALL_LEVEL_READPERIPHERAL        (AR_CL_TASK | AR_CL_C2ISR | AR_INTSTS_DISABLEALLINTERUPTS | AR_INTSTS_SUSPENDALLINTERRUPTS | AR_INTSTS_SUSPENDOSINTERRUPTS)
#define AR_CALL_LEVEL_WRITEPERIPHERAL       (AR_CL_TASK | AR_CL_C2ISR | AR_INTSTS_DISABLEALLINTERUPTS | AR_INTSTS_SUSPENDALLINTERRUPTS | AR_INTSTS_SUSPENDOSINTERRUPTS)
#define AR_CALL_LEVEL_MODIFYPERIPHERAL      (AR_CL_TASK | AR_CL_C2ISR | AR_INTSTS_DISABLEALLINTERUPTS | AR_INTSTS_SUSPENDALLINTERRUPTS | AR_INTSTS_SUSPENDOSINTERRUPTS)

#define OSSVCID_INVALID     ((OSServiceIdType) 0xff)

#define AR_CALLLEVEL_IS_HOOK(clscb) \
    ( ((uint32)((clscb)->aroscb.call_level) & \
     (AR_CL_HK_STARTUP | AR_CL_HK_SHUTDOWN | AR_CL_HK_ERROR | \
      AR_CL_HK_PROT | AR_CL_HK_PREPOST | AR_CL_SYS_HK_BIT)) != (uint16)0x0000U )

#define AR_CALLLEVEL_IS_SYS_HOOK_OR_TRUSTED_OSAP(clscb) \
    ( (((uint32)((clscb)->aroscb.call_level) & AR_CL_SYS_HK_BIT) != (uint16)0x0000U) || \
      ((uint32)(clscb)->aroscb.p_currentosap->osap_trusted != (uint32)FALSE) )

#define AR_CALLLEVEL_IS_NOT_SYS_HOOK_AND_TRUSTED_OSAP(clscb) \
    ( (((uint32)((clscb)->aroscb.call_level) & AR_CL_SYS_HK_BIT) == (uint16)0x0000U) && \
      ((uint32)(clscb)->aroscb.p_currentosap->osap_trusted == (uint32)FALSE) )

#define AR_CALLLEVEL_IS_ERROR_HOOK(clscb) \
    (((uint32)((clscb)->aroscb.call_level) & AR_CL_HK_ERROR) != (uint16)0x0000U)

/*
 * Caution : When using 'AR_MATCH_CALLLEVEL','AR_NOT_MATCH_CALLLEVEL' macro, 'mask' should not have side effects.
 */
#define AR_MATCH_CALLLEVEL(clscb, mask) \
        (((uint32)((clscb)->aroscb.call_level) | (uint32)(mask)) == (uint32)(mask))

#define AR_NOT_MATCH_CALLLEVEL(clscb, mask) \
        (((uint32)((clscb)->aroscb.call_level) | (uint32)(mask)) != (uint32)(mask))

#define AR_IS_INTDISABLED(clscb) \
        (((uint32)((clscb)->aroscb.call_level) &                        \
          ((uint32)AR_INTSTS_DISABLEALLINTERUPTS | (uint32)AR_INTSTS_SUSPENDALLINTERRUPTS | (uint32)AR_INTSTS_SUSPENDOSINTERRUPTS)) !=  \
         (uint32)AR_INTSTS_NULL)

#define AR_IS_INTALLDISABLED(clscb) \
        (((uint32)((clscb)->aroscb.call_level) & (uint32)AR_INTSTS_DISABLEALLINTERUPTS) != (uint32)AR_INTSTS_NULL)

/*
 * Check error
 */
#define AR_IS_NOT_ACC_RIGHTS(clscb, bitmap)                                     \
    ((((uint32)((clscb)->aroscb.call_level) & AR_CL_SYS_HK_BIT)       == 0UL)   \
        && ((clscb)->aroscb.p_currentosap->osap_protected != (boolean)FALSE)    \
        && ((((clscb)->aroscb.p_currentosap->osap_bitmask & (bitmap)) == 0UL)))

#define AR_IS_NOT_ACC_ACTRES(objappconfig, curosapconfig)                                           \
    (   (ar_osapcb_ptr_table[(objappconfig)->osap_id]->osap_state != APPLICATION_ACCESSIBLE)        \
    && (    (ar_osapcb_ptr_table[(objappconfig)->osap_id]->osap_state != APPLICATION_RESTARTING)    \
        ||  ((objappconfig) != (curosapconfig))))

#define AR_IS_NOT_ACC_ACTIVE(objappconfig, curosapconfig)                                       \
    (   (ar_osapcb_ptr_table[(objappconfig)->osap_id]->osap_state != APPLICATION_ACCESSIBLE)    \
     && ((objappconfig) != (curosapconfig)))

#define AR_IS_NOT_ACC_AREA(clscb, bitmap)                                     \
    (((clscb)->aroscb.p_currentosap->osap_protected != (boolean)FALSE)        \
    && (((clscb)->aroscb.p_currentosap->osap_bitmask & (bitmap)) == 0UL))


#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)

AR_LOCAL_FORCE_INLINE void AR_CHECK_MEMREADWRITE_TICKTYPE(TickRefType pointer);
AR_LOCAL_FORCE_INLINE void AR_CHECK_MEMREADWRITE_TICKTYPE(TickRefType pointer)
{
    volatile TickType v = *pointer;
    *(volatile TickType *)pointer = v;
}

AR_LOCAL_FORCE_INLINE void AR_CHECK_MEMWRITE_TICKTYPE(TickRefType pointer);
AR_LOCAL_FORCE_INLINE void AR_CHECK_MEMWRITE_TICKTYPE(TickRefType pointer)
{
    *(volatile TickType *)pointer = (TickType)0;
}

AR_LOCAL_FORCE_INLINE void AR_CHECK_MEMWRITE_APLSTATETYPE(ApplicationStateRefType pointer);
AR_LOCAL_FORCE_INLINE void AR_CHECK_MEMWRITE_APLSTATETYPE(ApplicationStateRefType pointer)
{
    *(volatile ApplicationStateType *)pointer = (ApplicationStateType)0;
}

AR_LOCAL_FORCE_INLINE void AR_CHECK_MEMWRITE_TASKSTATETYPE(TaskStateRefType pointer);
AR_LOCAL_FORCE_INLINE void AR_CHECK_MEMWRITE_TASKSTATETYPE(TaskStateRefType pointer)
{
    *(volatile TaskStateType *)pointer = (TaskStateType)0;
}

AR_LOCAL_FORCE_INLINE void AR_CHECK_MEMWRITE_EVENTMASKTYPE(EventMaskRefType pointer);
AR_LOCAL_FORCE_INLINE void AR_CHECK_MEMWRITE_EVENTMASKTYPE(EventMaskRefType pointer)
{
    *(volatile EventMaskType *)pointer = (EventMaskType)0;
}

AR_LOCAL_FORCE_INLINE void AR_CHECK_MEMWRITE_TRYTOGETSTYPE(TryToGetSpinlockType *pointer);
AR_LOCAL_FORCE_INLINE void AR_CHECK_MEMWRITE_TRYTOGETSTYPE(TryToGetSpinlockType *pointer)
{
    *(volatile TryToGetSpinlockType *)pointer = (TryToGetSpinlockType)0;
}

AR_LOCAL_FORCE_INLINE void AR_CHECK_MEMWRITE_UINT8(uint8 *pointer);
AR_LOCAL_FORCE_INLINE void AR_CHECK_MEMWRITE_UINT8(uint8 *pointer)
{
    *(volatile uint8 *)pointer = (uint8)0;
}

AR_LOCAL_FORCE_INLINE void AR_CHECK_MEMWRITE_UINT16(uint16 *pointer);
AR_LOCAL_FORCE_INLINE void AR_CHECK_MEMWRITE_UINT16(uint16 *pointer)
{
    *(volatile uint16 *)pointer = (uint16)0;
}

AR_LOCAL_FORCE_INLINE void AR_CHECK_MEMWRITE_UINT32(uint32 *pointer);
AR_LOCAL_FORCE_INLINE void AR_CHECK_MEMWRITE_UINT32(uint32 *pointer)
{
    *(volatile uint32 *)pointer = (uint32)0;
}

#else /* ! (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

#define AR_CHECK_MEMREADWRITE_TICKTYPE(pointer)
#define AR_CHECK_MEMWRITE_TICKTYPE(pointer)
#define AR_CHECK_MEMWRITE_APLSTATETYPE(pointer)
#define AR_CHECK_MEMWRITE_TASKSTATETYPE(pointer)
#define AR_CHECK_MEMWRITE_EVENTMASKTYPE(pointer)
#define AR_CHECK_MEMWRITE_TRYTOGETSTYPE(pointer)
#define AR_CHECK_MEMWRITE_UINT8(pointer)
#define AR_CHECK_MEMWRITE_UINT16(pointer)
#define AR_CHECK_MEMWRITE_UINT32(pointer)

#endif /* ! (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */


#if (AR_OS_USE_ERRORHOOK == STD_ON)

/*
check user config.
*/
#define AR_IS_ENABLED_ERRORHOOK() ((USER_CFG_STD_ON_USE_SYSTEM_ERRORHOOK() | USER_CFG_STD_ON_USE_OSAP_ERRORHOOK()) != 0UL)

/*
Errorhook parameter element number
*/
#define AR_ActivateTask_TaskID_ERROR_PARAM_NO                   (0)
#define AR_ChainTask_TaskID_ERROR_PARAM_NO                      (0)
#define AR_GetTaskID_TaskID_ERROR_PARAM_NO                      (0)
#define AR_GetTaskState_TaskID_ERROR_PARAM_NO                   (0)
#define AR_GetTaskState_State_ERROR_PARAM_NO                    (1)
#define AR_DisableInterruptSource_DisableISR_ERROR_PARAM_NO     (0)
#define AR_EnableInterruptSource_EnableISR_ERROR_PARAM_NO       (0)
#define AR_EnableInterruptSource_ClearPending_ERROR_PARAM_NO    (1)
#define AR_ClearPendingInterrupt_ISRID_ERROR_PARAM_NO           (0)
#define AR_GetResource_ResID_ERROR_PARAM_NO                     (0)
#define AR_ReleaseResource_ResID_ERROR_PARAM_NO                 (0)
#define AR_SetEvent_TaskID_ERROR_PARAM_NO                       (0)
#define AR_SetEvent_Mask_ERROR_PARAM_NO                         (1)
#define AR_ClearEvent_Mask_ERROR_PARAM_NO                       (0)
#define AR_GetEvent_TaskID_ERROR_PARAM_NO                       (0)
#define AR_GetEvent_Event_ERROR_PARAM_NO                        (1)
#define AR_WaitEvent_Mask_ERROR_PARAM_NO                        (0)
#define AR_GetAlarmBase_AlarmID_ERROR_PARAM_NO                  (0)
#define AR_GetAlarmBase_Info_ERROR_PARAM_NO                     (1)
#define AR_GetAlarm_AlarmID_ERROR_PARAM_NO                      (0)
#define AR_GetAlarm_Tick_ERROR_PARAM_NO                         (1)
#define AR_SetRelAlarm_AlarmID_ERROR_PARAM_NO                   (0)
#define AR_SetRelAlarm_increment_ERROR_PARAM_NO                 (1)
#define AR_SetRelAlarm_cycle_ERROR_PARAM_NO                     (2)
#define AR_SetAbsAlarm_AlarmID_ERROR_PARAM_NO                   (0)
#define AR_SetAbsAlarm_start_ERROR_PARAM_NO                     (1)
#define AR_SetAbsAlarm_cycle_ERROR_PARAM_NO                     (2)
#define AR_CancelAlarm_AlarmID_ERROR_PARAM_NO                   (0)
#define AR_StartOS_Mode_ERROR_PARAM_NO                          (0)
#define AR_ShutdownOS_Error_ERROR_PARAM_NO                      (0)
#define AR_CallTF_FunctionIndex_ERROR_PARAM_NO                  (0)
#define AR_CallTF_FunctionParams_ERROR_PARAM_NO                 (1)
#define AR_CallFastTF_FunctionIndex_ERROR_PARAM_NO              (0)
#define AR_CallFastTF_FunctionParams_ERROR_PARAM_NO             (1)
#define AR_CheckISRMemoryAccess_ISRID_ERROR_PARAM_NO            (0)
#define AR_CheckISRMemoryAccess_Address_ERROR_PARAM_NO          (1)
#define AR_CheckISRMemoryAccess_Size_ERROR_PARAM_NO             (2)
#define AR_CheckObjectAccess_ApplID_ERROR_PARAM_NO              (0)
#define AR_CheckObjectAccess_ObjectType_ERROR_PARAM_NO          (1)
#define AR_CheckObjectAccess_ObjectID_ERROR_PARAM_NO            (2)
#define AR_CheckObjectOwnership_ObjectType_ERROR_PARAM_NO       (0)
#define AR_CheckObjectOwnership_ObjectID_ERROR_PARAM_NO         (1)
#define AR_CheckTaskMemoryAccess_TaskID_ERROR_PARAM_NO          (0)
#define AR_CheckTaskMemoryAccess_Address_ERROR_PARAM_NO         (1)
#define AR_CheckTaskMemoryAccess_Size_ERROR_PARAM_NO            (2)
#define AR_IncrementCounter_CounterID_ERROR_PARAM_NO            (0)
#define AR_GetCounterValue_CounterID_ERROR_PARAM_NO             (0)
#define AR_GetCounterValue_Value_ERROR_PARAM_NO                 (1)
#define AR_GetElapsedValue_CounterID_ERROR_PARAM_NO             (0)
#define AR_GetElapsedValue_Value_ERROR_PARAM_NO                 (1)
#define AR_GetElapsedValue_ElapsedValue_ERROR_PARAM_NO          (2)
#define AR_GetApplicationState_Application_ERROR_PARAM_NO       (0)
#define AR_GetApplicationState_Value_ERROR_PARAM_NO             (1)
#define AR_ControlIdle_CoreID_ERROR_PARAM_NO                    (0)
#define AR_ControlIdle_IdleMode_ERROR_PARAM_NO                  (1)
#define AR_IocSend_IocId_ERROR_PARAM_NO                         (0)
#define AR_IocSend_SenderId_ERROR_PARAM_NO                      (1)
#define AR_IocWrite_IocId_ERROR_PARAM_NO                        (0)
#define AR_IocWrite_SenderId_ERROR_PARAM_NO                     (1)
#define AR_IocSendGroup_IocId_ERROR_PARAM_NO                    (0)
#define AR_IocSendGroup_SenderId_ERROR_PARAM_NO                 (1)
#define AR_IocWriteGroup_IocId_ERROR_PARAM_NO                   (0)
#define AR_IocWriteGroup_SenderId_ERROR_PARAM_NO                (1)
#define AR_IocReceive_IocId_ERROR_PARAM_NO                      (0)
#define AR_IocRead_IocId_ERROR_PARAM_NO                         (0)
#define AR_IocReceiveGroup_IocId_ERROR_PARAM_NO                 (0)
#define AR_IocReadGroup_IocId_ERROR_PARAM_NO                    (0)
#define AR_IocEmptyQueue_IocId_ERROR_PARAM_NO                   (0)
#define AR_StartCore_CoreID_ERROR_PARAM_NO                      (0)
#define AR_StartCore_Status_ERROR_PARAM_NO                      (1)
#define AR_StartNonAutosarCore_CoreID_ERROR_PARAM_NO            (0)
#define AR_StartNonAutosarCore_Status_ERROR_PARAM_NO            (1)
#define AR_GetSpinlock_SpinlockId_ERROR_PARAM_NO                (0)
#define AR_ReleaseSpinlock_SpinlockId_ERROR_PARAM_NO            (0)
#define AR_TryToGetSpinlock_SpinlockId_ERROR_PARAM_NO           (0)
#define AR_TryToGetSpinlock_Success_ERROR_PARAM_NO              (1)
#define AR_ShutdownAllCores_Error_ERROR_PARAM_NO                (0)
#define AR_RaiseInterCoreInterrupt_CoreID_ERROR_PARAM_NO        (0)
#define AR_ReadPeripheralX_Area_ERROR_PARAM_NO                  (0)
#define AR_ReadPeripheralX_Address_ERROR_PARAM_NO               (1)
#define AR_ReadPeripheralX_ReadValue_ERROR_PARAM_NO             (2)
#define AR_WritePeripheralX_Area_ERROR_PARAM_NO                 (0)
#define AR_WritePeripheralX_Address_ERROR_PARAM_NO              (1)
#define AR_WritePeripheralX_WriteValue_ERROR_PARAM_NO           (2)
#define AR_ModifyPeripheralX_Area_ERROR_PARAM_NO                (0)
#define AR_ModifyPeripheralX_Address_ERROR_PARAM_NO             (1)
#define AR_ModifyPeripheralX_Clearmask_ERROR_PARAM_NO           (2)
#define AR_ModifyPeripheralX_Setmask_ERROR_PARAM_NO             (3)


#endif /* (AR_OS_USE_ERRORHOOK == STD_ON) */

#define OS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Os_MemMap.h"
extern AppModeType ar_appmode;
#define OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

extern ProtectionReturnType ar_protectionhook_call_internal(const mcos_uintptr_t param1, const mcos_uintptr_t param2);

extern void ar_startuphook_call(const mkcb_t *mkcb, clscb_t *clscb, CoreIdType my_core_id, int32_t sr);
extern void ar_shutdown_allcores_impl(const StatusType status);
extern void ar_os_shutdown_internal(StatusType status);
#if (AR_OS_USE_SHUTDOWNHOOK == STD_ON)
extern void ar_shutdownhook_call(const StatusType status);
#endif /* AR_OS_USE_SHUTDOWNHOOK */
extern void ar_system_call_error(void);
extern StatusType ar_no_support_service(void);
extern int32_t ar_system_call_startuphook(const mkcb_t *mkcb, clscb_t *clscb, int32_t sr);
extern void ar_system_call_shutdownhook(const mkcb_t *mkcb, clscb_t *clscb, StatusType status);
extern ProtectionReturnType ar_call_protectionhook(const mkcb_t *mkcb, clscb_t *clscb, StatusType status);
#if (AR_OS_USE_PRETASKHOOK == STD_ON)
extern void ar_call_pretaskhook(void);
#endif /* (AR_OS_USE_PRETASKHOOK == STD_ON) */
#if (AR_OS_USE_POSTTASKHOOK == STD_ON)
extern void ar_call_posttaskhook(void);
#endif /* (AR_OS_USE_POSTTASKHOOK == STD_ON) */
extern void ar_system_call_errorhook(const mkcb_t *mkcb, clscb_t *clscb, StatusType status);
extern void mcos_call_userhook_ar_target_exit_internal(mcos_uintptr_t param1, mcos_uintptr_t param2);

#if ((AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) || (AR_OS_USE_STACKMONITORING == STD_ON))
extern void ar_stack_overflow(void);
#endif /*  ((AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) || (AR_OS_USE_STACKMONITORING == STD_ON)) */

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define AR_CRITICAL_SECTION_NUM_0   (0)

AR_LOCAL_FORCE_INLINE ar_critical_section_t ar_get_critical_section(void);
AR_LOCAL_FORCE_INLINE ar_critical_section_t ar_critical_section_enter_core(clscb_t * const clscb);
AR_LOCAL_FORCE_INLINE ar_critical_section_t ar_critical_section_enter(void);
AR_LOCAL_FORCE_INLINE void ar_critical_section_leave_core(clscb_t * const clscb, const ar_critical_section_t cs);
AR_LOCAL_FORCE_INLINE void ar_critical_section_leave(const ar_critical_section_t cs);
AR_LOCAL_FORCE_INLINE void ar_critical_section_enaint(void);


AR_LOCAL_FORCE_INLINE ar_critical_section_t ar_get_critical_section(void)
{
    return (ar_critical_section_t)AR_CRITICAL_SECTION_NUM_0;
}

AR_LOCAL_FORCE_INLINE ar_critical_section_t ar_critical_section_enter_core(
    clscb_t * const clscb)
{
    uint8           nest;
    ar_intcb_t      *ar_intcb;

    ar_intcb = mcos_cls_get_arintcb(clscb);
    nest = ar_intcb->nested_lock_os_int_cnt;

    if ((uint32)nest == (uint32)0U)
    {
        int32_t bpri;

        bpri = mcos_hwl_cpu_getIntPriority();
        mcos_hwl_cpu_setIntPriority(MCOS_INTM_APRI_TO_BPRI(USER_CFG_AR_OS_EXEC_PRIORITY()));
        ar_intcb->saved_intbpri = bpri;
    }
    else
    {
        /* Nothing to do */
    }

    nest++;
    ar_intcb->nested_lock_os_int_cnt = nest;

    return (ar_critical_section_t)AR_CRITICAL_SECTION_NUM_0;
}

AR_LOCAL_FORCE_INLINE ar_critical_section_t ar_critical_section_enter(void)
{
    const mkcb_t    *mkcb;
    clscb_t         *clscb;

    mkcb = (const mkcb_t *)mcos_mkcc_get_current_control_block();
    clscb = mcos_mkcc_get_clscb(mkcb);

    return ar_critical_section_enter_core(clscb);
}

AR_LOCAL_FORCE_INLINE void ar_critical_section_leave_core(
    clscb_t * const clscb,
    const ar_critical_section_t cs)
{
    uint8           nest;
    ar_intcb_t      *ar_intcb;

    /*
     * 'cs' is not used in this function.
     * It exists to match specifications with the other functions of critical section.
     */
    (void)cs;
    ar_intcb = mcos_cls_get_arintcb(clscb);
    nest = ar_intcb->nested_lock_os_int_cnt;
    nest--;
    ar_intcb->nested_lock_os_int_cnt = nest;

    if ((uint32)nest == (uint32)0U)
    {
        mcos_hwl_cpu_setIntPriority(ar_intcb->saved_intbpri);
    }
    else
    {
        /* Nothing to do */
    }
}

AR_LOCAL_FORCE_INLINE void ar_critical_section_leave(
    const ar_critical_section_t cs)
{
    const mkcb_t    *mkcb;
    clscb_t         *clscb;

    mkcb = (const mkcb_t *)mcos_mkcc_get_current_control_block();
    clscb = mcos_mkcc_get_clscb(mkcb);

    ar_critical_section_leave_core(clscb, cs);
}

AR_LOCAL_FORCE_INLINE void ar_critical_section_enaint(void)
{
    const mkcb_t    *mkcb;
    clscb_t         *clscb;
    uint8           nest;
    ar_intcb_t      *ar_intcb;

    mkcb = (const mkcb_t *)mcos_mkcc_get_current_control_block();
    clscb = mcos_mkcc_get_clscb(mkcb);

    ar_intcb = mcos_cls_get_arintcb(clscb);
    nest = ar_intcb->nested_lock_os_int_cnt;

    if ((uint32)nest == AR_NESTED_LOCK_OS_INT_CNT_1)
    {
        int32_t bpri;

        ar_intcb->nested_lock_os_int_cnt = (uint8)0U;
        bpri = ar_intcb->saved_intbpri;

        /* enable interrupts */
        mcos_hwl_cpu_setIntPriority(ar_intcb->saved_intbpri);

        /* disable interrupts */
        mcos_hwl_cpu_setIntPriority(MCOS_INTM_APRI_TO_BPRI(USER_CFG_AR_OS_EXEC_PRIORITY()));
        ar_intcb->saved_intbpri = bpri;
        ar_intcb->nested_lock_os_int_cnt = (uint8)1U;
    }
    else
    {
        /* Nothing to do */
    }
}

#ifdef __cplusplus
}
#endif

#include "ar_multicore.h"

#include "ar_call_func.h"

#endif /* AR_KERNEL_IMPL_H */
