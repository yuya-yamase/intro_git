/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_StackCheck_StackTop2Data.c
 * [Module]			StackCheck_StackTop2Data
 * [Function]		StackCheck_StackTop2Data
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
#include <SS_MemmapStackTop2_Env.h>

#include <SS_StackCheck_StackTop2Data.h>

/*----------------------------------------------------------------------------
 *		Variables
 *--------------------------------------------------------------------------*/
#if (SS_USE_CORE_COUNT >= 3u)
#if (SS_USE_STACK_BOUNDARYCHECK == STD_ON)
uint32 SS_StackCheck_u4StackTop_2;
#endif /* (SS_USE_STACK_BOUNDARYCHECK == STD_ON) */
#endif /* (SS_USE_CORE_COUNT >= 3u) */
#include <SS_MemmapSdaDisableE_Env.h>
