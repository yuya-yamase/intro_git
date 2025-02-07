/* 5.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert Matrix                                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef ALERT_MTRX_CFG_H
#define ALERT_MTRX_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Genarete File Version                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_MTRX_CFG_H_GENERATE                (515142646)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "vardef.h"
#include "vardef_esopt.h"
#include "iohw_diflt.h"
#if 0   /* BEV BSW provisionally */
#else
#include "iohw_adc_channel_STUB.h"
#include "iohw_diflt_sgnl_STUB.h"
#endif
#include "vehspd_kmph.h"
#include "engspd_rpm.h"
#include "odo_km.h"
#include "locale.h"
#include "unitconvrt.h"
#include "veh_opemd.h"
#include "ptsctmp_cel.h"
#if 0   /* BEV BSW provisionally */
#include "flid_open.h"
#endif
#include "calibration.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_TASK_NUM_SLOT                      (5U)

#define ALERT_CH_TICK                            (ALERT_MAIN_TICK * ALERT_TASK_NUM_SLOT)

#define ALERT_HW_ID_B_BKEY_IGN__3P8V             (IOHW_DISGNL_IGN__3P8V)
#define ALERT_HW_ID_B_WASLEV_WLVL                (IOHW_DISGNL_WLVL_IN)
#define ALERT_HW_ID_C_PKBWAR_PKB                 (0xFFU)
#define ALERT_HW_ID_C_TPKBON_PKB                 (0xFFU)
#define ALERT_HW_ID_P_OILLEV_OIL_W               (IOHW_DISGNL_OILLVL)
#define ALERT_HW_ID_P_OILPRE_OP_SW               (IOHW_DISGNL_OIL_P)
#define ALERT_OPT_ID_B_PEDPRO_PUH_FLG            (VDF_ESO_CH_PEDPRO)
#define ALERT_OPT_ID_C_BRKHLD_BHEXIST            (VDF_ESO_CH_BRKHLD)
#define ALERT_OPT_ID_C_DRS_ARS1S90               (VDF_ESO_CH_DRS)
#define ALERT_OPT_ID_C_EPB_EPB                   (VDF_ESO_CH_EPB)
#define ALERT_OPT_ID_C_SLIP_VSCEXIST             (VDF_ESO_CH_VSC)
#define ALERT_OPT_ID_C_TPMS_TPM_DISC             (VDF_ESO_CH_TPMSCHN)
#define ALERT_OPT_ID_C_TPMS_TPM_VAR              (VDF_ESO_CH_TPMS)
#define ALERT_OPT_ID_P_TMNT_ECORUN               (VDF_ESO_CH_ECOFLAG)
#define ALERT_OPT_ID_S_APP_APP_EXT               (VDF_ESO_CH_AUTOP)
#define ALERT_OPT_ID_S_DSC_DSCEXIST              (VDF_ESO_CH_DSC)
#define ALERT_OPT_ID_S_FHL_FHL_EQ                (VDF_ESO_CH_FHL)
#define ALERT_OPT_ID_S_RSA_TSREQPD               (VDF_ESO_CH_RSA)
#define ALERT_OPT_ID_C_AVSWAR_AVSEXT             (VDF_ESO_CH_AVSEXT)
#define ALERT_OPT_ID_D_SFTPOS_VARTRM1            (VDF_ESO_CH_MT)
#define ALERT_OPT_ID_C_BRPADW_PWIINFO            (VDF_ESO_CH_BRPADW)
#define ALERT_OPT_ID_P_MILREQ_PTSYS              (VDF_ESO_CH_PTS_MILREQ)

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

#define ALERT_B_AIRBAG_CH_NUM                    (1U)
#define ALERT_B_ALOA_CH_NUM                      (1U)
#define ALERT_B_AVAS_CH_NUM                      (1U)
#define ALERT_B_BLGT_CH_NUM                      (1U)
#define ALERT_B_BVOOPE_CH_NUM                    (1U)
#define ALERT_B_PBD_CH_NUM                       (1U)
#define ALERT_B_PERSET_CH_NUM                    (1U)
#define ALERT_B_THEAD_CH_NUM                     (1U)
#define ALERT_B_TRFOG_CH_NUM                     (1U)
#define ALERT_B_TTAIL_CH_NUM                     (1U)
#define ALERT_B_WASLEV_CH_NUM                    (1U)
#define ALERT_O_POWMAN_CH_NUM                    (1U)
#define ALERT_S_EDSS_CH_NUM                      (2U)
#define ALERT_S_LCA_CH_NUM                       (7U)
#define ALERT_S_SCB_CH_NUM                       (1U)
#define ALERT_B_BDOOR_CH_NUM                     (1U)
#define ALERT_B_LEDHEA_CH_NUM                    (1U)
#define ALERT_B_MLGT_CH_NUM                      (1U)
#define ALERT_B_RSEREM_CH_NUM                    (6U)
#define ALERT_B_SMASTA_CH_NUM                    (15U)
#define ALERT_B_TBEAM12_CH_NUM                   (1U)
#define ALERT_B_TDOOR_CH_NUM                     (1U)
#define ALERT_B_TPWSR_CH_NUM                     (1U)
#define ALERT_B_TRWIP_CH_NUM                     (1U)
#define ALERT_C_BRKBZ_CH_NUM                     (1U)
#define ALERT_C_BRK_1_CH_NUM                     (1U)
#define ALERT_C_BRLV_1_CH_NUM                    (2U)
#define ALERT_C_ECB_CH_NUM                       (1U)
#define ALERT_C_PKBWAR_CH_NUM                    (2U)
#define ALERT_H_MAICER_CH_NUM                    (4U)
#define ALERT_H_PEXI_CH_NUM                      (2U)
#define ALERT_H_UNIOVE_CH_NUM                    (2U)
#define ALERT_M_VCOPE_CH_NUM                     (1U)
#define ALERT_O_EIGCON_CH_NUM                    (2U)
#define ALERT_P_CHEENG_CH_NUM                    (2U)
#define ALERT_P_OILPRE_CH_NUM                    (2U)
#define ALERT_P_ROLAWA_CH_NUM                    (2U)
#define ALERT_P_TMNT_CH_NUM                      (2U)
#define ALERT_S_ADASTT_CH_NUM                    (6U)
#define ALERT_S_BOS_CH_NUM                       (1U)
#define ALERT_S_CLESON_CH_NUM                    (4U)
#define ALERT_S_DSC_CH_NUM                       (1U)
#define ALERT_S_PKSB_CH_NUM                      (2U)
#define ALERT_S_PLUSSP_CH_NUM                    (1U)
#define ALERT_S_SEA_CH_NUM                       (2U)
#define ALERT_B_PEDPRO_CH_NUM                    (1U)
#define ALERT_C_ABS_CH_NUM                       (2U)
#define ALERT_C_BRKHLD_CH_NUM                    (4U)
#define ALERT_C_DRIMOD_CH_NUM                    (1U)
#define ALERT_C_DRS_CH_NUM                       (1U)
#define ALERT_C_EPB_CH_NUM                       (4U)
#define ALERT_C_MCBW_CH_NUM                      (1U)
#define ALERT_C_SLIP_CH_NUM                      (1U)
#define ALERT_C_TPKBON_CH_NUM                    (1U)
#define ALERT_C_TPMS_CH_NUM                      (3U)
#define ALERT_C_TRCOFF_CH_NUM                    (1U)
#define ALERT_C_VSCOFF_CH_NUM                    (1U)
#define ALERT_C_STEER_CH_NUM                     (4U)
#define ALERT_D_4WDSYS_CH_NUM                    (3U)
#define ALERT_D_ATFWRN_CH_NUM                    (2U)
#define ALERT_H_ACCHOL_CH_NUM                    (1U)
#define ALERT_H_ACONOF_CH_NUM                    (1U)
#define ALERT_H_BATCOO_CH_NUM                    (2U)
#define ALERT_H_BATLOW_CH_NUM                    (1U)
#define ALERT_H_DRIPOW_CH_NUM                    (1U)
#define ALERT_H_EVMOD_CH_NUM                     (3U)
#define ALERT_H_ONACCN_CH_NUM                    (1U)
#define ALERT_H_ONACCP_CH_NUM                    (1U)
#define ALERT_H_REASYS_CH_NUM                    (2U)
#define ALERT_H_RESADJ_CH_NUM                    (1U)
#define ALERT_H_SOCLOW_CH_NUM                    (2U)
#define ALERT_H_SYSMAL_CH_NUM                    (4U)
#define ALERT_H_TOWWAR_CH_NUM                    (1U)
#define ALERT_B_GRISHU_CH_NUM                    (1U)
#define ALERT_D_CVTOIL_CH_NUM                    (1U)
#define ALERT_D_SBW_CH_NUM                       (17U)
#define ALERT_H_TEVRN_CH_NUM                     (1U)
#define ALERT_M_BGLFSPD_CH_NUM                   (1U)
#define ALERT_M_T120_CH_NUM                      (1U)
#define ALERT_O_CHAMAL_CH_NUM                    (1U)
#define ALERT_P_COOTEM_CH_NUM                    (2U)
#define ALERT_P_FUECAP_CH_NUM                    (2U)
#define ALERT_P_GPF_CH_NUM                       (2U)
#define ALERT_P_MFLID_CH_NUM                     (1U)
#define ALERT_P_MILREQ_CH_NUM                    (1U)
#define ALERT_P_OILLEV_CH_NUM                    (1U)
#define ALERT_P_OILMIL_CH_NUM                    (1U)
#define ALERT_P_PLACON_CH_NUM                    (1U)
#define ALERT_S_ACC_CH_NUM                       (5U)
#define ALERT_S_APP_CH_NUM                       (2U)
#define ALERT_S_BSM_CH_NUM                       (2U)
#define ALERT_S_CCS_CH_NUM                       (2U)
#define ALERT_S_CVRS_CH_NUM                      (1U)
#define ALERT_S_DMC_CH_NUM                       (3U)
#define ALERT_S_FCTA_CH_NUM                      (1U)
#define ALERT_S_FHL_CH_NUM                       (1U)
#define ALERT_S_HEAECU_CH_NUM                    (1U)
#define ALERT_S_HEALEV_CH_NUM                    (2U)
#define ALERT_S_ISA_CH_NUM                       (2U)
#define ALERT_S_LDA_CH_NUM                       (4U)
#define ALERT_S_LTA_2_CH_NUM                     (4U)
#define ALERT_S_MWL_CH_NUM                       (2U)
#define ALERT_S_PCS1_CH_NUM                      (6U)
#define ALERT_S_OAA_CH_NUM                       (2U)
#define ALERT_S_RSA_CH_NUM                       (3U)
#define ALERT_S_RTAN_CH_NUM                      (1U)
#define ALERT_S_SWS_CH_NUM                       (2U)
#define ALERT_S_TMN_CH_NUM                       (1U)
#define ALERT_S_TSMODE_CH_NUM                    (1U)
#define ALERT_S_DA_CH_NUM                        (2U)
#define ALERT_S_ITS_CH_NUM                       (4U)
#define ALERT_S_ADTJA_CH_NUM                     (10U)
#define ALERT_C_BRK_0_CH_NUM                     (1U)
#define ALERT_S_FACTMD_CH_NUM                    (1U)
#define ALERT_P_BSTMOD_CH_NUM                    (1U)
#define ALERT_H_NLOCK_CH_NUM                     (1U)
#define ALERT_S_AHSS_CH_NUM                      (1U)
#define ALERT_C_AVSWAR_CH_NUM                    (1U)
#define ALERT_D_SFTPOS_CH_NUM                    (3U)
#define ALERT_P_OILLVG_CH_NUM                    (1U)
#define ALERT_B_FMSEAT_CH_NUM                    (1U)
#define ALERT_D_ASLR_CH_NUM                      (1U)
#define ALERT_H_REGBRA_CH_NUM                    (1U)
#define ALERT_H_BEVR_CH_NUM                      (1U)
#define ALERT_S_ERM_CH_NUM                       (2U)
#define ALERT_S_TLTA_CH_NUM                      (2U)
#define ALERT_D_TATLSD_CH_NUM                    (1U)
#define ALERT_H_SPDL_0_CH_NUM                    (3U)
#define ALERT_B_SPAT_CH_NUM                      (1U)
#define ALERT_P_HTGDMI_CH_NUM                    (1U)
#define ALERT_H_EWMUP_CH_NUM                     (1U)
#define ALERT_S_TCHAR_CH_NUM                     (2U)
#define ALERT_D_ATMAL_CH_NUM                     (1U)
#define ALERT_B_PBDKS_CH_NUM                     (2U)
#define ALERT_S_FRADAR_CH_NUM                    (1U)
#define ALERT_H_FSIND_CH_NUM                     (1U)
#define ALERT_S_PMAR_CH_NUM                      (3U)
#define ALERT_H_BATINS_CH_NUM                    (2U)
#define ALERT_S_FRRADA_CH_NUM                    (3U)
#define ALERT_H_LEAUNF_CH_NUM                    (2U)
#define ALERT_P_CHADYN_CH_NUM                    (1U)
#define ALERT_H_THEVM_CH_NUM                     (2U)
#define ALERT_S_MAPACC_CH_NUM                    (1U)
#define ALERT_P_PLOCK_CH_NUM                     (1U)
#define ALERT_B_TFFOG_CH_NUM                     (1U)
#define ALERT_C_OFRMDL_CH_NUM                    (1U)
#define ALERT_B_THESEN_CH_NUM                    (1U)
#define ALERT_P_TECOLP2_CH_NUM                   (1U)
#define ALERT_H_SBMMAL_CH_NUM                    (1U)
#define ALERT_H_ACDCSUP_CH_NUM                   (1U)
#define ALERT_M_MINDSPWR_CH_NUM                  (1U)
#define ALERT_H_XMDRJT_CH_NUM                    (2U)
#define ALERT_H_XMODE_CH_NUM                     (2U)
#define ALERT_B_BKEY_CH_NUM                      (1U)
#define ALERT_C_DAC_CH_NUM                       (2U)
#define ALERT_B_ESWUOC_CH_NUM                    (4U)
#define ALERT_H_XMGRIP_CH_NUM                    (4U)
#define ALERT_P_STOSTA_CH_NUM                    (5U)
#define ALERT_H_CHGCON_CH_NUM                    (1U)
#define ALERT_H_TVPSOF_CH_NUM                    (1U)
#define ALERT_B_ALOA2_CH_NUM                     (1U)
#define ALERT_D_TMWRN_CH_NUM                     (1U)
#define ALERT_H_BATREF_CH_NUM                    (1U)
#define ALERT_B_RPWSEA_CH_NUM                    (1U)
#define ALERT_H_TCBM_CH_NUM                      (1U)
#define ALERT_B_PCL_CH_NUM                       (1U)
#define ALERT_B_EXTSEA_CH_NUM                    (1U)
#define ALERT_D_LAUNCH_CH_NUM                    (1U)
#define ALERT_H_MYROOM_CH_NUM                    (2U)
#define ALERT_C_VSCEXP_CH_NUM                    (2U)
#define ALERT_P_ENGLIM_CH_NUM                    (1U)
#define ALERT_H_PRECON_CH_NUM                    (1U)
#define ALERT_H_MANBEV_CH_NUM                    (1U)
#define ALERT_P_TENGW_CH_NUM                     (1U)
#define ALERT_H_QUICHA_CH_NUM                    (4U)
#define ALERT_S_FCMDI_RWRN_CH_NUM                (1U)
#define ALERT_S_RSRDI_RWRN_CH_NUM                (1U)
#define ALERT_S_PSSDI_RWRN_CH_NUM                (1U)
#define ALERT_S_RCTA_RWRN_CH_NUM                 (1U)
#define ALERT_C_STABI_RWRN_CH_NUM                (1U)
#define ALERT_C_SDM_RWRN_CH_NUM                  (1U)
#define ALERT_H_SOLCHG_RWRN_CH_NUM               (1U)
#define ALERT_MET_IPAW_CH_NUM                    (1U)
#define ALERT_SLMD_CH_NUM                        (1U)
#define ALERT_D_IMT_RWRN_CH_NUM                  (1U)
#define ALERT_B_PWSTEP_RWRN_CH_NUM               (1U)
#define ALERT_D_4WDSYS_RWRN_CH_NUM               (1U)
#define ALERT_H_DCLDSP_CH_NUM                    (1U)
#define ALERT_P_FFW_RWRN_CH_NUM                  (1U)
#define ALERT_P_DPF_RWRN_CH_NUM                  (1U)
#define ALERT_H_PARLON_RWRN_CH_NUM               (1U)
#define ALERT_H_LBW_CH_NUM                       (1U)
#define ALERT_C_BRPADW_CH_NUM                    (1U)
#define ALERT_H_ZMILRQ_CH_NUM                    (3U)
#define ALERT_P_CIRMOD_CH_NUM                    (4U)
#define ALERT_C_SBRDMB_CH_NUM                    (1U)
#define ALERT_C_HCS_CH_NUM                       (3U)

#define ALERT_SPD_STSBIT_VALID                   (VEHSPD_STSBIT_VALID)
#define ALERT_SPD_STSBIT_UNKNOWN                 (VEHSPD_STSBIT_UNKNOWN)
#define ALERT_SPD_STSBIT_INVALID                 (VEHSPD_STSBIT_INVALID)
#define ALERT_SPD_FLUCT_DECR                     (VEHSPD_FLUCT_DECR)
#define ALERT_RPM_STSBIT_UNKNOWN                 (ENGSPD_STSBIT_UNKNOWN)
#define ALERT_RPM_STSBIT_VALID                   (ENGSPD_STSBIT_VALID)
#define ALERT_RPM_STSBIT_INVALID                 (ENGSPD_STSBIT_INVALID)
#define ALERT_ODO_STSBIT_VALID                   (ODO_STSBIT_VALID)
#define ALERT_UNIT_VAL_DIST_KM                   (UNIT_VAL_DIST_KM)
#define ALERT_UNIT_VAL_DIST_MILE                 (UNIT_VAL_DIST_MILE)
#define ALERT_UNIT_IDX_DIST                      (UNIT_IDX_DIST)
#define ALERT_PTS_INV_ON                         (VEH_OPEMD_PTS_INV_ON)
#define ALERT_PTS_INV_LAS                        (VEH_OPEMD_PTS_INV_LAS)
#define ALERT_PTSCTMP_STSBIT_VALID               (PTSCTMP_STSBIT_VALID)
#define ALERT_PTSCTMP_STSBIT_UNKNOWN             (PTSCTMP_STSBIT_UNKNOWN)
#define ALERT_PTSCTMP_STSBIT_INVALID             (PTSCTMP_STSBIT_INVALID)
#define ALERT_PTSCTMP_STSBIT_WTSW_HI             (PTSCTMP_STSBIT_WTSW_HI)
#define ALERT_PTSCTMP_STSBIT_WTSW_OP             (PTSCTMP_STSBIT_WTSW_OP)
#define ALERT_PTSCTMP_CEL_OFFSET                 (PTSCTMP_CEL_OFFSET)
#define ALERT_ESOPT_NUM_GR                       (VDF_ESO_NOW_AVA)
#define ALERT_PTSYS_0F_UNK                       (VDF_PTS_RX_0F_UNK)
#define ALERT_PTSYS_1F_NRX                       (VDF_PTS_RX_1F_NRX)
#define ALERT_STEER_VD_PTSYS_UNDEF               (VDF_PTS_RX_00_UNK)
#define ALERT_STEER_VD_PTSYS_HV                  (VDF_PTS_RX_03_HYB)
#define ALERT_STEER_VD_PTSYS_PHV                 (VDF_PTS_RX_04_HYB_PLU)
#define ALERT_STEER_VD_PTSYS_EV                  (VDF_PTS_RX_05_ELE_BAT)
#define ALERT_STEER_VD_PTSYS_HV_MOT              (VDF_PTS_RX_06_HYB_MOT)
#define ALERT_STEER_VD_PTSYS_FCV                 (VDF_PTS_RX_07_ELE_HYD)
#define ALERT_ENGTYPE_CAN_IOHW_INVALID           (0x00U)
#define ALERT_ENGTYPE_CAN_VALID                  (0x01U)
#define ALERT_ENGTYPE_IOHW_VALID                 (0x02U)
#define ALERT_ENGTYPE_CAN_IOHW_VALID             (0x03U)
#define ALERT_SHIFT_BZ_REV_DEST_JPN              (VDF_BZ_REV_JPN)
#define ALERT_SHIFT_BZ_REV_SOUNDTYPE_IN          (VDF_DS_2E_SBWC2_IN)
#define ALERT_PARLON_VD_PTSYS_FCV                (VDF_PTS_RX_07_ELE_HYD)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_g_AlertSpdKmphBiased(u2_ap_kmph, u1_a_BC)                (u1_g_VehspdKmphBiased(u2_ap_kmph, u1_a_BC))
#define u1_g_AlertSpdKmphInst(u2_ap_kmph, u1_a_OW_EN)               (u1_g_VehspdKmphInst(u2_ap_kmph, u1_a_OW_EN))
#define u1_g_AlertSpdFluctStat()                                    (u1_g_VehspdFluctStat())
#if 0   /* BEV BSW provisionally */
#define u1_g_AlertEngspdRpmInst(u2p_a_rpm)                          (u1_g_EngspdRpmInst(u2p_a_rpm))
#else
#define u1_g_AlertEngspdRpmInst(u2p_a_rpm)                          ((U1)0U)
#endif
#define u4_g_AlertUnitconvtrKmtoMi(x)                               (u4_g_UnitconvtrKmtoMi(x))
#define u1_g_AlertUnit(u1_a_IDX)                                    (u1_g_Unit(u1_a_IDX))
#if 0   /* BEV BSW provisionally */
#define u1_g_AlertPtsOn(u1_a_INV)                                   (u1_g_VehopemdPtsOn(u1_a_INV))
#else
#define u1_g_AlertPtsOn(u1_a_INV)                                   ((U1)FALSE)
#endif
#define u1_g_AlertPtsys()                                           (u1_g_VardefPtsRx())
#define u1_g_AlertEsOptAvailable(u2_a_CH)                           (u1_g_VardefEsOptAvaByCh(u2_a_CH))
#if 0   /* BEV BSW provisionally */
#define u1_g_AlertFLidopenMsgRqst()                                 (u1_g_FLidopenMsgRqst())
#else
#define u1_g_AlertFLidopenMsgRqst()                                 ((U1)FALSE)
#endif
#define u1_g_AlertOillvSw()                                         ((U1)FALSE)
#define u1_g_AlertShiftSbwFunc()                                    (u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_SBW))
#define u4_g_AlertRevBzrSoundType()                                 (u4_g_VardefDs2E_Las32((U2)VDF_DS_2E_20C2))
#define u1_g_AlertRevBzrDest()                                      (u1_g_VardefBzRevDstByPid())
#define u1_g_AlertZmilrqDispJdg()                                   (u1_g_VardefZmilrqDispJdg())
#define u1_g_AlertHcsAscext()                                       (u1_g_VardefHcsRxAscext())

#define u1_g_AlertCfgP_tmntOdoTripKm(u4p)                           (u1_g_OdoTripKm((U1)ODO_TRIP_CH_OM, (u4p)))
#define u1_g_AlertCfgP_tmntOdoKm(u4p)                               (u1_g_OdoKm((u4p)))
#define vd_g_AlertCfgS_fcmdi2VardefEsOpt(u4_ap_esopt)               (vd_g_VardefEsOptAva((u4_ap_esopt), (U1)VDF_ESO_NOW_AVA))
#define u1_g_AlertCfgTAILIsEnable()                                 ((U1)TRUE)
#define u1_g_AlertCfgRFOGIsEnable()                                 ((U1)TRUE)
#define u1_g_AlertCfgHEDLIsEnable()                                 ((U1)TRUE)
#define u1_g_AlertCfgTMntIsEnable()                                 (u1_g_VardefTmntOpt())
#define u1_g_AlertCfgNCLMTIsEnable()                                ((U1)TRUE)
#define u1_g_AlertCfgDCRCKDSPIsEnable()                             ((U1)TRUE)

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
void    vd_g_AlertO_powmanInit(void);
void    vd_g_AlertB_bdoorInit(void);
void    vd_g_AlertB_mlgtInit(void);
void    vd_g_AlertB_rseremInit(void);
void    vd_g_AlertB_smastaInit(void);
void    vd_g_AlertB_tbeam12Init(void);
void    vd_g_AlertB_tdoorInit(void);
void    vd_g_AlertB_tpwsrInit(void);
void    vd_g_AlertC_brkbzInit(void);
void    vd_g_AlertC_brlv_1Init(void);
void    vd_g_AlertC_pkbwarInit(void);
void    vd_g_AlertO_eigconInit(void);
void    vd_g_AlertP_oilpreInit(void);
void    vd_g_AlertP_tmntInit(void);
void    vd_g_AlertS_clesonInit(void);
void    vd_g_AlertS_seaInit(void);
void    vd_g_AlertC_epbInit(void);
void    vd_g_AlertC_steerInit(void);
void    vd_g_AlertD_sbwInit(void);
void    vd_g_AlertH_tevrnInit(void);
void    vd_g_AlertM_bglfspdInit(void);
void    vd_g_AlertP_oillevInit(void);
void    vd_g_AlertC_brk_0Init(void);
void    vd_g_AlertD_sftposInit(void);
void    vd_g_AlertB_fmseatInit(void);
void    vd_g_AlertB_pbdksInit(void);
void    vd_g_AlertB_tffogInit(void);
void    vd_g_AlertB_thesenInit(void);
void    vd_g_AlertH_acdcsupInit(void);
void    vd_g_AlertM_mindspwrInit(void);
void    vd_g_AlertB_bkeyInit(void);
void    vd_g_AlertB_eswuocInit(void);
void    vd_g_AlertH_tvpsofInit(void);
void    vd_g_AlertB_aloa2Init(void);
void    vd_g_AlertH_batrefInit(void);
void    vd_g_AlertP_cootemInit(void);
void    vd_g_AlertH_quichaInit(void);
void    vd_g_AlertC_sbrdmbInit(void);
void    vd_g_AlertC_hcsInit(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Required  */

/* U1    u1_g_VehspdKmphBiased(U2 * u2_ap_kmph, const U1 u1_a_BC);   */
/* U1    u1_g_VehspdKmphInst(U2 * u2_ap_kmph, const U1 u1_a_OW_EN);  */
/* U1    u1_g_VehspdFluctStat(void);                                 */
/* U1    u1_g_EngspdRpmInst(U2 * u2p_a_rpm);                         */
/* U4    u4_g_UnitconvtrKmtoMi(x);                                   */
/* U1    u1_g_Unit(const U1 u1_a_IDX);                               */
/* U1    u1_g_VehopemdPtsOn(const U1 u1_a_INV);                      */
/* U1    u1_g_VardefPtsRx(void);                                     */
/* U1    u1_g_VardefEsOptAvaByCh(const U2 u2_a_CH);                  */
/* U1    u1_g_VardefOilPressSw(void);                                */
/* U1    u1_g_FLidopenMsgRqst(void);                                 */
/* U1    u1_g_VardefOillvSw(void);                                   */

/* U1    u1_g_AlertCfgP_tmntOdoTripKm(U4 * u4p_a_0p001km);           */
/* void  vd_g_AlertCfgS_fcmdi2VardefEsOpt(U4 * u4_ap_esopt);         */
/* U1    u1_g_AlertCfgS_TinwngIsOpt(void);                           */
/* U1    u1_g_AlertCfgTAILIsEnable(void)                             */
/* U1    u1_g_AlertCfgRFOGIsEnable(void)                             */
/* U1    u1_g_AlertCfgHEDLIsEnable(void)                             */

U1      u1_g_AlertCfgOilrpm(U2 * u2p_a_Rpm);               /* Return : IOHW/CAN Valid/Invalid                */
U1      u1_g_AlertCfgPtsctmpCelFltrd(U2 * u2p_a_0p01cel);  /* Return : VALID/INVALID/UNKNOWN/WTSW_HI/WTSW_OP */
U1      u1_g_AlertCfgPtsctmpCelInst(U2 * u2p_a_0p01cel);   /* Return : VALID/INVALID/UNKNOWN                 */
U1      u1_g_AlertCfgS_cvrsAdds(U1 * u1p_a_rprt, U1 * u1p_a_sfty);  /* Return : VALID/UNKNOWN/INVALID/UNKNOWN&INVALID */
U1      u1_g_AlertCfgC_brk_0IsTmode(void);                 /* Return : TRUE/FALSE                            */
U2      u2_g_AlertCfgC_brk_0EngineRPMVal(void);            /* Return : Engine RPM data                       */
U1      u1_g_AlertCfgP_mflid_FlidCalibJdg(void);           /* Return : OPEN/CLOSE/WAIT/UNKNOWN               */
U1      u1_g_AlertCfgH_tevrnIsEnable(void);                /* Return : TRUE/FALSE                            */
U1      u1_g_AlertCfgIdlstp(void);                         /* Return : TRUE/FALSE                            */
U1      u1_g_AlertCfgEcomodeOn(void);                      /* Return : TRUE/FALSE                            */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const ST_ALERT_MTRX         st_gp_ALERT_B_AIRBAG_MTRX[ALERT_B_AIRBAG_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_ALOA_MTRX[ALERT_B_ALOA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_AVAS_MTRX[ALERT_B_AVAS_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_BLGT_MTRX[ALERT_B_BLGT_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_BVOOPE_MTRX[ALERT_B_BVOOPE_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_PBD_MTRX[ALERT_B_PBD_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_PERSET_MTRX[ALERT_B_PERSET_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_THEAD_MTRX[ALERT_B_THEAD_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_TRFOG_MTRX[ALERT_B_TRFOG_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_TTAIL_MTRX[ALERT_B_TTAIL_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_WASLEV_MTRX[ALERT_B_WASLEV_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_O_POWMAN_MTRX[ALERT_O_POWMAN_CH_NUM];
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
extern const ST_ALERT_MTRX         st_gp_ALERT_C_BRK_1_MTRX[ALERT_C_BRK_1_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_BRLV_1_MTRX[ALERT_C_BRLV_1_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_ECB_MTRX[ALERT_C_ECB_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_PKBWAR_MTRX[ALERT_C_PKBWAR_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_MAICER_MTRX[ALERT_H_MAICER_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_PEXI_MTRX[ALERT_H_PEXI_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_UNIOVE_MTRX[ALERT_H_UNIOVE_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_M_VCOPE_MTRX[ALERT_M_VCOPE_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_O_EIGCON_MTRX[ALERT_O_EIGCON_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_P_CHEENG_MTRX[ALERT_P_CHEENG_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_P_OILPRE_MTRX[ALERT_P_OILPRE_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_P_ROLAWA_MTRX[ALERT_P_ROLAWA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_P_TMNT_MTRX[ALERT_P_TMNT_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_ADASTT_MTRX[ALERT_S_ADASTT_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_BOS_MTRX[ALERT_S_BOS_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_CLESON_MTRX[ALERT_S_CLESON_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_DSC_MTRX[ALERT_S_DSC_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_PKSB_MTRX[ALERT_S_PKSB_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_PLUSSP_MTRX[ALERT_S_PLUSSP_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_SEA_MTRX[ALERT_S_SEA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_PEDPRO_MTRX[ALERT_B_PEDPRO_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_ABS_MTRX[ALERT_C_ABS_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_BRKHLD_MTRX[ALERT_C_BRKHLD_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_DRIMOD_MTRX[ALERT_C_DRIMOD_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_DRS_MTRX[ALERT_C_DRS_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_EPB_MTRX[ALERT_C_EPB_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_MCBW_MTRX[ALERT_C_MCBW_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_SLIP_MTRX[ALERT_C_SLIP_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_TPKBON_MTRX[ALERT_C_TPKBON_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_TPMS_MTRX[ALERT_C_TPMS_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_TRCOFF_MTRX[ALERT_C_TRCOFF_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_VSCOFF_MTRX[ALERT_C_VSCOFF_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_STEER_MTRX[ALERT_C_STEER_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_D_4WDSYS_MTRX[ALERT_D_4WDSYS_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_D_ATFWRN_MTRX[ALERT_D_ATFWRN_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_ACCHOL_MTRX[ALERT_H_ACCHOL_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_ACONOF_MTRX[ALERT_H_ACONOF_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_BATCOO_MTRX[ALERT_H_BATCOO_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_BATLOW_MTRX[ALERT_H_BATLOW_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_DRIPOW_MTRX[ALERT_H_DRIPOW_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_EVMOD_MTRX[ALERT_H_EVMOD_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_ONACCN_MTRX[ALERT_H_ONACCN_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_ONACCP_MTRX[ALERT_H_ONACCP_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_REASYS_MTRX[ALERT_H_REASYS_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_RESADJ_MTRX[ALERT_H_RESADJ_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_SOCLOW_MTRX[ALERT_H_SOCLOW_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_SYSMAL_MTRX[ALERT_H_SYSMAL_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_TOWWAR_MTRX[ALERT_H_TOWWAR_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_GRISHU_MTRX[ALERT_B_GRISHU_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_D_CVTOIL_MTRX[ALERT_D_CVTOIL_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_D_SBW_MTRX[ALERT_D_SBW_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_TEVRN_MTRX[ALERT_H_TEVRN_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_M_BGLFSPD_MTRX[ALERT_M_BGLFSPD_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_M_T120_MTRX[ALERT_M_T120_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_O_CHAMAL_MTRX[ALERT_O_CHAMAL_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_P_COOTEM_MTRX[ALERT_P_COOTEM_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_P_FUECAP_MTRX[ALERT_P_FUECAP_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_P_GPF_MTRX[ALERT_P_GPF_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_P_MFLID_MTRX[ALERT_P_MFLID_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_P_MILREQ_MTRX[ALERT_P_MILREQ_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_P_OILLEV_MTRX[ALERT_P_OILLEV_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_P_OILMIL_MTRX[ALERT_P_OILMIL_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_P_PLACON_MTRX[ALERT_P_PLACON_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_ACC_MTRX[ALERT_S_ACC_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_APP_MTRX[ALERT_S_APP_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_BSM_MTRX[ALERT_S_BSM_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_CCS_MTRX[ALERT_S_CCS_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_CVRS_MTRX[ALERT_S_CVRS_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_DMC_MTRX[ALERT_S_DMC_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_FCTA_MTRX[ALERT_S_FCTA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_FHL_MTRX[ALERT_S_FHL_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_HEAECU_MTRX[ALERT_S_HEAECU_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_HEALEV_MTRX[ALERT_S_HEALEV_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_ISA_MTRX[ALERT_S_ISA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_LDA_MTRX[ALERT_S_LDA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_LTA_2_MTRX[ALERT_S_LTA_2_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_MWL_MTRX[ALERT_S_MWL_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_PCS1_MTRX[ALERT_S_PCS1_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_OAA_MTRX[ALERT_S_OAA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_RSA_MTRX[ALERT_S_RSA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_RTAN_MTRX[ALERT_S_RTAN_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_SWS_MTRX[ALERT_S_SWS_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_TMN_MTRX[ALERT_S_TMN_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_TSMODE_MTRX[ALERT_S_TSMODE_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_DA_MTRX[ALERT_S_DA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_ITS_MTRX[ALERT_S_ITS_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_ADTJA_MTRX[ALERT_S_ADTJA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_BRK_0_MTRX[ALERT_C_BRK_0_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_FACTMD_MTRX[ALERT_S_FACTMD_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_P_BSTMOD_MTRX[ALERT_P_BSTMOD_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_NLOCK_MTRX[ALERT_H_NLOCK_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_AHSS_MTRX[ALERT_S_AHSS_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_AVSWAR_MTRX[ALERT_C_AVSWAR_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_D_SFTPOS_MTRX[ALERT_D_SFTPOS_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_P_OILLVG_MTRX[ALERT_P_OILLVG_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_FMSEAT_MTRX[ALERT_B_FMSEAT_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_D_ASLR_MTRX[ALERT_D_ASLR_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_REGBRA_MTRX[ALERT_H_REGBRA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_BEVR_MTRX[ALERT_H_BEVR_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_ERM_MTRX[ALERT_S_ERM_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_TLTA_MTRX[ALERT_S_TLTA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_D_TATLSD_MTRX[ALERT_D_TATLSD_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_SPDL_0_MTRX[ALERT_H_SPDL_0_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_SPAT_MTRX[ALERT_B_SPAT_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_P_HTGDMI_MTRX[ALERT_P_HTGDMI_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_EWMUP_MTRX[ALERT_H_EWMUP_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_TCHAR_MTRX[ALERT_S_TCHAR_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_D_ATMAL_MTRX[ALERT_D_ATMAL_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_PBDKS_MTRX[ALERT_B_PBDKS_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_FRADAR_MTRX[ALERT_S_FRADAR_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_FSIND_MTRX[ALERT_H_FSIND_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_PMAR_MTRX[ALERT_S_PMAR_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_BATINS_MTRX[ALERT_H_BATINS_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_FRRADA_MTRX[ALERT_S_FRRADA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_LEAUNF_MTRX[ALERT_H_LEAUNF_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_P_CHADYN_MTRX[ALERT_P_CHADYN_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_THEVM_MTRX[ALERT_H_THEVM_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_MAPACC_MTRX[ALERT_S_MAPACC_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_P_PLOCK_MTRX[ALERT_P_PLOCK_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_TFFOG_MTRX[ALERT_B_TFFOG_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_OFRMDL_MTRX[ALERT_C_OFRMDL_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_THESEN_MTRX[ALERT_B_THESEN_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_P_TECOLP2_MTRX[ALERT_P_TECOLP2_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_SBMMAL_MTRX[ALERT_H_SBMMAL_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_ACDCSUP_MTRX[ALERT_H_ACDCSUP_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_M_MINDSPWR_MTRX[ALERT_M_MINDSPWR_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_XMDRJT_MTRX[ALERT_H_XMDRJT_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_XMODE_MTRX[ALERT_H_XMODE_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_BKEY_MTRX[ALERT_B_BKEY_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_DAC_MTRX[ALERT_C_DAC_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_ESWUOC_MTRX[ALERT_B_ESWUOC_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_XMGRIP_MTRX[ALERT_H_XMGRIP_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_P_STOSTA_MTRX[ALERT_P_STOSTA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_CHGCON_MTRX[ALERT_H_CHGCON_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_TVPSOF_MTRX[ALERT_H_TVPSOF_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_ALOA2_MTRX[ALERT_B_ALOA2_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_D_TMWRN_MTRX[ALERT_D_TMWRN_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_BATREF_MTRX[ALERT_H_BATREF_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_RPWSEA_MTRX[ALERT_B_RPWSEA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_TCBM_MTRX[ALERT_H_TCBM_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_PCL_MTRX[ALERT_B_PCL_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_EXTSEA_MTRX[ALERT_B_EXTSEA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_D_LAUNCH_MTRX[ALERT_D_LAUNCH_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_MYROOM_MTRX[ALERT_H_MYROOM_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_VSCEXP_MTRX[ALERT_C_VSCEXP_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_P_ENGLIM_MTRX[ALERT_P_ENGLIM_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_PRECON_MTRX[ALERT_H_PRECON_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_MANBEV_MTRX[ALERT_H_MANBEV_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_P_TENGW_MTRX[ALERT_P_TENGW_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_QUICHA_MTRX[ALERT_H_QUICHA_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_FCMDI_RWRN_MTRX[ALERT_S_FCMDI_RWRN_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_RSRDI_RWRN_MTRX[ALERT_S_RSRDI_RWRN_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_PSSDI_RWRN_MTRX[ALERT_S_PSSDI_RWRN_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_S_RCTA_RWRN_MTRX[ALERT_S_RCTA_RWRN_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_STABI_RWRN_MTRX[ALERT_C_STABI_RWRN_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_SDM_RWRN_MTRX[ALERT_C_SDM_RWRN_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_SOLCHG_RWRN_MTRX[ALERT_H_SOLCHG_RWRN_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_MET_IPAW_MTRX[ALERT_MET_IPAW_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_SLMD_MTRX[ALERT_SLMD_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_D_IMT_RWRN_MTRX[ALERT_D_IMT_RWRN_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_B_PWSTEP_RWRN_MTRX[ALERT_B_PWSTEP_RWRN_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_D_4WDSYS_RWRN_MTRX[ALERT_D_4WDSYS_RWRN_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_DCLDSP_MTRX[ALERT_H_DCLDSP_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_P_FFW_RWRN_MTRX[ALERT_P_FFW_RWRN_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_P_DPF_RWRN_MTRX[ALERT_P_DPF_RWRN_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_PARLON_RWRN_MTRX[ALERT_H_PARLON_RWRN_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_LBW_MTRX[ALERT_H_LBW_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_BRPADW_MTRX[ALERT_C_BRPADW_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_H_ZMILRQ_MTRX[ALERT_H_ZMILRQ_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_P_CIRMOD_MTRX[ALERT_P_CIRMOD_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_SBRDMB_MTRX[ALERT_C_SBRDMB_CH_NUM];
extern const ST_ALERT_MTRX         st_gp_ALERT_C_HCS_MTRX[ALERT_C_HCS_CH_NUM];

#endif      /* ALERT_MTRX_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  alert_mtrx.c                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
