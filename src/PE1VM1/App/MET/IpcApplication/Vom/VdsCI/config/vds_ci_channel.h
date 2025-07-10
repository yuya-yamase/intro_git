/* 2.5.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vehicle Driving Support Configuration/Calibration Interface                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef VDS_CI_CHANNEL_H
#define VDS_CI_CHANNEL_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDS_CI_CHANNEL_H_MAJOR                 (2)
#define VDS_CI_CHANNEL_H_MINOR                 (5)
#define VDS_CI_CHANNEL_H_PATCH                 (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDS_CI_NUM_CH         (167U)

#define VDS_CI_SW_ASD_CONT    ( 0U)
#define VDS_CI_SW_ASD_CANC    ( 1U)
#define VDS_CI_SW_METSPDIS    ( 2U)
#define VDS_CI_SW_FCMUSER     ( 3U)
#define VDS_CI_SW_LCASGAPR    ( 4U)
#define VDS_CI_SW_ST_TDEF     ( 5U)
#define VDS_CI_SW_ST_TAUTO    ( 6U)
#define VDS_CI_SW_ST_ACOFF    ( 7U)
#define VDS_CI_SW_VRESTPSW    ( 8U)
#define VDS_CI_SW_M_SETSTS    ( 9U)
#define VDS_CI_SW_M_SETNXT    (10U)
#define VDS_CI_SW_PSRSP1      (11U)
#define VDS_CI_SW_PSRSP2      (12U)
#define VDS_CI_SW_PSRSP3      (13U)
#define VDS_CI_SW_PLUSSW      (14U)
#define VDS_CI_SW_M_COP_S     (15U)
#define VDS_CI_SW_M_OP_SUP    (16U)
#define VDS_CI_SW_PWSPSWAC    (17U)
#define VDS_CI_SW_BSMMSW      (18U)
#define VDS_CI_SW_CSRMSW      (19U)
#define VDS_CI_SW_FCMMSW      (20U)
#define VDS_CI_SW_ICSMSW      (21U)
#define VDS_CI_SW_LDA_SFB     (22U)
#define VDS_CI_SW_LDAMCUS     (23U)
#define VDS_CI_SW_PCSMSW      (24U)
#define VDS_CI_SW_RCTAMSW     (25U)
#define VDS_CI_SW_SW_DEA01    (26U)
#define VDS_CI_SW_SW_LTC01    (27U)
#define VDS_CI_SW_SW_RCD01    (28U)
#define VDS_CI_SW_TSR_OSL     (29U)
#define VDS_CI_SW_TSR_SNM     (30U)
#define VDS_CI_SW_RSCSW_OP    (31U)
#define VDS_CI_SW_TPINSEL     (32U)
#define VDS_CI_SW_TPINSELF    (33U)
#define VDS_CI_SW_TPINSELR    (34U)
#define VDS_CI_SW_TPUNTSET    (35U)
#define VDS_CI_SW_MINTRSOF    (36U)
#define VDS_CI_SW_PBDBZMVL    (37U)
#define VDS_CI_SW_PBDKSW      (38U)
#define VDS_CI_SW_PBDMCUS     (39U)
#define VDS_CI_SW_PBDMSW      (40U)
#define VDS_CI_SW_RSRMSW      (41U)
#define VDS_CI_SW_PSR_EN      (42U)
#define VDS_CI_SW_PSR_PSSR    (43U)
#define VDS_CI_SW_SR_BACK     (44U)
#define VDS_CI_SW_SR_COM      (45U)
#define VDS_CI_SW_SR_DRV      (46U)
#define VDS_CI_SW_SR_ST       (47U)
#define VDS_CI_SW_SR_TOP      (48U)
#define VDS_CI_SW_CLOCK_SU    (49U)
#define VDS_CI_SW_M_CUR200    (50U)
#define VDS_CI_SW_M_DPWREQ    (51U)
#define VDS_CI_SW_M_LMTREQ    (52U)
#define VDS_CI_SW_M_SLMREQ    (53U)
#define VDS_CI_SW_MRMRQBK     (54U)
#define VDS_CI_SW_MRMRQSW     (55U)
#define VDS_CI_SW_PWSPL_BK    (56U)
#define VDS_CI_SW_PWSPL_OK    (57U)
#define VDS_CI_SW_PWSPL_SU    (58U)
#define VDS_CI_SW_TBCSW       (59U)
#define VDS_CI_SW_BSMM_ILV    (60U)
#define VDS_CI_SW_IDASESW     (61U)
#define VDS_CI_SW_LCASGMSW    (62U)
#define VDS_CI_SW_LDASW       (63U)
#define VDS_CI_SW_PKSSVOL     (64U)
#define VDS_CI_SW_RSR_TIM     (65U)
#define VDS_CI_SW_RTAN_TIM    (66U)
#define VDS_CI_SW_ACCACLSW    (67U)
#define VDS_CI_SW_ACCRACSW    (68U)
#define VDS_CI_SW_ACCROSSW    (69U)
#define VDS_CI_SW_ACCSSOSW    (70U)
#define VDS_CI_SW_CTAMSW      (71U)
#define VDS_CI_SW_RTAN_MSW    (72U)
#define VDS_CI_SW_TSR_MAIN    (73U)
#define VDS_CI_SW_M_WEEK      (74U)
#define VDS_CI_SW_M_SETID     (75U)
#define VDS_CI_SW_M_SETTYP    (76U)
#define VDS_CI_SW_M_SETWKD    (77U)
#define VDS_CI_SW_CSR_MUTE    (78U)
#define VDS_CI_SW_HOFCUS      (79U)
#define VDS_CI_SW_SW_ITS04    (80U)
#define VDS_CI_SW_ACCADPSW    (81U)
#define VDS_CI_SW_LPSDKSW     (82U)
#define VDS_CI_SW_LPSDBZVL    (83U)
#define VDS_CI_SW_RPSDBZVL    (84U)
#define VDS_CI_SW_RPSDKSW     (85U)
#define VDS_CI_SW_SSMMODE     (86U)
#define VDS_CI_SW_GPFGENSW    (87U)
#define VDS_CI_SW_GPFINDSW    (88U)
#define VDS_CI_SW_ACINV_SW    (89U)
#define VDS_CI_SW_SR_NUM      (90U)
#define VDS_CI_SW_SDGMSW      (91U)
#define VDS_CI_SW_USMMAIN     (92U)
#define VDS_CI_SW_PDAMSW      (93U)
#define VDS_CI_SW_DRECSW      (94U)
#define VDS_CI_SW_ADDS_MSW    (95U)
#define VDS_CI_SW_SPBZ_OPE    (96U)
#define VDS_CI_SW_RSRCANSW    (97U)
#define VDS_CI_SW_VRAPRMSW    (98U)
#define VDS_CI_SW_VRAPMSWS    (99U)
#define VDS_CI_SW_VRAPRDIS    (100U)
#define VDS_CI_SW_RTWMSW      (101U)
#define VDS_CI_SW_BSD_SMSB    (102U)
#define VDS_CI_SW_BSD_SMSS    (103U)
#define VDS_CI_SW_SETDCLVI    (104U)
#define VDS_CI_SW_SETDCLVM    (105U)
#define VDS_CI_SW_METMDREJ    (106U)
#define VDS_CI_SW_TRLC_YN     (107U)
#define VDS_CI_SW_M_SLMDRQ    (108U)
#define VDS_CI_SW_TBWSW       (109U)
#define VDS_CI_SW_ULKMSW      (110U)
#define VDS_CI_SW_LKMSW       (111U)
#define VDS_CI_SW_M_PNCSW     (112U)
#define VDS_CI_SW_LMTDAANS    (113U)
#define VDS_CI_SW_M_OCOFOK    (114U)
#define VDS_CI_SW_SRPMSW      (115U)
#define VDS_CI_SW_RG_MD_SW    (116U)
#define VDS_CI_SW_RNGMSW      (117U)
#define VDS_CI_SW_LDAAMSW     (118U)
#define VDS_CI_SW_RSA_NEM     (119U)
#define VDS_CI_SW_RSA_LSM     (120U)
#define VDS_CI_SW_TRA_SW      (121U)
#define VDS_CI_SW_ERMSW       (122U)
#define VDS_CI_SW_ACCSPMSW    (123U)
#define VDS_CI_SW_ACCGCRSW    (124U)
#define VDS_CI_SW_CCSMDMSW    (125U)
#define VDS_CI_SW_SLSSOSW     (126U)
#define VDS_CI_SW_PMARSW      (127U)
#define VDS_CI_SW_DOAM_SW     (128U)
#define VDS_CI_SW_DOAM_TIM    (129U)
#define VDS_CI_SW_TMNVSW      (130U)
#define VDS_CI_SW_TMNSSW      (131U)
#define VDS_CI_SW_ITSSETSW    (132U)
#define VDS_CI_SW_DISSUISW    (133U)
#define VDS_CI_SW_DM_SW_A2    (134U)
#define VDS_CI_SW_AHSSWVSW    (135U)
#define VDS_CI_SW_AHSSDESW    (136U)
#define VDS_CI_SW_M_BB        (137U)
#define VDS_CI_SW_MLR_BB      (138U)
#define VDS_CI_SW_RLM_BB      (139U)
#define VDS_CI_SW_MRT_BB      (140U)
#define VDS_CI_SW_ART_BB      (141U)
#define VDS_CI_SW_PWLSW       (142U)
#define VDS_CI_SW_WVRD_BB     (143U)
#define VDS_CI_SW_WVRU_BB     (144U)
#define VDS_CI_SW_WROF_BB     (145U)
#define VDS_CI_SW_WRLO_BB     (146U)
#define VDS_CI_SW_WRIN_BB     (147U)
#define VDS_CI_SW_WRSW_BB     (148U)
#define VDS_CI_SW_WSVS_BB     (149U)
#define VDS_CI_SW_TRNBBSW     (150U)
#define VDS_CI_SW_LSW_BB      (151U)
#define VDS_CI_SW_FOG_BB      (152U)
#define VDS_CI_SW_RFG_BB      (153U)
#define VDS_CI_SW_WDI_BB      (154U)
#define VDS_CI_SW_TITE_BB     (155U)
#define VDS_CI_SW_MW_BB       (156U)
#define VDS_CI_SW_AECOSWBB    (157U)
#define VDS_CI_SW_METMDSEL    (158U)
#define VDS_CI_SW_HCSUPEN     (159U)
#define VDS_CI_SW_HCSDWEN     (160U)
#define VDS_CI_SW_HCSMNSW     (161U)
#define VDS_CI_SW_HCSSTPOP    (162U)
#define VDS_CI_SW_ADSEGDSW    (163U)
#define VDS_CI_SW_DPMS_BB     (164U)
#define VDS_CI_SW_POS_CALL    (165U)
#define VDS_CI_SW_POS_REG     (166U)

#define VDS_CI_LCASGAPR_MAX   ( 2U)
#define VDS_CI_M_COP_S_MAX    ( 3U)
#define VDS_CI_M_OP_SUP_OK    ( 1U)
#define VDS_CI_M_OP_SUP_NG    ( 0U)
#define VDS_CI_PWSPSWAC_MAX   ( 2U)
#define VDS_CI_DKMETDL_MAX    ( 2U)
#define VDS_CI_LDA_SFB_MAX    ( 7U)
#define VDS_CI_LDAMCUS_MAX    ( 3U)
#define VDS_CI_TSR_OSL_MAX    ( 3U)
#define VDS_CI_TSR_SNM_MAX    ( 3U)
#define VDS_CI_TPINSEL_MAX    (15U)
#define VDS_CI_TPINSELF_MAX   ( 7U)
#define VDS_CI_TPINSELR_MAX   ( 7U)
#define VDS_CI_TPUNTSET_MAX   ( 7U)
#define VDS_CI_PBDBZMVL_MAX   ( 3U)
#define VDS_CI_PBDMCUS_MAX    ( 7U)
#define VDS_CI_SR_COM_MAX     (15U)
#define VDS_CI_SR_DRV_MAX     ( 7U)
#define VDS_CI_PWSPL_SU_MAX   ( 3U)
#define VDS_CI_BSMM_ILV_MAX   ( 3U)
#define VDS_CI_DOAM_TIM_MAX   ( 3U)
#define VDS_CI_IDASESW_MAX    ( 3U)
#define VDS_CI_PKSSVOL_MAX    ( 3U)
#define VDS_CI_RSR_TIM_MAX    ( 7U)
#define VDS_CI_RTAN_TIM_MAX   ( 3U)
#define VDS_CI_ACCACLSW_MAX   ( 7U)
#define VDS_CI_ACCSSOSW_MAX   ( 3U)
#define VDS_CI_M_WEEK_MAX     ( 7U)
#define VDS_CI_LPSDBZVL_MAX   ( 3U)
#define VDS_CI_RPSDBZVL_MAX   ( 3U)
#define VDS_CI_SSMMODE_MAX    ( 2U)
#define VDS_CI_SR_NUM_MAX     (0xFFU)
#define VDS_CI_VRAPRMSW_MAX   ( 3U)
#define VDS_CI_VRAPMSWS_MAX   ( 3U)
#define VDS_BSD_SMSS_MAX      ( 3U)
#define VDSCI_TRLC_YN_MAX     ( 4U)
#define VDSCI_M_SLMDRQ_MAX    ( 2U)
#define VDS_CI_LMTDAANS_MAX   ( 3U)
#define VDS_CI_LDAAMSW_MAX    ( 7U)
#define VDS_CI_RSA_NEM_MAX    ( 7U)
#define VDS_CI_RSA_LSM_MAX    ( 7U)
#define VDS_CI_TRA_SW_MAX     ( 1U)
#define VDS_CI_ERMSW_MAX      ( 3U)
#define VDS_CI_ACCSPMSW_MAX   ( 7U)
#define VDS_CI_ACCGCRSW_MAX   ( 1U)
#define VDS_CI_CCSMDMSW_MAX   ( 1U)
#define VDS_CI_SLSSOSW_MAX    ( 3U)
#define VDS_CI_PMARSW_MAX     ( 1U)
#define VDS_CI_DOAM_SW_MAX    ( 1U)
#define VDS_CI_TMNVSW_MAX     ( 7U)
#define VDS_CI_TMNSSW_MAX     ( 7U)
#define VDS_CI_ITSSETSW_MAX   ( 1U)
#define VDS_CI_DISSUISW_MAX   ( 1U)
#define VDS_CI_DM_SW_A2_MAX   ( 7U)
#define VDS_CI_AHSSWVSW_MAX   ( 1U)
#define VDS_CI_AHSSDESW_MAX   ( 7U)
#define VDS_CI_M_BB_MAX       ( 4U)
#define VDS_CI_MLR_BB_MAX     ( 2U)
#define VDS_CI_RLM_BB_MAX     ( 3U)
#define VDS_CI_MRT_BB_MAX     ( 3U)
#define VDS_CI_ART_BB_MAX     ( 3U)
#define VDS_CI_TRNBBSW_MAX    ( 7U)
#define VDS_CI_LSW_BB_MAX     ( 7U)
#define VDS_CI_WDI_BB_MAX     ( 3U)
#define VDS_CI_TITE_BB_MAX    (15U)
#define VDS_CI_METMDSEL_MAX   ( 3U)
#define VDS_CI_ADSEGDSW_MAX   ( 3U)
#define VDS_CI_POS_CALL_MAX   ( 3U)
#define VDS_CI_POS_REG_MAX    ( 3U)

/* SETDCLVI */
#define VDS_CI_SETDCLVI_INIT  ( 0U)
#define VDS_CI_SETDCLVI_MAX   ( 3U)

/* SETDCLVM */
#define VDS_CI_SETDCLVM_INIT  ( 0U)
#define VDS_CI_SETDCLVM_MAX   ( 1U)

/* M_SLMREQ */
#define VDS_CI_M_SLMREQ_INIT  ( 7U)
#define VDS_CI_M_SLMREQ_MAX   ( 7U)

/* M_SETSTS */
#define VDS_CI_M_SETSTS_INIT  ( 0U)
#define VDS_CI_M_SETSTS_MAX   ( 3U)

/* M_SETNXT */
#define VDS_CI_M_SETNXT_INIT  ( 0U)
#define VDS_CI_M_SETNXT_MAX   ( 6U)

/* M_SETID */
#define VDS_CI_M_SETID_ID_NUM (0x0FU)
#define VDS_CI_M_SETID_ADD    (0x3EU)
#define VDS_CI_M_SETID_INIT   (0x3FU)
#define VDS_CI_M_SETID_MAX    (0x3FU)

/* M_SETTYP */
#define VDS_CI_M_SETTYP_INIT  ( 0U)
#define VDS_CI_M_SETTYP_START ( 1U)
#define VDS_CI_M_SETTYP_MAX   ( 4U)

/* M_SETWKD */
#define VDS_CI_M_SETWKD_INIT  ( 0U)
#define VDS_CI_M_SETWKD_MAX   ( 7U)

/* M_CUR200 */
#define VDS_CI_M_CUR200_INIT         ( 7U)
#define VDS_CI_M_CUR200_32A          ( 4U)
#define VDS_CI_M_CUR200_MAX          ( 7U)

/* CLOCK_SU */
#define VDS_CI_CLOCK_SU_INIT         ( 0U)
#define VDS_CI_CLOCK_SU_LOCK_UNLOCK  ( 2U)
#define VDS_CI_CLOCK_SU_OFF          ( 5U)

/* M_DPWREQ */
#define VDS_CI_M_DPWREQ_INIT         (15U)
#define VDS_CI_M_DPWREQ_350kW        ( 9U)

/* M_LMTREQ */
#define VDS_CI_M_LMTREQ_INIT         ( 7U)
#define VDS_CI_M_LMTREQ_MAX          ( 7U)
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

#endif      /* VDS_CI_CHANNEL_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  vds_ci_cfg.c                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
