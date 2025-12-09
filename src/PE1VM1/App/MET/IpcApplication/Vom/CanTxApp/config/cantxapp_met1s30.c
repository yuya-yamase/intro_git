/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Can Tx Application                                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CANTXAPP_MET1S30_C_MAJOR                     (0)
#define CANTXAPP_MET1S30_C_MINOR                     (0)
#define CANTXAPP_MET1S30_C_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "cantxapp_cfg_signal.h"
#include "cantxapp_mettx.h"

#include "oxcan.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((CANTXAPP_MET1S30_C_MAJOR != CANTXAPP_CFG_SIGNAL_H_MAJOR) || \
     (CANTXAPP_MET1S30_C_MINOR != CANTXAPP_CFG_SIGNAL_H_MINOR) || \
     (CANTXAPP_MET1S30_C_PATCH != CANTXAPP_CFG_SIGNAL_H_PATCH))
#error "cantxapp_met1s30.c and cantxapp_cfg_signal.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CANTXAPP_PBDMSW_OFF      (0U)
#define CANTXAPP_PBDMSW_ON       (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_CANTXAPP_MET_READ_BIT(u4_buf , u1_pos , u1_len) ((U1)((U1)((u4_buf)  >> (u1_pos)) & (U1)((1U << (u1_len)) - 1U)))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4    u4_sp_cantxapp_met1s30data[CANTXAPP_NBYTE_PAYLOAD8];
static U2    u2_s_cantxapp_pbdmsw_cnt;
static U1    u1_s_cantxapp_pbdmsw_req;
static U1    u1_s_cantxapp_pbdmsw_pre;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_CanTxAppSend_TITE_BB(void);
static void    vd_s_CanTxAppSend_ASD_CANC(void);
static void    vd_s_CanTxAppSend_ASD_CONT(void);
static void    vd_s_CanTxAppSend_RSRCANSW(void);
static void    vd_s_CanTxAppSend_PWLSW(void);
static void    vd_s_CanTxAppSend_MLR_BB(void);
static void    vd_s_CanTxAppSend_DPMS_BB(void);
static void    vd_s_CanTxAppSend_LSW_BB(void);
static void    vd_s_CanTxAppSend_WSVS_BB(void);
static void    vd_s_CanTxAppSend_M_BB(void);
static void    vd_s_CanTxAppSend_VRESTPSW(void);
static void    vd_s_CanTxAppSend_MRT_BB(void);
static void    vd_s_CanTxAppSend_RLM_BB(void);
static void    vd_s_CanTxAppSend_FOG_BB(void);
static void    vd_s_CanTxAppSend_RFG_BB(void);
static void    vd_s_CanTxAppSend_ART_BB(void);
static void    vd_s_CanTxAppSend_PBD_BB(void);
static void    vd_s_CanTxAppSend_POS_REG(void);
static void    vd_s_CanTxAppSend_POS_CALL(void);
static void    vd_s_CanTxAppSend_MW_BB(void);
static void    vd_s_CanTxAppSend_PBDMSW(void);
static void    vd_s_CanTxAppSend_WDI_BB(void);
static void    vd_s_CanTxAppSend_MOSS(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_CanTxAppMET1S30_Init(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_CanTxAppMET1S30_Init(void)
{
    U4                 u4_t_loop;

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)CANTXAPP_NBYTE_PAYLOAD8; u4_t_loop++){
        u4_sp_cantxapp_met1s30data[u4_t_loop] = (U4)0U;
    }

    u2_s_cantxapp_pbdmsw_cnt = (U2)U2_MAX;
    u1_s_cantxapp_pbdmsw_req = (U1)CANTXAPP_PBDMSW_OFF;
    u1_s_cantxapp_pbdmsw_pre = (U1)CANTXAPP_PBDMSW_OFF;
}
/*===================================================================================================================================*/
/*  void    vd_g_CanTxAppMET1S30_Send(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_CanTxAppMET1S30_Send(void)
{
    vd_s_CanTxAppSend_TITE_BB();
    vd_s_CanTxAppSend_ASD_CANC();
    vd_s_CanTxAppSend_ASD_CONT();
    vd_s_CanTxAppSend_RSRCANSW();
    vd_s_CanTxAppSend_PWLSW();
    vd_s_CanTxAppSend_MLR_BB();
    vd_s_CanTxAppSend_DPMS_BB();
    vd_s_CanTxAppSend_LSW_BB();
    vd_s_CanTxAppSend_WSVS_BB();
    vd_s_CanTxAppSend_M_BB();
    vd_s_CanTxAppSend_VRESTPSW();
    vd_s_CanTxAppSend_MRT_BB();
    vd_s_CanTxAppSend_RLM_BB();
    vd_s_CanTxAppSend_FOG_BB();
    vd_s_CanTxAppSend_RFG_BB();
    vd_s_CanTxAppSend_ART_BB();
    vd_s_CanTxAppSend_PBD_BB();
    vd_s_CanTxAppSend_POS_REG();
    vd_s_CanTxAppSend_POS_CALL();
    vd_s_CanTxAppSend_MW_BB();
    vd_s_CanTxAppSend_PBDMSW();
    vd_s_CanTxAppSend_WDI_BB();
    vd_s_CanTxAppSend_MOSS();
}
/*===================================================================================================================================*/
/*  void    vd_g_CanTxAppMET1S30_Put(const U4 * u4_ap_pck_rx, const U1 u1_a_BUFSIZE)                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u4_ap_pck_rx: xspi buffer                                                                                        */
/*                  u1_a_BUFSIZE: buffer size                                                                                        */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_CanTxAppMET1S30_Put(const U4 * u4_ap_pck_rx, const U1 u1_a_BUFSIZE)
{
    U4                 u4_t_loop;

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)u1_a_BUFSIZE; u4_t_loop++){
        if(u1_a_BUFSIZE <= (U1)CANTXAPP_NBYTE_PAYLOAD8){
            u4_sp_cantxapp_met1s30data[u4_t_loop] = u4_ap_pck_rx[u4_t_loop];
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_CanTxAppReqTx_PBDMSW(const U1 u1_a_OPT)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: PBDMSW signal value                                                                                    */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_CanTxAppReqTx_PBDMSW(const U1 u1_a_OPT)
{
    u1_s_cantxapp_pbdmsw_req = u1_a_OPT;
}
/*===================================================================================================================================*/
/*  static void    vd_s_CanTxAppSend_TITE_BB(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CanTxAppSend_TITE_BB(void)
{
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    u1_t_tx = u1_CANTXAPP_MET_READ_BIT(u4_sp_cantxapp_met1s30data[0], (U1)CANTXAPP_POS_1_2, (U1)CANTXAPP_LEN_4);
    u1_t_pre_tx = (U1)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_TITE_BB, &u1_t_pre_tx);
    (void)Com_SendSignal(ComConf_ComSignal_TITE_BB, &u1_t_tx);

    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_CanTxAppSend_ASD_CANC(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CanTxAppSend_ASD_CANC(void)
{
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    u1_t_tx = u1_CANTXAPP_MET_READ_BIT(u4_sp_cantxapp_met1s30data[0], (U1)CANTXAPP_POS_1_1, (U1)CANTXAPP_LEN_1);
    u1_t_pre_tx = (U1)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_ASD_CANC, &u1_t_pre_tx);
    (void)Com_SendSignal(ComConf_ComSignal_ASD_CANC, &u1_t_tx);

    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_CanTxAppSend_ASD_CONT(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CanTxAppSend_ASD_CONT(void)
{
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    u1_t_tx = u1_CANTXAPP_MET_READ_BIT(u4_sp_cantxapp_met1s30data[0], (U1)CANTXAPP_POS_1_0, (U1)CANTXAPP_LEN_1);
    u1_t_pre_tx = (U1)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_ASD_CONT, &u1_t_pre_tx);
    (void)Com_SendSignal(ComConf_ComSignal_ASD_CONT, &u1_t_tx);

    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_CanTxAppSend_RSRCANSW(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CanTxAppSend_RSRCANSW(void)
{
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    u1_t_tx = u1_CANTXAPP_MET_READ_BIT(u4_sp_cantxapp_met1s30data[0], (U1)CANTXAPP_POS_2_5, (U1)CANTXAPP_LEN_1);
    u1_t_pre_tx = (U1)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_RSRCANSW, &u1_t_pre_tx);
    (void)Com_SendSignal(ComConf_ComSignal_RSRCANSW, &u1_t_tx);

    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_CanTxAppSend_PWLSW(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CanTxAppSend_PWLSW(void)
{
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    u1_t_tx = u1_CANTXAPP_MET_READ_BIT(u4_sp_cantxapp_met1s30data[0], (U1)CANTXAPP_POS_2_3, (U1)CANTXAPP_LEN_1);
    u1_t_pre_tx = (U1)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_PWLSW, &u1_t_pre_tx);
    (void)Com_SendSignal(ComConf_ComSignal_PWLSW, &u1_t_tx);

    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_CanTxAppSend_MLR_BB(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CanTxAppSend_MLR_BB(void)
{
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    u1_t_tx = u1_CANTXAPP_MET_READ_BIT(u4_sp_cantxapp_met1s30data[0], (U1)CANTXAPP_POS_2_1, (U1)CANTXAPP_LEN_2);
    u1_t_pre_tx = (U1)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_MLR_BB, &u1_t_pre_tx);
    (void)Com_SendSignal(ComConf_ComSignal_MLR_BB, &u1_t_tx);

    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_CanTxAppSend_DPMS_BB(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CanTxAppSend_DPMS_BB(void)
{
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    u1_t_tx = u1_CANTXAPP_MET_READ_BIT(u4_sp_cantxapp_met1s30data[0], (U1)CANTXAPP_POS_2_0, (U1)CANTXAPP_LEN_1);
    u1_t_pre_tx = (U1)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_DPMS_BB, &u1_t_pre_tx);
    (void)Com_SendSignal(ComConf_ComSignal_DPMS_BB, &u1_t_tx);

    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_CanTxAppSend_LSW_BB(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CanTxAppSend_LSW_BB(void)
{
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    u1_t_tx = u1_CANTXAPP_MET_READ_BIT(u4_sp_cantxapp_met1s30data[0], (U1)CANTXAPP_POS_3_5, (U1)CANTXAPP_LEN_3);
    u1_t_pre_tx = (U1)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_LSW_BB, &u1_t_pre_tx);
    (void)Com_SendSignal(ComConf_ComSignal_LSW_BB, &u1_t_tx);

    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_CanTxAppSend_WSVS_BB(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CanTxAppSend_WSVS_BB(void)
{
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    u1_t_tx = u1_CANTXAPP_MET_READ_BIT(u4_sp_cantxapp_met1s30data[0], (U1)CANTXAPP_POS_3_4, (U1)CANTXAPP_LEN_1);
    u1_t_pre_tx = (U1)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_WSVS_BB, &u1_t_pre_tx);
    (void)Com_SendSignal(ComConf_ComSignal_WSVS_BB, &u1_t_tx);

    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_CanTxAppSend_M_BB(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CanTxAppSend_M_BB(void)
{
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    u1_t_tx = u1_CANTXAPP_MET_READ_BIT(u4_sp_cantxapp_met1s30data[0], (U1)CANTXAPP_POS_3_1, (U1)CANTXAPP_LEN_3);
    u1_t_pre_tx = (U1)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_M_BB, &u1_t_pre_tx);
    (void)Com_SendSignal(ComConf_ComSignal_M_BB, &u1_t_tx);

    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_CanTxAppSend_VRESTPSW(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CanTxAppSend_VRESTPSW(void)
{
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    u1_t_tx = u1_CANTXAPP_MET_READ_BIT(u4_sp_cantxapp_met1s30data[0], (U1)CANTXAPP_POS_4_7, (U1)CANTXAPP_LEN_1);
    u1_t_pre_tx = (U1)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_VRESTPSW, &u1_t_pre_tx);
    (void)Com_SendSignal(ComConf_ComSignal_VRESTPSW, &u1_t_tx);

    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_CanTxAppSend_MRT_BB(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CanTxAppSend_MRT_BB(void)
{
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    u1_t_tx = u1_CANTXAPP_MET_READ_BIT(u4_sp_cantxapp_met1s30data[0], (U1)CANTXAPP_POS_4_5, (U1)CANTXAPP_LEN_2);
    u1_t_pre_tx = (U1)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_MRT_BB, &u1_t_pre_tx);
    (void)Com_SendSignal(ComConf_ComSignal_MRT_BB, &u1_t_tx);

    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_CanTxAppSend_RLM_BB(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CanTxAppSend_RLM_BB(void)
{
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    u1_t_tx = u1_CANTXAPP_MET_READ_BIT(u4_sp_cantxapp_met1s30data[0], (U1)CANTXAPP_POS_4_3, (U1)CANTXAPP_LEN_2);
    u1_t_pre_tx = (U1)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_RLM_BB, &u1_t_pre_tx);
    (void)Com_SendSignal(ComConf_ComSignal_RLM_BB, &u1_t_tx);

    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_CanTxAppSend_FOG_BB(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CanTxAppSend_FOG_BB(void)
{
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    u1_t_tx = u1_CANTXAPP_MET_READ_BIT(u4_sp_cantxapp_met1s30data[0], (U1)CANTXAPP_POS_4_1, (U1)CANTXAPP_LEN_2);
    u1_t_pre_tx = (U1)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_FOG_BB, &u1_t_pre_tx);
    (void)Com_SendSignal(ComConf_ComSignal_FOG_BB, &u1_t_tx);

    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_CanTxAppSend_RFG_BB(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CanTxAppSend_RFG_BB(void)
{
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    u1_t_tx = u1_CANTXAPP_MET_READ_BIT(u4_sp_cantxapp_met1s30data[1], (U1)CANTXAPP_POS_5_5, (U1)CANTXAPP_LEN_2);
    u1_t_pre_tx = (U1)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_RFG_BB, &u1_t_pre_tx);
    (void)Com_SendSignal(ComConf_ComSignal_RFG_BB, &u1_t_tx);

    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_CanTxAppSend_ART_BB(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CanTxAppSend_ART_BB(void)
{
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    u1_t_tx = u1_CANTXAPP_MET_READ_BIT(u4_sp_cantxapp_met1s30data[1], (U1)CANTXAPP_POS_5_3, (U1)CANTXAPP_LEN_2);
    u1_t_pre_tx = (U1)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_ART_BB, &u1_t_pre_tx);
    (void)Com_SendSignal(ComConf_ComSignal_ART_BB, &u1_t_tx);

    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_CanTxAppSend_PBD_BB(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CanTxAppSend_PBD_BB(void)
{
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    u1_t_tx = u1_CANTXAPP_MET_READ_BIT(u4_sp_cantxapp_met1s30data[1], (U1)CANTXAPP_POS_5_0, (U1)CANTXAPP_LEN_3);
    u1_t_pre_tx = (U1)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_PBD_BB, &u1_t_pre_tx);
    (void)Com_SendSignal(ComConf_ComSignal_PBD_BB, &u1_t_tx);

    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_CanTxAppSend_POS_REG(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CanTxAppSend_POS_REG(void)
{
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    u1_t_tx = u1_CANTXAPP_MET_READ_BIT(u4_sp_cantxapp_met1s30data[1], (U1)CANTXAPP_POS_6_6, (U1)CANTXAPP_LEN_2);
    u1_t_pre_tx = (U1)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_POS_REG, &u1_t_pre_tx);
    (void)Com_SendSignal(ComConf_ComSignal_POS_REG, &u1_t_tx);

    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_CanTxAppSend_POS_CALL(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CanTxAppSend_POS_CALL(void)
{
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    u1_t_tx = u1_CANTXAPP_MET_READ_BIT(u4_sp_cantxapp_met1s30data[1], (U1)CANTXAPP_POS_6_2, (U1)CANTXAPP_LEN_2);
    u1_t_pre_tx = (U1)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_POS_CALL, &u1_t_pre_tx);
    (void)Com_SendSignal(ComConf_ComSignal_POS_CALL, &u1_t_tx);

    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_CanTxAppSend_MW_BB(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CanTxAppSend_MW_BB(void)
{
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    u1_t_tx = u1_CANTXAPP_MET_READ_BIT(u4_sp_cantxapp_met1s30data[1], (U1)CANTXAPP_POS_6_0, (U1)CANTXAPP_LEN_2);
    u1_t_pre_tx = (U1)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_MW_BB, &u1_t_pre_tx);
    (void)Com_SendSignal(ComConf_ComSignal_MW_BB, &u1_t_tx);

    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_CanTxAppSend_PBDMSW(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CanTxAppSend_PBDMSW(void)
{
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u2_s_cantxapp_pbdmsw_cnt < (U2)U2_MAX){
        u2_s_cantxapp_pbdmsw_cnt++;
    }

    if(u2_s_cantxapp_pbdmsw_cnt >= (U2)CANTXAPP_HOLD_TIME){
        if((u1_s_cantxapp_pbdmsw_pre != u1_s_cantxapp_pbdmsw_req) &&
           (u1_s_cantxapp_pbdmsw_req == (U1)CANTXAPP_PBDMSW_ON  )){
            u2_s_cantxapp_pbdmsw_cnt = (U2)0U;
        }
        u1_t_tx = u1_s_cantxapp_pbdmsw_req;
        u1_s_cantxapp_pbdmsw_pre = u1_t_tx;
    }
    else{
        u1_t_tx = u1_s_cantxapp_pbdmsw_pre;
    }

    u1_t_pre_tx = (U1)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_PBDMSW, &u1_t_pre_tx);
    (void)Com_SendSignal(ComConf_ComSignal_PBDMSW, &u1_t_tx);

    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_CanTxAppSend_WDI_BB(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CanTxAppSend_WDI_BB(void)
{
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    u1_t_tx = u1_CANTXAPP_MET_READ_BIT(u4_sp_cantxapp_met1s30data[1], (U1)CANTXAPP_POS_7_0, (U1)CANTXAPP_LEN_2);
    u1_t_pre_tx = (U1)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_WDI_BB, &u1_t_pre_tx);
    (void)Com_SendSignal(ComConf_ComSignal_WDI_BB, &u1_t_tx);

    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_CanTxAppSend_MOSS(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CanTxAppSend_MOSS(void)
{
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    u1_t_tx = u1_CANTXAPP_MET_READ_BIT(u4_sp_cantxapp_met1s30data[1], (U1)CANTXAPP_POS_8_0, (U1)CANTXAPP_LEN_2);
    u1_t_pre_tx = (U1)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_MOSS, &u1_t_pre_tx);
    (void)Com_SendSignal(ComConf_ComSignal_MOSS, &u1_t_tx);

    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
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
/*  0.0.0    11/13/2025  YN       New.                                                                                               */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  BEV-1    12/08/2025  YN       Changed function of PBDMSW transmission process.                                                   */
/*                                                                                                                                   */
/*  * YN   = Yujiro Nagaya, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
