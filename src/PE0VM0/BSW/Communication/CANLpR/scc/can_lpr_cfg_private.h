/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  CAN L-PDU Router                                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef CAN_LPR_CFG_H
#define CAN_LPR_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPR_CFG_H_MAJOR                      (1)
#define CAN_LPR_CFG_H_MINOR                      (0)
#define CAN_LPR_CFG_H_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "ComStack_Types.h"         /* src/PExVMy/BSW/CmnHdr/Platform/Platform_ExtDefs.h" */
                                    /* typedef      unsigned char       U1;   */
                                    /* typedef      unsigned short      U2;   */
                                    /* typedef      unsigned long       U4;   */
                                    /* typedef      signed char         S1;   */
                                    /* typedef      signed short        S2;   */
                                    /* typedef      signed long         S4;   */
                                    /* typedef      signed long         ZORN; */
#include "Can.h"
#include "ComM.h"
#include "bsw_comm_config.h"        /* BSW_COMM_BUS_TYPE_CHNUM(CAN)           */

#if (CAN_LPR_RR_EN_IPDU_TX == 1U)
#include "bsw_com_config.h"         /* BSW_COM_TX_MSG_NUM                     */
#endif /* #if (CAN_LPR_RR_EN_IPDU_TX == 1U) */

#include "can_lpr.h"
#include "can_lpfq.h"
#include "gpt_drv_frt.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPR_RR_UNK                           (0xffffU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPR_FQ_CAN_BIT_FQ_CH                 (0x007fU)
#define CAN_LPR_FQ_CAN_BIT_PDU_ID                (0xff80U)
#define CAN_LPR_FQ_CAN_LSB_PDU_ID                (7U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPR_FRT_INI                          (0xffffffffU)
#define CAN_LPR_FRT_MAX                          (0x7fffffffU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPR_PHY_TX_LOG_NWORD                 (3U)
#define CAN_LPR_PHY_TX_LOG_FRT                   (0U)
#define CAN_LPR_PHY_TX_LOG_HEAD                  (1U)
#define CAN_LPR_PHY_TX_LOG_CAN_ID                (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPR_PHY_TX_VACK_EN                   (0x0000U)
#define CAN_LPR_PHY_TX_VACK_DI                   (0xffffU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPR_PHY_TX_REQ_ACPT                  (0x00U)  /* Physical Tx Request is accepted                                         */
#define CAN_LPR_PHY_TX_PDU_NW_MAX                (18U)
#define CAN_LPR_PHY_TX_REQ_HEAD                  (0U)
#define CAN_LPR_PHY_TX_REQ_CAN_ID                (1U)
#define CAN_LPR_PHY_TX_REQ_SDU_B0                (2U)

#if ((CAN_LPR_PHY_TX_REQ_ACPT   != CAN_LPFQ_EAS_REQ_ACPT) || \
     (CAN_LPR_PHY_TX_PDU_NW_MAX != CAN_LPFQ_PDU_NW_MAX  ) || \
     (CAN_LPR_PHY_TX_REQ_HEAD   != CAN_LPFQ_WO_HEAD     ) || \
     (CAN_LPR_PHY_TX_REQ_CAN_ID != CAN_LPFQ_WO_CAN_ID   ) || \
     (CAN_LPR_PHY_TX_REQ_SDU_B0 != CAN_LPFQ_WO_SDU_B0   ))
#error "can_lpr_cfg_private.h : CAN_LPFQ_EAS_REQ_ACPT shall be equal to CAN_LPR_PHY_TX_REQ_ACPT(0x00U)."
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPR_NSM_NUM_TRX                      (3U)
#define CAN_LPR_NSM_FUL_EEE                      (0U)     /* Full Communication   - Tx Req Enabled  / Tx FIFO Enabled  / Rx Enabled  */
#define CAN_LPR_NSM_FUL_DEE                      (1U)     /* Full Communication   - Tx Req Disabled / Tx FIFO Enabled  / Rx Enabled  */
#define CAN_LPR_NSM_SIL_DDE                      (2U)     /* Silent Communication - Tx Req Disabled / Tx FIFO Disabled / Rx Enabled  */
#define CAN_LPR_NSM_NO__DDD                      (3U)     /* No Communication     - Tx Req Disabled / Tx FIFO Disabled / Rx Disabled */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPR_NUM_NET                          (BSW_COMM_BUS_TYPE_CHNUM(CAN))
#define CAN_LPR_NUM_IPDU_TX                      (BSW_COM_TX_MSG_NUM)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u4_CAN_LPR_FRT_MS(ms)                    ((U4)(ms) * ((U4)GPT_FRT_1US * (U4)1000U))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    void   ( * const          fp_vd_RES_CH)(const U2 u2_a_QUE_CH);
    U1     ( * const          fp_u1_DEQ_CH)(const U2 u2_a_QUE_CH, U4 * u4_ap_can, const U2 u2_a_NWORD);
                                                     /* The return value is CAN_LPR_PHY_TX_REQ_ACPT or not         */
    U4 *                      u4p_log;
    U4                        u4_regr_en;            /* = que_en : Tx Queue Enabled                                */
    U2                        u2_que_ch;             /* = "u2_a_QUE_CH" of fp_vd_RES_CH() and fp_u1_DEQ_CH()       */
    U2                        u2_vack;
}ST_CAN_LPR_PHY_TX;                                  /* Physical Tx                                                */

typedef struct{
    const ST_CAN_LPR_PHY_TX * stp_PHY_TX;
    U4                        u4_regr_en;            /* = lptx_en : L-PDU Tx Enabled                               */
    U2                        u2_nphy_tx;
    U2                        u2_ctrlr;
}ST_CAN_LPR_PHY_CH;                                  /* Physical Tx Channel                                        */

typedef struct{
    U1     ( * const          fp_u1_ENQ_CH)(const U2 u2_a_QUE_CH, const U4 * u4_ap_CAN);
    U4                        u4_regr_en;            /* = que_en : Tx Queue Enabled                                */
    U4                        u4_can_id;
    U2                        u2_epdu_id;
    U2                        u2_que_ch;
}ST_CAN_LPR_IPDU_TX;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U4                        u4_regr_en;            /* Egress Rule              / routing egress enabled            */
    U4                        u4_cid_min;            /* CAN ID Range Min                                             */
    U4                        u4_cid_max;            /* CAN ID Range Max                                             */
    U2                        u2_sdl_min;            /* Service Data Length Min [bytes]                              */
    U2                        u2_ep_begin;           /* index/offset of ST_CAN_LPR_ING->u2p_EPDU_ID                  */
}ST_CAN_LPR_RR;                                      /* Routing Rule                                                 */

typedef struct{
    U2                        u2_rr_begin;
    U2                        u2_num_rr;
}ST_CAN_LPR_RRMB;                                    /* Routing Rule by Rx Message Box                               */

typedef struct{
    void   ( * const          fp_vd_EGR)(const U2 u2_a_EPDU_ID, const CanMsgType * const st_ap_ECAN);
    U4                        u4_regr_en;            /* Egress Rule              / routing egress enabled            */
}ST_CAN_LPR_EGR;                                     /* Egress Port                                                  */

typedef struct{
    const ST_CAN_LPR_RR *     stp_RR;
    const ST_CAN_LPR_RRMB *   stp_RRMB;
    const ST_CAN_LPR_EGR *    stp_EGR;
    const U2 *                u2p_EPDU_ID;           /* Egress PDU-ID            / size = ST_CAN_LPR_ING->u2_num_egr */
    U4                        u4_ifrx_en;            /* Egress Rule              / CanIf Rx enabled                  */
    U2                        u2_num_rr;             /* number of routing rules  / size of stp_RR                    */
    U2                        u2_mb_min;             /* rx message box identifier min.                               */
    U2                        u2_mb_max;             /* rx message box identifier max.                               */
    U2                        u2_num_egr;            /* number of egress         / size of stp_EGR                   */
}ST_CAN_LPR_ING;                                     /* Ingress Port                                                 */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_CANLpRCfgInit(void);

#if (CAN_LPR_CFG_MAIN_START == 1U)
void    vd_g_CANLpRCfgMainStart(void);
#endif /* #if (CAN_LPR_CFG_MAIN_START == 1U) */
#if (CAN_LPR_CFG_MAIN_FINISH == 1U)
void    vd_g_CANLpRCfgMainFinish(void);
#endif /* #if (CAN_LPR_CFG_MAIN_FINISH == 1U) */

U4      u4_g_CANLpRCfgEgrEnabled(void);
void    vd_g_CANLpREgrbyRule(const ST_CAN_LPR_ING * const st_ap_ING,
                             const ST_CAN_LPR_RR * const st_ap_RR, const CanMsgType * const st_ap_ECAN);
void    vd_g_CANLpREgrFqCAN(const U2 u2_a_EPDU_ID, const CanMsgType * const st_ap_ECAN);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (CAN_LPR_CFG_DET == 1U)
#define CAN_LPR_DET_SECOC_TX                     (0U)
#define CAN_LPR_DET_PHY_TX                       (1U)
#define CAN_LPR_DET_VIR_TX                       (2U)
#define CAN_LPR_DET_FQ_CAN                       (3U)
void    vd_g_CANLpRCfgDet(const U1 u1_a_DET, const U1 u1_a_EAS_CHK, const U4 u4_a_CAN_ID);
#endif /* #if (CAN_LPR_CFG_DET == 1) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((CAN_LPR_RR_EN_SECOC_TX == 1U) || (CAN_LPR_RR_EN_SECOC_TX == 2U))
void    vd_g_CANLpREgrSecOCTx(const U2 u2_a_EPDU_ID, const CanMsgType * const st_ap_ECAN);
#endif /* #if ((CAN_LPR_RR_EN_SECOC_TX == 1U) || (CAN_LPR_RR_EN_SECOC_TX == 2U)) */
#if ((CAN_LPR_RR_EN_SECOC_RX == 1U) || (CAN_LPR_RR_EN_SECOC_RX == 2U))
void    vd_g_CANLpREgrSecOCRx(const U2 u2_a_EPDU_ID, const CanMsgType * const st_ap_ECAN);
#endif /* #if ((CAN_LPR_RR_EN_SECOC_RX == 1U) || (CAN_LPR_RR_EN_SECOC_RX == 2U)) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (CAN_LPR_RR_EN_CANIF_RX == 1U)
void    vd_g_CANLpREgrCanIfRx(const U2 u2_a_EPDU_ID, const CanMsgType * const st_ap_ECAN);
#endif /* #if (CAN_LPR_RR_EN_CANIF_RX == 1U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (CAN_LPR_RR_EN_VIR_TX == 1U)
void    vd_g_CANLpREgrVirTx(const U2 u2_a_EPDU_ID, const CanMsgType * const st_ap_ECAN);
#endif /* #if (CAN_LPR_RR_EN_VIR_TX == 1U) */

#if (CAN_LPR_RR_EN_UDS_TRX == 1U)
void    vd_g_CANLpREgrUdsTRx(const U2 u2_a_EPDU_ID, const CanMsgType * const st_ap_ECAN);
#endif /* #if (CAN_LPR_RR_EN_UDS_TRX == 1U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const U4                        u4_g_CAN_LPR_PHY_TX_TOUT;

extern const ST_CAN_LPR_PHY_TX         st_gp_CAN_LPR_PHY_TX[];
extern const U2                        u2_g_CAN_LPR_NUM_PHY_TX;

extern const ST_CAN_LPR_PHY_CH         st_gp_CAN_LPR_PHY_CH[];
extern const U1                        u1_g_CAN_LPR_NUM_PHY_CH;

extern const ST_CAN_LPR_PHY_CH * const stp_gp_CAN_LPR_PHY_CH_BY_CTRLR[];
extern const U1                        u1_g_CAN_LPR_NUM_PHY_CTRLR;

#if (CAN_LPR_RR_EN_IPDU_TX == 1U)
extern const ST_CAN_LPR_IPDU_TX        st_gp_CAN_LPR_IPDU_TX[CAN_LPR_NUM_IPDU_TX];
#endif /* #if (CAN_LPR_RR_EN_IPDU_TX == 1U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const ST_CAN_LPR_ING * const    stp_gp_CAN_LPR_ING[];
extern const U1                        u1_g_CAN_LPR_NUM_ING;

extern const U4                        u4_gp_CAN_LPR_REGR_EN_BY_NET[CAN_LPR_NUM_NET * CAN_LPR_NSM_NUM_TRX];

#endif      /* CAN_LPR_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see can_lpr.c                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
