/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_RamTest_RamAreaBottom3Data.c
 * [Module]			RamTest_RamAreaBottom3Data
 * [Function]		RamTest_RamAreaBottom3Data
 * [Notes]			None
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_TYPE.h>
#include <SS_Internal.h>

#include <SS_MemmapSdaDisableB_Env.h>
#include <SS_MemmapProtect_Env.h>
#include <SS_MemmapRamAreaBottom3_Env.h>

#include <SS_RamTest_RamAreaBottom3Data.h>
#include <SS_RamTest.h>

/*----------------------------------------------------------------------------
 *		Variables
 *--------------------------------------------------------------------------*/
#if (SS_USE_ADDRBUSCHECK == STD_ON)
#if (SS_USE_CORE_COUNT >= 4u)
uint32 SS_AddrBusChk_u4RamAreaBottom_3;
#endif /* (SS_USE_CORE_COUNT >= 4u) */
#endif /* (SS_USE_ADDRBUSCHECK == STD_ON) */
#include <SS_MemmapSdaDisableE_Env.h>
