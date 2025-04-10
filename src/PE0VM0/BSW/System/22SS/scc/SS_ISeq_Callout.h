/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_ISeq_Callout.h
 * [Module]			Initialize
 * [Function]		Initialize at change state
 * [Notes]			None
 ****************************************************************************/
#ifndef SS_ISEQ_CALLOUT_H
#define SS_ISEQ_CALLOUT_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <SS_TYPE.h>
#include <SS_Internal.h>

/*----------------------------------------------------------------------------
 *		Prototypes
 *--------------------------------------------------------------------------*/
void SS_Pm_preOsInitCallout(SS_BootType u4_BootSource);
void SS_Pm_postOsInitCallout(SS_BootType u4_BootSource);
void SS_Pm_preClockUpCallout(SS_BootType u4_BootSource);
void SS_Pm_postClockUpCallout(SS_BootType u4_BootSource);
#if (SS_USE_UP == STD_ON)
void SS_Pm_postStartOSCallout(SS_BootType u4_BootSource);
void SS_Pm_postRteStartCallout(SS_BootType u4_BootSource);
#endif /* (SS_USE_UP == STD_ON) */

#if (SS_USE_SLEEP == STD_ON)
#if (SS_USE_UP == STD_ON)
void SS_Pm_sleepCallout(void);
#endif /* (SS_USE_UP == STD_ON) */
void SS_Pm_wakeupCheckCallout(void);
void SS_Pm_reSleepCallout(void);
#endif /* (SS_USE_SLEEP == STD_ON) */

#if (SS_USE_UP == STD_ON)
void SS_Pm_DisableInterruptsCallout(SS_ShutdownReqSrcType u4_ReqSrc);
void SS_Pm_EnableInterruptsCallout(SS_ShutdownReqSrcType u4_ReqSrc);

#if (SS_USE_SHUTDOWN == STD_ON)
void SS_Pm_shutdownCallout(void);
#endif

#if (SS_USE_MODE == STD_OFF)
#if (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC)
void SS_Pm_preArbitrationCallout(void);
#endif
#endif
#endif /* (SS_USE_UP == STD_ON) */

#endif /* SS_ISEQ_CALLOUT_H */
