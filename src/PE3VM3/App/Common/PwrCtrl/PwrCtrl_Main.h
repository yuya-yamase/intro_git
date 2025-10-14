/* PwrCtrl_Main                                                                              */
/*********************************************************************************************/
/* Protected                                                                                 */
/* Copyright DENSO CORPORATION                                                               */
/*********************************************************************************************/

/*********************************************************************************************/
/* Object Name | PwrCtrl_Main/HEADER                                                         */
/*-------------------------------------------------------------------------------------------*/
/* Notes       |                                                                             */
/*********************************************************************************************/
#ifndef PWRCTRL_MAIN_H
#define PWRCTRL_MAIN_H

/*-------------------------------------------------------------------------------------------*/
/* Macros                                                                                    */
/*-------------------------------------------------------------------------------------------*/
/* 電源制御状態 */
#define PWRCTRL_MAIN_BON_REQ               (0x00U) /* +B起動シーケンス要求                   */
#define PWRCTRL_MAIN_WAKEUP_REQ            (0x01U) /* ウェイクアップシーケンス要求           */
#define PWRCTRL_MAIN_SIPOFF_MCUSTANDBY_REQ (0x02U) /* SIP電源OFF&MCUスタンバイシーケンス要求 */
#define PWRCTRL_MAIN_STANDBY_REQ           (0x03U) /* スタンバイシーケンス要求               */
#define PWRCTRL_MAIN_BUDET_REQ             (0x04U) /* BU断終了シーケンス要求                 */
#define PWRCTRL_MAIN_FORCEDOFF_REQ         (0x05U) /* SIP電源強制OFFシーケンス要求           */
#define PWRCTRL_MAIN_STBYCANCELST1_REQ     (0x06U) /* スタンバイ処理中の起動トリガ時シーケンス要求(SIP電源強制OFF処理開始) */
#define PWRCTRL_MAIN_STBYCANCELST2_REQ     (0x07U) /* スタンバイ処理中の起動トリガ時シーケンス要求(SYS系電源ON、SIP電源ON) */
#define PWRCTRL_MAIN_NO_REQ                (0xFFU) /* 要求無し(処理完了)                     */

#define PWRCTRL_MAIN_PROHIBITSLEEP_OFF     (0x00U)  /* スリープ許可 */
#define PWRCTRL_MAIN_PROHIBITSLEEP_ON      (0x01U)  /* スリープ禁止 */

/*-------------------------------------------------------------------------------------------*/
/* Function Prototypes                                                                       */
/*-------------------------------------------------------------------------------------------*/
void vd_g_PwrCtrlMainBonReq( void );
void vd_g_PwrCtrlMainWakeupReq( void );
void vd_g_PwrCtrlMainStandbyReq( void );
void vd_g_PwrCtrlMainBuDetReq( void );
void vd_g_PwrCtrlMainTask( void );

U1 u1_g_PwrCtrlMainShtdwnOk( void );
U1 u1_g_PwrCtrlWakeUpInfo( void );

void vd_g_PwrCtrlMainProhibitSleep( const U1 u1_a_ProhibitSleep );

#endif /* PWRCTRL_MAIN_H */

/**** End of File ****************************************************************************/
