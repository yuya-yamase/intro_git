/* 5.6.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert S_CCS                                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_CCS_C_MAJOR                      (5)
#define ALERT_S_CCS_C_MINOR                      (6)
#define ALERT_S_CCS_C_PATCH                      (0)

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
#if (ALERT_S_CCS_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_S_CCS.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_CCS_TT_CC_NUM_DST                (8U)
#define ALERT_S_CCS_PD_NUM_DST                   (14U)

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
static U4      u4_s_AlertS_ccsTtCcSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertS_ccsPdSrcchk   (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertS_ccsPdRwTx     (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_S_CCS_TT_CC_DST[ALERT_S_CCS_TT_CC_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_CCS_TT_CC_ON_W_G,                                          /* 01 ON_W_G                                          */
    (U1)ALERT_REQ_S_CCS_TT_CC_ON_G,                                            /* 02 ON_G                                            */
    (U1)ALERT_REQ_S_CCS_TT_CC_ON_Y,                                            /* 03 ON_Y                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 07 UNKNOWN                                         */
};
static const U4  u4_sp_ALERT_S_CCS_PD_CRIT[ALERT_S_CCS_PD_NUM_DST] = {
    (U4)0x00000060U,                                                           /* 00 UNKNOWN_RW                                      */
    (U4)0x000000C0U,                                                           /* 01 UNKNOWN_RW                                      */
    (U4)0x00000001U,                                                           /* 02 MLFNC                                           */
    (U4)0x00000062U,                                                           /* 03 DSBL_RW                                         */
    (U4)0x000000C2U,                                                           /* 04 DSBL_RW                                         */
    (U4)0x00000002U,                                                           /* 05 DSBL                                            */
    (U4)0x00000063U,                                                           /* 06 UNKNOWN_RW                                      */
    (U4)0x000000C3U,                                                           /* 07 UNKNOWN_RW                                      */
    (U4)0x00000068U,                                                           /* 08 UNKNOWN_RW                                      */
    (U4)0x000000C8U,                                                           /* 09 UNKNOWN_RW                                      */
    (U4)0x00000064U,                                                           /* 10 UNKNOWN_RW                                      */
    (U4)0x000000C4U,                                                           /* 11 UNKNOWN_RW                                      */
    (U4)0x00000070U,                                                           /* 12 UNKNOWN_RW                                      */
    (U4)0x000000D0U                                                            /* 13 UNKNOWN_RW                                      */
};
static const U4  u4_sp_ALERT_S_CCS_PD_MASK[ALERT_S_CCS_PD_NUM_DST] = {
    (U4)0x00000FFFU,                                                           /* 00 UNKNOWN_RW                                      */
    (U4)0x00000FFFU,                                                           /* 01 UNKNOWN_RW                                      */
    (U4)0x0000001FU,                                                           /* 02 MLFNC                                           */
    (U4)0x00000FFFU,                                                           /* 03 DSBL_RW                                         */
    (U4)0x00000FFFU,                                                           /* 04 DSBL_RW                                         */
    (U4)0x0000001FU,                                                           /* 05 DSBL                                            */
    (U4)0x00000FF3U,                                                           /* 06 UNKNOWN_RW                                      */
    (U4)0x00000FF3U,                                                           /* 07 UNKNOWN_RW                                      */
    (U4)0x00000FF8U,                                                           /* 08 UNKNOWN_RW                                      */
    (U4)0x00000FF8U,                                                           /* 09 UNKNOWN_RW                                      */
    (U4)0x00000FF4U,                                                           /* 10 UNKNOWN_RW                                      */
    (U4)0x00000FF4U,                                                           /* 11 UNKNOWN_RW                                      */
    (U4)0x00000FF0U,                                                           /* 12 UNKNOWN_RW                                      */
    (U4)0x00000FF0U                                                            /* 13 UNKNOWN_RW                                      */
};
static const U1  u1_sp_ALERT_S_CCS_PD_DST[ALERT_S_CCS_PD_NUM_DST] = {
    (U1)ALERT_REQ_S_CCS_PD_UNKNOWN_RW,                                         /* 00 UNKNOWN_RW                                      */
    (U1)ALERT_REQ_S_CCS_PD_UNKNOWN_RW,                                         /* 01 UNKNOWN_RW                                      */
    (U1)ALERT_REQ_S_CCS_PD_MLFNC,                                              /* 02 MLFNC                                           */
    (U1)ALERT_REQ_S_CCS_PD_DSBL_RW,                                            /* 03 DSBL_RW                                         */
    (U1)ALERT_REQ_S_CCS_PD_DSBL_RW,                                            /* 04 DSBL_RW                                         */
    (U1)ALERT_REQ_S_CCS_PD_DSBL,                                               /* 05 DSBL                                            */
    (U1)ALERT_REQ_S_CCS_PD_UNKNOWN_RW,                                         /* 06 UNKNOWN_RW                                      */
    (U1)ALERT_REQ_S_CCS_PD_UNKNOWN_RW,                                         /* 07 UNKNOWN_RW                                      */
    (U1)ALERT_REQ_S_CCS_PD_UNKNOWN_RW,                                         /* 08 UNKNOWN_RW                                      */
    (U1)ALERT_REQ_S_CCS_PD_UNKNOWN_RW,                                         /* 09 UNKNOWN_RW                                      */
    (U1)ALERT_REQ_S_CCS_PD_UNKNOWN_RW,                                         /* 10 UNKNOWN_RW                                      */
    (U1)ALERT_REQ_S_CCS_PD_UNKNOWN_RW,                                         /* 11 UNKNOWN_RW                                      */
    (U1)ALERT_REQ_S_CCS_PD_UNKNOWN_RW,                                         /* 12 UNKNOWN_RW                                      */
    (U1)ALERT_REQ_S_CCS_PD_UNKNOWN_RW                                          /* 13 UNKNOWN_RW                                      */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_S_CCS_MTRX[2] = {
    {
        &u4_s_AlertS_ccsTtCcSrcchk,                                            /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u1_sp_ALERT_S_CCS_TT_CC_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_S_CCS_TT_CC_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertS_ccsPdSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertS_ccsPdRwTx,                                                /* fp_vd_XDST                                         */

        &u4_sp_ALERT_S_CCS_PD_MASK[0],                                         /* u4p_MASK                                           */
        &u4_sp_ALERT_S_CCS_PD_CRIT[0],                                         /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_CCS_PD_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_S_CCS_PD_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_ccsTtCcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_ccsTtCcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_CCIND_LSB_MSGSTS = (U1)2U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_PDU_RX_CAN_EHV1G40,
                                     (U4)OXCAN_SYS_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;

    u1_t_sgnl     = (U1)0U;
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_CCIND, &u1_t_sgnl);
#endif
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_CCIND_LSB_MSGSTS);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_ccsPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_ccsPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_FCM1S40_TO_THRESH  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_CCMSG_LSB_MSGSTS   = (U1)4U;
    static const U1 u1_s_ALERT_ACCMSG3_LSB_VALUE  = (U1)5U;
    static const U1 u1_s_ALERT_ACCMSG3_LSB_MSGSTS = (U1)10U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_PDU_RX_CAN_EHV1G40,
                                     (U4)OXCAN_SYS_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;

    u1_t_sgnl     = (U1)0U;
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_CCMSG, &u1_t_sgnl);
#endif
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_CCMSG_LSB_MSGSTS);

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_FCM1S40_CH0,
                                     (U4)OXCAN_SYS_IGR,
                                     u2_s_ALERT_FCM1S40_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

     u1_t_sgnl    = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_ACCMSG3, &u1_t_sgnl);
    u4_t_src_chk |= ((U4)u1_t_sgnl   << u1_s_ALERT_ACCMSG3_LSB_VALUE);

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_ACCMSG3_LSB_MSGSTS);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertS_ccsPdRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertS_ccsPdRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    /* C_CW is handled in alert_S_ACC */
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     3/13/2020  SK       New.                                                                                               */
/*  5.1.0     9/ 4/2020  MO       Added Req for u1_sp_ALERT_S_CCS_TT_CC_DST.                                                         */
/*  5.2.0    12/ 8/2020  SO       Update for 800B 1A(Version update).                                                                */
/*  5.3.0     3/29/2021  SM       Update for 900B CV(Version update).                                                                */
/*  5.3.1     6/30/2021  TN       Update for 050D CV(Version update).                                                                */
/*  5.4.0    11/07/2023  RO       Update for 19PFv3(Version update).                                                                 */
/*  5.5.0    01/26/2024  DR       Update for 19PFv3(removed SET TT).                                                                 */
/*  5.6.0    04/12/2024  AA       Removed remote warning process   .                                                                 */
/*                                                                                                                                   */
/*  * SK   = Satoshi Kasai, NTTD MSE                                                                                                 */
/*  * MO   = Masaya Ozawa, NTTD MSE                                                                                                  */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*  * SM   = Shingo Miyamoto, NTTD MSE                                                                                               */
/*  * TN   = Toshiaki Nagashima, NTTD MSE                                                                                            */
/*  * RO   = Ryo Oohashi, KSE                                                                                                        */
/*  * DR   = Dyan Reyes, DTPH                                                                                                        */
/*  * AA   = Anna Asuncion, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
