/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2024 CRI Middleware Co., Ltd.
 *
 * Appli.   : CRI Sample Program
 * Module   : definition of hardware setting
 * File     : def_hw.h
 *
 ****************************************************************************/
#if		!defined(DEF_HW_H)
#define DEF_HW_H

/***************************************************************************
 *		インクルードファイル
 *		Include file
 ***************************************************************************/

/***************************************************************************
 *		定数マクロ
 *		Constant Macro
 ***************************************************************************/
/* タイマ周波数 */
#define HW_TIMER_FREQUENCY			(80U * 1000U * 1000U)
#define HW_TAUD_CLOCK				(80U * 1000U * 1000U)

/*======================================================================
  DMAC
  ======================================================================*/
/* [SPEC]
 * - 3つのDMACチャネルを使用します。
 * - 3つのDMACチャネルを"チャネルA","チャネルB","チャネルC"と表記します。
 * - このサンプルコードでは下記のように実際のDMACチャネルを割り当てています。
 *   - チャネルA: DMAC0 チャネル0
 *   - チャネルB: DMAC0 チャネル1
 *   - チャネルC: DMAC0 チャネル2
 * - "チャネルA"、"チャネルB"、"チャネルC"は異なるDMACチャネルである必要があります。
 * - "チャネルC"は3つのチャネルの中で最も優先度が"低い"必要があります。
 * - 使用するDMACチャネルを変更する場合は上記ご注意ください。
 * - DMACの円滑なデータ転送のためにチャネルA,チャネルBにそれぞれに二つのディスクリプタを利用します。
 * - 使用するディスクリプタメモリのポインタを設定してください。
 */
/* DMAC チャネルA */
#define HW_DMAC_CH_P					(0U)
/* DMAC チャネルB */
#define HW_DMAC_CH_N					(1U)
/* DMAC チャネルC */
#define HW_DMAC_CH_MASTER				(2U)
/* DMAC チャネルB割り込み番号 */
#define HW_DMAC_CH_N_INTR				(64U)

#if (HW_DMAC_CH_P == HW_DMAC_CH_N) \
	|| (HW_DMAC_CH_MASTER <= HW_DMAC_CH_P) \
	|| (HW_DMAC_CH_MASTER <= HW_DMAC_CH_N)
	#error Invalid combination of DMAC channels.
#endif

/* DMAC 転送要求トリガー番号 */
/* INTTAUD1I0 -> 208 */
#define HW_DMAC_TRANSFER_TRIGGER		(208U)

/* チャネルA,チャネルBの一度の転送のバイトサイズ */
#define HW_DMAC_BYTE_SIZE_PER_TRANSFER	(2U)
/* チャネルCの合計転送バイトサイズ */
#define HW_DMAC_CH_MASTER_TRNSFR_BYTE_SIZE	(0xFFFFFFFFU)

/* ディスクリプタポインタ */
#define HW_DESCRIPTOR_PTR_CH_P_0			(0U)
#define HW_DESCRIPTOR_PTR_CH_P_1			(4U)
#define HW_DESCRIPTOR_PTR_CH_N_0			(8U)
#define HW_DESCRIPTOR_PTR_CH_N_1			(12U)
#define HW_DESCRIPTOR_PTR_CH_MASTER_0		(16U)

/*======================================================================
  TAUD
  ======================================================================*/
/* TAUD マスタ チャネル */
#define HW_TAUD_CH_MASTER				(0U)
/* TAUD スレーブP チャネル */
#define HW_TAUD_CH_SLAVE_P				(1U)
/* TAUD スレーブN チャネル */
#define HW_TAUD_CH_SLAVE_N				(2U)

#if (HW_TAUD_CH_SLAVE_P == HW_TAUD_CH_SLAVE_N) \
	|| (HW_TAUD_CH_SLAVE_P <= HW_TAUD_CH_MASTER) \
	|| (HW_TAUD_CH_SLAVE_N <= HW_TAUD_CH_MASTER)
	#error Invalid combination of TAUD slave channels.
#endif

/* DMA転送先アドレス */
/*
 * HW_TAUD_CH_SLAVE_P, HW_TAUD_CH_SLAVE_Nの
 * 定義値に依存するため
 * 該当定義を変更した場合はアドレス変更が必要。
 */
#define HW_TAUD_CH_SLAVE_P_CDR_ADDR		(0xFFBF5004U)
#define HW_TAUD_CH_SLAVE_N_CDR_ADDR		(0xFFBF5008U)

#define HW_TAUD_RDT_ADDR				(0xFFBF5044U)

/*======================================================================
  TAUJ
  ======================================================================*/

#define HW_TAUJ_CH						(0U)

/***************************************************************************
 *      変数宣言
 *      Prototype Variables
 ***************************************************************************/

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/

 #endif	/* !defined(DEF_HW_H) */
/*------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                          */
/*------------------------------------------------------------------------------------------------------*/
