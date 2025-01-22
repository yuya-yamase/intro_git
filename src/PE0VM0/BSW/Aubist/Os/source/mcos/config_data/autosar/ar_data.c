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
[ar_data.c] - eMCOS AUTOSAR data
****************************************************************************/

#include "Os.h"
#include "mcos/mcos.cfg"
#include "mcos/mcos_ds.cfg"
#include "mcos/mcos_autosar.cfg"
#include "ar_data_local.h"
#include "ar_user_cfg_def.h"
#include "ar_ioc_local.h"
#include "ar_mkmsg.h"

#define AR_NUM_MKMSG_BUFFERS    (2)

/****************************************************************************
 * Micro-Kernel message buffers (request/return)
 ****************************************************************************/

#if (AR_OS_USE_MULTICORE == STD_ON)
/***************************************
 * Core0
 ***************************************/
#define OS_START_SEC_VAR_LOCAL0_MKMSG_BUFFERS
#include "Os_MemMap.h"

static ar_api_request_t ar_mkmsg_request_buffer_core0[AR_NUM_MKMSG_BUFFERS];

#define OS_STOP_SEC_VAR_LOCAL0_MKMSG_BUFFERS
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_LOCAL0_MKMSG_BUFFERS
#include "Os_MemMap.h"

static ar_api_return_t  ar_mkmsg_return_buffer_core0[AR_NUM_MKMSG_BUFFERS];

#define OS_STOP_SEC_VAR_LOCAL0_MKMSG_BUFFERS
#include "Os_MemMap.h"

/***************************************
 * Core1
 ***************************************/
#define OS_START_SEC_VAR_LOCAL1_MKMSG_BUFFERS
#include "Os_MemMap.h"

static ar_api_request_t ar_mkmsg_request_buffer_core1[AR_NUM_MKMSG_BUFFERS];

#define OS_STOP_SEC_VAR_LOCAL1_MKMSG_BUFFERS
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_LOCAL1_MKMSG_BUFFERS
#include "Os_MemMap.h"

static ar_api_return_t  ar_mkmsg_return_buffer_core1[AR_NUM_MKMSG_BUFFERS];

#define OS_STOP_SEC_VAR_LOCAL1_MKMSG_BUFFERS
#include "Os_MemMap.h"

/***************************************
 * Core2
 ***************************************/
#if (MP_CONTROL_CORE_COUNT >= 3U)

#define OS_START_SEC_VAR_LOCAL2_MKMSG_BUFFERS
#include "Os_MemMap.h"

static ar_api_request_t ar_mkmsg_request_buffer_core2[AR_NUM_MKMSG_BUFFERS];

#define OS_STOP_SEC_VAR_LOCAL2_MKMSG_BUFFERS
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_LOCAL2_MKMSG_BUFFERS
#include "Os_MemMap.h"

static ar_api_return_t  ar_mkmsg_return_buffer_core2[AR_NUM_MKMSG_BUFFERS];

#define OS_STOP_SEC_VAR_LOCAL2_MKMSG_BUFFERS
#include "Os_MemMap.h"

#endif  /* #if (MP_CONTROL_CORE_COUNT >= 3U) */

/***************************************
 * Core3
 ***************************************/
#if (MP_CONTROL_CORE_COUNT >= 4U)

#define OS_START_SEC_VAR_LOCAL3_MKMSG_BUFFERS
#include "Os_MemMap.h"

static ar_api_request_t ar_mkmsg_request_buffer_core3[AR_NUM_MKMSG_BUFFERS];

#define OS_STOP_SEC_VAR_LOCAL3_MKMSG_BUFFERS
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_LOCAL3_MKMSG_BUFFERS
#include "Os_MemMap.h"

static ar_api_return_t  ar_mkmsg_return_buffer_core3[AR_NUM_MKMSG_BUFFERS];

#define OS_STOP_SEC_VAR_LOCAL3_MKMSG_BUFFERS
#include "Os_MemMap.h"

#endif  /* #if (MP_CONTROL_CORE_COUNT >= 4U) */


/***************************************
 * Shared
 ***************************************/
#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/* ar_mkmsg_request_buffer_table[] */
ar_api_request_t * const ar_mkmsg_request_buffer_table[MP_CONTROL_CORE_COUNT] =
{
    &ar_mkmsg_request_buffer_core0[0],
    &ar_mkmsg_request_buffer_core1[0],
#if (MP_CONTROL_CORE_COUNT >= 3U)
    &ar_mkmsg_request_buffer_core2[0],
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 3U) */
#if (MP_CONTROL_CORE_COUNT >= 4U)
    &ar_mkmsg_request_buffer_core3[0],
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 4U) */
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/* ar_mkmsg_return_buffer_table[] */
ar_api_return_t * const ar_mkmsg_return_buffer_table[MP_CONTROL_CORE_COUNT] =
{
    &ar_mkmsg_return_buffer_core0[0],
    &ar_mkmsg_return_buffer_core1[0],
#if (MP_CONTROL_CORE_COUNT >= 3U)
    &ar_mkmsg_return_buffer_core2[0],
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 3U) */
#if (MP_CONTROL_CORE_COUNT >= 4U)
    &ar_mkmsg_return_buffer_core3[0],
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 4U) */
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#endif /* #if (AR_OS_USE_MULTICORE == STD_ON) */


/****************************************************************************
 * AUTOSAR data
 ****************************************************************************/
#if (AR_OS_USE_MULTICORE == STD_ON)
#define OS_START_SEC_VAR_CLEARED_32
#include "Os_MemMap.h"
volatile uint32 ar_core_state_table[AR_OS_NUM_CORES + AR_OS_NUM_NON_AUTOSAR_CORES];
#define OS_STOP_SEC_VAR_CLEARED_32
#include "Os_MemMap.h"
#endif /* #if (AR_OS_USE_MULTICORE == STD_ON) */

#define OS_START_SEC_VAR_CLEARED_32
#include "Os_MemMap.h"
volatile uint32     ar_activated_slave_corecnt;
#define OS_STOP_SEC_VAR_CLEARED_32
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Os_MemMap.h"
AppModeType  ar_appmode_core_saved[AR_OS_NUM_CORES];
#define OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Os_MemMap.h"
AppModeType  ar_appmode_core[AR_OS_NUM_CORES];
#define OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_CLEARED_BOOLEAN
#include "Os_MemMap.h"
volatile boolean ar_is_autosar_core[AR_OS_NUM_CORES];
#define OS_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Os_MemMap.h"

#if (AR_OS_USE_MULTICORE == STD_ON)

#define OS_START_SEC_VAR_CLEARED_8
#include "Os_MemMap.h"
volatile uint8   ar_core_phases[AR_OS_NUM_CORES]; /* NOTE : zero cleared */
#define OS_STOP_SEC_VAR_CLEARED_8
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_CLEARED_8
#include "Os_MemMap.h"
volatile uint8   ar_master_phase; /* NOTE : zero cleared */
#define OS_STOP_SEC_VAR_CLEARED_8
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_CLEARED_BOOLEAN
#include "Os_MemMap.h"
volatile boolean    ar_is_shutdown_accepted;
#define OS_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"
const ar_api_request_t  ar_shutdown_msg =
{
    /* head */
    {
        AR_SHUTDOWN_ALL_CORES_REQID,            /* reqid */
        {
            0,                                  /* tid (dummy) */
            MCOS_LCID_SELF,                     /* lcid (dummy) */
        },
    },
    /* union.data */
    {
        0U,                                     /* default_data (dummy) */
    }
};
#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#endif /* #if (AR_OS_USE_MULTICORE == STD_ON) */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/* User Configurations */
const ar_user_config_t ar_user_config = {
    0UL
#if (AR_OS_USE_GETSERVICEID == STD_ON)
    | (1UL << USER_CFG_SHIFT_USE_GETSERVICEID)
#endif
#if (AR_OS_USE_PARAMETERACCESS == STD_ON)
    | (1UL << USER_CFG_SHIFT_USE_PARAMETERACCESS)
#endif
#if (AR_OS_USE_MULTICORE == STD_ON)
    | (1UL << USER_CFG_SHIFT_USE_MULTICORE)
#endif
#if (AR_OS_EXIST_TASK == STD_ON)
    | (1UL << USER_CFG_SHIFT_EXIST_TASK)
#endif
#if (AR_OS_EXIST_EXTEND_TASK == STD_ON)
    | (1UL << USER_CFG_SHIFT_EXIST_EXTEND_TASK)
#endif
#if (AR_OS_EXIST_COUNTER == STD_ON)
    | (1UL << USER_CFG_SHIFT_EXIST_COUNTER)
#endif
#if (AR_OS_EXIST_C1ISR == STD_ON)
    | (1UL << USER_CFG_SHIFT_EXIST_C1ISR)
#endif
#if (AR_OS_EXIST_C2ISR == STD_ON)
    | (1UL << USER_CFG_SHIFT_EXIST_C2ISR)
#endif
#if (AR_OS_EXIST_RESOURCE == STD_ON)
    | (1UL << USER_CFG_SHIFT_EXIST_RESOURCE)
#endif
#if (AR_OS_EXIST_ALARM == STD_ON)
    | (1UL << USER_CFG_SHIFT_EXIST_ALARM)
#endif
#if (AR_OS_EXIST_OSAP == STD_ON)
    | (1UL << USER_CFG_SHIFT_EXIST_OSAP)
#endif
#if (AR_OS_EXIST_SPINLOCK == STD_ON)
    | (1UL << USER_CFG_SHIFT_EXIST_SPINLOCK)
#endif
#if (AR_OS_EXIST_IOC == STD_ON)
    | (1UL << USER_CFG_SHIFT_EXIST_IOC)
#endif
#if (AR_OS_EXIST_QUEUED_IOC == STD_ON)
    | (1UL << USER_CFG_SHIFT_EXIST_QUEUED_IOC)
#endif
#if (AR_OS_EXIST_UNQUEUED_IOC == STD_ON)
    | (1UL << USER_CFG_SHIFT_EXIST_UNQUEUED_IOC)
#endif
#if (AR_OS_EXIST_QUEUED_IOC_PULLCB == STD_ON)
    | (1UL << USER_CFG_SHIFT_EXIST_PULLCB_QUEUED_IOC)
#endif
#if (AR_OS_EXIST_UNQUEUED_IOC_PULLCB == STD_ON)
    | (1UL << USER_CFG_SHIFT_EXIST_PULLCB_UNQUEUED_IOC)
#endif
#if (AR_OS_EXIST_TRUSTED_FUNCTION == STD_ON)
    | (1UL << USER_CFG_SHIFT_EXIST_TRUSTED_FUNCTION)
#endif
#if (AR_OS_USE_RES_SCHEDULER == STD_ON)
    | (1UL << USER_CFG_SHIFT_USE_RES_SCHEDULER)
#endif
#if (AR_OS_USE_SYSTEM_COUNTER == STD_ON)
    | (1UL << USER_CFG_SHIFT_USE_SYSTEM_COUNTER)
#endif
#if (AR_OS_EXIST_NON_AUTOSAR_CORES == STD_ON)
    | (1UL << USER_CFG_SHIFT_EXIST_NON_AUTOSAR_CORES)
#endif
#if (AR_OS_USE_SYSTEM_ERRORHOOK == STD_ON)
    | (1UL << USER_CFG_SHIFT_USE_SYSTEM_ERRORHOOK)
#endif
#if (AR_OS_USE_OSAP_ERRORHOOK == STD_ON)
    | (1UL << USER_CFG_SHIFT_USE_OSAP_ERRORHOOK)
#endif
#if (AR_OS_USE_POSTTASKHOOK == STD_ON)
    | (1UL << USER_CFG_SHIFT_USE_POSTTASKHOOK)
#endif
#if (AR_OS_USE_PRETASKHOOK == STD_ON)
    | (1UL << USER_CFG_SHIFT_USE_PRETASKHOOK)
#endif
#if (AR_OS_USE_PROTECTIONHOOK == STD_ON)
    | (1UL << USER_CFG_SHIFT_USE_PROTECTIONHOOK)
#endif
#if (AR_OS_USE_SYSTEM_STARTUPHOOK == STD_ON)
    | (1UL << USER_CFG_SHIFT_USE_SYSTEM_STARTUPHOOK)
#endif
#if (AR_OS_USE_OSAP_STARTUPHOOK == STD_ON)
    | (1UL << USER_CFG_SHIFT_USE_OSAP_STARTUPHOOK)
#endif
#if (AR_OS_USE_SYSTEM_SHUTDOWNHOOK == STD_ON)
    | (1UL << USER_CFG_SHIFT_USE_SYSTEM_SHUTDOWNHOOK)
#endif
#if (AR_OS_USE_OSAP_SHUTDOWNHOOK == STD_ON)
    | (1UL << USER_CFG_SHIFT_USE_OSAP_SHUTDOWNHOOK)
#endif
#if (AR_OS_EXIST_OSAP_STACK == STD_ON)
    | (1UL << USER_CFG_SHIFT_EXIST_OSAP_STACK)
#endif
    ,
    (uint32)MCOS_CFG_AR_HOOK_STACKSIZE,
    (uint32)MCOS_CFG_AR_SYSCALL_STACKSIZE,
    (uint8)MCOS_AR_CFG_USE_RAISEINTERCOREINTERRUPT,
    AR_OS_NUM_CORES,
    AR_OS_NUM_NON_AUTOSAR_CORES,
    OS_CORE_ID_MASTER,

#if (AR_OS_EXIST_TASK == STD_ON)
    AR_OS_NUM_TASKS,
#else
    0U,
#endif

#if (AR_OS_EXIST_EXTEND_TASK == STD_ON)
    AR_OS_NUM_EXTEND_TASKS,
#else
    0U,
#endif

#if (AR_OS_EXIST_RESOURCE == STD_ON)
    AR_OS_NUM_RESOURCES,
#else
    0U,
#endif

#if (AR_OS_EXIST_COUNTER == STD_ON)
    AR_OS_NUM_COUNTERS,
#else
    0U,
#endif

#if (AR_OS_EXIST_ALARM == STD_ON)
    AR_OS_NUM_ALARMS,
#else
    0U,
#endif

#if (AR_OS_EXIST_OSAP == STD_ON)
    (uint8_t)AR_OS_NUM_OSAPPLICATIONS,
#else
    0U,
#endif

    AR_OS_NUM_APPMODES,

#if ((AR_OS_EXIST_C1ISR == STD_ON) || (AR_OS_EXIST_C2ISR == STD_ON))
    AR_OS_NUM_ISRS,
#else
    0U,
#endif

#if (AR_OS_EXIST_C1ISR == STD_ON)
    AR_OS_NUM_C1ISRS,
#else
    0U,
#endif

#if (AR_OS_EXIST_C2ISR == STD_ON)
    AR_OS_NUM_C2ISRS,
#else
    0U,
#endif

#if (AR_OS_EXIST_IOC == STD_ON)
    AR_OS_NUM_IOC_COMMUNICATIONS,
    AR_OS_NUM_IOC_RECEIVERS,
    AR_OS_NUM_IOC_SENDERS,
#else
    0U,
    0U,
    0U,
#endif

#if (AR_OS_EXIST_UNQUEUED_IOC == STD_ON)
    AR_OS_NUM_UNQUEUED_IOCS,
#else
    0U,
#endif

#if (AR_OS_EXIST_QUEUED_IOC == STD_ON)
    AR_OS_NUM_QUEUED_IOCS,
#else
    0U,
#endif

#if (AR_OS_EXIST_SPINLOCK == STD_ON)
    AR_OS_NUM_SPINLOCKS,
    AR_OS_NUM_SPINLOCK_NESTCBS,
#else
    0U,
    0U,
#endif

    (TaskType)AR_OS_NUM_TASKS_PER_CORE_MAX,
    (uint8)AR_OS_ACT_COUNT_PER_CORE_MAX,
    AR_HIGHEST_C2ISR_PRIORITY,
    AR_OS_EXEC_PRIORITY,
    AR_LOWEST_C1ISR_PRIORITY,

#if (AR_OS_EXIST_TRUSTED_FUNCTION == STD_ON)
    AR_OS_NUM_TRUSTED_FUNCTIONS,
#else
    0U,
#endif

#if (AR_OS_EXIST_PERIPHERAL_AREA == STD_ON)
    AR_OS_NUM_PERIPHERAL_AREAS
#else
    0U
#endif
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/****************************************************************************
 * Check library
 ****************************************************************************/
#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"
const uint8 * const * const ar_libchk = &ar_libchk_data;
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"
