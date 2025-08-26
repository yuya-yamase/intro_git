/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Oem eXtention of CAN End to End                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_E2E_CFG_C_MAJOR                    (2U)
#define OXCAN_E2E_CFG_C_MINOR                    (0U)
#define OXCAN_E2E_CFG_C_PATCH                    (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxcan_aubif_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OXCAN_E2E_CFG_C_MAJOR != OXCAN_AUBIF_CFG_H_MAJOR) || \
     (OXCAN_E2E_CFG_C_MINOR != OXCAN_AUBIF_CFG_H_MINOR) || \
     (OXCAN_E2E_CFG_C_PATCH != OXCAN_AUBIF_CFG_H_PATCH))
#error "oxcan_e2e_cfg.c and oxcan_aubif_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Transmission */
#if (OXCAN_E2E_NUM_TRA > 0U)
const U2                           u2_gp_OXCAN_E2E_TRA_BY_PDU[] = {
    (U2)U2_MAX
};
const U1                           u1_gp_OXCAN_E2E_TRA_LEN[OXCAN_E2E_NUM_TRA] = {
    (U1)0U
};
#endif /* #if (OXCAN_E2E_NUM_TRA > 0U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Reception   */
#if (OXCAN_E2E_NUM_REC > 0U)
const U2                           u2_gp_OXCAN_E2E_REC_BY_PDU[] = {

    (U2)0U,                             /* #define MSG_ADC1S14_RXCH0                       (39U) */
    (U2)U2_MAX,                         /* #define MSG_ADC1S15_RXCH0                       (40U) */
    (U2)U2_MAX,                         /* #define MSG_ADC1S16_RXCH0                       (41U) */
    (U2)U2_MAX,                         /* #define MSG_ADC1S17_RXCH0                       (42U) */
    (U2)U2_MAX,                         /* #define MSG_ADC1S27_RXCH0                       (43U) */
    (U2)U2_MAX,                         /* #define MSG_ADC1S31_RXCH0                       (44U) */
    (U2)U2_MAX,                         /* #define MSG_ADU1S03_RXCH0                       (45U) */
    (U2)U2_MAX,                         /* #define MSG_ADU1S05_RXCH0                       (46U) */
    (U2)U2_MAX,                         /* #define MSG_ADU1S06_RXCH0                       (47U) */
    (U2)U2_MAX,                         /* #define MSG_ADU1S07_RXCH0                       (48U) */
    (U2)U2_MAX,                         /* #define MSG_ARS1S01_RXCH0                       (49U) */
    (U2)U2_MAX,                         /* #define MSG_ARS1S90_RXCH0                       (50U) */
    (U2)U2_MAX,                         /* #define MSG_BAT1E45_RXCH0                       (51U) */
    (U2)U2_MAX,                         /* #define MSG_BAT1ED1_RXCH0                       (52U) */
    (U2)U2_MAX,                         /* #define MSG_BAT1ED5_RXCH0                       (53U) */
    (U2)U2_MAX,                         /* #define MSG_BAT1EDA_RXCH0                       (54U) */
    (U2)U2_MAX,                         /* #define MSG_BAT1EDB_RXCH0                       (55U) */
    (U2)U2_MAX,                         /* #define MSG_BAT1S01_RXCH0                       (56U) */
    (U2)U2_MAX,                         /* #define MSG_BAT1S08_RXCH0                       (57U) */
    (U2)U2_MAX,                         /* #define MSG_BAT1S11_RXCH0                       (58U) */
    (U2)U2_MAX,                         /* #define MSG_BAT2ED2_RXCH0                       (59U) */
    (U2)U2_MAX,                         /* #define MSG_BCC1S06_RXCH0                       (60U) */
    (U2)U2_MAX,                         /* #define MSG_BDB1F01_RXCH0                       (61U) */
    (U2)U2_MAX,                         /* #define MSG_BDB1F02_RXCH0                       (62U) */
    (U2)U2_MAX,                         /* #define MSG_BDB1F03_RXCH0                       (63U) */
    (U2)U2_MAX,                         /* #define MSG_BDB1S01_RXCH0                       (64U) */
    (U2)U2_MAX,                         /* #define MSG_BDB1S02_RXCH0                       (65U) */
    (U2)U2_MAX,                         /* #define MSG_BDB1S03_RXCH0                       (66U) */
    (U2)U2_MAX,                         /* #define MSG_BDB1S04_RXCH0                       (67U) */
    (U2)U2_MAX,                         /* #define MSG_BDB1S05_RXCH0                       (68U) */
    (U2)U2_MAX,                         /* #define MSG_BDB1S08_RXCH0                       (69U) */
    (U2)U2_MAX,                         /* #define MSG_BDB1S10_RXCH0                       (70U) */
    (U2)U2_MAX,                         /* #define MSG_BDB1S13_RXCH0                       (71U) */
    (U2)U2_MAX,                         /* #define MSG_BDB1S27_RXCH0                       (72U) */
    (U2)U2_MAX,                         /* #define MSG_BDB1S28_RXCH0                       (73U) */
    (U2)U2_MAX,                         /* #define MSG_BDB1S29_RXCH0                       (74U) */
    (U2)U2_MAX,                         /* #define MSG_BDB1S36_RXCH0                       (75U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S13_RXCH0                       (76U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S23_RXCH0                       (77U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S33_RXCH0                       (78U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S41_RXCH0                       (79U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S45_RXCH0                       (80U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S46_RXCH0                       (81U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S48_RXCH0                       (82U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S52_RXCH0                       (83U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S60_RXCH0                       (84U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S74_RXCH0                       (85U) */
    (U2)1U,                             /* #define MSG_BDC1S81_RXCH0                       (86U) */
    (U2)2U,                             /* #define MSG_BDC1S91_RXCH0                       (87U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S97_RXCH0                       (88U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S98_RXCH0                       (89U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1S99_RXCH0                       (90U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SH8_RXCH0                       (91U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SI1_RXCH0                       (92U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SI2_RXCH0                       (93U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SI3_RXCH0                       (94U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SI4_RXCH0                       (95U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SI5_RXCH0                       (96U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SI6_RXCH0                       (97U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SI7_RXCH0                       (98U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SI8_RXCH0                       (99U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SI9_RXCH0                       (100U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SJ0_RXCH0                       (101U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SJ1_RXCH0                       (102U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SJ2_RXCH0                       (103U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SV1_RXCH0                       (104U) */
    (U2)U2_MAX,                         /* #define MSG_BDC1SV2_RXCH0                       (105U) */
    (U2)U2_MAX,                         /* #define MSG_BDF3S01_RXCH0                       (106U) */
    (U2)U2_MAX,                         /* #define MSG_BDF3S02_RXCH0                       (107U) */
    (U2)U2_MAX,                         /* #define MSG_BDR3S02_RXCH0                       (108U) */
    (U2)U2_MAX,                         /* #define MSG_BKD1S01_RXCH0                       (109U) */
    (U2)U2_MAX,                         /* #define MSG_BKD1S02_RXCH0                       (110U) */
    (U2)U2_MAX,                         /* #define MSG_BSR1S01_RXCH0                       (111U) */
    (U2)U2_MAX,                         /* #define MSG_BSR1S02_RXCH0                       (112U) */
    (U2)U2_MAX,                         /* #define MSG_BSR1S03_RXCH0                       (113U) */
    (U2)U2_MAX,                         /* #define MSG_CMB1S03_RXCH0                       (114U) */
    (U2)U2_MAX,                         /* #define MSG_CMB1S04_RXCH0                       (115U) */
    (U2)U2_MAX,                         /* #define MSG_CSR1G10_RXCH0                       (116U) */
    (U2)U2_MAX,                         /* #define MSG_CSR1S04_RXCH0                       (117U) */
    (U2)U2_MAX,                         /* #define MSG_CSR1S07_RXCH0                       (118U) */
    (U2)U2_MAX,                         /* #define MSG_CSR1S08_RXCH0                       (119U) */
    (U2)U2_MAX,                         /* #define MSG_DDM1S00_RXCH0                       (120U) */
    (U2)U2_MAX,                         /* #define MSG_DDM1S09_RXCH0                       (121U) */
    (U2)U2_MAX,                         /* #define MSG_DDM1S12_RXCH0                       (122U) */
    (U2)U2_MAX,                         /* #define MSG_DDM1S16_RXCH0                       (123U) */
    (U2)3U,                             /* #define MSG_DDM1S17_RXCH0                       (124U) */
    (U2)U2_MAX,                         /* #define MSG_DDM1S32_RXCH0                       (125U) */
    (U2)U2_MAX,                         /* #define MSG_DDM1S35_RXCH0                       (126U) */
    (U2)U2_MAX,                         /* #define MSG_DDM1SFH_RXCH0                       (127U) */
    (U2)U2_MAX,                         /* #define MSG_DKY1S26_RXCH0                       (128U) */
    (U2)U2_MAX,                         /* #define MSG_DMC1S08_RXCH0                       (129U) */
    (U2)U2_MAX,                         /* #define MSG_DRL1S03_RXCH0                       (130U) */
    (U2)U2_MAX,                         /* #define MSG_DRR1S03_RXCH0                       (131U) */
    (U2)U2_MAX,                         /* #define MSG_DS11S27_RXCH0                       (132U) */
    (U2)U2_MAX,                         /* #define MSG_DS11S37_RXCH0                       (133U) */
    (U2)U2_MAX,                         /* #define MSG_DS11S40_RXCH0                       (134U) */
    (U2)U2_MAX,                         /* #define MSG_DS12F02_RXCH0                       (135U) */
    (U2)U2_MAX,                         /* #define MSG_DS12F03_RXCH0                       (136U) */
    (U2)U2_MAX,                         /* #define MSG_DST1S02_RXCH0                       (137U) */
    (U2)U2_MAX,                         /* #define MSG_EBU1D01_RXCH0                       (138U) */
    (U2)U2_MAX,                         /* #define MSG_ECT1G01_RXCH0                       (139U) */
    (U2)U2_MAX,                         /* #define MSG_ECT1G92_RXCH0                       (140U) */
    (U2)U2_MAX,                         /* #define MSG_ECT1S80_RXCH0                       (141U) */
    (U2)U2_MAX,                         /* #define MSG_ECT1S93_RXCH0                       (142U) */
    (U2)U2_MAX,                         /* #define MSG_EHV1E96_RXCH0                       (143U) */
    (U2)U2_MAX,                         /* #define MSG_EHV1F02_RXCH0                       (144U) */
    (U2)U2_MAX,                         /* #define MSG_EHV1F04_RXCH0                       (145U) */
    (U2)U2_MAX,                         /* #define MSG_EHV1G30_RXCH0                       (146U) */
    (U2)U2_MAX,                         /* #define MSG_EHV1S23_RXCH0                       (147U) */
    (U2)U2_MAX,                         /* #define MSG_EHV1S26_RXCH0                       (148U) */
    (U2)U2_MAX,                         /* #define MSG_EHV1S31_RXCH0                       (149U) */
    (U2)U2_MAX,                         /* #define MSG_EHV1S90_RXCH0                       (150U) */
    (U2)U2_MAX,                         /* #define MSG_EHV1S94_RXCH0                       (151U) */
    (U2)U2_MAX,                         /* #define MSG_EHV1S95_RXCH0                       (152U) */
    (U2)U2_MAX,                         /* #define MSG_EHV1S96_RXCH0                       (153U) */
    (U2)U2_MAX,                         /* #define MSG_EHV1S97_RXCH0                       (154U) */
    (U2)U2_MAX,                         /* #define MSG_EHV1S99_RXCH0                       (155U) */
    (U2)U2_MAX,                         /* #define MSG_EHV2G02_RXCH0                       (156U) */
    (U2)U2_MAX,                         /* #define MSG_EHV2G10_RXCH0                       (157U) */
    (U2)U2_MAX,                         /* #define MSG_EHV2G20_RXCH0                       (158U) */
    (U2)U2_MAX,                         /* #define MSG_EHV2G70_RXCH0                       (159U) */
    (U2)U2_MAX,                         /* #define MSG_EIM1S01_RXCH0                       (160U) */
    (U2)U2_MAX,                         /* #define MSG_ENG1C01_RXCH0                       (161U) */
    (U2)U2_MAX,                         /* #define MSG_ENG1C02_RXCH0                       (162U) */
    (U2)U2_MAX,                         /* #define MSG_ENG1D51_RXCH0                       (163U) */
    (U2)U2_MAX,                         /* #define MSG_ENG1D52_RXCH0                       (164U) */
    (U2)U2_MAX,                         /* #define MSG_ENG1D53_RXCH0                       (165U) */
    (U2)U2_MAX,                         /* #define MSG_ENG1D55_RXCH0                       (166U) */
    (U2)U2_MAX,                         /* #define MSG_ENG1D56_RXCH0                       (167U) */
    (U2)U2_MAX,                         /* #define MSG_ENG1D59_RXCH0                       (168U) */
    (U2)U2_MAX,                         /* #define MSG_ENG1D60_RXCH0                       (169U) */
    (U2)U2_MAX,                         /* #define MSG_ENG1G03_RXCH0                       (170U) */
    (U2)U2_MAX,                         /* #define MSG_ENG1G13_RXCH0                       (171U) */
    (U2)U2_MAX,                         /* #define MSG_ENG1G17_RXCH0                       (172U) */
    (U2)U2_MAX,                         /* #define MSG_ENG1G90_RXCH0                       (173U) */
    (U2)U2_MAX,                         /* #define MSG_ENG1G92_RXCH0                       (174U) */
    (U2)U2_MAX,                         /* #define MSG_ENG1S60_RXCH0                       (175U) */
    (U2)U2_MAX,                         /* #define MSG_ENG1S99_RXCH0                       (176U) */
    (U2)U2_MAX,                         /* #define MSG_EPS1D50_RXCH0                       (177U) */
    (U2)U2_MAX,                         /* #define MSG_EPS1S11_RXCH0                       (178U) */
    (U2)4U,                             /* #define MSG_EPS1S90_RXCH0                       (179U) */
    (U2)U2_MAX,                         /* #define MSG_FCM1C01_RXCH0                       (180U) */
    (U2)U2_MAX,                         /* #define MSG_FCM1S10_RXCH0                       (181U) */
    (U2)U2_MAX,                         /* #define MSG_FCM1S12_RXCH0                       (182U) */
    (U2)U2_MAX,                         /* #define MSG_FCM1S39_RXCH0                       (183U) */
    (U2)U2_MAX,                         /* #define MSG_FCM1S40_RXCH0                       (184U) */
    (U2)U2_MAX,                         /* #define MSG_FCM1S41_RXCH0                       (185U) */
    (U2)U2_MAX,                         /* #define MSG_FCM1S49_RXCH0                       (186U) */
    (U2)U2_MAX,                         /* #define MSG_FCM1S51_RXCH0                       (187U) */
    (U2)U2_MAX,                         /* #define MSG_FCM1S52_RXCH0                       (188U) */
    (U2)U2_MAX,                         /* #define MSG_FCM1S58_RXCH0                       (189U) */
    (U2)U2_MAX,                         /* #define MSG_FCM1S70_RXCH0                       (190U) */
    (U2)U2_MAX,                         /* #define MSG_FCM1S76_RXCH0                       (191U) */
    (U2)U2_MAX,                         /* #define MSG_FCM1S78_RXCH0                       (192U) */
    (U2)U2_MAX,                         /* #define MSG_FCM1S79_RXCH0                       (193U) */
    (U2)U2_MAX,                         /* #define MSG_FCM1S90_RXCH0                       (194U) */
    (U2)U2_MAX,                         /* #define MSG_FCM1S92_RXCH0                       (195U) */
    (U2)U2_MAX,                         /* #define MSG_FCM1S95_RXCH0                       (196U) */
    (U2)U2_MAX,                         /* #define MSG_FWD1S10_RXCH0                       (197U) */
    (U2)U2_MAX,                         /* #define MSG_IDT1S02_RXCH0                       (198U) */
    (U2)U2_MAX,                         /* #define MSG_IDT1S07_RXCH0                       (199U) */
    (U2)U2_MAX,                         /* #define MSG_IDT1S15_RXCH0                       (200U) */
    (U2)U2_MAX,                         /* #define MSG_IPA1S05_RXCH0                       (201U) */
    (U2)U2_MAX,                         /* #define MSG_ITS1S01_RXCH0                       (202U) */
    (U2)U2_MAX,                         /* #define MSG_ITS1S04_RXCH0                       (203U) */
    (U2)U2_MAX,                         /* #define MSG_ITS1S05_RXCH0                       (204U) */
    (U2)U2_MAX,                         /* #define MSG_LVN1S01_RXCH0                       (205U) */
    (U2)U2_MAX,                         /* #define MSG_MET1S33_RXCH0                       (206U) */
    (U2)U2_MAX,                         /* #define MSG_MGC1F13_RXCH0                       (207U) */
    (U2)U2_MAX,                         /* #define MSG_PCN1S01_RXCH0                       (208U) */
    (U2)U2_MAX,                         /* #define MSG_PDC1G01_RXCH0                       (209U) */
    (U2)U2_MAX,                         /* #define MSG_PDC1G02_RXCH0                       (210U) */
    (U2)5U                              /* #define MSG_PDS1S01_RXCH0                       (211U) */
};
const U1                           u1_gp_OXCAN_E2E_REC_LEN[OXCAN_E2E_NUM_REC] = {
    (U1)32U,                        /* 0 ADC1S14 32             bytes */
    (U1)21U,                        /* 1 BDC1S81 32 - FV/KZK 11 bytes */
    (U1)21U,                        /* 2 BDC1S91 32 - FV/KZK 11 bytes */
    (U1)32U,                        /* 3 DDM1S17 32             bytes */
    (U1)8U,                         /* 4 EPS1S90  8             bytes */
    (U1)8U                          /* 5 PDS1S01  8             bytes */
};
#endif /* #if (OXCAN_E2E_NUM_REC > 0U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  2.0.0     2/28/2025  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * TN = Takashi Nagai, DENSO                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
