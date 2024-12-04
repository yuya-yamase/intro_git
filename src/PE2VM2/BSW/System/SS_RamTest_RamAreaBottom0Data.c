/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_RamTest_RamAreaBottom0Data.c
 * [Module]			RamTest_RamAreaBottom0Data
 * [Function]		RamTest_RamAreaBottom0Data
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
#include <SS_MemmapRamAreaBottom0_Env.h>

#include <SS_RamTest_RamAreaBottom0Data.h>
#include <SS_RamTest.h>

/*----------------------------------------------------------------------------
 *		Variables
 *--------------------------------------------------------------------------*/
#if (SS_USE_ADDRBUSCHECK == STD_ON)
uint32 SS_AddrBusChk_u4RamAreaBottom_0;
#endif /* (SS_USE_ADDRBUSCHECK == STD_ON) */
#include <SS_MemmapSdaDisableE_Env.h>
