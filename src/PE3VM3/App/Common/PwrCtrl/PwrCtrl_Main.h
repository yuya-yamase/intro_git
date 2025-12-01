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

#include "PwrCtrl_cfg_private.h"
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

/* 端子モニタ取得端子 */
#define PWRCTRL_MAIN_PINID_AOSS_SLP        (PWRCTRL_CFG_PRIVATE_KIND_AOSS_SLP_ENTRY_EXIT)  /* AOSS_SLP_ENTRY_EXIT */
#define PWRCTRL_MAIN_PINID_POFF_COMP       (PWRCTRL_CFG_PRIVATE_KIND_POFF_COMPLETE_N)      /* POFF_COMPLETE_N     */
#define PWRCTRL_MAIN_PINID_PMA_PS          (PWRCTRL_CFG_PRIVATE_KIND_PMA_PS_HOLD)          /* PMA_PS_HOLD         */
#define PWRCTRL_MAIN_PINID_SOC_RES         (PWRCTRL_CFG_PRIVATE_KIND_SOC_RESOUT_N)         /* SOC_RESOUT_N        */
#define PWRCTRL_MAIN_PINID_SAIL_RES        (PWRCTRL_CFG_PRIVATE_KIND_SAIL_RESOUT_N)        /* SAIL_RESOUT_N       */
#define PWRCTRL_MAIN_PINID_MM_STBY         (PWRCTRL_CFG_PRIVATE_KIND_MM_STBY_N)            /* MM_STBY_N           */
#define PWRCTRL_MAIN_PINID_BOOT            (PWRCTRL_CFG_PRIVATE_KIND_BOOT)                 /* BOOT                */
#define PWRCTRL_MAIN_PINID_BU_DET          (PWRCTRL_CFG_PRIVATE_KIND_BU_DET)               /* BU_DET              */
#define PWRCTRL_MAIN_PINID_DBG_FAIL        (PWRCTRL_CFG_PRIVATE_KIND_DBG_FAIL_OFF)         /* DBG_FAIL_OFF        */
#define PWRCTRL_MAIN_PINID_SAIL_ERR1       (PWRCTRL_CFG_PRIVATE_KIND_SAIL_ERR1)            /* SAIL-ERR1           */
#define PWRCTRL_MAIN_PINID_SAIL_ERR2       (PWRCTRL_CFG_PRIVATE_KIND_SAIL_ERR2)            /* SAIL-ERR2           */

/* 端子モニタ取得値 */
#define PWRCTRL_MAIN_PIN_LOW               (STD_LOW)
#define PWRCTRL_MAIN_PIN_HIGH              (STD_HIGH)
#define PWRCTRL_MAIN_PIN_INVALID           (PWRCTRL_PINMONITOR_TMNL_STS_NON)

/* 端子モニタ取得処理 */
#define u1_g_PwrCtrlMainGetPinInfo         (u1_g_PwrCtrl_PinMonitor_GetPinInfo)

/*-------------------------------------------------------------------------------------------*/
/* Function Prototypes                                                                       */
/*-------------------------------------------------------------------------------------------*/
void vd_g_PwrCtrlMainBonReq( void );
void vd_g_PwrCtrlMainWakeupReq( void );
void vd_g_PwrCtrlMainBuDetReq( void );
void vd_g_PwrCtrlMainTask( void );

U1 u1_g_PwrCtrlMainShtdwnOk( void );
U1 u1_g_PwrCtrlWakeUpInfo( void );

void vd_g_PwrCtrlMainProhibitSleep( const U1 u1_a_ProhibitSleep );

#endif /* PWRCTRL_MAIN_H */

/**** End of File ****************************************************************************/
