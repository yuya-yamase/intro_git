/* Mcu_Sys_Pwr_c_v1-0-0                                                     */
/****************************************************************************/
/* Copyright (C) 2023 Denso Co.,Ltd. All rights reserved.                   */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Mcu_Sys_Pwr/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "Mcu_Common.h"
#include "Mcu_Sip_Pwr.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* SIP電源ON用定義 */
#define     MCU_SIP_PWRON_T_VB33_SIP_ON             (0u)     /* tVB33-SIP-ON:0ms            */
#define     MCU_SIP_PWRON_T_LOW_POWER_ON_LO         (0u)     /* tLOW-POWER-ON_LO:0ms        */
#define     MCU_SIP_PWRON_T_VB33_SIP_FREQ_LO        (0u)     /* tVB33-SIP-FREQ_LO:0ms       */
#define     MCU_SIP_PWRON_T_PM_PWR_EN_N_STEP1_LO    (0u)     /* tPM_PWR_EN_N_LO:0ms         */
#define     MCU_SIP_PWRON_T_PMIC_FAST_POFF_EN_N_LO  (0u)     /* tPMIC_FAST_POFF_EN_N_LO:0ms */
#define     MCU_SIP_PWRON_T_MM_OFF_REQ              (0u)     /* tMM-OFF-REQ_LO:0ms          */
#define     MCU_SIP_PWRON_T_LOW_POWER_ON_HI         (3u)     /* tLOW-POWER-ON_HI:15ms       */
#define     MCU_SIP_PWRON_T_VB33_SIP_FREQ           (1u)     /* tVB33-SIP-FREQ:5ms          */
#define     MCU_SIP_PWRON_T_AOSS_SLEEP_ENTRY_EXIT   (7u)     /* Wait time:35ms              */
#define     MCU_SIP_PWRON_T_POFF_COMPLETE_N         (7u)     /* Wait time:35ms              */
#define     MCU_SIP_PWRON_T_PM_PWR_EN_N_LO          (1u)     /* tPM_PWR_EN_N_LO:5ms         */
#define     MCU_SIP_PWRON_T_PMIC_FAST_POFF_EN_N     (1u)     /* tPMIC_FAST_POFF_EN_N:5ms    */
#define     MCU_SIP_PWRON_T_MM_SUSPEND_REQ_N        (1u)     /* tMM_SUSPEND_REQ_N:5ms       */
#define     MCU_SIP_PWRON_T_STR_WAKE                (1u)     /* tSTR_WAKE:5ms               */
#define     MCU_SIP_PWRON_T_PM_PWR_EN_N_HI_P2       (1u)     /* tPM_PWR_EN_N_HI_P2:5ms      */
#define     MCU_SIP_PWRON_T_PM_PWR_EN_N_ELPSD       (10u)    /* PN_PWR_EN_N=Lo→Hiの必要時間:50ms */
#define     MCU_SIP_PWRON_TIME_INVALID              (0xFFFFFFFFu)

#define     MCU_SIP_PWRON_STEP1      (0x01)
#define     MCU_SIP_PWRON_STEP2      (0x02)
#define     MCU_SIP_PWRON_STEP3      (0x03)
#define     MCU_SIP_PWRON_STEP4      (0x04)
#define     MCU_SIP_PWRON_STEP5      (0x05)
#define     MCU_SIP_PWRON_STEP6      (0x06)
#define     MCU_SIP_PWRON_STEP7      (0x07)
#define     MCU_SIP_PWRON_STEP8      (0x08)
#define     MCU_SIP_PWRON_STEP9      (0x09)
#define     MCU_SIP_PWRON_STEP_CMPLT (0xFF)

/* SIPレジューム用定義 */
#define     MCU_SIP_RESUME_T_LOW_POWER_ON          (0u)     /* tLOW-POWER-ON_HI:0ms     */
#define     MCU_SIP_RESUME_T_VB33_SIP_FREQ         (1u)     /* tVB33-SIP-FREQ:5ms       */
#define     MCU_SIP_RESUME_T_MM_SUSPEND_REQ_N      (1u)     /* tMM_SUSPEND_REQ_N:5ms    */
#define     MCU_SIP_RESUME_T_STR_WAKE              (1u)     /* tSTR_WAKE:5ms            */
#define     MCU_SIP_RESUME_TIME_INVALID            (0xFFFFFFFFu)

#define     MCU_SIP_RESUME_STEP1      (0x01)
#define     MCU_SIP_RESUME_STEP2      (0x02)
#define     MCU_SIP_RESUME_STEP3      (0x03)
#define     MCU_SIP_RESUME_STEP_CMPLT (0xFF)

/* SIP電源OFF用処理 */
#define     MCU_SIP_PWROFF_T_MM_OFF_REQ_HI          (0u)     /* tMM_OFF_REQ_HI:0ms   */
#define     MCU_SIP_PWROFF_T_VB33_SIP_FREQ          (1u)     /* tVB33-SIP-FREQ:5ms        */
#define     MCU_SIP_PWROFF_T_VB33_SIP_ON            (1u)     /* tVB33-SIP-ON:5ms          */
#define     MCU_SIP_PWROFF_T_LOW_POWER_ON           (1u)     /* tLOW-POWER-ON:5ms         */
#define     MCU_SIP_PWROFF_T_PM_PWR_EN_N            (1u)     /* tPM_PWR_EN_N:5ms          */
#define     MCU_SIP_PWROFF_T_PMIC_FAST_POFF_EN_N    (1u)     /* tPMIC_FAST_POFF_EN_N:5ms  */
#define     MCU_SIP_PWROFF_T_MM_SUSPEND_REQ_N       (1u)     /* tMM_SUSPEND_REQ_N:5ms     */
#define     MCU_SIP_PWROFF_T_STR_WAKE               (1u)     /* tSTR_WAKE:5ms             */
#define     MCU_SIP_PWROFF_T_MM_OFF_REQ_LO          (1u)     /* tMM_OFF_REQ_LO:5ms   */
#define     MCU_SIP_PWROFF_TIME_INVALID             (0xFFFFFFFFu)

#define     MCU_SIP_PWROFF_STEP1      (0x01)
#define     MCU_SIP_PWROFF_STEP2      (0x02)
#define     MCU_SIP_PWROFF_STEP3      (0x03)
#define     MCU_SIP_PWROFF_STEP4      (0x04)
#define     MCU_SIP_PWROFF_STEP5      (0x05)
#define     MCU_SIP_PWROFF_STEP6      (0x06)
#define     MCU_SIP_PWROFF_STEP_CMPLT (0xFF)

/* SIPスタンバイ用処理 */
#define     MCU_SIP_STANDBY_T_MM_SUSPEND_REQ_N        (0u)     /* tMM_SUSPEND_REQ_N:0ms    */
#define     MCU_SIP_STANDBY_T_STR_WAKE                (0u)     /* tSTR_WAKE:0ms            */
#define     MCU_SIP_STANDBY_T_VB33_SIP_FREQ           (0u)     /* tVB33-SIP-FREQ:0ms       */
#define     MCU_SIP_STANDBY_T_LOW_POWER_ON            (1u)     /* tLOW-POWER-ON:5ms        */
#define     MCU_SIP_STANDBY_TIME_INVALID              (0xFFFFFFFFu)

#define     MCU_SIP_STANDBY_STEP1      (0x01)
#define     MCU_SIP_STANDBY_STEP2      (0x02)
#define     MCU_SIP_STANDBY_STEP3      (0x03)
#define     MCU_SIP_STANDBY_STEP4      (0x04)
#define     MCU_SIP_STANDBY_STEP5      (0x05)
#define     MCU_SIP_STANDBY_STEP_CMPLT (0xFF)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/* SIP通常起動制御 */
static void Mcu_Sip_PwrOn_MainFunction( void );
static void Mcu_Sip_PwrOn_VB33_SIP_ON(void);
static void Mcu_Sip_PwrOn_LOW_POWER_ON_1(void);
static void Mcu_Sip_PwrOn_VB33_SIP_FREQ_1(void);
static void Mcu_Sip_PwrOn_PM_PWR_EN_N_1(void);
static void Mcu_Sip_PwrOn_PMIC_FAST_POFF_EN_N_1(void);
static void Mcu_Sip_PwrOn_MM_OFF_REQ(void);
static void Mcu_Sip_PwrOn_LOW_POWER_ON_2(void);
static void Mcu_Sip_PwrOn_VB33_SIP_FREQ_2(void);
static void Mcu_Sip_PwrOn_InitValChk_AOSS_SLEEP_ENTRY_EXIT(void);
static void Mcu_Sip_PwrOn_InitValChk_POFF_COMPLETE_N(void);
static void Mcu_Sip_PwrOn_PM_PWR_EN_N_2(void);
static void Mcu_Sip_PwrOn_PMIC_FAST_POFF_EN_N_2(void);
static void Mcu_Sip_PwrOn_MM_SUSPEND_REQ_N(void);
static void Mcu_Sip_PwrOn_STR_WAKE(void);
static void Mcu_Sip_PwrOn_InitValChk_PM_PSAIL_ERR_N(  void );
static void Mcu_Sip_PwrOn_InitValChk_PMA_PS_HOLD(void);
static void Mcu_Sip_PwrOn_ValChk_POFF_COMPLETE_N( void );
static void Mcu_Sip_PwrOn_ValChk_SOC_RESOUT_N(void);
static void Mcu_Sip_PwrOn_ValChk_SAIL_RESOUT_N(void);
static void Mcu_Sip_PwrOn_ValChk_PMA_PS_HOLD(void);
static void Mcu_Sip_PwrOn_PM_PWR_EN_N_3(void);
/* SIPレジューム制御 */
static void Mcu_Sip_Resume_MainFunction( void );
static void Mcu_Sip_Resume_LOW_POWER_ON(void);
static void Mcu_Sip_Resume_VB33_SIP_FREQ(void);
static void Mcu_Sip_Resume_MM_SUSPEND_REQ_N(void);
static void Mcu_Sip_Resume_STR_WAKE(void);
/* SIP電源OFF制御 */
static void Mcu_Sip_PwrOff_MainFunction( void );
static void Mcu_Sip_PwrOff_MM_OFF_REQ_1(void);
static void Mcu_Sip_PwrOff_ValChk_MM_STBY_N(void);
static void Mcu_Sip_PwrOff_ValChk_PMA_PS_HOLD(void);
static void Mcu_Sip_PwrOff_ValChk_SOC_RESOUT_N(void);
static void Mcu_Sip_PwrOff_ValChk_SAIL_RESOUT_N(void);
static void Mcu_Sip_PwrOff_ValChk_POFF_COMPLETE_N(void);
static void Mcu_Sip_PwrOff_VB33_SIP_FREQ(void);
static void Mcu_Sip_PwrOff_VB33_SIP_ON(void);
static void Mcu_Sip_PwrOff_LOW_POWER_ON(void);
static void Mcu_Sip_PwrOff_PM_PWR_EN_N(void);
static void Mcu_Sip_PwrOff_PMIC_FAST_POFF_EN_N(void);
static void Mcu_Sip_PwrOff_MM_SUSPEND_REQ_N(void);
static void Mcu_Sip_PwrOff_STR_WAKE(void);
static void Mcu_Sip_PwrOff_MM_OFF_REQ_2(void);
/* スタンバイシーケンス */
static void Mcu_Sip_Standby_MainFunction( void );
static void Mcu_Sip_Standby_MM_SUSPEND_REQ_N(void);
static void Mcu_Sip_Standby_STR_WAKE(void);
static void Mcu_Sip_Standby_ValChk_MM_STBY_N(void);
static void Mcu_Sip_Standby_ValChk_AOSS_SLEEP_ENTRY_EXIT(void);
static void Mcu_Sip_Standby_VB33_SIP_FREQ(void);
static void Mcu_Sip_Standby_LOW_POWER_ON(void);

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
static uint8  Mcu_Sip_PwrOn_Step;
static uint32 Mcu_Sip_PwrOn_VB33_SIP_ON_Time;
static uint32 Mcu_Sip_PwrOn_LOW_POWER_ON_Step1_Time;
static uint32 Mcu_Sip_PwrOn_VB33_SIP_FREQ_Step1_Time;
static uint32 Mcu_Sip_PwrOn_AOSS_SLEEP_ENTRY_EXIT_Time;
static uint32 Mcu_Sip_PwrOn_POFF_COMPLETE_N_init_Time;
static uint32 Mcu_Sip_PwrOn_PM_PWR_EN_N_Step1_Time;
static uint32 Mcu_Sip_PwrOn_PMIC_FAST_POFF_EN_N_Step1_Time;
static uint32 Mcu_Sip_PwrOn_MM_OFF_REQ_Step1_Time;
static uint32 Mcu_Sip_PwrOn_LOW_POWER_ON_Step2_Time;
static uint32 Mcu_Sip_PwrOn_VB33_SIP_FREQ_Step2_Time;
static uint32 Mcu_Sip_PwrOn_PM_PWR_EN_N_Step3_Time;
static uint32 Mcu_Sip_PwrOn_PMIC_FAST_POFF_EN_N_Step3_Time;
static uint32 Mcu_Sip_PwrOn_MM_SUSPEND_REQ_N_Time;
static uint32 Mcu_Sip_PwrOn_STR_WAKE_Time;
static uint32 Mcu_Sip_PwrOn_PM_PSAIL_ERR_N_Time;
static uint32 Mcu_Sip_PwrOn_PMA_PS_HOLD_Init_Time;
static uint32 Mcu_Sip_PwrOn_POFF_COMPLETE_N_Chk_Time;
static uint32 Mcu_Sip_PwrOn_SOC_RESOUT_N_Time;
static uint32 Mcu_Sip_PwrOn_SAIL_RESOUT_N_Time;
static uint32 Mcu_Sip_PwrOn_PMA_PS_HOLD_Chk_Time;
static uint32 Mcu_Sip_PwrOn_PM_PWR_EN_N_Lo_ElapsedTime;
static uint32 Mcu_Sip_PwrOn_PM_PWR_EN_N_Step9_Time;

static uint8  Mcu_Sip_Resume_Step;
static uint32 Mcu_Sip_Resume_LOW_POWER_ON_Time;
static uint32 Mcu_Sip_Resume_VB33_SIP_FREQ_Time;
static uint32 Mcu_Sip_Resume_MM_SUSPEND_REQ_N_Time;
static uint32 Mcu_Sip_Resume_STR_WAKE_Time;

static uint8  Mcu_Sip_PwrOff_Step;
static uint32 Mcu_Sip_PwrOff_MM_OFF_REQ_Step1_Time;
static uint32 Mcu_Sip_PwrOff_MM_STBY_N_Chk_Time;
static uint32 Mcu_Sip_PwrOff_PMA_PS_HOLD_Chk_Time;
static uint32 Mcu_Sip_PwrOff_SOC_RESOUT_N_Chk_Time;
static uint32 Mcu_Sip_PwrOff_SAIL_RESOUT_N_Chk_Time;
static uint32 Mcu_Sip_PwrOff_POFF_COMPLETE_N_Chk_Time;
static uint32 Mcu_Sip_PwrOff_VB33_SIP_FREQ_Time;
static uint32 Mcu_Sip_PwrOff_VB33_SIP_ON_Time;
static uint32 Mcu_Sip_PwrOff_LOW_POWER_ON_Time;
static uint32 Mcu_Sip_PwrOff_PM_PWR_EN_N_Time;
static uint32 Mcu_Sip_PwrOff_PMIC_FAST_POFF_EN_N_Time;
static uint32 Mcu_Sip_PwrOff_MM_SUSPEND_REQ_N_Time;
static uint32 Mcu_Sip_PwrOff_STR_WAKE_Time;
static uint32 Mcu_Sip_PwrOff_MM_OFF_REQ_Step6_Time;

static uint8  Mcu_Sip_Standby_Step;
static uint32 Mcu_Sip_Standby_MM_SUSPEND_REQ_N_Time;
static uint32 Mcu_Sip_Standby_STR_WAKE_Time;
static uint32 Mcu_Sip_Standby_MM_STBY_N_Chk_Time;
static uint32 Mcu_Sip_Standby_AOSS_SLEEP_ENTRY_EXIT_Chk_Time;
static uint32 Mcu_Sip_Standby_VB33_SIP_FREQ_Time;
static uint32 Mcu_Sip_Standby_LOW_POWER_ON_Time;

#if (MCU_ERR_CHK == 1U)
/* 異常系チェック用STB定義 */
uint8 u1_s_Mcu_Err_dbg_state;
/* 異常系チェック用STB定義 */
#endif

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
  Function      : Mcu_Sip_Bon_Init
  Description   : 6-8-1,6-8-2,6-9,5-3,SIP起動全体の初期化処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_Sip_Bon_Init( void )
{
	/* ステップ判定用RAMの初期化 */
	Mcu_Sip_PwrOn_Step   = (uint8)MCU_SIP_PWRON_STEP_CMPLT;
	Mcu_Sip_Resume_Step  = (uint8)MCU_SIP_RESUME_STEP_CMPLT;
	Mcu_Sip_PwrOff_Step  = (uint8)MCU_SIP_PWROFF_STEP_CMPLT;
	Mcu_Sip_Standby_Step = (uint8)MCU_SIP_STANDBY_STEP_CMPLT;
	
	/* 待機時間測定用RAMの初期化 */
	/* SiP通常起動 */
	Mcu_Sip_PwrOn_VB33_SIP_ON_Time                 = 0u;
	Mcu_Sip_PwrOn_LOW_POWER_ON_Step1_Time          = 0u;
	Mcu_Sip_PwrOn_VB33_SIP_FREQ_Step1_Time         = 0u;
	Mcu_Sip_PwrOn_AOSS_SLEEP_ENTRY_EXIT_Time       = 0u;
	Mcu_Sip_PwrOn_POFF_COMPLETE_N_init_Time        = 0u;
	Mcu_Sip_PwrOn_PM_PWR_EN_N_Step1_Time           = 0u;
	Mcu_Sip_PwrOn_PMIC_FAST_POFF_EN_N_Step1_Time   = 0u;
	Mcu_Sip_PwrOn_MM_OFF_REQ_Step1_Time            = 0u;
	Mcu_Sip_PwrOn_LOW_POWER_ON_Step2_Time          = 0u;
	Mcu_Sip_PwrOn_VB33_SIP_FREQ_Step2_Time         = 0u;
	Mcu_Sip_PwrOn_PM_PWR_EN_N_Step3_Time           = 0u;
	Mcu_Sip_PwrOn_PMIC_FAST_POFF_EN_N_Step3_Time   = 0u;
	Mcu_Sip_PwrOn_MM_SUSPEND_REQ_N_Time            = 0u;
	Mcu_Sip_PwrOn_STR_WAKE_Time                    = 0u;
	Mcu_Sip_PwrOn_PM_PSAIL_ERR_N_Time              = 0u;
	Mcu_Sip_PwrOn_PMA_PS_HOLD_Init_Time            = 0u;
	Mcu_Sip_PwrOn_POFF_COMPLETE_N_Chk_Time         = 0u;
	Mcu_Sip_PwrOn_SOC_RESOUT_N_Time                = 0u;
	Mcu_Sip_PwrOn_SAIL_RESOUT_N_Time               = 0u;
	Mcu_Sip_PwrOn_PMA_PS_HOLD_Chk_Time             = 0u;
	Mcu_Sip_PwrOn_PM_PWR_EN_N_Lo_ElapsedTime       = 0u;
	Mcu_Sip_PwrOn_PM_PWR_EN_N_Step9_Time           = 0u;

	/* SiPレジューム起動 */
	Mcu_Sip_Resume_LOW_POWER_ON_Time               = 0u;
	Mcu_Sip_Resume_VB33_SIP_FREQ_Time              = 0u;
	Mcu_Sip_Resume_MM_SUSPEND_REQ_N_Time           = 0u;
	Mcu_Sip_Resume_STR_WAKE_Time                   = 0u;

	/* SiP電源OFF */
	Mcu_Sip_PwrOff_MM_OFF_REQ_Step1_Time           = 0u;
	Mcu_Sip_PwrOff_MM_STBY_N_Chk_Time              = 0u;
	Mcu_Sip_PwrOff_PMA_PS_HOLD_Chk_Time            = 0u;
	Mcu_Sip_PwrOff_SOC_RESOUT_N_Chk_Time           = 0u;
	Mcu_Sip_PwrOff_SAIL_RESOUT_N_Chk_Time          = 0u;
	Mcu_Sip_PwrOff_POFF_COMPLETE_N_Chk_Time        = 0u;
	Mcu_Sip_PwrOff_VB33_SIP_FREQ_Time              = 0u;
	Mcu_Sip_PwrOff_VB33_SIP_ON_Time                = 0u;
	Mcu_Sip_PwrOff_LOW_POWER_ON_Time               = 0u;
	Mcu_Sip_PwrOff_PM_PWR_EN_N_Time                = 0u;
	Mcu_Sip_PwrOff_PMIC_FAST_POFF_EN_N_Time        = 0u;
	Mcu_Sip_PwrOff_MM_SUSPEND_REQ_N_Time           = 0u;
	Mcu_Sip_PwrOff_STR_WAKE_Time                   = 0u;
	Mcu_Sip_PwrOff_MM_OFF_REQ_Step6_Time           = 0u;

	/* SiPスタンバイ */
	Mcu_Sip_Standby_MM_SUSPEND_REQ_N_Time          = 0u;
	Mcu_Sip_Standby_STR_WAKE_Time                  = 0u;
	Mcu_Sip_Standby_MM_STBY_N_Chk_Time             = 0u;
	Mcu_Sip_Standby_AOSS_SLEEP_ENTRY_EXIT_Chk_Time = 0u;
	Mcu_Sip_Standby_VB33_SIP_FREQ_Time             = 0u;
	Mcu_Sip_Standby_LOW_POWER_ON_Time              = 0u;

}

/*****************************************************************************
  Function      : Mcu_Sip_Wkup_Init
  Description   : 6-8-1,6-8-2,6-9,5-3,SIP起動全体の初期化処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_Sip_Wkup_Init( void )
{
	/* ステップ判定用RAMの初期化 */
	Mcu_Sip_PwrOn_Step   = (uint8)MCU_SIP_PWRON_STEP_CMPLT;
	Mcu_Sip_Resume_Step  = (uint8)MCU_SIP_RESUME_STEP_CMPLT;
	Mcu_Sip_PwrOff_Step  = (uint8)MCU_SIP_PWROFF_STEP_CMPLT;
	Mcu_Sip_Standby_Step = (uint8)MCU_SIP_STANDBY_STEP_CMPLT;
	
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOn_Req
  Description   : 6-8-1.SIP通常起動制御_初期化処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_Sip_PwrOn_Req( void )
{
	/* 現在起動ステップの初期化 */
	Mcu_Sip_PwrOn_Step   = (uint8)MCU_SIP_PWRON_STEP1;
	/* 他処理の無効化 */
	Mcu_Sip_Resume_Step  = (uint8)MCU_SIP_RESUME_STEP_CMPLT;
	Mcu_Sip_PwrOff_Step  = (uint8)MCU_SIP_PWROFF_STEP_CMPLT;
	Mcu_Sip_Standby_Step = (uint8)MCU_SIP_STANDBY_STEP_CMPLT;
	
	/* 待機時間測定用RAMの初期化 */
	Mcu_Sip_PwrOn_VB33_SIP_ON_Time               = 0u;
	Mcu_Sip_PwrOn_LOW_POWER_ON_Step1_Time        = 0u;
	Mcu_Sip_PwrOn_VB33_SIP_FREQ_Step1_Time       = 0u;
	Mcu_Sip_PwrOn_AOSS_SLEEP_ENTRY_EXIT_Time     = 0u;
	Mcu_Sip_PwrOn_POFF_COMPLETE_N_init_Time      = 0u;
	Mcu_Sip_PwrOn_PM_PWR_EN_N_Step1_Time         = 0u;
	Mcu_Sip_PwrOn_PMIC_FAST_POFF_EN_N_Step1_Time = 0u;
	Mcu_Sip_PwrOn_MM_OFF_REQ_Step1_Time          = 0u;
	Mcu_Sip_PwrOn_LOW_POWER_ON_Step2_Time        = 0u;
	Mcu_Sip_PwrOn_VB33_SIP_FREQ_Step2_Time       = 0u;
	Mcu_Sip_PwrOn_PM_PWR_EN_N_Step3_Time         = 0u;
	Mcu_Sip_PwrOn_PMIC_FAST_POFF_EN_N_Step3_Time = 0u;
	Mcu_Sip_PwrOn_MM_SUSPEND_REQ_N_Time          = 0u;
	Mcu_Sip_PwrOn_STR_WAKE_Time                  = 0u;
	Mcu_Sip_PwrOn_PM_PSAIL_ERR_N_Time            = 0u;
	Mcu_Sip_PwrOn_PMA_PS_HOLD_Init_Time          = 0u;
	Mcu_Sip_PwrOn_POFF_COMPLETE_N_Chk_Time       = 0u;
	Mcu_Sip_PwrOn_SOC_RESOUT_N_Time              = 0u;
	Mcu_Sip_PwrOn_SAIL_RESOUT_N_Time             = 0u;
	Mcu_Sip_PwrOn_PMA_PS_HOLD_Chk_Time           = 0u;
	Mcu_Sip_PwrOn_PM_PWR_EN_N_Lo_ElapsedTime     = 0u;
	Mcu_Sip_PwrOn_PM_PWR_EN_N_Step9_Time         = 0u;

}

/*****************************************************************************
  Function      : Mcu_Sip_Resume_Req
  Description   : 6-8-2.SIPレジューム制御_要求確認処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_Sip_Resume_Req( void )
{
	/* 現在起動ステップの初期化 */
	Mcu_Sip_Resume_Step  = (uint8)MCU_SIP_RESUME_STEP1;
	/* 他処理の無効化 */
	Mcu_Sip_PwrOn_Step   = (uint8)MCU_SIP_PWRON_STEP_CMPLT;
	Mcu_Sip_PwrOff_Step  = (uint8)MCU_SIP_PWROFF_STEP_CMPLT;
	Mcu_Sip_Standby_Step = (uint8)MCU_SIP_STANDBY_STEP_CMPLT;
	
	/* 待機時間測定用RAMの初期化 */
	Mcu_Sip_Resume_LOW_POWER_ON_Time     = 0u;
	Mcu_Sip_Resume_VB33_SIP_FREQ_Time    = 0u;
	Mcu_Sip_Resume_MM_SUSPEND_REQ_N_Time = 0u;
	Mcu_Sip_Resume_STR_WAKE_Time         = 0u;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOff_Init
  Description   : 6-9.SIP電源OFF制御_初期化処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_Sip_PwrOff_Req( void )
{
	/* 現在起動ステップの初期化 */
	Mcu_Sip_PwrOff_Step  = (uint8)MCU_SIP_PWROFF_STEP1;
	/* 他処理の無効化 */
	Mcu_Sip_PwrOn_Step   = (uint8)MCU_SIP_PWRON_STEP_CMPLT;
	Mcu_Sip_Resume_Step  = (uint8)MCU_SIP_RESUME_STEP_CMPLT;
	Mcu_Sip_Standby_Step = (uint8)MCU_SIP_STANDBY_STEP_CMPLT;

	/* 待機時間測定用RAMの初期化 */
	Mcu_Sip_PwrOff_MM_OFF_REQ_Step1_Time    = 0u;
	Mcu_Sip_PwrOff_MM_STBY_N_Chk_Time       = 0u;
	Mcu_Sip_PwrOff_PMA_PS_HOLD_Chk_Time     = 0u;
	Mcu_Sip_PwrOff_SOC_RESOUT_N_Chk_Time    = 0u;
	Mcu_Sip_PwrOff_SAIL_RESOUT_N_Chk_Time   = 0u;
	Mcu_Sip_PwrOff_POFF_COMPLETE_N_Chk_Time = 0u;
	Mcu_Sip_PwrOff_VB33_SIP_FREQ_Time       = 0u;
	Mcu_Sip_PwrOff_VB33_SIP_ON_Time         = 0u;
	Mcu_Sip_PwrOff_LOW_POWER_ON_Time        = 0u;
	Mcu_Sip_PwrOff_PM_PWR_EN_N_Time         = 0u;
	Mcu_Sip_PwrOff_PMIC_FAST_POFF_EN_N_Time = 0u;
	Mcu_Sip_PwrOff_MM_SUSPEND_REQ_N_Time    = 0u;
	Mcu_Sip_PwrOff_STR_WAKE_Time            = 0u;
	Mcu_Sip_PwrOff_MM_OFF_REQ_Step6_Time    = 0u;

}

/*****************************************************************************
  Function      : Mcu_Sip_Pwr_Init
  Description   : 5-3.スタンバイシーケンス_初期化処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_Sip_Standby_Req( void )
{
	/* 現在起動ステップの初期化 */
	Mcu_Sip_Standby_Step = (uint8)MCU_SIP_STANDBY_STEP1;
	/* 他処理の無効化 */
	Mcu_Sip_PwrOn_Step   = (uint8)MCU_SIP_PWRON_STEP_CMPLT;
	Mcu_Sip_Resume_Step  = (uint8)MCU_SIP_RESUME_STEP_CMPLT;
	Mcu_Sip_PwrOff_Step  = (uint8)MCU_SIP_PWROFF_STEP_CMPLT;

	/* 待機時間測定用RAMの初期化 */
	Mcu_Sip_Standby_MM_SUSPEND_REQ_N_Time          = 0u;
	Mcu_Sip_Standby_STR_WAKE_Time                  = 0u;
	Mcu_Sip_Standby_MM_STBY_N_Chk_Time             = 0u;
	Mcu_Sip_Standby_AOSS_SLEEP_ENTRY_EXIT_Chk_Time = 0u;
	Mcu_Sip_Standby_VB33_SIP_FREQ_Time             = 0u;
	Mcu_Sip_Standby_LOW_POWER_ON_Time              = 0u;
}

/*****************************************************************************
  Function      : Mcu_Sip_Pwr_MainFunction
  Description   : 6-8-1,6-8-2,6-9,5-3,SIP電源定期処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_Sip_Pwr_MainFunction( void ){

	/* SIP通常起動制御 */
	if(Mcu_Sip_PwrOn_Step != (uint8)MCU_SIP_PWRON_STEP_CMPLT){
		Mcu_Sip_PwrOn_MainFunction();
	}
	/* SIPレジューム制御 */
	if(Mcu_Sip_Resume_Step != (uint8)MCU_SIP_RESUME_STEP_CMPLT){
		Mcu_Sip_Resume_MainFunction();
	}
	/* SIP電源OFF制御 */
	if(Mcu_Sip_PwrOff_Step != (uint8)MCU_SIP_PWROFF_STEP_CMPLT){
		Mcu_Sip_PwrOff_MainFunction();
	}
	/* スタンバイシーケンス */
	if(Mcu_Sip_Standby_Step != (uint8)MCU_SIP_STANDBY_STEP_CMPLT){
		Mcu_Sip_Standby_MainFunction();
	}
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOn_MainFunction
  Description   : 6-8-1.SIP通常起動制御_定期処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOn_MainFunction( void )
{
	/* PM_PWR_EN_N=Lo(Step3-1)からの経過時間 */
	if(Mcu_Sip_PwrOn_PM_PWR_EN_N_Step3_Time == MCU_SIP_PWRON_TIME_INVALID){
		Mcu_Sip_PwrOn_PM_PWR_EN_N_Lo_ElapsedTime++; /* Step3-1完了後、次の周期からカウント */
		if(Mcu_Sip_PwrOn_PM_PWR_EN_N_Lo_ElapsedTime >= MCU_SIP_PWRON_T_PM_PWR_EN_N_ELPSD){
			Mcu_Sip_PwrOn_PM_PWR_EN_N_Lo_ElapsedTime = MCU_SIP_PWRON_T_PM_PWR_EN_N_ELPSD; /* 最大値でガード */
		}
	}

/* SiPへの電源供給開始など */
	if(Mcu_Sip_PwrOn_Step == (uint8)MCU_SIP_PWRON_STEP1){
        /* VB-33-SIP-ON = Hi */
		Mcu_Sip_PwrOn_VB33_SIP_ON();               /* STEP1-1 */
        /* LOW-POWER-ON = Lo(SIP電源投入と合わせてLo論理確定) */
		Mcu_Sip_PwrOn_LOW_POWER_ON_1();            /* STEP1-2 */
        /* VB33-SIP-FREQ = Lo(SIP電源投入と合わせてLo論理確定) */
		Mcu_Sip_PwrOn_VB33_SIP_FREQ_1();           /* STEP1-3 */
        /* PM_PWR_EN_N = Hi(SIP電源投入と合わせてHi論理確定) */
		Mcu_Sip_PwrOn_PM_PWR_EN_N_1();             /* STEP1-4 */
        /* PMIC_FAST_POFF_MIN = Lo(SIP電源投入と合わせてLo論理確定) */
		Mcu_Sip_PwrOn_PMIC_FAST_POFF_EN_N_1();     /* STEP1-5 */
        /* MM_OFF_REQ = Lo(SIP電源投入と合わせてLo論理確定) */
		Mcu_Sip_PwrOn_MM_OFF_REQ();                /* STEP1-6 */

		/* STEP1-1～STEP1-6が完了していれば次のSTEPに進める */
		if((Mcu_Sip_PwrOn_VB33_SIP_ON_Time == MCU_SIP_PWRON_TIME_INVALID) &&
		   (Mcu_Sip_PwrOn_LOW_POWER_ON_Step1_Time == MCU_SIP_PWRON_TIME_INVALID) &&
		   (Mcu_Sip_PwrOn_VB33_SIP_FREQ_Step1_Time == MCU_SIP_PWRON_TIME_INVALID) &&
		   (Mcu_Sip_PwrOn_PM_PWR_EN_N_Step1_Time == MCU_SIP_PWRON_TIME_INVALID) &&
		   (Mcu_Sip_PwrOn_PMIC_FAST_POFF_EN_N_Step1_Time == MCU_SIP_PWRON_TIME_INVALID) &&
		   (Mcu_Sip_PwrOn_MM_OFF_REQ_Step1_Time == MCU_SIP_PWRON_TIME_INVALID)){
			Mcu_Sip_PwrOn_Step = (uint8)MCU_SIP_PWRON_STEP2;
		}
	}
		
	if(Mcu_Sip_PwrOn_Step == (uint8)MCU_SIP_PWRON_STEP2){
		/* VB-33-SIP-ON = HiからtLOW-POWER-ON_HI経過後にLOW-POWER-ON = Hi */
		Mcu_Sip_PwrOn_LOW_POWER_ON_2();                          /* STEP2-1 */
/* Wait 35ms(電圧安定のため)*/
/* POFF_COMPLETE_N&AOSS_SLEEP_ENTRY_EXIT=Lo */
		/* VB-33-SIP-ON = Hiから35ms後に初期値(AOSS_SLEEP_ENTRY_EXIT=Lo)チェック */
		Mcu_Sip_PwrOn_InitValChk_AOSS_SLEEP_ENTRY_EXIT();        /* STEP2-2 */
		/* VB-33-SIP-ON = Hiから35ms後に初期値(POFF_COMPLETE_N=Lo)チェック */
		Mcu_Sip_PwrOn_InitValChk_POFF_COMPLETE_N();              /* STEP2-3 */
		
		/* STEP2-1が完了していれば次の処理に進める */
		if(Mcu_Sip_PwrOn_LOW_POWER_ON_Step2_Time == MCU_SIP_PWRON_TIME_INVALID){
			/* LOW-POWER-ON_HIからtVB33-SIP-FREQ_HI経過後にVB33-SIP-FREQ = HI */
			Mcu_Sip_PwrOn_VB33_SIP_FREQ_2();                    /* STEP2-4 */
		}
		
		/* STEP2-2~STEP2-4が完了していれば次のSTEPに進める */
		if((Mcu_Sip_PwrOn_AOSS_SLEEP_ENTRY_EXIT_Time == MCU_SIP_PWRON_TIME_INVALID) &&
		   (Mcu_Sip_PwrOn_POFF_COMPLETE_N_init_Time == MCU_SIP_PWRON_TIME_INVALID) &&
		   (Mcu_Sip_PwrOn_VB33_SIP_FREQ_Step2_Time == MCU_SIP_PWRON_TIME_INVALID)){
			Mcu_Sip_PwrOn_Step = (uint8)MCU_SIP_PWRON_STEP3;
		   }
	}
	
	if(Mcu_Sip_PwrOn_Step == (uint8)MCU_SIP_PWRON_STEP3){
/* PM_PWER_EN_N=Lo */
		/* AOSS_SLEEP_NETRY_EXIT,POFF_COMPLETE_N初期値チェックからtPM_PWR_EN_N_LO経過後にPM_PWR_EN_N = Lo */
		Mcu_Sip_PwrOn_PM_PWR_EN_N_2();          /* STEP3-1 */

		/* STEP3-1が完了していれば次のSTEPに進める */
		if(Mcu_Sip_PwrOn_PM_PWR_EN_N_Step3_Time == MCU_SIP_PWRON_TIME_INVALID){
			/* BEVCDCFD-277 【暫定管理】1Sボード起動用のMCUパッチ充て */
			/* STEP4とSTEP5のチェックをスキップする */
			/* Mcu_Sip_PwrOn_Step = (uint8)MCU_SIP_PWRON_STEP4;*/
			Mcu_Sip_PwrOn_Step = (uint8)MCU_SIP_PWRON_STEP6;
		}
		
	}
		
	if(Mcu_Sip_PwrOn_Step >= (uint8)MCU_SIP_PWRON_STEP3){
		/* STEP3以降のSTEP時に並行して処理を行い、シーケンスの完了判定前(STEP9)に完了しているか確認する */
		/* AOSS_SLEEP_NETRY_EXIT,POFF_COMPLETE_N初期値チェックからtPMIC_FAST_POFF_EN_N_HI経過後にPMIC_FAST_POFF_EN_N = Hi */
		Mcu_Sip_PwrOn_PMIC_FAST_POFF_EN_N_2();      /* STEP3-2 */
		/* AOSS_SLEEP_NETRY_EXIT,POFF_COMPLETE_N初期値チェックからtMM-SUSPEND_REQ_N経過後にMM-SUSPEND_REQ_N = Hi */
		Mcu_Sip_PwrOn_MM_SUSPEND_REQ_N();           /* STEP3-3 */
		/* AOSS_SLEEP_NETRY_EXIT,POFF_COMPLETE_N初期値チェックからtSTR_WAKE経過後にSTR_WAKE = Hi */
		Mcu_Sip_PwrOn_STR_WAKE();                   /* STEP3-4 */
	}
		
	if(Mcu_Sip_PwrOn_Step == (uint8)MCU_SIP_PWRON_STEP4){
/* PM_PSAIL_ERR_N=Lo */
		/* PM_PWR_EN_N = Lo後にPM_PSAIL_ERR_N初期値(Hi→Lo)チェック */
		Mcu_Sip_PwrOn_InitValChk_PM_PSAIL_ERR_N();       /* STEP4-1 */

		/*STEP4-1が完了していれば次の処理に進める*/
		if(Mcu_Sip_PwrOn_PM_PSAIL_ERR_N_Time == MCU_SIP_PWRON_TIME_INVALID){
			Mcu_Sip_PwrOn_Step = (uint8)MCU_SIP_PWRON_STEP5;
		}
	}

	if(Mcu_Sip_PwrOn_Step == (uint8)MCU_SIP_PWRON_STEP5){
/* PMA_PS_HOLD=Lo */
		/* PM_PSAIL_ERR_N = Lo後にPMA_PS_HOLD初期値(Lo)チェック */
		Mcu_Sip_PwrOn_InitValChk_PMA_PS_HOLD();          /* STEP5-1 */

		/*STEP5-1が完了していれば次の処理に進める*/
		if(Mcu_Sip_PwrOn_PMA_PS_HOLD_Init_Time == MCU_SIP_PWRON_TIME_INVALID){
			Mcu_Sip_PwrOn_Step = (uint8)MCU_SIP_PWRON_STEP6;
		}
	}

	if(Mcu_Sip_PwrOn_Step == (uint8)MCU_SIP_PWRON_STEP6){
/* PMA_COMPLETE_N=Hi */
		/* PMA_PS_HOLD = Lo後にPOFF_COMPLETE_N変化(Lo→Hi)チェック */
		Mcu_Sip_PwrOn_ValChk_POFF_COMPLETE_N();         /* STEP6-1 */

		/*STEP6-1が完了していれば次の処理に進める*/
		if(Mcu_Sip_PwrOn_POFF_COMPLETE_N_Chk_Time == MCU_SIP_PWRON_TIME_INVALID){
			Mcu_Sip_PwrOn_Step = (uint8)MCU_SIP_PWRON_STEP7;
		}
	}

	if(Mcu_Sip_PwrOn_Step == (uint8)MCU_SIP_PWRON_STEP7){
/* SOC_RESOUT_N & SAIL_RESOUT_N=Hi */
		/* POFF_COMPLETE_N変化(Hi)後にSOC_RESOUT_N変化(Hi)チェック */
		Mcu_Sip_PwrOn_ValChk_SOC_RESOUT_N();        /* STEP7-1 */
		/* POFF_COMPLETE_N変化(Hi)後にSAIL_RESOUT_N変化(Hi)チェック */
		Mcu_Sip_PwrOn_ValChk_SAIL_RESOUT_N();       /* STEP7-2 */
		
		/*STEP7-1,7-2が完了していれば次の処理に進める*/
		if((Mcu_Sip_PwrOn_SOC_RESOUT_N_Time == MCU_SIP_PWRON_TIME_INVALID) &&
		   (Mcu_Sip_PwrOn_SAIL_RESOUT_N_Time == MCU_SIP_PWRON_TIME_INVALID)){
			Mcu_Sip_PwrOn_Step = (uint8)MCU_SIP_PWRON_STEP8;
		}
	}

	if(Mcu_Sip_PwrOn_Step == (uint8)MCU_SIP_PWRON_STEP8){
/* PMA_PS_HOLD=Hi */
		/* SOC_RESOUT_N & SAIL_RESOUT_N=Hi変化後にPMA_PS_HOLD変化(Hi)チェック */
		Mcu_Sip_PwrOn_ValChk_PMA_PS_HOLD();     /* STEP8-1 */
		/*STEP8-1が完了、かつSTEP3-1から50ms経過していれば次の処理に進める*/
		if(Mcu_Sip_PwrOn_PMA_PS_HOLD_Chk_Time == MCU_SIP_PWRON_TIME_INVALID){
			Mcu_Sip_PwrOn_Step = (uint8)MCU_SIP_PWRON_STEP9;
		}
	}
	
	if(Mcu_Sip_PwrOn_Step == (uint8)MCU_SIP_PWRON_STEP9){
/* PM_PWR_EN_N=Hi */
		/* STEP8完了後tPM_PWR_EN_N_HI_P2経過後にPM_PWR_EN_N = Hi */
		Mcu_Sip_PwrOn_PM_PWR_EN_N_3();         /* STEP9-1 */

		/* STEP9-1とSTEP3-2~STEP3-4が完了していればBONシーケンス完了とする */
		if((Mcu_Sip_PwrOn_PMIC_FAST_POFF_EN_N_Step3_Time == MCU_SIP_PWRON_TIME_INVALID) &&
		   (Mcu_Sip_PwrOn_MM_SUSPEND_REQ_N_Time == MCU_SIP_PWRON_TIME_INVALID) &&
		   (Mcu_Sip_PwrOn_STR_WAKE_Time == MCU_SIP_PWRON_TIME_INVALID) &&
		   (Mcu_Sip_PwrOn_PM_PWR_EN_N_Step9_Time == MCU_SIP_PWRON_TIME_INVALID)){
			Mcu_Sip_PwrOn_Step = (uint8)MCU_SIP_PWRON_STEP_CMPLT;
		}
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_Pwr_mainFunction
  Description   : 6-8-2.SIPレジューム制御_定期処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_Resume_MainFunction( void )
{
/* SIPレジューム制御 */
	if(Mcu_Sip_Resume_Step == (uint8)MCU_SIP_RESUME_STEP1){
        /* 起動判断(SIPレジューム)からtLOW-POWER-ON経過後にLOW-POWER-ON = Hi */
		Mcu_Sip_Resume_LOW_POWER_ON();         /* STEP1-1 */
		
		/* STEP1-1が完了していれば次のSTEPに進める */
		if(Mcu_Sip_Resume_LOW_POWER_ON_Time == MCU_SIP_RESUME_TIME_INVALID){
			Mcu_Sip_Resume_Step = (uint8)MCU_SIP_RESUME_STEP2;
		}
	}
	
	if(Mcu_Sip_Resume_Step == (uint8)MCU_SIP_RESUME_STEP2){
		/* LOW-POWER-ON = HiからtVB33-SIP-FREQ経過後にVB33-SIP-FREQ = Hi */
		Mcu_Sip_Resume_VB33_SIP_FREQ();         /* STEP2-1 */
		
		/* STEP2-1が完了していれば次のSTEPに進める */
		if(Mcu_Sip_Resume_VB33_SIP_FREQ_Time == MCU_SIP_RESUME_TIME_INVALID){
			Mcu_Sip_Resume_Step = (uint8)MCU_SIP_RESUME_STEP3;
		}
	}
	
	if(Mcu_Sip_Resume_Step == (uint8)MCU_SIP_RESUME_STEP3){
		/* VB33-SIP-FREQ = HiからtMM_SUSPEND_REQ_N経過後にMM_SUSPEND_REQ_N = Hi */
		Mcu_Sip_Resume_MM_SUSPEND_REQ_N();           /* STEP3-1 */
		/* VB33-SIP-FREQ = HiからtSTR_WAKE経過後にSTR_WAKE = Hi */
		Mcu_Sip_Resume_STR_WAKE();                   /* STEP3-2 */

		/* STEP3-1とSTEP3-2が完了していれば次のSTEPに進める */
		if((Mcu_Sip_Resume_MM_SUSPEND_REQ_N_Time == MCU_SIP_RESUME_TIME_INVALID)&&
		   (Mcu_Sip_Resume_STR_WAKE_Time == MCU_SIP_RESUME_TIME_INVALID)){
			Mcu_Sip_Resume_Step = (uint8)MCU_SIP_RESUME_STEP_CMPLT;
		}
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOff_MainFunction
  Description   : 6-9.SIP電源OFF制御_定期処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOff_MainFunction( void )
{
	if(Mcu_Sip_PwrOff_Step == MCU_SIP_PWROFF_STEP1){
		Mcu_Sip_PwrOff_MM_OFF_REQ_1(); /* STEP1-1 */
		
		/* STEP1-1が完了していれば次のSTEPに進める */
		if(Mcu_Sip_PwrOff_MM_OFF_REQ_Step1_Time == MCU_SIP_PWROFF_TIME_INVALID){
			/* BEVCDCFD-277 【暫定管理】1Sボード起動用のMCUパッチ充て */
			/* STEP2とSTEP3のチェックをスキップする */
			/* Mcu_Sip_PwrOff_Step = (uint8)MCU_SIP_PWROFF_STEP2;*/
			Mcu_Sip_PwrOff_Step = (uint8)MCU_SIP_PWROFF_STEP4;
		}
	}

/* MM_STBY_N =Lo? */
	if(Mcu_Sip_PwrOff_Step == MCU_SIP_PWROFF_STEP2){
		Mcu_Sip_PwrOff_ValChk_MM_STBY_N(); /* STEP2-1 */

		/* STEP2-1が完了していれば次の処理に進める */
		if (Mcu_Sip_PwrOff_MM_STBY_N_Chk_Time == MCU_SIP_PWROFF_TIME_INVALID){
			Mcu_Sip_PwrOff_Step = (uint8)MCU_SIP_PWROFF_STEP3;
		}
	}

/* PMA_PS_HOLD =Lo? */
	if(Mcu_Sip_PwrOff_Step == MCU_SIP_PWROFF_STEP3){
		Mcu_Sip_PwrOff_ValChk_PMA_PS_HOLD(); /* STEP3-1 */

		/* STEP3-1が完了していれば次の処理に進める */
		if (Mcu_Sip_PwrOff_PMA_PS_HOLD_Chk_Time == MCU_SIP_PWROFF_TIME_INVALID){
			Mcu_Sip_PwrOff_Step = (uint8)MCU_SIP_PWROFF_STEP4;
		}
	}

/* SOC_RESOUT_N & SAIL_RESOUT_N & POFF_COMPLETE_N =Lo? */
	if(Mcu_Sip_PwrOff_Step == MCU_SIP_PWROFF_STEP4){
		Mcu_Sip_PwrOff_ValChk_SOC_RESOUT_N();    /* STEP4-1 */
		Mcu_Sip_PwrOff_ValChk_SAIL_RESOUT_N();   /* STEP4-2 */
		Mcu_Sip_PwrOff_ValChk_POFF_COMPLETE_N(); /* STEP4-3 */

		/* STEP4-1~4-3が完了していれば次の処理に進める */
		if((Mcu_Sip_PwrOff_SOC_RESOUT_N_Chk_Time == MCU_SIP_PWROFF_TIME_INVALID) &&
		   (Mcu_Sip_PwrOff_SAIL_RESOUT_N_Chk_Time == MCU_SIP_PWROFF_TIME_INVALID) &&
		   (Mcu_Sip_PwrOff_POFF_COMPLETE_N_Chk_Time == MCU_SIP_PWROFF_TIME_INVALID)){
			 Mcu_Sip_PwrOff_Step = (uint8)MCU_SIP_PWROFF_STEP5;
		}
	}

	if(Mcu_Sip_PwrOff_Step == MCU_SIP_PWROFF_STEP5){
		Mcu_Sip_PwrOff_VB33_SIP_FREQ(); /* STEP5-1 */

		/* STEP5-1が完了していれば次のSTEPに進める */
		if (Mcu_Sip_PwrOff_VB33_SIP_FREQ_Time == MCU_SIP_PWROFF_TIME_INVALID){
			Mcu_Sip_PwrOff_Step = (uint8)MCU_SIP_PWROFF_STEP6;
		}
	}

	if(Mcu_Sip_PwrOff_Step == MCU_SIP_PWROFF_STEP6){
		Mcu_Sip_PwrOff_VB33_SIP_ON();         /* STEP6-1 */
		Mcu_Sip_PwrOff_LOW_POWER_ON();        /* STEP6-2 */
		Mcu_Sip_PwrOff_PM_PWR_EN_N();         /* STEP6-3 */
		Mcu_Sip_PwrOff_PMIC_FAST_POFF_EN_N(); /* STEP6-4 */
		Mcu_Sip_PwrOff_MM_SUSPEND_REQ_N();    /* STEP6-5 */
		Mcu_Sip_PwrOff_STR_WAKE();            /* STEP6-6 */
		Mcu_Sip_PwrOff_MM_OFF_REQ_2();        /* STEP6-7 */
	
		/* STEP6-1～6-7が完了していれば次のSTEPに進める */
		if((Mcu_Sip_PwrOff_VB33_SIP_ON_Time == MCU_SIP_PWROFF_TIME_INVALID) &&
		   (Mcu_Sip_PwrOff_LOW_POWER_ON_Time == MCU_SIP_PWROFF_TIME_INVALID) &&
		   (Mcu_Sip_PwrOff_PM_PWR_EN_N_Time == MCU_SIP_PWROFF_TIME_INVALID) &&
		   (Mcu_Sip_PwrOff_PMIC_FAST_POFF_EN_N_Time == MCU_SIP_PWROFF_TIME_INVALID) &&
		   (Mcu_Sip_PwrOff_MM_SUSPEND_REQ_N_Time == MCU_SIP_PWROFF_TIME_INVALID) &&
		   (Mcu_Sip_PwrOff_STR_WAKE_Time == MCU_SIP_PWROFF_TIME_INVALID) &&
		   (Mcu_Sip_PwrOff_MM_OFF_REQ_Step6_Time == MCU_SIP_PWROFF_TIME_INVALID)){
			Mcu_Sip_PwrOff_Step = (uint8)MCU_SIP_PWROFF_STEP_CMPLT;
		}
	}
	
	else{ /* SIP電源OFF制御が未完了の場合 */
		  /* 何もしない */
	}

	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_Stanby_MainFunction
  Description   : 5-3.スタンバイシーケンス_定期処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_Standby_MainFunction( void )
{
	if(Mcu_Sip_Standby_Step == MCU_SIP_STANDBY_STEP1){
		Mcu_Sip_Standby_MM_SUSPEND_REQ_N();           /* STEP1-1 */
		Mcu_Sip_Standby_STR_WAKE();                   /* STEP1-2 */
			
		/* STEP1-1～STEP1-2が完了していれば次のSTEPに進める */
		if((Mcu_Sip_Standby_MM_SUSPEND_REQ_N_Time == MCU_SIP_STANDBY_TIME_INVALID) &&
		   (Mcu_Sip_Standby_STR_WAKE_Time == MCU_SIP_STANDBY_TIME_INVALID)){
			/* BEVCDCFD-277 【暫定管理】1Sボード起動用のMCUパッチ充て */
			/* STEP2のチェックをスキップする */
			/* Mcu_Sip_Standby_Step = (uint8)MCU_SIP_STANDBY_STEP2;*/
			Mcu_Sip_Standby_Step = (uint8)MCU_SIP_STANDBY_STEP3;
		}
	}

/* MM_STBY_N =Lo? */
	if(Mcu_Sip_Standby_Step == MCU_SIP_STANDBY_STEP2){
		Mcu_Sip_Standby_ValChk_MM_STBY_N(); /* STEP2-1 */
		
		/* STEP2-1が完了していれば次の処理に進める */
		if(Mcu_Sip_Standby_MM_STBY_N_Chk_Time == MCU_SIP_STANDBY_TIME_INVALID){
			Mcu_Sip_Standby_Step = (uint8)MCU_SIP_STANDBY_STEP3;
		}
	}
	
/* AOSS_SLEEP_ENTRY_EXIT = Hi? */
	if(Mcu_Sip_Standby_Step == MCU_SIP_STANDBY_STEP3){
		Mcu_Sip_Standby_ValChk_AOSS_SLEEP_ENTRY_EXIT();        /* STEP3-1 */
			
		/* STEP3-1が完了していれば次の処理に進める */
		if(Mcu_Sip_Standby_AOSS_SLEEP_ENTRY_EXIT_Chk_Time == MCU_SIP_PWRON_TIME_INVALID){
			Mcu_Sip_Standby_Step = (uint8)MCU_SIP_STANDBY_STEP4;
		}
	}
	
	if(Mcu_Sip_Standby_Step == MCU_SIP_STANDBY_STEP4){
		Mcu_Sip_Standby_VB33_SIP_FREQ();         /* STEP4-1 */
			
		/* STEP4-1が完了していれば次のSTEPに進める */
		if(Mcu_Sip_Standby_VB33_SIP_FREQ_Time == MCU_SIP_PWRON_TIME_INVALID){
			Mcu_Sip_Standby_Step = (uint8)MCU_SIP_STANDBY_STEP5;
		}
	}

	if(Mcu_Sip_Standby_Step == MCU_SIP_STANDBY_STEP5){
		Mcu_Sip_Standby_LOW_POWER_ON();          /* STEP5-1 */
		
		/* STEP5-1が完了していれば次のSTEPに進める */
		if(Mcu_Sip_Standby_LOW_POWER_ON_Time == MCU_SIP_PWRON_TIME_INVALID){
			Mcu_Sip_Standby_Step = (uint8)MCU_SIP_STANDBY_STEP_CMPLT;
		}
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOn_VB33_SIP_ON
  Description   : SIP電源制御 VB33-SIP-ON (3.3V：SIP電源)
                  (ソフトウェア処理：MCU →DDコン)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOn_VB33_SIP_ON( void )
{
	if(Mcu_Sip_PwrOn_VB33_SIP_ON_Time != MCU_SIP_PWRON_TIME_INVALID){
#if 0
		if(Mcu_Sip_PwrOn_VB33_SIP_ON_Time >= MCU_SIP_PWRON_T_VB33_SIP_ON){ /* tVB33-SIP-ON経過したか */
#endif
			(void)Dio_WriteChannel(DIO_ID_APORT5_CH1, MCU_DIO_HIGH);
			Mcu_Sip_PwrOn_VB33_SIP_ON_Time = MCU_SIP_PWRON_TIME_INVALID;      /* 経過していれば計測完了を設定 */
#if 0
		}
		else{
			Mcu_Sip_PwrOn_VB33_SIP_ON_Time++;
		}
#endif
	}
	
	return;
}
/*****************************************************************************
  Function      : Mcu_Sip_PwrOn_LOW_POWER_ON_1
  Description   : SIP電源制御 LOW-POWER-ON (VB33-SIPのDDコンモード切替)
                  (ソフトウェア処理：MCU →DDコン)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOn_LOW_POWER_ON_1( void )
{
	if(Mcu_Sip_PwrOn_LOW_POWER_ON_Step1_Time != MCU_SIP_PWRON_TIME_INVALID){
#if 0
		if(Mcu_Sip_PwrOn_LOW_POWER_ON_Step1_Time >= MCU_SIP_PWRON_T_LOW_POWER_ON_LO){ /* SIP電源投入と合わせて、Lo論理確定させる*/
#endif
			(void)Dio_WriteChannel(DIO_ID_PORT10_CH5, MCU_DIO_LOW);
			Mcu_Sip_PwrOn_LOW_POWER_ON_Step1_Time = MCU_SIP_PWRON_TIME_INVALID;
#if 0
		}
		else{
			Mcu_Sip_PwrOn_LOW_POWER_ON_Step1_Time++;
		}
#endif
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOn_VB33_SIP_FREQ_1
  Description   : SIP電源制御 VB33-SIP-FREQ (3.3V：SIP電源)
                  (ソフトウェア処理：MCU →DDコン)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOn_VB33_SIP_FREQ_1( void )
{
	if(Mcu_Sip_PwrOn_VB33_SIP_FREQ_Step1_Time != MCU_SIP_PWRON_TIME_INVALID){
#if 0
		if(Mcu_Sip_PwrOn_VB33_SIP_FREQ_Step1_Time >= MCU_SIP_PWRON_T_VB33_SIP_FREQ_LO){ /* SIP電源投入と合わせて、Lo論理確定させる*/
#endif
			vd_g_Pwm_SetPeriodAndDuty((U1)PWM_CH_01_DDC_SIP_FREQ, (U2)MCU_SIP_PWM_PERIOD_OFF, (U2)MCU_SIP_PWM_DUTYCYCLE_OFF);
			Mcu_Sip_PwrOn_VB33_SIP_FREQ_Step1_Time = MCU_SIP_PWRON_TIME_INVALID;
#if 0	
		}
		else{
			Mcu_Sip_PwrOn_VB33_SIP_FREQ_Step1_Time++;
		}
#endif
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOn_PM_PWR_EN_N_1
  Description   : PMIC制御(電源ON/OFF) PM_PWR_EN_N
                  (ソフトウェア処理：MCU →SOC PMIC)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOn_PM_PWR_EN_N_1( void )
{
	if(Mcu_Sip_PwrOn_PM_PWR_EN_N_Step1_Time != MCU_SIP_PWRON_TIME_INVALID){
#if 0
		if(Mcu_Sip_PwrOn_PM_PWR_EN_N_Step1_Time >= MCU_SIP_PWRON_T_PM_PWR_EN_N_STEP1_LO){ /* SIP電源投入と合わせて、Lo論理確定させる*/
#endif
			(void)Dio_WriteChannel(DIO_ID_PORT8_CH2, MCU_DIO_HIGH);
			Mcu_Sip_PwrOn_PM_PWR_EN_N_Step1_Time = MCU_SIP_PWRON_TIME_INVALID;
#if 0
		}
		else{
			Mcu_Sip_PwrOn_PM_PWR_EN_N_Step1_Time++;
		}
#endif
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOn_PMIC_FAST_POFF_EN_N_1
  Description   : PMIC制御(電源ON/OFF) PMIC_FAST_POFF_EN_N
                  (ソフトウェア処理：MCU →SOC PMIC)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOn_PMIC_FAST_POFF_EN_N_1( void )
{
	if(Mcu_Sip_PwrOn_PMIC_FAST_POFF_EN_N_Step1_Time != MCU_SIP_PWRON_TIME_INVALID){
#if 0
		if(Mcu_Sip_PwrOn_PMIC_FAST_POFF_EN_N_Step1_Time >= MCU_SIP_PWRON_T_PMIC_FAST_POFF_EN_N_LO){ /* SIP電源投入と合わせてLo論理確定させる*/
#endif
			(void)Dio_WriteChannel(DIO_ID_PORT8_CH0, MCU_DIO_LOW);
			Mcu_Sip_PwrOn_PMIC_FAST_POFF_EN_N_Step1_Time = MCU_SIP_PWRON_TIME_INVALID;
#if 0
		}
		else{
			Mcu_Sip_PwrOn_PMIC_FAST_POFF_EN_N_Step1_Time++;
		}
#endif
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOn_MM_OFF_REQ
  Description   : SOC終了制御(電源OFF) MM_OFF_REQ (ソフトウェア処理：MCU →SOC)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOn_MM_OFF_REQ( void )
{
	if(Mcu_Sip_PwrOn_MM_OFF_REQ_Step1_Time != MCU_SIP_PWRON_TIME_INVALID){
#if 0
		if(Mcu_Sip_PwrOn_MM_OFF_REQ_Step1_Time >= MCU_SIP_PWRON_T_MM_OFF_REQ){  /* SIP電源投入と合わせて、Lo論理確定させる*/
#endif
			(void)Dio_WriteChannel(DIO_ID_PORT17_CH2, MCU_DIO_LOW);
			Mcu_Sip_PwrOn_MM_OFF_REQ_Step1_Time = MCU_SIP_PWRON_TIME_INVALID;
#if 0
		}
		else{
			Mcu_Sip_PwrOn_MM_OFF_REQ_Step1_Time++;
		}
#endif
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOn_LOW_POWER_ON_2
  Description   : SIP電源制御 LOW-POWER-ON (VB33-SIPのDDコンモード切替)
                  (ソフトウェア処理：MCU →DDコン)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOn_LOW_POWER_ON_2( void )
{
	if(Mcu_Sip_PwrOn_LOW_POWER_ON_Step2_Time != MCU_SIP_PWRON_TIME_INVALID){
		if(Mcu_Sip_PwrOn_LOW_POWER_ON_Step2_Time >= MCU_SIP_PWRON_T_LOW_POWER_ON_HI){ /* tLOW-POWER-ON_HI経過したか */
			(void)Dio_WriteChannel(DIO_ID_PORT10_CH5, MCU_DIO_HIGH);
			Mcu_Sip_PwrOn_LOW_POWER_ON_Step2_Time = MCU_SIP_PWRON_TIME_INVALID;          /* 経過していれば計測完了を設定 */
		}
	
		else{
			Mcu_Sip_PwrOn_LOW_POWER_ON_Step2_Time++;
		}
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOn_InitValChk_AOSS_SLEEP_ENTRY_EXIT
  Description   : 電源など状態監視(QC標準系) AOSS_SLEEP_ENTRY_EXIT
                  (ソフトウェア処理(QCソフト)：SOC PMIC →MCU)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOn_InitValChk_AOSS_SLEEP_ENTRY_EXIT( void )
{
	uint8 read_lv;
    
	if(Mcu_Sip_PwrOn_AOSS_SLEEP_ENTRY_EXIT_Time != MCU_SIP_PWRON_TIME_INVALID){
		if(Mcu_Sip_PwrOn_AOSS_SLEEP_ENTRY_EXIT_Time >= MCU_SIP_PWRON_T_AOSS_SLEEP_ENTRY_EXIT){
			read_lv = Dio_ReadChannel(DIO_ID_PORT17_CH0);

			if( read_lv == (uint8)MCU_DIO_LOW){
				Mcu_Sip_PwrOn_AOSS_SLEEP_ENTRY_EXIT_Time = MCU_SIP_PWRON_TIME_INVALID;
			}
		}
		
		else{
			Mcu_Sip_PwrOn_AOSS_SLEEP_ENTRY_EXIT_Time++;
#if (MCU_ERR_CHK == 1U)
			u1_s_Mcu_Err_dbg_state = MCU_ERR_BON_STEP2_2; /* TP */
#endif
		}
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOn_InitValChk_POFF_COMPLETE_N
  Description   : 電源など状態監視(QC標準系) POFF_COMPLETE_N
                  (ソフトウェア処理(QCソフト)：SOC PMIC →MCU)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOn_InitValChk_POFF_COMPLETE_N( void )
{
	uint8 read_lv;
    
	if(Mcu_Sip_PwrOn_POFF_COMPLETE_N_init_Time != MCU_SIP_PWRON_TIME_INVALID){
		if(Mcu_Sip_PwrOn_POFF_COMPLETE_N_init_Time >= MCU_SIP_PWRON_T_POFF_COMPLETE_N){
		read_lv = Dio_ReadChannel(DIO_ID_PORT8_CH6);

			if( read_lv == (uint8)MCU_DIO_LOW){
				Mcu_Sip_PwrOn_POFF_COMPLETE_N_init_Time = MCU_SIP_PWRON_TIME_INVALID;
			}
		}
		
		else{
			Mcu_Sip_PwrOn_POFF_COMPLETE_N_init_Time++;
#if (MCU_ERR_CHK == 1U)
			u1_s_Mcu_Err_dbg_state = MCU_ERR_BON_STEP2_3; /* TP */
#endif
		}
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOn_VB33_SIP_FREQ_2
  Description   : SIP電源制御 VB33-SIP-FREQ (3.3V：SIP電源)
                  (ソフトウェア処理：MCU →DDコン)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOn_VB33_SIP_FREQ_2( void )
{
	if(Mcu_Sip_PwrOn_VB33_SIP_FREQ_Step2_Time != MCU_SIP_PWRON_TIME_INVALID){
		if(Mcu_Sip_PwrOn_VB33_SIP_FREQ_Step2_Time >= MCU_SIP_PWRON_T_VB33_SIP_FREQ){  /* tVB33-SIP-FREQ経過したか */
			vd_g_Pwm_SetPeriodAndDuty((U1)PWM_CH_01_DDC_SIP_FREQ, (U2)MCU_SIP_PWM_PERIOD_DEF, (U2)MCU_SIP_PWM_DUTYCYCLE_DEF);
			Mcu_Sip_PwrOn_VB33_SIP_FREQ_Step2_Time = MCU_SIP_PWRON_TIME_INVALID;         /* 経過していれば計測完了を設定 */
		}
	
		else{
			Mcu_Sip_PwrOn_VB33_SIP_FREQ_Step2_Time++;
		}
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOn_PM_PWR_EN_N_2
  Description   : PMIC制御(電源ON/OFF) PM_PWR_EN_N
                  (ソフトウェア処理：MCU →SOC PMIC)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOn_PM_PWR_EN_N_2( void )
{
	if(Mcu_Sip_PwrOn_PM_PWR_EN_N_Step3_Time != MCU_SIP_PWRON_TIME_INVALID){
		if(Mcu_Sip_PwrOn_PM_PWR_EN_N_Step3_Time >= MCU_SIP_PWRON_T_PM_PWR_EN_N_LO){  /* tPM_PWR_EN_N_LO経過したか */
			(void)Dio_WriteChannel(DIO_ID_PORT8_CH2, MCU_DIO_LOW);
			Mcu_Sip_PwrOn_PM_PWR_EN_N_Step3_Time = MCU_SIP_PWRON_TIME_INVALID;          /* 経過していれば計測完了を設定 */
		}
	
		else{
			Mcu_Sip_PwrOn_PM_PWR_EN_N_Step3_Time++;
		}
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOn_PMIC_FAST_POFF_EN_N_2
  Description   : PMIC制御(電源ON/OFF) PMIC_FAST_POFF_EN_N
                  (ソフトウェア処理：MCU →SOC PMIC)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOn_PMIC_FAST_POFF_EN_N_2( void )
{
	if(Mcu_Sip_PwrOn_PMIC_FAST_POFF_EN_N_Step3_Time != MCU_SIP_PWRON_TIME_INVALID){
		if(Mcu_Sip_PwrOn_PMIC_FAST_POFF_EN_N_Step3_Time >= MCU_SIP_PWRON_T_PMIC_FAST_POFF_EN_N){  /* tPMIC_FAST_POFF_EN_N経過したか */
			(void)Dio_WriteChannel(DIO_ID_PORT8_CH0, MCU_DIO_HIGH);
			Mcu_Sip_PwrOn_PMIC_FAST_POFF_EN_N_Step3_Time = MCU_SIP_PWRON_TIME_INVALID;          /* 経過していれば計測完了を設定 */
		}
	
		else{
			Mcu_Sip_PwrOn_PMIC_FAST_POFF_EN_N_Step3_Time++;
		}
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOn_MM_SUSPEND_REQ_N
  Description   : STR制御 MM_SUSPEND_REQ_N (ソフトウェア処理：MCU →SOC 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOn_MM_SUSPEND_REQ_N( void )
{
	if(Mcu_Sip_PwrOn_MM_SUSPEND_REQ_N_Time != MCU_SIP_PWRON_TIME_INVALID){
		if(Mcu_Sip_PwrOn_MM_SUSPEND_REQ_N_Time >= MCU_SIP_PWRON_T_MM_SUSPEND_REQ_N){  /* tMM_SUSPEND_REQ_N経過したか */
			(void)Dio_WriteChannel(DIO_ID_PORT10_CH10, MCU_DIO_HIGH);
			Mcu_Sip_PwrOn_MM_SUSPEND_REQ_N_Time = MCU_SIP_PWRON_TIME_INVALID;           /* 経過していれば計測完了を設定 */
		}
	
		else{
			Mcu_Sip_PwrOn_MM_SUSPEND_REQ_N_Time++;
		}
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOn_STR_WAKE
  Description   : STR制御 STR_WAKE (ソフトウェア処理：MCU →SOC 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOn_STR_WAKE( void )
{
	if(Mcu_Sip_PwrOn_STR_WAKE_Time != MCU_SIP_PWRON_TIME_INVALID){
		if(Mcu_Sip_PwrOn_STR_WAKE_Time >= MCU_SIP_PWRON_T_STR_WAKE){  /* tSTR_WAKE経過したか */
			(void)Dio_WriteChannel(DIO_ID_PORT22_CH0, MCU_DIO_HIGH);
			Mcu_Sip_PwrOn_STR_WAKE_Time = MCU_SIP_PWRON_TIME_INVALID;           /* 経過していれば計測完了を設定 */
		}
	
		else{
			Mcu_Sip_PwrOn_STR_WAKE_Time++;
		}
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOn_InitValChk_PM_PSAIL_ERR_N
  Description   : 電源など状態監視(QC標準系) PM_PSAIL_ERR_N
                  (ソフトウェア処理(QCソフト)：SOC →MCU)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOn_InitValChk_PM_PSAIL_ERR_N( void )
{
	uint8 read_lv;
    
	if( Mcu_Sip_PwrOn_PM_PSAIL_ERR_N_Time != MCU_SIP_PWRON_TIME_INVALID){
		read_lv = Dio_ReadChannel(DIO_ID_PORT8_CH4); /* P8_4 */

		if( read_lv == (uint8)MCU_DIO_LOW){
			Mcu_Sip_PwrOn_PM_PSAIL_ERR_N_Time = MCU_SIP_PWRON_TIME_INVALID;
		}
#if (MCU_ERR_CHK == 1U)
		u1_s_Mcu_Err_dbg_state = MCU_ERR_BON_STEP4_1; /* TP */
#endif
	}

	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOn_InitValChk_PMA_PS_HOLD
  Description   : 電源など状態監視(QC標準系) PMA_PS_HOLD
                  (ソフトウェア処理(QCソフト)：SOC →MCU)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOn_InitValChk_PMA_PS_HOLD( void )
{
	uint8 read_lv;
    
	if( Mcu_Sip_PwrOn_PMA_PS_HOLD_Init_Time != MCU_SIP_PWRON_TIME_INVALID){
		read_lv = Dio_ReadChannel(DIO_ID_PORT3_CH1);

		if( read_lv == (uint8)MCU_DIO_LOW){
			Mcu_Sip_PwrOn_PMA_PS_HOLD_Init_Time = MCU_SIP_PWRON_TIME_INVALID;
		}
#if (MCU_ERR_CHK == 1U)
		u1_s_Mcu_Err_dbg_state = MCU_ERR_BON_STEP5_1; /* TP */
#endif
	}

	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOn_ValChk_POFF_COMPLETE_N
  Description   : 電源など状態監視(QC標準系) POFF_COMPLETE_N
                  (ソフトウェア処理(QCソフト)：SOC PMIC →MCU)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOn_ValChk_POFF_COMPLETE_N( void )
{
	uint8 read_lv;
    
	if(Mcu_Sip_PwrOn_POFF_COMPLETE_N_Chk_Time != MCU_SIP_PWRON_TIME_INVALID){
		read_lv = Dio_ReadChannel(DIO_ID_PORT8_CH6);

		if( read_lv == (uint8)MCU_DIO_HIGH){
			Mcu_Sip_PwrOn_POFF_COMPLETE_N_Chk_Time = MCU_SIP_PWRON_TIME_INVALID;
		}
#if (MCU_ERR_CHK == 1U)
		u1_s_Mcu_Err_dbg_state = MCU_ERR_BON_STEP6_1; /* TP */
#endif
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOn_ValChk_SOC_RESOUT_N
  Description   : 電源など状態監視(QC標準系) SOC_RES_OUT_N
                  (ソフトウェア処理(QCソフト)：SOC PMIC →MCU)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOn_ValChk_SOC_RESOUT_N( void )
{
	uint8 read_lv;
    
	if(Mcu_Sip_PwrOn_SOC_RESOUT_N_Time != MCU_SIP_PWRON_TIME_INVALID){
		read_lv = Dio_ReadChannel(DIO_ID_PORT8_CH3);

		if( read_lv == (uint8)MCU_DIO_HIGH){
			Mcu_Sip_PwrOn_SOC_RESOUT_N_Time = MCU_SIP_PWRON_TIME_INVALID;
		}
#if (MCU_ERR_CHK == 1U)
		u1_s_Mcu_Err_dbg_state = MCU_ERR_BON_STEP7_1; /* TP */
#endif
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOn_ValChk_SAIL_RESOUT_N
  Description   : SAIL状態監視 SAIL_RES_OUT_N
                  (ソフトウェア処理(QCソフト)：SOC →MCU)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOn_ValChk_SAIL_RESOUT_N( void )
{
	uint8 read_lv;
    
	if(Mcu_Sip_PwrOn_SAIL_RESOUT_N_Time != MCU_SIP_PWRON_TIME_INVALID){
		read_lv = Dio_ReadChannel(DIO_ID_PORT8_CH8);

		if( read_lv == (uint8)MCU_DIO_HIGH){
			Mcu_Sip_PwrOn_SAIL_RESOUT_N_Time = MCU_SIP_PWRON_TIME_INVALID;
		}
#if (MCU_ERR_CHK == 1U)
		u1_s_Mcu_Err_dbg_state = MCU_ERR_BON_STEP7_2; /* TP */
#endif
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOn_ValChk_PMA_PS_HOLD
  Description   : 電源など状態監視(QC標準系) PMA_PS_HOLD
                  (ソフトウェア処理(QCソフト)：SOC →MCU)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOn_ValChk_PMA_PS_HOLD( void )
{
	uint8 read_lv;
    
	if( Mcu_Sip_PwrOn_PMA_PS_HOLD_Chk_Time != MCU_SIP_PWRON_TIME_INVALID){
		read_lv = Dio_ReadChannel(DIO_ID_PORT3_CH1);

		if( read_lv == (uint8)MCU_DIO_HIGH){
			Mcu_Sip_PwrOn_PMA_PS_HOLD_Chk_Time = MCU_SIP_PWRON_TIME_INVALID;
		}
#if (MCU_ERR_CHK == 1U)
		u1_s_Mcu_Err_dbg_state = MCU_ERR_BON_STEP8_1; /* TP */
#endif
	}

	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOn_PM_PWR_EN_N_3
  Description   : PMIC制御(電源ON/OFF) PM_PWR_EN_N
                  (ソフトウェア処理：MCU →SOC PMIC
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOn_PM_PWR_EN_N_3( void )
{
	if(Mcu_Sip_PwrOn_PM_PWR_EN_N_Step9_Time != MCU_SIP_PWRON_TIME_INVALID){
		if(Mcu_Sip_PwrOn_PM_PWR_EN_N_Step9_Time >= MCU_SIP_PWRON_T_PM_PWR_EN_N_HI_P2){  /* tPM_PWR_EN_N_HI_P2経過したか */
			if (Mcu_Sip_PwrOn_PM_PWR_EN_N_Lo_ElapsedTime >= MCU_SIP_PWRON_T_PM_PWR_EN_N_ELPSD){
				(void)Dio_WriteChannel(DIO_ID_PORT8_CH2, MCU_DIO_HIGH);
				Mcu_Sip_PwrOn_PM_PWR_EN_N_Step9_Time = MCU_SIP_PWRON_TIME_INVALID;          /* 経過していれば計測完了を設定 */
			}
		}
	
		else{
			Mcu_Sip_PwrOn_PM_PWR_EN_N_Step9_Time++;
		}
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_Resume_LOW_POWER_ON
  Description   : SIP電源制御 LOW-POWER-ON (VB33-SIPのDDコンモード切替)
                  (ソフトウェア処理：MCU →DDコン)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_Resume_LOW_POWER_ON( void )
{
	if(Mcu_Sip_Resume_LOW_POWER_ON_Time != MCU_SIP_RESUME_TIME_INVALID){
#if 0
		if(Mcu_Sip_Resume_LOW_POWER_ON_Time >= MCU_SIP_RESUME_T_LOW_POWER_ON){ /* tLOW-POWER-ON_HI経過したか */
#endif
			(void)Dio_WriteChannel(DIO_ID_PORT10_CH5, MCU_DIO_HIGH);
			Mcu_Sip_Resume_LOW_POWER_ON_Time = MCU_SIP_RESUME_TIME_INVALID;                 /* 経過していれば計測完了を設定 */
#if 0
		}
		else{
			Mcu_Sip_Resume_LOW_POWER_ON_Time++;
		}
#endif
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_Resume_VB33_SIP_FREQ
  Description   : SIP電源制御 VB33-SIP-FREQ (3.3V：SIP電源)
                  (ソフトウェア処理：MCU →DDコン)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_Resume_VB33_SIP_FREQ( void )
{
	if(Mcu_Sip_Resume_VB33_SIP_FREQ_Time != MCU_SIP_RESUME_TIME_INVALID){
		if(Mcu_Sip_Resume_VB33_SIP_FREQ_Time >= MCU_SIP_RESUME_T_VB33_SIP_FREQ){  /* tVB33-SIP-FREQ経過したか */
			vd_g_Pwm_SetPeriodAndDuty((U1)PWM_CH_01_DDC_SIP_FREQ, (U2)MCU_SIP_PWM_PERIOD_DEF, (U2)MCU_SIP_PWM_DUTYCYCLE_DEF);
			Mcu_Sip_Resume_VB33_SIP_FREQ_Time = MCU_SIP_RESUME_TIME_INVALID;         /* 経過していれば計測完了を設定 */
		}
	
		else{
			Mcu_Sip_Resume_VB33_SIP_FREQ_Time++;
		}
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_Resume_MM_SUSPEND_REQ_N
  Description   : STR制御 MM_SUSPEND_REQ_N (ソフトウェア処理：MCU →SOC 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_Resume_MM_SUSPEND_REQ_N( void )
{
	if(Mcu_Sip_Resume_MM_SUSPEND_REQ_N_Time != MCU_SIP_RESUME_TIME_INVALID){
		if(Mcu_Sip_Resume_MM_SUSPEND_REQ_N_Time >= MCU_SIP_RESUME_T_MM_SUSPEND_REQ_N){  /* tMM_SUSPEND_REQ_N経過したか */
			(void)Dio_WriteChannel(DIO_ID_PORT10_CH10, MCU_DIO_HIGH);
			Mcu_Sip_Resume_MM_SUSPEND_REQ_N_Time = MCU_SIP_RESUME_TIME_INVALID;           /* 経過していれば計測完了を設定 */
		}
	
		else{
			Mcu_Sip_Resume_MM_SUSPEND_REQ_N_Time++;
		}
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_Resume_STR_WAKE
  Description   : STR制御 STR_WAKE (ソフトウェア処理：MCU →SOC 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_Resume_STR_WAKE( void )
{
	if(Mcu_Sip_Resume_STR_WAKE_Time != MCU_SIP_RESUME_TIME_INVALID){
		if(Mcu_Sip_Resume_STR_WAKE_Time >= MCU_SIP_RESUME_T_STR_WAKE){  /* tSTR_WAKE経過したか */
			(void)Dio_WriteChannel(DIO_ID_PORT22_CH0, MCU_DIO_HIGH);
			Mcu_Sip_Resume_STR_WAKE_Time = MCU_SIP_RESUME_TIME_INVALID;           /* 経過していれば計測完了を設定 */
		}
	
		else{
			Mcu_Sip_Resume_STR_WAKE_Time++;
		}
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOff_MM_OFF_REQ_1
  Description   : SOC終了制御(電源OFF)
				  MM_OFF_REQ
				  (ソフトウェア処理：MCU →SOC)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOff_MM_OFF_REQ_1( void )
{
	if(Mcu_Sip_PwrOff_MM_OFF_REQ_Step1_Time != MCU_SIP_PWROFF_TIME_INVALID){
#if 0
		if(Mcu_Sip_PwrOff_MM_OFF_REQ_Step1_Time >= MCU_SIP_PWROFF_T_MM_OFF_REQ_HI){  /* tVB33-SIP-FREQ経過したか */
#endif
			(void)Dio_WriteChannel(DIO_ID_PORT17_CH2, MCU_DIO_HIGH);
			Mcu_Sip_PwrOff_MM_OFF_REQ_Step1_Time = MCU_SIP_PWROFF_TIME_INVALID;         /* 経過していれば計測完了を設定 */
#if 0
		}
	
		else{
			Mcu_Sip_PwrOff_MM_OFF_REQ_Step1_Time++;
		}
#endif
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOff_ValChk_MM_STBY_N
  Description   : ソフト状態監視(TEN独自系)
  				  MM_STBY_N(ソフトウェア処理：SOC →MCU)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOff_ValChk_MM_STBY_N( void )
{
	uint8 read_lv;
	
	if( Mcu_Sip_PwrOff_MM_STBY_N_Chk_Time != MCU_SIP_PWROFF_TIME_INVALID){
		read_lv = Dio_ReadChannel(DIO_ID_PORT10_CH11);

		if( read_lv == (uint8)MCU_DIO_LOW){
			Mcu_Sip_PwrOff_MM_STBY_N_Chk_Time = MCU_SIP_PWROFF_TIME_INVALID;
		}
#if (MCU_ERR_CHK == 1U)
		u1_s_Mcu_Err_dbg_state = MCU_ERR_SIPOFF_STEP2_1; /* TP */
#endif
	}

	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOff_ValChk_PMA_PS_HOLD
  Description   : 電源など状態監視(QC標準系)
                  PMA_PS_HOLD(ソフトウェア処理(QCソフト)：SOC →MCU)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOff_ValChk_PMA_PS_HOLD( void )
{
	uint8 read_lv;
	
	if( Mcu_Sip_PwrOff_PMA_PS_HOLD_Chk_Time != MCU_SIP_PWROFF_TIME_INVALID){
		read_lv = Dio_ReadChannel(DIO_ID_PORT3_CH1);

		if( read_lv == (uint8)MCU_DIO_LOW){
			Mcu_Sip_PwrOff_PMA_PS_HOLD_Chk_Time = MCU_SIP_PWROFF_TIME_INVALID;
		}
#if (MCU_ERR_CHK == 1U)
		u1_s_Mcu_Err_dbg_state = MCU_ERR_SIPOFF_STEP3_1; /* TP */
#endif
	}
	
	return;
}
/*****************************************************************************
  Function      : Mcu_Sip_PwrOff_ValChk_SOC_RESOUT_N
  Description   : 電源など状態監視(QC標準系)
                  SOC_RESOUT_N(ソフトウェア処理(QCソフト)：SOC →MCU)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOff_ValChk_SOC_RESOUT_N( void )
{
	uint8 read_lv;
	
	if( Mcu_Sip_PwrOff_SOC_RESOUT_N_Chk_Time != MCU_SIP_PWROFF_TIME_INVALID){
		read_lv = Dio_ReadChannel(DIO_ID_PORT8_CH3);

		if( read_lv == (uint8)MCU_DIO_LOW){
			Mcu_Sip_PwrOff_SOC_RESOUT_N_Chk_Time = MCU_SIP_PWROFF_TIME_INVALID;
		}
#if (MCU_ERR_CHK == 1U)
		u1_s_Mcu_Err_dbg_state = MCU_ERR_SIPOFF_STEP4_1; /* TP */
#endif
	}
	
	return;
}
/*****************************************************************************
  Function      : Mcu_Sip_PwrOff_ValChk_SAIL_RESOUT_N
  Description   : SAIL状態監視
                  SAIL_RESOUT_N(ソフトウェア処理(QCソフト)：SOC →MCU)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOff_ValChk_SAIL_RESOUT_N( void )
{
	uint8 read_lv;
	
	if( Mcu_Sip_PwrOff_SAIL_RESOUT_N_Chk_Time != MCU_SIP_PWROFF_TIME_INVALID){
		read_lv = Dio_ReadChannel(DIO_ID_PORT8_CH8);

		if( read_lv == (uint8)MCU_DIO_LOW){
			Mcu_Sip_PwrOff_SAIL_RESOUT_N_Chk_Time = MCU_SIP_PWROFF_TIME_INVALID;
		}
#if (MCU_ERR_CHK == 1U)
		u1_s_Mcu_Err_dbg_state = MCU_ERR_SIPOFF_STEP4_2; /* TP */
#endif
	}

	return;
}
/*****************************************************************************
  Function      : Mcu_Sip_PwrOff_ValChk_POFF_COMPLETE_N
  Description   : 電源など状態監視(QC標準系)
				  POFF_COMPLETE_N(ソフトウェア処理(QCソフト)：SOC PMIC →MCU)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOff_ValChk_POFF_COMPLETE_N( void )
{
	uint8 read_lv;
	
	if( Mcu_Sip_PwrOff_POFF_COMPLETE_N_Chk_Time != MCU_SIP_PWROFF_TIME_INVALID){
		read_lv = Dio_ReadChannel(DIO_ID_PORT8_CH6);

		if( read_lv == (uint8)MCU_DIO_LOW){
			Mcu_Sip_PwrOff_POFF_COMPLETE_N_Chk_Time = MCU_SIP_PWROFF_TIME_INVALID;
		}
#if (MCU_ERR_CHK == 1U)
		u1_s_Mcu_Err_dbg_state = MCU_ERR_SIPOFF_STEP4_3; /* TP */
#endif
	}

	return;
}
/*****************************************************************************
  Function      : Mcu_Sip_PwrOff_VB33_SIP_FREQ
  Description   : SIP電源制御
				  VB33-SIP-FREQ(3.3V：SIP電源)(ソフトウェア処理：MCU →DDコン)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOff_VB33_SIP_FREQ( void )
{
	if(Mcu_Sip_PwrOff_VB33_SIP_FREQ_Time != MCU_SIP_PWROFF_TIME_INVALID){
		if(Mcu_Sip_PwrOff_VB33_SIP_FREQ_Time >= MCU_SIP_PWROFF_T_VB33_SIP_FREQ){  /* tVB33-SIP-FREQ経過したか */
			vd_g_Pwm_SetPeriodAndDuty((U1)PWM_CH_01_DDC_SIP_FREQ, (U2)MCU_SIP_PWM_PERIOD_OFF, (U2)MCU_SIP_PWM_DUTYCYCLE_OFF);
			Mcu_Sip_PwrOff_VB33_SIP_FREQ_Time = MCU_SIP_PWROFF_TIME_INVALID;         /* 経過していれば計測完了を設定 */
		}
	
		else{
			Mcu_Sip_PwrOff_VB33_SIP_FREQ_Time++;
		}
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOff_VB33_SIP_ON
  Description   : SIP電源制御
				  VB33-SIP-ON
				  (3.3V：SIP電源)
				  (ソフトウェア処理：MCU →DDコン)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOff_VB33_SIP_ON( void )
{
	if(Mcu_Sip_PwrOff_VB33_SIP_ON_Time != MCU_SIP_PWROFF_TIME_INVALID){
		if(Mcu_Sip_PwrOff_VB33_SIP_ON_Time >= MCU_SIP_PWROFF_T_VB33_SIP_ON){  /* tVB33-SIP-ON経過したか */
			(void)Dio_WriteChannel(DIO_ID_APORT5_CH1, MCU_DIO_LOW);
			Mcu_Sip_PwrOff_VB33_SIP_ON_Time = MCU_SIP_PWROFF_TIME_INVALID;         /* 経過していれば計測完了を設定 */
		}
	
		else{
			Mcu_Sip_PwrOff_VB33_SIP_ON_Time++;
		}
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOff_LOW_POWER_ON
  Description   : SIP電源制御
				  LOW-POWER-ON
				  (VB33-SIPのDDコンモード切替)
				  (ソフトウェア処理：MCU →DDコン)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOff_LOW_POWER_ON( void )
{
	if(Mcu_Sip_PwrOff_LOW_POWER_ON_Time != MCU_SIP_PWROFF_TIME_INVALID){
		if(Mcu_Sip_PwrOff_LOW_POWER_ON_Time >= MCU_SIP_PWROFF_T_LOW_POWER_ON){  /* tLOW-POWER-ON経過したか */
			(void)Dio_WriteChannel(DIO_ID_PORT10_CH5, MCU_DIO_LOW);
			Mcu_Sip_PwrOff_LOW_POWER_ON_Time = MCU_SIP_PWROFF_TIME_INVALID;         /* 経過していれば計測完了を設定 */
		}
	
		else{
			Mcu_Sip_PwrOff_LOW_POWER_ON_Time++;
		}
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOff_PM_PWR_EN_N
  Description   : PMIC制御(電源ON/OFF)
				  PM_PWR_EN
				  (ソフトウェア処理：MCU →SOC PMIC)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOff_PM_PWR_EN_N( void )
{
	if(Mcu_Sip_PwrOff_PM_PWR_EN_N_Time != MCU_SIP_PWROFF_TIME_INVALID){
		if(Mcu_Sip_PwrOff_PM_PWR_EN_N_Time >= MCU_SIP_PWROFF_T_PM_PWR_EN_N){  /* tPM-PWR-EN-N経過したか */
			(void)Dio_WriteChannel(DIO_ID_PORT8_CH2, MCU_DIO_LOW);
			Mcu_Sip_PwrOff_PM_PWR_EN_N_Time = MCU_SIP_PWROFF_TIME_INVALID;         /* 経過していれば計測完了を設定 */
		}
	
		else{
			Mcu_Sip_PwrOff_PM_PWR_EN_N_Time++;
		}
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOff_PMIC_FAST_POFF_EN_N
  Description   : PMIC制御(電源ON/OFF)
				  PMIC_FAST_POFF_EN_N
				  (ソフトウェア処理：MCU →SOC PMIC)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOff_PMIC_FAST_POFF_EN_N( void )
{
	if(Mcu_Sip_PwrOff_PMIC_FAST_POFF_EN_N_Time != MCU_SIP_PWROFF_TIME_INVALID){
		if(Mcu_Sip_PwrOff_PMIC_FAST_POFF_EN_N_Time >= MCU_SIP_PWROFF_T_PMIC_FAST_POFF_EN_N){  /* tPMIC-FAST-POFF-EN-N経過したか */
			(void)Dio_WriteChannel(DIO_ID_PORT8_CH0, MCU_DIO_LOW);
			Mcu_Sip_PwrOff_PMIC_FAST_POFF_EN_N_Time = MCU_SIP_PWROFF_TIME_INVALID;         /* 経過していれば計測完了を設定 */
		}
	
		else{
			Mcu_Sip_PwrOff_PMIC_FAST_POFF_EN_N_Time++;
		}
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOff_MM_SUSPEND_REQ_N
  Description   : STR制御
				  MM_SUSPEND_REQ_N
				  (ソフトウェア処理：MCU →SOC)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOff_MM_SUSPEND_REQ_N( void )
{
	if(Mcu_Sip_PwrOff_MM_SUSPEND_REQ_N_Time != MCU_SIP_PWROFF_TIME_INVALID){
		if(Mcu_Sip_PwrOff_MM_SUSPEND_REQ_N_Time >= MCU_SIP_PWROFF_T_MM_SUSPEND_REQ_N){  /* tMM-SUSPENDED-REQ-N経過したか */
			(void)Dio_WriteChannel(DIO_ID_PORT10_CH10, MCU_DIO_LOW);
			Mcu_Sip_PwrOff_MM_SUSPEND_REQ_N_Time = MCU_SIP_PWROFF_TIME_INVALID;         /* 経過していれば計測完了を設定 */
		}
	
		else{
			Mcu_Sip_PwrOff_MM_SUSPEND_REQ_N_Time++;
		}
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOff_STR_WAKE
  Description   : STR制御
				  STR_WAKE
				  (ソフトウェア処理：MCU →SOC)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOff_STR_WAKE( void )
{
	if(Mcu_Sip_PwrOff_STR_WAKE_Time != MCU_SIP_PWROFF_TIME_INVALID){
		if(Mcu_Sip_PwrOff_STR_WAKE_Time >= MCU_SIP_PWROFF_T_STR_WAKE){  /* tWAIT-STR-WAKE経過したか */
			(void)Dio_WriteChannel(DIO_ID_PORT22_CH0, MCU_DIO_LOW);
			Mcu_Sip_PwrOff_STR_WAKE_Time = MCU_SIP_PWROFF_TIME_INVALID;         /* 経過していれば計測完了を設定 */
		}
	
		else{
			Mcu_Sip_PwrOff_STR_WAKE_Time++;
		}
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOff_MM_OFF_REQ_2
  Description   : SOC終了制御(電源OFF)
				  MM_OFF_REQ
				  (ソフトウェア処理：MCU →SOC)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_PwrOff_MM_OFF_REQ_2( void )
{
	if(Mcu_Sip_PwrOff_MM_OFF_REQ_Step6_Time != MCU_SIP_PWROFF_TIME_INVALID){
		if(Mcu_Sip_PwrOff_MM_OFF_REQ_Step6_Time >= MCU_SIP_PWROFF_T_MM_OFF_REQ_LO){  /* tMM-OFF-REQ-LO経過したか */
			(void)Dio_WriteChannel(DIO_ID_PORT17_CH2, MCU_DIO_LOW);
			Mcu_Sip_PwrOff_MM_OFF_REQ_Step6_Time = MCU_SIP_PWROFF_TIME_INVALID;         /* 経過していれば計測完了を設定 */
		}
	
		else{
			Mcu_Sip_PwrOff_MM_OFF_REQ_Step6_Time++;
		}
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_Standby_MM_SUSPEND_REQ_N
  Description   : STR制御 MM_SUSPEND_REQ_N (ソフトウェア処理：MCU →SOC 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_Standby_MM_SUSPEND_REQ_N( void )
{
	if(Mcu_Sip_Standby_MM_SUSPEND_REQ_N_Time != MCU_SIP_STANDBY_TIME_INVALID){
#if 0
		if(Mcu_Sip_Standby_MM_SUSPEND_REQ_N_Time >= MCU_SIP_STANDBY_T_MM_SUSPEND_REQ_N){  /* tMM_SUSPEND_REQ_N経過したか */
#endif
			(void)Dio_WriteChannel(DIO_ID_PORT10_CH10, MCU_DIO_LOW);
			Mcu_Sip_Standby_MM_SUSPEND_REQ_N_Time = MCU_SIP_STANDBY_TIME_INVALID;           /* 経過していれば計測完了を設定 */
#if 0
		}
	
		else{
			Mcu_Sip_Standby_MM_SUSPEND_REQ_N_Time++;
		}
#endif	
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_Standby_STR_WAKE
  Description   : STR制御 STR_WAKE (ソフトウェア処理：MCU →SOC 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_Standby_STR_WAKE( void )
{
	if(Mcu_Sip_Standby_STR_WAKE_Time != MCU_SIP_STANDBY_TIME_INVALID){
#if 0
		if(Mcu_Sip_Standby_STR_WAKE_Time >= MCU_SIP_STANDBY_T_STR_WAKE){  /* tSTR_WAKE経過したか */
#endif
			(void)Dio_WriteChannel(DIO_ID_PORT22_CH0, MCU_DIO_LOW);
			Mcu_Sip_Standby_STR_WAKE_Time = MCU_SIP_STANDBY_TIME_INVALID;           /* 経過していれば計測完了を設定 */
#if 0
		}
	
		else{
			Mcu_Sip_Standby_STR_WAKE_Time++;
		}
#endif	
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_Standby_ValChk_MM_STBY_N
  Description   : ソフト状態監視(TEN独自系)
  				  MM_STBY_N(ソフトウェア処理：SOC →MCU)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_Standby_ValChk_MM_STBY_N( void )
{
	uint8 read_lv;
    
	if(Mcu_Sip_Standby_MM_STBY_N_Chk_Time != MCU_SIP_STANDBY_TIME_INVALID){
		read_lv = Dio_ReadChannel(DIO_ID_PORT10_CH11);

		if( read_lv == (uint8)MCU_DIO_LOW){
			Mcu_Sip_Standby_MM_STBY_N_Chk_Time = MCU_SIP_STANDBY_TIME_INVALID;
		}
#if (MCU_ERR_CHK == 1U)
		u1_s_Mcu_Err_dbg_state = MCU_ERR_STANDBY_MMSTBY; /* TP */
#endif
	}

	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_Standby_ValChk_AOSS_SLEEP_ENTRY_EXIT
  Description   : 電源など状態監視(QC標準系) AOSS_SLEEP_ENTRY_EXIT
                  (ソフトウェア処理(QCソフト)：SOC PMIC →MCU)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_Standby_ValChk_AOSS_SLEEP_ENTRY_EXIT( void )
{
	uint8 read_lv;
    
	if(Mcu_Sip_Standby_AOSS_SLEEP_ENTRY_EXIT_Chk_Time != MCU_SIP_STANDBY_TIME_INVALID){
		read_lv = Dio_ReadChannel(DIO_ID_PORT17_CH0);

		if( read_lv == (uint8)MCU_DIO_HIGH){
			Mcu_Sip_Standby_AOSS_SLEEP_ENTRY_EXIT_Chk_Time = MCU_SIP_STANDBY_TIME_INVALID;
		}
#if (MCU_ERR_CHK == 1U)
		u1_s_Mcu_Err_dbg_state = MCU_ERR_STANDBY_AOSS; /* TP */
#endif
	}

	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_Standby_VB33_SIP_FREQ
  Description   : SIP電源制御 VB33-SIP-FREQ (3.3V：SIP電源)
                  (ソフトウェア処理：MCU →DDコン)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_Standby_VB33_SIP_FREQ( void )
{
	if(Mcu_Sip_Standby_VB33_SIP_FREQ_Time != MCU_SIP_STANDBY_TIME_INVALID){
#if 0
		if(Mcu_Sip_Standby_VB33_SIP_FREQ_Time >= MCU_SIP_STANDBY_T_VB33_SIP_FREQ){  /* tVB33-SIP-FREQ経過したか */
#endif
			vd_g_Pwm_SetPeriodAndDuty((U1)PWM_CH_01_DDC_SIP_FREQ, (U2)MCU_SIP_PWM_PERIOD_OFF, (U2)MCU_SIP_PWM_DUTYCYCLE_OFF);
			Mcu_Sip_Standby_VB33_SIP_FREQ_Time = MCU_SIP_STANDBY_TIME_INVALID;    /* 経過していれば計測完了を設定 */
		}
#if 0
		else{
			Mcu_Sip_Standby_VB33_SIP_FREQ_Time++;
		}
	}
#endif
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_Standby_LOW_POWER_ON
  Description   : SIP電源制御 LOW-POWER-ON (VB33-SIPのDDコンモード切替)
                  (ソフトウェア処理：MCU →DDコン)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void Mcu_Sip_Standby_LOW_POWER_ON( void )
{
	if(Mcu_Sip_Standby_LOW_POWER_ON_Time != MCU_SIP_STANDBY_TIME_INVALID){
		if(Mcu_Sip_Standby_LOW_POWER_ON_Time >= MCU_SIP_STANDBY_T_LOW_POWER_ON){  /* tLOW-POWER-ON経過したか */
			(void)Dio_WriteChannel(DIO_ID_PORT10_CH5, MCU_DIO_LOW);
			Mcu_Sip_Standby_LOW_POWER_ON_Time = MCU_SIP_STANDBY_TIME_INVALID;
		}

		else{
			Mcu_Sip_Standby_LOW_POWER_ON_Time++;
		}
	}
	
	return;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOn_GetSts
  Description   : SIP電源ON ステータス通知関数
  param[in/out] : none
  return        : MCU_SIP_PWR_NOTCOMP：実行中
                  MCU_SIP_PWR_COMP   ：実行完了
  Note          : none
*****************************************************************************/
uint8 Mcu_Sip_PwrOn_GetSts( void )
{
	uint8 u1_t_ret;
	
	if(Mcu_Sip_PwrOn_Step != (uint8)MCU_SIP_PWRON_STEP_CMPLT){
		u1_t_ret = (uint8)MCU_SIP_PWR_NOTCOMP;
	}
	else{
		u1_t_ret = (uint8)MCU_SIP_PWR_COMP;
	}
	
	return u1_t_ret;
}

/*****************************************************************************
  Function      : Mcu_Sip_Resume_GetSts
  Description   : SIP電源RESUME ステータス通知関数
  param[in/out] : none
  return        : MCU_SIP_PWR_NOTCOMP：実行中
                  MCU_SIP_PWR_COMP   ：実行完了
  Note          : none
*****************************************************************************/
uint8 Mcu_Sip_Resume_GetSts( void )
{
	uint8 u1_t_ret;
	
	if(Mcu_Sip_Resume_Step != (uint8)MCU_SIP_RESUME_STEP_CMPLT){
		u1_t_ret = (uint8)MCU_SIP_PWR_NOTCOMP;
	}
	else{
		u1_t_ret = (uint8)MCU_SIP_PWR_COMP;
	}
	
	return u1_t_ret;
}

/*****************************************************************************
  Function      : Mcu_Sip_PwrOff_GetSts
  Description   : SIP電源OFF ステータス通知関数
  param[in/out] : none
  return        : MCU_SIP_PWR_NOTCOMP：実行中
                  MCU_SIP_PWR_COMP   ：実行完了
  Note          : none
*****************************************************************************/
uint8 Mcu_Sip_PwrOff_GetSts( void )
{
	uint8 u1_t_ret;

	if(Mcu_Sip_PwrOff_Step != (uint8)MCU_SIP_PWROFF_STEP_CMPLT){
		u1_t_ret = (uint8)MCU_SIP_PWR_NOTCOMP;
	}
	else{
		u1_t_ret = (uint8)MCU_SIP_PWR_COMP;
	}
	
	return u1_t_ret;
}

/*****************************************************************************
  Function      : Mcu_Sip_Standby_GetSts
  Description   : SIP電源スタンバイ移行 ステータス通知関数
  param[in/out] : none
  return        : MCU_SIP_PWR_NOTCOMP：実行中
                  MCU_SIP_PWR_COMP   ：実行完了
  Note          : none
*****************************************************************************/
uint8 Mcu_Sip_Standby_GetSts( void )
{
	uint8 u1_t_ret;
	
	if(Mcu_Sip_Standby_Step != (uint8)MCU_SIP_STANDBY_STEP_CMPLT){
		u1_t_ret = (uint8)MCU_SIP_PWR_NOTCOMP;
	}
	else{
		u1_t_ret = (uint8)MCU_SIP_PWR_COMP;
	}
	
	return u1_t_ret;
}

/*#define ***_STOP_SEC_CODE
#include <***_MemMap.h>*/

/**** End of File ***********************************************************/
