/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_Error.h
 * [Module]			Error
 * [Function]		Error
 * [Notes]			None
 ****************************************************************************/

#ifndef SS_ERROR_H
#define SS_ERROR_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/
#define SS_ERROR_NONE       (0x5a5a5a5aUL) /*	Error Factor : No Error					*/
#define SS_ERROR_DATA       (0x00000001UL) /*	Error Factor : Data Error				*/
#define SS_ERROR_SCHEDULER  (0x00000004UL) /*	Error Factor : OS API Error				*/
#define SS_ERROR_STACKCHECK (0x00000010UL) /*	Error Factor : Stack Check Error		*/
#define SS_ERROR_SLEEP      (0x00000020UL) /*	Error Factor : Sleep Error				*/
#define SS_ERROR_CLOCK      (0x00000080UL) /*	Error Factor : Clock Error				*/
#define SS_ERROR_RAMTEST    (0x00000200UL) /*	Error Factor : RAM Test Error			*/
#define SS_ERROR_ROMTEST    (0x00000800UL) /*	Error Factor : ROM Test Error			*/

/*----------------------------------------------------------------------------
 *		Types
 *--------------------------------------------------------------------------*/
typedef uint32 SS_ErrorFactorType;

/*----------------------------------------------------------------------------
 *		Prototypes
 *--------------------------------------------------------------------------*/
void SS_Error_init(void);
void SS_Error_check(void);
void SS_Error_notify(SS_ErrorFactorType u4_Factor);
void SS_Error_setFactor(SS_ErrorFactorType u4_Factor);

extern SS_ErrorFactorType SS_Error_u4Factor;

#endif /* SS_ERROR_H */
