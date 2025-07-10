/* 5.2.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert S_APP                                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_APP_C_MAJOR                      (5)
#define ALERT_S_APP_C_MINOR                      (2)
#define ALERT_S_APP_C_PATCH                      (0)

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
#if (ALERT_S_APP_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_S_APP.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_APP_BC_NUM_DST                   (32U)

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
static U4      u4_s_AlertS_appBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_S_APP_BC_DST[ALERT_S_APP_BC_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_APP_BC_NOTOPERATED1,                                       /* 01 NOTOPERATED1                                    */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 02 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_NOTOPERATED2,                                       /* 03 NOTOPERATED2                                    */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_S_APP_BC_COMPLETION,                                         /* 06 COMPLETION                                      */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 16 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 17 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 18 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 19 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 20 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 21 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 22 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 23 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 24 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 25 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 26 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 27 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 28 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 29 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 30 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE                                         /* 31 DISCONTINUE                                     */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_S_APP_MTRX[1] = {
    {
        &u4_s_AlertS_appBcSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_APP_BC_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_S_APP_BC_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_appBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_appBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_RXD_PDU_CAN_IPA1S05_CH0) && defined(ComConf_ComSignal_IPA_BZ2)
    static const U2 u2_s_ALERT_S_APP_BC_THRSH_TO   = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_S_APP_BC_LSB_COMSTS = (U1)3U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_IPA1S05_CH0,
                                          (U4)OXCAN_SYS_IGR,
                                          u2_s_ALERT_S_APP_BC_THRSH_TO) & (U1)(COM_TIMEOUT | COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_IPA_BZ2, &u1_t_sgnl);

    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_S_APP_BC_LSB_COMSTS);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_RXD_PDU_CAN_IPA1S05_CH0) && defined(ComConf_ComSignal_IPA_BZ2) */
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     3/23/2020  KH       New.                                                                                               */
/*  5.1.0     8/18/2020  ZS       Fix remote warning logic.                                                                          */
/*  5.1.1     3/25/2021  MO       Update for 840B CV(Version update).                                                                */
/*  5.1.2     1/19/2022  KAT      Update for 840B#2 CV(Version update).                                                              */
/*  5.2.0     6/23/2025  HY       Change for BEV System_Consideration_2.(MET-S_ADMID-CSTD-0-02-A-C0,MET-S_ADTT-CSTD-0-02-A-C0)       */
/*                                                                                                                                   */
/*  * KH   = Koji Hattori, NTTD MSE                                                                                                  */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * MO   = Masayuki Oofuji, NTTD MSE                                                                                               */
/*  * KAT  = Katsushi Takahashi, NTTD MSE                                                                                            */
/*  * HY   = Haruki Yagi, KSE                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
