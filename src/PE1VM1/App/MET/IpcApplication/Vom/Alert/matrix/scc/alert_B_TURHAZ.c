/* 5.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert B_TUHAZ                                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_B_TUHAZ_C_MAJOR                      (5)
#define ALERT_B_TUHAZ_C_MINOR                      (0)
#define ALERT_B_TUHAZ_C_PATCH                      (0)

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
#if (ALERT_B_TUHAZ_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_B_TUHAZ.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_B_TURHAZ_L_NUM_DST                 (8U)
#define ALERT_B_TURHAZ_R_NUM_DST                 (8U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_alert_b_turhaz_msgsts_l;
static U1      u1_s_alert_b_turhaz_msgsts_r;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertB_turhazLSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertB_turhazRSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_B_TURHAZ_L_DST[ALERT_B_TURHAZ_L_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_B_TURHAZ_L_ON,                                               /* 05 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 07 UNKNOWN                                         */
};

static const U1  u1_sp_ALERT_B_TURHAZ_R_DST[ALERT_B_TURHAZ_R_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_B_TURHAZ_R_ON,                                               /* 05 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 07 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_B_TURHAZ_MTRX[2] = {
    {
        &u4_s_AlertB_turhazLSrcchk,                                            /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_TURHAZ_L_DST[0],                                        /* u1p_DST                                            */
        (U2)ALERT_B_TURHAZ_L_NUM_DST,                                          /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertB_turhazRSrcchk,                                            /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_TURHAZ_R_DST[0],                                        /* u1p_DST                                            */
        (U2)ALERT_B_TURHAZ_R_NUM_DST,                                          /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertB_turhazInitvoid)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertB_turhazInit(void)
{
    u1_s_alert_b_turhaz_msgsts_l = (U1)COM_NO_RX;
    u1_s_alert_b_turhaz_msgsts_r = (U1)COM_NO_RX;
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_turhazLSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_VOM                                                                                                         */
/*                  u4_a_IGN_TM                                                                                                      */
/*                  u1_a_LAS                                                                                                         */
/*  Return:         u4_t_src_chk                                                                                                     */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_turhazLSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_B_TUHAZ_L_LSB_BDC1S23 = (U1)1U;
    static const U4 u4_s_ALERT_B_TUHAZ_L_BIT_BAT_WT  = (U4)0x00000004U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_BDC1S23_CH0,
                                    (U4)ALERT_CAN_SYS_ALL,
                                    (U2)U2_MAX) & (U1)COM_NO_RX;
    vd_g_AlertBRxTrnsSts(&u1_s_alert_b_turhaz_msgsts_l, u1_t_msgsts);

    u4_t_src_chk = (((U4)u1_s_alert_b_turhaz_msgsts_l & (U4)COM_NO_RX) << u1_s_ALERT_B_TUHAZ_L_LSB_BDC1S23);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_MTNLS_L, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_B_TUHAZ_L_BIT_BAT_WT;
    }

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_turhazRSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_VOM                                                                                                         */
/*                  u4_a_IGN_TM                                                                                                      */
/*                  u1_a_LAS                                                                                                         */
/*  Return:         u4_t_src_chk                                                                                                     */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_turhazRSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_B_TUHAZ_R_LSB_BDC1S23 = (U1)1U;
    static const U4 u4_s_ALERT_B_TUHAZ_R_BIT_BAT_WT  = (U4)0x00000004U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_BDC1S23_CH0,
                                    (U4)ALERT_CAN_SYS_ALL,
                                    (U2)U2_MAX) & (U1)COM_NO_RX;
    vd_g_AlertBRxTrnsSts(&u1_s_alert_b_turhaz_msgsts_r, u1_t_msgsts);

    u4_t_src_chk = (((U4)u1_s_alert_b_turhaz_msgsts_r & (U4)COM_NO_RX) << u1_s_ALERT_B_TUHAZ_R_LSB_BDC1S23);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_MTNLS_R, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_B_TUHAZ_R_BIT_BAT_WT;
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
/*  5.0.0    11/27/2025  SH       Newly created for Bev Step3                                                                        */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * SH   = Sae Hirose, Denso Techno                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
