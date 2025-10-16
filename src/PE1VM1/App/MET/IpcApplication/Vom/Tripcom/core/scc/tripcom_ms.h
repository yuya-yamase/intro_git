/* 2.1.3 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Memory Service for Trip Computer                                                                                                 */
/*                                                                                                                                   */
/*  tripcom_ms.h can only be included from                                                                                           */
/*    - tripcom/core/scc/tripcom_cfg_private.h                                                                                       */
/*    - tripcom/core/scc/tripcom_ms_cfg_private.h                                                                                    */
/*    - tripcom/app/scc/XXX_cfg_private.h                                                                                            */
/*  and an application DOES NOT write other ones data.                                                                               */
/*===================================================================================================================================*/

#ifndef TRIPCOM_MS_H
#define TRIPCOM_MS_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_MS_H_MAJOR                      (2)
#define TRIPCOM_MS_H_MINOR                      (1)
#define TRIPCOM_MS_H_PATCH                      (3)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define TRIPCOM_MS_NUM_ID                    (181U)          defined at tripcom_ms_cfg_private.h */
#define TRIPCOM_MS_ID_AVGFE_TA_FE               ( 0U)
#define TRIPCOM_MS_ID_AVGFE_TA_FU               ( 1U)
#define TRIPCOM_MS_ID_AVGFE_TA_OC               ( 2U)
#define TRIPCOM_MS_ID_AVGFE_DC_FE               ( 3U)
#define TRIPCOM_MS_ID_AVGFE_DC_FU               ( 4U)
#define TRIPCOM_MS_ID_AVGFE_DC_OC               ( 5U)
#define TRIPCOM_MS_ID_AVGFE_RF_FE               ( 6U)
#define TRIPCOM_MS_ID_AVGFE_RF_FU               ( 7U)
#define TRIPCOM_MS_ID_AVGFE_RF_OC               ( 8U)
#define TRIPCOM_MS_ID_AVGFE_ONEM_FE             ( 9U)
#define TRIPCOM_MS_ID_AVGFE_ONEM_FU             (10U)
#define TRIPCOM_MS_ID_AVGFE_ONEM_OC             (11U)
#define TRIPCOM_MS_ID_AVGHE_TA_HE               (12U)
#define TRIPCOM_MS_ID_AVGHE_TA_HU               (13U)
#define TRIPCOM_MS_ID_AVGHE_TA_OC               (14U)
#define TRIPCOM_MS_ID_AVGHE_DC_HE               (15U)
#define TRIPCOM_MS_ID_AVGHE_DC_HU               (16U)
#define TRIPCOM_MS_ID_AVGHE_DC_OC               (17U)
#define TRIPCOM_MS_ID_AVGHE_RF_HE               (18U)
#define TRIPCOM_MS_ID_AVGHE_RF_HU               (19U)
#define TRIPCOM_MS_ID_AVGHE_RF_OC               (20U)
#define TRIPCOM_MS_ID_AVGEE_TA_EE               (21U)
#define TRIPCOM_MS_ID_AVGEE_TA_EU               (22U)
#define TRIPCOM_MS_ID_AVGEE_TA_OC               (23U)
#define TRIPCOM_MS_ID_AVGEE_DC_EE               (24U)
#define TRIPCOM_MS_ID_AVGEE_DC_EU               (25U)
#define TRIPCOM_MS_ID_AVGEE_DC_OC               (26U)
#define TRIPCOM_MS_ID_AVGEE_ONEM_EE             (27U)
#define TRIPCOM_MS_ID_AVGEE_ONEM_EU             (28U)
#define TRIPCOM_MS_ID_AVGEE_ONEM_OC             (29U)
#define TRIPCOM_MS_ID_AVGEE_FIVEM_EE            (30U)
#define TRIPCOM_MS_ID_AVGEE_FIVEM_EU            (31U)
#define TRIPCOM_MS_ID_AVGEE_FIVEM_OC            (32U)
#define TRIPCOM_MS_ID_INSTFE_FE                 (33U)
#define TRIPCOM_MS_ID_INSTFE_FU                 (34U)
#define TRIPCOM_MS_ID_INSTFE_OC                 (35U)
#define TRIPCOM_MS_ID_INSTFE_DV                 (36U)
#define TRIPCOM_MS_ID_INSTHE_HE                 (37U)
#define TRIPCOM_MS_ID_INSTHE_HU                 (38U)
#define TRIPCOM_MS_ID_INSTHE_OC                 (39U)
#define TRIPCOM_MS_ID_INSTHE_DV                 (40U)
#define TRIPCOM_MS_ID_INSTEE_EE                 (41U)
#define TRIPCOM_MS_ID_INSTEE_EU                 (42U)
#define TRIPCOM_MS_ID_INSTEE_OC                 (43U)
#define TRIPCOM_MS_ID_INSTEE_DV                 (44U)
#define TRIPCOM_MS_ID_DTE_OC                    (45U)
#define TRIPCOM_MS_ID_DTE_FE                    (46U)
#define TRIPCOM_MS_ID_EVDTE_OC                  (47U)
#define TRIPCOM_MS_ID_EVDTE_PCT                 (48U)
#define TRIPCOM_MS_ID_AVGVEHSPD_TA_SP           (49U)
#define TRIPCOM_MS_ID_AVGVEHSPD_TA_OC           (50U)
#define TRIPCOM_MS_ID_AVGVEHSPD_TA_ET           (51U)
#define TRIPCOM_MS_ID_AVGVEHSPD_DC_SP           (52U)
#define TRIPCOM_MS_ID_AVGVEHSPD_DC_OC           (53U)
#define TRIPCOM_MS_ID_AVGVEHSPD_DC_ET           (54U)
#define TRIPCOM_MS_ID_SAVEFS_LC_F               (55U)
#define TRIPCOM_MS_ID_SAVEFS_DC_F               (56U)
#define TRIPCOM_MS_ID_ECOSTPTM_LC_ET            (57U)
#define TRIPCOM_MS_ID_ECOSTPTM_DC_ET            (58U)
#define TRIPCOM_MS_ID_ECOSTPTM_ST_ET            (59U)
#define TRIPCOM_MS_ID_PTSRUNTM_LC_ET            (60U)
#define TRIPCOM_MS_ID_PTSRUNTM_DC_ET            (61U)
#define TRIPCOM_MS_ID_PTSRUNDIST_LC_OC          (62U)
#define TRIPCOM_MS_ID_PTSRUNDIST_DC_OC          (63U)
#define TRIPCOM_MS_ID_EVRATIO_DT                (64U)
#define TRIPCOM_MS_ID_EVRATIO_DV                (65U)
#define TRIPCOM_MS_ID_EVRATIO_EV_ET             (66U)
#define TRIPCOM_MS_ID_EVRATIO_NEV_ET            (67U)
#define TRIPCOM_MS_ID_AVGVEHSPD_TR_A_SP         (68U)
#define TRIPCOM_MS_ID_AVGVEHSPD_TR_A_OC         (69U)
#define TRIPCOM_MS_ID_AVGVEHSPD_TR_A_ET         (70U)
#define TRIPCOM_MS_ID_AVGVEHSPD_TR_B_SP         (71U)
#define TRIPCOM_MS_ID_AVGVEHSPD_TR_B_OC         (72U)
#define TRIPCOM_MS_ID_AVGVEHSPD_TR_B_ET         (73U)
#define TRIPCOM_MS_ID_PTSRUNTM_TR_A_ET          (74U)
#define TRIPCOM_MS_ID_PTSRUNTM_TR_B_ET          (75U)
#define TRIPCOM_MS_ID_PTSRUNDIST_TR_A_OC        (76U)
#define TRIPCOM_MS_ID_PTSRUNDIST_TR_B_OC        (77U)
#define TRIPCOM_MS_ID_DTE_ED_U1_CG_STS          (78U)
#define TRIPCOM_MS_ID_DTE_ED_U2_CRSCG           (79U)
#define TRIPCOM_MS_ID_DTE_ED_U4_SPDPLS_CG       (80U)
#define TRIPCOM_MS_ID_DTE_ED_U4_FCP_CG          (81U)
#define TRIPCOM_MS_ID_DTE_ED_U4_CNSM_FUEL       (82U)
#define TRIPCOM_MS_ID_DTE_ED_U1_CRS_STS         (83U)
#define TRIPCOM_MS_ID_DTE_ED_U4_KS_SPPLS        (84U)
#define TRIPCOM_MS_ID_DTE_ED_U2_KH_1KM          (85U)
#define TRIPCOM_MS_ID_DTE_ED_U2_KH_1MI          (86U)
#define TRIPCOM_MS_ID_DTE_ED_U4_KF_SPPLS        (87U)
#define TRIPCOM_MS_ID_DTE_ED_U2_KZ_10CC         (88U)
#define TRIPCOM_MS_ID_DTE_ED_U4_TC              (89U)
#define TRIPCOM_MS_ID_DTE_ED_U2_BLWME_CNT       (90U)
#define TRIPCOM_MS_ID_AVGGRPH_TAFE_FE00         (91U)
#define TRIPCOM_MS_ID_AVGGRPH_TAFE_FE01         (92U)
#define TRIPCOM_MS_ID_AVGGRPH_TAFE_FE02         (93U)
#define TRIPCOM_MS_ID_AVGGRPH_TAFE_FE03         (94U)
#define TRIPCOM_MS_ID_AVGGRPH_TAFE_FE04         (95U)
#define TRIPCOM_MS_ID_AVGGRPH_TAFE_FE05         (96U)
#define TRIPCOM_MS_ID_AVGGRPH_TAFE_DT00         (97U)
#define TRIPCOM_MS_ID_AVGGRPH_TAFE_DT01         (98U)
#define TRIPCOM_MS_ID_AVGGRPH_TAFE_DT02         (99U)
#define TRIPCOM_MS_ID_AVGGRPH_TAFE_DT03         (100U)
#define TRIPCOM_MS_ID_AVGGRPH_TAFE_DT04         (101U)
#define TRIPCOM_MS_ID_AVGGRPH_TAFE_DT05         (102U)
#define TRIPCOM_MS_ID_AVGGRPH_TAFE_LTST         (103U)
#define TRIPCOM_MS_ID_AVGGRPH_TAFE_MAX          (104U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE00         (105U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE01         (106U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE02         (107U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE03         (108U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE04         (109U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE05         (110U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE06         (111U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE07         (112U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE08         (113U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE09         (114U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE10         (115U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE11         (116U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE12         (117U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE13         (118U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE14         (119U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE15         (120U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE16         (121U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE17         (122U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE18         (123U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE19         (124U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE20         (125U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE21         (126U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE22         (127U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE23         (128U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE24         (129U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE25         (130U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE26         (131U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE27         (132U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE28         (133U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_FE29         (134U)
#define TRIPCOM_MS_ID_AVGGRPH_1MFE_LTST         (135U)
#define TRIPCOM_MS_ID_AVGGRPH_TAEE_EE00         (136U)
#define TRIPCOM_MS_ID_AVGGRPH_TAEE_EE01         (137U)
#define TRIPCOM_MS_ID_AVGGRPH_TAEE_EE02         (138U)
#define TRIPCOM_MS_ID_AVGGRPH_TAEE_EE03         (139U)
#define TRIPCOM_MS_ID_AVGGRPH_TAEE_EE04         (140U)
#define TRIPCOM_MS_ID_AVGGRPH_TAEE_EE05         (141U)
#define TRIPCOM_MS_ID_AVGGRPH_TAEE_DT00         (142U)
#define TRIPCOM_MS_ID_AVGGRPH_TAEE_DT01         (143U)
#define TRIPCOM_MS_ID_AVGGRPH_TAEE_DT02         (144U)
#define TRIPCOM_MS_ID_AVGGRPH_TAEE_DT03         (145U)
#define TRIPCOM_MS_ID_AVGGRPH_TAEE_DT04         (146U)
#define TRIPCOM_MS_ID_AVGGRPH_TAEE_DT05         (147U)
#define TRIPCOM_MS_ID_AVGGRPH_TAEE_LTST         (148U)
#define TRIPCOM_MS_ID_AVGGRPH_TAEE_MAX          (149U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE00         (150U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE01         (151U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE02         (152U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE03         (153U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE04         (154U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE05         (155U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE06         (156U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE07         (157U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE08         (158U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE09         (159U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE10         (160U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE11         (161U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE12         (162U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE13         (163U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE14         (164U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE15         (165U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE16         (166U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE17         (167U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE18         (168U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE19         (169U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE20         (170U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE21         (171U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE22         (172U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE23         (173U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE24         (174U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE25         (175U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE26         (176U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE27         (177U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE28         (178U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_EE29         (179U)
#define TRIPCOM_MS_ID_AVGGRPH_1MEE_LTST         (180U)

#define TRIPCOM_MS_NVMSTS_NON                   (0x00U)
#define TRIPCOM_MS_NVMSTS_SUC                   (0x01U)
#define TRIPCOM_MS_NVMSTS_FAIL                  (0x02U)
#define TRIPCOM_MS_NVMSTS_REQ                   (0x04U)
#define TRIPCOM_MS_NVMSTS_WAIT                  (0x08U)

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
void            vd_g_TripcomMsBonInit(void);
void            vd_g_TripcomMsInit(void);
void            vd_g_TripcomMsMainTask(void);
U4              u4_g_TripcomMsGetAccmltVal(const U1 u1_a_ID);
void            vd_g_TripcomMsSetAccmltVal(const U1 u1_a_ID, const U4 u4_a_VAL);
void            vd_g_TripcomMsSetNvmRqst(const U1 u1_a_ID);
void            vd_g_TripcomMsSetNvmRslt(const U1 u1_a_ID, const U1 u1_a_rslt);
void            vd_g_TripcomMsSetNvmGrphRslt(const U1 u1_a_ID, const U1 u1_a_rslt);
void            vd_g_TripcomMsClrRimRslt(void);
U1              u1_g_TripcomMsGetNvmRslt(const U1 u1_a_ID);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* TRIPCOM_MS_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  tripcom_ms.c                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
