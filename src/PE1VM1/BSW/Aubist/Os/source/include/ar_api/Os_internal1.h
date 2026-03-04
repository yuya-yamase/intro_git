/*
    Copyright (C) 2018 By eSOL Co.,Ltd. Tokyo, Japan

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
[Os_internal1.h] - Os module header
****************************************************************************/

#ifndef OS_INTERNAL1_H
#define OS_INTERNAL1_H

/* AUTOSAR specification version information [SWS_BSW_00059] */
#define OS_VENDOR_ID                    (0x003DU)
#define OS_MODULE_ID                    (0x0001U)
#define OS_AR_RELEASE_MAJOR_VERSION     (4U)
#define OS_AR_RELEASE_MINOR_VERSION     (5U)
#define OS_AR_RELEASE_REVISION_VERSION  (0U)
#define OS_SW_MAJOR_VERSION             (1U)
#define OS_SW_MINOR_VERSION             (2U)
#define OS_SW_PATCH_VERSION             (0U)

#include "Std_Types.h"
#if defined __ARMCC_VERSION
#if defined __arm__
#if __ARMCC_VERSION >= 6000000U
#define AR_FORCE_INLINE                 inline __attribute__((always_inline))
#define AR_LOCAL_FORCE_INLINE           static inline __attribute__((always_inline))

#else /* #if __ARMCC_VERSION >= 6000000U */
    #error This compiler is not supported.
#endif /* #if __ARMCC_VERSION >= 6000000U */
#else /* #if defined __arm__ */
    #error This compiler is not supported.
#endif /* #elif definede __arm__ */

#else /* #if defined __ARMCC_VERSION */
#define AR_FORCE_INLINE                 inline
#define AR_LOCAL_FORCE_INLINE           static inline

#endif /* #if defined __ARMCC_VERSION */


/*
 * Data Types
 */

typedef uint8   TaskStateType;
typedef uint32  EventMaskType;
typedef uint32  TickType;
typedef uint32  AppModeType;
typedef uint8   OSServiceIdType;
typedef uint8   ProtectionReturnType;
typedef uint8   ApplicationType;
typedef uint8   ObjectTypeType;
typedef unsigned long MemorySizeType;
typedef uint8   ApplicationStateType;
typedef uint8   AccessType;
typedef boolean ObjectAccessType;
typedef uint8   RestartType;
typedef float32 PhysicalTimeType;

typedef struct {
    TickType    maxallowedvalue;
    TickType    ticksperbase;
    TickType    mincycle;
} AlarmBaseType;

typedef uint8   TryToGetSpinlockType;
#define TRYTOGETSPINLOCK_SUCCESS    ((TryToGetSpinlockType) 0)
#define TRYTOGETSPINLOCK_NOSUCCESS  ((TryToGetSpinlockType) 1)

typedef uint32  AlarmType;
typedef uint32  ResourceType;
typedef uint32  TaskType;
typedef uint32  ISRType;
typedef uint32  CounterType;
typedef uint8   CoreIdType;
typedef uint32  SpinlockIdType;
typedef uint32  IocType;
typedef uint32  TrustedFunctionIndexType;
typedef uint32  AreaIdType;

typedef uint8   IdleModeType;
#define IDLE_NO_HALT    ((IdleModeType) 0)

typedef AlarmBaseType *             AlarmBaseRefType;
typedef TaskType *                  TaskRefType;
typedef TaskStateType *             TaskStateRefType;
typedef EventMaskType *             EventMaskRefType;
typedef TickType *                  TickRefType;
typedef ApplicationStateType *      ApplicationStateRefType;
typedef void *                      MemoryStartAddressType;
typedef void *                      TrustedFunctionParameterRefType;
/* CAUTION! This type prohibits its use outside of eMCOS AUTOSAR. */
typedef void const *                ConstMemoryStartAddressType;

#define DeclareTask(TaskIdentifier)
#define DeclareResource(ResourceIdentifier)
#define DeclareEvent(EventIdentifier)
#define DeclareAlarm(AlarmIdentifier)

#define TASK(TaskName)  void ar_task_entry_  ## TaskName(void)
#define ISR(ISRName)    void ar_isr_entry_   ## ISRName(void)
#define C1ISR(ISRName)  void ar_c1isr_entry_ ## ISRName(void)
#define ALARMCALLBACK(AlarmCallBackName) \
    void ar_alarm_entry_ ## AlarmCallBackName(void)

typedef union {
    TaskType                        d_task;
    TaskRefType                     d_taskref;
    TaskStateRefType                d_taskstateref;
    ISRType                         d_isr;
    ResourceType                    d_resource;
    EventMaskType                   d_eventmask;
    EventMaskRefType                d_eventmaskref;
    AlarmType                       d_alarm;
    AlarmBaseRefType                d_alarmbaseref;
    TickRefType                     d_tickref;
    TickType                        d_tick;
    AppModeType                     d_appmode;
    StatusType                      d_status;
    StatusType                      *d_statusref;
    TrustedFunctionIndexType        d_trustedfunctionindex;
    TrustedFunctionParameterRefType d_trustedfunctionparameterref;
    CounterType                     d_counter;
    ApplicationType                 d_application;
    RestartType                     d_restart;
    ApplicationStateRefType         d_applicationstateref;
    CoreIdType                      d_coreid;
    IdleModeType                    d_idlemode;
    IocType                         d_ioc;
    SpinlockIdType                  d_spinlockid;
    TryToGetSpinlockType            *d_trytogetspinlockref;
    MemorySizeType                  d_memorysize;
    MemoryStartAddressType          d_memorystartaddress;
    ObjectTypeType                  d_objecttype;
    AreaIdType                      d_areaid;
    uint32                          d_uint32;
    boolean                         d_clearpending;
    void const                      *d_address;
    void                            *d_readvalue;
    uint32                          d_writevalue;
    uint32                          d_clearmask;
    uint32                          d_setmask;
} ar_errhk_param_t;

/*
 * Error Code
 */
#define E_OS_ACCESS                         (1U)
#define E_OS_CALLEVEL                       (2U)
#define E_OS_ID                             (3U)
#define E_OS_LIMIT                          (4U)
#define E_OS_NOFUNC                         (5U)
#define E_OS_RESOURCE                       (6U)
#define E_OS_STATE                          (7U)
#define E_OS_VALUE                          (8U)
#define E_OS_SERVICEID                      (9U)
#define E_OS_ILLEGAL_ADDRESS                (10U)
#define E_OS_MISSINGEND                     (11U)
#define E_OS_DISABLEDINT                    (12U)
#define E_OS_STACKFAULT                     (13U)
#define E_OS_PROTECTION_MEMORY              (14U)
#define E_OS_PROTECTION_TIME_TASK           (15U)
#define E_OS_PROTECTION_TIME_ISR            (16U)
#define E_OS_PROTECTION_ARRIVAL_TASK        (17U)
#define E_OS_PROTECTION_ARRIVAL_ISR         (18U)
#define E_OS_PROTECTION_LOCKED_RESOURCE     (19U)
#define E_OS_PROTECTION_LOCKED_OSINT        (20U)
#define E_OS_PROTECTION_LOCKED_ALLINT       (21U)
#define E_OS_PROTECTION_EXCEPTION           (22U)
#define E_OS_PROTECTION_FATAL               (23U)
#define E_OS_MODE                           (24U)
#define E_OS_SHUTDOWN_FATAL                 (25U)
#define E_OS_PARAM_POINTER                  (26U)
#define E_OS_SYS_ASSERT_FATAL               (27U)
#define E_OS_STACKINSUFFICIENT              (28U)
#define E_OS_CORE                           (29U)
#define E_OS_SPINLOCK                       (30U)
#define E_OS_INTERFERENCE_DEADLOCK          (31U)
#define E_OS_NESTING_DEADLOCK               (32U)
#define E_OS_SHUTDOWN_OTHER_CORE            (33U)
#define E_OS_SYS_ILLEGAL_ADDRESS            (34U)
#define E_OS_SYSTEM                         (35U)
#define E_OS_INSUFFICIENT_SYSTEM_MEMORY     (36U)
#define E_OS_INSUFFICIENT_OSAP_MEMORY       (37U)
#define AR_ERRCODE_NUM                      (37U)

#define IOC_E_OK            (0U)
#define IOC_E_NOK           (1U)
#define IOC_E_LIMIT         (130U)
#define IOC_E_LOST_DATA     (64U)
#define IOC_E_NO_DATA       (131U)

#define UINT32_INVALID      (0xffffffffU)
#define UINT8_INVALID       (0xffU)

#define SUSPENDED           ((TaskStateType) 0)
#define RUNNING             ((TaskStateType) 1)
#define READY               ((TaskStateType) 2)
#define WAITING             ((TaskStateType) 3)

#define INVALID_TASK            ((TaskType) UINT32_INVALID)
#define INVALID_COUNTER         ((CounterType) UINT32_INVALID)
#define INVALID_ISR             ((ISRType) UINT32_INVALID)
#define INVALID_APPMODE         ((AppModeType) UINT32_INVALID)
#define INVALID_OSAPPLICATION   ((ApplicationType) UINT8_INVALID)
#define INVALID_SPINLOCK        ((SpinlockIdType) UINT32_INVALID)

#define DONOTCARE           ((AppModeType) UINT32_INVALID)

#define APPLICATION_ACCESSIBLE  ((ApplicationStateType) 0)
#define APPLICATION_RESTARTING  ((ApplicationStateType) 1)
#define APPLICATION_TERMINATED  ((ApplicationStateType) 2)

#define ACCESS      (TRUE)
#define NO_ACCESS   (FALSE)


#define OSServiceId_ActivateTask                ((OSServiceIdType) 0xe0)
#define OSServiceId_TerminateTask               ((OSServiceIdType) 0xe1)
#define OSServiceId_ChainTask                   ((OSServiceIdType) 0xe2)
#define OSServiceId_Schedule                    ((OSServiceIdType) 0xe3)
#define OSServiceId_GetTaskID                   ((OSServiceIdType) 0xe4)
#define OSServiceId_GetTaskState                ((OSServiceIdType) 0xe5)

#define OSServiceId_DisableAllInterrupts        ((OSServiceIdType) 0xe6)
#define OSServiceId_EnableAllInterrupts         ((OSServiceIdType) 0xe7)
#define OSServiceId_SuspendAllInterrupts        ((OSServiceIdType) 0xe8)
#define OSServiceId_ResumeAllInterrupts         ((OSServiceIdType) 0xe9)
#define OSServiceId_SuspendOSInterrupts         ((OSServiceIdType) 0xea)
#define OSServiceId_ResumeOSInterrupts          ((OSServiceIdType) 0xeb)

#define OSServiceId_DisableInterruptSource      ((OSServiceIdType) 0x30)
#define OSServiceId_EnableInterruptSource       ((OSServiceIdType) 0x31)
#define OSServiceId_ClearPendingInterrupt       ((OSServiceIdType) 0x32)

#define OSServiceId_GetResource                 ((OSServiceIdType) 0xec)
#define OSServiceId_ReleaseResource             ((OSServiceIdType) 0xed)

#define OSServiceId_SetEvent                    ((OSServiceIdType) 0xee)
#define OSServiceId_ClearEvent                  ((OSServiceIdType) 0xef)
#define OSServiceId_GetEvent                    ((OSServiceIdType) 0xf0)
#define OSServiceId_WaitEvent                   ((OSServiceIdType) 0xf1)

#define OSServiceId_GetAlarmBase                ((OSServiceIdType) 0xf2)
#define OSServiceId_GetAlarm                    ((OSServiceIdType) 0xf3)
#define OSServiceId_SetRelAlarm                 ((OSServiceIdType) 0xf4)
#define OSServiceId_SetAbsAlarm                 ((OSServiceIdType) 0xf5)
#define OSServiceId_CancelAlarm                 ((OSServiceIdType) 0xf6)

#define OSServiceId_GetActiveApplicationMode    ((OSServiceIdType) 0xf7)
#define OSServiceId_StartOS                     ((OSServiceIdType) 0xf8)
#define OSServiceId_ShutdownOS                  ((OSServiceIdType) 0xf9)
#define OSServiceId_GetApplicationID            ((OSServiceIdType) 0x00)
#define OSServiceId_GetISRID                    ((OSServiceIdType) 0x01)

#define OSServiceId_CallTrustedFunction         ((OSServiceIdType) 0x02)
#define OSServiceId_CheckISRMemoryAccess        ((OSServiceIdType) 0x03)
#define OSServiceId_CheckTaskMemoryAccess       ((OSServiceIdType) 0x04)
#define OSServiceId_CheckObjectAccess           ((OSServiceIdType) 0x05)
#define OSServiceId_CheckObjectOwnership        ((OSServiceIdType) 0x06)

#define OSServiceId_StartScheduleTableRel       ((OSServiceIdType) 0x07)
#define OSServiceId_StartScheduleTableAbs       ((OSServiceIdType) 0x08)
#define OSServiceId_StopScheduleTable           ((OSServiceIdType) 0x09)
#define OSServiceId_NextScheduleTable           ((OSServiceIdType) 0x0a)
#define OSServiceId_StartScheduleTableSynchron  ((OSServiceIdType) 0x0b)
#define OSServiceId_SyncScheduleTable           ((OSServiceIdType) 0x0c)
#define OSServiceId_GetScheduleTableStatus      ((OSServiceIdType) 0x0e)
#define OSServiceId_SetScheduleTableAsync       ((OSServiceIdType) 0x0d)

#define OSServiceId_IncrementCounter            ((OSServiceIdType) 0x0f)
#define OSServiceId_GetCounterValue             ((OSServiceIdType) 0x10)
#define OSServiceId_GetElapsedValue             ((OSServiceIdType) 0x11)

#define OSServiceId_TerminateApplication        ((OSServiceIdType) 0x12)
#define OSServiceId_AllowAccess                 ((OSServiceIdType) 0x13)
#define OSServiceId_GetApplicationState         ((OSServiceIdType) 0x14)
#define OSServiceId_ControlIdle                 ((OSServiceIdType) 0x1d)
#define IOCServiceId_IOC_Send                   ((OSServiceIdType) 0x1e)
#define IOCServiceId_IOC_Write                  ((OSServiceIdType) 0x1f)
#define IOCServiceId_IOC_SendGroup              ((OSServiceIdType) 0x20)
#define IOCServiceId_IOC_WriteGroup             ((OSServiceIdType) 0x21)
#define IOCServiceId_IOC_Receive                ((OSServiceIdType) 0x22)
#define IOCServiceId_IOC_Read                   ((OSServiceIdType) 0x23)
#define IOCServiceId_IOC_ReceiveGroup           ((OSServiceIdType) 0x24)
#define IOCServiceId_IOC_ReadGroup              ((OSServiceIdType) 0x25)
#define IOCServiceId_IOC_EmptyQueue             ((OSServiceIdType) 0x26)
#define OSServiceId_GetCurrentApplicationID     ((OSServiceIdType) 0x27)

#define OSServiceId_GetNumberOfActivatedCores   ((OSServiceIdType) 0x15)
#define OSServiceId_GetCoreID                   ((OSServiceIdType) 0x16)
#define OSServiceId_StartCore                   ((OSServiceIdType) 0x17)
#define OSServiceId_StartNonAutosarCore         ((OSServiceIdType) 0x18)
#define OSServiceId_GetSpinlock                 ((OSServiceIdType) 0x19)
#define OSServiceId_ReleaseSpinlock             ((OSServiceIdType) 0x1a)
#define OSServiceId_TryToGetSpinlock            ((OSServiceIdType) 0x1b)
#define OSServiceId_ShutdownAllCores            ((OSServiceIdType) 0x1c)

#define OSServiceId_IllegalExitTask             ((OSServiceIdType) 0x80)
#define OSServiceId_ExitC2ISR                   ((OSServiceIdType) 0x81)
#define OSServiceId_RaiseInterCoreInterrupt     ((OSServiceIdType) 0x82)

#define OSServiceId_CallFastTrustedFunction     ((OSServiceIdType) 0x86)

#define OSServiceId_ActivateTaskAsyn            ((OSServiceIdType) 0x33)
#define OSServiceId_SetEventAsyn                ((OSServiceIdType) 0x34)

#define OSServiceId_ReadPeripheral8             ((OSServiceIdType) 0x28)
#define OSServiceId_ReadPeripheral16            ((OSServiceIdType) 0x29)
#define OSServiceId_ReadPeripheral32            ((OSServiceIdType) 0x2a)
#define OSServiceId_WritePeripheral8            ((OSServiceIdType) 0x2b)
#define OSServiceId_WritePeripheral16           ((OSServiceIdType) 0x2c)
#define OSServiceId_WritePeripheral32           ((OSServiceIdType) 0x2d)
#define OSServiceId_ModifyPeripheral8           ((OSServiceIdType) 0x2e)
#define OSServiceId_ModifyPeripheral16          ((OSServiceIdType) 0x35)
#define OSServiceId_ModifyPeripheral32          ((OSServiceIdType) 0x2f)


#define AP_NoAccess     (0x0U)
#define AP_Executable   (0x1U)
#define AP_Readable     (0x2U)
#define AP_Writable     (0x4U)
#define AP_StackSpace   (0x8U)

#define OSMEMORY_IS_READABLE(AccessType)    ((AccessType) & AP_Readable)
#define OSMEMORY_IS_WRITEABLE(AccessType)   ((AccessType) & AP_Writable)
#define OSMEMORY_IS_EXECUTABLE(AccessType)  ((AccessType) & AP_Executable)
#define OSMEMORY_IS_STACKSPACE(AccessType)  ((AccessType) & AP_StackSpace)

#define NO_RESTART                  (0x00U)
#define RESTART                     (0x01U)

#define PRO_IGNORE                  (0x00U)
#define PRO_SHUTDOWN                (0x01U)
#define PRO_TERMINATETASKISR        (0x02U)
#define PRO_TERMINATEAPPL           (0x03U)
#define PRO_TERMINATEAPPL_RESTART   (0x04U)

#define OBJECT_TASK                 (0x01U)
#define OBJECT_ISR                  (0x02U)
#define OBJECT_ALARM                (0x03U)
#define OBJECT_RESOURCE             (0x04U)
#define OBJECT_COUNTER              (0x05U)
#define OBJECT_SPINLOCK             (0x07U)

#endif /* OS_INTERNAL1_H */
