/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_StackCheck_StackBottom1Data.c
 * [Module]			StackCheck_StackBottom1Data
 * [Function]		StackCheck_StackBottom1Data
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
#include <SS_MemmapStackBottom1_Env.h>

#include <SS_StackCheck_StackBottom1Data.h>

/*----------------------------------------------------------------------------
 *		Variables
 *--------------------------------------------------------------------------*/
#if (SS_USE_CORE_COUNT >= 2u)
#if (SS_USE_STACK_BOUNDARYCHECK == STD_ON)
uint32 SS_StackCheck_u4StackBottom_1;
#endif /* (SS_USE_STACK_BOUNDARYCHECK == STD_ON) */
#endif /* (SS_USE_CORE_COUNT >= 2u) */
#include <SS_MemmapSdaDisableE_Env.h>
