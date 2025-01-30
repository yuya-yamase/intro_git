/* 5.0.0*/
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert H_ZMILRQ                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_ZMILRQ_C_MAJOR                   (5)
#define ALERT_H_ZMILRQ_C_MINOR                   (0)
#define ALERT_H_ZMILRQ_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_H_ZMILRQ_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_H_ZMILRQ.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_ZMILRQ_TT_AMB_NUM_DST            (22U)
#define ALERT_H_ZMILRQ_TT_RED_NUM_DST            (22U)
#define ALERT_H_ZMILRQ_RWRN_NUM_DST              (4U)

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
static U4      u4_s_AlertH_zmilrqTtAmbSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertH_zmilrqTtRedSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertH_zmilrqRwrnSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertH_zmilrqRwrnRwTx   (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_H_ZMILRQ_TT_AMB_DST[ALERT_H_ZMILRQ_TT_AMB_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_H_ZMILRQ_TT_AMB_ON,                                          /* 01 ON                                              */
    (U1)ALERT_REQ_H_ZMILRQ_TT_AMB_ON,                                          /* 02 ON                                              */
    (U1)ALERT_REQ_H_ZMILRQ_TT_AMB_ON,                                          /* 03 ON                                              */
    (U1)ALERT_REQ_H_ZMILRQ_TT_AMB_FLSH4H,                                      /* 04 FLSH4H                                          */
    (U1)ALERT_REQ_H_ZMILRQ_TT_AMB_FLSH1H,                                      /* 05 FLSH1H                                          */
    (U1)ALERT_REQ_H_ZMILRQ_TT_AMB_ON,                                          /* 06 ON                                              */
    (U1)ALERT_REQ_H_ZMILRQ_TT_AMB_ON,                                          /* 07 ON                                              */
    (U1)ALERT_REQ_H_ZMILRQ_TT_AMB_ON,                                          /* 08 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_H_ZMILRQ_TT_AMB_ON,                                          /* 12 ON                                              */
    (U1)ALERT_REQ_H_ZMILRQ_TT_AMB_ON,                                          /* 13 ON                                              */
    (U1)ALERT_REQ_H_ZMILRQ_TT_AMB_ON,                                          /* 14 ON                                              */
    (U1)ALERT_REQ_H_ZMILRQ_TT_AMB_FLSH4H,                                      /* 15 FLSH4H                                          */
    (U1)ALERT_REQ_H_ZMILRQ_TT_AMB_FLSH1H,                                      /* 16 FLSH1H                                          */
    (U1)ALERT_REQ_H_ZMILRQ_TT_AMB_ON,                                          /* 17 ON                                              */
    (U1)ALERT_REQ_H_ZMILRQ_TT_AMB_ON,                                          /* 18 ON                                              */
    (U1)ALERT_REQ_H_ZMILRQ_TT_AMB_ON,                                          /* 19 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 20 UNKNOWN                                         */
    (U1)ALERT_REQ_H_ZMILRQ_TT_AMB_ON                                           /* 21 ON                                              */
};

static const U4  u4_sp_ALERT_H_ZMILRQ_TT_AMB_CRIT[ALERT_H_ZMILRQ_TT_AMB_NUM_DST] = {
    (U4)0x00000000U,                                                           /* 00 UNKNOWN                                         */
    (U4)0x00000001U,                                                           /* 01 ON                                              */
    (U4)0x00000002U,                                                           /* 02 ON                                              */
    (U4)0x00000003U,                                                           /* 03 ON                                              */
    (U4)0x00000004U,                                                           /* 04 FLSH4H                                          */
    (U4)0x00000005U,                                                           /* 05 FLSH1H                                          */
    (U4)0x00000006U,                                                           /* 06 ON                                              */
    (U4)0x00000007U,                                                           /* 07 ON                                              */
    (U4)0x00000008U,                                                           /* 08 ON                                              */
    (U4)0x00000010U,                                                           /* 09 UNKNOWN                                         */
    (U4)0x00000020U,                                                           /* 10 UNKNOWN                                         */
    (U4)0x00000040U,                                                           /* 11 UNKNOWN                                         */
    (U4)0x00000041U,                                                           /* 12 ON                                              */
    (U4)0x00000042U,                                                           /* 13 ON                                              */
    (U4)0x00000043U,                                                           /* 14 ON                                              */
    (U4)0x00000044U,                                                           /* 15 FLSH4H                                          */
    (U4)0x00000045U,                                                           /* 16 FLSH1H                                          */
    (U4)0x00000046U,                                                           /* 17 ON                                              */
    (U4)0x00000047U,                                                           /* 18 ON                                              */
    (U4)0x00000048U,                                                           /* 19 ON                                              */
    (U4)0x00000050U,                                                           /* 20 UNKNOWN                                         */
    (U4)0x00000060U                                                            /* 21 ON                                              */
};

static const U4  u4_sp_ALERT_H_ZMILRQ_TT_AMB_MASK[ALERT_H_ZMILRQ_TT_AMB_NUM_DST] = {
    (U4)0x0000007FU,                                                           /* 00 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 01 ON                                              */
    (U4)0x0000007FU,                                                           /* 02 ON                                              */
    (U4)0x0000007FU,                                                           /* 03 ON                                              */
    (U4)0x0000007FU,                                                           /* 04 FLSH4H                                          */
    (U4)0x0000007FU,                                                           /* 05 FLSH1H                                          */
    (U4)0x0000007FU,                                                           /* 06 ON                                              */
    (U4)0x0000007FU,                                                           /* 07 ON                                              */
    (U4)0x00000078U,                                                           /* 08 ON                                              */
    (U4)0x00000070U,                                                           /* 09 UNKNOWN                                         */
    (U4)0x00000060U,                                                           /* 10 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 11 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 12 ON                                              */
    (U4)0x0000007FU,                                                           /* 13 ON                                              */
    (U4)0x0000007FU,                                                           /* 14 ON                                              */
    (U4)0x0000007FU,                                                           /* 15 FLSH4H                                          */
    (U4)0x0000007FU,                                                           /* 16 FLSH1H                                          */
    (U4)0x0000007FU,                                                           /* 17 ON                                              */
    (U4)0x0000007FU,                                                           /* 18 ON                                              */
    (U4)0x00000078U,                                                           /* 19 ON                                              */
    (U4)0x00000070U,                                                           /* 20 UNKNOWN                                         */
    (U4)0x00000060U                                                            /* 21 ON                                              */
};

static const U1  u1_sp_ALERT_H_ZMILRQ_TT_RED_DST[ALERT_H_ZMILRQ_TT_RED_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_H_ZMILRQ_TT_RED_ON,                                          /* 01 ON                                              */
    (U1)ALERT_REQ_H_ZMILRQ_TT_RED_ON,                                          /* 02 ON                                              */
    (U1)ALERT_REQ_H_ZMILRQ_TT_RED_ON,                                          /* 03 ON                                              */
    (U1)ALERT_REQ_H_ZMILRQ_TT_RED_FLSH4H,                                      /* 04 FLSH4H                                          */
    (U1)ALERT_REQ_H_ZMILRQ_TT_RED_FLSH1H,                                      /* 05 FLSH1H                                          */
    (U1)ALERT_REQ_H_ZMILRQ_TT_RED_ON,                                          /* 06 ON                                              */
    (U1)ALERT_REQ_H_ZMILRQ_TT_RED_ON,                                          /* 07 ON                                              */
    (U1)ALERT_REQ_H_ZMILRQ_TT_RED_ON,                                          /* 08 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_H_ZMILRQ_TT_RED_ON,                                          /* 10 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_H_ZMILRQ_TT_RED_ON,                                          /* 12 ON                                              */
    (U1)ALERT_REQ_H_ZMILRQ_TT_RED_ON,                                          /* 13 ON                                              */
    (U1)ALERT_REQ_H_ZMILRQ_TT_RED_ON,                                          /* 14 ON                                              */
    (U1)ALERT_REQ_H_ZMILRQ_TT_RED_FLSH4H,                                      /* 15 FLSH4H                                          */
    (U1)ALERT_REQ_H_ZMILRQ_TT_RED_FLSH1H,                                      /* 16 FLSH1H                                          */
    (U1)ALERT_REQ_H_ZMILRQ_TT_RED_ON,                                          /* 17 ON                                              */
    (U1)ALERT_REQ_H_ZMILRQ_TT_RED_ON,                                          /* 18 ON                                              */
    (U1)ALERT_REQ_H_ZMILRQ_TT_RED_ON,                                          /* 19 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 20 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 21 UNKNOWN                                         */
};

static const U4  u4_sp_ALERT_H_ZMILRQ_TT_RED_CRIT[ALERT_H_ZMILRQ_TT_RED_NUM_DST] = {
    (U4)0x00000000U,                                                           /* 00 UNKNOWN                                         */
    (U4)0x00000001U,                                                           /* 01 ON                                              */
    (U4)0x00000002U,                                                           /* 02 ON                                              */
    (U4)0x00000003U,                                                           /* 03 ON                                              */
    (U4)0x00000004U,                                                           /* 04 FLSH4H                                          */
    (U4)0x00000005U,                                                           /* 05 FLSH1H                                          */
    (U4)0x00000006U,                                                           /* 06 ON                                              */
    (U4)0x00000007U,                                                           /* 07 ON                                              */
    (U4)0x00000008U,                                                           /* 08 ON                                              */
    (U4)0x00000010U,                                                           /* 09 UNKNOWN                                         */
    (U4)0x00000020U,                                                           /* 10 ON                                              */
    (U4)0x00000040U,                                                           /* 11 UNKNOWN                                         */
    (U4)0x00000041U,                                                           /* 12 ON                                              */
    (U4)0x00000042U,                                                           /* 13 ON                                              */
    (U4)0x00000043U,                                                           /* 14 ON                                              */
    (U4)0x00000044U,                                                           /* 15 FLSH4H                                          */
    (U4)0x00000045U,                                                           /* 16 FLSH1H                                          */
    (U4)0x00000046U,                                                           /* 17 ON                                              */
    (U4)0x00000047U,                                                           /* 18 ON                                              */
    (U4)0x00000048U,                                                           /* 19 ON                                              */
    (U4)0x00000050U,                                                           /* 20 UNKNOWN                                         */
    (U4)0x00000060U                                                            /* 21 UNKNOWN                                         */
};

static const U4  u4_sp_ALERT_H_ZMILRQ_TT_RED_MASK[ALERT_H_ZMILRQ_TT_RED_NUM_DST] = {
    (U4)0x0000007FU,                                                           /* 00 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 01 ON                                              */
    (U4)0x0000007FU,                                                           /* 02 ON                                              */
    (U4)0x0000007FU,                                                           /* 03 ON                                              */
    (U4)0x0000007FU,                                                           /* 04 FLSH4H                                          */
    (U4)0x0000007FU,                                                           /* 05 FLSH1H                                          */
    (U4)0x0000007FU,                                                           /* 06 ON                                              */
    (U4)0x0000007FU,                                                           /* 07 ON                                              */
    (U4)0x00000078U,                                                           /* 08 ON                                              */
    (U4)0x00000070U,                                                           /* 09 UNKNOWN                                         */
    (U4)0x00000060U,                                                           /* 10 ON                                              */
    (U4)0x0000007FU,                                                           /* 11 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 12 ON                                              */
    (U4)0x0000007FU,                                                           /* 13 ON                                              */
    (U4)0x0000007FU,                                                           /* 14 ON                                              */
    (U4)0x0000007FU,                                                           /* 15 FLSH4H                                          */
    (U4)0x0000007FU,                                                           /* 16 FLSH1H                                          */
    (U4)0x0000007FU,                                                           /* 17 ON                                              */
    (U4)0x0000007FU,                                                           /* 18 ON                                              */
    (U4)0x00000078U,                                                           /* 19 ON                                              */
    (U4)0x00000070U,                                                           /* 20 UNKNOWN                                         */
    (U4)0x00000060U                                                            /* 21 UNKNOWN                                         */
};

static const U1  u1_sp_ALERT_H_ZMILRQ_RWRN_DST[ALERT_H_ZMILRQ_RWRN_NUM_DST] = {
    (U1)ALERT_REQ_H_ZMILRQ_RWRN_ZESWREQ,                                       /* 00 ZESWREQ                                         */
    (U1)ALERT_REQ_H_ZMILRQ_RWRN_ZESWREQ,                                       /* 01 ZESWREQ                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_H_ZMILRQ_RWRN_ZESWREQ                                        /* 03 ZESWREQ                                         */
};

static const U4  u4_sp_ALERT_H_ZMILRQ_RWRN_CRIT[ALERT_H_ZMILRQ_RWRN_NUM_DST] = {
    (U4)0x00000002U,                                                           /* 00 ZESWREQ                                         */
    (U4)0x00000020U,                                                           /* 01 ZESWREQ                                         */
    (U4)0x00000100U,                                                           /* 02 UNKNOWN                                         */
    (U4)0x00000200U                                                            /* 03 ZESWREQ                                         */
};

static const U4  u4_sp_ALERT_H_ZMILRQ_RWRN_MASK[ALERT_H_ZMILRQ_RWRN_NUM_DST] = {
    (U4)0x0000030FU,                                                           /* 00 ZESWREQ                                         */
    (U4)0x000003F0U,                                                           /* 01 ZESWREQ                                         */
    (U4)0x00000300U,                                                           /* 02 UNKNOWN                                         */
    (U4)0x00000200U                                                            /* 03 ZESWREQ                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_H_ZMILRQ_MTRX[3] = {
    {
        &u4_s_AlertH_zmilrqTtAmbSrcchk,                                        /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_H_ZMILRQ_TT_AMB_MASK[0],                                  /* u4p_MASK                                           */
        &u4_sp_ALERT_H_ZMILRQ_TT_AMB_CRIT[0],                                  /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_ZMILRQ_TT_AMB_DST[0],                                   /* u1p_DST                                            */
        (U2)ALERT_H_ZMILRQ_TT_AMB_NUM_DST,                                     /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertH_zmilrqTtRedSrcchk,                                        /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_H_ZMILRQ_TT_RED_MASK[0],                                  /* u4p_MASK                                           */
        &u4_sp_ALERT_H_ZMILRQ_TT_RED_CRIT[0],                                  /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_ZMILRQ_TT_RED_DST[0],                                   /* u1p_DST                                            */
        (U2)ALERT_H_ZMILRQ_TT_RED_NUM_DST,                                     /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertH_zmilrqRwrnSrcchk,                                         /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertH_zmilrqRwrnRwTx,                                           /* fp_vd_XDST                                         */

        &u4_sp_ALERT_H_ZMILRQ_RWRN_MASK[0],                                    /* u4p_MASK                                           */
        &u4_sp_ALERT_H_ZMILRQ_RWRN_CRIT[0],                                    /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_ZMILRQ_RWRN_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_H_ZMILRQ_RWRN_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_zmilrqTtAmbSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_zmilrqTtAmbSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_H_ZMILRQ_TTAMB_TO_THRSH = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_H_ZMILRQ_TTAMB_LSB_MSG  = (U1)4U;
    static const U1 u1_s_ALERT_H_ZMILRQ_TTAMB_DISP_JDG = (U1)6U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U1              u1_t_disp_jdg;

    u1_t_disp_jdg = u1_g_AlertZmilrqDispJdg();

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV1S99_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_H_ZMILRQ_TTAMB_TO_THRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_EVMILRQA, &u1_t_sgnl);

    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk  |= ((U4)u1_t_msgsts << u1_s_ALERT_H_ZMILRQ_TTAMB_LSB_MSG);
    u4_t_src_chk  |= ((U4)u1_t_disp_jdg << u1_s_ALERT_H_ZMILRQ_TTAMB_DISP_JDG);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_zmilrqTtRedSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_zmilrqTtRedSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_H_ZMILRQ_TTRED_TO_THRSH = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_H_ZMILRQ_TTRED_LSB_MSG  = (U1)4U;
    static const U1 u1_s_ALERT_H_ZMILRQ_TTRED_DISP_JDG = (U1)6U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U1              u1_t_disp_jdg;

    u1_t_disp_jdg = u1_g_AlertZmilrqDispJdg();

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV1S99_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_H_ZMILRQ_TTRED_TO_THRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_EVMILRQR, &u1_t_sgnl);

    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk  |= ((U4)u1_t_msgsts << u1_s_ALERT_H_ZMILRQ_TTRED_LSB_MSG);
    u4_t_src_chk  |= ((U4)u1_t_disp_jdg << u1_s_ALERT_H_ZMILRQ_TTRED_DISP_JDG);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_zmilrqRwrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_zmilrqRwrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_H_ZMILRQ_RWRN_TO_THRSH  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_H_ZMILRQ_RWRN_LSB_AMBER = (U1)4U;
    static const U1 u1_s_ALERT_H_ZMILRQ_RWRN_LSB_MSG   = (U1)8U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl_amber;
    U1              u1_t_sgnl_red;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV1S99_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_H_ZMILRQ_RWRN_TO_THRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u1_t_sgnl_red = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_EVMILRQR, &u1_t_sgnl_red);

    u1_t_sgnl_amber = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_EVMILRQA, &u1_t_sgnl_amber);

    u4_t_src_chk  = (U4)u1_t_sgnl_red;
    u4_t_src_chk  |= ((U4)u1_t_sgnl_amber << u1_s_ALERT_H_ZMILRQ_RWRN_LSB_AMBER);
    u4_t_src_chk  |= ((U4)u1_t_msgsts << u1_s_ALERT_H_ZMILRQ_RWRN_LSB_MSG);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertH_zmilrqRwrnRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertH_zmilrqRwrnRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    static const U4 u4_s_ALERT_H_ZMILRQ_TIM_RW_ENBL = ((U4)15000U / (U4)ALERT_MAIN_TICK);
    U1              u1_t_sgnl;
    U1              u1_t_milreq_ava;

    if(((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U                             ) &&
       (u4_a_IGN_TM                       >= u4_s_ALERT_H_ZMILRQ_TIM_RW_ENBL    ) &&
       (u1_a_DST                          == (U1)ALERT_REQ_H_ZMILRQ_RWRN_ZESWREQ)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

    /*MILREQ TT and ZMILRQ TT is exclusive*/
    /*When MILREQ is Available, ZMILRQ will be Not Available*/
    u1_t_milreq_ava = u1_g_AlertEsOptAvailable(ALERT_OPT_ID_P_MILREQ_PTSYS);
    if(u1_t_milreq_ava == (U1)TRUE){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_ZESW, &u1_t_sgnl);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     7/ 8/2024  PG       Newly created for 19PFv3                                                                           */
/*                                                                                                                                   */
/*  * PG   = Patrick Garcia, DTPH                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
