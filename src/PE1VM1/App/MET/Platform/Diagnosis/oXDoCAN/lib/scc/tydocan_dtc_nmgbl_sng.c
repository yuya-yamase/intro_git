/* 1.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for Toyota MET/HUD based on AUBIST/DEM, DCM                                                                     */
/*  NM Diag  Detection of abnormal global-ecu (Detection of sleep ng continuation)                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_DTC_NMGBL_SNG_C_MAJOR           (1U)
#define TYDOCAN_DTC_NMGBL_SNG_C_MINOR           (0U)
#define TYDOCAN_DTC_NMGBL_SNG_C_PATCH           (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_cfg_private.h"
#include "tydocan_dtc_nmgbl.h"
#include "tydocan_dtc_nmgbl_cfg_private.h"
#include "oxdocan_aubif.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (TYDOCAN_DTC_NMGBL_SNG_C_MAJOR != OXDOCAN_CFG_H_MAJOR)
#error "tydocan_dtc_nmgbl_sng.c and oxdocan_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((TYDOCAN_DTC_NMGBL_SNG_C_MAJOR != TYDOCAN_DTC_NMGBL_H_MAJOR) || \
     (TYDOCAN_DTC_NMGBL_SNG_C_MINOR != TYDOCAN_DTC_NMGBL_H_MINOR) || \
     (TYDOCAN_DTC_NMGBL_SNG_C_PATCH != TYDOCAN_DTC_NMGBL_H_PATCH))
#error "tydocan_dtc_nmgbl_sng.c and tydocan_dtc_nmgbl.h : source and header files are inconsistent!"
#endif

#if ((TYDOCAN_DTC_NMGBL_SNG_C_MAJOR != TYDOCAN_DTC_NMGBL_CFG_H_MAJOR) || \
     (TYDOCAN_DTC_NMGBL_SNG_C_MINOR != TYDOCAN_DTC_NMGBL_CFG_H_MINOR) || \
     (TYDOCAN_DTC_NMGBL_SNG_C_PATCH != TYDOCAN_DTC_NMGBL_CFG_H_PATCH))
#error "tydocan_dtc_nmgbl_sng.c and tydocan_dtc_nmgbl_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_NMGBL_SNG_NUM_STS                  (3U)
#define TYDC_NMGBL_SNG_STS_STB                  (0U)
#define TYDC_NMGBL_SNG_STS_RUN                  (1U)
#define TYDC_NMGBL_SNG_STS_INA                  (2U)

#define TYDC_NMGBL_SNG_ACT_TO_STB               (0U)
#define TYDC_NMGBL_SNG_ACT_TO_RUN               (1U)
#define TYDC_NMGBL_SNG_ACT_TO_INA               (2U)
#define TYDC_NMGBL_SNG_ACT_STB                  (3U)
#define TYDC_NMGBL_SNG_ACT_RUN                  (4U)
#define TYDC_NMGBL_SNG_ACT_INA                  (5U)

#define TYDC_NMGBL_SNG_EAS_CHK_PWR_ACT          (0x04U)
#define TYDC_NMGBL_SNG_EAS_CHK_SL_TOUT          (0x02U)
#define TYDC_NMGBL_SNG_EAS_CHK_SSR_END          (0x01U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U1      u1_nm;
    U1      u1_diag;
    U1      u1_nm_ch;
    U1      u1_diag_ch;
}ST_TYDC_NMGBL_SNG_CANID;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_TYDC_NMGBL_SNG_CANID  st_sp_tydc_nmgbl_sng_log[TYDC_DTC_NMGBL_SNGF_NUM];

static U4                       u4_s_tydc_nmgbl_sng_slm_elpsd;
static U1                       u1_s_tydc_nmgbl_sng_ctrl            __attribute__((section(".bss_BACK")));

static U2                       u2_s_tydc_nmgbl_sng_slm_tout;

static U1                       u1_s_tydc_nmgbl_sng_tr_capt;

static U1                       u1_s_tydc_nmgbl_sng_ssr_end         __attribute__((section(".bss_BACK")));
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2      u2_s_TydcDtcNmGblSngEaschk_Stb(const U1 u1_a_PWRACT, const U1 u1_a_NMWK);
static U2      u2_s_TydcDtcNmGblSngEaschk_Run(const U1 u1_a_PWRACT, const U1 u1_a_NMWK);
static U2      u2_s_TydcDtcNmGblSngEaschk_Ina(const U1 u1_a_PWRACT, const U1 u1_a_NMWK);

static void    vd_s_TydcDtcNmGblSngActToStb(const U2 u2_a_EAS_CHK, const U1 u1_a_NMWK);
static void    vd_s_TydcDtcNmGblSngActToRun(const U2 u2_a_EAS_CHK, const U1 u1_a_NMWK);
static void    vd_s_TydcDtcNmGblSngActToIna(const U2 u2_a_EAS_CHK, const U1 u1_a_NMWK);

static void    vd_s_TydcDtcNmGblSngBufInit(void);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcNmGblSngInit(const U1 u1_a_BR_INIT)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcNmGblSngInit(const U1 u1_a_BR_INIT)
{
    if(u1_a_BR_INIT == (U1)TRUE){
        u1_s_tydc_nmgbl_sng_ctrl     = (U1)TYDC_NMGBL_SNG_STS_STB;
        u1_s_tydc_nmgbl_sng_ssr_end  = (U1)FALSE;
    }

    u4_s_tydc_nmgbl_sng_slm_elpsd = (U4)0U;
    u2_s_tydc_nmgbl_sng_slm_tout  = (U2)0U;

    vd_s_TydcDtcNmGblSngBufInit();

    u1_s_tydc_nmgbl_sng_tr_capt  = (U1)FALSE;
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcNmGblSngMainTask(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcNmGblSngMainTask(void)
{
    static const U1          u1_sp_TYDC_NMGBL_SNG_STM[] = {
        (U1)TYDC_NMGBL_SNG_ACT_STB,     (U1)TYDC_NMGBL_SNG_ACT_TO_STB,  (U1)TYDC_NMGBL_SNG_ACT_INA,
        (U1)TYDC_NMGBL_SNG_ACT_STB,     (U1)TYDC_NMGBL_SNG_ACT_TO_STB,  (U1)TYDC_NMGBL_SNG_ACT_INA,
        (U1)TYDC_NMGBL_SNG_ACT_STB,     (U1)TYDC_NMGBL_SNG_ACT_TO_STB,  (U1)TYDC_NMGBL_SNG_ACT_INA,
        (U1)TYDC_NMGBL_SNG_ACT_STB,     (U1)TYDC_NMGBL_SNG_ACT_TO_STB,  (U1)TYDC_NMGBL_SNG_ACT_INA,
        (U1)TYDC_NMGBL_SNG_ACT_TO_RUN,  (U1)TYDC_NMGBL_SNG_ACT_RUN,     (U1)TYDC_NMGBL_SNG_ACT_INA,
        (U1)TYDC_NMGBL_SNG_ACT_TO_RUN,  (U1)TYDC_NMGBL_SNG_ACT_RUN,     (U1)TYDC_NMGBL_SNG_ACT_TO_STB,
        (U1)TYDC_NMGBL_SNG_ACT_TO_RUN,  (U1)TYDC_NMGBL_SNG_ACT_TO_INA,  (U1)TYDC_NMGBL_SNG_ACT_INA,
        (U1)TYDC_NMGBL_SNG_ACT_TO_RUN,  (U1)TYDC_NMGBL_SNG_ACT_TO_INA,  (U1)TYDC_NMGBL_SNG_ACT_TO_STB
    };

    static U2   ( * const    fp_sp_u2_TYDC_NMGBL_SNG_EAS_CHK[])(const U1 u1_a_PWRACT, const U1 u1_a_NMWK) = {
        &u2_s_TydcDtcNmGblSngEaschk_Stb,    /* TYDC_NMGBL_SNG_STS_STB        (0U) */
        &u2_s_TydcDtcNmGblSngEaschk_Run,    /* TYDC_NMGBL_SNG_STS_RUN        (1U) */
        &u2_s_TydcDtcNmGblSngEaschk_Ina     /* TYDC_NMGBL_SNG_STS_INA        (2U) */
    };

    static void ( * const    fp_sp_vd_TYDC_NMGBL_SNG_ACT[])(const U2 u2_a_EAS_CHK, const U1 u1_a_NMWK) = {
        &vd_s_TydcDtcNmGblSngActToStb,      /* TYDC_NMGBL_SNG_ACT_TO_STB     (0U) */
        &vd_s_TydcDtcNmGblSngActToRun,      /* TYDC_NMGBL_SNG_ACT_TO_RUN     (1U) */
        &vd_s_TydcDtcNmGblSngActToIna       /* TYDC_NMGBL_SNG_ACT_TO_INA     (2U) */
                                            /* TYDC_NMGBL_SNG_ACT_STB        (3U) */
                                            /* TYDC_NMGBL_SNG_ACT_RUN        (4U) */
                                            /* TYDC_NMGBL_SNG_ACT_INA        (5U) */
    };

    U2      u2_t_eas_chk;
    U2      u2_t_act;
    U1      u1_t_pwr;
    U1      u1_t_nmwk;

    if(u1_s_tydc_nmgbl_sng_ctrl  >= (U1)TYDC_NMGBL_SNG_NUM_STS){

        u1_s_tydc_nmgbl_sng_ctrl = (U1)TYDC_NMGBL_SNG_STS_STB;
    }
    else{

        u1_t_nmwk     = u1_g_TyDoCANDtcNmGblCfgNmRun();
        if(u1_s_tydc_nmgbl_sng_ctrl == (U1)TYDC_NMGBL_SNG_STS_STB){
            u1_t_pwr  = u1_g_TyDoCANDtcNmGblCfgWkmAct((U1)FALSE);
        }
        else if(u1_s_tydc_nmgbl_sng_ctrl == (U1)TYDC_NMGBL_SNG_STS_RUN){
            u1_t_pwr  = u1_g_TyDoCANDtcNmGblCfgWkmAct((U1)TRUE);
        }
        else{
            u1_t_pwr  = u1_g_TyDoCANDtcNmGblCfgWkmReAct();
        }

        u2_t_eas_chk = (*fp_sp_u2_TYDC_NMGBL_SNG_EAS_CHK[u1_s_tydc_nmgbl_sng_ctrl])(u1_t_pwr, u1_t_nmwk);

        u2_t_act = (u2_t_eas_chk * (U2)TYDC_NMGBL_SNG_NUM_STS) + (U2)u1_s_tydc_nmgbl_sng_ctrl;
        u2_t_act = (U2)u1_sp_TYDC_NMGBL_SNG_STM[u2_t_act];
        if(u2_t_act < (U2)TYDC_NMGBL_SNG_ACT_STB){
            (*fp_sp_vd_TYDC_NMGBL_SNG_ACT[u2_t_act])(u2_t_eas_chk, u1_t_nmwk);
        }
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDtcTrchk_U2A13(const U2 u2_a_ELPSD)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDtcTrchk_U2A13(const U2 u2_a_ELPSD)
{
    U1      u1_t_capt;
    U1      u1_t_ret;

    u1_t_capt = u1_s_tydc_nmgbl_sng_tr_capt;
    u1_s_tydc_nmgbl_sng_tr_capt = (U1)FALSE;

    if(u1_t_capt != (U1)0U){
        u1_s_tydc_nmgbl_sng_ssr_end = (U1)TRUE;
        u1_t_ret = (U1)OXDC_DTC_TR_ACT;
    }
    else{
        u1_t_ret = (U1)OXDC_DTC_TR_INA;
    }

    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  uint8   u1_g_oXDoCANAubIfNmGblSngf(uint8 * u1_ap_sngf, Dem_MonitorDataType u4_a_mon)                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
#if (DEM_READFUNC_MONITORDATA_SUPPORT == STD_ON)
uint8   u1_g_oXDoCANAubIfNmGblSngf(uint8 * u1_ap_sngf, Dem_MonitorDataType u4_a_mon)
#else
uint8   u1_g_oXDoCANAubIfNmGblSngf(uint8 * u1_ap_sngf)
#endif
{
    U1 *    u1_tp_dst;
    U4      u4_t_lpcnt;

    if(u1_ap_sngf != vdp_PTR_NA){
        if(u1_s_tydc_nmgbl_sng_ssr_end == (U1)TRUE){

            for(u4_t_lpcnt = (U4)0U; (U4)u4_t_lpcnt < (U4)TYDC_DTC_NMGBL_SNGF_NUM; u4_t_lpcnt++){
                u1_tp_dst = &u1_ap_sngf[u4_t_lpcnt * (U4)TYDC_DTC_NMGBL_SNGF_SIZE];

                u1_tp_dst[0]  = (U1)0U;                                                 /* [0] support  */
                u1_tp_dst[1]  =     st_sp_tydc_nmgbl_sng_log[u4_t_lpcnt].u1_nm;         /* [1] NM CANID */
                u1_tp_dst[2]  = (U1)0U;                                                 /* [2] support  */
                u1_tp_dst[3]  =     st_sp_tydc_nmgbl_sng_log[u4_t_lpcnt].u1_nm_ch;      /* [3] NM Rx ch */

                u1_tp_dst[4]  = (U1)0U;                                                 /* [4] support    */
                u1_tp_dst[5]  =     st_sp_tydc_nmgbl_sng_log[u4_t_lpcnt].u1_diag;       /* [5] diag CANID */
                u1_tp_dst[6]  = (U1)0U;                                                 /* [6] support    */
                u1_tp_dst[7]  =     st_sp_tydc_nmgbl_sng_log[u4_t_lpcnt].u1_diag_ch;    /* [7] diag Rx ch */

                /* For 19PFv3, there is no "Message with MsgID" to target. */
                u1_tp_dst[8]  = (U1)0U;                                                 /* [8] support      */
                u1_tp_dst[9]  = (U1)0U;                                                 /* [9] sp ev CANID  */
                u1_tp_dst[10] = (U1)0U;                                                 /* [10] support     */
                u1_tp_dst[11] = (U1)0U;                                                 /* [11] sp ev Rx ch */
            }
        }
    }

    return((Std_ReturnType)E_OK);
}
/*===================================================================================================================================*/
/*  static U2      u2_s_TydcDtcNmGblSngEaschk_Stb(const U1 u1_a_PWRACT, const U1 u1_a_NMWK)                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2      u2_s_TydcDtcNmGblSngEaschk_Stb(const U1 u1_a_PWRACT, const U1 u1_a_NMWK)
{
    U2      u2_t_eas_chk;

    if(u1_a_PWRACT == (U1)TRUE){
        u2_t_eas_chk = (U2)TYDC_NMGBL_SNG_EAS_CHK_PWR_ACT;
    }
    else{
        u2_t_eas_chk = (U2)0U;
    }

    return(u2_t_eas_chk);
}
/*===================================================================================================================================*/
/*  static U2      u2_s_TydcDtcNmGblSngEaschk_Run(const U1 u1_a_PWRACT, const U1 u1_a_NMWK)                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2      u2_s_TydcDtcNmGblSngEaschk_Run(const U1 u1_a_PWRACT, const U1 u1_a_NMWK)
{
    static const U4          u4_s_TYDC_DTC_NMGBL_SNG_SLM_MAX    = (U4)U4_MAX - ((U4)OXDC_MAIN_TICK << 1U);
    U2                       u2_t_eas_chk;

    u2_t_eas_chk = (U2)0U;

    if(u1_a_NMWK == (U1)TRUE){
        if(u4_s_tydc_nmgbl_sng_slm_elpsd < u4_s_TYDC_DTC_NMGBL_SNG_SLM_MAX){
            u4_s_tydc_nmgbl_sng_slm_elpsd += (U4)OXDC_MAIN_TICK;
        }
    }
    else{
        u4_s_tydc_nmgbl_sng_slm_elpsd = (U4)0U;
    }

    if(u1_a_PWRACT == (U1)TRUE){
        u2_t_eas_chk |= (U2)TYDC_NMGBL_SNG_EAS_CHK_PWR_ACT;
    }

    if(u4_s_tydc_nmgbl_sng_slm_elpsd >= u4_g_TYDC_DTC_NMGBL_SLM_TOUT){
        u2_t_eas_chk |= (U2)TYDC_NMGBL_SNG_EAS_CHK_SL_TOUT;
    }

    return(u2_t_eas_chk);
}
/*===================================================================================================================================*/
/*  static U2      u2_s_TydcDtcNmGblSngEaschk_Ina(const U1 u1_a_PWRACT, const U1 u1_a_NMWK)                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2      u2_s_TydcDtcNmGblSngEaschk_Ina(const U1 u1_a_PWRACT, const U1 u1_a_NMWK)
{
    static const U2         u2_s_TYDC_DTC_NMGBL_SNG_INA_TOUT = (U2)10000U / (U2)OXDC_MAIN_TICK; /* 10s */

    U4                      u4_t_cid;
    U4                      u4_t_lpcnt;
    U2                      u2_t_eas_chk;
    U1                      u1_t_exist;

    u2_t_eas_chk = (U2)0U;

    if(u1_a_PWRACT == (U1)TRUE){
        u2_t_eas_chk |= (U2)TYDC_NMGBL_SNG_EAS_CHK_PWR_ACT;
    }

    if(u1_s_tydc_nmgbl_sng_ssr_end == (U1)TRUE){
        u2_t_eas_chk |= (U2)TYDC_NMGBL_SNG_EAS_CHK_SSR_END;
    }
    else if(u2_s_tydc_nmgbl_sng_slm_tout < u2_s_TYDC_DTC_NMGBL_SNG_INA_TOUT){
        u2_s_tydc_nmgbl_sng_slm_tout++;
    }
    else{

        if(u1_s_tydc_nmgbl_sng_tr_capt != (U1)TRUE){
            vd_g_TyDoCANDtcNmGblSetMonitorMode((U1)TYDC_DTC_NMGBL_RXMON_NONE);
            for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TYDC_DTC_NMGBL_SNGF_NUM; u4_t_lpcnt++){

                u1_t_exist = u1_g_TyDoCANDtcNmGblGetCidByCnt((U1)TYDC_DTC_NMGBL_CID_NM, (U1)u4_t_lpcnt, &u4_t_cid);
                if(u1_t_exist == (U1)TRUE){
                    st_sp_tydc_nmgbl_sng_log[u4_t_lpcnt].u1_nm    = (U1)(u4_t_cid & (U4)U1_MAX);
                    st_sp_tydc_nmgbl_sng_log[u4_t_lpcnt].u1_nm_ch = u1_g_TYDC_DTC_NMGBL_REC_CH_BIT;
                }

                u1_t_exist = u1_g_TyDoCANDtcNmGblGetCidByCnt((U1)TYDC_DTC_NMGBL_CID_DI, (U1)u4_t_lpcnt, &u4_t_cid);
                if(u1_t_exist == (U1)TRUE){
                    st_sp_tydc_nmgbl_sng_log[u4_t_lpcnt].u1_diag    = (U1)(u4_t_cid & (U4)U1_MAX);
                    st_sp_tydc_nmgbl_sng_log[u4_t_lpcnt].u1_diag_ch = u1_g_TYDC_DTC_NMGBL_REC_CH_BIT;
                }
            }
            vd_g_TyDoCANDtcNmGblCanidClear();
            u1_s_tydc_nmgbl_sng_tr_capt = (U1)TRUE;
        }
    }

    return(u2_t_eas_chk);
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDtcNmGblSngActToStb(const U2 u2_a_EAS_CHK, const U1 u1_a_NMWK)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDtcNmGblSngActToStb(const U2 u2_a_EAS_CHK, const U1 u1_a_NMWK)
{
    U1      u1_t_mode;

    u1_t_mode = u1_g_TyDoCANDtcNmGblGetMonitorMode();
    if(u1_t_mode != (U1)TYDC_DTC_NMGBL_RXMON_WK){
        vd_g_TyDoCANDtcNmGblSetMonitorMode((U1)TYDC_DTC_NMGBL_RXMON_NONE);
        vd_g_TyDoCANDtcNmGblCanidClear();
    }
    vd_s_TydcDtcNmGblSngBufInit();

    u1_s_tydc_nmgbl_sng_ssr_end   = (U1)FALSE;

    u2_s_tydc_nmgbl_sng_slm_tout  = (U2)0U;
    u4_s_tydc_nmgbl_sng_slm_elpsd = (U4)0U;
    u1_s_tydc_nmgbl_sng_ctrl      = (U1)TYDC_NMGBL_SNG_STS_STB;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDtcNmGblSngActToRun(const U2 u2_a_EAS_CHK, const U1 u1_a_NMWK)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDtcNmGblSngActToRun(const U2 u2_a_EAS_CHK, const U1 u1_a_NMWK)
{
    u1_s_tydc_nmgbl_sng_ctrl      = (U1)TYDC_NMGBL_SNG_STS_RUN;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDtcNmGblSngActToIna(const U2 u2_a_EAS_CHK, const U1 u1_a_NMWK)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDtcNmGblSngActToIna(const U2 u2_a_EAS_CHK, const U1 u1_a_NMWK)
{
    vd_g_TyDoCANDtcNmGblCanidClear();
    vd_g_TyDoCANDtcNmGblSetMonitorMode((U1)TYDC_DTC_NMGBL_RXMON_SNG);

    vd_s_TydcDtcNmGblSngBufInit();

    u2_s_tydc_nmgbl_sng_slm_tout  = (U2)0U;
    u4_s_tydc_nmgbl_sng_slm_elpsd = (U4)0U;
    u1_s_tydc_nmgbl_sng_ctrl      = (U1)TYDC_NMGBL_SNG_STS_INA;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDtcNmGblSngBufInit(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDtcNmGblSngBufInit(void)
{
    U4  u4_t_lpcnt;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TYDC_DTC_NMGBL_SNGF_NUM; u4_t_lpcnt++){
        st_sp_tydc_nmgbl_sng_log[u4_t_lpcnt].u1_diag    = (U1)0U;
        st_sp_tydc_nmgbl_sng_log[u4_t_lpcnt].u1_nm      = (U1)0U;
        st_sp_tydc_nmgbl_sng_log[u4_t_lpcnt].u1_diag_ch = (U1)0U;
        st_sp_tydc_nmgbl_sng_log[u4_t_lpcnt].u1_nm_ch   = (U1)0U;
    }
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     1/17/2024  TI       New.                                                                                               */
/*  1.0.1     7/04/2024  TI       tydocan_dtc_nmgbl_wk.c v1.0.0 -> v1.0.1                                                            */
/*                                                                                                                                   */
/*  * TI = Tomoko Inuzuka, DENSO                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
