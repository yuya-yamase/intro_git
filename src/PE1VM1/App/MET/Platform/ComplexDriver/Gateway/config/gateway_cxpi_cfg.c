/* 1.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Toyota CXPI Gateway                                                                                                              */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GATEWAY_CXPI_CFG_C_MAJOR                      (1)
#define GATEWAY_CXPI_CFG_C_MINOR                      (0)
#define GATEWAY_CXPI_CFG_C_PATCH                      (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gateway_cxpi_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((GATEWAY_CXPI_CFG_C_MAJOR != GATEWAY_CXPI_CFG_H_MAJOR) || \
     (GATEWAY_CXPI_CFG_C_MINOR != GATEWAY_CXPI_CFG_H_MINOR) || \
     (GATEWAY_CXPI_CFG_C_PATCH != GATEWAY_CXPI_CFG_H_PATCH))
#error "Source and header files are inconsistent!"
#endif

#if ((GATEWAY_CXPI_CFG_C_MAJOR != GATEWAY_CXPI_CFG_PRIVATE_H_MAJOR) || \
     (GATEWAY_CXPI_CFG_C_MINOR != GATEWAY_CXPI_CFG_PRIVATE_H_MINOR) || \
     (GATEWAY_CXPI_CFG_C_PATCH != GATEWAY_CXPI_CFG_PRIVATE_H_PATCH))
#error "Source and parameter files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Compatibility Check                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_gwcxcfg_CxpJdg1;
static U1 u1_s_gwcxcfg_CxpJdg2;
static U1 u1_s_gwcxcfg_CxpUerr;
static U1 u1_s_gwcxcfg_CxpJdg3;
static U1 u1_s_gwcxcfg_CxpJdgT;
static U1 u1_s_gwcxcfg_CxpJdgW;
static U1 u1_s_gwcxcfg_CxpErr;
static U1 u1_s_gwcxcfg_CxpTerr;
static U1 u1_s_gwcxcfg_CxpWerr;

static U1 u1_s_gwcxcfg_Vfpext_last;
static U1 u1_s_gwcxcfg_gfpext_last;
static U1 u1_s_gwcxcfg_tmpabnl_last;
static U1 u1_s_gwcxcfg_mterr_last;
static U1 u1_s_gwcxcfg_tmpabnr_last;
static U1 u1_s_gwcxcfg_tmpmfix_last;
static U1 u1_s_gwcxcfg_grpfail0_last;
static U1 u1_s_gwcxcfg_grpfail1_last;
static U1 u1_s_gwcxcfg_cccount_last;
static U1 u1_s_gwcxcfg_stself_last;

static U1 u1_s_gwcxcfg_hed_s2_last;
static U1 u1_s_gwcxcfg_tal_s2_last;
static U1 u1_s_gwcxcfg_drl_s2_last;
static U1 u1_s_gwcxcfg_aut_s2_last;
static U1 u1_s_gwcxcfg_off_s2_last;
static U1 u1_s_gwcxcfg_ahb_s2_last;
static U1 u1_s_gwcxcfg_pas_s2_last;
static U1 u1_s_gwcxcfg_hib_s2_last;
static U1 u1_s_gwcxcfg_bw_s2_last;
static U1 u1_s_gwcxcfg_rfg_s2_last;
static U1 u1_s_gwcxcfg_fog_s2_last;

static U1 u1_s_gwcxcfg_wvr_s2_last;
static U1 u1_s_gwcxcfg_wsw_s2_last;
static U1 u1_s_gwcxcfg_wrsw_s2_last;
static U1 u1_s_gwcxcfg_wron_s2_last;
static U1 u1_s_gwcxcfg_wrin_s2_last;
static U1 u1_s_gwcxcfg_wint_s2_last;
static U1 u1_s_gwcxcfg_wmst_s2_last;
static U1 u1_s_gwcxcfg_wa_s2_last;
static U1 u1_s_gwcxcfg_whi_s2_last;
static U1 u1_s_gwcxcfg_wlo_s2_last;
static U1 u1_s_gwcxcfg_woff_s2_last;

static U1 u1_s_gwcxcfg_rheostat;

static U1 u1_s_gwcxcfg_vibtoffg;
static U1 u1_s_gwcxcfg_vibstrg;
static U1 u1_s_gwcxcfg_vibtong;

static U1 u1_s_gwcxcfg_ostgf;
static U1 u1_s_gwcxcfg_t_logi;
static U1 u1_s_gwcxcfg_el_sens;

static U1 u1_s_gwcxcfg_adim;
static U1 u1_s_gwcxcfg_hedh;
static U1 u1_s_gwcxcfg_hedl;
static U1 u1_s_gwcxcfg_tail_cxmet1s06;
static U1 u1_s_gwcxcfg_ffog;
static U1 u1_s_gwcxcfg_rfog;
static U1 u1_s_gwcxcfg_conlt_pr;
static U1 u1_s_gwcxcfg_bw_sw_pr;
static U1 u1_s_gwcxcfg_autint;

static U1 u1_s_gwcxcfg_pwsts;

static U1 u1_s_gwcxcfg_hed_s2_old;
static U1 u1_s_gwcxcfg_tal_s2_old;
static U1 u1_s_gwcxcfg_drl_s2_old;
static U1 u1_s_gwcxcfg_aut_s2_old;
static U1 u1_s_gwcxcfg_off_s2_old;
static U1 u1_s_gwcxcfg_ahb_s2_old;
static U1 u1_s_gwcxcfg_pas_s2_old;
static U1 u1_s_gwcxcfg_hib_s2_old;
static U1 u1_s_gwcxcfg_bw_s2_old;
static U1 u1_s_gwcxcfg_rfg_s2_old;
static U1 u1_s_gwcxcfg_fog_s2_old;
static U1 u1_s_gwcxcfg_crgl_s2_old;
static U1 u1_s_gwcxcfg_crgr_s2_old;
static U1 u1_s_gwcxcfg_trnl_s2_old;
static U1 u1_s_gwcxcfg_trnr_s2_old;
static U1 u1_s_gwcxcfg_cxp_terr_chgflg;

static U1 u1_s_gwcxcfg_wvr_s2_old;
static U1 u1_s_gwcxcfg_wsw_s2_old;
static U1 u1_s_gwcxcfg_wrsw_s2_old;
static U1 u1_s_gwcxcfg_wron_s2_old;
static U1 u1_s_gwcxcfg_wrin_s2_old;
static U1 u1_s_gwcxcfg_wint_s2_old;
static U1 u1_s_gwcxcfg_wmst_s2_old;
static U1 u1_s_gwcxcfg_wa_s2_old;
static U1 u1_s_gwcxcfg_whi_s2_old;
static U1 u1_s_gwcxcfg_wlo_s2_old;
static U1 u1_s_gwcxcfg_woff_s2_old;
static U1 u1_s_gwcxcfg_wamc_s2_old;
static U1 u1_s_gwcxcfg_moff_s2_old;
static U1 u1_s_gwcxcfg_mn_s2_old;
static U1 u1_s_gwcxcfg_mauto_s2_old;
static U1 u1_s_gwcxcfg_mwpdn_s2_old;
static U1 u1_s_gwcxcfg_mwpup_s2_old;
static U1 u1_s_gwcxcfg_mhi_s2_old;
static U1 u1_s_gwcxcfg_cxp_werr_chgflg;
static U1 u1_s_cxcmb1s05_cxpsts_old;
static U1 u1_s_cxcmb1s06_cxpsts_old;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void vd_s_GwcxCfg_Init_CxpiToCan(void);

static void vd_s_GwcxCfg_Init_AUD_MUTE(void);
static void vd_s_GwcxCfg_Init_VOL_LV(void);
static void vd_s_GwcxCfg_Init_CXP_JDG1(void);
static void vd_s_GwcxCfg_Init_CXP_JDG2(void);
static void vd_s_GwcxCfg_Init_VFPEXT(void);
static void vd_s_GwcxCfg_Init_MTERR(void);
static void vd_s_GwcxCfg_Init_GFPEXT(void);
static void vd_s_GwcxCfg_Init_GRPHLDL(void);
static void vd_s_GwcxCfg_Init_GRPHLDR(void);
static void vd_s_GwcxCfg_Init_TMPABNL(void);
static void vd_s_GwcxCfg_Init_TMPABNR(void);
static void vd_s_GwcxCfg_Init_TMPMFIX(void);
static void vd_s_GwcxCfg_Init_GRPFAIL0(void);
static void vd_s_GwcxCfg_Init_GRPFAIL1(void);
static void vd_s_GwcxCfg_Init_CXP_UERR(void);
static void vd_s_GwcxCfg_Init_CXP_JDG3(void);
static void vd_s_GwcxCfg_Init_CXP_ERR(void);
static void vd_s_GwcxCfg_Init_CCCOUNT(void);
static void vd_s_GwcxCfg_Init_ST_SEL_F(void);
static void vd_s_GwcxCfg_Init_MET1S45(void);
static void vd_s_GwcxCfg_Init_CXP_JDGT(void);
static void vd_s_GwcxCfg_Init_CXP_TERR(void);
static void vd_s_GwcxCfg_Init_LMTS_S2(void);
static void vd_s_GwcxCfg_Init_HED_S2(void);
static void vd_s_GwcxCfg_Init_TAL_S2(void);
static void vd_s_GwcxCfg_Init_DRL_S2(void);
static void vd_s_GwcxCfg_Init_AUT_S2(void);
static void vd_s_GwcxCfg_Init_OFF_S2(void);
static void vd_s_GwcxCfg_Init_AHB_S2(void);
static void vd_s_GwcxCfg_Init_PAS_S2(void);
static void vd_s_GwcxCfg_Init_HIB_S2(void);
static void vd_s_GwcxCfg_Init_BW_S2(void);
static void vd_s_GwcxCfg_Init_RFG_S2(void);
static void vd_s_GwcxCfg_Init_FOG_S2(void);
static void vd_s_GwcxCfg_Init_CRGL_S2(void);
static void vd_s_GwcxCfg_Init_CRGR_S2(void);
static void vd_s_GwcxCfg_Init_TRNL_S2(void);
static void vd_s_GwcxCfg_Init_TRNR_S2(void);
static void vd_s_GwcxCfg_Init_CMB1S05(void);
static void vd_s_GwcxCfg_Init_CXP_JDGW(void);
static void vd_s_GwcxCfg_Init_CXP_WERR(void);
static void vd_s_GwcxCfg_Init_LMWS_S2(void);
static void vd_s_GwcxCfg_Init_WVR_S2(void);
static void vd_s_GwcxCfg_Init_WSW_S2(void);
static void vd_s_GwcxCfg_Init_WRSW_S2(void);
static void vd_s_GwcxCfg_Init_WRON_S2(void);
static void vd_s_GwcxCfg_Init_WRIN_S2(void);
static void vd_s_GwcxCfg_Init_WINT_S2(void);
static void vd_s_GwcxCfg_Init_WMST_S2(void);
static void vd_s_GwcxCfg_Init_WA_S2(void);
static void vd_s_GwcxCfg_Init_WHI_S2(void);
static void vd_s_GwcxCfg_Init_WLO_S2(void);
static void vd_s_GwcxCfg_Init_WOFF_S2(void);
static void vd_s_GwcxCfg_Init_WAMC_S2(void);
static void vd_s_GwcxCfg_Init_WAI_S2(void);
static void vd_s_GwcxCfg_Init_MOFF_S2(void);
static void vd_s_GwcxCfg_Init_MN_S2(void);
static void vd_s_GwcxCfg_Init_MAUTO_S2(void);
static void vd_s_GwcxCfg_Init_MWPDN_S2(void);
static void vd_s_GwcxCfg_Init_MWPUP_S2(void);
static void vd_s_GwcxCfg_Init_MHI_S2(void);
static void vd_s_GwcxCfg_Init_CMB1S06(void);

static U1 u1_s_GwcxCfg_CXCMB1S05_Msgsts(void);
static U1 u1_s_GwcxCfg_CXCMB1S06_Msgsts(void);

static void vd_s_GwcxCfg_CXP_JDGT_Send(const U1  u1_a_PWRSTS);
static void vd_s_GwcxCfg_CXP_TERR_Send(const U1  u1_a_PWRSTS);
static void vd_s_GwcxCfg_CXP_JDGW_Send(const U1  u1_a_PWRSTS);
static void vd_s_GwcxCfg_CXP_WERR_Send(const U1  u1_a_PWRSTS);
static U1 u1_s_GwcxCfg_LMTS_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_HED_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_TAL_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_DRL_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_AUT_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_OFF_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_AHB_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_PAS_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_HIB_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_BW_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_RFG_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_FOG_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_LMWS_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_WVR_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_WSW_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_WRSW_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_WRON_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_WRIN_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_WINT_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_WMST_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_WA_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_WHI_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_WLO_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_WOFF_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_WAMC_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_WAI_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_MOFF_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_MN_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_MAUTO_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_MWPDN_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_MWPUP_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_MHI_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);

static void vd_s_GwcxCfgUpdCxpErr(void);
static void vd_s_GwcxCfgUpd_CXP_UERR(void);
static void vd_s_GwcxCfgUpd_CXP_ERR(void);
static void vd_s_GwcxCfgUpd_CXP_TERR(void);
static void vd_s_GwcxCfgUpd_CXP_WERR(void);

static void vd_s_GwcxCfg_Init_CanToCxpi(void);

static U1 u1_s_GwcxCfg_FCM1S28_Msgsts(void);
static U1 u1_s_GwcxCfg_ACN1S03_Msgsts(void);
static U1 u1_s_GwcxCfg_BDB1S01_Msgsts(void);
static U1 u1_s_GwcxCfg_BDB1S22_Msgsts(void);
static U1 u1_s_GwcxCfg_WIP1S01_Msgsts(void);

static void vd_s_GwcxCfg_Init_RHEOSTAT(void);
static void vd_s_GwcxCfg_Init_VIBTOFFG(void);
static void vd_s_GwcxCfg_Init_VIBSTRG(void);
static void vd_s_GwcxCfg_Init_VIBTONG(void);
static void vd_s_GwcxCfg_Init_O_STG_F(void);
static void vd_s_GwcxCfg_Init_T_LOGI(void);
static void vd_s_GwcxCfg_Init_EL_SENS(void);
static void vd_s_GwcxCfg_Init_ADIM(void);
static void vd_s_GwcxCfg_Init_HEDH(void);
static void vd_s_GwcxCfg_Init_HEDL(void);
static void vd_s_GwcxCfg_Init_TAIL06(void);
static void vd_s_GwcxCfg_Init_FFOG(void);
static void vd_s_GwcxCfg_Init_RFOG(void);
static void vd_s_GwcxCfg_Init_CONLT_PR(void);
static void vd_s_GwcxCfg_Init_BW_SW_PR(void);
static void vd_s_GwcxCfg_Init_AUTINT(void);

static void vd_s_GwcxCfg_CXMET1S01_SetData(const U1  u1_a_PWRSTS);

static U1 u1_s_GwcxCfg_RHEOSTAT_SetData(const U1  u1_a_PWRSTS);
static U1 u1_s_GwcxCfg_VIBTOFFG_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_VIBSTRG_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_VIBTONG_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_O_STG_F_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_T_LOGI_SetData(const U1  u1_a_PWRSTS);
static U1 u1_s_GwcxCfg_EL_SENS_SetData(const U1  u1_a_PWRSTS);
static U1 u1_s_GwcxCfg_ADIM_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_HEDH_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_HEDL_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_TAIL06_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_FFOG_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_RFOG_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_CONLT_PR_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_BW_SW_PR_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);
static U1 u1_s_GwcxCfg_AUTINT_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS);

static void vd_s_GwcxCfg_CXMET1S01_Send(void);
static void vd_s_GwcxCfg_CXMET1S03_Send(void);
static void vd_s_GwcxCfg_CXMET1S04_Send(void);
static void vd_s_GwcxCfg_CXMET1S05_Send(void);
static void vd_s_GwcxCfg_CXMET1S06_Send(void);

static void vd_s_GwcxCfg_RHEOSTAT_Send(void);
static void vd_s_GwcxCfg_VIBTOFFG_Send(void);
static void vd_s_GwcxCfg_VIBSTRG_Send(void);
static void vd_s_GwcxCfg_VIBTONG_Send(void);
static void vd_s_GwcxCfg_O_STG_F_Send(void);
static void vd_s_GwcxCfg_T_LOGI_Send(void);
static void vd_s_GwcxCfg_EL_SENS_Send(void);
static void vd_s_GwcxCfg_ADIM_Send(void);
static void vd_s_GwcxCfg_HEDH_Send(void);
static void vd_s_GwcxCfg_HEDL_Send(void);
static void vd_s_GwcxCfg_TAIL06_Send(void);
static void vd_s_GwcxCfg_FFOG_Send(void);
static void vd_s_GwcxCfg_RFOG_Send(void);
static void vd_s_GwcxCfg_CONLT_PR_Send(void);
static void vd_s_GwcxCfg_BW_SW_PR_Send(void);
static void vd_s_GwcxCfg_AUTINT_Send(void);

static U1 u1_s_GwcxCfg_CMB1S05_SetData(const U1  u1_a_PWRSTS);
static U1 u1_s_GwcxCfg_CMB1S06_SetData(const U1  u1_a_PWRSTS);
static U1 u1_s_GwcxCfg_MsgRcvFirst(const U1  u1_a_MSGSTS_OLD, const U1  u1_a_MSGSTS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1        u1_g_GWCX_ERRCHKTASK_NUM  = (U1)GATEWAY_CXPICFG_ERRCHKTASK_NUM;         /*  ErrorChkTask Number              */
const U1        u1_g_GWCX_WRTMSG_NUM      = (U1)GATEWAY_CXPICFG_WRTMSG_NUM;             /*  Gateway Write Message Number     */


const ST_GWCX_ERRCHK st_gp_GWCX_ERRCHKIF[GATEWAY_CXPICFG_ERRCHKTASK_NUM] = {
/*  fp_vd_errchk                                                      */
    {&vd_s_GwcxCfgUpdCxpErr}                      /*  Cxpi Err Check  */
};

const ST_GWCX_MSGCONF st_gp_GWCX_MSGIF[GATEWAY_CXPICFG_WRTMSG_NUM] = {
/*  fp_vd_send                                                        */
    {&vd_s_GwcxCfg_CXMET1S01_SetData}             /*  CXMET1S01       */
};

static const U1 u1_sp_GWCX_CONLT_PR_SENDMSG[GWCXCFG_CONLT_PR_MSGTBL_NUM] = {
    (U1)GWCXCFG_CONLT_PR_OFF,                     /* 0b:OFF           */
    (U1)GWCXCFG_CONLT_PR_ON                       /* 1b:ON            */
};

static const U1 u1_sp_GWCX_BW_SW_PR_SENDMSG[GWCXCFG_BW_SW_PR_MSGTBL_NUM] = {
    (U1)GWCXCFG_BW_SW_PR_OFF,                     /* 0b:OFF           */
    (U1)GWCXCFG_BW_SW_PR_ON                       /* 1b:ON            */
};

static const U1 u1_sp_GWCX_AUTINT_SENDMSG[GWCXCFG_AUTINT_MSGTBL_NUM] = {
    (U1)GWCXCFG_AUTINT_OFF,                       /* 0b:OFF           */
    (U1)GWCXCFG_AUTINT_ON                         /* 1b:ON            */
};

/*===================================================================================================================================*/
/*  Initialization processing                                                                                                        */
/*  Scope : Public                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
void vd_g_GatewayCxpiCfgInit(void)
{
    vd_s_GwcxCfg_Init_CanToCxpi();
    vd_s_GwcxCfg_Init_CxpiToCan();
}

/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CxpiToCan(void)
{
    /* Initialize MET1S41 */
    vd_s_GwcxCfg_Init_AUD_MUTE();
    vd_s_GwcxCfg_Init_VOL_LV();
    vd_s_GwcxCfg_Init_CXP_JDG1();

    /* Initialize MET1S43 */
    vd_s_GwcxCfg_Init_CXP_JDG2();
    vd_s_GwcxCfg_Init_VFPEXT();
    vd_s_GwcxCfg_Init_MTERR();
    vd_s_GwcxCfg_Init_GFPEXT();
    vd_s_GwcxCfg_Init_GRPHLDL();
    vd_s_GwcxCfg_Init_GRPHLDR();
    vd_s_GwcxCfg_Init_TMPABNL();
    vd_s_GwcxCfg_Init_TMPABNR();
    vd_s_GwcxCfg_Init_TMPMFIX();
    vd_s_GwcxCfg_Init_GRPFAIL0();
    vd_s_GwcxCfg_Init_GRPFAIL1();
    vd_s_GwcxCfg_Init_CXP_UERR();

    /* Initialize MET1S44 */
    vd_s_GwcxCfg_Init_CXP_JDG3();
    vd_s_GwcxCfg_Init_CXP_ERR();
    vd_s_GwcxCfg_Init_CCCOUNT();

    /* Initialize MET1S45 */
    vd_s_GwcxCfg_Init_ST_SEL_F();
    vd_s_GwcxCfg_Init_MET1S45();

    /* Initialize CMB1S05 */
    vd_s_GwcxCfg_Init_CXP_JDGT();
    vd_s_GwcxCfg_Init_CXP_TERR();
    vd_s_GwcxCfg_Init_LMTS_S2();
    vd_s_GwcxCfg_Init_HED_S2();
    vd_s_GwcxCfg_Init_TAL_S2();
    vd_s_GwcxCfg_Init_DRL_S2();
    vd_s_GwcxCfg_Init_AUT_S2();
    vd_s_GwcxCfg_Init_OFF_S2();
    vd_s_GwcxCfg_Init_AHB_S2();
    vd_s_GwcxCfg_Init_PAS_S2();
    vd_s_GwcxCfg_Init_HIB_S2();
    vd_s_GwcxCfg_Init_BW_S2();
    vd_s_GwcxCfg_Init_RFG_S2();
    vd_s_GwcxCfg_Init_FOG_S2();
    vd_s_GwcxCfg_Init_CRGL_S2();
    vd_s_GwcxCfg_Init_CRGR_S2();
    vd_s_GwcxCfg_Init_TRNL_S2();
    vd_s_GwcxCfg_Init_TRNR_S2();
    vd_s_GwcxCfg_Init_CMB1S05();
    
    /* Initialize CMB1S06 */
    vd_s_GwcxCfg_Init_CXP_JDGW();
    vd_s_GwcxCfg_Init_CXP_WERR();
    vd_s_GwcxCfg_Init_LMWS_S2();
    vd_s_GwcxCfg_Init_WVR_S2();
    vd_s_GwcxCfg_Init_WSW_S2();
    vd_s_GwcxCfg_Init_WRSW_S2();
    vd_s_GwcxCfg_Init_WRON_S2();
    vd_s_GwcxCfg_Init_WRIN_S2();
    vd_s_GwcxCfg_Init_WINT_S2();
    vd_s_GwcxCfg_Init_WMST_S2();
    vd_s_GwcxCfg_Init_WA_S2();
    vd_s_GwcxCfg_Init_WHI_S2();
    vd_s_GwcxCfg_Init_WLO_S2();
    vd_s_GwcxCfg_Init_WOFF_S2();
    vd_s_GwcxCfg_Init_WAMC_S2();
    vd_s_GwcxCfg_Init_WAI_S2();
    vd_s_GwcxCfg_Init_MOFF_S2();
    vd_s_GwcxCfg_Init_MN_S2();
    vd_s_GwcxCfg_Init_MAUTO_S2();
    vd_s_GwcxCfg_Init_MWPDN_S2();
    vd_s_GwcxCfg_Init_MWPUP_S2();
    vd_s_GwcxCfg_Init_MHI_S2();
    vd_s_GwcxCfg_Init_CMB1S06();
}

#if defined(ComConf_ComSignal_AUD_MUTE)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_AUD_MUTE(void)
{
    U1 u1_t_tx_AudMute;             /*  Signal AUD_MUTE            */

    u1_t_tx_AudMute = (U1)GWCXCFG_AUDMUTE_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_AUD_MUTE, (&u1_t_tx_AudMute));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_AUD_MUTE(void)
{
}
#endif

#if defined(ComConf_ComSignal_VOL_LV)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_VOL_LV(void)
{
    S1 s1_t_tx_VolLv;               /*  Signal VOL_LV              */

    s1_t_tx_VolLv = (S1)GWCXCFG_VOL_LV_DEF;

    (void)Com_SendSignal(ComConf_ComSignal_VOL_LV, (&s1_t_tx_VolLv));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_VOL_LV(void)
{
}
#endif

#if defined(ComConf_ComSignal_CXP_JDG1)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CXP_JDG1(void)
{
    u1_s_gwcxcfg_CxpJdg1 = (U1)GWCXCFG_CXPIJDG_UNDET;

    (void)Com_SendSignal(ComConf_ComSignal_CXP_JDG1, (&u1_s_gwcxcfg_CxpJdg1));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CXP_JDG1(void)
{
    u1_s_gwcxcfg_CxpJdg1 = (U1)GWCXCFG_CXPIJDG_UNDET;
}
#endif

#if defined(ComConf_ComSignal_CXP_JDG3)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CXP_JDG3(void)
{
    u1_s_gwcxcfg_CxpJdg3 = (U1)GWCXCFG_CXPIJDG_UNDET;
    
    (void)Com_SendSignal(ComConf_ComSignal_CXP_JDG3, (&u1_s_gwcxcfg_CxpJdg3));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CXP_JDG3(void)
{
    u1_s_gwcxcfg_CxpJdg3 = (U1)GWCXCFG_CXPIJDG_UNDET;
}
#endif

#if defined(ComConf_ComSignal_CXP_ERR)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CXP_ERR(void)
{
    u1_s_gwcxcfg_CxpErr = (U1)GATEWAY_CXPICFG_CXPICOM_NORM;
    
    (void)Com_SendSignal(ComConf_ComSignal_CXP_ERR, (&u1_s_gwcxcfg_CxpErr));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CXP_ERR(void)
{
    u1_s_gwcxcfg_CxpErr = (U1)GATEWAY_CXPICFG_CXPICOM_NORM;
}
#endif

#if defined(ComConf_ComSignal_CCCOUNT)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CCCOUNT(void)
{
    u1_s_gwcxcfg_cccount_last = (U1)0U;
    
    (void)Com_SendSignal(ComConf_ComSignal_CCCOUNT, (&u1_s_gwcxcfg_cccount_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CCCOUNT(void)
{
    u1_s_gwcxcfg_cccount_last = (U1)0U;
}
#endif

#if defined(ComConf_ComSignal_CXP_JDG2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CXP_JDG2(void)
{
    u1_s_gwcxcfg_CxpJdg2 = (U1)GWCXCFG_CXPIJDG_UNDET;

    (void)Com_SendSignal(ComConf_ComSignal_CXP_JDG2, (&u1_s_gwcxcfg_CxpJdg2));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CXP_JDG2(void)
{
    u1_s_gwcxcfg_CxpJdg2 = (U1)GWCXCFG_CXPIJDG_UNDET;
}
#endif

#if defined(ComConf_ComSignal_VFPEXT)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_VFPEXT(void)
{
    u1_s_gwcxcfg_Vfpext_last = (U1)GWCXCFG_STGSWSTAT_VIB_EXIST_UNDET;

    (void)Com_SendSignal(ComConf_ComSignal_VFPEXT, (&u1_s_gwcxcfg_Vfpext_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_VFPEXT(void)
{
    u1_s_gwcxcfg_Vfpext_last = (U1)GWCXCFG_STGSWSTAT_VIB_EXIST_UNDET;
}
#endif

#if defined(ComConf_ComSignal_MTERR)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_MTERR(void)
{
    u1_s_gwcxcfg_mterr_last = (U1)GWCXCFG_STGSWSTAT_MOT_NML;

    (void)Com_SendSignal(ComConf_ComSignal_MTERR, (&u1_s_gwcxcfg_mterr_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_MTERR(void)
{
    u1_s_gwcxcfg_mterr_last = (U1)GWCXCFG_STGSWSTAT_MOT_NML;
}
#endif

#if defined(ComConf_ComSignal_GFPEXT)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_GFPEXT(void)
{
    u1_s_gwcxcfg_gfpext_last = (U1)GWCXCFG_STGSWSTAT_GRP_EXIST_UNDET;

    (void)Com_SendSignal(ComConf_ComSignal_GFPEXT, (&u1_s_gwcxcfg_gfpext_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_GFPEXT(void)
{
    u1_s_gwcxcfg_gfpext_last = (U1)GWCXCFG_STGSWSTAT_GRP_EXIST_UNDET;
}
#endif

#if defined(ComConf_ComSignal_GRPHLDL)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_GRPHLDL(void)
{
    U1 u1_t_tx_Grphldl;             /*  Signal GRPHLDL             */

    u1_t_tx_Grphldl = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_GRPHLDL, (&u1_t_tx_Grphldl));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_GRPHLDL(void)
{
}
#endif

#if defined(ComConf_ComSignal_GRPHLDR)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_GRPHLDR(void)
{
    U1 u1_t_tx_Grphldr;             /*  Signal GRPHLDR             */

    u1_t_tx_Grphldr = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_GRPHLDR, (&u1_t_tx_Grphldr));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_GRPHLDR(void)
{
}
#endif

#if defined(ComConf_ComSignal_TMPABNL)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_TMPABNL(void)
{
    u1_s_gwcxcfg_tmpabnl_last = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_TMPABNL, (&u1_s_gwcxcfg_tmpabnl_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_TMPABNL(void)
{
    u1_s_gwcxcfg_tmpabnl_last = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_TMPABNR)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_TMPABNR(void)
{
    u1_s_gwcxcfg_tmpabnr_last = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_TMPABNR, (&u1_s_gwcxcfg_tmpabnr_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_TMPABNR(void)
{
    u1_s_gwcxcfg_tmpabnr_last = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_TMPMFIX)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_TMPMFIX(void)
{
    u1_s_gwcxcfg_tmpmfix_last = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_TMPMFIX, (&u1_s_gwcxcfg_tmpmfix_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_TMPMFIX(void)
{
    u1_s_gwcxcfg_tmpmfix_last = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_GRPFAIL0)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_GRPFAIL0(void)
{
    u1_s_gwcxcfg_grpfail0_last = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_GRPFAIL0, (&u1_s_gwcxcfg_grpfail0_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_GRPFAIL0(void)
{
    u1_s_gwcxcfg_grpfail0_last = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_GRPFAIL1)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_GRPFAIL1(void)
{
    u1_s_gwcxcfg_grpfail1_last = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_GRPFAIL1, (&u1_s_gwcxcfg_grpfail1_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_GRPFAIL1(void)
{
    u1_s_gwcxcfg_grpfail1_last = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_CXP_UERR)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CXP_UERR(void)
{
    u1_s_gwcxcfg_CxpUerr = (U1)GATEWAY_CXPICFG_CXPICOM_NORM;

    (void)Com_SendSignal(ComConf_ComSignal_CXP_UERR, (&u1_s_gwcxcfg_CxpUerr));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CXP_UERR(void)
{
    u1_s_gwcxcfg_CxpUerr = (U1)GATEWAY_CXPICFG_CXPICOM_NORM;
}
#endif

#if defined(ComConf_ComSignal_ST_SEL_F)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_ST_SEL_F(void)
{
    u1_s_gwcxcfg_stself_last = (U1)GWCXCFG_STGHTRPRES_UNDET;

    (void)Com_SendSignal(ComConf_ComSignal_ST_SEL_F, (&u1_s_gwcxcfg_stself_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_ST_SEL_F(void)
{
    u1_s_gwcxcfg_stself_last = (U1)GWCXCFG_STGHTRPRES_UNDET;
}
#endif

#if defined(ComConf_ComSignal_CXP_JDGT)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CXP_JDGT(void)
{
    u1_s_gwcxcfg_CxpJdgT = (U1)GWCXCFG_CXPIJDG_UNDET;

    (void)Com_SendSignal(ComConf_ComSignal_CXP_JDGT, (&u1_s_gwcxcfg_CxpJdgT));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CXP_JDGT(void)
{
    u1_s_gwcxcfg_CxpJdgT = (U1)GWCXCFG_CXPIJDG_UNDET;
}
#endif

#if defined(ComConf_ComSignal_CXP_TERR)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CXP_TERR(void)
{
    u1_s_gwcxcfg_CxpTerr = (U1)GATEWAY_CXPICFG_CXPICOM_NORM;
    u1_s_gwcxcfg_cxp_terr_chgflg = (U1)FALSE;

    (void)Com_SendSignal(ComConf_ComSignal_CXP_TERR, (&u1_s_gwcxcfg_CxpTerr));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CXP_TERR(void)
{
    u1_s_gwcxcfg_CxpTerr = (U1)GATEWAY_CXPICFG_CXPICOM_NORM;
    u1_s_gwcxcfg_cxp_terr_chgflg = (U1)FALSE;
}
#endif

#if defined(ComConf_ComSignal_CXP_JDGW)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CXP_JDGW(void)
{
    u1_s_gwcxcfg_CxpJdgW = (U1)GWCXCFG_CXPIJDG_UNDET;

    (void)Com_SendSignal(ComConf_ComSignal_CXP_JDGW, (&u1_s_gwcxcfg_CxpJdgW));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CXP_JDGW(void)
{
    u1_s_gwcxcfg_CxpJdgW = (U1)GWCXCFG_CXPIJDG_UNDET;
}
#endif

#if defined(ComConf_ComSignal_CXP_WERR)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CXP_WERR(void)
{
    u1_s_gwcxcfg_CxpWerr = (U1)GATEWAY_CXPICFG_CXPICOM_NORM;
    u1_s_gwcxcfg_cxp_werr_chgflg = (U1)FALSE;

    (void)Com_SendSignal(ComConf_ComSignal_CXP_WERR, (&u1_s_gwcxcfg_CxpWerr));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CXP_WERR(void)
{
    u1_s_gwcxcfg_CxpWerr = (U1)GATEWAY_CXPICFG_CXPICOM_NORM;
    u1_s_gwcxcfg_cxp_werr_chgflg = (U1)FALSE;
}
#endif

#if defined(ComConf_ComSignal_LMTS_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_LMTS_S2(void)
{
    U1 u1_t_tx_Lmts_s2;             /*  Signal LMTS_S2              */

    u1_t_tx_Lmts_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_LMTS_S2, (&u1_t_tx_Lmts_s2));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_LMTS_S2(void)
{
}
#endif

#if defined(ComConf_ComSignal_HED_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_HED_S2(void)
{
    u1_s_gwcxcfg_hed_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_hed_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_HED_S2, (&u1_s_gwcxcfg_hed_s2_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_HED_S2(void)
{
    u1_s_gwcxcfg_hed_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_hed_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_TAL_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_TAL_S2(void)
{
    u1_s_gwcxcfg_tal_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_tal_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_TAL_S2, (&u1_s_gwcxcfg_tal_s2_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_TAL_S2(void)
{
    u1_s_gwcxcfg_tal_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_tal_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_DRL_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_DRL_S2(void)
{
    u1_s_gwcxcfg_drl_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_drl_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_DRL_S2, (&u1_s_gwcxcfg_drl_s2_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_DRL_S2(void)
{
    u1_s_gwcxcfg_drl_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_drl_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_AUT_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_AUT_S2(void)
{
    u1_s_gwcxcfg_aut_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_aut_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_AUT_S2, (&u1_s_gwcxcfg_aut_s2_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_AUT_S2(void)
{
    u1_s_gwcxcfg_aut_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_aut_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_OFF_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_OFF_S2(void)
{
    u1_s_gwcxcfg_off_s2_last = (U1)GWCXCFG_STGSWSTAT_ON;
    u1_s_gwcxcfg_off_s2_old  = (U1)GWCXCFG_STGSWSTAT_ON;

    (void)Com_SendSignal(ComConf_ComSignal_OFF_S2, (&u1_s_gwcxcfg_off_s2_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_OFF_S2(void)
{
    u1_s_gwcxcfg_off_s2_last = (U1)GWCXCFG_STGSWSTAT_ON;
    u1_s_gwcxcfg_off_s2_old  = (U1)GWCXCFG_STGSWSTAT_ON;
}
#endif

#if defined(ComConf_ComSignal_AHB_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_AHB_S2(void)
{
    u1_s_gwcxcfg_ahb_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_ahb_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_AHB_S2, (&u1_s_gwcxcfg_ahb_s2_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_AHB_S2(void)
{
    u1_s_gwcxcfg_ahb_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_ahb_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_PAS_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_PAS_S2(void)
{
    u1_s_gwcxcfg_pas_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_pas_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_PAS_S2, (&u1_s_gwcxcfg_pas_s2_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_PAS_S2(void)
{
    u1_s_gwcxcfg_pas_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_pas_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_HIB_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_HIB_S2(void)
{
    u1_s_gwcxcfg_hib_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_hib_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_HIB_S2, (&u1_s_gwcxcfg_hib_s2_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_HIB_S2(void)
{
    u1_s_gwcxcfg_hib_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_hib_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_BW_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_BW_S2(void)
{
    u1_s_gwcxcfg_bw_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_bw_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_BW_S2, (&u1_s_gwcxcfg_bw_s2_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_BW_S2(void)
{
    u1_s_gwcxcfg_bw_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_bw_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_RFG_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_RFG_S2(void)
{
    u1_s_gwcxcfg_rfg_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_rfg_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_RFG_S2, (&u1_s_gwcxcfg_rfg_s2_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_RFG_S2(void)
{
    u1_s_gwcxcfg_rfg_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_rfg_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_FOG_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_FOG_S2(void)
{
    u1_s_gwcxcfg_fog_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_fog_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_FOG_S2, (&u1_s_gwcxcfg_fog_s2_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_FOG_S2(void)
{
    u1_s_gwcxcfg_fog_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_fog_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_CRGL_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CRGL_S2(void)
{
    U1 u1_t_tx_crgl_s2;             /*  Signal CRGL_S2             */

    u1_t_tx_crgl_s2          = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_crgl_s2_old = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_CRGL_S2, (&u1_t_tx_crgl_s2));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CRGL_S2(void)
{
    u1_s_gwcxcfg_crgl_s2_old = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_CRGR_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CRGR_S2(void)
{
    U1 u1_t_tx_crgr_s2;             /*  Signal CRGR_S2             */

    u1_t_tx_crgr_s2          = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_crgr_s2_old = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_CRGR_S2, (&u1_t_tx_crgr_s2));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CRGR_S2(void)
{
    u1_s_gwcxcfg_crgr_s2_old = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_TRNL_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_TRNL_S2(void)
{
    U1 u1_t_tx_trnl_s2;             /*  Signal TRNL_S2             */

    u1_t_tx_trnl_s2          = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_trnl_s2_old = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_TRNL_S2, (&u1_t_tx_trnl_s2));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_TRNL_S2(void)
{
    u1_s_gwcxcfg_trnl_s2_old = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_TRNR_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_TRNR_S2(void)
{
    U1 u1_t_tx_trnr_s2;             /*  Signal TRNR_S2             */

    u1_t_tx_trnr_s2          = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_trnr_s2_old = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_TRNR_S2, (&u1_t_tx_trnr_s2));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_TRNR_S2(void)
{
    u1_s_gwcxcfg_trnr_s2_old = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_LMWS_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_LMWS_S2(void)
{
    U1 u1_t_tx_Lmws_s2;             /*  Signal LMWS_S2              */

    u1_t_tx_Lmws_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_LMWS_S2, (&u1_t_tx_Lmws_s2));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_LMWS_S2(void)
{
}
#endif

#if defined(ComConf_ComSignal_WVR_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_WVR_S2(void)
{
    u1_s_gwcxcfg_wvr_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_wvr_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_WVR_S2, (&u1_s_gwcxcfg_wvr_s2_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_WVR_S2(void)
{
    u1_s_gwcxcfg_wvr_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_wvr_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_WSW_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_WSW_S2(void)
{
    u1_s_gwcxcfg_wsw_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_wsw_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_WSW_S2, (&u1_s_gwcxcfg_wsw_s2_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_WSW_S2(void)
{
    u1_s_gwcxcfg_wsw_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_wsw_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_WRSW_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_WRSW_S2(void)
{
    u1_s_gwcxcfg_wrsw_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_wrsw_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_WRSW_S2, (&u1_s_gwcxcfg_wrsw_s2_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_WRSW_S2(void)
{
    u1_s_gwcxcfg_wrsw_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_wrsw_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_WRON_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_WRON_S2(void)
{
    u1_s_gwcxcfg_wron_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_wron_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_WRON_S2, (&u1_s_gwcxcfg_wron_s2_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_WRON_S2(void)
{
    u1_s_gwcxcfg_wron_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_wron_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_WRIN_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_WRIN_S2(void)
{
    u1_s_gwcxcfg_wrin_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_wrin_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_WRIN_S2, (&u1_s_gwcxcfg_wrin_s2_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_WRIN_S2(void)
{
    u1_s_gwcxcfg_wrin_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_wrin_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_WINT_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_WINT_S2(void)
{
    u1_s_gwcxcfg_wint_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_wint_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_WINT_S2, (&u1_s_gwcxcfg_wint_s2_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_WINT_S2(void)
{
    u1_s_gwcxcfg_wint_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_wint_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_WMST_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_WMST_S2(void)
{
    u1_s_gwcxcfg_wmst_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_wmst_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_WMST_S2, (&u1_s_gwcxcfg_wmst_s2_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_WMST_S2(void)
{
    u1_s_gwcxcfg_wmst_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_wmst_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_WA_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_WA_S2(void)
{
    u1_s_gwcxcfg_wa_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_wa_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_WA_S2, (&u1_s_gwcxcfg_wa_s2_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_WA_S2(void)
{
    u1_s_gwcxcfg_wa_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_wa_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_WHI_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_WHI_S2(void)
{
    u1_s_gwcxcfg_whi_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_whi_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_WHI_S2, (&u1_s_gwcxcfg_whi_s2_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_WHI_S2(void)
{
    u1_s_gwcxcfg_whi_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_whi_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_WLO_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_WLO_S2(void)
{
    u1_s_gwcxcfg_wlo_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_wlo_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_WLO_S2, (&u1_s_gwcxcfg_wlo_s2_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_WLO_S2(void)
{
    u1_s_gwcxcfg_wlo_s2_last = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_wlo_s2_old  = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_WOFF_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_WOFF_S2(void)
{
    u1_s_gwcxcfg_woff_s2_last = (U1)GWCXCFG_STGSWSTAT_ON;
    u1_s_gwcxcfg_woff_s2_old  = (U1)GWCXCFG_STGSWSTAT_ON;

    (void)Com_SendSignal(ComConf_ComSignal_WOFF_S2, (&u1_s_gwcxcfg_woff_s2_last));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_WOFF_S2(void)
{
    u1_s_gwcxcfg_woff_s2_last = (U1)GWCXCFG_STGSWSTAT_ON;
    u1_s_gwcxcfg_woff_s2_old  = (U1)GWCXCFG_STGSWSTAT_ON;
}
#endif

#if defined(ComConf_ComSignal_WAMC_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_WAMC_S2(void)
{
    U1 u1_t_tx_Wamc_s2;             /*  Signal WAMC_S2              */

    u1_t_tx_Wamc_s2          = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_wamc_s2_old = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_WAMC_S2, (&u1_t_tx_Wamc_s2));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_WAMC_S2(void)
{
    u1_s_gwcxcfg_wamc_s2_old = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_WAI_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_WAI_S2(void)
{
    U1 u1_t_tx_Wai_s2;              /*  Signal WAI_S2               */

    u1_t_tx_Wai_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_WAI_S2, (&u1_t_tx_Wai_s2));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_WAI_S2(void)
{
}
#endif

#if defined(ComConf_ComSignal_MOFF_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_MOFF_S2(void)
{
    U1 u1_t_tx_Moff_s2;             /*  Signal MOFF_S2              */

    u1_t_tx_Moff_s2          = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_moff_s2_old = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_MOFF_S2, (&u1_t_tx_Moff_s2));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_MOFF_S2(void)
{
    u1_s_gwcxcfg_moff_s2_old = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_MN_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_MN_S2(void)
{
    U1 u1_t_tx_Mn_s2;               /*  Signal MN_S2                */

    u1_t_tx_Mn_s2          = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_mn_s2_old = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_MN_S2, (&u1_t_tx_Mn_s2));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_MN_S2(void)
{
    u1_s_gwcxcfg_mn_s2_old = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_MAUTO_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_MAUTO_S2(void)
{
    U1 u1_t_tx_Mauto_s2;            /*  Signal MAUTO_S2             */

    u1_t_tx_Mauto_s2          = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_mauto_s2_old = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_MAUTO_S2, (&u1_t_tx_Mauto_s2));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_MAUTO_S2(void)
{
    u1_s_gwcxcfg_mauto_s2_old = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_MWPDN_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_MWPDN_S2(void)
{
    U1 u1_t_tx_Mwpdn_s2;            /*  Signal MWPDN_S2             */

    u1_t_tx_Mwpdn_s2          = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_mwpdn_s2_old = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_MWPDN_S2, (&u1_t_tx_Mwpdn_s2));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_MWPDN_S2(void)
{
    u1_s_gwcxcfg_mwpdn_s2_old = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_MWPUP_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_MWPUP_S2(void)
{
    U1 u1_t_tx_Mwpup_s2;            /*  Signal MWPUP_S2             */

    u1_t_tx_Mwpup_s2          = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_mwpup_s2_old = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_MWPUP_S2, (&u1_t_tx_Mwpup_s2));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_MWPUP_S2(void)
{
    u1_s_gwcxcfg_mwpup_s2_old = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(ComConf_ComSignal_MHI_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_MHI_S2(void)
{
    U1 u1_t_tx_Mhi_s2;              /*  Signal MHI_S2               */

    u1_t_tx_Mhi_s2          = (U1)GWCXCFG_STGSWSTAT_OFF;
    u1_s_gwcxcfg_mhi_s2_old = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_MHI_S2, (&u1_t_tx_Mhi_s2));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_MHI_S2(void)
{
    u1_s_gwcxcfg_mhi_s2_old = (U1)GWCXCFG_STGSWSTAT_OFF;
}
#endif

#if defined(MSG_MET1S45_TXCH0)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_MET1S45(void)
{
    u1_s_gwcxcfg_pwsts = (U1)GWCXCFG_PWRSTS_B_BITPOS;
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_MET1S45(void)
{
    u1_s_gwcxcfg_pwsts = (U1)GWCXCFG_PWRSTS_B_BITPOS;
}
#endif

#if defined(MSG_CMB1S05_TXCH0)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CMB1S05(void)
{
    u1_s_cxcmb1s05_cxpsts_old = (U1)COM_NO_RX;
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CMB1S05(void)
{
    u1_s_cxcmb1s05_cxpsts_old = (U1)COM_NO_RX;
}
#endif

#if defined(MSG_CMB1S06_TXCH0)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CMB1S06(void)
{
    u1_s_cxcmb1s06_cxpsts_old = (U1)COM_NO_RX;
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CMB1S06(void)
{
    u1_s_cxcmb1s06_cxpsts_old = (U1)COM_NO_RX;
}
#endif

/*===================================================================================================================================*/
/*  Update CXPI Error Bit Status                                                                                                     */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfgUpdCxpErr(void)
{
    vd_s_GwcxCfgUpd_CXP_UERR();
    vd_s_GwcxCfgUpd_CXP_ERR();
    vd_s_GwcxCfgUpd_CXP_TERR();
    vd_s_GwcxCfgUpd_CXP_WERR();
}

#if defined(ComConf_ComSignal_CXP_UERR) && \
   (defined(OXCAN_PDU_RX_CXP_SWS1S02) && defined(OXCAN_PDU_RX_CXP_SWS1S04))
/*===================================================================================================================================*/
/*  Update CXPI Error Bit Status                                                                                                     */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfgUpd_CXP_UERR(void)
{
    U1 u1_t_cxsws1s02_timeout;        /*  CXSWS1S02 Timeout             */
    U1 u1_t_cxsws1s04_timeout;        /*  CXSWS1S04 Timeout             */
    U1 u1_t_cxsws1s02_supd;           /*  CXSWS1S02 Variation Support   */
    U1 u1_t_cxsws1s04_supd;           /*  CXSWS1S04 Variation Support   */

    u1_t_cxsws1s02_timeout = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CXP_SWS1S02,
                                                   (U2)OXCAN_RX_SYS_NRX_PAR | (U2)OXCAN_RX_SYS_TOE_PAR,
                                                   u2_GATEWAY_RXTO_THRSH) & (U1)COM_TIMEOUT;
    u1_t_cxsws1s04_timeout = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CXP_SWS1S04,
                                                   (U2)OXCAN_RX_SYS_NRX_PAR | (U2)OXCAN_RX_SYS_TOE_PAR,
                                                   u2_GATEWAY_RXTO_THRSH) & (U1)COM_TIMEOUT;

    u1_t_cxsws1s02_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXSWS1S02);
    u1_t_cxsws1s04_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXSWS1S04);

    if(((u1_t_cxsws1s02_timeout != (U1)0U) && (u1_t_cxsws1s02_supd == (U1)TRUE)) ||
       ((u1_t_cxsws1s04_timeout != (U1)0U) && (u1_t_cxsws1s04_supd == (U1)TRUE))){
        u1_s_gwcxcfg_CxpUerr = (U1)GATEWAY_CXPICFG_CXPICOM_ERR;
    }
    else{
        u1_s_gwcxcfg_CxpUerr = (U1)GATEWAY_CXPICFG_CXPICOM_NORM;
    }
}
#elif defined(ComConf_ComSignal_CXP_UERR) && defined(OXCAN_PDU_RX_CXP_SWS1S02)
/*===================================================================================================================================*/
/*  Update CXPI Error Bit Status                                                                                                     */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfgUpd_CXP_UERR(void)
{
    U1 u1_t_cxsws1s02_timeout;        /*  CXSWS1S02 Timeout             */
    U1 u1_t_cxsws1s02_supd;           /*  CXSWS1S02 Variation Support   */

    u1_t_cxsws1s02_timeout = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CXP_SWS1S02,
                                                   (U2)OXCAN_RX_SYS_NRX_PAR | (U2)OXCAN_RX_SYS_TOE_PAR,
                                                   u2_GATEWAY_RXTO_THRSH) & (U1)COM_TIMEOUT;

    u1_t_cxsws1s02_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXSWS1S02);

    if((u1_t_cxsws1s02_timeout != (U1)0U) && (u1_t_cxsws1s02_supd == (U1)TRUE)){
        u1_s_gwcxcfg_CxpUerr = (U1)GATEWAY_CXPICFG_CXPICOM_ERR;
    }
    else{
        u1_s_gwcxcfg_CxpUerr = (U1)GATEWAY_CXPICFG_CXPICOM_NORM;
    }
}
#elif defined(ComConf_ComSignal_CXP_UERR) && defined(OXCAN_PDU_RX_CXP_SWS1S04)
/*===================================================================================================================================*/
/*  Update CXPI Error Bit Status                                                                                                     */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfgUpd_CXP_UERR(void)
{
    U1 u1_t_cxsws1s04_timeout;        /*  CXSWS1S04 Timeout             */
    U1 u1_t_cxsws1s04_supd;           /*  CXSWS1S04 Variation Support   */

    u1_t_cxsws1s04_timeout = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CXP_SWS1S04,
                                                   (U2)OXCAN_RX_SYS_NRX_PAR | (U2)OXCAN_RX_SYS_TOE_PAR,
                                                   u2_GATEWAY_RXTO_THRSH) & (U1)COM_TIMEOUT;

    u1_t_cxsws1s04_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXSWS1S04);

    if((u1_t_cxsws1s04_timeout != (U1)0U) && (u1_t_cxsws1s04_supd == (U1)TRUE)){
        u1_s_gwcxcfg_CxpUerr = (U1)GATEWAY_CXPICFG_CXPICOM_ERR;
    }
    else{
        u1_s_gwcxcfg_CxpUerr = (U1)GATEWAY_CXPICFG_CXPICOM_NORM;
    }
}
#else
/*===================================================================================================================================*/
/*  Update CXPI Error Bit Status                                                                                                     */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfgUpd_CXP_UERR(void)
{
    u1_s_gwcxcfg_CxpUerr = (U1)GATEWAY_CXPICFG_CXPICOM_NORM;
}
#endif

#if defined(ComConf_ComSignal_CXP_ERR) && defined(OXCAN_PDU_RX_CXP_MPS1S01)
/*===================================================================================================================================*/
/*  Update CXPI Error Bit Status                                                                                                     */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfgUpd_CXP_ERR(void)
{
    U1 u1_t_cxmps1s01_timeout;        /*  CXMPS1S01 Timeout             */
    U1 u1_t_cxmps1s01_supd;           /*  CXMPS1S01 Variation Support   */

    u1_t_cxmps1s01_timeout = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CXP_MPS1S01,
                                                   (U2)OXCAN_RX_SYS_NRX_PAR | (U2)OXCAN_RX_SYS_TOE_PAR,
                                                   u2_GATEWAY_RXTO_THRSH) & (U1)COM_TIMEOUT;

    u1_t_cxmps1s01_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXMPS1S01);

    if((u1_t_cxmps1s01_timeout != (U1)0U) && (u1_t_cxmps1s01_supd == (U1)TRUE)){
        u1_s_gwcxcfg_CxpErr = (U1)GATEWAY_CXPICFG_CXPICOM_ERR;
    }
    else{
        u1_s_gwcxcfg_CxpErr = (U1)GATEWAY_CXPICFG_CXPICOM_NORM;
    }
}
#else
/*===================================================================================================================================*/
/*  Update CXPI Error Bit Status                                                                                                     */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfgUpd_CXP_ERR(void)
{
    u1_s_gwcxcfg_CxpErr = (U1)GATEWAY_CXPICFG_CXPICOM_NORM;
}
#endif

#if defined(ComConf_ComSignal_CXP_TERR) && defined(OXCAN_PDU_RX_CXP_CMB1S05)
/*===================================================================================================================================*/
/*  Update CXPI Error Bit Status                                                                                                     */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfgUpd_CXP_TERR(void)
{
    U1 u1_t_cxcmb1s05_timeout;        /*  CXCMB1S05 Timeout             */
    U1 u1_t_cxcmb1s05_supd;           /*  CXCMB1S05 Variation Support   */
    U1 u1_t_cxpterr_old;              /*  Signal old Value CXP_TERR     */

    u1_t_cxcmb1s05_timeout = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CXP_CMB1S05,
                                                   (U2)OXCAN_RX_SYS_NRX_PAR | (U2)OXCAN_RX_SYS_TOE_PAR,
                                                   u2_GATEWAY_RXTO_THRSH) & (U1)COM_TIMEOUT;

    u1_t_cxcmb1s05_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S05);
    u1_t_cxpterr_old = u1_s_gwcxcfg_CxpTerr;

    if((u1_t_cxcmb1s05_timeout != (U1)0U) && (u1_t_cxcmb1s05_supd == (U1)TRUE)){
        u1_s_gwcxcfg_CxpTerr = (U1)GATEWAY_CXPICFG_CXPICOM_ERR;
    }
    else{
        u1_s_gwcxcfg_CxpTerr = (U1)GATEWAY_CXPICFG_CXPICOM_NORM;
    }

    if(u1_s_gwcxcfg_CxpTerr != u1_t_cxpterr_old){
        u1_s_gwcxcfg_cxp_terr_chgflg = (U1)TRUE;
    }
    else{
        u1_s_gwcxcfg_cxp_terr_chgflg = (U1)FALSE;
    }
}
#else
/*===================================================================================================================================*/
/*  Update CXPI Error Bit Status                                                                                                     */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfgUpd_CXP_TERR(void)
{
    u1_s_gwcxcfg_CxpTerr = (U1)GATEWAY_CXPICFG_CXPICOM_NORM;
    u1_s_gwcxcfg_cxp_terr_chgflg = (U1)FALSE;
}
#endif

#if defined(ComConf_ComSignal_CXP_WERR) && defined(OXCAN_PDU_RX_CXP_CMB1S06)
/*===================================================================================================================================*/
/*  Update CXPI Error Bit Status                                                                                                     */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfgUpd_CXP_WERR(void)
{
    U1 u1_t_cxcmb1s06_timeout;        /*  CXCMB1S06 Timeout             */
    U1 u1_t_cxcmb1s06_supd;           /*  CXCMB1S06 Variation Support   */
    U1 u1_t_cxpwerr_old;              /*  Signal old Value CXP_WERR     */

    u1_t_cxcmb1s06_timeout = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CXP_CMB1S06,
                                                   (U2)OXCAN_RX_SYS_NRX_PAR | (U2)OXCAN_RX_SYS_TOE_PAR,
                                                   u2_GATEWAY_RXTO_THRSH) & (U1)COM_TIMEOUT;

    u1_t_cxcmb1s06_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S06);
    
    u1_t_cxpwerr_old = u1_s_gwcxcfg_CxpWerr;


    if((u1_t_cxcmb1s06_timeout != (U1)0U) && (u1_t_cxcmb1s06_supd == (U1)TRUE)){
        u1_s_gwcxcfg_CxpWerr = (U1)GATEWAY_CXPICFG_CXPICOM_ERR;
    }
    else{
        u1_s_gwcxcfg_CxpWerr = (U1)GATEWAY_CXPICFG_CXPICOM_NORM;
    }
    
    if(u1_s_gwcxcfg_CxpWerr != u1_t_cxpwerr_old){
        u1_s_gwcxcfg_cxp_werr_chgflg = (U1)TRUE;
    }
    else{
        u1_s_gwcxcfg_cxp_werr_chgflg = (U1)FALSE;
    }
}
#else
/*===================================================================================================================================*/
/*  Update CXPI Error Bit Status                                                                                                     */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfgUpd_CXP_WERR(void)
{
    u1_s_gwcxcfg_CxpWerr = (U1)GATEWAY_CXPICFG_CXPICOM_NORM;
    u1_s_gwcxcfg_cxp_werr_chgflg = (U1)FALSE;
}
#endif

#if defined(OXCAN_PDU_RX_CXP_CMB1S05)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_CXCMB1S05_Msgsts(void)
{
    U1 u1_t_msgsts;                     /*  Receive Status              */

    u1_t_msgsts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CXP_CMB1S05,
                                        (U2)OXCAN_RX_SYS_NRX_PAR | (U2)OXCAN_RX_SYS_TOE_PAR,
                                        u2_GATEWAY_RXTO_THRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    return(u1_t_msgsts);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_CXCMB1S05_Msgsts(void)
{
    U1 u1_t_msgsts;                     /*  Receive Status              */

    u1_t_msgsts = ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    return(u1_t_msgsts);
}
#endif

#if defined(OXCAN_PDU_RX_CXP_CMB1S06)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_CXCMB1S06_Msgsts(void)
{
    U1 u1_t_msgsts;                     /*  Receive Status              */

    u1_t_msgsts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CXP_CMB1S06,
                                        (U2)OXCAN_RX_SYS_NRX_PAR | (U2)OXCAN_RX_SYS_TOE_PAR,
                                        u2_GATEWAY_RXTO_THRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    return(u1_t_msgsts);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_CXCMB1S06_Msgsts(void)
{
    U1 u1_t_msgsts;                     /*  Receive Status              */

    u1_t_msgsts = ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    return(u1_t_msgsts);
}
#endif

#if defined(ComConf_ComSignal_CXP_JDGT) && defined(OXCAN_PDU_RX_CXP_CMB1S05)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXP_JDGT_Send(const U1  u1_a_PWRSTS)
{
    U1 u1_t_supd;            /*  Variation Support */

    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S05);

    if(u1_t_supd == (U1)TRUE){
        u1_s_gwcxcfg_CxpJdgT = (U1)GWCXCFG_CXPIJDG_EXIST;
    }
    else{
        u1_s_gwcxcfg_CxpJdgT = (U1)GWCXCFG_CXPIJDG_NOTEXIST;
    }

    (void)Com_SendSignal(ComConf_ComSignal_CXP_JDGT, (&u1_s_gwcxcfg_CxpJdgT));
}
#elif defined(ComConf_ComSignal_CXP_JDGT)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXP_JDGT_Send(const U1  u1_a_PWRSTS)
{
    u1_s_gwcxcfg_CxpJdgT = (U1)GWCXCFG_CXPIJDG_NOTEXIST;

    (void)Com_SendSignal(ComConf_ComSignal_CXP_JDGT, (&u1_s_gwcxcfg_CxpJdgT));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXP_JDGT_Send(const U1  u1_a_PWRSTS)
{
}
#endif

#if defined(ComConf_ComSignal_CXP_TERR) && defined(OXCAN_PDU_RX_CXP_CMB1S05)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXP_TERR_Send(const U1  u1_a_PWRSTS)
{
    (void)Com_SendSignal(ComConf_ComSignal_CXP_TERR, (&u1_s_gwcxcfg_CxpTerr));
}
#elif defined(ComConf_ComSignal_CXP_TERR)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXP_TERR_Send(const U1  u1_a_PWRSTS)
{
   (void)Com_SendSignal(ComConf_ComSignal_CXP_TERR, (&u1_s_gwcxcfg_CxpTerr));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXP_TERR_Send(const U1  u1_a_PWRSTS)
{
}
#endif

#if defined(ComConf_ComSignal_CXP_JDGW) && defined(OXCAN_PDU_RX_CXP_CMB1S06)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXP_JDGW_Send(const U1  u1_a_PWRSTS)
{
    U1 u1_t_supd;            /*  Variation Support */

    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S06);

    if(u1_t_supd == (U1)TRUE){
        u1_s_gwcxcfg_CxpJdgW = (U1)GWCXCFG_CXPIJDG_EXIST;
    }
    else{
        u1_s_gwcxcfg_CxpJdgW = (U1)GWCXCFG_CXPIJDG_NOTEXIST;
     }

    (void)Com_SendSignal(ComConf_ComSignal_CXP_JDGW, (&u1_s_gwcxcfg_CxpJdgW));
}
#elif defined(ComConf_ComSignal_CXP_JDGW)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXP_JDGW_Send(const U1  u1_a_PWRSTS)
{
    u1_s_gwcxcfg_CxpJdgW = (U1)GWCXCFG_CXPIJDG_NOTEXIST;

    (void)Com_SendSignal(ComConf_ComSignal_CXP_JDGW, (&u1_s_gwcxcfg_CxpJdgW));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXP_JDGW_Send(const U1  u1_a_PWRSTS)
{
}
#endif

#if defined(ComConf_ComSignal_CXP_WERR) && defined(OXCAN_PDU_RX_CXP_CMB1S06)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXP_WERR_Send(const U1  u1_a_PWRSTS)
{
    (void)Com_SendSignal(ComConf_ComSignal_CXP_WERR, (&u1_s_gwcxcfg_CxpWerr));
}
#elif defined(ComConf_ComSignal_CXP_WERR)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXP_WERR_Send(const U1  u1_a_PWRSTS)
{
    (void)Com_SendSignal(ComConf_ComSignal_CXP_WERR, (&u1_s_gwcxcfg_CxpWerr));
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXP_WERR_Send(const U1  u1_a_PWRSTS)
{
}
#endif

/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CanToCxpi(void)
{
    /* Initialize CXMET1S01 */
    vd_s_GwcxCfg_Init_RHEOSTAT();
    vd_s_GwcxCfg_CXMET1S01_Send();

    /* Initialize CXMET1S03 */
    vd_s_GwcxCfg_Init_VIBTOFFG();
    vd_s_GwcxCfg_Init_VIBSTRG();
    vd_s_GwcxCfg_Init_VIBTONG();
    vd_s_GwcxCfg_CXMET1S03_Send();

    /* Initialize CXMET1S04 */
    vd_s_GwcxCfg_Init_O_STG_F();
    vd_s_GwcxCfg_CXMET1S04_Send();

    /* Initialize CXMET1S05 */
    vd_s_GwcxCfg_Init_T_LOGI();
    vd_s_GwcxCfg_Init_EL_SENS();
    vd_s_GwcxCfg_CXMET1S05_Send();

    /* Initialize CXMET1S06 */
    vd_s_GwcxCfg_Init_ADIM();
    vd_s_GwcxCfg_Init_HEDH();
    vd_s_GwcxCfg_Init_HEDL();
    vd_s_GwcxCfg_Init_TAIL06();
    vd_s_GwcxCfg_Init_FFOG();
    vd_s_GwcxCfg_Init_RFOG();
    vd_s_GwcxCfg_Init_CONLT_PR();
    vd_s_GwcxCfg_Init_BW_SW_PR();
    vd_s_GwcxCfg_Init_AUTINT();
    vd_s_GwcxCfg_CXMET1S06_Send();
}

#if defined(CxpiCdd_TsWr0Cxmet1s01RHEOSTAT)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_RHEOSTAT(void)
{
    u1_s_gwcxcfg_rheostat = (U1)0U;
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_RHEOSTAT(void)
{
    u1_s_gwcxcfg_rheostat = (U1)0U;
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s03VIBTOFFG)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_VIBTOFFG(void)
{
    u1_s_gwcxcfg_vibtoffg = (U1)GWCXCFG_STGVIB_MOTOR_OFF_UNUSED_0;
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_VIBTOFFG(void)
{
    u1_s_gwcxcfg_vibtoffg = (U1)GWCXCFG_STGVIB_MOTOR_OFF_UNUSED_0;
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s03VIBSTRG)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_VIBSTRG(void)
{
    u1_s_gwcxcfg_vibstrg = (U1)GWCXCFG_STGVIB_VIBSTR_UNUSED_0;
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_VIBSTRG(void)
{
    u1_s_gwcxcfg_vibstrg = (U1)GWCXCFG_STGVIB_VIBSTR_UNUSED_0;
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s03VIBTONG)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_VIBTONG(void)
{
    u1_s_gwcxcfg_vibtong = (U1)GWCXCFG_STGVIB_MOTOR_ON_UNUSED_0;
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_VIBTONG(void)
{
    u1_s_gwcxcfg_vibtong = (U1)GWCXCFG_STGVIB_MOTOR_ON_UNUSED_0;
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s04O_STG_F)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_O_STG_F(void)
{
    u1_s_gwcxcfg_ostgf = (U1)GWCXCFG_STGHTR_OFF;
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_O_STG_F(void)
{
    u1_s_gwcxcfg_ostgf = (U1)GWCXCFG_STGHTR_OFF;
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s05T_LOGI) && defined(GATEWAY_CXPICFG_T_LOGI_SUP)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_T_LOGI(void)
{
    U1 u1_t_cstm;                        /*  Diag Customize             */

    u1_t_cstm = (U1)((u4_g_VardefDs2E_Las32((U2)VDF_DS_2E_2209) & (U4)VDF_DS_2E_TDSS_MSK) >> GWCXCFG_SHIFT_1BYTE);
    if(u1_t_cstm <= (U1)GWCXCFG_T_LOGI_MAX){
        u1_s_gwcxcfg_t_logi = u1_t_cstm;
    }
    else{
        u1_s_gwcxcfg_t_logi = (U1)GWCXCFG_T_LOGI_NOLOGIC;
    }
}
#elif defined(CxpiCdd_TsWr0Cxmet1s05T_LOGI)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_T_LOGI(void)
{
    u1_s_gwcxcfg_t_logi = (U1)GWCXCFG_T_LOGI_NOLOGIC;
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_T_LOGI(void)
{
    u1_s_gwcxcfg_t_logi = (U1)GWCXCFG_T_LOGI_NOLOGIC;
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s05EL_SENS)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_EL_SENS(void)
{
    u1_s_gwcxcfg_el_sens = (U1)GWCXCFG_EL_SENS_NORMAL;
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_EL_SENS(void)
{
    u1_s_gwcxcfg_el_sens = (U1)GWCXCFG_EL_SENS_NORMAL;
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s06ADIM)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_ADIM(void)
{
    u1_s_gwcxcfg_adim = (U1)GWCXCFG_ADIM_UNDET;
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_ADIM(void)
{
    u1_s_gwcxcfg_adim = (U1)GWCXCFG_ADIM_UNDET;
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s06HEDH)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_HEDH(void)
{
    u1_s_gwcxcfg_hedh = (U1)GWCXCFG_HEDH_OFF;
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_HEDH(void)
{
    u1_s_gwcxcfg_hedh = (U1)GWCXCFG_HEDH_OFF;
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s06HEDL)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_HEDL(void)
{
    u1_s_gwcxcfg_hedl = (U1)GWCXCFG_HEDL_OFF;
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_HEDL(void)
{
    u1_s_gwcxcfg_hedl = (U1)GWCXCFG_HEDL_OFF;
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s06TAIL)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_TAIL06(void)
{
    u1_s_gwcxcfg_tail_cxmet1s06 = (U1)GWCXCFG_TAIL_OFF;
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_TAIL06(void)
{
    u1_s_gwcxcfg_tail_cxmet1s06 = (U1)GWCXCFG_TAIL_OFF;
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s06FFOG)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_FFOG(void)
{
    u1_s_gwcxcfg_ffog = (U1)GWCXCFG_FFOG_OFF;
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_FFOG(void)
{
    u1_s_gwcxcfg_ffog = (U1)GWCXCFG_FFOG_OFF;
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s06RFOG)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_RFOG(void)
{
    u1_s_gwcxcfg_rfog = (U1)GWCXCFG_RFOG_OFF;
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_RFOG(void)
{
    u1_s_gwcxcfg_rfog = (U1)GWCXCFG_RFOG_OFF;
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s06CONLT_PR)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CONLT_PR(void)
{
    u1_s_gwcxcfg_conlt_pr = (U1)GWCXCFG_CONLT_PR_NOSEND;
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_CONLT_PR(void)
{
    u1_s_gwcxcfg_conlt_pr = (U1)GWCXCFG_CONLT_PR_NOSEND;
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s06BW_SW_PR)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_BW_SW_PR(void)
{
    u1_s_gwcxcfg_bw_sw_pr = (U1)GWCXCFG_BW_SW_PR_NOSEND;
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_BW_SW_PR(void)
{
    u1_s_gwcxcfg_bw_sw_pr = (U1)GWCXCFG_BW_SW_PR_NOSEND;
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s06AUTINT)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_AUTINT(void)
{
    u1_s_gwcxcfg_autint = (U1)GWCXCFG_AUTINT_NOSEND;
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway initial                                                                                                      */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_Init_AUTINT(void)
{
    u1_s_gwcxcfg_autint = (U1)GWCXCFG_AUTINT_NOSEND;
}
#endif

#if defined(CXPICDD_FRM_0_CH0_CXMET1S01_INDEX) && \
   defined(ComConf_ComSignal_RHEOSTAT)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXMET1S01_SetData(const U1  u1_a_PWRSTS)
{
    U1 u1_t_data_updated;                   /*  Data Update Flag           */

    u1_t_data_updated = (U1)GWCXCFG_NOTUPDATED;

    u1_t_data_updated |= u1_s_GwcxCfg_RHEOSTAT_SetData(u1_a_PWRSTS);

    if(u1_t_data_updated == (U1)GWCXCFG_UPDATED){
        vd_s_GwcxCfg_CXMET1S01_Send();
    }
}
#elif defined(CXPICDD_FRM_0_CH0_CXMET1S01_INDEX)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXMET1S01_SetData(const U1  u1_a_PWRSTS)
{
    vd_s_GwcxCfg_CXMET1S01_Send();
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXMET1S01_SetData(const U1  u1_a_PWRSTS)
{
}
#endif

#if defined(MSG_FCM1S28_RXCH0)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_FCM1S28_Msgsts(void)
{
    U1 u1_t_msgsts;                     /*  Receive Status              */

    u1_t_msgsts  = Com_GetIPDUStatus(MSG_FCM1S28_RXCH0);
    u1_t_msgsts &= ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    return(u1_t_msgsts);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_FCM1S28_Msgsts(void)
{
    U1 u1_t_msgsts;                     /*  Receive Status              */

    u1_t_msgsts = ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    return(u1_t_msgsts);
}
#endif

#if defined(MSG_ACN1S03_RXCH0)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_ACN1S03_Msgsts(void)
{
    U1 u1_t_msgsts;                     /*  Receive Status              */

    u1_t_msgsts  = Com_GetIPDUStatus(MSG_ACN1S03_RXCH0);
    u1_t_msgsts &= ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    return(u1_t_msgsts);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_ACN1S03_Msgsts(void)
{
    U1 u1_t_msgsts;                     /*  Receive Status              */

    u1_t_msgsts = ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    return(u1_t_msgsts);
}
#endif

#if defined(MSG_BDB1S01_RXCH0)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_BDB1S01_Msgsts(void)
{
    U1 u1_t_msgsts;                     /*  Receive Status              */

    u1_t_msgsts  = Com_GetIPDUStatus(MSG_BDB1S01_RXCH0);
    u1_t_msgsts &= ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    return(u1_t_msgsts);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_BDB1S01_Msgsts(void)
{
    U1 u1_t_msgsts;                     /*  Receive Status              */

    u1_t_msgsts = ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    return(u1_t_msgsts);
}
#endif

#if defined(OXCAN_PDU_RX_CAN_BDB1S22)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_BDB1S22_Msgsts(void)
{
    U1 u1_t_msgsts;                     /*  Receive Status              */

    u1_t_msgsts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_BDB1S22,
                                        (U2)OXCAN_RX_SYS_NRX_POE | (U2)OXCAN_RX_SYS_TOE_POE,
                                        u2_GATEWAY_BDB1S22_THRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    return(u1_t_msgsts);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_BDB1S22_Msgsts(void)
{
    U1 u1_t_msgsts;                     /*  Receive Status              */

    u1_t_msgsts = ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    return(u1_t_msgsts);
}
#endif

#if defined(OXCAN_PDU_RX_CAN_WIP1S01_RXCH0)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WIP1S01_Msgsts(void)
{
    U1 u1_t_msgsts;                     /*  Receive Status              */

    u1_t_msgsts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_WIP1S01_RXCH0,
                                        (U2)OXCAN_RX_SYS_NRX_PAR | (U2)OXCAN_RX_SYS_TOE_PAR,
                                        u2_GATEWAY_WIP1S01_THRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    return(u1_t_msgsts);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WIP1S01_Msgsts(void)
{
    U1 u1_t_msgsts;                     /*  Receive Status              */

    u1_t_msgsts = ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    return(u1_t_msgsts);
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s01RHEOSTAT) && defined(ComConf_ComSignal_RHEOSTAT)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_RHEOSTAT_SetData(const U1  u1_a_PWRSTS)
{
    U1 u1_t_data_updated;                   /*  Data Update Flag           */
    U1 u1_t_tx_rheostat_old;                /*  Signal old Value RHEOSTAT  */

    u1_t_tx_rheostat_old = u1_s_gwcxcfg_rheostat;
    
    (void)Com_ReceiveSignal(ComConf_ComSignal_RHEOSTAT, (&u1_s_gwcxcfg_rheostat));                  /* get Signal Value */

    if(u1_t_tx_rheostat_old != u1_s_gwcxcfg_rheostat){
        u1_t_data_updated = (U1)GWCXCFG_UPDATED;
    }
    else{
        u1_t_data_updated = (U1)GWCXCFG_NOTUPDATED;
    }

    return(u1_t_data_updated);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s01RHEOSTAT)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_RHEOSTAT_SetData(const U1  u1_a_PWRSTS)
{
    u1_s_gwcxcfg_rheostat = u1_s_gwcxcfg_rheostat;

    return((U1)GWCXCFG_NOTUPDATED);
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_RHEOSTAT_SetData(const U1  u1_a_PWRSTS)
{
    return((U1)GWCXCFG_NOTUPDATED);
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s03VIBTOFFG) && defined(ComConf_ComSignal_VIBTOFFG)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_VIBTOFFG_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_data_updated;                   /*  Data Update Flag           */
    U1 u1_t_tx_vibtoffg_old;                /*  Signal old Value VIBTOFFG  */


    u1_t_tx_vibtoffg_old = u1_s_gwcxcfg_vibtoffg;                    /* store old values */

    if(u1_a_MSGSTS != (U1)0U){
        u1_s_gwcxcfg_vibtoffg = (U1)GWCXCFG_STGVIB_MOTOR_OFF_UNUSED_0;
    }
    else{
        (void)Com_ReceiveSignal(ComConf_ComSignal_VIBTOFFG, (&u1_s_gwcxcfg_vibtoffg));
    }

    if(u1_t_tx_vibtoffg_old != u1_s_gwcxcfg_vibtoffg){
        u1_t_data_updated = (U1)GWCXCFG_UPDATED;
    }
    else{
        u1_t_data_updated = (U1)GWCXCFG_NOTUPDATED;
    }

    return(u1_t_data_updated);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s03VIBTOFFG)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_VIBTOFFG_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    u1_s_gwcxcfg_vibtoffg = (U1)GWCXCFG_STGVIB_MOTOR_OFF_UNUSED_0;

    return((U1)GWCXCFG_NOTUPDATED);
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_VIBTOFFG_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)GWCXCFG_NOTUPDATED);
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s03VIBSTRG) && defined(ComConf_ComSignal_VIBSTRG)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_VIBSTRG_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_data_updated;                   /*  Data Update Flag           */
    U1 u1_t_tx_vibstrg_old;                 /*  Signal old Value VIBSTRG   */


    u1_t_tx_vibstrg_old  = u1_s_gwcxcfg_vibstrg;

    if(u1_a_MSGSTS != (U1)0U){
        u1_s_gwcxcfg_vibstrg = (U1)GWCXCFG_STGVIB_VIBSTR_UNUSED_0;
    }
    else{
        (void)Com_ReceiveSignal(ComConf_ComSignal_VIBSTRG, (&u1_s_gwcxcfg_vibstrg));
    }

    if(u1_t_tx_vibstrg_old != u1_s_gwcxcfg_vibstrg){
        u1_t_data_updated = (U1)GWCXCFG_UPDATED;
    }
    else{
        u1_t_data_updated = (U1)GWCXCFG_NOTUPDATED;
    }

    return(u1_t_data_updated);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s03VIBSTRG)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_VIBSTRG_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    u1_s_gwcxcfg_vibstrg = (U1)GWCXCFG_STGVIB_VIBSTR_UNUSED_0;

    return((U1)GWCXCFG_NOTUPDATED);
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_VIBSTRG_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)GWCXCFG_NOTUPDATED);
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s03VIBTONG) && defined(ComConf_ComSignal_VIBTONG)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_VIBTONG_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_data_updated;                   /*  Data Update Flag           */
    U1 u1_t_tx_vibtong_old;                 /*  Signal old Value VIBTONG   */


    u1_t_tx_vibtong_old  = u1_s_gwcxcfg_vibtong;

    if(u1_a_MSGSTS != (U1)0U){
        u1_s_gwcxcfg_vibtong  = (U1)GWCXCFG_STGVIB_MOTOR_ON_UNUSED_0;
    }
    else{
        (void)Com_ReceiveSignal(ComConf_ComSignal_VIBTONG, (&u1_s_gwcxcfg_vibtong));
    }

    if(u1_t_tx_vibtong_old != u1_s_gwcxcfg_vibtong){
        u1_t_data_updated = (U1)GWCXCFG_UPDATED;
    }
    else{
        u1_t_data_updated = (U1)GWCXCFG_NOTUPDATED;
    }

    return(u1_t_data_updated);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s03VIBTONG)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_VIBTONG_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    u1_s_gwcxcfg_vibtong  = (U1)GWCXCFG_STGVIB_MOTOR_ON_UNUSED_0;

    return((U1)GWCXCFG_NOTUPDATED);
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_VIBTONG_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)GWCXCFG_NOTUPDATED);
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s04O_STG_F) && defined(ComConf_ComSignal_O_STG_F)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_O_STG_F_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_data_updated;                /*  Data Update Flag           */
    U1 u1_t_tx_ostgf_old;                /*  Signal old Value O_STG_F   */

    u1_t_tx_ostgf_old = u1_s_gwcxcfg_ostgf;                       /* store old value */

    if(u1_a_MSGSTS != (U1)0U){                    /* error case */
        u1_s_gwcxcfg_ostgf = (U1)GWCXCFG_STGHTR_OFF;
    }
    else{
        (void)Com_ReceiveSignal(ComConf_ComSignal_O_STG_F, (&u1_s_gwcxcfg_ostgf));
    }

    if(u1_t_tx_ostgf_old != u1_s_gwcxcfg_ostgf){
        u1_t_data_updated = (U1)GWCXCFG_UPDATED;
    }
    else{
        u1_t_data_updated = (U1)GWCXCFG_NOTUPDATED;
    }

    return(u1_t_data_updated);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s04O_STG_F)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_O_STG_F_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    u1_s_gwcxcfg_ostgf = (U1)GWCXCFG_STGHTR_OFF;

    return((U1)GWCXCFG_NOTUPDATED);
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_O_STG_F_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)GWCXCFG_NOTUPDATED);
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s05T_LOGI) && defined(GATEWAY_CXPICFG_T_LOGI_SUP)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_T_LOGI_SetData(const U1  u1_a_PWRSTS)
{
    U1 u1_t_data_updated;                /*  Data Update Flag           */
    U1 u1_t_tx_t_logi_old;               /*  Signal old Value T_LOGI    */
    U1 u1_t_cstm;                        /*  Diag Customize             */

    if(((u1_a_PWRSTS & (U1)GWCXCFG_PWRSTS_IGR_BITPOS) != (U1)0U) ||
       ((u1_a_PWRSTS & (U1)GWCXCFG_PWRSTS_ACC_BITPOS) != (U1)0U) ||
       ((u1_a_PWRSTS & (U1)GWCXCFG_PWRSTS_BA_BITPOS)  != (U1)0U)){

        u1_t_tx_t_logi_old = u1_s_gwcxcfg_t_logi;                        /* store old value */

        u1_t_cstm = (U1)((u4_g_VardefDs2E_Las32((U2)VDF_DS_2E_2209) & (U4)VDF_DS_2E_TDSS_MSK) >> GWCXCFG_SHIFT_1BYTE);
        if(u1_t_cstm <= (U1)GWCXCFG_T_LOGI_MAX){
            u1_s_gwcxcfg_t_logi = u1_t_cstm;
        }

        if(u1_t_tx_t_logi_old  != u1_s_gwcxcfg_t_logi ){
            u1_t_data_updated = (U1)GWCXCFG_UPDATED;
        }
        else{
            u1_t_data_updated = (U1)GWCXCFG_NOTUPDATED;
        }
    }
    else{
        u1_t_cstm = (U1)((u4_g_VardefDs2E_Las32((U2)VDF_DS_2E_2209) & (U4)VDF_DS_2E_TDSS_MSK) >> GWCXCFG_SHIFT_1BYTE);
        if(u1_t_cstm <= (U1)GWCXCFG_T_LOGI_MAX){
            u1_s_gwcxcfg_t_logi = u1_t_cstm;
        }
        u1_t_data_updated = (U1)GWCXCFG_NOTUPDATED;
    }

    return(u1_t_data_updated);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s05T_LOGI)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_T_LOGI_SetData(const U1  u1_a_PWRSTS)
{
    u1_s_gwcxcfg_t_logi = (U1)GWCXCFG_T_LOGI_NOLOGIC;

    return((U1)GWCXCFG_NOTUPDATED);
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_T_LOGI_SetData(const U1  u1_a_PWRSTS)
{
    return((U1)GWCXCFG_NOTUPDATED);
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s05EL_SENS) && defined(GATEWAY_CXPICFG_EL_SENS_SUP)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_EL_SENS_SetData(const U1  u1_a_PWRSTS)
{
    U1 u1_t_data_updated;                /*  Data Update Flag           */
    U1 u1_t_tx_el_sens_old;              /*  Signal old Value EL_SENS   */

    if(((u1_a_PWRSTS & (U1)GWCXCFG_PWRSTS_IGR_BITPOS) != (U1)0U) ||
       ((u1_a_PWRSTS & (U1)GWCXCFG_PWRSTS_ACC_BITPOS) != (U1)0U) ||
       ((u1_a_PWRSTS & (U1)GWCXCFG_PWRSTS_BA_BITPOS)  != (U1)0U)){

        u1_t_tx_el_sens_old = u1_s_gwcxcfg_el_sens;                       /* store old value */

        u1_s_gwcxcfg_el_sens = u1_g_HmiMcstELSENS();

        if(u1_t_tx_el_sens_old != u1_s_gwcxcfg_el_sens){
            u1_t_data_updated = (U1)GWCXCFG_UPDATED;
        }
        else{
            u1_t_data_updated = (U1)GWCXCFG_NOTUPDATED;
        }
    }
    else{
        u1_s_gwcxcfg_el_sens = (U1)GWCXCFG_EL_SENS_NORMAL;
        u1_t_data_updated = (U1)GWCXCFG_NOTUPDATED;
    }

    return(u1_t_data_updated);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s05EL_SENS)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_EL_SENS_SetData(const U1  u1_a_PWRSTS)
{
    u1_s_gwcxcfg_el_sens = (U1)GWCXCFG_EL_SENS_NORMAL;

    return((U1)GWCXCFG_NOTUPDATED);
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_EL_SENS_SetData(const U1  u1_a_PWRSTS)
{
    return((U1)GWCXCFG_NOTUPDATED);
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s06ADIM) && defined(ComConf_ComSignal_ADIM)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_ADIM_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_data_updated;                /*  Data Update Flag           */
    U1 u1_t_tx_adim_old;                 /*  Signal old Value ADIM      */

    u1_t_tx_adim_old = u1_s_gwcxcfg_adim;                       /* store old value */

    if(u1_a_MSGSTS == (U1)0U){
        (void)Com_ReceiveSignal(ComConf_ComSignal_ADIM, (&u1_s_gwcxcfg_adim));
    }

    if(u1_t_tx_adim_old != u1_s_gwcxcfg_adim){
        u1_t_data_updated = (U1)GWCXCFG_UPDATED;
    }
    else{
        u1_t_data_updated = (U1)GWCXCFG_NOTUPDATED;
    }

    return(u1_t_data_updated);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s06ADIM)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_ADIM_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    u1_s_gwcxcfg_adim = (U1)GWCXCFG_ADIM_UNDET;

    return((U1)GWCXCFG_NOTUPDATED);
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_ADIM_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)GWCXCFG_NOTUPDATED);
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s06HEDH) && defined(ComConf_ComSignal_HEDH)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_HEDH_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_data_updated;                /*  Data Update Flag           */
    U1 u1_t_tx_hedh_old;                 /*  Signal old Value HEDH      */

    u1_t_tx_hedh_old = u1_s_gwcxcfg_hedh;

    if(u1_a_MSGSTS == (U1)0U){
        (void)Com_ReceiveSignal(ComConf_ComSignal_HEDH, (&u1_s_gwcxcfg_hedh));
    }

    if(u1_t_tx_hedh_old != u1_s_gwcxcfg_hedh){
        u1_t_data_updated = (U1)GWCXCFG_UPDATED;
    }
    else{
        u1_t_data_updated = (U1)GWCXCFG_NOTUPDATED;
    }

    return(u1_t_data_updated);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s06HEDH)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_HEDH_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    u1_s_gwcxcfg_hedh = (U1)GWCXCFG_HEDH_OFF;

    return((U1)GWCXCFG_NOTUPDATED);
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_HEDH_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)GWCXCFG_NOTUPDATED);
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s06HEDL) && defined(ComConf_ComSignal_HEDL)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_HEDL_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_data_updated;                /*  Data Update Flag           */
    U1 u1_t_tx_hedl_old;                 /*  Signal old Value HEDL      */

    u1_t_tx_hedl_old = u1_s_gwcxcfg_hedl;

    if(u1_a_MSGSTS == (U1)0U){
        (void)Com_ReceiveSignal(ComConf_ComSignal_HEDL, (&u1_s_gwcxcfg_hedl));
    }

    if(u1_t_tx_hedl_old != u1_s_gwcxcfg_hedl){
        u1_t_data_updated = (U1)GWCXCFG_UPDATED;
    }
    else{
        u1_t_data_updated = (U1)GWCXCFG_NOTUPDATED;
    }

    return(u1_t_data_updated);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s06HEDL)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_HEDL_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    u1_s_gwcxcfg_hedl = (U1)GWCXCFG_HEDL_OFF;

    return((U1)GWCXCFG_NOTUPDATED);
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_HEDL_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)GWCXCFG_NOTUPDATED);
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s06TAIL) && defined(ComConf_ComSignal_TAIL)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_TAIL06_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_data_updated;                /*  Data Update Flag           */
    U1 u1_t_tx_tail_old;                 /*  Signal old Value TAIL      */

    u1_t_tx_tail_old = u1_s_gwcxcfg_tail_cxmet1s06;

    if(u1_a_MSGSTS != (U1)0U){
        u1_s_gwcxcfg_tail_cxmet1s06 = (U1)GWCXCFG_TAIL_OFF;
    }
    else{
        (void)Com_ReceiveSignal(ComConf_ComSignal_TAIL, (&u1_s_gwcxcfg_tail_cxmet1s06));
    }

    if(u1_t_tx_tail_old != u1_s_gwcxcfg_tail_cxmet1s06){
        u1_t_data_updated = (U1)GWCXCFG_UPDATED;
    }
    else{
        u1_t_data_updated = (U1)GWCXCFG_NOTUPDATED;
    }

    return(u1_t_data_updated);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s06TAIL)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_TAIL06_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    u1_s_gwcxcfg_tail_cxmet1s06 = (U1)GWCXCFG_TAIL_OFF;

    return((U1)GWCXCFG_NOTUPDATED);
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_TAIL06_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)GWCXCFG_NOTUPDATED);
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s06FFOG) && defined(ComConf_ComSignal_FFOG)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_FFOG_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_data_updated;                /*  Data Update Flag           */
    U1 u1_t_tx_ffog_old;                 /*  Signal old Value FFOG      */

    u1_t_tx_ffog_old = u1_s_gwcxcfg_ffog;

    if(u1_a_MSGSTS == (U1)0U){
        (void)Com_ReceiveSignal(ComConf_ComSignal_FFOG, (&u1_s_gwcxcfg_ffog));
    }

    if(u1_t_tx_ffog_old != u1_s_gwcxcfg_ffog){
        u1_t_data_updated = (U1)GWCXCFG_UPDATED;
    }
    else{
        u1_t_data_updated = (U1)GWCXCFG_NOTUPDATED;
    }

    return(u1_t_data_updated);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s06FFOG)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_FFOG_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    u1_s_gwcxcfg_ffog = (U1)GWCXCFG_FFOG_OFF;

    return((U1)GWCXCFG_NOTUPDATED);
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_FFOG_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)GWCXCFG_NOTUPDATED);
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s06RFOG) && defined(ComConf_ComSignal_RFOG)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_RFOG_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_data_updated;                /*  Data Update Flag           */
    U1 u1_t_tx_rfog_old;                 /*  Signal old Value RFOG      */

    u1_t_tx_rfog_old = u1_s_gwcxcfg_rfog;

    if(u1_a_MSGSTS == (U1)0U){
        (void)Com_ReceiveSignal(ComConf_ComSignal_RFOG, (&u1_s_gwcxcfg_rfog));
    }

    if(u1_t_tx_rfog_old != u1_s_gwcxcfg_rfog){
        u1_t_data_updated = (U1)GWCXCFG_UPDATED;
    }
    else{
        u1_t_data_updated = (U1)GWCXCFG_NOTUPDATED;
    }

    return(u1_t_data_updated);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s06RFOG)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_RFOG_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    u1_s_gwcxcfg_rfog = (U1)GWCXCFG_RFOG_OFF;

    return((U1)GWCXCFG_NOTUPDATED);
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_RFOG_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)GWCXCFG_NOTUPDATED);
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s06CONLT_PR) && defined(ComConf_ComSignal_CONLT_PR)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_CONLT_PR_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_data_updated;                /*  Data Update Flag           */
    U1 u1_t_tx_conlt_pr_old;             /*  Signal old Value CONLT_PR  */
    U1 u1_t_tx_conlt_pr_sig;             /*  Signal Value CONLT_PR      */

    u1_t_tx_conlt_pr_old = u1_s_gwcxcfg_conlt_pr;

    if(u1_a_MSGSTS != (U1)0U){
        u1_s_gwcxcfg_conlt_pr = (U1)GWCXCFG_CONLT_PR_NOSEND;
    }
    else{
        (void)Com_ReceiveSignal(ComConf_ComSignal_CONLT_PR, (&u1_t_tx_conlt_pr_sig));
        
        if(u1_t_tx_conlt_pr_sig < (U1)GWCXCFG_CONLT_PR_MSGTBL_NUM){
            u1_s_gwcxcfg_conlt_pr = u1_sp_GWCX_CONLT_PR_SENDMSG[u1_t_tx_conlt_pr_sig];
        }
    }

    if(u1_t_tx_conlt_pr_old != u1_s_gwcxcfg_conlt_pr){
        u1_t_data_updated = (U1)GWCXCFG_UPDATED;
    }
    else{
        u1_t_data_updated = (U1)GWCXCFG_NOTUPDATED;
    }

    return(u1_t_data_updated);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s06CONLT_PR)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_CONLT_PR_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    u1_s_gwcxcfg_conlt_pr = (U1)GWCXCFG_CONLT_PR_NOSEND;

    return((U1)GWCXCFG_NOTUPDATED);
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_CONLT_PR_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)GWCXCFG_NOTUPDATED);
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s06BW_SW_PR) && defined(ComConf_ComSignal_BW_SW_PR)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_BW_SW_PR_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_data_updated;                /*  Data Update Flag           */
    U1 u1_t_tx_bw_sw_pr_old;             /*  Signal old Value BW_SW_PR  */
    U1 u1_t_tx_bw_sw_pr_sig;             /*  Signal Value BW_SW_PR      */

    u1_t_tx_bw_sw_pr_old = u1_s_gwcxcfg_bw_sw_pr;

    if(u1_a_MSGSTS != (U1)0U){
        u1_s_gwcxcfg_bw_sw_pr = (U1)GWCXCFG_BW_SW_PR_NOSEND;
    }
    else{
        (void)Com_ReceiveSignal(ComConf_ComSignal_BW_SW_PR, (&u1_t_tx_bw_sw_pr_sig));
        
        if(u1_t_tx_bw_sw_pr_sig < (U1)GWCXCFG_BW_SW_PR_MSGTBL_NUM){
            u1_s_gwcxcfg_bw_sw_pr = u1_sp_GWCX_BW_SW_PR_SENDMSG[u1_t_tx_bw_sw_pr_sig];
        }
    }

    if(u1_t_tx_bw_sw_pr_old != u1_s_gwcxcfg_bw_sw_pr){
        u1_t_data_updated = (U1)GWCXCFG_UPDATED;
    }
    else{
        u1_t_data_updated = (U1)GWCXCFG_NOTUPDATED;
    }

    return(u1_t_data_updated);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s06BW_SW_PR)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_BW_SW_PR_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    u1_s_gwcxcfg_bw_sw_pr = (U1)GWCXCFG_BW_SW_PR_NOSEND;

    return((U1)GWCXCFG_NOTUPDATED);
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_BW_SW_PR_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)GWCXCFG_NOTUPDATED);
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s06AUTINT) && defined(ComConf_ComSignal_AUTOINT)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_AUTINT_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_data_updated;                /*  Data Update Flag           */
    U1 u1_t_tx_autint_old;               /*  Signal old Value AUTINT    */
    U1 u1_t_tx_autoint_sig;              /*  Signal Value AUTOINT       */

    u1_t_tx_autint_old = u1_s_gwcxcfg_autint;

    if(u1_a_MSGSTS != (U1)0U){
        u1_s_gwcxcfg_autint = (U1)GWCXCFG_AUTINT_NOSEND;
    }
    else{
        (void)Com_ReceiveSignal(ComConf_ComSignal_AUTOINT, (&u1_t_tx_autoint_sig));
        
        if(u1_t_tx_autoint_sig < (U1)GWCXCFG_AUTINT_MSGTBL_NUM){
            u1_s_gwcxcfg_autint = u1_sp_GWCX_AUTINT_SENDMSG[u1_t_tx_autoint_sig];
        }
    }

    if(u1_t_tx_autint_old != u1_s_gwcxcfg_autint){
        u1_t_data_updated = (U1)GWCXCFG_UPDATED;
    }
    else{
        u1_t_data_updated = (U1)GWCXCFG_NOTUPDATED;
    }

    return(u1_t_data_updated);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s06AUTINT)
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_AUTINT_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    u1_s_gwcxcfg_autint = (U1)GWCXCFG_AUTINT_NOSEND;

    return((U1)GWCXCFG_NOTUPDATED);
}
#else
/*===================================================================================================================================*/
/*  CAN to CXPI gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    u1_t_data_updated : Signal Update                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_AUTINT_SetData(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)GWCXCFG_NOTUPDATED);
}
#endif

#if defined(CXPICDD_FRM_0_CH0_CXMET1S01_INDEX) && \
   defined(ComConf_ComSignal_RHEOSTAT)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXMET1S01_Send(void)
{
    vd_s_GwcxCfg_RHEOSTAT_Send();

#if 0   /* BEV BSW provisionally */
    vd_g_oXCANCxptxTrgrTx((U1)CXPICDD_FRM_0_CH0_CXMET1S01_INDEX);
#endif
}
#elif defined(CXPICDD_FRM_0_CH0_CXMET1S02_INDEX)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXMET1S01_Send(void)
{
    vd_s_GwcxCfg_RHEOSTAT_Send();
}
#else
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXMET1S01_Send(void)
{
}
#endif

#if defined(CXPICDD_FRM_0_CH0_CXMET1S03_INDEX) && \
   (defined(ComConf_ComSignal_VIBTOFFG) || defined(ComConf_ComSignal_VIBSTRG)  || defined(ComConf_ComSignal_VIBTONG))
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXMET1S03_Send(void)
{
    vd_s_GwcxCfg_VIBTOFFG_Send();
    vd_s_GwcxCfg_VIBSTRG_Send();
    vd_s_GwcxCfg_VIBTONG_Send();

#if 0   /* BEV BSW provisionally */
    vd_g_oXCANCxptxTrgrTx((U1)CXPICDD_FRM_0_CH0_CXMET1S03_INDEX);
#endif
}
#elif defined(CXPICDD_FRM_0_CH0_CXMET1S03_INDEX)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXMET1S03_Send(void)
{
    vd_s_GwcxCfg_VIBTOFFG_Send();
    vd_s_GwcxCfg_VIBSTRG_Send();
    vd_s_GwcxCfg_VIBTONG_Send();
}
#else
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXMET1S03_Send(void)
{
}
#endif

#if defined(CXPICDD_FRM_0_CH0_CXMET1S04_INDEX) && defined(ComConf_ComSignal_O_STG_F)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXMET1S04_Send(void)
{
    vd_s_GwcxCfg_O_STG_F_Send();

#if 0   /* BEV BSW provisionally */
    vd_g_oXCANCxptxTrgrTx((U1)CXPICDD_FRM_0_CH0_CXMET1S04_INDEX);
#endif
}
#elif defined(CXPICDD_FRM_0_CH0_CXMET1S04_INDEX)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXMET1S04_Send(void)
{
    vd_s_GwcxCfg_O_STG_F_Send();
}
#else
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXMET1S04_Send(void)
{
}
#endif

#if defined(CXPICDD_FRM_0_CH0_CXMET1S05_INDEX) && \
   (defined(GATEWAY_CXPICFG_T_LOGI_SUP) || defined(GATEWAY_CXPICFG_EL_SENS_SUP))
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXMET1S05_Send(void)
{
    vd_s_GwcxCfg_T_LOGI_Send();
    vd_s_GwcxCfg_EL_SENS_Send();

#if 0   /* BEV BSW provisionally */
    vd_g_oXCANCxptxTrgrTx((U1)CXPICDD_FRM_0_CH0_CXMET1S05_INDEX);
#endif
}
#elif defined(CXPICDD_FRM_0_CH0_CXMET1S05_INDEX)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXMET1S05_Send(void)
{
    vd_s_GwcxCfg_T_LOGI_Send();
    vd_s_GwcxCfg_EL_SENS_Send();
}
#else
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXMET1S05_Send(void)
{
}
#endif

#if defined(CXPICDD_FRM_0_CH0_CXMET1S06_INDEX) && \
   (defined(ComConf_ComSignal_ADIM)     || defined(ComConf_ComSignal_HEDH)     || defined(ComConf_ComSignal_HEDL) || \
    defined(ComConf_ComSignal_TAIL)     || defined(ComConf_ComSignal_FFOG)     || defined(ComConf_ComSignal_RFOG) || \
    defined(ComConf_ComSignal_CONLT_PR) || defined(ComConf_ComSignal_BW_SW_PR) || defined(ComConf_ComSignal_AUTOINT))
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXMET1S06_Send(void)
{
    vd_s_GwcxCfg_ADIM_Send();
    vd_s_GwcxCfg_HEDH_Send();
    vd_s_GwcxCfg_HEDL_Send();
    vd_s_GwcxCfg_TAIL06_Send();
    vd_s_GwcxCfg_FFOG_Send();
    vd_s_GwcxCfg_RFOG_Send();
    vd_s_GwcxCfg_CONLT_PR_Send();
    vd_s_GwcxCfg_BW_SW_PR_Send();
    vd_s_GwcxCfg_AUTINT_Send();

#if 0   /* BEV BSW provisionally */
    vd_g_oXCANCxptxTrgrTx((U1)CXPICDD_FRM_0_CH0_CXMET1S06_INDEX);
#endif
}
#elif defined(CXPICDD_FRM_0_CH0_CXMET1S06_INDEX)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXMET1S06_Send(void)
{
    vd_s_GwcxCfg_ADIM_Send();
    vd_s_GwcxCfg_HEDH_Send();
    vd_s_GwcxCfg_HEDL_Send();
    vd_s_GwcxCfg_TAIL06_Send();
    vd_s_GwcxCfg_FFOG_Send();
    vd_s_GwcxCfg_RFOG_Send();
    vd_s_GwcxCfg_CONLT_PR_Send();
    vd_s_GwcxCfg_BW_SW_PR_Send();
    vd_s_GwcxCfg_AUTINT_Send();
}
#else
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CXMET1S06_Send(void)
{
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s01RHEOSTAT) && defined(ComConf_ComSignal_RHEOSTAT)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_RHEOSTAT_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s01RHEOSTAT(u1_s_gwcxcfg_rheostat);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s01RHEOSTAT)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_RHEOSTAT_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s01RHEOSTAT((U1)0);
}
#else
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_RHEOSTAT_Send(void)
{
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s03VIBTOFFG) && defined(ComConf_ComSignal_VIBTOFFG)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_VIBTOFFG_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s03VIBTOFFG(u1_s_gwcxcfg_vibtoffg);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s03VIBTOFFG)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_VIBTOFFG_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s03VIBTOFFG((U1)GWCXCFG_STGVIB_MOTOR_OFF_UNUSED_0);
}
#else
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_VIBTOFFG_Send(void)
{
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s03VIBSTRG) && defined(ComConf_ComSignal_VIBSTRG)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_VIBSTRG_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s03VIBSTRG(u1_s_gwcxcfg_vibstrg);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s03VIBSTRG)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_VIBSTRG_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s03VIBSTRG((U1)GWCXCFG_STGVIB_VIBSTR_UNUSED_0);
}
#else
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_VIBSTRG_Send(void)
{
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s03VIBTONG) && defined(ComConf_ComSignal_VIBTONG)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_VIBTONG_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s03VIBTONG(u1_s_gwcxcfg_vibtong);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s03VIBTONG)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_VIBTONG_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s03VIBTONG((U1)GWCXCFG_STGVIB_MOTOR_ON_UNUSED_0);
}
#else
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_VIBTONG_Send(void)
{
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s04O_STG_F) && defined(ComConf_ComSignal_O_STG_F)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_O_STG_F_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s04O_STG_F(u1_s_gwcxcfg_ostgf);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s04O_STG_F)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_O_STG_F_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s04O_STG_F((U1)GWCXCFG_STGHTR_OFF);
}
#else
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_O_STG_F_Send(void)
{
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s05T_LOGI) && defined(GATEWAY_CXPICFG_T_LOGI_SUP)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_T_LOGI_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s05T_LOGI(u1_s_gwcxcfg_t_logi);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s05T_LOGI)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_T_LOGI_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s05T_LOGI((U1)GWCXCFG_T_LOGI_NOLOGIC);
}
#else
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_T_LOGI_Send(void)
{
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s05EL_SENS) && defined(GATEWAY_CXPICFG_EL_SENS_SUP)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_EL_SENS_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s05EL_SENS(u1_s_gwcxcfg_el_sens);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s05EL_SENS)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_EL_SENS_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s05EL_SENS((U1)GWCXCFG_EL_SENS_NORMAL);
}
#else
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_EL_SENS_Send(void)
{
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s06ADIM) && defined(ComConf_ComSignal_ADIM)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_ADIM_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s06ADIM(u1_s_gwcxcfg_adim);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s06ADIM)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_ADIM_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s06ADIM((U1)GWCXCFG_ADIM_UNDET);
}
#else
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_ADIM_Send(void)
{
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s06HEDH) && defined(ComConf_ComSignal_HEDH)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_HEDH_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s06HEDH(u1_s_gwcxcfg_hedh);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s06HEDH)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_HEDH_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s06HEDH((U1)GWCXCFG_HEDH_OFF);
}
#else
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_HEDH_Send(void)
{
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s06HEDL) && defined(ComConf_ComSignal_HEDL)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_HEDL_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s06HEDL(u1_s_gwcxcfg_hedl);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s06HEDL)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_HEDL_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s06HEDL((U1)GWCXCFG_HEDL_OFF);
}
#else
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_HEDL_Send(void)
{
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s06TAIL) && defined(ComConf_ComSignal_TAIL)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_TAIL06_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s06TAIL(u1_s_gwcxcfg_tail_cxmet1s06);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s06TAIL)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_TAIL06_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s06TAIL((U1)GWCXCFG_TAIL_OFF);
}
#else
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_TAIL06_Send(void)
{
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s06FFOG) && defined(ComConf_ComSignal_FFOG)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_FFOG_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s06FFOG(u1_s_gwcxcfg_ffog);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s06FFOG)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_FFOG_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s06FFOG((U1)GWCXCFG_FFOG_OFF);
}
#else
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_FFOG_Send(void)
{
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s06RFOG) && defined(ComConf_ComSignal_RFOG)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_RFOG_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s06RFOG(u1_s_gwcxcfg_rfog);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s06RFOG)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_RFOG_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s06RFOG((U1)GWCXCFG_RFOG_OFF);
}
#else
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_RFOG_Send(void)
{
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s06CONLT_PR) && defined(ComConf_ComSignal_CONLT_PR)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CONLT_PR_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s06CONLT_PR(u1_s_gwcxcfg_conlt_pr);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s06CONLT_PR)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CONLT_PR_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s06CONLT_PR((U1)GWCXCFG_CONLT_PR_NOSEND);
}
#else
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_CONLT_PR_Send(void)
{
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s06BW_SW_PR) && defined(ComConf_ComSignal_BW_SW_PR)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_BW_SW_PR_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s06BW_SW_PR(u1_s_gwcxcfg_bw_sw_pr);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s06BW_SW_PR)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_BW_SW_PR_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s06BW_SW_PR((U1)GWCXCFG_BW_SW_PR_NOSEND);
}
#else
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_BW_SW_PR_Send(void)
{
}
#endif

#if defined(CxpiCdd_TsWr0Cxmet1s06AUTINT) && defined(ComConf_ComSignal_AUTOINT)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_AUTINT_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s06AUTINT(u1_s_gwcxcfg_autint);
}
#elif defined(CxpiCdd_TsWr0Cxmet1s06AUTINT)
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_AUTINT_Send(void)
{
    CxpiCdd_TsWr0Cxmet1s06AUTINT((U1)GWCXCFG_AUTINT_NOSEND);
}
#else
/*===================================================================================================================================*/
/*  Send data to CXPI                                                                                                                */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static void vd_s_GwcxCfg_AUTINT_Send(void)
{
}
#endif

#if defined(MSG_CMB1S05_TXCH0)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    u1_t_ret : Event Send Flag                                                                                            */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_CMB1S05_SetData(const U1  u1_a_PWRSTS)
{
    U1 u1_t_msgsts;         /*  Receive Status             */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S05);
    u1_t_msgsts = u1_s_GwcxCfg_CXCMB1S05_Msgsts();

    if(u1_t_supd == (U1)TRUE){
        u1_t_ret = u1_s_GwcxCfg_MsgRcvFirst(u1_s_cxcmb1s05_cxpsts_old, u1_t_msgsts);
        u1_s_cxcmb1s05_cxpsts_old = u1_t_msgsts & (U1)COM_NO_RX;
    }
    else{
        u1_s_cxcmb1s05_cxpsts_old = (U1)COM_NO_RX;
    }

    u1_t_ret |= u1_s_GwcxCfg_LMTS_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_HED_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_TAL_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_DRL_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_AUT_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_OFF_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_AHB_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_PAS_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_HIB_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_BW_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_RFG_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_FOG_S2_Send(u1_a_PWRSTS, u1_t_msgsts);

    return(u1_t_ret);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    u1_t_ret : Event Send Flag                                                                                            */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_CMB1S05_SetData(const U1  u1_a_PWRSTS)
{
    return((U1)FALSE);
}
#endif


#if defined(MSG_CMB1S06_TXCH0)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    u1_t_ret : Event Send Flag                                                                                            */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_CMB1S06_SetData(const U1  u1_a_PWRSTS)
{
    U1 u1_t_msgsts;         /*  Receive Status             */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S06);
    u1_t_msgsts = u1_s_GwcxCfg_CXCMB1S06_Msgsts();

    if(u1_t_supd == (U1)TRUE){
        u1_t_ret = u1_s_GwcxCfg_MsgRcvFirst(u1_s_cxcmb1s06_cxpsts_old, u1_t_msgsts);
        u1_s_cxcmb1s06_cxpsts_old = u1_t_msgsts & (U1)COM_NO_RX;
    }
    else{
        u1_s_cxcmb1s06_cxpsts_old = (U1)COM_NO_RX;
    }

    u1_t_ret |= u1_s_GwcxCfg_LMWS_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_WVR_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_WSW_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_WRSW_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_WRON_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_WRIN_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_WINT_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_WMST_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_WA_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_WHI_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_WLO_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_WOFF_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_WAMC_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_WAI_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_MOFF_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_MN_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_MAUTO_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_MWPDN_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_MWPUP_S2_Send(u1_a_PWRSTS, u1_t_msgsts);
    u1_t_ret |= u1_s_GwcxCfg_MHI_S2_Send(u1_a_PWRSTS, u1_t_msgsts);

    return(u1_t_ret);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: -                                                                                                                     */
/*  Return:    u1_t_ret : Event Send Flag                                                                                            */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_CMB1S06_SetData(const U1  u1_a_PWRSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_LMTS_S2) && defined(CxpiCdd_RsRd0Cxcmb1s05LMTS)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_LMTS_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Lmts_s2;     /*  Signal LMTS_S2             */
    U1 u1_t_supd;           /*  Variation Support          */

    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S05);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpTerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_Lmts_s2 = CxpiCdd_RsRd0Cxcmb1s05LMTS();
        }
        else{
            u1_t_tx_Lmts_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        }
    }
    else{
        u1_t_tx_Lmts_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
    }
    
    (void)Com_SendSignal(ComConf_ComSignal_LMTS_S2, (&u1_t_tx_Lmts_s2));
    
    return((U1)FALSE);
}
#elif defined(ComConf_ComSignal_LMTS_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_LMTS_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Lmts_s2;     /*  Signal LMTS_S2             */

    u1_t_tx_Lmts_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_LMTS_S2, (&u1_t_tx_Lmts_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_LMTS_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_HED_S2) && defined(CxpiCdd_RsRd0Cxcmb1s05HED)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_HED_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_hed_s2;      /*  Signal HED_S2              */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S05);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpTerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_hed_s2           = CxpiCdd_RsRd0Cxcmb1s05HED();
            u1_s_gwcxcfg_hed_s2_last = u1_t_tx_hed_s2;
        }
        else{
            u1_t_tx_hed_s2 = u1_s_gwcxcfg_hed_s2_last;
        }
    }
    else{
        u1_t_tx_hed_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        u1_s_gwcxcfg_hed_s2_last = u1_t_tx_hed_s2;
    }
    
    (void)Com_SendSignal(ComConf_ComSignal_HED_S2, (&u1_t_tx_hed_s2));
    
    if(u1_s_gwcxcfg_hed_s2_old != u1_t_tx_hed_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_hed_s2_old = u1_t_tx_hed_s2;

    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_HED_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_HED_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_hed_s2;      /*  Signal HED_S2              */

    u1_t_tx_hed_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_HED_S2, (&u1_t_tx_hed_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_HED_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_TAL_S2) && defined(CxpiCdd_RsRd0Cxcmb1s05TAL)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_TAL_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_tal_s2;      /*  Signal TAL_S2              */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S05);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpTerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_tal_s2           = CxpiCdd_RsRd0Cxcmb1s05TAL();
            u1_s_gwcxcfg_tal_s2_last = u1_t_tx_tal_s2;
        }
        else{
            u1_t_tx_tal_s2 = u1_s_gwcxcfg_tal_s2_last;
        }
    }
    else{
        u1_t_tx_tal_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        u1_s_gwcxcfg_tal_s2_last = u1_t_tx_tal_s2;
    }
    
    (void)Com_SendSignal(ComConf_ComSignal_TAL_S2, (&u1_t_tx_tal_s2));
    
    if(u1_s_gwcxcfg_tal_s2_old != u1_t_tx_tal_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_tal_s2_old = u1_t_tx_tal_s2;

    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_TAL_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_TAL_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_tal_s2;      /*  Signal TAL_S2              */

    u1_t_tx_tal_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_TAL_S2, (&u1_t_tx_tal_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_TAL_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_DRL_S2) && defined(CxpiCdd_RsRd0Cxcmb1s05DRL)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_DRL_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_drl_s2;      /*  Signal DRL_S2              */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S05);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpTerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_drl_s2           = CxpiCdd_RsRd0Cxcmb1s05DRL();
            u1_s_gwcxcfg_drl_s2_last = u1_t_tx_drl_s2;
        }
        else{
            u1_t_tx_drl_s2 = u1_s_gwcxcfg_drl_s2_last;
        }
    }
    else{
        u1_t_tx_drl_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        u1_s_gwcxcfg_drl_s2_last = u1_t_tx_drl_s2;
    }
    
    (void)Com_SendSignal(ComConf_ComSignal_DRL_S2, (&u1_t_tx_drl_s2));
    
    if(u1_s_gwcxcfg_drl_s2_old != u1_t_tx_drl_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_drl_s2_old = u1_t_tx_drl_s2;

    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_DRL_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_DRL_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_drl_s2;      /*  Signal DRL_S2              */

    u1_t_tx_drl_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_DRL_S2, (&u1_t_tx_drl_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_DRL_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_AUT_S2) && defined(CxpiCdd_RsRd0Cxcmb1s05AUT)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_AUT_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_aut_s2;      /*  Signal AUT_S2              */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S05);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpTerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_aut_s2           = CxpiCdd_RsRd0Cxcmb1s05AUT();
            u1_s_gwcxcfg_aut_s2_last = u1_t_tx_aut_s2;
        }
        else{
            u1_t_tx_aut_s2 = u1_s_gwcxcfg_aut_s2_last;
        }
    }
    else{
        u1_t_tx_aut_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        u1_s_gwcxcfg_aut_s2_last = u1_t_tx_aut_s2;
    }
    
    (void)Com_SendSignal(ComConf_ComSignal_AUT_S2, (&u1_t_tx_aut_s2));
    
    if(u1_s_gwcxcfg_aut_s2_old != u1_t_tx_aut_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_aut_s2_old = u1_t_tx_aut_s2;

    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_AUT_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_AUT_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_aut_s2;      /*  Signal AUT_S2              */

    u1_t_tx_aut_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_AUT_S2, (&u1_t_tx_aut_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_AUT_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_OFF_S2) && defined(CxpiCdd_RsRd0Cxcmb1s05OFF)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_OFF_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_off_s2;      /*  Signal OFF_S2              */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S05);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpTerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_off_s2           = CxpiCdd_RsRd0Cxcmb1s05OFF();
            u1_s_gwcxcfg_off_s2_last = u1_t_tx_off_s2;
        }
        else{
            u1_t_tx_off_s2 = u1_s_gwcxcfg_off_s2_last;
        }
    }
    else{
        u1_t_tx_off_s2 = (U1)GWCXCFG_STGSWSTAT_ON;
        u1_s_gwcxcfg_off_s2_last = u1_t_tx_off_s2;
    }
    
    (void)Com_SendSignal(ComConf_ComSignal_OFF_S2, (&u1_t_tx_off_s2));
    
    if(u1_s_gwcxcfg_off_s2_old != u1_t_tx_off_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_off_s2_old = u1_t_tx_off_s2;

    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_OFF_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_OFF_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_off_s2;      /*  Signal OFF_S2              */

    u1_t_tx_off_s2 = (U1)GWCXCFG_STGSWSTAT_ON;

    (void)Com_SendSignal(ComConf_ComSignal_OFF_S2, (&u1_t_tx_off_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_OFF_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_AHB_S2) && defined(CxpiCdd_RsRd0Cxcmb1s05AHB)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_AHB_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_ahb_s2;      /*  Signal AHB_S2              */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S05);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpTerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_ahb_s2           = CxpiCdd_RsRd0Cxcmb1s05AHB();
            u1_s_gwcxcfg_ahb_s2_last = u1_t_tx_ahb_s2;
        }
        else{
            u1_t_tx_ahb_s2 = u1_s_gwcxcfg_ahb_s2_last;
        }
    }
    else{
        u1_t_tx_ahb_s2  = (U1)GWCXCFG_STGSWSTAT_OFF;
        u1_s_gwcxcfg_ahb_s2_last = u1_t_tx_ahb_s2;
    }
    
    (void)Com_SendSignal(ComConf_ComSignal_AHB_S2, (&u1_t_tx_ahb_s2));
    
    if(u1_s_gwcxcfg_ahb_s2_old != u1_t_tx_ahb_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_ahb_s2_old = u1_t_tx_ahb_s2;

    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_AHB_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_AHB_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_ahb_s2;      /*  Signal AHB_S2              */

    u1_t_tx_ahb_s2  = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_AHB_S2, (&u1_t_tx_ahb_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_AHB_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_PAS_S2) && defined(CxpiCdd_RsRd0Cxcmb1s05PAS)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_PAS_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_pas_s2;      /*  Signal PAS_S2              */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S05);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpTerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_pas_s2           = CxpiCdd_RsRd0Cxcmb1s05PAS();
            u1_s_gwcxcfg_pas_s2_last = u1_t_tx_pas_s2;
        }
        else{
            u1_t_tx_pas_s2 = u1_s_gwcxcfg_pas_s2_last;
        }
    }
    else{
        u1_t_tx_pas_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        u1_s_gwcxcfg_pas_s2_last = u1_t_tx_pas_s2;
    }
    
    (void)Com_SendSignal(ComConf_ComSignal_PAS_S2, (&u1_t_tx_pas_s2));
    
    if(u1_s_gwcxcfg_pas_s2_old != u1_t_tx_pas_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_pas_s2_old = u1_t_tx_pas_s2;

    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_PAS_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_PAS_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_pas_s2;      /*  Signal PAS_S2              */

    u1_t_tx_pas_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_PAS_S2, (&u1_t_tx_pas_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_PAS_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_HIB_S2) && defined(CxpiCdd_RsRd0Cxcmb1s05HIB)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_HIB_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_hib_s2;      /*  Signal HIB_S2              */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S05);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpTerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_hib_s2           = CxpiCdd_RsRd0Cxcmb1s05HIB();
            u1_s_gwcxcfg_hib_s2_last = u1_t_tx_hib_s2;
        }
        else{
            u1_t_tx_hib_s2 = u1_s_gwcxcfg_hib_s2_last;
        }
    }
    else{
        u1_t_tx_hib_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        u1_s_gwcxcfg_hib_s2_last = u1_t_tx_hib_s2;
    }
    
    (void)Com_SendSignal(ComConf_ComSignal_HIB_S2, (&u1_t_tx_hib_s2));
    
    if(u1_s_gwcxcfg_hib_s2_old != u1_t_tx_hib_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_hib_s2_old = u1_t_tx_hib_s2;

    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_HIB_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_HIB_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_hib_s2;      /*  Signal HIB_S2              */

    u1_t_tx_hib_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_HIB_S2, (&u1_t_tx_hib_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_HIB_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_BW_S2) && defined(CxpiCdd_RsRd0Cxcmb1s05BW)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_BW_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_bw_s2;       /*  Signal BW_S2               */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S05);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpTerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_bw_s2           = CxpiCdd_RsRd0Cxcmb1s05BW();
            u1_s_gwcxcfg_bw_s2_last = u1_t_tx_bw_s2;
        }
        else{
            u1_t_tx_bw_s2 = u1_s_gwcxcfg_bw_s2_last;
        }
    }
    else{
        u1_t_tx_bw_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        u1_s_gwcxcfg_bw_s2_last = u1_t_tx_bw_s2;
    }
    
    (void)Com_SendSignal(ComConf_ComSignal_BW_S2, (&u1_t_tx_bw_s2));
    
    if(u1_s_gwcxcfg_bw_s2_old != u1_t_tx_bw_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_bw_s2_old = u1_t_tx_bw_s2;

    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_BW_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_BW_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_bw_s2;       /*  Signal BW_S2               */

    u1_t_tx_bw_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_BW_S2, (&u1_t_tx_bw_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_BW_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_RFG_S2) && defined(CxpiCdd_RsRd0Cxcmb1s05RFG)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_RFG_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_rfg_s2;      /*  Signal RFG_S2              */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S05);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpTerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_rfg_s2           = CxpiCdd_RsRd0Cxcmb1s05RFG();
            u1_s_gwcxcfg_rfg_s2_last = u1_t_tx_rfg_s2;
        }
        else{
            u1_t_tx_rfg_s2  = u1_s_gwcxcfg_rfg_s2_last;
        }
    }
    else{
        u1_t_tx_rfg_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        u1_s_gwcxcfg_rfg_s2_last = u1_t_tx_rfg_s2;
    }
    
    (void)Com_SendSignal(ComConf_ComSignal_RFG_S2, (&u1_t_tx_rfg_s2));
    
    if(u1_s_gwcxcfg_rfg_s2_old != u1_t_tx_rfg_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_rfg_s2_old = u1_t_tx_rfg_s2;

    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_RFG_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_RFG_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_rfg_s2;      /*  Signal RFG_S2              */

    u1_t_tx_rfg_s2  = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_RFG_S2, (&u1_t_tx_rfg_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_RFG_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_FOG_S2) && defined(CxpiCdd_RsRd0Cxcmb1s05FOG)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_FOG_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_fog_s2;      /*  Signal FOG_S2              */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S05);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpTerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_fog_s2           = CxpiCdd_RsRd0Cxcmb1s05FOG();
            u1_s_gwcxcfg_fog_s2_last = u1_t_tx_fog_s2;
        }
        else{
            u1_t_tx_fog_s2 = u1_s_gwcxcfg_fog_s2_last;
        }
    }
    else{
        u1_t_tx_fog_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        u1_s_gwcxcfg_fog_s2_last = u1_t_tx_fog_s2;
    }
    
    (void)Com_SendSignal(ComConf_ComSignal_FOG_S2, (&u1_t_tx_fog_s2));
    
    if(u1_s_gwcxcfg_fog_s2_old != u1_t_tx_fog_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_fog_s2_old = u1_t_tx_fog_s2;

    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_FOG_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_FOG_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_fog_s2;      /*  Signal FOG_S2              */

    u1_t_tx_fog_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_FOG_S2, (&u1_t_tx_fog_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_FOG_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_LMWS_S2) && defined(CxpiCdd_RsRd0Cxcmb1s06LMWS)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_LMWS_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Lmws_s2;     /*  Signal LMWS_S2             */
    U1 u1_t_supd;           /*  Variation Support          */

    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S06);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpWerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_Lmws_s2 = CxpiCdd_RsRd0Cxcmb1s06LMWS();
        }
        else{
            u1_t_tx_Lmws_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        }
    }
    else{
        u1_t_tx_Lmws_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_LMWS_S2, (&u1_t_tx_Lmws_s2));
    
    return((U1)FALSE);
}
#elif defined(ComConf_ComSignal_LMWS_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_LMWS_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Lmws_s2;     /*  Signal LMWS_S2             */

    u1_t_tx_Lmws_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_LMWS_S2, (&u1_t_tx_Lmws_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_LMWS_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_WVR_S2) && defined(CxpiCdd_RsRd0Cxcmb1s06WVR)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WVR_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Wvr_s2;      /*  Signal WVR_S2              */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S06);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpWerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_Wvr_s2           = CxpiCdd_RsRd0Cxcmb1s06WVR();
            u1_s_gwcxcfg_wvr_s2_last = u1_t_tx_Wvr_s2;
        }
        else{
            u1_t_tx_Wvr_s2 = u1_s_gwcxcfg_wvr_s2_last;
        }
    }
    else{
        u1_t_tx_Wvr_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        u1_s_gwcxcfg_wvr_s2_last = u1_t_tx_Wvr_s2;
    }

    (void)Com_SendSignal(ComConf_ComSignal_WVR_S2, (&u1_t_tx_Wvr_s2));

    if(u1_s_gwcxcfg_wvr_s2_old != u1_t_tx_Wvr_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_wvr_s2_old = u1_t_tx_Wvr_s2;
    
    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_WVR_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WVR_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Wvr_s2;      /*  Signal WVR_S2              */

    u1_t_tx_Wvr_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_WVR_S2, (&u1_t_tx_Wvr_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WVR_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_WSW_S2) && defined(CxpiCdd_RsRd0Cxcmb1s06WSW)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WSW_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Wsw_s2;      /*  Signal WSW_S2              */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S06);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpWerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_Wsw_s2           = CxpiCdd_RsRd0Cxcmb1s06WSW();
            u1_s_gwcxcfg_wsw_s2_last = u1_t_tx_Wsw_s2;
        }
        else{
            u1_t_tx_Wsw_s2 = u1_s_gwcxcfg_wsw_s2_last;
        }
    }
    else{
        u1_t_tx_Wsw_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        u1_s_gwcxcfg_wsw_s2_last = u1_t_tx_Wsw_s2;
    }

    (void)Com_SendSignal(ComConf_ComSignal_WSW_S2, (&u1_t_tx_Wsw_s2));

    if(u1_s_gwcxcfg_wsw_s2_old != u1_t_tx_Wsw_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_wsw_s2_old = u1_t_tx_Wsw_s2;
    
    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_WSW_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WSW_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Wsw_s2;      /*  Signal WSW_S2              */

    u1_t_tx_Wsw_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_WSW_S2, (&u1_t_tx_Wsw_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WSW_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_WRSW_S2) && defined(CxpiCdd_RsRd0Cxcmb1s06WRSW)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WRSW_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Wrsw_s2;     /*  Signal WRSW_S2             */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S06);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpWerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_Wrsw_s2           = CxpiCdd_RsRd0Cxcmb1s06WRSW();
            u1_s_gwcxcfg_wrsw_s2_last = u1_t_tx_Wrsw_s2;
        }
        else{
            u1_t_tx_Wrsw_s2 = u1_s_gwcxcfg_wrsw_s2_last;
        }
    }
    else{
        u1_t_tx_Wrsw_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        u1_s_gwcxcfg_wrsw_s2_last = u1_t_tx_Wrsw_s2;
    }

    (void)Com_SendSignal(ComConf_ComSignal_WRSW_S2, (&u1_t_tx_Wrsw_s2));

    if(u1_s_gwcxcfg_wrsw_s2_old != u1_t_tx_Wrsw_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_wrsw_s2_old = u1_t_tx_Wrsw_s2;
    
    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_WRSW_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WRSW_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Wrsw_s2;     /*  Signal WRSW_S2             */

    u1_t_tx_Wrsw_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_WRSW_S2, (&u1_t_tx_Wrsw_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WRSW_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_WRON_S2) && defined(CxpiCdd_RsRd0Cxcmb1s06WRON)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WRON_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Wron_s2;     /*  Signal WRON_S2             */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S06);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpWerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_Wron_s2           = CxpiCdd_RsRd0Cxcmb1s06WRON();
            u1_s_gwcxcfg_wron_s2_last = u1_t_tx_Wron_s2;
        }
        else{
            u1_t_tx_Wron_s2 = u1_s_gwcxcfg_wron_s2_last;
        }
    }
    else{
        u1_t_tx_Wron_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        u1_s_gwcxcfg_wron_s2_last = u1_t_tx_Wron_s2;
    }

    (void)Com_SendSignal(ComConf_ComSignal_WRON_S2, (&u1_t_tx_Wron_s2));

    if(u1_s_gwcxcfg_wron_s2_old != u1_t_tx_Wron_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_wron_s2_old = u1_t_tx_Wron_s2;
    
    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_WRON_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WRON_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Wron_s2;     /*  Signal WRON_S2             */

    u1_t_tx_Wron_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_WRON_S2, (&u1_t_tx_Wron_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WRON_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_WRIN_S2) && defined(CxpiCdd_RsRd0Cxcmb1s06WRIN)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WRIN_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Wrin_s2;     /*  Signal WRIN_S2             */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S06);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpWerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_Wrin_s2           = CxpiCdd_RsRd0Cxcmb1s06WRIN();
            u1_s_gwcxcfg_wrin_s2_last = u1_t_tx_Wrin_s2;
        }
        else{
            u1_t_tx_Wrin_s2 = u1_s_gwcxcfg_wrin_s2_last;
        }
    }
    else{
        u1_t_tx_Wrin_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        u1_s_gwcxcfg_wrin_s2_last = u1_t_tx_Wrin_s2;
    }

    (void)Com_SendSignal(ComConf_ComSignal_WRIN_S2, (&u1_t_tx_Wrin_s2));

    if(u1_s_gwcxcfg_wrin_s2_old != u1_t_tx_Wrin_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_wrin_s2_old = u1_t_tx_Wrin_s2;
    
    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_WRIN_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WRIN_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Wrin_s2;     /*  Signal WRIN_S2             */

    u1_t_tx_Wrin_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_WRIN_S2, (&u1_t_tx_Wrin_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WRIN_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_WINT_S2) && defined(CxpiCdd_RsRd0Cxcmb1s06WINT)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WINT_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Wint_s2;     /*  Signal WINT_S2             */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S06);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpWerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_Wint_s2           = CxpiCdd_RsRd0Cxcmb1s06WINT();
            u1_s_gwcxcfg_wint_s2_last = u1_t_tx_Wint_s2;
        }
        else{
            u1_t_tx_Wint_s2 = u1_s_gwcxcfg_wint_s2_last;
        }
    }
    else{
        u1_t_tx_Wint_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        u1_s_gwcxcfg_wint_s2_last = u1_t_tx_Wint_s2;
    }

    (void)Com_SendSignal(ComConf_ComSignal_WINT_S2, (&u1_t_tx_Wint_s2));

    if(u1_s_gwcxcfg_wint_s2_old != u1_t_tx_Wint_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_wint_s2_old = u1_t_tx_Wint_s2;
    
    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_WINT_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WINT_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Wint_s2;     /*  Signal WINT_S2             */

    u1_t_tx_Wint_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_WINT_S2, (&u1_t_tx_Wint_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WINT_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_WMST_S2) && defined(CxpiCdd_RsRd0Cxcmb1s06WMST)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WMST_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Wmst_s2;     /*  Signal WMST_S2             */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S06);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpWerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_Wmst_s2           = CxpiCdd_RsRd0Cxcmb1s06WMST();
            u1_s_gwcxcfg_wmst_s2_last = u1_t_tx_Wmst_s2;
        }
        else{
            u1_t_tx_Wmst_s2 = u1_s_gwcxcfg_wmst_s2_last;
        }
    }
    else{
        u1_t_tx_Wmst_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        u1_s_gwcxcfg_wmst_s2_last = u1_t_tx_Wmst_s2;
    }

    (void)Com_SendSignal(ComConf_ComSignal_WMST_S2, (&u1_t_tx_Wmst_s2));

    if(u1_s_gwcxcfg_wmst_s2_old != u1_t_tx_Wmst_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_wmst_s2_old = u1_t_tx_Wmst_s2;
    
    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_WMST_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WMST_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Wmst_s2;     /*  Signal WMST_S2             */

    u1_t_tx_Wmst_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_WMST_S2, (&u1_t_tx_Wmst_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WMST_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_WA_S2) && defined(CxpiCdd_RsRd0Cxcmb1s06WA)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WA_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Wa_s2;       /*  Signal WA_S2               */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S06);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpWerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_Wa_s2           = CxpiCdd_RsRd0Cxcmb1s06WA();
            u1_s_gwcxcfg_wa_s2_last = u1_t_tx_Wa_s2;
        }
        else{
            u1_t_tx_Wa_s2 = u1_s_gwcxcfg_wa_s2_last;
        }
    }
    else{
        u1_t_tx_Wa_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        u1_s_gwcxcfg_wa_s2_last = u1_t_tx_Wa_s2;
    }

    (void)Com_SendSignal(ComConf_ComSignal_WA_S2, (&u1_t_tx_Wa_s2));

    if(u1_s_gwcxcfg_wa_s2_old != u1_t_tx_Wa_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_wa_s2_old = u1_t_tx_Wa_s2;
    
    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_WA_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WA_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Wa_s2;       /*  Signal WA_S2               */

    u1_t_tx_Wa_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_WA_S2, (&u1_t_tx_Wa_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WA_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_WHI_S2) && defined(CxpiCdd_RsRd0Cxcmb1s06WHI)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WHI_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Whi_s2;      /*  Signal WHI_S2              */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S06);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpWerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_Whi_s2           = CxpiCdd_RsRd0Cxcmb1s06WHI();
            u1_s_gwcxcfg_whi_s2_last = u1_t_tx_Whi_s2;
        }
        else{
            u1_t_tx_Whi_s2 = u1_s_gwcxcfg_whi_s2_last;
        }
    }
    else{
        u1_t_tx_Whi_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        u1_s_gwcxcfg_whi_s2_last = u1_t_tx_Whi_s2;
    }

    (void)Com_SendSignal(ComConf_ComSignal_WHI_S2, (&u1_t_tx_Whi_s2));

    if(u1_s_gwcxcfg_whi_s2_old != u1_t_tx_Whi_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_whi_s2_old = u1_t_tx_Whi_s2;
    
    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_WHI_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WHI_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Whi_s2;      /*  Signal WHI_S2              */

    u1_t_tx_Whi_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_WHI_S2, (&u1_t_tx_Whi_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WHI_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_WLO_S2) && defined(CxpiCdd_RsRd0Cxcmb1s06WLO)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WLO_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Wlo_s2;      /*  Signal WLO_S2              */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S06);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpWerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_Wlo_s2           = CxpiCdd_RsRd0Cxcmb1s06WLO();
            u1_s_gwcxcfg_wlo_s2_last = u1_t_tx_Wlo_s2;
        }
        else{
            u1_t_tx_Wlo_s2 = u1_s_gwcxcfg_wlo_s2_last;
        }
    }
    else{
        u1_t_tx_Wlo_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        u1_s_gwcxcfg_wlo_s2_last = u1_t_tx_Wlo_s2;
    }

    (void)Com_SendSignal(ComConf_ComSignal_WLO_S2, (&u1_t_tx_Wlo_s2));

    if(u1_s_gwcxcfg_wlo_s2_old != u1_t_tx_Wlo_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_wlo_s2_old = u1_t_tx_Wlo_s2;
    
    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_WLO_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WLO_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Wlo_s2;      /*  Signal WLO_S2              */

    u1_t_tx_Wlo_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_WLO_S2, (&u1_t_tx_Wlo_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WLO_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_WOFF_S2) && defined(CxpiCdd_RsRd0Cxcmb1s06WOFF)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WOFF_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Woff_s2;     /*  Signal WOFF_S2             */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S06);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpWerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_Woff_s2           = CxpiCdd_RsRd0Cxcmb1s06WOFF();
            u1_s_gwcxcfg_woff_s2_last = u1_t_tx_Woff_s2;
        }
        else{
            u1_t_tx_Woff_s2 = u1_s_gwcxcfg_woff_s2_last;
        }
    }
    else{
        u1_t_tx_Woff_s2 = (U1)GWCXCFG_STGSWSTAT_ON;
        u1_s_gwcxcfg_woff_s2_last = u1_t_tx_Woff_s2;
    }

    (void)Com_SendSignal(ComConf_ComSignal_WOFF_S2, (&u1_t_tx_Woff_s2));

    if(u1_s_gwcxcfg_woff_s2_old != u1_t_tx_Woff_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_woff_s2_old = u1_t_tx_Woff_s2;
    
    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_WOFF_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WOFF_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Woff_s2;     /*  Signal WOFF_S2             */

    u1_t_tx_Woff_s2 = (U1)GWCXCFG_STGSWSTAT_ON;

    (void)Com_SendSignal(ComConf_ComSignal_WOFF_S2, (&u1_t_tx_Woff_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WOFF_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_WAMC_S2) && defined(CxpiCdd_RsRd0Cxcmb1s06WAMC)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WAMC_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Wamc_s2;     /*  Signal WAMC_S2             */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S06);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpWerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_Wamc_s2 = CxpiCdd_RsRd0Cxcmb1s06WAMC();
        }
        else{
            u1_t_tx_Wamc_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        }
    }
    else{
        u1_t_tx_Wamc_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_WAMC_S2, (&u1_t_tx_Wamc_s2));

    if(u1_s_gwcxcfg_wamc_s2_old != u1_t_tx_Wamc_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_wamc_s2_old = u1_t_tx_Wamc_s2;
    
    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_WAMC_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WAMC_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Wamc_s2;     /*  Signal WAMC_S2             */

    u1_t_tx_Wamc_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_WAMC_S2, (&u1_t_tx_Wamc_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WAMC_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_WAI_S2) && defined(CxpiCdd_RsRd0Cxcmb1s06WAI)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WAI_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Wai_s2;      /*  Signal WAI_S2              */
    U1 u1_t_supd;           /*  Variation Support          */

    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S06);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpWerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_Wai_s2 = CxpiCdd_RsRd0Cxcmb1s06WAI();
        }
        else{
            u1_t_tx_Wai_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        }
    }
    else{
        u1_t_tx_Wai_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_WAI_S2, (&u1_t_tx_Wai_s2));

    
    return((U1)FALSE);
}
#elif defined(ComConf_ComSignal_WAI_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WAI_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Wai_s2;      /*  Signal WAI_S2              */

    u1_t_tx_Wai_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_WAI_S2, (&u1_t_tx_Wai_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_WAI_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_MOFF_S2) && defined(CxpiCdd_RsRd0Cxcmb1s06MOFF)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_MOFF_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Moff_s2;     /*  Signal MOFF_S2             */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S06);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpWerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_Moff_s2 = CxpiCdd_RsRd0Cxcmb1s06MOFF();
        }
        else{
            u1_t_tx_Moff_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        }
    }
    else{
        u1_t_tx_Moff_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_MOFF_S2, (&u1_t_tx_Moff_s2));

    if(u1_s_gwcxcfg_moff_s2_old != u1_t_tx_Moff_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_moff_s2_old = u1_t_tx_Moff_s2;
    
    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_MOFF_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_MOFF_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Moff_s2;     /*  Signal MOFF_S2             */

    u1_t_tx_Moff_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_MOFF_S2, (&u1_t_tx_Moff_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_MOFF_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_MN_S2) && defined(CxpiCdd_RsRd0Cxcmb1s06MN)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_MN_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Mn_s2;       /*  Signal MN_S2               */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S06);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpWerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_Mn_s2 = CxpiCdd_RsRd0Cxcmb1s06MN();
        }
        else{
            u1_t_tx_Mn_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        }
    }
    else{
        u1_t_tx_Mn_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_MN_S2, (&u1_t_tx_Mn_s2));

    if(u1_s_gwcxcfg_mn_s2_old != u1_t_tx_Mn_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_mn_s2_old = u1_t_tx_Mn_s2;
    
    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_MN_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_MN_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Mn_s2;       /*  Signal MN_S2               */

    u1_t_tx_Mn_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_MN_S2, (&u1_t_tx_Mn_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_MN_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_MAUTO_S2) && defined(CxpiCdd_RsRd0Cxcmb1s06MAUTO)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_MAUTO_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Mauto_s2;    /*  Signal MAUTO_S2            */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S06);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpWerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_Mauto_s2 = CxpiCdd_RsRd0Cxcmb1s06MAUTO();
        }
        else{
            u1_t_tx_Mauto_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        }
    }
    else{
        u1_t_tx_Mauto_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_MAUTO_S2, (&u1_t_tx_Mauto_s2));

    if(u1_s_gwcxcfg_mauto_s2_old != u1_t_tx_Mauto_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_mauto_s2_old = u1_t_tx_Mauto_s2;
    
    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_MAUTO_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_MAUTO_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Mauto_s2;    /*  Signal MAUTO_S2            */

    u1_t_tx_Mauto_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_MAUTO_S2, (&u1_t_tx_Mauto_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_MAUTO_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_MWPDN_S2) && defined(CxpiCdd_RsRd0Cxcmb1s06MWPDN)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_MWPDN_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Mwpdn_s2;    /*  Signal MWPDN_S2            */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S06);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpWerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_Mwpdn_s2 = CxpiCdd_RsRd0Cxcmb1s06MWPDN();
        }
        else{
            u1_t_tx_Mwpdn_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        }
    }
    else{
        u1_t_tx_Mwpdn_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_MWPDN_S2, (&u1_t_tx_Mwpdn_s2));

    if(u1_s_gwcxcfg_mwpdn_s2_old != u1_t_tx_Mwpdn_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_mwpdn_s2_old = u1_t_tx_Mwpdn_s2;
    
    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_MWPDN_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_MWPDN_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Mwpdn_s2;    /*  Signal MWPDN_S2            */

    u1_t_tx_Mwpdn_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_MWPDN_S2, (&u1_t_tx_Mwpdn_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_MWPDN_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_MWPUP_S2) && defined(CxpiCdd_RsRd0Cxcmb1s06MWPUP)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_MWPUP_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Mwpup_s2;    /*  Signal MWPUP_S2            */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S06);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpWerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_Mwpup_s2 = CxpiCdd_RsRd0Cxcmb1s06MWPUP();
        }
        else{
            u1_t_tx_Mwpup_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        }
    }
    else{
        u1_t_tx_Mwpup_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_MWPUP_S2, (&u1_t_tx_Mwpup_s2));

    if(u1_s_gwcxcfg_mwpup_s2_old != u1_t_tx_Mwpup_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_mwpup_s2_old = u1_t_tx_Mwpup_s2;
    
    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_MWPUP_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_MWPUP_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Mwpup_s2;    /*  Signal MWPUP_S2            */

    u1_t_tx_Mwpup_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_MWPUP_S2, (&u1_t_tx_Mwpup_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_MWPUP_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

#if defined(ComConf_ComSignal_MHI_S2) && defined(CxpiCdd_RsRd0Cxcmb1s06MHI)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_MHI_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Mhi_s2;      /*  Signal MHI_S2              */
    U1 u1_t_supd;           /*  Variation Support          */
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    u1_t_supd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXCMB1S06);

    if(u1_t_supd == (U1)TRUE){
        if((u1_a_MSGSTS          == (U1)0                           ) &&
           (u1_s_gwcxcfg_CxpWerr == (U1)GATEWAY_CXPICFG_CXPICOM_NORM)){
            u1_t_tx_Mhi_s2 = CxpiCdd_RsRd0Cxcmb1s06MHI();
        }
        else{
            u1_t_tx_Mhi_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
        }
    }
    else{
        u1_t_tx_Mhi_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_MHI_S2, (&u1_t_tx_Mhi_s2));

    if(u1_s_gwcxcfg_mhi_s2_old != u1_t_tx_Mhi_s2){
        u1_t_ret = (U1)TRUE;
    }

    u1_s_gwcxcfg_mhi_s2_old = u1_t_tx_Mhi_s2;
    
    return(u1_t_ret);
}
#elif defined(ComConf_ComSignal_MHI_S2)
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_MHI_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    U1 u1_t_tx_Mhi_s2;      /*  Signal MHI_S2              */

    u1_t_tx_Mhi_s2 = (U1)GWCXCFG_STGSWSTAT_OFF;

    (void)Com_SendSignal(ComConf_ComSignal_MHI_S2, (&u1_t_tx_Mhi_s2));
    
    return((U1)FALSE);
}
#else
/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_PWRSTS : Power States                                                                                            */
/*  Return:    -                                                                                                                     */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_MHI_S2_Send(const U1  u1_a_PWRSTS, const U1  u1_a_MSGSTS)
{
    return((U1)FALSE);
}
#endif

/*===================================================================================================================================*/
/*  CXPI to CAN gateway                                                                                                              */
/*  Scope : Private                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments: u1_a_MSGSTS_OLD : Message Status Old                                                                                  */
/*             u1_a_MSGSTS     : Message Status                                                                                      */
/*  Return:    u1_t_ret : Message Receive First                                                                                      */
/*===================================================================================================================================*/
static U1 u1_s_GwcxCfg_MsgRcvFirst(const U1  u1_a_MSGSTS_OLD, const U1  u1_a_MSGSTS)
{
    U1 u1_t_ret;            /*  Return                     */

    u1_t_ret = (U1)FALSE;
    if((u1_a_MSGSTS ==(U1)0) && (u1_a_MSGSTS_OLD == (U1)COM_NO_RX)){
        u1_t_ret = (U1)TRUE;
    }
    
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  -------------------------------------------------------------------------------------------  */
/*  1.0.0           2020/3/25   RS      New.                                                                                         */
/*  1.0.1           2020/10/5   RS      gateway_cxpi.c v1.0.0 -> v1.0.1                                                              */
/*                                                                                                                                   */
/*  Revision        Date        Author  Change Description                                                                           */
/* --------------- ----------  -------  -------------------------------------------------------------------------------------------- */
/*  800B-1          2020/10/5   RS      Change config for 800B CV.                                                                   */
/*  800B-2          2020/10/5   RS      Change config for 800B CV-R.                                                                 */
/*  800B-3          2020/10/27  RS      Hotfix: CXMET1S02,CXMET1S03,CXMET1S04 send Power condition delete                            */
/*  800B-4          2020/12/15  RS      Change config for 800B 1A.                                                                   */
/*  800B-5          2021/02/15  HO      Change Cxpi IF.                                                                              */
/*  178D-1          2021/11/12  RS      Change config for 178D/893B 1A.                                                              */
/*  117D-1          2022/08/24  RS      Change config for 115D/117D 1A.                                                              */
/*  200D-1          2022/11/1   RS      Change config for 115D/117D MPT.                                                             */
/*                                                                                                                                   */
/*  * RS = Ryosuke Sato, KSE                                                                                                         */
/*  * HO = Hiroaki Ogawa, KSE                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
