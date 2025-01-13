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

#include "veh_opemd.h"
#include "oxcan.h"
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
ISR(INTOSTM3_ISR);
ISR(INTP4_ISR);

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

    return E_OK;
}


Std_ReturnType Ecu_Intg_initAppCallout(Ecu_Intg_BootCauseType u4BootCause)
{
    return E_OK;
}


Std_ReturnType Ecu_Intg_mainFuncCddHigh(void)
{

    BswM_CS_MainFunctionHigh();

    return E_OK;
}


Std_ReturnType Ecu_Intg_mainFuncCddMidIn(void)
{

    /* vd_g_Wdg_SetTriggerCondition((U2)0U); */
    vd_g_oXCANMainPreTask();
    vd_g_VehopemdMainTask();
    /*vd_g_Wdg_SetTriggerCondition((U2)0U);*/

    return E_OK;
}


Std_ReturnType Ecu_Intg_mainFuncApp(void)
{
    return E_OK;
}


Std_ReturnType Ecu_Intg_mainFuncCddMidOut(void)
{


    vd_g_oXCANMainPostTask();


    return E_OK;
}


Std_ReturnType Ecu_Intg_mainFuncCddLow(void)   /* C-DC CEN VM Low Task: 1ms */
{
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


ISR(INTOSTM3_ISR)
{
    /*    INTOSTM3_ISR;*/
}

ISR(INTP4_ISR)
{
    /*    INTP4_ISR;*/
}
