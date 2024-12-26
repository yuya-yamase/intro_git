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
#define XSPI_COMC_ID_ivi 			(SPI_COMC_ID_SOC_MCU2)		/* COM ID（MCAL/SPI） */
#define XSPI_EN_PORT_ivi 			(DIO_ID_PORT4_CH1)			/* EN端子ポート（MCAL/DIO） */
#define XSPI_FRM_PORT_ivi 			(DIO_ID_PORT10_CH12)		/* Frame端子ポート（MCAL/DIO） */
#define XSPI_SCLK_PORT_ivi 			(PORT_ID_PORT24_PIN10)		/* SCLKポート（MCAL/PORT） */
#define XSPI_TXD_PORT_ivi 			(PORT_ID_PORT24_PIN12) 		/* TXDポート（MCAL/PORT） */
#define XSPI_RXD_PORT_ivi 			(PORT_ID_PORT24_PIN13)		/* RXDポート（MCAL/PORT） */
#define XSPI_SCLK_MODE_CFG_ivi 		(PORT_MODE_CFG_P24_10_17)	/* SCLKポート設定値（MCAL/PORT） */
#define XSPI_TXD_MODE_CFG_ivi 		(PORT_MODE_CFG_P24_12_18)	/* TXDポート設定値（MCAL/PORT） */
#define XSPI_RXD_MODE_CFG_ivi 		(PORT_MODE_CFG_P24_13_19)	/* RXDポート設定値（MCAL/PORT） */

#define XSPI_COMC_ID_meter 			(SPI_COMC_ID_SOC_MCU1)		/* COM ID（MCAL/SPI） */
#define XSPI_EN_PORT_meter 			(DIO_ID_PORT4_CH9)			/* EN端子ポート（MCAL/DIO） */
#define XSPI_FRM_PORT_meter 		(DIO_ID_PORT10_CH13)		/* Frame端子ポート（MCAL/DIO） */
#define XSPI_SCLK_PORT_meter 		(PORT_ID_PORT4_PIN7)		/* SCLKポート（MCAL/PORT） */
#define XSPI_TXD_PORT_meter 		(PORT_ID_PORT4_PIN10) 		/* TXDポート（MCAL/PORT） */
#define XSPI_RXD_PORT_meter 		(PORT_ID_PORT4_PIN6)		/* RXDポート（MCAL/PORT） */
#define XSPI_SCLK_MODE_CFG_meter 	(PORT_MODE_CFG_P4_7_6)		/* SCLKポート設定値（MCAL/PORT） */
#define XSPI_TXD_MODE_CFG_meter 	(PORT_MODE_CFG_P4_10_7)		/* TXDポート設定値（MCAL/PORT） */
#define XSPI_RXD_MODE_CFG_meter 	(PORT_MODE_CFG_P4_6_5)		/* RXDポート設定値（MCAL/PORT） */

#define XSPI_COMC_ID_central 		(SPI_COMC_ID_SOC_MCU3)		/* COM ID（MCAL/SPI）*/
#define XSPI_EN_PORT_central 		(DIO_ID_PORT21_CH7)			/* EN端子ポート（MCAL/DIO）*/
#define XSPI_FRM_PORT_central 		(DIO_ID_PORT21_CH4)			/* Frame端子ポート（MCAL/DIO）*/
#define XSPI_SCLK_PORT_central 		(PORT_ID_PORT21_PIN0)		/* SCLKポート（MCAL/PORT） */
#define XSPI_TXD_PORT_central		(PORT_ID_PORT21_PIN1) 		/* TXDポート（MCAL/PORT） */
#define XSPI_RXD_PORT_central 		(PORT_ID_PORT21_PIN2)		/* RXDポート（MCAL/PORT） */
#define XSPI_SCLK_MODE_CFG_central 	(PORT_MODE_CFG_P21_0_11)	/* SCLKポート設定値（MCAL/PORT） */
#define XSPI_TXD_MODE_CFG_central 	(PORT_MODE_CFG_P21_1_12)	/* TXDポート設定値（MCAL/PORT） */
#define XSPI_RXD_MODE_CFG_central 	(PORT_MODE_CFG_P21_2_13)	/* RXDポート設定値（MCAL/PORT） */

/*------------------------------------------*/
/*	セクション設定(RAM配置)					*/
/*------------------------------------------*/
#define XSPI_RAM_SECTION 		".app_common_cram0_bss"

/*------------------------------------------*/
/*	有効フレームサイズ						*/
/*------------------------------------------*/
#define XSPI_FRAME_SIZE_ivi			(5552UL)
#define XSPI_FRAME_SIZE_meter		(5620UL)
#define XSPI_FRAME_SIZE_central		(5628UL)

/*----------------------------------------------*/
/*	送受信データバッファ方式					*/
/*	リングバッファ方式：XSPI_DATA_BUFFER_RING	*/
/*	ダブルバッファ方式：XSPI_DATA_BUFFER_DOUBLE	*/
/*----------------------------------------------*/
#define XSPI_DATA_BUFFER_RING	(0)
#define XSPI_DATA_BUFFER_DOUBLE	(1)

/* CAN1単コア疎通環境では設定変更禁止 */
#define XSPI_DATA_BUFFER_ivi		(XSPI_DATA_BUFFER_RING)		/* リングバッファ方式 */
#define XSPI_DATA_BUFFER_meter		(XSPI_DATA_BUFFER_DOUBLE)	/* ダブルバッファ方式 */
#define XSPI_DATA_BUFFER_central	(XSPI_DATA_BUFFER_RING)		/* リングバッファ方式 */

/*------------------------------------------*/
/*	リングバッファ用バッファページ数		*/
/*------------------------------------------*/
#define XSPI_RCV_PAGE			(3)								/* 送信バッファページ数 */
#define XSPI_SND_PAGE			(3)								/* 受信バッファページ数 */

/*----------------------------------------------------------------------*/
/*	データチェック方式													*/
/*	データチェックなし：XSPI_DATA_CHECK_NONE							*/
/*	データチェックあり（FCC）：XSPI_DATA_CHECK_FCC						*/
/*	データチェックあり（全領域チェックサム）：XSPI_DATA_CHECK_SUM		*/
/*----------------------------------------------------------------------*/
#define XSPI_DATA_CHECK_NONE	(0)
#define XSPI_DATA_CHECK_FCC		(1)
#define XSPI_DATA_CHECK_SUM		(2)

/* CAN1単コア疎通環境では設定変更禁止 */
#define XSPI_DATA_CHECK_ivi		(XSPI_DATA_CHECK_FCC)			/* データチェックあり（FCC） */
#define XSPI_DATA_CHECK_meter	(XSPI_DATA_CHECK_SUM)			/* データチェックあり（全領域チェックサム） */
#define XSPI_DATA_CHECK_central	(XSPI_DATA_CHECK_FCC)			/* データチェックあり（FCC） */

#endif	/* XSPICFG_H */
