/* 5.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert S_ISA                                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_ISA_C_MAJOR                      (5)
#define ALERT_S_ISA_C_MINOR                      (4)
#define ALERT_S_ISA_C_PATCH                      (0)

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
#if (ALERT_S_ISA_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_S_ISA.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_ISA_TT_NUM_DST                   (16U)
#define ALERT_S_ISA_PD_NUM_DST                   (4U)

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
static U4      u4_s_AlertS_isaTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertS_isaPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertS_isaPdRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_S_ISA_TT_DST[ALERT_S_ISA_TT_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_ISA_TT_ON_W,                                               /* 01 ON_W                                            */
    (U1)ALERT_REQ_S_ISA_TT_ON_G,                                               /* 02 ON_G                                            */
    (U1)ALERT_REQ_S_ISA_TT_ON_A,                                               /* 03 ON_A                                            */
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
static const U4  u4_sp_ALERT_S_ISA_PD_CRIT[ALERT_S_ISA_PD_NUM_DST] = {
    (U4)0x00000003U,                                                           /* 00 RW                                              */
    (U4)0x00000006U,                                                           /* 01 RW                                              */
    (U4)0x00000019U,                                                           /* 02 MALFUNC                                         */
    (U4)0x0000001AU                                                            /* 03 UNAVLBL                                         */
};
static const U4  u4_sp_ALERT_S_ISA_PD_MASK[ALERT_S_ISA_PD_NUM_DST] = {
    (U4)0x0000007FU,                                                           /* 00 RW                                              */
    (U4)0x0000007FU,                                                           /* 01 RW                                              */
    (U4)0x0000007FU,                                                           /* 02 MALFUNC                                         */
    (U4)0x0000007FU                                                            /* 03 UNAVLBL                                         */
};
static const U1  u1_sp_ALERT_S_ISA_PD_DST[ALERT_S_ISA_PD_NUM_DST] = {
    (U1)ALERT_REQ_S_ISA_PD_RW,                                                 /* 00 RW                                              */
    (U1)ALERT_REQ_S_ISA_PD_RW,                                                 /* 01 RW                                              */
    (U1)ALERT_REQ_S_ISA_PD_MALFUNC,                                            /* 02 MALFUNC                                         */
    (U1)ALERT_REQ_S_ISA_PD_UNAVLBL                                             /* 03 UNAVLBL                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_S_ISA_MTRX[2] = {
    {
        &u4_s_AlertS_isaTtSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_ISA_TT_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_S_ISA_TT_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertS_isaPdSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertS_isaPdRwTx,                                                /* fp_vd_XDST                                         */

        &u4_sp_ALERT_S_ISA_PD_MASK[0],                                         /* u4p_MASK                                           */
        &u4_sp_ALERT_S_ISA_PD_CRIT[0],                                         /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_ISA_PD_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_S_ISA_PD_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_isaTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_isaTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_S_ISA_TT_LSB_MSGSTS = (U1)2U;
    static const U2 u2_s_ALERT_S_ISA_TT_THRSH_TO   = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_FCM1S39_CH0,
                                     (U4)OXCAN_SYS_IGR,
                                     u2_s_ALERT_S_ISA_TT_THRSH_TO) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
#if defined(ComConf_ComSignal_ISAID)
    (void)Com_ReceiveSignal(ComConf_ComSignal_ISAID, &u1_t_sgnl);
#endif /* defined(ComConf_ComSignal_ISAID) */
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_S_ISA_TT_LSB_MSGSTS);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_isaPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_isaPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_S_ISA_PD_LSB_MSGSTS = (U1)5U;
    static const U2 u2_s_ALERT_S_ISA_PD_THRSH_TO   = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_FCM1S40_CH0,
                                     (U4)OXCAN_SYS_IGR,
                                     u2_s_ALERT_S_ISA_PD_THRSH_TO) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
#if defined(ComConf_ComSignal_ACCMSG3)
    (void)Com_ReceiveSignal(ComConf_ComSignal_ACCMSG3, &u1_t_sgnl);
#endif /* defined(ComConf_ComSignal_ACCMSG3) */
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_S_ISA_PD_LSB_MSGSTS);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertS_isaPdRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertS_isaPdRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
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
/*  5.0.0     2/26/2020  SM       New.                                                                                               */
/*  5.1.0    12/ 8/2020  SO       Update for 800B 1A(Version update).                                                                */
/*  5.1.1     3/25/2021  SO       Update for 840B CV(Version update).                                                                */
/*  5.1.2     8/23/2021  TM       Add Compile switch.                                                                                */
/*  5.2.0    10/25/2021  HU       Update for 840B 1A(Version update).                                                                */
/*  5.3.0     4/ 5/2024  AA       Added remote warning handling (C_CW)                                                               */
/*  5.4.0     6/17/2024  AA       Added communication interrupt process in u4_s_AlertS_isaTtSrcchk                                   */
/*                                                                                                                                   */
/*  * SM   = Shingo Miyamoto, NTTD MSE                                                                                               */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*  * TM   = Tatsuya Mori, NTTD MSE                                                                                                  */
/*  * HU   = Hidekazu Usui, NTTD MSE                                                                                                 */
/*  * AA   = Anna Asuncion, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
