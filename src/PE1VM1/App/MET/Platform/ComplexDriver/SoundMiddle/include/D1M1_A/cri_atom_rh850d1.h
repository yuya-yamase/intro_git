/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2020 CRI Middleware Co.,Ltd.
 *
 * Library  : CRI Atom
 * Module   : Library User's Header for RH850D1(p002)
 * File     : cri_atom_rh850d1.h
 *
 ****************************************************************************/
/*!
 *	\file		cri_atom_rh850d1.h
 */

/* 多重定義防止					*/
/* Prevention of redefinition	*/
#ifndef	CRI_ATOM_RH850D1_H_INCLUDED
#define	CRI_ATOM_RH850D1_H_INCLUDED

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
#include "cri_xpt.h"
#include "cri_error.h"
#include <cri_atom_at.h>
#include "cri_sfr_config_rh850d1.h"

/***************************************************************************
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/
/*JP
 * \brief デフォルトサーバ処理の実行頻度
 * \ingroup ATOMEXLIB_RH850D1
 * \par 説明:
 * サーバ処理を実行する頻度のデフォルト値です。
 */
#define CRIATOMEX_DEFAULT_SERVER_FREQUENCY_RH850D1		100

/*JP
 * \brief デフォルト最大ボイス数
 * \ingroup ATOMEXLIB_RH850D1
 * \par 説明:
 * ミキサに登録可能な最大ボイス数のデフォルト値です。
 */
#define CRIATOMEX_DEFAULT_MAX_VOICES_RH850D1			5

/*JP
 * \brief デフォルト最大パラメータブロック数
 * \ingroup ATOMEXLIB_RH850D1
 * \par 説明:
 * 音声再生時にパラメータ管理を行うための領域の数のデフォルト値です。
 */
#define CRIATOMEX_DEFAULT_MAX_PARAMETER_BLOCKS_RH850D1	(1024 / 2)

/*JP
 * \brief デフォルト最大カテゴリ数
 * \ingroup ATOMEXLIB_RH850D1
 * \par 説明:
 * アプリケーションで作成するカテゴリの数のデフォルト値です。
 */
#define CRIATOMEX_DEFAULT_MAX_CATEGORIES_RH850D1		(16 / 2)

/*JP
 * \brief デフォルト最大再生ボイスプール数
 * \ingroup ATOMEXLIB_RH850D1
 * \par 説明:
 * アプリケーションで同時に再生できるボイスプール数のデフォルト値です。
 */
#define CRIATOMEX_DEFAULT_MAX_PLAY_VOICE_POOLS_RH850D1	(5)

/***************************************************************************
 *      処理マクロ
 *      Macro Functions
 ***************************************************************************/ 

/*==========================================================================
 *      CRI Atom API
 *=========================================================================*/


/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*JP
 * \brief ライブラリ用ドライバにデフォルト値をセット
 * \ingroup ATOMEXLIB_RH850D1
 * \param[out]	p_config	ライブラリ用ドライバ構造体へのポインタ
 * \par 説明:
 * ドライバコンフィグ構造体（ ::CriAtomExDrvConfig_Rh850d1 ）に、
 * デフォルトの値をセットします。
 * \sa CriAtomExDrvConfig_Rh850d1
1 */
#define criAtomExDrv_SetDefaultConfig_Rh850d1(p_config)			\
	{															\
		(p_config)->timer_initialize_func		= CRI_NULL;		\
		(p_config)->timer_finalize_func			= CRI_NULL;		\
		(p_config)->timer_get_count_func		= CRI_NULL;		\
		(p_config)->timer_frequency				= 0xFFFFFFFFUL;	\
	}

/*JP
 * \brief ライブラリ初期化用コンフィグ構造体にデフォルト値をセット
 * \ingroup ATOMEXLIB_RH850D1
 * \param[out]	p_config	初期化用コンフィグ構造体へのポインタ
 * \par 説明:
 * ::criAtomEx_Initialize_Rh850d1 関数に設定するコンフィグ構造体
 * （ ::CriAtomExConfig_Rh850d1 ）に、デフォルトの値をセットします。<br>
 * \sa CriAtomExConfig_Rh850d1
 */
#define criAtomEx_SetDefaultConfig_Rh850d1(p_config)					\
	{																	\
		criAtomEx_SetDefaultConfig(&(p_config)->atom_ex);				\
		{																\
			(p_config)->atom_ex.server_frequency			= (CriFloat32)CRIATOMEX_DEFAULT_SERVER_FREQUENCY_RH850D1; \
			(p_config)->atom_ex.max_virtual_voices			= CRIATOMEX_DEFAULT_MAX_VOICES_RH850D1 * 2;	\
			(p_config)->atom_ex.max_sequences				= 0;		\
			(p_config)->atom_ex.max_tracks					= 0;		\
			(p_config)->atom_ex.max_track_items				= 0;		\
			(p_config)->atom_ex.max_parameter_blocks		= CRIATOMEX_DEFAULT_MAX_PARAMETER_BLOCKS_RH850D1; \
			(p_config)->atom_ex.max_categories				= CRIATOMEX_DEFAULT_MAX_CATEGORIES_RH850D1;	\
			(p_config)->atom_ex.thread_model				= CRIATOMEX_THREAD_MODEL_SINGLE; \
		}																\
		criAtomExHcaMx_SetDefaultConfig(&(p_config)->hca_mx);			\
		{																\
			(p_config)->hca_mx.server_frequency				= (CriFloat32)CRIATOMEX_DEFAULT_SERVER_FREQUENCY_RH850D1; \
			(p_config)->hca_mx.max_voices					= CRIATOMEX_DEFAULT_MAX_VOICES_RH850D1;	\
		}																\
		criAtomExSoundGenerator_SetDefaultConfig(&(p_config)->sound_generator);	\
		{																\
			(p_config)->sound_generator.server_frequency	= (CriFloat32)CRIATOMEX_DEFAULT_SERVER_FREQUENCY_RH850D1; \
		}																\
		criAtomExRawPcmFloat_SetDefaultConfig_AT(&(p_config)->raw_pcm_float); \
		{																\
			(p_config)->raw_pcm_float.server_frequency		= (CriFloat32)CRIATOMEX_DEFAULT_SERVER_FREQUENCY_RH850D1; \
		}																\
		criAtomExRawPcmSint16_SetDefaultConfig_AT(&(p_config)->raw_pcm_sint16); \
		{																\
			(p_config)->raw_pcm_sint16.server_frequency		= (CriFloat32)CRIATOMEX_DEFAULT_SERVER_FREQUENCY_RH850D1; \
		}																\
		criAtomExAdx_SetDefaultConfig(&(p_config)->adx); \
		{																\
			(p_config)->adx.server_frequency				= (CriFloat32)CRIATOMEX_DEFAULT_SERVER_FREQUENCY_RH850D1; \
		}																\
		(p_config)->initialize_hca_mx					= CRI_FALSE;	\
		(p_config)->initialize_sound_generator			= CRI_TRUE;		\
		(p_config)->initialize_raw_pcm_float			= CRI_FALSE;	\
		(p_config)->initialize_raw_pcm_sint16			= CRI_TRUE;		\
		(p_config)->initialize_adx						= CRI_TRUE;		\
		(p_config)->sampling_rate						= CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE; \
		(p_config)->max_play_voice_pools				= CRIATOMEX_DEFAULT_MAX_PLAY_VOICE_POOLS_RH850D1; \
		{																\
			(p_config)->sfr_config.clkfix_clk				= 8 * 1000 * 1000;/*High Speed IntOsc(fRH)*/ \
			(p_config)->sfr_config.drv.dmac_initialize_func	= CRI_NULL;	\
			(p_config)->sfr_config.drv.dmac_finalize_func	= CRI_NULL;	\
			(p_config)->sfr_config.drv.dmac_start_func		= CRI_NULL;	\
			(p_config)->sfr_config.drv.dmac_intr_func		= CRI_NULL;	\
			(p_config)->sfr_config.drv.dmac_stop_func		= CRI_NULL;	\
			(p_config)->sfr_config.drv.pcmp_initialize_func	= CRI_NULL;	\
			(p_config)->sfr_config.drv.pcmp_finalize_func	= CRI_NULL;	\
			(p_config)->sfr_config.drv.pcmp_start_func		= CRI_NULL;	\
			(p_config)->sfr_config.drv.pcmp_stop_func		= CRI_NULL;	\
			(p_config)->sfr_config.drv.intr_disable_func	= CRI_NULL;	\
			(p_config)->sfr_config.drv.intr_enable_func		= CRI_NULL;	\
			(p_config)->sfr_config.pwm_method				= CRISFRCONFIG_PWM_METHOD_NORMAL; \
		}																\
		criAtomExDrv_SetDefaultConfig_Rh850d1(&(p_config)->drv);		\
	}

/***************************************************************************
 *      データ型宣言
 *      Data Type Declarations
 ***************************************************************************/


/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*JP
 * \brief タイマ初期化ドライバ関数
 * \ingroup ATOMEXLIB_RH850D1
 * \par 説明:
 * タイマの利用に先立つタイミングでコールバックされるドライバ関数です。<br>
 * 回路に必要な初期化を行ってください。
 * \sa CriAtomExDrvConfig_Rh850d1, CriAtomExDrvTimerFinalizeFunc, CriAtomExDrvTimerGetCountFunc
 */
typedef void (CRIAPI *CriAtomExDrvTimerInitializeFunc)(void);

/* 旧バージョンとの互換性維持用 */
typedef CriAtomExDrvTimerInitializeFunc CriAtomExDrv_TimerInitialize;

/*JP
 * \brief タイマ終了処理ドライバ関数
 * \ingroup ATOMEXLIB_RH850D1
 * \par 説明:
 * タイマの利用を終えるタイミングでコールバックされるドライバ関数です。<br>
 * 回路に必要な終了処理を行ってください。
 * \sa CriAtomExDrvConfig_Rh850d1, CriAtomExDrvTimerInitializeFunc, CriAtomExDrvTimerGetCountFunc
 */
typedef void (CRIAPI *CriAtomExDrvTimerFinalizeFunc)(void);

/* 旧バージョンとの互換性維持用 */
typedef CriAtomExDrvTimerFinalizeFunc CriAtomExDrv_TimerFinalize;

/*JP
 * \brief タイマカウント取得ドライバ関数
 * \ingroup ATOMEXLIB_RH850D1
 * \return		CriUint32	タイマカウント
 * \par 説明:
 * タイマカウントを取得するタイミングでコールバックされるドライバ関数です。<br>
 * タイマカウント値を返却してください。<br>
 * 本関数の戻り値と CriAtomExDrvConfig_Rh850d1::timer_frequency から経過時間が算出されます。
 * \par 備考:
 * ::CriAtomExDrvTimerInitializeFunc の呼び出し後 ::CriAtomExDrvTimerFinalizeFunc 呼び出しまでの
 * 期間で呼び出される可能性があります。
 * \sa CriAtomExDrvConfig_Rh850d1, CriAtomExDrvTimerInitializeFunc, CriAtomExDrvTimerFinalizeFunc
 */
typedef CriUint32 (CRIAPI *CriAtomExDrvTimerGetCountFunc)(void);

/* 旧バージョンとの互換性維持用 */
typedef CriAtomExDrvTimerGetCountFunc CriAtomExDrv_TimerGetCount;

/*JP
 * \brief Atom ライブラリ用ドライバ構造体
 * \ingroup ATOMEXLIB_RH850D1
 * \par 説明:
 * CRI Atomライブラリで使用するドライバを指定するための構造体です。<br>
 * <br>
 * CRI Atomライブラリは動作中にレジスタアクセスが必要になると本構造体で
 * 指定されたドライバ群を呼び出します。各ドライバは要求内容に応じて処理を
 * 行う必要があります。
 */
typedef struct CriAtomExDrvConfigTag_Rh850d1
{
	/* タイマドライバ */
	CriAtomExDrvTimerInitializeFunc			timer_initialize_func;		/*JP< タイマ初期化ドライバ関数 */
	CriAtomExDrvTimerFinalizeFunc			timer_finalize_func;		/*JP< タイマ終了処理ドライバ関数 */
	CriAtomExDrvTimerGetCountFunc			timer_get_count_func;		/*JP< タイマカウント取得ドライバ関数 */
	CriUint32								timer_frequency;			/*JP< タイマ周波数[Hz] */
} CriAtomExDrvConfig_Rh850d1;

/*JP
 * \brief Atom ライブラリ初期化パラメータ構造体
 * \ingroup ATOMEXLIB_RH850D1
 * CRI Atomライブラリの動作仕様を指定するための構造体です。<br>
 * ::criAtomEx_Initialize_Rh850d1 関数の引数に指定します。<br>
 * <br>
 * CRI Atomライブラリは、初期化時に本構造体で指定された設定に応じて、内部リソースを
 * 必要なだけ確保します。<br>
 * ライブラリが必要とするワーク領域のサイズは、本構造体で指定されたパラメータに応じて
 * 変化します。
 * \par 備考:
 * デフォルト設定を使用する場合、 ::criAtomEx_SetDefaultConfig_Rh850d1 関数で構造体にデフォルト
 * パラメータをセットした後、 ::criAtomEx_Initialize_Rh850d1 関数に構造体を指定してください。<br>
 * \attention
 * 将来的にメンバが増える可能性があるため、 ::criAtomEx_SetDefaultConfig_Rh850d1 関数を使用しない
 * 場合には、使用前に必ず構造体をゼロクリアしてください。<br>
 * （構造体のメンバに不定値が入らないようご注意ください。）
 * \sa criAtomEx_Initialize_Rh850d1, CriAtomExConfig, CriAtomExHcaMxConfig,
 * CriAtomExSoundGeneratorConfig, CriAtomExRawPcmFloatConfig_AT, CriAtomExDrvConfig_Rh850d1
 */
typedef struct CriAtomExConfigTag_Rh850d1
{
	CriAtomExConfig					atom_ex;					/*JP< AtomEx初期化用コンフィグ */
	CriAtomExHcaMxConfig			hca_mx;						/*JP< HcaMx初期化用コンフィグ */
	CriAtomExSoundGeneratorConfig	sound_generator;			/*JP< SoundGenerator初期化用コンフィグ */
	CriAtomExRawPcmFloatConfig_AT	raw_pcm_float;				/*JP< RawPcmFloat初期化用コンフィグ */
	CriAtomExRawPcmSint16Config_AT	raw_pcm_sint16;				/*JP< RawPcmSint16初期化用コンフィグ */
	CriAtomExAdxConfig				adx;						/*JP< Adx初期化用コンフィグ */
	CriBool							initialize_hca_mx;			/*JP< HcaMx初期化フラグ */
	CriBool							initialize_sound_generator;	/*JP< SoundGenerator初期化フラグ */
	CriBool							initialize_raw_pcm_float;	/*JP< RawPcmFloat初期化フラグ */
	CriBool							initialize_raw_pcm_sint16;	/*JP< RawPcmSint16初期化フラグ */
	CriBool							initialize_adx;				/*JP< Adx初期化フラグ */
	CriSint32						sampling_rate;				/*JP< サンプリングレート */
	CriSint32						max_play_voice_pools;		/*JP< 最大再生ボイスプール数 */
	CriSfrConfig_RH850D1			sfr_config;					/*JP< SFRコンフィグ */
	CriAtomExDrvConfig_Rh850d1		drv;						/*JP< AtomEx用ドライバコンフィグ */
} CriAtomExConfig_Rh850d1;


/***************************************************************************
 *      変数宣言
 *      Prototype Variables
 ***************************************************************************/

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*==========================================================================
 *      CRI Atom API
 *=========================================================================*/

/*JP
 * \brief オンメモリAWBハンドルの作成
 * \ingroup ATOMLIB_RH850D1
 * \param[in]	awb_mem			AWBファイルを読み込んだメモリ領域へのポインタ
 * \param[in]	awb_mem_size	AWBファイルサイズ
 * \param[in]	work			オンメモリAWB用ワーク領域へのポインタ
 * \param[in]	work_size		オンメモリAWB用ワーク領域サイズ
 * \return		CriAtomAwbHn オンメモリAWBハンドル
 * \par 説明:
 * メモリ上に読み込まれたAWBファイルイメージから、オンメモリAWBハンドルを作成します。<br>
 * 同じオンメモリAWBファイルイメージから複数のオンメモリAWBハンドルを作成することができます。<br>
 * ワーク領域を確保する方法には、以下の2通りの方法があります。<br>
 * <b>(a) User Allocator方式</b>：メモリの確保／解放に、ユーザが用意した関数を使用する方法。<br>
 * <b>(b) Fixed Memory方式</b>：必要なメモリ領域を直接ライブラリに渡す方法。<br>
 * <br>
 * User Allocator方式を用いる場合、ユーザがワーク領域を用意する必要はありません。<br>
 * workにNULL、work_sizeに0を指定するだけで、必要なメモリを登録済みのメモリ確保関数から確保します。<br>
 * オンメモリAWBハンドル作成時に動的に確保されたメモリは、<br>
 * オンメモリAWB破棄時（ ::criAtomAwb_Release 関数実行時）に解放されます。<br>
 * Fixed Memor方式を用いる場合は、::CRIATOMAWB_WORKSIZE_FOR_LOADFROMMEMORY 関数を使って
 * 必要なワーク領域サイズを求めてください。<br>
 * ワーク領域とは異なり、awb_mem は必ずユーザの責任で管理する必要がある点には注意してください。<br>
 * <br>
 * \attention
 * 本関数が成功すると、 awb_memで渡されたメモリ領域の参照を開始します。<br>
 * なお、awb_mem で指すメモリ領域は ::criAtomAwb_Release 関数実行後に手動で解放してください。
 * \sa CRIATOMAWB_WORKSIZE_FOR_LOADFROMMEMORY,criAtomAwb_Release
 */
CriAtomAwbHn CRIAPI criAtomAwb_LoadFromMemory_Rh850d1(
	const void *awb_mem, CriSint32 awb_mem_size, void *work, CriSint32 work_size);

/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/

/* Rh850d1用AtomExの初期化時のワークサイズ計算 */
/*JP
 * \brief ライブラリ初期化用ワーク領域サイズの計算
 * \ingroup ATOMEXLIB_RH850D1
 * \param[in]	config		初期化用パラメータ構造体
 * \return		CriSint32	ワーク領域サイズ
 * \par 説明:
 * ライブラリを使用するために必要な、ワーク領域のサイズを取得します。<br>
 * \par 備考:
 * ライブラリが必要とするワーク領域のサイズは、ライブラリ初期化用パラメータ
 * 構造体（ ::CriAtomExConfig_Rh850d1 ）の内容によって変化します。<br>
 * <br>
 * 引数 config の情報は、関数内でのみ参照されます。<br>
 * 関数を抜けた後は参照されませんので、関数実行後に config の領域を解放しても
 * 問題ありません。
 * \sa CriAtomExConfig_Rh850d1, criAtomEx_Initialize_Rh850d1
 */
CriSint32 CRIAPI criAtomEx_CalculateWorkSize_Rh850d1(const CriAtomExConfig_Rh850d1 *config);

/*JP
 * \brief ライブラリの初期化
 * \ingroup ATOMEXLIB_RH850D1
 * \param[in]	config		初期化用パラメータ構造体
 * \param[in]	work		ワーク領域
 * \param[in]	work_size	ワーク領域サイズ
 * \par 説明：
 * AtomExの初期化を以下の関数を呼び出して行います。<br>
 * ::criAtomEx_Initialize_AT
 * \attention
 * 本関数は完了復帰型の関数です。<br>
 * 各種注意事項は ::criAtomEx_Initialize_AT に準じます。
 * \sa criAtomEx_CalculateWorkSize_Rh850d1, criAtomEx_Finalize_Rh850d1
 */
void CRIAPI criAtomEx_Initialize_Rh850d1(const CriAtomExConfig_Rh850d1 *config, void *work, CriSint32 work_size);

/*JP
 * \brief ライブラリの終了
 * \ingroup ATOMEXLIB_RH850D1
 * \par 説明:
 * ライブラリを終了します。<br>
 * \attention
 * ::criAtomEx_Initialize_Rh850d1 関数実行前に本関数を実行することはできません。<br>
 * \sa criAtomEx_Initialize_Rh850d1
 */
void CRIAPI criAtomEx_Finalize_Rh850d1(void);

/*JP
 * \brief 割り込みごとの処理
 * \ingroup ATOMEXLIB_RH850D1
 * \par 説明:
 * 割り込みごとの処理を行います。<br>
 * ライブラリ内部では割り込みハンドラを定義しないためアプリケーションで
 * 対応するDMAC割り込みハンドラを定義する必要があります。<br>
 * 当該DMAC割り込みハンドラ内で以下のように本関数を呼び出してください。<br>
 * <br>
 * \code
 * ## DMACの割り込みハンドラを定義する。
 * #pragma ghs interrupt(nonreentrant)
 * void intp_intdma_X_X(void)
 * {
 *   ## 割り込みハンドラ内で呼び出す
 *   criAtomEx_ExecServerIntr_Rh850d1();
 * }
 *	※上記仮想コード内の"##"は行末までのコメントアウト開始を示しています。
 * \endcode
 * \attention
 * 本関数を呼び出すハンドラの優先度は、ライブラリの他関数を呼び出す
 * ハンドラよりも高い優先度を設定する必要があります。
 * \sa criAtomEx_SetDefaultConfig_Rh850d1, criAtomEx_Initialize_Rh850d1
 */
void CRIAPI criAtomEx_ExecServerIntr_Rh850d1(void);

#ifdef __cplusplus
}
#endif

#endif	/* CRI_ATOM_RH850D1_H_INCLUDED */

/* --- end of file --- */
