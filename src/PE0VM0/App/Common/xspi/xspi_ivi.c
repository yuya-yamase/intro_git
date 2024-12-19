/****************************************************************************/
/*【ファイル名】xspi.c                                                 */
/*【モジュール名】XSPIドライバ			                                	*/
/****************************************************************************/
/****************************
*		include	files		*
****************************/
#include "Rte_BswUcfg.h"
#include "Port.h"
#include "Spi.h"
#include "Dma.h"
#include "Dio.h"
#include "xspi.h"
#include "xspi_internal.h"

/************************************************************************
*																		*
*				Ｄefine Ｄeclare Ｓection								*
*																		*
************************************************************************/
/*------------------------------------------*/
/*	MCAL関連								*/
/*------------------------------------------*/
#define	XSPI_COMC_ID_ivi 		(SPI_COMC_ID_SOC_MCU2)		/* COM ID（MCAL/SPI）*/
#define XSPI_EN_PORT_ivi 		(DIO_ID_PORT4_CH1)			/* EN端子ポート（MCAL/DIO）*/
#define XSPI_FRM_PORT_ivi 		(DIO_ID_PORT10_CH12)		/* Frame端子ポート（MCAL/DIO）*/
#define XSPI_SCLK_PORT_ivi 		(PORT_ID_PORT24_PIN10)		/* SCLKポート（MCAL/PORT） */
#define XSPI_TXD_PORT_ivi 		(PORT_ID_PORT24_PIN12) 		/* TXDポート（MCAL/PORT） */
#define XSPI_RXD_PORT_ivi 		(PORT_ID_PORT24_PIN13)		/* RXDポート（MCAL/PORT） */
#define XSPI_SCLK_MODE_CFG_ivi 	(PORT_MODE_CFG_P24_10_17)	/* SCLKポート設定値（MCAL/PORT） */
#define XSPI_TXD_MODE_CFG_ivi 	(PORT_MODE_CFG_P24_12_18)	/* TXDポート設定値（MCAL/PORT） */
#define XSPI_RXD_MODE_CFG_ivi 	(PORT_MODE_CFG_P24_13_19)	/* RXDポート設定値（MCAL/PORT） */

/****************************
*		buffers				*
****************************/
#define APP_COMMON_START_SEC_CRAM0_BSS
#include "APP_COMMON_Memmap.h"
BF_DRV_SPI		bf_drv_SpiMng_ivi;
#define APP_COMMON_STOP_SEC_CRAM0_BSS
#include "APP_COMMON_Memmap.h"

static uint8	bf_drv_EnSignal_ivi;		/* EN信号状態 */
static uint8	bf_drv_ComTimeCount_ivi;	/* 通信中M-SPIドライバ定周期(5ms)呼び出し回数カウンタ */
static uint32	bf_drv_DMA_Cnt_ivi;
static uint8	bf_drv_Dbg_ErrInfo_ivi;		/* デバッグ用エラー情報 */

#if 1 /* [★XSPI暫定対応(T.B.D)]初回データダミー対応 */
static uint8 	bf_drv_dummy_flag_ivi = 1;
#endif /* [★XSPI暫定対応(T.B.D)]初回データダミー対応 */

/****************************
*		prototype			*
****************************/
uint8	fs_tbl_Excute_ivi( uint8 event );					/* 処理テーブル内の該当状態・イベントの関数／状態を実施 */
void	fc_SpiInit_ivi( void );								/* ドライバ初期化 */
void	fc_SpiStartPrepare_ivi( void );						/* 送受信開始準備 */
void	fc_SpiEnd_ivi( void );								/* 送受信終了 */
void	fc_SpiAbort_ivi( void );							/* 送受信ドライバ中断 */
void	fc_SpiStop_ivi( void );								/* 送受信ドライバ停止 */

uint8	fc_drv_ENSigCheck_ivi( void );						/* EN信号状態チェック */
uint8	fc_drv_Spi_SubEvent_5ms_ivi( void );				/* XSPIメインサブイベント処理(5ms経過時) */
uint8	fc_drv_Spi_SubEvent_10ms_ivi( void );				/* XSPIメインサブイベント処理(10ms経過時) */
uint8	fc_drv_Spi_SubEvent_15ms_ivi( void );				/* XSPIメインサブイベント処理(15ms経過時) */
uint8	fc_drv_Spi_SubEvent_20ms_ivi( void );				/* XSPIメインサブイベント処理(20ms経過時) */
void	fc_drv_SpiRcvDpageRenew_ivi( void );				/* ドライバ用受信バッファページ更新 */
void	fc_drv_SpiSendDpageRenew_ivi( void );				/* ドライバ用送信バッファページ更新 */
void	fc_drv_SpiSetErrInfoKind_ivi( uint8 kind );			/* エラー種別情報設定 */
void	fc_drv_SpiClearErrInfoKind_ivi( uint8 kind );		/* エラー種別情報クリア */
void	fc_drv_SpiSetDbgErrInfo_ivi( uint8 dbg_errinfo );	/* デバッグ用エラー情報設定 */
uint8   fc_drv_SpiFccCheck_ivi( uint32* frame );			/* FCCチェック */
uint32	fc_drv_CalculationFcc_ivi( uint32 *ulbuf );			/* FCC計算処理 */

/********************************
*		table					*
********************************/
static const TBL_DRV_SPI	tb_drv_SpiDrvJmp_ivi[CMDRV_STAT_MAX][CMDRV_EVT_MAX] = {
/* 状態 */
/* 0: 初期化前 */
	{													/* Event */
		{ 0,					0 },					/* 0：初期化 */
		{ 0,					0 },					/* 1：定周期(5mS)通常動作 */
		{ 0,					0 },					/* 2：定周期(5mS)通信継続 */
		{ 0,					0 },					/* 3：転送未完了タイムアウト */
		{ fc_SpiInit_ivi,			CMDRV_STAT_IDLE },		/* 4：EN信号High */
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
		{ fc_SpiInit_ivi,			CMDRV_STAT_IDLE },		/* 4：EN信号High */
		{ 0,					0 },					/* 5：EN信号Low */
		{ 0,					0 },					/* 6：通信終了(5ms未満) */
		{ 0,					0 },					/* 7：通信終了(10ms以上) */
	},
/* 2: アイドル状態（EN信号High） */
	{													/* Event */
		{ 0,					0 },					/* 0：初期化 */
		{ fc_SpiStartPrepare_ivi,	CMDRV_STAT_COMM },		/* 1：定周期(5mS)通常動作 */
		{ 0,					0 },					/* 2：定周期(5mS)通信継続 */
		{ 0,					0 },					/* 3：転送未完了タイムアウト */
		{ 0,					0 },					/* 4：EN信号High */
		{ fc_SpiStop_ivi,			CMDRV_STAT_INVALID },	/* 5：EN信号Low */
		{ 0,					0 },					/* 6：通信終了(5ms未満) */
		{ 0,					0 },					/* 7：通信終了(10ms以上) */
	},
/* 3: 送受信状態 */
	{													/* Event */
		{ 0,					0 },					/* 0：初期化 */
		{ 0,					0 },					/* 1：定周期(5mS)通常動作 */
		{ 0,					0 },					/* 2：定周期(5mS)通信継続 */
		{ fc_SpiAbort_ivi,			CMDRV_STAT_RETRY },		/* 3：転送未完了タイムアウト */
		{ 0,					0 },					/* 4：EN信号High */
		{ fc_SpiStop_ivi,			CMDRV_STAT_INVALID },	/* 5：EN信号Low */
		{ fc_SpiEnd_ivi,			CMDRV_STAT_IDLE },		/* 6：通信終了(5ms未満) */
		{ fc_SpiEnd_ivi,			CMDRV_STAT_COMM },		/* 7：通信終了(10ms以上) */
	},
/* 4: リトライ状態(アイドル) */
	{													/* Event */
		{ 0,					0 },					/* 0：初期化 */
		{ fc_SpiStartPrepare_ivi,	CMDRV_STAT_COMM },		/* 1：定周期(5mS)通常動作 */
		{ 0,					0 },					/* 2：定周期(5mS)通信継続 */
		{ 0,					0 },					/* 3：転送未完了タイムアウト */
		{ 0,					0 },					/* 4：EN信号High */
		{ fc_SpiStop_ivi,			CMDRV_STAT_INVALID },	/* 5：EN信号Low */
		{ fc_SpiEnd_ivi,			CMDRV_STAT_IDLE },		/* 6：通信終了(5ms未満) */
		{ fc_SpiEnd_ivi,			CMDRV_STAT_COMM },		/* 7：通信終了(10ms以上) */
	}
};

/************************************************************************************
*																					*
*		SYMBOL		:	PDR_SPI_FRM_WR												*
*																					*
*		DESCRIPTION	:	Frame端子ポート設定											*
*																					*
*		PARAMETER	:	IN  	:	uint32		level								*
*									( 0::Low )	bit clear 							*
*									( 1::High)	bit set   							*
*																					*
*						OUT 	:	None											*
*																					*
*						RET 	:	None											*
*																					*
************************************************************************************/
static	void	PDR_SPI_FRM_WR_ivi	( uint32 level )
{
	Dio_WriteChannel( XSPI_FRM_PORT_ivi, level);
}

/************************************************************************************
*																					*
*		SYMBOL		:	PDR_SPI_EN													*
*																					*
*		DESCRIPTION	:	Enable端子ポート取得										*
*																					*
*		PARAMETER	:	IN  	:	None											*
*																					*
*						OUT 	:	None											*
*																					*
*						RET 	:	uint8 	EN端子Port状態							*
*											( 0::Low )	Ready						*
*											( 1::High)	Busy						*
*																					*
************************************************************************************/
static	uint8	PDR_SPI_EN_ivi ( void )
{
	return ( Dio_ReadChannel( XSPI_EN_PORT_ivi ) );
}

/************************************************************************************
*																					*
*		SYMBOL		:	XSPI_MEMSET													*
*																					*
*		DESCRIPTION	:	memset関数(XSPI用)											*
*																					*
*		PARAMETER	:	IN/OUT	:	void*	address									*
*						IN 		:	uint8	value									*
*						IN 		:	uint32	size									*
*																					*
*						OUT 	:	None											*
*																					*
*						RET 	:	None											*
*																					*
************************************************************************************/
static	void	XSPI_MEMSET_ivi ( void * address, uint8 value, uint32 size )
{
	uint8 *ptr = (uint8 *)address;
	while ((unsigned int)0 < size)
	{
		size--;
		*ptr = value;
		ptr++;
	}
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
void	xspi_Init_ivi(
	uint8	ch
)
{
	(VOID)ch;
	Port_SetPinMode( XSPI_SCLK_PORT_ivi, XSPI_SCLK_MODE_CFG_ivi );
	Port_SetPinMode( XSPI_TXD_PORT_ivi, XSPI_TXD_MODE_CFG_ivi );
	Port_SetPinMode( XSPI_RXD_PORT_ivi, XSPI_RXD_MODE_CFG_ivi );

	XSPI_MEMSET_ivi( &bf_drv_SpiMng_ivi, 0, sizeof(bf_drv_SpiMng_ivi) );	/* ドライバ管理バッファ初期化 */
	bf_drv_EnSignal_ivi = 0;										/* EN信号状態初期化 */
	bf_drv_ComTimeCount_ivi = 0;									/* 通信中M-SPIドライバ定周期(5mS)呼び出し回数カウンタ初期化 */

	bf_drv_DMA_Cnt_ivi = 0;											/* DMA転送カウントを初期化 */
	bf_drv_Dbg_ErrInfo_ivi = 0;										/* デバッグ用エラー情報を初期化 */

	PDR_SPI_FRM_WR_ivi( STD_HIGH );									/* Frame信号をHigh出力 */

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
void	xspi_DeInit_ivi(
	uint8	ch
)
{
	(VOID)ch;
	
	/* SPI非同期通信中断 */
	Spi_CancelAsyncTransmit( XSPI_COMC_ID_ivi );
	
	XSPI_MEMSET_ivi( &bf_drv_SpiMng_ivi, 0, sizeof(bf_drv_SpiMng_ivi) );	/* ドライバ管理バッファ初期化 */
	bf_drv_EnSignal_ivi = 0;										/* EN信号状態初期化 */
	bf_drv_ComTimeCount_ivi = 0;									/* 通信中M-SPIドライバ定周期(5mS)呼び出し回数カウンタ初期化 */

	PDR_SPI_FRM_WR_ivi( STD_HIGH );									/* Frame信号をHigh出力 */

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
uint8	xspi_GetCondition_ivi(
	uint8 ch
)
{
	(VOID)ch;
	uint8	stat, cond;
	stat = bf_drv_SpiMng_ivi.stat;				/* ドライバ状態遷移取得 */

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
#if 0 /* [★XSPI暫定対応(T.B.D)]CLib関数の為無効*/
        CLibTracePortLogOut( XSPI_TRCID_CPU_COM,     (unsigned short)0xFFFF, (unsigned short)0x0301, (unsigned short)stat,
							 (unsigned short)0x0000, (unsigned short)0x0000, (unsigned short)0x0000, (unsigned short)0x0000);
#endif /* [★XSPI暫定対応(T.B.D)]CLib関数の為無効*/

		bf_drv_SpiMng_ivi.stat = CMDRV_STAT_INIT;	/* 念の為、初期化前へ遷移 */
		cond = XSPI_DCOND_INIT;				/* 状態 ← 初期化前 */
		break;
	}

	return( cond );							/* ドライバ状態 */
}


/****************************************************************************
*																			*
*		SYMBOL		: xspi_Write											*
*																			*
*		DESCRIPTION	: Frame単位での送信バッファアドレス取得処理				*
*																			*
*		PARAMETER	: IN  :	ch		チャネルID								*
*						XSPI_CH_01	(0x00)	XSPIチャネルID：01（IVI向け）	*
*						XSPI_CH_02	(0x01)	XSPIチャネルID：02（METER向け）	*
*						XSPI_CH_03	(0x02)	XSPIチャネルID：03（CENTRAL向け）*
*																			*
*					  OUT :	*result	バッファ取得結果						*
*						XSPI_NG	(0x00)	バッファ取得失敗 					*
*						XSPI_OK	(0x01)	バッファ取得成功 	 				*
*																			*
*					  RET :	送信バッファページアドレス						*
*																			*
****************************************************************************/
uint8*	xspi_Write_ivi(
	uint8 ch,	uint8* result
)
{
	(VOID)ch;
	uint8 page = bf_drv_SpiMng_ivi.snd.page_task;
	uint8 page_current;

	*result = XSPI_NG;

	if( bf_drv_SpiMng_ivi.snd.page[page].inf == SND_FRM_DATA_NON )	/* 送信データ無し */
	{
		/* 現在ページを保存 */
		page_current = page;

		/* ページデータありを設定して送信ページ番号を更新 */
		bf_drv_SpiMng_ivi.snd.page[page].inf = SND_FRM_DATA_FIX;
		page++;
		page %= (uint8)XSPI_SND_PAGE;
		bf_drv_SpiMng_ivi.snd.page_task = page;

		*result = XSPI_OK;

		/* 現在ページのドライバ管理バッファ送信ページアドレス取得 */
		return( bf_drv_SpiMng_ivi.snd.page[page_current].dat );
	}

	return( NULL_PTR );
}


/****************************************************************************
*																			*
*		SYMBOL		: xspi_Read												*
*																			*
*		DESCRIPTION	: Frame単位での受信バッファアドレス取得処理				*
*																			*
*		PARAMETER	: IN  :	ch		チャネルID								*
*						XSPI_CH_01	(0x00)	XSPIチャネルID：01（IVI向け）	*
*						XSPI_CH_02	(0x01)	XSPIチャネルID：02（METER向け）	*
*						XSPI_CH_03	(0x02)	XSPIチャネルID：03（CENTRAL向け）*
*																			*
*					  OUT :	*result	バッファ取得結果						*
*						XSPI_NG	(0x00)	バッファ取得失敗 					*
*						XSPI_OK	(0x01)	バッファ取得成功 	 				*
*																			*
*					  RET :	受信バッファページアドレス						*
*																			*
****************************************************************************/
uint8*	xspi_Read_ivi(
	uint8 ch,	uint8* result
)
{
	(VOID)ch;
	uint8 page = bf_drv_SpiMng_ivi.rcv.page_task;
	uint8 page_current;
	uint8 fcc;

	*result = XSPI_NG;
	
	if( bf_drv_SpiMng_ivi.rcv.page[page].inf == RCV_FRM_DATA_FIX )	/* 受信データあり */
	{
		/* 現在ページを保存 */
		page_current = page;

		/* ページデータなしを設定して受信ページ番号を更新 */
		bf_drv_SpiMng_ivi.rcv.page[page].inf = RCV_FRM_DATA_NON;
		page++;
		page %= (uint8)XSPI_RCV_PAGE;
		bf_drv_SpiMng_ivi.rcv.page_task = page;

		/* FCCチェック */
		fcc = fc_drv_SpiFccCheck_ivi( (uint32*)bf_drv_SpiMng_ivi.rcv.page[page_current].dat );
		if( fcc == XSPI_OK )
		{
			fc_drv_SpiClearErrInfoKind_ivi( XSPI_ERR_KIND_FCC );

			*result = XSPI_OK;

			/* 現在ページのドライバ管理バッファ受信ページアドレス取得 */
			return( bf_drv_SpiMng_ivi.rcv.page[page_current].dat );
		}
		else
		{
			/* FCC不一致 */
			fc_drv_SpiSetErrInfoKind_ivi( XSPI_ERR_KIND_FCC );
			fc_drv_SpiSetDbgErrInfo_ivi( XSPI_ERR_DBG_FCC );
		}
	}

	return( NULL_PTR );
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
void	xspi_Main_ivi(
	uint8	ch
)
{
	(VOID)ch;
	uint8	event;			/* イベントNo. */
	uint8	stat;

	/* テーブル処理前の状態を保存 */
	stat = bf_drv_SpiMng_ivi.stat;
	event = fc_drv_ENSigCheck_ivi();			/* EN信号状態チェック */

	/* 現在の遷移状態のイベントをチェック */
	switch( stat )				/* ドライバ状態 */
	{

		case CMDRV_STAT_INIT :				/* 初期化前 */
		case CMDRV_STAT_INVALID :			/* 通信無効（EN信号Low状態） */
			bf_drv_ComTimeCount_ivi = 0;
			break;

		case CMDRV_STAT_RETRY:				/* リトライ状態 */
		case CMDRV_STAT_IDLE :				/* アイドル状態（EN信号High状態） */
			/* EN信号がHighの場合は通信開始 */
			bf_drv_ComTimeCount_ivi = 0;

			fc_drv_SpiClearErrInfoKind_ivi( XSPI_ERR_KIND_ENCHG );

			break;

		case CMDRV_STAT_COMM :				/* 送受信状態 */
			if( event == (uint8)CMDRV_EVT_NORMAL )
			{
				switch( bf_drv_ComTimeCount_ivi )
				{
				case	CMDRV_COM_TIME_1	:		/* 定周期(5mS)回数カウント 通信中１ */
					event = fc_drv_Spi_SubEvent_5ms_ivi();
					break;
				case	CMDRV_COM_TIME_2	:		/* 定周期(5mS)回数カウント 通信中２ */
					event = fc_drv_Spi_SubEvent_10ms_ivi();
					break;
				case	CMDRV_COM_TIME_x	:		/* 定周期(5mS)回数カウント 通信中３ */
					event = fc_drv_Spi_SubEvent_15ms_ivi();
					break;
				case	CMDRV_COM_TIMEOUT	:		/* 定周期(5mS)回数カウント 通信中最大値 */
					event = fc_drv_Spi_SubEvent_20ms_ivi();
					break;
				default:
					bf_drv_ComTimeCount_ivi = 0;
					break;
				}
			}
			else
			{
				fc_drv_SpiSetErrInfoKind_ivi( XSPI_ERR_KIND_ENCHG );
				bf_drv_ComTimeCount_ivi = 0;
			}
			break;

		default :							/* 状態に該当なし */
#if 0 /* [★XSPI暫定対応(T.B.D)]CLib関数の為無効*/
			CLibTracePortLogOut( XSPI_TRCID_CPU_COM,    (unsigned short)0xFFFF, (unsigned short)0x0302, (unsigned short)stat,
								(unsigned short)0x0000, (unsigned short)0x0000, (unsigned short)0x0000, (unsigned short)0x0000 );
#endif /* [★XSPI暫定対応(T.B.D)]CLib関数の為無効*/

			bf_drv_SpiMng_ivi.stat = CMDRV_STAT_INIT;	/* 念の為、初期化前へ遷移 */
			stat = CMDRV_STAT_MAX;
			break;
	}

	if ( stat == (uint8)CMDRV_STAT_MAX )
	{
		return;		/* 何もしない */
	}

	/* 処理テーブル内の該当状態・イベントの関数／状態を実施 */
	(VOID)fs_tbl_Excute_ivi( event );

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
*						XSPI_ERR_KIND_FCC	(0x02)	FCC不一致 				*
*						XSPI_ERR_KIND_ENCHG	(0x40)	EN信号変化 				*
*						XSPI_ERR_KIND_TIM	(0x80)	通信時間オーバ 			*
*																			*
****************************************************************************/
uint8	xspi_GetErrInfo_ivi(
	uint8	ch
)
{
	(VOID)ch;
	return( bf_drv_SpiMng_ivi.err_info );
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
uint8	fs_tbl_Excute_ivi(
	uint8	event					/* イベントNo. */
)
{
	uint8	stat;

	/* テーブル処理前の状態を保存 */
	stat = bf_drv_SpiMng_ivi.stat;

	/* 処理テーブル内の該当状態・イベントの関数アドレス有無チェック */
	if( tb_drv_SpiDrvJmp_ivi[stat][event].func != NULL_PTR )
	{	/* 処理テーブル内の該当状態・イベントの関数アドレスあり */
		/* 該当する処理関数呼び出し */
		tb_drv_SpiDrvJmp_ivi[stat][event].func();
	}
	/* 処理テーブル内の該当状態・イベントの次の状態有無チェック */
	if( tb_drv_SpiDrvJmp_ivi[stat][event].next_stat != (uint8)0 )
	{	/* 処理テーブル内の該当状態・イベントの次の状態あり */
		/* 該当する次の状態をセット */
		bf_drv_SpiMng_ivi.stat = tb_drv_SpiDrvJmp_ivi[stat][event].next_stat;
	}

	return( bf_drv_SpiMng_ivi.stat );
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
void	fc_SpiInit_ivi(
	void
)
{
	/* 送信バッファデータあり情報セット */
	bf_drv_SpiMng_ivi.snd.page[XSPI_SND_PAGE].inf = SND_FRM_DATA_FIX;

	/* Frame 信号High出力	*/
	PDR_SPI_FRM_WR_ivi( STD_HIGH );
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
void	fc_SpiStartPrepare_ivi(
	void
)
{
	uint8		spage, rpage;
	uint8		*rcv_buf, *snd_buf;
	uint32		fcc_offset;
	uint32		fcc_calc;

	/* 受信バッファ指定 */
	rpage = bf_drv_SpiMng_ivi.rcv.page_drv;

	/* 受信用バッファ空チェック */
	if( bf_drv_SpiMng_ivi.rcv.page[rpage].inf != (uint8)RCV_FRM_DATA_NON )
	{	/* 受信用バッファにデータあり（固定アドレスへ受信＆破棄） */
		rpage = XSPI_RCV_PAGE;
		fc_drv_SpiSetDbgErrInfo_ivi( XSPI_ERR_DBG_OVERFLOW );
	}
#if 1 /* [★XSPI暫定対応(T.B.D)]初回データダミー対応 */
	if( bf_drv_dummy_flag_ivi == 1 )
	{
		rpage = XSPI_RCV_PAGE;
	}
#endif /* [★XSPI暫定対応(T.B.D)]初回データダミー対応 */

	/* 受信用バッファアドレス */
	rcv_buf = (uint8 *)&bf_drv_SpiMng_ivi.rcv.page[rpage].dat[0];
	/* 受信中バッファページ保存 */
	bf_drv_SpiMng_ivi.rcv.page_rcv = rpage;

	/* 送信バッファ指定 */
	spage = bf_drv_SpiMng_ivi.snd.page_drv;

	/* 送信用バッファデータありチェック */
	if( bf_drv_SpiMng_ivi.snd.page[spage].inf != (uint8)SND_FRM_DATA_FIX )
	{	/* 送信用バッファ内にデータセットされていない（固定アドレスを指定して空データ送信） */
		spage = XSPI_SND_PAGE;
	}
#if 1 /* [★XSPI暫定対応(T.B.D)]初回データダミー対応 */
	if( bf_drv_dummy_flag_ivi == 1 )
	{
		spage = XSPI_SND_PAGE;
	}
#endif /* [★XSPI暫定対応(T.B.D)]初回データダミー対応 */

	/* 送信用バッファアドレス */
	snd_buf = (uint8 *)&bf_drv_SpiMng_ivi.snd.page[spage].dat[0];

	/* 送信中バッファページ保存 */
	bf_drv_SpiMng_ivi.snd.page_send = spage;
	
	/* Frame Header未使用領域(Byte0)にデバッグ用エラー情報をセット */
	snd_buf[0] = bf_drv_Dbg_ErrInfo_ivi;

	/* Calclation FCC */
#if 0 /* [T.B.D]IVI向け暫定対応 */
	fcc_offset = XSPI_FCC_OFFSET;
#else
	fcc_offset = (uint32)(5552 - 4);
#endif /* [T.B.D]IVI向け暫定対応 */
	fcc_calc = fc_drv_CalculationFcc_ivi((uint32*)snd_buf);
	snd_buf[fcc_offset] = BYTE_SWAP4(fcc_calc);
	snd_buf[fcc_offset+1] = BYTE_SWAP3(fcc_calc);
	snd_buf[fcc_offset+2] = BYTE_SWAP2(fcc_calc);
	snd_buf[fcc_offset+3] = BYTE_SWAP1(fcc_calc);

	bf_drv_ComTimeCount_ivi = 1;	/* 通信中M-SPIドライバ定周期(5mS)呼び出し回数カウント開始 */

	/* SPI非同期通信開始 */
	Spi_AsyncTransmit( XSPI_COMC_ID_ivi, (const Spi_ModeC_DataType *)snd_buf, (const Spi_ModeC_DataType *)rcv_buf,(U2)XSPI_SND_FRM_MAX );

	/* Frame信号をLow出力 */
	PDR_SPI_FRM_WR_ivi( STD_LOW );

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
void	fc_SpiEnd_ivi(
	void
)
{
	sint32 err;

	fc_drv_SpiClearErrInfoKind_ivi( XSPI_ERR_KIND_TIM );

	/* オーバーランエラー状態チェック */
	err = Spi_GetOvrunErrStatus( XSPI_COMC_ID_ivi );
	if( err != 0)
	{
		fc_drv_SpiSetErrInfoKind_ivi( XSPI_ERR_KIND_TRX );
		fc_drv_SpiSetDbgErrInfo_ivi( XSPI_ERR_DBG_DMAOVERRUN );
	}
	else {
		fc_drv_SpiClearErrInfoKind_ivi( XSPI_ERR_KIND_TRX );

		/* 送受信バッファページ更新 */
		fc_drv_SpiRcvDpageRenew_ivi();
		fc_drv_SpiSendDpageRenew_ivi();

#if 1 /* [★XSPI暫定対応(T.B.D)]初回データダミー対応 */
		bf_drv_dummy_flag_ivi = 0;
#endif /* [★XSPI暫定対応(T.B.D)]初回データダミー対応 */
	}

	/* 経過時間チェック(通信開始から10ms以上経過している場合) */
	if(bf_drv_ComTimeCount_ivi > CMDRV_COM_TIME_1 ){
		/* 送受信開始準備 */
		fc_SpiStartPrepare_ivi();
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
void	fc_SpiAbort_ivi(
	void
)
{
	/* SPI非同期通信中断 */
	Spi_CancelAsyncTransmit( XSPI_COMC_ID_ivi );

	PDR_SPI_FRM_WR_ivi( STD_HIGH );	/* Frame 信号High出力 */

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
void	fc_SpiStop_ivi(
	void
)
{
	/* SPI非同期通信中断 */
	Spi_CancelAsyncTransmit( XSPI_COMC_ID_ivi );

	fc_drv_SpiSendDpageRenew_ivi();	/* ドライバ用送信バッファページ更新 */

	PDR_SPI_FRM_WR_ivi( STD_HIGH );	/* Frame 信号High出力 */
}


/****************************************************************************/
/**************				ドライバ内部サブ処理				*************/
/****************************************************************************/

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
*										CMDRV_EVT_NORMAL (1)	EN信号変化なし		*
*										CMDRV_EVT_ENHIGH (2)	EN信号Highへ変化	*
*										CMDRV_EVT_ENLOW  (3)	EN信号Lowへ変化		*
*																			*
****************************************************************************/
uint8	fc_drv_ENSigCheck_ivi(
	void
)
{
	uint8	en_now;

	en_now = (uint8)PDR_SPI_EN_ivi();				/* 現在の EN信号状態を外部ポートから取得 */

	if( bf_drv_EnSignal_ivi != en_now )
	{	/* EN信号状態変化 */
		bf_drv_EnSignal_ivi = en_now;			/* EN信号状態更新 */

		if( bf_drv_EnSignal_ivi == (uint8)STD_HIGH )
		{	/* EN High */
#if 0 /* [★XSPI暫定対応(T.B.D)]CLib関数の為無効*/
			CLibTracePortLogOut( XSPI_TRCID_CPU_COM,    (unsigned short)0xEEEE, (unsigned short)0x0001, (unsigned short)0x0000,
								(unsigned short)0x0000, (unsigned short)0x0000, (unsigned short)0x0000, (unsigned short)0x0000);
#endif /* [★XSPI暫定対応(T.B.D)]CLib関数の為無効*/

			/* 処理テーブル内の該当状態・イベントの関数／状態を実施 */
			return( CMDRV_EVT_ENHIGH );	/* EN信号High検知イベント */
		}
		else
		{	/* EN Low */
#if 0 /* [★XSPI暫定対応(T.B.D)]CLib関数の為無効*/
			CLibTracePortLogOut( XSPI_TRCID_CPU_COM,    (unsigned short)0xEEEE, (unsigned short)0x0000, (unsigned short)0x0000,
								(unsigned short)0x0000, (unsigned short)0x0000, (unsigned short)0x0000, (unsigned short)0x0000);
#endif /* [★XSPI暫定対応(T.B.D)]CLib関数の為無効*/

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
uint8	fc_drv_Spi_SubEvent_5ms_ivi(
	void
)
{
	uint8 spi_stat;
	uint8 event;

	/* Frame信号をHigh出力 */
	PDR_SPI_FRM_WR_ivi( STD_HIGH );

	/* SPI通信状態の取得 */
	spi_stat = Spi_GetStatus( XSPI_COMC_ID_ivi );
	if ( spi_stat == SPI_IDLE )
	{
		/* 通信終了 */
		event = CMDRV_EVT_COMEND;
	}
	else
	{
		/* 通信継続 */
		bf_drv_ComTimeCount_ivi++;
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
uint8	fc_drv_Spi_SubEvent_10ms_ivi(
	void
)
{
	const Spi_ModeC_ChannelConfigType* t_pcstChannelConfig = &cstSpi_UcfgModeCData.pstChannelConfig[XSPI_COMC_ID_ivi];
	uint8 spi_stat;
	uint8 event;

	/* SPI通信状態チェック */
	spi_stat = Spi_GetStatus( XSPI_COMC_ID_ivi );
	if ( spi_stat == SPI_IDLE )
	{	/* 通信終了 */
		event = CMDRV_EVT_COMEND_10ms;
	}
	else
	{
		/* ＤＭＡ転送中のカウント値を取得 */
		bf_drv_DMA_Cnt_ivi = Dma_GetTransCount( t_pcstChannelConfig->u1DmaRxChannel );

		/* 通信継続 */
		bf_drv_ComTimeCount_ivi++;
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
uint8	fc_drv_Spi_SubEvent_15ms_ivi(
	void
)
{
	const Spi_ModeC_ChannelConfigType* t_pcstChannelConfig = &cstSpi_UcfgModeCData.pstChannelConfig[XSPI_COMC_ID_ivi];
	uint16 DTC;
	uint8 spi_stat;
	uint8 event;

	/* DMA転送カウントチェック(転送カウントに減少あり) */
	DTC = Dma_GetTransCount( t_pcstChannelConfig->u1DmaRxChannel );
	if( ( DTC < bf_drv_DMA_Cnt_ivi ) )
	{	/* 前回のカウント値よりカウントダウン */

		/* SPI通信状態チェック */
		spi_stat = Spi_GetStatus( XSPI_COMC_ID_ivi );
		if ( spi_stat == SPI_IDLE )
		{	/* 通信終了 */
			event = CMDRV_EVT_COMEND_10ms;
		}
		else
		{	/* 通信継続 */
			bf_drv_ComTimeCount_ivi++;
			event = CMDRV_EVT_N_NEXT;
		}
	}
	else
	{	/* 前回のカウント値に変化なし */
		bf_drv_ComTimeCount_ivi = 0;
		event = CMDRV_EVT_TIMEOUT;
		fc_drv_SpiSetErrInfoKind_ivi( XSPI_ERR_KIND_TIM );
		fc_drv_SpiSetDbgErrInfo_ivi( XSPI_ERR_DBG_SLAVETIM15 );
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
uint8	fc_drv_Spi_SubEvent_20ms_ivi(
	void
)
{
	uint8 spi_stat;
	uint8 event;

	/* SPI通信状態チェック */
	spi_stat = Spi_GetStatus( XSPI_COMC_ID_ivi );
	if ( spi_stat == SPI_IDLE )
	{	/* 通信終了 */
		event = CMDRV_EVT_COMEND_10ms;
	}
	else
	{	/* 転送未完了タイムアウト */
		bf_drv_ComTimeCount_ivi = 0;
		event = CMDRV_EVT_TIMEOUT;
		fc_drv_SpiSetErrInfoKind_ivi( XSPI_ERR_KIND_TIM );
		fc_drv_SpiSetDbgErrInfo_ivi( XSPI_ERR_DBG_SLAVETIM20 );
	}

	return( event );
}

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_SpiFccCheck									*
*																			*
*		DESCRIPTION	: FCCチェック											*
*																			*
*		PARAMETER	: IN  :	uint8*	フレーム								*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :													*
*							uint8	チェック結果							*
*										XSPI_NG		(0x00)	 異常 			*
*										XSPI_OK		(0x01)	 正常 			*
*																			*
****************************************************************************/
uint8	fc_drv_SpiFccCheck_ivi(
	uint32* frame
)
{
	uint8 ret = XSPI_OK;
	uint32 fcc;
	uint32 fcc_calc;

	/* Calclation FCC */
	fcc = BYTE_SWAP_32(frame[XSPI_FCC_LONG_OFFSET]);
	fcc_calc = fc_drv_CalculationFcc_ivi(frame);

	if( fcc != fcc_calc ){
		ret = XSPI_NG;
	}

	return( ret );
}

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_CalculationFcc_Sub_Addition					*
*																			*
*		DESCRIPTION	: FCC 計算処理											*
*																			*
*		PARAMETER	: IN  	:	agvUl_data1 …	FCC 加算データ1 			*
*							:	agvUl_data2 …	FCC 加算データ2 			*
*																			*
*					  OUT 	:	None										*
*																			*
*					  RET 	:	FCC 演算結果								*
*																			*
****************************************************************************/
static	uint32	fc_drv_CalculationFcc_Sub_Addition_ivi(uint32 agvUl_data1, uint32 agvUl_data2)
{
	uint32	wkvUl_result;
	uint32	wkvUl_data1;
	uint32	wkvUl_data2;

	wkvUl_data1 = agvUl_data1;
	wkvUl_data2 = agvUl_data2;

	/* Over Flowチェック([ULONG_MAX - agvUl_data1 ] vs [wkvUl_data2 ]) */
	if(	(ULONG_MAX - wkvUl_data1 ) >= wkvUl_data2 )
	{	/* -Yes (  >=  )- Over Flowしない時 */
		wkvUl_result = wkvUl_data1 + wkvUl_data2;	/* fcc 算出処理 */
	}
	else
	{	/* -No (  <   )- Over Flowする時 */
		/* fcc 演算	*/
		if( wkvUl_data1  >= wkvUl_data2 )
		{	/* -Yes (  >=  )- 以上 */
			wkvUl_result = wkvUl_data2 - (ULONG_MAX - wkvUl_data1 + 1UL);
		}
		else
		{	/* -No  (  <   )- 未満 */
			wkvUl_result = wkvUl_data1 - (ULONG_MAX - wkvUl_data2 + 1UL);
		}
	}

	return( wkvUl_result );
}

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_CalculationFcc									*
*																			*
*		DESCRIPTION	: FCC計算処理											*
*																			*
*		PARAMETER	: IN  :	ulbuf		･･･	ﾊﾞｯﾌｧﾎﾟｲﾝﾀ						*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	計算結果（FCCの１の補数）						*
*																			*
****************************************************************************/
uint32	fc_drv_CalculationFcc_ivi(uint32 *ulbuf)
{
	uint32 ulfcc, frame_id, msg_offset;
	uint32	ulfcc_temp;
	uint8	*flame_header;
	uint32	subframe_offset;

	flame_header = (uint8*)&ulbuf[0];

	/* Frame Header 上位4byte 下位4byte 加算 */
	ulfcc = fc_drv_CalculationFcc_Sub_Addition_ivi( BYTE_SWAP_32(ulbuf[0]), BYTE_SWAP_32(ulbuf[1]));

	/* Sub Frame 0 上位4byte 下位4byte 加算 */
	ulfcc_temp = fc_drv_CalculationFcc_Sub_Addition_ivi( BYTE_SWAP_32(ulbuf[2]), BYTE_SWAP_32(ulbuf[3]));
	ulfcc = fc_drv_CalculationFcc_Sub_Addition_ivi( ulfcc, ulfcc_temp );

	/* 未使用、Sub Frame1～Sub Frame7 上位4byte 下位4byte 加算 */
	for(frame_id = 1; frame_id < XSPI_SUB_FRAME_MAX; frame_id++)
	{
		subframe_offset = flame_header[frame_id];

		if( subframe_offset != (uint8)0 )
		{
			msg_offset = ((uint32)subframe_offset * (uint32)8UL) / sizeof(uint32);
			ulfcc_temp = fc_drv_CalculationFcc_Sub_Addition_ivi( BYTE_SWAP_32(ulbuf[msg_offset]), BYTE_SWAP_32(ulbuf[msg_offset + (uint32)1]) );
			ulfcc = fc_drv_CalculationFcc_Sub_Addition_ivi( ulfcc, ulfcc_temp );
		}
	}

	return( ulfcc );
}

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_SpiRcvDpageRenew								*
*																			*
*		DESCRIPTION	: ドライバ用受信バッファページ更新						*
*																			*
*		PARAMETER	: IN  :	None											*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	None											*
*																			*
****************************************************************************/
void	fc_drv_SpiRcvDpageRenew_ivi(
	void
)
{
	uint8	page;

	/* ドライバ受信中バッファページ */
	page = bf_drv_SpiMng_ivi.rcv.page_rcv;

	if( bf_drv_SpiMng_ivi.rcv.page_drv == page )
	{	/* 受信バッファ空で新たなデータを受信（固定ページでは無い） */
		bf_drv_SpiMng_ivi.rcv.page[page].inf = RCV_FRM_DATA_FIX;	/* 受信データあり情報 */

		/* ドライバ用受信バッファページ更新 */
		page++;
		page %= (uint8)XSPI_RCV_PAGE;
		bf_drv_SpiMng_ivi.rcv.page_drv = page;
	}
}


/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_SpiSendDpageRenew								*
*																			*
*		DESCRIPTION	: ドライバ用送信バッファページ更新						*
*																			*
*		PARAMETER	: IN  :	None											*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	None											*
*																			*
****************************************************************************/
void	fc_drv_SpiSendDpageRenew_ivi(
	void
)
{
	uint8	page;

	/* ドライバ送信中バッファページ */
	page = bf_drv_SpiMng_ivi.snd.page_send;

	if( bf_drv_SpiMng_ivi.snd.page_drv == page )
	{	/* 送信データありを送信（固定ページでは無い） */
		bf_drv_SpiMng_ivi.snd.page[page].inf = SND_FRM_DATA_NON;	/* 送信データなし情報 */

		/* ドライバ用送信バッファページ更新 */
		page++;
		page %= (uint8)XSPI_SND_PAGE;
		bf_drv_SpiMng_ivi.snd.page_drv = page;
	}
}


/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_SpiSetErrInfoKind								*
*																			*
*		DESCRIPTION	: ドライバ用エラー情報設定								*
*																			*
*		PARAMETER	: IN  :	uint8 kind：エラー種別							*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	None											*
*																			*
****************************************************************************/
void	fc_drv_SpiSetErrInfoKind_ivi( uint8 kind )
{
	/* エラー情報に種別をセット */
	bf_drv_SpiMng_ivi.err_info |= (uint8)(kind & (uint8)XSPI_ERR_MSK_KIND) ;
}

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_SpiclearErrInfoKind							*
*																			*
*		DESCRIPTION	: ドライバ用エラー情報クリア							*
*																			*
*		PARAMETER	: IN  :	uint8 kind：エラー種別							*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	None											*
*																			*
****************************************************************************/
void	fc_drv_SpiClearErrInfoKind_ivi( uint8 kind )
{
	/* エラー情報種別をクリア */
	bf_drv_SpiMng_ivi.err_info &= (~kind) ;
}

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_SpiSetDbgErrInfo								*
*																			*
*		DESCRIPTION	: デバッグ用エラー情報設定処理							*
*																			*
*		PARAMETER	: IN  :	uint8 dbg_errinfo：デバッグ用エラー情報			*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	None											*
*																			*
****************************************************************************/
void	fc_drv_SpiSetDbgErrInfo_ivi( uint8 dbg_errinfo )
{
	/*  デバッグ用エラー情報にエラー情報をセット */
	bf_drv_Dbg_ErrInfo_ivi |= (uint8)(dbg_errinfo & (uint8)XSPI_ERR_MSK_DBG) ;
}