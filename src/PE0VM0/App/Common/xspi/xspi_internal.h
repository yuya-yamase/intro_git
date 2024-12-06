/***************************************************************************/
/*【ファイル名】xspi_internal.h                                       */
/***************************************************************************/
#ifndef	XSPI_INTERNAL_H
#define	XSPI_INTERNAL_H

/************************************************************************
*																		*
*				Ｌocal Ｄefine Ｄeclare Ｓection						*
*																		*
************************************************************************/
#define		VOID			void

/*------------------------------*/
/*	フレームバッファサイズ関連	*/
/*------------------------------*/
#define		XSPI_RCV_PAGE	(3)		/* 受信バッファページ数 */
#define		XSPI_SND_PAGE	(3)		/* 送信バッファページ数 */

/*------------------------------*/
/*	ドライバ状態				*/
/*------------------------------*/
enum {
	CMDRV_STAT_INIT = 0,			/* 初期化前 */
	CMDRV_STAT_INVALID,				/* 通信無効（EN信号Low状態） */
	CMDRV_STAT_IDLE,				/* アイドル状態（EN信号High状態） */
	CMDRV_STAT_COMM,				/* 送受信状態 */
	CMDRV_STAT_RETRY,				/* リトライ状態 */
	CMDRV_STAT_MAX
};

/*------------------------------*/
/*	イベントＮｏ				*/
/*------------------------------*/
enum {
	CMDRV_EVT_INIT =0,				/* 初期化 */
	CMDRV_EVT_NORMAL,				/* 定周期(5mS)通常動作(Frame信号) */
	CMDRV_EVT_N_NEXT,				/* 定周期(5mS)通信継続(Frame信号) */
	CMDRV_EVT_TIMEOUT,				/* 転送未完了タイムアウト */
	CMDRV_EVT_ENHIGH,				/* EN信号High */
	CMDRV_EVT_ENLOW,				/* EN信号Low */
	CMDRV_EVT_COMEND,				/* 通信終了(5ms未満) */
	CMDRV_EVT_COMEND_10ms,			/* 通信終了(10ms以上) */
	CMDRV_EVT_MAX
};

/*------------------------------*/
/*	通信中呼び出しカウンタ状態	*/
/*------------------------------*/
#define	CMDRV_COM_TIME_1	(1)		/* 定周期(5mS)回数カウント 通信中１     */
#define	CMDRV_COM_TIME_2	(2)		/* 定周期(5mS)回数カウント 通信中２     */
#define	CMDRV_COM_TIME_x	(3)		/* 定周期(5mS)回数カウント 通信中最大値 */
#define	CMDRV_COM_TIMEOUT	(4)		/* 定周期(5mS)回数カウント 通信中最大値 */

/*------------------------------------------*/
/*	送受信ページデータ有無状態フラグ		*/
/*------------------------------------------*/
#define	SND_FRM_DATA_NON	(0x00)	/* 送信ページデータ無し		*/
#define	SND_FRM_DATA_FIX	(0x01)	/* 送信ページデータ確定		*/
#define	RCV_FRM_DATA_NON	(0x00)	/* 受信ページデータ無し		*/
#define	RCV_FRM_DATA_FIX	(0x01)	/* 受信ページデータ確定		*/

/*------------------------------------------*/
/*	エンディアン変換						*/
/*------------------------------------------*/
#define BYTE_SWAP1(x)       (  (uint32)(x)        & (uint32)0x000000FFUL )
#define BYTE_SWAP2(x)       ( ((uint32)(x) >>  8) & (uint32)0x000000FFUL )
#define BYTE_SWAP3(x)       ( ((uint32)(x) >> 16) & (uint32)0x000000FFUL )
#define BYTE_SWAP4(x)       ( ((uint32)(x) >> 24) & (uint32)0x000000FFUL )
#define BYTE_SWAP_32(x)     ((uint32) ( (BYTE_SWAP1(x) << 24) | (BYTE_SWAP2(x) << 16) | (BYTE_SWAP3(x) << 8) | BYTE_SWAP4(x) ))
#define ULONG_MAX     0xffffffffUL

/*------------------------------*/
/*	サブフレーム関連			*/
/*------------------------------*/
#define XSPI_SUB_FRAME_MAX		(8)					/* M-SPI Sub Frame MAX					*/
#define XSPI_FRAME_SIZE			(XSPI_SND_FRM_MAX-4)	/* M-SPI Frame Size	(exclude FCC)		*/
#define XSPI_FCC_OFFSET			(XSPI_FRAME_SIZE)		/* M-SPI FCC Offset						*/
#define XSPI_FCC_LONG_OFFSET	(XSPI_FRAME_SIZE/4)		/* M-SPI FCC Offset	(XSPI_FRAME_SIZE/sizof(LONG))	*/

/*------------------------------*/
/*	通信エラー検出状態フラグ	*/
/*------------------------------*/
#define		XSPI_ERR_MSK_DBG		(0x1F)			/* MASK：デバッグ用エラー				*/
#define		XSPI_ERR_DBG_FCC		(0x01)			/* FCC不一致							*/
#define		XSPI_ERR_DBG_OVERFLOW	(0x02)			/* 受信バッファ溢れ						*/
#define		XSPI_ERR_DBG_DMAOVERRUN	(0x04)			/* DMAオーバーランエラー				*/
#define		XSPI_ERR_DBG_SLAVETIM20	(0x08)			/* Slave通信タイムアウトエラー（20ms）	*/
#define		XSPI_ERR_DBG_SLAVETIM15	(0x10)			/* Slave通信タイムアウトエラー（15ms）	*/

/************************************************************************
*																		*
*				Ｓtruct Ｄeclare Ｓection								*
*																		*
************************************************************************/
/*------------------------------*/
/*	ドライバ管理バッファ		*/
/*------------------------------*/
typedef struct {
	uint8	stat;						/* 遷移状態 */
	uint8	err_info;					/* エラー通知管理用 */

	struct {							/* 送信管理情報 */
		uint8   page_task;				/* タスク用送信バッファ書き込みページ	*/
		uint8   page_drv;				/* ドライバ用送信バッファページ	*/
		uint8	page_send;				/* ドライバ送信中のページ（空ページも含めて） */
		uint8	dummy[3];				/* ４byteアライメント用ダミー */

		struct {
			uint8	dat[XSPI_SND_FRM_MAX];	/* 送信データ領域 */
			uint8	inf;				/* 送信ページデータ有(1)／無(0) */
			uint8	dummy[3];			/* ４byteアライメント用ダミー */
		} page[XSPI_SND_PAGE + 1];
	} snd;

	struct {							/* 受信管理情報 */
		uint8   page_task;				/* タスク用受信バッファ書き込みページ	*/
		uint8   page_drv;				/* ドライバ用受信バッファページ	*/
		uint8	page_rcv;				/* ドライバ受信中のページ（空ページも含めて） */
		uint8	dummy[1];				/* ４byteアライメント用ダミー */

		struct {
			uint8	dat[XSPI_RCV_FRM_MAX];	/* 受信データ領域 */
			uint8	inf;				/* 受信ページデータ有(1)／無(0) */
			uint8	dummy[3];			/* ４byteアライメント用ダミー */
		} page[XSPI_RCV_PAGE + 1];
	} rcv;
} BF_DRV_SPI;

/*------------------------------*/
/*	ドライバ管理テーブル		*/
/*------------------------------*/
typedef struct {
	void(*func)(void);					/* イベント処理関数アドレス */
	uint8	next_stat;					/* 処理後の状態 */
} TBL_DRV_SPI;

#endif	/* XSPI_INTERNAL_H */
