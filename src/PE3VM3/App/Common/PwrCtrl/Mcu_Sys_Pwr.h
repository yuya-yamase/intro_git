/* Mcu_Sys_Pwr                                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name | Mcu_Sys_Pwr/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

#ifndef MCU_SYS_PWR_H
#define MCU_SYS_PWR_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "pwm_drv.h"
#include "Mcu_PwrCtrl_Port.h"

/*--------------------------------------------------------------------------*/
/*  Literal Definitions                                                     */
/*--------------------------------------------------------------------------*/

/* PWM制御 */
#define     MCU_SYS_PWM_PERIOD_OFF          (0U)
/* 周波数：487.804878[kHz], デューティ：50[%], カウントクロック周波数：80[MHz] 分周なし */
#define     MCU_SYS_PWM_PERIOD              (164U)		/* 80MHz, (1/487.805)*80000 = 163.99[counts] */
#define 	MCU_SYS_PWM_DUTYCYCLE(i)        ((uint16)(((uint32)(i) * (uint32)PWM_DRV_DUTY_MAX) / (uint32)10000U))

/* SYS電源ON ウェイトタイム設定 */
/* 待ち時間は中間値(TYP)を設定 "-"であればMINを指定 */
#define     MCU_WAIT_DISCHARGE_TIME         (50U / MCU_SYS_TASK_TIME)
#define     MCU_WAIT_BU_DD_MODE_TIME        (0U                     )
#define     MCU_WAIT_BOOST_DCDC_TIME        (0U                     )
#define     MCU_WAIT_BOOST_ASIL_DCDC_TIME   (0U                     )
#define     MCU_WAIT_DD_FREQ_TIME           (5U  / MCU_SYS_TASK_TIME)
#define     MCU_WAIT_BOOST_ASIL_FREQ_TIME   (5U  / MCU_SYS_TASK_TIME)
#define     MCU_WAIT_V33_PERI_TIME          (5U  / MCU_SYS_TASK_TIME)
#define     MCU_WAIT_V33_ASIL_TIME          (5U  / MCU_SYS_TASK_TIME)
#define     MCU_WAIT_V18_TIME               (15U / MCU_SYS_TASK_TIME)
#define     MCU_WAIT_V18_ASIL_TIME          (15U / MCU_SYS_TASK_TIME)
#define     MCU_WAIT_AUDIO_TIME             (15U / MCU_SYS_TASK_TIME)
#define     MCU_WAIT_V11_ASIL_TIME          (15U / MCU_SYS_TASK_TIME)
#define     MCU_WAIT_EIZO_TIME              (15U / MCU_SYS_TASK_TIME)

/* SYS電源OFF ウェイトタイム設定 */
/* 仕様から全端子共通の時間設定のためウェイトタイム設定も共通とする */
#define     MCU_WAIT_SYSOFF                 (0U                     )

/* カウンタ最大値 */
#define     MCU_SYS_COUNTTIME_FIN               (0xFFFFFFFFU)

/* SYS電源ON/OFF 現在起動ステップ状態管理 */
#define     MCU_SYS_STEP1             (1U)
#define     MCU_SYS_STEP2             (2U)
#define     MCU_SYS_STEP3             (3U)
#define     MCU_SYS_STEP4             (4U)
#define     MCU_SYS_STEP_OK           (5U)

/* CentralからのSYS電源ON/OFF要求トリガ */
#define     MCU_SYS_CENTRAL_NON             (0U)
#define     MCU_SYS_CENTRAL_ON              (1U)

/* GVIFリンク監視用 */
#define     MCU_GVIF_LNK_ACTIVE       (1U)     /* リンク確立 */
#define     MCU_GVIF_LNK_TIMEOUT      (5000U)  /* 起動からリンク確立までの時間要件 5000ms */
#define     MCU_GVIF_RESTRT_STS_1ST   (0U)     /* GVIFリンク用状態 初回 */
#define     MCU_GVIF_RESTRT_STS_2ND   (1U)     /* GVIFリンク用状態 2回目以降 */
#define     MCU_GVIF_RESTRT_STS_CMP   (2U)     /* GVIFリンク用状態 完了 */



/*--------------------------------------------------------------------------*/
/*  Function Prototypes                                                     */
/*--------------------------------------------------------------------------*/
void    Mcu_Sys_PwrOn_Init( void );
void    Mcu_Sys_PwrOn_MainFunction( void );

void    Mcu_Sys_PwrOn_Start( void );                /* SYS電源ON要求 */
void    Mcu_Sys_PwrOff_Start( void );               /* SYS電源OFF要求 */
uint8   Mcu_Sys_PwrOn_GetStep( void );
uint8   Mcu_Sys_PwrOn_GetSts( void );               /* SYS電源ONシーケンス状態問い合わせ */
uint8   Mcu_Sys_PwrOff_GetSts( void );              /* SYS電源OFFシーケンス状態問い合わせ */
uint8   Mcu_Sys_Shtdwn_GetSts( void );              /* SYS系デバイス終了状態問い合わせ */

void    Mcu_Dev_Pwron( void );

#endif /* MCU_SYS_PWR_H */

/**** End of File ***********************************************************/
