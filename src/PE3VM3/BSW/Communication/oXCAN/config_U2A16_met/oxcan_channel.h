/* 1.1.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Oem eXtention of CAN Channel                                                                                                     */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  WARNING :                                                                                                                        */
/*  oxcan_channel.h is included in oxcan.h                                                                                           */
/*  DO NOT include this file in any file even though this configuration header is public.                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef OXCAN_CHANNEL_H
#define OXCAN_CHANNEL_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_CHANNEL_H_MAJOR                    (1U)
#define OXCAN_CHANNEL_H_MINOR                    (1U)
#define OXCAN_CHANNEL_H_PATCH                    (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_NUM_CH                             (1U)
#define OXCAN_CH_0_VCAN                          (0U)                      /* #define ComMConf_ComMChannel_CDC_VCAN_BUS (0U) */

#define OXCAN_COMCONT_NUM_CH                     (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_PDU_NUM_RX                         (96U)

#define OXCAN_PDU_RX_CAN_ABG1D50_RXCH0           (0U)
#define OXCAN_PDU_RX_CAN_ABG1D51_RXCH0           (1U)
#define OXCAN_PDU_RX_CAN_ABG1S09_RXCH0           (2U)
#define OXCAN_PDU_RX_CAN_ACN1D50_RXCH0           (3U)
#define OXCAN_PDU_RX_CAN_ACN1S03_RXCH0           (4U)
#define OXCAN_PDU_RX_CAN_ACN1S15_RXCH0           (5U)
#define OXCAN_PDU_RX_CAN_ACN1S25_RXCH0           (6U)
#define OXCAN_PDU_RX_CAN_ACN1S29_RXCH0           (7U)
#define OXCAN_PDU_RX_CAN_ADC1S27_RXCH0           (8U)
#define OXCAN_PDU_RX_CAN_ADC1S30_RXCH0           (9U)
#define OXCAN_PDU_RX_CAN_ADC1S31_RXCH0           (10U)
#define OXCAN_PDU_RX_CAN_ADU1S03_RXCH0           (11U)
#define OXCAN_PDU_RX_CAN_ADU1S05_RXCH0           (12U)
#define OXCAN_PDU_RX_CAN_ADU1S06_RXCH0           (13U)
#define OXCAN_PDU_RX_CAN_AVN1S95_RXCH0           (14U)
#define OXCAN_PDU_RX_CAN_BAT1E45_RXCH0           (15U)
#define OXCAN_PDU_RX_CAN_BAT1ED1_RXCH0           (16U)
#define OXCAN_PDU_RX_CAN_BAT1ED4_RXCH0           (17U)
#define OXCAN_PDU_RX_CAN_BAT1ED5_RXCH0           (18U)
#define OXCAN_PDU_RX_CAN_BAT1EDA_RXCH0           (19U)
#define OXCAN_PDU_RX_CAN_BAT1EDB_RXCH0           (20U)
#define OXCAN_PDU_RX_CAN_BAT1S08_RXCH0           (21U)
#define OXCAN_PDU_RX_CAN_BAT2ED2_RXCH0           (22U)
#define OXCAN_PDU_RX_CAN_BDB1F03_RXCH0           (23U)
#define OXCAN_PDU_RX_CAN_BDB1S10_RXCH0           (24U)
#define OXCAN_PDU_RX_CAN_BDC1S41_RXCH0           (25U)
#define OXCAN_PDU_RX_CAN_BDC1S81_RXCH0           (26U)
#define OXCAN_PDU_RX_CAN_BDC1S82_RXCH0           (27U)
#define OXCAN_PDU_RX_CAN_BDC1SH8_RXCH0           (28U)
#define OXCAN_PDU_RX_CAN_BDF3S01_RXCH0           (29U)
#define OXCAN_PDU_RX_CAN_BDF3S02_RXCH0           (30U)
#define OXCAN_PDU_RX_CAN_BDR3S02_RXCH0           (31U)
#define OXCAN_PDU_RX_CAN_CDC1S04_RXCH0           (32U)
#define OXCAN_PDU_RX_CAN_CMB1S03_RXCH0           (33U)
#define OXCAN_PDU_RX_CAN_CMB1S04_RXCH0           (34U)
#define OXCAN_PDU_RX_CAN_DCM1S08_RXCH0           (35U)
#define OXCAN_PDU_RX_CAN_DDM1S00_RXCH0           (36U)
#define OXCAN_PDU_RX_CAN_DDM1S09_RXCH0           (37U)
#define OXCAN_PDU_RX_CAN_DDM1S16_RXCH0           (38U)
#define OXCAN_PDU_RX_CAN_DDM1S35_RXCH0           (39U)
#define OXCAN_PDU_RX_CAN_DDM1SFG_RXCH0           (40U)
#define OXCAN_PDU_RX_CAN_DDM1SFH_RXCH0           (41U)
#define OXCAN_PDU_RX_CAN_DKY1S26_RXCH0           (42U)
#define OXCAN_PDU_RX_CAN_DS11S27_RXCH0           (43U)
#define OXCAN_PDU_RX_CAN_EBU1D01_RXCH0           (44U)
#define OXCAN_PDU_RX_CAN_ECT1S93_RXCH0           (45U)
#define OXCAN_PDU_RX_CAN_EHV1E96_RXCH0           (46U)
#define OXCAN_PDU_RX_CAN_EHV1F02_RXCH0           (47U)
#define OXCAN_PDU_RX_CAN_EHV1S23_RXCH0           (48U)
#define OXCAN_PDU_RX_CAN_EHV2G10_RXCH0           (49U)
#define OXCAN_PDU_RX_CAN_EHV2G20_RXCH0           (50U)
#define OXCAN_PDU_RX_CAN_EIM1S01_RXCH0           (51U)
#define OXCAN_PDU_RX_CAN_ENG1C01_RXCH0           (52U)
#define OXCAN_PDU_RX_CAN_ENG1C02_RXCH0           (53U)
#define OXCAN_PDU_RX_CAN_ENG1D51_RXCH0           (54U)
#define OXCAN_PDU_RX_CAN_ENG1D52_RXCH0           (55U)
#define OXCAN_PDU_RX_CAN_ENG1D53_RXCH0           (56U)
#define OXCAN_PDU_RX_CAN_ENG1D55_RXCH0           (57U)
#define OXCAN_PDU_RX_CAN_ENG1D56_RXCH0           (58U)
#define OXCAN_PDU_RX_CAN_ENG1D59_RXCH0           (59U)
#define OXCAN_PDU_RX_CAN_ENG1D60_RXCH0           (60U)
#define OXCAN_PDU_RX_CAN_ENG1S51_RXCH0           (61U)
#define OXCAN_PDU_RX_CAN_EPS1D50_RXCH0           (62U)
#define OXCAN_PDU_RX_CAN_FCM1C01_RXCH0           (63U)
#define OXCAN_PDU_RX_CAN_FCM1S49_RXCH0           (64U)
#define OXCAN_PDU_RX_CAN_FCM1S76_RXCH0           (65U)
#define OXCAN_PDU_RX_CAN_FCM1S79_RXCH0           (66U)
#define OXCAN_PDU_RX_CAN_FCM1S90_RXCH0           (67U)
#define OXCAN_PDU_RX_CAN_FCM1S95_RXCH0           (68U)
#define OXCAN_PDU_RX_CAN_IDT1S07_RXCH0           (69U)
#define OXCAN_PDU_RX_CAN_IDT1S15_RXCH0           (70U)
#define OXCAN_PDU_RX_CAN_MET1S02_RXCH0           (71U)
#define OXCAN_PDU_RX_CAN_MGC1F13_RXCH0           (72U)
#define OXCAN_PDU_RX_CAN_PDC1G01_RXCH0           (73U)
#define OXCAN_PDU_RX_CAN_PWC1S41_RXCH0           (74U)
#define OXCAN_PDU_RX_CAN_RCP1S03_RXCH0           (75U)
#define OXCAN_PDU_RX_CAN_RSE1G20_RXCH0           (76U)
#define OXCAN_PDU_RX_CAN_RSE1G24_RXCH0           (77U)
#define OXCAN_PDU_RX_CAN_RSE1G25_RXCH0           (78U)
#define OXCAN_PDU_RX_CAN_RSE1G26_RXCH0           (79U)
#define OXCAN_PDU_RX_CAN_RSE1G29_RXCH0           (80U)
#define OXCAN_PDU_RX_CAN_RSE1S02_RXCH0           (81U)
#define OXCAN_PDU_RX_CAN_SCS1S10_RXCH0           (82U)
#define OXCAN_PDU_RX_CAN_VGR1D50_RXCH0           (83U)
#define OXCAN_PDU_RX_CAN_VSC1D51_RXCH0           (84U)
#define OXCAN_PDU_RX_CAN_VSC1G13_RXCH0           (85U)
#define OXCAN_PDU_RX_CAN_WIP1S01_RXCH0           (86U)
#define OXCAN_PDU_RX_CAN_ZN11S08_RXCH0           (87U)
#define OXCAN_PDU_RX_CAN_ZN11S32_RXCH0           (88U)
#define OXCAN_PDU_RX_CAN_ZN11S63_RXCH0           (89U)
#define OXCAN_PDU_RX_CAN_ZN11S64_RXCH0           (90U)
#define OXCAN_PDU_RX_CAN_ZN11S65_RXCH0           (91U)
#define OXCAN_PDU_RX_CAN_ZN11S66_RXCH0           (92U)
#define OXCAN_PDU_RX_CAN_ZN11S67_RXCH0           (93U)
#define OXCAN_PDU_RX_CAN_ZN11SF6_RXCH0           (94U)
#define OXCAN_PDU_RX_CAN_ZN11SF7_RXCH0           (95U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_AUB_CXPI_SUP                       (0U)                          /* 1 = Aubist/CXPI is supported, other = not          */
#define OXCAN_AUB_CSM_SUP                        (0U)                          /* 1 = Aubist/CSM is supported, other = not           */
#define OXCAN_AUB_CRPT_SW_SUP                    (0U)                          /* 1 = Aubist/Crypto-sw is supported, other = not     */
#define OXCAN_NMDIAG_GBL_SUP                     (0U)                          /* 1 = NM Diag (global-ecu) is supported, other = not */
#define OXCAN_IC_TJA1145_USE                     (0U)                          /* 1 = TJA1145 is use, other = not                    */
#define OXCAN_IC_TJA1145_REFRESH                 (0U)                          /* 1 = With Refresh , other = not                     */

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

#endif      /* OXCAN_CHANNEL_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see  oxcan_cfg.c and oxcan_rx_cfg.c                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
