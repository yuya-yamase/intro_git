/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_SleepTm_BuData.c
 * [Module]			SleepTm
 * [Function]		Sleep Timer
 * [Notes]			None
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_TYPE.h>
#include <SS_Internal.h>

#include <SS_MemmapSdaDisableB_Env.h>
#include <SS_Memmap_Env.h>
#include <SS_MemmapBu_Env.h> /* Backup RAM に配置 */

#include <SS_SleepTm_BuData.h>

/*----------------------------------------------------------------------------
 *		Variables
 *--------------------------------------------------------------------------*/

#if (SS_USE_SLEEP == STD_ON)

uint32 SS_SleepTm_u4AlarmPeriod;
uint32 SS_SleepTm_u4AlarmPeriodBkUp;
uint32 SS_SleepTm_u4ElapsedTime;
uint32 SS_SleepTm_u4ElapsedTimeBkUp;

#endif /* (SS_USE_SLEEP == STD_ON) */

#include <SS_MemmapSdaDisableE_Env.h>
