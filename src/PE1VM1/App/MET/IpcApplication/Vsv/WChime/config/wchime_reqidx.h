/* 2.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vehicle Status Viewer / Toyota IPC/MET Warning Chime                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef WCHIME_REQ_IDX_H
#define WCHIME_REQ_IDX_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define WCHIME_REQ_IDX_H_MAJOR                   (2)
#define WCHIME_REQ_IDX_H_MINOR                   (0)
#define WCHIME_REQ_IDX_H_PATCH                   (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define WCHIME_NUM_CH                            (4U)                           /* Number of buzzer CH.                              */

#define WCHIME_CH_00                             (0U)                           /* Buzzer CH 0.                                      */
#define WCHIME_CH_01                             (1U)                           /* Buzzer CH 1.                                      */
#define WCHIME_CH_02                             (2U)                           /* Buzzer CH 2.                                      */
#define WCHIME_CH_03                             (3U)                           /* Buzzer CH 3.                                      */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define WCHIME_NUM_REQ                           (201U)                         /* Number of buzzer request ID                       */

#define WCHIME_REQ_CO_PCS_TSTMD1                 (0U)                           /* MET-S_PCS1-CSTD-                                  */
#define WCHIME_REQ_IN_PCS_TSTMD2                 (1U)                           /* MET-S_PCS1-CSTD-                                  */
#define WCHIME_REQ_IN_PCS_TSTMD3                 (2U)                           /* MET-S_PCS1-CSTD-                                  */
#define WCHIME_REQ_IN_PCS_TSTMD4                 (3U)                           /* MET-S_PCS1-CSTD-                                  */
#define WCHIME_REQ_IN_PCS_TSTMD5                 (4U)                           /* MET-S_PCS1-CSTD-                                  */
#define WCHIME_REQ_IN_PCS_TSTMD6                 (5U)                           /* MET-S_PCS1-CSTD-                                  */
#define WCHIME_REQ_IN_BRK_TST_LRN                (6U)                           /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_SI_BRK_TST_STRT               (7U)                           /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_SI_BRK_TST_FIN                (8U)                           /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_IN_FRRADA_CMP                 (9U)                           /* MET-S_FRRADA-CSTD--                               */
#define WCHIME_REQ_IN_FRRADA_ERR                 (10U)                          /* MET-S_FRRADA-CSTD--                               */
#define WCHIME_REQ_SI_PTS_RDY                    (11U)                          /* MET-H_REASYS-CSTD-                                */
#define WCHIME_REQ_IN_PCS                        (12U)                          /* MET-S_PCS1-CSTD-                                  */
#define WCHIME_REQ_IN_ACC                        (13U)                          /* MET-S_ACC-CSTD-                                   */
#define WCHIME_REQ_IN_STEER_UNDRIVE              (14U)                          /* MET-C_STEER-CSTD--                                */
#define WCHIME_REQ_IN_LCS_APR                    (15U)                          /* MET-S_LCA-CSTD-                                   */
#define WCHIME_REQ_IN_DOA                        (16U)                          /* MET-S_SEA-CSTD-                                   */
#define WCHIME_REQ_CO_CSR_FR_SD                  (17U)                          /* MET-S_CLESON-CSTD-                                */
#define WCHIME_REQ_IN_CSR_FR_MD                  (18U)                          /* MET-S_CLESON-CSTD-                                */
#define WCHIME_REQ_CO_CSR_RR_SD                  (19U)                          /* MET-S_CLESON-CSTD-                                */
#define WCHIME_REQ_IN_CSR_RR_MD                  (20U)                          /* MET-S_CLESON-CSTD-                                */
#define WCHIME_REQ_CO_CSR_FRRR_SD                (21U)                          /* MET-S_CLESON-CSTD-                                */
#define WCHIME_REQ_IN_CSR_FRRR_MD                (22U)                          /* MET-S_CLESON-CSTD-                                */
#define WCHIME_REQ_IN_CSR_RCTA                   (23U)                          /* MET-S_CLESON-CSTD-                                */
#define WCHIME_REQ_IN_PCS_PED                    (24U)                          /* MET-S_PCS1-CSTD-                                  */
#define WCHIME_REQ_IN_FCTA_STEP_STOP             (25U)                          /* MET-S_FCTA-CSTD-                                  */
#define WCHIME_REQ_IN_EDSS_R04                   (26U)                          /* MET-S_EDSS-CSTD-                                  */
#define WCHIME_REQ_IN_CSR_FR_LD                  (27U)                          /* MET-S_CLESON-CSTD-                                */
#define WCHIME_REQ_IN_CSR_RR_LD                  (28U)                          /* MET-S_CLESON-CSTD-                                */
#define WCHIME_REQ_IN_CSR_FRRR_LD                (29U)                          /* MET-S_CLESON-CSTD-                                */
#define WCHIME_REQ_IN_DA                         (30U)                          /* MET-S_DA-CSTD-                                    */
#define WCHIME_REQ_IN_TCHAR_CYCL2                (31U)                          /* MET-S_TCHAR-CSTD--                                */
#define WCHIME_REQ_IN_EDSS_R03                   (32U)                          /* MET-S_EDSS-CSTD-                                  */
#define WCHIME_REQ_IN_ADTJA_PTN6                 (33U)                          /* MET-S_ADTJA-CSTD-                                 */
#define WCHIME_REQ_IN_EIGCON_EG_PWROFF           (34U)                          /* MET-O_EIGCON-CSTD-                                */
#define WCHIME_REQ_IN_SCB                        (35U)                          /* MET-S_SCB-CSTD-                                   */
#define WCHIME_REQ_IN_BSM                        (36U)                          /* MET-S_BSM-CSTD-                                   */
#define WCHIME_REQ_IN_LDA                        (37U)                          /* MET-S_LDA-CSTD-                                   */
#define WCHIME_REQ_IN_INFRA_INT                  (38U)                          /* MET-S_ITS-CSTD-                                   */
#define WCHIME_REQ_IN_SMASTA_INT3                (39U)                          /* MET-B_SMASTA-CSTD--                               */
#define WCHIME_REQ_IN_OAA_HFCT                   (40U)                          /* MET-S_OAA-CSTD-                                   */
#define WCHIME_REQ_SI_FCTA                       (41U)                          /* MET-S_FCTA-CSTD-                                  */
#define WCHIME_REQ_IN_CSR_FR_FD                  (42U)                          /* MET-S_CLESON-CSTD-                                */
#define WCHIME_REQ_IN_CSR_RR_FD                  (43U)                          /* MET-S_CLESON-CSTD-                                */
#define WCHIME_REQ_IN_CSR_FRRR_FD                (44U)                          /* MET-S_CLESON-CSTD-                                */
#define WCHIME_REQ_IN_TCHAR_CYCL1                (45U)                          /* MET-S_TCHAR-CSTD--                                */
#define WCHIME_REQ_IN_BRK_FLDLEAK                (46U)                          /* MET-C_BRLV-CSTD-                                  */
#define WCHIME_REQ_IN_STEER_STP                  (47U)                          /* MET-C_STEER-CSTD--                                */
#define WCHIME_REQ_IN_SBLT_FMV                   (48U)                          /* MET-B_SEAREM-CSTD-                                */
#define WCHIME_REQ_IN_ROLAWA_ENST_VRUN           (49U)                          /* MET-P_ROLAWA-CSTD-                                */
#define WCHIME_REQ_SI_SBW_RJCT                   (50U)                          /* MET-D_SBW-CSTD--                                  */
#define WCHIME_REQ_CO_NACCON                     (51U)                          /* MET-H_ONACCN-CSTD-                                */
#define WCHIME_REQ_CO_PEXI_HV_NDBW               (52U)                          /* MET-H_PEXI-CSTD-                                  */
#define WCHIME_REQ_SI_COOTEM                     (53U)                          /* MET-P_COOTEM-CSTD-                                */
#define WCHIME_REQ_CO_ACCHOL                     (54U)                          /* MET-H_ACCHOL-CSTD-                                */
#define WCHIME_REQ_IN_SBW_AUTOP                  (55U)                          /* MET-D_SBW-CSTD--                                  */
#define WCHIME_REQ_SI_RSA_SIGN_CAUTION2          (56U)                          /* MET-S_RSA-CSTD--                                  */
#define WCHIME_REQ_SI_ESWUOC_REL                 (57U)                          /* MET-B_ESWUOC-CSTD-                                */
#define WCHIME_REQ_IN_ADTJA_PTN5                 (58U)                          /* MET-S_ADTJA-CSTD-                                 */
#define WCHIME_REQ_IN_PMAR                       (59U)                          /* MET-S_PMAR-CSTD--                                 */
#define WCHIME_REQ_IN_PKBWAR                     (60U)                          /* MET-C_PKBWAR-CSTD-                                */
#define WCHIME_REQ_CO_SOCLOW_HV                  (61U)                          /* MET-H_SOCLOW-CSTD-                                */
#define WCHIME_REQ_SI_APP_NONOPE_REQ2            (62U)                          /* MET-S_APP-CSTD-                                   */
#define WCHIME_REQ_SI_APP_NONOPE_REQ4            (63U)                          /* MET-S_APP-CSTD-                                   */
#define WCHIME_REQ_IN_OILPRE                     (64U)                          /* MET-P_OILPRE-CSTD-                                */
#define WCHIME_REQ_CO_SYSMAL_RNG_P               (65U)                          /* MET-H_SYSMAL-CSTD-                                */
#define WCHIME_REQ_IN_CHAMAL_BAT_FAIL            (66U)                          /* MET-O_CHAMAL-CSTD-                                */
#define WCHIME_REQ_IN_SYSMAL_REMDST_0M           (67U)                          /* MET-H_SYSMAL-CSTD-                                */
#define WCHIME_REQ_IN_SYSMAL_REQSTP              (68U)                          /* MET-H_SYSMAL-CSTD-                                */
#define WCHIME_REQ_SI_ADTJA_PTN3                 (69U)                          /* MET-S_ADTJA-CSTD-                                 */
#define WCHIME_REQ_IN_EPB                        (70U)                          /* MET-C_EPB-CSTD-                                   */
#define WCHIME_REQ_CO_EIGCON_IGOFF               (71U)                          /* MET-O_EIGCON-CSTD-                                */
#define WCHIME_REQ_SI_SPDL_DISACT                (72U)                          /* MET-H_SPDL-CSTD-                                  */
#define WCHIME_REQ_SI_SFTPOS_NML                 (73U)                          /* MET-D_SFTPOS-CSTD--                               */
#define WCHIME_REQ_SI_ACC_LSPDCNSL               (74U)                          /* MET-S_ACC-CSTD-                                   */
#define WCHIME_REQ_SI_BEVR_DOUBLE                (75U)                          /* MET-H_BEVR-CSTD-                                  */
#define WCHIME_REQ_SI_LTA_CNCL                   (76U)                          /* MET-S_LTA-CSTD-                                   */
#define WCHIME_REQ_SI_SPDL_REJECT                (77U)                          /* MET-H_SPDL-CSTD-                                  */
#define WCHIME_REQ_SI_LCS_CNCL                   (78U)                          /* MET-S_LCA-CSTD-                                   */
#define WCHIME_REQ_SI_APP_DIS_ASSIST             (79U)                          /* MET-S_APP-CSTD-                                   */
#define WCHIME_REQ_SI_APP_CMPLT                  (80U)                          /* MET-S_APP-CSTD-                                   */
#define WCHIME_REQ_SI_DCLDSP_OPERJCT             (81U)                          /* MET-H_DCLDSP-CSTD--                               */
#define WCHIME_REQ_SI_LCS_ACK                    (82U)                          /* MET-S_LCA-CSTD-                                   */
#define WCHIME_REQ_SI_XMDRJT                     (83U)                          /* MET-H_XMDRJT-CSTD--                               */
#define WCHIME_REQ_SI_XMGRIP_DOUBLE              (84U)                          /* MET-H_XMGRIP-CSTD-                                */
#define WCHIME_REQ_SI_X_MODE_DEACTIVATE          (85U)                          /* MET-H_XMODE-CSTD--                                */
#define WCHIME_REQ_SI_X_MODE_REJECT              (86U)                          /* MET-H_XMODE-CSTD--                                */
#define WCHIME_REQ_SI_BSTMOD_REJ                 (87U)                          /* MET-P_BSTMOD-CSTD--                               */
#define WCHIME_REQ_SI_DOA_RJCT                   (88U)                          /* MET-S_SEA-CSTD-                                   */
#define WCHIME_REQ_SI_MET_WRN_VOL_CSTM           (89U)                          /* MET-M_MWVCUS-CSTD-                                */
#define WCHIME_REQ_CO_ROLAWA_ENST_VSTP           (90U)                          /* MET-P_ROLAWA-CSTD-                                */
#define WCHIME_REQ_SI_SBW_SPL_STATE              (91U)                          /* MET-D_SBW-CSTD--                                  */
#define WCHIME_REQ_IN_DMC_LV2                    (92U)                          /* MET-S_DMC-CSTD-                                   */
#define WCHIME_REQ_IN_SFTPOS_REV                 (93U)                          /* MET-D_SFTPOS-CSTD--                               */
#define WCHIME_REQ_IN_SMASTA_INT2                (94U)                          /* MET-B_SMASTA-CSTD--                               */
#define WCHIME_REQ_CO_SMASTA_CON                 (95U)                          /* MET-B_SMASTA-CSTD--                               */
#define WCHIME_REQ_IN_SOCLOW_NPOS                (96U)                          /* MET-H_SOCLOW-CSTD-                                */
#define WCHIME_REQ_CO_STOSTA                     (97U)                          /* MET-P_STOSTA-CSTD--                               */
#define WCHIME_REQ_IN_ACC_BRKREQ                 (98U)                          /* MET-S_ACC-CSTD-                                   */
#define WCHIME_REQ_IN_SBLT_LV2                   (99U)                          /* MET-B_SEAREM-CSTD-                                */
#define WCHIME_REQ_IN_ACC_OVERSPD                (100U)                         /* MET-S_ACC-CSTD-                                   */
#define WCHIME_REQ_SI_ACC_SHIFTREQ               (101U)                         /* MET-S_ACC-CSTD-                                   */
#define WCHIME_REQ_IN_TPMS_CYCL                  (102U)                         /* MET-C_TPMS-CSTD--                                 */
#define WCHIME_REQ_SI_SWS                        (103U)                         /* MET-S_SWS-CSTD-                                   */
#define WCHIME_REQ_IN_MINDSPWR_LV2               (104U)                         /* MET-M_MINDSPWR-CSTD-                              */
#define WCHIME_REQ_IN_BGLFSPD                    (105U)                         /* MET-M_BGLFSPD-CSTD-                               */
#define WCHIME_REQ_IN_DR_OPN                     (106U)                         /* MET-B_BDOOR-CSTD-                                 */
#define WCHIME_REQ_IN_BRK_SYS_MAL                (107U)                         /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_IN_BRK_SYS_NOOPE2             (108U)                         /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_IN_BRK_SYS_NOOPE1             (109U)                         /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_SI_STEER_LMT                  (110U)                         /* MET-C_STEER-CSTD--                                */
#define WCHIME_REQ_SI_HYB_HT                     (111U)                         /* MET-H_UNIOVE-CSTD-                                */
#define WCHIME_REQ_SI_SBW_MAL                    (112U)                         /* MET-D_SBW-CSTD--                                  */
#define WCHIME_REQ_IN_SBW_MAL                    (113U)                         /* MET-D_SBW-CSTD--                                  */
#define WCHIME_REQ_IN_SYSMAL_REMDST_500M         (114U)                         /* MET-H_SYSMAL-CSTD-                                */
#define WCHIME_REQ_IN_SYSMAL_REMDST_1KM          (115U)                         /* MET-H_SYSMAL-CSTD-                                */
#define WCHIME_REQ_IN_LTA_PTN2                   (116U)                         /* MET-S_LTA-CSTD-                                   */
#define WCHIME_REQ_SI_LTA_PTN3                   (117U)                         /* MET-S_LTA-CSTD-                                   */
#define WCHIME_REQ_IN_ADTJA_PTN4                 (118U)                         /* MET-S_ADTJA-CSTD-                                 */
#define WCHIME_REQ_SI_ADTJA_PTN7                 (119U)                         /* MET-S_ADTJA-CSTD-                                 */
#define WCHIME_REQ_SI_MINDSPWR_LV1               (120U)                         /* MET-M_MINDSPWR-CSTD-                              */
#define WCHIME_REQ_IN_SBLT_LV1                   (121U)                         /* MET-B_SEAREM-CSTD-                                */
#define WCHIME_REQ_SI_SBLT                       (122U)                         /* MET-B_SEAREM-CSTD-                                */
#define WCHIME_REQ_SI_GPF                        (123U)                         /* MET-P_GPF-CSTD-                                   */
#define WCHIME_REQ_SI_RSA_SIGN_CTN1_OTH          (124U)                         /* MET-S_RSA-CSTD--                                  */
#define WCHIME_REQ_SI_RSA_SIGN_CTN1_LX           (125U)                         /* MET-S_RSA-CSTD--                                  */
#define WCHIME_REQ_SI_CHKENG                     (126U)                         /* MET-P_CHEENG-CSTD-                                */
#define WCHIME_REQ_SI_DMC_LV1                    (127U)                         /* MET-S_DMC-CSTD-                                   */
#define WCHIME_REQ_SI_ADTJA_PTN2                 (128U)                         /* MET-S_ADTJA-CSTD-                                 */
#define WCHIME_REQ_SI_SYSMAL_FAIL                (129U)                         /* MET-H_SYSMAL-CSTD-                                */
#define WCHIME_REQ_IN_LTA_PTN1                   (130U)                         /* MET-S_LTA-CSTD-                                   */
#define WCHIME_REQ_SI_INFRA_SNGL                 (131U)                         /* MET-S_ITS-CSTD-                                   */
#define WCHIME_REQ_SI_MLT_MSG                    (132U)                         /* MET-G_MULDISPMM-CSTD-                             */
#define WCHIME_REQ_IN_BKEY                       (133U)                         /* MET-B_BKEY-CSTD-                                  */
#define WCHIME_REQ_CO_LIGHT                      (134U)                         /* MET-B_BLGT-CSTD-                                  */
#define WCHIME_REQ_SI_ACC_AUTOSTART              (135U)                         /* MET-S_ACC-CSTD-                                   */
#define WCHIME_REQ_SI_SBW_RCPT                   (136U)                         /* MET-D_SBW-CSTD--                                  */
#define WCHIME_REQ_SI_BEVR_SINGLE                (137U)                         /* MET-H_BEVR-CSTD-                                  */
#define WCHIME_REQ_SI_XMGRIP_SINGLE              (138U)                         /* MET-H_XMGRIP-CSTD-                                */
#define WCHIME_REQ_SI_X_MODE_ON                  (139U)                         /* MET-H_XMODE-CSTD--                                */
#define WCHIME_REQ_SI_DMODE_CHANGE               (140U)                         /* MET-C_SBRDMB-CSTD--                               */
#define WCHIME_REQ_IN_LDA_HFCT                   (141U)                         /* MET-S_LDA-CSTD-                                   */
#define WCHIME_REQ_IN_BATINS                     (142U)                         /* MET-H_BATINS-CSTD-                                */
#define WCHIME_REQ_SI_TPMS_SINGLE                (143U)                         /* MET-C_TPMS-CSTD--                                 */
#define WCHIME_REQ_SI_TCHAR_SNGL                 (144U)                         /* MET-S_TCHAR-CSTD--                                */
#define WCHIME_REQ_IN_LDA_WARN                   (145U)                         /* MET-S_LDA-CSTD-                                   */
#define WCHIME_REQ_SI_SMASTA_SNGL                (146U)                         /* MET-B_SMASTA-CSTD--                               */
#define WCHIME_REQ_IN_TOWWAR                     (147U)                         /* MET-H_TOWWAR-CSTD-                                */
#define WCHIME_REQ_SI_BATCOO                     (148U)                         /* MET-H_BATCOO-CSTD-                                */
#define WCHIME_REQ_SI_TMN_LVN                    (149U)                         /* MET-S_TMN-CSTD-                                   */
#define WCHIME_REQ_IN_SMASTA_INT1                (150U)                         /* MET-B_SMASTA-CSTD--                               */
#define WCHIME_REQ_SI_BRK_APP3                   (151U)                         /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_IN_BRK_APP1                   (152U)                         /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_IN_BRK_APP2                   (153U)                         /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_SI_ADTJA_PTN1                 (154U)                         /* MET-S_ADTJA-CSTD-                                 */
#define WCHIME_REQ_SI_BKHLD_NOTACT_R16           (155U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_NOTREL               (156U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_NOTACT_R07           (157U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_NOTACT_R08           (158U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_NOTACT_R17           (159U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_REL_R10              (160U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_REL_R11              (161U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_NOTACT_R13           (162U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_ACC_APPRVLSTART            (163U)                         /* MET-S_ACC-CSTD-                                   */
#define WCHIME_REQ_SI_PERSET_SUC                 (164U)                         /* MET-B_PERSET-CSTD-                                */
#define WCHIME_REQ_SI_PERSET_FAIL                (165U)                         /* MET-B_PERSET-CSTD-                                */
#define WCHIME_REQ_CO_PERSET_DET                 (166U)                         /* MET-B_PERSET-CSTD-                                */
#define WCHIME_REQ_SI_RSA_CHG_SPLDLMT            (167U)                         /* MET-S_RSA-CSTD--                                  */
#define WCHIME_REQ_SI_FMSEAT_MEM_SCS             (168U)                         /* MET-B_FMSEAT-CSTD--                               */
#define WCHIME_REQ_SI_FMSEAT_MEM_REJ             (169U)                         /* MET-B_FMSEAT-CSTD--                               */
#define WCHIME_REQ_SI_FMSEAT_ERS_INFO            (170U)                         /* MET-B_FMSEAT-CSTD--                               */
#define WCHIME_REQ_SI_FMSEAT_MEM_CALL            (171U)                         /* MET-B_FMSEAT-CSTD--                               */
#define WCHIME_REQ_SI_ESWUOC_RJCT                (172U)                         /* MET-B_ESWUOC-CSTD-                                */
#define WCHIME_REQ_SI_SMASTA_SNGL2               (173U)                         /* MET-B_SMASTA-CSTD--                               */
#define WCHIME_REQ_SI_EV_RJCT_HEAT               (174U)                         /* MET-H_EVMOD-CSTD--                                */
#define WCHIME_REQ_SI_EV_RJCT_BAT                (175U)                         /* MET-H_EVMOD-CSTD--                                */
#define WCHIME_REQ_SI_EV_RJCT_SPD                (176U)                         /* MET-H_EVMOD-CSTD--                                */
#define WCHIME_REQ_SI_EV_RJCT_ACC                (177U)                         /* MET-H_EVMOD-CSTD--                                */
#define WCHIME_REQ_SI_EV_RJCT_OTH                (178U)                         /* MET-H_EVMOD-CSTD--                                */
#define WCHIME_REQ_SI_EV_DCTV_LWBAT              (179U)                         /* MET-H_EVMOD-CSTD--                                */
#define WCHIME_REQ_SI_EV_DCTV_SPD                (180U)                         /* MET-H_EVMOD-CSTD--                                */
#define WCHIME_REQ_SI_EV_DCTV_ACCL               (181U)                         /* MET-H_EVMOD-CSTD--                                */
#define WCHIME_REQ_SI_EV_DCTV                    (182U)                         /* MET-H_EVMOD-CSTD--                                */
#define WCHIME_REQ_SI_TURHAZ_STA_LC_LS           (183U)                         /* MET-B_TURHAZ-CSTD--                               */
#define WCHIME_REQ_SI_TURHAZ_STA_LC_MS           (184U)                         /* MET-B_TURHAZ-CSTD--                               */
#define WCHIME_REQ_SI_TURHAZ_STA_LC_HS           (185U)                         /* MET-B_TURHAZ-CSTD--                               */
#define WCHIME_REQ_SI_TURHAZ_STA_MC_LS           (186U)                         /* MET-B_TURHAZ-CSTD--                               */
#define WCHIME_REQ_SI_TURHAZ_STA_MC_MS           (187U)                         /* MET-B_TURHAZ-CSTD--                               */
#define WCHIME_REQ_SI_TURHAZ_STA_MC_HS           (188U)                         /* MET-B_TURHAZ-CSTD--                               */
#define WCHIME_REQ_SI_TURHAZ_STA_HC_LS           (189U)                         /* MET-B_TURHAZ-CSTD--                               */
#define WCHIME_REQ_SI_TURHAZ_STA_HC_MS           (190U)                         /* MET-B_TURHAZ-CSTD--                               */
#define WCHIME_REQ_SI_TURHAZ_STA_HC_HS           (191U)                         /* MET-B_TURHAZ-CSTD--                               */
#define WCHIME_REQ_SI_TURHAZ_FIN_LC_LS           (192U)                         /* MET-B_TURHAZ-CSTD--                               */
#define WCHIME_REQ_SI_TURHAZ_FIN_LC_MS           (193U)                         /* MET-B_TURHAZ-CSTD--                               */
#define WCHIME_REQ_SI_TURHAZ_FIN_LC_HS           (194U)                         /* MET-B_TURHAZ-CSTD--                               */
#define WCHIME_REQ_SI_TURHAZ_FIN_MC_LS           (195U)                         /* MET-B_TURHAZ-CSTD--                               */
#define WCHIME_REQ_SI_TURHAZ_FIN_MC_MS           (196U)                         /* MET-B_TURHAZ-CSTD--                               */
#define WCHIME_REQ_SI_TURHAZ_FIN_MC_HS           (197U)                         /* MET-B_TURHAZ-CSTD--                               */
#define WCHIME_REQ_SI_TURHAZ_FIN_HC_LS           (198U)                         /* MET-B_TURHAZ-CSTD--                               */
#define WCHIME_REQ_SI_TURHAZ_FIN_HC_MS           (199U)                         /* MET-B_TURHAZ-CSTD--                               */
#define WCHIME_REQ_SI_TURHAZ_FIN_HC_HS           (200U)                         /* MET-B_TURHAZ-CSTD--                               */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define WCHIME_REQBIT_NUM_WORD                   ((WCHIME_NUM_REQ + 31U) >> 5)  /* Number of rows to convert buzzer req. ID to bit.  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define WCHIME_NUM_VOL                           (177U)                /* Number of volume ID                                        */


#define WCHIME_VOL_SBW_REVERSE_SI_MID            (0U)                  /* For sbw reverse buzzer Single MID                          */
#define WCHIME_VOL_SBW_REVERSE_SI_MAX            (1U)                  /* For sbw reverse buzzer Single MAX                          */
#define WCHIME_VOL_SBW_REVERSE_IN_MID            (2U)                  /* For sbw reverse buzzer Intermittent MID                    */
#define WCHIME_VOL_SBW_REVERSE_IN_MAX            (3U)                  /* For sbw reverse buzzer Intermittent MAX                    */
#define WCHIME_VOL_SEAREM_FMV_MID                (4U)                  /* For seatbelt reminder buzzer(fmv MID)                      */
#define WCHIME_VOL_SEAREM_FMV_MAX                (5U)                  /* For seatbelt reminder buzzer(fmv MAX)                      */
#define WCHIME_VOL_SEAREM_LV1_MID                (6U)                  /* For seatbelt reminder buzzer(level 1 MID)                  */
#define WCHIME_VOL_SEAREM_LV1_MAX                (7U)                  /* For seatbelt reminder buzzer(level 1 MAX)                  */
#define WCHIME_VOL_SEAREM_LV2_MID                (8U)                  /* For seatbelt reminder buzzer(level 2 MID)                  */
#define WCHIME_VOL_SEAREM_LV2_MAX                (9U)                  /* For seatbelt reminder buzzer(level 2 MAX)                  */
#define WCHIME_VOL_SEAREM_SI_MID                 (10U)                 /* For seatbelt reminder buzzer(si MID)                       */
#define WCHIME_VOL_SEAREM_SI_MAX                 (11U)                 /* For seatbelt reminder buzzer(si MAX)                       */
#define WCHIME_VOL_MC_MID                        (12U)                 /* For master caution MID                                     */
#define WCHIME_VOL_MC_MAX                        (13U)                 /* For master caution MAX                                     */
#define WCHIME_VOL_ACC_MID                       (14U)                 /* For ACC auto start MID                                     */
#define WCHIME_VOL_ACC_MAX                       (15U)                 /* For ACC auto start MAX                                     */
#define WCHIME_VOL_TMN_MID                       (16U)                 /* For TMN MID                                                */
#define WCHIME_VOL_TMN_MAX                       (17U)                 /* For TMN MAX                                                */
#define WCHIME_VOL_CSR_FR_SD_0                   (18U)                 /* For Clearance sonar buzzer Fr(SD) CSR_VOL:0                */
#define WCHIME_VOL_CSR_FR_SD_1                   (19U)                 /* For Clearance sonar buzzer Fr(SD) CSR_VOL:1                */
#define WCHIME_VOL_CSR_FR_SD_2                   (20U)                 /* For Clearance sonar buzzer Fr(SD) CSR_VOL:2                */
#define WCHIME_VOL_CSR_FR_SD_3                   (21U)                 /* For Clearance sonar buzzer Fr(SD) CSR_VOL:3                */
#define WCHIME_VOL_CSR_FR_SD_4                   (22U)                 /* For Clearance sonar buzzer Fr(SD) CSR_VOL:4                */
#define WCHIME_VOL_CSR_FR_SD_5                   (23U)                 /* For Clearance sonar buzzer Fr(SD) CSR_VOL:5                */
#define WCHIME_VOL_CSR_FR_SD_6                   (24U)                 /* For Clearance sonar buzzer Fr(SD) CSR_VOL:6                */
#define WCHIME_VOL_CSR_FR_SD_7                   (25U)                 /* For Clearance sonar buzzer Fr(SD) CSR_VOL:7                */
#define WCHIME_VOL_CSR_FR_MD_0                   (26U)                 /* For Clearance sonar buzzer Fr(MD) CSR_VOL:0                */
#define WCHIME_VOL_CSR_FR_MD_1                   (27U)                 /* For Clearance sonar buzzer Fr(MD) CSR_VOL:1                */
#define WCHIME_VOL_CSR_FR_MD_2                   (28U)                 /* For Clearance sonar buzzer Fr(MD) CSR_VOL:2                */
#define WCHIME_VOL_CSR_FR_MD_3                   (29U)                 /* For Clearance sonar buzzer Fr(MD) CSR_VOL:3                */
#define WCHIME_VOL_CSR_FR_MD_4                   (30U)                 /* For Clearance sonar buzzer Fr(MD) CSR_VOL:4                */
#define WCHIME_VOL_CSR_FR_MD_5                   (31U)                 /* For Clearance sonar buzzer Fr(MD) CSR_VOL:5                */
#define WCHIME_VOL_CSR_FR_MD_6                   (32U)                 /* For Clearance sonar buzzer Fr(MD) CSR_VOL:6                */
#define WCHIME_VOL_CSR_FR_MD_7                   (33U)                 /* For Clearance sonar buzzer Fr(MD) CSR_VOL:7                */
#define WCHIME_VOL_CSR_FR_LD_0                   (34U)                 /* For Clearance sonar buzzer Fr(LD) CSR_VOL:0                */
#define WCHIME_VOL_CSR_FR_LD_1                   (35U)                 /* For Clearance sonar buzzer Fr(LD) CSR_VOL:1                */
#define WCHIME_VOL_CSR_FR_LD_2                   (36U)                 /* For Clearance sonar buzzer Fr(LD) CSR_VOL:2                */
#define WCHIME_VOL_CSR_FR_LD_3                   (37U)                 /* For Clearance sonar buzzer Fr(LD) CSR_VOL:3                */
#define WCHIME_VOL_CSR_FR_LD_4                   (38U)                 /* For Clearance sonar buzzer Fr(LD) CSR_VOL:4                */
#define WCHIME_VOL_CSR_FR_LD_5                   (39U)                 /* For Clearance sonar buzzer Fr(LD) CSR_VOL:5                */
#define WCHIME_VOL_CSR_FR_LD_6                   (40U)                 /* For Clearance sonar buzzer Fr(LD) CSR_VOL:6                */
#define WCHIME_VOL_CSR_FR_LD_7                   (41U)                 /* For Clearance sonar buzzer Fr(LD) CSR_VOL:7                */
#define WCHIME_VOL_CSR_FR_FD_0                   (42U)                 /* For Clearance sonar buzzer Fr(FD) CSR_VOL:0                */
#define WCHIME_VOL_CSR_FR_FD_1                   (43U)                 /* For Clearance sonar buzzer Fr(FD) CSR_VOL:1                */
#define WCHIME_VOL_CSR_FR_FD_2                   (44U)                 /* For Clearance sonar buzzer Fr(FD) CSR_VOL:2                */
#define WCHIME_VOL_CSR_FR_FD_3                   (45U)                 /* For Clearance sonar buzzer Fr(FD) CSR_VOL:3                */
#define WCHIME_VOL_CSR_FR_FD_4                   (46U)                 /* For Clearance sonar buzzer Fr(FD) CSR_VOL:4                */
#define WCHIME_VOL_CSR_FR_FD_5                   (47U)                 /* For Clearance sonar buzzer Fr(FD) CSR_VOL:5                */
#define WCHIME_VOL_CSR_FR_FD_6                   (48U)                 /* For Clearance sonar buzzer Fr(FD) CSR_VOL:6                */
#define WCHIME_VOL_CSR_FR_FD_7                   (49U)                 /* For Clearance sonar buzzer Fr(FD) CSR_VOL:7                */
#define WCHIME_VOL_CSR_RR_SD_0                   (50U)                 /* For Clearance sonar buzzer Rr(SD) CSR_VOL:0                */
#define WCHIME_VOL_CSR_RR_SD_1                   (51U)                 /* For Clearance sonar buzzer Rr(SD) CSR_VOL:1                */
#define WCHIME_VOL_CSR_RR_SD_2                   (52U)                 /* For Clearance sonar buzzer Rr(SD) CSR_VOL:2                */
#define WCHIME_VOL_CSR_RR_SD_3                   (53U)                 /* For Clearance sonar buzzer Rr(SD) CSR_VOL:3                */
#define WCHIME_VOL_CSR_RR_SD_4                   (54U)                 /* For Clearance sonar buzzer Rr(SD) CSR_VOL:4                */
#define WCHIME_VOL_CSR_RR_SD_5                   (55U)                 /* For Clearance sonar buzzer Rr(SD) CSR_VOL:5                */
#define WCHIME_VOL_CSR_RR_SD_6                   (56U)                 /* For Clearance sonar buzzer Rr(SD) CSR_VOL:6                */
#define WCHIME_VOL_CSR_RR_SD_7                   (57U)                 /* For Clearance sonar buzzer Rr(SD) CSR_VOL:7                */
#define WCHIME_VOL_CSR_RR_MD_0                   (58U)                 /* For Clearance sonar buzzer Rr(MD) CSR_VOL:0                */
#define WCHIME_VOL_CSR_RR_MD_1                   (59U)                 /* For Clearance sonar buzzer Rr(MD) CSR_VOL:1                */
#define WCHIME_VOL_CSR_RR_MD_2                   (60U)                 /* For Clearance sonar buzzer Rr(MD) CSR_VOL:2                */
#define WCHIME_VOL_CSR_RR_MD_3                   (61U)                 /* For Clearance sonar buzzer Rr(MD) CSR_VOL:3                */
#define WCHIME_VOL_CSR_RR_MD_4                   (62U)                 /* For Clearance sonar buzzer Rr(MD) CSR_VOL:4                */
#define WCHIME_VOL_CSR_RR_MD_5                   (63U)                 /* For Clearance sonar buzzer Rr(MD) CSR_VOL:5                */
#define WCHIME_VOL_CSR_RR_MD_6                   (64U)                 /* For Clearance sonar buzzer Rr(MD) CSR_VOL:6                */
#define WCHIME_VOL_CSR_RR_MD_7                   (65U)                 /* For Clearance sonar buzzer Rr(MD) CSR_VOL:7                */
#define WCHIME_VOL_CSR_RR_LD_0                   (66U)                 /* For Clearance sonar buzzer Rr(LD) CSR_VOL:0                */
#define WCHIME_VOL_CSR_RR_LD_1                   (67U)                 /* For Clearance sonar buzzer Rr(LD) CSR_VOL:1                */
#define WCHIME_VOL_CSR_RR_LD_2                   (68U)                 /* For Clearance sonar buzzer Rr(LD) CSR_VOL:2                */
#define WCHIME_VOL_CSR_RR_LD_3                   (69U)                 /* For Clearance sonar buzzer Rr(LD) CSR_VOL:3                */
#define WCHIME_VOL_CSR_RR_LD_4                   (70U)                 /* For Clearance sonar buzzer Rr(LD) CSR_VOL:4                */
#define WCHIME_VOL_CSR_RR_LD_5                   (71U)                 /* For Clearance sonar buzzer Rr(LD) CSR_VOL:5                */
#define WCHIME_VOL_CSR_RR_LD_6                   (72U)                 /* For Clearance sonar buzzer Rr(LD) CSR_VOL:6                */
#define WCHIME_VOL_CSR_RR_LD_7                   (73U)                 /* For Clearance sonar buzzer Rr(LD) CSR_VOL:7                */
#define WCHIME_VOL_CSR_RR_FD_0                   (74U)                 /* For Clearance sonar buzzer Rr(FD) CSR_VOL:0                */
#define WCHIME_VOL_CSR_RR_FD_1                   (75U)                 /* For Clearance sonar buzzer Rr(FD) CSR_VOL:1                */
#define WCHIME_VOL_CSR_RR_FD_2                   (76U)                 /* For Clearance sonar buzzer Rr(FD) CSR_VOL:2                */
#define WCHIME_VOL_CSR_RR_FD_3                   (77U)                 /* For Clearance sonar buzzer Rr(FD) CSR_VOL:3                */
#define WCHIME_VOL_CSR_RR_FD_4                   (78U)                 /* For Clearance sonar buzzer Rr(FD) CSR_VOL:4                */
#define WCHIME_VOL_CSR_RR_FD_5                   (79U)                 /* For Clearance sonar buzzer Rr(FD) CSR_VOL:5                */
#define WCHIME_VOL_CSR_RR_FD_6                   (80U)                 /* For Clearance sonar buzzer Rr(FD) CSR_VOL:6                */
#define WCHIME_VOL_CSR_RR_FD_7                   (81U)                 /* For Clearance sonar buzzer Rr(FD) CSR_VOL:7                */
#define WCHIME_VOL_CSR_FRRR_SD_0                 (82U)                 /* For Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:0             */
#define WCHIME_VOL_CSR_FRRR_SD_1                 (83U)                 /* For Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:1             */
#define WCHIME_VOL_CSR_FRRR_SD_2                 (84U)                 /* For Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:2             */
#define WCHIME_VOL_CSR_FRRR_SD_3                 (85U)                 /* For Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:3             */
#define WCHIME_VOL_CSR_FRRR_SD_4                 (86U)                 /* For Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:4             */
#define WCHIME_VOL_CSR_FRRR_SD_5                 (87U)                 /* For Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:5             */
#define WCHIME_VOL_CSR_FRRR_SD_6                 (88U)                 /* For Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:6             */
#define WCHIME_VOL_CSR_FRRR_SD_7                 (89U)                 /* For Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:7             */
#define WCHIME_VOL_CSR_FRRR_MD_FR_0              (90U)                 /* For Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:0         */
#define WCHIME_VOL_CSR_FRRR_MD_FR_1              (91U)                 /* For Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:1         */
#define WCHIME_VOL_CSR_FRRR_MD_FR_2              (92U)                 /* For Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:2         */
#define WCHIME_VOL_CSR_FRRR_MD_FR_3              (93U)                 /* For Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:3         */
#define WCHIME_VOL_CSR_FRRR_MD_FR_4              (94U)                 /* For Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:4         */
#define WCHIME_VOL_CSR_FRRR_MD_FR_5              (95U)                 /* For Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:5         */
#define WCHIME_VOL_CSR_FRRR_MD_FR_6              (96U)                 /* For Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:6         */
#define WCHIME_VOL_CSR_FRRR_MD_FR_7              (97U)                 /* For Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:7         */
#define WCHIME_VOL_CSR_FRRR_MD_RR_0              (98U)                 /* For Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:0         */
#define WCHIME_VOL_CSR_FRRR_MD_RR_1              (99U)                 /* For Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:1         */
#define WCHIME_VOL_CSR_FRRR_MD_RR_2              (100U)                /* For Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:2         */
#define WCHIME_VOL_CSR_FRRR_MD_RR_3              (101U)                /* For Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:3         */
#define WCHIME_VOL_CSR_FRRR_MD_RR_4              (102U)                /* For Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:4         */
#define WCHIME_VOL_CSR_FRRR_MD_RR_5              (103U)                /* For Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:5         */
#define WCHIME_VOL_CSR_FRRR_MD_RR_6              (104U)                /* For Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:6         */
#define WCHIME_VOL_CSR_FRRR_MD_RR_7              (105U)                /* For Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:7         */
#define WCHIME_VOL_CSR_FRRR_LD_FR_0              (106U)                /* For Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:0         */
#define WCHIME_VOL_CSR_FRRR_LD_FR_1              (107U)                /* For Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:1         */
#define WCHIME_VOL_CSR_FRRR_LD_FR_2              (108U)                /* For Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:2         */
#define WCHIME_VOL_CSR_FRRR_LD_FR_3              (109U)                /* For Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:3         */
#define WCHIME_VOL_CSR_FRRR_LD_FR_4              (110U)                /* For Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:4         */
#define WCHIME_VOL_CSR_FRRR_LD_FR_5              (111U)                /* For Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:5         */
#define WCHIME_VOL_CSR_FRRR_LD_FR_6              (112U)                /* For Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:6         */
#define WCHIME_VOL_CSR_FRRR_LD_FR_7              (113U)                /* For Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:7         */
#define WCHIME_VOL_CSR_FRRR_LD_RR_0              (114U)                /* For Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:0         */
#define WCHIME_VOL_CSR_FRRR_LD_RR_1              (115U)                /* For Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:1         */
#define WCHIME_VOL_CSR_FRRR_LD_RR_2              (116U)                /* For Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:2         */
#define WCHIME_VOL_CSR_FRRR_LD_RR_3              (117U)                /* For Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:3         */
#define WCHIME_VOL_CSR_FRRR_LD_RR_4              (118U)                /* For Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:4         */
#define WCHIME_VOL_CSR_FRRR_LD_RR_5              (119U)                /* For Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:5         */
#define WCHIME_VOL_CSR_FRRR_LD_RR_6              (120U)                /* For Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:6         */
#define WCHIME_VOL_CSR_FRRR_LD_RR_7              (121U)                /* For Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:7         */
#define WCHIME_VOL_CSR_FRRR_FD_FR_0              (122U)                /* For Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:0         */
#define WCHIME_VOL_CSR_FRRR_FD_FR_1              (123U)                /* For Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:1         */
#define WCHIME_VOL_CSR_FRRR_FD_FR_2              (124U)                /* For Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:2         */
#define WCHIME_VOL_CSR_FRRR_FD_FR_3              (125U)                /* For Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:3         */
#define WCHIME_VOL_CSR_FRRR_FD_FR_4              (126U)                /* For Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:4         */
#define WCHIME_VOL_CSR_FRRR_FD_FR_5              (127U)                /* For Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:5         */
#define WCHIME_VOL_CSR_FRRR_FD_FR_6              (128U)                /* For Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:6         */
#define WCHIME_VOL_CSR_FRRR_FD_FR_7              (129U)                /* For Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:7         */
#define WCHIME_VOL_CSR_FRRR_FD_RR_0              (130U)                /* For Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:0         */
#define WCHIME_VOL_CSR_FRRR_FD_RR_1              (131U)                /* For Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:1         */
#define WCHIME_VOL_CSR_FRRR_FD_RR_2              (132U)                /* For Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:2         */
#define WCHIME_VOL_CSR_FRRR_FD_RR_3              (133U)                /* For Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:3         */
#define WCHIME_VOL_CSR_FRRR_FD_RR_4              (134U)                /* For Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:4         */
#define WCHIME_VOL_CSR_FRRR_FD_RR_5              (135U)                /* For Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:5         */
#define WCHIME_VOL_CSR_FRRR_FD_RR_6              (136U)                /* For Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:6         */
#define WCHIME_VOL_CSR_FRRR_FD_RR_7              (137U)                /* For Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:7         */
#define WCHIME_VOL_TURHAZ_STA_LCSTM_LSPD         (138U)                /* For flasher start sound(customize: low, low speed)         */
#define WCHIME_VOL_TURHAZ_STA_LCSTM_MSPD         (139U)                /* For flasher start sound(customize: low, middle speed)      */
#define WCHIME_VOL_TURHAZ_STA_LCSTM_HSPD         (140U)                /* For flasher start sound(customize: low, high speed)        */
#define WCHIME_VOL_TURHAZ_STA_MCSTM_LSPD         (141U)                /* For flasher start sound(customize: middle, low speed)      */
#define WCHIME_VOL_TURHAZ_STA_MCSTM_MSPD         (142U)                /* For flasher start sound(customize: middle, middle speed)   */
#define WCHIME_VOL_TURHAZ_STA_MCSTM_HSPD         (143U)                /* For flasher start sound(customize: middle, high speed)     */
#define WCHIME_VOL_TURHAZ_STA_HCSTM_LSPD         (144U)                /* For flasher start sound(customize: high, low speed)        */
#define WCHIME_VOL_TURHAZ_STA_HCSTM_MSPD         (145U)                /* For flasher start sound(customize: high, middle speed)     */
#define WCHIME_VOL_TURHAZ_STA_HCSTM_HSPD         (146U)                /* For flasher start sound(customize: high, high speed)       */
#define WCHIME_VOL_TURHAZ_FIN_LCSTM_LSPD         (147U)                /* For flasher finish sound(customize: low, low speed)        */
#define WCHIME_VOL_TURHAZ_FIN_LCSTM_MSPD         (148U)                /* For flasher finish sound(customize: low, middle speed)     */
#define WCHIME_VOL_TURHAZ_FIN_LCSTM_HSPD         (149U)                /* For flasher finish sound(customize: low, high speed)       */
#define WCHIME_VOL_TURHAZ_FIN_MCSTM_LSPD         (150U)                /* For flasher finish sound(customize: middle, low speed)     */
#define WCHIME_VOL_TURHAZ_FIN_MCSTM_MSPD         (151U)                /* For flasher finish sound(customize: middle, middle speed)  */
#define WCHIME_VOL_TURHAZ_FIN_MCSTM_HSPD         (152U)                /* For flasher finish sound(customize: middle, high speed)    */
#define WCHIME_VOL_TURHAZ_FIN_HCSTM_LSPD         (153U)                /* For flasher finish sound(customize: high, low speed)       */
#define WCHIME_VOL_TURHAZ_FIN_HCSTM_MSPD         (154U)                /* For flasher finish sound(customize: high, middle speed)    */
#define WCHIME_VOL_TURHAZ_FIN_HCSTM_HSPD         (155U)                /* For flasher finish sound(customize: high, high speed)      */
#define WCHIME_VOL_CSR_RCTA_0                    (156U)                /* For RCTA buzzer(from CSR ECU) CSR_VOL:0                    */
#define WCHIME_VOL_CSR_RCTA_1                    (157U)                /* For RCTA buzzer(from CSR ECU) CSR_VOL:1                    */
#define WCHIME_VOL_CSR_RCTA_2                    (158U)                /* For RCTA buzzer(from CSR ECU) CSR_VOL:2                    */
#define WCHIME_VOL_CSR_RCTA_3                    (159U)                /* For RCTA buzzer(from CSR ECU) CSR_VOL:3                    */
#define WCHIME_VOL_CSR_RCTA_4                    (160U)                /* For RCTA buzzer(from CSR ECU) CSR_VOL:4                    */
#define WCHIME_VOL_CSR_RCTA_5                    (161U)                /* For RCTA buzzer(from CSR ECU) CSR_VOL:5                    */
#define WCHIME_VOL_CSR_RCTA_6                    (162U)                /* For RCTA buzzer(from CSR ECU) CSR_VOL:6                    */
#define WCHIME_VOL_CSR_RCTA_7                    (163U)                /* For RCTA buzzer(from CSR ECU) CSR_VOL:7                    */
#define WCHIME_VOL_RSA                           (164U)                /* For RSA buzzer(Lexus brand)                                */
#define WCHIME_VOL__800HZ_57DB                   (165U)                /* 800Hz 57dB                                                 */
#define WCHIME_VOL__800HZ_61DB                   (166U)                /* 800Hz 61dB                                                 */
#define WCHIME_VOL__800HZ_63DB                   (167U)                /* 800Hz 63dB                                                 */
#define WCHIME_VOL__800HZ_67DB                   (168U)                /* 800Hz 67dB                                                 */
#define WCHIME_VOL__800HZ_73DB                   (169U)                /* 800Hz 73dB                                                 */
#define WCHIME_VOL_1600HZ_63DB                   (170U)                /* 1600Hz 63dB                                                */
#define WCHIME_VOL_1600HZ_67DB                   (171U)                /* 1600Hz 67dB                                                */
#define WCHIME_VOL_1600HZ_73DB                   (172U)                /* 1600Hz 73dB                                                */
#define WCHIME_VOL_1600HZ_77DB                   (173U)                /* 1600Hz 77dB                                                */
#define WCHIME_VOL_2400HZ_63DB                   (174U)                /* 2400Hz 63dB                                                */
#define WCHIME_VOL_2400HZ_67DB                   (175U)                /* 2400Hz 67dB                                                */
#define WCHIME_VOL_2400HZ_73DB                   (176U)                /* 2400Hz 73dB                                                */

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

#endif      /* WCHIME_REQ_IDX_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  wchime_arb_cfg.c                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
