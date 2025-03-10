/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 *【ファイル名】	Ecu_Arb.h
 *【モジュール名】	Arbitration
 *【機能】
 *【備考】
 ****************************************************************************/
#ifndef ECU_ARB_H
#define ECU_ARB_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS.h>
#include <ehvm.h>
#include <Ecu_Arb_Cfg.h>

/*----------------------------------------------------------------------------
 *		置換シンボル定義
 *--------------------------------------------------------------------------*/
#define ECU_VCCID0 ((ehvm_uint32_t)0U)
#define ECU_VCCID1 ((ehvm_uint32_t)1U)
#define ECU_VCCID2 ((ehvm_uint32_t)2U)
#define ECU_VCCID3 ((ehvm_uint32_t)3U)

/*----------------------------------------------------------------------------
 *		プロトタイプ宣言
 *--------------------------------------------------------------------------*/
#if (SS_USE_MODE == STD_ON)
void Ecu_Arb_init(void);
#if (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC)
boolean Ecu_Arb_mainFunction(boolean bAWake);
#endif /* SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC */
/* vv Wfdで置き換え予定 vv */
void Ecu_Arb_clearWkUpFctr(void);
#if (ECU_MY_VM == VMm)
void Ecu_Arb_wkUpFctrInit(void);
#endif
/* ^^ Wfdで置き換え予定 ^^ */
#endif /* SS_USE_MODE == STD_ON */

#endif /* ECU_ARB_H */
