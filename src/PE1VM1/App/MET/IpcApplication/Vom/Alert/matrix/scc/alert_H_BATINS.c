/* 5.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert H_BATINS                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_BATINS_C_MAJOR                   (5)
#define ALERT_H_BATINS_C_MINOR                   (4)
#define ALERT_H_BATINS_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_H_BATINS_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_H_BATINS.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_BATINS_BC_NUM_DST                (32U)
#define ALERT_H_BATINS_PD_NUM_DST                (16U)

#define ALERT_H_BATINS_RWSGNL_BAT1               (0U)
#define ALERT_H_BATINS_RWSGNL_BAT2               (1U)
#define ALERT_H_BATINS_RWSGNL_BAT3               (2U)

#define ALERT_H_BATINS_NUM_RWSGNL                (3U)

#define ALERT_H_BATINS_RWT_IG                    (0x10U)

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
static U4      u4_s_AlertH_batinsBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertH_batinsPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertH_batinsPdRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_H_BATINS_BC_DST[ALERT_H_BATINS_BC_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_H_BATINS_BC_CYCL,                                            /* 05 CYCL                                            */
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
static const U1  u1_sp_ALERT_H_BATINS_PD_DST[ALERT_H_BATINS_PD_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_H_BATINS_PD_REQINSPECT,                                      /* 02 REQINSPECT                                      */
    (U1)ALERT_REQ_H_BATINS_PD_DIAGNOSIS,                                       /* 03 DIAGNOSIS                                       */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_H_BATINS_PD_EMERGENCY,                                       /* 05 EMERGENCY                                       */
    (U1)ALERT_REQ_H_BATINS_PD_UNAVAILABL,                                      /* 06 UNAVAILABL                                      */
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

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_H_BATINS_MTRX[2] = {
    {
        &u4_s_AlertH_batinsBcSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_BATINS_BC_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_H_BATINS_BC_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertH_batinsPdSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertH_batinsPdRwTx,                                             /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_BATINS_PD_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_H_BATINS_PD_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_batinsBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_batinsBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_H_BATINS_THRSH_TO  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_H_BATINS_BC_MSGSTS = (U1)3U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_BS_CHK_B, &u1_t_sgnl);

    u4_t_src_chk  = (U4)u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_BAT1S01_CH0,
                                      (U4)OXCAN_SYS_IGR | (U4)OXCAN_SYS_IGP,
                                      u2_s_ALERT_H_BATINS_THRSH_TO) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_H_BATINS_BC_MSGSTS);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_batinsPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_batinsPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_H_BATINS_PD_MSGSTS = (U1)3U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_BS_CHK_B, &u1_t_sgnl);

    u4_t_src_chk  = (U4)u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_BAT1S01_CH0,
                                      (U4)OXCAN_SYS_IGR | (U4)OXCAN_SYS_IGP,
                                      (U2)U2_MAX) & (U1)COM_NO_RX;

    u4_t_src_chk    |= ((U4)u1_t_msgsts << u1_s_ALERT_H_BATINS_PD_MSGSTS);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertH_batinsPdRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertH_batinsPdRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
#if 0   /* BEV Rebase provisionally */
    static const U4 u4_s_ALERT_H_BATINS_RWT_THRESH = ((U4)15000U / (U4)ALERT_MAIN_TICK);

    static const U1 u1_sp_ALERT_H_BATINS_RWTX_CRT[ALERT_H_BATINS_NUM_RWSGNL] = {
        ((U1)ALERT_VOM_RWT_EN      | (U1)((U1)1U << ALERT_REQ_H_BATINS_PD_REQINSPECT)),
        ((U1)ALERT_VOM_RWT_EN      | (U1)((U1)1U << ALERT_REQ_H_BATINS_PD_EMERGENCY)),
        ((U1)ALERT_H_BATINS_RWT_IG | (U1)((U1)1U << ALERT_REQ_H_BATINS_PD_UNAVAILABL))
    };

    U1              u1_tp_sgnl[ALERT_H_BATINS_NUM_RWSGNL];
    U1              u1_t_rw;
    U4              u4_t_idx;

    u1_t_rw  = (U1)0U;
    if(u1_a_DST != (U1)ALERT_REQ_UNKNOWN){
        u1_t_rw = ((U1)1U << u1_a_DST);
        if(u4_a_IGN_TM >= u4_s_ALERT_H_BATINS_RWT_THRESH){
            u1_t_rw |= (U1)ALERT_H_BATINS_RWT_IG;
        }
    }
    u1_t_rw |= (u1_a_VOM & (U1)ALERT_VOM_RWT_EN);

    for(u4_t_idx = (U4)0U; u4_t_idx < (U4)ALERT_H_BATINS_NUM_RWSGNL; u4_t_idx++){
        if((u1_t_rw & u1_sp_ALERT_H_BATINS_RWTX_CRT[u4_t_idx]) == u1_sp_ALERT_H_BATINS_RWTX_CRT[u4_t_idx]){
            u1_tp_sgnl[u4_t_idx] = (U1)ALERT_RW_SGNL_ON;
        }
        else{
            u1_tp_sgnl[u4_t_idx] = (U1)ALERT_RW_SGNL_OFF;
        }
    }

    (void)Com_SendSignal(ComConf_ComSignal_BAT1, &u1_tp_sgnl[ALERT_H_BATINS_RWSGNL_BAT1]);
    (void)Com_SendSignal(ComConf_ComSignal_BAT2, &u1_tp_sgnl[ALERT_H_BATINS_RWSGNL_BAT2]);
    (void)Com_SendSignal(ComConf_ComSignal_BAT3, &u1_tp_sgnl[ALERT_H_BATINS_RWSGNL_BAT3]);
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
/*  5.0.0     6/27/2019  ZS       New.                                                                                               */
/*  5.1.0     8/ 8/2019  ZS       Add remote warning.                                                                                */
/*  5.1.1    10/10/2019  TH       modify rw criteria                                                                                 */
/*  5.1.2    12/16/2019  ZS       Fix QAC Warning.                                                                                   */
/*  5.2.0     3/24/2020  TI       Change to filename of 800B.                                                                        */
/*  5.3.0    12/ 8/2020  TN       Update for 800B 1A(Version update).                                                                */
/*  5.3.1     2/22/2022  TM       Fix static code analysis error.                                                                    */
/*  5.4.0     1/17/2024  KH       Update for 19PFv3 CV.                                                                              */
/*                                                                                                                                   */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * TH   = Takuya Hiraide, NTTD MSE                                                                                                */
/*  * TI   = Takuro Iwanaga, NTTD MSE                                                                                                */
/*  * TN   = Toshiaki Nagashima, NTTD MSE                                                                                            */
/*  * MY   = Masaki Yoshizawa, NTTD MSE                                                                                              */
/*  * KH   = Kiko Huerte, DTPH                                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/
