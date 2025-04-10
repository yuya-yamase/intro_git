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
#define XSPI_COMC_ID 			(SPI_COMC_ID_SOC_MCU2)		/* COM ID（MCAL/SPI） */
#define XSPI_EN_PORT 			(DIO_ID_PORT4_CH1)			/* EN端子ポート（MCAL/DIO） */
#define XSPI_FRM_PORT 			(DIO_ID_PORT10_CH12)		/* Frame端子ポート（MCAL/DIO） */
#define XSPI_SCLK_PORT 			(PORT_ID_PORT24_PIN10)		/* SCLKポート（MCAL/PORT） */
#define XSPI_TXD_PORT 			(PORT_ID_PORT24_PIN12) 		/* TXDポート（MCAL/PORT） */
#define XSPI_RXD_PORT 			(PORT_ID_PORT24_PIN13)		/* RXDポート（MCAL/PORT） */
#define XSPI_SCLK_MODE_CFG 		(PORT_MODE_CFG_P24_10_MSPI3SC)	/* SCLKポート設定値（MCAL/PORT） */
#define XSPI_TXD_MODE_CFG 		(PORT_MODE_CFG_P24_12_MSPI3SI)	/* TXDポート設定値（MCAL/PORT） */
#define XSPI_RXD_MODE_CFG 		(PORT_MODE_CFG_P24_13_MSPI3SO)	/* RXDポート設定値（MCAL/PORT） */
#define XSPI_OST_CH				(GPT_OST_CH_01)				/* OSTMチャネル（MCAL/GPT） */

/*------------------------------------------*/
/*	有効フレームサイズ						*/
/*------------------------------------------*/
#define XSPI_FRAME_SIZE			(5552UL)

/*----------------------------------------------*/
/*	送受信データバッファ方式					*/
/*	リングバッファ方式：XSPI_DATA_BUFFER_RING	*/
/*	ダブルバッファ方式：XSPI_DATA_BUFFER_DOUBLE	*/
/*----------------------------------------------*/
#define XSPI_DATA_BUFFER_RING	(0)
#define XSPI_DATA_BUFFER_DOUBLE	(1)
#define XSPI_DATA_BUFFER		(XSPI_DATA_BUFFER_RING)		/* リングバッファ方式 */

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
#define XSPI_DATA_CHECK			(XSPI_DATA_CHECK_FCC)		/* データチェックあり（FCC） */

#endif	/* XSPICFG_H */
