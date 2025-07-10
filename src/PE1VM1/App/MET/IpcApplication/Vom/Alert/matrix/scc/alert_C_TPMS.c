/* 5.1.4 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert C_TPMS                                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_TPMS_C_MAJOR                     (5)
#define ALERT_C_TPMS_C_MINOR                     (1)
#define ALERT_C_TPMS_C_PATCH                     (4)

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
#if (ALERT_C_TPMS_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_C_TPMS.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_TPMS_TT_NUM_DST                  (7U)
#define ALERT_C_TPMS_BC_NUM_DST                  (8U)
#define ALERT_C_TPMS_PD_NUM_DST                  (5U)

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
static U4      u4_s_AlertC_tpmsTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertC_tpmsBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertC_tpmsPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertC_tpmsPdRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U4  u4_sp_ALERT_C_TPMS_TT_CRIT[ALERT_C_TPMS_TT_NUM_DST] = {
    (U4)0x00000020U,                                                           /* 00 MALFUNC                                         */
    (U4)0x00000060U,                                                           /* 01 STOP                                            */
    (U4)0x00000001U,                                                           /* 02 LOWPRE                                          */
    (U4)0x00000002U,                                                           /* 03 INIT                                            */
    (U4)0x00000003U,                                                           /* 04 STOP                                            */
    (U4)0x00000004U,                                                           /* 05 TEST                                            */
    (U4)0x00000005U                                                            /* 06 MALFUNC                                         */
};
static const U4  u4_sp_ALERT_C_TPMS_TT_MASK[ALERT_C_TPMS_TT_NUM_DST] = {
    (U4)0x00000060U,                                                           /* 00 MALFUNC                                         */
    (U4)0x00000060U,                                                           /* 01 STOP                                            */
    (U4)0x0000001FU,                                                           /* 02 LOWPRE                                          */
    (U4)0x0000001FU,                                                           /* 03 INIT                                            */
    (U4)0x0000001FU,                                                           /* 04 STOP                                            */
    (U4)0x0000001FU,                                                           /* 05 TEST                                            */
    (U4)0x0000001FU                                                            /* 06 MALFUNC                                         */
};
static const U1  u1_sp_ALERT_C_TPMS_TT_DST[ALERT_C_TPMS_TT_NUM_DST] = {
    (U1)ALERT_REQ_C_TPMS_TT_MALFUNC,                                           /* 00 MALFUNC                                         */
    (U1)ALERT_REQ_C_TPMS_TT_STOP,                                              /* 01 STOP                                            */
    (U1)ALERT_REQ_C_TPMS_TT_LOWPRE,                                            /* 02 LOWPRE                                          */
    (U1)ALERT_REQ_C_TPMS_TT_INIT,                                              /* 03 INIT                                            */
    (U1)ALERT_REQ_C_TPMS_TT_STOP,                                              /* 04 STOP                                            */
    (U1)ALERT_REQ_C_TPMS_TT_TEST,                                              /* 05 TEST                                            */
    (U1)ALERT_REQ_C_TPMS_TT_MALFUNC                                            /* 06 MALFUNC                                         */
};
static const U1  u1_sp_ALERT_C_TPMS_BC_DST[ALERT_C_TPMS_BC_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_C_TPMS_BC_SINGLE,                                            /* 01 SINGLE                                          */
    (U1)ALERT_REQ_C_TPMS_BC_CYCL,                                              /* 02 CYCL                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 07 UNKNOWN                                         */
};
static const U4  u4_sp_ALERT_C_TPMS_PD_CRIT[ALERT_C_TPMS_PD_NUM_DST] = {
    (U4)0x00000100U,                                                           /* 00 MALFUNC                                         */
    (U4)0x0000002DU,                                                           /* 01 NOTCHG                                          */
    (U4)0x00000002U,                                                           /* 02 MALFUNC                                         */
    (U4)0x00000014U,                                                           /* 03 LOW_E                                           */
    (U4)0x00000016U                                                            /* 04 LOW_S                                           */
};
static const U4  u4_sp_ALERT_C_TPMS_PD_MASK[ALERT_C_TPMS_PD_NUM_DST] = {
    (U4)0x00000100U,                                                           /* 00 MALFUNC                                         */
    (U4)0x000000FFU,                                                           /* 01 NOTCHG                                          */
    (U4)0x000000BEU,                                                           /* 02 MALFUNC                                         */
    (U4)0x000000BEU,                                                           /* 03 LOW_E                                           */
    (U4)0x000000BEU                                                            /* 04 LOW_S                                           */
};
static const U1  u1_sp_ALERT_C_TPMS_PD_DST[ALERT_C_TPMS_PD_NUM_DST] = {
    (U1)ALERT_REQ_C_TPMS_PD_MALFUNC,                                           /* 00 MALFUNC                                         */
    (U1)ALERT_REQ_C_TPMS_PD_NOTCHG,                                            /* 01 NOTCHG                                          */
    (U1)ALERT_REQ_C_TPMS_PD_MALFUNC,                                           /* 02 MALFUNC                                         */
    (U1)ALERT_REQ_C_TPMS_PD_LOW_E,                                             /* 03 LOW_E                                           */
    (U1)ALERT_REQ_C_TPMS_PD_LOW_S                                              /* 04 LOW_S                                           */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_C_TPMS_MTRX[3] = {
    {
        &u4_s_AlertC_tpmsTtSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_C_TPMS_TT_MASK[0],                                        /* u4p_MASK                                           */
        &u4_sp_ALERT_C_TPMS_TT_CRIT[0],                                        /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_TPMS_TT_DST[0],                                         /* u1p_DST                                            */
        (U2)ALERT_C_TPMS_TT_NUM_DST,                                           /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertC_tpmsBcSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_TPMS_BC_DST[0],                                         /* u1p_DST                                            */
        (U2)ALERT_C_TPMS_BC_NUM_DST,                                           /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertC_tpmsPdSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertC_tpmsPdRwTx,                                               /* fp_vd_XDST                                         */

        &u4_sp_ALERT_C_TPMS_PD_MASK[0],                                        /* u4p_MASK                                           */
        &u4_sp_ALERT_C_TPMS_PD_CRIT[0],                                        /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_TPMS_PD_DST[0],                                         /* u1p_DST                                            */
        (U2)ALERT_C_TPMS_PD_NUM_DST,                                           /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_tpmsTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_tpmsTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_RXD_PDU_CAN_TPM1S02_CH0) && defined(ComConf_ComSignal_TPM_IND)
    static const U2 u2_s_ALERT_C_TPMS_TT_TO_THRSH   = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U4 u4_s_ALERT_C_TPMS_TT_BIT_DEST   = (U4)0x00000040U;
    static const U1 u1_s_ALERT_C_TPMS_TT_LSB_MSGSTS = (U1)4U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_msgsts;
    U1              u1_t_dest;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_TPM1S02_CH0,
                                     (U4)OXCAN_SYS_IGR,
                                     u2_s_ALERT_C_TPMS_TT_TO_THRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_TPM_IND, &u1_t_sgnl);
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_C_TPMS_TT_LSB_MSGSTS);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    u1_t_dest     = u1_g_AlertEsOptAvailable((U2)ALERT_OPT_ID_C_TPMS_TPM_DISC);
    if(u1_t_dest == (U1)TRUE){
        u4_t_src_chk |= u4_s_ALERT_C_TPMS_TT_BIT_DEST;
    }

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_RXD_PDU_CAN_TPM1S02_CH0) && defined(ComConf_ComSignal_TPM_IND) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_tpmsBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_tpmsBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_RXD_PDU_CAN_TPM1S02_CH0) && defined(ComConf_ComSignal_TPM_BZR)
    static const U1 u1_s_ALERT_C_TPMS_BC_LSB_MSGSTS = (U1)2U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_msgsts;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_TPM1S02_CH0,
                                     (U4)OXCAN_SYS_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_TPM_BZR, &u1_t_sgnl);
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_C_TPMS_BC_LSB_MSGSTS);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_RXD_PDU_CAN_TPM1S02_CH0) && defined(ComConf_ComSignal_TPM_BZR) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_tpmsPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_tpmsPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if (defined(OXCAN_RXD_PDU_CAN_TPM1S02_CH0) && defined(ComConf_ComSignal_TPM_DISP)) && (defined(OXCAN_RXD_PDU_CAN_TPM1S03_CH0) && defined(ComConf_ComSignal_TPM_REQ0))
    static const U2 u2_s_ALERT_C_TPMS_PD_TO_THRSH    = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_C_TPMS_PD_LSB_TPM1S02 = (U1)7U;
    static const U1 u1_s_ALERT_C_TPMS_PD_LSB_TPMDISP = (U1)1U;
    static const U1 u1_s_ALERT_C_TPMS_PD_LSB_TPM1S03 = (U1)6U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_tpm1s02_sts;
    U1              u1_t_tpm1s03_sts;

    u1_t_tpm1s02_sts = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_TPM1S02_CH0,
                                        (U4)OXCAN_SYS_IGR,
                                        u2_s_ALERT_C_TPMS_PD_TO_THRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u4_t_src_chk     = ((U4)u1_t_tpm1s02_sts << u1_s_ALERT_C_TPMS_PD_LSB_TPM1S02);

    u1_t_tpm1s03_sts = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_TPM1S03_CH0,
                                        (U4)OXCAN_SYS_IGR,
                                        (U2)U2_MAX) & (U1)COM_NO_RX;
    u4_t_src_chk    |= ((U4)u1_t_tpm1s03_sts << u1_s_ALERT_C_TPMS_PD_LSB_TPM1S03);

    u1_t_sgnl        = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_TPM_DISP, &u1_t_sgnl);
    u4_t_src_chk    |= ((U4)u1_t_sgnl        << u1_s_ALERT_C_TPMS_PD_LSB_TPMDISP);

    u1_t_sgnl        = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_TPM_REQ0, &u1_t_sgnl);
    u4_t_src_chk    |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* (defined(OXCAN_RXD_PDU_CAN_TPM1S02_CH0) && defined(ComConf_ComSignal_TPM_DISP)) &&
          (defined(OXCAN_RXD_PDU_CAN_TPM1S03_CH0) && defined(ComConf_ComSignal_TPM_REQ0)) */
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertC_tpmsPdRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertC_tpmsPdRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    U1              u1_t_tirw;
    U1              u1_t_tilw;
#if defined(ComConf_ComSignal_TIPW) /*840B_CAN CV-R*/
    U1              u1_t_tipw;
#endif /* defined(ComConf_ComSignal_TIPW) */ /*840B_CAN CV-R*/
    U1              u1_t_esopt;

    u1_t_esopt = u1_g_AlertEsOptAvailable((U2)ALERT_OPT_ID_C_TPMS_TPM_VAR);
    u1_t_tirw  = (U1)ALERT_RW_SGNL_OFF;
    u1_t_tilw  = (U1)ALERT_RW_SGNL_OFF;
#if defined(ComConf_ComSignal_TIPW) /*840B_CAN CV-R*/
    u1_t_tipw  = (U1)ALERT_RW_SGNL_OFF;
#endif /* defined(ComConf_ComSignal_TIPW) */ /*840B_CAN CV-R*/
    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN) != (U1)0U  ) &&
       (u1_t_esopt                        == (U1)TRUE)){
        if(u1_a_DST == (U1)ALERT_REQ_C_TPMS_PD_MALFUNC){
            u1_t_tirw = (U1)ALERT_RW_SGNL_ON;
        }

        if(u1_a_DST == (U1)ALERT_REQ_C_TPMS_PD_LOW_S){
            u1_t_tilw = (U1)ALERT_RW_SGNL_ON;
        }

#if defined(ComConf_ComSignal_TIPW) /*840B_CAN CV-R*/
        if(u1_a_DST == (U1)ALERT_REQ_C_TPMS_PD_LOW_E){
            u1_t_tipw = (U1)ALERT_RW_SGNL_ON;
        }
#endif /* defined(ComConf_ComSignal_TIPW) */ /*840B_CAN CV-R*/
    }

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_TIRW, &u1_t_tirw);    /* COM Tx STUB delete */
    (void)Com_SendSignal(ComConf_ComSignal_TILW, &u1_t_tilw);    /* COM Tx STUB delete */
#endif
#if defined(ComConf_ComSignal_TIPW) /*840B_CAN CV-R*/
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_TIPW, &u1_t_tipw);    /* COM Tx STUB delete */
#endif
#endif /* defined(ComConf_ComSignal_TIPW) */ /*840B_CAN CV-R*/
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     3/ 9/2020  SN       New.                                                                                               */
/*  5.0.1     9/ 2/2020  DS       Update filename.                                                                                   */
/*  5.0.2    10/ 1/2020  ZS       Fix QAC warnning.                                                                                  */
/*  5.1.0    12/ 8/2020  TN       Update for 800B 1A(Version update).                                                                */
/*  5.1.1     3/25/2021  RI       Update for 840B CV(Version update).                                                                */
/*  5.1.2     8/ 4/2022  RN       Update for 840B#2 1A(Version update).                                                              */
/*  5.1.3    10/20/2022  HU       Update for 840B#2 MPT(Version update).                                                             */
/*  5.1.4    12/12/2023  RO       Update for 19PFv3                    .                                                             */
/*                                                                                                                                   */
/*  * SN   = Shinichiro Naito, NTTD MSE                                                                                              */
/*  * DS   = Daisuke Suzuki, NTTD MSE                                                                                                */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * TN   = Toshiaki Nagashima, NTTD MSE                                                                                            */
/*  * RI   = Ren Ito, NTTD MSE                                                                                                       */
/*  * RN   = Ryuga Nakanishi, NTTD MSE                                                                                               */
/*  * HU   = Hiroshi Umezawa, NTTD MSE                                                                                               */
/*  * RO   = Ryo Oohashi, KSE                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
