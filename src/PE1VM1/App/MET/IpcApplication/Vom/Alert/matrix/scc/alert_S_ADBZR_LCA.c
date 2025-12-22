/* 5.5.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert S_ADBZR_LCA                                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_ADBZR_LCA_C_MAJOR                      (5)
#define ALERT_S_ADBZR_LCA_C_MINOR                      (5)
#define ALERT_S_ADBZR_LCA_C_PATCH                      (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_S_ADBZR_LCA_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_S_ADBZR_LCA.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_ADBZR_LCA_RQ_NUM_DST             (4U)
#define ALERT_S_ADBZR_LCA_CL_NUM_DST             (4U)
#define ALERT_S_ADBZR_LCA_VC_NUM_DST             (8U)

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
static U4      u4_s_AlertS_adbzr_lcaRqSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertS_adbzr_lcaClSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertS_adbzr_lcaVcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_S_ADBZR_LCA_RQ_DST[ALERT_S_ADBZR_LCA_RQ_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_ADBZR_LCA_RQ_SINGLE,                                       /* 01 SINGLE                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 03 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_S_ADBZR_LCA_CL_DST[ALERT_S_ADBZR_LCA_CL_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_ADBZR_LCA_CL_DOUBLE,                                       /* 01 DOUBLE                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 03 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_S_ADBZR_LCA_VC_DST[ALERT_S_ADBZR_LCA_VC_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_ADBZR_LCA_VC_CYCL,                                         /* 01 CYCL                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 07 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_S_ADBZR_LCA_MTRX[3] = {
    {
        &u4_s_AlertS_adbzr_lcaRqSrcchk,                                        /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_ADBZR_LCA_RQ_DST[0],                                    /* u1p_DST                                            */
        (U2)ALERT_S_ADBZR_LCA_RQ_NUM_DST,                                      /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertS_adbzr_lcaClSrcchk,                                        /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_ADBZR_LCA_CL_DST[0],                                    /* u1p_DST                                            */
        (U2)ALERT_S_ADBZR_LCA_CL_NUM_DST,                                      /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertS_adbzr_lcaVcSrcchk,                                        /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_ADBZR_LCA_VC_DST[0],                                    /* u1p_DST                                            */
        (U2)ALERT_S_ADBZR_LCA_VC_NUM_DST,                                      /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_adbzr_lcaRqSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_adbzr_lcaRqSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_S_ADBZR_LCA_RQ_LSB = (U1)1U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_DS11S37_CH0,
                                      (U4)OXCAN_SYS_IGR | (U4)OXCAN_SYS_IGP,
                                      (U2)U2_MAX) & (U1)COM_NO_RX;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_LCSRQBZ, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_S_ADBZR_LCA_RQ_LSB);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_adbzr_lcaClSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_adbzr_lcaClSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_S_ADBZR_LCA_CL_LSB = (U1)1U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_DS11S37_CH0,
                                     (U4)OXCAN_SYS_IGR | (U4)OXCAN_SYS_IGP,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_LCANGBZ, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_S_ADBZR_LCA_CL_LSB);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_adbzr_lcaVcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_adbzr_lcaVcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_S_ADBZR_LCA_VC_TO  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);                    /*For THRESH/Judgement time*/
    static const U1 u1_s_ALERT_S_ADBZR_LCA_VC_LSB = (U1)1U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_DS11S37_CH0,
                                      (U4)OXCAN_SYS_IGR | (U4)OXCAN_SYS_IGP,
                                      u2_s_ALERT_S_ADBZR_LCA_VC_TO) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_LCAVCBZ, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_S_ADBZR_LCA_VC_LSB);

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
/*  5.0.0     3/11/2020  MY       New.                                                                                               */
/*  5.1.0    12/ 4/2020  SO       Add RW CH, and Change PD_MG matrix table.                                                          */
/*  5.1.1     3/19/2021  TN       Update for 840B CV(Version update).                                                                */
/*  5.1.2     6/24/2021  SO       Update for 050D CV(Version update).                                                                */
/*  5.2.0     1/ 5/2022  HU       Update for 840B 1A(Delete RW functions).                                                           */
/*  5.3.0     1/ 5/2022  HU       Update for 840B 1A(Version update).                                                                */
/*  5.3.1     7/12/2022  RN       Update for 840B#2 1A(Version update).                                                              */
/*  5.3.2    10/13/2022  SM       Update for 296D Certification Vehicle(Version update).                                             */
/*  5.4.0    11/20/2023  DR       Update for 19PFv3                                                                                  */
/*  5.5.0     6/23/2025  HY       Change for BEV System_Consideration_2.(MET-S_ADMID-CSTD-0-02-A-C0,MET-S_ADTT-CSTD-0-02-A-C0)       */
/*  5.5.1    12/18/2025  DT       Change for BEV System_Consideration_ADAS.(MET-S_ADBZR-CSTD-0-06-A-C0)                              */
/*                                                                                                                                   */
/*  * MY   = Masaki Yoshizawa, NTTD MSE                                                                                              */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*  * TN   = Toshiaki Nagashima, NTTD MSE                                                                                            */
/*  * HU   = Hidekazu Usui, NTTD MSE                                                                                                 */
/*  * RN   = Ryuga Nakanishi, NTTD MSE                                                                                               */
/*  * SM   = Shingo Miyamoto, NTTD MSE                                                                                               */
/*  * DR   = Dyan Reyes, DTPH                                                                                                        */
/*  * HY   = Haruki Yagi, KSE                                                                                                        */
/*  * DT   = Dj Tutanes, DTPH                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
