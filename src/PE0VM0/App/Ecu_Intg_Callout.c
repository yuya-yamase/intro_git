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

#include <Ecu_Memmap_SdaDisableB_env.h>
#include <Ecu_Memmap.h>
#include <Ecu_Intg.h>
#include <Ecu_Intg_Callout.h>
#include <Ecu_Int.h>

#include "Dio.h"
#include "Adc.h"
#include "wdg_drv.h"

#include "iohw_adc.h"
#include "iohw_diflt.h"

#include "icu_drv_wk.h"

#include "veh_opemd.h"
#include "oxcan.h"

#include "stub.h"

#include "Mcu_PwrCtrl.h"

/* 暫定 */
#include "Mcu_Sys_Pwr.h"

#include "ExtSigCtrl_Main.h"

/*----------------------------------------------------------------------------
 *		置換シンボル定義
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		変数宣言
 *--------------------------------------------------------------------------*/
static U1                    u1_s_iohw_adc_flipcount;

#include <Ecu_Memmap_SdaDisableE_env.h>

/*----------------------------------------------------------------------------
 *      プロトタイプ宣言
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		プログラム
 *--------------------------------------------------------------------------*/

Std_ReturnType Ecu_Intg_initCdd(Ecu_Intg_BootCauseType u4BootCause)
{

    switch (u4BootCause){
        case ECU_INTG_u4BTCAUSE_PON :
            vd_g_oXCANRstInit();
            vd_g_VehopemdRstInit();

            vd_g_StubBonInit();
            break;
        case ECU_INTG_u4BTCAUSE_RESET:
            vd_g_oXCANRstInit();
            vd_g_VehopemdRstInit();

            vd_g_StubRstInit();
            break;
        default:
            vd_g_oXCANWkupInit();
            vd_g_VehopemdWkupInit();

            vd_g_StubWkupInit();
            break;
    }

    return E_OK;
}


Std_ReturnType Ecu_Intg_initAppCallout(Ecu_Intg_BootCauseType u4BootCause)
{
    /* User Hook start */
    vd_g_Mcu_PwrCtrl_Bon_Wakeup_Req( u4BootCause ); /* +B-ONウェイクアップシーケンス開始 */
    ExtSigCtrl_Init();
    /* User Hook end */

    return E_OK;
}


Std_ReturnType Ecu_Intg_mainFuncCddHigh(void)
{
    BswM_CS_MainFunctionHigh();

    return E_OK;
}


Std_ReturnType Ecu_Intg_mainFuncCddMidIn(void)
{
    vd_g_Wdg_SetTriggerCondition((U2)0U);

    vd_g_oXCANMainPreTask();
    vd_g_VehopemdMainTask();

    return E_OK;
}


Std_ReturnType Ecu_Intg_mainFuncApp(void)
{
    /* User Hook start */
    vd_g_Mcu_PwrCtrl_Task1ms();
    ExtSigCtrl_MainFunction();

    /* 暫定：デバイスON制御 */
    Mcu_Dev_Pwron();

    /* User Hook end */

    return E_OK;
}


Std_ReturnType Ecu_Intg_mainFuncCddMidOut(void)
{
    if ( ( u1_s_iohw_adc_flipcount & 0x01 ) == 0x01 )
    {
        vd_g_IoHwDifltMainTask();               /* 10ms */
        vd_g_IoHwAdcSeqAct((U1)FALSE);
        vd_g_IoHwAdcCvstStart();
    }
    else
    {
        vd_g_IoHwAdcCvstFinish();
        vd_g_IoHwAdcMainTask();
    }
    u1_s_iohw_adc_flipcount++;

    vd_g_oXCANMainPostTask();

    return E_OK;
}


Std_ReturnType Ecu_Intg_mainFuncCddLow(void)   /* C-DC VM0 Low Task: 10ms */
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
