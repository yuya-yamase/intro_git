/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  CAN L-PDU Router : Ingress and Egress Definitions                                                                                */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  WARNING :                                                                                                                        */
/*  can_lpr_iae.h is included in can_lpr.h.                                                                                          */
/*  DO NOT include this file in any file even though this configuration header is public.                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef CAN_LPR_IAE_H
#define CAN_LPR_IAE_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPR_IAE_H_MAJOR                      (1)
#define CAN_LPR_IAE_H_MINOR                      (0)
#define CAN_LPR_IAE_H_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPR_NUM_ING                          (15U)

#define CAN_LPR_ING_PHY_CAN_MIN                  (0U)
#define CAN_LPR_ING_PHY_CAN_MAX                  (11U)
#define CAN_LPR_ING_VIR_CAN_MIN                  (12U)
#define CAN_LPR_ING_VIR_CAN_MAX                  (12U)

#define CAN_LPR_ING_G2M_2                        (3U)
#define CAN_LPR_ING_G2M_1                        (5U)
#define CAN_LPR_ING_G5M                          (7U)
#define CAN_LPR_ING_LOCAL                        (11U)
#define CAN_LPR_ING_VIR_0                        (12U)
#define CAN_LPR_ING_SECOC_TX                     (13U)
#define CAN_LPR_ING_SECOC_RX                     (14U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Routing Egress Enabled : Port              */
/*      1234567890123456789012345678901       */
#define CAN_LPR_REGR_EN_SECOC_TX                 (0x00000001U)
#define CAN_LPR_REGR_EN_SECOC_RX                 (0x00000002U)
#define CAN_LPR_REGR_EN_PHY_FQ_G2M1              (0x00000004U)
#define CAN_LPR_REGR_EN_PHY_FQ_G5M               (0x00000008U)
#define CAN_LPR_REGR_EN_PHY_FQ_LOCA              (0x00000010U)
#define CAN_LPR_REGR_EN_UDS_FQ_G2M1              (0x00000020U)
#define CAN_LPR_REGR_EN_PHY_TX_G2M1              (0x00000040U)
#define CAN_LPR_REGR_EN_PHY_TX_G5M               (0x00000080U)
#define CAN_LPR_REGR_EN_PHY_TX_LOCA              (0x00000100U)
#define CAN_LPR_REGR_EN_VIR_TX_0                 (0x00000200U)
#define CAN_LPR_REGR_EN_UDS_TX_VIR_0             (0x00000400U)
#define CAN_LPR_REGR_EN_PHY_RX_G2M1              (0x00000800U)
#define CAN_LPR_REGR_EN_PHY_RX_G2M2              (0x00001000U)
#define CAN_LPR_REGR_EN_PHY_RX_LOCA              (0x00002000U)

#define CAN_LPR_REGR_EN_BIT_PORT                 (0x00001fffU)
#define CAN_LPR_REGR_EN_BIT_DS28                 (0x00001ff3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPR_RR_EN_SECOC_TX                   (1U)      /* 1U   : SecOC Tx is enabled  and vd_g_CANLpRSecOCTRxPosHigh is disabled */
                                                           /* 2U   : SecOC Tx is enabled  and vd_g_CANLpRSecOCTRxPosHigh is enabled  */
                                                           /* else : SecOC Tx is disabled and vd_g_CANLpRSecOCTRxPosHigh is disabled */
#define CAN_LPR_RR_EN_SECOC_RX                   (0U)      /* 1U   : SecOC Rx is enabled  and vd_g_CANLpRSecOCTRxPosHigh is disabled */
                                                           /* 2U   : SecOC Rx is enabled  and vd_g_CANLpRSecOCTRxPosHigh is enabled  */
                                                           /* else : SecOC Rx is disabled and vd_g_CANLpRSecOCTRxPosHigh is disabled */
#define CAN_LPR_RR_EN_CANIF_RX                   (0U)      /* 1U   : Egress Port CanIf Rx is enabled,                  else disabled */
#define CAN_LPR_RR_EN_IPDU_TX                    (0U)      /* 1U   : Ingress Port I-PDU/Physical CAN Tx is enabled,    else disabled */
#define CAN_LPR_RR_EN_VIR_TX                     (1U)      /* 1U   : Egress Port Virtual CAN Tx is enabled,            else disabled */
#define CAN_LPR_RR_EN_UDS_TRX                    (1U)      /* 1U   : Egress Port UDS Tx/Rx is enabled,                 else disabled */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPR_PHY_TX_VACK_CH                   (12U)     /* <  0xffffU : Physical Tx/Virtual Ack is enabled                        */
                                                           /* >= 0xffffU : Physical Tx/Virtual Ack is disabled                       */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPR_CFG_DET                          (1U)      /* 1U   : Development Error Trace / vd_g_CANLpRCfgDet() is enabled,       */
                                                           /*                                                    else disabled       */
#define CAN_LPR_CFG_MAIN_START                   (0U)      /* 1U   : vd_g_CANLpRCfgMainStart()  is enabled,      else disabled       */
#define CAN_LPR_CFG_MAIN_FINISH                  (0U)      /* 1U   : vd_g_CANLpRCfgMainFinish() is enabled,      else disabled       */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_CANLpRDs28PhyTxEN(const U1 u1_a_ENA);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* CAN_LPR_IAE_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see can_lpr_cfg.c                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
