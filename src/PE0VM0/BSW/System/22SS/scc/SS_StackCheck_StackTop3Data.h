/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_StackCheck_StackTop3Data.h
 * [Module]			StackCheck_StackTop3Data
 * [Function]		StackCheck_StackTop3Data
 * [Notes]			None
 ****************************************************************************/

#ifndef SS_STACKCHECK_STACKTOP3DATA_H
#define SS_STACKCHECK_STACKTOP3DATA_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_Internal.h>

/*----------------------------------------------------------------------------
 *		Externs
 *--------------------------------------------------------------------------*/
#if (SS_USE_CORE_COUNT >= 4u)
#if (SS_USE_STACK_BOUNDARYCHECK == STD_ON)
extern uint32 SS_StackCheck_u4StackTop_3;
#endif /* (SS_USE_STACK_BOUNDARYCHECK == STD_ON) */
#endif /* (SS_USE_CORE_COUNT >= 4u) */

#endif /* SS_STACKCHECK_STACKTOP3DATA_H */
