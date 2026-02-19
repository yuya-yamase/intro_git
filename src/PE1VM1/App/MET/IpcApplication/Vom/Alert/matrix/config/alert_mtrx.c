/* 5.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert Matrix                                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_MTRX_C_MAJOR                       (5)
#define ALERT_MTRX_C_MINOR                       (4)
#define ALERT_MTRX_C_PATCH                       (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "fpcall_vd_fvd.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_MTRX_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_mtrx.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Project Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
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
    {  &st_gp_ALERT_B_ALOA2_MTRX[0],         (U2)ALERT_CH_B_ALOA2,                  (U1)ALERT_B_ALOA2_CH_NUM,           (U1)0U  },
    {  &st_gp_ALERT_B_AVAS_MTRX[0],          (U2)ALERT_CH_B_AVAS,                   (U1)ALERT_B_AVAS_CH_NUM,            (U1)0U  },
    {  &st_gp_ALERT_B_BLGT_MTRX[0],          (U2)ALERT_CH_B_BLGT,                   (U1)ALERT_B_BLGT_CH_NUM,            (U1)0U  },
    {  &st_gp_ALERT_B_BVOOPE_MTRX[0],        (U2)ALERT_CH_B_BVOOPE,                 (U1)ALERT_B_BVOOPE_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_B_PBD_MTRX[0],           (U2)ALERT_CH_B_PBD,                    (U1)ALERT_B_PBD_CH_NUM,             (U1)0U  },
    {  &st_gp_ALERT_B_THEAD_MTRX[0],         (U2)ALERT_CH_B_THEAD,                  (U1)ALERT_B_THEAD_CH_NUM,           (U1)0U  },
    {  &st_gp_ALERT_B_TRFOG_MTRX[0],         (U2)ALERT_CH_B_TRFOG,                  (U1)ALERT_B_TRFOG_CH_NUM,           (U1)0U  },
    {  &st_gp_ALERT_B_TTAIL_MTRX[0],         (U2)ALERT_CH_B_TTAIL,                  (U1)ALERT_B_TTAIL_CH_NUM,           (U1)0U  },
    {  &st_gp_ALERT_B_WASLEV_MTRX[0],        (U2)ALERT_CH_B_WASLEV,                 (U1)ALERT_B_WASLEV_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_S_ADBZR_EDSS_MTRX[0],    (U2)ALERT_CH_S_ADBZR_EDSS,             (U1)ALERT_S_ADBZR_EDSS_CH_NUM,      (U1)0U  },
    {  &st_gp_ALERT_S_ADBZR_ITS_MTRX[0],     (U2)ALERT_CH_S_ADBZR_ITS,              (U1)ALERT_S_ADBZR_ITS_CH_NUM,       (U1)0U  },
    {  &st_gp_ALERT_S_ADBZR_LCA_MTRX[0],     (U2)ALERT_CH_S_ADBZR_LCA_RQ,           (U1)ALERT_S_ADBZR_LCA_CH_NUM,       (U1)0U  },
    {  &st_gp_ALERT_S_ADBZR_SCB_MTRX[0],     (U2)ALERT_CH_S_ADBZR_SCB,              (U1)ALERT_S_ADBZR_SCB_CH_NUM,       (U1)0U  },
    {  &st_gp_ALERT_B_BDOOR_MTRX[0],         (U2)ALERT_CH_B_BDOOR,                  (U1)ALERT_B_BDOOR_CH_NUM,           (U1)0U  },
    {  &st_gp_ALERT_B_LEDHEA_MTRX[0],        (U2)ALERT_CH_B_LEDHEA,                 (U1)ALERT_B_LEDHEA_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_B_MLGT_MTRX[0],          (U2)ALERT_CH_B_MLGT,                   (U1)ALERT_B_MLGT_CH_NUM,            (U1)0U  },
    {  &st_gp_ALERT_B_RSEREM_MTRX[0],        (U2)ALERT_CH_B_RSEREM_IGOFF,           (U1)ALERT_B_RSEREM_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_B_SMASTA_MTRX[0],        (U2)ALERT_CH_B_SMASTA_BCDR,            (U1)ALERT_B_SMASTA_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_B_TBEAM12_MTRX[0],       (U2)ALERT_CH_B_TBEAM12,                (U1)ALERT_B_TBEAM12_CH_NUM,         (U1)0U  },
    {  &st_gp_ALERT_B_TDOOR_MTRX[0],         (U2)ALERT_CH_B_TDOOR,                  (U1)ALERT_B_TDOOR_CH_NUM,           (U1)0U  },
    {  &st_gp_ALERT_B_TPWSR_MTRX[0],         (U2)ALERT_CH_B_TPWSR,                  (U1)ALERT_B_TPWSR_CH_NUM,           (U1)0U  },
    {  &st_gp_ALERT_B_TRWIP_MTRX[0],         (U2)ALERT_CH_B_TRWIP,                  (U1)ALERT_B_TRWIP_CH_NUM,           (U1)0U  },
    {  &st_gp_ALERT_C_BRKBZ_MTRX[0],         (U2)ALERT_CH_C_BRKBZ,                  (U1)ALERT_C_BRKBZ_CH_NUM,           (U1)0U  },
    {  &st_gp_ALERT_C_BRK_2_MTRX[0],         (U2)ALERT_CH_C_BRK_2,                  (U1)ALERT_C_BRK_2_CH_NUM,           (U1)0U  },
    {  &st_gp_ALERT_C_BRLV_2_MTRX[0],        (U2)ALERT_CH_C_BRLV_2_WRN,             (U1)ALERT_C_BRLV_2_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_C_ECB_MTRX[0],           (U2)ALERT_CH_C_ECB,                    (U1)ALERT_C_ECB_CH_NUM,             (U1)0U  },
    {  &st_gp_ALERT_H_MAICER_MTRX[0],        (U2)ALERT_CH_H_MAICER_PD1,             (U1)ALERT_H_MAICER_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_H_PEXI_MTRX[0],          (U2)ALERT_CH_H_PEXI,                   (U1)ALERT_H_PEXI_CH_NUM,            (U1)0U  },
    {  &st_gp_ALERT_O_EIGCON_MTRX[0],        (U2)ALERT_CH_O_EIGCON,                 (U1)ALERT_O_EIGCON_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_S_ADBZR_CSR_MTRX[0],     (U2)ALERT_CH_S_ADBZR_CSR_BZ,           (U1)ALERT_S_ADBZR_CSR_CH_NUM,       (U1)0U  },
    {  &st_gp_ALERT_S_ADBZR_PMAR_MTRX[0],    (U2)ALERT_CH_S_ADBZR_PMAR,             (U1)ALERT_S_ADBZR_PMAR_CH_NUM,      (U1)0U  },
    {  &st_gp_ALERT_S_ADBZR_SEA_MTRX[0],     (U2)ALERT_CH_S_ADBZR_SEA,              (U1)ALERT_S_ADBZR_SEA_CH_NUM,       (U1)0U  },
    {  &st_gp_ALERT_B_TFFOG_MTRX[0],         (U2)ALERT_CH_B_TFFOG,                  (U1)ALERT_B_TFFOG_CH_NUM,           (U1)0U  },
    {  &st_gp_ALERT_B_THESEN_MTRX[0],        (U2)ALERT_CH_B_THESEN,                 (U1)ALERT_B_THESEN_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_H_TVPSOF_MTRX[0],        (U2)ALERT_CH_H_TVPSOF,                 (U1)ALERT_H_TVPSOF_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_B_RPWSEA_MTRX[0],        (U2)ALERT_CH_B_RPWSEA,                 (U1)ALERT_B_RPWSEA_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_C_BRPADW_MTRX[0],        (U2)ALERT_CH_C_BRPADW,                 (U1)ALERT_C_BRPADW_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_C_HCS_MTRX[0],           (U2)ALERT_CH_C_HCS_TTB,                (U1)ALERT_C_HCS_CH_NUM,             (U1)0U  },
    {  &st_gp_ALERT_H_BATTRW_MTRX[0],        (U2)ALERT_CH_H_BATTRW,                 (U1)ALERT_H_BATTRW_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_O_PDSMAL_MTRX[0],        (U2)ALERT_CH_O_PDSMAL_BC,              (U1)ALERT_O_PDSMAL_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_B_TURHAZ_MTRX[0],        (U2)ALERT_CH_B_TURHAZ_L,               (U1)ALERT_B_TURHAZ_CH_NUM,          (U1)0U  },
    {  &st_gp_ALERT_B_AIRBAG_MTRX[0],        (U2)ALERT_CH_B_AIRBAG,                 (U1)ALERT_B_AIRBAG_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_B_PEDPRO_MTRX[0],        (U2)ALERT_CH_B_PEDPRO,                 (U1)ALERT_B_PEDPRO_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_C_ABS_MTRX[0],           (U2)ALERT_CH_C_ABS_TT,                 (U1)ALERT_C_ABS_CH_NUM,             (U1)1U  },
    {  &st_gp_ALERT_C_BRKHLD_MTRX[0],        (U2)ALERT_CH_C_BRKHLD_STBY,            (U1)ALERT_C_BRKHLD_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_C_DRS_MTRX[0],           (U2)ALERT_CH_C_DRS,                    (U1)ALERT_C_DRS_CH_NUM,             (U1)1U  },
    {  &st_gp_ALERT_C_EPB_MTRX[0],           (U2)ALERT_CH_C_EPB_TT_PKB,             (U1)ALERT_C_EPB_CH_NUM,             (U1)1U  },
    {  &st_gp_ALERT_C_MCBW_MTRX[0],          (U2)ALERT_CH_C_MCBW,                   (U1)ALERT_C_MCBW_CH_NUM,            (U1)1U  },
    {  &st_gp_ALERT_C_SLIP_MTRX[0],          (U2)ALERT_CH_C_SLIP,                   (U1)ALERT_C_SLIP_CH_NUM,            (U1)1U  },
    {  &st_gp_ALERT_C_TPMS_MTRX[0],          (U2)ALERT_CH_C_TPMS,                   (U1)ALERT_C_TPMS_CH_NUM,            (U1)1U  },
    {  &st_gp_ALERT_C_TRCOFF_MTRX[0],        (U2)ALERT_CH_C_TRCOFF,                 (U1)ALERT_C_TRCOFF_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_C_VSCOFF_MTRX[0],        (U2)ALERT_CH_C_VSCOFF,                 (U1)ALERT_C_VSCOFF_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_B_FMSEAT_MTRX[0],        (U2)ALERT_CH_B_FMSEAT,                 (U1)ALERT_B_FMSEAT_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_B_PBDKS_MTRX[0],         (U2)ALERT_CH_B_PBDKS,                  (U1)ALERT_B_PBDKS_CH_NUM,           (U1)1U  },
    {  &st_gp_ALERT_B_BDOOR_MTRX[0],         (U2)ALERT_CH_B_BDOOR,                  (U1)ALERT_B_BDOOR_CH_NUM,           (U1)1U  },
    {  &st_gp_ALERT_B_LEDHEA_MTRX[0],        (U2)ALERT_CH_B_LEDHEA,                 (U1)ALERT_B_LEDHEA_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_B_MLGT_MTRX[0],          (U2)ALERT_CH_B_MLGT,                   (U1)ALERT_B_MLGT_CH_NUM,            (U1)1U  },
    {  &st_gp_ALERT_B_RSEREM_MTRX[0],        (U2)ALERT_CH_B_RSEREM_IGOFF,           (U1)ALERT_B_RSEREM_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_B_SMASTA_MTRX[0],        (U2)ALERT_CH_B_SMASTA_BCDR,            (U1)ALERT_B_SMASTA_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_B_SPAT_MTRX[0],          (U2)ALERT_CH_B_SPAT,                   (U1)ALERT_B_SPAT_CH_NUM,            (U1)1U  },
    {  &st_gp_ALERT_B_TBEAM12_MTRX[0],       (U2)ALERT_CH_B_TBEAM12,                (U1)ALERT_B_TBEAM12_CH_NUM,         (U1)1U  },
    {  &st_gp_ALERT_B_TDOOR_MTRX[0],         (U2)ALERT_CH_B_TDOOR,                  (U1)ALERT_B_TDOOR_CH_NUM,           (U1)1U  },
    {  &st_gp_ALERT_B_TPWSR_MTRX[0],         (U2)ALERT_CH_B_TPWSR,                  (U1)ALERT_B_TPWSR_CH_NUM,           (U1)1U  },
    {  &st_gp_ALERT_B_TRWIP_MTRX[0],         (U2)ALERT_CH_B_TRWIP,                  (U1)ALERT_B_TRWIP_CH_NUM,           (U1)1U  },
    {  &st_gp_ALERT_C_AVSWAR_MTRX[0],        (U2)ALERT_CH_C_AVSWAR,                 (U1)ALERT_C_AVSWAR_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_C_BRKBZ_MTRX[0],         (U2)ALERT_CH_C_BRKBZ,                  (U1)ALERT_C_BRKBZ_CH_NUM,           (U1)1U  },
    {  &st_gp_ALERT_C_BRK_2_MTRX[0],         (U2)ALERT_CH_C_BRK_2,                  (U1)ALERT_C_BRK_2_CH_NUM,           (U1)1U  },
    {  &st_gp_ALERT_C_BRLV_2_MTRX[0],        (U2)ALERT_CH_C_BRLV_2_WRN,             (U1)ALERT_C_BRLV_2_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_C_ECB_MTRX[0],           (U2)ALERT_CH_C_ECB,                    (U1)ALERT_C_ECB_CH_NUM,             (U1)1U  },
    {  &st_gp_ALERT_H_MAICER_MTRX[0],        (U2)ALERT_CH_H_MAICER_PD1,             (U1)ALERT_H_MAICER_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_H_PEXI_MTRX[0],          (U2)ALERT_CH_H_PEXI,                   (U1)ALERT_H_PEXI_CH_NUM,            (U1)1U  },
    {  &st_gp_ALERT_O_EIGCON_MTRX[0],        (U2)ALERT_CH_O_EIGCON,                 (U1)ALERT_O_EIGCON_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_S_ADBZR_DMC_MTRX[0],     (U2)ALERT_CH_S_ADBZR_DMC,              (U1)ALERT_S_ADBZR_DMC_CH_NUM,       (U1)1U  },
    {  &st_gp_ALERT_S_ADBZR_FRRADA_MTRX[0],  (U2)ALERT_CH_S_ADBZR_FRRADA_CMP,       (U1)ALERT_S_ADBZR_FRRADA_CH_NUM,    (U1)1U  },
    {  &st_gp_ALERT_S_ADBZR_TCHAR_MTRX[0],   (U2)ALERT_CH_S_ADBZR_TCHAR,            (U1)ALERT_S_ADBZR_TCHAR_CH_NUM,     (U1)1U  },
    {  &st_gp_ALERT_S_ADBZR_CSR_MTRX[0],     (U2)ALERT_CH_S_ADBZR_CSR_BZ,           (U1)ALERT_S_ADBZR_CSR_CH_NUM,       (U1)1U  },
    {  &st_gp_ALERT_S_ADBZR_PMAR_MTRX[0],    (U2)ALERT_CH_S_ADBZR_PMAR,             (U1)ALERT_S_ADBZR_PMAR_CH_NUM,      (U1)1U  },
    {  &st_gp_ALERT_S_ADBZR_SEA_MTRX[0],     (U2)ALERT_CH_S_ADBZR_SEA,              (U1)ALERT_S_ADBZR_SEA_CH_NUM,       (U1)1U  },
    {  &st_gp_ALERT_H_DCLDSP_MTRX[0],        (U2)ALERT_CH_H_DCLDSP,                 (U1)ALERT_H_DCLDSP_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_C_BRPADW_MTRX[0],        (U2)ALERT_CH_C_BRPADW,                 (U1)ALERT_C_BRPADW_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_B_TURHAZ_MTRX[0],        (U2)ALERT_CH_B_TURHAZ_L,               (U1)ALERT_B_TURHAZ_CH_NUM,          (U1)1U  },
    {  &st_gp_ALERT_S_ADBZR_TCW_MTRX[0],     (U2)ALERT_CH_S_ADBZR_TCW,              (U1)ALERT_S_ADBZR_TCW_CH_NUM,       (U1)1U  },
    {  &st_gp_ALERT_C_STEER_MTRX[0],         (U2)ALERT_CH_C_STEER_TT,               (U1)ALERT_C_STEER_CH_NUM,           (U1)2U  },
    {  &st_gp_ALERT_H_ACCHOL_MTRX[0],        (U2)ALERT_CH_H_ACCHOL,                 (U1)ALERT_H_ACCHOL_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_BATINS_MTRX[0],        (U2)ALERT_CH_H_BATINS_BC,              (U1)ALERT_H_BATINS_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_DRIPOW_MTRX[0],        (U2)ALERT_CH_H_DRIPOW,                 (U1)ALERT_H_DRIPOW_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_ONACCN_MTRX[0],        (U2)ALERT_CH_H_ONACCN,                 (U1)ALERT_H_ONACCN_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_REASYS_MTRX[0],        (U2)ALERT_CH_H_REASYS_TT,              (U1)ALERT_H_REASYS_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_REGBRA_MTRX[0],        (U2)ALERT_CH_H_REGBRA,                 (U1)ALERT_H_REGBRA_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_SYSMAL_MTRX[0],        (U2)ALERT_CH_H_SYSMAL_BC,              (U1)ALERT_H_SYSMAL_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_TOWWAR_MTRX[0],        (U2)ALERT_CH_H_TOWWAR,                 (U1)ALERT_H_TOWWAR_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_B_BDOOR_MTRX[0],         (U2)ALERT_CH_B_BDOOR,                  (U1)ALERT_B_BDOOR_CH_NUM,           (U1)2U  },
    {  &st_gp_ALERT_B_LEDHEA_MTRX[0],        (U2)ALERT_CH_B_LEDHEA,                 (U1)ALERT_B_LEDHEA_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_B_MLGT_MTRX[0],          (U2)ALERT_CH_B_MLGT,                   (U1)ALERT_B_MLGT_CH_NUM,            (U1)2U  },
    {  &st_gp_ALERT_B_RSEREM_MTRX[0],        (U2)ALERT_CH_B_RSEREM_IGOFF,           (U1)ALERT_B_RSEREM_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_B_SMASTA_MTRX[0],        (U2)ALERT_CH_B_SMASTA_BCDR,            (U1)ALERT_B_SMASTA_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_B_TBEAM12_MTRX[0],       (U2)ALERT_CH_B_TBEAM12,                (U1)ALERT_B_TBEAM12_CH_NUM,         (U1)2U  },
    {  &st_gp_ALERT_B_TDOOR_MTRX[0],         (U2)ALERT_CH_B_TDOOR,                  (U1)ALERT_B_TDOOR_CH_NUM,           (U1)2U  },
    {  &st_gp_ALERT_B_TPWSR_MTRX[0],         (U2)ALERT_CH_B_TPWSR,                  (U1)ALERT_B_TPWSR_CH_NUM,           (U1)2U  },
    {  &st_gp_ALERT_B_TRWIP_MTRX[0],         (U2)ALERT_CH_B_TRWIP,                  (U1)ALERT_B_TRWIP_CH_NUM,           (U1)2U  },
    {  &st_gp_ALERT_C_BRKBZ_MTRX[0],         (U2)ALERT_CH_C_BRKBZ,                  (U1)ALERT_C_BRKBZ_CH_NUM,           (U1)2U  },
    {  &st_gp_ALERT_C_BRK_2_MTRX[0],         (U2)ALERT_CH_C_BRK_2,                  (U1)ALERT_C_BRK_2_CH_NUM,           (U1)2U  },
    {  &st_gp_ALERT_C_BRLV_2_MTRX[0],        (U2)ALERT_CH_C_BRLV_2_WRN,             (U1)ALERT_C_BRLV_2_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_C_ECB_MTRX[0],           (U2)ALERT_CH_C_ECB,                    (U1)ALERT_C_ECB_CH_NUM,             (U1)2U  },
    {  &st_gp_ALERT_H_MAICER_MTRX[0],        (U2)ALERT_CH_H_MAICER_PD1,             (U1)ALERT_H_MAICER_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_H_PEXI_MTRX[0],          (U2)ALERT_CH_H_PEXI,                   (U1)ALERT_H_PEXI_CH_NUM,            (U1)2U  },
    {  &st_gp_ALERT_O_EIGCON_MTRX[0],        (U2)ALERT_CH_O_EIGCON,                 (U1)ALERT_O_EIGCON_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_S_ADBZR_CSR_MTRX[0],     (U2)ALERT_CH_S_ADBZR_CSR_BZ,           (U1)ALERT_S_ADBZR_CSR_CH_NUM,       (U1)2U  },
    {  &st_gp_ALERT_S_ADBZR_PMAR_MTRX[0],    (U2)ALERT_CH_S_ADBZR_PMAR,             (U1)ALERT_S_ADBZR_PMAR_CH_NUM,      (U1)2U  },
    {  &st_gp_ALERT_S_ADBZR_SEA_MTRX[0],     (U2)ALERT_CH_S_ADBZR_SEA,              (U1)ALERT_S_ADBZR_SEA_CH_NUM,       (U1)2U  },
    {  &st_gp_ALERT_C_BRPADW_MTRX[0],        (U2)ALERT_CH_C_BRPADW,                 (U1)ALERT_C_BRPADW_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_B_TURHAZ_MTRX[0],        (U2)ALERT_CH_B_TURHAZ_L,               (U1)ALERT_B_TURHAZ_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_O_FNCLIM_MTRX[0],        (U2)ALERT_CH_O_FNCLIM,                 (U1)ALERT_O_FNCLIM_CH_NUM,          (U1)2U  },
    {  &st_gp_ALERT_B_GRISHU_MTRX[0],        (U2)ALERT_CH_B_GRISHU,                 (U1)ALERT_B_GRISHU_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_D_SBW_MTRX[0],           (U2)ALERT_CH_D_SBW_BZ_BSFT,            (U1)ALERT_D_SBW_CH_NUM,             (U1)3U  },
    {  &st_gp_ALERT_H_LEAUNF_MTRX[0],        (U2)ALERT_CH_H_LEAUNF,                 (U1)ALERT_H_LEAUNF_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_M_BGLFSPD_MTRX[0],       (U2)ALERT_CH_M_BGLFSPD,                (U1)ALERT_M_BGLFSPD_CH_NUM,         (U1)3U  },
    {  &st_gp_ALERT_M_T120_MTRX[0],          (U2)ALERT_CH_M_T120,                   (U1)ALERT_M_T120_CH_NUM,            (U1)3U  },
    {  &st_gp_ALERT_O_CHAMAL_MTRX[0],        (U2)ALERT_CH_O_CHAMAL,                 (U1)ALERT_O_CHAMAL_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_B_BDOOR_MTRX[0],         (U2)ALERT_CH_B_BDOOR,                  (U1)ALERT_B_BDOOR_CH_NUM,           (U1)3U  },
    {  &st_gp_ALERT_B_LEDHEA_MTRX[0],        (U2)ALERT_CH_B_LEDHEA,                 (U1)ALERT_B_LEDHEA_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_B_MLGT_MTRX[0],          (U2)ALERT_CH_B_MLGT,                   (U1)ALERT_B_MLGT_CH_NUM,            (U1)3U  },
    {  &st_gp_ALERT_B_RSEREM_MTRX[0],        (U2)ALERT_CH_B_RSEREM_IGOFF,           (U1)ALERT_B_RSEREM_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_B_SMASTA_MTRX[0],        (U2)ALERT_CH_B_SMASTA_BCDR,            (U1)ALERT_B_SMASTA_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_B_TBEAM12_MTRX[0],       (U2)ALERT_CH_B_TBEAM12,                (U1)ALERT_B_TBEAM12_CH_NUM,         (U1)3U  },
    {  &st_gp_ALERT_B_TDOOR_MTRX[0],         (U2)ALERT_CH_B_TDOOR,                  (U1)ALERT_B_TDOOR_CH_NUM,           (U1)3U  },
    {  &st_gp_ALERT_B_TPWSR_MTRX[0],         (U2)ALERT_CH_B_TPWSR,                  (U1)ALERT_B_TPWSR_CH_NUM,           (U1)3U  },
    {  &st_gp_ALERT_B_TRWIP_MTRX[0],         (U2)ALERT_CH_B_TRWIP,                  (U1)ALERT_B_TRWIP_CH_NUM,           (U1)3U  },
    {  &st_gp_ALERT_C_BRKBZ_MTRX[0],         (U2)ALERT_CH_C_BRKBZ,                  (U1)ALERT_C_BRKBZ_CH_NUM,           (U1)3U  },
    {  &st_gp_ALERT_C_BRK_2_MTRX[0],         (U2)ALERT_CH_C_BRK_2,                  (U1)ALERT_C_BRK_2_CH_NUM,           (U1)3U  },
    {  &st_gp_ALERT_C_BRLV_2_MTRX[0],        (U2)ALERT_CH_C_BRLV_2_WRN,             (U1)ALERT_C_BRLV_2_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_C_ECB_MTRX[0],           (U2)ALERT_CH_C_ECB,                    (U1)ALERT_C_ECB_CH_NUM,             (U1)3U  },
    {  &st_gp_ALERT_H_MAICER_MTRX[0],        (U2)ALERT_CH_H_MAICER_PD1,             (U1)ALERT_H_MAICER_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_H_PEXI_MTRX[0],          (U2)ALERT_CH_H_PEXI,                   (U1)ALERT_H_PEXI_CH_NUM,            (U1)3U  },
    {  &st_gp_ALERT_O_EIGCON_MTRX[0],        (U2)ALERT_CH_O_EIGCON,                 (U1)ALERT_O_EIGCON_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_S_ADBZR_CSR_MTRX[0],     (U2)ALERT_CH_S_ADBZR_CSR_BZ,           (U1)ALERT_S_ADBZR_CSR_CH_NUM,       (U1)3U  },
    {  &st_gp_ALERT_S_ADBZR_PMAR_MTRX[0],    (U2)ALERT_CH_S_ADBZR_PMAR,             (U1)ALERT_S_ADBZR_PMAR_CH_NUM,      (U1)3U  },
    {  &st_gp_ALERT_S_ADBZR_SEA_MTRX[0],     (U2)ALERT_CH_S_ADBZR_SEA,              (U1)ALERT_S_ADBZR_SEA_CH_NUM,       (U1)3U  },
    {  &st_gp_ALERT_D_SFTPOS_MTRX[0],        (U2)ALERT_CH_D_SFTPOS_B_RJTB,          (U1)ALERT_D_SFTPOS_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_M_MINDSPWR_MTRX[0],      (U2)ALERT_CH_M_MINDSPWR,               (U1)ALERT_M_MINDSPWR_CH_NUM,        (U1)3U  },
    {  &st_gp_ALERT_B_ESWUOC_MTRX[0],        (U2)ALERT_CH_B_ESWUOC_BCB,             (U1)ALERT_B_ESWUOC_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_C_BRPADW_MTRX[0],        (U2)ALERT_CH_C_BRPADW,                 (U1)ALERT_C_BRPADW_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_B_TURHAZ_MTRX[0],        (U2)ALERT_CH_B_TURHAZ_L,               (U1)ALERT_B_TURHAZ_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_M_SECMSG_MTRX[0],        (U2)ALERT_CH_M_SECMSG,                 (U1)ALERT_M_SECMSG_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_B_SECBDC_MTRX[0],        (U2)ALERT_CH_B_SECBDC,                 (U1)ALERT_B_SECBDC_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_D_SECDDC_MTRX[0],        (U2)ALERT_CH_D_SECDDC,                 (U1)ALERT_D_SECDDC_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_S_SECADC_MTRX[0],        (U2)ALERT_CH_S_SECADC,                 (U1)ALERT_S_SECADC_CH_NUM,          (U1)3U  },
    {  &st_gp_ALERT_S_ADBZR_ACC_MTRX[0],     (U2)ALERT_CH_S_ADBZR_ACC,              (U1)ALERT_S_ADBZR_ACC_CH_NUM,       (U1)4U  },
    {  &st_gp_ALERT_S_ADBZR_APP_MTRX[0],     (U2)ALERT_CH_S_ADBZR_APP,              (U1)ALERT_S_ADBZR_APP_CH_NUM,       (U1)4U  },
    {  &st_gp_ALERT_S_ADBZR_BSM_MTRX[0],     (U2)ALERT_CH_S_ADBZR_BSM,              (U1)ALERT_S_ADBZR_BSM_CH_NUM,       (U1)4U  },
    {  &st_gp_ALERT_S_ADBZR_FCTA_MTRX[0],    (U2)ALERT_CH_S_ADBZR_FCTA,             (U1)ALERT_S_ADBZR_FCTA_CH_NUM,      (U1)4U  },
    {  &st_gp_ALERT_S_ADBZR_LDA_MTRX[0],     (U2)ALERT_CH_S_ADBZR_LDA_LDW,          (U1)ALERT_S_ADBZR_LDA_CH_NUM,       (U1)4U  },
    {  &st_gp_ALERT_S_ADBZR_LTA_MTRX[0],     (U2)ALERT_CH_S_ADBZR_LTA_LKA,          (U1)ALERT_S_ADBZR_LTA_CH_NUM,       (U1)4U  },
    {  &st_gp_ALERT_S_ADBZR_PCS_MTRX[0],     (U2)ALERT_CH_S_ADBZR_PCS,              (U1)ALERT_S_ADBZR_PCS_CH_NUM,       (U1)4U  },
    {  &st_gp_ALERT_S_ADBZR_RSA_MTRX[0],     (U2)ALERT_CH_S_ADBZR_RSA_SGN,          (U1)ALERT_S_ADBZR_RSA_CH_NUM,       (U1)4U  },
    {  &st_gp_ALERT_S_ADBZR_SWS_MTRX[0],     (U2)ALERT_CH_S_ADBZR_SWS,              (U1)ALERT_S_ADBZR_SWS_CH_NUM,       (U1)4U  },
    {  &st_gp_ALERT_S_ADBZR_TMN_MTRX[0],     (U2)ALERT_CH_S_ADBZR_TMN,              (U1)ALERT_S_ADBZR_TMN_CH_NUM,       (U1)4U  },
    {  &st_gp_ALERT_S_ADBZR_DA_MTRX[0],      (U2)ALERT_CH_S_ADBZR_DA,               (U1)ALERT_S_ADBZR_DA_CH_NUM,        (U1)4U  },
    {  &st_gp_ALERT_S_TMTT_MTRX[0],          (U2)ALERT_CH_S_TMTT,                   (U1)ALERT_S_TMTT_CH_NUM,            (U1)4U  },
    {  &st_gp_ALERT_S_TMBZR_MTRX[0],         (U2)ALERT_CH_S_TMBZR_BC_AD,            (U1)ALERT_S_TMBZR_CH_NUM,           (U1)4U  },
    {  &st_gp_ALERT_B_BDOOR_MTRX[0],         (U2)ALERT_CH_B_BDOOR,                  (U1)ALERT_B_BDOOR_CH_NUM,           (U1)4U  },
    {  &st_gp_ALERT_B_LEDHEA_MTRX[0],        (U2)ALERT_CH_B_LEDHEA,                 (U1)ALERT_B_LEDHEA_CH_NUM,          (U1)4U  },
    {  &st_gp_ALERT_B_MLGT_MTRX[0],          (U2)ALERT_CH_B_MLGT,                   (U1)ALERT_B_MLGT_CH_NUM,            (U1)4U  },
    {  &st_gp_ALERT_B_RSEREM_MTRX[0],        (U2)ALERT_CH_B_RSEREM_IGOFF,           (U1)ALERT_B_RSEREM_CH_NUM,          (U1)4U  },
    {  &st_gp_ALERT_B_SMASTA_MTRX[0],        (U2)ALERT_CH_B_SMASTA_BCDR,            (U1)ALERT_B_SMASTA_CH_NUM,          (U1)4U  },
    {  &st_gp_ALERT_B_TBEAM12_MTRX[0],       (U2)ALERT_CH_B_TBEAM12,                (U1)ALERT_B_TBEAM12_CH_NUM,         (U1)4U  },
    {  &st_gp_ALERT_B_TDOOR_MTRX[0],         (U2)ALERT_CH_B_TDOOR,                  (U1)ALERT_B_TDOOR_CH_NUM,           (U1)4U  },
    {  &st_gp_ALERT_B_TPWSR_MTRX[0],         (U2)ALERT_CH_B_TPWSR,                  (U1)ALERT_B_TPWSR_CH_NUM,           (U1)4U  },
    {  &st_gp_ALERT_B_TRWIP_MTRX[0],         (U2)ALERT_CH_B_TRWIP,                  (U1)ALERT_B_TRWIP_CH_NUM,           (U1)4U  },
    {  &st_gp_ALERT_C_BRKBZ_MTRX[0],         (U2)ALERT_CH_C_BRKBZ,                  (U1)ALERT_C_BRKBZ_CH_NUM,           (U1)4U  },
    {  &st_gp_ALERT_C_BRK_2_MTRX[0],         (U2)ALERT_CH_C_BRK_2,                  (U1)ALERT_C_BRK_2_CH_NUM,           (U1)4U  },
    {  &st_gp_ALERT_C_BRLV_2_MTRX[0],        (U2)ALERT_CH_C_BRLV_2_WRN,             (U1)ALERT_C_BRLV_2_CH_NUM,          (U1)4U  },
    {  &st_gp_ALERT_C_ECB_MTRX[0],           (U2)ALERT_CH_C_ECB,                    (U1)ALERT_C_ECB_CH_NUM,             (U1)4U  },
    {  &st_gp_ALERT_H_MAICER_MTRX[0],        (U2)ALERT_CH_H_MAICER_PD1,             (U1)ALERT_H_MAICER_CH_NUM,          (U1)4U  },
    {  &st_gp_ALERT_H_PEXI_MTRX[0],          (U2)ALERT_CH_H_PEXI,                   (U1)ALERT_H_PEXI_CH_NUM,            (U1)4U  },
    {  &st_gp_ALERT_O_EIGCON_MTRX[0],        (U2)ALERT_CH_O_EIGCON,                 (U1)ALERT_O_EIGCON_CH_NUM,          (U1)4U  },
    {  &st_gp_ALERT_S_ADBZR_CSR_MTRX[0],     (U2)ALERT_CH_S_ADBZR_CSR_BZ,           (U1)ALERT_S_ADBZR_CSR_CH_NUM,       (U1)4U  },
    {  &st_gp_ALERT_S_ADBZR_PMAR_MTRX[0],    (U2)ALERT_CH_S_ADBZR_PMAR,             (U1)ALERT_S_ADBZR_PMAR_CH_NUM,      (U1)4U  },
    {  &st_gp_ALERT_S_ADBZR_SEA_MTRX[0],     (U2)ALERT_CH_S_ADBZR_SEA,              (U1)ALERT_S_ADBZR_SEA_CH_NUM,       (U1)4U  },
    {  &st_gp_ALERT_C_BRPADW_MTRX[0],        (U2)ALERT_CH_C_BRPADW,                 (U1)ALERT_C_BRPADW_CH_NUM,          (U1)4U  },
    {  &st_gp_ALERT_B_TURHAZ_MTRX[0],        (U2)ALERT_CH_B_TURHAZ_L,               (U1)ALERT_B_TURHAZ_CH_NUM,          (U1)4U  }
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
    static void    (* const fp_vd_ALERT_MTRX_INIT[])(void) = {
        &vd_g_AlertB_blgtInit,
        &vd_g_AlertB_bvoopeInit,
        &vd_g_AlertB_pbdInit,
        &vd_g_AlertB_theadInit,
        &vd_g_AlertB_trfogInit,
        &vd_g_AlertB_ttailInit,
        &vd_g_AlertB_waslevInit,
        &vd_g_AlertB_bdoorInit,
        &vd_g_AlertB_mlgtInit,
        &vd_g_AlertB_rseremInit,
        &vd_g_AlertB_smastaInit,
        &vd_g_AlertB_tbeam12Init,
        &vd_g_AlertB_tdoorInit,
        &vd_g_AlertB_tpwsrInit,
        &vd_g_AlertC_brlv_2Init,
        &vd_g_AlertC_epbInit,
        &vd_g_AlertC_steerInit,
        &vd_g_AlertD_sbwInit,
        &vd_g_AlertM_bglfspdInit,
        &vd_g_AlertB_fmseatInit,
        &vd_g_AlertB_pbdksInit,
        &vd_g_AlertB_tffogInit,
        &vd_g_AlertB_thesenInit,
        &vd_g_AlertM_mindspwrInit,
        &vd_g_AlertB_eswuocInit,
        &vd_g_AlertH_tvpsofInit,
        &vd_g_AlertB_aloa2Init,
        &vd_g_AlertC_hcsInit,
        &vd_g_AlertH_battrwInit,
        &vd_g_AlertO_pdsmalInit,
        &vd_g_AlertB_turhazInit,
        &vd_g_AlertO_fnclimInit,
        &vd_g_AlertB_secbdcInit
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
/*  5.2.0    06/25/2025  KO       Change for BEV System_Consideration_2                                                              */
/*  5.3.0    11/27/2025  PG       Change for BEV System_Consideration_ADAS                                                           */
/*  5.4.0    01/07/2026  SN       Change for BEV FF2                                                                                 */
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
/*  BEV-10    6/17/2025  JS       Change for BEV System_Consideration_2.(MET-C_BRKBZ-CSTD-2-00-B-C0)                                 */
/*  BEV-11    6/20/2025  KO       Change for BEV System_Consideration_2.(MET-O_PDSMAL-CSTD-0-00-A-C0)                                */
/*  BEV-12    6/23/2025  HY       Change for BEV System_Consideration_2.(MET-S_ADMID-CSTD-0-02-A-C0 / MET-S_ADTT-CSTD-0-02-A-C0)     */
/*  BEV-13    7/07/2025  KT       Delete for BEV System_Consideration_2.(MET-B_PCL-CSTD-A0-02-B-C0 etc.)                             */
/*  BEV-14   11/27/2025  PG       Change for BEV System_Consideration_ADAS. (MET-S_TMTT-CSTD-0-01-A-C0)                              */
/*  BEV-15   11/28/2025  HL       Change for BEV System_Consideration_ADAS.(MET-S_TMBZR-CSTD-0-01-A-C0)                              */
/*  BEV-16   12/04/2025  SH       Change for BEV System_Consideration_ADAS.(MET-B_TURHAZ-CSTD-1-01-A-C1)                             */
/*  BEV-17   12/05/2025  KH       Change for BEV System_Consideration_ADAS.(MET-C_STEER-CSTD-0-02-B-C0)                              */
/*  BEV-18   12/10/2025  EA       Change for BEV System_Consideration_ADAS EDSS.(MET-S_ADBZR-CSTD-0-06-A-C0)                         */
/*  BEV-19   12/10/2025  DT       Change for BEV System_Consideration_ADAS TCW.(MET-S_ADBZR-CSTD-0-06-A-C0)                          */
/*  BEV-20   12/12/2025  ED       Change for BEV System_Consideration_ADAS SEA.(MET-S_ADBZR-CSTD-0-06-A-C0)                          */
/*  BEV-21   12/18/2025  ED       Change for BEV System_Consideration_ADAS ADBZR.(MET-S_ADBZR-CSTD-0-06-A-C0)                        */
/*  BEV-22   12/18/2025  KH       Update for BEV System_Consideration_ADAS. (B_PBDKS / C_TPMS / H_BATTRW / H_LEAUNF)                 */
/*  BEV-23    1/14/2025  JS       Change for BEV System_Consideration_FF2.(MET-H_PEXI-CSTD-1-00-A-C0)                                */
/*  BEV-24    1/16/2026  SN       Change for BEV FF2.(MET-O_FNCLIM-CSTD-0-00-A-C0)                                                   */
/*  BEV-25   01/16/2026  KM       Update for BEV FF2. (B_PERSET)                                                                     */
/*  BEV-26   01/23/2026  NI       Change for BEV Full_functioin2                                                                     */
/*                                MET-D_SFTPOS-CSTD-1-00-B-C0,MET-H_SYSMAL-CSTD-2-00-C-C0                                            */
/*                                Change Alert_REQ for SFTPOS AND Change Alert_CH for SYSMAL.                                        */
/*  BEV-27   02/10/2026  KO       Change for BEV FF2.(MET-M_SECMSG-CSTD-0-01-A-C0)                                                   */
/*  BEV-28   02/10/2026  SH       Change MCUID0209-0213 from Calibration to OMUSVIID                                                 */
/*  BEV-29   02/06/2026  HY       Change config for BEV Full_Function_2.                                                             */
/*                                MET-B_SECBDC-CSTD-0-00-A-C0                                                                        */
/*                                Changed due to specification change from feature to legacy.                                        */
/*  BEV-30   02/06/2026  YH       Change config for BEV Full_Function_2.                                                             */
/*                                MET-D_SECDDC-CSTD-0-00-A-C0                                                                        */
/*                                Changed due to specification change from feature to legacy.                                        */
/*  BEV-31   02/09/2026  YH       Change config for BEV Full_Function_2.                                                             */
/*                                MET-S_SECADC-CSTD-0-00-A-C0                                                                        */
/*                                Changed due to specification change from feature to legacy.                                        */
/*                                                                                                                                   */
/*  * YI   = Yoshiki Iwata, Denso                                                                                                    */
/*  * RS   = Ryuki Sako,      Denso Techno                                                                                           */
/*  * KO   = Kazuto Oishi,    Denso Techno                                                                                           */
/*  * HF   = Hinari Fukamachi,KSE                                                                                                    */
/*  * JS   = Jun Sugiyam,KSE                                                                                                         */
/*  * HY   = Haruki Yagi, KSE                                                                                                        */
/*  * KT   = Kenta Takaji,    Denso Techno                                                                                           */
/*  * PG   = Patrick Garcia,  DTPH                                                                                                   */
/*  * HL   = Harry Lapiceros,  DTPH                                                                                                  */
/*  * SH   = Sae Hirose,      Denso Techno                                                                                           */
/*  * KH   = Kiko Huerte,     DTPH                                                                                                   */
/*  * EA   = Eunice Avelin,   DTPH                                                                                                   */
/*  * DT   = Dj Tutanes,      DTPH                                                                                                   */
/*  * ED   = Emoh Dagasdas,   DTPH                                                                                                   */
/*  * SN   = Shizuka Nakajima,KSE                                                                                                    */
/*  * KM   = Kane Malapo,     DTPH                                                                                                   */
/*  * NI   = Naoki Inagaki,   KSE                                                                                                    */
/*  * YH   = Yuki Hatakeyama, KSE                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
