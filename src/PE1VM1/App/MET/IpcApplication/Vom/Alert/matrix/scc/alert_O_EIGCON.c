/* 5.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert O_EIGCON                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_O_EIGCON_C_MAJOR                   (5)
#define ALERT_O_EIGCON_C_MINOR                   (4)
#define ALERT_O_EIGCON_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"
#include "alert_brx.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_O_EIGCON_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_O_EIGCON.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_O_EIGCON_ENG_NUM_DST               (64U)
#define ALERT_O_EIGCON_POWSTS_NUM_DST            (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (defined(OXCAN_PDU_RX_CAN_PMN1G03) || defined(OXCAN_PDU_RX_CAN_PMN1F03)) && defined(ComConf_ComSignal_MOD_EIG) /* _235D_CAN_ */
static U1      u1_s_alert_o_eigcon_pow_msg_pmn;
#endif /* (defined(OXCAN_PDU_RX_CAN_PMN1G03) || defined(OXCAN_PDU_RX_CAN_PMN1F03)) && defined(ComConf_ComSignal_BZRQ_EIG) */
#if (defined(OXCAN_PDU_RX_CAN_PMN1G03) || defined(OXCAN_PDU_RX_CAN_PMN1F03)) && defined(ComConf_ComSignal_MOD_EIG) /* _235D_CAN_ */
static U1      u1_s_alert_o_eigcon_pow_msg_pdc;
#endif /* (defined(OXCAN_PDU_RX_CAN_PMN1G03) || defined(OXCAN_PDU_RX_CAN_PMN1F03)) && defined(ComConf_ComSignal_MOD_EIG) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertO_eigconEngSrcchk   (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertO_eigconPowstsSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_O_EIGCON_ENG_DST[ALERT_O_EIGCON_ENG_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_O_EIGCON_ENG_CYCLE,                                          /* 01 CYCLE                                           */
    (U1)ALERT_REQ_O_EIGCON_ENG_ON,                                             /* 02 ON                                              */
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
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 31 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 32 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 33 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 34 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 35 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 36 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 37 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 38 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 39 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 40 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 41 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 42 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 43 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 44 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 45 UNKNOWN                                         */
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
static const U4  u4_sp_ALERT_O_EIGCON_POWSTS_CRIT[ALERT_O_EIGCON_POWSTS_NUM_DST] = {
    (U4)0x02000009U,                                                           /* 00 ACC                                             */
    (U4)0x10000002U                                                            /* 01 POWER                                           */
};
static const U4  u4_sp_ALERT_O_EIGCON_POWSTS_MASK[ALERT_O_EIGCON_POWSTS_NUM_DST] = {
    (U4)0x020000FFU,                                                           /* 00 ACC                                             */
    (U4)0x10000037U                                                            /* 01 POWER                                           */
};
static const U1  u1_sp_ALERT_O_EIGCON_POWSTS_DST[ALERT_O_EIGCON_POWSTS_NUM_DST] = {
    (U1)ALERT_REQ_O_EIGCON_POWSTS_ACC,                                         /* 00 ACC                                             */
    (U1)ALERT_REQ_O_EIGCON_POWSTS_POWER                                        /* 01 POWER                                           */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_O_EIGCON_MTRX[2] = {
    {
        &u4_s_AlertO_eigconEngSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_O_EIGCON_ENG_DST[0],                                      /* u1p_DST                                            */
        (U2)ALERT_O_EIGCON_ENG_NUM_DST,                                        /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertO_eigconPowstsSrcchk,                                       /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_O_EIGCON_POWSTS_MASK[0],                                  /* u4p_MASK                                           */
        &u4_sp_ALERT_O_EIGCON_POWSTS_CRIT[0],                                  /* u4p_CRIT                                           */

        &u1_sp_ALERT_O_EIGCON_POWSTS_DST[0],                                   /* u1p_DST                                            */
        (U2)ALERT_O_EIGCON_POWSTS_NUM_DST,                                     /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertO_eigconInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertO_eigconInit(void)
{
#if (defined(OXCAN_PDU_RX_CAN_PMN1G03) || defined(OXCAN_PDU_RX_CAN_PMN1F03)) && defined(ComConf_ComSignal_MOD_EIG) /* _235D_CAN_ */
    u1_s_alert_o_eigcon_pow_msg_pmn = (U1)COM_NO_RX;
#endif /* (defined(OXCAN_PDU_RX_CAN_PMN1G03) || defined(OXCAN_PDU_RX_CAN_PMN1F03)) && defined(ComConf_ComSignal_BZRQ_EIG) */
#if (defined(OXCAN_PDU_RX_CAN_PMN1G03) || defined(OXCAN_PDU_RX_CAN_PMN1F03)) && defined(ComConf_ComSignal_MOD_EIG) /* _235D_CAN_ */
    u1_s_alert_o_eigcon_pow_msg_pdc = (U1)COM_NO_RX;
#endif /* (defined(OXCAN_PDU_RX_CAN_PMN1G03) || defined(OXCAN_PDU_RX_CAN_PMN1F03)) && defined(ComConf_ComSignal_MOD_EIG) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertO_eigconEngSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertO_eigconEngSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if (defined(OXCAN_PDU_RX_CAN_PMN1G03) || defined(OXCAN_PDU_RX_CAN_PMN1F03)) && defined(ComConf_ComSignal_BZRQ_EIG) /* _235D_CAN_ */
    static const U2 u2_s_ALERT_O_EIGCON_ENG_TO_TRSH = ((U2)3600U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_O_EIGCON_ENG_LSB_MSG = (U1)4U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_msgsts;

#if defined(OXCAN_PDU_RX_CAN_PMN1G03)
    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_PMN1G03,
                                          (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                          u2_s_ALERT_O_EIGCON_ENG_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#else
    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_PMN1F03,
                                          (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                          u2_s_ALERT_O_EIGCON_ENG_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#endif /* defined(OXCAN_PDU_RX_CAN_PMN1G03) */

    u1_t_sgnl     = (U1)0U;
#ifdef ComConf_ComSignal_BZRQ_EIG
    (void)Com_ReceiveSignal(ComConf_ComSignal_BZRQ_EIG, &u1_t_sgnl);
#endif /* ComConf_ComSignal_BZRQ_EIG */ /* 235D_CAN */
    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_O_EIGCON_ENG_LSB_MSG);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* (defined(OXCAN_PDU_RX_CAN_PMN1G03) || defined(OXCAN_PDU_RX_CAN_PMN1F03)) && defined(ComConf_ComSignal_BZRQ_EIG) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertO_eigconPowstsSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertO_eigconPowstsSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if (defined(OXCAN_PDU_RX_CAN_PMN1G03) || defined(OXCAN_PDU_RX_CAN_PMN1F03)) && defined(ComConf_ComSignal_MOD_EIG) /* _235D_CAN_ */
    static const U2 u2_s_ALERT_O_EIGCON_POW_TO_TRSH = ((U2)3600U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_O_EIGCON_POW_LSB_PDC = (U1)6U;
    static const U1 u1_s_ALERT_O_EIGCON_POW_LSB_PMN = (U1)4U;
    static const U1 u1_s_ALERT_O_EIGCON_POW_LSB_ACC = (U1)3U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_msgsts;

#if defined(OXCAN_PDU_RX_CAN_PMN1G03)
    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_PMN1G03,
                                          (U2)OXCAN_RX_SYS_NRX_BAT | (U2)OXCAN_RX_SYS_TOE_BAT,
                                          u2_s_ALERT_O_EIGCON_POW_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#else
    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_PMN1F03,
                                          (U2)OXCAN_RX_SYS_NRX_BAT | (U2)OXCAN_RX_SYS_TOE_BAT,
                                          u2_s_ALERT_O_EIGCON_POW_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#endif /* defined(OXCAN_PDU_RX_CAN_PMN1G03) */

    vd_g_AlertBRxTrnsSts(&u1_s_alert_o_eigcon_pow_msg_pmn, u1_t_msgsts);

    u1_t_sgnl     = (U1)0U;
#ifdef ComConf_ComSignal_MOD_EIG
    (void)Com_ReceiveSignal(ComConf_ComSignal_MOD_EIG, &u1_t_sgnl);
#endif /* ComConf_ComSignal_MOD_EIG */ /* 235D_CAN */
    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_s_alert_o_eigcon_pow_msg_pmn << u1_s_ALERT_O_EIGCON_POW_LSB_PMN);

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_PDC1G01,
                                          (U2)OXCAN_RX_SYS_NRX_BAT | (U2)OXCAN_RX_SYS_TOE_BAT,
                                          u2_s_ALERT_O_EIGCON_POW_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) == (U1)0U){
        u1_t_msgsts |= (U1)ALERT_BRX_FACT_NO_RX;
    }
    vd_g_AlertBRxTrnsSts(&u1_s_alert_o_eigcon_pow_msg_pdc, u1_t_msgsts);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_ACC_PDC, &u1_t_sgnl);
    u4_t_src_chk |= ((U4)u1_t_sgnl                       << u1_s_ALERT_O_EIGCON_POW_LSB_ACC);
    u4_t_src_chk |= ((U4)u1_s_alert_o_eigcon_pow_msg_pdc << u1_s_ALERT_O_EIGCON_POW_LSB_PDC);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* (defined(OXCAN_PDU_RX_CAN_PMN1G03) || defined(OXCAN_PDU_RX_CAN_PMN1F03)) && defined(ComConf_ComSignal_MOD_EIG) */
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     5/ 7/2020  DS       New.                                                                                               */
/*  5.1.0     9/16/2020  MY       Fix ACC/POWSTS power supply state.                                                                 */
/*  5.2.0    12/ 7/2020  MO       Update for 800B 1A(Add PMN1F03).                                                                   */
/*  5.3.0     4/ 8/2021  SO       Delete ACC Ch.                                                                                     */
/*  5.4.0     6/24/2021  SO       Change matrix table for POWSTS.                                                                    */
/*                                                                                                                                   */
/*  * DS   = Daisuke Suzuki, NTTD MSE                                                                                                */
/*  * MY   = Masaki Yoshizawa, NTTD MSE                                                                                              */
/*  * MO   = Masayuki Oofuji, NTTD MSE                                                                                               */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
