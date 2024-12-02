/* ADC-r04-303 */
/************************************************************************************************/
/*																								*/
/*		ADC Driver : Low Driver layer for RH850U2A/U2B											*/
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

#include "Adc_Pil.h"
#include "Reg_Adc.h"
#if (ADC_CFG_DEM_SET_EVENT==STD_ON)
#include "Rte_Dem_Type.h"
#endif
#if (ADC_CFG_HW_TRG_API==STD_ON)
#include "Reg_Pic2.h"
#endif

/*==============================================================================================*/
/* prototypes																					*/
/*==============================================================================================*/

/*==============================================================================================*/
/* defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/

/*--------------------------------------------------------------------------*/
/* define - register														*/
/*--------------------------------------------------------------------------*/
/* HW Trigger	*/
#define	ADC_TRGMD_MASK		(uint8)(~ADC_SGCR_TRGMD_SG3_4)
#define	ADC_TRGMD_ENABLE	(uint8)(ADC_SGCR_TRGMD_HARD*ADC_SGCR_TRGMD_SG0_2)
#define	ADC_TRGMD_DISABLE	(uint8)(ADC_SGCR_TRGMD_SOFT*ADC_SGCR_TRGMD_SG0_2)
/* THxCR	*/
#define	ADC_TH_HOLD_TRG_ENABLE	(uint8)(ADC_THACR_HLDTE_ENABLE		*ADC_THACR_HLDTE)		/* Group A and B common	*/


/*  Scan Group x Start Trigger Control Register 	: ADCXnSGTSELx	x:Scan Group0-4	*/
#define		ADC_SetSGTSEL(xSEL0,xSEL1,xSEL2,xSEL3)												\
	 ((uint32)(																					\
	    /*(uint32)(ADC_SGTSELX_TXSEL_SOFT	* ADC_SGTSELX_TXSEL_5)	* TxSEL5	:  	5		*/	\
	    /*(uint32)(ADC_SGTSELX_TXSEL_SOFT	* ADC_SGTSELX_TXSEL_4)	* TxSEL4	:  	4		*/	\
	   (uint32)(((xSEL3)==STD_ON) ?									/* TxSEL3	:  	3		*/	\
			(ADC_SGTSELX_TXSEL_HARD	* ADC_SGTSELX_TXSEL_3) :									\
			(ADC_SGTSELX_TXSEL_SOFT	* ADC_SGTSELX_TXSEL_3) )									\
	   +(uint32)(((xSEL2)==STD_ON) ?								/* TxSEL2	:  	2		*/	\
			(ADC_SGTSELX_TXSEL_HARD	* ADC_SGTSELX_TXSEL_2) :									\
			(ADC_SGTSELX_TXSEL_SOFT	* ADC_SGTSELX_TXSEL_2) )									\
	   +(uint32)(((xSEL1)==STD_ON) ?								/* TxSEL1	:  1		*/	\
			(ADC_SGTSELX_TXSEL_HARD	* ADC_SGTSELX_TXSEL_1) :									\
			(ADC_SGTSELX_TXSEL_SOFT	* ADC_SGTSELX_TXSEL_1) )									\
	   +(uint32)(((xSEL0)==STD_ON) ?								/* TxSEL0	:  0		*/	\
			(ADC_SGTSELX_TXSEL_HARD	* ADC_SGTSELX_TXSEL_0) :									\
			(ADC_SGTSELX_TXSEL_SOFT	* ADC_SGTSELX_TXSEL_0) )									\
	))
#if	(MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
	/*#define ADC_DFGTMENT		(uint32)(ADC_VCR_GTMENT_DISABLED * ADC_VCR_GTMENT)				* GTMENT	(U2A)				*/
	/*#define ADC_DFEGTMTAG		(uint32)((uint32)ADC_ZERO		 * ADC_VCR_GTMTAG_0)			* GTMTAG	(U2A)				*/
	#define	ADC_SPECIFIC_HWUNIT	(ADC_HWUNIT2)
#else
	/* #define ADC_DFGTMENT		(uint32)(ADC_VCR_DFENT_DISABLED * ADC_VCR_DFENT)				* DFENT	(U2B)					*/
	/* #define ADC_DFEGTMTAG		(uint32)(ADC_ZERO				* ADC_VCR_DFETAG_0) 		* DFETAG	(U2B)				*/
	#define	ADC_SPECIFIC_HWUNIT	(ADC_HWUNITA)
#endif
/*#define	ADC_VCR_NORMAL 																									\	*/
/*	((uint32) 																												\	*/
/*		 ((uint32)((uint32)ADC_VCR_VCULLMTBS_DISABLED * ADC_VCR_VCULLMTBS_0)					* VCULLMTBS :31 - 28		\	*/
/*		+(uint32)((uint32)ADC_VCR_WTTS_DISABLED * ADC_VCR_WTTS_0)								* WTTS		:27 - 24		\	*/
/*		+ADC_DFGTMENT																			*			:20				\	*/
/*		+ADC_DFEGTMTAG																			*			:19 - 16		\	*/
/*		 (uint32)((uint32)ADC_VCR_CNVCLS_NORMAL * ADC_VCR_CNVCLS_0)								* CNVCLSL	:14 - 11		\	*/
/*		+(uint32)((uint32)ADC_ZERO * ADC_VCR_MPXV_0)											* MPXV		:10 -  8		\	*/
/*		+(uint32)((uint32)ADC_VCR_ADIE_NOTOUTPUT * ADC_VCR_ADIE)								* ADIE		: 7				\	*/
/*	))	*/
#define	ADC_SGMCYCR	(uint8)(ADC_ZERO * ADC_SGMCYCR_MCYC_0)

#if	(MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A )
	#define	ADC_PWDCR	(uint8)(ADC_PWDCR_PWE_DISABLE * ADC_PWDCR_PWE)
#endif

#define		ADC_TH_AUTOSAMPLING																\
	 ((uint8)(																				\
		 (uint8)(ADC_THCR_ASMPMSK_AUTO * ADC_THCR_ASMPMSK)		/* ASMPMSK	:  0		*/	\
	))
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A)
	#define	ADC_TH_DISABLE																	\
	 ((uint8)(																				\
	    (uint8)(ADC_THER_THZE_DISABLE * ADC_THER_TH3E)			/* TH3E		:  3		*/	\
	   +(uint8)(ADC_THER_THZE_DISABLE * ADC_THER_TH2E)			/* TH2E		:  2		*/	\
	   +(uint8)(ADC_THER_THZE_DISABLE * ADC_THER_TH1E)			/* TH1E		:  1		*/	\
	   +(uint8)(ADC_THER_THZE_DISABLE * ADC_THER_TH0E)			/* TH0E		:  0		*/	\
	))
#else	/* MCAL_TARGET_RH850U2B	*/
	#define	ADC_TH_DISABLE																	\
	 ((uint8)(																				\
		(uint8)(ADC_THER_THZE_DISABLE * ADC_THER_TH5E)			/* TH5E		:  5		*/	\
	   +(uint8)(ADC_THER_THZE_DISABLE * ADC_THER_TH4E)			/* TH4E		:  4		*/	\
	   +(uint8)(ADC_THER_THZE_DISABLE * ADC_THER_TH3E)			/* TH3E		:  3		*/	\
	   +(uint8)(ADC_THER_THZE_DISABLE * ADC_THER_TH2E)			/* TH2E		:  2		*/	\
	   +(uint8)(ADC_THER_THZE_DISABLE * ADC_THER_TH1E)			/* TH1E		:  1		*/	\
	   +(uint8)(ADC_THER_THZE_DISABLE * ADC_THER_TH0E)			/* TH0E		:  0		*/	\
	))
#endif

#define ADC_TH_DISABLE_GRPA																	\
	 (uint8)((ADC_THACR_HLDCTE_DISABLE	* ADC_THACR_HLDCTE)									\
			+(ADC_THACR_HLDTE_DISABLE	* ADC_THACR_HLDTE)									\
			+(ADC_THACR_SGS_SG1			* ADC_THACR_SGS_0))
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	#define ADC_TH_DISABLE_GRPB																\
	 (uint8)((ADC_THBCR_HLDCTE_DISABLE	* ADC_THBCR_HLDCTE)									\
			+(ADC_THBCR_HLDTE_DISABLE	* ADC_THBCR_HLDTE)									\
			+(ADC_THBCR_SGS_SG1			* ADC_THBCR_SGS_0))
#endif

#ifdef ADC_USE_TH
#define	ADC_VCR_TH					(uint32)((uint32)ADC_VCR_CNVCLS_HOLD * ADC_VCR_CNVCLS_0)		/* CNVCLSL	:14 - 11						*/
#define ADC_TH_SAMPLING_START		(uint8)(ADC_THSMPSTCR_SMPST_START * ADC_THSMPSTCR_SMPST)
#endif
#define	ADC_ODD_EVE_JUDGE_MASK		((uint16)1U)													/* 15 - 2bit Mask							*/
#define	ADC_SGVCPR_EVENSET			((uint16)1U)													/* VCSP setting of SGVCPR for even channels	*/
#define	ADC_SGVCPR_ODDSET			((uint16)2U)													/* VCSP setting of SGVCPR for odd channels	*/

#if	(MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
#define	ADC_AIRISELR0_INIT_VALUE	((uint32)0x00000000u)
#define	ADC_AIRISELR1_INIT_VALUE	((uint32)0xff800000u)
#define	ADC_AIRDSELR0_INIT_VALUE	((uint32)0x0f000000u)
#define	ADC_AIRDSELR1_INIT_VALUE	((uint32)0xff800000u)
#endif

/*--------------------------------------------------------------------------*/
/* define - constant														*/
/*--------------------------------------------------------------------------*/
#define ADC_VCEP_CAL				((uint16)1U)													/* VCEP Calculation constants				*/

/*==============================================================================================*/
/* constants																					*/
/*==============================================================================================*/
/* config to register set value convert table	*/
#ifdef ADC_USE_TH
#define ADC_START_SEC_CONST_8
#include "Adc_MemMap.h"
static CONST(uint8, ADC_CONST) s_cu1THCnvSGTbl[ADC_SG_NUM] = {
	/* same as Group A and B		*/
	(ADC_THACR_SGS_SG1*ADC_THACR_SGS_0),							/* ADC_SG0	dummy(not use)	*/
	(ADC_THACR_SGS_SG1*ADC_THACR_SGS_0),							/* ADC_SG1					*/
	(ADC_THACR_SGS_SG2*ADC_THACR_SGS_0),							/* ADC_SG2					*/
	(ADC_THACR_SGS_SG3*ADC_THACR_SGS_0),							/* ADC_SG3					*/
	(ADC_THACR_SGS_SG4*ADC_THACR_SGS_0)								/* ADC_SG4					*/
};
#define ADC_STOP_SEC_CONST_8
#include "Adc_MemMap.h"
#endif

#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	#ifdef ADC_USE_TH
	#define ADC_START_SEC_CONST_16
	#include "Adc_MemMap.h"
	static CONST(uint16, ADC_CONST) s_cu2THCnvGrpBTbl[ADC_TH_NUM] = {
		(uint16)(ADC_THGSR_TH0GS_SELECTED_B*ADC_THGSR_TH0GS),		/* ADC_CH00					*/
		(uint16)(ADC_THGSR_TH1GS_SELECTED_B*ADC_THGSR_TH1GS),		/* ADC_CH01					*/
		(uint16)(ADC_THGSR_TH2GS_SELECTED_B*ADC_THGSR_TH2GS),		/* ADC_CH02					*/
		(uint16)(ADC_THGSR_TH3GS_SELECTED_B*ADC_THGSR_TH3GS),		/* ADC_CH03					*/
		(uint16)(ADC_THGSR_TH4GS_SELECTED_B*ADC_THGSR_TH4GS),		/* ADC_CH04					*/
		(uint16)(ADC_THGSR_TH5GS_SELECTED_B*ADC_THGSR_TH5GS)		/* ADC_CH05					*/
	};
	#define ADC_STOP_SEC_CONST_16
	#include "Adc_MemMap.h"
	#endif
#endif
	
/*==============================================================================================*/
/* variables																					*/
/*==============================================================================================*/

/*==============================================================================================*/
/* prototype for local functions																*/
/*==============================================================================================*/
#define ADC_START_SEC_CODE_GLOBAL
#include "Adc_MemMap.h"
static FUNC(void, ADC_CODE) Adc_Pil_RegVarInit(
	VAR(uint32,		ADC_VAR_NO_INIT)			t_u4VCR[ADC_HWUNIT_NUM][ADC_CHANNEL_NUM],
	VAR(uint32,		ADC_VAR_NO_INIT)			t_u4SGTSEL[ADC_SG_NUM],
	VAR(uint16,		ADC_VAR_NO_INIT)			t_u2SGVCPR[ADC_HWUNIT_NUM][ADC_SG_NUM],
	VAR(uint8,		ADC_VAR_NO_INIT)			t_u1SGCR[ADC_HWUNIT_NUM][ADC_SG_NUM]
	#ifdef ADC_USE_TH
	,VAR(uint8,		ADC_VAR_NO_INIT)			t_u1THxCR[ADC_HWUNIT_WTH_NUM][ADC_TH_GRP_NUM]
	,VAR(uint8, 	ADC_VAR_NO_INIT)			t_u1THSMPSTCR[ADC_HWUNIT_WTH_NUM]
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	,VAR(uint16,	ADC_VAR_NO_INIT)			t_u2THGSR[ADC_HWUNIT_WTH_NUM]
	#endif
	#endif
);

static FUNC(void, ADC_CODE) Adc_Pil_DataInit(
	VAR(uint32,		ADC_VAR_NO_INIT)			t_u4VCR[ADC_HWUNIT_NUM][ADC_CHANNEL_NUM],
	VAR(uint32,		ADC_VAR_NO_INIT)			t_u4SGTSEL[ADC_SG_NUM],
	VAR(uint16,		ADC_VAR_NO_INIT)			t_u2SGVCPR[ADC_HWUNIT_NUM][ADC_SG_NUM],
	VAR(uint8,		ADC_VAR_NO_INIT)			t_u1SGCR[ADC_HWUNIT_NUM][ADC_SG_NUM]
	#ifdef ADC_USE_TH
	,VAR(uint8,		ADC_VAR_NO_INIT)			t_u1THxCR[ADC_HWUNIT_WTH_NUM][ADC_TH_GRP_NUM]
	,VAR(uint8,		ADC_VAR_NO_INIT)			t_u1THSMPSTCR[ADC_HWUNIT_WTH_NUM]
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	,VAR(uint16,	ADC_VAR_NO_INIT)			t_u2THGSR[ADC_HWUNIT_WTH_NUM]
	#endif
	#endif
);
static FUNC(void, ADC_CODE) Adc_Pil_SetSGVCPR(
	VAR(uint16,				ADC_VAR_NO_INIT)	t_u2SGVCPR[ADC_HWUNIT_NUM][ADC_SG_NUM],
	CONST(Adc_GroupType,	ADC_CONST)			t_cudGrp,
	CONST(uint16,			ADC_CONST)			t_cu2VCSP,
	CONST(uint16,			ADC_CONST)			t_cu2VCEP
);
static FUNC(void, ADC_CODE) Adc_Pil_SetSGCR(
	VAR(uint8,				ADC_VAR_NO_INIT)	t_u1SGCR[ADC_HWUNIT_NUM][ADC_SG_NUM],
	CONST(Adc_GroupType,	ADC_CONST)			t_cudGrp
);
static FUNC(void, ADC_CODE) Adc_Pil_SetVCR(
	VAR(uint32,				ADC_VAR_NO_INIT)	t_u4VCR[ADC_HWUNIT_NUM][ADC_CHANNEL_NUM],
	CONST(Adc_GroupType,	ADC_CONST)			t_cudGrp,
	CONST(uint16,			ADC_CONST)			t_cu2VCSP
);
static FUNC(void, ADC_CODE) Adc_Pil_CrctVCEP(
	VAR(uint16, 			ADC_VAR_NO_INIT)	t_u2CrntVChNbr[ADC_HWUNIT_NUM],
	CONST(Adc_GroupType,	ADC_CONST)			t_cudGrp,
	CONST(uint16,			ADC_CONST)			t_cu2VCEP
);
static FUNC(void, ADC_CODE) Adc_Pil_SetSGTSEL(
	VAR(uint32,				ADC_VAR_NO_INIT)	t_u4SGTSEL[ADC_SG_NUM],
	CONST(Adc_GroupType,	ADC_CONST)			t_cudGrp
);

#if ((ADC_CFG_START_STOP_GRP_API==STD_ON) || (ADC_CFG_READ_GRP_API==STD_ON) || (ADC_CFG_HW_TRG_API==STD_ON) || defined (ADC_USE_DMA))
static FUNC(uint16, ADC_CODE) Adc_Pil_GetVCStartPos(
	CONST(Adc_HWUnitType,	ADC_CONST)	t_cudHWUnit,
	CONST(Adc_SGType,		ADC_CONST)	t_cudSG
);
#endif

static FUNC(uint16, ADC_CODE) Adc_Pil_GetVCEndPos(
	CONST(Adc_HWUnitType,	ADC_CONST)	t_cudHWUnit,
	CONST(Adc_SGType,		ADC_CONST)	t_cudSG
);

#if (ADC_CFG_REG_CHK==STD_ON)
static FUNC(uint32, ADC_CODE) Adc_Pil_RegchkPreFix(
	CONST(Adc_GroupType,	ADC_CONST)	t_cudGrp,
	CONST(Adc_HWUnitType,	ADC_CONST)	t_cudHWUnit,
	CONST(Adc_SGType,		ADC_CONST)	t_cudSG
);
static FUNC(uint32, ADC_CODE) Adc_Pil_RegchkPreFixADCR1(
	CONST(Adc_HWUnitType,	ADC_CONST)	t_cudHWUnit
);
static FUNC(uint32, ADC_CODE) Adc_Pil_RegchkPreFixADCR2(
	CONST(Adc_HWUnitType,	ADC_CONST)	t_cudHWUnit
);
static FUNC(uint32, ADC_CODE) Adc_Pil_RegchkPreFixSMPCR(
	CONST(Adc_HWUnitType,	ADC_CONST)	t_cudHWUnit
);
static FUNC(uint32, ADC_CODE) Adc_Pil_RegchkPreFixSGMCYCR(
	CONST(Adc_GroupType,	ADC_CONST)	t_cudGrp,
	CONST(Adc_HWUnitType,	ADC_CONST)	t_cudHWUnit,
	CONST(Adc_SGType,		ADC_CONST)	t_cudSG
);
static FUNC(uint32, ADC_CODE) Adc_Pil_RegchkPreFixTHER(
	CONST(Adc_HWUnitType,	ADC_CONST)	t_cudHWUnit
);
static FUNC(uint32, ADC_CODE) Adc_Pil_RegchkPostFix(
	CONST(Adc_GroupType,	ADC_CONST)			t_cudGrp,
	CONST(Adc_HWUnitType,	ADC_CONST)			t_cudHWUnit,
	CONST(Adc_SGType,		ADC_CONST)			t_cudSG,
	VAR(uint32,				ADC_VAR_NO_INIT)	t_u4VCR[ADC_HWUNIT_NUM][ADC_CHANNEL_NUM],
	VAR(uint32,				ADC_VAR_NO_INIT)	t_u4SGTSEL[ADC_SG_NUM],
	VAR(uint16,				ADC_VAR_NO_INIT)	t_u2SGVCPR[ADC_HWUNIT_NUM][ADC_SG_NUM]
	#ifdef ADC_USE_TH
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	,VAR(uint16,			ADC_VAR_NO_INIT)	t_u2THGSR[ADC_HWUNIT_WTH_NUM]
	#endif
	#endif
);

static FUNC(uint32, ADC_CODE) Adc_Pil_RegchkDynamic(
	CONST(Adc_GroupType,	ADC_CONST)			t_cudGrp,
	CONST(Adc_HWUnitType,	ADC_CONST)			t_cudHWUnit,
	CONST(Adc_SGType,		ADC_CONST)			t_cudSG
	#ifdef ADC_USE_TH
	,VAR(uint8,				ADC_VAR_NO_INIT)	t_u1THxCR[ADC_HWUNIT_WTH_NUM][ADC_TH_GRP_NUM]
	#endif
);
static FUNC(uint32, ADC_CODE) Adc_Pil_RegchkDynamicSGCR(
	CONST(Adc_GroupType,	ADC_CONST)			t_cudGrp,
	CONST(Adc_HWUnitType,	ADC_CONST)			t_cudHWUnit,
	CONST(Adc_SGType,		ADC_CONST)			t_cudSG
);
#ifdef ADC_USE_TH
static FUNC(uint32, ADC_CODE) Adc_Pil_RegchkDynamicTHxCR(
	CONST(Adc_GroupType,	ADC_CONST)			t_cudGrp,
	CONST(Adc_HWUnitType,	ADC_CONST)			t_cudHWUnit,
	VAR(uint8,				ADC_VAR_NO_INIT)	t_u1THxCR[ADC_HWUNIT_WTH_NUM][ADC_TH_GRP_NUM]
);
#endif

static FUNC(void, ADC_CODE) Adc_Pil_RegchkCalExpctValue(
	CONST(boolean,			ADC_CONST)			t_cblisAllRegCheck,
	CONST(Adc_HWUnitType,	ADC_CONST)			t_cudHWUnit,
	VAR(uint32,				ADC_VAR_NO_INIT)	t_u4VCR[ADC_HWUNIT_NUM][ADC_CHANNEL_NUM],
	VAR(uint32,				ADC_VAR_NO_INIT)	t_u4SGTSEL[ADC_SG_NUM],
	VAR(uint16,				ADC_VAR_NO_INIT)	t_u2SGVCPR[ADC_HWUNIT_NUM][ADC_SG_NUM]
	#ifdef ADC_USE_TH
	,VAR(uint8,				ADC_VAR_NO_INIT)	t_u1THxCR[ADC_HWUNIT_WTH_NUM][ADC_TH_GRP_NUM]
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	,VAR(uint16,			ADC_VAR_NO_INIT)	t_u2THGSR[ADC_HWUNIT_WTH_NUM]
	#endif
	#endif
);
static FUNC(void, ADC_CODE) Adc_Pil_RegchkVarInit(
	CONST(boolean,				ADC_CONST)			t_cblisAllRegCheck,
	CONST(Adc_HWUnitType,		ADC_CONST)			t_cudHWUnit,
	VAR(uint16, 				ADC_VAR_NO_INIT)	t_u2CrntVChNbr[ADC_HWUNIT_NUM]
	#ifdef ADC_USE_TH
	,VAR(uint16,				ADC_VAR_NO_INIT)	t_u2VCStartPos[ADC_CFG_GRP_SIZE],
	VAR(Adc_GroupType,			ADC_VAR_NO_INIT)	t_udTHGrpId[ADC_HWUNIT_WTH_NUM][ADC_TH_GRP_NUM],
	VAR(uint8, 					ADC_VAR_NO_INIT)	t_u1THGrpCount[ADC_HWUNIT_WTH_NUM]
	#endif
);
#endif

#define ADC_STOP_SEC_CODE_GLOBAL
#include "Adc_MemMap.h"

/*----------------------------------------------------------------------------------------------*/
/* API Functions																				*/
/*----------------------------------------------------------------------------------------------*/
#define ADC_START_SEC_CODE_GLOBAL
#include "Adc_MemMap.h"

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
FUNC(void, ADC_CODE) Adc_Pil_Init(void)
{
				VAR(Adc_HWUnitType,						ADC_VAR_NO_INIT)	t_udHWUnit;
				VAR(Adc_SGType,							ADC_VAR_NO_INIT)	t_udSG;
				VAR(sint32,								ADC_VAR_NO_INIT)	t_s4VChNbr;
				VAR(uint32,								ADC_VAR_NO_INIT)	t_u4VCR[ADC_HWUNIT_NUM][ADC_CHANNEL_NUM];
				VAR(uint32,								ADC_VAR_NO_INIT)	t_u4SGTSEL[ADC_SG_NUM];
	volatile	VAR(uint32,								ADC_VAR_NO_INIT)	t_u4DIR;
				VAR(uint16,								ADC_VAR_NO_INIT)	t_u2SGVCPR[ADC_HWUNIT_NUM][ADC_SG_NUM];
				VAR(uint8, 								ADC_VAR_NO_INIT)	t_u1SGCR[ADC_HWUNIT_NUM][ADC_SG_NUM];
				#if	(MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A)
	volatile	P2VAR(Reg_Adc_SELB_Type,	AUTOMATIC,	ADC_VAR_NO_INIT)	t_pstSELBReg;
				#endif
				#ifdef ADC_USE_TH
				VAR(uint8,								ADC_VAR_NO_INIT)	t_u1THxCR[ADC_HWUNIT_WTH_NUM][ADC_TH_GRP_NUM];
				VAR(uint8, 								ADC_VAR_NO_INIT)	t_u1THSMPSTCR[ADC_HWUNIT_WTH_NUM];
				#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
				VAR(uint16, ADC_VAR_NO_INIT)								t_u2THGSR[ADC_HWUNIT_WTH_NUM];
				#endif
				#endif

	Adc_Pil_RegVarInit(t_u4VCR, t_u4SGTSEL, t_u2SGVCPR, t_u1SGCR
		#ifdef ADC_USE_TH
		,t_u1THxCR, t_u1THSMPSTCR
		#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
		,t_u2THGSR
		#endif
		#endif
	);
	Adc_Pil_DataInit(t_u4VCR, t_u4SGTSEL, t_u2SGVCPR, t_u1SGCR
		#ifdef ADC_USE_TH
		,t_u1THxCR, t_u1THSMPSTCR
		#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
		,t_u2THGSR
		#endif
		#endif
	);
	for (t_udHWUnit=ADC_HWUNIT0;t_udHWUnit<(Adc_HWUnitType)ADC_HWUNIT_NUM;t_udHWUnit++) {
		cpstReg_Adc[t_udHWUnit]->stMODULE.u1ADCR1	= Adc_cstUserConfig.cpstHWConfig->cu1ADCR1[t_udHWUnit];
		cpstReg_Adc[t_udHWUnit]->stMODULE.u1ADCR2	= Adc_cstUserConfig.cpstHWConfig->cu1ADCR2[t_udHWUnit];
		cpstReg_Adc[t_udHWUnit]->stMODULE.u4SMPCR	= Adc_cstUserConfig.cpstHWConfig->cu4SMPCR[t_udHWUnit];
		#if !((MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B) && ((MCAL_PKG_TARGET==MCAL_PKG_U2B10_292PIN) || (MCAL_PKG_TARGET==MCAL_PKG_U2B6_292PIN)))
		if (t_udHWUnit<ADC_HWUNIT_WTH_NUM) {
		#endif
			#ifdef ADC_USE_TH
		 		cpstReg_Adc[t_udHWUnit]->stMODULE.u1THCR	= ADC_TH_AUTOSAMPLING;
				#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
				cpstReg_Adc[t_udHWUnit]->stMODULE.u2THGSR	= t_u2THGSR[t_udHWUnit];
				#endif
				cpstReg_Adc[t_udHWUnit]->stMODULE.u1THER	= Adc_cstUserConfig.cpstHWConfig->cu1THER[t_udHWUnit];
			#else
				cpstReg_Adc[t_udHWUnit]->stMODULE.u1THER	= ADC_TH_DISABLE;
			#endif
		#if !((MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B) && ((MCAL_PKG_TARGET==MCAL_PKG_U2B10_292PIN) || (MCAL_PKG_TARGET==MCAL_PKG_U2B6_292PIN)))
		}
		#endif
		/* SGVCPR, SGMCYCR	*/
		for (t_udSG=ADC_SG0;t_udSG<(Adc_SGType)ADC_SG_NUM;t_udSG++) {
			cpstReg_Adc[t_udHWUnit]->stMODULE.stSG[t_udSG].u2SGVCPR		= t_u2SGVCPR[t_udHWUnit][t_udSG];
			cpstReg_Adc[t_udHWUnit]->stMODULE.stSG[t_udSG].u1SGMCYCR	= ADC_SGMCYCR;
		}
		/* VCR, DIR	*/
		for ( t_s4VChNbr=0; t_s4VChNbr < (sint32)ADC_CHANNEL_NUM; t_s4VChNbr++ ) {
			cpstReg_Adc[t_udHWUnit]->stMODULE.u4VCR[t_s4VChNbr] = t_u4VCR[t_udHWUnit][t_s4VChNbr];
			t_u4DIR = cpstReg_Adc[t_udHWUnit]->stMODULE.u4DIR[t_s4VChNbr];
		}
		/* THxCR*/
		#if !((MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B) && ((MCAL_PKG_TARGET==MCAL_PKG_U2B10_292PIN) || (MCAL_PKG_TARGET==MCAL_PKG_U2B6_292PIN)))
		if (t_udHWUnit<ADC_HWUNIT_WTH_NUM) {
		#endif
			#ifdef ADC_USE_TH
				cpstReg_Adc[t_udHWUnit]->stMODULE.u1THACR	= Adc_cstUserConfig.cpstHWConfig->cu1THACR[t_udHWUnit] | t_u1THxCR[t_udHWUnit][ADC_TH_GRP_A];
				#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
				cpstReg_Adc[t_udHWUnit]->stMODULE.u1THBCR	= Adc_cstUserConfig.cpstHWConfig->cu1THBCR[t_udHWUnit] | t_u1THxCR[t_udHWUnit][ADC_TH_GRP_B];
				#endif
			#else	/* #ifdef ADC_USE_TH	*/
				cpstReg_Adc[t_udHWUnit]->stMODULE.u1THACR	= ADC_TH_DISABLE_GRPA;
				#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
				cpstReg_Adc[t_udHWUnit]->stMODULE.u1THBCR	= ADC_TH_DISABLE_GRPB;
				#endif
			#endif
		#if !((MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B) && ((MCAL_PKG_TARGET==MCAL_PKG_U2B10_292PIN) || (MCAL_PKG_TARGET==MCAL_PKG_U2B6_292PIN)))
		}
		#endif
		/* PWDCR	*/
		#if	(MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
		cpstReg_Adc[t_udHWUnit]->stMODULE.u1PWDCR	= ADC_PWDCR;
		#endif
		/* SGCR	*/
		for (t_udSG=ADC_SG0;t_udSG<(Adc_SGType)ADC_SG_NUM;t_udSG++) {
			cpstReg_Adc[t_udHWUnit]->stMODULE.stSG[t_udSG].u1SGCR		= t_u1SGCR[t_udHWUnit][t_udSG];
		}

		/* THSMPSTCR	@notice First conversion (including after selfdiagnosis) 10us */
		#ifdef ADC_USE_TH
		#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A)
		if (t_udHWUnit<ADC_HWUNIT_WTH_NUM) {
		#endif
			cpstReg_Adc[t_udHWUnit]->stMODULE.u1THSMPSTCR =  t_u1THSMPSTCR[t_udHWUnit];
		#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A)
		}
		#endif
		#endif
	}

	#if	(MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
	/* SGTSEL	*/
	t_pstSELBReg = cpstReg_SELB_Adc[ADC_ZERO];
	for (t_udSG=ADC_SG0;t_udSG<(Adc_SGType)ADC_SG_NUM;t_udSG++) {
		t_pstSELBReg->u4SGTSEL[t_udSG]	= t_u4SGTSEL[t_udSG];
	}
	#endif

	#if	(MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	/* AIR interrupt	*/
	Reg_AIR.u4AIRISELR0 = ADC_AIRISELR0_INIT_VALUE;
	Reg_AIR.u4AIRISELR1 = ADC_AIRISELR1_INIT_VALUE;
	/* AIR DMA			*/
	Reg_AIR.u4AIRDSELR0 = ADC_AIRDSELR0_INIT_VALUE;
	Reg_AIR.u4AIRDSELR1 = ADC_AIRDSELR1_INIT_VALUE;
	#endif
}

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
/* Description			: Starts the conversion of the requested HW Unit and Scan Group			*/
/************************************************************************************************/
#if (ADC_CFG_START_STOP_GRP_API==STD_ON)
FUNC(void, ADC_CODE) Adc_Pil_StartConversion(
	CONST(Adc_HWUnitType,	ADC_CONST)	t_cudHWUnit,
	CONST(Adc_SGType,		ADC_CONST)	t_cudSG
)
{
	cpstReg_Adc[t_cudHWUnit]->stMODULE.stSG[t_cudSG ].u1SGSTCR
		= (uint8)(ADC_SGSTCR_SGST_SCAN_START*ADC_SGSTCR_SGST);
}
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
/* Description			: Stops the conversion of the requested HW Unit and Scan Group			*/
/************************************************************************************************/
#if ((ADC_CFG_START_STOP_GRP_API==STD_ON) || (ADC_CFG_HW_TRG_API==STD_ON))
FUNC(void, ADC_CODE) Adc_Pil_StopGroupConversion(
	CONST(Adc_HWUnitType,	ADC_CONST)	t_cudHWUnit,
	CONST(Adc_SGType,		ADC_CONST)	t_cudSG
)
{
	VAR(uint8,	ADC_VAR_NO_INIT)	t_u1SGSR;
	#if (ADC_CFG_PROCESS_TIMEOUT!=0xffffffffu)
	VAR(uint32, ADC_VAR_NO_INIT)	t_u4ReadCnt;
	#endif

	/* stop conversion				*/
	cpstReg_Adc[t_cudHWUnit]->stMODULE.stSG[t_cudSG].u1SGSTPCR
		= (uint8)(ADC_SGSTPCR_SGST_SCAN_STOP*ADC_SGSTPCR_SGSTP);


	/* wait until conversion stop	*/
	#if (ADC_CFG_PROCESS_TIMEOUT!=0xffffffffu)
	t_u4ReadCnt = (uint32)ADC_ZERO;
	#endif
	while(1) {
		t_u1SGSR = cpstReg_Adc[t_cudHWUnit]->stMODULE.stSG[t_cudSG].u1SGSR & (uint8)(ADC_SGSR_SGACT);
		if (t_u1SGSR==(uint8)ADC_ZERO) {
			break;
		}
		#if (ADC_CFG_PROCESS_TIMEOUT!=0xffffffffu)
		if (t_u4ReadCnt<(uint32)ADC_CFG_PROCESS_TIMEOUT) {
			t_u4ReadCnt++;
		} else {
			#if (ADC_CFG_DEM_SET_EVENT==STD_ON)
			(void)Dem_SetEventStatus(ADC_CFG_E_TIMEOUT_ERROR,DEM_EVENT_STATUS_FAILED);
			#endif
			break;
		}
		#endif
	}
}
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
)
{
	VAR(uint8,	ADC_VAR_NO_INIT)		t_u1SGCR;


	t_u1SGCR	= cpstReg_Adc[t_cudHWUnit]->stMODULE.stSG[t_cudSG].u1SGCR;

	if ((t_cu1StreamingAcces==(uint8)STD_ON) || (t_cu1DMA==(uint8)STD_ON)) {
		t_u1SGCR	|= (uint8)(ADC_SGCR_ADIE);
	} else {
		/* single access mode & DMA Off	*/
		if (t_cu1IntrptUse==(uint8)STD_ON) {
			/* interrupt enable			*/
			t_u1SGCR	|= (uint8)(ADC_SGCR_ADIE);
		} else {
			/* interrupt disable		*/
			t_u1SGCR	&= ~((uint8)ADC_SGCR_ADIE);
		}
	}
	cpstReg_Adc[t_cudHWUnit]->stMODULE.stSG[t_cudSG].u1SGCR = t_u1SGCR;
}
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
)
{
	VAR(uint16, ADC_VAR_NO_INIT)				i;
	VAR(uint32, ADC_VAR_NO_INIT)				t_u4DIR;
	VAR(uint16, ADC_VAR_NO_INIT)				t_u2VCStartPos;
	VAR(uint16, ADC_VAR_NO_INIT)				t_u2VCEndPos;

	t_u2VCStartPos	= Adc_Pil_GetVCStartPos(t_cudHWUnit,t_cudSG);
	t_u2VCEndPos	= t_u2VCStartPos + t_cu2CnvChSize - ADC_VCEP_CAL;

	for(i=t_u2VCStartPos; i<=t_u2VCEndPos; i++) {
		t_u4DIR = cpstReg_Adc[t_cudHWUnit]->stMODULE.u4DIR[i];
		t_pudDataBuffer[i-t_u2VCStartPos] = (Adc_ValueGroupType)(uint16)(t_u4DIR & (uint32)ADC_DIR_DR);
	}
}
#endif

/************************************************************************************************/
/* Service name			: Adc_Pil_IsCnvCompleted												*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/* 		Adc_HWUnitType	: HW Unit Number														*/
/* 		Adc_SGType		: Scan Group Number														*/
/* 		uin8			: convert channel size													*/
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
)
{
	VAR(uint32,		ADC_VAR_NO_INIT)				t_u4DIR;
	VAR(uint16,		ADC_VAR_NO_INIT)				t_u2VCEndPos;
	VAR(boolean,	ADC_VAR_NO_INIT)				t_blisComplete;

	t_u2VCEndPos	= Adc_Pil_GetVCEndPos(t_cudHWUnit,t_cudSG);
	t_u4DIR			= cpstReg_Adc[t_cudHWUnit]->stMODULE.u4DIR[t_u2VCEndPos] & (uint32)ADC_DIR_WFLAG;
	t_blisComplete	= FALSE;
	if ( (ADC_DIR_WFLAG_SET * ADC_DIR_WFLAG) == t_u4DIR ) {
		/* Not Storing A/D conversion value in ADCXnDRj	*/
		t_blisComplete	= TRUE;
	}
	return(t_blisComplete );
}

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
)
{
	VAR(uint8, ADC_VAR_NO_INIT)				t_u1HWTrg;

	t_u1HWTrg = (uint8)ADC_TRGMD_DISABLE;
	if (t_cblisHWTriggerOn==TRUE) {
		t_u1HWTrg = (uint8)ADC_TRGMD_ENABLE;
	}
	cpstReg_Adc[t_cudHWUnit]->stMODULE.stSG[t_cudSG].u1SGCR =
		(cpstReg_Adc[t_cudHWUnit]->stMODULE.stSG[t_cudSG].u1SGCR & ADC_TRGMD_MASK)+t_u1HWTrg;
}
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
)
{
	volatile	VAR(uint32,	ADC_VAR_NO_INIT)	t_u4DIR;
				VAR(uint16,	ADC_VAR_NO_INIT)	t_u2VCSP;
				VAR(uint16,	ADC_VAR_NO_INIT)	t_u2VCEP;
				VAR(uint16,	ADC_VAR_NO_INIT)	t_u2VChNbr;

	t_u2VCSP = Adc_Pil_GetVCStartPos(t_cudHWUnit, t_cudSG);
	t_u2VCEP = Adc_Pil_GetVCEndPos(t_cudHWUnit, t_cudSG);

	for (t_u2VChNbr = t_u2VCSP; t_u2VChNbr <= t_u2VCEP; t_u2VChNbr++) {
		t_u4DIR = cpstReg_Adc[t_cudHWUnit]->stMODULE.u4DIR[t_u2VChNbr];
	}
}
#endif

/************************************************************************************************/
/* Service name			: Adc_Pil_DisableSGHWTrigger											*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: None																	*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Disable Track & Hpld Sampling (call by DeInit only)					*/
/************************************************************************************************/
#if (ADC_CFG_DEINIT_API==STD_ON)
FUNC(void, ADC_CODE) Adc_Pil_DisableSGHWTrigger(void)
{
	VAR(Adc_HWUnitType,	ADC_VAR_NO_INIT)		t_udHWUnit;
	VAR(Adc_SGType,		ADC_VAR_NO_INIT)		t_udSG;

	for (t_udHWUnit=ADC_HWUNIT0;t_udHWUnit<(Adc_HWUnitType)ADC_HWUNIT_NUM;t_udHWUnit++) {
		for (t_udSG=ADC_SG0;t_udSG<ADC_SG_NUM;t_udSG++) {
			cpstReg_Adc[t_udHWUnit]->stMODULE.stSG[t_udSG].u1SGCR &= ADC_TRGMD_MASK;
		}
	}
}
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
)
{
	VAR(uint16, ADC_VAR_NO_INIT)	t_u2VCStartPos;

	t_u2VCStartPos	= Adc_Pil_GetVCStartPos(t_cudHWUnit,t_cudSG);
	return((volatile uint16*)&(cpstReg_Adc[t_cudHWUnit]->stMODULE.u2DR[t_u2VCStartPos]));
}
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
/* Description			: Start Track & Hpld Sampling											*/
/************************************************************************************************/
#ifdef ADC_USE_TH
FUNC(void, ADC_CODE) Adc_Pil_StartTrackHold(
	CONST(Adc_HWUnitType,			ADC_CONST)	t_cudHWUnit,
	CONST(Adc_TrackHoldGroupType,	ADC_CONST)	t_cudTHGrp
)
{
	volatile	P2VAR(uint8,	AUTOMATIC,	ADC_VAR_NO_INIT)		t_pu1THxCR;
				VAR(uint8,					ADC_VAR_NO_INIT)		t_u1THxCR;

	t_pu1THxCR = &(cpstReg_Adc[t_cudHWUnit]->stMODULE.u1THACR);
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	if (t_cudTHGrp==ADC_TH_GRP_B) {
		t_pu1THxCR = &(cpstReg_Adc[t_cudHWUnit]->stMODULE.u1THBCR);
	}
	#endif

	t_u1THxCR 	= *t_pu1THxCR;
	t_u1THxCR  |= ADC_TH_HOLD_TRG_ENABLE;
	*t_pu1THxCR	= t_u1THxCR;
}
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
/* Description			: Stop Track & Hpld Sampling											*/
/************************************************************************************************/
#ifdef ADC_USE_TH
FUNC(void, ADC_CODE) Adc_Pil_StopTrackHold(
    CONST(Adc_HWUnitType,           ADC_CONST)  t_cudHWUnit,
    CONST(Adc_TrackHoldGroupType,   ADC_CONST)  t_cudTHGrp
)
{
    #define     ADC_TH_HOLD_TRG_DISABLE (uint8)(~ADC_THACR_HLDTE)       /* Group A and B common */
    volatile    P2VAR(uint8,    AUTOMATIC,  ADC_VAR_NO_INIT)        t_pu1THxCR;
                VAR(uint8,                  ADC_VAR_NO_INIT)        t_u1THxCR;

    t_pu1THxCR = &(cpstReg_Adc[t_cudHWUnit]->stMODULE.u1THACR);
    #if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
    if (t_cudTHGrp==ADC_TH_GRP_B) {
        t_pu1THxCR = &(cpstReg_Adc[t_cudHWUnit]->stMODULE.u1THBCR);
    }
    #endif

    t_u1THxCR   = *t_pu1THxCR;
    t_u1THxCR  &= ADC_TH_HOLD_TRG_DISABLE;
    *t_pu1THxCR = t_u1THxCR;
}
#endif

/************************************************************************************************/
/* Service name			: Adc_Pil_DisableAllTHTrigger											*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: None																	*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Disable Track & Hpld Trigger (call by DeInit only)					*/
/************************************************************************************************/
#if (ADC_CFG_DEINIT_API==STD_ON)
#ifdef ADC_USE_TH
FUNC(void, ADC_CODE) Adc_Pil_DisableAllTHTrigger(void)
{
	#define		ADC_TH_GRPA_TRG_MASK			(uint8)(~ADC_THACR_HLDTE)
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	#define		ADC_TH_GRPB_TRG_MASK			(uint8)(~ADC_THBCR_HLDTE)
	#endif

	VAR(Adc_HWUnitType,				ADC_VAR_NO_INIT)	t_udHWUnit;
	VAR(uint8,						ADC_VAR_NO_INIT)	t_u1THxCR;

	for (t_udHWUnit=ADC_HWUNIT0;t_udHWUnit<ADC_HWUNIT_WTH_NUM;t_udHWUnit++) {
		/* Group A	*/
		t_u1THxCR = cpstReg_Adc[t_udHWUnit]->stMODULE.u1THACR;
		t_u1THxCR  &= ADC_TH_GRPA_TRG_MASK;
		cpstReg_Adc[t_udHWUnit]->stMODULE.u1THACR = t_u1THxCR;
		#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
		/* Group B	*/
		t_u1THxCR = cpstReg_Adc[t_udHWUnit]->stMODULE.u1THBCR;
		t_u1THxCR  &= ADC_TH_GRPB_TRG_MASK;
		cpstReg_Adc[t_udHWUnit]->stMODULE.u1THBCR = t_u1THxCR;
		#endif
	}
}
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
/* Description			: Stop Track & Hpld Sampling (call by DeInit only)						*/
/************************************************************************************************/
#if (ADC_CFG_DEINIT_API==STD_ON)
#ifdef ADC_USE_TH
FUNC(void, ADC_CODE) Adc_Pil_StopAllTrackHold(void)
{
	#define	ADC_STOP_TH		(uint8)(ADC_THSTPCR_THSTP_STOP * ADC_THSTPCR_THSTP)

	VAR(Adc_HWUnitType, ADC_VAR_NO_INIT)	t_udHWUnit;

	for ( t_udHWUnit=ADC_HWUNIT0;t_udHWUnit<(Adc_HWUnitType)ADC_HWUNIT_WTH_NUM; t_udHWUnit++) {
		cpstReg_Adc[t_udHWUnit]->stMODULE.u1THSTPCR = ADC_STOP_TH;
	}
}
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
/* Description			: Stop Track & Hpld Sampling (call by DeInit only)						*/
/************************************************************************************************/
#if (ADC_CFG_DEINIT_API==STD_ON)
#ifdef ADC_USE_TH
FUNC(void, ADC_CODE) Adc_Pil_DisableAllTHOperation(void)
{
	VAR(Adc_HWUnitType, ADC_VAR_NO_INIT)	t_udHWUnit;

	for ( t_udHWUnit=ADC_HWUNIT0;t_udHWUnit<(Adc_HWUnitType)ADC_HWUNIT_WTH_NUM; t_udHWUnit++) {
		cpstReg_Adc[t_udHWUnit]->stMODULE.u1THER = ADC_TH_DISABLE;
	}
}
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
FUNC(void, ADC_CODE) Adc_Pil_ForcedTermination(void)
{
	#define		ADC_HALT	(uint8)(ADC_ADHALTR_HALT_SCAN_HALT * ADC_ADHALTR_HALT)

	VAR(Adc_HWUnitType, ADC_VAR_NO_INIT)	t_udHWUnit;

	for (t_udHWUnit=ADC_HWUNIT0;t_udHWUnit<(Adc_HWUnitType)ADC_HWUNIT_NUM;t_udHWUnit++) {
		cpstReg_Adc[t_udHWUnit]->stMODULE.u1ADHALTR = ADC_HALT;
	}
}
#endif

/*--------------------------------------------------------------------------*/
/* only when register check is  available									*/
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
/*		(following is availabel when ADC_CFG_REG_REFRESH is STD_ON)								*/
/* 		ADC_REGCHK_REFRESH_SUCCESS		: Error detected but refresh is success					*/
/* 		ADC_REGCHK_REFRESH_IMPOSSIBLE	: Error detected for unrefreshable register	 			*/
/* 		ADC_REGCHK_REFRESH_FAILED		: Error detected and refresh failed			 			*/
/* Description			: Check all registers and refresh ones w expected value.				*/
/************************************************************************************************/
FUNC(uint32, ADC_CODE) Adc_Pil_Regchk_All(void)
{
	VAR(uint32,			ADC_VAR_NO_INIT)	t_u4ChkResult;
	VAR(Adc_GroupType, 	ADC_VAR_NO_INIT) 	t_udGrp;
	VAR(Adc_HWUnitType,	ADC_VAR_NO_INIT)	t_udHWUnit;
	VAR(Adc_SGType,		ADC_VAR_NO_INIT) 	t_udSG;
	VAR(boolean,		ADC_VAR_NO_INIT)	t_blisAllRegCheck;
	VAR(uint32,			ADC_VAR_NO_INIT)	t_u4VCR[ADC_HWUNIT_NUM][ADC_CHANNEL_NUM];
	VAR(uint32,			ADC_VAR_NO_INIT)	t_u4SGTSEL[ADC_SG_NUM];
	VAR(uint16,			ADC_VAR_NO_INIT)	t_u2SGVCPR[ADC_HWUNIT_NUM][ADC_SG_NUM];
	#ifdef ADC_USE_TH
	VAR(uint8,			ADC_VAR_NO_INIT)	t_u1THxCR[ADC_HWUNIT_WTH_NUM][ADC_TH_GRP_NUM];
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	VAR(uint16,			ADC_VAR_NO_INIT)	t_u2THGSR[ADC_HWUNIT_WTH_NUM];
	#endif
	#endif

	t_blisAllRegCheck 	= TRUE;
	t_udHWUnit			= ADC_HWUNIT_NUM;		/* dummy value	*/
	Adc_Pil_RegchkCalExpctValue(t_blisAllRegCheck,t_udHWUnit,t_u4VCR,t_u4SGTSEL,t_u2SGVCPR
		#ifdef ADC_USE_TH
		,t_u1THxCR
		#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
		,t_u2THGSR
		#endif
		#endif
	);
	t_u4ChkResult	= ADC_REGCHK_OK;
	for (t_udGrp=ADC_GRP00;t_udGrp<(Adc_GroupType)ADC_CFG_GRP_SIZE;t_udGrp++) {
		t_udHWUnit		= Adc_GetHWUnitID(t_udGrp);
		t_udSG			= Adc_GetSGID(t_udGrp);
		t_u4ChkResult  |= Adc_Pil_RegchkPreFix(t_udGrp,t_udHWUnit,t_udSG);
		t_u4ChkResult  |= Adc_Pil_RegchkPostFix(t_udGrp,t_udHWUnit,t_udSG,
												t_u4VCR, t_u4SGTSEL, t_u2SGVCPR
												#ifdef ADC_USE_TH
												#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
												,t_u2THGSR
												#endif
												#endif
												);
		t_u4ChkResult  |= Adc_Pil_RegchkDynamic(t_udGrp,t_udHWUnit,t_udSG
												#ifdef ADC_USE_TH
												,t_u1THxCR
												#endif
												);
	}
	return(t_u4ChkResult);
}
/************************************************************************************************/
/* Service name			: Adc_Pil_Regchk_Grp													*/
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
/* Description			: Check Group related registers and refresh ones w expected value.		*/
/************************************************************************************************/
FUNC(uint32, ADC_CODE) Adc_Pil_Regchk_Grp(
	CONST(Adc_GroupType,	ADC_CONST)	t_cudGrp
)
{
	VAR(uint32,			ADC_VAR_NO_INIT)	t_u4ChkResult;
	VAR(Adc_HWUnitType,	ADC_VAR_NO_INIT)	t_udHWUnit;
	VAR(Adc_SGType,		ADC_VAR_NO_INIT) 	t_udSG;
	VAR(boolean,		ADC_VAR_NO_INIT)	t_blisAllRegCheck;
	VAR(uint32,			ADC_VAR_NO_INIT)	t_u4VCR[ADC_HWUNIT_NUM][ADC_CHANNEL_NUM];
	VAR(uint32,			ADC_VAR_NO_INIT)	t_u4SGTSEL[ADC_SG_NUM];
	VAR(uint16,			ADC_VAR_NO_INIT)	t_u2SGVCPR[ADC_HWUNIT_NUM][ADC_SG_NUM];
	#ifdef ADC_USE_TH
	VAR(uint8,			ADC_VAR_NO_INIT)	t_u1THxCR[ADC_HWUNIT_WTH_NUM][ADC_TH_GRP_NUM];
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	VAR(uint16,			ADC_VAR_NO_INIT)	t_u2THGSR[ADC_HWUNIT_WTH_NUM];
	#endif
	#endif

	t_blisAllRegCheck 	= FALSE;
	t_udHWUnit			= Adc_GetHWUnitID(t_cudGrp);
	t_udSG				= Adc_GetSGID(t_cudGrp);
	Adc_Pil_RegchkCalExpctValue(t_blisAllRegCheck,t_udHWUnit,t_u4VCR,t_u4SGTSEL,t_u2SGVCPR
		#ifdef ADC_USE_TH
		,t_u1THxCR
		#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
		,t_u2THGSR
		#endif
		#endif
	);
	t_u4ChkResult  = Adc_Pil_RegchkPreFix(t_cudGrp,t_udHWUnit,t_udSG);
	t_u4ChkResult  |= Adc_Pil_RegchkPostFix(t_cudGrp,t_udHWUnit,t_udSG,
											t_u4VCR, t_u4SGTSEL, t_u2SGVCPR
											#ifdef ADC_USE_TH
											#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
											,t_u2THGSR
											#endif
											#endif
											);
	t_u4ChkResult  |= Adc_Pil_RegchkDynamic(t_cudGrp,t_udHWUnit,t_udSG
											#ifdef ADC_USE_TH
											,t_u1THxCR
											#endif
											);
	return(t_u4ChkResult);
}

/************************************************************************************************/
/* Service name			: Adc_Pil_RegchkPreFix													*/
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
/*		(following is availabel when ADC_CFG_REG_REFRESH is STD_ON)								*/
/* 		ADC_REGCHK_REFRESH_SUCCESS		: Error detected but refresh is success					*/
/* 		ADC_REGCHK_REFRESH_IMPOSSIBLE	: Error detected for unrefreshable register	 			*/
/* 		ADC_REGCHK_REFRESH_FAILED		: Error detected and refresh failed			 			*/
/* Description			: Check registers deceided by a configuration							*/
/************************************************************************************************/
static FUNC(uint32, ADC_CODE) Adc_Pil_RegchkPreFix(
	CONST(Adc_GroupType,	ADC_CONST)	t_cudGrp,
	CONST(Adc_HWUnitType,	ADC_CONST)	t_cudHWUnit,
	CONST(Adc_SGType,		ADC_CONST)	t_cudSG
)
{
	VAR(uint32,					ADC_VAR_NO_INIT)	t_u4ChkResult;
	#ifdef ADC_USE_TH
	VAR(Adc_TrackHoldGroupType,	ADC_VAR_NO_INIT)	t_udTHGrp;
	#endif

	t_u4ChkResult  = Adc_Pil_RegchkPreFixADCR1(t_cudHWUnit);
	t_u4ChkResult |= Adc_Pil_RegchkPreFixADCR2(t_cudHWUnit);
	t_u4ChkResult |= Adc_Pil_RegchkPreFixSMPCR(t_cudHWUnit);
	t_u4ChkResult |= Adc_Pil_RegchkPreFixSGMCYCR(t_cudGrp,t_cudHWUnit,t_cudSG);
	t_u4ChkResult |= Adc_Pil_RegchkPreFixTHER(t_cudHWUnit);

	#if	(MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	/* t_u4ChkResult is updated in ADC_RegValueCheckByAllUnits	*/
	ADC_RegValueCheckByAllUnits(uint32, Reg_AIR.u4AIRISELR0, ADC_AIRISELR0_INIT_VALUE, ADC_AIRISELR0_DEFBIT);
	/* AIRISELR1	not using	*/
	ADC_RegValueCheckByAllUnits(uint32, Reg_AIR.u4AIRDSELR0, ADC_AIRDSELR0_INIT_VALUE, ADC_AIRDSELR0_DEFBIT);
	/* AIRDSELR1	not using	*/
	#endif

	#ifdef ADC_USE_TH
	t_udTHGrp = Adc_GetTHGrp(t_cudGrp);
	if (t_udTHGrp!=ADC_TH_GRP_NONE) {
		if (t_cudHWUnit<ADC_HWUNIT_WTH_NUM) {
			/* t_u4ChkResult is updated in ADC_RegValueCheckByHWUnit	*/
			ADC_RegValueCheckByHWUnit(uint8, cpstReg_Adc[t_cudHWUnit]->stMODULE.u1THCR, ADC_TH_AUTOSAMPLING, ADC_THCR_DEFBIT, t_cudHWUnit);
		}
	}
	#endif
	return(t_u4ChkResult);
}
/************************************************************************************************/
/* Service name			: Adc_Pil_RegchkPreFixADCR1												*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/* 		Adc_HWUnitType	: HW Unit Number														*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: uint32																*/
/* 		ADC_REGCHK_OK					: No Error detected										*/
/* 		ADC_REGCHK_NG					: Error detected										*/
/*		(following is availabel when ADC_CFG_REG_REFRESH is STD_ON)								*/
/* 		ADC_REGCHK_REFRESH_SUCCESS		: Error detected but refresh is success					*/
/* 		ADC_REGCHK_REFRESH_IMPOSSIBLE	: Error detected for unrefreshable register	 			*/
/* 		ADC_REGCHK_REFRESH_FAILED		: Error detected and refresh failed			 			*/
/* Description			: Check ADCR1															*/
/************************************************************************************************/
static FUNC(uint32, ADC_CODE) Adc_Pil_RegchkPreFixADCR1(
	CONST(Adc_HWUnitType,	ADC_CONST)	t_cudHWUnit
)
{
	VAR(uint32,			ADC_VAR_NO_INIT)	t_u4ChkResult;

	t_u4ChkResult = ADC_REGCHK_OK;
	if (t_cudHWUnit<ADC_HWUNIT_NUM) {
		/* t_u4ChkResult is updated in ADC_RegValueCheckByHWUnit	*/
		ADC_RegValueCheckByHWUnit(uint8, cpstReg_Adc[t_cudHWUnit]->stMODULE.u1ADCR1, Adc_cstUserConfig.cpstHWConfig->cu1ADCR1[t_cudHWUnit],	ADC_ADCR1_DEFBIT,t_cudHWUnit);
	}
	return(t_u4ChkResult);
}
/************************************************************************************************/
/* Service name			: Adc_Pil_RegchkPreFixADCR2												*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/* 		Adc_HWUnitType	: HW Unit Number														*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: uint32																*/
/* 		ADC_REGCHK_OK					: No Error detected										*/
/* 		ADC_REGCHK_NG					: Error detected										*/
/*		(following is availabel when ADC_CFG_REG_REFRESH is STD_ON)								*/
/* 		ADC_REGCHK_REFRESH_SUCCESS		: Error detected but refresh is success					*/
/* 		ADC_REGCHK_REFRESH_IMPOSSIBLE	: Error detected for unrefreshable register	 			*/
/* 		ADC_REGCHK_REFRESH_FAILED		: Error detected and refresh failed			 			*/
/* Description			: Check ADCR2															*/
/************************************************************************************************/
static FUNC(uint32, ADC_CODE) Adc_Pil_RegchkPreFixADCR2(
	CONST(Adc_HWUnitType,	ADC_CONST)	t_cudHWUnit
)
{
	VAR(uint32,			ADC_VAR_NO_INIT)	t_u4ChkResult;

	t_u4ChkResult = ADC_REGCHK_OK;
	if (t_cudHWUnit<ADC_HWUNIT_NUM) {
		/* t_u4ChkResult is updated in ADC_RegValueCheckByHWUnit	*/
		ADC_RegValueCheckByHWUnit(uint8, cpstReg_Adc[t_cudHWUnit]->stMODULE.u1ADCR2, Adc_cstUserConfig.cpstHWConfig->cu1ADCR2[t_cudHWUnit], ADC_ADCR2_DEFBIT, t_cudHWUnit);
	}
	return(t_u4ChkResult);
}
/************************************************************************************************/
/* Service name			: Adc_Pil_RegchkPreFixSMPCR												*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/* 		Adc_HWUnitType	: HW Unit Number														*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: uint32																*/
/* 		ADC_REGCHK_OK					: No Error detected										*/
/* 		ADC_REGCHK_NG					: Error detected										*/
/*		(following is availabel when ADC_CFG_REG_REFRESH is STD_ON)								*/
/* 		ADC_REGCHK_REFRESH_SUCCESS		: Error detected but refresh is success					*/
/* 		ADC_REGCHK_REFRESH_IMPOSSIBLE	: Error detected for unrefreshable register	 			*/
/* 		ADC_REGCHK_REFRESH_FAILED		: Error detected and refresh failed			 			*/
/* Description			: Check SMPCR															*/
/************************************************************************************************/
static FUNC(uint32, ADC_CODE) Adc_Pil_RegchkPreFixSMPCR(
	CONST(Adc_HWUnitType,	ADC_CONST)	t_cudHWUnit
)
{
	VAR(uint32,			ADC_VAR_NO_INIT)	t_u4ChkResult;

	t_u4ChkResult = ADC_REGCHK_OK;
	if (t_cudHWUnit<ADC_HWUNIT_NUM) {
		/* t_u4ChkResult is updated in ADC_RegValueCheckByHWUnit	*/
		ADC_RegValueCheckByHWUnit(uint32, cpstReg_Adc[t_cudHWUnit]->stMODULE.u4SMPCR, Adc_cstUserConfig.cpstHWConfig->cu4SMPCR[t_cudHWUnit], ADC_SMPCR_DEFBIT, t_cudHWUnit);
	}
	return(t_u4ChkResult);
}
/************************************************************************************************/
/* Service name			: Adc_Pil_RegchkPreFixSGMCYCR											*/
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
/*		(following is availabel when ADC_CFG_REG_REFRESH is STD_ON)								*/
/* 		ADC_REGCHK_REFRESH_SUCCESS		: Error detected but refresh is success					*/
/* 		ADC_REGCHK_REFRESH_IMPOSSIBLE	: Error detected for unrefreshable register	 			*/
/* 		ADC_REGCHK_REFRESH_FAILED		: Error detected and refresh failed			 			*/
/* Description			: Check SGMCYCR															*/
/************************************************************************************************/
static FUNC(uint32, ADC_CODE) Adc_Pil_RegchkPreFixSGMCYCR(
	CONST(Adc_GroupType,	ADC_CONST)	t_cudGrp,		/* 	used in ADC_RegValueCheckByScanGroup */
	CONST(Adc_HWUnitType,	ADC_CONST)	t_cudHWUnit,
	CONST(Adc_SGType,		ADC_CONST)	t_cudSG
)
{
	VAR(uint32,			ADC_VAR_NO_INIT)	t_u4ChkResult;

	t_u4ChkResult = ADC_REGCHK_OK;
	if (t_cudHWUnit<ADC_HWUNIT_NUM) {
		/* t_u4ChkResult is updated in ADC_RegValueCheckByScanGroup	*/
		ADC_RegValueCheckByScanGroup(uint8, cpstReg_Adc[t_cudHWUnit]->stMODULE.stSG[t_cudSG].u1SGMCYCR, ADC_SGMCYCR, ADC_SGMCYCR_DEFBIT);
	}
	return(t_u4ChkResult);
}
/************************************************************************************************/
/* Service name			: Adc_Pil_RegchkPreFixTHER												*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/* 		Adc_HWUnitType	: HW Unit Number														*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: uint32																*/
/* 		ADC_REGCHK_OK					: No Error detected										*/
/* 		ADC_REGCHK_NG					: Error detected										*/
/*		(following is availabel when ADC_CFG_REG_REFRESH is STD_ON)								*/
/* 		ADC_REGCHK_REFRESH_SUCCESS		: Error detected but refresh is success					*/
/* 		ADC_REGCHK_REFRESH_IMPOSSIBLE	: Error detected for unrefreshable register	 			*/
/* 		ADC_REGCHK_REFRESH_FAILED		: Error detected and refresh failed			 			*/
/* Description			: Check THER															*/
/************************************************************************************************/
static FUNC(uint32, ADC_CODE) Adc_Pil_RegchkPreFixTHER(
	CONST(Adc_HWUnitType,	ADC_CONST)	t_cudHWUnit
)
{
	VAR(uint32,					ADC_VAR_NO_INIT)	t_u4ChkResult;
	VAR(uint8,					ADC_VAR_NO_INIT)	t_u1RegValue;
	VAR(uint8,					ADC_VAR_NO_INIT)	t_u1ExpectedValue;
	#if (ADC_CFG_REG_REFRESH==STD_ON)
	#ifdef ADC_USE_TH
	VAR(boolean,				ADC_VAR_NO_INIT)	t_b1isRunning;
	#endif
	#endif

	t_u4ChkResult	= ADC_REGCHK_OK;
	if (t_cudHWUnit<ADC_HWUNIT_WTH_NUM) {
		#ifdef ADC_USE_TH
		t_u1ExpectedValue	= Adc_cstUserConfig.cpstHWConfig->cu1THER[t_cudHWUnit] & (uint8)ADC_THER_DEFBIT;
		#else
		t_u1ExpectedValue	= ADC_TH_DISABLE & (uint8)ADC_THER_DEFBIT;
		#endif

		ADC_ENTER_CRITICAL_SECTION(ADC_CODE);
		t_u1RegValue		= cpstReg_Adc[t_cudHWUnit]->stMODULE.u1THER  & (uint8)ADC_THER_DEFBIT;
		if (t_u1RegValue!=t_u1ExpectedValue) {
			#if (ADC_CFG_REG_REFRESH==STD_ON)
			#ifdef ADC_USE_TH
			t_b1isRunning	= Adc_IsTHinHWUnitRunning(t_cudHWUnit);
			if (t_b1isRunning==TRUE) {
				t_u4ChkResult |= ADC_REGCHK_REFRESH_IMPOSSIBLE;
			} else {
			#endif
				cpstReg_Adc[t_cudHWUnit]->stMODULE.u1THER	= t_u1ExpectedValue;
				t_u1RegValue								= cpstReg_Adc[t_cudHWUnit]->stMODULE.u1THER  & (uint8)ADC_THER_DEFBIT;
				if (t_u1RegValue==t_u1ExpectedValue) {
					t_u4ChkResult	|= ADC_REGCHK_REFRESH_SUCCESS;
				} else {
					t_u4ChkResult	|= ADC_REGCHK_REFRESH_FAILED;
				}
			#ifdef ADC_USE_TH
			}
			#endif
			#else
				t_u4ChkResult  |= ADC_REGCHK_NG;
			#endif
		}
		ADC_EXIT_CRITICAL_SECTION(ADC_CODE);
	}
	return(t_u4ChkResult);
}
/************************************************************************************************/
/* Service name			: Adc_Pil_RegchkPostFix													*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* 		Adc_HWUnitType	: HW Unit Number														*/
/* 		Adc_SGType		: Scan Group Number														*/
/*		VCR				: Async: VCR			register setting value							*/
/*		SGTSEL			: Async: SGTSEL			register setting value							*/
/*		SGVCPR			: Async: SGVCPR			register setting value							*/
/*		THGSR			: Async: THGSR			register setting value							*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: uint32																*/
/* 		ADC_REGCHK_OK					: No Error detected										*/
/* 		ADC_REGCHK_NG					: Error detected										*/
/*		(following is availabel when ADC_CFG_REG_REFRESH is STD_ON)								*/
/* 		ADC_REGCHK_REFRESH_SUCCESS		: Error detected but refresh is success					*/
/* 		ADC_REGCHK_REFRESH_IMPOSSIBLE	: Error detected for unrefreshable register	 			*/
/* 		ADC_REGCHK_REFRESH_FAILED		: Error detected and refresh failed			 			*/
/* Description			: Check registers deceided by some configurations						*/
/************************************************************************************************/
static FUNC(uint32, ADC_CODE) Adc_Pil_RegchkPostFix(
	CONST(Adc_GroupType,	ADC_CONST)			t_cudGrp,		/* 	used in ADC_RegValueCheckByScanGroup */
	CONST(Adc_HWUnitType,	ADC_CONST)			t_cudHWUnit,
	CONST(Adc_SGType,		ADC_CONST)			t_cudSG,
	VAR(uint32,				ADC_VAR_NO_INIT)	t_u4VCR[ADC_HWUNIT_NUM][ADC_CHANNEL_NUM],
	VAR(uint32,				ADC_VAR_NO_INIT)	t_u4SGTSEL[ADC_SG_NUM],
	VAR(uint16,				ADC_VAR_NO_INIT)	t_u2SGVCPR[ADC_HWUNIT_NUM][ADC_SG_NUM]
	#ifdef ADC_USE_TH
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	,VAR(uint16,			ADC_VAR_NO_INIT)	t_u2THGSR[ADC_HWUNIT_WTH_NUM]
	#endif
	#endif
)
{
	VAR(uint32,						ADC_VAR_NO_INIT)	t_u4ChkResult;
	VAR(uint16,						ADC_VAR_NO_INIT)	i;
	VAR(uint16,						ADC_VAR_NO_INIT)	t_u2Start;
	VAR(uint16,						ADC_VAR_NO_INIT)	t_u2End;
	#ifdef ADC_USE_TH
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	VAR(Adc_TrackHoldGroupType,		ADC_VAR_NO_INIT)	t_udTHGrp;
	#endif
	#endif
	#if ((MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A)				\
	 || ((MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)				\
		&& ((MCAL_PKG_TARGET==MCAL_PKG_U2B24_468PIN)			\
		 || (MCAL_PKG_TARGET==MCAL_PKG_U2B24_373PIN)			\
		 || (MCAL_PKG_TARGET==MCAL_PKG_U2B20_468PIN)			\
		 || (MCAL_PKG_TARGET==MCAL_PKG_U2B20_373PIN))))
	VAR(Adc_TriggerSourceType,		ADC_VAR_NO_INIT)	t_udTriggerSource;
	#endif

	t_u4ChkResult = ADC_REGCHK_OK;
	if( t_cudHWUnit<ADC_HWUNIT_NUM) {
		/* t_u4ChkResult is updated in ADC_RegValueCheckByScanGroup	*/
		#if	(MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
		t_udTriggerSource = Adc_GetTriggerSource(t_cudGrp);
		if ((t_cudHWUnit==ADC_SPECIFIC_HWUNIT) && (t_udTriggerSource==ADC_TRIGG_SRC_HW))  {
			ADC_RegValueCheckByScanGroup(uint32, cpstReg_SELB_Adc[ADC_ZERO]->u4SGTSEL[t_cudSG], t_u4SGTSEL[t_cudSG], ADC_SGTSEL_DEFBIT);
		}
		#endif
		ADC_RegValueCheckByScanGroup(uint16, cpstReg_Adc[t_cudHWUnit]->stMODULE.stSG[t_cudSG].u2SGVCPR, t_u2SGVCPR[t_cudHWUnit][t_cudSG], ADC_SGVCPR_DEFBIT);
		/* VCR	*/
		t_u2Start	= t_u2SGVCPR[t_cudHWUnit][t_cudSG] & (uint16)ADC_SGVCPR_VCSP;
		t_u2End		= (t_u2SGVCPR[t_cudHWUnit][t_cudSG] & (uint16)ADC_SGVCPR_VCEP)>>ADC_SGVCPR_VCEP_BITPOS;
		for (i=t_u2Start;i<=t_u2End;i++) {
			/* t_u4ChkResult is updated in ADC_RegValueCheckByScanGroup	*/
			ADC_RegValueCheckByScanGroup(uint32, cpstReg_Adc[t_cudHWUnit]->stMODULE.u4VCR[i], t_u4VCR[t_cudHWUnit][i], ADC_VCR_DEFBIT);
		}
	}
	#ifdef ADC_USE_TH
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	t_udTHGrp = Adc_GetTHGrp(t_cudGrp);
	if (t_udTHGrp!=ADC_TH_GRP_NONE) {
		if (t_cudHWUnit<ADC_HWUNIT_WTH_NUM) {
		/* t_u4ChkResult is updated in ADC_RegValueCheckByHWUnit	*/
			ADC_RegValueCheckByHWUnit(uint16, cpstReg_Adc[t_cudHWUnit]->stMODULE.u2THGSR, t_u2THGSR[t_cudHWUnit], ADC_THGSR_DEFBIT, t_cudHWUnit);
		}
	}
	#endif
	#endif
	return(t_u4ChkResult);
}

/************************************************************************************************/
/* Service name			: Adc_Pil_RegchkDynamic													*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* 		Adc_HWUnitType	: HW Unit Number														*/
/* 		Adc_SGType		: Scan Group Number														*/
/*		THxCR			: Async: THxCR		register setting value								*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: uint32																*/
/* 		ADC_REGCHK_OK					: No Error detected										*/
/* 		ADC_REGCHK_NG					: Error detected										*/
/*		(following is availabel when ADC_CFG_REG_REFRESH is STD_ON)								*/
/* 		ADC_REGCHK_REFRESH_SUCCESS		: Error detected but refresh is success					*/
/* 		ADC_REGCHK_REFRESH_IMPOSSIBLE	: Error detected for unrefreshable register	 			*/
/* 		ADC_REGCHK_REFRESH_FAILED		: Error detected and refresh failed			 			*/
/* Description			: Check registers deceided by convesion status							*/
/************************************************************************************************/
static FUNC(uint32, ADC_CODE) Adc_Pil_RegchkDynamic(
	CONST(Adc_GroupType,	ADC_CONST)			t_cudGrp,	
	CONST(Adc_HWUnitType,	ADC_CONST)			t_cudHWUnit,
	CONST(Adc_SGType,		ADC_CONST)			t_cudSG
	#ifdef ADC_USE_TH
	,VAR(uint8,				ADC_VAR_NO_INIT)	t_u1THxCR[ADC_HWUNIT_WTH_NUM][ADC_TH_GRP_NUM]
	#endif
)
{
	VAR(uint32,						ADC_VAR_NO_INIT)	t_u4ChkResult;

	t_u4ChkResult = Adc_Pil_RegchkDynamicSGCR(t_cudGrp,t_cudHWUnit,t_cudSG);
	#ifdef ADC_USE_TH
	t_u4ChkResult |= Adc_Pil_RegchkDynamicTHxCR(t_cudGrp,t_cudHWUnit,t_u1THxCR);
	#endif

	return(t_u4ChkResult);
}
/************************************************************************************************/
/* Service name			: Adc_Pil_RegchkDynamicSGCR												*/
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
/*		(following is availabel when ADC_CFG_REG_REFRESH is STD_ON)								*/
/* 		ADC_REGCHK_REFRESH_SUCCESS		: Error detected but refresh is success					*/
/* 		ADC_REGCHK_REFRESH_IMPOSSIBLE	: Error detected for unrefreshable register	 			*/
/* 		ADC_REGCHK_REFRESH_FAILED		: Error detected and refresh failed			 			*/
/* Description			: Check SGCR															*/
/************************************************************************************************/
static FUNC(uint32, ADC_CODE) Adc_Pil_RegchkDynamicSGCR(
	CONST(Adc_GroupType,	ADC_CONST)			t_cudGrp,
	CONST(Adc_HWUnitType,	ADC_CONST)			t_cudHWUnit,
	CONST(Adc_SGType,		ADC_CONST)			t_cudSG
)
{
	VAR(Adc_TriggerSourceType,		ADC_VAR_NO_INIT)	t_udTriggerSource;
	VAR(Adc_GroupAccessModeType,	ADC_VAR_NO_INIT)	t_udAccessMode;
	VAR(Adc_StatusType,				ADC_VAR_NO_INIT)	t_udStatus;
	VAR(uint32,						ADC_VAR_NO_INIT)	t_u4ChkResult;
	VAR(uint8,						ADC_VAR_NO_INIT)	t_u1DMAOn;
	VAR(uint8,						ADC_VAR_NO_INIT)	t_u1IntrptUse;
	VAR(uint8,						ADC_VAR_NO_INIT)	t_u1RegValue;
	VAR(uint8, 						ADC_VAR_NO_INIT)	t_u1ExpectedValue;

	t_u4ChkResult	= ADC_REGCHK_OK;
	if (t_cudGrp<ADC_CFG_GRP_SIZE) {
		t_u1ExpectedValue = Adc_cstUserConfig.cpstHWConfig->cu1SGCR[t_cudGrp] & ADC_SGCR_DEFBIT;
		ADC_ENTER_CRITICAL_SECTION(ADC_CODE);
		t_udStatus			= Adc_GetGroupStatus(t_cudGrp);
		t_u1RegValue		= cpstReg_Adc[t_cudHWUnit]->stMODULE.stSG[t_cudSG].u1SGCR & ADC_SGCR_DEFBIT;

		if (t_udStatus==ADC_IDLE) {
			if (t_u1RegValue!=t_u1ExpectedValue) {
				#if (ADC_CFG_REG_REFRESH==STD_ON)
				cpstReg_Adc[t_cudHWUnit]->stMODULE.stSG[t_cudSG].u1SGCR = t_u1ExpectedValue;
				t_u1RegValue = cpstReg_Adc[t_cudHWUnit]->stMODULE.stSG[t_cudSG].u1SGCR & ADC_SGCR_DEFBIT;
				if (t_u1RegValue==t_u1ExpectedValue) {
					t_u4ChkResult |= ADC_REGCHK_REFRESH_SUCCESS;
				} else {
					t_u4ChkResult |= ADC_REGCHK_REFRESH_FAILED;
				}
				#else
				t_u4ChkResult  |= ADC_REGCHK_NG;
				#endif
			}
		} else {
			t_udAccessMode	= Adc_GetGrpAccessMode(t_cudGrp);
			t_u1DMAOn		= Adc_IsDMAOn(t_cudGrp);
			t_u1IntrptUse	= Adc_GetIntrptUse(t_cudGrp);
			/* ADIE	*/
			if ((t_udAccessMode==ADC_ACCESS_MODE_STREAMING)||(t_u1DMAOn==STD_ON)||(t_u1IntrptUse==(uint8)STD_ON)) {
				t_u1ExpectedValue |= (uint8)(ADC_SGCR_ADIE);
			}
			/* TRGMD	*/
			t_udTriggerSource = Adc_GetTriggerSource(t_cudGrp);
			if (t_udTriggerSource==ADC_TRIGG_SRC_HW) {
				t_u1ExpectedValue |= (uint8)(ADC_TRGMD_ENABLE);
			}
			t_u1RegValue = cpstReg_Adc[t_cudHWUnit]->stMODULE.stSG[t_cudSG].u1SGCR & ADC_SGCR_DEFBIT;
			if (t_u1RegValue!=t_u1ExpectedValue) {
				#if (ADC_CFG_REG_REFRESH==STD_ON)
				t_u4ChkResult |= ADC_REGCHK_REFRESH_IMPOSSIBLE;
				#else
				t_u4ChkResult  |= ADC_REGCHK_NG;
				#endif
			}
		}
		ADC_EXIT_CRITICAL_SECTION(ADC_CODE);
	}
	return(t_u4ChkResult);
}
/************************************************************************************************/
/* Service name			: Adc_Pil_RegchkDynamicTHxCR											*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* 		Adc_HWUnitType	: HW Unit Number														*/
/*		THxCR			: Async: THxCR		register setting value								*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: uint32																*/
/* 		ADC_REGCHK_OK					: No Error detected										*/
/* 		ADC_REGCHK_NG					: Error detected										*/
/*		(following is availabel when ADC_CFG_REG_REFRESH is STD_ON)								*/
/* 		ADC_REGCHK_REFRESH_SUCCESS		: Error detected but refresh is success					*/
/* 		ADC_REGCHK_REFRESH_IMPOSSIBLE	: Error detected for unrefreshable register	 			*/
/* 		ADC_REGCHK_REFRESH_FAILED		: Error detected and refresh failed			 			*/
/* Description			: Check THxCR															*/
/************************************************************************************************/
#ifdef ADC_USE_TH
static FUNC(uint32, ADC_CODE) Adc_Pil_RegchkDynamicTHxCR(
	CONST(Adc_GroupType,	ADC_CONST)			t_cudGrp,
	CONST(Adc_HWUnitType,	ADC_CONST)			t_cudHWUnit,
	VAR(uint8,				ADC_VAR_NO_INIT)	t_u1THxCR[ADC_HWUNIT_WTH_NUM][ADC_TH_GRP_NUM]
)
{
	VAR(uint32,					ADC_VAR_NO_INIT)	t_u4ChkResult;
	VAR(Adc_TrackHoldGroupType,	ADC_VAR_NO_INIT)	t_udTHGrp;
	VAR(Adc_StatusType,			ADC_VAR_NO_INIT)	t_udStatus;
	VAR(uint8,					ADC_VAR_NO_INIT)	t_u1RegValue;
	VAR(uint8, 					ADC_VAR_NO_INIT)	t_u1ExpectedValue;
	VAR(boolean,				ADC_VAR_NO_INIT)	t_b1isRunning;

	t_u4ChkResult	= ADC_REGCHK_OK;
	t_udTHGrp		= Adc_GetTHGrp(t_cudGrp);
	if (t_udTHGrp!=ADC_TH_GRP_NONE) {
		ADC_ENTER_CRITICAL_SECTION(ADC_CODE);
		#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A)
		t_u1RegValue			= cpstReg_Adc[t_cudHWUnit]->stMODULE.u1THACR & ADC_THACR_DEFBIT;
		t_u1ExpectedValue		= Adc_cstUserConfig.cpstHWConfig->cu1THACR[t_cudHWUnit]|t_u1THxCR[t_cudHWUnit][ADC_TH_GRP_A] & ADC_THACR_DEFBIT;
		#elif (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
		if (t_udTHGrp==ADC_TH_GRP_A) {
			t_u1RegValue		= cpstReg_Adc[t_cudHWUnit]->stMODULE.u1THACR & ADC_THACR_DEFBIT;
			t_u1ExpectedValue	= Adc_cstUserConfig.cpstHWConfig->cu1THACR[t_cudHWUnit]|t_u1THxCR[t_cudHWUnit][ADC_TH_GRP_A] & ADC_THACR_DEFBIT;
		} else {
			t_u1RegValue		= cpstReg_Adc[t_cudHWUnit]->stMODULE.u1THBCR & ADC_THBCR_DEFBIT;
			t_u1ExpectedValue	= Adc_cstUserConfig.cpstHWConfig->cu1THBCR[t_cudHWUnit]|t_u1THxCR[t_cudHWUnit][ADC_TH_GRP_B] & ADC_THBCR_DEFBIT;
		}
		#endif
		t_b1isRunning = Adc_IsHWUnitRunning(t_cudHWUnit);
		if (t_b1isRunning==TRUE) {
			t_udStatus = Adc_GetGroupStatus(t_cudGrp);
			if (t_udStatus!=ADC_IDLE) {									\
				t_u1ExpectedValue  |= ADC_TH_HOLD_TRG_ENABLE;
			}
			if (t_u1RegValue!=t_u1ExpectedValue) {
				#if (ADC_CFG_REG_REFRESH==STD_ON)
				t_u4ChkResult |= ADC_REGCHK_REFRESH_IMPOSSIBLE;
				#else
				t_u4ChkResult  |= ADC_REGCHK_NG;
				#endif
			}
		} else {
			if (t_u1RegValue!=t_u1ExpectedValue) {
				#if (ADC_CFG_REG_REFRESH==STD_ON)
					#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A)
					cpstReg_Adc[t_cudHWUnit]->stMODULE.u1THACR	= t_u1ExpectedValue;
					t_u1RegValue								= cpstReg_Adc[t_cudHWUnit]->stMODULE.u1THACR & ADC_THACR_DEFBIT;
					#elif (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
					if (t_udTHGrp==ADC_TH_GRP_A) {
						cpstReg_Adc[t_cudHWUnit]->stMODULE.u1THACR	= t_u1ExpectedValue;
						t_u1RegValue								= cpstReg_Adc[t_cudHWUnit]->stMODULE.u1THACR & ADC_THACR_DEFBIT;
					} else {
						cpstReg_Adc[t_cudHWUnit]->stMODULE.u1THBCR	= t_u1ExpectedValue;
						t_u1RegValue								= cpstReg_Adc[t_cudHWUnit]->stMODULE.u1THBCR & ADC_THBCR_DEFBIT;
					}
					#endif
					if (t_u1RegValue==t_u1ExpectedValue) {
						t_u4ChkResult |= ADC_REGCHK_REFRESH_SUCCESS;
					} else {
						t_u4ChkResult |= ADC_REGCHK_REFRESH_FAILED;
					}
				#else
					t_u4ChkResult  |= ADC_REGCHK_NG;
				#endif
			}
		}
		ADC_EXIT_CRITICAL_SECTION(ADC_CODE);
	}
	return(t_u4ChkResult);
}
#endif	/* #ifdef ADC_USE_TH	*/

/************************************************************************************************/
/* Service name			: Adc_Pil_RegchkCalExpctValue											*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/* 		isAllRegCheck	: TRUE : check all registers											*/
/*						  FALSE: check Group related registers 									*/
/* 		Adc_HWUnitType	: HW Unit Number														*/
/* Parameters (inout)	: 																		*/
/*		VCR				: Async: VCR			register setting value							*/
/*		SGTSEL			: Async: SGTSEL			register setting value							*/
/*		SGVCPR			: Async: SGVCPR			register setting value							*/
/*		THxCR			: Async: THxCR			register setting value							*/
/*		THGSR			: Async: THGSR			register setting value							*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: calcuate the register setting value									*/
/************************************************************************************************/
static FUNC(void, ADC_CODE) Adc_Pil_RegchkCalExpctValue(
	CONST(boolean,			ADC_CONST)			t_cblisAllRegCheck,
	CONST(Adc_HWUnitType,	ADC_CONST)			t_cudHWUnit,
	VAR(uint32,				ADC_VAR_NO_INIT)	t_u4VCR[ADC_HWUNIT_NUM][ADC_CHANNEL_NUM],
	VAR(uint32,				ADC_VAR_NO_INIT)	t_u4SGTSEL[ADC_SG_NUM],
	VAR(uint16,				ADC_VAR_NO_INIT)	t_u2SGVCPR[ADC_HWUNIT_NUM][ADC_SG_NUM]
	#ifdef ADC_USE_TH
	,VAR(uint8,				ADC_VAR_NO_INIT)	t_u1THxCR[ADC_HWUNIT_WTH_NUM][ADC_TH_GRP_NUM]
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	,VAR(uint16,			ADC_VAR_NO_INIT)	t_u2THGSR[ADC_HWUNIT_WTH_NUM]
	#endif
	#endif
)
{
	VAR(Adc_GroupType, 							ADC_VAR_NO_INIT) 	t_udGrp;
	VAR(Adc_HWUnitType,							ADC_VAR_NO_INIT)	t_udHWUnit;
	VAR(uint16,									ADC_VAR_NO_INIT)	t_u2VCEP;
	VAR(uint16,									ADC_VAR_NO_INIT)	t_u2VCSP;
	VAR(uint16, 								ADC_VAR_NO_INIT)	t_u2CrntVChNbr[ADC_HWUNIT_NUM];
	VAR(uint16, 								ADC_VAR_NO_INIT)	t_u2CnvChSize;
	#ifdef ADC_USE_TH
		P2CONST(Adc_GrpHWInfoType,	AUTOMATIC,	ADC_CONST)			t_cpstGrpHWInfo;
		VAR(Adc_SGType,							ADC_VAR_NO_INIT)	t_udSG;
		VAR(Adc_ChannelType,					ADC_VAR_NO_INIT)	t_udCH;
		VAR(uint16,								ADC_VAR_NO_INIT)	t_u2VCStartPos[ADC_CFG_GRP_SIZE];
		VAR(Adc_TrackHoldGroupType,				ADC_VAR_NO_INIT)	t_udTHGrpTmp;
		VAR(Adc_GroupType,						ADC_VAR_NO_INIT)	t_udTHGrpId[ADC_HWUNIT_WTH_NUM][ADC_TH_GRP_NUM];
		VAR(uint8, 								ADC_VAR_NO_INIT)	t_u1THGrpCount[ADC_HWUNIT_WTH_NUM];
		VAR(uint8, 								ADC_VAR_NO_INIT)	t_u1CrntTHGrpCount;
		VAR(boolean,							ADC_VAR_NO_INIT)	t_blisComplete;
		VAR(uint32,								ADC_VAR_NO_INIT)	i;
		VAR(uint16, 							ADC_VAR_NO_INIT)	t_u2CnvCh;
	#endif

	/* var initial	*/
	Adc_Pil_RegchkVarInit(t_cblisAllRegCheck,t_cudHWUnit,t_u2CrntVChNbr
		#ifdef ADC_USE_TH
		,t_u2VCStartPos,
		t_udTHGrpId,
		t_u1THGrpCount
		#endif
	);

	/* Convert config data to register data	*/
	for (t_udGrp=ADC_GRP00;t_udGrp<(Adc_GroupType)ADC_CFG_GRP_SIZE;t_udGrp++) {
		t_udHWUnit			= Adc_GetHWUnitID(t_udGrp);
		if ((t_cudHWUnit==t_udHWUnit)||(t_cblisAllRegCheck==TRUE)) {
			t_u2CnvChSize	= Adc_GetCnvChSize(t_udGrp);
			t_u2VCSP		= t_u2CrntVChNbr[t_udHWUnit];				/* virtual pointer start	*/	
			t_u2VCEP		= t_u2VCSP + t_u2CnvChSize - ADC_VCEP_CAL;	/* virtual pointer end		*/	
			Adc_Pil_SetSGVCPR(t_u2SGVCPR,t_udGrp,t_u2VCSP,t_u2VCEP);	/* SGVCPR					*/
			Adc_Pil_SetVCR(t_u4VCR,t_udGrp,t_u2VCSP);					/* VCR						*/
			Adc_Pil_CrctVCEP(t_u2CrntVChNbr,t_udGrp,t_u2VCEP);			/* correct VCEP				*/

			#ifdef ADC_USE_TH
			/* THxCR	*/
			if (t_udHWUnit<ADC_HWUNIT_WTH_NUM) {
				t_u1CrntTHGrpCount = t_u1THGrpCount[t_udHWUnit];
				t_blisComplete = FALSE;
				t_cpstGrpHWInfo	= Adc_cstUserConfig.cpstHWConfig->cpstGrpHWInfo;
				for ( t_u2CnvCh=0; t_u2CnvCh<t_u2CnvChSize; t_u2CnvCh++ ) {
					t_udCH		= t_cpstGrpHWInfo[t_udGrp].cudCnvChTbl[t_u2CnvCh];
					for ( i=0; i<ADC_TH_NUM;i++) {
						if ( t_udCH == Adc_cstUserConfig.cpstHWConfig->cudHWTHCHTbl[t_udHWUnit][i] ) {
							/* Use T&H 	*/
							if (t_u1CrntTHGrpCount<ADC_TH_GRP_NUM) {
								t_udSG										= Adc_GetSGID(t_udGrp);
								t_u1THxCR[t_udHWUnit][t_u1CrntTHGrpCount]	= s_cu1THCnvSGTbl[t_udSG];
								t_udTHGrpId[t_udHWUnit][t_u1CrntTHGrpCount]	= t_udGrp;
								t_u1CrntTHGrpCount++;
								t_u1THGrpCount[t_udHWUnit]					= t_u1CrntTHGrpCount;
								t_blisComplete								= TRUE;
								break;
							}
						}
					}
					if (t_blisComplete==TRUE) {
						break;
					}
				}
			}
			#endif

			Adc_Pil_SetSGTSEL(t_u4SGTSEL,t_udGrp);									/* SGTSEL:Unit2(U2A),UnitA(U2B)	*/
			/* Adc_CnvInfoType	*/
			#ifdef ADC_USE_TH
			t_u2VCStartPos[t_udGrp]	= t_u2VCSP;
			#endif
		}
	}
	#ifdef ADC_USE_TH
	/* THGSR VCR(for T&H))	*/
	for(t_udHWUnit=ADC_HWUNIT0;t_udHWUnit<(Adc_HWUnitType)ADC_HWUNIT_WTH_NUM;t_udHWUnit++) {
		if ((t_cudHWUnit==t_udHWUnit)||(t_cblisAllRegCheck==TRUE)) {
			for(t_udTHGrpTmp=ADC_TH_GRP_A;t_udTHGrpTmp<ADC_TH_GRP_NUM;t_udTHGrpTmp++) {
				t_udGrp	= t_udTHGrpId[t_udHWUnit][t_udTHGrpTmp];
				if (ADC_GRP_NONE!=t_udGrp) {
					/* T&H use	*/
					t_u2CnvChSize	= Adc_GetCnvChSize(t_udGrp);
					#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
					t_u2THGSR[t_udHWUnit] = (uint16)ADC_ZERO;
					#endif
					t_cpstGrpHWInfo	= Adc_cstUserConfig.cpstHWConfig->cpstGrpHWInfo;
					for (t_u2CnvCh=0; t_u2CnvCh<t_u2CnvChSize; t_u2CnvCh++) {
						t_udCH		= t_cpstGrpHWInfo[t_udGrp].cudCnvChTbl[t_u2CnvCh] ;
						for ( i=0; i<ADC_TH_NUM; i++) {
							if (t_udCH== Adc_cstUserConfig.cpstHWConfig->cudHWTHCHTbl[t_udHWUnit][i] ) {
								/* T&H use channel	*/
								/* VCR Setting		*/
								t_u2VCSP = t_u2VCStartPos[t_udGrp] + t_u2CnvCh;
								t_u4VCR[t_udHWUnit][t_u2VCSP] |= ADC_VCR_TH;
								/* THGSR setting	*/
								#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
								if (t_udTHGrpTmp==ADC_TH_GRP_B) {
									t_u2THGSR[t_udHWUnit] |= s_cu2THCnvGrpBTbl[t_udCH];	
								}
								#endif
								break;
							}
						}
					}
				}
			}
		}	
	}
	#endif
}
/************************************************************************************************/
/* Service name			: Adc_Pil_RegchkVarInit													*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/* 		isAllRegCheck	: TRUE : check all registers											*/
/*						  FALSE: check Group related registers 									*/
/* 		Adc_HWUnitType	: HW Unit Number														*/
/*		CrntVChNbr		: current VCR number													*/
/* Parameters (inout)	: 																		*/
/*		VCStartPos		: VCR Start Position													*/
/*		THGrpId			: T&H Group ID															*/
/*		THGrpCount		: T&H Group Count														*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Initializes the register check internal data 			.				*/
/************************************************************************************************/
static FUNC(void, ADC_CODE) Adc_Pil_RegchkVarInit(
	CONST(boolean,				ADC_CONST)			t_cblisAllRegCheck,
	CONST(Adc_HWUnitType,		ADC_CONST)			t_cudHWUnit,
	VAR(uint16, 				ADC_VAR_NO_INIT)	t_u2CrntVChNbr[ADC_HWUNIT_NUM]
	#ifdef ADC_USE_TH
	,VAR(uint16,				ADC_VAR_NO_INIT)	t_u2VCStartPos[ADC_CFG_GRP_SIZE],
	VAR(Adc_GroupType,			ADC_VAR_NO_INIT)	t_udTHGrpId[ADC_HWUNIT_WTH_NUM][ADC_TH_GRP_NUM],
	VAR(uint8, 					ADC_VAR_NO_INIT)	t_u1THGrpCount[ADC_HWUNIT_WTH_NUM]
	#endif
)
{
 	VAR(Adc_HWUnitType,	ADC_VAR_NO_INIT)	t_udHWUnit;
	#ifdef ADC_USE_TH
	VAR(uint32,			ADC_VAR_NO_INIT)	i;
	#endif
	#ifdef ADC_USE_TH
	VAR(Adc_GroupType, 	ADC_VAR_NO_INIT) 	t_udGrp;
	VAR(Adc_HWUnitType,	ADC_VAR_NO_INIT)	t_udHWUnitwTH;
	#endif
	
	/* var initial	*/
	#ifdef ADC_USE_TH
	for (t_udGrp=ADC_GRP00;t_udGrp<(Adc_GroupType)ADC_CFG_GRP_SIZE;t_udGrp++) {
		t_u2VCStartPos[t_udGrp]	= (uint16)ADC_ZERO;
	}
	#endif
	if (t_cblisAllRegCheck==TRUE) {
		for (t_udHWUnit=ADC_HWUNIT0;t_udHWUnit<(Adc_HWUnitType)ADC_HWUNIT_NUM;t_udHWUnit++) {
			t_u2CrntVChNbr[t_udHWUnit]	= (uint16)ADC_ZERO;
		}
		#ifdef ADC_USE_TH
		for (t_udHWUnitwTH=ADC_HWUNIT0;t_udHWUnitwTH<(uint32)ADC_HWUNIT_WTH_NUM;t_udHWUnitwTH++) {
			t_u1THGrpCount[t_udHWUnitwTH]	= (uint8)ADC_ZERO;
			for(i=0;i<(uint32)ADC_TH_GRP_NUM;i++) {
				t_udTHGrpId[t_udHWUnitwTH][i]	= ADC_GRP_NONE;	/* Undefined group ID	*/
			}
		}
		#endif
	} else {
		if (t_cudHWUnit<ADC_HWUNIT_WTH_NUM) {
			t_u2CrntVChNbr[t_cudHWUnit]		= (uint16)ADC_ZERO;
			#ifdef ADC_USE_TH
			t_u1THGrpCount[t_cudHWUnit] = (uint8)ADC_ZERO;
			for(i=0;i<(uint32)ADC_TH_GRP_NUM;i++) {
				t_udTHGrpId[t_cudHWUnit][i]	= ADC_GRP_NONE;		/* Undefined group ID	*/
			}
			#endif
		}
	}
}

#endif	/* if (ADC_CFG_REG_CHK==STD_ON)	*/

/*----------------------------------------------------------------------------------------------*/
/* Private API 																					*/
/*----------------------------------------------------------------------------------------------*/

/************************************************************************************************/
/* Service name			: Adc_Pil_RegVarInit													*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: None																	*/
/* Parameters (inout)	: 																		*/
/*		VCR				: Async: VCR			register setting value							*/
/*		SGTSEL			: Async: SGTSEL		register setting value								*/
/*		SGVCPR			: Async: SGVCPR		register setting value								*/
/*		SGCR			: Async: SGCR		register setting value								*/
/*		THxCR			: Async: THxCR		register setting value								*/
/*		THSMPSTCR		: Async: THSMPSTCR	register setting value								*/
/*		THGSR			: Async: THGSR		register setting value								*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Initializes the register setting value  			.					*/
/************************************************************************************************/
static FUNC(void, ADC_CODE) Adc_Pil_RegVarInit(
	VAR(uint32,		ADC_VAR_NO_INIT)	t_u4VCR[ADC_HWUNIT_NUM][ADC_CHANNEL_NUM],
	VAR(uint32,		ADC_VAR_NO_INIT)	t_u4SGTSEL[ADC_SG_NUM],
	VAR(uint16,		ADC_VAR_NO_INIT)	t_u2SGVCPR[ADC_HWUNIT_NUM][ADC_SG_NUM],
	VAR(uint8,		ADC_VAR_NO_INIT)	t_u1SGCR[ADC_HWUNIT_NUM][ADC_SG_NUM]
	#ifdef ADC_USE_TH
	,VAR(uint8,		ADC_VAR_NO_INIT)	t_u1THxCR[ADC_HWUNIT_WTH_NUM][ADC_TH_GRP_NUM]
	,VAR(uint8, 	ADC_VAR_NO_INIT)	t_u1THSMPSTCR[ADC_HWUNIT_WTH_NUM]
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	,VAR(uint16,	ADC_VAR_NO_INIT)	t_u2THGSR[ADC_HWUNIT_WTH_NUM]
	#endif
	#endif
)
{
	VAR(Adc_SGType,		ADC_VAR_NO_INIT)		t_udSG;
	VAR(Adc_HWUnitType,	ADC_VAR_NO_INIT)		t_udHWUnit;
	VAR(uint32,			ADC_VAR_NO_INIT)		i;
	#ifdef ADC_USE_TH
	VAR(Adc_HWUnitType,	ADC_VAR_NO_INIT)		t_udHWUnitwTH;
	#endif

	for (t_udHWUnit=ADC_HWUNIT0;t_udHWUnit<(Adc_HWUnitType)ADC_HWUNIT_NUM;t_udHWUnit++) {
		for (i=0;i<(uint32)ADC_CHANNEL_NUM;i++) {
			t_u4VCR[t_udHWUnit][i] = (uint32)ADC_ZERO;
		}
		for (t_udSG=ADC_SG0;t_udSG<(Adc_SGType)ADC_SG_NUM;t_udSG++) {
			t_u2SGVCPR[t_udHWUnit][t_udSG]	= (uint16)ADC_ZERO;
			t_u1SGCR[  t_udHWUnit][t_udSG]	= (uint8)ADC_ZERO;
		}
	}
	for (t_udSG=ADC_SG0;t_udSG<(Adc_SGType)ADC_SG_NUM;t_udSG++) {
		t_u4SGTSEL[t_udSG] = (uint32)ADC_ZERO;
	}

	#ifdef ADC_USE_TH
	for (t_udHWUnitwTH=ADC_HWUNIT0;t_udHWUnitwTH<(Adc_HWUnitType)ADC_HWUNIT_WTH_NUM;t_udHWUnitwTH++ ) {
		#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
		t_u2THGSR[t_udHWUnitwTH]		= (uint16)ADC_ZERO;		/* Group A				*/
		#endif
		t_u1THSMPSTCR[t_udHWUnitwTH]	= (uint8)ADC_ZERO;
		for(i=0;i<(uint32)ADC_TH_GRP_NUM;i++) {
			t_u1THxCR[t_udHWUnitwTH][i]		= (uint8)ADC_ZERO;
		}
	}
	#endif
}
/************************************************************************************************/
/* Service name			: Adc_Pil_DataInit														*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: None																	*/
/* Parameters (inout)	: 																		*/
/*		VCR				: Async: VCR			register setting value							*/
/*		SGTSEL			: Async: SGTSEL			register setting value							*/
/*		SGVCPR			: Async: SGVCPR			register setting value							*/
/*		SGCR			: Async: SGCR			register setting value							*/
/*		THxCR			: Async: THxCR			register setting value							*/
/*		THSMPSTCR		: Async: THSMPSTCR		register setting value							*/
/*		THGSR			: Async: THGSR			register setting value							*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Initializes the ADC internal data 			.						*/
/************************************************************************************************/
static FUNC(void, ADC_CODE) Adc_Pil_DataInit(
	VAR(uint32,		ADC_VAR_NO_INIT)	t_u4VCR[ADC_HWUNIT_NUM][ADC_CHANNEL_NUM],
	VAR(uint32,		ADC_VAR_NO_INIT)	t_u4SGTSEL[ADC_SG_NUM],
	VAR(uint16,		ADC_VAR_NO_INIT)	t_u2SGVCPR[ADC_HWUNIT_NUM][ADC_SG_NUM],
	VAR(uint8,		ADC_VAR_NO_INIT)	t_u1SGCR[ADC_HWUNIT_NUM][ADC_SG_NUM]
	#ifdef ADC_USE_TH
	,VAR(uint8,		ADC_VAR_NO_INIT)	t_u1THxCR[ADC_HWUNIT_WTH_NUM][ADC_TH_GRP_NUM]
	,VAR(uint8, 	ADC_VAR_NO_INIT)	t_u1THSMPSTCR[ADC_HWUNIT_WTH_NUM]
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	,VAR(uint16,	ADC_VAR_NO_INIT)	t_u2THGSR[ADC_HWUNIT_WTH_NUM]
	#endif
	#endif
)
{
	VAR(Adc_GroupType, 							ADC_VAR_NO_INIT) 	t_udGrp;
	VAR(Adc_HWUnitType,							ADC_VAR_NO_INIT)	t_udHWUnit;
	VAR(uint16,									ADC_VAR_NO_INIT)	t_u2VCEP;
	VAR(uint16,									ADC_VAR_NO_INIT)	t_u2VCSP;
	VAR(uint16, 								ADC_VAR_NO_INIT)	t_u2CrntVChNbr[ADC_HWUNIT_NUM];
	VAR(uint16, 								ADC_VAR_NO_INIT)	t_u2CnvChSize;
	#ifdef ADC_USE_TH
		P2CONST(Adc_GrpHWInfoType,	AUTOMATIC,	ADC_CONST)			t_cpstGrpHWInfo;
		VAR(Adc_SGType,							ADC_VAR_NO_INIT)	t_udSG;
		VAR(Adc_HWUnitType,						ADC_VAR_NO_INIT)	t_udHWUnitwTH;
		VAR(Adc_ChannelType,					ADC_VAR_NO_INIT)	t_udCH;
		VAR(uint16,								ADC_VAR_NO_INIT)	t_u2VCStartPos[ADC_CFG_GRP_SIZE];
		VAR(Adc_TrackHoldGroupType,				ADC_VAR_NO_INIT)	t_udTHGrpTmp;
		VAR(Adc_TrackHoldGroupType,				ADC_VAR_NO_INIT)	t_udTHGrp[ADC_CFG_GRP_SIZE];
		VAR(Adc_GroupType,						ADC_VAR_NO_INIT)	t_udTHGrpId[ADC_HWUNIT_WTH_NUM][ADC_TH_GRP_NUM];
		VAR(uint8, 								ADC_VAR_NO_INIT)	t_u1THGrpCount[ADC_HWUNIT_WTH_NUM];
		VAR(uint8, 								ADC_VAR_NO_INIT)	t_u1CrntTHGrpCount;
		VAR(boolean,							ADC_VAR_NO_INIT)	t_blisComplete;
		VAR(uint32,								ADC_VAR_NO_INIT)	i;
		VAR(uint16, 							ADC_VAR_NO_INIT)	t_u2CnvCh;
		#if	(MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
			VAR(uint16,							ADC_VAR_NO_INIT)	t_u2THGSRValue;
		#endif
	#endif


	/* var initial	*/
	for (t_udHWUnit=ADC_HWUNIT0;t_udHWUnit<(Adc_HWUnitType)ADC_HWUNIT_NUM;t_udHWUnit++) {
		t_u2CrntVChNbr[t_udHWUnit] = (uint16)ADC_ZERO;
	}
	#ifdef ADC_USE_TH
	for (t_udHWUnitwTH=ADC_HWUNIT0;t_udHWUnitwTH<(Adc_HWUnitType)ADC_HWUNIT_WTH_NUM;t_udHWUnitwTH++) {
		t_u1THGrpCount[t_udHWUnitwTH] = (uint8)ADC_ZERO;
		for(i=0;i<(uint32)ADC_TH_GRP_NUM;i++) {
			t_udTHGrpId[t_udHWUnitwTH][i]	= ADC_GRP_NONE;		/* Undefined group ID	*/
		}
	}
	#endif

	/* Convert config data to register data	*/
	for (t_udGrp=ADC_GRP00;t_udGrp<(Adc_GroupType)ADC_CFG_GRP_SIZE;t_udGrp++ ) {
		t_udHWUnit		= Adc_GetHWUnitID(t_udGrp);
		t_u2CnvChSize	= Adc_GetCnvChSize(t_udGrp);
		t_u2VCSP		= t_u2CrntVChNbr[t_udHWUnit];				/* virtual pointer start	*/	
		t_u2VCEP		= t_u2VCSP + t_u2CnvChSize - ADC_VCEP_CAL;	/* virtual pointer end		*/	
		Adc_Pil_SetSGVCPR(t_u2SGVCPR,t_udGrp,t_u2VCSP,t_u2VCEP);	/* SGVCPR					*/
		Adc_Pil_SetSGCR(t_u1SGCR,t_udGrp);							/* SGCR						*/
		Adc_Pil_SetVCR(t_u4VCR,t_udGrp,t_u2VCSP);					/* VCR						*/
		Adc_Pil_CrctVCEP(t_u2CrntVChNbr,t_udGrp,t_u2VCEP);			/* correct VCEP				*/

		#ifdef ADC_USE_TH
		/* THxCR	*/
		t_cpstGrpHWInfo	= Adc_cstUserConfig.cpstHWConfig->cpstGrpHWInfo;
		t_udTHGrpTmp	= ADC_TH_GRP_NONE;
		if (t_udHWUnit<ADC_HWUNIT_WTH_NUM) {
			t_u1CrntTHGrpCount = t_u1THGrpCount[t_udHWUnit];
			t_blisComplete = FALSE;
			for ( t_u2CnvCh=0; t_u2CnvCh<t_u2CnvChSize; t_u2CnvCh++ ) {
				t_udCH = t_cpstGrpHWInfo[t_udGrp].cudCnvChTbl[t_u2CnvCh];
				for ( i=0; i<ADC_TH_NUM;i++) {
					if ( t_udCH == Adc_cstUserConfig.cpstHWConfig->cudHWTHCHTbl[t_udHWUnit][i] ) {
						/* Use T&H 	*/
						if (t_u1CrntTHGrpCount<ADC_TH_GRP_NUM) {
							t_udSG										= Adc_GetSGID(t_udGrp);
							t_udTHGrpTmp								= (Adc_TrackHoldGroupType)t_u1CrntTHGrpCount;
							t_u1THxCR[t_udHWUnit][t_u1CrntTHGrpCount]	= s_cu1THCnvSGTbl[t_udSG];
							t_u1THSMPSTCR[t_udHWUnit]					= ADC_TH_SAMPLING_START;
							t_udTHGrpId[t_udHWUnit][t_u1CrntTHGrpCount]	= t_udGrp;
							t_u1CrntTHGrpCount++;
							t_u1THGrpCount[t_udHWUnit]					= t_u1CrntTHGrpCount;
							t_blisComplete								= TRUE;
							break;
						}
					}
				}
				if (t_blisComplete==TRUE) {
					break;
				}
			}
		}
		#endif
		Adc_Pil_SetSGTSEL(t_u4SGTSEL,t_udGrp);									/* SGTSEL:Unit2(U2A),UnitA(U2B)	*/
		/* Adc_CnvInfoType	*/
		#ifdef ADC_USE_TH
		t_u2VCStartPos[t_udGrp]	= t_u2VCSP;
		t_udTHGrp[t_udGrp]		= t_udTHGrpTmp;
		#endif
	}
	#ifdef ADC_USE_TH
	/* THGSR VCR(for T&H))	*/
	for(t_udHWUnit=ADC_HWUNIT0;t_udHWUnit<(Adc_HWUnitType)ADC_HWUNIT_WTH_NUM;t_udHWUnit++) {
		for(t_udTHGrpTmp=ADC_TH_GRP_A;t_udTHGrpTmp<ADC_TH_GRP_NUM;t_udTHGrpTmp++) {
			t_udGrp	= t_udTHGrpId[t_udHWUnit][t_udTHGrpTmp];
			if ( ADC_GRP_NONE != t_udGrp ) {
				/* T&H use	*/
				t_u2CnvChSize	= Adc_GetCnvChSize(t_udGrp);
				#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
				t_u2THGSRValue	= (uint16)ADC_ZERO;
				#endif
				for (t_u2CnvCh=0; t_u2CnvCh<t_u2CnvChSize; t_u2CnvCh++) {
					t_udCH = t_cpstGrpHWInfo[t_udGrp].cudCnvChTbl[t_u2CnvCh] ;
					for ( i=0; i<ADC_TH_NUM; i++) {
						if (t_udCH== Adc_cstUserConfig.cpstHWConfig->cudHWTHCHTbl[t_udHWUnit][i] ) {
							/* T&H use channel	*/
							/* VCR Setting		*/
							t_u2VCSP = t_u2VCStartPos[t_udGrp] + t_u2CnvCh;
							t_u4VCR[t_udHWUnit][t_u2VCSP] |= ADC_VCR_TH;
							/* THGSR setting	*/
							#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
							if (t_udTHGrpTmp==ADC_TH_GRP_B) {
								t_u2THGSRValue |= s_cu2THCnvGrpBTbl[t_udCH];
							}
							#endif
							break;
						}
					}
				}
			}
		}

		#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
		t_u2THGSR[t_udHWUnit] = t_u2THGSRValue;
		#endif
	}
	Adc_SetTHGrp(&t_udTHGrp[ADC_ZERO]);
	#endif
}

/************************************************************************************************/
/* Service name			: Adc_Pil_SetSGVCPR														*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* 		VCSP			: Virtual channel start pointer											*/
/* 		VCEP			: Virtual channel end pointer											*/
/* Parameters (inout)	: 																		*/
/*		SGVCPR			: Async: SGVCPR		register setting value								*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: calcuate the SGVCPR register setting value							*/
/************************************************************************************************/
static FUNC(void, ADC_CODE) Adc_Pil_SetSGVCPR(
	VAR(uint16,				ADC_VAR_NO_INIT)	t_u2SGVCPR[ADC_HWUNIT_NUM][ADC_SG_NUM],
	CONST(Adc_GroupType,	ADC_CONST)			t_cudGrp,
	CONST(uint16,			ADC_CONST)			t_cu2VCSP,
	CONST(uint16,			ADC_CONST)			t_cu2VCEP
)
{
	VAR(Adc_HWUnitType,	ADC_VAR_NO_INIT)	t_udHWUnit;
	VAR(Adc_SGType,		ADC_VAR_NO_INIT)	t_udSG;

	t_udHWUnit	= Adc_GetHWUnitID(t_cudGrp);
	t_udSG		= Adc_GetSGID(t_cudGrp);
	if ((t_udHWUnit<ADC_HWUNIT_NUM) && (t_udSG<ADC_SG_NUM)) {
		t_u2SGVCPR[t_udHWUnit][t_udSG] = (uint16)(t_cu2VCEP * (uint16)ADC_SGVCPR_VCEP_0)
									   + (uint16)(t_cu2VCSP * (uint16)ADC_SGVCPR_VCSP_0);
	}
}

/************************************************************************************************/
/* Service name			: Adc_Pil_SetSGCR														*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* Parameters (inout)	: 																		*/
/*		SGCR			: Async: SGCR		register setting value								*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: calcuate the SGCR register setting value								*/
/************************************************************************************************/
static FUNC(void, ADC_CODE) Adc_Pil_SetSGCR(
	VAR(uint8,				ADC_VAR_NO_INIT)	t_u1SGCR[ADC_HWUNIT_NUM][ADC_SG_NUM],
	CONST(Adc_GroupType,	ADC_CONST)			t_cudGrp
)
{
	VAR(Adc_HWUnitType,	ADC_VAR_NO_INIT)	t_udHWUnit;
	VAR(Adc_SGType,		ADC_VAR_NO_INIT)	t_udSG;

	t_udHWUnit	= Adc_GetHWUnitID(t_cudGrp);
	t_udSG		= Adc_GetSGID(t_cudGrp);
	if ((t_udHWUnit<ADC_HWUNIT_NUM) && (t_udSG<ADC_SG_NUM)) {
		t_u1SGCR[t_udHWUnit][t_udSG] = Adc_cstUserConfig.cpstHWConfig->cu1SGCR[t_cudGrp];
	}
}

/************************************************************************************************/
/* Service name			: Adc_Pil_SetVCR														*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* 		VCSP			: Virtual channel start pointer											*/
/* Parameters (inout)	: 																		*/
/*		VCR				: Async: VCR	register setting value									*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: calcuate the VCR register setting value								*/
/************************************************************************************************/
static FUNC(void, ADC_CODE) Adc_Pil_SetVCR(
	VAR(uint32,				ADC_VAR_NO_INIT)	t_u4VCR[ADC_HWUNIT_NUM][ADC_CHANNEL_NUM],
	CONST(Adc_GroupType,	ADC_CONST)			t_cudGrp,
	CONST(uint16,			ADC_CONST)			t_cu2VCSP
)
{
	VAR(Adc_HWUnitType,	ADC_VAR_NO_INIT)	t_udHWUnit;
	VAR(Adc_SGType,		ADC_VAR_NO_INIT)	t_udSG;
	VAR(uint16, 		ADC_VAR_NO_INIT)	t_u2CnvCh;
	VAR(uint16, 		ADC_VAR_NO_INIT)	t_u2CnvChSize;

	t_udHWUnit		= Adc_GetHWUnitID(t_cudGrp);
	t_udSG			= Adc_GetSGID(t_cudGrp);
	t_u2CnvChSize	= Adc_GetCnvChSize(t_cudGrp);

	for (t_u2CnvCh=0;t_u2CnvCh<t_u2CnvChSize;t_u2CnvCh++) {
		if ((t_udHWUnit<ADC_HWUNIT_NUM) && (t_udSG<ADC_SG_NUM)) {
			t_u4VCR[t_udHWUnit][t_cu2VCSP+t_u2CnvCh]
				= (uint32)(Adc_cstUserConfig.cpstHWConfig->cpstGrpHWInfo[t_cudGrp].cudCnvChTbl[t_u2CnvCh]);
		}
	}
}

/************************************************************************************************/
/* Service name			: Adc_Pil_CrctVCEP														*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* 		VCEP			: Virtual channel end pointer											*/
/* Parameters (inout)	: 																		*/
/*		CrntVChNbr		: Async: Next virtual channel start position							*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: correct the VCEP														*/
/************************************************************************************************/
static FUNC(void, ADC_CODE) Adc_Pil_CrctVCEP(
	VAR(uint16, 			ADC_VAR_NO_INIT)	t_u2CrntVChNbr[ADC_HWUNIT_NUM],
	CONST(Adc_GroupType,	ADC_CONST)			t_cudGrp,
	CONST(uint16,			ADC_CONST)			t_cu2VCEP
)
{
	VAR(Adc_HWUnitType,	ADC_VAR_NO_INIT)	t_udHWUnit;
	VAR(uint16, 		ADC_VAR_NO_INIT)	t_u2CnvChSize;

	t_udHWUnit		= Adc_GetHWUnitID(t_cudGrp);
	t_u2CnvChSize	= Adc_GetCnvChSize(t_cudGrp);

	if (t_udHWUnit < ADC_HWUNIT_NUM) {
		if ((t_u2CnvChSize & ADC_ODD_EVE_JUDGE_MASK) == 0U) {
			t_u2CrntVChNbr[t_udHWUnit] = t_cu2VCEP + ADC_SGVCPR_EVENSET;	/* even		*/
		} else {
			t_u2CrntVChNbr[t_udHWUnit] = t_cu2VCEP + ADC_SGVCPR_ODDSET;		/* odd		*/
		}
	}
}

/************************************************************************************************/
/* Service name			: Adc_Pil_SetSGTSEL														*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* Parameters (inout)	: 																		*/
/*		SGTSEL			: Async: SGTSEL		register setting value								*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: calcuate the SGTSEL register setting value(U2A:Unit2,U2B:UnitA		*/
/************************************************************************************************/
static FUNC(void, ADC_CODE) Adc_Pil_SetSGTSEL(
	VAR(uint32,				ADC_VAR_NO_INIT)	t_u4SGTSEL[ADC_SG_NUM],
	CONST(Adc_GroupType,	ADC_CONST)			t_cudGrp
)
{
	#if ((MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A)				\
	 || ((MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)				\
		&& ((MCAL_PKG_TARGET==MCAL_PKG_U2B24_468PIN)			\
		 || (MCAL_PKG_TARGET==MCAL_PKG_U2B24_373PIN)			\
		 || (MCAL_PKG_TARGET==MCAL_PKG_U2B20_468PIN)			\
		 || (MCAL_PKG_TARGET==MCAL_PKG_U2B20_373PIN))))
		VAR(Adc_HWUnitType,			ADC_VAR_NO_INIT)	t_udHWUnit;
		VAR(Adc_TriggerSourceType,	ADC_VAR_NO_INIT)	t_udTriggerSource;
		VAR(Adc_SGType,				ADC_VAR_NO_INIT)	t_udSG;

		t_udHWUnit			= Adc_GetHWUnitID(t_cudGrp);
		t_udTriggerSource	= Adc_GetTriggerSource(t_cudGrp);
		if ((t_udHWUnit==ADC_SPECIFIC_HWUNIT) && (t_udTriggerSource==ADC_TRIGG_SRC_HW))  {
			t_udSG = Adc_GetSGID(t_cudGrp);
			if (t_udSG<ADC_SG_NUM) { 
				t_u4SGTSEL[t_udSG] = ADC_SetSGTSEL(	/* never wraparound :ignore QAC-3383/3384	*/
					Adc_cstUserConfig.cpstHWConfig->cpstGrpHWInfo[t_cudGrp].cu1HWTrgTaud2Ch7,
					Adc_cstUserConfig.cpstHWConfig->cpstGrpHWInfo[t_cudGrp].cu1HWTrgTaud2Ch15,
					Adc_cstUserConfig.cpstHWConfig->cpstGrpHWInfo[t_cudGrp].cu1HWTrgTauJ2Ch3,
					Adc_cstUserConfig.cpstHWConfig->cpstGrpHWInfo[t_cudGrp].cu1HWTrgTauJ3Ch3);
			}
		}
	#endif
}

/************************************************************************************************/
/* Service name			: Adc_Pil_GetVCStartPos													*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/* 		Adc_HWUnitType	: HW Unit Number														*/
/* 		Adc_SGType		: Scan Group Number														*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: Start Pos																*/
/* Description			: get the virtaul channel start position								*/
/************************************************************************************************/
#if ((ADC_CFG_START_STOP_GRP_API==STD_ON) || (ADC_CFG_READ_GRP_API==STD_ON) || (ADC_CFG_HW_TRG_API==STD_ON) || defined (ADC_USE_DMA))
static FUNC(uint16, ADC_CODE) Adc_Pil_GetVCStartPos(
	CONST(Adc_HWUnitType,	ADC_CONST)	t_cudHWUnit,
	CONST(Adc_SGType,		ADC_CONST)	t_cudSG
)
{
	return (uint16)(cpstReg_Adc[t_cudHWUnit]->stMODULE.stSG[t_cudSG].u2SGVCPR & (uint16)ADC_SGVCPR_VCSP);
}
#endif

/************************************************************************************************/
/* Service name			: Adc_Pil_GetVCEndPos													*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/* 		Adc_HWUnitType	: HW Unit Number														*/
/* 		Adc_SGType		: Scan Group Number														*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: End Pos																*/
/* Description			: get the virtaul channel end position									*/
/************************************************************************************************/
static FUNC(uint16, ADC_CODE) Adc_Pil_GetVCEndPos(
	CONST(Adc_HWUnitType,	ADC_CONST)	t_cudHWUnit,
	CONST(Adc_SGType,		ADC_CONST)	t_cudSG
)
{
	return (uint16)((cpstReg_Adc[t_cudHWUnit]->stMODULE.stSG[t_cudSG].u2SGVCPR & (uint16)ADC_SGVCPR_VCEP)>>ADC_SGVCPR_VCEP_BITPOS);
}

#define ADC_STOP_SEC_CODE_GLOBAL
#include "Adc_MemMap.h"

/*-- End Of File -------------------------------------------------------------------------------*/
