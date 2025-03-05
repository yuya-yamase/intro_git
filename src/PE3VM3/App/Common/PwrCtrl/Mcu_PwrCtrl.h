/* Mcu_PwrCtrl                                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name | Mcu_PwrCtrl/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

#ifndef     MCU_PWRCTRL_H
#define     MCU_PWRCTRL_H

#include <Ecu_Intg.h>
#include <Ecu_IntgHAL.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* 電源制御状態 */
#define MCU_PWRCTRL_BON_REQ               (0x00) /* +B起動シーケンス要求                    */
#define MCU_PWRCTRL_WAKEUP_REQ            (0x01) /* ウェイクアップシーケンス要求            */
#define MCU_PWRCTRL_SIPOFF_MCUSTANDBY_REQ (0x02) /* SIP電源OFF&MCUスタンバイシーケンス要求  */
#define MCU_PWRCTRL_STANDBY_REQ           (0x03) /* スタンバイシーケンス要求                */
#define MCU_PWRCTRL_NO_REQ                (0xFF) /* 要求無し(処理完了)                      */
/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void vd_g_Mcu_PwrCtrl_Bon_Wakeup_Req(void);
void vd_g_Mcu_PwrCtrl_SipOffMcuStandby_Req(void);
void vd_g_Mcu_PwrCtrl_Standby_Req(void);
void vd_g_Mcu_PwrCtrl_Task(void);

uint8 u1_g_Mcu_PwrCtrl_ShtdwnOk(void);

#endif /* MCU_PWRCTRL_H */

/**** End of File ***********************************************************/
