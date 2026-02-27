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

static ar_tcb_t ar_tcb_eMCOS_TASK_High;
static ar_tcb_t ar_tcb_eMCOS_TASK_Idle;
static ar_tcb_t ar_tcb_eMCOS_TASK_Medium;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"




/*
 * Stacks for Basic Task
 *
 */
#pragma ghs section bss=".osVar_stack_core0_pri1"
static mcos_stack_t ar_stack_core0_pri1[MCOS_STACK_SIZE(1024U)];
#pragma ghs section bss=default
#pragma ghs section bss=".osVar_stack_core0_pri8"
static mcos_stack_t ar_stack_core0_pri8[MCOS_STACK_SIZE(8192U)];
#pragma ghs section bss=default
#pragma ghs section bss=".osVar_stack_core0_pri12"
static mcos_stack_t ar_stack_core0_pri12[MCOS_STACK_SIZE(4096U)];
#pragma ghs section bss=default

/*
 * Task configurations
 *
 */


#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

const ar_task_config_t ar_task_configs[AR_OS_NUM_TASKS] = {
    {
        &GENNAME_TASK(eMCOS_TASK_High),
        MCOS_STACK_SIZE(4096U),
        (uint8)AR_MCOS_TPRI(12),
        (uint8)AR_MCOS_TPRI(12),
        1U,
        0U,
        (void *)&ar_stack_core0_pri12,
        (const ar_osap_config_t  *)NULL
    },
    {
        &GENNAME_TASK(eMCOS_TASK_Idle),
        MCOS_STACK_SIZE(1024U),
        (uint8)AR_MCOS_TPRI(1),
        (uint8)AR_MCOS_TPRI(1),
        0U,
        1U,
        (void *)&ar_stack_core0_pri1,
        (const ar_osap_config_t  *)NULL
    },
    {
        &GENNAME_TASK(eMCOS_TASK_Medium),
        MCOS_STACK_SIZE(8192U),
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
    &ar_tcb_eMCOS_TASK_High,
    &ar_tcb_eMCOS_TASK_Idle,
    &ar_tcb_eMCOS_TASK_Medium
};

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"







/*
 * Category 2 ISR control blocks
 */

#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_eMCOS_ISR_INTOSTM1TINT;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_eMCOS_ISR_INTP38;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_eMCOS_ISR_INTOSTM8TINT;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_eMCOS_ISR_INTRIIC0EE;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_eMCOS_ISR_INTRIIC0RI;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_eMCOS_ISR_INTRIIC0TI;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_eMCOS_ISR_INTRIIC0TEI;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_eMCOS_ISR_INTRIIC1EE;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_eMCOS_ISR_INTRIIC1RI;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_eMCOS_ISR_INTRIIC1TI;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_eMCOS_ISR_INTRIIC1TEI;

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
    },
    {
        &(ar_int_configs[10]),
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
    &ar_isrcb_eMCOS_ISR_INTOSTM1TINT,
    &ar_isrcb_eMCOS_ISR_INTP38,
    &ar_isrcb_eMCOS_ISR_INTOSTM8TINT,
    &ar_isrcb_eMCOS_ISR_INTRIIC0EE,
    &ar_isrcb_eMCOS_ISR_INTRIIC0RI,
    &ar_isrcb_eMCOS_ISR_INTRIIC0TI,
    &ar_isrcb_eMCOS_ISR_INTRIIC0TEI,
    &ar_isrcb_eMCOS_ISR_INTRIIC1EE,
    &ar_isrcb_eMCOS_ISR_INTRIIC1RI,
    &ar_isrcb_eMCOS_ISR_INTRIIC1TI,
    &ar_isrcb_eMCOS_ISR_INTRIIC1TEI
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
        &GENNAME_ISR(eMCOS_ISR_INTOSTM1TINT),
        HAL_V850_INTC2_OFFSET + 200U,  /* INTC2 : 200 */
        -3,
        AR_DISABLE
    },
    {
        &GENNAME_ISR(eMCOS_ISR_INTP38),
        HAL_V850_INTC2_OFFSET + 582U,  /* INTC2 : 582 */
        -5,
        AR_DISABLE
    },
    {
        &GENNAME_ISR(eMCOS_ISR_INTOSTM8TINT),
        HAL_V850_INTC2_OFFSET + 207U,  /* INTC2 : 207 */
        -2,
        AR_DISABLE
    },
    {
        &GENNAME_ISR(eMCOS_ISR_INTRIIC0EE),
        HAL_V850_INTC2_OFFSET + 685U,  /* INTC2 : 685 */
        -1,
        AR_DISABLE
    },
    {
        &GENNAME_ISR(eMCOS_ISR_INTRIIC0RI),
        HAL_V850_INTC2_OFFSET + 686U,  /* INTC2 : 686 */
        -1,
        AR_DISABLE
    },
    {
        &GENNAME_ISR(eMCOS_ISR_INTRIIC0TI),
        HAL_V850_INTC2_OFFSET + 687U,  /* INTC2 : 687 */
        -1,
        AR_DISABLE
    },
    {
        &GENNAME_ISR(eMCOS_ISR_INTRIIC0TEI),
        HAL_V850_INTC2_OFFSET + 688U,  /* INTC2 : 688 */
        -1,
        AR_DISABLE
    },
    {
        &GENNAME_ISR(eMCOS_ISR_INTRIIC1EE),
        HAL_V850_INTC2_OFFSET + 689U,  /* INTC2 : 689 */
        -1,
        AR_DISABLE
    },
    {
        &GENNAME_ISR(eMCOS_ISR_INTRIIC1RI),
        HAL_V850_INTC2_OFFSET + 690U,  /* INTC2 : 690 */
        -1,
        AR_DISABLE
    },
    {
        &GENNAME_ISR(eMCOS_ISR_INTRIIC1TI),
        HAL_V850_INTC2_OFFSET + 691U,  /* INTC2 : 691 */
        -1,
        AR_DISABLE
    },
    {
        &GENNAME_ISR(eMCOS_ISR_INTRIIC1TEI),
        HAL_V850_INTC2_OFFSET + 692U,  /* INTC2 : 692 */
        -1,
        AR_DISABLE
    }
};

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"






/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/
