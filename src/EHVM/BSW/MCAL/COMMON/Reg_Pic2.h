/* Reg_PIC2-r04-303 */
/************************************************************************************************/
/*																								*/
/*		PIC2 register definition (for U2A/U2B)													*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/
#ifndef REG_PIC2_H
#define REG_PIC2_H

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include "Platform_Types.h"
#include "Mcal_SpalCmn.h"

/*==============================================================================================*/
/* defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/

/*----------------------------------------------------------------------------------------------*/
/* PIC2 HW info																					*/
/*----------------------------------------------------------------------------------------------*/
#define	PIC2_REG_ARRAY_SIZE						(1U)
#define	PIC2_REG_ARRAY_ID0						(0U)

#define	PIC2_REG_TAUD_SIZE						(2U)
#define	PIC2_REG_TAUD0							(0U)
#define	PIC2_REG_TAUD1							(1U)

#define	PIC2_TSEL_MAXSIZE						(4U)
#define	PIC2_TSEL_SG_MAXSIZE					(6U)			/* not support diag SG							*/
#define	PIC2_ADC_SG_MAXSIZE						(6U)
#define	PIC2_ADCTEN4nj_MAXSIZE					(3U)			/* ADTEN 4										*/
#define	PIC2_ADCTENynj_MAXSIZE					(4U)			/* ADTEN 5 -8									*/

/* ADTEN 4							*/
#define	PIC2_ADCTEN40j							(0U)
#define	PIC2_ADCTEN41j							(1U)

#if	(MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A) 
	#define	PIC2_HWUNIT_WPIC2_SIZE				(2U)
	#define	PIC2_ADC_SG_NUM						(5U)			/* (j) 0-4:scan group							*/
#elif (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	#define	PIC2_HWUNIT_WPIC2_SIZE				(4U)
	#define	PIC2_ADC_SG_NUM						(5U)			/* (j) 0-4:scan group, (5:SG-Diag(not support)	*/
	#define	PIC2_PIC24_ADCTCFG_SIZE				(10U)
#endif

/*----------------------------------------------------------------------------------------------*/
/* define register value 																		*/
/*----------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/
/* PIC2xADCXnTSELj : A/D Converter n(=0-3) Trigger Select Control Register j(=0-4)			*/
/*------------------------------------------------------------------------------------------*/
/* Setting Value	*/
#define PIC2_ADCXnTSEL_NOTSELECTED				(0U)
#define PIC2_ADCXnTSEL_SELECTED					(1U)

/* Bit position		*/
#define PIC2_PIC2xADCXnTSELj31					(BIT31)
#define PIC2_PIC2xADCXnTSELj30					(BIT30)
#define PIC2_PIC2xADCXnTSELj29					(BIT29)
#define PIC2_PIC2xADCXnTSELj28					(BIT28)
#define PIC2_PIC2xADCXnTSELj27					(BIT27)
#define PIC2_PIC2xADCXnTSELj26					(BIT26)
#define PIC2_PIC2xADCXnTSELj25					(BIT25)
#define PIC2_PIC2xADCXnTSELj24					(BIT24)
#define PIC2_PIC2xADCXnTSELj23					(BIT23)
#define PIC2_PIC2xADCXnTSELj22					(BIT22)
#define PIC2_PIC2xADCXnTSELj21					(BIT21)
#define PIC2_PIC2xADCXnTSELj20					(BIT20)
#define PIC2_PIC2xADCXnTSELj19					(BIT19)
#define PIC2_PIC2xADCXnTSELj18					(BIT18)
#define PIC2_PIC2xADCXnTSELj17					(BIT17)
#define PIC2_PIC2xADCXnTSELj16					(BIT16)
#define PIC2_PIC2xADCXnTSELj15					(BIT15)
#define PIC2_PIC2xADCXnTSELj14					(BIT14)
#define PIC2_PIC2xADCXnTSELj13					(BIT13)
#define PIC2_PIC2xADCXnTSELj12					(BIT12)
#define PIC2_PIC2xADCXnTSELj11					(BIT11)
#define PIC2_PIC2xADCXnTSELj10					(BIT10)
#define PIC2_PIC2xADCXnTSELj09					(BIT9)
#define PIC2_PIC2xADCXnTSELj08					(BIT8)
#define PIC2_PIC2xADCXnTSELj07					(BIT7)
#define PIC2_PIC2xADCXnTSELj06					(BIT6)
#define PIC2_PIC2xADCXnTSELj05					(BIT5)
#define PIC2_PIC2xADCXnTSELj04					(BIT4)
#define PIC2_PIC2xADCXnTSELj03					(BIT3)
#define PIC2_PIC2xADCXnTSELj02					(BIT2)
#define PIC2_PIC2xADCXnTSELj01					(BIT1)
#define PIC2_PIC2xADCXnTSELj00					(BIT0)

#if	(MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A) 
	#define		PIC2_20TSEL_DEFBIT					(PIC2_PIC2xADCXnTSELj06|PIC2_PIC2xADCXnTSELj05|PIC2_PIC2xADCXnTSELj04|PIC2_PIC2xADCXnTSELj03|PIC2_PIC2xADCXnTSELj01|PIC2_PIC2xADCXnTSELj00)
#elif (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	#define		PIC2_20TSEL_DEFBIT					(PIC2_PIC2xADCXnTSELj06|PIC2_PIC2xADCXnTSELj05|PIC2_PIC2xADCXnTSELj01|PIC2_PIC2xADCXnTSELj00)
#endif

#define		PIC2_21TSEL_DEFBIT					(PIC2_PIC2xADCXnTSELj01|PIC2_PIC2xADCXnTSELj00)

/*------------------------------------------------------------------------------------------*/
/* PIC2xADCXnEDGSEL : A/D Converter n Trigger Edge Selection Control Register				*/
/*------------------------------------------------------------------------------------------*/
/* Setting Value	*/
#define PIC2_ADCXnEDGSEL_RISING					(0U)
#define PIC2_ADCXnEDGSEL_FALLING				(1U)
#define PIC2_ADCXnEDGSEL_BOTH					(2U)
/* Bit position		*/
#define PIC2_PIC2xADCXnEDGSEL_SGDIAG			(BIT11+BIT10)	/* SG-Diag		*/
#define PIC2_PIC2xADCXnEDGSEL_SGDIAG_0			(BIT10)
#define PIC2_PIC2xADCXnEDGSEL_SG4				(BIT9+BIT8)		/* scan group 4	*/
#define PIC2_PIC2xADCXnEDGSEL_SG4_0				(BIT8)
#define PIC2_PIC2xADCXnEDGSEL_SG3				(BIT7+BIT6)		/* scan group 3	*/
#define PIC2_PIC2xADCXnEDGSEL_SG3_0				(BIT6)
#define PIC2_PIC2xADCXnEDGSEL_SG2				(BIT5+BIT4)		/* scan group 2	*/
#define PIC2_PIC2xADCXnEDGSEL_SG2_0				(BIT4)
#define PIC2_PIC2xADCXnEDGSEL_SG1				(BIT3+BIT2)		/* scan group 1	*/
#define PIC2_PIC2xADCXnEDGSEL_SG1_0				(BIT2)
#define PIC2_PIC2xADCXnEDGSEL_SG0				(BIT1+BIT0)		/* scan group 0	*/
#define PIC2_PIC2xADCXnEDGSEL_SG0_0				(BIT0)

#define		PIC2_EDGSEL_DEFBIT					(PIC2_PIC2xADCXnEDGSEL_SG4|PIC2_PIC2xADCXnEDGSEL_SG3|PIC2_PIC2xADCXnEDGSEL_SG2|PIC2_PIC2xADCXnEDGSEL_SG1|PIC2_PIC2xADCXnEDGSEL_SG0)

/*------------------------------------------------------------------------------------------*/
/* PIC20ADTEN4nj(U2A/U2B),PIC21ADTEN4nj(U2B)												*/
/*		: A/D Converter Trigger Output Selection Control Register (n=0to1;j=0to5)			*/
/*------------------------------------------------------------------------------------------*/
/* Setting Value (ADTEN common)	*/
#define PIC2_ADTEN_TRG_TAUD_NOTSELECT			(0U)
#define PIC2_ADTEN_TRG_TAUD_SELECTED			(1U)
/* Bit position		*/
#define PIC2_PIC2xADTEN_TRG_TAUD15				(BIT15)
#define PIC2_PIC2xADTEN_TRG_TAUD14				(BIT14)
#define PIC2_PIC2xADTEN_TRG_TAUD13				(BIT13)
#define PIC2_PIC2xADTEN_TRG_TAUD12				(BIT12)
#define PIC2_PIC2xADTEN_TRG_TAUD11				(BIT11)
#define PIC2_PIC2xADTEN_TRG_TAUD10				(BIT10)
#define PIC2_PIC2xADTEN_TRG_TAUD09				(BIT9)
#define PIC2_PIC2xADTEN_TRG_TAUD08				(BIT8)
#define PIC2_PIC2xADTEN_TRG_TAUD07				(BIT7)
#define PIC2_PIC2xADTEN_TRG_TAUD06				(BIT6)
#define PIC2_PIC2xADTEN_TRG_TAUD05				(BIT5)
#define PIC2_PIC2xADTEN_TRG_TAUD04				(BIT4)
#define PIC2_PIC2xADTEN_TRG_TAUD03				(BIT3)
#define PIC2_PIC2xADTEN_TRG_TAUD02				(BIT2)
#define PIC2_PIC2xADTEN_TRG_TAUD01				(BIT1)
#define PIC2_PIC2xADTEN_TRG_TAUD00				(BIT0)

#define		PIC2_ADTEN_TRG_TAUD_DEFBIT			(0xffffu)

/*------------------------------------------------------------------------------------------*/
/* PIC20ADTEN4nj : A/D Converter Trigger Output Selection Control Register (n=2;j=0to5)		*/
/*------------------------------------------------------------------------------------------*/
/* Setting Value (ADTEN common)	*/
#define PIC2_ADTEN_TRG_DISABLE					(0U)
#define PIC2_ADTEN_TRG_ENABLE					(1U)
/* Bit position		*/
#define PIC2_PIC2xADTEN_TRG_E1CLR				(BIT5)
#define PIC2_PIC2xADTEN_TRG_E1CMP1				(BIT4)
#define PIC2_PIC2xADTEN_TRG_E1CMP0				(BIT3)
#define PIC2_PIC2xADTEN_TRG_E0CLR				(BIT2)
#define PIC2_PIC2xADTEN_TRG_E0CMP1				(BIT1)
#define PIC2_PIC2xADTEN_TRG_E0CMP0				(BIT0)

/*------------------------------------------------------------------------------------------*/
/* PIC20ADTEN5nj : A/D Converter Trigger Output Selection Control Register (n=0to3;j=0to5)	*/
/*------------------------------------------------------------------------------------------*/
/* Setting Value (refer to PIC20ADTEN4nj)	*/
/* #define PIC2_ADTEN_TRG_DISABLE				(0U)	*/
/* #define PIC2_ADTEN_TRG_ENABLE				(1U)	*/
/* Bit position		*/
#if	(MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A) 
	#define PIC2_PIC2xADTEN_TRG_TIM3_CH7		(BIT31)
	#define PIC2_PIC2xADTEN_TRG_TIM3_CH6		(BIT30)
	#define PIC2_PIC2xADTEN_TRG_TIM3_CH5		(BIT29)
	#define PIC2_PIC2xADTEN_TRG_TIM3_CH4		(BIT28)
	#define PIC2_PIC2xADTEN_TRG_TIM3_CH3		(BIT27)
	#define PIC2_PIC2xADTEN_TRG_TIM3_CH2		(BIT26)
	#define PIC2_PIC2xADTEN_TRG_TIM3_CH1		(BIT25)
	#define PIC2_PIC2xADTEN_TRG_TIM3_CH0		(BIT24)
	#define PIC2_PIC2xADTEN_TRG_TIM2_CH7		(BIT23)
	#define PIC2_PIC2xADTEN_TRG_TIM2_CH6		(BIT22)
	#define PIC2_PIC2xADTEN_TRG_TIM2_CH5		(BIT21)
	#define PIC2_PIC2xADTEN_TRG_TIM2_CH4		(BIT20)
	#define PIC2_PIC2xADTEN_TRG_TIM2_CH3		(BIT19)
	#define PIC2_PIC2xADTEN_TRG_TIM2_CH2		(BIT18)
	#define PIC2_PIC2xADTEN_TRG_TIM2_CH1		(BIT17)
	#define PIC2_PIC2xADTEN_TRG_TIM2_CH0		(BIT16)
	#define PIC2_PIC2xADTEN_TRG_TIM1_CH7		(BIT15)
	#define PIC2_PIC2xADTEN_TRG_TIM1_CH6		(BIT14)
	#define PIC2_PIC2xADTEN_TRG_TIM1_CH5		(BIT13)
	#define PIC2_PIC2xADTEN_TRG_TIM1_CH4		(BIT12)
	#define PIC2_PIC2xADTEN_TRG_TIM1_CH3		(BIT11)
	#define PIC2_PIC2xADTEN_TRG_TIM1_CH2		(BIT10)
	#define PIC2_PIC2xADTEN_TRG_TIM1_CH1		(BIT9)
	#define PIC2_PIC2xADTEN_TRG_TIM1_CH0		(BIT8)
	#define PIC2_PIC2xADTEN_TRG_TIM0_CH7		(BIT7)
	#define PIC2_PIC2xADTEN_TRG_TIM0_CH6		(BIT6)
	#define PIC2_PIC2xADTEN_TRG_TIM0_CH5		(BIT5)
	#define PIC2_PIC2xADTEN_TRG_TIM0_CH4		(BIT4)
	#define PIC2_PIC2xADTEN_TRG_TIM0_CH3		(BIT3)
	#define PIC2_PIC2xADTEN_TRG_TIM0_CH2		(BIT2)
	#define PIC2_PIC2xADTEN_TRG_TIM0_CH1		(BIT1)
	#define PIC2_PIC2xADTEN_TRG_TIM0_CH0		(BIT0)
#elif (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	#define PIC2_PIC2xADTEN_TRG_GTM19			(BIT19)
	#define PIC2_PIC2xADTEN_TRG_GTM18			(BIT18)
	#define PIC2_PIC2xADTEN_TRG_GTM17			(BIT17)
	#define PIC2_PIC2xADTEN_TRG_GTM16			(BIT16)
	#define PIC2_PIC2xADTEN_TRG_GTM15			(BIT15)
	#define PIC2_PIC2xADTEN_TRG_GTM14			(BIT14)
	#define PIC2_PIC2xADTEN_TRG_GTM13			(BIT13)
	#define PIC2_PIC2xADTEN_TRG_GTM12			(BIT12)
	#define PIC2_PIC2xADTEN_TRG_GTM11			(BIT11)
	#define PIC2_PIC2xADTEN_TRG_GTM10			(BIT10)
	#define PIC2_PIC2xADTEN_TRG_GTM9			(BIT9)
	#define PIC2_PIC2xADTEN_TRG_GTM8			(BIT8)
	#define PIC2_PIC2xADTEN_TRG_GTM7			(BIT7)
	#define PIC2_PIC2xADTEN_TRG_GTM6			(BIT6)
	#define PIC2_PIC2xADTEN_TRG_GTM5			(BIT5)
	#define PIC2_PIC2xADTEN_TRG_GTM4			(BIT4)
	#define PIC2_PIC2xADTEN_TRG_GTM3			(BIT3)
	#define PIC2_PIC2xADTEN_TRG_GTM2			(BIT2)
	#define PIC2_PIC2xADTEN_TRG_GTM1			(BIT1)
	#define PIC2_PIC2xADTEN_TRG_GTM0			(BIT0)
#endif

#if	(MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A) 
/*------------------------------------------------------------------------------------------*/
/* PIC20ADTEN6nj : A/D Converter Trigger Output Selection Control Register (n:0to1)			*/
/*------------------------------------------------------------------------------------------*/
/* Setting Value (refer to PIC20ADTEN4nj)	*/
/* #define PIC2_ADTEN_TRG_DISABLE				(0U)	*/
/* #define PIC2_ADTEN_TRG_ENABLE				(1U)	*/
/* Bit position		*/
#define PIC2_PIC2xADTEN_TRG_AM1CH7_IVMR			(BIT31)
#define PIC2_PIC2xADTEN_TRG_AM1CH7_TMR			(BIT30)
#define PIC2_PIC2xADTEN_TRG_AM1CH6_IVMR			(BIT29)
#define PIC2_PIC2xADTEN_TRG_AM1CH6_TMR			(BIT28)
#define PIC2_PIC2xADTEN_TRG_AM1CH5_IVMR			(BIT27)
#define PIC2_PIC2xADTEN_TRG_AM1CH5_TMR			(BIT26)
#define PIC2_PIC2xADTEN_TRG_AM1CH4_IVMR			(BIT25)
#define PIC2_PIC2xADTEN_TRG_AM1CH4_TMR			(BIT24)
#define PIC2_PIC2xADTEN_TRG_AM1CH3_IVMR			(BIT23)
#define PIC2_PIC2xADTEN_TRG_AM1CH3_TMR			(BIT22)
#define PIC2_PIC2xADTEN_TRG_AM1CH2_IVMR			(BIT21)
#define PIC2_PIC2xADTEN_TRG_AM1CH2_TMR			(BIT20)
#define PIC2_PIC2xADTEN_TRG_AM1CH1_IVMR			(BIT19)
#define PIC2_PIC2xADTEN_TRG_AM1CH1_TMR			(BIT18)
#define PIC2_PIC2xADTEN_TRG_AM1CH0_IVMR			(BIT17)
#define PIC2_PIC2xADTEN_TRG_AM1CH0_TMR			(BIT16)	
#define PIC2_PIC2xADTEN_TRG_AM0CH7_IVMR			(BIT15)
#define PIC2_PIC2xADTEN_TRG_AM0CH7_TMR			(BIT14)
#define PIC2_PIC2xADTEN_TRG_AM0CH6_IVMR			(BIT13)
#define PIC2_PIC2xADTEN_TRG_AM0CH6_TMR			(BIT12)
#define PIC2_PIC2xADTEN_TRG_AM0CH5_IVMR			(BIT11)
#define PIC2_PIC2xADTEN_TRG_AM0CH5_TMR			(BIT10)
#define PIC2_PIC2xADTEN_TRG_AM0CH4_IVMR			(BIT9)
#define PIC2_PIC2xADTEN_TRG_AM0CH4_TMR			(BIT8)
#define PIC2_PIC2xADTEN_TRG_AM0CH3_IVMR			(BIT7)
#define PIC2_PIC2xADTEN_TRG_AM0CH3_TMR			(BIT6)
#define PIC2_PIC2xADTEN_TRG_AM0CH2_IVMR			(BIT5)
#define PIC2_PIC2xADTEN_TRG_AM0CH2_TMR			(BIT4)
#define PIC2_PIC2xADTEN_TRG_AM0CH1_IVMR			(BIT3)
#define PIC2_PIC2xADTEN_TRG_AM0CH1_TMR			(BIT2)
#define PIC2_PIC2xADTEN_TRG_AM0CH0_IVMR			(BIT1)
#define PIC2_PIC2xADTEN_TRG_AM0CH0_TMR			(BIT0)
#endif

/*------------------------------------------------------------------------------------------*/
/* PIC20ADTEN7nj : A/D Converter Trigger Output Selection Control Register (n=0to3;j=0to5)	*/
/*------------------------------------------------------------------------------------------*/
/* Setting Value (refer to PIC20ADTEN4nj)	*/
/* #define PIC2_ADTEN_TRG_DISABLE				(0U)	*/
/* #define PIC2_ADTEN_TRG_ENABLE				(1U)	*/
/* Bit position		*/
#if	(MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A) 
	#define PIC2_PIC2xADTEN_TRG_AM3CH7_IVMR		(BIT31)
	#define PIC2_PIC2xADTEN_TRG_AM3CH7_TMR		(BIT30)
	#define PIC2_PIC2xADTEN_TRG_AM3CH6_IVMR		(BIT29)
	#define PIC2_PIC2xADTEN_TRG_AM3CH6_TMR		(BIT28)
	#define PIC2_PIC2xADTEN_TRG_AM3CH5_IVMR		(BIT27)
	#define PIC2_PIC2xADTEN_TRG_AM3CH5_TMR		(BIT26)
	#define PIC2_PIC2xADTEN_TRG_AM3CH4_IVMR		(BIT25)
	#define PIC2_PIC2xADTEN_TRG_AM3CH4_TMR		(BIT24)
	#define PIC2_PIC2xADTEN_TRG_AM3CH3_IVMR		(BIT23)
	#define PIC2_PIC2xADTEN_TRG_AM3CH3_TMR		(BIT22)
	#define PIC2_PIC2xADTEN_TRG_AM3CH2_IVMR		(BIT21)
	#define PIC2_PIC2xADTEN_TRG_AM3CH2_TMR		(BIT20)
	#define PIC2_PIC2xADTEN_TRG_AM3CH1_IVMR		(BIT19)
	#define PIC2_PIC2xADTEN_TRG_AM3CH1_TMR		(BIT18)
	#define PIC2_PIC2xADTEN_TRG_AM3CH0_IVMR		(BIT17)
	#define PIC2_PIC2xADTEN_TRG_AM3CH0_TMR		(BIT16)	
	#define PIC2_PIC2xADTEN_TRG_AM2CH7_IVMR		(BIT15)
	#define PIC2_PIC2xADTEN_TRG_AM2CH7_TMR		(BIT14)
	#define PIC2_PIC2xADTEN_TRG_AM2CH6_IVMR		(BIT13)
	#define PIC2_PIC2xADTEN_TRG_AM2CH6_TMR		(BIT12)
	#define PIC2_PIC2xADTEN_TRG_AM2CH5_IVMR		(BIT11)
	#define PIC2_PIC2xADTEN_TRG_AM2CH5_TMR		(BIT10)
	#define PIC2_PIC2xADTEN_TRG_AM2CH4_IVMR		(BIT9)
	#define PIC2_PIC2xADTEN_TRG_AM2CH4_TMR		(BIT8)
	#define PIC2_PIC2xADTEN_TRG_AM2CH3_IVMR		(BIT7)
	#define PIC2_PIC2xADTEN_TRG_AM2CH3_TMR		(BIT6)
	#define PIC2_PIC2xADTEN_TRG_AM2CH2_IVMR		(BIT5)
	#define PIC2_PIC2xADTEN_TRG_AM2CH2_TMR		(BIT4)
	#define PIC2_PIC2xADTEN_TRG_AM2CH1_IVMR		(BIT3)
	#define PIC2_PIC2xADTEN_TRG_AM2CH1_TMR		(BIT2)
	#define PIC2_PIC2xADTEN_TRG_AM2CH0_IVMR		(BIT1)
	#define PIC2_PIC2xADTEN_TRG_AM2CH0_TMR		(BIT0)
#elif (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD93ON		(BIT19)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD92ON		(BIT18)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD91ON		(BIT17)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD90ON		(BIT15)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD63ON		(BIT15)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD62ON		(BIT14)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD61ON		(BIT13)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD60ON		(BIT12)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD43ON		(BIT11)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD42ON		(BIT10)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD41ON		(BIT9)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD40ON		(BIT8)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD23ON		(BIT7)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD22ON		(BIT6)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD21ON		(BIT5)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD20ON		(BIT4)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD03ON		(BIT3)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD02ON		(BIT2)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD01ON		(BIT1)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD00ON		(BIT0)
#endif

/*------------------------------------------------------------------------------------------*/
/* PIC20ADTEN8nj : A/D Converter Trigger Output Selection Control Register (n=0to3;j=0to5)	*/
/*------------------------------------------------------------------------------------------*/
/* Setting Value (refer to PIC20ADTEN4nj)	*/
/* #define PIC2_ADTEN_TRG_DISABLE				(0U)	*/
/* #define PIC2_ADTEN_TRG_ENABLE				(1U)	*/
/* Bit position		*/
#if	(MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A) 
	#define PIC2_PIC2xADTEN_TRG_MCS3_CH7		(BIT31)
	#define PIC2_PIC2xADTEN_TRG_MCS3_CH6		(BIT30)
	#define PIC2_PIC2xADTEN_TRG_MCS3_CH5		(BIT29)
	#define PIC2_PIC2xADTEN_TRG_MCS3_CH4		(BIT28)
	#define PIC2_PIC2xADTEN_TRG_MCS3_CH3		(BIT27)
	#define PIC2_PIC2xADTEN_TRG_MCS3_CH2		(BIT26)
	#define PIC2_PIC2xADTEN_TRG_MCS3_CH1		(BIT25)
	#define PIC2_PIC2xADTEN_TRG_MCS3_CH0		(BIT24)
	#define PIC2_PIC2xADTEN_TRG_MCS2_CH7		(BIT23)
	#define PIC2_PIC2xADTEN_TRG_MCS2_CH6		(BIT22)
	#define PIC2_PIC2xADTEN_TRG_MCS2_CH5		(BIT21)
	#define PIC2_PIC2xADTEN_TRG_MCS2_CH4		(BIT20)
	#define PIC2_PIC2xADTEN_TRG_MCS2_CH3		(BIT19)
	#define PIC2_PIC2xADTEN_TRG_MCS2_CH2		(BIT18)
	#define PIC2_PIC2xADTEN_TRG_MCS2_CH1		(BIT17)
	#define PIC2_PIC2xADTEN_TRG_MCS2_CH0		(BIT16)	
	#define PIC2_PIC2xADTEN_TRG_MCS1_CH7		(BIT15)
	#define PIC2_PIC2xADTEN_TRG_MCS1_CH6		(BIT14)
	#define PIC2_PIC2xADTEN_TRG_MCS1_CH5		(BIT13)
	#define PIC2_PIC2xADTEN_TRG_MCS1_CH4		(BIT12)
	#define PIC2_PIC2xADTEN_TRG_MCS1_CH3		(BIT11)
	#define PIC2_PIC2xADTEN_TRG_MCS1_CH2		(BIT10)
	#define PIC2_PIC2xADTEN_TRG_MCS1_CH1		(BIT9)
	#define PIC2_PIC2xADTEN_TRG_MCS1_CH0		(BIT8)
	#define PIC2_PIC2xADTEN_TRG_MCS0_CH7		(BIT7)
	#define PIC2_PIC2xADTEN_TRG_MCS0_CH6		(BIT6)
	#define PIC2_PIC2xADTEN_TRG_MCS0_CH5		(BIT5)
	#define PIC2_PIC2xADTEN_TRG_MCS0_CH4		(BIT4)
	#define PIC2_PIC2xADTEN_TRG_MCS0_CH3		(BIT3)
	#define PIC2_PIC2xADTEN_TRG_MCS0_CH2		(BIT2)
	#define PIC2_PIC2xADTEN_TRG_MCS0_CH1		(BIT1)
	#define PIC2_PIC2xADTEN_TRG_MCS0_CH0		(BIT0)
#elif (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD93OFF		(BIT19)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD92OFF		(BIT18)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD91OFF		(BIT17)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD90OFF		(BIT15)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD63OFF		(BIT15)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD62OFF		(BIT14)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD61OFF		(BIT13)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD60OFF		(BIT12)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD43OFF		(BIT11)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD42OFF		(BIT10)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD41OFF		(BIT9)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD40OFF		(BIT8)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD23OFF		(BIT7)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD22OFF		(BIT6)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD21OFF		(BIT5)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD20OFF		(BIT4)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD03OFF		(BIT3)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD02OFF		(BIT2)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD01OFF		(BIT1)
	#define PIC2_PIC2xADTEN_TRG_ATUTMD00OFF		(BIT0)
#endif

/*------------------------------------------------------------------------------------------*/
/* PIC21ADTEN5nj : A/D Converter Trigger Output Control Register (n=0to3;j=0to5)			*/
/*------------------------------------------------------------------------------------------*/
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	/* Setting Value (refer to PIC20ADTEN4nj)	*/
	/* #define PIC2_ADTEN_TRG_DISABLE			(0U)	*/
	/* #define PIC2_ADTEN_TRG_ENABLE			(1U)	*/
	/* Bit position		*/
	#define PIC2_PIC2xADTEN5_TRG_GRC73			(BIT31)
	#define PIC2_PIC2xADTEN5_TRG_GRC72			(BIT30)
	#define PIC2_PIC2xADTEN5_TRG_GRC71			(BIT29)
	#define PIC2_PIC2xADTEN5_TRG_GRC70			(BIT28)
	#define PIC2_PIC2xADTEN5_TRG_GRC63			(BIT27)
	#define PIC2_PIC2xADTEN5_TRG_GRC62			(BIT26)
	#define PIC2_PIC2xADTEN5_TRG_GRC61			(BIT25)
	#define PIC2_PIC2xADTEN5_TRG_GRC60			(BIT24)
	#define PIC2_PIC2xADTEN5_TRG_GRC43			(BIT23)
	#define PIC2_PIC2xADTEN5_TRG_GRC42			(BIT22)
	#define PIC2_PIC2xADTEN5_TRG_GRC41			(BIT21)
	#define PIC2_PIC2xADTEN5_TRG_GRC40			(BIT20)
	#define PIC2_PIC2xADTEN5_TRG_GRC03			(BIT19)
	#define PIC2_PIC2xADTEN5_TRG_GRC02			(BIT18)
	#define PIC2_PIC2xADTEN5_TRG_GRC01			(BIT17)
	#define PIC2_PIC2xADTEN5_TRG_GRC00			(BIT16)	
	#define PIC2_PIC2xADTEN5_TRG_OCRG7			(BIT15)
	#define PIC2_PIC2xADTEN5_TRG_OCRG6			(BIT14)
	#define PIC2_PIC2xADTEN5_TRG_OCRG5			(BIT13)
	#define PIC2_PIC2xADTEN5_TRG_OCRG4			(BIT12)
	#define PIC2_PIC2xADTEN5_TRG_OCRG3			(BIT11)
	#define PIC2_PIC2xADTEN5_TRG_OCRG2			(BIT10)
	#define PIC2_PIC2xADTEN5_TRG_OCRG1			(BIT9)
	#define PIC2_PIC2xADTEN5_TRG_OCRG0			(BIT8)
	#define PIC2_PIC2xADTEN5_TRG_ATU			(BIT0)
#endif

/*------------------------------------------------------------------------------------------*/
/* PIC21ADTEN6nj : A/D Converter Trigger Output Control Register (n=0to3;j=0to5)			*/
/* PIC21DSADTEN0n1 : DSADC Start Trigger Output Control Register (n=0to3,8to13)				*/
/* PIC21DSADTEN1n1 : DSADC Stop Trigger Output Control Register (n=0to3,8to13)				*/
/*------------------------------------------------------------------------------------------*/
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	/* Setting Value (refer to PIC20ADTEN4nj)	*/
	/* #define PIC2_ADTEN_TRG_DISABLE			(0U)	*/
	/* #define PIC2_ADTEN_TRG_ENABLE			(1U)	*/
	/* Bit position		*/
	#define PIC2_PIC2xADTEN_TRG_OCRG13			(BIT29)
	#define PIC2_PIC2xADTEN_TRG_OCRG12			(BIT28)
	#define PIC2_PIC2xADTEN_TRG_OCRG11			(BIT27)
	#define PIC2_PIC2xADTEN_TRG_OCRG10			(BIT26)
	#define PIC2_PIC2xADTEN_TRG_OCRG9			(BIT25)
	#define PIC2_PIC2xADTEN_TRG_OCRG8			(BIT24)
	#define PIC2_PIC2xADTEN_TRG_OCR1D113		(BIT23)
	#define PIC2_PIC2xADTEN_TRG_OCR1D112		(BIT22)
	#define PIC2_PIC2xADTEN_TRG_OCR1D111		(BIT21)
	#define PIC2_PIC2xADTEN_TRG_OCR1D110		(BIT20)
	#define PIC2_PIC2xADTEN_TRG_OCR1D93			(BIT19)
	#define PIC2_PIC2xADTEN_TRG_OCR1D92			(BIT18)
	#define PIC2_PIC2xADTEN_TRG_OCR1D91			(BIT17)
	#define PIC2_PIC2xADTEN_TRG_OCR1D90			(BIT16)	
	#define PIC2_PIC2xADTEN_TRG_OCR1D63			(BIT15)
	#define PIC2_PIC2xADTEN_TRG_OCR1D62			(BIT14)
	#define PIC2_PIC2xADTEN_TRG_OCR1D61			(BIT13)
	#define PIC2_PIC2xADTEN_TRG_OCR1D60			(BIT12)
	#define PIC2_PIC2xADTEN_TRG_OCR1D43			(BIT11)
	#define PIC2_PIC2xADTEN_TRG_OCR1D42			(BIT10)
	#define PIC2_PIC2xADTEN_TRG_OCR1D41			(BIT9)
	#define PIC2_PIC2xADTEN_TRG_OCR1D40			(BIT8)
	#define PIC2_PIC2xADTEN_TRG_OCR1D23			(BIT7)
	#define PIC2_PIC2xADTEN_TRG_OCR1D22			(BIT6)
	#define PIC2_PIC2xADTEN_TRG_OCR1D21			(BIT5)
	#define PIC2_PIC2xADTEN_TRG_OCR1D20			(BIT4)
	#define PIC2_PIC2xADTEN_TRG_OCR1D03			(BIT3)
	#define PIC2_PIC2xADTEN_TRG_OCR1D02			(BIT2)
	#define PIC2_PIC2xADTEN_TRG_OCR1D01			(BIT1)
	#define PIC2_PIC2xADTEN_TRG_OCR1D00			(BIT0)
#endif

/*------------------------------------------------------------------------------------------*/
/* PIC21ADTEN7nj : A/D Converter Trigger Output Control Register (n=0to3;j=0to5)			*/
/* PIC21DSADTEN0n2 : DSADC Start Trigger Output Control Register (n=0to3,8to13)				*/
/* PIC21DSADTEN1n2 : DSADC Stop Trigger Output Control Register (n=0to3,8to13)				*/
/*------------------------------------------------------------------------------------------*/
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	/* Setting Value (refer to PIC20ADTEN4nj)	*/
	/* #define PIC2_ADTEN_TRG_DISABLE			(0U)	*/
	/* #define PIC2_ADTEN_TRG_ENABLE			(1U)	*/
	/* Bit position		*/
	#define PIC2_PIC2xADTEN_TRG_OCR2D113		(BIT23)
	#define PIC2_PIC2xADTEN_TRG_OCR2D112		(BIT22)
	#define PIC2_PIC2xADTEN_TRG_OCR2D111		(BIT21)
	#define PIC2_PIC2xADTEN_TRG_OCR2D110		(BIT20)
	#define PIC2_PIC2xADTEN_TRG_OCR2D93			(BIT19)
	#define PIC2_PIC2xADTEN_TRG_OCR2D92			(BIT18)
	#define PIC2_PIC2xADTEN_TRG_OCR2D91			(BIT17)
	#define PIC2_PIC2xADTEN_TRG_OCR2D90			(BIT16)	
	#define PIC2_PIC2xADTEN_TRG_OCR2D63			(BIT15)
	#define PIC2_PIC2xADTEN_TRG_OCR2D62			(BIT14)
	#define PIC2_PIC2xADTEN_TRG_OCR2D61			(BIT13)
	#define PIC2_PIC2xADTEN_TRG_OCR2D60			(BIT12)
	#define PIC2_PIC2xADTEN_TRG_OCR2D43			(BIT11)
	#define PIC2_PIC2xADTEN_TRG_OCR2D42			(BIT10)
	#define PIC2_PIC2xADTEN_TRG_OCR2D41			(BIT9)
	#define PIC2_PIC2xADTEN_TRG_OCR2D40			(BIT8)
	#define PIC2_PIC2xADTEN_TRG_OCR2D23			(BIT7)
	#define PIC2_PIC2xADTEN_TRG_OCR2D22			(BIT6)
	#define PIC2_PIC2xADTEN_TRG_OCR2D21			(BIT5)
	#define PIC2_PIC2xADTEN_TRG_OCR2D20			(BIT4)
	#define PIC2_PIC2xADTEN_TRG_OCR2D03			(BIT3)
	#define PIC2_PIC2xADTEN_TRG_OCR2D02			(BIT2)
	#define PIC2_PIC2xADTEN_TRG_OCR2D01			(BIT1)
	#define PIC2_PIC2xADTEN_TRG_OCR2D00			(BIT0)
#endif

/*------------------------------------------------------------------------------------------*/
/* PIC21ADTEN8nj : A/D Converter Trigger Output Control Register (n=0to3;j=0to5)			*/
/* PIC21DSADTEN0n3 : DSADC Start Trigger Output Control Register (n=0to3,8to13)				*/
/* PIC21DSADTEN1n3 : DSADC Stop Trigger Output Control Register (n=0to3,8to13)				*/
/*------------------------------------------------------------------------------------------*/
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	/* Setting Value (refer to PIC20ADTEN4nj)	*/
	/* #define PIC2_ADTEN_TRG_DISABLE			(0U)	*/
	/* #define PIC2_ADTEN_TRG_ENABLE			(1U)	*/
	/* Bit position		*/
	#define PIC2_PIC2xADTEN_TRG_UDID93			(BIT19)
	#define PIC2_PIC2xADTEN_TRG_UDID92			(BIT18)
	#define PIC2_PIC2xADTEN_TRG_UDID91			(BIT17)
	#define PIC2_PIC2xADTEN_TRG_UDID90			(BIT16)	
	#define PIC2_PIC2xADTEN_TRG_UDID63			(BIT15)
	#define PIC2_PIC2xADTEN_TRG_UDID62			(BIT14)
	#define PIC2_PIC2xADTEN_TRG_UDID61			(BIT13)
	#define PIC2_PIC2xADTEN_TRG_UDID60			(BIT12)
	#define PIC2_PIC2xADTEN_TRG_UDID43			(BIT11)
	#define PIC2_PIC2xADTEN_TRG_UDID42			(BIT10)
	#define PIC2_PIC2xADTEN_TRG_UDID41			(BIT9)
	#define PIC2_PIC2xADTEN_TRG_UDID40			(BIT8)
	#define PIC2_PIC2xADTEN_TRG_UDID23			(BIT7)
	#define PIC2_PIC2xADTEN_TRG_UDID22			(BIT6)
	#define PIC2_PIC2xADTEN_TRG_UDID21			(BIT5)
	#define PIC2_PIC2xADTEN_TRG_UDID20			(BIT4)
	#define PIC2_PIC2xADTEN_TRG_UDID03			(BIT3)
	#define PIC2_PIC2xADTEN_TRG_UDID02			(BIT2)
	#define PIC2_PIC2xADTEN_TRG_UDID01			(BIT1)
	#define PIC2_PIC2xADTEN_TRG_UDID00			(BIT0)
#endif

/*------------------------------------------------------------------------------------------*/
/* PIC20DSADTEN0n0 : DSADC Start Trigger Output Control Register (n=0to3,8to13)				*/
/* PIC20DSADTEN1n0 : DSADC Stop Trigger Output Control Register (n=0to3,8to13)				*/
/*------------------------------------------------------------------------------------------*/
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	/* Setting Value (refer to PIC20ADTEN4nj)	*/
	/* #define PIC2_ADTEN_TRG_DISABLE			(0U)	*/
	/* #define PIC2_ADTEN_TRG_ENABLE			(1U)	*/
	/* Bit position		*/
	#define PIC2_PIC2xADTEN_TRG_N0n027			(BIT27)
	#define PIC2_PIC2xADTEN_TRG_N0n026			(BIT26)
	#define PIC2_PIC2xADTEN_TRG_N0n025			(BIT25)
	#define PIC2_PIC2xADTEN_TRG_N0n024			(BIT24)
	#define PIC2_PIC2xADTEN_TRG_N0n023			(BIT23)
	#define PIC2_PIC2xADTEN_TRG_N0n022			(BIT22)
	#define PIC2_PIC2xADTEN_TRG_N0n021			(BIT21)
	#define PIC2_PIC2xADTEN_TRG_N0n020			(BIT20)
	#define PIC2_PIC2xADTEN_TRG_N0n019			(BIT19)
	#define PIC2_PIC2xADTEN_TRG_N0n018			(BIT18)
	#define PIC2_PIC2xADTEN_TRG_N0n017			(BIT17)
	#define PIC2_PIC2xADTEN_TRG_N0n016			(BIT16)	
	#define PIC2_PIC2xADTEN_TRG_N0n015			(BIT15)
	#define PIC2_PIC2xADTEN_TRG_N0n014			(BIT14)
	#define PIC2_PIC2xADTEN_TRG_N0n013			(BIT13)
	#define PIC2_PIC2xADTEN_TRG_N0n012			(BIT12)
	#define PIC2_PIC2xADTEN_TRG_N0n011			(BIT11)
	#define PIC2_PIC2xADTEN_TRG_N0n010			(BIT10)
	#define PIC2_PIC2xADTEN_TRG_N0n009			(BIT9)
	#define PIC2_PIC2xADTEN_TRG_N0n008			(BIT8)
	#define PIC2_PIC2xADTEN_TRG_N0n007			(BIT7)
	#define PIC2_PIC2xADTEN_TRG_N0n006			(BIT6)
	#define PIC2_PIC2xADTEN_TRG_N0n005			(BIT5)
	#define PIC2_PIC2xADTEN_TRG_N0n004			(BIT4)
	#define PIC2_PIC2xADTEN_TRG_N0n003			(BIT3)
	#define PIC2_PIC2xADTEN_TRG_N0n002			(BIT2)
	#define PIC2_PIC2xADTEN_TRG_N0n001			(BIT1)
	#define PIC2_PIC2xADTEN_TRG_N0n000			(BIT0)
#endif

/*------------------------------------------------------------------------------------------*/
/* PIC20DSADTEN0n1 : DSADC Start Trigger Output Control Register (n=0to3,8to13)				*/
/* PIC20DSADTEN1n1 : DSADC Stop Trigger Output Control Register (n=0to3,8to13)				*/
/*------------------------------------------------------------------------------------------*/
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	/* Setting Value (refer to PIC20ADTEN4nj)	*/
	/* #define PIC2_ADTEN_TRG_DISABLE			(0U)	*/
	/* #define PIC2_ADTEN_TRG_ENABLE			(1U)	*/
	/* Bit position		*/
	#define PIC2_PIC2xADTEN_TRG_N0n105			(BIT5)
	#define PIC2_PIC2xADTEN_TRG_N0n104			(BIT4)
	#define PIC2_PIC2xADTEN_TRG_N0n103			(BIT3)
	#define PIC2_PIC2xADTEN_TRG_N0n102			(BIT2)
	#define PIC2_PIC2xADTEN_TRG_N0n101			(BIT1)
	#define PIC2_PIC2xADTEN_TRG_N0n100			(BIT0)
#endif

/*------------------------------------------------------------------------------------------*/
/* PIC20DSADTEN0n2 : DSADC Start Trigger Output Control Register (n=0to3,8to13)				*/
/* PIC20DSADTEN1n2 : DSADC Stop Trigger Output Control Register (n=0to3,8to13)				*/
/*------------------------------------------------------------------------------------------*/
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	/* Setting Value (refer to PIC20ADTEN4nj)	*/
	/* #define PIC2_ADTEN_TRG_DISABLE			(0U)	*/
	/* #define PIC2_ADTEN_TRG_ENABLE			(1U)	*/
	/* Bit position		*/
	#define PIC2_PIC2xADTEN_TRG_N0n219			(BIT19)
	#define PIC2_PIC2xADTEN_TRG_N0n218			(BIT18)
	#define PIC2_PIC2xADTEN_TRG_N0n217			(BIT17)
	#define PIC2_PIC2xADTEN_TRG_N0n216			(BIT16)	
	#define PIC2_PIC2xADTEN_TRG_N0n215			(BIT15)
	#define PIC2_PIC2xADTEN_TRG_N0n214			(BIT14)
	#define PIC2_PIC2xADTEN_TRG_N0n213			(BIT13)
	#define PIC2_PIC2xADTEN_TRG_N0n212			(BIT12)
	#define PIC2_PIC2xADTEN_TRG_N0n211			(BIT11)
	#define PIC2_PIC2xADTEN_TRG_N0n210			(BIT10)
	#define PIC2_PIC2xADTEN_TRG_N0n209			(BIT9)
	#define PIC2_PIC2xADTEN_TRG_N0n208			(BIT8)
	#define PIC2_PIC2xADTEN_TRG_N0n207			(BIT7)
	#define PIC2_PIC2xADTEN_TRG_N0n206			(BIT6)
	#define PIC2_PIC2xADTEN_TRG_N0n205			(BIT5)
	#define PIC2_PIC2xADTEN_TRG_N0n204			(BIT4)
	#define PIC2_PIC2xADTEN_TRG_N0n203			(BIT3)
	#define PIC2_PIC2xADTEN_TRG_N0n202			(BIT2)
	#define PIC2_PIC2xADTEN_TRG_N0n201			(BIT1)
	#define PIC2_PIC2xADTEN_TRG_N0n200			(BIT0)
#endif

/*------------------------------------------------------------------------------------------*/
/* PIC20DSADTEN0n3 : DSADC Start Trigger Output Control Register (n=0to3,8to13)				*/
/* PIC20DSADTEN1n3 : DSADC Stop Trigger Output Control Register (n=0to3,8to13)				*/
/*------------------------------------------------------------------------------------------*/
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	/* Setting Value (refer to PIC20ADTEN4nj)	*/
	/* #define PIC2_ADTEN_TRG_DISABLE			(0U)	*/
	/* #define PIC2_ADTEN_TRG_ENABLE			(1U)	*/
	/* Bit position		*/
	#define PIC2_PIC2xADTEN_TRG_N0n319			(BIT19)
	#define PIC2_PIC2xADTEN_TRG_N0n318			(BIT18)
	#define PIC2_PIC2xADTEN_TRG_N0n317			(BIT17)
	#define PIC2_PIC2xADTEN_TRG_N0n316			(BIT16)	
	#define PIC2_PIC2xADTEN_TRG_N0n315			(BIT15)
	#define PIC2_PIC2xADTEN_TRG_N0n314			(BIT14)
	#define PIC2_PIC2xADTEN_TRG_N0n313			(BIT13)
	#define PIC2_PIC2xADTEN_TRG_N0n312			(BIT12)
	#define PIC2_PIC2xADTEN_TRG_N0n311			(BIT11)
	#define PIC2_PIC2xADTEN_TRG_N0n310			(BIT10)
	#define PIC2_PIC2xADTEN_TRG_N0n309			(BIT9)
	#define PIC2_PIC2xADTEN_TRG_N0n308			(BIT8)
	#define PIC2_PIC2xADTEN_TRG_N0n307			(BIT7)
	#define PIC2_PIC2xADTEN_TRG_N0n306			(BIT6)
	#define PIC2_PIC2xADTEN_TRG_N0n305			(BIT5)
	#define PIC2_PIC2xADTEN_TRG_N0n304			(BIT4)
	#define PIC2_PIC2xADTEN_TRG_N0n303			(BIT3)
	#define PIC2_PIC2xADTEN_TRG_N0n302			(BIT2)
	#define PIC2_PIC2xADTEN_TRG_N0n301			(BIT1)
	#define PIC2_PIC2xADTEN_TRG_N0n300			(BIT0)
#endif

/*------------------------------------------------------------------------------------------*/
/* PIC21DSADTEN0n0 : DSADC Start Trigger Output Control Register (n=0to3,8to13)				*/
/* PIC21DSADTEN1n0 : DSADC Stop Trigger Output Control Register (n=0to3,8to13)				*/
/*------------------------------------------------------------------------------------------*/
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	/* Setting Value (refer to PIC20ADTEN4nj)	*/
	/* #define PIC2_ADTEN_TRG_DISABLE			(0U)	*/
	/* #define PIC2_ADTEN_TRG_ENABLE			(1U)	*/
	/* Bit position		*/
	#define PIC2_PIC2xADTEN_TRG_OCRC133			(BIT31)
	#define PIC2_PIC2xADTEN_TRG_OCRC132			(BIT30)
	#define PIC2_PIC2xADTEN_TRG_OCRC131			(BIT29)
	#define PIC2_PIC2xADTEN_TRG_OCRC130			(BIT28)
	#define PIC2_PIC2xADTEN_TRG_OCRC123			(BIT27)
	#define PIC2_PIC2xADTEN_TRG_OCRC122			(BIT26)
	#define PIC2_PIC2xADTEN_TRG_OCRC121			(BIT25)
	#define PIC2_PIC2xADTEN_TRG_OCRC120			(BIT24)
	#define PIC2_PIC2xADTEN_TRG_OCRC113			(BIT23)
	#define PIC2_PIC2xADTEN_TRG_OCRC112			(BIT22)
	#define PIC2_PIC2xADTEN_TRG_OCRC111			(BIT21)
	#define PIC2_PIC2xADTEN_TRG_OCRC110			(BIT20)
	#define PIC2_PIC2xADTEN_TRG_OCRC103			(BIT19)
	#define PIC2_PIC2xADTEN_TRG_OCRC102			(BIT18)
	#define PIC2_PIC2xADTEN_TRG_OCRC101			(BIT17)
	#define PIC2_PIC2xADTEN_TRG_OCRC100			(BIT16)	
	#define PIC2_PIC2xADTEN_TRG_OCRG7			(BIT15)
	#define PIC2_PIC2xADTEN_TRG_OCRG6			(BIT14)
	#define PIC2_PIC2xADTEN_TRG_OCRG5			(BIT13)
	#define PIC2_PIC2xADTEN_TRG_OCRG4			(BIT12)
	#define PIC2_PIC2xADTEN_TRG_OCRG3			(BIT11)
	#define PIC2_PIC2xADTEN_TRG_OCRG2			(BIT10)
	#define PIC2_PIC2xADTEN_TRG_OCRG1			(BIT9)
	#define PIC2_PIC2xADTEN_TRG_OCRG0			(BIT8)
	#define PIC2_PIC2xADTEN_TRG_OCRC93			(BIT7)
	#define PIC2_PIC2xADTEN_TRG_OCRC92			(BIT6)
	#define PIC2_PIC2xADTEN_TRG_OCRC91			(BIT5)
	#define PIC2_PIC2xADTEN_TRG_OCRC90			(BIT4)
	#define PIC2_PIC2xADTEN_TRG_OCRC83			(BIT3)
	#define PIC2_PIC2xADTEN_TRG_OCRC82			(BIT2)
	#define PIC2_PIC2xADTEN_TRG_OCRC81			(BIT1)
	#define PIC2_PIC2xADTEN_TRG_OCRC80			(BIT0)
#endif


/*----------------------------------------------------------------------------------*/
/* PIC2ADTCFGk : A/D Converter Trigger Output Configuration Register (k=0-9)		*/
/*----------------------------------------------------------------------------------*/
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
/* Setting Value	*/
/* Bit position		*/
	#define PIC2_PIC24_ADTCFG_UPPER				(0x01FF0000U)
	#define PIC2_PIC24_ADTCFG_UPPER_0			(BIT16)
	#define PIC2_PIC24_ADTCFG_LOWER				(0x000001FFU)
	#define PIC2_PIC24_ADTCFG_LOWER_0			(BIT0)
#endif

/*--------------------------------------------------------------------------------------*/
/* register type definition																*/
/*--------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------*/
/* PIC20/21																			*/
/*----------------------------------------------------------------------------------*/

/* U2A:PIC2ADCJnTSELj,PIC2ADCJnEDGSEL	U2B:PIC20ADCKnTSELj,PIC20ADCKnEDGSEL		*/
typedef struct {
	uint32	u4TSEL[PIC2_TSEL_SG_MAXSIZE];
	uint32	u4Dummy;
	uint16	u2EDGSEL;
	uint16	u2Dummy;
} Pic2_PIC2xADCXnTSELjType;

/* U2A:PIC2ADTEN4kj						U2B:PIC20ADTEN4nj							*/
typedef struct {
	struct {
		uint16	u2Data;
		uint16	u2Dummy;
	} stTrgCH[PIC2_TSEL_SG_MAXSIZE];
	uint32	u4Dummy[2];
} Pic2_PIC2xADTEN4njType;

/* U2A:PIC2ADTEN5nj						U2B:PIC20ADTEN5nj							*/
typedef struct {
	uint32	u4Data[PIC2_ADC_SG_MAXSIZE];
	uint32	u4Dummy[2];
} Pic2_PIC2xADTENynjType;

/* PIC20/PIC21 common 	*/
typedef struct {
	Pic2_PIC2xADCXnTSELjType	stADCXnTSELj[PIC2_TSEL_MAXSIZE];			/* 0xFFBFC000 - 0xFFBFC07F	*/
	Pic2_PIC2xADTEN4njType		stADTEN4nj[PIC2_ADCTEN4nj_MAXSIZE];			/* 0xFFBFC080 - 0xFFBFC0DF	*/
	uint32						u4Dummy[40];
	Pic2_PIC2xADTENynjType		stADTEN5nj[PIC2_ADCTENynj_MAXSIZE];			/* 0xFFBFC180 - 0xFFBFC1FF	*/
	Pic2_PIC2xADTENynjType		stADTEN6nj[PIC2_ADCTENynj_MAXSIZE];			/* 0xFFBFC200 - 0xFFBFC27F	*/
	Pic2_PIC2xADTENynjType		stADTEN7nj[PIC2_ADCTENynj_MAXSIZE];			/* 0xFFBFC280 - 0xFFBFC2FF	*/
	Pic2_PIC2xADTENynjType		stADTEN8nj[PIC2_ADCTENynj_MAXSIZE];			/* 0xFFBFC300 - 0xFFBFC37F	*/
	/* 0x380	*/
} Reg_Pic2x_Type;

/* 	*/
/*----------------------------------------------------------------------------------*/
/* PIC24																			*/
/*----------------------------------------------------------------------------------*/
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
/* U2A:-								U2B:PIC2ADTCFGk							*/
typedef struct {
	uint32	u4Data;
} Pic2_PIC2ADTCFGType;

/* PIC24	*/
typedef struct {
	Pic2_PIC2ADTCFGType			stADTCFG[PIC2_PIC24_ADCTCFG_SIZE];			/* 0xFFBFE000 - 0xFFBFE027	*/
} Reg_Pic24_Type;
#endif


/*==============================================================================================*/
/* base address definition																		*/
/*==============================================================================================*/

#if	(MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A) 
	/* PIC2	*/
	#define		Reg_PIC20		(*(volatile Reg_Pic2x_Type*)		(0xFFBFC000U))
#elif (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	/* PIC2	*/
	#define		Reg_PIC20		(*(volatile Reg_Pic2x_Type*)		(0xFFBFC000U))
	#define		Reg_PIC21		(*(volatile Reg_Pic2x_Type*)		(0xFFBFC800U))
#endif

/*==============================================================================================*/
/* external symbols																				*/
/*==============================================================================================*/
extern volatile Reg_Pic2x_Type* const	cpstReg_Pic20[PIC2_REG_ARRAY_SIZE];
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
extern volatile Reg_Pic2x_Type* const	cpstReg_Pic21[PIC2_REG_ARRAY_SIZE];
#endif

#endif
/*-- End Of File -------------------------------------------------------------------------------*/

