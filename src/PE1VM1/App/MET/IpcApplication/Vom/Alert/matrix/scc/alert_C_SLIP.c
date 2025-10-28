/* 5.1.1 */
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
#define ALERT_C_SLIP_C_MINOR                     (1)
#define ALERT_C_SLIP_C_PATCH                     (1)

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
#define ALERT_C_SLIP_NUM_DST                     (64U)

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
static void    vd_s_AlertC_slipRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

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
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 16 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 17 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 18 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 19 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 20 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 21 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 22 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 23 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 24 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 25 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 26 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 27 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 28 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 29 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 30 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 31 MALFUNC_RW                                      */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 32 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 33 UNKNOWN                                         */
    (U1)ALERT_REQ_C_SLIP_TESTMODE,                                             /* 34 TESTMODE                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 35 UNKNOWN                                         */
    (U1)ALERT_REQ_C_SLIP_OPERATING,                                            /* 36 OPERATING                                       */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 37 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 38 UNKNOWN                                         */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 39 MALFUNC_RW                                      */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 40 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 41 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 42 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 43 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 44 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 45 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 46 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 47 UNKNOWN                                         */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 48 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 49 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 50 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 51 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 52 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 53 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 54 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 55 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 56 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 57 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 58 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 59 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 60 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 61 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,                                           /* 62 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_SLIP_MALFUNC_RW                                            /* 63 MALFUNC_RW                                      */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_C_SLIP_MTRX[1] = {
    {
        &u4_s_AlertC_slipSrcchk,                                               /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertC_slipRwTx,                                                 /* fp_vd_XDST                                         */

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
#if 0   /* BEV Rebase provisionally */
    static const U2 u2_s_ALERT_C_SLIP_TO_THRESH   = ((U2)1000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_C_SLIP_LSB_VSC1S95 = (U1)3U;
    static const U1 u1_s_ALERT_C_SLIP_LSB_DDRTWV  = (U1)5U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_VSC1S95,
                                          (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                          u2_s_ALERT_C_SLIP_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_C_SLIP_LSB_VSC1S95);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_SLP_WL, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    u1_t_sgnl     = (U1)0U;
#ifdef ComConf_ComSignal_DDRTWV
    (void)Com_ReceiveSignal(ComConf_ComSignal_DDRTWV, &u1_t_sgnl);
#endif /* ComConf_ComSignal_DDRTWV */ /* 235D_CAN */
    u4_t_src_chk |= ((U4)u1_t_sgnl   << u1_s_ALERT_C_SLIP_LSB_DDRTWV);

    return(u4_t_src_chk);
#else   /* BEV Rebase provisionally */
    return((U4)0U);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertC_slipRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertC_slipRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
#if 0   /* BEV Rebase provisionally */
    U1              u1_t_sgnl;
    U1              u1_t_esopt_vsc;

    u1_t_esopt_vsc = u1_g_AlertEsOptAvailable((U2)ALERT_OPT_ID_C_SLIP_VSCEXIST);
    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN) != (U1)0U                         ) &&
       (u1_t_esopt_vsc                    == (U1)TRUE                       ) &&
       (u1_a_DST                          == (U1)ALERT_REQ_C_SLIP_MALFUNC_RW)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_VSCW, &u1_t_sgnl);
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
/*  5.0.0     3/12/2020  SM       New.                                                                                               */
/*  5.1.0     8/25/2020  RI       Remove Communication disruption Judgement of less than 10V.                                        */
/*  5.1.1     7/ 1/2021  SO       Update for 050D CV(Version update).                                                                */
/*                                                                                                                                   */
/*  * SM   = Shingo Miyamoto, NTTD MSE                                                                                               */
/*  * RI   = Ren Ito, NTTD MSE                                                                                                       */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
