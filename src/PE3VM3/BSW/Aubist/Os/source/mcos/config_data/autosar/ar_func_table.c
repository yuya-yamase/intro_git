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
[ar_func_table.c] - function call table
****************************************************************************/

#include "ar_func_table_local.h"

#include "ar_task.h"
#include "ar_resource.h"
#include "ar_interrupt.h"
#include "ar_ici.h"
#include "ar_counter.h"
#include "ar_alarm.h"
#include "ar_spinlock.h"
#include "ar_ioc.h"
#include "ar_osap.h"
#include "ar_call_func.h"
#include "ar_peripheral.h"


#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

const ar_func_table_t ar_func_table = {
    /*
     * FUNC_ar_interrupt_init              func_ar_interrupt_init;
     * FUNC_ar_CheckISROwnership           func_ar_CheckISROwnership;
     * FUNC_ar_cat2_get_iid                func_ar_cat2_get_iid;
     * FUNC_ar_get_isrcb                   func_ar_get_isrcb;
     * FUNC_ar_get_isr_config              func_ar_get_isr_config;
     * FUNC_ar_cat2_check_lcid             func_ar_cat2_check_lcid;  (only if AR_OS_USE_EXTENDEDSTATUS == STD_ON)
     */
#if (AR_OS_EXIST_C2ISR == STD_ON)
    &ar_interrupt_init,
#if (AR_OS_EXIST_OSAP == STD_ON) && (AR_ENABLE_CHECK_OBJECT_OWNERSHIP != 0U)
    &ar_CheckISROwnership,
#else /* #if (AR_OS_EXIST_OSAP == STD_ON) && (AR_ENABLE_CHECK_OBJECT_OWNERSHIP != 0U) */
    &ar_dummy_CheckObjectOwnership,
#endif /* #if (AR_OS_EXIST_OSAP == STD_ON) && (AR_ENABLE_CHECK_OBJECT_OWNERSHIP != 0U) */
    &ar_cat2_get_iid,
    &ar_get_isrcb,
    &ar_get_isr_config,
#if (AR_OS_USE_EXTENDEDSTATUS == STD_ON)
    &ar_dummy_ar_check_lcid,
#endif /* #if (AR_OS_USE_EXTENDEDSTATUS == STD_ON) */
#else /* #if (AR_OS_EXIST_C2ISR == STD_ON) */
    &ar_dummy_void_void,
    &ar_dummy_CheckObjectOwnership,
    &ar_dummy_ar_cat2_get_iid,
    &ar_dummy_get_isrcb,
    &ar_dummy_get_isr_config,
#if (AR_OS_USE_EXTENDEDSTATUS == STD_ON)
    &ar_dummy_ar_check_lcid,
#endif /* #if (AR_OS_USE_EXTENDEDSTATUS == STD_ON) */
#endif /* #if (AR_OS_EXIST_C2ISR == STD_ON) */

    /*
     * FUNC_ar_alarm_init                  func_ar_alarm_init;
     * FUNC_ar_get_alarm_base_impl         func_ar_get_alarm_base_impl;
     * FUNC_ar_get_alarm_impl              func_ar_get_alarm_impl;
     * FUNC_ar_set_rel_alarm_impl          func_ar_set_rel_alarm_impl;
     * FUNC_ar_set_abs_alarm_impl          func_ar_set_abs_alarm_impl;
     * FUNC_ar_cancel_alarm_impl           func_ar_cancel_alarm_impl;
     * FUNC_ar_CheckAlarmOwnership         func_ar_CheckAlarmOwnership;
     */
#if (AR_OS_EXIST_ALARM == STD_ON)
    &ar_alarm_init,
    &ar_get_alarm_base_impl,
    &ar_get_alarm_impl,
    &ar_set_rel_alarm_impl,
    &ar_set_abs_alarm_impl,
    &ar_cancel_alarm_impl,
#if (AR_OS_EXIST_OSAP == STD_ON) && (AR_ENABLE_CHECK_OBJECT_OWNERSHIP != 0U)
    &ar_CheckAlarmOwnership,
#else /* #if (AR_OS_EXIST_OSAP == STD_ON) && (AR_ENABLE_CHECK_OBJECT_OWNERSHIP != 0U) */
    &ar_dummy_CheckObjectOwnership,
#endif /* #if (AR_OS_EXIST_OSAP == STD_ON) && (AR_ENABLE_CHECK_OBJECT_OWNERSHIP != 0U) */
#else /* #if (AR_OS_EXIST_ALARM == STD_ON) */
    &ar_dummy_void_void,
    &ar_dummy_mkmsg_get_alarm_base_impl,
    &ar_dummy_mkmsg_get_alarm_impl,
    &ar_dummy_mkmsg_set_rel_alarm_impl,
    &ar_dummy_mkmsg_set_abs_alarm_impl,
    &ar_dummy_mkmsg_cancel_alarm_impl,
    &ar_dummy_CheckObjectOwnership,
#endif /* #if (AR_OS_EXIST_ALARM == STD_ON) */

    /*
     * FUNC_ar_cat1_interrupt_init         func_ar_cat1_interrupt_init;
     * FUNC_ar_cat1_get_iid                func_ar_cat1_get_iid;
     * FUNC_ar_get_cat1_int_config         func_ar_get_cat1_int_config;
     * FUNC_ar_cat1_check_lcid             func_ar_cat1_check_lcid;  (only when AR_OS_USE_EXTENDEDSTATUS == STD_ON)
     */
#if (AR_OS_EXIST_C1ISR == STD_ON)
    &ar_cat1_interrupt_init,
    &ar_dummy_ar_cat1_get_iid,
    &ar_get_cat1_int_config,
#if (AR_OS_USE_EXTENDEDSTATUS == STD_ON)
    &ar_dummy_ar_check_lcid,
#endif /* #if (AR_OS_USE_EXTENDEDSTATUS == STD_ON) */
#else /* #if (AR_OS_EXIST_C1ISR == STD_ON) */
    &ar_dummy_void_void,
    &ar_dummy_ar_cat1_get_iid,
    &ar_dummy_get_cat1_int_config,
#if (AR_OS_USE_EXTENDEDSTATUS == STD_ON)
    &ar_dummy_ar_check_lcid,
#endif /* #if (AR_OS_USE_EXTENDEDSTATUS == STD_ON) */
#endif /* #if (AR_OS_EXIST_C1ISR == STD_ON) */

    /*
     * FUNC_ar_counter_init                func_ar_counter_init;
     * FUNC_ar_get_counter_value_impl      func_ar_get_counter_value_impl;
     * FUNC_ar_get_elapsed_value_impl      func_ar_get_elapsed_value_impl;
     * FUNC_ar_CheckCounterOwnership       func_ar_CheckCounterOwnership;
     */
#if (AR_OS_EXIST_COUNTER == STD_ON)
    &ar_counter_init,
    &ar_get_counter_value_impl,
    &ar_get_elapsed_value_impl,
#if (AR_OS_EXIST_OSAP == STD_ON) && (AR_ENABLE_CHECK_OBJECT_OWNERSHIP != 0U)
    &ar_CheckCounterOwnership,
#else /* #if (AR_OS_EXIST_OSAP == STD_ON) && (AR_ENABLE_CHECK_OBJECT_OWNERSHIP != 0U) */
    &ar_dummy_CheckObjectOwnership,
#endif /* #if (AR_OS_EXIST_OSAP == STD_ON) && (AR_ENABLE_CHECK_OBJECT_OWNERSHIP != 0U) */
#else /* #if (AR_OS_EXIST_COUNTER == STD_ON) */
    &ar_dummy_void_void,
    &ar_dummy_mkmsg_get_counter_value_impl,
    &ar_dummy_mkmsg_get_elapsed_value_impl,
    &ar_dummy_CheckObjectOwnership,
#endif /* #if (AR_OS_EXIST_COUNTER == STD_ON) */

    /*
     * FUNC_ar_set_event_impl              func_ar_set_event_impl;
     * FUNC_ar_get_event_impl              func_ar_get_event_impl;
     */
#if (AR_OS_EXIST_EXTEND_TASK == STD_ON)
    &ar_set_event_impl,
    &ar_get_event_impl,
#else /* #if (AR_OS_EXIST_EXTEND_TASK == STD_ON) */
    &ar_dummy_mkmsg_set_event_impl,
    &ar_dummy_mkmsg_get_event_impl,
#endif /* #if (AR_OS_EXIST_EXTEND_TASK == STD_ON) */

    /*
     * FUNC_ar_ioc_init                 func_ar_ioc_init;
     * FUNC_ar_ioc_init_queued          func_ar_ioc_init_queued:
     * FUNC_ar_ioc_init_unqueued        func_ar_ioc_init_unqueued:
     * FUNC_ar_ioc_send_impl            func_ar_ioc_send_impl;
     * FUNC_ar_ioc_write_impl           func_ar_ioc_write_impl;
     * FUNC_ar_ioc_lock_get             func_ar_ioc_lock_get;
     * FUNC_ar_ioc_lock_release         func_ar_ioc_lock_release;
     */
#if (AR_OS_EXIST_IOC == STD_ON)
    &ar_ioc_init,
#if (AR_OS_EXIST_QUEUED_IOC == STD_ON)
    &ar_ioc_init_queued,
#else /* #if (AR_OS_EXIST_QUEUED_IOC == STD_ON) */
    &ar_dummy_ar_ioc_init_queued,
#endif /* #if (AR_OS_EXIST_QUEUED_IOC == STD_ON) */
#if (AR_OS_EXIST_UNQUEUED_IOC == STD_ON)
    &ar_ioc_init_unqueued,
#else /* #if (AR_OS_EXIST_UNQUEUED_IOC == STD_ON) */
    &ar_dummy_ar_ioc_init_unqueued,
#endif /* #if (AR_OS_EXIST_UNQUEUED_IOC == STD_ON) */
#if (AR_OS_EXIST_QUEUED_IOC == STD_ON)
    &ar_ioc_send_impl,
#else /* #if (AR_OS_EXIST_QUEUED_IOC == STD_ON) */
    &ar_dummy_mkmsg_ioc_send_impl,
#endif /* #if (AR_OS_EXIST_QUEUED_IOC == STD_ON) */
#if (AR_OS_EXIST_UNQUEUED_IOC == STD_ON)
    &ar_ioc_write_impl,
#else /* #if (AR_OS_EXIST_UNQUEUED_IOC == STD_ON) */
    &ar_dummy_mkmsg_ioc_write_impl,
#endif /* #if (AR_OS_EXIST_UNQUEUED_IOC == STD_ON) */
#if (AR_OS_USE_MULTICORE == STD_ON)
    &ar_ioc_lock_get,
    &ar_ioc_lock_release,
#else /* #if (AR_OS_USE_MULTICORE == STD_ON) */
    &ar_dummy_ar_ioc_lock,
    &ar_dummy_ar_ioc_lock,
#endif /* #if (AR_OS_USE_MULTICORE == STD_ON) */

#else /* #if (AR_OS_EXIST_IOC == STD_ON) */
    &ar_dummy_void_void,
    &ar_dummy_ar_ioc_init_queued,
    &ar_dummy_ar_ioc_init_unqueued,
    &ar_dummy_mkmsg_ioc_send_impl,
    &ar_dummy_mkmsg_ioc_write_impl,
    &ar_dummy_ar_ioc_lock,
    &ar_dummy_ar_ioc_lock,
#endif /* #if (AR_OS_EXIST_IOC == STD_ON) */

    /*
     * FUNC_ar_resource_init               func_ar_resource_init;
     * FUNC_ar_task_force_release_resources    func_ar_task_force_release_resources;
     * FUNC_ar_c2isr_force_release_resources   func_ar_c2isr_force_release_resources;
     */
#if (AR_OS_EXIST_RESOURCE == STD_ON)
    &ar_resource_init,
#if (AR_OS_EXIST_TASK == STD_ON)
    &ar_task_force_release_resources,
#else /* #if (AR_OS_EXIST_TASK == STD_ON) */
    &ar_dummy_ar_task_force_release_resources,
#endif /* #if (AR_OS_EXIST_TASK == STD_ON) */
#if (AR_OS_EXIST_C2ISR == STD_ON)
    &ar_c2isr_force_release_resources,
#else /* #if (AR_OS_EXIST_C2ISR == STD_ON) */
    &ar_dummy_ar_c2isr_force_release_resources,
#endif /* #if (AR_OS_EXIST_C2ISR == STD_ON) */
#else /* #if (AR_OS_EXIST_RESOURCE == STD_ON) */
    &ar_dummy_void_void,
    &ar_dummy_ar_task_force_release_resources,
    &ar_dummy_ar_c2isr_force_release_resources,
#endif /* #if (AR_OS_EXIST_RESOURCE == STD_ON) */

    /*
     * FUNC_ar_spinlock_init               func_ar_spinlock_init;
     * FUNC_ar_spinlock_force_release      func_ar_spinlock_force_release;
     * FUNC_ar_spinlock_cancel             func_ar_spinlock_cancel;
     */
#if (AR_OS_EXIST_SPINLOCK == STD_ON)
    &ar_spinlock_init,
    &ar_spinlock_force_release,
    &ar_dummy_ar_spinlock_cancel,
#else /* #if (AR_OS_EXIST_SPINLOCK == STD_ON) */
    &ar_dummy_void_void,
    &ar_dummy_ar_spinlock_force_release,
    &ar_dummy_ar_spinlock_cancel,
#endif /* #if (AR_OS_EXIST_SPINLOCK == STD_ON) */

    /*
     * FUNC_ar_task_init                   func_ar_task_init;
     * FUNC_ar_activate_task_impl          func_ar_activate_task_impl;
     * FUNC_ar_get_task_state_impl         func_ar_get_task_state_impl;
     * FUNC_ar_CheckTaskOwnership          func_ar_CheckTaskOwnership;
     */
#if (AR_OS_EXIST_TASK == STD_ON)
    &ar_task_init,
    &ar_activate_task_impl,
    &ar_get_task_state_impl,
#if (AR_OS_EXIST_OSAP == STD_ON) && (AR_ENABLE_CHECK_OBJECT_OWNERSHIP != 0U)
    &ar_CheckTaskOwnership,
#else /* #if (AR_OS_EXIST_OSAP == STD_ON) && (AR_ENABLE_CHECK_OBJECT_OWNERSHIP != 0U) */
    &ar_dummy_CheckObjectOwnership,
#endif /* #if (AR_OS_EXIST_OSAP == STD_ON) && (AR_ENABLE_CHECK_OBJECT_OWNERSHIP != 0U) */
#else /* #if (AR_OS_EXIST_TASK == STD_ON) */
    &ar_dummy_ar_task_init,
    &ar_dummy_mkmsg_activate_task_impl,
    &ar_dummy_mkmsg_get_task_state_impl,
    &ar_dummy_CheckObjectOwnership,
#endif /* #if (AR_OS_EXIST_TASK == STD_ON) */

    /*
     * FUNC_ar_multicore_init              func_ar_multicore_init;
     * FUNC_ar_multicore_init              func_ar_multicore_init;
     * FUNC_ar_ici_init                    func_ar_ici_init;
     * FUNC_ar_shutdown_allcores_impl      func_ar_shutdown_allcores_impl;
     * FUNC_mcos_main_slave                func_mcos_main_slave;
     * FUNC_ar_sync_cores                  func_ar_sync_cores;
     * FUNC_ar_interrupt_bind              func_ar_interrupt_bind;
     * FUNC_mcos_mkmsg_init                func_mcos_mkmsg_init;
     */
#if (AR_OS_USE_MULTICORE == STD_ON)
    &ar_set_mastercore_booted,
    &ar_multicore_init,
    &ar_ici_init,
    &ar_shutdown_allcores_impl,
    &mcos_main_slave,
    &ar_sync_cores,
#if (AR_OS_EXIST_C2ISR == STD_ON)
    &ar_interrupt_bind,
#else /* #if (AR_OS_EXIST_C2ISR == STD_ON) */
    &ar_dummy_void_void,
#endif /* #if (AR_OS_EXIST_C2ISR == STD_ON) */
    &mcos_mkmsg_init,
#else /* #if (AR_OS_USE_MULTICORE == STD_ON) */
    &ar_dummy_void_void,
    &ar_dummy_void_void,
    &ar_dummy_void_void,
    &ar_os_shutdown_internal,
    &ar_dummy_mcos_main_slave,
    &ar_dummy_ar_sync_cores,
    &ar_dummy_void_void,
    &ar_dummy_mcos_mkmsg_init,
#endif /* #if (AR_OS_USE_MULTICORE == STD_ON) */


    /*
     * FUNC_ar_system_call_errorhook       func_ar_system_call_errorhook;
     */
#if (AR_OS_USE_SYSTEM_ERRORHOOK == STD_ON)
    &ar_system_call_errorhook,
#else
    &ar_dummy_call_system_errorhook,
#endif

    /*
     * FUNC_ar_call_posttaskhook           func_ar_call_posttaskhook;
     */
#if (AR_OS_USE_POSTTASKHOOK == STD_ON)
    &ar_call_posttaskhook,
#else
    &ar_dummy_void_void,
#endif

    /*
     * FUNC_ar_call_pretaskhook            func_ar_call_pretaskhook;
     */
#if (AR_OS_USE_PRETASKHOOK == STD_ON)
    &ar_call_pretaskhook,
#else
    &ar_dummy_void_void,
#endif

    /*
     * FUNC_ar_call_protectionhook         func_ar_call_protectionhook;
     */
#if (AR_OS_USE_PROTECTIONHOOK == STD_ON)
    &ar_call_protectionhook,
#else
    &ar_dummy_ar_call_protectionhook,
#endif

    /*
     * FUNC_ar_system_call_startuphook     func_ar_system_call_startuphook;
     */
#if (AR_OS_USE_SYSTEM_STARTUPHOOK == STD_ON)
    &ar_system_call_startuphook,
#else
    &ar_dummy_ar_system_call_startuphook,
#endif

    /*
     * FUNC_ar_system_call_shutdownhook    func_ar_system_call_shutdownhook;
     */
#if (AR_OS_USE_SYSTEM_SHUTDOWNHOOK == STD_ON)
    &ar_system_call_shutdownhook,
#else
    &ar_dummy_ar_system_call_shutdownhook,
#endif

    /*
     * FUNC_ar_osap_call_errorhook         func_ar_osap_call_errorhook;
     */
#if (AR_OS_USE_OSAP_ERRORHOOK == STD_ON)
    &ar_osap_call_errorhook,
#else /* #if (AR_OS_USE_OSAP_ERRORHOOK == STD_ON) */
    &ar_dummy_ar_osap_call_errorhook,
#endif /* #if (AR_OS_USE_OSAP_ERRORHOOK == STD_ON) */

    /*
     * FUNC_ar_osap_call_shutdownhook      func_ar_osap_call_shutdownhook;
     */
#if (AR_OS_USE_OSAP_SHUTDOWNHOOK == STD_ON)
    &ar_osap_call_shutdownhook,
#else /* #if (AR_OS_USE_OSAP_SHUTDOWNHOOK == STD_ON) */
    &ar_dummy_ar_osap_call_shutdownhook,
#endif /* #if (AR_OS_USE_OSAP_SHUTDOWNHOOK == STD_ON) */

    /*
     * FUNC_ar_osap_call_startuphook       func_ar_osap_call_startuphook;
     */
#if (AR_OS_USE_OSAP_STARTUPHOOK == STD_ON)
    &ar_osap_call_startuphook,
#else /* #if (AR_OS_USE_OSAP_STARTUPHOOK == STD_ON) */
    &ar_dummy_ar_osap_call_startuphook,
#endif /* #if (AR_OS_USE_OSAP_STARTUPHOOK == STD_ON) */

    /*
     * FUNC_ar_system_counter_start        func_ar_system_counter_start;
     * FUNC_ar_system_counter_stop         func_ar_system_counter_stop;
     */
#if (AR_OS_USE_SYSTEM_COUNTER == STD_ON)
    &ar_system_counter_start,
    &ar_system_counter_stop,
#else /* #if (AR_OS_USE_SYSTEM_COUNTER == STD_ON) */
    &ar_dummy_void_void,
    &ar_dummy_void_void,
#endif /* #if (AR_OS_USE_SYSTEM_COUNTER == STD_ON) */

    /*
     * FUNC_ar_chk_isr_owner               func_ar_chk_isr_owner;
     */
#if (AR_OS_EXIST_OSAP == STD_ON)
    &ar_chk_isr_owner,
#else /* (AR_OS_EXIST_OSAP == STD_ON) */
    &ar_dummy_ar_chk_isr_owner,
#endif /* (AR_OS_EXIST_OSAP == STD_ON) */

    /*
     * FUNC_ar_peripheral_chk_address     func_ar_peripheral_chk_address;
     */
#if (AR_OS_EXIST_PERIPHERAL_AREA == STD_ON)
    &ar_peripheral_chk_address,
#else /* (AR_OS_EXIST_PERIPHERAL_AREA == STD_ON) */
    &ar_dummy_ar_peripheral_chk_address,
#endif /* (AR_OS_EXIST_PERIPHERAL_AREA == STD_ON) */


#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)

    /*
     * FUNC_ar_CheckAlarmAccess            func_ar_CheckAlarmAccess;
     */
#if (AR_OS_EXIST_ALARM == STD_ON) && (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U)
    &ar_CheckAlarmAccess,
#else /* #if (AR_OS_EXIST_ALARM == STD_ON) && (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U) */
    &ar_dummy_ar_CheckAlarmAccess,
#endif /* #if (AR_OS_EXIST_ALARM == STD_ON) &&  (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U) */

    /*
     * FUNC_ar_CheckISRAccess              func_ar_CheckISRAccess;
     * FUNC_ar_check_isr_memory            func_ar_check_isr_memory;
     */
#if (AR_OS_EXIST_C2ISR == STD_ON) && (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U)
    &ar_CheckISRAccess,
    &ar_check_isr_memory,
#else /* #if (AR_OS_EXIST_C2ISR == STD_ON) && (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U) */
    &ar_dummy_ar_CheckISRAccess,
    &ar_dummy_ar_check_isr_memory,
#endif /* #if (AR_OS_EXIST_C2ISR == STD_ON) && (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U) */

    /*
     * FUNC_ar_forcibly_terminate_counter  func_ar_forcibly_terminate_counter;
     * FUNC_ar_CheckCounterAccess          func_ar_CheckCounterAccess;
     */
#if (AR_OS_EXIST_COUNTER == STD_ON)
    &ar_dummy_ar_forcibly_terminate_counter,
#if (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U)
    &ar_CheckCounterAccess,
#else /* #if (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U) */
    &ar_dummy_ar_CheckCounterAccess,
#endif /* #if (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U) */
#else /* #if (AR_OS_EXIST_COUNTER == STD_ON) */
    &ar_dummy_ar_forcibly_terminate_counter,
    &ar_dummy_ar_CheckCounterAccess,
#endif /* #if (AR_OS_EXIST_COUNTER == STD_ON) */

    /*
     * FUNC_ar_CheckResourceAccess         func_ar_CheckResourceAccess;
     */
#if (AR_OS_EXIST_RESOURCE == STD_ON) && (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U)
    &ar_CheckResourceAccess,
#else /* #if (AR_OS_EXIST_RESOURCE == STD_ON) && (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U) */
    &ar_dummy_ar_CheckResourceAccess,
#endif /* #if (AR_OS_EXIST_RESOURCE == STD_ON) && (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U) */

    /*
     * FUNC_ar_CheckSpinlockAccess         func_ar_CheckSpinlockAccess;
     */
#if (AR_OS_EXIST_SPINLOCK == STD_ON) && (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U)
    &ar_CheckSpinlockAccess,
#else /* #if (AR_OS_EXIST_SPINLOCK == STD_ON) && (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U) */
    &ar_dummy_ar_CheckSpinlockAccess,
#endif /* #if (AR_OS_EXIST_SPINLOCK == STD_ON) && (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U) */

    /*
     * FUNC_ar_CheckTaskAccess             func_ar_CheckTaskAccess;
     */
#if (AR_OS_EXIST_TASK == STD_ON) && (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U)
    &ar_CheckTaskAccess,
#else /* #if (AR_OS_EXIST_TASK == STD_ON) && (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U) */
    &ar_dummy_ar_CheckTaskAccess,
#endif /* #if (AR_OS_EXIST_TASK == STD_ON) && (AR_ENABLE_CHECK_OBJECT_ACCESS != 0U) */

#endif /* #if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/*
 * System service table
 */
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

const ar_svc_table_t ar_svc_table = {
    /* [0x00] ar_svc_entity_enableallinterrupts */
#if (AR_OS_USE_ENABLE_ALL_INTERRUPTS == STD_ON)
    &(AR_SVC_ENTITY(EnableAllInterrupts)),
#else
    &ar_nspt_svc_EnableAllInterrupts,
#endif

    /* [0x01] ar_svc_entity_disableallinterrupts */
#if (AR_OS_USE_DISABLE_ALL_INTERRUPTS == STD_ON)
    &(AR_SVC_ENTITY(DisableAllInterrupts)),
#else
    &ar_nspt_svc_DisableAllInterrupts,
#endif

    /* [0x02] ar_svc_entity_resumeallinterrupts */
#if (AR_OS_USE_RESUME_ALL_INTERRUPTS == STD_ON)
    &(AR_SVC_ENTITY(ResumeAllInterrupts)),
#else
    &ar_nspt_svc_ResumeAllInterrupts,
#endif

    /* [0x03] ar_svc_entity_suspendallinterrupts */
#if (AR_OS_USE_SUSPEND_ALL_INTERRUPTS == STD_ON)
    &(AR_SVC_ENTITY(SuspendAllInterrupts)),
#else
    &ar_nspt_svc_SuspendAllInterrupts,
#endif

    /* [0x04] ar_svc_entity_resumeosinterrupts */
#if (AR_OS_USE_RESUME_OSINTERRUPTS == STD_ON)
    &(AR_SVC_ENTITY(ResumeOSInterrupts)),
#else
    &ar_nspt_svc_ResumeOSInterrupts,
#endif

    /* [0x05] ar_svc_entity_suspendosinterrupts */
#if (AR_OS_USE_SUSPEND_OSINTERRUPTS == STD_ON)
    &(AR_SVC_ENTITY(SuspendOSInterrupts)),
#else
    &ar_nspt_svc_SuspendOSInterrupts,
#endif

    /* [0x06] ar_svc_entity_disableinterruptsource */
    /* [0x07] ar_svc_entity_enableinterruptsource */
#if (AR_OS_EXIST_C2ISR == STD_ON)
#if (AR_OS_USE_DISABLE_INTERRUPT_SOURCE == STD_ON)
    &(AR_SVC_ENTITY(DisableInterruptSource)),
#else
    &ar_nspt_svc_DisableInterruptSource,
#endif
#if (AR_OS_USE_ENABLE_INTERRUPT_SOURCE == STD_ON)
    &(AR_SVC_ENTITY(EnableInterruptSource)),
#else
    &ar_nspt_svc_EnableInterruptSource,
#endif
#else /* #if (AR_OS_EXIST_C2ISR == STD_ON) */
    &ar_nspt_svc_DisableInterruptSource,
    &ar_nspt_svc_EnableInterruptSource,
#endif /* #if (AR_OS_EXIST_C2ISR == STD_ON) */

    /* [0x08] ar_svc_entity_checktaskmemoryaccess */
#if (AR_OS_USE_CHECK_TASK_MEMORY_ACCESS == STD_ON)
    &(AR_SVC_ENTITY(CheckTaskMemoryAccess)),
#else
    &ar_nspt_svc_CheckTaskMemoryAccess,
#endif

    /* [0x09] ar_svc_entity_checkisrmemoryaccess */
#if (AR_OS_USE_CHECK_ISR_MEMORY_ACCESS == STD_ON)
    &(AR_SVC_ENTITY(CheckISRMemoryAccess)),
#else
    &ar_nspt_svc_CheckISRMemoryAccess,
#endif

    /* [0x0A] ar_svc_entity_checkobjectaccess */
#if (AR_OS_USE_CHECK_OBJECT_ACCESS == STD_ON)
    &(AR_SVC_ENTITY(CheckObjectAccess)),
#else
    &ar_nspt_svc_CheckObjectAccess,
#endif

    /* [0x0B] ar_svc_entity_checkobjectownership */
#if (AR_OS_USE_CHECK_OBJECT_OWNERSHIP == STD_ON)
    &(AR_SVC_ENTITY(CheckObjectOwnership)),
#else
    &ar_nspt_svc_CheckObjectOwnership,
#endif

    /* [0x0C] ar_svc_entity_controlidle */
    &(AR_SVC_ENTITY(ControlIdle)),

    /* [0x0D] ar_svc_entity_getapplicationstate */
    &(AR_SVC_ENTITY(GetApplicationState)),

    /* [0x0E] ar_svc_entity_getactiveapplicationmode */
    &(AR_SVC_ENTITY(GetActiveApplicationMode)),

    /* [0x0F] ar_svc_entity_terminateapplication */
    &ar_nspt_svc_TerminateApplication,

    /* [0x10] ar_svc_entity_allowaccess */
    &ar_nspt_svc_AllowAccess,

    /* [0x11] ar_svc_entity_ar_get_errhk_svcid */
#if (AR_OS_USE_ERRORHOOK == STD_ON) && (AR_OS_USE_GETSERVICEID == STD_ON)
    &(AR_SVC_ENTITY(ar_get_errhk_svcid)),
#else /* (AR_OS_USE_ERRORHOOK == STD_ON) && (AR_OS_USE_GETSERVICEID == STD_ON) */
    &ar_nspt_svc_ar_get_errhk_svcid,
#endif /* (AR_OS_USE_ERRORHOOK == STD_ON) && (AR_OS_USE_GETSERVICEID == STD_ON) */

    /* [0x12] ar_svc_entity_ar_get_errhk_param */
#if (AR_OS_USE_ERRORHOOK == STD_ON) && (AR_OS_USE_PARAMETERACCESS == STD_ON)
    &(AR_SVC_ENTITY(ar_get_errhk_param)),
#else /* (AR_OS_USE_ERRORHOOK == STD_ON) && (AR_OS_USE_PARAMETERACCESS == STD_ON) */
    &ar_nspt_svc_ar_get_errhk_param,
#endif /* (AR_OS_USE_ERRORHOOK == STD_ON) && (AR_OS_USE_PARAMETERACCESS == STD_ON) */

    /* [0x13] ar_svc_entity_shutdownos */
#if (AR_OS_USE_MULTICORE != STD_ON)
    &(AR_SVC_ENTITY(ShutdownOS)),
#else /* !(AR_OS_USE_MULTICORE != STD_ON) */
    &ar_nspt_svc_ShutdownOS,
#endif /* !(AR_OS_USE_MULTICORE != STD_ON) */

    /* [0x14] ar_svc_entity_shutdownallcores */
    /* [0x15] ar_svc_entity_getnumberofactivatecores */
#if (AR_OS_USE_MULTICORE == STD_ON)
    &(AR_SVC_ENTITY(ShutdownAllCores)),
    &(AR_SVC_ENTITY(GetNumberOfActivatedCores)),
#else /* !(AR_OS_USE_MULTICORE == STD_ON) */
    &ar_nspt_svc_ShutdownAllCores,
    &ar_nspt_svc_GetNumberOfActivatedCores,
#endif /* !(AR_OS_USE_MULTICORE == STD_ON) */

    /* [0x16] ar_svc_entity_activatetask */
    /* [0x17] ar_svc_entity_terminatetask */
    /* [0x18] ar_svc_entity_chaintask */
    /* [0x19] ar_svc_entity_schedule */
    /* [0x1A] ar_svc_entity_gettaskstate */
    /* [0x1B] ar_svc_entity_ar_illegal_exit_task */
#if (AR_OS_EXIST_TASK == STD_ON)
    &(AR_SVC_ENTITY(ActivateTask)),
    &(AR_SVC_ENTITY(TerminateTask)),
#if (AR_OS_USE_CHAIN_TASK == STD_ON)
    &(AR_SVC_ENTITY(ChainTask)),
#else
    &ar_nspt_svc_ChainTask,
#endif
    &(AR_SVC_ENTITY(Schedule)),
    &(AR_SVC_ENTITY(GetTaskState)),
    &(AR_SVC_ENTITY(ar_illegal_exit_task)),
#else /* !(AR_OS_EXIST_TASK == STD_ON) */
    &ar_nspt_svc_ActivateTask,
    &ar_nspt_svc_TerminateTask,
    &ar_nspt_svc_ChainTask,
    &ar_nspt_svc_Schedule,
    &ar_nspt_svc_GetTaskState,
    &ar_nspt_svc_ar_illegal_exit_task,
#endif /* !(AR_OS_EXIST_TASK == STD_ON) */

    /* [0x1C] ar_svc_entity_setevent */
    /* [0x1D] ar_svc_entity_clearevent */
    /* [0x1E] ar_svc_entity_getevent */
    /* [0x1F] ar_svc_entity_waitevent */
#if (AR_OS_EXIST_EXTEND_TASK == STD_ON)
    &(AR_SVC_ENTITY(SetEvent)),
    &(AR_SVC_ENTITY(ClearEvent)),
    &(AR_SVC_ENTITY(GetEvent)),
    &(AR_SVC_ENTITY(WaitEvent)),
#else /* !(AR_OS_EXIST_EXTEND_TASK == STD_ON) */
    &ar_nspt_svc_SetEvent,
    &ar_nspt_svc_ClearEvent,
    &ar_nspt_svc_GetEvent,
    &ar_nspt_svc_WaitEvent,
#endif /* !(AR_OS_EXIST_EXTEND_TASK == STD_ON) */

    /* [0x20] ar_svc_entity_getresource */
    /* [0x21] ar_svc_entity_releaseresource */
#if (AR_OS_EXIST_RESOURCE == STD_ON)
    &(AR_SVC_ENTITY(GetResource)),
    &(AR_SVC_ENTITY(ReleaseResource)),
#else /* !(AR_OS_EXIST_RESOURCE == STD_ON) */
    &ar_nspt_svc_GetResource,
    &ar_nspt_svc_ReleaseResource,
#endif /* !(AR_OS_EXIST_RESOURCE == STD_ON) */

    /* [0x22] ar_svc_entity_incrementcounter */
    /* [0x23] ar_svc_entity_getcountervalue */
    /* [0x24] ar_svc_entity_getelapsedvalue */
#if (AR_OS_EXIST_COUNTER == STD_ON)
    &(AR_SVC_ENTITY(IncrementCounter)),
    &(AR_SVC_ENTITY(GetCounterValue)),
    &(AR_SVC_ENTITY(GetElapsedValue)),
#else /* !(AR_OS_EXIST_COUNTER == STD_ON) */
    &ar_nspt_svc_IncrementCounter,
    &ar_nspt_svc_GetCounterValue,
    &ar_nspt_svc_GetElapsedValue,
#endif /* !(AR_OS_EXIST_COUNTER == STD_ON) */

    /* [0x25] ar_svc_entity_getalarmbase */
    /* [0x26] ar_svc_entity_getalarm */
    /* [0x27] ar_svc_entity_setrelalarm */
    /* [0x28] ar_svc_entity_setabsalarm */
    /* [0x29] ar_svc_entity_cancelalarm */
#if (AR_OS_EXIST_ALARM == STD_ON)
    &(AR_SVC_ENTITY(GetAlarmBase)),
    &(AR_SVC_ENTITY(GetAlarm)),
    &(AR_SVC_ENTITY(SetRelAlarm)),
    &(AR_SVC_ENTITY(SetAbsAlarm)),
    &(AR_SVC_ENTITY(CancelAlarm)),
#else /* !(AR_OS_EXIST_ALARM == STD_ON) */
    &ar_nspt_svc_GetAlarmBase,
    &ar_nspt_svc_GetAlarm,
    &ar_nspt_svc_SetRelAlarm,
    &ar_nspt_svc_SetAbsAlarm,
    &ar_nspt_svc_CancelAlarm,
#endif /* !(AR_OS_EXIST_ALARM == STD_ON) */

    /* [0x2A] ar_svc_entity_calltrustedfunction */
#if (AR_OS_EXIST_TRUSTED_FUNCTION == STD_ON)
    &(AR_SVC_ENTITY(CallTrustedFunction)),
#else /* !(AR_OS_EXIST_TRUSTED_FUNCTION == STD_ON) */
    &ar_nspt_svc_CallTrustedFunction,
#endif /* !(AR_OS_EXIST_TRUSTED_FUNCTION == STD_ON) */

    /* [0x2B] ar_svc_entity_ar_ioc_send */
    /* [0x2C] ar_svc_entity_ar_ioc_write */
    /* [0x2D] ar_svc_entity_ar_ioc_recive */
    /* [0x2E] ar_svc_entity_ar_ioc_read */
    /* [0x2F] ar_svc_entity_ar_ioc_empty_queue */
#if (AR_OS_EXIST_IOC == STD_ON)
#if (AR_OS_EXIST_QUEUED_IOC == STD_ON)
    &(AR_SVC_ENTITY(ar_ioc_send)),
#else /* #if (AR_OS_EXIST_QUEUED_IOC == STD_ON) */
    &ar_nspt_svc_ar_ioc_send,
#endif /* #if (AR_OS_EXIST_QUEUED_IOC == STD_ON) */
#if (AR_OS_EXIST_UNQUEUED_IOC == STD_ON)
    &(AR_SVC_ENTITY(ar_ioc_write)),
#else /* #if (AR_OS_EXIST_UNQUEUED_IOC == STD_ON) */
    &ar_nspt_svc_ar_ioc_write,
#endif /* #if (AR_OS_EXIST_UNQUEUED_IOC == STD_ON) */
#if (AR_OS_EXIST_QUEUED_IOC == STD_ON)
    &(AR_SVC_ENTITY(ar_ioc_receive)),
#else /* #if (AR_OS_EXIST_QUEUED_IOC == STD_ON) */
    &ar_nspt_svc_ar_ioc_receive,
#endif /* #if (AR_OS_EXIST_QUEUED_IOC == STD_ON) */
#if (AR_OS_EXIST_UNQUEUED_IOC == STD_ON)
    &(AR_SVC_ENTITY(ar_ioc_read)),
#else /* #if (AR_OS_EXIST_UNQUEUED_IOC == STD_ON) */
    &ar_nspt_svc_ar_ioc_read,
#endif /* #if (AR_OS_EXIST_UNQUEUED_IOC == STD_ON) */
#if (AR_OS_EXIST_QUEUED_IOC == STD_ON)
    &(AR_SVC_ENTITY(ar_ioc_empty_queue)),
#else /* #if (AR_OS_EXIST_QUEUED_IOC == STD_ON) */
    &ar_nspt_svc_ar_ioc_empty_queue,
#endif /* #if (AR_OS_EXIST_QUEUED_IOC == STD_ON) */
#else /* !(AR_OS_EXIST_IOC == STD_ON) */
    &ar_nspt_svc_ar_ioc_send,
    &ar_nspt_svc_ar_ioc_write,
    &ar_nspt_svc_ar_ioc_receive,
    &ar_nspt_svc_ar_ioc_read,
    &ar_nspt_svc_ar_ioc_empty_queue,
#endif /* !(AR_OS_EXIST_IOC == STD_ON) */

    /* [0x30] ar_svc_entity_getspinlock */
    /* [0x31] ar_svc_entity_releasespinlock */
    /* [0x32] ar_svc_entity_trytogetspinlock */
#if (AR_OS_EXIST_SPINLOCK == STD_ON)
    &(AR_SVC_ENTITY(GetSpinlock)),
    &(AR_SVC_ENTITY(ReleaseSpinlock)),
    &(AR_SVC_ENTITY(TryToGetSpinlock)),
#else /* !(AR_OS_EXIST_SPINLOCK == STD_ON) */
    &ar_nspt_svc_GetSpinlock,
    &ar_nspt_svc_ReleaseSpinlock,
    &ar_nspt_svc_TryToGetSpinlock,
#endif /* !(AR_OS_EXIST_SPINLOCK == STD_ON) */

    /* [0x33] ar_svc_entity_raiseintercoreinterrupt */
#if (AR_OS_USE_MULTICORE == STD_ON)
    &(AR_SVC_ENTITY(RaiseInterCoreInterrupt)),
#else /* !(AR_OS_USE_MULTICORE == STD_ON) */
    &ar_nspt_svc_RaiseInterCoreInterrupt,
#endif /* !(AR_OS_USE_MULTICORE == STD_ON) */

    /* [0x34] ar_svc_entity_getspinlockskiperrorchk */
    /* [0x35] ar_svc_entity_releasespinlockskiperrorchk */
    /* [0x36] ar_svc_entity_trytogetspinlockskiperrorchk */
#if (AR_OS_EXIST_SPINLOCK == STD_ON)
    &(AR_SVC_ENTITY(GetSpinlockSkipErrorChk)),
    &(AR_SVC_ENTITY(ReleaseSpinlockSkipErrorChk)),
    &(AR_SVC_ENTITY(TryToGetSpinlockSkipErrorChk)),
#else /* !(AR_OS_EXIST_SPINLOCK == STD_ON) */
    &ar_nspt_svc_GetSpinlockSkipErrorChk,
    &ar_nspt_svc_ReleaseSpinlockSkipErrorChk,
    &ar_nspt_svc_TryToGetSpinlockSkipErrorChk,
#endif /* !(AR_OS_EXIST_SPINLOCK == STD_ON) */

    /* [0x37] ar_svc_entity_ar_errorhook_call */
#if (AR_OS_USE_ERRORHOOK == STD_ON)
    &(AR_SVC_ENTITY(ar_errorhook_call)),
#else /* !(AR_OS_USE_ERRORHOOK == STD_ON) */
    &ar_nspt_svc_ar_errorhook_call,
#endif /* !(AR_OS_USE_ERRORHOOK == STD_ON) */

    /* [0x38] ar_svc_entity_activatetask_asyn */
#if ((AR_OS_EXIST_TASK == STD_ON) && (AR_OS_USE_MULTICORE == STD_ON))
    &(AR_SVC_ENTITY(ActivateTaskAsyn)),
#else
    &ar_nspt_svc_ActivateTaskAsyn,
#endif

    /* [0x39] ar_svc_entity_setevent_asyn */
#if ((AR_OS_EXIST_EXTEND_TASK == STD_ON) && (AR_OS_USE_MULTICORE == STD_ON))
    &(AR_SVC_ENTITY(SetEventAsyn)),
#else
    &ar_nspt_svc_SetEventAsyn,
#endif

    /* [0x3A] ar_svc_clear_pending_interrupt */
#if ((AR_OS_EXIST_C2ISR == STD_ON) && (AR_OS_USE_CLEAR_PENDING_INTERRUPT == STD_ON))
    &(AR_SVC_ENTITY(ClearPendingInterrupt)),
#else /* ((AR_OS_EXIST_C2ISR == STD_ON) && (AR_OS_USE_CLEAR_PENDING_INTERRUPT == STD_ON)) */
    &ar_nspt_svc_ClearPendingInterrupt,
#endif /* ((AR_OS_EXIST_C2ISR == STD_ON) && (AR_OS_USE_CLEAR_PENDING_INTERRUPT == STD_ON)) */

    /* [0x3B] ar_svc_read_peripheral8 */
    /* [0x3C] ar_svc_read_peripheral16 */
    /* [0x3D] ar_svc_read_peripheral32 */
    /* [0x3E] ar_svc_write_peripheral8 */
    /* [0x3F] ar_svc_write_peripheral16 */
    /* [0x40] ar_svc_write_peripheral32 */
    /* [0x41] ar_svc_mpdify_peripheral8 */
    /* [0x42] ar_svc_mpdify_peripheral16 */
    /* [0x43] ar_svc_mpdify_peripheral32 */
    &(AR_SVC_ENTITY(ReadPeripheral8)),
    &(AR_SVC_ENTITY(ReadPeripheral16)),
    &(AR_SVC_ENTITY(ReadPeripheral32)),
    &(AR_SVC_ENTITY(WritePeripheral8)),
    &(AR_SVC_ENTITY(WritePeripheral16)),
    &(AR_SVC_ENTITY(WritePeripheral32)),
    &(AR_SVC_ENTITY(ModifyPeripheral8)),
    &(AR_SVC_ENTITY(ModifyPeripheral16)),
    &(AR_SVC_ENTITY(ModifyPeripheral32))
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

const AR_SVC_ENTITY_CallFastTrustedFunction ar_svc_call_fast_trusted_function =
#if (AR_OS_EXIST_TRUSTED_FUNCTION == STD_ON)
    &(AR_SVC_ENTITY(CallFastTrustedFunction));
#else /* !(AR_OS_EXIST_TRUSTED_FUNCTION == STD_ON) */
    &ar_nspt_svc_CallFastTrustedFunction;
#endif /* !(AR_OS_EXIST_TRUSTED_FUNCTION == STD_ON) */

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

