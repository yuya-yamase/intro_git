/* PIC2-r04-303 */
/************************************************************************************************/
/*																								*/
/*		Pic2 Driver : Upper layer for RH850U2A/U2B												*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/
#ifndef PIC2_H
#define PIC2_H

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include "Std_Types.h"
#include "Mcal_SpalCmn.h"

#include "Adc_Cfg.h"
#include "Reg_Pic2.h"

/*==============================================================================================*/
/* defines																						*/
/*==============================================================================================*/
/*--------------------------------------------------------------------------*/
/* defines - intenal use													*/
/*--------------------------------------------------------------------------*/
#define PIC2_CODE
#define PIC2_CONST
#define PIC2_VAR_INIT
#define PIC2_VAR_NO_INIT
#define	PIC2_ZERO				(0u)

/*------------------------------------------------------------------*/
/* A/D Converter Trigger Output Select								*/
/*------------------------------------------------------------------*/
/* U2A:PIC2ADTEN4kj(k=0-1,j=0-4),	U2B:PIC20ADTEN4nj(n=0-1,j=0-5)	*/
/* 									U2B:PIC21ADTEN4nj(n=0-1,j=0-5)	*/
#define PIC2_TAUX_TRG_OFF		((uint16)PIC2_ZERO)
#define PIC2_TAUX_TRG_CH00		((uint16)PIC2_PIC2xADTEN_TRG_TAUD00)
#define PIC2_TAUX_TRG_CH01		((uint16)PIC2_PIC2xADTEN_TRG_TAUD01)
#define PIC2_TAUX_TRG_CH02		((uint16)PIC2_PIC2xADTEN_TRG_TAUD02)
#define PIC2_TAUX_TRG_CH03		((uint16)PIC2_PIC2xADTEN_TRG_TAUD03)
#define PIC2_TAUX_TRG_CH04		((uint16)PIC2_PIC2xADTEN_TRG_TAUD04)
#define PIC2_TAUX_TRG_CH05		((uint16)PIC2_PIC2xADTEN_TRG_TAUD05)
#define PIC2_TAUX_TRG_CH06		((uint16)PIC2_PIC2xADTEN_TRG_TAUD06)
#define PIC2_TAUX_TRG_CH07		((uint16)PIC2_PIC2xADTEN_TRG_TAUD07)
#define PIC2_TAUX_TRG_CH08		((uint16)PIC2_PIC2xADTEN_TRG_TAUD08)
#define PIC2_TAUX_TRG_CH09		((uint16)PIC2_PIC2xADTEN_TRG_TAUD09)
#define PIC2_TAUX_TRG_CH10		((uint16)PIC2_PIC2xADTEN_TRG_TAUD10)
#define PIC2_TAUX_TRG_CH11		((uint16)PIC2_PIC2xADTEN_TRG_TAUD11)
#define PIC2_TAUX_TRG_CH12		((uint16)PIC2_PIC2xADTEN_TRG_TAUD12)
#define PIC2_TAUX_TRG_CH13		((uint16)PIC2_PIC2xADTEN_TRG_TAUD13)
#define PIC2_TAUX_TRG_CH14		((uint16)PIC2_PIC2xADTEN_TRG_TAUD14)
#define PIC2_TAUX_TRG_CH15		((uint16)PIC2_PIC2xADTEN_TRG_TAUD15)

/*--------------------------------------------------------------------------*/
/* defines - compile SW														*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* defines - config data access												*/
/*--------------------------------------------------------------------------*/
#define Pic2_GetPic20TSEL(gID)		(Adc_cstUserConfig.cpstPIC2Confg->cpu4Pic20TSEL[gID])
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
#define Pic2_GetPic21TSEL(gID)		(Adc_cstUserConfig.cpstPIC2Confg->cpu4Pic21TSEL[gID])
#endif

/*--------------------------------------------------------------------------*/
/* defines - register check													*/
/*--------------------------------------------------------------------------*/
#if (ADC_CFG_REG_CHK==STD_ON)
#if (ADC_CFG_REG_REFRESH==STD_ON)
/* check by SG for PIC2	*/
#define	PIC2_RegValueCheckBySG(size,reg,expt,sg)					\
{																	\
	VAR(size,			ADC_VAR_NO_INIT)	t_uxRegValue;			\
	VAR(size,			ADC_VAR_NO_INIT)	t_uxExpectedValue;		\
	VAR(boolean,		ADC_VAR_NO_INIT)	t_b1isRunning;			\
																	\
	t_uxRegValue		= (reg);									\
	t_uxExpectedValue	= (expt);									\
	if (t_uxRegValue!=t_uxExpectedValue) {							\
		ADC_ENTER_CRITICAL_SECTION(ADC_CODE);						\
		t_b1isRunning	= Pic2_IsSGRunning(sg);						\
		if (t_b1isRunning==FALSE) {									\
			(reg) = (expt);											\
			t_uxRegValue = (reg);									\
			if (t_uxRegValue==t_uxExpectedValue) {					\
				t_u4ChkResult	|= ADC_REGCHK_REFRESH_SUCCESS;		\
			} else {												\
				t_u4ChkResult	|= ADC_REGCHK_REFRESH_FAILED;		\
			}														\
		} else {													\
			t_u4ChkResult |= ADC_REGCHK_REFRESH_IMPOSSIBLE;			\
		}															\
		ADC_EXIT_CRITICAL_SECTION(ADC_CODE);						\
	}																\
}
#else
#define	PIC2_RegValueCheckBySG(size,reg,expt,sg)					\
{																	\
	VAR(size,	ADC_VAR_NO_INIT)	t_uxRegValue;					\
	VAR(size,	ADC_VAR_NO_INIT)	t_uxExpectedValue;				\
																	\
	t_uxRegValue		= (reg);									\
	t_uxExpectedValue	= (expt);									\
	if (t_uxRegValue!=t_uxExpectedValue) {							\
		t_u4ChkResult  |= ADC_REGCHK_NG;							\
	}																\
}
#endif	/* if (ADC_CFG_REG_REFRESH==STD_ON)	*/
#endif	/* if (ADC_CFG_REG_CHK==STD_ON)	*/

/*==============================================================================================*/
/* data types / structs / unions / macros														*/
/*==============================================================================================*/
/*--------------------------------------------------------------------------*/
/* data types - defined by AUTOSAR											*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* data types - original													*/
/*--------------------------------------------------------------------------*/
typedef	uint8	Pic2_GroupType;
typedef	uint8	Pic2_SGType;
/*--------------------------------------------------------------------------*/
/* enum - defined by AUTOSAR												*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* enum - original															*/
/*--------------------------------------------------------------------------*/
/* A/D Converter Trigger Edge	*/
typedef enum {
	PIC2_EDG_DIRECT_RISING	= PIC2_ADCXnEDGSEL_RISING,
	PIC2_EDG_DIRECT_FALLING	= PIC2_ADCXnEDGSEL_FALLING,
	PIC2_EDG_DIRECT_BOTH	= PIC2_ADCXnEDGSEL_BOTH
} Pic2_EDGSELType;

/*--------------------------------------------------------------------------*/
/* structs																	*/
/*--------------------------------------------------------------------------*/
/* PIC2 Config	*/
typedef struct {
	const	uint32*				cpu4Pic20TSEL;							/* ADC Trigger Selection (PIC20)	ADC_CFG_GRP_SIZE		*/
	const	Pic2_EDGSELType*	cpudEDGSEL;								/* ADC Trigger Edge Direction		ADC_CFG_GRP_SIZE		*/
	const	uint16*				cpu2Pic20ADTEN40;						/* Trigger Output TAUD0  (PIC20)	PIC2_TSEL_SG_MAXSIZE	*/
	const	uint16*				cpu2Pic20ADTEN41;						/* Trigger Output TAUD1  (PIC20)	PIC2_TSEL_SG_MAXSIZE	*/
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	const	uint32*				cpu4Pic21TSEL;							/* ADC Trigger Selection (PIC21)	ADC_CFG_GRP_SIZE		*/
	const	uint16*				cpu2Pic21ADTEN40;						/* Trigger Output TAUD2  (PIC21)	PIC2_TSEL_SG_MAXSIZE	*/
	const	uint16*				cpu2Pic21ADTEN41;						/* Trigger Output TAUD3  (PIC21)	PIC2_TSEL_SG_MAXSIZE	*/
#endif
} Pic2_ConfigType;

#if	(ADC_CFG_GLOBAL_REG_CONTROL == STD_ON)
/*==============================================================================================*/
/* external symbols																				*/
/*==============================================================================================*/
/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
#define ADC_START_SEC_CODE_GLOBAL
#include "Adc_MemMap.h"
/*----------------------------------------------------------------------------------------------*/
/*	API Functions																				*/
/*----------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------*/
/* Public API 																					*/
/*----------------------------------------------------------------------------------------------*/

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
FUNC(void, PIC2_CODE) Pic2_Init(void);

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
);
#endif

/*--------------------------------------------------------------------------*/
/* only when register check is  available									*/
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
/*		(following is available when ADC_CFG_REG_REFRESH is STD_ON)								*/
/* 		ADC_REGCHK_REFRESH_SUCCESS		: Error detected but refresh is success					*/
/* 		ADC_REGCHK_REFRESH_IMPOSSIBLE	: Error detected for unrefreshable register	 			*/
/* 		ADC_REGCHK_REFRESH_FAILED		: Error detected and refresh failed			 			*/
/* Description			: Check all registers and refresh ones with expected value.				*/
/************************************************************************************************/
FUNC(uint32, PIC2_CODE) Pic2_Regchk_All(void);

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
/*		(following is available when ADC_CFG_REG_REFRESH is STD_ON)								*/
/* 		ADC_REGCHK_REFRESH_SUCCESS		: Error detected but refresh is success					*/
/* 		ADC_REGCHK_REFRESH_IMPOSSIBLE	: Error detected for unrefreshable register	 			*/
/* 		ADC_REGCHK_REFRESH_FAILED		: Error detected and refresh failed			 			*/
/* Description			: Check Group related registers and refresh ones with expected value.	*/
/************************************************************************************************/
FUNC(uint32, PIC2_CODE) Pic2_Regchk_Grp(
	CONST(Pic2_GroupType,	PIC2_CONST)	t_cudGrp
);

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
);
#endif	/* if (ADC_CFG_REG_REFRESH==STD_ON)	*/
#endif	/* if (ADC_CFG_REG_CHK==STD_ON)	*/

#define ADC_STOP_SEC_CODE_GLOBAL
#include "Adc_MemMap.h"

#endif
#endif
/*-- End Of File -------------------------------------------------------------------------------*/
