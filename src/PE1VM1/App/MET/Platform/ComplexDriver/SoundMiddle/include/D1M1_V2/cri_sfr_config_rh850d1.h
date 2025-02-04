/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2020 CRI Middleware Co., Ltd.
 *
 * Library  : CRI SFR Config
 * Module   : Library User's Header for RH850D1(p003)
 * File     : cri_sfr_config_rh850d1.h
 *
 ****************************************************************************/
/*!
 *	\file		cri_sfr_config_rh850d1.h
 */

/* 多重定義防止					*/
/* Prevention of redefinition	*/
#ifndef CRI_SFR_CONFIG_RH850D1_H_INCLUDED
#define CRI_SFR_CONFIG_RH850D1_H_INCLUDED

/***************************************************************************
 *      インクルードファイル;
 *      Include files
 ***************************************************************************/
#include <cri_xpt.h>

/***************************************************************************
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/
/*JP
 * \brief サウンド出力の最大チャンネル数
 * \ingroup SFRCONFIG_RH850D1
 * \par 説明:
 * サウンド出力可能な最大チャンネル数を表します。<br>
 */
#define CRISFRCONFIG_DEFAULT_MAX_CHANNELS	(1)

/***************************************************************************
 *      処理マクロ
 *      Macro Functions
 ***************************************************************************/

/***************************************************************************
 *      データ型宣言
 *      Data Type Declarations
 ***************************************************************************/
/*==========================================================================
 *      CRI SFR Config API
 *=========================================================================*/
/*JP
 * \brief DMAC初期化ドライバ関数
 * \ingroup SFRCONFIG_RH850D1
 * \param[in]	read_head	リード領域の先頭位置
 * \param[in]	read_size	リード領域のサイズ
 * \par 説明:
 * DMACの利用に先立つタイミングでコールバックされるドライバ関数です。<br>
 * 回路に必要な初期化を行ってください。<br>
 * 本関数の引数でDMACのリード領域が通知されます。該当領域をハードウェア機能で
 * ガードしている場合にはガードを解除してください。
 * \sa CriSfrDrvConfig_Rh850d1, CriSfrDrvDmacFinalizeFunc, CriSfrDrvDmacStartFunc, CriSfrDrvDmacIntrFunc, CriSfrDrvDmacStopFunc
 */
typedef void (CRIAPI *CriSfrDrvDmacInitializeFunc)(CriUint32 read_head, CriUint32 read_size);

/* 旧バージョンとの互換性維持用 */
typedef CriSfrDrvDmacInitializeFunc CriSfrDrv_DmacInitialize;

/*JP
 * \brief DMAC終了処理ドライバ関数
 * \ingroup SFRCONFIG_RH850D1
 * \par 説明:
 * DMACの利用を終えるタイミングでコールバックされるドライバ関数です。<br>
 * 回路に必要な終了処理を行ってください。
 * \sa CriSfrDrvConfig_Rh850d1, CriSfrDrvDmacInitializeFunc, CriSfrDrvDmacStartFunc, CriSfrDrvDmacIntrFunc, CriSfrDrvDmacStopFunc
 */
typedef void (CRIAPI *CriSfrDrvDmacFinalizeFunc)(void);

/* 旧バージョンとの互換性維持用 */
typedef CriSfrDrvDmacFinalizeFunc CriSfrDrv_DmacFinalize;

/*JP
 * \brief DMAC開始ドライバ関数
 * \ingroup SFRCONFIG_RH850D1
 * \param[in]	dsa			DSAレジスタ設定値
 * \param[in]	dda			DDAレジスタ設定値
 * \param[in]	dtc			DTCレジスタ設定値
 * \param[in]	dtct		DTCTレジスタ設定値
 * \param[in]	drsa		DRSAレジスタ設定値
 * \param[in]	drda		DRDAレジスタ設定値
 * \param[in]	drtc		DRTCレジスタ設定値
 * \param[in]	dtcc		DTCCレジスタ設定値
 * \param[in]	dtfr		DTFRレジスタ設定値
 * \par 説明:
 * DMACによる転送を開始するタイミングでコールバックされるドライバ関数です。<br>
 * 本関数の引数で指定された内容で各レジスタを設定し、割り込み許可をした後に
 * DMAC転送を開始してください。
 * \par 備考:
 * ::CriSfrDrvDmacInitializeFunc の呼び出し後 ::CriSfrDrvDmacFinalizeFunc 呼び出しまでの
 * 期間で呼び出される可能性があります。
 * \sa CriSfrDrvConfig_Rh850d1, CriSfrDrvDmacInitializeFunc, CriSfrDrvDmacFinalizeFunc, CriSfrDrvDmacIntrFunc, CriSfrDrvDmacStopFunc
 */
typedef void (CRIAPI *CriSfrDrvDmacStartFunc)(CriUint32 dsa, CriUint32 dda, CriUint32 dtc, CriUint32 dtct, CriUint32 drsa, CriUint32 drda, CriUint32 drtc, CriUint32 dtcc, CriUint32 dtfr);

/* 旧バージョンとの互換性維持用 */
typedef CriSfrDrvDmacStartFunc CriSfrDrv_DmacStart;

/*JP
 * \brief DMAC割込ドライバ関数
 * \ingroup SFRCONFIG_RH850D1
 * \param[in]	drsa		DRSAレジスタ設定値
 * \param[in]	drda		DRDAレジスタ設定値
 * \param[in]	drtc		DRTCレジスタ設定値
 * \par 説明:
 * DMACによる割り込みハンドラからコールバックされるドライバ関数です。<br>
 * 本関数の引数で指定されたリロード内容で各レジスタを設定してください。
 * \par 備考:
 * ::CriSfrDrvDmacInitializeFunc の呼び出し後 ::CriSfrDrvDmacFinalizeFunc 呼び出しまでの
 * 期間で呼び出される可能性があります。
 * \attention
 * 割り込みハンドラ内からのみ呼び出されます。
 * \sa CriSfrDrvConfig_Rh850d1, CriSfrDrvDmacInitializeFunc, CriSfrDrvDmacFinalizeFunc, CriSfrDrvDmacStartFunc, CriSfrDrvDmacStopFunc
 */
typedef void (CRIAPI *CriSfrDrvDmacIntrFunc)(CriUint32 drsa, CriUint32 drda, CriUint32 drtc);

/* 旧バージョンとの互換性維持用 */
typedef CriSfrDrvDmacIntrFunc CriSfrDrv_DmacIntr;

/*JP
 * \brief DMAC停止ドライバ関数
 * \ingroup SFRCONFIG_RH850D1
 * \par 説明:
 * DMACによる転送を停止するタイミングでコールバックされるドライバ関数です。<br>
 * 割り込み許可の解除をして、DMAC転送を停止してください。
 * \par 備考:
 * ::CriSfrDrvDmacInitializeFunc の呼び出し後 ::CriSfrDrvDmacFinalizeFunc 呼び出しまでの
 * 期間で呼び出される可能性があります。
 * \sa CriSfrDrvConfig_Rh850d1, CriSfrDrvDmacInitializeFunc, CriSfrDrvDmacFinalizeFunc, CriSfrDrvDmacStartFunc, CriSfrDrvDmacIntrFunc
 */
typedef void (CRIAPI *CriSfrDrvDmacStopFunc)(void);

/* 旧バージョンとの互換性維持用 */
typedef CriSfrDrvDmacStopFunc CriSfrDrv_DmacStop;

/*JP
 * \brief PCMP初期化ドライバ関数
 * \ingroup SFRCONFIG_RH850D1
 * \param[in]	tpwm		TPWMレジスタ設定値
 * \param[in]	cksel		CKSELレジスタ設定値
 * \param[in]	offs		OFFSレジスタ設定値
 * \par 説明:
 * PCMPの利用に先立つタイミングでコールバックされるドライバ関数です。<br>
 * 本関数の引数で指定された内容で各レジスタを設定し、回路に必要な初期化を行ってください。
 * \sa CriSfrDrvConfig_Rh850d1, CriSfrDrvPcmpFinalizeFunc, CriSfrDrvPcmpStartFunc, CriSfrDrvPcmpStopFunc
 */
typedef void (CRIAPI *CriSfrDrvPcmpInitializeFunc)(CriUint32 tpwm, CriUint32 cksel, CriUint32 offs);

/* 旧バージョンとの互換性維持用 */
typedef CriSfrDrvPcmpInitializeFunc CriSfrDrv_PcmpInitialize;

/*JP
 * \brief PCMP終了処理ドライバ関数
 * \ingroup SFRCONFIG_RH850D1
 * \par 説明:
 * PCMPの利用を終えるタイミングでコールバックされるドライバ関数です。
 * 回路に必要な終了処理を行ってください。
 * \par 備考:
 * ::CriSfrDrvPcmpInitializeFunc の呼び出し後 ::CriSfrDrvPcmpFinalizeFunc 呼び出しまでの
 * 期間で呼び出される可能性があります。
 * \sa CriSfrDrvConfig_Rh850d1, CriSfrDrvPcmpInitializeFunc, CriSfrDrvPcmpStartFunc, CriSfrDrvPcmpStopFunc
 */
typedef void (CRIAPI *CriSfrDrvPcmpFinalizeFunc)(void);

/* 旧バージョンとの互換性維持用 */
typedef CriSfrDrvPcmpFinalizeFunc CriSfrDrv_PcmpFinalize;

/*JP
 * \brief PCMP開始ドライバ関数
 * \ingroup SFRCONFIG_RH850D1
 * \param[in]	ausa		AUSAレジスタ初期設定値(2回連続ストア)
 * \param[in]	ctl			CTLレジスタ設定値(変換開始の設定値を含む)
 * \par 説明:
 * PCMPによる変換を開始するタイミングでコールバックされるドライバ関数です。<br>
 * 本関数の引数で指定された内容で各レジスタを設定し、変換を開始してください。<br>
 * \par 備考:
 * ::CriSfrDrvPcmpInitializeFunc の呼び出し後 ::CriSfrDrvPcmpFinalizeFunc 呼び出しまでの
 * 期間で呼び出される可能性があります。
 * \attention
 * AUSAレジスタはデータ長が2のFIFOであるため同値を2回連続でストアする必要があります。
 * \sa CriSfrDrvConfig_Rh850d1, CriSfrDrvPcmpInitializeFunc, CriSfrDrvPcmpFinalizeFunc, CriSfrDrvPcmpStopFunc
 */
typedef void (CRIAPI *CriSfrDrvPcmpStartFunc)(CriUint32 ausa, CriUint32 ctl);

/* 旧バージョンとの互換性維持用 */
typedef CriSfrDrvPcmpStartFunc CriSfrDrv_PcmpStart;

/*JP
 * \brief PCMP停止ドライバ関数
 * \ingroup SFRCONFIG_RH850D1
 * \par 説明:
 * PCMPによる変換を停止するタイミングでコールバックされるドライバ関数です。<br>
 * 変換を停止してください。
 * \par 備考:
 * ::CriSfrDrvPcmpInitializeFunc の呼び出し後 ::CriSfrDrvPcmpFinalizeFunc 呼び出しまでの
 * 期間で呼び出される可能性があります。
 * \sa CriSfrDrvConfig_Rh850d1, CriSfrDrvPcmpInitializeFunc, CriSfrDrvPcmpFinalizeFunc, CriSfrDrvPcmpStartFunc
 */
typedef void (CRIAPI *CriSfrDrvPcmpStopFunc)(void);

/* 旧バージョンとの互換性維持用 */
typedef CriSfrDrvPcmpStopFunc CriSfrDrv_PcmpStop;

/*JP
 * \brief 割込み禁止ドライバ関数
 * \ingroup SFRCONFIG_RH850D1
 * \par 説明:
 * EIレベル・マスカブル例外を禁止するタイミングでコールバックされるドライバ関数です。<br>
 * 割込み禁止を設定してください。
 * \par 備考:
 * ::CriSfrDrvIntrEnableFunc が呼び出される前に、必ず本関数が呼び出されます。
 * \sa CriSfrDrvConfig_Rh850d1, CriSfrDrvIntrEnableFunc
 */
typedef void (CRIAPI *CriSfrDrvIntrDisableFunc)(void);

/*JP
 * \brief 割込み許可ドライバ関数
 * \ingroup SFRCONFIG_RH850D1
 * \par 説明:
 * EIレベル・マスカブル例外を許可するタイミングでコールバックされるドライバ関数です。<br>
 * 割込み許可を設定してください。
 * \par 備考:
 * ::CriSfrDrvIntrDisableFunc の呼び出し後に、必ず本関数が呼び出されます。
 * \sa CriSfrDrvConfig_Rh850d1, CriSfrDrvIntrDisableFunc
 */
typedef void (CRIAPI *CriSfrDrvIntrEnableFunc)(void);

/*JP
 * \brief Damp ライブラリ用ドライバ構造体
 * \ingroup SFRCONFIG_RH850D1
 * \par 説明:
 * CRI Dampライブラリで使用するドライバを指定するための構造体です。<br>
 * <br>
 * CRI Dampライブラリは動作中にレジスタアクセスが必要になると本構造体で
 * 指定されたドライバ群を呼び出します。各ドライバは要求内容に応じて処理を
 * 行う必要があります。
 */
typedef struct CriSfrDrvConfigTag_Rh850d1
{
	/* DMACドライバ */
	CriSfrDrvDmacInitializeFunc			dmac_initialize_func;		/*JP< DMAC初期化ドライバ関数 */
	CriSfrDrvDmacFinalizeFunc			dmac_finalize_func;			/*JP< DMAC終了処理ドライバ関数 */
	CriSfrDrvDmacStartFunc				dmac_start_func;			/*JP< DMAC開始ドライバ関数 */
	CriSfrDrvDmacIntrFunc				dmac_intr_func;				/*JP< DMAC割込ドライバ関数 */
	CriSfrDrvDmacStopFunc				dmac_stop_func;				/*JP< DMAC停止ドライバ関数 */

	/* PCMPドライバ */
	CriSfrDrvPcmpInitializeFunc			pcmp_initialize_func;		/*JP< PCMP初期化ドライバ関数 */
	CriSfrDrvPcmpFinalizeFunc			pcmp_finalize_func;			/*JP< PCMP終了処理ドライバ関数 */
	CriSfrDrvPcmpStartFunc				pcmp_start_func;			/*JP< PCMP開始ドライバ関数 */
	CriSfrDrvPcmpStopFunc				pcmp_stop_func;				/*JP< PCMP停止ドライバ関数 */

	/* 割込みドライバ */
	CriSfrDrvIntrDisableFunc			intr_disable_func;			/*JP< 割込み禁止ドライバ関数 */
	CriSfrDrvIntrEnableFunc				intr_enable_func;			/*JP< 割込み許可ドライバ関数 */
} CriSfrDrvConfig_Rh850d1;

/*JP
 * \brief PWM出力方式
 * \ingroup SFRCONFIG_RH850D1
 * \par 説明:
 * PWM出力方式の指定です。
 */
typedef enum {
	CRISFRCONFIG_PWM_METHOD_NORMAL = 0,		/*JP< 通常 */
	CRISFRCONFIG_PWM_METHOD_HIGH_PRECISION,	/*JP< 高精度（CPU負荷と引き換えに誤差を軽減させます） */

	CRISFRCONFIG_PWM_METHOD_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriSfrConfigPwmMethod;

/*JP
 * \brief SFRコンフィグ構造体
 * \ingroup SFRCONFIG_RH850D1
 * \par 説明:
 * サウンド出力を行うためのハードウェア資源を指定するための構造体です。<br>
 * \attention
 * 将来的にメンバが増える可能性があるため、 使用前に必ず構造体をゼロクリアしてください。<br>
 * （構造体のメンバに不定値が入らないようご注意ください。）
 */
typedef struct CriSfrConfigTag_RH850D1 {
	/*JP
		\brief CLKFIXクロック値
		\par 説明:
		CLKFIXのクロック値を指定します。<br>
		単位は[Hz]です。アプリケーションで定めたクロック値を指定してください。<br>
	*/
	CriUint32 clkfix_clk;

	/*JP
		\brief ドライバコンフィグ
		\par 説明:
		PWM出力に使用するドライバ群を指定します。
	 */
	CriSfrDrvConfig_Rh850d1 drv;

	/*JP
		\brief PWM出力方式
		\par 説明:
		PWM出力方式を指定します。
	 */
	CriSfrConfigPwmMethod pwm_method;
} CriSfrConfig_RH850D1;

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*==========================================================================
 *      CRI SFR Config API
 *=========================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* CRI_SFR_CONFIG_RH850D1_H_INCLUDED */
