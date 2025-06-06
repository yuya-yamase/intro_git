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
#define PWRCTRL_SIP_OFF_T_PMICFASTPOFF     (     5U / PWRCTRL_CFG_TASK_TIME) /* tPMIC_FAST_POFF_EN_N:5ms                                             */
#define PWRCTRL_SIP_OFF_T_MM_SUSPEND_REQ_N (     5U / PWRCTRL_CFG_TASK_TIME) /* tMM_SUSPEND_REQ_N:5ms                                                */
#define PWRCTRL_SIP_OFF_T_STR_WAKE         (     5U / PWRCTRL_CFG_TASK_TIME) /* tSTR_WAKE:5ms                                                        */
#define PWRCTRL_SIP_OFF_T_MM_OFF_REQ_LO    (     5U / PWRCTRL_CFG_TASK_TIME) /* tMM_OFF_REQ_LO:5ms                                                   */
#define PWRCTRL_SIP_OFF_WAIT_MM_STBY       (     5U / PWRCTRL_CFG_TASK_TIME) /* MM_STBY_N =Loチェック待機時間:5ms                                    */

/* SIPスタンバイ用処理 */
#define PWRCTRL_SIP_STBY_T_MM_SUSPEND_REQ  (0U)                              /* tMM_SUSPEND_REQ_N:0ms                                                */
#define PWRCTRL_SIP_STBY_T_STR_WAKE        (0U)                              /* tSTR_WAKE:0ms                                                        */
#define PWRCTRL_SIP_STBY_T_MM_STBY         (0U)                              /* MM_STBY_N:0ms                                                        */
#define PWRCTRL_SIP_STBY_T_AOSS            (0U)                              /* AOSS_SLEEP_ENTRY_EXIT:0ms                                            */
#define PWRCTRL_SIP_STBY_T_VB33_SIP_FREQ   (0U)                              /* tVB33-SIP-FREQ:0ms                                                   */
#define PWRCTRL_SIP_STBY_T_LOW_POWER_ON    (     5U / PWRCTRL_CFG_TASK_TIME) /* tLOW-POWER-ON:5ms                                                    */

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
static void vd_s_PwrCtrl_Sip_DioWriteCheck(U4* u4_a_counter , const U1 u1_a_ontime ,const Dio_ChannelType u2_a_ChannelId , const Dio_LevelType u1_a_Level);
static void vd_s_PwrCtrl_Sip_DioReadCheck(U4* u4_a_counter , const U1 u1_a_ontime ,const U1 u1_a_PinID , const Dio_LevelType u1_a_Level);
static void vd_s_PwrCtrl_Sip_DioFreqAct(U4* u4_a_counter , const U1 u1_a_ontime ,const U1 u1_a_PWM_CH, const U2 u2_a_PERIOD, const U2 u2_a_DUTY);

/* LOW_POWER_ON状態要求 */
static U1 u1_s_PwrCtrl_Sip_LOW_POWER_ON_Sts;

/* ON/OFFシーケンス起動要求 */
static U1 u1_s_PwrCtrl_Sip_Pwr_Sts;

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
static U4 u4_s_PwrCtrl_Sip_Off_PMIC_FAST_POFF_EN_N_Tim;
static U4 u4_s_PwrCtrl_Sip_Off_MM_SUSPEND_REQ_N_Tim;
static U4 u4_s_PwrCtrl_Sip_Off_STR_WAKE_Tim;
static U4 u4_s_PwrCtrl_Sip_Off_MM_OFF_REQ_Step6_Tim;

static U1 u1_s_PwrCtrl_Sip_Stby_Step;
static U4 u4_s_PwrCtrl_Sip_Stby_MM_SUSPEND_REQ_N_Tim;
static U4 u4_s_PwrCtrl_Sip_Stby_STR_WAKE_Tim;
static U4 u4_s_PwrCtrl_Sip_Stby_MM_STBY_N_Chk_Tim;
static U4 u4_s_PwrCtrl_Sip_Stby_AOSS_Tim;
static U4 u4_s_PwrCtrl_Sip_Stby_FREQ_Tim;
static U4 u4_s_PwrCtrl_Sip_Stby_LOW_POWER_ON_Tim;

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
/* SIPレジューム制御 */
static void vd_s_PwrCtrlSipRsmMainFunc( void );
/* SIP電源OFF制御 */
static void vd_s_PwrCtrlSipOffMainFunc( void );
/* スタンバイ制御 */
static void vd_s_PwrCtrlSipStbyMainFunc( void );

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
#define vd_s_PwrCtrlSipOnInitValChkAOSS()  (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_On_AOSS_Tim, (U1)PWRCTRL_SIP_ON_T_AOSS,(U1)PWRCTRL_CFG_PRIVATE_KIND_AOSS_SLP_ENTRY_EXIT, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOnInitChkPOFFCOMP() (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_On_POFF_COMPLETE_N_Init_Tim, (U1)PWRCTRL_SIP_ON_T_POFF_COMPLETE_N,(U1)PWRCTRL_CFG_PRIVATE_KIND_POFF_COMPLETE_N, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOnPMPWREN2()        (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Step3_Tim, (U1)PWRCTRL_SIP_ON_T_PM_PWR_EN_N_LO,(U1)PWRCTRL_CFG_PRIVATE_PORT_PM_PWR_EN, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOnPMICFASTPOFF2()   (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_On_PMIC_FAST_POFF_EN_N_Step3_Tim, (U1)PWRCTRL_SIP_ON_T_PMICFASTPOFF,(U1)PWRCTRL_CFG_PRIVATE_PORT_PMIC_FAST_POFF_EN, (Dio_LevelType)MCU_DIO_HIGH))
#define vd_s_PwrCtrlSipOnMMSUSPEND()       (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_On_MM_SUSPEND_REQ_N_Tim, (U1)PWRCTRL_SIP_ON_T_MM_SUSPEND_REQ_N,(U1)PWRCTRL_CFG_PRIVATE_PORT_MM_SUSPEND_REQ, (Dio_LevelType)MCU_DIO_HIGH))
#define vd_s_PwrCtrlSipOnSTRWAKE()         (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_On_STR_WAKE_Tim, (U1)PWRCTRL_SIP_ON_T_STR_WAKE,(U1)PWRCTRL_CFG_PRIVATE_PORT_STR_WAKE, (Dio_LevelType)MCU_DIO_HIGH))
#define vd_s_PwrCtrlSipOnInitChkPSHOLD()   (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Init_Tim, (U1)PWRCTRL_SIP_ON_T_PMA_PS_HOLD_INIT,(U1)PWRCTRL_CFG_PRIVATE_KIND_PMA_PS_HOLD, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOnValChkPOFFCOMP()  (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_On_POFF_COMPLETE_N_Chk_Tim, (U1)PWRCTRL_SIP_ON_T_POFF_COMP_VAL,(U1)PWRCTRL_CFG_PRIVATE_KIND_POFF_COMPLETE_N, (Dio_LevelType)MCU_DIO_HIGH))
#define vd_s_PwrCtrlSipOnValChkSOCRSOUT()  (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_On_SOC_RESOUT_N_Tim, (U1)PWRCTRL_SIP_ON_T_SOC_RESOUT_N,(U1)PWRCTRL_CFG_PRIVATE_KIND_SOC_RESOUT_N, (Dio_LevelType)MCU_DIO_HIGH))
#define vd_s_PwrCtrlSipOnValChkSAILRSOUT() (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_On_SAIL_RESOUT_N_Tim, (U1)PWRCTRL_SIP_ON_T_SAIL_RESOUT_N,(U1)PWRCTRL_CFG_PRIVATE_KIND_SAIL_RESOUT_N, (Dio_LevelType)MCU_DIO_HIGH))
#define vd_s_PwrCtrlSipOnValChkPSHOLD()    (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Chk_Tim, (U1)PWRCTRL_SIP_ON_T_PMA_PS_HOLD_VAL,(U1)PWRCTRL_CFG_PRIVATE_KIND_PMA_PS_HOLD, (Dio_LevelType)MCU_DIO_HIGH))
#define vd_s_PwrCtrlSipOnPMPWREN3()        (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Step8_Tim, (U1)PWRCTRL_SIP_ON_T_PM_PWR_EN_N_HI_P2,(U1)PWRCTRL_CFG_PRIVATE_PORT_PM_PWR_EN, (Dio_LevelType)MCU_DIO_HIGH))
/* SIPレジューム制御 */
#define vd_s_PwrCtrlSipRsmLOWPOWERON()     (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Rsm_LOW_POWER_ON_Tim, (U1)PWRCTRL_SIP_RSM_T_LOW_POWER_ON,(U1)PWRCTRL_CFG_PRIVATE_PORT_LOW_POWER, (Dio_LevelType)MCU_DIO_HIGH))
#define vd_s_PwrCtrlSipRsmVB33SIPFREQ()    (vd_s_PwrCtrl_Sip_DioFreqAct(&u4_s_PwrCtrl_Sip_Rsm_VB33_SIP_FREQ_Tim, (U1)PWRCTRL_SIP_RSM_T_VB33_SIP_FREQ,(U1)PWM_CH_01_DDC_SIP_FREQ, (U2)PWRCTRL_SIP_PWM_PERIOD_DEF, (U2)PWRCTRL_SIP_PWM_DUTYCYCLE_DEF))
#define vd_s_PwrCtrlSipRsmMMSUSPEND()      (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Rsm_MM_SUSPEND_REQ_N_Tim, (U1)PWRCTRL_SIP_RSM_T_MM_SUSPEND_REQ_N,(U1)PWRCTRL_CFG_PRIVATE_PORT_MM_SUSPEND_REQ, (Dio_LevelType)MCU_DIO_HIGH))
#define vd_s_PwrCtrlSipRsmSTRWAKE()        (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Rsm_STR_WAKE_Tim, (U1)PWRCTRL_SIP_RSM_T_STR_WAKE,(U1)PWRCTRL_CFG_PRIVATE_PORT_STR_WAKE, (Dio_LevelType)MCU_DIO_HIGH))
/* SIP電源OFF制御 */
#define vd_s_PwrCtrlSipOffMMOFFREQ1()      (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Off_MM_OFF_REQ_Step1_Tim, (U1)PWRCTRL_SIP_OFF_T_MM_OFF_REQ_HI,(U1)PWRCTRL_CFG_PRIVATE_PORT_MM_OFF_REQ, (Dio_LevelType)MCU_DIO_HIGH))
#define vd_s_PwrCtrlSipOffValChkMMSTBY()   (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_Off_MM_STBY_N_Chk_Tim, (U1)PWRCTRL_SIP_OFF_T_MM_STBY,(U1)PWRCTRL_CFG_PRIVATE_KIND_MM_STBY_N, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOffValChkPSHOLD()   (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_Off_PMA_PS_HOLD_Chk_Tim, (U1)PWRCTRL_SIP_OFF_T_PMA_PS_HOLD,(U1)PWRCTRL_CFG_PRIVATE_KIND_PMA_PS_HOLD, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOffValChkSOCRSOUT() (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_Off_SOC_RESOUT_N_Chk_Tim, (U1)PWRCTRL_SIP_OFF_T_SOC_RESOUT_N,(U1)PWRCTRL_CFG_PRIVATE_KIND_SOC_RESOUT_N, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOffValChkSAILROUT() (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_Off_SAIL_RESOUT_N_Chk_Tim, (U1)PWRCTRL_SIP_OFF_T_SAIL_RESOUT_N,(U1)PWRCTRL_CFG_PRIVATE_KIND_SAIL_RESOUT_N, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOffValChkPOFFCOMP() (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_Off_POFF_COMPLETE_N_Chk_Tim, (U1)PWRCTRL_SIP_OFF_T_POFF_COMPLETE_N,(U1)PWRCTRL_CFG_PRIVATE_KIND_POFF_COMPLETE_N, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOffVB33SIPFREQ()    (vd_s_PwrCtrl_Sip_DioFreqAct(&u4_s_PwrCtrl_Sip_Off_VB33_SIP_FREQ_Tim, (U1)PWRCTRL_SIP_OFF_T_VB33_SIP_FREQ,(U1)PWM_CH_01_DDC_SIP_FREQ, (U2)PWRCTRL_SIP_PWM_PERIOD_OFF, (U2)PWRCTRL_SIP_PWM_DUTYCYCLE_OFF))
#define vd_s_PwrCtrlSipOffVB33SIPON()      (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Off_VB33_SIP_ON_Tim, (U1)PWRCTRL_SIP_OFF_T_VB33_SIP_ON,(U1)PWRCTRL_CFG_PRIVATE_PORT_VB33_SIP, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOffLOWPOWERON()     (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Off_LOW_POWER_ON_Tim, (U1)PWRCTRL_SIP_OFF_T_LOW_POWER_ON,(U1)PWRCTRL_CFG_PRIVATE_PORT_LOW_POWER, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOffPMPWREN()        (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Off_PM_PWR_EN_N_Tim, (U1)PWRCTRL_SIP_OFF_T_PM_PWR_EN_N,(U1)PWRCTRL_CFG_PRIVATE_PORT_PM_PWR_EN, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOffPMICFASTPOFF()   (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Off_PMIC_FAST_POFF_EN_N_Tim, (U1)PWRCTRL_SIP_OFF_T_PMICFASTPOFF,(U1)PWRCTRL_CFG_PRIVATE_PORT_PMIC_FAST_POFF_EN, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOffMMSUSPEND()      (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Off_MM_SUSPEND_REQ_N_Tim, (U1)PWRCTRL_SIP_OFF_T_MM_SUSPEND_REQ_N,(U1)PWRCTRL_CFG_PRIVATE_PORT_MM_SUSPEND_REQ, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOffSTRWAKE()        (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Off_STR_WAKE_Tim, (U1)PWRCTRL_SIP_OFF_T_STR_WAKE,(U1)PWRCTRL_CFG_PRIVATE_PORT_STR_WAKE, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipOffMMOFFREQ2()      (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Off_MM_OFF_REQ_Step6_Tim, (U1)PWRCTRL_SIP_OFF_T_MM_OFF_REQ_LO,(U1)PWRCTRL_CFG_PRIVATE_PORT_MM_OFF_REQ, (Dio_LevelType)MCU_DIO_LOW))
/* スタンバイシーケンス */
#define vd_s_PwrCtrlSipStbyMMSUSPEND()     (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Stby_MM_SUSPEND_REQ_N_Tim, (U1)PWRCTRL_SIP_STBY_T_MM_SUSPEND_REQ,(U1)PWRCTRL_CFG_PRIVATE_PORT_MM_SUSPEND_REQ, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipStbySTRWAKE()       (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Stby_STR_WAKE_Tim, (U1)PWRCTRL_SIP_STBY_T_STR_WAKE,(U1)PWRCTRL_CFG_PRIVATE_PORT_STR_WAKE, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipStbyValChkMMSTBY()  (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_Stby_MM_STBY_N_Chk_Tim, (U1)PWRCTRL_SIP_STBY_T_MM_STBY,(U1)PWRCTRL_CFG_PRIVATE_KIND_MM_STBY_N, (Dio_LevelType)MCU_DIO_LOW))
#define vd_s_PwrCtrlSipStbyValChkAOSS()    (vd_s_PwrCtrl_Sip_DioReadCheck(&u4_s_PwrCtrl_Sip_Stby_AOSS_Tim, (U1)PWRCTRL_SIP_STBY_T_AOSS,(U1)PWRCTRL_CFG_PRIVATE_KIND_AOSS_SLP_ENTRY_EXIT, (Dio_LevelType)MCU_DIO_HIGH))
#define vd_s_PwrCtrlSipStbyVB33SIPFREQ()   (vd_s_PwrCtrl_Sip_DioFreqAct(&u4_s_PwrCtrl_Sip_Stby_FREQ_Tim, (U1)PWRCTRL_SIP_STBY_T_VB33_SIP_FREQ,(U1)PWM_CH_01_DDC_SIP_FREQ, (U2)PWRCTRL_SIP_PWM_PERIOD_OFF, (U2)PWRCTRL_SIP_PWM_DUTYCYCLE_OFF))
#define vd_s_PwrCtrlSipStbyLOWPOWERON()    (vd_s_PwrCtrl_Sip_DioWriteCheck(&u4_s_PwrCtrl_Sip_Stby_LOW_POWER_ON_Tim, (U1)PWRCTRL_SIP_STBY_T_LOW_POWER_ON,(U1)PWRCTRL_CFG_PRIVATE_PORT_LOW_POWER, (Dio_LevelType)MCU_DIO_LOW))

/*--------------------------------------------------------------------------*/
/* Functions                                                                */
/*--------------------------------------------------------------------------*/

/*#define ***_START_SEC_CODE
#include <***_MemMap.h>*/
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
  return        : FALSE(0)：LOW_POWER_ON Lo
                  TRUE(1) ：LOW_POWER_ON Hi
  Note          : none
*****************************************************************************/
U1 u1_g_PwrCtrlSipLowPowerOnInfo( void )
{
    return(u1_s_PwrCtrl_Sip_LOW_POWER_ON_Sts);
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

    /* ステップ判定用RAMの初期化 */
    u1_s_PwrCtrl_Sip_On_Step                          = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Rsm_Step                         = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Off_Step                         = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Stby_Step                        = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    
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
    u4_s_PwrCtrl_Sip_Off_PMIC_FAST_POFF_EN_N_Tim      = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_MM_SUSPEND_REQ_N_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_STR_WAKE_Tim                 = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_MM_OFF_REQ_Step6_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;

    /* SiPスタンバイ */
    u4_s_PwrCtrl_Sip_Stby_MM_SUSPEND_REQ_N_Tim        = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_STR_WAKE_Tim                = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_MM_STBY_N_Chk_Tim           = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_AOSS_Tim                    = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_FREQ_Tim                    = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_LOW_POWER_ON_Tim            = (U4)PWRCTRL_SIP_TIME_INIT;
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
    /* ステップ判定用RAMの初期化 */
    u1_s_PwrCtrl_Sip_On_Step       = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Rsm_Step      = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Off_Step      = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Stby_Step     = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    
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

    /* 現在起動ステップの初期化 */
    u1_s_PwrCtrl_Sip_On_Step                          = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
    /* 他処理の無効化 */
    u1_s_PwrCtrl_Sip_Rsm_Step                         = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Off_Step                         = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Stby_Step                        = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    
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

    /* 現在起動ステップの初期化 */
    u1_s_PwrCtrl_Sip_Rsm_Step                 = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
    /* 他処理の無効化 */
    u1_s_PwrCtrl_Sip_On_Step                  = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Off_Step                 = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Stby_Step                = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    
    /* 待機時間測定用RAMの初期化 */
    u4_s_PwrCtrl_Sip_Rsm_LOW_POWER_ON_Tim     = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Rsm_VB33_SIP_FREQ_Tim    = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Rsm_MM_SUSPEND_REQ_N_Tim = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Rsm_STR_WAKE_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
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

    /* 現在起動ステップの初期化 */
    u1_s_PwrCtrl_Sip_Off_Step                     = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
    /* 他処理の無効化 */
    u1_s_PwrCtrl_Sip_On_Step                      = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Rsm_Step                     = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Stby_Step                    = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;

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
    u4_s_PwrCtrl_Sip_Off_PMIC_FAST_POFF_EN_N_Tim  = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_MM_SUSPEND_REQ_N_Tim     = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_STR_WAKE_Tim             = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Off_MM_OFF_REQ_Step6_Tim     = (U4)PWRCTRL_SIP_TIME_INIT;

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

    /* 現在起動ステップの初期化 */
    u1_s_PwrCtrl_Sip_Stby_Step                 = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
    /* 他処理の無効化 */
    u1_s_PwrCtrl_Sip_On_Step                   = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Rsm_Step                  = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
    u1_s_PwrCtrl_Sip_Off_Step                  = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;

    /* 待機時間測定用RAMの初期化 */
    u4_s_PwrCtrl_Sip_Stby_MM_SUSPEND_REQ_N_Tim = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_STR_WAKE_Tim         = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_MM_STBY_N_Chk_Tim    = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_AOSS_Tim             = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_FREQ_Tim             = (U4)PWRCTRL_SIP_TIME_INIT;
    u4_s_PwrCtrl_Sip_Stby_LOW_POWER_ON_Tim     = (U4)PWRCTRL_SIP_TIME_INIT;
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
            /* 【todo】5-6.SIP電源強制OFFシーケンス */
            break;

        default:
            break;
    }
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
        u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Lo_ElapsedTim++; /* Step3-1完了後、次の周期からカウント */
        if(u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Lo_ElapsedTim >= (U4)PWRCTRL_SIP_ON_T_PM_PWR_EN_N_ELPSD){
            u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Lo_ElapsedTim = (U4)PWRCTRL_SIP_ON_T_PM_PWR_EN_N_ELPSD; /* 最大値でガード */
        }
    }

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
        if((u4_s_PwrCtrl_Sip_On_AOSS_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_On_POFF_COMPLETE_N_Init_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_On_VB33_SIP_FREQ_Step2_Tim == (U4)PWRCTRL_SIP_TIME_INVALID)){
            u1_s_PwrCtrl_Sip_On_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP3;
           }

        /* 【todo】STEP2-2、2-3が50ms経過しても完了してなければSTEPを完了させる */
        /* 【todo】異常保存して強制OFFシーケンス(PMIC異常DDコン)へ移行 */

    }
    
    if(u1_s_PwrCtrl_Sip_On_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP3){
/* PM_PWR_EN_N=Lo */
        /* AOSS_SLEEP_NETRY_EXIT,POFF_COMPLETE_N初期値チェックからtPM_PWR_EN_N_LO経過後にPM_PWR_EN_N = Lo */
        vd_s_PwrCtrlSipOnPMPWREN2();                           /* STEP3-1 */

        /* STEP3-1が完了していれば次のSTEPに進める */
        if(u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Step3_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
            u1_s_PwrCtrl_Sip_On_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP4;
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
        
    if(u1_s_PwrCtrl_Sip_On_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP4){
/* PMA_PS_HOLD=Lo */
        /* PMA_PS_HOLD初期値(Lo)チェック */
        vd_s_PwrCtrlSipOnInitChkPSHOLD();          /* STEP4-1 */

#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_BON_STEP4_1; /* TP */
#endif

        /* STEP4-1が完了していれば次の処理に進める */
        if(u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Init_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
            u1_s_PwrCtrl_Sip_On_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP5;
        }

        /* 【todo】STEP5-1が300ms経過しても完了してなければSTEPを完了させる */
        /* 【todo】異常保存して強制OFFシーケンス(SOC異常)へ移行 */

    }

    if(u1_s_PwrCtrl_Sip_On_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP5){
/* POFF_COMPLETE_N=Hi */
        /* PMA_PS_HOLD = Lo後にPOFF_COMPLETE_N変化(Lo→Hi)チェック */
        vd_s_PwrCtrlSipOnValChkPOFFCOMP();         /* STEP5-1 */

#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_BON_STEP5_1; /* TP */
#endif

        /* STEP5-1が完了していれば次の処理に進める */
        if(u4_s_PwrCtrl_Sip_On_POFF_COMPLETE_N_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
            u1_s_PwrCtrl_Sip_On_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP6;

            /* 【todo】5-9. PM_PSAIL_ERR_N監視処理開始 */
            /* 【todo】4.0版参照 5-12-1. PGOOD_ASIL_VB監視処理開始 4.0版参照 */

        }
    }

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

        /* SAIL_RESOUT_N変化(Hi)チェックが完了したらEtherSW起動要求を通知 */
        if(u4_s_PwrCtrl_Sip_On_SAIL_RESOUT_N_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
            EthSW_PowerON_Req_Bon(); /* 暫定_EtherSW起動要求 */
        }
        
        /* STEP6-1,6-2が完了していれば次の処理に進める */
        if((u4_s_PwrCtrl_Sip_On_SOC_RESOUT_N_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_On_SAIL_RESOUT_N_Tim == (U4)PWRCTRL_SIP_TIME_INVALID)){
            u1_s_PwrCtrl_Sip_On_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP7;
        }

        /* 【todo】STEP6-1、6-2が200ms経過しても完了してなければSTEPを完了させる */
        /* 【todo】異常保存して強制OFFシーケンス(PMIC異常)へ移行 */

    }

    if(u1_s_PwrCtrl_Sip_On_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP7){
/* PMA_PS_HOLD=Hi */
        /* SOC_RESOUT_N & SAIL_RESOUT_N=Hi変化後にPMA_PS_HOLD変化(Hi)チェック */
        vd_s_PwrCtrlSipOnValChkPSHOLD();     /* STEP7-1 */

#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_BON_STEP7_1; /* TP */
#endif

        /* STEP7-1が完了、かつSTEP3-1から50ms経過していれば次の処理に進める */
        if((u4_s_PwrCtrl_Sip_On_PMA_PS_HOLD_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_On_PM_PWR_EN_N_Lo_ElapsedTim == (U4)PWRCTRL_SIP_ON_T_PM_PWR_EN_N_ELPSD)){
            u1_s_PwrCtrl_Sip_On_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP8;

            /* 【todo】5-10. PMA_PS_HOLD監視処理開始 */
            /* 【todo】5-7. SAIL UART Message監視開始 */

        }

        /* 【todo】STEP8-1が200ms経過しても完了してなければSTEPを完了させる */
        /* 【todo】異常保存して強制OFFシーケンス(SOC異常)へ移行 */

    }
    
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
        if((U1)u4_s_PwrCtrl_Sip_Rsm_VB33_SIP_FREQ_Tim == (U1)PWRCTRL_SIP_TIME_INVALID){
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
    if(u1_s_PwrCtrl_Sip_Off_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP1){
        vd_s_PwrCtrlSipOffMMOFFREQ1(); /* STEP1-1 */
        
        /* STEP1-1が完了していれば次のSTEPに進める */
        if(u4_s_PwrCtrl_Sip_Off_MM_OFF_REQ_Step1_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
            u1_s_PwrCtrl_Sip_Off_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP2;
        }
    }

/* MM_STBY_N =Lo? */
    if((U1)u1_s_PwrCtrl_Sip_Off_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP2){
        vd_s_PwrCtrlSipOffValChkMMSTBY();         /* STEP2-1 */

#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_SIPOFF_STEP2_1; /* TP */
#endif

        /* STEP2-1が完了していれば次の処理に進める */
        if (u4_s_PwrCtrl_Sip_Off_MM_STBY_N_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
            u1_s_PwrCtrl_Sip_Off_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP3;
        }
        else
        {
            u4_s_PwrCtrl_Sip_Off_MM_STBY_N_Chk_Tim++; /* sleepに進めるための暫定処理 */
        /* 【todo】STEP2-1が100秒経過しても完了してなければSTEPを完了させる */
        /* 【todo】異常保存して強制OFFシーケンス(SOC異常)へ移行 */
            if( u4_s_PwrCtrl_Sip_Off_MM_STBY_N_Chk_Tim >= (U4)PWRCTRL_SIP_OFF_WAIT_MM_STBY){
                (void)Dio_WriteChannel(DIO_ID_PORT8_CH0, MCU_DIO_LOW);
                u4_s_PwrCtrl_Sip_Off_MM_STBY_N_Chk_Tim = (U4)PWRCTRL_SIP_TIME_INVALID;
                u1_s_PwrCtrl_Sip_Off_Step              = (U1)PWRCTRL_COMMON_PROCESS_STEP7;
            }
        }
    }

/* PMA_PS_HOLD =Lo? */
    if(u1_s_PwrCtrl_Sip_Off_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP3){
        vd_s_PwrCtrlSipOffValChkPSHOLD(); /* STEP3-1 */

#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_SIPOFF_STEP3_1; /* TP */
#endif

        /* STEP3-1が完了していれば次の処理に進める */
        if (u4_s_PwrCtrl_Sip_Off_PMA_PS_HOLD_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
            u1_s_PwrCtrl_Sip_Off_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP4;
        }
        
        /* 【todo】STEP3-1が3秒経過しても完了してなければSTEPを完了させる */
        /* 【todo】異常保存して強制OFFシーケンス(SOC異常)へ移行 */

    }

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
        if((u4_s_PwrCtrl_Sip_Off_SOC_RESOUT_N_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_Off_SAIL_RESOUT_N_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_Off_POFF_COMPLETE_N_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID)){
             u1_s_PwrCtrl_Sip_Off_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP5;
        }
        /* 【todo】STEP3が100ms経過しても完了してなければ異常ルートに移行させる */
        /* 【todo】異常保存 */
        /* 【todo】SAIL_RESOUT_N & POFF_COMPLETE_N =Loチェックを行う */
        /* 【todo】YESなら強制OFFシーケンス(PMIC異常)へ移行 */
        /* 【todo】NOなら強制OFFシーケンス(SoC異常)へ移行 */

    }

    if(u1_s_PwrCtrl_Sip_Off_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP5){
        vd_s_PwrCtrlSipOffVB33SIPFREQ(); /* STEP5-1 */

        /* STEP5-1が完了していれば次のSTEPに進める */
        if (u4_s_PwrCtrl_Sip_Off_VB33_SIP_FREQ_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
            u1_s_PwrCtrl_Sip_Off_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP6;
        }
    }

    if(u1_s_PwrCtrl_Sip_Off_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP6){
        vd_s_PwrCtrlSipOffVB33SIPON();       /* STEP6-1 */
        vd_s_PwrCtrlSipOffLOWPOWERON();      /* STEP6-2 */
        vd_s_PwrCtrlSipOffPMPWREN();         /* STEP6-3 */
        vd_s_PwrCtrlSipOffPMICFASTPOFF();    /* STEP6-4 */
        vd_s_PwrCtrlSipOffMMSUSPEND();       /* STEP6-5 */
        vd_s_PwrCtrlSipOffSTRWAKE();         /* STEP6-6 */
        vd_s_PwrCtrlSipOffMMOFFREQ2();       /* STEP6-7 */
    
        if(u4_s_PwrCtrl_Sip_Off_LOW_POWER_ON_Tim == PWRCTRL_SIP_TIME_INVALID){
            /* LOW-POWER-ON_LOを検知時に端子モニタ停止を設定 */
            u1_s_PwrCtrl_Sip_LOW_POWER_ON_Sts = (U1)FALSE;
        }

        /* STEP6-1～6-7が完了していれば次のSTEPに進める */
        if((u4_s_PwrCtrl_Sip_Off_VB33_SIP_ON_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_Off_LOW_POWER_ON_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_Off_PM_PWR_EN_N_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_Off_PMIC_FAST_POFF_EN_N_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_Off_MM_SUSPEND_REQ_N_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_Off_STR_WAKE_Tim == (U4)PWRCTRL_SIP_TIME_INVALID) &&
           (u4_s_PwrCtrl_Sip_Off_MM_OFF_REQ_Step6_Tim == (U4)PWRCTRL_SIP_TIME_INVALID)){
            u1_s_PwrCtrl_Sip_Off_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
            u1_s_PwrCtrl_Sip_Pwr_Sts  = (U1)PWRCTRL_SIP_STS_NON;
        }
    }
    
    /* 【todo】シス検向けsleep処理のための強制OFFシーケンス実行処理 */
    /* 【todo】強制OFFシーケンス追加時に削除すること */
    if(u1_s_PwrCtrl_Sip_Off_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP7){
        vd_s_PwrCtrlSipOffValChkPOFFCOMP();

        if(u4_s_PwrCtrl_Sip_Off_POFF_COMPLETE_N_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
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
        if(u4_s_PwrCtrl_Sip_Stby_MM_STBY_N_Chk_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
            u1_s_PwrCtrl_Sip_Stby_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP3;
        }

        /* 【todo】STEP2-1が100秒経過しても完了してなければSTEPを完了させる */
        /* 【todo】異常保存して強制OFFシーケンス(SOC異常)へ移行 */

    }
    
/* AOSS_SLEEP_ENTRY_EXIT = Hi? */
    if(u1_s_PwrCtrl_Sip_Stby_Step == (U1)PWRCTRL_COMMON_PROCESS_STEP3){
        vd_s_PwrCtrlSipStbyValChkAOSS(); /* STEP3-1 */

#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_STANDBY_AOSS; /* TP */
#endif

        /* STEP3-1が完了していれば次の処理に進める */
        if(u4_s_PwrCtrl_Sip_Stby_AOSS_Tim == (U4)PWRCTRL_SIP_TIME_INVALID){
            u1_s_PwrCtrl_Sip_Stby_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP4;
        }

        /* 【todo】STEP3-1が100ms経過しても完了してなければSTEPを完了させる */
        /* 【todo】異常保存して強制OFFシーケンス(PMIC異常)へ移行 */

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
  Function      : vd_s_PwrCtrl_Sip_DioWriteCheck
  Description   : SIP共通 待ち時間の計測+DIOのWRITE処理実行関数
  param[in/out] :[out] U4*      u4_a_counter                待ち時間の計測結果を格納
                 [in ] const U1 u1_a_ontime                 待ち時間計測のしきい値
                 [in ] const Dio_ChannelType u2_a_ChannelId DIOのWRITE処理を行うチャンネルID
                 [in ] const Dio_LevelType u1_a_Level       DIOで設定したい出力値
  return        : -
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrl_Sip_DioWriteCheck(U4* u4_a_counter , const U1 u1_a_ontime ,
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
  param[in/out] :[out] U4       u4_a_counter          待ち時間の計測結果を格納
                 [in ] const U1 u1_a_ontime           待ち時間計測のしきい値
                 [in ] const U1 u1_a_PinID            READ処理を行うチャンネルI
                 [in ] const Dio_LevelType u1_a_Level READ結果の照合
  return        : -
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrl_Sip_DioReadCheck(U4* u4_a_counter , const U1 u1_a_ontime ,
        const U1 u1_a_PinID , const Dio_LevelType u1_a_Level)
{
    U1 u1_t_read_lv;

    if(*u4_a_counter != (U4)PWRCTRL_SIP_TIME_INVALID){
        if(*u4_a_counter >= u1_a_ontime){                               /* u1_a_ontime時間が経過したか */
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
  param[in/out] :[out] U4       u4_a_counter 待ち時間の計測結果を格納
                :[in ] const U1 u1_a_ontime  待ち時間計測のしきい値
                :[in ] const U1 u1_a_PWM_CH  PWM処理を行うチャンネル
                :[in ] const U2 u2_a_PERIOD  PWM処理の周期
                :[in ] const U2 u2_a_DUTY    PWM処理の出力値
  return        : -
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrl_Sip_DioFreqAct(U4* u4_a_counter , const U1 u1_a_ontime ,
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

/*#define ***_STOP_SEC_CODE
#include <***_MemMap.h>*/

/**** End of File ***********************************************************/
