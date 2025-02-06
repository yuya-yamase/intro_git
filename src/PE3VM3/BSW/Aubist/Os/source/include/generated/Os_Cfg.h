/****************************************************************************
 * Protected                                                                *
 * Copyright AUBASS CO., LTD.                                               *
 ****************************************************************************

    Copyright (C) 2022 eSOL Co.,Ltd. Tokyo, Japan

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
 [ Os_Cfg.h ] - OS module's configuration header file
****************************************************************************/


#ifndef OS_CFG_H
#define OS_CFG_H

#include "Os_Cfg_base.h"

#define TotalNumberOfCores              (1U)

#define AR_OS_USE_OSAP_ERRORHOOK        (STD_OFF)
#define AR_OS_USE_OSAP_STARTUPHOOK      (STD_OFF)
#define AR_OS_USE_OSAP_SHUTDOWNHOOK     (STD_OFF)

#define AR_OS_USE_GETSERVICEID          (STD_OFF)
#define AR_OS_USE_PARAMETERACCESS       (STD_OFF)
#define AR_OS_USE_SYSTEM_COUNTER        (STD_OFF)

#define AR_OS_USE_START_OS                                              (STD_ON)
#define AR_OS_USE_ENABLE_ALL_INTERRUPTS                                 (STD_ON)
#define AR_OS_USE_DISABLE_ALL_INTERRUPTS                                (STD_ON)
#define AR_OS_USE_RESUME_ALL_INTERRUPTS                                 (STD_ON)
#define AR_OS_USE_SUSPEND_ALL_INTERRUPTS                                (STD_ON)
#define AR_OS_USE_RESUME_OSINTERRUPTS                                   (STD_ON)
#define AR_OS_USE_SUSPEND_OSINTERRUPTS                                  (STD_ON)
#define AR_OS_USE_DISABLE_INTERRUPT_SOURCE                              (STD_ON)
#define AR_OS_USE_ENABLE_INTERRUPT_SOURCE                               (STD_ON)
#define AR_OS_USE_CLEAR_PENDING_INTERRUPT                               (STD_ON)
#define AR_OS_USE_CHECK_TASK_MEMORY_ACCESS                              (STD_OFF)
#define AR_OS_USE_CHECK_ISR_MEMORY_ACCESS                               (STD_OFF)
#define AR_OS_USE_CHECK_OBJECT_ACCESS                                   (STD_OFF)
#define AR_OS_USE_CHECK_OBJECT_OWNERSHIP                                (STD_OFF)
#define AR_OS_USE_CONTROL_IDLE                                          (STD_ON)
#define AR_OS_USE_GET_APPLICATION_STATE                                 (STD_ON)
#define AR_OS_USE_GET_ACTIVE_APPLICATION_MODE                           (STD_ON)
#define AR_OS_USE_TERMINATE_APPLICATION                                 (STD_OFF)
#define AR_OS_USE_ALLOW_ACCESS                                          (STD_OFF)
#define AR_OS_USE_SHUTDOWN_OS                                           (STD_ON)
#define AR_OS_USE_SHUTDOWN_ALL_CORES                                    (STD_ON)
#define AR_OS_USE_GET_NUMBER_OF_ACTIVATED_CORES                         (STD_ON)
#define AR_OS_USE_START_CORE                                            (STD_ON)
#define AR_OS_USE_START_NON_AUTOSAR_CORE                                (STD_ON)
#define AR_OS_USE_ACTIVATE_TASK                                         (STD_ON)
#define AR_OS_USE_ACTIVATE_TASK_ASYN                                    (STD_ON)
#define AR_OS_USE_TERMINATE_TASK                                        (STD_ON)
#define AR_OS_USE_CHAIN_TASK                                            (STD_ON)
#define AR_OS_USE_SCHEDULE                                              (STD_ON)
#define AR_OS_USE_GET_TASK_STATE                                        (STD_ON)
#define AR_OS_USE_SET_EVENT                                             (STD_ON)
#define AR_OS_USE_SET_EVENT_ASYN                                        (STD_ON)
#define AR_OS_USE_CLEAR_EVENT                                           (STD_ON)
#define AR_OS_USE_GET_EVENT                                             (STD_ON)
#define AR_OS_USE_WAIT_EVENT                                            (STD_ON)
#define AR_OS_USE_GET_RESOURCE                                          (STD_ON)
#define AR_OS_USE_RELEASE_RESOURCE                                      (STD_ON)
#define AR_OS_USE_INCREMENT_COUNTER                                     (STD_ON)
#define AR_OS_USE_GET_COUNTER_VALUE                                     (STD_ON)
#define AR_OS_USE_GET_ELAPSED_VALUE                                     (STD_ON)
#define AR_OS_USE_GET_ALARM_BASE                                        (STD_ON)
#define AR_OS_USE_GET_ALARM                                             (STD_ON)
#define AR_OS_USE_SET_REL_ALARM                                         (STD_ON)
#define AR_OS_USE_SET_ABS_ALARM                                         (STD_ON)
#define AR_OS_USE_CANCEL_ALARM                                          (STD_ON)
#define AR_OS_USE_GET_SPINLOCK                                          (STD_ON)
#define AR_OS_USE_RELEASE_SPINLOCK                                      (STD_ON)
#define AR_OS_USE_TRY_TO_GET_SPINLOCK                                   (STD_ON)
#define AR_OS_USE_GET_SPINLOCK_SKIP_ERROR_CHK                           (STD_ON)
#define AR_OS_USE_RELEASE_SPINLOCK_SKIP_ERROR_CHK                       (STD_ON)
#define AR_OS_USE_TRY_TO_GET_SPINLOCK_SKIP_ERROR_CHK                    (STD_ON)
#define AR_OS_USE_CALL_FAST_TRUSTED_FUNCTION                            (STD_ON)
#define AR_OS_USE_READ_PERIPHERAL8                                      (STD_ON)
#define AR_OS_USE_READ_PERIPHERAL16                                     (STD_ON)
#define AR_OS_USE_READ_PERIPHERAL32                                     (STD_ON)
#define AR_OS_USE_WRITE_PERIPHERAL8                                     (STD_ON)
#define AR_OS_USE_WRITE_PERIPHERAL16                                    (STD_ON)
#define AR_OS_USE_WRITE_PERIPHERAL32                                    (STD_ON)
#define AR_OS_USE_MODIFY_PERIPHERAL8                                    (STD_ON)
#define AR_OS_USE_MODIFY_PERIPHERAL16                                   (STD_ON)
#define AR_OS_USE_MODIFY_PERIPHERAL32                                   (STD_ON)

#define AR_OS_EXIST_OSAP                (STD_OFF)
#define AR_OS_EXIST_OSAP_STACK          (STD_OFF)

#define AR_OS_NUM_CORES                 (1U)
#define AR_OS_NUM_NON_AUTOSAR_CORES     (0U)

#define AR_OS_EXIST_NON_AUTOSAR_CORES   (STD_OFF)
#define AR_OS_EXIST_TASK                (STD_ON)
#define AR_OS_EXIST_EXTEND_TASK         (STD_OFF)
#define AR_OS_EXIST_COUNTER             (STD_ON)
#define AR_OS_EXIST_C1ISR               (STD_OFF)
#define AR_OS_EXIST_C2ISR               (STD_ON)
#define AR_OS_EXIST_RESOURCE            (STD_OFF)
#define AR_OS_EXIST_ALARM               (STD_ON)

#define AR_OS_EXIST_SPINLOCK            (STD_OFF)
#define AR_OS_EXIST_IOC                 (STD_OFF)
#define AR_OS_EXIST_QUEUED_IOC          (STD_OFF)
#define AR_OS_EXIST_UNQUEUED_IOC        (STD_OFF)
#define AR_OS_EXIST_QUEUED_IOC_PULLCB   (STD_OFF)
#define AR_OS_EXIST_UNQUEUED_IOC_PULLCB (STD_OFF)
#define AR_OS_EXIST_TRUSTED_FUNCTION    (STD_OFF)
#define AR_OS_USE_RES_SCHEDULER         (STD_OFF)

#define AR_OS_EXIST_PERIPHERAL_AREA     (STD_OFF)

/* MASTER CORE */
#define OS_CORE_ID_MASTER               ((CoreIdType)0)
/* CORE ID(s)  */
#define OS_CORE_ID_0                    ((CoreIdType)0)


#define AR_OS_NUM_TASKS                                     ((uint16)0x0005U)
#define AR_OS_NUM_EXTEND_TASKS                              ((uint16)0x0000U)
#define AR_OS_NUM_RESOURCES                                 ((uint16)0x0000U)
#define AR_OS_NUM_STANDARD_RESOURCES                        ((uint16)0x0000U)
#define AR_OS_NUM_COUNTERS                                  ((uint16)0x0001U)
#define AR_OS_NUM_ALARMS                                    ((uint16)0x0003U)
#define AR_OS_NUM_OSAPPLICATIONS                            ((uint16)0x0000U)
#define AR_OS_NUM_APPMODES                                  ((uint16)0x0001U)
#define AR_OS_NUM_ISRS                                      ((uint16)0x0003U)
#define AR_OS_NUM_C1ISRS                                    ((uint16)0x0000U)
#define AR_OS_NUM_C2ISRS                                    ((uint16)0x0003U)
#define AR_OS_NUM_IOC_COMMUNICATIONS                        ((uint16)0x0000U)
#define AR_OS_NUM_IOC_RECEIVERS                             ((uint16)0x0000U)
#define AR_OS_NUM_IOC_SENDERS                               ((uint16)0x0000U)
#define AR_OS_NUM_UNQUEUED_IOCS                             ((uint16)0x0000U)
#define AR_OS_NUM_QUEUED_IOCS                               ((uint16)0x0000U)
#define AR_OS_NUM_SPINLOCKS                                 ((uint16)0x0000U)
#define AR_OS_NUM_SPINLOCK_NESTCBS                          ((uint16)0x0000U)
#define AR_OS_NUM_PERIPHERAL_AREAS                          ((uint16)0x0000U)

#define AR_OS_NUM_TASKS_PER_CORE_MAX                        (5)
#define AR_OS_ACT_COUNT_PER_CORE_MAX                        (8)

/*
 * Task ID
 */
/* Extend Tasks */
/* Basic Tasks */
#define Ecu_IdleTask                                        (AR_OS_NUM_EXTEND_TASKS + ((uint16)0x0000U))
#define Ecu_InitTask                                        (AR_OS_NUM_EXTEND_TASKS + ((uint16)0x0001U))
#define Task_MM_High                                        (AR_OS_NUM_EXTEND_TASKS + ((uint16)0x0002U))
#define Task_MM_Low                                         (AR_OS_NUM_EXTEND_TASKS + ((uint16)0x0003U))
#define Task_MM_Medium                                      (AR_OS_NUM_EXTEND_TASKS + ((uint16)0x0004U))



/*
 * Counter ID
 */
#define OS_SYSTEM_COUNTER0                                  ((uint16)0x0000U)

/*
 * Alarm ID
 */
#define ECU_u2HIGHTASK_ALM                                  ((uint16)0x0000U)
#define ECU_u2LOWTASK_ALM                                   ((uint16)0x0001U)
#define ECU_u2MEDIUMTASK_ALM                                ((uint16)0x0002U)


/*
 * OsAppMode ID
 */
#define OSDEFAULTAPPMODE                                    ((AppModeType)0x0000U)

/*
 * ISR ID
 */
/* Category 2 ISRs */
#define INTOSTM3_ISR                                        ((uint16)0x0000U)
#define INTP4_ISR                                           ((uint16)0x0001U)
#define OS_SYSTEM_COUNTER_ISR0                              ((uint16)0x0002U)



/* Highest Category 2 ISR Priority if any  */
#define AR_HIGHEST_C2ISR_PRIORITY (-5)

/* OS Execution Priority */
#define AR_OS_EXEC_PRIORITY       (-5)

/* Lowest Category 1 ISR Priority if any  */
#define AR_LOWEST_C1ISR_PRIORITY  (-6)



/*
 * Counter Constants and Macros
 */
#define OSMAXALLOWEDVALUE_OS_SYSTEM_COUNTER0       (1000000U)
#define OSTICKSPERBASE_OS_SYSTEM_COUNTER0          (1U)
#define OSMINCYCLE_OS_SYSTEM_COUNTER0              (1U)
#define OS_TICKS2NS_OS_SYSTEM_COUNTER0(tick)       ( (PhysicalTimeType)(0.001) * (PhysicalTimeType)(1000000000.0) * (PhysicalTimeType)(tick) )
#define OS_TICKS2US_OS_SYSTEM_COUNTER0(tick)       ( (PhysicalTimeType)(0.001) * (PhysicalTimeType)(1000000.0) * (PhysicalTimeType)(tick) )
#define OS_TICKS2MS_OS_SYSTEM_COUNTER0(tick)       ( (PhysicalTimeType)(0.001) * (PhysicalTimeType)(1000.0) * (PhysicalTimeType)(tick) )
#define OS_TICKS2SEC_OS_SYSTEM_COUNTER0(tick)      ( (PhysicalTimeType)(0.001) * (PhysicalTimeType)(tick) )
#endif /* OS_CFG_H */

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/
