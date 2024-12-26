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
static uint8	bf_drv_EnSignal_meter;		/* EN信号状態 */
static uint8	bf_drv_ComTimeCount_meter;	/* 通信中M-SPIドライバ定周期(5ms)呼び出し回数カウンタ */
static uint32	bf_drv_DMA_Cnt_meter;			/* DMA転送カウント */

static uint8 	bf_drv_skip_first_data_meter = XSPI_NG;		/* [T.B.D]暫定対応 初回データスキップ */
static uint32 	bf_drv_dummy_rcvdata_meter = 0x00000000UL;	/* [T.B.D]暫定対応 初回データスキップ */
static uint32 	bf_drv_dummy_snddata_meter = 0x00000000UL;	/* [T.B.D]暫定対応 初回データスキップ */

extern BF_DRV_SPI_DOUBLE	bf_drv_SpiMng_meter;		/* XSPI管理情報 */

#ifdef XSPI_DEBUG
extern uint8	bf_drv_Dbg_ErrInfo_meter;		/* デバッグ用エラー情報 */
#endif	/* XSPI_DEBUG */

/****************************
*		prototype			*
****************************/
static uint8	fs_tbl_Excute_meter( uint8 event );						/* 処理テーブル内の該当状態・イベントの関数／状態を実施 */
static void		fc_SpiInit_meter( void );									/* ドライバ初期化 */
static void		fc_SpiStartPrepare_meter( void );							/* 送受信開始準備 */
static void		fc_SpiEnd_meter( void );									/* 送受信終了 */
static void		fc_SpiAbort_meter( void );								/* 送受信ドライバ中断 */
static void		fc_SpiStop_meter( void );									/* 送受信ドライバ停止 */

static uint8	fc_drv_ENSigCheck_meter( void );							/* EN信号状態チェック */
static uint8	fc_drv_Spi_SubEvent_5ms_meter( void );					/* XSPIメインサブイベント処理(5ms経過時) */
static uint8	fc_drv_Spi_SubEvent_10ms_meter( void );					/* XSPIメインサブイベント処理(10ms経過時) */
static uint8	fc_drv_Spi_SubEvent_15ms_meter( void );					/* XSPIメインサブイベント処理(15ms経過時) */
static uint8	fc_drv_Spi_SubEvent_20ms_meter( void );					/* XSPIメインサブイベント処理(20ms経過時) */

extern void		fc_drv_ClearXSpiMng_meter( void );						/* XSPI管理情報初期化 */
extern void		fc_drv_SpiSetErrInfoKind_meter( uint8 kind );				/* エラー種別情報設定 */
extern void		fc_drv_SpiClearErrInfoKind_meter( uint8 kind );			/* エラー種別情報クリア */
#ifdef XSPI_DEBUG
extern void		fc_drv_SpiSetDbgErrInfo_meter( uint8 err_info );			/* デバッグ用エラー情報設定 */
#endif	/* XSPI_DEBUG */

extern uint8	fc_drv_getRcvBufPage_meter( void );						/* 受信バッファページ取得 */
extern uint8	fc_drv_getSndBufPage_meter( void );						/* 送信バッファページ取得 */
extern uint8	fc_drv_ReadBuf_meter( uint8* p_addr, uint32 size );		/* 受信データ読み出し */
extern uint8	fc_drv_WriteBuf_meter( const uint8* p_addr, uint32 size );/* 送信データ書き込み */

#if (XSPI_DATA_CHECK_meter != XSPI_DATA_CHECK_NONE)
extern uint8	fc_drv_CheckIntegrityData_meter( const uint8* p_frame );	/* 整合性データチェック */
extern void		fc_drv_AddIntegrityData_meter( uint8* p_frame );			/* 整合性データ付加 */
#endif	/* XSPI_DATA_CHECK_meter */

/********************************
*		table					*
********************************/
static const TBL_DRV_SPI	tb_drv_SpiDrvJmp_meter[CMDRV_STAT_MAX][CMDRV_EVT_MAX] = {
/* 状態 */
/* 0: 初期化前 */
	{													/* Event */
		{ 0,					0 },					/* 0：初期化 */
		{ 0,					0 },					/* 1：定周期(5mS)通常動作 */
		{ 0,					0 },					/* 2：定周期(5mS)通信継続 */
		{ 0,					0 },					/* 3：転送未完了タイムアウト */
		{ fc_SpiInit_meter,			CMDRV_STAT_IDLE },		/* 4：EN信号High */
		{ 0,					0 },					/* 5：EN信号Low */
		{ 0,					0 },					/* 6：通信終了(5ms未満) */
		{ 0,					0 },					/* 7：通信終了(10ms以上) */
	},
/* 1: 通信無効（EN信号Low） */
	{													/* Event */
		{ 0,					0 },					/* 0：初期化 */
		{ 0,					0 },					/* 1：定周期(5mS)通常動作 */
		{ 0,					0 },					/* 2：定周期(5mS)通信継続 */
		{ 0,					0 },					/* 3：転送未完了タイムアウト */
		{ fc_SpiInit_meter,			CMDRV_STAT_IDLE },		/* 4：EN信号High */
		{ 0,					0 },					/* 5：EN信号Low */
		{ 0,					0 },					/* 6：通信終了(5ms未満) */
		{ 0,					0 },					/* 7：通信終了(10ms以上) */
	},
/* 2: アイドル状態（EN信号High） */
	{													/* Event */
		{ 0,					0 },					/* 0：初期化 */
		{ fc_SpiStartPrepare_meter,	CMDRV_STAT_COMM },		/* 1：定周期(5mS)通常動作 */
		{ 0,					0 },					/* 2：定周期(5mS)通信継続 */
		{ 0,					0 },					/* 3：転送未完了タイムアウト */
		{ 0,					0 },					/* 4：EN信号High */
		{ fc_SpiStop_meter,			CMDRV_STAT_INVALID },	/* 5：EN信号Low */
		{ 0,					0 },					/* 6：通信終了(5ms未満) */
		{ 0,					0 },					/* 7：通信終了(10ms以上) */
	},
/* 3: 送受信状態 */
	{													/* Event */
		{ 0,					0 },					/* 0：初期化 */
		{ 0,					0 },					/* 1：定周期(5mS)通常動作 */
		{ 0,					0 },					/* 2：定周期(5mS)通信継続 */
		{ fc_SpiAbort_meter,			CMDRV_STAT_RETRY },		/* 3：転送未完了タイムアウト */
		{ 0,					0 },					/* 4：EN信号High */
		{ fc_SpiStop_meter,			CMDRV_STAT_INVALID },	/* 5：EN信号Low */
		{ fc_SpiEnd_meter,			CMDRV_STAT_IDLE },		/* 6：通信終了(5ms未満) */
		{ fc_SpiEnd_meter,			CMDRV_STAT_COMM },		/* 7：通信終了(10ms以上) */
	},
/* 4: リトライ状態(アイドル) */
	{													/* Event */
		{ 0,					0 },					/* 0：初期化 */
		{ fc_SpiStartPrepare_meter,	CMDRV_STAT_COMM },		/* 1：定周期(5mS)通常動作 */
		{ 0,					0 },					/* 2：定周期(5mS)通信継続 */
		{ 0,					0 },					/* 3：転送未完了タイムアウト */
		{ 0,					0 },					/* 4：EN信号High */
		{ fc_SpiStop_meter,			CMDRV_STAT_INVALID },	/* 5：EN信号Low */
		{ fc_SpiEnd_meter,			CMDRV_STAT_IDLE },		/* 6：通信終了(5ms未満) */
		{ fc_SpiEnd_meter,			CMDRV_STAT_COMM },		/* 7：通信終了(10ms以上) */
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
static void	PDR_SPI_FRM_WR_meter ( uint32 level )
{
	Dio_WriteChannel( XSPI_FRM_PORT_meter, level);
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
static uint8	PDR_SPI_EN_meter ( void )
{
	return ( Dio_ReadChannel( XSPI_EN_PORT_meter ) );
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
void	xspi_Init_meter(
	uint8	ch
)
{
	(VOID)ch;
	/* SPIポート設定 */
	Port_SetPinMode( XSPI_SCLK_PORT_meter, XSPI_SCLK_MODE_CFG_meter );
	Port_SetPinMode( XSPI_TXD_PORT_meter, XSPI_TXD_MODE_CFG_meter );
	Port_SetPinMode( XSPI_RXD_PORT_meter, XSPI_RXD_MODE_CFG_meter );

	/* XSPI管理情報初期化 */
	fc_drv_ClearXSpiMng_meter();

	/* EN信号状態初期化 */
	bf_drv_EnSignal_meter = 0U;

	/* 通信中M-SPIドライバ定周期(5mS)呼び出し回数カウンタ初期化 */
	bf_drv_ComTimeCount_meter = 0U;

	/* DMA転送カウントを初期化 */
	bf_drv_DMA_Cnt_meter = 0UL;

	/* Frame信号をHigh出力 */
	PDR_SPI_FRM_WR_meter( STD_HIGH );

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
void	xspi_DeInit_meter(
	uint8	ch
)
{
	(VOID)ch;

	/* SPI非同期通信中断 */
	Spi_CancelAsyncTransmit( XSPI_COMC_ID_meter );

	/* XSPI管理情報初期化 */
	fc_drv_ClearXSpiMng_meter();

	/* EN信号状態初期化 */
	bf_drv_EnSignal_meter = 0U;

	/* 通信中M-SPIドライバ定周期(5mS)呼び出し回数カウンタ初期化 */
	bf_drv_ComTimeCount_meter = 0U;

	/* DMA転送カウントを初期化 */
	bf_drv_DMA_Cnt_meter = 0UL;

	/* Frame信号をHigh出力 */
	PDR_SPI_FRM_WR_meter( STD_HIGH );

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
uint8	xspi_GetCondition_meter(
	uint8 ch
)
{
	(VOID)ch;
	uint8	stat, cond;
	stat = bf_drv_SpiMng_meter.stat;				/* ドライバ状態遷移取得 */

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
		bf_drv_SpiMng_meter.stat = CMDRV_STAT_INIT;	/* 念の為、初期化前へ遷移 */
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
uint8	xspi_Write_meter(
	uint8 ch,	const uint8* addr,	uint32 size
)
{
	(VOID)ch;
	uint8 result = XSPI_NG;

	result = fc_drv_WriteBuf_meter( addr, size );

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
uint8	xspi_Read_meter(
	uint8 ch,	uint8* addr,	uint32 size
)
{
	(VOID)ch;
	uint8 result = XSPI_NG;

	result = fc_drv_ReadBuf_meter( addr, size );

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
void	xspi_Main_meter(
	uint8	ch
)
{
	(VOID)ch;
	uint8	event;			/* イベントNo. */
	uint8	stat;

	/* テーブル処理前の状態を保存 */
	stat = bf_drv_SpiMng_meter.stat;
	event = fc_drv_ENSigCheck_meter();			/* EN信号状態チェック */

	/* 現在の遷移状態のイベントをチェック */
	switch( stat )				/* ドライバ状態 */
	{

		case CMDRV_STAT_INIT :				/* 初期化前 */
		case CMDRV_STAT_INVALID :			/* 通信無効（EN信号Low状態） */
			bf_drv_ComTimeCount_meter = 0U;
			break;

		case CMDRV_STAT_RETRY:				/* リトライ状態 */
		case CMDRV_STAT_IDLE :				/* アイドル状態（EN信号High状態） */
			/* EN信号がHighの場合は通信開始 */
			bf_drv_ComTimeCount_meter = 0U;

			fc_drv_SpiClearErrInfoKind_meter( XSPI_ERR_KIND_ENCHG );

			break;

		case CMDRV_STAT_COMM :				/* 送受信状態 */
			if( event == (uint8)CMDRV_EVT_NORMAL )
			{
				switch( bf_drv_ComTimeCount_meter )
				{
				case	CMDRV_COM_TIME_1	:		/* 定周期(5mS)回数カウント 通信中１ */
					event = fc_drv_Spi_SubEvent_5ms_meter();
					break;
				case	CMDRV_COM_TIME_2	:		/* 定周期(5mS)回数カウント 通信中２ */
					event = fc_drv_Spi_SubEvent_10ms_meter();
					break;
				case	CMDRV_COM_TIME_x	:		/* 定周期(5mS)回数カウント 通信中３ */
					event = fc_drv_Spi_SubEvent_15ms_meter();
					break;
				case	CMDRV_COM_TIMEOUT	:		/* 定周期(5mS)回数カウント 通信中最大値 */
					event = fc_drv_Spi_SubEvent_20ms_meter();
					break;
				default:
					bf_drv_ComTimeCount_meter = 0U;
					break;
				}
			}
			else
			{
				fc_drv_SpiSetErrInfoKind_meter( XSPI_ERR_KIND_ENCHG );
				bf_drv_ComTimeCount_meter = 0U;
			}
			break;

		default :							/* 状態に該当なし */
			bf_drv_SpiMng_meter.stat = CMDRV_STAT_INIT;	/* 念の為、初期化前へ遷移 */
			stat = CMDRV_STAT_MAX;
			break;
	}

	if ( stat == (uint8)CMDRV_STAT_MAX )
	{
		return;		/* 何もしない */
	}

	/* 処理テーブル内の該当状態・イベントの関数／状態を実施 */
	(VOID)fs_tbl_Excute_meter( event );

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
uint8	xspi_GetErrInfo_meter(
	uint8	ch
)
{
	(VOID)ch;
	return( bf_drv_SpiMng_meter.err_info );
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
static uint8	fs_tbl_Excute_meter(
	uint8	event					/* イベントNo. */
)
{
	uint8	stat;

	/* テーブル処理前の状態を保存 */
	stat = bf_drv_SpiMng_meter.stat;

	/* 処理テーブル内の該当状態・イベントの関数アドレス有無チェック */
	if( tb_drv_SpiDrvJmp_meter[stat][event].func != NULL_PTR )
	{	/* 処理テーブル内の該当状態・イベントの関数アドレスあり */
		/* 該当する処理関数呼び出し */
		tb_drv_SpiDrvJmp_meter[stat][event].func();
	}
	/* 処理テーブル内の該当状態・イベントの次の状態有無チェック */
	if( tb_drv_SpiDrvJmp_meter[stat][event].next_stat != 0U )
	{	/* 処理テーブル内の該当状態・イベントの次の状態あり */
		/* 該当する次の状態をセット */
		bf_drv_SpiMng_meter.stat = tb_drv_SpiDrvJmp_meter[stat][event].next_stat;
	}
	return( bf_drv_SpiMng_meter.stat );
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
static void	fc_SpiInit_meter(
	void
)
{
	/* Frame 信号High出力 */
	PDR_SPI_FRM_WR_meter( STD_HIGH );
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
static void	fc_SpiStartPrepare_meter(
	void
)
{
	uint8	spage, rpage;
	uint8	*rcv_buf, *snd_buf;

	/* バッファページ切り替え */
	rpage = fc_drv_getRcvBufPage_meter();
	spage = fc_drv_getSndBufPage_meter();

	/* バッファアドレス取得 */
	rcv_buf = (uint8 *)&bf_drv_SpiMng_meter.rcv.page[rpage].dat[0];
	snd_buf = (uint8 *)&bf_drv_SpiMng_meter.snd.page[spage].dat[0];

#ifdef XSPI_DEBUG
	/* [T.B.D]暫定対応 初回データスキップ */
	if( bf_drv_skip_first_data_meter == XSPI_OK )
	{
		/* Frame Header未使用領域(Byte0)にデバッグ用エラー情報をセット */
		snd_buf[0] = bf_drv_Dbg_ErrInfo_meter;
	}
#endif	/* XSPI_DEBUG */

	/* 整合性データ付与 */
#if (XSPI_DATA_CHECK_meter != XSPI_DATA_CHECK_NONE)
	fc_drv_AddIntegrityData_meter(snd_buf);
#endif	/* XSPI_DATA_CHECK_meter */

	bf_drv_ComTimeCount_meter = 1U;	/* 呼び出し回数カウント開始 */

	/* [T.B.D]暫定対応 初回データスキップ */
	if( bf_drv_skip_first_data_meter == XSPI_NG )
	{
		/* ダミーデータ送信 */
		Spi_AsyncTransmit( XSPI_COMC_ID_meter, (const Spi_ModeC_DataType *)&bf_drv_dummy_snddata_meter, (const Spi_ModeC_DataType *)&bf_drv_dummy_rcvdata_meter, sizeof(uint32) );
	}
	else
	{
		/* SPI非同期通信開始 */
		Spi_AsyncTransmit( XSPI_COMC_ID_meter, (const Spi_ModeC_DataType *)snd_buf, (const Spi_ModeC_DataType *)rcv_buf,(U2)XSPI_FRM_MAX );
	}

	/* Frame信号をLow出力 */
	PDR_SPI_FRM_WR_meter( STD_LOW );

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
static void	fc_SpiEnd_meter(
	void
)
{
	sint32 err;

	fc_drv_SpiClearErrInfoKind_meter( XSPI_ERR_KIND_TIM );

	/* オーバーランエラー状態チェック */
	err = Spi_GetOvrunErrStatus( XSPI_COMC_ID_meter );
	if( err != 0 )
	{
		fc_drv_SpiSetErrInfoKind_meter( XSPI_ERR_KIND_TRX );
#ifdef XSPI_DEBUG
		fc_drv_SpiSetDbgErrInfo_meter( XSPI_ERR_DBG_DMAOVERRUN );
#endif	/* XSPI_DEBUG */
	}
	else {
		fc_drv_SpiClearErrInfoKind_meter( XSPI_ERR_KIND_TRX );

#ifdef XSPI_DEBUG
		/* [T.B.D]暫定対応 初回データスキップ */
		if( bf_drv_skip_first_data_meter == XSPI_NG )
		{
			bf_drv_Dbg_ErrInfo_meter = 0U;
		}
#endif	/* XSPI_DEBUG */

		/* [T.B.D]暫定対応 初回データスキップ */
		bf_drv_skip_first_data_meter = XSPI_OK;
	}

	/* 経過時間チェック(通信開始から10ms以上経過している場合) */
	if(bf_drv_ComTimeCount_meter > CMDRV_COM_TIME_1 ){
		/* 送受信開始準備 */
		fc_SpiStartPrepare_meter();
	}
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
static void	fc_SpiAbort_meter(
	void
)
{
	/* SPI非同期通信中断 */
	Spi_CancelAsyncTransmit( XSPI_COMC_ID_meter );

	PDR_SPI_FRM_WR_meter( STD_HIGH );	/* Frame 信号High出力 */

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
static void	fc_SpiStop_meter(
	void
)
{
	/* SPI非同期通信中断 */
	Spi_CancelAsyncTransmit( XSPI_COMC_ID_meter );

	PDR_SPI_FRM_WR_meter( STD_HIGH );	/* Frame 信号High出力 */
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
uint8	fc_drv_ENSigCheck_meter(
	void
)
{
	uint8 en_now;

	/* 現在の EN信号状態を外部ポートから取得 */
	en_now = (uint8)PDR_SPI_EN_meter();

	if( bf_drv_EnSignal_meter != en_now )
	{	/* EN信号状態変化 */
		bf_drv_EnSignal_meter = en_now;		/* EN信号状態更新 */

		if( bf_drv_EnSignal_meter == STD_HIGH )
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

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_Spi_SubEvent_5ms								*
*																			*
*		DESCRIPTION	: XSPIメインサブイベント処理(5ms経過時)					*
*																			*
*		PARAMETER	: IN  :	None											*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	uint8	イベントNo								*
*																			*
****************************************************************************/
static uint8	fc_drv_Spi_SubEvent_5ms_meter(
	void
)
{
	uint8 spi_stat;
	uint8 event;

	/* Frame信号をHigh出力 */
	PDR_SPI_FRM_WR_meter( STD_HIGH );

	/* SPI通信状態の取得 */
	spi_stat = Spi_GetStatus( XSPI_COMC_ID_meter );
	if ( spi_stat == SPI_IDLE )
	{
		/* 通信終了 */
		event = CMDRV_EVT_COMEND;
	}
	else
	{
		/* 通信継続 */
		bf_drv_ComTimeCount_meter++;
		event = CMDRV_EVT_N_NEXT;
	}

	return( event );
}

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_Spi_SubEvent_10ms								*
*																			*
*		DESCRIPTION	: XSPIメインサブイベント処理(10ms経過時)				*
*																			*
*		PARAMETER	: IN  :	None											*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	uint8	イベントNo								*
*																			*
****************************************************************************/
static uint8	fc_drv_Spi_SubEvent_10ms_meter(
	void
)
{
	const Spi_ModeC_ChannelConfigType* t_pcstChannelConfig = &cstSpi_UcfgModeCData.pstChannelConfig[XSPI_COMC_ID_meter];
	uint8 spi_stat;
	uint8 event;

	/* SPI通信状態チェック */
	spi_stat = Spi_GetStatus( XSPI_COMC_ID_meter );
	if ( spi_stat == SPI_IDLE )
	{	/* 通信終了 */
		event = CMDRV_EVT_COMEND_10ms;
	}
	else
	{
		/* ＤＭＡ転送中のカウント値を取得 */
		bf_drv_DMA_Cnt_meter = Dma_GetTransCount( t_pcstChannelConfig->u1DmaRxChannel );

		/* 通信継続 */
		bf_drv_ComTimeCount_meter++;
		event = CMDRV_EVT_N_NEXT;
	}

	return( event );
}

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_Spi_SubEvent_15ms								*
*																			*
*		DESCRIPTION	: XSPIメインサブイベント処理(15ms経過時)				*
*																			*
*		PARAMETER	: IN  :	None											*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	uint8	イベントNo								*
*																			*
****************************************************************************/
static uint8	fc_drv_Spi_SubEvent_15ms_meter(
	void
)
{
	const Spi_ModeC_ChannelConfigType* t_pcstChannelConfig = &cstSpi_UcfgModeCData.pstChannelConfig[XSPI_COMC_ID_meter];
	uint16 DTC;
	uint8 spi_stat;
	uint8 event;

	/* DMA転送カウントチェック(転送カウントに減少あり) */
	DTC = Dma_GetTransCount( t_pcstChannelConfig->u1DmaRxChannel );
	if( ( DTC < bf_drv_DMA_Cnt_meter ) )
	{	/* 前回のカウント値よりカウントダウン */

		/* SPI通信状態チェック */
		spi_stat = Spi_GetStatus( XSPI_COMC_ID_meter );
		if ( spi_stat == SPI_IDLE )
		{	/* 通信終了 */
			event = CMDRV_EVT_COMEND_10ms;
		}
		else
		{	/* 通信継続 */
			bf_drv_ComTimeCount_meter++;
			event = CMDRV_EVT_N_NEXT;
		}
	}
	else
	{	/* 前回のカウント値に変化なし */
		bf_drv_ComTimeCount_meter = 0U;
		event = CMDRV_EVT_TIMEOUT;
		fc_drv_SpiSetErrInfoKind_meter( XSPI_ERR_KIND_TIM );
#ifdef XSPI_DEBUG
		fc_drv_SpiSetDbgErrInfo_meter( XSPI_ERR_DBG_SLAVETIM15 );
#endif	/* XSPI_DEBUG */
	}

	return( event );
}

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_Spi_SubEvent_20ms								*
*																			*
*		DESCRIPTION	: XSPIメインサブイベント処理(20ms経過時)				*
*																			*
*		PARAMETER	: IN  :	None											*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	uint8	イベントNo								*
*																			*
****************************************************************************/
static uint8	fc_drv_Spi_SubEvent_20ms_meter(
	void
)
{
	uint8 spi_stat;
	uint8 event;

	/* SPI通信状態チェック */
	spi_stat = Spi_GetStatus( XSPI_COMC_ID_meter );
	if ( spi_stat == SPI_IDLE )
	{	/* 通信終了 */
		event = CMDRV_EVT_COMEND_10ms;
	}
	else
	{	/* 転送未完了タイムアウト */
		bf_drv_ComTimeCount_meter = 0U;
		event = CMDRV_EVT_TIMEOUT;
		fc_drv_SpiSetErrInfoKind_meter( XSPI_ERR_KIND_TIM );
#ifdef XSPI_DEBUG
		fc_drv_SpiSetDbgErrInfo_meter( XSPI_ERR_DBG_SLAVETIM20 );
#endif	/* XSPI_DEBUG */
	}

	return( event );
}
