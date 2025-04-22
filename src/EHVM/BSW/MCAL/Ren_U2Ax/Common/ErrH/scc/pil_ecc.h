/* pil_ecc_r04-3000-0000-a-v03 */
/************************************************************************************************/
/*																								*/
/*		PIL ECC Driver																			*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#if 0 // zantei MPU‚Í2ŒŽ––”ñ‘Î‰ž

#ifndef PIL_ECC_H
#define PIL_ECC_H

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include	"ErrH_mcu_def.h"

/*==============================================================================================*/
/* defines / data types / structs / unions / macros												*/
/*==============================================================================================*/

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
/*----------------------------------------------------------------------------------------------*/
/* API Functions																				*/
/*----------------------------------------------------------------------------------------------*/
/************************************************************************************************/
/* Service name		:	Local RAM Ecc Fatal Error Status Clear Function(Core0)					*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(inout):	None																	*/
/* Return value		:	None																	*/
/* Caveats			:	None																	*/
/************************************************************************************************/
void	Pil_Ecc_ClearLramPe0EccFatalErrorStatus( void );

/************************************************************************************************/
/* Service name		:	Local RAM Ecc Fatal Error Status Clear Function(Core1)					*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(inout):	None																	*/
/* Return value		:	None																	*/
/* Caveats			:	None																	*/
/************************************************************************************************/
void	Pil_Ecc_ClearLramPe1EccFatalErrorStatus( void );

#if ( MCU_CORE_NUM > MCU_DUALCORE )
/************************************************************************************************/
/* Service name		:	Local RAM Ecc Fatal Error Status Clear Function(Core2)					*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(inout):	None																	*/
/* Return value		:	None																	*/
/* Caveats			:	None																	*/
/************************************************************************************************/
void	Pil_Ecc_ClearLramPe2EccFatalErrorStatus( void );
#endif

#if ( MCU_CORE_NUM > MCU_TRIPLECORE )
/************************************************************************************************/
/* Service name		:	Local RAM Ecc Fatal Error Status Clear Function(Core3)					*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(inout):	None																	*/
/* Return value		:	None																	*/
/* Caveats			:	None																	*/
/************************************************************************************************/
void	Pil_Ecc_ClearLramPe3EccFatalErrorStatus( void );
#endif

/************************************************************************************************/
/* Service name		:	Cluster RAM Ecc Fatal Error Status Clear Function						*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(inout):	None																	*/
/* Return value		:	None																	*/
/* Caveats			:	None																	*/
/************************************************************************************************/
void	Pil_Ecc_ClearCramEccFatalErrorStatus( void );

/************************************************************************************************/
/* Service name		:	Cluster RAM Ecc Fatal Error Status Get Function							*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(inout):	None																	*/
/* Return value		:	Error Detect Status(=0:not error detect, !=0:error detect)				*/
/* Caveats			:	None																	*/
/************************************************************************************************/
ZORN	Pil_Ecc_GetCramEccFatalErrorStatus( void );

/*----------------------------------------------------------------------------------------------*/
/* Scheduled / Event Functions																	*/
/*----------------------------------------------------------------------------------------------*/

#endif /* PIL_ECC_H */

#endif // zantei MPU‚Í2ŒŽ––”ñ‘Î‰ž

/*-- End Of File -------------------------------------------------------------------------------*/
