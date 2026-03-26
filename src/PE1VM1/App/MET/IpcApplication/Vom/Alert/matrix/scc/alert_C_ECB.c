/* 5.7.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert C_ECB                                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_ECB_C_MAJOR                      (5)
#define ALERT_C_ECB_C_MINOR                      (7)
#define ALERT_C_ECB_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_C_ECB_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_C_ECB.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_ECB_TT_NUM_DST                   (32U)
#define ALERT_C_ECB_PD_NUM_DST                   (8U)

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
static U4      u4_s_AlertC_ecbTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertC_ecbPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_C_ECB_TT_DST[ALERT_C_ECB_TT_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_C_ECB_TT_TESTMODE,                                           /* 01 TESTMODE                                        */
    (U1)ALERT_REQ_C_ECB_TT_LEARNING1,                                          /* 02 LEARNING1                                       */
    (U1)ALERT_REQ_C_ECB_TT_LEARNING2,                                          /* 03 LEARNING2                                       */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_C_ECB_TT_MALFUNC,                                            /* 06 MALFUNC                                         */
    (U1)ALERT_REQ_C_ECB_TT_UNAVAILABLE,                                        /* 07 UNAVAILABLE                                     */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_C_ECB_TT_MALFUNC,                                            /* 16 MALFUNC                                         */
    (U1)ALERT_REQ_C_ECB_TT_MALFUNC,                                            /* 17 MALFUNC                                         */
    (U1)ALERT_REQ_C_ECB_TT_MALFUNC,                                            /* 18 MALFUNC                                         */
    (U1)ALERT_REQ_C_ECB_TT_MALFUNC,                                            /* 19 MALFUNC                                         */
    (U1)ALERT_REQ_C_ECB_TT_MALFUNC,                                            /* 20 MALFUNC                                         */
    (U1)ALERT_REQ_C_ECB_TT_MALFUNC,                                            /* 21 MALFUNC                                         */
    (U1)ALERT_REQ_C_ECB_TT_MALFUNC,                                            /* 22 MALFUNC                                         */
    (U1)ALERT_REQ_C_ECB_TT_MALFUNC,                                            /* 23 MALFUNC                                         */
    (U1)ALERT_REQ_C_ECB_TT_MALFUNC,                                            /* 24 MALFUNC                                         */
    (U1)ALERT_REQ_C_ECB_TT_MALFUNC,                                            /* 25 MALFUNC                                         */
    (U1)ALERT_REQ_C_ECB_TT_MALFUNC,                                            /* 26 MALFUNC                                         */
    (U1)ALERT_REQ_C_ECB_TT_MALFUNC,                                            /* 27 MALFUNC                                         */
    (U1)ALERT_REQ_C_ECB_TT_MALFUNC,                                            /* 28 MALFUNC                                         */
    (U1)ALERT_REQ_C_ECB_TT_MALFUNC,                                            /* 29 MALFUNC                                         */
    (U1)ALERT_REQ_C_ECB_TT_MALFUNC,                                            /* 30 MALFUNC                                         */
    (U1)ALERT_REQ_C_ECB_TT_MALFUNC                                             /* 31 MALFUNC                                         */
};
static const U1  u1_sp_ALERT_C_ECB_PD_DST[ALERT_C_ECB_PD_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_C_ECB_PD_FAILDISP,                                           /* 01 FAILDISP                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_C_ECB_PD_FAILDISP,                                           /* 04 FAILDISP                                        */
    (U1)ALERT_REQ_C_ECB_PD_FAILDISP,                                           /* 05 FAILDISP                                        */
    (U1)ALERT_REQ_C_ECB_PD_FAILDISP,                                           /* 06 FAILDISP                                        */
    (U1)ALERT_REQ_C_ECB_PD_FAILDISP                                            /* 07 FAILDISP                                        */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_C_ECB_MTRX[2] = {
    {
        &u4_s_AlertC_ecbTtSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_ECB_TT_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_C_ECB_TT_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertC_ecbPdSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_ECB_PD_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_C_ECB_PD_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_ecbTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_VOM                                                                                                         */
/*                  u4_a_IGN_TM                                                                                                      */
/*                  u1_a_LAS                                                                                                         */
/*  Return:         u4_t_src_chk                                                                                                     */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_ecbTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_C_ECB_TT_TO_THRESH   = ((U2)1000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_C_ECB_TT_LSB_B_EBW   = (U1)3U;

    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_DDM1S17_CH0,
                                    (U4)OXCAN_SYS_IGR | (U4)OXCAN_SYS_IGP,
                                    u2_s_ALERT_C_ECB_TT_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_EBW, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_C_ECB_TT_LSB_B_EBW);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_ecbPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_VOM                                                                                                         */
/*                  u4_a_IGN_TM                                                                                                      */
/*                  u1_a_LAS                                                                                                         */
/*  Return:         u4_t_src_chk                                                                                                     */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_ecbPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_C_ECB_PD_TO_THRESH    = ((U2)1000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_C_ECB_PD_LSB_EBW_MID  = (U1)1U;

    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_msgsts = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_DDM1S17_CH0,
                                    (U4)OXCAN_SYS_IGR | (U4)OXCAN_SYS_IGP,
                                    u2_s_ALERT_C_ECB_PD_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_EBW_MID, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_C_ECB_PD_LSB_EBW_MID);

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
/*  5.0.0     3/24/2020  ZS       New.                                                                                               */
/*  5.1.0     5/19/2020  ZS       Fix u1_sp_ALERT_C_ECB_TT_JDG Table.                                                                */
/*  5.2.0     5/25/2020  ZS       Fix remote warning signal EPBW -> ECBW.                                                            */
/*  5.3.0     6/ 1/2020  ZS       Fix mid_jdg and mid2_jdg bit shift value.                                                          */
/*  5.4.0     8/25/2020  KT       Removed communication disruption verdicts below 10.0v.                                             */
/*  5.4.1     7/ 1/2021  SO       Update for 050D CV(Version update).                                                                */
/*  5.4.2     1/19/2022  HU       Update for 840B #2 CV(Version update).                                                             */
/*  5.5.0     11/25/2024 KO       Change for BEV System_Consideration_1.                                                             */
/*  5.6.0     1/13/2026  HT       Change for Full_function2 (MET-M_REMWAR-CSTD-2-04-A-C0)                                            */
/*                                Removed "ALERT_REQ" in order to transfer signal transmission control from the MCU to the SoC       */
/*  5.7.0     3/16/2026  NI       Change for BEV Full_Function_2.                                                                    */
/*                                MET-C_ECB-CSTD-1-00-C-C0                                                                           */
/*                                Changed split TT and PD, and rename the definitions accordingly.                                   */
/*                                                                                                                                   */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * KT   = Kenichi Takahashi, NTTD MSE                                                                                             */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*  * HU   = Hidekazu Usui, NTTD MSE                                                                                                 */
/*  * KO   = Kazuto Oishi,  Denso Techno                                                                                             */
/*  * HT   = Hibiki Tanii, KSE                                                                                                       */
/*  * NI   = Naoki Inagaki, KSE                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
