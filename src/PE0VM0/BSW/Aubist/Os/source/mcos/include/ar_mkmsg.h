/*
    Copyright (C) 2017 eSOL Co.,Ltd. Tokyo, Japan

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
[ ar_mkmsg.h ] - MCOS AUTOSAR mkmsg interface header
****************************************************************************/

#ifndef AR_MKMSG_H
#define AR_MKMSG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ar_api/Os_internal.h"

#include "mcos_basic.h"
#include "ar_mcos.h"

/*
 * Message ID
 */

/* Inter-Core request IDs for AUTOSAR */
#define AR_API_BASE_REQID                   ((msg_generic_id_t)0x0000)

#define AR_ACTIVATE_TASK_REQID              ((msg_generic_id_t)0x0000 + AR_API_BASE_REQID)
#define AR_GET_TASK_STATE_REQID             ((msg_generic_id_t)0x0001 + AR_API_BASE_REQID)
#define AR_SET_EVENT_REQID                  ((msg_generic_id_t)0x0002 + AR_API_BASE_REQID)
#define AR_GET_EVENT_REQID                  ((msg_generic_id_t)0x0003 + AR_API_BASE_REQID)
#define AR_GET_COUNTER_VALUE_REQID          ((msg_generic_id_t)0x0004 + AR_API_BASE_REQID)
#define AR_GET_ELAPSED_VALUE_REQID          ((msg_generic_id_t)0x0005 + AR_API_BASE_REQID)
#define AR_GET_ALARM_BASE_REQID             ((msg_generic_id_t)0x0006 + AR_API_BASE_REQID)
#define AR_GET_ALARM_REQID                  ((msg_generic_id_t)0x0007 + AR_API_BASE_REQID)
#define AR_SET_REL_ALARM_REQID              ((msg_generic_id_t)0x0008 + AR_API_BASE_REQID)
#define AR_SET_ABS_ALARM_REQID              ((msg_generic_id_t)0x0009 + AR_API_BASE_REQID)
#define AR_CANCEL_ALARM_REQID               ((msg_generic_id_t)0x000A + AR_API_BASE_REQID)
#define AR_IOC_SEND_REQID                   ((msg_generic_id_t)0x0010 + AR_API_BASE_REQID)
#define AR_IOC_WRITE_REQID                  ((msg_generic_id_t)0x0011 + AR_API_BASE_REQID)
#define AR_SHUTDOWN_ALL_CORES_REQID         ((msg_generic_id_t)0x0012 + AR_API_BASE_REQID)
#define AR_GET_APPLICATION_STATE_REQID      ((msg_generic_id_t)0x0013 + AR_API_BASE_REQID)

/*
 * Generic inter-core request packet for AUTOSAR
 */
typedef struct
{
    mcos_id_t        tid;
    mcos_id_t        lcid;
} ar_caller_t;

typedef struct ar_intercore_request {
    msg_generic_id_t           reqid;
    ar_caller_t                caller;
} ar_intercore_request_t;

/*
 * Generic inter-core return packet for AUTOSAR
 */
typedef struct ar_intercore_return {
    StatusType  status;
} ar_intercore_return_t;


/*
 * Request packet for AUTOSAR API
 */
typedef struct {
    TaskType        task_id;
    const ar_osap_config_t *p_osapconfig;
} ar_apireq_activatetask_t;

typedef struct {
    TaskType        task_id;
    const ar_osap_config_t *p_osapconfig;
} ar_apireq_gettaskstate_t;

typedef struct {
    TaskType        task_id;
    EventMaskType   event;
    const ar_osap_config_t *p_osapconfig;
} ar_apireq_setevent_t;

typedef struct {
    TaskType        task_id;
    const ar_osap_config_t *p_osapconfig;
} ar_apireq_getevent_t;

typedef struct {
    CounterType     counter_id;
    const ar_osap_config_t *p_osapconfig;
} ar_apireq_getcountervalue_t;

typedef struct {
    CounterType     counter_id;
    TickType        value;
    const ar_osap_config_t *p_osapconfig;
} ar_apireq_getelapsedvalue_t;

typedef struct {
    AlarmType       alarm_id;
    const ar_osap_config_t *p_osapconfig;
} ar_apireq_getalarmbase_t;

typedef struct {
    AlarmType       alarm_id;
    const ar_osap_config_t *p_osapconfig;
} ar_apireq_getalarm_t;

typedef struct {
    AlarmType       alarm_id;
    TickType        increment;
    TickType        cycle;
    const ar_osap_config_t *p_osapconfig;
} ar_apireq_setrelalarm_t;

typedef struct {
    AlarmType       alarm_id;
    TickType        start;
    TickType        cycle;
    const ar_osap_config_t *p_osapconfig;
} ar_apireq_setabsalarm_t;

typedef struct {
    AlarmType       alarm_id;
    const ar_osap_config_t *p_osapconfig;
} ar_apireq_cancelalarm_t;

typedef struct {
    IocType                   receiver_id;
} ar_apireq_ioc_t;

#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
typedef struct {
    ApplicationType appl_id;
} ar_apireq_getapplicationstate_t;
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

typedef union {
    /* default */
    uint32              default_data;

    /* ActivateTask */
    ar_apireq_activatetask_t activate_task;

    /* GetTaskState */
    ar_apireq_gettaskstate_t get_task_state;

    /* SetEvent */
    ar_apireq_setevent_t set_event;

    /* GetEvent */
    ar_apireq_getevent_t get_event;

    /* GetCounterValue */
    ar_apireq_getcountervalue_t get_counter_value;

    /* GetElapsedValue */
    ar_apireq_getelapsedvalue_t get_elapsed_value;

    /* GetAlarmBase */
    ar_apireq_getalarmbase_t get_alarm_base;

    /* GetAlarm */
    ar_apireq_getalarm_t get_alarm;

    /* SetRelAlarm */
    ar_apireq_setrelalarm_t set_rel_alarm;

    /* SetAbsAlarm */
    ar_apireq_setabsalarm_t set_abs_alarm;

    /* CancelAlarm */
    ar_apireq_cancelalarm_t cancel_alarm;
    /* IOC */
    ar_apireq_ioc_t ioc;

    /* ShutdownAllCores: no data */

#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
    /* GetApplicationState */
    ar_apireq_getapplicationstate_t get_app_state;
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
} ar_apidata_t;

typedef struct ar_api_request {
    ar_intercore_request_t  head;

    /* API specific information */
    ar_apidata_t            data;
} ar_api_request_t;

/*
 * Return values packet for AUTOSAR API
 */
typedef struct ar_api_return {
    ar_intercore_return_t   head;

    /* API specific information */
    union {
        /* GetTaskState */
        struct {
            TaskStateType   state;
        } get_task_state;

        /* GetEvent */
        struct {
            EventMaskType   event;
        } get_event;

        /* GetCounterValue */
        struct {
            TickType        value;
        } get_counter_value;

        /* GetElapsedValue */
        struct {
            TickType        value;
            TickType        elapsed_value;
        } get_elapsed_value;

        /* GetAlarmBase */
        struct {
            AlarmBaseType   info;
        } get_alarm_base;

        /* GetAlarm */
        struct {
            TickType        tick;
        } get_alarm;

#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
        /* GetApplicationState */
        struct {
            ApplicationStateType  state;
        } get_app_state;

#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

        /* [PRQA_2966] Countermeasure for PRQA warning. */
        uint32  default_data;
    } data;
} ar_api_return_t;

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

extern void ar_mkmsg_callback(const mkcb_t * const mkcb, volatile const void * const p_request, void * const p_reply);

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* AR_MKMSG_H */
