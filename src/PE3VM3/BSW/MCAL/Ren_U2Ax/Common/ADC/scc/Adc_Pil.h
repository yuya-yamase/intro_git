/* ADC-r04-303 */
/************************************************************************************************/
/*																								*/
/*		ADC Driver : Low Driver layer for RH850U2A/U2B											*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/
#ifndef ADC_PIL_H
#define ADC_PIL_H

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
/* Service name			: Adc_Pil_Init															*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: None																	*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Initializes the ADC hardware units and driver.						*/
/************************************************************************************************/
FUNC(void, ADC_CODE) Adc_Pil_Init(void);

/************************************************************************************************/
/* Service name			: Adc_Pil_StartConversion												*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/* 		Adc_HWUnitType	: HW Unit Number														*/
/* 		Adc_SGType		: Scan Group Number														*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Starts the conversion of all channels of the requested 				*/
/************************************************************************************************/
#if (ADC_CFG_START_STOP_GRP_API==STD_ON)
FUNC(void, ADC_CODE) Adc_Pil_StartConversion(
	CONST(Adc_HWUnitType,	ADC_CONST) t_cudHWUnit,
	CONST(Adc_SGType,		ADC_CONST) t_cudSG
);
#endif

/************************************************************************************************/
/* Service name			: Adc_Pil_StopGroupConversion											*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/* 		Adc_HWUnitType	: HW Unit Number														*/
/* 		Adc_SGType		: Scan Group Number														*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Stops the conversion of the requested ADC Channel group.				*/
/************************************************************************************************/
#if ((ADC_CFG_START_STOP_GRP_API==STD_ON) || (ADC_CFG_HW_TRG_API==STD_ON))
FUNC(void, ADC_CODE) Adc_Pil_StopGroupConversion(
	CONST(Adc_HWUnitType,	ADC_CONST)	t_cudHWUnit,
	CONST(Adc_SGType,		ADC_CONST)	t_cudSG
);
#endif

/************************************************************************************************/
/* Service name			: Adc_Pil_SetCnvEndIntrpt												*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/* 		Adc_HWUnitType	: HW Unit Number														*/
/* 		Adc_SGType		: Scan Group Number														*/
/*		IntrptUse		: STD_ON : Interrupt use,			STD_OFF : Interrupt not use			*/
/*		DMA				: STD_ON : DMA use,					STD_OFF : DMA not use				*/
/*		StreamingAcces	: STD_ON : Streaming Access mode,	STD_OFF : Single Access mode		*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Set Group Conversion End interrupt(ADIE)								*/
/************************************************************************************************/
#if ((ADC_CFG_START_STOP_GRP_API==STD_ON) || (ADC_CFG_READ_GRP_API==STD_ON) || (ADC_CFG_HW_TRG_API==STD_ON))
FUNC(void, ADC_CODE) Adc_Pil_SetCnvEndIntrpt(
	CONST(Adc_HWUnitType,	ADC_CONST)	t_cudHWUnit,
	CONST(Adc_SGType,		ADC_CONST)	t_cudSG,
	CONST(uint8,			ADC_CONST)	t_cu1IntrptUse,
	CONST(uint8,			ADC_CONST)	t_cu1DMA,
	CONST(uint8,			ADC_CONST)	t_cu1StreamingAcces
);
#endif

/************************************************************************************************/
/* Service name			: Adc_Pil_GetCnvData													*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/* 		Adc_HWUnitType	: HW Unit Number														*/
/* 		Adc_SGType		: Scan Group Number														*/
/* 		uint16			: convert channel size													*/
/* Parameters (inout)	: 																		*/
/*		DataBufferPtr	: Sync: pointer to result data buffer									*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Reads the group conversion result 									*/
/************************************************************************************************/
#if (ADC_CFG_READ_GRP_API==STD_ON)
FUNC(void, ADC_CODE) Adc_Pil_GetCnvData(
	CONST(Adc_HWUnitType,					ADC_CONST)		t_cudHWUnit,
	CONST(Adc_SGType,						ADC_CONST)		t_cudSG,
	CONST(uint16,							ADC_CONST)		t_cu2CnvChSize,
	P2VAR(Adc_ValueGroupType,	AUTOMATIC,	ADC_VAR_INIT)	t_pudDataBuffer
);
#endif

/************************************************************************************************/
/* Service name			: Adc_Pil_IsCnvCompleted												*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/* 		Adc_HWUnitType	: HW Unit Number														*/
/* 		Adc_SGType		: Scan Group Number														*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: conversion status														*/
/*		TRUE			: complete																*/
/*		FALSE			: progressing															*/
/* Description			: Get the group conversion status (only not use DMA)					*/
/************************************************************************************************/
FUNC(boolean, ADC_CODE) Adc_Pil_IsCnvCompleted(
	CONST(Adc_HWUnitType,	ADC_CONST)	t_cudHWUnit,
	CONST(Adc_SGType,		ADC_CONST)	t_cudSG
);

/************************************************************************************************/
/* Service name			: Adc_Pil_SetHardwareTrigger											*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/* 		Adc_HWUnitType	: HW Unit Number														*/
/* 		Adc_SGType		: Scan Group Number														*/
/* 		boolean			: TRUE:HW Trigger on ,FALSE:HW Trigger off								*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Set  HW Trigger (TRGMD)												*/
/************************************************************************************************/
#if (ADC_CFG_HW_TRG_API==STD_ON)
FUNC(void, ADC_CODE) Adc_Pil_SetHardwareTrigger(
	CONST(Adc_HWUnitType,	ADC_CONST)	t_cudHWUnit,
	CONST(Adc_SGType,		ADC_CONST)	t_cudSG,
	CONST(boolean,			ADC_CONST)	t_cblisHWTriggerOn
);
#endif

/************************************************************************************************/
/* Service name			: Adc_Pil_ClearDIR														*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/* 		Adc_HWUnitType	: HW Unit Number														*/
/* 		Adc_SGType		: Scan Group Number														*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Clear Data Supplementary Information Register							*/
/************************************************************************************************/
#if ((ADC_CFG_START_STOP_GRP_API==STD_ON) || (ADC_CFG_HW_TRG_API==STD_ON))
FUNC(void, ADC_CODE) Adc_Pil_ClearDIR(
	CONST(Adc_HWUnitType,	ADC_CONST)	t_cudHWUnit,
	CONST(Adc_SGType,		ADC_CONST)	t_cudSG
);
#endif

/************************************************************************************************/
/* Service name			: Adc_Pil_DisableSGHWTrigger											*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: None																	*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Disable all Scan Group HW Trigger (call by DeInit only)				*/
/************************************************************************************************/
#if (ADC_CFG_DEINIT_API==STD_ON)
FUNC(void, ADC_CODE) Adc_Pil_DisableSGHWTrigger(void);
#endif

/************************************************************************************************/
/* Service name			: Adc_Pil_GetDRAdr														*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/* 		Adc_HWUnitType	: HW Unit Number														*/
/* 		Adc_SGType		: Scan Group Number														*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: DR register adress													*/
/* Description			: get the start data register address									*/
/************************************************************************************************/
#ifdef ADC_USE_DMA
volatile FUNC_P2VAR(uint16, AUTOMATIC, ADC_CODE) Adc_Pil_GetDRAdr(
	CONST(Adc_HWUnitType,	ADC_CONST)	t_cudHWUnit,
	CONST(Adc_SGType,		ADC_CONST)	t_cudSG
);
#endif

/************************************************************************************************/
/* Service name			: Adc_Pil_StartTrackHold												*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/* 		Adc_HWUnitType			: HW Unit Number												*/
/*		Adc_TrackHoldGroupType	: Track and Hold Group (Grp A/Grp B)							*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Start Track & Hold Sampling											*/
/************************************************************************************************/
#ifdef ADC_USE_TH
FUNC(void, ADC_CODE) Adc_Pil_StartTrackHold(
	CONST(Adc_HWUnitType,			ADC_CONST)	t_cudHWUnit,
	CONST(Adc_TrackHoldGroupType,	ADC_CONST)	t_cudTHGrp
);
#endif

/************************************************************************************************/
/* Service name			: Adc_Pil_StopTrackHold													*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/* 		Adc_HWUnitType			: HW Unit Number												*/
/*		Adc_TrackHoldGroupType	: Track and Hold Group (Grp A/Grp B)							*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Stop Track & Hold Sampling											*/
/************************************************************************************************/
#ifdef ADC_USE_TH
FUNC(void, ADC_CODE) Adc_Pil_StopTrackHold(
	CONST(Adc_HWUnitType,			ADC_CONST)	t_cudHWUnit,
	CONST(Adc_TrackHoldGroupType,	ADC_CONST)	t_cudTHGrp
);
#endif

/************************************************************************************************/
/* Service name			: Adc_Pil_DisableAllTHTrigger											*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: None																	*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Disable Track & Hold Trigger (call by DeInit only)					*/
/************************************************************************************************/
#if (ADC_CFG_DEINIT_API==STD_ON)
#ifdef ADC_USE_TH
FUNC(void, ADC_CODE) Adc_Pil_DisableAllTHTrigger(void);
#endif
#endif

/************************************************************************************************/
/* Service name			: Adc_Pil_StopAllTrackHold												*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: None																	*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Stop Track & Hold Sampling (call by DeInit only)						*/
/************************************************************************************************/
#if (ADC_CFG_DEINIT_API==STD_ON)
#ifdef ADC_USE_TH
FUNC(void, ADC_CODE) Adc_Pil_StopAllTrackHold(void);
#endif
#endif

/************************************************************************************************/
/* Service name			: Adc_Pil_DisableAllTHOperation											*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: None																	*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Stop Track & Hold Sampling (call by DeInit only)						*/
/************************************************************************************************/
#if (ADC_CFG_DEINIT_API==STD_ON)
#ifdef ADC_USE_TH
FUNC(void, ADC_CODE) Adc_Pil_DisableAllTHOperation(void);
#endif
#endif

/************************************************************************************************/
/* Service name			: Adc_Pil_ForcedTermination												*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: None																	*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: forcibly terminate and initialize (call by DeInit only)				*/
/************************************************************************************************/
#if (ADC_CFG_DEINIT_API==STD_ON)
FUNC(void, ADC_CODE) Adc_Pil_ForcedTermination(void);
#endif

/*--------------------------------------------------------------------------*/
/* only register check is  available										*/
/*--------------------------------------------------------------------------*/
#if (ADC_CFG_REG_CHK==STD_ON)
/************************************************************************************************/
/* Service name			: Adc_Pil_Regchk_All													*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Reentrant																*/
/* Parameters (in)		: None																	*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: uint32																*/
/* 		ADC_REGCHK_OK					: No Error detected										*/
/* 		ADC_REGCHK_NG					: Error detected										*/
/*		(following is available when ADC_CFG_REG_REFRESH is STD_ON)								*/
/* 		ADC_REGCHK_REFRESH_SUCCESS		: Error detected but refresh is success					*/
/* 		ADC_REGCHK_REFRESH_IMPOSSIBLE	: Error detected for unrefreshable register	 			*/
/* 		ADC_REGCHK_REFRESH_FAILED		: Error detected and refresh failed			 			*/
/* Description			: Check all registers and refresh ones with expected value.				*/
/************************************************************************************************/
FUNC(uint32, ADC_CODE) Adc_Pil_Regchk_All(void);

/************************************************************************************************/
/* Service name			: Adc_Pil_Regchk_Grp													*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Reentrant																*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: uint32																*/
/* 		ADC_REGCHK_OK					: No Error detected										*/
/* 		ADC_REGCHK_NG					: Error detected										*/
/*		(following is available when ADC_CFG_REG_REFRESH is STD_ON)								*/
/* 		ADC_REGCHK_REFRESH_SUCCESS		: Error detected but refresh is success					*/
/* 		ADC_REGCHK_REFRESH_IMPOSSIBLE	: Error detected for unrefreshable register	 			*/
/* 		ADC_REGCHK_REFRESH_FAILED		: Error detected and refresh failed			 			*/
/* Description			: Check Group related registers and refresh ones with expected value.	*/
/************************************************************************************************/
FUNC(uint32, ADC_CODE) Adc_Pil_Regchk_Grp(
	CONST(Adc_GroupType,	ADC_CONST)	t_cudGrp
);

#endif

#define ADC_STOP_SEC_CODE_GLOBAL
#include "Adc_MemMap.h"

#endif
/*-- End Of File -------------------------------------------------------------------------------*/
