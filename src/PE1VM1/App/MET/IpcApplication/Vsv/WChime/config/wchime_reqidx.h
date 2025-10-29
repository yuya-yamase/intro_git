/* 2.1.0 */
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
#define WCHIME_REQ_IDX_H_MINOR                   (1)
#define WCHIME_REQ_IDX_H_PATCH                   (0)

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
#define WCHIME_NUM_REQ                           (191U)                         /* Number of buzzer request ID                       */

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
#define WCHIME_REQ_IN_BATTRW                     (35U)                          /* MET-H_BATTRW-CSTD-                                */
#define WCHIME_REQ_IN_SCB                        (36U)                          /* MET-S_SCB-CSTD-                                   */
#define WCHIME_REQ_IN_BSM                        (37U)                          /* MET-S_BSM-CSTD-                                   */
#define WCHIME_REQ_IN_LDA                        (38U)                          /* MET-S_LDA-CSTD-                                   */
#define WCHIME_REQ_IN_INFRA_INT                  (39U)                          /* MET-S_ITS-CSTD-                                   */
#define WCHIME_REQ_IN_SMASTA_INT3                (40U)                          /* MET-B_SMASTA-CSTD--                               */
#define WCHIME_REQ_IN_OAA_HFCT                   (41U)                          /* MET-S_OAA-CSTD-                                   */
#define WCHIME_REQ_SI_FCTA                       (42U)                          /* MET-S_FCTA-CSTD-                                  */
#define WCHIME_REQ_IN_CSR_FR_FD                  (43U)                          /* MET-S_CLESON-CSTD-                                */
#define WCHIME_REQ_IN_CSR_RR_FD                  (44U)                          /* MET-S_CLESON-CSTD-                                */
#define WCHIME_REQ_IN_CSR_FRRR_FD                (45U)                          /* MET-S_CLESON-CSTD-                                */
#define WCHIME_REQ_IN_TCHAR_CYCL1                (46U)                          /* MET-S_TCHAR-CSTD--                                */
#define WCHIME_REQ_IN_BRK_FLDLEAK                (47U)                          /* MET-C_BRLV-CSTD-                                  */
#define WCHIME_REQ_IN_STEER_STP                  (48U)                          /* MET-C_STEER-CSTD--                                */
#define WCHIME_REQ_IN_SBLT_FMV                   (49U)                          /* MET-B_SEAREM-CSTD-                                */
#define WCHIME_REQ_IN_ROLAWA_ENST_VRUN           (50U)                          /* MET-P_ROLAWA-CSTD-                                */
#define WCHIME_REQ_SI_SBW_RJCT                   (51U)                          /* MET-D_SBW-CSTD--                                  */
#define WCHIME_REQ_CO_NACCON                     (52U)                          /* MET-H_ONACCN-CSTD-                                */
#define WCHIME_REQ_CO_PEXI_HV_NDBW               (53U)                          /* MET-H_PEXI-CSTD-                                  */
#define WCHIME_REQ_SI_COOTEM                     (54U)                          /* MET-P_COOTEM-CSTD-                                */
#define WCHIME_REQ_CO_ACCHOL                     (55U)                          /* MET-H_ACCHOL-CSTD-                                */
#define WCHIME_REQ_IN_SBW_AUTOP                  (56U)                          /* MET-D_SBW-CSTD--                                  */
#define WCHIME_REQ_SI_RSA_SIGN_CAUTION2          (57U)                          /* MET-S_RSA-CSTD--                                  */
#define WCHIME_REQ_SI_ESWUOC_REL                 (58U)                          /* MET-B_ESWUOC-CSTD-                                */
#define WCHIME_REQ_IN_ADTJA_PTN5                 (59U)                          /* MET-S_ADTJA-CSTD-                                 */
#define WCHIME_REQ_IN_PMAR                       (60U)                          /* MET-S_PMAR-CSTD--                                 */
#define WCHIME_REQ_IN_PKBWAR                     (61U)                          /* MET-C_PKBWAR-CSTD-                                */
#define WCHIME_REQ_CO_SOCLOW_HV                  (62U)                          /* MET-H_SOCLOW-CSTD-                                */
#define WCHIME_REQ_SI_APP_NONOPE_REQ2            (63U)                          /* MET-S_APP-CSTD-                                   */
#define WCHIME_REQ_SI_APP_NONOPE_REQ4            (64U)                          /* MET-S_APP-CSTD-                                   */
#define WCHIME_REQ_IN_OILPRE                     (65U)                          /* MET-P_OILPRE-CSTD-                                */
#define WCHIME_REQ_CO_SYSMAL_RNG_P               (66U)                          /* MET-H_SYSMAL-CSTD-                                */
#define WCHIME_REQ_IN_CHAMAL_BAT_FAIL            (67U)                          /* MET-O_CHAMAL-CSTD-                                */
#define WCHIME_REQ_IN_SYSMAL_REMDST_0M           (68U)                          /* MET-H_SYSMAL-CSTD-                                */
#define WCHIME_REQ_IN_SYSMAL_REQSTP              (69U)                          /* MET-H_SYSMAL-CSTD-                                */
#define WCHIME_REQ_SI_ADTJA_PTN3                 (70U)                          /* MET-S_ADTJA-CSTD-                                 */
#define WCHIME_REQ_IN_EPB                        (71U)                          /* MET-C_EPB-CSTD-                                   */
#define WCHIME_REQ_CO_EIGCON_IGOFF               (72U)                          /* MET-O_EIGCON-CSTD-                                */
#define WCHIME_REQ_SI_SPDL_DISACT                (73U)                          /* MET-H_SPDL-CSTD-                                  */
#define WCHIME_REQ_SI_SFTPOS_NML                 (74U)                          /* MET-D_SFTPOS-CSTD--                               */
#define WCHIME_REQ_SI_ACC_LSPDCNSL               (75U)                          /* MET-S_ACC-CSTD-                                   */
#define WCHIME_REQ_SI_BEVR_DOUBLE                (76U)                          /* MET-H_BEVR-CSTD-                                  */
#define WCHIME_REQ_SI_LTA_CNCL                   (77U)                          /* MET-S_LTA-CSTD-                                   */
#define WCHIME_REQ_SI_SPDL_REJECT                (78U)                          /* MET-H_SPDL-CSTD-                                  */
#define WCHIME_REQ_SI_LCS_CNCL                   (79U)                          /* MET-S_LCA-CSTD-                                   */
#define WCHIME_REQ_SI_APP_DIS_ASSIST             (80U)                          /* MET-S_APP-CSTD-                                   */
#define WCHIME_REQ_SI_APP_CMPLT                  (81U)                          /* MET-S_APP-CSTD-                                   */
#define WCHIME_REQ_SI_DCLDSP_OPERJCT             (82U)                          /* MET-H_DCLDSP-CSTD--                               */
#define WCHIME_REQ_SI_LCS_ACK                    (83U)                          /* MET-S_LCA-CSTD-                                   */
#define WCHIME_REQ_SI_XMDRJT                     (84U)                          /* MET-H_XMDRJT-CSTD--                               */
#define WCHIME_REQ_SI_XMGRIP_DOUBLE              (85U)                          /* MET-H_XMGRIP-CSTD-                                */
#define WCHIME_REQ_SI_X_MODE_DEACTIVATE          (86U)                          /* MET-H_XMODE-CSTD--                                */
#define WCHIME_REQ_SI_X_MODE_REJECT              (87U)                          /* MET-H_XMODE-CSTD--                                */
#define WCHIME_REQ_SI_BSTMOD_REJ                 (88U)                          /* MET-P_BSTMOD-CSTD--                               */
#define WCHIME_REQ_SI_DOA_RJCT                   (89U)                          /* MET-S_SEA-CSTD-                                   */
#define WCHIME_REQ_SI_MET_WRN_VOL_CSTM           (90U)                          /* MET-M_MWVCUS-CSTD-                                */
#define WCHIME_REQ_CO_ROLAWA_ENST_VSTP           (91U)                          /* MET-P_ROLAWA-CSTD-                                */
#define WCHIME_REQ_SI_SBW_SPL_STATE              (92U)                          /* MET-D_SBW-CSTD--                                  */
#define WCHIME_REQ_IN_DMC_LV2                    (93U)                          /* MET-S_DMC-CSTD-                                   */
#define WCHIME_REQ_IN_SFTPOS_REV                 (94U)                          /* MET-D_SFTPOS-CSTD--                               */
#define WCHIME_REQ_IN_SMASTA_INT2                (95U)                          /* MET-B_SMASTA-CSTD--                               */
#define WCHIME_REQ_CO_SMASTA_CON                 (96U)                          /* MET-B_SMASTA-CSTD--                               */
#define WCHIME_REQ_IN_SOCLOW_NPOS                (97U)                          /* MET-H_SOCLOW-CSTD-                                */
#define WCHIME_REQ_CO_STOSTA                     (98U)                          /* MET-P_STOSTA-CSTD--                               */
#define WCHIME_REQ_IN_ACC_BRKREQ                 (99U)                          /* MET-S_ACC-CSTD-                                   */
#define WCHIME_REQ_IN_SBLT_LV2                   (100U)                         /* MET-B_SEAREM-CSTD-                                */
#define WCHIME_REQ_IN_ACC_OVERSPD                (101U)                         /* MET-S_ACC-CSTD-                                   */
#define WCHIME_REQ_SI_ACC_SHIFTREQ               (102U)                         /* MET-S_ACC-CSTD-                                   */
#define WCHIME_REQ_IN_TPMS_CYCL                  (103U)                         /* MET-C_TPMS-CSTD--                                 */
#define WCHIME_REQ_SI_SWS                        (104U)                         /* MET-S_SWS-CSTD-                                   */
#define WCHIME_REQ_IN_MINDSPWR_LV2               (105U)                         /* MET-M_MINDSPWR-CSTD-                              */
#define WCHIME_REQ_IN_BGLFSPD                    (106U)                         /* MET-M_BGLFSPD-CSTD-                               */
#define WCHIME_REQ_IN_DR_OPN                     (107U)                         /* MET-B_BDOOR-CSTD-                                 */
#define WCHIME_REQ_IN_BRK_SYS_MAL                (108U)                         /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_IN_BRK_SYS_NOOPE2             (109U)                         /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_IN_BRK_SYS_NOOPE1             (110U)                         /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_SI_STEER_LMT                  (111U)                         /* MET-C_STEER-CSTD--                                */
#define WCHIME_REQ_SI_HYB_HT                     (112U)                         /* MET-H_UNIOVE-CSTD-                                */
#define WCHIME_REQ_SI_SBW_MAL                    (113U)                         /* MET-D_SBW-CSTD--                                  */
#define WCHIME_REQ_IN_SBW_MAL                    (114U)                         /* MET-D_SBW-CSTD--                                  */
#define WCHIME_REQ_IN_SYSMAL_REMDST_500M         (115U)                         /* MET-H_SYSMAL-CSTD-                                */
#define WCHIME_REQ_IN_SYSMAL_REMDST_1KM          (116U)                         /* MET-H_SYSMAL-CSTD-                                */
#define WCHIME_REQ_IN_LTA_PTN2                   (117U)                         /* MET-S_LTA-CSTD-                                   */
#define WCHIME_REQ_SI_LTA_PTN3                   (118U)                         /* MET-S_LTA-CSTD-                                   */
#define WCHIME_REQ_IN_ADTJA_PTN4                 (119U)                         /* MET-S_ADTJA-CSTD-                                 */
#define WCHIME_REQ_SI_ADTJA_PTN7                 (120U)                         /* MET-S_ADTJA-CSTD-                                 */
#define WCHIME_REQ_SI_MINDSPWR_LV1               (121U)                         /* MET-M_MINDSPWR-CSTD-                              */
#define WCHIME_REQ_IN_SBLT_LV1                   (122U)                         /* MET-B_SEAREM-CSTD-                                */
#define WCHIME_REQ_SI_SBLT                       (123U)                         /* MET-B_SEAREM-CSTD-                                */
#define WCHIME_REQ_SI_GPF                        (124U)                         /* MET-P_GPF-CSTD-                                   */
#define WCHIME_REQ_SI_RSA_SIGN_CTN1_OTH          (125U)                         /* MET-S_RSA-CSTD--                                  */
#define WCHIME_REQ_SI_RSA_SIGN_CTN1_LX           (126U)                         /* MET-S_RSA-CSTD--                                  */
#define WCHIME_REQ_SI_CHKENG                     (127U)                         /* MET-P_CHEENG-CSTD-                                */
#define WCHIME_REQ_SI_DMC_LV1                    (128U)                         /* MET-S_DMC-CSTD-                                   */
#define WCHIME_REQ_SI_ADTJA_PTN2                 (129U)                         /* MET-S_ADTJA-CSTD-                                 */
#define WCHIME_REQ_SI_SYSMAL_FAIL                (130U)                         /* MET-H_SYSMAL-CSTD-                                */
#define WCHIME_REQ_IN_LTA_PTN1                   (131U)                         /* MET-S_LTA-CSTD-                                   */
#define WCHIME_REQ_SI_INFRA_SNGL                 (132U)                         /* MET-S_ITS-CSTD-                                   */
#define WCHIME_REQ_SI_MLT_MSG_OTH                (133U)                         /* MET-G_MULDISPMM-CSTD-                             */
#define WCHIME_REQ_SI_MLT_MSG_LX                 (134U)                         /* MET-G_MULDISPMM-CSTD-                             */
#define WCHIME_REQ_IN_BKEY                       (135U)                         /* MET-B_BKEY-CSTD-                                  */
#define WCHIME_REQ_CO_LIGHT                      (136U)                         /* MET-B_BLGT-CSTD-                                  */
#define WCHIME_REQ_SI_ACC_AUTOSTART              (137U)                         /* MET-S_ACC-CSTD-                                   */
#define WCHIME_REQ_SI_SBW_RCPT                   (138U)                         /* MET-D_SBW-CSTD--                                  */
#define WCHIME_REQ_SI_BEVR_SINGLE                (139U)                         /* MET-H_BEVR-CSTD-                                  */
#define WCHIME_REQ_SI_XMGRIP_SINGLE              (140U)                         /* MET-H_XMGRIP-CSTD-                                */
#define WCHIME_REQ_SI_X_MODE_ON                  (141U)                         /* MET-H_XMODE-CSTD--                                */
#define WCHIME_REQ_SI_DMODE_CHANGE               (142U)                         /* MET-C_SBRDMB-CSTD--                               */
#define WCHIME_REQ_IN_LDA_HFCT                   (143U)                         /* MET-S_LDA-CSTD-                                   */
#define WCHIME_REQ_IN_BATINS                     (144U)                         /* MET-H_BATINS-CSTD-                                */
#define WCHIME_REQ_SI_TPMS_SINGLE                (145U)                         /* MET-C_TPMS-CSTD--                                 */
#define WCHIME_REQ_SI_TCHAR_SNGL                 (146U)                         /* MET-S_TCHAR-CSTD--                                */
#define WCHIME_REQ_IN_LDA_WARN                   (147U)                         /* MET-S_LDA-CSTD-                                   */
#define WCHIME_REQ_SI_SMASTA_SNGL                (148U)                         /* MET-B_SMASTA-CSTD--                               */
#define WCHIME_REQ_IN_TOWWAR                     (149U)                         /* MET-H_TOWWAR-CSTD-                                */
#define WCHIME_REQ_SI_BATCOO                     (150U)                         /* MET-H_BATCOO-CSTD-                                */
#define WCHIME_REQ_SI_TMN_LVN                    (151U)                         /* MET-S_TMN-CSTD-                                   */
#define WCHIME_REQ_IN_SMASTA_INT1                (152U)                         /* MET-B_SMASTA-CSTD--                               */
#define WCHIME_REQ_SI_BRK_APP3                   (153U)                         /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_IN_BRK_APP1                   (154U)                         /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_IN_BRK_APP2                   (155U)                         /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_SI_ADTJA_PTN1                 (156U)                         /* MET-S_ADTJA-CSTD-                                 */
#define WCHIME_REQ_SI_BKHLD_NOTACT_R16           (157U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_NOTREL               (158U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_NOTACT_R07           (159U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_NOTACT_R08           (160U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_NOTACT_R17           (161U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_REL_R10              (162U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_REL_R11              (163U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_NOTACT_R13           (164U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_ACC_APPRVLSTART            (165U)                         /* MET-S_ACC-CSTD-                                   */
#define WCHIME_REQ_SI_PERSET_SUC                 (166U)                         /* MET-B_PERSET-CSTD-                                */
#define WCHIME_REQ_SI_PERSET_FAIL                (167U)                         /* MET-B_PERSET-CSTD-                                */
#define WCHIME_REQ_CO_PERSET_DET                 (168U)                         /* MET-B_PERSET-CSTD-                                */
#define WCHIME_REQ_SI_RSA_CHG_SPLDLMT            (169U)                         /* MET-S_RSA-CSTD--                                  */
#define WCHIME_REQ_SI_FMSEAT_MEM_SCS             (170U)                         /* MET-B_FMSEAT-CSTD--                               */
#define WCHIME_REQ_SI_FMSEAT_MEM_REJ             (171U)                         /* MET-B_FMSEAT-CSTD--                               */
#define WCHIME_REQ_SI_FMSEAT_ERS_INFO            (172U)                         /* MET-B_FMSEAT-CSTD--                               */
#define WCHIME_REQ_SI_FMSEAT_MEM_CALL            (173U)                         /* MET-B_FMSEAT-CSTD--                               */
#define WCHIME_REQ_SI_ESWUOC_RJCT                (174U)                         /* MET-B_ESWUOC-CSTD-                                */
#define WCHIME_REQ_SI_SMASTA_SNGL2               (175U)                         /* MET-B_SMASTA-CSTD--                               */
#define WCHIME_REQ_SI_EV_RJCT_HEAT               (176U)                         /* MET-H_EVMOD-CSTD--                                */
#define WCHIME_REQ_SI_EV_RJCT_BAT                (177U)                         /* MET-H_EVMOD-CSTD--                                */
#define WCHIME_REQ_SI_EV_RJCT_SPD                (178U)                         /* MET-H_EVMOD-CSTD--                                */
#define WCHIME_REQ_SI_EV_RJCT_ACC                (179U)                         /* MET-H_EVMOD-CSTD--                                */
#define WCHIME_REQ_SI_EV_RJCT_OTH                (180U)                         /* MET-H_EVMOD-CSTD--                                */
#define WCHIME_REQ_SI_EV_DCTV_LWBAT              (181U)                         /* MET-H_EVMOD-CSTD--                                */
#define WCHIME_REQ_SI_EV_DCTV_SPD                (182U)                         /* MET-H_EVMOD-CSTD--                                */
#define WCHIME_REQ_SI_EV_DCTV_ACCL               (183U)                         /* MET-H_EVMOD-CSTD--                                */
#define WCHIME_REQ_SI_EV_DCTV                    (184U)                         /* MET-H_EVMOD-CSTD--                                */
#define WCHIME_REQ_SI_TURHAZ_STA_LS              (185U)                         /* MET-B_TURHAZ-CSTD--                               */
#define WCHIME_REQ_SI_TURHAZ_STA_MS              (186U)                         /* MET-B_TURHAZ-CSTD--                               */
#define WCHIME_REQ_SI_TURHAZ_STA_HS              (187U)                         /* MET-B_TURHAZ-CSTD--                               */
#define WCHIME_REQ_SI_TURHAZ_FIN_LS              (188U)                         /* MET-B_TURHAZ-CSTD--                               */
#define WCHIME_REQ_SI_TURHAZ_FIN_MS              (189U)                         /* MET-B_TURHAZ-CSTD--                               */
#define WCHIME_REQ_SI_TURHAZ_FIN_HS              (190U)                         /* MET-B_TURHAZ-CSTD--                               */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define WCHIME_REQBIT_NUM_WORD                   ((WCHIME_NUM_REQ + 31U) >> 5)  /* Number of rows to convert buzzer req. ID to bit.  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define WCHIME_NUM_VOL                           (176U)                /* Number of volume ID                                        */


#define WCHIME_VOL_REVERSE_IN_MID                (0U)                  /* For reverse buzzer Intermittent MID                        */
#define WCHIME_VOL_REVERSE_IN_MAX                (1U)                  /* For reverse buzzer Intermittent MAX                        */
#define WCHIME_VOL_SEAREM_FMV_MID                (2U)                  /* For seatbelt reminder buzzer(fmv MID)                      */
#define WCHIME_VOL_SEAREM_FMV_MAX                (3U)                  /* For seatbelt reminder buzzer(fmv MAX)                      */
#define WCHIME_VOL_SEAREM_LV1_MID                (4U)                  /* For seatbelt reminder buzzer(level 1 MID)                  */
#define WCHIME_VOL_SEAREM_LV1_MAX                (5U)                  /* For seatbelt reminder buzzer(level 1 MAX)                  */
#define WCHIME_VOL_SEAREM_LV2_MID                (6U)                  /* For seatbelt reminder buzzer(level 2 MID)                  */
#define WCHIME_VOL_SEAREM_LV2_MAX                (7U)                  /* For seatbelt reminder buzzer(level 2 MAX)                  */
#define WCHIME_VOL_SEAREM_SI_MID                 (8U)                  /* For seatbelt reminder buzzer(si MID)                       */
#define WCHIME_VOL_SEAREM_SI_MAX                 (9U)                  /* For seatbelt reminder buzzer(si MAX)                       */
#define WCHIME_VOL_MC_MID                        (10U)                 /* For master caution MID                                     */
#define WCHIME_VOL_MC_MAX                        (11U)                 /* For master caution MAX                                     */
#define WCHIME_VOL_ACC_MID                       (12U)                 /* For ACC auto start MID                                     */
#define WCHIME_VOL_ACC_MAX                       (13U)                 /* For ACC auto start MAX                                     */
#define WCHIME_VOL_TMN_MID                       (14U)                 /* For TMN MID                                                */
#define WCHIME_VOL_TMN_MAX                       (15U)                 /* For TMN MAX                                                */
#define WCHIME_VOL_RSA_MID                       (16U)                 /* For RSA buzzer MID(Lexus brand)                            */
#define WCHIME_VOL_RSA_MAX                       (17U)                 /* For RSA buzzer MAX(Lexus brand)                            */
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
#define WCHIME_VOL__800HZ_57DB                   (164U)                /* 800Hz 57dB                                                 */
#define WCHIME_VOL__800HZ_61DB                   (165U)                /* 800Hz 61dB                                                 */
#define WCHIME_VOL__800HZ_63DB                   (166U)                /* 800Hz 63dB                                                 */
#define WCHIME_VOL__800HZ_67DB                   (167U)                /* 800Hz 67dB                                                 */
#define WCHIME_VOL__800HZ_73DB                   (168U)                /* 800Hz 73dB                                                 */
#define WCHIME_VOL_1600HZ_63DB                   (169U)                /* 1600Hz 63dB                                                */
#define WCHIME_VOL_1600HZ_67DB                   (170U)                /* 1600Hz 67dB                                                */
#define WCHIME_VOL_1600HZ_73DB                   (171U)                /* 1600Hz 73dB                                                */
#define WCHIME_VOL_1600HZ_77DB                   (172U)                /* 1600Hz 77dB                                                */
#define WCHIME_VOL_2400HZ_63DB                   (173U)                /* 2400Hz 63dB                                                */
#define WCHIME_VOL_2400HZ_67DB                   (174U)                /* 2400Hz 67dB                                                */
#define WCHIME_VOL_2400HZ_73DB                   (175U)                /* 2400Hz 73dB                                                */

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
