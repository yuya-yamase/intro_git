/* 5.2.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert B_TFFOG                                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_B_TFFOG_C_MAJOR                    (5)
#define ALERT_B_TFFOG_C_MINOR                    (2)
#define ALERT_B_TFFOG_C_PATCH                    (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"
#include "alert_brx.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "oxcan_channel_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_B_TFFOG_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_B_TFFOG.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_B_TFFOG_NUM_DST                    (16U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_alert_b_tffog_dlycnt;
static U1      u1_s_alert_b_tffog_msgsts_ffog;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertB_tffogSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_B_TFFOG_DST[ALERT_B_TFFOG_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_B_TFFOG_ON,                                                  /* 11 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_B_TFFOG_MTRX[1] = {
    {
        &u4_s_AlertB_tffogSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_TFFOG_DST[0],                                           /* u1p_DST                                            */
        (U2)ALERT_B_TFFOG_NUM_DST,                                             /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertB_tffogInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertB_tffogInit(void)
{
    u4_s_alert_b_tffog_dlycnt      = (U4)0U;
    u1_s_alert_b_tffog_msgsts_ffog = (U1)COM_NO_RX;
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_tffogSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_tffogSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_B_TFFOG_TO_THRESH   = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_B_TFFOG_LSB_SGNL    = (U1)1U;
    static const U1 u1_s_ALERT_B_TFFOG_LSB_MSGSTS  = (U1)2U;
    static const U4 u4_s_ALERT_B_TFFOG_TIM_DLY     = ((U4)300U  / (U4)ALERT_CH_TICK);
    static const U4 u4_s_ALERT_B_TFFOG_BIT_DLY_CMP = (U4)0x00000001U;
    static const U4 u4_s_ALERT_B_TFFOG_BIT_BAT_WT  = (U4)0x00000008U;
    U1              u1_t_trns_fact;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_trns_fact = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_BDB1S03_CH0,
                                      (U4)ALERT_CAN_SYS_PNC_ALL,
                                      u2_s_ALERT_B_TFFOG_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) == (U1)0U){
        u1_t_trns_fact |= (U1)ALERT_BRX_FACT_NO_RX;
    }
    vd_g_AlertBRxTrnsSts(&u1_s_alert_b_tffog_msgsts_ffog, u1_t_trns_fact);

    u1_t_sgnl      = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_FFOG, &u1_t_sgnl);

    u4_t_src_chk   = (U4)u1_t_sgnl << u1_s_ALERT_B_TFFOG_LSB_SGNL;

    if((u1_t_sgnl                                        == (U1)0U       ) ||
       ((u1_s_alert_b_tffog_msgsts_ffog & (U1)COM_NO_RX) == (U1)COM_NO_RX)){
        u4_s_alert_b_tffog_dlycnt = (U4)0U;
    }
    else if(u4_s_alert_b_tffog_dlycnt >= u4_s_ALERT_B_TFFOG_TIM_DLY){
        u4_t_src_chk             |= u4_s_ALERT_B_TFFOG_BIT_DLY_CMP;
        u4_s_alert_b_tffog_dlycnt = u4_s_ALERT_B_TFFOG_TIM_DLY;
    }
    else{
        u4_s_alert_b_tffog_dlycnt++;
    }

    u4_t_src_chk  |= (((U4)u1_s_alert_b_tffog_msgsts_ffog & (U4)COM_NO_RX) << u1_s_ALERT_B_TFFOG_LSB_MSGSTS);

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_B_TFFOG_BIT_BAT_WT;
    }

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     2/19/2020  ZS       New.                                                                                               */
/*  5.1.0    10/26/2021  HU       Update for 840B 1A(Version update).                                                                */
/*  5.2.0     1/29/2024  SW       Update for 19PFv3.                                                                                 */
/*                                                                                                                                   */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * HU   = Hidekazu Usui, NTTD MSE                                                                                                 */
/*  * SW   = Shun Watanabe, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
