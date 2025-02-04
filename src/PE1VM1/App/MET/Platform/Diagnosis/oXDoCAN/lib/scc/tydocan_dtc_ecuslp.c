/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for Toyota MET/HUD based on AUBIST/DEM, DCM                                                                     */
/*  ECU Sleep Diag (Detection of excessive wakeup and sleep ng continuation)                                                         */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_DTC_ECUSLP_C_MAJOR              (1U)
#define TYDOCAN_DTC_ECUSLP_C_MINOR              (0U)
#define TYDOCAN_DTC_ECUSLP_C_PATCH              (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_cfg_private.h"
#include "tydocan_dtc_ecuslp_cfg_private.h"
#include "tydocan_sal.h"
#include "oxdocan_aubif.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (TYDOCAN_DTC_ECUSLP_C_MAJOR != OXDOCAN_CFG_H_MAJOR)
#error "tydocan_dtc_ecuslp.c and oxdocan_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((TYDOCAN_DTC_ECUSLP_C_MAJOR != TYDOCAN_DTC_ECUSLP_H_MAJOR) || \
     (TYDOCAN_DTC_ECUSLP_C_MINOR != TYDOCAN_DTC_ECUSLP_H_MINOR) || \
     (TYDOCAN_DTC_ECUSLP_C_PATCH != TYDOCAN_DTC_ECUSLP_H_PATCH))
#error "tydocan_dtc_ecuslp.c and tydocan_dtc_ecuslp.h : source and header files are inconsistent!"
#endif

#if ((TYDOCAN_DTC_ECUSLP_C_MAJOR != TYDOCAN_DTC_ECUSLP_CFG_H_MAJOR) || \
     (TYDOCAN_DTC_ECUSLP_C_MINOR != TYDOCAN_DTC_ECUSLP_CFG_H_MINOR) || \
     (TYDOCAN_DTC_ECUSLP_C_PATCH != TYDOCAN_DTC_ECUSLP_CFG_H_PATCH))
#error "tydocan_dtc_ecuslp.c and tydocan_dtc_ecuslp_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_ECUSLP_BR_LAS                      (0x5aU)
#define TYDC_ECUSLP_BR_UNK                      (0x00U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_ECUSLP_NUM_STS                     (3U)
#define TYDC_ECUSLP_STS_STB                     (0U)
#define TYDC_ECUSLP_STS_RUN                     (1U)
#define TYDC_ECUSLP_STS_INA                     (2U)

#define TYDC_ECUSLP_ACT_TO_RUN_INI              (0U)
#define TYDC_ECUSLP_ACT_TO_RUN_CYC              (1U)
#define TYDC_ECUSLP_ACT_TO_RUN                  (2U)
#define TYDC_ECUSLP_ACT_TO_INA_WLU              (3U)       /* Wake-up Log is updated    */
#define TYDC_ECUSLP_ACT_TO_INA                  (4U)
#define TYDC_ECUSLP_ACT_RUN                     (5U)

#define TYDC_ECUSLP_EAS_CHK_SL_TOUT             (0x01U)
#define TYDC_ECUSLP_EAS_CHK_WK_TOUT             (0x02U)
#define TYDC_ECUSLP_EAS_CHK_GE_WKCT             (0x04U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_ECUSLP_SS_STS_NONE                 (0U)
#define TYDC_ECUSLP_SS_STS_DETECT               (1U)
#define TYDC_ECUSLP_SS_STS_NOTICE               (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U2              u2_cnt;
    U1              u1_last;
    volatile U1     u1_valid;
}ST_TYDC_ECUSLP_WKM;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_TYDC_ECUSLP_WKM   st_s_tydc_ecuslp_br     __attribute__((section(".bss_BACK")));

static ST_TYDC_ECUSLP_WKM   st_s_tydc_ecuslp_wkm;
static U4                   u4_s_tydc_ecuslp_slm_elpsd;
static U2                   u2_s_tydc_ecuslp_ina_tout;
static U1                   u1_s_tydc_ecuslp_ctrl;

static U4                   u4_sp_tydc_ecuslp_ss_capt[TYDC_DTC_ECUSLP_NUM_SS];
static U1                   u1_sp_tydc_ecuslp_ss_sts[TYDC_DTC_ECUSLP_NUM_SS];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2       u2_s_TydcDtcEcuSlpEaschk_Stb(const U2 u2_a_RUN, const U4 u4_a_SNGF);
static U2       u2_s_TydcDtcEcuSlpEaschk_Run(const U2 u2_a_RUN, const U4 u4_a_SNGF);
static U2       u2_s_TydcDtcEcuSlpEaschk_Wkm(void);

static void     vd_s_TydcDtcEcuSlpActToRunIni(const U2 u2_a_EAS_CHK, const U4 u4_a_SNGF);
static void     vd_s_TydcDtcEcuSlpActToRunCyc(const U2 u2_a_EAS_CHK, const U4 u4_a_SNGF);
static void     vd_s_TydcDtcEcuSlpActToRun(const U2 u2_a_EAS_CHK, const U4 u4_a_SNGF);
static void     vd_s_TydcDtcEcuSlpActToInaWlu(const U2 u2_a_EAS_CHK, const U4 u4_a_SNGF);
static void     vd_s_TydcDtcEcuSlpActToIna(const U2 u2_a_EAS_CHK, const U4 u4_a_SNGF);

static void     vd_s_TydcDtcEcuSlpWkmInit(const U1 u1_a_BR_VALID);
static void     vd_s_TydcDtcEcuSlpWkmCapt(void);
static void     vd_s_TydcDtcEcuSlpWkmElpsd(void);
static void     vd_s_TydcDtcEcuSlpSsCapt_U2A00(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcEcuSlpBonInit(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcEcuSlpBonInit(void)
{
    vd_g_TyDoCANDtcEcuSlpCfgWake((U1)FALSE);

    vd_s_TydcDtcEcuSlpWkmInit((U1)TYDC_ECUSLP_BR_LAS);
    u1_s_tydc_ecuslp_ctrl      = (U1)TYDC_ECUSLP_STS_INA;

    u4_s_tydc_ecuslp_slm_elpsd = (U4)0U;
    u2_s_tydc_ecuslp_ina_tout  = (U2)U2_MAX;

    u4_sp_tydc_ecuslp_ss_capt[TYDC_DTC_ECUSLP_SS_U2A00] = (U4)0U;
    u4_sp_tydc_ecuslp_ss_capt[TYDC_DTC_ECUSLP_SS_U2A01] = (U4)0U;
    u1_sp_tydc_ecuslp_ss_sts[TYDC_DTC_ECUSLP_SS_U2A00]  = (U1)TYDC_ECUSLP_SS_STS_NONE;
    u1_sp_tydc_ecuslp_ss_sts[TYDC_DTC_ECUSLP_SS_U2A01]  = (U1)TYDC_ECUSLP_SS_STS_NONE;
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcEcuSlpWkupInit(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcEcuSlpWkupInit(void)
{
    U1      u1_t_valid;

    u1_t_valid = st_s_tydc_ecuslp_br.u1_valid;
    if(u1_t_valid == (U1)TYDC_ECUSLP_BR_LAS){

        vd_g_TyDoCANDtcEcuSlpCfgWake((U1)TRUE);

        st_s_tydc_ecuslp_wkm.u2_cnt   = st_s_tydc_ecuslp_br.u2_cnt;
        st_s_tydc_ecuslp_wkm.u1_last  = st_s_tydc_ecuslp_br.u1_last;
        st_s_tydc_ecuslp_wkm.u1_valid = (U1)TYDC_ECUSLP_BR_LAS;

        u1_s_tydc_ecuslp_ctrl         = (U1)TYDC_ECUSLP_STS_STB;

        u4_s_tydc_ecuslp_slm_elpsd = (U4)0U;
        u2_s_tydc_ecuslp_ina_tout  = (U2)U2_MAX;

        u4_sp_tydc_ecuslp_ss_capt[TYDC_DTC_ECUSLP_SS_U2A00] = (U4)0U;
        u4_sp_tydc_ecuslp_ss_capt[TYDC_DTC_ECUSLP_SS_U2A01] = (U4)0U;
        u1_sp_tydc_ecuslp_ss_sts[TYDC_DTC_ECUSLP_SS_U2A00]  = (U1)TYDC_ECUSLP_SS_STS_NONE;
        u1_sp_tydc_ecuslp_ss_sts[TYDC_DTC_ECUSLP_SS_U2A01]  = (U1)TYDC_ECUSLP_SS_STS_NONE;
    }
    else{
        vd_g_TyDoCANDtcEcuSlpBonInit();
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcEcuSlpRstInit(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcEcuSlpRstInit(void)
{
    U1      u1_t_valid;

    u1_t_valid = st_s_tydc_ecuslp_br.u1_valid;
    if(u1_t_valid   == (U1)TYDC_ECUSLP_BR_LAS){

        vd_g_TyDoCANDtcEcuSlpCfgWake((U1)FALSE);

        st_s_tydc_ecuslp_wkm.u2_cnt   = st_s_tydc_ecuslp_br.u2_cnt;
        st_s_tydc_ecuslp_wkm.u1_last  = st_s_tydc_ecuslp_br.u1_last;
        st_s_tydc_ecuslp_wkm.u1_valid = (U1)TYDC_ECUSLP_BR_LAS;

        u1_s_tydc_ecuslp_ctrl         = (U1)TYDC_ECUSLP_STS_STB;

        u4_s_tydc_ecuslp_slm_elpsd = (U4)0U;
        u2_s_tydc_ecuslp_ina_tout  = (U2)U2_MAX;

        u4_sp_tydc_ecuslp_ss_capt[TYDC_DTC_ECUSLP_SS_U2A00] = (U4)0U;
        u4_sp_tydc_ecuslp_ss_capt[TYDC_DTC_ECUSLP_SS_U2A01] = (U4)0U;
        u1_sp_tydc_ecuslp_ss_sts[TYDC_DTC_ECUSLP_SS_U2A00]  = (U1)TYDC_ECUSLP_SS_STS_NONE;
        u1_sp_tydc_ecuslp_ss_sts[TYDC_DTC_ECUSLP_SS_U2A01]  = (U1)TYDC_ECUSLP_SS_STS_NONE;
    }
    else{
        vd_g_TyDoCANDtcEcuSlpBonInit();
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcEcuSlpMainTask(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcEcuSlpMainTask(void)
{
    static const U1          u1_sp_TYDC_ECUSLP_STM[] = {
        (U1)TYDC_ECUSLP_ACT_TO_RUN,     (U1)TYDC_ECUSLP_ACT_RUN,        (U1)TYDC_ECUSLP_ACT_TO_RUN_INI,
        (U1)TYDC_ECUSLP_ACT_TO_RUN,     (U1)TYDC_ECUSLP_ACT_TO_INA,     (U1)TYDC_ECUSLP_ACT_TO_RUN_INI,
        (U1)TYDC_ECUSLP_ACT_TO_RUN_INI, (U1)TYDC_ECUSLP_ACT_TO_RUN_CYC, (U1)TYDC_ECUSLP_ACT_TO_RUN_INI,
        (U1)TYDC_ECUSLP_ACT_TO_RUN,     (U1)TYDC_ECUSLP_ACT_TO_INA,     (U1)TYDC_ECUSLP_ACT_TO_RUN_INI,
        (U1)TYDC_ECUSLP_ACT_TO_INA_WLU, (U1)TYDC_ECUSLP_ACT_TO_INA,     (U1)TYDC_ECUSLP_ACT_TO_RUN_INI,
        (U1)TYDC_ECUSLP_ACT_TO_INA_WLU, (U1)TYDC_ECUSLP_ACT_TO_INA,     (U1)TYDC_ECUSLP_ACT_TO_RUN_INI
    };

    static U2   ( * const    fp_sp_u2_TYDC_ECUSLP_EAS_CHK[])(const U2 u2_a_RUN, const U4 u4_a_SNGF) = {
        &u2_s_TydcDtcEcuSlpEaschk_Stb,      /* TYDC_ECUSLP_STS_STB        (0U) */
        &u2_s_TydcDtcEcuSlpEaschk_Run       /* TYDC_ECUSLP_STS_RUN        (1U) */
    };

    static void ( * const    fp_sp_vd_TYDC_ECUSLP_ACT[])(const U2 u2_a_EAS_CHK, const U4 u4_a_SNGF) = {
        &vd_s_TydcDtcEcuSlpActToRunIni,     /* TYDC_ECUSLP_ACT_TO_RUN_INI (0U) */
        &vd_s_TydcDtcEcuSlpActToRunCyc,     /* TYDC_ECUSLP_ACT_TO_RUN_CYC (1U) */
        &vd_s_TydcDtcEcuSlpActToRun,        /* TYDC_ECUSLP_ACT_TO_RUN     (2U) */
        &vd_s_TydcDtcEcuSlpActToInaWlu,     /* TYDC_ECUSLP_ACT_TO_INA_WLU (3U) */
        &vd_s_TydcDtcEcuSlpActToIna         /* TYDC_ECUSLP_ACT_TO_INA     (4U) */
                                            /* TYDC_ECUSLP_ACT_RUN        (5U) */
    };

    U4      u4_t_sngf;
    U2      u2_t_eas_chk;
    U2      u2_t_act;
    U1      u1_t_act;

    if(u2_s_tydc_ecuslp_ina_tout < (U2)U2_MAX){
        u2_s_tydc_ecuslp_ina_tout++;
    }

    if((u1_s_tydc_ecuslp_ctrl == (U1)TYDC_ECUSLP_STS_STB) ||
       (u1_s_tydc_ecuslp_ctrl == (U1)TYDC_ECUSLP_STS_RUN)){
        u1_t_act  = u1_g_TyDoCANDtcEcuSlpCfgWkmAct((U1)TRUE);
    }
    else{
        u1_t_act  = u1_g_TyDoCANDtcEcuSlpCfgWkmAct((U1)FALSE);
    }

    if((u1_t_act                  != (U1)TRUE                     ) ||
       (u1_s_tydc_ecuslp_ctrl     >= (U1)TYDC_ECUSLP_NUM_STS      ) ||
       (u2_s_tydc_ecuslp_ina_tout <  u2_g_TYDC_DTC_ECUSLP_INA_TOUT)){
        u1_s_tydc_ecuslp_ctrl = (U1)TYDC_ECUSLP_STS_INA;
    }
    else{

        u2_t_eas_chk  = (U2)0U;
        if(u1_s_tydc_ecuslp_ctrl < (U1)TYDC_ECUSLP_STS_INA){

            u4_t_sngf     = u4_g_TyDoCANDtcEcuSlpCfgSngfChk();
            u2_t_eas_chk  = (*fp_sp_u2_TYDC_ECUSLP_EAS_CHK[u1_s_tydc_ecuslp_ctrl])(u2_t_eas_chk, u4_t_sngf);
        }
        else{
            u4_t_sngf     = (U4)0x00U;
        }

        u2_t_act = (u2_t_eas_chk * (U2)TYDC_ECUSLP_NUM_STS) + (U2)u1_s_tydc_ecuslp_ctrl;
        u2_t_act = (U2)u1_sp_TYDC_ECUSLP_STM[u2_t_act];
        if(u2_t_act < (U2)TYDC_ECUSLP_ACT_RUN){
            (*fp_sp_vd_TYDC_ECUSLP_ACT[u2_t_act])(u2_t_eas_chk, u4_t_sngf);
        }
        else{
            vd_s_TydcDtcEcuSlpWkmElpsd();
        }
    }

    if(u2_s_tydc_ecuslp_ina_tout < u2_g_TYDC_DTC_ECUSLP_INA_TOUT){
        vd_g_TyDoCANDtcEcuSlpRcvryEvhk(u2_s_tydc_ecuslp_ina_tout);
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANDtcEcuSlpTmrwkImmdwn(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANDtcEcuSlpTmrwkImmdwn(void)
{
    U4      u4_t_elpsd;
    U2      u2_t_wk_cnt;
    U1      u1_t_valid;
    U1      u1_t_shtdwn;

    u1_t_valid = st_s_tydc_ecuslp_br.u1_valid;
    if(u1_t_valid != (U1)TYDC_ECUSLP_BR_LAS){

        vd_g_DateclkEtmStart(u1_g_TYDC_DTC_ECUSLP_DCT_CH, (U4)0U);

        st_s_tydc_ecuslp_br.u2_cnt   = (U2)0U;
        st_s_tydc_ecuslp_br.u1_last  = (U1)U1_MAX;
        st_s_tydc_ecuslp_br.u1_valid = (U1)TYDC_ECUSLP_BR_LAS;

        u1_t_shtdwn = (U1)TRUE;
    }
    else{

        u2_t_wk_cnt = st_s_tydc_ecuslp_br.u2_cnt;
        u4_t_elpsd  = u4_g_DateclkEtmElapsed(u1_g_TYDC_DTC_ECUSLP_DCT_CH);
        if(u4_t_elpsd < u4_g_TYDC_DTC_ECUSLP_WKM_TOUT){
            u1_t_shtdwn = (U1)TRUE;
        }
        else if(u2_t_wk_cnt >= u2_g_TYDC_DTC_ECUSLP_WKC_THRSH){
            u1_t_shtdwn = (U1)FALSE;
        }
        else{

            vd_g_DateclkEtmStart(u1_g_TYDC_DTC_ECUSLP_DCT_CH, (U4)0U);

            st_s_tydc_ecuslp_br.u2_cnt   = (U2)0U;
            st_s_tydc_ecuslp_br.u1_last  = (U1)U1_MAX;
            st_s_tydc_ecuslp_br.u1_valid = (U1)TYDC_ECUSLP_BR_LAS;

            u1_t_shtdwn = (U1)TRUE;
        }
    }

    return(u1_t_shtdwn);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDtcTrchk_U2A00(const U2 u2_a_ELPSD)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDtcTrchk_U2A00(const U2 u2_a_ELPSD)
{
    U4      u4_t_wkf;
    U1      u1_t_wkf_sts;
    U1      u1_t_capt;

    u4_t_wkf = u4_sp_tydc_ecuslp_ss_capt[TYDC_DTC_ECUSLP_SS_U2A00];
    u1_t_wkf_sts = u1_sp_tydc_ecuslp_ss_sts[TYDC_DTC_ECUSLP_SS_U2A00];

    if((u4_t_wkf != (U4)0U) && (u1_t_wkf_sts == (U1)TYDC_ECUSLP_SS_STS_DETECT)){
        u1_t_capt   = (U1)OXDC_DTC_TR_ACT;
        u1_sp_tydc_ecuslp_ss_sts[TYDC_DTC_ECUSLP_SS_U2A00] = (U1)TYDC_ECUSLP_SS_STS_NOTICE;
    }
    else{
        u1_t_capt   = (U1)OXDC_DTC_TR_INA;
    }

    return(u1_t_capt);
}
/*===================================================================================================================================*/
/*  uint8   u1_g_oXDoCANAubIfEcuWkf(uint8 * u1_ap_wkf, Dem_MonitorDataType u4_a_mon)                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
#if (DEM_READFUNC_MONITORDATA_SUPPORT == STD_ON)
uint8   u1_g_oXDoCANAubIfEcuWkf(uint8 * u1_ap_wkf, Dem_MonitorDataType u4_a_mon)
#else
uint8   u1_g_oXDoCANAubIfEcuWkf(uint8 * u1_ap_wkf)
#endif
{
    U4      u4_t_wkf;
    U1      u1_t_wkf_sts;
    U1      u1_tp_src[TYDC_DTC_ECUSLP_WKF_NBYTE];
    U1 *    u1_tp_dst;
    U4      u4_t_lpcnt;

    if(u1_ap_wkf != vdp_PTR_NA){

        u1_t_wkf_sts = u1_sp_tydc_ecuslp_ss_sts[TYDC_DTC_ECUSLP_SS_U2A00];
        if(u1_t_wkf_sts != (U1)TYDC_ECUSLP_SS_STS_NONE){
            u4_t_wkf = u4_sp_tydc_ecuslp_ss_capt[TYDC_DTC_ECUSLP_SS_U2A00];
        }
        else{
            u4_t_wkf = (U4)0U;
        }
        vd_g_TyDoCANDtcEcuSlpCfgWkfTx(u4_t_wkf, &u1_tp_src[0]);
        u1_tp_dst = &u1_ap_wkf[0];
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)OXDC_DATA_REA_ANS_NB_AC20; u4_t_lpcnt++){
            u1_tp_dst[u4_t_lpcnt] = u1_tp_src[u4_t_lpcnt];
        }
    }

    return((Std_ReturnType)E_OK);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDtcTrchk_U2A01(const U2 u2_a_ELPSD)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDtcTrchk_U2A01(const U2 u2_a_ELPSD)
{
    U4      u4_t_wkf;
    U1      u1_t_wkf_sts;
    U1      u1_t_capt;

    u4_t_wkf = u4_sp_tydc_ecuslp_ss_capt[TYDC_DTC_ECUSLP_SS_U2A01];
    u1_t_wkf_sts = u1_sp_tydc_ecuslp_ss_sts[TYDC_DTC_ECUSLP_SS_U2A01];

    if((u4_t_wkf != (U4)0U) && (u1_t_wkf_sts == (U1)TYDC_ECUSLP_SS_STS_DETECT)){
        u1_t_capt   = (U1)OXDC_DTC_TR_ACT;
        u1_sp_tydc_ecuslp_ss_sts[TYDC_DTC_ECUSLP_SS_U2A01] = (U1)TYDC_ECUSLP_SS_STS_NOTICE;
    }
    else{
        u1_t_capt   = (U1)OXDC_DTC_TR_INA;
    }

    return(u1_t_capt);
}
/*===================================================================================================================================*/
/*  uint8   u1_g_oXDoCANAubIfEcuSngf(uint8 * u1_ap_sngf, Dem_MonitorDataType u4_a_mon)                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
#if (DEM_READFUNC_MONITORDATA_SUPPORT == STD_ON)
uint8   u1_g_oXDoCANAubIfEcuSngf(uint8 * u1_ap_sngf, Dem_MonitorDataType u4_a_mon)
#else
uint8   u1_g_oXDoCANAubIfEcuSngf(uint8 * u1_ap_sngf)
#endif
{
    U4      u4_t_wkf;
    U1      u1_t_wkf_sts;
    U1      u1_tp_src[TYDC_DTC_ECUSLP_WKF_NBYTE];
    U1 *    u1_tp_dst;
    U4      u4_t_lpcnt;

    if(u1_ap_sngf != vdp_PTR_NA){

        u1_t_wkf_sts = u1_sp_tydc_ecuslp_ss_sts[TYDC_DTC_ECUSLP_SS_U2A01];
        if(u1_t_wkf_sts != (U1)TYDC_ECUSLP_SS_STS_NONE){
            u4_t_wkf = u4_sp_tydc_ecuslp_ss_capt[TYDC_DTC_ECUSLP_SS_U2A01];
        }
        else{
            u4_t_wkf = (U4)0U;
        }
        vd_g_TyDoCANDtcEcuSlpCfgWkfTx(u4_t_wkf, &u1_tp_src[0]);
        u1_tp_dst = &u1_ap_sngf[0];
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)OXDC_DATA_REA_ANS_NB_AC21; u4_t_lpcnt++){
            u1_tp_dst[u4_t_lpcnt] = u1_tp_src[u4_t_lpcnt];
        }
    }

    return((Std_ReturnType)E_OK);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDtcUdmDelEcuSlp(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDtcUdmDelEcuSlp(void)
{
    vd_g_TyDoCANDtcEcuSlpBonInit();
    return((U1)OXDC_DTC_UDM_DEL_OK);
}
/*===================================================================================================================================*/
/*  static U2      u2_s_TydcDtcEcuSlpEaschk_Stb(const U2 u2_a_RUN, const U4 u4_a_SNGF)                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2      u2_s_TydcDtcEcuSlpEaschk_Stb(const U2 u2_a_RUN, const U4 u4_a_SNGF)
{
    U4      u4_t_elpsd;

    u4_t_elpsd = u4_g_DateclkEtmElapsed(u1_g_TYDC_DTC_ECUSLP_DCT_CH);
    if((u4_a_SNGF                    != (U4)0U                       ) &&
       (u4_t_elpsd                   <= u4_g_TYDC_DTC_ECUSLP_WKM_TOUT) &&
       (st_s_tydc_ecuslp_wkm.u2_cnt  <  (U2)U2_MAX                   )){

       st_s_tydc_ecuslp_wkm.u2_cnt++;
   }

    u4_s_tydc_ecuslp_slm_elpsd = (U4)0U;

    return(u2_s_TydcDtcEcuSlpEaschk_Wkm());
}
/*===================================================================================================================================*/
/*  static U2      u2_s_TydcDtcEcuSlpEaschk_Run(const U2 u2_a_RUN, const U4 u4_a_SNGF)                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2      u2_s_TydcDtcEcuSlpEaschk_Run(const U2 u2_a_RUN, const U4 u4_a_SNGF)
{
    static const U4     u4_s_TYDC_DTC_ECUSLP_SLM_MAX = (U4)U4_MAX - ((U4)OXDC_MAIN_TICK << 1U);
    U2                  u2_t_eas_chk;

    if(u4_a_SNGF == (U4)0U){
        u4_s_tydc_ecuslp_slm_elpsd = (U4)0U;
    }
    else if(u4_s_tydc_ecuslp_slm_elpsd < u4_s_TYDC_DTC_ECUSLP_SLM_MAX){
        u4_s_tydc_ecuslp_slm_elpsd += (U4)OXDC_MAIN_TICK;
    }
    else{
        /* Do Nothing */
    }

    if(u4_s_tydc_ecuslp_slm_elpsd >= u4_g_TYDC_DTC_ECUSLP_SLM_TOUT){
        u2_t_eas_chk = u2_s_TydcDtcEcuSlpEaschk_Wkm() | (U2)TYDC_ECUSLP_EAS_CHK_SL_TOUT;
    }
    else{
        u2_t_eas_chk = u2_s_TydcDtcEcuSlpEaschk_Wkm();
    }

    return(u2_t_eas_chk);
}
/*===================================================================================================================================*/
/*  static U2      u2_s_TydcDtcEcuSlpEaschk_Wkm(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2      u2_s_TydcDtcEcuSlpEaschk_Wkm(void)
{
    U4      u4_t_elpsd;
    U2      u2_t_eas_chk;

    u4_t_elpsd = u4_g_DateclkEtmElapsed(u1_g_TYDC_DTC_ECUSLP_DCT_CH);
    if(u4_t_elpsd < u4_g_TYDC_DTC_ECUSLP_WKM_TOUT){
        u2_t_eas_chk = (U2)0U;
    }
    else if(st_s_tydc_ecuslp_wkm.u2_cnt >= u2_g_TYDC_DTC_ECUSLP_WKC_THRSH){
        u2_t_eas_chk = (U2)TYDC_ECUSLP_EAS_CHK_GE_WKCT;
    }
    else{
        u2_t_eas_chk = (U2)TYDC_ECUSLP_EAS_CHK_WK_TOUT;
    }

    return(u2_t_eas_chk);
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDtcEcuSlpActToRunIni(const U2 u2_a_EAS_CHK, const U4 u4_a_SNGF)                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDtcEcuSlpActToRunIni(const U2 u2_a_EAS_CHK, const U4 u4_a_SNGF)
{
    vd_s_TydcDtcEcuSlpWkmInit((U1)TYDC_ECUSLP_BR_LAS);
    u4_s_tydc_ecuslp_slm_elpsd = (U4)0U;
    u1_s_tydc_ecuslp_ctrl      = (U1)TYDC_ECUSLP_STS_RUN;
    u4_sp_tydc_ecuslp_ss_capt[TYDC_DTC_ECUSLP_SS_U2A00]  = (U1)0U;
    u4_sp_tydc_ecuslp_ss_capt[TYDC_DTC_ECUSLP_SS_U2A01]  = (U1)0U;
    u1_sp_tydc_ecuslp_ss_sts[TYDC_DTC_ECUSLP_SS_U2A00]   = (U1)TYDC_ECUSLP_SS_STS_NONE;
    u1_sp_tydc_ecuslp_ss_sts[TYDC_DTC_ECUSLP_SS_U2A01]   = (U1)TYDC_ECUSLP_SS_STS_NONE;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDtcEcuSlpActToRunCyc(const U2 u2_a_EAS_CHK, const U4 u4_a_SNGF)                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDtcEcuSlpActToRunCyc(const U2 u2_a_EAS_CHK, const U4 u4_a_SNGF)
{
    vd_s_TydcDtcEcuSlpWkmInit((U1)TYDC_ECUSLP_BR_LAS);
 /* u4_s_tydc_ecuslp_slm_elpsd = (U4)0U; */ /* This statement are intentiolally commented out */
    u1_s_tydc_ecuslp_ctrl      = (U1)TYDC_ECUSLP_STS_RUN;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDtcEcuSlpActToRun(const U2 u2_a_EAS_CHK, const U4 u4_a_SNGF)                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDtcEcuSlpActToRun(const U2 u2_a_EAS_CHK, const U4 u4_a_SNGF)
{
    vd_s_TydcDtcEcuSlpWkmCapt();
    u4_s_tydc_ecuslp_slm_elpsd = (U4)0U;
    u1_s_tydc_ecuslp_ctrl      = (U1)TYDC_ECUSLP_STS_RUN;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDtcEcuSlpActToInaWlu(const U2 u2_a_EAS_CHK, const U4 u4_a_SNGF)                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDtcEcuSlpActToInaWlu(const U2 u2_a_EAS_CHK, const U4 u4_a_SNGF)
{
    vd_s_TydcDtcEcuSlpWkmCapt();
    vd_s_TydcDtcEcuSlpSsCapt_U2A00();

    vd_s_TydcDtcEcuSlpWkmInit((U1)TYDC_ECUSLP_BR_UNK);

    u4_s_tydc_ecuslp_slm_elpsd = (U4)0U;
    u2_s_tydc_ecuslp_ina_tout  = (U2)0U;
    u1_s_tydc_ecuslp_ctrl      = (U1)TYDC_ECUSLP_STS_INA;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDtcEcuSlpActToIna(const U2 u2_a_EAS_CHK, const U4 u4_a_SNGF)                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDtcEcuSlpActToIna(const U2 u2_a_EAS_CHK, const U4 u4_a_SNGF)
{
    U2      u2_t_capt;

    u2_t_capt = u2_a_EAS_CHK & ((U2)TYDC_ECUSLP_EAS_CHK_SL_TOUT | (U2)TYDC_ECUSLP_EAS_CHK_GE_WKCT);
    if(u2_t_capt == ((U2)TYDC_ECUSLP_EAS_CHK_SL_TOUT | (U2)TYDC_ECUSLP_EAS_CHK_GE_WKCT)){
        vd_s_TydcDtcEcuSlpSsCapt_U2A00();
        u4_sp_tydc_ecuslp_ss_capt[TYDC_DTC_ECUSLP_SS_U2A01] = u4_a_SNGF;
        u1_sp_tydc_ecuslp_ss_sts[TYDC_DTC_ECUSLP_SS_U2A01]  = (U1)TYDC_ECUSLP_SS_STS_DETECT;
    }
    else if(u2_t_capt == (U2)TYDC_ECUSLP_EAS_CHK_SL_TOUT){
        u4_sp_tydc_ecuslp_ss_capt[TYDC_DTC_ECUSLP_SS_U2A01] = u4_a_SNGF;
        u1_sp_tydc_ecuslp_ss_sts[TYDC_DTC_ECUSLP_SS_U2A01]  = (U1)TYDC_ECUSLP_SS_STS_DETECT;
    }
    else if(u2_t_capt == (U2)TYDC_ECUSLP_EAS_CHK_GE_WKCT){
        vd_s_TydcDtcEcuSlpSsCapt_U2A00();
    }
    else{
        /* Do Nothing */
    }

    vd_s_TydcDtcEcuSlpWkmInit((U1)TYDC_ECUSLP_BR_UNK);

    u4_s_tydc_ecuslp_slm_elpsd = (U4)0U;
    u2_s_tydc_ecuslp_ina_tout  = (U2)0U;
    u1_s_tydc_ecuslp_ctrl      = (U1)TYDC_ECUSLP_STS_INA;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDtcEcuSlpWkmInit(const U1 u1_a_BR_VALID)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDtcEcuSlpWkmInit(const U1 u1_a_BR_VALID)
{
    U4      u4_t_lpcnt;

    vd_g_DateclkEtmStart(u1_g_TYDC_DTC_ECUSLP_DCT_CH, (U4)0U);

    st_s_tydc_ecuslp_br.u1_valid  = (U1)TYDC_ECUSLP_BR_UNK;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < u1_g_TYDC_DTC_ECUSLP_NUM_LOG; u4_t_lpcnt++){
        u4_gp_tydc_dtc_ecuslp_log_wk[u4_t_lpcnt] = (U4)0U;
    }

    st_s_tydc_ecuslp_br.u2_cnt    = (U2)0U;
    st_s_tydc_ecuslp_br.u1_last   = (U1)U1_MAX;

    st_s_tydc_ecuslp_br.u1_valid  = u1_a_BR_VALID;

    st_s_tydc_ecuslp_wkm.u2_cnt   = (U2)0U;
    st_s_tydc_ecuslp_wkm.u1_last  = (U1)U1_MAX;
    st_s_tydc_ecuslp_wkm.u1_valid = (U1)TYDC_ECUSLP_BR_LAS;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDtcEcuSlpWkmCapt(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDtcEcuSlpWkmCapt(void)
{
    U4      u4_t_wkf;

    if(st_s_tydc_ecuslp_wkm.u2_cnt > st_s_tydc_ecuslp_br.u2_cnt){

        if(st_s_tydc_ecuslp_wkm.u1_last >= u1_g_TYDC_DTC_ECUSLP_NUM_LOG){
            st_s_tydc_ecuslp_wkm.u1_last = (U1)0U;
        }

        u4_t_wkf = u4_g_TyDoCANDtcEcuSlpCfgWkfChk();
        u4_gp_tydc_dtc_ecuslp_log_wk[st_s_tydc_ecuslp_wkm.u1_last] = u4_t_wkf;
        st_s_tydc_ecuslp_wkm.u1_last++;
    }

    st_s_tydc_ecuslp_br.u1_valid = (U1)TYDC_ECUSLP_BR_UNK;

    st_s_tydc_ecuslp_br.u2_cnt   = st_s_tydc_ecuslp_wkm.u2_cnt;
    st_s_tydc_ecuslp_br.u1_last  = st_s_tydc_ecuslp_wkm.u1_last;

    st_s_tydc_ecuslp_br.u1_valid = (U1)TYDC_ECUSLP_BR_LAS;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDtcEcuSlpWkmElpsd(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDtcEcuSlpWkmElpsd(void)
{
    st_s_tydc_ecuslp_br.u1_valid = (U1)TYDC_ECUSLP_BR_UNK;
    st_s_tydc_ecuslp_br.u2_cnt   = st_s_tydc_ecuslp_wkm.u2_cnt;
    st_s_tydc_ecuslp_br.u1_valid = (U1)TYDC_ECUSLP_BR_LAS;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDtcEcuSlpSsCapt_U2A00(void)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDtcEcuSlpSsCapt_U2A00(void)
{
    U4      u4_t_lpcnt;
    U4      u4_t_wkf;

    u4_t_wkf     = (U4)0U;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_TYDC_DTC_ECUSLP_NUM_LOG; u4_t_lpcnt++){
        u4_t_wkf |= u4_gp_tydc_dtc_ecuslp_log_wk[u4_t_lpcnt];
    }
    u4_sp_tydc_ecuslp_ss_capt[TYDC_DTC_ECUSLP_SS_U2A00] = u4_t_wkf;
    u1_sp_tydc_ecuslp_ss_sts[TYDC_DTC_ECUSLP_SS_U2A00]  = (U1)TYDC_ECUSLP_SS_STS_DETECT;
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     2/4/2022  AS       New.                                                                                                */
/*                                                                                                                                   */
/*  * AS = Atsunori Sugita, DENSO Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
