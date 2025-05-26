/* PwrCtrl_Common                                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name | PwrCtrl_Common/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/
#ifndef PWRCTRL_COMMON_H
#define PWRCTRL_COMMON_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define PWRCTRL_COMMON_SYS_PWR_OFF        (0U)
#define PWRCTRL_COMMON_SYS_PWR_ON         (1U)

#define MCU_DIO_LOW                (0U)
#define MCU_DIO_HIGH               (1U)

#define PWRCTRL_COMMON_PROCESS_STEP1      (0x01)
#define PWRCTRL_COMMON_PROCESS_STEP2      (0x02)
#define PWRCTRL_COMMON_PROCESS_STEP3      (0x03)
#define PWRCTRL_COMMON_PROCESS_STEP4      (0x04)
#define PWRCTRL_COMMON_PROCESS_STEP5      (0x05)
#define PWRCTRL_COMMON_PROCESS_STEP6      (0x06)
#define PWRCTRL_COMMON_PROCESS_STEP7      (0x07)
#define PWRCTRL_COMMON_PROCESS_STEP8      (0x08)
#define PWRCTRL_COMMON_PROCESS_STEP9      (0x09)
#define PWRCTRL_COMMON_PROCESS_STEP_CMPLT (0xFF)


#if (PWRCTRL_CFG__PRIVATE_ERR_CHK == PWRCTRL_CFG__PRIVATE_ERR_CHK_ENABLE)
/* 異常系チェック用STB定義 */
extern U1 u1_s_pwrctrl_common_err_dbg_state;

#define PWRCTRL_COMMON_ERR_NON            (0U)  /* 異常系エラー未発生 */
#define PWRCTRL_COMMON_ERR_BON_STEP2_2    (1U)  /* BONシーケンス AOSS_SLEEP_ENTRY_EXIT Lo待ち異常 */
#define PWRCTRL_COMMON_ERR_BON_STEP2_3    (2U)  /* BONシーケンス POFF_COMPLETE_N Lo待ち異常 */
#define PWRCTRL_COMMON_ERR_BON_STEP4_1    (3U)  /* BONシーケンス PMA_PS_HOLD Lo待ち異常 */
#define PWRCTRL_COMMON_ERR_BON_STEP5_1    (4U)  /* BONシーケンス POFF_COMPLETE_N Hi待ち異常 */
#define PWRCTRL_COMMON_ERR_BON_STEP6_1    (5U)  /* BONシーケンス SOC_RESOUT_N Hi待ち異常 */
#define PWRCTRL_COMMON_ERR_BON_STEP6_2    (6U)  /* BONシーケンス SAIL_RESOUT_N Hi待ち異常 */
#define PWRCTRL_COMMON_ERR_BON_STEP7_1    (7U)  /* BONシーケンス PMA_PS_HOLD Hi待ち異常 */
#define PWRCTRL_COMMON_ERR_BON_MMSTBY     (8U)  /* BONシーケンス MM_STBY_N Hi待ち異常 */
#define PWRCTRL_COMMON_ERR_WAKE_AOSS_HI   (9U)  /* ウェイクアップシーケンス AOSS_SLEEP_ENTRY_EXIT Hi待ち異常 */
#define PWRCTRL_COMMON_ERR_WAKE_AOSS_LO   (10U) /* ウェイクアップシーケンス AOSS_SLEEP_ENTRY_EXIT Lo待ち異常 */
#define PWRCTRL_COMMON_ERR_WAKE_MMSTBY    (11U) /* ウェイクアップシーケンス MM_STBY_N Hi待ち異常 */
#define PWRCTRL_COMMON_ERR_SIPOFF_STEP2_1 (12U) /* SIP電源OFF&MCUスタンバイシーケンス MM_STBY_N Lo待ち異常 */
#define PWRCTRL_COMMON_ERR_SIPOFF_STEP3_1 (13U) /* SIP電源OFF&MCUスタンバイシーケンス PMA_PS_HOLD Lo待ち異常 */
#define PWRCTRL_COMMON_ERR_SIPOFF_STEP4_1 (14U) /* SIP電源OFF&MCUスタンバイシーケンス SOC_RESOUT_N Lo待ち異常 */
#define PWRCTRL_COMMON_ERR_SIPOFF_STEP4_2 (15U) /* SIP電源OFF&MCUスタンバイシーケンス SAIL_RESOUT_N Lo待ち異常 */
#define PWRCTRL_COMMON_ERR_SIPOFF_STEP4_3 (16U) /* SIP電源OFF&MCUスタンバイシーケンス POFF_COMPLETE_N Lo待ち異常 */
#define PWRCTRL_COMMON_ERR_STANDBY_MMSTBY (17U) /* スタンバイシーケンス MM_STBY_N Lo待ち異常 */
#define PWRCTRL_COMMON_ERR_STANDBY_AOSS   (18U) /* スタンバイシーケンス AOSS_SLEEP_ENTRY_EXIT Hi待ち異常 */

/* 異常系チェック用STB定義 */
#endif /* PWRCTRL_CFG__PRIVATE_ERR_CHK == PWRCTRL_CFG__PRIVATE_ERR_CHK_ENABLE */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void    vd_g_McuDevPwronWritePort( void );
void    vd_g_McuDevPwronSetPort( U1 u1_a_port_id, U1 u1_a_port_level );

#endif /* PWRCTRL_COMMON_H */

/**** End of File ***********************************************************/
