/* PwrCtrl_Sip                                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name | PwrCtrl_Sip/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/
#ifndef PWRCTRL_SIP_H
#define PWRCTRL_SIP_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/*  Literal Definitions                                                     */
/*--------------------------------------------------------------------------*/
#define PWRCTRL_SIP_STS_NON               (0U)
#define PWRCTRL_SIP_STS_PWRON             (1U)
#define PWRCTRL_SIP_STS_RESUME            (2U)
#define PWRCTRL_SIP_STS_PWROFF            (3U)
#define PWRCTRL_SIP_STS_STANDBY           (4U)
#define PWRCTRL_SIP_STS_BUDET             (5U)
#define PWRCTRL_SIP_STS_FORCEDOFF         (6U)

/* PWM制御 */
#define     PWRCTRL_SIP_PWM_PERIOD_OFF    (0U)
#define     PWRCTRL_SIP_PWM_PERIOD_DEF    (163U)

/* 周波数：487.804878[kHz], デューティ：50[%], カウントクロック周波数：80[MHz] 分周なし */
#define     PWRCTRL_SIP_PWM_DUTYCYCLE_OFF (0x0000U)
#define     PWRCTRL_SIP_PWM_DUTYCYCLE_DEF (0x4000U)

/* SIP強制電源OFFシーケンス開始要求 */
#define PWRCTRL_SIP_FORCEDOFF_NON         (0U)
#define PWRCTRL_SIP_FORCEDOFF_SOCERR      (1U)
#define PWRCTRL_SIP_FORCEDOFF_PMICERR     (2U)
#define PWRCTRL_SIP_FORCEDOFF_DDCONV      (3U)

#define PWRCTRL_SIP_FOFF_DDCONV_OFF       (0x00U) /* SIP入力DDコン電源OFF処理未実施 */
#define PWRCTRL_SIP_FOFF_DDCONV_ON        (0x01U) /* SIP入力DDコン電源OFF処理実施   */

/* 初期化 */
void vd_g_PwrCtrlSipBonInit( void );
void vd_g_PwrCtrlSipWkupInit( void );

/* 実行要求通知関数 */
void vd_g_PwrCtrlSipOnReq( void );
void vd_g_PwrCtrlSipOnPwrOnReq( void );
void vd_g_PwrCtrlSipRsmReq( void );
void vd_g_PwrCtrlSipOffReq( void );
void vd_g_PwrCtrlSipStbyReq( void );
void vd_g_PwrCtrlSipForcedOffSTEP1Req( void );
void vd_g_PwrCtrlSipForcedOffSTEP2Req( void );
void vd_g_PwrCtrlSipForcedOffSTEP4Req( void );

/* 定期処理 */
void vd_g_PwrCtrlSipMainFunc( void );

/* 実行状態通知関数 */
U1 u1_g_PwrCtrlSipGetSts( void );
/* LOW_POWER_ON状態通知関数 */
U1 u1_g_PwrCtrlSipLowPowerOnInfo( void );
/* SIP電源強制OFF要求通知関数 */
U1 u1_g_PwrCtrlSipFOffInfo( void );
/* SIP電源強制OFF状態通知関数 */
U1 u1_g_PwrCtrlSipFOffGetSts( void );
/* EtherSW制御要求処理 */
void vd_g_PwrCtrlSipEthReqJudge( void );

#endif /* PWRCTRL_SIP_H */

/**** End of File ***********************************************************/
