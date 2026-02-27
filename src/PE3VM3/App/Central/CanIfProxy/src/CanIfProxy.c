/* CanIfProxy_c_v0-0-0														*/
/****************************************************************************/
/* Copyright (C) 2025 Denso Co.,Ltd. All rights reserved.					*/
/****************************************************************************/

/****************************************************************************/
/* Object Name	| CanIfProxy/CODE											*/
/*--------------------------------------------------------------------------*/
/* Notes		|															*/
/****************************************************************************/

/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Include Files															*/
/*--------------------------------------------------------------------------*/
#include "VCan.h"
#include "VCanAck.h"
#include "ChipCom_Cfg.h"
#include "CanIfProxy.h"
#include "CanIfProxy_Lcfg.h"

/*--------------------------------------------------------------------------*/
/* Macros																	*/
/*--------------------------------------------------------------------------*/
/* Bit mask */
#define u4CANIFPROXY_MASK_BIT_07_00				((uint32)0x000000FFU)		/* 4byte 7-0bit mask value */
#define u4CANIFPROXY_MASK_BIT_15_08				((uint32)0x0000FF00U)		/* 4byte 15-8bit mask value */
#define u4CANIFPROXY_MASK_BIT_23_16				((uint32)0x00FF0000U)		/* 4byte 23-16bit mask value */
#define u4CANIFPROXY_MASK_BIT_31_24				((uint32)0xFF000000U)		/* 4byte 31-24bit mask value */
/* byte shift */
#define u1CANIFPROXY_SHIFT_1BYTE				((uint8)8U)					/* 1byte shift value */
#define u1CANIFPROXY_SHIFT_2BYTE				((uint8)16U)				/* 2byte shift value */
#define u1CANIFPROXY_SHIFT_3BYTE				((uint8)24U)				/* 4byte shift value */

/* Max length of CAN data */
#define CANIFPROXY_CAN_DATA_LEN_MAX				(32U)
/* Max length of CAN data */
#define CANIFPROXY_CAN_FD_DATA_LEN_MAX			(32U)

/* N_PCI length */
#define CANIFPROXY_NPCI_LEN_SF					(0x01U)
#define CANIFPROXY_NPCI_LEN_SF_LD				(0x02U)
#define CANIFPROXY_NPCI_LEN_FF					(0x02U)
#define CANIFPROXY_NPCI_LEN_FF_LD				(0x06U)
#define CANIFPROXY_NPCI_LEN_CF					(0x01U)
#define CANIFPROXY_NPCI_LEN_FC					(0x03U)

/* N_PDUType */
#define CANIFPROXY_NPDUTYPE_SF					(0x00) /* Single Frame */
#define CANIFPROXY_NPDUTYPE_FF					(0x10) /* First Frame */
#define CANIFPROXY_NPDUTYPE_CF					(0x20) /* Consecutive Frame */
#define CANIFPROXY_NPDUTYPE_FC					(0x30) /* Flow Control */
#define CANIFPROXY_NPDUTYPE_UNDEF				(0xF0) /* Undefined */

/* Flow status */
#define CANIFPROXY_FS_CTS						(0x00U)
#define CANIFPROXY_FS_WT						(0x01U)
#define CANIFPROXY_FS_OVFLW						(0x02U)

/* Upper limit of flow status wait */
#define CANIFPROXY_FS_WT_LIMIT					(0x03U)

/* FF_DL large data Judgment value */
#define CANIFPROXY_FFDL_LD_JUDGE_VALUE			(0U)
/* FF_DL short data maximum value */
#define CANIFPROXY_FFDL_SD_MAX					(4095U)

/* STmin MIN (ISO 15765-2) */
#define CANIFPROXY_STMIN_MIN_MS                 (0x00U)
/* STmin MAX (ISO 15765-2) */
#define CANIFPROXY_STMIN_MAX_MS                 (0x7FU)
/* STmin MIN (ISO 15765-2) */
#define CANIFPROXY_STMIN_MIN_US                 (0xF1U)
/* STmin MAX (ISO 15765-2) */
#define CANIFPROXY_STMIN_MAX_US                 (0xF9U)
/* STmin margin */
#define CANIFPROXY_STMIN_MARGIN                 (0x01U)

/* Data field offset */
#define CANIFPROXY_DF_OFFS_NPDUTYPE				(0x00U)
#define CANIFPROXY_DF_OFFS_FS					(0x00U)
#define CANIFPROXY_DF_OFFS_BS					(0x01U)
#define CANIFPROXY_DF_OFFS_STMIN				(0x02U)
#define CANIFPROXY_DF_OFFS_FFDL_BYTE1			(0x00U)
#define CANIFPROXY_DF_OFFS_FFDL_BYTE0			(0x01U)
#define CANIFPROXY_DF_OFFS_FFDL_LD_BYTE3		(0x02U)
#define CANIFPROXY_DF_OFFS_FFDL_LD_BYTE2		(0x03U)
#define CANIFPROXY_DF_OFFS_FFDL_LD_BYTE1		(0x04U)
#define CANIFPROXY_DF_OFFS_FFDL_LD_BYTE0		(0x05U)

/* Data field mask */
#define CANIFPROXY_DF_MASK_NPDUTYPE				(0xF0U)
#define CANIFPROXY_DF_MASK_FS					(0x0FU)
#define CANIFPROXY_DF_MASK_FFDL_BYTE1			(0x00000F00U)
#define CANIFPROXY_DF_MASK_FFDL_BYTE0			(0x000000FFU)
		
/* Request controll status */
#define CANIFPROXY_REQ_CTRL_STS_IDLE			(0U)
#define CANIFPROXY_REQ_CTRL_STS_RX_FC			(3U)
#define CANIFPROXY_REQ_CTRL_STS_TX_CF			(4U)

/* Return value */
#define u1CANIFPROXY_E_OK						((uint8)1U)
#define u1CANIFPROXY_E_DONE						((uint8)2U)
#define u1CANIFPROXY_E_WAIT						((uint8)3U)
#define u1CANIFPROXY_E_NOT_OK					((uint8)0U)

/*--------------------------------------------------------------------------*/
/* Types																	*/
/*--------------------------------------------------------------------------*/
typedef struct {
	uint16 u2Head;					/* Buffer Head */
	uint16 u2Tail;					/* Buffer Tail */
} CanIfProxy_SfStatusType;

typedef struct {
	uint32 u4FfDl;					/* FF_DL (First Frame data length) */
	uint32 u4TxNDataLen;			/* Length of transmitted N data */
	uint16 u2Head;					/* Buffer Head */
	uint16 u2Tail;					/* Buffer Tail */
	uint16 u2Timeout;				/* Timeout judgement time */
	uint16 u2Timer;					/* Timer for timeout and transmit cycle */
	uint8 u1Fs;						/* FC FS (Flow status) */
	uint8 u1Bs;						/* FC BS (Block Size) */
	uint8 u1STMin;					/* FC STmin (Separation Time Minimum) */
	uint8 u1CfPeriodPwrOn;			/* CF Period in Powr-On */
	uint8 u1CfPeriodPwrOff;			/* CF Period in Powr-Off */
	uint8 u1CfTxNumPwrOn;			/* Number of CF transmit per period in Power-On[time] */
	uint8 u1CfTxNumPwrOff;			/* Number of CF transmit per period in Power-Off[time] */
	uint8 u1IsRcvFf;				/* Is FF received */
	uint8 u1IsRcvFc;				/* Is FC received */
	uint8 u1TxBlock;				/* Number of transmitted block */
	uint8 u1WtCnt;					/* FC FS wait counter */
	uint8 u1FrameCntInTx;			/* Counter of frame in transit */
} CanIfProxy_MfStatusType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes														*/
/*--------------------------------------------------------------------------*/
static void CanIfProxy_InitStatus( void );
static void CanIfProxy_InitSfRequest( void );
static void CanIfProxy_InitMfRequest( void );
static void CanIfProxy_InitTxMode( void );
static void CanIfProxy_ReceiveRequest( const CanMsgType* t_pstMsg );
static void CanIfProxy_SetSfToReqBuff( const CanMsgType* t_pstMsg );
static void CanIfProxy_SetMfToReqBuff( const CanMsgType* t_pstMsg );
static void CanIfProxy_ReceiveResponse( const CanMsgType* t_pstMsg );
static void CanIfProxy_DecrementFrameCounterInTx( Can_IdType t_u4CanId );
static void CanIfProxy_TransmitRequest( void );
static uint8 CanIfProxy_TransmitSF( void );
static uint8 CanIfProxy_TransmitFF( void );
static uint8 CanIfProxy_TransmitCF( void );
static uint8 CanIfProxy_ReceiveFC( void );
static void CanIfProxy_TransmitMfAbort( void );
static void CanIfProxy_ReadFfNpci( uint8* t_pu1Data );
static void CanIfProxy_ReadFcNpci( uint8* t_pu1Data );
static uint8 CanIfProxy_GetNPduType( const CanMsgType* t_pstMsg );
static uint8 CanIfProxy_GetNDataLen( const CanMsgType* t_pstMsg );
static void CanIfProxy_CalcCfThroughput( void );
static uint8 CanIfProxy_IsResFrame( uint32 t_u4CanId );
static uint8 CanIfProxy_IsPowerOn( void );
static uint8 CanIfProxy_IsEmptyTxSfBuff( void );
static uint8 CanIfProxy_IsFullTxSfBuff( void );
static void CanIfProxy_AddIdxTxSfBuff( uint16* t_pu2Idx );
static void CanIfProxy_Memcpy( uint8* t_pu1Dst, uint8* t_pu1Src, uint16 t_u2Size );
static void CanIfProxy_ReceiveChipComData( void );
static void CanIfProxy_ReceiveObcTxMode( void );
static void CanIfProxy_SetObcTxMode( uint8 t_u1RxData );
static void CanIfProxy_TransmitTxModeNotification( void );
static void CanIfProxy_AckTransmit( Can_IdType t_u4CanId );

/*--------------------------------------------------------------------------*/
/* Data 																	*/
/*--------------------------------------------------------------------------*/
#define CANIFPROXY_START_SEC_VAR_CLEARED_32
#include <CanIfProxy_MemMap.h>

/* Request Controll Status */
static uint8 CanIfProxy_u1ReqCtrlStatus;

/* Buffer Status */
static CanIfProxy_SfStatusType CanIfProxy_stSfReqStatus;
static CanIfProxy_MfStatusType CanIfProxy_stMfReqStatus;

/* OBC Transmit Mode */
static uint8 CanIfProxy_u1ObcTxMode;

#define CANIFPROXY_STOP_SEC_VAR_CLEARED_32
#include <CanIfProxy_MemMap.h>

#define CANIFPROXY_START_SEC_VAR_POWER_ON_CLEARED_32
#include <CanIfProxy_MemMap.h>
#define CANIFPROXY_STOP_SEC_VAR_POWER_ON_CLEARED_32
#include <CanIfProxy_MemMap.h>

#define CANIFPROXY_START_SEC_VAR_INIT_32
#include <CanIfProxy_MemMap.h>
#define CANIFPROXY_STOP_SEC_VAR_INIT_32
#include <CanIfProxy_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants																*/
/*--------------------------------------------------------------------------*/
#define CANIFPROXY_START_SEC_CONST
#include <CanIfProxy_MemMap.h>
#define CANIFPROXY_STOP_SEC_CONST
#include <CanIfProxy_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Functions																*/
/*--------------------------------------------------------------------------*/
#define CANIFPROXY_START_SEC_CODE
#include <CanIfProxy_MemMap.h>
/****************************************************************************/
/* Scheduled Functions														*/
/****************************************************************************/
/*****************************************************************************
  Function		: Initialize this module.
  Description	: Initialize this module.
  param[in/out] : None
  return		: None
  Note			: None
*****************************************************************************/
void CanIfProxy_Init( void )
{
	/* Initialize status */
	CanIfProxy_InitStatus();

	/* Initialize request */
	CanIfProxy_InitSfRequest();
	CanIfProxy_InitMfRequest();
	
	/* Initialize tx mode */
	CanIfProxy_InitTxMode();

	return;
}

/*****************************************************************************
  Function		: Performs the processing of this module.
  Description	: Performs the processing of this module.
  param[in/out] : None
  return		: None
  Note			: None
*****************************************************************************/
void CanIfProxy_MainFunction( void )
{
	/* Receive ChipCom Data */
	CanIfProxy_ReceiveChipComData();
	
	/* Transmit request */
	CanIfProxy_TransmitRequest();
	
	return;
}

/****************************************************************************/
/* Service API																*/
/****************************************************************************/


/****************************************************************************/
/* Callback Functions and Notifications 									*/
/****************************************************************************/
/*****************************************************************************
  Function		: Receive CAN messages.
  Description	: Receives CAN messages and pushes them to the transmit buffer.
  param[in/out] : CAN message
  return		: None
  Note			: None
*****************************************************************************/
void CanIfProxy_RxIndication( const CanMsgType* t_pstMsg )
{
	/* Check argument */
	if (   ( t_pstMsg != NULL_PTR )
		&& ( t_pstMsg->ptData != NULL_PTR )
		&& ( t_pstMsg->u1Length <= (uint8)CANIFPROXY_CAN_FD_DATA_LEN_MAX ) )
		/* todo: Check CAN ID */
	{
		CanIfProxy_ReceiveRequest( t_pstMsg );
	}

	return;
}

/*****************************************************************************
  Function		: Receive CAN messages.
  Description	: Receives CAN messages and transmit to the ChipCom.
  param[in/out] : 
  return		: None
  Note			: None
*****************************************************************************/
uint8 VCan_URxIndication( uint8 t_u1Controller, uint8 t_u1MsgBuffer, const CanMsgType* t_pstMsg )
{
	uint8 t_u1Ret;
	uint8 t_u1IsResFrame;

	t_u1Ret = (uint8)CAN_PROC_OK;

	/* Check argument */
	if (   ( t_pstMsg != NULL_PTR )
		&& ( t_pstMsg->ptData != NULL_PTR )
		&& ( t_pstMsg->u1Length <= (uint8)CANIFPROXY_CAN_FD_DATA_LEN_MAX ) )
		/* todo: Check CAN ID */
	{

		t_u1IsResFrame = CanIfProxy_IsResFrame( t_pstMsg->u4Id );

		if ( t_u1IsResFrame == (uint8)TRUE )
		{
			CanIfProxy_ReceiveResponse( t_pstMsg );
			t_u1Ret = (uint8)CAN_PROC_NG;
		}
	}

	return t_u1Ret;
}

/*****************************************************************************
  Function		: Receive CAN Ack.
  Description	: Receives CAN Ack and .
  param[in/out] : 
  return		: None
  Note			: None
*****************************************************************************/
void CanIfProxy_AckIndication( Can_IdType t_u4CanId )
{
	/* Transmit Ack */
	CanIfProxy_AckTransmit( t_u4CanId );
	
	/* Decrement the counter of frame in transit */
	CanIfProxy_DecrementFrameCounterInTx( t_u4CanId );
	
}

/****************************************************************************/
/* Internal Functions														*/
/****************************************************************************/
/*****************************************************************************
  Function		: Initialize Message Status
  Description	: Initialize Message Status
  param[in/out] : None
  return		: None
  Note			: None
*****************************************************************************/
static void CanIfProxy_InitStatus( void )
{
	/* Initialize status */
	CanIfProxy_u1ReqCtrlStatus = (uint8)CANIFPROXY_REQ_CTRL_STS_IDLE;

	return;
}

/*****************************************************************************
  Function		: Set message buffer
  Description	: Set message buffer
  param[in/out] : None
  return		: None
  Note			: None
*****************************************************************************/
static void CanIfProxy_InitSfRequest( void )
{
	CanIfProxy_stSfReqStatus.u2Head = (uint16)0U;
	CanIfProxy_stSfReqStatus.u2Tail = (uint16)0U;
	return;
}

/*****************************************************************************
  Function		: Set message buffer
  Description	: Set message buffer
  param[in/out] : None
  return		: None
  Note			: None
*****************************************************************************/
static void CanIfProxy_InitMfRequest( void )
{
	CanIfProxy_stMfReqStatus.u2Head = (uint16)0U;
	CanIfProxy_stMfReqStatus.u2Tail = (uint16)0U;
	CanIfProxy_stMfReqStatus.u2Timer = (uint16)0U;
	CanIfProxy_stMfReqStatus.u4TxNDataLen = (uint32)0U;
	CanIfProxy_stMfReqStatus.u1TxBlock = (uint8)0U;
	CanIfProxy_stMfReqStatus.u1IsRcvFf = (uint8)0U;
	CanIfProxy_stMfReqStatus.u1IsRcvFc = (uint8)0U;
	CanIfProxy_stMfReqStatus.u1WtCnt = (uint8)0U;
	CanIfProxy_stMfReqStatus.u1FrameCntInTx = (uint8)0U;

//	CanIfProxy_stMfReqStatus.u4FfDl = (uint32)0U;
//	CanIfProxy_stMfReqStatus.u1Fs = (uint8)0U;
//	CanIfProxy_stMfReqStatus.u1Bs = (uint8)0U;
//	CanIfProxy_stMfReqStatus.u1STMin = (uint8)0U;
//	CanIfProxy_stMfReqStatus.u1CfPeriodPwrOn = (uint8)0U;
//	CanIfProxy_stMfReqStatus.u1CfPeriodPwrOff = (uint8)0U;
//	CanIfProxy_stMfReqStatus.u1CfTxNumPwrOn = (uint8)0U;
//	CanIfProxy_stMfReqStatus.u1CfTxNumPwrOff = (uint8)0U;
//	CanIfProxy_stMfReqStatus.u2Timeout = (uint16)0U;

	return;
}

/*****************************************************************************
  Function		: Set message buffer
  Description	: Set message buffer
  param[in/out] : None
  return		: None
  Note			: None
*****************************************************************************/
static void CanIfProxy_InitTxMode( void )
{
	/* Initialize Tx Mode */
	CanIfProxy_u1ObcTxMode = (uint8)STD_OFF;
	return;
}
/*****************************************************************************
  Function		: Set message buffer
  Description	: Set message buffer
  param[in/out] : None
  return		: None
  Note			: None
*****************************************************************************/
static void CanIfProxy_ReceiveRequest( const CanMsgType* t_pstMsg )
{
	uint8 t_u1NPduType;

	/* Get N_PDUtype from CAN message */
	t_u1NPduType = CanIfProxy_GetNPduType( t_pstMsg );

	if ( t_u1NPduType != (uint8)CANIFPROXY_NPDUTYPE_UNDEF )
	{
		if ( t_u1NPduType == (uint8)CANIFPROXY_NPDUTYPE_SF )
		{
			/* Set SF request buffer */
			CanIfProxy_SetSfToReqBuff( t_pstMsg );
		}
		else
		{
			if( t_u1NPduType == (uint8)CANIFPROXY_NPDUTYPE_FF )
			{
				/* Initialize request */
				CanIfProxy_InitMfRequest();

				/* Memory received FF */
				CanIfProxy_stMfReqStatus.u1IsRcvFf = (uint8)TRUE;

				/* Read N_PCI */
				CanIfProxy_ReadFfNpci( t_pstMsg->ptData );
			}

			/* Set MF request buffer */
			CanIfProxy_SetMfToReqBuff( t_pstMsg );
		}
	}

	return;
}

/*****************************************************************************
  Function		: Set Single-CAN message buffer
  Description	: Set Single-CAN message buffer
  param[in/out] : None
  return		: None
  Note			: None
*****************************************************************************/
static void CanIfProxy_SetSfToReqBuff( const CanMsgType* t_pstMsg )
{
	uint8 t_u1IsFull;
	uint16 t_u2Tail;

	/* todo: Suspend Interrupts */

	t_u1IsFull = CanIfProxy_IsFullTxSfBuff();
	if ( t_u1IsFull == (uint8)FALSE )
	{
		t_u2Tail = CanIfProxy_stSfReqStatus.u2Tail;
		CanIfProxy_u4SfReqBuffCanId[t_u2Tail] = t_pstMsg->u4Id;
		CanIfProxy_u1SfReqBuffDataLength[t_u2Tail] = t_pstMsg->u1Length;
		CanIfProxy_Memcpy( &CanIfProxy_u1SfReqBuffData[t_u2Tail][0U], t_pstMsg->ptData, t_pstMsg->u1Length );
		CanIfProxy_AddIdxTxSfBuff( &t_u2Tail );
		CanIfProxy_stSfReqStatus.u2Tail = t_u2Tail;
	}

	/* todo: Resume Interrupts */

	return;
}

/*****************************************************************************
  Function		: Set Multi-CAN message buffer
  Description	: Set Multi-CAN message buffer
  param[in/out] : None
  return		: None
  Note			: None
*****************************************************************************/
static void CanIfProxy_SetMfToReqBuff( const CanMsgType* t_pstMsg )
{
	uint16 t_u2Tail;
	uint16 t_u2TailNext;

	/* todo: Suspend Interrupts */

	t_u2Tail = CanIfProxy_stMfReqStatus.u2Tail;
	t_u2TailNext = t_u2Tail + (uint16)1U;

	if ( t_u2TailNext < CanIfProxy_cu2MfReqFrameNum )
	/* todo: Check Can ID */
	{
		CanIfProxy_u4MfReqBuffCanId = t_pstMsg->u4Id;
		CanIfProxy_u1MfReqBuffDataLength[t_u2Tail] = t_pstMsg->u1Length;
		CanIfProxy_Memcpy( &CanIfProxy_u1MfReqBuffData[t_u2Tail][0U], t_pstMsg->ptData, t_pstMsg->u1Length );
		CanIfProxy_stMfReqStatus.u2Tail = t_u2TailNext;
	}

	/* todo: Resume Interrupts */

	return;
}

/*****************************************************************************
  Function		: 
  Description	: 
  param[in/out] : 
  return		: None
  Note			: None
*****************************************************************************/
static void CanIfProxy_ReceiveResponse( const CanMsgType* t_pstMsg )
{
	uint8 t_u1NPduType;

	/* Get N_PDUtype from CAN message */
	t_u1NPduType = CanIfProxy_GetNPduType( t_pstMsg );

	if ( t_u1NPduType != (uint8)CANIFPROXY_NPDUTYPE_UNDEF )
	{
		if ( t_u1NPduType == (uint8)CANIFPROXY_NPDUTYPE_FC )
		{
			/* Read N_PCI */
			CanIfProxy_ReadFcNpci( t_pstMsg->ptData );

			/* Memory received FF */
			CanIfProxy_stMfReqStatus.u1IsRcvFc = (uint8)TRUE;

			/* todo: If FS is CTS, tampering with BS and STmin */
		}

		/* Transmit to ChipCom */
		(void)ChipCom_CanTransmit( t_pstMsg );
	}

	return;
}

/*****************************************************************************
  Function		: 
  Description	: 
  param[in/out] : None
  return		: None
  Note			: None
*****************************************************************************/
static void CanIfProxy_DecrementFrameCounterInTx( Can_IdType t_u4CanId )
{
	uint8 t_u1FrameCntInTx;

	if ( CanIfProxy_u4MfReqBuffCanId == t_u4CanId )
	{
		/* Decrement the counter of frame in transit */
		t_u1FrameCntInTx = CanIfProxy_stMfReqStatus.u1FrameCntInTx;
		if ( t_u1FrameCntInTx > (uint8)0U )
		{
			CanIfProxy_stMfReqStatus.u1FrameCntInTx--;
		}
	}

	return;
}

/*****************************************************************************
  Function		: Transmit CAN message
  Description	: Transmit CAN message to Virtual CAN
  param[in/out] : None
  return		: None
  Note			: None
*****************************************************************************/
static void CanIfProxy_TransmitRequest( void )
{
	Std_ReturnType t_u1Ret;
	uint8 t_u1ReqCtrlStatus;

	/* Get message status */
	t_u1ReqCtrlStatus = CanIfProxy_u1ReqCtrlStatus;

	if ( ( t_u1ReqCtrlStatus != (uint8)CANIFPROXY_REQ_CTRL_STS_IDLE )
		&& ( CanIfProxy_stMfReqStatus.u1IsRcvFf == (uint8)TRUE ) )
	{
		t_u1ReqCtrlStatus = (uint8)CANIFPROXY_REQ_CTRL_STS_IDLE;
	}

	/* Status is Idle */
	if ( t_u1ReqCtrlStatus == (uint8)CANIFPROXY_REQ_CTRL_STS_IDLE )
	{
		/* Detect receive FF */
		if ( CanIfProxy_stMfReqStatus.u1IsRcvFf == (uint8)TRUE )
		{
			/* Clear received FF */
			CanIfProxy_stMfReqStatus.u1IsRcvFf = (uint8)FALSE;

			/* Transmit FF */
			t_u1Ret = CanIfProxy_TransmitFF();

			if ( t_u1Ret == (Std_ReturnType)E_OK )
			{
				/* Update status */
				t_u1ReqCtrlStatus = (uint8)CANIFPROXY_REQ_CTRL_STS_RX_FC;
			}
			else
			{
				/* Abort */
				CanIfProxy_TransmitMfAbort();
				/* Update status */
				/* t_u1ReqCtrlStatus = (uint8)CANIFPROXY_REQ_CTRL_STS_IDLE; */
			}
		}
		else
		{
			/* Transmit SF */
			(void)CanIfProxy_TransmitSF();

			/* Update status */
			/* t_u1ReqCtrlStatus = (uint8)CANIFPROXY_REQ_CTRL_STS_IDLE; */
		}
	}

	/* Status is Receive FC */
	if ( t_u1ReqCtrlStatus == (uint8)CANIFPROXY_REQ_CTRL_STS_RX_FC )
	{
		/* Judge timeout */
		if ( CanIfProxy_stMfReqStatus.u2Timer >= CanIfProxy_stMfReqStatus.u2Timeout )
		{
			/* Abort */
			CanIfProxy_TransmitMfAbort();
			/* Update status */
			t_u1ReqCtrlStatus = (uint8)CANIFPROXY_REQ_CTRL_STS_IDLE;
		}
		else
		{
			/* Detect receive FC */
			if ( CanIfProxy_stMfReqStatus.u1IsRcvFc == (uint8)TRUE )
			{
				/* Clear received FC */
				CanIfProxy_stMfReqStatus.u1IsRcvFc = (uint8)FALSE;

				/* Received FC */
				t_u1Ret = CanIfProxy_ReceiveFC();

				if ( t_u1Ret == u1CANIFPROXY_E_OK )
				{
					/* Set timer */
					CanIfProxy_CalcCfThroughput();
					CanIfProxy_stMfReqStatus.u2Timer = (uint8)0;

					/* Update status */
					t_u1ReqCtrlStatus = (uint8)CANIFPROXY_REQ_CTRL_STS_TX_CF;
				}
				else if ( t_u1Ret == u1CANIFPROXY_E_NOT_OK )
				{
					/* Abort */
					CanIfProxy_TransmitMfAbort();
					/* Update status */
					t_u1ReqCtrlStatus = (uint8)CANIFPROXY_REQ_CTRL_STS_IDLE;
				}
			}
		}
	}

	/* Status is transmit CF */
	if ( t_u1ReqCtrlStatus == (uint8)CANIFPROXY_REQ_CTRL_STS_TX_CF )
	{
		/* Transmit CF */
		t_u1Ret = CanIfProxy_TransmitCF();

		if ( t_u1Ret == u1CANIFPROXY_E_DONE )
		{
			/* Initialize request */
			CanIfProxy_InitMfRequest();
			/* Update status */
			t_u1ReqCtrlStatus = (uint8)CANIFPROXY_REQ_CTRL_STS_IDLE;
		}
		else if ( t_u1Ret == u1CANIFPROXY_E_WAIT )
		{
			/* Set Timer */
			CanIfProxy_stMfReqStatus.u2Timeout = (uint16)CanIfProxy_cu2NAs + (uint16)CanIfProxy_cu2NBs;
			CanIfProxy_stMfReqStatus.u2Timer = (uint8)0;

			/* Update status */
			t_u1ReqCtrlStatus = (uint8)CANIFPROXY_REQ_CTRL_STS_RX_FC;
		}
		else if ( t_u1Ret == u1CANIFPROXY_E_NOT_OK )
		{
			/* Abort */
			CanIfProxy_TransmitMfAbort();
			/* Update status */
			t_u1ReqCtrlStatus = (uint8)CANIFPROXY_REQ_CTRL_STS_IDLE;
		}
		else
		{
			/* nop */
		}
	}

	/* Set status */
	CanIfProxy_u1ReqCtrlStatus = t_u1ReqCtrlStatus;

	return;
}

/*****************************************************************************
  Function		: 
  Description	: 
  param[in/out] : 
  return		: None
  Note			: None
*****************************************************************************/
static uint8 CanIfProxy_TransmitSF( void )
{
	uint8 t_u1Ret;
	uint8 t_u1VcanRet;
	uint8 t_u1IsEmpty;
	uint16 t_u2Head;
	CanMsgType t_stMsg;

	t_u1Ret = u1CANIFPROXY_E_OK;

	t_u1IsEmpty = CanIfProxy_IsEmptyTxSfBuff();
	if ( t_u1IsEmpty == (uint8)FALSE )
	{
		/* Get head */
		t_u2Head = CanIfProxy_stSfReqStatus.u2Head;

		/* Make message */
		t_stMsg.u4Id = CanIfProxy_u4SfReqBuffCanId[t_u2Head];
		t_stMsg.u1Length = CanIfProxy_u1SfReqBuffDataLength[t_u2Head];
		t_stMsg.ptData = &CanIfProxy_u1SfReqBuffData[t_u2Head][0U];

		/* Transmit to Virtual CAN */
		t_u1VcanRet = VCan_TxReq( CanIfProxy_cu1VcanCtrl, CanIfProxy_cu1VcanMbox, &t_stMsg );

		if ( t_u1VcanRet != (uint8)CAN_PROC_OK )
		{
			t_u1Ret = u1CANIFPROXY_E_NOT_OK;
		}

		/* Update head */
		CanIfProxy_AddIdxTxSfBuff( &t_u2Head );
		CanIfProxy_stSfReqStatus.u2Head = t_u2Head;
	}

	return t_u1Ret;
}

/*****************************************************************************
  Function		: 
  Description	: 
  param[in/out] : 
  return		: None
  Note			: none
*****************************************************************************/
static uint8 CanIfProxy_TransmitFF( void )
{
	uint8 t_u1Ret;
	uint8 t_u1VcanRet;
	uint16 t_u2Head;
	CanMsgType t_stMsg;

	t_u1Ret = u1CANIFPROXY_E_OK;

	/* Get head */
	t_u2Head = CanIfProxy_stMfReqStatus.u2Head;

	/* Make message */
	t_stMsg.u4Id = CanIfProxy_u4MfReqBuffCanId;
	t_stMsg.u1Length = CanIfProxy_u1MfReqBuffDataLength[t_u2Head];
	t_stMsg.ptData = &CanIfProxy_u1MfReqBuffData[t_u2Head][0U];

	/* Transmit to Virtual CAN */
	t_u1VcanRet = VCan_TxReq( CanIfProxy_cu1VcanCtrl, CanIfProxy_cu1VcanMbox, &t_stMsg );

	if ( t_u1VcanRet == (uint8)CAN_PROC_OK )
	{
		/* Update N data len */
		CanIfProxy_stMfReqStatus.u4TxNDataLen += (uint32)CanIfProxy_GetNDataLen( &t_stMsg );

		/* Update head */
		t_u2Head++;
		CanIfProxy_stMfReqStatus.u2Head = t_u2Head;

		/* Set Timer */
		CanIfProxy_stMfReqStatus.u2Timeout = (uint16)CanIfProxy_cu2NAs + (uint16)CanIfProxy_cu2NBs;
		CanIfProxy_stMfReqStatus.u2Timer = (uint8)0;
	}
	else
	{
		t_u1Ret = u1CANIFPROXY_E_NOT_OK;
	}

	return t_u1Ret;
}

/*****************************************************************************
  Function		: 
  Description	: 
  param[in/out] : 
  return		: None
  Note			: none
*****************************************************************************/
static uint8 CanIfProxy_TransmitCF( void )
{
	uint8 t_u1Ret;
	uint8 t_u1IsPowerOn;
	uint8 t_u1CfPeriod;
	uint8 t_u1CfTxNum;
	uint8 t_u1TxBlock;
	uint16 t_u2Timer;
	uint16 t_u2Head;
	uint16 t_u2Tail;
	uint32 t_u4TxNDataLen;
	uint8 t_u1TxCnt;
	uint8 t_u1FrameCntInTx;
	uint8 t_u1VcanRet;
	CanMsgType t_stMsg;
	uint32 t_u4FfDl;

	t_u1Ret = u1CANIFPROXY_E_OK;

	/* Get Cf period and Nunber of transmit */
	t_u1IsPowerOn = CanIfProxy_IsPowerOn();

	if ( t_u1IsPowerOn == (uint8)TRUE )
	{
		t_u1CfPeriod = CanIfProxy_stMfReqStatus.u1CfPeriodPwrOn;
		t_u1CfTxNum = CanIfProxy_stMfReqStatus.u1CfTxNumPwrOn;
	}
	else
	{
		t_u1CfPeriod = CanIfProxy_stMfReqStatus.u1CfPeriodPwrOff;
		t_u1CfTxNum = CanIfProxy_stMfReqStatus.u1CfTxNumPwrOff;
	}

	/* Count up timer */
	t_u2Timer = CanIfProxy_stMfReqStatus.u2Timer;
	t_u2Timer++;

	if ( t_u2Timer >= t_u1CfPeriod )
	{
		/* Get head */
		t_u2Head = CanIfProxy_stMfReqStatus.u2Head;
		/* Get tail */
		t_u2Tail  = CanIfProxy_stMfReqStatus.u2Tail;
		/* Get transmitted block */
		t_u1TxBlock = CanIfProxy_stMfReqStatus.u1TxBlock;
		/* Get N data length */
		t_u4TxNDataLen = CanIfProxy_stMfReqStatus.u4TxNDataLen;
		/* Get the counter of frame in transit */
		t_u1FrameCntInTx = CanIfProxy_stMfReqStatus.u1FrameCntInTx;
		
		t_u4FfDl = CanIfProxy_stMfReqStatus.u4FfDl;

		for ( t_u1TxCnt = (uint8)0U; t_u1TxCnt < t_u1CfTxNum; t_u1TxCnt++ )
		{
			if ( ( t_u2Head < t_u2Tail )
				&& ( t_u1FrameCntInTx <= CanIfProxy_cu1TxLimit ) )
			{
				/* Make message */
				t_stMsg.u4Id = CanIfProxy_u4MfReqBuffCanId;
				t_stMsg.u1Length = CanIfProxy_u1MfReqBuffDataLength[t_u2Head];
				t_stMsg.ptData = &CanIfProxy_u1MfReqBuffData[t_u2Head][0U];

				/* Transmit to Virtual CAN */
				t_u1VcanRet = VCan_TxReq( CanIfProxy_cu1VcanCtrl, CanIfProxy_cu1VcanMbox, &t_stMsg );

				if ( t_u1VcanRet == (uint8)CAN_PROC_OK )
				{
					/* Increment head */
					t_u2Head++;

					/* Increment the counter of frame in transit */
					t_u1FrameCntInTx++;

					/* Update N data len */
					t_u4TxNDataLen += (uint32)CanIfProxy_GetNDataLen( &t_stMsg );

					/* Count up block */
					t_u1TxBlock++;

					/* Judge done */
					if ( t_u4TxNDataLen == t_u4FfDl )
					{
						t_u1Ret = u1CANIFPROXY_E_DONE;
						break;
					}

					/* Judge wait */
					if ( t_u1TxBlock == CanIfProxy_stMfReqStatus.u1Bs )
					{
						t_u1Ret = u1CANIFPROXY_E_WAIT;
						break;
					}
				}
				else
				{
					t_u1Ret = u1CANIFPROXY_E_NOT_OK;
					break;
				}
			}
			else
			{
				break;
			}
		}

		/* Clear t_u2Timer */
		t_u2Timer = (uint8)0U;

		/* Get the counter of frame in transit */
		CanIfProxy_stMfReqStatus.u1FrameCntInTx = t_u1FrameCntInTx;
		/* Update N data length */
		CanIfProxy_stMfReqStatus.u4TxNDataLen = t_u4TxNDataLen;
		/* Update transmitted block */
		CanIfProxy_stMfReqStatus.u1TxBlock = t_u1TxBlock;

		/* Update head */
		CanIfProxy_stMfReqStatus.u2Head = t_u2Head;
	}

	/* Update timer */
	CanIfProxy_stMfReqStatus.u2Timer = t_u2Timer;

	return t_u1Ret;
}

/*****************************************************************************
  Function		: 
  Description	: 
  param[in/out] : 
  return		: None
  Note			: None
*****************************************************************************/
static uint8 CanIfProxy_ReceiveFC( void )
{
	uint8 t_u1Ret;
	uint8 t_u1Fs;
	uint8 t_u1WtCnt;

	t_u1Ret = u1CANIFPROXY_E_OK;

	t_u1Fs = CanIfProxy_stMfReqStatus.u1Fs;
	t_u1WtCnt = CanIfProxy_stMfReqStatus.u1WtCnt;

	if ( t_u1Fs == (uint8)CANIFPROXY_FS_WT )
	{
		t_u1WtCnt++;
		if ( t_u1WtCnt < (uint8)CANIFPROXY_FS_WT_LIMIT )
		{
			/* Set Timer */
			CanIfProxy_stMfReqStatus.u2Timeout = (uint16)CanIfProxy_cu2NBs;
			CanIfProxy_stMfReqStatus.u2Timer = (uint8)0;
			t_u1Ret = u1CANIFPROXY_E_WAIT;
		}
		else
		{
			t_u1Ret = u1CANIFPROXY_E_NOT_OK;
		}
	}
	else if ( t_u1Fs == (uint8)CANIFPROXY_FS_OVFLW )
	{
		t_u1Ret = u1CANIFPROXY_E_NOT_OK;
	}
	else
	{
		/* nop */
	}

	return t_u1Ret;
}

/*****************************************************************************
  Function		: 
  Description	: 
  param[in/out] : 
  return		: None
  Note			: None
*****************************************************************************/
static void CanIfProxy_TransmitMfAbort( void )
{
	/* Initialize request */
	CanIfProxy_InitMfRequest();
}

/*****************************************************************************
  Function		: 
  Description	: 
  param[in/out] : 
  return		: None
  Note			: None
*****************************************************************************/
static void CanIfProxy_ReadFfNpci( uint8* t_pu1Data )
{
	uint32 t_u4FfDl;

	t_u4FfDl =  ( (uint32)t_pu1Data[CANIFPROXY_DF_OFFS_FFDL_BYTE1] < u1CANIFPROXY_SHIFT_1BYTE ) & (uint8)CANIFPROXY_DF_MASK_FFDL_BYTE1;
	t_u4FfDl +=   (uint32)t_pu1Data[CANIFPROXY_DF_OFFS_FFDL_BYTE0] & (uint32)CANIFPROXY_DF_MASK_FFDL_BYTE0;

	if ( t_u4FfDl == (uint32)CANIFPROXY_FFDL_LD_JUDGE_VALUE )
	{
		t_u4FfDl =  ( (uint32)t_pu1Data[CANIFPROXY_DF_OFFS_FFDL_LD_BYTE3] < u1CANIFPROXY_SHIFT_3BYTE ) & u4CANIFPROXY_MASK_BIT_31_24;
		t_u4FfDl += ( (uint32)t_pu1Data[CANIFPROXY_DF_OFFS_FFDL_LD_BYTE2] < u1CANIFPROXY_SHIFT_2BYTE ) & u4CANIFPROXY_MASK_BIT_23_16;
		t_u4FfDl += ( (uint32)t_pu1Data[CANIFPROXY_DF_OFFS_FFDL_LD_BYTE1] < u1CANIFPROXY_SHIFT_1BYTE ) & u4CANIFPROXY_MASK_BIT_15_08;
		t_u4FfDl +=   (uint32)t_pu1Data[CANIFPROXY_DF_OFFS_FFDL_LD_BYTE0] & u4CANIFPROXY_MASK_BIT_07_00;
	}

	CanIfProxy_stMfReqStatus.u4FfDl = t_u4FfDl;

	return;
}

/*****************************************************************************
  Function		: 
  Description	: 
  param[in/out] : 
  return		: None
  Note			: None
*****************************************************************************/
static void CanIfProxy_ReadFcNpci( uint8* t_pu1Data )
{
	CanIfProxy_stMfReqStatus.u1Fs = t_pu1Data[CANIFPROXY_DF_OFFS_FS] & (uint8)CANIFPROXY_DF_MASK_FS;
	CanIfProxy_stMfReqStatus.u1Bs = t_pu1Data[CANIFPROXY_DF_OFFS_BS];
	CanIfProxy_stMfReqStatus.u1STMin = t_pu1Data[CANIFPROXY_DF_OFFS_STMIN];

	return;
}

/*****************************************************************************
  Function		: 
  Description	: 
  param[in/out] : 
  return		: None
  Note			: None
*****************************************************************************/
static uint8 CanIfProxy_GetNPduType( const CanMsgType* t_pstMsg )
{
	uint8 t_u1NPduType;

	/* Get N_PDUType */
	t_u1NPduType = ( t_pstMsg->ptData[CANIFPROXY_DF_OFFS_NPDUTYPE] & (uint8)CANIFPROXY_DF_MASK_NPDUTYPE );

	return t_u1NPduType;
}

/*****************************************************************************
  Function		: 
  Description	: 
  param[in/out] : 
  return		: None
  Note			: None
*****************************************************************************/
static uint8 CanIfProxy_GetNDataLen( const CanMsgType* t_pstMsg )
{
	uint8 t_u1NDataLen;
	uint8 t_u1NPduType;

	t_u1NDataLen = t_pstMsg->u1Length;
	t_u1NPduType = CanIfProxy_GetNPduType( t_pstMsg );

	switch ( t_u1NPduType )
	{
		case (uint8)CANIFPROXY_NPDUTYPE_SF:
			if ( t_u1NDataLen <= (uint8)CANIFPROXY_CAN_DATA_LEN_MAX )
			{
				t_u1NDataLen -= (uint8)CANIFPROXY_NPCI_LEN_SF;
			}
			else
			{
				t_u1NDataLen -= (uint8)CANIFPROXY_NPCI_LEN_SF_LD;
			}
			break;
		case (uint8)CANIFPROXY_NPDUTYPE_FF:
			if ( CanIfProxy_stMfReqStatus.u4FfDl <= (uint32)CANIFPROXY_FFDL_SD_MAX )
			{
				t_u1NDataLen -= (uint8)CANIFPROXY_NPCI_LEN_FF;
			}
			else
			{
				t_u1NDataLen -= (uint8)CANIFPROXY_NPCI_LEN_FF_LD;
			}
			break;
		case (uint8)CANIFPROXY_NPDUTYPE_CF:
			t_u1NDataLen -= (uint8)CANIFPROXY_NPCI_LEN_CF;
			break;
		case (uint8)CANIFPROXY_NPDUTYPE_FC:
			t_u1NDataLen -= (uint8)CANIFPROXY_NPCI_LEN_FC;
			break;
		default:
			break;
	}

	return t_u1NDataLen;
}

/*****************************************************************************
  Function		: 
  Description	: 
  param[in/out] : 
  return		: None
  Note			: None
*****************************************************************************/
static void CanIfProxy_CalcCfThroughput( void )
{
	uint8 t_u1StMin;
	uint8 t_u1PeriodPwrOn;
	uint8 t_u1PeriodPwrOff;
	uint8 t_u1TxNumPwrOn;
	uint8 t_u1TxNumPwrOff;

	t_u1StMin = CanIfProxy_stMfReqStatus.u1STMin;

	if ( t_u1StMin == (uint8)CANIFPROXY_STMIN_MIN_MS )
	{
		t_u1PeriodPwrOn = CanIfProxy_cu1CfPeriodPwrOnSelf;
		t_u1PeriodPwrOff = CanIfProxy_cu1CfPeriodPwrOffSelf;
		t_u1TxNumPwrOn = CanIfProxy_cu1CfTxNumPwrOnSelf;
		t_u1TxNumPwrOff = CanIfProxy_cu1CfTxNumPwrOffSelf;
	}
	else if ( ( t_u1StMin > (uint8)CANIFPROXY_STMIN_MIN_MS )
		&& ( t_u1StMin <= (uint8)CANIFPROXY_STMIN_MAX_MS ) )
	{
		t_u1PeriodPwrOn = t_u1StMin + (uint8)CANIFPROXY_STMIN_MARGIN;
		t_u1PeriodPwrOff = t_u1StMin + (uint8)CANIFPROXY_STMIN_MARGIN;
		t_u1TxNumPwrOn = CanIfProxy_cu1CfTxNumDef;
		t_u1TxNumPwrOff = CanIfProxy_cu1CfTxNumDef;
	}
	else if ( ( t_u1StMin >= (uint8)CANIFPROXY_STMIN_MIN_US )
		&& ( t_u1StMin <= (uint8)CANIFPROXY_STMIN_MAX_US ) )
	{
		t_u1PeriodPwrOn = CanIfProxy_cu1CfPeriodDef + (uint8)CANIFPROXY_STMIN_MARGIN;
		t_u1PeriodPwrOff = CanIfProxy_cu1CfPeriodDef + (uint8)CANIFPROXY_STMIN_MARGIN;
		t_u1TxNumPwrOn = CanIfProxy_cu1CfTxNumDef;
		t_u1TxNumPwrOff = CanIfProxy_cu1CfTxNumDef;
	}
	else
	{
		t_u1PeriodPwrOn = (uint8)CANIFPROXY_STMIN_MAX_MS;
		t_u1PeriodPwrOff = (uint8)CANIFPROXY_STMIN_MAX_MS;
		t_u1TxNumPwrOn = CanIfProxy_cu1CfTxNumDef;
		t_u1TxNumPwrOff = CanIfProxy_cu1CfTxNumDef;
	}

	CanIfProxy_stMfReqStatus.u1CfPeriodPwrOn = t_u1PeriodPwrOn;
	CanIfProxy_stMfReqStatus.u1CfPeriodPwrOff = t_u1PeriodPwrOff;
	CanIfProxy_stMfReqStatus.u1CfTxNumPwrOn = t_u1TxNumPwrOn;
	CanIfProxy_stMfReqStatus.u1CfTxNumPwrOff = t_u1TxNumPwrOff;

	return;
}

/*****************************************************************************
  Function		: 
  Description	: 
  param[in/out] : 
  return		: None
  Note			: None
*****************************************************************************/
static uint8 CanIfProxy_IsResFrame( uint32 t_u4CanId )
{
	uint8 t_u1Ret;
	uint16 t_u2i;

	t_u1Ret = (uint8)FALSE;

	for ( t_u2i = (uint16)0U; t_u2i < CanIfProxy_cu2ResCanIdRangeNum; t_u2i++ )
	{
		if ( ( t_u4CanId >= CanIfProxy_cu4ResCanIdTble[t_u2i].u4Min )
			&& ( t_u4CanId <= CanIfProxy_cu4ResCanIdTble[t_u2i].u4Max ) )
		{
			t_u1Ret = (uint8)TRUE;
			break;
		}
	}

	return t_u1Ret;
}

/*****************************************************************************
  Function		: 
  Description	: 
  param[in/out] : 
  return		: None
  Note			: None
*****************************************************************************/
static uint8 CanIfProxy_IsPowerOn( void )
{
	uint8 t_u1Ret;
	
	if ( CanIfProxy_u1ObcTxMode == STD_ON )
	{
		t_u1Ret = (uint8)TRUE;
	}
	else
	{
		t_u1Ret = (uint8)FALSE;
	}

	return t_u1Ret;
}

/*****************************************************************************
  Function		: 
  Description	: 
  param[in/out] : None
  return		: None
  Note			: None
*****************************************************************************/
static uint8 CanIfProxy_IsEmptyTxSfBuff( void )
{
	uint8 t_u1Ret;

	t_u1Ret = (uint8)FALSE;

	if( CanIfProxy_stSfReqStatus.u2Head == CanIfProxy_stSfReqStatus.u2Tail )
	{
		t_u1Ret = (uint8)TRUE;
	}
	return t_u1Ret;
}

/*****************************************************************************
  Function		: 
  Description	: 
  param[in/out] : None
  return		: None
  Note			: None
*****************************************************************************/
static uint8 CanIfProxy_IsFullTxSfBuff( void )
{
	uint8 t_u1Ret;
	uint16 t_u2Tail;

	t_u1Ret = (uint8)FALSE;

	t_u2Tail = CanIfProxy_stSfReqStatus.u2Tail;
	CanIfProxy_AddIdxTxSfBuff( &t_u2Tail );

	if ( t_u2Tail == CanIfProxy_stSfReqStatus.u2Head )
	{
		t_u1Ret = (uint8)TRUE;
	}

	return t_u1Ret;
}

/*****************************************************************************
  Function		: 
  Description	: 
  param[in/out] : None
  return		: None
  Note			: None
*****************************************************************************/
static void CanIfProxy_AddIdxTxSfBuff( uint16* t_pu2Idx )
{
	uint16 t_u2Idx;

	t_u2Idx = *t_pu2Idx;
	t_u2Idx++;

	if ( t_u2Idx == CanIfProxy_cu2ReqBuffSfNum )
	{
		t_u2Idx = (uint16)0U;
	}
	*t_pu2Idx = t_u2Idx;

	return;
}

/*****************************************************************************
  Function		: 
  Description	: 
  param[in/out] : None
  return		: None
  Note			: None
*****************************************************************************/
static void CanIfProxy_Memcpy( uint8* t_pu1Dst, uint8* t_pu1Src, uint16 t_u2Size )
{
	uint16 t_u2i;

	/* Copy data */
	for ( t_u2i = (uint16)0U; t_u2i < t_u2Size; t_u2i++ )
	{
		t_pu1Dst[t_u2i] = t_pu1Src[t_u2i];
	}
	return;
}

/*****************************************************************************
  Function		: 
  Description	: 
  param[in/out] : None
  return		: None
  Note			: None
*****************************************************************************/
static void CanIfProxy_ReceiveChipComData( void )
{
	/* Receive Tx Mode */
	CanIfProxy_ReceiveObcTxMode();
	
	return;
}
	
/*****************************************************************************
  Function		: 
  Description	: 
  param[in/out] : None
  return		: None
  Note			: None
*****************************************************************************/
static void CanIfProxy_ReceiveObcTxMode( void )
{
	Std_ReturnType t_u1Ret;
    uint8 t_u1RxData;
    
    /* Receive Tx Mode */
    t_u1Ret = ChipCom_ReceiveSignal( (Com_SignalIdType)SIGNAL_CHIPCOM_BUS_OBC1S01_OBCTXMODEREQ, &t_u1RxData );
    
    /* Check result */
    if( t_u1Ret == E_OK )
    {
        /* Eliminate data corruption */
        if(   ( t_u1RxData == STD_OFF )
           || ( t_u1RxData == STD_ON ) )
        {
            /* Check whether the received value differs from the previous value */
            if( t_u1RxData != CanIfProxy_u1ObcTxMode )
            {
                CanIfProxy_SetObcTxMode( t_u1RxData );
                
                /* Transmit the completion of OBC transmission mode switching */
                CanIfProxy_TransmitTxModeNotification();
            }
        }
    }
	return;
}
/*****************************************************************************
  Function      : 
  Description   : 
  param[in/out] : None
  return        : None
  Note          : None
*****************************************************************************/
static void CanIfProxy_SetObcTxMode( uint8 t_u1RxData )
{
    /* Set Tx Mode */
    CanIfProxy_u1ObcTxMode = t_u1RxData;
	return;
}

/*****************************************************************************
  Function      : 
  Description   : 
  param[in/out] : None
  return        : None
  Note          : None
*****************************************************************************/
static void CanIfProxy_TransmitTxModeNotification( void )
{
    uint8 t_u1TxData;
    
    t_u1TxData = CanIfProxy_u1ObcTxMode;
    
    /* Transmit Tx Mode to ChipCom */
    (void)ChipCom_SendSignal( (Com_SignalIdType)SIGNAL_CHIPCOM_BUS_OBC1M01_OBCTXMODENOTIF, &t_u1TxData );
    
    return;
}

/*****************************************************************************
  Function      : 
  Description   : 
  param[in/out] : None
  return        : None
  Note          : None
*****************************************************************************/
static void CanIfProxy_AckTransmit( Can_IdType t_u4CanId )
{
	/* Transmit Ack to Virtual CAN */
	VCanAck_Transmit( t_u4CanId );
	
	return;
}

#define CANIFPROXY_STOP_SEC_CODE
#include <CanIfProxy_MemMap.h>
/**** End of File ***********************************************************/
