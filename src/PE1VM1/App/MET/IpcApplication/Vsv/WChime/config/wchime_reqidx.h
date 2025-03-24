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
#define WCHIME_NUM_REQ                           (153U)                         /* Number of buzzer request ID                       */

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
#define WCHIME_REQ_IN_DOA                        (10U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_CO_CSR_FR_SD                  (11U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_CSR_FR_MD                  (12U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_CO_CSR_RR_SD                  (13U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_CSR_RR_MD                  (14U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_CO_CSR_FRRR_SD                (15U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_CSR_FRRR_MD                (16U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_CSR_RCTA                   (17U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_SYSMAL_REMDST_0M           (18U)                          /* MET-H_SYSMAL-CSTD-                                */
#define WCHIME_REQ_IN_PCS_PED                    (19U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_FCTA_STEP_STOP             (20U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_EDSS_R04                   (21U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_CSR_FR_LD                  (22U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_CSR_RR_LD                  (23U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_CSR_FRRR_LD                (24U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_DA                         (25U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_TCHAR_CYCL2                (26U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_EDSS_R03                   (27U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_EIGCON_EG_PWROFF           (28U)                          /* MET-O_EIGCON-CSTD-                                */
#define WCHIME_REQ_IN_SCB                        (29U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_BSM                        (30U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_LDA                        (31U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_INFRA_INT                  (32U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_SMASTA_INT3                (33U)                          /* MET-B_SMASTA-CSTD--                               */
#define WCHIME_REQ_IN_CSR_FR_FD                  (34U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_CSR_RR_FD                  (35U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_CSR_FRRR_FD                (36U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_TCHAR_CYCL1                (37U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_BRK_FLDLEAK                (38U)                          /* MET-C_BRLV-CSTD-                                  */
#define WCHIME_REQ_IN_STEER_STP                  (39U)                          /* MET-C_STEER-CSTD-                                 */
#define WCHIME_REQ_IN_SBLT_FMV                   (40U)                          /* MET-B_SEAREM-CSTD--                               */
#define WCHIME_REQ_IN_ACC_BRKREQ                 (41U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_BRK_TST_FIN                (42U)                          /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_SI_SBW_RJCT                   (43U)                          /* MET-D_SBW-CSTD-                                   */
#define WCHIME_REQ_CO_NACCON                     (44U)                          /* MET-H_ONACCN-CSTD-                                */
#define WCHIME_REQ_CO_PEXI_HV_NDBW               (45U)                          /* MET-H_PEXI-CSTD-                                  */
#define WCHIME_REQ_CO_ACCHOL                     (46U)                          /* MET-H_ACCHOL-CSTD-                                */
#define WCHIME_REQ_IN_SBW_AUTOP                  (47U)                          /* MET-D_SBW-CSTD-                                   */
#define WCHIME_REQ_IN_RSA_SIGN_CAUTION2          (48U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_ESWUOC_REL                 (49U)                          /* MET-B_ESWUOC-CSTD-                                */
#define WCHIME_REQ_IN_PMAR                       (50U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_APP_NONOPE_REQ2            (51U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_CO_APP_NONOPE_REQ4            (52U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_CO_SYSMAL_RNG_P               (53U)                          /* MET-H_SYSMAL-CSTD-                                */
#define WCHIME_REQ_IN_CHAMAL_BAT_FAIL            (54U)                          /* MET-O_CHAMAL-CSTD-                                */
#define WCHIME_REQ_IN_SYSMAL_REQSTP              (55U)                          /* MET-H_SYSMAL-CSTD-                                */
#define WCHIME_REQ_IN_BRK_TST_LRN                (56U)                          /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_IN_EPB                        (57U)                          /* MET-C_EPB-CSTD-                                   */
#define WCHIME_REQ_CO_EIGCON_IGOFF               (58U)                          /* MET-O_EIGCON-CSTD-                                */
#define WCHIME_REQ_SI_SFTPOS_NML                 (59U)                          /* MET-D_SFTPOS-CSTD-                                */
#define WCHIME_REQ_SI_ACC_LSPDCNSL               (60U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_LTA_CNCL                   (61U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_LCS_CNCL                   (62U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_APP_DIS_ASSIST             (63U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_APP_CMPLT                  (64U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_DCLDSP_OPERJCT             (65U)                          /* MET-H_DCLDSP-CSTD-                                */
#define WCHIME_REQ_SI_LCS_ACK                    (66U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_DOA_RJCT                   (67U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_MET_WRN_VOL_CSTM           (68U)                          /* MET-M_MWVCUS-CSTD-                                */
#define WCHIME_REQ_SI_SBW_SPL_STATE              (69U)                          /* MET-D_SBW-CSTD-                                   */
#define WCHIME_REQ_IN_DMC_LV2                    (70U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_SFTPOS_REV                 (71U)                          /* MET-D_SFTPOS-CSTD-                                */
#define WCHIME_REQ_IN_SMASTA_INT2                (72U)                          /* MET-B_SMASTA-CSTD--                               */
#define WCHIME_REQ_CO_SMASTA_CON                 (73U)                          /* MET-B_SMASTA-CSTD--                               */
#define WCHIME_REQ_IN_SBLT_LV2                   (74U)                          /* MET-B_SEAREM-CSTD--                               */
#define WCHIME_REQ_IN_ACC_OVERSPD                (75U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_ACC_SHIFTREQ               (76U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_TPMS_CYCL                  (77U)                          /* MET-C_TPMS-CSTD-                                  */
#define WCHIME_REQ_SI_SWS                        (78U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_MINDSPWR_LV2               (79U)                          /* MET-M_MINDSPWR-CSTD-                              */
#define WCHIME_REQ_IN_BGLFSPD                    (80U)                          /* MET-M_BGLFSPD-CSTD-                               */
#define WCHIME_REQ_IN_DR_OPN                     (81U)                          /* MET-B_BDOOR-CSTD-                                 */
#define WCHIME_REQ_IN_BRK_SYS_MAL                (82U)                          /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_IN_BRK_SYS_NOOPE2             (83U)                          /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_IN_BRK_SYS_NOOPE1             (84U)                          /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_SI_STEER_LMT                  (85U)                          /* MET-C_STEER-CSTD-                                 */
#define WCHIME_REQ_SI_SBW_MAL                    (86U)                          /* MET-D_SBW-CSTD-                                   */
#define WCHIME_REQ_IN_SBW_MAL                    (87U)                          /* MET-D_SBW-CSTD-                                   */
#define WCHIME_REQ_IN_SYSMAL_REMDST_500M         (88U)                          /* MET-H_SYSMAL-CSTD-                                */
#define WCHIME_REQ_IN_SYSMAL_REMDST_1KM          (89U)                          /* MET-H_SYSMAL-CSTD-                                */
#define WCHIME_REQ_IN_LTA_PTN2                   (90U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_LTA_PTN3                   (91U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_MINDSPWR_LV1               (92U)                          /* MET-M_MINDSPWR-CSTD-                              */
#define WCHIME_REQ_IN_SBLT_LV1                   (93U)                          /* MET-B_SEAREM-CSTD--                               */
#define WCHIME_REQ_SI_SBLT                       (94U)                          /* MET-B_SEAREM-CSTD--                               */
#define WCHIME_REQ_SI_RSA_SIGN_CTN1_OTH          (95U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_DMC_LV1                    (96U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_SYSMAL_FAIL                (97U)                          /* MET-H_SYSMAL-CSTD-                                */
#define WCHIME_REQ_IN_LTA_PTN1                   (98U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_INFRA_SNGL                 (99U)                          /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_MLT_MSG                    (100U)                         /* MET-G_MULDISPMM-CSTD-                             */
#define WCHIME_REQ_CO_LIGHT                      (101U)                         /* MET-B_BLGT-CSTD-                                  */
#define WCHIME_REQ_SI_ACC_AUTOSTART              (102U)                         /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_SBW_RCPT                   (103U)                         /* MET-D_SBW-CSTD-                                   */
#define WCHIME_REQ_IN_LDA_HFCT                   (104U)                         /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_BATINS                     (105U)                         /* MET-H_BATINS-CSTD-                                */
#define WCHIME_REQ_SI_TPMS_SINGLE                (106U)                         /* MET-C_TPMS-CSTD-                                  */
#define WCHIME_REQ_SI_TCHAR_SNGL                 (107U)                         /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_LDA_WARN                   (108U)                         /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_SMASTA_SNGL                (109U)                         /* MET-B_SMASTA-CSTD--                               */
#define WCHIME_REQ_IN_TOWWAR                     (110U)                         /* MET-H_TOWWAR-CSTD-                                */
#define WCHIME_REQ_SI_TMN_LVN                    (111U)                         /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_IN_SMASTA_INT1                (112U)                         /* MET-B_SMASTA-CSTD--                               */
#define WCHIME_REQ_SI_BRK_APP3                   (113U)                         /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_IN_BRK_APP1                   (114U)                         /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_IN_BRK_APP2                   (115U)                         /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_SI_BKHLD_NOTACT_R16           (116U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_NOTREL               (117U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_NOTACT_R07           (118U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_NOTACT_R08           (119U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_NOTACT_R17           (120U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_REL_R10              (121U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_REL_R11              (122U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BKHLD_NOTACT_R13           (123U)                         /* MET-C_BRKHLD-CSTD-                                */
#define WCHIME_REQ_SI_BRK_TST_STRT               (124U)                         /* MET-C_BRKBZ-CSTD-                                 */
#define WCHIME_REQ_SI_ACC_APPRVLSTART            (125U)                         /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_PERSET_SUC                 (126U)                         /* MET-B_PERSET-CSTD-                                */
#define WCHIME_REQ_SI_PERSET_FAIL                (127U)                         /* MET-B_PERSET-CSTD-                                */
#define WCHIME_REQ_SI_RSA_CHG_SPLDLMT            (128U)                         /* MET-S_ADBZR-CSTD-                                 */
#define WCHIME_REQ_SI_FMSEAT_MEM_SCS             (129U)                         /* MET-B_FMSEAT-CSTD--                               */
#define WCHIME_REQ_SI_FMSEAT_MEM_REJ             (130U)                         /* MET-B_FMSEAT-CSTD--                               */
#define WCHIME_REQ_SI_FMSEAT_ERS_INFO            (131U)                         /* MET-B_FMSEAT-CSTD--                               */
#define WCHIME_REQ_SI_FMSEAT_MEM_CALL            (132U)                         /* MET-B_FMSEAT-CSTD--                               */
#define WCHIME_REQ_SI_ESWUOC_RJCT                (133U)                         /* MET-B_ESWUOC-CSTD-                                */
#define WCHIME_REQ_SI_SMASTA_SNGL2               (134U)                         /* MET-B_SMASTA-CSTD--                               */
#define WCHIME_REQ_SI_TURHAZ_STA_LC_LS           (135U)                         /* MET-B_TURHAZ-CSTD-                                */
#define WCHIME_REQ_SI_TURHAZ_STA_LC_MS           (136U)                         /* MET-B_TURHAZ-CSTD-                                */
#define WCHIME_REQ_SI_TURHAZ_STA_LC_HS           (137U)                         /* MET-B_TURHAZ-CSTD-                                */
#define WCHIME_REQ_SI_TURHAZ_STA_MC_LS           (138U)                         /* MET-B_TURHAZ-CSTD-                                */
#define WCHIME_REQ_SI_TURHAZ_STA_MC_MS           (139U)                         /* MET-B_TURHAZ-CSTD-                                */
#define WCHIME_REQ_SI_TURHAZ_STA_MC_HS           (140U)                         /* MET-B_TURHAZ-CSTD-                                */
#define WCHIME_REQ_SI_TURHAZ_STA_HC_LS           (141U)                         /* MET-B_TURHAZ-CSTD-                                */
#define WCHIME_REQ_SI_TURHAZ_STA_HC_MS           (142U)                         /* MET-B_TURHAZ-CSTD-                                */
#define WCHIME_REQ_SI_TURHAZ_STA_HC_HS           (143U)                         /* MET-B_TURHAZ-CSTD-                                */
#define WCHIME_REQ_SI_TURHAZ_FIN_LC_LS           (144U)                         /* MET-B_TURHAZ-CSTD-                                */
#define WCHIME_REQ_SI_TURHAZ_FIN_LC_MS           (145U)                         /* MET-B_TURHAZ-CSTD-                                */
#define WCHIME_REQ_SI_TURHAZ_FIN_LC_HS           (146U)                         /* MET-B_TURHAZ-CSTD-                                */
#define WCHIME_REQ_SI_TURHAZ_FIN_MC_LS           (147U)                         /* MET-B_TURHAZ-CSTD-                                */
#define WCHIME_REQ_SI_TURHAZ_FIN_MC_MS           (148U)                         /* MET-B_TURHAZ-CSTD-                                */
#define WCHIME_REQ_SI_TURHAZ_FIN_MC_HS           (149U)                         /* MET-B_TURHAZ-CSTD-                                */
#define WCHIME_REQ_SI_TURHAZ_FIN_HC_LS           (150U)                         /* MET-B_TURHAZ-CSTD-                                */
#define WCHIME_REQ_SI_TURHAZ_FIN_HC_MS           (151U)                         /* MET-B_TURHAZ-CSTD-                                */
#define WCHIME_REQ_SI_TURHAZ_FIN_HC_HS           (152U)                         /* MET-B_TURHAZ-CSTD-                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define WCHIME_REQBIT_NUM_WORD                   ((WCHIME_NUM_REQ + 31U) >> 5)  /* Number of rows to convert buzzer req. ID to bit.  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define WCHIME_NUM_VOL                           (198U)                /* Number of volume ID                                        */


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
#define WCHIME_VOL_BASE_NOTICE1_MID              (176U)                /* For notification sound MID                                 */
#define WCHIME_VOL_BASE_NOTICE1_MAX              (177U)                /* For notification sound MAX                                 */
#define WCHIME_VOL_BASE_NOTICE2_MID              (178U)                /* For special notification sound MID                         */
#define WCHIME_VOL_BASE_NOTICE2_MAX              (179U)                /* For special notification sound MAX                         */
#define WCHIME_VOL_BASE_ACCEPT_MID               (180U)                /* For accept sound MID                                       */
#define WCHIME_VOL_BASE_ACCEPT_MAX               (181U)                /* For accept sound MAX                                       */
#define WCHIME_VOL_BASE_REJECT_MID               (182U)                /* For reject sound MID                                       */
#define WCHIME_VOL_BASE_REJECT_MAX               (183U)                /* For reject sound MAX                                       */
#define WCHIME_VOL_BASE_INTWARNL_MID             (184U)                /* For intermittent sound (low urgency) MID                   */
#define WCHIME_VOL_BASE_INTWARNL_MAX             (185U)                /* For intermittent sound (low urgency) MAX                   */
#define WCHIME_VOL_BASE_INTWARNM_MID             (186U)                /* For intermittent sound (moderate urgency) MID              */
#define WCHIME_VOL_BASE_INTWARNM_MAX             (187U)                /* For intermittent sound (moderate urgency) MAX              */
#define WCHIME_VOL_BASE_INTWARNH_MID             (188U)                /* For intermittent sound (high urgency) MID                  */
#define WCHIME_VOL_BASE_INTWARNH_MAX             (189U)                /* For intermittent sound (high urgency) MAX                  */
#define WCHIME_VOL_BASE_CONTWARN_MID             (190U)                /* For continuous sound MID                                   */
#define WCHIME_VOL_BASE_CONTWARN_MAX             (191U)                /* For continuous sound MAX                                   */
#define WCHIME_VOL_AD_DOT_MID                    (192U)                /* PreDOT Sound MID                                           */
#define WCHIME_VOL_AD_DOT_MAX                    (193U)                /* PreDOT Sound MAX                                           */
#define WCHIME_VOL_ADAS_MID                      (194U)                /* ADAS Tab Display Area Buzzer MID                           */
#define WCHIME_VOL_ADAS_MAX                      (195U)                /* ADAS Tab Display Area Buzzer MAX                           */
#define WCHIME_VOL_AT_MID                        (196U)                /* AT Buzzer MID                                              */
#define WCHIME_VOL_AT_MAX                        (197U)                /* AT Buzzer MAX                                              */

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
