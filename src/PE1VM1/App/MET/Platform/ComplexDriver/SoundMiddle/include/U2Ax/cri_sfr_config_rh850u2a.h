/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2024 CRI Middleware Co., Ltd.
 *
 * Library  : CRI SFR Config
 * Module   : Library User's Header for RH850U2A
 * File     : cri_sfr_config_rh850u2a.h
 *
 ****************************************************************************/
/*!
 *	\file		cri_sfr_config_rh850u2a.h
 */

/* 多重定義防止					*/
/* Prevention of redefinition	*/
#ifndef CRI_SFR_CONFIG_RH850U2A_H_INCLUDED
#define CRI_SFR_CONFIG_RH850U2A_H_INCLUDED

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
 * \ingroup SFRCONFIG_RH850U2A
 * \par 説明:
 * サウンド出力可能な最大チャンネル数を表します。<br>
 */
#define CRISFRCONFIG_DEFAULT_MAX_CHANNELS	(1)

/*JP
 * \brief TAUD動作クロックのデフォルト値
 * \ingroup SFRCONFIG_RH850U2A
 * \par 説明:
 * TAUD動作クロックのデフォルト値を表します。<br>
 */
#define CRISFRCONFIG_DEFAULT_TAUD_CLOCK		(80UL * 1000UL * 1000UL)

/***************************************************************************
 *      処理マクロ
 *      Macro Functions
 ***************************************************************************/
/*==========================================================================
 *      CRI SFR Config API
 *=========================================================================*/
/*JP
 * \brief SFRコンフィグ構造体にデフォルト値をセット
 * \ingroup SFRCONFIG_RH850U2A
 * \param[out]	p_config	SFRコンフィグ構造体へのポインタ
 * \par 説明:
 * SFRコンフィグ構造体
 * （ ::CriSfrConfig_RH850U2A ）に、デフォルトの値をセットします。<br>
 * \sa CriSfrConfig_RH850U2A
 */
#define criSfr_SetDefaultConfig_Rh850u2a(p_config)			\
	do { \
		(p_config)->taud_clk					= CRISFRCONFIG_DEFAULT_TAUD_CLOCK; \
		(p_config)->drv.dmac_start_func			= CRI_NULL;	\
		(p_config)->drv.dmac_intr_func			= CRI_NULL;	\
		(p_config)->drv.dmac_stop_func			= CRI_NULL;	\
		(p_config)->drv.dmac_disable_intr_func	= CRI_NULL;	\
		(p_config)->drv.dmac_enable_intr_func	= CRI_NULL;	\
		(p_config)->drv.taud_start_func			= CRI_NULL;	\
		(p_config)->drv.taud_stop_func			= CRI_NULL;	\
	} while (CRI_FALSE)

/***************************************************************************
 *      データ型宣言
 *      Data Type Declarations
 ***************************************************************************/
/*==========================================================================
 *      CRI SFR Config API
 *=========================================================================*/

/*JP
 * \brief DMA channel
 * \ingroup SFRCONFIG_RH850U2A
 * \par 説明:
 * DMAドライバで使用する各channelの定義です。<br>
 * DMAドライバ関数の引数で受け渡しされる各種テーブルデータの
 * アクセス用インデックスおよびテーブル長を示す定義です。<br>
 * \sa CriSfrDrvDmacStartFunc, CriSfrDrvDmacIntrFunc
 */
typedef enum {
	CRISFRDRVDMACH_P = 0,			/*JP< PWM出力P channel */
	CRISFRDRVDMACH_N,				/*JP< PWM出力N channel */

	CRISFRDRVDMACH_NUM
} CriSfrDrvDmaCh;

/*JP
 * \brief Descriptor ID
 * \ingroup SFRCONFIG_RH850U2A
 * \par 説明:
 * DMAドライバで使用する各ディスクリプタのIDです。<br>
 * IDはDMAドライバ関数の引数であるディスクリプタIDテーブルで受け渡しされ、
 * 転送時に利用するディスクリプタを識別するために利用します。<br>
 * \sa CriSfrDrvDmacStartFunc, CriSfrDrvDmacIntrFunc
 */
typedef enum {
	CRISFRDRVDESCRIPTORID_P_0 = 0,			/*JP< For CH P, Descriptor_0 */
	CRISFRDRVDESCRIPTORID_N_0,				/*JP< For CH N, Descriptor_0 */
	CRISFRDRVDESCRIPTORID_P_1,				/*JP< For CH P, Descriptor_1 */
	CRISFRDRVDESCRIPTORID_N_1,				/*JP< For CH N, Descriptor_1 */

	CRISFRDRVDESCRIPTOR_NUM
} CriSfrDrvDescriptorId;

/*JP
 * \brief Dmac開始ドライバ関数
 * \ingroup SFRCONFIG_RH850U2A
 * \param[in]	src_addr_tbl		転送元アドレステーブル
 * \param[in]	descriptor_id_tbl	ディスクリプタIDテーブル
 * \param[in]	transfer_count		転送回数
 * \par 説明:
 * Dmac転送を開始するタイミングでコールバックされるドライバ関数です。<br>
 * TAUDのMaster/Slaveへ転送を行う３つすべてのチャネルの
 * DMA転送を開始してください。<br>
 * ::CriSfrDrvDmaCh でアクセスできるsrc_addr_tbl内のアドレスを
 * ディスクリプタのSARに設定してください。<br>
 * 各チャネルの初回動作時に利用するディスクリプタのIDが
 * ::CriSfrDrvDmaCh ごとにdescriptor_id_tblで指定されます。<br>
 * 指定されたIDに対応するディスクリプタへのポインタを
 * DMAjDPPTR_n.PTRに書き込んでください。<br>
 * transfer_countの転送回数で ::CRISFRDRVDMACH_P ,
 * ::CRISFRDRVDMACH_N のディスクリプタステップが終了するように
 * ディスクリプタのTSRに設定してください。<br>
 * \sa CriSfrDrvConfig_Rh850u2a, CriSfrDrvDmacIntrFunc, CriSfrDrvDmacStopFunc
 */
typedef void (CRIAPI *CriSfrDrvDmacStartFunc)(const CriUint32 src_addr_tbl[CRISFRDRVDMACH_NUM], const CriSfrDrvDescriptorId descriptor_id_tbl[CRISFRDRVDMACH_NUM], CriUint32 transfer_count);

/*JP
 * \brief Dmac割込ドライバ関数
 * \ingroup SFRCONFIG_RH850U2A
 * \param[in]	reload_src_addr_tbl	転送元アドレスリロードテーブル
 * \param[in]	descriptor_id_tbl	ディスクリプタIDテーブル
 * \param[in]	transfer_count		転送回数
 * \par 説明:
 * Dmacの割込みハンドラ駆動のタイミングでコールバックされるドライバ関数です。<br>
 * 本関数の引数で指定された内容で各ディスクリプタを設定してください。<br>
 * ::CriSfrDrvDmaCh でアクセスできるreload_src_addr_tbl内のアドレスを
 * descriptor_id_tblで示すディスクリプタのSARにセットしてください。<br>
 * transfer_countの転送回数で ::CRISFRDRVDMACH_P , ::CRISFRDRVDMACH_N の
 * ディスクリプタステップが終了するようにdescriptor_id_tblで示す
 * ディスクリプタのTSRに設定してください。<br>
 * \attention
 * ライブラリの割込みハンドラ内からのみ呼び出されます。<br>
 * \sa CriSfrDrvConfig_Rh850u2a, CriSfrDrvDmacStartFunc, CriSfrDrvDmacStopFunc
 */
typedef void (CRIAPI *CriSfrDrvDmacIntrFunc)(const CriUint32 reload_src_addr_tbl[CRISFRDRVDMACH_NUM], const CriSfrDrvDescriptorId descriptor_id_tbl[CRISFRDRVDMACH_NUM], CriUint32 transfer_count);

/*JP
 * \brief Dmac停止ドライバ関数
 * \ingroup SFRCONFIG_RH850U2A
 * \par 説明:
 * Dmacの使用を停止するタイミングでコールバックされるドライバ関数です。<br>
 * TAUDのMaster/Slaveへ転送を行う３つすべてのチャネルの
 * DMA転送を停止してください。<br>
 * \sa CriSfrDrvConfig_Rh850u2a, CriSfrDrvDmacStartFunc, CriSfrDrvDmacIntrFunc
 */
typedef void (CRIAPI *CriSfrDrvDmacStopFunc)(void);

/*JP
 * \brief DMA割込み禁止ドライバ関数
 * \ingroup SFRCONFIG_RH850U2A
 * \par 説明:
 * DMA割込みを禁止するタイミングでコールバックされるドライバ関数です。<br>
 * DMA割込みを禁止してください。<br>
 * \par 備考:
 * ::CriSfrDrvDmacEnableIntrFunc の呼び出し前に本関数が呼び出されます。<br>
 * \sa CriSfrDrvConfig_Rh850u2a, CriSfrDrvDmacEnableIntrFunc
 */
typedef void (CRIAPI *CriSfrDrvDmacDisableIntrFunc)(void);

/*JP
 * \brief DMA割込み許可ドライバ関数
 * \ingroup SFRCONFIG_RH850U2A
 * \par 説明:
 * DMA割込みを許可するタイミングでコールバックされるドライバ関数です。<br>
 * DMA割込みを許可してください。<br>
 * \par 備考:
 * ::CriSfrDrvDmacDisableIntrFunc の呼び出し後に本関数が呼び出されます。<br>
 * \sa CriSfrDrvConfig_Rh850u2a, CriSfrDrvDmacDisableIntrFunc
 */
typedef void (CRIAPI *CriSfrDrvDmacEnableIntrFunc)(void);

/*JP
 * \brief TAUD開始ドライバ関数
 * \ingroup SFRCONFIG_RH850U2A
 * \param[in]	master_CDR		マスターチャネルCDRレジスタ用初期値
 * \param[in]	slave_CDR		スレーブチャネルCDRレジスタ用初期値
 * \par 説明:
 * TAUDの使用を開始するタイミングでコールバックされるドライバ関数です。<br>
 * TAUD動作開始前にmaster_CDRの値をマスターチャネルのTAUDnCDRmレジスタにセットしてください。<br>
 * TAUD動作開始前にslave_CDRの値をスレーブチャネルのTAUDnCDRmレジスタにセットしてください。<br>
 * Master,Slaveとして利用する3つのTAUDチャネルの動作を同時に開始してください。<br>
 * \sa CriSfrDrvConfig_Rh850u2a, CriSfrDrvTaudStopFunc
 */
typedef void (CRIAPI *CriSfrDrvTaudStartFunc)(CriUint16 master_CDR,CriUint16 slave_CDR);

/*JP
 * \brief TAUD停止ドライバ関数
 * \ingroup SFRCONFIG_RH850U2A
 * \par 説明:
 * TAUDの使用を停止するタイミングでコールバックされるドライバ関数です。<br>
 * Master,Slaveとして利用する3つのTAUDチャネルの動作を同時に停止してください。<br>
 * \sa CriSfrDrvConfig_Rh850u2a, CriSfrDrvTaudStartFunc
 */
typedef void (CRIAPI *CriSfrDrvTaudStopFunc)(void);

/*JP
 * \brief Damp ライブラリ用ドライバ構造体
 * \ingroup SFRCONFIG_RH850U2A
 * \par 説明:
 * CRI Dampライブラリで使用するドライバを指定するための構造体です。<br>
 * <br>
 * CRI Dampライブラリは動作中にレジスタアクセスが必要になると本構造体で
 * 指定されたドライバ群を呼び出します。<br>
 * 各ドライバは要求内容に応じて処理を行う必要があります。<br>
 */
typedef struct CriSfrDrvConfigTag_Rh850u2a
{
	/* DMACドライバ */
	CriSfrDrvDmacStartFunc				dmac_start_func;			/*JP< DMAC開始ドライバ関数 */
	CriSfrDrvDmacIntrFunc				dmac_intr_func;				/*JP< DMAC割込ドライバ関数 */
	CriSfrDrvDmacStopFunc				dmac_stop_func;				/*JP< DMAC停止ドライバ関数 */
	CriSfrDrvDmacDisableIntrFunc		dmac_disable_intr_func;		/*JP< 割込み禁止ドライバ関数 */
	CriSfrDrvDmacEnableIntrFunc			dmac_enable_intr_func;		/*JP< 割込み許可ドライバ関数 */

	/* TAUDドライバ */
	CriSfrDrvTaudStartFunc				taud_start_func;			/*JP< TAUD開始ドライバ関数 */
	CriSfrDrvTaudStopFunc				taud_stop_func;				/*JP< TAUD停止ドライバ関数 */
} CriSfrDrvConfig_Rh850u2a;

/*JP
 * \brief SFRコンフィグ構造体
 * \ingroup SFRCONFIG_RH850U2A
 * \par 説明:
 * サウンド出力を行うためのハードウェア資源を指定するための構造体です。<br>
 * \attention
 * 将来的にメンバが増える可能性があるため、必ず ::criSfr_SetDefaultConfig_Rh850u2a 
 * で構造体にデフォルトパラメータをセットしてから使用してください。<br>
 * （構造体のメンバに不定値が入らないようご注意ください。）<br>
 * \sa criSfr_SetDefaultConfig_Rh850u2a
 */
typedef struct CriSfrConfigTag_RH850U2A {
	/*JP
		\brief TAUD動作クロック値
		\par 説明:
		TAUDの動作クロック値を指定します。<br>
		単位は[Hz]です。アプリケーションで定めたクロック値を指定してください。<br>
	*/
	CriUint32 taud_clk;

	/*JP
		\brief ドライバコンフィグ
		\par 説明:
		PWM出力に使用するドライバ群を指定します。
	 */
	CriSfrDrvConfig_Rh850u2a drv;
} CriSfrConfig_RH850U2A;

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

#endif /* CRI_SFR_CONFIG_RH850U2A_H_INCLUDED */
