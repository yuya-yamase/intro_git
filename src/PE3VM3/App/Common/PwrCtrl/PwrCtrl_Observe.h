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
#define PWRCTRL_OBSERVE_POWER_OFF  (0x00U)  /* スタンバイ要求検知 */
#define PWRCTRL_OBSERVE_POWER_ON   (0x01U)  /* 起動検知 */
/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void vd_g_PwrCtrlObserveInit( void );
void vd_g_PwrCtrlObserveOnOffTriggerDetect( void );

U1 u1_g_PwrCtrlObserveOnOffTrigger( void );
void vd_g_PwrCtrlObserveVm3StbyInfo( const U1 u1_a_ProhibitSleep );

#endif /* PWRCTRL_OBSERVE_H */

/**** End of File ***********************************************************/
