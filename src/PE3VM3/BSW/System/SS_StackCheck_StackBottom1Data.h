/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_StackCheck_StackBottom1Data.h
 * [Module]			StackCheck_StackBottom1Data
 * [Function]		StackCheck_StackBottom1Data
 * [Notes]			None
 ****************************************************************************/

#ifndef SS_STACKCHECK_STACKBOTTOM1DATA_H
#define SS_STACKCHECK_STACKBOTTOM1DATA_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_Internal.h>

/*----------------------------------------------------------------------------
 *		Externs
 *--------------------------------------------------------------------------*/
#if (SS_USE_CORE_COUNT >= 2u)
#if (SS_USE_STACK_BOUNDARYCHECK == STD_ON)
extern uint32 SS_StackCheck_u4StackBottom_1;
#endif /* (SS_USE_STACK_BOUNDARYCHECK == STD_ON) */
#endif /* (SS_USE_CORE_COUNT >= 2u) */

#endif /* SS_STACKCHECK_STACKBOTTOM1DATA_H */
