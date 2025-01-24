/*
    Copyright (C) 2011 By eSOL Co.,Ltd. Tokyo, Japan

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
[mcos_ar_ds.h] - eMCOS AUTOSAR Debug Support API interface header
****************************************************************************/
#ifndef MCOS_AR_DS_H
#define MCOS_AR_DS_H

#include "mcos/mcos_ds.cfg"
#include "mcos/mcos_ds.h"

/* OBJECT alarm */
#define MCOS_TRACE_FUNCNO_GETALARMBASE                  ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_ALARM << 8) | 0x00)          /* GetAlarmBase()                */
#define MCOS_TRACE_FUNCNO_GETALARM                      ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_ALARM << 8) | 0x01)          /* GetAlarm()                    */
#define MCOS_TRACE_FUNCNO_SETRELALARM                   ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_ALARM << 8) | 0x02)          /* SetRelAlarm()                 */
#define MCOS_TRACE_FUNCNO_SETABSALARM                   ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_ALARM << 8) | 0x03)          /* SetAbsAlarm()                 */
#define MCOS_TRACE_FUNCNO_CANCELALARM                   ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_ALARM << 8) | 0x04)          /* CancelAlarm()                 */

/* OBJECT OSapplication */
#define MCOS_TRACE_FUNCNO_GETAPPLICATIONID              ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_OSAPPLICATION << 8) | 0x00)  /* GetApplicationID()            */
#define MCOS_TRACE_FUNCNO_GETAPPLICATIONSTATE           ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_OSAPPLICATION << 8) | 0x01)  /* GetApplicationState()         */
#define MCOS_TRACE_FUNCNO_GETACTIVEAPPLICATIONMODE      ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_OSAPPLICATION << 8) | 0x02)  /* GetActiveApplicationMode()    */
#define MCOS_TRACE_FUNCNO_GETCURRENTAPPLICATIONID       ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_OSAPPLICATION << 8) | 0x04)  /* GetCurrentApplicationID()     */

/* OBJECT core */
#define MCOS_TRACE_FUNCNO_GETNUMBEROFACTIVATEDCORES     ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_CORE << 8) | 0x00)           /* GetNumberOfActivatedCores()   */
#define MCOS_TRACE_FUNCNO_STARTCORE                     ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_CORE << 8) | 0x01)           /* StartCore()                   */
#define MCOS_TRACE_FUNCNO_STARTNONAUTOSARCORE           ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_CORE << 8) | 0x02)           /* StartNonAutosarCore()         */

/* OBJECT counter */
#define MCOS_TRACE_FUNCNO_INCREMENTCOUNTER              ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_COUNTER << 8) | 0x00)        /* IncrementCounter()             */
#define MCOS_TRACE_FUNCNO_GETCOUNTERVALUE               ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_COUNTER << 8) | 0x01)        /* GetCounterValue()              */
#define MCOS_TRACE_FUNCNO_GETELAPSEDVALUE               ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_COUNTER << 8) | 0x02)        /* GetElapsedValue()              */

/* OBJECT event */
#define MCOS_TRACE_FUNCNO_SETEVENT                      ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_EVENT << 8) | 0x00)          /* SetEvent()                     */
#define MCOS_TRACE_FUNCNO_CLEAREVENT                    ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_EVENT << 8) | 0x01)          /* ClearEvent()                   */
#define MCOS_TRACE_FUNCNO_GETEVENT                      ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_EVENT << 8) | 0x02)          /* GetEvent()                     */
#define MCOS_TRACE_FUNCNO_WAITEVENT                     ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_EVENT << 8) | 0x03)          /* WaitEvent()                    */
#define MCOS_TRACE_FUNCNO_SETEVENTASYN                  ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_EVENT << 8) | 0x04)          /* SetEventAsyn()                 */

/* OBJECT interrupt */
#define MCOS_TRACE_FUNCNO_ENABLEALLINTERRUPTS           ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_INTERRUPT << 8) | 0x00)      /* EnableAllInterrupts()          */
#define MCOS_TRACE_FUNCNO_DISABLEALLINTERRUPTS          ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_INTERRUPT << 8) | 0x01)      /* DisableAllInterrupts()         */
#define MCOS_TRACE_FUNCNO_RESUMEALLINTERRUPTS           ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_INTERRUPT << 8) | 0x02)      /* ResumeAllInterrupts()          */
#define MCOS_TRACE_FUNCNO_SUSPENDALLINTERRUPTS          ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_INTERRUPT << 8) | 0x03)      /* SuspendAllInterrupts()         */
#define MCOS_TRACE_FUNCNO_RESUMEOSINTERRUPTS            ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_INTERRUPT << 8) | 0x04)      /* ResumeOSInterrupts()           */
#define MCOS_TRACE_FUNCNO_SUSPENDOSINTERRUPTS           ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_INTERRUPT << 8) | 0x05)      /* SuspendOSInterrupts()          */
#define MCOS_TRACE_FUNCNO_DISABLEINTERRUPTSOURCE        ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_INTERRUPT << 8) | 0x06)      /* DisableInterruptSource()       */
#define MCOS_TRACE_FUNCNO_ENABLEINTERRUPTSOURCE         ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_INTERRUPT << 8) | 0x07)      /* EnableInterruptSource()        */
#define MCOS_TRACE_FUNCNO_GETISRID                      ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_INTERRUPT << 8) | 0x08)      /* GetISRID()                     */
#define MCOS_TRACE_FUNCNO_RAISEINTERCOREINTERRUPT       ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_INTERRUPT << 8) | 0x09)      /* RaiseInterCoreInterrupt()      */
#define MCOS_TRACE_FUNCNO_CLEARPENDINGINTERRUPT         ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_INTERRUPT << 8) | 0x0A)      /* ClearPendingInterrupt()        */


/* OBJECT ioc */
#define MCOS_TRACE_FUNCNO_AR_IOC_SEND                   ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_IOC << 8) | 0x00)            /* ar_ioc_send()                  */
#define MCOS_TRACE_FUNCNO_AR_IOC_WRITE                  ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_IOC << 8) | 0x01)            /* ar_ioc_write()                 */
#define MCOS_TRACE_FUNCNO_AR_IOC_RECEIVE                ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_IOC << 8) | 0x02)            /* ar_ioc_receive()               */
#define MCOS_TRACE_FUNCNO_AR_IOC_READ                   ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_IOC << 8) | 0x03)            /* ar_ioc_read()                  */
#define MCOS_TRACE_FUNCNO_AR_AR_IOC_EMPTY_QUEUE         ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_IOC << 8) | 0x04)            /* ar_ioc_empty_queue()           */

/* OBJECT objectaccess */
#define MCOS_TRACE_FUNCNO_CHECKTASKMEMORYACCESS         ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_OBJECTACCESS << 8) | 0x00)   /* CheckTaskMemoryAccess()        */
#define MCOS_TRACE_FUNCNO_CHECKISRMEMORYACCESS          ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_OBJECTACCESS << 8) | 0x01)   /* CheckISRMemoryAccess()         */
#define MCOS_TRACE_FUNCNO_CHECKOBJECTACCESS             ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_OBJECTACCESS << 8) | 0x02)   /* CheckObjectAccess()            */
#define MCOS_TRACE_FUNCNO_CHECKOBJECTOWNERSHIP          ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_OBJECTACCESS << 8) | 0x03)   /* CheckObjectOwnership()         */

/* OBJECT os */
#define MCOS_TRACE_FUNCNO_STARTOS                       ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_OS << 8) | 0x00)             /* StartOS()                      */
#define MCOS_TRACE_FUNCNO_CONTROLIDLE                   ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_OS << 8) | 0x01)             /* ControlIdle()                  */
#define MCOS_TRACE_FUNCNO_SHUTDOWNOS                    ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_OS << 8) | 0x02)             /* ShutdownOS()                   */
#define MCOS_TRACE_FUNCNO_SHUTDOWNALLCORES              ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_OS << 8) | 0x03)             /* ShutdownAllCores()             */

/* OBJECT resource */
#define MCOS_TRACE_FUNCNO_GETRESOURCE                   ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_RESOURCE << 8) | 0x00)       /* GetResource()                  */
#define MCOS_TRACE_FUNCNO_RELEASERESOURCE               ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_RESOURCE << 8) | 0x01)       /* ReleaseResource()              */

/* OBJECT spinlock */
#define MCOS_TRACE_FUNCNO_GETSPINLOCK                   ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_SPINLOCK << 8) | 0x00)       /* GetSpinlock()                  */
#define MCOS_TRACE_FUNCNO_GETSPINLOCKSKIPERRORCHK       ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_SPINLOCK << 8) | 0x01)       /* GetSpinlockSkipErrorChk()      */
#define MCOS_TRACE_FUNCNO_RELEASESPINLOCK               ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_SPINLOCK << 8) | 0x02)       /* ReleaseSpinlock()              */
#define MCOS_TRACE_FUNCNO_RELEASESPINLOCKSKIPERRORCHK   ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_SPINLOCK << 8) | 0x03)       /* ReleaseSpinlockSkipErrorChk()  */
#define MCOS_TRACE_FUNCNO_TRYTOGETSPINLOCK              ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_SPINLOCK << 8) | 0x04)       /* TryToGetSpinlock()             */
#define MCOS_TRACE_FUNCNO_TRYTOGETSPINLOCKSKIPERRORCHK  ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_SPINLOCK << 8) | 0x05)       /* TryToGetSpinlockSkipErrorChk() */

/* OBJECT task */
#define MCOS_TRACE_FUNCNO_ACTIVATETASK                  ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_TASK << 8) | 0x00)           /* ActivateTask()                  */
#define MCOS_TRACE_FUNCNO_TERMINATETASK                 ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_TASK << 8) | 0x01)           /* TerminateTask()                 */
#define MCOS_TRACE_FUNCNO_CHAINTASK                     ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_TASK << 8) | 0x02)           /* ChainTask()                     */
#define MCOS_TRACE_FUNCNO_SCHEDULE                      ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_TASK << 8) | 0x03)           /* Schedule()                      */
#define MCOS_TRACE_FUNCNO_GETTASKID                     ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_TASK << 8) | 0x04)           /* GetTaskID()                     */
#define MCOS_TRACE_FUNCNO_GETTASKSTATE                  ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_TASK << 8) | 0x05)           /* GetTaskState()                  */
#define MCOS_TRACE_FUNCNO_AR_ILLEGAL_EXIT_TASK          ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_TASK << 8) | 0x06)           /* ar_illegal_exit_task()          */
#define MCOS_TRACE_FUNCNO_ACTIVATETASKASYN              ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_TASK << 8) | 0x07)           /* ActivateTaskAsyn()              */

/* OBJECT TrustedFunction */
#define MCOS_TRACE_FUNCNO_CALLTRUSTEDFUNCTION           ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_TRUSTEDFUNCTION << 8) | 0x00) /* CallTrustedFunction()          */
#define MCOS_TRACE_FUNCNO_CALLFASTTRUSTEDFUNCTION       ((uint16_t)(MCOS_TRACE_OBJID_AUTOSAR_TRUSTEDFUNCTION << 8) | 0x01) /* CallFastTrustedFunction()      */

#endif /* #ifndef MCOS_AR_DS_H */
