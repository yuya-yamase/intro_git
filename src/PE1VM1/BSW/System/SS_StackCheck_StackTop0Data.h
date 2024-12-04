/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_StackCheck_StackTop0Data.h
 * [Module]			StackCheck_StackTop0Data
 * [Function]		StackCheck_StackTop0Data
 * [Notes]			None
 ****************************************************************************/

#ifndef SS_STACKCHECK_STACKTOP0DATA_H
#define SS_STACKCHECK_STACKTOP0DATA_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_Internal.h>

/*----------------------------------------------------------------------------
 *		Externs
 *--------------------------------------------------------------------------*/
#if (SS_USE_STACK_BOUNDARYCHECK == STD_ON)
extern uint32 SS_StackCheck_u4StackTop_0;
#endif /* (SS_USE_STACK_BOUNDARYCHECK == STD_ON) */

#endif /* SS_STACKCHECK_STACKTOP0DATA_H */
