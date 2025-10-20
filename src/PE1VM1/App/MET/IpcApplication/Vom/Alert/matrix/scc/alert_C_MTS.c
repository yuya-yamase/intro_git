/* 5.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert C_MTS                                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_MTS_C_MAJOR                      (5)
#define ALERT_C_MTS_C_MINOR                      (0)
#define ALERT_C_MTS_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_C_MTS_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_C_MTS.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_MTS_TT_NUM_DST                   (26U)
#define ALERT_C_MTS_PD_NUM_DST                   (32U)

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
static U4      u4_s_AlertC_mtsTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertC_mtsPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U4  u4_sp_ALERT_C_MTS_TT_CRIT[ALERT_C_MTS_TT_NUM_DST] = {
    (U4)0x00000000U,                                                           /* 00 UNKNOWN                                         */
    (U4)0x00000008U,                                                           /* 01 UNKNOWN                                         */
    (U4)0x00000010U,                                                           /* 02 UNKNOWN                                         */
    (U4)0x00000018U,                                                           /* 03 UNKNOWN                                         */
    (U4)0x00000020U,                                                           /* 04 MOGUL                                           */
    (U4)0x00000028U,                                                           /* 05 UNKNOWN                                         */
    (U4)0x00000030U,                                                           /* 06 ROCK                                            */
    (U4)0x00000038U,                                                           /* 07 UNKNOWN                                         */
    (U4)0x00000040U,                                                           /* 08 UNKNOWN                                         */
    (U4)0x00000041U,                                                           /* 09 UNKNOWN                                         */
    (U4)0x00000042U,                                                           /* 10 DIRT                                            */
    (U4)0x00000043U,                                                           /* 11 UNKNOWN                                         */
    (U4)0x00000044U,                                                           /* 12 DIRT                                            */
    (U4)0x00000045U,                                                           /* 13 MOGUL                                           */
    (U4)0x00000046U,                                                           /* 14 DIRT                                            */
    (U4)0x00000047U,                                                           /* 15 UNKNOWN                                         */
    (U4)0x00000048U,                                                           /* 16 AUTO                                            */
    (U4)0x00000050U,                                                           /* 17 MUD                                             */
    (U4)0x00000058U,                                                           /* 18 SAND                                            */
    (U4)0x00000060U,                                                           /* 19 SNOW                                            */
    (U4)0x00000068U,                                                           /* 20 UNKNOWN                                         */
    (U4)0x00000070U,                                                           /* 21 UNKNOWN                                         */
    (U4)0x00000078U,                                                           /* 22 UNKNOWN                                         */
    (U4)0x00000080U,                                                           /* 23 UNKNOWN                                         */
    (U4)0x00000100U,                                                           /* 24 UNKNOWN                                         */
    (U4)0x00000180U                                                            /* 25 UNKNOWN                                         */
};

static const U4  u4_sp_ALERT_C_MTS_TT_MASK[ALERT_C_MTS_TT_NUM_DST] = {
    (U4)0x000001F8U,                                                           /* 00 UNKNOWN                                         */
    (U4)0x000001F8U,                                                           /* 01 UNKNOWN                                         */
    (U4)0x000001F8U,                                                           /* 02 UNKNOWN                                         */
    (U4)0x000001F8U,                                                           /* 03 UNKNOWN                                         */
    (U4)0x000001F8U,                                                           /* 04 MOGUL                                           */
    (U4)0x000001F8U,                                                           /* 05 UNKNOWN                                         */
    (U4)0x000001F8U,                                                           /* 06 ROCK                                            */
    (U4)0x000001F8U,                                                           /* 07 UNKNOWN                                         */
    (U4)0x000001FFU,                                                           /* 08 UNKNOWN                                         */
    (U4)0x000001FFU,                                                           /* 09 UNKNOWN                                         */
    (U4)0x000001FFU,                                                           /* 10 DIRT                                            */
    (U4)0x000001FFU,                                                           /* 11 UNKNOWN                                         */
    (U4)0x000001FFU,                                                           /* 12 DIRT                                            */
    (U4)0x000001FFU,                                                           /* 13 MOGUL                                           */
    (U4)0x000001FFU,                                                           /* 14 DIRT                                            */
    (U4)0x000001FFU,                                                           /* 15 UNKNOWN                                         */
    (U4)0x000001F8U,                                                           /* 16 AUTO                                            */
    (U4)0x000001F8U,                                                           /* 17 MUD                                             */
    (U4)0x000001F8U,                                                           /* 18 SAND                                            */
    (U4)0x000001F8U,                                                           /* 19 SNOW                                            */
    (U4)0x000001F8U,                                                           /* 20 UNKNOWN                                         */
    (U4)0x000001F8U,                                                           /* 21 UNKNOWN                                         */
    (U4)0x000001F8U,                                                           /* 22 UNKNOWN                                         */
    (U4)0x00000180U,                                                           /* 23 UNKNOWN                                         */
    (U4)0x00000180U,                                                           /* 24 UNKNOWN                                         */
    (U4)0x00000180U                                                            /* 25 UNKNOWN                                         */
};

static const U1  u1_sp_ALERT_C_MTS_TT_DST[ALERT_C_MTS_TT_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_C_MTS_TT_MOGUL,                                              /* 04 MOGUL                                           */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_C_MTS_TT_ROCK,                                               /* 06 ROCK                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_C_MTS_TT_DIRT,                                               /* 10 DIRT                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_C_MTS_TT_DIRT,                                               /* 12 DIRT                                            */
    (U1)ALERT_REQ_C_MTS_TT_MOGUL,                                              /* 13 MOGUL                                           */
    (U1)ALERT_REQ_C_MTS_TT_DIRT,                                               /* 14 DIRT                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_C_MTS_TT_AUTO,                                               /* 16 AUTO                                            */
    (U1)ALERT_REQ_C_MTS_TT_MUD,                                                /* 17 MUD                                             */
    (U1)ALERT_REQ_C_MTS_TT_SAND,                                               /* 18 SAND                                            */
    (U1)ALERT_REQ_C_MTS_TT_SNOW,                                               /* 19 SNOW                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 20 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 21 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 22 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 23 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 24 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 25 UNKNOWN                                         */
};

static const U1  u1_sp_ALERT_C_MTS_PD_DST[ALERT_C_MTS_PD_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_C_MTS_PD_DEACT,                                              /* 04 DEACT                                           */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_C_MTS_PD_UNAVAIL,                                            /* 06 UNAVAIL                                         */
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
const ST_ALERT_MTRX st_gp_ALERT_C_MTS_MTRX[2] = {
    {
        &u4_s_AlertC_mtsTtSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_C_MTS_TT_MASK[0],                                         /* u4p_MASK                                           */
        &u4_sp_ALERT_C_MTS_TT_CRIT[0],                                         /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_MTS_TT_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_C_MTS_TT_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertC_mtsPdSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4*)vdp_PTR_NA,                                                 /* u4p_MASK                                           */
        (const U4*)vdp_PTR_NA,                                                 /* u4p_CRIT                                           */

        & u1_sp_ALERT_C_MTS_PD_DST[0],                                         /* u1p_DST                                            */
        (U2)ALERT_C_MTS_PD_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_mtsTtSrcchk      (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_VOM                                                                                                         */
/*                  u4_a_IGN_TM                                                                                                      */
/*                  u1_a_LAS                                                                                                         */
/*  Return:         u4_t_src_chk                                                                                                     */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_mtsTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if 0   /* BEV Rebase provisionally */
    static const U2 u2_s_ALERT_CH_C_MTS_TT_THRSH   = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_CH_C_MTS_TT_MSGSTS  = (U1)7U;
    static const U1 u1_s_ALERT_CH_C_MTS_TT_B_OMODE = (U1)3U;
    U4              u4_t_src_chk;
    U1              u1_t_mode_slct;
    U1              u1_t_mode_ava_info;
    U1              u1_t_msgsts;

    u1_t_msgsts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1G90,
                                   (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                   u2_s_ALERT_CH_C_MTS_TT_THRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_mode_ava_info = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_OMSINF, &u1_t_mode_ava_info);

    u1_t_mode_slct = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_OMODE, &u1_t_mode_slct);

    u4_t_src_chk  = (U4)u1_t_mode_ava_info;
    u4_t_src_chk |= ((U4)u1_t_mode_slct << u1_s_ALERT_CH_C_MTS_TT_B_OMODE);
    u4_t_src_chk |= ((U4)u1_t_msgsts    << u1_s_ALERT_CH_C_MTS_TT_MSGSTS);

    return(u4_t_src_chk);
#else   /* BEV Rebase provisionally */
    return((U4)0U);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_mtsPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_VOM                                                                                                         */
/*                  u4_a_IGN_TM                                                                                                      */
/*                  u1_a_LAS                                                                                                         */
/*  Return:         u4_t_src_chk                                                                                                     */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_mtsPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if 0   /* BEV Rebase provisionally */
    static const U2 u2_s_ALERT_CH_C_MTS_PD_THRSH   = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_CH_C_MTS_PD_MSGSTS  = (U1)3U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_msgsts;

    u1_t_msgsts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1G90,
                                   (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                   u2_s_ALERT_CH_C_MTS_PD_THRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_OMS_DISP, &u1_t_sgnl);

    u4_t_src_chk = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_CH_C_MTS_PD_MSGSTS);

    return(u4_t_src_chk);
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
/*  5.0.0    8/16/2024   YR       Newly created for 19PFv3                                                                           */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * YR   = Yhana Regalario, DTPH                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
