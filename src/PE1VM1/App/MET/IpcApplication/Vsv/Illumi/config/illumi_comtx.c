/* 2.2.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Illumination  Communication/Tx                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ILLUMI_COM_TX_C_MAJOR                   (2)
#define ILLUMI_COM_TX_C_MINOR                   (2)
#define ILLUMI_COM_TX_C_PATCH                   (2)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "illumi_cfg_private.h"
#include "illumi_comtx.h"

#include "dim_usadjbysw.h"
#include "oxcan.h"
#include "calibration.h"
#include "iohw_diflt.h"
#include "rim_ctl.h"
#include "vardef.h"
#include "veh_opemd.h"
#include "vptran_sel.h"
#include "dio_if.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((ILLUMI_COM_TX_C_MAJOR != ILLUMI_COM_TX_H_MAJOR) || \
     (ILLUMI_COM_TX_C_MINOR != ILLUMI_COM_TX_H_MINOR) || \
     (ILLUMI_COM_TX_C_PATCH != ILLUMI_COM_TX_H_PATCH))
#error "illumi_comtx.c and illumi_comtx.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ILLUMI_RHEO_EVTX_NUM_STS                (3U)
#define ILLUMI_RHEO_EVTX_STS_FIN                (0U)
#define ILLUMI_RHEO_EVTX_STS_TRG                (1U)
#define ILLUMI_RHEO_EVTX_STS_WAI                (2U)

#define ILLUMI_RHEO_CHK_TX_NUM                  (8U)
#define ILLUMI_RHEO_CHK_TX_ACK                  (0x01U)
#define ILLUMI_RHEO_CHK_TX_TOUT                 (0x02U)
#define ILLUMI_RHEO_CHK_TX_RQST                 (0x04U)

#define ILLUMI_RHEO_TX_ACT_TO_FIN               (0U)
#define ILLUMI_RHEO_TX_ACT_TO_TRG               (1U)
#define ILLUMI_RHEO_TX_ACT_TRG                  (2U)
#define ILLUMI_RHEO_TX_ACT_TO_WAI               (3U)
#define ILLUMI_RHEO_TX_ACT_WAI                  (4U)
#define ILLUMI_RHEO_TX_ACT_INIT                 (5U)

#define ILLUMI_RHEO_TX_NUM_STM                  (ILLUMI_RHEO_EVTX_NUM_STS * ILLUMI_RHEO_CHK_TX_NUM)

#define ILLUMI_RHEO_TX_MAX                      (100U)  /* RHEOSTAT MAX Value  */
#define ILLUMI_DUTY_TX_MAX                      (1000U) /* IL2_DUTY,TR2_DUTY MAX Value  */

#define ILLUMI_RHEOPOS_TX_DEF                   (31U)   /* RHEO_POS Default Value  */

#define ILLUMI_LOUNGE_ON                        (0x00U)
#define ILLUMI_LOUNGE_OFF                       (0x01U)
#define ILLUMI_LOUNGE_UNK                       (0x02U) /* ILL_OF Unknown */

#define ILLUMI_TAIL_CN_UNK                      (0x00U)  /* TAIL_CN Unknown     */
#define ILLUMI_TAIL_CN_ACT                      (0x02U)  /* TAIL_CN Active      */
#define ILLUMI_TAIL_CN_INACT                    (0x03U)  /* TAIL_CN Inactive    */

#define ILLUMI_DIM_LVL_RHEOSTAT_NUM             (CALIB_MCUID0270_RHEO_STEP)
#define ILLUMI_DIM_LVL_TR2_NUM                  (CALIB_MCUID0292_TR2_STEP)
#define ILLUMI_DIM_LVL_IL2_NUM                  (CALIB_MCUID0314_IL2_STEP)
#define ILLUMI_DIM_LVL_BKLT_NUM                 (CALIB_BL_STEP)
#define ILLUMI_DIM_LVL_OFS                      (1U)    /* Lelel Offset Value  */
#define ILLUMI_ILL_OUT_TX_MAX                   (100U)  /* ILL_OUT MAX Value   */

#define ILLUMI_COMTX_IL2STS_PARK                (0U)
#define ILLUMI_COMTX_IL2STS_DRIVE               (1U)
#define ILLUMI_COMTX_IL2STS_INVLD               (2U)

#define ILLUMI_COMTX_FADE_TIM                   (1000U / ILLUMI_COM_TX_TICK)
#define ILLUMI_COMTX_B_P_DLY_MAX                (1000U / ILLUMI_COM_TX_TICK)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U2      u2_fadein;
    U2      u2_fadeout;
}ST_ILL_FADE;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2       u2_s_illumi_tc_nmwk_tout;
static U2       u2_s_illumi_rheo_nmwk_tout;
static U2       u2_s_illumi_rheo_evt_tout;
static U1       u1_s_illumi_rheo_tx_ctrl;

static U1       u1_s_illumi_rheo_tx_pct;
static U1       u1_s_illumi_rheo_tx_ack;

static U2       u2_s_illumi_rheo_tx_tr;
static U2       u2_s_illumi_rheo_tx_il;
static U1       u1_s_illumi_lounge_tx;
static U1       u1_s_illumi_rheo_tx_pos;
static U1       u1_s_illumi_tail_cn_tx;

static U2       u2_s_illumi_comtx_b_p_dlycnt;
static U2       u2_s_illumi_comtx_fade_tmelpsd;
static U1       u1_s_illumi_comtx_il2sts;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static        U2       u2_s_IllumiILFadeJdg(const U2 u2_a_LVL, const U2 u2_a_PCT);
static        U1       u1_s_IllumiILFadeDriveJdg(void);
static        void     vd_s_IllumiRheoTx(const U2 * u2_ap_DIM_LVL);
static        void     vd_s_IllumiLoungeTx(const U2 * u2_ap_DIM_LVL);
static        U1       u1_s_IllumiLoungeHysJdg(const U2 * u2_ap_DIM_LVL);
static        void     vd_s_IllumiPosTx(const U2 * u2_ap_DIM_LVL);
static        void     vd_s_IllumiTftbkTx(const U2 * u2_ap_DIM_LVL);
static        void     vd_s_IllumiTailCancelTx(void);
static        void     vd_s_IllumiRheoTxAct(const U2 u2_a_ACT, const U1 u1_a_RHEOPCT, const U1 u1_a_RHEODRTX);
static        U2       u2_s_IllumiRheoTxCtrl(const U2 * u2_ap_DIM_LVL, U1 * u1_ap_RHEOPCT, U1 * u1_ap_RHEODRTX);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_IllumiComTxInit(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IllumiComTxInit(void)
{
#if ((defined(ComConf_ComSignal_RHEO_IN)) || (defined(ComConf_ComSignal_ILL_OUT)))
    U1                   u1_t_tx;
#endif /* #if ((defined(ComConf_ComSignal_RHEO_IN)) || (defined(ComConf_ComSignal_ILL_OUT))) */
    U1                   u1_t_rheosw;


    u2_s_illumi_tc_nmwk_tout   = (U2)U2_MAX;
    u2_s_illumi_rheo_nmwk_tout = (U2)U2_MAX;
    u2_s_illumi_rheo_evt_tout  = (U2)U2_MAX;
    u1_s_illumi_rheo_tx_ctrl   = (U1)ILLUMI_RHEO_EVTX_STS_FIN;
    u1_t_rheosw   = u1_CALIB_MCUID0430_RHEOSW;

    u1_s_illumi_rheo_tx_pct = (U1)0U;
#if ((defined(ComConf_ComSignal_RHEO_IN)) || (defined(ComConf_ComSignal_ILL_OUT)))
    u1_t_tx = (U1)U1_MAX;
#endif /* #if ((defined(ComConf_ComSignal_RHEO_IN)) || (defined(ComConf_ComSignal_ILL_OUT))) */

    if(u1_t_rheosw == (U1)CALIB_MCUID0430_THUMB_WHEEL){
        u1_s_illumi_tail_cn_tx = (U1)ILLUMI_TAIL_CN_UNK;
    }
    else{
        u1_s_illumi_tail_cn_tx = (U1)ILLUMI_TAIL_CN_INACT;
    }
    u1_s_illumi_rheo_tx_ack    = (U1)0U;
    u2_s_illumi_rheo_tx_tr     = (U2)0U;
    u2_s_illumi_rheo_tx_il     = (U2)0U;
    u1_s_illumi_rheo_tx_pos    = (U1)ILLUMI_RHEOPOS_TX_DEF;

#ifdef ComConf_ComSignal_ILL_OUT
    (void)Com_SendSignal(ComConf_ComSignal_ILL_OUT, &u1_t_tx);
#endif /* #ifdef ComConf_ComSignal_ILL_OUT */
#ifdef ComConf_ComSignal_RHEO_IN
    (void)Com_SendSignal(ComConf_ComSignal_RHEO_IN, &u1_t_tx);
#endif /* #ifdef ComConf_ComSignal_RHEO_IN */
    (void)Com_SendSignal(ComConf_ComSignal_RHEOSTAT, &u1_s_illumi_rheo_tx_pct);
    (void)Com_SendSignal(ComConf_ComSignal_TR2_DUTY, &u2_s_illumi_rheo_tx_tr);
    (void)Com_SendSignal(ComConf_ComSignal_IL2_DUTY, &u2_s_illumi_rheo_tx_il);
    (void)Com_SendSignal(ComConf_ComSignal_RHEO_POS, &u1_s_illumi_rheo_tx_pos);

    vd_s_IllumiTailCancelTx();
    u2_s_illumi_comtx_b_p_dlycnt   = (U2)ILLUMI_COMTX_B_P_DLY_MAX;
    u2_s_illumi_comtx_fade_tmelpsd = (U2)U2_MAX;
    u1_s_illumi_comtx_il2sts       = (U1)ILLUMI_COMTX_IL2STS_INVLD;
}
/*===================================================================================================================================*/
/*  void    vd_g_IllumiComTxBonInit(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IllumiComTxBonInit(void)
{
    U1                  u1_t_data;
    U1                  u1_t_lounge_tx;
    U2                  u2_tp_dim_lvl[ILLUMI_NUM_DIM_LVL];

    u1_t_data = (U1)ILLUMI_LOUNGE_UNK;
    vd_g_Rim_WriteU1((U2)RIMID_U1_ILLUMI_LOUNGE, u1_t_data);
    u1_s_illumi_lounge_tx = u1_t_data;

    u2_tp_dim_lvl[ILLUMI_DIM_LVL_USADJ_DAY]   = u2_g_DimLvlUsadjust((U1)DIM_DAYNIGHT_LVL_DAY);
    u2_tp_dim_lvl[ILLUMI_DIM_LVL_USADJ_NIGHT] = u2_g_DimLvlUsadjust((U1)DIM_DAYNIGHT_LVL_NIGHT);
    u2_tp_dim_lvl[ILLUMI_DIM_LVL_DAYNIGHT]    = (U2)u1_g_DimLvlDaynight();
    u1_t_lounge_tx = u1_s_IllumiLoungeHysJdg(&u2_tp_dim_lvl[0]);

    (void)Com_SendSignal(ComConf_ComSignal_ILL_OF, &u1_t_lounge_tx);
}
/*===================================================================================================================================*/
/*  void    vd_g_IllumiComTxRstwkInit(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IllumiComTxRstwkInit(void)
{
    U1                  u1_t_data;
    U1                  u1_t_sts;
    U1                  u1_t_lounge_tx;
    U2                  u2_tp_dim_lvl[ILLUMI_NUM_DIM_LVL];

    u1_t_data = (U1)ILLUMI_LOUNGE_UNK;
    u1_t_sts = u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_ILLUMI_LOUNGE, &u1_t_data);
    if((u1_t_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        u1_s_illumi_lounge_tx = u1_t_data;
    }
    else{
        u1_s_illumi_lounge_tx = (U1)ILLUMI_LOUNGE_UNK;
    }
    u2_tp_dim_lvl[ILLUMI_DIM_LVL_USADJ_DAY]   = u2_g_DimLvlUsadjust((U1)DIM_DAYNIGHT_LVL_DAY);
    u2_tp_dim_lvl[ILLUMI_DIM_LVL_USADJ_NIGHT] = u2_g_DimLvlUsadjust((U1)DIM_DAYNIGHT_LVL_NIGHT);
    u2_tp_dim_lvl[ILLUMI_DIM_LVL_DAYNIGHT]    = (U2)u1_g_DimLvlDaynight();
    u1_t_lounge_tx = u1_s_IllumiLoungeHysJdg(&u2_tp_dim_lvl[0]);

    (void)Com_SendSignal(ComConf_ComSignal_ILL_OF, &u1_t_lounge_tx);
}
/*===================================================================================================================================*/
/*  U2      u2_g_IllumiComTx(const U2 * u2_ap_DIM_LVL, const U2 u2_a_OW)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_IllumiComTx(const U2 * u2_ap_DIM_LVL, const U2 u2_a_OW)
{
    vd_s_IllumiRheoTx(u2_ap_DIM_LVL);
    vd_s_IllumiLoungeTx(u2_ap_DIM_LVL);
    vd_s_IllumiTftbkTx(u2_ap_DIM_LVL);
    vd_s_IllumiTailCancelTx();
    vd_s_IllumiPosTx(u2_ap_DIM_LVL);

    return((U2)0U);
}
/*===================================================================================================================================*/
/*  U2      u2_g_IllumiTRTx(const U2 * u2_ap_DIM_LVL, const U2 u2_a_OW)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_IllumiTRTx(const U2 * u2_ap_DIM_LVL, const U2 u2_a_OW)
{
    U2                  u2_t_pct;
    U2                  u2_t_lvl;

    u2_t_lvl = u2_ap_DIM_LVL[ILLUMI_DIM_LVL_USADJ_NIGHT];
    if(u2_t_lvl < (U2)ILLUMI_DIM_LVL_TR2_NUM){
        u2_t_lvl = ((U2)ILLUMI_DIM_LVL_TR2_NUM - (U2)ILLUMI_DIM_LVL_OFS) - u2_t_lvl;
        u2_t_pct = u2_CALIB_MCUID0292_TR2_PCT[u2_t_lvl];
    }
    else{
        u2_t_pct = (U2)ILLUMI_DUTY_TX_MAX;
    }
    if(u2_t_pct != u2_s_illumi_rheo_tx_tr){
       (void)Com_SendSignal(ComConf_ComSignal_TR2_DUTY, &u2_t_pct);
        (void)Com_TriggerIPDUSend((PduIdType)MSG_MET1S38_TXCH0);
    }
    u2_s_illumi_rheo_tx_tr = u2_t_pct;

    return((U2)0U);
}
/*===================================================================================================================================*/
/*  U2      u2_g_IllumiILTx(const U2 * u2_ap_DIM_LVL, const U2 u2_a_OW)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_IllumiILTx(const U2 * u2_ap_DIM_LVL, const U2 u2_a_OW)
{
    U2                  u2_t_pct;
    U2                  u2_t_lvl;

    u2_t_lvl = u2_ap_DIM_LVL[ILLUMI_DIM_LVL_USADJ_NIGHT];
    if(u2_t_lvl < (U2)ILLUMI_DIM_LVL_IL2_NUM){
        u2_t_lvl = ((U2)ILLUMI_DIM_LVL_IL2_NUM - (U2)ILLUMI_DIM_LVL_OFS) - u2_t_lvl;
        u2_t_pct = u2_CALIB_MCUID0314_IL2_PCT[u2_t_lvl];
        u2_t_pct = u2_s_IllumiILFadeJdg(u2_t_lvl, u2_t_pct);
    }
    else{
        u2_t_pct = (U2)ILLUMI_DUTY_TX_MAX;
    }
    if(u2_t_pct != u2_s_illumi_rheo_tx_il){
        (void)Com_SendSignal(ComConf_ComSignal_IL2_DUTY, &u2_t_pct);
        (void)Com_TriggerIPDUSend((PduIdType)MSG_MET1S38_TXCH0);
    }
    u2_s_illumi_rheo_tx_il = u2_t_pct;

    return((U2)0U);
}

/*===================================================================================================================================*/
/*  static U2   u2_s_IllumiILFadeJdg(const U2 u2_a_LVL, const U2 u2_a_PCT)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U2  u2_a_LVL : Step                                                                                              */
/*                  U2  u2_a_PCT : Duty[LSB:0.1%]                                                                                    */
/*  Return:         U2  u2_t_pct : Duty[LSB:0.1%]                                                                                    */
/*===================================================================================================================================*/
static U2   u2_s_IllumiILFadeJdg(const U2 u2_a_LVL, const U2 u2_a_PCT)
{
    static const U2     u2_s_ILLUMI_COMTX_FADE_PCT_LSB = (U2)10000U;
    static const U2     u2_s_ILLUMI_COMTX_FADE_PCT_MAX = (U2)10000U;
    static const ST_ILL_FADE    st_sp_ILLUMI_FADE_PCT[ILLUMI_COMTX_FADE_TIM] = {
/*      FadeIn      FadeOut                   */
        {(U2)0U,    (U2)10000U},    /*    0ms */
        {(U2)0U,    (U2)10000U},    /*   20ms */
        {(U2)0U,    (U2)10000U},    /*   40ms */
        {(U2)0U,    (U2)10000U},    /*   60ms */
        {(U2)0U,    (U2)10000U},    /*   80ms */
        {(U2)330U,  (U2)7854U },    /*  100ms */
        {(U2)330U,  (U2)7854U },    /*  120ms */
        {(U2)330U,  (U2)7854U },    /*  140ms */
        {(U2)330U,  (U2)7854U },    /*  160ms */
        {(U2)330U,  (U2)7854U },    /*  180ms */
        {(U2)737U,  (U2)6111U },    /*  200ms */
        {(U2)737U,  (U2)6111U },    /*  220ms */
        {(U2)737U,  (U2)6111U },    /*  240ms */
        {(U2)737U,  (U2)6111U },    /*  260ms */
        {(U2)737U,  (U2)6111U },    /*  280ms */
        {(U2)1237U, (U2)4696U },    /*  300ms */
        {(U2)1237U, (U2)4696U },    /*  320ms */
        {(U2)1237U, (U2)4696U },    /*  340ms */
        {(U2)1237U, (U2)4696U },    /*  360ms */
        {(U2)1237U, (U2)4696U },    /*  380ms */
        {(U2)1853U, (U2)3546U },    /*  400ms */
        {(U2)1853U, (U2)3546U },    /*  420ms */
        {(U2)1853U, (U2)3546U },    /*  440ms */
        {(U2)1853U, (U2)3546U },    /*  460ms */
        {(U2)1853U, (U2)3546U },    /*  480ms */
        {(U2)2612U, (U2)2612U },    /*  500ms */
        {(U2)2612U, (U2)2612U },    /*  520ms */
        {(U2)2612U, (U2)2612U },    /*  540ms */
        {(U2)2612U, (U2)2612U },    /*  560ms */
        {(U2)2612U, (U2)2612U },    /*  580ms */
        {(U2)3546U, (U2)1853U },    /*  600ms */
        {(U2)3546U, (U2)1853U },    /*  620ms */
        {(U2)3546U, (U2)1853U },    /*  640ms */
        {(U2)3546U, (U2)1853U },    /*  660ms */
        {(U2)3546U, (U2)1853U },    /*  680ms */
        {(U2)4696U, (U2)1237U },    /*  700ms */
        {(U2)4696U, (U2)1237U },    /*  720ms */
        {(U2)4696U, (U2)1237U },    /*  740ms */
        {(U2)4696U, (U2)1237U },    /*  760ms */
        {(U2)4696U, (U2)1237U },    /*  780ms */
        {(U2)6111U, (U2)737U  },    /*  800ms */
        {(U2)6111U, (U2)737U  },    /*  820ms */
        {(U2)6111U, (U2)737U  },    /*  840ms */
        {(U2)6111U, (U2)737U  },    /*  860ms */
        {(U2)6111U, (U2)737U  },    /*  880ms */
        {(U2)7854U, (U2)330U  },    /*  900ms */
        {(U2)7854U, (U2)330U  },    /*  920ms */
        {(U2)7854U, (U2)330U  },    /*  940ms */
        {(U2)7854U, (U2)330U  },    /*  960ms */
        {(U2)7854U, (U2)330U  }     /*  980ms */
    };

    U1                  u1_t_at;
    U1                  u1_t_ig;
    U2                  u2_t_cnt;
    U2                  u2_t_min;
    U1                  u1_t_sts;
    U2                  u2_t_pct;

    u1_t_at = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_AT);
    u1_t_ig = u1_g_VehopemdIgnOn();

    if((u1_CALIB_MCUID0741_IL2OUTILLRUN == (U1)TRUE) && (u1_t_at == (U1)TRUE)
    && (u1_t_ig == (U1)TRUE)){
        if(u2_a_LVL == (U2)0U){
            u2_t_min = u2_CALIB_MCUID0743_IOUTILLRUNMAX;
        }
        else{
            u2_t_min = u2_CALIB_MCUID0742_IOUTILLRUN;
        }

        u1_t_sts = u1_s_IllumiILFadeDriveJdg();
        if(u1_t_sts == (U1)ILLUMI_COMTX_IL2STS_DRIVE){
            if(u2_s_illumi_comtx_fade_tmelpsd < (U2)ILLUMI_COMTX_FADE_TIM){
                u2_t_cnt = st_sp_ILLUMI_FADE_PCT[u2_s_illumi_comtx_fade_tmelpsd].u2_fadeout;
            }
            else{
                u2_t_cnt = (U2)0U;
            }
        }
        else{
            if(u2_s_illumi_comtx_fade_tmelpsd < (U2)ILLUMI_COMTX_FADE_TIM){
                u2_t_cnt = st_sp_ILLUMI_FADE_PCT[u2_s_illumi_comtx_fade_tmelpsd].u2_fadein;
            }
            else{
                u2_t_cnt = u2_s_ILLUMI_COMTX_FADE_PCT_MAX;
            }
        }

        if(u2_a_PCT >= u2_t_min){
            u2_t_pct = (U2)((U4)u2_t_min + ((((U4)u2_a_PCT - (U4)u2_t_min) * (U4)u2_t_cnt) / (U4)u2_s_ILLUMI_COMTX_FADE_PCT_LSB));
        }
        else{
            u2_t_pct = (U2)((U4)u2_t_min - ((((U4)u2_t_min - (U4)u2_a_PCT) * (U4)u2_t_cnt) / (U4)u2_s_ILLUMI_COMTX_FADE_PCT_LSB));
        }
    }
    else{
        u2_s_illumi_comtx_b_p_dlycnt   = (U2)ILLUMI_COMTX_B_P_DLY_MAX;
        u2_s_illumi_comtx_fade_tmelpsd = (U2)U2_MAX;
        u1_s_illumi_comtx_il2sts       = (U1)ILLUMI_COMTX_IL2STS_INVLD;
        u2_t_pct = u2_a_PCT;
    }
    return(u2_t_pct);
}

/*===================================================================================================================================*/
/*  static U1   u1_s_IllumiILFadeDriveJdg(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1  u1_t_sts : Status(Drive/Park/Invalid)                                                                        */
/*===================================================================================================================================*/
static U1   u1_s_IllumiILFadeDriveJdg(void)
{
    U1                  u1_t_sts;
    U1                  u1_t_b_p;
    U1                  u1_t_chk;
    U2                  u2_t_range;
    U1                  u1_t_sftsts;
    U1                  u1_t_sft_p;

    u1_t_b_p = (U1)TRUE;
    u1_t_chk = (U1)Com_GetIPDUStatus(MSG_ECT1G01_RXCH0) & (U1)COM_NO_RX;
    if(u1_t_chk == (U1)0U){
        (void)Com_ReceiveSignal(ComConf_ComSignal_B_P, &u1_t_b_p);
    }
    if(u1_t_b_p == (U1)TRUE){
        u2_s_illumi_comtx_b_p_dlycnt = (U2)U2_MAX;
    }
    else if(u2_s_illumi_comtx_b_p_dlycnt >= (U2)U2_MAX){
        u2_s_illumi_comtx_b_p_dlycnt = (U2)0U;
    }
    else if(u2_s_illumi_comtx_b_p_dlycnt >= (U2)ILLUMI_COMTX_B_P_DLY_MAX){
        u2_s_illumi_comtx_b_p_dlycnt = (U2)ILLUMI_COMTX_B_P_DLY_MAX;
    }
    else{
        u2_s_illumi_comtx_b_p_dlycnt++;
    }

    u2_t_range   = (U2)0x0000U;
    u1_t_sftsts  = u1_g_VptranRangeSelected(&u2_t_range);
    u1_t_sft_p = (U1)FALSE;
    /* Treat as shift P if signal is not VALID */
    if ((u1_t_sftsts != (U1)VPTRAN_VALID) || ((u2_t_range & (U2)VPTRAN_RNG_MSK) == (U2)VPTRAN_OFF) || ((u2_t_range & (U2)VPTRAN_RNG_MSK) == (U2)VPTRAN_RNG_P_ON)) {
        u1_t_sft_p = (U1)TRUE;
    }

    if(u1_t_sft_p == (U1)FALSE){                                                    /* RangeValid w/o P             */
        u1_t_sts = (U1)ILLUMI_COMTX_IL2STS_DRIVE;
    }
    else if(u1_t_b_p == (U1)TRUE){                                                  /* B_P=1 or NORX                */
        u1_t_sts = (U1)ILLUMI_COMTX_IL2STS_PARK;
    }
    else if(u2_s_illumi_comtx_b_p_dlycnt >= (U2)ILLUMI_COMTX_B_P_DLY_MAX){          /* B_P=0(1s elapsed)            */
        u1_t_sts = (U1)ILLUMI_COMTX_IL2STS_DRIVE;
    }
    else{
        u1_t_sts = (U1)ILLUMI_COMTX_IL2STS_PARK;
    }

    if((u1_s_illumi_comtx_il2sts < (U1)ILLUMI_COMTX_IL2STS_INVLD)
    && (u1_t_sts != u1_s_illumi_comtx_il2sts)){
        u2_s_illumi_comtx_fade_tmelpsd = (U2)0U;
    }
    else if(u2_s_illumi_comtx_fade_tmelpsd >= (U2)U2_MAX){
        u2_s_illumi_comtx_fade_tmelpsd = (U2)U2_MAX;
    }
    else{
        u2_s_illumi_comtx_fade_tmelpsd++;
    }
    u1_s_illumi_comtx_il2sts = u1_t_sts;

    return(u1_t_sts);
}

/*===================================================================================================================================*/
/*  void    vd_g_IllumiRheoTxAck(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IllumiRheoTxAck(void)
{
    u1_s_illumi_rheo_tx_ack = (U1)ILLUMI_RHEO_CHK_TX_ACK;
}
/*===================================================================================================================================*/
/*  U1      u1_g_IllumiRheoTxNmwk(const U2 u2_a_TOUT)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_IllumiRheoTxNmwk(const U2 u2_a_TOUT)
{
    U1                   u1_t_nmwk;

    if(u2_s_illumi_rheo_nmwk_tout < u2_a_TOUT){
        u1_t_nmwk = (U1)TRUE;
    }
    else{
        u1_t_nmwk = (U1)FALSE;
    }

    return(u1_t_nmwk);
}
/*===================================================================================================================================*/
/*  static void    vd_s_IllumiRheoTx(const U2 * u2_ap_DIM_LVL)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_IllumiRheoTx(const U2 * u2_ap_DIM_LVL)
{
    U2                  u2_t_act;
    U1                  u1_t_pct;
    U1                  u1_t_drtx;

    u1_t_pct  = (U1)0U;
    u1_t_drtx = (U1)0U;

    u2_t_act = u2_s_IllumiRheoTxCtrl(u2_ap_DIM_LVL, &u1_t_pct, &u1_t_drtx);
    vd_s_IllumiRheoTxAct(u2_t_act, u1_t_pct, u1_t_drtx);
}
/*===================================================================================================================================*/
/*  static U2    u2_s_IllumiRheoTxCtrl(const U2 * u2_ap_DIM_LVL, U1 * u1_ap_RHEOPCT, U1 * u1_ap_RHEODRTX)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2      u2_s_IllumiRheoTxCtrl(const U2 * u2_ap_DIM_LVL, U1 * u1_ap_RHEOPCT, U1 * u1_ap_RHEODRTX)
{
    static const U2     u2_sp_ILLUMI_RHEO_TX_TOUT[ILLUMI_RHEO_EVTX_NUM_STS] = {
        (U2)0U,             /* ILLUMI_RHEO_EVTX_STS_FIN */
        (U2)(400U / 20U),   /* ILLUMI_RHEO_EVTX_STS_TRG */
        (U2)(200U / 20U)    /* ILLUMI_RHEO_EVTX_STS_WAI */
    };
    static const U1     u1_sp_ILLUMI_RHEO_STM[ILLUMI_RHEO_TX_NUM_STM] = {
        (U1)ILLUMI_RHEO_TX_ACT_TO_FIN, (U1)ILLUMI_RHEO_TX_ACT_TRG,    (U1)ILLUMI_RHEO_TX_ACT_WAI,
        (U1)ILLUMI_RHEO_TX_ACT_TO_FIN, (U1)ILLUMI_RHEO_TX_ACT_TO_WAI, (U1)ILLUMI_RHEO_TX_ACT_WAI,
        (U1)ILLUMI_RHEO_TX_ACT_TO_FIN, (U1)ILLUMI_RHEO_TX_ACT_TO_FIN, (U1)ILLUMI_RHEO_TX_ACT_TO_FIN,
        (U1)ILLUMI_RHEO_TX_ACT_TO_FIN, (U1)ILLUMI_RHEO_TX_ACT_TO_WAI, (U1)ILLUMI_RHEO_TX_ACT_TO_FIN,
        (U1)ILLUMI_RHEO_TX_ACT_TO_TRG, (U1)ILLUMI_RHEO_TX_ACT_TRG,    (U1)ILLUMI_RHEO_TX_ACT_WAI,
        (U1)ILLUMI_RHEO_TX_ACT_TO_TRG, (U1)ILLUMI_RHEO_TX_ACT_TO_WAI, (U1)ILLUMI_RHEO_TX_ACT_WAI,
        (U1)ILLUMI_RHEO_TX_ACT_TO_TRG, (U1)ILLUMI_RHEO_TX_ACT_TO_FIN, (U1)ILLUMI_RHEO_TX_ACT_TO_FIN,
        (U1)ILLUMI_RHEO_TX_ACT_TO_TRG, (U1)ILLUMI_RHEO_TX_ACT_TO_WAI, (U1)ILLUMI_RHEO_TX_ACT_TO_FIN
    };

    U2                  u2_t_lvl;
    U2                  u2_t_tout;
    U2                  u2_t_chk;
    U2                  u2_t_act;

    U1                  u1_t_pct;
    U1                  u1_t_stschk;
#ifdef ComConf_ComSignal_RHEO_IN
    U1                  u1_t_drtx;
#endif

    u2_t_lvl = u2_ap_DIM_LVL[ILLUMI_DIM_LVL_USADJ_NIGHT];
    if((u1_s_illumi_rheo_tx_ctrl < (U1)ILLUMI_RHEO_EVTX_NUM_STS   ) &&
       (u2_t_lvl                 < (U2)ILLUMI_DIM_LVL_RHEOSTAT_NUM)){
        u2_t_lvl = ((U2)ILLUMI_DIM_LVL_RHEOSTAT_NUM - (U2)ILLUMI_DIM_LVL_OFS) - u2_t_lvl;
        u1_t_pct = u1_CALIB_MCUID0270_RHEO_PCT[u2_t_lvl];
#ifdef ComConf_ComSignal_RHEO_IN
        u1_t_drtx    = u1_t_pct;
#endif
        u1_t_stschk = u1_s_illumi_rheo_tx_ack & (U1)ILLUMI_RHEO_CHK_TX_ACK;

        if(u1_t_pct != u1_s_illumi_rheo_tx_pct){
            u1_t_stschk |= (U1)ILLUMI_RHEO_CHK_TX_RQST;
        }

        if(u2_s_illumi_rheo_evt_tout < (U2)U2_MAX){
            u2_s_illumi_rheo_evt_tout++;
        }

        if(u2_s_illumi_rheo_nmwk_tout < (U2)U2_MAX){
            u2_s_illumi_rheo_nmwk_tout++;
        }

        u2_t_tout = u2_sp_ILLUMI_RHEO_TX_TOUT[u1_s_illumi_rheo_tx_ctrl];
        if(u2_s_illumi_rheo_evt_tout >= u2_t_tout){
            u1_t_stschk |= (U1)ILLUMI_RHEO_CHK_TX_TOUT;
        }

        u2_t_chk = ((U2)u1_t_stschk * (U2)ILLUMI_RHEO_EVTX_NUM_STS) + (U2)u1_s_illumi_rheo_tx_ctrl;
        u2_t_act = (U2)u1_sp_ILLUMI_RHEO_STM[u2_t_chk];
    }
    else{
        u2_t_act   = (U2)ILLUMI_RHEO_TX_ACT_INIT;
        u1_t_pct   = (U1)ILLUMI_RHEO_TX_MAX;
#ifdef ComConf_ComSignal_RHEO_IN
        u1_t_drtx  = (U1)ILLUMI_RHEO_TX_MAX;
#endif
    }

    (*u1_ap_RHEOPCT)   = u1_t_pct;
#ifdef ComConf_ComSignal_RHEO_IN
    (*u1_ap_RHEODRTX)  = u1_t_drtx;
#endif

    return(u2_t_act);
}
/*===================================================================================================================================*/
/*  static void    vd_s_IllumiRheoTxAct(const U2 u2_a_ACT, const U1 u1_a_RHEOPCT, const U1 u1_a_RHEODRTX)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_IllumiRheoTxAct(const U2 u2_a_ACT, const U1 u1_a_RHEOPCT, const U1 u1_a_RHEODRTX)
{
    switch(u2_a_ACT){
        case (U2)ILLUMI_RHEO_TX_ACT_TO_FIN:
            u1_s_illumi_rheo_tx_ctrl   = (U1)ILLUMI_RHEO_EVTX_STS_FIN;
            break;
        case (U2)ILLUMI_RHEO_TX_ACT_TRG:
            u1_s_illumi_rheo_tx_ctrl   = (U1)ILLUMI_RHEO_EVTX_STS_TRG;
            break;
        case (U2)ILLUMI_RHEO_TX_ACT_TO_WAI:
            u2_s_illumi_rheo_evt_tout  = (U2)0U;
            u1_s_illumi_rheo_tx_ctrl   = (U1)ILLUMI_RHEO_EVTX_STS_WAI;
            break;
        case (U2)ILLUMI_RHEO_TX_ACT_WAI:
            u1_s_illumi_rheo_tx_ctrl   = (U1)ILLUMI_RHEO_EVTX_STS_WAI;
            break;
        case (U2)ILLUMI_RHEO_TX_ACT_TO_TRG:
            u2_s_illumi_rheo_nmwk_tout = (U2)0U;
            u2_s_illumi_rheo_evt_tout  = (U2)0U;
            u1_s_illumi_rheo_tx_ctrl   = (U1)ILLUMI_RHEO_EVTX_STS_TRG;

            u1_s_illumi_rheo_tx_ack    = (U1)0U;
            u1_s_illumi_rheo_tx_pct    = u1_a_RHEOPCT;
            (void)Com_SendSignal(ComConf_ComSignal_RHEOSTAT, &u1_s_illumi_rheo_tx_pct);
            (void)Com_TriggerIPDUSend((PduIdType)MSG_MET1S01_TXCH0);
            break;
     /* case ILLUMI_RHEO_TX_ACT_INIT: */
        default:
            u2_s_illumi_rheo_nmwk_tout = (U2)U2_MAX;
            u2_s_illumi_rheo_evt_tout  = (U2)U2_MAX;
            u1_s_illumi_rheo_tx_ctrl   = (U1)ILLUMI_RHEO_EVTX_STS_FIN;

            u1_s_illumi_rheo_tx_ack    = (U1)0U;
            u1_s_illumi_rheo_tx_pct    = u1_a_RHEOPCT;
            (void)Com_SendSignal(ComConf_ComSignal_RHEOSTAT, &u1_s_illumi_rheo_tx_pct);
            break;
    }

#ifdef ComConf_ComSignal_RHEO_IN
    (void)Com_SendSignal(ComConf_ComSignal_RHEO_IN, &u1_a_RHEODRTX);
#endif
}
/*===================================================================================================================================*/
/*  static void    vd_s_IllumiLoungeTx(const U2 * u2_ap_DIM_LVL)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_IllumiLoungeTx(const U2 * u2_ap_DIM_LVL)
{
    U1                  u1_t_tx;

    u1_t_tx = u1_s_IllumiLoungeHysJdg(u2_ap_DIM_LVL);
    if(u1_t_tx != u1_s_illumi_lounge_tx){
        (void)Com_SendSignal(ComConf_ComSignal_ILL_OF, &u1_t_tx);
        (void)Com_TriggerIPDUSend((PduIdType)MSG_MET1S01_TXCH0);
    }
    u1_s_illumi_lounge_tx = u1_t_tx;
}
/*===================================================================================================================================*/
/*  static void    vd_s_IllumiPosTx(const U2 * u2_ap_DIM_LVL)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_IllumiPosTx(const U2 * u2_ap_DIM_LVL)
{
    U2                  u2_t_daynight;
    U2                  u2_t_lvl;
    U1                  u1_t_tx;

    u2_t_daynight = u2_ap_DIM_LVL[ILLUMI_DIM_LVL_DAYNIGHT];
    if(u2_t_daynight < (U2)DIM_DAYNIGHT_NUM_LVL){
        u2_t_lvl = u2_ap_DIM_LVL[u2_t_daynight];
        if(u2_t_lvl       < (U2)ILLUMI_DIM_LVL_RHEOSTAT_NUM){
            u1_t_tx = (U1)u2_t_lvl;
        }
        else{
            u1_t_tx = (U1)ILLUMI_DIM_LVL_RHEOSTAT_NUM - (U1)1U;
        }
    }
    else{
        u1_t_tx = (U1)ILLUMI_RHEOPOS_TX_DEF;
    }

    if(u1_t_tx != u1_s_illumi_rheo_tx_pos){
        (void)Com_SendSignal(ComConf_ComSignal_RHEO_POS, &u1_t_tx);
        (void)Com_TriggerIPDUSend((PduIdType)MSG_MET1S39_TXCH0);
    }
    u1_s_illumi_rheo_tx_pos = u1_t_tx;
}
/*===================================================================================================================================*/
/*  static void    vd_s_IllumiTftbkTx(const U2 * u2_ap_DIM_LVL)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_IllumiTftbkTx(const U2 * u2_ap_DIM_LVL)
{
#ifdef ComConf_ComSignal_ILL_OUT

    U2                  u2_t_daynight;
    U2                  u2_t_lvl;
    U1                  u1_t_tx;

    u1_t_tx       = (U1)U1_MAX;
    u2_t_daynight = u2_ap_DIM_LVL[ILLUMI_DIM_LVL_DAYNIGHT];
    if(u2_t_daynight < (U2)ILLUMI_DIM_LVL_DAYNIGHT){
        u2_t_lvl = u2_ap_DIM_LVL[u2_t_daynight];
        if(u2_t_lvl < (U2)ILLUMI_DIM_LVL_BKLT_NUM){
            u2_t_lvl = ((U2)ILLUMI_DIM_LVL_BKLT_NUM - (U2)ILLUMI_DIM_LVL_OFS) - u2_t_lvl;
            if(u2_t_daynight == (U2)ILLUMI_DIM_LVL_USADJ_DAY){
                u1_t_tx = u1_CALIB_MCUID0342_BL_PCT_DAY[u2_t_lvl];
            }
            else{
                u1_t_tx = u1_CALIB_MCUID0386_BL_PCT_NIGHT[u2_t_lvl];
            }
        }
        else{
            u1_t_tx = (U1)ILLUMI_RHEO_TX_MAX;
        }
    }

    (void)Com_SendSignal(ComConf_ComSignal_ILL_OUT, &u1_t_tx);
#endif
}
/*===================================================================================================================================*/
/*  static void    vd_s_IllumiTailCancelTx(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_IllumiTailCancelTx(void)
{
    U1                  u1_t_tx;
    U1                  u1_t_tailcnsw_act;                            /* Tailcancel Sw                                               */
    U1                  u1_t_rheosw;

    u1_t_tx       = (U1)ILLUMI_TAIL_CN_UNK;
    u1_t_rheosw   = u1_CALIB_MCUID0430_RHEOSW;

    if(u1_t_rheosw   == (U1)CALIB_MCUID0430_THUMB_WHEEL){
        u1_t_tailcnsw_act = u1_g_IoHwDifltSwitch((U2)IOHW_DISGNL_TAIL_CANCEL_IN);
        if(u1_t_tailcnsw_act != (U1)IOHW_DIFLT_SWITCH_UNKNWN){
            u1_t_tailcnsw_act = u1_g_DioIfChAct((U2)DIO_IF_CH_TAI_CN, (U1)TRUE);
            if(u1_t_tailcnsw_act == (U1)TRUE){
                u1_t_tx = (U1)ILLUMI_TAIL_CN_ACT;
            }
            else{
                u1_t_tx = (U1)ILLUMI_TAIL_CN_INACT;
            }
        }
        else{
            /* Do Nothing */
        }

    }
    else{
        u1_t_tx = (U1)ILLUMI_TAIL_CN_INACT;
    }
    (void)Com_SendSignal(ComConf_ComSignal_TAIL_CN, &u1_t_tx);
    if(u2_s_illumi_tc_nmwk_tout < (U2)U2_MAX){
        u2_s_illumi_tc_nmwk_tout++;
    }

    if(u1_t_tx != u1_s_illumi_tail_cn_tx){
        u2_s_illumi_tc_nmwk_tout = (U2)0U;
        (void)Com_TriggerIPDUSend((PduIdType)MSG_MET1S01_TXCH0);
    }
    u1_s_illumi_tail_cn_tx = u1_t_tx;
}
/*===================================================================================================================================*/
/*  static U1       u1_s_IllumiLoungeHysJdg(const U2 * u2_ap_DIM_LVL)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const U2 * u2_ap_DIM_LVL                                                                                         */
/*  Return:         u1_t_tx                                                                                                          */
/*===================================================================================================================================*/
static U1       u1_s_IllumiLoungeHysJdg(const U2 * u2_ap_DIM_LVL)
{
    U1                  u1_t_tx;
    U1                  u1_t_hys_lower;
    U1                  u1_t_hys_upper;
    U2                  u2_t_daynight;
    U2                  u2_t_lvl;

    u2_t_daynight  = u2_ap_DIM_LVL[ILLUMI_DIM_LVL_DAYNIGHT];
    u2_t_lvl       = u2_ap_DIM_LVL[ILLUMI_DIM_LVL_USADJ_NIGHT];
    u1_t_hys_lower = u1_CALIB_MCUID0336_ILLOF_LV;
    u1_t_hys_upper = u1_CALIB_MCUID0337_ILLOF_CAN_LV;

    if(u2_t_daynight == (U2)DIM_DAYNIGHT_LVL_NIGHT){
        if(u2_t_lvl <= (U2)u1_t_hys_lower){
            u1_t_tx = (U1)ILLUMI_LOUNGE_OFF;
        }
        else if(u2_t_lvl >= (U2)u1_t_hys_upper){
            u1_t_tx = (U1)ILLUMI_LOUNGE_ON;
        }
        else if(u1_s_illumi_lounge_tx >= (U1)ILLUMI_LOUNGE_UNK){
            u1_t_tx = (U1)ILLUMI_LOUNGE_OFF;
        }
        else{
            u1_t_tx = u1_s_illumi_lounge_tx;
        }
    }
    else{
        u1_t_tx = (U1)ILLUMI_LOUNGE_ON;
    }

    vd_g_Rim_WriteU1((U2)RIMID_U1_ILLUMI_LOUNGE, u1_t_tx);

    return(u1_t_tx);
}
/*===================================================================================================================================*/
/*  U1      u1_g_IllumiTcTxNmwk(const U2 u2_a_TOUT)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_IllumiTcTxNmwk(const U2 u2_a_TOUT)
{
    U1                  u1_t_nmwk;                            /* Tailcancel State                                                    */

    if(u2_s_illumi_tc_nmwk_tout < u2_a_TOUT){
        u1_t_nmwk = (U1)TRUE;
    }
    else{
        u1_t_nmwk = (U1)FALSE;
    }

    return(u1_t_nmwk);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    10/11/2018  TN       New.                                                                                               */
/*  1.1.0    12/ 6/2018  TN       Bug Fix : MET1S01 was transmitted even though signal change event was not detected.                */
/*  1.2.0     2/22/2019  TN       ComConf_ComSignal_ILL_OUT and ComConf_ComSignal_RHEO_IN was implemented.                           */
/*  1.3.0    10/ 3/2019  TN       u1_g_IllumiRheoTxNmwk was implemented for NM Diag.                                                 */
/*  1.4.0    03/21/2020  SM       800B Vehicle Settings                                                                              */
/*  1.5.0    04/13/2020  SM       Over Write function was implemented.                                                               */
/*  1.5.1    11/20/2020  KM       Fixed QAC warning.(STCYC)                                                                          */
/*  1.5.2    08/10/2020  XT       Fixed Output RHEOSTAT=100% and ILL_OF=0 if the External Output is not supported                    */
/*  2.0.1    11/16/2021  SA       Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.1.0    02/07/2022  SA       illumi v2.0.1 -> v2.1.0.                                                                           */
/*  2.2.0    01/11/2024  TH       for 19PFv3  Add RHEO_POS,TR2_DUTY,IR2_DUTY  etc                                                    */
/*  2.2.1     9/18/2024  SM       Add u1_g_IllumiTcTxNmwk for NM Diag                                                                */
/*  2.2.2    11/19/2024  TH       Fix : EventTx Timing                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/* 19PFv3-1   1/12/2024  SH       Change reading RHEOSTAT calibration parameter                                                      */
/* 19PFv3-2   2/16/2024  SH       Change MCUCONST v010->v012                                                                         */
/* 19PFv3-3   2/23/2024  SH       Change ILL_OF control                                                                              */
/* 19PFv3-4   4/12/2024  SH       Add calibration guard                                                                              */
/* 19PFv3-5   6/27/2024  TN(DT)   Delete Calibration Guard Process.                                                                  */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * TN     = Takashi Nagai, DENSO                                                                                                  */
/*  * SM     = Shota Maegawa, Denso Techno                                                                                           */
/*  * KM     = Kota Matoba                                                                                                           */
/*  * XT     = Xinyuan Tong, DNST                                                                                                    */
/*  * SA     = Seiya Asaoka                                                                                                          */
/*  * SH     = Sae Hirose, Denso Techno                                                                                              */
/*  * TH     = Taisuke Hirakawa, KSE                                                                                                 */
/*  * TN(DT) = Tetsushi Nakano, Denso Techno                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/
