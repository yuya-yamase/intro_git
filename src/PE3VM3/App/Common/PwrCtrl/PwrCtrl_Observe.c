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
/* 起動検知/スタンバイ要求検知 */
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
/* 起動検知/スタンバイ要求検知 */
static U1 u1_s_PwrCtrlObserveJdgVm3Stby( void );
static void vd_s_PwrCtrlObserveOnOffTriggerDetect( void );
/* 異常監視 */
static U2 u2_g_PwrCtrlObserveSailUartSeq( void );
static U2 u2_g_PwrCtrlObserveSailErrSeq( void );
static U2 u2_s_PwrCtrlObservePsailSeq( void );
static U2 u2_g_PwrCtrlObserveSpiFailSeq( void );
static U2 u2_s_PwrCtrlObservePsHoldSeq( void );
static U2 u2_s_PwrCtrlObservePgdAsilVbSeq( void );
static U2 u2_s_PwrCtrlObservePgdAsilVsysSeq( void );
static U2 u2_s_PwrCtrlObservePgdAsilVsysV11Seq( void );
static U2 u2_s_PwrCtrlObservePgdDiodeSeq( void );
static U2 u2_s_PwrCtrlObservePgdVbSeq( void );
static U2 u2_s_PwrCtrlObservePgdVsysSeq( void );
/* リセット要求検知 */
static U2 u2_s_PwrCtrlObserveSoCResetReqSeq( void );
static U2 u2_s_PwrCtrlObserveNMDiagResetSeq( void );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/* 起動検知/スタンバイ要求検知 */
static U1 u1_s_PwrCtrl_Observe_TriggerInfo;   /* 起動検知/OFF検知判定結果 */
static U1 u1_s_PwrCtrl_Observe_Vm3StbyInfo;   /* VM3スリープ許可情報 */
static U4 u4_s_PwrCtrl_Observe_SleepTime;     /* スリープ条件継続時間 */
/* 異常監視 */
static U1 u1_s_PwrCtrl_Observe_Psail_Sts;           /* PM_PSAIL_ERR_N監視状態 */
static U1 u1_s_PwrCtrl_Observe_PsHold_Sts;          /* PMA_PS_HOLD監視状態 */
static U1 u1_s_PwrCtrl_Observe_PgdAsilVbLowPwr_Sts; /* PGOOD_ASIL_VB監視(LOW-POWER-ON)状態 */
static U1 u1_s_PwrCtrl_Observe_PgdAsilVbSysPwr_Sts; /* PGOOD_ASIL_VB監視(SYS電源制御)状態 */
static U1 u1_s_PwrCtrl_Observe_PgdAsilVsys_Sts;     /* PGOOD_ASIL_VSYS監視状態 */
static U1 u1_s_PwrCtrl_Observe_PgdAsilVsysV11_Sts;  /* PGOOD_ASIL_VSYS(V11)監視状態 */
static U1 u1_s_PwrCtrl_Observe_PgdDiode_Sts;        /* PGOOD_DIODE監視状態 */
static U1 u1_s_PwrCtrl_Observe_PgdVb_Sts;           /* PGOOD_VB監視状態 */
static U1 u1_s_PwrCtrl_Observe_PgdVsys_Sts;         /* PGOOD_VSYS監視状態 */
static U1 u1_s_PwrCtrl_Observe_SocPower_Sts;        /* SoC起動状態 */
static U2 u2_s_PwrCtrl_Observe_Err_Sts;             /* 監視異常発生内容 */
/* リセット要求検知 */
static U1 u1_s_PwrCtrl_Observe_SoCResetErr_Sts;     /* SoCリセット要求(異常)監視状態 */
static U1 u1_s_PwrCtrl_Observe_PreSoCResetReq;      /* SoCリセット要求前回値 */
static U1 u1_s_PwrCtrl_Observe_PreNMDiagReset;      /* NMダイアグリセット前回値 */
static U2 u2_s_PwrCtrl_Observe_Reset_Sts;           /* リセット要求内容 */

#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
U2 u2_g_PwrCtrl_Observe_Err_Sts_debug;              /* 監視異常発生内容(デバッグ用) */
#endif
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
    /* 起動検知/スタンバイ要求検知 */
    u1_s_PwrCtrl_Observe_TriggerInfo = (U1)PWRCTRL_OBSERVE_POWER_ON;
    u1_s_PwrCtrl_Observe_Vm3StbyInfo = (U1)PWRCTRL_MAIN_PROHIBITSLEEP_OFF;
    u4_s_PwrCtrl_Observe_SleepTime = (U4)PWRCTRL_OBSERVE_SLEEP_CLR;
    /* 異常監視 */
    vd_g_PwrCtrl_ObserveSAIL_Init();
    u2_s_PwrCtrl_Observe_Err_Sts = (U2)PWRCTRL_OBSERVE_ERR_NON;
    u1_s_PwrCtrl_Observe_Psail_Sts = (U1)PWRCTRL_OBSERVE_OFF;
    u1_s_PwrCtrl_Observe_PsHold_Sts = (U1)PWRCTRL_OBSERVE_OFF;
    u1_s_PwrCtrl_Observe_PgdAsilVbLowPwr_Sts = (U1)PWRCTRL_OBSERVE_OFF;
    u1_s_PwrCtrl_Observe_PgdAsilVbSysPwr_Sts = (U1)PWRCTRL_OBSERVE_OFF;
    u1_s_PwrCtrl_Observe_PgdAsilVsys_Sts = (U1)PWRCTRL_OBSERVE_OFF;
    u1_s_PwrCtrl_Observe_PgdAsilVsysV11_Sts = (U1)PWRCTRL_OBSERVE_OFF;
    u1_s_PwrCtrl_Observe_PgdDiode_Sts = (U1)PWRCTRL_OBSERVE_OFF;
    u1_s_PwrCtrl_Observe_PgdVb_Sts = (U1)PWRCTRL_OBSERVE_OFF;
    u1_s_PwrCtrl_Observe_PgdVsys_Sts = (U1)PWRCTRL_OBSERVE_OFF;
    u1_s_PwrCtrl_Observe_SocPower_Sts = (U1)PWRCTRL_OBSERVE_SOCPOWER_OFF;
#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
    u2_g_PwrCtrl_Observe_Err_Sts_debug = (U2)PWRCTRL_OBSERVE_ERR_NON;
#endif
    /* リセット要求検知 */
    u2_s_PwrCtrl_Observe_Reset_Sts = (U2)PWRCTRL_OBSERVE_RESET_NON;
    u1_s_PwrCtrl_Observe_SoCResetErr_Sts = (U1)PWRCTRL_OBSERVE_OFF;
    u1_s_PwrCtrl_Observe_PreSoCResetReq = (U1)PWRCTRL_COM_SOCRESET_NON;
    u1_s_PwrCtrl_Observe_PreNMDiagReset = (U1)PWRCTRL_COM_NMDIAGRESET_NON;
    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlObserveMainFunc
  Description   : 監視定期処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlObserveMainFunc( void )
{
    U2 u2_t_obserr;
    U2 u2_t_resetreq;

    u2_t_obserr = (U2)PWRCTRL_OBSERVE_ERR_NON;
    u2_t_resetreq = (U2)PWRCTRL_OBSERVE_RESET_NON;

    /* 起動検知/スタンバイ要求検知 */
    vd_s_PwrCtrlObserveOnOffTriggerDetect();                /* 起動検知/スタンバイ要求検知処理 */

    /* SAIL UART Message監視/SAIL-ERR監視定期処理 */
    vd_g_PwrCtrl_ObserveSAIL_Main();

    /* 異常監視 */
#ifdef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF
    if(u1_g_PwrCtrl_Main_DbgFailOffFlag == (U1)MCU_DIO_HIGH)
    {
#endif
        u2_t_obserr |= u2_g_PwrCtrlObserveSailUartSeq();    /* SAIL UART Message監視 */
        u2_t_obserr |= u2_g_PwrCtrlObserveSailErrSeq();     /* SAIL-ERR監視 */
        /* u2_t_obserr |= u2_s_PwrCtrlObservePsailSeq(); */ /* PM_PSAIL_ERR_N監視 */
        u2_t_obserr |= u2_s_PwrCtrlObservePsHoldSeq();      /* PMA_PS_HOLD監視 */
        u2_t_obserr |= u2_g_PwrCtrlObserveSpiFailSeq();     /* SPI通信途絶監視 */
#ifdef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF
    }
#endif
    u2_t_obserr |= u2_s_PwrCtrlObservePgdAsilVbSeq();       /* PGOOD_ASIL_VB監視 */
    u2_t_obserr |= u2_s_PwrCtrlObservePgdAsilVsysSeq();     /* PGOOD_ASIL_VSYS監視 */
    u2_t_obserr |= u2_s_PwrCtrlObservePgdAsilVsysV11Seq();  /* PGOOD_ASIL_VSYS(V11)監視 */
    u2_t_obserr |= u2_s_PwrCtrlObservePgdDiodeSeq();        /* PGOOD_DIODE監視 */
    u2_t_obserr |= u2_s_PwrCtrlObservePgdVbSeq();           /* PGOOD_VB監視 */
    u2_t_obserr |= u2_s_PwrCtrlObservePgdVsysSeq();         /* PGOOD_VSYS監視 */

    /* リセット要求検知 */
    u2_t_resetreq |= u2_s_PwrCtrlObserveSoCResetReqSeq();   /* SoCリセット要求監視 */
    u2_t_resetreq |= u2_s_PwrCtrlObserveNMDiagResetSeq();   /* NMダイアグリセット監視 */

    u2_s_PwrCtrl_Observe_Err_Sts = u2_t_obserr;             /* 監視異常発生内容を更新 */
#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
    u2_g_PwrCtrl_Observe_Err_Sts_debug |= u2_t_obserr;      /* 監視異常発生内容(デバッグ用)を更新(起動中保持) */
#endif
    u2_s_PwrCtrl_Observe_Reset_Sts = u2_t_resetreq;         /* リセット要求内容を更新 */
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlObserveOnOffTriggerDetect
  Description   : 起動検知/スタンバイ要求検知監視処理
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlObserveOnOffTriggerDetect( void )
{
    U1 u1_t_stby_rslt;  /* 全VMのスタンバイ可否 */
    U1 u1_t_stby_vm1;   /* VM1のスタンバイ可否 */
    U1 u1_t_stby_vm2;   /* VM2のスタンバイ可否 */
    U1 u1_t_stby_vm3;   /* VM3のスタンバイ可否 */
    U1 u1_t_force_slp;  /* 強制スリープ条件成立有無 */
    U1 u1_t_boot;       /* Boot信号 */

    u1_t_stby_rslt = (U1)PWRCTRL_OBSERVE_STBY_NG;

    /* 全VMのスタンバイ可否 */
    u1_t_stby_vm1 = u1_g_PwrCtrlComRxGetVm1Stby();
    u1_t_stby_vm2 = u1_g_PwrCtrlComRxGetVm2Stby();
    u1_t_stby_vm3 = u1_s_PwrCtrlObserveJdgVm3Stby();

    /* 全VMのスタンバイ可否判定 */
    if((u1_t_stby_vm1 == (U1)PWRCTRL_OBSERVE_STBY_OK)
    && (u1_t_stby_vm2 == (U1)PWRCTRL_OBSERVE_STBY_OK)
    && (u1_t_stby_vm3 == (U1)PWRCTRL_OBSERVE_STBY_OK))
    {
        /* 60秒未経過 */
        if( u4_s_PwrCtrl_Observe_SleepTime < (U4)PWRCTRL_OBSERVE_SLEEP_TIME ){
            u4_s_PwrCtrl_Observe_SleepTime++;
        }
        else
        {
            /* 全VMスタンバイ可 */
            u1_t_stby_rslt = (U1)PWRCTRL_OBSERVE_STBY_OK;
        }
    }
    else{
        /* 60秒継続クリア */
        u4_s_PwrCtrl_Observe_SleepTime = (U4)PWRCTRL_OBSERVE_SLEEP_CLR;
    }

    /* 強制スリープ条件成立有無 */
    u1_t_force_slp = u1_g_PwrCtrlComRxGetForceSleep();

    /* Boot信号 */
    u1_t_boot = u1_g_PwrCtrl_PinMonitor_GetPinInfo((U1)PWRCTRL_CFG_PRIVATE_KIND_BOOT);

    /* スタンバイ条件成立 */
    if( ((u1_t_stby_rslt == (U1)PWRCTRL_OBSERVE_STBY_OK)     /* 全VMスタンバイ可 */
     ||  (u1_t_force_slp == (U1)PWRCTRL_OBSERVE_FSLP_ON))    /* または、強制スリープ条件成立 */
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
  return        : [Out] 起動検知/OFF検知判定結果
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
  Function      : vd_g_PwrCtrlObservePsailReq
  Description   : PM_PSAIL_ERR_N監視開始/終了要求通知処理
  param[in/out] :[ in ] u1_a_req:0 終了要求
                                 1 開始要求
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlObservePsailReq(const U1 u1_a_req )
{
    u1_s_PwrCtrl_Observe_Psail_Sts = u1_a_req;

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlObservePsHoldReq
  Description   : PMA_PS_HOLD監視開始/終了要求通知処理
  param[in/out] :[ in ] u1_a_req:開始/終了要求
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlObservePsHoldReq(const U1 u1_a_req )
{
    u1_s_PwrCtrl_Observe_PsHold_Sts = u1_a_req;

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlObservePgdAsilVbSysPwrReq
  Description   : PGOOD_ASIL_VB監視開始/終了要求(SYS電源制御状態)通知処理
  param[in/out] :[ in ] u1_a_req:開始/終了要求
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlObservePgdAsilVbSysPwrReq(const U1 u1_a_req )
{
    u1_s_PwrCtrl_Observe_PgdAsilVbSysPwr_Sts = u1_a_req;

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlObservePgdAsilVbLowPwrReq
  Description   : PGOOD_ASIL_VB監視開始/終了要求(LOW-POWER-ON状態)通知処理
  param[in/out] :[ in ] u1_a_req:開始/終了要求
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlObservePgdAsilVbLowPwrReq(const U1 u1_a_req )
{
    u1_s_PwrCtrl_Observe_PgdAsilVbLowPwr_Sts = u1_a_req;

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlObservePgdAsilVsysReq
  Description   : PGOOD_ASIL_VSYS監視開始/終了要求通知処理
  param[in/out] :[ in ] u1_a_req:開始/終了要求
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlObservePgdAsilVsysReq(const U1 u1_a_req )
{
    u1_s_PwrCtrl_Observe_PgdAsilVsys_Sts = u1_a_req;

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlObservePgdAsilVsysV11Req
  Description   : PGOOD_ASIL_VSYS(V11)監視監視開始/終了要求通知処理
  param[in/out] :[ in ] u1_a_req:開始/終了要求
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlObservePgdAsilVsysV11Req(const U1 u1_a_req )
{
    u1_s_PwrCtrl_Observe_PgdAsilVsysV11_Sts = u1_a_req;

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlObservePgdDiodeReq
  Description   : PGOOD_DIODE監視開始/終了要求通知処理
  param[in/out] :[ in ] u1_a_req:開始/終了要求
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlObservePgdDiodeReq(const U1 u1_a_req )
{
    u1_s_PwrCtrl_Observe_PgdDiode_Sts = u1_a_req;

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlObservePgdVbReq
  Description   : PGOOD_VB監視開始/終了要求通知処理
  param[in/out] :[ in ] u1_a_req:開始/終了要求
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlObservePgdVbReq(const U1 u1_a_req )
{
    u1_s_PwrCtrl_Observe_PgdVb_Sts = u1_a_req;

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlObservePgdVsysReq
  Description   : PGOOD_VSYS監視監視開始/終了要求通知処理
  param[in/out] :[ in ] u1_a_req:開始/終了要求
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlObservePgdVsysReq(const U1 u1_a_req )
{
    u1_s_PwrCtrl_Observe_PgdVsys_Sts = u1_a_req;

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlObserveSoCResetErrReq
  Description   : SoCリセット要求(異常)検知開始/終了要求通知処理
  param[in/out] :[ in ] u1_a_req:開始/終了要求
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlObserveSoCResetErrReq(const U1 u1_a_req )
{
    u1_s_PwrCtrl_Observe_SoCResetErr_Sts = u1_a_req;

    return;
}

/*****************************************************************************
  Function      : u2_g_PwrCtrlObserveGetErrSts
  Description   : 監視異常発生内容取得処理
  param[in/out] : none
  return        : 監視異常発生内容
  Note          : none
*****************************************************************************/
U2 u2_g_PwrCtrlObserveGetErrSts(void)
{
    return(u2_s_PwrCtrl_Observe_Err_Sts);
}

/*****************************************************************************
  Function      : u2_g_PwrCtrlObserveGetResetSts
  Description   : リセット要求内容取得処理
  param[in/out] : none
  return        : リセット要求内容
  Note          : none
*****************************************************************************/
U2 u2_g_PwrCtrlObserveGetResetSts(void)
{
    return(u2_s_PwrCtrl_Observe_Reset_Sts);
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlObserveSetSocPower
  Description   : SoC起動状態設定処理
  param[in/out] :[ in ] u1_a_sts:SoC起動状態
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlObserveSetSocPower(const U1 u1_a_sts )
{
    u1_s_PwrCtrl_Observe_SocPower_Sts = u1_a_sts;  /* 監視制御用に設定内容保存 */
    vd_g_PwrCtrlComTxSetSoCPower(u1_a_sts);        /* VM間通信送信設定 */
    
    return;
}

/*****************************************************************************
  Function      : u1_s_PwrCtrlObserveJdgVm3Stby
  Description   : VM3スタンバイ条件成立判定処理
  param[in/out] : none
  return        : [Out] VM3のスタンバイ条件成立有無
  Note          : none
*****************************************************************************/
static U1 u1_s_PwrCtrlObserveJdgVm3Stby( void )
{
    U1 u1_t_stbyinfo;

    u1_t_stbyinfo = (U1)PWRCTRL_OBSERVE_STBY_NG;

    /* スリープ許可 */
    if(u1_s_PwrCtrl_Observe_Vm3StbyInfo == (U1)PWRCTRL_MAIN_PROHIBITSLEEP_OFF)
    {
        /* スタンバイ可 */
        u1_t_stbyinfo = (U1)PWRCTRL_OBSERVE_STBY_OK;
    }

    return(u1_t_stbyinfo);
}

/*****************************************************************************
  Function      : u2_g_PwrCtrlObserveSailUartSeq
  Description   : SAIL UART Message監視処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static U2 u2_g_PwrCtrlObserveSailUartSeq( void )
{
    U2 u2_t_ret;
    U1 u1_t_sailuart;

    u2_t_ret = (U2)PWRCTRL_OBSERVE_ERR_NON;

    /* SAIL UART Message監視結果を取得 */
    u1_t_sailuart = u1_g_PwrCtrl_ObserveSAIL_UartErrSts();

    /* SAIL UART Message監視結果が異常の場合 */
    if(u1_t_sailuart == (U1)PWRCTRL_OBSERVESAIL_NG)
    {
        /* SAIL UART Message監視視異常発生を返却 */
        u2_t_ret = (U2)PWRCTRL_OBSERVE_ERR_SAILUART;
    }

    return(u2_t_ret);
}

/*****************************************************************************
  Function      : u2_g_PwrCtrlObserveSailErrSeq
  Description   : SAIL-ERR監視処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static U2 u2_g_PwrCtrlObserveSailErrSeq( void )
{
    U2 u2_t_ret;
    U1 u1_t_sailerr;

    u2_t_ret = (U2)PWRCTRL_OBSERVE_ERR_NON;

    /* SAIL-ERR監視結果を取得 */
    u1_t_sailerr = u1_g_PwrCtrl_ObserveSAIL_SailErrSts();

    /* SAIL-ERR監視結果が異常の場合 */
    if(u1_t_sailerr == (U1)PWRCTRL_OBSERVESAIL_NG)
    {
        /* SAIL-ERR監視異常発生を返却 */
        u2_t_ret = (U2)PWRCTRL_OBSERVE_ERR_SAILERR;
    }

    return(u2_t_ret);
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlObservePsailSeq
  Description   : PM_PSAIL_ERR_N監視処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static U2 u2_s_PwrCtrlObservePsailSeq( void )
{
    U2 u2_t_ret;
    U1 u1_t_read_lv;

    u2_t_ret = (U2)PWRCTRL_OBSERVE_ERR_NON;

    /* PM_PSAIL_ERR_N監視実行状態の場合 */
    if(u1_s_PwrCtrl_Observe_Psail_Sts == (U1)PWRCTRL_OBSERVE_ON)
    {
        /* PM_PSAIL_ERR_N端子状態を取得 */
        u1_t_read_lv = u1_g_PwrCtrl_PinMonitor_GetPinInfo((U1)PWRCTRL_CFG_PRIVATE_KIND_PM_PSAIL_ERR_N);

        /* 端子の読み出し結果がLOWの場合 */
        if(u1_t_read_lv == (U1)MCU_DIO_LOW)
        {
            /* PM_PSAIL_ERR_N監視異常発生を返却 */
            u2_t_ret = (U2)PWRCTRL_OBSERVE_ERR_PMPSAIL;
        }
    }

    return(u2_t_ret);
}

/*****************************************************************************
  Function      : u1_g_PwrCtrlObservePsHoldSeq
  Description   : PMA_PS_HOLD監視処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static U2 u2_s_PwrCtrlObservePsHoldSeq( void )
{
    U2 u2_t_ret;
    U1 u1_t_read_lv;

    u2_t_ret = (U2)PWRCTRL_OBSERVE_ERR_NON;

    /* PMA_PS_HOLD監視実行状態の場合 */
    if(u1_s_PwrCtrl_Observe_PsHold_Sts == (U1)PWRCTRL_OBSERVE_ON)
    {
        /* PMA_PS_HOLD端子状態を取得 */
        u1_t_read_lv = u1_g_PwrCtrl_PinMonitor_GetPinInfo((U1)PWRCTRL_CFG_PRIVATE_KIND_PMA_PS_HOLD);

        /* 端子の読み出し結果がLOWの場合 */
        if(u1_t_read_lv == (U1)MCU_DIO_LOW)
        {
            /* PMA_PS_HOLD監視異常発生を返却 */
            u2_t_ret = (U2)PWRCTRL_OBSERVE_ERR_PMAPS;
        }
    }

    return(u2_t_ret);
}

/*****************************************************************************
  Function      : u2_g_PwrCtrlObserveSpiFailSeq
  Description   : SPI通信途絶監視処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static U2 u2_g_PwrCtrlObserveSpiFailSeq( void )
{
    U2 u2_t_ret;
    U1 u1_t_spifail;

    u2_t_ret = (U2)PWRCTRL_OBSERVE_ERR_NON;

    /* SoC起動状態の場合 */
    if(u1_s_PwrCtrl_Observe_SocPower_Sts == (U1)PWRCTRL_OBSERVE_SOCPOWER_ON)
    {
        /* SPI通信途絶結果を取得 */
        u1_t_spifail = u1_g_PwrCtrlComGetSpiFail();

        /* SPI通信途絶結果が異常の場合 */
        if(u1_t_spifail == (U1)PWRCTRL_COM_SPIFAIL_NG)
        {
            /* SPI通信途絶異常発生を返却 */
            u2_t_ret = (U2)PWRCTRL_OBSERVE_ERR_SPI;
        }
    }

    return(u2_t_ret);
}

/*****************************************************************************
  Function      : u2_s_PwrCtrlObservePgdAsilVbSeq
  Description   : PGOOD_ASIL_VB監視処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static U2 u2_s_PwrCtrlObservePgdAsilVbSeq( void )
{
    U2 u2_t_ret;
    U1 u1_t_read_lv;

    u2_t_ret = (U2)PWRCTRL_OBSERVE_ERR_NON;

    /* PGOOD_ASIL_VB監視実行状態(LOW-POWER-ON =Hi & SYS電源ON制御完了)の場合 */
    if((u1_s_PwrCtrl_Observe_PgdAsilVbLowPwr_Sts == (U1)PWRCTRL_OBSERVE_ON)
     &&(u1_s_PwrCtrl_Observe_PgdAsilVbSysPwr_Sts == (U1)PWRCTRL_OBSERVE_ON))
    {
        /* PGOOD_ASIL_VB端子状態を取得 */
        u1_t_read_lv = u1_g_PwrCtrl_PinMonitor_GetPinInfo((U1)PWRCTRL_CFG_PRIVATE_KIND_PGOOD_ASIL_VB);

        /* 端子の読み出し結果がLOWの場合 */
        if(u1_t_read_lv == (U1)MCU_DIO_LOW)
        {
            /* PGOOD監視異常発生を返却 */
            u2_t_ret = (U2)PWRCTRL_OBSERVE_ERR_PGD_ASIL_VB;
        }
    }

    return(u2_t_ret);
}

/*****************************************************************************
  Function      : u2_s_PwrCtrlObservePgdAsilVsysSeq
  Description   : PGOOD_ASIL_VSYS監視処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static U2 u2_s_PwrCtrlObservePgdAsilVsysSeq( void )
{
    U2 u2_t_ret;
    U1 u1_t_read_lv;

    u2_t_ret = (U2)PWRCTRL_OBSERVE_ERR_NON;

    /* PGOOD_ASIL_VSYS監視実行状態の場合 */
    if(u1_s_PwrCtrl_Observe_PgdAsilVsys_Sts == (U1)PWRCTRL_OBSERVE_ON)
    {
        /* PGOOD_ASIL_VSYS端子状態を取得 */
        u1_t_read_lv = u1_g_PwrCtrl_PinMonitor_GetPinInfo((U1)PWRCTRL_CFG_PRIVATE_KIND_PGOOD_ASIL_VSYS);

        /* 端子の読み出し結果がLOWの場合 */
        if(u1_t_read_lv == (U1)MCU_DIO_LOW)
        {
            /* PGOOD_ASIL_VSYS監視異常発生を返却 */
            u2_t_ret = (U2)PWRCTRL_OBSERVE_ERR_PGD_ASIL_VSYS;
        }
    }

    return(u2_t_ret);
}

/*****************************************************************************
  Function      : u2_s_PwrCtrlObservePgdAsilVsysV11Seq
  Description   : PGOOD_ASIL_VSYS(V11)監視処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static U2 u2_s_PwrCtrlObservePgdAsilVsysV11Seq( void )
{
    U2 u2_t_ret;
    U1 u1_t_read_lv;

    u2_t_ret = (U2)PWRCTRL_OBSERVE_ERR_NON;

    /* PGOOD_ASIL_VSYS(V11)監視実行状態の場合 */
    if(u1_s_PwrCtrl_Observe_PgdAsilVsysV11_Sts == (U1)PWRCTRL_OBSERVE_ON)
    {
        /* PGOOD_ASIL_VSYS(V11)端子状態を取得 */
        u1_t_read_lv = u1_g_PwrCtrl_PinMonitor_GetPinInfo((U1)PWRCTRL_CFG_PRIVATE_KIND_PGOOD_ASIL_VSYS_V11);

        /* 端子の読み出し結果がLOWの場合 */
        if(u1_t_read_lv == (U1)MCU_DIO_LOW)
        {
            /* PGOOD_ASIL_VSYS(V11)監視異常発生を返却 */
            u2_t_ret = (U2)PWRCTRL_OBSERVE_ERR_PGD_ASIL_VSYS_V11;
        }
    }

    return(u2_t_ret);
}

/*****************************************************************************
  Function      : u2_s_PwrCtrlObservePgdDiodeSeq
  Description   : PGOOD_DIODE監視処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static U2 u2_s_PwrCtrlObservePgdDiodeSeq( void )
{
    U2 u2_t_ret;
    U1 u1_t_read_lv;

    u2_t_ret = (U2)PWRCTRL_OBSERVE_ERR_NON;

    /* PGOOD_DIODE監視実行状態の場合 */
    if(u1_s_PwrCtrl_Observe_PgdDiode_Sts == (U1)PWRCTRL_OBSERVE_ON)
    {
        /* PGOOD_DIODE端子状態を取得 */
        u1_t_read_lv = u1_g_PwrCtrl_PinMonitor_GetPinInfo((U1)PWRCTRL_CFG_PRIVATE_KIND_PGOOD_DIODE);

        /* 端子の読み出し結果がLOWの場合 */
        if(u1_t_read_lv == (U1)MCU_DIO_LOW)
        {
            /* PGOOD_DIODE監視異常発生を返却 */
            u2_t_ret = (U2)PWRCTRL_OBSERVE_ERR_PGD_DIODE;
        }
    }

    return(u2_t_ret);
}

/*****************************************************************************
  Function      : u2_s_PwrCtrlObservePgdVbSeq
  Description   : PGOOD_VB監視処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static U2 u2_s_PwrCtrlObservePgdVbSeq( void )
{
    U2 u2_t_ret;
    U1 u1_t_read_lv;

    u2_t_ret = (U2)PWRCTRL_OBSERVE_ERR_NON;

    /* PGOOD_VB監視実行状態の場合 */
    if(u1_s_PwrCtrl_Observe_PgdVb_Sts == (U1)PWRCTRL_OBSERVE_ON)
    {
        /* PGOOD_VB端子状態を取得 */
        u1_t_read_lv = u1_g_PwrCtrl_PinMonitor_GetPinInfo((U1)PWRCTRL_CFG_PRIVATE_KIND_PGOOD_VB);

        /* 端子の読み出し結果のどちらかがLOWの場合 */
        if(u1_t_read_lv == (U1)MCU_DIO_LOW)
        {
            /* PGOOD_VB監視異常発生を返却 */
            u2_t_ret = (U2)PWRCTRL_OBSERVE_ERR_PGD_VB;
        }
    }

    return(u2_t_ret);
}

/*****************************************************************************
  Function      : u2_s_PwrCtrlObservePgdVsysSeq
  Description   : PGOOD_VSYS監視処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static U2 u2_s_PwrCtrlObservePgdVsysSeq( void )
{
    U2 u2_t_ret;
    U1 u1_t_read_lv;

    u2_t_ret = (U2)PWRCTRL_OBSERVE_ERR_NON;

    /* PGOOD_VSYS監視実行状態の場合 */
    if(u1_s_PwrCtrl_Observe_PgdVsys_Sts == (U1)PWRCTRL_OBSERVE_ON)
    {
        /* PGOOD_VSYS端子状態を取得 */
        u1_t_read_lv = u1_g_PwrCtrl_PinMonitor_GetPinInfo((U1)PWRCTRL_CFG_PRIVATE_KIND_PGOOD_VSYS);

        /* 端子の読み出し結果のどちらかがLOWの場合 */
        if(u1_t_read_lv == (U1)MCU_DIO_LOW)
        {
            /* PGOOD_VSYS監視異常発生を返却 */
            u2_t_ret = (U2)PWRCTRL_OBSERVE_ERR_PGD_VSYS;
        }
    }

    return(u2_t_ret);
}

/*****************************************************************************
  Function      : u2_s_PwrCtrlObserveSoCResetReqSeq
  Description   : SoCリセット要求検知処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static U2 u2_s_PwrCtrlObserveSoCResetReqSeq( void )
{
    U2 u2_t_ret;
    U1 u1_t_read_req;

    u2_t_ret = (U2)PWRCTRL_OBSERVE_ERR_NON;

    /* SoCリセット要求を取得 */
    u1_t_read_req = u1_g_PwrCtrlComGetSoCResetReq();

    /* 取得内容がSoCリセット要求(正常)の場合 */
    if(u1_t_read_req == (U1)PWRCTRL_COM_SOCRESET_SOCNORM)
    {
        /* SoC起動状態 かつ 前回値がSoCリセット要求(正常)以外の場合 */
        if((u1_s_PwrCtrl_Observe_SocPower_Sts == (U1)PWRCTRL_OBSERVE_SOCPOWER_ON)
        && (u1_s_PwrCtrl_Observe_PreSoCResetReq != (U1)PWRCTRL_COM_SOCRESET_SOCNORM))
        {
            u2_t_ret = (U2)PWRCTRL_OBSERVE_RESET_SOCNORM;
        }
    }

    /* 取得内容がSoCリセット要求(異常)の場合 */
    if(u1_t_read_req == (U1)PWRCTRL_COM_SOCRESET_SOCERR)
    {
        /* SoCリセット要求(異常)検知実行状態 かつ 前回値がSoCリセット要求(異常)以外の場合 */
        if((u1_s_PwrCtrl_Observe_SoCResetErr_Sts == (U1)PWRCTRL_OBSERVE_ON)
        && (u1_s_PwrCtrl_Observe_PreSoCResetReq != (U1)PWRCTRL_OBSERVE_RESET_SOCERR))
        {
            u2_t_ret = (U2)PWRCTRL_OBSERVE_RESET_SOCERR;
        }
    }

    /* SoCリセット要求の前回値を更新 */
    u1_s_PwrCtrl_Observe_PreSoCResetReq = u1_t_read_req;

    return(u2_t_ret);
}

/*****************************************************************************
  Function      : u2_s_PwrCtrlObserveNMDiagResetSeq
  Description   : NMダイアグリセット検知処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static U2 u2_s_PwrCtrlObserveNMDiagResetSeq( void )
{
    U2 u2_t_ret;
    U1 u1_t_read_req;

    u2_t_ret = (U2)PWRCTRL_OBSERVE_ERR_NON;

    /* NMダイアグリセットを取得 */
    u1_t_read_req = u1_g_PwrCtrlComGetNMDiagReset();
    
    /* 取得内容がNMダイアグリセット要求の場合 */
    if(u1_t_read_req == (U1)PWRCTRL_COM_NMDIAGRESET_REQ)
    {
        /* SoC起動状態 かつ 前回値がNMダイアグリセット要求以外の場合 */
        if((u1_s_PwrCtrl_Observe_SocPower_Sts == (U1)PWRCTRL_OBSERVE_SOCPOWER_ON)
        && (u1_s_PwrCtrl_Observe_PreNMDiagReset != (U1)PWRCTRL_COM_NMDIAGRESET_REQ))
        {
            u2_t_ret = (U2)PWRCTRL_OBSERVE_RESET_NMDIAG;
        }
    }

    /* NMダイアグリセットの前回値を更新 */
    u1_s_PwrCtrl_Observe_PreNMDiagReset = u1_t_read_req;

    return(u2_t_ret);
}

/****************************************************************************/
/* Service API                                                              */
/****************************************************************************/
/**** End of File ***********************************************************/
