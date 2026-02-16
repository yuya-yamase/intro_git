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
#include "rim_ctl.h"
#include "rim_ctl_cfg.h"
#include "ivdsh.h"
#include "illumi_comtx.h"
#include "dimmer.h"
#include "iohw_adc_sh.h"

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
#define DREC_TX_FNC_BIT_MAX                      (0x3U)
#define DREC_TX_MAIN_TICK                        (50U)
#define DREC_TX_CYC_TIME                         ((U1)1200U / (U1)DREC_TX_MAIN_TICK)
#define DREC_TX_CYC_INIT                         (1U)
#define DREC_TX_CNT_SIG                          (1U)

#define DREC_TX_SHIFT_DATA_NM2                   (6U)
#define DREC_TX_SHIFT_RHEO_IN                    (8U)
#define DREC_TX_SHIFT_ILL_OUT                    (16U)
#define DREC_TX_SHIFT_SW_INF                     (24U)
#define DREC_TX_SHIFT_DISP_TMP                   (8U)
#define DREC_TX_SHIFT_LN_FC                      (16U)
#define DREC_TX_SHIFT_RF_FC                      (24U)

#define DREC_TX_VM_2WORD                         (2U)
#define DREC_TX_BUF0                             (0U)
#define DREC_TX_BUF1                             (1U)

#define DREC_TX_SIG_MASK_2BIT                    (0x3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1                        u1_s_drec_com_cnt;
static U1                        u1_s_drec_tx_datanm2;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_DrectxMsg_MET1D51(void);

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
    U4                  u4_t_loop;
    U4                  u4_tp_tx_data[DREC_TX_VM_2WORD];
    U1                  u1_t_tx;

    u1_s_drec_com_cnt     = (U1)0U;
    u1_s_drec_tx_datanm2  = (U1)0U;

    vd_g_Rim_WriteU1((U2)RIMID_U1_DREC_TX, u1_s_drec_tx_datanm2);

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)DREC_TX_VM_2WORD; u4_t_loop++){
        u4_tp_tx_data[u4_t_loop] = (U4)0U;
    }

 /* u1_t_tx = (U1)0U; */
 /* u4_tp_tx_data[DREC_TX_BUF0] |= (U4)u1_t_tx << DREC_TX_SHIFT_DATA_NM2; */    /* DATA_NM2 is 0 transmission */

 /* u1_t_tx = (U1)0U; */
 /* u4_tp_tx_data[DREC_TX_BUF0] |= (U4)u1_t_tx; */                              /* D_N_INF is 0 transmission  */

    u1_t_tx = (U1)U1_MAX;
    u4_tp_tx_data[DREC_TX_BUF0] |= (U4)u1_t_tx << DREC_TX_SHIFT_RHEO_IN;        /* RHEO_IN  */

    u1_t_tx = (U1)U1_MAX;
    u4_tp_tx_data[DREC_TX_BUF0] |= (U4)u1_t_tx << DREC_TX_SHIFT_ILL_OUT;        /* ILL_OUT  */

 /* u1_t_tx = (U1)0U; */
 /* u4_tp_tx_data[DREC_TX_BUF0] |= (U4)u1_t_tx << DREC_TX_SHIFT_SW_INF; */      /* SW_INF is 0 transmission   */

    u1_t_tx = (U1)U1_MAX;
    u4_tp_tx_data[DREC_TX_BUF1] |= (U4)u1_t_tx;                                 /* IG_VOL   */

    u1_t_tx = (U1)U1_MAX;
    u4_tp_tx_data[DREC_TX_BUF1] |= (U4)u1_t_tx << DREC_TX_SHIFT_DISP_TMP;       /* DISP_TMP */

 /* u1_t_tx = (U1)0U; */
 /* u4_tp_tx_data[DREC_TX_BUF1] |= (U4)u1_t_tx << DREC_TX_SHIFT_LN_FC; */       /* LN_FC is 0 transmission    */

 /* u1_t_tx = (U1)0U; */
 /* u4_tp_tx_data[DREC_TX_BUF1] |= (U4)u1_t_tx << DREC_TX_SHIFT_RF_FC; */       /* RF_FC is 0 transmission    */

    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM1TO2_MET1D51, &u4_tp_tx_data[0], (U2)DREC_TX_VM_2WORD);
}
/*===================================================================================================================================*/
/*  void    vd_g_DrectxRstInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DrectxRstInit(void)
{
    U4                  u4_t_loop;
    U4                  u4_tp_tx_data[DREC_TX_VM_2WORD];
    U1                  u1_t_br;
    U1                  u1_t_rimsts;
    U1                  u1_t_tx;

    u1_s_drec_com_cnt     = (U1)0U;
    u1_s_drec_tx_datanm2  = (U1)0U;

    u1_t_br = (U1)0U;
    u1_t_rimsts = u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_DREC_TX, &u1_t_br);

    if((u1_t_rimsts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        u1_s_drec_tx_datanm2 = (u1_t_br & (U1)DREC_TX_SIG_MASK_2BIT);
    }
    else{
        vd_g_Rim_WriteU1((U2)RIMID_U1_DREC_TX, u1_s_drec_tx_datanm2);
    }

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)DREC_TX_VM_2WORD; u4_t_loop++){
        u4_tp_tx_data[u4_t_loop] = (U4)0U;
    }

    u4_tp_tx_data[DREC_TX_BUF0] |= (U4)u1_s_drec_tx_datanm2 << DREC_TX_SHIFT_DATA_NM2;     /* DATA_NM2 */

 /* u1_t_tx = (U1)0U; */
 /* u4_tp_tx_data[DREC_TX_BUF0] |= (U4)u1_t_tx; */                                         /* D_N_INF is 0 transmission */

    u1_t_tx = (U1)U1_MAX;
    u4_tp_tx_data[DREC_TX_BUF0] |= (U4)u1_t_tx << DREC_TX_SHIFT_RHEO_IN;                   /* RHEO_IN  */

    u1_t_tx = (U1)U1_MAX;
    u4_tp_tx_data[DREC_TX_BUF0] |= (U4)u1_t_tx << DREC_TX_SHIFT_ILL_OUT;                   /* ILL_OUT  */

 /* u1_t_tx = (U1)0U; */
 /* u4_tp_tx_data[DREC_TX_BUF0] |= (U4)u1_t_tx << DREC_TX_SHIFT_SW_INF; */                 /* SW_INF is 0 transmission  */

    u1_t_tx = (U1)U1_MAX;
    u4_tp_tx_data[DREC_TX_BUF1] |= (U4)u1_t_tx;                                            /* IG_VOL   */

    u1_t_tx = (U1)U1_MAX;
    u4_tp_tx_data[DREC_TX_BUF1] |= (U4)u1_t_tx << DREC_TX_SHIFT_DISP_TMP;                  /* DISP_TMP */

 /* u1_t_tx = (U1)0U; */
 /* u4_tp_tx_data[DREC_TX_BUF1] |= (U4)u1_t_tx << DREC_TX_SHIFT_LN_FC; */                  /* LN_FC is 0 transmission   */

 /* u1_t_tx = (U1)0U; */
 /* u4_tp_tx_data[DREC_TX_BUF1] |= (U4)u1_t_tx << DREC_TX_SHIFT_RF_FC; */                  /* RF_FC is 0 transmission   */

    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM1TO2_MET1D51, &u4_tp_tx_data[0], (U2)DREC_TX_VM_2WORD);
}
/*===================================================================================================================================*/
/*  void    vd_g_DrecTxWkupInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DrectxWkupInit(void)
{
    U4                  u4_t_loop;
    U4                  u4_tp_tx_data[DREC_TX_VM_2WORD];
    U1                  u1_t_br;
    U1                  u1_t_rimsts;
    U1                  u1_t_tx;

    u1_s_drec_com_cnt     = (U1)0U;
    u1_s_drec_tx_datanm2  = (U1)0U;

    u1_t_br = (U1)0U;
    u1_t_rimsts = u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_DREC_TX, &u1_t_br);

    if((u1_t_rimsts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        u1_s_drec_tx_datanm2 = (u1_t_br & (U1)DREC_TX_SIG_MASK_2BIT);
    }
    else{
        vd_g_Rim_WriteU1((U2)RIMID_U1_DREC_TX, u1_s_drec_tx_datanm2);
    }

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)DREC_TX_VM_2WORD; u4_t_loop++){
        u4_tp_tx_data[u4_t_loop] = (U4)0U;
    }

    u4_tp_tx_data[DREC_TX_BUF0] |= (U4)u1_s_drec_tx_datanm2 << DREC_TX_SHIFT_DATA_NM2;     /* DATA_NM2 */

 /* u1_t_tx = (U1)0U; */
 /* u4_tp_tx_data[DREC_TX_BUF0] |= (U4)u1_t_tx; */                                         /* D_N_INF is 0 transmission */

    u1_t_tx = (U1)U1_MAX;
    u4_tp_tx_data[DREC_TX_BUF0] |= (U4)u1_t_tx << DREC_TX_SHIFT_RHEO_IN;                   /* RHEO_IN  */

    u1_t_tx = (U1)U1_MAX;
    u4_tp_tx_data[DREC_TX_BUF0] |= (U4)u1_t_tx << DREC_TX_SHIFT_ILL_OUT;                   /* ILL_OUT  */

 /* u1_t_tx = (U1)0U; */
 /* u4_tp_tx_data[DREC_TX_BUF0] |= (U4)u1_t_tx << DREC_TX_SHIFT_SW_INF; */                 /* SW_INF is 0 transmission  */

    u1_t_tx = (U1)U1_MAX;
    u4_tp_tx_data[DREC_TX_BUF1] |= (U4)u1_t_tx;                                            /* IG_VOL   */

    u1_t_tx = (U1)U1_MAX;
    u4_tp_tx_data[DREC_TX_BUF1] |= (U4)u1_t_tx << DREC_TX_SHIFT_DISP_TMP;                  /* DISP_TMP */

 /* u1_t_tx = (U1)0U; */
 /* u4_tp_tx_data[DREC_TX_BUF1] |= (U4)u1_t_tx << DREC_TX_SHIFT_LN_FC; */                  /* LN_FC is 0 transmission   */

 /* u1_t_tx = (U1)0U; */
 /* u4_tp_tx_data[DREC_TX_BUF1] |= (U4)u1_t_tx << DREC_TX_SHIFT_RF_FC; */                  /* RF_FC is 0 transmission   */

    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM1TO2_MET1D51, &u4_tp_tx_data[0], (U2)DREC_TX_VM_2WORD);
}
/*===================================================================================================================================*/
/*  void    vd_g_DrectxMainTask(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DrectxMainTask(void)
{
    if(u1_s_drec_com_cnt < (U1)U1_MAX){
        u1_s_drec_com_cnt++;
    }

    if(u1_s_drec_com_cnt > (U1)DREC_TX_CYC_TIME){
        u1_s_drec_tx_datanm2 = (u1_s_drec_tx_datanm2 + (U1)DREC_TX_CNT_SIG) & (U1)DREC_TX_FNC_BIT_MAX;
        vd_g_Rim_WriteU1((U2)RIMID_U1_DREC_TX, u1_s_drec_tx_datanm2);
        u1_s_drec_com_cnt = (U1)DREC_TX_CYC_INIT;
    }

    vd_s_DrectxMsg_MET1D51();
}
/*===================================================================================================================================*/
/*  static void    vd_s_DrectxMsg_MET1D51(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_DrectxMsg_MET1D51(void)
{
    static const U2     u2_s_DREC_TX_VOL_ADC_MAX = (U2)0x0fffU;
    static const U2     u2_s_DREC_TX_VOL_MUL     = (U2)1243U;
    static const U2     u2_s_DREC_TX_VOL_DIV     = (U2)20480U;

    U4                  u4_t_loop;
    U4                  u4_tp_tx_data[DREC_TX_VM_2WORD];
    U4                  u4_t_vol;
    U2                  u2_t_adc;
    U1                  u1_t_tx;

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)DREC_TX_VM_2WORD; u4_t_loop++){
        u4_tp_tx_data[u4_t_loop] = (U4)0U;
    }

    u1_t_tx = (u1_s_drec_tx_datanm2 & (U1)DREC_TX_SIG_MASK_2BIT);
    u4_tp_tx_data[DREC_TX_BUF0] |= (U4)u1_t_tx << DREC_TX_SHIFT_DATA_NM2;       /* DATA_NM2 */

    u1_t_tx = (u1_g_DimDrTxDninf() & (U1)DREC_TX_SIG_MASK_2BIT);
    u4_tp_tx_data[DREC_TX_BUF0] |= (U4)u1_t_tx;                                 /* D_N_INF  */

    u1_t_tx = u1_g_IllumiRheoDrTxRheoin();
    u4_tp_tx_data[DREC_TX_BUF0] |= (U4)u1_t_tx << DREC_TX_SHIFT_RHEO_IN;        /* RHEO_IN  */

    u1_t_tx = u1_g_IllumiTftbkDrTxIllout();
    u4_tp_tx_data[DREC_TX_BUF0] |= (U4)u1_t_tx << DREC_TX_SHIFT_ILL_OUT;        /* ILL_OUT  */

 /* u1_t_tx = (U1)0U; */
 /* u4_tp_tx_data[DREC_TX_BUF0] |= (U4)u1_t_tx << DREC_TX_SHIFT_SW_INF; */      /* SW_INF is 0 transmission */

    u2_t_adc = u2_g_IoHwAdcLv((U1)ADC_CH_B_MON2);
    if(u2_t_adc <= u2_s_DREC_TX_VOL_ADC_MAX){
        u4_t_vol = ((U4)u2_t_adc * (U4)u2_s_DREC_TX_VOL_MUL) / (U4)u2_s_DREC_TX_VOL_DIV;
        if(u4_t_vol > (U4)U1_MAX){
            u4_t_vol = (U4)U1_MAX;
        }
    }
    else{
        u4_t_vol = (U4)U1_MAX;
    }

    u1_t_tx = (U1)u4_t_vol;
    u4_tp_tx_data[DREC_TX_BUF1] |= (U4)u1_t_tx;                                 /* IG_VOL   */

    u1_t_tx = (U1)U1_MAX;
    u4_tp_tx_data[DREC_TX_BUF1] |= (U4)u1_t_tx << DREC_TX_SHIFT_DISP_TMP;       /* DISP_TMP */

 /* u1_t_tx = (U1)0U; */
 /* u4_tp_tx_data[DREC_TX_BUF1] |= (U4)u1_t_tx << DREC_TX_SHIFT_LN_FC; */       /* LN_FC is 0 transmission */

 /* u1_t_tx = (U1)0U; */
 /* u4_tp_tx_data[DREC_TX_BUF1] |= (U4)u1_t_tx << DREC_TX_SHIFT_RF_FC; */       /* RF_FC is 0 transmission */

    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM1TO2_MET1D51, &u4_tp_tx_data[0], (U2)DREC_TX_VM_2WORD);
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
/*  BEV-1    10/22/2025  YN       Change for BEV rebase.                                                                             */
/*  BEV-2    10/24/2025  YN       Change for BEV rebase.                                                                             */
/*  BEV-3    02/11/2026  YN       Change for BEV FF2.(MET-M_DVRD-CSTD-2-02)                                                          */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * AM   = Atsushi Mizutani, DensoTechno                                                                                           */
/*  * AS   = Ayumi Saito, DensoTechno                                                                                                */
/*  * YN   = Yujiro Nagaya, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
