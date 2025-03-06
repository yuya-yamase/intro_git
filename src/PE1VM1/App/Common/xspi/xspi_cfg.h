/***************************************************************************/
/*【ファイル名】xspi_cfg.h                                                 */
/***************************************************************************/
#ifndef XSPICFG_H
#define XSPICFG_H

/************************************************************************
*																		*
*				Ｄefine Ｄeclare Ｓection								*
*																		*
************************************************************************/

/*------------------------------------------*/
/*	XSPIデバッグ用コンパイルSW 				*/
/*------------------------------------------*/
#define XSPI_DEBUG

/*------------------------------------------*/
/*	MCAL関連								*/
/*------------------------------------------*/
#define XSPI_COMC_ID 			(SPI_COMC_ID_SOC_MCU1)		/* COM ID（MCAL/SPI） */
#define XSPI_EN_PORT 			(DIO_ID_PORT4_CH9)			/* EN端子ポート（MCAL/DIO） */
#define XSPI_FRM_PORT 			(DIO_ID_PORT10_CH13)		/* Frame端子ポート（MCAL/DIO） */
#define XSPI_SCLK_PORT 			(PORT_ID_PORT4_PIN7)		/* SCLKポート（MCAL/PORT） */
#define XSPI_TXD_PORT 			(PORT_ID_PORT4_PIN10) 		/* TXDポート（MCAL/PORT） */
#define XSPI_RXD_PORT 			(PORT_ID_PORT4_PIN6)		/* RXDポート（MCAL/PORT） */
#define XSPI_SCLK_MODE_CFG 		(PORT_MODE_CFG_P4_7_MSPI2SC)		/* SCLKポート設定値（MCAL/PORT） */
#define XSPI_TXD_MODE_CFG 		(PORT_MODE_CFG_P4_10_MSPI2SI)		/* TXDポート設定値（MCAL/PORT） */
#define XSPI_RXD_MODE_CFG 		(PORT_MODE_CFG_P4_6_MSPI2SO)		/* RXDポート設定値（MCAL/PORT） */
#define XSPI_OST_CH				(GPT_OST_CH_00)				/* OSTMチャネル（MCAL/GPT） */

/*------------------------------------------*/
/*	有効フレームサイズ						*/
/*------------------------------------------*/
#define XSPI_FRAME_SIZE			(5620UL)

/*----------------------------------------------*/
/*	送受信データバッファ方式					*/
/*	リングバッファ方式：XSPI_DATA_BUFFER_RING	*/
/*	ダブルバッファ方式：XSPI_DATA_BUFFER_DOUBLE	*/
/*----------------------------------------------*/
#define XSPI_DATA_BUFFER_RING	(0)
#define XSPI_DATA_BUFFER_DOUBLE	(1)
#define XSPI_DATA_BUFFER		(XSPI_DATA_BUFFER_DOUBLE)	/* ダブルバッファ方式 */

/*------------------------------------------*/
/*	リングバッファ用バッファページ数		*/
/*------------------------------------------*/
#if ( XSPI_DATA_BUFFER == XSPI_DATA_BUFFER_RING )
#define XSPI_RCV_PAGE			(3)		/* 送信バッファページ数 */
#define XSPI_SND_PAGE			(3)		/* 受信バッファページ数 */
#endif

/*----------------------------------------------------------------------*/
/*	データチェック方式													*/
/*	データチェックなし：XSPI_DATA_CHECK_NONE							*/
/*	データチェックあり（FCC）：XSPI_DATA_CHECK_FCC						*/
/*	データチェックあり（全領域チェックサム）：XSPI_DATA_CHECK_SUM		*/
/*----------------------------------------------------------------------*/
#define XSPI_DATA_CHECK_NONE	(0)
#define XSPI_DATA_CHECK_FCC		(1)
#define XSPI_DATA_CHECK_SUM		(2)
#define XSPI_DATA_CHECK			(XSPI_DATA_CHECK_SUM)		/* データチェックあり（全領域チェックサム） */

#endif	/* XSPICFG_H */
