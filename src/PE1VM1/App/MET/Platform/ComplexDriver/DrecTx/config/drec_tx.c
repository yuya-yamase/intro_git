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
static U1                        u1_s_drec_tx_bpe_evt;


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
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
    u1_s_drec_tx_bpe_evt   = (U1)0U;

#if 0   /* BEV Rebase provisionally */
    vd_g_Rim_WriteU2((U2)RIMID_U2_DREC_TX, (U2)0U);
#endif   /* BEV Rebase provisionally */

    u1_t_tx = (U1)0U;
#if 0   /* BEV Rebase provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_DATA_NM2, &u1_t_tx);
    (void)Com_SendSignal(ComConf_ComSignal_SW_INF,   &u1_t_tx);
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
    u1_s_drec_tx_bpe_evt   = (U1)0U;

    u2_t_br = (U2)0U;
#if 0   /* BEV Rebase provisionally */
    (void)u1_g_Rim_ReadU2withStatus((U2)RIMID_U2_DREC_TX, &u2_t_br);
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
    u1_s_drec_tx_bpe_evt   = (U1)0U;

    u2_t_br = (U2)0U;
#if 0   /* BEV Rebase provisionally */
    (void)u1_g_Rim_ReadU2withStatus((U2)RIMID_U2_DREC_TX, &u2_t_br);
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
    U1                  u1_t_fnc;

    u2_t_br = (U2)0U;
#if 0   /* BEV Rebase provisionally */
    (void)u1_g_Rim_ReadU2withStatus((U2)RIMID_U2_DREC_TX, &u2_t_br);
#endif   /* BEV Rebase provisionally */
    u2_t_br = (u2_t_br + u2_s_drec_tx_evt) & (U2)DREC_TX_FNC_BIT_MAX;
#if 0   /* BEV Rebase provisionally */
    vd_g_Rim_WriteU2((U2)RIMID_U2_DREC_TX, u2_t_br);
#endif   /* BEV Rebase provisionally */

    u2_s_drec_tx_evt = (U2)0U;

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
/*  static void    vd_s_DrectxMsg_MET1D51(const U1 * u1_ap_FNC)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_DrectxMsg_MET1D51(const U1 * u1_ap_FNC)
{
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
/*  BEV-2    10/24/2025 YN        Change for BEV rebase.                                                                             */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * AM   = Atsushi Mizutani, DensoTechno                                                                                           */
/*  * AS   = Ayumi Saito, DensoTechno                                                                                                */
/*  * YN   = Yujiro Nagaya, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
