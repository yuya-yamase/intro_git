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

ar_isrcb_t ar_isrcb_eMCOS_ISR_INTOSTM5TINT;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_eMCOS_ISR_INTTAUD0I14;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_eMCOS_ISR_INTRCAN3REC;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_eMCOS_ISR_INTRCAN3TRX;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_eMCOS_ISR_INTRCAN5REC;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_eMCOS_ISR_INTRCAN5TRX;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_eMCOS_ISR_INTRCAN7REC;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_eMCOS_ISR_INTRCAN7TRX;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_eMCOS_ISR_INTRCAN11REC;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

ar_isrcb_t ar_isrcb_eMCOS_ISR_INTRCAN11TRX;

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
    &ar_isrcb_eMCOS_ISR_INTOSTM5TINT,
    &ar_isrcb_eMCOS_ISR_INTTAUD0I14,
    &ar_isrcb_eMCOS_ISR_INTRCAN3REC,
    &ar_isrcb_eMCOS_ISR_INTRCAN3TRX,
    &ar_isrcb_eMCOS_ISR_INTRCAN5REC,
    &ar_isrcb_eMCOS_ISR_INTRCAN5TRX,
    &ar_isrcb_eMCOS_ISR_INTRCAN7REC,
    &ar_isrcb_eMCOS_ISR_INTRCAN7TRX,
    &ar_isrcb_eMCOS_ISR_INTRCAN11REC,
    &ar_isrcb_eMCOS_ISR_INTRCAN11TRX
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
        &GENNAME_ISR(eMCOS_ISR_INTOSTM5TINT),
        HAL_V850_INTC2_OFFSET + 204U,  /* INTC2 : 204 */
        -2,
        AR_DISABLE
    },
    {
        &GENNAME_ISR(eMCOS_ISR_INTTAUD0I14),
        HAL_V850_INTC1_OFFSET + 26U,  /* INTC1 : 26 */
        -1,
        AR_DISABLE
    },
    {
        &GENNAME_ISR(eMCOS_ISR_INTRCAN3REC),
        HAL_V850_INTC2_OFFSET + 308U,  /* INTC2 : 308 */
        -6,
        AR_DISABLE
    },
    {
        &GENNAME_ISR(eMCOS_ISR_INTRCAN3TRX),
        HAL_V850_INTC2_OFFSET + 309U,  /* INTC2 : 309 */
        -6,
        AR_DISABLE
    },
    {
        &GENNAME_ISR(eMCOS_ISR_INTRCAN5REC),
        HAL_V850_INTC2_OFFSET + 314U,  /* INTC2 : 314 */
        -6,
        AR_DISABLE
    },
    {
        &GENNAME_ISR(eMCOS_ISR_INTRCAN5TRX),
        HAL_V850_INTC2_OFFSET + 315U,  /* INTC2 : 315 */
        -6,
        AR_DISABLE
    },
    {
        &GENNAME_ISR(eMCOS_ISR_INTRCAN7REC),
        HAL_V850_INTC2_OFFSET + 320U,  /* INTC2 : 320 */
        -6,
        AR_DISABLE
    },
    {
        &GENNAME_ISR(eMCOS_ISR_INTRCAN7TRX),
        HAL_V850_INTC2_OFFSET + 321U,  /* INTC2 : 321 */
        -6,
        AR_DISABLE
    },
    {
        &GENNAME_ISR(eMCOS_ISR_INTRCAN11REC),
        HAL_V850_INTC2_OFFSET + 334U,  /* INTC2 : 334 */
        -6,
        AR_DISABLE
    },
    {
        &GENNAME_ISR(eMCOS_ISR_INTRCAN11TRX),
        HAL_V850_INTC2_OFFSET + 335U,  /* INTC2 : 335 */
        -6,
        AR_DISABLE
    }
};

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"






/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-1-0                                              */
/****************************************************************************/
