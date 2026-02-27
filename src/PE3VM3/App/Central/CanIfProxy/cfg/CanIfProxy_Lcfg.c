/* CanIfProxy_Lcfg_c_v0-0-0                                                 */
/****************************************************************************/
/* Copyright (C) 2025 Denso Co.,Ltd. All rights reserved.                   */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CanIfProxy_Lcfg/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "CanIfProxy.h"
#include "CanIfProxy_Lcfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define CANIFPROXY_START_SEC_VAR_POWER_ON_CLEARED_32
#include <CanIfProxy_MemMap.h>

/* Request buffer for Single frame */
uint8 CanIfProxy_u1SfReqBuffData[CANIFPROXY_CFG_REQ_BUFF_SF_NUM][CANIFPROXY_CFG_CAN_DATA_LEN_MAX];
uint8 CanIfProxy_u1SfReqBuffDataLength[CANIFPROXY_CFG_REQ_BUFF_SF_NUM];
uint32 CanIfProxy_u4SfReqBuffCanId[CANIFPROXY_CFG_REQ_BUFF_SF_NUM];

/* Request buffer for Multi frame */
uint8 CanIfProxy_u1MfReqBuffData[CANIFPROXY_CFG_MF_REQ_FRAME_NUM][CANIFPROXY_CFG_CAN_DATA_LEN_MAX];
uint8 CanIfProxy_u1MfReqBuffDataLength[CANIFPROXY_CFG_MF_REQ_FRAME_NUM];
uint32 CanIfProxy_u4MfReqBuffCanId;

#define CANIFPROXY_STOP_SEC_VAR_POWER_ON_CLEARED_32
#include <CanIfProxy_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define CANIFPROXY_START_SEC_CONFIG_DATA_32
#include <CanIfProxy_MemMap.h>

/* vCAN channel */
const uint8 CanIfProxy_cu1VcanCtrl = (uint8)CANIFPROXY_VCAN_CTRL;
/* vCAN Mailbox */
const uint8 CanIfProxy_cu1VcanMbox = (uint8)CANIFPROXY_VCAN_MBOX;
/* Number of single frame to request */
const uint16 CanIfProxy_cu2ReqBuffSfNum = (uint16)CANIFPROXY_CFG_REQ_BUFF_SF_NUM;
/* Number of frames in the multi frame to request */
const uint16 CanIfProxy_cu2MfReqFrameNum = (uint16)CANIFPROXY_CFG_MF_REQ_FRAME_NUM;
/* N_As [ms] */
const uint16 CanIfProxy_cu2NAs = (uint16)CANIFPROXY_CFG_N_AS;
/* N_Bs [ms] */
const uint16 CanIfProxy_cu2NBs = (uint16)CANIFPROXY_CFG_N_BS;
/* CF Period in Powr-On */
const uint8 CanIfProxy_cu1CfPeriodPwrOnSelf = (uint8)CANIFPROXY_CFG_CF_PERIOD_PWRON;
/* CF Period in Powr-Off */
const uint8 CanIfProxy_cu1CfPeriodPwrOffSelf = (uint8)CANIFPROXY_CFG_CF_PERIOD_PWROFF;
/* CF Period Default */
const uint8 CanIfProxy_cu1CfPeriodDef = (uint8)CANIFPROXY_CFG_CF_PERIOD_DEF;
/* Number of CF transmit per period in Power-On[time] */
const uint8 CanIfProxy_cu1CfTxNumPwrOnSelf = (uint8)CANIFPROXY_CFG_CF_TX_NUM_PWRON;
/* Number of CF transmit per period in Power-Off[time] */
const uint8 CanIfProxy_cu1CfTxNumPwrOffSelf = (uint8)CANIFPROXY_CFG_CF_TX_NUM_PWROFF;
/* Number of CF transmit per period Default[time] */
const uint8 CanIfProxy_cu1CfTxNumDef = (uint8)CANIFPROXY_CFG_CF_TX_NUM_DEF;
/* Limit number of messages in transit */
const uint8 CanIfProxy_cu1TxLimit = (uint8)CANIFPROXY_CFG_TX_LIMIT;
/* Number of Response CAN ID range */
const uint16 CanIfProxy_cu2ResCanIdRangeNum = (uint16)CANIFPROXY_CFG_RES_CANID_RANGE_NUM;

/* Response CAN ID table */
const CanIfProxy_U4RangeType CanIfProxy_cu4ResCanIdTble[CANIFPROXY_CFG_RES_CANID_RANGE_NUM] = {
	{ (uint32)0xD8DAE100, (uint32)0xD8DAE1FF },
	{ (uint32)0x58DAE100, (uint32)0x58DAE1FF },
	{ (uint32)0xD8DB33F1, (uint32)0xD8DB33F1 },
	{ (uint32)0x58DB33F1, (uint32)0x58DB33F1 },
	{ (uint32)0x00000708, (uint32)0x0000070F },
	{ (uint32)0x000007DF, (uint32)0x000007DF }
};

#define CANIFPROXY_STOP_SEC_CONFIG_DATA_32
#include <CanIfProxy_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Functions                                                                */
/*--------------------------------------------------------------------------*/

/**** End of File ***********************************************************/
