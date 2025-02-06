/* ADC-r04-303 */
/************************************************************************************************/
/*																								*/
/*		ADC Driver : User Configuration															*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/
#ifndef ADC_CFG_H
#define ADC_CFG_H

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
/*--------------------------------------------------------------------------------------*/
/*  include callback functions															*/
/*--------------------------------------------------------------------------------------*/

/*==============================================================================================*/
/*	User Configuration																			*/
/*==============================================================================================*/

/*--------------------------------------------------------------------------------------*/
/*  	General																			*/
/*--------------------------------------------------------------------------------------*/
/* Critical Section					*/
#define ADC_ENTER_CRITICAL_SECTION(x)											/* ADC exclusive area start						*/
#define ADC_EXIT_CRITICAL_SECTION(x)											/* ADC exclusive area end						*/

/* API								*/
#define ADC_CFG_DEINIT_API					(STD_OFF)							/* Adc_DeInit()									*/
#define ADC_CFG_START_STOP_GRP_API			(STD_ON)							/* Adc_Start/StopGroupConversion()				*/
#define ADC_CFG_HW_TRG_API					(STD_OFF)							/* Adc_Enable/DisableHardwareTrigger()			*/
#define ADC_CFG_READ_GRP_API				(STD_ON)							/* Adc_ReadGroup()								*/

/* features							*/
#define ADC_CFG_GRP_NOTIF_CAPABILITY		(STD_OFF)							/* Conversion End Notification Use				*/

#define ADC_CFG_DET_REPORT_RUNTIMEERROR		(STD_OFF)							/* Run Time Error Use							*/
#define ADC_CFG_DEM_SET_EVENT				(STD_OFF)							/* DEM error notification use					*/
#define ADC_CFG_PROCESS_TIMEOUT				(2000U)								/* Repeated judgment timeout value				*/
#define ADC_CFG_REG_CHK						(STD_OFF)							/* Register Check function Use					*/
#define ADC_CFG_REG_REFRESH					(STD_OFF)							/* Register Refresh Use							*/

/*--------------------------------------------------------------------------------------*/
/*  	HW Unit Setting																	*/
/*--------------------------------------------------------------------------------------*/
/* HW Unit 0						*/
#define ADC_CFG_HWUNIT0_SUSPEND_METHOD		(ADC_SUSPEND_METHOD_SYNC)			/* Suspend Method								*/
#define ADC_CFG_HWUNIT0_RESULT_FORMAT		(ADC_FORMAT_UNSIGNED_INTEGER)		/* Result Format								*/
#define ADC_CFG_HWUNIT0_RESULT_ALIGN		(ADC_ALIGN_RIGHT)					/* Result align									*/
#define ADC_CFG_HWUNIT0_RESOLUTION			(ADC_RESOLUTION_12BIT)				/* Resolution									*/
#define ADC_CFG_HWUNIT0_SAMPLING_PERIOD		(ADC_SAMPLING_PERIOD_18STATES)		/* Sampling Period								*/
#define ADC_CFG_HWUNIT0_BUFFER_AMP			(STD_ON)							/* Buffer Amplifie								*/
#define ADC_CFG_HWUNIT0_TH0					(STD_OFF)							/* ADC_CH00										*/
#define ADC_CFG_HWUNIT0_TH1					(STD_OFF)							/* ADC_CH01										*/
#define ADC_CFG_HWUNIT0_TH2					(STD_OFF)							/* ADC_CH02										*/
#define ADC_CFG_HWUNIT0_TH3					(STD_OFF)							/* ADC_CH03										*/
#define ADC_CFG_HWUNIT0_TH4					(STD_OFF)							/* U2B only:ADC_CH04							*/
#define ADC_CFG_HWUNIT0_TH5					(STD_OFF)							/* U2B only:ADC_CH05							*/

/* HW Unit 1						*/
#define ADC_CFG_HWUNIT1_SUSPEND_METHOD		(ADC_SUSPEND_METHOD_SYNC)			/* Suspend Method								*/
#define ADC_CFG_HWUNIT1_RESULT_FORMAT		(ADC_FORMAT_UNSIGNED_INTEGER)		/* Result Format								*/
#define ADC_CFG_HWUNIT1_RESULT_ALIGN		(ADC_ALIGN_RIGHT)					/* Result align									*/
#define ADC_CFG_HWUNIT1_RESOLUTION			(ADC_RESOLUTION_12BIT)				/* Resolution									*/
#define ADC_CFG_HWUNIT1_SAMPLING_PERIOD		(ADC_SAMPLING_PERIOD_18STATES)		/* Sampling Period								*/
#define ADC_CFG_HWUNIT1_BUFFER_AMP			(STD_ON)							/* Buffer Amplifie								*/
#define ADC_CFG_HWUNIT1_TH0					(STD_OFF)							/* ADC_CH00										*/
#define ADC_CFG_HWUNIT1_TH1					(STD_OFF)							/* ADC_CH01										*/
#define ADC_CFG_HWUNIT1_TH2					(STD_OFF)							/* ADC_CH02										*/
#define ADC_CFG_HWUNIT1_TH3					(STD_OFF)							/* ADC_CH03										*/
#define ADC_CFG_HWUNIT1_TH4					(STD_OFF)							/* U2B only:ADC_CH04							*/
#define ADC_CFG_HWUNIT1_TH5					(STD_OFF)							/* U2B only:ADC_CH05							*/

/* HW Unit 2						*/
#define ADC_CFG_HWUNIT2_SUSPEND_METHOD		(ADC_SUSPEND_METHOD_SYNC)			/* Suspend Method								*/
#define ADC_CFG_HWUNIT2_RESULT_FORMAT		(ADC_FORMAT_UNSIGNED_INTEGER)		/* Result Format								*/
#define ADC_CFG_HWUNIT2_RESULT_ALIGN		(ADC_ALIGN_RIGHT)					/* Result align									*/
#define ADC_CFG_HWUNIT2_RESOLUTION			(ADC_RESOLUTION_12BIT)				/* Resolution									*/
#define ADC_CFG_HWUNIT2_SAMPLING_PERIOD		(ADC_SAMPLING_PERIOD_18STATES)		/* Sampling Period								*/
#define ADC_CFG_HWUNIT2_BUFFER_AMP			(STD_ON)							/* Buffer Amplifie								*/

/*--------------------------------------------------------------------------------------*/
/*  	Conversion Group Setting														*/
/*--------------------------------------------------------------------------------------*/
#define ADC_CFG_GRP_SIZE					(3U)								/* The total number of groups					*/
/*------------------------------------------------------*/
/* Group00												*/
/*------------------------------------------------------*/
#define ADC_GR_0							(ADC_GRP00)							/* ID (ADC_GRPxx not changed)					*/
#define ADC_CFG_GRP00_HWUNIT				(ADC_HWUNIT0)						/* HW Unit										*/
#define ADC_CFG_GRP00_SG					(ADC_SG0)							/* Scan Group									*/
#define ADC_CFG_GRP00_CNV_CH_SIZE			(8U)								/* Total number of conversion channels			*/
#define ADC_CFG_GRP00_CNV_CH				{ADC_CH00,ADC_CH01,ADC_CH06,ADC_CH07,ADC_CH08,	\
											 ADC_CH17,ADC_CH18,ADC_CH19}			/* Conversion channels							*/
#define ADC_CFG_GRP00_CNV_MODE				(ADC_CONV_MODE_ONESHOT)				/* Conversion Mode								*/
#define ADC_CFG_GRP00_TRIGG_SRC				(ADC_TRIGG_SRC_SW)					/* Conversion Trigger							*/
#define ADC_CFG_GRP00_USE_CNV_INT			(STD_OFF)							/* Interrupt Use								*/
#define ADC_CFG_GRP00_CNV_NOTIF				(NULL_PTR)							/* Conversion End Notification 					*/
#define ADC_CFG_GRP00_USE_DMA				(STD_OFF)							/* DMA Use										*/
#define ADC_CFG_GRP00_USE_DMA_HALF_INT		(STD_OFF)							/* DMA Half Interrupt Use						*/
#define ADC_CFG_GRP00_DMA_ID				(ADC_DMA_OFF)						/* DMA ID										*/
#define ADC_CFG_GRP00_ACCESS_MODE			(ADC_ACCESS_MODE_SINGLE)			/* Access mode									*/
#define ADC_CFG_GRP00_STREAMING_NUM			(1U)								/* Number of repeat in streaming access mode.	*/
/* HW Trigger Selection					*/
#define ADC_CFG_GRP00_EDG_DIRECTION			(PIC2_EDG_DIRECT_RISING)			/* HW Trigger effective edge					*/
/* U2A:Unit0/1			U2B:Unit0/1/2/3	*/
#define ADC_CFG_GRP00_TAUD0					(STD_OFF)							/* TAUD0 interrupt signal(s)					*/
#define ADC_CFG_GRP00_TAUD1					(STD_OFF)							/* TAUD1 interrupt signal(s)					*/
#define ADC_CFG_GRP00_TSG30TG0				(STD_OFF)							/* TSG30ADTRG0 signal of TSG30					*/
#define ADC_CFG_GRP00_TSG30TG1				(STD_OFF)							/* TSG30ADTRG1 signal of TSG30					*/
/* U2A:Unit0/1			U2B:None		*/
#define ADC_CFG_GRP00_TAUJ0_CH3				(STD_OFF)							/* TAUJ0 CH3 interrupt signal(s)				*/
#define ADC_CFG_GRP00_TAUJ1_CH3				(STD_OFF)							/* TAUJ1 CH3 interrupt signal(s)				*/
/* U2A:None				U2B:Unit0/1/2/3	*/
#define ADC_CFG_GRP00_TAUD2					(STD_OFF)							/* TAUD2 interrupt signal(s)					*/
#define ADC_CFG_GRP00_TAUD3					(STD_OFF)							/* TAUD3 interrupt signal(s)					*/
#define ADC_CFG_GRP00_E3S0AD				(STD_OFF)							/* EMU30S channel 0 ADTRG						*/
#define ADC_CFG_GRP00_E3S0AD1				(STD_OFF)							/* EMU30S channel 0 ADTRG1						*/
/* U2A:Unit2			U2B:UnitA		*/
#define ADC_CFG_GRP00_TAUD2_CH7				(STD_OFF)							/* TAUD2 CH7  interrupt signal					*/
#define ADC_CFG_GRP00_TAUD2_CH15			(STD_OFF)							/* TAUD2 CH15 interrupt signal					*/
#define ADC_CFG_GRP00_TAUJ2_CH3				(STD_OFF)							/* TAUJ2 CH3  interrupt signal					*/
#define ADC_CFG_GRP00_TAUJ3_CH3				(STD_OFF)							/* TAUJ3 CH3  interrupt signal					*/

/*------------------------------------------------------*/
/* Group01												*/
/*------------------------------------------------------*/
#define ADC_GR_1							(ADC_GRP01)							/* ID (ADC_GRPxx not changed)					*/
#define ADC_CFG_GRP01_HWUNIT				(ADC_HWUNIT1)						/* HW Unit										*/
#define ADC_CFG_GRP01_SG					(ADC_SG0)							/* Scan Group									*/
#define ADC_CFG_GRP01_CNV_CH_SIZE			(17U)								/* Total number of conversion channels			*/
#define ADC_CFG_GRP01_CNV_CH				{ADC_CH00,ADC_CH01,ADC_CH02,ADC_CH03,ADC_CH04,	\
											 ADC_CH05,ADC_CH06,ADC_CH07,ADC_CH08,ADC_CH09,	\
											 ADC_CH10,ADC_CH11,ADC_CH12,ADC_CH13,ADC_CH14,	\
											 ADC_CH15,ADC_CH17}					/* Conversion channels							*/
#define ADC_CFG_GRP01_CNV_MODE				(ADC_CONV_MODE_ONESHOT)				/* Conversion Mode								*/
#define ADC_CFG_GRP01_TRIGG_SRC				(ADC_TRIGG_SRC_SW)					/* Conversion Trigger							*/
#define ADC_CFG_GRP01_USE_CNV_INT			(STD_OFF)							/* Interrupt Use								*/
#define ADC_CFG_GRP01_CNV_NOTIF				(NULL_PTR)							/* Conversion End Notification 					*/
#define ADC_CFG_GRP01_USE_DMA				(STD_OFF)							/* DMA Use										*/
#define ADC_CFG_GRP01_USE_DMA_HALF_INT		(STD_OFF)							/* DMA Half Interrupt Use						*/
#define ADC_CFG_GRP01_DMA_ID				(ADC_DMA_OFF)						/* DMA ID										*/
#define ADC_CFG_GRP01_ACCESS_MODE			(ADC_ACCESS_MODE_SINGLE)			/* Access mode									*/
#define ADC_CFG_GRP01_STREAMING_NUM			(1U)								/* Number of repeat in streaming access mode.	*/
/* HW Trigger Selection					*/
#define ADC_CFG_GRP01_EDG_DIRECTION			(PIC2_EDG_DIRECT_RISING)			/* HW Trigger effective edge					*/
/* U2A:Unit0/1			U2B:Unit0/1/2/3	*/
#define ADC_CFG_GRP01_TAUD0					(STD_OFF)							/* TAUD0 interrupt signal(s)					*/
#define ADC_CFG_GRP01_TAUD1					(STD_OFF)							/* TAUD1 interrupt signal(s)					*/
#define ADC_CFG_GRP01_TSG30TG0				(STD_OFF)							/* TSG30ADTRG0 signal of TSG30					*/
#define ADC_CFG_GRP01_TSG30TG1				(STD_OFF)							/* TSG30ADTRG1 signal of TSG30					*/
/* U2A:Unit0/1			U2B:None		*/
#define ADC_CFG_GRP01_TAUJ0_CH3				(STD_OFF)							/* TAUJ0 CH3 interrupt signal(s)				*/
#define ADC_CFG_GRP01_TAUJ1_CH3				(STD_OFF)							/* TAUJ1 CH3 interrupt signal(s)				*/
/* U2A:None				U2B:Unit0/1/2/3	*/
#define ADC_CFG_GRP01_TAUD2					(STD_OFF)							/* TAUD2 interrupt signal(s)					*/
#define ADC_CFG_GRP01_TAUD3					(STD_OFF)							/* TAUD3 interrupt signal(s)					*/
#define ADC_CFG_GRP01_E3S0AD				(STD_OFF)							/* EMU30S channel 0 ADTRG						*/
#define ADC_CFG_GRP01_E3S0AD1				(STD_OFF)							/* EMU30S channel 0 ADTRG1						*/
/* U2A:Unit2			U2B:UnitA		*/
#define ADC_CFG_GRP01_TAUD2_CH7				(STD_OFF)							/* TAUD2 CH7  interrupt signal					*/
#define ADC_CFG_GRP01_TAUD2_CH15			(STD_OFF)							/* TAUD2 CH15 interrupt signal					*/
#define ADC_CFG_GRP01_TAUJ2_CH3				(STD_OFF)							/* TAUJ2 CH3  interrupt signal					*/
#define ADC_CFG_GRP01_TAUJ3_CH3				(STD_OFF)							/* TAUJ3 CH3  interrupt signal					*/

/*------------------------------------------------------*/
/* Group02												*/
/*------------------------------------------------------*/
#define ADC_GR_2							(ADC_GRP02)							/* ID (ADC_GRPxx not changed)					*/
#define ADC_CFG_GRP02_HWUNIT				(ADC_HWUNIT2)						/* HW Unit										*/
#define ADC_CFG_GRP02_SG					(ADC_SG0)							/* Scan Group									*/
#define ADC_CFG_GRP02_CNV_CH_SIZE			(2U)								/* Total number of conversion channels			*/
#define ADC_CFG_GRP02_CNV_CH				{ADC_CH03,ADC_CH04}					/* Conversion channels							*/
#define ADC_CFG_GRP02_CNV_MODE				(ADC_CONV_MODE_ONESHOT)				/* Conversion Mode								*/
#define ADC_CFG_GRP02_TRIGG_SRC				(ADC_TRIGG_SRC_SW)					/* Conversion Trigger							*/
#define ADC_CFG_GRP02_USE_CNV_INT			(STD_OFF)							/* Interrupt Use								*/
#define ADC_CFG_GRP02_CNV_NOTIF				(NULL_PTR)							/* Conversion End Notification 					*/
#define ADC_CFG_GRP02_USE_DMA				(STD_OFF)							/* DMA Use										*/
#define ADC_CFG_GRP02_USE_DMA_HALF_INT		(STD_OFF)							/* DMA Half Interrupt Use						*/
#define ADC_CFG_GRP02_DMA_ID				(ADC_DMA_OFF)						/* DMA ID										*/
#define ADC_CFG_GRP02_ACCESS_MODE			(ADC_ACCESS_MODE_SINGLE)			/* Access mode									*/
#define ADC_CFG_GRP02_STREAMING_NUM			(1U)								/* Number of repeat in streaming access mode.	*/
/* HW Trigger Selection					*/
#define ADC_CFG_GRP02_EDG_DIRECTION			(PIC2_EDG_DIRECT_RISING)			/* HW Trigger effective edge					*/
/* U2A:Unit0/1			U2B:Unit0/1/2/3	*/
#define ADC_CFG_GRP02_TAUD0					(STD_OFF)							/* TAUD0 interrupt signal(s)					*/
#define ADC_CFG_GRP02_TAUD1					(STD_OFF)							/* TAUD1 interrupt signal(s)					*/
#define ADC_CFG_GRP02_TSG30TG0				(STD_OFF)							/* TSG30ADTRG0 signal of TSG30					*/
#define ADC_CFG_GRP02_TSG30TG1				(STD_OFF)							/* TSG30ADTRG1 signal of TSG30					*/
/* U2A:Unit0/1			U2B:None		*/
#define ADC_CFG_GRP02_TAUJ0_CH3				(STD_OFF)							/* TAUJ0 CH3 interrupt signal(s)				*/
#define ADC_CFG_GRP02_TAUJ1_CH3				(STD_OFF)							/* TAUJ1 CH3 interrupt signal(s)				*/
/* U2A:None				U2B:Unit0/1/2/3	*/
#define ADC_CFG_GRP02_TAUD2					(STD_OFF)							/* TAUD2 interrupt signal(s)					*/
#define ADC_CFG_GRP02_TAUD3					(STD_OFF)							/* TAUD3 interrupt signal(s)					*/
#define ADC_CFG_GRP02_E3S0AD				(STD_OFF)							/* EMU30S channel 0 ADTRG						*/
#define ADC_CFG_GRP02_E3S0AD1				(STD_OFF)							/* EMU30S channel 0 ADTRG1						*/
/* U2A:Unit2			U2B:UnitA		*/
#define ADC_CFG_GRP02_TAUD2_CH7				(STD_OFF)							/* TAUD2 CH7  interrupt signal					*/
#define ADC_CFG_GRP02_TAUD2_CH15			(STD_OFF)							/* TAUD2 CH15 interrupt signal					*/
#define ADC_CFG_GRP02_TAUJ2_CH3				(STD_OFF)							/* TAUJ2 CH3  interrupt signal					*/
#define ADC_CFG_GRP02_TAUJ3_CH3				(STD_OFF)							/* TAUJ3 CH3  interrupt signal					*/

/*--------------------------------------------------------------------------------------*/
/*  	HW Trigger TAUD	Configuration Setting											*/
/*---------------------	----------------------------------------------------------------*/
/* HW Trigger TAUD0 Configuration:	U2A:Unit0/1		U2B:Unit0/1/2/3	*/
#define ADC_CFG_HWTRG_TAUD0_SG0				(PIC2_TAUX_TRG_OFF)
#define ADC_CFG_HWTRG_TAUD0_SG1				(PIC2_TAUX_TRG_OFF)
#define ADC_CFG_HWTRG_TAUD0_SG2				(PIC2_TAUX_TRG_OFF)
#define ADC_CFG_HWTRG_TAUD0_SG3				(PIC2_TAUX_TRG_OFF)
#define ADC_CFG_HWTRG_TAUD0_SG4				(PIC2_TAUX_TRG_OFF)
/* HW Trigger TAUD1 Configuration:	U2A:Unit0/1		U2B:Unit0/1/2/3	*/
#define ADC_CFG_HWTRG_TAUD1_SG0				(PIC2_TAUX_TRG_OFF)
#define ADC_CFG_HWTRG_TAUD1_SG1				(PIC2_TAUX_TRG_OFF)
#define ADC_CFG_HWTRG_TAUD1_SG2				(PIC2_TAUX_TRG_OFF)
#define ADC_CFG_HWTRG_TAUD1_SG3				(PIC2_TAUX_TRG_OFF)
#define ADC_CFG_HWTRG_TAUD1_SG4				(PIC2_TAUX_TRG_OFF)
/* HW Trigger TAUD2 Configuration:	U2A:None		U2B:Unit0/1/2/3	*/
#define ADC_CFG_HWTRG_TAUD2_SG0				(PIC2_TAUX_TRG_OFF)
#define ADC_CFG_HWTRG_TAUD2_SG1				(PIC2_TAUX_TRG_OFF)
#define ADC_CFG_HWTRG_TAUD2_SG2				(PIC2_TAUX_TRG_OFF)
#define ADC_CFG_HWTRG_TAUD2_SG3				(PIC2_TAUX_TRG_OFF)
#define ADC_CFG_HWTRG_TAUD2_SG4				(PIC2_TAUX_TRG_OFF)
/* HW Trigger TAUD3 Configuration:	U2A:None		U2B:Unit0/1/2/3	*/
#define ADC_CFG_HWTRG_TAUD3_SG0				(PIC2_TAUX_TRG_OFF)
#define ADC_CFG_HWTRG_TAUD3_SG1				(PIC2_TAUX_TRG_OFF)
#define ADC_CFG_HWTRG_TAUD3_SG2				(PIC2_TAUX_TRG_OFF)
#define ADC_CFG_HWTRG_TAUD3_SG3				(PIC2_TAUX_TRG_OFF)
#define ADC_CFG_HWTRG_TAUD3_SG4				(PIC2_TAUX_TRG_OFF)

#endif /* ADC_CFG_H */
/*-- End Of File -------------------------------------------------------------------------------*/
