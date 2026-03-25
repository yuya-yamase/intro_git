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
#define WCHIME_NUM_REQ                           (178U)                         /* Number of buzzer request ID                       */

#define WCHIME_REQ_CO_PCS_TSTMD1                 (0U)                           /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_PCS_TSTMD5                 (1U)                           /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_PCS_TSTMD6                 (2U)                           /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_FRRADA_CMP                 (3U)                           /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_FRRADA_ERR                 (4U)                           /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_PTS_RDY                    (5U)                           /* MET-H_REASYS-CSTD-                                */
#define WCHIME_REQ_IN_PCS                        (6U)                           /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_ACC                        (7U)                           /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_STEER_UNDRIVE              (8U)                           /* MET-C_STEER-CSTD-                                 */
#define WCHIME_REQ_IN_LCS_APR                    (9U)                           /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_TMBZR_TEN_PRI8             (10U)                          /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_IN_DOA                        (11U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_CO_CSR_FR_SD                  (12U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_CSR_FR_MD                  (13U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_CO_CSR_RR_SD                  (14U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_CSR_RR_MD                  (15U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_CO_CSR_FRRR_SD                (16U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_CSR_FRRR_MD                (17U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_CSR_RCTA                   (18U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_SYSMAL_REMDST_0M           (19U)                          /* MET-H_SYSMAL-CSTD-                                */
#define WCHIME_REQ_IN_TCW_BUZ                    (20U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_PCS_PED                    (21U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_FCTA_STEP_STOP             (22U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_EDSS_R04                   (23U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_CSR_FR_LD                  (24U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_CSR_RR_LD                  (25U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_CSR_FRRR_LD                (26U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_DA                         (27U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_TCHAR_CYCL2                (28U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_TMBZR_TEN_PRI7             (29U)                          /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_IN_EDSS_R03                   (30U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_TMBZR_TEN_PRI6P5           (31U)                          /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_IN_EIGCON_EG_PWROFF           (32U)                          /* MET-O_EIGCON-CSTD-                                */
#define WCHIME_REQ_IN_BATTRW                     (33U)                          /* MET-H_BATTRW-CSTD-                                */
#define WCHIME_REQ_IN_SCB                        (34U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_BSM                        (35U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_LDA                        (36U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_INFRA_INT                  (37U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_SMASTA_INT3                (38U)                          /* MET-B_SMASTA-CSTD-                                */
#define WCHIME_REQ_IN_CSR_FR_FD                  (39U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_CSR_RR_FD                  (40U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_CSR_FRRR_FD                (41U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_TCHAR_CYCL1                (42U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_BRK_FLDLEAK                (43U)                          /* MET-C_BRLV-CSTD-                                  */
#define WCHIME_REQ_IN_STEER_STP                  (44U)                          /* MET-C_STEER-CSTD-                                 */
#define WCHIME_REQ_IN_TMBZR_TEN_PRI6             (45U)                          /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_IN_SBLT_FMV                   (46U)                          /* MET-B_SEAREM-CSTD--                               */
#define WCHIME_REQ_IN_ACC_BRKREQ                 (47U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_SBW_RJCT                   (48U)                          /* MET-D_SBW-CSTD-                                   */
#define WCHIME_REQ_CO_NACCON                     (49U)                          /* MET-H_ONACCN-CSTD-                                */
#define WCHIME_REQ_CO_PEXI_HV_NDBW               (50U)                          /* MET-H_PEXI-CSTD-                                  */
#define WCHIME_REQ_CO_ACCHOL                     (51U)                          /* MET-H_ACCHOL-CSTD-                                */
#define WCHIME_REQ_IN_SBW_AUTOP                  (52U)                          /* MET-D_SBW-CSTD-                                   */
#define WCHIME_REQ_IN_RSA_SIGN_CAUTION2          (53U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_ESWUOC_REL                 (54U)                          /* MET-B_ESWUOC-CSTD-                                */
#define WCHIME_REQ_IN_PMAR                       (55U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_BRK_APP6                   (56U)                          /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_CO_SYSMAL_RNG_P               (57U)                          /* MET-H_SYSMAL-CSTD-                                */
#define WCHIME_REQ_IN_CHAMAL_BAT_FAIL            (58U)                          /* MET-O_CHAMAL-CSTD-                                */
#define WCHIME_REQ_IN_SYSMAL_REQSTP              (59U)                          /* MET-H_SYSMAL-CSTD-                                */
#define WCHIME_REQ_IN_BRK_APP4                   (60U)                          /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_CO_TMBZR_CONT_PRI5            (61U)                          /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_IN_TMBZR_TEN_PRI5             (62U)                          /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_IN_EPB                        (63U)                          /* MET-C_EPB-CSTD-                                   */
#define WCHIME_REQ_CO_EIGCON_IGOFF               (64U)                          /* MET-O_EIGCON-CSTD-                                */
#define WCHIME_REQ_SI_ACC_LSPDCNSL               (65U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_LTA_CNCL                   (66U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_LCS_CNCL                   (67U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_TMBZR_ANN_PRI4P5           (68U)                          /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_SI_TMBZR_RCV_PRI4P5           (69U)                          /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_SI_TMBZR_RJT_PRI4P5           (70U)                          /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_SI_SFTPOS_NML                 (71U)                          /* MET-D_SFTPOS-CSTD-                                */
#define WCHIME_REQ_SI_APP_DIS_ASSIST             (72U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_APP_CMPLT                  (73U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_DCLDSP_OPERJCT             (74U)                          /* MET-H_DCLDSP-CSTD-                                */
#define WCHIME_REQ_SI_LCS_ACK                    (75U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_BSTMOD_RJCT                (76U)                          /* MET-P_BSTMOD-CSTD-                                */
#define WCHIME_REQ_SI_DOA_RJCT                   (77U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_MET_WRN_VOL_CSTM           (78U)                          /* MET-M_MWVCUS-CSTD-                                */
#define WCHIME_REQ_SI_SBW_SPL_STATE              (79U)                          /* MET-D_SBW-CSTD-                                   */
#define WCHIME_REQ_IN_EDSS_WRN_BUZ               (80U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_DMC_LV2                    (81U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_SFTPOS_REV                 (82U)                          /* MET-D_SFTPOS-CSTD-                                */
#define WCHIME_REQ_IN_SMASTA_INT2                (83U)                          /* MET-B_SMASTA-CSTD-                                */
#define WCHIME_REQ_CO_SMASTA_CON                 (84U)                          /* MET-B_SMASTA-CSTD-                                */
#define WCHIME_REQ_IN_SBLT_LV2                   (85U)                          /* MET-B_SEAREM-CSTD--                               */
#define WCHIME_REQ_IN_ACC_OVERSPD                (86U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_ACC_SHIFTREQ               (87U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_TPMS_CYCL                  (88U)                          /* MET-C_TPMS-CSTD-                                  */
#define WCHIME_REQ_SI_SWS                        (89U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_MINDSPWR_LV2               (90U)                          /* MET-M_MINDSPWR-CSTD-                              */
#define WCHIME_REQ_IN_BGLFSPD                    (91U)                          /* MET-M_BGLFSPD-CSTD-                               */
#define WCHIME_REQ_IN_DR_OPN                     (92U)                          /* MET-B_BDOOR-CSTD-                                 */
#define WCHIME_REQ_IN_BRK_SYS_MAL                (93U)                          /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_IN_BRK_SYS_NOOPE2             (94U)                          /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_IN_BRK_SYS_NOOPE1             (95U)                          /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_SI_STEER_LMT                  (96U)                          /* MET-C_STEER-CSTD-                                 */
#define WCHIME_REQ_SI_SBW_MAL                    (97U)                          /* MET-D_SBW-CSTD-                                   */
#define WCHIME_REQ_IN_SBW_MAL                    (98U)                          /* MET-D_SBW-CSTD-                                   */
#define WCHIME_REQ_IN_SYSMAL_REMDST_500M         (99U)                          /* MET-H_SYSMAL-CSTD-                                */
#define WCHIME_REQ_IN_SYSMAL_REMDST_1KM          (100U)                         /* MET-H_SYSMAL-CSTD-                                */
#define WCHIME_REQ_IN_LTA_PTN2                   (101U)                         /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_LTA_PTN3                   (102U)                         /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_TMBZR_ANN_PRI4             (103U)                         /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_SI_TMBZR_RCV_PRI4             (104U)                         /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_SI_TMBZR_RJT_PRI4             (105U)                         /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_CO_TMBZR_CONT_PRI4            (106U)                         /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_IN_TMBZR_TEN_PRI4             (107U)                         /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_SI_MINDSPWR_LV1               (108U)                         /* MET-M_MINDSPWR-CSTD-                              */
#define WCHIME_REQ_IN_SBLT_LV1                   (109U)                         /* MET-B_SEAREM-CSTD--                               */
#define WCHIME_REQ_IN_SBLT_MISUSE                (110U)                         /* MET-B_OPTMON-CSTD-                                */
#define WCHIME_REQ_SI_SBLT                       (111U)                         /* MET-B_SEAREM-CSTD--                               */
#define WCHIME_REQ_SI_RSA_SIGN_CTN1              (112U)                         /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_DMC_LV1                    (113U)                         /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_SYSMAL_FAIL                (114U)                         /* MET-H_SYSMAL-CSTD-                                */
#define WCHIME_REQ_IN_PDSMAL                     (115U)                         /* MET-O_PDSMAL-CST0                                 */
#define WCHIME_REQ_IN_LTA_PTN1                   (116U)                         /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_INFRA_SNGL                 (117U)                         /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_MLT_MSG                    (118U)                         /* MET-G_MULDISPMM-CSTD-                             */
#define WCHIME_REQ_SI_TMBZR_ANN_PRI3             (119U)                         /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_SI_TMBZR_RCV_PRI3             (120U)                         /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_SI_TMBZR_RJT_PRI3             (121U)                         /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_CO_TMBZR_CONT_PRI3            (122U)                         /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_IN_TMBZR_TEN_PRI3             (123U)                         /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_SI_ACC_AUTOSTART              (124U)                         /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_CO_LIGHT                      (125U)                         /* MET-B_BLGT-CSTD-                                  */
#define WCHIME_REQ_SI_SBW_RCPT                   (126U)                         /* MET-D_SBW-CSTD-                                   */
#define WCHIME_REQ_IN_TMBZR_DOHREQ               (127U)                         /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_IN_LDA_HFCT                   (128U)                         /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_BATINS                     (129U)                         /* MET-H_BATINS-CSTD-                                */
#define WCHIME_REQ_SI_TPMS_SINGLE                (130U)                         /* MET-C_TPMS-CSTD-                                  */
#define WCHIME_REQ_SI_TCHAR_SNGL                 (131U)                         /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_LDA_WARN                   (132U)                         /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_SMASTA_SNGL                (133U)                         /* MET-B_SMASTA-CSTD-                                */
#define WCHIME_REQ_IN_TOWWAR                     (134U)                         /* MET-H_TOWWAR-CSTD-                                */
#define WCHIME_REQ_SI_TMN_LVN                    (135U)                         /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_TMBZR_ANN_PRI2             (136U)                         /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_SI_TMBZR_RCV_PRI2             (137U)                         /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_SI_TMBZR_RJT_PRI2             (138U)                         /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_CO_TMBZR_CONT_PRI2            (139U)                         /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_IN_TMBZR_TEN_PRI2             (140U)                         /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_IN_SMASTA_INT1                (141U)                         /* MET-B_SMASTA-CSTD-                                */
#define WCHIME_REQ_SI_BRK_APP3                   (142U)                         /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_IN_BRK_APP1                   (143U)                         /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_IN_BRK_APP2                   (144U)                         /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_SI_BKHLD_NOTACT_R16           (145U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_NOTREL               (146U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_NOTACT_R07           (147U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_NOTACT_R08           (148U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_NOTACT_R17           (149U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_REL_R10              (150U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_REL_R11              (151U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_NOTACT_R13           (152U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_TMBZR_ANN_PRI1             (153U)                         /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_SI_TMBZR_RCV_PRI1             (154U)                         /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_SI_TMBZR_RJT_PRI1             (155U)                         /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_CO_TMBZR_CONT_PRI1            (156U)                         /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_IN_TMBZR_TEN_PRI1             (157U)                         /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_SI_BRK_APP5                   (158U)                         /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_SI_RSA_CHG_SPLDLMT            (159U)                         /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_ACC_APPRVLSTART            (160U)                         /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_FMSEAT_MEM_SCS             (161U)                         /* MET-B_FMSEAT-CSTD--                               */
#define WCHIME_REQ_SI_FMSEAT_MEM_REJ             (162U)                         /* MET-B_FMSEAT-CSTD--                               */
#define WCHIME_REQ_SI_FMSEAT_ERS_INFO            (163U)                         /* MET-B_FMSEAT-CSTD--                               */
#define WCHIME_REQ_SI_FMSEAT_MEM_CALL            (164U)                         /* MET-B_FMSEAT-CSTD--                               */
#define WCHIME_REQ_SI_ESWUOC_RJCT                (165U)                         /* MET-B_ESWUOC-CSTD-                                */
#define WCHIME_REQ_SI_SMASTA_SNGL2               (166U)                         /* MET-B_SMASTA-CST2                                 */
#define WCHIME_REQ_SI_TURHAZ_STA_LS              (167U)                         /* MET-B_TURHAZ-CSTD-                                */
#define WCHIME_REQ_SI_TURHAZ_STA_MS              (168U)                         /* MET-B_TURHAZ-CSTD-                                */
#define WCHIME_REQ_SI_TURHAZ_STA_HS              (169U)                         /* MET-B_TURHAZ-CSTD-                                */
#define WCHIME_REQ_SI_TURHAZ_FIN_LS              (170U)                         /* MET-B_TURHAZ-CSTD-                                */
#define WCHIME_REQ_SI_TURHAZ_FIN_MS              (171U)                         /* MET-B_TURHAZ-CSTD-                                */
#define WCHIME_REQ_SI_TURHAZ_FIN_HS              (172U)                         /* MET-B_TURHAZ-CSTD-                                */
#define WCHIME_REQ_SI_TMBZR_ANN_PRI0             (173U)                         /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_SI_TMBZR_RCV_PRI0             (174U)                         /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_SI_TMBZR_RJT_PRI0             (175U)                         /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_CO_TMBZR_CONT_PRI0            (176U)                         /* MET-S_TMBZR-CST0                                  */
#define WCHIME_REQ_IN_TMBZR_TEN_PRI0             (177U)                         /* MET-S_TMBZR-CST0                                  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define WCHIME_REQBIT_NUM_WORD                   ((WCHIME_NUM_REQ + 31U) >> 5)  /* Number of rows to convert buzzer req. ID to bit.  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define WCHIME_NUM_VOL                           (178U)                /* Number of volume ID                                        */


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
#define WCHIME_VOL_CSR_FR_SD_0                   (10U)                 /* For Clearance sonar buzzer Fr(SD) CSR_VOL:0                */
#define WCHIME_VOL_CSR_FR_SD_1                   (11U)                 /* For Clearance sonar buzzer Fr(SD) CSR_VOL:1                */
#define WCHIME_VOL_CSR_FR_SD_2                   (12U)                 /* For Clearance sonar buzzer Fr(SD) CSR_VOL:2                */
#define WCHIME_VOL_CSR_FR_SD_3                   (13U)                 /* For Clearance sonar buzzer Fr(SD) CSR_VOL:3                */
#define WCHIME_VOL_CSR_FR_SD_4                   (14U)                 /* For Clearance sonar buzzer Fr(SD) CSR_VOL:4                */
#define WCHIME_VOL_CSR_FR_SD_5                   (15U)                 /* For Clearance sonar buzzer Fr(SD) CSR_VOL:5                */
#define WCHIME_VOL_CSR_FR_SD_6                   (16U)                 /* For Clearance sonar buzzer Fr(SD) CSR_VOL:6                */
#define WCHIME_VOL_CSR_FR_SD_7                   (17U)                 /* For Clearance sonar buzzer Fr(SD) CSR_VOL:7                */
#define WCHIME_VOL_CSR_FR_MD_0                   (18U)                 /* For Clearance sonar buzzer Fr(MD) CSR_VOL:0                */
#define WCHIME_VOL_CSR_FR_MD_1                   (19U)                 /* For Clearance sonar buzzer Fr(MD) CSR_VOL:1                */
#define WCHIME_VOL_CSR_FR_MD_2                   (20U)                 /* For Clearance sonar buzzer Fr(MD) CSR_VOL:2                */
#define WCHIME_VOL_CSR_FR_MD_3                   (21U)                 /* For Clearance sonar buzzer Fr(MD) CSR_VOL:3                */
#define WCHIME_VOL_CSR_FR_MD_4                   (22U)                 /* For Clearance sonar buzzer Fr(MD) CSR_VOL:4                */
#define WCHIME_VOL_CSR_FR_MD_5                   (23U)                 /* For Clearance sonar buzzer Fr(MD) CSR_VOL:5                */
#define WCHIME_VOL_CSR_FR_MD_6                   (24U)                 /* For Clearance sonar buzzer Fr(MD) CSR_VOL:6                */
#define WCHIME_VOL_CSR_FR_MD_7                   (25U)                 /* For Clearance sonar buzzer Fr(MD) CSR_VOL:7                */
#define WCHIME_VOL_CSR_FR_LD_0                   (26U)                 /* For Clearance sonar buzzer Fr(LD) CSR_VOL:0                */
#define WCHIME_VOL_CSR_FR_LD_1                   (27U)                 /* For Clearance sonar buzzer Fr(LD) CSR_VOL:1                */
#define WCHIME_VOL_CSR_FR_LD_2                   (28U)                 /* For Clearance sonar buzzer Fr(LD) CSR_VOL:2                */
#define WCHIME_VOL_CSR_FR_LD_3                   (29U)                 /* For Clearance sonar buzzer Fr(LD) CSR_VOL:3                */
#define WCHIME_VOL_CSR_FR_LD_4                   (30U)                 /* For Clearance sonar buzzer Fr(LD) CSR_VOL:4                */
#define WCHIME_VOL_CSR_FR_LD_5                   (31U)                 /* For Clearance sonar buzzer Fr(LD) CSR_VOL:5                */
#define WCHIME_VOL_CSR_FR_LD_6                   (32U)                 /* For Clearance sonar buzzer Fr(LD) CSR_VOL:6                */
#define WCHIME_VOL_CSR_FR_LD_7                   (33U)                 /* For Clearance sonar buzzer Fr(LD) CSR_VOL:7                */
#define WCHIME_VOL_CSR_FR_FD_0                   (34U)                 /* For Clearance sonar buzzer Fr(FD) CSR_VOL:0                */
#define WCHIME_VOL_CSR_FR_FD_1                   (35U)                 /* For Clearance sonar buzzer Fr(FD) CSR_VOL:1                */
#define WCHIME_VOL_CSR_FR_FD_2                   (36U)                 /* For Clearance sonar buzzer Fr(FD) CSR_VOL:2                */
#define WCHIME_VOL_CSR_FR_FD_3                   (37U)                 /* For Clearance sonar buzzer Fr(FD) CSR_VOL:3                */
#define WCHIME_VOL_CSR_FR_FD_4                   (38U)                 /* For Clearance sonar buzzer Fr(FD) CSR_VOL:4                */
#define WCHIME_VOL_CSR_FR_FD_5                   (39U)                 /* For Clearance sonar buzzer Fr(FD) CSR_VOL:5                */
#define WCHIME_VOL_CSR_FR_FD_6                   (40U)                 /* For Clearance sonar buzzer Fr(FD) CSR_VOL:6                */
#define WCHIME_VOL_CSR_FR_FD_7                   (41U)                 /* For Clearance sonar buzzer Fr(FD) CSR_VOL:7                */
#define WCHIME_VOL_CSR_RR_SD_0                   (42U)                 /* For Clearance sonar buzzer Rr(SD) CSR_VOL:0                */
#define WCHIME_VOL_CSR_RR_SD_1                   (43U)                 /* For Clearance sonar buzzer Rr(SD) CSR_VOL:1                */
#define WCHIME_VOL_CSR_RR_SD_2                   (44U)                 /* For Clearance sonar buzzer Rr(SD) CSR_VOL:2                */
#define WCHIME_VOL_CSR_RR_SD_3                   (45U)                 /* For Clearance sonar buzzer Rr(SD) CSR_VOL:3                */
#define WCHIME_VOL_CSR_RR_SD_4                   (46U)                 /* For Clearance sonar buzzer Rr(SD) CSR_VOL:4                */
#define WCHIME_VOL_CSR_RR_SD_5                   (47U)                 /* For Clearance sonar buzzer Rr(SD) CSR_VOL:5                */
#define WCHIME_VOL_CSR_RR_SD_6                   (48U)                 /* For Clearance sonar buzzer Rr(SD) CSR_VOL:6                */
#define WCHIME_VOL_CSR_RR_SD_7                   (49U)                 /* For Clearance sonar buzzer Rr(SD) CSR_VOL:7                */
#define WCHIME_VOL_CSR_RR_MD_0                   (50U)                 /* For Clearance sonar buzzer Rr(MD) CSR_VOL:0                */
#define WCHIME_VOL_CSR_RR_MD_1                   (51U)                 /* For Clearance sonar buzzer Rr(MD) CSR_VOL:1                */
#define WCHIME_VOL_CSR_RR_MD_2                   (52U)                 /* For Clearance sonar buzzer Rr(MD) CSR_VOL:2                */
#define WCHIME_VOL_CSR_RR_MD_3                   (53U)                 /* For Clearance sonar buzzer Rr(MD) CSR_VOL:3                */
#define WCHIME_VOL_CSR_RR_MD_4                   (54U)                 /* For Clearance sonar buzzer Rr(MD) CSR_VOL:4                */
#define WCHIME_VOL_CSR_RR_MD_5                   (55U)                 /* For Clearance sonar buzzer Rr(MD) CSR_VOL:5                */
#define WCHIME_VOL_CSR_RR_MD_6                   (56U)                 /* For Clearance sonar buzzer Rr(MD) CSR_VOL:6                */
#define WCHIME_VOL_CSR_RR_MD_7                   (57U)                 /* For Clearance sonar buzzer Rr(MD) CSR_VOL:7                */
#define WCHIME_VOL_CSR_RR_LD_0                   (58U)                 /* For Clearance sonar buzzer Rr(LD) CSR_VOL:0                */
#define WCHIME_VOL_CSR_RR_LD_1                   (59U)                 /* For Clearance sonar buzzer Rr(LD) CSR_VOL:1                */
#define WCHIME_VOL_CSR_RR_LD_2                   (60U)                 /* For Clearance sonar buzzer Rr(LD) CSR_VOL:2                */
#define WCHIME_VOL_CSR_RR_LD_3                   (61U)                 /* For Clearance sonar buzzer Rr(LD) CSR_VOL:3                */
#define WCHIME_VOL_CSR_RR_LD_4                   (62U)                 /* For Clearance sonar buzzer Rr(LD) CSR_VOL:4                */
#define WCHIME_VOL_CSR_RR_LD_5                   (63U)                 /* For Clearance sonar buzzer Rr(LD) CSR_VOL:5                */
#define WCHIME_VOL_CSR_RR_LD_6                   (64U)                 /* For Clearance sonar buzzer Rr(LD) CSR_VOL:6                */
#define WCHIME_VOL_CSR_RR_LD_7                   (65U)                 /* For Clearance sonar buzzer Rr(LD) CSR_VOL:7                */
#define WCHIME_VOL_CSR_RR_FD_0                   (66U)                 /* For Clearance sonar buzzer Rr(FD) CSR_VOL:0                */
#define WCHIME_VOL_CSR_RR_FD_1                   (67U)                 /* For Clearance sonar buzzer Rr(FD) CSR_VOL:1                */
#define WCHIME_VOL_CSR_RR_FD_2                   (68U)                 /* For Clearance sonar buzzer Rr(FD) CSR_VOL:2                */
#define WCHIME_VOL_CSR_RR_FD_3                   (69U)                 /* For Clearance sonar buzzer Rr(FD) CSR_VOL:3                */
#define WCHIME_VOL_CSR_RR_FD_4                   (70U)                 /* For Clearance sonar buzzer Rr(FD) CSR_VOL:4                */
#define WCHIME_VOL_CSR_RR_FD_5                   (71U)                 /* For Clearance sonar buzzer Rr(FD) CSR_VOL:5                */
#define WCHIME_VOL_CSR_RR_FD_6                   (72U)                 /* For Clearance sonar buzzer Rr(FD) CSR_VOL:6                */
#define WCHIME_VOL_CSR_RR_FD_7                   (73U)                 /* For Clearance sonar buzzer Rr(FD) CSR_VOL:7                */
#define WCHIME_VOL_CSR_FRRR_SD_0                 (74U)                 /* For Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:0             */
#define WCHIME_VOL_CSR_FRRR_SD_1                 (75U)                 /* For Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:1             */
#define WCHIME_VOL_CSR_FRRR_SD_2                 (76U)                 /* For Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:2             */
#define WCHIME_VOL_CSR_FRRR_SD_3                 (77U)                 /* For Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:3             */
#define WCHIME_VOL_CSR_FRRR_SD_4                 (78U)                 /* For Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:4             */
#define WCHIME_VOL_CSR_FRRR_SD_5                 (79U)                 /* For Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:5             */
#define WCHIME_VOL_CSR_FRRR_SD_6                 (80U)                 /* For Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:6             */
#define WCHIME_VOL_CSR_FRRR_SD_7                 (81U)                 /* For Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:7             */
#define WCHIME_VOL_CSR_FRRR_MD_FR_0              (82U)                 /* For Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:0         */
#define WCHIME_VOL_CSR_FRRR_MD_FR_1              (83U)                 /* For Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:1         */
#define WCHIME_VOL_CSR_FRRR_MD_FR_2              (84U)                 /* For Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:2         */
#define WCHIME_VOL_CSR_FRRR_MD_FR_3              (85U)                 /* For Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:3         */
#define WCHIME_VOL_CSR_FRRR_MD_FR_4              (86U)                 /* For Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:4         */
#define WCHIME_VOL_CSR_FRRR_MD_FR_5              (87U)                 /* For Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:5         */
#define WCHIME_VOL_CSR_FRRR_MD_FR_6              (88U)                 /* For Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:6         */
#define WCHIME_VOL_CSR_FRRR_MD_FR_7              (89U)                 /* For Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:7         */
#define WCHIME_VOL_CSR_FRRR_MD_RR_0              (90U)                 /* For Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:0         */
#define WCHIME_VOL_CSR_FRRR_MD_RR_1              (91U)                 /* For Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:1         */
#define WCHIME_VOL_CSR_FRRR_MD_RR_2              (92U)                 /* For Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:2         */
#define WCHIME_VOL_CSR_FRRR_MD_RR_3              (93U)                 /* For Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:3         */
#define WCHIME_VOL_CSR_FRRR_MD_RR_4              (94U)                 /* For Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:4         */
#define WCHIME_VOL_CSR_FRRR_MD_RR_5              (95U)                 /* For Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:5         */
#define WCHIME_VOL_CSR_FRRR_MD_RR_6              (96U)                 /* For Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:6         */
#define WCHIME_VOL_CSR_FRRR_MD_RR_7              (97U)                 /* For Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:7         */
#define WCHIME_VOL_CSR_FRRR_LD_FR_0              (98U)                 /* For Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:0         */
#define WCHIME_VOL_CSR_FRRR_LD_FR_1              (99U)                 /* For Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:1         */
#define WCHIME_VOL_CSR_FRRR_LD_FR_2              (100U)                /* For Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:2         */
#define WCHIME_VOL_CSR_FRRR_LD_FR_3              (101U)                /* For Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:3         */
#define WCHIME_VOL_CSR_FRRR_LD_FR_4              (102U)                /* For Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:4         */
#define WCHIME_VOL_CSR_FRRR_LD_FR_5              (103U)                /* For Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:5         */
#define WCHIME_VOL_CSR_FRRR_LD_FR_6              (104U)                /* For Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:6         */
#define WCHIME_VOL_CSR_FRRR_LD_FR_7              (105U)                /* For Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:7         */
#define WCHIME_VOL_CSR_FRRR_LD_RR_0              (106U)                /* For Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:0         */
#define WCHIME_VOL_CSR_FRRR_LD_RR_1              (107U)                /* For Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:1         */
#define WCHIME_VOL_CSR_FRRR_LD_RR_2              (108U)                /* For Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:2         */
#define WCHIME_VOL_CSR_FRRR_LD_RR_3              (109U)                /* For Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:3         */
#define WCHIME_VOL_CSR_FRRR_LD_RR_4              (110U)                /* For Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:4         */
#define WCHIME_VOL_CSR_FRRR_LD_RR_5              (111U)                /* For Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:5         */
#define WCHIME_VOL_CSR_FRRR_LD_RR_6              (112U)                /* For Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:6         */
#define WCHIME_VOL_CSR_FRRR_LD_RR_7              (113U)                /* For Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:7         */
#define WCHIME_VOL_CSR_FRRR_FD_FR_0              (114U)                /* For Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:0         */
#define WCHIME_VOL_CSR_FRRR_FD_FR_1              (115U)                /* For Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:1         */
#define WCHIME_VOL_CSR_FRRR_FD_FR_2              (116U)                /* For Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:2         */
#define WCHIME_VOL_CSR_FRRR_FD_FR_3              (117U)                /* For Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:3         */
#define WCHIME_VOL_CSR_FRRR_FD_FR_4              (118U)                /* For Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:4         */
#define WCHIME_VOL_CSR_FRRR_FD_FR_5              (119U)                /* For Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:5         */
#define WCHIME_VOL_CSR_FRRR_FD_FR_6              (120U)                /* For Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:6         */
#define WCHIME_VOL_CSR_FRRR_FD_FR_7              (121U)                /* For Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:7         */
#define WCHIME_VOL_CSR_FRRR_FD_RR_0              (122U)                /* For Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:0         */
#define WCHIME_VOL_CSR_FRRR_FD_RR_1              (123U)                /* For Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:1         */
#define WCHIME_VOL_CSR_FRRR_FD_RR_2              (124U)                /* For Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:2         */
#define WCHIME_VOL_CSR_FRRR_FD_RR_3              (125U)                /* For Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:3         */
#define WCHIME_VOL_CSR_FRRR_FD_RR_4              (126U)                /* For Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:4         */
#define WCHIME_VOL_CSR_FRRR_FD_RR_5              (127U)                /* For Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:5         */
#define WCHIME_VOL_CSR_FRRR_FD_RR_6              (128U)                /* For Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:6         */
#define WCHIME_VOL_CSR_FRRR_FD_RR_7              (129U)                /* For Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:7         */
#define WCHIME_VOL_TURHAZ_STA_LCSTM_LSPD         (130U)                /* For flasher start sound(customize: low, low speed)         */
#define WCHIME_VOL_TURHAZ_STA_LCSTM_MSPD         (131U)                /* For flasher start sound(customize: low, middle speed)      */
#define WCHIME_VOL_TURHAZ_STA_LCSTM_HSPD         (132U)                /* For flasher start sound(customize: low, high speed)        */
#define WCHIME_VOL_TURHAZ_STA_MCSTM_LSPD         (133U)                /* For flasher start sound(customize: middle, low speed)      */
#define WCHIME_VOL_TURHAZ_STA_MCSTM_MSPD         (134U)                /* For flasher start sound(customize: middle, middle speed)   */
#define WCHIME_VOL_TURHAZ_STA_MCSTM_HSPD         (135U)                /* For flasher start sound(customize: middle, high speed)     */
#define WCHIME_VOL_TURHAZ_STA_HCSTM_LSPD         (136U)                /* For flasher start sound(customize: high, low speed)        */
#define WCHIME_VOL_TURHAZ_STA_HCSTM_MSPD         (137U)                /* For flasher start sound(customize: high, middle speed)     */
#define WCHIME_VOL_TURHAZ_STA_HCSTM_HSPD         (138U)                /* For flasher start sound(customize: high, high speed)       */
#define WCHIME_VOL_TURHAZ_FIN_LCSTM_LSPD         (139U)                /* For flasher finish sound(customize: low, low speed)        */
#define WCHIME_VOL_TURHAZ_FIN_LCSTM_MSPD         (140U)                /* For flasher finish sound(customize: low, middle speed)     */
#define WCHIME_VOL_TURHAZ_FIN_LCSTM_HSPD         (141U)                /* For flasher finish sound(customize: low, high speed)       */
#define WCHIME_VOL_TURHAZ_FIN_MCSTM_LSPD         (142U)                /* For flasher finish sound(customize: middle, low speed)     */
#define WCHIME_VOL_TURHAZ_FIN_MCSTM_MSPD         (143U)                /* For flasher finish sound(customize: middle, middle speed)  */
#define WCHIME_VOL_TURHAZ_FIN_MCSTM_HSPD         (144U)                /* For flasher finish sound(customize: middle, high speed)    */
#define WCHIME_VOL_TURHAZ_FIN_HCSTM_LSPD         (145U)                /* For flasher finish sound(customize: high, low speed)       */
#define WCHIME_VOL_TURHAZ_FIN_HCSTM_MSPD         (146U)                /* For flasher finish sound(customize: high, middle speed)    */
#define WCHIME_VOL_TURHAZ_FIN_HCSTM_HSPD         (147U)                /* For flasher finish sound(customize: high, high speed)      */
#define WCHIME_VOL_CSR_RCTA_0                    (148U)                /* For RCTA buzzer(from CSR ECU) CSR_VOL:0                    */
#define WCHIME_VOL_CSR_RCTA_1                    (149U)                /* For RCTA buzzer(from CSR ECU) CSR_VOL:1                    */
#define WCHIME_VOL_CSR_RCTA_2                    (150U)                /* For RCTA buzzer(from CSR ECU) CSR_VOL:2                    */
#define WCHIME_VOL_CSR_RCTA_3                    (151U)                /* For RCTA buzzer(from CSR ECU) CSR_VOL:3                    */
#define WCHIME_VOL_CSR_RCTA_4                    (152U)                /* For RCTA buzzer(from CSR ECU) CSR_VOL:4                    */
#define WCHIME_VOL_CSR_RCTA_5                    (153U)                /* For RCTA buzzer(from CSR ECU) CSR_VOL:5                    */
#define WCHIME_VOL_CSR_RCTA_6                    (154U)                /* For RCTA buzzer(from CSR ECU) CSR_VOL:6                    */
#define WCHIME_VOL_CSR_RCTA_7                    (155U)                /* For RCTA buzzer(from CSR ECU) CSR_VOL:7                    */
#define WCHIME_VOL_BASE_NOTICE1_MID              (156U)                /* For notification sound MID                                 */
#define WCHIME_VOL_BASE_NOTICE1_MAX              (157U)                /* For notification sound MAX                                 */
#define WCHIME_VOL_BASE_NOTICE2_MID              (158U)                /* For special notification sound MID                         */
#define WCHIME_VOL_BASE_NOTICE2_MAX              (159U)                /* For special notification sound MAX                         */
#define WCHIME_VOL_BASE_ACCEPT_MID               (160U)                /* For accept sound MID                                       */
#define WCHIME_VOL_BASE_ACCEPT_MAX               (161U)                /* For accept sound MAX                                       */
#define WCHIME_VOL_BASE_REJECT_MID               (162U)                /* For reject sound MID                                       */
#define WCHIME_VOL_BASE_REJECT_MAX               (163U)                /* For reject sound MAX                                       */
#define WCHIME_VOL_BASE_INTWARNL_MID             (164U)                /* For intermittent sound (low urgency) MID                   */
#define WCHIME_VOL_BASE_INTWARNL_MAX             (165U)                /* For intermittent sound (low urgency) MAX                   */
#define WCHIME_VOL_BASE_INTWARNM_MID             (166U)                /* For intermittent sound (moderate urgency) MID              */
#define WCHIME_VOL_BASE_INTWARNM_MAX             (167U)                /* For intermittent sound (moderate urgency) MAX              */
#define WCHIME_VOL_BASE_INTWARNH_MID             (168U)                /* For intermittent sound (high urgency) MID                  */
#define WCHIME_VOL_BASE_INTWARNH_MAX             (169U)                /* For intermittent sound (high urgency) MAX                  */
#define WCHIME_VOL_BASE_CONTWARN_MID             (170U)                /* For continuous sound MID                                   */
#define WCHIME_VOL_BASE_CONTWARN_MAX             (171U)                /* For continuous sound MAX                                   */
#define WCHIME_VOL_AD_DOT_MID                    (172U)                /* PreDOT Sound MID                                           */
#define WCHIME_VOL_AD_DOT_MAX                    (173U)                /* PreDOT Sound MAX                                           */
#define WCHIME_VOL_SEA_REJECT_MID                (174U)                /* For SEA door open reject MID                               */
#define WCHIME_VOL_SEA_REJECT_MAX                (175U)                /* For SEA door open reject MAX                               */
#define WCHIME_VOL_PCS_SEA_INTWARNH_MID          (176U)                /* For PCS/SEA warning MID                                    */
#define WCHIME_VOL_PCS_SEA_INTWARNH_MAX          (177U)                /* For PCS/SEA warning MAX                                    */

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
