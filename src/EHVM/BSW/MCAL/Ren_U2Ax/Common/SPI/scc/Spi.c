/* Spi-r04-3000-0200-a-v00 */
/************************************************************************************************/
/*																								*/
/*		SPI Driver																				*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
#include	"Std_Types.h"
#include	"gpt_busywait.h"
#include	"Spi_Ucfg.h"

#include	"Dma.h"

#include	"Spi.h"
#include	"pil_spi.h"

/*==============================================================================================*/
/*	prototypes																					*/
/*==============================================================================================*/
#ifdef JGXSTACK
void SYNC_stack_s_cstSpi_UcfgModeCChannelData_u4NotifId( const S4* t_pcs4Param );
#endif

/*==============================================================================================*/
/*	defines / data types / structs / unions / macros											*/
/*==============================================================================================*/
/* DMA設定値 */
/* シングル転送、リロード機能1,2OFF、ディスティネーションアドレス固定、ソースアドレス増加 */
#define	u1SPI_SEND_DMA_MODE					((U1)(DMA_DMAMODE2))
/* シングル転送、リロード機能1,2OFF、ディスティネーションアドレス増加、ソースアドレス固定 */
#define	u1SPI_RECEIVE_DMA_MODE				((U1)(DMA_DMAMODE1))

/*==============================================================================================*/
/*	constants																					*/
/*==============================================================================================*/

/*==============================================================================================*/
/*	variables																					*/
/*==============================================================================================*/


/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
#pragma ghs section text=".SPI_TEXT_CODE"
/*----------------------------------------------------------------------------------------------*/
/* API Functions																				*/
/*----------------------------------------------------------------------------------------------*/
#if ( SPI_CFG_MODEA_USE == ON )
/*----------------------------------------------------------------------------------------------*/
/*	Synchronous Transmit Function(Single Frame)													*/
/*	return		: ReceiveData																	*/
/*	parameters	: ModeAChannelID, SendData														*/
/*----------------------------------------------------------------------------------------------*/
U4	Spi_SyncTransmit_SingleFrame( U1 t_u1ModeAChannelID, U4 t_u4SendData )
{
	const	Spi_ModeA_ChannelConfigType*	t_pcstChannelConfig;
	const	Pil_Spi_ChannelConfigType*		t_pcstPilChannelConfig;
	U4										t_u4ReceiveData;
	U1										t_u1HwChannel;
	U1										t_u1ComResult;

	t_pcstChannelConfig = &cstSpi_UcfgModeAData.pstChannelConfig[t_u1ModeAChannelID];
	t_u1HwChannel = t_pcstChannelConfig->u1HwChannel;
	t_pcstPilChannelConfig = &t_pcstChannelConfig->stPilChannelConfig;
	t_u1ComResult = (U1)OK;

	Pil_Spi_SetFrameNumber( t_u1HwChannel , (U2)1U );
	t_u4ReceiveData = Pil_Spi_SendReceiveData( t_u1HwChannel, t_u4SendData, t_pcstPilChannelConfig, &t_u1ComResult );

	return ( t_u4ReceiveData );
}

/*----------------------------------------------------------------------------------------------*/
/*	Synchronous Transmit Function																*/
/*	return		: Transmission command has been accepted or not									*/
/*	parameters	: Sequence ID																	*/
/*----------------------------------------------------------------------------------------------*/
Std_ReturnType Spi_SyncTransmit ( Spi_SequenceType Sequence )
{
	const	Spi_ModeA_ChannelConfigType*	t_pcstChannelConfig;
	const	Pil_Spi_ChannelConfigType*		t_pcstPilChannelConfig;
	U1										t_u1HwChannel;
	U2										t_u2Length;	
	S4										i;
	U2										t_u2DataSize;	
	U1										t_u1ModeAChannelID;
	U1										t_u1ReturnValue;
	const	Spi_DataBufferType*				t_pcu1SrcDataPtr;
	Spi_DataBufferType*						t_pu1DesDataPtr;
	U1										t_u1ComResult;
	U1										t_u1SeqResult;

	t_u1ModeAChannelID = cstSpi_UcfgModeAData.pstSeqConfig[Sequence];
	t_pcstChannelConfig = &cstSpi_UcfgModeAData.pstChannelConfig[t_u1ModeAChannelID];
	t_u2DataSize = t_pcstChannelConfig->u2DataSize;
	t_u1HwChannel = t_pcstChannelConfig->u1HwChannel;
	t_pcstPilChannelConfig = &t_pcstChannelConfig->stPilChannelConfig;
	t_u2Length = stSpi_ModeA_ChannelData[t_u1ModeAChannelID].u2DataBufferLength;
	t_pcu1SrcDataPtr = stSpi_ModeA_ChannelData[t_u1ModeAChannelID].pcu1SrcDataPtr;
	t_pu1DesDataPtr = stSpi_ModeA_ChannelData[t_u1ModeAChannelID].pu1DesDataPtr;
	t_u1ReturnValue = (Std_ReturnType)E_NOT_OK;
	t_u1ComResult = (U1)OK;
	t_u1SeqResult = (U1)OK;

	if ( stSpi_ModeA_ChannelData[t_u1ModeAChannelID].enSeqResult != SPI_SEQ_PENDING )
	{
		/* Set sequence state to SPI_SEQ_PENDING */
		stSpi_ModeA_ChannelData[t_u1ModeAChannelID].enSeqResult = SPI_SEQ_PENDING;

		Pil_Spi_SetFrameNumber( t_u1HwChannel , t_u2Length );

		if ( t_u2DataSize == PIL_SPI_LENGTH_8BIT )
		{
			for ( i = (S4)0U; i < (S4)t_u2Length; i++ )
			{
				t_pu1DesDataPtr[i] = (U1)Pil_Spi_SendReceiveData( t_u1HwChannel, (U4)t_pcu1SrcDataPtr[i], t_pcstPilChannelConfig, &t_u1ComResult );
				t_u1SeqResult |= t_u1ComResult;
			}
		}
		else if ( t_u2DataSize == PIL_SPI_LENGTH_16BIT )
		{
			for ( i = (S4)0U; i < (S4)t_u2Length; i++ )
			{
				((U2*)t_pu1DesDataPtr)[i] = (U2)Pil_Spi_SendReceiveData( t_u1HwChannel, (U4)((const U2*)t_pcu1SrcDataPtr)[i], t_pcstPilChannelConfig, &t_u1ComResult );
				t_u1SeqResult |= t_u1ComResult;
			}
		}
		else
		{
			for ( i = (S4)0U; i < (S4)t_u2Length; i++ )
			{
				((U4*)t_pu1DesDataPtr)[i] = Pil_Spi_SendReceiveData( t_u1HwChannel, (U4)((const U4*)t_pcu1SrcDataPtr)[i], t_pcstPilChannelConfig, &t_u1ComResult );
				t_u1SeqResult |= t_u1ComResult;
			}
		}

		/* If it hasn't timed out, set it to OK. */
		if( t_u1SeqResult == (U1)OK )
		{
			stSpi_ModeA_ChannelData[t_u1ModeAChannelID].enSeqResult = SPI_SEQ_OK;
			t_u1ReturnValue = (Std_ReturnType)E_OK;
		}
		else
		{
			stSpi_ModeA_ChannelData[t_u1ModeAChannelID].enSeqResult = SPI_SEQ_FAILED;
		}
	}

	return( t_u1ReturnValue );
}

/*----------------------------------------------------------------------------------------------*/
/*	Get Sequence Result Function																*/
/*	return		: Sequence Result																*/
/*	parameters	: Sequence ID																	*/
/*----------------------------------------------------------------------------------------------*/
Spi_SeqResultType Spi_GetSequenceResult ( Spi_SequenceType Sequence )
{
	Spi_SeqResultType 	t_enSeqResult;
	U1					t_u1ModeAChannelID;

	t_u1ModeAChannelID = cstSpi_UcfgModeAData.pstSeqConfig[Sequence];

	/* inform of sequence status (result) */
	t_enSeqResult = stSpi_ModeA_ChannelData[t_u1ModeAChannelID].enSeqResult;

	return( t_enSeqResult );
}

/*----------------------------------------------------------------------------------------------*/
/*	Setup Enternal Buffer Function																*/
/*	return		: Setup command has been accepted												*/
/*	parameters	: ModeAChannelID, SrcBufferPointer, DesBufferPointer, FrameLength				*/
/*----------------------------------------------------------------------------------------------*/
Std_ReturnType Spi_SetupEB ( Spi_ChannelType Channel,  const Spi_DataBufferType* SrcDataBufferPtr, Spi_DataBufferType* DesDataBufferPtr, Spi_NumberOfDataType Length )
{
	BSW_CFG_GETSPINLOCK_SPI();
	/* DI_ALL(); */		/* GETSPINLOCK内でDI_ALL実施のためコメント化 */

	/* Transmit buffer address */
	stSpi_ModeA_ChannelData[Channel].pcu1SrcDataPtr  = SrcDataBufferPtr;

	/* receive buffer address */
	stSpi_ModeA_ChannelData[Channel].pu1DesDataPtr   = DesDataBufferPtr;

	/* Number of buffer arrays		*/
	stSpi_ModeA_ChannelData[Channel].u2DataBufferLength = Length;

	/* EI_ALL(); */		/* RELEASESPINLOCK内でEI_ALL実施のためコメント化 */
	BSW_CFG_RELEASESPINLOCK_SPI();

	return( (Std_ReturnType)E_OK );
}

/*----------------------------------------------------------------------------------------------*/
/*	RegChk Function																				*/
/*	return		: Register Check Result															*/
/*	parameters	: Channel, Mode																	*/
/*----------------------------------------------------------------------------------------------*/
Spi_RegChkResultType	Spi_CheckRegister( Spi_ChannelType Channel, Spi_RegChkModeType Mode )
{
	const	Spi_ModeA_ChannelConfigType*	t_pcstModeAChannelConfig;
	const	Pil_Spi_ChannelConfigType*		t_pcstPilChannelConfig;
	U1										t_u1HwChannel;
	U1										t_u1RegError;
	U1										t_u1UnitNo;
	Spi_RegChkResultType					t_enResult;

	t_enResult = SPI_REGCHK_NG;

	if( Channel < cstSpi_UcfgModeAData.u1ChannelNum )
	{
		t_pcstModeAChannelConfig = &cstSpi_UcfgModeAData.pstChannelConfig[Channel];
		t_u1HwChannel = t_pcstModeAChannelConfig->u1HwChannel;
		t_pcstPilChannelConfig = &t_pcstModeAChannelConfig->stPilChannelConfig;

		t_u1RegError = Pil_Spi_CheckComMode( t_u1HwChannel, t_pcstPilChannelConfig );

		if( t_u1RegError == (U1)NG )
		{
			/* Refresh requirement check */
			if( Mode == SPI_REGCHK_MODE_WITH_REFRESH )
			{
				/* BSW_CFG_GETSPINLOCK_SPI(); */	/* CheckRegisterとSyncTransmit同時実行は禁止のため、割り禁不要 */
				/* DI_ALL(); */						/* GETSPINLOCK内でDI_ALL実施のためコメント化 */

				/*  各レジスタはCTL0.EN=0のときのみ設定可能なため、EN=0とする */
				Pil_Spi_DisableCommunication( t_u1HwChannel );
				Pil_Spi_SetComMode( t_u1HwChannel, t_pcstPilChannelConfig );

				t_u1UnitNo = Pil_Spi_GetUnitNo( t_u1HwChannel );				/* ユニット番号を取得する */
				Pil_Spi_EnableUnit( t_u1UnitNo );								/* 対象のユニットを有効化する */

				/* EI_ALL(); */		/* RELEASESPINLOCK内でEI_ALL実施のためコメント化 */
				/* BSW_CFG_RELEASESPINLOCK_SPI(); */

				/* recheck */
				t_u1RegError = Pil_Spi_CheckComMode( t_u1HwChannel, t_pcstPilChannelConfig );

				if( t_u1RegError == (U1)OK )
				{
					t_enResult = SPI_REGCHK_REFRESH_SUCCESS;
				}
				else
				{
					t_enResult = SPI_REGCHK_REFRESH_FAILED;
				}
			}
		}
		else
		{
			t_enResult = SPI_REGCHK_OK;
		}
	}

	return ( t_enResult );
}
#endif

#if ( SPI_CFG_MODEB_USE == ON )
/*----------------------------------------------------------------------------------------------*/
/*	Interrupt Transmit Function																	*/
/*	return		: ReceiveData																	*/
/*	parameters	: ModeBChannelID, SendData														*/
/*----------------------------------------------------------------------------------------------*/
U4	Spi_InterruptTransmit( U1 t_u1ModeBChannelID, U4 t_u4SendData )
{
	const	Spi_ModeB_ChannelConfigType*	t_pcstChannelConfig;
	const	Pil_Spi_ChannelConfigType*		t_pcstPilChannelConfig;
	U4										t_u4ReceiveData;
	U1										t_u1HwChannel;

	t_pcstChannelConfig = &cstSpi_UcfgModeBData.pstChannelConfig[t_u1ModeBChannelID];
	t_u1HwChannel = t_pcstChannelConfig->u1HwChannel;
	t_pcstPilChannelConfig = &t_pcstChannelConfig->stPilChannelConfig;

	Pil_Spi_SetFrameNumber( t_u1HwChannel , (U2)1U );
	t_u4ReceiveData = Pil_Spi_SendReceiveData( t_u1HwChannel, t_u4SendData, t_pcstPilChannelConfig );

	return ( t_u4ReceiveData );
}
#endif

#if ( SPI_CFG_MODEC_USE == ON )
/*----------------------------------------------------------------------------------------------*/
/*	Asynchronous Transmit Function																*/
/*	return		: Result( u1SPI_NO_ERROR / u1SPI_DMA_ADDRESS_ALIGNMENT_ERROR / u1SPI_DMA_TIMEOUT )	*/
/*	parameters	: ModeCChannelID, SendDataBufferPointer(Async),									*/
/*				: ReceiveDataBufferPointer(Async), SendReceiveDataTimes(1 Times = 1/2/4byte)	*/
/*----------------------------------------------------------------------------------------------*/
U1	Spi_AsyncTransmit( U1 t_u1ModeCChannelID, const Spi_ModeC_DataType* t_pcstSendData, const Spi_ModeC_DataType* t_pcstReceiveData, U2 t_u2Times )
{
	const	Spi_ModeC_ChannelConfigType*	t_pcstChannelConfig;
	const	Pil_Spi_ChannelConfigType*		t_pcstPilChannelConfig;
	U1										t_u1HwChannel;
	U1										t_u1SendDmaChannel;
	U1										t_u1ReceiveDmaChannel;
	U1										t_u1UnitNo;
	U1										t_u1ChNo;
	U1										t_u1MasterSlave;
	U2										t_u2Data;
	U1										t_u1Ret;
	U4										t_u4AddressMask;
#if ( SPI_CFG_SENDDMASTOP_TIMEOUT < PIL_SPI_WAIT_MAX ) || ( SPI_CFG_RECEIVEDMASTOP_TIMEOUT < PIL_SPI_WAIT_MAX ) || ( SPI_CFG_ASYNCDMASTART_TIMEOUT  < PIL_SPI_WAIT_MAX )
	U4										t_u4CountVal;
#endif

	t_pcstChannelConfig = &cstSpi_UcfgModeCData.pstChannelConfig[t_u1ModeCChannelID];
	t_u4AddressMask = t_pcstChannelConfig->u4AddressMask;
	t_u1Ret = u1SPI_NO_ERROR;

	if ( ( ( (U4)t_pcstSendData & t_u4AddressMask ) == 0 )
	  && ( ( (U4)t_pcstReceiveData & t_u4AddressMask ) == 0 ) )
	{
		t_u1HwChannel = t_pcstChannelConfig->u1HwChannel;
		t_pcstPilChannelConfig = &t_pcstChannelConfig->stPilChannelConfig;
		t_u1SendDmaChannel = t_pcstChannelConfig->u1DmaTxChannel;
		t_u1ReceiveDmaChannel = t_pcstChannelConfig->u1DmaRxChannel;
		t_u1MasterSlave = t_pcstPilChannelConfig->u1MasterSlave;

		t_u1UnitNo = Pil_Spi_GetUnitNo( t_u1HwChannel );
		t_u1ChNo = Pil_Spi_GetSpiChNo( t_u1HwChannel );

		BSW_CFG_GETSPINLOCK_SPI();
		/* DI_ALL(); */		/* GETSPINLOCK内でDI_ALL実施のためコメント化 */

		/* DMA転送無効化 */
		Dma_DisableTrans( t_u1SendDmaChannel );
		Dma_DisableTrans( t_u1ReceiveDmaChannel );

		/* 同一HwChannelで実施中の通信停止 */
		Pil_Spi_DisableCommunication( t_u1HwChannel );

		/* レジスタ再設定(使用時リフレッシュ) */
		Pil_Spi_SetComMode( t_u1HwChannel, t_pcstPilChannelConfig );

#if ( SPI_CFG_SENDDMASTOP_TIMEOUT < PIL_SPI_WAIT_MAX )
		t_u4CountVal = (U4)0;
#endif
		/* Dma_Disable前に実施開始していたDMA転送の完了待ち(Dma_SetTransModeでDMA設定後にDMA転送完了すると、DMA転送回数が1回ずれるため) */
		while(Dma_GetTransStatus( t_u1SendDmaChannel ) == u1DMA_TRANS_STATUS_BUSY)
		{
			/* DMA転送の完了待ち */
#if ( SPI_CFG_SENDDMASTOP_TIMEOUT < PIL_SPI_WAIT_MAX )
			/* タイムアウト判定 */
			if( t_u4CountVal >= (U4)SPI_CFG_SENDDMASTOP_TIMEOUT )
			{
				t_u1Ret = u1SPI_DMA_TIMEOUT;
				break;
			}
			vd_g_Gpt_BusyWait( GPT_BUSY_WAIT_1_US );
			t_u4CountVal++;														/* @qac 3383:ラップアラウンドしない */
#endif
		}

		Dma_SetTransMode( t_u1SendDmaChannel,
						  t_pcstChannelConfig->u1DmaSize,
						  u1SPI_SEND_DMA_MODE,
						  (volatile const void*)&( t_pcstSendData->u1Data ),
						  (volatile const void*)&(cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unTXDA0.u4Data),
						  t_u2Times );

		/* DMA転送有効化(送信側) */
		Dma_EnableTrans( t_u1SendDmaChannel );

#if ( SPI_CFG_RECEIVEDMASTOP_TIMEOUT < PIL_SPI_WAIT_MAX )
		t_u4CountVal = (U4)0;
#endif
		/* Dma_Disable前に実施開始していたDMA転送の完了待ち(SetTransModeでDMA設定後にDMA転送完了すると、DMA転送回数が1回ずれるため) */
		while(Dma_GetTransStatus( t_u1ReceiveDmaChannel ) == u1DMA_TRANS_STATUS_BUSY)
		{
			/* DMA転送の完了待ち */
#if ( SPI_CFG_RECEIVEDMASTOP_TIMEOUT < PIL_SPI_WAIT_MAX )
			/* タイムアウト判定 */
			if( t_u4CountVal >= (U4)SPI_CFG_RECEIVEDMASTOP_TIMEOUT )
			{
				t_u1Ret = u1SPI_DMA_TIMEOUT;
				break;
			}
			vd_g_Gpt_BusyWait( GPT_BUSY_WAIT_1_US );
			t_u4CountVal++;														/* @qac 3383:ラップアラウンドしない */
#endif
		}

		Dma_SetTransMode( t_u1ReceiveDmaChannel,
						  t_pcstChannelConfig->u1DmaSize,
						  u1SPI_RECEIVE_DMA_MODE,
						  (volatile const void*)&(cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unRXDA0.u4Data),
						  (volatile const void*)&( t_pcstReceiveData->u1Data ),
						  t_u2Times );

		/* 受信完了通知の有効・無効のコンフィグによって割り込み許可・禁止を切り替える */
		Dma_SetInterrupt( t_pcstChannelConfig->u1DmaRxChannel, (U1)OFF, t_pcstChannelConfig->u1NotifEnable );

		/* DMA転送有効化(受信側) */
		Dma_EnableTrans( t_u1ReceiveDmaChannel );

		/* DMA転送トリガ */
		Pil_Spi_StartAsync( t_u1HwChannel, t_pcstPilChannelConfig, t_u2Times );

		stSpi_ModeC_ChannelData[t_u1ModeCChannelID].u1Status = u1SPI_BUSY;

		if ( t_u1MasterSlave == (U1)PIL_SPI_MASTERSLAVE_SLAVE )
		{
#if ( SPI_CFG_ASYNCDMASTART_TIMEOUT < PIL_SPI_WAIT_MAX )
			t_u4CountVal = (U4)0;
#endif
			do{
				t_u2Data = Dma_GetTransCount( t_u1SendDmaChannel );				/* DMA転送回数取得 */
#if ( SPI_CFG_ASYNCDMASTART_TIMEOUT < PIL_SPI_WAIT_MAX )
				/* タイムアウト判定 */
				if( t_u4CountVal >= (U4)SPI_CFG_ASYNCDMASTART_TIMEOUT )
				{
					t_u1Ret = u1SPI_DMA_TIMEOUT;
					break;
				}
				vd_g_Gpt_BusyWait( GPT_BUSY_WAIT_1_US );
				t_u4CountVal++;													/* @qac 3383:ラップアラウンドしない */
#endif
			}while ( t_u2Data >= t_u2Times );
		}

		/* EI_ALL(); */		/* RELEASESPINLOCK内でEI_ALL実施のためコメント化 */
		BSW_CFG_RELEASESPINLOCK_SPI();
	}
	else
	{
		t_u1Ret = u1SPI_DMA_ADDRESS_ALIGNMENT_ERROR;
	}

	return ( t_u1Ret );
}

/*----------------------------------------------------------------------------------------------*/
/*	Transmit Status Get Function																*/
/*	return		: Transmit Status																*/
/*	parameters	: ModeCChannelID																*/
/*----------------------------------------------------------------------------------------------*/
U1		Spi_GetStatus( U1 t_u1ModeCChannelID )
{
	U1										t_u1Status;
	U1										t_u1ReceiveDmaChannel;

	BSW_CFG_GETSPINLOCK_SPI();
	/* DI_ALL(); */		/* GETSPINLOCK内でDI_ALL実施のためコメント化 */

	t_u1Status = stSpi_ModeC_ChannelData[t_u1ModeCChannelID].u1Status;

	if( t_u1Status == u1SPI_BUSY )
	{
		t_u1ReceiveDmaChannel = cstSpi_UcfgModeCData.pstChannelConfig[t_u1ModeCChannelID].u1DmaRxChannel;
		if( Dma_GetTransCount( t_u1ReceiveDmaChannel ) == (U2)0 )
		{
			t_u1Status = u1SPI_IDLE;
			stSpi_ModeC_ChannelData[t_u1ModeCChannelID].u1Status = t_u1Status;
		}
	}

	/* EI_ALL(); */		/* RELEASESPINLOCK内でEI_ALL実施のためコメント化 */
	BSW_CFG_RELEASESPINLOCK_SPI();

	return( t_u1Status );
}

/*----------------------------------------------------------------------------------------------*/
/*	Asynchronous Transmit Cancel Function														*/
/*	return		: none																			*/
/*	parameters	: ModeCChannelID																*/
/*----------------------------------------------------------------------------------------------*/
void	Spi_CancelAsyncTransmit( U1 t_u1ModeCChannelID )
{
	U1										t_u1SendDmaChannel;
	U1										t_u1ReceiveDmaChannel;
#if ( SPI_CFG_SENDDMASTOP_TIMEOUT < PIL_SPI_WAIT_MAX ) || ( SPI_CFG_RECEIVEDMASTOP_TIMEOUT < PIL_SPI_WAIT_MAX )
	U4										t_u4CountVal;
#endif
	
	t_u1SendDmaChannel = cstSpi_UcfgModeCData.pstChannelConfig[t_u1ModeCChannelID].u1DmaTxChannel;
	t_u1ReceiveDmaChannel = cstSpi_UcfgModeCData.pstChannelConfig[t_u1ModeCChannelID].u1DmaRxChannel;

	BSW_CFG_GETSPINLOCK_SPI();
	/* DI_ALL(); */		/* GETSPINLOCK内でDI_ALL実施のためコメント化 */

	Dma_DisableTrans( t_u1SendDmaChannel );
	Dma_DisableTrans( t_u1ReceiveDmaChannel );

	/* 受信完了通知の有効・無効のコンフィグにかかわらず割り込み禁止にする */
	Dma_SetInterrupt( t_u1ReceiveDmaChannel, (U1)OFF, (U1)OFF );

#if ( SPI_CFG_SENDDMASTOP_TIMEOUT < PIL_SPI_WAIT_MAX )
	t_u4CountVal = (U4)0;
#endif
	while(Dma_GetTransStatus( t_u1SendDmaChannel ) == u1DMA_TRANS_STATUS_BUSY)
	{
		/* DMA転送の完了待ち */
#if ( SPI_CFG_SENDDMASTOP_TIMEOUT < PIL_SPI_WAIT_MAX )
		/* タイムアウト判定 */
		if( t_u4CountVal >= (U4)SPI_CFG_SENDDMASTOP_TIMEOUT )
		{
			break;
		}
		vd_g_Gpt_BusyWait( GPT_BUSY_WAIT_1_US );
		t_u4CountVal++;														/* @qac 3383:ラップアラウンドしない */
#endif
	}
#if ( SPI_CFG_RECEIVEDMASTOP_TIMEOUT < PIL_SPI_WAIT_MAX )
	t_u4CountVal = (U4)0;
#endif
	while(Dma_GetTransStatus( t_u1ReceiveDmaChannel ) == u1DMA_TRANS_STATUS_BUSY)
	{
		/* DMA転送の完了待ち */
#if ( SPI_CFG_RECEIVEDMASTOP_TIMEOUT < PIL_SPI_WAIT_MAX )
		/* タイムアウト判定 */
		if( t_u4CountVal >= (U4)SPI_CFG_RECEIVEDMASTOP_TIMEOUT )
		{
			break;
		}
		vd_g_Gpt_BusyWait( GPT_BUSY_WAIT_1_US );
		t_u4CountVal++;														/* @qac 3383:ラップアラウンドしない */
#endif
	}

	Pil_Spi_DisableCommunication( cstSpi_UcfgModeCData.pstChannelConfig[t_u1ModeCChannelID].u1HwChannel );
	stSpi_ModeC_ChannelData[t_u1ModeCChannelID].u1Status = u1SPI_IDLE;

	/* EI_ALL(); */		/* RELEASESPINLOCK内でEI_ALL実施のためコメント化 */
	BSW_CFG_RELEASESPINLOCK_SPI();
}
#endif

#if ( SPI_CFG_MODEC_USE == ON )
/*----------------------------------------------------------------------------------------------*/
/*	Overrun Error Status Get Function															*/
/*	return		: Overrun Error Status															*/
/*	parameters	: ModeCChannelID																*/
/*----------------------------------------------------------------------------------------------*/
ZORN	Spi_GetOvrunErrStatus( U1 t_u1ModeCChannelID )
{
	ZORN									t_udStatus;
	U1										t_u1HwChannel;

	t_u1HwChannel = cstSpi_UcfgModeCData.pstChannelConfig[t_u1ModeCChannelID].u1HwChannel;
	t_udStatus = Pil_Spi_GetOvrunErrStatus( t_u1HwChannel );

	return ( t_udStatus );
}
#endif

/*----------------------------------------------------------------------------------------------*/
/* Scheduled / Event Functions																	*/
/*----------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------*/
/*	Pre Port Initialization Function															*/
/*	return		: none																			*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	Spi_PrePortInit( void )
{
#if ( SPI_CFG_MODEA_USE == ON )
	const	Spi_ModeA_ChannelConfigType*	t_pcstModeAChannelConfig;
#endif

#if ( SPI_CFG_MODEB_USE == ON )
	const	Spi_ModeB_ChannelConfigType*	t_pcstModeBChannelConfig;
#endif

#if ( SPI_CFG_MODEC_USE == ON )
	const	Spi_ModeC_ChannelConfigType*	t_pcstModeCChannelConfig;
#endif

#if ( ( SPI_CFG_MODEA_USE == ON ) || ( SPI_CFG_MODEB_USE == ON ) || ( SPI_CFG_MODEC_USE == ON ) )
	const	Pil_Spi_ChannelConfigType*		t_pcstPilChannelConfig;
	S4										i;
	U1										t_u1HwChannel;
	U1										t_u1UnitNo;
	U1										t_u1Enable_Unit[u1PIL_SPI_UNIT_NUM];

	for ( i = (S4)0; i < (S4)u1PIL_SPI_UNIT_NUM; i++ )
	{
		t_u1Enable_Unit[i] = (U1)OFF;									/* 初期値無効とする */
	}
#endif
/* Pil_Spi_SetComModeは、通信停止状態でのコールが前提だが、							*/
/* 本関数コール時は、通信停止状態のため、Pil_Spi_DisableCommunicationはコールしない	*/

#if ( SPI_CFG_MODEA_USE == ON )
	for( i = (S4)0; i < (S4)cstSpi_UcfgModeAData.u1ChannelNum; i++ )
	{
		t_pcstModeAChannelConfig = &cstSpi_UcfgModeAData.pstChannelConfig[i];
		t_u1HwChannel = t_pcstModeAChannelConfig->u1HwChannel;
		t_pcstPilChannelConfig = &t_pcstModeAChannelConfig->stPilChannelConfig;

		Pil_Spi_SetComMode( t_u1HwChannel, t_pcstPilChannelConfig );

		t_u1UnitNo = Pil_Spi_GetUnitNo( t_u1HwChannel );				/* ユニット番号を取得する */
		t_u1Enable_Unit[t_u1UnitNo] = (U1)ON;							/* 有効にするべきユニット番号を記憶する */
	}
#endif

#if ( SPI_CFG_MODEB_USE == ON )
	for( i = (S4)0; i < (S4)cstSpi_UcfgModeBData.u1ChannelNum; i++ )
	{
		t_pcstModeBChannelConfig = &cstSpi_UcfgModeBData.pstChannelConfig[i];
		t_u1HwChannel = t_pcstModeBChannelConfig->u1HwChannel;
		t_pcstPilChannelConfig = &t_pcstModeBChannelConfig->stPilChannelConfig;

		Pil_Spi_SetComMode( t_u1HwChannel, t_pcstPilChannelConfig );

		t_u1UnitNo = Pil_Spi_GetUnitNo( t_u1HwChannel );				/* ユニット番号を取得する */
		t_u1Enable_Unit[t_u1UnitNo] = (U1)ON;							/* 有効にするべきユニット番号を記憶する */
	}
#endif

#if ( SPI_CFG_MODEC_USE == ON )
	for( i = (S4)0; i < (S4)cstSpi_UcfgModeCData.u1ChannelNum; i++ )
	{
		t_pcstModeCChannelConfig = &cstSpi_UcfgModeCData.pstChannelConfig[i];
		t_u1HwChannel = t_pcstModeCChannelConfig->u1HwChannel;
		t_pcstPilChannelConfig = &t_pcstModeCChannelConfig->stPilChannelConfig;

		Pil_Spi_SetComMode( t_u1HwChannel, t_pcstPilChannelConfig );

		t_u1UnitNo = Pil_Spi_GetUnitNo( t_u1HwChannel );				/* ユニット番号を取得する */
		t_u1Enable_Unit[t_u1UnitNo] = (U1)ON;							/* 有効にするべきユニット番号を記憶する */
	}
#endif

#if ( ( SPI_CFG_MODEA_USE == ON ) || ( SPI_CFG_MODEB_USE == ON ) || ( SPI_CFG_MODEC_USE == ON ) )
	for ( i = (S4)0; i < (S4)u1PIL_SPI_UNIT_NUM; i++ )
	{
		if ( t_u1Enable_Unit[i] == (U1)ON )
		{
			Pil_Spi_EnableUnit( (U1)i );
		}
	}
#endif
/* @notice Pil_Spi_EnableUnitコール後、「MSPInCLK * 3」経過後にクロック信号、CS信号のデフォルトレベルが反映される。 */
/*         上記時間はポート初期設定の前までに反映できていれば良いため、成り行きで確保している。 */
}

/*----------------------------------------------------------------------------------------------*/
/*	Initialization1 Function																	*/
/*	return		: none																			*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	Spi_Init1( void )
{
#if ( ( SPI_CFG_MODEA_USE == ON ) || ( SPI_CFG_MODEC_USE == ON ) )
	S4										i;
#endif

#if ( SPI_CFG_MODEA_USE == ON )
	for ( i = (S4)0U; i < (S4)cstSpi_UcfgModeAData.u1ChannelNum; i++ )
	{
		stSpi_ModeA_ChannelData[i].pcu1SrcDataPtr = NULL_PTR;						/* Transmit buffer address */
		stSpi_ModeA_ChannelData[i].pu1DesDataPtr  = NULL_PTR;						/* receive buffer address */
		stSpi_ModeA_ChannelData[i].u2DataBufferLength = (Spi_NumberOfDataType)0U;	/* Number of buffer arrays	*/
		stSpi_ModeA_ChannelData[i].enSeqResult = SPI_SEQ_OK;						/* Sequece result */
	}
#endif

#if ( SPI_CFG_MODEC_USE == ON )
	for( i = (S4)0; i < (S4)cstSpi_UcfgModeCData.u1ChannelNum; i++ )
	{
		stSpi_ModeC_ChannelData[i].u1Status = u1SPI_IDLE;
	}
#endif
}

/*----------------------------------------------------------------------------------------------*/
/*	De-Initialization Function																	*/
/*	return		: none																			*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	Spi_DeInit( void )/* 使用しているチャネルのみDeInit。 */
{
#if ( SPI_CFG_MODEA_USE == ON )
	const	Spi_ModeA_ChannelConfigType*	t_pcstModeAChannelConfig;
#endif

#if ( SPI_CFG_MODEB_USE == ON )
	const	Spi_ModeB_ChannelConfigType*	t_pcstModeBChannelConfig;
#endif

#if ( SPI_CFG_MODEC_USE == ON )
	const	Spi_ModeC_ChannelConfigType*	t_pcstModeCChannelConfig;
	U1										t_u1SendDmaChannel;
	U1										t_u1ReceiveDmaChannel;
#if ( SPI_CFG_SENDDMASTOP_TIMEOUT < PIL_SPI_WAIT_MAX ) || ( SPI_CFG_RECEIVEDMASTOP_TIMEOUT < PIL_SPI_WAIT_MAX )
	U4										t_u4CountVal;
#endif
#endif

#if ( ( SPI_CFG_MODEA_USE == ON ) || ( SPI_CFG_MODEB_USE == ON ) || ( SPI_CFG_MODEC_USE == ON ) )
	S4										i;
	U1										t_u1HwChannel;
#endif

#if ( SPI_CFG_MODEA_USE == ON )
	for( i = (S4)0; i < (S4)cstSpi_UcfgModeAData.u1ChannelNum; i++ )
	{
		t_pcstModeAChannelConfig = &cstSpi_UcfgModeAData.pstChannelConfig[i];
		t_u1HwChannel = t_pcstModeAChannelConfig->u1HwChannel;

		Pil_Spi_DisableCommunication( t_u1HwChannel );
	}
#endif

#if ( SPI_CFG_MODEB_USE == ON )
	for( i = (S4)0; i < (S4)cstSpi_UcfgModeBData.u1ChannelNum; i++ )
	{
		t_pcstModeBChannelConfig = &cstSpi_UcfgModeBData.pstChannelConfig[i];
		t_u1HwChannel = t_pcstModeBChannelConfig->u1HwChannel;

		Pil_Spi_DisableCommunication( t_u1HwChannel );
	}
#endif

#if ( SPI_CFG_MODEC_USE == ON )
	for( i = (S4)0; i < (S4)cstSpi_UcfgModeCData.u1ChannelNum; i++ )
	{
		t_pcstModeCChannelConfig = &cstSpi_UcfgModeCData.pstChannelConfig[i];
		t_u1HwChannel = t_pcstModeCChannelConfig->u1HwChannel;

		t_u1SendDmaChannel = t_pcstModeCChannelConfig->u1DmaTxChannel;
		Dma_DisableTrans( t_u1SendDmaChannel );

		t_u1ReceiveDmaChannel = t_pcstModeCChannelConfig->u1DmaRxChannel;
		Dma_DisableTrans( t_u1ReceiveDmaChannel );

#if ( SPI_CFG_SENDDMASTOP_TIMEOUT < PIL_SPI_WAIT_MAX )
		t_u4CountVal = (U4)0;
#endif
		while(Dma_GetTransStatus( t_u1SendDmaChannel ) == u1DMA_TRANS_STATUS_BUSY)
		{
			/* DMA転送の完了待ち */
#if ( SPI_CFG_SENDDMASTOP_TIMEOUT < PIL_SPI_WAIT_MAX )
			/* タイムアウト判定 */
			if( t_u4CountVal >= (U4)SPI_CFG_SENDDMASTOP_TIMEOUT )
			{
				break;
			}
			vd_g_Gpt_BusyWait( GPT_BUSY_WAIT_1_US );
			t_u4CountVal++;													/* @qac 3383:ラップアラウンドしない */
#endif
		}
#if ( SPI_CFG_RECEIVEDMASTOP_TIMEOUT < PIL_SPI_WAIT_MAX )
		t_u4CountVal = (U4)0;
#endif
		while(Dma_GetTransStatus( t_u1ReceiveDmaChannel ) == u1DMA_TRANS_STATUS_BUSY)
		{
			/* DMA転送の完了待ち */
#if ( SPI_CFG_RECEIVEDMASTOP_TIMEOUT < PIL_SPI_WAIT_MAX )
			/* タイムアウト判定 */
			if( t_u4CountVal >= (U4)SPI_CFG_RECEIVEDMASTOP_TIMEOUT )
			{
				break;
			}
			vd_g_Gpt_BusyWait( GPT_BUSY_WAIT_1_US );
			t_u4CountVal++;													/* @qac 3383:ラップアラウンドしない */
#endif
		}

		Pil_Spi_DisableCommunication( t_u1HwChannel );
	}
#endif
}

#if ( SPI_CFG_MODEC_USE == ON )
/*----------------------------------------------------------------------------------------------*/
/*	Interrupt Function																			*/
/*	return		: none																			*/
/*	parameters	: ModeCChannelID																*/
/*----------------------------------------------------------------------------------------------*/
void Spi_ReceiveInterrupt( const S4* t_pcs4Param )
{
//	const	Spi_ModeC_ChannelConfigType*	t_pcstChannelConfig;
//	U4										t_u4NotifId;
//	S4										t_s4Param;
//	U1										t_u1ModeCChannelID;

//	t_u1ModeCChannelID = (U1)(*t_pcs4Param);
//	t_pcstChannelConfig = &cstSpi_UcfgModeCData.pstChannelConfig[t_u1ModeCChannelID];
//	t_u4NotifId = t_pcstChannelConfig->u4NotifId;
//	t_s4Param = (S4)t_pcstChannelConfig->u1NotifArg;

//	(void)Rte_SendEvent( t_u4NotifId , &t_s4Param );
#ifdef JGXSTACK
//    SYNC_stack_s_cstSpi_UcfgModeCChannelData_u4NotifId( &t_s4Param );
#endif /* JGXSTACK */

}
#endif

/*----------------------------------------------------------------------------------------------*/
/* Local Functions																				*/
/*----------------------------------------------------------------------------------------------*/

#pragma ghs section text=default
/*-- End Of File -------------------------------------------------------------------------------*/
