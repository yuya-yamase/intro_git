/* PwrCtrl_Observe_c_v1-0-0                                                     */
/****************************************************************************/
/* Copyright (C) 2023 Denso Co.,Ltd. All rights reserved.                   */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | PwrCtrl_Observe/CODE                                      */
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

#define PWRCTRL_OBSERVE_SLEEP_TIME        (60000U / PWRCTRL_CFG_TASK_TIME) /* 60sec/5ms周期 */
#define PWRCTRL_OBSERVE_SLEEP_CLR         (0U)     /* 時間クリア値 */
#define PWRCTRL_OBSERVE_STBY_OK           (PWRCTRL_COM_STBY_OK)
#define PWRCTRL_OBSERVE_STBY_NG           (PWRCTRL_COM_STBY_NG)
#define PWRCTRL_OBSERVE_FSLP_ON           (PWRCTRL_COM_FSLP_ON)
#define PWRCTRL_OBSERVE_FSLP_OFF          (PWRCTRL_COM_FSLP_OFF)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static U1 u1_s_PwrCtrlObserveJdgVm3Stby( void );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
static U1 u1_s_PwrCtrl_Observe_TriggerInfo;   /* 起動検知/OFF検知判定結果 */
static U1 u1_s_PwrCtrl_Observe_Vm3StbyInfo;   /* VM3スタンバイ条件成立有無 */
static U4 u4_s_PwrCtrl_Observe_SleepTime;     /* スリープ条件継続時間 */

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Functions                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Scheduled Functions                                                      */
/****************************************************************************/
/*****************************************************************************
  Function      : vd_g_PwrCtrlObserveInit
  Description   : 状態監視全体の初期化処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlObserveInit( void )
{
    u1_s_PwrCtrl_Observe_TriggerInfo = (U1)PWRCTRL_OBSERVE_POWER_ON;
    u1_s_PwrCtrl_Observe_Vm3StbyInfo = (U1)PWRCTRL_MAIN_PROHIBITSLEEP_OFF;
    u4_s_PwrCtrl_Observe_SleepTime = (U4)PWRCTRL_OBSERVE_SLEEP_CLR;

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlObserveOnOffTriggerDetect
  Description   : 起動検知/スタンバイ要求検知監視処理
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlObserveOnOffTriggerDetect( void )
{
    U1 u1_t_stby_rslt;  /* 全VMのスタンバイ可否 */
    U1 u1_t_force_slp;  /* 強制スリープ条件成立有無 */
    U1 u1_t_boot;       /* Boot信号 */

    /* 全VMのスタンバイ可否 */
    u1_t_stby_rslt = u1_g_PwrCtrlComRxGetVm1Stby();
    u1_t_stby_rslt &= u1_g_PwrCtrlComRxGetVm2Stby();
    u1_t_stby_rslt &= u1_s_PwrCtrlObserveJdgVm3Stby();

    /* 強制スリープ条件成立有無 */
    u1_t_force_slp = u1_g_PwrCtrlComRxGetForceSleep();

    /* Boot信号 */
    u1_t_boot = u1_g_PwrCtrl_PinMonitor_GetPinInfo(PWRCTRL_CFG_PRIVATE_KIND_BOOT);

    /* スタンバイ条件成立 */
    if( ((u1_t_stby_rslt == (U1)PWRCTRL_COM_STBY_OK)         /* 全VMスタンバイ可 */
     ||  (u1_t_force_slp == (U1)PWRCTRL_COM_FSLP_ON))        /* または、強制スリープ条件成立 */
     &&  (u1_t_boot == (U1)STD_LOW))                         /* 上記かつ、Boot = Low */
    {
        u1_s_PwrCtrl_Observe_TriggerInfo = (U1)PWRCTRL_OBSERVE_POWER_OFF;  /* スタンバイ要求検知 */
    }
    /* スタンバイ条件非成立 */
    else{
        u1_s_PwrCtrl_Observe_TriggerInfo = (U1)PWRCTRL_OBSERVE_POWER_ON;   /* 起動検知 */
    }

    return;
}

/*****************************************************************************
  Function      : u1_g_PwrCtrlObserveOnOffTrigger
  Description   : 起動検知(起動トリガ)/OFF検知(サスペンド処理トリガ)結果取得
  return        : [Out] VM3のスタンバイ条件成立有無
  Note          : none
*****************************************************************************/
U1 u1_g_PwrCtrlObserveOnOffTrigger( void )
{
    return(u1_s_PwrCtrl_Observe_TriggerInfo);
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlObserveVm3StbyInfo
  Description   : VM3スタンバイ条件通知処理
  param[in/out] : [in] u1_a_ProhibitSleep スリープ禁止/許可
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlObserveVm3StbyInfo( const U1 u1_a_ProhibitSleep )
{
    u1_s_PwrCtrl_Observe_Vm3StbyInfo = u1_a_ProhibitSleep;

    return;
}

/*****************************************************************************
  Function      : u1_s_PwrCtrlObserveRxVm3Stby
  Description   : VM3スタンバイ条件成立判定処理(60秒間継続判定)
  param[in/out] : none
  return        : [Out] VM3のスタンバイ条件成立有無
  Note          : none
*****************************************************************************/
static U1 u1_s_PwrCtrlObserveJdgVm3Stby( void )
{
    U1 u1_t_stbyinfo;

    u1_t_stbyinfo = (U1)PWRCTRL_COM_STBY_NG;

    /* スリープ許可 */
    if(u1_s_PwrCtrl_Observe_Vm3StbyInfo == (U1)PWRCTRL_MAIN_PROHIBITSLEEP_OFF)
    {
        /* 60秒継続判定 */
        if( u4_s_PwrCtrl_Observe_SleepTime < (U4)PWRCTRL_OBSERVE_SLEEP_TIME ){
            u4_s_PwrCtrl_Observe_SleepTime++;
        }
        else{
            /* スタンバイ可 */
            u1_t_stbyinfo = (U1)PWRCTRL_COM_STBY_OK;
        }
    }
    /* スリープ禁止 */
    else{
        /* 60秒継続クリア */
        u4_s_PwrCtrl_Observe_SleepTime = (U4)PWRCTRL_OBSERVE_SLEEP_CLR;
    }

    return(u1_t_stbyinfo);
}

/****************************************************************************/
/* Service API                                                              */
/****************************************************************************/
/**** End of File ***********************************************************/
