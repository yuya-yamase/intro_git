/* 5.5.0 */
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
#define ALERT_C_ECB_C_MINOR                      (5)
#define ALERT_C_ECB_C_PATCH                      (0)

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
#define ALERT_C_ECB_NUM_DST                      (24U)

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

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_C_ECB_DST[ALERT_C_ECB_NUM_DST] = {
    (U1)ALERT_REQ_C_ECB_FAILDISP,                                              /* 00 FAILDISP                                        */
    (U1)ALERT_REQ_C_ECB_FDISP_RW,                                              /* 01 FDISP_RW                                        */
    (U1)ALERT_REQ_C_ECB_TESTMODE,                                              /* 02 TESTMODE                                        */
    (U1)ALERT_REQ_C_ECB_TM_DISP,                                               /* 03 TM_DISP                                         */
    (U1)ALERT_REQ_C_ECB_TM_DISP_RW,                                            /* 04 TM_DISP_RW                                      */
    (U1)ALERT_REQ_C_ECB_LERNING1,                                              /* 05 LERNING1                                        */
    (U1)ALERT_REQ_C_ECB_LNG1_DISP,                                             /* 06 LNG1_DISP                                       */
    (U1)ALERT_REQ_C_ECB_LNG1_DISP_RW,                                          /* 07 LNG1_DISP_RW                                    */
    (U1)ALERT_REQ_C_ECB_LERNING2,                                              /* 08 LERNING2                                        */
    (U1)ALERT_REQ_C_ECB_LNG2_DISP,                                             /* 09 LNG2_DISP                                       */
    (U1)ALERT_REQ_C_ECB_LNG2_DISP_RW,                                          /* 10 LNG2_DISP_RW                                    */
    (U1)ALERT_REQ_C_ECB_FAILDISP,                                              /* 11 FAILDISP                                        */
    (U1)ALERT_REQ_C_ECB_FDISP_RW,                                              /* 12 FDISP_RW                                        */
    (U1)ALERT_REQ_C_ECB_FAILDISP,                                              /* 13 FAILDISP                                        */
    (U1)ALERT_REQ_C_ECB_FDISP_RW,                                              /* 14 FDISP_RW                                        */
    (U1)ALERT_REQ_C_ECB_MALFUNC,                                               /* 15 MALFUNC                                         */
    (U1)ALERT_REQ_C_ECB_MFNC_RW,                                               /* 16 MFNC_RW                                         */
    (U1)ALERT_REQ_C_ECB_MFNC_DISP,                                             /* 17 MFNC_DISP                                       */
    (U1)ALERT_REQ_C_ECB_MFNC_DISP_RW,                                          /* 18 MFNC_DISP_RW                                    */
    (U1)ALERT_REQ_C_ECB_UNAVAILABL,                                            /* 19 UNAVAILABL                                      */
    (U1)ALERT_REQ_C_ECB_UNABL_RW,                                              /* 20 UNABL_RW                                        */
    (U1)ALERT_REQ_C_ECB_UNABL_DISP,                                            /* 21 UNABL_DISP                                      */
    (U1)ALERT_REQ_C_ECB_UNABL_DISP_RW,                                         /* 22 UNABL_DISP_RW                                   */
    (U1)ALERT_REQ_C_ECB_MFNC_DISP_RW                                           /* 23 MFNC_DISP_RW                                    */
};
static const U4  u4_sp_ALERT_C_ECB_CRIT[ALERT_C_ECB_NUM_DST] = {
    (U4)0x00000002U,                                                           /* 00 FAILDISP                                        */
    (U4)0x00000003U,                                                           /* 01 FDISP_RW                                        */
    (U4)0x00000004U,                                                           /* 02 TESTMODE                                        */
    (U4)0x00000006U,                                                           /* 03 TM_DISP                                         */
    (U4)0x00000007U,                                                           /* 04 TM_DISP_RW                                      */
    (U4)0x00000008U,                                                           /* 05 LERNING1                                        */
    (U4)0x0000000AU,                                                           /* 06 LNG1_DISP                                       */
    (U4)0x0000000BU,                                                           /* 07 LNG1_DISP_RW                                    */
    (U4)0x0000000CU,                                                           /* 08 LERNING2                                        */
    (U4)0x0000000EU,                                                           /* 09 LNG2_DISP                                       */
    (U4)0x0000000FU,                                                           /* 10 LNG2_DISP_RW                                    */
    (U4)0x00000012U,                                                           /* 11 FAILDISP                                        */
    (U4)0x00000013U,                                                           /* 12 FDISP_RW                                        */
    (U4)0x00000016U,                                                           /* 13 FAILDISP                                        */
    (U4)0x00000017U,                                                           /* 14 FDISP_RW                                        */
    (U4)0x00000018U,                                                           /* 15 MALFUNC                                         */
    (U4)0x00000019U,                                                           /* 16 MFNC_RW                                         */
    (U4)0x0000001AU,                                                           /* 17 MFNC_DISP                                       */
    (U4)0x0000001BU,                                                           /* 18 MFNC_DISP_RW                                    */
    (U4)0x0000001CU,                                                           /* 19 UNAVAILABL                                      */
    (U4)0x0000001DU,                                                           /* 20 UNABL_RW                                        */
    (U4)0x0000001EU,                                                           /* 21 UNABL_DISP                                      */
    (U4)0x0000001FU,                                                           /* 22 UNABL_DISP_RW                                   */
    (U4)0x00000040U                                                            /* 23 MFNC_DISP_RW                                    */
};
static const U4  u4_sp_ALERT_C_ECB_MASK[ALERT_C_ECB_NUM_DST] = {
    (U4)0x0000007FU,                                                           /* 00 FAILDISP                                        */
    (U4)0x0000007FU,                                                           /* 01 FDISP_RW                                        */
    (U4)0x0000007EU,                                                           /* 02 TESTMODE                                        */
    (U4)0x0000007FU,                                                           /* 03 TM_DISP                                         */
    (U4)0x0000007FU,                                                           /* 04 TM_DISP_RW                                      */
    (U4)0x0000007EU,                                                           /* 05 LERNING1                                        */
    (U4)0x0000007FU,                                                           /* 06 LNG1_DISP                                       */
    (U4)0x0000007FU,                                                           /* 07 LNG1_DISP_RW                                    */
    (U4)0x0000007EU,                                                           /* 08 LERNING2                                        */
    (U4)0x0000007FU,                                                           /* 09 LNG2_DISP                                       */
    (U4)0x0000007FU,                                                           /* 10 LNG2_DISP_RW                                    */
    (U4)0x0000007FU,                                                           /* 11 FAILDISP                                        */
    (U4)0x0000007FU,                                                           /* 12 FDISP_RW                                        */
    (U4)0x0000007FU,                                                           /* 13 FAILDISP                                        */
    (U4)0x0000007FU,                                                           /* 14 FDISP_RW                                        */
    (U4)0x0000007FU,                                                           /* 15 MALFUNC                                         */
    (U4)0x0000007FU,                                                           /* 16 MFNC_RW                                         */
    (U4)0x0000007FU,                                                           /* 17 MFNC_DISP                                       */
    (U4)0x0000007FU,                                                           /* 18 MFNC_DISP_RW                                    */
    (U4)0x0000007FU,                                                           /* 19 UNAVAILABL                                      */
    (U4)0x0000007FU,                                                           /* 20 UNABL_RW                                        */
    (U4)0x0000007FU,                                                           /* 21 UNABL_DISP                                      */
    (U4)0x0000007FU,                                                           /* 22 UNABL_DISP_RW                                   */
    (U4)0x00000040U                                                            /* 23 MFNC_DISP_RW                                    */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_C_ECB_MTRX[1] = {
    {
        &u4_s_AlertC_ecbSrcchk,                                                /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertC_ecbRwTx,                                                  /* fp_vd_XDST                                         */

        &u4_sp_ALERT_C_ECB_MASK[0],                                            /* u4p_MASK                                           */
        &u4_sp_ALERT_C_ECB_CRIT[0],                                            /* u4p_CRIT                                           */

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
#if defined(OXCAN_PDU_RX_CAN_DDM1S17_RXCH0) && (defined(ComConf_ComSignal_B_EBW) || defined(ComConf_ComSignal_DDRTWV) || defined(ComConf_ComSignal_EBW_MID))
    static const U2 u2_s_ALERT_C_ECB_TO_THRESH   = ((U2)1000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_C_ECB_LSB_EBW_MID  = (U1)1U;
    static const U1 u1_s_ALERT_C_ECB_LSB_B_EBW   = (U1)2U;
    static const U1 u1_s_ALERT_C_ECB_LSB_DDM1S17    = (U1)5U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl_ddrtwv;
    U1              u1_t_sgnl_ebw_mid;
    U1              u1_t_sgnl_b_ebw;
    U4              u4_t_src_chk;

    u1_t_msgsts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_DDM1S17_RXCH0,
                                                (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                                u2_s_ALERT_C_ECB_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl_ddrtwv     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_DDRTWV, &u1_t_sgnl_ddrtwv);

    u1_t_sgnl_ebw_mid    = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_EBW_MID, &u1_t_sgnl_ebw_mid);

    u1_t_sgnl_b_ebw      = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_EBW, &u1_t_sgnl_b_ebw);

    u4_t_src_chk         = (((U4)u1_t_msgsts        <<  u1_s_ALERT_C_ECB_LSB_DDM1S17)  |  ((U4)u1_t_sgnl_b_ebw  <<  u1_s_ALERT_C_ECB_LSB_B_EBW) |
                            ((U4)u1_t_sgnl_ebw_mid  <<  u1_s_ALERT_C_ECB_LSB_EBW_MID)  |  u1_t_sgnl_ddrtwv);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_DDM1S17_RXCH0) && (defined(ComConf_ComSignal_B_EBW) || defined(ComConf_ComSignal_DDRTWV) || ComConf_ComSignal_EBW_MID) */
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
                                               | (U4)((U4)1U << ALERT_REQ_C_ECB_LNG1_DISP_RW )
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
/*  5.5.0     11/25/2024 KO       Change for BEV System_Consideration_1.                                                             */
/*                                                                                                                                   */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * KT   = Kenichi Takahashi, NTTD MSE                                                                                             */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*  * HU   = Hidekazu Usui, NTTD MSE                                                                                                 */
/*  * KO   = Kazuto Oishi,  Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
