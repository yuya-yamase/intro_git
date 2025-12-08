/* 5.2.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert Matrix                                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef ALERT_MTRX_CFG_H
#define ALERT_MTRX_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "vardef.h"
#include "vehspd_kmph.h"
#include "calibration.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_TASK_NUM_SLOT                      (5U)

#define ALERT_CH_TICK                            (ALERT_MAIN_TICK * ALERT_TASK_NUM_SLOT)

#define ALERT_CAN_SYS_PNC_ALL                    ((U4)OXCAN_SYS_PNC_44 | (U4)OXCAN_SYS_PNC_43 | (U4)OXCAN_SYS_PNC_40 | (U4)OXCAN_SYS_PNC_16)
#define ALERT_CAN_SYS_ALL                        (ALERT_CAN_SYS_PNC_ALL | (U4)OXCAN_SYS_PBA | (U4)OXCAN_SYS_ACC | (U4)OXCAN_SYS_IGR | (U4)OXCAN_SYS_IGP)

#define ALERT_HW_ID_B_WASLEV_WLVL                (U2_MAX)

#define ALERT_CFG_B_BDOOR_RRCY                   (TRUE)
#define ALERT_CFG_B_BDOOR_RLCY                   (TRUE)
#define ALERT_CFG_B_BDOOR_BCTY                   (TRUE)
#define ALERT_CFG_B_BDOOR_LGCY                   (TRUE)
#define ALERT_CFG_B_BDOOR_HDCY_BDB               (TRUE)
#define ALERT_CFG_B_BDOOR_RPSDWARN               (FALSE)
#define ALERT_CFG_B_BDOOR_LPSDWARN               (FALSE)
#define ALERT_CFG_B_BDOOR_SLP_POS                (FALSE)
#define ALERT_CFG_B_TDOOR_RPSDWARN               (FALSE)
#define ALERT_CFG_B_TDOOR_LPSDWARN               (FALSE)
#define ALERT_CFG_B_TDOOR_SLP_POS                (FALSE)
#define ALERT_CFG_B_TDOOR_DISP_TIME              (240000U)

#define ALERT_B_AIRBAG_CH_NUM                    (1U)
#define ALERT_B_AVAS_CH_NUM                      (1U)
#define ALERT_B_BLGT_CH_NUM                      (1U)
#define ALERT_B_BVOOPE_CH_NUM                    (1U)
#define ALERT_B_PBD_CH_NUM                       (1U)
#define ALERT_B_PERSET_CH_NUM                    (1U)
#define ALERT_B_THEAD_CH_NUM                     (1U)
#define ALERT_B_TRFOG_CH_NUM                     (1U)
#define ALERT_B_TTAIL_CH_NUM                     (1U)
#define ALERT_B_WASLEV_CH_NUM                    (1U)
#define ALERT_S_EDSS_CH_NUM                      (1U)
#define ALERT_S_LCA_CH_NUM                       (3U)
#define ALERT_S_SCB_CH_NUM                       (1U)
#define ALERT_B_BDOOR_CH_NUM                     (1U)
#define ALERT_B_LEDHEA_CH_NUM                    (1U)
#define ALERT_B_MLGT_CH_NUM                      (1U)
#define ALERT_B_RSEREM_CH_NUM                    (6U)
#define ALERT_B_SMASTA_CH_NUM                    (6U)
#define ALERT_B_TBEAM12_CH_NUM                   (1U)
#define ALERT_B_TDOOR_CH_NUM                     (1U)
#define ALERT_B_TPWSR_CH_NUM                     (1U)
#define ALERT_B_TRWIP_CH_NUM                     (1U)
#define ALERT_C_BRKBZ_CH_NUM                     (1U)
#define ALERT_C_BRK_2_CH_NUM                     (1U)
#define ALERT_C_BRLV_2_CH_NUM                    (2U)
#define ALERT_C_ECB_CH_NUM                       (1U)
#define ALERT_H_MAICER_CH_NUM                    (4U)
#define ALERT_H_PEXI_CH_NUM                      (2U)
#define ALERT_O_EIGCON_CH_NUM                    (1U)
#define ALERT_S_CLESON_CH_NUM                    (2U)
#define ALERT_S_SEA_CH_NUM                       (1U)
#define ALERT_B_PEDPRO_CH_NUM                    (1U)
#define ALERT_C_ABS_CH_NUM                       (2U)
#define ALERT_C_BRKHLD_CH_NUM                    (3U)
#define ALERT_C_DRS_CH_NUM                       (1U)
#define ALERT_C_EPB_CH_NUM                       (3U)
#define ALERT_C_MCBW_CH_NUM                      (1U)
#define ALERT_C_SLIP_CH_NUM                      (1U)
#define ALERT_C_TPMS_CH_NUM                      (1U)
#define ALERT_C_TRCOFF_CH_NUM                    (1U)
#define ALERT_C_VSCOFF_CH_NUM                    (1U)
#define ALERT_C_STEER_CH_NUM                     (3U)
#define ALERT_H_ACCHOL_CH_NUM                    (1U)
#define ALERT_H_DRIPOW_CH_NUM                    (1U)
#define ALERT_H_ONACCN_CH_NUM                    (1U)
#define ALERT_H_REASYS_CH_NUM                    (2U)
#define ALERT_H_SYSMAL_CH_NUM                    (3U)
#define ALERT_H_TOWWAR_CH_NUM                    (1U)
#define ALERT_B_GRISHU_CH_NUM                    (1U)
#define ALERT_D_SBW_CH_NUM                       (17U)
#define ALERT_M_BGLFSPD_CH_NUM                   (1U)
#define ALERT_M_T120_CH_NUM                      (1U)
#define ALERT_O_CHAMAL_CH_NUM                    (1U)
#define ALERT_S_ACC_CH_NUM                       (1U)
#define ALERT_S_APP_CH_NUM                       (1U)
#define ALERT_S_BSM_CH_NUM                       (1U)
#define ALERT_S_DMC_CH_NUM                       (1U)
#define ALERT_S_FCTA_CH_NUM                      (1U)
#define ALERT_S_LDA_CH_NUM                       (2U)
#define ALERT_S_LTA_2_CH_NUM                     (2U)
#define ALERT_S_PCS1_CH_NUM                      (1U)
#define ALERT_S_RSA_CH_NUM                       (2U)
#define ALERT_S_SWS_CH_NUM                       (1U)
#define ALERT_S_TMN_CH_NUM                       (1U)
#define ALERT_S_DA_CH_NUM                        (1U)
#define ALERT_S_ITS_CH_NUM                       (1U)
#define ALERT_C_AVSWAR_CH_NUM                    (1U)
#define ALERT_D_SFTPOS_CH_NUM                    (2U)
#define ALERT_B_FMSEAT_CH_NUM                    (1U)
#define ALERT_H_REGBRA_CH_NUM                    (1U)
#define ALERT_B_SPAT_CH_NUM                      (1U)
#define ALERT_S_TCHAR_CH_NUM                     (1U)
#define ALERT_B_PBDKS_CH_NUM                     (1U)
#define ALERT_S_PMAR_CH_NUM                      (1U)
#define ALERT_H_BATINS_CH_NUM                    (2U)
#define ALERT_S_FRRADA_CH_NUM                    (2U)
#define ALERT_H_LEAUNF_CH_NUM                    (1U)
#define ALERT_B_TFFOG_CH_NUM                     (1U)
#define ALERT_B_THESEN_CH_NUM                    (1U)
#define ALERT_M_MINDSPWR_CH_NUM                  (1U)
#define ALERT_B_ESWUOC_CH_NUM                    (4U)
#define ALERT_H_TVPSOF_CH_NUM                    (1U)
#define ALERT_B_ALOA2_CH_NUM                     (1U)
#define ALERT_B_RPWSEA_CH_NUM                    (1U)
#define ALERT_H_DCLDSP_CH_NUM                    (1U)
#define ALERT_C_BRPADW_CH_NUM                    (1U)
#define ALERT_C_HCS_CH_NUM                       (3U)
#define ALERT_H_BATTRW_CH_NUM                    (1U)
#define ALERT_O_PDSMAL_CH_NUM                    (2U)
#define ALERT_S_TMTT_CH_NUM                      (1U)
#define ALERT_S_TMBZR_CH_NUM                     (2U)
#define ALERT_B_TURHAZ_CH_NUM                    (2U)

#define ALERT_SPD_STSBIT_VALID                   (VEHSPD_STSBIT_VALID)
#define ALERT_SPD_STSBIT_UNKNOWN                 (VEHSPD_STSBIT_UNKNOWN)
#define ALERT_SPD_STSBIT_INVALID                 (VEHSPD_STSBIT_INVALID)
#define ALERT_SPD_FLUCT_DECR                     (VEHSPD_FLUCT_DECR)
#define ALERT_PTSYS_0F_UNK                       (VDF_PTS_RX_0F_UNK)
#define ALERT_PTSYS_1F_NRX                       (VDF_PTS_RX_1F_NRX)
#define ALERT_STEER_VD_PTSYS_UNDEF               (VDF_PTS_RX_00_UNK)
#define ALERT_STEER_VD_PTSYS_HV                  (VDF_PTS_RX_03_HYB)
#define ALERT_STEER_VD_PTSYS_PHV                 (VDF_PTS_RX_04_HYB_PLU)
#define ALERT_STEER_VD_PTSYS_EV                  (VDF_PTS_RX_05_ELE_BAT)
#define ALERT_STEER_VD_PTSYS_HV_MOT              (VDF_PTS_RX_06_HYB_MOT)
#define ALERT_STEER_VD_PTSYS_FCV                 (VDF_PTS_RX_07_ELE_HYD)
#if 0   /* BEV Rebase provisionally */
#define ALERT_SHIFT_BZ_REV_SOUNDTYPE_IN          (VDF_DS_2E_SBWC2_IN)
#else   /* BEV Rebase provisionally */
#define ALERT_SHIFT_BZ_REV_SOUNDTYPE_IN          (0x00000001U)
#endif   /* BEV Rebase provisionally */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_g_AlertSpdKmphBiased(u2_ap_kmph, u1_a_BC)                (u1_g_VehspdKmphBiased(u2_ap_kmph, u1_a_BC))
#define u1_g_AlertSpdKmphInst(u2_ap_kmph, u1_a_OW_EN)               (u1_g_VehspdKmphInst(u2_ap_kmph, u1_a_OW_EN))
#define u1_g_AlertSpdFluctStat()                                    (u1_g_VehspdFluctStat())
#define u1_g_AlertPtsys()                                           (u1_g_VardefPtsRx())
#if 0   /* BEV Rebase provisionally */
#define u4_g_AlertRevBzrSoundType()                                 (u4_g_VardefDs2E_Las32((U2)VDF_DS_2E_20C2))
#else   /* BEV Rebase provisionally */
#define u4_g_AlertRevBzrSoundType()                                 ((U4)ALERT_SHIFT_BZ_REV_SOUNDTYPE_IN)
#endif   /* BEV Rebase provisionally */
#define u1_g_AlertHcsAscext()                                       (u1_g_VardefHcsRxAscext())

#define u1_g_AlertCfgTAILIsEnable()                                 ((U1)TRUE)
#define u1_g_AlertCfgRFOGIsEnable()                                 ((U1)TRUE)
#define u1_g_AlertCfgHEDLIsEnable()                                 ((U1)TRUE)

#define u1_ALERT_CFG_B_TDOOR_RRCY                                   (u1_CALIB_MCUID0209_RRCYM)
#define u1_ALERT_CFG_B_TDOOR_RLCY                                   (u1_CALIB_MCUID0210_RLCYM)
#define u1_ALERT_CFG_B_TDOOR_BCTY                                   (u1_CALIB_MCUID0211_BCTYM)
#define u1_ALERT_CFG_B_TDOOR_LGCY                                   (u1_CALIB_MCUID0212_LGCYM)
#define u1_ALERT_CFG_B_TDOOR_HDCY_BDB                               (u1_CALIB_MCUID0213_HDCY_BDBM)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Provided  */
void    vd_g_AlertB_blgtInit(void);
void    vd_g_AlertB_bvoopeInit(void);
void    vd_g_AlertB_pbdInit(void);
void    vd_g_AlertB_persetInit(void);
void    vd_g_AlertB_theadInit(void);
void    vd_g_AlertB_trfogInit(void);
void    vd_g_AlertB_ttailInit(void);
void    vd_g_AlertB_waslevInit(void);
void    vd_g_AlertB_bdoorInit(void);
void    vd_g_AlertB_mlgtInit(void);
void    vd_g_AlertB_rseremInit(void);
void    vd_g_AlertB_smastaInit(void);
void    vd_g_AlertB_tbeam12Init(void);
void    vd_g_AlertB_tdoorInit(void);
void    vd_g_AlertB_tpwsrInit(void);
void    vd_g_AlertC_brlv_2Init(void);
void    vd_g_AlertS_seaInit(void);
void    vd_g_AlertC_epbInit(void);
void    vd_g_AlertC_steerInit(void);
void    vd_g_AlertD_sbwInit(void);
void    vd_g_AlertM_bglfspdInit(void);
void    vd_g_AlertB_fmseatInit(void);
void    vd_g_AlertB_pbdksInit(void);
void    vd_g_AlertB_tffogInit(void);
void    vd_g_AlertB_thesenInit(void);
void    vd_g_AlertM_mindspwrInit(void);
void    vd_g_AlertB_eswuocInit(void);
void    vd_g_AlertH_tvpsofInit(void);
void    vd_g_AlertB_aloa2Init(void);
void    vd_g_AlertC_hcsInit(void);
void    vd_g_AlertH_battrwInit(void);
void    vd_g_AlertO_pdsmalInit(void);
void    vd_g_AlertB_turhazInit(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Required  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const ST_ALERT_MTRX         st_gp_ALERT_B_AIRBAG_MTRX[ALERT_B_AIRBAG_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_AVAS_MTRX[ALERT_B_AVAS_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_BLGT_MTRX[ALERT_B_BLGT_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_BVOOPE_MTRX[ALERT_B_BVOOPE_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_PBD_MTRX[ALERT_B_PBD_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_PERSET_MTRX[ALERT_B_PERSET_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_THEAD_MTRX[ALERT_B_THEAD_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_TRFOG_MTRX[ALERT_B_TRFOG_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_TTAIL_MTRX[ALERT_B_TTAIL_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_WASLEV_MTRX[ALERT_B_WASLEV_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_EDSS_MTRX[ALERT_S_EDSS_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_LCA_MTRX[ALERT_S_LCA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_SCB_MTRX[ALERT_S_SCB_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_BDOOR_MTRX[ALERT_B_BDOOR_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_LEDHEA_MTRX[ALERT_B_LEDHEA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_MLGT_MTRX[ALERT_B_MLGT_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_RSEREM_MTRX[ALERT_B_RSEREM_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_SMASTA_MTRX[ALERT_B_SMASTA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_TBEAM12_MTRX[ALERT_B_TBEAM12_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_TDOOR_MTRX[ALERT_B_TDOOR_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_TPWSR_MTRX[ALERT_B_TPWSR_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_TRWIP_MTRX[ALERT_B_TRWIP_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_BRKBZ_MTRX[ALERT_C_BRKBZ_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_BRK_2_MTRX[ALERT_C_BRK_2_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_BRLV_2_MTRX[ALERT_C_BRLV_2_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_ECB_MTRX[ALERT_C_ECB_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_MAICER_MTRX[ALERT_H_MAICER_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_PEXI_MTRX[ALERT_H_PEXI_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_O_EIGCON_MTRX[ALERT_O_EIGCON_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_CLESON_MTRX[ALERT_S_CLESON_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_SEA_MTRX[ALERT_S_SEA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_PEDPRO_MTRX[ALERT_B_PEDPRO_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_ABS_MTRX[ALERT_C_ABS_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_BRKHLD_MTRX[ALERT_C_BRKHLD_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_DRS_MTRX[ALERT_C_DRS_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_EPB_MTRX[ALERT_C_EPB_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_MCBW_MTRX[ALERT_C_MCBW_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_SLIP_MTRX[ALERT_C_SLIP_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_TPMS_MTRX[ALERT_C_TPMS_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_TRCOFF_MTRX[ALERT_C_TRCOFF_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_VSCOFF_MTRX[ALERT_C_VSCOFF_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_STEER_MTRX[ALERT_C_STEER_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_ACCHOL_MTRX[ALERT_H_ACCHOL_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_DRIPOW_MTRX[ALERT_H_DRIPOW_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_ONACCN_MTRX[ALERT_H_ONACCN_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_REASYS_MTRX[ALERT_H_REASYS_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_SYSMAL_MTRX[ALERT_H_SYSMAL_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_TOWWAR_MTRX[ALERT_H_TOWWAR_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_GRISHU_MTRX[ALERT_B_GRISHU_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_D_SBW_MTRX[ALERT_D_SBW_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_M_BGLFSPD_MTRX[ALERT_M_BGLFSPD_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_M_T120_MTRX[ALERT_M_T120_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_O_CHAMAL_MTRX[ALERT_O_CHAMAL_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_ACC_MTRX[ALERT_S_ACC_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_APP_MTRX[ALERT_S_APP_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_BSM_MTRX[ALERT_S_BSM_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_DMC_MTRX[ALERT_S_DMC_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_FCTA_MTRX[ALERT_S_FCTA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_LDA_MTRX[ALERT_S_LDA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_LTA_2_MTRX[ALERT_S_LTA_2_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_PCS1_MTRX[ALERT_S_PCS1_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_RSA_MTRX[ALERT_S_RSA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_SWS_MTRX[ALERT_S_SWS_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_TMN_MTRX[ALERT_S_TMN_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_DA_MTRX[ALERT_S_DA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_ITS_MTRX[ALERT_S_ITS_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_AVSWAR_MTRX[ALERT_C_AVSWAR_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_D_SFTPOS_MTRX[ALERT_D_SFTPOS_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_FMSEAT_MTRX[ALERT_B_FMSEAT_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_REGBRA_MTRX[ALERT_H_REGBRA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_SPAT_MTRX[ALERT_B_SPAT_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_TCHAR_MTRX[ALERT_S_TCHAR_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_PBDKS_MTRX[ALERT_B_PBDKS_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_PMAR_MTRX[ALERT_S_PMAR_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_BATINS_MTRX[ALERT_H_BATINS_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_FRRADA_MTRX[ALERT_S_FRRADA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_LEAUNF_MTRX[ALERT_H_LEAUNF_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_TFFOG_MTRX[ALERT_B_TFFOG_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_THESEN_MTRX[ALERT_B_THESEN_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_M_MINDSPWR_MTRX[ALERT_M_MINDSPWR_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_ESWUOC_MTRX[ALERT_B_ESWUOC_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_TVPSOF_MTRX[ALERT_H_TVPSOF_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_ALOA2_MTRX[ALERT_B_ALOA2_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_RPWSEA_MTRX[ALERT_B_RPWSEA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_DCLDSP_MTRX[ALERT_H_DCLDSP_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_BRPADW_MTRX[ALERT_C_BRPADW_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_HCS_MTRX[ALERT_C_HCS_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_BATTRW_MTRX[ALERT_H_BATTRW_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_O_PDSMAL_MTRX[ALERT_O_PDSMAL_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_TMTT_MTRX[ALERT_S_TMTT_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_TMBZR_MTRX[ALERT_S_TMBZR_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_TURHAZ_MTRX[ALERT_B_TURHAZ_CH_NUM];

#endif      /* ALERT_MTRX_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  alert_mtrx.c                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
