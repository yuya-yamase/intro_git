/* ADCDIAG-r04-303 */
/************************************************************************************************/
/*																								*/
/*		ADC DIAG Driver : User Configuration													*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/
#ifndef ADCDIAG_CFG_H
#define ADCDIAG_CFG_H

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
/*----------------------------------------------------------------------------------------------*/
/*  include callback functions																	*/
/*----------------------------------------------------------------------------------------------*/
extern void AdcDiag_TestNotification(uint8 t_u1HWUnit);
/*==============================================================================================*/
/*	User Configuration																			*/
/*==============================================================================================*/

/*----------------------------------------------------------------------------------------------*/
/*  	General																					*/
/*----------------------------------------------------------------------------------------------*/
#define ADCDIAG_CFG_SELFDIAG_WIRINGBREAK_TIMEOUT     (0xFFFFFFFFU)
#define ADCDIAG_CFG_SELFDIAG_TH_TIMEOUT              (0xFFFFFFFFU)
#define ADCDIAG_CFG_SELFDIAG_TH_VCH0_TIMEOUT         (0xFFFFFFFFU)
#define ADCDIAG_CFG_WIRINGBREAK_TIMEOUT              (0xFFFFFFFFU)
#define ADCDIAG_CFG_PINLEVEL_TIMEOUT                 (0xFFFFFFFFU)
#define ADCDIAG_CFG_ADCORE_TIMEOUT                   (0xFFFFFFFFU)
#define ADCDIAG_CFG_MODULE_RESET_TIMEOUT             (0xFFFFFFFFU)

#define ADCDIAG_CFG_SG_MULTICYCLE               	 (10U)     		/* Value used for SGMCYCRx MCYC, where is the the scan group used by AdcDiag */
#define ADCDIAG_CFG_PULSE_WIDTH_WIRING_BREAK_1  	 (0x14U)   		/* Value used for ODCR.ODPW for wiring break mode 1 */
#define ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR          (STD_ON)		/* Report runtime error use   */

#define	ADCDIAG_CFG_ERR_NOTIF_CAPABILITY			 (STD_ON)		/* Error Notification Use   */
/* Define these macros to control interrupt handler functions */
#define ADCDIAG_CFG_USE_ISR_ADC_HWUNIT0_ERR
#define ADCDIAG_CFG_USE_ISR_ADC_HWUNIT1_ERR
#define ADCDIAG_CFG_USE_ISR_ADC_HWUNIT2_ERR
/*--------------------------------------------------------------------------------------------- */
/*      Hw Units Configuration                                                                  */
/*--------------------------------------------------------------------------------------------- */
/* Define these macros to set which user notification will be used */
#define ADCDIAG_CFG_HW_UNIT0_USER_NOTIFICATION      (AdcDiag_TestNotification)
#define ADCDIAG_CFG_HW_UNIT1_USER_NOTIFICATION      (AdcDiag_TestNotification)
#define ADCDIAG_CFG_HW_UNIT2_USER_NOTIFICATION      (AdcDiag_TestNotification)

/* Define these macros to set which ADC HW Unit will be used */
#define ADCDIAG_CFG_HW_UNIT0_USED                   (TRUE)
#define ADCDIAG_CFG_HW_UNIT1_USED                   (TRUE)
#define ADCDIAG_CFG_HW_UNIT2_USED                   (TRUE)
/*----------------------------------------------------------------------------------------------*/
/*  	Voltage Level Combinations																*/
/*----------------------------------------------------------------------------------------------*/
#define ADCDIAG_CFG_PIN_LVL_VOLTAGE_LEVEL0        		    (ADC_TDCR_TDLV_LEVEL0)
#define ADCDIAG_CFG_PIN_LVL_VOLTAGE_LEVEL1       		    (ADC_TDCR_TDLV_LEVEL1)
#define ADCDIAG_CFG_PIN_LVL_VOLTAGE_LEVEL2       		    (ADC_TDCR_TDLV_LEVEL2)
#define ADCDIAG_CFG_PIN_LVL_VOLTAGE_LEVEL3       		    (ADC_TDCR_TDLV_LEVEL3)
#define ADCDIAG_CFG_TH_VOLTAGE_LEVEL_TOTAL_COMBINATION    	(4U)
/*----------------------------------------------------------------------------------------------*/
/*  	Range Values for Self-Diagnosis T&H														*/
/*----------------------------------------------------------------------------------------------*/
#define ADCDIAG_CFG_TH_MIN_RANGE_VSS								(0x0U)
#define ADCDIAG_CFG_TH_MAX_RANGE_VSS								(0x140U)
#define ADCDIAG_CFG_TH_MIN_RANGE_1_2VCC						    	(0x3EC0U)
#define ADCDIAG_CFG_TH_MAX_RANGE_1_2VCC							    (0x4140U)
#define ADCDIAG_CFG_TH_MIN_RANGE_VCC								(0x7EC0U)
#define ADCDIAG_CFG_TH_MAX_RANGE_VCC								(0x7FF8U)
/*----------------------------------------------------------------------------------------------*/
/*  	Range Values for Self-Diagnosis Wiring Break Detection									*/
/*----------------------------------------------------------------------------------------------*/
#define ADCDIAG_CFG_WIRING_BREAK_MIN_RANGE_VSS						(0x0U)
#define ADCDIAG_CFG_WIRING_BREAK_MAX_RANGE_VSS						(0x320U)
#define ADCDIAG_CFG_WIRING_BREAK_MIN_RANGE_VCC						(0x7A00U)
#define ADCDIAG_CFG_WIRING_BREAK_MAX_RANGE_VCC						(0x7FF8U)
/*----------------------------------------------------------------------------------------------*/
/*  	Conversion Group Setting																*/
/*----------------------------------------------------------------------------------------------*/
#define ADCDIAG_CFG_GRP_SIZE					(65U)			/* The total number of groups	*/
#define ADCDIAG_CFG_MAX_BUFFER_SIZE				(8U)			/* Size for Self-Diagnosis results */

#define ADCDIAG_CFG_GRP00_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 00	*/
#define ADCDIAG_CFG_GRP01_PHYSICAL_CH_NO					(0U)			/* Number of Physical  channel for AdcDiag  group 01	*/
#define ADCDIAG_CFG_GRP02_PHYSICAL_CH_NO					(3U)			/* Number of Physical  channel for AdcDiag  group 02	*/
#define ADCDIAG_CFG_GRP03_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 03	*/
#define ADCDIAG_CFG_GRP04_PHYSICAL_CH_NO					(0U)			/* Number of Physical  channel for AdcDiag  group 04	*/
#define ADCDIAG_CFG_GRP05_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 05	*/
#define ADCDIAG_CFG_GRP06_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 06	*/
#define ADCDIAG_CFG_GRP07_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 07	*/
#define ADCDIAG_CFG_GRP08_PHYSICAL_CH_NO					(4U)			/* Number of Physical  channel for AdcDiag  group 08	*/
#define ADCDIAG_CFG_GRP09_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 09	*/
#define ADCDIAG_CFG_GRP10_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 10	*/
#define ADCDIAG_CFG_GRP11_PHYSICAL_CH_NO					(3U)			/* Number of Physical  channel for AdcDiag  group 11	*/
#define ADCDIAG_CFG_GRP12_PHYSICAL_CH_NO					(4U)			/* Number of Physical  channel for AdcDiag  group 12	*/
#define ADCDIAG_CFG_GRP13_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 13	*/
#define ADCDIAG_CFG_GRP14_PHYSICAL_CH_NO					(3U)			/* Number of Physical  channel for AdcDiag  group 14	*/
#define ADCDIAG_CFG_GRP15_PHYSICAL_CH_NO					(0U)			/* Number of Physical  channel for AdcDiag  group 15	*/
#define ADCDIAG_CFG_GRP16_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 16	*/
#define ADCDIAG_CFG_GRP17_PHYSICAL_CH_NO					(2U)			/* Number of Physical  channel for AdcDiag  group 17	*/
#define ADCDIAG_CFG_GRP18_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 18	*/
#define ADCDIAG_CFG_GRP19_PHYSICAL_CH_NO					(3U)			/* Number of Physical  channel for AdcDiag  group 19	*/
#define ADCDIAG_CFG_GRP20_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 20	*/
#define ADCDIAG_CFG_GRP21_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 21	*/
#define ADCDIAG_CFG_GRP22_PHYSICAL_CH_NO					(2U)			/* Number of Physical  channel for AdcDiag  group 22	*/
#define ADCDIAG_CFG_GRP23_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 23	*/
#define ADCDIAG_CFG_GRP24_PHYSICAL_CH_NO					(0U)			/* Number of Physical  channel for AdcDiag  group 24	*/
#define ADCDIAG_CFG_GRP25_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 25	*/
#define ADCDIAG_CFG_GRP26_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 26	*/
#define ADCDIAG_CFG_GRP27_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 27	*/
#define ADCDIAG_CFG_GRP28_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 28	*/
#define ADCDIAG_CFG_GRP29_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 29	*/
#define ADCDIAG_CFG_GRP30_PHYSICAL_CH_NO					(0U)			/* Number of Physical  channel for AdcDiag  group 30	*/
#define ADCDIAG_CFG_GRP31_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 31	*/
#define ADCDIAG_CFG_GRP32_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 32	*/
#define ADCDIAG_CFG_GRP33_PHYSICAL_CH_NO					(3U)			/* Number of Physical  channel for AdcDiag  group 33	*/
#define ADCDIAG_CFG_GRP34_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 34	*/
#define ADCDIAG_CFG_GRP35_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 35	*/
#define ADCDIAG_CFG_GRP36_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 36	*/
#define ADCDIAG_CFG_GRP37_PHYSICAL_CH_NO					(2U)			/* Number of Physical  channel for AdcDiag  group 37	*/
#define ADCDIAG_CFG_GRP38_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 38	*/
#define ADCDIAG_CFG_GRP39_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 39	*/
#define ADCDIAG_CFG_GRP40_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 40	*/
#define ADCDIAG_CFG_GRP41_PHYSICAL_CH_NO					(3U)			/* Number of Physical  channel for AdcDiag  group 41	*/
#define ADCDIAG_CFG_GRP42_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 42	*/
#define ADCDIAG_CFG_GRP43_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 43	*/
#define ADCDIAG_CFG_GRP44_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 44	*/
#define ADCDIAG_CFG_GRP45_PHYSICAL_CH_NO					(0U)			/* Number of Physical  channel for AdcDiag  group 45	*/
#define ADCDIAG_CFG_GRP46_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 46	*/
#define ADCDIAG_CFG_GRP47_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 47	*/
#define ADCDIAG_CFG_GRP48_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 48	*/
#define ADCDIAG_CFG_GRP49_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 49	*/
#define ADCDIAG_CFG_GRP50_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 50	*/
#define ADCDIAG_CFG_GRP51_PHYSICAL_CH_NO					(0U)			/* Number of Physical  channel for AdcDiag  group 51	*/
#define ADCDIAG_CFG_GRP52_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 52	*/
#define ADCDIAG_CFG_GRP53_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 53	*/
#define ADCDIAG_CFG_GRP54_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 54	*/
#define ADCDIAG_CFG_GRP55_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 55	*/
#define ADCDIAG_CFG_GRP56_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 56	*/
#define ADCDIAG_CFG_GRP57_PHYSICAL_CH_NO					(0U)			/* Number of Physical  channel for AdcDiag  group 57	*/
#define ADCDIAG_CFG_GRP58_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 58	*/
#define ADCDIAG_CFG_GRP59_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 59	*/
#define ADCDIAG_CFG_GRP60_PHYSICAL_CH_NO					(0U)			/* Number of Physical  channel for AdcDiag  group 60	*/
#define ADCDIAG_CFG_GRP61_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 61	*/
#define ADCDIAG_CFG_GRP62_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 62	*/
#define ADCDIAG_CFG_GRP63_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 63	*/
#define ADCDIAG_CFG_GRP64_PHYSICAL_CH_NO					(1U)			/* Number of Physical  channel for AdcDiag  group 64	*/

#define ADCDIAG_CFG_GRP00_ID					(0U)					    	                /* ID */
#define ADCDIAG_CFG_GRP00_HWUNIT				(ADC_HWUNIT0)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP00_SG					(ADC_SG1)						                /* Scan Group */
#define ADCDIAG_CFG_GRP00_CNV_CH				{ADC_VCR_GCTRL_AN000}		/* Conversion channels */
#define ADCDIAG_CFG_GRP00_START_POINTER		    (1U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP00_STOP_POINTER			(1U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP00_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE1)          /* Wiring-Break Detection Mode 1 */

#define ADCDIAG_CFG_GRP01_ID					(1U)					    	                /* ID */
#define ADCDIAG_CFG_GRP01_HWUNIT				(ADC_HWUNIT1)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP01_SG					(ADC_SG2)						                /* Scan Group */
#define ADCDIAG_CFG_GRP01_CNV_CH				{}		/* Conversion channels */
#define ADCDIAG_CFG_GRP01_START_POINTER		    (2U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP01_STOP_POINTER			(3U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP01_DIAG_TYPE			    (ADCDIAG_AD_CORE_SELF_DIAG)          /* Self-Diag ADcore */

#define ADCDIAG_CFG_GRP02_ID					(2U)					    	                /* ID */
#define ADCDIAG_CFG_GRP02_HWUNIT				(ADC_HWUNIT1)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP02_SG					(ADC_SG0)						                /* Scan Group */
#define ADCDIAG_CFG_GRP02_CNV_CH				{ADC_VCR_GCTRL_AN100,ADC_VCR_GCTRL_AN101,ADC_VCR_GCTRL_AN102}		/* Conversion channels */
#define ADCDIAG_CFG_GRP02_START_POINTER		    (0U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP02_STOP_POINTER			(2U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP02_DIAG_TYPE			    (ADCDIAG_PIN_LEVEL)          /* Pin-Level Self-Diag */

#define ADCDIAG_CFG_GRP03_ID					(3U)					    	                /* ID */
#define ADCDIAG_CFG_GRP03_HWUNIT				(ADC_HWUNIT0)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP03_SG					(ADC_SG3)						                /* Scan Group */
#define ADCDIAG_CFG_GRP03_CNV_CH				{ADC_VCR_GCTRL_AN001}		/* Conversion channels */
#define ADCDIAG_CFG_GRP03_START_POINTER		    (3U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP03_STOP_POINTER			(3U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP03_DIAG_TYPE			    (ADCDIAG_SELF_DIAG_WIRING_BREAK_DETECTION_MODE1)          /*  Self-Diag Wiring-Break Detection Mode 1 */

#define ADCDIAG_CFG_GRP04_ID					(4U)					    	                /* ID */
#define ADCDIAG_CFG_GRP04_HWUNIT				(ADC_HWUNIT2)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP04_SG					(ADC_SG3)						                /* Scan Group */
#define ADCDIAG_CFG_GRP04_CNV_CH				{}		/* Conversion channels */
#define ADCDIAG_CFG_GRP04_START_POINTER		    (1U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP04_STOP_POINTER			(3U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP04_DIAG_TYPE			    (ADCDIAG_AD_CORE_SELF_DIAG)          /* Self-Diag ADcore */

#define ADCDIAG_CFG_GRP05_ID					(5U)					    	                /* ID */
#define ADCDIAG_CFG_GRP05_HWUNIT				(ADC_HWUNIT0)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP05_SG					(ADC_SG4)						                /* Scan Group */
#define ADCDIAG_CFG_GRP05_CNV_CH				{ADC_VCR_GCTRL_AN061}		/* Conversion channels */
#define ADCDIAG_CFG_GRP05_START_POINTER		    (4U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP05_STOP_POINTER			(5U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP05_DIAG_TYPE			    (ADCDIAG_SELF_DIAG_WIRING_BREAK_DETECTION_MODE2)          /*  Self-Diag Wiring-Break Detection Mode 2 */

#define ADCDIAG_CFG_GRP06_ID					(6U)					    	                /* ID */
#define ADCDIAG_CFG_GRP06_HWUNIT				(ADC_HWUNIT2)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP06_SG					(ADC_SG4)						                /* Scan Group */
#define ADCDIAG_CFG_GRP06_CNV_CH				{ADC_VCR_GCTRL_AN200}		/* Conversion channels */
#define ADCDIAG_CFG_GRP06_START_POINTER		    (3U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP06_STOP_POINTER			(4U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP06_DIAG_TYPE			    (ADCDIAG_SELF_DIAG_WIRING_BREAK_DETECTION_MODE2)          /*  Self-Diag Wiring-Break Detection Mode 2 */

#define ADCDIAG_CFG_GRP07_ID					(7U)					    	                /* ID */
#define ADCDIAG_CFG_GRP07_HWUNIT				(ADC_HWUNIT2)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP07_SG					(ADC_SG2)						                /* Scan Group */
#define ADCDIAG_CFG_GRP07_CNV_CH				{ADC_VCR_GCTRL_AN201}		/* Conversion channels */
#define ADCDIAG_CFG_GRP07_START_POINTER		    (1U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP07_STOP_POINTER			(1U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP07_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE2)          /* Wiring-Break Detection Mode 2 */

#define ADCDIAG_CFG_GRP08_ID					(8U)					    	                /* ID */
#define ADCDIAG_CFG_GRP08_HWUNIT				(ADC_HWUNIT0)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP08_SG					(ADC_SG1)						                /* Scan Group */
#define ADCDIAG_CFG_GRP08_CNV_CH				{ADC_VCR_GCTRL_AN000,ADC_VCR_GCTRL_AN001,ADC_VCR_GCTRL_AN002,ADC_VCR_GCTRL_AN003}		/* Conversion channels */
#define ADCDIAG_CFG_GRP08_START_POINTER		    (0U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP08_STOP_POINTER			(9U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP08_DIAG_TYPE			    (ADCDIAG_SELF_DIAG_TH)          /* Self-Diag T&H */

#define ADCDIAG_CFG_GRP09_ID					(9U)					    	                /* ID */
#define ADCDIAG_CFG_GRP09_HWUNIT				(ADC_HWUNIT0)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP09_SG					(ADC_SG2)						                /* Scan Group */
#define ADCDIAG_CFG_GRP09_CNV_CH				{ADC_VCR_GCTRL_AN060}		/* Conversion channels */
#define ADCDIAG_CFG_GRP09_START_POINTER		    (4U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP09_STOP_POINTER			(4U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP09_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE2)          /* Wiring-Break Detection Mode 2 */

#define ADCDIAG_CFG_GRP10_ID					(10U)					    	                /* ID */
#define ADCDIAG_CFG_GRP10_HWUNIT				(ADC_HWUNIT1)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP10_SG					(ADC_SG2)						                /* Scan Group */
#define ADCDIAG_CFG_GRP10_CNV_CH				{ADC_VCR_GCTRL_AN100}		/* Conversion channels */
#define ADCDIAG_CFG_GRP10_START_POINTER		    (2U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP10_STOP_POINTER			(2U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP10_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE2)          /* Wiring-Break Detection Mode 2 */

#define ADCDIAG_CFG_GRP11_ID					(11U)					    	                /* ID */
#define ADCDIAG_CFG_GRP11_HWUNIT				(ADC_HWUNIT2)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP11_SG					(ADC_SG0)						                /* Scan Group */
#define ADCDIAG_CFG_GRP11_CNV_CH				{ADC_VCR_GCTRL_AN201,ADC_VCR_GCTRL_AN202,ADC_VCR_GCTRL_AN262}		/* Conversion channels */
#define ADCDIAG_CFG_GRP11_START_POINTER		    (9U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP11_STOP_POINTER			(11U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP11_DIAG_TYPE			    (ADCDIAG_PIN_LEVEL)          /* Pin-Level Self-Diag */

#define ADCDIAG_CFG_GRP12_ID					(12U)					    	                /* ID */
#define ADCDIAG_CFG_GRP12_HWUNIT				(ADC_HWUNIT1)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP12_SG					(ADC_SG1)						                /* Scan Group */
#define ADCDIAG_CFG_GRP12_CNV_CH				{ADC_VCR_GCTRL_AN100,ADC_VCR_GCTRL_AN101,ADC_VCR_GCTRL_AN102,ADC_VCR_GCTRL_AN103}		/* Conversion channels */
#define ADCDIAG_CFG_GRP12_START_POINTER		    (0U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP12_STOP_POINTER			(9U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP12_DIAG_TYPE			    (ADCDIAG_SELF_DIAG_TH)          /* Self-Diag T&H */

#define ADCDIAG_CFG_GRP13_ID					(13U)					    	                /* ID */
#define ADCDIAG_CFG_GRP13_HWUNIT				(ADC_HWUNIT0)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP13_SG					(ADC_SG1)						                /* Scan Group */
#define ADCDIAG_CFG_GRP13_CNV_CH				{ADC_VCR_GCTRL_AN061}		/* Conversion channels */
#define ADCDIAG_CFG_GRP13_START_POINTER		    (3U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP13_STOP_POINTER			(3U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP13_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE1)          /* Wiring-Break Detection Mode 1 */

#define ADCDIAG_CFG_GRP14_ID					(14U)					    	                /* ID */
#define ADCDIAG_CFG_GRP14_HWUNIT				(ADC_HWUNIT0)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP14_SG					(ADC_SG0)						                /* Scan Group */
#define ADCDIAG_CFG_GRP14_CNV_CH				{ADC_VCR_GCTRL_AN001,ADC_VCR_GCTRL_AN002,ADC_VCR_GCTRL_AN062}		/* Conversion channels */
#define ADCDIAG_CFG_GRP14_START_POINTER		    (9U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP14_STOP_POINTER			(11U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP14_DIAG_TYPE			    (ADCDIAG_PIN_LEVEL)          /* Pin-Level Self-Diag */

#define ADCDIAG_CFG_GRP15_ID					(15U)					    	                /* ID */
#define ADCDIAG_CFG_GRP15_HWUNIT				(ADC_HWUNIT0)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP15_SG					(ADC_SG2)						                /* Scan Group */
#define ADCDIAG_CFG_GRP15_CNV_CH				{}		/* Conversion channels */
#define ADCDIAG_CFG_GRP15_START_POINTER		    (2U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP15_STOP_POINTER			(5U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP15_DIAG_TYPE			    (ADCDIAG_AD_CORE_SELF_DIAG)          /* Self-Diag ADcore */

#define ADCDIAG_CFG_GRP16_ID					(16U)					    	                /* ID */
#define ADCDIAG_CFG_GRP16_HWUNIT				(ADC_HWUNIT1)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP16_SG					(ADC_SG3)						                /* Scan Group */
#define ADCDIAG_CFG_GRP16_CNV_CH				{ADC_VCR_GCTRL_AN160}		/* Conversion channels */
#define ADCDIAG_CFG_GRP16_START_POINTER		    (3U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP16_STOP_POINTER			(3U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP16_DIAG_TYPE			    (ADCDIAG_SELF_DIAG_WIRING_BREAK_DETECTION_MODE1)          /*  Self-Diag Wiring-Break Detection Mode 1 */

#define ADCDIAG_CFG_GRP17_ID					(17U)					    	                /* ID */
#define ADCDIAG_CFG_GRP17_HWUNIT				(ADC_HWUNIT1)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP17_SG					(ADC_SG0)						                /* Scan Group */
#define ADCDIAG_CFG_GRP17_CNV_CH				{ADC_VCR_GCTRL_AN160,ADC_VCR_GCTRL_AN161}		/* Conversion channels */
#define ADCDIAG_CFG_GRP17_START_POINTER		    (1U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP17_STOP_POINTER			(2U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP17_DIAG_TYPE			    (ADCDIAG_PIN_LEVEL)          /* Pin-Level Self-Diag */

#define ADCDIAG_CFG_GRP18_ID					(18U)					    	                /* ID */
#define ADCDIAG_CFG_GRP18_HWUNIT				(ADC_HWUNIT2)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP18_SG					(ADC_SG2)						                /* Scan Group */
#define ADCDIAG_CFG_GRP18_CNV_CH				{ADC_VCR_GCTRL_AN260}		/* Conversion channels */
#define ADCDIAG_CFG_GRP18_START_POINTER		    (3U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP18_STOP_POINTER			(3U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP18_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE2)          /* Wiring-Break Detection Mode 2 */

#define ADCDIAG_CFG_GRP19_ID					(19U)					    	                /* ID */
#define ADCDIAG_CFG_GRP19_HWUNIT				(ADC_HWUNIT1)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP19_SG					(ADC_SG0)						                /* Scan Group */
#define ADCDIAG_CFG_GRP19_CNV_CH				{ADC_VCR_GCTRL_AN101,ADC_VCR_GCTRL_AN102,ADC_VCR_GCTRL_AN162}		/* Conversion channels */
#define ADCDIAG_CFG_GRP19_START_POINTER		    (9U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP19_STOP_POINTER			(11U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP19_DIAG_TYPE			    (ADCDIAG_PIN_LEVEL)          /* Pin-Level Self-Diag */

#define ADCDIAG_CFG_GRP20_ID					(20U)					    	                /* ID */
#define ADCDIAG_CFG_GRP20_HWUNIT				(ADC_HWUNIT2)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP20_SG					(ADC_SG1)						                /* Scan Group */
#define ADCDIAG_CFG_GRP20_CNV_CH				{ADC_VCR_GCTRL_AN201}		/* Conversion channels */
#define ADCDIAG_CFG_GRP20_START_POINTER		    (1U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP20_STOP_POINTER			(1U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP20_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE1)          /* Wiring-Break Detection Mode 1 */

#define ADCDIAG_CFG_GRP21_ID					(21U)					    	                /* ID */
#define ADCDIAG_CFG_GRP21_HWUNIT				(ADC_HWUNIT2)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP21_SG					(ADC_SG3)						                /* Scan Group */
#define ADCDIAG_CFG_GRP21_CNV_CH				{ADC_VCR_GCTRL_AN260}		/* Conversion channels */
#define ADCDIAG_CFG_GRP21_START_POINTER		    (3U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP21_STOP_POINTER			(3U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP21_DIAG_TYPE			    (ADCDIAG_SELF_DIAG_WIRING_BREAK_DETECTION_MODE1)          /*  Self-Diag Wiring-Break Detection Mode 1 */

#define ADCDIAG_CFG_GRP22_ID					(22U)					    	                /* ID */
#define ADCDIAG_CFG_GRP22_HWUNIT				(ADC_HWUNIT0)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP22_SG					(ADC_SG0)						                /* Scan Group */
#define ADCDIAG_CFG_GRP22_CNV_CH				{ADC_VCR_GCTRL_AN060,ADC_VCR_GCTRL_AN061}		/* Conversion channels */
#define ADCDIAG_CFG_GRP22_START_POINTER		    (4U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP22_STOP_POINTER			(5U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP22_DIAG_TYPE			    (ADCDIAG_PIN_LEVEL)          /* Pin-Level Self-Diag */

#define ADCDIAG_CFG_GRP23_ID					(23U)					    	                /* ID */
#define ADCDIAG_CFG_GRP23_HWUNIT				(ADC_HWUNIT1)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP23_SG					(ADC_SG2)						                /* Scan Group */
#define ADCDIAG_CFG_GRP23_CNV_CH				{ADC_VCR_GCTRL_AN160}		/* Conversion channels */
#define ADCDIAG_CFG_GRP23_START_POINTER		    (4U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP23_STOP_POINTER			(4U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP23_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE2)          /* Wiring-Break Detection Mode 2 */

#define ADCDIAG_CFG_GRP24_ID					(24U)					    	                /* ID */
#define ADCDIAG_CFG_GRP24_HWUNIT				(ADC_HWUNIT0)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP24_SG					(ADC_SG1)						                /* Scan Group */
#define ADCDIAG_CFG_GRP24_CNV_CH				{}		/* Conversion channels */
#define ADCDIAG_CFG_GRP24_START_POINTER		    (2U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP24_STOP_POINTER			(3U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP24_DIAG_TYPE			    (ADCDIAG_AD_CORE_SELF_DIAG)          /* Self-Diag ADcore */

#define ADCDIAG_CFG_GRP25_ID					(25U)					    	                /* ID */
#define ADCDIAG_CFG_GRP25_HWUNIT				(ADC_HWUNIT1)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP25_SG					(ADC_SG1)						                /* Scan Group */
#define ADCDIAG_CFG_GRP25_CNV_CH				{ADC_VCR_GCTRL_AN161}		/* Conversion channels */
#define ADCDIAG_CFG_GRP25_START_POINTER		    (3U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP25_STOP_POINTER			(3U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP25_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE1)          /* Wiring-Break Detection Mode 1 */

#define ADCDIAG_CFG_GRP26_ID					(26U)					    	                /* ID */
#define ADCDIAG_CFG_GRP26_HWUNIT				(ADC_HWUNIT0)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP26_SG					(ADC_SG4)						                /* Scan Group */
#define ADCDIAG_CFG_GRP26_CNV_CH				{ADC_VCR_GCTRL_AN001}		/* Conversion channels */
#define ADCDIAG_CFG_GRP26_START_POINTER		    (0U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP26_STOP_POINTER			(0U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP26_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE2)          /* Wiring-Break Detection Mode 2 */

#define ADCDIAG_CFG_GRP27_ID					(27U)					    	                /* ID */
#define ADCDIAG_CFG_GRP27_HWUNIT				(ADC_HWUNIT2)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP27_SG					(ADC_SG1)						                /* Scan Group */
#define ADCDIAG_CFG_GRP27_CNV_CH				{ADC_VCR_GCTRL_AN260}		/* Conversion channels */
#define ADCDIAG_CFG_GRP27_START_POINTER		    (3U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP27_STOP_POINTER			(3U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP27_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE1)          /* Wiring-Break Detection Mode 1 */

#define ADCDIAG_CFG_GRP28_ID					(28U)					    	                /* ID */
#define ADCDIAG_CFG_GRP28_HWUNIT				(ADC_HWUNIT2)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP28_SG					(ADC_SG4)						                /* Scan Group */
#define ADCDIAG_CFG_GRP28_CNV_CH				{ADC_VCR_GCTRL_AN260}		/* Conversion channels */
#define ADCDIAG_CFG_GRP28_START_POINTER		    (4U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP28_STOP_POINTER			(5U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP28_DIAG_TYPE			    (ADCDIAG_SELF_DIAG_WIRING_BREAK_DETECTION_MODE2)          /*  Self-Diag Wiring-Break Detection Mode 2 */

#define ADCDIAG_CFG_GRP29_ID					(29U)					    	                /* ID */
#define ADCDIAG_CFG_GRP29_HWUNIT				(ADC_HWUNIT2)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP29_SG					(ADC_SG4)						                /* Scan Group */
#define ADCDIAG_CFG_GRP29_CNV_CH				{ADC_VCR_GCTRL_AN263}		/* Conversion channels */
#define ADCDIAG_CFG_GRP29_START_POINTER		    (3U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP29_STOP_POINTER			(3U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP29_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE2)          /* Wiring-Break Detection Mode 2 */

#define ADCDIAG_CFG_GRP30_ID					(30U)					    	                /* ID */
#define ADCDIAG_CFG_GRP30_HWUNIT				(ADC_HWUNIT2)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP30_SG					(ADC_SG3)						                /* Scan Group */
#define ADCDIAG_CFG_GRP30_CNV_CH				{}		/* Conversion channels */
#define ADCDIAG_CFG_GRP30_START_POINTER		    (2U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP30_STOP_POINTER			(2U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP30_DIAG_TYPE			    (ADCDIAG_AD_CORE_SELF_DIAG)          /* Self-Diag ADcore */

#define ADCDIAG_CFG_GRP31_ID					(31U)					    	                /* ID */
#define ADCDIAG_CFG_GRP31_HWUNIT				(ADC_HWUNIT1)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP31_SG					(ADC_SG4)						                /* Scan Group */
#define ADCDIAG_CFG_GRP31_CNV_CH				{ADC_VCR_GCTRL_AN161}		/* Conversion channels */
#define ADCDIAG_CFG_GRP31_START_POINTER		    (4U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP31_STOP_POINTER			(5U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP31_DIAG_TYPE			    (ADCDIAG_SELF_DIAG_WIRING_BREAK_DETECTION_MODE2)          /*  Self-Diag Wiring-Break Detection Mode 2 */

#define ADCDIAG_CFG_GRP32_ID					(32U)					    	                /* ID */
#define ADCDIAG_CFG_GRP32_HWUNIT				(ADC_HWUNIT0)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP32_SG					(ADC_SG3)						                /* Scan Group */
#define ADCDIAG_CFG_GRP32_CNV_CH				{ADC_VCR_GCTRL_AN060}		/* Conversion channels */
#define ADCDIAG_CFG_GRP32_START_POINTER		    (3U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP32_STOP_POINTER			(3U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP32_DIAG_TYPE			    (ADCDIAG_SELF_DIAG_WIRING_BREAK_DETECTION_MODE1)          /*  Self-Diag Wiring-Break Detection Mode 1 */

#define ADCDIAG_CFG_GRP33_ID					(33U)					    	                /* ID */
#define ADCDIAG_CFG_GRP33_HWUNIT				(ADC_HWUNIT0)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP33_SG					(ADC_SG0)						                /* Scan Group */
#define ADCDIAG_CFG_GRP33_CNV_CH				{ADC_VCR_GCTRL_AN000,ADC_VCR_GCTRL_AN001,ADC_VCR_GCTRL_AN002}		/* Conversion channels */
#define ADCDIAG_CFG_GRP33_START_POINTER		    (1U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP33_STOP_POINTER			(3U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP33_DIAG_TYPE			    (ADCDIAG_PIN_LEVEL)          /* Pin-Level Self-Diag */

#define ADCDIAG_CFG_GRP34_ID					(34U)					    	                /* ID */
#define ADCDIAG_CFG_GRP34_HWUNIT				(ADC_HWUNIT0)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP34_SG					(ADC_SG2)						                /* Scan Group */
#define ADCDIAG_CFG_GRP34_CNV_CH				{ADC_VCR_GCTRL_AN073}		/* Conversion channels */
#define ADCDIAG_CFG_GRP34_START_POINTER		    (1U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP34_STOP_POINTER			(1U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP34_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE2)          /* Wiring-Break Detection Mode 2 */

#define ADCDIAG_CFG_GRP35_ID					(35U)					    	                /* ID */
#define ADCDIAG_CFG_GRP35_HWUNIT				(ADC_HWUNIT1)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP35_SG					(ADC_SG2)						                /* Scan Group */
#define ADCDIAG_CFG_GRP35_CNV_CH				{ADC_VCR_GCTRL_AN173}		/* Conversion channels */
#define ADCDIAG_CFG_GRP35_START_POINTER		    (1U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP35_STOP_POINTER			(1U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP35_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE2)          /* Wiring-Break Detection Mode 2 */

#define ADCDIAG_CFG_GRP36_ID					(36U)					    	                /* ID */
#define ADCDIAG_CFG_GRP36_HWUNIT				(ADC_HWUNIT2)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP36_SG					(ADC_SG1)						                /* Scan Group */
#define ADCDIAG_CFG_GRP36_CNV_CH				{ADC_VCR_GCTRL_AN200}		/* Conversion channels */
#define ADCDIAG_CFG_GRP36_START_POINTER		    (1U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP36_STOP_POINTER			(1U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP36_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE1)          /* Wiring-Break Detection Mode 1 */

#define ADCDIAG_CFG_GRP37_ID					(37U)					    	                /* ID */
#define ADCDIAG_CFG_GRP37_HWUNIT				(ADC_HWUNIT2)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP37_SG					(ADC_SG0)						                /* Scan Group */
#define ADCDIAG_CFG_GRP37_CNV_CH				{ADC_VCR_GCTRL_AN260,ADC_VCR_GCTRL_AN261}		/* Conversion channels */
#define ADCDIAG_CFG_GRP37_START_POINTER		    (2U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP37_STOP_POINTER			(3U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP37_DIAG_TYPE			    (ADCDIAG_PIN_LEVEL)          /* Pin-Level Self-Diag */

#define ADCDIAG_CFG_GRP38_ID					(38U)					    	                /* ID */
#define ADCDIAG_CFG_GRP38_HWUNIT				(ADC_HWUNIT1)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP38_SG					(ADC_SG3)						                /* Scan Group */
#define ADCDIAG_CFG_GRP38_CNV_CH				{ADC_VCR_GCTRL_AN101}		/* Conversion channels */
#define ADCDIAG_CFG_GRP38_START_POINTER		    (3U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP38_STOP_POINTER			(3U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP38_DIAG_TYPE			    (ADCDIAG_SELF_DIAG_WIRING_BREAK_DETECTION_MODE1)          /*  Self-Diag Wiring-Break Detection Mode 1 */

#define ADCDIAG_CFG_GRP39_ID					(39U)					    	                /* ID */
#define ADCDIAG_CFG_GRP39_HWUNIT				(ADC_HWUNIT2)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP39_SG					(ADC_SG2)						                /* Scan Group */
#define ADCDIAG_CFG_GRP39_CNV_CH				{ADC_VCR_GCTRL_AN262}		/* Conversion channels */
#define ADCDIAG_CFG_GRP39_START_POINTER		    (4U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP39_STOP_POINTER			(4U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP39_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE2)          /* Wiring-Break Detection Mode 2 */

#define ADCDIAG_CFG_GRP40_ID					(40U)					    	                /* ID */
#define ADCDIAG_CFG_GRP40_HWUNIT				(ADC_HWUNIT0)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP40_SG					(ADC_SG2)						                /* Scan Group */
#define ADCDIAG_CFG_GRP40_CNV_CH				{ADC_VCR_GCTRL_AN001}		/* Conversion channels */
#define ADCDIAG_CFG_GRP40_START_POINTER		    (1U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP40_STOP_POINTER			(1U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP40_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE2)          /* Wiring-Break Detection Mode 2 */

#define ADCDIAG_CFG_GRP41_ID					(41U)					    	                /* ID */
#define ADCDIAG_CFG_GRP41_HWUNIT				(ADC_HWUNIT2)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP41_SG					(ADC_SG0)						                /* Scan Group */
#define ADCDIAG_CFG_GRP41_CNV_CH				{ADC_VCR_GCTRL_AN200,ADC_VCR_GCTRL_AN201,ADC_VCR_GCTRL_AN202}		/* Conversion channels */
#define ADCDIAG_CFG_GRP41_START_POINTER		    (0U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP41_STOP_POINTER			(2U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP41_DIAG_TYPE			    (ADCDIAG_PIN_LEVEL)          /* Pin-Level Self-Diag */

#define ADCDIAG_CFG_GRP42_ID					(42U)					    	                /* ID */
#define ADCDIAG_CFG_GRP42_HWUNIT				(ADC_HWUNIT1)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP42_SG					(ADC_SG4)						                /* Scan Group */
#define ADCDIAG_CFG_GRP42_CNV_CH				{ADC_VCR_GCTRL_AN101}		/* Conversion channels */
#define ADCDIAG_CFG_GRP42_START_POINTER		    (3U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP42_STOP_POINTER			(4U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP42_DIAG_TYPE			    (ADCDIAG_SELF_DIAG_WIRING_BREAK_DETECTION_MODE2)          /*  Self-Diag Wiring-Break Detection Mode 2 */

#define ADCDIAG_CFG_GRP43_ID					(43U)					    	                /* ID */
#define ADCDIAG_CFG_GRP43_HWUNIT				(ADC_HWUNIT2)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP43_SG					(ADC_SG2)						                /* Scan Group */
#define ADCDIAG_CFG_GRP43_CNV_CH				{ADC_VCR_GCTRL_AN200}		/* Conversion channels */
#define ADCDIAG_CFG_GRP43_START_POINTER		    (1U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP43_STOP_POINTER			(1U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP43_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE2)          /* Wiring-Break Detection Mode 2 */

#define ADCDIAG_CFG_GRP44_ID					(44U)					    	                /* ID */
#define ADCDIAG_CFG_GRP44_HWUNIT				(ADC_HWUNIT2)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP44_SG					(ADC_SG3)						                /* Scan Group */
#define ADCDIAG_CFG_GRP44_CNV_CH				{ADC_VCR_GCTRL_AN201}		/* Conversion channels */
#define ADCDIAG_CFG_GRP44_START_POINTER		    (3U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP44_STOP_POINTER			(3U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP44_DIAG_TYPE			    (ADCDIAG_SELF_DIAG_WIRING_BREAK_DETECTION_MODE1)          /*  Self-Diag Wiring-Break Detection Mode 1 */

#define ADCDIAG_CFG_GRP45_ID					(45U)					    	                /* ID */
#define ADCDIAG_CFG_GRP45_HWUNIT				(ADC_HWUNIT2)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP45_SG					(ADC_SG3)						                /* Scan Group */
#define ADCDIAG_CFG_GRP45_CNV_CH				{}		/* Conversion channels */
#define ADCDIAG_CFG_GRP45_START_POINTER		    (2U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP45_STOP_POINTER			(3U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP45_DIAG_TYPE			    (ADCDIAG_AD_CORE_SELF_DIAG)          /* Self-Diag ADcore */

#define ADCDIAG_CFG_GRP46_ID					(46U)					    	                /* ID */
#define ADCDIAG_CFG_GRP46_HWUNIT				(ADC_HWUNIT1)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP46_SG					(ADC_SG2)						                /* Scan Group */
#define ADCDIAG_CFG_GRP46_CNV_CH				{ADC_VCR_GCTRL_AN100}		/* Conversion channels */
#define ADCDIAG_CFG_GRP46_START_POINTER		    (1U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP46_STOP_POINTER			(1U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP46_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE2)          /* Wiring-Break Detection Mode 2 */

#define ADCDIAG_CFG_GRP47_ID					(47U)					    	                /* ID */
#define ADCDIAG_CFG_GRP47_HWUNIT				(ADC_HWUNIT0)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP47_SG					(ADC_SG1)						                /* Scan Group */
#define ADCDIAG_CFG_GRP47_CNV_CH				{ADC_VCR_GCTRL_AN060}		/* Conversion channels */
#define ADCDIAG_CFG_GRP47_START_POINTER		    (3U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP47_STOP_POINTER			(3U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP47_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE1)          /* Wiring-Break Detection Mode 1 */

#define ADCDIAG_CFG_GRP48_ID					(48U)					    	                /* ID */
#define ADCDIAG_CFG_GRP48_HWUNIT				(ADC_HWUNIT1)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP48_SG					(ADC_SG3)						                /* Scan Group */
#define ADCDIAG_CFG_GRP48_CNV_CH				{ADC_VCR_GCTRL_AN101}		/* Conversion channels */
#define ADCDIAG_CFG_GRP48_START_POINTER		    (3U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP48_STOP_POINTER			(3U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP48_DIAG_TYPE			    (ADCDIAG_SELF_DIAG_WIRING_BREAK_DETECTION_MODE1)          /*  Self-Diag Wiring-Break Detection Mode 1 */

#define ADCDIAG_CFG_GRP49_ID					(49U)					    	                /* ID */
#define ADCDIAG_CFG_GRP49_HWUNIT				(ADC_HWUNIT0)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP49_SG					(ADC_SG2)						                /* Scan Group */
#define ADCDIAG_CFG_GRP49_CNV_CH				{ADC_VCR_GCTRL_AN063}		/* Conversion channels */
#define ADCDIAG_CFG_GRP49_START_POINTER		    (1U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP49_STOP_POINTER			(1U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP49_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE2)          /* Wiring-Break Detection Mode 2 */

#define ADCDIAG_CFG_GRP50_ID					(50U)					    	                /* ID */
#define ADCDIAG_CFG_GRP50_HWUNIT				(ADC_HWUNIT0)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP50_SG					(ADC_SG4)						                /* Scan Group */
#define ADCDIAG_CFG_GRP50_CNV_CH				{ADC_VCR_GCTRL_AN000}		/* Conversion channels */
#define ADCDIAG_CFG_GRP50_START_POINTER		    (3U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP50_STOP_POINTER			(4U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP50_DIAG_TYPE			    (ADCDIAG_SELF_DIAG_WIRING_BREAK_DETECTION_MODE2)          /*  Self-Diag Wiring-Break Detection Mode 2 */

#define ADCDIAG_CFG_GRP51_ID					(51U)					    	                /* ID */
#define ADCDIAG_CFG_GRP51_HWUNIT				(ADC_HWUNIT0)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP51_SG					(ADC_SG2)						                /* Scan Group */
#define ADCDIAG_CFG_GRP51_CNV_CH				{}		/* Conversion channels */
#define ADCDIAG_CFG_GRP51_START_POINTER		    (4U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP51_STOP_POINTER			(4U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP51_DIAG_TYPE			    (ADCDIAG_AD_CORE_SELF_DIAG)          /* Self-Diag ADcore */

#define ADCDIAG_CFG_GRP52_ID					(52U)					    	                /* ID */
#define ADCDIAG_CFG_GRP52_HWUNIT				(ADC_HWUNIT0)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP52_SG					(ADC_SG1)						                /* Scan Group */
#define ADCDIAG_CFG_GRP52_CNV_CH				{ADC_VCR_GCTRL_AN001}		/* Conversion channels */
#define ADCDIAG_CFG_GRP52_START_POINTER		    (2U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP52_STOP_POINTER			(2U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP52_DIAG_TYPE			    (ADCDIAG_PIN_LEVEL)          /* Pin-Level Self-Diag */

#define ADCDIAG_CFG_GRP53_ID					(53U)					    	                /* ID */
#define ADCDIAG_CFG_GRP53_HWUNIT				(ADC_HWUNIT0)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP53_SG					(ADC_SG1)						                /* Scan Group */
#define ADCDIAG_CFG_GRP53_CNV_CH				{ADC_VCR_GCTRL_AN001}		/* Conversion channels */
#define ADCDIAG_CFG_GRP53_START_POINTER		    (1U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP53_STOP_POINTER			(1U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP53_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE1)          /* Wiring-Break Detection Mode 1 */

#define ADCDIAG_CFG_GRP54_ID					(54U)					    	                /* ID */
#define ADCDIAG_CFG_GRP54_HWUNIT				(ADC_HWUNIT2)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP54_SG					(ADC_SG2)						                /* Scan Group */
#define ADCDIAG_CFG_GRP54_CNV_CH				{ADC_VCR_GCTRL_AN262}		/* Conversion channels */
#define ADCDIAG_CFG_GRP54_START_POINTER		    (5U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP54_STOP_POINTER			(5U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP54_DIAG_TYPE			    (ADCDIAG_PIN_LEVEL)          /* Pin-Level Self-Diag */

#define ADCDIAG_CFG_GRP55_ID					(55U)					    	                /* ID */
#define ADCDIAG_CFG_GRP55_HWUNIT				(ADC_HWUNIT1)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP55_SG					(ADC_SG2)						                /* Scan Group */
#define ADCDIAG_CFG_GRP55_CNV_CH				{ADC_VCR_GCTRL_AN162}		/* Conversion channels */
#define ADCDIAG_CFG_GRP55_START_POINTER		    (3U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP55_STOP_POINTER			(3U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP55_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE2)          /* Wiring-Break Detection Mode 2 */

#define ADCDIAG_CFG_GRP56_ID					(56U)					    	                /* ID */
#define ADCDIAG_CFG_GRP56_HWUNIT				(ADC_HWUNIT2)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP56_SG					(ADC_SG1)						                /* Scan Group */
#define ADCDIAG_CFG_GRP56_CNV_CH				{ADC_VCR_GCTRL_AN261}		/* Conversion channels */
#define ADCDIAG_CFG_GRP56_START_POINTER		    (3U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP56_STOP_POINTER			(3U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP56_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE1)          /* Wiring-Break Detection Mode 1 */

#define ADCDIAG_CFG_GRP57_ID					(57U)					    	                /* ID */
#define ADCDIAG_CFG_GRP57_HWUNIT				(ADC_HWUNIT1)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP57_SG					(ADC_SG1)						                /* Scan Group */
#define ADCDIAG_CFG_GRP57_CNV_CH				{}		/* Conversion channels */
#define ADCDIAG_CFG_GRP57_START_POINTER		    (1U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP57_STOP_POINTER			(3U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP57_DIAG_TYPE			    (ADCDIAG_AD_CORE_SELF_DIAG)          /* Self-Diag ADcore */

#define ADCDIAG_CFG_GRP58_ID					(58U)					    	                /* ID */
#define ADCDIAG_CFG_GRP58_HWUNIT				(ADC_HWUNIT0)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP58_SG					(ADC_SG2)						                /* Scan Group */
#define ADCDIAG_CFG_GRP58_CNV_CH				{ADC_VCR_GCTRL_AN000}		/* Conversion channels */
#define ADCDIAG_CFG_GRP58_START_POINTER		    (2U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP58_STOP_POINTER			(2U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP58_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE2)          /* Wiring-Break Detection Mode 2 */

#define ADCDIAG_CFG_GRP59_ID					(59U)					    	                /* ID */
#define ADCDIAG_CFG_GRP59_HWUNIT				(ADC_HWUNIT1)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP59_SG					(ADC_SG1)						                /* Scan Group */
#define ADCDIAG_CFG_GRP59_CNV_CH				{ADC_VCR_GCTRL_AN100}		/* Conversion channels */
#define ADCDIAG_CFG_GRP59_START_POINTER		    (1U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP59_STOP_POINTER			(1U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP59_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE1)          /* Wiring-Break Detection Mode 1 */

#define ADCDIAG_CFG_GRP60_ID					(60U)					    	                /* ID */
#define ADCDIAG_CFG_GRP60_HWUNIT				(ADC_HWUNIT1)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP60_SG					(ADC_SG1)						                /* Scan Group */
#define ADCDIAG_CFG_GRP60_CNV_CH				{}		/* Conversion channels */
#define ADCDIAG_CFG_GRP60_START_POINTER		    (1U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP60_STOP_POINTER			(1U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP60_DIAG_TYPE			    (ADCDIAG_AD_CORE_SELF_DIAG)          /* Self-Diag ADcore */

#define ADCDIAG_CFG_GRP61_ID					(61U)					    	                /* ID */
#define ADCDIAG_CFG_GRP61_HWUNIT				(ADC_HWUNIT0)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP61_SG					(ADC_SG1)						                /* Scan Group */
#define ADCDIAG_CFG_GRP61_CNV_CH				{ADC_VCR_GCTRL_AN001}		/* Conversion channels */
#define ADCDIAG_CFG_GRP61_START_POINTER		    (3U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP61_STOP_POINTER			(3U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP61_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE2)          /* Wiring-Break Detection Mode 2 */

#define ADCDIAG_CFG_GRP62_ID					(62U)					    	                /* ID */
#define ADCDIAG_CFG_GRP62_HWUNIT				(ADC_HWUNIT1)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP62_SG					(ADC_SG0)						                /* Scan Group */
#define ADCDIAG_CFG_GRP62_CNV_CH				{ADC_VCR_GCTRL_AN100}		/* Conversion channels */
#define ADCDIAG_CFG_GRP62_START_POINTER		    (1U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP62_STOP_POINTER			(1U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP62_DIAG_TYPE			    (ADCDIAG_PIN_LEVEL)          /* Pin-Level Self-Diag */

#define ADCDIAG_CFG_GRP63_ID					(63U)					    	                /* ID */
#define ADCDIAG_CFG_GRP63_HWUNIT				(ADC_HWUNIT1)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP63_SG					(ADC_SG2)						                /* Scan Group */
#define ADCDIAG_CFG_GRP63_CNV_CH				{ADC_VCR_GCTRL_AN101}		/* Conversion channels */
#define ADCDIAG_CFG_GRP63_START_POINTER		    (1U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP63_STOP_POINTER			(1U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP63_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE2)          /* Wiring-Break Detection Mode 2 */

#define ADCDIAG_CFG_GRP64_ID					(64U)					    	                /* ID */
#define ADCDIAG_CFG_GRP64_HWUNIT				(ADC_HWUNIT0)				                    /* HW Unit */
#define ADCDIAG_CFG_GRP64_SG					(ADC_SG2)						                /* Scan Group */
#define ADCDIAG_CFG_GRP64_CNV_CH				{ADC_VCR_GCTRL_AN062}		/* Conversion channels */
#define ADCDIAG_CFG_GRP64_START_POINTER		    (4U)					                        /* Start Channel Pointer */
#define	ADCDIAG_CFG_GRP64_STOP_POINTER			(4U)					                        /* Stop Channel Pointer */
#define	ADCDIAG_CFG_GRP64_DIAG_TYPE			    (ADCDIAG_WIRING_BREAK_DETECTION_MODE2)          /* Wiring-Break Detection Mode 2 */

#endif /* ADCDIAG_CFG_H */
/*---------------------------------- End Of File ------------------------------------------------*/
