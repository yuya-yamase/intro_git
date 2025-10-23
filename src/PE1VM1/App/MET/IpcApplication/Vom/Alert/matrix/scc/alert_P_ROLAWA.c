/* 5.2.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert P_ROLAWA                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_P_ROLAWA_C_MAJOR                   (5)
#define ALERT_P_ROLAWA_C_MINOR                   (2)
#define ALERT_P_ROLAWA_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_P_ROLAWA_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_P_ROLAWA.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_P_ROLAWA_BC_NUM_DST                (16U)
#define ALERT_P_ROLAWA_PD_NUM_DST                (32U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertP_rolawaBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertP_rolawaPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_P_ROLAWA_BC_DST[ALERT_P_ROLAWA_BC_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_P_ROLAWA_BC_VEHRUN,                                          /* 01 VEHRUN                                          */
    (U1)ALERT_REQ_P_ROLAWA_BC_VEHSTP,                                          /* 02 VEHSTP                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_P_ROLAWA_PD_DST[ALERT_P_ROLAWA_PD_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_P_ROLAWA_PD_VEHRUN,                                          /* 01 VEHRUN                                          */
    (U1)ALERT_REQ_P_ROLAWA_PD_VEHSTP,                                          /* 02 VEHSTP                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_P_ROLAWA_PD_VEHSTP2,                                         /* 04 VEHSTP2                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 16 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 17 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 18 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 19 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 20 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 21 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 22 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 23 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 24 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 25 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 26 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 27 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 28 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 29 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 30 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 31 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_P_ROLAWA_MTRX[2] = {
    {
        &u4_s_AlertP_rolawaBcSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_ROLAWA_BC_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_P_ROLAWA_BC_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertP_rolawaPdSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_ROLAWA_PD_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_P_ROLAWA_PD_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_rolawaBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_rolawaBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if 0   /* BEV Rebase provisionally */
#if (defined(OXCAN_PDU_RX_CAN_ENG1S97) || defined(OXCAN_PDU_RX_CAN_ENG1G97)) && defined(ComConf_ComSignal_B_ESTBZ)
    static const U2 u2_s_ALERT_P_ROLAWA_BC_TO_THRESH = ((U2)5200U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_B_ESTBZ_LSB_MSGSTS    = (U1)2U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

#ifdef OXCAN_PDU_RX_CAN_ENG1G97
    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1G97,
                                          (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                          u2_s_ALERT_P_ROLAWA_BC_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#else
    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1S97,
                                          (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                          u2_s_ALERT_P_ROLAWA_BC_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#endif /* OXCAN_PDU_RX_CAN_ENG1G97 */

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_ESTBZ, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_B_ESTBZ_LSB_MSGSTS);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* (defined(OXCAN_PDU_RX_CAN_ENG1S97) | defined(OXCAN_PDU_RX_CAN_ENG1G97)) && defined(ComConf_ComSignal_B_ESTBZ) */
#else   /* BEV Rebase provisionally */
    return((U4)0U);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_rolawaPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_rolawaPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if 0   /* BEV Rebase provisionally */
#if (defined(OXCAN_PDU_RX_CAN_ENG1S97) || defined(OXCAN_PDU_RX_CAN_ENG1G97)) && defined(ComConf_ComSignal_B_ESTMSG)
    static const U1 u1_s_ALERT_B_ESTMSG_LSB_MSGSTS = (U1)4U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

#ifdef OXCAN_PDU_RX_CAN_ENG1G97
    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1G97,
                                          (U2)OXCAN_RX_SYS_NRX_IGR,
                                          (U2)U2_MAX) & (U1)COM_NO_RX;
#else
    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1S97,
                                          (U2)OXCAN_RX_SYS_NRX_IGR,
                                          (U2)U2_MAX) & (U1)COM_NO_RX;
#endif /* OXCAN_PDU_RX_CAN_ENG1G97 */

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_ESTMSG, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_B_ESTMSG_LSB_MSGSTS);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* (defined(OXCAN_PDU_RX_CAN_ENS1G97) | defined(OXCAN_PDU_RX_CAN_ENG1G97)) && defined(ComConf_ComSignal_B_ESTMSG) */
#else   /* BEV Rebase provisionally */
    return((U4)0U);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     2/27/2020  SK       New.                                                                                               */
/*  5.1.0     8/24/2020  TN       Change timeout status for ENG1G97 5000ms -> 5200ms.                                                */
/*  5.2.0     9/ 6/2021  TM       Fix Primary compile switch to ENG1G97.                                                             */
/*                                                                                                                                   */
/*  * SK   = Satoshi Kasai, NTTD MSE                                                                                                 */
/*  * TN   = Toshiaki Nagashima, NTTD MSE                                                                                            */
/*  * TM   = Tatsuya Mori, NTTD MSE                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
