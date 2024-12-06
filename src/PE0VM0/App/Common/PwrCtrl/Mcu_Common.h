/* Mcu_Common                                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name | Mcu_Common/HEADER                                          */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

#ifndef MCU_COMMON_H
#define MCU_COMMON_H

#include <Std_Types.h>
#include "Dio.h"
#include "Dio_Symbols.h"
#include "pwm_drv.h"

#define MCU_SYS_PWR_OFF (0U)
#define MCU_SYS_PWR_ON (1U)

#define MCU_DIO_LOW  (0U)
#define MCU_DIO_HIGH (1U)

/* 異常系チェック実行可否定義 */
#define MCU_ERR_CHK (1U)

#if (MCU_ERR_CHK == 1U)
/* 異常系チェック用STB定義 */
extern uint8 u1_s_Mcu_Err_dbg_state;

#define MCU_ERR_NON            (0U)  /* 異常系エラー未発生 */
#define MCU_ERR_BON_STEP2_2    (1U)  /* BONシーケンス AOSS_SLEEP_ENTRY_EXIT Lo待ち異常 */
#define MCU_ERR_BON_STEP2_3    (2U)  /* BONシーケンス POFF_COMPLETE_N Lo待ち異常 */
#define MCU_ERR_BON_STEP4_1    (3U)  /* BONシーケンス PM_PSAIL_ERR_N Lo待ち異常 */
#define MCU_ERR_BON_STEP5_1    (4U)  /* BONシーケンス PMA_PS_HOLD Lo待ち異常 */
#define MCU_ERR_BON_STEP6_1    (5U)  /* BONシーケンス POFF_COMPLETE_N Hi待ち異常 */
#define MCU_ERR_BON_STEP7_1    (6U)  /* BONシーケンス SOC_RESOUT_N Hi待ち異常 */
#define MCU_ERR_BON_STEP7_2    (7U)  /* BONシーケンス SAIL_RESOUT_N Hi待ち異常 */
#define MCU_ERR_BON_STEP8_1    (8U)  /* BONシーケンス PMA_PS_HOLD Hi待ち異常 */
#define MCU_ERR_BON_MMSTBY     (9U)  /* BONシーケンス MM_STBY_N Hi待ち異常 */
#define MCU_ERR_WAKE_AOSS_HI   (10U) /* ウェイクアップシーケンス AOSS_SLEEP_ENTRY_EXIT Hi待ち異常 */
#define MCU_ERR_WAKE_AOSS_LO   (11U) /* ウェイクアップシーケンス AOSS_SLEEP_ENTRY_EXIT Lo待ち異常 */
#define MCU_ERR_WAKE_MMSTBY    (12U) /* ウェイクアップシーケンス MM_STBY_N Hi待ち異常 */
#define MCU_ERR_SIPOFF_STEP2_1 (13U) /* SIP電源OFF&MCUスタンバイシーケンス MM_STBY_N Lo待ち異常 */
#define MCU_ERR_SIPOFF_STEP3_1 (14U) /* SIP電源OFF&MCUスタンバイシーケンス PMA_PS_HOLD Lo待ち異常 */
#define MCU_ERR_SIPOFF_STEP4_1 (15U) /* SIP電源OFF&MCUスタンバイシーケンス SOC_RESOUT_N Lo待ち異常 */
#define MCU_ERR_SIPOFF_STEP4_2 (16U) /* SIP電源OFF&MCUスタンバイシーケンス SAIL_RESOUT_N Lo待ち異常 */
#define MCU_ERR_SIPOFF_STEP4_3 (17U) /* SIP電源OFF&MCUスタンバイシーケンス POFF_COMPLETE_N Lo待ち異常 */
#define MCU_ERR_STANDBY_MMSTBY (18U) /* スタンバイシーケンス MM_STBY_N Lo待ち異常 */
#define MCU_ERR_STANDBY_AOSS   (19U) /* スタンバイシーケンス AOSS_SLEEP_ENTRY_EXIT Hi待ち異常 */

/* 異常系チェック用STB定義 */
#endif /* MCU_ERR_CHK == 1U */

#endif /* MCU_COMMON_H */

/**** End of File ***********************************************************/
