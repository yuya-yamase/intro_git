/* 5.4.2 */
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
#define ALERT_C_ECB_C_MINOR                      (4)
#define ALERT_C_ECB_C_PATCH                      (2)

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
#if (ALERT_C_ECB_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_C_ECB.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_ECB_NUM_DST                      (64U)

#define ALERT_C_ECB_B_EBW_JDG_NUM                (32U)
#define ALERT_C_ECB_EBW_MID_JDG_NUM              (8U)
#define ALERT_C_ECB_DDRTWV_JDG_NUM               (8U)
#define ALERT_C_ECB_TT_JDG_NUM                   (46U)
#define ALERT_C_ECB_MID_JDG_NUM                  (16U)
#define ALERT_C_ECB_TT_RW_JDG_NUM                (16U)

#define ALERT_C_ECB_B_EBW_UNKNOWN                (0U)
#define ALERT_C_ECB_B_EBW_TESTMODE               (1U)
#define ALERT_C_ECB_B_EBW_LERNING1               (2U)
#define ALERT_C_ECB_B_EBW_LERNING2               (3U)
#define ALERT_C_ECB_B_EBW_MALFUNC                (4U)
#define ALERT_C_ECB_B_EBW_UNAVAILBL              (5U)

#define ALERT_C_ECB_EBW_MID_UNKNOWN              (0U)
#define ALERT_C_ECB_EBW_MID_FAILDISP             (1U)

#define ALERT_C_ECB_DDRTWV_RW_OFF                (0U)
#define ALERT_C_ECB_DDRTWV_RW_ON                 (1U)

#define ALERT_C_ECB_TT_JDG_UNKNOWN               (0U)
#define ALERT_C_ECB_TT_JDG_TESTMODE              (1U)
#define ALERT_C_ECB_TT_JDG_LERNING1              (2U)
#define ALERT_C_ECB_TT_JDG_LERNING2              (3U)
#define ALERT_C_ECB_TT_JDG_MALFUNC               (4U)
#define ALERT_C_ECB_TT_JDG_UNAVAILBL             (5U)

#define ALERT_C_ECB_MID_JDG_UNKNOWN              (0U)
#define ALERT_C_ECB_MID_JDG_FAILDISP             (1U)
#define ALERT_C_ECB_MID_JDG_FAILDISP_RW          (2U)

#define ALERT_C_ECB_TT_RW_OFF                    (0U)
#define ALERT_C_ECB_TT_RW_ON                     (1U)

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
static U4      u4_s_AlertC_ecbSrcchk      (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertC_ecbRwTx        (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);
static void    vd_s_AlertC_ecb_b_ebw_jdg  (const U1 u1_a_MSGSTS95,  U1 * u1_ap_b_ebw_jdg,  U1 * u1_ap_b_ebw_rw_jdg,
                                           const U1 u1_a_MSGSTS97,  U1 * u1_ap_b_ebw2_jdg, U1 * u1_ap_b_ebw2_rw_jdg);
static void    vd_s_AlertC_ecb_ebw_mid_jdg(const U1 u1_a_MSGSTS95,  U1 * u1_ap_ebw_mid_jdg,
                                           const U1 u1_a_MSGSTS97,  U1 * u1_ap_ebw_mid2_jdg);
static void    vd_s_AlertC_ecb_ddrtwv_jdg (const U1 u1_a_MSGSTS95,  U1 * u1_ap_ddrtwv_jdg,
                                           const U1 u1_a_MSGSTS97,  U1 * u1_ap_ddrtwv2_jdg);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_C_ECB_DST[ALERT_C_ECB_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_C_ECB_FAILDISP,                                              /* 02 FAILDISP                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_C_ECB_FDISP_RW,                                              /* 04 FDISP_RW                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_C_ECB_TESTMODE,                                              /* 08 TESTMODE                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_C_ECB_TM_DISP,                                               /* 10 TM_DISP                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_C_ECB_TM_DISP_RW,                                            /* 12 TM_DISP_RW                                      */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_C_ECB_LERNING1,                                              /* 16 LERNING1                                        */
    (U1)ALERT_REQ_C_ECB_LNG1_RW,                                               /* 17 LNG1_RW                                         */
    (U1)ALERT_REQ_C_ECB_LNG1_DISP,                                             /* 18 LNG1_DISP                                       */
    (U1)ALERT_REQ_C_ECB_LNG1_DISP_RW,                                          /* 19 LNG1_DISP_RW                                    */
    (U1)ALERT_REQ_C_ECB_LNG1_DISP_RW,                                          /* 20 LNG1_DISP_RW                                    */
    (U1)ALERT_REQ_C_ECB_LNG1_DISP_RW,                                          /* 21 LNG1_DISP_RW                                    */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 22 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 23 UNKNOWN                                         */
    (U1)ALERT_REQ_C_ECB_LERNING2,                                              /* 24 LERNING2                                        */
    (U1)ALERT_REQ_C_ECB_LNG2_RW,                                               /* 25 LNG2_RW                                         */
    (U1)ALERT_REQ_C_ECB_LNG2_DISP,                                             /* 26 LNG2_DISP                                       */
    (U1)ALERT_REQ_C_ECB_LNG2_DISP_RW,                                          /* 27 LNG2_DISP_RW                                    */
    (U1)ALERT_REQ_C_ECB_LNG2_DISP_RW,                                          /* 28 LNG2_DISP_RW                                    */
    (U1)ALERT_REQ_C_ECB_LNG2_DISP_RW,                                          /* 29 LNG2_DISP_RW                                    */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 30 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 31 UNKNOWN                                         */
    (U1)ALERT_REQ_C_ECB_MALFUNC,                                               /* 32 MALFUNC                                         */
    (U1)ALERT_REQ_C_ECB_MFNC_RW,                                               /* 33 MFNC_RW                                         */
    (U1)ALERT_REQ_C_ECB_MFNC_DISP,                                             /* 34 MFNC_DISP                                       */
    (U1)ALERT_REQ_C_ECB_MFNC_DISP_RW,                                          /* 35 MFNC_DISP_RW                                    */
    (U1)ALERT_REQ_C_ECB_MFNC_DISP_RW,                                          /* 36 MFNC_DISP_RW                                    */
    (U1)ALERT_REQ_C_ECB_MFNC_DISP_RW,                                          /* 37 MFNC_DISP_RW                                    */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 38 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 39 UNKNOWN                                         */
    (U1)ALERT_REQ_C_ECB_UNAVAILABL,                                            /* 40 UNAVAILABL                                      */
    (U1)ALERT_REQ_C_ECB_UNABL_RW,                                              /* 41 UNABL_RW                                        */
    (U1)ALERT_REQ_C_ECB_UNABL_DISP,                                            /* 42 UNABL_DISP                                      */
    (U1)ALERT_REQ_C_ECB_UNABL_DISP_RW,                                         /* 43 UNABL_DISP_RW                                   */
    (U1)ALERT_REQ_C_ECB_UNABL_DISP_RW,                                         /* 44 UNABL_DISP_RW                                   */
    (U1)ALERT_REQ_C_ECB_UNABL_DISP_RW,                                         /* 45 UNABL_DISP_RW                                   */
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

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_C_ECB_MTRX[1] = {
    {
        &u4_s_AlertC_ecbSrcchk,                                                /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertC_ecbRwTx,                                                  /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_ECB_DST[0],                                             /* u1p_DST                                            */
        (U2)ALERT_C_ECB_NUM_DST,                                               /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_ecbSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_ecbSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_sp_ALERT_C_ECB_TT_JDG[ALERT_C_ECB_TT_JDG_NUM] = {
        (U1)ALERT_C_ECB_TT_JDG_UNKNOWN,
        (U1)ALERT_C_ECB_TT_JDG_TESTMODE,
        (U1)ALERT_C_ECB_TT_JDG_LERNING1,
        (U1)ALERT_C_ECB_TT_JDG_LERNING2,
        (U1)ALERT_C_ECB_TT_JDG_MALFUNC,
        (U1)ALERT_C_ECB_TT_JDG_UNAVAILBL,
        (U1)ALERT_C_ECB_TT_JDG_UNKNOWN,
        (U1)ALERT_C_ECB_TT_JDG_UNKNOWN,
        (U1)ALERT_C_ECB_TT_JDG_TESTMODE,
        (U1)ALERT_C_ECB_TT_JDG_TESTMODE,
        (U1)ALERT_C_ECB_TT_JDG_LERNING1,
        (U1)ALERT_C_ECB_TT_JDG_LERNING2,
        (U1)ALERT_C_ECB_TT_JDG_MALFUNC,
        (U1)ALERT_C_ECB_TT_JDG_UNAVAILBL,
        (U1)ALERT_C_ECB_TT_JDG_UNKNOWN,
        (U1)ALERT_C_ECB_TT_JDG_UNKNOWN,
        (U1)ALERT_C_ECB_TT_JDG_LERNING1,
        (U1)ALERT_C_ECB_TT_JDG_LERNING1,
        (U1)ALERT_C_ECB_TT_JDG_LERNING1,
        (U1)ALERT_C_ECB_TT_JDG_LERNING2,
        (U1)ALERT_C_ECB_TT_JDG_LERNING1,
        (U1)ALERT_C_ECB_TT_JDG_UNAVAILBL,
        (U1)ALERT_C_ECB_TT_JDG_UNKNOWN,
        (U1)ALERT_C_ECB_TT_JDG_UNKNOWN,
        (U1)ALERT_C_ECB_TT_JDG_LERNING2,
        (U1)ALERT_C_ECB_TT_JDG_LERNING2,
        (U1)ALERT_C_ECB_TT_JDG_LERNING2,
        (U1)ALERT_C_ECB_TT_JDG_LERNING2,
        (U1)ALERT_C_ECB_TT_JDG_LERNING2,
        (U1)ALERT_C_ECB_TT_JDG_UNAVAILBL,
        (U1)ALERT_C_ECB_TT_JDG_UNKNOWN,
        (U1)ALERT_C_ECB_TT_JDG_UNKNOWN,
        (U1)ALERT_C_ECB_TT_JDG_MALFUNC,
        (U1)ALERT_C_ECB_TT_JDG_MALFUNC,
        (U1)ALERT_C_ECB_TT_JDG_LERNING1,
        (U1)ALERT_C_ECB_TT_JDG_LERNING2,
        (U1)ALERT_C_ECB_TT_JDG_MALFUNC,
        (U1)ALERT_C_ECB_TT_JDG_UNAVAILBL,
        (U1)ALERT_C_ECB_TT_JDG_UNKNOWN,
        (U1)ALERT_C_ECB_TT_JDG_UNKNOWN,
        (U1)ALERT_C_ECB_TT_JDG_UNAVAILBL,
        (U1)ALERT_C_ECB_TT_JDG_UNAVAILBL,
        (U1)ALERT_C_ECB_TT_JDG_UNAVAILBL,
        (U1)ALERT_C_ECB_TT_JDG_UNAVAILBL,
        (U1)ALERT_C_ECB_TT_JDG_UNAVAILBL,
        (U1)ALERT_C_ECB_TT_JDG_UNAVAILBL
    };

    static const U1 u1_sp_ALERT_C_ECB_MID_JDG[ALERT_C_ECB_MID_JDG_NUM] = {
        (U1)ALERT_C_ECB_MID_JDG_UNKNOWN,
        (U1)ALERT_C_ECB_MID_JDG_UNKNOWN,
        (U1)ALERT_C_ECB_MID_JDG_UNKNOWN,
        (U1)ALERT_C_ECB_MID_JDG_UNKNOWN,
        (U1)ALERT_C_ECB_MID_JDG_FAILDISP,
        (U1)ALERT_C_ECB_MID_JDG_FAILDISP_RW,
        (U1)ALERT_C_ECB_MID_JDG_FAILDISP,
        (U1)ALERT_C_ECB_MID_JDG_FAILDISP_RW,
        (U1)ALERT_C_ECB_MID_JDG_FAILDISP,
        (U1)ALERT_C_ECB_MID_JDG_FAILDISP,
        (U1)ALERT_C_ECB_MID_JDG_FAILDISP_RW,
        (U1)ALERT_C_ECB_MID_JDG_FAILDISP_RW,
        (U1)ALERT_C_ECB_MID_JDG_FAILDISP,
        (U1)ALERT_C_ECB_MID_JDG_FAILDISP_RW,
        (U1)ALERT_C_ECB_MID_JDG_FAILDISP_RW,
        (U1)ALERT_C_ECB_MID_JDG_FAILDISP_RW
    };

    static const U1 u1_sp_ALERT_C_ECB_TT_RW_JDG[ALERT_C_ECB_TT_RW_JDG_NUM] = {
        (U1)ALERT_C_ECB_TT_RW_OFF,
        (U1)ALERT_C_ECB_TT_RW_OFF,
        (U1)ALERT_C_ECB_TT_RW_OFF,
        (U1)ALERT_C_ECB_TT_RW_OFF,
        (U1)ALERT_C_ECB_TT_RW_OFF,
        (U1)ALERT_C_ECB_TT_RW_ON,
        (U1)ALERT_C_ECB_TT_RW_OFF,
        (U1)ALERT_C_ECB_TT_RW_ON,
        (U1)ALERT_C_ECB_TT_RW_OFF,
        (U1)ALERT_C_ECB_TT_RW_OFF,
        (U1)ALERT_C_ECB_TT_RW_ON,
        (U1)ALERT_C_ECB_TT_RW_ON,
        (U1)ALERT_C_ECB_TT_RW_OFF,
        (U1)ALERT_C_ECB_TT_RW_ON,
        (U1)ALERT_C_ECB_TT_RW_ON,
        (U1)ALERT_C_ECB_TT_RW_ON
    };

#if defined(OXCAN_PDU_RX_CAN_VSC1S95) && (defined(ComConf_ComSignal_B_EBW) || defined(ComConf_ComSignal_DDRTWV) || defined(ComConf_ComSignal_EBW_MID))
    static const U2 u2_s_ALERT_C_ECB_TO_THRESH95   = ((U2)1000U / (U2)OXCAN_MAIN_TICK);
#endif /* defined(OXCAN_PDU_RX_CAN_VSC1S95) && (defined(ComConf_ComSignal_B_EBW) || defined(ComConf_ComSignal_DDRTWV) || ComConf_ComSignal_EBW_MID) */
#if defined(OXCAN_PDU_RX_CAN_VSC1S97) && (defined(ComConf_ComSignal_B_EBW2) || defined(ComConf_ComSignal_DDRTWV2) || defined(ComConf_ComSignal_EBW_MID2))
    static const U2 u2_s_ALERT_C_ECB_TO_THRESH97   = ((U2)1000U / (U2)OXCAN_MAIN_TICK);
#endif /* defined(OXCAN_PDU_RX_CAN_VSC1S97) && (defined(ComConf_ComSignal_B_EBW2) || defined(ComConf_ComSignal_DDRTWV2) || ComConf_ComSignal_EBW_MID2) */
    static const U1 u1_s_ALERT_C_ECB_LSB_TT_SGNL   = (U1)3U;
    static const U1 u1_s_ALERT_C_ECB_LSB_MID_SGNL  = (U1)3U;
    static const U1 u1_s_ALERT_C_ECB_LSB_MID2_SGNL = (U1)2U;
    static const U1 u1_s_ALERT_C_ECB_LSB_RW_SGNL   = (U1)1U;
    static const U1 u1_s_ALERT_C_ECB_LSB_TT_JDG    = (U1)3U;
    static const U1 u1_s_ALERT_C_ECB_LSB_MID_JDG   = (U1)1U;
    U1              u1_t_vsc1s95_msgsts;
    U1              u1_t_vsc1s97_msgsts;
    U1              u1_t_b_ebw_jdg;
    U1              u1_t_b_ebw2_jdg;
    U1              u1_t_b_ebw_rw_jdg;
    U1              u1_t_b_ebw2_rw_jdg;
    U1              u1_t_ebw_mid_jdg;
    U1              u1_t_ebw_mid2_jdg;
    U1              u1_t_ddrtwv_jdg;
    U1              u1_t_ddrtwv2_jdg;
    U1              u1_t_tt_sts;
    U1              u1_t_tt_jdg;
    U1              u1_t_mid_sts;
    U1              u1_t_mid_jdg;
    U1              u1_t_tt_rw_sts;
    U1              u1_t_tt_rw_jdg;
    U4              u4_t_src_chk;

#if defined(OXCAN_PDU_RX_CAN_VSC1S95) && (defined(ComConf_ComSignal_B_EBW) || defined(ComConf_ComSignal_DDRTWV) || defined(ComConf_ComSignal_EBW_MID))
    u1_t_vsc1s95_msgsts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_VSC1S95,
                                                (U2)OXCAN_RX_SYS_NRX_POE | (U2)OXCAN_RX_SYS_TOE_POE,
                                                u2_s_ALERT_C_ECB_TO_THRESH95) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#else
    u1_t_vsc1s95_msgsts = (U1)COM_NO_RX;
#endif /* defined(OXCAN_PDU_RX_CAN_VSC1S95) && (defined(ComConf_ComSignal_B_EBW) || defined(ComConf_ComSignal_DDRTWV) || ComConf_ComSignal_EBW_MID) */

#if defined(OXCAN_PDU_RX_CAN_VSC1S97) && (defined(ComConf_ComSignal_B_EBW2) || defined(ComConf_ComSignal_DDRTWV2) || defined(ComConf_ComSignal_EBW_MID2))
    u1_t_vsc1s97_msgsts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_VSC1S97,
                                                (U2)OXCAN_RX_SYS_NRX_POE | (U2)OXCAN_RX_SYS_TOE_POE,
                                                u2_s_ALERT_C_ECB_TO_THRESH97) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#else
    u1_t_vsc1s97_msgsts = (U1)COM_NO_RX;
#endif /* defined(OXCAN_PDU_RX_CAN_VSC1S97) && (defined(ComConf_ComSignal_B_EBW2) || defined(ComConf_ComSignal_DDRTWV2) || ComConf_ComSignal_EBW_MID2) */

    u1_t_b_ebw_jdg      = (U1)ALERT_C_ECB_B_EBW_UNKNOWN;
    u1_t_b_ebw2_jdg     = (U1)ALERT_C_ECB_B_EBW_UNKNOWN;
    u1_t_b_ebw_rw_jdg   = (U1)0U;
    u1_t_b_ebw2_rw_jdg  = (U1)0U;
    vd_s_AlertC_ecb_b_ebw_jdg(u1_t_vsc1s95_msgsts,   &u1_t_b_ebw_jdg,  &u1_t_b_ebw_rw_jdg,
                              u1_t_vsc1s97_msgsts,   &u1_t_b_ebw2_jdg, &u1_t_b_ebw2_rw_jdg);

    u1_t_ebw_mid_jdg    = (U1)ALERT_C_ECB_EBW_MID_UNKNOWN;
    u1_t_ebw_mid2_jdg   = (U1)ALERT_C_ECB_EBW_MID_UNKNOWN;
    vd_s_AlertC_ecb_ebw_mid_jdg(u1_t_vsc1s95_msgsts, &u1_t_ebw_mid_jdg,
                                u1_t_vsc1s97_msgsts, &u1_t_ebw_mid2_jdg);

    u1_t_ddrtwv_jdg     = (U1)ALERT_C_ECB_DDRTWV_RW_OFF;
    u1_t_ddrtwv2_jdg    = (U1)ALERT_C_ECB_DDRTWV_RW_OFF;
    vd_s_AlertC_ecb_ddrtwv_jdg(u1_t_vsc1s95_msgsts,  &u1_t_ddrtwv_jdg,
                               u1_t_vsc1s97_msgsts,  &u1_t_ddrtwv2_jdg);

    u1_t_tt_sts         = ((U1)(u1_t_b_ebw_jdg   << u1_s_ALERT_C_ECB_LSB_TT_SGNL ) | u1_t_b_ebw2_jdg);
    u1_t_tt_jdg         = u1_sp_ALERT_C_ECB_TT_JDG[u1_t_tt_sts];

    u1_t_mid_sts        = ((U1)(u1_t_ddrtwv_jdg  << u1_s_ALERT_C_ECB_LSB_RW_SGNL ) | u1_t_ddrtwv2_jdg   |
                           (U1)(u1_t_ebw_mid_jdg << u1_s_ALERT_C_ECB_LSB_MID_SGNL) | (U1)(u1_t_ebw_mid2_jdg << u1_s_ALERT_C_ECB_LSB_MID2_SGNL));
    u1_t_mid_jdg        = u1_sp_ALERT_C_ECB_MID_JDG[u1_t_mid_sts];

    u1_t_tt_rw_sts      = (u1_t_b_ebw_rw_jdg                                       | u1_t_b_ebw2_rw_jdg |
                           (U1)(u1_t_ddrtwv_jdg  << u1_s_ALERT_C_ECB_LSB_RW_SGNL ) | u1_t_ddrtwv2_jdg);
    u1_t_tt_rw_jdg      = u1_sp_ALERT_C_ECB_TT_RW_JDG[u1_t_tt_rw_sts];

    u4_t_src_chk        = (((U4)u1_t_tt_jdg      << u1_s_ALERT_C_ECB_LSB_TT_JDG)   | ((U4)u1_t_mid_jdg      << u1_s_ALERT_C_ECB_LSB_MID_JDG) | (U4)u1_t_tt_rw_jdg);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertC_ecb_b_ebw_jdg(const U1 u1_a_MSGSTS95,  U1 * u1_ap_b_ebw_jdg,  U1 * u1_ap_b_ebw_rw_jdg,                */
/*                                           const U1 u1_a_MSGSTS97,  U1 * u1_ap_b_ebw2_jdg, U1 * u1_ap_b_ebw2_rw_jdg)               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertC_ecb_b_ebw_jdg(const U1 u1_a_MSGSTS95,  U1 * u1_ap_b_ebw_jdg,  U1 * u1_ap_b_ebw_rw_jdg,
                                         const U1 u1_a_MSGSTS97,  U1 * u1_ap_b_ebw2_jdg, U1 * u1_ap_b_ebw2_rw_jdg)
{
#if defined(ComConf_ComSignal_B_EBW) || defined(ComConf_ComSignal_B_EBW2)
    static const U1 u1_sp_ALERT_C_ECB_B_EBW_JDG[ALERT_C_ECB_B_EBW_JDG_NUM] = {
        (U1)ALERT_C_ECB_B_EBW_UNKNOWN,
        (U1)ALERT_C_ECB_B_EBW_TESTMODE,
        (U1)ALERT_C_ECB_B_EBW_LERNING1,
        (U1)ALERT_C_ECB_B_EBW_LERNING2,
        (U1)ALERT_C_ECB_B_EBW_UNKNOWN,
        (U1)ALERT_C_ECB_B_EBW_UNKNOWN,
        (U1)ALERT_C_ECB_B_EBW_MALFUNC,
        (U1)ALERT_C_ECB_B_EBW_UNAVAILBL,
        (U1)ALERT_C_ECB_B_EBW_UNKNOWN,
        (U1)ALERT_C_ECB_B_EBW_UNKNOWN,
        (U1)ALERT_C_ECB_B_EBW_UNKNOWN,
        (U1)ALERT_C_ECB_B_EBW_UNKNOWN,
        (U1)ALERT_C_ECB_B_EBW_UNKNOWN,
        (U1)ALERT_C_ECB_B_EBW_UNKNOWN,
        (U1)ALERT_C_ECB_B_EBW_UNKNOWN,
        (U1)ALERT_C_ECB_B_EBW_UNKNOWN,
        (U1)ALERT_C_ECB_B_EBW_MALFUNC,
        (U1)ALERT_C_ECB_B_EBW_MALFUNC,
        (U1)ALERT_C_ECB_B_EBW_MALFUNC,
        (U1)ALERT_C_ECB_B_EBW_MALFUNC,
        (U1)ALERT_C_ECB_B_EBW_MALFUNC,
        (U1)ALERT_C_ECB_B_EBW_MALFUNC,
        (U1)ALERT_C_ECB_B_EBW_MALFUNC,
        (U1)ALERT_C_ECB_B_EBW_MALFUNC,
        (U1)ALERT_C_ECB_B_EBW_MALFUNC,
        (U1)ALERT_C_ECB_B_EBW_MALFUNC,
        (U1)ALERT_C_ECB_B_EBW_MALFUNC,
        (U1)ALERT_C_ECB_B_EBW_MALFUNC,
        (U1)ALERT_C_ECB_B_EBW_MALFUNC,
        (U1)ALERT_C_ECB_B_EBW_MALFUNC,
        (U1)ALERT_C_ECB_B_EBW_MALFUNC,
        (U1)ALERT_C_ECB_B_EBW_MALFUNC
    };
    static const U1 u1_s_ALERT_C_ECB_LSB_TT_MSGSTS = (U1)3U;
    U1              u1_t_sgnl;
#endif /* defined(ComConf_ComSignal_B_EBW) || defined(ComConf_ComSignal_B_EBW2) */
    static const U1 u1_s_ALERT_C_ECB_TT_RW_MASK    = (U1)0x04U;
    static const U1 u1_s_ALERT_C_ECB_B_EBW_RW_ON   = (U1)0x08U;
    static const U1 u1_s_ALERT_C_ECB_B_EBW2_RW_ON  = (U1)0x04U;
#ifdef ComConf_ComSignal_B_EBW
    U1              u1_t_b_ebw_sts;
#endif /* ComConf_ComSignal_B_EBW */
#ifdef ComConf_ComSignal_B_EBW2
    U1              u1_t_b_ebw2_sts;
#endif /* ComConf_ComSignal_B_EBW2 */

#if defined(ComConf_ComSignal_B_EBW)
    u1_t_sgnl         = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_EBW, &u1_t_sgnl);
    u1_t_b_ebw_sts    = (u1_t_sgnl | (U1)(u1_a_MSGSTS95 << u1_s_ALERT_C_ECB_LSB_TT_MSGSTS));
    *u1_ap_b_ebw_jdg  = u1_sp_ALERT_C_ECB_B_EBW_JDG[u1_t_b_ebw_sts];
#else
    *u1_ap_b_ebw_jdg  = (U1)ALERT_C_ECB_B_EBW_UNKNOWN;
#endif /* defined(ComConf_ComSignal_B_EBW) */

#if defined(ComConf_ComSignal_B_EBW2)
    u1_t_sgnl         = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_EBW2, &u1_t_sgnl);
    u1_t_b_ebw2_sts   = (u1_t_sgnl | (U1)(u1_a_MSGSTS97 << u1_s_ALERT_C_ECB_LSB_TT_MSGSTS));
    *u1_ap_b_ebw2_jdg = u1_sp_ALERT_C_ECB_B_EBW_JDG[u1_t_b_ebw2_sts];
#else
    *u1_ap_b_ebw2_jdg = (U1)ALERT_C_ECB_B_EBW_UNKNOWN;
#endif /* defined(ComConf_ComSignal_B_EBW2) */

    if((*u1_ap_b_ebw_jdg  & u1_s_ALERT_C_ECB_TT_RW_MASK) != (U1)0U){
        *u1_ap_b_ebw_rw_jdg  = u1_s_ALERT_C_ECB_B_EBW_RW_ON;
    }
    if((*u1_ap_b_ebw2_jdg & u1_s_ALERT_C_ECB_TT_RW_MASK) != (U1)0U){
        *u1_ap_b_ebw2_rw_jdg = u1_s_ALERT_C_ECB_B_EBW2_RW_ON;
    }
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertC_ecb_ebw_mid_jdg(const U1 u1_a_MSGSTS95, U1 * u1_ap_ebw_mid_jdg,                                       */
/*                                             const U1 u1_a_MSGSTS97, U1 * u1_ap_ebw_mid2_jdg)                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertC_ecb_ebw_mid_jdg(const U1 u1_a_MSGSTS95, U1 * u1_ap_ebw_mid_jdg,
                                           const U1 u1_a_MSGSTS97, U1 * u1_ap_ebw_mid2_jdg)
{
#if defined(ComConf_ComSignal_EBW_MID) || defined(ComConf_ComSignal_EBW_MID2)
    static const U1 u1_sp_ALERT_C_ECB_EBW_MID_JDG[ALERT_C_ECB_EBW_MID_JDG_NUM] = {
        (U1)ALERT_C_ECB_EBW_MID_UNKNOWN,
        (U1)ALERT_C_ECB_EBW_MID_FAILDISP,
        (U1)ALERT_C_ECB_EBW_MID_UNKNOWN,
        (U1)ALERT_C_ECB_EBW_MID_UNKNOWN,
        (U1)ALERT_C_ECB_EBW_MID_FAILDISP,
        (U1)ALERT_C_ECB_EBW_MID_FAILDISP,
        (U1)ALERT_C_ECB_EBW_MID_FAILDISP,
        (U1)ALERT_C_ECB_EBW_MID_FAILDISP
    };
    static const U1 u1_s_ALERT_C_ECB_LSB_MID_MSGSTS = (U1)1U;
    U1              u1_t_sgnl;
#endif /* defined(ComConf_ComSignal_EBW_MID) || defined(ComConf_ComSignal_EBW_MID2) */
#ifdef ComConf_ComSignal_EBW_MID
    U1              u1_t_mid_sts;
#endif /* ComConf_ComSignal_EBW_MID */
#ifdef ComConf_ComSignal_EBW_MID2
    U1              u1_t_mid2_sts;
#endif /* ComConf_ComSignal_EBW_MID2 */

#if defined(ComConf_ComSignal_EBW_MID)
    u1_t_sgnl           = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_EBW_MID, &u1_t_sgnl);
    u1_t_mid_sts        = (u1_t_sgnl | (U1)(u1_a_MSGSTS95 << u1_s_ALERT_C_ECB_LSB_MID_MSGSTS));
    *u1_ap_ebw_mid_jdg  = u1_sp_ALERT_C_ECB_EBW_MID_JDG[u1_t_mid_sts];
#else
    *u1_ap_ebw_mid_jdg  = (U1)ALERT_C_ECB_EBW_MID_UNKNOWN;
#endif /* defined(ComConf_ComSignal_EBW_MID) */

#if defined(ComConf_ComSignal_EBW_MID2)
    u1_t_sgnl           = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_EBW_MID2, &u1_t_sgnl);
    u1_t_mid2_sts       = (u1_t_sgnl | (U1)(u1_a_MSGSTS97 << u1_s_ALERT_C_ECB_LSB_MID_MSGSTS));
    *u1_ap_ebw_mid2_jdg = u1_sp_ALERT_C_ECB_EBW_MID_JDG[u1_t_mid2_sts];
#else
    *u1_ap_ebw_mid2_jdg = (U1)ALERT_C_ECB_EBW_MID_UNKNOWN;
#endif /* defined(ComConf_ComSignal_EBW_MID2) */
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertC_ecb_ddrtwv_jdg(const U1 u1_a_MSGSTS95, U1 * u1_ap_ddrtwv_jdg,                                         */
/*                                            const U1 u1_a_MSGSTS97, U1 * u1_ap_ddrtwv2_jdg)                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertC_ecb_ddrtwv_jdg(const U1 u1_a_MSGSTS95, U1 * u1_ap_ddrtwv_jdg,
                                          const U1 u1_a_MSGSTS97, U1 * u1_ap_ddrtwv2_jdg)
{
    static const U1 u1_sp_ALERT_C_ECB_DDRTWV_JDG[ALERT_C_ECB_DDRTWV_JDG_NUM] = {
        (U1)ALERT_C_ECB_DDRTWV_RW_OFF,
        (U1)ALERT_C_ECB_DDRTWV_RW_ON,
        (U1)ALERT_C_ECB_DDRTWV_RW_OFF,
        (U1)ALERT_C_ECB_DDRTWV_RW_OFF,
        (U1)ALERT_C_ECB_DDRTWV_RW_ON,
        (U1)ALERT_C_ECB_DDRTWV_RW_ON,
        (U1)ALERT_C_ECB_DDRTWV_RW_ON,
        (U1)ALERT_C_ECB_DDRTWV_RW_ON
    };
    static const U1 u1_s_ALERT_C_ECB_LSB_RW_MSGSTS = (U1)1U;
    U1              u1_t_sgnl;
#if defined(ComConf_ComSignal_DDRTWV)
    U1              u1_t_ddrtwv_sts;
#endif /* defined(ComConf_ComSignal_DDRTWV) */
#if defined(ComConf_ComSignal_DDRTWV2)
    U1              u1_t_ddrtwv2_sts;
#endif /* defined(ComConf_ComSignal_DDRTWV2) */

#if defined(ComConf_ComSignal_DDRTWV)
    u1_t_sgnl          = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_DDRTWV, &u1_t_sgnl);
    u1_t_ddrtwv_sts    = (u1_t_sgnl | (U1)(u1_a_MSGSTS95 << u1_s_ALERT_C_ECB_LSB_RW_MSGSTS));
    *u1_ap_ddrtwv_jdg  = u1_sp_ALERT_C_ECB_DDRTWV_JDG[u1_t_ddrtwv_sts];
#else
    *u1_ap_ddrtwv_jdg  = (U1)ALERT_C_ECB_DDRTWV_RW_OFF;
#endif /* defined(ComConf_ComSignal_DDRTWV) */

#if defined(ComConf_ComSignal_DDRTWV2)
    u1_t_sgnl          = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_DDRTWV2, &u1_t_sgnl);
    u1_t_ddrtwv2_sts   = (u1_t_sgnl | (U1)(u1_a_MSGSTS97 << u1_s_ALERT_C_ECB_LSB_RW_MSGSTS));
    *u1_ap_ddrtwv2_jdg = u1_sp_ALERT_C_ECB_DDRTWV_JDG[u1_t_ddrtwv2_sts];
#else
    *u1_ap_ddrtwv2_jdg = (U1)ALERT_C_ECB_DDRTWV_RW_OFF;
#endif /* defined(ComConf_ComSignal_DDRTWV2) */
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertC_ecbRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertC_ecbRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    static const U4 u4_s_ALERT_C_ECB_RWTX_CRT = ((U4)((U4)1U << ALERT_REQ_C_ECB_FDISP_RW     )
                                               | (U4)((U4)1U << ALERT_REQ_C_ECB_TM_DISP_RW   )
                                               | (U4)((U4)1U << ALERT_REQ_C_ECB_LNG1_RW      )
                                               | (U4)((U4)1U << ALERT_REQ_C_ECB_LNG1_DISP_RW )
                                               | (U4)((U4)1U << ALERT_REQ_C_ECB_LNG2_RW      )
                                               | (U4)((U4)1U << ALERT_REQ_C_ECB_LNG2_DISP_RW )
                                               | (U4)((U4)1U << ALERT_REQ_C_ECB_MFNC_RW      )
                                               | (U4)((U4)1U << ALERT_REQ_C_ECB_MFNC_DISP_RW )
                                               | (U4)((U4)1U << ALERT_REQ_C_ECB_UNABL_RW     )
                                               | (U4)((U4)1U << ALERT_REQ_C_ECB_UNABL_DISP_RW));
    static const U1 u1_s_ALERT_C_ECB_RWTX_MSK = (U1)0x1FU;
    U1              u1_t_sgnl;
    U4              u4_t_rw;

    u4_t_rw = ((U4)1U << (u1_a_DST & u1_s_ALERT_C_ECB_RWTX_MSK));
    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN)      != (U1)0U) &&
       ((u4_t_rw  & u4_s_ALERT_C_ECB_RWTX_CRT) != (U4)0U)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_ECBW, &u1_t_sgnl);
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
/*                                                                                                                                   */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * KT   = Kenichi Takahashi, NTTD MSE                                                                                             */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*  * HU   = Hidekazu Usui, NTTD MSE                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
