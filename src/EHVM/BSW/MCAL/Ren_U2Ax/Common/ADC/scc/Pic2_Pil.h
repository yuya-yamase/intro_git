/* PIC2-r04-303 */
/************************************************************************************************/
/*																								*/
/*		PIC2 Driver : Low Driver layer for RH850U2A/U2B											*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/
#ifndef PIC2_PIL_H
#define PIC2_PIL_H

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
#include "Std_Types.h"
#include "Mcal_SpalCmn.h"

#include "Adc.h"

/*==============================================================================================*/
/*	defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
#define ADC_START_SEC_CODE_GLOBAL
#include "Adc_MemMap.h"
/*----------------------------------------------------------------------------------------------*/
/*	API Functions																				*/
/*----------------------------------------------------------------------------------------------*/

/************************************************************************************************/
/* Service name			: Pic2_Pil_Init															*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: None																	*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Initializes the PIC2 hardware units and driver.						*/
/************************************************************************************************/
FUNC(void, PIC2_CODE) Pic2_Pil_Init(void);

/************************************************************************************************/
/* Service name			: Pic2_Pil_SetHardwareTrigger											*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/* 		Adc_HWUnitType	: HW Unit Number														*/
/* 		Adc_SGType		: Scan Group Number														*/
/*		Pic20TSEL		: ADC Trigger Selection (PIC20)											*/
/*		Pic21TSEL		: ADC Trigger Selection (PIC21)											*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Set HW Trigger (TRGMD)												*/
/************************************************************************************************/
#if (ADC_CFG_HW_TRG_API==STD_ON)
FUNC(void, PIC2_CODE) Pic2_Pil_SetHardwareTrigger(
	CONST(Adc_HWUnitType,	PIC2_CONST)	t_cudHWUnit,
	CONST(Adc_SGType,		PIC2_CONST)	t_cudSG,
	CONST(uint32,			PIC2_CONST)	t_cu4Pi20TSEL
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
   ,CONST(uint32,			PIC2_CONST)	t_cu4Pi21TSEL
	#endif
);
#endif

#if (ADC_CFG_REG_CHK==STD_ON)
/************************************************************************************************/
/* Service name			: Pic2_Pil_Regchk_All													*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Reentrant																*/
/* Parameters (in)		: None																	*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: uint32																*/
/* 		ADC_REGCHK_OK					: No Error detected										*/
/* 		ADC_REGCHK_NG					: Error detected										*/
/*		(following is availabel when ADC_CFG_REG_REFRESH is STD_ON)								*/
/* 		ADC_REGCHK_REFRESH_SUCCESS		: Error detected but refresh is success					*/
/* 		ADC_REGCHK_REFRESH_IMPOSSIBLE	: Error detected for unrefreshable register	 			*/
/* 		ADC_REGCHK_REFRESH_FAILED		: Error detected and refresh failed			 			*/
/* Description			: Check Group rerated registers and refresh ones w expected value.		*/
/************************************************************************************************/
FUNC(uint32, ADC_CODE) Pic2_Pil_Regchk_All(void);

/************************************************************************************************/
/* Service name			: Pic2_Pil_Regchk_Grp													*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: uint32																*/
/* 		ADC_REGCHK_OK					: No Error detected										*/
/* 		ADC_REGCHK_NG					: Error detected										*/
/*		(following is availabel when ADC_CFG_REG_REFRESH is STD_ON)								*/
/* 		ADC_REGCHK_REFRESH_SUCCESS		: Error detected but refresh is success					*/
/* 		ADC_REGCHK_REFRESH_IMPOSSIBLE	: Error detected for unrefreshable register	 			*/
/* 		ADC_REGCHK_REFRESH_FAILED		: Error detected and refresh failed			 			*/
/* Description			: Check Group rerated registers and refresh ones w expected value.		*/
/************************************************************************************************/
FUNC(uint32, ADC_CODE) Pic2_Pil_Regchk_Grp(
	CONST(Adc_GroupType,	ADC_CONST)	t_cudGrp
);
#endif

#define ADC_STOP_SEC_CODE_GLOBAL
#include "Adc_MemMap.h"

#endif
/*-- End Of File -------------------------------------------------------------------------------*/
