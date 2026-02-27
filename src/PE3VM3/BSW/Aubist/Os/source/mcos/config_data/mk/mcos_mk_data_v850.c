/*
    Copyright(C) 2019 eSOL Co., Ltd. All rights reserved.

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
[ mcos_mk_data_v850.c ] - eMCOS Microkernel AUTOSAR Data for V850
****************************************************************************/
#include <mp.cfg>
#include <mcos/mcos.cfg>
#include <hal/cpu/v850/hal/hal_v850_cfg.h>
#include <hal/cpu/v850/mcos/mcos_v850.cfg>

#include "mcos_mk_data.h"
#include "mcos_v850_local.h"

/* MP_CORE_COUNT, MP_CONTROL_CORE_COUNT */
#if MP_CORE_COUNT > 4U
#error MP_CORE_COUNT exceeds the upper limit.
#endif

#if MP_CONTROL_CORE_COUNT > 4U
#error MP_CONTROL_CORE_COUNT exceeds the upper limit.
#endif

/****************************************************************************
 * configuration value check
****************************************************************************/

/* MKMSG interrupt id */

#if MP_CONTROL_CORE_COUNT >= 2U

#if ((MCOS_V850_MKMSG_INTERRUPT_NUMBER < 0U) || (MCOS_V850_MKMSG_INTERRUPT_NUMBER > 3U))
#error Invalid MCOS_V850_MKMSG_INTERRUPT_NUMBER value
#endif /* #if ((MCOS_V850_MKMSG_INTERRUPT_NUMBER < 0U) || (MCOS_V850_MKMSG_INTERRUPT_NUMBER > 3U)) */

/* RaiseInterCoreInterrupt interrupt id */

#if ((MCOS_V850_ICI_INTERRUPT_NUMBER < 0U) || (MCOS_V850_ICI_INTERRUPT_NUMBER > 3U))
#error Invalid MCOS_V850_ICI_INTERRUPT_NUMBER value
#endif /* #if ((MCOS_V850_ICI_INTERRUPT_NUMBER < 0U) || (MCOS_V850_ICI_INTERRUPT_NUMBER > 3U)) */

#endif /* #if MP_CONTROL_CORE_COUNT >= 2U */

#if MP_CONTROL_CORE_COUNT >= 2U

/* MKMSG buffer size */
#define MKMSG_SYNC_BUF_SIZE                 ((uint32_t)MP_CONTROL_CORE_COUNT - 1U)
#define MKMSG_ASYNC_BUF_SIZE                ((sizeof(ar_api_request_t) + sizeof(mcos_ringbuf_vunit_t))/sizeof(mcos_ringbuf_vunit_t))
#define MKMSG_ASYNC_BYTE_BUF_SIZE           (MKMSG_ASYNC_BUF_SIZE * sizeof(mcos_ringbuf_vunit_t))

#endif /* #if MP_CONTROL_CORE_COUNT >= 2U */

/****************************************************************************
 * Core0
 ****************************************************************************/
#if (MP_CONTROL_CORE_COUNT >= 2U)

#define OS_START_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

/* Micro-Kernel control block */
static hwlcb_t hwlcb_core0;

#define OS_STOP_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

static volatile mcos_ringbuf_funit_t   sync_data_core0[MKMSG_SYNC_BUF_SIZE];

#define OS_STOP_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

static volatile mcos_ringbuf_uint8_t   async_data_core0[MKMSG_ASYNC_BYTE_BUF_SIZE];

#define OS_STOP_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

#endif /* #if (MP_CONTROL_CORE_COUNT >= 2U) */

#define OS_START_SEC_VAR_LOCAL0_NO_INIT_64
#include "Os_MemMap.h"

/* System stack */
static mcos_stack_t mk_sysstack_core0[MCOS_STACK_SIZE(MCOS_CFG_SYS_STACKSIZE)];

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_64
#include "Os_MemMap.h"

/****************************************************************************
 * Core1
 ****************************************************************************/
#if (MP_CONTROL_CORE_COUNT >= 2U)

#define OS_START_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

/* Micro-Kernel control block */
static hwlcb_t hwlcb_core1;

#define OS_STOP_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"


#define OS_START_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

static volatile mcos_ringbuf_funit_t   sync_data_core1[MKMSG_SYNC_BUF_SIZE];

#define OS_STOP_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

static volatile mcos_ringbuf_uint8_t   async_data_core1[MKMSG_ASYNC_BYTE_BUF_SIZE];

#define OS_STOP_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_LOCAL1_NO_INIT_64
#include "Os_MemMap.h"

/* System stack */
static mcos_stack_t mk_sysstack_core1[MCOS_STACK_SIZE(MCOS_CFG_SYS_STACKSIZE)];

#define OS_STOP_SEC_VAR_LOCAL1_NO_INIT_64
#include "Os_MemMap.h"

#endif /* #if (MP_CONTROL_CORE_COUNT >= 2U) */

/****************************************************************************
 * Core2
 ****************************************************************************/
#if (MP_CONTROL_CORE_COUNT >= 3U)

#define OS_START_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

/* Micro-Kernel control block */
static hwlcb_t hwlcb_core2;

#define OS_STOP_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"


#define OS_START_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

static volatile mcos_ringbuf_funit_t   sync_data_core2[MKMSG_SYNC_BUF_SIZE];

#define OS_STOP_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

static volatile mcos_ringbuf_uint8_t   async_data_core2[MKMSG_ASYNC_BYTE_BUF_SIZE];

#define OS_STOP_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_LOCAL2_NO_INIT_64
#include "Os_MemMap.h"

/* System stack */
static mcos_stack_t mk_sysstack_core2[MCOS_STACK_SIZE(MCOS_CFG_SYS_STACKSIZE)];

#define OS_STOP_SEC_VAR_LOCAL2_NO_INIT_64
#include "Os_MemMap.h"

#endif  /* #if (MP_CONTROL_CORE_COUNT >= 3U) */

/****************************************************************************
 * Core3
 ****************************************************************************/
#if (MP_CONTROL_CORE_COUNT >= 4U)

#define OS_START_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

/* Micro-Kernel control block */
static hwlcb_t hwlcb_core3;

#define OS_STOP_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"


#define OS_START_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

static volatile mcos_ringbuf_funit_t   sync_data_core3[MKMSG_SYNC_BUF_SIZE];

#define OS_STOP_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

static volatile mcos_ringbuf_uint8_t   async_data_core3[MKMSG_ASYNC_BYTE_BUF_SIZE];

#define OS_STOP_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_LOCAL3_NO_INIT_64
#include "Os_MemMap.h"

/* System stack */
static mcos_stack_t mk_sysstack_core3[MCOS_STACK_SIZE(MCOS_CFG_SYS_STACKSIZE)];

#define OS_STOP_SEC_VAR_LOCAL3_NO_INIT_64
#include "Os_MemMap.h"

#endif  /* #if (MP_CONTROL_CORE_COUNT >= 4U) */


/****************************************************************************
 * Shared
 ****************************************************************************/
#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/* mcos_mksysstack_bottom_addr_table[] */
const void * const mcos_mksysstack_bottom_addr_table[MP_CONTROL_CORE_COUNT] =
{
    (void *)((mcos_uintptr_t)mk_sysstack_core0 + MCOS_STACK_SIZE_IN_BYTES(MCOS_CFG_SYS_STACKSIZE)),
#if (MP_CONTROL_CORE_COUNT >= 2U)
    (void *)((mcos_uintptr_t)mk_sysstack_core1 + MCOS_STACK_SIZE_IN_BYTES(MCOS_CFG_SYS_STACKSIZE)),
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 2U) */
#if (MP_CONTROL_CORE_COUNT >= 3U)
    (void *)((mcos_uintptr_t)mk_sysstack_core2 + MCOS_STACK_SIZE_IN_BYTES(MCOS_CFG_SYS_STACKSIZE)),
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 3U) */
#if (MP_CONTROL_CORE_COUNT >= 4U)
    (void *)((mcos_uintptr_t)mk_sysstack_core3 + MCOS_STACK_SIZE_IN_BYTES(MCOS_CFG_SYS_STACKSIZE)),
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 4U) */
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/* mcos_mksysstack_top_addr_table[] */
const void * const mcos_mksysstack_top_addr_table[MP_CONTROL_CORE_COUNT] =
{
    (void *)mk_sysstack_core0,
#if (MP_CONTROL_CORE_COUNT >= 2U)
    (void *)mk_sysstack_core1,
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 2U) */
#if (MP_CONTROL_CORE_COUNT >= 3U)
    (void *)mk_sysstack_core2,
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 3U) */
#if (MP_CONTROL_CORE_COUNT >= 4U)
    (void *)mk_sysstack_core3,
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 4U) */
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/* mcos_v850_hwlcb_table[] */
hwlcb_t * const mcos_v850_hwlcb_table[MP_CONTROL_CORE_COUNT] =
{
#if MP_CONTROL_CORE_COUNT == 1U
    NULL
#else /* #if MP_CONTROL_CORE_COUNT == 1U */
    &hwlcb_core0,
#if (MP_CONTROL_CORE_COUNT >= 2U)
    &hwlcb_core1,
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 2U) */
#if (MP_CONTROL_CORE_COUNT >= 3U)
    &hwlcb_core2,
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 3U) */
#if (MP_CONTROL_CORE_COUNT >= 4U)
    &hwlcb_core3,
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 4U) */
#endif /* #if MP_CONTROL_CORE_COUNT == 1U */
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/* mcos_v850_sync_data_table[] */
volatile mcos_ringbuf_funit_t * const mcos_v850_sync_data_table[MP_CONTROL_CORE_COUNT] =
{
#if MP_CONTROL_CORE_COUNT == 1U
    NULL
#else   /* #if MP_CONTROL_CORE_COUNT == 1U */
    &sync_data_core0[0],
#if (MP_CONTROL_CORE_COUNT >= 2U)
    &sync_data_core1[0],
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 2U) */
#if (MP_CONTROL_CORE_COUNT >= 3U)
    &sync_data_core2[0],
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 3U) */
#if (MP_CONTROL_CORE_COUNT >= 4U)
    &sync_data_core3[0],
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 4U) */
#endif /* #if MP_CONTROL_CORE_COUNT == 1U */
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/* mcos_v850_async_data_table[] */
volatile mcos_ringbuf_uint8_t * const mcos_v850_async_data_table[MP_CONTROL_CORE_COUNT] =
{
#if MP_CONTROL_CORE_COUNT == 1U
    NULL
#else   /* #if MP_CONTROL_CORE_COUNT == 1U */
    &async_data_core0[0],
#if (MP_CONTROL_CORE_COUNT >= 2U)
    &async_data_core1[0],
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 2U) */
#if (MP_CONTROL_CORE_COUNT >= 3U)
    &async_data_core2[0],
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 3U) */
#if (MP_CONTROL_CORE_COUNT >= 4U)
    &async_data_core3[0],
#endif  /* #if (MP_CONTROL_CORE_COUNT >= 4U) */
#endif /* #if MP_CONTROL_CORE_COUNT == 1U */
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"


#if ((MCOS_CFG_DS_TIME_ENABLE != 0U) && (MCOS_TEST_DS_PRFM == MCOS_TEST_DS_PRFM_MODE_DETAILED))
#define OS_START_SEC_VAR_CLEARED_32
#include "Os_MemMap.h"
volatile uint32_t    mcos_v850_prfm_cnt[32];
#define OS_STOP_SEC_VAR_CLEARED_32
#include "Os_MemMap.h"
#endif /* #if ((MCOS_CFG_DS_TIME_ENABLE != 0U) && (MCOS_TEST_DS_PRFM == MCOS_TEST_DS_PRFM_MODE_DETAILED)) */
