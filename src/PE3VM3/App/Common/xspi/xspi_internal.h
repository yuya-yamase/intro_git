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
#include "Spi_Ucfg.h"
#include "gpt_drv_ost.h"

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
	CMDRV_EVT_NORMAL,				/* 通常動作(Frame信号) */
	CMDRV_EVT_N_NEXT,				/* 通信継続(Frame信号) */
	CMDRV_EVT_TIMEOUT,				/* 転送未完了タイムアウト */
	CMDRV_EVT_ENHIGH,				/* EN信号High */
	CMDRV_EVT_ENLOW,				/* EN信号Low */
	CMDRV_EVT_COMEND,				/* 通信終了 */
	CMDRV_EVT_MAX
};

/*------------------------------*/
/*	通信中呼び出しカウンタ状態	*/
/*------------------------------*/
#define	CMDRV_COM_TIME_0	(0)		/* 通信中呼び出しカウント 通信中0     */
#define	CMDRV_COM_TIME_1	(1)		/* 通信中呼び出しカウント 通信中1     */
#define	CMDRV_COM_TIME_2	(2)		/* 通信中呼び出しカウント 通信中2     */
#define	CMDRV_COM_TIMEOUT	(3)		/* 通信中呼び出しカウント 通信中最大値 */

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
/*	OSTM制御関連				*/
/*------------------------------*/
#define XSPI_OST_START_CTRL	(uint32)GPT_OST_START_CTRL_BIT_IRQ_EN |(uint32)GPT_OST_START_CTRL_BIT_TRG_ST	/* GPT_OST_START_CTRL */
#define XSPI_OST_CNT_INIT	((uint32)( 1000UL * GPT_OST_1US ))	/* 初期化用（1.0ms） */
#define XSPI_OST_CNT_COMEND	((uint32)( 400UL * GPT_OST_1US ))	/* 通信終了用（0.4ms） */

#if ( XSPI_COMM_CYCLE == XSPI_COMM_CYCLE_5ms )

#define XSPI_OST_CNT_NORMAL	((uint32)( 1600UL * GPT_OST_1US ))	/* 通常動作用（1.6ms） */
#define XSPI_OST_CNT_ENMONI	((uint32)( 5000UL * GPT_OST_1US ))	/* EN信号監視用（5.0ms） */
#define XSPI_OST_CNT_N_NEXT	((uint32)( 2000UL * GPT_OST_1US ))	/* 通信継続用（2.0ms） */

#else	/* (XSPI_COMM_CYCLE == XSPI_COMM_CYCLE_10ms) */

#define XSPI_OST_CNT_NORMAL	((uint32)( 9600UL * GPT_OST_1US ))	/* 通常動作用（9.6ms） */
#define XSPI_OST_CNT_ENMONI	((uint32)( 10000UL * GPT_OST_1US ))	/* EN信号監視用（10.0ms） */
#define XSPI_OST_CNT_N_NEXT	((uint32)( 5000UL * GPT_OST_1US ))	/* 通信継続用（5.0ms） */

#endif	/* (XSPI_COMM_CYCLE) */

/*------------------------------*/
/*	バッファ制御関連			*/
/*------------------------------*/
#if ( XSPI_DATA_BUFFER == XSPI_DATA_BUFFER_DOUBLE )

#define XSPI_BUF_PAGE_0			(0x00)			/* バッファページ0 */
#define XSPI_BUF_PAGE_1			(0x01)			/* バッファページ1 */
#define XSPI_BUF_PAGE_LOCK		(0x02)			/* バッファページロック */
#define XSPI_BUF_PAGE			(2)				/* バッファページ数 */

#else	/* (XSPI_DATA_BUFFER == XSPI_DATA_BUFFER_RING) */

#define	SND_FRM_DATA_NON		(0x00)			/* 送信ページデータ無し */
#define	SND_FRM_DATA_FIX		(0x01)			/* 送信ページデータ確定 */
#define	RCV_FRM_DATA_NON		(0x00)			/* 受信ページデータ無し */
#define	RCV_FRM_DATA_FIX		(0x01)			/* 受信ページデータ確定 */

#endif	/* (XSPI_DATA_BUFFER) */

/*------------------------------*/
/*	整合性データチェック関連	*/
/*------------------------------*/
#if (XSPI_DATA_CHECK == XSPI_DATA_CHECK_FCC)

#define XSPI_SUB_FRAME_MAX		(8)						/* XSPI Sub Frame MAX */
#define XSPI_SUB_FRAME_UNIT		(8)						/* XSPI Sub Frame UNIT */
#define XSPI_FCC_OFFSET			(XSPI_FRAME_SIZE - 4)	/* XSPI FCC Offset */
#define XSPI_FCC_LONG_OFFSET	(XSPI_FCC_OFFSET / 4)	/* XSPI FCC Offset(LONG) */

#elif (XSPI_DATA_CHECK == XSPI_DATA_CHECK_SUM)
#ifdef XSPI_CHECK_SUM_CENTRAL
	#define	XSPI_PAYLOAD_NUM		(1)						/* Payload数 */
	#define	XSPI_HEADER_SIZE		(8)						/* header size */
	#define	XSPI_PAYLOAD1_SIZE		(1200)					/* payload1 size */
#else
	#define	XSPI_PAYLOAD_NUM		(3)						/* Payload数 */
	#define	XSPI_HEADER_SIZE		(8)						/* header size */
	#define	XSPI_PAYLOAD1_SIZE		(2000)					/* payload1 size */
	#define	XSPI_PAYLOAD2_SIZE		(2000)					/* payload2 size */
	#define	XSPI_PAYLOAD3_SIZE		(1600)					/* payload3 size */
#endif	/* XSPI_CHECK_SUM_CENTRAL */

#define XSPI_CHKSUM_OFFSET		(XSPI_FRAME_SIZE - (XSPI_PAYLOAD_NUM * 4))	/* XSPI CheckSum Offset */
#define XSPI_CHKSUM_LONG_OFFSET	(XSPI_CHKSUM_OFFSET / 4)	/* XSPI CheckSum Offset(LONG) */

#define	XSPI_CHKSUM_XOR			(0x5a5a5a5aU)			/* CheckSum XOR */

#endif	/* (XSPI_DATA_CHECK) */

#ifdef XSPI_DEBUG
/*------------------------------*/
/*	通信エラー検出状態フラグ	*/
/*------------------------------*/
#define		XSPI_ERR_MSK_DBG			(0x7F)		/* MASK：デバッグ用エラー				*/
#define		XSPI_ERR_DBG_INTG			(0x01)		/* データ整合性エラー					*/
#define		XSPI_ERR_DBG_OVERFLOW		(0x02)		/* 受信バッファ溢れ						*/
#define		XSPI_ERR_DBG_DMAOVERRUN		(0x04)		/* DMAオーバーランエラー				*/
#define		XSPI_ERR_DBG_SLAVETIM		(0x08)		/* Slave通信タイムアウトエラー（CLK出力あり）	*/
#define		XSPI_ERR_DBG_SLAVETIM_NOCLK	(0x10)		/* Slave通信タイムアウトエラー（CLK出力なし）	*/
#define		XSPI_ERR_DBG_TX_LOCKED		(0x20)		/* 送信バッファロックエラー 			*/
#define		XSPI_ERR_DBG_RX_LOCKED		(0x40)		/* 受信バッファロックエラー 			*/
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
#if ( XSPI_DATA_BUFFER == XSPI_DATA_BUFFER_DOUBLE )
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
#else	/* XSPI_DATA_BUFFER == XSPI_DATA_BUFFER_RING */
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
#endif	/* XSPI_DATA_BUFFER */

} BF_DRV_SPI;

/*------------------------------*/
/*	ドライバ管理テーブル		*/
/*------------------------------*/
typedef struct {
	uint8(*func)(void);					/* イベント処理関数アドレス */
	uint8	next_stat;					/* 処理後の状態 */
	uint32	ostm_cnt;					/* OSTMカウント */
} TBL_DRV_SPI;

#endif	/* XSPI_INTERNAL_H */
