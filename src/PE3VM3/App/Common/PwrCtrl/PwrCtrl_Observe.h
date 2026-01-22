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
#define PWRCTRL_OBSERVE_OFF        (0x00U)  /* 監視終了 */
#define PWRCTRL_OBSERVE_ON         (0x01U)  /* 監視開始 */
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
void vd_s_PwrCtrlObservePgdAsilVbLowPwrReq( const U1 u1_a_req );
void vd_s_PwrCtrlObservePgdAsilVbSysPwrReq( const U1 u1_a_req );
void vd_s_PwrCtrlObservePgdAsilVsysReq( const U1 u1_a_req );
void vd_s_PwrCtrlObservePgdAsilVsysV11Req( const U1 u1_a_req );
void vd_s_PwrCtrlObservePgdDiodeReq( const U1 u1_a_req );
void vd_s_PwrCtrlObservePgdVbReq( const U1 u1_a_req );
void vd_s_PwrCtrlObservePgdVsysReq( const U1 u1_a_req );
U2 u2_g_PwrCtrlObserveGetErrSts( void );

#endif /* PWRCTRL_OBSERVE_H */

/**** End of File ***********************************************************/
