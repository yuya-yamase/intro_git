/*****************************************************************************
 *	Copyright DENSO Corporation and AUBASS Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]      SS_State_Callout.h
 * [Module]         System State Management
 * [Function]       SS_State
 * [Notes]          None
 ****************************************************************************/
#ifndef SS_STATE_CALLOUT_H
#define SS_STATE_CALLOUT_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_Internal.h>

/*----------------------------------------------------------------------------
 *      Prototypes
 *--------------------------------------------------------------------------*/
/* Hook */
#if (SS_USE_MODE == STD_ON)
void SS_Mm_entryRunCallout(void);
void SS_Mm_entryPostRunCallout(void);
void SS_Mm_entryPreRunCallout(void);
void SS_Mm_reEntryPreRunCallout(void);

#if (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC)
void SS_Mm_preArbitrationCallout(void);
#endif

#if (SS_USE_SLEEP == STD_ON)
void SS_Pm_sleepCheckCallout(void);
#endif /* (SS_USE_SLEEP == STD_ON) */

#endif /* (SS_USE_MODE == STD_ON) */

#endif /* SS_STATE_CALLOUT_H */
