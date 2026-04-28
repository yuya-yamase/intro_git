/***************************************************************************/
/*【ファイル名】xspi.h                                                */
/***************************************************************************/
#ifndef XSPI_H
#define XSPI_H

/****************************
*		include	files		*
****************************/
#include <Std_Types.h>

/************************************************************************
*																		*
*				Ｄefine Ｄeclare Ｓection								*
*																		*
************************************************************************/
/*------------------------------*/
/*	通信フレーム最大長			*/
/*------------------------------*/
#define XSPI_FRM_MAX				(1512UL)			/* フレーム最大長		*/
#define XSPI_FRM_MAX_WORD			(XSPI_FRM_MAX / 4)	/* フレーム最大長（4byte単位） */
#define XSPI_RCV_FRM_MAX			(XSPI_FRM_MAX_WORD)	/* 受信フレーム最大長	*/
#define XSPI_SND_FRM_MAX			(XSPI_FRM_MAX_WORD)	/* 送信フレーム最大長	*/

/*------------------------------*/
/*	チャネルID					*/
/*------------------------------*/
#define		XSPI_CH_01				(0x00)			/* XSPIチャネルID：01（IVI向け）	*/
#define		XSPI_CH_02				(0x01)			/* XSPIチャネルID：02（METER向け）	*/
#define		XSPI_CH_03				(0x02)			/* XSPIチャネルID：03（CENTRAL向け）*/

/*------------------------------*/
/*	XSPIドライバ状態			*/
/*------------------------------*/
#define		XSPI_DCOND_INIT			(0x00)			/* 初期化前					*/
#define		XSPI_DCOND_INVALID		(0x01)			/* 通信無効（EN信号Low）	*/
#define		XSPI_DCOND_IDLE			(0x02)			/* アイドル（EN信号High）	*/
#define		XSPI_DCOND_TRANSMIT		(0x03)			/* 送受信中					*/

/*------------------------------*/
/*	通信エラー検出状態フラグ	*/
/*------------------------------*/
#define		XSPI_ERR_MSK_KIND			(0x7F)		/* MASK：エラー種別 */
#define		XSPI_ERR_KIND_NONE			(0x00)		/* エラー無し       */
#define		XSPI_ERR_KIND_TRX			(0x01)		/* 送受信エラー     */
#define		XSPI_ERR_KIND_INTG			(0x02)		/* データ整合性エラー */
#define		XSPI_ERR_KIND_ENCHG			(0x04)		/* EN信号変化		*/
#define		XSPI_ERR_KIND_TIM			(0x08)		/* 通信時間オーバ	*/
#define		XSPI_ERR_KIND_RX_BUF_OVF	(0x10)		/* 受信バッファオーバーフロー */
#define		XSPI_ERR_KIND_RX_BUF_EMPTY	(0x20)		/* 受信バッファ空 */
#define		XSPI_ERR_KIND_ARG			(0x40)		/* 引数値不正 */

/*------------------------------*/
/*	XSPI異常判定フラグ			*/
/*------------------------------*/
#define	XSPI_NG						(0x00)			/* 異常 */
#define	XSPI_OK						(0x01)			/* 正常 */

/*------------------------------*/
/*	外部API						*/
/*------------------------------*/
extern void		xspi_Init( const uint8 ch );					/* XSPI通信ドライバ初期化処理 */
extern void		xspi_DeInit( const uint8 ch );				/* XSPI通信ドライバ終了処理 */
extern uint8	xspi_GetCondition( const uint8 ch );			/* XSPI通信ドライバ状態取得処理 */
extern uint8	xspi_Write( const uint8 ch, const uint32* const addr, const uint32 word_size );	/* 送信データ書き込み処理 */
extern uint8	xspi_Read( const uint8 ch, uint32* const addr, const uint32 word_size );	/* 受信データ読み出し処理 */
extern void		xspi_Main( const uint8 ch );					/* XSPI通信ドライバメイン処理 */
extern uint8	xspi_GetErrInfo( const uint8 ch );			/* XSPI通信ドライバエラー情報取得処理 */

#endif	/* XSPI_H */
