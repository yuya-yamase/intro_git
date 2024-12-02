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
 [ Os_Cfg.c ] - OS module's configuration data file
****************************************************************************/

#include "Os.h"
#include "ar_kernel_impl.h"
#include "ar_mcos.h"
#include "ar_task.h"
#include "ar_resource_local.h"
#include "ar_counter_local.h"
#include "ar_alarm_local.h"
#include "ar_interrupt_local.h"
#include "ar_osap_local.h"
#include "ar_multicore.h"
#include "ar_spinlock_local.h"
#include "ar_ioc_local.h"
#include "Os_Cfg_internal.h"
#include "mcos/mcos_ds.cfg"
#include "hal/cpu/v850/hal/hal_v850_cfg.h"


#define OS_START_SEC_VAR_NO_INIT_16
#include "Os_MemMap.h"

mcos_id_t ar_task2thread_table[AR_OS_NUM_TASKS];

#define OS_STOP_SEC_VAR_NO_INIT_16
#include "Os_MemMap.h"

#if (MCOS_CFG_DS_TRACE_ENABLE || (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON))

#define OS_START_SEC_VAR_NO_INIT_16
#include "Os_MemMap.h"

TaskType ar_thread2task_table[MCOS_CFG_THR_MAX*MP_CONTROL_CORE_COUNT];

#define OS_STOP_SEC_VAR_NO_INIT_16
#include "Os_MemMap.h"

#endif /* #if (MCOS_CFG_DS_TRACE_ENABLE || (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)) */

/*
 * Task control blocks
 */

#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

static ar_tcb_t ar_tcb_Ecu_IdleTask;
static ar_tcb_t ar_tcb_Ecu_InitTask;
static ar_tcb_t ar_tcb_Task_MM_High;
static ar_tcb_t ar_tcb_Task_MM_Low;
static ar_tcb_t ar_tcb_Task_MM_Medium;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"




/*
 * Stacks for Basic Task
 *
 */
#pragma ghs section bss=".osVar_stack_core0_pri1"
static mcos_stack_t ar_stack_core0_pri1[MCOS_STACK_SIZE(1024U)];
#pragma ghs section bss=default
#pragma ghs section bss=".osVar_stack_core0_pri4"
static mcos_stack_t ar_stack_core0_pri4[MCOS_STACK_SIZE(1024U)];
#pragma ghs section bss=default
#pragma ghs section bss=".osVar_stack_core0_pri8"
static mcos_stack_t ar_stack_core0_pri8[MCOS_STACK_SIZE(4608U)];
#pragma ghs section bss=default
#pragma ghs section bss=".osVar_stack_core0_pri12"
static mcos_stack_t ar_stack_core0_pri12[MCOS_STACK_SIZE(2048U)];
#pragma ghs section bss=default
#pragma ghs section bss=".osVar_stack_core0_pri20"
static mcos_stack_t ar_stack_core0_pri20[MCOS_STACK_SIZE(1024U)];
#pragma ghs section bss=default

/*
 * Task configurations
 *
 */


#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

const ar_task_config_t ar_task_configs[AR_OS_NUM_TASKS] = {
    {
        &GENNAME_TASK(Ecu_IdleTask),
        MCOS_STACK_SIZE(1024U),
        (uint8)AR_MCOS_TPRI(1),
        (uint8)AR_MCOS_TPRI(1),
        0U,
        1U,
        (void *)&ar_stack_core0_pri1,
        (const ar_osap_config_t  *)NULL
    },
    {
        &GENNAME_TASK(Ecu_InitTask),
        MCOS_STACK_SIZE(1024U),
        (uint8)AR_MCOS_TPRI(20),
        (uint8)AR_MCOS_TPRI(20),
        0U,
        1U,
        (void *)&ar_stack_core0_pri20,
        (const ar_osap_config_t  *)NULL
    },
    {
        &GENNAME_TASK(Task_MM_High),
        MCOS_STACK_SIZE(2048U),
        (uint8)AR_MCOS_TPRI(12),
        (uint8)AR_MCOS_TPRI(12),
        1U,
        0U,
        (void *)&ar_stack_core0_pri12,
        (const ar_osap_config_t  *)NULL
    },
    {
        &GENNAME_TASK(Task_MM_Low),
        MCOS_STACK_SIZE(1024U),
        (uint8)AR_MCOS_TPRI(4),
        (uint8)AR_MCOS_TPRI(4),
        1U,
        0U,
        (void *)&ar_stack_core0_pri4,
        (const ar_osap_config_t  *)NULL
    },
    {
        &GENNAME_TASK(Task_MM_Medium),
        MCOS_STACK_SIZE(4608U),
        (uint8)AR_MCOS_TPRI(8),
        (uint8)AR_MCOS_TPRI(8),
        1U,
        0U,
        (void *)&ar_stack_core0_pri8,
        (const ar_osap_config_t  *)NULL
    }
};

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

/*
 * table of pointer to Task control block
 */

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

ar_tcb_t * const ar_tcb_ptr_table[AR_OS_NUM_TASKS] ={
    &ar_tcb_Ecu_IdleTask,
    &ar_tcb_Ecu_InitTask,
    &ar_tcb_Task_MM_High,
    &ar_tcb_Task_MM_Low,
    &ar_tcb_Task_MM_Medium
};

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"



/*
 * Counter control blocks
 */

#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

static ar_countercb_t ar_countercb_OS_SYSTEM_COUNTER0;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

/*
 * Counter configurations
 *
 */

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

const ar_counter_config_t ar_counter_configs[AR_OS_NUM_COUNTERS] = {
    {
        1000000U,
        1U,
        1U,
        {
            1000000U,
            2000001U
        },
        (const ar_osap_config_t  *)NULL    }
};

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

/*
 * table of pointer to Counter control block
 */

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

ar_countercb_t * const ar_countercb_ptr_table[AR_OS_NUM_COUNTERS] = {
    &ar_countercb_OS_SYSTEM_COUNTER0
};

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"



/*
 * Alarm action stub functions
 *
 */
#define OS_START_SEC_CODE
#include "Os_MemMap.h"
static void ar_alarm_action_ECU_u2HIGHTASK_ALM(void);
static void
ar_alarm_action_ECU_u2HIGHTASK_ALM(void)
{
   (void)ar_act_activatetask(Task_MM_High, NULL);
}
static void ar_alarm_action_ECU_u2LOWTASK_ALM(void);
static void
ar_alarm_action_ECU_u2LOWTASK_ALM(void)
{
   (void)ar_act_activatetask(Task_MM_Low, NULL);
}
static void ar_alarm_action_ECU_u2MEDIUMTASK_ALM(void);
static void
ar_alarm_action_ECU_u2MEDIUMTASK_ALM(void)
{
   (void)ar_act_activatetask(Task_MM_Medium, NULL);
}

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

/*
 * Alarm control blocks
 */

#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

static ar_alarmcb_t ar_alarmcb_ECU_u2HIGHTASK_ALM;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

static ar_alarmcb_t ar_alarmcb_ECU_u2LOWTASK_ALM;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

static ar_alarmcb_t ar_alarmcb_ECU_u2MEDIUMTASK_ALM;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

/*
 * Alarm configurations
 *
 */

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

const ar_alarm_config_t ar_alarm_configs[AR_OS_NUM_ALARMS] = {
    {
        &ar_countercb_OS_SYSTEM_COUNTER0,
        0U,
        (AR_ALARM_ACTIVATETASK | AR_ALARM_RELATIVE),
        0U,
        0U,
        &ar_alarm_action_ECU_u2HIGHTASK_ALM,
        77U,
        (const ar_osap_config_t  *)NULL    },             {
        &ar_countercb_OS_SYSTEM_COUNTER0,
        0U,
        (AR_ALARM_ACTIVATETASK | AR_ALARM_RELATIVE),
        0U,
        0U,
        &ar_alarm_action_ECU_u2LOWTASK_ALM,
        28U,
        (const ar_osap_config_t  *)NULL    },             {
        &ar_countercb_OS_SYSTEM_COUNTER0,
        0U,
        (AR_ALARM_ACTIVATETASK | AR_ALARM_RELATIVE),
        0U,
        0U,
        &ar_alarm_action_ECU_u2MEDIUMTASK_ALM,
        51U,
        (const ar_osap_config_t  *)NULL    }
};

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

/*
 * table of pointer to Alarm control block
 */

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

ar_alarmcb_t * const ar_alarmcb_ptr_table[AR_OS_NUM_ALARMS] = {
    &ar_alarmcb_ECU_u2HIGHTASK_ALM,
    &ar_alarmcb_ECU_u2LOWTASK_ALM,
    &ar_alarmcb_ECU_u2MEDIUMTASK_ALM
};

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"




/*
 * Category 2 ISR control blocks
 */

#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_INTRIIC0EE_ISR;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_INTRIIC0RI_ISR;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_INTRIIC0TI_ISR;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_INTRIIC0TEI_ISR;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_INTRIIC1EE_ISR;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_INTRIIC1RI_ISR;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_INTRIIC1TI_ISR;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_INTRIIC1TEI_ISR;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_OS_SYSTEM_COUNTER_ISR0;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_INTTAUD0CH14;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"



/*
 * Category 2 ISR configurations
 *
 */

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

const ar_isr_config_t ar_isr_configs[AR_OS_NUM_C2ISRS] = {
    {
        &(ar_int_configs[0]),
        (const ar_osap_config_t  *)NULL
    },
    {
        &(ar_int_configs[1]),
        (const ar_osap_config_t  *)NULL
    },
    {
        &(ar_int_configs[2]),
        (const ar_osap_config_t  *)NULL
    },
    {
        &(ar_int_configs[3]),
        (const ar_osap_config_t  *)NULL
    },
    {
        &(ar_int_configs[4]),
        (const ar_osap_config_t  *)NULL
    },
    {
        &(ar_int_configs[5]),
        (const ar_osap_config_t  *)NULL
    },
    {
        &(ar_int_configs[6]),
        (const ar_osap_config_t  *)NULL
    },
    {
        &(ar_int_configs[7]),
        (const ar_osap_config_t  *)NULL
    },
    {
        &(ar_int_configs[8]),
        (const ar_osap_config_t  *)NULL
    },
    {
        &(ar_int_configs[9]),
        (const ar_osap_config_t  *)NULL
    }
};

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

/*
 * table of pointer to Category 2 ISR control block
 */

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

ar_isrcb_t * const ar_isrcb_ptr_table[AR_OS_NUM_C2ISRS] = {
    &ar_isrcb_INTRIIC0EE_ISR,
    &ar_isrcb_INTRIIC0RI_ISR,
    &ar_isrcb_INTRIIC0TI_ISR,
    &ar_isrcb_INTRIIC0TEI_ISR,
    &ar_isrcb_INTRIIC1EE_ISR,
    &ar_isrcb_INTRIIC1RI_ISR,
    &ar_isrcb_INTRIIC1TI_ISR,
    &ar_isrcb_INTRIIC1TEI_ISR,
    &ar_isrcb_OS_SYSTEM_COUNTER_ISR0,
    &ar_isrcb_INTTAUD0CH14
};

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"


/*
 * Interrupt configurations
 *
 */

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

const ar_int_config_t ar_int_configs[AR_OS_NUM_C2ISRS] = {
    /* for Category 2 ISR */

    {
        &GENNAME_ISR(INTRIIC0EE_ISR),
        HAL_V850_INTC2_OFFSET + 685U,  /* INTC2 : 685 */
        -1,
        AR_DISABLE
    },
    {
        &GENNAME_ISR(INTRIIC0RI_ISR),
        HAL_V850_INTC2_OFFSET + 686U,  /* INTC2 : 686 */
        -1,
        AR_DISABLE
    },
    {
        &GENNAME_ISR(INTRIIC0TI_ISR),
        HAL_V850_INTC2_OFFSET + 687U,  /* INTC2 : 687 */
        -1,
        AR_DISABLE
    },
    {
        &GENNAME_ISR(INTRIIC0TEI_ISR),
        HAL_V850_INTC2_OFFSET + 688U,  /* INTC2 : 688 */
        -1,
        AR_DISABLE
    },
    {
        &GENNAME_ISR(INTRIIC1EE_ISR),
        HAL_V850_INTC2_OFFSET + 689U,  /* INTC2 : 689 */
        -1,
        AR_DISABLE
    },
    {
        &GENNAME_ISR(INTRIIC1RI_ISR),
        HAL_V850_INTC2_OFFSET + 690U,  /* INTC2 : 690 */
        -1,
        AR_DISABLE
    },
    {
        &GENNAME_ISR(INTRIIC1TI_ISR),
        HAL_V850_INTC2_OFFSET + 691U,  /* INTC2 : 691 */
        -1,
        AR_DISABLE
    },
    {
        &GENNAME_ISR(INTRIIC1TEI_ISR),
        HAL_V850_INTC2_OFFSET + 692U,  /* INTC2 : 692 */
        -1,
        AR_DISABLE
    },
    {
        &GENNAME_ISR(OS_SYSTEM_COUNTER_ISR0),
        HAL_V850_INTC2_OFFSET + 204U,  /* INTC2 : 204 */
        -2,
        AR_ENABLE
    },
    {
        &GENNAME_ISR(INTTAUD0CH14),
        HAL_V850_INTC1_OFFSET + 26U,  /* INTC1 : 26 */
        -1,
        AR_DISABLE
    }
};

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"






/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/
