/* 5.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert Matrix                                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Genarete File Version                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_MTRX_C_GENERATE                    (515142646)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_MTRX_C_MAJOR                       (5)
#define ALERT_MTRX_C_MINOR                       (1)
#define ALERT_MTRX_C_PATCH                       (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "fpcall_vd_fvd.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Genarete File Version Check                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_MTRX_C_GENERATE != ALERT_MTRX_H_GENERATE)
#error "alert_mtrx.c and alert_mtrx.h : Creation time is different!"
#endif
#if (ALERT_MTRX_C_GENERATE != ALERT_MTRX_CFG_H_GENERATE)
#error "alert_mtrx.c and alert_mtrx_cfg_private.h : Creation time is different!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_MTRX_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_mtrx.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Project Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if 0   /* BEV BSW provisionally */
#if (__PRJ_LIB_ALERT_D1L1_330D_HEV__ != 1)
#error "alert_mtrx.c : Target project is inactive!"
#endif
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
const ST_ALERT_TASK         st_gp_ALERT_TASK_CFG[]   = {
    /* stp_MTRX,                             u2_ch_begin,                           u1_num_mtrx,                        u1_slot      */
    {  &st_gp_ALERT_B_AIRBAG_MTRX[0],        (U2)ALERT_CH_B_AIRBAG,                 (U1)ALERT_B_AIRBAG_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_B_ALOA_MTRX[0],          (U2)ALERT_CH_B_ALOA,                   (U1)ALERT_B_ALOA_CH_NUM,            (U1)0U  },
    {  &st_gp_ALERT_B_ALOA2_MTRX[0],         (U2)ALERT_CH_B_ALOA2,                  (U1)ALERT_B_ALOA2_CH_NUM,           (U1)0U  },
    {  &st_gp_ALERT_B_AVAS_MTRX[0],          (U2)ALERT_CH_B_AVAS,                   (U1)ALERT_B_AVAS_CH_NUM,            (U1)0U  },
    {  &st_gp_ALERT_B_BLGT_MTRX[0],          (U2)ALERT_CH_B_BLGT,                   (U1)ALERT_B_BLGT_CH_NUM,            (U1)0U  },
    {  &st_gp_ALERT_B_BVOOPE_MTRX[0],        (U2)ALERT_CH_B_BVOOPE,                 (U1)ALERT_B_BVOOPE_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_B_PBD_MTRX[0],           (U2)ALERT_CH_B_PBD,                    (U1)ALERT_B_PBD_CH_NUM,             (U1)0U  },
    {  &st_gp_ALERT_B_PERSET_MTRX[0],        (U2)ALERT_CH_B_PERSET,                 (U1)ALERT_B_PERSET_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_B_THEAD_MTRX[0],         (U2)ALERT_CH_B_THEAD,                  (U1)ALERT_B_THEAD_CH_NUM,           (U1)0U  },
    {  &st_gp_ALERT_B_TRFOG_MTRX[0],         (U2)ALERT_CH_B_TRFOG,                  (U1)ALERT_B_TRFOG_CH_NUM,           (U1)0U  },
    {  &st_gp_ALERT_B_TTAIL_MTRX[0],         (U2)ALERT_CH_B_TTAIL,                  (U1)ALERT_B_TTAIL_CH_NUM,           (U1)0U  },
    {  &st_gp_ALERT_B_WASLEV_MTRX[0],        (U2)ALERT_CH_B_WASLEV,                 (U1)ALERT_B_WASLEV_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_O_POWMAN_MTRX[0],        (U2)ALERT_CH_O_POWMAN,                 (U1)ALERT_O_POWMAN_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_S_EDSS_MTRX[0],          (U2)ALERT_CH_S_EDSS_BC,                (U1)ALERT_S_EDSS_CH_NUM,            (U1)0U  },
    {  &st_gp_ALERT_S_ITS_MTRX[0],           (U2)ALERT_CH_S_ITS_TT,                 (U1)ALERT_S_ITS_CH_NUM,             (U1)0U  },
    {  &st_gp_ALERT_S_LCA_MTRX[0],           (U2)ALERT_CH_S_LCA_TT_L,               (U1)ALERT_S_LCA_CH_NUM,             (U1)0U  },
    {  &st_gp_ALERT_S_PSSDI_RWRN_MTRX[0],    (U2)ALERT_CH_S_PSSDI_RWRN,             (U1)ALERT_S_PSSDI_RWRN_CH_NUM,      (U1)0U  },
    {  &st_gp_ALERT_S_SCB_MTRX[0],           (U2)ALERT_CH_S_SCB,                    (U1)ALERT_S_SCB_CH_NUM,             (U1)0U  },
    {  &st_gp_ALERT_B_BDOOR_MTRX[0],         (U2)ALERT_CH_B_BDOOR,                  (U1)ALERT_B_BDOOR_CH_NUM,           (U1)0U  },
    {  &st_gp_ALERT_B_LEDHEA_MTRX[0],        (U2)ALERT_CH_B_LEDHEA,                 (U1)ALERT_B_LEDHEA_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_B_MLGT_MTRX[0],          (U2)ALERT_CH_B_MLGT,                   (U1)ALERT_B_MLGT_CH_NUM,            (U1)0U  },
    {  &st_gp_ALERT_B_RSEREM_MTRX[0],        (U2)ALERT_CH_B_RSEREM_IGOFF,           (U1)ALERT_B_RSEREM_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_B_SMASTA_MTRX[0],        (U2)ALERT_CH_B_SMASTA_S1B,             (U1)ALERT_B_SMASTA_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_B_TBEAM12_MTRX[0],       (U2)ALERT_CH_B_TBEAM12,                (U1)ALERT_B_TBEAM12_CH_NUM,         (U1)0U  },
    {  &st_gp_ALERT_B_TDOOR_MTRX[0],         (U2)ALERT_CH_B_TDOOR,                  (U1)ALERT_B_TDOOR_CH_NUM,           (U1)0U  },
    {  &st_gp_ALERT_B_TPWSR_MTRX[0],         (U2)ALERT_CH_B_TPWSR,                  (U1)ALERT_B_TPWSR_CH_NUM,           (U1)0U  },
    {  &st_gp_ALERT_B_TRWIP_MTRX[0],         (U2)ALERT_CH_B_TRWIP,                  (U1)ALERT_B_TRWIP_CH_NUM,           (U1)0U  },
    {  &st_gp_ALERT_C_BRKBZ_MTRX[0],         (U2)ALERT_CH_C_BRKBZ,                  (U1)ALERT_C_BRKBZ_CH_NUM,           (U1)0U  },
    {  &st_gp_ALERT_C_BRK_0_MTRX[0],         (U2)ALERT_CH_C_BRK_0,                  (U1)ALERT_C_BRK_0_CH_NUM,           (U1)0U  },
    {  &st_gp_ALERT_C_BRK_2_MTRX[0],         (U2)ALERT_CH_C_BRK_2,                  (U1)ALERT_C_BRK_2_CH_NUM,           (U1)0U  },
    {  &st_gp_ALERT_C_BRLV_2_MTRX[0],        (U2)ALERT_CH_C_BRLV_2_WRN,             (U1)ALERT_C_BRLV_2_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_C_ECB_MTRX[0],           (U2)ALERT_CH_C_ECB,                    (U1)ALERT_C_ECB_CH_NUM,             (U1)0U  },
    {  &st_gp_ALERT_C_PKBWAR_MTRX[0],        (U2)ALERT_CH_C_PKBWAR_BC,              (U1)ALERT_C_PKBWAR_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_D_ATMAL_MTRX[0],         (U2)ALERT_CH_D_ATMAL,                  (U1)ALERT_D_ATMAL_CH_NUM,           (U1)0U  },
    {  &st_gp_ALERT_H_MAICER_MTRX[0],        (U2)ALERT_CH_H_MAICER_PD1,             (U1)ALERT_H_MAICER_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_H_PEXI_MTRX[0],          (U2)ALERT_CH_H_PEXI_TT,                (U1)ALERT_H_PEXI_CH_NUM,            (U1)0U  },
    {  &st_gp_ALERT_H_UNIOVE_MTRX[0],        (U2)ALERT_CH_H_UNIOVE_TT_BC,           (U1)ALERT_H_UNIOVE_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_M_VCOPE_MTRX[0],         (U2)ALERT_CH_M_VCOPE,                  (U1)ALERT_M_VCOPE_CH_NUM,           (U1)0U  },
    {  &st_gp_ALERT_O_EIGCON_MTRX[0],        (U2)ALERT_CH_O_EIGCON_ENG,             (U1)ALERT_O_EIGCON_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_P_CHEENG_MTRX[0],        (U2)ALERT_CH_P_CHEENG_WRN,             (U1)ALERT_P_CHEENG_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_P_OILPRE_MTRX[0],        (U2)ALERT_CH_P_OILPRE_WRN,             (U1)ALERT_P_OILPRE_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_P_ROLAWA_MTRX[0],        (U2)ALERT_CH_P_ROLAWA_BC,              (U1)ALERT_P_ROLAWA_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_P_STOSTA_MTRX[0],        (U2)ALERT_CH_P_STOSTA_TT,              (U1)ALERT_P_STOSTA_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_P_TMNT_MTRX[0],          (U2)ALERT_CH_P_TMNT_TT,                (U1)ALERT_P_TMNT_CH_NUM,            (U1)0U  },
    {  &st_gp_ALERT_S_ADASTT_MTRX[0],        (U2)ALERT_CH_S_ADASTT_TT,              (U1)ALERT_S_ADASTT_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_S_BOS_MTRX[0],           (U2)ALERT_CH_S_BOS,                    (U1)ALERT_S_BOS_CH_NUM,             (U1)0U  },
    {  &st_gp_ALERT_S_CLESON_MTRX[0],        (U2)ALERT_CH_S_CLESON_TT,              (U1)ALERT_S_CLESON_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_S_DSC_MTRX[0],           (U2)ALERT_CH_S_DSC,                    (U1)ALERT_S_DSC_CH_NUM,             (U1)0U  },
    {  &st_gp_ALERT_S_PKSB_MTRX[0],          (U2)ALERT_CH_S_PKSB_TT,                (U1)ALERT_S_PKSB_CH_NUM,            (U1)0U  },
    {  &st_gp_ALERT_S_PLUSSP_MTRX[0],        (U2)ALERT_CH_S_PLUSSP,                 (U1)ALERT_S_PLUSSP_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_S_PMAR_MTRX[0],          (U2)ALERT_CH_S_PMAR_BC,                (U1)ALERT_S_PMAR_CH_NUM,            (U1)0U  },
    {  &st_gp_ALERT_S_SEA_MTRX[0],           (U2)ALERT_CH_S_SEA_BC,                 (U1)ALERT_S_SEA_CH_NUM,             (U1)0U  },
    {  &st_gp_ALERT_B_TFFOG_MTRX[0],         (U2)ALERT_CH_B_TFFOG,                  (U1)ALERT_B_TFFOG_CH_NUM,           (U1)0U  },
    {  &st_gp_ALERT_B_THESEN_MTRX[0],        (U2)ALERT_CH_B_THESEN,                 (U1)ALERT_B_THESEN_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_B_BKEY_MTRX[0],          (U2)ALERT_CH_B_BKEY,                   (U1)ALERT_B_BKEY_CH_NUM,            (U1)0U  },
    {  &st_gp_ALERT_H_TVPSOF_MTRX[0],        (U2)ALERT_CH_H_TVPSOF,                 (U1)ALERT_H_TVPSOF_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_B_RPWSEA_MTRX[0],        (U2)ALERT_CH_B_RPWSEA,                 (U1)ALERT_B_RPWSEA_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_B_PCL_MTRX[0],           (U2)ALERT_CH_B_PCL,                    (U1)ALERT_B_PCL_CH_NUM,             (U1)0U  },
    {  &st_gp_ALERT_C_VSCEXP_MTRX[0],        (U2)ALERT_CH_C_VSCEXP_NOSTEP,          (U1)ALERT_C_VSCEXP_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_H_PRECON_MTRX[0],        (U2)ALERT_CH_H_PRECON,                 (U1)ALERT_H_PRECON_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_C_BRPADW_MTRX[0],        (U2)ALERT_CH_C_BRPADW,                 (U1)ALERT_C_BRPADW_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_C_HCS_MTRX[0],           (U2)ALERT_CH_C_HCS_TTB,                (U1)ALERT_C_HCS_CH_NUM,             (U1)0U  },
    {  &st_gp_ALERT_B_PEDPRO_MTRX[0],        (U2)ALERT_CH_B_PEDPRO,                 (U1)ALERT_B_PEDPRO_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_C_ABS_MTRX[0],           (U2)ALERT_CH_C_ABS_TT,                 (U1)ALERT_C_ABS_CH_NUM,             (U1)1U  },
    {  &st_gp_ALERT_C_BRKHLD_MTRX[0],        (U2)ALERT_CH_C_BRKHLD_STBY,            (U1)ALERT_C_BRKHLD_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_C_DRIMOD_MTRX[0],        (U2)ALERT_CH_C_DRIMOD_TT,              (U1)ALERT_C_DRIMOD_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_C_DRS_MTRX[0],           (U2)ALERT_CH_C_DRS,                    (U1)ALERT_C_DRS_CH_NUM,             (U1)1U  },
    {  &st_gp_ALERT_C_EPB_MTRX[0],           (U2)ALERT_CH_C_EPB_TT_PKB,             (U1)ALERT_C_EPB_CH_NUM,             (U1)1U  },
    {  &st_gp_ALERT_C_MCBW_MTRX[0],          (U2)ALERT_CH_C_MCBW,                   (U1)ALERT_C_MCBW_CH_NUM,            (U1)1U  },
    {  &st_gp_ALERT_C_SLIP_MTRX[0],          (U2)ALERT_CH_C_SLIP,                   (U1)ALERT_C_SLIP_CH_NUM,            (U1)1U  },
    {  &st_gp_ALERT_C_TPKBON_MTRX[0],        (U2)ALERT_CH_C_TPKBON,                 (U1)ALERT_C_TPKBON_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_C_TPMS_MTRX[0],          (U2)ALERT_CH_C_TPMS_TT,                (U1)ALERT_C_TPMS_CH_NUM,            (U1)1U  },
    {  &st_gp_ALERT_C_TRCOFF_MTRX[0],        (U2)ALERT_CH_C_TRCOFF_TT,              (U1)ALERT_C_TRCOFF_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_C_VSCOFF_MTRX[0],        (U2)ALERT_CH_C_VSCOFF,                 (U1)ALERT_C_VSCOFF_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_B_FMSEAT_MTRX[0],        (U2)ALERT_CH_B_FMSEAT,                 (U1)ALERT_B_FMSEAT_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_B_PBDKS_MTRX[0],         (U2)ALERT_CH_B_PBDKS_PD,               (U1)ALERT_B_PBDKS_CH_NUM,           (U1)1U  },
    {  &st_gp_ALERT_D_TATLSD_MTRX[0],        (U2)ALERT_CH_D_TATLSD,                 (U1)ALERT_D_TATLSD_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_S_TLTA_MTRX[0],          (U2)ALERT_CH_S_TLTA_TRST,              (U1)ALERT_S_TLTA_CH_NUM,            (U1)1U  },
    {  &st_gp_ALERT_B_BDOOR_MTRX[0],         (U2)ALERT_CH_B_BDOOR,                  (U1)ALERT_B_BDOOR_CH_NUM,           (U1)1U  },
    {  &st_gp_ALERT_B_LEDHEA_MTRX[0],        (U2)ALERT_CH_B_LEDHEA,                 (U1)ALERT_B_LEDHEA_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_B_MLGT_MTRX[0],          (U2)ALERT_CH_B_MLGT,                   (U1)ALERT_B_MLGT_CH_NUM,            (U1)1U  },
    {  &st_gp_ALERT_B_RSEREM_MTRX[0],        (U2)ALERT_CH_B_RSEREM_IGOFF,           (U1)ALERT_B_RSEREM_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_B_SMASTA_MTRX[0],        (U2)ALERT_CH_B_SMASTA_S1B,             (U1)ALERT_B_SMASTA_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_B_SPAT_MTRX[0],          (U2)ALERT_CH_B_SPAT,                   (U1)ALERT_B_SPAT_CH_NUM,            (U1)1U  },
    {  &st_gp_ALERT_B_TBEAM12_MTRX[0],       (U2)ALERT_CH_B_TBEAM12,                (U1)ALERT_B_TBEAM12_CH_NUM,         (U1)1U  },
    {  &st_gp_ALERT_B_TDOOR_MTRX[0],         (U2)ALERT_CH_B_TDOOR,                  (U1)ALERT_B_TDOOR_CH_NUM,           (U1)1U  },
    {  &st_gp_ALERT_B_TPWSR_MTRX[0],         (U2)ALERT_CH_B_TPWSR,                  (U1)ALERT_B_TPWSR_CH_NUM,           (U1)1U  },
    {  &st_gp_ALERT_B_TRWIP_MTRX[0],         (U2)ALERT_CH_B_TRWIP,                  (U1)ALERT_B_TRWIP_CH_NUM,           (U1)1U  },
    {  &st_gp_ALERT_C_AVSWAR_MTRX[0],        (U2)ALERT_CH_C_AVSWAR,                 (U1)ALERT_C_AVSWAR_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_C_BRKBZ_MTRX[0],         (U2)ALERT_CH_C_BRKBZ,                  (U1)ALERT_C_BRKBZ_CH_NUM,           (U1)1U  },
    {  &st_gp_ALERT_C_BRK_0_MTRX[0],         (U2)ALERT_CH_C_BRK_0,                  (U1)ALERT_C_BRK_0_CH_NUM,           (U1)1U  },
    {  &st_gp_ALERT_C_BRK_2_MTRX[0],         (U2)ALERT_CH_C_BRK_2,                  (U1)ALERT_C_BRK_2_CH_NUM,           (U1)1U  },
    {  &st_gp_ALERT_C_BRLV_2_MTRX[0],        (U2)ALERT_CH_C_BRLV_2_WRN,             (U1)ALERT_C_BRLV_2_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_C_ECB_MTRX[0],           (U2)ALERT_CH_C_ECB,                    (U1)ALERT_C_ECB_CH_NUM,             (U1)1U  },
    {  &st_gp_ALERT_C_PKBWAR_MTRX[0],        (U2)ALERT_CH_C_PKBWAR_BC,              (U1)ALERT_C_PKBWAR_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_D_ATMAL_MTRX[0],         (U2)ALERT_CH_D_ATMAL,                  (U1)ALERT_D_ATMAL_CH_NUM,           (U1)1U  },
    {  &st_gp_ALERT_H_MAICER_MTRX[0],        (U2)ALERT_CH_H_MAICER_PD1,             (U1)ALERT_H_MAICER_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_H_PEXI_MTRX[0],          (U2)ALERT_CH_H_PEXI_TT,                (U1)ALERT_H_PEXI_CH_NUM,            (U1)1U  },
    {  &st_gp_ALERT_H_SPDL_0_MTRX[0],        (U2)ALERT_CH_H_SPDL_0_TT,              (U1)ALERT_H_SPDL_0_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_H_TCBM_MTRX[0],          (U2)ALERT_CH_H_TCBM,                   (U1)ALERT_H_TCBM_CH_NUM,            (U1)1U  },
    {  &st_gp_ALERT_H_UNIOVE_MTRX[0],        (U2)ALERT_CH_H_UNIOVE_TT_BC,           (U1)ALERT_H_UNIOVE_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_M_VCOPE_MTRX[0],         (U2)ALERT_CH_M_VCOPE,                  (U1)ALERT_M_VCOPE_CH_NUM,           (U1)1U  },
    {  &st_gp_ALERT_O_EIGCON_MTRX[0],        (U2)ALERT_CH_O_EIGCON_ENG,             (U1)ALERT_O_EIGCON_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_P_CHADYN_MTRX[0],        (U2)ALERT_CH_P_CHADYN,                 (U1)ALERT_P_CHADYN_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_P_CHEENG_MTRX[0],        (U2)ALERT_CH_P_CHEENG_WRN,             (U1)ALERT_P_CHEENG_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_P_OILPRE_MTRX[0],        (U2)ALERT_CH_P_OILPRE_WRN,             (U1)ALERT_P_OILPRE_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_P_ROLAWA_MTRX[0],        (U2)ALERT_CH_P_ROLAWA_BC,              (U1)ALERT_P_ROLAWA_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_P_STOSTA_MTRX[0],        (U2)ALERT_CH_P_STOSTA_TT,              (U1)ALERT_P_STOSTA_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_P_TMNT_MTRX[0],          (U2)ALERT_CH_P_TMNT_TT,                (U1)ALERT_P_TMNT_CH_NUM,            (U1)1U  },
    {  &st_gp_ALERT_S_FACTMD_MTRX[0],        (U2)ALERT_CH_S_FACTMD,                 (U1)ALERT_S_FACTMD_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_S_FRADAR_MTRX[0],        (U2)ALERT_CH_S_FRADAR,                 (U1)ALERT_S_FRADAR_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_S_FRRADA_MTRX[0],        (U2)ALERT_CH_S_FRRADA_TT,              (U1)ALERT_S_FRRADA_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_S_TCHAR_MTRX[0],         (U2)ALERT_CH_S_TCHAR_BC,               (U1)ALERT_S_TCHAR_CH_NUM,           (U1)1U  },
    {  &st_gp_ALERT_S_ADASTT_MTRX[0],        (U2)ALERT_CH_S_ADASTT_TT,              (U1)ALERT_S_ADASTT_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_S_BOS_MTRX[0],           (U2)ALERT_CH_S_BOS,                    (U1)ALERT_S_BOS_CH_NUM,             (U1)1U  },
    {  &st_gp_ALERT_S_CLESON_MTRX[0],        (U2)ALERT_CH_S_CLESON_TT,              (U1)ALERT_S_CLESON_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_S_DSC_MTRX[0],           (U2)ALERT_CH_S_DSC,                    (U1)ALERT_S_DSC_CH_NUM,             (U1)1U  },
    {  &st_gp_ALERT_S_PKSB_MTRX[0],          (U2)ALERT_CH_S_PKSB_TT,                (U1)ALERT_S_PKSB_CH_NUM,            (U1)1U  },
    {  &st_gp_ALERT_S_PLUSSP_MTRX[0],        (U2)ALERT_CH_S_PLUSSP,                 (U1)ALERT_S_PLUSSP_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_S_PMAR_MTRX[0],          (U2)ALERT_CH_S_PMAR_BC,                (U1)ALERT_S_PMAR_CH_NUM,            (U1)1U  },
    {  &st_gp_ALERT_S_SEA_MTRX[0],           (U2)ALERT_CH_S_SEA_BC,                 (U1)ALERT_S_SEA_CH_NUM,             (U1)1U  },
    {  &st_gp_ALERT_C_OFRMDL_MTRX[0],        (U2)ALERT_CH_C_OFRMDL,                 (U1)ALERT_C_OFRMDL_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_B_BKEY_MTRX[0],          (U2)ALERT_CH_B_BKEY,                   (U1)ALERT_B_BKEY_CH_NUM,            (U1)1U  },
    {  &st_gp_ALERT_C_DAC_MTRX[0],           (U2)ALERT_CH_C_DAC_TT,                 (U1)ALERT_C_DAC_CH_NUM,             (U1)1U  },
    {  &st_gp_ALERT_B_EXTSEA_MTRX[0],        (U2)ALERT_CH_B_EXTSEA,                 (U1)ALERT_B_EXTSEA_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_H_MANBEV_MTRX[0],        (U2)ALERT_CH_H_MANBEV,                 (U1)ALERT_H_MANBEV_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_C_STABI_RWRN_MTRX[0],    (U2)ALERT_CH_C_STABI_RWRN,             (U1)ALERT_C_STABI_RWRN_CH_NUM,      (U1)1U  },
    {  &st_gp_ALERT_C_SDM_RWRN_MTRX[0],      (U2)ALERT_CH_C_SDM_RWRN,               (U1)ALERT_C_SDM_RWRN_CH_NUM,        (U1)1U  },
    {  &st_gp_ALERT_H_DCLDSP_MTRX[0],        (U2)ALERT_CH_H_DCLDSP,                 (U1)ALERT_H_DCLDSP_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_C_BRPADW_MTRX[0],        (U2)ALERT_CH_C_BRPADW,                 (U1)ALERT_C_BRPADW_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_H_ZMILRQ_MTRX[0],        (U2)ALERT_CH_H_ZMILRQ_RWRN,            (U1)ALERT_H_ZMILRQ_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_C_SBRDMB_MTRX[0],        (U2)ALERT_CH_C_SBRDMB,                 (U1)ALERT_C_SBRDMB_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_C_BRK_0_MTRX[0],         (U2)ALERT_CH_C_BRK_0,                  (U1)ALERT_C_BRK_0_CH_NUM,           (U1)2U  },
    {  &st_gp_ALERT_C_STEER_MTRX[0],         (U2)ALERT_CH_C_STEER_TT,               (U1)ALERT_C_STEER_CH_NUM,           (U1)2U  },
    {  &st_gp_ALERT_D_4WDSYS_MTRX[0],        (U2)ALERT_CH_D_4WDSYS_TT,              (U1)ALERT_D_4WDSYS_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_ACCHOL_MTRX[0],        (U2)ALERT_CH_H_ACCHOL,                 (U1)ALERT_H_ACCHOL_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_ACONOF_MTRX[0],        (U2)ALERT_CH_H_ACONOF,                 (U1)ALERT_H_ACONOF_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_BATCOO_MTRX[0],        (U2)ALERT_CH_H_BATCOO_TT_PD,           (U1)ALERT_H_BATCOO_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_BATINS_MTRX[0],        (U2)ALERT_CH_H_BATINS_BC,              (U1)ALERT_H_BATINS_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_BATLOW_MTRX[0],        (U2)ALERT_CH_H_BATLOW,                 (U1)ALERT_H_BATLOW_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_BEVR_MTRX[0],          (U2)ALERT_CH_H_BEVR,                   (U1)ALERT_H_BEVR_CH_NUM,            (U1)2U  },
    {  &st_gp_ALERT_H_DRIPOW_MTRX[0],        (U2)ALERT_CH_H_DRIPOW,                 (U1)ALERT_H_DRIPOW_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_FSIND_MTRX[0],         (U2)ALERT_CH_H_FSIND,                  (U1)ALERT_H_FSIND_CH_NUM,           (U1)2U  },
    {  &st_gp_ALERT_H_LEAUNF_MTRX[0],        (U2)ALERT_CH_H_LEAUNF_PD_PWC,          (U1)ALERT_H_LEAUNF_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_MYROOM_MTRX[0],        (U2)ALERT_CH_H_MYROOM_PD_MSG,          (U1)ALERT_H_MYROOM_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_ONACCN_MTRX[0],        (U2)ALERT_CH_H_ONACCN,                 (U1)ALERT_H_ONACCN_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_ONACCP_MTRX[0],        (U2)ALERT_CH_H_ONACCP,                 (U1)ALERT_H_ONACCP_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_REASYS_MTRX[0],        (U2)ALERT_CH_H_REASYS_TT,              (U1)ALERT_H_REASYS_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_REGBRA_MTRX[0],        (U2)ALERT_CH_H_REGBRA,                 (U1)ALERT_H_REGBRA_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_RESADJ_MTRX[0],        (U2)ALERT_CH_H_RESADJ,                 (U1)ALERT_H_RESADJ_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_SOCLOW_MTRX[0],        (U2)ALERT_CH_H_SOCLOW_TT_PD,           (U1)ALERT_H_SOCLOW_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_SYSMAL_MTRX[0],        (U2)ALERT_CH_H_SYSMAL_BC,              (U1)ALERT_H_SYSMAL_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_TOWWAR_MTRX[0],        (U2)ALERT_CH_H_TOWWAR,                 (U1)ALERT_H_TOWWAR_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_P_BSTMOD_MTRX[0],        (U2)ALERT_CH_P_BSTMOD,                 (U1)ALERT_P_BSTMOD_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_B_BDOOR_MTRX[0],         (U2)ALERT_CH_B_BDOOR,                  (U1)ALERT_B_BDOOR_CH_NUM,           (U1)2U  },
    {  &st_gp_ALERT_B_LEDHEA_MTRX[0],        (U2)ALERT_CH_B_LEDHEA,                 (U1)ALERT_B_LEDHEA_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_B_MLGT_MTRX[0],          (U2)ALERT_CH_B_MLGT,                   (U1)ALERT_B_MLGT_CH_NUM,            (U1)2U  },
    {  &st_gp_ALERT_B_RSEREM_MTRX[0],        (U2)ALERT_CH_B_RSEREM_IGOFF,           (U1)ALERT_B_RSEREM_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_B_SMASTA_MTRX[0],        (U2)ALERT_CH_B_SMASTA_S1B,             (U1)ALERT_B_SMASTA_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_B_TBEAM12_MTRX[0],       (U2)ALERT_CH_B_TBEAM12,                (U1)ALERT_B_TBEAM12_CH_NUM,         (U1)2U  },
    {  &st_gp_ALERT_B_TDOOR_MTRX[0],         (U2)ALERT_CH_B_TDOOR,                  (U1)ALERT_B_TDOOR_CH_NUM,           (U1)2U  },
    {  &st_gp_ALERT_B_TPWSR_MTRX[0],         (U2)ALERT_CH_B_TPWSR,                  (U1)ALERT_B_TPWSR_CH_NUM,           (U1)2U  },
    {  &st_gp_ALERT_B_TRWIP_MTRX[0],         (U2)ALERT_CH_B_TRWIP,                  (U1)ALERT_B_TRWIP_CH_NUM,           (U1)2U  },
    {  &st_gp_ALERT_C_BRKBZ_MTRX[0],         (U2)ALERT_CH_C_BRKBZ,                  (U1)ALERT_C_BRKBZ_CH_NUM,           (U1)2U  },
    {  &st_gp_ALERT_C_BRK_2_MTRX[0],         (U2)ALERT_CH_C_BRK_2,                  (U1)ALERT_C_BRK_2_CH_NUM,           (U1)2U  },
    {  &st_gp_ALERT_C_BRLV_2_MTRX[0],        (U2)ALERT_CH_C_BRLV_2_WRN,             (U1)ALERT_C_BRLV_2_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_C_ECB_MTRX[0],           (U2)ALERT_CH_C_ECB,                    (U1)ALERT_C_ECB_CH_NUM,             (U1)2U  },
    {  &st_gp_ALERT_C_PKBWAR_MTRX[0],        (U2)ALERT_CH_C_PKBWAR_BC,              (U1)ALERT_C_PKBWAR_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_D_ATMAL_MTRX[0],         (U2)ALERT_CH_D_ATMAL,                  (U1)ALERT_D_ATMAL_CH_NUM,           (U1)2U  },
    {  &st_gp_ALERT_H_MAICER_MTRX[0],        (U2)ALERT_CH_H_MAICER_PD1,             (U1)ALERT_H_MAICER_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_NLOCK_MTRX[0],         (U2)ALERT_CH_H_NLOCK,                  (U1)ALERT_H_NLOCK_CH_NUM,           (U1)2U  },
    {  &st_gp_ALERT_H_PEXI_MTRX[0],          (U2)ALERT_CH_H_PEXI_TT,                (U1)ALERT_H_PEXI_CH_NUM,            (U1)2U  },
    {  &st_gp_ALERT_H_THEVM_MTRX[0],         (U2)ALERT_CH_H_THEVM_TT,               (U1)ALERT_H_THEVM_CH_NUM,           (U1)2U  },
    {  &st_gp_ALERT_H_UNIOVE_MTRX[0],        (U2)ALERT_CH_H_UNIOVE_TT_BC,           (U1)ALERT_H_UNIOVE_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_M_VCOPE_MTRX[0],         (U2)ALERT_CH_M_VCOPE,                  (U1)ALERT_M_VCOPE_CH_NUM,           (U1)2U  },
    {  &st_gp_ALERT_O_EIGCON_MTRX[0],        (U2)ALERT_CH_O_EIGCON_ENG,             (U1)ALERT_O_EIGCON_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_P_CHEENG_MTRX[0],        (U2)ALERT_CH_P_CHEENG_WRN,             (U1)ALERT_P_CHEENG_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_P_HTGDMI_MTRX[0],        (U2)ALERT_CH_P_HTGDMI,                 (U1)ALERT_P_HTGDMI_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_P_OILPRE_MTRX[0],        (U2)ALERT_CH_P_OILPRE_WRN,             (U1)ALERT_P_OILPRE_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_P_ROLAWA_MTRX[0],        (U2)ALERT_CH_P_ROLAWA_BC,              (U1)ALERT_P_ROLAWA_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_P_STOSTA_MTRX[0],        (U2)ALERT_CH_P_STOSTA_TT,              (U1)ALERT_P_STOSTA_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_P_TMNT_MTRX[0],          (U2)ALERT_CH_P_TMNT_TT,                (U1)ALERT_P_TMNT_CH_NUM,            (U1)2U  },
    {  &st_gp_ALERT_S_ADASTT_MTRX[0],        (U2)ALERT_CH_S_ADASTT_TT,              (U1)ALERT_S_ADASTT_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_S_BOS_MTRX[0],           (U2)ALERT_CH_S_BOS,                    (U1)ALERT_S_BOS_CH_NUM,             (U1)2U  },
    {  &st_gp_ALERT_S_CLESON_MTRX[0],        (U2)ALERT_CH_S_CLESON_TT,              (U1)ALERT_S_CLESON_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_S_DSC_MTRX[0],           (U2)ALERT_CH_S_DSC,                    (U1)ALERT_S_DSC_CH_NUM,             (U1)2U  },
    {  &st_gp_ALERT_S_PKSB_MTRX[0],          (U2)ALERT_CH_S_PKSB_TT,                (U1)ALERT_S_PKSB_CH_NUM,            (U1)2U  },
    {  &st_gp_ALERT_S_PLUSSP_MTRX[0],        (U2)ALERT_CH_S_PLUSSP,                 (U1)ALERT_S_PLUSSP_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_S_PMAR_MTRX[0],          (U2)ALERT_CH_S_PMAR_BC,                (U1)ALERT_S_PMAR_CH_NUM,            (U1)2U  },
    {  &st_gp_ALERT_S_SEA_MTRX[0],           (U2)ALERT_CH_S_SEA_BC,                 (U1)ALERT_S_SEA_CH_NUM,             (U1)2U  },
    {  &st_gp_ALERT_H_SBMMAL_MTRX[0],        (U2)ALERT_CH_H_SBMMAL,                 (U1)ALERT_H_SBMMAL_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_B_BKEY_MTRX[0],          (U2)ALERT_CH_B_BKEY,                   (U1)ALERT_B_BKEY_CH_NUM,            (U1)2U  },
    {  &st_gp_ALERT_H_CHGCON_MTRX[0],        (U2)ALERT_CH_H_CHGCON,                 (U1)ALERT_H_CHGCON_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_BATREF_MTRX[0],        (U2)ALERT_CH_H_BATREF,                 (U1)ALERT_H_BATREF_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_QUICHA_MTRX[0],        (U2)ALERT_CH_H_QUICHA_CHG,             (U1)ALERT_H_QUICHA_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_SOLCHG_RWRN_MTRX[0],   (U2)ALERT_CH_H_SOLCHG_RWRN,            (U1)ALERT_H_SOLCHG_RWRN_CH_NUM,     (U1)2U  },
    {  &st_gp_ALERT_SLMD_MTRX[0],            (U2)ALERT_CH_SLMD,                     (U1)ALERT_SLMD_CH_NUM,              (U1)2U  },
    {  &st_gp_ALERT_H_PARLON_RWRN_MTRX[0],   (U2)ALERT_CH_H_PARLON_RWRN,            (U1)ALERT_H_PARLON_RWRN_CH_NUM,     (U1)2U  },
    {  &st_gp_ALERT_H_LBW_MTRX[0],           (U2)ALERT_CH_H_LBW,                    (U1)ALERT_H_LBW_CH_NUM,             (U1)2U  },
    {  &st_gp_ALERT_C_BRPADW_MTRX[0],        (U2)ALERT_CH_C_BRPADW,                 (U1)ALERT_C_BRPADW_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_D_4WDSYS_RWRN_MTRX[0],   (U2)ALERT_CH_D_4WDSYS_RWRN,            (U1)ALERT_D_4WDSYS_RWRN_CH_NUM,     (U1)2U  },
    {  &st_gp_ALERT_B_GRISHU_MTRX[0],        (U2)ALERT_CH_B_GRISHU,                 (U1)ALERT_B_GRISHU_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_D_CVTOIL_MTRX[0],        (U2)ALERT_CH_D_CVTOIL,                 (U1)ALERT_D_CVTOIL_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_D_ASLR_MTRX[0],          (U2)ALERT_CH_D_ASLR,                   (U1)ALERT_D_ASLR_CH_NUM,            (U1)3U  },
    {  &st_gp_ALERT_D_SBW_MTRX[0],           (U2)ALERT_CH_D_SBW_BZ_BSFT,            (U1)ALERT_D_SBW_CH_NUM,             (U1)3U  },
    {  &st_gp_ALERT_H_ACDCSUP_MTRX[0],       (U2)ALERT_CH_H_ACDCSUP,                (U1)ALERT_H_ACDCSUP_CH_NUM,         (U1)3U  },
    {  &st_gp_ALERT_H_TEVRN_MTRX[0],         (U2)ALERT_CH_H_TEVRN,                  (U1)ALERT_H_TEVRN_CH_NUM,           (U1)3U  },
    {  &st_gp_ALERT_H_XMDRJT_MTRX[0],        (U2)ALERT_CH_H_XMDRJT_BC,              (U1)ALERT_H_XMDRJT_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_H_XMODE_MTRX[0],         (U2)ALERT_CH_H_XMODE_BC,               (U1)ALERT_H_XMODE_CH_NUM,           (U1)3U  },
    {  &st_gp_ALERT_M_BGLFSPD_MTRX[0],       (U2)ALERT_CH_M_BGLFSPD,                (U1)ALERT_M_BGLFSPD_CH_NUM,         (U1)3U  },
    {  &st_gp_ALERT_M_T120_MTRX[0],          (U2)ALERT_CH_M_T120,                   (U1)ALERT_M_T120_CH_NUM,            (U1)3U  },
    {  &st_gp_ALERT_O_CHAMAL_MTRX[0],        (U2)ALERT_CH_O_CHAMAL,                 (U1)ALERT_O_CHAMAL_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_P_COOTEM_MTRX[0],        (U2)ALERT_CH_P_COOTEM_TT_BC,           (U1)ALERT_P_COOTEM_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_P_FUECAP_MTRX[0],        (U2)ALERT_CH_P_FUECAP_TT,              (U1)ALERT_P_FUECAP_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_P_GPF_MTRX[0],           (U2)ALERT_CH_P_GPF_WRN,                (U1)ALERT_P_GPF_CH_NUM,             (U1)3U  },
    {  &st_gp_ALERT_P_MFLID_MTRX[0],         (U2)ALERT_CH_P_MFLID,                  (U1)ALERT_P_MFLID_CH_NUM,           (U1)3U  },
    {  &st_gp_ALERT_P_MILREQ_MTRX[0],        (U2)ALERT_CH_P_MILREQ,                 (U1)ALERT_P_MILREQ_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_P_OILLEV_MTRX[0],        (U2)ALERT_CH_P_OILLEV,                 (U1)ALERT_P_OILLEV_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_P_OILLVG_MTRX[0],        (U2)ALERT_CH_P_OILLVG,                 (U1)ALERT_P_OILLVG_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_P_OILMIL_MTRX[0],        (U2)ALERT_CH_P_OILMIL,                 (U1)ALERT_P_OILMIL_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_P_PLACON_MTRX[0],        (U2)ALERT_CH_P_PLACON,                 (U1)ALERT_P_PLACON_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_H_EWMUP_MTRX[0],         (U2)ALERT_CH_H_EWMUP,                  (U1)ALERT_H_EWMUP_CH_NUM,           (U1)3U  },
    {  &st_gp_ALERT_B_BDOOR_MTRX[0],         (U2)ALERT_CH_B_BDOOR,                  (U1)ALERT_B_BDOOR_CH_NUM,           (U1)3U  },
    {  &st_gp_ALERT_B_LEDHEA_MTRX[0],        (U2)ALERT_CH_B_LEDHEA,                 (U1)ALERT_B_LEDHEA_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_B_MLGT_MTRX[0],          (U2)ALERT_CH_B_MLGT,                   (U1)ALERT_B_MLGT_CH_NUM,            (U1)3U  },
    {  &st_gp_ALERT_B_RSEREM_MTRX[0],        (U2)ALERT_CH_B_RSEREM_IGOFF,           (U1)ALERT_B_RSEREM_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_B_SMASTA_MTRX[0],        (U2)ALERT_CH_B_SMASTA_S1B,             (U1)ALERT_B_SMASTA_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_B_TBEAM12_MTRX[0],       (U2)ALERT_CH_B_TBEAM12,                (U1)ALERT_B_TBEAM12_CH_NUM,         (U1)3U  },
    {  &st_gp_ALERT_B_TDOOR_MTRX[0],         (U2)ALERT_CH_B_TDOOR,                  (U1)ALERT_B_TDOOR_CH_NUM,           (U1)3U  },
    {  &st_gp_ALERT_B_TPWSR_MTRX[0],         (U2)ALERT_CH_B_TPWSR,                  (U1)ALERT_B_TPWSR_CH_NUM,           (U1)3U  },
    {  &st_gp_ALERT_B_TRWIP_MTRX[0],         (U2)ALERT_CH_B_TRWIP,                  (U1)ALERT_B_TRWIP_CH_NUM,           (U1)3U  },
    {  &st_gp_ALERT_C_BRKBZ_MTRX[0],         (U2)ALERT_CH_C_BRKBZ,                  (U1)ALERT_C_BRKBZ_CH_NUM,           (U1)3U  },
    {  &st_gp_ALERT_C_BRK_0_MTRX[0],         (U2)ALERT_CH_C_BRK_0,                  (U1)ALERT_C_BRK_0_CH_NUM,           (U1)3U  },
    {  &st_gp_ALERT_C_BRK_2_MTRX[0],         (U2)ALERT_CH_C_BRK_2,                  (U1)ALERT_C_BRK_2_CH_NUM,           (U1)3U  },
    {  &st_gp_ALERT_C_BRLV_2_MTRX[0],        (U2)ALERT_CH_C_BRLV_2_WRN,             (U1)ALERT_C_BRLV_2_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_C_ECB_MTRX[0],           (U2)ALERT_CH_C_ECB,                    (U1)ALERT_C_ECB_CH_NUM,             (U1)3U  },
    {  &st_gp_ALERT_C_PKBWAR_MTRX[0],        (U2)ALERT_CH_C_PKBWAR_BC,              (U1)ALERT_C_PKBWAR_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_D_ATMAL_MTRX[0],         (U2)ALERT_CH_D_ATMAL,                  (U1)ALERT_D_ATMAL_CH_NUM,           (U1)3U  },
    {  &st_gp_ALERT_H_MAICER_MTRX[0],        (U2)ALERT_CH_H_MAICER_PD1,             (U1)ALERT_H_MAICER_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_H_PEXI_MTRX[0],          (U2)ALERT_CH_H_PEXI_TT,                (U1)ALERT_H_PEXI_CH_NUM,            (U1)3U  },
    {  &st_gp_ALERT_H_UNIOVE_MTRX[0],        (U2)ALERT_CH_H_UNIOVE_TT_BC,           (U1)ALERT_H_UNIOVE_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_M_VCOPE_MTRX[0],         (U2)ALERT_CH_M_VCOPE,                  (U1)ALERT_M_VCOPE_CH_NUM,           (U1)3U  },
    {  &st_gp_ALERT_O_EIGCON_MTRX[0],        (U2)ALERT_CH_O_EIGCON_ENG,             (U1)ALERT_O_EIGCON_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_P_CHEENG_MTRX[0],        (U2)ALERT_CH_P_CHEENG_WRN,             (U1)ALERT_P_CHEENG_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_P_OILPRE_MTRX[0],        (U2)ALERT_CH_P_OILPRE_WRN,             (U1)ALERT_P_OILPRE_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_P_ROLAWA_MTRX[0],        (U2)ALERT_CH_P_ROLAWA_BC,              (U1)ALERT_P_ROLAWA_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_P_STOSTA_MTRX[0],        (U2)ALERT_CH_P_STOSTA_TT,              (U1)ALERT_P_STOSTA_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_P_TECOLP2_MTRX[0],       (U2)ALERT_CH_P_TECOLP2,                (U1)ALERT_P_TECOLP2_CH_NUM,         (U1)3U  },
    {  &st_gp_ALERT_P_TMNT_MTRX[0],          (U2)ALERT_CH_P_TMNT_TT,                (U1)ALERT_P_TMNT_CH_NUM,            (U1)3U  },
    {  &st_gp_ALERT_S_ADASTT_MTRX[0],        (U2)ALERT_CH_S_ADASTT_TT,              (U1)ALERT_S_ADASTT_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_S_BOS_MTRX[0],           (U2)ALERT_CH_S_BOS,                    (U1)ALERT_S_BOS_CH_NUM,             (U1)3U  },
    {  &st_gp_ALERT_S_CLESON_MTRX[0],        (U2)ALERT_CH_S_CLESON_TT,              (U1)ALERT_S_CLESON_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_S_DSC_MTRX[0],           (U2)ALERT_CH_S_DSC,                    (U1)ALERT_S_DSC_CH_NUM,             (U1)3U  },
    {  &st_gp_ALERT_S_PKSB_MTRX[0],          (U2)ALERT_CH_S_PKSB_TT,                (U1)ALERT_S_PKSB_CH_NUM,            (U1)3U  },
    {  &st_gp_ALERT_S_PLUSSP_MTRX[0],        (U2)ALERT_CH_S_PLUSSP,                 (U1)ALERT_S_PLUSSP_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_S_PMAR_MTRX[0],          (U2)ALERT_CH_S_PMAR_BC,                (U1)ALERT_S_PMAR_CH_NUM,            (U1)3U  },
    {  &st_gp_ALERT_S_SEA_MTRX[0],           (U2)ALERT_CH_S_SEA_BC,                 (U1)ALERT_S_SEA_CH_NUM,             (U1)3U  },
    {  &st_gp_ALERT_D_SFTPOS_MTRX[0],        (U2)ALERT_CH_D_SFTPOS_B_RJTB,          (U1)ALERT_D_SFTPOS_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_P_PLOCK_MTRX[0],         (U2)ALERT_CH_P_PLOCK,                  (U1)ALERT_P_PLOCK_CH_NUM,           (U1)3U  },
    {  &st_gp_ALERT_M_MINDSPWR_MTRX[0],      (U2)ALERT_CH_M_MINDSPWR,               (U1)ALERT_M_MINDSPWR_CH_NUM,        (U1)3U  },
    {  &st_gp_ALERT_B_BKEY_MTRX[0],          (U2)ALERT_CH_B_BKEY,                   (U1)ALERT_B_BKEY_CH_NUM,            (U1)3U  },
    {  &st_gp_ALERT_B_ESWUOC_MTRX[0],        (U2)ALERT_CH_B_ESWUOC_BCB,             (U1)ALERT_B_ESWUOC_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_H_XMGRIP_MTRX[0],        (U2)ALERT_CH_H_XMGRIP_TT_IND,          (U1)ALERT_H_XMGRIP_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_D_TMWRN_MTRX[0],         (U2)ALERT_CH_D_TMWRN,                  (U1)ALERT_D_TMWRN_CH_NUM,           (U1)3U  },
    {  &st_gp_ALERT_P_ENGLIM_MTRX[0],        (U2)ALERT_CH_P_ENGLIM,                 (U1)ALERT_P_ENGLIM_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_P_TENGW_MTRX[0],         (U2)ALERT_CH_P_TENGW,                  (U1)ALERT_P_TENGW_CH_NUM,           (U1)3U  },
    {  &st_gp_ALERT_D_IMT_RWRN_MTRX[0],      (U2)ALERT_CH_D_IMT_RWRN,               (U1)ALERT_D_IMT_RWRN_CH_NUM,        (U1)3U  },
    {  &st_gp_ALERT_B_PWSTEP_RWRN_MTRX[0],   (U2)ALERT_CH_B_PWSTEP_RWRN,            (U1)ALERT_B_PWSTEP_RWRN_CH_NUM,     (U1)3U  },
    {  &st_gp_ALERT_P_FFW_RWRN_MTRX[0],      (U2)ALERT_CH_P_FFW_RWRN,               (U1)ALERT_P_FFW_RWRN_CH_NUM,        (U1)3U  },
    {  &st_gp_ALERT_P_DPF_RWRN_MTRX[0],      (U2)ALERT_CH_P_DPF_RWRN,               (U1)ALERT_P_DPF_RWRN_CH_NUM,        (U1)3U  },
    {  &st_gp_ALERT_C_BRPADW_MTRX[0],        (U2)ALERT_CH_C_BRPADW,                 (U1)ALERT_C_BRPADW_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_P_CIRMOD_MTRX[0],        (U2)ALERT_CH_P_CIRMOD_TT_ALC,          (U1)ALERT_P_CIRMOD_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_D_LAUNCH_MTRX[0],        (U2)ALERT_CH_D_LAUNCH,                 (U1)ALERT_D_LAUNCH_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_D_ATFWRN_MTRX[0],        (U2)ALERT_CH_D_ATFWRN_PD,              (U1)ALERT_D_ATFWRN_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_H_EVMOD_MTRX[0],         (U2)ALERT_CH_H_EVMOD_TT,               (U1)ALERT_H_EVMOD_CH_NUM,           (U1)3U  },
    {  &st_gp_ALERT_S_ACC_MTRX[0],           (U2)ALERT_CH_S_ACC_TT_CC,              (U1)ALERT_S_ACC_CH_NUM,             (U1)4U  },
    {  &st_gp_ALERT_S_ADTJA_MTRX[0],         (U2)ALERT_CH_S_ADTJA_TT,               (U1)ALERT_S_ADTJA_CH_NUM,           (U1)4U  },
    {  &st_gp_ALERT_S_AHSS_MTRX[0],          (U2)ALERT_CH_S_AHSS,                   (U1)ALERT_S_AHSS_CH_NUM,            (U1)4U  },
    {  &st_gp_ALERT_S_APP_MTRX[0],           (U2)ALERT_CH_S_APP_BC,                 (U1)ALERT_S_APP_CH_NUM,             (U1)4U  },
    {  &st_gp_ALERT_MET_IPAW_MTRX[0],        (U2)ALERT_CH_MET_IPAW,                 (U1)ALERT_MET_IPAW_CH_NUM,          (U1)4U  },
    {  &st_gp_ALERT_S_BSM_MTRX[0],           (U2)ALERT_CH_S_BSM_BC,                 (U1)ALERT_S_BSM_CH_NUM,             (U1)4U  },
    {  &st_gp_ALERT_S_CCS_MTRX[0],           (U2)ALERT_CH_S_CCS_TT_CC,              (U1)ALERT_S_CCS_CH_NUM,             (U1)4U  },
    {  &st_gp_ALERT_S_CVRS_MTRX[0],          (U2)ALERT_CH_S_CVRS,                   (U1)ALERT_S_CVRS_CH_NUM,            (U1)4U  },
    {  &st_gp_ALERT_S_DMC_MTRX[0],           (U2)ALERT_CH_S_DMC_BC,                 (U1)ALERT_S_DMC_CH_NUM,             (U1)4U  },
    {  &st_gp_ALERT_S_ERM_MTRX[0],           (U2)ALERT_CH_S_ERM_TT,                 (U1)ALERT_S_ERM_CH_NUM,             (U1)4U  },
    {  &st_gp_ALERT_S_FCMDI_RWRN_MTRX[0],    (U2)ALERT_CH_S_FCMDI_RWRN,             (U1)ALERT_S_FCMDI_RWRN_CH_NUM,      (U1)4U  },
    {  &st_gp_ALERT_S_FCTA_MTRX[0],          (U2)ALERT_CH_S_FCTA,                   (U1)ALERT_S_FCTA_CH_NUM,            (U1)4U  },
    {  &st_gp_ALERT_S_FHL_MTRX[0],           (U2)ALERT_CH_S_FHL,                    (U1)ALERT_S_FHL_CH_NUM,             (U1)4U  },
    {  &st_gp_ALERT_S_HEAECU_MTRX[0],        (U2)ALERT_CH_S_HEAECU,                 (U1)ALERT_S_HEAECU_CH_NUM,          (U1)4U  },
    {  &st_gp_ALERT_S_HEALEV_MTRX[0],        (U2)ALERT_CH_S_HEALEV_TT,              (U1)ALERT_S_HEALEV_CH_NUM,          (U1)4U  },
    {  &st_gp_ALERT_S_ISA_MTRX[0],           (U2)ALERT_CH_S_ISA_TT,                 (U1)ALERT_S_ISA_CH_NUM,             (U1)4U  },
    {  &st_gp_ALERT_S_LDA_MTRX[0],           (U2)ALERT_CH_S_LDA_TT_LDA,             (U1)ALERT_S_LDA_CH_NUM,             (U1)4U  },
    {  &st_gp_ALERT_S_LTA_2_MTRX[0],         (U2)ALERT_CH_S_LTA_2_TT,               (U1)ALERT_S_LTA_2_CH_NUM,           (U1)4U  },
    {  &st_gp_ALERT_S_MAPACC_MTRX[0],        (U2)ALERT_CH_S_MAPACC,                 (U1)ALERT_S_MAPACC_CH_NUM,          (U1)4U  },
    {  &st_gp_ALERT_S_MWL_MTRX[0],           (U2)ALERT_CH_S_MWL_TT_IND,             (U1)ALERT_S_MWL_CH_NUM,             (U1)4U  },
    {  &st_gp_ALERT_S_PCS1_MTRX[0],          (U2)ALERT_CH_S_PCS1_TT,                (U1)ALERT_S_PCS1_CH_NUM,            (U1)4U  },
    {  &st_gp_ALERT_S_OAA_MTRX[0],           (U2)ALERT_CH_S_OAA_BC,                 (U1)ALERT_S_OAA_CH_NUM,             (U1)4U  },
    {  &st_gp_ALERT_S_RCTA_RWRN_MTRX[0],     (U2)ALERT_CH_S_RCTA_RWRN,              (U1)ALERT_S_RCTA_RWRN_CH_NUM,       (U1)4U  },
    {  &st_gp_ALERT_S_RSA_MTRX[0],           (U2)ALERT_CH_S_RSA_BC_SGN,             (U1)ALERT_S_RSA_CH_NUM,             (U1)4U  },
    {  &st_gp_ALERT_S_RTAN_MTRX[0],          (U2)ALERT_CH_S_RTAN,                   (U1)ALERT_S_RTAN_CH_NUM,            (U1)4U  },
    {  &st_gp_ALERT_S_SWS_MTRX[0],           (U2)ALERT_CH_S_SWS_BC,                 (U1)ALERT_S_SWS_CH_NUM,             (U1)4U  },
    {  &st_gp_ALERT_S_TMN_MTRX[0],           (U2)ALERT_CH_S_TMN,                    (U1)ALERT_S_TMN_CH_NUM,             (U1)4U  },
    {  &st_gp_ALERT_S_TSMODE_MTRX[0],        (U2)ALERT_CH_S_TSMODE,                 (U1)ALERT_S_TSMODE_CH_NUM,          (U1)4U  },
    {  &st_gp_ALERT_S_DA_MTRX[0],            (U2)ALERT_CH_S_DA_BC,                  (U1)ALERT_S_DA_CH_NUM,              (U1)4U  },
    {  &st_gp_ALERT_B_BDOOR_MTRX[0],         (U2)ALERT_CH_B_BDOOR,                  (U1)ALERT_B_BDOOR_CH_NUM,           (U1)4U  },
    {  &st_gp_ALERT_B_LEDHEA_MTRX[0],        (U2)ALERT_CH_B_LEDHEA,                 (U1)ALERT_B_LEDHEA_CH_NUM,          (U1)4U  },
    {  &st_gp_ALERT_B_MLGT_MTRX[0],          (U2)ALERT_CH_B_MLGT,                   (U1)ALERT_B_MLGT_CH_NUM,            (U1)4U  },
    {  &st_gp_ALERT_B_RSEREM_MTRX[0],        (U2)ALERT_CH_B_RSEREM_IGOFF,           (U1)ALERT_B_RSEREM_CH_NUM,          (U1)4U  },
    {  &st_gp_ALERT_B_SMASTA_MTRX[0],        (U2)ALERT_CH_B_SMASTA_S1B,             (U1)ALERT_B_SMASTA_CH_NUM,          (U1)4U  },
    {  &st_gp_ALERT_B_TBEAM12_MTRX[0],       (U2)ALERT_CH_B_TBEAM12,                (U1)ALERT_B_TBEAM12_CH_NUM,         (U1)4U  },
    {  &st_gp_ALERT_B_TDOOR_MTRX[0],         (U2)ALERT_CH_B_TDOOR,                  (U1)ALERT_B_TDOOR_CH_NUM,           (U1)4U  },
    {  &st_gp_ALERT_B_TPWSR_MTRX[0],         (U2)ALERT_CH_B_TPWSR,                  (U1)ALERT_B_TPWSR_CH_NUM,           (U1)4U  },
    {  &st_gp_ALERT_B_TRWIP_MTRX[0],         (U2)ALERT_CH_B_TRWIP,                  (U1)ALERT_B_TRWIP_CH_NUM,           (U1)4U  },
    {  &st_gp_ALERT_C_BRKBZ_MTRX[0],         (U2)ALERT_CH_C_BRKBZ,                  (U1)ALERT_C_BRKBZ_CH_NUM,           (U1)4U  },
    {  &st_gp_ALERT_C_BRK_0_MTRX[0],         (U2)ALERT_CH_C_BRK_0,                  (U1)ALERT_C_BRK_0_CH_NUM,           (U1)4U  },
    {  &st_gp_ALERT_C_BRK_2_MTRX[0],         (U2)ALERT_CH_C_BRK_2,                  (U1)ALERT_C_BRK_2_CH_NUM,           (U1)4U  },
    {  &st_gp_ALERT_C_BRLV_2_MTRX[0],        (U2)ALERT_CH_C_BRLV_2_WRN,             (U1)ALERT_C_BRLV_2_CH_NUM,          (U1)4U  },
    {  &st_gp_ALERT_C_ECB_MTRX[0],           (U2)ALERT_CH_C_ECB,                    (U1)ALERT_C_ECB_CH_NUM,             (U1)4U  },
    {  &st_gp_ALERT_C_PKBWAR_MTRX[0],        (U2)ALERT_CH_C_PKBWAR_BC,              (U1)ALERT_C_PKBWAR_CH_NUM,          (U1)4U  },
    {  &st_gp_ALERT_D_ATMAL_MTRX[0],         (U2)ALERT_CH_D_ATMAL,                  (U1)ALERT_D_ATMAL_CH_NUM,           (U1)4U  },
    {  &st_gp_ALERT_H_MAICER_MTRX[0],        (U2)ALERT_CH_H_MAICER_PD1,             (U1)ALERT_H_MAICER_CH_NUM,          (U1)4U  },
    {  &st_gp_ALERT_H_PEXI_MTRX[0],          (U2)ALERT_CH_H_PEXI_TT,                (U1)ALERT_H_PEXI_CH_NUM,            (U1)4U  },
    {  &st_gp_ALERT_H_UNIOVE_MTRX[0],        (U2)ALERT_CH_H_UNIOVE_TT_BC,           (U1)ALERT_H_UNIOVE_CH_NUM,          (U1)4U  },
    {  &st_gp_ALERT_M_VCOPE_MTRX[0],         (U2)ALERT_CH_M_VCOPE,                  (U1)ALERT_M_VCOPE_CH_NUM,           (U1)4U  },
    {  &st_gp_ALERT_O_EIGCON_MTRX[0],        (U2)ALERT_CH_O_EIGCON_ENG,             (U1)ALERT_O_EIGCON_CH_NUM,          (U1)4U  },
    {  &st_gp_ALERT_P_CHEENG_MTRX[0],        (U2)ALERT_CH_P_CHEENG_WRN,             (U1)ALERT_P_CHEENG_CH_NUM,          (U1)4U  },
    {  &st_gp_ALERT_P_OILPRE_MTRX[0],        (U2)ALERT_CH_P_OILPRE_WRN,             (U1)ALERT_P_OILPRE_CH_NUM,          (U1)4U  },
    {  &st_gp_ALERT_P_ROLAWA_MTRX[0],        (U2)ALERT_CH_P_ROLAWA_BC,              (U1)ALERT_P_ROLAWA_CH_NUM,          (U1)4U  },
    {  &st_gp_ALERT_P_STOSTA_MTRX[0],        (U2)ALERT_CH_P_STOSTA_TT,              (U1)ALERT_P_STOSTA_CH_NUM,          (U1)4U  },
    {  &st_gp_ALERT_P_TMNT_MTRX[0],          (U2)ALERT_CH_P_TMNT_TT,                (U1)ALERT_P_TMNT_CH_NUM,            (U1)4U  },
    {  &st_gp_ALERT_S_ADASTT_MTRX[0],        (U2)ALERT_CH_S_ADASTT_TT,              (U1)ALERT_S_ADASTT_CH_NUM,          (U1)4U  },
    {  &st_gp_ALERT_S_BOS_MTRX[0],           (U2)ALERT_CH_S_BOS,                    (U1)ALERT_S_BOS_CH_NUM,             (U1)4U  },
    {  &st_gp_ALERT_S_CLESON_MTRX[0],        (U2)ALERT_CH_S_CLESON_TT,              (U1)ALERT_S_CLESON_CH_NUM,          (U1)4U  },
    {  &st_gp_ALERT_S_DSC_MTRX[0],           (U2)ALERT_CH_S_DSC,                    (U1)ALERT_S_DSC_CH_NUM,             (U1)4U  },
    {  &st_gp_ALERT_S_PKSB_MTRX[0],          (U2)ALERT_CH_S_PKSB_TT,                (U1)ALERT_S_PKSB_CH_NUM,            (U1)4U  },
    {  &st_gp_ALERT_S_PLUSSP_MTRX[0],        (U2)ALERT_CH_S_PLUSSP,                 (U1)ALERT_S_PLUSSP_CH_NUM,          (U1)4U  },
    {  &st_gp_ALERT_S_PMAR_MTRX[0],          (U2)ALERT_CH_S_PMAR_BC,                (U1)ALERT_S_PMAR_CH_NUM,            (U1)4U  },
    {  &st_gp_ALERT_S_SEA_MTRX[0],           (U2)ALERT_CH_S_SEA_BC,                 (U1)ALERT_S_SEA_CH_NUM,             (U1)4U  },
    {  &st_gp_ALERT_B_BKEY_MTRX[0],          (U2)ALERT_CH_B_BKEY,                   (U1)ALERT_B_BKEY_CH_NUM,            (U1)4U  },
    {  &st_gp_ALERT_S_RSRDI_RWRN_MTRX[0],    (U2)ALERT_CH_S_RSRDI_RWRN,             (U1)ALERT_S_RSRDI_RWRN_CH_NUM,      (U1)4U  },
    {  &st_gp_ALERT_C_BRPADW_MTRX[0],        (U2)ALERT_CH_C_BRPADW,                 (U1)ALERT_C_BRPADW_CH_NUM,          (U1)4U  }
};

const U2                    u2_g_ALERT_NUM_TASK      = (U2)sizeof(st_gp_ALERT_TASK_CFG) / (U2)sizeof(st_gp_ALERT_TASK_CFG[0]);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertMtrxInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertMtrxInit(void)
{
    static void     (* const fp_vd_ALERT_MTRX_INIT[])(void) = {
        &vd_g_AlertB_blgtInit,
        &vd_g_AlertB_bvoopeInit,
        &vd_g_AlertB_pbdInit,
        &vd_g_AlertB_persetInit,
        &vd_g_AlertB_theadInit,
        &vd_g_AlertB_trfogInit,
        &vd_g_AlertB_ttailInit,
        &vd_g_AlertB_waslevInit,
        &vd_g_AlertO_powmanInit,
        &vd_g_AlertB_bdoorInit,
        &vd_g_AlertB_mlgtInit,
        &vd_g_AlertB_rseremInit,
        &vd_g_AlertB_smastaInit,
        &vd_g_AlertB_tbeam12Init,
        &vd_g_AlertB_tdoorInit,
        &vd_g_AlertB_tpwsrInit,
        &vd_g_AlertC_brkbzInit,
        &vd_g_AlertC_brlv_2Init,
        &vd_g_AlertC_pkbwarInit,
        &vd_g_AlertO_eigconInit,
        &vd_g_AlertP_oilpreInit,
        &vd_g_AlertP_tmntInit,
        &vd_g_AlertS_clesonInit,
        &vd_g_AlertS_seaInit,
        &vd_g_AlertC_epbInit,
        &vd_g_AlertC_steerInit,
        &vd_g_AlertD_sbwInit,
        &vd_g_AlertH_tevrnInit,
        &vd_g_AlertM_bglfspdInit,
        &vd_g_AlertP_oillevInit,
        &vd_g_AlertC_brk_0Init,
        &vd_g_AlertD_sftposInit,
        &vd_g_AlertB_fmseatInit,
        &vd_g_AlertB_pbdksInit,
        &vd_g_AlertB_tffogInit,
        &vd_g_AlertB_thesenInit,
        &vd_g_AlertH_acdcsupInit,
        &vd_g_AlertM_mindspwrInit,
        &vd_g_AlertB_bkeyInit,
        &vd_g_AlertB_eswuocInit,
        &vd_g_AlertH_tvpsofInit,
        &vd_g_AlertB_aloa2Init,
        &vd_g_AlertH_batrefInit,
        &vd_g_AlertP_cootemInit,
        &vd_g_AlertH_quichaInit,
        &vd_g_AlertC_sbrdmbInit,
        &vd_g_AlertC_hcsInit
    };

    vd_g_Fpcall_vd_Fvd(&fp_vd_ALERT_MTRX_INIT[0], u2_NC_VD_FVD(fp_vd_ALERT_MTRX_INIT));
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0    05/10/2019  YI       New.                                                                                               */
/*  5.1.0    10/15/2024  RS       Change for BEV System_Consideration_1                                                              */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  BEV-1    10/25/2024  RS       Change for BEV System_Consideration_1.(MET-H_DRIPOW-CSTD-1-00-A-C0)                                */
/*  BEV-2    10/30/2024  RS       Change for BEV System_Consideration_1.(MET-H_SYSMAL-CSTD-2-00-A-C0)                                */
/*  BEV-3    11/01/2024  KO       Change for BEV System_Consideration_1.(MET-C_STEER-CSTD-0-00-A-C0)                                 */
/*  BEV-4    11/03/2024  KO       Change for BEV System_Consideration_1.(MET-C_TRCOFF-CSTD-1-00-A-C0)                                */
/*  BEV-5    11/12/2024  KO       Change for BEV System_Consideration_1.(MET-C_BRLV-CSTD-2-00-A-C0)                                  */
/*  BEV-6    11/25/2024  KO       Change for BEV System_Consideration_1.(MET-C_ECB-CSTD-1-00-A-C0 / MET-C_EPB-CSTD-1-00-A-C0)        */
/*  BEV-7    12/20/2024  KO       Change for BEV System_Consideration_1.(MET-H_ZMILREQ-CSTD-1-00-A-C0)                               */
/*  BEV-8     2/10/2025  HF       Change for BEV System_Consideration_1.(MET-D_SBW-CSTD-3-00-A-C0)                                   */
/*  BEV-9     2/10/2025  HF       Change for BEV System_Consideration_1.(MET-C_BRK-CSTD-2-00-A-C0)                                   */
/*                                                                                                                                   */
/*  * YI   = Yoshiki Iwata, Denso                                                                                                    */
/*  * RS   = Ryuki Sako,      Denso Techno                                                                                           */
/*  * KO   = Kazuto Oishi,    Denso Techno                                                                                           */
/*  * HF   = Hinari Fukamachi,KSE                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
