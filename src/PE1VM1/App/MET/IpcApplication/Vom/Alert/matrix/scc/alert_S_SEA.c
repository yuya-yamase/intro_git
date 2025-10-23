/* 5.7.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert S_SEA                                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_SEA_C_MAJOR                      (5)
#define ALERT_S_SEA_C_MINOR                      (7)
#define ALERT_S_SEA_C_PATCH                      (0)

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
#if (ALERT_S_SEA_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_S_SEA.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_SEA_BC_NUM_DST                   (64U)
#define ALERT_S_SEA_PD_NUM_DST                   (32U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_alert_s_sea_msgsts_doa_buz;
static U1      u1_s_alert_s_sea_msgsts_doam_msg;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertS_seaBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertS_seaPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_S_SEA_BC_DST[ALERT_S_SEA_BC_NUM_DST] = {
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
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 31 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 32 UNKNOWN                                         */
    (U1)ALERT_REQ_S_SEA_BC_DOUBLE,                                             /* 33 DOUBLE                                          */
    (U1)ALERT_REQ_S_SEA_BC_CYCLE,                                              /* 34 CYCLE                                           */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 35 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 36 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 37 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 38 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 39 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 40 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 41 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 42 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 43 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 44 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 45 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 46 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 47 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 48 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 49 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 50 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 51 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 52 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 53 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 54 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 55 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 56 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 57 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 58 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 59 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 60 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 61 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 62 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 63 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_S_SEA_PD_DST[ALERT_S_SEA_PD_NUM_DST] = {
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
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 16 UNKNOWN                                         */
    (U1)ALERT_REQ_S_SEA_PD_SEASTOP,                                            /* 17 SEASTOP                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 18 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 19 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 20 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 21 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 22 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 23 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 24 UNKNOWN                                         */
    (U1)ALERT_REQ_S_SEA_PD_SEASTOP,                                            /* 25 SEASTOP                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 26 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 27 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 28 UNKNOWN                                         */
    (U1)ALERT_REQ_S_SEA_PD_SEASTOP,                                            /* 29 SEASTOP                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 30 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 31 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_S_SEA_MTRX[2] = {
    {
        &u4_s_AlertS_seaBcSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_SEA_BC_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_S_SEA_BC_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertS_seaPdSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_SEA_PD_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_S_SEA_PD_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertS_seaInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertS_seaInit(void)
{
    u1_s_alert_s_sea_msgsts_doa_buz  = (U1)COM_NO_RX;
    u1_s_alert_s_sea_msgsts_doam_msg = (U1)COM_NO_RX;
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_seaBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_seaBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if 0   /* BEV Rebase provisionally */
    static const U2 u2_s_ALERT_S_SEA_BC_TO_THRESH  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_S_SEA_BC_LSB_MSGSTS = (U1)3U;
    static const U4 u4_s_ALERT_S_SEA_BC_BIT_BAT_WT = (U4)0x00000020U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_DOA_BUZ, &u1_t_sgnl);

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_BSR1S01,
                                     (U2)OXCAN_RX_SYS_NRX_PBA | (U2)OXCAN_RX_SYS_TOE_PBA,
                                     u2_s_ALERT_S_SEA_BC_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    vd_g_AlertBRxTrnsSts(&u1_s_alert_s_sea_msgsts_doa_buz, u1_t_msgsts);

    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_s_alert_s_sea_msgsts_doa_buz << u1_s_ALERT_S_SEA_BC_LSB_MSGSTS);

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_S_SEA_BC_BIT_BAT_WT;
    }

    return(u4_t_src_chk);
#else   /* BEV Rebase provisionally */
    return((U4)0U);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_seaPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_seaPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if 0   /* BEV Rebase provisionally */
    static const U2 u2_s_ALERT_S_SEA_PD_TO_THRESH  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_S_SEA_PD_LSB_MSGSTS = (U1)1U;
    static const U4 u4_s_ALERT_S_SEA_PD_BIT_IGN_ON = (U4)0x00000008U;
    static const U4 u4_s_ALERT_S_SEA_PD_BIT_BAT_WT = (U4)0x00000010U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_DOAM_MSG, &u1_t_sgnl);

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_BSR1S02,
                                     (U2)OXCAN_RX_SYS_NRX_PBA | (U2)OXCAN_RX_SYS_TOE_PBA,
                                     u2_s_ALERT_S_SEA_PD_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    vd_g_AlertBRxTrnsSts(&u1_s_alert_s_sea_msgsts_doam_msg, u1_t_msgsts);

    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_s_alert_s_sea_msgsts_doam_msg << u1_s_ALERT_S_SEA_PD_LSB_MSGSTS);

    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_S_SEA_PD_BIT_IGN_ON;
    }

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_S_SEA_PD_BIT_BAT_WT;
    }

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
/*  5.0.0     3/24/2020  ZS       New.                                                                                               */
/*  5.1.0     6/ 1/2020  DS       Fix u1_sp_ALERT_S_DOA_BC_DST table.                                                                */
/*  5.2.0     9/ 7/2020  TI       Change filename and power state for PD.                                                            */
/*  5.3.0    10/ 1/2020  ZS       Fix timeout timer spec and Index table for PD.                                                     */
/*  5.4.0    12/10/2020  MO       Add BA_PDC data for PD.                                                                            */
/*  5.4.1    12/14/2020  KT       Update for 032D CV(Version update).                                                                */
/*  5.5.0     6/ 1/2021  SO       Change disp time (3000ms->7000ms).                                                                 */
/*  5.5.1     6/30/2021  TN       Update for 050D CV(Version update).                                                                */
/*  5.6.0     8/13/2021  MO       Change dlytimer thresh.                                                                            */
/*  5.6.1     6/28/2022  YN       Update for 840B#2 1A(Version update).                                                              */
/*  5.7.0     1/09/2024  RO       Update for 19PFv3.                                                                                 */
/*                                                                                                                                   */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * DS   = Daisuke Suzuki, NTTD MSE                                                                                                */
/*  * TI   = Takuro Iwanaga, NTTD MSE                                                                                                */
/*  * MO   = Masayuki Oofuji, NTTD MSE                                                                                               */
/*  * KT   = Kenichi Takahashi, NTTD MSE                                                                                             */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*  * TN   = Toshiaki Nagashima, NTTD MSE                                                                                            */
/*  * YN   = Yuma Nagahara, NTTD MSE                                                                                                 */
/*  * RO   = Ryo Oohashi, KSE                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
