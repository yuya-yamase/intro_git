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

/*------------------------------------------------------------------*/
/* A/D Converter Trigger Output Select								*/
/*------------------------------------------------------------------*/
/* U2A:PIC2ADTEN4kj(k=2,j=0-4),				U2B:PIC20ADTEN4nj(n=2,j=0-5)		*/
/* ENCA not supported															*/
/* U2A:PIC2ADTEN5nj(n=0-1,j=0-4)												*/
/* U2B:PIC20ADTEN5nj(n=0-3,j=0-5)												*/
/* U2A:PIC2ADTEN6nj(n=0,1,j=0-4),			U2B:-								*/
/* U2A:PIC2ADTEN7nj(n=0,1,j=0-4)												*/
/* U2B:PIC20ADTEN7nj(n=0-3,j=0-5)												*/
/* U2A:PIC2ADTEN8nj(n=0,1,j=0-4)												*/
/* U2B:PIC20ADTEN8nj(n=0-3,j=0-5)												*/
/* U2B:PIC2ADTCFGk(k=0-9)														*/
/*   1-  80 : TOMi OUTx		(i = 0 to 4,	x = 0 to 15)	*/
/*  81-  96 : undefeine										*/
/*  97- 176 : ATOMi OUTx	(i = 0 to 9,	x = 0 to 7),	*/
/* 177- 240 : TIOi OUTx		(i = 1-4,6-9,	x = 0 to 7),	*/
/* 241- 280 : TOMi OUTx_N	(i = 0 to 4, 	x = 0 to 7),	*/
/* 281- 336 : ATOMi OUTx_N	(i = 0 to 6, 	x = 0 to 7),	*/
/* 337- 344 : TIOi OUTx_N	(i = 1,		 	x = 0 to 7),	*/
/* 345- 424 : MCSi IRQx		(i = 0 to 9, 	x = 0 to 7),	*/
/* 425- 480 : TIMi IRQx		(i = 0 to 6, 	x = 0 to 7),	*/

/*--------------------------------------------------------------------------*/
/* structs																	*/
/*--------------------------------------------------------------------------*/
/* PIC2 Config	*/
typedef struct {
	const	uint32*				cpu4Pic20TSEL;							/* ADC Trigger Selection (PIC20)	ADC_CFG_GRP_SIZE		*/
	const	Pic2_EDGSELType*	cpudEDGSEL;								/* ADC Trigger Edge Direction		ADC_CFG_GRP_SIZE		*/
	const	uint16*				cpu2Pic20ADTEN40;						/* Trigger Output TAUD0 (PIC20)		PIC2_TSEL_SG_MAXSIZE		*/
	const	uint16*				cpu2Pic20ADTEN41;						/* Trigger Output TAUD1 (PIC20)		PIC2_TSEL_SG_MAXSIZE		*/
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	const	uint32*				cpu4Pic21TSEL;							/* ADC Trigger Selection (PIC21)	PIC2_TSEL_SG_MAXSIZE		*/
	const	uint16*				cpu2Pic21ADTEN40;						/* Trigger Output TAUD0 (PIC21)		PIC2_TSEL_SG_MAXSIZE		*/
	const	uint16*				cpu2Pic21ADTEN41;						/* Trigger Output TAUD1 (PIC21)		PIC2_TSEL_SG_MAXSIZE		*/
#endif
} Pic2_ConfigType;

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
/*----------------------------------------------------------------------------------------------*/
/* Private API (public API in ADC module) 														*/
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
/* only register check is  available										*/
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
/* Description			: Check all registers and refresh ones w expected value.				*/
/************************************************************************************************/
FUNC(uint32, PIC2_CODE) Pic2_Regchk_All(void);

/************************************************************************************************/
/* Service name			: Pic2_Regchk_Grp														*/
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
FUNC(uint32, PIC2_CODE) Pic2_Regchk_Grp(
	CONST(Pic2_GroupType,	PIC2_CONST)	t_cudGrp
);
#endif

#define ADC_STOP_SEC_CODE_GLOBAL
#include "Adc_MemMap.h"

#endif
/*-- End Of File -------------------------------------------------------------------------------*/
