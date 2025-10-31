/* 5.2.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert B_TPWSR                                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_B_TPWSR_C_MAJOR                    (5)
#define ALERT_B_TPWSR_C_MINOR                    (2)
#define ALERT_B_TPWSR_C_PATCH                    (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"
#include "alert_brx.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_B_TPWSR_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_B_TPWSR.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_B_TPWSR_NUM_DST                    (16U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_alert_b_tpwsr_est_tm;
static U1      u1_s_alert_b_tpwsr_pwwarn_last;
static U1      u1_s_alert_b_tpwsr_srwarn_last;
static U1      u1_s_alert_b_tpwsr_msgsts;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertB_tpwsrSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_B_TPWSR_DST[ALERT_B_TPWSR_NUM_DST] = {
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
    (U1)ALERT_REQ_B_TPWSR_WRN_SR,                                              /* 10 WRN_SR                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_B_TPWSR_WRN_PW,                                              /* 12 WRN_PW                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_B_TPWSR_WRN,                                                 /* 14 WRN                                             */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_B_TPWSR_MTRX[1] = {
    {
        &u4_s_AlertB_tpwsrSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_TPWSR_DST[0],                                           /* u1p_DST                                            */
        (U2)ALERT_B_TPWSR_NUM_DST,                                             /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertB_tpwsrInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertB_tpwsrInit(void)
{
    u4_s_alert_b_tpwsr_est_tm      = (U4)U4_MAX;
    u1_s_alert_b_tpwsr_pwwarn_last = (U1)0U;
    u1_s_alert_b_tpwsr_srwarn_last = (U1)0U;
    u1_s_alert_b_tpwsr_msgsts      = (U1)COM_NO_RX;
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_tpwsrSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_tpwsrSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U4  u4_s_ALERT_B_TPWSR_TM_EST     = ((U4)30000U / (U4)ALERT_MAIN_TICK);
    static const U4  u4_s_ALERT_B_TPWSR_TM_RST     = (U4)1U;
    static const U4  u4_s_ALERT_B_TPWSR_BIT_TM_EST = (U4)0x00000001U;
    static const U4  u4_s_ALERT_B_TPWSR_BIT_BAT_WT = (U4)0x00000008U;
    static const U1  u1_s_ALERT_B_TPWSR_LSB_PWWARN = (U1)2U;
    static const U1  u1_s_ALERT_B_TPWSR_LSB_SRWARN = (U1)1U;
    U4               u4_t_srcchk;
    U1               u1_t_pwwarn;
    U1               u1_t_srwarn;
    U1               u1_t_msgsts;

    u1_t_msgsts = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_BDB1S03_CH0,
                                    (U4)OXCAN_SYS_IGR | (U4)OXCAN_SYS_IGP,
                                    (U2)U2_MAX) & (U1)COM_NO_RX;
    vd_g_AlertBRxTrnsSts(&u1_s_alert_b_tpwsr_msgsts, u1_t_msgsts);

    u4_t_srcchk = (U4)0U;
    u1_t_pwwarn = (U1)0U;
    u1_t_srwarn = (U1)0U;
    if((u1_s_alert_b_tpwsr_msgsts & (U1)COM_NO_RX) != (U1)COM_NO_RX){
        (void)Com_ReceiveSignal(ComConf_ComSignal_PWWARN, &u1_t_pwwarn);
        u4_t_srcchk  = ((U4)u1_t_pwwarn << u1_s_ALERT_B_TPWSR_LSB_PWWARN);
#if defined(ComConf_ComSignal_SRWARN)
        (void)Com_ReceiveSignal(ComConf_ComSignal_SRWARN, &u1_t_srwarn);
#endif
        u4_t_srcchk |= ((U4)u1_t_srwarn << u1_s_ALERT_B_TPWSR_LSB_SRWARN);
    }

    if(((u1_t_pwwarn ^ u1_s_alert_b_tpwsr_pwwarn_last) != (U1)0U) ||
       ((u1_t_srwarn ^ u1_s_alert_b_tpwsr_srwarn_last) != (U1)0U)){
        u4_s_alert_b_tpwsr_est_tm = u4_s_ALERT_B_TPWSR_TM_RST;
    }
    else if(u4_s_alert_b_tpwsr_est_tm >= u4_s_ALERT_B_TPWSR_TM_EST){
        u4_s_alert_b_tpwsr_est_tm = u4_s_ALERT_B_TPWSR_TM_EST;
        u4_t_srcchk              |= u4_s_ALERT_B_TPWSR_BIT_TM_EST;
    }
    else{
        u4_s_alert_b_tpwsr_est_tm++;
    }

    u1_s_alert_b_tpwsr_pwwarn_last = u1_t_pwwarn;
    u1_s_alert_b_tpwsr_srwarn_last = u1_t_srwarn;

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_srcchk |= u4_s_ALERT_B_TPWSR_BIT_BAT_WT;
    }

    return(u4_t_srcchk);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     4/ 6/2020  MY       New.                                                                                               */
/*  5.0.1     3/26/2021  TN       Update for 840B CV(Version update).                                                                */
/*  5.0.2     9/27/2021  TM       Add compile switch for SRWARN.                                                                     */
/*  5.1.0    10/27/2021  HU       Update for 840B 1A(Version update).                                                                */
/*  5.2.0    11/ 4/2021  MO       Change timer thresh.                                                                               */
/*                                                                                                                                   */
/*  * MY   = Masaki Yoshizawa, NTTD MSE                                                                                              */
/*  * TN   = Toshiaki Nagashima, NTTD MSE                                                                                            */
/*  * TM   = Tatsuya Mori, NTTD MSE                                                                                                  */
/*  * HU   = Hidekazu Usui, NTTD MSE                                                                                                 */
/*  * MO   = Masayuki Oofuji, NTTD MSE                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
