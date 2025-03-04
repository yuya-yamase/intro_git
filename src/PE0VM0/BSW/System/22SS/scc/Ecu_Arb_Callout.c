/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 *【ファイル名】	Ecu_Arb_Callout.c
 *【モジュール名】	Arbitration
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
#include <Ecu_Arb_Callout.h>
#include <Ecu_Arb_Cfg.h>
#include <Ecu_IntgHAL.h>

/*----------------------------------------------------------------------------
 *		置換シンボル定義
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		変数宣言
 *--------------------------------------------------------------------------*/
#include <Ecu_Memmap_SdaDisableE_env.h>
#if (ECU_MY_VM == VMm)
/**---------------------------------------------------------------------------
 * [Format]     void Ecu_Arb_exitInitCallout(void)
 * [Function]   Init exit処理Callout
 * [Arguments]  None
 * [Return]     None
 * [Notes]      None
 *--------------------------------------------------------------------------*/
void Ecu_Arb_exitInitCallout(void)
{
    /* 一般VMのRUN遷移確認後に実施する処理を実装 */
    Ecu_IntgHAL_clearRAMV();
    Ecu_IntgHAL_clearResetFactor();

    return;
}

/**---------------------------------------------------------------------------
 * [Format]     void Ecu_Arb_entryPrpSlpCallout(void)
 * [Function]   スリープ準備開始Callout
 * [Arguments]  None
 * [Return]     None
 * [Notes]      None
 *--------------------------------------------------------------------------*/
void Ecu_Arb_entryPrpSlpCallout(void)
{
    /* NvM_WriteAll等を想定 */
    return;
}

/**---------------------------------------------------------------------------
 * [Format]     void Ecu_Arb_stopPrpSlpCallout(void)
 * [Function]   スリープ準備中断Callout
 * [Arguments]  None
 * [Return]     None
 * [Notes]      None
 *--------------------------------------------------------------------------*/
void Ecu_Arb_stopPrpSlpCallout(void)
{
    /* NvM_CancelWriteAll等を想定 */
    return;
}

/**---------------------------------------------------------------------------
 * [Format]     boolean Ecu_Arb_prpSlpCallout(void)
 * [Function]   スリープ準備Callout
 * [Arguments]  None
 * [Return]     スリープ準備完了:TRUE、スリープ準備未完了:FALSE
 * [Notes]      None
 *--------------------------------------------------------------------------*/
boolean Ecu_Arb_prpSlpCallout(void)
{
    boolean bSleepOK;
    /* スリープ準備処理を監視して処理完了したらTRUEを返してください */
    bSleepOK = TRUE;

    return (bSleepOK);
}
#endif

/**---------------------------------------------------------------------------
 * [Format]     void Ecu_Arb_awakeMskCallout(void)
 * [Function]   Awake要因マスクCallout
 * [Arguments]  None
 * [Return]     None
 * [Notes]      None
 *--------------------------------------------------------------------------*/
void Ecu_Arb_awakeMskCallout(void)
{
    /* Awake要因マスク処理の実装を想定 */
    return;
}

/**---------------------------------------------------------------------------
 * [Format]     void Ecu_Arb_awakeUnMskCallout(void)
 * [Function]   Awake要因アンマスクCallout
 * [Arguments]  None
 * [Return]     None
 * [Notes]      None
 *--------------------------------------------------------------------------*/
void Ecu_Arb_awakeUnMskCallout(void)
{
    /* Awake要因アンマスク処理の実装を想定 */
    return;
}
