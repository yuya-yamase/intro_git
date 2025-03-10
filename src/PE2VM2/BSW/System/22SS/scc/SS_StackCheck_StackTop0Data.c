/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_StackCheck_StackTop0Data.c
 * [Module]			StackCheck_StackTop0Data
 * [Function]		StackCheck_StackTop0Data
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
#include <SS_MemmapStackTop0_Env.h>

#include <SS_StackCheck_StackTop0Data.h>

/*----------------------------------------------------------------------------
 *		Variables
 *--------------------------------------------------------------------------*/
#if (SS_USE_STACK_BOUNDARYCHECK == STD_ON)
uint32 SS_StackCheck_u4StackTop_0;
#endif /* (SS_USE_STACK_BOUNDARYCHECK == STD_ON) */
#include <SS_MemmapSdaDisableE_Env.h>
