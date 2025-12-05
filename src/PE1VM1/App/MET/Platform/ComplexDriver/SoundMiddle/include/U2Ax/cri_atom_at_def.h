/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2024 CRI Middleware Co., Ltd.
 *
 * Library  : CRI Atom
 * Module   : Definition of Library User's Header for Automotive
 * File     : cri_atom_at_def.h
 *
 ****************************************************************************/
/*!
 *	\file		cri_atom_at_def.h
 */

/* 多重定義防止					*/
/* Prevention of redefinition	*/
#ifndef CRI_INCL_CRI_ATOM_AT_DEF_H
#define CRI_INCL_CRI_ATOM_AT_DEF_H

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
#include <cri_xpt.h>

/***************************************************************************
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/
#define CRIATOM_DEFAULT_OUTPUT_CHANNELS				(1)
#define CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE		(24000)
#define CRIATOM_DEFAULT_INPUT_MAX_CHANNELS			(2)
#define CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE		(24000)
#define CRIATOM_DEFAULT_DECODE_LATENCY				(0)
#define CRIATOM_DEFAULT_DBAS_MAX_STREAMS			(8)
#define CRIATOM_SOUND_RENDERER_DEFAULT				(CRIATOM_SOUND_RENDERER_NATIVE)

/*==========================================================================
 *      CRI Atom API
 *=========================================================================*/
/*JP
 * \brief Automotive固有サウンドレンダラ識別子
 * \ingroup ATOMLIB_AT
 * \par 説明:
 * Automotive固有のサウンドレンダラ識別子です。<br>
 * CRIATOM_SOUND_RENDERER_SOUND_GENERATOR 
 * を指定して作成されたサウンドレンダラは、
 * 波形情報に従い、波形を生成して再生を行います。<br>
 * 但し、使用出来る波形データはモノラルのみです。<br>
 * \attention
 * ::criAtomExSoundGenerator_Initialize 関数にてサウンドジェネレータを
 * 初期化していない場合、本サウンドレンダラ識別子を指定した再生を
 * することは出来ません。
 * \sa CriAtomSoundRendererType
 */
#define CRIATOM_SOUND_RENDERER_SOUND_GENERATOR	(CRIATOM_SOUND_RENDERER_HW2)

/*JP
 * \brief Automotive固有サウンドレンダラ識別子
 * \ingroup ATOMLIB_AT
 * \par 説明:
 * Automotive固有のサウンドレンダラ識別子です。<br>
 * CRIATOM_SOUND_RENDERER_RAW_PCM_FLOAT 
 * を指定して作成されたサウンドレンダラは、
 * メモリ上に展開されたRawPCMデータを参照して再生を行います。<br>
 * 但し、使用出来るRawPCMデータはモノラルのみです。<br>
 * \attention
 * ::criAtomExRawPcmFloat_Initialize_AT 関数にてRawPcmFloatを初期化していない場合、
 * 本サウンドレンダラ識別子を指定した再生をすることは出来ません。
 * \sa CriAtomSoundRendererType
 */
#define CRIATOM_SOUND_RENDERER_RAW_PCM_FLOAT	(CRIATOM_SOUND_RENDERER_HW3)

/*JP
 * \brief Automotive固有サウンドレンダラ識別子
 * \ingroup ATOMLIB_AT
 * \par 説明:
 * Automotive固有のサウンドレンダラ識別子です。<br>
 * CRIATOM_SOUND_RENDERER_RAW_PCM_SINT16 
 * を指定して作成されたサウンドレンダラは、
 * メモリ上に展開されたRawPCMデータを参照して再生を行います。<br>
 * 但し、使用出来るRawPCMデータはモノラルのみです。<br>
 * \attention
 * ::criAtomExRawPcmSint16_Initialize_AT 関数にてRawPcmSint16を初期化していない場合、
 * 本サウンドレンダラ識別子を指定した再生をすることは出来ません。
 * \sa CriAtomSoundRendererType
 */
#define CRIATOM_SOUND_RENDERER_RAW_PCM_SINT16	(CRIATOM_SOUND_RENDERER_HW4)
/*JP
 * \brief Automotive固有サウンドレンダラ識別子
 * \ingroup ATOMLIB_AT
 * \par 説明:
 * Automotive固有のサウンドレンダラ識別子です。<br>
 * CRIATOM_SOUND_RENDERER_ADX
 * を指定して作成されたサウンドレンダラは、
 * メモリ上に展開されたADXデータを参照して再生を行います。<br>
 * 但し、使用出来るADXデータはモノラルのみです。<br>
 * \attention
 * ::criAtomExAdx_Initialize 関数にてAdxを初期化していない場合、
 * 本サウンドレンダラ識別子を指定した再生をすることは出来ません。
 * \sa CriAtomSoundRendererType
 */
#define CRIATOM_SOUND_RENDERER_ADX				(CRIATOM_SOUND_RENDERER_HW5)
 /*==========================================================================
 *      CRI Atom AWB API
 *=========================================================================*/
/*JP
 * \brief オンメモリAWBハンドルの作成に必要なワーク領域サイズ(Automotive向け)
 * \ingroup ATOMLIB_AWB
 * \par 説明:
 * オンメモリAWBハンドルの作成に必要なワーク領域サイズです。<br>
 * \sa criAtomAwb_LoadFromMemoryAt
 */
#define CRIATOMAWB_WORKSIZE_FOR_LOADFROMMEMORYAT	(8 * (CriSint32)sizeof(CriUintPtr))

/*==========================================================================
 *      CRI AtomEx Voice Pool API
 *=========================================================================*/
/*JP
 * \brief デフォルトボイス数
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \par 説明:
 * ボイスプール当たりのボイス数のデフォルト値です。<br>
 * ボイスプール作成時にデフォルト値設定を使用すると、
 * ::CRIATOMEX_DEFAULT_VOICES_PER_POOL 数分のボイスが確保されます。<br>
 * \sa criAtomExVoicePool_SetDefaultConfigForStandardVoicePool
 */
#define CRIATOMEX_DEFAULT_VOICES_PER_POOL	(8)

/*==========================================================================
 *      CRI AtomEx Playback API
 *=========================================================================*/
/*JP
 * \brief 無効な再生ID
 * \ingroup ATOMEXLIB_PLAYBACK
 * \par 説明:
 * ::criAtomExPlayer_Start 関数で音声の再生を開始した際、
 * ボイスリミットコントロール等によりボイスが確保できなかった場合に返される、
 * 無効な再生IDです。<br>
 * \par 備考:
 * 再生 ID を指定する API に対して本 ID をセットした場合でも、
 * エラーコールバックは発生しません。<br>
 * （何もされずに関数からリターンします。）<br>
 * そのため、 ::criAtomExPlayer_Start 関数の結果にかかわらず、
 * 再生 ID を使用した処理を常時行っても、特に問題ありません。<br>
 * \sa CriAtomExPlaybackId, criAtomExPlayer_Start
 */
#define CRIATOMEX_INVALID_PLAYBACK_ID	(0xFFFFFFFFu)

/***************************************************************************
 *      処理マクロ
 *      Macro Functions
 ***************************************************************************/
/*==========================================================================
 *      CRI Atom API
 *=========================================================================*/
/*JP
 * \brief ユーザアロケータの登録
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	p_malloc_func	メモリ確保関数
 * \param[in]	p_free_func		メモリ解放関数
 * \param[in]	p_obj			ユーザ指定オブジェクト
 * \par 説明:
 * CRI Atom ライブラリにメモリアロケータ（メモリの確保／解放関数）を登録します。<br>
 * 本マクロでアロケータを登録すると、Atomライブラリがワーク領域を必要とするタイミングで、
 * ユーザが登録したメモリ確保／解放処理が呼び出されることになります。<br>
 * その結果、ワーク領域を必要とする関数（ ::criAtomPlayer_CreateAdxPlayer 関数等）に対し、
 * 個別にワーク領域をセットする処理を省略することが可能になります。<br>
 * （ワーク領域に NULL ポインタ、ワーク領域サイズに 0 バイトを指定した場合でも、
 * アロケータからの動的メモリ確保によりライブラリが問題なく動作するようになります。）<br>
 * \par 注意:
 * メモリ確保／解放関数のポインタに NULL を指定することで、
 * アロケータの登録を解除することも可能です。<br>
 * ただし、未解放のメモリ領域が残っている状態で登録を解除すると、
 * エラーコールバックが返され、登録の解除に失敗します。<br>
 * （引き続き登録済みのアロケータが呼び出されることになります。）<br>
 * <br>
 * 本マクロは内部的に ::criAtom_SetUserMallocFunction 関数と
 * ::criAtom_SetUserFreeFunction 関数を呼び出します。<br>
 * 本関数とこれらの API を併用しないようご注意ください。<br>
 * （本関数の呼び出しにより、上記 API にセットした内容が上書きされます。）<br>
 * <br>
 * また、登録されたメモリアロケータ関数はマルスレッドモード時に複数のスレッドからコール
 * されることがあります。従って、メモリアロケート処理がスレッドセーフでない場合は独自に
 * メモリアロケート処理を排他制御する必要があります。
 */
#define criAtom_SetUserAllocator(p_malloc_func, p_free_func, p_obj)	\
{\
	criAtom_SetUserMallocFunction(p_malloc_func, p_obj);\
	criAtom_SetUserFreeFunction(p_free_func, p_obj);\
}

 /*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
 /*JP
 * \brief ユーザアロケータの登録
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	p_malloc_func	メモリ確保関数
 * \param[in]	p_free_func		メモリ解放関数
 * \param[in]	p_obj			ユーザ指定オブジェクト
 * \par 説明:
 * CRI Atom ライブラリにメモリアロケータ（メモリの確保／解放関数）を登録します。<br>
 * 本マクロでアロケータを登録すると、Atomライブラリがワーク領域を必要とするタイミングで、
 * ユーザが登録したメモリ確保／解放処理が呼び出されることになります。<br>
 * その結果、ワーク領域を必要とする関数（ ::criAtomExPlayer_Create 関数等）に対し、
 * 個別にワーク領域をセットする処理を省略することが可能になります。<br>
 * （ワーク領域に NULL ポインタ、ワーク領域サイズに 0 バイトを指定した場合でも、
 * アロケータからの動的メモリ確保によりライブラリが問題なく動作するようになります。）<br>
 * \par 注意:
 * メモリ確保／解放関数のポインタに NULL を指定することで、
 * アロケータの登録を解除することも可能です。<br>
 * ただし、未解放のメモリ領域が残っている状態で登録を解除すると、
 * エラーコールバックが返され、登録の解除に失敗します。<br>
 * （引き続き登録済みのアロケータが呼び出されることになります。）<br>
 * <br>
 * 本マクロは内部的に ::criAtom_SetUserAllocator マクロや
 * ::criAtom_SetUserMallocFunction 関数、 ::criAtom_SetUserFreeFunction
 * 関数を呼び出します。<br>
 * 本関数とこれらの API を併用しないようご注意ください。<br>
 * （本関数の呼び出しにより、上記 API にセットした内容が上書きされます。）<br>
 * <br>
 * また、登録されたメモリアロケータ関数はマルスレッドモード時に複数のスレッドからコール
 * されることがあります。従って、メモリアロケート処理がスレッドセーフでない場合は独自に
 * メモリアロケート処理を排他制御する必要があります。
 */
#define criAtomEx_SetUserAllocator(p_malloc_func, p_free_func, p_obj)	\
	criAtom_SetUserAllocator((p_malloc_func), (p_free_func), (p_obj))

/*JP
 * \brief ライブラリ初期化用コンフィグ構造体にデフォルト値をセット
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[out]	p_config	初期化用コンフィグ構造体へのポインタ
 * \par 説明:
 * ::criAtomEx_Initialize 関数に設定するコンフィグ構造体（ ::CriAtomExConfig ）に、
 * デフォルトの値をセットします。<br>
 * \sa
 * CriAtomExConfig
 */
#define criAtomEx_SetDefaultConfig(p_config)	\
{\
	(p_config)->thread_model = CRIATOMEX_THREAD_MODEL_MULTI;\
	(p_config)->server_frequency = 60.0f;\
	(p_config)->parameter_update_interval = 1;\
	(p_config)->enable_atom_sound_disabled_mode = CRI_FALSE;\
	(p_config)->max_virtual_voices = 16;\
	(p_config)->max_parameter_blocks = 1024;\
	(p_config)->max_categories = 16;\
	(p_config)->categories_per_playback = 4;\
	(p_config)->max_sequences = (p_config)->max_virtual_voices;\
	(p_config)->max_tracks = (CriUint32)((p_config)->max_virtual_voices) * 2u; \
	(p_config)->max_track_items = (CriUint32)((p_config)->max_virtual_voices) * 2u; \
	(p_config)->max_aisac_auto_modulations = 0;\
	(p_config)->max_pitch = 2400.0f;\
	(p_config)->context = NULL;\
}

/*==========================================================================
 *      CRI AtomEx HCA-MX API
 *=========================================================================*/
/*JP
 * \brief HCA-MX初期化コンフィグ構造体にデフォルト値をセット
 * \ingroup ATOMEXLIB_HCA_MX
 * \par 説明:
 * ::criAtomExHcaMx_Initialize 関数に設定するコンフィグ構造体
 * （ ::CriAtomExHcaMxConfig ）に、デフォルト値をセットします。<br>
 * \sa criAtomExHcaMx_Initialize, CriAtomExHcaMxConfig
 */
#define criAtomExHcaMx_SetDefaultConfig(p_config)	\
{\
	(p_config)->server_frequency = 60.0f;\
	(p_config)->num_mixers = 1;\
	(p_config)->max_voices = 16;\
	(p_config)->max_input_channels = CRIATOM_DEFAULT_INPUT_MAX_CHANNELS;\
	(p_config)->max_sampling_rate = CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE;\
	(p_config)->output_channels = CRIATOM_DEFAULT_OUTPUT_CHANNELS;\
	(p_config)->output_sampling_rate = CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE;\
	(p_config)->sound_renderer_type	= CRIATOM_SOUND_RENDERER_DEFAULT;\
}

 /*==========================================================================
 *      CRI AtomEx SoundGenerator API
 *=========================================================================*/
/*JP
 * \brief CriAtomExSoundGeneratroConfigへのデフォルトパラメータをセット
 * \ingroup ATOMEXLIB_AT
 * \param[out]	p_config	初期化用コンフィグ構造体へのポインタ
 * \par 説明:
 * ::criAtomExSoundGenerator_Initialize 関数に設定するコンフィグ構造体
 * （ ::CriAtomExSoundGeneratroConfig ）に、デフォルトの値をセットします。<br>
 * \sa
 * CriAtomExSoundGeneratroConfig, criAtomExSoundGenerator_Initialize
 */
#define criAtomExSoundGenerator_SetDefaultConfig(p_config)				\
{																		\
	(p_config)->server_frequency = 60.0f;								\
	(p_config)->sound_renderer_type = CRIATOM_SOUND_RENDERER_NATIVE;	\
	(p_config)->sampling_rate = CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE;	\
}

/*==========================================================================
 *      CRI AtomEx RawPCM Float API for Automotive
 *=========================================================================*/
/*JP
 * \brief CriAtomExRawPcmFloatConfig_ATへのデフォルトパラメータをセット
 * \ingroup ATOMEXLIB_AT
 * \param[out]	p_config	初期化用コンフィグ構造体へのポインタ
 * \par 説明:
 * ::criAtomExRawPcmFloat_Initialize_AT 関数に設定するコンフィグ構造体
 * （ ::CriAtomExRawPcmFloatConfig_AT ）に、デフォルトの値をセットします。<br>
 * \sa
 * CriAtomExRawPcmFloatConfig_AT, criAtomExRawPcmFloat_Initialize_AT
 */
#define criAtomExRawPcmFloat_SetDefaultConfig_AT(p_config)				\
{																		\
	(p_config)->server_frequency = 60.0f;								\
	(p_config)->sound_renderer_type = CRIATOM_SOUND_RENDERER_NATIVE;	\
	(p_config)->sampling_rate = CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE;	\
}

/*==========================================================================
 *      CRI AtomEx RawPCM Sint16 API for Automotive
 *=========================================================================*/
/*JP
 * \brief CriAtomExRawPcmSint16Config_ATへのデフォルトパラメータをセット
 * \ingroup ATOMEXLIB_AT
 * \param[out]	p_config	初期化用コンフィグ構造体へのポインタ
 * \par 説明:
 * ::criAtomExRawPcmSint16_Initialize_AT 関数に設定するコンフィグ構造体
 * （ ::CriAtomExRawPcmSint16Config_AT ）に、デフォルトの値をセットします。<br>
 * \sa
 * CriAtomExRawPcmSint16Config_AT, criAtomExRawPcmSint16_Initialize_AT
 */
#define criAtomExRawPcmSint16_SetDefaultConfig_AT(p_config)				\
{																		\
	(p_config)->server_frequency = 60.0f;								\
	(p_config)->sound_renderer_type = CRIATOM_SOUND_RENDERER_NATIVE;	\
	(p_config)->sampling_rate = CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE;	\
}

/*==========================================================================
 *      CRI AtomEx ADX API for Automotive
 *=========================================================================*/
/*JP
 * \brief CriAtomExAdxConfigへのデフォルトパラメータをセット
 * \ingroup ATOMEXLIB_AT
 * \param[out]	p_config	初期化用コンフィグ構造体へのポインタ
 * \par 説明:
 * ::criAtomExAdx_Initialize 関数に設定するコンフィグ構造体
 * （ ::CriAtomExAdxConfig ）に、デフォルトの値をセットします。<br>
 * \sa
 * CriAtomExAdxConfig, criAtomExAdx_Initialize
 */
#define criAtomExAdx_SetDefaultConfig(p_config)				\
{																		\
	(p_config)->server_frequency = 60.0f;								\
	(p_config)->sound_renderer_type = CRIATOM_SOUND_RENDERER_NATIVE;	\
	(p_config)->sampling_rate = CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE;	\
}

/*==========================================================================
 *      CRI AtomEx Voice Pool API
 *=========================================================================*/

/*JP
 * \brief ADXボイスプール作成用コンフィグ構造体にデフォルト値をセット
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[out]	p_config	ADXボイスプール作成用コンフィグ構造体へのポインタ
 * \par 説明:
 * ::criAtomExVoicePool_AllocateAdxVoicePool 関数に設定するコンフィグ構造体
 * （ ::CriAtomExAdxVoicePoolConfig ）に、デフォルトの値をセットします。<br>
 * \sa CriAtomExAdxVoicePoolConfig, criAtomExVoicePool_AllocateAdxVoicePool
 */
#define criAtomExVoicePool_SetDefaultConfigForAdxVoicePool(p_config)	\
{\
	(p_config)->identifier = 0;\
	(p_config)->num_voices = CRIATOMEX_DEFAULT_VOICES_PER_POOL;\
	(p_config)->player_config.reserved = 0;\
}

/*JP
 * \brief サウンドジェネレータボイスプール作成用コンフィグ構造体にデフォルト値をセット
 * \ingroup ATOMEXLIB_AT
 * \param[out]	p_config	サウンドジェネレータボイスプール作成用コンフィグ構造体へのポインタ
 * \par 説明:
 * ::criAtomExVoicePool_AllocateSoundGeneratorVoicePool 関数に設定するコンフィグ構造体
 * （ ::CriAtomExSoundGeneratorVoicePoolConfig ）に、デフォルトの値をセットします。<br>
 * \sa CriAtomExSoundGeneratorVoicePoolConfig, criAtomExVoicePool_AllocateSoundGeneratorVoicePool
 */
#define criAtomExVoicePool_SetDefaultConfigForSoundGeneratorVoicePool(p_config)	\
{																				\
	(p_config)->identifier = 0;													\
	(p_config)->num_voices = CRIATOMEX_DEFAULT_VOICES_PER_POOL;					\
	(p_config)->player_config.reserved = 0;										\
}

/*JP
 * \brief RawPCM Sint16ボイスプール作成用コンフィグ構造体にデフォルト値をセット
 * \ingroup ATOMEXLIB_AT
 * \param[out]	p_config	RawPCM Sint16ボイスプール作成用コンフィグ構造体へのポインタ
 * \par 説明:
 * ::criAtomExVoicePool_AllocateRawPcmSint16VoicePool_AT 関数に設定するコンフィグ構造体
 * （ ::CriAtomExRawPcmSint16VoicePoolConfig_AT ）に、デフォルトの値をセットします。<br>
 * \sa CriAtomExRawPcmSint16VoicePoolConfig_AT, criAtomExVoicePool_AllocateRawPcmSint16VoicePool_AT
 */
#define criAtomExVoicePool_SetDefaultConfigForRawPcmSint16VoicePool_AT(p_config) \
{																				\
	(p_config)->identifier = 0;													\
	(p_config)->num_voices = CRIATOMEX_DEFAULT_VOICES_PER_POOL;					\
	(p_config)->player_config.reserved = 0;										\
}

/*==========================================================================
 *      CRI AtomEx Player API
 *=========================================================================*/
/*JP
 * \brief プレーヤ作成用コンフィグ構造体にデフォルト値をセット
 * \ingroup ATOMEXLIB_PLAYER
 * \param[out]	p_config	AtomExプレーヤ作成用コンフィグ構造体へのポインタ
 * \par 説明:
 * ::criAtomExPlayer_Create 関数に設定するコンフィグ構造体
 * （ ::CriAtomExPlayerConfig ）に、デフォルトの値をセットします。<br>
 * \sa CriAtomExPlayerConfig, criAtomExPlayer_Create
 */
#define criAtomExPlayer_SetDefaultConfig(p_config)	\
{\
	(p_config)->max_path_strings = 1;\
	(p_config)->max_path = 0;\
	(p_config)->updates_time = CRI_TRUE;\
}

/*==========================================================================
 *      CRI AtomEx API for Automotive
 *=========================================================================*/
 /*JP
 * \brief CriAtomExConfig_ATへのデフォルトパラメータをセット
 * \ingroup ATOMEXLIB_AT
 * \param[out]	p_config	初期化用コンフィグ構造体へのポインタ
 * \par 説明:
 * ::criAtomEx_Initialize_AT 関数に設定するコンフィグ構造体
 * （ ::CriAtomExConfig_AT ）に、デフォルトの値をセットします。<br>
 * \sa
 * CriAtomExConfig_AT
 */
#define criAtomEx_SetDefaultConfig_AT(p_config)								\
{																			\
	criAtomEx_SetDefaultConfig(&(p_config)->atom_ex);						\
	criAtomExAdx_SetDefaultConfig(&(p_config)->adx);						\
	criAtomExHcaMx_SetDefaultConfig(&(p_config)->hca_mx);					\
	(p_config)->hca_mx.sound_renderer_type = CRIATOM_SOUND_RENDERER_NATIVE;	\
	criAtomExSoundGenerator_SetDefaultConfig(&(p_config)->sound_generator);	\
	criAtomExRawPcmFloat_SetDefaultConfig_AT(&(p_config)->raw_pcm_float);	\
	criAtomExRawPcmSint16_SetDefaultConfig_AT(&(p_config)->raw_pcm_sint16);	\
	(p_config)->initialize_hca_mx = CRI_FALSE;								\
	(p_config)->initialize_sound_generator = CRI_TRUE;						\
	(p_config)->initialize_raw_pcm_float = CRI_TRUE;						\
	(p_config)->initialize_raw_pcm_sint16 = CRI_FALSE;						\
	(p_config)->initialize_adx = CRI_TRUE;									\
	(p_config)->sampling_rate = CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE;		\
	(p_config)->version = CRI_ATOM_AT_VERSION;								\
}

/***************************************************************************
 *      データ型宣言
 *      Data Type Declarations
 ***************************************************************************/
/*==========================================================================
 *      CRI Atom API
 *=========================================================================*/
/*JP
 * \brief メモリ確保関数
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	obj		ユーザ指定オブジェクト
 * \param[in]	size	要求メモリサイズ（バイト単位）
 * \return		void*	確保したメモリのアドレス（失敗時はNULL）
 * \par 説明:
 * メモリ確保関数登録用のインターフェースです。<br>
 * CRI Atomライブラリがライブラリ内で行うメモリ確保処理を、
 * ユーザ独自のメモリ確保処理に置き換えたい場合に使用します。<br>
 * \par 備考:
 * コールバック関数が実行される際には、sizeに必要とされるメモリのサイズがセット
 * されています。<br>
 * コールバック関数内でsize分のメモリを確保し、確保したメモリのアドレスを
 * 戻り値として返してください。<br>
 * 尚、引数の obj には、::criAtom_SetUserMallocFunction 関数で登録したユーザ指定
 * オブジェクトが渡されます。<br>
 * メモリ確保時にメモリマネージャ等を参照する必要がある場合には、
 * 当該オブジェクトを ::criAtom_SetUserMallocFunction 関数の引数にセットしておき、
 * 本コールバック関数の引数を経由して参照してください。<br>
 * \attention
 * メモリの確保に失敗した場合、エラーコールバックが返されたり、呼び出し元の関数が
 * 失敗する可能性がありますのでご注意ください。
 * \sa CriAtomFreeFunc, criAtom_SetUserMallocFunction
 */
typedef void *(CRIAPI *CriAtomMallocFunc)(void *obj, CriUint32 size);

/*JP
 * \brief メモリ解放関数
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	obj		ユーザ指定オブジェクト
 * \param[in]	mem		解放するメモリアドレス
 * \return				なし
 * \par 説明:
 * メモリ解放関数登録用のインターフェースです。<br>
 * CRI Atomライブラリ内がライブラリ内で行うメモリ解放処理を、
 * ユーザ独自のメモリ解放処理に置き換えたい場合に使用します。<br>
 * \par 備考:
 * コールバック関数が実行される際には、memに解放すべきメモリのアドレスがセット
 * されています。<br>
 * コールバック関数内でmemの領域のメモリを解放してください。
 * 尚、引数の obj には、::criAtom_SetUserFreeFunction 関数で登録したユーザ指定
 * オブジェクトが渡されます。<br>
 * メモリ確保時にメモリマネージャ等を参照する必要がある場合には、
 * 当該オブジェクトを ::criAtom_SetUserFreeFunction 関数の引数にセットしておき、
 * 本コールバック関数の引数を経由して参照してください。<br>
 * \sa CriAtomMallocFunc, criAtom_SetUserFreeFunction
 */
typedef void (CRIAPI *CriAtomFreeFunc)(void *obj, void *mem);

/*JP
 * \brief サウンドレンダラタイプ
 * \ingroup ATOMLIB_GLOBAL
 * \par 説明:
 * Atomプレーヤが内部で作成するサウンドレンダラの種別を指定するためのデータ型です。<br>
 * Atomプレーヤ作成時にコンフィグ構造体のパラメータとして指定します。
 * \attention
 * ::CRIATOM_SOUND_RENDERER_ANY は ::criAtomExPlayer_SetSoundRendererType 関数に対してのみ指定可能です。<br>
 * ボイスプール作成時には使用できません。<br>
 * \sa CriAtomAdxPlayerConfig, criAtomPlayer_CreateAdxPlayer
 */
typedef enum CriAtomSoundRendererTypeTag {
	CRIATOM_SOUND_RENDERER_NATIVE = 1,		/*JP<プラットフォームライブラリへ出力	*/
	CRIATOM_SOUND_RENDERER_ASR = 2,			/*JP<Atom Sound Rendererへ出力			*/
	CRIATOM_SOUND_RENDERER_HAPTIC = 3,

	CRIATOM_SOUND_RENDERER_HW1 = 4,
	CRIATOM_SOUND_RENDERER_HW2 = 5,
	CRIATOM_SOUND_RENDERER_HW3 = 6,
	CRIATOM_SOUND_RENDERER_HW4 = 7,
	CRIATOM_SOUND_RENDERER_HW5 = 8,

	CRIATOM_SOUND_RENDERER_ANY = 0,			/*JP<出力方式を制限しない				*/

	/* enum size is 4bytes */
	CRIATOM_SOUND_RENDERER_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomSoundRendererType;

/*==========================================================================
 *      CRI Atom Player API
 *=========================================================================*/
/*JP
 * ADXプレーヤ作成用コンフィグ構造体
 * \ingroup ATOMLIB_PLAYER
 * \par 説明:
 * ADXが再生可能なプレーヤを作成する際に、動作仕様を指定するための構造体です。<br>
 * ::criAtomPlayer_CreateAdxPlayer 関数の引数に指定します。<br>
 * <br>
 * 作成されるプレーヤは、ハンドル作成時に本構造体で指定された設定に応じて、
 * 内部リソースを必要なだけ確保します。<br>
 * プレーヤが必要とするワーク領域のサイズは、本構造体で指定されたパラメータに応じて変化します。
 * \attention
 * 将来的にメンバが増える可能性があるため、 ::criAtomPlayer_SetDefaultConfigForAdxPlayer
 * マクロを使用しない場合には、使用前に必ず構造体をゼロクリアしてください。<br>
 * （構造体のメンバに不定値が入らないようご注意ください。）
 * \sa criAtomPlayer_CreateAdxPlayer, criAtomPlayer_SetDefaultConfigForAdxPlayer
 */
typedef struct CriAtomAdxPlayerConfigTag {
	CriSint32 reserved;
} CriAtomAdxPlayerConfig;

/*JP
 * \brief サウンドジェネレータプレーヤ用コンフィグ構造体
 * \ingroup ATOMLIB_AT
 * \par 説明:
 * サウンドジェネレータプレーヤを作成する際に指定するパラメータです。<br>
 * ::criAtomPlayer_CalculateWorkSizeForSoundGeneratorPlayer 関数および
 * ::criAtomPlayer_CreateSoundGeneratorPlayer 関数の config として指定します。
 * \par 備考:
 * デフォルト設定を使用する場合、 ::criAtomPlayer_SetDefaultConfigForSoundGeneratorPlayer マクロで
 * 構造体にデフォルトパラメータをセットした後、::criAtomPlayer_CalculateWorkSizeForSoundGeneratorPlayer 関数
 * または ::criAtomPlayer_CreateSoundGeneratorPlayer 関数に構造体を指定してください。<br>
 * \attention
 * 将来的にメンバが増える可能性があるため、 ::criAtomPlayer_SetDefaultConfigForSoundGeneratorPlayer
 * マクロを使用しない場合には、使用前に必ず構造体をゼロクリアしてください。<br>
 * （構造体のメンバに不定値が入らないようご注意ください。）
 * \sa criAtomPlayer_CalculateWorkSizeForSoundGeneratorPlayer, criAtomPlayer_CreateSoundGeneratorPlayer
 */
typedef struct CriAtomSoundGeneratorPlayerConfigTag {
	CriSint32 reserved;
} CriAtomSoundGeneratorPlayerConfig;

 /*JP
 * \brief RawPCM Sint16プレーヤ用コンフィグ構造体
 * \ingroup ATOMLIB_AT
 * \par 説明:
 * RawPCM Sint16プレーヤを作成する際に指定するパラメータです。<br>
 * ::criAtomPlayer_CalculateWorkSizeForRawPcmSint16Player_AT 関数および
 * ::criAtomPlayer_CreateRawPcmSint16Player_AT 関数の config として指定します。
 * \par 備考:
 * デフォルト設定を使用する場合、 ::criAtomPlayer_SetDefaultConfigForRawPcmSint16Player_AT マクロで
 * 構造体にデフォルトパラメータをセットした後、::criAtomPlayer_CalculateWorkSizeForRawPcmSint16Player_AT 関数
 * または ::criAtomPlayer_CreateRawPcmSint16Player_AT 関数に構造体を指定してください。<br>
 * \attention
 * 将来的にメンバが増える可能性があるため、 ::criAtomPlayer_SetDefaultConfigForRawPcmSint16Player_AT
 * マクロを使用しない場合には、使用前に必ず構造体をゼロクリアしてください。<br>
 * （構造体のメンバに不定値が入らないようご注意ください。）
 * \sa criAtomPlayer_CalculateWorkSizeForRawPcmSint16Player_AT, criAtomPlayer_CreateRawPcmSint16Player_AT
 */
typedef struct CriAtomRawPcmSint16PlayerConfigTag_AT {
	CriSint32	reserved;
} CriAtomRawPcmSint16PlayerConfig_AT;

/*==========================================================================
 *      CRI Atom AWB API
 *=========================================================================*/
struct CriAtomAwbTag;
/*JP
 * \brief AWBハンドル
 * \ingroup ATOMLIB_AWB
 * \par 説明:
 * 再生データが含まれているAWBファイルのTOC情報を示すハンドルです。<br>
 * ::criAtomAwb_LoadToc 関数で取得します。<br>
 * \sa criAtomAwb_LoadToc
 */
typedef struct CriAtomAwbTag *CriAtomAwbHn;

/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*JP
 * \brief メモリ確保関数
 * \ingroup ATOMEXLIB_GLOBAL
 * \par 説明:
 * アロケータ登録時に使用するメモリ確保関数の型です。
 * \sa criAtomEx_SetUserAllocator
 */
typedef CriAtomMallocFunc CriAtomExMallocFunc;

/*JP
 * \brief メモリ解放関数
 * \ingroup ATOMEXLIB_GLOBAL
 * \par 説明:
 * アロケータ登録時に使用するメモリ解放関数の型です。
 * \sa criAtomEx_SetUserAllocator
 */
typedef CriAtomFreeFunc CriAtomExFreeFunc;

/*JP
 * \brief スレッドモデル
 * \ingroup ATOMEXLIB_GLOBAL
 * \par 説明:
 * Atomライブラリがどのようなスレッドモデルで動作するかを表します。<br>
 * ライブラリ初期化時（ ::criAtomEx_Initialize関数 ）に ::CriAtomExConfig 
 * 構造体にて指定します。
 * \sa criAtomEx_Initialize, CriAtomExConfig
 */
typedef enum CriAtomExThreadModelTag {
	/*JP
	 * \brief マルチスレッド
	 * \par 説明:
	 * ライブラリは内部でスレッドを作成し、マルチスレッドにて動作します。<br>
	 * スレッドは ::criAtomEx_Initialize 関数呼び出し時に作成されます。<br>
	 * ライブラリのサーバ処理は、作成されたスレッド上で定期的に実行されます。<br>
	 */
	CRIATOMEX_THREAD_MODEL_MULTI = 0,
	
	/*JP
	 * \brief マルチスレッド（ユーザ駆動式）
	 * \par 説明:
	 * ライブラリは内部でスレッドを作成し、マルチスレッドにて動作します。<br>
	 * スレッドは ::criAtomEx_Initialize 関数呼び出し時に作成されます。<br>
	 * サーバ処理自体は作成されたスレッド上で実行されますが、
	 * CRIATOMEX_THREAD_MODEL_MULTI とは異なり、自動的には実行されません。<br>
	 * ユーザは ::criAtomEx_ExecuteMain 関数で明示的にサーバ処理を駆動する必要があります。<br>
	 * （  ::criAtomEx_ExecuteMain 関数を実行すると、スレッドが起動し、サーバ処理が実行されます。）<br>
	 */
	CRIATOMEX_THREAD_MODEL_MULTI_USER_DRIVEN = 3,
	
	/*JP
	 * \brief ユーザマルチスレッド
	 * \par 説明:
	 * ライブラリ内部ではスレッドを作成しませんが、ユーザが独自に作成したスレッド
	 * からサーバ処理関数を呼び出せるよう、内部の排他制御は行います。<br>
	 * サーバ処理は ::criAtomEx_ExecuteMain 関数内で同期実行されます。<br>
	 */
	CRIATOMEX_THREAD_MODEL_USER_MULTI = 1,
	
	/*JP
	 * \brief シングルスレッド
	 * \par 説明:
	 * ライブラリ内部でスレッドを作成しません。また、内部の排他制御も行いません。<br>
	 * サーバ処理は ::criAtomEx_ExecuteMain 関数内で同期実行されます。<br>
	 * \attention
	 * このモデルを選択した場合、各APIとサーバ処理関数とを同一スレッドから呼び出すようにしてください。<br>
	 */
	CRIATOMEX_THREAD_MODEL_SINGLE = 2,
	
	/* enum size is 4bytes */
	CRIATOMEX_THREAD_MODEL_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExThreadModel;

/*JP
 * \brief Atomライブラリ初期化用コンフィグ構造体
 * \ingroup ATOMEXLIB_GLOBAL
 * CRI Atomライブラリの動作仕様を指定するための構造体です。<br>
 * ::criAtomEx_Initialize 関数の引数に指定します。<br>
 * <br>
 * CRI Atomライブラリは、初期化時に本構造体で指定された設定に応じて、内部リソースを
 * 必要なだけ確保します。<br>
 * ライブラリが必要とするワーク領域のサイズは、本構造体で指定されたパラメータに応じて
 * 変化します。
 * \par 備考:
 * デフォルト設定を使用する場合、 ::criAtomEx_SetDefaultConfig マクロで構造体にデフォルト
 * パラメータをセットした後、 ::criAtomEx_Initialize 関数に構造体を指定してください。<br>
 * \attention
 * 将来的にメンバが増える可能性があるため、 ::criAtomEx_SetDefaultConfig マクロを使用しない
 * 場合には、使用前に必ず構造体をゼロクリアしてください。<br>
 * （構造体のメンバに不定値が入らないようご注意ください。）
 * \sa criAtomEx_Initialize, criAtomEx_SetDefaultConfig
 */
typedef struct CriAtomExConfigTag {
	/*JP
		\brief スレッドモデル
		\par 説明:
		CRI Atomライブラリのスレッドモデルを指定します。<br>
		\sa CriAtomExThreadModel
	*/
	CriAtomExThreadModel thread_model;
	
	/*JP
		\brief サーバ処理の実行頻度
		\par 説明:
		サーバ処理を実行する頻度を指定します。<br>
		通常、アプリケーションのフレームレートと同じ値を指定します。<br>
		<br>
		CRI Atomライブラリは、ファイル読み込みの管理や、音声データのデコード、音声の出力、
		ステータスの更新等、ライブラリ内部で行う処理のほとんどを1つの関数でまとめて
		行います。<br>
		CRIミドルウェアでは、こういったライブラリ内の処理を一括して行う関数のことを
		"サーバ処理"と呼んでいます。<br>
		<br>
		スレッドモデルが ::CRIATOMEX_THREAD_MODEL_MULTI の場合、サーバ処理は
		CRI Atomライブラリが作成するスレッドで、定期的に実行されます。<br>
		スレッドモデルが ::CRIATOMEX_THREAD_MODEL_SINGLE や ::CRIATOMEX_THREAD_MODEL_USER_MULTI 
		の場合、サーバ処理は ::criAtomEx_ExecuteMain 関数内で実行されます。<br>
		<br>
		server_frequency には、サーバ処理を実行する頻度を指定します。<br>
		スレッドモデルが ::CRIATOMEX_THREAD_MODEL_MULTI の場合、CRI Atomライブラリは指定された
		頻度でサーバ処理が実行されるよう、サーバ処理の呼び出し間隔を調節します。<br>
		スレッドモデルが ::CRIATOMEX_THREAD_MODEL_SINGLE や ::CRIATOMEX_THREAD_MODEL_USER_MULTI 
		の場合、ユーザは ::criAtomEx_ExecuteMain 関数を server_frequency で指定した頻度以上
		で実行する必要があります。<br>
		<br>
		アプリケーションのフレームレートの変動が大きく、サーバ処理を実行する頻度にバラツキ
		ができてしまう場合には、最悪のフレームレートを想定して server_frequency の値を指定
		するか、またはスレッドモデルに ::CRIATOMEX_THREAD_MODEL_MULTI を指定してください。
		\par 備考:
		Atomライブラリのサーバ処理では、以下のような処理が行われます。<br>
		- 発音リクエストの処理（ボイスの取得等）
		- パラメータの更新（ボリュームやパン、ピッチ等の変更の適用）
		- 音声データのデコードと出力
		.
		サーバ処理の実行頻度を多くすると、単位サーバ処理当たりの音声データデコード量が少なくなります。<br>
		その結果、単位サーバ当たりの処理負荷は小さくなります（負荷が分散されます）が、
		サーバ処理の実行に伴うオーバーヘッドは大きくなります。<br>
		（スレッドの起床回数やパラメータの更新回数が多くなります。）<br>
		<br>
		サーバ処理の実行頻度を少なくすると、スレッドの起床や発音リクエストの処理、
		パラメータの更新処理の回数が減り、アプリケーション全体の処理負荷は下がります。<br>
		反面、データをリロードする頻度が下がるため、単位サーバ処理当たりデコード量は増え、
		デコード結果を保持するためのバッファサイズが余分に必要になります。<br>
		また、発音リクエストを処理する頻度が下がるため、
		発音リクエストから音声出力開始までにかかる時間は長くなります。<br>
		\attention
		スレッドモデルに ::CRIATOMEX_THREAD_MODEL_SINGLE や ::CRIATOMEX_THREAD_MODEL_USER_MULTI 
		を指定したにもかかわらず、 ::criAtomEx_ExecuteMain 関数が server_frequency で
		指定した値以下の頻度でしか実行されなかった場合、再生中の音が途切れる等の問題が
		発生する可能性がありますので、ご注意ください。<br>
		\sa criAtomEx_ExecuteMain
	*/
	CriFloat32 server_frequency;
	
	/*JP
		\brief パラメータ更新間隔
		\par 説明:
		サーバ処理実行時にパラメータの更新処理を行う間隔を指定します。<br>
		parameter_update_interval の値を変更することで、
		サーバ処理の実行回数を変えることなくパラメータ更新頻度を下げることが可能です。<br>
		<br>
		parameter_update_interval には、パラメータの更新処理を何サーバごとに行うかを指定します。<br>
		例えば、 parameter_update_interval を 2 に設定すると、
		サーバ処理 2 回に対し、 1 回だけパラメータの変更が行われます。<br>
		（パラメータの更新頻度が 1/2 になります。）<br>
		\par 備考:
		サーバ処理周波数（ server_frequency ）を下げると、
		サーバ処理の実行回数が減るため、アプリケーション全体の処理負荷は下がりますが、
		サーバ処理同士の間隔が開くため、バッファリングすべきデータの量が増加します。<br>
		その結果、バッファリングのために必要なメモリのサイズは増加します。<br>
		<br>
		これに対し、サーバ処理周波数を変更せずにパラメータ更新間隔（ parameter_update_interval ）
		の値を上げた場合、メモリサイズを増加させずに負荷を下げることが可能となります。<br>
		ただし、サーバ処理の駆動に伴う処理のオーバーヘッド（スレッドの起床負荷等）
		は削減されないため、サーバ処理の回数を減らす場合に比べ、負荷削減の効果は薄いです。<br>
		\par 注意:
		parameter_update_interval の値を変更した場合、
		発音リクエストの処理頻度も少なくなります。<br>
		そのため、 parameter_update_interval の値を変更すると、
		発音リクエストから音声出力開始までにかかる時間が長くなります。<br>
	*/
	CriSint32 parameter_update_interval;
	
	/*JP
		\brief CRI Atom Library以外を使った音声出力を行うことを指定するフラグ
		\par 説明:
		CRI Atom Libraryを使用せずに音声出力する際にCRI_TRUEを指定します。<br>
		::criAtomEx_SetDefaultConfig マクロでは、CRI Atom Libraryを指定するため、CRI_FALSEが指定されます。<br>
		CRI Atom Library以外の音声出力ライブラリを用いる場合は、本フラグにCRI_TRUEを指定してから、criAtomEx_Initializeを
		実行するようにしてください。
		\attention
		本フラグを切り替える際には、AtomライブラリをcriAtomEx_Finalizeで終了してから、フラグの内容を変更し、再度
		criAtomEx_Initializeにて初期化処理を行うようにしてください。<br>
	*/
	CriBool enable_atom_sound_disabled_mode;
	
	/*JP
		\brief 最大バーチャルボイス数
		\par 説明:
		アプリケーションで同時に発音制御を行うボイスの数です。<br>
		Atomライブラリは、初期化時に max_virtual_voices で指定された数分だけ
		発音管理に必要なリソースを確保します。<br>
		\par 備考:
		max_virtual_voices で指定された数以上の音声を同時に発音することはできません。<br>
		また、 max_virtual_voices 分の発音リクエストを行ったとしても、実際に
		発音される音声の数は、必ずしも max_virtual_voices に一致するとは限りません。<br>
		実際に発音可能な音声の数は、ボイスプールで確保されたボイス数や、
		ターゲット機で利用可能なハードウェアボイスの数に依存します。<br>
		<br>
		バーチャルボイス数の目安は、「最大同時発音数＋1V当たりの発音リクエスト数」です。<br>
		バーチャルボイス数が最大同時発音数より少ない場合や、
		発音数とリクエスト数の合計が最大バーチャルボイスを超える場合、
		エラーコールバック関数に警告が返される可能性があります。<br>
		<br>
		CRIATOMEX_RETRY_VOICE_ALLOCATION を指定して AtomEx プレーヤを作成する場合、
		上記よりもさらに多くのバーチャルボイスを必要とする可能性があります。<br>
	*/
	CriSint32 max_virtual_voices;
	
	/*JP
		\brief 最大パラメータブロック数
		\par 説明:
		音声再生時にパラメータ管理を行うための領域の数です。<br>
		Atomライブラリは、初期化時に max_parameter_blocks で指定された数分だけ
		パラメータ管理に必要なリソースを確保します。<br>
		\par 備考:
		1つのキューを再生するのに必要なパラメータブロック数は、
		再生するキューの内容によって変化します。<br>
		（操作するパラメータの数に比例して必要なパラメータブロック数は増加します。）<br>
		<br>
		パラメータブロック数が不足した場合、再生するキューに対して
		一部のパラメータが設定されないことになります。<br>
		（ボリュームやピッチ、フィルタ等が意図した値にならない可能性があります。）<br>
		アプリケーション実行中にパラメータブロック数不足のエラーが発生した場合、
		max_parameter_blocks の値を増やしてください。<br>
	*/
	CriSint32 max_parameter_blocks;

	/*JP
		\brief 最大カテゴリ数
		\par 説明:
		アプリケーションで作成するカテゴリの数です。<br>
		Atomライブラリは、初期化時に max_categories で指定された数分
		のカテゴリを作成できるリソースを確保します。<br>
		\attention
		max_categories で指定された数以上のカテゴリを作成することはできません。<br>
		オーサリングツール上で作成したカテゴリの数が 
		max_categories を超える場合、ACFファイルのロードに失敗します。<br>
	*/
	CriSint32 max_categories;

	/*JP
		\brief 再生単位でのカテゴリ参照数
		\par 説明:
		再生単位で参照可能なカテゴリの数です。<br>
		Atomライブラリは、初期化時に categories_per_playback で指定された数分
		のカテゴリを参照できるリソースを確保します。<br>
		指定可能な最大値は ::CRIATOMEXCATEGORY_MAX_CATEGORIES_PER_PLAYBACK です。
		\attention
		categories_per_playback で指定された数以上のカテゴリをキューやプレーヤから参照することはできません。<br>
		オーサリングツール上で作成したキューの参照カテゴリ数が 
		categories_per_playback を超える場合、ACFファイルのロードに失敗します。<br>
	*/
	CriSint32 categories_per_playback;

	/*JP
		\brief 最大再生シーケンス数
		\par 説明:
		アプリケーションで同時に再生するシーケンスの数です。<br>
		Atomライブラリは、初期化時に max_sequences で指定された数と max_virtual_voices で指定された数の総和分
		のシーケンスを再生できるリソースを確保します。<br>
		\attention
		Ver.2.00以降のライブラリでは全てのキューがシーケンスとして再生されるため、 max_sequences に加えて
		 max_virtual_voices 数分のリソースが確保されます。<br>
		max_sequences で指定された数以上のシーケンスを再生することはできません。<br>
		エラーコールバックが発生した場合、この値を大きくしてください。<br>
	*/
	CriSint32 max_sequences;

	/*JP
		\brief 最大再生トラック数
		\par 説明:
		アプリケーションで同時再生するシーケンス内のトラック総数です。<br>
		Atomライブラリは、初期化時に max_tracks で指定された数と max_virtual_voices で指定された数の総和分
		のトラックを再生できるリソースを確保します。<br>
		\attention
		Ver.2.00以降のライブラリでは全てのキューがシーケンスとして再生されるため、 max_tracks に加えて
		 max_virtual_voices 数分のリソースが確保されます。<br>
		max_tracks で指定された数以上のトラックを再生することはできません。<br>
		エラーコールバックが発生した場合、この値を大きくしてください。<br>
	*/
	CriUint32 max_tracks;

	/*JP
		\brief 最大トラックアイテム数
		\par 説明:
		アプリケーションで同時再生するシーケンス内のイベントの総数です。<br>
		Atomライブラリは、初期化時に max_track_items で指定された数と max_virtual_voices で指定された数の総和分
		のトラックアイテムを作成できるリソースを確保します。<br>
		\attention
		Ver.2.00以降のライブラリでは全てのキューがシーケンスとして再生されるため、 max_track_items に加えて
		 max_virtual_voices 数分のリソースが確保されます。<br>
		max_track_items で指定された数以上のトラックアイテムを
		作成することはできません。<br>
		トラックアイテムは波形や、ループイベント等のシーケンストラック再生時に
		管理が必要なイベントです。<br>
		エラーコールバックが発生した場合、この値を大きくしてください。<br>
	*/
	CriUint32 max_track_items;
	
	/*JP
		\brief 最大AISACオートモジュレーション数（仕様停止）
		\par 説明:
		Ver.2.00.00以降のライブラリでは使用停止となりました。
		ライブラリ内部での本メンバへの参照は行われません。<br>
	*/
	CriUint32 max_aisac_auto_modulations;

	/*JP
		\brief ピッチ変更の上限値
		\par 説明:
		Atomライブラリ内で適用されるピッチ変更の上限値を設定します。<br>
		max_pitchに設定された値以上のピッチ変更が、ライブラリ内でクリップされます。<br>
		<br>
		ピッチはセント単位で指定します。<br>
		1セントは1オクターブの1/1200です。半音は100セントです。<br>
		<br>
		例えば、 max_pitch に 1200.0f を設定した場合、
		1200セントを超えるピッチが設定されたキューを再生したとしても、
		ピッチが1200セントに抑えられて再生されます。<br>
		\par 備考:
		キューに設定されたピッチに、AISACによるピッチ変更やドップラー効果が追加適用された場合、
		予期せぬレベルまでピッチが上がる恐れがあります。<br>
		（ピッチに比例して単位時間当たりのデコード量が増加するため、
		ピッチが高すぎる音を大量に鳴らした場合、処理負荷が急増する恐れがあります。）<br>
		<br>
		本パラメータであらかじめピッチ上限を設定しておくことで、
		想定外の負荷変動を回避することが可能となります。<br>
		例えば、 max_pitch に 1200.0f を設定した場合、
		アプリケーション中でどのような操作を行ったとしてもピッチが1200セント
		（＝2倍速再生）までに抑えられるため、
		単位時間あたりのデコード量は最大でも通常時の2倍までに制限されます。<br>
		\par 注意:
		max_pitchには 0.0f 以上の値を設定する必要があります。<br>
		（ 0.0f を指定した場合、ピッチの変更は一切行われなくなります。）<br>
	*/
	CriFloat32 max_pitch;

	/*JP
		\brief プラットフォーム固有の初期化パラメータへのポインタ
		\par 説明:
		CRI Atomライブラリを動作させるために必要な、
		プラットフォーム固有の初期化パラメータへのポインタを指定します。
		NULLを指定した場合、デフォルトパラメータでプラットフォーム毎に必要な初期化を行います。<br>
		パラメータ構造体は各プラットフォーム固有ヘッダに定義されています。
		パラメータ構造体が定義されていないプラットフォームでは、常にNULLを指定してください。
		\sa criAtomEx_Initialize
	*/
	void *context;
} CriAtomExConfig;

/*==========================================================================
 *      CRI AtomEx HCA-MX API
 *=========================================================================*/
/*JP
 * \brief HCA-MX初期化用コンフィグ構造体
 * \ingroup ATOMEXLIB_HCA_MX
 * HCA-MXの動作仕様を指定するための構造体です。<br>
 * ::criAtomExHcaMx_Initialize 関数の引数に指定します。<br>
 * \par 備考:
 * デフォルト設定を使用する場合、 ::criAtomExHcaMx_SetDefaultConfig マクロで
 * 構造体にデフォルトパラメータをセットした後、 ::criAtomExHcaMx_Initialize 関数
 * に構造体を指定してください。<br>
 * \attention
 * 将来的にメンバが増える可能性があるため、 ::criAtomExHcaMx_SetDefaultConfig 
 * マクロを使用しない場合には、使用前に必ず構造体をゼロクリアしてください。<br>
 * （構造体のメンバに不定値が入らないようご注意ください。）
 * \sa criAtomExHcaMx_Initialize, criAtomExHcaMx_SetDefaultConfig
 */
typedef struct CriAtomExHcaMxConfigTag {
	/*JP
		\brief サーバ処理の実行頻度
		\par 説明:
		サーバ処理を実行する頻度を指定します。<br>
		\attention
		Atomライブラリ初期化時に指定した値（ ::CriAtomExConfig 構造体の
		server_frequency ）と、同じ値をセットする必要があります。<br>
		\sa CriAtomExConfig
	*/
	CriFloat32 server_frequency;
	
	/*JP
		\brief ミキサ数
		\par 説明:
		HCA-MXデコード結果を送信するミキサの数を指定します。<br>
		ミキサを複数作成することで、
		ミキサごとに異なるDSPバスのDSP FXを適用することが可能になります。<br>
		\attention
		HCA-MXのデコード処理、および定常状態の処理負荷は、
		ミキサの数に比例して重くなります。<br>
		<br>
		本パラメータを0に設定した場合でも、ミキサは 1 つだけ作成されます。<br>
		（旧バージョンとの互換性維持のため。）<br>
		HCA-MXを使用しない場合には、本パラメータと max_voices の両方を 0 
		に設定してください。<br>
	*/
	CriSint32 num_mixers;
	
	/*JP
		\brief ミキサに登録可能な最大ボイス数
		\par 説明:
		ミキサごとに登録可能なHCA-MXボイスの数を指定します。<br>
		HCA-MXボイスプールを作成する際には、ボイスの総数が
		num_mixers × max_voices を超えないようご注意ください。
	*/
	CriSint32 max_voices;
	
	/*JP
		\brief 入力データの最大チャンネル数
		\par 説明:
		アプリケーション中で再生するHCA-MXデータの最大チャンネル数を指定します。<br>
		再生するデータがモノラルの場合は1を、ステレオの場合は2を指定してください。<br>
		\par 備考:
		HCA-MX初期化時に max_input_channels に指定された数以下の音声データが
		再生可能になります。<br>
		例えば、 max_input_channels に6を指定した場合、5.1ch音声だけでなく、
		モノラル音声やステレオ音声も再生可能になります。<br>
		100個のデータのうち、99個がモノラル、1個がステレオの場合でも、
		max_input_channels には2を指定する必要があります。<br>
	*/
	CriSint32 max_input_channels;
	
	/*JP
		\brief 最大サンプリングレート
		\par 説明:
		HCA-MXの出力に指定できる最大サンプリングレートです。<br>
		ミキサの最終出力でピッチを変更する場合に設定します。<br>
		ミキサの最終出力でピッチを変更しない場合は、output_sampling_rateと同じ値を設定してください。<br>
		\par 備考:
		例えばHCA-MX再生時に::criAtomExHcaMx_SetFrequencyRatio 関数に 2.0f を指定してピッチを上げる場合は、
		output_sampling_rate * 2 を指定してHCA-MXを初期化してください。<br>
	*/
	CriSint32 max_sampling_rate;

	/*JP
		\brief 出力チャンネル数
		\par 説明:
		HCA-MXデータの出力チャンネル数を指定します。<br>
		通常、ターゲット機に接続されたスピーカーの数（出力デバイスの
		最大チャンネル数）を指定します。<br>
		\par 備考:
		モノラル音声のみを再生し、パンをコントロールしない場合には、
		output_channels を1にすることで、処理負荷を下げることが可能です。<br>
		\attention
		output_channels の数を max_input_channels 以下の値に設定することは
		できません。<br>
	*/
	CriSint32 output_channels;
	
	/*JP
		\brief 出力サンプリングレート
		\par 説明:
		再生するHCA-MXデータのサンプリングレートを指定します。<br>
		HCA-MXデータを作成する際には、必ず全ての音声データを同一のサンプリング
		レートで作成し、その値を output_sampling_rate に指定してください。<br>
		\par 備考:
		HCA-MXは、音単位のサンプリングレート変更を行えません。<br>
	*/
	CriSint32 output_sampling_rate;
	
	/*JP
		\brief サウンドレンダラタイプ
		\par 説明:
		HCA-MXの出力先サウンドレンダラの種別を指定します。<br>
		sound_renderer_type に CRIATOM_SOUND_RENDERER_DEFAULT を指定した場合、
		音声データはデフォルト設定のサウンドレンダラに転送されます。<br>
		sound_renderer_type に CRIATOM_SOUND_RENDERER_NATIVE を指定した場合、
		音声データはデフォルト設定の各プラットフォームのサウンド出力に転送されます。<br>
		sound_renderer_type に CRIATOM_SOUND_RENDERER_ASR を指定した場合、
		音声データはASR（Atom Sound Renderer）に転送されます。<br>
		（ASRの出力先は、ASR初期化時に別途指定。）
	*/
	CriAtomSoundRendererType sound_renderer_type;
} CriAtomExHcaMxConfig;

/*==========================================================================
 *      CRI AtomEx ACF API
 *=========================================================================*/
 /*JP
 * \brief AISACコントロールID
 * \ingroup ATOMEXLIB_ACF
 * \par 説明:
 * AISACコントロールIDは、AISACコントロールに対して割り当てられている一意のIDです。<br>
 * AISACコントロールIDをプログラム中で保持する際には、本変数型を用いて値を取り扱う必要があります。<br>
 * \sa criAtomExPlayer_SetAisacControlById, criAtomExAcf_GetAisacControlIdByName, criAtomExAcf_GetAisacControlNameById
 */
typedef CriUint32 CriAtomExAisacControlId;

/*==========================================================================
 *      CRI AtomEx SoundGenerator API
 *=========================================================================*/
/*JP
 * \brief サウンドジェネレータ初期化用コンフィグ構造体
 * \ingroup ATOMEXLIB_AT
 * \par 説明:
 * サウンドジェネレータを初期化する際に指定するパラメータです。<br>
 * ::criAtomExSoundGenerator_CalculateWorkSize 関数および
 * ::criAtomExSoundGenerator_Initialize 関数の config として指定します。
 * \par 備考:
 * デフォルト設定を使用する場合、 ::criAtomExSoundGenerator_SetDefaultConfig マクロで
 * 構造体にデフォルトパラメータをセットした後、::criAtomExSoundGenerator_CalculateWorkSize 関数
 * または ::criAtomExSoundGenerator_Initialize 関数に構造体を指定してください。<br>
 * \attention
 * 将来的にメンバが増える可能性があるため、 ::criAtomExSoundGenerator_CalculateWorkSize
 * マクロを使用しない場合には、使用前に必ず構造体をゼロクリアしてください。<br>
 * （構造体のメンバに不定値が入らないようご注意ください。）
 * \sa criAtomExSoundGenerator_CalculateWorkSize, criAtomExSoundGenerator_Initialize
 */
typedef struct CriAtomExSoundGeneratorConfigTag {
	CriFloat32					server_frequency;		/*JP< サーバー動作周波数		*/
	CriAtomSoundRendererType	sound_renderer_type;	/*JP< サウンドレンダラタイプ	*/
	CriSint32					sampling_rate;			/*JP< サンプリングレート		*/
} CriAtomExSoundGeneratorConfig;

/*==========================================================================
 *      CRI AtomEx RawPCM Float API for Automotive
 *=========================================================================*/
/*JP
 * \brief RawPCM Float初期化用コンフィグ構造体
 * \ingroup ATOMEXLIB_AT
 * \par 説明:
 * RawPCM Floatを初期化する際に指定するパラメータです。<br>
 * ::criAtomExRawPcmFloat_CalculateWorkSize_AT 関数および
 * ::criAtomExRawPcmFloat_Initialize_AT 関数の config として指定します。
 * \par 備考:
 * デフォルト設定を使用する場合、 ::criAtomExRawPcmFloat_SetDefaultConfig_AT マクロで
 * 構造体にデフォルトパラメータをセットした後、::criAtomExRawPcmFloat_CalculateWorkSize_AT 関数
 * または ::criAtomExRawPcmFloat_Initialize_AT 関数に構造体を指定してください。<br>
 * \attention
 * 将来的にメンバが増える可能性があるため、 ::criAtomExRawPcmFloat_CalculateWorkSize_AT
 * マクロを使用しない場合には、使用前に必ず構造体をゼロクリアしてください。<br>
 * （構造体のメンバに不定値が入らないようご注意ください。）
 * \sa criAtomExRawPcmFloat_CalculateWorkSize_AT, criAtomExRawPcmFloat_Initialize_AT
 */
typedef struct CriAtomExRawPcmFloatConfigTag_AT {
	CriFloat32					server_frequency;		/*JP< サーバー動作周波数		*/
	CriAtomSoundRendererType	sound_renderer_type;	/*JP< サウンドレンダラタイプ	*/
	CriSint32					sampling_rate;			/*JP< サンプリングレート		*/
} CriAtomExRawPcmFloatConfig_AT;

/*==========================================================================
 *      CRI AtomEx RawPCM Sint16 API for Automotive
 *=========================================================================*/
/*JP
 * \brief RawPCM Sint16初期化用コンフィグ構造体
 * \ingroup ATOMEXLIB_AT
 * \par 説明:
 * RawPCM Sint16を初期化する際に指定するパラメータです。<br>
 * ::criAtomExRawPcmSint16_CalculateWorkSize_AT 関数および
 * ::criAtomExRawPcmSint16_Initialize_AT 関数の config として指定します。
 * \par 備考:
 * デフォルト設定を使用する場合、 ::criAtomExRawPcmSint16_SetDefaultConfig_AT マクロで
 * 構造体にデフォルトパラメータをセットした後、::criAtomExRawPcmSint16_CalculateWorkSize_AT 関数
 * または ::criAtomExRawPcmSint16_Initialize_AT 関数に構造体を指定してください。<br>
 * \attention
 * 将来的にメンバが増える可能性があるため、 ::criAtomExRawPcmSint16_CalculateWorkSize_AT
 * マクロを使用しない場合には、使用前に必ず構造体をゼロクリアしてください。<br>
 * （構造体のメンバに不定値が入らないようご注意ください。）
 * \sa criAtomExRawPcmSint16_CalculateWorkSize_AT, criAtomExRawPcmSint16_Initialize_AT
 */
typedef struct CriAtomExRawPcmSint16ConfigTag_AT {
	CriFloat32					server_frequency;		/*JP< サーバー動作周波数		*/
	CriAtomSoundRendererType	sound_renderer_type;	/*JP< サウンドレンダラタイプ	*/
	CriSint32					sampling_rate;			/*JP< サンプリングレート		*/
} CriAtomExRawPcmSint16Config_AT;

/*==========================================================================
 *      CRI AtomEx ADX API for Automotive
 *=========================================================================*/
/*JP
 * \brief ADX初期化用コンフィグ構造体
 * \ingroup ATOMEXLIB_AT
 * \par 説明:
 * ADXを初期化する際に指定するパラメータです。<br>
 * ::criAtomExAdx_CalculateWorkSize 関数および
 * ::criAtomExAdx_Initialize 関数の config として指定します。
 * \par 備考:
 * デフォルト設定を使用する場合、 ::criAtomExAdx_SetDefaultConfig マクロで
 * 構造体にデフォルトパラメータをセットした後、::criAtomExAdx_CalculateWorkSize 関数
 * または ::criAtomExAdx_Initialize 関数に構造体を指定してください。<br>
 * \attention
 * 将来的にメンバが増える可能性があるため、 ::criAtomExAdx_CalculateWorkSize
 * マクロを使用しない場合には、使用前に必ず構造体をゼロクリアしてください。<br>
 * （構造体のメンバに不定値が入らないようご注意ください。）
 * \sa criAtomExAdx_CalculateWorkSize, criAtomExAdx_Initialize
 */
typedef struct CriAtomExAdxConfigTag {
	CriFloat32					server_frequency;		/*JP< サーバー動作周波数		*/
	CriAtomSoundRendererType	sound_renderer_type;	/*JP< サウンドレンダラタイプ	*/
	CriSint32					sampling_rate;			/*JP< サンプリングレート		*/
} CriAtomExAdxConfig;

/*==========================================================================
 *      CRI AtomEx ACB API
 *=========================================================================*/
struct CriAtomExAcbTag;
typedef struct CriAtomExAcbTag CriAtomExAcbObj;
/*JP
 * \brief ACBハンドル
 * \ingroup ATOMEXLIB_ACB
 * \par 説明:
 * キューシート情報を管理するハンドルです。<br>
 * ::criAtomExAcb_LoadAcbFile 関数等で読み込んだキューシートファイル内の
 * 音声を再生する場合、本ハンドルとキューIDをプレーヤに対してセットします。<br>
 * \sa criAtomExAcb_LoadAcbFile, criAtomExPlayer_SetCueId
 */
typedef CriAtomExAcbObj *CriAtomExAcbHn;

/*JP
 * \brief キューID
 * \ingroup ATOMEXLIB_ACB
 * \par 説明:
 * キューIDは、ユーザがオーサリングツール上でキューに対して割り当てた一意のIDです。<br>
 * キューIDをプログラム中で保持する際には、本変数型を用いて値を取り扱う必要があります。<br>
 * \sa criAtomExPlayer_SetCueId
 */
typedef CriSint32 CriAtomExCueId;

/*==========================================================================
 *      CRI AtomEx Voice Pool API
 *=========================================================================*/
struct CriAtomExVoicePoolTag;
typedef struct CriAtomExVoicePoolTag CriAtomExVoicePoolObj;
/*JP
 * \brief ボイスプールハンドル
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \par 説明:
 * ボイスプールを制御するためのハンドルです。<br>
 * ::criAtomExVoicePool_AllocateStandardVoicePool 関数等でボイスプールを作成した際、
 * 関数の戻り値として返されます。<br>
 * ボイスプールハンドルは、ボイスプールの情報取得や、ボイスプールを解放する
 * 際に使用します。
 * \sa criAtomExVoicePool_AllocateStandardVoicePool, criAtomExVoicePool_Free
 */
typedef struct CriAtomExVoicePoolTag *CriAtomExVoicePoolHn;

/*JP
 * \brief ボイスプール識別子
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \par 説明:
 * ボイスプール識別子は、ボイスプールを一意に識別するためのIDです。<br>
 * ボイスプール識別子をプログラム中で保持する際には、
 * 本変数型を用いて値を取り扱う必要があります。<br>
 * \par 備考
 * ボイスプール識別子は、以下の2つに対して指定する必要があります。<br>
 * 	- ボイスプール（ボイスプール作成用コンフィグ構造体で指定）
 * 	- プレーヤ（criAtomExPlayer_SetVoicePoolIdentifier関数で指定）
 * ボイスプールとプレーヤの両方に識別子を設定することで、
 * 当該プレーヤは当該ボイスプールからのみボイスを取得するようになります。<br>
 * <br>
 * 複数のボイスプールに同一のボイスプール識別子を指定することも可能です。<br>
 * \sa CriAtomExStandardVoicePoolConfig, criAtomExPlayer_SetVoicePoolIdentifier
 */
typedef CriUint32 CriAtomExVoicePoolIdentifier;

/*JP
 * \brief ADXボイスプール作成用コンフィグ構造体
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \par 説明:
 * ADXボイスプールの仕様を指定するための構造体です。<br>
 * ::criAtomExVoicePool_AllocateAdxVoicePool 関数に引数として渡します。<br>
 * \attention
 * 将来的にメンバが増える可能性があるため、 ::criAtomExVoicePool_SetDefaultConfigForAdxVoicePool
 * マクロを使用しない場合には、使用前に必ず構造体をゼロクリアしてください。<br>
 * （構造体のメンバに不定値が入らないようご注意ください。）
 * \sa criAtomExVoicePool_AllocateAdxVoicePool, criAtomExVoicePool_SetDefaultConfigForAdxVoicePool
 */
typedef struct CriAtomExAdxVoicePoolConfigTag {
	CriAtomExVoicePoolIdentifier identifier;	/*JP< ボイスプール識別子	*/
	CriSint32 num_voices;						/*JP< プールするボイスの数	*/
	CriAtomAdxPlayerConfig player_config;		/*JP< ボイスの仕様			*/
} CriAtomExAdxVoicePoolConfig;

/*JP
 * \brief サウンドジェネレータボイスプール作成用コンフィグ構造体
 * \ingroup ATOMEXLIB_AT
 * \par 説明:
 * サウンドジェネレータボイスプールの仕様を指定するための構造体です。<br>
 * ::criAtomExVoicePool_AllocateSoundGeneratorVoicePool 関数に引数として渡します。<br>
 * \attention
 * 将来的にメンバが増える可能性があるため、 ::criAtomExVoicePool_SetDefaultConfigForSoundGeneratorVoicePool
 * マクロを使用しない場合には、使用前に必ず構造体をゼロクリアしてください。<br>
 * （構造体のメンバに不定値が入らないようご注意ください。）
 * \sa criAtomExVoicePool_AllocateSoundGeneratorVoicePool, criAtomExVoicePool_SetDefaultConfigForSoundGeneratorVoicePool
 */
typedef struct CriAtomExSoundGeneratorVoicePoolConfigTag {
	CriAtomExVoicePoolIdentifier		identifier;		/*JP< ボイスプール識別子	*/
	CriSint32							num_voices;		/*JP< プールするボイスの数	*/
	CriAtomSoundGeneratorPlayerConfig	player_config;	/*JP< ボイスの仕様			*/
} CriAtomExSoundGeneratorVoicePoolConfig;

/*JP
 * \brief RawPCM Sint16ボイスプール作成用コンフィグ構造体
 * \ingroup ATOMEXLIB_AT
 * \par 説明:
 * RawPCM Sint16ボイスプールの仕様を指定するための構造体です。<br>
 * ::criAtomExVoicePool_AllocateRawPcmSint16VoicePool_AT 関数に引数として渡します。<br>
 * \attention
 * 将来的にメンバが増える可能性があるため、 ::criAtomExVoicePool_SetDefaultConfigForRawPcmSint16VoicePool_AT
 * マクロを使用しない場合には、使用前に必ず構造体をゼロクリアしてください。<br>
 * （構造体のメンバに不定値が入らないようご注意ください。）
 * \sa criAtomExVoicePool_AllocateRawPcmSint16VoicePool_AT, criAtomExVoicePool_SetDefaultConfigForRawPcmSint16VoicePool_AT
 */
typedef struct CriAtomExRawPcmSint16VoicePoolConfigTag_AT {
	CriAtomExVoicePoolIdentifier		identifier;		/*JP< ボイスプール識別子	*/
	CriSint32							num_voices;		/*JP< プールするボイスの数	*/
	CriAtomRawPcmSint16PlayerConfig_AT	player_config;	/*JP< ボイスの仕様			*/
} CriAtomExRawPcmSint16VoicePoolConfig_AT;

/*==========================================================================
 *      CRI AtomEx Player API
 *=========================================================================*/

/*JP
 * \brief プレーヤ作成用コンフィグ構造体
 * \ingroup ATOMEXLIB_PLAYER
 * \par 説明:
 * AtomExプレーヤを作成する際に、動作仕様を指定するための構造体です。<br>
 * ::criAtomExPlayer_Create 関数の引数に指定します。<br>
 * <br>
 * 作成されるプレーヤは、ハンドル作成時に本構造体で指定された設定に応じて、
 * 内部リソースを必要なだけ確保します。<br>
 * プレーヤが必要とするワーク領域のサイズは、本構造体で指定されたパラメータに応じて変化します。
 * \attention
 * 将来的にメンバが増える可能性があるため、 ::criAtomExPlayer_SetDefaultConfig
 * マクロを使用しない場合には、使用前に必ず構造体をゼロクリアしてください。<br>
 * （構造体のメンバに不定値が入らないようご注意ください。）
 * \sa criAtomExPlayer_Create,  criAtomExPlayer_SetDefaultConfig
 */
typedef struct CriAtomExPlayerConfigTag {
	/*JP
		\brief 最大パス文字列数
		\par 説明:
		AtomExプレーヤが保持するパス文字列の数です。<br>
		\par 備考:
		::criAtomExPlayer_SetFile 関数を実行すると、
		指定したパス文字列がAtomExプレーヤ内に保持されます。<br>
		AtomExプレーヤはデフォルト状態ではパス文字列を1つしか保持しません。<br>
		（メモリサイズ削減のため。）<br>
		プレーヤ作成時に指定する max_path_strings の数を増やせば、
		AtomExプレーヤは指定された数分のパス文字列を保存するようになります。<br>
		max_path_strings に2以上の値を指定することで、
		1つのプレーヤで複数のファイルを同時にパス指定で再生することが可能となります。<br>
		ただし、 max_path_strings の値に応じて必要なワーク領域のサイズは増加します。<br>
		（max_path_strings×max_pathバイトのメモリが必要となります。）<br>
		\sa criAtomExPlayer_SetDefaultConfig, criAtomExPlayer_SetFile
	*/
	CriSint32 max_path_strings;
	
	/*JP
		\brief 最大パス長
		\par 説明:
		AtomExプレーヤに指定可能なファイルパスの最大長です。<br>
		ファイル名を指定して音声を再生を行う場合、使用するパスの最大長を max_path 
		として指定する必要があります。<br>
		\par 備考:
		本パラメータは、パッキングされていない音声ファイルを、
		ファイル名を指定して再生する際にのみセットする必要があります。<br>
		ファイル名指定の再生を行わず、キューIDや波形データIDを指定して再生を行う場合、
		max_path を 0 に設定することが可能です。<br>
		\attention
		::criAtomExPlayer_SetDefaultConfig マクロで CriAtomExPlayerConfig 構造体に
		デフォルト値を設定した場合、 max_path には 0 がセットされます。<br>
		ファイル名を指定して再生を行う場合、 ::criAtomExPlayer_SetDefaultConfig 
		マクロを使用しないか、または ::criAtomExPlayer_SetDefaultConfig マクロ実行後
		に再度パスの最大長をセットする必要があります。<br>
		\sa criAtomExPlayer_SetDefaultConfig, criAtomExPlayer_SetFile
	*/
	CriSint32 max_path;
	
	/* 
		\brief 時刻更新の有無
		\par 説明:
		AtomExプレーヤが時刻更新処理を行うかどうかを指定します。<br>
		\par 備考:
		updates_time に CRI_FALSE を指定した場合、
		作成されたAtomExプレーヤは再生時刻の更新を行いません。<br>
		その結果、 ::criAtomExPlayer_GetTime 関数による再生時刻の取得は行えなくなりますが、
		音声再生時の処理負荷をわずかに下げることが可能となります。<br>
		\sa criAtomExPlayer_GetTime
	*/
	CriBool updates_time;
} CriAtomExPlayerConfig;

struct CriAtomExPlayerTag;
typedef struct CriAtomExPlayerTag CriAtomExPlayerObj;
/*JP
 * \brief プレーヤハンドル
 * \ingroup ATOMEXLIB_PLAYER
 * \par 説明:
 * CriAtomExPlayerHn は、音声再生用に作られたプレーヤを操作するためのハンドルです。<br>
 * ::criAtomExPlayer_Create 関数で音声再生用のプレーヤを作成すると、
 * 関数はプレーヤ操作用に、この"AtomExプレーヤハンドル"を返します。
 * <br>
 * データのセットや再生の開始、ステータスの取得等、プレーヤに対して行う操作は、
 * 全てAtomExプレーヤハンドルを介して実行されます。<br>
 * \sa criAtomExPlayer_Create
 */
typedef CriAtomExPlayerObj *CriAtomExPlayerHn;

/*JP
 * \brief プレーヤステータス
 * \ingroup ATOMEXLIB_PLAYER
 * \par 説明:
 * AtomExプレーヤの再生状態を示す値です。<br>
 * ::criAtomExPlayer_GetStatus 関数で取得可能です。<br>
 * <br>
 * 再生状態は、通常以下の順序で遷移します。<br>
 * -# CRIATOMEXPLAYER_STATUS_STOP
 * -# CRIATOMEXPLAYER_STATUS_PREP
 * -# CRIATOMEXPLAYER_STATUS_PLAYING
 * -# CRIATOMEXPLAYER_STATUS_PLAYEND
 * .
 * AtomExプレーヤ作成直後の状態は、停止状態（ CRIATOMEXPLAYER_STATUS_STOP ）です。<br>
 * ::criAtomExPlayer_SetData 関数等でデータをセットし、 ::criAtomExPlayer_Start 関数を
 * 実行すると、再生準備状態（ CRIATOMEXPLAYER_STATUS_PREP ）に遷移し、再生準備を始めます。<br>
 * データが充分供給され、再生準備が整うと、ステータスは再生中（ CRIATOMEXPLAYER_STATUS_PLAYING ）
 * に変わり、音声の出力が開始されます。<br>
 * セットされたデータを全て再生し終えた時点で、ステータスは再生完了
 * （ CRIATOMEXPLAYER_STATUS_PLAYEND ）に変わります。
 * \par 備考
 * AtomExプレーヤは、Atomプレーヤと異なり、1つのプレーヤで複数音の再生が可能です。<br>
 * そのため、再生中のAtomExプレーヤに対して ::criAtomExPlayer_Start 関数を実行すると、
 * 2つの音が重なって再生されます。<br>
 * 再生中に ::criAtomExPlayer_Stop 関数を実行した場合、AtomExプレーヤで再生中の全ての音声
 * が停止し、ステータスは CRIATOMEXPLAYER_STATUS_STOP に戻ります。<br>
 * （ ::criAtomExPlayer_Stop 関数の呼び出しタイミングによっては、 CRIATOMEXPLAYER_STATUS_STOP 
 * に遷移するまでに時間がかかる場合があります。）<br>
 * <br>
 * 1つのAtomExプレーヤで複数回 ::criAtomExPlayer_Start 関数を実行した場合、
 * 1つでも再生準備中の音があれば、ステータスは CRIATOMEXPLAYER_STATUS_PREP 状態になります。<br>
 * （全ての音声が再生中の状態になるまで、ステータスは CRIATOMEXPLAYER_STATUS_PLAYING 状態に
 * 遷移しません。）<br>
 * また、 CRIATOMEXPLAYER_STATUS_PLAYING 状態のプレーヤに対し、再度 ::criAtomExPlayer_Start 
 * 関数を実行した場合、ステータスは一時的に CRIATOMEXPLAYER_STATUS_PREP に戻ります。<br>
 * <br>
 * 再生中に不正なデータを読み込んだ場合や、ファイルアクセスに失敗した場合、
 * ステータスは CRIATOMEXPLAYER_STATUS_ERROR に遷移します。<br>
 * 複数の音声を再生中にある音声でエラーが発生した場合、プレーヤのステータスは
 * 他の音声の状態に関係なく、 CRIATOMEXPLAYER_STATUS_ERROR に遷移します。<br>
 * \sa criAtomExPlayer_GetStatus, criAtomExPlayer_SetData, criAtomExPlayer_Start, criAtomExPlayer_Stop
 */
typedef enum CriAtomExPlayerStatusTag {
	CRIATOMEXPLAYER_STATUS_STOP = 0,		/*JP< 停止中		*/
	CRIATOMEXPLAYER_STATUS_PREP,			/*JP< 再生準備中	*/
	CRIATOMEXPLAYER_STATUS_PLAYING,			/*JP< 再生中		*/
	CRIATOMEXPLAYER_STATUS_PLAYEND,			/*JP< 再生完了		*/
	CRIATOMEXPLAYER_STATUS_ERROR,			/*JP< エラーが発生	*/
	CRIATOMEXPLAYER_STATUS_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExPlayerStatus;

/*JP
 * \brief 再生ID
 * \ingroup ATOMEXLIB_PLAYER
 * \par 説明:
 * ::criAtomExPlayer_Start 関数実行時に返されるIDです。<br>
 * プレーヤ単位ではなく、 ::criAtomExPlayer_Start 関数で再生した個々の音声に対して
 * パラメータ変更や状態取得を行いたい場合、本IDを使用して制御を行う必要があります。<br>
 * 無効な再生IDは::CRIATOMEX_INVALID_PLAYBACK_IDです。
 * \sa criAtomExPlayer_Start, criAtomExPlayback_GetStatus, CRIATOMEX_INVALID_PLAYBACK_ID
 */
typedef CriUint32 CriAtomExPlaybackId;

/*==========================================================================
 *      CRI AtomEx Sequencer API
 *=========================================================================*/
/*JP
 * \brief シーケンスループ解除コールバック
 * \ingroup ATOMEXLIB_SEQUENCER
 * \par 説明:
 * \param[in]	cue_id	ループエンドに到達したキューID
 * \return				ループ解除フラグ（ループ解除：CRI_TRUE／ループ継続：CRI_FALSE）
 * AtomExライブラリのシーケンスループエンド時に発生するループ解除コールバック関数型です。<br>
 * 引数 cue_id には、本コールバックの発生元キューのIDが入力されます。<br>
 * 戻り値にCRI_TRUEを指定すると、当該キューのループを解除し、再生を終了させることが可能です。<br>
 * コールバック関数の登録には ::criAtomExSequencer_SetBreakLoopCallback_AT 関数を使用します。<br>
 * 登録したコールバック関数は、サーバ関数内でループエンドに到達したタイミングで必ず実行されます。<br>
 * そのため、サーバ処理への割り込みを考慮しないAPIを実行した場合、
 * エラーが発生したり、デッドロックが発生する可能性があります。<br>
 * 基本的に、コールバック関数内ではAtomライブラリAPIを使用しないでください。<br>
 * 本コールバック関数内で長時間処理をブロックすると、音切れ等の問題が発生しますので、
 * ご注意ください。<br>
 * \sa criAtomExSequencer_SetBreakLoopCallback_AT
 */
typedef CriBool (CRIAPI *CriAtomExSequencerBreakLoopCbFunc_AT)(CriAtomExCueId cue_id);

/*==========================================================================
 *      CRI AtomEx API for Automotive
 *=========================================================================*/
/*JP
 * \brief Atomライブラリ初期化用コンフィグ構造体
 * \ingroup ATOMEXLIB_AT
 * CRI Atomライブラリの動作仕様を指定するための構造体です。<br>
 * ::criAtomEx_Initialize_AT 関数の引数に指定します。<br>
 * \sa criAtomEx_Initialize_AT, criAtomEx_SetDefaultConfig_AT
 */
typedef struct CriAtomExConfigTag_AT {
	CriAtomExConfig					atom_ex;					/*JP< AtomEx初期化用コンフィグ構造体			*/
	CriAtomExHcaMxConfig			hca_mx;						/*JP< HCA-MX初期化用コンフィグ構造体			*/
	CriAtomExSoundGeneratorConfig	sound_generator;			/*JP< SoundGenerator初期化用コンフィグ構造体	*/
	CriAtomExRawPcmFloatConfig_AT	raw_pcm_float;				/*JP< RawPCM Float初期化用コンフィグ構造体		*/
	CriAtomExRawPcmSint16Config_AT	raw_pcm_sint16;				/*JP< RawPCM Sint16初期化用コンフィグ構造体		*/
	CriAtomExAdxConfig				adx;						/*JP< ADX初期化用コンフィグ構造体		*/
	CriBool							initialize_hca_mx;			/*JP< HCA-MXを初期化するかどうか				*/
	CriBool							initialize_sound_generator;	/*JP< SoundGeneratorを初期化するかどうか		*/
	CriBool							initialize_raw_pcm_float;	/*JP< RawPCM Floatを初期化するかどうか			*/
	CriBool							initialize_raw_pcm_sint16;	/*JP< RawPCM Sint16を初期化するかどうか			*/
	CriBool							initialize_adx;				/*JP< ADXを初期化するかどうか			*/
	CriSint32						sampling_rate;				/*JP< サンプリングレート						*/
	CriUint32						version;					/*JP< モジュールのバージョン番号				*/
} CriAtomExConfig_AT;


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
 * \brief メモリ確保関数の登録
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	func		メモリ確保関数
 * \param[in]	obj			ユーザ指定オブジェクト
 * \par 説明:
 * CRI Atomライブラリにメモリ確保関数を登録します。<br>
 * CRI Atomライブラリ内がライブラリ内で行うメモリ確保処理を、
 * ユーザ独自のメモリ確保処理に置き換えたい場合に使用します。<br>
 * <br>
 * 本関数の使用手順は以下のとおりです。<br>
 * (1) ::CriAtomMallocFunc インターフェースに副ったメモリ確保関数を用意する。<br>
 * (2) ::criAtom_SetUserMallocFunction 関数を使用し、CRI Atomライブラリに対して
 * メモリ確保関数を登録する。<br>
 * <br>
 * 具体的なコードの例は以下のとおりです。
 * \par 例:
 * \code
 * ## 独自のメモリ確保関数を用意
 * void *user_malloc(void *obj, CriUint32 size)
 * {
 * 	void *mem;
 *
 * 	## メモリの確保
 * 	mem = malloc(size);
 *
 * 	return (mem);
 * }
 *
 * main()
 * {
 * 		:
 * 	## メモリ確保関数の登録
 * 	criAtom_SetUserMallocFunction(user_malloc, NULL);
 * 		:
 * }
 *	※上記仮想コード内の"##"は行末までのコメントアウト開始を示しています。
 * \endcode
 * \par 備考:
 * 引数の obj に指定した値は、 ::CriAtomMallocFunc に引数として渡されます。<br>
 * メモリ確保時にメモリマネージャ等を参照する必要がある場合には、
 * 当該オブジェクトを本関数の引数にセットしておき、コールバック関数で引数を経由
 * して参照してください。<br>
 * \attention
 * メモリ確保関数を登録する際には、合わせてメモリ解放関数（ ::CriAtomFreeFunc ）を
 * 登録する必要があります。
 * \sa CriAtomMallocFunc, criAtom_SetUserFreeFunction
 */
void CRIAPI criAtom_SetUserMallocFunction(CriAtomMallocFunc func, void *obj);

/*JP
 * \brief メモリ解放関数の登録
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	func		メモリ解放関数
 * \param[in]	obj			ユーザ指定オブジェクト
 * \par 説明:
 * CRI Atomライブラリにメモリ解放関数を登録します。<br>
 * CRI Atomライブラリ内がライブラリ内で行うメモリ解放処理を、
 * ユーザ独自のメモリ解放処理に置き換えたい場合に使用します。<br>
 * <br>
 * 本関数の使用手順は以下のとおりです。<br>
 * (1) ::CriAtomFreeFunc インターフェースに副ったメモリ解放関数を用意する。<br>
 * (2) ::criAtom_SetUserFreeFunction 関数を使用し、CRI Atomライブラリに対して
 * メモリ解放関数を登録する。<br>
 * <br>
 * 具体的なコードの例は以下のとおりです。
 * \par 例:
 * \code
 * ## 独自のメモリ解放関数を用意
 * void user_free(void *obj, void *mem)
 * {
 * 	## メモリの解放
 * 	free(mem);
 *
 * 	return;
 * }
 *
 * main()
 * {
 * 		:
 * 	## メモリ解放関数の登録
 * 	criAtom_SetUserFreeFunction(user_free, NULL);
 * 		:
 * }
 *	※上記仮想コード内の"##"は行末までのコメントアウト開始を示しています。
 * \endcode
 * \par 備考:
 * 引数の obj に指定した値は、 ::CriAtomFreeFunc に引数として渡されます。<br>
 * メモリ確保時にメモリマネージャ等を参照する必要がある場合には、
 * 当該オブジェクトを本関数の引数にセットしておき、コールバック関数で引数を経由
 * して参照してください。<br>
 * \attention
 * メモリ解放関数を登録する際には、合わせてメモリ確保関数（ ::CriAtomMallocFunc ）を
 * 登録する必要があります。
 * \sa CriAtomFreeFunc, criAtom_SetUserMallocFunction
 */
void CRIAPI criAtom_SetUserFreeFunction(CriAtomFreeFunc func, void *obj);

/*==========================================================================
 *      CRI Atom AWB API
 *=========================================================================*/
/*JP
 * \brief オンメモリAWBハンドルの作成(Automotive向け)
 * \ingroup ATOMLIB_AWB
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
 * Fixed Memory方式を用いる場合は、::CRIATOMAWB_WORKSIZE_FOR_LOADFROMMEMORYAT 関数を使って
 * 必要なワーク領域サイズを求めてください。<br>
 * ワーク領域とは異なり、awb_mem は必ずユーザの責任で管理する必要がある点には注意してください。<br>
 * <br>
 * \attention
 * 本関数が成功すると、 awb_memで渡されたメモリ領域の参照を開始します。<br>
 * なお、awb_mem で指すメモリ領域は ::criAtomAwb_Release 関数実行後に手動で解放してください。
 * \sa CRIATOMAWB_WORKSIZE_FOR_LOADFROMMEMORYAT,criAtomAwb_Release
 */
CriAtomAwbHn CRIAPI criAtomAwb_LoadFromMemoryAt(
	const void *awb_mem, CriSint32 awb_mem_size, void *work, CriSint32 work_size);

/*JP
 * \brief AWBハンドルの解放
 * \ingroup ATOMLIB_AWB
 * \param[in]	awb	AWBハンドル
 * \return		なし
 * \par 説明:
 * AWBハンドルを解放します。<br>
 * 使い終わったAWBハンドルは、本関数で解放してください。<br>
 * 解放したAWBハンドルは無効なハンドルになるので、使用しないでください。<br>
 * \attention
 * 本関数を実行すると、指定したAWBデータを参照しているAtomプレーヤが存在しないか、
 * ライブラリ内で検索処理が行われます。<br>
 * そのため、本関数実行中に他スレッドでAtomプレーヤの作成／破棄を行うと、
 * アクセス違反やデッドロック等の重大な不具合を誘発する恐れがあります。<br>
 * 本関数実行時にAtomプレーヤの作成／破棄を他スレッドで行う必要がある場合、
 * 本関数を ::criAtom_Lock 関数でロックしてから実行してください。<br>
 * <br>
 * AtomExプレーヤを使用してAWBファイルを再生する場合、
 * 再生中に本関数でAWBハンドルを破棄してはいけません。<br>
 * 必ずAtomExプレーヤを停止させてさせてから本関数を実行してください。<br>
 * \sa criAtomAwb_LoadToc, criAtomAwb_LoadTocAsync, criAtomAwb_GetStatus
 */
void CRIAPI criAtomAwb_Release(CriAtomAwbHn awb);

/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*JP
 * \brief サーバ処理の実行
 * \ingroup ATOMEXLIB_GLOBAL
 * \par 説明:
 * CRI Atomライブラリの内部状態を更新します。<br>
 * アプリケーションは、この関数を定期的に実行する必要があります。<br>
 * <br>
 * サーバ処理を実行すべき回数は、ライブラリ初期化時のパラメータに依存します。<br>
 * ライブラリ初期化時にスレッドモデルを ::CRIATOMEX_THREAD_MODEL_MULTI に設定した場合、
 * リアルタイム性の要求される処理は全てCRI Atomライブラリ内で定期的に自動実行されるため、
 * 本関数の呼び出し頻度は少なくても問題は発生しません。<br>
 * （最低でも毎秒1回程度実行されていれば、音切れ等の問題が発生することはありません。）<br>
 * ライブラリ初期化時にスレッドモデルを ::CRIATOMEX_THREAD_MODEL_SINGLE や
 * ::CRIATOMEX_THREAD_MODEL_USER_MULTI に設定した場合、ファイルの読み込み管理や、
 * データのデコード、音声の出力等、音声再生に必要な処理のほぼ全てが本関数内で実行されます。<br>
 * また、音声再生処理に同期して、CRI File Systemライブラリのファイルアクセスとデータ展開処理を実行します。<br>
 * そのため、ライブラリ初期化時に指定したサーバ処理の実行頻度（ ::CriAtomExConfig 構造体の
 * server_frequency ）を下回る頻度で本関数を実行した場合や、
 * 大きいデータの読み込み、圧縮ファイルの読み込み等を行う場合、
 * 音切れ等の問題が発生する可能性があるので注意してください。<br>
 * \par 備考:
 * ライブラリ初期化時にスレッドモデルを ::CRIATOMEX_THREAD_MODEL_MULTI に設定した場合でも、
 * 本関数を実行する必要があります。<br>
 * （スレッドモデルを ::CRIATOMEX_THREAD_MODEL_MULTI の場合、ステータス更新等、ごく一部の
 * 処理のみを行うため、本関数内で長時間処理がブロックされることはありません。）
 * <br>
 * CRI File Systemライブラリのサーバ処理は、CRI Atomライブラリ内部で実行されます。<br>
 * そのため、本関数を実行している場合、アプリケーション側で別途CRI File Systemライブラリ
 * のサーバ処理を呼び出す必要はありません。<br>
 */
void CRIAPI criAtomEx_ExecuteMain(void);

/*JP
 * \brief オンメモリACFデータの登録に必要なワーク領域サイズの計算(Automotive向け)
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	acf_data		ACFデータアドレス
 * \param[in]	acf_data_size	ACFデータサイズ
 * \return		CriSint32		ワーク領域サイズ
 * \retval		0以上			正常に処理が完了
 * \retval		-1				エラーが発生
 * \par 説明:
 * ::criAtomEx_RegisterAcfDataAt 関数の実行に必要なワーク領域サイズを計算します。<br>
 * ::criAtomEx_SetUserAllocator マクロによるアロケータ登録を行わずに
 * ::criAtomEx_RegisterAcfData 関数でACF情報を登録する際には、
 * 本関数が返すサイズ分のメモリをワーク領域として渡す必要があります。<br>
 * <br>
 * ワーク領域サイズの計算に失敗すると、本関数は -1 を返します。<br>
 * ワーク領域サイズの計算に失敗した理由については、エラーコールバックのメッセージで確認可能です。<br>
 * \attention
 * ワーク領域のサイズはライブラリ初期化時（ ::criAtomEx_Initialize 関数実行時）
 * に指定したパラメータによって変化します。<br>
 * そのため、本関数を実行する前に、ライブラリを初期化しておく必要があります。<br>
 * \sa criAtomEx_RegisterAcfDataAt
 */
CriSint32 CRIAPI criAtomEx_CalculateWorkSizeForRegisterAcfDataAt(
	const void *acf_data, CriSint32 acf_data_size);

/*JP
 * \brief オンメモリACFデータの登録(Automotive向け)
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	acf_data		ACFデータアドレス
 * \param[in]	acf_data_size	ACFデータサイズ
 * \param[in]	work		ワーク領域
 * \param[in]	work_size	ワーク領域サイズ
 * \par 説明:
 * メモリ上に配置されたACFデータをライブラリに取り込みます。<br>
 * ACF情報の登録に必要なワーク領域のサイズは、
 * ::criAtomEx_CalculateWorkSizeForRegisterAcfDataAt 関数で計算します。<br>
 * \par 備考:
 * ::criAtomEx_SetUserAllocator マクロを使用してアロケータを登録済みの場合、
 * 本関数にワーク領域を指定する必要はありません。<br>
 * （ work に NULL 、 work_size に 0 を指定することで、登録済みのアロケータ
 * から必要なワーク領域サイズ分のメモリが動的に確保されます。）
 * \attention
 * 本関数を実行する前に、ライブラリを初期化しておく必要があります。<br>
 * <br>
 * 本関数にセットしたデータ領域とワーク領域は、 ::criAtomEx_UnregisterAcf 関数を実行するまでの間、
 * アプリケーションで保持する必要があります。<br>
 * （ ::criAtomEx_UnregisterAcf 関数実行前に、ワーク領域のメモリを解放しないでください。）
 * また、データ領域の一部はワークとして使用されます。<br>
 * \sa criAtomEx_UnregisterAcf
 */
void CRIAPI criAtomEx_RegisterAcfDataAt(
	const void *acf_data, CriSint32 acf_data_size, void *work, CriSint32 work_size);

/*JP
 * \brief ACFの登録解除
 * \ingroup ATOMEXLIB_GLOBAL
 * \par 説明:
 * ACF情報の登録を解除します。<br>
 * \attention
 * ::criAtomEx_RegisterAcfFile 関数実行前に本関数を実行することはできません。<br>
 * \sa criAtomEx_RegisterAcfConfig, criAtomEx_RegisterAcfData, criAtomEx_RegisterAcfFile
 */
void CRIAPI criAtomEx_UnregisterAcf(void);

/*JP
 * \brief 再生中のキューIDの取得
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[out]	ids				再生中キューID受け取り用配列
 * \param[in]	length			再生中キューID受け取り用配列要素数
 * \return		CriSint32		再生中キューIDの個数
 * \retval		0以上			正常に処理が完了
 * \retval		-1				エラーが発生
 * \par 説明:
 * 全てのプレーヤにて再生中キューIDを取得します。<br>
 * 再生中キューIDの取得に成功すると、第1引数（ids配列）に再生中キューIDが保存され、
 * 再生中キューIDの個数が戻り値として返ります。
 * また、第1引数にNULL、第2引数（length）に0を指定した場合、
 * 再生中キューIDの個数のみを取得することが出来ます。
 * \par 備考:
 * 出力先の第1引数には、再生が行われた順にキューIDが格納されています。<br>
 * <br>
 * 同一のキューIDが複数再生されている場合、その再生数分が配列に格納されます。<br>
 * <br>
 * 本関数で取得出来る最大の再生中キューIDの個数は ::CriAtomExConfig の max_virtual_voices と同値です。
 * <br>
 * 第2引数に指定した要素数よりも再生中キューIDの個数が上回る場合、再生が行われた順に格納されたキューIDを
 * 第2引数に指定した要素数分のみ取得することが出来ます。<br>
 * \attention
 * 再生中キューIDの配列およびID数は ::criAtomEx_ExecuteMain 関数実行後に更新されます。<br>
 * そのため、 ::criAtomExPlayer_Start 関数や ::criAtomExPlayer_Stop 関数実行直後に本関数を実行した場合、
 * 各関数実行前の ::criAtomEx_ExecuteMain 関数実行後と同様な結果が取得されます。<br>
 * <br>
 * ::criAtomExPlayer_Stop 関数の実行などによって停止処理に移行しているキューは再生中とみなされません。
 */
CriSint32 CRIAPI criAtomEx_GetPlayingCueIds(CriAtomExCueId *ids, CriSint32 length);

/*==========================================================================
 *      CRI AtomEx ACB API
 *=========================================================================*/
/*JP
 * \brief オンメモリACBデータのロードに必要なワーク領域サイズの計算(Automotive向け)
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_data		ACBデータアドレス
 * \param[in]	acb_data_size	ACBデータサイズ
 * \param[in]	awb_hn			Stream再生用AWBハンドル
 * \return		CriSint32	ワーク領域サイズ
 * \par 説明:
 * ::criAtomExAcb_LoadAcbDataWithAwbHnAt 関数の実行に必要なワーク領域サイズを計算します。
 * ::criAtomEx_SetUserAllocator マクロによるアロケータ登録を行わずに
 * ::criAtomExAcb_LoadAcbDataWithAwbHnAt 関数でAWBデータをロードする際には、
 * 本関数が返すサイズ分のメモリをワーク領域として渡す必要があります。<br>
 * <br>
 * ワーク領域サイズの計算に失敗すると、本関数は -1 を返します。<br>
 * ワーク領域サイズの計算に失敗した理由については、エラーコールバックのメッセージで確認可能です。<br>
 * \attention
 * ワーク領域のサイズはライブラリ初期化時（ ::criAtomEx_Initialize 関数実行時）
 * に指定したパラメータによって変化します。<br>
 * そのため、本関数を実行する前に、ライブラリを初期化しておく必要があります。<br>
 * \sa criAtomExAcb_LoadAcbDataWithAwbHnAt
 */
CriSint32 CRIAPI criAtomExAcb_CalculateWorkSizeForLoadAcbDataWithAwbHnAt(
	const void *acb_data, CriSint32 acb_data_size, CriAtomAwbHn awb_hn);

/*JP
 * \brief オンメモリACBデータのロード(Automotive向け)
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_data		ACBデータアドレス
 * \param[in]	acb_data_size	ACBデータサイズ
 * \param[in]	awb_hn			Stream再生用AWBハンドル
 * \param[in]	work			オンメモリACB用ワーク領域へのポインタ
 * \param[in]	work_size		オンメモリACB用ワーク領域サイズ
 * \return		CriAtomExAcbHn	ACBハンドル
 * \par 説明:
 * ACBデータをロードし、キュー再生に必要な情報を取り込みます。<br>
 * ACBデータのロードに必要なワーク領域のサイズは、
 * ::criAtomExAcb_CalculateWorkSizeForLoadAcbDataWithAwbHnAt 関数で計算します。<br>
 * <br>
 * 第3引数の awb_hn には、ストリーム再生用のAWBハンドルを指定します。<br>
 * （オンメモリ再生のみのACBデータをロードする場合、 awb_hn 
 * にセットした値は無視されます。）<br>
 * <br>
 * ACBデータをロードすると、ACBデータにアクセスするためのACBハンドル
 * （ ::CriAtomExAcbHn ）が返されます。<br>
 * AtomExプレーヤに対し、 ::criAtomExPlayer_SetCueId 関数でACBハンドル、および再生する
 * キューのIDをセットすることで、ACBデータ内のキューを再生することが可能です。<br>
 * <br>
 * ACBファイルのロードに成功すると、本関数は戻り値として ACB ハンドルを返します。<br>
 * リードエラー等によりACBファイルのロードに失敗した場合、本関数は戻り値として
 * CRI_NULL を返します。<br>
 * \par 備考:
 * ::criAtomEx_SetUserAllocator マクロを使用してアロケータを登録済みの場合、
 * 本関数にワーク領域を指定する必要はありません。<br>
 * （ work に NULL 、 work_size に 0 を指定することで、登録済みのアロケータ
 * から必要なワーク領域サイズ分のメモリが動的に確保されます。）
 * <br>
 * 本関数は即時復帰関数です。<br>
 * ACBファイルを事前にメモリにロードしてから本関数を実行することで、
 * ACBハンドル作成時に処理がブロックされるのを回避可能です。<br>
 * \attention
 * 本関数にてセットしたデータ領域やワーク領域のメモリ内容とストリーム用AWBハンドルはACBハンドル破棄時
 * までアプリケーション中で保持し続ける必要があります。<br>
 * （セット済みのワーク領域に値を書き込んだり、メモリ解放したりしてはいけません。）<br>
 * また、データ領域の一部はワークとして使用されます。<br>
 * <br>
 * ACBハンドルは内部的にバインダ（ CriFsBinderHn ）を確保します。<br>
 * ACBファイルをロードする場合、ACBハンドル数分のバインダが確保できる設定で
 * Atomライブラリ（またはCRI File Systemライブラリ）を初期化する必要があります。<br>
 * \attention
 * 本関数を実行する前に、ライブラリを初期化しておく必要があります。<br>
 * \sa criAtomExAcb_CalculateWorkSizeForLoadAcbDataWithAwbHnAt, CriAtomExAcbHn, criAtomExPlayer_SetCueId
 */
CriAtomExAcbHn CRIAPI criAtomExAcb_LoadAcbDataWithAwbHnAt(
	const void *acb_data, CriSint32 acb_data_size, CriAtomAwbHn awb_hn,
	void *work, CriSint32 work_size);

/*JP
 * \brief ACBハンドルのリリース
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACBハンドル
 * \par 説明:
 * ACBハンドルを解放します。<br>
 * ::criAtomEx_SetUserAllocator マクロを使用してアロケータを登録済みの場合、
 * ACBハンドル作成時に確保されたメモリ領域が解放されます。<br>
 * （ACBハンドル作成時にワーク領域を渡した場合、本関数実行後であれば
 * ワーク領域を解放可能です。）<br>
 * \par 備考:
 * 本関数でACBハンドルを破棄する際には、
 * 当該ACBハンドルを参照しているキューは全て停止されます。<br>
 * （本関数実行後に、ACBハンドルの作成に使用したワーク領域や、
 * ACBデータが配置されていた領域が参照されることはありません。）<br>
 * \attention
 * 本関数を実行すると、破棄しようとしているACBデータを参照している
 * Atomプレーヤが存在しないか、ライブラリ内で検索処理が行われます。<br>
 * そのため、本関数実行中に他スレッドでAtomプレーヤの作成／破棄を行うと、
 * アクセス違反やデッドロック等の重大な不具合を誘発する恐れがあります。<br>
 * 本関数実行時にAtomプレーヤの作成／破棄を他スレッドで行う必要がある場合、
 * Atomプレーヤの作成／破棄を ::criAtomEx_Lock 関数でロックしてから実行ください。<br>
 * \sa criAtomExAcb_LoadAcbData, criAtomExAcb_LoadAcbFile
 */
void CRIAPI criAtomExAcb_Release(CriAtomExAcbHn acb_hn);

/*==========================================================================
 *      CRI AtomEx Voice Pool API
 *=========================================================================*/
/*JP
 * \brief ADXボイスプール作成用ワーク領域サイズの計算
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[in]	config		ADXボイスプール作成用コンフィグ構造体
 * \return		CriSint32	ワーク領域サイズ
 * \retval		0以上		正常に処理が完了
 * \retval		-1			エラーが発生
 * \par 説明:
 * ADXボイスプールの作成に必要なワーク領域のサイズを計算します。<br>
 * ::criAtomEx_SetUserAllocator マクロによるアロケータ登録を行わずに
 * ::criAtomExVoicePool_AllocateAdxVoicePool 関数でボイスプールを作成する際には、
 * ::criAtomExVoicePool_AllocateAdxVoicePool 関数に本関数が返すサイズ分のメモリをワーク
 * 領域として渡す必要があります。<br>
 * <br>
 * ワーク領域サイズの計算に失敗すると、本関数は -1 を返します。<br>
 * ワーク領域サイズの計算に失敗した理由については、エラーコールバックのメッセージで確認可能です。<br>
 * \par 備考:
 * ボイスプールの作成に必要なワークメモリのサイズは、プレーヤ作成用コンフィグ
 * 構造体（ ::CriAtomExAdxVoicePoolConfig ）の内容によって変化します。<br>
 * <br>
 * 引数にNULLを指定した場合、デフォルト設定
 * （ ::criAtomExVoicePool_SetDefaultConfigForAdxVoicePool マクロ使用時と
 * 同じパラメータ）でワーク領域サイズを計算します。
 * <br>
 * 引数 config の情報は、関数内でのみ参照されます。<br>
 * 関数を抜けた後は参照されませんので、関数実行後に config の領域を解放しても
 * 問題ありません。
 * \attention
 * ワーク領域のサイズはライブラリ初期化時（ ::criAtomEx_Initialize 関数実行時）
 * に指定したパラメータによって変化します。<br>
 * そのため、本関数を実行する前に、ライブラリを初期化しておく必要があります。<br>
 * \sa criAtomExVoicePool_AllocateAdxVoicePool
 */
CriSint32 CRIAPI criAtomExVoicePool_CalculateWorkSizeForAdxVoicePool(
	const CriAtomExAdxVoicePoolConfig *config);

/*JP
 * \brief ADXボイスプールの作成
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[in]	config		ADXボイスプール作成用コンフィグ構造体
 * \param[in]	work		ワーク領域
 * \param[in]	work_size	ワーク領域サイズ
 * \return		CriAtomExVoicePoolHn	ボイスプールハンドル
 * \par 説明：
 * ADXボイスプールを作成します。<br>
 * ボイスプールを作成する際には、ワーク領域としてメモリを渡す必要があります。<br>
 * 必要なメモリのサイズは、 ::criAtomExVoicePool_CalculateWorkSizeForAdxVoicePool 
 * 関数で計算します。<br>
 * （::criAtomEx_SetUserAllocator マクロを使用してアロケータを登録済みの場合、
 * 本関数にワーク領域を指定する必要はありません。）<br>
 * <br>
 * 本関数を実行することで、ADX再生が可能なボイスがプールされます。<br>
 * AtomExプレーヤでADXデータ（もしくはADXデータを含むキュー）の再生を行うと、
 * AtomExプレーヤは作成されたADXボイスプールからボイスを取得し、再生を行います。<br>
 * <br>
 * ボイスプールの作成に成功すると、戻り値としてボイスプールハンドルが返されます。<br>
 * アプリケーション終了時には、作成したボイスプールを ::criAtomExVoicePool_Free 
 * 関数で破棄する必要があります。<br>
 * <br>
 * ボイスプールの作成に失敗すると、本関数はNULLを返します。<br>
 * ボイスプールの作成に失敗した理由については、エラーコールバックのメッセージで確認可能です。<br>
 * \par 備考:
 * ボイスプール作成時には、プール作成用コンフィグ構造体
 * （ ::CriAtomExAdxVoicePoolConfig 構造体の num_voices ）
 * で指定した数分のボイスが、ライブラリ内で作成されます。<br>
 * 作成するボイスの数が多いほど、同時に再生可能なADX音声の数は増えますが、
 * 反面、使用するメモリは増加します。<br>
 * <br>
 * ボイスプール作成時には、ボイス数の他に、再生可能な音声のチャンネル数、
 * サンプリング周波数、ストリーム再生の有無を指定します。<br>
 * <br>
 * ボイスプール作成時に指定する音声チャンネル数（ ::CriAtomExAdxVoicePoolConfig 
 * 構造体の player_config.max_channels ）は、ボイスプール内のボイスが再生できる
 * 音声データのチャンネル数になります。<br>
 * チャンネル数を少なくすることで、ボイスプールの作成に必要なメモリサイズは
 * 小さくなりますが、指定されたチャンネル数を越えるデータは再生できなくなります。<br>
 * 例えば、ボイスプールをモノラルで作成した場合、ステレオのデータは再生できません。<br>
 * （ステレオデータを再生する場合、AtomExプレーヤは、ステレオが再生可能な
 * ボイスプールからのみボイスを取得します。）<br>
 * ただし、ステレオのボイスプールを作成した場合、モノラルデータ再生時にステレオ
 * ボイスプールのボイスが使用される可能性はあります。<br>
 * <br>
 * サンプリングレート（ ::CriAtomExAdxVoicePoolConfig 構造体の 
 * player_config.max_sampling_rate ）についても、値を下げることでもボイスプール
 * に必要なメモリサイズは小さくすることが可能ですが、指定されたサンプリングレート
 * を越えるデータは再生できなくなります。<br>
 * （指定されたサンプリングレート以下のデータのみが再生可能です。）<br>
 * <br>
 * ストリーミング再生の有無（::CriAtomExAdxVoicePoolConfig 構造体の 
 * player_config.streaming_flag ）についても、オンメモリ再生のみのボイスプールは
 * ストリーミング再生可能なボイスプールに比べ、サイズが小さくなります。<br>
 * <br>
 * 尚、AtomExプレーヤがデータを再生した際に、
 * ボイスプール内のボイスが全て使用中であった場合、
 * ボイスプライオリティによる発音制御が行われます。<br>
 * （ボイスプライオリティの詳細は ::criAtomExPlayer_SetVoicePriority 
 * 関数の説明をご参照ください。）<br>
 * \attention
 * 本関数を実行する前に、ライブラリを初期化しておく必要があります。<br>
 * <br>
 * 本関数にワーク領域をセットした場合、セットした領域のメモリをボイスプール破棄時
 * までアプリケーション中で保持し続ける必要があります。<br>
 * （セット済みのワーク領域に値を書き込んだり、メモリ解放したりしてはいけません。）<br>
 * <br>
 * 引数 config の情報は、関数内でのみ参照されます。<br>
 * 関数を抜けた後は参照されませんので、関数実行後に config の領域を解放しても
 * 問題ありません。
 * <br>
 * ストリーム再生用のボイスプールは、内部的にボイスの数分だけローダ（ CriFsLoaderHn ）
 * を確保します。<br>
 * ストリーム再生用のボイスプールを作成する場合、ボイス数分のローダが確保できる設定で
 * Atomライブラリ（またはCRI File Systemライブラリ）を初期化する必要があります。<br>
 * <br>
 * 本関数は完了復帰型の関数です。<br>
 * ボイスプールの作成にかかる時間は、プラットフォームによって異なります。<br>
 * ゲームループ等の画面更新が必要なタイミングで本関数を実行するとミリ秒単位で
 * 処理がブロックされ、フレーム落ちが発生する恐れがあります。<br>
 * ボイスプールの作成／破棄は、シーンの切り替わり等、負荷変動を許容できる
 * タイミングで行うようお願いいたします。<br>
 * \sa CriAtomExAdxVoicePoolConfig, criAtomExVoicePool_CalculateWorkSizeForAdxVoicePool, criAtomExVoicePool_Free
 */
CriAtomExVoicePoolHn CRIAPI criAtomExVoicePool_AllocateAdxVoicePool(
	const CriAtomExAdxVoicePoolConfig *config, void *work, CriSint32 work_size);

/*JP
 * \brief サウンドジェネレータボイスプール作成用ワーク領域サイズの計算
 * \ingroup ATOMEXLIB_AT
 * \param[in]	config		サウンドジェネレータボイスプール作成用コンフィグ構造体
 * \return		CriSint32	ワーク領域サイズ
 * \retval		0以上		正常に処理が完了
 * \retval		-1			エラーが発生
 * \par 説明:
 * サウンドジェネレータボイスプールの作成に必要なワーク領域のサイズを計算します。<br>
 * ::criAtomEx_SetUserAllocator マクロによるアロケータ登録を行わずに
 * ::criAtomExVoicePool_AllocateSoundGeneratorVoicePool 関数でボイスプールを作成する際には、
 * ::criAtomExVoicePool_AllocateSoundGeneratorVoicePool 関数に本関数が返すサイズ分のメモリをワーク
 * 領域として渡す必要があります。<br>
 * <br>
 * ワーク領域サイズの計算に失敗すると、本関数は -1 を返します。<br>
 * ワーク領域サイズの計算に失敗した理由については、エラーコールバックのメッセージで確認可能です。<br>
 * \par 備考:
 * ボイスプールの作成に必要なワークメモリのサイズは、プレーヤ作成用コンフィグ
 * 構造体（ ::CriAtomExSoundGeneratorVoicePoolConfig ）の内容によって変化します。<br>
 * <br>
 * 引数にNULLを指定した場合、デフォルト設定
 * （ ::criAtomExVoicePool_SetDefaultConfigForSoundGeneratorVoicePool マクロ使用時
 * と同じパラメータ）でワーク領域サイズを計算します。
 * <br>
 * 引数 config の情報は、関数内でのみ参照されます。<br>
 * 関数を抜けた後は参照されませんので、関数実行後に config の領域を解放しても
 * 問題ありません。
 * \attention
 * ワーク領域のサイズはライブラリ初期化時（ ::criAtomEx_Initialize 関数実行時）
 * に指定したパラメータによって変化します。<br>
 * そのため、本関数を実行する前に、ライブラリを初期化しておく必要があります。<br>
 * \sa criAtomExVoicePool_AllocateSoundGeneratorVoicePool
 */
CriSint32 CRIAPI criAtomExVoicePool_CalculateWorkSizeForSoundGeneratorVoicePool(
	const CriAtomExSoundGeneratorVoicePoolConfig *config);

/*JP
 * \brief サウンドジェネレータボイスプールの作成
 * \ingroup ATOMEXLIB_AT
 * \param[in]	config		サウンドジェネレータボイスプール作成用コンフィグ構造体
 * \param[in]	work		ワーク領域
 * \param[in]	work_size	ワーク領域サイズ
 * \return		CriAtomExVoicePoolHn	ボイスプールハンドル
 * \par 説明：
 * サウンドジェネレータボイスプールを作成します。<br>
 * （サウンドジェネレータボイスは、波形生成を行うボイスです。）<br>
 * <br>
 * ボイスプールを作成する際には、ワーク領域としてメモリを渡す必要があります。<br>
 * 必要なメモリのサイズは、 ::criAtomExVoicePool_CalculateWorkSizeForSoundGeneratorVoicePool 
 * 関数で計算します。<br>
 * （::criAtomEx_SetUserAllocator マクロを使用してアロケータを登録済みの場合、
 * 本関数にワーク領域を指定する必要はありません。）<br>
 * <br>
 * 本関数を実行することで、サウンドジェネレータを使用した再生が可能なボイスがプールされます。<br>
 * AtomExプレーヤで再生を行うと、AtomExプレーヤは作成されたサウンドジェネレータボイスプールから
 * ボイスを取得し、再生を行います。<br>
 * <br>
 * ボイスプールの作成に成功すると、戻り値としてボイスプールハンドルが返されます。<br>
 * アプリケーション終了時には、作成したボイスプールを ::criAtomExVoicePool_Free 
 * 関数で破棄する必要があります。<br>
 * <br>
 * ボイスプールの作成に失敗すると、本関数はNULLを返します。<br>
 * ボイスプールの作成に失敗した理由については、エラーコールバックのメッセージで確認可能です。<br>
 * \par 備考:
 * ボイスプール作成時には、プール作成用コンフィグ構造体
 * （ ::CriAtomExSoundGeneratorVoicePoolConfig 構造体の num_voices ）
 * で指定した数分のボイスが、ライブラリ内で作成されます。<br>
 * 作成するボイスの数が多いほど、同時に再生可能な音声の数は増えますが、
 * 反面、使用するメモリは増加します。<br>
 * <br>
 * 尚、AtomExプレーヤがデータを再生した際に、
 * ボイスプール内のボイスが全て使用中であった場合、
 * ボイスプライオリティによる発音制御が行われます。<br>
 * （ボイスプライオリティの詳細は ::criAtomExPlayer_SetVoicePriority 
 * 関数の説明をご参照ください。）<br>
 * \attention
 * 本関数を実行する前に、ライブラリを初期化しておく必要があります。<br>
 * <br>
 * 本関数にワーク領域をセットした場合、セットした領域のメモリをボイスプール破棄時
 * までアプリケーション中で保持し続ける必要があります。<br>
 * （セット済みのワーク領域に値を書き込んだり、メモリ解放したりしてはいけません。）<br>
 * <br>
 * 引数 config の情報は、関数内でのみ参照されます。<br>
 * 関数を抜けた後は参照されませんので、関数実行後に config の領域を解放しても
 * 問題ありません。
 * <br>
 * 本関数は完了復帰型の関数です。<br>
 * ボイスプールの作成にかかる時間は、プラットフォームによって異なります。<br>
 * ゲームループ等の画面更新が必要なタイミングで本関数を実行するとミリ秒単位で
 * 処理がブロックされ、フレーム落ちが発生する恐れがあります。<br>
 * ボイスプールの作成／破棄は、シーンの切り替わり等、負荷変動を許容できる
 * タイミングで行うようお願いいたします。<br>
 * \sa CriAtomExSoundGeneratorVoicePoolConfig, criAtomExVoicePool_CalculateWorkSizeForSoundGeneratorVoicePool,
 * criAtomExVoicePool_Free
 */
CriAtomExVoicePoolHn CRIAPI criAtomExVoicePool_AllocateSoundGeneratorVoicePool(
	const CriAtomExSoundGeneratorVoicePoolConfig *config, void *work, CriSint32 work_size);

/*JP
 * \brief RawPCM Sint16ボイスプール作成用ワーク領域サイズの計算
 * \ingroup ATOMEXLIB_AT
 * \param[in]	config		RawPCM Sint16ボイスプール作成用コンフィグ構造体
 * \return		CriSint32	ワーク領域サイズ
 * \retval		0以上		正常に処理が完了
 * \retval		-1			エラーが発生
 * \par 説明:
 * RawPCM Sint16ボイスプールの作成に必要なワーク領域のサイズを計算します。<br>
 * ::criAtomEx_SetUserAllocator マクロによるアロケータ登録を行わずに
 * ::criAtomExVoicePool_AllocateRawPcmSint16VoicePool_AT 関数でボイスプールを作成する際には、
 * ::criAtomExVoicePool_AllocateRawPcmSint16VoicePool_AT 関数に本関数が返すサイズ分のメモリをワーク
 * 領域として渡す必要があります。<br>
 * <br>
 * ワーク領域サイズの計算に失敗すると、本関数は -1 を返します。<br>
 * ワーク領域サイズの計算に失敗した理由については、エラーコールバックのメッセージで確認可能です。<br>
 * \par 備考:
 * ボイスプールの作成に必要なワークメモリのサイズは、プレーヤ作成用コンフィグ
 * 構造体（ ::CriAtomExRawPcmSint16VoicePoolConfig_AT ）の内容によって変化します。<br>
 * <br>
 * 引数にNULLを指定した場合、デフォルト設定
 * （ ::criAtomExVoicePool_SetDefaultConfigForRawPcmSint16VoicePool_AT マクロ使用時
 * と同じパラメータ）でワーク領域サイズを計算します。
 * <br>
 * 引数 config の情報は、関数内でのみ参照されます。<br>
 * 関数を抜けた後は参照されませんので、関数実行後に config の領域を解放しても
 * 問題ありません。
 * \attention
 * ワーク領域のサイズはライブラリ初期化時（ ::criAtomEx_Initialize 関数実行時）
 * に指定したパラメータによって変化します。<br>
 * そのため、本関数を実行する前に、ライブラリを初期化しておく必要があります。<br>
 * \sa criAtomExVoicePool_AllocateRawPcmSint16VoicePool_AT
 */
CriSint32 CRIAPI criAtomExVoicePool_CalculateWorkSizeForRawPcmSint16VoicePool_AT(
	const CriAtomExRawPcmSint16VoicePoolConfig_AT *config);

/*JP
 * \brief RawPCM Sint16ボイスプールの作成
 * \ingroup ATOMEXLIB_AT
 * \param[in]	config		RawPCM Sint16ボイスプール作成用コンフィグ構造体
 * \param[in]	work		ワーク領域
 * \param[in]	work_size	ワーク領域サイズ
 * \return		CriAtomExVoicePoolHn	ボイスプールハンドル
 * \par 説明：
 * RawPCM Sint16ボイスプールを作成します。<br>
 * （RawPCM Sint16ボイスは、波形生成を行うボイスです。）<br>
 * <br>
 * ボイスプールを作成する際には、ワーク領域としてメモリを渡す必要があります。<br>
 * 必要なメモリのサイズは、 ::criAtomExVoicePool_CalculateWorkSizeForRawPcmSint16VoicePool_AT 
 * 関数で計算します。<br>
 * （::criAtomEx_SetUserAllocator マクロを使用してアロケータを登録済みの場合、
 * 本関数にワーク領域を指定する必要はありません。）<br>
 * <br>
 * 本関数を実行することで、RawPCM Sint16の再生が可能なボイスがプールされます。<br>
 * AtomExプレーヤで再生を行うと、AtomExプレーヤは作成されたRawPCM Sint16ボイスプールから
 * ボイスを取得し、再生を行います。<br>
 * <br>
 * ボイスプールの作成に成功すると、戻り値としてボイスプールハンドルが返されます。<br>
 * アプリケーション終了時には、作成したボイスプールを ::criAtomExVoicePool_Free 
 * 関数で破棄する必要があります。<br>
 * <br>
 * ボイスプールの作成に失敗すると、本関数はNULLを返します。<br>
 * ボイスプールの作成に失敗した理由については、エラーコールバックのメッセージで確認可能です。<br>
 * \par 備考:
 * ボイスプール作成時には、プール作成用コンフィグ構造体
 * （ ::CriAtomExRawPcmSint16VoicePoolConfig_AT 構造体の num_voices ）
 * で指定した数分のボイスが、ライブラリ内で作成されます。<br>
 * 作成するボイスの数が多いほど、同時に再生可能な音声の数は増えますが、
 * 反面、使用するメモリは増加します。<br>
 * <br>
 * 尚、AtomExプレーヤがデータを再生した際に、
 * ボイスプール内のボイスが全て使用中であった場合、
 * ボイスプライオリティによる発音制御が行われます。<br>
 * （ボイスプライオリティの詳細は ::criAtomExPlayer_SetVoicePriority 
 * 関数の説明をご参照ください。）<br>
 * \attention
 * 本関数を実行する前に、ライブラリを初期化しておく必要があります。<br>
 * <br>
 * 本関数にワーク領域をセットした場合、セットした領域のメモリをボイスプール破棄時
 * までアプリケーション中で保持し続ける必要があります。<br>
 * （セット済みのワーク領域に値を書き込んだり、メモリ解放したりしてはいけません。）<br>
 * <br>
 * 引数 config の情報は、関数内でのみ参照されます。<br>
 * 関数を抜けた後は参照されませんので、関数実行後に config の領域を解放しても
 * 問題ありません。
 * <br>
 * 本関数は完了復帰型の関数です。<br>
 * ボイスプールの作成にかかる時間は、プラットフォームによって異なります。<br>
 * ゲームループ等の画面更新が必要なタイミングで本関数を実行するとミリ秒単位で
 * 処理がブロックされ、フレーム落ちが発生する恐れがあります。<br>
 * ボイスプールの作成／破棄は、シーンの切り替わり等、負荷変動を許容できる
 * タイミングで行うようお願いいたします。<br>
 * \sa CriAtomExRawPcmSint16VoicePoolConfig_AT, criAtomExVoicePool_CalculateWorkSizeForRawPcmSint16VoicePool_AT,
 * criAtomExVoicePool_Free
 */
CriAtomExVoicePoolHn CRIAPI criAtomExVoicePool_AllocateRawPcmSint16VoicePool_AT(
	const CriAtomExRawPcmSint16VoicePoolConfig_AT *config, void *work, CriSint32 work_size);

/*JP
 * \brief ボイスプールの破棄
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[in]	pool		ボイスプールハンドル
 * \par 説明:
 * 作成済みのボイスプールを破棄します。<br>
 * ::criAtomEx_SetUserAllocator マクロを使用してアロケータを登録済みの場合、
 * ボイスプール作成時に確保されたメモリ領域が解放されます。<br>
 * （ボイスプール作成時にワーク領域を渡した場合、本関数実行後であれば
 * ワーク領域を解放可能です。）<br>
 * \attention
 * 本関数は完了復帰型の関数です。<br>
 * 音声再生中にボイスプールを破棄した場合、本関数内で再生停止を待ってから
 * リソースの解放が行われます。<br>
 * （ファイルから再生している場合は、さらに読み込み完了待ちが行われます。）<br>
 * そのため、本関数内で処理が長時間（数フレーム）ブロックされる可能性があります。<br>
 * ボイスプールの作成／破棄は、シーンの切り替わり等、負荷変動を許容できる
 * タイミングで行うようお願いいたします。<br>
 * \sa criAtomExVoicePool_AllocateStandardVoicePool
 */
void CRIAPI criAtomExVoicePool_Free(CriAtomExVoicePoolHn pool);

/*==========================================================================
 *      CRI AtomEx Player API
 *=========================================================================*/
/*JP
 * \brief AtomExPlayer用ワーク領域サイズの計算
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	config		プレーヤ作成用コンフィグ構造体
 * \return		CriSint32	ワーク領域サイズ
 * \retval		0以上		正常に処理が完了
 * \retval		-1			エラーが発生
 * \par 説明:
 * AtomExプレーヤを作成するために必要な、ワーク領域のサイズを取得します。<br>
 * アロケータを登録せずにAtomExプレーヤを作成する場合、
 * あらかじめ本関数で計算したワーク領域サイズ分のメモリを
 * ワーク領域として ::criAtomExPlayer_Create 関数にセットする必要があります。<br>
 * <br>
 * プレーヤの作成に必要なワークメモリのサイズは、プレーヤ作成用コンフィグ
 * 構造体（ ::CriAtomExPlayerConfig ）の内容によって変化します。<br>
 * <br>
 * 引数にNULLを指定した場合、デフォルト設定
 * （ ::criAtomExPlayer_SetDefaultConfig 適用時と同じパラメータ）で
 * ワーク領域サイズを計算します。
 * <br>
 * ワーク領域サイズ計算時に失敗した場合、戻り値は -1 になります。<br>
 * ワーク領域サイズの計算に失敗した理由については、エラーコールバックの
 * メッセージで確認可能です。<br>
 * \par 備考:
 * 引数 config の情報は、関数内でのみ参照されます。<br>
 * 関数を抜けた後は参照されませんので、関数実行後に config の領域を解放しても
 * 問題ありません。
 * \attention
 * 本関数を実行する前に、ライブラリを初期化しておく必要があります。<br>
 * \sa CriAtomExPlayerConfig, criAtomExPlayer_Create
 */
CriSint32 CRIAPI criAtomExPlayer_CalculateWorkSize(
	const CriAtomExPlayerConfig *config);

/*JP
 * \brief AtomExPlayerの作成
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	config		AtomExプレーヤ作成用コンフィグ構造体
 * \param[in]	work		ワーク領域
 * \param[in]	work_size	ワーク領域サイズ
 * \return		CriAtomExPlayerHn	AtomExプレーヤハンドル
 * \par 説明:
 * AtomExプレーヤを作成します。<br>
 * <br>
 * プレーヤを作成する際には、ライブラリが内部で利用するためのメモリ領域（ワーク領域）
 * を確保する必要があります。<br>
 * ワーク領域を確保する方法には、以下の2通りの方法があります。<br>
 * <b>(a) User Allocator方式</b>：メモリの確保／解放に、ユーザが用意した関数を使用する方法。<br>
 * <b>(b) Fixed Memory方式</b>：必要なメモリ領域を直接ライブラリに渡す方法。<br>
 * <br>
 * User Allocator方式を用いる場合、ユーザがワーク領域を用意する必要はありません。<br>
 * workにNULL、work_sizeに0を指定するだけで、必要なメモリを登録済みのメモリ確保関数から確保します。<br>
 * AtomExプレーヤ作成時に確保されたメモリは、AtomExプレーヤ破棄時（ ::criAtomExPlayer_Destroy 
 * 関数実行時）に解放されます。<br>
 * <br>
 * Fixed Memory方式を用いる場合、ワーク領域として別途確保済みのメモリ領域を本関数に
 * 設定する必要があります。<br>
 * ワーク領域のサイズは ::criAtomExPlayer_CalculateWorkSize 関数で取得可能です。<br>
 * AtomExプレーヤ作成前に ::criAtomExPlayer_CalculateWorkSize 関数で取得した
 * サイズ分のメモリを予め確保しておき、本関数に設定してください。<br>
 * 尚、Fixed Memory方式を用いた場合、ワーク領域はAtomExプレーヤの破棄
 * （ ::criAtomExPlayer_Destroy 関数）を行なうまでの間、ライブラリ内で利用され続けます。<br>
 * AtomExプレーヤの破棄を行なう前に、ワーク領域のメモリを解放しないでください。<br>
 * \par 例:
 * 【User Allocator方式によるAtomExプレーヤの作成】<br>
 * User Allocator方式を用いる場合、AtomExプレーヤの作成／破棄の手順は以下のようになります。<br>
 * 	-# AtomExプレーヤ作成前に、 ::criAtomEx_SetUserAllocator 関数を用いてメモリ確保／解放関数を登録する。<br>
 * 	-# AtomExプレーヤ作成用コンフィグ構造体にパラメータをセットする。<br>
 * 	-# ::criAtomExPlayer_Create 関数でAtomExプレーヤを作成する。<br>
 * （workにはNULL、work_sizeには0を指定する。）<br>
 * 	-# ハンドルが不要になったら ::criAtomExPlayer_Destroy 関数でAtomExプレーヤを破棄する。<br>
 * 	.
 * <br>具体的なコードは以下のとおりです。<br>
 * \code
 * ## 独自のメモリ確保関数
 * void *user_malloc(void *obj, CriUint32 size)
 * {
 * 	void *mem;
 * 	
 * 	## メモリの確保
 * 	mem = malloc(size);
 * 	
 * 	return (mem);
 * }
 * 
 * ## 独自のメモリ解放関数を用意
 * void user_free(void *obj, void *mem)
 * {
 * 	## メモリの解放
 * 	free(mem);
 * 	
 * 	return;
 * }
 * 
 * main()
 * {
 * 	CriAtomExPlayerConfig config;	## AtomExプレーヤ作成用コンフィグ構造体
 * 	CriAtomExPlayerHn player;		## AtomExプレーヤハンドル
 * 		:
 * 	## 独自のメモリアロケータを登録
 * 	criAtomEx_SetUserAllocator(user_malloc, user_free, NULL);
 * 	
 * 	## AtomExプレーヤ作成用コンフィグ構造体を設定
 * 	criAtomExPlayer_SetDefaultConfig(&config);
 * 	
 * 	## AtomExプレーヤの作成
 * 	## ワーク領域にはNULLと0を指定する。
 * 	## →必要なメモリは、登録したメモリ確保関数を使って確保される。
 * 	player = criAtomExPlayer_Create(&config, NULL, 0);
 * 		:
 * 	## 音声再生処理
 * 		:
 * 	## AtomExプレーヤが不要になった時点で破棄
 * 	## →AtomExプレーヤ作成時にライブラリ内で確保されたメモリが解放される。
 * 	criAtomExPlayer_Destroy(player);
 * 		:
 * }
 *	※上記仮想コード内の"##"は行末までのコメントアウト開始を示しています。
 * \endcode
 * ※ライブラリ初期化時にメモリ確保／解放関数を登録済みの場合、AtomExプレーヤ作成時
 * に再度関数を登録する必要はありません。<br>
 * <br>
 * 【Fixed Memory方式によるAtomExプレーヤの作成】<br>
 * Fixed Memory方式を用いる場合、AtomExプレーヤの作成／破棄の手順は以下のようになります。<br>
 * 	-# AtomExプレーヤ作成用コンフィグ構造体にパラメータをセットする。<br>
 * 	-# AtomExプレーヤの作成に必要なワーク領域のサイズを、
 * ::criAtomExPlayer_CalculateWorkSize 関数を使って計算する。<br>
 * 	-# ワーク領域サイズ分のメモリを確保する。<br>
 * 	-# ::criAtomExPlayer_Create 関数でAtomExプレーヤを作成する。<br>
 * （workには確保したメモリのアドレスを、work_sizeにはワーク領域のサイズを指定する。）<br>
 * 	-# ハンドルが不要になったら ::criAtomExPlayer_Destroy 関数でAtomExプレーヤを破棄する。<br>
 * 	-# ワーク領域のメモリを解放する。<br>
 * 	.
 * <br>具体的なコードは以下のとおりです。<br>
 * \code
 * main()
 * {
 * 	CriAtomExPlayerConfig config;	## AtomExプレーヤ作成用コンフィグ構造体
 * 	CriAtomExPlayerHn player;		## AtomExプレーヤハンドル
 * 	void *work;						## ワーク領域アドレス
 * 	CriSint32 work_size;			## ワーク領域サイズ
 * 		:
 * 	## AtomExプレーヤ作成用コンフィグ構造体を設定
 * 	criAtomExPlayer_SetDefaultConfig(&config);
 * 	
 * 	## AtomExプレーヤの作成に必要なワーク領域のサイズを計算
 * 	work_size = criAtomExPlayer_CalculateWorkSize(&config);
 * 	
 * 	## ワーク領域用にメモリを確保
 * 	work = malloc((size_t)work_size);
 * 	
 * 	## AtomExプレーヤの作成
 * 	## ワーク領域にはNULLと0を指定する。
 * 	## →確保済みのワーク領域を指定する。
 * 	player = criAtomExPlayer_Create(&config, work, work_size);
 * 		:
 * 	## 音声再生処理
 * 	## →この間、確保したメモリは保持し続ける。
 * 		:
 * 	## AtomExプレーヤが不要になった時点で破棄
 * 	criAtomExPlayer_Destroy(player);
 * 	
 * 	## 必要なくなったワーク領域を解放する
 * 	free(work);
 * 		:
 * }
 *	※上記仮想コード内の"##"は行末までのコメントアウト開始を示しています。
 * \endcode
 * ::criAtomExPlayer_Create 関数を実行すると、AtomExプレーヤが作成され、
 * プレーヤを制御するためのハンドル（ ::CriAtomExPlayerHn ）が返されます。<br>
 * データのセット、再生の開始、ステータスの取得等、AtomExプレーヤに対して
 * 行う操作は、全てハンドルに対して行います。<br>
 * <br>
 * プレーヤの作成に失敗した場合、戻り値として NULL が返されます。<br>
 * プレーヤの作成に失敗した理由については、エラーコールバックのメッセージで確認可能です。<br>
 * <br>
 * 作成されたAtomExプレーヤハンドルを使用して音声データを再生する手順は以下のとおりです。<br>
 * -# ::criAtomExPlayer_SetData 関数を使用して、AtomExプレーヤに再生するデータをセットする。<br>
 * （ファイル再生時は、 ::criAtomExPlayer_SetFile 関数または ::criAtomExPlayer_SetContentId 
 * 関数を使用する。）<br>
 * -# ::criAtomExPlayer_Start 関数で再生を開始する。<br>
 * \par 備考:
 * 引数 config の情報は、関数内でのみ参照されます。<br>
 * 関数を抜けた後は参照されませんので、関数実行後に config の領域を解放しても
 * 問題ありません。
 * \attention
 * 本関数を実行する前に、ライブラリを初期化しておく必要があります。<br>
 * <br>
 * 本関数は完了復帰型の関数です。<br>
 * AtomExプレーヤの作成にかかる時間は、プラットフォームによって異なります。<br>
 * ゲームループ等の画面更新が必要なタイミングで本関数を実行するとミリ秒単位で
 * 処理がブロックされ、フレーム落ちが発生する恐れがあります。<br>
 * AtomExプレーヤの作成／破棄は、シーンの切り替わり等、負荷変動を許容できる
 * タイミングで行うようお願いいたします。<br>
 * \sa CriAtomExPlayerConfig, criAtomExPlayer_CalculateWorkSize,
 * CriAtomExPlayerHn, criAtomExPlayer_Destroy,
 * criAtomExPlayer_SetData, criAtomExPlayer_SetFile, criAtomExPlayer_SetContentId,
 * criAtomExPlayer_Start
 */
CriAtomExPlayerHn CRIAPI criAtomExPlayer_Create(
	const CriAtomExPlayerConfig *config, void *work, CriSint32 work_size);

/*JP
 * \brief AtomExプレーヤの破棄
 * \ingroup ATOMExLIB_PLAYER
 * \param[in]	player		AtomExプレーヤハンドル
 * \par 説明:
 * AtomExプレーヤを破棄します。<br>
 * 本関数を実行した時点で、AtomExプレーヤ作成時に確保されたリソースが全て解放されます。<br>
 * また、引数に指定したAtomExプレーヤハンドルも無効になります。<br>
 * \attention
 * 本関数は完了復帰型の関数です。<br>
 * 音声再生中のAtomExプレーヤを破棄しようとした場合、本関数内で再生停止を
 * 待ってからリソースの解放が行われます。<br>
 * （ファイルから再生している場合は、さらに読み込み完了待ちが行われます。）<br>
 * そのため、本関数内で処理が長時間（数フレーム）ブロックされる可能性があります。<br>
 * AtomExプレーヤの作成／破棄は、シーンの切り替わり等、負荷変動を許容できる
 * タイミングで行うようお願いいたします。<br>
 * \sa criAtomExPlayer_Create, CriAtomExPlayerHn
 */
void CRIAPI criAtomExPlayer_Destroy(CriAtomExPlayerHn player);

/*JP
 * \brief 音声データのセット（キューID指定）
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomExプレーヤハンドル
 * \param[in]	acb_hn			ACBハンドル
 * \param[in]	id				キューID
 * \par 説明:
 * キューIDを、AtomExプレーヤに関連付けます。<br>
 * 本関数でキューIDを指定後、 ::criAtomExPlayer_Start 関数で再生を
 * 開始すると、指定されたキューが再生されます。
 * \par 例:
 * \code
 * main()
 * {
 * 		:
 * 	## 音声データをセット
 * 	criAtomExPlayer_SetCueId(player, acb_hn, 100);
 * 	
 * 	## セットされた音声データを再生
 * 	criAtomExPlayer_Start(player);
 * 		:
 * }
 *	※上記仮想コード内の"##"は行末までのコメントアウト開始を示しています。
 * \endcode
 * 尚、一旦セットしたデータの情報は、他のデータがセットされるまでAtomExプレーヤ内に保持
 * されます。<br>
 * そのため、同じデータを何度も再生する場合には、再生毎にデータをセットしなおす必要
 * はありません。
 * \par 備考:
 * 第2引数（ ach_hn ）に NULL を指定した場合、全てのACBデータを対象に、指定したキューIDに
 * 合致するデータがないか、ライブラリ内で検索が行われます。<br>
 * （指定したキューIDを持つACBデータが見つかった時点で、
 * 当該ACBデータのキューがプレーヤにセットされます。）<br>
 * この際、検索の順序は、ACBデータのロード順とは逆順で行われます。<br>
 * （後からロードされたデータから優先的に検索が行われます。）<br>
 * <br>
 * ::criAtomExPlayer_SetCueId 関数でキューをセットした場合、以下の関数で設定された
 * パラメータは無視されます。<br>
 * 	- ::criAtomExPlayer_SetFormat
 * 	- ::criAtomExPlayer_SetNumChannels
 * 	- ::criAtomExPlayer_SetSamplingRate
 * 	.
 * （音声フォーマットやチャンネル数、サンプリングレート等の情報は、
 * ACB ファイルの情報を元に自動的にセットされます。）<br>
 * \sa criAtomExPlayer_Start
 */
void CRIAPI criAtomExPlayer_SetCueId(
	CriAtomExPlayerHn player, CriAtomExAcbHn acb_hn, CriAtomExCueId id);

/*JP
 * \brief 再生の開始
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomExプレーヤハンドル
 * \return		CriAtomExPlaybackId		再生ID
 * \par 説明:
 * 音声データの再生処理を開始します。<br>
 * 本関数を実行する前に、事前に ::criAtomExPlayer_SetData 関数等を使用し、再生する
 * 音声データをAtomExプレーヤにセットしておく必要があります。<br>
 * 例えば、オンメモリの音声データを再生する場合には、以下のように事前に
 * ::criAtomExPlayer_SetData 関数を使って音声データをセットした後、本関数を実行する
 * 必要があります。<br>
 * \code
 * main()
 * {
 * 		:
 * 	## 音声データをセット
 * 	criAtomExPlayer_SetData(player, buffer, buffer_size);
 * 	
 * 	## 再生する音声データのフォーマットを指定
 * 	criAtomExPlayer_SetFormat(player, CRIATOMEX_FORMAT_HCA_MX);
 * 	criAtomExPlayer_SetNumChannels(player, 1);
 * 	criAtomExPlayer_SetSamplingRate(player, 24000);
 * 	
 * 	## セットされた音声データを再生
 * 	criAtomExPlayer_Start(player);
 * 		:
 * }
 *	※上記仮想コード内の"##"は行末までのコメントアウト開始を示しています。
 * \endcode
 * 本関数実行後、再生の進み具合（発音が開始されたか、再生が完了したか等）がどうなって
 * いるかは、ステータスを取得することで確認が可能です。<br>
 * ステータスの取得には、 ::criAtomExPlayer_GetStatus 関数を使用します。<br>
 * ::criAtomExPlayer_GetStatus 関数は以下の5通りのステータスを返します。<br>
 * 	-# CRIATOMEXPLAYER_STATUS_STOP
 * 	-# CRIATOMEXPLAYER_STATUS_PREP
 * 	-# CRIATOMEXPLAYER_STATUS_PLAYING
 * 	-# CRIATOMEXPLAYER_STATUS_PLAYEND
 * 	-# CRIATOMEXPLAYER_STATUS_ERROR
 * 	.
 * AtomExプレーヤを作成した時点では、AtomExプレーヤのステータスは停止状態
 * （ CRIATOMEXPLAYER_STATUS_STOP ）です。<br>
 * 再生する音声データをセット後、本関数を実行することで、AtomExプレーヤのステータスが
 * 準備状態（ CRIATOMEXPLAYER_STATUS_PREP ）に変更されます。<br>
 * （CRIATOMEXPLAYER_STATUS_PREP は、データ供給やデコードの開始を待っている状態です。）<br>
 * 再生の開始に充分なデータが供給された時点で、AtomExプレーヤはステータスを
 * 再生状態（ CRIATOMEXPLAYER_STATUS_PLAYING ）に変更し、音声の出力を開始します。<br>
 * セットされたデータを全て再生し終えると、AtomExプレーヤはステータスを再生終了状態
 * （ CRIATOMEXPLAYER_STATUS_PLAYEND ）に変更します。<br>
 * 尚、再生中にエラーが発生した場合には、AtomExプレーヤはステータスをエラー状態
 * （ CRIATOMEXPLAYER_STATUS_ERROR ）に変更します。<br>
 * <br>
 * AtomExプレーヤのステータスをチェックし、ステータスに応じて処理を切り替えることで、
 * 音声の再生状態に連動したプログラムを作成することが可能です。<br>
 * 例えば、音声の再生完了を待って処理を進めたい場合には、以下のようなコードになります。
 * \code
 * main()
 * {
 * 		:
 * 	## 音声データをセット
 * 	criAtomExPlayer_SetData(player, buffer, buffer_size);
 * 	
 * 	## 再生する音声データのフォーマットを指定
 * 	criAtomExPlayer_SetFormat(player, CRIATOMEX_FORMAT_ADX);
 * 	criAtomExPlayer_SetNumChannels(player, 1);
 * 	criAtomExPlayer_SetSamplingRate(player, 22050);
 * 	
 * 	## セットされた音声データを再生
 * 	criAtomExPlayer_Start(player);
 * 	
 * 	## 再生完了待ち
 * 	for (;;) {
 * 		## ステータスの取得
 * 		status = criAtomExPlayer_GetStatus(player);
 * 		
 * 		## ステータスのチェック
 * 		if (status == CRIATOMEXPLAYER_STATUS_PLAYEND) {
 * 			## 再生終了時はループを抜ける
 * 			break;
 * 		}
 * 		
 * 		## サーバ処理の実行
 * 		criAtomEx_ExecuteMain();
 * 		
 * 		## 画面表示の更新等
 * 			:
 * 	}
 * 		:
 * }
 *	※上記仮想コード内の"##"は行末までのコメントアウト開始を示しています。
 * \endcode
 * \par 備考:
 * 関数実行時に発音リソースが確保できない場合（全てのボイスが使用中で、なおかつ
 * 他のボイスを奪い取れない場合等）、本関数は CRIATOMEX_INVALID_PLAYBACK_ID を返します。<br>
 * しかし、戻り値を元にエラーチェックを行わなくても、ほとんどのケースで問題は発生しません。<br>
 * 再生ID（ ::CriAtomExPlaybackId ）を使用する API に対し、 CRIATOMEX_INVALID_PLAYBACK_ID 
 * をセットしたとしても、Atomライブラリは特に何も処理しません。<br>
 * そのため、デバッグ目的で発音が行われたかどうかをチェックしたい場合を除き、
 * 本関数の結果に応じてアプリケーション側で処理を切り分ける必要はありません。<br>
 * （ CRIATOMEX_INVALID_PLAYBACK_ID が返された際に、有効な再生IDが返された場合と
 * 同様の処理を行っても、エラーコールバック等は発生しません。）<br>
 * <br>
 * プライオリティの比較によって指定したキューの再生が行われなかった場合、
 * 戻り値としてCRIATOMEX_INVALID_PLAYBACK_IDが返ります。
 * \sa criAtomExPlayer_SetData, criAtomExPlayer_SetFile, criAtomExPlayer_GetStatus,
 * criAtomExPlayer_Pause, criAtomEx_ExecuteMain
 */
CriAtomExPlaybackId CRIAPI criAtomExPlayer_Start(CriAtomExPlayerHn player);

/*JP
 * \brief 再生の停止
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomExプレーヤハンドル
 * \par 説明:
 * 再生の停止要求を発行します。<br>
 * 音声再生中のAtomExプレーヤに対して本関数を実行すると、
 * AtomExプレーヤは再生を停止（ファイルの読み込みや、発音を停止）し、
 * ステータスを停止状態（ CRIATOMEXPLAYER_STATUS_STOP ）に遷移します。<br>
 * 再生している特定のキューのみ停止したい場合は、 ::criAtomExPlayer_StopSpecifiedCueId 関数を使用してください。
 * \par 備考:
 * 既に停止しているAtomExプレーヤ（ステータスが CRIATOMEXPLAYER_STATUS_PLAYEND や
 * CRIATOMEXPLAYER_STATUS_ERROR のAtomExプレーヤ） に対して本関数を実行すると、
 * AtomExプレーヤのステータスを CRIATOMEXPLAYER_STATUS_STOP に変更します。
 * \attention
 * 本関数は完了復帰型の関数ではありません。<br>
 * そのため、関数内で処理が長時間ブロックすることはありませんが、
 * 関数を抜けた時点では再生が停止していない可能性がある点にご注意ください。<br>
 * （停止状態になるまでに、時間がかかる場合があります。）<br>
 * 停止を保証する必要がある場合には、本関数呼び出し後、
 * AtomExプレーヤのステータスが停止状態（CRIATOMEXPLAYER_STATUS_STOP）
 * になることを確認してください。
 * \sa criAtomExPlayer_Start, criAtomExPlayer_GetStatus
 */
void CRIAPI criAtomExPlayer_Stop(CriAtomExPlayerHn player);

/*JP
 * \brief 再生の停止（キューID指定）
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomExプレーヤハンドル
 * \param[in]	id			キューID
 * \par 説明:
 * 指定したキューIDの再生の停止要求を発行します。<br>
 * 指定したキューIDを再生中のAtomExプレーヤに対して本関数を実行すると、
 * AtomExプレーヤは指定したキューIDの再生を停止（ファイルの読み込みや、発音を停止）します。
 * 指定したキューID以外のキューが再生されている場合、ステータスは再生状態（ CRIATOMEXPLAYER_STATUS_PLAYING ）を維持し、
 * 指定したキューIDのみが再生されている場合は停止状態（ CRIATOMEXPLAYER_STATUS_STOP ）に遷移します。<br>
 * 再生している全てのキューを停止したい場合は、 ::criAtomExPlayer_Stop 関数を使用してください。
 * \par 備考:
 * 既に停止しているAtomExプレーヤ（ステータスが CRIATOMEXPLAYER_STATUS_PLAYEND や
 * CRIATOMEXPLAYER_STATUS_ERROR のAtomExプレーヤ） に対して本関数を実行すると、
 * AtomExプレーヤのステータスを CRIATOMEXPLAYER_STATUS_STOP に変更します。
 * \attention
 * 本関数は完了復帰型の関数ではありません。<br>
 * そのため、関数内で処理が長時間ブロックすることはありませんが、
 * 関数を抜けた時点では再生が停止していない可能性がある点にご注意ください。<br>
 * （停止状態になるまでに、時間がかかる場合があります。）<br>
 * 停止を保証する必要がある場合には、本関数呼び出し後、
 * AtomExプレーヤのステータスが停止状態（CRIATOMEXPLAYER_STATUS_STOP）
 * になることを確認してください。
 * \sa criAtomExPlayer_Start, criAtomExPlayer_GetStatus
 */
void CRIAPI criAtomExPlayer_StopSpecifiedCueId(CriAtomExPlayerHn player, CriAtomExCueId id);

/*JP
 * \brief ステータスの取得
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomExプレーヤハンドル
 * \return		CriAtomExPlayerStatus	ステータス
 * \par 説明:
 * AtomExプレーヤのステータスを取得します。<br>
 * ステータスはAtomExプレーヤの再生状態を示す値で、以下の5通りの値が存在します。<br>
 * -# CRIATOMEXPLAYER_STATUS_STOP
 * -# CRIATOMEXPLAYER_STATUS_PREP
 * -# CRIATOMEXPLAYER_STATUS_PLAYING
 * -# CRIATOMEXPLAYER_STATUS_PLAYEND
 * -# CRIATOMEXPLAYER_STATUS_ERROR
 * .
 * AtomExプレーヤを作成した時点では、AtomExプレーヤのステータスは停止状態
 * （ CRIATOMEXPLAYER_STATUS_STOP ）です。<br>
 * 再生する音声データをセット後、::criAtomExPlayer_Start 関数を実行することで、
 * AtomExプレーヤのステータスが準備状態（ CRIATOMEXPLAYER_STATUS_PREP ）に変更されます。<br>
 * （CRIATOMEXPLAYER_STATUS_PREP は、データ供給やデコードの開始を待っている状態です。）<br>
 * 再生の開始に充分なデータが供給された時点で、AtomExプレーヤはステータスを
 * 再生状態（ CRIATOMEXPLAYER_STATUS_PLAYING ）に変更し、音声の出力を開始します。<br>
 * セットされたデータを全て再生し終えると、AtomExプレーヤはステータスを再生終了状態
 * （ CRIATOMEXPLAYER_STATUS_PLAYEND ）に変更します。<br>
 * 尚、再生中にエラーが発生した場合には、AtomExプレーヤはステータスをエラー状態
 * （ CRIATOMEXPLAYER_STATUS_ERROR ）に変更します。<br>
 * <br>
 * AtomExプレーヤのステータスをチェックし、ステータスに応じて処理を切り替えることで、
 * 音声の再生状態に連動したプログラムを作成することが可能です。<br>
 * 例えば、音声の再生完了を待って処理を進めたい場合には、以下のようなコードになります。
 * \code
 * main()
 * {
 * 		:
 * 	## 音声データをセット
 * 	criAtomExPlayer_SetData(player, buffer, buffer_size);
 * 	
 * 	## 再生する音声データのフォーマットを指定
 * 	criAtomExPlayer_SetFormat(player, CRIATOMEX_FORMAT_ADX);
 * 	criAtomExPlayer_SetNumChannels(player, 1);
 * 	criAtomExPlayer_SetSamplingRate(player, 24000);
 * 	
 * 	## セットされた音声データを再生
 * 	criAtomExPlayer_Start(player);
 * 	
 * 	## 再生完了待ち
 * 	for (;;) {
 * 		## ステータスの取得
 * 		status = criAtomExPlayer_GetStatus(player);
 * 		
 * 		## ステータスのチェック
 * 		if (status == CRIATOMEXPLAYER_STATUS_PLAYEND) {
 * 			## 再生終了時はループを抜ける
 * 			break;
 * 		}
 * 		
 * 		## サーバ処理の実行
 * 		criAtomEx_ExecuteMain();
 * 		
 * 		## 画面表示の更新等
 * 			:
 * 	}
 * 		:
 * }
 *	※上記仮想コード内の"##"は行末までのコメントアウト開始を示しています。
 * \endcode
 * \sa criAtomExPlayer_Start
 */
CriAtomExPlayerStatus CRIAPI criAtomExPlayer_GetStatus(CriAtomExPlayerHn player);

/*JP
 * \brief 再生パラメータの更新（再生中の音全て）
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomExプレーヤハンドル
 * \par 説明:
 * AtomExプレーヤに設定されている再生パラメータ（AISACコントロール値を含む）を使用して、
 * このAtomExプレーヤで再生中の音全ての再生パラメータを更新します。<br>
 * \par 例:
 * \code
 * CriFloat32 volume;
 * ## Start playback
 * criAtomExPlayer_Start(player);
 *                :
 * criAtomExPlayer_Start(player);
 *                :
 * ## Change Volume
 * volume = 0.3f;
 * criAtomExPlayer_SetVolume(player, volume);
 * criAtomExPlayer_UpdateAll(player);
 *	※上記仮想コード内の"##"は行末までのコメントアウト開始を示しています。
 * \endcode
 * \sa criAtomExPlayer_Update
 */
void CRIAPI criAtomExPlayer_UpdateAll(CriAtomExPlayerHn player);

/*JP
 * \brief ボリュームの設定
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomExプレーヤハンドル
 * \param[in]	volume		ボリューム値
 * \par 説明:
 * 出力音声のボリュームを指定します。<br>
 * 本関数でボリュームを設定後、::criAtomExPlayer_Start 関数で再生を開始すると、
 * 設定されたボリュームで音声が再生されます。<br>
 * またボリューム設定後に ::criAtomExPlayer_Update 関数や ::criAtomExPlayer_UpdateAll 
 * 関数を呼び出すことで、すでに再生された音声のボリュームを更新することも可能です。<br>
 * <br>
 * ボリューム値は音声データの振幅に対する倍率です（単位はデシベルではありません）。<br>
 * 例えば、1.0fを指定した場合、原音はそのままのボリュームで出力されます。<br>
 * 0.5fを指定した場合、原音波形の振幅を半分にしたデータと同じ音量（-6dB）で
 * 音声が出力されます。<br>
 * 0.0fを指定した場合、音声はミュートされます（無音になります）。<br>
 * ボリュームのデフォルト値は1.0fです。<br>
 * \par 例:
 * \code
 * 	：
 * ## ボリュームの設定
 * criAtomExPlayer_SetVolume(player, 0.5f);
 * 
 * ## 再生の開始
 * ## 備考）ボリュームはプレーヤに設定された値（＝0.5f）で再生される。
 * id = criAtomExPlayer_Start(player);
 * 	：
 * ## ボリュームの変更
 * ## 注意）この時点では再生中の音声のボリュームは変更されない。
 * criAtomExPlayer_SetVolume(player, 0.3f);
 * 
 * ## プレーヤに設定されたボリュームを再生中の音声にも反映
 * criAtomExPlayer_Update(player, id);
 * 	：
 *	※上記仮想コード内の"##"は行末までのコメントアウト開始を示しています。
 * \endcode
 * \par 備考:
 * ボリューム値には0.0f以上の値が設定可能です。<br>
 * （Atomライブラリ Ver.1.21.07より、
 * ボリューム値に1.0fを超える値を指定できるようになりました。）<br>
 * 1.0fを超える値をセットした場合、<b>プラットフォームによっては</b>、
 * 波形データを元素材よりも大きな音量で再生可能です。<br>
 * ボリューム値に0.0f未満の値を指定した場合、値は0.0fにクリップされます。<br>
 * （ボリューム値に負の値を設定した場合でも、
 * 波形データの位相が反転されることはありません。）<br>
 * <br>
 * キュー再生時、データ側にボリュームが設定されている場合に本関数を呼び出すと、
 * データ側に設定されている値と本関数による設定値とを<b>乗算</b>した値が適用されます。<br>
 * 例えば、データ側のボリュームが0.8f、AtomExプレーヤのボリュームが0.5fの場合、
 * 実際に適用されるボリュームは0.4fになります。<br>
 * <br>
 * デシベルで設定したい場合、以下の計算式で変換してから設定してください。<br>
 * \code
 * volume = powf(10.0f, db_vol / 20.0f);
 * \endcode
 * ※db_volがデシベル値、volumeがボリューム値です。
 * \attention
 * 1.0fを超えるボリュームを指定する場合、以下の点に注意する必要があります。<br>
 *  - プラットフォームごとに挙動が異なる可能性がある。
 *  - 音割れが発生する可能性がある。
 *  .
 * <br>
 * 本関数に1.0fを超えるボリューム値を設定した場合でも、
 * 音声が元の波形データよりも大きな音量で再生されるかどうかは、
 * プラットフォームや音声圧縮コーデックの種別によって異なります。<br>
 * そのため、マルチプラットフォームタイトルでボリュームを調整する場合には、
 * 1.0fを超えるボリューム値を使用しないことをおすすめします。<br>
 * （1.0fを超えるボリューム値を指定した場合、同じ波形データを再生した場合でも、
 * 機種ごとに異なる音量で出力される可能性があります。）<br>
 * <br>
 * また、音量を上げることが可能な機種であっても、
 * ハードウェアで出力可能な音量には上限があるため、
 * 音割れによるノイズが発生する可能性があります。<br>
 * \sa criAtomExPlayer_Start, criAtomExPlayer_Update, criAtomExPlayer_UpdateAll
 */
void CRIAPI criAtomExPlayer_SetVolume(
	CriAtomExPlayerHn player, CriFloat32 volume);

/*JP
 * \brief AISACコントロール値の設定（コントロールID指定）
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomExプレーヤハンドル
 * \param[in]	control_id		コントロールID
 * \param[in]	control_value	コントロール値（0.0f〜1.0f）
 * \par 説明:
 * コントロールID指定でAISACのコントロール値を指定します。<br>
 * 本関数でAISACコントロール値を設定後、::criAtomExPlayer_Start 関数により再生開始すると、
 * 設定されたAISACコントロール値で再生されます。<br>
 * また設定後、::criAtomExPlayer_Update 関数、::criAtomExPlayer_UpdateAll 関数を呼び出すことにより、
 * すでに再生された音声のAISACコントロール値を更新することができます。<br>
 * 設定したコントロール値を削除するには、::criAtomExPlayer_ClearAisacControls 関数を使用してください。<br>
 * <br>
 * AISACコントロール値には、0.0f〜1.0fの範囲で実数値を指定します。<br>
 * \par 例:
 * \code
 * 	：
 * ## AISACコントロール値の設定
 * CriAtomExAisacControlId control_id = 0;
 * CriFloat32 control_value = 0.5f;
 * criAtomExPlayer_SetAisacControlById(player, control_id, control_value);
 * 
 * ## 再生の開始
 * id = criAtomExPlayer_Start(player);
 * 	：
 * ## パラメータの変更
 * ## 注意）この時点では再生中の音声のパラメータは変更されない。
 * control_value = 0.3f;
 * criAtomExPlayer_SetAisacControlById(player, control_id, control_value);
 * 
 * ## プレーヤに設定されたパラメータを再生中の音声にも反映
 * criAtomExPlayer_Update(player, id);
 * 	：
 *	※上記仮想コード内の"##"は行末までのコメントアウト開始を示しています。
 * \endcode
 * \par 備考:
 * AISACのコントロールタイプによって、以下のように挙動が変わります。
 * 	- オフ
 * 		- 本関数等によるAISACコントロール値が未設定の場合はそのAISACは動作しません。
 * 	- オートモジュレーション
 * 		- 本関数の設定値には影響されず、時間経過とともに自動的にAISACコントロール値が変化します。
 * 	- ランダム
 * 		- 本関数等によって設定されたAISACコントロール値を中央値として、データに設定されたランダム幅でランダマイズし、最終的なAISACコントロール値を決定します。
 * 		- ランダマイズ処理は再生開始時のパラメータ適用でのみ行われ、再生中の音声に対するAISACコントロール値変更はできません。
 * 		- 再生開始時にAISACコントロール値が設定されていなかった場合、0.0fを中央値としてランダマイズ処理を行います。
 * 		.
 * \sa criAtomExPlayer_Start, criAtomExPlayer_Update, criAtomExPlayer_UpdateAll, criAtomExPlayer_SetAisacControlByName, criAtomExPlayer_ClearAisacControls
 */
void CRIAPI criAtomExPlayer_SetAisacControlById(
	CriAtomExPlayerHn player, CriAtomExAisacControlId control_id, CriFloat32 control_value);

/*JP
 * \brief プレーヤに設定されているAISACコントロール値の削除
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomExプレーヤハンドル
 * \par 説明:
 * プレーヤに設定されているAISACコントロール値を全て削除します。<br>
 * また削除後、::criAtomExPlayer_Update 関数、::criAtomExPlayer_UpdateAll 関数を呼び出すことにより、
 * すでに再生中の音声に対してAISACコントロール値の削除が行えます。
 * \sa criAtomExPlayer_SetAisacControlById, criAtomExPlayer_SetAisacControlByName, criAtomExPlayer_Update, criAtomExPlayer_UpdateAll
 */
void CRIAPI criAtomExPlayer_ClearAisacControls(CriAtomExPlayerHn player);

/*==========================================================================
 *      CRI AtomEx Sequencer API
 *=========================================================================*/
/*JP
 * \brief シーケンスループ解除コールバック関数の登録
 * \ingroup ATOMEXLIB_SEQUENCER
 * \param[in]	func		シーケンスループ解除コールバック関数
 * \par 説明:
 * シーケンスループエンド時に発生するループ解除コールバック関数を登録します。<br>
 * 登録されたコールバック関数は、サーバー関数内でシーケンスループエンドを処理するタイミングで実行されます。<br>
 * \attention
 * そのため、サーバ処理への割り込みを考慮しないAPIを実行した場合、
 * エラーが発生したり、デッドロックが発生する可能性があります。<br>
 * 基本的に、コールバック関数内ではAtomライブラリAPIを使用しないでください。<br>
 * 本コールバック関数内で長時間処理をブロックすると、音切れ等の問題が発生しますので、
 * ご注意ください。<br>
 * <br>
 * コールバック関数は1つしか登録できません。<br>
 * 登録操作を複数回行った場合、既に登録済みのコールバック関数が、
 * 後から登録したコールバック関数により上書きされてしまいます。<br>
 * <br>
 * funcにNULLを指定するとことで登録済み関数の登録解除が行えます。<br>
 * \sa CriAtomExSequencerBreakLoopCbFunc_AT
 */
void CRIAPI criAtomExSequencer_SetBreakLoopCallback_AT(CriAtomExSequencerBreakLoopCbFunc_AT func);

/*==========================================================================
 *      CRI AtomEx API for Automotive
 *=========================================================================*/

#ifdef __cplusplus
}
#endif
#endif	/* CRI_INCL_CRI_ATOM_AT_DEF_H */

/* --- end of file --- */
