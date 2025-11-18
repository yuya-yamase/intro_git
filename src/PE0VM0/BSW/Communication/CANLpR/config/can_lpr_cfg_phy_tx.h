/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  CAN L-PDU Router Physical CAN Tx Configuration                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef CAN_LPR_CFG_PHY_TX_H
#define CAN_LPR_CFG_PHY_TX_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPR_CFG_PHY_TX_H_MAJOR               (1)
#define CAN_LPR_CFG_PHY_TX_H_MINOR               (0)
#define CAN_LPR_CFG_PHY_TX_H_PATCH               (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPR_NUM_PHY_CTRLR                    (12U)
#define CAN_LPR_PHY_CTRLR_G2M2                   (3U)
#define CAN_LPR_PHY_CTRLR_G2M1                   (5U)
#define CAN_LPR_PHY_CTRLR_G5M                    (7U)
#define CAN_LPR_PHY_CTRLR_LOCA                   (11U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPR_NUM_PHY_CH                       (3U)
#define CAN_LPR_PHY_CH_G2M1                      (0U)
#define CAN_LPR_PHY_CH_G5M                       (1U)
#define CAN_LPR_PHY_CH_LOCA                      (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4          u4_sp_can_lpr_phy_tx_log_0[CAN_LPR_PHY_TX_LOG_NWORD] __attribute__((section(".bss_CAN_LPR_PHY_TX")));
static U4          u4_sp_can_lpr_phy_tx_log_1[CAN_LPR_PHY_TX_LOG_NWORD] __attribute__((section(".bss_CAN_LPR_PHY_TX")));
static U4          u4_sp_can_lpr_phy_tx_log_2[CAN_LPR_PHY_TX_LOG_NWORD] __attribute__((section(".bss_CAN_LPR_PHY_TX")));
static U4          u4_sp_can_lpr_phy_tx_log_3[CAN_LPR_PHY_TX_LOG_NWORD] __attribute__((section(".bss_CAN_LPR_PHY_TX")));
static U4          u4_sp_can_lpr_phy_tx_log_4[CAN_LPR_PHY_TX_LOG_NWORD] __attribute__((section(".bss_CAN_LPR_PHY_TX")));
static U4          u4_sp_can_lpr_phy_tx_log_5[CAN_LPR_PHY_TX_LOG_NWORD] __attribute__((section(".bss_CAN_LPR_PHY_TX")));
static U4          u4_sp_can_lpr_phy_tx_log_6[CAN_LPR_PHY_TX_LOG_NWORD] __attribute__((section(".bss_CAN_LPR_PHY_TX")));
static U4          u4_sp_can_lpr_phy_tx_log_7[CAN_LPR_PHY_TX_LOG_NWORD] __attribute__((section(".bss_CAN_LPR_PHY_TX")));
static U4          u4_sp_can_lpr_phy_tx_log_8[CAN_LPR_PHY_TX_LOG_NWORD] __attribute__((section(".bss_CAN_LPR_PHY_TX")));
static U4          u4_sp_can_lpr_phy_tx_log_9[CAN_LPR_PHY_TX_LOG_NWORD] __attribute__((section(".bss_CAN_LPR_PHY_TX")));
static U4          u4_sp_can_lpr_phy_tx_log_10[CAN_LPR_PHY_TX_LOG_NWORD] __attribute__((section(".bss_CAN_LPR_PHY_TX")));
static U4          u4_sp_can_lpr_phy_tx_log_11[CAN_LPR_PHY_TX_LOG_NWORD] __attribute__((section(".bss_CAN_LPR_PHY_TX")));
static U4          u4_sp_can_lpr_phy_tx_log_12[CAN_LPR_PHY_TX_LOG_NWORD] __attribute__((section(".bss_CAN_LPR_PHY_TX")));

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U4                        u4_g_CAN_LPR_PHY_TX_TOUT = u4_CAN_LPR_FRT_MS(400U); /* 400 milliseconds */

const ST_CAN_LPR_PHY_TX         st_gp_CAN_LPR_PHY_TX[]   = {
    /* CAN_LPR_REGR_EN_PHY_TX_G2M1 */
    {
        &vd_g_CANLpFqResCh,                                /* fp_vd_RES_CH */
        &u1_g_CANLpFqDeqCh,                                /* fp_u1_DEQ_CH */
        &u4_sp_can_lpr_phy_tx_log_0[0U],                   /* u4p_log      */
        (U4)CAN_LPR_REGR_EN_PHY_FQ_G2M1,                   /* u4_regr_en   */
        (U2)CAN_LPFQ_CH_PHY_TX_G2M1_P0,                    /* u2_que_ch    */
        (U2)CAN_LPR_PHY_TX_VACK_DI                         /* u2_vack      */
    },
    {
        &vd_g_CANLpFqResCh,                                /* fp_vd_RES_CH */
        &u1_g_CANLpFqDeqCh,                                /* fp_u1_DEQ_CH */
        &u4_sp_can_lpr_phy_tx_log_1[0U],                   /* u4p_log      */
        (U4)CAN_LPR_REGR_EN_PHY_FQ_G2M1,                   /* u4_regr_en   */
        (U2)CAN_LPFQ_CH_PHY_TX_G2M1_P1,                    /* u2_que_ch    */
        (U2)CAN_LPR_PHY_TX_VACK_DI                         /* u2_vack      */
    },
    {
        &vd_g_CANLpFqResCh,                                /* fp_vd_RES_CH */
        &u1_g_CANLpFqDeqCh,                                /* fp_u1_DEQ_CH */
        &u4_sp_can_lpr_phy_tx_log_2[0U],                   /* u4p_log      */
        (U4)CAN_LPR_REGR_EN_PHY_FQ_G2M1,                   /* u4_regr_en   */
        (U2)CAN_LPFQ_CH_PHY_TX_G2M1_P2,                    /* u2_que_ch    */
        (U2)CAN_LPR_PHY_TX_VACK_DI                         /* u2_vack      */
    },
    {
        &vd_g_CANLpFqResCh,                                /* fp_vd_RES_CH */
        &u1_g_CANLpFqDeqCh,                                /* fp_u1_DEQ_CH */
        &u4_sp_can_lpr_phy_tx_log_3[0U],                   /* u4p_log      */
        (U4)CAN_LPR_REGR_EN_PHY_FQ_G2M1,                   /* u4_regr_en   */
        (U2)CAN_LPFQ_CH_PHY_TX_G2M1_P3,                    /* u2_que_ch    */
        (U2)CAN_LPR_PHY_TX_VACK_DI                         /* u2_vack      */
    },
    {
        &vd_g_CANLpFqResCh,                                /* fp_vd_RES_CH */
        &u1_g_CANLpFqDeqCh,                                /* fp_u1_DEQ_CH */
        &u4_sp_can_lpr_phy_tx_log_4[0U],                   /* u4p_log      */
        (U4)CAN_LPR_REGR_EN_PHY_FQ_G2M1,                   /* u4_regr_en   */
        (U2)CAN_LPFQ_CH_PHY_TX_G2M1_P4,                    /* u2_que_ch    */
        (U2)CAN_LPR_PHY_TX_VACK_DI                         /* u2_vack      */
    },
    {
        &vd_g_CANLpFqResCh,                                /* fp_vd_RES_CH */
        &u1_g_CANLpFqDeqCh,                                /* fp_u1_DEQ_CH */
        &u4_sp_can_lpr_phy_tx_log_5[0U],                   /* u4p_log      */
        (U4)CAN_LPR_REGR_EN_PHY_FQ_G2M1,                   /* u4_regr_en   */
        (U2)CAN_LPFQ_CH_PHY_TX_G2M1_P5,                    /* u2_que_ch    */
        (U2)CAN_LPR_PHY_TX_VACK_DI                         /* u2_vack      */
    },
    {
        &vd_g_CANLpFqResCh,                                /* fp_vd_RES_CH */
        &u1_g_CANLpFqDeqCh,                                /* fp_u1_DEQ_CH */
        &u4_sp_can_lpr_phy_tx_log_6[0U],                   /* u4p_log      */
        (U4)CAN_LPR_REGR_EN_PHY_FQ_G2M1,                   /* u4_regr_en   */
        (U2)CAN_LPFQ_CH_PHY_TX_G2M1_P6,                    /* u2_que_ch    */
        (U2)CAN_LPR_PHY_TX_VACK_DI                         /* u2_vack      */
    },
    {
        &vd_g_CANLpFqResCh,                                /* fp_vd_RES_CH */
        &u1_g_CANLpFqDeqCh,                                /* fp_u1_DEQ_CH */
        &u4_sp_can_lpr_phy_tx_log_7[0U],                   /* u4p_log      */
        (U4)CAN_LPR_REGR_EN_UDS_FQ_G2M1,                   /* u4_regr_en   */
        (U2)CAN_LPFQ_CH_PHY_TX_G2M1_P7,                    /* u2_que_ch    */
        (U2)CAN_LPR_PHY_TX_VACK_EN                         /* u2_vack      */
    },
    /* CAN_LPR_REGR_EN_PHY_TX_G5M  */
    {
        &vd_g_CANLpFqResCh,                                /* fp_vd_RES_CH */
        &u1_g_CANLpFqDeqCh,                                /* fp_u1_DEQ_CH */
        &u4_sp_can_lpr_phy_tx_log_8[0U],                   /* u4p_log      */
        (U4)CAN_LPR_REGR_EN_PHY_FQ_G5M,                    /* u4_regr_en   */
        (U2)CAN_LPFQ_CH_PHY_TX_G5M__P0,                    /* u2_que_ch    */
        (U2)CAN_LPR_PHY_TX_VACK_DI                         /* u2_vack      */
    },
    {
        &vd_g_CANLpFqResCh,                                /* fp_vd_RES_CH */
        &u1_g_CANLpFqDeqCh,                                /* fp_u1_DEQ_CH */
        &u4_sp_can_lpr_phy_tx_log_9[0U],                   /* u4p_log      */
        (U4)CAN_LPR_REGR_EN_PHY_FQ_G5M,                    /* u4_regr_en   */
        (U2)CAN_LPFQ_CH_PHY_TX_G5M__P1,                    /* u2_que_ch    */
        (U2)CAN_LPR_PHY_TX_VACK_DI                         /* u2_vack      */
    },
    {
        &vd_g_CANLpFqResCh,                                /* fp_vd_RES_CH */
        &u1_g_CANLpFqDeqCh,                                /* fp_u1_DEQ_CH */
        &u4_sp_can_lpr_phy_tx_log_10[0U],                   /* u4p_log      */
        (U4)CAN_LPR_REGR_EN_PHY_FQ_G5M,                    /* u4_regr_en   */
        (U2)CAN_LPFQ_CH_PHY_TX_G5M__P2,                    /* u2_que_ch    */
        (U2)CAN_LPR_PHY_TX_VACK_DI                         /* u2_vack      */
    },
    {
        &vd_g_CANLpFqResCh,                                /* fp_vd_RES_CH */
        &u1_g_CANLpFqDeqCh,                                /* fp_u1_DEQ_CH */
        &u4_sp_can_lpr_phy_tx_log_11[0U],                   /* u4p_log      */
        (U4)CAN_LPR_REGR_EN_PHY_FQ_G5M,                    /* u4_regr_en   */
        (U2)CAN_LPFQ_CH_PHY_TX_G5M__P3,                    /* u2_que_ch    */
        (U2)CAN_LPR_PHY_TX_VACK_DI                         /* u2_vack      */
    },
    /* CAN_LPR_REGR_EN_PHY_TX_LOCA  */
    {
        &vd_g_CANLpFqResCh,                                /* fp_vd_RES_CH */
        &u1_g_CANLpFqDeqCh,                                /* fp_u1_DEQ_CH */
        &u4_sp_can_lpr_phy_tx_log_12[0U],                   /* u4p_log      */
        (U4)CAN_LPR_REGR_EN_PHY_FQ_LOCA,                   /* u4_regr_en   */
        (U2)CAN_LPFQ_CH_PHY_TX_LOCA_P0,                    /* u2_que_ch    */
        (U2)CAN_LPR_PHY_TX_VACK_DI                         /* u2_vack      */
    }
};
const U2                        u2_g_CAN_LPR_NUM_PHY_TX = (U2)13U;

const ST_CAN_LPR_PHY_CH         st_gp_CAN_LPR_PHY_CH[CAN_LPR_NUM_PHY_CH] = {
    /* CAN_LPR_REGR_EN_PHY_TX_G2M1 */
    {
        &st_gp_CAN_LPR_PHY_TX[0U],                         /* stp_PHY_TX */
        (U4)CAN_LPR_REGR_EN_PHY_TX_G2M1,                   /* u4_regr_en */
        (U2)8U,                                            /* u2_nphy_tx */
        (U2)CAN_LPR_PHY_CTRLR_G2M1,                        /* u2_ctrlr   */
    },
    /* CAN_LPR_REGR_EN_PHY_TX_G5M  */
    {
        &st_gp_CAN_LPR_PHY_TX[8U],                         /* stp_PHY_TX */
        (U4)CAN_LPR_REGR_EN_PHY_TX_G5M,                    /* u4_regr_en */
        (U2)4U,                                            /* u2_nphy_tx */
        (U2)CAN_LPR_PHY_CTRLR_G5M,                         /* u2_ctrlr   */
    },
    /* CAN_LPR_REGR_EN_PHY_TX_LOCA  */
    {
        &st_gp_CAN_LPR_PHY_TX[12U],                        /* stp_PHY_TX */
        (U4)CAN_LPR_REGR_EN_PHY_TX_LOCA,                   /* u4_regr_en */
        (U2)1U,                                            /* u2_nphy_tx */
        (U2)CAN_LPR_PHY_CTRLR_LOCA                         /* u2_ctrlr   */
    }
};
const U1                        u1_g_CAN_LPR_NUM_PHY_CH = (U1)CAN_LPR_NUM_PHY_CH;

const ST_CAN_LPR_PHY_CH * const stp_gp_CAN_LPR_PHY_CH_BY_CTRLR[CAN_LPR_NUM_PHY_CTRLR] = {
    NULL_PTR,                                              /* controller               0   */
    NULL_PTR,                                              /* controller               1   */
    NULL_PTR,                                              /* controller               2   */
    NULL_PTR,                                              /* CAN_LPR_PHY_CTRLR_G2M2  (3U) */
    NULL_PTR,                                              /* controller               4   */
    &st_gp_CAN_LPR_PHY_CH[CAN_LPR_PHY_CH_G2M1],            /* CAN_LPR_PHY_CTRLR_G2M1  (5U) */
    NULL_PTR,                                              /* controller               6   */
    &st_gp_CAN_LPR_PHY_CH[CAN_LPR_PHY_CH_G5M],             /* CAN_LPR_PHY_CTRLR_G5M   (7U) */
    NULL_PTR,                                              /* controller               8   */
    NULL_PTR,                                              /* controller               9   */
    NULL_PTR,                                              /* controller              10   */
    &st_gp_CAN_LPR_PHY_CH[CAN_LPR_PHY_CH_LOCA]             /* CAN_LPR_PHY_CTRLR_LOCA (11U) */
};
const U1                        u1_g_CAN_LPR_NUM_PHY_CTRLR = (U1)CAN_LPR_NUM_PHY_CTRLR;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (CAN_LPR_RR_EN_IPDU_TX == 1U)
const ST_CAN_LPR_IPDU_TX        st_gp_CAN_LPR_IPDU_TX[CAN_LPR_NUM_IPDU_TX] = {
    {
        &u1_g_CANLpFqEnqCh,                 /* fp_u1_ENQ_CH */
        (U4)0x00000004U,                    /* u4_regr_en   */
        (U4)0x00000000U,                    /* u4_can_id    */
        (U2)0x0000U,                        /* u2_epdu_id   */
        (U2)CAN_LPFQ_CH_SECOC_TX            /* u2_que_ch    */
    }
};
#endif /* #if (CAN_LPR_RR_EN_IPDU_TX == 1U) */

#endif      /* CAN_LPR_CFG_PHY_TX_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/18/2025  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
