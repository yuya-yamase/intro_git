/* CanIfProxy_Lcfg_h_v0-0-0                                                 */
/****************************************************************************/
/* Copyright (C) 2025 Denso Co.,Ltd. All rights reserved.                   */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CanIfProxy_Lcfg/HEADER                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CANIFPROXY_LCFG_H
#define CANIFPROXY_LCFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/* vCAN controller */
#define CANIFPROXY_VCAN_CTRL						(0x80U + 0x00U)
/* vCAN Mailbox */
#define CANIFPROXY_VCAN_MBOX						(0x06U)
/* Max length of CAN data */
#define CANIFPROXY_CFG_CAN_DATA_LEN_MAX				(32U)
/* Number of single frames in the request buffer (10 frame + 1) */
#define CANIFPROXY_CFG_REQ_BUFF_SF_NUM				(11U)
/* Number of frames in the multi frame to request ( 65650byte/31byte + 5 frame + 1) */
#define CANIFPROXY_CFG_MF_REQ_FRAME_NUM				(2124U)
/* N_As [ms] */
#define CANIFPROXY_CFG_N_AS							(1000U)
/* N_Bs [ms] */
#define CANIFPROXY_CFG_N_BS							(1000U)
/* CF Period in Powr-On */
#define CANIFPROXY_CFG_CF_PERIOD_PWRON				(14U)
/* CF Period in Powr-Off */
#define CANIFPROXY_CFG_CF_PERIOD_PWROFF				(1U)
/* CF Period Default */
#define CANIFPROXY_CFG_CF_PERIOD_DEF				(1U)
/* Number of CF transmit per period in Power-On[time] */
#define CANIFPROXY_CFG_CF_TX_NUM_PWRON				(1U)
/* Number of CF transmit per period in Power-Off[time] */
#define CANIFPROXY_CFG_CF_TX_NUM_PWROFF				(4U)
/* Number of CF transmit per period Default[time] */
#define CANIFPROXY_CFG_CF_TX_NUM_DEF				(1U)
/* Limit number of messages in transit */
#define CANIFPROXY_CFG_TX_LIMIT						(8U)
/* Number of Response CAN ID range */
#define CANIFPROXY_CFG_RES_CANID_RANGE_NUM			(4U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Unsigned integer range type */
typedef struct {
	uint32	u4Min;
	uint32	u4Max;
} CanIfProxy_U4RangeType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define CANIFPROXY_START_SEC_VAR_CLEARED_32
#include <CanIfProxy_MemMap.h>

/* Request buffer for Single frame */
extern uint8 CanIfProxy_u1SfReqBuffData[CANIFPROXY_CFG_REQ_BUFF_SF_NUM][CANIFPROXY_CFG_CAN_DATA_LEN_MAX];
extern uint8 CanIfProxy_u1SfReqBuffDataLength[CANIFPROXY_CFG_REQ_BUFF_SF_NUM];
extern uint32 CanIfProxy_u4SfReqBuffCanId[CANIFPROXY_CFG_REQ_BUFF_SF_NUM];

/* Request buffer for Multi frame */
extern uint8 CanIfProxy_u1MfReqBuffData[CANIFPROXY_CFG_MF_REQ_FRAME_NUM][CANIFPROXY_CFG_CAN_DATA_LEN_MAX];
extern uint8 CanIfProxy_u1MfReqBuffDataLength[CANIFPROXY_CFG_MF_REQ_FRAME_NUM];
extern uint32 CanIfProxy_u4MfReqBuffCanId;

#define CANIFPROXY_STOP_SEC_VAR_CLEARED_32
#include <CanIfProxy_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define CANIFPROXY_START_SEC_CONFIG_DATA_32
#include <CanIfProxy_MemMap.h>

/* vCAN channel */
extern const uint8 CanIfProxy_cu1VcanCtrl;
/* vCAN Mailbox */
extern const uint8 CanIfProxy_cu1VcanMbox;
/* Number of single frame to request */
extern const uint16 CanIfProxy_cu2ReqBuffSfNum;
/* Number of frames in the multi frame to request */
extern const uint16 CanIfProxy_cu2MfReqFrameNum;
/* N_As [ms] */
extern const uint16 CanIfProxy_cu2NAs;
/* N_Bs [ms] */
extern const uint16 CanIfProxy_cu2NBs;
/* CF Period in Powr-On */
extern const uint8 CanIfProxy_cu1CfPeriodPwrOnSelf;
/* CF Period in Powr-Off */
extern const uint8 CanIfProxy_cu1CfPeriodPwrOffSelf;
/* CF Period Default */
extern const uint8 CanIfProxy_cu1CfPeriodDef;
/* Number of CF transmit per period in Power-On[time] */
extern const uint8 CanIfProxy_cu1CfTxNumPwrOnSelf;
/* Number of CF transmit per period in Power-Off[time] */
extern const uint8 CanIfProxy_cu1CfTxNumPwrOffSelf;
/* Number of CF transmit per period Default[time] */
extern const uint8 CanIfProxy_cu1CfTxNumDef;
/* Limit number of messages in transit */
extern const uint8 CanIfProxy_cu1TxLimit;
/* Number of Response CAN ID range */
extern const uint16 CanIfProxy_cu2ResCanIdRangeNum;

/* Response CAN ID table */
extern const CanIfProxy_U4RangeType CanIfProxy_cu4ResCanIdTble[CANIFPROXY_CFG_RES_CANID_RANGE_NUM];

#define CANIFPROXY_STOP_SEC_CONFIG_DATA_32
#include <CanIfProxy_MemMap.h>

#endif /* CANIFPROXY_LCFG_H */

/**** End of File ***********************************************************/
