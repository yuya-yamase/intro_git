/* Reg_ADC-r04-303 */
/************************************************************************************************/
/*																								*/
/*		ADC register definition (for RH850U2x)													*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
#include "Mcal_SpalCmn.h"
#include "Reg_Adc.h"

/*==============================================================================================*/
/*	prototypes																					*/
/*==============================================================================================*/

/*==============================================================================================*/
/*	defines / data types / structs / unions / macros											*/
/*==============================================================================================*/

/*==============================================================================================*/
/*	constants																					*/
/*==============================================================================================*/
#define ADC_START_SEC_CONST_UNSPECIFIED			/* ADC RODATA CONST UNSPECIFIED Section Start					*/
#include "Adc_MemMap.h"

volatile Reg_Adc_Type* const cpstReg_Adc[ADC_HWUNIT_NUM] = {
#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) 
	(&Reg_ADC0),
	(&Reg_ADC1),
	(&Reg_ADC2)

#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) 
	(&Reg_ADC0),
	(&Reg_ADC1),
	(&Reg_ADC2)
	#if ((MCAL_PKG_TARGET==MCAL_PKG_U2B24_468PIN)		\
	  || (MCAL_PKG_TARGET==MCAL_PKG_U2B24_373PIN)		\
	  || (MCAL_PKG_TARGET==MCAL_PKG_U2B20_468PIN)		\
	  || (MCAL_PKG_TARGET==MCAL_PKG_U2B20_373PIN)		\
	  || (MCAL_PKG_TARGET==MCAL_PKG_U2B10_468PIN)		\
	  || (MCAL_PKG_TARGET==MCAL_PKG_U2B10_373PIN))
	,(&Reg_ADC3)
	#endif
	#if ((MCAL_PKG_TARGET==MCAL_PKG_U2B24_468PIN)		\
	  || (MCAL_PKG_TARGET==MCAL_PKG_U2B24_373PIN)		\
	  || (MCAL_PKG_TARGET==MCAL_PKG_U2B20_468PIN)		\
	  || (MCAL_PKG_TARGET==MCAL_PKG_U2B20_373PIN))
	,(&Reg_ADCA)
	#endif
#endif
};
volatile Reg_Adc_SELB_Type* const cpstReg_SELB_Adc[ADC_SELB_MODULE_NUM] = {
	(&Reg_SELB)
};

/*
#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) 
volatile Reg_Air_Type* const cpstReg_AIR_Adc[ADC_AIR_MODULE_NUM] = {
	(&Reg_AIR)
};
#endif
*/
#define ADC_STOP_SEC_CONST_UNSPECIFIED			/* ADC RODATA CONST UNSPECIFIED Section Stop							*/
#include "Adc_MemMap.h"

/*-- End Of File -------------------------------------------------------------------------------*/
