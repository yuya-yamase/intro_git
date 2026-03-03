/* PwrCtrl_Observe                                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name | PwrCtrl_Observe/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/
#ifndef PWRCTRL_OBSERVE_H
#define PWRCTRL_OBSERVE_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* 起動検知/スタンバイ要求検知 */
#define PWRCTRL_OBSERVE_POWER_OFF  (0x00U)  /* スタンバイ要求検知 */
#define PWRCTRL_OBSERVE_POWER_ON   (0x01U)  /* 起動検知 */
/* 異常監視 */
#define PWRCTRL_OBSERVE_OFF                     (0x00U)     /* 監視終了 */
#define PWRCTRL_OBSERVE_ON                      (0x01U)     /* 監視開始 */
#define PWRCTRL_OBSERVE_ERR_NON                 (0x0000U)   /* 異常なし */
#define PWRCTRL_OBSERVE_ERR_SAILUART            (0x0001U)   /* 5-7.SAIL UART Message監視 異常検知 */
#define PWRCTRL_OBSERVE_ERR_SAILERR             (0x0002U)   /* 5-8.SAIL-ERR監視 異常検知  */
#define PWRCTRL_OBSERVE_ERR_PMPSAIL             (0x0004U)   /* 5-9.PM_PSAIL_ERR_N監視 異常検知  */
#define PWRCTRL_OBSERVE_ERR_PMAPS               (0x0008U)   /* 5-10.PMA_PS_HOLD監視 異常検知  */
#define PWRCTRL_OBSERVE_ERR_SPI                 (0x0010U)   /* 5-11.SPI通信途絶監視 異常検知  */
#define PWRCTRL_OBSERVE_ERR_PGD_ASIL_VB         (0x0020U)   /* 5-12-1. PGOOD_ASIL_VB監視 異常検知  */
#define PWRCTRL_OBSERVE_ERR_PGD_ASIL_VSYS       (0x0040U)   /* 5-12-2. PGOOD_ASIL_VSYS監視 異常検知  */
#define PWRCTRL_OBSERVE_ERR_PGD_ASIL_VSYS_V11   (0x0080U)   /* 5-12-3. PGOOD_ASIL_VSYS(V11)監視 異常検知  */
#define PWRCTRL_OBSERVE_ERR_PGD_DIODE           (0x0100U)   /* 5-12-4. PGOOD_DIODE監視 異常検知  */
#define PWRCTRL_OBSERVE_ERR_PGD_VB              (0x0200U)   /* 5-12-5. PGOOD_VB監視 異常検知  */
#define PWRCTRL_OBSERVE_ERR_PGD_VSYS            (0x0400U)   /* 5-12-5. PGOOD_VSYS監視 異常検知  */

/* リセット要求検知 */
#define PWRCTRL_OBSERVE_RESET_NON               (0x0000U)   /* 異常なし */
#define PWRCTRL_OBSERVE_RESET_SOCNORM           (0x0001U)   /* SoCリセット要求(正常) */
#define PWRCTRL_OBSERVE_RESET_SOCERR            (0x0002U)   /* SoCリセット要求(異常) */
#define PWRCTRL_OBSERVE_RESET_CDC               (0x0004U)   /* CDCリセット要求 */
#define PWRCTRL_OBSERVE_RESET_NMDIAG            (0x0008U)   /* NMダイアグリセット */

#define PWRCTRL_OBSERVE_SOCPOWER_OFF            (PWRCTRL_COM_SOCPOWER_OFF)   /* SoC停止 */
#define PWRCTRL_OBSERVE_SOCPOWER_ON             (PWRCTRL_COM_SOCPOWER_ON)    /* SoC起動 */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void vd_g_PwrCtrlObserveInit( void );
void vd_g_PwrCtrlObserveMainFunc( void );
/* 起動検知/スタンバイ要求検知 */
U1 u1_g_PwrCtrlObserveOnOffTrigger( void );
void vd_g_PwrCtrlObserveVm3StbyInfo( const U1 u1_a_ProhibitSleep );
/* 異常監視 */
void vd_g_PwrCtrlObservePsailReq( const U1 u1_a_req );
void vd_g_PwrCtrlObservePsHoldReq( const U1 u1_a_req );
void vd_g_PwrCtrlObservePgdAsilVbLowPwrReq( const U1 u1_a_req );
void vd_g_PwrCtrlObservePgdAsilVbSysPwrReq( const U1 u1_a_req );
void vd_g_PwrCtrlObservePgdAsilVsysReq( const U1 u1_a_req );
void vd_g_PwrCtrlObservePgdAsilVsysV11Req( const U1 u1_a_req );
void vd_g_PwrCtrlObservePgdDiodeReq( const U1 u1_a_req );
void vd_g_PwrCtrlObservePgdVbReq( const U1 u1_a_req );
void vd_g_PwrCtrlObservePgdVsysReq( const U1 u1_a_req );
U2 u2_g_PwrCtrlObserveGetErrSts( void );
/* リセット要求検知 */
void vd_g_PwrCtrlObserveSoCResetErrReq( const U1 u1_a_req );
U2 u2_g_PwrCtrlObserveGetResetSts(void);

void vd_g_PwrCtrlObserveSetSocPower(const U1 u1_a_sts );

#endif /* PWRCTRL_OBSERVE_H */

/**** End of File ***********************************************************/
