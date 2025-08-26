/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 *【ファイル名】	Ecu_App.h
 *【モジュール名】	Application Sample
 *【機能】アプリケーションサンプル
 *【備考】
 ****************************************************************************/
#ifndef ECU_INTG_H
#define ECU_INTG_H

/*----------------------------------------------------------------------------
 *		ヘッダインクルード
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS.h>
#include <Ecu_IntgHAL_Cfg.h>

/*----------------------------------------------------------------------------
 *		Types
 *--------------------------------------------------------------------------*/
typedef uint32 Ecu_Intg_BootCauseType;
typedef uint8  Ecu_Intg_STResetType;
typedef uint8  Ecu_Intg_STResetKeyType;

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/
#define ECU_INTG_u4BTCAUSE_PON       (0x00000001UL)
#define ECU_INTG_u4BTCAUSE_RESET     (0x00000002UL)
#define ECU_INTG_u4BTCAUSE_WKUP_ANY  (0x00000004UL)
#define ECU_INTG_u4BTCAUSE_WKUP_TMR  (0x00000008UL)
#define ECU_INTG_u4BTCAUSE_WKUP_OTHS (0x00000010UL)

// Ecu_Intg_sleep()の引数用
#define ECU_INTG_u41stSLEEP (0UL)
#define ECU_INTG_u4RESLEEP  (1UL)

#define ECU_INTG_ST_RESET_SOFT ((Ecu_Intg_STResetType)0U)
#define ECU_INTG_ST_RESET_HARD ((Ecu_Intg_STResetType)1U)
#define ECU_INTG_ST_RESET_BRAM ((Ecu_Intg_STResetType)2U)

#define ECU_INTG_ST_RESET_KEY_ON  ((Ecu_Intg_STResetKeyType)0x5AU)
#define ECU_INTG_ST_RESET_KEY_OFF ((Ecu_Intg_STResetKeyType)0x00U)

#define ECU_INTG_ST_RESET_REASON_NUM (ECU_INTG_ST_RESET_BY_UNKNOWN + 1U)

/*----------------------------------------------------------------------------
 *		変数宣言
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		プロトタイプ宣言
 *--------------------------------------------------------------------------*/

void Ecu_Intg_init(void);
void Ecu_Intg_initApp(void);
#if 0
void Ecu_Intg_preClockUp(void);
void Ecu_Intg_postClockUp(void);
#endif

#if (SS_USE_MODE == STD_ON)
Std_ReturnType Ecu_Intg_arbitrate(SS_Mm_modeType u4SS_Mode);
#endif
Ecu_Intg_BootCauseType Ecu_Intg_hasBootCause(void);

void Ecu_Intg_checkAndImmShutdown(void);

Std_ReturnType Ecu_Intg_pushLevelDI(uint8 u1PriorityLevel);
Std_ReturnType Ecu_Intg_popLevelEI(void);

#if (SS_USE_SLEEP == STD_ON)
void Ecu_Intg_checkWakeup(void);
void Ecu_Intg_sleep(uint32 u4ResleepFlag);
#endif
#if ((SS_USE_MODE == STD_ON) && (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC))
void Ecu_Intg_sendSleepNG(void);
#endif

boolean Ecu_Intg_checkSTReset(uint8 u1Reason, boolean bClearFlag);
void    Ecu_Intg_performSTReset(Ecu_Intg_STResetType u1Type, uint8 u1Reason);

void Ecu_Intg_preSTResetCallout(Ecu_Intg_STResetType u1Type, uint8 u1Reason);

#endif /* ECU_INTG_H */
