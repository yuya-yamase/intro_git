/*
    Copyright (C) 2018 By eSOL Co.,Ltd. Tokyo, Japan

    This software is protected by the law and the agreement concerning
    a Japanese country copyright method, an international agreement,
    and other intellectual property right and may be used and copied
    only in accordance with the terms of such license and with the inclusion
    of the above copyright notice.

    This software or any other copies thereof may not be provided
    or otherwise made available to any other person.  No title to
    and access of the software is hereby transferred.

    The information in this software is subject to change without
    notice and should not be construed as a commitment by eSOL Co.,Ltd.
*/

/****************************************************************************
[ar_call_func.h] - switch function call for user config header
****************************************************************************/

#ifndef AR_CALL_FUNC_H
#define AR_CALL_FUNC_H

#include "ar_alarm.h"
#include "ar_counter.h"
#include "ar_interrupt.h"
#include "ar_ioc.h"
#include "ar_osap.h"
#include "ar_resource.h"
#include "ar_spinlock.h"
#include "ar_task.h"
#include "ar_svc_id.h"
#include "ar_peripheral.h"

/*
 * ar_func_table_t and related function types
 */
typedef void (*FUNC_ar_alarm_init)(void);
typedef StatusType (*FUNC_ar_get_alarm_base_impl)(const AlarmType alarm_id, const AlarmBaseRefType p_info, const ar_osap_config_t * const p_osapconfig);
typedef StatusType (*FUNC_ar_get_alarm_impl)(const AlarmType alarm_id, const TickRefType p_tick, const ar_osap_config_t * const p_osapconfig);
typedef StatusType (*FUNC_ar_set_rel_alarm_impl)(const mkcb_t * const mkcb, const AlarmType alarm_id, const TickType increment, const TickType cycle, const ar_osap_config_t * const p_osapconfig);
typedef StatusType (*FUNC_ar_set_abs_alarm_impl)(const AlarmType alarm_id, const TickType start, const TickType cycle, const ar_osap_config_t * const p_osapconfig);
typedef StatusType (*FUNC_ar_cancel_alarm_impl)(const mkcb_t * const mkcb, const AlarmType alarm_id, const ar_osap_config_t * const p_osapconfig);
typedef ApplicationType (*FUNC_ar_CheckAlarmOwnership)(uint32 object_id);
typedef void (*FUNC_ar_cat1_interrupt_init)(void);
typedef void (*FUNC_ar_interrupt_init)(void);
typedef ar_isrcb_t * (*FUNC_ar_get_isrcb)(ISRType cat2isr);
typedef const ar_isr_config_t * (*FUNC_ar_get_isr_config)(ISRType cat2isr);
typedef const ar_cat1_int_config_t * (*FUNC_ar_get_cat1_int_config)(ISRType cat1isr);
typedef AccessType (*FUNC_ar_check_isr_memory)(ISRType ISRID, ConstMemoryStartAddressType start, MemorySizeType size);
typedef ApplicationType (*FUNC_ar_CheckISROwnership)(uint32 object_id);
#if (AR_OS_USE_EXTENDEDSTATUS == STD_ON)
typedef StatusType (*FUNC_ar_cat1_check_lcid)(ISRType ISRID);
typedef StatusType (*FUNC_ar_cat2_check_lcid)(ISRType ISRID);
#endif /* #if (AR_OS_USE_EXTENDEDSTATUS == STD_ON) */
typedef mcos_id_t (*FUNC_ar_cat1_get_iid)(ISRType ISRID);
typedef mcos_id_t (*FUNC_ar_cat2_get_iid)(ISRType ISRID);
typedef void (*FUNC_ar_counter_init)(void);
typedef StatusType (*FUNC_ar_get_counter_value_impl)(const CounterType counter_id, const TickRefType p_value, const ar_osap_config_t * const p_osapconfig);
typedef StatusType (*FUNC_ar_get_elapsed_value_impl)(const CounterType counter_id, const TickRefType p_value, const TickRefType p_elapsed_value, const ar_osap_config_t * const p_osapconfig);
typedef ApplicationType (*FUNC_ar_CheckCounterOwnership)(uint32 object_id);
typedef StatusType (*FUNC_ar_set_event_impl)(clscb_t * const clscb, const TaskType task_id, const EventMaskType event, const ar_osap_config_t * const p_osapconfig);

typedef StatusType (*FUNC_ar_get_event_impl)(
#if (AR_OS_USE_EXTENDEDSTATUS == STD_ON)
        clscb_t * const clscb,
#endif /* #if (AR_OS_USE_EXTENDEDSTATUS == STD_ON) */
        const TaskType task_id, const EventMaskRefType p_event, const ar_osap_config_t * const p_osapconfig);

typedef void (*FUNC_ar_ioc_init)(void);
typedef void (*FUNC_ar_ioc_init_queued)(IocType ioc_id);
typedef void (*FUNC_ar_ioc_init_unqueued)(IocType ioc_id, const ar_ioc_config_t * const p_config, const ar_ioc_receiver_config_t *p_receiver_config);
typedef Std_ReturnType (*FUNC_ar_ioc_send_impl)(const mkcb_t * const mkcb, const IocType receiver_id, const void * const in);
typedef void (*FUNC_ar_ioc_write_impl)(const mkcb_t * const mkcb, const IocType receiver_id, const void * const in);
typedef void (*FUNC_ar_ioc_lock_get)(const ar_ioc_config_t * const p_config);
typedef void (*FUNC_ar_ioc_lock_release)(const ar_ioc_config_t * const p_config);
typedef void (*FUNC_ar_resource_init)(void);
typedef void (*FUNC_ar_task_force_release_resources)(ar_tcb_t * const p_atcb);
typedef void (*FUNC_ar_c2isr_force_release_resources)(ar_isrcb_t * const p_isrcb);
typedef void (*FUNC_ar_spinlock_init)(void);
typedef void (*FUNC_ar_spinlock_force_release)(ar_spinlockcb_t * const p_last_spinlockcb);
typedef void (*FUNC_ar_spinlock_cancel)(ar_spinlockcb_t * const p_spinlockcb);
typedef StatusType (*FUNC_ar_task_init)(void);
typedef StatusType (*FUNC_ar_activate_task_impl)(clscb_t * const clscb, const TaskType task_id, const ar_osap_config_t * const p_osapconfig);
typedef StatusType (*FUNC_ar_get_task_state_impl)(const mkcb_t *const mkcb, const TaskType task_id, const TaskStateRefType p_state, const ar_osap_config_t * const p_osapconfig);
typedef ApplicationType (*FUNC_ar_CheckTaskOwnership)(uint32 object_id);
typedef void (*FUNC_ar_set_mastercore_booted)(void);
typedef void (*FUNC_ar_multicore_init)(void);
typedef void (*FUNC_ar_ici_init)(void);
typedef void (*FUNC_ar_shutdown_allcores_impl)(const StatusType status);
typedef void (*FUNC_mcos_main_slave)(const int32_t pcid, const void * const ptr);
typedef void (*FUNC_ar_sync_cores)(const uint8 phase, const boolean check_shutdown);
typedef void (*FUNC_ar_system_call_errorhook)(const mkcb_t *mkcb, clscb_t *clscb, StatusType status);
typedef void (*FUNC_ar_call_posttaskhook)(void);
typedef void (*FUNC_ar_call_pretaskhook)(void);
typedef ProtectionReturnType (*FUNC_ar_call_protectionhook)(const mkcb_t *mkcb, clscb_t *clscb, StatusType status);
typedef int32_t (*FUNC_ar_system_call_startuphook)(const mkcb_t *mkcb, clscb_t *clscb, int32_t sr);
typedef void (*FUNC_ar_system_call_shutdownhook)(const mkcb_t *mkcb, clscb_t *clscb, StatusType status);
typedef void (*FUNC_ar_osap_call_errorhook)(const StatusType status, const OSServiceIdType svcid);
typedef void (*FUNC_ar_osap_call_shutdownhook)(const StatusType status);
typedef int32_t (*FUNC_ar_osap_call_startuphook)(int32_t sr, CoreIdType my_core_id);
typedef void (*FUNC_ar_system_counter_start)(void);
typedef void (*FUNC_ar_system_counter_stop)(void);
typedef void (*FUNC_ar_interrupt_bind)(void);
typedef void (*FUNC_mcos_mkmsg_init)(const mkcb_t * const mkcb);

typedef StatusType (*FUNC_ar_chk_isr_owner)(ISRType ISRID,  const clscb_t *clscb);
typedef StatusType (*FUNC_ar_peripheral_chk_address)(const clscb_t* clscb, AreaIdType Area, const void* Address, uint32 Range);

#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
typedef ObjectAccessType (*FUNC_ar_CheckAlarmAccess)(ApplicationType ApplID, AlarmType alarm_id);
typedef ObjectAccessType (*FUNC_ar_CheckISRAccess)(ApplicationType ApplID, ISRType ISRID);
typedef void (*FUNC_ar_forcibly_terminate_counter)(const ar_osap_config_t * p_osapconfig);
typedef ObjectAccessType (*FUNC_ar_CheckCounterAccess)(ApplicationType ApplID, CounterType CounterID);
typedef ObjectAccessType (*FUNC_ar_CheckResourceAccess)(ApplicationType ApplID, ResourceType ResourceID);
typedef ObjectAccessType (*FUNC_ar_CheckSpinlockAccess)(ApplicationType ApplID, SpinlockIdType spinlock_id);
typedef ObjectAccessType (*FUNC_ar_CheckTaskAccess)(ApplicationType ApplID, TaskType TaskID);
#endif /* #if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

/*
 * ar_svc_table_t and related function types
 */
typedef void (*AR_SVC_ENTITY_EnableAllInterrupts)(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef void (*AR_SVC_ENTITY_DisableAllInterrupts)(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef void (*AR_SVC_ENTITY_ResumeAllInterrupts)(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef void (*AR_SVC_ENTITY_SuspendAllInterrupts)(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef void (*AR_SVC_ENTITY_ResumeOSInterrupts)(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef void (*AR_SVC_ENTITY_SuspendOSInterrupts)(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_DisableInterruptSource)(ISRType ISRID
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_EnableInterruptSource)(ISRType ISRID, boolean ClearPending
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_ClearPendingInterrupt)(ISRType ISRID
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef AccessType (*AR_SVC_ENTITY_CheckTaskMemoryAccess)(TaskType TaskID, MemoryStartAddressType Address, MemorySizeType Size
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef AccessType (*AR_SVC_ENTITY_CheckISRMemoryAccess)(ISRType ISRID, MemoryStartAddressType Address, MemorySizeType Size
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef ObjectAccessType (*AR_SVC_ENTITY_CheckObjectAccess)(ApplicationType ApplID, ObjectTypeType ObjectType, uint32 ObjectID
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef ApplicationType (*AR_SVC_ENTITY_CheckObjectOwnership)(ObjectTypeType object_type, uint32 object_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_ControlIdle)(CoreIdType core_id, IdleModeType idle_mode
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_GetApplicationState)(ApplicationType Application, ApplicationStateRefType Value
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef AppModeType (*AR_SVC_ENTITY_GetActiveApplicationMode)(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_TerminateApplication)(ApplicationType Application, RestartType RestartOption
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_AllowAccess)(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef OSServiceIdType (*AR_SVC_ENTITY_ar_get_errhk_svcid)(void);
typedef uint32 (*AR_SVC_ENTITY_ar_get_errhk_param)(uint8 par_num);
typedef void (*AR_SVC_ENTITY_ShutdownOS)(StatusType Error
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef void (*AR_SVC_ENTITY_ShutdownAllCores)(StatusType Error
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef uint32 (*AR_SVC_ENTITY_GetNumberOfActivatedCores)(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_ActivateTask)(TaskType TaskID
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef void (*AR_SVC_ENTITY_ActivateTaskAsyn)(TaskType TaskID
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_TerminateTask)(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_ChainTask)(TaskType TaskID
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_Schedule)(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_GetTaskState)(TaskType TaskID, TaskStateRefType State
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef void (*AR_SVC_ENTITY_ar_illegal_exit_task)(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_SetEvent)(TaskType task_id, EventMaskType event
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef void (*AR_SVC_ENTITY_SetEventAsyn)(TaskType task_id, EventMaskType event
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_ClearEvent)(EventMaskType event
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_GetEvent)(TaskType task_id, EventMaskRefType p_event
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_WaitEvent)(EventMaskType event
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_GetResource)(ResourceType resource_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_ReleaseResource)(ResourceType resource_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_IncrementCounter)(CounterType counter_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_GetCounterValue)(CounterType counter_id, TickRefType p_value
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_GetElapsedValue)(CounterType counter_id, TickRefType p_value, TickRefType p_elapsed_value
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_GetAlarmBase)(AlarmType alarm_id, AlarmBaseRefType p_info
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_GetAlarm)(AlarmType alarm_id, TickRefType p_tick
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_SetRelAlarm)(AlarmType alarm_id, TickType increment, TickType cycle
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_SetAbsAlarm)(AlarmType alarm_id, TickType start, TickType cycle
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_CancelAlarm)(AlarmType alarm_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_CallTrustedFunction)(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef Std_ReturnType (*AR_SVC_ENTITY_ar_ioc_send)(IocType ioc_sender_id, void *in
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef Std_ReturnType (*AR_SVC_ENTITY_ar_ioc_write)(IocType ioc_sender_id, void *in
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef Std_ReturnType (*AR_SVC_ENTITY_ar_ioc_receive)(IocType receiver_id, void *out
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef Std_ReturnType (*AR_SVC_ENTITY_ar_ioc_read)(IocType receiver_id, void *out
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_ar_ioc_empty_queue)(IocType receiver_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_GetSpinlock)(SpinlockIdType spinlock_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_ReleaseSpinlock)(SpinlockIdType spinlock_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_TryToGetSpinlock)(SpinlockIdType spinlock_id, TryToGetSpinlockType *p_success
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_RaiseInterCoreInterrupt)(CoreIdType CoreID
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_GetSpinlockSkipErrorChk)(SpinlockIdType spinlock_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_ReleaseSpinlockSkipErrorChk)(SpinlockIdType spinlock_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef StatusType (*AR_SVC_ENTITY_TryToGetSpinlockSkipErrorChk)(SpinlockIdType spinlock_id, TryToGetSpinlockType *p_success
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
typedef void (*AR_SVC_ENTITY_ar_errorhook_call)(const StatusType status, const OSServiceIdType svcid, const ar_errhk_param_t errhk_param[AR_ERRHK_PARAM_NUM]);
typedef StatusType (*AR_SVC_ENTITY_CallFastTrustedFunction)(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
);
typedef StatusType (*AR_SVC_ENTITY_ReadPeripheral8)(AreaIdType Area, const uint8* Address, uint8* ReadValue);
typedef StatusType (*AR_SVC_ENTITY_ReadPeripheral16)(AreaIdType Area, const uint16* Address, uint16* ReadValue);
typedef StatusType (*AR_SVC_ENTITY_ReadPeripheral32)(AreaIdType Area, const uint32* Address, uint32* ReadValue);
typedef StatusType (*AR_SVC_ENTITY_WritePeripheral8)(AreaIdType Area, uint8* Address, uint8 WriteValue);
typedef StatusType (*AR_SVC_ENTITY_WritePeripheral16)(AreaIdType Area, uint16* Address, uint16 WriteValue);
typedef StatusType (*AR_SVC_ENTITY_WritePeripheral32)(AreaIdType Area, uint32* Address, uint32 WriteValue);
typedef StatusType (*AR_SVC_ENTITY_ModifyPeripheral8)(AreaIdType Area, uint8* Address, uint8 Clearmask, uint8 Setmask);
typedef StatusType (*AR_SVC_ENTITY_ModifyPeripheral16)(AreaIdType Area, uint16* Address, uint16 Clearmask, uint16 Setmask);
typedef StatusType (*AR_SVC_ENTITY_ModifyPeripheral32)(AreaIdType Area, uint32* Address, uint32 Clearmask, uint32 Setmask);

typedef struct
{
    /* AR_OS_EXIST_C2ISR */
    FUNC_ar_interrupt_init              func_ar_interrupt_init;
    FUNC_ar_CheckISROwnership           func_ar_CheckISROwnership;
    FUNC_ar_cat2_get_iid                func_ar_cat2_get_iid;
    FUNC_ar_get_isrcb                   func_ar_get_isrcb;
    FUNC_ar_get_isr_config              func_ar_get_isr_config;
#if (AR_OS_USE_EXTENDEDSTATUS == STD_ON)
    FUNC_ar_cat2_check_lcid             func_ar_cat2_check_lcid;
#endif /* #if (AR_OS_USE_EXTENDEDSTATUS == STD_ON) */

    /* AR_OS_EXIST_ALARM */
    FUNC_ar_alarm_init                  func_ar_alarm_init;
    FUNC_ar_get_alarm_base_impl         func_ar_get_alarm_base_impl;
    FUNC_ar_get_alarm_impl              func_ar_get_alarm_impl;
    FUNC_ar_set_rel_alarm_impl          func_ar_set_rel_alarm_impl;
    FUNC_ar_set_abs_alarm_impl          func_ar_set_abs_alarm_impl;
    FUNC_ar_cancel_alarm_impl           func_ar_cancel_alarm_impl;
    FUNC_ar_CheckAlarmOwnership         func_ar_CheckAlarmOwnership;

    /* AR_OS_EXIST_C1ISR */
    FUNC_ar_cat1_interrupt_init         func_ar_cat1_interrupt_init;
    FUNC_ar_cat1_get_iid                func_ar_cat1_get_iid;
    FUNC_ar_get_cat1_int_config         func_ar_get_cat1_int_config;
#if (AR_OS_USE_EXTENDEDSTATUS == STD_ON)
    FUNC_ar_cat1_check_lcid             func_ar_cat1_check_lcid;
#endif /* #if (AR_OS_USE_EXTENDEDSTATUS == STD_ON) */

    /* AR_OS_EXIST_COUNTER */
    FUNC_ar_counter_init                func_ar_counter_init;
    FUNC_ar_get_counter_value_impl      func_ar_get_counter_value_impl;
    FUNC_ar_get_elapsed_value_impl      func_ar_get_elapsed_value_impl;
    FUNC_ar_CheckCounterOwnership       func_ar_CheckCounterOwnership;

    /* AR_OS_EXIST_EXTEND_TASK */
    FUNC_ar_set_event_impl              func_ar_set_event_impl;
    FUNC_ar_get_event_impl              func_ar_get_event_impl;

    /* AR_OS_EXIST_IOC */
    FUNC_ar_ioc_init                    func_ar_ioc_init;
    FUNC_ar_ioc_init_queued             func_ar_ioc_init_queued;
    FUNC_ar_ioc_init_unqueued           func_ar_ioc_init_unqueued;
    FUNC_ar_ioc_send_impl               func_ar_ioc_send_impl;
    FUNC_ar_ioc_write_impl              func_ar_ioc_write_impl;
    FUNC_ar_ioc_lock_get                func_ar_ioc_lock_get;
    FUNC_ar_ioc_lock_release            func_ar_ioc_lock_release;

    /* AR_OS_EXIST_RESOURCE */
    FUNC_ar_resource_init               func_ar_resource_init;
    FUNC_ar_task_force_release_resources    func_ar_task_force_release_resources;
    FUNC_ar_c2isr_force_release_resources   func_ar_c2isr_force_release_resources;

    /* AR_OS_EXIST_SPINLOCK */
    FUNC_ar_spinlock_init               func_ar_spinlock_init;
    FUNC_ar_spinlock_force_release      func_ar_spinlock_force_release;
    FUNC_ar_spinlock_cancel             func_ar_spinlock_cancel;

    /* AR_OS_EXIST_TASK */
    FUNC_ar_task_init                   func_ar_task_init;
    FUNC_ar_activate_task_impl          func_ar_activate_task_impl;
    FUNC_ar_get_task_state_impl         func_ar_get_task_state_impl;
    FUNC_ar_CheckTaskOwnership          func_ar_CheckTaskOwnership;

    /* AR_OS_USE_MULTICORE */
    FUNC_ar_set_mastercore_booted       func_ar_set_mastercore_booted;
    FUNC_ar_multicore_init              func_ar_multicore_init;
    FUNC_ar_ici_init                    func_ar_ici_init;
    FUNC_ar_shutdown_allcores_impl      func_ar_shutdown_allcores_impl;
    FUNC_mcos_main_slave                func_mcos_main_slave;
    FUNC_ar_sync_cores                  func_ar_sync_cores;
    FUNC_ar_interrupt_bind              func_ar_interrupt_bind;
    FUNC_mcos_mkmsg_init                func_mcos_mkmsg_init;

    /* AR_OS_USE_SYSTEM_ERRORHOOK */
    FUNC_ar_system_call_errorhook       func_ar_system_call_errorhook;

    /* AR_OS_USE_POSTTASKHOOK */
    FUNC_ar_call_posttaskhook           func_ar_call_posttaskhook;

    /* AR_OS_USE_PRETASKHOOK */
    FUNC_ar_call_pretaskhook            func_ar_call_pretaskhook;

    /* AR_OS_USE_PROTECTIONHOOK */
    FUNC_ar_call_protectionhook         func_ar_call_protectionhook;

    /* AR_OS_USE_SYSTEM_STARTUPHOOK */
    FUNC_ar_system_call_startuphook     func_ar_system_call_startuphook;

    /* AR_OS_USE_SYSTEM_SHUTDOWNHOOK */
    FUNC_ar_system_call_shutdownhook    func_ar_system_call_shutdownhook;

    /* AR_OS_USE_OSAP_ERRORHOOK */
    FUNC_ar_osap_call_errorhook         func_ar_osap_call_errorhook;

    /* AR_OS_USE_OSAP_SHUTDOWNHOOK */
    FUNC_ar_osap_call_shutdownhook      func_ar_osap_call_shutdownhook;

    /* AR_OS_USE_OSAP_STARTUPHOOK */
    FUNC_ar_osap_call_startuphook       func_ar_osap_call_startuphook;

    /* AR_OS_USE_SYSTEM_COUNTER */
    FUNC_ar_system_counter_start        func_ar_system_counter_start;
    FUNC_ar_system_counter_stop         func_ar_system_counter_stop;

    /* AR_OS_EXIST_OSAP */
    FUNC_ar_chk_isr_owner               func_ar_chk_isr_owner;

    /* AR_OS_EXIST_PERIPHERAL_AREA */
    FUNC_ar_peripheral_chk_address      func_ar_peripheral_chk_address;


#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
    /* AR_OS_EXIST_ALARM */
    FUNC_ar_CheckAlarmAccess            func_ar_CheckAlarmAccess;

    /* AR_OS_EXIST_C2ISR */
    FUNC_ar_CheckISRAccess              func_ar_CheckISRAccess;
    FUNC_ar_check_isr_memory            func_ar_check_isr_memory;

    /* AR_OS_EXIST_COUNTER */
    FUNC_ar_forcibly_terminate_counter  func_ar_forcibly_terminate_counter;
    FUNC_ar_CheckCounterAccess          func_ar_CheckCounterAccess;

    /* AR_OS_EXIST_RESOURCE */
    FUNC_ar_CheckResourceAccess         func_ar_CheckResourceAccess;

    /* AR_OS_EXIST_SPINLOCK */
    FUNC_ar_CheckSpinlockAccess         func_ar_CheckSpinlockAccess;

    /* AR_OS_EXIST_TASK */
    FUNC_ar_CheckTaskAccess             func_ar_CheckTaskAccess;
#endif /* #if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
} ar_func_table_t;

typedef struct
{
    AR_SVC_ENTITY_EnableAllInterrupts           ar_svc_entity_enableallinterrupts;          /* [0x00] AR_SVCID_ENABLEALLINTERRUPTS */
    AR_SVC_ENTITY_DisableAllInterrupts          ar_svc_entity_disableallinterrupts;         /* [0x01] AR_SVCID_DISABLEALLINTERRUPTS */
    AR_SVC_ENTITY_ResumeAllInterrupts           ar_svc_entity_resumeallinterrupts;          /* [0x02] AR_SVCID_RESUMEALLINTERRUPTS */
    AR_SVC_ENTITY_SuspendAllInterrupts          ar_svc_entity_suspendallinterrupts;         /* [0x03] AR_SVCID_SUSPENDALLINTERRUPTS */
    AR_SVC_ENTITY_ResumeOSInterrupts            ar_svc_entity_resumeosinterrupts;           /* [0x04] AR_SVCID_RESUMEOSINTERRUPTS */
    AR_SVC_ENTITY_SuspendOSInterrupts           ar_svc_entity_suspendosinterrupts;          /* [0x05] AR_SVCID_SUSPENDOSINTERRUPTS */
    AR_SVC_ENTITY_DisableInterruptSource        ar_svc_entity_disableinterruptsource;       /* [0x06] AR_SVCID_DISABLEINTERRUPTSOURCE */
    AR_SVC_ENTITY_EnableInterruptSource         ar_svc_entity_enableinterruptsource;        /* [0x07] AR_SVCID_ENABLEINTERRUPTSOURCE */
    AR_SVC_ENTITY_CheckTaskMemoryAccess         ar_svc_entity_checktaskmemoryaccess;        /* [0x08] AR_SVCID_CHECKTASKMEMORYACCESS */
    AR_SVC_ENTITY_CheckISRMemoryAccess          ar_svc_entity_checkisrmemoryaccess;         /* [0x09] AR_SVCID_CHECKISRMEMORYACCESS */
    AR_SVC_ENTITY_CheckObjectAccess             ar_svc_entity_checkobjectaccess;            /* [0x0A] AR_SVCID_CHECKOBJECTACCESS */
    AR_SVC_ENTITY_CheckObjectOwnership          ar_svc_entity_checkobjectownership;         /* [0x0B] AR_SVCID_CHECKOBJECTOWNERSHIP */
    AR_SVC_ENTITY_ControlIdle                   ar_svc_entity_controlidle;                  /* [0x0C] AR_SVCID_CONTROLIDLE */
    AR_SVC_ENTITY_GetApplicationState           ar_svc_entity_getapplicationstate;          /* [0x0D] AR_SVCID_GETAPPLICATIONSTATE */
    AR_SVC_ENTITY_GetActiveApplicationMode      ar_svc_entity_getactiveapplicationmode;     /* [0x0E] AR_SVCID_GETACTIVEAPPLICATIONMODE */
    AR_SVC_ENTITY_TerminateApplication          ar_svc_entity_terminateapplication;         /* [0x0F] AR_SVCID_TERMINATEAPPLICATION */
    AR_SVC_ENTITY_AllowAccess                   ar_svc_entity_allowaccess;                  /* [0x10] AR_SVCID_ALLOWACCESS */
    AR_SVC_ENTITY_ar_get_errhk_svcid            ar_svc_entity_ar_get_errhk_svcid;           /* [0x11] AR_SVCID_AR_GET_ERRHK_SVCID */
    AR_SVC_ENTITY_ar_get_errhk_param            ar_svc_entity_ar_get_errhk_param;           /* [0x12] AR_SVCID_AR_GET_ERRHK_PARAM */
    AR_SVC_ENTITY_ShutdownOS                    ar_svc_entity_shutdownos;                   /* [0x13] AR_SVCID_SHUTDOWNOS */
    AR_SVC_ENTITY_ShutdownAllCores              ar_svc_entity_shutdownallcores;             /* [0x14] AR_SVCID_SHUTDOWNALLCORES */
    AR_SVC_ENTITY_GetNumberOfActivatedCores     ar_svc_entity_getnumberofactivatecores;     /* [0x15] AR_SVCID_GETNUMBEROFACTIVATEDCORES */
    AR_SVC_ENTITY_ActivateTask                  ar_svc_entity_activatetask;                 /* [0x16] AR_SVCID_ACTIVATETASK */
    AR_SVC_ENTITY_TerminateTask                 ar_svc_entity_terminatetask;                /* [0x17] AR_SVCID_TERMINATETASK */
    AR_SVC_ENTITY_ChainTask                     ar_svc_entity_chaintask;                    /* [0x18] AR_SVCID_CHAINTASK */
    AR_SVC_ENTITY_Schedule                      ar_svc_entity_schedule;                     /* [0x19] AR_SVCID_SCHEDULE */
    AR_SVC_ENTITY_GetTaskState                  ar_svc_entity_gettaskstate;                 /* [0x1A] AR_SVCID_GETTASKSTATE */
    AR_SVC_ENTITY_ar_illegal_exit_task          ar_svc_entity_ar_illegal_exit_task;         /* [0x1B] AR_SVCID_AR_ILLEGAL_EXIT_TASK */
    AR_SVC_ENTITY_SetEvent                      ar_svc_entity_setevent;                     /* [0x1C] AR_SVCID_SETEVENT */
    AR_SVC_ENTITY_ClearEvent                    ar_svc_entity_clearevent;                   /* [0x1D] AR_SVCID_CLEAREVENT */
    AR_SVC_ENTITY_GetEvent                      ar_svc_entity_getevent;                     /* [0x1E] AR_SVCID_GETEVENT */
    AR_SVC_ENTITY_WaitEvent                     ar_svc_entity_waitevent;                    /* [0x1F] AR_SVCID_WAITEVENT */
    AR_SVC_ENTITY_GetResource                   ar_svc_entity_getresource;                  /* [0x20] AR_SVCID_GETRESOURCE */
    AR_SVC_ENTITY_ReleaseResource               ar_svc_entity_releaseresource;              /* [0x21] AR_SVCID_RELEASERESOURCE */
    AR_SVC_ENTITY_IncrementCounter              ar_svc_entity_incrementcounter;             /* [0x22] AR_SVCID_INCREMENTCOUNTER */
    AR_SVC_ENTITY_GetCounterValue               ar_svc_entity_getcountervalue;              /* [0x23] AR_SVCID_GETCOUNTERVALUE */
    AR_SVC_ENTITY_GetElapsedValue               ar_svc_entity_getelapsedvalue;              /* [0x24] AR_SVCID_GETELAPSEDVALUE */
    AR_SVC_ENTITY_GetAlarmBase                  ar_svc_entity_getalarmbase;                 /* [0x25] AR_SVCID_GETALARMBASE */
    AR_SVC_ENTITY_GetAlarm                      ar_svc_entity_getalarm;                     /* [0x26] AR_SVCID_GETALARM */
    AR_SVC_ENTITY_SetRelAlarm                   ar_svc_entity_setrelalarm;                  /* [0x27] AR_SVCID_SETRELALARM */
    AR_SVC_ENTITY_SetAbsAlarm                   ar_svc_entity_setabsalarm;                  /* [0x28] AR_SVCID_SETABSALARM */
    AR_SVC_ENTITY_CancelAlarm                   ar_svc_entity_cancelalarm;                  /* [0x29] AR_SVCID_CANCELALARM */
    AR_SVC_ENTITY_CallTrustedFunction           ar_svc_entity_calltrustedfunction;          /* [0x2A] AR_SVCID_CALLTRUSTEDFUNCTION */
    AR_SVC_ENTITY_ar_ioc_send                   ar_svc_entity_ar_ioc_send;                  /* [0x2B] AR_SVCID_AR_IOC_SEND */
    AR_SVC_ENTITY_ar_ioc_write                  ar_svc_entity_ar_ioc_write;                 /* [0x2C] AR_SVCID_AR_IOC_WRITE */
    AR_SVC_ENTITY_ar_ioc_receive                ar_svc_entity_ar_ioc_recive;                /* [0x2D] AR_SVCID_AR_IOC_RECEIVE */
    AR_SVC_ENTITY_ar_ioc_read                   ar_svc_entity_ar_ioc_read;                  /* [0x2E] AR_SVCID_AR_IOC_READ */
    AR_SVC_ENTITY_ar_ioc_empty_queue            ar_svc_entity_ar_ioc_empty_queue;           /* [0x2F] AR_SVCID_AR_IOC_EMPTY_QUEUE */
    AR_SVC_ENTITY_GetSpinlock                   ar_svc_entity_getspinlock;                  /* [0x30] AR_SVCID_GETSPINLOCK */
    AR_SVC_ENTITY_ReleaseSpinlock               ar_svc_entity_releasespinlock;              /* [0x31] AR_SVCID_RELEASESPINLOCK */
    AR_SVC_ENTITY_TryToGetSpinlock              ar_svc_entity_trytogetspinlock;             /* [0x32] AR_SVCID_TRYTOGETSPINLOCK */
    AR_SVC_ENTITY_RaiseInterCoreInterrupt       ar_svc_entity_raiseintercoreinterrupt;      /* [0x33] AR_SVCID_RAISEINTERCOREINTERRUPT */
    AR_SVC_ENTITY_GetSpinlockSkipErrorChk       ar_svc_entity_getspinlockskiperrorchk;      /* [0x34] AR_SVCID_GETSPINLOCKSKIPERRORCHK */
    AR_SVC_ENTITY_ReleaseSpinlockSkipErrorChk   ar_svc_entity_releasespinlockskiperrorchk;  /* [0x35] AR_SVCID_RELEASESPINLOCKSKIPERRORCHK */
    AR_SVC_ENTITY_TryToGetSpinlockSkipErrorChk  ar_svc_entity_trytogetspinlockskiperrorchk; /* [0x36] AR_SVCID_TRYTOGETSPINLOCKSKIPERRORCHK */
    AR_SVC_ENTITY_ar_errorhook_call             ar_svc_entity_ar_errorhook_call;            /* [0x37] AR_SVCID_AR_ERRORHOOK_CALL */
    AR_SVC_ENTITY_ActivateTaskAsyn              ar_svc_entity_activatetask_asyn;            /* [0x38] AR_SVCID_ACTIVATETASKASYN */
    AR_SVC_ENTITY_SetEventAsyn                  ar_svc_entity_setevent_asyn;                /* [0x39] AR_SVCID_SETEVENTASYN */
    AR_SVC_ENTITY_ClearPendingInterrupt         ar_svc_clear_pending_interrupt;             /* [0x3A] AR_SVCID_CLEARPENDINGINTERRUPT */
    AR_SVC_ENTITY_ReadPeripheral8               ar_svc_read_peripheral8;                    /* [0x3B] AR_SVCID_READPERIPHERAL8 */
    AR_SVC_ENTITY_ReadPeripheral16              ar_svc_read_peripheral16;                   /* [0x3C] AR_SVCID_READPERIPHERAL16 */
    AR_SVC_ENTITY_ReadPeripheral32              ar_svc_read_peripheral32;                   /* [0x3D] AR_SVCID_READPERIPHERAL32 */
    AR_SVC_ENTITY_WritePeripheral8              ar_svc_write_peripheral8;                   /* [0x3E] AR_SVCID_WRITEPERIPHERAL8 */
    AR_SVC_ENTITY_WritePeripheral16             ar_svc_write_peripheral16;                  /* [0x3F] AR_SVCID_WRITEPERIPHERAL16 */
    AR_SVC_ENTITY_WritePeripheral32             ar_svc_write_peripheral32;                  /* [0x40] AR_SVCID_WRITEPERIPHERAL32 */
    AR_SVC_ENTITY_ModifyPeripheral8             ar_svc_modify_peripheral8;                  /* [0x41] AR_SVCID_MODIFYPERIPHERAL8 */
    AR_SVC_ENTITY_ModifyPeripheral16            ar_svc_modify_peripheral16;                 /* [0x42] AR_SVCID_MODIFYPERIPHERAL16 */
    AR_SVC_ENTITY_ModifyPeripheral32            ar_svc_modify_peripheral32;                 /* [0x43] AR_SVCID_MODIFYPERIPHERAL32 */
} ar_svc_table_t;

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern const ar_func_table_t                ar_func_table;

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern const ar_svc_table_t                 ar_svc_table;

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"
#endif /* #if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

/*
 * dummy functions
 */
#define OS_START_SEC_CODE
#include "Os_MemMap.h"

extern void ar_dummy_void_void(void);
extern StatusType ar_dummy_mkmsg_get_alarm_base_impl(const AlarmType alarm_id, const AlarmBaseRefType p_info, const ar_osap_config_t * const p_osapconfig);
extern StatusType ar_dummy_mkmsg_get_alarm_impl(const AlarmType alarm_id, const TickRefType p_tick, const ar_osap_config_t * const p_osapconfig);
extern StatusType ar_dummy_mkmsg_set_rel_alarm_impl(const mkcb_t * const mkcb, const AlarmType alarm_id, const TickType increment, const TickType cycle, const ar_osap_config_t * const p_osapconfig);
extern StatusType ar_dummy_mkmsg_set_abs_alarm_impl(const AlarmType alarm_id, const TickType start, const TickType cycle, const ar_osap_config_t * const p_osapconfig);
extern StatusType ar_dummy_mkmsg_cancel_alarm_impl(const mkcb_t * const mkcb, const AlarmType alarm_id, const ar_osap_config_t * const p_osapconfig);
extern StatusType ar_dummy_mkmsg_get_counter_value_impl(const CounterType counter_id, const TickRefType p_value, const ar_osap_config_t * const p_osapconfig);
extern StatusType ar_dummy_mkmsg_get_elapsed_value_impl(const CounterType counter_id, const TickRefType p_value, const TickRefType p_elapsed_value, const ar_osap_config_t * const p_osapconfig);
extern StatusType ar_dummy_mkmsg_set_event_impl(clscb_t * const clscb, const TaskType task_id, const EventMaskType event, const ar_osap_config_t * const p_osapconfig);

extern StatusType ar_dummy_mkmsg_get_event_impl(
#if (AR_OS_USE_EXTENDEDSTATUS == STD_ON)
        clscb_t * const clscb,
#endif /* #if (AR_OS_USE_EXTENDEDSTATUS == STD_ON) */
        const TaskType task_id, const EventMaskRefType p_event, const ar_osap_config_t * const p_osapconfig);

extern Std_ReturnType ar_dummy_mkmsg_ioc_send_impl(const mkcb_t * const mkcb, const IocType receiver_id, const void * const in);
extern void ar_dummy_mkmsg_ioc_write_impl(const mkcb_t * const mkcb, const IocType receiver_id, const void * const in);
extern StatusType ar_dummy_ar_task_init(void);
extern StatusType ar_dummy_mkmsg_activate_task_impl(clscb_t * const clscb, const TaskType task_id, const ar_osap_config_t * const p_osapconfig);
extern StatusType ar_dummy_mkmsg_get_task_state_impl(const mkcb_t *const mkcb, const TaskType task_id, const TaskStateRefType p_state, const ar_osap_config_t * const p_osapconfig);
extern void ar_dummy_mcos_main_slave(const int32_t pcid, const void * const ptr);
extern void ar_dummy_ar_sync_cores(const uint8 phase, const boolean check_shutdown);
extern void ar_dummy_mcos_mkmsg_init(const mkcb_t * const mkcb);
extern void ar_dummy_call_system_errorhook(const mkcb_t *mkcb, clscb_t *clscb, StatusType status);
extern void ar_dummy_ar_system_call_shutdownhook(const mkcb_t *mkcb, clscb_t *clscb, StatusType status);
extern ProtectionReturnType ar_dummy_ar_call_protectionhook(const mkcb_t *mkcb, clscb_t *clscb, StatusType status);
extern int32_t ar_dummy_ar_system_call_startuphook(const mkcb_t *mkcb, clscb_t *clscb, int32_t sr);
extern void ar_dummy_ar_osap_call_errorhook(const StatusType status, const OSServiceIdType svcid);
extern void ar_dummy_ar_osap_call_shutdownhook(const StatusType status);
extern int32_t ar_dummy_ar_osap_call_startuphook(int32_t sr, CoreIdType my_core_id);
extern void ar_dummy_ar_task_force_release_resources(ar_tcb_t * const p_atcb);
extern void ar_dummy_ar_c2isr_force_release_resources(ar_isrcb_t * const p_isrcb);
extern void ar_dummy_ar_spinlock_force_release(ar_spinlockcb_t * const p_last_spinlockcb);
extern void ar_dummy_ar_spinlock_cancel(ar_spinlockcb_t * const p_last_spinlockcb);
extern void ar_dummy_ar_ioc_init_queued(IocType ioc_id);
extern void ar_dummy_ar_ioc_init_unqueued(IocType ioc_id, const ar_ioc_config_t * const p_config, const ar_ioc_receiver_config_t *p_receiver_config);
extern void ar_dummy_ar_ioc_lock(const ar_ioc_config_t * const p_config);
extern ApplicationType ar_dummy_CheckObjectOwnership(uint32 object_id);

#if (AR_OS_USE_EXTENDEDSTATUS == STD_ON)
extern StatusType ar_dummy_ar_check_lcid(ISRType ISRID);
#endif /* #if (AR_OS_USE_EXTENDEDSTATUS == STD_ON) */
extern mcos_id_t ar_dummy_ar_cat1_get_iid(ISRType ISRID);
extern mcos_id_t ar_dummy_ar_cat2_get_iid(ISRType ISRID);
extern const ar_cat1_int_config_t *ar_dummy_get_cat1_int_config(ISRType cat1isr);
extern ar_isrcb_t *ar_dummy_get_isrcb(ISRType cat2isr);
extern const ar_isr_config_t *ar_dummy_get_isr_config(ISRType cat2isr);

extern StatusType ar_dummy_ar_chk_isr_owner(ISRType ISRID, const clscb_t *clscb);
extern StatusType ar_dummy_ar_peripheral_chk_address(const clscb_t* clscb, AreaIdType Area, const void* Address, uint32 Range);

#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
extern ObjectAccessType ar_dummy_ar_CheckAlarmAccess(ApplicationType ApplID, AlarmType alarm_id);
extern ObjectAccessType ar_dummy_ar_CheckISRAccess(ApplicationType ApplID, ISRType ISRID);
extern AccessType ar_dummy_ar_check_isr_memory(ISRType ISRID, ConstMemoryStartAddressType start, MemorySizeType size);
extern void ar_dummy_ar_forcibly_terminate_counter(const ar_osap_config_t * p_osapconfig);
extern ObjectAccessType ar_dummy_ar_CheckCounterAccess(ApplicationType ApplID, CounterType CounterID);
extern ObjectAccessType ar_dummy_ar_CheckResourceAccess(ApplicationType ApplID, ResourceType ResourceID);
extern ObjectAccessType ar_dummy_ar_CheckSpinlockAccess(ApplicationType ApplID, SpinlockIdType spinlock_id);
extern ObjectAccessType ar_dummy_ar_CheckTaskAccess(ApplicationType ApplID, TaskType TaskID);
#endif /* #if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

extern void ar_nspt_svc_EnableAllInterrupts(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
extern void ar_nspt_svc_DisableAllInterrupts(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
extern void ar_nspt_svc_ResumeAllInterrupts(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
extern void ar_nspt_svc_SuspendAllInterrupts(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
extern void ar_nspt_svc_ResumeOSInterrupts(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
extern void ar_nspt_svc_SuspendOSInterrupts(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_DisableInterruptSource(ISRType ISRID
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_EnableInterruptSource(ISRType ISRID, boolean ClearPending
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_ClearPendingInterrupt(ISRType ISRID
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern AccessType ar_nspt_svc_CheckTaskMemoryAccess(TaskType TaskID, MemoryStartAddressType Address, MemorySizeType Size
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern AccessType ar_nspt_svc_CheckISRMemoryAccess(ISRType ISRID, MemoryStartAddressType Address, MemorySizeType Size
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern AccessType ar_nspt_svc_CheckObjectAccess(ApplicationType ApplID, ObjectTypeType ObjectType, uint32 ObjectID
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern AccessType ar_nspt_svc_CheckObjectOwnership(ObjectTypeType object_type, uint32 object_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
extern StatusType ar_nspt_svc_TerminateApplication(ApplicationType Application, RestartType RestartOption
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_AllowAccess(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
extern OSServiceIdType ar_nspt_svc_ar_get_errhk_svcid(void);
extern uint32 ar_nspt_svc_ar_get_errhk_param(uint8 par_num);
extern void ar_nspt_svc_ShutdownOS(StatusType Error
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern void ar_nspt_svc_ShutdownAllCores(StatusType Error
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern uint32 ar_nspt_svc_GetNumberOfActivatedCores(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_ActivateTask(TaskType TaskID
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern void ar_nspt_svc_ActivateTaskAsyn(TaskType TaskID
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_TerminateTask(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_ChainTask(TaskType TaskID
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_Schedule(
#if !MCOS_CFG_DS_TRACE_LOG_API
    void
#else /* !MCOS_CFG_DS_TRACE_LOG_API */
    const void *p_ret_adr
#endif /* !MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_GetTaskState(TaskType TaskID, TaskStateRefType State
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_SetEvent(TaskType task_id, EventMaskType event
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern void ar_nspt_svc_SetEventAsyn(TaskType task_id, EventMaskType event
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_ClearEvent(EventMaskType event
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_GetEvent(TaskType task_id, EventMaskRefType p_event
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_WaitEvent(EventMaskType event
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_GetResource(ResourceType resource_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_ReleaseResource(ResourceType resource_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_IncrementCounter(CounterType counter_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_GetCounterValue(CounterType counter_id, TickRefType p_value
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_GetElapsedValue(CounterType counter_id, TickRefType p_value, TickRefType p_elapsed_value
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_GetAlarmBase(AlarmType alarm_id, AlarmBaseRefType p_info
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_GetAlarm(AlarmType alarm_id, TickRefType p_tick
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_SetRelAlarm(AlarmType alarm_id, TickType increment, TickType cycle
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_SetAbsAlarm(AlarmType alarm_id, TickType start, TickType cycle
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_CancelAlarm(AlarmType alarm_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
extern StatusType ar_nspt_svc_CallTrustedFunction(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
extern Std_ReturnType ar_nspt_svc_ar_ioc_send(IocType ioc_sender_id, void *in
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern Std_ReturnType ar_nspt_svc_ar_ioc_write(IocType ioc_sender_id, void *in
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern Std_ReturnType ar_nspt_svc_ar_ioc_receive(IocType receiver_id, void *out
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern Std_ReturnType ar_nspt_svc_ar_ioc_read(IocType receiver_id, void *out
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_ar_ioc_empty_queue(IocType receiver_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_GetSpinlock(SpinlockIdType spinlock_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_ReleaseSpinlock(SpinlockIdType spinlock_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_TryToGetSpinlock(SpinlockIdType spinlock_id, TryToGetSpinlockType *p_success
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_RaiseInterCoreInterrupt(CoreIdType CoreID
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_GetSpinlockSkipErrorChk(SpinlockIdType spinlock_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_ReleaseSpinlockSkipErrorChk(SpinlockIdType spinlock_id
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern StatusType ar_nspt_svc_TryToGetSpinlockSkipErrorChk(SpinlockIdType spinlock_id, TryToGetSpinlockType *p_success
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );
extern void ar_nspt_svc_ar_errorhook_call(const StatusType status, const OSServiceIdType svcid, const ar_errhk_param_t errhk_param[AR_ERRHK_PARAM_NUM]);
extern StatusType ar_nspt_svc_CallFastTrustedFunction(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams
#if MCOS_CFG_DS_TRACE_LOG_API
    , const void *p_ret_adr
#endif /* MCOS_CFG_DS_TRACE_LOG_API */
    );


#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

/*
 * call macros
 */
#define CALL_ar_interrupt_init()     (ar_func_table.func_ar_interrupt_init)()
#define CALL_ar_check_isr_memory(ISRID, start, size)     (ar_func_table.func_ar_check_isr_memory)(ISRID, start, size)
#define CALL_ar_CheckISROwnership(object_id)     (ar_func_table.func_ar_CheckISROwnership)(object_id)
#define CALL_ar_cat2_get_iid(ISRID)  (ar_func_table.func_ar_cat2_get_iid)(ISRID)
#define CALL_ar_get_isrcb(ISRID)       (ar_func_table.func_ar_get_isrcb)(ISRID)
#define CALL_ar_get_isr_config(ISRID)  (ar_func_table.func_ar_get_isr_config)(ISRID)
#define CALL_ar_get_cat1_int_config(ISRID) (ar_func_table.func_ar_get_cat1_int_config)(ISRID)
#define CALL_ar_alarm_init()     (ar_func_table.func_ar_alarm_init)()
#define CALL_ar_get_alarm_base_impl(alarm_id, p_info, p_osapconfig)     (ar_func_table.func_ar_get_alarm_base_impl)(alarm_id, p_info, p_osapconfig)
#define CALL_ar_get_alarm_impl(alarm_id, p_tick, p_osapconfig)     (ar_func_table.func_ar_get_alarm_impl)(alarm_id, p_tick, p_osapconfig)
#define CALL_ar_set_rel_alarm_impl(mkcb, alarm_id, increment, cycle, p_osapconfig)     (ar_func_table.func_ar_set_rel_alarm_impl)(mkcb, alarm_id, increment, cycle, p_osapconfig)
#define CALL_ar_set_abs_alarm_impl(alarm_id, start, cycle, p_osapconfig)     (ar_func_table.func_ar_set_abs_alarm_impl)(alarm_id, start, cycle, p_osapconfig)
#define CALL_ar_cancel_alarm_impl(mkcb, alarm_id, p_osapconfig)     (ar_func_table.func_ar_cancel_alarm_impl)(mkcb, alarm_id, p_osapconfig)
#define CALL_ar_CheckAlarmOwnership(object_id)     (ar_func_table.func_ar_CheckAlarmOwnership)(object_id)
#define CALL_ar_cat1_interrupt_init()     (ar_func_table.func_ar_cat1_interrupt_init)()
#define CALL_ar_counter_init()     (ar_func_table.func_ar_counter_init)()
#define CALL_ar_get_counter_value_impl(counter_id, p_value, p_osapconfig)     (ar_func_table.func_ar_get_counter_value_impl)(counter_id, p_value, p_osapconfig)
#define CALL_ar_get_elapsed_value_impl(counter_id, p_value, p_elapsed_value, p_osapconfig)     (ar_func_table.func_ar_get_elapsed_value_impl)(counter_id, p_value, p_elapsed_value, p_osapconfig)
#define CALL_ar_CheckCounterOwnership(object_id)     (ar_func_table.func_ar_CheckCounterOwnership)(object_id)
#define CALL_ar_set_event_impl(clscb, task_id, event, p_osapconfig)     (ar_func_table.func_ar_set_event_impl)(clscb, task_id, event, p_osapconfig)

#if (AR_OS_USE_EXTENDEDSTATUS == STD_ON)
#define CALL_ar_get_event_impl(clscb, task_id, p_event, p_osapconfig) (ar_func_table.func_ar_get_event_impl)(clscb, task_id, p_event, p_osapconfig)
#else /* #if (AR_OS_USE_EXTENDEDSTATUS == STD_ON) */
#define CALL_ar_get_event_impl(task_id, p_event, p_osapconfig)        (ar_func_table.func_ar_get_event_impl)(task_id, p_event, p_osapconfig)
#endif /* #if (AR_OS_USE_EXTENDEDSTATUS == STD_ON) */

#define CALL_ar_ioc_init()     (ar_func_table.func_ar_ioc_init)()
#define CALL_ar_ioc_init_queued(ioc_id)  (ar_func_table.func_ar_ioc_init_queued)(ioc_id)
#define CALL_ar_ioc_init_unqueued(ioc_id, p_config, p_receiver_config)  (ar_func_table.func_ar_ioc_init_unqueued)(ioc_id, p_config, p_receiver_config)
#define CALL_ar_ioc_send_impl(mkcb, receiver_id, in)     (ar_func_table.func_ar_ioc_send_impl)(mkcb, receiver_id, in)
#define CALL_ar_ioc_write_impl(mkcb, receiver_id, in)     (ar_func_table.func_ar_ioc_write_impl)(mkcb, receiver_id, in)
#define CALL_ar_ioc_lock_get(p_config)     (ar_func_table.func_ar_ioc_lock_get)(p_config)
#define CALL_ar_ioc_lock_release(p_config)     (ar_func_table.func_ar_ioc_lock_release)(p_config)
#define CALL_ar_resource_init()     (ar_func_table.func_ar_resource_init)()
#define CALL_ar_task_force_release_resources(p_atcb)     (ar_func_table.func_ar_task_force_release_resources)(p_atcb)
#define CALL_ar_c2isr_force_release_resources(p_isrcb)     (ar_func_table.func_ar_c2isr_force_release_resources)(p_isrcb)
#define CALL_ar_spinlock_init()     (ar_func_table.func_ar_spinlock_init)()
#define CALL_ar_spinlock_force_release(p_last_spinlockcb)     (ar_func_table.func_ar_spinlock_force_release)(p_last_spinlockcb)
#define CALL_ar_task_init()     (ar_func_table.func_ar_task_init)()
#define CALL_ar_activate_task_impl(clscb, task_id, p_osapconfig)     (ar_func_table.func_ar_activate_task_impl)(clscb, task_id, p_osapconfig)
#define CALL_ar_get_task_state_impl(mkcb, task_id, p_state, p_osapconfig)     (ar_func_table.func_ar_get_task_state_impl)(mkcb, task_id, p_state, p_osapconfig)
#define CALL_ar_CheckTaskOwnership(object_id)     (ar_func_table.func_ar_CheckTaskOwnership)(object_id)
#define CALL_ar_set_mastercore_booted()     (ar_func_table.func_ar_set_mastercore_booted)()
#define CALL_ar_multicore_init()     (ar_func_table.func_ar_multicore_init)()
#define CALL_ar_ici_init()     (ar_func_table.func_ar_ici_init)()
#define CALL_ar_shutdown_allcores_impl(status)     (ar_func_table.func_ar_shutdown_allcores_impl)(status)
#define CALL_mcos_main_slave(pcid, ptr)     (ar_func_table.func_mcos_main_slave)(pcid, ptr)
#define CALL_ar_sync_cores(phase, check_shutdown)     (ar_func_table.func_ar_sync_cores)(phase, check_shutdown)
#define CALL_mcos_mkmsg_init(mkcb)   (ar_func_table.func_mcos_mkmsg_init)(mkcb)

#define CALL_ar_system_call_errorhook(mkcb, clscb, status)    (ar_func_table.func_ar_system_call_errorhook)(mkcb, clscb, status)
#define CALL_ar_call_posttaskhook()    (ar_func_table.func_ar_call_posttaskhook)()
#define CALL_ar_call_pretaskhook()    (ar_func_table.func_ar_call_pretaskhook)()
#define CALL_ar_call_protectionhook(mkcb, clscb, status)    (ar_func_table.func_ar_call_protectionhook)(mkcb, clscb, status)
#define CALL_ar_system_call_startuphook(mkcb, clscb, sr)    (ar_func_table.func_ar_system_call_startuphook)(mkcb, clscb, sr)
#define CALL_ar_system_call_shutdownhook(mksb, clscb, status)    (ar_func_table.func_ar_system_call_shutdownhook)(mkcb, clscb, status)

#define CALL_ar_osap_call_errorhook(status, svcid)     (ar_func_table.func_ar_osap_call_errorhook)(status, svcid)
#define CALL_ar_osap_call_shutdownhook(status)     (ar_func_table.func_ar_osap_call_shutdownhook)(status)
#define CALL_ar_osap_call_startuphook(sr, my_core_id)     (ar_func_table.func_ar_osap_call_startuphook)(sr, my_core_id)
#define CALL_ar_system_counter_start()     (ar_func_table.func_ar_system_counter_start)()
#define CALL_ar_system_counter_stop()     (ar_func_table.func_ar_system_counter_stop)()
#define CALL_ar_interrupt_bind()     (ar_func_table.func_ar_interrupt_bind)()

#define CALL_ar_chk_isr_owner(ISRID, clscb)   (ar_func_table.func_ar_chk_isr_owner)(ISRID, clscb)
#define CALL_ar_peripheral_chk_address(clscb, Area, Address, Range)    (ar_func_table.func_ar_peripheral_chk_address)(clscb, Area, Address, Range)

#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)

#define CALL_ar_CheckAlarmAccess(ApplID, alarm_id)     (ar_func_table.func_ar_CheckAlarmAccess)(ApplID, alarm_id)
#define CALL_ar_CheckISRAccess(ApplID, ISRID)     (ar_func_table.func_ar_CheckISRAccess)(ApplID, ISRID)
#define CALL_ar_CheckCounterAccess(ApplID, CounterID)     (ar_func_table.func_ar_CheckCounterAccess)(ApplID, CounterID)
#define CALL_ar_CheckResourceAccess(ApplID, ResourceID)     (ar_func_table.func_ar_CheckResourceAccess)(ApplID, ResourceID)
#define CALL_ar_CheckSpinlockAccess(ApplID, spinlock_id)     (ar_func_table.func_ar_CheckSpinlockAccess)(ApplID, spinlock_id)
#define CALL_ar_CheckTaskAccess(ApplID, TaskID)     (ar_func_table.func_ar_CheckTaskAccess)(ApplID, TaskID)

#endif /* #if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

#endif /* AR_CALL_FUNC_H */
