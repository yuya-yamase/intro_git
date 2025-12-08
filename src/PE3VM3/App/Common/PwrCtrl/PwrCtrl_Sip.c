/* PwrCtrl_Sip_c_v1-0-0                                                     */
/****************************************************************************/
/* Copyright (C) 2023 Denso Co.,Ltd. All rights reserved.                   */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | PwrCtrl_Sip/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "PwrCtrl_cfg_private.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* SIP制御共通定義 */
#define PWRCTRL_SIP_TIME_INIT              (0x00000000U)
#define PWRCTRL_SIP_TIME_INVALID           (0xFFFFFFFFU)
/* EtherSW要求通知制御定義 */
#define PWRCTRL_ETH_REQ_NON                (0U)                              /* EtherSW要求無し */
#define PWRCTRL_ETH_REQ_OFF                (1U)                              /* EtherSW終了要求 */
#define PWRCTRL_ETH_REQ_ON                 (2U)                              /* EtherSW起動要求 */

/* SIP電源ON用定義 */
#define PWRCTRL_SIP_ON_T_VB33_SIP_ON       (0U)                              /* tVB33-SIP-ON:0ms                                                     */
#define PWRCTRL_SIP_ON_T_LOW_POWER_ON_LO   (0U)                              /* tLOW-POWER-ON_LO:0ms                                                 */
#define PWRCTRL_SIP_ON_T_VB33_SIP_FREQ_LO  (0U)                              /* tVB33-SIP-FREQ_LO:0ms                                                */
#define PWRCTRL_SIP_ON_T_PMPWREN_STEP1_LO  (0U)                              /* tPM_PWR_EN_N_LO:0ms                                                  */
#define PWRCTRL_SIP_ON_T_PMICFASTPOFF_LO   (0U)                              /* tPMIC_FAST_POFF_EN_N_LO:0ms                                          */
#define PWRCTRL_SIP_ON_T_MM_OFF_REQ        (0U)                              /* tMM-OFF-REQ_LO:0ms                                                   */
#define PWRCTRL_SIP_ON_T_LOW_POWER_ON_HI   ( 15U / PWRCTRL_CFG_TASK_TIME)    /* tLOW-POWER-ON_HI:15ms                                                */
#define PWRCTRL_SIP_ON_T_VB33_SIP_FREQ     (  5U / PWRCTRL_CFG_TASK_TIME)    /* tVB33-SIP-FREQ:5ms                                                   */
#define PWRCTRL_SIP_ON_T_AOSS              ( 35U / PWRCTRL_CFG_TASK_TIME)    /* Wait time:35ms                                                       */
#define PWRCTRL_SIP_ON_T_POFF_COMPLETE_N   ( 35U / PWRCTRL_CFG_TASK_TIME)    /* Wait time:35ms                                                       */
#define PWRCTRL_SIP_ON_T_PM_PWR_EN_N_LO    (  5U / PWRCTRL_CFG_TASK_TIME)    /* tPM_PWR_EN_N_LO:5ms                                                  */
#define PWRCTRL_SIP_ON_T_PMICFASTPOFF      (  5U / PWRCTRL_CFG_TASK_TIME)    /* tPMIC_FAST_POFF_EN_N:5ms                                             */
#define PWRCTRL_SIP_ON_T_MM_SUSPEND_REQ_N  (  5U / PWRCTRL_CFG_TASK_TIME)    /* tMM_SUSPEND_REQ_N:5ms                                                */
#define PWRCTRL_SIP_ON_T_STR_WAKE          (  5U / PWRCTRL_CFG_TASK_TIME)    /* tSTR_WAKE:5ms                                                        */
#define PWRCTRL_SIP_ON_T_PM_PWR_EN_N_HI_P2 (  5U / PWRCTRL_CFG_TASK_TIME)    /* tPM_PWR_EN_N_HI_P2:5ms                                               */
#define PWRCTRL_SIP_ON_T_PMA_PS_HOLD_INIT  (0U)                              /* PMA_PS_HOLD:0ms                                                      */
#define PWRCTRL_SIP_ON_T_POFF_COMP_VAL     (0U)                              /* POFF_COMPLETE_N:0ms                                                  */
#define PWRCTRL_SIP_ON_T_SOC_RESOUT_N      (0U)                              /* SOC_RESOUT_N:0ms                                                     */
#define PWRCTRL_SIP_ON_T_SAIL_RESOUT_N     (0U)                              /* SAIL_RESOUT_N:0ms                                                    */
#define PWRCTRL_SIP_ON_T_PMA_PS_HOLD_VAL   (0U)                              /* PMA_PS_HOLD:0ms                                                      */
#define PWRCTRL_SIP_ON_T_PM_PWR_EN_N_ELPSD ( 50U / PWRCTRL_CFG_TASK_TIME)    /* PN_PWR_EN_N=Lo→Hiの必要時間:50ms                                    */
#define PWRCTRL_SIP_ON_WAIT_POFFCOMP_AOSS  ( 50U / PWRCTRL_CFG_TASK_TIME)    /* POFF_COMPLETE_N =Lo & AOSS_SLEEP_ENTRY_EXIT =Loチェック待機時間:50ms */
#define PWRCTRL_SIP_ON_WAIT_PMA_PS_HOLD_LO (300U / PWRCTRL_CFG_TASK_TIME)    /* PMA_PS_HOLD =Loチェック待機時間:300ms                                */
#define PWRCTRL_SIP_ON_WAIT_POFFCOMP       (300U / PWRCTRL_CFG_TASK_TIME)    /* POFF_COMPLETE_N =Hiチェック待機時間:300ms                            */
#define PWRCTRL_SIP_ON_WAIT_SOC_SAIL_RES   (200U / PWRCTRL_CFG_TASK_TIME)    /* SOC_RESOUT_N =Hi & SAIL_RESOUT_N =Hiチェック待機時間:200ms           */
#define PWRCTRL_SIP_ON_WAIT_PMA_PS_HOLD_HI (200U / PWRCTRL_CFG_TASK_TIME)    /* PMA_PS_HOLD =Hiチェック待機時間:200ms                                */

/* SIPレジューム用定義 */
#define PWRCTRL_SIP_RSM_T_LOW_POWER_ON     (0U)                              /* tLOW-POWER-ON_HI:0ms                                                 */
#define PWRCTRL_SIP_RSM_T_VB33_SIP_FREQ    (5U / PWRCTRL_CFG_TASK_TIME)      /* tVB33-SIP-FREQ:5ms                                                   */
#define PWRCTRL_SIP_RSM_T_MM_SUSPEND_REQ_N (5U / PWRCTRL_CFG_TASK_TIME)      /* tMM_SUSPEND_REQ_N:5ms                                                */
#define PWRCTRL_SIP_RSM_T_STR_WAKE         (5U / PWRCTRL_CFG_TASK_TIME)      /* tSTR_WAKE:5ms                                                        */

/* SIP電源OFF用処理 */
#define PWRCTRL_SIP_OFF_T_MM_OFF_REQ_HI    (0U)                              /* tMM_OFF_REQ_HI:0ms                                                   */
#define PWRCTRL_SIP_OFF_T_MM_STBY          (0U)                              /* MM_STBY_N:0ms                                                        */
#define PWRCTRL_SIP_OFF_T_PMA_PS_HOLD      (0U)                              /* PMA_PS_HOLD:0ms                                                      */
#define PWRCTRL_SIP_OFF_T_SOC_RESOUT_N     (0U)                              /* SOC_RESOUT_N:0ms                                                     */
#define PWRCTRL_SIP_OFF_T_SAIL_RESOUT_N    (0U)                              /* SAIL_RESOUT_N:0ms                                                    */
#define PWRCTRL_SIP_OFF_T_POFF_COMPLETE_N  (0U)                              /* POFF_COMPLETE_N:0ms                                                  */
#define PWRCTRL_SIP_OFF_T_VB33_SIP_FREQ    (     5U / PWRCTRL_CFG_TASK_TIME) /* tVB33-SIP-FREQ:5ms                                                   */
#define PWRCTRL_SIP_OFF_T_VB33_SIP_ON      (     5U / PWRCTRL_CFG_TASK_TIME) /* tVB33-SIP-ON:5ms                                                     */
#define PWRCTRL_SIP_OFF_T_LOW_POWER_ON     (     5U / PWRCTRL_CFG_TASK_TIME) /* tLOW-POWER-ON:5ms                                                    */
#define PWRCTRL_SIP_OFF_T_PM_PWR_EN_N      (     5U / PWRCTRL_CFG_TASK_TIME) /* tPM_PWR_EN_N:5ms                                                     */
#define PWRCTRL_SIP_OFF_T_PM_RESIN         (     5U / PWRCTRL_CFG_TASK_TIME) /* tPM_RESIN:5ms                                                        */
#define PWRCTRL_SIP_OFF_T_PMICFASTPOFF     (     5U / PWRCTRL_CFG_TASK_TIME) /* tPMIC_FAST_POFF_EN_N:5ms                                             */
#define PWRCTRL_SIP_OFF_T_MM_SUSPEND_REQ_N (     5U / PWRCTRL_CFG_TASK_TIME) /* tMM_SUSPEND_REQ_N:5ms                                                */
#define PWRCTRL_SIP_OFF_T_STR_WAKE         (     5U / PWRCTRL_CFG_TASK_TIME) /* tSTR_WAKE:5ms                                                        */
#define PWRCTRL_SIP_OFF_T_MM_OFF_REQ_LO    (     5U / PWRCTRL_CFG_TASK_TIME) /* tMM_OFF_REQ_LO:5ms                                                   */
#define PWRCTRL_SIP_OFF_WAIT_MM_STBY       (100000U / PWRCTRL_CFG_TASK_TIME) /* MM_STBY_N =Loチェック待機時間:100秒                                    */
#define PWRCTRL_SIP_OFF_WAIT_PMA_PS_HOLD   (  3000U / PWRCTRL_CFG_TASK_TIME) /* PMA_PS_HOLD =Loチェック待機時間:3秒                                  */
#define PWRCTRL_SIP_OFF_WAIT_SOC_RESOUT_N  (   100U / PWRCTRL_CFG_TASK_TIME) /* SOC_RESOUT_N    =Loチェック待機時間:100ms                            */
#define PWRCTRL_SIP_OFF_WAIT_SAIL_RESOUT_N (   100U / PWRCTRL_CFG_TASK_TIME) /* SAIL_RESOUT_N   =Loチェック待機時間:100ms                            */
#define PWRCTRL_SIP_OFF_WAIT_POFF_COMP     (   100U / PWRCTRL_CFG_TASK_TIME) /* POFF_COMPLETE_N =Loチェック待機時間:100ms                            */

/* SIPスタンバイ用処理 */
#define PWRCTRL_SIP_STBY_T_MM_SUSPEND_REQ  (0U)                              /* tMM_SUSPEND_REQ_N:0ms                                                */
#define PWRCTRL_SIP_STBY_T_STR_WAKE        (0U)                              /* tSTR_WAKE:0ms                                                        */
#define PWRCTRL_SIP_STBY_T_MM_STBY         (0U)                              /* MM_STBY_N:0ms                                                        */
#define PWRCTRL_SIP_STBY_T_AOSS            (0U)                              /* AOSS_SLEEP_ENTRY_EXIT:0ms                                            */
#define PWRCTRL_SIP_STBY_T_VB33_SIP_FREQ   (0U)                              /* tVB33-SIP-FREQ:0ms                                                   */
#define PWRCTRL_SIP_STBY_T_LOW_POWER_ON    (     5U / PWRCTRL_CFG_TASK_TIME) /* tLOW-POWER-ON:5ms                                                    */
#define PWRCTRL_SIP_STBY_WAIT_MM_STBY      (100000U / PWRCTRL_CFG_TASK_TIME) /* MM_STBY_N =Loチェック待機時間:100秒                                  */
#define PWRCTRL_SIP_STBY_WAIT_AOSS         (  5000U / PWRCTRL_CFG_TASK_TIME) /* AOSS_SLEEP_ENTRY_EXIT =Hiチェック待機時間:5秒                      */

/* SIP電源強制OFF用処理 */
#define PWRCTRL_SIP_FOFF_T_PMICFASTPOFF    (0U)                              /* tPMIC_FAST_POFF_EN_N:0ms                                             */
#define PWRCTRL_SIP_FOFF_T_POFF_COMPLETE_N (0U)                              /* POFF_COMPLETE_N:0ms                                                  */
#define PWRCTRL_SIP_FOFF_T_PMRESIN_HI      (0U)                              /* tPM_RESIN:0ms                                                        */
#define PWRCTRL_SIP_FOFF_T_PMRESIN_LO      (  10U / PWRCTRL_CFG_TASK_TIME)   /* tPM_RESIN:10ms                                                       */
#define PWRCTRL_SIP_FOFF_T_VB33_SIP_FREQ   (0U)                              /* tVB33-SIP-FREQ:0ms                                                   */
#define PWRCTRL_SIP_FOFF_T_LOW_POWER_ON    (   5U / PWRCTRL_CFG_TASK_TIME)   /* tLOW-POWER-ON:5ms                                                    */
#define PWRCTRL_SIP_FOFF_T_VB33_SIP_ON     (0U)                              /* tVB33-SIP-ON:0ms                                                     */
#define PWRCTRL_SIP_FOFF_T_PM_PWR_EN_N     (0U)                              /* tPM_PWR_EN_N:0ms                                                     */
#define PWRCTRL_SIP_FOFF_T_PM_RESIN_LO2    (0U)                              /* tPM_RESIN:0ms                                                        */
#define PWRCTRL_SIP_FOFF_T_PMICFASTPOFF_P2 (0U)                              /* tPMIC_FAST_POFF_EN_N:0ms                                             */
#define PWRCTRL_SIP_FOFF_T_MM_SUSPEND_REQ  (0U)                              /* tMM_SUSPEND_REQ_N:0ms                                                */
#define PWRCTRL_SIP_FOFF_T_STR_WAKE        (0U)                              /* tSTR_WAKE:0ms                                                        */
#define PWRCTRL_SIP_FOFF_T_MM_OFF_REQ_LO   (0U)                              /* tMM_OFF_REQ_LO:0ms                                                   */
#define PWRCTRL_SIP_FOFF_T_DDCONV_OFF_WAIT (  10U / PWRCTRL_CFG_TASK_TIME)   /* DDコンに対するOFF区間確保時間:10ms                                   */
#define PWRCTRL_SIP_FOFF_WAIT_POFF_COMP    ( 100U / PWRCTRL_CFG_TASK_TIME)   /* POFF_COMPLETE_N =Loチェック待機時間:100ms                            */
#define PWRCTRL_SIP_FOFF_WAIT_POFF_COMP_P2 (5000U / PWRCTRL_CFG_TASK_TIME)   /* POFF_COMPLETE_N =Loチェック待機時間:5秒                              */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/* SIP制御共通処理 */
static void vd_s_PwrCtrl_Sip_DioWriteCheck(U4 * const u4_a_counter , const U1 u1_a_ontime ,const Dio_ChannelType u2_a_ChannelId , const Dio_LevelType u1_a_Level);
static void vd_s_PwrCtrl_Sip_DioReadCheck(U4 * const u4_a_counter , U4 * const u4_a_wait_counter ,const U1 u1_a_ontime ,const U1 u1_a_PinID , const Dio_LevelType u1_a_Level);
static void vd_s_PwrCtrl_Sip_DioFreqAct(U4 * const u4_a_counter , const U1 u1_a_ontime ,const U1 u1_a_PWM_CH, const U2 u2_a_PERIOD, const U2 u2_a_DUTY);

/* LOW_POWER_ON状態要求 */
static U1 u1_s_PwrCtrl_Sip_LOW_POWER_ON_Sts;

/* SIP電源強制OFF要求 */
static U1 u1_s_PwrCtrl_Sip_FOff_Sts;

/* SIP入力DDコン電源OFF処理実施要否通知 */
static U1 u1_s_PwrCtrl_Sip_DDConvFlag;

/* EtherSW要求通知制御開始要求 */
static U1 u1_s_PwrCtrl_Sip_EthReq_Sts;

/* ON/OFFシーケンス起動要求 */
static U1 u1_s_PwrCtrl_Sip_Pwr_Sts;

/* WAKEUP-STAT端子状態 */
static U1 u1_s_PwrCtrl_Sip_WAKEUP_STAT1;
static U1 u1_s_PwrCtrl_Sip_WAKEUP_STAT2;
static U1 u1_s_PwrCtrl_Sip_WAKEUP_STAT3;

static U1 u1_s_PwrCtrl_Sip_On_Step;
static U4 u4_s_PwrCtrl_Sip_On_VB33SIPON_Tim;
static U4 u4_s_PwrCtrl_Sip_On_LOPWON_S1_Tim;
static U4 u4_s_PwrCtrl_Sip_On_SIPFRQ_S1_Tim;
static U4 u4_s_PwrCtrl_Sip_On_AOSS_Tim;
static U4 u4_s_PwrCtrl_Sip_On_POFF_COMPLETE_N_Init_Tim;
static U4 u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Step1_Tim;
static U4 u4_s_PwrCtrl_Sip_On_PMIC_FAST_POFF_EN_N_Step1_Tim;
static U4 u4_s_PwrCtrl_Sip_On_MM_OFF_REQ_Step1_Tim;
static U4 u4_s_PwrCtrl_Sip_On_LOW_POWER_ON_Step2_Tim;
static U4 u4_s_PwrCtrl_Sip_On_VB33_SIP_FREQ_Step2_Tim;
static U4 u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Step3_Tim;
static U4 u4_s_PwrCtrl_Sip_On_PMIC_FAST_POFF_EN_N_Step3_Tim;
static U4 u4_s_PwrCtrl_Sip_On_MM_SUSPEND_REQ_N_Tim;
static U4 u4_s_PwrCtrl_Sip_On_STR_WAKE_Tim;
static U4 u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Init_Tim;
static U4 u4_s_PwrCtrl_Sip_On_POFF_COMPLETE_N_Chk_Tim;
static U4 u4_s_PwrCtrl_Sip_On_SOC_RESOUT_N_Tim;
static U4 u4_s_PwrCtrl_Sip_On_SAIL_RESOUT_N_Tim;
static U4 u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Chk_Tim;
static U4 u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Lo_ElapsedTim;
static U4 u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Step8_Tim;
static U4 u4_s_PwrCtrl_Sip_On_AOSS_Wait_Tim;
static U4 u4_s_PwrCtrl_Sip_On_POFFCOMP_Wait_Tim;
static U4 u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Wait_Tim;
static U4 u4_s_PwrCtrl_Sip_On_SOC_RESOUT_Wait_Tim;
static U4 u4_s_PwrCtrl_Sip_On_SAIL_RESOUT_Wait_Tim;

static U1 u1_s_PwrCtrl_Sip_Rsm_Step;
static U4 u4_s_PwrCtrl_Sip_Rsm_LOW_POWER_ON_Tim;
static U4 u4_s_PwrCtrl_Sip_Rsm_VB33_SIP_FREQ_Tim;
static U4 u4_s_PwrCtrl_Sip_Rsm_MM_SUSPEND_REQ_N_Tim;
static U4 u4_s_PwrCtrl_Sip_Rsm_STR_WAKE_Tim;

static U1 u1_s_PwrCtrl_Sip_Off_Step;
static U4 u4_s_PwrCtrl_Sip_Off_MM_OFF_REQ_Step1_Tim;
static U4 u4_s_PwrCtrl_Sip_Off_MM_STBY_N_Chk_Tim;
static U4 u4_s_PwrCtrl_Sip_Off_PMA_PS_HOLD_Chk_Tim;
static U4 u4_s_PwrCtrl_Sip_Off_SOC_RESOUT_N_Chk_Tim;
static U4 u4_s_PwrCtrl_Sip_Off_SAIL_RESOUT_N_Chk_Tim;
static U4 u4_s_PwrCtrl_Sip_Off_POFF_COMPLETE_N_Chk_Tim;
static U4 u4_s_PwrCtrl_Sip_Off_VB33_SIP_FREQ_Tim;
static U4 u4_s_PwrCtrl_Sip_Off_VB33_SIP_ON_Tim;
static U4 u4_s_PwrCtrl_Sip_Off_LOW_POWER_ON_Tim;
static U4 u4_s_PwrCtrl_Sip_Off_PM_PWR_EN_N_Tim;
static U4 u4_s_PwrCtrl_Sip_Off_PM_RESIN_Tim;
static U4 u4_s_PwrCtrl_Sip_Off_PMIC_FAST_POFF_EN_N_Tim;
static U4 u4_s_PwrCtrl_Sip_Off_MM_SUSPEND_REQ_N_Tim;
static U4 u4_s_PwrCtrl_Sip_Off_STR_WAKE_Tim;
static U4 u4_s_PwrCtrl_Sip_Off_MM_OFF_REQ_Step6_Tim;
static U4 u4_s_PwrCtrl_Sip_Off_MM_STBY_Wait_Tim;
static U4 u4_s_PwrCtrl_Sip_Off_PMA_PS_HOLD_Wait_Tim;
static U4 u4_s_PwrCtrl_Sip_Off_SOC_RESOUT_N_Wait_Tim;
static U4 u4_s_PwrCtrl_Sip_Off_SAIL_RESOUT_N_Wait_Tim;
static U4 u4_s_PwrCtrl_Sip_Off_POFF_COMPLETE_N_Wait_Tim;

static U1 u1_s_PwrCtrl_Sip_Stby_Step;
static U4 u4_s_PwrCtrl_Sip_Stby_MM_SUSPEND_REQ_N_Tim;
static U4 u4_s_PwrCtrl_Sip_Stby_STR_WAKE_Tim;
static U4 u4_s_PwrCtrl_Sip_Stby_MM_STBY_N_Chk_Tim;
static U4 u4_s_PwrCtrl_Sip_Stby_AOSS_Tim;
static U4 u4_s_PwrCtrl_Sip_Stby_FREQ_Tim;
static U4 u4_s_PwrCtrl_Sip_Stby_LOW_POWER_ON_Tim;
static U4 u4_s_PwrCtrl_Sip_Stby_MM_STBY_N_Wait_Tim;
static U4 u4_s_PwrCtrl_Sip_Stby_AOSS_Wait_Tim;

static U1 u1_s_PwrCtrl_Sip_ForcedOff_Step;
static U4 u4_s_PwrCtrl_Sip_ForcedOff_PMICFASTPOFF_Tim;
static U4 u4_s_PwrCtrl_Sip_ForcedOff_POFF_COMPLETE_N_Chk_Tim;
static U4 u4_s_PwrCtrl_Sip_ForcedOff_PMRESIN_HiChk_Tim;
static U4 u4_s_PwrCtrl_Sip_ForcedOff_PMRESIN_LoChk_Tim;
static U4 u4_s_PwrCtrl_Sip_ForcedOff_VB33_SIP_FREQ_Tim;
static U4 u4_s_PwrCtrl_Sip_ForcedOff_LOW_POWER_ON_Tim;
static U4 u4_s_PwrCtrl_Sip_ForcedOff_VB33_SIP_ON_Tim;
static U4 u4_s_PwrCtrl_Sip_ForcedOff_PM_PWR_EN_N_Tim;
static U4 u4_s_PwrCtrl_Sip_ForcedOff_PM_RESIN_Step6_Tim;
static U4 u4_s_PwrCtrl_Sip_ForcedOff_PMICFASTPOFF_Step6_Tim;
static U4 u4_s_PwrCtrl_Sip_ForcedOff_MM_SUSPEND_REQ_N_Tim;
static U4 u4_s_PwrCtrl_Sip_ForcedOff_STR_WAKE_Tim;
static U4 u4_s_PwrCtrl_Sip_ForcedOff_MM_OFF_REQ_Tim;
static U4 u4_s_PwrCtrl_Sip_ForcedOff_DDConvOFFWait_Tim;
static U4 u4_s_PwrCtrl_Sip_ForcedOff_POFFCOMP_Wait_Tim;
static U4 u4_s_PwrCtrl_Sip_ForcedOff_POFFCOMP_Wait_Step4_Tim;

#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
/* 異常系チェック用STB定義 */
U1 u1_s_pwrctrl_common_err_dbg_state;
/* 異常系チェック用STB定義 */
#endif

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/* SIP通常起動制御 */
static void vd_s_PwrCtrlSipOnMainFunc( void );
static void vd_s_PwrCtrlSipOnStep1( void );
static void vd_s_PwrCtrlSipOnStep2( void );
static void vd_s_PwrCtrlSipOnStep3( void );
static void vd_s_PwrCtrlSipOnStep4( void );
static void vd_s_PwrCtrlSipOnStep5( void );
static void vd_s_PwrCtrlSipOnStep6( void );
static void vd_s_PwrCtrlSipOnStep7( void );
static void vd_s_PwrCtrlSipOnStep8( void );
/* SIPレジューム制御 */
static void vd_s_PwrCtrlSipRsmMainFunc( void );
/* SIP電源OFF制御 */
static void vd_s_PwrCtrlSipOffMainFunc( void );
static void vd_s_PwrCtrlSipOffStep1( void );
static void vd_s_PwrCtrlSipOffStep2( void );
static void vd_s_PwrCtrlSipOffStep3( void );
static void vd_s_PwrCtrlSipOffStep4( void );
static void vd_s_PwrCtrlSipOffStep5( void );
static void vd_s_PwrCtrlSipOffStep6( void );
/* スタンバイ制御 */
static void vd_s_PwrCtrlSipStbyMainFunc( void );
/* SIP電源強制OFF制御 */
static void vd_s_PwrCtrlSipForcedOffMainFunc( void );
static void vd_s_PwrCtrlSipForcedOffStep1( void );
static void vd_s_PwrCtrlSipForcedOffStep2( void );
static void vd_s_PwrCtrlSipForcedOffStep3( void );
static void vd_s_PwrCtrlSipForcedOffStep4( void );
static void vd_s_PwrCtrlSipForcedOffStep5( void );
/* SIP電源強制OFF初期化要求 共通変数初期化 */
static void vd_s_PwrCtrlSipForcedOffInitReq( void );
/* WAKEUP-STAT端子の設定関数 */
static void vd_s_PwrCtrl_Sip_Write_WAKEUP_STAT(void);

/*--------------------------------------------------------------------------*/
/* Function Macros                                                          */
/*--------------------------------------------------------------------------*/
/* SIP通常起動制御 */
#define vd_s_PwrCtrlSipOnVB33SIPON()       (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_On_VB33SIPON_Tim, (U1)PWRCTRL_SIP_ON_T_VB33_SIP_ON,(U1)PWRCTRL_CFG_PRIVATE_PORT_VB33_SIP, (Dio_LevelType)MCU_DIO_HIGH))
#define vd_s_PwrCtrlSipOnLOWPOWERON1()     (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_On_LOPWON_S1_Tim, (U1)PWRCTRL_SIP_ON_T_LOW_POWER_ON_LO,(U1)PWRCTRL_CFG_PRIVATE_PORT_LOW_POWER, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOnVB33SIPFREQ1()    (vd_s_PwrCtrl_Sip_DioFreqAct(&u4_s_PwrCtrl_Sip_On_SIPFRQ_S1_Tim, (U1)PWRCTRL_SIP_ON_T_VB33_SIP_FREQ_LO,(U1)PWM_CH_01_DDC_SIP_FREQ, (U2)PWRCTRL_SIP_PWM_PERIOD_OFF, (U2)PWRCTRL_SIP_PWM_DUTYCYCLE_OFF))
#define vd_s_PwrCtrlSipOnPMPWREN1()        (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Step1_Tim, (U1)PWRCTRL_SIP_ON_T_PMPWREN_STEP1_LO,(U1)PWRCTRL_CFG_PRIVATE_PORT_PM_PWR_EN, (Dio_LevelType)MCU_DIO_HIGH))
#define vd_s_PwrCtrlSipOnPMICFASTPOFF1()   (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_On_PMIC_FAST_POFF_EN_N_Step1_Tim, (U1)PWRCTRL_SIP_ON_T_PMICFASTPOFF_LO,(U1)PWRCTRL_CFG_PRIVATE_PORT_PMIC_FAST_POFF_EN, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOnMMOFFREQ()        (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_On_MM_OFF_REQ_Step1_Tim, (U1)PWRCTRL_SIP_ON_T_MM_OFF_REQ,(U1)PWRCTRL_CFG_PRIVATE_PORT_MM_OFF_REQ, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOnLOWPOWERON2()     (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_On_LOW_POWER_ON_Step2_Tim, (U1)PWRCTRL_SIP_ON_T_LOW_POWER_ON_HI,(U1)PWRCTRL_CFG_PRIVATE_PORT_LOW_POWER, (Dio_LevelType)MCU_DIO_HIGH))
#define vd_s_PwrCtrlSipOnVB33SIPFREQ2()    (vd_s_PwrCtrl_Sip_DioFreqAct(&u4_s_PwrCtrl_Sip_On_VB33_SIP_FREQ_Step2_Tim, (U1)PWRCTRL_SIP_ON_T_VB33_SIP_FREQ,(U1)PWM_CH_01_DDC_SIP_FREQ, (U2)PWRCTRL_SIP_PWM_PERIOD_DEF, (U2)PWRCTRL_SIP_PWM_DUTYCYCLE_DEF))
#define vd_s_PwrCtrlSipOnInitValChkAOSS()  (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_On_AOSS_Tim, &u4_s_PwrCtrl_Sip_On_AOSS_Wait_Tim, (U1)PWRCTRL_SIP_ON_T_AOSS,(U1)PWRCTRL_CFG_PRIVATE_KIND_AOSS_SLP_ENTRY_EXIT, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOnInitChkPOFFCOMP() (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_On_POFF_COMPLETE_N_Init_Tim, &u4_s_PwrCtrl_Sip_On_POFFCOMP_Wait_Tim, (U1)PWRCTRL_SIP_ON_T_POFF_COMPLETE_N,(U1)PWRCTRL_CFG_PRIVATE_KIND_POFF_COMPLETE_N, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOnPMPWREN2()        (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Step3_Tim, (U1)PWRCTRL_SIP_ON_T_PM_PWR_EN_N_LO,(U1)PWRCTRL_CFG_PRIVATE_PORT_PM_PWR_EN, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOnPMICFASTPOFF2()   (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_On_PMIC_FAST_POFF_EN_N_Step3_Tim, (U1)PWRCTRL_SIP_ON_T_PMICFASTPOFF,(U1)PWRCTRL_CFG_PRIVATE_PORT_PMIC_FAST_POFF_EN, (Dio_LevelType)MCU_DIO_HIGH))
#define vd_s_PwrCtrlSipOnMMSUSPEND()       (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_On_MM_SUSPEND_REQ_N_Tim, (U1)PWRCTRL_SIP_ON_T_MM_SUSPEND_REQ_N,(U1)PWRCTRL_CFG_PRIVATE_PORT_MM_SUSPEND_REQ, (Dio_LevelType)MCU_DIO_HIGH))
#define vd_s_PwrCtrlSipOnSTRWAKE()         (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_On_STR_WAKE_Tim, (U1)PWRCTRL_SIP_ON_T_STR_WAKE,(U1)PWRCTRL_CFG_PRIVATE_PORT_STR_WAKE, (Dio_LevelType)MCU_DIO_HIGH))
#define vd_s_PwrCtrlSipOnInitChkPSHOLD()   (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Init_Tim, &u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Wait_Tim,(U1)PWRCTRL_SIP_ON_T_PMA_PS_HOLD_INIT,(U1)PWRCTRL_CFG_PRIVATE_KIND_PMA_PS_HOLD, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOnValChkPOFFCOMP()  (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_On_POFF_COMPLETE_N_Chk_Tim, &u4_s_PwrCtrl_Sip_On_POFFCOMP_Wait_Tim,(U1)PWRCTRL_SIP_ON_T_POFF_COMP_VAL,(U1)PWRCTRL_CFG_PRIVATE_KIND_POFF_COMPLETE_N, (Dio_LevelType)MCU_DIO_HIGH))
#define vd_s_PwrCtrlSipOnValChkSOCRSOUT()  (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_On_SOC_RESOUT_N_Tim, &u4_s_PwrCtrl_Sip_On_SOC_RESOUT_Wait_Tim, (U1)PWRCTRL_SIP_ON_T_SOC_RESOUT_N,(U1)PWRCTRL_CFG_PRIVATE_KIND_SOC_RESOUT_N, (Dio_LevelType)MCU_DIO_HIGH))
#define vd_s_PwrCtrlSipOnValChkSAILRSOUT() (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_On_SAIL_RESOUT_N_Tim, &u4_s_PwrCtrl_Sip_On_SAIL_RESOUT_Wait_Tim, (U1)PWRCTRL_SIP_ON_T_SAIL_RESOUT_N,(U1)PWRCTRL_CFG_PRIVATE_KIND_SAIL_RESOUT_N, (Dio_LevelType)MCU_DIO_HIGH))
#define vd_s_PwrCtrlSipOnValChkPSHOLD()    (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Chk_Tim, &u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Wait_Tim, (U1)PWRCTRL_SIP_ON_T_PMA_PS_HOLD_VAL,(U1)PWRCTRL_CFG_PRIVATE_KIND_PMA_PS_HOLD, (Dio_LevelType)MCU_DIO_HIGH))
#define vd_s_PwrCtrlSipOnPMPWREN3()        (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Step8_Tim, (U1)PWRCTRL_SIP_ON_T_PM_PWR_EN_N_HI_P2,(U1)PWRCTRL_CFG_PRIVATE_PORT_PM_PWR_EN, (Dio_LevelType)MCU_DIO_HIGH))
/* SIPレジューム制御 */
#define vd_s_PwrCtrlSipRsmLOWPOWERON()     (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Rsm_LOW_POWER_ON_Tim, (U1)PWRCTRL_SIP_RSM_T_LOW_POWER_ON,(U1)PWRCTRL_CFG_PRIVATE_PORT_LOW_POWER, (Dio_LevelType)MCU_DIO_HIGH))
#define vd_s_PwrCtrlSipRsmVB33SIPFREQ()    (vd_s_PwrCtrl_Sip_DioFreqAct(&u4_s_PwrCtrl_Sip_Rsm_VB33_SIP_FREQ_Tim, (U1)PWRCTRL_SIP_RSM_T_VB33_SIP_FREQ,(U1)PWM_CH_01_DDC_SIP_FREQ, (U2)PWRCTRL_SIP_PWM_PERIOD_DEF, (U2)PWRCTRL_SIP_PWM_DUTYCYCLE_DEF))
#define vd_s_PwrCtrlSipRsmMMSUSPEND()      (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Rsm_MM_SUSPEND_REQ_N_Tim, (U1)PWRCTRL_SIP_RSM_T_MM_SUSPEND_REQ_N,(U1)PWRCTRL_CFG_PRIVATE_PORT_MM_SUSPEND_REQ, (Dio_LevelType)MCU_DIO_HIGH))
#define vd_s_PwrCtrlSipRsmSTRWAKE()        (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Rsm_STR_WAKE_Tim, (U1)PWRCTRL_SIP_RSM_T_STR_WAKE,(U1)PWRCTRL_CFG_PRIVATE_PORT_STR_WAKE, (Dio_LevelType)MCU_DIO_HIGH))
/* SIP電源OFF制御 */
#define vd_s_PwrCtrlSipOffMMOFFREQ1()      (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Off_MM_OFF_REQ_Step1_Tim, (U1)PWRCTRL_SIP_OFF_T_MM_OFF_REQ_HI,(U1)PWRCTRL_CFG_PRIVATE_PORT_MM_OFF_REQ, (Dio_LevelType)MCU_DIO_HIGH))
#define vd_s_PwrCtrlSipOffValChkMMSTBY()   (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_Off_MM_STBY_N_Chk_Tim, &u4_s_PwrCtrl_Sip_Off_MM_STBY_Wait_Tim, (U1)PWRCTRL_SIP_OFF_T_MM_STBY,(U1)PWRCTRL_CFG_PRIVATE_KIND_MM_STBY_N, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOffValChkPSHOLD()   (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_Off_PMA_PS_HOLD_Chk_Tim, &u4_s_PwrCtrl_Sip_Off_PMA_PS_HOLD_Wait_Tim ,(U1)PWRCTRL_SIP_OFF_T_PMA_PS_HOLD,(U1)PWRCTRL_CFG_PRIVATE_KIND_PMA_PS_HOLD, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOffValChkSOCRSOUT() (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_Off_SOC_RESOUT_N_Chk_Tim, &u4_s_PwrCtrl_Sip_Off_SOC_RESOUT_N_Wait_Tim, (U1)PWRCTRL_SIP_OFF_T_SOC_RESOUT_N,(U1)PWRCTRL_CFG_PRIVATE_KIND_SOC_RESOUT_N, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOffValChkSAILROUT() (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_Off_SAIL_RESOUT_N_Chk_Tim, &u4_s_PwrCtrl_Sip_Off_SAIL_RESOUT_N_Wait_Tim, (U1)PWRCTRL_SIP_OFF_T_SAIL_RESOUT_N,(U1)PWRCTRL_CFG_PRIVATE_KIND_SAIL_RESOUT_N, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOffValChkPOFFCOMP() (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_Off_POFF_COMPLETE_N_Chk_Tim, &u4_s_PwrCtrl_Sip_Off_POFF_COMPLETE_N_Wait_Tim, (U1)PWRCTRL_SIP_OFF_T_POFF_COMPLETE_N,(U1)PWRCTRL_CFG_PRIVATE_KIND_POFF_COMPLETE_N, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOffVB33SIPFREQ()    (vd_s_PwrCtrl_Sip_DioFreqAct(&u4_s_PwrCtrl_Sip_Off_VB33_SIP_FREQ_Tim, (U1)PWRCTRL_SIP_OFF_T_VB33_SIP_FREQ,(U1)PWM_CH_01_DDC_SIP_FREQ, (U2)PWRCTRL_SIP_PWM_PERIOD_OFF, (U2)PWRCTRL_SIP_PWM_DUTYCYCLE_OFF))
#define vd_s_PwrCtrlSipOffVB33SIPON()      (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Off_VB33_SIP_ON_Tim, (U1)PWRCTRL_SIP_OFF_T_VB33_SIP_ON,(U1)PWRCTRL_CFG_PRIVATE_PORT_VB33_SIP, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOffLOWPOWERON()     (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Off_LOW_POWER_ON_Tim, (U1)PWRCTRL_SIP_OFF_T_LOW_POWER_ON,(U1)PWRCTRL_CFG_PRIVATE_PORT_LOW_POWER, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOffPMPWREN()        (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Off_PM_PWR_EN_N_Tim, (U1)PWRCTRL_SIP_OFF_T_PM_PWR_EN_N,(U1)PWRCTRL_CFG_PRIVATE_PORT_PM_PWR_EN, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOffPMRESIN()        (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Off_PM_RESIN_Tim, (U1)PWRCTRL_SIP_OFF_T_PM_RESIN,(U1)PWRCTRL_CFG_PRIVATE_PORT_PM_RESIN, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOffPMICFASTPOFF()   (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Off_PMIC_FAST_POFF_EN_N_Tim, (U1)PWRCTRL_SIP_OFF_T_PMICFASTPOFF,(U1)PWRCTRL_CFG_PRIVATE_PORT_PMIC_FAST_POFF_EN, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOffMMSUSPEND()      (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Off_MM_SUSPEND_REQ_N_Tim, (U1)PWRCTRL_SIP_OFF_T_MM_SUSPEND_REQ_N,(U1)PWRCTRL_CFG_PRIVATE_PORT_MM_SUSPEND_REQ, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOffSTRWAKE()        (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Off_STR_WAKE_Tim, (U1)PWRCTRL_SIP_OFF_T_STR_WAKE,(U1)PWRCTRL_CFG_PRIVATE_PORT_STR_WAKE, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOffMMOFFREQ2()      (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Off_MM_OFF_REQ_Step6_Tim, (U1)PWRCTRL_SIP_OFF_T_MM_OFF_REQ_LO,(U1)PWRCTRL_CFG_PRIVATE_PORT_MM_OFF_REQ, (Dio_LevelType)MCU_DIO_LOW))
/* スタンバイシーケンス */
#define vd_s_PwrCtrlSipStbyMMSUSPEND()     (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Stby_MM_SUSPEND_REQ_N_Tim, (U1)PWRCTRL_SIP_STBY_T_MM_SUSPEND_REQ,(U1)PWRCTRL_CFG_PRIVATE_PORT_MM_SUSPEND_REQ, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipStbySTRWAKE()       (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Stby_STR_WAKE_Tim, (U1)PWRCTRL_SIP_STBY_T_STR_WAKE,(U1)PWRCTRL_CFG_PRIVATE_PORT_STR_WAKE, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipStbyValChkMMSTBY()  (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_Stby_MM_STBY_N_Chk_Tim, &u4_s_PwrCtrl_Sip_Stby_MM_STBY_N_Wait_Tim, (U1)PWRCTRL_SIP_STBY_T_MM_STBY,(U1)PWRCTRL_CFG_PRIVATE_KIND_MM_STBY_N, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipStbyValChkAOSS()    (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_Stby_AOSS_Tim, &u4_s_PwrCtrl_Sip_Stby_AOSS_Wait_Tim, (U1)PWRCTRL_SIP_STBY_T_AOSS,(U1)PWRCTRL_CFG_PRIVATE_KIND_AOSS_SLP_ENTRY_EXIT, (Dio_LevelType)MCU_DIO_HIGH))
#define vd_s_PwrCtrlSipStbyVB33SIPFREQ()   (vd_s_PwrCtrl_Sip_DioFreqAct(&u4_s_PwrCtrl_Sip_Stby_FREQ_Tim, (U1)PWRCTRL_SIP_STBY_T_VB33_SIP_FREQ,(U1)PWM_CH_01_DDC_SIP_FREQ, (U2)PWRCTRL_SIP_PWM_PERIOD_OFF, (U2)PWRCTRL_SIP_PWM_DUTYCYCLE_OFF))
#define vd_s_PwrCtrlSipStbyLOWPOWERON()    (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Stby_LOW_POWER_ON_Tim, (U1)PWRCTRL_SIP_STBY_T_LOW_POWER_ON,(U1)PWRCTRL_CFG_PRIVATE_PORT_LOW_POWER, (Dio_LevelType)MCU_DIO_LOW))
/* SIP電源強制OFFシーケンス */
#define vd_s_PwrCtrlSipFOffPMICFASTPOFF1()   (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_ForcedOff_PMICFASTPOFF_Tim, (U1)PWRCTRL_SIP_FOFF_T_PMICFASTPOFF,(U1)PWRCTRL_CFG_PRIVATE_PORT_PMIC_FAST_POFF_EN, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipFOffValChkPOFFCOMP()  (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_ForcedOff_POFF_COMPLETE_N_Chk_Tim, &u4_s_PwrCtrl_Sip_ForcedOff_POFFCOMP_Wait_Tim, (U1)PWRCTRL_SIP_FOFF_T_POFF_COMPLETE_N,(U1)PWRCTRL_CFG_PRIVATE_KIND_POFF_COMPLETE_N, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipFOffPMRESINHI()       (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_ForcedOff_PMRESIN_HiChk_Tim, (U1)PWRCTRL_SIP_FOFF_T_PMRESIN_HI,(U1)PWRCTRL_CFG_PRIVATE_PORT_PM_RESIN, (Dio_LevelType)MCU_DIO_HIGH))
#define vd_s_PwrCtrlSipFOffPMRESINLO()       (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_ForcedOff_PMRESIN_LoChk_Tim, (U1)PWRCTRL_SIP_FOFF_T_PMRESIN_LO,(U1)PWRCTRL_CFG_PRIVATE_PORT_PM_RESIN, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipFOffValChkPOFFCOMP2() (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_ForcedOff_POFF_COMPLETE_N_Chk_Tim, &u4_s_PwrCtrl_Sip_ForcedOff_POFFCOMP_Wait_Step4_Tim, (U1)PWRCTRL_SIP_FOFF_T_POFF_COMPLETE_N,(U1)PWRCTRL_CFG_PRIVATE_KIND_POFF_COMPLETE_N, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipFOffVB33SIPFREQ()     (vd_s_PwrCtrl_Sip_DioFreqAct(&u4_s_PwrCtrl_Sip_ForcedOff_VB33_SIP_FREQ_Tim, (U1)PWRCTRL_SIP_FOFF_T_VB33_SIP_FREQ,(U1)PWM_CH_01_DDC_SIP_FREQ, (U2)PWRCTRL_SIP_PWM_PERIOD_OFF, (U2)PWRCTRL_SIP_PWM_DUTYCYCLE_OFF))
#define vd_s_PwrCtrlSipFOffLOWPOWERON()      (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_ForcedOff_LOW_POWER_ON_Tim, (U1)PWRCTRL_SIP_FOFF_T_LOW_POWER_ON,(U1)PWRCTRL_CFG_PRIVATE_PORT_LOW_POWER, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipFOffVB33SIPON()       (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_ForcedOff_VB33_SIP_ON_Tim, (U1)PWRCTRL_SIP_FOFF_T_VB33_SIP_ON,(U1)PWRCTRL_CFG_PRIVATE_PORT_VB33_SIP, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipFOffPMPWREN()         (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_ForcedOff_PM_PWR_EN_N_Tim, (U1)PWRCTRL_SIP_FOFF_T_PM_PWR_EN_N,(U1)PWRCTRL_CFG_PRIVATE_PORT_PM_PWR_EN, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipFOffPMRESIN()         (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_ForcedOff_PM_RESIN_Step6_Tim, (U1)PWRCTRL_SIP_FOFF_T_PM_RESIN_LO2,(U1)PWRCTRL_CFG_PRIVATE_PORT_PM_RESIN, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipFOffPMICFASTPOFF2()   (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_ForcedOff_PMICFASTPOFF_Step6_Tim, (U1)PWRCTRL_SIP_FOFF_T_PMICFASTPOFF_P2,(U1)PWRCTRL_CFG_PRIVATE_PORT_PMIC_FAST_POFF_EN, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipFOffMMSUSPEND()       (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_ForcedOff_MM_SUSPEND_REQ_N_Tim, (U1)PWRCTRL_SIP_FOFF_T_MM_SUSPEND_REQ,(U1)PWRCTRL_CFG_PRIVATE_PORT_MM_SUSPEND_REQ, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipFOffSTRWAKE()         (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_ForcedOff_STR_WAKE_Tim, (U1)PWRCTRL_SIP_FOFF_T_STR_WAKE,(U1)PWRCTRL_CFG_PRIVATE_PORT_STR_WAKE, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipFOffMMOFFREQ()        (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_ForcedOff_MM_OFF_REQ_Tim, (U1)PWRCTRL_SIP_FOFF_T_MM_OFF_REQ_LO,(U1)PWRCTRL_CFG_PRIVATE_PORT_MM_OFF_REQ, (Dio_LevelType)MCU_DIO_LOW))

/*--------------------------------------------------------------------------*/
/* Functions                                                                */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* Scheduled Functions                                                      */
/****************************************************************************/
/****************************************************************************/
/* Service API                                                              */
/****************************************************************************/
/*****************************************************************************
  Function      : u1_g_PwrCtrlSipGetSts
  Description   : SIP電源 ステータス通知関数
  param[in/out] : none
  return        : FALSE(0)：シーケンス実行中
                  TRUE(1) ：シーケンス完了
  Note          : none
*****************************************************************************/
U1 u1_g_PwrCtrlSipGetSts( void )
{
    U1 u1_t_ret;

    u1_t_ret = (U1)FALSE; /* 初期化：SIP電源シーケンス実行中 */

    if ( u1_s_PwrCtrl_Sip_Pwr_Sts == (U1)PWRCTRL_SIP_STS_NON )
    {
        u1_t_ret = (U1)TRUE;
    }

    return ( u1_t_ret );
}

/*****************************************************************************
  Function      : u1_g_PwrCtrlSipLowPowerOnInfo
  Description   : LOW_POWER_ON ステータス通知関数
  param[in/out] : none
  return        : FALSE(0)：LOW_POWER_ON 端子モニタリング開始条件非成立
                  TRUE(1) ：LOW_POWER_ON 端子モニタリング開始条件成立
  Note          : none
*****************************************************************************/
U1 u1_g_PwrCtrlSipLowPowerOnInfo( void )
{
    return(u1_s_PwrCtrl_Sip_LOW_POWER_ON_Sts);
}

/*****************************************************************************
  Function      : u1_g_PwrCtrlSipFOffInfo
  Description   : SIP電源強制OFF要求通知関数
  param[in/out] : none
  return        : 要求無し (0)：PWRCTRL_SIP_FORCEDOFF_NON
                  SOC異常  (1)：PWRCTRL_SIP_FORCEDOFF_SOCERR
                  PMIC異常 (2)：PWRCTRL_SIP_FORCEDOFF_PMICERR
                  DDコンOFF(3)：PWRCTRL_SIP_FORCEDOFF_DDCONV
  Note          : none
*****************************************************************************/
U1 u1_g_PwrCtrlSipFOffInfo( void )
{
    return(u1_s_PwrCtrl_Sip_FOff_Sts);
}

/*****************************************************************************
  Function      : u1_g_PwrCtrlSipFOffGetSts
  Description   : SIP入力DDコン電源OFF処理実施要否通知関数
  param[in/out] : none
  return        : SIP入力DDコン電源OFF処理未実施 (0)：PWRCTRL_SIP_FOFF_DDCONV_OFF
                  SIP入力DDコン電源OFF処理実施   (1)：PWRCTRL_SIP_FOFF_DDCONV_ON
  Note          : none
*****************************************************************************/
U1 u1_g_PwrCtrlSipFOffGetSts( void )
{
    return(u1_s_PwrCtrl_Sip_DDConvFlag);
}

/*****************************************************************************
  Function      : u1_g_PwrCtrlSipStbyStepGetSts
  Description   : SIPスタンバイ/SIP電源OFFシーケンス現在STEP通知関数
  param[in/out] : [in] u1_a_stby: スタンバイシーケンス/SIP電源OFFシーケンス判定
  return        : 現在STEP数
  Note          : none
*****************************************************************************/
U1 u1_g_PwrCtrlSipStbyStepGetSts( const U1 u1_a_stby )
{
    U1 u1_t_ret;
    
    /* スタンバイシーケンスの現在STEP要求の場合 */
    if(u1_a_stby == (U1)PWRCTRL_SIP_STBY_STEP_REQ){
        /* 戻り値にスタンバイシーケンスのSTEP数を設定 */
        u1_t_ret = u1_s_PwrCtrl_Sip_Stby_Step;
    }
    
    else if(u1_a_stby == (U1)PWRCTRL_SIP_SIPOFF_STEP_REQ){
        /* 戻り値にSIP電源OFFシーケンスのSTEP数を設定 */
        u1_t_ret = u1_s_PwrCtrl_Sip_Off_Step;
    }
    
    else{
        /* 範囲外の場合は異常値としてCMPLTを設定 */
        u1_t_ret = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    }
    
    return(u1_t_ret);
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlSipEthReqJudge
  Description   : EtherSW制御要求処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlSipEthReqJudge( void )
{
    U1 u1_t_readlv;
    
    /* EtherSW起動要求有りの場合 */
    if(u1_s_PwrCtrl_Sip_EthReq_Sts == (U1)PWRCTRL_ETH_REQ_ON){
    
        /* SAIL_RESOUT_Nの端子情報を取得する */
        u1_t_readlv = u1_g_PwrCtrl_PinMonitor_GetPinInfo((U1)PWRCTRL_CFG_PRIVATE_KIND_SAIL_RESOUT_N);
        
        if(u1_t_readlv == (U1)MCU_DIO_HIGH){
            /* Hiを検知したらEtherSW起動要求を通知 */
            EthSwt_SWIC_PowerOn(); /* EtherSW起動要求 */
            
            /* EtherSWPowerON通知制御開始要求を無しに設定 */
            u1_s_PwrCtrl_Sip_EthReq_Sts = (U1)PWRCTRL_ETH_REQ_NON;
        }
    }
    
    /* EtherSW終了要求有りの場合 */
    else if(u1_s_PwrCtrl_Sip_EthReq_Sts == (U1)PWRCTRL_ETH_REQ_OFF){
        /* SAIL_RESOUT_Nの端子情報を取得する */
        u1_t_readlv = u1_g_PwrCtrl_PinMonitor_GetPinInfo((U1)PWRCTRL_CFG_PRIVATE_KIND_SAIL_RESOUT_N);
        
        if(u1_t_readlv == (U1)MCU_DIO_LOW){
            /* Loを検知したらEtherSW終了要求を通知 */
            EthSwt_SWIC_PowerOff(); /* EtherSW終了要求 */
            
            /* EtherSWPowerON通知制御開始要求を無しに設定 */
            u1_s_PwrCtrl_Sip_EthReq_Sts = (U1)PWRCTRL_ETH_REQ_NON;
        }
    }
    
    else{
        
        /* EtherSW要求無しの場合 */
        /* 何もしない */
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlSipBonInit
  Description   : 6-8-1,6-8-2,6-9,5-3,SIP起動全体の初期化処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlSipBonInit( void )
{
    u1_s_PwrCtrl_Sip_LOW_POWER_ON_Sts                 = (U1)FALSE;
    u1_s_PwrCtrl_Sip_Pwr_Sts                          = (U1)PWRCTRL_SIP_STS_NON;
    u1_s_PwrCtrl_Sip_FOff_Sts                         = (U1)PWRCTRL_SIP_FORCEDOFF_NON;
    u1_s_PwrCtrl_Sip_EthReq_Sts                       = (U1)PWRCTRL_ETH_REQ_NON;
    
    /* SIP入力DDコン電源OFF処理未実施状態を設定 */
    u1_s_PwrCtrl_Sip_DDConvFlag                       = (U1)PWRCTRL_SIP_FOFF_DDCONV_OFF;

    /* ステップ判定用RAMの初期化 */
    u1_s_PwrCtrl_Sip_On_Step                          = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Rsm_Step                         = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Off_Step                         = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Stby_Step                        = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_ForcedOff_Step                   = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    
    /* WAKEUP-STAT端子状態の初期化 */
    u1_s_PwrCtrl_Sip_WAKEUP_STAT1                     = (U1)MCU_DIO_LOW;
    u1_s_PwrCtrl_Sip_WAKEUP_STAT2                     = (U1)MCU_DIO_LOW;
    u1_s_PwrCtrl_Sip_WAKEUP_STAT3                     = (U1)MCU_DIO_LOW;

    /* WAKEUP-STAT端子状態のRIM更新 */
    vd_g_Rim_WriteU1((U2)RIMID_U1_PWCTR_SOC_WU_STAT1, u1_s_PwrCtrl_Sip_WAKEUP_STAT1);
    vd_g_Rim_WriteU1((U2)RIMID_U1_PWCTR_SOC_WU_STAT2, u1_s_PwrCtrl_Sip_WAKEUP_STAT2);

    /* 待機時間測定用RAMの初期化 */
    /* SiP通常起動 */
    u4_s_PwrCtrl_Sip_On_VB33SIPON_Tim                 = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_LOPWON_S1_Tim                 = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_SIPFRQ_S1_Tim                 = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_AOSS_Tim                      = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_POFF_COMPLETE_N_Init_Tim      = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Step1_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PMIC_FAST_POFF_EN_N_Step1_Tim = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_MM_OFF_REQ_Step1_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_LOW_POWER_ON_Step2_Tim        = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_VB33_SIP_FREQ_Step2_Tim       = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Step3_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PMIC_FAST_POFF_EN_N_Step3_Tim = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_MM_SUSPEND_REQ_N_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_STR_WAKE_Tim                  = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Init_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_POFF_COMPLETE_N_Chk_Tim       = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_SOC_RESOUT_N_Tim              = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_SAIL_RESOUT_N_Tim             = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Chk_Tim           = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Lo_ElapsedTim     = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Step8_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_AOSS_Wait_Tim                 = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_POFFCOMP_Wait_Tim             = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Wait_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_SOC_RESOUT_Wait_Tim           = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_SAIL_RESOUT_Wait_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;

    /* SiPレジューム起動 */
    u4_s_PwrCtrl_Sip_Rsm_LOW_POWER_ON_Tim             = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Rsm_VB33_SIP_FREQ_Tim            = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Rsm_MM_SUSPEND_REQ_N_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Rsm_STR_WAKE_Tim                 = (U4)PWRCTRL_SIP_TIME_INIT;

    /* SiP電源OFF */
    u4_s_PwrCtrl_Sip_Off_MM_OFF_REQ_Step1_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_MM_STBY_N_Chk_Tim            = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_PMA_PS_HOLD_Chk_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_SOC_RESOUT_N_Chk_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_SAIL_RESOUT_N_Chk_Tim        = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_POFF_COMPLETE_N_Chk_Tim      = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_VB33_SIP_FREQ_Tim            = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_VB33_SIP_ON_Tim              = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_LOW_POWER_ON_Tim             = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_PM_PWR_EN_N_Tim              = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_PM_RESIN_Tim                 = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_PMIC_FAST_POFF_EN_N_Tim      = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_MM_SUSPEND_REQ_N_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_STR_WAKE_Tim                 = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_MM_OFF_REQ_Step6_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_MM_STBY_Wait_Tim             = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_PMA_PS_HOLD_Wait_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_SOC_RESOUT_N_Wait_Tim        = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_SAIL_RESOUT_N_Wait_Tim       = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_POFF_COMPLETE_N_Wait_Tim     = (U4)PWRCTRL_SIP_TIME_INIT;

    /* SiPスタンバイ */
    u4_s_PwrCtrl_Sip_Stby_MM_SUSPEND_REQ_N_Tim        = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_STR_WAKE_Tim                = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_MM_STBY_N_Chk_Tim           = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_AOSS_Tim                    = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_FREQ_Tim                    = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_LOW_POWER_ON_Tim            = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_MM_STBY_N_Wait_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_AOSS_Wait_Tim               = (U4)PWRCTRL_SIP_TIME_INIT;

    /* SiP強制電源OFF */
    u4_s_PwrCtrl_Sip_ForcedOff_PMICFASTPOFF_Tim        = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_POFF_COMPLETE_N_Chk_Tim = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_PMRESIN_HiChk_Tim       = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_PMRESIN_LoChk_Tim       = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_VB33_SIP_FREQ_Tim       = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_LOW_POWER_ON_Tim        = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_VB33_SIP_ON_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_PM_PWR_EN_N_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_PM_RESIN_Step6_Tim      = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_PMICFASTPOFF_Step6_Tim  = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_MM_SUSPEND_REQ_N_Tim    = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_STR_WAKE_Tim            = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_MM_OFF_REQ_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_DDConvOFFWait_Tim       = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_POFFCOMP_Wait_Tim       = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_POFFCOMP_Wait_Step4_Tim = (U4)PWRCTRL_SIP_TIME_INIT;

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlSipWkupInit
  Description   : 6-8-1,6-8-2,6-9,5-3,SIP起動全体の初期化処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlSipWkupInit( void )
{
    U1 u1_t_wust1_buf;
    U1 u1_t_wust2_buf;
    U1 u1_t_wust1_ret;
    U1 u1_t_wust2_ret;

    u1_s_PwrCtrl_Sip_LOW_POWER_ON_Sts                 = (U1)FALSE;
    u1_s_PwrCtrl_Sip_Pwr_Sts                          = (U1)PWRCTRL_SIP_STS_NON;
    u1_s_PwrCtrl_Sip_FOff_Sts                         = (U1)PWRCTRL_SIP_FORCEDOFF_NON;
    u1_s_PwrCtrl_Sip_EthReq_Sts                       = (U1)PWRCTRL_ETH_REQ_NON;
    
    /* SIP入力DDコン電源OFF処理未実施状態を設定 */
    u1_s_PwrCtrl_Sip_DDConvFlag                       = (U1)PWRCTRL_SIP_FOFF_DDCONV_OFF;

    /* ステップ判定用RAMの初期化 */
    u1_s_PwrCtrl_Sip_On_Step                          = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Rsm_Step                         = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Off_Step                         = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Stby_Step                        = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_ForcedOff_Step                   = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    
    /* WAKEUP-STAT1初期化 */
    u1_t_wust1_buf = (U1)MCU_DIO_LOW;
    u1_t_wust1_ret = u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_PWCTR_SOC_WU_STAT1, &u1_t_wust1_buf);
    if((u1_t_wust1_ret & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK)
    {
        u1_s_PwrCtrl_Sip_WAKEUP_STAT1 = u1_t_wust1_buf;
    }
    else
    {
        u1_s_PwrCtrl_Sip_WAKEUP_STAT1 = (U1)MCU_DIO_HIGH;
    }
    /* WAKEUP-STAT2初期化 */
    u1_t_wust2_buf = (U1)MCU_DIO_LOW;
    u1_t_wust2_ret = u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_PWCTR_SOC_WU_STAT2, &u1_t_wust2_buf);
    if((u1_t_wust2_ret & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK)
    {
        u1_s_PwrCtrl_Sip_WAKEUP_STAT2 = u1_t_wust2_buf;
    }
    else
    {
        u1_s_PwrCtrl_Sip_WAKEUP_STAT2 = (U1)MCU_DIO_LOW;
    }
    /* WAKEUP-STAT3初期化 */
    u1_s_PwrCtrl_Sip_WAKEUP_STAT3 = (U1)MCU_DIO_LOW;

    /* 待機時間測定用RAMの初期化 */
    /* SiP通常起動 */
    u4_s_PwrCtrl_Sip_On_VB33SIPON_Tim                 = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_LOPWON_S1_Tim                 = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_SIPFRQ_S1_Tim                 = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_AOSS_Tim                      = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_POFF_COMPLETE_N_Init_Tim      = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Step1_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PMIC_FAST_POFF_EN_N_Step1_Tim = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_MM_OFF_REQ_Step1_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_LOW_POWER_ON_Step2_Tim        = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_VB33_SIP_FREQ_Step2_Tim       = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Step3_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PMIC_FAST_POFF_EN_N_Step3_Tim = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_MM_SUSPEND_REQ_N_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_STR_WAKE_Tim                  = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Init_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_POFF_COMPLETE_N_Chk_Tim       = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_SOC_RESOUT_N_Tim              = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_SAIL_RESOUT_N_Tim             = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Chk_Tim           = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Lo_ElapsedTim     = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Step8_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_AOSS_Wait_Tim                 = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_POFFCOMP_Wait_Tim             = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Wait_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_SOC_RESOUT_Wait_Tim           = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_SAIL_RESOUT_Wait_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;

    /* SiPレジューム起動 */
    u4_s_PwrCtrl_Sip_Rsm_LOW_POWER_ON_Tim             = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Rsm_VB33_SIP_FREQ_Tim            = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Rsm_MM_SUSPEND_REQ_N_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Rsm_STR_WAKE_Tim                 = (U4)PWRCTRL_SIP_TIME_INIT;

    /* SiP電源OFF */
    u4_s_PwrCtrl_Sip_Off_MM_OFF_REQ_Step1_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_MM_STBY_N_Chk_Tim            = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_PMA_PS_HOLD_Chk_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_SOC_RESOUT_N_Chk_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_SAIL_RESOUT_N_Chk_Tim        = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_POFF_COMPLETE_N_Chk_Tim      = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_VB33_SIP_FREQ_Tim            = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_VB33_SIP_ON_Tim              = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_LOW_POWER_ON_Tim             = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_PM_PWR_EN_N_Tim              = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_PM_RESIN_Tim                 = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_PMIC_FAST_POFF_EN_N_Tim      = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_MM_SUSPEND_REQ_N_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_STR_WAKE_Tim                 = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_MM_OFF_REQ_Step6_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_MM_STBY_Wait_Tim             = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_PMA_PS_HOLD_Wait_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_SOC_RESOUT_N_Wait_Tim        = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_SAIL_RESOUT_N_Wait_Tim       = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_POFF_COMPLETE_N_Wait_Tim     = (U4)PWRCTRL_SIP_TIME_INIT;

    /* SiPスタンバイ */
    u4_s_PwrCtrl_Sip_Stby_MM_SUSPEND_REQ_N_Tim        = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_STR_WAKE_Tim                = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_MM_STBY_N_Chk_Tim           = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_AOSS_Tim                    = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_FREQ_Tim                    = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_LOW_POWER_ON_Tim            = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_MM_STBY_N_Wait_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_AOSS_Wait_Tim               = (U4)PWRCTRL_SIP_TIME_INIT;

    /* SiP強制電源OFF */
    u4_s_PwrCtrl_Sip_ForcedOff_PMICFASTPOFF_Tim        = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_POFF_COMPLETE_N_Chk_Tim = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_PMRESIN_HiChk_Tim       = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_PMRESIN_LoChk_Tim       = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_VB33_SIP_FREQ_Tim       = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_LOW_POWER_ON_Tim        = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_VB33_SIP_ON_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_PM_PWR_EN_N_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_PM_RESIN_Step6_Tim      = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_PMICFASTPOFF_Step6_Tim  = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_MM_SUSPEND_REQ_N_Tim    = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_STR_WAKE_Tim            = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_MM_OFF_REQ_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_DDConvOFFWait_Tim       = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_POFFCOMP_Wait_Tim       = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_POFFCOMP_Wait_Step4_Tim = (U4)PWRCTRL_SIP_TIME_INIT;

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlSipOnReq
  Description   : 6-8-1.SIP通常起動制御_初期化処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlSipOnReq( void )
{
    u1_s_PwrCtrl_Sip_LOW_POWER_ON_Sts                 = (U1)FALSE;
    u1_s_PwrCtrl_Sip_Pwr_Sts                          = (U1)PWRCTRL_SIP_STS_PWRON;
    u1_s_PwrCtrl_Sip_FOff_Sts                         = (U1)PWRCTRL_SIP_FORCEDOFF_NON;
    u1_s_PwrCtrl_Sip_EthReq_Sts                       = (U1)PWRCTRL_ETH_REQ_NON;

    /* WAKEUP-STAT端子の設定 */
    vd_s_PwrCtrl_Sip_Write_WAKEUP_STAT();

    /* 現在起動ステップの初期化 */
    u1_s_PwrCtrl_Sip_On_Step                          = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
    /* 他処理の無効化 */
    u1_s_PwrCtrl_Sip_Rsm_Step                         = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Off_Step                         = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Stby_Step                        = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_ForcedOff_Step                   = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    
    /* 待機時間測定用RAMの初期化 */
    u4_s_PwrCtrl_Sip_On_VB33SIPON_Tim                 = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_LOPWON_S1_Tim                 = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_SIPFRQ_S1_Tim                 = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_AOSS_Tim                      = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_POFF_COMPLETE_N_Init_Tim      = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Step1_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PMIC_FAST_POFF_EN_N_Step1_Tim = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_MM_OFF_REQ_Step1_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_LOW_POWER_ON_Step2_Tim        = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_VB33_SIP_FREQ_Step2_Tim       = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Step3_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PMIC_FAST_POFF_EN_N_Step3_Tim = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_MM_SUSPEND_REQ_N_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_STR_WAKE_Tim                  = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Init_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_POFF_COMPLETE_N_Chk_Tim       = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_SOC_RESOUT_N_Tim              = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_SAIL_RESOUT_N_Tim             = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Chk_Tim           = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Lo_ElapsedTim     = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Step8_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_AOSS_Wait_Tim                 = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_POFFCOMP_Wait_Tim             = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Wait_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_SOC_RESOUT_Wait_Tim           = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_SAIL_RESOUT_Wait_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;
    
    /* 計測点③Soc起動の検知状態をクリア */
    vd_g_PwrCtrlComTxClrBootLog((U1)PWRCTRL_COM_BOOTLOG_BONREQ);

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlSipOnPwrOnReq
  Description   : 6-8-1.SIP通常起動制御_初期化処理 電源のみ起動処理開始要求
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlSipOnPwrOnReq( void )
{
    u1_s_PwrCtrl_Sip_Pwr_Sts                         = (U1)PWRCTRL_SIP_STS_PWRON;
    u1_s_PwrCtrl_Sip_FOff_Sts                        = (U1)PWRCTRL_SIP_FORCEDOFF_NON;
    u1_s_PwrCtrl_Sip_LOW_POWER_ON_Sts                = (U1)TRUE;
    u1_s_PwrCtrl_Sip_EthReq_Sts                      = (U1)PWRCTRL_ETH_REQ_NON;

    /* WAKEUP-STAT端子の設定 */
    vd_s_PwrCtrl_Sip_Write_WAKEUP_STAT();

    /* 現在起動ステップの初期化 */
    u1_s_PwrCtrl_Sip_On_Step                          = (U1)PWRCTRL_COMMON_PROCESS_STEP3;
    /* 他処理の無効化 */
    u1_s_PwrCtrl_Sip_Rsm_Step                         = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Off_Step                         = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Stby_Step                        = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_ForcedOff_Step                   = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    
    /* 待機時間測定用RAMの初期化 */
    u4_s_PwrCtrl_Sip_On_VB33SIPON_Tim                 = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_LOPWON_S1_Tim                 = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_SIPFRQ_S1_Tim                 = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_AOSS_Tim                      = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_POFF_COMPLETE_N_Init_Tim      = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Step1_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PMIC_FAST_POFF_EN_N_Step1_Tim = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_MM_OFF_REQ_Step1_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_LOW_POWER_ON_Step2_Tim        = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_VB33_SIP_FREQ_Step2_Tim       = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Step3_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PMIC_FAST_POFF_EN_N_Step3_Tim = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_MM_SUSPEND_REQ_N_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_STR_WAKE_Tim                  = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Init_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_POFF_COMPLETE_N_Chk_Tim       = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_SOC_RESOUT_N_Tim              = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_SAIL_RESOUT_N_Tim             = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Chk_Tim           = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Lo_ElapsedTim     = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Step8_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_AOSS_Wait_Tim                 = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_POFFCOMP_Wait_Tim             = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Wait_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_SOC_RESOUT_Wait_Tim           = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_On_SAIL_RESOUT_Wait_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;
    
    /* 計測点③Soc起動の検知状態をクリア */
    vd_g_PwrCtrlComTxClrBootLog((U1)PWRCTRL_COM_BOOTLOG_BONREQ);

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlSipRsmReq
  Description   : 6-8-2.SIPレジューム制御_要求確認処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlSipRsmReq( void )
{
    u1_s_PwrCtrl_Sip_LOW_POWER_ON_Sts         = (U1)FALSE;
    u1_s_PwrCtrl_Sip_Pwr_Sts                  = (U1)PWRCTRL_SIP_STS_RESUME;
    u1_s_PwrCtrl_Sip_EthReq_Sts               = (U1)PWRCTRL_ETH_REQ_ON;

    /* WAKEUP-STAT端子の設定 */
    vd_s_PwrCtrl_Sip_Write_WAKEUP_STAT();

    /* 現在起動ステップの初期化 */
    u1_s_PwrCtrl_Sip_Rsm_Step                 = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
    /* 他処理の無効化 */
    u1_s_PwrCtrl_Sip_On_Step                  = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Off_Step                 = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Stby_Step                = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_ForcedOff_Step           = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    
    /* 待機時間測定用RAMの初期化 */
    u4_s_PwrCtrl_Sip_Rsm_LOW_POWER_ON_Tim     = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Rsm_VB33_SIP_FREQ_Tim    = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Rsm_MM_SUSPEND_REQ_N_Tim = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Rsm_STR_WAKE_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    
    /* 計測点③'STRWakeの検知状態をクリア */
    vd_g_PwrCtrlComTxClrBootLog((U1)PWRCTRL_COM_BOOTLOG_STRREQ);

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlSipOffReq
  Description   : 6-9.SIP電源OFF制御_初期化処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlSipOffReq( void )
{
    u1_s_PwrCtrl_Sip_Pwr_Sts                      = (U1)PWRCTRL_SIP_STS_PWROFF;
    u1_s_PwrCtrl_Sip_FOff_Sts                     = (U1)PWRCTRL_SIP_FORCEDOFF_NON;
    u1_s_PwrCtrl_Sip_EthReq_Sts                   = (U1)PWRCTRL_ETH_REQ_NON;

    /* 現在起動ステップの初期化 */
    u1_s_PwrCtrl_Sip_Off_Step                     = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
    /* 他処理の無効化 */
    u1_s_PwrCtrl_Sip_On_Step                      = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Rsm_Step                     = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Stby_Step                    = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_ForcedOff_Step               = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;

    /* 待機時間測定用RAMの初期化 */
    u4_s_PwrCtrl_Sip_Off_MM_OFF_REQ_Step1_Tim     = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_MM_STBY_N_Chk_Tim        = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_PMA_PS_HOLD_Chk_Tim      = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_SOC_RESOUT_N_Chk_Tim     = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_SAIL_RESOUT_N_Chk_Tim    = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_POFF_COMPLETE_N_Chk_Tim  = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_VB33_SIP_FREQ_Tim        = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_VB33_SIP_ON_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_LOW_POWER_ON_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_PM_PWR_EN_N_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_PM_RESIN_Tim             = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_PMIC_FAST_POFF_EN_N_Tim  = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_MM_SUSPEND_REQ_N_Tim     = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_STR_WAKE_Tim             = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_MM_OFF_REQ_Step6_Tim     = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_MM_STBY_Wait_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_PMA_PS_HOLD_Wait_Tim     = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_SOC_RESOUT_N_Wait_Tim    = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_SAIL_RESOUT_N_Wait_Tim   = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_POFF_COMPLETE_N_Wait_Tim = (U4)PWRCTRL_SIP_TIME_INIT;

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlSipStbyReq
  Description   : 5-3.スタンバイシーケンス_初期化処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlSipStbyReq( void )
{
    u1_s_PwrCtrl_Sip_Pwr_Sts                   = (U1)PWRCTRL_SIP_STS_STANDBY;
    u1_s_PwrCtrl_Sip_FOff_Sts                  = (U1)PWRCTRL_SIP_FORCEDOFF_NON;
    u1_s_PwrCtrl_Sip_EthReq_Sts                = (U1)PWRCTRL_ETH_REQ_NON;

    /* 現在起動ステップの初期化 */
    u1_s_PwrCtrl_Sip_Stby_Step                 = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
    /* 他処理の無効化 */
    u1_s_PwrCtrl_Sip_On_Step                   = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Rsm_Step                  = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Off_Step                  = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_ForcedOff_Step            = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;

    /* 待機時間測定用RAMの初期化 */
    u4_s_PwrCtrl_Sip_Stby_MM_SUSPEND_REQ_N_Tim = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_STR_WAKE_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_MM_STBY_N_Chk_Tim    = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_AOSS_Tim             = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_FREQ_Tim             = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_LOW_POWER_ON_Tim     = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_MM_STBY_N_Wait_Tim   = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_AOSS_Wait_Tim        = (U4)PWRCTRL_SIP_TIME_INIT;

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlSipForcedOffSTEP1Req
  Description   : 5-6.SIP電源強制OFFシーケンス STEP1開始要求
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlSipForcedOffSTEP1Req( void )
{
    /* 起動ステップの初期化 */
    /* SIP電源強制OFF処理(SoC異常)開始 */
    u1_s_PwrCtrl_Sip_ForcedOff_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
    /* EtherSW終了要求を設定 */
    u1_s_PwrCtrl_Sip_EthReq_Sts     = (U1)PWRCTRL_ETH_REQ_OFF;
    
    vd_s_PwrCtrlSipForcedOffInitReq();

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlSipForcedOffSTEP2Req
  Description   : 5-6.SIP電源強制OFFシーケンス STEP2開始要求
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlSipForcedOffSTEP2Req( void )
{
    /* 起動ステップの初期化 */
    /* SIP電源強制OFF処理(PMIC異常)開始 */
    u1_s_PwrCtrl_Sip_ForcedOff_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP2;
    
    vd_s_PwrCtrlSipForcedOffInitReq();

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlSipForcedOffSTEP4Req
  Description   : 5-6.SIP電源強制OFFシーケンス STEP4開始要求
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlSipForcedOffSTEP4Req( void )
{
    /* 起動ステップの初期化 */
    /* SIP入力DDコンOFF処理開始 */
    u1_s_PwrCtrl_Sip_ForcedOff_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP4;
    
    vd_s_PwrCtrlSipForcedOffInitReq();

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlSipStandbyCancelSTEP1Req
  Description   : 5-6-1.スタンバイ処理中の起動トリガ時シーケンス STEP1開始要求
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlSipStandbyCancelSTEP1Req( void )
{
    /* 起動ステップの初期化 */
    u1_s_PwrCtrl_Sip_ForcedOff_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP1;

    vd_s_PwrCtrlSipForcedOffInitReq();

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlSipSetDDConvOff
  Description   : SIP入力DDコン電源OFF処理実施/未実施設定
  param[in/out] : [in] u1_a_ddconv: SIP入力DDコン電源OFF処理実施有無
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlSipSetDDConvOff( const U1 u1_a_ddconv )
{
    /* SIP入力DDコン電源OFF処理未実施状態を設定 */
    u1_s_PwrCtrl_Sip_DDConvFlag     = u1_a_ddconv;

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlSipSoCOnComp
  Description   : SIP共通 SoC起動完了を受信時のWAKEUP-STAT1設定関数
  param[in/out] : -
  return        : -
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlSipSoCOnComp(void)
{
    /* MCUコールドスタート(WALEUP-STAT1=Low)の場合のみ実施 */
    if(u1_s_PwrCtrl_Sip_WAKEUP_STAT1 == (U1)MCU_DIO_LOW)
    {
        /* MCUホットスタート(WALEUP-STAT1=High)を設定 */
        u1_s_PwrCtrl_Sip_WAKEUP_STAT1 = (U1)MCU_DIO_HIGH;
        vd_g_Rim_WriteU1((U2)RIMID_U1_PWCTR_SOC_WU_STAT1, u1_s_PwrCtrl_Sip_WAKEUP_STAT1);

        /* 端子設定 */
        (void)Dio_WriteChannel(Mcu_Dio_PortId[PWRCTRL_CFG_PRIVATE_PORT_WAKEUP_STAT1], u1_s_PwrCtrl_Sip_WAKEUP_STAT1);
    }
    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlSipSoCOnError
  Description   : SIP共通 SoC異常検知時のWAKEUP-STAT2設定関数
  param[in/out] : -
  return        : -
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlSipSoCOnError(void)
{
    /* WALEUP-STAT2設定用情報を保存 */
    u1_s_PwrCtrl_Sip_WAKEUP_STAT2 = (U1)MCU_DIO_HIGH;
    vd_g_Rim_WriteU1((U2)RIMID_U1_PWCTR_SOC_WU_STAT2, u1_s_PwrCtrl_Sip_WAKEUP_STAT2);

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSipForcedOffInitReq
  Description   : 5-6.SIP電源強制OFFシーケンス 共通部分の初期化
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSipForcedOffInitReq( void )
{
    u1_s_PwrCtrl_Sip_Pwr_Sts                           = (U1)PWRCTRL_SIP_STS_FORCEDOFF;
    u1_s_PwrCtrl_Sip_FOff_Sts                          = (U1)PWRCTRL_SIP_FORCEDOFF_NON;

    /* 他処理の無効化 */
    u1_s_PwrCtrl_Sip_On_Step                           = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Rsm_Step                          = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Off_Step                          = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Stby_Step                         = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;

    /* 待機時間測定用RAMの初期化 */
    u4_s_PwrCtrl_Sip_ForcedOff_PMICFASTPOFF_Tim        = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_POFF_COMPLETE_N_Chk_Tim = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_PMRESIN_HiChk_Tim       = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_PMRESIN_LoChk_Tim       = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_VB33_SIP_FREQ_Tim       = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_LOW_POWER_ON_Tim        = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_VB33_SIP_ON_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_PM_PWR_EN_N_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_PM_RESIN_Step6_Tim      = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_PMICFASTPOFF_Step6_Tim  = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_MM_SUSPEND_REQ_N_Tim    = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_STR_WAKE_Tim            = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_MM_OFF_REQ_Tim          = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_DDConvOFFWait_Tim       = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_POFFCOMP_Wait_Tim       = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_ForcedOff_POFFCOMP_Wait_Step4_Tim = (U4)PWRCTRL_SIP_TIME_INIT;

    /* SIP入力DDコン電源OFF処理未実施状態を設定 */
    u1_s_PwrCtrl_Sip_DDConvFlag                        = (U1)PWRCTRL_SIP_FOFF_DDCONV_OFF;

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlSipMainFunc
  Description   : 6-8-1,6-8-2,6-9,5-3,SIP電源定期処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlSipMainFunc( void )
{
    /* 【todo】u1_s_PwrCtrl_Sip_Pwr_Stsで各制御を実行する */
    /* 理由：同時に各制御を実行することはないため */
    switch ( u1_s_PwrCtrl_Sip_Pwr_Sts )
    {
        case (U1)PWRCTRL_SIP_STS_PWRON:        /* SIP通常起動制御 */
            vd_s_PwrCtrlSipOnMainFunc();
            break;

        case (U1)PWRCTRL_SIP_STS_RESUME:       /* SIPレジューム制御 */
            vd_s_PwrCtrlSipRsmMainFunc();
            break;

        case (U1)PWRCTRL_SIP_STS_PWROFF:       /* SIP電源OFF制御 */
            vd_s_PwrCtrlSipOffMainFunc();
            break;

        case (U1)PWRCTRL_SIP_STS_STANDBY:      /* スタンバイシーケンス */
            vd_s_PwrCtrlSipStbyMainFunc();
            break;

        case (U1)PWRCTRL_SIP_STS_BUDET:        /* BU-DET処理 */
            /* 【todo】6-5.BU-DET処理 */
            break;

        case (U1)PWRCTRL_SIP_STS_FORCEDOFF:    /* SIP電源強制OFFシーケンス */
            vd_s_PwrCtrlSipForcedOffMainFunc();
            break;

        default:
            /* 未定義の要求が通知された場合は何もしない */
            break;
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSipOnMainFunc
  Description   : 6-8-1.SIP通常起動制御_定期処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSipOnMainFunc( void )
{
    /* PM_PWR_EN_N=Lo(Step3-1)からの経過時間 */
    if(u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Step3_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
        if(u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Lo_ElapsedTim >= (U4)PWRCTRL_SIP_ON_T_PM_PWR_EN_N_ELPSD){
            u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Lo_ElapsedTim = (U4)PWRCTRL_SIP_ON_T_PM_PWR_EN_N_ELPSD; /* 最大値でガード */
        }
        else{
            u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Lo_ElapsedTim++; /* Step3-1完了後、次の周期からカウント */
        }
    }
    vd_s_PwrCtrlSipOnStep1(); /* SiPへの電源供給開始 */
    vd_s_PwrCtrlSipOnStep2(); /* POFF_COMPLETE_N、AOSS_SLEEP_ENTRY_EXITの初期値チェック */
    vd_s_PwrCtrlSipOnStep3(); /* PM_PWR_EN_N = Lo設定 */
    vd_s_PwrCtrlSipOnStep4(); /* PMA_PS_HOLD初期値チェック */
    vd_s_PwrCtrlSipOnStep5(); /* SOC PMICによるSIP内部電源ONチェック */
    vd_s_PwrCtrlSipOnStep6(); /* SOCリセット解除正常完了チェック */
    vd_s_PwrCtrlSipOnStep7(); /* SOCのハードウェア起動チェック */
    vd_s_PwrCtrlSipOnStep8(); /* PM_PWR_EN_N = Hi設定 */
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSipOnStep1
  Description   : 6-8-1.SIP通常起動制御_STEP1処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSipOnStep1( void )
{
/* SiPへの電源供給開始など */
    if(u1_s_PwrCtrl_Sip_On_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP1){
        /* VB-33-SIP-ON = Hi */
        vd_s_PwrCtrlSipOnVB33SIPON();               /* STEP1-1      */
        /* LOW-POWER-ON = Lo(SIP電源投入と合わせてLo論理確定)       */
        vd_s_PwrCtrlSipOnLOWPOWERON1();             /* STEP1-2      */
        /* VB33-SIP-FREQ = Lo(SIP電源投入と合わせてLo論理確定)      */
        vd_s_PwrCtrlSipOnVB33SIPFREQ1();            /* STEP1-3      */
        /* PM_PWR_EN_N = Hi(SIP電源投入と合わせてHi論理確定)        */
        vd_s_PwrCtrlSipOnPMPWREN1();                /* STEP1-4      */
        /* PMIC_FAST_POFF_MIN = Lo(SIP電源投入と合わせてLo論理確定) */
        vd_s_PwrCtrlSipOnPMICFASTPOFF1();           /* STEP1-5      */
        /* MM_OFF_REQ = Lo(SIP電源投入と合わせてLo論理確定)         */
        vd_s_PwrCtrlSipOnMMOFFREQ();                /* STEP1-6      */

        /* STEP1-1～STEP1-6が完了していれば次のSTEPに進める */
        if((u4_s_PwrCtrl_Sip_On_VB33SIPON_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_On_LOPWON_S1_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_On_SIPFRQ_S1_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Step1_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_On_PMIC_FAST_POFF_EN_N_Step1_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_On_MM_OFF_REQ_Step1_Tim == (U4)PWRCTRL_SIP_TIME_INVALID)){
            u1_s_PwrCtrl_Sip_On_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP2;
        }
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSipOnStep2
  Description   : 6-8-1.SIP通常起動制御_STEP2処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSipOnStep2( void )
{
    if(u1_s_PwrCtrl_Sip_On_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP2){
        /* VB-33-SIP-ON = HiからtLOW-POWER-ON_HI経過後にLOW-POWER-ON = Hi */
        vd_s_PwrCtrlSipOnLOWPOWERON2();                 /* STEP2-1 */
/* Wait 35ms(電圧安定のため)*/
/* POFF_COMPLETE_N&AOSS_SLEEP_ENTRY_EXIT=Lo */
        /* VB-33-SIP-ON = Hiから35ms後に初期値(AOSS_SLEEP_ENTRY_EXIT=Lo)チェック */
        vd_s_PwrCtrlSipOnInitValChkAOSS();              /* STEP2-2 */

#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_BON_STEP2_2; /* TP */
#endif

        /* VB-33-SIP-ON = Hiから35ms後に初期値(POFF_COMPLETE_N=Lo)チェック */
        vd_s_PwrCtrlSipOnInitChkPOFFCOMP();             /* STEP2-3 */

#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_BON_STEP2_3; /* TP */
#endif
        
        /* STEP2-1が完了していれば次の処理に進める */
        if(u4_s_PwrCtrl_Sip_On_LOW_POWER_ON_Step2_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
            /* LOW-POWER-ON_HIを検知時に端子モニタ開始を設定 */
            u1_s_PwrCtrl_Sip_LOW_POWER_ON_Sts = (U1)TRUE;
            
            /* LOW-POWER-ON_HIからtVB33-SIP-FREQ_HI経過後にVB33-SIP-FREQ = HI */
            vd_s_PwrCtrlSipOnVB33SIPFREQ2();            /* STEP2-4 */
        }
        
        /* STEP2-2~STEP2-4が完了していれば次のSTEPに進める */
#ifndef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF
        if((u4_s_PwrCtrl_Sip_On_AOSS_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_On_POFF_COMPLETE_N_Init_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_On_VB33_SIP_FREQ_Step2_Tim == (U4)PWRCTRL_SIP_TIME_INVALID)){
#else
        if(((u4_s_PwrCtrl_Sip_On_AOSS_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
            (u4_s_PwrCtrl_Sip_On_POFF_COMPLETE_N_Init_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
            (u4_s_PwrCtrl_Sip_On_VB33_SIP_FREQ_Step2_Tim == (U4)PWRCTRL_SIP_TIME_INVALID)) ||
            ((u1_g_PwrCtrl_Main_DbgFailOffFlag == (U1)MCU_DIO_LOW) &&
            (u4_s_PwrCtrl_Sip_On_AOSS_Tim >= (U4)PWRCTRL_SIP_ON_T_AOSS) &&
            (u4_s_PwrCtrl_Sip_On_POFF_COMPLETE_N_Init_Tim >= (U4)PWRCTRL_SIP_ON_T_POFF_COMPLETE_N))){
#endif
            u1_s_PwrCtrl_Sip_On_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP3;
            u4_s_PwrCtrl_Sip_On_POFFCOMP_Wait_Tim = (U4)PWRCTRL_SIP_TIME_INIT;
           }

        /* STEP2-2、2-3が50ms経過しても完了してなければSTEPを完了させる */
        else{
            if((u4_s_PwrCtrl_Sip_On_AOSS_Wait_Tim > PWRCTRL_SIP_ON_WAIT_POFFCOMP_AOSS) ||
              (u4_s_PwrCtrl_Sip_On_POFFCOMP_Wait_Tim > PWRCTRL_SIP_ON_WAIT_POFFCOMP_AOSS)){
                /* 強制OFFシーケンス(DDコンOFF)要求を設定 */
                u1_s_PwrCtrl_Sip_FOff_Sts = (U1)PWRCTRL_SIP_FORCEDOFF_DDCONV;
                /* 【todo】異常内容の保存[ID0001/0002] */
                /* SoC異常検知の設定 */
                vd_g_PwrCtrlSipSoCOnError();
            }
        }
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSipOnStep3
  Description   : 6-8-1.SIP通常起動制御_STEP3処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSipOnStep3( void )
{
    if(u1_s_PwrCtrl_Sip_On_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP3){
/* PM_PWR_EN_N=Lo */
        /* AOSS_SLEEP_NETRY_EXIT,POFF_COMPLETE_N初期値チェックからtPM_PWR_EN_N_LO経過後にPM_PWR_EN_N = Lo */
        vd_s_PwrCtrlSipOnPMPWREN2();                           /* STEP3-1 */

        /* STEP3-1が完了していれば次のSTEPに進める */
        if(u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Step3_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
            u1_s_PwrCtrl_Sip_On_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP4;
            /* SoC起動通知(PM_PWR_EN_N = Lo) */
            vd_g_PwrCtrlComTxSetSoCOnStart();
        }
    }
        
    if(u1_s_PwrCtrl_Sip_On_Step >= (U1)PWRCTRL_COMMON_PROCESS_STEP3){
        /* STEP3以降のSTEP時に並行して処理を行い、シーケンスの完了判定前(STEP9)に完了しているか確認する */
        /* AOSS_SLEEP_NETRY_EXIT,POFF_COMPLETE_N初期値チェックからtPMIC_FAST_POFF_EN_N_HI経過後にPMIC_FAST_POFF_EN_N = Hi */
        vd_s_PwrCtrlSipOnPMICFASTPOFF2();           /* STEP3-2 */
        /* AOSS_SLEEP_NETRY_EXIT,POFF_COMPLETE_N初期値チェックからtMM-SUSPEND_REQ_N経過後にMM-SUSPEND_REQ_N = Hi */
        vd_s_PwrCtrlSipOnMMSUSPEND();               /* STEP3-3 */
        /* AOSS_SLEEP_NETRY_EXIT,POFF_COMPLETE_N初期値チェックからtSTR_WAKE経過後にSTR_WAKE = Hi */
        vd_s_PwrCtrlSipOnSTRWAKE();                 /* STEP3-4 */
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSipOnStep4
  Description   : 6-8-1.SIP通常起動制御_STEP4処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSipOnStep4( void )
{
    if(u1_s_PwrCtrl_Sip_On_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP4){
/* PMA_PS_HOLD=Lo */
        /* PMA_PS_HOLD初期値(Lo)チェック */
        vd_s_PwrCtrlSipOnInitChkPSHOLD();          /* STEP4-1 */

#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_BON_STEP4_1; /* TP */
#endif

        /* STEP4-1が完了していれば次の処理に進める */
#ifndef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF
        if(u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Init_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
#else
        if((u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Init_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) ||
           (u1_g_PwrCtrl_Main_DbgFailOffFlag == (U1)MCU_DIO_LOW)){
#endif
            u1_s_PwrCtrl_Sip_On_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP5;
            u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Wait_Tim = (U4)PWRCTRL_SIP_TIME_INIT;
        }

        else{
            /* STEP4-1が300ms経過しても完了してなければSTEPを完了させる */
            if(u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Wait_Tim > (U4)PWRCTRL_SIP_ON_WAIT_PMA_PS_HOLD_LO){
                /* 強制OFFシーケンス(SoC異常)要求を設定 */
                u1_s_PwrCtrl_Sip_FOff_Sts = (U1)PWRCTRL_SIP_FORCEDOFF_SOCERR;
                /* 【todo】異常内容の保存[ID0003] */
                /* SoC異常検知の設定 */
                vd_g_PwrCtrlSipSoCOnError();
            }
        }

    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSipOnStep5
  Description   : 6-8-1.SIP通常起動制御_STEP5処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSipOnStep5( void )
{
    if(u1_s_PwrCtrl_Sip_On_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP5){
/* POFF_COMPLETE_N=Hi */
        /* PMA_PS_HOLD = Lo後にPOFF_COMPLETE_N変化(Lo→Hi)チェック */
        vd_s_PwrCtrlSipOnValChkPOFFCOMP();         /* STEP5-1 */

#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_BON_STEP5_1; /* TP */
#endif

        /* STEP5-1が完了していれば次の処理に進める */
#ifndef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF
        if(u4_s_PwrCtrl_Sip_On_POFF_COMPLETE_N_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
#else
        if((u4_s_PwrCtrl_Sip_On_POFF_COMPLETE_N_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) ||
           (u1_g_PwrCtrl_Main_DbgFailOffFlag == (U1)MCU_DIO_LOW)){
#endif
            u1_s_PwrCtrl_Sip_On_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP6;
            /* EtherSW起動要求を設定 */
            u1_s_PwrCtrl_Sip_EthReq_Sts = (U1)PWRCTRL_ETH_REQ_ON;

            /* 【todo】5-9. PM_PSAIL_ERR_N監視処理開始 */
            /* 【todo】4.0版参照 5-12-1. PGOOD_ASIL_VB監視処理開始 4.0版参照 */

        }
        
        else{
            /* STEP5-1が300ms経過しても完了してなければSTEPを完了させる */
            if(u4_s_PwrCtrl_Sip_On_POFFCOMP_Wait_Tim > (U4)PWRCTRL_SIP_ON_WAIT_POFFCOMP){
                /* 強制OFFシーケンス(PMIC異常)要求を設定 */
                u1_s_PwrCtrl_Sip_FOff_Sts = (U1)PWRCTRL_SIP_FORCEDOFF_PMICERR;
                /* 【todo】異常内容の保存[ID0004] */
                /* SoC異常検知の設定 */
                vd_g_PwrCtrlSipSoCOnError();
            }
        }
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSipOnStep6
  Description   : 6-8-1.SIP通常起動制御_STEP6処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSipOnStep6( void )
{
    if(u1_s_PwrCtrl_Sip_On_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP6){
/* SOC_RESOUT_N & SAIL_RESOUT_N=Hi */
        /* POFF_COMPLETE_N変化(Hi)後にSOC_RESOUT_N変化(Hi)チェック */
        vd_s_PwrCtrlSipOnValChkSOCRSOUT();        /* STEP6-1 */

#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_BON_STEP6_1; /* TP */
#endif

        /* POFF_COMPLETE_N変化(Hi)後にSAIL_RESOUT_N変化(Hi)チェック */
        vd_s_PwrCtrlSipOnValChkSAILRSOUT();       /* STEP6-2 */

#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_BON_STEP6_2; /* TP */
#endif
       
        /* STEP6-1,6-2が完了していれば次の処理に進める */
#ifndef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF
        if((u4_s_PwrCtrl_Sip_On_SOC_RESOUT_N_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_On_SAIL_RESOUT_N_Tim == (U4)PWRCTRL_SIP_TIME_INVALID)){
#else
        if(((u4_s_PwrCtrl_Sip_On_SOC_RESOUT_N_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
            (u4_s_PwrCtrl_Sip_On_SAIL_RESOUT_N_Tim == (U4)PWRCTRL_SIP_TIME_INVALID)) ||
            (u1_g_PwrCtrl_Main_DbgFailOffFlag == (U1)MCU_DIO_LOW)){
#endif
            u1_s_PwrCtrl_Sip_On_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP7;
            /* 計測点③SoC起動設定(SOC_RESOUT_N & SAIL_RESOUT_N=Hi) */
            vd_g_PwrCtrlComTxSetBootLog((U1)PWRCTRL_COM_BOOTLOG_BONREQ);
        }

        else{
            /* STEP6-1、6-2が200ms経過しても完了してなければSTEPを完了させる */
            if((u4_s_PwrCtrl_Sip_On_SOC_RESOUT_Wait_Tim > (U4)PWRCTRL_SIP_ON_WAIT_SOC_SAIL_RES) ||
              (u4_s_PwrCtrl_Sip_On_SAIL_RESOUT_Wait_Tim > (U4)PWRCTRL_SIP_ON_WAIT_SOC_SAIL_RES)){
                /* 強制OFFシーケンス(PMIC異常)要求を設定 */
                u1_s_PwrCtrl_Sip_FOff_Sts = (U1)PWRCTRL_SIP_FORCEDOFF_PMICERR;
                /* 【todo】異常内容の保存[ID0005/0006] */
                /* SoC異常検知の設定 */
                vd_g_PwrCtrlSipSoCOnError();
            }
        }
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSipOnStep7
  Description   : 6-8-1.SIP通常起動制御_STEP7処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSipOnStep7( void )
{
    if(u1_s_PwrCtrl_Sip_On_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP7){
/* PMA_PS_HOLD=Hi */
        /* SOC_RESOUT_N & SAIL_RESOUT_N=Hi変化後にPMA_PS_HOLD変化(Hi)チェック */
        vd_s_PwrCtrlSipOnValChkPSHOLD();     /* STEP7-1 */

#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_BON_STEP7_1; /* TP */
#endif

        /* STEP7-1が完了、かつSTEP3-1から50ms経過していれば次の処理に進める */
#ifndef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF
        if((u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Lo_ElapsedTim == (U4)PWRCTRL_SIP_ON_T_PM_PWR_EN_N_ELPSD)){
#else
        if(((u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
            (u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Lo_ElapsedTim == (U4)PWRCTRL_SIP_ON_T_PM_PWR_EN_N_ELPSD)) ||
           ((u1_g_PwrCtrl_Main_DbgFailOffFlag == (U1)MCU_DIO_LOW) &&
            (u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Lo_ElapsedTim == (U4)PWRCTRL_SIP_ON_T_PM_PWR_EN_N_ELPSD))){
#endif
            u1_s_PwrCtrl_Sip_On_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP8;

            /* 【todo】5-10. PMA_PS_HOLD監視処理開始 */
            /* 【todo】5-7. SAIL UART Message監視開始 */

        }

        else{
            /* STEP8-1が200ms経過しても完了してなければSTEPを完了させる */
            if(u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Wait_Tim > (U4)PWRCTRL_SIP_ON_WAIT_PMA_PS_HOLD_HI){
                /* 強制OFFシーケンス(SoC異常)要求を設定 */
                u1_s_PwrCtrl_Sip_FOff_Sts = (U1)PWRCTRL_SIP_FORCEDOFF_SOCERR;
                /* 【todo】異常内容の保存[ID0007] */
                /* SoC異常検知の設定 */
                vd_g_PwrCtrlSipSoCOnError();
            }
        }
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSipOnStep8
  Description   : 6-8-1.SIP通常起動制御_STEP8処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSipOnStep8( void )
{
    if(u1_s_PwrCtrl_Sip_On_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP8){
/* PM_PWR_EN_N=Hi */
        /* STEP7完了後tPM_PWR_EN_N_HI_P2経過後にPM_PWR_EN_N = Hi */
        vd_s_PwrCtrlSipOnPMPWREN3();         /* STEP8-1 */

        /* STEP8-1とSTEP3-2~STEP3-4が完了していればBONシーケンス完了とする */
        if((u4_s_PwrCtrl_Sip_On_PMIC_FAST_POFF_EN_N_Step3_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_On_MM_SUSPEND_REQ_N_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_On_STR_WAKE_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Step8_Tim == (U4)PWRCTRL_SIP_TIME_INVALID)){
            u1_s_PwrCtrl_Sip_On_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
            u1_s_PwrCtrl_Sip_Pwr_Sts = (U1)PWRCTRL_SIP_STS_NON;
        }
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSipRsmMainFunc
  Description   : 6-8-2.SIPレジューム制御_定期処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSipRsmMainFunc( void )
{
/* SIPレジューム制御 */
    if(u1_s_PwrCtrl_Sip_Rsm_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP1){
        /* 起動判断(SIPレジューム)からtLOW-POWER-ON経過後にLOW-POWER-ON = Hi */
        vd_s_PwrCtrlSipRsmLOWPOWERON();         /* STEP1-1 */
        
        /* STEP1-1が完了していれば次のSTEPに進める */
        if(u4_s_PwrCtrl_Sip_Rsm_LOW_POWER_ON_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
            /* LOW-POWER-ON_HIを検知 */
            u1_s_PwrCtrl_Sip_LOW_POWER_ON_Sts = (U1)TRUE;
            u1_s_PwrCtrl_Sip_Rsm_Step     = (U1)PWRCTRL_COMMON_PROCESS_STEP2;
        }
    }
    
    if(u1_s_PwrCtrl_Sip_Rsm_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP2){
        /* LOW-POWER-ON = HiからtVB33-SIP-FREQ経過後にVB33-SIP-FREQ = Hi */
        vd_s_PwrCtrlSipRsmVB33SIPFREQ();         /* STEP2-1 */
        
        /* STEP2-1が完了していれば次のSTEPに進める */
        if(u4_s_PwrCtrl_Sip_Rsm_VB33_SIP_FREQ_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
            u1_s_PwrCtrl_Sip_Rsm_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP3;
        }
    }
    
    if(u1_s_PwrCtrl_Sip_Rsm_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP3){
        /* VB33-SIP-FREQ = HiからtMM_SUSPEND_REQ_N経過後にMM_SUSPEND_REQ_N = Hi */
        vd_s_PwrCtrlSipRsmMMSUSPEND();           /* STEP3-1 */
        /* VB33-SIP-FREQ = HiからtSTR_WAKE経過後にSTR_WAKE = Hi */
        vd_s_PwrCtrlSipRsmSTRWAKE();             /* STEP3-2 */

        /* STEP3-1とSTEP3-2が完了していれば次のSTEPに進める */
        if((u4_s_PwrCtrl_Sip_Rsm_MM_SUSPEND_REQ_N_Tim == (U4)PWRCTRL_SIP_TIME_INVALID)&&
           (u4_s_PwrCtrl_Sip_Rsm_STR_WAKE_Tim == (U4)PWRCTRL_SIP_TIME_INVALID)){
            u1_s_PwrCtrl_Sip_Rsm_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
            u1_s_PwrCtrl_Sip_Pwr_Sts  = (U1)PWRCTRL_SIP_STS_NON;
            /* SoC起動通知(STR_WAKE = Hi) */
            vd_g_PwrCtrlComTxSetSoCOnStart();
            /* 計測点③'STRWake時設定(STR_WAKE = Hi) */
            vd_g_PwrCtrlComTxSetBootLog((U1)PWRCTRL_COM_BOOTLOG_STRREQ);
        }
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSipOffMainFunc
  Description   : 6-9.SIP電源OFF制御_定期処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSipOffMainFunc( void )
{
    vd_s_PwrCtrlSipOffStep1(); /* MM_OFF_REQ = Lo設定 */
    vd_s_PwrCtrlSipOffStep2(); /* MM_STBY_N応答チェック(TEN/DNソフトウェア終了処理完了確認) */
    vd_s_PwrCtrlSipOffStep3(); /* PMA_PS_HOLD応答チェック(SOCシャットダウン完了確認) */
    vd_s_PwrCtrlSipOffStep4(); /* SOC_RESOUT_N SAIL_RESOUT_N POFF_COMPLETE_N応答チェック(SOCリセット処理、およびSIP電源OFF完了確認) */
    vd_s_PwrCtrlSipOffStep5(); /* SIP入力DDコン電源OFF処理 */
    vd_s_PwrCtrlSipOffStep6(); /* SIP入力DDコン電源OFF処理 */
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSipOffStep1
  Description   : 6-9.SIP電源OFF制御_STEP1処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSipOffStep1( void )
{
    if(u1_s_PwrCtrl_Sip_Off_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP1){
        vd_s_PwrCtrlSipOffMMOFFREQ1(); /* STEP1-1 */
        
        /* STEP1-1が完了していれば次のSTEPに進める */
        if(u4_s_PwrCtrl_Sip_Off_MM_OFF_REQ_Step1_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
            u1_s_PwrCtrl_Sip_Off_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP2;
        }
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSipOffStep2
  Description   : 6-9.SIP電源OFF制御_STEP2処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSipOffStep2( void )
{
/* MM_STBY_N =Lo? */
    if(u1_s_PwrCtrl_Sip_Off_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP2){
        vd_s_PwrCtrlSipOffValChkMMSTBY();         /* STEP2-1 */

#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_SIPOFF_STEP2_1; /* TP */
#endif

        /* STEP2-1が完了していれば次の処理に進める */
#ifndef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF
        if (u4_s_PwrCtrl_Sip_Off_MM_STBY_N_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
#else
        if ((u4_s_PwrCtrl_Sip_Off_MM_STBY_N_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) ||
            (u1_g_PwrCtrl_Main_DbgFailOffFlag == (U1)MCU_DIO_LOW)){
#endif
            u1_s_PwrCtrl_Sip_Off_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP3;
        }
        else{
            /* STEP2-1が100秒経過しても完了してなければSTEPを完了させる */
            if(u4_s_PwrCtrl_Sip_Off_MM_STBY_Wait_Tim > (U4)PWRCTRL_SIP_OFF_WAIT_MM_STBY){
                /* 強制OFFシーケンス(SoC異常)要求を設定 */
                u1_s_PwrCtrl_Sip_FOff_Sts = (U1)PWRCTRL_SIP_FORCEDOFF_SOCERR;
                /* 【todo】異常内容の保存[ID0015] */
                /* SoC異常検知の設定 */
                vd_g_PwrCtrlSipSoCOnError();
            }
        }
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSipOffStep3
  Description   : 6-9.SIP電源OFF制御_STEP3処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSipOffStep3( void )
{
/* PMA_PS_HOLD =Lo? */
    if(u1_s_PwrCtrl_Sip_Off_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP3){
        vd_s_PwrCtrlSipOffValChkPSHOLD(); /* STEP3-1 */

#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_SIPOFF_STEP3_1; /* TP */
#endif

        /* STEP3-1が完了していれば次の処理に進める */
#ifndef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF
        if (u4_s_PwrCtrl_Sip_Off_PMA_PS_HOLD_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
#else
        if ((u4_s_PwrCtrl_Sip_Off_PMA_PS_HOLD_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) ||
            (u1_g_PwrCtrl_Main_DbgFailOffFlag == (U1)MCU_DIO_LOW)){
#endif
            u1_s_PwrCtrl_Sip_Off_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP4;
        }
        
        else{
            /* STEP3-1が3秒経過しても完了してなければSTEPを完了させる */
            if(u4_s_PwrCtrl_Sip_Off_PMA_PS_HOLD_Wait_Tim > (U4)PWRCTRL_SIP_OFF_WAIT_PMA_PS_HOLD){
                /* 強制OFFシーケンス(SoC異常)要求を設定 */
                u1_s_PwrCtrl_Sip_FOff_Sts = (U1)PWRCTRL_SIP_FORCEDOFF_SOCERR;
                /* 【todo】異常内容の保存[ID0016] */
                /* SoC異常検知の設定 */
                vd_g_PwrCtrlSipSoCOnError();
            }
        }
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSipOffStep4
  Description   : 6-9.SIP電源OFF制御_STEP4処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSipOffStep4( void )
{
    U1 u1_t_socres_lv;        /* SOC_RESOUT_N  リード結果 */
    U1 u1_t_sailres_lv;       /* SAIL_RESOUT_N リード結果 */

/* SOC_RESOUT_N & SAIL_RESOUT_N & POFF_COMPLETE_N =Lo? */
    if(u1_s_PwrCtrl_Sip_Off_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP4){
        vd_s_PwrCtrlSipOffValChkSOCRSOUT(); /* STEP4-1 */

#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_SIPOFF_STEP4_1; /* TP */
#endif

        vd_s_PwrCtrlSipOffValChkSAILROUT(); /* STEP4-2 */

#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_SIPOFF_STEP4_2; /* TP */
#endif

        vd_s_PwrCtrlSipOffValChkPOFFCOMP(); /* STEP4-3 */

#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_SIPOFF_STEP4_3; /* TP */
#endif

        /* STEP4-1~4-3が完了していれば次の処理に進める */
#ifndef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF
        if((u4_s_PwrCtrl_Sip_Off_SOC_RESOUT_N_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_Off_SAIL_RESOUT_N_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_Off_POFF_COMPLETE_N_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID)){
#else
        if(((u4_s_PwrCtrl_Sip_Off_SOC_RESOUT_N_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
            (u4_s_PwrCtrl_Sip_Off_SAIL_RESOUT_N_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
            (u4_s_PwrCtrl_Sip_Off_POFF_COMPLETE_N_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID)) ||
            ((u1_g_PwrCtrl_Main_DbgFailOffFlag == (U1)MCU_DIO_LOW) &&
            (u4_s_PwrCtrl_Sip_Off_POFF_COMPLETE_N_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID))){
#endif
             u1_s_PwrCtrl_Sip_Off_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP5;
        }
        else{
#ifndef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF
            /* STEP4-1~4-3が100ms経過しても完了してなければSTEPを完了させる */
            if((u4_s_PwrCtrl_Sip_Off_SOC_RESOUT_N_Wait_Tim > (U4)PWRCTRL_SIP_OFF_WAIT_SOC_RESOUT_N)  ||
              (u4_s_PwrCtrl_Sip_Off_SAIL_RESOUT_N_Wait_Tim > (U4)PWRCTRL_SIP_OFF_WAIT_SAIL_RESOUT_N) ||
              (u4_s_PwrCtrl_Sip_Off_POFF_COMPLETE_N_Wait_Tim > (U4)PWRCTRL_SIP_OFF_WAIT_POFF_COMP)){
                
                /* 【todo】異常内容の保存[ID0017/0018/0019] */
                /* SoC異常検知の設定 */
                vd_g_PwrCtrlSipSoCOnError();
                
                /* SAIL_RESOUT_N & SoC_RESOUT_N =Loチェックを行う */
                u1_t_socres_lv  = u1_g_PwrCtrl_PinMonitor_GetPinInfo((U1)PWRCTRL_CFG_PRIVATE_KIND_SOC_RESOUT_N);
                u1_t_sailres_lv = u1_g_PwrCtrl_PinMonitor_GetPinInfo((U1)PWRCTRL_CFG_PRIVATE_KIND_SAIL_RESOUT_N);
                
                if((u1_t_socres_lv == (U1)MCU_DIO_LOW) && 
                  (u1_t_sailres_lv == (U1)MCU_DIO_LOW)){
                   /* SAIL_RESOUT_N & SoC_RESOUT_N =Loであれば強制OFFシーケンス(PMIC異常)へ移行 */
                   u1_s_PwrCtrl_Sip_FOff_Sts = (U1)PWRCTRL_SIP_FORCEDOFF_PMICERR;
                }
                else{
                   /* SAIL_RESOUT_N & SoC_RESOUT_N =Loでなければ強制OFFシーケンス(SOC異常)へ移行 */
                   u1_s_PwrCtrl_Sip_FOff_Sts = (U1)PWRCTRL_SIP_FORCEDOFF_SOCERR;
                }
            }
#else
            if(u1_g_PwrCtrl_Main_DbgFailOffFlag == (U1)MCU_DIO_HIGH){
                /* STEP4-1~4-3が100ms経過しても完了してなければSTEPを完了させる */
                if((u4_s_PwrCtrl_Sip_Off_SOC_RESOUT_N_Wait_Tim > (U4)PWRCTRL_SIP_OFF_WAIT_SOC_RESOUT_N)  ||
                  (u4_s_PwrCtrl_Sip_Off_SAIL_RESOUT_N_Wait_Tim > (U4)PWRCTRL_SIP_OFF_WAIT_SAIL_RESOUT_N) ||
                  (u4_s_PwrCtrl_Sip_Off_POFF_COMPLETE_N_Wait_Tim > (U4)PWRCTRL_SIP_OFF_WAIT_POFF_COMP)){
                
                    /* 【todo】異常内容の保存[ID0017/0018/0019] */
                    /* SoC異常検知の設定 */
                    vd_g_PwrCtrlSipSoCOnError();
                    
                    /* SAIL_RESOUT_N & SoC_RESOUT_N =Loチェックを行う */
                    u1_t_socres_lv  = u1_g_PwrCtrl_PinMonitor_GetPinInfo((U1)PWRCTRL_CFG_PRIVATE_KIND_SOC_RESOUT_N);
                    u1_t_sailres_lv = u1_g_PwrCtrl_PinMonitor_GetPinInfo((U1)PWRCTRL_CFG_PRIVATE_KIND_SAIL_RESOUT_N);
                    
                    if((u1_t_socres_lv == (U1)MCU_DIO_LOW) && 
                      (u1_t_sailres_lv == (U1)MCU_DIO_LOW)){
                       /* SAIL_RESOUT_N & SoC_RESOUT_N =Loであれば強制OFFシーケンス(PMIC異常)へ移行 */
                       u1_s_PwrCtrl_Sip_FOff_Sts = (U1)PWRCTRL_SIP_FORCEDOFF_PMICERR;
                    }
                    else{
                       /* SAIL_RESOUT_N & SoC_RESOUT_N =Loでなければ強制OFFシーケンス(SOC異常)へ移行 */
                       u1_s_PwrCtrl_Sip_FOff_Sts = (U1)PWRCTRL_SIP_FORCEDOFF_SOCERR;
                    }
                }
            }
#endif
        }
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSipOffStep5
  Description   : 6-9.SIP電源OFF制御_STEP5処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSipOffStep5( void )
{
    if(u1_s_PwrCtrl_Sip_Off_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP5){
        vd_s_PwrCtrlSipOffVB33SIPFREQ(); /* STEP5-1 */

        /* STEP5-1が完了していれば次のSTEPに進める */
        if (u4_s_PwrCtrl_Sip_Off_VB33_SIP_FREQ_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
            u1_s_PwrCtrl_Sip_Off_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP6;
        }
    }

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSipOffStep6
  Description   : 6-9.SIP電源OFF制御_STEP6処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSipOffStep6( void )
{
    if(u1_s_PwrCtrl_Sip_Off_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP6){
        vd_s_PwrCtrlSipOffVB33SIPON();       /* STEP6-1 */
        vd_s_PwrCtrlSipOffLOWPOWERON();      /* STEP6-2 */
        vd_s_PwrCtrlSipOffPMPWREN();         /* STEP6-3 */
        vd_s_PwrCtrlSipOffPMRESIN();         /* PM_RESIN端子 Lo設定 */
        vd_s_PwrCtrlSipOffPMICFASTPOFF();    /* STEP6-4 */
        vd_s_PwrCtrlSipOffMMSUSPEND();       /* STEP6-5 */
        vd_s_PwrCtrlSipOffSTRWAKE();         /* STEP6-6 */
        vd_s_PwrCtrlSipOffMMOFFREQ2();       /* STEP6-7 */
    
        if(u4_s_PwrCtrl_Sip_Off_LOW_POWER_ON_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
            /* LOW-POWER-ON_LOを検知時に端子モニタ停止を設定 */
            u1_s_PwrCtrl_Sip_LOW_POWER_ON_Sts = (U1)FALSE;
        }

        /* STEP6-1～6-7が完了していれば次のSTEPに進める */
        if((u4_s_PwrCtrl_Sip_Off_VB33_SIP_ON_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_Off_LOW_POWER_ON_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_Off_PM_PWR_EN_N_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_Off_PM_RESIN_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_Off_PMIC_FAST_POFF_EN_N_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_Off_MM_SUSPEND_REQ_N_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_Off_STR_WAKE_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_Off_MM_OFF_REQ_Step6_Tim == (U4)PWRCTRL_SIP_TIME_INVALID)){
            u1_s_PwrCtrl_Sip_Off_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
            u1_s_PwrCtrl_Sip_Pwr_Sts  = (U1)PWRCTRL_SIP_STS_NON;
        }
    }

    return;
}

/*****************************************************************************
  Function      : PwrCtrl_Sip_Stanby_MainFunc
  Description   : 5-3.スタンバイシーケンス_定期処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSipStbyMainFunc( void )
{
    if(u1_s_PwrCtrl_Sip_Stby_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP1){
        vd_s_PwrCtrlSipStbyMMSUSPEND(); /* STEP1-1 */
        vd_s_PwrCtrlSipStbySTRWAKE();       /* STEP1-2 */
            
        /* STEP1-1～STEP1-2が完了していれば次のSTEPに進める */
        if((u4_s_PwrCtrl_Sip_Stby_MM_SUSPEND_REQ_N_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_Stby_STR_WAKE_Tim == (U4)PWRCTRL_SIP_TIME_INVALID)){
            u1_s_PwrCtrl_Sip_Stby_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP2;
        }
    }

/* MM_STBY_N =Lo? */
    if(u1_s_PwrCtrl_Sip_Stby_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP2){
        vd_s_PwrCtrlSipStbyValChkMMSTBY(); /* STEP2-1 */

#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_STANDBY_MMSTBY; /* TP */
#endif

        /* STEP2-1が完了していれば次の処理に進める */
#ifndef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF
        if(u4_s_PwrCtrl_Sip_Stby_MM_STBY_N_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
#else
        if((u4_s_PwrCtrl_Sip_Stby_MM_STBY_N_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) ||
           (u1_g_PwrCtrl_Main_DbgFailOffFlag == (U1)MCU_DIO_LOW)){
#endif
            u1_s_PwrCtrl_Sip_Stby_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP3;
        }

        else
        {
            /* STEP2-1が100秒経過しても完了してなければSTEPを完了させる */
            if(u4_s_PwrCtrl_Sip_Stby_MM_STBY_N_Wait_Tim > (U4)PWRCTRL_SIP_STBY_WAIT_MM_STBY){
                /* 強制OFFシーケンス(SoC異常)要求を設定 */
                u1_s_PwrCtrl_Sip_FOff_Sts = (U1)PWRCTRL_SIP_FORCEDOFF_SOCERR;
                /* 【todo】異常内容の保存[ID0013] */
                /* SoC異常検知の設定 */
                vd_g_PwrCtrlSipSoCOnError();
            }
        }
    }
    
/* AOSS_SLEEP_ENTRY_EXIT = Hi? */
    if(u1_s_PwrCtrl_Sip_Stby_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP3){
        vd_s_PwrCtrlSipStbyValChkAOSS(); /* STEP3-1 */

#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_STANDBY_AOSS; /* TP */
#endif

        /* STEP3-1が完了していれば次の処理に進める */
#ifndef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF
        if(u4_s_PwrCtrl_Sip_Stby_AOSS_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
#else
        if((u4_s_PwrCtrl_Sip_Stby_AOSS_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) ||
           (u1_g_PwrCtrl_Main_DbgFailOffFlag == (U1)MCU_DIO_LOW)){
#endif
            u1_s_PwrCtrl_Sip_Stby_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP4;
        }
        else
        {
            /* STEP3-1が5s経過しても完了してなければSTEPを完了させる */
            if(u4_s_PwrCtrl_Sip_Stby_AOSS_Wait_Tim > (U4)PWRCTRL_SIP_STBY_WAIT_AOSS){
                /* 強制OFFシーケンス(PMIC異常)要求を設定 */
                u1_s_PwrCtrl_Sip_FOff_Sts = (U1)PWRCTRL_SIP_FORCEDOFF_PMICERR;
                /* 【todo】異常内容の保存[ID0014] */
                /* SoC異常検知の設定 */
                vd_g_PwrCtrlSipSoCOnError();
            }
        }
    }
    
    if(u1_s_PwrCtrl_Sip_Stby_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP4){
        vd_s_PwrCtrlSipStbyVB33SIPFREQ(); /* STEP4-1 */
            
        /* STEP4-1が完了していれば次のSTEPに進める */
        if(u4_s_PwrCtrl_Sip_Stby_FREQ_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
            u1_s_PwrCtrl_Sip_Stby_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP5;
        }
    }

    if(u1_s_PwrCtrl_Sip_Stby_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP5){
        vd_s_PwrCtrlSipStbyLOWPOWERON(); /* STEP5-1 */
        
        /* STEP5-1が完了していれば次のSTEPに進める */
        if(u4_s_PwrCtrl_Sip_Stby_LOW_POWER_ON_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
            /* LOW-POWER-ON_LOを検知時に端子モニタ停止を設定 */
            u1_s_PwrCtrl_Sip_LOW_POWER_ON_Sts = (U1)FALSE;
            u1_s_PwrCtrl_Sip_Stby_Step    = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
            u1_s_PwrCtrl_Sip_Pwr_Sts      = (U1)PWRCTRL_SIP_STS_NON;
        }
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSipForcedOffMainFunc
  Description   : 5-6.SIP電源強制OFFシーケンス_定期処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSipForcedOffMainFunc( void )
{
/* SIP電源強制OFF処理(SoC異常)開始 */
    vd_s_PwrCtrlSipForcedOffStep1();
    
/* SIP電源強制OFF処理(PMIC異常)開始 */
    vd_s_PwrCtrlSipForcedOffStep2();
    vd_s_PwrCtrlSipForcedOffStep3();

/* SIP入力DDコンOFF処理開始 */
    vd_s_PwrCtrlSipForcedOffStep4();
    vd_s_PwrCtrlSipForcedOffStep5();
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSipForcedOffStep1
  Description   : 5-6.SIP電源強制OFFシーケンス_STEP1処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSipForcedOffStep1( void )
{
    if(u1_s_PwrCtrl_Sip_ForcedOff_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP1){
        vd_s_PwrCtrlSipFOffPMICFASTPOFF1(); /* STEP1-1 */
/* POFF_COMPLETE_N =Lo? */
        vd_s_PwrCtrlSipFOffValChkPOFFCOMP(); /* STEP1-2 */

        /* STEP1-1とSTEP1-2が完了していればSTEPを完了して起動要因判定に進める */
        if((u4_s_PwrCtrl_Sip_ForcedOff_PMICFASTPOFF_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_ForcedOff_POFF_COMPLETE_N_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID)){
            u1_s_PwrCtrl_Sip_ForcedOff_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
            u1_s_PwrCtrl_Sip_Pwr_Sts        = (U1)PWRCTRL_SIP_STS_NON;
        }

        else{
            /* STEP1-2が100ms経過しても完了していなければ次のSTEPに移行 */
            if(u4_s_PwrCtrl_Sip_ForcedOff_POFFCOMP_Wait_Tim > (U4)PWRCTRL_SIP_FOFF_WAIT_POFF_COMP){
                u1_s_PwrCtrl_Sip_ForcedOff_Step                    = (U1)PWRCTRL_COMMON_PROCESS_STEP2;
                u4_s_PwrCtrl_Sip_ForcedOff_POFF_COMPLETE_N_Chk_Tim = (U4)PWRCTRL_SIP_TIME_INIT;
                /* 【todo】異常内容の保存[ID0020] */
                /* SoC異常検知の設定 */
                vd_g_PwrCtrlSipSoCOnError();
            }
        }
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSipForcedOffStep2
  Description   : 5-6.SIP電源強制OFFシーケンス_STEP2処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSipForcedOffStep2( void )
{
    if(u1_s_PwrCtrl_Sip_ForcedOff_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP2){
        vd_s_PwrCtrlSipFOffPMRESINHI(); /* STEP2-1 */
        
        /* STEP2-1が完了していればSTEP2-2に進める */
        if(u4_s_PwrCtrl_Sip_ForcedOff_PMRESIN_HiChk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
            vd_s_PwrCtrlSipFOffPMRESINLO(); /* STEP2-2 */
        }

        /* STEP2-2が完了していれば次のSTEPに進める */
        if(u4_s_PwrCtrl_Sip_ForcedOff_PMRESIN_LoChk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
            u1_s_PwrCtrl_Sip_ForcedOff_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP3;
        }
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSipForcedOffStep3
  Description   : 5-6.SIP電源強制OFFシーケンス_STEP3処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSipForcedOffStep3( void )
{
/* POFF_COMPLETE_N =Lo? */
    if(u1_s_PwrCtrl_Sip_ForcedOff_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP3){
        vd_s_PwrCtrlSipFOffValChkPOFFCOMP2(); /* STEP3-1 */

        /* STEP3が完了していれば次のSTEPに進める */
        if(u4_s_PwrCtrl_Sip_ForcedOff_POFF_COMPLETE_N_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
            u1_s_PwrCtrl_Sip_ForcedOff_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP4;
        }

        else{
            /* STEP3が5秒経過しても完了していなければ異常内容を保存してから次のSTEPに進める */
            if(u4_s_PwrCtrl_Sip_ForcedOff_POFFCOMP_Wait_Step4_Tim > (U4)PWRCTRL_SIP_FOFF_WAIT_POFF_COMP_P2){
                u1_s_PwrCtrl_Sip_ForcedOff_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP4;
                /* 【todo】異常内容の保存[ID0021] */
                /* SoC異常検知の設定 */
                vd_g_PwrCtrlSipSoCOnError();
            }
        }
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSipForcedOffStep4
  Description   : 5-6.SIP電源強制OFFシーケンス_STEP4処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSipForcedOffStep4( void )
{
    if(u1_s_PwrCtrl_Sip_ForcedOff_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP4){
        vd_s_PwrCtrlSipFOffVB33SIPFREQ(); /* STEP4-1 */

        /* STEP4-1が完了していれば次のSTEPに進める */
        if(u4_s_PwrCtrl_Sip_ForcedOff_VB33_SIP_FREQ_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
            u1_s_PwrCtrl_Sip_ForcedOff_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP5;
        }
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSipForcedOffStep5
  Description   : 5-6.SIP電源強制OFFシーケンス_STEP5処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSipForcedOffStep5( void )
{
    if(u1_s_PwrCtrl_Sip_ForcedOff_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP5){
        vd_s_PwrCtrlSipFOffLOWPOWERON(); /* STEP5-1 */
        
        /* STEP5-1が完了していればSTEP5-2に進める */
        if(u4_s_PwrCtrl_Sip_ForcedOff_LOW_POWER_ON_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
            vd_s_PwrCtrlSipFOffVB33SIPON(); /* STEP5-2 */
        }
        
        /* STEP5-2が完了していればSTEP5-3～STEP5-7に進める */
        if(u4_s_PwrCtrl_Sip_ForcedOff_VB33_SIP_ON_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
            vd_s_PwrCtrlSipFOffPMPWREN();       /* STEP5-3 */
            vd_s_PwrCtrlSipFOffPMRESIN();       /* PM_RESIN端子 Lo設定 */
            vd_s_PwrCtrlSipFOffPMICFASTPOFF2(); /* STEP5-4 */
            vd_s_PwrCtrlSipFOffMMSUSPEND();     /* STEP5-5 */
            vd_s_PwrCtrlSipFOffSTRWAKE();       /* STEP5-6 */
            vd_s_PwrCtrlSipFOffMMOFFREQ();      /* STEP5-7 */
        }

        /* STEP5-3～STEP5-7が完了していれば次のSTEPに進める */
        if((u4_s_PwrCtrl_Sip_ForcedOff_PM_PWR_EN_N_Tim       == (U4)PWRCTRL_SIP_TIME_INVALID) &&
          (u4_s_PwrCtrl_Sip_ForcedOff_PM_RESIN_Step6_Tim     == (U4)PWRCTRL_SIP_TIME_INVALID) &&
          (u4_s_PwrCtrl_Sip_ForcedOff_PMICFASTPOFF_Step6_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
          (u4_s_PwrCtrl_Sip_ForcedOff_MM_SUSPEND_REQ_N_Tim   == (U4)PWRCTRL_SIP_TIME_INVALID) &&
          (u4_s_PwrCtrl_Sip_ForcedOff_STR_WAKE_Tim           == (U4)PWRCTRL_SIP_TIME_INVALID) &&
          (u4_s_PwrCtrl_Sip_ForcedOff_MM_OFF_REQ_Tim         == (U4)PWRCTRL_SIP_TIME_INVALID)){
            /* DDコンに対するOFF区間確保時間の待機 */
            if(u4_s_PwrCtrl_Sip_ForcedOff_DDConvOFFWait_Tim >= (U4)PWRCTRL_SIP_FOFF_T_DDCONV_OFF_WAIT){
               /* 待機時間が満了したら次のSTEPに進める */
               u1_s_PwrCtrl_Sip_ForcedOff_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
               u1_s_PwrCtrl_Sip_DDConvFlag     = (U1)PWRCTRL_SIP_FOFF_DDCONV_ON;
               u1_s_PwrCtrl_Sip_Pwr_Sts        = (U1)PWRCTRL_SIP_STS_NON;
            }
            
            else{
               u4_s_PwrCtrl_Sip_ForcedOff_DDConvOFFWait_Tim++;
            }
        }
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSipDioWriteCheck
  Description   : SIP共通 待ち時間の計測+DIOのWRITE処理実行関数
  param[in/out] :[out] U4 * const u4_a_counter              待ち時間の計測結果を格納
                 [in ] const U1 u1_a_ontime                 待ち時間計測のしきい値
                 [in ] const Dio_ChannelType u2_a_ChannelId DIOのWRITE処理を行うチャンネルID
                 [in ] const Dio_LevelType u1_a_Level       DIOで設定したい出力値
  return        : -
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrl_Sip_DioWriteCheck(U4 * const u4_a_counter , const U1 u1_a_ontime ,
        const Dio_ChannelType u2_a_ChannelId , const Dio_LevelType u1_a_Level)
{
    if(*u4_a_counter != (U4)PWRCTRL_SIP_TIME_INVALID){
        if(*u4_a_counter >= u1_a_ontime){                                       /* u1_a_ontime時間が経過したか */
            (void)Dio_WriteChannel(Mcu_Dio_PortId[u2_a_ChannelId], u1_a_Level); /* 経過していればDIOのWRITE関数をコール */
            *u4_a_counter = (U4)PWRCTRL_SIP_TIME_INVALID;                       /* 待ち時間の測定結果に完了を通知 */
         }
         else{
            (*u4_a_counter)++;                                                  /* 待ち時間のしきい値に達していない場合はカウントをインクリメント */
         }
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrl_Sip_DioReadCheck
  Description   : SIP共通 待ち時間の計測+DIOのREAD処理実行関数
  param[in/out] :[out] U4 * const u4_a_counter        待ち時間の計測結果を格納
                 [out] U4 * const u4_a_wait_counter   待機時間の計測結果を格納
                 [in ] const U1 u1_a_ontime           待ち時間計測のしきい値
                 [in ] const U1 u1_a_PinID            READ処理を行うチャンネルI
                 [in ] const Dio_LevelType u1_a_Level READ結果の照合
  return        : -
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrl_Sip_DioReadCheck(U4 * const u4_a_counter , U4 * const u4_a_wait_counter , const U1 u1_a_ontime ,
        const U1 u1_a_PinID , const Dio_LevelType u1_a_Level)
{
    U1 u1_t_read_lv;

    if(*u4_a_counter != (U4)PWRCTRL_SIP_TIME_INVALID){
        if(*u4_a_counter >= u1_a_ontime){                               /* u1_a_ontime時間が経過したか */
            if(*u4_a_wait_counter < (U4)PWRCTRL_SIP_TIME_INVALID){
                (*u4_a_wait_counter)++;                                 /* 待機時間測定カウンタをインクリメント */
            }
            u1_t_read_lv = u1_g_PwrCtrl_PinMonitor_GetPinInfo(u1_a_PinID); /* DIOのREAD関数をコール */
            if( u1_t_read_lv == u1_a_Level){                            /* READ関数で読みだした結果が期待値と一致するか */
                *u4_a_counter = (U4)PWRCTRL_SIP_TIME_INVALID;           /* 一致すれば待ち時間の測定結果に完了を通知 */
            }
        }
        else{
           (*u4_a_counter)++;                                           /* 待ち時間のしきい値に達していない場合はカウントをインクリメント */
        }
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrl_Sip_DioFreqAct
  Description   : SIP共通 待ち時間の計測+PWM処理実行関数
  param[in/out] :[out] U4 * const u4_a_counter 待ち時間の計測結果を格納
                :[in ] const U1 u1_a_ontime  待ち時間計測のしきい値
                :[in ] const U1 u1_a_PWM_CH  PWM処理を行うチャンネル
                :[in ] const U2 u2_a_PERIOD  PWM処理の周期
                :[in ] const U2 u2_a_DUTY    PWM処理の出力値
  return        : -
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrl_Sip_DioFreqAct(U4 * const u4_a_counter , const U1 u1_a_ontime ,
              const U1 u1_a_PWM_CH, const U2 u2_a_PERIOD, const U2 u2_a_DUTY)
{
    if(*u4_a_counter != (U4)PWRCTRL_SIP_TIME_INVALID){
        if(*u4_a_counter >= u1_a_ontime){                                    /* u1_a_ontime時間が経過したか */
            vd_g_Pwm_SetPeriodAndDuty(u1_a_PWM_CH, u2_a_PERIOD, u2_a_DUTY);
            *u4_a_counter = (U4)PWRCTRL_SIP_TIME_INVALID;                    /* 一致すれば待ち時間の測定結果に完了を通知 */
        }
        else{
            (*u4_a_counter)++;                                               /* 待ち時間のしきい値に達していない場合はカウントをインクリメント */
        }
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrl_Sip_Write_WAKEUP_STAT
  Description   : SIP共通 WAKEUP-STAT端子の設定関数
  param[in/out] : -
  return        : -
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrl_Sip_Write_WAKEUP_STAT(void)
{
    (void)Dio_WriteChannel(Mcu_Dio_PortId[PWRCTRL_CFG_PRIVATE_PORT_WAKEUP_STAT1], u1_s_PwrCtrl_Sip_WAKEUP_STAT1);
    (void)Dio_WriteChannel(Mcu_Dio_PortId[PWRCTRL_CFG_PRIVATE_PORT_WAKEUP_STAT2], u1_s_PwrCtrl_Sip_WAKEUP_STAT2);
    (void)Dio_WriteChannel(Mcu_Dio_PortId[PWRCTRL_CFG_PRIVATE_PORT_WAKEUP_STAT3], u1_s_PwrCtrl_Sip_WAKEUP_STAT3);

    /* 端子設定後、WAKEUP-STAT2の情報をクリア */
    u1_s_PwrCtrl_Sip_WAKEUP_STAT2 = (U1)MCU_DIO_LOW;
    vd_g_Rim_WriteU1((U2)RIMID_U1_PWCTR_SOC_WU_STAT2, u1_s_PwrCtrl_Sip_WAKEUP_STAT2);

    return;
}

/**** End of File ***********************************************************/
