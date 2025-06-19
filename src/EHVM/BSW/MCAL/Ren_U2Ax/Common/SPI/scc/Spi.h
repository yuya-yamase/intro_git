/* Spi-r04-3000-0200-a-v00 */
/************************************************************************************************/
/*																								*/
/*		SPI Driver																				*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef SPI_H
#define SPI_H

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
#include "Spi_Ucfg.h"

#include "pil_spi.h"



/*==============================================================================================*/
/*	defines / data types / structs / unions / macros											*/
/*==============================================================================================*/
/* SPI Transmit Status */
#define		u1SPI_IDLE						((U1)0)
#define		u1SPI_BUSY						((U1)1)

/* 従来ソフトとの互換性のための定義 */
#define		SPI_IDLE						(0)
#define		SPI_BUSY						(1)

/* SPI functional safety level */
#define		SPI_QM							(0)
#define		SPI_ASIL						(1)

/* Spi SpinLockID */
typedef	struct{
	U2										u2SpinlockId;
}Spi_UserConfigType;

/* Spi Mode C Data Type */
typedef	Pil_Spi_ModeC_DataType				Spi_ModeC_DataType;

typedef U1									Spi_ChannelType;
typedef U1									Spi_DataBufferType;
typedef U2									Spi_NumberOfDataType;
typedef U1									Spi_SequenceType;

/* Definition of specific Sequences status for SPI Handler/Driver */
typedef enum
{
  /* The last transmission of the Sequence has been finished successfully */
  SPI_SEQ_OK = 0,
  /* The Sequence is ongoing or queued but not finished yet */
  SPI_SEQ_PENDING,
  /* The last transmission of the Sequence has failed */
  SPI_SEQ_FAILED,
  /* The last transmission of the Sequence has been canceled */
  SPI_SEQ_CANCELED
} Spi_SeqResultType;

/* Spi Mode A Channel Config Type */
typedef	struct{
	Pil_Spi_ChannelConfigType				stPilChannelConfig;
	U4										u4CoreId;
	U2										u2DataSize;
	U1										u1HwChannel;
}Spi_ModeA_ChannelConfigType;

/* Spi Mode A UserConfigType */
typedef	struct{
	const Spi_ModeA_ChannelConfigType*		pstChannelConfig;
	const U1*								pstSeqConfig;
	U1										u1ChannelNum;
}Spi_ModeA_UserConfigType;

/* Channel buffer information */
typedef struct {
	const Spi_DataBufferType*				pcu1SrcDataPtr;				/* Send buffer address (8 bits)		*/
	Spi_DataBufferType*						pu1DesDataPtr;				/* Receive buffer address (8 bits)	*/
	Spi_NumberOfDataType					u2DataBufferLength;			/* Number of buffer arrays	*/
	Spi_SeqResultType						enSeqResult;				/* Sequence result */
} Spi_ModeA_ChannelDataType;

/* Spi Mode B Channel Config Type */
typedef	struct{
	Pil_Spi_ChannelConfigType				stPilChannelConfig;
	U4										u4CoreId;
	U1										u1HwChannel;
}Spi_ModeB_ChannelConfigType;

/* Spi Mode B UserConfigType */
typedef	struct{
	const Spi_ModeB_ChannelConfigType*		pstChannelConfig;
	U1										u1ChannelNum;
}Spi_ModeB_UserConfigType;

/* Spi Mode C Channel Data Type */
typedef	struct{
	U1										u1Status;	/* ModeC実施中かどうか */
}Spi_ModeC_ChannelDataType;

/* Spi Mode C Channel Config Type */
typedef	struct{
	Pil_Spi_ChannelConfigType				stPilChannelConfig;
	U4										u4CoreId;
	U4										u4NotifId;
	U4										u4AddressMask;	
	U1										u1HwChannel;
	U1										u1DmaTxChannel;	/* DMA送信チャネル */
	U1										u1DmaRxChannel;	/* DMA受信チャネル */
	U1										u1DmaSize;		/* DMA転送サイズ */
	U1										u1NotifArg;
	U1										u1NotifEnable;
}Spi_ModeC_ChannelConfigType;

/* Spi Mode C User Config Type */
typedef	struct{
	const Spi_ModeC_ChannelConfigType*		pstChannelConfig;
	U1										u1ChannelNum;
}Spi_ModeC_UserConfigType;

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
/*----------------------------------------------------------------------------------------------*/
/* API Functions																				*/
/*----------------------------------------------------------------------------------------------*/
#if ( SPI_CFG_MODEA_USE == ON )
/************************************************************************************************/
/*	Service name	:	Synchronous Transmit Function(SingleFrame)								*/
/*	Reentrancy		:	Concurrency Safe for different unit numbers								*/
/*					:	Re-entrant for the same unit numbers									*/
/*	Parameters (in)	:	ModeAChannelID - ModeA Channel ID										*/
/*					:	SendData - Send Data(right-align)										*/
/*	Return value	:	ReceiveData(right-align)												*/
/*	Caveat			:	・同一ハードユニットは全て同一コアで使用すること						*/
/************************************************************************************************/
U4		Spi_SyncTransmit_SingleFrame( U1 t_u1ModeAChannelID, U4 t_u4SendData );

/************************************************************************************************/
/*	Service name	:	Synchronous Transmit Function											*/
/*	Reentrancy		:	Concurrency Safe for different sequence ID								*/
/*  Parameters(in)	:   Sequence - Sequence ID													*/
/*  Return value	:   E_OK	 - Transmission command has been accepted						*/
/*					:   E_NOT_OK - Transmission command has been rejected						*/
/*  Caveat			:   Call after Spi_PrePortInit() and Spi_SetupEB.							*/
/************************************************************************************************/
Std_ReturnType Spi_SyncTransmit ( Spi_SequenceType Sequence );

/************************************************************************************/
/*  Service name	:   Spi_GetSequenceResult										*/
/*  Reentrancy		:   Re-entrant													*/
/*  Parameters(in)	:   Sequence - Sequence ID										*/
/*  Return value	:   Spi_SeqResultType (SPI_SEQ_OK/SPI_SEQ_PENDING)				*/
/*  Caveat			:   Call after Spi_PrePortInit().								*/
/*					:   SPI_SEQ_FAILED/SPI_SEQ_CANCELED is not supported			*/
/************************************************************************************/
Spi_SeqResultType Spi_GetSequenceResult ( Spi_SequenceType Sequence );

/************************************************************************************/
/*  Service name	:   Spi_SetupEB													*/
/*	Reentrancy		:	Concurrency Safe for different unit numbers					*/
/*  Parameters(in)	:   Channel - ModeA Channel ID.									*/
/*					:   SrcDataBufferPtr - Pointer to source data buffer.			*/
/*					:   DesDataBufferPtr - Pointer to destination data buffer.		*/
/*					:   Length - Length(number of data elements) of TX/RX data		*/
/*  Return value	:   E_OK - Setup command has been accepted						*/
/*  Caveat			:   Call after Spi_PrePortInit().								*/
/************************************************************************************/
Std_ReturnType Spi_SetupEB ( Spi_ChannelType Channel,  const Spi_DataBufferType* SrcDataBufferPtr, Spi_DataBufferType* DesDataBufferPtr, Spi_NumberOfDataType Length );
#endif

#if ( SPI_CFG_MODEB_USE == ON )
/************************************************************************************************/
/*	Service name	:	Interrupt Transmit Function												*/
/*	Reentrancy		:	Concurrency Safe for different unit numbers								*/
/*					:	Re-entrant for the same unit numbers									*/
/*	Parameters (in)	:	ModeBChannelID - ModeB Channel ID										*/
/*					:	SendData - Send Data													*/
/*	Return value	:	ReceiveData																*/
/*	Caveat			:	・同一ハードユニットは全て同一コアで使用すること						*/
/************************************************************************************************/
U4		Spi_InterruptTransmit( U1 t_u1ModeBChannelID, U4 t_u4SendData );
#endif

#if ( SPI_CFG_MODEC_USE == ON )
/************************************************************************************************/
/*	Service name	:	Asynchronous Transmit Function											*/
/*	Reentrancy		:	Concurrency Safe for different unit numbers								*/
/*					:	Re-entrant for the same unit numbers									*/
/*	Parameters (in)	:	ModeCChannelID - ModeCChannelID											*/
/*					:	SendData(Async) - Send Data Buffer Pointer								*/
/*					:	Times - Send Receive Data Times (1 - 0xFFFF(1 times = 1/2/4byte))		*/
/*	Parameters (out):	ReceiveData(Async) - Receive Data Buffer Pointer						*/
/*	Return value	:	Result( No Error(==0) or Error(!=0) )									*/
/*	Caveat			:	・同一ハードユニットは全て同一コアで使用すること						*/
/*					:	・通信中に再発行した場合は通信を強制停止し、							*/
/*					:	  新しいデータを再セットして通信する。									*/
/*					:	・通信中は同じユニットを使用する他ModeC Channel IDに対する				*/
/*					:	  本APIの発行禁止														*/
/*					:	・DMAC/DTSの両方をサポート												*/
/************************************************************************************************/
ZORN	Spi_AsyncTransmit( U1 t_u1ModeCChannelID, const Spi_ModeC_DataType* t_pcstSendData, const Spi_ModeC_DataType* t_pcstReceiveData, U2 t_u2Times );

/************************************************************************************************/
/*	Service name	:	Transmit Status Get Function											*/
/*	Reentrancy		:	Concurrency Safe for different Channel ID								*/
/*					:	Re-entrant for the same Channel ID										*/
/*	Parameters (in)	:	ModeCChannelID - ModeC Channel ID										*/
/*	Return value	:	Status - ( IDLE or BUSY )												*/
/*	Caveat			:	・同一ハードユニットは全て同一コアで使用すること						*/
/************************************************************************************************/
U1		Spi_GetStatus( U1 t_u1ModeCChannelID );

/************************************************************************************************/
/*	Service name	:	Asynchronous Transmit Cancel Function									*/
/*	Reentrancy		:	Concurrency Safe for different unit numbers								*/
/*					:	Re-entrant for the same unit numbers									*/
/*	Parameters (in)	:	ModeCChannelID - ModeC Channel ID										*/
/*	Return value	:	none																	*/
/*	Caveat			:	・同一ハードユニットは全て同一コアで使用すること						*/
/************************************************************************************************/
void	Spi_CancelAsyncTransmit( U1 t_u1ModeCChannelID );
#endif

#if ( SPI_CFG_MODEC_USE == ON )
/************************************************************************************************/
/*	Service name	:	Overrun Error Status Get Function										*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	ModeCChannelID - ModeC Channel ID										*/
/*	Return value	:	Overrun Error Status( No Error(==0) or Error(!=0) )						*/
/*	Caveat			:	・オーバーランエラーはスレーブモード時のみ検出する						*/
/************************************************************************************************/
ZORN	Spi_GetOvrunErrStatus( U1 t_u1ModeCChannelID );
#endif

/*----------------------------------------------------------------------------------------------*/
/* Scheduled / Event Functions																	*/
/*----------------------------------------------------------------------------------------------*/
/************************************************************************************************/
/*	Function		:	Initialization1															*/
/*	Schedule		:	Init1																	*/
/*	Parameters (in)	:	none																	*/
/*	Relation Module	:	Before ErrH_Init_1														*/
/*	Caveat			:	none																	*/
/************************************************************************************************/
void	Spi_Init1( void );

/************************************************************************************************/
/*	Function		:	Pre-Port Initialization													*/
/*	Schedule		:	Init																	*/
/*	Parameters (in)	:	none																	*/
/*	Relation Module	:	none																	*/
/*	Caveat			:	none																	*/
/************************************************************************************************/
void	Spi_PrePortInit( void );

/************************************************************************************************/
/*	Function		:	De-Initialization														*/
/*	Schedule		:	DeInit																	*/
/*	Parameters (in)	:	none																	*/
/*	Relation Module	:	Before Dma_DeInit														*/
/*	Caveat			:	none																	*/
/************************************************************************************************/
void	Spi_DeInit( void );

/************************************************************************************************/
/*	Function		:	Refresh																	*/
/*	Schedule		:	Refresh																	*/
/*	Parameters (in)	:	none																	*/
/*	Relation Module	:	none																	*/
/*	Caveat			:	・本APIは全コアのアイドルタスクよりコールすること						*/
/************************************************************************************************/
void	Spi_Refresh( void );

#if ( SPI_CFG_MODEC_USE == ON )
/************************************************************************************************/
/*	Function		:	Interrupt Function														*/
/*	Schedule		:	DMA Trans End															*/
/*	Parameters (in)	:	t_pcs4Param(Sync) - Notification Parameter pointer						*/
/*					:		t_ps4Param[0]:ModeCChannelID - ModeC Channel ID						*/
/*	Relation Module	:	none																	*/
/*	Caveat			:	none																	*/
/************************************************************************************************/
void Spi_ReceiveInterrupt( const S4* t_pcs4Param );
#endif

/*==============================================================================================*/
/* constants																					*/
/*==============================================================================================*/
extern	const	Spi_UserConfigType			cstSpi_UcfgData;
#if ( SPI_CFG_MODEA_USE == ON )
extern	const	Spi_ModeA_UserConfigType	cstSpi_UcfgModeAData;
#endif /* ( SPI_CFG_MODEA_USE == ON ) */
#if ( SPI_CFG_MODEB_USE == ON )
extern	const	Spi_ModeB_UserConfigType	cstSpi_UcfgModeBData;
#endif /* ( SPI_CFG_MODEB_USE == ON ) */
#if ( SPI_CFG_MODEC_USE == ON )
extern	const	Spi_ModeC_UserConfigType	cstSpi_UcfgModeCData;
#endif /* ( SPI_CFG_MODEC_USE == ON ) */

/*==============================================================================================*/
/* variables																					*/
/*==============================================================================================*/
#if ( SPI_CFG_MODEC_USE == ON )
extern	Spi_ModeC_ChannelDataType			stSpi_ModeC_ChannelData[];
#endif

#if ( SPI_CFG_MODEA_USE == ON )
extern	Spi_ModeA_ChannelDataType			stSpi_ModeA_ChannelData[];
#endif


#endif /* SPI_H */
/*-- End Of File -------------------------------------------------------------------------------*/
