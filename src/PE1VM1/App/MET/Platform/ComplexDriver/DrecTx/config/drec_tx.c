/* 1.0.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/* Drive Recorder / CAN Communication Tx                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DREC_TX_C_MAJOR                          (1)
#define DREC_TX_C_MINOR                          (0)
#define DREC_TX_C_PATCH                          (2)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "drec_tx.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif
#include "rim_ctl.h"
#if 0   /* BEV BSW provisionally */
#else
#include "rim_ctl_cfg_STUB.h"
#endif
#include "rim_ctl_cfg.h"
#include "dio_if.h"
#include "iohw_adc.h"

#if 0   /* BEV BSW provisionally */
#include "fuelvol_tau.h"
#endif
#include "gauge.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DREC_TX_C_MAJOR != DREC_TX_H_MAJOR) || \
     (DREC_TX_C_MINOR != DREC_TX_H_MINOR) || \
     (DREC_TX_C_PATCH != DREC_TX_H_PATCH))
#error "drec_tx.c and drec_tx.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DREC_TX_NUM_MSG                          (2U)
#define DREC_TX_MSG_MET1D50                      (0U)
#define DREC_TX_MSG_MET1D51                      (1U)

#define DREC_TX_FNC_LSB_MET1D50                  (0U)
#define DREC_TX_FNC_LSB_MET1D51                  (8U)
#define DREC_TX_FNC_BIT_MET1D50                  (0x0001U)
#define DREC_TX_FNC_BIT_MET1D51                  (0x0100U)
#define DREC_TX_FNC_BIT_MAX                      (0x0303U)

#define DREC_TX_BPE_STS_CHK_SW_ACT               (0x01U)
#define DREC_TX_BPE_STS_CHK_LP_EVT               (0x02U)

#define DREC_TX_BPE_NUM_CH                       (10U)
#define DREC_TX_BPE_CH_STE_LEFT                  (0U)
#define DREC_TX_BPE_CH_STE_RIGHT                 (1U)
#define DREC_TX_BPE_CH_STE_UP                    (2U)
#define DREC_TX_BPE_CH_STE_DOWN                  (3U)
#define DREC_TX_BPE_CH_STE_TOP                   (4U)
#define DREC_TX_BPE_CH_STE_BACK                  (5U)
#define DREC_TX_BPE_CH_STE_ENTER                 (6U)
#define DREC_TX_BPE_CH_RHE_UP                    (7U)
#define DREC_TX_BPE_CH_RHE_DOWN                  (8U)
#define DREC_TX_BPE_CH_ODO                       (9U)

#define DREC_TX_BPE_NUM_STS                      (2U)
#define DREC_TX_BPE_STS_REL                      (0U)
#define DREC_TX_BPE_STS_PRE                      (1U)

#define DREC_TX_BPE_ACT_TO_REL                   (0U)
#define DREC_TX_BPE_ACT_TO_REL_EVT               (1U)
#define DREC_TX_BPE_ACT_TO_PRE                   (2U)
#define DREC_TX_BPE_ACT_PRE                      (3U)
#define DREC_TX_BPE_ACT_TO_PRE_EVT               (4U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U1         u1_tm_elpsd;
    U1         u1_sts;
}ST_DREC_TX_BPE_CH;

typedef struct{
    U2         u2_sw_ch;
    U2         u2_lsb;
}ST_DREC_TX_BPE_EVT;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2                        u2_s_drec_tx_evt;
static U1                        u1_s_drec_tx_mrst_tout;
static U1                        u1_s_drec_tx_bpe_evt;

static ST_DREC_TX_BPE_CH         st_sp_drec_tx_bpe_ch[DREC_TX_BPE_NUM_CH];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_DrectxMsg_MET1D50(const U1 * u1_ap_FNC);
static void    vd_s_DrectxMsg_MET1D51(const U1 * u1_ap_FNC);
static U1      u1_s_DrectxSwInfchk(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_DrectxRstInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DrectxBonInit(void)
{
    U4                  u4_t_lpcnt;
    U1                  u1_t_tx;

    u2_s_drec_tx_evt       = (U2)0U;
    u1_s_drec_tx_mrst_tout = (U1)U1_MAX;
    u1_s_drec_tx_bpe_evt   = (U1)0U;

    vd_g_Rim_WriteU2((U2)RIMID_U2_DREC_TX, (U2)0U);

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)DREC_TX_BPE_NUM_CH; u4_t_lpcnt++){
        st_sp_drec_tx_bpe_ch[u4_t_lpcnt].u1_tm_elpsd = (U1)0U;
        st_sp_drec_tx_bpe_ch[u4_t_lpcnt].u1_sts      = (U1)DREC_TX_BPE_STS_REL;
    }

    u1_t_tx = (U1)0U;
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_DATA_NUM, &u1_t_tx);    /* COM Tx STUB delete */
    (void)Com_SendSignal(ComConf_ComSignal_MET_REST, &u1_t_tx);    /* COM Tx STUB delete */
    (void)Com_SendSignal(ComConf_ComSignal_DATA_NM2, &u1_t_tx);    /* COM Tx STUB delete */
    (void)Com_SendSignal(ComConf_ComSignal_SW_INF,   &u1_t_tx);    /* COM Tx STUB delete */
#endif

    u1_t_tx = (U1)FALSE;
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_FLWNG_ON, &u1_t_tx);    /* COM Tx STUB delete */
    (void)Com_SendSignal(ComConf_ComSignal_ACTV_TST, &u1_t_tx);    /* COM Tx STUB delete */
#endif

    u1_t_tx = (U1)U1_MAX;
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_IG_VOL,   &u1_t_tx);    /* COM Tx STUB delete */
    (void)Com_SendSignal(ComConf_ComSignal_DISP_TMP, &u1_t_tx);    /* COM Tx STUB delete */
#endif
}
/*===================================================================================================================================*/
/*  void    vd_g_DrectxRstInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DrectxRstInit(void)
{
    U4                  u4_t_lpcnt;
    U2                  u2_t_br;
    U1                  u1_t_fnc;
    U1                  u1_t_tx;

    u2_s_drec_tx_evt       = (U2)0U;
    u1_s_drec_tx_mrst_tout = (U1)0U;
    u1_s_drec_tx_bpe_evt   = (U1)0U;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)DREC_TX_BPE_NUM_CH; u4_t_lpcnt++){
        st_sp_drec_tx_bpe_ch[u4_t_lpcnt].u1_tm_elpsd = (U1)0U;
        st_sp_drec_tx_bpe_ch[u4_t_lpcnt].u1_sts      = (U1)DREC_TX_BPE_STS_REL;
    }

    u2_t_br = (U2)0U;
    (void)u1_g_Rim_ReadU2withStatus((U2)RIMID_U2_DREC_TX, &u2_t_br);

    u1_t_fnc = (U1)(u2_t_br >> DREC_TX_FNC_LSB_MET1D50);
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_DATA_NUM, &u1_t_fnc);    /* COM Tx STUB delete */
#endif

    u1_t_tx = (U1)TRUE;
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_MET_REST, &u1_t_tx);    /* COM Tx STUB delete */
#endif

    u1_t_tx = (U1)FALSE;
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_FLWNG_ON, &u1_t_tx);    /* COM Tx STUB delete */
    (void)Com_SendSignal(ComConf_ComSignal_ACTV_TST, &u1_t_tx);    /* COM Tx STUB delete */
#endif

    u1_t_fnc = (U1)(u2_t_br >> DREC_TX_FNC_LSB_MET1D51);
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_DATA_NM2, &u1_t_fnc);    /* COM Tx STUB delete */
#endif

    u1_t_tx = (U1)0U;
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_SW_INF,   &u1_t_tx);    /* COM Tx STUB delete */
#endif

    u1_t_tx = (U1)U1_MAX;
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_IG_VOL,   &u1_t_tx);    /* COM Tx STUB delete */
    (void)Com_SendSignal(ComConf_ComSignal_DISP_TMP, &u1_t_tx);    /* COM Tx STUB delete */
#endif
}
/*===================================================================================================================================*/
/*  void    vd_g_DrecTxWkupInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DrectxWkupInit(void)
{
    U4                  u4_t_lpcnt;
    U2                  u2_t_br;
    U1                  u1_t_fnc;
    U1                  u1_t_tx;

    u2_s_drec_tx_evt       = (U2)0U;
    u1_s_drec_tx_mrst_tout = (U1)U1_MAX;
    u1_s_drec_tx_bpe_evt   = (U1)0U;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)DREC_TX_BPE_NUM_CH; u4_t_lpcnt++){
        st_sp_drec_tx_bpe_ch[u4_t_lpcnt].u1_tm_elpsd = (U1)0U;
        st_sp_drec_tx_bpe_ch[u4_t_lpcnt].u1_sts      = (U1)DREC_TX_BPE_STS_REL;
    }

    u2_t_br = (U2)0U;
    (void)u1_g_Rim_ReadU2withStatus((U2)RIMID_U2_DREC_TX, &u2_t_br);

    u1_t_fnc = (U1)(u2_t_br >> DREC_TX_FNC_LSB_MET1D50);
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_DATA_NUM, &u1_t_fnc);    /* COM Tx STUB delete */
#endif

    u1_t_tx = (U1)FALSE;
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_MET_REST, &u1_t_tx);    /* COM Tx STUB delete */
    (void)Com_SendSignal(ComConf_ComSignal_FLWNG_ON, &u1_t_tx);    /* COM Tx STUB delete */
    (void)Com_SendSignal(ComConf_ComSignal_ACTV_TST, &u1_t_tx);    /* COM Tx STUB delete */
#endif

    u1_t_fnc = (U1)(u2_t_br >> DREC_TX_FNC_LSB_MET1D51);
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_DATA_NM2, &u1_t_fnc);    /* COM Tx STUB delete */
#endif

    u1_t_tx = (U1)0U;
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_SW_INF,   &u1_t_tx);    /* COM Tx STUB delete */
#endif

    u1_t_tx = (U1)U1_MAX;
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_IG_VOL,   &u1_t_tx);    /* COM Tx STUB delete */
    (void)Com_SendSignal(ComConf_ComSignal_DISP_TMP, &u1_t_tx);    /* COM Tx STUB delete */
#endif
}
/*===================================================================================================================================*/
/*  void    vd_g_DrectxMainTask(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DrectxMainTask(void)
{
    U2                  u2_t_br;
    U2                  u2_t_tx_evt;
    U1                  u1_t_fnc;

    u2_t_br = (U2)0U;
    (void)u1_g_Rim_ReadU2withStatus((U2)RIMID_U2_DREC_TX, &u2_t_br);
    u2_t_br = (u2_t_br + u2_s_drec_tx_evt) & (U2)DREC_TX_FNC_BIT_MAX;
    vd_g_Rim_WriteU2((U2)RIMID_U2_DREC_TX, u2_t_br);

    u2_t_tx_evt = u2_s_drec_tx_evt & (U2)DREC_TX_FNC_BIT_MET1D50;
    if((u1_s_drec_tx_mrst_tout <  (U1)U1_MAX) &&
       (u2_t_tx_evt            != (U2)0U    )){
        u1_s_drec_tx_mrst_tout++;
    }
    u2_s_drec_tx_evt = (U2)0U;

    u1_t_fnc = (U1)(u2_t_br >> DREC_TX_FNC_LSB_MET1D50);
    vd_s_DrectxMsg_MET1D50(&u1_t_fnc);
    u1_t_fnc = (U1)(u2_t_br >> DREC_TX_FNC_LSB_MET1D51);
    vd_s_DrectxMsg_MET1D51(&u1_t_fnc);
}
/*===================================================================================================================================*/
/*  void    vd_g_DrectxTxAck(const U2 u2_a_MSG)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DrectxTxAck(const U2 u2_a_MSG)
{
    if(u2_a_MSG == (U2)MSG_MET1D50_TXCH0){
        u2_s_drec_tx_evt |= (U2)DREC_TX_FNC_BIT_MET1D50;
    }
    else if(u2_a_MSG == (U2)MSG_MET1D51_TXCH0){
        u2_s_drec_tx_evt |= (U2)DREC_TX_FNC_BIT_MET1D51;
        u1_s_drec_tx_bpe_evt = (U1)0U;
    }
    else{
        /* Do Nothing */
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_DrectxMsg_MET1D50(const U1 * u1_ap_FNC)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_DrectxMsg_MET1D50(const U1 * u1_ap_FNC)
{
    static const U1     u1_s_DREC_TX_MRST_MAX = (U1)7U;

    U1                  u1_t_tx;

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_DATA_NUM, u1_ap_FNC);    /* COM Tx STUB delete */
#endif
    
 /* (void)Com_SendSignal(ComConf_ComSignal_RNW_COND, &u1_t_tx); */ /* written by fuelvol */
 /* (void)Com_SendSignal(ComConf_ComSignal_STOP_JG,  &u1_t_tx); */ /* written by fuelvol */

    u1_t_tx = u1_g_GaugeOwActSts((U1)GAUGE_CH_FUELSEG);
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_ACTV_TST, &u1_t_tx);    /* COM Tx STUB delete */
#endif

 /* (void)Com_SendSignal(ComConf_ComSignal_IGON_SIG, &u1_t_tx); */ /* written by fuelvol */
 /* (void)Com_SendSignal(ComConf_ComSignal_STON_SIG, &u1_t_tx); */ /* written by fuelvol */
    if(u1_s_drec_tx_mrst_tout < u1_s_DREC_TX_MRST_MAX){
        u1_t_tx = (U1)TRUE;
    }
    else{
        u1_t_tx = (U1)FALSE;
    }
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_MET_REST, &u1_t_tx);    /* COM Tx STUB delete */
#endif

#if 0   /* BEV BSW provisionally */
    u1_t_tx = u1_g_FuelvolTauLwAct();
#else
    u1_t_tx = (U1)FALSE;
#endif
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_FLWNG_ON, &u1_t_tx);    /* COM Tx STUB delete */
#endif

 /* (void)Com_SendSignal(ComConf_ComSignal_FL_DISP,  &u1_t_tx); */ /* written by fuelvol */
 /* (void)Com_SendSignal(ComConf_ComSignal_FL_COMP,  &u1_t_tx); */ /* written by fuelvol */
 /* (void)Com_SendSignal(ComConf_ComSignal_FL_IS,    &u1_t_tx); */ /* written by fuelvol */
 /* (void)Com_SendSignal(ComConf_ComSignal_FL_AS,    &u1_t_tx); */ /* written by fuelvol */
 /* (void)Com_SendSignal(ComConf_ComSignal_FL_DS,    &u1_t_tx); */ /* written by fuelvol */
 /* (void)Com_SendSignal(ComConf_ComSignal_SBFL_DS,  &u1_t_tx); */ /* written by fuelvol */
}
/*===================================================================================================================================*/
/*  static void    vd_s_DrectxMsg_MET1D51(const U1 * u1_ap_FNC)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_DrectxMsg_MET1D51(const U1 * u1_ap_FNC)
{
    static const U2     u2_s_DREC_TX_IG_MAX = (U2)1023U;
    static const U2     u2_s_DREC_TX_IG_MUL = (U2)4010U;
    static const U2     u2_s_DREC_TX_IG_OFS = (U2)10240U;
    static const U2     u2_s_DREC_TX_IG_DIV = (U2)20480U;

    U4                  u4_t_igvol;
    U1                  u1_t_tx;

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_DATA_NM2, u1_ap_FNC);    /* COM Tx STUB delete */
#endif

 /* (void)Com_SendSignal(ComConf_ComSignal_D_N_INF,  &u1_t_tx);   */ /* written by dimmer */
 /* (void)Com_SendSignal(ComConf_ComSignal_RHEO_IN,  &u1_t_tx);   */ /* written by illumi */
 /* (void)Com_SendSignal(ComConf_ComSignal_ILL_OUT,  &u1_t_tx);   */ /* written by illumi */

    u1_s_drec_tx_bpe_evt |= u1_s_DrectxSwInfchk();
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_SW_INF,   &u1_s_drec_tx_bpe_evt);    /* COM Tx STUB delete */
#endif

    u4_t_igvol = (U4)u2_g_IoHwAdcLv((U1)ADC_CH_IG_MON);
    if(u4_t_igvol > (U4)u2_s_DREC_TX_IG_MAX){
        u1_t_tx = (U1)U1_MAX;
    }
    else{
        u4_t_igvol = (u4_t_igvol * (U4)u2_s_DREC_TX_IG_MUL) + (U4)u2_s_DREC_TX_IG_OFS; /* PRQA S 3383 */
        /* The maximum value of u4_t_igvol is 1023.                                        */
        /* The value of u2_s_DREC_TX_IG_MUL is 4010.                                       */
        /* The value of u2_s_DREC_TX_IG_OFS is 10240.                                      */
        /* So calculations is always less than U4_MAX. (4112470)                           */
        /* It is not necessary to check the wraparound.                                    */
        u4_t_igvol =  u4_t_igvol / (U4)u2_s_DREC_TX_IG_DIV;
        u1_t_tx    = (U1)u4_t_igvol;
    }
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_IG_VOL, &u1_t_tx);    /* COM Tx STUB delete */
#endif

    u1_t_tx = (U1)U1_MAX;
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_DISP_TMP, &u1_t_tx);    /* COM Tx STUB delete */
#endif
 /* (void)Com_SendSignal(ComConf_ComSignal_LN_FC,    &u1_t_tx);   */ /* written by tripcom */
 /* (void)Com_SendSignal(ComConf_ComSignal_RF_FC,    &u1_t_tx);   */ /* written by tripcom */
}
/*===================================================================================================================================*/
/*  static U1      u1_s_DrectxSwInfchk(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_DrectxSwInfchk(void)
{
    static const U1         u1_s_DREC_TX_BPE_TIM_LP_EVT = (U1)16U; /* 800 milliseconds / 50 milliseconds */

    static const U1         u1_sp_DREC_TX_BPE_STM[] = {
        (U1)DREC_TX_BPE_ACT_TO_REL, (U1)DREC_TX_BPE_ACT_TO_REL_EVT,
        (U1)DREC_TX_BPE_ACT_TO_PRE, (U1)DREC_TX_BPE_ACT_PRE,
        (U1)DREC_TX_BPE_ACT_TO_REL, (U1)DREC_TX_BPE_ACT_TO_REL,
        (U1)DREC_TX_BPE_ACT_TO_PRE, (U1)DREC_TX_BPE_ACT_TO_PRE_EVT,
    };

    static const ST_DREC_TX_BPE_EVT  st_sp_DREC_TX_BPE_EVT[] = {
        {(U2)DIO_IF_CH_STE_LE,  (U2)0U},    /* DREC_TX_BPE_CH_STE_LEFT    (0U) */
        {(U2)DIO_IF_CH_STE_RI,  (U2)0U},    /* DREC_TX_BPE_CH_STE_RIGHT   (1U) */
        {(U2)DIO_IF_CH_STE_UP,  (U2)0U},    /* DREC_TX_BPE_CH_STE_UP      (2U) */
        {(U2)DIO_IF_CH_STE_DW,  (U2)0U},    /* DREC_TX_BPE_CH_STE_DOWN    (3U) */
        {(U2)U2_MAX,            (U2)2U},    /* DREC_TX_BPE_CH_STE_TOP     (4U) */
        {(U2)DIO_IF_CH_STE_BA,  (U2)2U},    /* DREC_TX_BPE_CH_STE_BACK    (5U) */
        {(U2)DIO_IF_CH_STE_EN,  (U2)2U},    /* DREC_TX_BPE_CH_STE_ENTER   (6U) */
        {(U2)DIO_IF_CH_DIM_UP,  (U2)4U},    /* DREC_TX_BPE_CH_RHE_UP      (7U) */
        {(U2)DIO_IF_CH_DIM_DW,  (U2)4U},    /* DREC_TX_BPE_CH_RHE_DOWN    (8U) */
        {(U2)DIO_IF_CH_OT_SEL,  (U2)6U}     /* DREC_TX_BPE_CH_ODO         (9U) */
    };

    static const U1         u1_sp_DREC_TX_BPE_EVT[] = {
        (U1)0x00U,                          /* DREC_TX_BPE_ACT_TO_REL     (0U) */
        (U1)0x01U,                          /* DREC_TX_BPE_ACT_TO_REL_EVT (1U) */
        (U1)0x00U,                          /* DREC_TX_BPE_ACT_TO_PRE     (2U) */
        (U1)0x00U,                          /* DREC_TX_BPE_ACT_PRE        (3U) */
        (U1)0x02U                           /* DREC_TX_BPE_ACT_TO_PRE_EVT (4U) */
    };

    static const U1         u1_sp_DREC_TX_BPE_NEXT[] = {
        (U1)0x00U,                          /* DREC_TX_BPE_ACT_TO_REL     (0U) */
        (U1)0x00U,                          /* DREC_TX_BPE_ACT_TO_REL_EVT (1U) */
        (U1)0x11U,                          /* DREC_TX_BPE_ACT_TO_PRE     (2U) */
        (U1)0x01U,                          /* DREC_TX_BPE_ACT_PRE        (3U) */
        (U1)0x01U                           /* DREC_TX_BPE_ACT_TO_PRE_EVT (4U) */
    };

    U4                      u4_t_lpcnt;
    U1                      u1_t_sw_act;
    U1                      u1_t_sts_chk;
    U1                      u1_t_act;
    U1                      u1_t_evt;

    u1_t_evt = (U1)0U;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)DREC_TX_BPE_NUM_CH; u4_t_lpcnt++){

        u1_t_sw_act = u1_g_DioIfChAct(st_sp_DREC_TX_BPE_EVT[u4_t_lpcnt].u2_sw_ch, (U1)TRUE);
        if(u1_t_sw_act == (U1)TRUE){
            u1_t_sts_chk = (U1)DREC_TX_BPE_STS_CHK_SW_ACT;
        }
        else{
            u1_t_sts_chk = (U1)0U;
        }

        if(st_sp_drec_tx_bpe_ch[u4_t_lpcnt].u1_tm_elpsd < (U1)U1_MAX){
            st_sp_drec_tx_bpe_ch[u4_t_lpcnt].u1_tm_elpsd++;
        }

        if(st_sp_drec_tx_bpe_ch[u4_t_lpcnt].u1_tm_elpsd >= u1_s_DREC_TX_BPE_TIM_LP_EVT){
            u1_t_sts_chk |= (U1)DREC_TX_BPE_STS_CHK_LP_EVT;
        }

        if(st_sp_drec_tx_bpe_ch[u4_t_lpcnt].u1_sts < (U1)DREC_TX_BPE_NUM_STS){
            u1_t_act = (u1_t_sts_chk * (U1)DREC_TX_BPE_NUM_STS) + st_sp_drec_tx_bpe_ch[u4_t_lpcnt].u1_sts;
            u1_t_act = u1_sp_DREC_TX_BPE_STM[u1_t_act];
        }
        else{
            u1_t_act = (U1)DREC_TX_BPE_ACT_TO_REL;
        }
        u1_t_evt |= (U1)(u1_sp_DREC_TX_BPE_EVT[u1_t_act] << st_sp_DREC_TX_BPE_EVT[u4_t_lpcnt].u2_lsb);

        u1_t_act  = u1_sp_DREC_TX_BPE_NEXT[u1_t_act];
        st_sp_drec_tx_bpe_ch[u4_t_lpcnt].u1_sts = u1_t_act & (U1)0x01U;
        u1_t_act &= (U1)0x10U;
        if(u1_t_act != (U1)0U){
            st_sp_drec_tx_bpe_ch[u4_t_lpcnt].u1_tm_elpsd = (U1)0U;
        }
    }

    return(u1_t_evt);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    12/20/2018  TN       New.                                                                                               */
/*  1.0.1    07/22/2020  YA       Sw information acquisition changed from SwPxy to DioIf                                             */
/*  1.0.2    10/18/2021  AS       Response to QAC.                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * AM   = Atsushi Mizutani, DensoTechno                                                                                           */
/*  * AS   = Ayumi Saito, DensoTechno                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
