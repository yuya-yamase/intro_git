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
[Os_internal2_3.h] - Os module header
****************************************************************************/

#ifndef OS_INTERNAL2_3_H
#define OS_INTERNAL2_3_H

/*
 * OS Services by function call
 */
#define EnableAllInterrupts             AR_FNC(EnableAllInterrupts)
#define DisableAllInterrupts            AR_FNC(DisableAllInterrupts)
#define ResumeAllInterrupts             AR_FNC(ResumeAllInterrupts)
#define SuspendAllInterrupts            AR_FNC(SuspendAllInterrupts)
#define ResumeOSInterrupts              AR_FNC(ResumeOSInterrupts)
#define SuspendOSInterrupts             AR_FNC(SuspendOSInterrupts)
#define DisableInterruptSource          AR_FNC(DisableInterruptSource)
#define EnableInterruptSource           AR_FNC(EnableInterruptSource)
#define ClearPendingInterrupt           AR_FNC(ClearPendingInterrupt)
#define CheckTaskMemoryAccess           AR_FNC(CheckTaskMemoryAccess)
#define CheckISRMemoryAccess            AR_FNC(CheckISRMemoryAccess)
#define CheckObjectAccess               AR_FNC(CheckObjectAccess)
#define CheckObjectOwnership            AR_FNC(CheckObjectOwnership)
#define ControlIdle                     AR_FNC(ControlIdle)
#define GetApplicationState             AR_FNC(GetApplicationState)
#define GetActiveApplicationMode        AR_FNC(GetActiveApplicationMode)
#define ar_get_errhk_svcid              AR_FNC(ar_get_errhk_svcid)
#define ar_get_errhk_param              AR_FNC(ar_get_errhk_param)
#define ShutdownOS                      AR_FNC(ShutdownOS)
#define ShutdownAllCores                AR_FNC(ShutdownAllCores)
#define GetNumberOfActivatedCores       AR_FNC(GetNumberOfActivatedCores)
#define ActivateTask                    AR_FNC(ActivateTask)
#define ActivateTaskAsyn                AR_FNC(ActivateTaskAsyn)
#define TerminateTask                   AR_FNC(TerminateTask)
#define ChainTask                       AR_FNC(ChainTask)
#define Schedule                        AR_FNC(Schedule)
#define GetTaskState                    AR_FNC(GetTaskState)
#define SetEvent                        AR_FNC(SetEvent)
#define SetEventAsyn                    AR_FNC(SetEventAsyn)
#define ClearEvent                      AR_FNC(ClearEvent)
#define GetEvent                        AR_FNC(GetEvent)
#define WaitEvent                       AR_FNC(WaitEvent)
#define GetResource                     AR_FNC(GetResource)
#define ReleaseResource                 AR_FNC(ReleaseResource)
#define IncrementCounter                AR_FNC(IncrementCounter)
#define GetCounterValue                 AR_FNC(GetCounterValue)
#define GetElapsedValue                 AR_FNC(GetElapsedValue)
#define GetAlarmBase                    AR_FNC(GetAlarmBase)
#define GetAlarm                        AR_FNC(GetAlarm)
#define SetRelAlarm                     AR_FNC(SetRelAlarm)
#define SetAbsAlarm                     AR_FNC(SetAbsAlarm)
#define CancelAlarm                     AR_FNC(CancelAlarm)
#define CallTrustedFunction             AR_FNC(CallTrustedFunction)
#define CallFastTrustedFunction         AR_FNC(CallFastTrustedFunction)
#define ar_ioc_send                     AR_FNC(ar_ioc_send)
#define ar_ioc_write                    AR_FNC(ar_ioc_write)
#define ar_ioc_receive                  AR_FNC(ar_ioc_receive)
#define ar_ioc_read                     AR_FNC(ar_ioc_read)
#define ar_ioc_empty_queue              AR_FNC(ar_ioc_empty_queue)
#define GetSpinlock                     AR_FNC(GetSpinlock)
#define GetSpinlockSkipErrorChk         AR_FNC(GetSpinlockSkipErrorChk)
#define ReleaseSpinlock                 AR_FNC(ReleaseSpinlock)
#define ReleaseSpinlockSkipErrorChk     AR_FNC(ReleaseSpinlockSkipErrorChk)
#define TryToGetSpinlock                AR_FNC(TryToGetSpinlock)
#define TryToGetSpinlockSkipErrorChk    AR_FNC(TryToGetSpinlockSkipErrorChk)
#define RaiseInterCoreInterrupt         AR_FNC(RaiseInterCoreInterrupt)
#define ar_illegal_exit_task            AR_FNC(ar_illegal_exit_task)
#define ReadPeripheral8                 AR_FNC(ReadPeripheral8)
#define ReadPeripheral16                AR_FNC(ReadPeripheral16)
#define ReadPeripheral32                AR_FNC(ReadPeripheral32)
#define WritePeripheral8                AR_FNC(WritePeripheral8)
#define WritePeripheral16               AR_FNC(WritePeripheral16)
#define WritePeripheral32               AR_FNC(WritePeripheral32)
#define ModifyPeripheral8               AR_FNC(ModifyPeripheral8)
#define ModifyPeripheral16              AR_FNC(ModifyPeripheral16)
#define ModifyPeripheral32              AR_FNC(ModifyPeripheral32)

#endif /* OS_INTERNAL2_3_H */
