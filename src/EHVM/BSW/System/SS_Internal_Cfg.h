/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_Internal_Cfg.h
 * [Module]			Configuration
 * [Function]		Configuration of SS internal
 * [Revision]		1.60
 * [Notes]			Customize file
 ****************************************************************************/

#ifndef SS_INTERNAL_CFG_H
#define SS_INTERNAL_CFG_H

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/

#define SS_USE_SLEEP      (STD_ON)  /* Use sleep */
#define SS_USE_MODE       (STD_OFF) /* Use mode */
#define SS_USE_SHUTDOWN   (STD_OFF) /* Use shutdown */
#define SS_USE_CORE_COUNT (4UL)     /* Use cores count */

#define SS_MM_ARBITRATION_PERIODIC (0xA5A5A5A5UL)               /* Arbitration periodic */
#define SS_MM_ARBITRATION_EVENT    (0x5A5A5A5AUL)               /* Arbitration event */
#define SS_MM_ARBITRATION          (SS_MM_ARBITRATION_PERIODIC) /* Select Arbitration */
#define SS_MM_USE_ASYNC_ARB        (STD_OFF)                    /* 非同期状態遷移 */
#define SS_MM_u4ASYNC_WAIT_UP      (5UL)                        /* 非同期状態遷移の調停用待ち周回数 */

/* RAM Test */
#define SS_USE_STACK_BOUNDARYCHECK (STD_OFF) /* Use stack boundary check */
#define SS_USE_PRISTACKCHECK       (STD_OFF) /* Use primary stack check */

/* Memory */
#define SS_u4PRIMARYSTACKSIZE_0 (256UL)        /* PrimaryStack size Core0 */
#define SS_u4PRIMARYSTACKSIZE_1 (256UL)        /* PrimaryStack size Core1 */
#define SS_u4PRIMARYSTACKSIZE_2 (256UL)        /* PrimaryStack size Core2 */
#define SS_u4PRIMARYSTACKSIZE_3 (256UL)        /* PrimaryStack size Core3 */
#define SS_STACKSIZE_0          (2048UL)       /* stack size */
#define SS_STACKSIZE_1          (2048UL)       /* stack size */
#define SS_STACKSIZE_2          (2048UL)       /* stack size */
#define SS_STACKSIZE_3          (2048UL)       /* stack size */
#define SS_STACKINITVAL         (0x00000000UL) /* Main/Primary stack initial value */

/* SleepTm */
#define SS_SLEEPTM_u4SLEEPTIME_MAX (3600000UL) /* Sleep time max (LSB 1ms) */

#define SS_USE_INTERNAL_CALLTRUSTED_B (STD_OFF)
#define SS_USE_INTERNAL_CALLTRUSTED_C (STD_OFF)

/* RTE */
#define SS_INTG_RTE (STD_OFF) /* Call Rte_start */

/* for Aubist */
#define SS_INTG_VC      (1UL)
#define SS_INTG_AB      (2UL)
#define SS_INTG_RE_OS   (3UL)
#define SS_INTG_ASR_PKG (SS_INTG_VC)

#define SS_USE_UP (STD_OFF)

/* Memory size check */
#if (SS_u4PRIMARYSTACKSIZE_0 % 4u == 0u)
/* 4nになってるので、OK */
#else
#error "SS_u4PRIMARYSTACKSIZE_0 is not 4n Aligned"
#endif
#if (SS_u4PRIMARYSTACKSIZE_1 % 4u == 0u)
/* 4nになってるので、OK */
#else
#error "SS_u4PRIMARYSTACKSIZE_1 is not 4n Aligned"
#endif
#if (SS_u4PRIMARYSTACKSIZE_2 % 4u == 0u)
/* 4nになってるので、OK */
#else
#error "SS_u4PRIMARYSTACKSIZE_2 is not 4n Aligned"
#endif
#if (SS_u4PRIMARYSTACKSIZE_3 % 4u == 0u)
/* 4nになってるので、OK */
#else
#error "SS_u4PRIMARYSTACKSIZE_3 is not 4n Aligned"
#endif
#if (SS_STACKSIZE_0 % 4u == 0u)
/* 4nになってるので、OK */
#else
#error "SS_STACKSIZE_0 is not 4n Aligned"
#endif
#if (SS_STACKSIZE_1 % 4u == 0u)
/* 4nになってるので、OK */
#else
#error "SS_STACKSIZE_1 is not 4n Aligned"
#endif
#if (SS_STACKSIZE_2 % 4u == 0u)
/* 4nになってるので、OK */
#else
#error "SS_STACKSIZE_2 is not 4n Aligned"
#endif
#if (SS_STACKSIZE_3 % 4u == 0u)
/* 4nになってるので、OK */
#else
#error "SS_STACKSIZE_3 is not 4n Aligned"
#endif

#endif /* SS_INTERNAL_CFG_H */
