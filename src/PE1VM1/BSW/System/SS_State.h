/*****************************************************************************
 *	Copyright DENSO Corporation and AUBASS Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]      SS_State.h
 * [Module]         System State Management
 * [Function]       SS_State
 * [Notes]          None
 ****************************************************************************/
#ifndef SS_STATE_H
#define SS_STATE_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <SS_TYPE.h>
#include <SS_Internal.h>

#if (SS_USE_MODE == STD_ON)
/*----------------------------------------------------------------------------
 *      Symbols
 *--------------------------------------------------------------------------*/

#define SS_MM_VIA_RESET         (0x01U)
#define SS_MM_VIA_DEEPSTOP      (0x02U)
#define SS_MM_VIA_STOP          (0x04U)
#define SS_MM_VIA_SLEEPCANCEL   (0x08U)
#define SS_MM_VIA_POSTRUNCANCEL (0x10U)

#define SS_MM_PRERUN_SUP (0xC33C3CC3UL)
#define SS_MM_PRERUN_WUP (0xA55A5AA5UL)
#define SS_MM_RUN        (0x5AA5A55AUL)
#define SS_MM_POSTRUN    (0x3CC3C33CUL)

#define SS_STATE_DO_RUNENTRY      (0x00000001U)
#define SS_STATE_DO_POSTRUNENTRY  (0x00000002U)
#define SS_STATE_DO_PRERUNENTRY   (0x00000004U)
#define SS_STATE_DO_PRERUNREENTRY (0x00000008U)
#define SS_STATE_DO_SLEEP         (0x00000040U)
#define SS_STATE_DO_SHUTDOWN      (0x00000080U)
#define SS_STATE_NOTDO_HOOK       (0x00000010U)
#define SS_STATE_ARBITRATE_ERROR  (0x00000020U)

#define SS_PM_TARGET_SHUTDOWN (0xA5A5A5A5UL)
#define SS_PM_TARGET_SLEEP    (0x5A5A5A5AUL)

/*----------------------------------------------------------------------------
 *		Types
 *--------------------------------------------------------------------------*/
typedef uint8  SS_Mm_viaType;
typedef uint32 SS_Mm_modeType;
typedef uint32 SS_Pm_shutdownTargetType;

/*----------------------------------------------------------------------------
 *      Prototypes
 *--------------------------------------------------------------------------*/
/* Inter Component Interface */

/* For Initialize */
void SS_State_init(SS_BootType u4_BootSource);

/* For App */
SS_Mm_modeType SS_Mm_getMode(void);
SS_Mm_viaType  SS_Mm_getPreRunSource(void);
void           SS_Mm_cancelShutdown(void);

#if (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC)
#if (SS_MM_USE_ASYNC_ARB == STD_OFF)
void SS_Mm_requestPreRun(void);
#endif /* (SS_MM_USE_ASYNC_ARB == STD_OFF) */
void SS_Mm_requestRun(void);
void SS_Mm_requestPostRun(void);
void SS_Mm_mainFunction(void);
#if (SS_MM_USE_ASYNC_ARB == STD_ON)
void SS_Mm_releasePreRun(void);
void SS_Mm_releaseRun(void);
void SS_Mm_releasePostRun(void);
#endif
#endif /* (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC) */

#if (SS_MM_ARBITRATION == SS_MM_ARBITRATION_EVENT)
void SS_Mm_releasePreRun(void);
void SS_Mm_releaseRun(void);
void SS_Mm_releasePostRun(void);
void SS_Mm_transit(void);
#endif

/*----------------------------------------------------------------------------
 *		Prototypes
 *--------------------------------------------------------------------------*/
#if (SS_USE_SHUTDOWN == STD_ON)
#if (SS_USE_SLEEP == STD_ON)
Std_ReturnType SS_Pm_selectShutdownTarget(SS_Pm_shutdownTargetType u4_target);
#endif /* (SS_USE_SLEEP == STD_ON) */
#endif /* (SS_USE_SHUTDOWN == STD_ON) */

#endif /* (SS_USE_MODE == STD_ON) */

#endif /* SS_STATE_H */
