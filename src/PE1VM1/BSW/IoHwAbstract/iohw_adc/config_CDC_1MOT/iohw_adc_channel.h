/* 1.8.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  IO Hardware Abstraction Analog Digital Converter                                                                                 */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  WARNING :                                                                                                                        */
/*  iohw_adc_channel.h is included in iohw_adc.h.                                                                                    */
/*  DO NOT include this file in any file even though this configuration header is public.                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef IOHW_ADC_CHANNEL_H
#define IOHW_ADC_CHANNEL_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IOHW_ADC_CHANNEL_H_MAJOR                 (1)
#define IOHW_ADC_CHANNEL_H_MINOR                 (8)
#define IOHW_ADC_CHANNEL_H_PATCH                 (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ADC_NUM_CH                               (ADC_CFG_GRP00_CNV_CH_SIZE + ADC_CFG_GRP01_CNV_CH_SIZE + ADC_CFG_GRP02_CNV_CH_SIZE)
#define ADC_CH_IG_MON                            (0U)      /* This macro is necessary for integration with iohw_difilt */
#define ADC_CH_USB_ADP                           (0U)      /* USB-ADP-DET,      ADCJ0I0,   AP0_0   */
#define ADC_CH_GPS_ANT                           (1U)      /* GPS-ANT-DET,      ADCJ0I1,   AP0_1   */
#define ADC_CH_DAB_ANT1                          (2U)      /* DAB-ANT-DET1,     ADCJ0I2,   AP0_2   */
#define ADC_CH_DAB_ANT2                          (3U)      /* DAB-ANT-DET2,     ADCJ0I3,   AP0_3   */
#define ADC_CH_PMA                               (4U)      /* PMA_THERM_P,      ADCJ0I6,   AP0_6   */
#define ADC_CH_PMC                               (5U)      /* PMC_THERM_P,      ADCJ0I7,   AP0_7   */
#define ADC_CH_PME                               (6U)      /* PME_THERM_P,      ADCJ0I8,   AP0_8   */
#define ADC_CH_RESERVED_ADCJ0I17                 (7U)      /* Reserved(AD),     ADCJ0I17,  AP1_1   */
#define ADC_CH_RESERVED_ADCJ0I18                 (8U)      /* Reserved(AD),     ADCJ0I18,  AP1_2   */
#define ADC_CH_RESERVED_ADCJ0I19                 (9U)      /* Reserved(AD),     ADCJ0I19,  AP1_3   */
#define ADC_CH_MIC                               (10U)     /* MIC-DET,          ADCJ1I0,   AP2_0   */
#define ADC_CH_MIC2                              (11U)     /* MIC2-DET,         ADCJ1I1,   AP2_1   */
#define ADC_CH_MIC3                              (12U)     /* MIC3-DET,         ADCJ1I2,   AP2_2   */
#define ADC_CH_MIC4                              (13U)     /* MIC4-DET,         ADCJ1I3,   AP2_3   */
#define ADC_CH_BTWA1                             (14U)     /* BT/WIFI-ANT-DET2, ADCJ1I4,   AP2_4   */
#define ADC_CH_BTWA2                             (15U)     /* BT/WIFI-ANT-DET,  ADCJ1I5,   AP2_5   */
#define ADC_CH_USB_CUR                           (16U)     /* USB-CURRENT-DET,  ADCJ1I6,   AP2_6   */
#define ADC_CH_B_MON3                            (17U)     /* +B-MONITOR3,      ADCJ1I7,   AP2_7   */
#define ADC_CH_HUD_M_S_IN                        (18U)     /* HUD_MAIN_SW_IN,   ADCJ1I8,   AP2_8   */
#define ADC_CH_CAN5_MON                          (19U)     /* CAN-5V-MONITOR,   ADCJ1I9,   AP2_9   */
#define ADC_CH_PIC_CUR                           (20U)     /* PIC-CURRENT-DET,  ADCJ1I10,  AP2_10  */
#define ADC_CH_PIC_OFS                           (21U)     /* PIC-OFFSET-DET,   ADCJ1I11,  AP2_11  */
#define ADC_CH_BRD_ID0                           (22U)     /* BRD_ID0,          ADCJ1I12,  AP2_12  */
#define ADC_CH_BRD_ID1                           (23U)     /* BRD_ID1,          ADCJ1I13,  AP2_13  */
#define ADC_CH_TEMP3                             (24U)     /* TEMP3,            ADCJ1I14,  AP2_14  */
#define ADC_CH_TEMP4                             (25U)     /* TEMP4,            ADCJ1I15,  AP2_15  */
#define ADC_CH_RHE_IN                            (26U)     /* RHEOSTAT_UD_IN,   ADCJ1I17,  AP3_1   */
#define ADC_CH_B_MON2                            (27U)     /* +B-MONITOR2,      ADCJ2I3,   AP4_3   */
#define ADC_CH_B_MON1                            (28U)     /* +B-MONITOR1,      ADCJ2I4,   AP4_4   */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ADC_NUM_GR                               (ADC_CFG_GRP_SIZE)
#define ADC_GR_UN_0                              (ADC_GR_0)
#define ADC_GR_UN_1                              (ADC_GR_1)
#define ADC_GR_UN_2                              (ADC_GR_2)

#define ADC_UN_0_NUM_CH                          (ADC_CFG_GRP00_CNV_CH_SIZE)
#define ADC_UN_1_NUM_CH                          (ADC_CFG_GRP01_CNV_CH_SIZE)
#define ADC_UN_2_NUM_CH                          (ADC_CFG_GRP02_CNV_CH_SIZE)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IOHW_ADC_LV_MAX                          (0x0fffU) /* resolution = 12 bit */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* IOHW_ADC_CHANNEL_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see iohw_adc_cfg.c                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/
