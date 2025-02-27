/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_SleepTm.c
 * [Module]			SleepTm
 * [Function]		Sleep Timer
 * [Notes]			None
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_TYPE.h>
#include <SS_Internal.h>

#include <SS_MemmapSdaDisableB_Env.h>
#include <SS_Memmap_Env.h>
#include <SS_SleepTm_BuData.h>

#include <SS_MemmapSdaDisableE_Env.h>

#include <SS_MemmapSdaSelectB_Env.h>
#include <SS_SleepTm.h>
#include <SS_HSTm.h>

#include <SS_MemmapSdaSelectE_Env.h>

/*----------------------------------------------------------------------------
 *		Prototypes
 *--------------------------------------------------------------------------*/
#if (SS_USE_SLEEP == STD_ON)

static Std_ReturnType SS_SleepTm_getAlarmPeriod(uint32 *pt_AlarmPeriod);
static Std_ReturnType SS_SleepTm_getElapsedTime(uint32 *pt_ElapsedTime);

/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/
#define SS_SleepTm_setDataWithBkUp(var, val) \
    {                                        \
        (var)       = (val);                 \
        (var##BkUp) = ~(val);                \
    }

/**---------------------------------------------------------------------------
 * [Format]		void SS_SleepTm_stop(void)
 * [Function]	目覚ましタイマ停止処理
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_SleepTm_stop(void)
{
    /* 各変数の初期化 */
    SS_SleepTm_setDataWithBkUp(SS_SleepTm_u4AlarmPeriod, 0UL);
    SS_SleepTm_setDataWithBkUp(SS_SleepTm_u4ElapsedTime, 0UL);

    /* タイマ停止 */
    SS_HSTm_stop();

    return;
}

/**---------------------------------------------------------------------------
 * [Format]		Std_ReturnType SS_SleepTm_start(uint32 u4_RealTime)
 * [Function]	目覚ましタイマ開始処理
 * [Arguments]	uint32 u4_RealTime : スリープ指定時間(実時間)
 * [Return]		Std_ReturnType
 *				  - E_OK : 開始成功
 *				  - E_NOT_OK : 開始失敗 (範囲外の指定)
 * [Notes]		None
 *--------------------------------------------------------------------------*/
Std_ReturnType SS_SleepTm_start(uint32 u4_RealTime)
{
    uint32         u4_RegTime;
    Std_ReturnType u1_Result;

    /* auto変数の初期化 */
    u1_Result = E_NOT_OK;

    /* 入力引数が許容範囲か確認する */
    if ((u4_RealTime <= SS_SLEEPTM_u4SLEEPTIME_MAX) && (u4_RealTime >= SS_u4REGSLEEPTIME_MIN))
    {
        /* 周期を変更するので一旦停止 */
        SS_SleepTm_stop();

        /* ユーザが指定したアラーム周期をSleepTm LSBから */
        /* HSTm LSBに変換して変数を更新する */
        u4_RegTime = SS_HSTm_convLsbRealToReg(u4_RealTime);
        SS_SleepTm_setDataWithBkUp(SS_SleepTm_u4AlarmPeriod, u4_RegTime);

        /* アラーム周期を指定してタイマスタート */
        SS_HSTm_start(u4_RegTime);

        u1_Result = E_OK;
    }

    return u1_Result;
}

/**---------------------------------------------------------------------------
 * [Format]		Std_ReturnType SS_SleepTm_getTime(uint32* pt_RealTime)
 * [Function]	スリープ経過時間取得
 * [Arguments]	uint32* pt_RealTime スリープ経過時間(Elapsed)
 * [Return] 	Std_ReturnType
 *				  - E_OK	 : 取得成功
 *				  - E_NOT_OK : 取得失敗 (RAM異常)
 * [Notes]		None
 *--------------------------------------------------------------------------*/
Std_ReturnType SS_SleepTm_getTime(uint32 *pt_RealTime)
{
    uint32         u4_AlarmPeriod;
    uint32         u4_ElapsedTime;
    uint32         u4_UnclearedTime;
    Std_ReturnType u1_Result;
    Std_ReturnType u1_ResultAlarmPeriod;
    Std_ReturnType u1_ResultElapsedTime;

    /* auto変数の初期化 */
    u4_AlarmPeriod = 0UL;
    u4_ElapsedTime = 0UL;
    u1_Result      = E_NOT_OK;

    if (pt_RealTime != NULL_PTR)
    {
        /* アラーム周期を取得する */
        u1_ResultAlarmPeriod = SS_SleepTm_getAlarmPeriod(&u4_AlarmPeriod);
        /* 経過時間を取得する */
        u1_ResultElapsedTime = SS_SleepTm_getElapsedTime(&u4_ElapsedTime);

        if ((u1_ResultAlarmPeriod == E_OK) && (u1_ResultElapsedTime == E_OK))
        { /* どちらとも取得できた場合 */
            if (u4_AlarmPeriod != 0U)
            { /* アラーム周期が0でない場合 */
                /* 未精算時間を取得する */
                u4_UnclearedTime = SS_HSTm_getTime(u4_AlarmPeriod);

                if ((SS_TYPE_u4MAX - u4_UnclearedTime) >= u4_ElapsedTime)
                {
                    /* 未精算時間を加算する */
                    u4_ElapsedTime += u4_UnclearedTime;

                    u1_Result = E_OK;
                }
                else
                { /* ラップラウンドにより加算できないので、E_NOT_OKを返す */
                    u1_Result = E_NOT_OK;
                }
            }
            /* 1msLSBに変換して返却値(引数ポインタ)に代入する */
            *pt_RealTime = SS_HSTm_convLsbRegToReal(u4_ElapsedTime);
        }
    }

    return u1_Result;
}

/**---------------------------------------------------------------------------
 * [Format]		boolean SS_SleepTm_isUp(void)
 * [Function]	目覚ましタイマ満了確認
 * [Arguments]	None
 * [Return]		boolean
 *				  - TRUE : 目覚ましタイマ満了した
 *				  - FALSE : 目覚ましタイマ満了していない
 * [Notes]		None
 *--------------------------------------------------------------------------*/
boolean SS_SleepTm_isUp(void)
{
    /* タイマ満了フラグを返却する */
    return SS_HSTm_isExpired();
}

/**---------------------------------------------------------------------------
 * [Format]		Std_ReturnType SS_SleepTm_resetUp(void)
 * [Function]	目覚ましタイマ満了状態リセット
 * [Arguments]	None
 * [Return]		Std_ReturnType
 *				  - E_OK : タイマ満了状態リセット成功
 *				  - E_NOT_OK : タイマ満了状態リセット失敗 (RAM異常)
 * [Notes]		None
 *--------------------------------------------------------------------------*/
Std_ReturnType SS_SleepTm_resetUp(void)
{
    boolean        b_IsExpired;
    uint32         u4_AlarmPeriod;
    uint32         u4_ElapsedTime;
    Std_ReturnType u1_Result;
    Std_ReturnType u1_ResultAlarmPeriod;
    Std_ReturnType u1_ResultElapsedTime;

    /* auto変数の初期化 */
    u4_AlarmPeriod = 0UL;
    u4_ElapsedTime = 0UL;
    u1_Result      = E_NOT_OK;

    /* タイマ満了確認する */
    b_IsExpired = SS_HSTm_isExpired();

    if (b_IsExpired == TRUE)
    { /* 満了している場合 */
        /* アラーム周期を取得する */
        u1_ResultAlarmPeriod = SS_SleepTm_getAlarmPeriod(&u4_AlarmPeriod);
        /* 経過時間を取得する */
        u1_ResultElapsedTime = SS_SleepTm_getElapsedTime(&u4_ElapsedTime);

        if ((u1_ResultAlarmPeriod == E_OK) && (u1_ResultElapsedTime == E_OK))
        { /* どちらとも取得できた場合 */
            if ((SS_TYPE_u4MAX - u4_AlarmPeriod) >= u4_ElapsedTime)
            {
                /* 経過時間にアラーム周期を加算する */
                u4_ElapsedTime += u4_AlarmPeriod;
                SS_SleepTm_setDataWithBkUp(SS_SleepTm_u4ElapsedTime, u4_ElapsedTime);
                /* 戻り値にE_OKを設定して終了 */
                u1_Result = E_OK;
            }
            else
            { /* ラップラウンドにより加算できないので、E_NOT_OKを返す */
                u1_Result = E_NOT_OK;
            }
        }
        /* アラーム周期をリロードする */
        SS_HSTm_reload(u4_AlarmPeriod);
    }
    else
    { /* 満了してなかったら、何もせずにE_OKを返す */
        u1_Result = E_OK;
    }

    return u1_Result;
}

/**---------------------------------------------------------------------------
 * [Format]		static Std_ReturnType SS_SleepTm_getAlarmPeriod(uint32* pt_AlarmPeriod)
 * [Function]	ユーザが指定したスリープ時間（レジスタ設定LSB）を取得する
 * [Arguments]	uint32* pt_AlarmPeriod: （出力）スリープ指定時間(レジスタ設定LSB)
 * [Return] 	Std_ReturnType
 *				  - E_OK	 : 取得成功
 *				  - E_NOT_OK : 取得失敗
 * [Notes]		None
 *--------------------------------------------------------------------------*/
static Std_ReturnType SS_SleepTm_getAlarmPeriod(uint32 *pt_AlarmPeriod)
{
    Std_ReturnType u1_Result;

    /* auto変数の初期化 */
    u1_Result = E_NOT_OK;

    /* 破損判定 */
    
    if (SS_SleepTm_u4AlarmPeriod == (~SS_SleepTm_u4AlarmPeriodBkUp))
    { /* 破損してなかったら */
        /* アラーム周期を返却する */
        *pt_AlarmPeriod = SS_SleepTm_u4AlarmPeriod;
        u1_Result       = E_OK;
    }

    return u1_Result;
}

/**---------------------------------------------------------------------------
 * [Format]		static Std_ReturnType SS_SleepTm_getElapsedTime(uint32* pt_ElapsedTime)
 * [Function]	これまでに確定したスリープ経過時間（レジスタ設定LSB）を取得する
 * [Arguments]	uint32* pt_ElapsedTime: （出力）スリープ経過時間(レジスタ設定LSB)
 * [Return] 	Std_ReturnType
 *				  - E_OK	 : 取得成功
 *				  - E_NOT_OK : 取得失敗
 * [Notes]		None
 *--------------------------------------------------------------------------*/
static Std_ReturnType SS_SleepTm_getElapsedTime(uint32 *pt_ElapsedTime)
{
    Std_ReturnType u1_Result;

    /* auto変数の初期化 */
    u1_Result = E_NOT_OK;

    /* 破損判定 */
    
    if (SS_SleepTm_u4ElapsedTime == (~SS_SleepTm_u4ElapsedTimeBkUp))
    { /* 破損してなかったら */
        /* 経過時間を返却する */
        *pt_ElapsedTime = SS_SleepTm_u4ElapsedTime;
        u1_Result       = E_OK;
    }

    return u1_Result;
}

#endif /* (SS_USE_SLEEP == STD_ON) */
