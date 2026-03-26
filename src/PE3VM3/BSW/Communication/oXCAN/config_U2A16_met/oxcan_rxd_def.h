/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  OEM eXtention of CAN : Rx Detection                                                                                              */
/*                                                                                                                                   */
/*  WARNING :                                                                                                                        */
/*  oxcan_rxd_def.h is included in oxcan_lib.h and oxcan.h                                                                           */
/*  DO NOT include this file in any file even though this configuration header is public.                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef OXCAN_RXD_DEF_H
#define OXCAN_RXD_DEF_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_RXD_DEF_H_MAJOR                    (2U)
#define OXCAN_RXD_DEF_H_MINOR                    (0U)
#define OXCAN_RXD_DEF_H_PATCH                    (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_RXD_NUM_GR                         (1U)
#define OXCAN_RXD_GR_CAN                         (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_RXD_NUM_PDU                        (101U)

#define OXCAN_RXD_PDU_CAN_ABG1D50_CH0            (0U)
#define OXCAN_RXD_PDU_CAN_ABG1D51_CH0            (1U)
#define OXCAN_RXD_PDU_CAN_ABG1S09_CH0            (2U)
#define OXCAN_RXD_PDU_CAN_ACN1D50_CH0            (3U)
#define OXCAN_RXD_PDU_CAN_ACN1S03_CH0            (4U)
#define OXCAN_RXD_PDU_CAN_ACN1S15_CH0            (5U)
#define OXCAN_RXD_PDU_CAN_ACN1S25_CH0            (6U)
#define OXCAN_RXD_PDU_CAN_ACN1S29_CH0            (7U)
#define OXCAN_RXD_PDU_CAN_ADC1S27_CH0            (8U)
#define OXCAN_RXD_PDU_CAN_ADC1S30_CH0            (9U)
#define OXCAN_RXD_PDU_CAN_ADC1S31_CH0            (10U)
#define OXCAN_RXD_PDU_CAN_ADU1S03_CH0            (11U)
#define OXCAN_RXD_PDU_CAN_ADU1S05_CH0            (12U)
#define OXCAN_RXD_PDU_CAN_ADU1S06_CH0            (13U)
#define OXCAN_RXD_PDU_CAN_AVN1S95_CH0            (14U)
#define OXCAN_RXD_PDU_CAN_BAT1E45_CH0            (15U)
#define OXCAN_RXD_PDU_CAN_BAT1EDA_CH0            (16U)
#define OXCAN_RXD_PDU_CAN_BAT1S08_CH0            (17U)
#define OXCAN_RXD_PDU_CAN_BAT2ED2_CH0            (18U)
#define OXCAN_RXD_PDU_CAN_BDB1F03_CH0            (19U)
#define OXCAN_RXD_PDU_CAN_BDB1S10_CH0            (20U)
#define OXCAN_RXD_PDU_CAN_BDC1S41_CH0            (21U)
#define OXCAN_RXD_PDU_CAN_BDC1S81_CH0            (22U)
#define OXCAN_RXD_PDU_CAN_BDC1S82_CH0            (23U)
#define OXCAN_RXD_PDU_CAN_BDC1S91_CH0            (24U)
#define OXCAN_RXD_PDU_CAN_BDC1SH8_CH0            (25U)
#define OXCAN_RXD_PDU_CAN_BDC1SI1_CH0            (26U)
#define OXCAN_RXD_PDU_CAN_BDC1SI2_CH0            (27U)
#define OXCAN_RXD_PDU_CAN_BDC1SI3_CH0            (28U)
#define OXCAN_RXD_PDU_CAN_BDC1SI4_CH0            (29U)
#define OXCAN_RXD_PDU_CAN_BDC1SI5_CH0            (30U)
#define OXCAN_RXD_PDU_CAN_BDC1SI6_CH0            (31U)
#define OXCAN_RXD_PDU_CAN_BDC1SI7_CH0            (32U)
#define OXCAN_RXD_PDU_CAN_BDC1SI8_CH0            (33U)
#define OXCAN_RXD_PDU_CAN_BDC1SI9_CH0            (34U)
#define OXCAN_RXD_PDU_CAN_BDC1SJ0_CH0            (35U)
#define OXCAN_RXD_PDU_CAN_BDC1SJ1_CH0            (36U)
#define OXCAN_RXD_PDU_CAN_BDC1SJ2_CH0            (37U)
#define OXCAN_RXD_PDU_CAN_BDF3S01_CH0            (38U)
#define OXCAN_RXD_PDU_CAN_BDF3S02_CH0            (39U)
#define OXCAN_RXD_PDU_CAN_BDR3S02_CH0            (40U)
#define OXCAN_RXD_PDU_CAN_CDC1S04_CH0            (41U)
#define OXCAN_RXD_PDU_CAN_CMB1S03_CH0            (42U)
#define OXCAN_RXD_PDU_CAN_CMB1S04_CH0            (43U)
#define OXCAN_RXD_PDU_CAN_DCM1S08_CH0            (44U)
#define OXCAN_RXD_PDU_CAN_DDM1S00_CH0            (45U)
#define OXCAN_RXD_PDU_CAN_DDM1S09_CH0            (46U)
#define OXCAN_RXD_PDU_CAN_DDM1S16_CH0            (47U)
#define OXCAN_RXD_PDU_CAN_DDM1S35_CH0            (48U)
#define OXCAN_RXD_PDU_CAN_DDM1SFH_CH0            (49U)
#define OXCAN_RXD_PDU_CAN_DKY1S26_CH0            (50U)
#define OXCAN_RXD_PDU_CAN_DS11S27_CH0            (51U)
#define OXCAN_RXD_PDU_CAN_EBU1D01_CH0            (52U)
#define OXCAN_RXD_PDU_CAN_ECT1S93_CH0            (53U)
#define OXCAN_RXD_PDU_CAN_EHV1E96_CH0            (54U)
#define OXCAN_RXD_PDU_CAN_EHV1F02_CH0            (55U)
#define OXCAN_RXD_PDU_CAN_EHV1S23_CH0            (56U)
#define OXCAN_RXD_PDU_CAN_EHV2G10_CH0            (57U)
#define OXCAN_RXD_PDU_CAN_EHV2G20_CH0            (58U)
#define OXCAN_RXD_PDU_CAN_EIM1S01_CH0            (59U)
#define OXCAN_RXD_PDU_CAN_ENG1C01_CH0            (60U)
#define OXCAN_RXD_PDU_CAN_ENG1C02_CH0            (61U)
#define OXCAN_RXD_PDU_CAN_ENG1D51_CH0            (62U)
#define OXCAN_RXD_PDU_CAN_ENG1D52_CH0            (63U)
#define OXCAN_RXD_PDU_CAN_ENG1D53_CH0            (64U)
#define OXCAN_RXD_PDU_CAN_ENG1D55_CH0            (65U)
#define OXCAN_RXD_PDU_CAN_ENG1D56_CH0            (66U)
#define OXCAN_RXD_PDU_CAN_ENG1D59_CH0            (67U)
#define OXCAN_RXD_PDU_CAN_ENG1D60_CH0            (68U)
#define OXCAN_RXD_PDU_CAN_ENG1S51_CH0            (69U)
#define OXCAN_RXD_PDU_CAN_EPS1D50_CH0            (70U)
#define OXCAN_RXD_PDU_CAN_FCM1C01_CH0            (71U)
#define OXCAN_RXD_PDU_CAN_FCM1S49_CH0            (72U)
#define OXCAN_RXD_PDU_CAN_FCM1S76_CH0            (73U)
#define OXCAN_RXD_PDU_CAN_FCM1S79_CH0            (74U)
#define OXCAN_RXD_PDU_CAN_FCM1S90_CH0            (75U)
#define OXCAN_RXD_PDU_CAN_FCM1S95_CH0            (76U)
#define OXCAN_RXD_PDU_CAN_IDT1S07_CH0            (77U)
#define OXCAN_RXD_PDU_CAN_IDT1S15_CH0            (78U)
#define OXCAN_RXD_PDU_CAN_MET1S02_CH0            (79U)
#define OXCAN_RXD_PDU_CAN_MGC1F13_CH0            (80U)
#define OXCAN_RXD_PDU_CAN_PDC1G01_CH0            (81U)
#define OXCAN_RXD_PDU_CAN_RCP1S03_CH0            (82U)
#define OXCAN_RXD_PDU_CAN_RCP1S04_CH0            (83U)
#define OXCAN_RXD_PDU_CAN_RCP1S05_CH0            (84U)
#define OXCAN_RXD_PDU_CAN_RCP1S06_CH0            (85U)
#define OXCAN_RXD_PDU_CAN_RSE1G20_CH0            (86U)
#define OXCAN_RXD_PDU_CAN_RSE1G24_CH0            (87U)
#define OXCAN_RXD_PDU_CAN_RSE1G25_CH0            (88U)
#define OXCAN_RXD_PDU_CAN_RSE1G26_CH0            (89U)
#define OXCAN_RXD_PDU_CAN_RSE1S02_CH0            (90U)
#define OXCAN_RXD_PDU_CAN_VGR1D50_CH0            (91U)
#define OXCAN_RXD_PDU_CAN_VSC1D51_CH0            (92U)
#define OXCAN_RXD_PDU_CAN_VSC1G13_CH0            (93U)
#define OXCAN_RXD_PDU_CAN_WIP1S01_CH0            (94U)
#define OXCAN_RXD_PDU_CAN_ZN11S08_CH0            (95U)
#define OXCAN_RXD_PDU_CAN_ZN11S63_CH0            (96U)
#define OXCAN_RXD_PDU_CAN_ZN11S64_CH0            (97U)
#define OXCAN_RXD_PDU_CAN_ZN11S65_CH0            (98U)
#define OXCAN_RXD_PDU_CAN_ZN11S66_CH0            (99U)
#define OXCAN_RXD_PDU_CAN_ZN11S67_CH0            (100U)

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

#endif      /* OXCAN_RXD_DEF_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see and oxcan_rxd_cfg.c                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/
