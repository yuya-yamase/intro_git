/* PIC2-r04-303 */
/************************************************************************************************/
/*																								*/
/*		PIC2 Driver : Low Driver layer for RH850U2A/U2B											*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include "Std_Types.h"
#include "Mcal_SpalCmn.h"
#include "McalCommon_lib.h"

#include "Pic2_Pil.h"
#include "Reg_Pic2.h"

/*==============================================================================================*/
/* prototypes																					*/
/*==============================================================================================*/

/*==============================================================================================*/
/* defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/
/*--------------------------------------------------------------------------*/
/* defines																	*/
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* structs																	*/
/*--------------------------------------------------------------------------*/

#if	(ADC_CFG_GLOBAL_REG_CONTROL == STD_ON)
/*==============================================================================================*/
/* constants																					*/
/*==============================================================================================*/
/* config to register set value convert table	*/
#define ADC_START_SEC_CONST_16
#include "Adc_MemMap.h"
static CONST(uint16, PIC2_CONST)	s_u2EDGSELBitPostbl[PIC2_ADC_SG_NUM] = {
	PIC2_PIC2xADCXnEDGSEL_SG0_0,		/* scan group 0	*/
	PIC2_PIC2xADCXnEDGSEL_SG1_0,		/* scan group 1	*/
	PIC2_PIC2xADCXnEDGSEL_SG2_0,		/* scan group 2	*/
	PIC2_PIC2xADCXnEDGSEL_SG3_0,		/* scan group 3	*/
	PIC2_PIC2xADCXnEDGSEL_SG4_0			/* scan group 4	*/
};
#define ADC_STOP_SEC_CONST_16
#include "Adc_MemMap.h"

/*==============================================================================================*/
/* variables																					*/
/*==============================================================================================*/
/*==============================================================================================*/
/* prototype for local functions																*/
/*==============================================================================================*/
#define ADC_START_SEC_CODE_GLOBAL
#include "Adc_MemMap.h"

#if (ADC_CFG_REG_CHK==STD_ON)
static FUNC(uint32, ADC_CODE) Pic2_Pil_RegchkPreFix(
	CONST(Adc_GroupType,				PIC2_CONST)				t_cudGrp,
	CONST(Adc_HWUnitType,				PIC2_CONST)				t_cudHWUnit,
	CONST(Adc_SGType,					PIC2_CONST)				t_cudSG
);
static FUNC(uint32, ADC_CODE) Pic2_Pil_RegchkPostFix(
	CONST(Adc_HWUnitType,				PIC2_CONST)				t_cudHWUnit,
	CONST(Adc_SGType,					PIC2_CONST)				t_cudSG,
	P2VAR(uint16,			AUTOMATIC,	PIC2_VAR_NO_INIT)		t_pu2Pic20EDGSEL
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	,P2VAR(uint16,	AUTOMATIC, PIC2_VAR_NO_INIT)				t_pu2Pic21EDGSEL
	#endif
);
static FUNC(uint32, ADC_CODE) Pic2_Pil_RegchkDynamic(
	CONST(Adc_GroupType,				PIC2_CONST)				t_cudGrp,
	CONST(Adc_HWUnitType,				PIC2_CONST)				t_cudHWUnit,
	CONST(Adc_SGType,					PIC2_CONST)				t_cudSG
);
#endif

static FUNC(void, PIC2_CODE) Pic2_Pil_DataInit(
	P2VAR(uint16,	AUTOMATIC,	PIC2_VAR_NO_INIT)	t_pu2Pic20EDGSEL
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	,P2VAR(uint16,	AUTOMATIC,	PIC2_VAR_NO_INIT)	t_pu2Pic21EDGSEL
	#endif
);

#define ADC_STOP_SEC_CODE_GLOBAL
#include "Adc_MemMap.h"

/*----------------------------------------------------------------------------------------------*/
/* API Functions																				*/
/*----------------------------------------------------------------------------------------------*/
#define ADC_START_SEC_CODE_GLOBAL
#include "Adc_MemMap.h"

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
FUNC(void, PIC2_CODE) Pic2_Pil_Init(void)
{
	VAR(Adc_HWUnitType,	PIC2_VAR_NO_INIT)							t_udHWUnit;
	VAR(Adc_SGType,		PIC2_VAR_NO_INIT)							t_udSG;
	VAR(Adc_GroupType,	PIC2_VAR_NO_INIT)							t_udGrp;
	VAR(uint16,			PIC2_VAR_NO_INIT)							t_u2Pic20EDGSEL[PIC2_HWUNIT_WPIC2_SIZE];
	VAR(uint32,			PIC2_VAR_NO_INIT)							t_u4TSEL;
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	VAR(uint16,			PIC2_VAR_NO_INIT)							t_u2Pic21EDGSEL[PIC2_HWUNIT_WPIC2_SIZE];
	#endif


	/* init the internal data	*/
	Pic2_Pil_DataInit(
		&t_u2Pic20EDGSEL[0]
		#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
		,&t_u2Pic21EDGSEL[0]
		#endif
	);

	/* ADC Trigger Edge Direction			*/
	for( t_udHWUnit=ADC_HWUNIT0; t_udHWUnit<(Adc_HWUnitType)PIC2_HWUNIT_WPIC2_SIZE; t_udHWUnit++ ) {
		cpstReg_Pic20[PIC2_REG_ARRAY_ID0]->stADCXnTSELj[t_udHWUnit].u2EDGSEL = t_u2Pic20EDGSEL[t_udHWUnit];
		#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
		cpstReg_Pic21[PIC2_REG_ARRAY_ID0]->stADCXnTSELj[t_udHWUnit].u2EDGSEL = t_u2Pic21EDGSEL[t_udHWUnit];
		#endif
	}

	/* Trigger Output */
	for( t_udSG=ADC_SG0; t_udSG<(Adc_SGType)PIC2_ADC_SG_NUM; t_udSG++ ) {
		cpstReg_Pic20[PIC2_REG_ARRAY_ID0]->stADTEN4nj[PIC2_ADCTEN40j].stTrgCH[t_udSG].u2Data = Adc_cstUserConfig.cpstPIC2Confg->cpu2Pic20ADTEN40[t_udSG];
		cpstReg_Pic20[PIC2_REG_ARRAY_ID0]->stADTEN4nj[PIC2_ADCTEN41j].stTrgCH[t_udSG].u2Data = Adc_cstUserConfig.cpstPIC2Confg->cpu2Pic20ADTEN41[t_udSG];
		#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
		cpstReg_Pic21[PIC2_REG_ARRAY_ID0]->stADTEN4nj[PIC2_ADCTEN40j].stTrgCH[t_udSG].u2Data = Adc_cstUserConfig.cpstPIC2Confg->cpu2Pic21ADTEN40[t_udSG];
		cpstReg_Pic21[PIC2_REG_ARRAY_ID0]->stADTEN4nj[PIC2_ADCTEN41j].stTrgCH[t_udSG].u2Data = Adc_cstUserConfig.cpstPIC2Confg->cpu2Pic21ADTEN41[t_udSG];
		#endif
	}

	t_u4TSEL = PIC2_ZERO;
	for (t_udGrp=ADC_GRP00;t_udGrp<(Adc_GroupType)ADC_CFG_GRP_SIZE;t_udGrp++) {
		t_udHWUnit	= Adc_GetHWUnitID(t_udGrp);
		t_udSG		= Adc_GetSGID(t_udGrp);
		/* ADC Trigger Selection (Not select)			*/
		cpstReg_Pic20[PIC2_REG_ARRAY_ID0]->stADCXnTSELj[t_udHWUnit].u4TSEL[t_udSG] = t_u4TSEL;
		#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
		cpstReg_Pic21[PIC2_REG_ARRAY_ID0]->stADCXnTSELj[t_udHWUnit].u4TSEL[t_udSG] = t_u4TSEL;
		#endif
	}
}

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
)
{
	cpstReg_Pic20[PIC2_REG_ARRAY_ID0]->stADCXnTSELj[t_cudHWUnit].u4TSEL[t_cudSG] = t_cu4Pi20TSEL;
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	cpstReg_Pic21[PIC2_REG_ARRAY_ID0]->stADCXnTSELj[t_cudHWUnit].u4TSEL[t_cudSG] = t_cu4Pi21TSEL;
	#endif
}
#endif

/*--------------------------------------------------------------------------*/
/* only when register check is available 									*/
/*--------------------------------------------------------------------------*/
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
/*		(following is available when ADC_CFG_REG_REFRESH is STD_ON)								*/
/* 		ADC_REGCHK_REFRESH_SUCCESS		: Error detected but refresh is success					*/
/* 		ADC_REGCHK_REFRESH_IMPOSSIBLE	: Error detected for unrefreshable register	 			*/
/* 		ADC_REGCHK_REFRESH_FAILED		: Error detected and refresh failed			 			*/
/* Description			: Check all registers and refresh ones with expected value.				*/
/************************************************************************************************/
FUNC(uint32, ADC_CODE) Pic2_Pil_Regchk_All(void)
{
	VAR(uint32,			ADC_VAR_NO_INIT)	t_u4ChkResult;
	VAR(Adc_GroupType, 	ADC_VAR_NO_INIT) 	t_udGrp;
	VAR(Adc_HWUnitType,	ADC_VAR_NO_INIT)	t_udHWUnit;
	VAR(Adc_SGType,		ADC_VAR_NO_INIT) 	t_udSG;
	VAR(uint16,			PIC2_VAR_NO_INIT)	t_u2Pic20EDGSEL[PIC2_HWUNIT_WPIC2_SIZE];
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	VAR(uint16,			PIC2_VAR_NO_INIT)	t_u2Pic21EDGSEL[PIC2_HWUNIT_WPIC2_SIZE];
	#endif

	Pic2_Pil_DataInit(
		&t_u2Pic20EDGSEL[0]
		#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
		,&t_u2Pic21EDGSEL[0]
		#endif
	);
	t_u4ChkResult	= ADC_REGCHK_OK;
	for (t_udGrp=ADC_GRP00;t_udGrp<(Adc_GroupType)ADC_CFG_GRP_SIZE;t_udGrp++ ) {
		t_udHWUnit		= Adc_GetHWUnitID(t_udGrp);
		t_udSG			= Adc_GetSGID(t_udGrp);
		t_u4ChkResult  |= Pic2_Pil_RegchkPreFix(t_udGrp,t_udHWUnit,t_udSG);
		t_u4ChkResult  |= Pic2_Pil_RegchkPostFix(t_udHWUnit,t_udSG,
												 &t_u2Pic20EDGSEL[0]
												 #if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
												 ,&t_u2Pic21EDGSEL[0]
												 #endif
												);
		t_u4ChkResult  |= Pic2_Pil_RegchkDynamic(t_udGrp,t_udHWUnit,t_udSG);
	}
	return(t_u4ChkResult);
}

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
/*		(following is available when ADC_CFG_REG_REFRESH is STD_ON)								*/
/* 		ADC_REGCHK_REFRESH_SUCCESS		: Error detected but refresh is success					*/
/* 		ADC_REGCHK_REFRESH_IMPOSSIBLE	: Error detected for unrefreshable register	 			*/
/* 		ADC_REGCHK_REFRESH_FAILED		: Error detected and refresh failed			 			*/
/* Description			: Check Group related registers and refresh ones with expected value.	*/
/************************************************************************************************/
FUNC(uint32, ADC_CODE) Pic2_Pil_Regchk_Grp(
	CONST(Adc_GroupType,	PIC2_CONST)	t_cudGrp
)
{
	VAR(uint32,			ADC_VAR_NO_INIT)	t_u4ChkResult;
	VAR(Adc_HWUnitType,	ADC_VAR_NO_INIT)	t_udHWUnit;
	VAR(Adc_SGType,		ADC_VAR_NO_INIT) 	t_udSG;
	VAR(uint16,			PIC2_VAR_NO_INIT)	t_u2Pic20EDGSEL[PIC2_HWUNIT_WPIC2_SIZE];
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	VAR(uint16,			PIC2_VAR_NO_INIT)	t_u2Pic21EDGSEL[PIC2_HWUNIT_WPIC2_SIZE];
	#endif

	t_udHWUnit		= Adc_GetHWUnitID(t_cudGrp);
	t_udSG			= Adc_GetSGID(t_cudGrp);
	Pic2_Pil_DataInit(
		&t_u2Pic20EDGSEL[0]
		#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
		,&t_u2Pic21EDGSEL[0]
		#endif
	);
	t_u4ChkResult   = Pic2_Pil_RegchkPreFix(t_cudGrp,t_udHWUnit,t_udSG);
	t_u4ChkResult  |= Pic2_Pil_RegchkPostFix(t_udHWUnit,t_udSG,
											 &t_u2Pic20EDGSEL[0]
											 #if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
											 ,&t_u2Pic21EDGSEL[0]
											 #endif
											);
	t_u4ChkResult  |= Pic2_Pil_RegchkDynamic(t_cudGrp,t_udHWUnit,t_udSG);
	return(t_u4ChkResult);
}
/*----------------------------------------------------------------------------------------------*/
/* Private API 																					*/
/*----------------------------------------------------------------------------------------------*/
/************************************************************************************************/
/* Service name			: Pic2_Pil_RegchkPreFix													*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* 		Adc_HWUnitType	: HW Unit Number														*/
/* 		Adc_SGType		: Scan Group Number														*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: uint32																*/
/* 		ADC_REGCHK_OK					: No Error detected										*/
/* 		ADC_REGCHK_NG					: Error detected										*/
/*		(following is available when ADC_CFG_REG_REFRESH is STD_ON)								*/
/* 		ADC_REGCHK_REFRESH_SUCCESS		: Error detected but refresh is success					*/
/* 		ADC_REGCHK_REFRESH_IMPOSSIBLE	: Error detected for unrefreshable register	 			*/
/* 		ADC_REGCHK_REFRESH_FAILED		: Error detected and refresh failed			 			*/
/* Description			: Check registers deceided by a configuration							*/
/************************************************************************************************/
static FUNC(uint32, ADC_CODE) Pic2_Pil_RegchkPreFix(
	CONST(Adc_GroupType,				PIC2_CONST)				t_cudGrp,		/* 	used in ADC_RegValueCheckByScanGroup */
	CONST(Adc_HWUnitType,				PIC2_CONST)				t_cudHWUnit,
	CONST(Adc_SGType,					PIC2_CONST)				t_cudSG
)
{
	VAR(uint32,			ADC_VAR_NO_INIT)	t_u4ChkResult;

	t_u4ChkResult	= ADC_REGCHK_OK;
	/* Trigger Output */
	/* t_u4ChkResult is updated in ADC_RegValueCheckBySGwoMask	*/
	ADC_RegValueCheckBySGwoMask(uint16, cpstReg_Pic20[PIC2_REG_ARRAY_ID0]->stADTEN4nj[PIC2_ADCTEN40j].stTrgCH[t_cudSG].u2Data, Adc_cstUserConfig.cpstPIC2Confg->cpu2Pic20ADTEN40[t_cudSG]);
	ADC_RegValueCheckBySGwoMask(uint16, cpstReg_Pic20[PIC2_REG_ARRAY_ID0]->stADTEN4nj[PIC2_ADCTEN41j].stTrgCH[t_cudSG].u2Data, Adc_cstUserConfig.cpstPIC2Confg->cpu2Pic20ADTEN41[t_cudSG]);
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	ADC_RegValueCheckBySGwoMask(uint16, cpstReg_Pic21[PIC2_REG_ARRAY_ID0]->stADTEN4nj[PIC2_ADCTEN40j].stTrgCH[t_cudSG].u2Data, Adc_cstUserConfig.cpstPIC2Confg->cpu2Pic21ADTEN40[t_cudSG]);
	ADC_RegValueCheckBySGwoMask(uint16, cpstReg_Pic21[PIC2_REG_ARRAY_ID0]->stADTEN4nj[PIC2_ADCTEN41j].stTrgCH[t_cudSG].u2Data, Adc_cstUserConfig.cpstPIC2Confg->cpu2Pic21ADTEN41[t_cudSG]);
	#endif

	return(t_u4ChkResult);
}
/************************************************************************************************/
/* Service name			: Pic2_Pil_RegchkPostFix												*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/* 		Adc_HWUnitType	: HW Unit Number														*/
/* 		Adc_SGType		: Scan Group Number														*/
/*		Pic20EDGSEL		: Sync: Pic20EDGSEL register											*/
/*		Pic21EDGSEL		: Sync: Pic21EDGSEL register											*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: uint32																*/
/* 		ADC_REGCHK_OK					: No Error detected										*/
/* 		ADC_REGCHK_NG					: Error detected										*/
/*		(following is available when ADC_CFG_REG_REFRESH is STD_ON)								*/
/* 		ADC_REGCHK_REFRESH_SUCCESS		: Error detected but refresh is success					*/
/* 		ADC_REGCHK_REFRESH_IMPOSSIBLE	: Error detected for unrefreshable register	 			*/
/* 		ADC_REGCHK_REFRESH_FAILED		: Error detected and refresh failed			 			*/
/* Description			: Check registers deceided by some configurations						*/
/************************************************************************************************/
static FUNC(uint32, ADC_CODE) Pic2_Pil_RegchkPostFix(
	CONST(Adc_HWUnitType,				PIC2_CONST)				t_cudHWUnit,
	CONST(Adc_SGType,					PIC2_CONST)				t_cudSG,
	P2VAR(uint16,			AUTOMATIC,	PIC2_VAR_NO_INIT)		t_pu2Pic20EDGSEL
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	,P2VAR(uint16,	AUTOMATIC, PIC2_VAR_NO_INIT)				t_pu2Pic21EDGSEL
	#endif
)
{
	VAR(uint32,			ADC_VAR_NO_INIT)	t_u4ChkResult;

	t_u4ChkResult	= ADC_REGCHK_OK;
	if (t_cudHWUnit<PIC2_HWUNIT_WPIC2_SIZE) {
		/* t_u4ChkResult is updated in ADC_RegValueCheckByHWUnit	*/
		/* ADC Trigger Edge Direction			*/
		ADC_RegValueCheckByHWUnit(uint16, cpstReg_Pic20[PIC2_REG_ARRAY_ID0]->stADCXnTSELj[t_cudHWUnit].u2EDGSEL, t_pu2Pic20EDGSEL[t_cudHWUnit], PIC2_EDGSEL_DEFBIT,t_cudHWUnit); 
		#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
		ADC_RegValueCheckByHWUnit(uint16, cpstReg_Pic21[PIC2_REG_ARRAY_ID0]->stADCXnTSELj[t_cudHWUnit].u2EDGSEL, t_pu2Pic21EDGSEL[t_cudHWUnit], PIC2_EDGSEL_DEFBIT,t_cudHWUnit);
		#endif
	}
	return(t_u4ChkResult);
}

/************************************************************************************************/
/* Service name			: Pic2_Pil_RegchkDynamic												*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* 		Adc_HWUnitType	: HW Unit Number														*/
/* 		Adc_SGType		: Scan Group Number														*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: uint32																*/
/* 		ADC_REGCHK_OK					: No Error detected										*/
/* 		ADC_REGCHK_NG					: Error detected										*/
/*		(following is available when ADC_CFG_REG_REFRESH is STD_ON)								*/
/* 		ADC_REGCHK_REFRESH_SUCCESS		: Error detected but refresh is success					*/
/* 		ADC_REGCHK_REFRESH_IMPOSSIBLE	: Error detected for unrefreshable register	 			*/
/* 		ADC_REGCHK_REFRESH_FAILED		: Error detected and refresh failed			 			*/
/* Description			: Check registers deceided by conversion status							*/
/************************************************************************************************/
static FUNC(uint32, ADC_CODE) Pic2_Pil_RegchkDynamic(
	CONST(Adc_GroupType,				PIC2_CONST)				t_cudGrp,
	CONST(Adc_HWUnitType,				PIC2_CONST)				t_cudHWUnit,
	CONST(Adc_SGType,					PIC2_CONST)				t_cudSG
)
{
	VAR(uint32,			ADC_VAR_NO_INIT)	t_u4ChkResult;
	VAR(Adc_StatusType,	ADC_VAR_NO_INIT)	t_udStatus;
	VAR(uint32,			ADC_VAR_NO_INIT)	t_u4RegValue;
	VAR(uint32,			ADC_VAR_NO_INIT)	t_u4ExpectedValue;

	t_u4ChkResult	= ADC_REGCHK_OK;
	ADC_ENTER_CRITICAL_SECTION(ADC_CODE);
	t_udStatus		= Adc_GetGroupStatus(t_cudGrp);
	t_u4RegValue	= cpstReg_Pic20[PIC2_REG_ARRAY_ID0]->stADCXnTSELj[t_cudHWUnit].u4TSEL[t_cudSG] & PIC2_20TSEL_DEFBIT;
	if (t_udStatus==ADC_IDLE) {
		t_u4ExpectedValue	= (uint32)PIC2_ZERO & PIC2_20TSEL_DEFBIT;
		if (t_u4RegValue!=t_u4ExpectedValue) {
			#if (ADC_CFG_REG_REFRESH==STD_ON)
			cpstReg_Pic20[PIC2_REG_ARRAY_ID0]->stADCXnTSELj[t_cudHWUnit].u4TSEL[t_cudSG] = t_u4ExpectedValue;
			t_u4RegValue = cpstReg_Pic20[PIC2_REG_ARRAY_ID0]->stADCXnTSELj[t_cudHWUnit].u4TSEL[t_cudSG] & PIC2_20TSEL_DEFBIT;
			if (t_u4RegValue==t_u4ExpectedValue) {
				t_u4ChkResult |= ADC_REGCHK_REFRESH_SUCCESS;
			} else {
				t_u4ChkResult |= ADC_REGCHK_REFRESH_FAILED;
			}
			#else
			t_u4ChkResult  |= ADC_REGCHK_NG;
			#endif
		}
	} else {
		t_u4ExpectedValue	= Adc_cstUserConfig.cpstPIC2Confg->cpu4Pic20TSEL[t_cudGrp] & PIC2_20TSEL_DEFBIT;
		if (t_u4RegValue!=t_u4ExpectedValue) {
			#if (ADC_CFG_REG_REFRESH==STD_ON)
			t_u4ChkResult |= ADC_REGCHK_REFRESH_IMPOSSIBLE;
			#else
			t_u4ChkResult  |= ADC_REGCHK_NG;
			#endif
		}
	}
	ADC_EXIT_CRITICAL_SECTION(ADC_CODE);

	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	ADC_ENTER_CRITICAL_SECTION(ADC_CODE);
	t_u4RegValue		= cpstReg_Pic21[PIC2_REG_ARRAY_ID0]->stADCXnTSELj[t_cudHWUnit].u4TSEL[t_cudSG] & PIC2_21TSEL_DEFBIT;
	t_udStatus		= Adc_GetGroupStatus(t_cudGrp);
	if (t_udStatus==ADC_IDLE) {
		t_u4RegValue		= cpstReg_Pic21[PIC2_REG_ARRAY_ID0]->stADCXnTSELj[t_cudHWUnit].u4TSEL[t_cudSG] & PIC2_21TSEL_DEFBIT;
		t_u4ExpectedValue	= (uint32)PIC2_ZERO & PIC2_21TSEL_DEFBIT;
		if (t_u4RegValue!=t_u4ExpectedValue) {
			#if (ADC_CFG_REG_REFRESH==STD_ON)
			cpstReg_Pic21[PIC2_REG_ARRAY_ID0]->stADCXnTSELj[t_cudHWUnit].u4TSEL[t_cudSG] = t_u4ExpectedValue;
			t_u4RegValue = cpstReg_Pic21[PIC2_REG_ARRAY_ID0]->stADCXnTSELj[t_cudHWUnit].u4TSEL[t_cudSG] & PIC2_21TSEL_DEFBIT;
			if (t_u4RegValue==t_u4ExpectedValue) {
				t_u4ChkResult |= ADC_REGCHK_REFRESH_SUCCESS;
			} else {
				t_u4ChkResult |= ADC_REGCHK_REFRESH_FAILED;
			}
			#else
			t_u4ChkResult  |= ADC_REGCHK_NG;
			#endif
		}
	} else {
		t_u4ExpectedValue	= Adc_cstUserConfig.cpstPIC2Confg->cpu4Pic21TSEL[t_cudGrp] & PIC2_21TSEL_DEFBIT;
		if (t_u4RegValue!=t_u4ExpectedValue) {
			#if (ADC_CFG_REG_REFRESH==STD_ON)
			t_u4ChkResult |= ADC_REGCHK_REFRESH_IMPOSSIBLE;
			#else
			t_u4ChkResult  |= ADC_REGCHK_NG;
			#endif
		}
	}
	ADC_EXIT_CRITICAL_SECTION(ADC_CODE);
	#endif

	return(t_u4ChkResult);
}

#endif	/* if (ADC_CFG_REG_CHK==STD_ON)	*/

/************************************************************************************************/
/* Service name			: Pic2_Pil_DataInit														*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: None																	*/
/* Parameters (inout)	: 																		*/
/*		Pic20EDGSEL		: Async: Pic20EDGSEL register											*/
/*		Pic21EDGSEL		: Async: Pic21EDGSEL register											*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Initializes the PIC2 internal data 			.						*/
/************************************************************************************************/
static FUNC(void, PIC2_CODE) Pic2_Pil_DataInit(
	P2VAR(uint16,	AUTOMATIC, PIC2_VAR_NO_INIT)		t_pu2Pic20EDGSEL
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	,P2VAR(uint16,	AUTOMATIC, PIC2_VAR_NO_INIT)		t_pu2Pic21EDGSEL
	#endif
)
{
	VAR(Adc_GroupType,	PIC2_VAR_NO_INIT)				t_udGrp;
	VAR(Adc_HWUnitType,	PIC2_VAR_NO_INIT)				t_udHWUnit;
	VAR(Adc_SGType,		PIC2_VAR_NO_INIT)				t_udSG;
	VAR(uint16,			PIC2_VAR_NO_INIT)				t_u2Data;
	VAR(uint32,			PIC2_VAR_NO_INIT)				t_u4Data;

	/** set initial value	**/
	/* ADC Trigger Edge Direction			*/
	for( t_udHWUnit=ADC_HWUNIT0; t_udHWUnit<(Adc_HWUnitType)PIC2_HWUNIT_WPIC2_SIZE; t_udHWUnit++ ) {
		t_pu2Pic20EDGSEL[t_udHWUnit] = (uint16)PIC2_ZERO;
		#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
			t_pu2Pic21EDGSEL[t_udHWUnit] = (uint16)PIC2_ZERO;
		#endif
	}

	/** set configuration value	**/
	for (t_udGrp=ADC_GRP00;t_udGrp<(Adc_GroupType)ADC_CFG_GRP_SIZE;t_udGrp++) {
		t_udHWUnit		= Adc_GetHWUnitID(t_udGrp);
		t_udSG			= Adc_GetSGID(t_udGrp);

		/* ADC Trigger Edge Direction			*/
		if ( t_udHWUnit < (Adc_HWUnitType)PIC2_HWUNIT_WPIC2_SIZE ) {
			t_u4Data = Adc_cstUserConfig.cpstPIC2Confg->cpu4Pic20TSEL[t_udGrp];
		
			if (t_u4Data!=(uint32)PIC2_ZERO) {
				t_u2Data						= (uint16)Adc_cstUserConfig.cpstPIC2Confg->cpudEDGSEL[t_udGrp];
				t_u2Data    				   *= s_u2EDGSELBitPostbl[t_udSG];		/* never wraparound :ignore QAC-3383/3384	*/
				t_pu2Pic20EDGSEL[t_udHWUnit]	+= t_u2Data;
			}
		#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
			t_u4Data = Adc_cstUserConfig.cpstPIC2Confg->cpu4Pic21TSEL[t_udGrp];

			if (t_u4Data!=(uint32)PIC2_ZERO) {
				t_u2Data						 = (uint16)Adc_cstUserConfig.cpstPIC2Confg->cpudEDGSEL[t_udGrp];
				t_u2Data   						*= s_u2EDGSELBitPostbl[t_udSG];		/* never wraparound :ignore QAC-3383/3384	*/
				t_pu2Pic21EDGSEL[t_udHWUnit]	+= t_u2Data;
			}
		#endif
		}
	}
}

#define ADC_STOP_SEC_CODE_GLOBAL
#include "Adc_MemMap.h"

#endif
/*-- End Of File -------------------------------------------------------------------------------*/
