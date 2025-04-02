/* 5.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert P_CHEENG                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_P_CHEENG_C_MAJOR                   (5)
#define ALERT_P_CHEENG_C_MINOR                   (4)
#define ALERT_P_CHEENG_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "oxcan_channel_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_P_CHEENG_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_P_CHEENG.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_P_CHEENG_WRN_NUM_DST               (32U)
#define ALERT_P_CHEENG_BC_NUM_DST                (4U)

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
static U4      u4_s_AlertP_cheengWrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertP_cheengBcSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertP_cheengWrnRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_P_CHEENG_WRN_DST[ALERT_P_CHEENG_WRN_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_P_CHEENG_WRN_MLFNC2,                                         /* 01 MLFNC2                                          */
    (U1)ALERT_REQ_P_CHEENG_WRN_MLFNC1,                                         /* 02 MLFNC1                                          */
    (U1)ALERT_REQ_P_CHEENG_WRN_MLFNC3_RW,                                      /* 03 MLFNC3_RW                                       */
    (U1)ALERT_REQ_P_CHEENG_WRN_MLFNC4_RW,                                      /* 04 MLFNC4_RW                                       */
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
static const U1  u1_sp_ALERT_P_CHEENG_BC_DST[ALERT_P_CHEENG_BC_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_P_CHEENG_BC_SINGLE,                                          /* 01 SINGLE                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 03 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_P_CHEENG_MTRX[2] = {
    {
        &u4_s_AlertP_cheengWrnSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertP_cheengWrnRwTx,                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_CHEENG_WRN_DST[0],                                      /* u1p_DST                                            */
        (U2)ALERT_P_CHEENG_WRN_NUM_DST,                                        /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertP_cheengBcSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_CHEENG_BC_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_P_CHEENG_BC_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_cheengWrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_cheengWrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#ifdef ComConf_ComSignal_B_ENGMSG
    static const U1 u1_s_ALERT_P_CHEENG_WRN_LSB_ENG1 = (U1)4U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

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
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_ENGMSG, &u1_t_sgnl);
#endif
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_P_CHEENG_WRN_LSB_ENG1);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* ComConf_ComSignal_B_ENGMSG */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_cheengBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_cheengBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#ifdef ComConf_ComSignal_B_ENGBZ
    static const U1 u1_s_ALERT_P_CHEENG_BC_LSB_MSTS = (U1)1U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

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
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_ENGBZ, &u1_t_sgnl);
#endif
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_P_CHEENG_BC_LSB_MSTS);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* ComConf_ComSignal_B_ENGBZ */
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertP_cheengWrnRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertP_cheengWrnRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    static const U2 u2_s_ALERT_P_CHEENG_WRN_RW_CRT = (U2)((U2)1U << ALERT_REQ_P_CHEENG_WRN_MLFNC3_RW)
                                                   | (U2)((U2)1U << ALERT_REQ_P_CHEENG_WRN_MLFNC4_RW);           /* EG1W             */
    static const U1 u1_s_ALERT_P_CHEENG_WRN_RW_MSK = (U1)0x07U;

    U1              u1_t_sgnl;
    U2              u2_t_rw;

    u2_t_rw  = ((U2)1U << (u1_a_DST & u1_s_ALERT_P_CHEENG_WRN_RW_MSK));
    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN)           != (U1)0U) &&
       ((u2_t_rw  & u2_s_ALERT_P_CHEENG_WRN_RW_CRT) != (U2)0U)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_EG1W, &u1_t_sgnl);    /* COM Tx STUB delete */
#endif
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     3/23/2020  SM       New.                                                                                               */
/*  5.1.0    12/ 8/2020  MO       Update for 800B 1A(Version update).                                                                */
/*  5.2.0     9/ 6/2021  TM       Fix Primary compile switch to ENG1G97.                                                             */
/*  5.3.0     1/ 6/2022  HU       Update for 840B 1A(Modify RW functions).                                                           */
/*  5.4.0    12/28/2023  RO       Update for 19PFv3(Version update).                                                                 */
/*                                                                                                                                   */
/*  * SM   = Shingo Miyamoto, NTTD MSE                                                                                               */
/*  * MO   = Masayuki Oofuji, NTTD MSE                                                                                               */
/*  * TM   = Tatsuya Mori, NTTD MSE                                                                                                  */
/*  * HU   = Hidekazu Usui, NTTD MSE                                                                                                 */
/*  * RO   = Ryo Oohashi, KSE                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
