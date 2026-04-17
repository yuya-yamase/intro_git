/* 5.3.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert C_SLIP                                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_SLIP_C_MAJOR                     (5)
#define ALERT_C_SLIP_C_MINOR                     (3)
#define ALERT_C_SLIP_C_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_C_SLIP_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_C_SLIP.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_SLIP_NUM_DST                     (32U)

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
static U4      u4_s_AlertC_slipSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_C_SLIP_DST[ALERT_C_SLIP_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_C_SLIP_TESTMODE,                                             /* 02 TESTMODE                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_C_SLIP_OPERATING,                                            /* 04 OPERATING                                       */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_C_SLIP_MALFUNC,                                              /* 07 MALFUNC                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_C_SLIP_MALFUNC,                                              /* 16 MALFUNC                                         */
    (U1)ALERT_REQ_C_SLIP_MALFUNC,                                              /* 17 MALFUNC                                         */
    (U1)ALERT_REQ_C_SLIP_MALFUNC,                                              /* 18 MALFUNC                                         */
    (U1)ALERT_REQ_C_SLIP_MALFUNC,                                              /* 19 MALFUNC                                         */
    (U1)ALERT_REQ_C_SLIP_MALFUNC,                                              /* 20 MALFUNC                                         */
    (U1)ALERT_REQ_C_SLIP_MALFUNC,                                              /* 21 MALFUNC                                         */
    (U1)ALERT_REQ_C_SLIP_MALFUNC,                                              /* 22 MALFUNC                                         */
    (U1)ALERT_REQ_C_SLIP_MALFUNC,                                              /* 23 MALFUNC                                         */
    (U1)ALERT_REQ_C_SLIP_MALFUNC,                                              /* 24 MALFUNC                                         */
    (U1)ALERT_REQ_C_SLIP_MALFUNC,                                              /* 25 MALFUNC                                         */
    (U1)ALERT_REQ_C_SLIP_MALFUNC,                                              /* 26 MALFUNC                                         */
    (U1)ALERT_REQ_C_SLIP_MALFUNC,                                              /* 27 MALFUNC                                         */
    (U1)ALERT_REQ_C_SLIP_MALFUNC,                                              /* 28 MALFUNC                                         */
    (U1)ALERT_REQ_C_SLIP_MALFUNC,                                              /* 29 MALFUNC                                         */
    (U1)ALERT_REQ_C_SLIP_MALFUNC,                                              /* 30 MALFUNC                                         */
    (U1)ALERT_REQ_C_SLIP_MALFUNC                                               /* 31 MALFUNC                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_C_SLIP_MTRX[1] = {
    {
        &u4_s_AlertC_slipSrcchk,                                               /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_SLIP_DST[0],                                            /* u1p_DST                                            */
        (U2)ALERT_C_SLIP_NUM_DST,                                              /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_slipSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_slipSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_C_SLIP_TO_THRESH   = ((U2)1000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_C_SLIP_LSB_DDM1S17 = (U1)3U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_DDM1S17_CH0,
                                      (U4)OXCAN_SYS_IGR | (U4)OXCAN_SYS_IGP,
                                      u2_s_ALERT_C_SLIP_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_C_SLIP_LSB_DDM1S17);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_SLP_WL, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

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
/*  5.0.0     3/12/2020  SM       New.                                                                                               */
/*  5.1.0     8/25/2020  RI       Remove Communication disruption Judgement of less than 10V.                                        */
/*  5.1.1     7/ 1/2021  SO       Update for 050D CV(Version update).                                                                */
/*  5.2.0     1/13/2026  HT       Change for Full_function2 (MET-M_REMWAR-CSTD-2-04-A-C0)                                            */
/*                                Removed "ALERT_REQ" in order to transfer signal transmission control from the MCU to the SoC       */
/*  5.3.0     4/ 6/2026  HY       Change for Electronic CV (MET-M_REMWAR-CSTD-2-05-A-C0)                                             */
/*                                Remove the remote warning signal receiving process.                                                */
/*                                                                                                                                   */
/*  * SM   = Shingo Miyamoto, NTTD MSE                                                                                               */
/*  * RI   = Ren Ito, NTTD MSE                                                                                                       */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*  * HT   = Hibiki Tanii, KSE                                                                                                       */
/*  * HY   = Haruki Yagi, KSE                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
