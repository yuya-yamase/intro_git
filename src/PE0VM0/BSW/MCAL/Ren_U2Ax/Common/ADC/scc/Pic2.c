/* PIC2-r04-303 */
/************************************************************************************************/
/*																								*/
/*		PIC2 Driver : Upper layer for RH850U2A/U2B												*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/
/* Not Support Streaming Access Mode	*/
/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include "Std_Types.h"
#include "Mcal_SpalCmn.h"

#include "Pic2.h"
#include "Pic2_Pil.h"

/*==============================================================================================*/
/* defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/
#if	(ADC_CFG_GLOBAL_REG_CONTROL == STD_ON)
/*==============================================================================================*/
/* constants																					*/
/*==============================================================================================*/
/*==============================================================================================*/
/* variables																					*/
/*==============================================================================================*/
/*==============================================================================================*/
/* prototype for local functions																*/
/*==============================================================================================*/
/*==============================================================================================*/
/* API Functions																				*/
/*==============================================================================================*/
#define ADC_START_SEC_CODE_GLOBAL
#include "Adc_MemMap.h"

/************************************************************************************************/
/* Service name			: Pic2_Init																*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: None																	*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Initializes the PIC2 hardware units and driver.						*/
/************************************************************************************************/
FUNC(void, PIC2_CODE) Pic2_Init(void)
{
	Pic2_Pil_Init();
}

/************************************************************************************************/
/* Service name			: Pic2_SetHardwareTrigger												*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* 		boolean			: TRUE:HW Trigger on ,FALSE:HW Trigger off								*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Set HW Trigger (TRGMD)												*/
/************************************************************************************************/
#if (ADC_CFG_HW_TRG_API==STD_ON)
FUNC(void, PIC2_CODE) Pic2_SetHardwareTrigger(
	CONST(Pic2_GroupType,	PIC2_CONST)	t_cudGrp,
	CONST(boolean,			PIC2_CONST)	t_cblisHWTriggerOn
)
{
	VAR(Adc_HWUnitType,	PIC2_VAR_NO_INIT) 	t_udHWUnit;
	VAR(Adc_SGType,		PIC2_VAR_NO_INIT) 	t_udSG;
	VAR(uint32,			PIC2_VAR_NO_INIT)	t_u4Pi20TSEL;
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	VAR(uint32,			PIC2_VAR_NO_INIT)	t_u4Pi21TSEL;
	#endif
			
	t_udHWUnit		= Adc_GetHWUnitID(t_cudGrp);
	t_udSG			= Adc_GetSGID(t_cudGrp);
	t_u4Pi20TSEL	= (uint32)PIC2_ZERO;
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	t_u4Pi21TSEL	= (uint32)PIC2_ZERO;
	#endif
	if (t_cblisHWTriggerOn==TRUE) {
		t_u4Pi20TSEL = Pic2_GetPic20TSEL(t_cudGrp);
		#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
		t_u4Pi21TSEL = Pic2_GetPic21TSEL(t_cudGrp);
		#endif
	}
	Pic2_Pil_SetHardwareTrigger(t_udHWUnit,t_udSG,t_u4Pi20TSEL
		#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
		,t_u4Pi21TSEL
		#endif
	 );
}
#endif

/*--------------------------------------------------------------------------*/
/* only when register check is available 									*/
/*--------------------------------------------------------------------------*/
#if (ADC_CFG_REG_CHK==STD_ON)
/************************************************************************************************/
/* Service name			: Pic2_Regchk_All														*/
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
/* Description			: Check all registers and refresh ones with expected value.				*/
/************************************************************************************************/
FUNC(uint32, PIC2_CODE) Pic2_Regchk_All(void)
{
	VAR(uint32,						ADC_VAR_NO_INIT)	t_u4ChkResult;

	t_u4ChkResult  = Pic2_Pil_Regchk_All();
	return(t_u4ChkResult);
}

/************************************************************************************************/
/* Service name			: Pic2_Regchk_Grp														*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Reentrant																*/
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
/* Description			: Check Group related registers and refresh ones with expected value.	*/
/************************************************************************************************/
FUNC(uint32, PIC2_CODE) Pic2_Regchk_Grp(
	CONST(Pic2_GroupType,	PIC2_CONST)	t_cudGrp
)
{
	VAR(uint32,						ADC_VAR_NO_INIT)	t_u4ChkResult;

	t_u4ChkResult  = Pic2_Pil_Regchk_Grp(t_cudGrp);
	return(t_u4ChkResult);
}

#if (ADC_CFG_REG_REFRESH==STD_ON)
/************************************************************************************************/
/* Service name			: Pic2_IsSGRunning														*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/* 		Pic2_SGType		: Scan Group Number														*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: 																		*/
/*		Adc status		: TRUE: some conversion is active, FALSE:no conversion is active		*/
/* Description			: Return the conversion status of a specific scan group					*/
/*						  in all HW Units that share the PIC2 registers.						*/
/************************************************************************************************/
FUNC(boolean, PIC2_CODE) Pic2_IsSGRunning(
	CONST(Pic2_SGType,	PIC2_CONST)	t_cudSG
)
{
	VAR(boolean,		ADC_VAR_NO_INIT)	t_b1isRunning;
	VAR(Adc_GroupType,  ADC_VAR_NO_INIT)	t_udGrp;

	t_b1isRunning = FALSE;

	for (t_udGrp=ADC_GRP00;t_udGrp<(Adc_GroupType)ADC_CFG_GRP_SIZE;t_udGrp++) {
		if (Adc_GetHWUnitID(t_udGrp)<(Adc_HWUnitType)PIC2_HWUNIT_WPIC2_SIZE) {
			if (Adc_GetSGID(t_udGrp)==t_cudSG) {
				if (Adc_GetGrpStatus(t_udGrp)!=ADC_IDLE) {
					t_b1isRunning = TRUE;
					break;
				}
			}
		}
	}
	return(t_b1isRunning);
}
#endif	/* if (ADC_CFG_REG_REFRESH==STD_ON)	*/
#endif	/* if (ADC_CFG_REG_CHK==STD_ON)	*/

#define ADC_STOP_SEC_CODE_GLOBAL
#include "Adc_MemMap.h"

#endif
/*-- End Of File -------------------------------------------------------------------------------*/
