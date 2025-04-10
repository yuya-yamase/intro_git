/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2024 CRI Middleware Co.,Ltd.
 *
 * Library  : CRI Atom
 * Module   : Library User's Header for RH850U2A
 * File     : cri_atom_rh850u2a.h
 *
 ****************************************************************************/
/*!
 *	\file		cri_atom_rh850u2a.h
 */

/* 多重定義防止					*/
/* Prevention of redefinition	*/
#ifndef	CRI_ATOM_RH850U2A_H_INCLUDED
#define	CRI_ATOM_RH850U2A_H_INCLUDED

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
#include <cri_xpt.h>
#include <cri_error.h>
#include <cri_atom_at.h>
#include <cri_sfr_config_rh850u2a.h>

/***************************************************************************
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/
/*JP
 * \brief デフォルトサーバ処理の実行頻度
 * \ingroup ATOMEXLIB_RH850U2A
 * \par 説明:
 * サーバ処理を実行する頻度のデフォルト値です。
 */
#define CRIATOMEX_DEFAULT_SERVER_FREQUENCY_RH850U2A		100

/*JP
 * \brief デフォルト最大ボイス数
 * \ingroup ATOMEXLIB_RH850U2A
 * \par 説明:
 * ミキサに登録可能な最大ボイス数のデフォルト値です。
 */
#define CRIATOMEX_DEFAULT_MAX_VOICES_RH850U2A			5

/*JP
 * \brief デフォルト最大パラメータブロック数
 * \ingroup ATOMEXLIB_RH850U2A
 * \par 説明:
 * 音声再生時にパラメータ管理を行うための領域の数のデフォルト値です。
 */
#define CRIATOMEX_DEFAULT_MAX_PARAMETER_BLOCKS_RH850U2A	(1024 / 2)

/*JP
 * \brief デフォルト最大カテゴリ数
 * \ingroup ATOMEXLIB_RH850U2A
 * \par 説明:
 * アプリケーションで作成するカテゴリの数のデフォルト値です。
 */
#define CRIATOMEX_DEFAULT_MAX_CATEGORIES_RH850U2A		(16 / 2)

/*JP
 * \brief デフォルト最大再生ボイスプール数
 * \ingroup ATOMEXLIB_RH850U2A
 * \par 説明:
 * アプリケーションで同時に再生できるボイスプール数のデフォルト値です。
 */
#define CRIATOMEX_DEFAULT_MAX_PLAY_VOICE_POOLS_RH850U2A	(5)

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
 * \ingroup ATOMEXLIB_RH850U2A
 * \param[out]	p_config	ライブラリ用ドライバ構造体へのポインタ
 * \par 説明:
 * ドライバコンフィグ構造体（ ::CriAtomExDrvConfig_Rh850u2a ）に、
 * デフォルトの値をセットします。
 * \sa CriAtomExDrvConfig_Rh850u2a
 */
#define criAtomExDrv_SetDefaultConfig_Rh850u2a(p_config)		\
	{															\
		(p_config)->timer_start_func			= CRI_NULL;		\
		(p_config)->timer_stop_func				= CRI_NULL;		\
		(p_config)->timer_get_count_func		= CRI_NULL;		\
		(p_config)->timer_frequency				= 0xFFFFFFFFUL;	\
	}

/*JP
 * \brief ライブラリ初期化用コンフィグ構造体にデフォルト値をセット
 * \ingroup ATOMEXLIB_RH850U2A
 * \param[out]	p_config	初期化用コンフィグ構造体へのポインタ
 * \par 説明:
 * ::criAtomEx_Initialize_Rh850u2a 関数に設定するコンフィグ構造体
 * （ ::CriAtomExConfig_Rh850u2a ）に、デフォルトの値をセットします。<br>
 * \sa CriAtomExConfig_Rh850u2a
 */
#define criAtomEx_SetDefaultConfig_Rh850u2a(p_config)					\
	{																	\
		criAtomEx_SetDefaultConfig(&(p_config)->atom_ex);				\
		{																\
			(p_config)->atom_ex.server_frequency			= (CriFloat32)CRIATOMEX_DEFAULT_SERVER_FREQUENCY_RH850U2A; \
			(p_config)->atom_ex.max_virtual_voices			= CRIATOMEX_DEFAULT_MAX_VOICES_RH850U2A * 2;	\
			(p_config)->atom_ex.max_sequences				= 0;		\
			(p_config)->atom_ex.max_tracks					= 0;		\
			(p_config)->atom_ex.max_track_items				= 0;		\
			(p_config)->atom_ex.max_parameter_blocks		= CRIATOMEX_DEFAULT_MAX_PARAMETER_BLOCKS_RH850U2A; \
			(p_config)->atom_ex.max_categories				= CRIATOMEX_DEFAULT_MAX_CATEGORIES_RH850U2A;	\
			(p_config)->atom_ex.thread_model				= CRIATOMEX_THREAD_MODEL_SINGLE; \
		}																\
		criAtomExHcaMx_SetDefaultConfig(&(p_config)->hca_mx);			\
		{																\
			(p_config)->hca_mx.server_frequency				= (CriFloat32)CRIATOMEX_DEFAULT_SERVER_FREQUENCY_RH850U2A; \
			(p_config)->hca_mx.max_voices					= CRIATOMEX_DEFAULT_MAX_VOICES_RH850U2A;	\
		}																\
		criAtomExSoundGenerator_SetDefaultConfig(&(p_config)->sound_generator);	\
		{																\
			(p_config)->sound_generator.server_frequency	= (CriFloat32)CRIATOMEX_DEFAULT_SERVER_FREQUENCY_RH850U2A; \
		}																\
		criAtomExRawPcmFloat_SetDefaultConfig_AT(&(p_config)->raw_pcm_float); \
		{																\
			(p_config)->raw_pcm_float.server_frequency		= (CriFloat32)CRIATOMEX_DEFAULT_SERVER_FREQUENCY_RH850U2A; \
		}																\
		criAtomExRawPcmSint16_SetDefaultConfig_AT(&(p_config)->raw_pcm_sint16); \
		{																\
			(p_config)->raw_pcm_sint16.server_frequency		= (CriFloat32)CRIATOMEX_DEFAULT_SERVER_FREQUENCY_RH850U2A; \
		}																\
		criAtomExAdx_SetDefaultConfig(&(p_config)->adx); \
		{																\
			(p_config)->adx.server_frequency				= (CriFloat32)CRIATOMEX_DEFAULT_SERVER_FREQUENCY_RH850U2A; \
		}																\
		(p_config)->initialize_hca_mx					= CRI_FALSE;	\
		(p_config)->initialize_sound_generator			= CRI_TRUE;		\
		(p_config)->initialize_raw_pcm_float			= CRI_FALSE;	\
		(p_config)->initialize_raw_pcm_sint16			= CRI_TRUE;		\
		(p_config)->initialize_adx						= CRI_TRUE;		\
		(p_config)->sampling_rate						= CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE; \
		(p_config)->max_play_voice_pools				= CRIATOMEX_DEFAULT_MAX_PLAY_VOICE_POOLS_RH850U2A; \
		criSfr_SetDefaultConfig_Rh850u2a(&(p_config)->sfr_config);		\
		criAtomExDrv_SetDefaultConfig_Rh850u2a(&(p_config)->drv);		\
	}

/***************************************************************************
 *      データ型宣言
 *      Data Type Declarations
 ***************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*JP
 * \brief タイマ開始ドライバ関数
 * \ingroup ATOMEXLIB_RH850U2A
 * \par 説明:
 * タイマの利用に先立つタイミングでコールバックされるドライバ関数です。<br>
 * Free-Runningタイマが停止中なら開始してください。<br>
 * \sa CriAtomExDrvConfig_Rh850u2a, CriAtomExDrvTimerStopFunc, CriAtomExDrvTimerGetCountFunc
 */
typedef void (CRIAPI *CriAtomExDrvTimerStartFunc)(void);

/*JP
 * \brief タイマ停止ドライバ関数
 * \ingroup ATOMEXLIB_RH850U2A
 * \par 説明:
 * タイマの利用を終えるタイミングでコールバックされるドライバ関数です。<br>
 * Free-Runningタイマを停止できます。<br>
 * \sa CriAtomExDrvConfig_Rh850u2a, CriAtomExDrvTimerStartFunc, CriAtomExDrvTimerGetCountFunc
 */
typedef void (CRIAPI *CriAtomExDrvTimerStopFunc)(void);

/*JP
 * \brief タイマカウント取得ドライバ関数
 * \ingroup ATOMEXLIB_RH850U2A
 * \return		CriUint32	タイマカウント
 * \par 説明:
 * タイマカウントを取得するタイミングでコールバックされるドライバ関数です。<br>
 * タイマカウント値を返却してください。<br>
 * 本関数の戻り値と CriAtomExDrvConfig_Rh850u2a::timer_frequency から経過時間が算出されます。
 * \par 備考:
 * ::CriAtomExDrvTimerStartFunc の呼び出し後 ::CriAtomExDrvTimerStopFunc 呼び出しまでの
 * 期間で繰り返し呼び出される可能性があります。
 * \sa CriAtomExDrvConfig_Rh850u2a, CriAtomExDrvTimerStartFunc, CriAtomExDrvTimerStopFunc
 */
typedef CriUint32 (CRIAPI *CriAtomExDrvTimerGetCountFunc)(void);

/*JP
 * \brief Atom ライブラリ用ドライバ構造体
 * \ingroup ATOMEXLIB_RH850U2A
 * \par 説明:
 * CRI Atomライブラリで使用するドライバを指定するための構造体です。<br>
 * <br>
 * CRI Atomライブラリは動作中にレジスタアクセスが必要になると本構造体で
 * 指定されたドライバ群を呼び出します。各ドライバは要求内容に応じて処理を
 * 行う必要があります。
 */
typedef struct CriAtomExDrvConfigTag_Rh850u2a
{
	/* タイマドライバ */
	CriAtomExDrvTimerStartFunc				timer_start_func;			/*JP< タイマ開始ドライバ関数 */
	CriAtomExDrvTimerStopFunc				timer_stop_func;			/*JP< タイマ停止ドライバ関数 */
	CriAtomExDrvTimerGetCountFunc			timer_get_count_func;		/*JP< タイマカウント取得ドライバ関数 */
	CriUint32								timer_frequency;			/*JP< タイマ周波数[Hz] */
} CriAtomExDrvConfig_Rh850u2a;

/*JP
 * \brief Atom ライブラリ初期化パラメータ構造体
 * \ingroup ATOMEXLIB_RH850U2A
 * CRI Atomライブラリの動作仕様を指定するための構造体です。<br>
 * ::criAtomEx_Initialize_Rh850u2a 関数の引数に指定します。<br>
 * <br>
 * CRI Atomライブラリは、初期化時に本構造体で指定された設定に応じて、内部リソースを
 * 必要なだけ確保します。<br>
 * ライブラリが必要とするワーク領域のサイズは、本構造体で指定されたパラメータに応じて
 * 変化します。
 * \par 備考:
 * デフォルト設定を使用する場合、 ::criAtomEx_SetDefaultConfig_Rh850u2a 関数で構造体にデフォルト
 * パラメータをセットした後、 ::criAtomEx_Initialize_Rh850u2a 関数に構造体を指定してください。<br>
 * \attention
 * 将来的にメンバが増える可能性があるため、 ::criAtomEx_SetDefaultConfig_Rh850u2a 関数を使用しない
 * 場合には、使用前に必ず構造体をゼロクリアしてください。<br>
 * （構造体のメンバに不定値が入らないようご注意ください。）
 * \sa criAtomEx_Initialize_Rh850u2a, CriAtomExConfig, CriAtomExHcaMxConfig,
 * CriAtomExSoundGeneratorConfig, CriAtomExRawPcmFloatConfig_AT, CriAtomExDrvConfig_Rh850u2a
 */
typedef struct CriAtomExConfigTag_Rh850u2a
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
	CriSfrConfig_RH850U2A			sfr_config;					/*JP< SFRコンフィグ */
	CriAtomExDrvConfig_Rh850u2a		drv;						/*JP< AtomEx用ドライバコンフィグ */
} CriAtomExConfig_Rh850u2a;


/***************************************************************************
 *      変数宣言
 *      Prototype Variables
 ***************************************************************************/

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/

/*==========================================================================
 *      CRI Atom API
 *=========================================================================*/

/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/

/* Rh850u2a用AtomExの初期化時のワークサイズ計算 */
/*JP
 * \brief ライブラリ初期化用ワーク領域サイズの計算
 * \ingroup ATOMEXLIB_RH850U2A
 * \param[in]	config		初期化用パラメータ構造体
 * \return		CriSint32	ワーク領域サイズ
 * \par 説明:
 * ライブラリを使用するために必要な、ワーク領域のサイズを取得します。<br>
 * \par 備考:
 * ライブラリが必要とするワーク領域のサイズは、ライブラリ初期化用パラメータ
 * 構造体（ ::CriAtomExConfig_Rh850u2a ）の内容によって変化します。<br>
 * <br>
 * 引数 config の情報は、関数内でのみ参照されます。<br>
 * 関数を抜けた後は参照されませんので、関数実行後に config の領域を解放しても
 * 問題ありません。
 * \sa CriAtomExConfig_Rh850u2a, criAtomEx_Initialize_Rh850u2a
 */
CriSint32 CRIAPI criAtomEx_CalculateWorkSize_Rh850u2a(const CriAtomExConfig_Rh850u2a *config);

/*JP
 * \brief ライブラリの初期化
 * \ingroup ATOMEXLIB_RH850U2A
 * \param[in]	config		初期化用パラメータ構造体
 * \param[in]	work		ワーク領域
 * \param[in]	work_size	ワーク領域サイズ
 * \par 説明：
 * AtomExの初期化を行います。<br>
 * \attention
 * 本関数は完了復帰型の関数です。<br>
 * \sa criAtomEx_CalculateWorkSize_Rh850u2a, criAtomEx_Finalize_Rh850u2a
 */
void CRIAPI criAtomEx_Initialize_Rh850u2a(const CriAtomExConfig_Rh850u2a *config, void *work, CriSint32 work_size);

/*JP
 * \brief ライブラリの終了
 * \ingroup ATOMEXLIB_RH850U2A
 * \par 説明:
 * ライブラリを終了します。<br>
 * \attention
 * ::criAtomEx_Initialize_Rh850u2a 関数実行前に本関数を実行することはできません。<br>
 * \sa criAtomEx_Initialize_Rh850u2a
 */
void CRIAPI criAtomEx_Finalize_Rh850u2a(void);

/*JP
 * \brief 割込み定期処理
 * \ingroup ATOMEXLIB_RH850U2A
 * \par 説明:
 * 割込みごとの処理を行います。<br>
 * ライブラリ内部では割り込みハンドラを定義しないためアプリケーションで
 * 対応するDMA割込みハンドラを定義する必要があります。<br>
 * DMA転送完了時に当該DMA割込みハンドラ内から以下のように本関数を呼び出してください。<br>
 * <br>
 * \code
 * ## DMAの割込みハンドラを定義する。
 * void RsrcIntrHandler_Dma(void)
 * {
 *   ## 転送完了なら割込みハンドラから呼び出す
 *   if (DMA転送完了したか？) {
 *     criAtomEx_ExecServerIntr_Rh850u2a();
 *   }
 * }
 *	※上記仮想コード内の"##"は行末までのコメントアウト開始を示しています。
 * \endcode
 * なお、本関数でFPUは使用されません。<br>
 *
 * \attention
 * 本関数を呼び出すハンドラの優先度は、ライブラリの他関数を呼び出す
 * ハンドラよりも高い優先度を設定する必要があります。
 * \sa criAtomEx_SetDefaultConfig_Rh850u2a, criAtomEx_Initialize_Rh850u2a
 */
void CRIAPI criAtomEx_ExecServerIntr_Rh850u2a(void);

/*JP
 * \brief ライブラリで使用される変数を初期化する
 * \ingroup ATOMEXLIB_RH850U2A
 * \par 説明:
 * ライブラリ内の.bss領域、.rdata領域に配置される変数を初期化します。<br>
 * \attention
 * ビルド時に.bss, .rdataを初期化しないシステムの場合には、
 * Atomライブラリを使用する前に必ず本関数を呼び出してください。<br>
 * .bss, .rdataを初期化せず、かつ本関数も呼び出されない状態でAtomライブラリを使用した場合、
 * Atomライブラリが意図通り動作せず、システムへ重篤な問題を引き起こす可能性があります。
 */
void CRIAPI criAtomEx_PreInitialize_Rh850u2a(void);

#ifdef __cplusplus
}
#endif

#endif	/* CRI_ATOM_RH850U2A_H_INCLUDED */

/* --- end of file --- */
