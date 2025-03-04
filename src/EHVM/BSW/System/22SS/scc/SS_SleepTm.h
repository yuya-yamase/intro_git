/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_SleepTm.h
 * [Module]			SleepTm
 * [Function]		SleepTm
 * [Notes]			None
 ****************************************************************************/

#ifndef SS_SLEEPTM_H
#define SS_SLEEPTM_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_Internal.h>

/*----------------------------------------------------------------------------
 *		Prototypes
 *--------------------------------------------------------------------------*/
#if (SS_USE_SLEEP == STD_ON)
Std_ReturnType SS_SleepTm_start(uint32 u4_RealTime);
void           SS_SleepTm_stop(void);
boolean        SS_SleepTm_isUp(void);
Std_ReturnType SS_SleepTm_resetUp(void);
Std_ReturnType SS_SleepTm_getTime(uint32 *pt_RealTime);
#endif /* (SS_USE_SLEEP == STD_ON) */

#endif /* SS_SLEEPTM_H */
