/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		StackCheck.h
 * [Module]			StackCheck
 * [Function]		StackCheck
 * [Notes]			None
 ****************************************************************************/

#ifndef SS_STACKCHECK_H
#define SS_STACKCHECK_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_Internal.h>

/*----------------------------------------------------------------------------
 *		Prototypes
 *--------------------------------------------------------------------------*/
#if (SS_USE_STACK_BOUNDARYCHECK == STD_ON)
void SS_StackCheck_init(void);
void SS_StackCheck_exec(void);
#endif /* (SS_USE_STACK_BOUNDARYCHECK == STD_ON) */

#endif /* SS_STACKCHECK_H */
