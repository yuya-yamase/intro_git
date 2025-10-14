/* 5.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert_S_DSC                                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_DSC_C_MAJOR                      (5)
#define ALERT_S_DSC_C_MINOR                      (4)
#define ALERT_S_DSC_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_S_DSC_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_S_DSC.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_DSC_NUM_DST                      (64U)

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
static U4      u4_s_AlertS_dscSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertS_dscRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_S_DSC_DST[ALERT_S_DSC_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_DSC_MSG2,                                                  /* 01 MSG2                                            */
    (U1)ALERT_REQ_S_DSC_MSG4,                                                  /* 02 MSG4                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_S_DSC_MSG3,                                                  /* 04 MSG3                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_S_DSC_MSG2,                                                  /* 09 MSG2                                            */
    (U1)ALERT_REQ_S_DSC_MSG4,                                                  /* 10 MSG4                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_S_DSC_MSG3,                                                  /* 12 MSG3                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 16 UNKNOWN                                         */
    (U1)ALERT_REQ_S_DSC_MSG2,                                                  /* 17 MSG2                                            */
    (U1)ALERT_REQ_S_DSC_MSG4,                                                  /* 18 MSG4                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 19 UNKNOWN                                         */
    (U1)ALERT_REQ_S_DSC_MSG3,                                                  /* 20 MSG3                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 21 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 22 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 23 UNKNOWN                                         */
    (U1)ALERT_REQ_S_DSC_RW,                                                    /* 24 RW                                              */
    (U1)ALERT_REQ_S_DSC_MSG2_RW,                                               /* 25 MSG2_RW                                         */
    (U1)ALERT_REQ_S_DSC_MSG4_RW,                                               /* 26 MSG4_RW                                         */
    (U1)ALERT_REQ_S_DSC_RW,                                                    /* 27 RW                                              */
    (U1)ALERT_REQ_S_DSC_MSG3_RW,                                               /* 28 MSG3_RW                                         */
    (U1)ALERT_REQ_S_DSC_RW,                                                    /* 29 RW                                              */
    (U1)ALERT_REQ_S_DSC_RW,                                                    /* 30 RW                                              */
    (U1)ALERT_REQ_S_DSC_RW,                                                    /* 31 RW                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 32 UNKNOWN                                         */
    (U1)ALERT_REQ_S_DSC_MSG2,                                                  /* 33 MSG2                                            */
    (U1)ALERT_REQ_S_DSC_MSG4,                                                  /* 34 MSG4                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 35 UNKNOWN                                         */
    (U1)ALERT_REQ_S_DSC_MSG3,                                                  /* 36 MSG3                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 37 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 38 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 39 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 40 UNKNOWN                                         */
    (U1)ALERT_REQ_S_DSC_MSG2,                                                  /* 41 MSG2                                            */
    (U1)ALERT_REQ_S_DSC_MSG4,                                                  /* 42 MSG4                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 43 UNKNOWN                                         */
    (U1)ALERT_REQ_S_DSC_MSG3,                                                  /* 44 MSG3                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 45 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 46 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 47 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 48 UNKNOWN                                         */
    (U1)ALERT_REQ_S_DSC_MSG2,                                                  /* 49 MSG2                                            */
    (U1)ALERT_REQ_S_DSC_MSG4,                                                  /* 50 MSG4                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 51 UNKNOWN                                         */
    (U1)ALERT_REQ_S_DSC_MSG3,                                                  /* 52 MSG3                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 53 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 54 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 55 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 56 UNKNOWN                                         */
    (U1)ALERT_REQ_S_DSC_MSG2,                                                  /* 57 MSG2                                            */
    (U1)ALERT_REQ_S_DSC_MSG4,                                                  /* 58 MSG4                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 59 UNKNOWN                                         */
    (U1)ALERT_REQ_S_DSC_MSG3,                                                  /* 60 MSG3                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 61 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 62 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 63 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_S_DSC_MTRX[1] = {
    {
        &u4_s_AlertS_dscSrcchk,                                                /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertS_dscRwTx,                                                  /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_DSC_DST[0],                                             /* u1p_DST                                            */
        (U2)ALERT_S_DSC_NUM_DST,                                               /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_dscSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_dscSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_ENG1G92) || defined(OXCAN_PDU_RX_CAN_ENG1S92)
#ifdef OXCAN_PDU_RX_CAN_ENG1G92
    static const U2 u2_s_ALERT_S_DSC_TO_TRSH_ENG1G92 = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
#else
    static const U2 u2_s_ALERT_S_DSC_TO_TRSH_ENG1S92 = ((U2)5200U / (U2)OXCAN_MAIN_TICK);
#endif /* OXCAN_PDU_RX_CAN_ENG1G92 */
    static const U1 u1_s_ALERT_S_DSC_LSB_SGNL        = (U1)3U;
    static const U1 u1_s_ALERT_S_DSC_FAIL_VAL        = (U1)4U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

#ifdef OXCAN_PDU_RX_CAN_ENG1G92
    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1G92,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_S_DSC_TO_TRSH_ENG1G92) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#else
    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1S92,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_S_DSC_TO_TRSH_ENG1S92) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#endif /* OXCAN_PDU_RX_CAN_ENG1G92 */

    u1_t_sgnl     = (U1)0U;

    if((u1_t_msgsts & (U1)COM_TIMEOUT) != (U1)0U){
        u1_t_sgnl = u1_s_ALERT_S_DSC_FAIL_VAL;
    }
    else if((u1_t_msgsts & (U1)COM_NO_RX) != (U1)0U){
        u1_t_sgnl = (U1)0U;
    }
    else{
        (void)Com_ReceiveSignal(ComConf_ComSignal_GOSMINF, &u1_t_sgnl);
    }
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u1_t_sgnl     = (U1)0U;
    if ((u1_t_msgsts & (U1)COM_NO_RX) == (U1)0U) {
        (void)Com_ReceiveSignal(ComConf_ComSignal_GOSLAMP, &u1_t_sgnl);
    } 
    u4_t_src_chk  |= ((U4)u1_t_sgnl << u1_s_ALERT_S_DSC_LSB_SGNL);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_ENG1G92) || defined(OXCAN_PDU_RX_CAN_ENG1S92) */

}

/*===================================================================================================================================*/
/*  static U4      vd_s_AlertS_dscRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertS_dscRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    static const U1 u1_s_ALERT_S_DSC_RWTX_CRT = ((U1)((U1)1U << ALERT_REQ_S_DSC_MSG3   )
                                              |  (U1)((U1)1U << ALERT_REQ_S_DSC_MSG2_RW)
                                              |  (U1)((U1)1U << ALERT_REQ_S_DSC_MSG3_RW)
                                              |  (U1)((U1)1U << ALERT_REQ_S_DSC_MSG4_RW)
                                              |  (U1)((U1)1U << ALERT_REQ_S_DSC_RW     ));
    static const U1 u1_s_ALERT_S_DSC_RWTX_MSK = (U1)0x07U;
    U1              u1_t_sgnl;
    U1              u1_t_esopt_sw_dsc;
    U4              u4_t_rw;

    u4_t_rw = ((U4)1U << (u1_a_DST & u1_s_ALERT_S_DSC_RWTX_MSK));
    u1_t_esopt_sw_dsc = u1_g_AlertEsOptAvailable((U2)ALERT_OPT_ID_S_DSC_DSCEXIST);
    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN)         != (U1)0U                 ) &&
       (u1_t_esopt_sw_dsc                         == (U1)TRUE               ) &&
       ((u4_t_rw & (U4)u1_s_ALERT_S_DSC_RWTX_CRT) != (U4)0U                 )){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_GOSW, &u1_t_sgnl);
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
/*  5.1.0     9/ 2/2020  ZS       Change THRESH time by signal flame.                                                                */
/*  5.1.1     7/12/2022  RN       Update for 840B#2 1A(Version update).                                                              */
/*  5.1.2    11/18/2022  HU       Update for 840B#2 MPT(Version update).                                                             */
/*  5.2.0    11/10/2023  SN       Delete TT function and sending RW                                                                  */
/*  5.3.0     4/ 1/2024  AA       Applied remote warning of GOSW                                                                     */
/*  5.4.0     4/17/2024  AA       Fixed remote warning                                                                               */
/*                                                                                                                                   */
/*  * FN   = Farah Niwa, NTTD MSE                                                                                                    */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * RN   = Ryuga Nakanishi, NTTD MSE                                                                                               */
/*  * HU   = Hidekazu Usui, NTTD MSE                                                                                                 */
/*  * SN   = Shimon Nambu, Denso Techno                                                                                              */
/*  * AA   = Anna Asuncion, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
