/* ChipCom_Lcfg_c_v1-0-0                                                    */
/****************************************************************************/
/* Copyright (C) 2025 Denso Co.,Ltd. All rights reserved.                   */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | ChipCom_Lcfg/CODE                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "xspi.h"

#include "ChipCom.h"
#include "ChipCom_Lcfg.h"

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
#define CHIPCOM_START_SEC_VAR_CLEARED_32
#include <ChipCom_MemMap.h>

/* Message status */
uint8 ChipCom_u1MsgStatus[CHIPCOM_CFG_MSG_NUM];
/* Message buffer */
uint8 ChipCom_u1MsgBuff[CHIPCOM_CFG_MSG_BUFF_SIZE];
/* Message buffer for satellite */
uint8 ChipCom_u1MsgBuffStl[CHIPCOM_SATELLITE_NUM][CHIPCOM_CFG_MSG_BUFF_SIZE];
/* Received time of messagest */
uint16 ChipCom_u2MsgRxTime[CHIPCOM_CFG_RX_MSG_NUM];

/* Packet reception history */
uint8 ChipCom_u1PktRxHst[CHIPCOM_CFG_RX_PKT_NUM];
/* Packet transmission request */
uint8 ChipCom_u1PktTxReq[CHIPCOM_CFG_TX_PKT_NUM];
/* Packet reception status */
uint8 ChipCom_u1RxStatus[CHIPCOM_CFG_RX_PKT_NUM];
/* Packet transmission status */
uint8 ChipCom_u1TxStatus[CHIPCOM_CFG_TX_PKT_NUM];
/* Packet buffer bank */
uint8 ChipCom_u1PktBuffBank[CHIPCOM_CFG_PKT_NUM];
/* Packet buffer */
uint8 ChipCom_u1PktBuff[CHIPCOM_CFG_PKT_BANK_NUM][CHIPCOM_CFG_MSG_BUFF_SIZE];
/* Packet transmission request time */
uint16 ChipCom_u2PktTxReqTime[CHIPCOM_CFG_TX_PKT_NUM];
/* Packet sequence number */
uint16 ChipCom_u2PktSeq[CHIPCOM_CFG_PKT_NUM];
/* Packet buffer offset */
uint16 ChipCom_u2PktBuffOffs[CHIPCOM_CFG_PKT_NUM];

/* Receive buffer */
uint32 ChipCom_u4RxBuff[CHIPCOM_CFG_RX_BUFF_SIZE_INT];
/* Transmit buffer */
uint32 ChipCom_u4TxBuff[CHIPCOM_CFG_TX_BUFF_SIZE_INT];

#define CHIPCOM_STOP_SEC_VAR_CLEARED_32
#include <ChipCom_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define CHIPCOM_START_SEC_CONFIG_DATA_32
#include <ChipCom_MemMap.h>

/* Master core ID */
const uint8 ChipCom_cu1CoreIdMst = (uint8)CHIPCOM_CORE_ID_MASTER;
/* Number of satellite core */
const uint8 ChipCom_cu1StlCoreNum = (uint8)CHIPCOM_SATELLITE_NUM;
/* Number of handle(Data) */
const uint16 ChipCom_cu2HandleNum = (uint16)CHIPCOM_CFG_HANDLE_NUM;
/* Number of message */
const uint16 ChipCom_cu2MsgNum = (uint16)CHIPCOM_CFG_MSG_NUM;
/* Number of receive message */
const uint16 ChipCom_cu2RxMsgNum = (uint16)CHIPCOM_CFG_RX_MSG_NUM;
/* Top ID of receive message */
const uint16 ChipCom_cu2RxMsgTop = (uint16)CHIPCOM_CFG_MSG_RX_TOP;
/* Size of message buffer */
const uint16 ChipCom_cu2MsgBuffSize = (uint16)CHIPCOM_CFG_MSG_BUFF_SIZE;
/* Number of Receive packets */
const uint16 ChipCom_cu2RxPktNum = (uint16)CHIPCOM_CFG_RX_PKT_NUM;
/* Number of Transmission packets */
const uint16 ChipCom_cu2TxPktNum = (uint16)CHIPCOM_CFG_TX_PKT_NUM;
/* Top ID of Receive packets */
const uint16 ChipCom_cu2RxPktIdTop = (uint16)CHIPCOM_CFG_RX_PKT_TOP;
/* Top ID of Transmission packets */
const uint16 ChipCom_cu2TxPktIdTop = (uint16)CHIPCOM_CFG_TX_PKT_TOP;
/* Number of Packet buffer bank */
const uint8 ChipCom_cu1PktBuffBankNum = (uint8)CHIPCOM_CFG_PKT_BANK_NUM;
/* Receive buffer fixed-length area */
uint8* const ChipCom_pu1RxBuffFla = (uint8*)&ChipCom_u4RxBuff[CHIPCOM_CFG_XSPI_HEADER_SIZE_INT];
/* Transmit buffer fixed-length area */
uint8* const ChipCom_pu1TxBuffFla = (uint8*)&ChipCom_u4TxBuff[CHIPCOM_CFG_XSPI_HEADER_SIZE_INT];
/* Receive buffer variable-length area */
uint8* const ChipCom_pu1RxBuffVla = (uint8*)&ChipCom_u4RxBuff[CHIPCOM_CFG_RX_BUFF_VLA_OFFS_INT];
/* Transmit buffer variable-length area */
uint8* const ChipCom_pu1TxBuffVla = (uint8*)&ChipCom_u4TxBuff[CHIPCOM_CFG_TX_BUFF_VLA_OFFS_INT];
/* Size of receive buffer */
const uint16 ChipCom_cu2RxBuffSizeInt = (uint16)(CHIPCOM_CFG_RX_BUFF_SIZE_INT - CHIPCOM_CFG_XSPI_FCC_SIZE_INT);
/* Size of transmit buffer */
const uint16 ChipCom_cu2TxBuffSizeInt = (uint16)(CHIPCOM_CFG_TX_BUFF_SIZE_INT - CHIPCOM_CFG_XSPI_FCC_SIZE_INT);
/* Size of transmit buffer fixed-length area */
const uint16 ChipCom_cu2TxBuffFlaSize = (uint16)CHIPCOM_CFG_TX_BUFF_FLA_SIZE;
/* Size of receive buffer variable-length area */
const uint16 ChipCom_cu2RxBuffVlaSize = (uint16)CHIPCOM_CFG_RX_BUFF_VLA_SIZE;
/* Size of transmit buffer variable-length area */
const uint16 ChipCom_cu2TxBuffVlaSize = (uint16)CHIPCOM_CFG_TX_BUFF_VLA_SIZE;
/* Size of XSPI header */
const uint16 ChipCom_cu2XspiHeaderSize = (uint16)CHIPCOM_CFG_XSPI_HEADER_SIZE;

/* Division ratio of the communication cycle */
const uint8 ChipCom_cu1ComTickDivRatio = (uint8)3U;
/* XSPI Channel for ChipCom */
const uint8 ChipCom_cu1XspiCh = (uint8)XSPI_CH_03;
/* XSPI data initial value */
const uint8 ChipCom_cu1XspiDataInit = (uint8)0x00U;
/* XSPI header initial value table */
const uint8 ChipCom_cu1XspiHeaderInit[CHIPCOM_CFG_XSPI_HEADER_SIZE] = {
    (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00
};

/* Message table of PKT00 */
const uint16 ChipCom_cu2Pkt00MsgTbl[CHIPCOM_CFG_PKT00_MSG_NUM] = {
    (uint16)   0U, (uint16)   1U
};
/* Message table of PKT01 */
const uint16 ChipCom_cu2Pkt01MsgTbl[CHIPCOM_CFG_PKT01_MSG_NUM] = {
    (uint16)   2U, (uint16)   3U
};
/* Message table of PKT02 */
const uint16 ChipCom_cu2Pkt02MsgTbl[CHIPCOM_CFG_PKT02_MSG_NUM] = {
    (uint16)   4U, (uint16)   5U
};
/* Message table of PKT03 */
const uint16 ChipCom_cu2Pkt03MsgTbl[CHIPCOM_CFG_PKT03_MSG_NUM] = {
    (uint16)   6U, (uint16)   7U
};
/* Message table of PKT04 */
const uint16 ChipCom_cu2Pkt04MsgTbl[CHIPCOM_CFG_PKT04_MSG_NUM] = {
    (uint16)   8U, (uint16)   9U, (uint16)  10U, (uint16)  11U
};
/* Message table of PKT05 */
const uint16 ChipCom_cu2Pkt05MsgTbl[CHIPCOM_CFG_PKT05_MSG_NUM] = {
    (uint16)  12U, (uint16)  13U
};
/* Message table of PKT06 */
const uint16 ChipCom_cu2Pkt06MsgTbl[CHIPCOM_CFG_PKT06_MSG_NUM] = {
    (uint16)  14U, (uint16)  15U
};

/* Packet information table */
const ChipCom_PktInfoType ChipCom_cstPktInfoTbl[CHIPCOM_CFG_PKT_NUM] = {
	/* u1TxCoreId, u1StlId,   pu2MsgTbl,                   u2Period,            u2MsgNum,      u2TotalDataLen, u2MsgBuffOffs, u2SeqMax,      u2Payload,     u2LastTxLen,   u2TxRxBuffOffs */
	{ (uint8)1U,   (uint8)0U, &ChipCom_cu2Pkt00MsgTbl[0U], (uint16)(    5U/5U), (uint16)   2U, (uint16)    5U, (uint16)   0U, (uint16)   0U, (uint16)   5U, (uint16)   5U, (uint16)    2U }, /* [PKT00] */
	{ (uint8)2U,   (uint8)0U, &ChipCom_cu2Pkt01MsgTbl[0U], (uint16)(    5U/5U), (uint16)   2U, (uint16)    5U, (uint16)   5U, (uint16)   0U, (uint16)   5U, (uint16)   5U, (uint16)    9U }, /* [PKT01] */
	{ (uint8)1U,   (uint8)0U, &ChipCom_cu2Pkt02MsgTbl[0U], (uint16)(  100U/5U), (uint16)   2U, (uint16)    5U, (uint16)  10U, (uint16)   0U, (uint16)   5U, (uint16)   5U, (uint16)   16U }, /* [PKT02] */
	{ (uint8)3U,   (uint8)0U, &ChipCom_cu2Pkt03MsgTbl[0U], (uint16)(    5U/5U), (uint16)   2U, (uint16)    5U, (uint16)  15U, (uint16)   0U, (uint16)   5U, (uint16)   5U, (uint16)    2U }, /* [PKT03] */
	{ (uint8)3U,   (uint8)0U, &ChipCom_cu2Pkt04MsgTbl[0U], (uint16)(    5U/5U), (uint16)   4U, (uint16)  368U, (uint16)  20U, (uint16)   0U, (uint16) 368U, (uint16) 368U, (uint16)    9U }, /* [PKT04] */
	{ (uint8)3U,   (uint8)0U, &ChipCom_cu2Pkt05MsgTbl[0U], (uint16)(   20U/5U), (uint16)   2U, (uint16)    8U, (uint16) 388U, (uint16)   0U, (uint16)   8U, (uint16)   8U, (uint16)  379U }, /* [PKT05] */
	{ (uint8)3U,   (uint8)0U, &ChipCom_cu2Pkt06MsgTbl[0U], (uint16)(  100U/5U), (uint16)   2U, (uint16)    5U, (uint16) 396U, (uint16)   0U, (uint16)   5U, (uint16)   5U, (uint16)  389U }  /* [PKT06] */
};

/* Packet ID to Packet index table */
const uint16 ChipCom_cu2PktId2PktIdx[CHIPCOM_CFG_PKT_NUM] = {
	(uint16)   0U, /* [PKT00] */
	(uint16)   1U, /* [PKT01] */
	(uint16)   2U, /* [PKT02] */
	(uint16)   0U, /* [PKT03] */
	(uint16)   1U, /* [PKT04] */
	(uint16)   2U, /* [PKT05] */
	(uint16)   3U  /* [PKT06] */
};

/* Packet ID to message ID of check digit */
const uint16 ChipCom_cu2PktId2ChkDigitMsgId[CHIPCOM_CFG_PKT_NUM] = {
	(uint16)   0U, /* [PKT00] */
	(uint16)   2U, /* [PKT01] */
	(uint16)   4U, /* [PKT02] */
	(uint16)   6U, /* [PKT03] */
	(uint16)   8U, /* [PKT04] */
	(uint16)  12U, /* [PKT05] */
	(uint16)  14U  /* [PKT06] */
};

/* Message ID to message index */
const uint16 ChipCom_cu2MsdId2Idx[CHIPCOM_CFG_MSG_NUM] = {
	(uint16)   0U, /* [0] */
	(uint16)   1U, /* [1] */
	(uint16)   2U, /* [2] */
	(uint16)   3U, /* [3] */
	(uint16)   4U, /* [4] */
	(uint16)   5U, /* [5] */
	(uint16)   0U, /* [6] */
	(uint16)   1U, /* [7] */
	(uint16)   2U, /* [8] */
	(uint16)   3U, /* [9] */
	(uint16)   4U, /* [10] */
	(uint16)   5U, /* [11] */
	(uint16)   6U, /* [12] */
	(uint16)   7U, /* [13] */
	(uint16)   8U, /* [14] */
	(uint16)   9U  /* [15] */
};

/* Message ID to data ID of sequence number */
const uint16 ChipCom_cu2MsdId2SeqDataId[CHIPCOM_CFG_MSG_NUM] = {
	(uint16)   0U, /* [0] */
	(uint16)   0U, /* [1] */
	(uint16)   2U, /* [2] */
	(uint16)   2U, /* [3] */
	(uint16)   4U, /* [4] */
	(uint16)   4U, /* [5] */
	(uint16)   6U, /* [6] */
	(uint16)   6U, /* [7] */
	(uint16)   8U, /* [8] */
	(uint16)   8U, /* [9] */
	(uint16)   8U, /* [10] */
	(uint16)   8U, /* [11] */
	(uint16)  33U, /* [12] */
	(uint16)  33U, /* [13] */
	(uint16)  35U, /* [14] */
	(uint16)  35U  /* [15] */
};

/* Message received timeout table */
const uint16 ChipCom_cu2MsgRxTimeoutTbl[CHIPCOM_CFG_MSG_NUM] = {
	(uint16)( 10000U/5U), /* [0] */
	(uint16)(    50U/5U), /* [1] */
	(uint16)( 10000U/5U), /* [2] */
	(uint16)( 10000U/5U), /* [3] */
	(uint16)( 10000U/5U), /* [4] */
	(uint16)(  1000U/5U), /* [5] */
	(uint16)( 10000U/5U), /* [6] */
	(uint16)( 10000U/5U), /* [7] */
	(uint16)( 10000U/5U), /* [8] */
	(uint16)(    50U/5U), /* [9] */
	(uint16)(    50U/5U), /* [10] */
	(uint16)( 10150U/5U), /* [11] */
	(uint16)( 10000U/5U), /* [12] */
	(uint16)(   200U/5U), /* [13] */
	(uint16)( 10000U/5U), /* [14] */
	(uint16)(  1000U/5U)  /* [15] */
};

/* Message buffer initial value table */
const uint8 ChipCom_cu1MsgBuffInit[CHIPCOM_CFG_MSG_BUFF_SIZE] = {
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00,                                                     /* [0] */
	(uint8)0x01,                                                                                            /* [1] */
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00,                                                     /* [2] */
	(uint8)0x00,                                                                                            /* [3] */
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00,                                                     /* [4] */
	(uint8)0x00,                                                                                            /* [5] */
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00,                                                     /* [6] */
	(uint8)0x00,                                                                                            /* [7] */
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00,                                                     /* [8] */
	(uint8)0x01,                                                                                            /* [9] */
	(uint8)0x00,                                                                                            /* [10] */
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, /* [11] */
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00,                           /* [12] */
	(uint8)0x01, (uint8)0x00, (uint8)0x01, (uint8)0x00, (uint8)0x01, (uint8)0x00, (uint8)0x01, (uint8)0x00, /* [13] */
	(uint8)0x01, (uint8)0x00, (uint8)0x01, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, /* [14] */
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x01, (uint8)0x00, (uint8)0x01, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, /* [15] */
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, /* [16] */
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, 
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, /* [17] */
	(uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF,                           /* [18] */
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00,                                                     /* [19] */
	(uint8)0x00,                                                                                            /* [20] */
	(uint8)0xFF, (uint8)0xFF, (uint8)0x00,                                                                  /* [21] */
	(uint8)0xFF,                                                                                            /* [22] */
	(uint8)0x00,                                                                                            /* [23] */
	(uint8)0x00, (uint8)0x00,                                                                               /* [24] */
	(uint8)0x00, (uint8)0x00,                                                                               /* [25] */
	(uint8)0x00, (uint8)0x00,                                                                               /* [26] */
	(uint8)0x00, (uint8)0x00,                                                                               /* [27] */
	(uint8)0x00, (uint8)0x00,                                                                               /* [28] */
	(uint8)0x00, (uint8)0x00,                                                                               /* [29] */
	(uint8)0x3F, (uint8)0x3F, (uint8)0x3F, (uint8)0x3F, (uint8)0x3F, (uint8)0x3F, (uint8)0x3F, (uint8)0x3F, /* [30] */
	(uint8)0x3F, (uint8)0x3F, (uint8)0x3F, (uint8)0x3F, (uint8)0x3F, (uint8)0x3F, (uint8)0x3F, (uint8)0x3F, 
	(uint8)0x3F, (uint8)0x00, 
	(uint8)0x00,                                                                                            /* [31] */
	(uint8)0x00,                                                                                            /* [32] */
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00,                                                     /* [33] */
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00,                                                     /* [34] */
	(uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00,                                                     /* [35] */
	(uint8)0x00                                                                                             /* [36] */
};

/* Data information table */
const ChipCom_DataInfoType ChipCom_cstDataInfoTbl[CHIPCOM_CFG_HANDLE_NUM] = {
	/* u2DataLen,    u2MsgBuffOffs, u1DataType,                          u1StlId  */
	{ (uint16)   4U, (uint16)   0U, (uint8)CHIPCOM_DATA_TYPE_PRIMITIVE4, (uint8)0U }, /* [0] */
	{ (uint16)   1U, (uint16)   4U, (uint8)CHIPCOM_DATA_TYPE_PRIMITIVE1, (uint8)0U }, /* [1] */
	{ (uint16)   4U, (uint16)   5U, (uint8)CHIPCOM_DATA_TYPE_PRIMITIVE4, (uint8)0U }, /* [2] */
	{ (uint16)   1U, (uint16)   9U, (uint8)CHIPCOM_DATA_TYPE_PRIMITIVE1, (uint8)0U }, /* [3] */
	{ (uint16)   4U, (uint16)  10U, (uint8)CHIPCOM_DATA_TYPE_PRIMITIVE4, (uint8)0U }, /* [4] */
	{ (uint16)   1U, (uint16)  14U, (uint8)CHIPCOM_DATA_TYPE_PRIMITIVE1, (uint8)0U }, /* [5] */
	{ (uint16)   4U, (uint16)  15U, (uint8)CHIPCOM_DATA_TYPE_PRIMITIVE4, (uint8)0U }, /* [6] */
	{ (uint16)   1U, (uint16)  19U, (uint8)CHIPCOM_DATA_TYPE_ARRAY     , (uint8)0U }, /* [7] */
	{ (uint16)   4U, (uint16)  20U, (uint8)CHIPCOM_DATA_TYPE_PRIMITIVE4, (uint8)0U }, /* [8] */
	{ (uint16)   1U, (uint16)  24U, (uint8)CHIPCOM_DATA_TYPE_ARRAY     , (uint8)0U }, /* [9] */
	{ (uint16)   1U, (uint16)  25U, (uint8)CHIPCOM_DATA_TYPE_PRIMITIVE1, (uint8)0U }, /* [10] */
	{ (uint16)   8U, (uint16)  26U, (uint8)CHIPCOM_DATA_TYPE_ARRAY     , (uint8)0U }, /* [11] */
	{ (uint16)   6U, (uint16)  34U, (uint8)CHIPCOM_DATA_TYPE_ARRAY     , (uint8)0U }, /* [12] */
	{ (uint16)  16U, (uint16)  40U, (uint8)CHIPCOM_DATA_TYPE_ARRAY     , (uint8)0U }, /* [13] */
	{ (uint16) 244U, (uint16)  56U, (uint8)CHIPCOM_DATA_TYPE_ARRAY     , (uint8)0U }, /* [14] */
	{ (uint16)   8U, (uint16) 300U, (uint8)CHIPCOM_DATA_TYPE_ARRAY     , (uint8)0U }, /* [15] */
	{ (uint16)  24U, (uint16) 308U, (uint8)CHIPCOM_DATA_TYPE_ARRAY     , (uint8)0U }, /* [16] */
	{ (uint16)   8U, (uint16) 332U, (uint8)CHIPCOM_DATA_TYPE_ARRAY     , (uint8)0U }, /* [17] */
	{ (uint16)   6U, (uint16) 340U, (uint8)CHIPCOM_DATA_TYPE_ARRAY     , (uint8)0U }, /* [18] */
	{ (uint16)   4U, (uint16) 346U, (uint8)CHIPCOM_DATA_TYPE_ARRAY     , (uint8)0U }, /* [19] */
	{ (uint16)   1U, (uint16) 350U, (uint8)CHIPCOM_DATA_TYPE_ARRAY     , (uint8)0U }, /* [20] */
	{ (uint16)   3U, (uint16) 351U, (uint8)CHIPCOM_DATA_TYPE_ARRAY     , (uint8)0U }, /* [21] */
	{ (uint16)   1U, (uint16) 354U, (uint8)CHIPCOM_DATA_TYPE_ARRAY     , (uint8)0U }, /* [22] */
	{ (uint16)   1U, (uint16) 355U, (uint8)CHIPCOM_DATA_TYPE_ARRAY     , (uint8)0U }, /* [23] */
	{ (uint16)   2U, (uint16) 356U, (uint8)CHIPCOM_DATA_TYPE_ARRAY     , (uint8)0U }, /* [24] */
	{ (uint16)   2U, (uint16) 358U, (uint8)CHIPCOM_DATA_TYPE_ARRAY     , (uint8)0U }, /* [25] */
	{ (uint16)   2U, (uint16) 360U, (uint8)CHIPCOM_DATA_TYPE_ARRAY     , (uint8)0U }, /* [26] */
	{ (uint16)   2U, (uint16) 362U, (uint8)CHIPCOM_DATA_TYPE_ARRAY     , (uint8)0U }, /* [27] */
	{ (uint16)   2U, (uint16) 364U, (uint8)CHIPCOM_DATA_TYPE_ARRAY     , (uint8)0U }, /* [28] */
	{ (uint16)   2U, (uint16) 366U, (uint8)CHIPCOM_DATA_TYPE_ARRAY     , (uint8)0U }, /* [29] */
	{ (uint16)  18U, (uint16) 368U, (uint8)CHIPCOM_DATA_TYPE_ARRAY     , (uint8)0U }, /* [30] */
	{ (uint16)   1U, (uint16) 386U, (uint8)CHIPCOM_DATA_TYPE_ARRAY     , (uint8)0U }, /* [31] */
	{ (uint16)   1U, (uint16) 387U, (uint8)CHIPCOM_DATA_TYPE_ARRAY     , (uint8)0U }, /* [32] */
	{ (uint16)   4U, (uint16) 388U, (uint8)CHIPCOM_DATA_TYPE_PRIMITIVE4, (uint8)0U }, /* [33] */
	{ (uint16)   4U, (uint16) 392U, (uint8)CHIPCOM_DATA_TYPE_ARRAY     , (uint8)0U }, /* [34] */
	{ (uint16)   4U, (uint16) 396U, (uint8)CHIPCOM_DATA_TYPE_PRIMITIVE4, (uint8)0U }, /* [35] */
	{ (uint16)   1U, (uint16) 400U, (uint8)CHIPCOM_DATA_TYPE_PRIMITIVE1, (uint8)0U }  /* [36] */
};

/* Data handle to Message handle table */
const uint16 ChipCom_cu2DataHdl2MsgHdlTbl[CHIPCOM_CFG_HANDLE_NUM] = {
	(uint16)0,    /* [0] */
	(uint16)1,    /* [1] */
	(uint16)2,    /* [2] */
	(uint16)3,    /* [3] */
	(uint16)4,    /* [4] */
	(uint16)5,    /* [5] */
	(uint16)6,    /* [6] */
	(uint16)7,    /* [7] */
	(uint16)8,    /* [8] */
	(uint16)9,    /* [9] */
	(uint16)10,   /* [10] */
	(uint16)10,   /* [11] */
	(uint16)10,   /* [12] */
	(uint16)10,   /* [13] */
	(uint16)10,   /* [14] */
	(uint16)10,   /* [15] */
	(uint16)10,   /* [16] */
	(uint16)10,   /* [17] */
	(uint16)11,   /* [18] */
	(uint16)11,   /* [19] */
	(uint16)11,   /* [20] */
	(uint16)11,   /* [21] */
	(uint16)11,   /* [22] */
	(uint16)11,   /* [23] */
	(uint16)11,   /* [24] */
	(uint16)11,   /* [25] */
	(uint16)11,   /* [26] */
	(uint16)11,   /* [27] */
	(uint16)11,   /* [28] */
	(uint16)11,   /* [29] */
	(uint16)11,   /* [30] */
	(uint16)11,   /* [31] */
	(uint16)11,   /* [32] */
	(uint16)12,   /* [33] */
	(uint16)13,   /* [34] */
	(uint16)14,   /* [35] */
	(uint16)15    /* [36] */
};

/* Receive indication function  */
#if CHIPCOM_BSW == CHIPCOM_BSW_AUBIST
extern void CanIfProxy_RxIndication( const CanMsgType* t_pstMsg );
const ChipCom_CanIf_RxIndicationFuncType ChipCom_pfcCanIf_RxIndication = CanIfProxy_RxIndication;
#else /* CHIPCOM_BSW == CHIPCOM_BSW_MICROSAR */
extern void CanIfStub_RxIndication( const CanMsgType* t_pstMsg );
const ChipCom_CanIf_RxIndicationFuncType ChipCom_pfcCanIf_RxIndication = CanIfStub_RxIndication;
#endif

/* Get core ID function  */
#if CHIPCOM_SATELLITE_NUM == (0U)
extern uint8 ChipCom_GetCoreIdDummy( void );
const ChipCom_GetCoreIdFuncType ChipCom_pfcGetCoreId = ChipCom_GetCoreIdDummy;
#else
#include "Os.h"
const ChipCom_GetCoreIdFuncType ChipCom_pfcGetCoreId = GetCoreID;
#endif

#define CHIPCOM_STOP_SEC_CONFIG_DATA_32
#include <ChipCom_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Functions                                                                */
/*--------------------------------------------------------------------------*/

/**** End of File ***********************************************************/
