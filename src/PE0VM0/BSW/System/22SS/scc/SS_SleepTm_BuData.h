/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_SleepTm_BuData.h
 * [Module]			SleepTm
 * [Function]		Sleep Timer
 * [Notes]			None
 ****************************************************************************/

#ifndef SS_SLEEPTM_BUDATA_H
#define SS_SLEEPTM_BUDATA_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_Internal.h>

/*----------------------------------------------------------------------------
 *		Externs
 *--------------------------------------------------------------------------*/

#if (SS_USE_SLEEP == STD_ON)
extern uint32 SS_SleepTm_u4AlarmPeriod;
extern uint32 SS_SleepTm_u4AlarmPeriodBkUp;
extern uint32 SS_SleepTm_u4ElapsedTime;
extern uint32 SS_SleepTm_u4ElapsedTimeBkUp;
#endif /* (SS_USE_SLEEP == STD_ON) */

#endif /* SS_SLEEPTM_BUDATA_H */
