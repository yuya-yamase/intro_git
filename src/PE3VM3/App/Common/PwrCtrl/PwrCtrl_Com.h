/* PwrCtrl_Com                                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name | PwrCtrl_Com/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/
#ifndef PWRCTRL_COM_H
#define PWRCTRL_COM_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* VM間通信用定義 */
/* スタンバイ条件成立有無用 */
#define PWRCTRL_COM_STBY_NG                 (0U)  /* スタンバイ条件非成立 */
#define PWRCTRL_COM_STBY_OK                 (1U)  /* スタンバイ条件成立 */

/* 強制スリープ条件成立有無用 */
#define PWRCTRL_COM_FSLP_OFF                (0U)  /* 強制スリープ条件非成立 */
#define PWRCTRL_COM_FSLP_ON                 (1U)  /* 強制スリープ条件成立 */

/* SoCリセット要求状態 */
#define PWRCTRL_COM_SOCRESET_NON            (0x00U) /* SoCリセット要求:未設定 */

/* STRモード状態 */
#define PWRCTRL_COM_STR_OFF                 (0U)  /* STRモードOFF */
#define PWRCTRL_COM_STR_ON                  (1U)  /* STRモードON  */

/* SIP電源再起動通知用 */
#define PWRCTRL_COM_PWRON_NOINFO            (0U)  /* SIP電源再起動なし */
#define PWRCTRL_COM_PWRON_CANCEL_START      (1U)  /* スタンバイ処理中断開始(スタンバイ処理中の起動トリガ時) */
#define PWRCTRL_COM_PWRON_CANCEL_TO_ON      (2U)  /* 電源再起動開始(スタンバイ処理中の起動トリガ時) */
#define PWRCTRL_COM_PWRON_FRCOFF_TO_ON      (3U)  /* 電源再起動開始(SIP電源強制OFF) */
#define PWRCTRL_COM_PWRON_PMAPSHOLD_TO_ON   (4U)  /* 電源再起動開始(PMA_PS_HOLD監視) */

/* SIP異常検知通知用 */
#define PWRCTRL_COM_PWRERR_NOERR            (0U)  /* 異常検知なし */
#define PWRCTRL_COM_PWRERR_FOFF_SOCERR      (1U)  /* 異常検知(SIP電源強制OFF:SOC異常系) */
#define PWRCTRL_COM_PWRERR_FOFF_PMICERR     (2U)  /* 異常検知(SIP電源強制OFF:PMIC異常系/SOCPMICリセット) */
#define PWRCTRL_COM_PWRERR_FOFF_DDERR       (3U)  /* 異常検知(SIP電源強制OFF:PMIC異常系/DDコンOFF) */
#define PWRCTRL_COM_PWRERR_PMPSAILERRN      (5U)  /* 異常検知(PM_PSAIL_ERR_N監視) */
#define PWRCTRL_COM_PWRERR_PMAPSHOLD        (6U)  /* 異常検知(PMA_PS_HOLD監視) */

/* 起動ログ計測点検知データ定義 */
#define PWRCTRL_COM_BOOTLOG_INITREQ         (0U)  /* 全データクリア要求 */
#define PWRCTRL_COM_BOOTLOG_BONREQ          (1U)  /* Soc起動時要求 */
#define PWRCTRL_COM_BOOTLOG_STRREQ          (2U)  /* STRWake時要求 */
#define PWRCTRL_COM_BOOTLOG_ETHREQ          (3U)  /* Ethリンクアップ時要求 */

#define PWRCTRL_COM_ETH_LINKUP_NODETECT     (0x00U)
#define PWRCTRL_COM_ETH_LINKUP_DETECT       (0x01U)
/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/* 共通 */
void vd_g_PwrCtrlComBonInit( void );
void vd_g_PwrCtrlComWkupInit( void );

/* 受信 */
void vd_g_PwrCtrlComRxTask( void );
U1 u1_g_PwrCtrlComRxGetVm1Stby( void );
U1 u1_g_PwrCtrlComRxGetVm2Stby( void );
U1 u1_g_PwrCtrlComRxGetForceSleep( void );
U1 u1_g_PwrCtrlComGetSoCSts( void );
U1 u1_g_PwrCtrlComGetSoCResetReq( void );
U1 u1_g_PwrCtrlComGetSTRMode( void );

/* 送信 */
void vd_g_PwrCtrlComTxTask( void );
void vd_g_PwrCtrlComTxClr( void );
void vd_g_PwrCtrlComTxSetPwrOn( const U1 u1_a_data );
void vd_g_PwrCtrlComTxSetPwrErr( const U1 u1_a_data );
void vd_g_PwrCtrlComTxSetSoCOnStart( void );
void vd_g_PwrCtrlComTxSetBootLog( const U1 u1_a_req );
void vd_g_PwrCtrlComTxClrBootLog( const U1 u1_a_req );
void vd_g_PwrCtrlComEthLinkup( const U1 u1_a_det);

#endif /* PWRCTRL_COM_H */

/**** End of File ***********************************************************/
