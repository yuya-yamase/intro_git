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
#include "OS.h"

#include <Ecu_Memmap_SdaDisableB_env.h>
#include <Ecu_Memmap.h>
#include <Ecu_Intg.h>
#include <Ecu_Intg_Callout.h>
#include <Ecu_Int.h>

#include "wdg_drv.h"

#include "xspi.h"

/* IVI */
#include "x_spi_ivi.h"

#include "IVI_PwrCtrl_Main.h"
#include "IVI_ExtSigCtrl_Main.h"
#include "IVI_PictCtrl_Main.h"
#include "IVI_GyrCtrl_Main.h"
#include "IVI_DspCtrl_Main.h"
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
ISR(INTOSTM1_ISR);
ISR(INTP38_ISR);

/*----------------------------------------------------------------------------
 *		プログラム
 *--------------------------------------------------------------------------*/

Std_ReturnType Ecu_Intg_initCdd(Ecu_Intg_BootCauseType u4BootCause)
{
    return E_OK;
}


Std_ReturnType Ecu_Intg_initAppCallout(Ecu_Intg_BootCauseType u4BootCause)
{
    /* XSPI初期化処理 */
    xspi_Init( XSPI_CH_01 );

    /* IVI */
    vd_g_Ivi_PwrCtrl_Main_Bon_init();
    vd_g_Ivi_ExtSigCtrl_Main_Bon_init();
    vd_g_Ivi_PictCtrl_Main_Bon_init();
    vd_g_Ivi_GyrCtrl_Main_Bon_init();
    vd_g_Ivi_DspCtrl_Main_Bon_init();

    return E_OK;
}


Std_ReturnType Ecu_Intg_mainFuncCddHigh(void)
{
    /* IVI */
    vd_g_Ivi_PictCtrl_Main_1ms();

    return E_OK;
}


Std_ReturnType Ecu_Intg_mainFuncCddMidIn(void)   /* C-DC IVI Mid Task: 1ms */
{
    return E_OK;
}


Std_ReturnType Ecu_Intg_mainFuncApp(void)   /* C-DC IVI Mid Task: 1ms */
{
    /* XSPI Receive */
    vd_g_XspiIviMain1st();

    vd_g_Ivi_PwrCtrl_Main();
    vd_g_Ivi_ExtSigCtrl_Main();
    vd_g_Ivi_PictCtrl_Main_5ms();
    vd_g_Ivi_GyrCtrl_Main();
    vd_g_Ivi_DspCtrl_Main();

    /* XSPI Send */
    vd_g_XspiIviMain2nd();

    return E_OK;
}


Std_ReturnType Ecu_Intg_mainFuncCddMidOut(void)   /* C-DC IVI Mid Task: 1ms */
{
    return E_OK;
}


Std_ReturnType Ecu_Intg_mainFuncCddLow(void)   /* C-DC IVI Low Task: 10ms */
{
    vd_g_Wdg_SetTriggerCondition((U2)0U);
    return E_OK;
}


Std_ReturnType Ecu_Intg_idleFuncOut(void)
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

    return (0UL);
}
#endif

#if (SS_USE_SLEEP == STD_ON)
// TRUE : ウェイクアップ要求する
// FALSE :ウェイクアップ要求しない（起動要因=ECU_INTG_u4BTCAUSE_WKUP_ANYならFALSEでもウェイクアップする）
boolean Ecu_Intg_isWakeupCallout(Ecu_Intg_BootCauseType u4BootCause)
{
    return FALSE;
}
#endif

void Ecu_Intg_preSTResetCallout(Ecu_Intg_STResetType u1Type, uint8 u1Reason)
{
    /* リセット前ユーザ実装処理 */

    return;
}

ISR(INTOSTM1_ISR)
{
    /*    INTOSTM1_ISR;*/
    /* XSPIメイン処理 */
    xspi_Main( XSPI_CH_01 );

}

ISR(INTP38_ISR)
{
    /*    INTP38_ISR;*/
}
