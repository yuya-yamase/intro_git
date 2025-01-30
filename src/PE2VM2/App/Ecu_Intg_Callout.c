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

#include "veh_opemd.h"
#include "oxcan.h"
#include "l3r_test.h"

/*----------------------------------------------------------------------------
 *		置換シンボル定義
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		変数宣言
 *--------------------------------------------------------------------------*/
static U1 u1_s_5ms_counter;
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
    switch (u4BootCause){
        case ECU_INTG_u4BTCAUSE_PON :
            vd_g_oXCANRstInit();
            vd_g_VehopemdRstInit();
            break;
        case ECU_INTG_u4BTCAUSE_RESET:
            vd_g_oXCANRstInit();
            vd_g_VehopemdRstInit();
           break;
        default:
            vd_g_oXCANWkupInit();
            vd_g_VehopemdWkupInit();
            break;
    }

    u1_s_5ms_counter = 0;
    return E_OK;
}


Std_ReturnType Ecu_Intg_initAppCallout(Ecu_Intg_BootCauseType u4BootCause)
{
    /* XSPI初期化処理 */
    xspi_Init( XSPI_CH_01 );

    vd_g_XspiIviInit();

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

    vd_g_L3rTestCycleHigh();
    BswM_CS_MainFunctionHigh();

    return E_OK;
}


Std_ReturnType Ecu_Intg_mainFuncCddMidIn(void)   /* C-DC IVI Mid Task: 1ms */
{
    /* vd_g_Wdg_SetTriggerCondition((U2)0U); */
    if ( u1_s_5ms_counter >= 4 )
    {

        vd_g_oXCANMainPreTask();

        vd_g_VehopemdMainTask();
    }
    /* vd_g_Wdg_SetTriggerCondition((U2)0U);*/

    return E_OK;
}


Std_ReturnType Ecu_Intg_mainFuncApp(void)   /* C-DC IVI Mid Task: 1ms */
{
    /* XSPI Receive */
    vd_g_XspiIviMain1st();

    /* IVI */
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
    /* ↓11/15sample↓ */
    /* vd_g_oXCANMainPostTask()内でBswM_Can_GetChFailStatus()をコールして「レジスタ固着異常」「初期化異常」をMCALに通知しているが */
    /* 仮想CAN通信では「レジスタ固着異常」「初期化異常」は発生しない為、差し替え不要 */
    /* vd_g_oXCANMainPostTask(); */
    /* ↑11/15sample↑ */
    if ( u1_s_5ms_counter >= 4 )
    {
	    vd_g_oXCANMainPostTask();
        u1_s_5ms_counter = 0;
    }
    else
    {
        u1_s_5ms_counter++;
    }

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
