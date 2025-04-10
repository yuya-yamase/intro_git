/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 *【ファイル名】	Ecu_AppIntg.c
 *【モジュール名】	Application Sample
 *【機能】
 *【備考】
 ****************************************************************************/
/*----------------------------------------------------------------------------
 *		ヘッダインクルード
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS.h>
// #include <Wdg.h>

#include "icu_drv_wk.h"

#include <Ecu_Memmap_SdaDisableB_env.h>
#include <Ecu_Memmap.h>
#include <Ecu_Intg.h>
#include <Ecu_Int.h>
#include <Ecu_Intg_Callout.h>

/*----------------------------------------------------------------------------
 *		置換シンボル定義
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		変数宣言
 *--------------------------------------------------------------------------*/

#include <Ecu_Memmap_SdaDisableE_env.h>

/*----------------------------------------------------------------------------
 *      プロトタイプ宣言
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		プログラム
 *--------------------------------------------------------------------------*/
#if 0
Std_ReturnType Ecu_Intg_preClockCallout(Ecu_Intg_BootCauseType u4BootCause)
{
    return E_OK;
}

Std_ReturnType Ecu_Intg_postClockCallout(Ecu_Intg_BootCauseType u4BootCause)
{
    return E_OK;
}
#endif
Std_ReturnType Ecu_Intg_initAppCallout(Ecu_Intg_BootCauseType u4BootCause)
{
    return E_OK;
}

#if (SS_USE_SLEEP == STD_ON)
uint32 Ecu_Intg_sleepCallout(void)
{
    // 0: 間欠起床タイマOFF
    // 1000: 1sアラーム設定
    // 10000: 10sアラーム設定

    return (0UL);
}
#endif

#if (SS_USE_SLEEP == STD_ON)
uint32 Ecu_Intg_reSleepCallout(void)
{
    // 0: 間欠起床タイマOFF
    // 1000: 1sアラーム設定
    // 10000: 10sアラーム設定
    vd_g_IcuWkInit((U1)ICU_WK_CFG_PREP_MCU_TO_LPM);
    return (0UL);
}
#endif

#if (SS_USE_SLEEP == STD_ON)
// TRUE : ウェイクアップ要求する
// FALSE :ウェイクアップ要求しない（起動要因=ECU_INTG_u4BTCAUSE_WKUP_ANYならFALSEでもウェイクアップする）
boolean Ecu_Intg_isWakeupCallout(Ecu_Intg_BootCauseType u4BootCause)
{
    static const U4     u4_s_ECU_M_USRHK_WKSRC_IRQST = (U4)(ICU_WK_WRQ_HWI_WK | ICU_WK_WRQ_CAN_VEH);

    U4      u4_t_irqst;
    U1      u1_t_ret;

    u1_t_ret = (U1)FALSE;
    u4_t_irqst = u4_g_IcuWkRQst((U1)ICU_WK_GR_A0, u4_s_ECU_M_USRHK_WKSRC_IRQST, (U1)FALSE);
    if(u4_t_irqst != (U4)0U){
        u1_t_ret = (U1)TRUE;
    }
    return (u1_t_ret);
}
#endif

void Ecu_Intg_preSTResetCallout(Ecu_Intg_STResetType u1Type, uint8 u1Reason)
{
    /* リセット前ユーザ実装処理 */

    return;
}
