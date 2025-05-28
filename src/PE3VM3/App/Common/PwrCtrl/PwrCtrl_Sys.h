/* PwrCtrl_Sys                                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name | PwrCtrl_Sys/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/
#ifndef PWRCTRL_SYS_H
#define PWRCTRL_SYS_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/*  Literal Definitions                                                     */
/*--------------------------------------------------------------------------*/

/* PWM制御 */
#define     PWRCTRL_SYS_PWM_PERIOD_OFF          (0U)
/* 周波数：487.804878[kHz], デューティ：50[%], カウントクロック周波数：80[MHz] 分周なし */
#define     PWRCTRL_SYS_PWM_PERIOD              (163U)		/* 80MHz, (1/487.805)*80000 = 163.99[counts] */
#define     PWRCTRL_SYS_PWM_DUTYCYCLE(i)        ((U2)(((U4)(i) * (U4)PWM_DRV_DUTY_MAX) / (U4)10000U))

/* SYS電源ON ウェイトタイム設定 */
/* 待ち時間は中間値(TYP)を設定 "-"であればMINを指定 */
#define     PWRCTRL_SYS_WAIT_TIME_INIT              (0U)
#define     PWRCTRL_SYS_WAIT_DISCHARGE_TIME         (50U / PWRCTRL_CFG_TASK_TIME)
#define     PWRCTRL_SYS_WAIT_BU_DD_MODE_TIME        (0U)
#define     PWRCTRL_SYS_WAIT_BOOST_DCDC_TIME        (0U)
#define     PWRCTRL_SYS_WAIT_BOOST_ASIL_DCDC_TIME   (0U)
#define     PWRCTRL_SYS_WAIT_DD_FREQ_TIME           (5U  / PWRCTRL_CFG_TASK_TIME)
#define     PWRCTRL_SYS_WAIT_BOOST_ASIL_FREQ_TIME   (5U  / PWRCTRL_CFG_TASK_TIME)
#define     PWRCTRL_SYS_WAIT_V33_PERI_TIME          (5U  / PWRCTRL_CFG_TASK_TIME)
#define     PWRCTRL_SYS_WAIT_V33_ASIL_TIME          (5U  / PWRCTRL_CFG_TASK_TIME)
#define     PWRCTRL_SYS_WAIT_V18_TIME               (15U / PWRCTRL_CFG_TASK_TIME)
#define     PWRCTRL_SYS_WAIT_V18_ASIL_TIME          (15U / PWRCTRL_CFG_TASK_TIME)
#define     PWRCTRL_SYS_WAIT_AUDIO_TIME             (15U / PWRCTRL_CFG_TASK_TIME)
#define     PWRCTRL_SYS_WAIT_V11_ASIL_TIME          (15U / PWRCTRL_CFG_TASK_TIME)
#define     PWRCTRL_SYS_WAIT_EIZO_TIME              (15U / PWRCTRL_CFG_TASK_TIME)

/* SYS電源OFF ウェイトタイム設定 */
/* 仕様から全端子共通の時間設定のためウェイトタイム設定も共通とする */
#define     PWRCTRL_SYS_WAIT_SYSOFF                 (0U)

/* カウンタ最大値 */
#define     PWRCTRL_SYS_COUNTTIME_FIN           (0xFFFFFFFFU)

/* SYS電源ON/OFF要求トリガ */
#define     PWRCTRL_SYS_NON           (0U)
#define     PWRCTRL_SYS_OFF           (1U)
#define     PWRCTRL_SYS_ON            (2U)

/* GVIFリンク監視用 */
#define     MCU_GVIF_LNK_ACTIVE       (1U)     /* リンク確立 */
#define     MCU_GVIF_LNK_TIMEOUT      (5000U)  /* 起動からリンク確立までの時間要件 5000ms */
#define     MCU_GVIF_RESTRT_STS_1ST   (0U)     /* GVIFリンク用状態 初回 */
#define     MCU_GVIF_RESTRT_STS_2ND   (1U)     /* GVIFリンク用状態 2回目以降 */
#define     MCU_GVIF_RESTRT_STS_CMP   (2U)     /* GVIFリンク用状態 完了 */

/*--------------------------------------------------------------------------*/
/*  Function Prototypes                                                     */
/*--------------------------------------------------------------------------*/
void vd_g_PwrCtrlSysInit( void );
void vd_g_PwrCtrlSysPwrOnMainFunction( void );
void vd_g_PwrCtrlSysPwrOffMainFunction( void );

void vd_g_PwrCtrlSysPwrOnStart( void );                /* SYS電源ON要求 */
void vd_g_PwrCtrlSysPwrOffStart( void );               /* SYS電源OFF要求 */
U1   u1_g_PwrCtrlSysGetSts( void );                    /* SYS電源シーケンス状態問い合わせ */
U1   u1_g_PwrCtrlSysShtdwnGetSts( void );              /* SYS系デバイス終了状態問い合わせ */

void Mcu_Dev_Pwron( void );

#endif /* PWRCTRL_SYS_H */

/**** End of File ***********************************************************/
