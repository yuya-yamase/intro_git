/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_Error_Callout.h
 * [Module]			Error
 * [Function]		Error
 * [Notes]			None
 ****************************************************************************/

#ifndef SS_ERROR_CALLOUT_H
#define SS_ERROR_CALLOUT_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <SS_Error.h>

/*----------------------------------------------------------------------------
 *		Prototypes
 *--------------------------------------------------------------------------*/
void SS_Error_bSyncCallout(SS_ErrorFactorType u4_Factor);
void SS_Error_immCallout(SS_ErrorFactorType u4_Factor);
void SS_Error_ResetCallout(void);

#endif /* SS_ERROR_CALLOUT_H */
