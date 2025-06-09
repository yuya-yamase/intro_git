/****************************************************************************/
/*【ファイル名】xspi.c                                                      */
/*【モジュール名】XSPIドライバ			                                    */
/****************************************************************************/
/****************************
*		include	files		*
****************************/
#include "xspi_internal.h"

/************************************************************************
*																		*
*				Ｄefine Ｄeclare Ｓection								*
*																		*
************************************************************************/
/****************************
*		variables			*
****************************/
static uint8	bf_drv_EnSignal;		/* EN信号状態 */
static uint8	bf_drv_ComTimeCount;	/* 呼び出し回数カウンタ */

static uint8 	bf_drv_skip_first_data = XSPI_NG;		/* 暫定対応 初回データスキップ */
static uint32 	bf_drv_dummy_rcvdata = 0x00000000UL;	/* 暫定対応 初回データスキップ */
static uint32 	bf_drv_dummy_snddata = 0x00000000UL;	/* 暫定対応 初回データスキップ */

static uint32	bf_drv_OST_START[GPT_OST_START_NUM_CFG] = {	/* OSTM開始情報 */
	((uint32)GPT_OST_START_CTRL_BIT_IRQ_EN |
	 (uint32)GPT_OST_START_CTRL_BIT_TRG_ST),		/* GPT_OST_START_CTRL */
	 (uint32)XSPI_OST_CNT_10ms						/* GPT_OST_START_PERIOD */
	};

extern BF_DRV_SPI	bf_drv_SpiMng;		/* XSPI管理情報 */

#ifdef XSPI_DEBUG
extern uint8	bf_drv_Dbg_ErrInfo;		/* デバッグ用エラー情報 */
#endif	/* XSPI_DEBUG */

/****************************
*		prototype			*
****************************/
static uint8	fs_tbl_Excute( uint8 event );						/* 処理テーブル内の該当状態・イベントの関数／状態を実施 */
static void		fc_SpiInit( void );									/* ドライバ初期化 */
static void		fc_SpiStartPrepare( void );							/* 送受信開始準備 */
static void		fc_SpiEnd( void );									/* 送受信終了 */
static void		fc_SpiAbort( void );								/* 送受信ドライバ中断 */
static void		fc_SpiStop( void );									/* 送受信ドライバ停止 */

static uint8	fc_drv_ENSigCheck( void );							/* EN信号状態チェック */

extern void		fc_drv_ClearXSpiMng( void );						/* XSPI管理情報初期化 */
extern void		fc_drv_SpiSetErrInfoKind( uint8 kind );				/* エラー種別情報設定 */
extern void		fc_drv_SpiClearErrInfoKind( uint8 kind );			/* エラー種別情報クリア */
#ifdef XSPI_DEBUG
extern void		fc_drv_SpiSetDbgErrInfo( uint8 err_info );			/* デバッグ用エラー情報設定 */
#endif	/* XSPI_DEBUG */

extern uint8	fc_drv_getRcvBufPage( void );						/* 受信バッファページ取得 */
extern uint8	fc_drv_getSndBufPage( void );						/* 送信バッファページ取得 */
extern uint8	fc_drv_ReadBuf( uint8* p_addr, uint32 size );		/* 受信データ読み出し */
extern uint8	fc_drv_WriteBuf( const uint8* p_addr, uint32 size );/* 送信データ書き込み */

#if (XSPI_DATA_BUFFER != XSPI_DATA_BUFFER_DOUBLE)
extern void		fc_drv_SpiRcvDpageRenew( void );					/* ドライバ用受信バッファページ更新 */
extern void		fc_drv_SpiSendDpageRenew( void );					/* ドライバ用送信バッファページ更新 */
#endif	/* XSPI_DATA_BUFFER */

#if (XSPI_DATA_CHECK != XSPI_DATA_CHECK_NONE)
extern uint8	fc_drv_CheckIntegrityData( const uint8* p_frame );	/* 整合性データチェック */
extern void		fc_drv_AddIntegrityData( uint8* p_frame );			/* 整合性データ付加 */
#endif	/* XSPI_DATA_CHECK */

/********************************
*		table					*
********************************/
static const TBL_DRV_SPI	tb_drv_SpiDrvJmp[CMDRV_STAT_MAX][CMDRV_EVT_MAX] = {
/* 状態 */
/* 0: 初期化前 */
	{																		/* Event */
		{ 0,					0,					0					},	/* 0：初期化 */
		{ 0,					0,					0					},	/* 1：通常動作 */
		{ 0,					0,					0					},	/* 2：通信継続 */
		{ 0,					0,					0					},	/* 3：転送未完了タイムアウト */
		{ fc_SpiInit,			CMDRV_STAT_IDLE,	XSPI_OST_CNT_10ms	},	/* 4：EN信号High */
		{ 0,					0,					0					},	/* 5：EN信号Low */
		{ 0,					0,					0					},	/* 6：通信終了 */
	},
/* 1: 通信無効（EN信号Low） */
	{																		/* Event */
		{ 0,					0,					0					},	/* 0：初期化 */
		{ 0,					0,					0					},	/* 1：通常動作 */
		{ 0,					0,					0					},	/* 2：通信継続 */
		{ 0,					0,					0					},	/* 3：転送未完了タイムアウト */
		{ fc_SpiInit,			CMDRV_STAT_IDLE,	XSPI_OST_CNT_10ms	},	/* 4：EN信号High */
		{ 0,					0,					0					},	/* 5：EN信号Low */
		{ 0,					0,					0					},	/* 6：通信終了 */
	},
/* 2: アイドル状態（EN信号High） */
	{																		/* Event */
		{ 0,					0,					0					},	/* 0：初期化 */
		{ fc_SpiStartPrepare,	CMDRV_STAT_COMM,	XSPI_OST_CNT_9_6ms	},	/* 1：通常動作 */
		{ 0,					0,					0					},	/* 2：通信継続 */
		{ 0,					0,					0					},	/* 3：転送未完了タイムアウト */
		{ 0,					0,					0					},	/* 4：EN信号High */
		{ fc_SpiStop,			CMDRV_STAT_INVALID,	XSPI_OST_CNT_10ms	},	/* 5：EN信号Low */
		{ 0,					0,					0					},	/* 6：通信終了 */
	},
/* 3: 送受信状態 */
	{																		/* Event */
		{ 0,					0,					0					},	/* 0：初期化 */
		{ 0,					0,					0					},	/* 1：通常動作 */
		{ 0,					0,					XSPI_OST_CNT_10ms	},	/* 2：通信継続 */
		{ fc_SpiAbort,			CMDRV_STAT_RETRY,	XSPI_OST_CNT_0_4ms	},	/* 3：転送未完了タイムアウト */
		{ 0,					0,					0					},	/* 4：EN信号High */
		{ fc_SpiStop,			CMDRV_STAT_INVALID,	XSPI_OST_CNT_10ms	},	/* 5：EN信号Low */
		{ fc_SpiEnd,			CMDRV_STAT_IDLE,	XSPI_OST_CNT_0_4ms	},	/* 6：通信終了 */
	},
/* 4: リトライ状態(アイドル) */
	{																		/* Event */
		{ 0,					0,					0					},	/* 0：初期化 */
		{ fc_SpiStartPrepare,	CMDRV_STAT_COMM,	XSPI_OST_CNT_9_6ms	},	/* 1：通常動作 */
		{ 0,					0,					0					},	/* 2：通信継続 */
		{ 0,					0,					0					},	/* 3：転送未完了タイムアウト */
		{ 0,					0,					0					},	/* 4：EN信号High */
		{ fc_SpiStop,			CMDRV_STAT_INVALID,	XSPI_OST_CNT_10ms	},	/* 5：EN信号Low */
		{ fc_SpiEnd,			CMDRV_STAT_IDLE,	XSPI_OST_CNT_0_4ms	},	/* 6：通信終了 */
	}
};

/****************************************************************************
*																			*
*		SYMBOL		:	PDR_SPI_FRM_WR										*
*																			*
*		DESCRIPTION	:	Frame端子ポート設定									*
*																			*
*		PARAMETER	:	IN  	:	uint32		level						*
*									( 0::Low )	bit clear 					*
*									( 1::High)	bit set   					*
*																			*
*						OUT 	:	None									*
*																			*
*						RET 	:	None									*
*																			*
****************************************************************************/
static void	PDR_SPI_FRM_WR ( uint32 level )
{
	Dio_WriteChannel( XSPI_FRM_PORT, level);
}

/****************************************************************************
*																			*
*		SYMBOL		:	PDR_SPI_EN											*
*																			*
*		DESCRIPTION	:	Enable端子ポート取得								*
*																			*
*		PARAMETER	:	IN  	:	None									*
*																			*
*						OUT 	:	None									*
*																			*
*						RET 	:	uint8 	EN端子Port状態					*
*											( 0::Low )	Ready				*
*											( 1::High)	Busy				*
*																			*
*****************************************************************************/
static uint8	PDR_SPI_EN ( void )
{
	return ( Dio_ReadChannel( XSPI_EN_PORT ) );
}

/****************************************************************************/
/************** 			公開インターフェース				*************/
/****************************************************************************/

/****************************************************************************
*																			*
*		SYMBOL		: xspi_Init												*
*																			*
*		DESCRIPTION	: XSPI通信ドライバ初期化処理							*
*																			*
*		PARAMETER	: IN  :	ch		チャネルID								*
*						XSPI_CH_01	(0x00)	XSPIチャネルID：01（IVI向け）	*
*						XSPI_CH_02	(0x01)	XSPIチャネルID：02（METER向け）	*
*						XSPI_CH_03	(0x02)	XSPIチャネルID：03（CENTRAL向け）*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	None											*
*																			*
****************************************************************************/
void	xspi_Init(
	uint8	ch
)
{
	(VOID)ch;
	/* SPIポート設定 */
	Port_SetPinMode( XSPI_SCLK_PORT, XSPI_SCLK_MODE_CFG );
	Port_SetPinMode( XSPI_TXD_PORT, XSPI_TXD_MODE_CFG );
	Port_SetPinMode( XSPI_RXD_PORT, XSPI_RXD_MODE_CFG );

	/* XSPI管理情報初期化 */
	fc_drv_ClearXSpiMng();

	/* EN信号状態初期化 */
	bf_drv_EnSignal = 0U;

	/* 呼び出し回数カウンタ初期化 */
	bf_drv_ComTimeCount = 0U;

	/* Frame信号をHigh出力 */
	PDR_SPI_FRM_WR( STD_HIGH );

	/* OSTM起動（1ms） */
	bf_drv_OST_START[GPT_OST_START_PERIOD] = XSPI_OST_CNT_1ms;
	vd_g_Gpt_OstStart( XSPI_OST_CH, bf_drv_OST_START );

	return;
}


/****************************************************************************
*																			*
*		SYMBOL		: xspi_DeInit											*
*																			*
*		DESCRIPTION	: XSPI通信ドライバ終了処理								*
*																			*
*		PARAMETER	: IN  :	ch		チャネルID								*
*						XSPI_CH_01	(0x00)	XSPIチャネルID：01（IVI向け）	*
*						XSPI_CH_02	(0x01)	XSPIチャネルID：02（METER向け）	*
*						XSPI_CH_03	(0x02)	XSPIチャネルID：03（CENTRAL向け）*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	None											*
*																			*
****************************************************************************/
void	xspi_DeInit(
	uint8	ch
)
{
	(VOID)ch;

	/* OSTM停止 */
	vd_g_Gpt_OstStop( XSPI_OST_CH );

	/* SPI非同期通信中断 */
	Spi_CancelAsyncTransmit( XSPI_COMC_ID );

	/* XSPI管理情報初期化 */
	fc_drv_ClearXSpiMng();

	/* EN信号状態初期化 */
	bf_drv_EnSignal = 0U;

	/* 呼び出し回数カウンタ初期化 */
	bf_drv_ComTimeCount = 0U;

	/* Frame信号をHigh出力 */
	PDR_SPI_FRM_WR( STD_HIGH );

	return;
}

/****************************************************************************
*																			*
*		SYMBOL		: xspi_GetCondition										*
*																			*
*		DESCRIPTION	: XSPI通信ドライバ状態取得処理							*
*																			*
*		PARAMETER	: IN  :	ch		チャネルID								*
*						XSPI_CH_01	(0x00)	XSPIチャネルID：01（IVI向け）	*
*						XSPI_CH_02	(0x01)	XSPIチャネルID：02（METER向け）	*
*						XSPI_CH_03	(0x02)	XSPIチャネルID：03（CENTRAL向け）*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	uint8	ドライバ状態							*
*							XSPI_DCOND_INIT		(0x00)	初期化前			*
*							XSPI_DCOND_INVALID	(0x01)	通信無効（EN信号Low）*
*							XSPI_DCOND_IDLE		(0x02)	アイドル（EN信号High）*
*							XSPI_DCOND_TRANSMIT	(0x03)	送受信中			*
*																			*
****************************************************************************/
uint8	xspi_GetCondition(
	uint8 ch
)
{
	(VOID)ch;
	uint8	stat, cond;
	stat = bf_drv_SpiMng.stat;				/* ドライバ状態遷移取得 */

	switch (stat)
	{
	case CMDRV_STAT_INIT :					/* 初期化前 */
		cond = XSPI_DCOND_INIT;
		break;
	case CMDRV_STAT_INVALID :				/* 通信無効（EN信号Low状態） */
		cond = XSPI_DCOND_INVALID;
		break;
	case CMDRV_STAT_RETRY:					/* リトライ状態 */
	case CMDRV_STAT_IDLE :					/* アイドル状態（EN信号High状態） */
		cond = XSPI_DCOND_IDLE;				/* アイドル状態 */
		break;
	case CMDRV_STAT_COMM :					/* 送受信状態 */
		cond = XSPI_DCOND_TRANSMIT;
		break;

	default :
		bf_drv_SpiMng.stat = CMDRV_STAT_INIT;	/* 念の為、初期化前へ遷移 */
		cond = XSPI_DCOND_INIT;				/* 状態 ← 初期化前 */
		break;
	}

	return( cond );							/* ドライバ状態 */
}

/****************************************************************************
*																			*
*		SYMBOL		: xspi_Write											*
*																			*
*		DESCRIPTION	: 送信データ書き込み処理								*
*																			*
*		PARAMETER	: IN  :	ch		チャネルID								*
*						XSPI_CH_01	(0x00)	XSPIチャネルID：01（IVI向け）	*
*						XSPI_CH_02	(0x01)	XSPIチャネルID：02（METER向け）	*
*						XSPI_CH_03	(0x02)	XSPIチャネルID：03（CENTRAL向け）*
*																			*
*					  IN :	addr	書き込みデータアドレス					*
*					  IN  :	size	書き込みデータサイズ					*
*																			*
*					  RET :	result	書き込み結果							*
*						XSPI_NG	(0x00)	書き込み失敗 						*
*						XSPI_OK	(0x01)	書き込み成功 	 					*
*																			*
****************************************************************************/
uint8	xspi_Write(
	uint8 ch,	const uint8* addr,	uint32 size
)
{
	(VOID)ch;
	uint8 result = XSPI_NG;

	result = fc_drv_WriteBuf( addr, size );

	return( result );
}

/****************************************************************************
*																			*
*		SYMBOL		: xspi_Read												*
*																			*
*		DESCRIPTION	: 受信データ読み出し処理								*
*																			*
*		PARAMETER	: IN  :	ch		チャネルID								*
*						XSPI_CH_01	(0x00)	XSPIチャネルID：01（IVI向け）	*
*						XSPI_CH_02	(0x01)	XSPIチャネルID：02（METER向け）	*
*						XSPI_CH_03	(0x02)	XSPIチャネルID：03（CENTRAL向け）*
*																			*
*					  OUT :	addr	読み出しデータアドレス					*
*					  IN  :	size	読み出しデータサイズ					*
*																			*
*					  RET :	result	読み出し結果							*
*						XSPI_NG	(0x00)	読み出し失敗	 					*
*						XSPI_OK	(0x01)	読み出し成功	 	 				*
*																			*
****************************************************************************/
uint8	xspi_Read(
	uint8 ch,	uint8* addr,	uint32 size
)
{
	(VOID)ch;
	uint8 result = XSPI_NG;

	result = fc_drv_ReadBuf( addr, size );

	return( result );
}

/****************************************************************************
*																			*
*		SYMBOL		: xspi_Main												*
*																			*
*		DESCRIPTION	: XSPI通信メイン処理									*
*						(5mS周期で呼び出されること)							*
*																			*
*		PARAMETER	: IN  :	ch		チャネルID								*
*						XSPI_CH_01	(0x00)	XSPIチャネルID：01（IVI向け）	*
*						XSPI_CH_02	(0x01)	XSPIチャネルID：02（METER向け）	*
*						XSPI_CH_03	(0x02)	XSPIチャネルID：03（CENTRAL向け）*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	None											*
*																			*
****************************************************************************/
void	xspi_Main(
	uint8	ch
)
{
	(VOID)ch;
	uint8	event;			/* イベントNo. */
	uint8	stat;
	uint8	spi_stat;

	/* テーブル処理前の状態を保存 */
	stat = bf_drv_SpiMng.stat;
	event = fc_drv_ENSigCheck();			/* EN信号状態チェック */

	/* 現在の遷移状態のイベントをチェック */
	switch( stat )				/* ドライバ状態 */
	{

		case CMDRV_STAT_INIT :				/* 初期化前 */
		case CMDRV_STAT_INVALID :			/* 通信無効（EN信号Low状態） */
			bf_drv_ComTimeCount = 0U;
			break;

		case CMDRV_STAT_RETRY:				/* リトライ状態 */
		case CMDRV_STAT_IDLE :				/* アイドル状態（EN信号High状態） */
			/* EN信号がHighの場合は通信開始 */
			bf_drv_ComTimeCount = 0U;

			fc_drv_SpiClearErrInfoKind( XSPI_ERR_KIND_ENCHG );

			break;

		case CMDRV_STAT_COMM :				/* 送受信状態 */
			if( event == (uint8)CMDRV_EVT_NORMAL )
			{
				/* SPI通信状態の取得 */
				spi_stat = Spi_GetStatus( XSPI_COMC_ID );
				if( spi_stat == SPI_IDLE )
				{
					/* 通信終了 */
					event = CMDRV_EVT_COMEND;
				}
				else
				{
					bf_drv_ComTimeCount++;
					if( bf_drv_ComTimeCount < CMDRV_COM_TIMEOUT )
					{
						/* 通信継続 */
						event = CMDRV_EVT_N_NEXT;
					}
					else
					{
						/* 転送未完了タイムアウト */
						bf_drv_ComTimeCount = 0U;
						event = CMDRV_EVT_TIMEOUT;
						fc_drv_SpiSetErrInfoKind( XSPI_ERR_KIND_TIM );
#ifdef XSPI_DEBUG
						fc_drv_SpiSetDbgErrInfo( XSPI_ERR_DBG_SLAVETIM20 );
#endif	/* XSPI_DEBUG */
					}
				}
			}
			else
			{
				fc_drv_SpiSetErrInfoKind( XSPI_ERR_KIND_ENCHG );
				bf_drv_ComTimeCount = 0U;
			}
			break;

		default :							/* 状態に該当なし */
			bf_drv_SpiMng.stat = CMDRV_STAT_INIT;	/* 念の為、初期化前へ遷移 */
			stat = CMDRV_STAT_MAX;
			break;
	}

	if ( stat == (uint8)CMDRV_STAT_MAX )
	{
		return;		/* 何もしない */
	}

	/* 処理テーブル内の該当状態・イベントの関数／状態を実施 */
	(VOID)fs_tbl_Excute( event );

}

/****************************************************************************
*																			*
*		SYMBOL		: xspi_GetErrInfo										*
*																			*
*		DESCRIPTION	: XSPI通信ドライバエラー情報取得処理					*
*																			*
*		PARAMETER	: IN  :	ch		チャネルID								*
*						XSPI_CH_01	(0x00)	XSPIチャネルID：01（IVI向け）	*
*						XSPI_CH_02	(0x01)	XSPIチャネルID：02（METER向け）	*
*						XSPI_CH_03	(0x02)	XSPIチャネルID：03（CENTRAL向け）*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	uint8											*
*						XSPI_ERR_KIND_NONE	(0x00)	エラー無し 				*
*						XSPI_ERR_KIND_TRX	(0x01)	送受信エラー 			*
*						XSPI_ERR_KIND_INTG	(0x02)	データ整合性エラー		*
*						XSPI_ERR_KIND_ENCHG	(0x40)	EN信号変化 				*
*						XSPI_ERR_KIND_TIM	(0x80)	通信時間オーバ 			*
*																			*
****************************************************************************/
uint8	xspi_GetErrInfo(
	uint8	ch
)
{
	(VOID)ch;
	return( bf_drv_SpiMng.err_info );
}

/****************************************************************************/
/**************			ドライバ内部処理（状態遷移関連）		*************/
/****************************************************************************/

/****************************************************************************
*																			*
*		SYMBOL		: fs_tbl_Excute											*
*																			*
*		DESCRIPTION	: 処理テーブル内の該当状態・イベントの関数／状態を実施	*
*																			*
*		PARAMETER	: IN  :													*
*							uint8	event		イベントNo.					*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :													*
*							uint8	実施後の遷移状態						*
*																			*
****************************************************************************/
static uint8	fs_tbl_Excute(
	uint8	event					/* イベントNo. */
)
{
	uint8	stat;

	/* テーブル処理前の状態を保存 */
	stat = bf_drv_SpiMng.stat;

	/* 処理テーブル内の該当状態・イベントの関数アドレス有無チェック */
	if( tb_drv_SpiDrvJmp[stat][event].func != NULL_PTR )
	{	/* 処理テーブル内の該当状態・イベントの関数アドレスあり */
		/* 該当する処理関数呼び出し */
		tb_drv_SpiDrvJmp[stat][event].func();
	}
	/* 処理テーブル内の該当状態・イベントの次の状態有無チェック */
	if( tb_drv_SpiDrvJmp[stat][event].next_stat != 0U )
	{	/* 処理テーブル内の該当状態・イベントの次の状態あり */
		/* 該当する次の状態をセット */
		bf_drv_SpiMng.stat = tb_drv_SpiDrvJmp[stat][event].next_stat;
	}

	/* OSTM停止 */
	vd_g_Gpt_OstStop( XSPI_OST_CH );

	if( tb_drv_SpiDrvJmp[stat][event].ostm_cnt != 0UL )
	{
		/* OSTM割り込みのカウンタ値をセット */
		bf_drv_OST_START[GPT_OST_START_PERIOD] = tb_drv_SpiDrvJmp[stat][event].ostm_cnt;
	}
	else
	{
		/* OSTM割り込みのカウンタ値を10msでセット（通常の状態遷移では起こりえない） */
		bf_drv_OST_START[GPT_OST_START_PERIOD] = XSPI_OST_CNT_10ms;
	}

	/* OSTM起動 */
	vd_g_Gpt_OstStart( XSPI_OST_CH, bf_drv_OST_START );

	return( bf_drv_SpiMng.stat );
}


/****************************************************************************
*																			*
*		SYMBOL		: fc_SpiInit											*
*																			*
*		DESCRIPTION	: ドライバ初期化										*
*																			*
*		PARAMETER	: IN  :	None											*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	None											*
*																			*
****************************************************************************/
static void	fc_SpiInit(
	void
)
{
	/* Frame 信号High出力 */
	PDR_SPI_FRM_WR( STD_HIGH );
}

/****************************************************************************
*																			*
*		SYMBOL		: fc_SpiStartPrepare									*
*																			*
*		DESCRIPTION	: 送受信開始準備										*
*																			*
*		PARAMETER	: IN  :	None											*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	None											*
*																			*
****************************************************************************/
static void	fc_SpiStartPrepare(
	void
)
{
	uint8	spage, rpage;
	uint8	*rcv_buf, *snd_buf;

	/* バッファページ切り替え */
	rpage = fc_drv_getRcvBufPage();
	spage = fc_drv_getSndBufPage();

	/* バッファアドレス取得 */
	rcv_buf = (uint8 *)&bf_drv_SpiMng.rcv.page[rpage].dat[0];
	snd_buf = (uint8 *)&bf_drv_SpiMng.snd.page[spage].dat[0];

#ifdef XSPI_DEBUG
	/* 暫定対応 初回データスキップ */
	if( bf_drv_skip_first_data == XSPI_OK )
	{
		/* Frame Header未使用領域(Byte0)にデバッグ用エラー情報をセット */
		snd_buf[0] = bf_drv_Dbg_ErrInfo;
	}
#endif	/* XSPI_DEBUG */

	/* 整合性データ付与 */
#if (XSPI_DATA_CHECK != XSPI_DATA_CHECK_NONE)
	fc_drv_AddIntegrityData(snd_buf);
#endif	/* XSPI_DATA_CHECK */

	bf_drv_ComTimeCount = 1U;	/* 呼び出し回数カウント開始 */

	/* 暫定対応 初回データスキップ */
	if( bf_drv_skip_first_data == XSPI_NG )
	{
		/* ダミーデータ送信 */
		Spi_AsyncTransmit( XSPI_COMC_ID, (const Spi_ModeC_DataType *)&bf_drv_dummy_snddata, (const Spi_ModeC_DataType *)&bf_drv_dummy_rcvdata, 1U );
	}
	else
	{
		/* SPI非同期通信開始 */
		Spi_AsyncTransmit( XSPI_COMC_ID, (const Spi_ModeC_DataType *)snd_buf, (const Spi_ModeC_DataType *)rcv_buf,(U2)XSPI_FRM_MAX / 4  );
	}

	/* Frame信号をLow出力 */
	PDR_SPI_FRM_WR( STD_LOW );

}

/****************************************************************************
*																			*
*		SYMBOL		: fc_SpiEnd												*
*																			*
*		DESCRIPTION	: 送受信終了											*
*																			*
*		PARAMETER	: IN  :	None											*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	None											*
*																			*
****************************************************************************/
static void	fc_SpiEnd(
	void
)
{
	sint32 err;

	fc_drv_SpiClearErrInfoKind( XSPI_ERR_KIND_TIM );

	/* オーバーランエラー状態チェック */
	err = Spi_GetOvrunErrStatus( XSPI_COMC_ID );
	if( err != 0 )
	{
		fc_drv_SpiSetErrInfoKind( XSPI_ERR_KIND_TRX );
#ifdef XSPI_DEBUG
		fc_drv_SpiSetDbgErrInfo( XSPI_ERR_DBG_DMAOVERRUN );
#endif	/* XSPI_DEBUG */
	}
	else {
		fc_drv_SpiClearErrInfoKind( XSPI_ERR_KIND_TRX );

#if (XSPI_DATA_BUFFER != XSPI_DATA_BUFFER_DOUBLE)
		/* 送受信バッファページ更新 */
		fc_drv_SpiRcvDpageRenew();
		fc_drv_SpiSendDpageRenew();
#endif	/* XSPI_DATA_BUFFER */

#ifdef XSPI_DEBUG
		/* 暫定対応 初回データスキップ */
		if( bf_drv_skip_first_data == XSPI_NG )
		{
			bf_drv_Dbg_ErrInfo = 0U;
		}
#endif	/* XSPI_DEBUG */

		/* 暫定対応 初回データスキップ */
		bf_drv_skip_first_data = XSPI_OK;
	}

	/* Frame信号をHigh出力 */
	PDR_SPI_FRM_WR( STD_HIGH );

}


/****************************************************************************
*																			*
*		SYMBOL		: fc_SpiAbort											*
*																			*
*		DESCRIPTION	: 送受信ドライバ中断									*
*																			*
*		PARAMETER	: IN  :	None											*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	None											*
*																			*
****************************************************************************/
static void	fc_SpiAbort(
	void
)
{
	/* SPI非同期通信中断 */
	Spi_CancelAsyncTransmit( XSPI_COMC_ID );

	PDR_SPI_FRM_WR( STD_HIGH );	/* Frame 信号High出力 */

}


/****************************************************************************
*																			*
*		SYMBOL		: fc_SpiStop											*
*																			*
*		DESCRIPTION	: 送受信ドライバ停止									*
*																			*
*		PARAMETER	: IN  :	None											*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	None											*
*																			*
****************************************************************************/
static void	fc_SpiStop(
	void
)
{
	/* SPI非同期通信中断 */
	Spi_CancelAsyncTransmit( XSPI_COMC_ID );

#if (XSPI_DATA_BUFFER != XSPI_DATA_BUFFER_DOUBLE)
	fc_drv_SpiSendDpageRenew();	/* ドライバ用送信バッファページ更新 */
#endif	/* XSPI_DATA_BUFFER */

	PDR_SPI_FRM_WR( STD_HIGH );	/* Frame 信号High出力 */
}

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_ENSigCheck										*
*																			*
*		DESCRIPTION	: EN信号状態チェック									*
*																			*
*		PARAMETER	: IN  :	None											*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :													*
*							uint8	イベントNo.								*
*								CMDRV_EVT_NORMAL (1)	EN信号変化なし		*
*								CMDRV_EVT_ENHIGH (2)	EN信号Highへ変化	*
*								CMDRV_EVT_ENLOW  (3)	EN信号Lowへ変化		*
*																			*
****************************************************************************/
uint8	fc_drv_ENSigCheck(
	void
)
{
	uint8 en_now;

	/* 現在の EN信号状態を外部ポートから取得 */
	en_now = (uint8)PDR_SPI_EN();

	if( bf_drv_EnSignal != en_now )
	{	/* EN信号状態変化 */
		bf_drv_EnSignal = en_now;		/* EN信号状態更新 */

		if( bf_drv_EnSignal == STD_HIGH )
		{	/* EN High */
			/* 処理テーブル内の該当状態・イベントの関数／状態を実施 */
			return( CMDRV_EVT_ENHIGH );	/* EN信号High検知イベント */
		}
		else
		{	/* EN Low */
			/* 処理テーブル内の該当状態・イベントの関数／状態を実施 */
			return( CMDRV_EVT_ENLOW );	/* EN信号Low検知イベント */
		}
	}

	return( CMDRV_EVT_NORMAL );			/* 変化なし */
}
