/*
    Copyright (C) 2018 eSOL Co.,Ltd. Tokyo, Japan

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
[ ar_user_cfg_def.h ] - MCOS AUTOSAR user configuration define header
****************************************************************************/

#ifndef AR_USER_CFG_DEF_H
#define AR_USER_CFG_DEF_H

#include "Os_internal.h"

/*
 * user configuration defines table
*/

typedef struct
{
    uint32              config_data;            /* EXIST,USE config */
    uint32              hook_stacksize;         /* mcos.cfg: MCOS_CFG_AR_HOOK_STACKSIZE */
    uint32              syscall_stacksize;      /* mcos.cfg: MCOS_CFG_AR_SYSCALL_STACKSIZE */
    uint8               use_raiseintercore;     /* mcos_autosar.cfg: MCOS_AR_CFG_USE_RAISEINTERCOREINTERRUPT */
    CoreIdType          num_cores;              /* AR_OS_NUM_CORES */
    CoreIdType          num_non_autosar_cores;  /* AR_OS_NUM_NON_AUTOSAR_CORES */
    CoreIdType          core_id_master;         /* OS_CORE_ID_MASTER */
    TaskType            num_tasks;              /* AR_OS_NUM_TASKS */
    TaskType            num_extend_tasks;       /* AR_OS_NUM_EXTEND_TASKS */
    ResourceType        num_resources;          /* AR_OS_NUM_RESOURCES */
    CounterType         num_counters;           /* AR_OS_NUM_COUNTERS */
    AlarmType           num_alarms;             /* AR_OS_NUM_ALARMS */
    ApplicationType     num_osapplications;     /* AR_OS_NUM_OSAPPLICATIONS */
    AppModeType         num_appmodes;           /* AR_OS_NUM_APPMODES */
    ISRType             num_isrs;               /* AR_OS_NUM_ISRS */
    ISRType             num_c1isrs;             /* AR_OS_NUM_C1ISRS */
    ISRType             num_c2isrs;             /* AR_OS_NUM_C2ISRS */
    IocType             num_ioc_communications; /* AR_OS_NUM_IOC_COMMUNICATIONS */
    IocType             num_ioc_receivers;      /* AR_OS_NUM_IOC_RECEIVERS */
    IocType             num_ioc_senders;        /* AR_OS_NUM_IOC_SENDERS */
    IocType             num_unqueued_iocs;      /* AR_OS_NUM_UNQUEUED_IOCS */
    IocType             num_queued_iocs;        /* AR_OS_NUM_QUEUED_IOCS */
    SpinlockIdType      num_spinlocks;          /* AR_OS_NUM_SPINLOCKS */
    SpinlockIdType      num_spinlock_nestcbs;   /* AR_OS_NUM_SPINLOCK_NESTCBS */
    TaskType            num_tasks_per_core_max; /* AR_OS_NUM_TASKS_PER_CORE_MAX */
    uint8               act_count_per_core_max; /* AR_OS_ACT_COUNT_PER_CORE_MAX */
    sint32              highest_c2isr_priority; /* AR_HIGHEST_C2ISR_PRIORITY */
    sint32              os_exec_priority;       /* AR_OS_EXEC_PRIORITY */
    sint32              lowest_c1isr_priority;  /* AR_LOWEST_C1ISR_PRIORITY */
    uint32              num_trusted_functions;  /* AR_OS_NUM_TRUSTED_FUNCTIONS */
    uint32              num_peripheralarea;     /* AR_OS_NUM_PERIHERAL_AREA */
} ar_user_config_t;

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern const ar_user_config_t ar_user_config;

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/* EXIST,USE config bit define */
#define USER_CFG_SHIFT_USE_GETSERVICEID           0U
#define USER_CFG_SHIFT_USE_PARAMETERACCESS        1U
#define USER_CFG_SHIFT_USE_MULTICORE              2U
#define USER_CFG_SHIFT_EXIST_TASK                 3U
#define USER_CFG_SHIFT_EXIST_EXTEND_TASK          4U
#define USER_CFG_SHIFT_EXIST_COUNTER              5U
#define USER_CFG_SHIFT_EXIST_C1ISR                6U
#define USER_CFG_SHIFT_EXIST_C2ISR                7U
#define USER_CFG_SHIFT_EXIST_RESOURCE             8U
#define USER_CFG_SHIFT_EXIST_ALARM                9U
#define USER_CFG_SHIFT_EXIST_OSAP                 10U
#define USER_CFG_SHIFT_EXIST_SPINLOCK             11U
#define USER_CFG_SHIFT_EXIST_IOC                  12U
#define USER_CFG_SHIFT_EXIST_QUEUED_IOC           13U
#define USER_CFG_SHIFT_EXIST_UNQUEUED_IOC         14U
#define USER_CFG_SHIFT_EXIST_PULLCB_QUEUED_IOC    15U
#define USER_CFG_SHIFT_EXIST_PULLCB_UNQUEUED_IOC  16U
#define USER_CFG_SHIFT_EXIST_TRUSTED_FUNCTION     17U
#define USER_CFG_SHIFT_USE_RES_SCHEDULER          18U
#define USER_CFG_SHIFT_USE_SYSTEM_COUNTER         19U
#define USER_CFG_SHIFT_EXIST_NON_AUTOSAR_CORES    20U
#define USER_CFG_SHIFT_USE_SYSTEM_ERRORHOOK       21U
#define USER_CFG_SHIFT_USE_OSAP_ERRORHOOK         22U
#define USER_CFG_SHIFT_USE_POSTTASKHOOK           23U
#define USER_CFG_SHIFT_USE_PRETASKHOOK            24U
#define USER_CFG_SHIFT_USE_PROTECTIONHOOK         25U
#define USER_CFG_SHIFT_USE_SYSTEM_STARTUPHOOK     26U
#define USER_CFG_SHIFT_USE_OSAP_STARTUPHOOK       27U
#define USER_CFG_SHIFT_USE_SYSTEM_SHUTDOWNHOOK    28U
#define USER_CFG_SHIFT_USE_OSAP_SHUTDOWNHOOK      29U
#define USER_CFG_SHIFT_EXIST_OSAP_STACK           30U


/* config check macro */
#define USER_CFG_STD_ON_USE_GETSERVICEID()    \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_USE_GETSERVICEID))
#define USER_CFG_STD_ON_USE_PARAMETERACCESS() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_USE_PARAMETERACCESS))
#define USER_CFG_STD_ON_USE_MULTICORE() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_USE_MULTICORE))
#define USER_CFG_STD_ON_EXIST_TASK() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_EXIST_TASK))
#define USER_CFG_STD_ON_EXIST_EXTEND_TASK() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_EXIST_EXTEND_TASK))
#define USER_CFG_STD_ON_EXIST_COUNTER() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_EXIST_COUNTER))
#define USER_CFG_STD_ON_EXIST_C1ISR() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_EXIST_C1ISR))
#define USER_CFG_STD_ON_EXIST_C2ISR() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_EXIST_C2ISR))
#define USER_CFG_STD_ON_EXIST_RESOURCE() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_EXIST_RESOURCE))
#define USER_CFG_STD_ON_EXIST_ALARM() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_EXIST_ALARM))
#define USER_CFG_STD_ON_EXIST_OSAP() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_EXIST_OSAP))
#define USER_CFG_STD_ON_EXIST_SPINLOCK() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_EXIST_SPINLOCK))
#define USER_CFG_STD_ON_EXIST_IOC() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_EXIST_IOC))
#define USER_CFG_STD_ON_EXIST_QUEUED_IOC() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_EXIST_QUEUED_IOC))
#define USER_CFG_STD_ON_EXIST_UNQUEUED_IOC() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_EXIST_UNQUEUED_IOC))
#define USER_CFG_STD_ON_EXIST_PULLCB_QUEUED_IOC() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_EXIST_PULLCB_QUEUED_IOC))
#define USER_CFG_STD_ON_EXIST_PULLCB_UNQUEUED_IOC() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_EXIST_PULLCB_UNQUEUED_IOC))
#define USER_CFG_STD_ON_EXIST_TRUSTED_FUNCTION() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_EXIST_TRUSTED_FUNCTION))
#define USER_CFG_STD_ON_USE_RES_SCHEDULER() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_USE_RES_SCHEDULER))
#define USER_CFG_STD_ON_USE_SYSTEM_COUNTER() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_USE_SYSTEM_COUNTER))
#define USER_CFG_STD_ON_EXIST_NON_AUTOSAR_CORES() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_EXIST_NON_AUTOSAR_CORES))
#define USER_CFG_STD_ON_USE_SYSTEM_ERRORHOOK() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_USE_SYSTEM_ERRORHOOK))
#define USER_CFG_STD_ON_USE_OSAP_ERRORHOOK() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_USE_OSAP_ERRORHOOK))
#define USER_CFG_STD_ON_USE_POSTTASKHOOK() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_USE_POSTTASKHOOK))
#define USER_CFG_STD_ON_USE_PRETASKHOOK() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_USE_PRETASKHOOK))
#define USER_CFG_STD_ON_USE_PROTECTIONHOOK() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_USE_PROTECTIONHOOK))
#define USER_CFG_STD_ON_USE_SYSTEM_STARTUPHOOK() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_USE_SYSTEM_STARTUPHOOK))
#define USER_CFG_STD_ON_USE_OSAP_STARTUPHOOK() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_USE_OSAP_STARTUPHOOK))
#define USER_CFG_STD_ON_USE_SYSTEM_SHUTDOWNHOOK() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_USE_SYSTEM_SHUTDOWNHOOK))
#define USER_CFG_STD_ON_USE_OSAP_SHUTDOWNHOOK() \
    (ar_user_config.config_data & ((uint32)1 << USER_CFG_SHIFT_USE_OSAP_SHUTDOWNHOOK))
#define USER_CFG_STD_ON_EXIST_OSAP_STACK() \
    (ar_user_config.config_data & ((uint32_t)1 << USER_CFG_SHIFT_EXIST_OSAP_STACK))

#define USER_CFG_MCOS_CFG_AR_HOOK_STACKSIZE()              (ar_user_config.hook_stacksize)
#define USER_CFG_MCOS_CFG_AR_SYSCALL_STACKSIZE()           (ar_user_config.syscall_stacksize)
#define USER_CFG_MCOS_AR_CFG_USE_RAISEINTERCOREINTERRUPT() (ar_user_config.use_raiseintercore)
#define USER_CFG_AR_OS_NUM_CORES()              (ar_user_config.num_cores)
#define USER_CFG_AR_OS_NUM_NON_AUTOSAR_CORES()  (ar_user_config.num_non_autosar_cores)
#define USER_CFG_AR_OS_CORE_ID_MASTER()         (ar_user_config.core_id_master)
#define USER_CFG_AR_OS_NUM_TASKS()              (ar_user_config.num_tasks)
#define USER_CFG_AR_OS_NUM_EXTEND_TASKS()       (ar_user_config.num_extend_tasks)
#define USER_CFG_AR_OS_NUM_RESOURCES()          (ar_user_config.num_resources)
#define USER_CFG_AR_OS_NUM_COUNTERS()           (ar_user_config.num_counters)
#define USER_CFG_AR_OS_NUM_ALARMS()             (ar_user_config.num_alarms)
#define USER_CFG_AR_OS_NUM_OSAPPLICATIONS()     (ar_user_config.num_osapplications)
#define USER_CFG_AR_OS_NUM_APPMODES()           (ar_user_config.num_appmodes)
#define USER_CFG_AR_OS_NUM_ISRS()               (ar_user_config.num_isrs)
#define USER_CFG_AR_OS_NUM_C1ISRS()             (ar_user_config.num_c1isrs)
#define USER_CFG_AR_OS_NUM_C2ISRS()             (ar_user_config.num_c2isrs)
#define USER_CFG_AR_OS_NUM_IOC_COMMUNICATIONS() (ar_user_config.num_ioc_communications)
#define USER_CFG_AR_OS_NUM_IOC_RECEIVERS()      (ar_user_config.num_ioc_receivers)
#define USER_CFG_AR_OS_NUM_IOC_SENDERS()        (ar_user_config.num_ioc_senders)
#define USER_CFG_AR_OS_NUM_UNQUEUED_IOCS()      (ar_user_config.num_unqueued_iocs)
#define USER_CFG_AR_OS_NUM_QUEUED_IOCS()        (ar_user_config.num_queued_iocs)
#define USER_CFG_AR_OS_NUM_SPINLOCKS()          (ar_user_config.num_spinlocks)
#define USER_CFG_AR_OS_NUM_SPINLOCK_NESTCBS()   (ar_user_config.num_spinlock_nestcbs)
#define USER_CFG_AR_OS_NUM_TASKS_PER_CORE_MAX() (ar_user_config.num_tasks_per_core_max)
#define USER_CFG_AR_OS_ACT_COUNT_PER_CORE_MAX() (ar_user_config.act_count_per_core_max)
#define USER_CFG_AR_HIGHEST_C2ISR_PRIORITY()    (ar_user_config.highest_c2isr_priority)
#define USER_CFG_AR_OS_EXEC_PRIORITY()          (ar_user_config.os_exec_priority)
#define USER_CFG_AR_LOWEST_C1ISR_PRIORITY()     (ar_user_config.lowest_c1isr_priority)
#define USER_CFG_AR_OS_NUM_TRUSTED_FUNCTIONS()  (ar_user_config.num_trusted_functions)
#define USER_CFG_AR_OS_NUM_PERIPHERALAREA()     (ar_user_config.num_peripheralarea)
#endif
