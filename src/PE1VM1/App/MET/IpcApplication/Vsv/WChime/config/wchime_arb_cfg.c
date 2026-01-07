/* 2.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vehicle Status Viewer / Toyota IPC/MET Warning Chime                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define WCHIME_ARB_CFG_C_MAJOR                   (2)
#define WCHIME_ARB_CFG_C_MINOR                   (1)
#define WCHIME_ARB_CFG_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "wchime_cfg_private.h"

#include "oxcan.h"
#include "alert.h"
#include "sbltsync.h"
#include "vardef.h"
#include "veh_opemd.h"

#include "sound_cri_mgr.h"
#include "thblnkr.h"
#include "vptran_sel_typ.h"

#include "wchime_grd_cfg.h"

#include "calibration.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((WCHIME_ARB_CFG_C_MAJOR != WCHIME_CFG_H_MAJOR) || \
     (WCHIME_ARB_CFG_C_MINOR != WCHIME_CFG_H_MINOR) || \
     (WCHIME_ARB_CFG_C_PATCH != WCHIME_CFG_H_PATCH))
#error "wchime_arb_cfg.c and wchime_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (WCHIME_REQBIT_NUM_WORD > WCHIME_REQBIT_NWORD_MAX)
#error "WCHIME_REQBIT_NUM_WORD shall be less than or equal to WCHIME_REQBIT_NWORD_MAX."
#endif

#define WCHIME_CNV_IDX                      (5U)                                        /* For index operation in buffers.           */
#define WCHIME_CNV_POS                      ((0x01U << WCHIME_CNV_IDX) - 1U)            /* For bit position operation in buffers.    */

#define WCHIME_RCTA_BUZZ_CH                 (WCHIME_CH_00)                              /* CH number for RCTA.                       */

#define WCHIME_BZRRQ_P_PTN1                 (1U)                                        /* RSA buzzer Constant display area 1.       */
#define WCHIME_BZRRQ_P_PTN2                 (2U)                                        /* RSA buzzer Constant display area 2.       */
#define WCHIME_BZRRQ_P_PTN3                 (3U)                                        /* RSA buzzer Constant display area 3.       */

#define WCHIME_BZRRQ_A_PTN1                 (1U)                                        /* RSA buzzer ADAS display area 1.           */
#define WCHIME_BZRRQ_A_PTN2                 (2U)                                        /* RSA buzzer ADAS display area 2.           */
#define WCHIME_BZRRQ_A_PTN3                 (3U)                                        /* RSA buzzer ADAS display area 3.           */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
ST_WCHIME_ARB_CH            st_gp_wchime_arb_ch[WCHIME_NUM_CH];                     /* Buzzer request arbitration result by channel. */

U1                          u1_g_wchime_alrt_csr_vol_old;                           /* CSR_VOL result from ALERT (OLD).              */
U1                          u1_g_wchime_alrt_csr_vol_now;                           /* CSR_VOL result from ALERT (NOW).              */

U1                          u1_gp_wchime_cyclchk[WCHIME_NUM_CH];                 /* Whether sound time is remained or not of each CH */

static U4                   u4_s_wchime_apprq_bit[WCHIME_REQBIT_NUM_WORD];          /* S_APP buzer last request bit.                 */

static U1                   u1_s_wchime_sftpos_si_last;                             /* SFTPOS single buzzer last request             */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  void    vd_s_wChimeCfgSftposRjctReqchk(U4* u4p_a_reqbit);
static  void    vd_s_wChimeCfgRctaReqchk(U4 * u4p_a_reqbit);
static  void    vd_s_wChimeCfgMcReqchk(U4 * u4p_a_reqbit);
static  void    vd_s_wChimeCfgSbltRemReqchk(U4 * u4p_a_reqbit);
static  void    vd_s_wChimeCfgTurhazReqchk(U4 * u4p_a_reqbit);
static  void    vd_s_wChimeCfgMindspDelchk(U4 * u4p_a_reqbit);
static  void    vd_s_wChimeCfgAppDelchk(U4 * u4p_a_reqbit);
static  void    vd_s_wChimeCfgBglfspdDelchk(U4 * u4p_a_reqbit);
static  void    vd_s_wChimeCfgBlgtDelchk(U4 * u4p_a_reqbit);
static  void    vd_s_wChimeCfgAppReqchk(U4 * u4p_a_reqbit);
static  void    vd_s_wChimeCfgMWVCReqchk(U4 * u4p_a_reqbit);

static  void    vd_s_wChimeCfgReqOn(U4 * u4_ap_reqbit, const U1 u1_a_REQ_ID);
static  void    vd_s_wChimeCfgReqDel(U4 * u4_ap_reqbit, const U1 u1_a_REQ_ID);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Bitmap of buzzer allocation to each channel. */
static const U4              u4_sp_WCHIME_REQBIT_CH_0[WCHIME_REQBIT_NUM_WORD] = {
    (U4)0xF8FC0FFFU,
    (U4)0xFFFFBC7FU,
    (U4)0xFFEFFFFFU,
    (U4)0xFFFFCFFFU,
    (U4)0xFFFFFFFFU,
    (U4)0x0000F81FU
};

static const U4              u4_sp_WCHIME_REQBIT_CH_1[WCHIME_REQBIT_NUM_WORD] = {
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x000007E0U
};

static const U4              u4_sp_WCHIME_REQBIT_CH_2[WCHIME_REQBIT_NUM_WORD] = {
    (U4)0x0703F000U,
    (U4)0x00000380U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U
};

static const U4              u4_sp_WCHIME_REQBIT_CH_3[WCHIME_REQBIT_NUM_WORD] = {
    (U4)0x00000000U,
    (U4)0x00004000U,
    (U4)0x00100000U,
    (U4)0x00003000U,
    (U4)0x00000000U,
    (U4)0x00000000U
};

const U4 * const             u4p_gp_WCHIME_REQBIT_BY_CH[WCHIME_NUM_CH] = {
    &u4_sp_WCHIME_REQBIT_CH_0[0],
    &u4_sp_WCHIME_REQBIT_CH_1[0],
    &u4_sp_WCHIME_REQBIT_CH_2[0],
    &u4_sp_WCHIME_REQBIT_CH_3[0]
};
const U1                     u1_g_WCHIME_NUM_CH = (U1)WCHIME_NUM_CH;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_wChimeCfgInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_wChimeCfgInit(void)
{
    U4                    u4_t_lpcnt;

    u1_g_wchime_alrt_csr_vol_old  = (U1)ALERT_REQ_UNKNOWN;
    u1_g_wchime_alrt_csr_vol_now  = (U1)ALERT_REQ_UNKNOWN;

    u1_s_wchime_sftpos_si_last    = (U1)ALERT_REQ_UNKNOWN;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_WCHIME_REQBIT_NUM_WORD; u4_t_lpcnt++){
        u4_s_wchime_apprq_bit[u4_t_lpcnt] = (U4)0U;
    }
    u1_g_wchime_silencetime_flag = (U1)FALSE;

    vd_g_wChimeGrdCfgInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_wChimeCfgPreTask(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_wChimeCfgPreTask(void)
{
}
/*===================================================================================================================================*/
/*  void    vd_g_wChimeCfgPostTask(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_wChimeCfgPostTask(void)
{
}
/*===================================================================================================================================*/
/*  void    vd_g_wChimeCfgReqchk(U4 * u4p_a_reqbit)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_wChimeCfgReqchk(U4 * u4p_a_reqbit)
{
    /* ----------------------------------------------------------------------------------------------- */
    /* Attention :                                                                                     */
    /* ----------------------------------------------------------------------------------------------- */
    /* The size of u4p_a_reqbit[] is equal to WCHIME_REQBIT_NWORD_MAX(7U).                             */
    /* u4p_a_reqbit[0] - u4p_a_reqbit[WCHIME_REQBIT_NUM_WORD - 1] is being initialized to 0x00000000U  */
    /* before vd_g_wChimeCfgReqchk is called.                                                          */
    /* ----------------------------------------------------------------------------------------------- */

    static const ST_ALERT_REQBIT   st_sp_WCHIME_ALERT_REQBIT[] = {
        {  (U2)ALERT_CH_S_ADBZR_PCS,        (U1)ALERT_REQ_S_ADBZR_PCS_NOTICE,      (U1)WCHIME_REQ_CO_PCS_TSTMD1         >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_CO_PCS_TSTMD1         & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_PCS,        (U1)ALERT_REQ_S_ADBZR_PCS_RDR_CMP,     (U1)WCHIME_REQ_IN_PCS_TSTMD5         >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_PCS_TSTMD5         & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_PCS,        (U1)ALERT_REQ_S_ADBZR_PCS_CMR_CMP,     (U1)WCHIME_REQ_IN_PCS_TSTMD6         >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_PCS_TSTMD6         & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_FRRADA_CMP, (U1)ALERT_REQ_S_ADBZR_FRRADA_CMP_CYC,  (U1)WCHIME_REQ_IN_FRRADA_CMP         >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_FRRADA_CMP         & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_FRRADA_ERR, (U1)ALERT_REQ_S_ADBZR_FRRADA_ERR_CYC,  (U1)WCHIME_REQ_IN_FRRADA_ERR         >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_FRRADA_ERR         & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_H_REASYS_BC,        (U1)ALERT_REQ_H_REASYS_BC_SINGLE,      (U1)WCHIME_REQ_SI_PTS_RDY            >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_PTS_RDY            & (U1)0x1FU)  }, /* MET-H_REASYS-CSTD-            */
        {  (U2)ALERT_CH_S_ADBZR_PCS,        (U1)ALERT_REQ_S_ADBZR_PCS_ALERT_PCS,   (U1)WCHIME_REQ_IN_PCS                >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_PCS                & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_ACC,        (U1)ALERT_REQ_S_ADBZR_ACC_WARN,        (U1)WCHIME_REQ_IN_ACC                >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_ACC                & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_C_STEER_BC,         (U1)ALERT_REQ_C_STEER_BC_CYCL_UNDRVE,  (U1)WCHIME_REQ_IN_STEER_UNDRIVE      >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_STEER_UNDRIVE      & (U1)0x1FU)  }, /* MET-C_STEER-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_LCA_VC,     (U1)ALERT_REQ_S_ADBZR_LCA_VC_CYCL,     (U1)WCHIME_REQ_IN_LCS_APR            >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_LCS_APR            & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_TEN_8,     (U1)WCHIME_REQ_IN_TMBZR_TEN_PRI8     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_TMBZR_TEN_PRI8     & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_ADBZR_SEA,        (U1)ALERT_REQ_S_ADBZR_SEA_CYCLE,       (U1)WCHIME_REQ_IN_DOA                >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_DOA                & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_CSR_BZ,     (U1)ALERT_REQ_S_ADBZR_CSR_BZ_FR_CAD,   (U1)WCHIME_REQ_CO_CSR_FR_SD          >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_CO_CSR_FR_SD          & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_CSR_BZ,     (U1)ALERT_REQ_S_ADBZR_CSR_BZ_FR_SD,    (U1)WCHIME_REQ_IN_CSR_FR_MD          >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_CSR_FR_MD          & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_CSR_BZ,     (U1)ALERT_REQ_S_ADBZR_CSR_BZ_RR_CAD,   (U1)WCHIME_REQ_CO_CSR_RR_SD          >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_CO_CSR_RR_SD          & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_CSR_BZ,     (U1)ALERT_REQ_S_ADBZR_CSR_BZ_RR_SD,    (U1)WCHIME_REQ_IN_CSR_RR_MD          >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_CSR_RR_MD          & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_CSR_BZ,     (U1)ALERT_REQ_S_ADBZR_CSR_BZ_CAD,      (U1)WCHIME_REQ_CO_CSR_FRRR_SD        >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_CO_CSR_FRRR_SD        & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_CSR_BZ,     (U1)ALERT_REQ_S_ADBZR_CSR_BZ_SD,       (U1)WCHIME_REQ_IN_CSR_FRRR_MD        >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_CSR_FRRR_MD        & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_H_SYSMAL_BC,        (U1)ALERT_REQ_H_SYSMAL_BC_CYCL1,       (U1)WCHIME_REQ_IN_SYSMAL_REMDST_0M   >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_SYSMAL_REMDST_0M   & (U1)0x1FU)  }, /* MET-H_SYSMAL-CSTD-            */
        {  (U2)ALERT_CH_S_ADBZR_TCW,        (U1)ALERT_REQ_S_ADBZR_TCW_CYCL,        (U1)WCHIME_REQ_IN_TCW_BUZ            >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_TCW_BUZ            & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_PCS,        (U1)ALERT_REQ_S_ADBZR_PCS_WRN,         (U1)WCHIME_REQ_IN_PCS_PED            >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_PCS_PED            & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_FCTA,       (U1)ALERT_REQ_S_ADBZR_FCTA_CYCL,       (U1)WCHIME_REQ_IN_FCTA_STEP_STOP     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_FCTA_STEP_STOP     & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_EDSS,       (U1)ALERT_REQ_S_ADBZR_EDSS_CYCL2,      (U1)WCHIME_REQ_IN_EDSS_R04           >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_EDSS_R04           & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_CSR_BZ,     (U1)ALERT_REQ_S_ADBZR_CSR_BZ_FR_MD,    (U1)WCHIME_REQ_IN_CSR_FR_LD          >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_CSR_FR_LD          & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_CSR_BZ,     (U1)ALERT_REQ_S_ADBZR_CSR_BZ_RR_MD,    (U1)WCHIME_REQ_IN_CSR_RR_LD          >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_CSR_RR_LD          & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_CSR_BZ,     (U1)ALERT_REQ_S_ADBZR_CSR_BZ_MD,       (U1)WCHIME_REQ_IN_CSR_FRRR_LD        >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_CSR_FRRR_LD        & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_DA,         (U1)ALERT_REQ_S_ADBZR_DA_CYCLE,        (U1)WCHIME_REQ_IN_DA                 >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_DA                 & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_TCHAR,      (U1)ALERT_REQ_S_ADBZR_TCHAR_CYCL2,     (U1)WCHIME_REQ_IN_TCHAR_CYCL2        >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_TCHAR_CYCL2        & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_TEN_7,     (U1)WCHIME_REQ_IN_TMBZR_TEN_PRI7     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_TMBZR_TEN_PRI7     & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_ADBZR_EDSS,       (U1)ALERT_REQ_S_ADBZR_EDSS_CYCL1,      (U1)WCHIME_REQ_IN_EDSS_R03           >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_EDSS_R03           & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_TEN_6P5,   (U1)WCHIME_REQ_IN_TMBZR_TEN_PRI6P5   >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_TMBZR_TEN_PRI6P5   & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_O_EIGCON,           (U1)ALERT_REQ_O_EIGCON_CYCLE,          (U1)WCHIME_REQ_IN_EIGCON_EG_PWROFF   >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_EIGCON_EG_PWROFF   & (U1)0x1FU)  }, /* MET-O_EIGCON-CSTD-            */
        {  (U2)ALERT_CH_H_BATTRW,           (U1)ALERT_REQ_H_BATTRW_THERMALBC,      (U1)WCHIME_REQ_IN_BATTRW             >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_BATTRW             & (U1)0x1FU)  }, /* MET-H_BATTRW-CSTD-            */
        {  (U2)ALERT_CH_S_ADBZR_SCB,        (U1)ALERT_REQ_S_ADBZR_SCB_CYCL,        (U1)WCHIME_REQ_IN_SCB                >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_SCB                & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_BSM,        (U1)ALERT_REQ_S_ADBZR_BSM_WARNING,     (U1)WCHIME_REQ_IN_BSM                >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_BSM                & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_LDA_LDW,    (U1)ALERT_REQ_S_ADBZR_LDA_LDW_CYCL1,   (U1)WCHIME_REQ_IN_LDA                >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_LDA                & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_ITS,        (U1)ALERT_REQ_S_ADBZR_ITS_CYCL,        (U1)WCHIME_REQ_IN_INFRA_INT          >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_INFRA_INT          & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_B_SMASTA_BCI3,      (U1)ALERT_REQ_B_SMASTA_BCI3_ON,        (U1)WCHIME_REQ_IN_SMASTA_INT3        >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_SMASTA_INT3        & (U1)0x1FU)  }, /* MET-B_SMASTA-CSTD-            */
        {  (U2)ALERT_CH_S_ADBZR_CSR_BZ,     (U1)ALERT_REQ_S_ADBZR_CSR_BZ_FR_LD,    (U1)WCHIME_REQ_IN_CSR_FR_FD          >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_CSR_FR_FD          & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_CSR_BZ,     (U1)ALERT_REQ_S_ADBZR_CSR_BZ_RR_LD,    (U1)WCHIME_REQ_IN_CSR_RR_FD          >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_CSR_RR_FD          & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_CSR_BZ,     (U1)ALERT_REQ_S_ADBZR_CSR_BZ_LD,       (U1)WCHIME_REQ_IN_CSR_FRRR_FD        >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_CSR_FRRR_FD        & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_TCHAR,      (U1)ALERT_REQ_S_ADBZR_TCHAR_CYCL1,     (U1)WCHIME_REQ_IN_TCHAR_CYCL1        >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_TCHAR_CYCL1        & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_C_BRLV_2_BC,        (U1)ALERT_REQ_C_BRLV_2_BC_MALFUNC,     (U1)WCHIME_REQ_IN_BRK_FLDLEAK        >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_BRK_FLDLEAK        & (U1)0x1FU)  }, /* MET-C_BRLV-CSTD-              */
        {  (U2)ALERT_CH_C_STEER_BC,         (U1)ALERT_REQ_C_STEER_BC_CYCL,         (U1)WCHIME_REQ_IN_STEER_STP          >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_STEER_STP          & (U1)0x1FU)  }, /* MET-C_STEER-CSTD-             */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_TEN_6,     (U1)WCHIME_REQ_IN_TMBZR_TEN_PRI6     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_TMBZR_TEN_PRI6     & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_ADBZR_ACC,        (U1)ALERT_REQ_S_ADBZR_ACC_REQ_BRK,     (U1)WCHIME_REQ_IN_ACC_BRKREQ         >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_ACC_BRKREQ         & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_D_SBW_BZ_BSFT,      (U1)ALERT_REQ_D_SBW_BZ_BSFT_DOUBLE,    (U1)WCHIME_REQ_SI_SBW_RJCT           >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_SBW_RJCT           & (U1)0x1FU)  }, /* MET-D_SBW-CSTD-               */
        {  (U2)ALERT_CH_H_ONACCN,           (U1)ALERT_REQ_H_ONACCN_MALFUNC,        (U1)WCHIME_REQ_CO_NACCON             >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_CO_NACCON             & (U1)0x1FU)  }, /* MET-H_ONACCN-CSTD-            */
        {  (U2)ALERT_CH_H_PEXI_WARN,        (U1)ALERT_REQ_H_PEXI_WARN_MALFUNC,     (U1)WCHIME_REQ_CO_PEXI_HV_NDBW       >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_CO_PEXI_HV_NDBW       & (U1)0x1FU)  }, /* MET-H_PEXI-CSTD-              */
        {  (U2)ALERT_CH_H_ACCHOL,           (U1)ALERT_REQ_H_ACCHOL_MALFUNC,        (U1)WCHIME_REQ_CO_ACCHOL             >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_CO_ACCHOL             & (U1)0x1FU)  }, /* MET-H_ACCHOL-CSTD-            */
        {  (U2)ALERT_CH_H_ACCHOL,           (U1)ALERT_REQ_H_ACCHOL_HVSYSOVHT,      (U1)WCHIME_REQ_CO_ACCHOL             >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_CO_ACCHOL             & (U1)0x1FU)  }, /* MET-H_ACCHOL-CSTD-            */
        {  (U2)ALERT_CH_H_ACCHOL,           (U1)ALERT_REQ_H_ACCHOL_EVSYSOVHT,      (U1)WCHIME_REQ_CO_ACCHOL             >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_CO_ACCHOL             & (U1)0x1FU)  }, /* MET-H_ACCHOL-CSTD-            */
        {  (U2)ALERT_CH_H_ACCHOL,           (U1)ALERT_REQ_H_ACCHOL_FCVSYSOVHT,     (U1)WCHIME_REQ_CO_ACCHOL             >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_CO_ACCHOL             & (U1)0x1FU)  }, /* MET-H_ACCHOL-CSTD-            */
        {  (U2)ALERT_CH_D_SBW_BZ_IGSFT,     (U1)ALERT_REQ_D_SBW_BZ_IGSFT_CYCLE,    (U1)WCHIME_REQ_IN_SBW_AUTOP          >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_SBW_AUTOP          & (U1)0x1FU)  }, /* MET-D_SBW-CSTD-               */
        {  (U2)ALERT_CH_S_ADBZR_RSA_SGN,    (U1)ALERT_REQ_S_ADBZR_RSA_SGN_R_LGHT,  (U1)WCHIME_REQ_IN_RSA_SIGN_CAUTION2  >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_RSA_SIGN_CAUTION2  & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_B_ESWUOC_BCB,       (U1)ALERT_REQ_B_ESWUOC_BCB_DOUBLE,     (U1)WCHIME_REQ_SI_ESWUOC_REL         >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_ESWUOC_REL         & (U1)0x1FU)  }, /* MET-B_ESWUOC-CSTD-            */
        {  (U2)ALERT_CH_S_ADBZR_PMAR,       (U1)ALERT_REQ_S_ADBZR_PMAR_ON,         (U1)WCHIME_REQ_IN_PMAR               >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_PMAR               & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_C_BRKBZ,            (U1)ALERT_REQ_C_BRKBZ_APPOPE6,         (U1)WCHIME_REQ_SI_BRK_APP6           >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_BRK_APP6           & (U1)0x1FU)  }, /* MET-C_BRKBZ-CSTD-             */
        {  (U2)ALERT_CH_H_SYSMAL_BC,        (U1)ALERT_REQ_H_SYSMAL_BC_ON,          (U1)WCHIME_REQ_CO_SYSMAL_RNG_P       >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_CO_SYSMAL_RNG_P       & (U1)0x1FU)  }, /* MET-H_SYSMAL-CSTD-            */
        {  (U2)ALERT_CH_O_CHAMAL,           (U1)ALERT_REQ_O_CHAMAL_CYCL,           (U1)WCHIME_REQ_IN_CHAMAL_BAT_FAIL    >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_CHAMAL_BAT_FAIL    & (U1)0x1FU)  }, /* MET-O_CHAMAL-CSTD-            */
        {  (U2)ALERT_CH_O_CHAMAL,           (U1)ALERT_REQ_O_CHAMAL_MALFUNC_BZ,     (U1)WCHIME_REQ_IN_CHAMAL_BAT_FAIL    >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_CHAMAL_BAT_FAIL    & (U1)0x1FU)  }, /* MET-O_CHAMAL-CSTD-            */
        {  (U2)ALERT_CH_O_CHAMAL,           (U1)ALERT_REQ_O_CHAMAL_PRMRYCHK_BZ,    (U1)WCHIME_REQ_IN_CHAMAL_BAT_FAIL    >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_CHAMAL_BAT_FAIL    & (U1)0x1FU)  }, /* MET-O_CHAMAL-CSTD-            */
        {  (U2)ALERT_CH_O_CHAMAL,           (U1)ALERT_REQ_O_CHAMAL_INSPECTION_BZ,  (U1)WCHIME_REQ_IN_CHAMAL_BAT_FAIL    >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_CHAMAL_BAT_FAIL    & (U1)0x1FU)  }, /* MET-O_CHAMAL-CSTD-            */
        {  (U2)ALERT_CH_H_SYSMAL_BC,        (U1)ALERT_REQ_H_SYSMAL_BC_CYCL2,       (U1)WCHIME_REQ_IN_SYSMAL_REQSTP      >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_SYSMAL_REQSTP      & (U1)0x1FU)  }, /* MET-H_SYSMAL-CSTD-            */
        {  (U2)ALERT_CH_C_BRKBZ,            (U1)ALERT_REQ_C_BRKBZ_APPOPE4,         (U1)WCHIME_REQ_IN_BRK_APP4           >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_BRK_APP4           & (U1)0x1FU)  }, /* MET-C_BRKBZ-CSTD-             */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_CONT_5,    (U1)WCHIME_REQ_CO_TMBZR_CONT_PRI5    >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_CO_TMBZR_CONT_PRI5    & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_TEN_5,     (U1)WCHIME_REQ_IN_TMBZR_TEN_PRI5     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_TMBZR_TEN_PRI5     & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_C_EPB_WRN_IG,       (U1)ALERT_REQ_C_EPB_WRN_IG_LOCK,       (U1)WCHIME_REQ_IN_EPB                >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_EPB                & (U1)0x1FU)  }, /* MET-C_EPB-CSTD-               */
        {  (U2)ALERT_CH_O_EIGCON,           (U1)ALERT_REQ_O_EIGCON_ON,             (U1)WCHIME_REQ_CO_EIGCON_IGOFF       >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_CO_EIGCON_IGOFF       & (U1)0x1FU)  }, /* MET-O_EIGCON-CSTD-            */
        {  (U2)ALERT_CH_S_ADBZR_ACC,        (U1)ALERT_REQ_S_ADBZR_ACC_CANCEL,      (U1)WCHIME_REQ_SI_ACC_LSPDCNSL       >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_ACC_LSPDCNSL       & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_LTA_LKA,    (U1)ALERT_REQ_S_ADBZR_LTA_LKA_DBL,     (U1)WCHIME_REQ_SI_LTA_CNCL           >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_LTA_CNCL           & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_LCA_CL,     (U1)ALERT_REQ_S_ADBZR_LCA_CL_DOUBLE,   (U1)WCHIME_REQ_SI_LCS_CNCL           >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_LCS_CNCL           & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_ANN_4P5,   (U1)WCHIME_REQ_SI_TMBZR_ANN_PRI4P5   >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_TMBZR_ANN_PRI4P5   & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_RCV_4P5,   (U1)WCHIME_REQ_SI_TMBZR_RCV_PRI4P5   >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_TMBZR_RCV_PRI4P5   & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_RJT_4P5,   (U1)WCHIME_REQ_SI_TMBZR_RJT_PRI4P5   >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_TMBZR_RJT_PRI4P5   & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_ADBZR_APP,        (U1)ALERT_REQ_S_ADBZR_APP_DISCONT,     (U1)WCHIME_REQ_SI_APP_DIS_ASSIST     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_APP_DIS_ASSIST     & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_APP,        (U1)ALERT_REQ_S_ADBZR_APP_COMPLETION,  (U1)WCHIME_REQ_SI_APP_CMPLT          >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_APP_CMPLT          & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_H_DCLDSP,           (U1)ALERT_REQ_H_DCLDSP_OPERJCT,        (U1)WCHIME_REQ_SI_DCLDSP_OPERJCT     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_DCLDSP_OPERJCT     & (U1)0x1FU)  }, /* MET-H_DCLDSP-CSTD-            */
        {  (U2)ALERT_CH_S_ADBZR_LCA_RQ,     (U1)ALERT_REQ_S_ADBZR_LCA_RQ_SINGLE,   (U1)WCHIME_REQ_SI_LCS_ACK            >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_LCS_ACK            & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_SEA,        (U1)ALERT_REQ_S_ADBZR_SEA_DOUBLE,      (U1)WCHIME_REQ_SI_DOA_RJCT           >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_DOA_RJCT           & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_D_SBW_BZ_BSFT,      (U1)ALERT_REQ_D_SBW_BZ_BSFT_SINGLESP,  (U1)WCHIME_REQ_SI_SBW_SPL_STATE      >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_SBW_SPL_STATE      & (U1)0x1FU)  }, /* MET-D_SBW-CSTD-               */
        {  (U2)ALERT_CH_S_ADBZR_EDSS,       (U1)ALERT_REQ_S_ADBZR_EDSS_CYCL3,      (U1)WCHIME_REQ_IN_EDSS_WRN_BUZ       >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_EDSS_WRN_BUZ       & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_DMC,        (U1)ALERT_REQ_S_ADBZR_DMC_CYCLE,       (U1)WCHIME_REQ_IN_DMC_LV2            >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_DMC_LV2            & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_D_SFTPOS_B_RSBW,    (U1)ALERT_REQ_D_SFTPOS_B_RSBW_CYCLE,   (U1)WCHIME_REQ_IN_SFTPOS_REV         >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_SFTPOS_REV         & (U1)0x1FU)  }, /* MET-D_SFTPOS-CSTD-            */
        {  (U2)ALERT_CH_B_SMASTA_BCI2,      (U1)ALERT_REQ_B_SMASTA_BCI2_ON,        (U1)WCHIME_REQ_IN_SMASTA_INT2        >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_SMASTA_INT2        & (U1)0x1FU)  }, /* MET-B_SMASTA-CSTD-            */
        {  (U2)ALERT_CH_B_SMASTA_BCDR,      (U1)ALERT_REQ_B_SMASTA_BCDR_ON,        (U1)WCHIME_REQ_CO_SMASTA_CON         >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_CO_SMASTA_CON         & (U1)0x1FU)  }, /* MET-B_SMASTA-CSTD-            */
        {  (U2)ALERT_CH_S_ADBZR_ACC,        (U1)ALERT_REQ_S_ADBZR_ACC_OVER_SPD,    (U1)WCHIME_REQ_IN_ACC_OVERSPD        >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_ACC_OVERSPD        & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_ACC,        (U1)ALERT_REQ_S_ADBZR_ACC_REQ_OPE,     (U1)WCHIME_REQ_SI_ACC_SHIFTREQ       >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_ACC_SHIFTREQ       & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_C_TPMS,             (U1)ALERT_REQ_C_TPMS_CYCL,             (U1)WCHIME_REQ_IN_TPMS_CYCL          >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_TPMS_CYCL          & (U1)0x1FU)  }, /* MET-C_TPMS-CSTD-              */
        {  (U2)ALERT_CH_S_ADBZR_SWS,        (U1)ALERT_REQ_S_ADBZR_SWS_SINGLE,      (U1)WCHIME_REQ_SI_SWS                >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_SWS                & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_M_MINDSPWR,         (U1)ALERT_REQ_M_MINDSPWR_CYCLE,        (U1)WCHIME_REQ_IN_MINDSPWR_LV2       >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_MINDSPWR_LV2       & (U1)0x1FU)  }, /* MET-M_MINDSPWR-CSTD-          */
        {  (U2)ALERT_CH_M_BGLFSPD,          (U1)ALERT_REQ_M_BGLFSPD_ON,            (U1)WCHIME_REQ_IN_BGLFSPD            >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_BGLFSPD            & (U1)0x1FU)  }, /* MET-M_BGLFSPD-CSTD-           */
        {  (U2)ALERT_CH_B_BDOOR,            (U1)ALERT_REQ_B_BDOOR_CYCLE,           (U1)WCHIME_REQ_IN_DR_OPN             >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_DR_OPN             & (U1)0x1FU)  }, /* MET-B_BDOOR-CSTD-             */
        {  (U2)ALERT_CH_C_BRKBZ,            (U1)ALERT_REQ_C_BRKBZ_FAILURE,         (U1)WCHIME_REQ_IN_BRK_SYS_MAL        >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_BRK_SYS_MAL        & (U1)0x1FU)  }, /* MET-C_BRKBZ-CSTD-             */
        {  (U2)ALERT_CH_C_BRKBZ,            (U1)ALERT_REQ_C_BRKBZ_UNAVAILABLE2,    (U1)WCHIME_REQ_IN_BRK_SYS_NOOPE2     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_BRK_SYS_NOOPE2     & (U1)0x1FU)  }, /* MET-C_BRKBZ-CSTD-             */
        {  (U2)ALERT_CH_C_BRKBZ,            (U1)ALERT_REQ_C_BRKBZ_UNAVAILABLE1,    (U1)WCHIME_REQ_IN_BRK_SYS_NOOPE1     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_BRK_SYS_NOOPE1     & (U1)0x1FU)  }, /* MET-C_BRKBZ-CSTD-             */
        {  (U2)ALERT_CH_C_STEER_BC,         (U1)ALERT_REQ_C_STEER_BC_SINGLE,       (U1)WCHIME_REQ_SI_STEER_LMT          >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_STEER_LMT          & (U1)0x1FU)  }, /* MET-C_STEER-CSTD-             */
        {  (U2)ALERT_CH_D_SBW_BZ_PT,        (U1)ALERT_REQ_D_SBW_BZ_PT_SINGLE,      (U1)WCHIME_REQ_SI_SBW_MAL            >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_SBW_MAL            & (U1)0x1FU)  }, /* MET-D_SBW-CSTD-               */
        {  (U2)ALERT_CH_D_SBW_BZ_PT,        (U1)ALERT_REQ_D_SBW_BZ_PT_CYCLE,       (U1)WCHIME_REQ_IN_SBW_MAL            >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_SBW_MAL            & (U1)0x1FU)  }, /* MET-D_SBW-CSTD-               */
        {  (U2)ALERT_CH_H_SYSMAL_BC,        (U1)ALERT_REQ_H_SYSMAL_BC_CYCL3,       (U1)WCHIME_REQ_IN_SYSMAL_REMDST_500M >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_SYSMAL_REMDST_500M & (U1)0x1FU)  }, /* MET-H_SYSMAL-CSTD-            */
        {  (U2)ALERT_CH_H_SYSMAL_BC,        (U1)ALERT_REQ_H_SYSMAL_BC_CYCL4,       (U1)WCHIME_REQ_IN_SYSMAL_REMDST_1KM  >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_SYSMAL_REMDST_1KM  & (U1)0x1FU)  }, /* MET-H_SYSMAL-CSTD-            */
        {  (U2)ALERT_CH_S_ADBZR_LTA_LTA,    (U1)ALERT_REQ_S_ADBZR_LTA_LTA_PTN2,    (U1)WCHIME_REQ_IN_LTA_PTN2           >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_LTA_PTN2           & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_LTA_LTA,    (U1)ALERT_REQ_S_ADBZR_LTA_LTA_PTN3,    (U1)WCHIME_REQ_SI_LTA_PTN3           >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_LTA_PTN3           & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_ANN_4,     (U1)WCHIME_REQ_SI_TMBZR_ANN_PRI4     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_TMBZR_ANN_PRI4     & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_RCV_4,     (U1)WCHIME_REQ_SI_TMBZR_RCV_PRI4     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_TMBZR_RCV_PRI4     & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_RJT_4,     (U1)WCHIME_REQ_SI_TMBZR_RJT_PRI4     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_TMBZR_RJT_PRI4     & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_CONT_4,    (U1)WCHIME_REQ_CO_TMBZR_CONT_PRI4    >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_CO_TMBZR_CONT_PRI4    & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_TEN_4,     (U1)WCHIME_REQ_IN_TMBZR_TEN_PRI4     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_TMBZR_TEN_PRI4     & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_M_MINDSPWR,         (U1)ALERT_REQ_M_MINDSPWR_SINGLE,       (U1)WCHIME_REQ_SI_MINDSPWR_LV1       >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_MINDSPWR_LV1       & (U1)0x1FU)  }, /* MET-M_MINDSPWR-CSTD-          */
        {  (U2)ALERT_CH_S_ADBZR_RSA_SGN,    (U1)ALERT_REQ_S_ADBZR_RSA_SGN_SPDLMT,  (U1)WCHIME_REQ_SI_RSA_SIGN_CTN1      >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_RSA_SIGN_CTN1      & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_DMC,        (U1)ALERT_REQ_S_ADBZR_DMC_SINGLE,      (U1)WCHIME_REQ_SI_DMC_LV1            >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_DMC_LV1            & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_H_SYSMAL_BC,        (U1)ALERT_REQ_H_SYSMAL_BC_SINGLE,      (U1)WCHIME_REQ_SI_SYSMAL_FAIL        >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_SYSMAL_FAIL        & (U1)0x1FU)  }, /* MET-H_SYSMAL-CSTD-            */
        {  (U2)ALERT_CH_O_PDSMAL_BC,        (U1)ALERT_REQ_O_PDSMAL_BC_CYCL,        (U1)WCHIME_REQ_IN_PDSMAL             >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_PDSMAL             & (U1)0x1FU)  }, /* MET-O_PDSMAL-CST0             */
        {  (U2)ALERT_CH_S_ADBZR_LTA_LTA,    (U1)ALERT_REQ_S_ADBZR_LTA_LTA_PTN1,    (U1)WCHIME_REQ_IN_LTA_PTN1           >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_LTA_PTN1           & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_ITS,        (U1)ALERT_REQ_S_ADBZR_ITS_SINGLE,      (U1)WCHIME_REQ_SI_INFRA_SNGL         >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_INFRA_SNGL         & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_ANN_3,     (U1)WCHIME_REQ_SI_TMBZR_ANN_PRI3     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_TMBZR_ANN_PRI3     & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_RCV_3,     (U1)WCHIME_REQ_SI_TMBZR_RCV_PRI3     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_TMBZR_RCV_PRI3     & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_RJT_3,     (U1)WCHIME_REQ_SI_TMBZR_RJT_PRI3     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_TMBZR_RJT_PRI3     & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_CONT_3,    (U1)WCHIME_REQ_CO_TMBZR_CONT_PRI3    >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_CO_TMBZR_CONT_PRI3    & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_TEN_3,     (U1)WCHIME_REQ_IN_TMBZR_TEN_PRI3     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_TMBZR_TEN_PRI3     & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_ADBZR_ACC,        (U1)ALERT_REQ_S_ADBZR_ACC_START,       (U1)WCHIME_REQ_SI_ACC_AUTOSTART      >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_ACC_AUTOSTART      & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_B_BLGT,             (U1)ALERT_REQ_B_BLGT_ON,               (U1)WCHIME_REQ_CO_LIGHT              >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_CO_LIGHT              & (U1)0x1FU)  }, /* MET-B_BLGT-CSTD-              */
        {  (U2)ALERT_CH_D_SBW_BZ_BSFT,      (U1)ALERT_REQ_D_SBW_BZ_BSFT_SINGLE,    (U1)WCHIME_REQ_SI_SBW_RCPT           >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_SBW_RCPT           & (U1)0x1FU)  }, /* MET-D_SBW-CSTD-               */
        {  (U2)ALERT_CH_S_TMBZR_BC_DOT,     (U1)ALERT_REQ_S_TMBZR_BC_DOT_DOHREQ,   (U1)WCHIME_REQ_IN_TMBZR_DOHREQ       >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_TMBZR_DOHREQ       & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_ADBZR_LDA_CSF,    (U1)ALERT_REQ_S_ADBZR_LDA_CSF_CYCL,    (U1)WCHIME_REQ_IN_LDA_HFCT           >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_LDA_HFCT           & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_H_BATINS_BC,        (U1)ALERT_REQ_H_BATINS_BC_CYCL,        (U1)WCHIME_REQ_IN_BATINS             >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_BATINS             & (U1)0x1FU)  }, /* MET-H_BATINS-CSTD-            */
        {  (U2)ALERT_CH_C_TPMS,             (U1)ALERT_REQ_C_TPMS_SINGLE,           (U1)WCHIME_REQ_SI_TPMS_SINGLE        >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_TPMS_SINGLE        & (U1)0x1FU)  }, /* MET-C_TPMS-CSTD-              */
        {  (U2)ALERT_CH_S_ADBZR_TCHAR,      (U1)ALERT_REQ_S_ADBZR_TCHAR_SINGLE,    (U1)WCHIME_REQ_SI_TCHAR_SNGL         >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_TCHAR_SNGL         & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_LDA_LDW,    (U1)ALERT_REQ_S_ADBZR_LDA_LDW_CYCL2,   (U1)WCHIME_REQ_IN_LDA_WARN           >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_LDA_WARN           & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_B_SMASTA_BCS1,      (U1)ALERT_REQ_B_SMASTA_BCS1_ON,        (U1)WCHIME_REQ_SI_SMASTA_SNGL        >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_SMASTA_SNGL        & (U1)0x1FU)  }, /* MET-B_SMASTA-CSTD-            */
        {  (U2)ALERT_CH_H_TOWWAR,           (U1)ALERT_REQ_H_TOWWAR_MLFNC_HV,       (U1)WCHIME_REQ_IN_TOWWAR             >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_TOWWAR             & (U1)0x1FU)  }, /* MET-H_TOWWAR-CSTD-            */
        {  (U2)ALERT_CH_H_TOWWAR,           (U1)ALERT_REQ_H_TOWWAR_MLFNC_EV,       (U1)WCHIME_REQ_IN_TOWWAR             >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_TOWWAR             & (U1)0x1FU)  }, /* MET-H_TOWWAR-CSTD-            */
        {  (U2)ALERT_CH_H_TOWWAR,           (U1)ALERT_REQ_H_TOWWAR_MLFNC_FCV,      (U1)WCHIME_REQ_IN_TOWWAR             >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_TOWWAR             & (U1)0x1FU)  }, /* MET-H_TOWWAR-CSTD-            */
        {  (U2)ALERT_CH_H_TOWWAR,           (U1)ALERT_REQ_H_TOWWAR_MLFNC_HV2,      (U1)WCHIME_REQ_IN_TOWWAR             >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_TOWWAR             & (U1)0x1FU)  }, /* MET-H_TOWWAR-CSTD-            */
        {  (U2)ALERT_CH_H_TOWWAR,           (U1)ALERT_REQ_H_TOWWAR_MLFNC,          (U1)WCHIME_REQ_IN_TOWWAR             >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_TOWWAR             & (U1)0x1FU)  }, /* MET-H_TOWWAR-CSTD-            */
        {  (U2)ALERT_CH_S_ADBZR_TMN,        (U1)ALERT_REQ_S_ADBZR_TMN_SINGLE,      (U1)WCHIME_REQ_SI_TMN_LVN            >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_TMN_LVN            & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_ANN_2,     (U1)WCHIME_REQ_SI_TMBZR_ANN_PRI2     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_TMBZR_ANN_PRI2     & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_RCV_2,     (U1)WCHIME_REQ_SI_TMBZR_RCV_PRI2     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_TMBZR_RCV_PRI2     & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_RJT_2,     (U1)WCHIME_REQ_SI_TMBZR_RJT_PRI2     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_TMBZR_RJT_PRI2     & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_CONT_2,    (U1)WCHIME_REQ_CO_TMBZR_CONT_PRI2    >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_CO_TMBZR_CONT_PRI2    & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_TEN_2,     (U1)WCHIME_REQ_IN_TMBZR_TEN_PRI2     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_TMBZR_TEN_PRI2     & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_B_SMASTA_BCI1,      (U1)ALERT_REQ_B_SMASTA_BCI1_ON,        (U1)WCHIME_REQ_IN_SMASTA_INT1        >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_SMASTA_INT1        & (U1)0x1FU)  }, /* MET-B_SMASTA-CSTD-            */
        {  (U2)ALERT_CH_C_BRKBZ,            (U1)ALERT_REQ_C_BRKBZ_APPOPE3,         (U1)WCHIME_REQ_SI_BRK_APP3           >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_BRK_APP3           & (U1)0x1FU)  }, /* MET-C_BRKBZ-CSTD-             */
        {  (U2)ALERT_CH_C_BRKBZ,            (U1)ALERT_REQ_C_BRKBZ_APPOPE1,         (U1)WCHIME_REQ_IN_BRK_APP1           >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_BRK_APP1           & (U1)0x1FU)  }, /* MET-C_BRKBZ-CSTD-             */
        {  (U2)ALERT_CH_C_BRKBZ,            (U1)ALERT_REQ_C_BRKBZ_APPOPE2,         (U1)WCHIME_REQ_IN_BRK_APP2           >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_BRK_APP2           & (U1)0x1FU)  }, /* MET-C_BRKBZ-CSTD-             */
        {  (U2)ALERT_CH_C_BRKHLD_WRN,       (U1)ALERT_REQ_C_BRKHLD_WRN_WRN1,       (U1)WCHIME_REQ_SI_BKHLD_NOTACT_R16   >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_BKHLD_NOTACT_R16   & (U1)0x1FU)  }, /* MET-C_BRKHLD-CSTD-            */
        {  (U2)ALERT_CH_C_BRKHLD_WRN,       (U1)ALERT_REQ_C_BRKHLD_WRN_ACT,        (U1)WCHIME_REQ_SI_BKHLD_NOTREL       >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_BKHLD_NOTREL       & (U1)0x1FU)  }, /* MET-C_BRKHLD-CSTD-            */
        {  (U2)ALERT_CH_C_BRKHLD_WRN,       (U1)ALERT_REQ_C_BRKHLD_WRN_UNAVBL1,    (U1)WCHIME_REQ_SI_BKHLD_NOTACT_R07   >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_BKHLD_NOTACT_R07   & (U1)0x1FU)  }, /* MET-C_BRKHLD-CSTD-            */
        {  (U2)ALERT_CH_C_BRKHLD_WRN,       (U1)ALERT_REQ_C_BRKHLD_WRN_UNAVBL2,    (U1)WCHIME_REQ_SI_BKHLD_NOTACT_R08   >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_BKHLD_NOTACT_R08   & (U1)0x1FU)  }, /* MET-C_BRKHLD-CSTD-            */
        {  (U2)ALERT_CH_C_BRKHLD_WRN,       (U1)ALERT_REQ_C_BRKHLD_WRN_UNAVBL3,    (U1)WCHIME_REQ_SI_BKHLD_NOTACT_R17   >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_BKHLD_NOTACT_R17   & (U1)0x1FU)  }, /* MET-C_BRKHLD-CSTD-            */
        {  (U2)ALERT_CH_C_BRKHLD_WRN,       (U1)ALERT_REQ_C_BRKHLD_WRN_MAINT1,     (U1)WCHIME_REQ_SI_BKHLD_REL_R10      >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_BKHLD_REL_R10      & (U1)0x1FU)  }, /* MET-C_BRKHLD-CSTD-            */
        {  (U2)ALERT_CH_C_BRKHLD_WRN,       (U1)ALERT_REQ_C_BRKHLD_WRN_MAINT2,     (U1)WCHIME_REQ_SI_BKHLD_REL_R11      >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_BKHLD_REL_R11      & (U1)0x1FU)  }, /* MET-C_BRKHLD-CSTD-            */
        {  (U2)ALERT_CH_C_BRKHLD_WRN,       (U1)ALERT_REQ_C_BRKHLD_WRN_UNAVBL4,    (U1)WCHIME_REQ_SI_BKHLD_NOTACT_R13   >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_BKHLD_NOTACT_R13   & (U1)0x1FU)  }, /* MET-C_BRKHLD-CSTD-            */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_ANN_1,     (U1)WCHIME_REQ_SI_TMBZR_ANN_PRI1     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_TMBZR_ANN_PRI1     & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_RCV_1,     (U1)WCHIME_REQ_SI_TMBZR_RCV_PRI1     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_TMBZR_RCV_PRI1     & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_RJT_1,     (U1)WCHIME_REQ_SI_TMBZR_RJT_PRI1     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_TMBZR_RJT_PRI1     & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_CONT_1,    (U1)WCHIME_REQ_CO_TMBZR_CONT_PRI1    >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_CO_TMBZR_CONT_PRI1    & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_TEN_1,     (U1)WCHIME_REQ_IN_TMBZR_TEN_PRI1     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_TMBZR_TEN_PRI1     & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_C_BRKBZ,            (U1)ALERT_REQ_C_BRKBZ_APPOPE5,         (U1)WCHIME_REQ_SI_BRK_APP5           >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_BRK_APP5           & (U1)0x1FU)  }, /* MET-C_BRKBZ-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_RSA_LMT,    (U1)ALERT_REQ_S_ADBZR_RSA_LMT_SINGLE,  (U1)WCHIME_REQ_SI_RSA_CHG_SPLDLMT    >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_RSA_CHG_SPLDLMT    & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_S_ADBZR_ACC,        (U1)ALERT_REQ_S_ADBZR_ACC_START_APRV,  (U1)WCHIME_REQ_SI_ACC_APPRVLSTART    >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_ACC_APPRVLSTART    & (U1)0x1FU)  }, /* MET-S_ADBZR-CSTD-             */
        {  (U2)ALERT_CH_B_FMSEAT,           (U1)ALERT_REQ_B_FMSEAT_MEM_SCS,        (U1)WCHIME_REQ_SI_FMSEAT_MEM_SCS     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_FMSEAT_MEM_SCS     & (U1)0x1FU)  }, /* MET-B_FMSEAT-CSTD--           */
        {  (U2)ALERT_CH_B_FMSEAT,           (U1)ALERT_REQ_B_FMSEAT_MEM_REJ,        (U1)WCHIME_REQ_SI_FMSEAT_MEM_REJ     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_FMSEAT_MEM_REJ     & (U1)0x1FU)  }, /* MET-B_FMSEAT-CSTD--           */
        {  (U2)ALERT_CH_B_FMSEAT,           (U1)ALERT_REQ_B_FMSEAT_ERS_INFO,       (U1)WCHIME_REQ_SI_FMSEAT_ERS_INFO    >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_FMSEAT_ERS_INFO    & (U1)0x1FU)  }, /* MET-B_FMSEAT-CSTD--           */
        {  (U2)ALERT_CH_B_FMSEAT,           (U1)ALERT_REQ_B_FMSEAT_MEM_CALL,       (U1)WCHIME_REQ_SI_FMSEAT_MEM_CALL    >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_FMSEAT_MEM_CALL    & (U1)0x1FU)  }, /* MET-B_FMSEAT-CSTD--           */
        {  (U2)ALERT_CH_B_ESWUOC_BC,        (U1)ALERT_REQ_B_ESWUOC_BC_DOUBLE,      (U1)WCHIME_REQ_SI_ESWUOC_RJCT        >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_ESWUOC_RJCT        & (U1)0x1FU)  }, /* MET-B_ESWUOC-CSTD-            */
        {  (U2)ALERT_CH_B_SMASTA_BCS2,      (U1)ALERT_REQ_B_SMASTA_BCS2_ON,        (U1)WCHIME_REQ_SI_SMASTA_SNGL2       >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_SMASTA_SNGL2       & (U1)0x1FU)  }, /* MET-B_SMASTA-CST2             */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_ANN_0,     (U1)WCHIME_REQ_SI_TMBZR_ANN_PRI0     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_TMBZR_ANN_PRI0     & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_RCV_0,     (U1)WCHIME_REQ_SI_TMBZR_RCV_PRI0     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_TMBZR_RCV_PRI0     & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_RJT_0,     (U1)WCHIME_REQ_SI_TMBZR_RJT_PRI0     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_SI_TMBZR_RJT_PRI0     & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_CONT_0,    (U1)WCHIME_REQ_CO_TMBZR_CONT_PRI0    >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_CO_TMBZR_CONT_PRI0    & (U1)0x1FU)  }, /* MET-S_TMBZR-CST0              */
        {  (U2)ALERT_CH_S_TMBZR_BC_AD,      (U1)ALERT_REQ_S_TMBZR_BC_AD_TEN_0,     (U1)WCHIME_REQ_IN_TMBZR_TEN_PRI0     >> 5U,  (U4)0x00000001 << ((U1)WCHIME_REQ_IN_TMBZR_TEN_PRI0     & (U1)0x1FU)  }  /* MET-S_TMBZR-CST0              */
    };

    U2 u2_t_num_reqbit;

    u2_t_num_reqbit = ((U2)sizeof(st_sp_WCHIME_ALERT_REQBIT)) / ((U2)sizeof(st_sp_WCHIME_ALERT_REQBIT[0]));
    vd_g_AlertReqToBit(st_sp_WCHIME_ALERT_REQBIT, u2_t_num_reqbit, u4p_a_reqbit, (U1)WCHIME_REQBIT_NUM_WORD);

    vd_s_wChimeCfgSftposRjctReqchk(u4p_a_reqbit);                   /* Set SFTPOS reject buzzer req.               */
    vd_s_wChimeCfgRctaReqchk(u4p_a_reqbit);                         /* Set RCTA buzzer req.                        */
    vd_s_wChimeCfgMcReqchk(u4p_a_reqbit);                           /* Set Master Caution buzzer req.              */
    vd_s_wChimeCfgSbltRemReqchk(u4p_a_reqbit);                      /* Set Seatbelt Reminder buzzer req.           */
    vd_s_wChimeCfgTurhazReqchk(u4p_a_reqbit);                       /* Set Flasher buzzer req.                     */
    vd_s_wChimeCfgMWVCReqchk(u4p_a_reqbit);                         /* Set Meter Warning Volume buzzer req.        */
    vd_s_wChimeCfgMindspDelchk(u4p_a_reqbit);                       /* Check to delete MINDSP warning buzzer req.  */
    vd_s_wChimeCfgAppDelchk(u4p_a_reqbit);                          /* Check to delete Advanced Park buzzer req.   */
    vd_s_wChimeCfgBglfspdDelchk(u4p_a_reqbit);                      /* Check to delete BGLFSPD warning buzzer req. */
    vd_s_wChimeCfgBlgtDelchk(u4p_a_reqbit);                         /* Check to delete Light Reminder buzzer req.  */
    vd_s_wChimeCfgAppReqchk(u4p_a_reqbit);                          /* Check to add silencetime APP buzzer req.    */
}
/*===================================================================================================================================*/
/*  U1      u1_g_wChimeCfgWavCycled(const U1 u1_a_WC_CH)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_wChimeCfgWavCycled(const U1 u1_a_WC_CH)
{
    U2 u2_t_tim;
    U1 u1_t_cycled;

    u2_t_tim = u2_g_SoundCriMgrGetTimRemained(u1_a_WC_CH);
    if(u2_t_tim <= (U2)1U){
        u1_t_cycled = (U1)TRUE;
    }
    else{
        u1_t_cycled = (U1)FALSE;
    }

    return(u1_t_cycled);
}
/*===================================================================================================================================*/
/*  U1      u1_g_wChimeCfgReqRead(const U4 * u4_ap_REQBIT, const U1 u1_a_REQ_ID)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_wChimeCfgReqRead(const U4 * u4_ap_REQBIT, const U1 u1_a_REQ_ID)
{
    U1 u1_t_idx;
    U1 u1_t_pos;
    U1 u1_t_result;

    u1_t_idx = u1_a_REQ_ID >> WCHIME_CNV_IDX;
    u1_t_pos = u1_a_REQ_ID & (U1)WCHIME_CNV_POS;

    u1_t_result = (U1)((U4)(u4_ap_REQBIT[u1_t_idx] >> u1_t_pos) & (U4)0x00000001U);

    return(u1_t_result);
}
/*===================================================================================================================================*/
/*  U1      u1_g_wChimeCfgIntermSplCnd(const U1 u1_a_REQ_SEL, const U1 u1_a_REQ_NEXT)                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_REQ_SEL  : current buzzer request ID                                                                        */
/*                  u1_a_REQ_NEXT : next buzzer request ID                                                                           */
/*  Return:         u1_t_chk      : check result if it is a special buzzer item with a high priority interrupt buzzer                */
/*===================================================================================================================================*/
U1      u1_g_wChimeCfgIntermSplCnd(const U1 u1_a_REQ_SEL, const U1 u1_a_REQ_NEXT)
{
    U1 u1_t_chk;

    u1_t_chk = (U1)FALSE;

    switch(u1_a_REQ_SEL){
        case (U1)WCHIME_REQ_IN_FRRADA_CMP:
        case (U1)WCHIME_REQ_IN_FRRADA_ERR:
        case (U1)WCHIME_REQ_IN_BSM:
        case (U1)WCHIME_REQ_IN_LDA:
        case (U1)WCHIME_REQ_IN_LDA_HFCT:
        case (U1)WCHIME_REQ_IN_LDA_WARN:
            if (u1_a_REQ_NEXT < u1_a_REQ_SEL)
            {
                u1_t_chk = (U1)TRUE;
            }
            break;
        default:
            /* Do Nothing */
            break;
    }
    return(u1_t_chk);
}
/*===================================================================================================================================*/
/*  static  void    vd_s_wChimeCfgSftposRjctReqchk(U4 * u4p_a_reqbit)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_wChimeCfgSftposRjctReqchk(U4* u4p_a_reqbit)
{
    U1 u1_t_sftpos_rjct_req;
    U1 u1_t_edge_jdg;

    u1_t_sftpos_rjct_req = u1_g_AlertReqByCh((U2)ALERT_CH_D_SFTPOS_B_RJTB);

    u1_t_edge_jdg = u1_s_wchime_sftpos_si_last ^ u1_t_sftpos_rjct_req;

    if(u1_t_edge_jdg != (U1)0U){
        if(u1_t_sftpos_rjct_req == (U1)ALERT_REQ_D_SFTPOS_B_RJTB_DBL1){
            vd_s_wChimeCfgReqOn(u4p_a_reqbit, (U1)WCHIME_REQ_SI_SFTPOS_NML);
        }
    }

    u1_s_wchime_sftpos_si_last = u1_t_sftpos_rjct_req;

}
/*===================================================================================================================================*/
/*  static  void    vd_s_wChimeCfgRctaReqchk(U4 * u4p_a_reqbit)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_wChimeCfgRctaReqchk(U4 * u4p_a_reqbit)
{
    U1 u1_t_req_sel;
    U1 u1_t_csr_req;
    U1 u1_t_alrt_csr_vol;

    u1_t_req_sel = u1_g_wChimeReqSel((U1)WCHIME_RCTA_BUZZ_CH, vdp_PTR_NA);

    /* RCTA buzzer with CSR ECU(CLESON Specification) */
    u1_g_wchime_alrt_csr_vol_old = u1_g_wchime_alrt_csr_vol_now;
    u1_t_alrt_csr_vol            = u1_g_AlertReqByCh((U2)ALERT_CH_S_ADBZR_CSR_VOL);
    if((u1_t_alrt_csr_vol == (U1)ALERT_REQ_S_ADBZR_CSR_VOL_VOL0) ||
       (u1_t_alrt_csr_vol == (U1)ALERT_REQ_S_ADBZR_CSR_VOL_VOL1) ||
       (u1_t_alrt_csr_vol == (U1)ALERT_REQ_S_ADBZR_CSR_VOL_VOL2) ||
       (u1_t_alrt_csr_vol == (U1)ALERT_REQ_S_ADBZR_CSR_VOL_VOL3) ||
       (u1_t_alrt_csr_vol == (U1)ALERT_REQ_S_ADBZR_CSR_VOL_VOL4) ||
       (u1_t_alrt_csr_vol == (U1)ALERT_REQ_S_ADBZR_CSR_VOL_VOL5) ||
       (u1_t_alrt_csr_vol == (U1)ALERT_REQ_S_ADBZR_CSR_VOL_VOL6) ||
       (u1_t_alrt_csr_vol == (U1)ALERT_REQ_S_ADBZR_CSR_VOL_VOL7)){
        u1_g_wchime_alrt_csr_vol_now = u1_t_alrt_csr_vol;
    }
    else{
        u1_g_wchime_alrt_csr_vol_now = (U1)ALERT_REQ_S_ADBZR_CSR_VOL_VOL7;
    }

    u1_t_csr_req = u1_g_AlertReqByCh((U2)ALERT_CH_S_ADBZR_CSR_BZ);

    if(u1_t_csr_req == (U1)ALERT_REQ_S_ADBZR_CSR_BZ_RCTA){
        if(u1_t_req_sel != (U1)WCHIME_REQ_IN_CSR_RCTA){         /* For intermittent buzzer, Need to make requestless duration. */
            vd_s_wChimeCfgReqOn(u4p_a_reqbit, (U1)WCHIME_REQ_IN_CSR_RCTA);
        }
        else{
            if(u1_g_wchime_alrt_csr_vol_old != u1_g_wchime_alrt_csr_vol_now){
                vd_s_wChimeCfgReqOn(u4p_a_reqbit, (U1)WCHIME_REQ_IN_CSR_RCTA);
            }
        }
    }
}
/*===================================================================================================================================*/
/*  static  void    vd_s_wChimeCfgMcReqchk(U4 * u4p_a_reqbit)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_wChimeCfgMcReqchk(U4 * u4p_a_reqbit)
{
    U1 u1_t_mstr_req;

    u1_t_mstr_req = u1_g_wChimeCfgMstrReq();

    if(u1_t_mstr_req == (U1)TRUE){
        vd_s_wChimeCfgReqOn(u4p_a_reqbit, (U1)WCHIME_REQ_SI_MLT_MSG);
    }
}
/*===================================================================================================================================*/
/*  static  void    vd_s_wChimeCfgSbltRemReqchk(U4 * u4p_a_reqbit)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_wChimeCfgSbltRemReqchk(U4 * u4p_a_reqbit)
{
    static const U1 u1_sp_WCHIME_SBLTID_LIST[SBLTSYNC_NUM_CHM] = {
        (U1)WCHIME_REQ_IN_SBLT_FMV,      /* 00 SBLTSYNC_CHM_REQ_LGL.   */
        (U1)WCHIME_REQ_IN_SBLT_LV2,      /* 01 SBLTSYNC_CHM_REQ_LV2.   */
        (U1)WCHIME_REQ_IN_SBLT_LV1,      /* 02 SBLTSYNC_CHM_REQ_LV1.   */
        (U1)WCHIME_REQ_SI_SBLT           /* 03 SBLTSYNC_CHM_REQ_UNBKL. */
    };

    U4 u4_t_loop;
    U1 u1_t_belt_req;

    u1_t_belt_req = u1_g_SbltsyncReqChm();
    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)SBLTSYNC_NUM_CHM; u4_t_loop++){
        if((u1_t_belt_req & (U1)(1U << u4_t_loop)) != (U1)0U){
            vd_s_wChimeCfgReqOn(u4p_a_reqbit, u1_sp_WCHIME_SBLTID_LIST[u4_t_loop]);
        }
    }
}
/*===================================================================================================================================*/
/*  static  void    vd_s_wChimeCfgTurhazReqchk(U4 * u4p_a_reqbit)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_wChimeCfgTurhazReqchk(U4 * u4p_a_reqbit)
{
    static const U1 u1_sp2_WCHIME_TURHAZ_TICVOL_LIST[THBLNKR_NUM_SPDMD] = {
        (U1)WCHIME_REQ_SI_TURHAZ_STA_LS,
        (U1)WCHIME_REQ_SI_TURHAZ_STA_MS,
        (U1)WCHIME_REQ_SI_TURHAZ_STA_HS
    };

    static const U1 u1_sp2_WCHIME_TURHAZ_TOCVOL_LIST[THBLNKR_NUM_SPDMD] = {
        (U1)WCHIME_REQ_SI_TURHAZ_FIN_LS,
        (U1)WCHIME_REQ_SI_TURHAZ_FIN_MS,
        (U1)WCHIME_REQ_SI_TURHAZ_FIN_HS
    };

    U1 u1_t_spdmd;
    U1 u1_t_tictoc;
    U1 u1_t_tictocreq;

    u1_t_spdmd  = (U1)0U;

    u1_t_tictoc = u1_g_ThblnkrTicTocReq(&u1_t_spdmd);

    if(u1_t_spdmd >= (U1)THBLNKR_NUM_SPDMD){
        u1_t_spdmd = (U1)THBLNKR_SPDMD_HI;
    }

    if(u1_t_tictoc == (U1)THBLNKR_TIC){
        u1_t_tictocreq = u1_sp2_WCHIME_TURHAZ_TICVOL_LIST[u1_t_spdmd];
        vd_s_wChimeCfgReqOn(u4p_a_reqbit, u1_t_tictocreq);
    }
    else if(u1_t_tictoc == (U1)THBLNKR_TOC){
        u1_t_tictocreq = u1_sp2_WCHIME_TURHAZ_TOCVOL_LIST[u1_t_spdmd];
        vd_s_wChimeCfgReqOn(u4p_a_reqbit, u1_t_tictocreq);
    }
    else{
        /* Do nothing */
    }
}

/*===================================================================================================================================*/
/*  static U1      vd_s_wChimeCfgAppReqchk(U4 * u4p_a_reqbit)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void   vd_s_wChimeCfgAppReqchk(U4 * u4p_a_reqbit)
{
    static const U1     u1_sp_WCHIME_APP_BZ_LIST[WCHIME_APP_BZ_NUM] = {
        (U1)WCHIME_REQ_SI_APP_DIS_ASSIST,     (U1)WCHIME_REQ_SI_APP_CMPLT
    };

    U4                    u4_t_loop;
    U4                    u4_t_lpcnt;
    U4                    u4_t_apprqbit;
    U4                    u4_t_appchkbit[WCHIME_REQBIT_NWORD_MAX];

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_WCHIME_REQBIT_NUM_WORD; u4_t_lpcnt++){
        u4_t_appchkbit[u4_t_lpcnt] = (U4)0U;
    }

    if(u1_g_wchime_silencetime_flag == (U1)TRUE){
        for(u4_t_loop = (U4)0U; u4_t_loop < (U4)WCHIME_APP_BZ_NUM; u4_t_loop++){
            vd_s_wChimeCfgReqOn(&u4_t_appchkbit[0], u1_sp_WCHIME_APP_BZ_LIST[u4_t_loop]);
        }

        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_WCHIME_REQBIT_NUM_WORD; u4_t_lpcnt++){
            u4_t_apprqbit =  (u4p_a_reqbit[u4_t_lpcnt] ^ u4_s_wchime_apprq_bit[u4_t_lpcnt]) | u4p_a_reqbit[u4_t_lpcnt];
            u4_t_apprqbit &= u4_t_appchkbit[u4_t_lpcnt];

            u4p_a_reqbit[u4_t_lpcnt] &= ((U4)U4_MAX ^ u4p_a_reqbit[u4_t_lpcnt]);
            u4p_a_reqbit[u4_t_lpcnt] |= u4_t_apprqbit;
        }
    }
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_WCHIME_REQBIT_NUM_WORD; u4_t_lpcnt++){
        u4_s_wchime_apprq_bit[u4_t_lpcnt]   = u4p_a_reqbit[u4_t_lpcnt];
    }

    u1_g_wchime_silencetime_flag = (U1)FALSE;
}
/*===================================================================================================================================*/
/*  static  void    vd_s_wChimeCfgMcReqchk(U4 * u4p_a_reqbit)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_wChimeCfgMWVCReqchk(U4 * u4p_a_reqbit)
{
    U1 u1_t_mwvc_req;

    u1_t_mwvc_req = u1_g_wChimeCfgMWVCReq();

    if(u1_t_mwvc_req == (U1)TRUE){
        vd_s_wChimeCfgReqOn(u4p_a_reqbit, (U1)WCHIME_REQ_SI_MET_WRN_VOL_CSTM);
    }
}
/*===================================================================================================================================*/
/*  static  void    vd_s_wChimeCfgMindspDelchk(U4 * u4p_a_reqbit)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_wChimeCfgMindspDelchk(U4 * u4p_a_reqbit)
{
    U1 u1_t_indsp;

    u1_t_indsp = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_INDSPDALT);

    if(u1_t_indsp == (U1)FALSE){
        vd_s_wChimeCfgReqDel(u4p_a_reqbit, (U1)WCHIME_REQ_SI_MINDSPWR_LV1);
        vd_s_wChimeCfgReqDel(u4p_a_reqbit, (U1)WCHIME_REQ_IN_MINDSPWR_LV2);
    }
}
/*===================================================================================================================================*/
/*  static  void    vd_s_wChimeCfgAppDelchk(U4 * u4p_a_reqbit)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_wChimeCfgAppDelchk(U4 * u4p_a_reqbit)
{
    U1 u1_t_app;

    u1_t_app = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_AUTOP);

    if(u1_t_app == (U1)FALSE){
        vd_s_wChimeCfgReqDel(u4p_a_reqbit, (U1)WCHIME_REQ_SI_APP_DIS_ASSIST);
    }
}
/*===================================================================================================================================*/
/*  static  void    vd_s_wChimeCfgBglfspdDelchk(U4 * u4p_a_reqbit)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_wChimeCfgBglfspdDelchk(U4 * u4p_a_reqbit)
{
    U1 u1_t_bglfspd;

    u1_t_bglfspd = u1_g_VardefMdlLEstWrnByPid();

    if(u1_t_bglfspd == (U1)FALSE){
        vd_s_wChimeCfgReqDel(u4p_a_reqbit, (U1)WCHIME_REQ_IN_BGLFSPD);
    }
}
/*===================================================================================================================================*/
/*  static  void    vd_s_wChimeCfgBlgtDelchk(U4 * u4p_a_reqbit)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_wChimeCfgBlgtDelchk(U4 * u4p_a_reqbit)
{
#if 0   /* BEV Rebase provisionally */
    U4  u4_t_tailcstm;

    u4_t_tailcstm = u4_g_VardefDs2E_Las32((U2)VDF_DS_2E_2041);

    if((u4_t_tailcstm & (U4)VDF_DS_2E_TRWC_EN) == (U4)0U){
        vd_s_wChimeCfgReqDel(u4p_a_reqbit, (U1)WCHIME_REQ_CO_LIGHT);
    }
#endif   /* BEV Rebase provisionally */
}
/*===================================================================================================================================*/
/*  static  void    vd_s_wChimeCfgReqOn(U4 * u4_ap_reqbit, const U1 u1_a_REQ_ID)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_wChimeCfgReqOn(U4 * u4_ap_reqbit, const U1 u1_a_REQ_ID)
{
    U1 u1_t_idx;
    U1 u1_t_pos;

    u1_t_idx = u1_a_REQ_ID >> WCHIME_CNV_IDX;
    u1_t_pos = u1_a_REQ_ID & (U1)WCHIME_CNV_POS;
    u4_ap_reqbit[u1_t_idx] |= ((U4)0x00000001U << u1_t_pos);
}
/*===================================================================================================================================*/
/*  static  void    vd_s_wChimeCfgReqDel(U4 * u4_ap_reqbit, const U1 u1_a_REQ_ID)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_wChimeCfgReqDel(U4 * u4_ap_reqbit, const U1 u1_a_REQ_ID)
{
    U1 u1_t_idx;
    U1 u1_t_pos;

    u1_t_idx = u1_a_REQ_ID >> WCHIME_CNV_IDX;
    u1_t_pos = u1_a_REQ_ID & (U1)WCHIME_CNV_POS;
    u4_ap_reqbit[u1_t_idx] &= ((U4)U4_MAX ^ ((U4)0x00000001U << u1_t_pos));
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/ 2/2018  TN       New.                                                                                               */
/*  1.1.0     3/27/2018  TN       wchime_arb.c v1.0.0 -> v1.1.0.                                                                     */
/*  1.2.0    11/19/2018  TN       wchime_arb.c v1.1.0 -> v1.2.0.                                                                     */
/*  1.3.0     4/ 2/2020  ToN      wchime_arb.c v1.2.0 -> v1.3.0.                                                                     */
/*  1.4.0     7/21/2020  HY       wchime_arb.c v1.3.0 -> v1.4.0.                                                                     */
/*  1.4.1    11/24/2020  TF       wchime_arb.c v1.4.0 -> v1.4.1.                                                                     */
/*  1.5.0    12/23/2020  YK       wchime_arb.c v1.4.1 -> v1.5.0.                                                                     */
/*  2.0.1    10/21/2021  MG       wchime_arb.c v1.5.0 -> v2.0.1.                                                                     */
/*  2.1.0    11/12/2024  GM       wchime_arb.c v2.0.1 -> v2.1.0.                                                                     */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  800B-1    4/ 2/2020  HY       Apply priority order list of buzzer for CV.                                                        */
/*  800B-2    8/28/2020  YK       Apply priority order list of buzzer for CV-R.                                                      */
/*                                Add customization processing for light reminder buzzer.                                            */
/*                                Apply the judgement for SBW reverse buzzer whether target is domestic or not.                      */
/*                                Add TURHAZ Sound Pressure Customization.                                                           */
/*  800B-3   11/24/2020  TF       Add function to read target request from bitmap of request.                                        */
/*  800B-4   12/15/2020  YK       Change the DID of customization for SBW reverse buzzer from 20C1 to 20C2.                          */
/*                                Add function check for RSA buzzer by control standard specification.                               */
/*                                Change the Alert_CH and Alert_REQ for COOTEM.                                                      */
/*                                Apply priority order list of buzzer for 1A.                                                        */
/*  840B-1    6/ 2/2021  MG       Apply priority order list of buzzer for CV.                                                        */
/*                                Change the Alert_CH and Alert_REQ for SMASTA.                                                      */
/*                                Add function check to delete ROLAWA warning buzzer req.                                            */
/*  893B-1    7/ 2/2021  MG       Apply AlertReqList for CV.                                                                         */
/*                                Delete processing for SBW reverse buzzer.                                                          */
/*  893B-2    8/ 3/2021  MG       Apply priority order list of buzzer for CV.                                                        */
/*  460B-1   11/11/2021  MG       Apply priority order list of buzzer for 1A.                                                        */
/*                                Apply AlertReqList for 1A.                                                                         */
/*  893B-3    2/ 2/2022  TA       Add function check to delete EPB warning buzzer req.                                               */
/*  178D-1    4/14/2022  MG       Change the Alert_CH and Alert_REQ for SFTPOS.                                                      */
/*  200D-1    7/19/2022  YK       Apply priority order list of buzzer for Pre1A.                                                     */
/*  200D-2   10/13/2022  YK       Apply priority order list of buzzer for 1A.                                                        */
/*                                Add processing for SBW reverse buzzer.                                                             */
/*  330D-1    1/11/2023  YKu      Apply priority order list of buzzer for CV-R.                                                      */
/*                                Add processing for Check to delete Advanced Park buzzer req.                                       */
/*  330D-2    2/ 2/2023  YK       Apply priority order list of buzzer for CV-R2.                                                     */
/*                                Add processing for Check to delete BGLFSPD warning buzzer req.                                     */
/*  330D-3    3/14/2023  YK       Apply priority order list of buzzer for 1A.                                                        */
/*  330D-4    6/ 1/2023  YK       Apply priority order list of buzzer for MPT.                                                       */
/*  19PFv3-1  9/22/2023  SH       Add a process to separate TURHAZ by brand                                                          */
/*  19PFv3-2 11/23/2023  RO       Add function check for add silencetime Advanced Park buzzer req.                                   */
/*  19PFv3-3 12/27/2023  SI       Add parameter of MET-M_MWVCUS-                                                                     */
/*                                Add vd_s_wChimeCfgMWVCReqchk()                                                                     */
/*  19PFv3-4  1/18/2024  SW       Add parameter of MET-B_SMASTA-                                                                     */
/*                                Delete vd_s_wChimeCfgSmaStaReqchk()                                                                */
/*  19PFv3-5  1/19/2024  YR       Remove buzzer request for BRKHLD                                                                   */
/*  19PFv3-6  1/30/2024  SW       Delete ROM and function for RSA                                                                    */
/*  19PFv3-7  2/ 8/2024  SW       Add parameter of MET-M_MINDSPWR-                                                                   */
/*                                Add vd_s_wChimeCfgMindspDelchk()                                                                   */
/*  19PFv3-8  2/13/2024  SW       Add u1_s_wChimeGetCalibU1DataNumChk()                                                              */
/*  19PFv3-9  2/15/2024  JMH      Added MET-B_BKEY Request                                                                           */
/*  19PFv3-10 2/20/2024  GM       Change config for 19PFv3 CV                                                                        */
/*  19PFv3-11 4/18/2024  T.Nakano Change for MET19PFV3-2977.                                                                         */
/*  19PFv3-12 4/23/2024  TR       Deleted RCTA Volume logic                                                                          */
/*  19PFv3-13 5/13/2024  YR       Change FCTA priority                                                                               */
/*  19PFv3-14 6/27/2024  T.Nakano Delete Calibration Guard Process.                                                                  */
/*  19PFv3-15 7/12/2024  T.Nakano Add Calibration Guard to Unify Vehicle Operation.                                                  */
/*  19PFv3-16 7/10/2024  TR       Add SBRDMB config and function buzzer req.                                                         */
/*  19PFv3-17 9/16/2024  YR       Change config for Master Caution, SBW and Turn Hazard                                              */
/*  19PFv3-18 9/25/2024  GM       Add Shift-By-Wire Judgement in SFTPOS Reject buzzer sounding condition                             */
/*  19PFv3-19 11/12/2024 GM       Add u1_g_wChimeCfgIntermSplCnd() for switching to high priority from intermittent buzzer items     */
/*  19PFv3-20 03/20/2025 SH       Added config for BATTRW                                                                            */
/*  BEV-1     11/11/2025 SH       Configured for CONTBUZZ2-CSTD-0008                                                                 */
/*  BEV-2     11/28/2025 HL       Add parameter of MET-S_TMBZR-CSTD-0-01-A-C0                                                        */
/*  BEV-3     12/10/2025 EA       Added and Changed EDSS of MET-S_ADBZR-CSTD-0-06-A-C0                                               */
/*  BEV-4     12/11/2025 DT       Added TCW of MET-S_ADBZR-CSTD-0-06-A-C0                                                            */
/*  BEV-5     12/12/2025 ED       Deleted function process request for WCHIME_REQ_SI_APP_CMPLT                                       */
/*  BEV-6     12/18/2025 ED       Change Macro name of MET-S_ADBZR-CSTD-0-06-A-C0                                                    */
/*  BEV-7     12/19/2025 KH       Update for BEV System_Consideration_ADAS.(C_TPMS / H_BATTRW)                                       */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * ToN  = Toshiharu Nagata, Denso Techno                                                                                          */
/*  * HY   = Hiroshige Yanase, Denso Techno                                                                                          */
/*  * YK   = Yuki Kawai, Denso Techno                                                                                                */
/*  * TF   = Tomohiro Furuichi, Denso Techno                                                                                         */
/*  * MG   = Mei Godo, KSE                                                                                                           */
/*  * TA   = Takayoshi Asai, Denso Techno                                                                                            */
/*  * YKu  = Yuta Kusunoki, Denso Techno                                                                                             */
/*  * SH   = Sae Hirose, Denso Techno                                                                                                */
/*  * RO   = Ryo Oohashi, Denso Techno                                                                                               */
/*  * SI   = Shugo Ichinose, Denso Techno                                                                                            */
/*  * SW   = Shun Watanabe, Denso Techno                                                                                             */
/*  * YR   = Yhana Regalario, Denso Techno Phil. Inc.                                                                                */
/*  * JMH  = James Michael Hilarion, DTPH                                                                                            */
/*  * GM   = Glen Monteposo, DTPH                                                                                                    */
/*  * TR   = Tebs Ramos, DTPH                                                                                                        */
/*  * T.Nakano   = Tetsushi Nakano, Denso Techno                                                                                     */
/*  * HL   = Harry Lapiceros, DTPH                                                                                                   */
/*  * EA   = Eunice Avelin, DTPH                                                                                                     */
/*  * DT   = Dj Tutanes, DTPH                                                                                                        */
/*  * ED   = Emoh Dagasdas, DTPH                                                                                                     */
/*  * KH   = Kiko Huerte, DTPH                                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/
