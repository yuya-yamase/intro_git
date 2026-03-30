/* ChipCom_c_v1-0-0                                                         */
/****************************************************************************/
/* Copyright (C) 2025 Denso Co.,Ltd. All rights reserved.                   */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | ChipCom/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "Os.h"

#include "ChipCom.h"
#include "ChipCom_Lcfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*++++++++++++++++*/
/* Fixed Value    */
/*++++++++++++++++*/
/* Bit mask */
#define CHIPCOM_U4_MASK_BIT_07_00				((uint32)0x000000FFU)		/* 4byte 7-0bit mask value */
#define CHIPCOM_U4_MASK_BIT_15_08				((uint32)0x0000FF00U)		/* 4byte 15-8bit mask value */
#define CHIPCOM_U4_MASK_BIT_23_16				((uint32)0x00FF0000U)		/* 4byte 23-16bit mask value */
#define CHIPCOM_U4_MASK_BIT_31_24				((uint32)0xFF000000U)		/* 4byte 31-24bit mask value */
#define CHIPCOM_U2_MASK_BIT_07_00				((uint16)0x00FFU)			/* 2byte 7-0bit mask value */
#define CHIPCOM_U2_MASK_BIT_15_08				((uint16)0xFF00U)			/* 2byte 15-8bit mask value */
/* byte shift */
#define CHIPCOM_U1_SHIFT_1BYTE					((uint8)8U)					/* 1byte shift value */
#define CHIPCOM_U1_SHIFT_2BYTE					((uint8)16U)				/* 2byte shift value */
#define CHIPCOM_U1_SHIFT_3BYTE					((uint8)24U)				/* 4byte shift value */
/* integer size */
#define CHIPCOM_INT_SIZE						(4U)

/* Max value of tick */
#define CHIPCOM_U2_TICK_MAX						((uint16)0xFFFFU)
/* Initial value of Packets bank */
#define CHIPCOM_PKT_BANK_INIT					(0U)
/* Packet sequence number size */
#define CHIPCOM_PKT_SEQ_SIZE					(2U)
/* Max length of data */
#define CHIPCOM_DATA_LEN_MAX					(280U)
/* Max length of CAN data */
#define CHIPCOM_CAN_DATA_LEN_MAX				(32U)
/* Size of variable-length area header */
#define CHIPCOM_VLA_HEADER_SIZE					(2U)
/* Position of message count in the variable-length area header */
#define CHIPCOM_VLA_MSG_NUM_POS					(0U)
/* Size of message header in the variable-length area */
#define CHIPCOM_VLA_MSG_HEADER_SIZE				(5U)
/* Position of message ID in the variable-length area */
#define CHIPCOM_VLA_MSG_ID_POS					(0U)
/* Position of message length in the variable-length area */
#define CHIPCOM_VLA_MSG_LEN_POS					(4U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static void ChipCom_InitFlaRelatedData( void );
static void ChipCom_InitVlaTxRelatedData( void );
static void ChipCom_InitVlaRxRelatedData( void );
static void ChipCom_InitMsgRelatedData( void );
static void ChipCom_TransmitMsg( void );
static void ChipCom_RequestPktTransmission( uint16 t_u2PktId );
static void ChipCom_ReceiveMsg( void );
static void ChipCom_JudgeReceiveTimeout( void );
static void ChipCom_Transmit( void );
static void ChipCom_WriteFla( void );
static void ChipCom_Receive( void );
static void ChipCom_ReadFla( void );
static void ChipCom_ReadVla( void );
static Std_ReturnType ChipCom_WriteCanMsg( const CanMsgType* t_pstCanMsg );
static Std_ReturnType ChipCom_ReadCanMsg( CanMsgType* t_pstCanMsg, uint8* t_pu1Buff );
static void ChipCom_SwitchPktBuffBank( uint16 t_u2PktId );
static uint8 ChipCom_GetPrePktBuffBank( uint16 t_u2PktId );
static uint8 ChipCom_GetNextPktBuffBank( uint16 t_u2PktId );
static void ChipCom_SetCheckDigit( uint16 t_u2PktId );
static void ChipCom_SetVlaTxMsgNum( uint16 t_u2MsgNum );
static uint16 ChipCom_GetVlaTxMsgNum( void );
static void ChipCom_SetVlaRxMsgNum( uint16 t_u2MsgNum );
static uint16 ChipCom_GetVlaRxMsgNum( void );
static uint16 ChipCom_ConvertSizeByte2Int( uint16 t_u2Size );
static void ChipCom_Memset( uint8* t_pu1Dst, uint8 t_u1Value, uint16 t_u2Size );
static void ChipCom_Memcpy( uint8* t_pu1Dst, uint8* t_pu1Src, uint16 t_u2Size );
static void ChipCom_ConvertTypeToArray( uint8* t_pu1Dst, void* t_pvdSrc, uint16 t_u2Size, uint8 t_u1Type );
static void ChipCom_ConvertTypeFromArray( void* t_pvdDst, uint8* t_pu1Src, uint16 t_u2Size, uint8 t_u1Type );
static void ChipCom_Convert4byteToArray( uint8* t_pu1Dst, uint32 t_u4Src );
static void ChipCom_ConvertArrayTo4byte( uint32* t_pu4Dst, uint8* t_pu1Src );
static void ChipCom_Convert2byteToArray( uint8* t_pu1Dst, uint16 t_u2Src );
static void ChipCom_ConvertArrayTo2byte( uint16* t_pu2Dst, uint8* t_pu1Src );
uint8 ChipCom_GetCoreIdDummy( void );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define CHIPCOM_START_SEC_VAR_CLEARED_32
#include <ChipCom_MemMap.h>

/* Tick time for communication */
static uint8 ChipCom_u1ComTick;
/* Tick time for service layer */
static uint16 ChipCom_u2SrvTick;
/* Variable-length area transmit size */
static uint16 ChipCom_u2VlaTxSize;

#define CHIPCOM_STOP_SEC_VAR_CLEARED_32
#include <ChipCom_MemMap.h>

#define CHIPCOM_START_SEC_VAR_POWER_ON_CLEARED_32
#include <ChipCom_MemMap.h>
#define CHIPCOM_STOP_SEC_VAR_POWER_ON_CLEARED_32
#include <ChipCom_MemMap.h>

#define CHIPCOM_START_SEC_VAR_INIT_32
#include <ChipCom_MemMap.h>
#define CHIPCOM_STOP_SEC_VAR_INIT_32
#include <ChipCom_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define CHIPCOM_START_SEC_CONST
#include <ChipCom_MemMap.h>
#define CHIPCOM_STOP_SEC_CONST
#include <ChipCom_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Functions                                                                */
/*--------------------------------------------------------------------------*/
#define CHIPCOM_START_SEC_CODE
#include <ChipCom_MemMap.h>
/****************************************************************************/
/* Scheduled Functions                                                      */
/****************************************************************************/
/**---------------------------------------------------------------------------
 * [Description] Initialize this module.
 * [Arguments]   None
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
void ChipCom_Init( void )
{
	/* Initialize FLA related data */
	ChipCom_InitFlaRelatedData();

	/* Initialization of VLA transmission related data */
	ChipCom_InitVlaTxRelatedData();

	/* Initialization of VLA reception related data */
	ChipCom_InitVlaRxRelatedData();

	/* Initialization of message data */
	ChipCom_InitMsgRelatedData();

	return;
}

/**---------------------------------------------------------------------------
 * [Description] Deinitialize this module.
 * [Arguments]   None
 * [Return]      None
 * [Notes]       For Expansion
 *--------------------------------------------------------------------------*/
void ChipCom_DeInit( void )
{
	/* No processing */

	return;
}

/**---------------------------------------------------------------------------
 * [Description] Performs the processing of this module.
 * [Arguments]   None
 * [Return]      None
 * [Notes]       For Expansion
 *--------------------------------------------------------------------------*/
void ChipCom_MainFunction( void )
{
#if CHIPCOM_TEST_MD == CHIPCOM_TEST_MD_DRV
	/* Test */
	ChipCom_MainFunctionTest();
#endif

	return;
}

/**---------------------------------------------------------------------------
 * [Description] Performs the processing of this module.
 * [Arguments]   None
 * [Return]      None
 * [Notes]       Performs processing after application processing.
 *--------------------------------------------------------------------------*/
void ChipCom_MainFunctionPostApp( void )
{
	/* Transmit message */
	ChipCom_TransmitMsg();

	return;
}

/**---------------------------------------------------------------------------
 * [Description] Performs the processing of this module.
 * [Arguments]   None
 * [Return]      None
 * [Notes]       Performs processing before application processing.
 *--------------------------------------------------------------------------*/
void ChipCom_MainFunctionPreApp( void )
{
	/* Receive message */
	ChipCom_ReceiveMsg();

	/* Judge Timeout */
	ChipCom_JudgeReceiveTimeout();

	return;
}

/**---------------------------------------------------------------------------
 * [Description] Performs the processing of this module.
 * [Arguments]   None
 * [Return]      None
 * [Notes]       Performs processing before transmission.
 *--------------------------------------------------------------------------*/
void ChipCom_MainFunctionPreTx( void )
{
	uint8 t_u1ComTick;
	t_u1ComTick = ChipCom_u1ComTick;

	/* Judge communication cycle */
	if ( t_u1ComTick == (uint8)0U )
	{
		/* Transmit */
		ChipCom_Transmit();
	}

	/* Update communication cycle */
	t_u1ComTick++;

	if ( t_u1ComTick >= ChipCom_cu1ComTickDivRatio )
	{
		t_u1ComTick = (uint8)0U;
	}

	ChipCom_u1ComTick = t_u1ComTick;

	return;
}

/**---------------------------------------------------------------------------
 * [Description] Performs the processing of this module.
 * [Arguments]   None
 * [Return]      None
 * [Notes]       Performs processing after reception.
 *--------------------------------------------------------------------------*/
void ChipCom_MainFunctionPostRx( void )
{
	/* Receive */
	ChipCom_Receive();

	return;
}

/****************************************************************************/
/* Service API                                                              */
/****************************************************************************/
/**---------------------------------------------------------------------------
 * [Description] Send signal.
 * [Arguments]   t_u2SignalId          : Signal name
 *               t_pvdSignalDataPtr    : Data address
 * [Return]      uint8                 : E_OK
 *                                     : E_NOT_OK
 * [Notes]       None
 *--------------------------------------------------------------------------*/
uint8 ChipCom_SendSignal( Com_SignalIdType t_u2SignalId, const void* t_pvdSignalDataPtr )
{
	uint8* t_pu1MsgBuff;
	uint8 t_pu1DataArray[CHIPCOM_DATA_LEN_MAX];
	const ChipCom_DataInfoType* t_pstDataInfo;
	uint8 t_u1Rtn;
	uint8 t_u1CoreId;

	t_u1Rtn = (uint8)E_NOT_OK;

	/* Check arguments */
	if (   ( t_pvdSignalDataPtr != NULL_PTR )
		&& ( t_u2SignalId < ChipCom_cu2HandleNum ) )
	{
		/* Get data information */
		t_pstDataInfo = &ChipCom_cstDataInfoTbl[t_u2SignalId];

		/* Convert variable type */
		ChipCom_ConvertTypeToArray( &t_pu1DataArray[0U], (void*)t_pvdSignalDataPtr, t_pstDataInfo->u2DataLen, t_pstDataInfo->u1DataType );	/* MISRA DEVIATION: Not referenced before assignment by callee */
		
		/* Get Core ID */
		t_u1CoreId = (uint8)(ChipCom_pfcGetCoreId)();
		if ( t_u1CoreId == ChipCom_cu1CoreIdMst )
		{
			/* Get buffer */
			t_pu1MsgBuff = &ChipCom_u1MsgBuff[t_pstDataInfo->u2MsgBuffOffs];
		}
		else
		{
			/* Get message buffer of satellite */
			t_pu1MsgBuff = &ChipCom_u1MsgBuffStl[t_pstDataInfo->u1StlId][t_pstDataInfo->u2MsgBuffOffs];
		}
		/* Copy data */
		ChipCom_Memcpy( t_pu1MsgBuff, &t_pu1DataArray[0U], t_pstDataInfo->u2DataLen );

		t_u1Rtn = (uint8)E_OK;
	}

//CHIPCOM_LOG_MSG( CHIPCOM_LOG_DEBUG,"ChipCom_SendSignal: Rtn=[%u],SigID=[%u],SigAddr=[%08X],MsgBuffAddr=[%08X]\r\n", t_u1Rtn, t_u2SignalId, (uint32)t_pvdSignalDataPtr, (uint32)t_pu1MsgBuff );

	return t_u1Rtn;
}

/**---------------------------------------------------------------------------
 * [Description] Receive signal.
 * [Arguments]   t_u2SignalId          : Signal name
 *               t_pvdSignalDataPtr    : Data address
 * [Return]      uint8                 : E_OK
 *                                     : E_NOT_OK
 * [Notes]       None
 *--------------------------------------------------------------------------*/
uint8 ChipCom_ReceiveSignal( Com_SignalIdType t_u2SignalId, void* t_pvdSignalDataPtr )
{
	uint8* t_pu1MsgBuff;
	uint8 t_pu1DataArray[CHIPCOM_DATA_LEN_MAX];
	const ChipCom_DataInfoType* t_pstDataInfo;
	uint8 t_u1Rtn;
	uint8 t_u1CoreId;

	t_u1Rtn = (uint8)E_NOT_OK;

	/* Check arguments */
	if (   ( t_pvdSignalDataPtr != NULL_PTR )
		&& ( t_u2SignalId < ChipCom_cu2HandleNum ) )
	{
		/* Get data information */
		t_pstDataInfo = &ChipCom_cstDataInfoTbl[t_u2SignalId];

		/* Get Core ID */
		t_u1CoreId = (uint8)(ChipCom_pfcGetCoreId)();
		if ( t_u1CoreId == ChipCom_cu1CoreIdMst )
		{
			/* Get buffer */
			t_pu1MsgBuff = &ChipCom_u1MsgBuff[t_pstDataInfo->u2MsgBuffOffs];
		}
		else
		{
			/* Get message buffer of satellite */
			t_pu1MsgBuff = &ChipCom_u1MsgBuffStl[t_pstDataInfo->u1StlId][t_pstDataInfo->u2MsgBuffOffs];
		}
		
		/* Copy data */
		ChipCom_Memcpy( &t_pu1DataArray[0U], t_pu1MsgBuff, t_pstDataInfo->u2DataLen );	/* MISRA DEVIATION: Not referenced before assignment by callee */

		/* Convert variable type */
		ChipCom_ConvertTypeFromArray( t_pvdSignalDataPtr, &t_pu1DataArray[0U], t_pstDataInfo->u2DataLen, t_pstDataInfo->u1DataType );

		t_u1Rtn = (uint8)E_OK;
	}

//CHIPCOM_LOG_MSG( CHIPCOM_LOG_DEBUG,"ChipCom_ReceiveSignal: Rtn=[%u],SigID=[%u],SigAddr=[%08X],MsgBuffAddr=[%08X]\r\n", t_u1Rtn, t_u2SignalId, (uint32)t_pvdSignalDataPtr, (uint32)t_pu1MsgBuff );

	return t_u1Rtn;
}

/**---------------------------------------------------------------------------
 * [Description] Get data status.
 * [Arguments]   t_u2SignalId          : Signal name
 * [Return]      ChipCom_IpduStatusType: CHIPCOM_TIMEOUT
 *                                     : CHIPCOM_NO_RX
 * [Notes]       The return value is logical sum.
 *--------------------------------------------------------------------------*/
ChipCom_IpduStatusType ChipCom_GetSignalStatus( Com_SignalIdType t_u2SignalId )
{
	uint16 t_u2RxMsgId;
	ChipCom_IpduStatusType t_u1Status;

	t_u1Status = (ChipCom_IpduStatusType)CHIPCOM_NO_RX;

	/* Check arguments */
	if ( t_u2SignalId < ChipCom_cu2HandleNum )
	{
		/* Get message status */
		t_u2RxMsgId = ChipCom_cu2DataHdl2MsgHdlTbl[t_u2SignalId];
		t_u1Status = (ChipCom_IpduStatusType)ChipCom_u1MsgStatus[t_u2RxMsgId];
	}

//CHIPCOM_LOG_MSG( CHIPCOM_LOG_DEBUG,"ChipCom_GetSignalStatus: SigID=[%u],MsgID=[%u],Sts=[%u]\r\n", t_u2SignalId, t_u2RxMsgId, t_u1Status );

	return t_u1Status;
}

/**---------------------------------------------------------------------------
 * [Description] Transmit CAN message.
 * [Arguments]   t_pstMsg              : Message
 * [Return]      Std_ReturnType        : E_OK
 *                                     : E_NOT_OK
 * [Notes]       None
 *--------------------------------------------------------------------------*/
Std_ReturnType ChipCom_CanTransmit( const CanMsgType* t_pstMsg )
{
	Std_ReturnType t_u1Rtn;

	t_u1Rtn = (Std_ReturnType)E_NOT_OK;

	/* Check arguments */
	if (   ( t_pstMsg != NULL_PTR )
		&& ( t_pstMsg->ptData != NULL_PTR )
		&& ( t_pstMsg->u1Length <= (uint8)CHIPCOM_CAN_DATA_LEN_MAX ) )
	{
		/* Write CAN Messages (variable-length area) */
		t_u1Rtn = ChipCom_WriteCanMsg( t_pstMsg );
	}

	return t_u1Rtn;
}

/**---------------------------------------------------------------------------
 * [Description] Get error information.
 * [Arguments]   None
 * [Return]      uint8                 : ERR_KIND_NONE
 *                                     : ERR_KIND_TRX
 *                                     : ERR_KIND_INTG
 *                                     : ERR_KIND_ENCHG
 *                                     : ERR_KIND_TIN
 *                                     : ERR_KIND_RX_BUF_OVF
 * [Notes]       None
 *--------------------------------------------------------------------------*/
uint8 ChipCom_GetErrInfo( void )
{
	uint8 t_u1ErrInfo;

	/* Get XSPI error information */
	t_u1ErrInfo = xspi_GetErrInfo( ChipCom_cu1XspiCh );

	return t_u1ErrInfo;
}

/****************************************************************************/
/* Callback Functions and Notifications                                     */
/****************************************************************************/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/**---------------------------------------------------------------------------
 * [Description] Initialization of FLA related data.
 * [Arguments]   None
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static void ChipCom_InitFlaRelatedData( void )
{
	/* Initialize communication tick */
	ChipCom_u1ComTick = (uint8)0U;

	/* Initialize header */
	ChipCom_Memcpy( (uint8*)&ChipCom_u4TxBuff[0U], (uint8*)&ChipCom_cu1XspiHeaderInit[0U], ChipCom_cu2XspiHeaderSize );
	ChipCom_Convert2byteToArray( &ChipCom_pu1TxBuffFla[0U], ChipCom_cu2TxPktNum );

	/* Initialize data of fixed-length area */
/*	ChipCom_Memset( (uint8*)&ChipCom_pu1TxBuffFla[0U], ChipCom_cu1XspiDataInit, ChipCom_cu2TxBuffFlaSize );*/

	/* Initialize data of fixed-length area */
/*	ChipCom_Memset( (uint8*)&ChipCom_pu1RxBuffFla[0U], ChipCom_cu1XspiDataInit, ChipCom_cu2RxBuffFlaSize );*/

	return;
}

/**---------------------------------------------------------------------------
 * [Description] Initialization of VLA transmission related data.
 * [Arguments]   None
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static void ChipCom_InitVlaTxRelatedData( void )
{
	/* Initialize data of variable-length area */
	ChipCom_Memset( (uint8*)&ChipCom_pu1TxBuffVla[0U], ChipCom_cu1XspiDataInit, ChipCom_cu2TxBuffVlaSize );

	/* Initilaize the transmit size */
	ChipCom_u2VlaTxSize = (uint16)CHIPCOM_VLA_HEADER_SIZE;

	/* Initialize the number of transmit messages */
	ChipCom_SetVlaTxMsgNum( (uint16)0U );

	return;
}

/**---------------------------------------------------------------------------
 * [Description] Initialization of VLA reception related data.
 * [Arguments]   None
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static void ChipCom_InitVlaRxRelatedData( void )
{
	/* Initialize data of variable-length area */
/*	ChipCom_Memset( (uint8*)&ChipCom_pu1RxBuffVla[0U], ChipCom_cu1XspiDataInit, ChipCom_cu2RxBuffVlaSize );*/

	/* Initialize the number of Receive messages */
	ChipCom_SetVlaRxMsgNum( (uint16)0U );

	return;
}

/**---------------------------------------------------------------------------
 * [Description] Initialization of message related data.
 * [Arguments]   None
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static void ChipCom_InitMsgRelatedData( void )
{
	uint16 t_u2PktId;
	uint16 t_u2PktIdx;
	uint16 t_u2MsgId;
	uint8 t_u1StlId;

	/* Initialize message buffer */
	ChipCom_Memcpy( &ChipCom_u1MsgBuff[0U], (uint8*)&ChipCom_cu1MsgBuffInit[0U], ChipCom_cu2MsgBuffSize );
	for ( t_u1StlId = (uint8)0U; t_u1StlId < ChipCom_cu1StlCoreNum; t_u1StlId++ )
	{
		ChipCom_Memcpy( &ChipCom_u1MsgBuffStl[t_u1StlId][0U], (uint8*)&ChipCom_cu1MsgBuffInit[0U], ChipCom_cu2MsgBuffSize );
	}

	/* Initialize message status */
	for ( t_u2MsgId = (uint16)0U; t_u2MsgId < ChipCom_cu2MsgNum; t_u2MsgId++)
	{
		ChipCom_u1MsgStatus[t_u2MsgId] = (uint8)CHIPCOM_NO_RX;
	}

	/* Initialize Tick */
	ChipCom_u2SrvTick = (uint16)0U;

	/* Get packet ID */
	t_u2PktId = ChipCom_cu2TxPktIdTop;

	for ( t_u2PktIdx = (uint16)0U; t_u2PktIdx < ChipCom_cu2TxPktNum; t_u2PktIdx++ )
	{
		/* Initialize bank */
		ChipCom_u1PktBuffBank[t_u2PktId] = (uint8)CHIPCOM_PKT_BANK_INIT;

		/* Transmission request time */
		ChipCom_u2PktTxReqTime[t_u2PktIdx] = CHIPCOM_U2_TICK_MAX;

		/* Request all packets transmission */
		ChipCom_RequestPktTransmission( t_u2PktId );

		/* Count-up packet ID */
		t_u2PktId++;
	}

	return;
}

/**---------------------------------------------------------------------------
 * [Description] Transmit message.
 * [Arguments]   None
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static void ChipCom_TransmitMsg( void )
{
	uint8 t_u1CoreId;
	const ChipCom_PktInfoType* t_pstPktInfo;
	uint16 t_u2PktId;
	uint16 t_u2PktIdx;
	uint16 t_u2ElapsedTime;
	uint8* t_pu1MsgBuff;
	uint8* t_pu1MsgBuffStl;

	/* Get Core ID */
	t_u1CoreId = (uint8)(ChipCom_pfcGetCoreId)();

	/* Get packet ID */
	t_u2PktId = ChipCom_cu2TxPktIdTop;

	/* Repeat the following processing for each transmission packet */
	for ( t_u2PktIdx = (uint16)0U; t_u2PktIdx < ChipCom_cu2TxPktNum; t_u2PktIdx++ )
	{
		/* Get packet information */
		t_pstPktInfo = &ChipCom_cstPktInfoTbl[t_u2PktId];

		/* Calculate elapsed time */
		t_u2ElapsedTime = ChipCom_u2SrvTick - ChipCom_u2PktTxReqTime[t_u2PktIdx];
		/* todo: Should verify wrap-around behavior */

		/* Judge transmission */
		if ( t_u2ElapsedTime >= t_pstPktInfo->u2Period )
		{
			if ( t_u1CoreId == ChipCom_cu1CoreIdMst )
			{

//CHIPCOM_LOG_MSG( DEBUGLOG_INFO,"ChipCom_TransmitMsg: CoreId=[%u], PktIdx=[%u], SrvTick=[%u], PktTxReqTick=[%u], Elapsed=[%u]\r\n",
//    t_u1CoreId, t_u2PktIdx, ChipCom_u2SrvTick, ChipCom_u2PktTxReqTime[t_u2PktIdx], t_u2ElapsedTime );

				/* Request transmission */
				ChipCom_RequestPktTransmission( t_u2PktId );

				/* Set transmit request time */
				ChipCom_u2PktTxReqTime[t_u2PktIdx] = ChipCom_u2SrvTick;
			}
			else
			{
				if ( t_u1CoreId == t_pstPktInfo->u1TxCoreId )
				{
					/* Get message buffer */
					t_pu1MsgBuff = &ChipCom_u1MsgBuff[t_pstPktInfo->u2MsgBuffOffs];

					/* Get message buffer of satellite */
					t_pu1MsgBuffStl = &ChipCom_u1MsgBuffStl[t_pstPktInfo->u1StlId][t_pstPktInfo->u2MsgBuffOffs];

					/* Suspend Interrupts */
					SuspendOSInterrupts();

					/* Copy data from packet buffer to message buffer */
					ChipCom_Memcpy( t_pu1MsgBuff, t_pu1MsgBuffStl, t_pstPktInfo->u2TotalDataLen );

					/* Resume Interrupts */
					ResumeOSInterrupts();

//CHIPCOM_LOG_MSG( DEBUGLOG_INFO,"ChipCom_TransmitMsg: CoreId=[%u], PktIdx=[%u], SrvTick=[%u], PktTxReqTick=[%u], Elapsed=[%u], MsgBuffAddr=[%08X], MsgBuffStlAddr=[%08X]\r\n",
//    t_u1CoreId, t_u2PktIdx, ChipCom_u2SrvTick, ChipCom_u2PktTxReqTime[t_u2PktIdx], t_u2ElapsedTime, (uint32)t_pu1MsgBuff, (uint32)t_pu1MsgBuffStl );

				}
			}
		}

		/* Count-up packet ID */
		t_u2PktId++;
	}

	return;
}

/**---------------------------------------------------------------------------
 * [Description] Request packet transmission.
 * [Arguments]   t_u2MsgId             : Packet ID
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static void ChipCom_RequestPktTransmission( uint16 t_u2PktId )
{
	const ChipCom_PktInfoType* t_pstPktInfo;
	uint8* t_pu1PktBuff;
	uint8* t_pu1MsgBuff;
	uint16 t_u2PktIdx;
	uint8 t_u1PktBank;

	/* Set check digit */
	ChipCom_SetCheckDigit( t_u2PktId );

	/* Get packet ID */
	t_u2PktIdx = ChipCom_cu2PktId2PktIdx[t_u2PktId];

	/* Get packet information */
	t_pstPktInfo = &ChipCom_cstPktInfoTbl[t_u2PktId];

	/* Get packet buffer */
	t_u1PktBank = ChipCom_u1PktBuffBank[t_u2PktId];
	t_pu1PktBuff = &ChipCom_u1PktBuff[t_u1PktBank][t_pstPktInfo->u2MsgBuffOffs];

	/* Get message buffer */
	t_pu1MsgBuff = &ChipCom_u1MsgBuff[t_pstPktInfo->u2MsgBuffOffs];

	/* Suspend Interrupts */
	SuspendOSInterrupts();

	/* Copy data from message buffer to packet buffer */
	ChipCom_Memcpy( t_pu1PktBuff, t_pu1MsgBuff, t_pstPktInfo->u2TotalDataLen );

	/* Request transmission */
	ChipCom_u1PktTxReq[t_u2PktIdx] = (uint8)STD_ON;

	/* Resume Interrupts */
	ResumeOSInterrupts();

//CHIPCOM_LOG_MSG( DEBUGLOG_INFO,"ChipCom_RequestPktTransmission: PktIdx=[%u], PktBank=[%u], MsgBuffAddr=[%08X], PktBuffAddr=[%08X]\r\n",
//    t_u2PktIdx, t_u1PktBank, (uint32)t_pu1MsgBuff, (uint32)t_pu1PktBuff );

	return;
}

/**---------------------------------------------------------------------------
 * [Description] Receive message.
 * [Arguments]   None
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static void ChipCom_ReceiveMsg( void )
{
	uint8 t_u1CoreId;
	const ChipCom_PktInfoType* t_pstPktInfo;
	uint16 t_u2PktId;
	uint16 t_u2PktIdx;
	uint16 t_u2MsgId;
	uint16 t_u2MsgIdx;
	uint16 t_u2MsgCnt;
	uint8 t_u1PktBank;
	uint8 t_u1MsgStatus;
	uint8* t_pu1PktBuff;
	uint8* t_pu1MsgBuff;
	uint8* t_pu1MsgBuffStl;

	/* Get Core ID */
	t_u1CoreId = (uint8)(ChipCom_pfcGetCoreId)();

	/* Get packet ID */
	t_u2PktId = ChipCom_cu2RxPktIdTop;

	/* Repeat the following processing for each received packet */
	for ( t_u2PktIdx = (uint16)0U; t_u2PktIdx < ChipCom_cu2RxPktNum; t_u2PktIdx++ )
	{
		/* Check received */
		if ( ChipCom_u1PktRxHst[t_u2PktIdx] == (uint8)STD_ON )
		{
			/* Get packet information */
			t_pstPktInfo = &ChipCom_cstPktInfoTbl[t_u2PktId];

			/* Get message buffer */
			t_pu1MsgBuff = &ChipCom_u1MsgBuff[t_pstPktInfo->u2MsgBuffOffs];

			/* Master Core */
			if ( t_u1CoreId == ChipCom_cu1CoreIdMst )
			{
				/* Get packet buffer */
				t_u1PktBank = ChipCom_u1PktBuffBank[t_u2PktId];
				t_pu1PktBuff = &ChipCom_u1PktBuff[t_u1PktBank][t_pstPktInfo->u2MsgBuffOffs];

				/* Suspend Interrupts */
				SuspendOSInterrupts();

				/* Copy data from packet buffer to message buffer */
				ChipCom_Memcpy( t_pu1MsgBuff, t_pu1PktBuff, t_pstPktInfo->u2TotalDataLen );

				/* Clear received history */
				ChipCom_u1PktRxHst[t_u2PktIdx] = (uint8)STD_OFF;

				/* Resume Interrupts */
				ResumeOSInterrupts();

				for ( t_u2MsgCnt = (uint16)0U; t_u2MsgCnt < t_pstPktInfo->u2MsgNum; t_u2MsgCnt++ )
				{
					t_u2MsgId = t_pstPktInfo->pu2MsgTbl[t_u2MsgCnt];
					t_u2MsgIdx = ChipCom_cu2MsdId2Idx[t_u2MsgId];

					/* Set message status (NO_RX and TIMEOUT) */
					t_u1MsgStatus = ChipCom_u1MsgStatus[t_u2MsgId];
					t_u1MsgStatus &= (uint8)~( (uint8)CHIPCOM_NO_RX | (uint8)CHIPCOM_TIMEOUT );
					ChipCom_u1MsgStatus[t_u2MsgId] = t_u1MsgStatus;

					/* Set received time */
					ChipCom_u2MsgRxTime[t_u2MsgIdx] = ChipCom_u2SrvTick;
				}

//CHIPCOM_LOG_MSG( DEBUGLOG_INFO,"ChipCom_ReceiveMsg: CoreId=[%u], PktIdx=[%u], PktBank=[%u], MsgBuffAddr=[%08X], PktBuffAddr=[%08X]\r\n",
//    t_u1CoreId, t_u2PktIdx, t_u1PktBank, (uint32)t_pu1MsgBuff, (uint32)t_pu1PktBuff );

			}
			/* Satellite Core */
			else
			{
				/* Get message buffer of satellite */
				t_pu1MsgBuffStl = &ChipCom_u1MsgBuffStl[t_pstPktInfo->u1StlId][t_pstPktInfo->u2MsgBuffOffs];

				/* Suspend Interrupts */
				SuspendOSInterrupts();

				/* Copy data from packet buffer to message buffer */
				ChipCom_Memcpy( t_pu1MsgBuffStl, t_pu1MsgBuff, t_pstPktInfo->u2TotalDataLen );

				/* Resume Interrupts */
				ResumeOSInterrupts();

//CHIPCOM_LOG_MSG( DEBUGLOG_INFO,"ChipCom_ReceiveMsg: CoreId=[%u], PktIdx=[%u], PktBank=[%u], MsgBuffAddr=[%08X], MsgBuffStlAddr=[%08X]\r\n",
//    t_u1CoreId, t_u2PktIdx, t_u1PktBank, (uint32)t_pu1MsgBuff, (uint32)t_pu1MsgBuffStl );

			}
		}

		/* Count-up packet ID */
		t_u2PktId++;
	}

	return;
}

/**---------------------------------------------------------------------------
 * [Description] Judge receive timeout.
 * [Arguments]   None
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static void ChipCom_JudgeReceiveTimeout( void )
{
	uint8 t_u1CoreId;
	uint16 t_u2MsgId;
	uint16 t_u2MsgIdx;
	uint16 t_u2ElapsedTime;
	uint8 t_u1MsgStatus;
	uint8 t_u1MsgStatusNoRx;

	/* Get Core ID */
	t_u1CoreId = (uint8)(ChipCom_pfcGetCoreId)();

	/* Master Core */
	if ( t_u1CoreId == ChipCom_cu1CoreIdMst )
	{
		t_u2MsgId = ChipCom_cu2RxMsgTop;

		/* Count-up service layer tick */
		ChipCom_u2SrvTick++;

		for ( t_u2MsgIdx = (uint16)0U; t_u2MsgIdx < ChipCom_cu2RxMsgNum; t_u2MsgIdx++ )
		{

			t_u1MsgStatus = ChipCom_u1MsgStatus[t_u2MsgId];
			t_u1MsgStatusNoRx = t_u1MsgStatus & (uint8)CHIPCOM_NO_RX;
			if ( t_u1MsgStatusNoRx == CHIPCOM_STATUS_NONE )
			{
				/* Calculate elapsed time */
				t_u2ElapsedTime = ChipCom_u2SrvTick - ChipCom_u2MsgRxTime[t_u2MsgIdx];
				/* todo: Should verify wrap-around behavior */

				/* Judge timeout */
				if ( t_u2ElapsedTime >= ChipCom_cu2MsgRxTimeoutTbl[t_u2MsgId] )
				{
					/* Set message status */
					t_u1MsgStatus |= (uint8)CHIPCOM_TIMEOUT;
					ChipCom_u1MsgStatus[t_u2MsgId] = t_u1MsgStatus;
				}
			}

			t_u2MsgId++;
		}
	}

	return;
}

/**---------------------------------------------------------------------------
 * [Description] Transmit.
 * [Arguments]   None
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static void ChipCom_Transmit( void )
{
	uint8 t_u1SpiCondition;
	uint8 t_u1SpiRst;
/*	uint16 t_u2TxSize;*/

	/* Write FLA (fixed-length area) */
	ChipCom_WriteFla();

	/* Check SPI Condition */
	t_u1SpiCondition = xspi_GetCondition( ChipCom_cu1XspiCh );
	if (   ( t_u1SpiCondition == (uint8)XSPI_DCOND_IDLE )
		|| ( t_u1SpiCondition == (uint8)XSPI_DCOND_TRANSMIT ) )
	{

		/* Calculate transmit data size */
/*		t_u2TxSize = ChipCom_cu2XspiHeaderSize + ChipCom_cu2TxBuffFlaSize + ChipCom_u2VlaTxSize;*/
/*		t_u2TxSize = ChipCom_ConvertSizeByte2Int(t_u2TxSize);*/
		
		/* Suspend Interrupts */
		SuspendOSInterrupts();
		
		/* Write to SPI Buffer */
/*		t_u1SpiRst = xspi_Write( ChipCom_cu1XspiCh, (const uint32*)&ChipCom_u4TxBuff[0U], t_u2TxSize );*/
		t_u1SpiRst = xspi_Write( ChipCom_cu1XspiCh, (const uint32*)&ChipCom_u4TxBuff[0U], ChipCom_cu2TxBuffSizeInt );

		if ( t_u1SpiRst == (uint8)XSPI_OK )
		{
			/* Initialization of VLA related data */
			ChipCom_InitVlaTxRelatedData();
		}
		else
		{
			/* todo: Storing in DLT */
//CHIPCOM_LOG_MSG( DEBUGLOG_INFO,"ChipCom_Transmit: SpiRst=[%u]\r\n", t_u1SpiRst );
		}
		/* Resume Interrupts */
		ResumeOSInterrupts();
	}
	else
	{
//CHIPCOM_LOG_MSG( DEBUGLOG_INFO,"ChipCom_Transmit: SpiCond=[%u]\r\n", t_u1SpiCondition );
	}

	return;
}

/**---------------------------------------------------------------------------
 * [Description] Write fixed-length area.
 * [Arguments]   None
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static void ChipCom_WriteFla( void )
{
	const ChipCom_PktInfoType* t_pstPktInfo;
	uint16 t_u2PktId;
	uint16 t_u2PktIdx;
	uint16 t_u2PktSeq;
	uint16 t_u2PktBuffOffs;
	uint8 t_u1TxStatus;
	uint8 t_u1PktBank;
	uint8* t_pu1PktBuff;
	uint8* t_pu1TxBuff;
	uint16 t_u2RemainPayloadLen;

	/* Get packet ID top */
	t_u2PktId = ChipCom_cu2TxPktIdTop;

	/* Repeat the following processing for each transmission packet */
	for ( t_u2PktIdx = (uint16)0U; t_u2PktIdx < ChipCom_cu2TxPktNum; t_u2PktIdx++ )
	{
		/* Get Transmission status */
		t_u1TxStatus = ChipCom_u1TxStatus[t_u2PktIdx];

		/* Get packet sequence number */
		t_u2PktSeq = ChipCom_u2PktSeq[t_u2PktId];

		/* Get packet buffer offset */
		t_u2PktBuffOffs = ChipCom_u2PktBuffOffs[t_u2PktId];

		/* Get packet information */
		t_pstPktInfo = &ChipCom_cstPktInfoTbl[t_u2PktId];

		/* Accept requests */
		if ( ChipCom_u1PktTxReq[t_u2PktIdx] == (uint8)STD_ON )
		{
			/* Suspend Interrupts not required because this function runs on the high-priority task. */

			/* Switch packet buffer bank */
			ChipCom_SwitchPktBuffBank( t_u2PktId );

			/* Clear request */
			ChipCom_u1PktTxReq[t_u2PktIdx] = (uint8)STD_OFF;

			/* Resume Interrupts not required because this function runs on the high-priority task */

			/* Initilaze status */
			t_u1TxStatus = (uint8)STD_ACTIVE;
			t_u2PktSeq = (uint16)0U;
			t_u2PktBuffOffs = t_pstPktInfo->u2MsgBuffOffs;
		}

		/* Write */
		if ( t_u1TxStatus == (uint8)STD_ACTIVE )
		{
			/* Get transmit buffer */
			t_pu1TxBuff = (uint8*)&ChipCom_pu1TxBuffFla[t_pstPktInfo->u2TxRxBuffOffs];

			/* Convert message ID to array */
			ChipCom_Convert2byteToArray( t_pu1TxBuff, t_u2PktSeq );

			/* Get transmit buffer of data part */
			t_pu1TxBuff = &t_pu1TxBuff[CHIPCOM_PKT_SEQ_SIZE];

			if ( t_u2PktSeq <= t_pstPktInfo->u2SeqMax )
			{
				/* Get packet buffer */
				t_u1PktBank = ChipCom_GetPrePktBuffBank( t_u2PktId );
				t_pu1PktBuff = &ChipCom_u1PktBuff[t_u1PktBank][t_u2PktBuffOffs];

				if ( t_u2PktSeq < t_pstPktInfo->u2SeqMax )
				{
					/* Copy data from packet buffer to transmit buffer */
					ChipCom_Memcpy( t_pu1TxBuff, t_pu1PktBuff, t_pstPktInfo->u2Payload );
					/* Update packet buffer offset */
					t_u2PktBuffOffs += t_pstPktInfo->u2Payload;
				}
				else
				{
					/* Copy data from packet buffer to transmit buffer */
					ChipCom_Memcpy( t_pu1TxBuff, t_pu1PktBuff, t_pstPktInfo->u2LastTxLen );
					t_u2RemainPayloadLen = t_pstPktInfo->u2Payload - t_pstPktInfo->u2LastTxLen;
					ChipCom_Memset( &t_pu1TxBuff[t_pstPktInfo->u2LastTxLen], ChipCom_cu1XspiDataInit, t_u2RemainPayloadLen );
				}
			}
			else
			{
				/* Set initial value to transmit buffer */
				ChipCom_Memset( t_pu1TxBuff, ChipCom_cu1XspiDataInit, t_pstPktInfo->u2Payload );

				/* Initilaze status */
				t_u1TxStatus = (uint8)STD_IDLE;
			}

			/* Count-up packet sequence number */
			t_u2PktSeq++;
		}

//CHIPCOM_LOG_MSG( DEBUGLOG_INFO,"ChipCom_WriteFla: PktIdx=[%u], PktSeq=[%u], PktBank=[%u], PktBuffAddr=[%08X], TxBuffAddr=[%08X]\r\n",
//    t_u2PktIdx, t_u2PktSeq, t_u1PktBank, (uint32)t_pu1PktBuff, (uint32)t_pu1TxBuff );

		/* Set packet buffer offset */
		ChipCom_u2PktBuffOffs[t_u2PktId] = t_u2PktBuffOffs;

		/* Set packet sequence number */
		ChipCom_u2PktSeq[t_u2PktId] = t_u2PktSeq;

		/* Set transition status */
		ChipCom_u1TxStatus[t_u2PktIdx] = t_u1TxStatus;

		/* Count-up packet ID */
		t_u2PktId++;
	}

	return;
}

/**---------------------------------------------------------------------------
 * [Description] Receive.
 * [Arguments]   None
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static void ChipCom_Receive( void )
{
	uint8 t_u1SpiRst;

	while(1)
	{
		/* Suspend Interrupts */
		SuspendOSInterrupts();
		
		/* Read from SPI Buffer */
		t_u1SpiRst = xspi_Read( ChipCom_cu1XspiCh,  &ChipCom_u4RxBuff[0U], ChipCom_cu2RxBuffSizeInt );
		
		/* todo: Setting the actual data size to be transmit reduces the processing load. */
		/* Resume Interrupts */
		ResumeOSInterrupts();
		
	
		/* Check SPI result */
		if ( t_u1SpiRst == (uint8)XSPI_OK )
		{
			
			/* Read FLA (fixed-length area) */
			ChipCom_ReadFla();
	
			/* Read VLA (variable-length area) */
			ChipCom_ReadVla();
	
			/* Initialize of reception related data */
			ChipCom_InitVlaRxRelatedData();
		}
		else
		{
			/* todo: Storing in DLT when synchronizing with SPI receive processing */
	//CHIPCOM_LOG_MSG( DEBUGLOG_INFO,"ChipCom_Receive: SpiRst=[%u]\r\n", t_u1SpiRst );
			break;
		}
	}

	return;
}

/**---------------------------------------------------------------------------
 * [Description] Read fixed-length area.
 * [Arguments]   None
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static void ChipCom_ReadFla( void )
{
	const ChipCom_PktInfoType* t_pstPktInfo;
	uint8* t_pu1RxBuff;
	uint8* t_pu1PktBuff;
	uint16 t_u2PktNum;
	uint16 t_u2PktId;
	uint16 t_u2PktIdx;
	uint16 t_u2PktSeq;
	uint16 t_u2PktSeqRcv;
	uint16 t_u2PktBuffOffs;
	uint8 t_u1RxStatus;
	uint8 t_u1PktBank;

	/* Get number of packet */
	ChipCom_ConvertArrayTo2byte( &t_u2PktNum, &ChipCom_pu1RxBuffFla[0U] );

	/* Packets exist? */
	if ( t_u2PktNum == ChipCom_cu2RxPktNum )
	{
		/* Get packet ID top */
		t_u2PktId = ChipCom_cu2RxPktIdTop;

		/* Repeat the following processing for each reception packet */
		for ( t_u2PktIdx = (uint16)0U; t_u2PktIdx < ChipCom_cu2RxPktNum; t_u2PktIdx++ )
		{
			/* Get reception status */
			t_u1RxStatus = ChipCom_u1RxStatus[t_u2PktIdx];

			/* Get Previous packet sequence number */
			t_u2PktSeq = ChipCom_u2PktSeq[t_u2PktId];

			/* Get packet buffer offset */
			t_u2PktBuffOffs = ChipCom_u2PktBuffOffs[t_u2PktId];

			/* Get packet information */
			t_pstPktInfo = &ChipCom_cstPktInfoTbl[t_u2PktId];

			/* Get receive buffer */
			t_pu1RxBuff = (uint8*)&ChipCom_pu1RxBuffFla[t_pstPktInfo->u2TxRxBuffOffs];

			/* Get received packet sequence number */
			ChipCom_ConvertArrayTo2byte( &t_u2PktSeqRcv, t_pu1RxBuff );

//CHIPCOM_LOG_MSG( DEBUGLOG_INFO,"ChipCom_ReadFla: PktIdx=[%u], RxStatusPre=[%u], PktSeqPre=[%u], PktSeqRcv=[%u], PktBuffOffsPre=[%u], RxBuffAddr=[%08X]\r\n",
//    t_u2PktIdx, t_u1RxStatus, t_u2PktSeq, t_u2PktSeqRcv, t_u2PktBuffOffs, (uint32)t_pu1RxBuff );

			/* New? */
			if ( t_u2PktSeqRcv == (uint16)0U )
			{
				/* Initilize packet sequence number */
				t_u2PktSeq = (uint16)0U;
				/* Initilize packet buffer offset */
				t_u2PktBuffOffs = t_pstPktInfo->u2MsgBuffOffs;
				/* reception transmit status */
				t_u1RxStatus = (uint8)STD_ACTIVE;
			}
			/* Continued? */
			else
			{
				t_u2PktSeq++;
				/* Check sequential number */
				if ( t_u2PktSeqRcv != t_u2PktSeq )
				{
					/* Initilize packet sequence number */
					t_u2PktSeq = (uint16)0U;
					/* Initilize packet buffer offset */
					t_u2PktBuffOffs = t_pstPktInfo->u2MsgBuffOffs;
					/* Reception transmit status */
					t_u1RxStatus = (uint8)STD_IDLE;
				}
			}

			/* Read */
			if ( t_u1RxStatus == (uint8)STD_ACTIVE )
			{
				if ( t_u2PktSeq <= t_pstPktInfo->u2SeqMax )
				{
					/* Get packet buffer */
					t_u1PktBank = ChipCom_GetNextPktBuffBank( t_u2PktId );
					t_pu1PktBuff = &ChipCom_u1PktBuff[t_u1PktBank][t_u2PktBuffOffs];

					/* Get transmit buffer of data part */
					t_pu1RxBuff = &t_pu1RxBuff[CHIPCOM_PKT_SEQ_SIZE];

					if ( t_u2PktSeq < t_pstPktInfo->u2SeqMax )
					{
						/* Copy data from receive buffer to packet buffer */
						ChipCom_Memcpy( t_pu1PktBuff, t_pu1RxBuff, t_pstPktInfo->u2Payload );
						/* Update packet buffer offset */
						t_u2PktBuffOffs += t_pstPktInfo->u2Payload;
					}
					else if ( t_u2PktSeq == t_pstPktInfo->u2SeqMax )
					{
						/* Copy data from receive buffer to packet buffer */
						ChipCom_Memcpy( t_pu1PktBuff, t_pu1RxBuff, t_pstPktInfo->u2LastTxLen );

						/* Switch Bank */
						ChipCom_SwitchPktBuffBank( t_u2PktId );
						/* Set receive history */
						ChipCom_u1PktRxHst[t_u2PktIdx] = (uint8)STD_ON;

						/* Initilize packet sequence number */
						t_u2PktSeq = (uint16)0U;
						/* Initilize packet buffer offset */
						t_u2PktBuffOffs = t_pstPktInfo->u2MsgBuffOffs;
						/* reception transmit status */
						t_u1RxStatus = (uint8)STD_IDLE;
					}
					else
					{
						/* No processing */
					}

//CHIPCOM_LOG_MSG( DEBUGLOG_INFO,"ChipCom_ReadFla: PktIdx=[%u], PktSeq=[%u], PktBankNext=[%u], RxStatus=[%u], RxHst=[%u], PktBuffOffs=[%u], RxBuffAddr=[%08X]\r\n",
//    t_u2PktIdx, t_u2PktSeq, t_u1PktBank, t_u1RxStatus, ChipCom_u1PktRxHst[t_u2PktIdx], t_u2PktBuffOffs, (uint32)t_pu1RxBuff );

				}
			}

			/* Set packet buffer offset */
			ChipCom_u2PktBuffOffs[t_u2PktId] = t_u2PktBuffOffs;

			/* Set packet sequence number */
			ChipCom_u2PktSeq[t_u2PktId] = t_u2PktSeq;

			/* Set reception status */
			ChipCom_u1RxStatus[t_u2PktIdx] = t_u1RxStatus;

			/* Count-up packet ID */
			t_u2PktId++;
		}

	}

	return;
}

/**---------------------------------------------------------------------------
 * [Description] Read variable-length area.
 * [Arguments]   None
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static void ChipCom_ReadVla( void )
{
	uint8* t_pu1RxBuff;
	uint16 t_u2RxMsgNum;
	uint16 t_u2MsgIdx;
	uint16 t_u2RxSize;
	uint16 t_u2RxSizeTotal;
	uint8 t_pu1CanData[CHIPCOM_CAN_DATA_LEN_MAX];
	Std_ReturnType t_u1ReadRst;
	CanMsgType t_stCanMsg;

	t_u2RxSizeTotal = (uint16)CHIPCOM_VLA_HEADER_SIZE;
	t_stCanMsg.ptData = &t_pu1CanData[0U];

	/* Read number of message */
	t_u2RxMsgNum = ChipCom_GetVlaRxMsgNum();

	/* Get message */
	t_pu1RxBuff = (uint8*)&ChipCom_pu1RxBuffVla[CHIPCOM_VLA_HEADER_SIZE];

	for ( t_u2MsgIdx = (uint16)0U; t_u2MsgIdx < t_u2RxMsgNum; t_u2MsgIdx++ )
	{
		/* Read CAN messages */
		t_u1ReadRst = ChipCom_ReadCanMsg( &t_stCanMsg, t_pu1RxBuff );	/* MISRA DEVIATION: Not referenced before assignment by callee */

		if ( t_u1ReadRst == (Std_ReturnType)E_OK )
		{
			/* Calculate received size */
			t_u2RxSize = (uint16)CHIPCOM_VLA_MSG_HEADER_SIZE + (uint16)t_stCanMsg.u1Length;
			t_u2RxSizeTotal += t_u2RxSize;

			/* Check buffer length exceeds the maximum length */
			if ( t_u2RxSizeTotal <= ChipCom_cu2RxBuffVlaSize )
			{
				/* Notify that a CAN message has been received */
				(ChipCom_pfcCanIf_RxIndication)( (const CanMsgType*)&t_stCanMsg );

				/* Get next message */
				t_pu1RxBuff = &t_pu1RxBuff[t_u2RxSize];
			}
			else
			{
				/* todo: Storing in DLT */
				break;
			}
		}
		else
		{
			/* todo: Storing in DLT */
			break;
		}
	}

	return;
}

/**---------------------------------------------------------------------------
 * [Description] Write CAN messages.
 * [Arguments]   t_pstCanMsg           : CAN message
 * [Return]      Std_ReturnType        : E_OK
 *                                     : E_NOT_OK
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static Std_ReturnType ChipCom_WriteCanMsg( const CanMsgType* t_pstCanMsg )
{
	uint8* t_pu1TxBuff;
	uint16 t_u2VlaTxMsgNum;
	uint16 t_u2VlaTxSize;
	uint16 t_u2EmptySize;
	uint16 t_u2MsgTxSize;
	uint8 t_pu1Headr[CHIPCOM_VLA_MSG_HEADER_SIZE];
	Std_ReturnType t_u1Rtn;

	/* Initialize result */
	t_u1Rtn = (Std_ReturnType)E_NOT_OK;

	t_u2VlaTxSize = ChipCom_u2VlaTxSize;
	t_u2EmptySize = ChipCom_cu2TxBuffVlaSize - t_u2VlaTxSize;
	t_u2MsgTxSize = (uint16)CHIPCOM_VLA_MSG_HEADER_SIZE + (uint16)t_pstCanMsg->u1Length;

	/* Check Empty Size */
	if ( t_u2MsgTxSize <= t_u2EmptySize )
	{
		/* Suspend Interrupts not required because caller is CanIf only */

		/* Add number of VLA transmit message  */
		t_u2VlaTxMsgNum = ChipCom_GetVlaTxMsgNum();
		t_u2VlaTxMsgNum++;
		ChipCom_SetVlaTxMsgNum( t_u2VlaTxMsgNum );

		/* Make header */
		ChipCom_Convert4byteToArray( &t_pu1Headr[CHIPCOM_VLA_MSG_ID_POS], t_pstCanMsg->u4Id );	/* MISRA DEVIATION: Not referenced before assignment by callee */
		t_pu1Headr[CHIPCOM_VLA_MSG_LEN_POS] = t_pstCanMsg->u1Length;

		/* Set message to buffer */
		t_pu1TxBuff = (uint8*)&ChipCom_pu1TxBuffVla[t_u2VlaTxSize];
		ChipCom_Memcpy( t_pu1TxBuff, &t_pu1Headr[0U], (uint16)CHIPCOM_VLA_MSG_HEADER_SIZE );
		t_pu1TxBuff = &t_pu1TxBuff[CHIPCOM_VLA_MSG_HEADER_SIZE];
		ChipCom_Memcpy( t_pu1TxBuff, t_pstCanMsg->ptData, (uint16)t_pstCanMsg->u1Length );

		/* Add VLA transmit size */
		t_u2VlaTxSize += t_u2MsgTxSize;
		ChipCom_u2VlaTxSize = t_u2VlaTxSize;

		/* Resume Interrupts not required because caller is CanIf only */

		/* Set result */
		t_u1Rtn = (Std_ReturnType)E_OK;
	}

	return t_u1Rtn;
}

/**---------------------------------------------------------------------------
 * [Description] Read CAN messages.
 * [Arguments]   t_pstCanMsg           : CAN message
 *               t_pu1Buff             : Data buffer
 * [Return]      Std_ReturnType        : E_OK
 *                                     : E_NOT_OK
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static Std_ReturnType ChipCom_ReadCanMsg( CanMsgType* t_pstCanMsg, uint8* t_pu1Buff )
{
	Std_ReturnType t_u1Rtn;

	/* Initialize result */
	t_u1Rtn = (Std_ReturnType)E_NOT_OK;

	/* Read header */
	ChipCom_ConvertArrayTo4byte( &(t_pstCanMsg->u4Id), &t_pu1Buff[CHIPCOM_VLA_MSG_ID_POS] );
	t_pstCanMsg->u1Length = t_pu1Buff[CHIPCOM_VLA_MSG_LEN_POS];

	/* Check receive data length */
	if ( t_pstCanMsg->u1Length <= (uint8)CHIPCOM_CAN_DATA_LEN_MAX )
	{
		/* Read data */
		ChipCom_Memcpy( &(t_pstCanMsg->ptData[0U]), &t_pu1Buff[CHIPCOM_VLA_MSG_HEADER_SIZE], (uint16)t_pstCanMsg->u1Length );

		t_u1Rtn = (Std_ReturnType)E_OK;
	}

	return t_u1Rtn;
}

/**---------------------------------------------------------------------------
 * [Description] Switch packet bank
 * [Arguments]   t_u2PktId             : Packet ID
 * [Return]      uint8                 : Packet bank
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static void ChipCom_SwitchPktBuffBank( uint16 t_u2PktId )
{
	ChipCom_u1PktBuffBank[t_u2PktId] = ChipCom_GetNextPktBuffBank(t_u2PktId);

	return;
}

/**---------------------------------------------------------------------------
 * [Description] Get previous packet bank
 * [Arguments]   t_u2PktId             : Packet ID
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static uint8 ChipCom_GetPrePktBuffBank( uint16 t_u2PktId )
{
	uint8 t_u1PktBank;

	t_u1PktBank = ChipCom_u1PktBuffBank[t_u2PktId];

	if ( t_u1PktBank == (uint8)0U )
	{
		t_u1PktBank = (uint8)ChipCom_cu1PktBuffBankNum - (uint8)1U;
	}
	else
	{
		t_u1PktBank--;
	}

	return t_u1PktBank;
}

/**---------------------------------------------------------------------------
 * [Description] Get next packet bank
 * [Arguments]   t_u2PktId             : Packet ID
 * [Return]      uint8                 : Packet bank
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static uint8 ChipCom_GetNextPktBuffBank( uint16 t_u2PktId )
{
	uint8 t_u1PktBank;

	t_u1PktBank = ChipCom_u1PktBuffBank[t_u2PktId];

	/* Switch bank */
	t_u1PktBank++;
	if ( t_u1PktBank >= ChipCom_cu1PktBuffBankNum )
	{
		t_u1PktBank = (uint8)CHIPCOM_PKT_BANK_INIT;
	}

	return t_u1PktBank;
}

/**---------------------------------------------------------------------------
 * [Description] Set check digit
 * [Arguments]   t_u2PktId             : Packet ID
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static void ChipCom_SetCheckDigit( uint16 t_u2PktId )
{
	uint16 t_u2MsgId;
	uint16 t_u2DataId;
	uint32 t_u4Data;

	/* Increment the Sequence number */
	t_u2MsgId = ChipCom_cu2PktId2ChkDigitMsgId[t_u2PktId];
	t_u2DataId = ChipCom_cu2MsdId2SeqDataId[t_u2MsgId];
	(void)ChipCom_ReceiveSignal( t_u2DataId, (void*)&t_u4Data );
	t_u4Data++;
	(void)ChipCom_SendSignal( t_u2DataId, (const void*)&t_u4Data );

	return;
}

/**---------------------------------------------------------------------------
 * [Description] Set number of transmit messages in variable-length area.
 * [Arguments]   t_u2MsgNum            : Number of messages
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static void ChipCom_SetVlaTxMsgNum( uint16 t_u2MsgNum )
{
	/* Convert variable type, and set number of messages */
	ChipCom_Convert2byteToArray( (uint8*)&ChipCom_pu1TxBuffVla[CHIPCOM_VLA_MSG_NUM_POS], t_u2MsgNum );
	return;
}

/**---------------------------------------------------------------------------
 * [Description] Get number of transmit messages in variable-length area.
 * [Arguments]   None
 * [Return]      None
 * [Notes]       uint16                : Number of messages
 *--------------------------------------------------------------------------*/
static uint16 ChipCom_GetVlaTxMsgNum( void )
{
	uint16 t_u2MsgNum;

	t_u2MsgNum = (uint16)0U;
	/* Get number of messages, and convert variable type */
	ChipCom_ConvertArrayTo2byte( &t_u2MsgNum, (uint8*)&ChipCom_pu1TxBuffVla[CHIPCOM_VLA_MSG_NUM_POS] );
	return t_u2MsgNum;
}

/**---------------------------------------------------------------------------
 * [Description] Set number of receive messages in variable-length area.
 * [Arguments]   t_u2MsgNum            : Number of messages
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static void ChipCom_SetVlaRxMsgNum( uint16 t_u2MsgNum )
{
	/* Convert variable type, and set number of messages */
	ChipCom_Convert2byteToArray( (uint8*)&ChipCom_pu1RxBuffVla[CHIPCOM_VLA_MSG_NUM_POS], t_u2MsgNum );
	return;
}

/**---------------------------------------------------------------------------
 * [Description] Get number of receive messages in variable-length area.
 * [Arguments]   None
 * [Return]      uint16                : Number of messages
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static uint16 ChipCom_GetVlaRxMsgNum( void )
{
	uint16 t_u2MsgNum;

	t_u2MsgNum = (uint16)0U;
	/* Get number of messages, and convert variable type */
	ChipCom_ConvertArrayTo2byte( &t_u2MsgNum, (uint8*)&ChipCom_pu1RxBuffVla[CHIPCOM_VLA_MSG_NUM_POS] );

	return t_u2MsgNum;
}

/**---------------------------------------------------------------------------
 * [Description] Convert size byte to integer.
 * [Arguments]   t_u2Size              : Byte size
 * [Return]      uint16                : Integer size
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static uint16 ChipCom_ConvertSizeByte2Int( uint16 t_u2Size )
{
	uint16 t_u2SizeInt;

	if ( t_u2Size > (uint16)1U )
	{
		t_u2SizeInt = t_u2Size - (uint16)1U;
		t_u2SizeInt = (t_u2SizeInt/(uint16)CHIPCOM_INT_SIZE) + (uint16)1U;
	}
	else
	{
		t_u2SizeInt = (uint16)1U;
	}

	return t_u2SizeInt;
}

/**---------------------------------------------------------------------------
 * [Description] Memory set.
 * [Arguments]   t_pu1Dst              : Destination
 *               t_u1Value             : Value
 *               t_u2Size              : Size
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static void ChipCom_Memset( uint8* t_pu1Dst, uint8 t_u1Value, uint16 t_u2Size )
{
	uint16 t_u2i;

	/* Copy data */
	for ( t_u2i = (uint16)0U; t_u2i < t_u2Size; t_u2i++ )
	{
		t_pu1Dst[t_u2i] = t_u1Value;
	}
	return;
}

/**---------------------------------------------------------------------------
 * [Description] Memory copy.
 * [Arguments]   t_pu1Dst              : Destination
 *               t_pu1Src              : Source
 *               t_u2Size              : Size
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static void ChipCom_Memcpy( uint8* t_pu1Dst, uint8* t_pu1Src, uint16 t_u2Size )
{
	uint16 t_u2i;

	/* Copy data */
	for ( t_u2i = (uint16)0U; t_u2i < t_u2Size; t_u2i++ )
	{
		t_pu1Dst[t_u2i] = t_pu1Src[t_u2i];
	}
	return;
}

/**---------------------------------------------------------------------------
 * [Description] Convert type to array.
 * [Arguments]   t_pu1Dst              : Destination
 *               t_pvdSrc              : Source
 *               t_u2Size              : size
 *               t_u1Type              : Type
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static void ChipCom_ConvertTypeToArray( uint8* t_pu1Dst, void* t_pvdSrc, uint16 t_u2Size, uint8 t_u1Type )
{
	/* Convert variable type */
	switch ( t_u1Type ) {
		case (uint8)CHIPCOM_DATA_TYPE_PRIMITIVE1:
			t_pu1Dst[0U] = *((uint8*)t_pvdSrc);
			break;
		case (uint8)CHIPCOM_DATA_TYPE_PRIMITIVE2:
			ChipCom_Convert2byteToArray( t_pu1Dst, *((uint16*)t_pvdSrc) );
			break;
		case (uint8)CHIPCOM_DATA_TYPE_PRIMITIVE4:
			ChipCom_Convert4byteToArray( t_pu1Dst, *((uint32*)t_pvdSrc) );
			break;
		default: /* CHIPCOM_DATA_TYPE_ARRAY */
			ChipCom_Memcpy( t_pu1Dst, (uint8*)t_pvdSrc, t_u2Size );
			break;
	}
	return;
}

/**---------------------------------------------------------------------------
 * [Description] Convert type from array.
 * [Arguments]   t_pvdDst              : Destination
 *               t_pu1Src              : Source
 *               t_u2Size              : size
 *               t_u1Type              : Type
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static void ChipCom_ConvertTypeFromArray( void* t_pvdDst, uint8* t_pu1Src, uint16 t_u2Size, uint8 t_u1Type )
{
	/* Convert variable type */
	switch ( t_u1Type ) {
		case (uint8)CHIPCOM_DATA_TYPE_PRIMITIVE1:
			*((uint8*)t_pvdDst) = t_pu1Src[0U];
			break;
		case (uint8)CHIPCOM_DATA_TYPE_PRIMITIVE2:
			ChipCom_ConvertArrayTo2byte( (uint16*)t_pvdDst, t_pu1Src );
			break;
		case (uint8)CHIPCOM_DATA_TYPE_PRIMITIVE4:
			ChipCom_ConvertArrayTo4byte( (uint32*)t_pvdDst, t_pu1Src );
			break;
		default: /* CHIPCOM_DATA_TYPE_ARRAY */
			ChipCom_Memcpy( (uint8*)t_pvdDst, t_pu1Src, t_u2Size );
			break;
	}
	return;
}

/**---------------------------------------------------------------------------
 * [Description] Convert unsigned integer to unsigned char array.
 * [Arguments]   t_pu1Dst              : Destination
 *               t_u4Src               : Source
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static void ChipCom_Convert4byteToArray( uint8* t_pu1Dst, uint32 t_u4Src )
{
	/* Convert variable type */
	t_pu1Dst[3U] = (uint8)t_u4Src;
	t_pu1Dst[2U] = (uint8)(t_u4Src >> CHIPCOM_U1_SHIFT_1BYTE);
	t_pu1Dst[1U] = (uint8)(t_u4Src >> CHIPCOM_U1_SHIFT_2BYTE);
	t_pu1Dst[0U] = (uint8)(t_u4Src >> CHIPCOM_U1_SHIFT_3BYTE);
	return;
}

/**---------------------------------------------------------------------------
 * [Description] Convert unsigned char array to unsigned integer.
 * [Arguments]   t_pu4Dst              : Destination
 *               t_pu1Src              : Source
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static void ChipCom_ConvertArrayTo4byte( uint32* t_pu4Dst, uint8* t_pu1Src )
{
	uint32 t_u4work;

	/* Convert variable type */
	t_u4work = ((uint32)t_pu1Src[3U]) & CHIPCOM_U4_MASK_BIT_07_00;
	t_u4work += (((uint32)t_pu1Src[2U]) << CHIPCOM_U1_SHIFT_1BYTE) & CHIPCOM_U4_MASK_BIT_15_08;
	t_u4work += (((uint32)t_pu1Src[1U]) << CHIPCOM_U1_SHIFT_2BYTE) & CHIPCOM_U4_MASK_BIT_23_16;
	t_u4work += (((uint32)t_pu1Src[0U]) << CHIPCOM_U1_SHIFT_3BYTE) & CHIPCOM_U4_MASK_BIT_31_24;
	*t_pu4Dst = t_u4work;
	return;
}

/**---------------------------------------------------------------------------
 * [Description] Convert unsigned short to unsigned char array.
 * [Arguments]   t_pu1Dst              : Destination
 *               t_u2Src               : Source
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static void ChipCom_Convert2byteToArray( uint8* t_pu1Dst, uint16 t_u2Src )
{
	/* Convert variable type */
	t_pu1Dst[1U] = (uint8)t_u2Src;
	t_pu1Dst[0U] = (uint8)(t_u2Src >> CHIPCOM_U1_SHIFT_1BYTE);
	return;
}

/**---------------------------------------------------------------------------
 * [Description] Convert unsigned char array to unsigned short.
 * [Arguments]   t_pu2Dst              : Destination
 *               t_pu1Src              : Source
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static void ChipCom_ConvertArrayTo2byte( uint16* t_pu2Dst, uint8* t_pu1Src )
{
	uint16 t_u2work;

	/* Convert variable type */
	t_u2work = ((uint16)t_pu1Src[1U]) & CHIPCOM_U2_MASK_BIT_07_00;
	t_u2work += (((uint16)t_pu1Src[0U]) << CHIPCOM_U1_SHIFT_1BYTE) & CHIPCOM_U2_MASK_BIT_15_08;
	*t_pu2Dst = t_u2work;
	return;
}

/**---------------------------------------------------------------------------
 * [Description] Get Core ID. (Dummy)
 * [Arguments]   None
 * [Return]      uint8                 : Code ID
 * [Notes]       None
 *--------------------------------------------------------------------------*/
uint8 ChipCom_GetCoreIdDummy( void )
{
	return ChipCom_cu1CoreIdMst;
}

#define CHIPCOM_STOP_SEC_CODE
#include <ChipCom_MemMap.h>

/**** End of File ***********************************************************/
