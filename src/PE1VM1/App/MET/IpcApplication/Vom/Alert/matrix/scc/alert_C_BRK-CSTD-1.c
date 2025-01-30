/* 5.3.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert C_BRK-CSTD-1                                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_BRK_1_C_MAJOR                    (5)
#define ALERT_C_BRK_1_C_MINOR                    (3)
#define ALERT_C_BRK_1_C_PATCH                    (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_C_BRK_1_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_C_BRK-CSTD-1.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_BRK_1_NUM_DST                    (64U)

#define ALERT_C_BRK_BRKJDG_NUM                   (64U)
#define ALERT_C_BRK_BRKJDG_UNKNOWN               (0U)
#define ALERT_C_BRK_BRKJDG_ON                    (1U)
#define ALERT_C_BRK_BRKJDG_MALFUNC               (2U)
#define ALERT_C_BRK_BRKJDG_ON_MLFNC              (3U)
#define ALERT_C_BRK_BRKJDG_ON_RW                 (4U)
#define ALERT_C_BRK_BRKJDG_MLFNC_RW              (5U)
#define ALERT_C_BRK_BRKJDG_WRN                   (6U)

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
static U4      u4_s_AlertC_brk_1Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertC_brk_1RwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_C_BRK_1_DST[ALERT_C_BRK_1_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_C_BRK_1_ON,                                                  /* 01 ON                                              */
    (U1)ALERT_REQ_C_BRK_1_MALFUNC,                                             /* 02 MALFUNC                                         */
    (U1)ALERT_REQ_C_BRK_1_ON_MLFNC,                                            /* 03 ON_MLFNC                                        */
    (U1)ALERT_REQ_C_BRK_1_ON_RW,                                               /* 04 ON_RW                                           */
    (U1)ALERT_REQ_C_BRK_1_MLFNC_RW,                                            /* 05 MLFNC_RW                                        */
    (U1)ALERT_REQ_C_BRK_1_WRN,                                                 /* 06 WRN                                             */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_C_BRK_1_ON,                                                  /* 08 ON                                              */
    (U1)ALERT_REQ_C_BRK_1_ON,                                                  /* 09 ON                                              */
    (U1)ALERT_REQ_C_BRK_1_ON_MLFNC,                                            /* 10 ON_MLFNC                                        */
    (U1)ALERT_REQ_C_BRK_1_ON_MLFNC,                                            /* 11 ON_MLFNC                                        */
    (U1)ALERT_REQ_C_BRK_1_ON_RW,                                               /* 12 ON_RW                                           */
    (U1)ALERT_REQ_C_BRK_1_WRN,                                                 /* 13 WRN                                             */
    (U1)ALERT_REQ_C_BRK_1_WRN,                                                 /* 14 WRN                                             */
    (U1)ALERT_REQ_C_BRK_1_ON,                                                  /* 15 ON                                              */
    (U1)ALERT_REQ_C_BRK_1_MALFUNC,                                             /* 16 MALFUNC                                         */
    (U1)ALERT_REQ_C_BRK_1_ON_MLFNC,                                            /* 17 ON_MLFNC                                        */
    (U1)ALERT_REQ_C_BRK_1_MALFUNC,                                             /* 18 MALFUNC                                         */
    (U1)ALERT_REQ_C_BRK_1_ON_MLFNC,                                            /* 19 ON_MLFNC                                        */
    (U1)ALERT_REQ_C_BRK_1_WRN,                                                 /* 20 WRN                                             */
    (U1)ALERT_REQ_C_BRK_1_MLFNC_RW,                                            /* 21 MLFNC_RW                                        */
    (U1)ALERT_REQ_C_BRK_1_WRN,                                                 /* 22 WRN                                             */
    (U1)ALERT_REQ_C_BRK_1_MALFUNC,                                             /* 23 MALFUNC                                         */
    (U1)ALERT_REQ_C_BRK_1_ON_MLFNC,                                            /* 24 ON_MLFNC                                        */
    (U1)ALERT_REQ_C_BRK_1_ON_MLFNC,                                            /* 25 ON_MLFNC                                        */
    (U1)ALERT_REQ_C_BRK_1_ON_MLFNC,                                            /* 26 ON_MLFNC                                        */
    (U1)ALERT_REQ_C_BRK_1_ON_MLFNC,                                            /* 27 ON_MLFNC                                        */
    (U1)ALERT_REQ_C_BRK_1_WRN,                                                 /* 28 WRN                                             */
    (U1)ALERT_REQ_C_BRK_1_WRN,                                                 /* 29 WRN                                             */
    (U1)ALERT_REQ_C_BRK_1_WRN,                                                 /* 30 WRN                                             */
    (U1)ALERT_REQ_C_BRK_1_ON_MLFNC,                                            /* 31 ON_MLFNC                                        */
    (U1)ALERT_REQ_C_BRK_1_ON_RW,                                               /* 32 ON_RW                                           */
    (U1)ALERT_REQ_C_BRK_1_ON_RW,                                               /* 33 ON_RW                                           */
    (U1)ALERT_REQ_C_BRK_1_WRN,                                                 /* 34 WRN                                             */
    (U1)ALERT_REQ_C_BRK_1_WRN,                                                 /* 35 WRN                                             */
    (U1)ALERT_REQ_C_BRK_1_ON_RW,                                               /* 36 ON_RW                                           */
    (U1)ALERT_REQ_C_BRK_1_WRN,                                                 /* 37 WRN                                             */
    (U1)ALERT_REQ_C_BRK_1_WRN,                                                 /* 38 WRN                                             */
    (U1)ALERT_REQ_C_BRK_1_ON_RW,                                               /* 39 ON_RW                                           */
    (U1)ALERT_REQ_C_BRK_1_MLFNC_RW,                                            /* 40 MLFNC_RW                                        */
    (U1)ALERT_REQ_C_BRK_1_WRN,                                                 /* 41 WRN                                             */
    (U1)ALERT_REQ_C_BRK_1_MLFNC_RW,                                            /* 42 MLFNC_RW                                        */
    (U1)ALERT_REQ_C_BRK_1_WRN,                                                 /* 43 WRN                                             */
    (U1)ALERT_REQ_C_BRK_1_WRN,                                                 /* 44 WRN                                             */
    (U1)ALERT_REQ_C_BRK_1_MLFNC_RW,                                            /* 45 MLFNC_RW                                        */
    (U1)ALERT_REQ_C_BRK_1_WRN,                                                 /* 46 WRN                                             */
    (U1)ALERT_REQ_C_BRK_1_MLFNC_RW,                                            /* 47 MLFNC_RW                                        */
    (U1)ALERT_REQ_C_BRK_1_WRN,                                                 /* 48 WRN                                             */
    (U1)ALERT_REQ_C_BRK_1_WRN,                                                 /* 49 WRN                                             */
    (U1)ALERT_REQ_C_BRK_1_WRN,                                                 /* 50 WRN                                             */
    (U1)ALERT_REQ_C_BRK_1_WRN,                                                 /* 51 WRN                                             */
    (U1)ALERT_REQ_C_BRK_1_WRN,                                                 /* 52 WRN                                             */
    (U1)ALERT_REQ_C_BRK_1_WRN,                                                 /* 53 WRN                                             */
    (U1)ALERT_REQ_C_BRK_1_WRN,                                                 /* 54 WRN                                             */
    (U1)ALERT_REQ_C_BRK_1_WRN,                                                 /* 55 WRN                                             */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 56 UNKNOWN                                         */
    (U1)ALERT_REQ_C_BRK_1_ON,                                                  /* 57 ON                                              */
    (U1)ALERT_REQ_C_BRK_1_MALFUNC,                                             /* 58 MALFUNC                                         */
    (U1)ALERT_REQ_C_BRK_1_ON_MLFNC,                                            /* 59 ON_MLFNC                                        */
    (U1)ALERT_REQ_C_BRK_1_ON_RW,                                               /* 60 ON_RW                                           */
    (U1)ALERT_REQ_C_BRK_1_MLFNC_RW,                                            /* 61 MLFNC_RW                                        */
    (U1)ALERT_REQ_C_BRK_1_WRN,                                                 /* 62 WRN                                             */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 63 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_C_BRK_1_MTRX[1] = {
    {
        &u4_s_AlertC_brk_1Srcchk,                                              /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertC_brk_1RwTx,                                                /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_BRK_1_DST[0],                                           /* u1p_DST                                            */
        (U2)ALERT_C_BRK_1_NUM_DST,                                             /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_brk_1Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_brk_1Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1  u1_sp_ALERT_C_BRK_BRKJDG[ALERT_C_BRK_BRKJDG_NUM] = {
        (U1)ALERT_C_BRK_BRKJDG_UNKNOWN,                                            /* 00 UNKNOWN                                     */
        (U1)ALERT_C_BRK_BRKJDG_MALFUNC,                                            /* 01 MALFUNC                                     */
        (U1)ALERT_C_BRK_BRKJDG_UNKNOWN,                                            /* 02 UNKNOWN                                     */
        (U1)ALERT_C_BRK_BRKJDG_MALFUNC,                                            /* 03 MALFUNC                                     */
        (U1)ALERT_C_BRK_BRKJDG_UNKNOWN,                                            /* 04 UNKNOWN                                     */
        (U1)ALERT_C_BRK_BRKJDG_MALFUNC,                                            /* 05 MALFUNC                                     */
        (U1)ALERT_C_BRK_BRKJDG_ON,                                                 /* 06 ON                                          */
        (U1)ALERT_C_BRK_BRKJDG_ON_MLFNC,                                           /* 07 ON_MLFNC                                    */
        (U1)ALERT_C_BRK_BRKJDG_UNKNOWN,                                            /* 08 UNKNOWN                                     */
        (U1)ALERT_C_BRK_BRKJDG_MLFNC_RW,                                           /* 09 MLFNC_RW                                    */
        (U1)ALERT_C_BRK_BRKJDG_UNKNOWN,                                            /* 10 UNKNOWN                                     */
        (U1)ALERT_C_BRK_BRKJDG_MLFNC_RW,                                           /* 11 MLFNC_RW                                    */
        (U1)ALERT_C_BRK_BRKJDG_UNKNOWN,                                            /* 12 UNKNOWN                                     */
        (U1)ALERT_C_BRK_BRKJDG_MLFNC_RW,                                           /* 13 MLFNC_RW                                    */
        (U1)ALERT_C_BRK_BRKJDG_ON_RW,                                              /* 14 ON_RW                                       */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 15 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_UNKNOWN,                                            /* 16 UNKNOWN                                     */
        (U1)ALERT_C_BRK_BRKJDG_UNKNOWN,                                            /* 17 UNKNOWN                                     */
        (U1)ALERT_C_BRK_BRKJDG_UNKNOWN,                                            /* 18 UNKNOWN                                     */
        (U1)ALERT_C_BRK_BRKJDG_UNKNOWN,                                            /* 19 UNKNOWN                                     */
        (U1)ALERT_C_BRK_BRKJDG_UNKNOWN,                                            /* 20 UNKNOWN                                     */
        (U1)ALERT_C_BRK_BRKJDG_UNKNOWN,                                            /* 21 UNKNOWN                                     */
        (U1)ALERT_C_BRK_BRKJDG_UNKNOWN,                                            /* 22 UNKNOWN                                     */
        (U1)ALERT_C_BRK_BRKJDG_UNKNOWN,                                            /* 23 UNKNOWN                                     */
        (U1)ALERT_C_BRK_BRKJDG_UNKNOWN,                                            /* 24 UNKNOWN                                     */
        (U1)ALERT_C_BRK_BRKJDG_UNKNOWN,                                            /* 25 UNKNOWN                                     */
        (U1)ALERT_C_BRK_BRKJDG_UNKNOWN,                                            /* 26 UNKNOWN                                     */
        (U1)ALERT_C_BRK_BRKJDG_UNKNOWN,                                            /* 27 UNKNOWN                                     */
        (U1)ALERT_C_BRK_BRKJDG_UNKNOWN,                                            /* 28 UNKNOWN                                     */
        (U1)ALERT_C_BRK_BRKJDG_UNKNOWN,                                            /* 29 UNKNOWN                                     */
        (U1)ALERT_C_BRK_BRKJDG_UNKNOWN,                                            /* 30 UNKNOWN                                     */
        (U1)ALERT_C_BRK_BRKJDG_UNKNOWN,                                            /* 31 UNKNOWN                                     */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 32 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 33 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 34 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 35 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 36 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 37 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 38 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 39 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 40 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 41 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 42 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 43 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 44 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 45 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 46 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 47 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 48 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 49 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 50 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 51 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 52 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 53 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 54 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 55 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 56 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 57 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 58 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 59 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 60 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 61 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN,                                                /* 62 WRN                                         */
        (U1)ALERT_C_BRK_BRKJDG_WRN                                                 /* 63 WRN                                         */
    };
#ifdef OXCAN_PDU_RX_CAN_VSC1S95
    static const U2 u2_s_ALERT_C_BRK_TO_THRESH_95  = ((U2)1000U / (U2)OXCAN_MAIN_TICK);
#ifdef ComConf_ComSignal_B_BRKW
    static const U1 u1_s_ALERT_C_BRK_LSB_B_BRKW    = (U1)1U;
#endif /* ComConf_ComSignal_B_BRKW */
#ifdef ComConf_ComSignal_DDRTWV
    static const U1 u1_s_ALERT_C_BRK_LSB_DDRTWV    = (U1)3U;
#endif /* ComConf_ComSignal_DDRTWV */
    static const U1 u1_s_ALERT_C_BRK_LSB_MGSSTS_95 = (U1)4U;
    static const U1 u1_s_ALERT_C_BRK_LSB_BRK1JDG   = (U1)3U;
#endif /* OXCAN_PDU_RX_CAN_VSC1S95 */

#ifdef OXCAN_PDU_RX_CAN_VSC1S97
    static const U2 u2_s_ALERT_C_BRK_TO_THRESH_97  = ((U2)1000U / (U2)OXCAN_MAIN_TICK);

#ifdef ComConf_ComSignal_B_BRKW2
    static const U1 u1_s_ALERT_C_BRK_LSB_B_BRKW2   = (U1)1U;
#endif /* ComConf_ComSignal_B_BRKW2 */
#ifdef ComConf_ComSignal_DDRTWV2
    static const U1 u1_s_ALERT_C_BRK_LSB_DDRTWV2   = (U1)3U;
#endif /* ComConf_ComSignal_DDRTWV2 */
    static const U1 u1_s_ALERT_C_BRK_LSB_MGSSTS_97 = (U1)4U;
#endif /* OXCAN_PDU_RX_CAN_VSC1S97 */

    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U1              u1_t_brk_jdg;
    U4              u4_t_src_chk;

#ifdef OXCAN_PDU_RX_CAN_VSC1S95
    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_VSC1S95,
                                          (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                          u2_s_ALERT_C_BRK_TO_THRESH_95) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_brk_jdg  = (U1)(u1_t_msgsts                            << u1_s_ALERT_C_BRK_LSB_MGSSTS_95);
#ifdef ComConf_ComSignal_BRK_MID
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_BRK_MID, &u1_t_sgnl);
    u1_t_brk_jdg |= u1_t_sgnl;
#endif /* ComConf_ComSignal_BRK_MID */
#ifdef ComConf_ComSignal_B_BRKW
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_BRKW, &u1_t_sgnl);
    u1_t_brk_jdg |= (U1)(u1_t_sgnl                              << u1_s_ALERT_C_BRK_LSB_B_BRKW);
#endif /* ComConf_ComSignal_B_BRKW */
#ifdef ComConf_ComSignal_DDRTWV
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_DDRTWV, &u1_t_sgnl);
    u1_t_brk_jdg |= (U1)(u1_t_sgnl                              << u1_s_ALERT_C_BRK_LSB_DDRTWV);
#endif /* ComConf_ComSignal_DDRTWV */

    u4_t_src_chk  = ((U4)u1_sp_ALERT_C_BRK_BRKJDG[u1_t_brk_jdg] << u1_s_ALERT_C_BRK_LSB_BRK1JDG);
#else
    u4_t_src_chk  = (U4)0U;
#endif /* OXCAN_PDU_RX_CAN_VSC1S95 */

#ifdef OXCAN_PDU_RX_CAN_VSC1S97
    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_VSC1S97,
                                          (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                          u2_s_ALERT_C_BRK_TO_THRESH_97) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_brk_jdg  = (U1)(u1_t_msgsts                            << u1_s_ALERT_C_BRK_LSB_MGSSTS_97);
#ifdef ComConf_ComSignal_BRK_MID2
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_BRK_MID2, &u1_t_sgnl);
    u1_t_brk_jdg |= u1_t_sgnl;
#endif /* ComConf_ComSignal_BRK_MID2 */
#ifdef ComConf_ComSignal_B_BRKW2
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_BRKW2, &u1_t_sgnl);
    u1_t_brk_jdg |= (U1)(u1_t_sgnl                              << u1_s_ALERT_C_BRK_LSB_B_BRKW2);
#endif /* ComConf_ComSignal_B_BRKW2 */
#ifdef ComConf_ComSignal_DDRTWV2
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_DDRTWV2, &u1_t_sgnl);
    u1_t_brk_jdg |= (U1)(u1_t_sgnl                              << u1_s_ALERT_C_BRK_LSB_DDRTWV2);
#endif /* ComConf_ComSignal_DDRTWV2 */

    u4_t_src_chk |= (U4)u1_sp_ALERT_C_BRK_BRKJDG[u1_t_brk_jdg];
#endif /* OXCAN_PDU_RX_CAN_VSC1S97 */

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertC_brk_1RwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertC_brk_1RwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    static const U1 u1_s_ALERT_C_BRK_1_RWTX_CRT = ((U1)((U1)1U << ALERT_REQ_C_BRK_1_ON_RW   )
                                                |  (U1)((U1)1U << ALERT_REQ_C_BRK_1_MLFNC_RW)
                                                |  (U1)((U1)1U << ALERT_REQ_C_BRK_1_WRN     ));
    static const U1 u1_s_ALERT_C_BRK_1_RWTX_MSK = (U1)0x07U;
#ifdef ALERT_CH_C_BRK_0
#if (ALERT_CH_C_BRK_0 < ALERT_NUM_CH)
    static const U1 u1_s_ALERT_C_BRK_0_RWTX_CRT = ((U1)((U1)1U << ALERT_REQ_C_BRK_0_LOW     )
                                                |  (U1)((U1)1U << ALERT_REQ_C_BRK_0_TMODE   ));
    static const U1 u1_s_ALERT_C_BRK_0_RWTX_MSK = (U1)0x03U;
    U1              u1_t_rw_brk_0;
#endif /* (ALERT_CH_C_BRK_0 < ALERT_NUM_CH) */
#endif /* ALERT_CH_C_BRK_0 */
    U1              u1_t_sgnl;
    U1              u1_t_rw_brk_1;
    U1              u1_t_rwtx_enbl;

    u1_t_rwtx_enbl = (U1)FALSE;

    u1_t_rw_brk_1 = ((U1)1U << (u1_a_DST & u1_s_ALERT_C_BRK_1_RWTX_MSK));
    u1_t_rw_brk_1 = (U1)(u1_t_rw_brk_1 & u1_s_ALERT_C_BRK_1_RWTX_CRT);
#ifdef ALERT_CH_C_BRK_0
#if (ALERT_CH_C_BRK_0 < ALERT_NUM_CH)
    u1_t_rw_brk_0 = ((U1)1U << (u1_g_AlertReqByCh((U2)ALERT_CH_C_BRK_0) & u1_s_ALERT_C_BRK_0_RWTX_MSK));
    u1_t_rw_brk_0 = (U1)(u1_t_rw_brk_0 & u1_s_ALERT_C_BRK_0_RWTX_CRT);
    if(u1_t_rw_brk_0 != (U1)0U){
        u1_t_rwtx_enbl = (U1)TRUE;
    }
#endif /* (ALERT_CH_C_BRK_0 < ALERT_NUM_CH) */
#endif /* ALERT_CH_C_BRK_0 */

    if(u1_t_rw_brk_1 != (U1)0U){
        u1_t_rwtx_enbl = (U1)TRUE;
    }

    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN) != (U1)0U) &&
       (u1_t_rwtx_enbl                    == (U1)TRUE)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_BRW, &u1_t_sgnl);
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
/*                                                                                                                                   */
/*  * MY   = Masaki Yoshizawa, NTTD MSE                                                                                              */
/*  * DS   = Daisuke Suzuki, NTTD MSE                                                                                                */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * TN   = Toshiaki Nagashima, NTTD MSE                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/
