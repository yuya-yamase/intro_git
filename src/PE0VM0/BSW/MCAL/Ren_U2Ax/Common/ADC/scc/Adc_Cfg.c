/* ADC-r04-303 */
/************************************************************************************************/
/*																								*/
/*		ADC Driver : User Configuration															*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
#include "Std_Types.h"
#include "Mcal_SpalCmn.h"

#include "Adc.h"
#include "Pic2.h"
#include "Reg_Pic2.h"
#include "Adc_Cfg.h"
#ifdef ADC_USE_DMA
#include "Dma_Cfg.h"
#endif	/* #ifdef ADC_USE_DMA	*/

/*==============================================================================================*/
/*	defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/

#if	(ADC_CFG_GLOBAL_REG_CONTROL == STD_ON)
/*----------------------------------------------------------------------------------*/
/* HW Setting																		*/
/*----------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------*/
/* 	A/D Converter Trigger Selection Control Register:PIC20ADCXnTSELj				*/
/*----------------------------------------------------------------------------------*/
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A)
	#define		PIC2_SetPic20TSEL(gNbr)																				\
		((uint32)(																									\
			(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj28)				/* TSELj28	: 28		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj27)			/* TSELj27	: 27		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj26)			/* TSELj26	: 26		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj25)			/* TSELj25	: 25		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj24)			/* TSELj24	: 24		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj23)			/* TSELj23	: 23		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj22)			/* TSELj22	: 22		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj21)			/* TSELj21	: 21		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj20)			/* TSELj20	: 20		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj19)			/* TSELj19	: 19		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj18)			/* TSELj18	: 18		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj17)			/* TSELj17	: 17		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj16)			/* TSELj16	: 16		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj15)			/* TSELj15	: 15		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj14)			/* TSELj14	: 14		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj13)			/* TSELj13	: 13		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj12)			/* TSELj12	: 12		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj11)			/* TSELj11	: 11		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj10)			/* TSELj10	: 10		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj09)			/* TSELj09	: 09		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj08)			/* TSELj08	: 08		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj07)			/* TSELj07	: 07		*/	\
			+(uint32)((ADC_CFG_GRP##gNbr##_TSG30TG1==STD_OFF) ?							/* TSELj06	: 06		*/	\
				(PIC2_ADCXnTSEL_NOTSELECTED			* PIC2_PIC2xADCXnTSELj06) :										\
				(PIC2_ADCXnTSEL_SELECTED			* PIC2_PIC2xADCXnTSELj06) )										\
			+(uint32)((ADC_CFG_GRP##gNbr##_TSG30TG0==STD_OFF) ?							/* TSELj05	: 05		*/	\
				(PIC2_ADCXnTSEL_NOTSELECTED			* PIC2_PIC2xADCXnTSELj05) :										\
				(PIC2_ADCXnTSEL_SELECTED			* PIC2_PIC2xADCXnTSELj05) )										\
			+(uint32)((ADC_CFG_GRP##gNbr##_TAUJ1_CH3==STD_OFF) ?						/* TSELj04	: 04		*/	\
				(PIC2_ADCXnTSEL_NOTSELECTED			* PIC2_PIC2xADCXnTSELj04) :										\
				(PIC2_ADCXnTSEL_SELECTED			* PIC2_PIC2xADCXnTSELj04) )										\
			+(uint32)((ADC_CFG_GRP##gNbr##_TAUJ0_CH3==STD_OFF) ?						/* TSELj03	: 03		*/	\
				(PIC2_ADCXnTSEL_NOTSELECTED			* PIC2_PIC2xADCXnTSELj03) :										\
				(PIC2_ADCXnTSEL_SELECTED			* PIC2_PIC2xADCXnTSELj03) )										\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj02)			/* TSELj02	: 02		*/	\
			+(uint32)((ADC_CFG_GRP##gNbr##_TAUD1==STD_OFF) ?							/* TSELj01	: 01		*/	\
				(PIC2_ADCXnTSEL_NOTSELECTED			* PIC2_PIC2xADCXnTSELj01) :										\
				(PIC2_ADCXnTSEL_SELECTED			* PIC2_PIC2xADCXnTSELj01) )										\
			+(uint32)((ADC_CFG_GRP##gNbr##_TAUD0==STD_OFF) ?							/* TSELj00	: 00		*/	\
				(PIC2_ADCXnTSEL_NOTSELECTED			* PIC2_PIC2xADCXnTSELj00) :										\
				(PIC2_ADCXnTSEL_SELECTED			* PIC2_PIC2xADCXnTSELj00) )										\
		))
#elif(MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	#define		PIC2_SetPic20TSEL(gNbr)																				\
		((uint32)(																									\
			(uint32)(PIC2_ADCXnTSEL_NOTSELECTED		* PIC2_PIC2xADCXnTSELj28)			/* TSELj28	: 28		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj27)			/* TSELj27	: 27		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj26)			/* TSELj26	: 26		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj25)			/* TSELj25	: 25		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj24)			/* TSELj24	: 24		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj23)			/* TSELj23	: 23		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj22)			/* TSELj22	: 22		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj19)			/* TSELj19	: 19		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj18)			/* TSELj18	: 18		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj17)			/* TSELj17	: 17		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj16)			/* TSELj16	: 16		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj15)			/* TSELj15	: 15		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj14)			/* TSELj14	: 14		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj13)			/* TSELj13	: 13		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj12)			/* TSELj12	: 12		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj11)			/* TSELj11	: 11		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj10)			/* TSELj10	: 10		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj09)			/* TSELj09	: 09		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj08)			/* TSELj08	: 08		*/	\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj07)			/* TSELj07	: 07		*/	\
			+(uint32)((ADC_CFG_GRP##gNbr##_TSG30TG1==STD_OFF) ?							/* TSELj06	: 06		*/	\
				(PIC2_ADCXnTSEL_NOTSELECTED			* PIC2_PIC2xADCXnTSELj06) :										\
				(PIC2_ADCXnTSEL_SELECTED			* PIC2_PIC2xADCXnTSELj06) )										\
			+(uint32)((ADC_CFG_GRP##gNbr##_TSG30TG0==STD_OFF) ?							/* TSELj05	: 05		*/	\
				(PIC2_ADCXnTSEL_NOTSELECTED			* PIC2_PIC2xADCXnTSELj05) :										\
				(PIC2_ADCXnTSEL_SELECTED			* PIC2_PIC2xADCXnTSELj05) )										\
			+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj02)			/* TSELj02	: 02		*/	\
			+(uint32)((ADC_CFG_GRP##gNbr##_TAUD1==STD_OFF) ?							/* TSELj01	: 01		*/	\
				(PIC2_ADCXnTSEL_NOTSELECTED			* PIC2_PIC2xADCXnTSELj01) :										\
				(PIC2_ADCXnTSEL_SELECTED			* PIC2_PIC2xADCXnTSELj01) )										\
			+(uint32)((ADC_CFG_GRP##gNbr##_TAUD0==STD_OFF) ?							/* TSELj00	: 00		*/	\
				(PIC2_ADCXnTSEL_NOTSELECTED			* PIC2_PIC2xADCXnTSELj00) :										\
				(PIC2_ADCXnTSEL_SELECTED			* PIC2_PIC2xADCXnTSELj00) )										\
		))
#endif
#define		PIC2_SetPic21TSEL(gNbr)																				\
	 ((uint32)(																									\
		 (uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj31)			/* TSELj31	: 31		*/	\
		+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj30)			/* TSELj30	: 30		*/	\
		+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj29)			/* TSELj29	: 29		*/	\
		+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj28)			/* TSELj28	: 28		*/	\
		+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj27)			/* TSELj27	: 27		*/	\
		+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj26)			/* TSELj26	: 26		*/	\
		+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj25)			/* TSELj25	: 25		*/	\
		+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj24)			/* TSELj24	: 24		*/	\
		+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj23)			/* TSELj23	: 23		*/	\
		+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj22)			/* TSELj22	: 22		*/	\
		+(uint32)((ADC_CFG_GRP##gNbr##_E3S0AD1==STD_OFF) ?							/* TSELj21	: 21		*/	\
			(PIC2_ADCXnTSEL_NOTSELECTED			* PIC2_PIC2xADCXnTSELj21) :										\
			(PIC2_ADCXnTSEL_SELECTED			* PIC2_PIC2xADCXnTSELj21) )										\
		+(uint32)((ADC_CFG_GRP##gNbr##_E3S0AD==STD_OFF) ?							/* TSELj20	: 20		*/	\
			(PIC2_ADCXnTSEL_NOTSELECTED			* PIC2_PIC2xADCXnTSELj20) :										\
			(PIC2_ADCXnTSEL_SELECTED			* PIC2_PIC2xADCXnTSELj20) )										\
		+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj19)			/* TSELj19	: 19		*/	\
		+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj18)			/* TSELj18	: 18		*/	\
		+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj17)			/* TSELj17	: 17		*/	\
		+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj16)			/* TSELj16	: 16		*/	\
		+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj15)			/* TSELj15	: 15		*/	\
		+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj14)			/* TSELj14	: 14		*/	\
		+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj12)			/* TSELj12	: 12		*/	\
		+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj11)			/* TSELj11	: 11		*/	\
		+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj10)			/* TSELj10	: 10		*/	\
		+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj09)			/* TSELj09	: 09		*/	\
		+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj08)			/* TSELj08	: 08		*/	\
		+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj07)			/* TSELj07	: 07		*/	\
		+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj06)			/* TSELj06	: 06		*/	\
		+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj05)			/* TSELj05	: 05		*/	\
		+(uint32)(PIC2_ADCXnTSEL_NOTSELECTED	* PIC2_PIC2xADCXnTSELj02)			/* TSELj02	: 02		*/	\
		+(uint32)((ADC_CFG_GRP##gNbr##_TAUD3==STD_OFF) ?							/* TSELj01	: 01		*/	\
			(PIC2_ADCXnTSEL_NOTSELECTED			* PIC2_PIC2xADCXnTSELj01) :										\
			(PIC2_ADCXnTSEL_SELECTED			* PIC2_PIC2xADCXnTSELj01) )										\
		+(uint32)((ADC_CFG_GRP##gNbr##_TAUD2==STD_OFF) ?							/* TSELj00	: 00		*/	\
			(PIC2_ADCXnTSEL_NOTSELECTED			* PIC2_PIC2xADCXnTSELj00) :										\
			(PIC2_ADCXnTSEL_SELECTED			* PIC2_PIC2xADCXnTSELj00) )										\
	))

/*--------------------------------------------------------------------------------------*/
/* Pic2 Configuration 																	*/
/*--------------------------------------------------------------------------------------*/
#define ADC_START_SEC_CONST_32				/* ADC RODATA CONST 32bit Section Start				*/
#include "Adc_MemMap.h"

/* ADC Trigger Selection						*/
static CONST(uint32, ADC_CONST) s_cu4Pic20TSEL[ADC_CFG_GRP_SIZE] = {
	#if (ADC_CFG_GRP_SIZE >=  1U)
		PIC2_SetPic20TSEL(00)
	#endif
	#if (ADC_CFG_GRP_SIZE >=  2U)
		,PIC2_SetPic20TSEL(01)
	#endif
	#if (ADC_CFG_GRP_SIZE >=  3U)
		,PIC2_SetPic20TSEL(02)
	#endif
	#if (ADC_CFG_GRP_SIZE >=  4U)
		,PIC2_SetPic20TSEL(03)
	#endif
	#if (ADC_CFG_GRP_SIZE >=  5U)
		,PIC2_SetPic20TSEL(04)
	#endif
	#if (ADC_CFG_GRP_SIZE >=  6U)
		,PIC2_SetPic20TSEL(05)
	#endif
	#if (ADC_CFG_GRP_SIZE >=  7U)
		,PIC2_SetPic20TSEL(06)
	#endif
	#if (ADC_CFG_GRP_SIZE >=  8U)
		,PIC2_SetPic20TSEL(07)
	#endif
	#if (ADC_CFG_GRP_SIZE >=  9U)
		,PIC2_SetPic20TSEL(08)
	#endif
	#if (ADC_CFG_GRP_SIZE >= 10U)
		,PIC2_SetPic20TSEL(09)
	#endif
	#if (ADC_CFG_GRP_SIZE >= 11U)
		,PIC2_SetPic20TSEL(10)
	#endif
	#if (ADC_CFG_GRP_SIZE >= 12U)
		,PIC2_SetPic20TSEL(11)
	#endif
	#if (ADC_CFG_GRP_SIZE >= 13U)
		,PIC2_SetPic20TSEL(12)
	#endif
	#if (ADC_CFG_GRP_SIZE >= 14U)
		,PIC2_SetPic20TSEL(13)
	#endif
	#if (ADC_CFG_GRP_SIZE >= 15U)
		,PIC2_SetPic20TSEL(14)
	#endif
};

/* ADC Trigger Edge Direction					*/
static CONST(Pic2_EDGSELType, ADC_CONST) s_cudPic20EDGSEL[ADC_CFG_GRP_SIZE] = {
	#if (ADC_CFG_GRP_SIZE >=  1U)	 
		ADC_CFG_GRP00_EDG_DIRECTION
	#endif
	#if (ADC_CFG_GRP_SIZE >=  2U)
		,ADC_CFG_GRP01_EDG_DIRECTION
	#endif
	#if (ADC_CFG_GRP_SIZE >=  3U)
		,ADC_CFG_GRP02_EDG_DIRECTION
	#endif
	#if (ADC_CFG_GRP_SIZE >=  4U)
		,ADC_CFG_GRP03_EDG_DIRECTION
	#endif
	#if (ADC_CFG_GRP_SIZE >=  5U)
		,ADC_CFG_GRP04_EDG_DIRECTION
	#endif
	#if (ADC_CFG_GRP_SIZE >=  6U)
		,ADC_CFG_GRP05_EDG_DIRECTION
	#endif
	#if (ADC_CFG_GRP_SIZE >=  7U)
		,ADC_CFG_GRP06_EDG_DIRECTION
	#endif
	#if (ADC_CFG_GRP_SIZE >=  8U)
		,ADC_CFG_GRP07_EDG_DIRECTION
	#endif
	#if (ADC_CFG_GRP_SIZE >=  9U)
		,ADC_CFG_GRP08_EDG_DIRECTION
	#endif
	#if (ADC_CFG_GRP_SIZE >= 10U)
		,ADC_CFG_GRP09_EDG_DIRECTION
	#endif
	#if (ADC_CFG_GRP_SIZE >= 11U)
		,ADC_CFG_GRP10_EDG_DIRECTION
	#endif
	#if (ADC_CFG_GRP_SIZE >= 12U)
		,ADC_CFG_GRP11_EDG_DIRECTION
	#endif
	#if (ADC_CFG_GRP_SIZE >= 13U)
		,ADC_CFG_GRP12_EDG_DIRECTION
	#endif
	#if (ADC_CFG_GRP_SIZE >= 14U)
		,ADC_CFG_GRP13_EDG_DIRECTION
	#endif
	#if (ADC_CFG_GRP_SIZE >= 15U)
		,ADC_CFG_GRP14_EDG_DIRECTION
	#endif
};
#define ADC_STOP_SEC_CONST_32				/* ADC RODATA CONST 32bit Section End				*/
#include "Adc_MemMap.h"

#define ADC_START_SEC_CONST_16				/* ADC RODATA CONST 16bit Section Start				*/
#include "Adc_MemMap.h"

/* Trigger Output TAUD0 (PIC20)					*/
static CONST(uint16, ADC_CONST) s_cu2Pic20ADTEN40[PIC2_TSEL_SG_MAXSIZE] = {
	ADC_CFG_HWTRG_TAUD0_SG0, ADC_CFG_HWTRG_TAUD0_SG1, ADC_CFG_HWTRG_TAUD0_SG2, ADC_CFG_HWTRG_TAUD0_SG3, ADC_CFG_HWTRG_TAUD0_SG4, ADC_ZERO
};

static CONST(uint16, ADC_CONST) s_cu2Pic20ADTEN41[PIC2_TSEL_SG_MAXSIZE] = {
	ADC_CFG_HWTRG_TAUD1_SG0, ADC_CFG_HWTRG_TAUD1_SG1, ADC_CFG_HWTRG_TAUD1_SG2, ADC_CFG_HWTRG_TAUD1_SG3, ADC_CFG_HWTRG_TAUD1_SG4, ADC_ZERO
};

#define ADC_STOP_SEC_CONST_16				/* ADC RODATA CONST 16bit Section End				*/
#include "Adc_MemMap.h"

#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
#define ADC_START_SEC_CONST_32				/* ADC RODATA CONST 32bit Section Start				*/
#include "Adc_MemMap.h"

static CONST(uint32, ADC_CONST) s_cu4Pic21TSEL[ADC_CFG_GRP_SIZE] = {
	#if (ADC_CFG_GRP_SIZE >=  1U)
		PIC2_SetPic21TSEL(00)
	#endif
	#if (ADC_CFG_GRP_SIZE >=  2U)
		,PIC2_SetPic21TSEL(01)
	#endif
	#if (ADC_CFG_GRP_SIZE >=  3U)
		,PIC2_SetPic21TSEL(02)
	#endif
	#if (ADC_CFG_GRP_SIZE >=  4U)
		,PIC2_SetPic21TSEL(03)
	#endif
	#if (ADC_CFG_GRP_SIZE >=  5U)
		,PIC2_SetPic21TSEL(04)
	#endif
	#if (ADC_CFG_GRP_SIZE >=  6U)
		,PIC2_SetPic21TSEL(05)
	#endif
	#if (ADC_CFG_GRP_SIZE >=  7U)
		,PIC2_SetPic21TSEL(06)
	#endif
	#if (ADC_CFG_GRP_SIZE >=  8U)
		,PIC2_SetPic21TSEL(07)
	#endif
	#if (ADC_CFG_GRP_SIZE >=  9U)
		,PIC2_SetPic21TSEL(08)
	#endif
	#if (ADC_CFG_GRP_SIZE >= 10U)
		,PIC2_SetPic21TSEL(09)
	#endif
	#if (ADC_CFG_GRP_SIZE >= 11U)
		,PIC2_SetPic21TSEL(10)
	#endif
	#if (ADC_CFG_GRP_SIZE >= 12U)
		,PIC2_SetPic21TSEL(11)
	#endif
	#if (ADC_CFG_GRP_SIZE >= 13U)
		,PIC2_SetPic21TSEL(12)
	#endif
	#if (ADC_CFG_GRP_SIZE >= 14U)
		,PIC2_SetPic21TSEL(13)
	#endif
	#if (ADC_CFG_GRP_SIZE >= 15U)
		,PIC2_SetPic21TSEL(14)
	#endif
};

#define ADC_STOP_SEC_CONST_32				/* ADC RODATA CONST 32bit Section End				*/
#include "Adc_MemMap.h"

#define ADC_START_SEC_CONST_16				/* ADC RODATA CONST 16bit Section Start				*/
#include "Adc_MemMap.h"

static CONST(uint16, ADC_CONST) s_cu2Pic21ADTEN40[PIC2_TSEL_SG_MAXSIZE] = {
	ADC_CFG_HWTRG_TAUD2_SG0, ADC_CFG_HWTRG_TAUD2_SG1, ADC_CFG_HWTRG_TAUD2_SG2, ADC_CFG_HWTRG_TAUD2_SG3, ADC_CFG_HWTRG_TAUD2_SG4, ADC_ZERO
};

static CONST(uint16, ADC_CONST) s_cu2Pic21ADTEN41[PIC2_TSEL_SG_MAXSIZE] = {
	ADC_CFG_HWTRG_TAUD3_SG0, ADC_CFG_HWTRG_TAUD3_SG1, ADC_CFG_HWTRG_TAUD3_SG2, ADC_CFG_HWTRG_TAUD3_SG3, ADC_CFG_HWTRG_TAUD3_SG4, ADC_ZERO
};
#define ADC_STOP_SEC_CONST_16				/* ADC RODATA CONST 16bit Section End				*/
#include "Adc_MemMap.h"

#endif	/* #if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)	*/

#define ADC_START_SEC_CONST_PTR				/* ADC RODATA CONST Pointer Section Start			*/
#include "Adc_MemMap.h"

/* Pic2 Configuration */
static CONST(Pic2_ConfigType, ADC_CONST) s_cstPic2_Config = {
	&s_cu4Pic20TSEL[0],						/* ADC Trigger Selection (PIC20)				*/
	&s_cudPic20EDGSEL[0],					/* ADC Trigger Edge Direction					*/
	&s_cu2Pic20ADTEN40[0],					/* Trigger Output TAUD0 (PIC20)					*/
	&s_cu2Pic20ADTEN41[0],					/* Trigger Output TAUD1 (PIC20)					*/
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	&s_cu4Pic21TSEL[0],						/* ADC Trigger Selection (PIC21)				*/
	&s_cu2Pic21ADTEN40[0],					/* Trigger Output TAUD2 (PIC21)					*/
	&s_cu2Pic21ADTEN41[0],					/* Trigger Output TAUD3 (PIC21)					*/
#endif
};

#define ADC_STOP_SEC_CONST_PTR				/* ADC RODATA CONST Pointer Section End				*/
#include "Adc_MemMap.h"
#endif

/*--------------------------------------------------------------------------------------*/
/* Adc Configuration 																	*/
/*--------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------*/
/* HW Setting																		*/
/*----------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------*/
/* Virtual Channel Register : ADCXnVCRj  j=0-63										*/
/*		Not Supported.																*/
/*----------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------*/
/* 	Sampling Control Register  						: ADCXnSMPCR					*/
/*----------------------------------------------------------------------------------*/
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A)
#define		ADC_SetSMPCR(hNbr)																							\
	 ((uint32)(																											\
		 (uint32)(ADC_SMPCR_EXSMPT_60STATES 	* ADC_SMPCR_EXSMPT_0)						/* ADTSTARTE: 23 - 1	*/	\
		+(uint32)((ADC_CFG_HWUNIT##hNbr##_BUFFER_AMP==STD_ON) ?								/* BUFAMPD	: 15		*/	\
			(ADC_SMPCR_BUFAMPD_ENABLE   		* ADC_SMPCR_BUFAMPD) :													\
			(ADC_SMPCR_BUFAMPD_DISABLE 			* ADC_SMPCR_BUFAMPD) )													\
		+(uint32)((ADC_CFG_HWUNIT##hNbr##_BUFFER_AMP==STD_ON) ?								/* SMPTS	: 12		*/	\
			(ADC_SMPCR_SMPTS_DISABLE 			* ADC_SMPCR_SMPTS) :													\
			(ADC_SMPCR_SMPTS_ENABLE  			* ADC_SMPCR_SMPTS) )													\
		+(uint32)((ADC_CFG_HWUNIT##hNbr##_BUFFER_AMP==STD_ON) ?								/* SMPT		:  7 -  0	*/	\
			(ADC_SMPCR_SMPT_18STATES 			* ADC_SMPCR_SMPT_0) :													\
			((ADC_CFG_HWUNIT##hNbr##_SAMPLING_PERIOD==ADC_SAMPLING_PERIOD_99STATES) ?									\
				(ADC_SMPCR_SMPT_99STATES 		* ADC_SMPCR_SMPT_0) :													\
				((ADC_CFG_HWUNIT##hNbr##_SAMPLING_PERIOD==ADC_SAMPLING_PERIOD_204STATES) ?								\
					(ADC_SMPCR_SMPT_204STATES	* ADC_SMPCR_SMPT_0) :													\
					(ADC_SMPCR_SMPT_252STATES	* ADC_SMPCR_SMPT_0)														\
				)																										\
			)																											\
		)																												\
	))
#elif (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B) 
#define		ADC_SetSMPCR(hNbr)																							\
	 ((uint32)(																											\
		 (uint32)(ADC_SMPCR_EXSMPT_60STATES		* ADC_SMPCR_EXSMPT_0)						/* ADTSTARTE: 23 - 1	*/	\
		+(uint32)((ADC_CFG_HWUNIT##hNbr##_BUFFER_AMP==STD_ON) ?								/* BUFAMPD	: 15		*/	\
			(ADC_SMPCR_BUFAMPD_ENABLE			* ADC_SMPCR_BUFAMPD) :													\
			(ADC_SMPCR_BUFAMPD_DISABLE			* ADC_SMPCR_BUFAMPD) )													\
		+(uint32)((ADC_CFG_HWUNIT##hNbr##_BUFFER_AMP==STD_ON) ?								/* SMPTS	: 12		*/	\
			(ADC_SMPCR_SMPTS_DISABLE			* ADC_SMPCR_SMPTS) :													\
			(ADC_SMPCR_SMPTS_ENABLE				* ADC_SMPCR_SMPTS) )													\
		+(uint32)((ADC_CFG_HWUNIT##hNbr##_BUFFER_AMP==STD_ON) ?								/* SMPT		:  7 -  0	*/	\
			(ADC_SMPCR_SMPT_18STATES			* ADC_SMPCR_SMPT_0) :													\
			((ADC_CFG_HWUNIT##hNbr##_SAMPLING_PERIOD==ADC_SAMPLING_PERIOD_102STATES) ?									\
				(ADC_SMPCR_SMPT_102STATES		* ADC_SMPCR_SMPT_0) :													\
				((ADC_CFG_HWUNIT##hNbr##_SAMPLING_PERIOD==ADC_SAMPLING_PERIOD_204STATES) ?								\
					(ADC_SMPCR_SMPT_204STATES	* ADC_SMPCR_SMPT_0) :													\
					(ADC_SMPCR_SMPT_252STATES	* ADC_SMPCR_SMPT_0)														\
				)																										\
			)																											\
		)																												\
	))
#endif
/*--------------------------------------------------------------------------------------*/
/*  Scan Group x Virtual Channel Pointer Register	: ADCXnSGVCPRx	x:Scan Group0-4		*/
/*--------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------*/
/*  Scan Group x Control Register 					: ADCXnSGCRx	x:Scan Group0-4	*/
/*----------------------------------------------------------------------------------*/
#define		ADC_SetSGCR(gNbr)																							\
	 ((uint8)(																											\
		 (uint8)(ADC_SGCR_ADTSTARTE_DISABLE	* ADC_SGCR_ADTSTARTE)							/* ADTSTARTE: 7			*/	\
		+(uint8)(ADC_SGCR_ADSTARTE_DISABLE	* ADC_SGCR_ADSTARTE)							/* ADSTARTE	: 6			*/	\
		+(uint8)((ADC_CFG_GRP##gNbr##_CNV_MODE==ADC_CONV_MODE_CONTINUOUS) ?					/* SCANMD	: 5			*/	\
			(ADC_SGCR_SCANMD_CONTINUOUS		* ADC_SGCR_SCANMD) :														\
			(ADC_SGCR_SCANMD_MULTI_CYCLE	* ADC_SGCR_SCANMD) )														\
		+((uint8)ADC_SGCR_ADIE_DISABLE		* ADC_SGCR_ADIE)								/* ADIE		: 4			*/	\
		+(uint8)(ADC_SGCR_TRGMD_SOFT		* ADC_SGCR_TRGMD_SG0_2)							/* TRGMD	: 0			*/	\
	))

/*----------------------------------------------------------------------------------*/
/*  A/D Control Register 1 							: ADCXnADCR1					*/
/*----------------------------------------------------------------------------------*/
#define		ADC_SetADCR1(hNbr)																							\
	 ((uint8)(																											\
		(uint8)((ADC_CFG_HWUNIT##hNbr##_SUSPEND_METHOD == ADC_SUSPEND_METHOD_ASYNC) ?		/* SUSMTD	:  1 - 0	*/	\
			(ADC_ADCR1_SUSMTD_ASYNC * ADC_ADCR1_SUSMTD_0) :																\
			(ADC_ADCR1_SUSMTD_SYNC  * ADC_ADCR1_SUSMTD_0) )																\
	))

/*----------------------------------------------------------------------------------*/
/*  A/D Control Register 2 							: ADCXnADCR2					*/
/*----------------------------------------------------------------------------------*/
#define		ADC_SetADCR2(hNbr)																							\
	 ((uint8)(																											\
		(uint8)((ADC_CFG_HWUNIT##hNbr##_RESULT_FORMAT==ADC_FORMAT_SIGNED_FIXED_POINT) ?	/* DFMT		:  6 - 4	*/		\
			(ADC_ADCR2_DFMT_12BIT_FIXED_POINT				* ADC_ADCR2_DFMT_0) :										\
			((ADC_CFG_HWUNIT##hNbr##_RESULT_FORMAT==ADC_FORMAT_SIGNED_INTEGER) ?										\
				(ADC_ADCR2_DFMT_12BIT_INT					* ADC_ADCR2_DFMT_0) :										\
				((ADC_CFG_HWUNIT##hNbr##_RESULT_FORMAT==ADC_FORMAT_UNSIGNED_FIXED_POINT) ?								\
					(((ADC_CFG_HWUNIT##hNbr##_RESOLUTION==ADC_RESOLUTION_10BIT) ?										\
						(ADC_ADCR2_DFMT_10BIT_UNFIXED_POINT	* ADC_ADCR2_DFMT_0) :										\
						(ADC_ADCR2_DFMT_12BIT_UNFIXED_POINT	* ADC_ADCR2_DFMT_0) ) ) :									\
					(((ADC_CFG_HWUNIT##hNbr##_RESULT_ALIGN==ADC_ALIGN_RIGHT) ?											\
						(ADC_ADCR2_DFMT_12BIT_UNINT_R		* ADC_ADCR2_DFMT_0) :										\
						(ADC_ADCR2_DFMT_12BIT_UNINT_L		* ADC_ADCR2_DFMT_0) )  )									\
				)																										\
			)																											\
		)																												\
		+(uint8)(ADC_ADCR2_ADDNT_2TIMES * ADC_ADCR2_ADDNT)									/* ADDNT	:  0		*/	\
	))

/*----------------------------------------------------------------------------------*/
/*  T&H Control Register 							: ADCXnTHCR						*/
/*----------------------------------------------------------------------------------*/
#define		ADC_SetTHCR()																								\
	 ((uint8)(																											\
		 (uint8)(ADC_THCR_ASMPMSK_AUTO * ADC_THCR_ASMPMSK)									/* ASMPMSK	:  0		*/	\
	))

/*----------------------------------------------------------------------------------*/
/*  T&H Enable Register 							: ADCXnTHER						*/
/*----------------------------------------------------------------------------------*/
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A)
	#define		ADC_SetTHER(hNbr)																						\
	 ((uint8)(																											\
	    (uint8)((ADC_CFG_HWUNIT##hNbr##_TH3 == STD_ON) ?									/* TH3E		:  3		*/	\
			(ADC_THER_THZE_ENABLE	* ADC_THER_TH3E) :																	\
			(ADC_THER_THZE_DISABLE	* ADC_THER_TH3E) )																	\
	   +(uint8)((ADC_CFG_HWUNIT##hNbr##_TH2 == STD_ON) ?									/* TH2E		:  2		*/	\
			(ADC_THER_THZE_ENABLE	* ADC_THER_TH2E) :																	\
			(ADC_THER_THZE_DISABLE	* ADC_THER_TH2E) )																	\
	   +(uint8)((ADC_CFG_HWUNIT##hNbr##_TH1 == STD_ON) ?									/* TH1E		:  1		*/	\
			(ADC_THER_THZE_ENABLE	* ADC_THER_TH1E) :																	\
			(ADC_THER_THZE_DISABLE	* ADC_THER_TH1E) )																	\
	   +(uint8)((ADC_CFG_HWUNIT##hNbr##_TH0 == STD_ON) ?									/* TH0E		:  0		*/	\
			(ADC_THER_THZE_ENABLE	* ADC_THER_TH0E) :																	\
			(ADC_THER_THZE_DISABLE	* ADC_THER_TH0E) )																	\
	))
#else	/* MCAL_TARGET_RH850U2B	*/
	#define		ADC_SetTHER(hNbr)																						\
	 ((uint8)(																											\
		(uint8)((ADC_CFG_HWUNIT##hNbr##_TH5 == STD_ON) ?									/* TH5E		:  5		*/	\
			(ADC_THER_THZE_ENABLE	* ADC_THER_TH5E) :																	\
			(ADC_THER_THZE_DISABLE	* ADC_THER_TH5E) )																	\
	   +(uint8)((ADC_CFG_HWUNIT##hNbr##_TH4 == STD_ON) ?									/* TH4E		:  4		*/	\
			(ADC_THER_THZE_ENABLE	* ADC_THER_TH4E) :																	\
			(ADC_THER_THZE_DISABLE	* ADC_THER_TH4E) )																	\
	   +(uint8)((ADC_CFG_HWUNIT##hNbr##_TH3 == STD_ON) ?									/* TH3E		:  3		*/	\
			(ADC_THER_THZE_ENABLE	* ADC_THER_TH3E) :																	\
			(ADC_THER_THZE_DISABLE	* ADC_THER_TH3E) )																	\
	   +(uint8)((ADC_CFG_HWUNIT##hNbr##_TH2 == STD_ON) ?									/* TH2E		:  2		*/	\
			(ADC_THER_THZE_ENABLE	* ADC_THER_TH2E) :																	\
			(ADC_THER_THZE_DISABLE	* ADC_THER_TH2E) )																	\
	   +(uint8)((ADC_CFG_HWUNIT##hNbr##_TH1 == STD_ON) ?									/* TH1E		:  1		*/	\
			(ADC_THER_THZE_ENABLE	* ADC_THER_TH1E) :																	\
			(ADC_THER_THZE_DISABLE	* ADC_THER_TH1E) )																	\
	   +(uint8)((ADC_CFG_HWUNIT##hNbr##_TH0 == STD_ON) ?									/* TH0E		:  0		*/	\
			(ADC_THER_THZE_ENABLE	* ADC_THER_TH0E) :																	\
			(ADC_THER_THZE_DISABLE	* ADC_THER_TH0E) )																	\
	))
#endif	/* #if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A)	*/

/*----------------------------------------------------------------------------------*/
/*  T&H Group A Control Register 					: ADCXnTHACR					*/
/*----------------------------------------------------------------------------------*/
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A)
	#define		ADC_SetTHACR(hNbr)																						\
	 ((uint8)((ADC_CFG_HWUNIT##hNbr##_TH3 == STD_ON) ?										/* HLDCTE	:  5		*/	\
				(ADC_THACR_HLDCTE_ENABLE					* ADC_THACR_HLDCTE) :										\
	   			((ADC_CFG_HWUNIT##hNbr##_TH2 == STD_ON) ?																\
					(ADC_THACR_HLDCTE_ENABLE				* ADC_THACR_HLDCTE) :										\
					((ADC_CFG_HWUNIT##hNbr##_TH1 == STD_ON) ?															\
						(ADC_THACR_HLDCTE_ENABLE			* ADC_THACR_HLDCTE) :										\
						((ADC_CFG_HWUNIT##hNbr##_TH0 == STD_ON) ?														\
							(ADC_THACR_HLDCTE_ENABLE		* ADC_THACR_HLDCTE) :										\
							(ADC_THACR_HLDCTE_DISABLE	* ADC_THACR_HLDCTE)												\
						)																								\
					)																									\
				)																										\
		))
#else	/* MCAL_TARGET_RH850U2B	*/
	#define		ADC_SetTHACR(hNbr)																						\
		((uint8)((ADC_CFG_HWUNIT##hNbr##_TH5 == STD_ON) ?									/* HLDCTE	:  5		*/	\
				(ADC_THACR_HLDCTE_ENABLE							* ADC_THACR_HLDCTE) :								\
	   			((ADC_CFG_HWUNIT##hNbr##_TH4 == STD_ON) ?																\
					(ADC_THACR_HLDCTE_ENABLE						* ADC_THACR_HLDCTE) :								\
	   				((ADC_CFG_HWUNIT##hNbr##_TH3 == STD_ON) ?															\
						(ADC_THACR_HLDCTE_ENABLE					* ADC_THACR_HLDCTE) :								\
		   				((ADC_CFG_HWUNIT##hNbr##_TH2 == STD_ON) ?														\
							(ADC_THACR_HLDCTE_ENABLE				* ADC_THACR_HLDCTE) :								\
							((ADC_CFG_HWUNIT##hNbr##_TH1 == STD_ON) ?													\
								(ADC_THACR_HLDCTE_ENABLE			* ADC_THACR_HLDCTE) :								\
								((ADC_CFG_HWUNIT##hNbr##_TH0 == STD_ON) ?												\
									(ADC_THACR_HLDCTE_ENABLE		* ADC_THACR_HLDCTE) :								\
									(ADC_THACR_HLDCTE_DISABLE	* ADC_THACR_HLDCTE) 									\
								)																						\
							)																							\
						)																								\
					)																									\
				)																										\
		))
#endif	/* #if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A)	*/

/*----------------------------------------------------------------------------------*/
/*  T&H Group B Control Register 					: ADCXnTHBCR					*/
/*----------------------------------------------------------------------------------*/
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	#define		ADC_SetTHBCR(hNbr)																						\
		((uint8)((ADC_CFG_HWUNIT##hNbr##_TH5 == STD_ON) ?									/* HLDCTE	:  5		*/	\
				(ADC_THBCR_HLDCTE_ENABLE							* ADC_THBCR_HLDCTE) :								\
	   			((ADC_CFG_HWUNIT##hNbr##_TH4 == STD_ON) ?																\
					(ADC_THBCR_HLDCTE_ENABLE						* ADC_THBCR_HLDCTE) :								\
	   				((ADC_CFG_HWUNIT##hNbr##_TH3 == STD_ON) ?															\
						(ADC_THBCR_HLDCTE_ENABLE					* ADC_THBCR_HLDCTE) :								\
		   				((ADC_CFG_HWUNIT##hNbr##_TH2 == STD_ON) ?														\
							(ADC_THBCR_HLDCTE_ENABLE				* ADC_THBCR_HLDCTE) :								\
							((ADC_CFG_HWUNIT##hNbr##_TH1 == STD_ON) ?													\
								(ADC_THBCR_HLDCTE_ENABLE			* ADC_THBCR_HLDCTE) :								\
								((ADC_CFG_HWUNIT##hNbr##_TH0 == STD_ON) ?												\
									(ADC_THBCR_HLDCTE_ENABLE		* ADC_THBCR_HLDCTE) :								\
									(ADC_THBCR_HLDCTE_DISABLE	* ADC_THBCR_HLDCTE)										\
								)																						\
							)																							\
						)																								\
					)																									\
				)																										\
		))
#endif	/* #if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)	*/

/*--------------------------------------------------------------------------------------*/
/*  	SW  Setting																		*/
/*--------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------*/
/*  	Adc Configuration 															*/
/*----------------------------------------------------------------------------------*/
#define ADC_START_SEC_CONST_8				/* ADC RODATA CONST 8bit Section Start				*/
#include "Adc_MemMap.h"

#if (ADC_CFG_GRP_SIZE >=  1U)	 
static CONST(Adc_ChannelType, ADC_CONST) s_cpstGrp00CnvChTbl[ADC_CFG_GRP00_CNV_CH_SIZE] = ADC_CFG_GRP00_CNV_CH;
#endif
#if (ADC_CFG_GRP_SIZE >=  2U)
static CONST(Adc_ChannelType, ADC_CONST) s_cpstGrp01CnvChTbl[ADC_CFG_GRP01_CNV_CH_SIZE] = ADC_CFG_GRP01_CNV_CH;
#endif
#if (ADC_CFG_GRP_SIZE >=  3U)
static CONST(Adc_ChannelType, ADC_CONST) s_cpstGrp02CnvChTbl[ADC_CFG_GRP02_CNV_CH_SIZE] = ADC_CFG_GRP02_CNV_CH;
#endif
#if (ADC_CFG_GRP_SIZE >=  4U)
static CONST(Adc_ChannelType, ADC_CONST) s_cpstGrp03CnvChTbl[ADC_CFG_GRP03_CNV_CH_SIZE] = ADC_CFG_GRP03_CNV_CH;
#endif
#if (ADC_CFG_GRP_SIZE >=  5U)
static CONST(Adc_ChannelType, ADC_CONST) s_cpstGrp04CnvChTbl[ADC_CFG_GRP04_CNV_CH_SIZE] = ADC_CFG_GRP04_CNV_CH;
#endif
#if (ADC_CFG_GRP_SIZE >=  6U)
static CONST(Adc_ChannelType, ADC_CONST) s_cpstGrp05CnvChTbl[ADC_CFG_GRP05_CNV_CH_SIZE] = ADC_CFG_GRP05_CNV_CH;
#endif
#if (ADC_CFG_GRP_SIZE >=  7U)
static CONST(Adc_ChannelType, ADC_CONST) s_cpstGrp06CnvChTbl[ADC_CFG_GRP06_CNV_CH_SIZE] = ADC_CFG_GRP06_CNV_CH;
#endif
#if (ADC_CFG_GRP_SIZE >=  8U)
static CONST(Adc_ChannelType, ADC_CONST) s_cpstGrp07CnvChTbl[ADC_CFG_GRP07_CNV_CH_SIZE] = ADC_CFG_GRP07_CNV_CH;
#endif
#if (ADC_CFG_GRP_SIZE >=  9U)
static CONST(Adc_ChannelType, ADC_CONST) s_cpstGrp08CnvChTbl[ADC_CFG_GRP08_CNV_CH_SIZE] = ADC_CFG_GRP08_CNV_CH;
#endif
#if (ADC_CFG_GRP_SIZE >= 10U)
static CONST(Adc_ChannelType, ADC_CONST) s_cpstGrp09CnvChTbl[ADC_CFG_GRP09_CNV_CH_SIZE] = ADC_CFG_GRP09_CNV_CH;
#endif
#if (ADC_CFG_GRP_SIZE >= 11U)
static CONST(Adc_ChannelType, ADC_CONST) s_cpstGrp10CnvChTbl[ADC_CFG_GRP10_CNV_CH_SIZE] = ADC_CFG_GRP10_CNV_CH;
#endif
#if (ADC_CFG_GRP_SIZE >= 12U)
static CONST(Adc_ChannelType, ADC_CONST) s_cpstGrp11CnvChTbl[ADC_CFG_GRP11_CNV_CH_SIZE] = ADC_CFG_GRP11_CNV_CH;
#endif
#if (ADC_CFG_GRP_SIZE >= 13U)
static CONST(Adc_ChannelType, ADC_CONST) s_cpstGrp12CnvChTbl[ADC_CFG_GRP12_CNV_CH_SIZE] = ADC_CFG_GRP12_CNV_CH;
#endif
#if (ADC_CFG_GRP_SIZE >= 14U)
static CONST(Adc_ChannelType, ADC_CONST) s_cpstGrp13CnvChTbl[ADC_CFG_GRP13_CNV_CH_SIZE] = ADC_CFG_GRP13_CNV_CH;
#endif
#if (ADC_CFG_GRP_SIZE >= 15U)
static CONST(Adc_ChannelType, ADC_CONST) s_cpstGrp14CnvChTbl[ADC_CFG_GRP14_CNV_CH_SIZE] = ADC_CFG_GRP14_CNV_CH;
#endif
#define ADC_STOP_SEC_CONST_8				/* ADC RODATA 8bit Section Stop						*/
#include "Adc_MemMap.h"

#define ADC_START_SEC_CONST_UNSPECIFIED		/* ADC RODATA CONST UNSPECIFIED Section Start		*/
#include "Adc_MemMap.h"
/* Adc HW Configuration */
static CONST(Adc_GrpHWInfoType, ADC_CONST) s_cstGrpHWInfo[ADC_CFG_GRP_SIZE] = {
	/* 		HW Unit						HW Trg:TAUD2 CH7  			HW Trg:TAUD2 CH15 			HW Trg:TAUJ2 CH3 			HW Trg:TAUJ3 CH3 																						*/
	#if (ADC_CFG_GRP_SIZE >=  1U)	 
		 {	&s_cpstGrp00CnvChTbl[0],	ADC_CFG_GRP00_TAUD2_CH7,	ADC_CFG_GRP00_TAUD2_CH15,	ADC_CFG_GRP00_TAUJ2_CH3,	ADC_CFG_GRP00_TAUJ3_CH3	}
	#endif
	#if (ADC_CFG_GRP_SIZE >=  2U)
		,{	&s_cpstGrp01CnvChTbl[0],	ADC_CFG_GRP01_TAUD2_CH7,	ADC_CFG_GRP01_TAUD2_CH15,	ADC_CFG_GRP01_TAUJ2_CH3,	ADC_CFG_GRP01_TAUJ3_CH3	}
	#endif
	#if (ADC_CFG_GRP_SIZE >=  3U)
		,{	&s_cpstGrp02CnvChTbl[0],	ADC_CFG_GRP02_TAUD2_CH7,	ADC_CFG_GRP02_TAUD2_CH15,	ADC_CFG_GRP02_TAUJ2_CH3,	ADC_CFG_GRP02_TAUJ3_CH3	}
	#endif
	#if (ADC_CFG_GRP_SIZE >=  4U)
		,{	&s_cpstGrp03CnvChTbl[0],	ADC_CFG_GRP03_TAUD2_CH7,	ADC_CFG_GRP03_TAUD2_CH15,	ADC_CFG_GRP03_TAUJ2_CH3,	ADC_CFG_GRP03_TAUJ3_CH3	}
	#endif
	#if (ADC_CFG_GRP_SIZE >=  5U)
		,{	&s_cpstGrp04CnvChTbl[0],	ADC_CFG_GRP04_TAUD2_CH7,	ADC_CFG_GRP04_TAUD2_CH15,	ADC_CFG_GRP04_TAUJ2_CH3,	ADC_CFG_GRP04_TAUJ3_CH3	}
	#endif
	#if (ADC_CFG_GRP_SIZE >=  6U)
		,{	&s_cpstGrp05CnvChTbl[0],	ADC_CFG_GRP05_TAUD2_CH7,	ADC_CFG_GRP05_TAUD2_CH15,	ADC_CFG_GRP05_TAUJ2_CH3,	ADC_CFG_GRP05_TAUJ3_CH3	}
	#endif
	#if (ADC_CFG_GRP_SIZE >=  7U)
		,{	&s_cpstGrp06CnvChTbl[0],	ADC_CFG_GRP06_TAUD2_CH7,	ADC_CFG_GRP06_TAUD2_CH15,	ADC_CFG_GRP06_TAUJ2_CH3,	ADC_CFG_GRP06_TAUJ3_CH3	}
	#endif
	#if (ADC_CFG_GRP_SIZE >=  8U)
		,{	&s_cpstGrp07CnvChTbl[0],	ADC_CFG_GRP07_TAUD2_CH7,	ADC_CFG_GRP07_TAUD2_CH15,	ADC_CFG_GRP07_TAUJ2_CH3,	ADC_CFG_GRP07_TAUJ3_CH3	}
	#endif
	#if (ADC_CFG_GRP_SIZE >=  9U)
		,{	&s_cpstGrp08CnvChTbl[0],	ADC_CFG_GRP08_TAUD2_CH7,	ADC_CFG_GRP08_TAUD2_CH15,	ADC_CFG_GRP08_TAUJ2_CH3,	ADC_CFG_GRP08_TAUJ3_CH3	}
	#endif
	#if (ADC_CFG_GRP_SIZE >= 10U)
		,{	&s_cpstGrp09CnvChTbl[0],	ADC_CFG_GRP09_TAUD2_CH7,	ADC_CFG_GRP09_TAUD2_CH15,	ADC_CFG_GRP09_TAUJ2_CH3,	ADC_CFG_GRP09_TAUJ3_CH3	}
	#endif
	#if (ADC_CFG_GRP_SIZE >= 11U)
		,{	&s_cpstGrp10CnvChTbl[0],	ADC_CFG_GRP10_TAUD2_CH7,	ADC_CFG_GRP10_TAUD2_CH15,	ADC_CFG_GRP10_TAUJ2_CH3,	ADC_CFG_GRP10_TAUJ3_CH3	}
	#endif
	#if (ADC_CFG_GRP_SIZE >= 12U)
		,{	&s_cpstGrp11CnvChTbl[0],	ADC_CFG_GRP11_TAUD2_CH7,	ADC_CFG_GRP11_TAUD2_CH15,	ADC_CFG_GRP11_TAUJ2_CH3,	ADC_CFG_GRP11_TAUJ3_CH3	}
	#endif
	#if (ADC_CFG_GRP_SIZE >= 13U)
		,{	&s_cpstGrp12CnvChTbl[0],	ADC_CFG_GRP12_TAUD2_CH7,	ADC_CFG_GRP12_TAUD2_CH15,	ADC_CFG_GRP12_TAUJ2_CH3,	ADC_CFG_GRP12_TAUJ3_CH3	}
	#endif
	#if (ADC_CFG_GRP_SIZE >= 14U)
		,{	&s_cpstGrp13CnvChTbl[0],	ADC_CFG_GRP13_TAUD2_CH7,	ADC_CFG_GRP13_TAUD2_CH15,	ADC_CFG_GRP13_TAUJ2_CH3,	ADC_CFG_GRP13_TAUJ3_CH3	}
	#endif
	#if (ADC_CFG_GRP_SIZE >= 15U)
		,{	&s_cpstGrp14CnvChTbl[0],	ADC_CFG_GRP14_TAUD2_CH7,	ADC_CFG_GRP14_TAUD2_CH15,	ADC_CFG_GRP14_TAUJ2_CH3,	ADC_CFG_GRP14_TAUJ3_CH3	}
	#endif
};

static CONST(Adc_HWConfigType, ADC_CONST) s_cstAdc_HWConfig = {
	&s_cstGrpHWInfo[ADC_ZERO],
	{ /* cudHWTHCHTbl[ADC_HWUNIT_WTH_NUM][ADC_TH_NUM];	Use T&H channel ID Tbl	*/
		{	/* HW Unit 0	*/
			#if (ADC_CFG_HWUNIT0_TH0==STD_ON)
				ADC_CH00,
			#else
				ADC_CH_NONE,
			#endif
			#if (ADC_CFG_HWUNIT0_TH1==STD_ON)
				ADC_CH01,
			#else
				ADC_CH_NONE,
			#endif
			#if (ADC_CFG_HWUNIT0_TH2==STD_ON)
				ADC_CH02,
			#else
				ADC_CH_NONE,
			#endif
			#if (ADC_CFG_HWUNIT0_TH3==STD_ON)
				ADC_CH03
			#else
				ADC_CH_NONE
			#endif
			#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
				#if (ADC_CFG_HWUNIT0_TH4==STD_ON)
					,ADC_CH04,
				#else
					,ADC_CH_NONE,
				#endif
				#if (ADC_CFG_HWUNIT0_TH5==STD_ON)
					ADC_CH05	
				#else
					ADC_CH_NONE
				#endif
			#endif
		},
		{	/* HW Unit 1	*/
			#if (ADC_CFG_HWUNIT1_TH0==STD_ON)
				ADC_CH00,
			#else
				ADC_CH_NONE,
			#endif
			#if (ADC_CFG_HWUNIT1_TH1==STD_ON)
				ADC_CH01,
			#else
				ADC_CH_NONE,
			#endif
			#if (ADC_CFG_HWUNIT1_TH2==STD_ON)
				ADC_CH02,
			#else
				ADC_CH_NONE,
			#endif
			#if (ADC_CFG_HWUNIT1_TH3==STD_ON)
				ADC_CH03
			#else
				ADC_CH_NONE
			#endif
			#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
				#if (ADC_CFG_HWUNIT1_TH4==STD_ON)
					,ADC_CH04,
				#else
					,ADC_CH_NONE,
				#endif
				#if (ADC_CFG_HWUNIT1_TH5==STD_ON)
					ADC_CH05
				#else
					ADC_CH_NONE
				#endif
			#endif	/* #if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)	*/
		},
		#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
		{	/* HW Unit 2	*/
			#if (ADC_CFG_HWUNIT2_TH0==STD_ON)
				ADC_CH00,
			#else
				ADC_CH_NONE,
			#endif
			#if (ADC_CFG_HWUNIT2_TH1==STD_ON)
				ADC_CH01,
			#else
				ADC_CH_NONE,
			#endif
			#if (ADC_CFG_HWUNIT2_TH2==STD_ON)
				ADC_CH02,
			#else
				ADC_CH_NONE,
			#endif
			#if (ADC_CFG_HWUNIT2_TH3==STD_ON)
				ADC_CH03,
			#else
				ADC_CH_NONE,
			#endif
			ADC_CH_NONE,
			ADC_CH_NONE
		}
		#endif	/* #if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)	*/
	},
	{	/* cu4SMPCR[ADC_HWUNIT_NUM];	ADCXnSMPCR	*/
		/*	HW Unit 0		HW Unit 1		HW Unit 2	*/
		ADC_SetSMPCR(0), ADC_SetSMPCR(1), ADC_SetSMPCR(2)
		#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
			#if ((MCAL_PKG_TARGET==MCAL_PKG_U2B24_468PIN)		\
			  || (MCAL_PKG_TARGET==MCAL_PKG_U2B24_373PIN)		\
			  || (MCAL_PKG_TARGET==MCAL_PKG_U2B20_468PIN)		\
			  || (MCAL_PKG_TARGET==MCAL_PKG_U2B20_373PIN)		\
			  || (MCAL_PKG_TARGET==MCAL_PKG_U2B10_468PIN)		\
			  || (MCAL_PKG_TARGET==MCAL_PKG_U2B10_373PIN))
				,ADC_SetSMPCR(3)	/* HW Unit 3	*/
			#endif
			#if ((MCAL_PKG_TARGET==MCAL_PKG_U2B24_468PIN)		\
			  || (MCAL_PKG_TARGET==MCAL_PKG_U2B24_373PIN)		\
			  || (MCAL_PKG_TARGET==MCAL_PKG_U2B20_468PIN)		\
			  || (MCAL_PKG_TARGET==MCAL_PKG_U2B20_373PIN))
				,ADC_SetSMPCR(A)	/* HW Unit A	*/
			#endif
		#endif	/* #if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)	*/
	},
	{	/* cu1SGCR [ADC_CFG_GRP_SIZE];	ADCXxSCCRx	*/
		#if (ADC_CFG_GRP_SIZE >=  1U)	 
			ADC_SetSGCR(00)
		#endif
		#if (ADC_CFG_GRP_SIZE >=  2U)
			,ADC_SetSGCR(01)
		#endif
		#if (ADC_CFG_GRP_SIZE >=  3U)
			,ADC_SetSGCR(02)
		#endif
		#if (ADC_CFG_GRP_SIZE >=  4U)
			,ADC_SetSGCR(03)
		#endif
		#if (ADC_CFG_GRP_SIZE >=  5U)
			,ADC_SetSGCR(04)
		#endif
		#if (ADC_CFG_GRP_SIZE >=  6U)
			,ADC_SetSGCR(05)
		#endif
		#if (ADC_CFG_GRP_SIZE >=  7U)
			,ADC_SetSGCR(06)
		#endif
		#if (ADC_CFG_GRP_SIZE >=  8U)
			,ADC_SetSGCR(07)
		#endif
		#if (ADC_CFG_GRP_SIZE >=  9U)
			,ADC_SetSGCR(08)
		#endif
		#if (ADC_CFG_GRP_SIZE >= 10U)
			,ADC_SetSGCR(09)
		#endif
		#if (ADC_CFG_GRP_SIZE >= 11U)
			,ADC_SetSGCR(10)
		#endif
		#if (ADC_CFG_GRP_SIZE >= 12U)
			,ADC_SetSGCR(11)
		#endif
		#if (ADC_CFG_GRP_SIZE >= 13U)
			,ADC_SetSGCR(12)
		#endif
		#if (ADC_CFG_GRP_SIZE >= 14U)
			,ADC_SetSGCR(13)
		#endif
		#if (ADC_CFG_GRP_SIZE >= 15U)
			,ADC_SetSGCR(14)
		#endif
	},
	{	/* cu1ADCR1[ADC_HWUNIT_NUM];	ADCXnADCR1	*/
		/*	HW Unit 0		HW Unit 1			HW Unit 2	*/
		ADC_SetADCR1(0),	ADC_SetADCR1(1),	ADC_SetADCR1(2)
		#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
			#if ((MCAL_PKG_TARGET==MCAL_PKG_U2B24_468PIN)		\
			  || (MCAL_PKG_TARGET==MCAL_PKG_U2B24_373PIN)		\
			  || (MCAL_PKG_TARGET==MCAL_PKG_U2B20_468PIN)		\
			  || (MCAL_PKG_TARGET==MCAL_PKG_U2B20_373PIN)		\
			  || (MCAL_PKG_TARGET==MCAL_PKG_U2B10_468PIN)		\
			  || (MCAL_PKG_TARGET==MCAL_PKG_U2B10_373PIN))
			  	,ADC_SetADCR1(3)	/* HW Unit 3	*/
			#endif
			#if ((MCAL_PKG_TARGET==MCAL_PKG_U2B24_468PIN)		\
			  || (MCAL_PKG_TARGET==MCAL_PKG_U2B24_373PIN)		\
			  || (MCAL_PKG_TARGET==MCAL_PKG_U2B20_468PIN)		\
			  || (MCAL_PKG_TARGET==MCAL_PKG_U2B20_373PIN))
			  	,ADC_SetADCR1(A)	/* HW Unit A	*/
			#endif
		#endif	/* #if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)	*/
	},
	{	/* cu1ADCR2[ADC_HWUNIT_NUM];	ADCXnADCR2	*/
		/*	HW Unit 0		HW Unit 1			HW Unit 2	*/
		ADC_SetADCR2(0),	ADC_SetADCR2(1),	ADC_SetADCR2(2)
		#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
			#if ((MCAL_PKG_TARGET==MCAL_PKG_U2B24_468PIN)		\
			  || (MCAL_PKG_TARGET==MCAL_PKG_U2B24_373PIN)		\
			  || (MCAL_PKG_TARGET==MCAL_PKG_U2B20_468PIN)		\
			  || (MCAL_PKG_TARGET==MCAL_PKG_U2B20_373PIN)		\
			  || (MCAL_PKG_TARGET==MCAL_PKG_U2B10_468PIN)		\
			  || (MCAL_PKG_TARGET==MCAL_PKG_U2B10_373PIN))
			  	,ADC_SetADCR2(3)	/* HW Unit 3	*/
			#endif
			#if ((MCAL_PKG_TARGET==MCAL_PKG_U2B24_468PIN)		\
			  || (MCAL_PKG_TARGET==MCAL_PKG_U2B24_373PIN)		\
			  || (MCAL_PKG_TARGET==MCAL_PKG_U2B20_468PIN)		\
			  || (MCAL_PKG_TARGET==MCAL_PKG_U2B20_373PIN))
			  	,ADC_SetADCR2(A)	/* HW Unit A	*/
			#endif
		#endif	/* #if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)	*/
	},
	#ifdef ADC_USE_TH
		{	/* cu1THCR [ADC_HWUNIT_WTH_NUM];	ADCXnTHCR							*/
			/*	HW Unit 0		HW Unit 1	*/
			ADC_SetTHCR(),		ADC_SetTHCR()
			#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
				/* HW Unit 2				*/
				,ADC_SetTHCR()
			#endif	/* #if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)	*/
		},
		{	/* cu1THER [ADC_HWUNIT_WTH_NUM];	ADCXnTHER							*/
			/*	HW Unit 0		HW Unit 1	*/
			ADC_SetTHER(0),		ADC_SetTHER(1)
			#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
				/* HW Unit 2				*/
				,ADC_SetTHER(2)
			#endif	/* #if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)	*/
		},	
		{	/* cu1THACR[ADC_HWUNIT_WTH_NUM];	ADCXnTHACR							*/
			/*	HW Unit 0		HW Unit 1	*/
			ADC_SetTHACR(0),	ADC_SetTHACR(1)
			#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
				/* HW Unit 2				*/
				,ADC_SetTHACR(2)
			#endif	/* #if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)	*/
		}
		#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
		,{	/* cu1THBCR[ADC_HWUNIT_WTH_NUM];	ADCXnTHBCR							*/
			/*	HW Unit 0		HW Unit 1			HW Unit 2						*/
			ADC_SetTHBCR(0),	ADC_SetTHBCR(1),	ADC_SetTHBCR(2)
		}
		#endif	/* #if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)	*/
	#endif	/* #ifdef ADC_USE_TH	*/
};

/* Adc SW Configuration */

static CONST(Adc_SWConfigType, ADC_CONST) s_cstSWConfig[ADC_CFG_GRP_SIZE] = {
	#if (ADC_CFG_GRP_SIZE >=  1U)
		{	ADC_CFG_GRP00_HWUNIT,
			ADC_CFG_GRP00_SG,
			ADC_CFG_GRP00_CNV_MODE,
			ADC_CFG_GRP00_TRIGG_SRC,
			ADC_CFG_GRP00_CNV_CH_SIZE,
			ADC_CFG_GRP00_USE_CNV_INT,
			ADC_CFG_GRP00_CNV_NOTIF,
			ADC_CFG_GRP00_USE_DMA,
			ADC_CFG_GRP00_USE_DMA_HALF_INT,
			ADC_CFG_GRP00_DMA_ID,
			ADC_CFG_GRP00_ACCESS_MODE,
			ADC_CFG_GRP00_STREAMING_NUM	}
	#endif
	#if (ADC_CFG_GRP_SIZE >=  2U)
		,{	ADC_CFG_GRP01_HWUNIT,
			ADC_CFG_GRP01_SG,		
			ADC_CFG_GRP01_CNV_MODE,
			ADC_CFG_GRP01_TRIGG_SRC,
			ADC_CFG_GRP01_CNV_CH_SIZE,
			ADC_CFG_GRP01_USE_CNV_INT,
			ADC_CFG_GRP01_CNV_NOTIF,
			ADC_CFG_GRP01_USE_DMA,
			ADC_CFG_GRP01_USE_DMA_HALF_INT,
			ADC_CFG_GRP01_DMA_ID,
			ADC_CFG_GRP01_ACCESS_MODE,
			ADC_CFG_GRP01_STREAMING_NUM	}
	#endif
	#if (ADC_CFG_GRP_SIZE >=  3U)
		,{	ADC_CFG_GRP02_HWUNIT,
			ADC_CFG_GRP02_SG,		
			ADC_CFG_GRP02_CNV_MODE,
			ADC_CFG_GRP02_TRIGG_SRC,
			ADC_CFG_GRP02_CNV_CH_SIZE,
			ADC_CFG_GRP02_USE_CNV_INT,
			ADC_CFG_GRP02_CNV_NOTIF,
			ADC_CFG_GRP02_USE_DMA,
			ADC_CFG_GRP02_USE_DMA_HALF_INT,
			ADC_CFG_GRP02_DMA_ID,
			ADC_CFG_GRP02_ACCESS_MODE,
			ADC_CFG_GRP02_STREAMING_NUM	}
	#endif
	#if (ADC_CFG_GRP_SIZE >=  4U)
		,{	ADC_CFG_GRP03_HWUNIT,
			ADC_CFG_GRP03_SG,		
			ADC_CFG_GRP03_CNV_MODE,
			ADC_CFG_GRP03_TRIGG_SRC,
			ADC_CFG_GRP03_CNV_CH_SIZE,
			ADC_CFG_GRP03_USE_CNV_INT,
			ADC_CFG_GRP03_CNV_NOTIF,
			ADC_CFG_GRP03_USE_DMA,
			ADC_CFG_GRP03_USE_DMA_HALF_INT,
			ADC_CFG_GRP03_DMA_ID,
			ADC_CFG_GRP03_ACCESS_MODE,
			ADC_CFG_GRP03_STREAMING_NUM	}
	#endif
	#if (ADC_CFG_GRP_SIZE >=  5U)
		,{	ADC_CFG_GRP04_HWUNIT,
			ADC_CFG_GRP04_SG,		
			ADC_CFG_GRP04_CNV_MODE,
			ADC_CFG_GRP04_TRIGG_SRC,
			ADC_CFG_GRP04_CNV_CH_SIZE,
			ADC_CFG_GRP04_USE_CNV_INT,
			ADC_CFG_GRP04_CNV_NOTIF,
			ADC_CFG_GRP04_USE_DMA,
			ADC_CFG_GRP04_USE_DMA_HALF_INT,
			ADC_CFG_GRP04_DMA_ID,
			ADC_CFG_GRP04_ACCESS_MODE,
			ADC_CFG_GRP04_STREAMING_NUM	}
	#endif
	#if (ADC_CFG_GRP_SIZE >=  6U)
		,{	ADC_CFG_GRP05_HWUNIT,
			ADC_CFG_GRP05_SG,		
			ADC_CFG_GRP05_CNV_MODE,
			ADC_CFG_GRP05_TRIGG_SRC,
			ADC_CFG_GRP05_CNV_CH_SIZE,
			ADC_CFG_GRP05_USE_CNV_INT,
			ADC_CFG_GRP05_CNV_NOTIF,
			ADC_CFG_GRP05_USE_DMA,
			ADC_CFG_GRP05_USE_DMA_HALF_INT,
			ADC_CFG_GRP05_DMA_ID,
			ADC_CFG_GRP05_ACCESS_MODE,
			ADC_CFG_GRP05_STREAMING_NUM	}
	#endif
	#if (ADC_CFG_GRP_SIZE >=  7U)
		,{	ADC_CFG_GRP06_HWUNIT,
			ADC_CFG_GRP06_SG,		
			ADC_CFG_GRP06_CNV_MODE,
			ADC_CFG_GRP06_TRIGG_SRC,
			ADC_CFG_GRP06_CNV_CH_SIZE,
			ADC_CFG_GRP06_USE_CNV_INT,
			ADC_CFG_GRP06_CNV_NOTIF,
			ADC_CFG_GRP06_USE_DMA,
			ADC_CFG_GRP06_USE_DMA_HALF_INT,
			ADC_CFG_GRP06_DMA_ID,
			ADC_CFG_GRP06_ACCESS_MODE,
			ADC_CFG_GRP06_STREAMING_NUM	}
	#endif
	#if (ADC_CFG_GRP_SIZE >=  8U)
		,{	ADC_CFG_GRP07_HWUNIT,
			ADC_CFG_GRP07_SG,		
			ADC_CFG_GRP07_CNV_MODE,
			ADC_CFG_GRP07_TRIGG_SRC,
			ADC_CFG_GRP07_CNV_CH_SIZE,
			ADC_CFG_GRP07_USE_CNV_INT,
			ADC_CFG_GRP07_CNV_NOTIF,
			ADC_CFG_GRP07_USE_DMA,
			ADC_CFG_GRP07_USE_DMA_HALF_INT,
			ADC_CFG_GRP07_DMA_ID,
			ADC_CFG_GRP07_ACCESS_MODE,
			ADC_CFG_GRP07_STREAMING_NUM	}
	#endif
	#if (ADC_CFG_GRP_SIZE >=  9U)
		,{	ADC_CFG_GRP08_HWUNIT,
			ADC_CFG_GRP08_SG,		
			ADC_CFG_GRP08_CNV_MODE,
			ADC_CFG_GRP08_TRIGG_SRC,
			ADC_CFG_GRP08_CNV_CH_SIZE,
			ADC_CFG_GRP08_USE_CNV_INT,
			ADC_CFG_GRP08_CNV_NOTIF,
			ADC_CFG_GRP08_USE_DMA,
			ADC_CFG_GRP08_USE_DMA_HALF_INT,
			ADC_CFG_GRP08_DMA_ID,
			ADC_CFG_GRP08_ACCESS_MODE,
			ADC_CFG_GRP08_STREAMING_NUM	}
	#endif
	#if (ADC_CFG_GRP_SIZE >= 10U)
		,{	ADC_CFG_GRP09_HWUNIT,
			ADC_CFG_GRP09_SG,		
			ADC_CFG_GRP09_CNV_MODE,
			ADC_CFG_GRP09_TRIGG_SRC,
			ADC_CFG_GRP09_CNV_CH_SIZE,
			ADC_CFG_GRP09_USE_CNV_INT,
			ADC_CFG_GRP09_CNV_NOTIF,
			ADC_CFG_GRP09_USE_DMA,
			ADC_CFG_GRP09_USE_DMA_HALF_INT,
			ADC_CFG_GRP09_DMA_ID,
			ADC_CFG_GRP09_ACCESS_MODE,
			ADC_CFG_GRP09_STREAMING_NUM	}
	#endif
	#if (ADC_CFG_GRP_SIZE >= 11U)
		,{	ADC_CFG_GRP10_HWUNIT,
			ADC_CFG_GRP10_SG,		
			ADC_CFG_GRP10_CNV_MODE,
			ADC_CFG_GRP10_TRIGG_SRC,
			ADC_CFG_GRP10_CNV_CH_SIZE,
			ADC_CFG_GRP10_USE_CNV_INT,
			ADC_CFG_GRP10_CNV_NOTIF,
			ADC_CFG_GRP10_USE_DMA,
			ADC_CFG_GRP10_USE_DMA_HALF_INT,
			ADC_CFG_GRP10_DMA_ID,
			ADC_CFG_GRP10_ACCESS_MODE,
			ADC_CFG_GRP10_STREAMING_NUM	}
	#endif
	#if (ADC_CFG_GRP_SIZE >= 12U)
		,{	ADC_CFG_GRP11_HWUNIT,
			ADC_CFG_GRP11_SG,		
			ADC_CFG_GRP11_CNV_MODE,
			ADC_CFG_GRP11_TRIGG_SRC,
			ADC_CFG_GRP11_CNV_CH_SIZE,
			ADC_CFG_GRP11_USE_CNV_INT,
			ADC_CFG_GRP11_CNV_NOTIF,
			ADC_CFG_GRP11_USE_DMA,
			ADC_CFG_GRP11_USE_DMA_HALF_INT,
			ADC_CFG_GRP11_DMA_ID,
			ADC_CFG_GRP11_ACCESS_MODE,
			ADC_CFG_GRP11_STREAMING_NUM	}
	#endif
	#if (ADC_CFG_GRP_SIZE >= 13U)
		,{	ADC_CFG_GRP12_HWUNIT,
			ADC_CFG_GRP12_SG,		
			ADC_CFG_GRP12_CNV_MODE,
			ADC_CFG_GRP12_TRIGG_SRC,
			ADC_CFG_GRP12_CNV_CH_SIZE,
			ADC_CFG_GRP12_USE_CNV_INT,
			ADC_CFG_GRP12_CNV_NOTIF,
			ADC_CFG_GRP12_USE_DMA,
			ADC_CFG_GRP12_USE_DMA_HALF_INT,
			ADC_CFG_GRP12_DMA_ID,
			ADC_CFG_GRP12_ACCESS_MODE,
			ADC_CFG_GRP12_STREAMING_NUM	}
	#endif
	#if (ADC_CFG_GRP_SIZE >= 14U)
		,{	ADC_CFG_GRP13_HWUNIT,
			ADC_CFG_GRP13_SG,		
			ADC_CFG_GRP13_CNV_MODE,
			ADC_CFG_GRP13_TRIGG_SRC,
			ADC_CFG_GRP13_CNV_CH_SIZE,
			ADC_CFG_GRP13_USE_CNV_INT,
			ADC_CFG_GRP13_CNV_NOTIF,
			ADC_CFG_GRP13_USE_DMA,
			ADC_CFG_GRP13_USE_DMA_HALF_INT,
			ADC_CFG_GRP13_DMA_ID,
			ADC_CFG_GRP13_ACCESS_MODE,
			ADC_CFG_GRP13_STREAMING_NUM	}
	#endif
	#if (ADC_CFG_GRP_SIZE >= 15U)
		,{	ADC_CFG_GRP14_HWUNIT,
			ADC_CFG_GRP14_SG,		
			ADC_CFG_GRP14_CNV_MODE,
			ADC_CFG_GRP14_TRIGG_SRC,
			ADC_CFG_GRP14_CNV_CH_SIZE,
			ADC_CFG_GRP14_USE_CNV_INT,
			ADC_CFG_GRP14_CNV_NOTIF,
			ADC_CFG_GRP14_USE_DMA,
			ADC_CFG_GRP14_USE_DMA_HALF_INT,
			ADC_CFG_GRP14_DMA_ID,
			ADC_CFG_GRP14_ACCESS_MODE,
			ADC_CFG_GRP14_STREAMING_NUM	}
	#endif
};

/* Adc_ConfigType	*/
CONST(Adc_ConfigType, ADC_CONST) Adc_cstUserConfig = {
	&s_cstSWConfig[ADC_ZERO],			/* ADC SW Configuration	*/
	&s_cstAdc_HWConfig,					/* ADC HW Configuration	*/
	#if	(ADC_CFG_GLOBAL_REG_CONTROL == STD_ON)
	&s_cstPic2_Config,					/* PIC2 Configuration	*/
	#endif
};

#define ADC_STOP_SEC_CONST_UNSPECIFIED			/* ADC RODATA CONST UNSPECIFIED Section Stop	*/
#include "Adc_MemMap.h"

/*-- End Of File -------------------------------------------------------------------------------*/
