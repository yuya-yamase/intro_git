/* 5.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert C_BRK-CSTD-2                                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_BRK_2_C_MAJOR                    (5)
#define ALERT_C_BRK_2_C_MINOR                    (4)
#define ALERT_C_BRK_2_C_PATCH                    (0)

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
#if (ALERT_C_BRK_2_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_C_BRK-CSTD-2.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_BRK_2_NUM_DST                    (64U)

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
static U4      u4_s_AlertC_brk_2Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertC_brk_2RwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_C_BRK_2_DST[ALERT_C_BRK_2_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_C_BRK_2_MALFUNC,                                             /* 01 MALFUNC                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_C_BRK_2_MALFUNC,                                             /* 03 MALFUNC                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_C_BRK_2_MALFUNC,                                             /* 05 MALFUNC                                         */
    (U1)ALERT_REQ_C_BRK_2_ON,                                                  /* 06 ON                                              */
    (U1)ALERT_REQ_C_BRK_2_ON_MLFNC,                                            /* 07 ON_MLFNC                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_C_BRK_2_MLFNC_RW,                                            /* 09 MLFNC_RW                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_C_BRK_2_MLFNC_RW,                                            /* 11 MLFNC_RW                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_C_BRK_2_MLFNC_RW,                                            /* 13 MLFNC_RW                                        */
    (U1)ALERT_REQ_C_BRK_2_ON_RW,                                               /* 14 ON_RW                                           */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 15 WRN                                             */
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
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 32 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 33 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 34 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 35 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 36 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 37 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 38 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 39 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 40 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 41 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 42 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 43 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 44 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 45 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 46 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 47 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 48 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 49 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 50 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 51 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 52 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 53 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 54 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 55 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 56 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 57 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 58 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 59 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 60 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 61 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN,                                                 /* 62 WRN                                             */
    (U1)ALERT_REQ_C_BRK_2_WRN                                                  /* 63 WRN                                             */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_C_BRK_2_MTRX[1] = {
    {
        &u4_s_AlertC_brk_2Srcchk,                                              /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertC_brk_2RwTx,                                                /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_BRK_2_DST[0],                                           /* u1p_DST                                            */
        (U2)ALERT_C_BRK_2_NUM_DST,                                             /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_brk_2Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_brk_2Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_DDM1S17_RXCH0)
    static const U2 u2_s_ALERT_C_BRK_TO_THRESH     = ((U2)1000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_C_BRK_LSB_B_BRKW    = (U1)1U;
    static const U1 u1_s_ALERT_C_BRK_LSB_DDRTWV    = (U1)3U;
    static const U1 u1_s_ALERT_C_BRK_LSB_MGSSTS    = (U1)4U;

    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_DDM1S17_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_C_BRK_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_C_BRK_LSB_MGSSTS);

    u1_t_sgnl     = (U1)0U;
#if defined(ComConf_ComSignal_BRK_MID)
    (void)Com_ReceiveSignal(ComConf_ComSignal_BRK_MID, &u1_t_sgnl);
#endif /* defined(ComConf_ComSignal_BRK_MID) */
    u4_t_src_chk |= (U4)u1_t_sgnl;

    u1_t_sgnl     = (U1)0U;
#if defined(ComConf_ComSignal_B_BRKW)
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_BRKW, &u1_t_sgnl);
#endif /* defined(ComConf_ComSignal_B_BRKW) */
    u4_t_src_chk |= ((U4)u1_t_sgnl  << u1_s_ALERT_C_BRK_LSB_B_BRKW);

    u1_t_sgnl     = (U1)0U;
#if defined(ComConf_ComSignal_DDRTWV)
    (void)Com_ReceiveSignal(ComConf_ComSignal_DDRTWV, &u1_t_sgnl);
#endif /* defined(ComConf_ComSignal_DDRTWV) */
    u4_t_src_chk |= ((U4)u1_t_sgnl  << u1_s_ALERT_C_BRK_LSB_DDRTWV);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_DDM1S17_RXCH0) */
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertC_brk_2RwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertC_brk_2RwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    static const U1 u1_s_ALERT_C_BRK_2_RWTX_CRT = ((U1)((U1)1U << ALERT_REQ_C_BRK_2_ON_RW   )
                                                |  (U1)((U1)1U << ALERT_REQ_C_BRK_2_MLFNC_RW)
                                                |  (U1)((U1)1U << ALERT_REQ_C_BRK_2_WRN     ));
    static const U1 u1_s_ALERT_C_BRK_2_RWTX_MSK = (U1)0x07U;
#ifdef ALERT_CH_C_BRK_0
#if (ALERT_CH_C_BRK_0 < ALERT_NUM_CH)
    static const U1 u1_s_ALERT_C_BRK_0_RWTX_CRT = ((U1)((U1)1U << ALERT_REQ_C_BRK_0_LOW     )
                                                |  (U1)((U1)1U << ALERT_REQ_C_BRK_0_TMODE   ));
    static const U1 u1_s_ALERT_C_BRK_0_RWTX_MSK = (U1)0x03U;
    U1              u1_t_rw_brk_0;
#endif /* (ALERT_CH_C_BRK_0 < ALERT_NUM_CH) */
#endif /* ALERT_CH_C_BRK_0 */
    U1              u1_t_sgnl;
    U1              u1_t_rw_brk_2;
    U1              u1_t_rwtx_enbl;

    u1_t_rwtx_enbl = (U1)FALSE;

    u1_t_rw_brk_2 = ((U1)1U << (u1_a_DST & u1_s_ALERT_C_BRK_2_RWTX_MSK));
    u1_t_rw_brk_2 = (U1)(u1_t_rw_brk_2 & u1_s_ALERT_C_BRK_2_RWTX_CRT);
#ifdef ALERT_CH_C_BRK_0
#if (ALERT_CH_C_BRK_0 < ALERT_NUM_CH)
    u1_t_rw_brk_0 = ((U1)1U << (u1_g_AlertReqByCh((U2)ALERT_CH_C_BRK_0) & u1_s_ALERT_C_BRK_0_RWTX_MSK));
    u1_t_rw_brk_0 = (U1)(u1_t_rw_brk_0 & u1_s_ALERT_C_BRK_0_RWTX_CRT);
    if(u1_t_rw_brk_0 != (U1)0U){
        u1_t_rwtx_enbl = (U1)TRUE;
    }
#endif /* (ALERT_CH_C_BRK_0 < ALERT_NUM_CH) */
#endif /* ALERT_CH_C_BRK_0 */

    if(u1_t_rw_brk_2 != (U1)0U){
        u1_t_rwtx_enbl = (U1)TRUE;
    }

    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN) != (U1)0U) &&
       (u1_t_rwtx_enbl                    == (U1)TRUE)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_BRW, &u1_t_sgnl);    /* COM Tx STUB delete */
#endif
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     3/25/2020  MY       New.                                                                                               */
/*  5.0.1     4/22/2020  DS       Rename module name.                                                                                */
/*  5.1.0     5/26/2020  ZS       Change remote warning logic.                                                                       */
/*  5.2.0     8/24/2020  TN       Delete judgment low voltage logic.                                                                 */
/*  5.3.0    12/ 8/2020  ZS       Fix BRK_JDG bit shift logic.                                                                       */
/*  5.3.1     3/26/2021  TN       Update for 840B CV(Version update).                                                                */
/*  5.4.0     2/10/2025  HF       Change for BEV System_Consideration_1.(MET-C_BRK-CSTD-2-00-A-C0)                                   */
/*                                                                                                                                   */
/*  * MY   = Masaki Yoshizawa, NTTD MSE                                                                                              */
/*  * DS   = Daisuke Suzuki, NTTD MSE                                                                                                */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * TN   = Toshiaki Nagashima, NTTD MSE                                                                                            */
/*  * HF   = Hinari Fukamachi, KSE                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
