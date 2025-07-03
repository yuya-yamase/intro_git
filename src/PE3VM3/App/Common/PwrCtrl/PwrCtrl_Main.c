/* PwrCtrl_Main_c_v1-0-0                                                    */
/****************************************************************************/
/* Copyright (C) 2023 Denso Co.,Ltd. All rights reserved.                   */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | PwrCtrl_Main/CODE                                         */
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
/* SYS電源状態 */
#define PWRCTRL_MAIN_SYS_STS_INIT       (0x00U)  /* 初期状態 */
#define PWRCTRL_MAIN_SYS_STS_INPRC      (0x01U)  /* 実行中 */
#define PWRCTRL_MAIN_SYS_STS_WAITDEV    (0x02U)  /* SYSデバイス終了待ち */
#define PWRCTRL_MAIN_SYS_STS_BUDET      (0x03U)  /* BU-DET判定中 */
#define PWRCTRL_MAIN_SYS_STS_COMP       (0xFFU)  /* 完了 */

/* 非冗長電源状態 */
#define PWRCTRL_MAIN_NRD_STS_INIT       (0x00U)  /* 初期状態 */
#define PWRCTRL_MAIN_NRD_STS_INPRC      (0x01U)  /* 実行中 */
#define PWRCTRL_MAIN_NRD_STS_COMP       (0xFFU)  /* 完了*/

/* SIP電源状態 */
#define PWRCTRL_MAIN_SIP_STS_INIT       (0x00U)  /* 初期状態 */
#define PWRCTRL_MAIN_SIP_STS_INPRC      (0x01U)  /* 実行中 */
#define PWRCTRL_MAIN_SIP_STS_CHK_MMSTBY (0x02U)  /* MM_STBY_N変化待ち */
#define PWRCTRL_MAIN_SIP_STS_CHK_AOSS   (0x03U)  /* AOSS_SLEEP_ENTRY_EXIT変化待ち */
#define PWRCTRL_MAIN_SIP_STS_CHK_WAKE   (0x04U)  /* 起動要因判定中 */
#define PWRCTRL_MAIN_SIP_STS_COMP       (0xFFU)  /* 完了 */

/* SIP強制電源OFF状態 */
#define PWRCTRL_MAIN_FORCEDOFF_STS_INIT    (0x00U)  /* 初期状態 */
#define PWRCTRL_MAIN_FORCEDOFF_STS_SOCERR  (0x01U)  /* SOC異常実行中 */
#define PWRCTRL_MAIN_FORCEDOFF_STS_PMICERR (0x02U)  /* PMIC異常実行中 */
#define PWRCTRL_MAIN_FORCEDOFF_STS_DDERR   (0x03U)  /* DDコンOFF実行中 */

/* Dio端子監視結果 */
#define PWRCTRL_MAIN_DIO_READ_CHK_INIT  (0x00U)  /* 状態監視初期状態 */
#define PWRCTRL_MAIN_DIO_READ_CHK_OK    (0x01U)  /* 指定時間内に正常応答 */
#define PWRCTRL_MAIN_DIO_READ_CHK_NG    (0xFFU)  /* 時間超過or異常応答 */

#define PWRCTRL_MAIN_BUSSLEEPTIME       (12000U) /* 60sec/5ms周期 */

#define PWRCTRL_MAIN_TIME_INIT          (0U)
#define PWRCTRL_MAIN_TIME_MMSTBY        (100000U / PWRCTRL_CFG_TASK_TIME)
#define PWRCTRL_MAIN_TIME_AOSS          (200U / PWRCTRL_CFG_TASK_TIME)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static void vd_s_PwrCtrlMainStartSet( void );
static void vd_s_PwrCtrlMainBonDDconvOnReq( void );
static void vd_s_PwrCtrlMainBonPwrOnReq( void );
static void vd_s_PwrCtrlMainSipOffMcuStandbyReq( void );
static void vd_s_PwrCtrlMainSipOffMcuStandbySysDevReq( void );

static void vd_s_PwrCtrlMainSleepJudge( void );

/* シーケンス動作用処理 */
static void vd_s_PwrCtrlMainBonSeq( void );
static void vd_s_PwrCtrlMainWakeUpSeq( void );
static void vd_s_PwrCtrlMainSipOffMcuStandbySeq( void );
static void vd_s_PwrCtrlMainStandbySeq( void );
static void vd_s_PwrCtrlMainForcedOffSeq( void );
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
static U1  u1_s_PwrCtrl_Main_Sts;                         /* 電源制御状態   */
static U1  u1_s_PwrCtrl_Main_SysPwrSts;                   /* SYS電源状態    */
static U1  u1_s_PwrCtrl_Main_NonRednPwrSts;               /* 非冗長電源状態 */
static U1  u1_s_PwrCtrl_Main_SipPwrSts;                   /* SIP電源状態    */

static U1  u1_s_PwrCtrl_Main_ShtdwnOkFlag;
static U1  u1_s_PwrCtrl_Main_BusSleepFlag;
static U4  u4_s_PwrCtrl_Main_BusSleep_Time;

static U4  u4_s_PwrCtrl_Main_MmStby;
static U4  u4_s_PwrCtrl_Main_Aoss;
static U1  u1_s_PwrCtrl_Main_WakeUpFlag;                  /* MCU起動状態    */

#ifdef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF
U1 u1_g_PwrCtrl_Main_DbgFailOffFlag; /* DBG-FAIL-OFF状態 */
#endif

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Functions                                                                */
/*--------------------------------------------------------------------------*/
/*****************************************************************************
  Function      : u1_g_PwrCtrlMainShtdwnOk
  Description   : 電源制御スリープ可否通知処理
  param[in/out] : none
  return        : PWRCTRL_COMMON_SYS_PWR_OFF(0) スリープNG
                  PWRCTRL_COMMON_SYS_PWR_ON (1) スリープOK
  Note          : none
*****************************************************************************/
U1 u1_g_PwrCtrlMainShtdwnOk( void )
{
    return( u1_s_PwrCtrl_Main_ShtdwnOkFlag );
}
/*****************************************************************************
  Function      : u1_g_PwrCtrlWakeUpInfo
  Description   : MCU初期化処理、またはウェイクアップ処理完了状態判定通知処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
U1 u1_g_PwrCtrlWakeUpInfo( void )
{
    return( u1_s_PwrCtrl_Main_WakeUpFlag );
}

/****************************************************************************/
/* Scheduled Functions                                                      */
/****************************************************************************/
/*****************************************************************************
  Function      : vd_g_PwrCtrlMainBonReq
  Description   : +B-ON,シーケンス要求
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlMainBonReq( void )
{
    /* 端子モニタ制御初期化処理 */
    vd_g_PwrCtrlPinMonitorInit();
    /* MCUの起動完了フラグをONに設定 */
    u1_s_PwrCtrl_Main_WakeUpFlag =(U1)TRUE;
    
#ifdef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF
    u1_g_PwrCtrl_Main_DbgFailOffFlag = (U1)MCU_DIO_INVALID;
#endif

    vd_s_PwrCtrlMainStartSet();
    /* SYS電源制御 初期化処理 */
    vd_g_PwrCtrlSysInit();
    /* 非冗長電源制御 初期化処理 */
    vd_g_PwrCtrlNoRedunInit();

    u1_s_PwrCtrl_Main_ShtdwnOkFlag = (U1)PWRCTRL_COMMON_SYS_PWR_OFF; /* 暫定 */

    vd_g_PwrCtrlSipBonInit();                                        /* SIP電源状態+B初期化要求 */
    vd_g_PwrCtrlSysPwrOnStart();
    vd_g_PwrCtrlNoRedunPwrOnStart();

    /* +B-ONシーケンス実施要求 */
    u1_s_PwrCtrl_Main_Sts       = (U1)PWRCTRL_MAIN_BON_REQ;
    u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_INPRC;    /* SYS電源：実行中 */
    u4_s_PwrCtrl_Main_MmStby    = (U4)PWRCTRL_MAIN_TIME_INIT;

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainBonDDconvOnReq
  Description   : +B-ON,SIP用DDコン起動処理開始要求
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainBonDDconvOnReq( void )
{
    vd_g_PwrCtrlSipOnReq();                                       /* SIP電源状態+B初期化要求 */

    /* +B-ONシーケンス実施要求 */
    u1_s_PwrCtrl_Main_Sts       = (U1)PWRCTRL_MAIN_BON_REQ;
    u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_COMP;  /* SYS電源状態：実行中→完了 */
    u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_INPRC; /* SIP電源状態：初期状態→実行中 */
    u4_s_PwrCtrl_Main_MmStby    = (U4)PWRCTRL_MAIN_TIME_INIT;

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainBonPwrOnReq
  Description   : +B-ON,SIP電源のみ起動処理開始要求
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainBonPwrOnReq( void )
{
    vd_g_PwrCtrlSipOnPwrOnReq();                                       /* SIP電源状態SIP起動初期化要求 */

    /* +B-ONシーケンス実施要求 */
    u1_s_PwrCtrl_Main_Sts       = (U1)PWRCTRL_MAIN_BON_REQ;
    u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_COMP;       /* SYS電源状態：実行中→完了 */
    u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_INPRC;      /* SIP電源状態：初期状態→実行中 */
    u4_s_PwrCtrl_Main_MmStby    = (U4)PWRCTRL_MAIN_TIME_INIT;

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlMainWakeupReq
  Description   : ウェイクアップシーケンス要求
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlMainWakeupReq( void )
{
    /* 端子モニタ制御初期化処理 */
    vd_g_PwrCtrlPinMonitorInit();
    /* MCUの起動完了フラグをONに設定 */
    u1_s_PwrCtrl_Main_WakeUpFlag =(U1)TRUE;

#ifdef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF 
    u1_g_PwrCtrl_Main_DbgFailOffFlag = (U1)MCU_DIO_INVALID;
#endif

    vd_s_PwrCtrlMainStartSet();
    /* SYS電源制御 初期化処理 */
    vd_g_PwrCtrlSysInit();
    /* 非冗長電源制御 初期化処理 */
    vd_g_PwrCtrlNoRedunInit();

    u1_s_PwrCtrl_Main_ShtdwnOkFlag = (U1)PWRCTRL_COMMON_SYS_PWR_OFF; /* 暫定 */

    vd_g_PwrCtrlSipWkupInit();                                       /* SIP電源状態Wakeup初期化要求 */
    vd_g_PwrCtrlSysPwrOnStart();
    vd_g_PwrCtrlNoRedunPwrOnStart();

    /* ウェイクアップシーケンス実施要求 */
    u1_s_PwrCtrl_Main_Sts       = (U1)PWRCTRL_MAIN_WAKEUP_REQ;
    u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_INPRC;    /* SYS電源：実行中 */
    u4_s_PwrCtrl_Main_Aoss      = (U4)PWRCTRL_MAIN_TIME_INIT;
    u4_s_PwrCtrl_Main_MmStby    = (U4)PWRCTRL_MAIN_TIME_INIT;

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainSipOffMcuStandbyReq
  Description   : SIP電源OFF&MCUスタンバイシーケンス要求
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainSipOffMcuStandbyReq( void )
{
    u1_s_PwrCtrl_Main_Sts           = (U1)PWRCTRL_MAIN_SIPOFF_MCUSTANDBY_REQ;
    vd_s_PwrCtrlMainStartSet();
    EthSwt_SWIC_PowerOff();                                             /* EtherSW終了要求 */

    u1_s_PwrCtrl_Main_BusSleepFlag  = (U1)PWRCTRL_COMMON_SYS_PWR_OFF;
    u1_s_PwrCtrl_Main_SipPwrSts     = (U1)PWRCTRL_MAIN_SIP_STS_INPRC; /* SIP電源状態：実行中 */
    vd_g_PwrCtrlSipOffReq();                                          /* SIP電源OFF */

    u1_s_PwrCtrl_Main_NonRednPwrSts = (U1)PWRCTRL_MAIN_NRD_STS_INPRC; /* 非冗長電源状態:開始→実行中 */
    vd_g_PwrCtrlNoRedunPwrOffStart();                                 /* 非冗長電源OFF要求 */

}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainSipOffMcuStandbySysDevReq
  Description   : SIP電源OFF&MCUスタンバイシーケンス
                  SYS系電源OFF、MCUスタンバイ処理開始要求
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainSipOffMcuStandbySysDevReq( void )
{
    u1_s_PwrCtrl_Main_Sts           = (U1)PWRCTRL_MAIN_SIPOFF_MCUSTANDBY_REQ;
    vd_s_PwrCtrlMainStartSet();
    EthSwt_SWIC_PowerOff();                                             /* EtherSW終了要求 */

    u1_s_PwrCtrl_Main_BusSleepFlag  = (U1)PWRCTRL_COMMON_SYS_PWR_OFF;
    u1_s_PwrCtrl_Main_SipPwrSts     = (U1)PWRCTRL_MAIN_SIP_STS_COMP;    /* SIP電源状態：実行中→完了 */
    u1_s_PwrCtrl_Main_SysPwrSts     = (U1)PWRCTRL_MAIN_SYS_STS_WAITDEV; /* SYS電源状態：開始→SYSデバイス終了待ち */
    u1_s_PwrCtrl_Main_NonRednPwrSts = (U1)PWRCTRL_MAIN_NRD_STS_INPRC;   /* 非冗長電源状態:開始→実行中 */
    vd_g_PwrCtrlNoRedunPwrOffStart();                                   /* 非冗長電源OFF要求 */

}

/*****************************************************************************
  Function      : vd_g_PwrCtrlMainStandbyReq
  Description   : スタンバイシーケンス要求
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlMainStandbyReq( void )
{
    /* ★要検討★処理実行中は要求を受け付けない */
    u1_s_PwrCtrl_Main_Sts           = (U1)PWRCTRL_MAIN_STANDBY_REQ;
    vd_s_PwrCtrlMainStartSet();
    EthSwt_SWIC_PowerOff();                                             /* EtherSW終了要求 */
    u1_s_PwrCtrl_Main_SipPwrSts     = (U1)PWRCTRL_MAIN_SIP_STS_INPRC; /* SIP電源状態：実行中 */
    vd_g_PwrCtrlSipStbyReq();                                         /* SIP電源スタンバイ */

    u1_s_PwrCtrl_Main_NonRednPwrSts = (U1)PWRCTRL_MAIN_NRD_STS_INPRC; /* 非冗長電源状態:開始→実行中 */
    vd_g_PwrCtrlNoRedunPwrOffStart();                                 /* 非冗長電源OFF要求 */
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlMainBuDetReq
  Description   : BU断終了シーケンス要求
  param[in/out] : [ in ] u1_s_evtype 発生したイベントタイプ
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlMainBuDetReq( void )
{
    /* 【todo】BU断終了シーケンス要求 */
    /* vd_g_PwrCtrlSipBuDetReq(); */
    /* 【todo】EtherSW終了要求処理をコールする */
    /* 暫定 はまり込み防止 */
    u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_INPRC;
    
    /* 【todo】デバイス関連のPIN制御を行う */
    /* 【todo】SYS電源のPIN制御を行う */
    /* 【todo】Ether関連のPIN制御を行う */
    /* 【todo】SIP電源のPIN制御を行う */
    /* 【todo】デバイス関連のPIN制御を行う */
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlMainForcedOffReq
  Description   : SIP電源強制OFFシーケンス要求
  param[in/out] : [ in ] u1_s_evtype 発生したイベントタイプ
  return        : none
  Note          : none
*****************************************************************************/
static void vd_g_PwrCtrlMainForcedOffReq( const U1 u1_s_evtype )
{
    switch(u1_s_evtype){
       case (U1)PWRCTRL_MAIN_FORCEDOFF_STS_SOCERR:
        u1_s_PwrCtrl_Main_Sts       = (U1)PWRCTRL_MAIN_FORCEDOFF_REQ;
        u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_INPRC; /* SIP電源状態：実行中 */
        vd_g_PwrCtrlSipFoccedOffSTEP1Req();                           /* SIP強制OFFシーケンス STEP1から開始 */
        break;

       case (U1)PWRCTRL_MAIN_FORCEDOFF_STS_PMICERR:
        u1_s_PwrCtrl_Main_Sts       = (U1)PWRCTRL_MAIN_FORCEDOFF_REQ;
        u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_INPRC; /* SIP電源状態：実行中 */
        vd_g_PwrCtrlSipFoccedOffSTEP2Req();                           /* SIP強制OFFシーケンス STEP2から開始 */
        break;

       case (U1)PWRCTRL_MAIN_FORCEDOFF_STS_DDERR:
        u1_s_PwrCtrl_Main_Sts       = (U1)PWRCTRL_MAIN_FORCEDOFF_REQ;
        u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_INPRC; /* SIP電源状態：実行中 */
        vd_g_PwrCtrlSipFoccedOffSTEP4Req();                           /* SIP強制OFFシーケンス STEP4から開始 */
        break;

       default:
        /* 何もしない */
        break;
    }
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlMainTask
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlMainTask( void )
{
    /* 端子モニタ定期処理 */
    vd_g_PwrCtrlPinMonitorMainFunc();
    
    /* 終了シーケンス開始要否の判定 */
    vd_s_PwrCtrlMainSleepJudge();

    u1_g_PwrCtrl_Main_DbgFailOffFlag = u1_g_PwrCtrl_PinMonitor_GetPinInfo(PWRCTRL_CFG_PRIVATE_KIND_DBG_FAIL_OFF);    /* DBG-FAIL-OFF端子の状態を取得 */

    if(u1_s_PwrCtrl_Main_Sts == (U1)PWRCTRL_MAIN_BON_REQ)
    {
       vd_s_PwrCtrlMainBonSeq();              /* +B起動シーケンス */
    }

    if(u1_s_PwrCtrl_Main_Sts == (U1)PWRCTRL_MAIN_WAKEUP_REQ)
    {
       vd_s_PwrCtrlMainWakeUpSeq();           /* ウェイクアップシーケンス */
    }

    if(u1_s_PwrCtrl_Main_Sts == (U1)PWRCTRL_MAIN_SIPOFF_MCUSTANDBY_REQ)
    {
       vd_s_PwrCtrlMainSipOffMcuStandbySeq(); /* SIP電源OFF&MCUスタンバイシーケンス */
    }

    if(u1_s_PwrCtrl_Main_Sts == (U1)PWRCTRL_MAIN_STANDBY_REQ)
    {
       vd_s_PwrCtrlMainStandbySeq();          /* スタンバイシーケンス */
    }

    if(u1_s_PwrCtrl_Main_Sts == (U1)PWRCTRL_MAIN_FORCEDOFF_REQ)
    {
       vd_s_PwrCtrlMainForcedOffSeq();        /* SIP電源強制OFFシーケンス */
    }

    /* 非冗長電源制御 */
    vd_g_PwrCtrlNoRedunMainFunction();

    /* EtherSW制御要求処理 */
    vd_g_PwrCtrlSipEthReqJudge();

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainSleepJudge
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainSleepJudge( void )
{
/* 暫定対応 start */
    /* 【todo】終了シーケンス開始条件を明確にする */
    U1 u1_t_boot;       /* 開発時のみ使用する、BOOT入力取得(量産時削除予定) */
    U1 u1_t_chk;

    u1_t_boot = (U1)STD_LOW;
    u1_t_chk  = (U1)FALSE;

    u1_t_chk = u1_g_oXCANEcuShtdwnOk();

    if ( u1_t_chk == (U1)TRUE )
    {
        if ( u4_s_PwrCtrl_Main_BusSleep_Time < (U4)PWRCTRL_MAIN_BUSSLEEPTIME )
        {
            u4_s_PwrCtrl_Main_BusSleep_Time++;
        }
    }
    else
    {
        u4_s_PwrCtrl_Main_BusSleep_Time = (U4)0u;
    }

    if ( u4_s_PwrCtrl_Main_BusSleep_Time == (U4)PWRCTRL_MAIN_BUSSLEEPTIME ) /* CANスリープが60sec間継続 */
    {
        /* BOOT入力値取得処理 */
        u1_t_boot = u1_g_PwrCtrl_PinMonitor_GetPinInfo(PWRCTRL_CFG_PRIVATE_KIND_BOOT);

        if ( u1_t_boot == (U1)STD_LOW )                                     /* BOOT=Loを検知 */
        {
            /* ★要検討★処理実行中は要求を受け付けない */
            if ( ( u1_s_PwrCtrl_Main_Sts == (U1)PWRCTRL_MAIN_NO_REQ )
              && ( u1_s_PwrCtrl_Main_BusSleepFlag == (U1)PWRCTRL_COMMON_SYS_PWR_ON ) )
            {
                vd_s_PwrCtrlMainSipOffMcuStandbyReq(); /* 暫定 SIP電源OFF&MCUスタンバイシーケンス要求 */
            }
        }
    }
/* 暫定対応 end */
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainStartSet
  Description   : シーケンス開始処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainStartSet( void )
{
    u1_s_PwrCtrl_Main_SysPwrSts     = (U1)PWRCTRL_MAIN_SYS_STS_INIT;      /* SYS電源：初期状態 */
    u1_s_PwrCtrl_Main_NonRednPwrSts = (U1)PWRCTRL_MAIN_NRD_STS_INIT;      /* 非冗長電源：初期状態 */
    u1_s_PwrCtrl_Main_SipPwrSts     = (U1)PWRCTRL_MAIN_SIP_STS_INIT;      /* SIP電源状態：初期状態 */
    
#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
    /* 異常系確認用RAMの初期化 */
    u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_NON;   /* TP */
    /* 異常系確認用RAMの初期化 */
#endif
    return;

}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainBonSeq(void)
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainBonSeq( void )
{
    U1 u1_t_syson_seq;                                                         /* SYS電源ONシーケンス状態問い合わせ結果 */
    U1 u1_t_sipon_seq;                                                         /* SIP電源ONシーケンス状態問い合わせ結果 */
    U1 u1_t_read_lv;                                                           /* MCU端子状態取得結果 */
    U1 u1_t_foff_req;                                                          /* SIP電源強制OFFシーケンス要求確認結果 */

    u1_t_foff_req = (U1)PWRCTRL_MAIN_FORCEDOFF_STS_INIT;
/* /BU-DET =Hi? */
    if ( u1_s_PwrCtrl_Main_SysPwrSts == (U1)PWRCTRL_MAIN_SYS_STS_BUDET )
    {
        u1_t_read_lv = u1_g_PwrCtrl_PinMonitor_GetPinInfo(PWRCTRL_CFG_PRIVATE_KIND_BU_DET);    /* BU-DET端子の状態を取得 */
        if ( u1_t_read_lv == (U1)MCU_DIO_HIGH )
        {
            /* 低電圧検知と判定してBU断シーケンスを開始する */
            vd_g_PwrCtrlMainBuDetReq();
        }
        
        else{
            /* 低電圧を検知していなければ正常ルートを進める */
            u1_s_PwrCtrl_Main_SysPwrSts = PWRCTRL_MAIN_SYS_STS_INPRC;
        }
    }

    /* SYS電源ON制御 */
    if ( u1_s_PwrCtrl_Main_SysPwrSts == (U1)PWRCTRL_MAIN_SYS_STS_INPRC )
    {
        vd_g_PwrCtrlSysPwrOnMainFunction();

        u1_t_syson_seq = u1_g_PwrCtrlSysGetSts();                              /* SYS電源シーケンス状態問い合わせ */
        if ( u1_t_syson_seq == (U1)TRUE )                                      /* 処理完了 */
        {
            u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_COMP;       /* SYS電源状態：実行中→完了 */
            u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_INPRC;      /* SIP電源状態：初期状態→実行中 */
            vd_g_PwrCtrlSipOnReq();                                            /* SIP電源ON要求(+B ON) */
        }
    }

    /* SIP電源ON処理 */
    if ( u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_INPRC )
    {
        vd_g_PwrCtrlSipMainFunc();                                             /* SIP通常起動制御 */

        u1_t_foff_req  = u1_g_PwrCtrlSipFOffInfo();                            /* SIP電源強制OFFシーケンス要求問い合わせ */
        u1_t_sipon_seq = u1_g_PwrCtrlSipGetSts();                              /* SIP電源シーケンス状態問い合わせ */
        if ( u1_t_sipon_seq == (U1)TRUE )                                      /* 処理完了 */
        {
            u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_CHK_MMSTBY; /* SIP電源状態：実行中→MM_STBY_N=Hi判定中 */
        }
    }

/* MM_STBY_N =Hi?(SOCメインドメインのQNX起動完了の確認) */
    if ( u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_CHK_MMSTBY )
    {
        u1_t_read_lv = u1_g_PwrCtrl_PinMonitor_GetPinInfo(PWRCTRL_CFG_PRIVATE_KIND_MM_STBY_N); /* MM_STBY_N端子の状態を取得 */
#ifndef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF
        if ( u1_t_read_lv == (U1)MCU_DIO_HIGH )
#else
        if (( u1_t_read_lv == (U1)MCU_DIO_HIGH) ||
            (u1_g_PwrCtrl_Main_DbgFailOffFlag == (U1)MCU_DIO_LOW))
#endif
        {
            u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_COMP;       /* SIP電源状態：MM_STBY_N=Hi判定中→完了 */
        }

        else{
            /* MM_STBY_N =Hiチェックを開始してから100秒経過しても完了しない場合 */
            if (u4_s_PwrCtrl_Main_MmStby >= (U4)PWRCTRL_MAIN_TIME_MMSTBY)
            {
                /* 強制OFFシーケンス(SoC異常)要求 */
                u1_t_foff_req = (U1)PWRCTRL_MAIN_FORCEDOFF_STS_SOCERR;
                /* 【todo】異常内容の保存 */
            }
        
            else {
                u4_s_PwrCtrl_Main_MmStby++;
            }
        }

#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_BON_MMSTBY; /* TP */
#endif
    }

    /* 強制OFFシーケンス要求 */
    vd_g_PwrCtrlMainForcedOffReq(u1_t_foff_req);
/* 終了処理 */
    /* ★要検討★：全部が完了したら、要求を落として処理完了状態にする */
    if ( ( u1_s_PwrCtrl_Main_SysPwrSts == (U1)PWRCTRL_MAIN_SYS_STS_COMP )
      && ( u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_COMP ) )
    {
        u1_s_PwrCtrl_Main_Sts          = (U1)PWRCTRL_MAIN_NO_REQ;              /* 処理完了 */
        u1_s_PwrCtrl_Main_BusSleepFlag = (U1)PWRCTRL_COMMON_SYS_PWR_ON;        /* 暫定 */
        
#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_NON;        /* 異常系エラーなし */
#endif
    }

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainWakeUpSeq(void)
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainWakeUpSeq( void )
{
    U1 u1_t_syson_seq;                                                                                     /* SYS電源ONシーケンス状態問い合わせ結果 */
    U1 u1_t_sipon_seq;                                                                                     /* SIPレジューム起動シーケンス状態問い合わせ結果 */
    U1 u1_t_read_lv;                                                                                       /* MCU端子状態取得結果 */
    U1 u1_t_foff_req;                                                                                      /* SIP電源強制OFFシーケンス要求確認結果 */

/* /BU-DET =Hi? */
    if ( u1_s_PwrCtrl_Main_SysPwrSts == (U1)PWRCTRL_MAIN_SYS_STS_BUDET )
    {
        u1_t_read_lv = u1_g_PwrCtrl_PinMonitor_GetPinInfo(PWRCTRL_CFG_PRIVATE_KIND_BU_DET);    /* BU-DET端子の状態を取得 */
        if ( u1_t_read_lv == (U1)MCU_DIO_HIGH )
        {
            /* 低電圧検知と判定してBU断シーケンスを開始する */
            vd_g_PwrCtrlMainBuDetReq();
        }
        
        else{
            /* 低電圧を検知していなければ正常ルートを進める */
            u1_s_PwrCtrl_Main_SysPwrSts = PWRCTRL_MAIN_SYS_STS_INPRC;
        }
    }

    /* 【todo】起動要因を取得する */
    /* 【todo】起動要因の判定を行う */

    /* SYS電源ON制御 */
    if ( u1_s_PwrCtrl_Main_SysPwrSts == (U1)PWRCTRL_MAIN_SYS_STS_INPRC )
    {
        vd_g_PwrCtrlSysPwrOnMainFunction();

        u1_t_syson_seq = u1_g_PwrCtrlSysGetSts();                                                         /* SYS電源シーケンス状態問い合わせ */
        if ( u1_t_syson_seq == (U1)TRUE )                                                                 /* 処理完了 */
        {
/* AOSS_SLEEP_ENTRY_EXIT＝Hi？(SIPがサスペンド状態であることを確認※1度のみ実施) */
            u1_t_read_lv = u1_g_PwrCtrl_PinMonitor_GetPinInfo(PWRCTRL_CFG_PRIVATE_KIND_AOSS_SLP_ENTRY_EXIT); /* AOSS_SLEEP_ENTRY_EXIT端子の状態を取得    */
            if(u1_t_read_lv == (U1)MCU_DIO_HIGH)
            {
                u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_COMP;                              /* SYS電源状態：実行中→完了 */
                u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_INPRC;                             /* SIP電源状態：初期状態→実行中 */
                vd_g_PwrCtrlSipRsmReq();                                                                  /* SIP電源ON要求(WakeUp) */
            }
            else{
               /* 【todo】異常内容保存 */
               /* +B-ONシーケンスのSIP通常起動から開始 */
               vd_s_PwrCtrlMainBonDDconvOnReq();
               
#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
                u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_WAKE_AOSS_HI; /* TP */
#endif
            }
        }
    }

/* SIP電源定期処理 */
    if(u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_INPRC)
    {
        vd_g_PwrCtrlSipMainFunc();                                                                        /* SIP電源 定期処理 */
        u1_t_sipon_seq = u1_g_PwrCtrlSipGetSts();                                                         /* SIP電源シーケンス状態問い合わせ */
        if(u1_t_sipon_seq == (U1)TRUE)                                                                    /* 処理完了 */
        {
            u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_CHK_AOSS;                              /* SIP電源状態：実行中→AOSS_SLEEP_ENTRY_EXIT=Low判定中 */
        }
    }

/* AOSS_SLEEP_ENTRY_EXIT=Lo?(PMICからのSIP電源レジューム完了確認) */
    if(u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_CHK_AOSS)
    {
        u1_t_read_lv = u1_g_PwrCtrl_PinMonitor_GetPinInfo(PWRCTRL_CFG_PRIVATE_KIND_AOSS_SLP_ENTRY_EXIT);   /* AOSS_SLEEP_ENTRY_EXIT端子の状態を取得    */
#ifndef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF
        if(u1_t_read_lv == (U1)MCU_DIO_LOW)
#else
        if((u1_t_read_lv == (U1)MCU_DIO_LOW) ||
           (u1_g_PwrCtrl_Main_DbgFailOffFlag == (U1)MCU_DIO_LOW))
#endif
        {
            u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_CHK_MMSTBY;                            /* SIP電源状態：AOSS_SLEEP_ENTRY_EXIT=Low判定中→MM_STBY_N=Hi判定中 */

            /* 【todo】5-9. PM_PSAIL_ERR_N監視処理開始 */
            /* 【todo】5-10. PMA_PS_HOLD監視処理開始 */
            /* 【todo】4.0版参照 5-12-1. PGOOD_ASIL_VB監視処理開始 4.0版参照 */
            /* 【todo】3.0版参照 5-7. SAIL UART Message監視開始 3.0版参照 */
        }

        else{
            /* AOSS_SLEEP_ENTRY_EXIT=Loチェックを開始してから5秒経過しても完了しない場合 */
            if (u4_s_PwrCtrl_Main_Aoss >= (U4)PWRCTRL_MAIN_TIME_AOSS)
            {
                /* 強制OFFシーケンス(PMIC異常)要求 */
                u1_t_foff_req = (U1)PWRCTRL_MAIN_FORCEDOFF_STS_PMICERR;
                /* 【todo】異常内容の保存 */
            }
        
            else {
                u4_s_PwrCtrl_Main_Aoss++;
            }
        }

#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_WAKE_AOSS_LO; /* TP */
#endif
    }
    
    /* 【todo】4.0版参照 SAIL-ERR[2:1] == 01かどうかのチェック 4.0版参照 */
    

/* MM_STBY_N =Hi?(SOCメインドメインのQNX起動完了の確認) */
    if (u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_CHK_MMSTBY)
    {
        u1_t_read_lv = u1_g_PwrCtrl_PinMonitor_GetPinInfo(PWRCTRL_CFG_PRIVATE_KIND_MM_STBY_N);             /* MM_STBY_N端子の状態を取得 */
#ifndef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF
        if(u1_t_read_lv == (U1)MCU_DIO_HIGH)
#else
        if((u1_t_read_lv == (U1)MCU_DIO_HIGH) ||
           (u1_g_PwrCtrl_Main_DbgFailOffFlag == (U1)MCU_DIO_LOW))
#endif
        {
            u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_COMP;                                  /* SIP電源状態：MM_STBY_N=Hi判定中→完了 */
            
            /* 【todo】4.0版参照 Wait time (MIN)5秒、(TYP)6秒、(MAX)20秒 4.0版参照 */
            /* 【todo】4.0版参照 5-7. SAIL UART Message監視開始 4.0版参照 */
        }

        else{
            /* MM_STBY_N =Hiチェックを開始してから100秒経過しても完了しない場合 */
            if (u4_s_PwrCtrl_Main_MmStby >= (U4)PWRCTRL_MAIN_TIME_MMSTBY)
            {
                /* 強制OFFシーケンス(SoC異常)要求 */
                u1_t_foff_req = (U1)PWRCTRL_MAIN_FORCEDOFF_STS_SOCERR;
                /* 【todo】異常内容の保存 */
            }
        
            else {
                u4_s_PwrCtrl_Main_MmStby++;
            }
        }

#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_WAKE_MMSTBY; /* TP */
#endif
    }

    /* 強制OFFシーケンス要求 */
    vd_g_PwrCtrlMainForcedOffReq(u1_t_foff_req);

/* 終了処理 */
    /* ★要検討★：全部が完了したら、要求を落として処理完了状態にする */
    if( (u1_s_PwrCtrl_Main_SysPwrSts == (U1)PWRCTRL_MAIN_SYS_STS_COMP)
     && (u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_COMP))
    {
        u1_s_PwrCtrl_Main_Sts = (U1)PWRCTRL_MAIN_NO_REQ;                                                  /* 処理完了 */
#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_NON;                                   /* 異常系エラーなし */
#endif
    }

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainSipOffMcuStandbySeq(void)
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainSipOffMcuStandbySeq( void )
{
    U1 u1_t_sipoff_seq;                                                      /* SIP電源OFFシーケンス状態問い合わせ結果 */
    U1 u1_t_foff_req;                                                        /* SIP電源強制OFFシーケンス要求確認結果 */
    U1 u1_t_nrdoff_seq;                                                      /* 非冗長電源OFFシーケンス状態問い合わせ結果 */
    U1 u1_t_sysoff_seq;                                                      /* SYS電源OFFシーケンス状態問い合わせ結果 */
    U1 u1_t_devoff_seq;                                                      /* SYS系デバイス終了状態問い合わせ結果 */

    /* SIP電源OFF処理 */
    if ( u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_INPRC )
    {
        vd_g_PwrCtrlSipMainFunc();                                           /* SIP電源 定期処理 */

        u1_t_foff_req  = u1_g_PwrCtrlSipFOffInfo();                          /* SIP電源強制OFFシーケンス要求問い合わせ */
        
        /* 強制OFFシーケンス要求 */
        vd_g_PwrCtrlMainForcedOffReq(u1_t_foff_req);

        u1_t_sipoff_seq = u1_g_PwrCtrlSipGetSts();                           /* SIP電源シーケンス状態問い合わせ */
        if ( u1_t_sipoff_seq == (U1)TRUE )                                   /* 処理完了 */
        {
            u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_COMP;     /* SIP電源状態：実行中→完了 */
            u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_WAITDEV;  /* SYS電源状態：開始→SYSデバイス終了待ち */
        }
    }

    /* SYS系デバイス終了状態問い合わせ */
    if ( u1_s_PwrCtrl_Main_SysPwrSts == (U1)PWRCTRL_MAIN_SYS_STS_WAITDEV )
    {
        u1_t_devoff_seq = u1_g_PwrCtrlSysShtdwnGetSts();                     /* SYS系デバイス終了状態問い合わせ */
        if ( u1_t_devoff_seq == (U1)TRUE )                                   /* 処理完了 */
        {
            u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_INPRC;    /* SYS電源状態:SYSデバイス終了待ち→実行中 */
            /* SYS電源OFF要求 */
            vd_g_PwrCtrlSysPwrOffStart();                                    /* SYS電源OFF要求 */
        }
    }

    /* SYS電源OFF制御 */
    if ( u1_s_PwrCtrl_Main_SysPwrSts == (U1)PWRCTRL_MAIN_SYS_STS_INPRC )     /* SYS電源状態:実行中 */
    {
        vd_g_PwrCtrlSysPwrOffMainFunction();
        u1_t_sysoff_seq = u1_g_PwrCtrlSysGetSts();                           /* SYS電源シーケンス状態問い合わせ */
        if ( u1_t_sysoff_seq == (U1)TRUE )                                   /* 処理完了 */
        {
            u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_COMP;     /* SYS電源状態：実行中→完了 */
        }
    }

    /* 非冗長電源OFFシーケンス状態問い合わせ */
    if ( u1_s_PwrCtrl_Main_NonRednPwrSts == (U1)PWRCTRL_MAIN_NRD_STS_INPRC )
    {
        u1_t_nrdoff_seq = u1_g_PwrCtrlNoRedunGetSts();                       /* 非冗長電源シーケンス状態問い合わせ */
        if ( u1_t_nrdoff_seq == (U1)TRUE )                                   /* 処理完了 */
        {
            u1_s_PwrCtrl_Main_NonRednPwrSts = (U1)PWRCTRL_MAIN_NRD_STS_COMP; /* 非冗長電源状態：実行中→完了 */
        }
    }

    /* 終了処理 */
    /* ★要検討★：全部が完了したら、要求を落として処理完了状態にする */
    if ( ( u1_s_PwrCtrl_Main_SysPwrSts     == (U1)PWRCTRL_MAIN_SYS_STS_COMP )
      && ( u1_s_PwrCtrl_Main_NonRednPwrSts == (U1)PWRCTRL_MAIN_NRD_STS_COMP )
      && ( u1_s_PwrCtrl_Main_SipPwrSts     == (U1)PWRCTRL_MAIN_SIP_STS_COMP ))
    {
        u1_s_PwrCtrl_Main_Sts          = (U1)PWRCTRL_MAIN_NO_REQ;            /* 処理完了 */
        u1_s_PwrCtrl_Main_ShtdwnOkFlag = (U1)PWRCTRL_COMMON_SYS_PWR_ON;      /* 暫定 */
        /* MCUの起動完了フラグをOFFに設定 */
        u1_s_PwrCtrl_Main_WakeUpFlag   = (U1)FALSE;

        
#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_NON;      /* 異常系エラーなし */
#endif
    }

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainStandbySeq(void)
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainStandbySeq( void )
{
    U1 u1_t_sipstb_seq;                                                      /* SIPスタンバイシーケンス状態問い合わせ結果 */
    U1 u1_t_foff_req;                                                        /* SIP電源強制OFFシーケンス要求確認結果 */
    U1 u1_t_nrdoff_seq;                                                      /* 非冗長電源OFFシーケンス状態問い合わせ結果 */
    U1 u1_t_sysoff_seq;                                                      /* SYS電源OFFシーケンス状態問い合わせ結果 */
    U1 u1_t_devoff_seq;                                                      /* SYS系デバイス終了状態問い合わせ結果 */

    /* SIP電源OFF */
    if(u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_INPRC)
    {
        vd_g_PwrCtrlSipMainFunc();                                           /* SIP電源 定期処理 */

        u1_t_foff_req  = u1_g_PwrCtrlSipFOffInfo();                          /* SIP電源強制OFFシーケンス要求問い合わせ */
        
        /* 強制OFFシーケンス要求 */
        vd_g_PwrCtrlMainForcedOffReq(u1_t_foff_req);

        u1_t_sipstb_seq = u1_g_PwrCtrlSipGetSts();                           /* SIP電源シーケンス状態問い合わせ */
        if(u1_t_sipstb_seq == (U1)TRUE)                                      /* 処理完了 */
        {
            u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_COMP;     /* SIP電源状態：実行中→完了 */
            u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_WAITDEV;  /* SYS電源状態：開始→SYSデバイス終了待ち */
        }
    }

    /* SYS系デバイス終了状態問い合わせ */
    if(u1_s_PwrCtrl_Main_SysPwrSts == (U1)PWRCTRL_MAIN_SYS_STS_WAITDEV)
    {
        u1_t_devoff_seq = u1_g_PwrCtrlSysShtdwnGetSts();                     /* SYS系デバイス終了状態問い合わせ */
        if(u1_t_devoff_seq ==(U1)TRUE)
        {                                                                    /* 処理完了 */
            u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_INPRC;    /* SYS電源状態:SYSデバイス終了待ち→実行中 */
            /* SYS電源OFF要求 */
            vd_g_PwrCtrlSysPwrOffStart();                                    /* SYS電源OFF要求 */
        }
    }

    /* SYS電源OFF制御 */
    if ( u1_s_PwrCtrl_Main_SysPwrSts == (U1)PWRCTRL_MAIN_SYS_STS_INPRC )     /* SYS電源状態:実行中 */
    {
        vd_g_PwrCtrlSysPwrOffMainFunction();
        u1_t_sysoff_seq = u1_g_PwrCtrlSysGetSts();                           /* SYS電源シーケンス状態問い合わせ */
        if(u1_t_sysoff_seq == (U1)TRUE)                                      /* 処理完了 */
        {
            u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_COMP;     /* SYS電源状態：実行中→完了 */
        }
    }
    

    /* 非冗長電源OFFシーケンス状態問い合わせ */
    if(u1_s_PwrCtrl_Main_NonRednPwrSts == (U1)PWRCTRL_MAIN_NRD_STS_INPRC)
    {
        u1_t_nrdoff_seq = u1_g_PwrCtrlNoRedunGetSts();                       /* 非冗長電源シーケンス状態問い合わせ */
        if(u1_t_nrdoff_seq == (U1)TRUE)                                      /* 処理完了 */
        {
            u1_s_PwrCtrl_Main_NonRednPwrSts = (U1)PWRCTRL_MAIN_NRD_STS_COMP; /* 非冗長電源状態：実行中→完了 */
        }
    }

    /* ★要検討★：全部が完了したら、要求を落として処理完了状態にする */
    if( (u1_s_PwrCtrl_Main_SysPwrSts     == (U1)PWRCTRL_MAIN_SYS_STS_COMP)
     && (u1_s_PwrCtrl_Main_NonRednPwrSts == (U1)PWRCTRL_MAIN_NRD_STS_COMP)
     && (u1_s_PwrCtrl_Main_SipPwrSts     == (U1)PWRCTRL_MAIN_SIP_STS_COMP))
     {
        u1_s_PwrCtrl_Main_Sts          = (U1)PWRCTRL_MAIN_NO_REQ;            /* 処理完了 */
        u1_s_PwrCtrl_Main_ShtdwnOkFlag = (U1)PWRCTRL_COMMON_SYS_PWR_ON;      /* 暫定 */
        /* MCUの起動完了フラグをOFFに設定 */
        u1_s_PwrCtrl_Main_WakeUpFlag = (U1)FALSE;

#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_NON;      /* 異常系エラーなし */
#endif 
     }
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainForcedOffSeq(void)
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainForcedOffSeq( void )
{
    U1 u1_t_sipstb_seq;                                                /* SIP電源強制OFFシーケンス状態問い合わせ結果 */
    U1 u1_t_sipfoff_seq;                                               /* SIP入力DDコン電源OFF処理実施要否取得結果 */
    U1 u1_t_wake_factor;                                               /* 起動要因 */
    U1 u1_t_boot;                                                      /* 暫定 */
    
    /* SIP電源強制OFF処理開始 */
    if(u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_INPRC){
        vd_g_PwrCtrlSipMainFunc();                                     /* SIP電源 定期処理 */

        u1_t_sipstb_seq = u1_g_PwrCtrlSipGetSts();                     /* SIP電源シーケンス状態問い合わせ */
        if(u1_t_sipstb_seq == (U1)TRUE)                                /* 処理完了 */
        {
          u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_COMP;
        }
    }
    
    /* SIP電源強制OFFシーケンス実施後動作の決定 */
    if(u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_COMP){

        /* 【todo】起動要因の取得 */
        /* 暫定対応(CANスリープ要否の確認、Bootチェック) */
        u1_t_wake_factor = u1_g_oXCANEcuShtdwnOk();
        u1_t_boot = u1_g_PwrCtrl_PinMonitor_GetPinInfo(PWRCTRL_CFG_PRIVATE_KIND_BOOT);
        
        /* 【todo】起動要因が成立しているかの判定 */
        if((u1_t_wake_factor == (U1)FALSE) ||
           (u1_t_boot == (U1)MCU_DIO_HIGH)){
            /* SIP入力DDコン電源OFF処理実施要否を取得 */
            u1_t_sipfoff_seq = u1_g_PwrCtrlSipFOffGetSts();
        
            if(u1_t_sipfoff_seq == (U1)PWRCTRL_SIP_FOFF_DDCONV_ON){
               /* SIP入力DDコン電源OFF処理実施 */
               u1_s_PwrCtrl_Main_Sts = (U1)PWRCTRL_MAIN_NO_REQ;        /* 処理完了 */
               vd_s_PwrCtrlMainBonDDconvOnReq();                       /* +B起動シーケンス SIP用DDコン起動処理開始要求 */
             }
             
            else{
               /* SIP入力DDコン電源OFF処理未実施 */
               u1_s_PwrCtrl_Main_Sts = (U1)PWRCTRL_MAIN_NO_REQ;        /* 処理完了 */
               vd_s_PwrCtrlMainBonPwrOnReq();                          /* +B起動シーケンス SIP電源のみ起動処理開始要求 */
            }
        }
        /* 【todo】起動要因非成立時 */
        else{
           u1_s_PwrCtrl_Main_Sts = (U1)PWRCTRL_MAIN_NO_REQ;            /* 処理完了 */
           vd_s_PwrCtrlMainSipOffMcuStandbySysDevReq();                /* SIP電源OFF&MCUスタンバイシーケンス SYS系電源OFF、MCUスタンバイ処理開始要求 */
        }
    }
    
    return;
}

/****************************************************************************/
/* Service API                                                              */
/****************************************************************************/
/**** End of File ***********************************************************/
