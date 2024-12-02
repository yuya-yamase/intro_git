/* Common-r04-r04-307 */
/************************************************************************************************/
/*																								*/
/*		McalCommon_lib(Timer)																*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/
#ifndef	MCALCOMMONPRESCALER_H
#define	MCALCOMMONPRESCALER_H

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include	"Std_Types.h"

/*==============================================================================================*/
/* defines																						*/
/*==============================================================================================*/

/*==============================================================================================*/
/* data types / structs / unions / macros														*/
/*==============================================================================================*/
/* unit types */
typedef enum {
	MCALCOMMON_UNIT_TAUD0 = 0U,
	MCALCOMMON_UNIT_TAUD1,
	MCALCOMMON_UNIT_TAUD2,
	MCALCOMMON_UNIT_TAUD3,
	MCALCOMMON_UNIT_TAUJ0,
	MCALCOMMON_UNIT_TAUJ1,
	MCALCOMMON_UNIT_TAUJ2,
	MCALCOMMON_UNIT_TAUJ3,
	MCALCOMMON_UNIT_MAX
} Mcalcommon_PsUnit;

/* Prescaler types */
typedef enum {
	MCALCOMMON_PS_CK0 = 0U,
	MCALCOMMON_PS_CK1,
	MCALCOMMON_PS_CK2,
	MCALCOMMON_PS_CK3_PRE,
	MCALCOMMON_PS_CK3_BRS
} Mcalcommon_PsType;

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
#define MCALCOMMON_START_SEC_CODE_GLOBAL
#include "McalCommon_MemMap.h"
/************************************************************************************************/
/* Service name		:	mcalcommon_SetPrescalerCfgVal											*/
/* Reentrancy		:	Non-Reentrant															*/
/* Parameters(in)	:	t_enUnit : unit															*/
/* Parameters(in)	:	t_enType : Prescale type												*/
/* Parameters(in)	:	t_u1Value : set value													*/
/* Return value		:	none																	*/
/* Limitation		:	none																	*/
/************************************************************************************************/
FUNC(void, MCALCOMMON_CODE) mcalcommon_SetPrescalerCfgVal(
	VAR(Mcalcommon_PsUnit, AUTOMATIC)	t_enUnit,
	VAR(Mcalcommon_PsType, AUTOMATIC)	t_enType,
	VAR(uint8, AUTOMATIC)				t_u1Value);

/************************************************************************************************/
/* Service name		:	mcalcommon_GetPrescalerCfgVal											*/
/* Reentrancy		:	Reentrant																*/
/* Parameters(in)	:	t_enUnit : unit															*/
/* Parameters(in)	:	t_enType : Prescale type												*/
/* Return value		:	Prescale value															*/
/* Limitation		:	none																	*/
/************************************************************************************************/
FUNC(uint8, MCALCOMMON_CODE) mcalcommon_GetPrescalerCfgVal(
	VAR(Mcalcommon_PsUnit, AUTOMATIC)	t_enUnit,
	VAR(Mcalcommon_PsType, AUTOMATIC)	t_enType);

#define MCALCOMMON_STOP_SEC_CODE_GLOBAL
#include "McalCommon_MemMap.h"

#endif	/* MCALCOMMONPRESCALER_H */
/*-- End Of File -------------------------------------------------------------------------------*/
