/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_StackCheck_StackBottom0Data.h
 * [Module]			StackCheck_StackBottom0Data
 * [Function]		StackCheck_StackBottom0Data
 * [Notes]			None
 ****************************************************************************/

#ifndef SS_STACKCHECK_STACKBOTTOM0DATA_H
#define SS_STACKCHECK_STACKBOTTOM0DATA_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_Internal.h>

/*----------------------------------------------------------------------------
 *		Externs
 *--------------------------------------------------------------------------*/
#if (SS_USE_STACK_BOUNDARYCHECK == STD_ON)
extern uint32 SS_StackCheck_u4StackBottom_0;
#endif /* (SS_USE_STACK_BOUNDARYCHECK == STD_ON) */

#endif /* SS_STACKCHECK_STACKBOTTOM0DATA_H */
