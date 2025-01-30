/* 5.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert P_TECOLP2                                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_P_TECOLP2_C_MAJOR                  (5)
#define ALERT_P_TECOLP2_C_MINOR                  (4)
#define ALERT_P_TECOLP2_C_PATCH                  (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_P_TECOLP2_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_P_TECOLP2.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_P_TECOLP2_NUM_DST                  (32U)

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
static U4      u4_s_AlertP_tecolp2Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_P_TECOLP2_DST[ALERT_P_TECOLP2_NUM_DST] = {
    (U1)ALERT_REQ_P_TECOLP2_ECOLP_ON,                                          /* 00 ECOLP_ON                                        */
    (U1)ALERT_REQ_P_TECOLP2_ECOLP_ON,                                          /* 01 ECOLP_ON                                        */
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
    (U1)ALERT_REQ_UNKNOWN                                                      /* 31 UNKNOWN                                         */
};
static const U4  u4_sp_ALERT_P_TECOLP2_MASK[ALERT_P_TECOLP2_NUM_DST] = {
    (U4)0x0000000FU,                                                           /* 00 ECOLP_ON                                        */
    (U4)0x000000F0U,                                                           /* 01 ECOLP_ON                                        */
    (U4)0x0000000FU,                                                           /* 02 UNKNOWN                                         */
    (U4)0x0000000FU,                                                           /* 03 UNKNOWN                                         */
    (U4)0x0000000FU,                                                           /* 04 UNKNOWN                                         */
    (U4)0x0000000FU,                                                           /* 05 UNKNOWN                                         */
    (U4)0x0000000FU,                                                           /* 06 UNKNOWN                                         */
    (U4)0x0000000FU,                                                           /* 07 UNKNOWN                                         */
    (U4)0x0000000FU,                                                           /* 08 UNKNOWN                                         */
    (U4)0x0000000FU,                                                           /* 09 UNKNOWN                                         */
    (U4)0x0000000FU,                                                           /* 10 UNKNOWN                                         */
    (U4)0x0000000FU,                                                           /* 11 UNKNOWN                                         */
    (U4)0x0000000FU,                                                           /* 12 UNKNOWN                                         */
    (U4)0x0000000FU,                                                           /* 13 UNKNOWN                                         */
    (U4)0x0000000FU,                                                           /* 14 UNKNOWN                                         */
    (U4)0x0000000FU,                                                           /* 15 UNKNOWN                                         */
    (U4)0x0000000FU,                                                           /* 16 UNKNOWN                                         */
    (U4)0x000000F0U,                                                           /* 17 UNKNOWN                                         */
    (U4)0x000000F0U,                                                           /* 18 UNKNOWN                                         */
    (U4)0x000000F0U,                                                           /* 19 UNKNOWN                                         */
    (U4)0x000000F0U,                                                           /* 20 UNKNOWN                                         */
    (U4)0x000000F0U,                                                           /* 21 UNKNOWN                                         */
    (U4)0x000000F0U,                                                           /* 22 UNKNOWN                                         */
    (U4)0x000000F0U,                                                           /* 23 UNKNOWN                                         */
    (U4)0x000000F0U,                                                           /* 24 UNKNOWN                                         */
    (U4)0x000000F0U,                                                           /* 25 UNKNOWN                                         */
    (U4)0x000000F0U,                                                           /* 26 UNKNOWN                                         */
    (U4)0x000000F0U,                                                           /* 27 UNKNOWN                                         */
    (U4)0x000000F0U,                                                           /* 28 UNKNOWN                                         */
    (U4)0x000000F0U,                                                           /* 29 UNKNOWN                                         */
    (U4)0x000000F0U,                                                           /* 30 UNKNOWN                                         */
    (U4)0x000000F0U                                                            /* 31 UNKNOWN                                         */
};
static const U4  u4_sp_ALERT_P_TECOLP2_CRIT[ALERT_P_TECOLP2_NUM_DST] = {
    (U4)0x00000003U,                                                           /* 00 ECOLP_ON                                        */
    (U4)0x00000030U,                                                           /* 01 ECOLP_ON                                        */
    (U4)0x00000000U,                                                           /* 02 UNKNOWN                                         */
    (U4)0x00000001U,                                                           /* 03 UNKNOWN                                         */
    (U4)0x00000002U,                                                           /* 04 UNKNOWN                                         */
    (U4)0x00000004U,                                                           /* 05 UNKNOWN                                         */
    (U4)0x00000005U,                                                           /* 06 UNKNOWN                                         */
    (U4)0x00000006U,                                                           /* 07 UNKNOWN                                         */
    (U4)0x00000007U,                                                           /* 08 UNKNOWN                                         */
    (U4)0x00000008U,                                                           /* 09 UNKNOWN                                         */
    (U4)0x00000009U,                                                           /* 10 UNKNOWN                                         */
    (U4)0x0000000AU,                                                           /* 11 UNKNOWN                                         */
    (U4)0x0000000BU,                                                           /* 12 UNKNOWN                                         */
    (U4)0x0000000CU,                                                           /* 13 UNKNOWN                                         */
    (U4)0x0000000DU,                                                           /* 14 UNKNOWN                                         */
    (U4)0x0000000EU,                                                           /* 15 UNKNOWN                                         */
    (U4)0x0000000FU,                                                           /* 16 UNKNOWN                                         */
    (U4)0x00000000U,                                                           /* 17 UNKNOWN                                         */
    (U4)0x00000010U,                                                           /* 18 UNKNOWN                                         */
    (U4)0x00000020U,                                                           /* 19 UNKNOWN                                         */
    (U4)0x00000040U,                                                           /* 20 UNKNOWN                                         */
    (U4)0x00000050U,                                                           /* 21 UNKNOWN                                         */
    (U4)0x00000060U,                                                           /* 22 UNKNOWN                                         */
    (U4)0x00000070U,                                                           /* 23 UNKNOWN                                         */
    (U4)0x00000080U,                                                           /* 24 UNKNOWN                                         */
    (U4)0x00000090U,                                                           /* 25 UNKNOWN                                         */
    (U4)0x000000A0U,                                                           /* 26 UNKNOWN                                         */
    (U4)0x000000B0U,                                                           /* 27 UNKNOWN                                         */
    (U4)0x000000C0U,                                                           /* 28 UNKNOWN                                         */
    (U4)0x000000D0U,                                                           /* 29 UNKNOWN                                         */
    (U4)0x000000E0U,                                                           /* 30 UNKNOWN                                         */
    (U4)0x000000F0U                                                            /* 31 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_P_TECOLP2_MTRX[1] = {
    {
        &u4_s_AlertP_tecolp2Srcchk,                                            /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_P_TECOLP2_MASK[0],                                        /* u4p_MASK                                           */
        &u4_sp_ALERT_P_TECOLP2_CRIT[0],                                        /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_TECOLP2_DST[0],                                         /* u1p_DST                                            */
        (U2)ALERT_P_TECOLP2_NUM_DST,                                           /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_tecolp2Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_tecolp2Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_P_TECOLP2_TO_B_ECO_THRESH = ((U2)3600U / (U2)OXCAN_MAIN_TICK);
    static const U2 u2_s_ALERT_P_TECOLP2_TO_IECO_THRESH  = ((U2)3600U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_P_ENG1G17_LSB_MSGSTS      = (U1)2U;
    static const U1 u1_s_ALERT_P_IECOHVST_LSB_SIGSTS     = (U1)4U;
    static const U1 u1_s_ALERT_P_EHV1F04_LSB_MSGSTS      = (U1)6U;

    U4              u4_t_src_chk;
    U1              u1_t_b_ecol_sgnl;
    U1              u1_t_iecohvst_sgnl;
    U1              u1_t_eng1g17_sts;
    U1              u1_t_ehv1f04_sts;

    u1_t_eng1g17_sts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1G17_02,
                                        (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                        u2_s_ALERT_P_TECOLP2_TO_B_ECO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_ehv1f04_sts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV1F04_31,
                                        (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                        u2_s_ALERT_P_TECOLP2_TO_IECO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_b_ecol_sgnl = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_ECOL, &u1_t_b_ecol_sgnl);

    u1_t_iecohvst_sgnl = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_IECOHVST, &u1_t_iecohvst_sgnl);

    u4_t_src_chk  = (U4)u1_t_b_ecol_sgnl;
    u4_t_src_chk |= ((U4)u1_t_eng1g17_sts   << u1_s_ALERT_P_ENG1G17_LSB_MSGSTS);
    u4_t_src_chk |= ((U4)u1_t_iecohvst_sgnl << u1_s_ALERT_P_IECOHVST_LSB_SIGSTS);
    u4_t_src_chk |= ((U4)u1_t_ehv1f04_sts   << u1_s_ALERT_P_EHV1F04_LSB_MSGSTS);

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
/*  5.0.0     3/ 2/2020  TI       New.                                                                                               */
/*  5.1.0    12/ 8/2020  SO       Update for 800B 1A(Version update).                                                                */
/*  5.1.1     3/25/2021  KT       Update how to get the Message Label.                                                               */
/*  5.2.0    10/28/2021  HU       Update for 840B 1A(Version update).                                                                */
/*  5.3.0     2/02/2024  DR       Update for 19PFv3.                                                                                 */
/*  5.4.0     3/01/2024  DR       Applied IECOHVST signal.                                                                           */
/*                                                                                                                                   */
/*  * TI   = Takuro Iwanaga, NTTD MSE                                                                                                */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*  * KT   = Kenichi Takahashi, NTTD MSE                                                                                             */
/*  * HU   = Hidekazu Usui, NTTD MSE                                                                                                 */
/*  * DR   = Dyan Reyes, DTPH                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
