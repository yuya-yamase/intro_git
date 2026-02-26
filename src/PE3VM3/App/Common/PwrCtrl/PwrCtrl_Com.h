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
#define PWRCTRL_COM_SOCRESET_SOCNORM        (0x01U) /* SoCリセット要求:SoCリセット要求(正常) */
#define PWRCTRL_COM_SOCRESET_SOCERR         (0x02U) /* SoCリセット要求:SoCリセット要求(異常) */
#define PWRCTRL_COM_SOCRESET_CDC            (0x03U) /* SoCリセット要求:CDCリセット要求 */

/* STRモード状態 */
#define PWRCTRL_COM_STR_OFF                 (0U)  /* STRモードOFF */
#define PWRCTRL_COM_STR_ON                  (1U)  /* STRモードON  */

/* SPI通信途絶監視結果 */
#define PWRCTRL_COM_SPIFAIL_OK              (0U)  /* 正常 */
#define PWRCTRL_COM_SPIFAIL_NG              (1U)  /* 異常 */

/* NMダイアグリセット */
#define PWRCTRL_COM_NMDIAGRESET_NON         (0U)  /* 要求無し */
#define PWRCTRL_COM_NMDIAGRESET_REQ         (1U)  /* NMダイアグリセット要求 */

/* SIP電源再起動通知用 */
#define PWRCTRL_COM_PWRON_NOINFO            (0U)  /* SIP電源再起動なし */
#define PWRCTRL_COM_PWRON_CANCEL_START      (1U)  /* スタンバイ処理中断開始(スタンバイ処理中の起動トリガ時) */
#define PWRCTRL_COM_PWRON_CANCEL_TO_ON      (2U)  /* 電源再起動開始(スタンバイ処理中の起動トリガ時) */
#define PWRCTRL_COM_PWRON_FRCOFF_TO_ON      (3U)  /* 電源再起動開始(SIP電源強制OFF) */
#define PWRCTRL_COM_PWRON_PMAPSHOLD_TO_ON   (4U)  /* 電源再起動開始(PMA_PS_HOLD監視) */
#define PWRCTRL_COM_PWRON_SAILERR_TO_ON     (5U)  /* 電源再起動開始(SAIL-ERR監視) */

/* SIP異常検知通知用 */
#define PWRCTRL_COM_PWRERR_NOERR            (0U)  /* 異常検知なし */
#define PWRCTRL_COM_PWRERR_FOFF_SOCERR      (1U)  /* 異常検知(SIP電源強制OFF:SOC異常系) */
#define PWRCTRL_COM_PWRERR_FOFF_PMICERR     (2U)  /* 異常検知(SIP電源強制OFF:PMIC異常系/SOCPMICリセット) */
#define PWRCTRL_COM_PWRERR_FOFF_DDERR       (3U)  /* 異常検知(SIP電源強制OFF:PMIC異常系/DDコンOFF) */
#define PWRCTRL_COM_PWRERR_SAILERR          (4U)  /* 異常検知(SAIL-ERR監視) */
#define PWRCTRL_COM_PWRERR_PMPSAILERRN      (5U)  /* 異常検知(PM_PSAIL_ERR_N監視) */
#define PWRCTRL_COM_PWRERR_PMAPSHOLD        (6U)  /* 異常検知(PMA_PS_HOLD監視) */

/* 起動ログ計測点検知データ定義 */
#define PWRCTRL_COM_BOOTLOG_INITREQ         (0U)  /* 全データクリア要求 */
#define PWRCTRL_COM_BOOTLOG_BONREQ          (1U)  /* Soc起動時要求 */
#define PWRCTRL_COM_BOOTLOG_STRREQ          (2U)  /* STRWake時要求 */
#define PWRCTRL_COM_BOOTLOG_ETHREQ          (3U)  /* Ethリンクアップ時要求 */

#define PWRCTRL_COM_ETH_LINKUP_NODETECT     (0x00U)
#define PWRCTRL_COM_ETH_LINKUP_DETECT       (0x01U)

/* SoC起動状態 */
#define PWRCTRL_COM_SOCPOWER_OFF            (0U)  /* SoC停止 */
#define PWRCTRL_COM_SOCPOWER_ON             (1U)  /* SoC起動 */

/* 起動条件通知 */
#define PWRCTRL_COM_SOCWKUP_NON             (0U)  /* 未設定 */
#define PWRCTRL_COM_SOCWKUP_NORM            (1U)  /* SoC正常起動 */
#define PWRCTRL_COM_SOCWKUP_STR             (2U)  /* SoC正常起動(STR起動) */
#define PWRCTRL_COM_SOCWKUP_FULLINIT        (3U)  /* SoC正常起動(完全初期化要因) */
#define PWRCTRL_COM_SOCWKUP_SUSPENDCANCEL   (4U)  /* SoC瞬断起動(サスペンド処置中にwkup) */
#define PWRCTRL_COM_SOCWKUP_SHUTDOWNCANCEL  (5U)  /* SoC瞬断起動(シャットダウン処置中にwkup) */
#define PWRCTRL_COM_SOCWKUP_SOCERR          (6U)  /* SoC異常起動(SoC異常) */
#define PWRCTRL_COM_SOCWKUP_PMICERR         (7U)  /* SoC異常起動(PMIC異常) */
#define PWRCTRL_COM_SOCWKUP_SAILERR         (8U)  /* SoC異常起動(SAIL異常) */
#define PWRCTRL_COM_SOCWKUP_CDCNORM         (9U)  /* CDC正常リセット */
#define PWRCTRL_COM_SOCWKUP_CDCERR          (10U) /* CDC異常リセット */
#define PWRCTRL_COM_SOCWKUP_SUSPENDERR      (11U) /* SoC異常起動(SoC検知・サスペンド中) */
#define PWRCTRL_COM_SOCWKUP_RESUMEERR       (12U) /* SoC異常起動(SoC検知・レジューム中) */

/* 起動条件通知 */
#define PWRCTRL_COM_USRRSTMASK_OFF          (0U)  /* 未設定 */
#define PWRCTRL_COM_USRRSTMASK_ON           (1U)  /* ユーザーリセット抑止区間 */

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
U1 u1_g_PwrCtrlComGetSpiFail( void );
U1 u1_g_PwrCtrlComGetNMDiagReset( void );

/* 送信 */
void vd_g_PwrCtrlComTxTask( void );
void vd_g_PwrCtrlComTxClr( void );
void vd_g_PwrCtrlComTxSetPwrOn( const U1 u1_a_data );
void vd_g_PwrCtrlComTxSetPwrErr( const U1 u1_a_data );
void vd_g_PwrCtrlComTxSetSoCOnStart( void );
void vd_g_PwrCtrlComTxSetBootLog( const U1 u1_a_req );
void vd_g_PwrCtrlComTxClrBootLog( const U1 u1_a_req );
void vd_g_PwrCtrlComTxSetSoCPower( const U1 u1_a_data );
void vd_g_PwrCtrlComTxSetSoCWkupCond( const U1 u1_a_data );
void vd_g_PwrCtrlComTxSetUsrRstMask( const U1 u1_a_data );
void vd_g_PwrCtrlComEthLinkup( const U1 u1_a_det );

#endif /* PWRCTRL_COM_H */

/**** End of File ***********************************************************/
