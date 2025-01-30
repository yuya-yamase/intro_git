/* 1.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for Toyota MET/HUD based on AUBIST/DEM, DCM                                                                     */
/*  NM Diag  Detection of abnormal global-ecu (Detection of excessive wakeup)                                                        */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_DTC_NMGBL_WK_C_MAJOR            (1U)
#define TYDOCAN_DTC_NMGBL_WK_C_MINOR            (0U)
#define TYDOCAN_DTC_NMGBL_WK_C_PATCH            (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_cfg_private.h"

#include "tydocan_dtc_nmgbl.h"
#include "tydocan_dtc_nmgbl_cfg_private.h"
#include "oxdocan_aubif.h"
#include "int_drv.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (TYDOCAN_DTC_NMGBL_WK_C_MAJOR != OXDOCAN_CFG_H_MAJOR)
#error "tydocan_dtc_nmgbl_wk.c and oxdocan_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((TYDOCAN_DTC_NMGBL_WK_C_MAJOR != TYDOCAN_DTC_NMGBL_H_MAJOR) || \
     (TYDOCAN_DTC_NMGBL_WK_C_MINOR != TYDOCAN_DTC_NMGBL_H_MINOR) || \
     (TYDOCAN_DTC_NMGBL_WK_C_PATCH != TYDOCAN_DTC_NMGBL_H_PATCH))
#error "tydocan_dtc_nmgbl_wk.c and tydocan_dtc_nmgbl.h : source and header files are inconsistent!"
#endif

#if ((TYDOCAN_DTC_NMGBL_WK_C_MAJOR != TYDOCAN_DTC_NMGBL_CFG_H_MAJOR) || \
     (TYDOCAN_DTC_NMGBL_WK_C_MINOR != TYDOCAN_DTC_NMGBL_CFG_H_MINOR) || \
     (TYDOCAN_DTC_NMGBL_WK_C_PATCH != TYDOCAN_DTC_NMGBL_CFG_H_PATCH))
#error "tydocan_dtc_nmgbl_wk.c and tydocan_dtc_nmgbl_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_NMGBL_WK_NUM_STS                   (3U)
#define TYDC_NMGBL_WK_STS_STB                   (0U)
#define TYDC_NMGBL_WK_STS_RUN                   (1U)
#define TYDC_NMGBL_WK_STS_INA                   (2U)

#define TYDC_NMGBL_WK_ACT_TO_STB                (0U)
#define TYDC_NMGBL_WK_ACT_TO_RUN                (1U)
#define TYDC_NMGBL_WK_ACT_TO_INA                (2U)
#define TYDC_NMGBL_WK_ACT_STB                   (3U)
#define TYDC_NMGBL_WK_ACT_RUN                   (4U)
#define TYDC_NMGBL_WK_ACT_INA                   (5U)

#define TYDC_NMGBL_WK_EAS_CHK_PWR_ACT           (0x08U)
#define TYDC_NMGBL_WK_EAS_CHK_GE_WKCT           (0x04U)
#define TYDC_NMGBL_WK_EAS_CHK_WK_TOUT           (0x02U)
#define TYDC_NMGBL_WK_EAS_CHK_SSR_END           (0x01U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U4      u4_term;
    U2      u2_cnt;
}ST_TYDC_NMGBL_WKM;

typedef struct{
    U1      u1_nm_aft;
    U1      u1_diag;
    U2      u2_ctrl;
    U1      u1_nm_bfo;
    U1      u1_ordr_nm;
    U1      u1_ordr_di;
    U1      u1_ordr_ctl;
}ST_TYDC_NMGBL_WKUP_CANID;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_TYDC_NMGBL_WKM            st_s_tydc_nmgbl_wkm                 __attribute__((section(".bss_BACK")));

static ST_TYDC_NMGBL_WKUP_CANID     st_sp_tydc_nmgbl_wk_log[TYDC_DTC_NMGBL_WKF_NUM] __attribute__((section(".bss_BACK")));
static U1                           u1_s_tydc_nmgbl_wkm_cnt             __attribute__((section(".bss_BACK")));

static U1                           u1_s_tydc_nmgbl_wk_ctrl             __attribute__((section(".bss_BACK")));
static U1                           u1_s_tydc_nmgbl_wk_ssr_end          __attribute__((section(".bss_BACK")));

static U1                           u1_s_tydc_nmgbl_wk_nmwk_last;
static U1                           u1_s_tydc_nmgbl_wk_tr_capt;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2      u2_s_TydcDtcNmGblWkEaschk_Stb(const U1 u1_a_PWRACT, const U1 u1_a_NMWK);
static U2      u2_s_TydcDtcNmGblWkEaschk_Run(const U1 u1_a_PWRACT, const U1 u1_a_NMWK);
static U2      u2_s_TydcDtcNmGblWkEaschk_Ina(const U1 u1_a_PWRACT, const U1 u1_a_NMWK);
static U2      u2_s_TydcDtcNmGblWkEaschk_Wkm(void);

static void    vd_s_TydcDtcNmGblWkActToStb(const U2 u2_a_EAS_CHK, const U1 u1_a_NMWK);
static void    vd_s_TydcDtcNmGblWkActToRun(const U2 u2_a_EAS_CHK, const U1 u1_a_NMWK);
static void    vd_s_TydcDtcNmGblWkActToIna(const U2 u2_a_EAS_CHK, const U1 u1_a_NMWK);

static void    vd_s_TydcDtcNmGblWkWkmInit(void);
static void    vd_s_TydcDtcNmGblWkBufInit(void);
static void    vd_s_TydcDtcNmGblWkRecWkFact(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcNmGblWkInit(const U1 u1_a_BR_INIT)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcNmGblWkInit(const U1 u1_a_BR_INIT)
{
    if(u1_a_BR_INIT == (U1)TRUE){

        vd_s_TydcDtcNmGblWkWkmInit();
        u1_s_tydc_nmgbl_wk_ctrl         = (U1)TYDC_NMGBL_WK_STS_STB;
        u1_s_tydc_nmgbl_wk_ssr_end      = (U1)FALSE;
        vd_s_TydcDtcNmGblWkBufInit();
    }

    u1_s_tydc_nmgbl_wk_nmwk_last = (U1)FALSE;
    u1_s_tydc_nmgbl_wk_tr_capt   = (U1)0U;
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcNmGblWkMainTask(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcNmGblWkMainTask(void)
{
    static const U1          u1_sp_TYDC_NMGBL_WK_STM[] = {
        (U1)TYDC_NMGBL_WK_ACT_STB,        (U1)TYDC_NMGBL_WK_ACT_TO_STB,     (U1)TYDC_NMGBL_WK_ACT_INA,
        (U1)TYDC_NMGBL_WK_ACT_STB,        (U1)TYDC_NMGBL_WK_ACT_TO_STB,     (U1)TYDC_NMGBL_WK_ACT_INA,
        (U1)TYDC_NMGBL_WK_ACT_STB,        (U1)TYDC_NMGBL_WK_ACT_TO_STB,     (U1)TYDC_NMGBL_WK_ACT_INA,
        (U1)TYDC_NMGBL_WK_ACT_STB,        (U1)TYDC_NMGBL_WK_ACT_TO_STB,     (U1)TYDC_NMGBL_WK_ACT_INA,
        (U1)TYDC_NMGBL_WK_ACT_STB,        (U1)TYDC_NMGBL_WK_ACT_TO_STB,     (U1)TYDC_NMGBL_WK_ACT_INA,
        (U1)TYDC_NMGBL_WK_ACT_STB,        (U1)TYDC_NMGBL_WK_ACT_TO_STB,     (U1)TYDC_NMGBL_WK_ACT_INA,
        (U1)TYDC_NMGBL_WK_ACT_STB,        (U1)TYDC_NMGBL_WK_ACT_TO_STB,     (U1)TYDC_NMGBL_WK_ACT_INA,
        (U1)TYDC_NMGBL_WK_ACT_STB,        (U1)TYDC_NMGBL_WK_ACT_TO_STB,     (U1)TYDC_NMGBL_WK_ACT_INA,
        (U1)TYDC_NMGBL_WK_ACT_TO_RUN,     (U1)TYDC_NMGBL_WK_ACT_RUN,        (U1)TYDC_NMGBL_WK_ACT_INA,
        (U1)TYDC_NMGBL_WK_ACT_TO_RUN,     (U1)TYDC_NMGBL_WK_ACT_RUN,        (U1)TYDC_NMGBL_WK_ACT_TO_STB,
        (U1)TYDC_NMGBL_WK_ACT_TO_RUN,     (U1)TYDC_NMGBL_WK_ACT_TO_RUN,     (U1)TYDC_NMGBL_WK_ACT_INA,
        (U1)TYDC_NMGBL_WK_ACT_TO_RUN,     (U1)TYDC_NMGBL_WK_ACT_TO_RUN,     (U1)TYDC_NMGBL_WK_ACT_TO_STB,
        (U1)TYDC_NMGBL_WK_ACT_TO_RUN,     (U1)TYDC_NMGBL_WK_ACT_TO_INA,     (U1)TYDC_NMGBL_WK_ACT_INA,
        (U1)TYDC_NMGBL_WK_ACT_TO_RUN,     (U1)TYDC_NMGBL_WK_ACT_TO_INA,     (U1)TYDC_NMGBL_WK_ACT_TO_STB,
        (U1)TYDC_NMGBL_WK_ACT_TO_RUN,     (U1)TYDC_NMGBL_WK_ACT_TO_INA,     (U1)TYDC_NMGBL_WK_ACT_INA,
        (U1)TYDC_NMGBL_WK_ACT_TO_RUN,     (U1)TYDC_NMGBL_WK_ACT_TO_INA,     (U1)TYDC_NMGBL_WK_ACT_TO_STB
    };

    static U2   ( * const    fp_sp_u2_TYDC_NMGBL_WK_EAS_CHK[])(const U1 u1_a_PWRACT, const U1 u1_a_NMWK) = {
        &u2_s_TydcDtcNmGblWkEaschk_Stb,     /* TYDC_NMGBL_WK_STS_STB        (0U) */
        &u2_s_TydcDtcNmGblWkEaschk_Run,     /* TYDC_NMGBL_WK_STS_RUN        (1U) */
        &u2_s_TydcDtcNmGblWkEaschk_Ina      /* TYDC_NMGBL_WK_STS_INA        (2U) */
    };

    static void ( * const    fp_sp_vd_TYDC_NMGBL_WK_ACT[])(const U2 u2_a_EAS_CHK, const U1 u1_a_NMWK) = {
        &vd_s_TydcDtcNmGblWkActToStb,       /* TYDC_NMGBL_WK_ACT_TO_STB     (0U) */
        &vd_s_TydcDtcNmGblWkActToRun,       /* TYDC_NMGBL_WK_ACT_TO_RUN     (1U) */
        &vd_s_TydcDtcNmGblWkActToIna        /* TYDC_NMGBL_WK_ACT_TO_INA     (2U) */
                                            /* TYDC_NMGBL_WK_ACT_STB        (3U) */
                                            /* TYDC_NMGBL_WK_ACT_RUN        (4U) */
                                            /* TYDC_NMGBL_WK_ACT_INA        (5U) */
    };

    U2                       u2_t_eas_chk;
    U2                       u2_t_act;
    U1                       u1_t_pwr;
    U1                       u1_t_nmwk;

    if(u1_s_tydc_nmgbl_wk_ctrl >= (U1)TYDC_NMGBL_WK_NUM_STS){

        u1_s_tydc_nmgbl_wk_ctrl = (U1)TYDC_NMGBL_WK_STS_STB;
    }
    else{

        u1_t_nmwk     = u1_g_TyDoCANDtcNmGblCfgNmRun();
        if(u1_s_tydc_nmgbl_wk_ctrl == (U1)TYDC_NMGBL_WK_STS_STB){
            u1_t_pwr  = u1_g_TyDoCANDtcNmGblCfgWkmAct((U1)FALSE);
        }
        else if(u1_s_tydc_nmgbl_wk_ctrl == (U1)TYDC_NMGBL_WK_STS_RUN){
            u1_t_pwr  = u1_g_TyDoCANDtcNmGblCfgWkmAct((U1)TRUE);
        }
        else{
            u1_t_pwr  = u1_g_TyDoCANDtcNmGblCfgWkmReAct();
        }

        u2_t_eas_chk = (*fp_sp_u2_TYDC_NMGBL_WK_EAS_CHK[u1_s_tydc_nmgbl_wk_ctrl])(u1_t_pwr, u1_t_nmwk);

        u1_s_tydc_nmgbl_wk_nmwk_last = u1_t_nmwk;

        u2_t_act = (u2_t_eas_chk * (U2)TYDC_NMGBL_WK_NUM_STS) + (U2)u1_s_tydc_nmgbl_wk_ctrl;
        u2_t_act = (U2)u1_sp_TYDC_NMGBL_WK_STM[u2_t_act];
        if(u2_t_act < (U2)TYDC_NMGBL_WK_ACT_STB){
            (*fp_sp_vd_TYDC_NMGBL_WK_ACT[u2_t_act])(u2_t_eas_chk, u1_t_nmwk);
        }
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDtcTrchk_U2A12(const U2 u2_a_ELPSD)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDtcTrchk_U2A12(const U2 u2_a_ELPSD)
{
    U1      u1_t_capt;
    U1      u1_t_ret;

    u1_t_capt = u1_s_tydc_nmgbl_wk_tr_capt;
    u1_s_tydc_nmgbl_wk_tr_capt = (U1)0U;

    if(u1_t_capt != (U1)0U){
        u1_s_tydc_nmgbl_wk_ssr_end = (U1)TRUE;
        u1_t_ret = (U1)OXDC_DTC_TR_ACT;
    }
    else{
        u1_t_ret = (U1)OXDC_DTC_TR_INA;
    }

    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  uint8   u1_g_oXDoCANAubIfNmGblWkf(uint8 * u1_ap_wkf, Dem_MonitorDataType u4_a_mon)                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
#if (DEM_READFUNC_MONITORDATA_SUPPORT == STD_ON)
uint8   u1_g_oXDoCANAubIfNmGblWkf(uint8 * u1_ap_wkf, Dem_MonitorDataType u4_a_mon)
#else
uint8   u1_g_oXDoCANAubIfNmGblWkf(uint8 * u1_ap_wkf)
#endif
{
    U1 *    u1_tp_dst;
    U4      u4_t_lpcnt;
    U4      u4_t_size;

    if(u1_ap_wkf != vdp_PTR_NA){
        if(u1_s_tydc_nmgbl_wk_ssr_end == (U1)TRUE){

            if(u1_s_tydc_nmgbl_wkm_cnt > (U1)TYDC_DTC_NMGBL_WKF_NUM){
                u1_s_tydc_nmgbl_wkm_cnt = (U1)TYDC_DTC_NMGBL_WKF_NUM;
            }
            for(u4_t_lpcnt = (U4)0U; (U4)u4_t_lpcnt < (U4)u1_s_tydc_nmgbl_wkm_cnt; u4_t_lpcnt++){
                u1_tp_dst = &u1_ap_wkf[u4_t_lpcnt * (U4)TYDC_DTC_NMGBL_WKF_SIZE];

                u1_tp_dst[0]  = (U1)0U;                                                         /* [0] support         */
                u1_tp_dst[1]  =     st_sp_tydc_nmgbl_wk_log[u4_t_lpcnt].u1_nm_bfo;              /* [1] NM before sleep */

                u1_tp_dst[2]  = (U1)0U;                                                         /* [2] support   */
                u1_tp_dst[3]  =     u1_g_TYDC_DTC_NMGBL_REC_CH_BIT;                             /* [3] wakeup ch */

                u1_tp_dst[4]  = (U1)0U;                                                         /* [4] support         */
                u1_tp_dst[5]  =     st_sp_tydc_nmgbl_wk_log[u4_t_lpcnt].u1_nm_aft;              /* [5] NM after wakeup */
                u1_tp_dst[6]  = (U1)0U;                                                         /* [6] support         */
                u1_tp_dst[7]  =     st_sp_tydc_nmgbl_wk_log[u4_t_lpcnt].u1_ordr_nm;             /* [7] NM rx order     */

                u1_tp_dst[8]  = (U1)0U;                                                         /* [8] support        */
                u1_tp_dst[9]  =     st_sp_tydc_nmgbl_wk_log[u4_t_lpcnt].u1_diag;                /* [9] diag           */
                u1_tp_dst[10] = (U1)0U;                                                         /* [10] support       */
                u1_tp_dst[11] =     st_sp_tydc_nmgbl_wk_log[u4_t_lpcnt].u1_ordr_di;             /* [11] diag rx order */

                u1_tp_dst[12] = (U1)0U;                                                         /* [12] support       */
                u1_tp_dst[13] = (U1)(st_sp_tydc_nmgbl_wk_log[u4_t_lpcnt].u2_ctrl >> 8U);        /* [13] ctrl(hi)      */
                u1_tp_dst[14] = (U1)0U;                                                         /* [14] support       */
                u1_tp_dst[15] = (U1)(st_sp_tydc_nmgbl_wk_log[u4_t_lpcnt].u2_ctrl & (U2)U1_MAX); /* [15] ctrl(lo)      */
                u1_tp_dst[16] = (U1)0U;                                                         /* [16] support       */
                u1_tp_dst[17] =     st_sp_tydc_nmgbl_wk_log[u4_t_lpcnt].u1_ordr_ctl;            /* [17] ctrl rx order */
            }
            if(u1_s_tydc_nmgbl_wkm_cnt < (U1)TYDC_DTC_NMGBL_WKF_NUM){
                u1_tp_dst = &u1_ap_wkf[u1_s_tydc_nmgbl_wkm_cnt * (U1)TYDC_DTC_NMGBL_WKF_SIZE];
                u4_t_size = ((U4)TYDC_DTC_NMGBL_WKF_NUM - (U4)u1_s_tydc_nmgbl_wkm_cnt) * (U4)TYDC_DTC_NMGBL_WKF_SIZE;
                vd_g_MemfillU1(u1_tp_dst, (U1)0x00U, u4_t_size);
            }
            vd_s_TydcDtcNmGblWkBufInit();
        }
    }

    return((Std_ReturnType)E_OK);
}
/*===================================================================================================================================*/
/*  static U2      u2_s_TydcDtcNmGblWkEaschk_Stb(const U1 u1_a_PWRACT, const U1 u1_a_NMWK)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2      u2_s_TydcDtcNmGblWkEaschk_Stb(const U1 u1_a_PWRACT, const U1 u1_a_NMWK)
{
    U2      u2_t_eas_chk;

    u2_t_eas_chk = (U2)0U;

    if(u1_a_PWRACT == (U1)TRUE){
        u2_t_eas_chk = (U2)TYDC_NMGBL_WK_EAS_CHK_PWR_ACT;
    }

    return(u2_t_eas_chk);
}
/*===================================================================================================================================*/
/*  static U2      u2_s_TydcDtcNmGblWkEaschk_Run(const U1 u1_a_PWRACT, const U1 u1_a_NMWK)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2      u2_s_TydcDtcNmGblWkEaschk_Run(const U1 u1_a_PWRACT, const U1 u1_a_NMWK)
{
    U4      u4_t_elpsd;
    U4      u4_t_term;
    U2      u2_t_eas_chk;

    u2_t_eas_chk = u2_s_TydcDtcNmGblWkEaschk_Wkm();

    if(u1_a_PWRACT == (U1)TRUE){
        u2_t_eas_chk |= (U2)TYDC_NMGBL_WK_EAS_CHK_PWR_ACT;
    }

    /* NM Sleep -> NM Wake */
    if((u1_a_NMWK == (U1)TRUE) &&
       (u1_a_NMWK != u1_s_tydc_nmgbl_wk_nmwk_last)){

        u4_t_elpsd = u4_g_DateclkEtmElapsed(u1_g_TYDC_DTC_NMGBL_DCT_CH);

        if(u4_t_elpsd >= st_s_tydc_nmgbl_wkm.u4_term){
            u4_t_term = u4_t_elpsd - st_s_tydc_nmgbl_wkm.u4_term;
        }
        else{
            u4_t_term = (U4)U4_MAX;
        }

        if(u4_t_term < u4_g_TYDC_DTC_NMGBL_TERM_LMT){
            st_s_tydc_nmgbl_wkm.u2_cnt++;
            st_s_tydc_nmgbl_wkm.u4_term = u4_t_elpsd;
        }
        else{
            vd_g_DateclkEtmStart(u1_g_TYDC_DTC_NMGBL_DCT_CH, (U4)0U);
            st_s_tydc_nmgbl_wkm.u4_term = (U4)0U;
            st_s_tydc_nmgbl_wkm.u2_cnt  = (U2)0U;
        }
    }

    if(st_s_tydc_nmgbl_wkm.u2_cnt >= (u2_g_TYDC_DTC_NMGBL_WKC_THRSH - (U2)1U)){
        vd_g_TyDoCANDtcNmGblSetMonitorMode((U1)TYDC_DTC_NMGBL_RXMON_WK);
    }

    return(u2_t_eas_chk);
}
/*===================================================================================================================================*/
/*  static U2      u2_s_TydcDtcNmGblWkEaschk_Ina(const U1 u1_a_PWRACT, const U1 u1_a_NMWK)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2      u2_s_TydcDtcNmGblWkEaschk_Ina(const U1 u1_a_PWRACT, const U1 u1_a_NMWK)
{
    U4      u4_t_cid;
    U4      u4_t_elpsd;
    U4      u4_t_term;
    U4      u4_t_gli;
    U2      u2_t_eas_chk;
    U1      u1_t_exist;
    U1      u1_t_rec_stop;

    u2_t_eas_chk = (U2)0U;

    if(u1_s_tydc_nmgbl_wk_ssr_end != (U1)TRUE){

        u4_t_elpsd = u4_g_DateclkEtmElapsed(u1_g_TYDC_DTC_NMGBL_DCT_CH);

        if(u4_t_elpsd >= st_s_tydc_nmgbl_wkm.u4_term){
            u4_t_term = u4_t_elpsd - st_s_tydc_nmgbl_wkm.u4_term;
        }
        else{
            u4_t_term = (U4)U4_MAX;
        }

        if((u1_s_tydc_nmgbl_wkm_cnt <  (U1)TYDC_DTC_NMGBL_WKF_NUM  ) &&
           (u4_t_term               <  u4_g_TYDC_DTC_NMGBL_TERM_LMT)){

            /* NM Sleep */
            if((u1_a_NMWK                                                  == (U1)FALSE) &&
               (st_sp_tydc_nmgbl_wk_log[u1_s_tydc_nmgbl_wkm_cnt].u1_nm_bfo == (U1)0U   )){

                u4_t_gli = u4_g_IRQ_DI();
                u1_t_exist = u1_g_TyDoCANDtcNmGblGetNmLast(&u4_t_cid);
                vd_g_TyDoCANDtcNmGblCanidClear();
                vd_g_IRQ_EI(u4_t_gli);

                if(u1_t_exist == (U1)TRUE){
                    st_sp_tydc_nmgbl_wk_log[u1_s_tydc_nmgbl_wkm_cnt].u1_nm_bfo     = (U1)(u4_t_cid & (U4)U1_MAX);
                }
            }
            /* NM Sleep -> NM Wake */
            else if((u1_a_NMWK                    == (U1)TRUE ) &&
                    (u1_s_tydc_nmgbl_wk_nmwk_last != u1_a_NMWK)){

                vd_s_TydcDtcNmGblWkRecWkFact();

                st_s_tydc_nmgbl_wkm.u4_term = u4_t_elpsd;
                u1_s_tydc_nmgbl_wkm_cnt++;

            }
            else{
                /* Do nothing */
            }
        }

        u1_t_rec_stop = u1_g_TyDoCANDtcNmGblCfgStopWkfRec();
        if((u1_s_tydc_nmgbl_wkm_cnt >= (U1)TYDC_DTC_NMGBL_WKF_NUM  ) ||
           (u4_t_term               >= u4_g_TYDC_DTC_NMGBL_TERM_LMT) ||
           (u1_t_rec_stop           == (U1)TRUE                    )){

            vd_g_TyDoCANDtcNmGblSetMonitorMode((U1)TYDC_DTC_NMGBL_RXMON_NONE);
            vd_g_TyDoCANDtcNmGblCanidClear();
            u1_s_tydc_nmgbl_wk_tr_capt = (U1)TRUE;
        }
    }

    if(u1_s_tydc_nmgbl_wk_ssr_end == (U1)TRUE){
        u2_t_eas_chk |= (U2)TYDC_NMGBL_WK_EAS_CHK_SSR_END;
    }

    if(u1_a_PWRACT == (U1)TRUE){
        u2_t_eas_chk |= (U2)TYDC_NMGBL_WK_EAS_CHK_PWR_ACT;
    }

    return(u2_t_eas_chk);
}
/*===================================================================================================================================*/
/*  static U2      u2_s_TydcDtcNmGblWkEaschk_Wkm(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2      u2_s_TydcDtcNmGblWkEaschk_Wkm(void)
{
    U4      u4_t_elpsd;
    U2      u2_t_eas_chk;

    u4_t_elpsd = u4_g_DateclkEtmElapsed(u1_g_TYDC_DTC_NMGBL_DCT_CH);

    if(u4_t_elpsd < u4_g_TYDC_DTC_NMGBL_WKM_TOUT){
        u2_t_eas_chk = (U2)0U;
    }
    else if(st_s_tydc_nmgbl_wkm.u2_cnt >= u2_g_TYDC_DTC_NMGBL_WKC_THRSH){
        u2_t_eas_chk = (U2)TYDC_NMGBL_WK_EAS_CHK_GE_WKCT;
    }
    else{
        u2_t_eas_chk = (U2)TYDC_NMGBL_WK_EAS_CHK_WK_TOUT;
    }

    return(u2_t_eas_chk);
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDtcNmGblWkActToStb(const U2 u2_a_EAS_CHK, const U1 u1_a_NMWK)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDtcNmGblWkActToStb(const U2 u2_a_EAS_CHK, const U1 u1_a_NMWK)
{
    U1      u1_t_mode;

    vd_s_TydcDtcNmGblWkWkmInit();
    vd_s_TydcDtcNmGblWkBufInit();

    u1_t_mode = u1_g_TyDoCANDtcNmGblGetMonitorMode();
    if(u1_t_mode != (U1)TYDC_DTC_NMGBL_RXMON_SNG){
        vd_g_TyDoCANDtcNmGblSetMonitorMode((U1)TYDC_DTC_NMGBL_RXMON_NONE);
        vd_g_TyDoCANDtcNmGblCanidClear();
    }

    u1_s_tydc_nmgbl_wk_ssr_end = (U1)FALSE;

    u1_s_tydc_nmgbl_wk_ctrl    = (U1)TYDC_NMGBL_WK_STS_STB;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDtcNmGblWkActToRun(const U2 u2_a_EAS_CHK, const U1 u1_a_NMWK)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDtcNmGblWkActToRun(const U2 u2_a_EAS_CHK, const U1 u1_a_NMWK)
{
    vd_s_TydcDtcNmGblWkWkmInit();

    u1_s_tydc_nmgbl_wk_ctrl      = (U1)TYDC_NMGBL_WK_STS_RUN;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDtcNmGblWkActToIna(const U2 u2_a_EAS_CHK, const U1 u1_a_NMWK)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDtcNmGblWkActToIna(const U2 u2_a_EAS_CHK, const U1 u1_a_NMWK)
{
    vd_s_TydcDtcNmGblWkWkmInit();

    u1_s_tydc_nmgbl_wk_ctrl      = (U1)TYDC_NMGBL_WK_STS_INA;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDtcNmGblWkWkmInit(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDtcNmGblWkWkmInit(void)
{
    vd_g_DateclkEtmStart(u1_g_TYDC_DTC_NMGBL_DCT_CH, (U4)0U);

    st_s_tydc_nmgbl_wkm.u4_term  = (U4)0U;
    st_s_tydc_nmgbl_wkm.u2_cnt   = (U2)0U;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDtcNmGblWkBufInit(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDtcNmGblWkBufInit(void)
{
    U4      u4_t_lpcnt;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TYDC_DTC_NMGBL_WKF_NUM; u4_t_lpcnt++){
        st_sp_tydc_nmgbl_wk_log[u4_t_lpcnt].u1_diag       = (U1)0U;
        st_sp_tydc_nmgbl_wk_log[u4_t_lpcnt].u1_nm_aft     = (U1)0U;
        st_sp_tydc_nmgbl_wk_log[u4_t_lpcnt].u1_nm_bfo     = (U1)0U;
        st_sp_tydc_nmgbl_wk_log[u4_t_lpcnt].u1_ordr_nm    = (U1)0U;
        st_sp_tydc_nmgbl_wk_log[u4_t_lpcnt].u1_ordr_di    = (U1)0U;
        st_sp_tydc_nmgbl_wk_log[u4_t_lpcnt].u1_ordr_ctl   = (U1)0U;
        st_sp_tydc_nmgbl_wk_log[u4_t_lpcnt].u2_ctrl       = (U2)0U;
    }
    u1_s_tydc_nmgbl_wkm_cnt   = (U1)0U;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcDtcNmGblWkRecWkFact(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcDtcNmGblWkRecWkFact(void)
{
    U4      u4_t_cid;
    U4      u4_t_gli;
    U1      u1_t_order;
    U1      u1_t_exist;

    u4_t_gli = u4_g_IRQ_DI();
    u1_t_exist = u1_g_TyDoCANDtcNmGblGetCidByCnt((U1)TYDC_DTC_NMGBL_CID_NM, (U1)0U, &u4_t_cid);
    if(u1_t_exist == (U1)TRUE){
        u1_t_order = u1_g_TyDoCANDtcNmGblGetRcvOrdr((U1)TYDC_DTC_NMGBL_CID_NM);
        st_sp_tydc_nmgbl_wk_log[u1_s_tydc_nmgbl_wkm_cnt].u1_nm_aft     = (U1)(u4_t_cid & (U4)U1_MAX);
        st_sp_tydc_nmgbl_wk_log[u1_s_tydc_nmgbl_wkm_cnt].u1_ordr_nm    = u1_t_order;
    }

    u1_t_exist = u1_g_TyDoCANDtcNmGblGetCidByCnt((U1)TYDC_DTC_NMGBL_CID_DI, (U1)0U, &u4_t_cid);
    if(u1_t_exist == (U1)TRUE){
        u1_t_order = u1_g_TyDoCANDtcNmGblGetRcvOrdr((U1)TYDC_DTC_NMGBL_CID_DI);
        st_sp_tydc_nmgbl_wk_log[u1_s_tydc_nmgbl_wkm_cnt].u1_diag     = (U1)(u4_t_cid & (U4)U1_MAX);
        st_sp_tydc_nmgbl_wk_log[u1_s_tydc_nmgbl_wkm_cnt].u1_ordr_di  = u1_t_order;
    }

    u1_t_exist = u1_g_TyDoCANDtcNmGblGetCidByCnt((U1)TYDC_DTC_NMGBL_CID_CTL, (U1)0U, &u4_t_cid);
    if(u1_t_exist == (U1)TRUE){
        u1_t_order = u1_g_TyDoCANDtcNmGblGetRcvOrdr((U1)TYDC_DTC_NMGBL_CID_CTL);
        st_sp_tydc_nmgbl_wk_log[u1_s_tydc_nmgbl_wkm_cnt].u2_ctrl     = (U2)(u4_t_cid & (U4)U2_MAX);
        st_sp_tydc_nmgbl_wk_log[u1_s_tydc_nmgbl_wkm_cnt].u1_ordr_ctl = u1_t_order;
    }
    vd_g_IRQ_EI(u4_t_gli);
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
/*  1.0.1     7/04/2024  TI       Removed u1_g_TyDoCANDtcNmGblWkTmrwkImmdwn.  Fixed the event determination order.                   */
/*                                                                                                                                   */
/*  * TI = Tomoko Inuzuka, DENSO                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
