/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 *【ファイル名】	Ecu_App.h
 *【モジュール名】	Application Sample
 *【機能】アプリケーションサンプル
 *【備考】
 ****************************************************************************/
#ifndef ECU_INTG_CALLOUT_H
#define ECU_INTG_CALLOUT_H

/*----------------------------------------------------------------------------
 *		ヘッダインクルード
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <Ecu_Intg.h>

/*----------------------------------------------------------------------------
 *		Types
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		変数宣言
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		プロトタイプ宣言
 *--------------------------------------------------------------------------*/
#if 0
Std_ReturnType Ecu_Intg_preClockCallout(Ecu_Intg_BootCauseType u4BootCause);
Std_ReturnType Ecu_Intg_postClockCallout(Ecu_Intg_BootCauseType u4BootCause);
#endif
Std_ReturnType Ecu_Intg_initAppCallout(Ecu_Intg_BootCauseType u4BootCause);

#if (SS_USE_SLEEP == STD_ON)
uint32  Ecu_Intg_sleepCallout(void);
uint32  Ecu_Intg_reSleepCallout(void);
boolean Ecu_Intg_isWakeupCallout(Ecu_Intg_BootCauseType u4BootCause);
#endif

void Ecu_Intg_preSTResetCallout(Ecu_Intg_STResetType u1Type, uint8 u1Reason);

#endif /* ECU_INTG_CALLOUT_H */
