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
#if 0   /* BEV Rebase provisionally */
#include "rim_ctl.h"
#include "rim_ctl_cfg.h"
#include "iohw_adc.h"
#endif   /* BEV Rebase provisionally */

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


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_DrectxMsg_MET1D50(const U1 * u1_ap_FNC);
static void    vd_s_DrectxMsg_MET1D51(const U1 * u1_ap_FNC);

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
    U1                  u1_t_tx;

    u2_s_drec_tx_evt       = (U2)0U;
    u1_s_drec_tx_mrst_tout = (U1)U1_MAX;
    u1_s_drec_tx_bpe_evt   = (U1)0U;

#if 0   /* BEV Rebase provisionally */
    vd_g_Rim_WriteU2((U2)RIMID_U2_DREC_TX, (U2)0U);
#endif   /* BEV Rebase provisionally */

    u1_t_tx = (U1)0U;
#if 0   /* BEV Rebase provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_DATA_NUM, &u1_t_tx);
    (void)Com_SendSignal(ComConf_ComSignal_MET_REST, &u1_t_tx);
    (void)Com_SendSignal(ComConf_ComSignal_DATA_NM2, &u1_t_tx);
    (void)Com_SendSignal(ComConf_ComSignal_SW_INF,   &u1_t_tx);
#endif   /* BEV Rebase provisionally */

    u1_t_tx = (U1)FALSE;
#if 0   /* BEV Rebase provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_FLWNG_ON, &u1_t_tx);
    (void)Com_SendSignal(ComConf_ComSignal_ACTV_TST, &u1_t_tx);
#endif   /* BEV Rebase provisionally */

    u1_t_tx = (U1)U1_MAX;
#if 0   /* BEV Rebase provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_IG_VOL,   &u1_t_tx);
    (void)Com_SendSignal(ComConf_ComSignal_DISP_TMP, &u1_t_tx);
#endif   /* BEV Rebase provisionally */
}
/*===================================================================================================================================*/
/*  void    vd_g_DrectxRstInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DrectxRstInit(void)
{
    U2                  u2_t_br;
    U1                  u1_t_fnc;
    U1                  u1_t_tx;

    u2_s_drec_tx_evt       = (U2)0U;
    u1_s_drec_tx_mrst_tout = (U1)0U;
    u1_s_drec_tx_bpe_evt   = (U1)0U;

    u2_t_br = (U2)0U;
#if 0   /* BEV Rebase provisionally */
    (void)u1_g_Rim_ReadU2withStatus((U2)RIMID_U2_DREC_TX, &u2_t_br);
#endif   /* BEV Rebase provisionally */

    u1_t_fnc = (U1)(u2_t_br >> DREC_TX_FNC_LSB_MET1D50);
#if 0   /* BEV Rebase provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_DATA_NUM, &u1_t_fnc);
#endif   /* BEV Rebase provisionally */

    u1_t_tx = (U1)TRUE;
#if 0   /* BEV Rebase provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_MET_REST, &u1_t_tx);
#endif   /* BEV Rebase provisionally */

    u1_t_tx = (U1)FALSE;
#if 0   /* BEV Rebase provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_FLWNG_ON, &u1_t_tx);
    (void)Com_SendSignal(ComConf_ComSignal_ACTV_TST, &u1_t_tx);
#endif   /* BEV Rebase provisionally */

    u1_t_fnc = (U1)(u2_t_br >> DREC_TX_FNC_LSB_MET1D51);
#if 0   /* BEV Rebase provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_DATA_NM2, &u1_t_fnc);
#endif   /* BEV Rebase provisionally */

    u1_t_tx = (U1)0U;
#if 0   /* BEV Rebase provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_SW_INF,   &u1_t_tx);
#endif   /* BEV Rebase provisionally */

    u1_t_tx = (U1)U1_MAX;
#if 0   /* BEV Rebase provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_IG_VOL,   &u1_t_tx);
    (void)Com_SendSignal(ComConf_ComSignal_DISP_TMP, &u1_t_tx);
#endif   /* BEV Rebase provisionally */
}
/*===================================================================================================================================*/
/*  void    vd_g_DrecTxWkupInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DrectxWkupInit(void)
{
    U2                  u2_t_br;
    U1                  u1_t_fnc;
    U1                  u1_t_tx;

    u2_s_drec_tx_evt       = (U2)0U;
    u1_s_drec_tx_mrst_tout = (U1)U1_MAX;
    u1_s_drec_tx_bpe_evt   = (U1)0U;

    u2_t_br = (U2)0U;
#if 0   /* BEV Rebase provisionally */
    (void)u1_g_Rim_ReadU2withStatus((U2)RIMID_U2_DREC_TX, &u2_t_br);
#endif   /* BEV Rebase provisionally */

    u1_t_fnc = (U1)(u2_t_br >> DREC_TX_FNC_LSB_MET1D50);
#if 0   /* BEV Rebase provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_DATA_NUM, &u1_t_fnc);
#endif   /* BEV Rebase provisionally */

    u1_t_tx = (U1)FALSE;
#if 0   /* BEV Rebase provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_MET_REST, &u1_t_tx);
    (void)Com_SendSignal(ComConf_ComSignal_FLWNG_ON, &u1_t_tx);
    (void)Com_SendSignal(ComConf_ComSignal_ACTV_TST, &u1_t_tx);
#endif   /* BEV Rebase provisionally */

    u1_t_fnc = (U1)(u2_t_br >> DREC_TX_FNC_LSB_MET1D51);
#if 0   /* BEV Rebase provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_DATA_NM2, &u1_t_fnc);
#endif   /* BEV Rebase provisionally */

    u1_t_tx = (U1)0U;
#if 0   /* BEV Rebase provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_SW_INF,   &u1_t_tx);
#endif   /* BEV Rebase provisionally */

    u1_t_tx = (U1)U1_MAX;
#if 0   /* BEV Rebase provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_IG_VOL,   &u1_t_tx);
    (void)Com_SendSignal(ComConf_ComSignal_DISP_TMP, &u1_t_tx);
#endif   /* BEV Rebase provisionally */
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
#if 0   /* BEV Rebase provisionally */
    (void)u1_g_Rim_ReadU2withStatus((U2)RIMID_U2_DREC_TX, &u2_t_br);
#endif   /* BEV Rebase provisionally */
    u2_t_br = (u2_t_br + u2_s_drec_tx_evt) & (U2)DREC_TX_FNC_BIT_MAX;
#if 0   /* BEV Rebase provisionally */
    vd_g_Rim_WriteU2((U2)RIMID_U2_DREC_TX, u2_t_br);
#endif   /* BEV Rebase provisionally */

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
#if 0   /* BEV Rebase provisionally */
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
#endif   /* BEV Rebase provisionally */
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

#if 0   /* BEV Rebase provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_DATA_NUM, u1_ap_FNC);
    
 /* (void)Com_SendSignal(ComConf_ComSignal_RNW_COND, &u1_t_tx); */ /* written by fuelvol */
 /* (void)Com_SendSignal(ComConf_ComSignal_STOP_JG,  &u1_t_tx); */ /* written by fuelvol */

    u1_t_tx = u1_g_GaugeOwActSts((U1)GAUGE_CH_FUELSEG);
    (void)Com_SendSignal(ComConf_ComSignal_ACTV_TST, &u1_t_tx);
#endif   /* BEV Rebase provisionally */

 /* (void)Com_SendSignal(ComConf_ComSignal_IGON_SIG, &u1_t_tx); */ /* written by fuelvol */
 /* (void)Com_SendSignal(ComConf_ComSignal_STON_SIG, &u1_t_tx); */ /* written by fuelvol */
    if(u1_s_drec_tx_mrst_tout < u1_s_DREC_TX_MRST_MAX){
        u1_t_tx = (U1)TRUE;
    }
    else{
        u1_t_tx = (U1)FALSE;
    }
#if 0   /* BEV Rebase provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_MET_REST, &u1_t_tx);

    u1_t_tx = u1_g_FuelvolTauLwAct();
    (void)Com_SendSignal(ComConf_ComSignal_FLWNG_ON, &u1_t_tx);
#endif   /* BEV Rebase provisionally */

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

#if 0   /* BEV Rebase provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_DATA_NM2, u1_ap_FNC);
#endif   /* BEV Rebase provisionally */

 /* (void)Com_SendSignal(ComConf_ComSignal_D_N_INF,  &u1_t_tx);   */ /* written by dimmer */
 /* (void)Com_SendSignal(ComConf_ComSignal_RHEO_IN,  &u1_t_tx);   */ /* written by illumi */
 /* (void)Com_SendSignal(ComConf_ComSignal_ILL_OUT,  &u1_t_tx);   */ /* written by illumi */

#if 0   /* BEV Rebase provisionally */
    u1_s_drec_tx_bpe_evt |= (U1)0U;
    (void)Com_SendSignal(ComConf_ComSignal_SW_INF,   &u1_s_drec_tx_bpe_evt);
#endif   /* BEV Rebase provisionally */

#if 0   /* BEV Rebase provisionally */
    u4_t_igvol = (U4)u2_g_IoHwAdcLv((U1)ADC_CH_IG_MON);
#else   /* BEV Rebase provisionally */
    u4_t_igvol = (U4)U4_MAX;
#endif   /* BEV Rebase provisionally */
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
#if 0   /* BEV Rebase provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_IG_VOL, &u1_t_tx);
#endif   /* BEV Rebase provisionally */

    u1_t_tx = (U1)U1_MAX;
#if 0   /* BEV Rebase provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_DISP_TMP, &u1_t_tx);
#endif   /* BEV Rebase provisionally */
 /* (void)Com_SendSignal(ComConf_ComSignal_LN_FC,    &u1_t_tx);   */ /* written by tripcom */
 /* (void)Com_SendSignal(ComConf_ComSignal_RF_FC,    &u1_t_tx);   */ /* written by tripcom */
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
/*  BEV-1    10/22/2025 YN        Change for BEV rebase.                                                                             */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * AM   = Atsushi Mizutani, DensoTechno                                                                                           */
/*  * AS   = Ayumi Saito, DensoTechno                                                                                                */
/*  * YN   = Yujiro Nagaya, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
