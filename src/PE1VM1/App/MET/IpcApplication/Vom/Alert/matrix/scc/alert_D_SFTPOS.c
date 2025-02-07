/* 5.3.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert D_SFTPOS                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_D_SFTPOS_C_MAJOR                   (5)
#define ALERT_D_SFTPOS_C_MINOR                   (3)
#define ALERT_D_SFTPOS_C_PATCH                   (0)

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
#if (ALERT_D_SFTPOS_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_D_SFTPOS.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_D_SFTPOS_B_RJTB_NUM_DST            (32U)
#define ALERT_D_SFTPOS_B_RCVT_NUM_DST            (23U)
#define ALERT_D_SFTPOS_B_RSBW_NUM_DST            (20U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_alert_d_sftpos_tm_elpsd;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertD_sftposBRjtbSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertD_sftposBRcvtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertD_sftposBRsbwSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_D_SFTPOS_B_RJTB_DST[ALERT_D_SFTPOS_B_RJTB_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SFTPOS_B_RJTB_DBL1,                                        /* 01 DBL1                                            */
    (U1)ALERT_REQ_D_SFTPOS_B_RJTB_DBL2,                                        /* 02 DBL2                                            */
    (U1)ALERT_REQ_D_SFTPOS_B_RJTB_DBL3,                                        /* 03 DBL3                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SFTPOS_B_RJTB_DBL1,                                        /* 05 DBL1                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SFTPOS_B_RJTB_DBL1,                                        /* 07 DBL1                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SFTPOS_B_RJTB_DBL1,                                        /* 09 DBL1                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SFTPOS_B_RJTB_DBL1,                                        /* 11 DBL1                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SFTPOS_B_RJTB_DBL1,                                        /* 13 DBL1                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SFTPOS_B_RJTB_DBL1,                                        /* 15 DBL1                                            */
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

static const U4  u4_sp_ALERT_D_SFTPOS_B_RCVT_CRIT[ALERT_D_SFTPOS_B_RCVT_NUM_DST] = {
    (U4)0x00000000U,                                                           /* 00 UNKNOWN                                         */
    (U4)0x00000400U,                                                           /* 01 UNKNOWN                                         */
    (U4)0x00000600U,                                                           /* 02 UNKNOWN                                         */
    (U4)0x00000700U,                                                           /* 03 UNKNOWN                                         */
    (U4)0x00000780U,                                                           /* 04 UNKNOWN                                         */
    (U4)0x000007C0U,                                                           /* 05 UNKNOWN                                         */
    (U4)0x000007C1U,                                                           /* 06 UNKNOWN                                         */
    (U4)0x000007C2U,                                                           /* 07 CYCLE                                           */
    (U4)0x000007C3U,                                                           /* 08 UNKNOWN                                         */
    (U4)0x000007C4U,                                                           /* 09 UNKNOWN                                         */
    (U4)0x000007C5U,                                                           /* 10 UNKNOWN                                         */
    (U4)0x000007C6U,                                                           /* 11 UNKNOWN                                         */
    (U4)0x000007C7U,                                                           /* 12 UNKNOWN                                         */
    (U4)0x000007C8U,                                                           /* 13 UNKNOWN                                         */
    (U4)0x000007C9U,                                                           /* 14 UNKNOWN                                         */
    (U4)0x000007CAU,                                                           /* 15 UNKNOWN                                         */
    (U4)0x000007CBU,                                                           /* 16 UNKNOWN                                         */
    (U4)0x000007CCU,                                                           /* 17 UNKNOWN                                         */
    (U4)0x000007CDU,                                                           /* 18 UNKNOWN                                         */
    (U4)0x000007CEU,                                                           /* 19 UNKNOWN                                         */
    (U4)0x000007CFU,                                                           /* 20 UNKNOWN                                         */
    (U4)0x000007D0U,                                                           /* 21 UNKNOWN                                         */
    (U4)0x000007E0U                                                            /* 22 UNKNOWN                                         */
};

static const U4  u4_sp_ALERT_D_SFTPOS_B_RCVT_MASK[ALERT_D_SFTPOS_B_RCVT_NUM_DST] = {
    (U4)0x00000400U,                                                           /* 00 UNKNOWN                                         */
    (U4)0x00000600U,                                                           /* 01 UNKNOWN                                         */
    (U4)0x00000700U,                                                           /* 02 UNKNOWN                                         */
    (U4)0x00000780U,                                                           /* 03 UNKNOWN                                         */
    (U4)0x000007C0U,                                                           /* 04 UNKNOWN                                         */
    (U4)0x000007FFU,                                                           /* 05 UNKNOWN                                         */
    (U4)0x000007FFU,                                                           /* 06 UNKNOWN                                         */
    (U4)0x000007FFU,                                                           /* 07 CYCLE                                           */
    (U4)0x000007FFU,                                                           /* 08 UNKNOWN                                         */
    (U4)0x000007FFU,                                                           /* 09 UNKNOWN                                         */
    (U4)0x000007FFU,                                                           /* 10 UNKNOWN                                         */
    (U4)0x000007FFU,                                                           /* 11 UNKNOWN                                         */
    (U4)0x000007FFU,                                                           /* 12 UNKNOWN                                         */
    (U4)0x000007FFU,                                                           /* 13 UNKNOWN                                         */
    (U4)0x000007FFU,                                                           /* 14 UNKNOWN                                         */
    (U4)0x000007FFU,                                                           /* 15 UNKNOWN                                         */
    (U4)0x000007FFU,                                                           /* 16 UNKNOWN                                         */
    (U4)0x000007FFU,                                                           /* 17 UNKNOWN                                         */
    (U4)0x000007FFU,                                                           /* 18 UNKNOWN                                         */
    (U4)0x000007FFU,                                                           /* 19 UNKNOWN                                         */
    (U4)0x000007FFU,                                                           /* 20 UNKNOWN                                         */
    (U4)0x000007F0U,                                                           /* 21 UNKNOWN                                         */
    (U4)0x000007E0U                                                            /* 22 UNKNOWN                                         */
};

static const U1  u1_sp_ALERT_D_SFTPOS_B_RCVT_DST[ALERT_D_SFTPOS_B_RCVT_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SFTPOS_B_RCVT_CYCLE,                                       /* 07 CYCLE                                           */
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
    (U1)ALERT_REQ_UNKNOWN                                                      /* 22 UNKNOWN                                         */
};

static const U4  u4_sp_ALERT_D_SFTPOS_B_RSBW_CRIT[ALERT_D_SFTPOS_B_RSBW_NUM_DST] = {
    (U4)0x00000000U,                                                           /* 00 UNKNOWN                                         */
    (U4)0x00000080U,                                                           /* 01 UNKNOWN                                         */
    (U4)0x000000C0U,                                                           /* 02 UNKNOWN                                         */
    (U4)0x000000C1U,                                                           /* 03 UNKNOWN                                         */
    (U4)0x000000C2U,                                                           /* 04 CYCLE                                           */
    (U4)0x000000C3U,                                                           /* 05 UNKNOWN                                         */
    (U4)0x000000C4U,                                                           /* 06 UNKNOWN                                         */
    (U4)0x000000C5U,                                                           /* 07 UNKNOWN                                         */
    (U4)0x000000C6U,                                                           /* 08 UNKNOWN                                         */
    (U4)0x000000C7U,                                                           /* 09 UNKNOWN                                         */
    (U4)0x000000C8U,                                                           /* 10 UNKNOWN                                         */
    (U4)0x000000C9U,                                                           /* 11 UNKNOWN                                         */
    (U4)0x000000CAU,                                                           /* 12 UNKNOWN                                         */
    (U4)0x000000CBU,                                                           /* 13 UNKNOWN                                         */
    (U4)0x000000CCU,                                                           /* 14 UNKNOWN                                         */
    (U4)0x000000CDU,                                                           /* 15 UNKNOWN                                         */
    (U4)0x000000CEU,                                                           /* 16 UNKNOWN                                         */
    (U4)0x000000CFU,                                                           /* 17 UNKNOWN                                         */
    (U4)0x000000D0U,                                                           /* 18 UNKNOWN                                         */
    (U4)0x000000E0U                                                            /* 19 UNKNOWN                                         */
};

static const U4  u4_sp_ALERT_D_SFTPOS_B_RSBW_MASK[ALERT_D_SFTPOS_B_RSBW_NUM_DST] = {
    (U4)0x00000080U,                                                           /* 00 UNKNOWN                                         */
    (U4)0x000000C0U,                                                           /* 01 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 02 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 03 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 04 CYCLE                                           */
    (U4)0x000000FFU,                                                           /* 05 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 06 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 07 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 08 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 09 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 10 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 11 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 12 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 13 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 14 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 15 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 16 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 17 UNKNOWN                                         */
    (U4)0x000000F0U,                                                           /* 18 UNKNOWN                                         */
    (U4)0x000000E0U                                                            /* 19 UNKNOWN                                         */
};

static const U1  u1_sp_ALERT_D_SFTPOS_B_RSBW_DST[ALERT_D_SFTPOS_B_RSBW_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SFTPOS_B_RSBW_CYCLE,                                       /* 04 CYCLE                                           */
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
    (U1)ALERT_REQ_UNKNOWN                                                      /* 19 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_D_SFTPOS_MTRX[3] = {
    {
        &u4_s_AlertD_sftposBRjtbSrcchk,                                        /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_D_SFTPOS_B_RJTB_DST[0],                                   /* u1p_DST                                            */
        (U2)ALERT_D_SFTPOS_B_RJTB_NUM_DST,                                     /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertD_sftposBRcvtSrcchk,                                        /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_D_SFTPOS_B_RCVT_MASK[0],                                  /* u4p_MASK                                           */
        &u4_sp_ALERT_D_SFTPOS_B_RCVT_CRIT[0],                                  /* u4p_CRIT                                           */

        &u1_sp_ALERT_D_SFTPOS_B_RCVT_DST[0],                                   /* u1p_DST                                            */
        (U2)ALERT_D_SFTPOS_B_RCVT_NUM_DST,                                     /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertD_sftposBRsbwSrcchk,                                        /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_D_SFTPOS_B_RSBW_MASK[0],                                  /* u4p_MASK                                           */
        &u4_sp_ALERT_D_SFTPOS_B_RSBW_CRIT[0],                                  /* u4p_CRIT                                           */

        &u1_sp_ALERT_D_SFTPOS_B_RSBW_DST[0],                                   /* u1p_DST                                            */
        (U2)ALERT_D_SFTPOS_B_RSBW_NUM_DST,                                     /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertD_sftposInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertD_sftposInit(void)
{
    u4_s_alert_d_sftpos_tm_elpsd = (U4)0U;
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_sftposBRjtbSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertD_sftposBRjtbSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_D_SFTPOS_BC_LSB_ECT   = (U1)4U;
    static const U1 u1_s_ALERT_D_SFTPOS_BC_LSB_RJTB2 = (U1)1U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ECT1G92_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_POE,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;

    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_D_SFTPOS_BC_LSB_ECT);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_RJTB, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_RJTB2, &u1_t_sgnl);
    u4_t_src_chk |= ((U4)u1_t_sgnl << u1_s_ALERT_D_SFTPOS_BC_LSB_RJTB2);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_sftposBRcvtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertD_sftposBRcvtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_D_SFTPOS_TO_THRESH    = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U4 u4_s_ALERT_D_SFTPOS_TIM_ELPSD    = ((U4)300U  / (U4)ALERT_CH_TICK);
    static const U4 u4_s_ALERT_D_SFTPOS_BIT_CVT      = (U4)0x00000040U;
    static const U4 u4_s_ALERT_D_SFTPOS_BIT_ELPSD    = (U4)0x00000080U;
    static const U4 u4_s_ALERT_D_SFTPOS_BIT_PTS_ON   = (U4)0x00000100U;
    static const U4 u4_s_ALERT_D_SFTPOS_BIT_TRNSMSSN = (U4)0x00000200U;
    static const U4 u4_s_ALERT_D_SFTPOS_BIT_DEST     = (U4)0x00000400U;
    static const U4 u4_s_ALERT_D_SFTPOS_BIT_MSK      = (U4)0x0000003FU;
    static const U4 u4_s_ALERT_D_SFTPOS_BIT_MSK_SGNL = (U4)0x00000002U;
    static const U1 u1_s_ALERT_D_SFTPOS_LSB_MSGSTS   = (U1)4U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_msgsts;
    U1              u1_t_sbw;
    U1              u1_t_pts_on;
    U1              u1_t_trnsmssn;
    U1              u1_t_dest;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_SFT_MET, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ECT1G92_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_POE | (U2)OXCAN_RX_SYS_TOE_POE,
                                     u2_s_ALERT_D_SFTPOS_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_D_SFTPOS_LSB_MSGSTS);

    u1_t_sbw = u1_g_AlertShiftSbwFunc();
    if(u1_t_sbw != (U1)TRUE){
        u4_t_src_chk |= u4_s_ALERT_D_SFTPOS_BIT_CVT;
    }

    if((u4_t_src_chk & u4_s_ALERT_D_SFTPOS_BIT_MSK) != u4_s_ALERT_D_SFTPOS_BIT_MSK_SGNL){
        u4_s_alert_d_sftpos_tm_elpsd = (U4)0U;
    }
    else{
        if(u4_s_alert_d_sftpos_tm_elpsd >= u4_s_ALERT_D_SFTPOS_TIM_ELPSD){
            u4_s_alert_d_sftpos_tm_elpsd = u4_s_ALERT_D_SFTPOS_TIM_ELPSD;
            u4_t_src_chk |= u4_s_ALERT_D_SFTPOS_BIT_ELPSD;
        }
        else{
            u4_s_alert_d_sftpos_tm_elpsd++;
        }
    }

    u1_t_pts_on   = u1_g_AlertPtsOn((U1)ALERT_PTS_INV_LAS);
    if(u1_t_pts_on == (U1)TRUE){
        u4_t_src_chk              |= u4_s_ALERT_D_SFTPOS_BIT_PTS_ON;
    }

    u1_t_trnsmssn = u1_g_AlertEsOptAvailable((U2)ALERT_OPT_ID_D_SFTPOS_VARTRM1);
    if(u1_t_trnsmssn != (U1)TRUE){
        u4_t_src_chk |= u4_s_ALERT_D_SFTPOS_BIT_TRNSMSSN;
    }

    u1_t_dest = u1_g_AlertRevBzrDest();
    if(u1_t_dest == (U1)ALERT_SHIFT_BZ_REV_DEST_JPN){
        u4_t_src_chk |= u4_s_ALERT_D_SFTPOS_BIT_DEST;
    }

    return(u4_t_src_chk);
}
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_sftposBRsbwSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertD_sftposBRsbwSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_D_SFTPOS_TO_THRESH        = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U4 u4_s_ALERT_D_SFTPOS_BIT_SBW          = (U4)0x00000040U;
    static const U4 u4_s_ALERT_D_SFTPOS_BIT_INTERMITTENT = (U4)0x00000080U;
    static const U1 u1_s_ALERT_D_SFTPOS_LSB_MSGSTS       = (U1)4U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_msgsts;
    U1              u1_t_sbw;
    U4              u4_t_intermittent;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_SFT_METS, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_SBW1G01,
                                     (U2)OXCAN_RX_SYS_NRX_POE | (U2)OXCAN_RX_SYS_TOE_POE,
                                     u2_s_ALERT_D_SFTPOS_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_D_SFTPOS_LSB_MSGSTS);

    u1_t_sbw = u1_g_AlertShiftSbwFunc();
    if(u1_t_sbw == (U1)TRUE){
        u4_t_src_chk |= u4_s_ALERT_D_SFTPOS_BIT_SBW;
    }

    u4_t_intermittent = u4_g_AlertRevBzrSoundType();
    if(u4_t_intermittent == (U4)ALERT_SHIFT_BZ_REV_SOUNDTYPE_IN){
        u4_t_src_chk |= u4_s_ALERT_D_SFTPOS_BIT_INTERMITTENT;
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
/*  5.0.0     3/ 3/2020  SM       New.                                                                                               */
/*  5.1.0    12/ 8/2020  TN       Change The processing order of the CAN signal.                                                     */
/*  5.2.0     1/19/2022  RI       Add CH for PD.                                                                                     */
/*  5.2.1     5/26/2022  HU       Fix QAC Warning(Empty if Statement).                                                               */
/*  5.2.2     1/24/2023  SS       Update for 345D 1A(Version update).                                                                */
/*  5.3.3    12/19/2023  GM       Update for 19PFv3 CV              .                                                                */
/*                                                                                                                                   */
/*  * SM   = Shingo Miyamoto, NTTD MSE                                                                                               */
/*  * TN   = Toshiaki Nagashima, NTTD MSE                                                                                            */
/*  * RI   = Ren Ito, NTTD MSE                                                                                                       */
/*  * HU   = Hidekazu Usui, NTTD MSE                                                                                                 */
/*  * SS   = Shuji Suzuki, NTTD MSE                                                                                                  */
/*  * GM   = Glen Monteposo, DTPH                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
