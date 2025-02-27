/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_StackCheck_StackTop3Data.c
 * [Module]			StackCheck_StackTop3Data
 * [Function]		StackCheck_StackTop3Data
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
#include <SS_MemmapStackTop3_Env.h>

#include <SS_StackCheck_StackTop3Data.h>

/*----------------------------------------------------------------------------
 *		Variables
 *--------------------------------------------------------------------------*/
#if (SS_USE_CORE_COUNT >= 4u)
#if (SS_USE_STACK_BOUNDARYCHECK == STD_ON)
uint32 SS_StackCheck_u4StackTop_3;
#endif /* (SS_USE_STACK_BOUNDARYCHECK == STD_ON) */
#endif /* (SS_USE_CORE_COUNT >= 4u) */
#include <SS_MemmapSdaDisableE_Env.h>
