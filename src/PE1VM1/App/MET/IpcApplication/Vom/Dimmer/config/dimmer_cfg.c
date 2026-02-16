/* 1.5.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Dimmer                                                                                                                           */
/*  configuration                                                                                                                    */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DIMMER_CFG_C_MAJOR                       (1)
#define DIMMER_CFG_C_MINOR                       (5)
#define DIMMER_CFG_C_PATCH                       (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "dimmer_cfg_private.h"
#include "dim_daynight_cfg_private.h"
#include "dim_usadjbysw_cfg_private.h"

#include "oxcan.h"
#if 0   /* BEV Rebase provisionally */
#include "es_inspect.h"
#endif   /* BEV Rebase provisionally */

#if 0   /* BEV Rebase provisionally */
#include "dio_if.h"
#endif   /* BEV Rebase provisionally */
#include "xspi_met_ch0.h"
#if 0   /* BEV Rebase provisionally */
#include "iohw_adc_sh.h"
#endif   /* BEV Rebase provisionally */
#include "mcst.h"
#include "hmiscreen.h"

#include "calibration.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DIMMER_CFG_C_MAJOR != DIMMER_H_MAJOR) || \
     (DIMMER_CFG_C_MINOR != DIMMER_H_MINOR) || \
     (DIMMER_CFG_C_PATCH != DIMMER_H_PATCH))
#error "dimmer_cfg.c and dimmer.h : source and header files are inconsistent!"
#endif

#if ((DIMMER_CFG_C_MAJOR != DIMMER_CFG_H_MAJOR) || \
     (DIMMER_CFG_C_MINOR != DIMMER_CFG_H_MINOR) || \
     (DIMMER_CFG_C_PATCH != DIMMER_CFG_H_PATCH))
#error "dimmer_cfg.c and dimmer_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DIM_IF_NUM_CFG                           (1U)

#define DIM_MAIN_TICK                            (20U) /* 20 milliseconds */

#define DIM_CANTX_TACN_OFF                       (0x03U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DIM_DAYNIGHT_ADIM_DAY                    (0x02U)
#define DIM_DAYNIGHT_ADIM_NIGHT                  (0x03U)

#define DIM_CFG_CSTM_SW_NON                      (0x00U)
#define DIM_CFG_CSTM_SW_UP                       (0x01U)
#define DIM_CFG_CSTM_SW_DW                       (0x02U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DIM_USADJ_BY_SW_COM_RX_UNKNOWN != COM_NO_RX  ) || \
     (DIM_USADJ_BY_SW_COM_RX_INVALID != COM_TIMEOUT))
#error "DIM_USADJ_BY_SW_COM_RX_UNKNOWN shall be equal to COM_NO_RX and DIM_USADJ_BY_SW_COM_RX_INVALID shall be equal to COM_TIMEOUT."
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1   u1_s_dim_adim_rxcnt;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static inline U1    u1_s_DimCfgCalibU1MaxChk(const U1 u1_a_CALIBID, const U1 u1_a_MAX, const U1 u1_a_DEF);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_DIM_IF             st_gp_DIM_IF_CFG[DIM_IF_NUM_CFG] = {
    {
        &u1_g_DimDaynightAdimchk,     /* fp_u1_DAY_NIGHT */
        &vd_g_DimUsadjbySwUpdt        /* fp_vd_US_ADJUST */
    }
};
const U1                    u1_g_DIM_IF_NUM_CFG = (U1)DIM_IF_NUM_CFG;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  dim_daynight                                                                                                                     */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2                    u2_gp_DIM_ADIM_RX_TOUT[DIM_ADIM_NUM_RX_TOUT] = {
    ((U2)3000U + (U2)3600U) / (U2)DIM_MAIN_TICK,   /* power-on mask + rxto =  3 + 3.6 seconds  */
    (U2)3600U / (U2)DIM_MAIN_TICK                  /* 3.6 seconds                              */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  dim_usadjbysw                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2                    u2_g_DIM_USADJ_BY_SW_NVM_UPDT = (U2)3000U / (U2)DIM_MAIN_TICK;
const U2                    u2_g_DIM_USADJ_BY_SW_LP_UPDT  = (U2)900U / (U2)DIM_MAIN_TICK;
const U2                    u2_g_DIM_USADJ_BY_SW_LP_ACT   = (U2)800U / (U2)DIM_MAIN_TICK;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_DimCfgInit(void)                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DimCfgInit(void)
{
    U1                      u1_t_tx;

    u1_t_tx = (U1)0U;
#if 0    /* BEV Rebase provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_D_N_INF,  &u1_t_tx);
#endif   /* BEV Rebase provisionally */

    vd_g_DimDaynightInit();
    vd_g_DimUsadjbySwInit();

    u1_s_dim_adim_rxcnt = u1_g_oXCANRxdEvcnt((U2)OXCAN_RXD_PDU_CAN_BDB1S01_CH0);
}
/*===================================================================================================================================*/
/*  U1      u1_g_DimCfgIFidx(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_DimCfgIFidx(void)
{
    return((U1)0U);
}
/*===================================================================================================================================*/
/*  U1      u1_g_DimDaynightCfgRxEnabled(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_DimDaynightCfgRxEnabled(void)
{
    U4                      u4_t_canbus_sts;
    U1                      u1_t_rx_ena;

    u4_t_canbus_sts = u4_g_oXCANSysActvtd() & ((U4)OXCAN_SYS_PNC_16 | (U4)OXCAN_SYS_PNC_44);
    if(u4_t_canbus_sts != (U4)0U){
        u1_t_rx_ena = (U1)TRUE;
    }
    else{
        u1_t_rx_ena = (U1)FALSE;
    }

    return(u1_t_rx_ena);
}
/*===================================================================================================================================*/
/*  U1      u1_g_DimDaynightCfgAdimRxEvt(U1 * u1_ap_daynight)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_DimDaynightCfgAdimRxEvt(U1 * u1_ap_daynight)
{
    U1                      u1_t_rx_cnt;
    U1                      u1_t_rx_evt;
    U1                      u1_t_adim;

    u1_t_rx_evt = (U1)FALSE;

    u1_t_rx_cnt = u1_g_oXCANRxdEvcnt((U2)OXCAN_RXD_PDU_CAN_ZN11S14_CH0);
    if(u1_t_rx_cnt != u1_s_dim_adim_rxcnt){

        u1_t_adim = (U1)0U;
        (void)Com_ReceiveSignal(ComConf_ComSignal_ADIM2, &u1_t_adim);
        if(u1_t_adim == (U1)DIM_DAYNIGHT_ADIM_DAY){
            (*u1_ap_daynight) = (U1)DIM_DAYNIGHT_LVL_DAY;
            u1_t_rx_evt       = (U1)TRUE;
        }
        else if(u1_t_adim == (U1)DIM_DAYNIGHT_ADIM_NIGHT){
            (*u1_ap_daynight) = (U1)DIM_DAYNIGHT_LVL_NIGHT;
            u1_t_rx_evt       = (U1)TRUE;
        }
        else{
            /* Do nothing */
        }
    }
    u1_s_dim_adim_rxcnt = u1_t_rx_cnt;

    return(u1_t_rx_evt);
}
/*===================================================================================================================================*/
/*  void    vd_g_DimDaynightCfgAdimRxchk(const U1 u1_a_RX_CHK, const U1 u1_a_DAYNIGHT)                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DimDaynightCfgAdimRxchk(const U1 u1_a_RX_CHK, const U1 u1_a_DAYNIGHT)
{
    static const U1         u1_sp_DIM_D_N_INF_BY_RX_CHK[DIM_ADIM_NUM_RX_CHK] = {
        (U1)0x00U,  /* DIM_ADIM_RX_CHK_VALID  (0U) */
        (U1)0x01U,  /* DIM_ADIM_RX_CHK_RT_1ST (1U) */
        (U1)0x01U,  /* DIM_ADIM_RX_CHK_RT_2ND (2U) */
        (U1)0x00U,  /* DIM_ADIM_RX_CHK_INIT   (3U) */
        (U1)0x00U   /* DIM_ADIM_RX_CHK_INACT  (4U) */
    };

    U1                      u1_t_tx;

    if(u1_a_RX_CHK != (U1)DIM_ADIM_RX_CHK_VALID){
        u1_t_tx = u1_sp_DIM_D_N_INF_BY_RX_CHK[u1_a_RX_CHK];
    }
    else if(u1_a_DAYNIGHT == (U1)DIM_DAYNIGHT_LVL_DAY){
        u1_t_tx = (U1)DIM_DAYNIGHT_ADIM_DAY;
    }
    else{
        u1_t_tx = (U1)DIM_DAYNIGHT_ADIM_NIGHT;
    }

#if 0    /* BEV Rebase provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_D_N_INF,  &u1_t_tx);
#endif   /* BEV Rebase provisionally */
}
/*===================================================================================================================================*/
/*  U1      u1_g_DimUsadjbySwCfgAdjstbl(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_DimUsadjbySwCfgAdjstbl(void)
{
    U1 u1_t_adjstbl;

    u1_t_adjstbl = u1_g_HmiScreen();
    return(u1_t_adjstbl);
}
/*===================================================================================================================================*/
/*  U1      u1_g_DimUsadjbySwCfgUpdwchk(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_DimUsadjbySwCfgUpdwchk(void)
{
    U1          u1_t_swchk;
    U1          u1_t_ch_act;

    u1_t_swchk  = (U1)0U;

    u1_t_ch_act = u1_g_XSpiDimSw();
    if(u1_t_ch_act == (U1)DIM_CFG_CSTM_SW_UP){
        u1_t_swchk |= (U1)DIM_USADJ_BY_SW_SWON_BIT_UP;
    }
    else if(u1_t_ch_act == (U1)DIM_CFG_CSTM_SW_DW){
        u1_t_swchk |= (U1)DIM_USADJ_BY_SW_SWON_BIT_DW;
    }
    else{
        /* Do Nothing */
    }

    return(u1_t_swchk);
}
/*===================================================================================================================================*/
/*  U1      u1_g_DimUsadjbySwVrCfgReAd(U2 * u2_a_ad)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_DimUsadjbySwVrCfgReAd(U2 * u2_a_ad)
{
    return((U1)FALSE);
}
/*===================================================================================================================================*/
/*  void    vd_g_DimUsadjbySwCfgNvmRead(U2 * u2_ap_lvl)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DimUsadjbySwCfgNvmRead(U2 * u2_ap_lvl)
{
    U1         u1_t_rheo_pos;
    U2         u2_t_lvl;
    U4         u4_t_chk_value;

    u4_t_chk_value = u4_g_McstBf((U1)MCST_BFI_RHEO_DAY);
    if(u4_t_chk_value > (U4)U2_MAX){
        u4_t_chk_value = (U4)U2_MAX;
    }
    u2_t_lvl = (U2)u4_t_chk_value;
    if(u2_t_lvl > (U2)DIM_USADJ_BY_SW_LVL_MAX){
        u2_ap_lvl[DIM_DAYNIGHT_LVL_DAY] = (U2)DIM_USADJ_BY_SW_LVL_MAX;
    }
    else{
        u2_ap_lvl[DIM_DAYNIGHT_LVL_DAY] = u2_t_lvl;
    }

    u4_t_chk_value = u4_g_McstBf((U1)MCST_BFI_RHEO_NIGHT);
    if(u4_t_chk_value > (U4)U2_MAX){
        u4_t_chk_value = (U4)U2_MAX;
    }
    u2_t_lvl = (U2)u4_t_chk_value;
    if(u2_t_lvl > (U2)DIM_USADJ_BY_SW_LVL_MAX){
        u1_t_rheo_pos = u1_s_DimCfgCalibU1MaxChk(u1_CALIB_MCUID0340_RHEOPOS_NIGHT, (U1)CALIB_MCUID0340_MAX, (U1)CALIB_MCUID0340_DEF);
        u2_ap_lvl[DIM_DAYNIGHT_LVL_NIGHT] = (U2)u1_t_rheo_pos;
    }
    else{
        u2_ap_lvl[DIM_DAYNIGHT_LVL_NIGHT] = u2_t_lvl;
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_DimUsadjbySwCfgNvmWrite(const U2 * u2_ap_LVL)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DimUsadjbySwCfgNvmWrite(const U2 * u2_ap_LVL)
{
    U1          u1_t_esi_chk;

#if 0   /* BEV Rebase provisionally */
    u1_t_esi_chk = u1_g_ESInspectMdBfield();
#else   /* BEV Rebase provisionally */
    u1_t_esi_chk = (U1)0U;
#endif   /* BEV Rebase provisionally */
    if(u1_t_esi_chk == (U1)0U){
        vd_g_McstBfPut((U1)MCST_BFI_RHEO_DAY,   (U4)u2_ap_LVL[DIM_DAYNIGHT_LVL_DAY]  );
        vd_g_McstBfPut((U1)MCST_BFI_RHEO_NIGHT, (U4)u2_ap_LVL[DIM_DAYNIGHT_LVL_NIGHT]);
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_DimUsadjbySwCfgComRxTAIL(U1 * u1p_a_tail)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_DimUsadjbySwCfgComRxTAIL(U1 * u1p_a_tail)
{
    U1          u1_t_rx_chk;
    U1          u1_t_tail_sup;

    u1_t_tail_sup = u1_CALIB_MCUID0341_TAIL;

    if(u1_t_tail_sup == (U1)TRUE){
        (void)Com_ReceiveSignal(ComConf_ComSignal_TAIL, u1p_a_tail);
        u1_t_rx_chk = Com_GetIPDUStatus(MSG_BDB1S03_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    }
    else{
        u1_t_rx_chk = (U1)COM_NO_RX;
    }

    return(u1_t_rx_chk);
}
/*===================================================================================================================================*/
/*  static inline U1    u1_s_DimCfgCalibU1MaxChk(const U1 u1_a_CALIBID, const U1 u1_a_MAX, const U1 u1_a_DEF)                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const U1 u1_a_CALIBID                                                                                            */
/*                  const U1 u1_a_MAX                                                                                                */
/*                  const U1 u1_a_DEF                                                                                                */
/*  Return:         U1 u1_t_ret                                                                                                      */
/*===================================================================================================================================*/
static inline U1    u1_s_DimCfgCalibU1MaxChk(const U1 u1_a_CALIBID, const U1 u1_a_MAX, const U1 u1_a_DEF)
{
    U1 u1_t_ret;

    u1_t_ret = u1_a_CALIBID;
    if(u1_t_ret > u1_a_MAX){
        u1_t_ret = u1_a_DEF;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/19/2018  TN       New.                                                                                               */
/*  1.1.0     1/15/2019  TN       dimmer v1.0.0 -> v1.1.0.                                                                           */
/*  1.2.0     2/26/2019  TN       dimmer v1.1.0 -> v1.2.0.                                                                           */
/*  1.3.0     9/11/2020  SH       Support PersonalCustomize, Change ADIM fail time, Delete TAIL Judge.                               */
/*  1.3.1    12/21/2020  KM       dimmer v1.3.0 -> v1.3.1.                                                                           */
/*  1.4.0     1/12/2021  KM       dimmer v1.3.1 -> v1.4.0.                                                                           */
/*  1.4.1     1/26/2021  KM       Fixed QAC warning.(No.2013 No Comments in Else Case)                                               */
/*  1.5.0     2/08/2021  KM       Support TAIL Judgement.                                                                            */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  0.0.1    10/12/2018  TN       dim_usadjbysw v1.0.0 -> v1.1.0.                                                                    */
/*  0.0.2    12/07/2021  SA       Support Hardsw and Softsw.                                                                         */
/*  0.0.3    05/12/2023  HH       Support Only Hardsw.                                                                               */
/*  19PFv3-1 04/12/2024  SH       Add calibration guard                                                                              */
/*  19PFv3-2 06/27/2024  TN(DT)   Delete Calibration Guard Process.                                                                  */
/*  19PFv3-3 07/12/2024  TN(DT)   Add Calibration Guard to Avoid out of array references.                                            */
/*  BEV-1    06/30/2025  SF       BSW Update:u1_g_DimDaynightCfgRxEnabled was modified                                               */
/*  BEV-2    10/10/2025  KO       Configured for BEVstep3_Rebase                                                                     */
/*  BEV-3    01/21/2026  KO       Change dimming judgment signal from ADIM to ADIM2 for FF2                                          */
/*                                                                                                                                   */
/*  * TN     = Takashi Nagai, DENSO                                                                                                  */
/*  * SH     = Shota Higashide                                                                                                       */
/*  * KM     = Kota Matoba                                                                                                           */
/*  * SA     = Seiya Asaoka                                                                                                          */
/*  * HH     = Hiroki Hara                                                                                                           */
/*  * SH     = Sae Hirose, Denso Techno                                                                                              */
/*  * TN(DT) = Tetsushi Nakano, Denso Techno                                                                                         */
/*  * SF     = Seiya Fukutome, Denso Techno                                                                                          */
/*  * KO     = Kazuto Oishi,  Denso Techno                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
