/* Mcu_Sip_Pwr                                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name | Mcu_Sip_Pwr/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

#ifndef     MCU_SIP_PWR_H
#define     MCU_SIP_PWR_H

/* 外部参照定義 */
#define     MCU_SIP_PWR_COMP     (1u)
#define     MCU_SIP_PWR_NOTCOMP  (0u)

/* PWM制御 */
#define     MCU_SIP_PWM_PERIOD_OFF     (0U)
#define     MCU_SIP_PWM_PERIOD_DEF     (163U)
/* 周波数：487.804878[kHz], デューティ：50[%], カウントクロック周波数：80[MHz] 分周なし */

#define     MCU_SIP_PWM_DUTYCYCLE_OFF  (0x0000U)
#define     MCU_SIP_PWM_DUTYCYCLE_DEF  (0x4000U)

/* 初期化 */
void Mcu_Sip_Bon_Init( void );
void Mcu_Sip_Wkup_Init( void );

/* 実行要求通知関数 */
void Mcu_Sip_PwrOn_Req( void );
void Mcu_Sip_Resume_Req( void );
void Mcu_Sip_PwrOff_Req( void );
void Mcu_Sip_Standby_Req( void );

/* 定期処理 */
void Mcu_Sip_Pwr_MainFunction( void );

/* 実行状態通知関数 */
uint8 Mcu_Sip_PwrOn_GetSts( void );
uint8 Mcu_Sip_Resume_GetSts( void );
uint8 Mcu_Sip_PwrOff_GetSts( void );
uint8 Mcu_Sip_Standby_GetSts( void );

#endif /* MCU_SIP_PWR_H */

/**** End of File ***********************************************************/
