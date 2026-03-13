/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  CAN L-PDU Router : Ingress and Egress Configuration                                                                              */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  WARNING :                                                                                                                        */
/*  DO NOT include this file in any file because this configuration header is private.                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef CAN_LPR_CFG_UDS_TRX_H
#define CAN_LPR_CFG_UDS_TRX_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPR_CFG_UDS_TRX_H_MAJOR              (1)
#define CAN_LPR_CFG_UDS_TRX_H_MINOR              (0)
#define CAN_LPR_CFG_UDS_TRX_H_PATCH              (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPR_UDS_RX_VIR_EN                    (0U)
#define CAN_LPR_UDS_RD_TEST                      (0U) /* 0:Product configuration  1:Remote Diag Communication Test configuration     */
                                                      /* If this configuration is modified, you must also update the following file: */
                                                      /*   PE1VM1\BSW\Communication\CANLpR\config\vcan_tx_ack_cfg.c                  */
                                                      /*   PE2VM2\BSW\Communication\CANLpR\config\vcan_tx_ack_cfg.c                  */
                                                      /* to maintain configuration consistency.                                      */
#if (CAN_LPR_UDS_RD_TEST == 1U)
#warning "can_lpr_cfg_uds_trx.h : This build uses a configuration for the Remote Diagnostics Communication Test. Do not use for production."
#endif /* #if (CAN_LPR_UDS_RD_TEST == 1U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (CAN_LPR_UDS_RD_TEST == 1U) /* This configuration is copied from bevstep3-cockpit_mm-dd-yyyy_CANLpR_vxxx_rxxx_RDCTE.xlsx. */
static const U4             u4_sp_CAN_LPR_UDS_EGR_TA_G2M_1[] = {
    (U4)0xffffffffU,           /* CAN-ID bit#15-8 Target Address : 0x00 - 0x1f */
    (U4)0xffffffffU,           /* CAN-ID bit#15-8 Target Address : 0x20 - 0x3f */
    (U4)0xffffffffU,           /* CAN-ID bit#15-8 Target Address : 0x40 - 0x5f */
    (U4)0xffffffffU,           /* CAN-ID bit#15-8 Target Address : 0x60 - 0x7f */
    (U4)0xffffffffU,           /* CAN-ID bit#15-8 Target Address : 0x80 - 0x9f */
    (U4)0xffffffffU,           /* CAN-ID bit#15-8 Target Address : 0xa0 - 0xbf */
    (U4)0xffffffffU,           /* CAN-ID bit#15-8 Target Address : 0xc0 - 0xdf */
    (U4)0x0000aaaaU            /* CAN-ID bit#15-8 Target Address : 0xe0 - 0xff */
};
static const U4             u4_sp_CAN_LPR_UDS_EGR_SO_G2M_1[] = {
    (U4)0xef7fffffU,           /* CAN-ID bit#7-0  Source Address : 0x00 - 0x1f */
    (U4)0xffffffffU,           /* CAN-ID bit#7-0  Source Address : 0x20 - 0x3f */
    (U4)0xffffffffU,           /* CAN-ID bit#7-0  Source Address : 0x40 - 0x5f */
    (U4)0xffffffffU,           /* CAN-ID bit#7-0  Source Address : 0x60 - 0x7f */
    (U4)0xffffffffU,           /* CAN-ID bit#7-0  Source Address : 0x80 - 0x9f */
    (U4)0xffffffffU,           /* CAN-ID bit#7-0  Source Address : 0xa0 - 0xbf */
    (U4)0xffffffffU,           /* CAN-ID bit#7-0  Source Address : 0xc0 - 0xdf */
    (U4)0xffffd557U            /* CAN-ID bit#7-0  Source Address : 0xe0 - 0xff */
};
static const U4             u4_sp_CAN_LPR_UDS_REC_TA_G2M_1[] = {
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x00 - 0x1f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x20 - 0x3f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x40 - 0x5f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x60 - 0x7f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x80 - 0x9f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0xa0 - 0xbf */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0xc0 - 0xdf */
    (U4)0x00000000U            /* CAN-ID bit#7-0  Source Address : 0xe0 - 0xff */
};
static const U4             u4_sp_CAN_LPR_UDS_REC_SO_G2M_1[] = {
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x00 - 0x1f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x20 - 0x3f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x40 - 0x5f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x60 - 0x7f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x80 - 0x9f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0xa0 - 0xbf */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0xc0 - 0xdf */
    (U4)0x00000000U            /* CAN-ID bit#7-0  Source Address : 0xe0 - 0xff */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U4             u4_sp_CAN_LPR_UDS_EGR_TA_VIR_0[] = {
    (U4)0xef7fffffU,           /* CAN-ID bit#15-8 Target Address : 0x00 - 0x1f */
    (U4)0xffffffffU,           /* CAN-ID bit#15-8 Target Address : 0x20 - 0x3f */
    (U4)0xffffffffU,           /* CAN-ID bit#15-8 Target Address : 0x40 - 0x5f */
    (U4)0xffffffffU,           /* CAN-ID bit#15-8 Target Address : 0x60 - 0x7f */
    (U4)0xffffffffU,           /* CAN-ID bit#15-8 Target Address : 0x80 - 0x9f */
    (U4)0xffffffffU,           /* CAN-ID bit#15-8 Target Address : 0xa0 - 0xbf */
    (U4)0xffffffffU,           /* CAN-ID bit#15-8 Target Address : 0xc0 - 0xdf */
    (U4)0xffffd557U            /* CAN-ID bit#15-8 Target Address : 0xe0 - 0xff */
};
static const U4             u4_sp_CAN_LPR_UDS_EGR_SO_VIR_0[] = {
    (U4)0x10800000U,           /* CAN-ID bit#7-0  Source Address : 0x00 - 0x1f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x20 - 0x3f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x40 - 0x5f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x60 - 0x7f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x80 - 0x9f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0xa0 - 0xbf */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0xc0 - 0xdf */
    (U4)0x0000aaaaU            /* CAN-ID bit#7-0  Source Address : 0xe0 - 0xff */
};

#else /* This configuration is copied from bevstep3-cockpit_mm-dd-yyyy_CANLpR_vxxx_rxxx.xlsx. */

static const U4             u4_sp_CAN_LPR_UDS_EGR_TA_G2M_1[] = {
    (U4)0xffffffffU,           /* CAN-ID bit#15-8 Target Address : 0x00 - 0x1f */
    (U4)0xffffffffU,           /* CAN-ID bit#15-8 Target Address : 0x20 - 0x3f */
    (U4)0xffffffffU,           /* CAN-ID bit#15-8 Target Address : 0x40 - 0x5f */
    (U4)0xffffffffU,           /* CAN-ID bit#15-8 Target Address : 0x60 - 0x7f */
    (U4)0xffffffffU,           /* CAN-ID bit#15-8 Target Address : 0x80 - 0x9f */
    (U4)0xffffffffU,           /* CAN-ID bit#15-8 Target Address : 0xa0 - 0xbf */
    (U4)0xffffffffU,           /* CAN-ID bit#15-8 Target Address : 0xc0 - 0xdf */
    (U4)0x0000aaaaU            /* CAN-ID bit#15-8 Target Address : 0xe0 - 0xff */
};
static const U4             u4_sp_CAN_LPR_UDS_EGR_SO_G2M_1[] = {
    (U4)0xef7fffffU,           /* CAN-ID bit#7-0  Source Address : 0x00 - 0x1f */
    (U4)0xffffffffU,           /* CAN-ID bit#7-0  Source Address : 0x20 - 0x3f */
    (U4)0xffffffffU,           /* CAN-ID bit#7-0  Source Address : 0x40 - 0x5f */
    (U4)0xffffffffU,           /* CAN-ID bit#7-0  Source Address : 0x60 - 0x7f */
    (U4)0xffffffffU,           /* CAN-ID bit#7-0  Source Address : 0x80 - 0x9f */
    (U4)0xffffffffU,           /* CAN-ID bit#7-0  Source Address : 0xa0 - 0xbf */
    (U4)0xffffffffU,           /* CAN-ID bit#7-0  Source Address : 0xc0 - 0xdf */
    (U4)0xffffd555U            /* CAN-ID bit#7-0  Source Address : 0xe0 - 0xff */
};
static const U4             u4_sp_CAN_LPR_UDS_REC_TA_G2M_1[] = {
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x00 - 0x1f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x20 - 0x3f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x40 - 0x5f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x60 - 0x7f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x80 - 0x9f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0xa0 - 0xbf */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0xc0 - 0xdf */
    (U4)0x00000000U            /* CAN-ID bit#7-0  Source Address : 0xe0 - 0xff */
};
static const U4             u4_sp_CAN_LPR_UDS_REC_SO_G2M_1[] = {
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x00 - 0x1f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x20 - 0x3f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x40 - 0x5f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x60 - 0x7f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x80 - 0x9f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0xa0 - 0xbf */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0xc0 - 0xdf */
    (U4)0x00000000U            /* CAN-ID bit#7-0  Source Address : 0xe0 - 0xff */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U4             u4_sp_CAN_LPR_UDS_EGR_TA_VIR_0[] = {
    (U4)0xef7fffffU,           /* CAN-ID bit#15-8 Target Address : 0x00 - 0x1f */
    (U4)0xffffffffU,           /* CAN-ID bit#15-8 Target Address : 0x20 - 0x3f */
    (U4)0xffffffffU,           /* CAN-ID bit#15-8 Target Address : 0x40 - 0x5f */
    (U4)0xffffffffU,           /* CAN-ID bit#15-8 Target Address : 0x60 - 0x7f */
    (U4)0xffffffffU,           /* CAN-ID bit#15-8 Target Address : 0x80 - 0x9f */
    (U4)0xffffffffU,           /* CAN-ID bit#15-8 Target Address : 0xa0 - 0xbf */
    (U4)0xffffffffU,           /* CAN-ID bit#15-8 Target Address : 0xc0 - 0xdf */
    (U4)0xffffd555U            /* CAN-ID bit#15-8 Target Address : 0xe0 - 0xff */
};
static const U4             u4_sp_CAN_LPR_UDS_EGR_SO_VIR_0[] = {
    (U4)0x10800000U,           /* CAN-ID bit#7-0  Source Address : 0x00 - 0x1f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x20 - 0x3f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x40 - 0x5f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x60 - 0x7f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x80 - 0x9f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0xa0 - 0xbf */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0xc0 - 0xdf */
    (U4)0x0000aaaaU            /* CAN-ID bit#7-0  Source Address : 0xe0 - 0xff */
};
#endif /* #if (CAN_LPR_UDS_RD_TEST == 1U)*/

#if (CAN_LPR_UDS_RX_VIR_EN == 1U)
static const U4             u4_sp_CAN_LPR_UDS_REC_TA_VIR_0[] = {
    (U4)0x00800000U,           /* CAN-ID bit#7-0  Source Address : 0x00 - 0x1f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x20 - 0x3f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x40 - 0x5f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x60 - 0x7f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x80 - 0x9f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0xa0 - 0xbf */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0xc0 - 0xdf */
    (U4)0x00000000U            /* CAN-ID bit#7-0  Source Address : 0xe0 - 0xff */
};
static const U4             u4_sp_CAN_LPR_UDS_REC_SO_VIR_0[] = {
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x00 - 0x1f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x20 - 0x3f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x40 - 0x5f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x60 - 0x7f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0x80 - 0x9f */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0xa0 - 0xbf */
    (U4)0x00000000U,           /* CAN-ID bit#7-0  Source Address : 0xc0 - 0xdf */
    (U4)0x00000002U            /* CAN-ID bit#7-0  Source Address : 0xe0 - 0xff */
};
#endif /* #if (CAN_LPR_UDS_RX_VIR_EN == 1U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_CAN_LPR_UDS_TRX    st_gp_CAN_LPR_UDS_TRX[] = {
    /* G2M_1 -> VIR_0 */
    {
        &vd_g_CANLpREgrVirTx,                    /* fp_vd_EGR  */
        &u4_sp_CAN_LPR_UDS_EGR_TA_G2M_1[0U],     /* u4p_EGR_TA */
        &u4_sp_CAN_LPR_UDS_EGR_SO_G2M_1[0U],     /* u4p_EGR_SO */
        &u4_sp_CAN_LPR_UDS_REC_TA_G2M_1[0U],     /* u4p_REC_TA */
        &u4_sp_CAN_LPR_UDS_REC_SO_G2M_1[0U],     /* u4p_REC_SO */
        (U4)0x00000a5aU,                         /* u4_type_en */
        (U2)0x8000U,                             /* u2_epdu_id */
        (U2)0xffffU                              /* u2_hrh     */
    },
    /* VIR_0 -> G2M_1 */
    {
        &vd_g_CANLpREgrFqCAN,                    /* fp_vd_EGR  */
        &u4_sp_CAN_LPR_UDS_EGR_TA_VIR_0[0U],     /* u4p_EGR_TA */
        &u4_sp_CAN_LPR_UDS_EGR_SO_VIR_0[0U],     /* u4p_EGR_SO */ 
#if (CAN_LPR_UDS_RX_VIR_EN == 1U)
        &u4_sp_CAN_LPR_UDS_REC_TA_VIR_0[0U],     /* u4p_REC_TA */ 
        &u4_sp_CAN_LPR_UDS_REC_SO_VIR_0[0U],     /* u4p_REC_SO */
#else
        NULL_PTR,                                /* u4p_REC_TA */ 
        NULL_PTR,                                /* u4p_REC_SO */ 
#endif
        (U4)0x00005252U,                         /* u4_type_en */
        (U2)0xff87U,                             /* u2_epdu_id */
        (U2)0xffffU                              /* u2_hrh     */
    }
};
const U2                    u2_g_CAN_LPR_NUM_UDS_TRX = (U2)2U;

#endif      /* CAN_LPR_CFG_UDS_TRX_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     5/ 9/2025  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
