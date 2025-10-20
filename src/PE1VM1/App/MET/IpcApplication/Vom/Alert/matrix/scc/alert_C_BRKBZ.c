/* 5.3.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert C_BRKBZ                                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_BRKBZ_C_MAJOR                    (5)
#define ALERT_C_BRKBZ_C_MINOR                    (3)
#define ALERT_C_BRKBZ_C_PATCH                    (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"

#include "g3mlib_mtrxsrch.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_C_BRKBZ_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_C_BRKBZ.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_BRKBZ_NUM_DST                    (18U)

#define ALERT_C_BRKBZ_BZJDG_REQ_TBL              (18U)
#define ALERT_C_BRKBZ_BZJDG_UNAVAILABLE1         (0U)
#define ALERT_C_BRKBZ_BZJDG_TESTMODE1            (1U)
#define ALERT_C_BRKBZ_BZJDG_TESTMODE2            (2U)
#define ALERT_C_BRKBZ_BZJDG_TESTMODE3            (3U)
#define ALERT_C_BRKBZ_BZJDG_APPOPE1              (4U)
#define ALERT_C_BRKBZ_BZJDG_APPOPE2              (5U)
#define ALERT_C_BRKBZ_BZJDG_FAILURE              (6U)
#define ALERT_C_BRKBZ_BZJDG_UNAVAILABLE2         (7U)
#define ALERT_C_BRKBZ_BZJDG_APPOPE3              (8U)
#define ALERT_C_BRKBZ_BZJDG_UNKNOWN              (9U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if defined(OXCAN_PDU_RX_CAN_VSC1S95) && defined(ComConf_ComSignal_B_BUZZER)
static U1      u1_s_alert_c_brkbz_b_buzze_last;
#endif /* defined(OXCAN_PDU_RX_CAN_VSC1S95) && defined(ComConf_ComSignal_B_BUZZER) */
#if defined(OXCAN_PDU_RX_CAN_VSC1S97) && defined(ComConf_ComSignal_B_BUZZE2)
static U1      u1_s_alert_c_brkbz_b_buzze2_last;
#endif /* defined(OXCAN_PDU_RX_CAN_VSC1S97) && defined(ComConf_ComSignal_B_BUZZE2) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertC_brkbzSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U4  u4_sp_ALERT_C_BRKBZ_CRIT[ALERT_C_BRKBZ_NUM_DST] = {
    (U4)0x00000001U,                                                           /* 00 TESTMODE1                                       */
    (U4)0x00000010U,                                                           /* 01 TESTMODE1                                       */
    (U4)0x00000002U,                                                           /* 02 TESTMODE2                                       */
    (U4)0x00000020U,                                                           /* 03 TESTMODE2                                       */
    (U4)0x00000003U,                                                           /* 04 TESTMODE3                                       */
    (U4)0x00000030U,                                                           /* 05 TESTMODE3                                       */
    (U4)0x00000006U,                                                           /* 06 FAILURE                                         */
    (U4)0x00000060U,                                                           /* 07 FAILURE                                         */
    (U4)0x00000007U,                                                           /* 08 UNAVAILABLE2                                    */
    (U4)0x00000070U,                                                           /* 09 UNAVAILABLE2                                    */
    (U4)0x00000000U,                                                           /* 10 UNAVAILABLE1                                    */
    (U4)0x00000000U,                                                           /* 11 UNAVAILABLE1                                    */
    (U4)0x00000008U,                                                           /* 12 APPOPE3                                         */
    (U4)0x00000080U,                                                           /* 13 APPOPE3                                         */
    (U4)0x00000004U,                                                           /* 14 APPOPE1                                         */
    (U4)0x00000040U,                                                           /* 15 APPOPE1                                         */
    (U4)0x00000005U,                                                           /* 16 APPOPE2                                         */
    (U4)0x00000050U                                                            /* 17 APPOPE2                                         */
};
static const U4  u4_sp_ALERT_C_BRKBZ_MASK[ALERT_C_BRKBZ_NUM_DST] = {
    (U4)0x0000000FU,                                                           /* 00 TESTMODE1                                       */
    (U4)0x000000F0U,                                                           /* 01 TESTMODE1                                       */
    (U4)0x0000000FU,                                                           /* 02 TESTMODE2                                       */
    (U4)0x000000F0U,                                                           /* 03 TESTMODE2                                       */
    (U4)0x0000000FU,                                                           /* 04 TESTMODE3                                       */
    (U4)0x000000F0U,                                                           /* 05 TESTMODE3                                       */
    (U4)0x0000000FU,                                                           /* 06 FAILURE                                         */
    (U4)0x000000F0U,                                                           /* 07 FAILURE                                         */
    (U4)0x0000000FU,                                                           /* 08 UNAVAILABLE2                                    */
    (U4)0x000000F0U,                                                           /* 09 UNAVAILABLE2                                    */
    (U4)0x0000000FU,                                                           /* 10 UNAVAILABLE1                                    */
    (U4)0x000000F0U,                                                           /* 11 UNAVAILABLE1                                    */
    (U4)0x0000000FU,                                                           /* 12 APPOPE3                                         */
    (U4)0x000000F0U,                                                           /* 13 APPOPE3                                         */
    (U4)0x0000000FU,                                                           /* 14 APPOPE1                                         */
    (U4)0x000000F0U,                                                           /* 15 APPOPE1                                         */
    (U4)0x0000000FU,                                                           /* 16 APPOPE2                                         */
    (U4)0x000000F0U                                                            /* 17 APPOPE2                                         */
};
static const U1  u1_sp_ALERT_C_BRKBZ_DST[ALERT_C_BRKBZ_NUM_DST] = {
    (U1)ALERT_REQ_C_BRKBZ_TESTMODE1,                                           /* 00 TESTMODE1                                       */
    (U1)ALERT_REQ_C_BRKBZ_TESTMODE1,                                           /* 01 TESTMODE1                                       */
    (U1)ALERT_REQ_C_BRKBZ_TESTMODE2,                                           /* 02 TESTMODE2                                       */
    (U1)ALERT_REQ_C_BRKBZ_TESTMODE2,                                           /* 03 TESTMODE2                                       */
    (U1)ALERT_REQ_C_BRKBZ_TESTMODE3,                                           /* 04 TESTMODE3                                       */
    (U1)ALERT_REQ_C_BRKBZ_TESTMODE3,                                           /* 05 TESTMODE3                                       */
    (U1)ALERT_REQ_C_BRKBZ_FAILURE,                                             /* 06 FAILURE                                         */
    (U1)ALERT_REQ_C_BRKBZ_FAILURE,                                             /* 07 FAILURE                                         */
    (U1)ALERT_REQ_C_BRKBZ_UNAVAILABLE2,                                        /* 08 UNAVAILABLE2                                    */
    (U1)ALERT_REQ_C_BRKBZ_UNAVAILABLE2,                                        /* 09 UNAVAILABLE2                                    */
    (U1)ALERT_REQ_C_BRKBZ_UNAVAILABLE1,                                        /* 10 UNAVAILABLE1                                    */
    (U1)ALERT_REQ_C_BRKBZ_UNAVAILABLE1,                                        /* 11 UNAVAILABLE1                                    */
    (U1)ALERT_REQ_C_BRKBZ_APPOPE3,                                             /* 12 APPOPE3                                         */
    (U1)ALERT_REQ_C_BRKBZ_APPOPE3,                                             /* 13 APPOPE3                                         */
    (U1)ALERT_REQ_C_BRKBZ_APPOPE1,                                             /* 14 APPOPE1                                         */
    (U1)ALERT_REQ_C_BRKBZ_APPOPE1,                                             /* 15 APPOPE1                                         */
    (U1)ALERT_REQ_C_BRKBZ_APPOPE2,                                             /* 16 APPOPE2                                         */
    (U1)ALERT_REQ_C_BRKBZ_APPOPE2                                              /* 17 APPOPE2                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_C_BRKBZ_MTRX[1] = {
    {
        &u4_s_AlertC_brkbzSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_C_BRKBZ_MASK[0],                                          /* u4p_MASK                                           */
        &u4_sp_ALERT_C_BRKBZ_CRIT[0],                                          /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_BRKBZ_DST[0],                                           /* u1p_DST                                            */
        (U2)ALERT_C_BRKBZ_NUM_DST,                                             /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertC_brkbzInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertC_brkbzInit(void)
{
#if defined(OXCAN_PDU_RX_CAN_VSC1S95) && defined(ComConf_ComSignal_B_BUZZER)
    u1_s_alert_c_brkbz_b_buzze_last  = (U1)0x00U;
#endif /* defined(OXCAN_PDU_RX_CAN_VSC1S95) && defined(ComConf_ComSignal_B_BUZZER) */
#if defined(OXCAN_PDU_RX_CAN_VSC1S97) && defined(ComConf_ComSignal_B_BUZZE2)
    u1_s_alert_c_brkbz_b_buzze2_last = (U1)0x00U;
#endif /* defined(OXCAN_PDU_RX_CAN_VSC1S97) && defined(ComConf_ComSignal_B_BUZZE2) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_brkbzSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_brkbzSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if 0   /* BEV Rebase provisionally */
    static const U4  u4_sp_ALERT_C_BRKBZ_BZJDG_CRIT[ALERT_C_BRKBZ_BZJDG_REQ_TBL] = {
        (U4)0x00000020U,                                                       /* 00 UNAVAILABLE1                                    */
        (U4)0x00000030U,                                                       /* 01 TESTMODE1                                       */
        (U4)0x00000060U,                                                       /* 02 APPOPE1                                         */
        (U4)0x00000070U,                                                       /* 03 APPOPE2                                         */
        (U4)0x00000080U,                                                       /* 04 FAILURE                                         */
        (U4)0x00000090U,                                                       /* 05 UNAVAILABLE2                                    */
        (U4)0x00000040U,                                                       /* 06 TESTMODE2                                       */
        (U4)0x00000045U,                                                       /* 07 TESTMODE2                                       */
        (U4)0x00000046U,                                                       /* 08 TESTMODE2                                       */
        (U4)0x00000048U,                                                       /* 09 TESTMODE2                                       */
        (U4)0x00000050U,                                                       /* 10 TESTMODE3                                       */
        (U4)0x00000054U,                                                       /* 11 TESTMODE3                                       */
        (U4)0x00000056U,                                                       /* 12 TESTMODE3                                       */
        (U4)0x00000058U,                                                       /* 13 TESTMODE3                                       */
        (U4)0x000000A0U,                                                       /* 14 APPOPE3                                         */
        (U4)0x000000A8U,                                                       /* 15 APPOPE3                                         */
        (U4)0x000000ABU,                                                       /* 16 APPOPE3                                         */
        (U4)0x000000ACU                                                        /* 17 APPOPE3                                         */
    };
    static const U4  u4_sp_ALERT_C_BRKBZ_BZJDG_MASK[ALERT_C_BRKBZ_BZJDG_REQ_TBL] = {
        (U4)0x000003F0U,                                                       /* 00 UNAVAILABLE1                                    */
        (U4)0x000003F0U,                                                       /* 01 TESTMODE1                                       */
        (U4)0x000003F0U,                                                       /* 02 APPOPE1                                         */
        (U4)0x000003F0U,                                                       /* 03 APPOPE2                                         */
        (U4)0x000003F0U,                                                       /* 04 FAILURE                                         */
        (U4)0x000003F0U,                                                       /* 05 UNAVAILABLE2                                    */
        (U4)0x000003FCU,                                                       /* 06 TESTMODE2                                       */
        (U4)0x000003FFU,                                                       /* 07 TESTMODE2                                       */
        (U4)0x000003FEU,                                                       /* 08 TESTMODE2                                       */
        (U4)0x000003F8U,                                                       /* 09 TESTMODE2                                       */
        (U4)0x000003FCU,                                                       /* 10 TESTMODE3                                       */
        (U4)0x000003FFU,                                                       /* 11 TESTMODE3                                       */
        (U4)0x000003FEU,                                                       /* 12 TESTMODE3                                       */
        (U4)0x000003F8U,                                                       /* 13 TESTMODE3                                       */
        (U4)0x000003F8U,                                                       /* 14 APPOPE3                                         */
        (U4)0x000003FEU,                                                       /* 15 APPOPE3                                         */
        (U4)0x000003FFU,                                                       /* 16 APPOPE3                                         */
        (U4)0x000003FCU                                                        /* 17 APPOPE3                                         */
    };
    static const U1  u1_sp_ALERT_C_BRKBZ_BZJDG_DST[ALERT_C_BRKBZ_BZJDG_REQ_TBL] = {
        (U1)ALERT_C_BRKBZ_BZJDG_UNAVAILABLE1,                                  /* 00 UNAVAILABLE1                                    */
        (U1)ALERT_C_BRKBZ_BZJDG_TESTMODE1,                                     /* 01 TESTMODE1                                       */
        (U1)ALERT_C_BRKBZ_BZJDG_APPOPE1,                                       /* 02 APPOPE1                                         */
        (U1)ALERT_C_BRKBZ_BZJDG_APPOPE2,                                       /* 03 APPOPE2                                         */
        (U1)ALERT_C_BRKBZ_BZJDG_FAILURE,                                       /* 04 FAILURE                                         */
        (U1)ALERT_C_BRKBZ_BZJDG_UNAVAILABLE2,                                  /* 05 UNAVAILABLE2                                    */
        (U1)ALERT_C_BRKBZ_BZJDG_TESTMODE2,                                     /* 06 TESTMODE2                                       */
        (U1)ALERT_C_BRKBZ_BZJDG_TESTMODE2,                                     /* 07 TESTMODE2                                       */
        (U1)ALERT_C_BRKBZ_BZJDG_TESTMODE2,                                     /* 08 TESTMODE2                                       */
        (U1)ALERT_C_BRKBZ_BZJDG_TESTMODE2,                                     /* 09 TESTMODE2                                       */
        (U1)ALERT_C_BRKBZ_BZJDG_TESTMODE3,                                     /* 10 TESTMODE3                                       */
        (U1)ALERT_C_BRKBZ_BZJDG_TESTMODE3,                                     /* 11 TESTMODE3                                       */
        (U1)ALERT_C_BRKBZ_BZJDG_TESTMODE3,                                     /* 12 TESTMODE3                                       */
        (U1)ALERT_C_BRKBZ_BZJDG_TESTMODE3,                                     /* 13 TESTMODE3                                       */
        (U1)ALERT_C_BRKBZ_BZJDG_APPOPE3,                                       /* 14 APPOPE3                                         */
        (U1)ALERT_C_BRKBZ_BZJDG_APPOPE3,                                       /* 15 APPOPE3                                         */
        (U1)ALERT_C_BRKBZ_BZJDG_APPOPE3,                                       /* 16 APPOPE3                                         */
        (U1)ALERT_C_BRKBZ_BZJDG_APPOPE3                                        /* 17 APPOPE3                                         */
    };
    static const ST_MTRX_SRCH st_s_ALERT_C_BRKBZ_MTRX_SRCH   =
                  /* u4p_MASK,                         u4p_CRIT,                            u2_len_inst, u2_num_srch                 */
                { &u4_sp_ALERT_C_BRKBZ_BZJDG_MASK[0], &u4_sp_ALERT_C_BRKBZ_BZJDG_CRIT[0], (U2)1U,        (U2)ALERT_C_BRKBZ_BZJDG_REQ_TBL };

    static const U1           u1_s_ALERT_C_BRKBZ_LSB_BZR     = (U1)4U;
    static const U1           u1_s_ALERT_C_BRKBZ_LSB_MSGSTS  = (U1)8U;
    static const U1           u1_s_ALERT_C_BRKBZ_LSB_BZR_REQ = (U1)4U;

#if defined(OXCAN_PDU_RX_CAN_VSC1S97) && defined(ComConf_ComSignal_B_BUZZE2)
    static const U2           u2_s_ALERT_C_BRKBZ_TO_THRESH97 = ((U2)1000U / (U2)OXCAN_MAIN_TICK);
    U1                        u1_t_msg_vsc97;
    U1                        u1_t_sgnl_b_buzze2;
#endif /* defined(OXCAN_PDU_RX_CAN_VSC1S97) && defined(ComConf_ComSignal_B_BUZZE2) */

#if defined(OXCAN_PDU_RX_CAN_VSC1S95) && defined(ComConf_ComSignal_B_BUZZER)
    static const U2           u2_s_ALERT_C_BRKBZ_TO_THRESH95 = ((U2)1000U / (U2)OXCAN_MAIN_TICK);
    U1                        u1_t_msg_vsc95;
    U1                        u1_t_sgnl_b_buzze;
#endif /* defined(OXCAN_PDU_RX_CAN_VSC1S95) && defined(ComConf_ComSignal_B_BUZZER) */
    U4                        u4_t_src_chk;
    U4                        u4_t_src_chk_b_buzze;
    U4                        u4_t_src_chk_b_buzze2;

#if defined(OXCAN_PDU_RX_CAN_VSC1S97) && defined(ComConf_ComSignal_B_BUZZE2)
    u1_t_msg_vsc97                   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_VSC1S97,
                                                             (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                                             u2_s_ALERT_C_BRKBZ_TO_THRESH97) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl_b_buzze2               = (U1)0U;
    if(u1_t_msg_vsc97 == (U1)0U){
        (void)Com_ReceiveSignal(ComConf_ComSignal_B_BUZZE2, &u1_t_sgnl_b_buzze2);
    }

    u4_t_src_chk_b_buzze2            = (U4)u1_s_alert_c_brkbz_b_buzze2_last;
    u4_t_src_chk_b_buzze2           |= ((U4)u1_t_sgnl_b_buzze2 << u1_s_ALERT_C_BRKBZ_LSB_BZR);
    u4_t_src_chk_b_buzze2           |= ((U4)u1_t_msg_vsc97     << u1_s_ALERT_C_BRKBZ_LSB_MSGSTS);

    u1_s_alert_c_brkbz_b_buzze2_last = u1_t_sgnl_b_buzze2;

    u4_t_src_chk_b_buzze2            = (U4)u2_g_MtrxSrch_lt(u4_t_src_chk_b_buzze2, &st_s_ALERT_C_BRKBZ_MTRX_SRCH);
    if(u4_t_src_chk_b_buzze2 < (U4)ALERT_C_BRKBZ_BZJDG_REQ_TBL){
        u4_t_src_chk_b_buzze2 = (U4)u1_sp_ALERT_C_BRKBZ_BZJDG_DST[u4_t_src_chk_b_buzze2];
    }
    else{
        u4_t_src_chk_b_buzze2 = (U4)ALERT_C_BRKBZ_BZJDG_UNKNOWN;
    }
#else
    u4_t_src_chk_b_buzze2            = (U4)ALERT_C_BRKBZ_BZJDG_UNKNOWN;
#endif /* defined(OXCAN_PDU_RX_CAN_VSC1S97) && defined(ComConf_ComSignal_B_BUZZE2) */

#if defined(OXCAN_PDU_RX_CAN_VSC1S95) && defined(ComConf_ComSignal_B_BUZZER)
    u1_t_msg_vsc95                   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_VSC1S95,
                                                             (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                                             u2_s_ALERT_C_BRKBZ_TO_THRESH95) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl_b_buzze                = (U1)0U;
    if(u1_t_msg_vsc95 == (U1)0U){
        (void)Com_ReceiveSignal(ComConf_ComSignal_B_BUZZER, &u1_t_sgnl_b_buzze);
    }

    u4_t_src_chk_b_buzze             = (U4)u1_s_alert_c_brkbz_b_buzze_last;
    u4_t_src_chk_b_buzze            |= ((U4)u1_t_sgnl_b_buzze << u1_s_ALERT_C_BRKBZ_LSB_BZR);
    u4_t_src_chk_b_buzze            |= ((U4)u1_t_msg_vsc95    << u1_s_ALERT_C_BRKBZ_LSB_MSGSTS);

    u1_s_alert_c_brkbz_b_buzze_last  = u1_t_sgnl_b_buzze;

    u4_t_src_chk_b_buzze             = (U4)u2_g_MtrxSrch_lt(u4_t_src_chk_b_buzze, &st_s_ALERT_C_BRKBZ_MTRX_SRCH);
    if(u4_t_src_chk_b_buzze < (U4)ALERT_C_BRKBZ_BZJDG_REQ_TBL){
        u4_t_src_chk_b_buzze = (U4)u1_sp_ALERT_C_BRKBZ_BZJDG_DST[u4_t_src_chk_b_buzze];
    }
    else{
        u4_t_src_chk_b_buzze = (U4)ALERT_C_BRKBZ_BZJDG_UNKNOWN;
    }
#else
    u4_t_src_chk_b_buzze             = (U4)ALERT_C_BRKBZ_BZJDG_UNKNOWN;
#endif /* defined(OXCAN_PDU_RX_CAN_VSC1S95) && defined(ComConf_ComSignal_B_BUZZER) */

    u4_t_src_chk                     = u4_t_src_chk_b_buzze2;
    u4_t_src_chk                    |= (u4_t_src_chk_b_buzze << u1_s_ALERT_C_BRKBZ_LSB_BZR_REQ);

    return(u4_t_src_chk);
#else   /* BEV Rebase provisionally */
    return((U4)0U);
#endif  /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     4/ 2/2020  FN       New.                                                                                               */
/*  5.1.0     9/ 9/2020  TI       Delete Low-voltage Jugdment and Change Search Table.                                               */
/*  5.1.1     9/24/2020  TH       Fix QAC Warning.                                                                                   */
/*  5.2.0    12/ 8/2020  TN       Update for 800B 1A(Version update).                                                                */
/*  5.3.0     2/ 3/2021  ZS       Fix Matrix table.                                                                                  */
/*  5.3.1     3/18/2021  SO       Update for 840B CV(Version update).                                                                */
/*                                                                                                                                   */
/*  * FN   = Farah Niwa, NTTD MSE                                                                                                    */
/*  * TI   = Takuro Iwanaga, NTTD MSE                                                                                                */
/*  * TH   = Takuya Hiraide, NTTD MSE                                                                                                */
/*  * TN   = Toshiaki Nagashima, NTTD MSE                                                                                            */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
