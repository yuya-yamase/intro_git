/* ChipCom_Lcfg_h_v1_0_0                                                    */
/****************************************************************************/
/* Copyright (C) 2025 Denso Co.,Ltd. All rights reserved.                   */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | ChipCom_Lcfg/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CHIPCOM_LCFG_H
#define CHIPCOM_LCFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#if CHIPCOM_BSW == CHIPCOM_BSW_MICROSAR
  #include "CDD_DebugLog.h"
#endif

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*++++++++++++++++*/
/* Debug          */
/*++++++++++++++++*/
/* Test mode */
#define CHIPCOM_TEST_MD_OFF                     (0U)
#define CHIPCOM_TEST_MD_LOG                     (1U)
#define CHIPCOM_TEST_MD_DRV                     (2U)
#define CHIPCOM_TEST_MD                         CHIPCOM_TEST_MD_OFF

/* Log level */
#define CHIPCOM_LOG_ERROR                       DEBUGLOG_ERROR
#define CHIPCOM_LOG_WARNING                     DEBUGLOG_WARNING
#define CHIPCOM_LOG_INFO                        DEBUGLOG_INFO
#define CHIPCOM_LOG_DEBUG                       DEBUGLOG_DEBUG

/* Output log function */
#if CHIPCOM_TEST_MD >= CHIPCOM_TEST_MD_LOG && CHIPCOM_BSW == CHIPCOM_BSW_MICROSAR
  #define CHIPCOM_LOG_MSG DEBUGLOG_LOG
#else
  #define CHIPCOM_LOG_MSG( log_level, message, ... )
#endif

#if CHIPCOM_TEST_MD == CHIPCOM_TEST_MD_DRV
void ChipCom_MainFunctionTest( void );
uint8 ChipCom_SendSignalDummy( Com_SignalIdType t_u2SignalId, const void* t_pvdSignalDataPtr );
#endif

/*++++++++++++++++*/
/* Fixed Value    */
/*++++++++++++++++*/
/* Data type */
#define CHIPCOM_DATA_TYPE_ARRAY					(0U)
#define CHIPCOM_DATA_TYPE_PRIMITIVE1			(1U)
#define CHIPCOM_DATA_TYPE_PRIMITIVE2			(2U)
#define CHIPCOM_DATA_TYPE_PRIMITIVE4			(4U)

/*++++++++++++++++*/
/* Configuration  */
/*++++++++++++++++*/
/* XSPI header size */
#define CHIPCOM_CFG_XSPI_HEADER_SIZE            (8U)
/* XSPI header size for interger array (lsb=4byte) */
#define CHIPCOM_CFG_XSPI_HEADER_SIZE_INT        (CHIPCOM_CFG_XSPI_HEADER_SIZE/4U)
/* XSPI FCC size */
#define CHIPCOM_CFG_XSPI_FCC_SIZE_INT           (4U/4U)

/* Number of handle (Data) */
#define CHIPCOM_CFG_HANDLE_NUM                  (37U)
/* Size of message buffer */
#define CHIPCOM_CFG_MSG_BUFF_SIZE               (401U)

/* Number of Packet buffer bank */
#define CHIPCOM_CFG_PKT_BANK_NUM                (2U)
/* Number of packets */
#define CHIPCOM_CFG_PKT_NUM                     (CHIPCOM_CFG_RX_PKT_NUM + CHIPCOM_CFG_TX_PKT_NUM)

/* Message table of each pakets */
#define CHIPCOM_CFG_PKT00_MSG_NUM               (2U)        /* PKT00 */
#define CHIPCOM_CFG_PKT01_MSG_NUM               (2U)        /* PKT01 */
#define CHIPCOM_CFG_PKT02_MSG_NUM               (2U)        /* PKT02 */
#define CHIPCOM_CFG_PKT03_MSG_NUM               (2U)        /* PKT03 */
#define CHIPCOM_CFG_PKT04_MSG_NUM               (4U)        /* PKT04 */
#define CHIPCOM_CFG_PKT05_MSG_NUM               (2U)        /* PKT05 */
#define CHIPCOM_CFG_PKT06_MSG_NUM               (2U)        /* PKT06 */

/* Size of received buffer */
#define CHIPCOM_CFG_RX_BUFF_SIZE                (1512U)
/* Size of transmit buffer */
#define CHIPCOM_CFG_TX_BUFF_SIZE                (1512U)
/* Size of received buffer for interger array (lsb=4byte) */
#define CHIPCOM_CFG_RX_BUFF_SIZE_INT            (CHIPCOM_CFG_RX_BUFF_SIZE/4U)
/* Size of transmit buffer for interger array (lsb=4byte) */
#define CHIPCOM_CFG_TX_BUFF_SIZE_INT            (CHIPCOM_CFG_TX_BUFF_SIZE/4U)
/* Address offset of received Variable-length area buffer for interger array (lsb=4byte) */
#define CHIPCOM_CFG_RX_BUFF_VLA_OFFS_INT        (CHIPCOM_CFG_RX_BUFF_VLA_OFFS/4U)
/* Address offset of transmit Variable-length area buffer for interger array (lsb=4byte) */
#define CHIPCOM_CFG_TX_BUFF_VLA_OFFS_INT        (CHIPCOM_CFG_TX_BUFF_VLA_OFFS/4U)

#if CHIPCOM_BSW == CHIPCOM_BSW_AUBIST

/* Core ID */
#define CHIPCOM_CORE_ID_MASTER                  (3U)
/* Number of satellite */
#define CHIPCOM_SATELLITE_NUM                   (0U)

/* Number of receive message */
#define CHIPCOM_CFG_RX_MSG_NUM                  (6U)
/* Number of transmit message */
#define CHIPCOM_CFG_TX_MSG_NUM                  (10U)
/* Number of message */
#define CHIPCOM_CFG_MSG_NUM                     (CHIPCOM_CFG_RX_MSG_NUM + CHIPCOM_CFG_TX_MSG_NUM)
/* Top ID of receive message */
#define CHIPCOM_CFG_MSG_RX_TOP                  (0U)

/* Number of receive packets */
#define CHIPCOM_CFG_RX_PKT_NUM                  (3U)
/* Number of transmit packets */
#define CHIPCOM_CFG_TX_PKT_NUM                  (4U)
/* Top ID of receive packets */
#define CHIPCOM_CFG_RX_PKT_TOP                  (0U)
/* Top ID of transmit packets */
#define CHIPCOM_CFG_TX_PKT_TOP                  (3U)

/* Size of received fixed-length area buffer */
#define CHIPCOM_CFG_RX_BUFF_FLA_SIZE            (24U)
/* Size of received Variable-length area buffer */
#define CHIPCOM_CFG_RX_BUFF_VLA_SIZE            (1476U)
/* Address offset of received Variable-length area buffer */
#define CHIPCOM_CFG_RX_BUFF_VLA_OFFS            (32U)
/* Size of transmit fixed-length area buffer */
#define CHIPCOM_CFG_TX_BUFF_FLA_SIZE            (396U)
/* Size of transmit Variable-length area buffer */
#define CHIPCOM_CFG_TX_BUFF_VLA_SIZE            (1104U)
/* Address offset of transmit Variable-length area buffer */
#define CHIPCOM_CFG_TX_BUFF_VLA_OFFS            (404U)

#else /* CHIPCOM_BSW == CHIPCOM_BSW_MICROSAR */

/* Core ID */
#define CHIPCOM_CORE_ID_MASTER                  (2U)
/* Number of satellite */
#define CHIPCOM_SATELLITE_NUM                   (0U)

/* Number of receive message */
#define CHIPCOM_CFG_RX_MSG_NUM                  (10U)
/* Number of transmit message */
#define CHIPCOM_CFG_TX_MSG_NUM                  (6U)
/* Number of message */
#define CHIPCOM_CFG_MSG_NUM                     (CHIPCOM_CFG_RX_MSG_NUM + CHIPCOM_CFG_TX_MSG_NUM)
/* Top ID of receive message */
#define CHIPCOM_CFG_MSG_RX_TOP                  (6U)

/* Number of receive packets */
#define CHIPCOM_CFG_RX_PKT_NUM                  (4U)
/* Number of transmit packets */
#define CHIPCOM_CFG_TX_PKT_NUM                  (3U)
/* Top ID of receive packets */
#define CHIPCOM_CFG_RX_PKT_TOP                  (3U)
/* Top ID of transmit packets */
#define CHIPCOM_CFG_TX_PKT_TOP                  (0U)

/* Size of received fixed-length area buffer */
#define CHIPCOM_CFG_RX_BUFF_FLA_SIZE            (396U)
/* Size of received Variable-length area buffer */
#define CHIPCOM_CFG_RX_BUFF_VLA_SIZE            (1104U)
/* Address offset of received Variable-length area buffer */
#define CHIPCOM_CFG_RX_BUFF_VLA_OFFS            (404U)
/* Size of transmit fixed-length area buffer */
#define CHIPCOM_CFG_TX_BUFF_FLA_SIZE            (24U)
/* Size of transmit Variable-length area buffer */
#define CHIPCOM_CFG_TX_BUFF_VLA_SIZE            (1476U)
/* Address offset of transmit Variable-length area buffer */
#define CHIPCOM_CFG_TX_BUFF_VLA_OFFS            (32U)

#endif

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Packet infomation type */
typedef struct {
	uint8 u1TxCoreId;
	uint8 u1StlId;
	const uint16* pu2MsgTbl;
	uint16 u2Period;
	uint16 u2MsgNum;
	uint16 u2TotalDataLen;
	uint16 u2MsgBuffOffs;
	uint16 u2SeqMax;
	uint16 u2Payload;
	uint16 u2LastTxLen;
	uint16 u2TxRxBuffOffs;
} ChipCom_PktInfoType;

/* Data infomation type */
typedef struct {
	uint16 u2DataLen;
	uint16 u2MsgBuffOffs;
	uint8 u1DataType;
	uint8 u1StlId;
} ChipCom_DataInfoType;

/* CanIf received indication function type */
typedef void (*ChipCom_CanIf_RxIndicationFuncType)(const CanMsgType*);
/* Get core ID function type */
#if CHIPCOM_BSW == CHIPCOM_BSW_AUBIST
typedef uint8 (*ChipCom_GetCoreIdFuncType)(void);
#else
typedef uint32 (*ChipCom_GetCoreIdFuncType)(void);
#endif

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define CHIPCOM_START_SEC_VAR_CLEARED_32
#include <ChipCom_MemMap.h>

/* Message status */
extern uint8 ChipCom_u1MsgStatus[CHIPCOM_CFG_MSG_NUM];
/* Message buffer */
extern uint8 ChipCom_u1MsgBuff[CHIPCOM_CFG_MSG_BUFF_SIZE];
/* Message buffer for satellite */
extern uint8 ChipCom_u1MsgBuffStl[CHIPCOM_SATELLITE_NUM][CHIPCOM_CFG_MSG_BUFF_SIZE];
/* Received time of messagest */
extern uint16 ChipCom_u2MsgRxTime[CHIPCOM_CFG_RX_MSG_NUM];

/* Packet reception history */
extern uint8 ChipCom_u1PktRxHst[CHIPCOM_CFG_RX_PKT_NUM];
/* Packet transmission request */
extern uint8 ChipCom_u1PktTxReq[CHIPCOM_CFG_TX_PKT_NUM];
/* Packet reception status */
extern uint8 ChipCom_u1RxStatus[CHIPCOM_CFG_RX_PKT_NUM];
/* Packet transmission status */
extern uint8 ChipCom_u1TxStatus[CHIPCOM_CFG_TX_PKT_NUM];
/* Packet buffer bank */
extern uint8 ChipCom_u1PktBuffBank[CHIPCOM_CFG_PKT_NUM];
/* Packet buffer */
extern uint8 ChipCom_u1PktBuff[CHIPCOM_CFG_PKT_BANK_NUM][CHIPCOM_CFG_MSG_BUFF_SIZE];
/* Packet transmission request time */
extern uint16 ChipCom_u2PktTxReqTime[CHIPCOM_CFG_TX_PKT_NUM];
/* Packet sequence number */
extern uint16 ChipCom_u2PktSeq[CHIPCOM_CFG_PKT_NUM];
/* Packet buffer offset */
extern uint16 ChipCom_u2PktBuffOffs[CHIPCOM_CFG_PKT_NUM];

/* Receive buffer */
extern uint32 ChipCom_u4RxBuff[CHIPCOM_CFG_RX_BUFF_SIZE_INT];
/* Transmit buffer */
extern uint32 ChipCom_u4TxBuff[CHIPCOM_CFG_TX_BUFF_SIZE_INT];

#define CHIPCOM_STOP_SEC_VAR_CLEARED_32
#include <ChipCom_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define CHIPCOM_START_SEC_CONFIG_DATA_32
#include <ChipCom_MemMap.h>

/* Master core ID */
extern const uint8 ChipCom_cu1CoreIdMst;
/* Number of satellite core */
extern const uint8 ChipCom_cu1StlCoreNum;
/* Number of handle(Data) */
extern const uint16 ChipCom_cu2HandleNum;
/* Number of message */
extern const uint16 ChipCom_cu2MsgNum;
/* Number of receive message */
extern const uint16 ChipCom_cu2RxMsgNum;
/* Top ID of receive message */
extern const uint16 ChipCom_cu2RxMsgTop;
/* Size of message buffer */
extern const uint16 ChipCom_cu2MsgBuffSize;
/* Number of Receive packets */
extern const uint16 ChipCom_cu2RxPktNum;
/* Number of Transmission packets */
extern const uint16 ChipCom_cu2TxPktNum;
/* Top ID of Receive packets */
extern const uint16 ChipCom_cu2RxPktIdTop;
/* Top ID of Transmission packets */
extern const uint16 ChipCom_cu2TxPktIdTop;
/* Number of Packet buffer bank */
extern const uint8 ChipCom_cu1PktBuffBankNum;
/* Receive packet buffer */
extern const uint8* ChipCom_pu1RxPktBuff[CHIPCOM_CFG_PKT_BANK_NUM];
/* Transmit packet buffer */
extern const uint8* ChipCom_pu1TxPktBuff[CHIPCOM_CFG_PKT_BANK_NUM];
/* Receive buffer fixed-length area */
extern uint8* const ChipCom_pu1RxBuffFla;
/* Transmit buffer fixed-length area */
extern uint8* const ChipCom_pu1TxBuffFla;
/* Receive buffer variable-length area */
extern uint8* const ChipCom_pu1RxBuffVla;
/* Transmit buffer variable-length area */
extern uint8* const ChipCom_pu1TxBuffVla;
/* Size of receive buffer */
extern const uint16 ChipCom_cu2RxBuffSizeInt;
/* Size of transmit buffer */
extern const uint16 ChipCom_cu2TxBuffSizeInt;
/* Size of transmit buffer fixed-length area */
extern const uint16 ChipCom_cu2TxBuffFlaSize;
/* Size of receive buffer variable-length area */
extern const uint16 ChipCom_cu2RxBuffVlaSize;
/* Size of transmit buffer variable-length area */
extern const uint16 ChipCom_cu2TxBuffVlaSize;
/* Size of XSPI header */
extern const uint16 ChipCom_cu2XspiHeaderSize;
/* Division ratio of the communication cycle */
extern const uint8 ChipCom_cu1ComTickDivRatio;
/* XSPI Channel for ChipCom */
extern const uint8 ChipCom_cu1XspiCh;
/* XSPI data initial value */
extern const uint8 ChipCom_cu1XspiDataInit;
/* XSPI header initial value table */
extern const uint8 ChipCom_cu1XspiHeaderInit[CHIPCOM_CFG_XSPI_HEADER_SIZE];
/* Message table of PKT00 */
extern const uint16 ChipCom_cu2Pkt00MsgTbl[CHIPCOM_CFG_PKT00_MSG_NUM];
/* Message table of PKT01 */
extern const uint16 ChipCom_cu2Pkt01MsgTbl[CHIPCOM_CFG_PKT01_MSG_NUM];
/* Message table of PKT02 */
extern const uint16 ChipCom_cu2Pkt02MsgTbl[CHIPCOM_CFG_PKT02_MSG_NUM];
/* Message table of PKT03 */
extern const uint16 ChipCom_cu2Pkt03MsgTbl[CHIPCOM_CFG_PKT03_MSG_NUM];
/* Message table of PKT04 */
extern const uint16 ChipCom_cu2Pkt04MsgTbl[CHIPCOM_CFG_PKT04_MSG_NUM];
/* Message table of PKT05 */
extern const uint16 ChipCom_cu2Pkt05MsgTbl[CHIPCOM_CFG_PKT05_MSG_NUM];
/* Message table of PKT06 */
extern const uint16 ChipCom_cu2Pkt06MsgTbl[CHIPCOM_CFG_PKT06_MSG_NUM];
/* Packet information table */
extern const ChipCom_PktInfoType ChipCom_cstPktInfoTbl[CHIPCOM_CFG_PKT_NUM];
/* Packet ID to Packet index table */
extern const uint16 ChipCom_cu2PktId2PktIdx[CHIPCOM_CFG_PKT_NUM];
/* Packet ID to message ID of check digit */
extern const uint16 ChipCom_cu2PktId2ChkDigitMsgId[CHIPCOM_CFG_PKT_NUM];
/* Message ID to message index */
extern const uint16 ChipCom_cu2MsdId2Idx[CHIPCOM_CFG_MSG_NUM];
/* Message ID to data ID of sequence number */
extern const uint16 ChipCom_cu2MsdId2SeqDataId[CHIPCOM_CFG_MSG_NUM];
/* Message received timeout table */
extern const uint16 ChipCom_cu2MsgRxTimeoutTbl[CHIPCOM_CFG_MSG_NUM];
/* Message buffer initial value table */
extern const uint8 ChipCom_cu1MsgBuffInit[CHIPCOM_CFG_MSG_BUFF_SIZE];
/* Data information table */
extern const ChipCom_DataInfoType ChipCom_cstDataInfoTbl[CHIPCOM_CFG_HANDLE_NUM];
/* Data handle to Message handle table */
extern const uint16 ChipCom_cu2DataHdl2MsgHdlTbl[CHIPCOM_CFG_HANDLE_NUM];

/* Receive indication function  */
extern const ChipCom_CanIf_RxIndicationFuncType ChipCom_pfcCanIf_RxIndication;
/* Get core ID function */
extern const ChipCom_GetCoreIdFuncType ChipCom_pfcGetCoreId;

#define CHIPCOM_STOP_SEC_CONFIG_DATA_32
#include <ChipCom_MemMap.h>

#endif /* CHIPCOM_LCFG_H */

/**** End of File ***********************************************************/
