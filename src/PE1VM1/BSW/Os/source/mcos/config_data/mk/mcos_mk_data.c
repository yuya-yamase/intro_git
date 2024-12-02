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
[ mcos_mk_data.c ] - eMCOS Microkernel AUTOSAR Data
****************************************************************************/

#include <mp.cfg>
#include <mcos/mcos.cfg>
#include "mcos_mk_local.h"
#include "mcos_mk_data.h"

/****************************************************************************
 * configuration value check
****************************************************************************/

#include "mcos_cls_buildchk.h"

#if MP_CORE_COUNT < MP_CONTROL_CORE_COUNT
#error MP_CONTROL_CORE_COUNT must be less than or equal to MP_CORE_COUNT.
#endif

/****************************************************************************
 * Core0
 ****************************************************************************/
#define OS_START_SEC_VAR_LOCAL0_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

/* Micro-Kernel control block */
static mkcb_st_t mkcb_core0;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_LOCAL0_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

/* Task control block */
static tcb_t tcb_core0[MCOS_CFG_THR_MAX];

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_LOCAL0_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

/* Activation control block */
static actcb_t actcb_core0[MCOS_CFG_THR_ACT_MAX];

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

/****************************************************************************
 * Core1
 ****************************************************************************/
#if (MP_CONTROL_CORE_COUNT >= 2U)

#define OS_START_SEC_VAR_LOCAL1_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

/* Micro-Kernel control block */
static mkcb_st_t mkcb_core1;

#define OS_STOP_SEC_VAR_LOCAL1_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_LOCAL1_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

/* Task control block */
static tcb_t tcb_core1[MCOS_CFG_THR_MAX];

#define OS_STOP_SEC_VAR_LOCAL1_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_LOCAL1_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

/* Activation control block */
static actcb_t actcb_core1[MCOS_CFG_THR_ACT_MAX];

#define OS_STOP_SEC_VAR_LOCAL1_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

#endif  /* #if (MP_CONTROL_CORE_COUNT >= 2U) */

/****************************************************************************
 * Core2
 ****************************************************************************/
#if (MP_CONTROL_CORE_COUNT >= 3U)

#define OS_START_SEC_VAR_LOCAL2_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

/* Micro-Kernel control block */
static mkcb_st_t mkcb_core2;

#define OS_STOP_SEC_VAR_LOCAL2_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_LOCAL2_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

/* Task control block */
static tcb_t tcb_core2[MCOS_CFG_THR_MAX];

#define OS_STOP_SEC_VAR_LOCAL2_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_LOCAL2_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

/* Activation control block */
static actcb_t actcb_core2[MCOS_CFG_THR_ACT_MAX];

#define OS_STOP_SEC_VAR_LOCAL2_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

#endif  /* #if (MP_CONTROL_CORE_COUNT >= 3U) */

/****************************************************************************
 * Core3
 ****************************************************************************/
#if (MP_CONTROL_CORE_COUNT >= 4U)

#define OS_START_SEC_VAR_LOCAL3_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

/* Micro-Kernel control block */
static mkcb_st_t mkcb_core3;

#define OS_STOP_SEC_VAR_LOCAL3_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_LOCAL3_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

/* Task control block */
static tcb_t tcb_core3[MCOS_CFG_THR_MAX];

#define OS_STOP_SEC_VAR_LOCAL3_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_LOCAL3_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

/* Activation control block */
static actcb_t actcb_core3[MCOS_CFG_THR_ACT_MAX];

#define OS_STOP_SEC_VAR_LOCAL3_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

#endif  /* #if (MP_CONTROL_CORE_COUNT >= 4U) */


/****************************************************************************
 * Shared
 ****************************************************************************/

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/* mcos_mkcb_ptr_table[] */
mkcb_t * const mcos_mkcb_ptr_table[MP_CONTROL_CORE_COUNT] =
{
    (mkcb_t *)&mkcb_core0,
#if (MP_CONTROL_CORE_COUNT >= 2U)
    (mkcb_t *)&mkcb_core1,
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 2U) */
#if (MP_CONTROL_CORE_COUNT >= 3U)
    (mkcb_t *)&mkcb_core2,
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 3U) */
#if (MP_CONTROL_CORE_COUNT >= 4U)
    (mkcb_t *)&mkcb_core3,
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 4U) */
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/* mcos_mkcb_cmn_ptr_table[] */
mkcb_cmn_t * const mcos_mkcb_cmn_ptr_table[MP_CONTROL_CORE_COUNT] =
{
    (mkcb_cmn_t *)&mkcb_core0.mk_cmn.cmn,
#if (MP_CONTROL_CORE_COUNT >= 2U)
    (mkcb_cmn_t *)&mkcb_core1.mk_cmn.cmn,
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 2U) */
#if (MP_CONTROL_CORE_COUNT >= 3U)
    (mkcb_cmn_t *)&mkcb_core2.mk_cmn.cmn,
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 3U) */
#if (MP_CONTROL_CORE_COUNT >= 4U)
    (mkcb_cmn_t *)&mkcb_core3.mk_cmn.cmn,
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 4U) */
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/* MKCONFIG data */
const mkconfig_t mcos_mkconfig =
{
    MP_CONTROL_CORE_COUNT,
    MP_CORE_COUNT,
    MP_MASTER_CORENO,
    MP_MIN_CORENO,
    MP_MAX_CORENO,
    MCOS_CFG_THR_MAX,
    (uint16_t)MCOS_CFG_THR_ACT_MAX,
    (uint32_t)MCOS_CFG_SYS_STACKSIZE
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/* mcos_tcb_ptr_table[] */
tcb_t * const mcos_tcb_ptr_table[MP_CONTROL_CORE_COUNT] =
{
    &tcb_core0[0],
#if (MP_CONTROL_CORE_COUNT >= 2U)
    &tcb_core1[0],
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 2U) */
#if (MP_CONTROL_CORE_COUNT >= 3U)
    &tcb_core2[0],
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 3U) */
#if (MP_CONTROL_CORE_COUNT >= 4U)
    &tcb_core3[0],
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 4U) */
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/* mcos_actcb_ptr_table[] */
actcb_t * const mcos_actcb_ptr_table[MP_CONTROL_CORE_COUNT] =
{
    &actcb_core0[0],
#if (MP_CONTROL_CORE_COUNT >= 2U)
    &actcb_core1[0],
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 2U) */
#if (MP_CONTROL_CORE_COUNT >= 3U)
    &actcb_core2[0],
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 3U) */
#if (MP_CONTROL_CORE_COUNT >= 4U)
    &actcb_core3[0],
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 4U) */
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#if MCOS_CFG_DS_TRACE_ENABLE

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

/* trace buffer count */
const uint32 mcos_trace_buffer_count = MCOS_CFG_DS_TRACE_COUNT_DEFAULT;

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

/*
 * eMCOS TRACE buffer
*/

#define OS_START_SEC_VAR_LOCAL0_CLEARED_32
#include "Os_MemMap.h"
static ds_trace_data_t mcos_trace_buf_core0[MCOS_CFG_DS_TRACE_COUNT_DEFAULT];
#define OS_STOP_SEC_VAR_LOCAL0_CLEARED_32
#include "Os_MemMap.h"

#if MP_CONTROL_CORE_COUNT > 1U

#define OS_START_SEC_VAR_LOCAL1_CLEARED_32
#include "Os_MemMap.h"
static ds_trace_data_t mcos_trace_buf_core1[MCOS_CFG_DS_TRACE_COUNT_DEFAULT];
#define OS_STOP_SEC_VAR_LOCAL1_CLEARED_32
#include "Os_MemMap.h"

#endif /* #if MP_CONTROL_CORE_COUNT > 1U */

#if MP_CONTROL_CORE_COUNT > 2U

#define OS_START_SEC_VAR_LOCAL2_CLEARED_32
#include "Os_MemMap.h"
static ds_trace_data_t mcos_trace_buf_core2[MCOS_CFG_DS_TRACE_COUNT_DEFAULT];
#define OS_STOP_SEC_VAR_LOCAL2_CLEARED_32
#include "Os_MemMap.h"

#endif /* #if MP_CONTROL_CORE_COUNT > 2U */

#if MP_CONTROL_CORE_COUNT > 3U

#define OS_START_SEC_VAR_LOCAL3_CLEARED_32
#include "Os_MemMap.h"
static ds_trace_data_t mcos_trace_buf_core3[MCOS_CFG_DS_TRACE_COUNT_DEFAULT];
#define OS_STOP_SEC_VAR_LOCAL3_CLEARED_32
#include "Os_MemMap.h"

#endif /* #if MP_CONTROL_CORE_COUNT > 3U */

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

ds_trace_data_t * const mcos_trace_buf_ptr[MP_CONTROL_CORE_COUNT] = {
        &mcos_trace_buf_core0[0],
#if MP_CONTROL_CORE_COUNT > 1U
        &mcos_trace_buf_core1[0],
#endif /* #if MP_CONTROL_CORE_COUNT > 1U */
#if MP_CONTROL_CORE_COUNT > 2U
        &mcos_trace_buf_core2[0],
#endif /* #if MP_CONTROL_CORE_COUNT > 2U */
#if MP_CONTROL_CORE_COUNT > 3U
        &mcos_trace_buf_core3[0],
#endif /* #if MP_CONTROL_CORE_COUNT > 3U */
};

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"


#define OS_START_SEC_VAR_GLOBAL_CLEARED_32
#include "Os_MemMap.h"

/*
 * Addresses of control blocks for debugging.
 * This is used by the script file to dump the trace buffers.
 */
dscb_local_t* mcos_ds_control_block[MP_CONTROL_CORE_COUNT];

#define OS_STOP_SEC_VAR_GLOBAL_CLEARED_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

const uint32_t mcos_ds_control_block_sz = sizeof(mcos_ds_control_block);

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#endif /* #if MCOS_CFG_DS_TRACE_ENABLE */
