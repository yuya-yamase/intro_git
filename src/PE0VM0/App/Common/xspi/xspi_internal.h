/***************************************************************************/
/*【ファイル名】xspi_internal.h                                       */
/***************************************************************************/
#ifndef	XSPI_INTERNAL_H
#define	XSPI_INTERNAL_H

/****************************
*		include	files		*
****************************/
#include "Port.h"
#include "Dma.h"
#include "Dio.h"
#include "Spi.h"
#include "Rte_BswUcfg.h"

#include "xspi.h"
#include "xspi_cfg.h"

/************************************************************************
*																		*
*				Ｌocal Ｄefine Ｄeclare Ｓection						*
*																		*
************************************************************************/
#define		VOID			void

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

/*------------------------------*/
/*	エンディアン変換マクロ		*/
/*------------------------------*/
#define BYTE_SWAP1(x)		(  (uint32)(x)        & (uint32)0x000000FFUL )
#define BYTE_SWAP2(x)		( ((uint32)(x) >>  8) & (uint32)0x000000FFUL )
#define BYTE_SWAP3(x)		( ((uint32)(x) >> 16) & (uint32)0x000000FFUL )
#define BYTE_SWAP4(x)		( ((uint32)(x) >> 24) & (uint32)0x000000FFUL )
#define BYTE_SWAP_32(x)		((uint32) ( (BYTE_SWAP1(x) << 24) | (BYTE_SWAP2(x) << 16) | (BYTE_SWAP3(x) << 8) | BYTE_SWAP4(x) ))
#define ULONG_MAX			(0xffffffffUL)

/*------------------------------*/
/*	バッファ制御関連			*/
/*------------------------------*/
#define	SND_FRM_DATA_NON		(0x00)			/* 送信ページデータ無し */
#define	SND_FRM_DATA_FIX		(0x01)			/* 送信ページデータ確定 */
#define	RCV_FRM_DATA_NON		(0x00)			/* 受信ページデータ無し */
#define	RCV_FRM_DATA_FIX		(0x01)			/* 受信ページデータ確定 */
#define XSPI_BUF_PAGE_0			(0x00)			/* バッファページ0 */
#define XSPI_BUF_PAGE_1			(0x01)			/* バッファページ1 */
#define XSPI_BUF_PAGE_LOCK		(0x02)			/* バッファページロック */
#define XSPI_BUF_PAGE			(2)				/* バッファページ数 */

/*------------------------------*/
/*	整合性データチェック関連	*/
/*------------------------------*/
#define XSPI_SUB_FRAME_MAX_ivi		(8)						/* XSPI Sub Frame MAX */
#define XSPI_SUB_FRAME_UNIT_ivi		(8)						/* XSPI Sub Frame UNIT */
#define XSPI_FCC_OFFSET_ivi			(XSPI_FRAME_SIZE_ivi - 4)	/* XSPI FCC Offset */
#define XSPI_FCC_LONG_OFFSET_ivi	(XSPI_FCC_OFFSET_ivi / 4)	/* XSPI FCC Offset(LONG) */

#define	XSPI_PAYLOAD_NUM_meter		(3)						/* Payload数 */
#define	XSPI_HEADER_SIZE_meter		(8)						/* header size */
#define	XSPI_PAYLOAD1_SIZE_meter		(2000)					/* payload1 size */
#define	XSPI_PAYLOAD2_SIZE_meter		(2000)					/* payload2 size */
#define	XSPI_PAYLOAD3_SIZE_meter		(1600)					/* payload3 size */

#define XSPI_CHKSUM_OFFSET_meter		(XSPI_FRAME_SIZE_meter - (XSPI_PAYLOAD_NUM_meter * 4))	/* XSPI CheckSum Offset */
#define XSPI_CHKSUM_LONG_OFFSET_meter	(XSPI_CHKSUM_OFFSET_meter / 4)	/* XSPI CheckSum Offset(LONG) */

#define	XSPI_CHKSUM_XOR_meter			(0x5a5a5a5aU)			/* CheckSum XOR */

#define XSPI_SUB_FRAME_MAX_central		(8)						/* XSPI Sub Frame MAX */
#define XSPI_SUB_FRAME_UNIT_central		(8)						/* XSPI Sub Frame UNIT */
#define XSPI_FCC_OFFSET_central			(XSPI_FRAME_SIZE_central - 4)	/* XSPI FCC Offset */
#define XSPI_FCC_LONG_OFFSET_central	(XSPI_FCC_OFFSET_central / 4)	/* XSPI FCC Offset(LONG) */

#ifdef XSPI_DEBUG
/*------------------------------*/
/*	通信エラー検出状態フラグ	*/
/*------------------------------*/
#define		XSPI_ERR_MSK_DBG		(0x7F)			/* MASK：デバッグ用エラー				*/
#define		XSPI_ERR_DBG_INTG		(0x01)			/* データ整合性エラー					*/
#define		XSPI_ERR_DBG_OVERFLOW	(0x02)			/* 受信バッファ溢れ						*/
#define		XSPI_ERR_DBG_DMAOVERRUN	(0x04)			/* DMAオーバーランエラー				*/
#define		XSPI_ERR_DBG_SLAVETIM20	(0x08)			/* Slave通信タイムアウトエラー（20ms）	*/
#define		XSPI_ERR_DBG_SLAVETIM15	(0x10)			/* Slave通信タイムアウトエラー（15ms）	*/
#define		XSPI_ERR_DBG_TX_LOCKED	(0x20)			/* 送信バッファロックエラー 			*/
#define		XSPI_ERR_DBG_RX_LOCKED	(0x40)			/* 受信バッファロックエラー 			*/
#endif /* XSPI_DEBUG */

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
	uint8	dummy[2];					/* alignment dummy */

	/* 送信管理情報(ダブルバッファ) */
	struct {
		struct {
			uint8	dat[XSPI_FRM_MAX];	/* 送信データ領域 */
		} page[XSPI_BUF_PAGE];
		uint8	page_inf;				/* ページ情報（bit0:ユーザー公開/ドライバ送信, bit1:ロック） */
		uint8	dummy[3];				/* alignment dummy */
	} snd;
	/* 受信管理情報(ダブルバッファ) */
	struct {
		struct {
			uint8	dat[XSPI_FRM_MAX];	/* 受信データ領域 */
		} page[XSPI_BUF_PAGE];
		uint8	page_inf;				/* ページ情報（bit0:ユーザー公開/ドライバ受信, bit1:ロック） */
		uint8	dummy[3];				/* alignment dummy */
	} rcv;

} BF_DRV_SPI_DOUBLE;

typedef struct {
	uint8	stat;						/* 遷移状態 */
	uint8	err_info;					/* エラー通知管理用 */
	uint8	dummy[2];					/* alignment dummy */

	/* 送信管理情報(リングバッファ) */
	struct {
		uint8   page_task;				/* タスク用送信バッファ書き込みページ	*/
		uint8   page_drv;				/* ドライバ用送信バッファページ	*/
		uint8	page_send;				/* ドライバ送信中のページ（空ページも含めて） */
		uint8	dummy[1];				/* alignment dummy */
		struct {
			uint8	dat[XSPI_FRM_MAX];	/* 送信データ領域 */
			uint8	inf;				/* 送信ページデータ有(1)／無(0) */
			uint8	dummy[3];			/* alignment dummy */
		} page[XSPI_SND_PAGE + 1];
	} snd;
	/* 受信管理情報(リングバッファ) */
	struct {
		uint8   page_task;				/* タスク用受信バッファ書き込みページ	*/
		uint8   page_drv;				/* ドライバ用受信バッファページ	*/
		uint8	page_rcv;				/* ドライバ受信中のページ（空ページも含めて） */
		uint8	dummy[1];				/* alignment dummy */
		struct {
			uint8	dat[XSPI_FRM_MAX];	/* 受信データ領域 */
			uint8	inf;				/* 受信ページデータ有(1)／無(0) */
			uint8	dummy[3];			/* alignment dummy */
		} page[XSPI_RCV_PAGE + 1];
	} rcv;

} BF_DRV_SPI_RING;

/*------------------------------*/
/*	ドライバ管理テーブル		*/
/*------------------------------*/
typedef struct {
	void(*func)(void);					/* イベント処理関数アドレス */
	uint8	next_stat;					/* 処理後の状態 */
} TBL_DRV_SPI;

#endif	/* XSPI_INTERNAL_H */
