/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_StackCheck_StackTop2Data.h
 * [Module]			StackCheck_StackTop2Data
 * [Function]		StackCheck_StackTop2Data
 * [Notes]			None
 ****************************************************************************/

#ifndef SS_STACKCHECK_STACKTOP2DATA_H
#define SS_STACKCHECK_STACKTOP2DATA_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_Internal.h>

/*----------------------------------------------------------------------------
 *		Externs
 *--------------------------------------------------------------------------*/
#if (SS_USE_CORE_COUNT >= 3u)
#if (SS_USE_STACK_BOUNDARYCHECK == STD_ON)
extern uint32 SS_StackCheck_u4StackTop_2;
#endif /* (SS_USE_STACK_BOUNDARYCHECK == STD_ON) */
#endif /* (SS_USE_CORE_COUNT >= 3u) */

#endif /* SS_STACKCHECK_STACKTOP2DATA_H */
