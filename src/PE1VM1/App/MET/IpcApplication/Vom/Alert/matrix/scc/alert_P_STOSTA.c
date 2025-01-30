/* 5.3.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert P_STOSTA                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_P_STOSTA_C_MAJOR                   (5)
#define ALERT_P_STOSTA_C_MINOR                   (3)
#define ALERT_P_STOSTA_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_P_STOSTA_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_P_STOSTA.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_P_STOSTA_TT_NUM_DST                (32U)
#define ALERT_P_STOSTA_BC_NUM_DST                (16U)
#define ALERT_P_STOSTA_PD_FAL_NUM_DST            (4U)
#define ALERT_P_STOSTA_PD_COA_NUM_DST            (3U)
#define ALERT_P_STOSTA_PD_INH_NUM_DST            (8U)

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
static U4      u4_s_AlertP_stostaTtSrcchk   (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertP_stostaBcSrcchk   (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertP_stostaPdFalSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertP_stostaPdCoaSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertP_stostaPdInhSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertP_stostaPdFalRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_P_STOSTA_TT_DST[ALERT_P_STOSTA_TT_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_P_STOSTA_TT_ON_A,                                            /* 01 ON_A                                            */
    (U1)ALERT_REQ_P_STOSTA_TT_ON_A,                                            /* 02 ON_A                                            */
    (U1)ALERT_REQ_P_STOSTA_TT_FLASH_A,                                         /* 03 FLASH_A                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_P_STOSTA_TT_ON_G,                                            /* 08 ON_G                                            */
    (U1)ALERT_REQ_P_STOSTA_TT_FLASH1_G,                                        /* 09 FLASH1_G                                        */
    (U1)ALERT_REQ_P_STOSTA_TT_FLASH2_G,                                        /* 10 FLASH2_G                                        */
    (U1)ALERT_REQ_P_STOSTA_TT_FLASH3_G,                                        /* 11 FLASH3_G                                        */
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
static const U1  u1_sp_ALERT_P_STOSTA_BC_DST[ALERT_P_STOSTA_BC_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_P_STOSTA_BC_ON,                                              /* 01 ON                                              */
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
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_P_STOSTA_PD_FAL_DST[ALERT_P_STOSTA_PD_FAL_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_P_STOSTA_PD_FAL_MLFNC,                                       /* 01 MLFNC                                           */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 03 UNKNOWN                                         */
};
static const U4  u4_sp_ALERT_P_STOSTA_PD_COA_CRIT[ALERT_P_STOSTA_PD_COA_NUM_DST] = {
    (U4)0x00000009U,                                                           /* 00 CNT_WT                                          */
    (U4)0x00000008U,                                                           /* 01 CNTN                                            */
    (U4)0x00000001U                                                            /* 02 WAIT                                            */
};
static const U4  u4_sp_ALERT_P_STOSTA_PD_COA_MASK[ALERT_P_STOSTA_PD_COA_NUM_DST] = {
    (U4)0x000000FFU,                                                           /* 00 CNT_WT                                          */
    (U4)0x000000F8U,                                                           /* 01 CNTN                                            */
    (U4)0x000000C7U                                                            /* 02 WAIT                                            */
};
static const U1  u1_sp_ALERT_P_STOSTA_PD_COA_DST[ALERT_P_STOSTA_PD_COA_NUM_DST] = {
    (U1)ALERT_REQ_P_STOSTA_PD_COA_CNT_WT,                                      /* 00 CNT_WT                                          */
    (U1)ALERT_REQ_P_STOSTA_PD_COA_CNTN,                                        /* 01 CNTN                                            */
    (U1)ALERT_REQ_P_STOSTA_PD_COA_WAIT                                         /* 02 WAIT                                            */
};
static const U4  u4_sp_ALERT_P_STOSTA_PD_INH_CRIT[ALERT_P_STOSTA_PD_INH_NUM_DST] = {
    (U4)0x00000001U,                                                           /* 00 NDBAT                                           */
    (U4)0x00000002U,                                                           /* 01 BATCHG                                          */
    (U4)0x0000000AU,                                                           /* 02 PRE                                             */
    (U4)0x0000000BU,                                                           /* 03 CLMT                                            */
    (U4)0x00000023U,                                                           /* 04 PRE                                             */
    (U4)0x00000025U,                                                           /* 05 CLMT                                            */
    (U4)0x00000026U,                                                           /* 06 BATCHG                                          */
    (U4)0x0000003FU                                                            /* 07 UNAVL                                           */
};
static const U4  u4_sp_ALERT_P_STOSTA_PD_INH_MASK[ALERT_P_STOSTA_PD_INH_NUM_DST] = {
    (U4)0x000000FFU,                                                           /* 00 NDBAT                                           */
    (U4)0x000000FFU,                                                           /* 01 BATCHG                                          */
    (U4)0x000000FFU,                                                           /* 02 PRE                                             */
    (U4)0x000000FFU,                                                           /* 03 CLMT                                            */
    (U4)0x000000FFU,                                                           /* 04 PRE                                             */
    (U4)0x000000FFU,                                                           /* 05 CLMT                                            */
    (U4)0x000000FFU,                                                           /* 06 BATCHG                                          */
    (U4)0x000000FFU                                                            /* 07 UNAVL                                           */
};
static const U1  u1_sp_ALERT_P_STOSTA_PD_INH_DST[ALERT_P_STOSTA_PD_INH_NUM_DST] = {
    (U1)ALERT_REQ_P_STOSTA_PD_INH_NDBAT,                                       /* 00 NDBAT                                           */
    (U1)ALERT_REQ_P_STOSTA_PD_INH_BATCHG,                                      /* 01 BATCHG                                          */
    (U1)ALERT_REQ_P_STOSTA_PD_INH_PRE,                                         /* 02 PRE                                             */
    (U1)ALERT_REQ_P_STOSTA_PD_INH_CLMT,                                        /* 03 CLMT                                            */
    (U1)ALERT_REQ_P_STOSTA_PD_INH_PRE,                                         /* 04 PRE                                             */
    (U1)ALERT_REQ_P_STOSTA_PD_INH_CLMT,                                        /* 05 CLMT                                            */
    (U1)ALERT_REQ_P_STOSTA_PD_INH_BATCHG,                                      /* 06 BATCHG                                          */
    (U1)ALERT_REQ_P_STOSTA_PD_INH_UNAVL                                        /* 07 UNAVL                                           */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_P_STOSTA_MTRX[5] = {
    {
        &u4_s_AlertP_stostaTtSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_STOSTA_TT_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_P_STOSTA_TT_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertP_stostaBcSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_STOSTA_BC_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_P_STOSTA_BC_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertP_stostaPdFalSrcchk,                                        /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertP_stostaPdFalRwTx,                                          /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_STOSTA_PD_FAL_DST[0],                                   /* u1p_DST                                            */
        (U2)ALERT_P_STOSTA_PD_FAL_NUM_DST,                                     /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertP_stostaPdCoaSrcchk,                                        /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_P_STOSTA_PD_COA_MASK[0],                                  /* u4p_MASK                                           */
        &u4_sp_ALERT_P_STOSTA_PD_COA_CRIT[0],                                  /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_STOSTA_PD_COA_DST[0],                                   /* u1p_DST                                            */
        (U2)ALERT_P_STOSTA_PD_COA_NUM_DST,                                     /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertP_stostaPdInhSrcchk,                                        /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_P_STOSTA_PD_INH_MASK[0],                                  /* u4p_MASK                                           */
        &u4_sp_ALERT_P_STOSTA_PD_INH_CRIT[0],                                  /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_STOSTA_PD_INH_DST[0],                                   /* u1p_DST                                            */
        (U2)ALERT_P_STOSTA_PD_INH_NUM_DST,                                     /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_stostaTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_stostaTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_ECO1S90) && defined(ComConf_ComSignal_SSLMP)
    static const U1 u1_s_ALERT_P_STOSTA_TT_LSB_STS = (U1)4U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ECO1S90,
                                     (U2)OXCAN_RX_SYS_NRX_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_SSLMP, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_P_STOSTA_TT_LSB_STS);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_ECO1S90) && defined(ComConf_ComSignal_SSLMP) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_stostaBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_stostaBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_ECO1S90) && defined(ComConf_ComSignal_ECOBZR)
    static const U2 u2_s_ALERT_P_STOSTA_BC_TO_THRS = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_P_STOSTA_BC_LSB_STS = (U1)2U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ECO1S90,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
									 u2_s_ALERT_P_STOSTA_BC_TO_THRS) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_ECOBZR, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_P_STOSTA_BC_LSB_STS);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_ECO1S90) && defined(ComConf_ComSignal_ECOBZR) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_stostaPdFalSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_stostaPdFalSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_ECO1S90) && defined(ComConf_ComSignal_INFSSFAL)
    static const U1 u1_s_ALERT_P_STOSTA_FAL_LSB_STS = (U1)1U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ECO1S90,
	                                 (U2)OXCAN_RX_SYS_NRX_IGR,
									 (U2)U2_MAX) & (U1)COM_NO_RX;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_INFSSFAL, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_P_STOSTA_FAL_LSB_STS);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_ECO1S90) && defined(ComConf_ComSignal_INFSSFAL) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_stostaPdCoaSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_stostaPdCoaSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_ECO1S90) && defined(ComConf_ComSignal_INFSSCOP) && defined(ComConf_ComSignal_INFSSADV)
    static const U2 u2_s_ALERT_P_STOSTA_COA_TO_THRS = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_P_STOSTA_COA_LSB_COP = (U1)3U;
    static const U1 u1_s_ALERT_P_STOSTA_COA_LSB_STS = (U1)6U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ECO1S90,
	                                 (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
									 u2_s_ALERT_P_STOSTA_COA_TO_THRS) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_INFSSADV, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_INFSSCOP, &u1_t_sgnl);
    u4_t_src_chk |= ((U4)u1_t_sgnl << u1_s_ALERT_P_STOSTA_COA_LSB_COP);

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_P_STOSTA_COA_LSB_STS);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_ECO1S90) && defined(ComConf_ComSignal_INFSSCOP) && defined(ComConf_ComSignal_INFSSADV) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_stostaPdInhSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_stostaPdInhSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_ECO1S90) && defined(ComConf_ComSignal_INFSSINH)
    static const U2 u2_s_ALERT_P_STOSTA_INH_TO_THRS = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_P_STOSTA_INH_LSB_STS = (U1)6U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ECO1S90,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_P_STOSTA_INH_TO_THRS) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_INFSSINH, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_P_STOSTA_INH_LSB_STS);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_ECO1S90) && defined(ComConf_ComSignal_INFSSINH) */
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertP_stostaPdFalRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertP_stostaPdFalRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    U1              u1_t_sgnl;

    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN) != (U1)0U                             ) &&
       (u1_a_DST                          == (U1)ALERT_REQ_P_STOSTA_PD_FAL_MLFNC)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_ISSW, &u1_t_sgnl);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     3/ 6/2020  MY       New.                                                                                               */
/*  5.1.0    12/ 8/2020  MO       Update for 800B 1A(Version update).                                                                */
/*  5.1.1     3/26/2021  MO       Update for 840B CV(Version update).                                                                */
/*  5.2.0     2/ 7/2022  SM       Update for 900B 1A2H(Version update).                                                              */
/*  5.2.1     7/12/2022  KK       Update for 840B #2 1A(Version update).                                                             */
/*  5.3.0     2/16/2024  RO       Update for 19PFv3 CV(Version update).                                                              */
/*                                                                                                                                   */
/*  * MY   = Masaki Yoshizawa, NTTD MSE                                                                                              */
/*  * MO   = Masayuki Oofuji, NTTD MSE                                                                                               */
/*  * SM   = Shingo Miyamoto, NTTD MSE                                                                                               */
/*  * KK   = Kenta Kawahara, NTTD MSE                                                                                                */
/*  * RO   = Ryo Oohashi, KSE                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
