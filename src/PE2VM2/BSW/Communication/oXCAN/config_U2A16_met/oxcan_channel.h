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

#define OXCAN_CH_0_CAN                           (0U)

#define OXCAN_COMCONT_NUM_CH                     (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_PDU_NUM_RX                         (241U)

#define OXCAN_PDU_RX_CAN_ABG1D50_RXCH0           (0U)
#define OXCAN_PDU_RX_CAN_ABG1D51_RXCH0           (1U)
#define OXCAN_PDU_RX_CAN_ABG1S01_RXCH0           (2U)
#define OXCAN_PDU_RX_CAN_ABG1S04_RXCH0           (3U)
#define OXCAN_PDU_RX_CAN_ACN1D50_RXCH0           (4U)
#define OXCAN_PDU_RX_CAN_ACN1S03_RXCH0           (5U)
#define OXCAN_PDU_RX_CAN_ACN1S04_RXCH0           (6U)
#define OXCAN_PDU_RX_CAN_ACN1S05_RXCH0           (7U)
#define OXCAN_PDU_RX_CAN_ACN1S07_RXCH0           (8U)
#define OXCAN_PDU_RX_CAN_ACN1S15_RXCH0           (9U)
#define OXCAN_PDU_RX_CAN_ACN1S16_RXCH0           (10U)
#define OXCAN_PDU_RX_CAN_ACN1S22_RXCH0           (11U)
#define OXCAN_PDU_RX_CAN_ACN1S25_RXCH0           (12U)
#define OXCAN_PDU_RX_CAN_ACN1S29_RXCH0           (13U)
#define OXCAN_PDU_RX_CAN_ADC1S06_RXCH0           (14U)
#define OXCAN_PDU_RX_CAN_ADC1S13_RXCH0           (15U)
#define OXCAN_PDU_RX_CAN_ADC1S14_RXCH0           (16U)
#define OXCAN_PDU_RX_CAN_ADC1S17_RXCH0           (17U)
#define OXCAN_PDU_RX_CAN_ADC1S19_RXCH0           (18U)
#define OXCAN_PDU_RX_CAN_ADC1S20_RXCH0           (19U)
#define OXCAN_PDU_RX_CAN_ADC1S23_RXCH0           (20U)
#define OXCAN_PDU_RX_CAN_ADC1S31_RXCH0           (21U)
#define OXCAN_PDU_RX_CAN_ADU1S02_RXCH0           (22U)
#define OXCAN_PDU_RX_CAN_ADU1S07_RXCH0           (23U)
#define OXCAN_PDU_RX_CAN_ADU1S18_RXCH0           (24U)
#define OXCAN_PDU_RX_CAN_ADU1S19_RXCH0           (25U)
#define OXCAN_PDU_RX_CAN_ADU1S20_RXCH0           (26U)
#define OXCAN_PDU_RX_CAN_ADU1S21_RXCH0           (27U)
#define OXCAN_PDU_RX_CAN_ADU1S22_RXCH0           (28U)
#define OXCAN_PDU_RX_CAN_ADU1S23_RXCH0           (29U)
#define OXCAN_PDU_RX_CAN_ADU1S24_RXCH0           (30U)
#define OXCAN_PDU_RX_CAN_ADU1S25_RXCH0           (31U)
#define OXCAN_PDU_RX_CAN_ADU1S26_RXCH0           (32U)
#define OXCAN_PDU_RX_CAN_ADU1S27_RXCH0           (33U)
#define OXCAN_PDU_RX_CAN_ADU1S28_RXCH0           (34U)
#define OXCAN_PDU_RX_CAN_BAT1E41_RXCH0           (35U)
#define OXCAN_PDU_RX_CAN_BAT1E45_RXCH0           (36U)
#define OXCAN_PDU_RX_CAN_BAT1S01_RXCH0           (37U)
#define OXCAN_PDU_RX_CAN_BAT1S08_RXCH0           (38U)
#define OXCAN_PDU_RX_CAN_BCC1S05_RXCH0           (39U)
#define OXCAN_PDU_RX_CAN_BCC1S06_RXCH0           (40U)
#define OXCAN_PDU_RX_CAN_BDB1F01_RXCH0           (41U)
#define OXCAN_PDU_RX_CAN_BDB1F03_RXCH0           (42U)
#define OXCAN_PDU_RX_CAN_BDB1S01_RXCH0           (43U)
#define OXCAN_PDU_RX_CAN_BDB1S08_RXCH0           (44U)
#define OXCAN_PDU_RX_CAN_BDB1S10_RXCH0           (45U)
#define OXCAN_PDU_RX_CAN_BDB1S19_RXCH0           (46U)
#define OXCAN_PDU_RX_CAN_BDB1S25_RXCH0           (47U)
#define OXCAN_PDU_RX_CAN_BDB1S26_RXCH0           (48U)
#define OXCAN_PDU_RX_CAN_BDB1S27_RXCH0           (49U)
#define OXCAN_PDU_RX_CAN_BDB1S28_RXCH0           (50U)
#define OXCAN_PDU_RX_CAN_BDB1S29_RXCH0           (51U)
#define OXCAN_PDU_RX_CAN_BDB1S35_RXCH0           (52U)
#define OXCAN_PDU_RX_CAN_BDB1S36_RXCH0           (53U)
#define OXCAN_PDU_RX_CAN_BDC1S14_RXCH0           (54U)
#define OXCAN_PDU_RX_CAN_BDC1S16_RXCH0           (55U)
#define OXCAN_PDU_RX_CAN_BDC1S22_RXCH0           (56U)
#define OXCAN_PDU_RX_CAN_BDC1S30_RXCH0           (57U)
#define OXCAN_PDU_RX_CAN_BDC1S41_RXCH0           (58U)
#define OXCAN_PDU_RX_CAN_BDC1S48_RXCH0           (59U)
#define OXCAN_PDU_RX_CAN_BDC1S81_RXCH0           (60U)
#define OXCAN_PDU_RX_CAN_BDC1S83_RXCH0           (61U)
#define OXCAN_PDU_RX_CAN_BDC1S97_RXCH0           (62U)
#define OXCAN_PDU_RX_CAN_BDC1S98_RXCH0           (63U)
#define OXCAN_PDU_RX_CAN_BDC1S99_RXCH0           (64U)
#define OXCAN_PDU_RX_CAN_BDC1SA0_RXCH0           (65U)
#define OXCAN_PDU_RX_CAN_BDC1SA1_RXCH0           (66U)
#define OXCAN_PDU_RX_CAN_BDC1SC1_RXCH0           (67U)
#define OXCAN_PDU_RX_CAN_BDC1SC2_RXCH0           (68U)
#define OXCAN_PDU_RX_CAN_BDC1SC3_RXCH0           (69U)
#define OXCAN_PDU_RX_CAN_BDC1SC4_RXCH0           (70U)
#define OXCAN_PDU_RX_CAN_BDC1SC5_RXCH0           (71U)
#define OXCAN_PDU_RX_CAN_BDC1SC6_RXCH0           (72U)
#define OXCAN_PDU_RX_CAN_BDC1SC7_RXCH0           (73U)
#define OXCAN_PDU_RX_CAN_BDC1SC8_RXCH0           (74U)
#define OXCAN_PDU_RX_CAN_BDC1SC9_RXCH0           (75U)
#define OXCAN_PDU_RX_CAN_BDC1SD1_RXCH0           (76U)
#define OXCAN_PDU_RX_CAN_BDC1SD2_RXCH0           (77U)
#define OXCAN_PDU_RX_CAN_BDC1SD3_RXCH0           (78U)
#define OXCAN_PDU_RX_CAN_BDC1SD4_RXCH0           (79U)
#define OXCAN_PDU_RX_CAN_BDC1SD5_RXCH0           (80U)
#define OXCAN_PDU_RX_CAN_BDC1SD6_RXCH0           (81U)
#define OXCAN_PDU_RX_CAN_BDC1SD7_RXCH0           (82U)
#define OXCAN_PDU_RX_CAN_BDC1SD8_RXCH0           (83U)
#define OXCAN_PDU_RX_CAN_BDC1SD9_RXCH0           (84U)
#define OXCAN_PDU_RX_CAN_BDC1SE1_RXCH0           (85U)
#define OXCAN_PDU_RX_CAN_BDC1SE2_RXCH0           (86U)
#define OXCAN_PDU_RX_CAN_BDC1SE3_RXCH0           (87U)
#define OXCAN_PDU_RX_CAN_BDC1SE4_RXCH0           (88U)
#define OXCAN_PDU_RX_CAN_BDC1SE5_RXCH0           (89U)
#define OXCAN_PDU_RX_CAN_BDC1SE6_RXCH0           (90U)
#define OXCAN_PDU_RX_CAN_BDC1SE7_RXCH0           (91U)
#define OXCAN_PDU_RX_CAN_BDC1SE8_RXCH0           (92U)
#define OXCAN_PDU_RX_CAN_BDC1SE9_RXCH0           (93U)
#define OXCAN_PDU_RX_CAN_BDC1SF1_RXCH0           (94U)
#define OXCAN_PDU_RX_CAN_BDC1SF2_RXCH0           (95U)
#define OXCAN_PDU_RX_CAN_BDC1SF3_RXCH0           (96U)
#define OXCAN_PDU_RX_CAN_BDC1SF4_RXCH0           (97U)
#define OXCAN_PDU_RX_CAN_BDC1SF6_RXCH0           (98U)
#define OXCAN_PDU_RX_CAN_BDC1SG4_RXCH0           (99U)
#define OXCAN_PDU_RX_CAN_BDC1SG6_RXCH0           (100U)
#define OXCAN_PDU_RX_CAN_BDC1SG7_RXCH0           (101U)
#define OXCAN_PDU_RX_CAN_BDC1SG8_RXCH0           (102U)
#define OXCAN_PDU_RX_CAN_BDC1SG9_RXCH0           (103U)
#define OXCAN_PDU_RX_CAN_BDC1SH3_RXCH0           (104U)
#define OXCAN_PDU_RX_CAN_BDC1SH4_RXCH0           (105U)
#define OXCAN_PDU_RX_CAN_BDC1SH5_RXCH0           (106U)
#define OXCAN_PDU_RX_CAN_BDC1SH6_RXCH0           (107U)
#define OXCAN_PDU_RX_CAN_BDC1SH8_RXCH0           (108U)
#define OXCAN_PDU_RX_CAN_BDF3S01_RXCH0           (109U)
#define OXCAN_PDU_RX_CAN_BDF3S02_RXCH0           (110U)
#define OXCAN_PDU_RX_CAN_BDR3S02_RXCH0           (111U)
#define OXCAN_PDU_RX_CAN_BSR1S01_RXCH0           (112U)
#define OXCAN_PDU_RX_CAN_BSR1S02_RXCH0           (113U)
#define OXCAN_PDU_RX_CAN_BSR1S03_RXCH0           (114U)
#define OXCAN_PDU_RX_CAN_CMB1S03_RXCH0           (115U)
#define OXCAN_PDU_RX_CAN_CMB1S04_RXCH0           (116U)
#define OXCAN_PDU_RX_CAN_CSR1S04_RXCH0           (117U)
#define OXCAN_PDU_RX_CAN_CSR1S07_RXCH0           (118U)
#define OXCAN_PDU_RX_CAN_DCM1S01_RXCH0           (119U)
#define OXCAN_PDU_RX_CAN_DCM1S03_RXCH0           (120U)
#define OXCAN_PDU_RX_CAN_DCM1S04_RXCH0           (121U)
#define OXCAN_PDU_RX_CAN_DDM1S16_RXCH0           (122U)
#define OXCAN_PDU_RX_CAN_DDM1S20_RXCH0           (123U)
#define OXCAN_PDU_RX_CAN_DDM1S32_RXCH0           (124U)
#define OXCAN_PDU_RX_CAN_DDM1S35_RXCH0           (125U)
#define OXCAN_PDU_RX_CAN_DDM1SFG_RXCH0           (126U)
#define OXCAN_PDU_RX_CAN_DDM1SFH_RXCH0           (127U)
#define OXCAN_PDU_RX_CAN_DKY1S26_RXCH0           (128U)
#define OXCAN_PDU_RX_CAN_DS11S27_RXCH0           (129U)
#define OXCAN_PDU_RX_CAN_DS11S37_RXCH0           (130U)
#define OXCAN_PDU_RX_CAN_DS11S40_RXCH0           (131U)
#define OXCAN_PDU_RX_CAN_DS12F02_RXCH0           (132U)
#define OXCAN_PDU_RX_CAN_DS12F03_RXCH0           (133U)
#define OXCAN_PDU_RX_CAN_DST1S02_RXCH0           (134U)
#define OXCAN_PDU_RX_CAN_EBU1D01_RXCH0           (135U)
#define OXCAN_PDU_RX_CAN_ECT1G01_RXCH0           (136U)
#define OXCAN_PDU_RX_CAN_EHV1E96_RXCH0           (137U)
#define OXCAN_PDU_RX_CAN_EHV1G70_RXCH0           (138U)
#define OXCAN_PDU_RX_CAN_EHV1G71_RXCH0           (139U)
#define OXCAN_PDU_RX_CAN_EHV1S23_RXCH0           (140U)
#define OXCAN_PDU_RX_CAN_EHV1S26_RXCH0           (141U)
#define OXCAN_PDU_RX_CAN_EHV1S31_RXCH0           (142U)
#define OXCAN_PDU_RX_CAN_EHV1S95_RXCH0           (143U)
#define OXCAN_PDU_RX_CAN_EHV1S97_RXCH0           (144U)
#define OXCAN_PDU_RX_CAN_EHV1SL2_RXCH0           (145U)
#define OXCAN_PDU_RX_CAN_EIM1S01_RXCH0           (146U)
#define OXCAN_PDU_RX_CAN_ENG1G13_RXCH0           (147U)
#define OXCAN_PDU_RX_CAN_ENG1G90_RXCH0           (148U)
#define OXCAN_PDU_RX_CAN_ENG1S60_RXCH0           (149U)
#define OXCAN_PDU_RX_CAN_FCM1C03_RXCH0           (150U)
#define OXCAN_PDU_RX_CAN_FCM1S10_RXCH0           (151U)
#define OXCAN_PDU_RX_CAN_FCM1S12_RXCH0           (152U)
#define OXCAN_PDU_RX_CAN_FCM1S39_RXCH0           (153U)
#define OXCAN_PDU_RX_CAN_FCM1S41_RXCH0           (154U)
#define OXCAN_PDU_RX_CAN_FCM1S51_RXCH0           (155U)
#define OXCAN_PDU_RX_CAN_FCM1S52_RXCH0           (156U)
#define OXCAN_PDU_RX_CAN_FCM1S66_RXCH0           (157U)
#define OXCAN_PDU_RX_CAN_FCM1S70_RXCH0           (158U)
#define OXCAN_PDU_RX_CAN_FCM1S79_RXCH0           (159U)
#define OXCAN_PDU_RX_CAN_FCM1S88_RXCH0           (160U)
#define OXCAN_PDU_RX_CAN_FCM1S90_RXCH0           (161U)
#define OXCAN_PDU_RX_CAN_IDT1S07_RXCH0           (162U)
#define OXCAN_PDU_RX_CAN_IDT1S08_RXCH0           (163U)
#define OXCAN_PDU_RX_CAN_IDT1S15_RXCH0           (164U)
#define OXCAN_PDU_RX_CAN_IPA1S05_RXCH0           (165U)
#define OXCAN_PDU_RX_CAN_ITS1S04_RXCH0           (166U)
#define OXCAN_PDU_RX_CAN_ITS1S08_RXCH0           (167U)
#define OXCAN_PDU_RX_CAN_LRS1S01_RXCH0           (168U)
#define OXCAN_PDU_RX_CAN_LRS1S03_RXCH0           (169U)
#define OXCAN_PDU_RX_CAN_LRS1S04_RXCH0           (170U)
#define OXCAN_PDU_RX_CAN_LVN1S01_RXCH0           (171U)
#define OXCAN_PDU_RX_CAN_MET1S33_RXCH0           (172U)
#define OXCAN_PDU_RX_CAN_MET1S38_RXCH0           (173U)
#define OXCAN_PDU_RX_CAN_MET1S47_RXCH0           (174U)
#define OXCAN_PDU_RX_CAN_MET1S55_RXCH0           (175U)
#define OXCAN_PDU_RX_CAN_PDC1G01_RXCH0           (176U)
#define OXCAN_PDU_RX_CAN_PDC1G02_RXCH0           (177U)
#define OXCAN_PDU_RX_CAN_PLG1G15_RXCH0           (178U)
#define OXCAN_PDU_RX_CAN_PLG1G16_RXCH0           (179U)
#define OXCAN_PDU_RX_CAN_PLG1S01_RXCH0           (180U)
#define OXCAN_PDU_RX_CAN_PLG1S06_RXCH0           (181U)
#define OXCAN_PDU_RX_CAN_PLG1S20_RXCH0           (182U)
#define OXCAN_PDU_RX_CAN_PLG1S21_RXCH0           (183U)
#define OXCAN_PDU_RX_CAN_PST1S01_RXCH0           (184U)
#define OXCAN_PDU_RX_CAN_PST1S02_RXCH0           (185U)
#define OXCAN_PDU_RX_CAN_RCP1S01_RXCH0           (186U)
#define OXCAN_PDU_RX_CAN_RCP1S02_RXCH0           (187U)
#define OXCAN_PDU_RX_CAN_RCP1S03_RXCH0           (188U)
#define OXCAN_PDU_RX_CAN_RRS1S01_RXCH0           (189U)
#define OXCAN_PDU_RX_CAN_RRS1S03_RXCH0           (190U)
#define OXCAN_PDU_RX_CAN_RRS1S04_RXCH0           (191U)
#define OXCAN_PDU_RX_CAN_RSE1G24_RXCH0           (192U)
#define OXCAN_PDU_RX_CAN_RSE1G25_RXCH0           (193U)
#define OXCAN_PDU_RX_CAN_RSE1G26_RXCH0           (194U)
#define OXCAN_PDU_RX_CAN_RSE1G29_RXCH0           (195U)
#define OXCAN_PDU_RX_CAN_RSE1S02_RXCH0           (196U)
#define OXCAN_PDU_RX_CAN_RST1S03_RXCH0           (197U)
#define OXCAN_PDU_RX_CAN_SCN1S01_RXCH0           (198U)
#define OXCAN_PDU_RX_CAN_SCS1S11_RXCH0           (199U)
#define OXCAN_PDU_RX_CAN_SCS1S14_RXCH0           (200U)
#define OXCAN_PDU_RX_CAN_SOL1S02_RXCH0           (201U)
#define OXCAN_PDU_RX_CAN_SOL1S03_RXCH0           (202U)
#define OXCAN_PDU_RX_CAN_SOL1S04_RXCH0           (203U)
#define OXCAN_PDU_RX_CAN_SOL1S05_RXCH0           (204U)
#define OXCAN_PDU_RX_CAN_TPM1S02_RXCH0           (205U)
#define OXCAN_PDU_RX_CAN_TPM1S03_RXCH0           (206U)
#define OXCAN_PDU_RX_CAN_TPM1S04_RXCH0           (207U)
#define OXCAN_PDU_RX_CAN_TPM1S05_RXCH0           (208U)
#define OXCAN_PDU_RX_CAN_TPM1S06_RXCH0           (209U)
#define OXCAN_PDU_RX_CAN_TPM1S08_RXCH0           (210U)
#define OXCAN_PDU_RX_CAN_TPM1S09_RXCH0           (211U)
#define OXCAN_PDU_RX_CAN_TPM1S10_RXCH0           (212U)
#define OXCAN_PDU_RX_CAN_TPM1S11_RXCH0           (213U)
#define OXCAN_PDU_RX_CAN_TPM1S12_RXCH0           (214U)
#define OXCAN_PDU_RX_CAN_TRA1S01_RXCH0           (215U)
#define OXCAN_PDU_RX_CAN_TRA1S02_RXCH0           (216U)
#define OXCAN_PDU_RX_CAN_UCB1S01_RXCH0           (217U)
#define OXCAN_PDU_RX_CAN_VSC1G13_RXCH0           (218U)
#define OXCAN_PDU_RX_CAN_VSC1G14_RXCH0           (219U)
#define OXCAN_PDU_RX_CAN_WIP1S01_RXCH0           (220U)
#define OXCAN_PDU_RX_CAN_YGW1S01_RXCH0           (221U)
#define OXCAN_PDU_RX_CAN_ZN11S08_RXCH0           (222U)
#define OXCAN_PDU_RX_CAN_ZN11S14_RXCH0           (223U)
#define OXCAN_PDU_RX_CAN_ZN11S19_RXCH0           (224U)
#define OXCAN_PDU_RX_CAN_ZN11S25_RXCH0           (225U)
#define OXCAN_PDU_RX_CAN_ZN11S26_RXCH0           (226U)
#define OXCAN_PDU_RX_CAN_ZN11S32_RXCH0           (227U)
#define OXCAN_PDU_RX_CAN_ZN11S60_RXCH0           (228U)
#define OXCAN_PDU_RX_CAN_ZN11S63_RXCH0           (229U)
#define OXCAN_PDU_RX_CAN_ZN11S64_RXCH0           (230U)
#define OXCAN_PDU_RX_CAN_ZN11S65_RXCH0           (231U)
#define OXCAN_PDU_RX_CAN_ZN11S66_RXCH0           (232U)
#define OXCAN_PDU_RX_CAN_ZN11S67_RXCH0           (233U)
#define OXCAN_PDU_RX_CAN_ZN11SF6_RXCH0           (234U)
#define OXCAN_PDU_RX_CAN_ZN11SF7_RXCH0           (235U)
#define OXCAN_PDU_RX_CAN_ZN11SF8_RXCH0           (236U)
#define OXCAN_PDU_RX_CAN_ZN11SF9_RXCH0           (237U)
#define OXCAN_PDU_RX_CAN_ZN21S13_RXCH0           (238U)
#define OXCAN_PDU_RX_CAN_ZN21S28_RXCH0           (239U)
#define OXCAN_PDU_RX_CAN_ZN21S72_RXCH0           (240U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_TXRX_NUM_ID                        (1U)
#define OXCAN_TXRX_ID_DIAG                       (0U)
/* #define OXCAN_TXRX_ID_APP                        (1U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_E2E_NUM_PROTECT_MSG                (0U)
#define OXCAN_E2E_NUM_CHECK_MSG                  (0U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_AUB_CXPI_SUP                       (0U)                          /* 1 = Aubist/CXPI is supported, other = not          */
#define OXCAN_AUB_E2E_SUP                        (0U)                          /* 1 = Aubist/E2E  is supported, other = not          */
#define OXCAN_RX_STOP_EN                         (0U)                          /* 1 = Pdu receive stop is enabled, other = not       */
#define OXCAN_NM_TX_STOP_EN                      (0U)                          /* 1 = NM transmission stop is enabled, other = not   */
#define OXCAN_APP_SLPNG_TOE                      (1U)                          /* 1 = Apply SleepNG Timeout is enabled, other = not  */
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
