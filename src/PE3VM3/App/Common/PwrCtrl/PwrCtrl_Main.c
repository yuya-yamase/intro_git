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
#define PWRCTRL_MAIN_SIP_STS_CHK_SAILERR (0x05U) /* SAILERR判定中 */
#define PWRCTRL_MAIN_SIP_STS_COMP       (0xFFU)  /* 完了 */

/* SIP強制電源OFF状態 */
#define PWRCTRL_MAIN_FORCEDOFF_STS_INIT    (0x00U)  /* 初期状態 */
#define PWRCTRL_MAIN_FORCEDOFF_STS_SOCERR  (0x01U)  /* SOC異常実行中 */
#define PWRCTRL_MAIN_FORCEDOFF_STS_PMICERR (0x02U)  /* PMIC異常実行中 */
#define PWRCTRL_MAIN_FORCEDOFF_STS_DDERR   (0x03U)  /* DDコンOFF実行中 */

/* スタンバイ処理中の起動トリガ処理遷移元 */
#define PWRCTRL_MAIN_STBYCANCEL_SIPOFF  (0x00U)  /* SIP電源強制OFF処理開始 */
#define PWRCTRL_MAIN_STBYCANCEL_OTHER   (0x01U)  /* その他 */

/* スタンバイ判定可否 */
#define PWRCTRL_MAIN_STBYJDG_OK         (0x00U)  /* スタンバイ判定可   */
#define PWRCTRL_MAIN_STBYJDG_NG         (0x01U)  /* スタンバイ判定不可 */

/* Dio端子監視結果 */
#define PWRCTRL_MAIN_DIO_READ_CHK_INIT  (0x00U)  /* 状態監視初期状態 */
#define PWRCTRL_MAIN_DIO_READ_CHK_OK    (0x01U)  /* 指定時間内に正常応答 */
#define PWRCTRL_MAIN_DIO_READ_CHK_NG    (0xFFU)  /* 時間超過or異常応答 */

#define PWRCTRL_MAIN_TIME_INIT          (0U)
#define PWRCTRL_MAIN_TIME_MMSTBY        (100000U / PWRCTRL_CFG_TASK_TIME)
#define PWRCTRL_MAIN_TIME_AOSS          (5000U / PWRCTRL_CFG_TASK_TIME)
#define PWRCTRL_MAIN_TIME_SAILERR       (5000U / PWRCTRL_CFG_TASK_TIME)

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
static void vd_s_PwrCtrlMainStandbyReq( void );
static void vd_s_PwrCtrlMainForcedOffReq( const U1 u1_s_evtype );
static void vd_s_PwrCtrlMainStbyCancelSt1Req( void );
static void vd_s_PwrCtrlMainStbyCancelSt2Req( const U1 u1_a_pre_seq );
static void vd_s_PwrCtrlMainPmPsailFsReq( void );
static void vd_s_PwrCtrlMainPmaPsFsReq( void );
static void vd_s_PwrCtrlMainObserveFsJudge( void );
static void vd_s_PwrCtrlMainOnOffJudge( void );

/* シーケンス動作用処理 */
static void vd_s_PwrCtrlMainBonSeq( void );
static void vd_s_PwrCtrlMainWakeUpSeq( void );
static void vd_s_PwrCtrlMainSipOffMcuStandbySeq( void );
static void vd_s_PwrCtrlMainSipOffMcuStandbySipOffStep( void );
static void vd_s_PwrCtrlMainSipOffMcuStandbySysDevOffStep( void );
static void vd_s_PwrCtrlMainSipOffMcuStandbySysOffStep( void );
static void vd_s_PwrCtrlMainSipOffMcuStandbyNrdOffStep( void );
static void vd_s_PwrCtrlMainStandbySeq( void );
static void vd_s_PwrCtrlMainStandbySipStby( void );
static void vd_s_PwrCtrlMainStandbySysDevOff( void );
static void vd_s_PwrCtrlMainStandbySysOff( void );
static void vd_s_PwrCtrlMainStandbyNrdOff( void );
static void vd_s_PwrCtrlMainForcedOffSeq( void );
static void vd_s_PwrCtrlMainStbyCancelSt1Seq( void );
static void vd_s_PwrCtrlMainStbyCancelSt2Seq( void );
static void vd_s_PwrCtrlMainPmPsailFsSeq( void );
static void vd_s_PwrCtrlMainPmaPsFsSeq( void );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
static U1  u1_s_PwrCtrl_Main_Sts;                         /* 電源制御状態   */
static U1  u1_s_PwrCtrl_Main_SysPwrSts;                   /* SYS電源状態    */
static U1  u1_s_PwrCtrl_Main_NonRednPwrSts;               /* 非冗長電源状態 */
static U1  u1_s_PwrCtrl_Main_SipPwrSts;                   /* SIP電源状態    */

static U1  u1_s_PwrCtrl_Main_ShtdwnOkFlag;
static U1  u1_s_PwrCtrl_Main_StbyJdgFlag;
static U1  u1_s_PwrCtrl_Main_SysPwrInfo;

static U4  u4_s_PwrCtrl_Main_MmStby;
static U4  u4_s_PwrCtrl_Main_Aoss;
static U4  u4_s_PwrCtrl_Main_SailErr;

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
    /* MCUウェイクアップ中は常にTRUE */
    return( (U1)TRUE );
}
/*****************************************************************************
  Function      : u1_g_PwrCtrlMainSysPwrInfo
  Description   : SYS電源制御実施状態通知処理
  param[in/out] : none
  return        : FALSE(0) SYS電源OFF制御開始
                  TRUE (1) SYS電源ON制御完了
  Note          : PGOOD_ASIL_VB端子モニタ監視条件用
*****************************************************************************/
U1 u1_g_PwrCtrlMainSysPwrInfo( void )
{
    return( u1_s_PwrCtrl_Main_SysPwrInfo );
}
/*****************************************************************************
  Function      : vd_g_PwrCtrlMainProhibitSleep
  Description   : VM3スリープ禁止許可設定用処理
  param[in/out] : [in] u1_a_ProhibitSleep スリープ禁止/許可
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlMainProhibitSleep( const U1 u1_a_ProhibitSleep )
{
    /* 監視機能に通知 */
    vd_g_PwrCtrlObserveVm3StbyInfo(u1_a_ProhibitSleep);

    return;
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
    
#ifdef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF
    u1_g_PwrCtrl_Main_DbgFailOffFlag = (U1)MCU_DIO_INVALID;
#endif

    vd_s_PwrCtrlMainStartSet();
    /* SYS電源制御 初期化処理 */
    vd_g_PwrCtrlSysInit();
    /* 非冗長電源制御 初期化処理 */
    vd_g_PwrCtrlNoRedunInit();

    u1_s_PwrCtrl_Main_ShtdwnOkFlag = (U1)PWRCTRL_COMMON_SYS_PWR_OFF;
    u1_s_PwrCtrl_Main_StbyJdgFlag  = (U1)PWRCTRL_MAIN_STBYJDG_NG;    /* スタンバイ判定不可 */
    u1_s_PwrCtrl_Main_SysPwrInfo   = (U1)FALSE;

    vd_g_PwrCtrlSipBonInit();                                        /* SIP電源状態+B初期化要求 */
    vd_g_PwrCtrlSysPwrOnStart();
    vd_g_PwrCtrlNoRedunPwrOnStart();

    /* +B-ONシーケンス実施要求 */
    u1_s_PwrCtrl_Main_Sts       = (U1)PWRCTRL_MAIN_BON_REQ;
    u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_INPRC;    /* SYS電源：実行中 */
    u4_s_PwrCtrl_Main_Aoss      = (U4)PWRCTRL_MAIN_TIME_INIT;
    u4_s_PwrCtrl_Main_SailErr   = (U4)PWRCTRL_MAIN_TIME_INIT;
    u4_s_PwrCtrl_Main_MmStby    = (U4)PWRCTRL_MAIN_TIME_INIT;

    /* 監視処理初期化 */
    vd_g_PwrCtrlObserveInit();

    /* VM間通信処理初期化 */
    vd_g_PwrCtrlComBonInit();

    /* PGOOD_VB監視 開始 */
    vd_g_PwrCtrlObservePgdVbReq((U1)PWRCTRL_OBSERVE_ON);

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

#ifdef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF 
    u1_g_PwrCtrl_Main_DbgFailOffFlag = (U1)MCU_DIO_INVALID;
#endif

    vd_s_PwrCtrlMainStartSet();
    /* SYS電源制御 初期化処理 */
    vd_g_PwrCtrlSysInit();
    /* 非冗長電源制御 初期化処理 */
    vd_g_PwrCtrlNoRedunInit();

    u1_s_PwrCtrl_Main_ShtdwnOkFlag = (U1)PWRCTRL_COMMON_SYS_PWR_OFF;
    u1_s_PwrCtrl_Main_StbyJdgFlag  = (U1)PWRCTRL_MAIN_STBYJDG_NG;    /* スタンバイ判定不可 */
    u1_s_PwrCtrl_Main_SysPwrInfo   = (U1)FALSE;

    vd_g_PwrCtrlSipWkupInit();                                       /* SIP電源状態Wakeup初期化要求 */
    vd_g_PwrCtrlSysPwrOnStart();
    vd_g_PwrCtrlNoRedunPwrOnStart();

    /* ウェイクアップシーケンス実施要求 */
    u1_s_PwrCtrl_Main_Sts       = (U1)PWRCTRL_MAIN_WAKEUP_REQ;
    u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_INPRC;    /* SYS電源：実行中 */
    u4_s_PwrCtrl_Main_Aoss      = (U4)PWRCTRL_MAIN_TIME_INIT;
    u4_s_PwrCtrl_Main_SailErr   = (U4)PWRCTRL_MAIN_TIME_INIT;
    u4_s_PwrCtrl_Main_MmStby    = (U4)PWRCTRL_MAIN_TIME_INIT;

    /* 監視処理初期化 */
    vd_g_PwrCtrlObserveInit();

    /* VM間通信処理初期化 */
    vd_g_PwrCtrlComWkupInit();

    /* PGOOD_VB監視 開始 */
    vd_g_PwrCtrlObservePgdVbReq((U1)PWRCTRL_OBSERVE_ON);

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

    u1_s_PwrCtrl_Main_StbyJdgFlag   = (U1)PWRCTRL_MAIN_STBYJDG_NG;    /* スタンバイ判定不可 */
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

    u1_s_PwrCtrl_Main_StbyJdgFlag   = (U1)PWRCTRL_MAIN_STBYJDG_NG;      /* スタンバイ判定不可 */
    u1_s_PwrCtrl_Main_SipPwrSts     = (U1)PWRCTRL_MAIN_SIP_STS_COMP;    /* SIP電源状態：実行中→完了 */
    u1_s_PwrCtrl_Main_SysPwrSts     = (U1)PWRCTRL_MAIN_SYS_STS_WAITDEV; /* SYS電源状態：開始→SYSデバイス終了待ち */
    u1_s_PwrCtrl_Main_NonRednPwrSts = (U1)PWRCTRL_MAIN_NRD_STS_INPRC;   /* 非冗長電源状態:開始→実行中 */
    vd_g_PwrCtrlNoRedunPwrOffStart();                                   /* 非冗長電源OFF要求 */

}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainStandbyReq
  Description   : スタンバイシーケンス要求
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainStandbyReq( void )
{
    u1_s_PwrCtrl_Main_Sts           = (U1)PWRCTRL_MAIN_STANDBY_REQ;
    vd_s_PwrCtrlMainStartSet();
    EthSwt_SWIC_PowerOff();                                             /* EtherSW終了要求 */

    u1_s_PwrCtrl_Main_StbyJdgFlag   = (U1)PWRCTRL_MAIN_STBYJDG_NG;    /* スタンバイ判定不可 */
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
  Function      : vd_s_PwrCtrlMainForcedOffReq
  Description   : SIP電源強制OFFシーケンス要求
  param[in/out] : [ in ] u1_s_evtype 発生したイベントタイプ
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainForcedOffReq( const U1 u1_s_evtype )
{
    switch(u1_s_evtype){
       case (U1)PWRCTRL_MAIN_FORCEDOFF_STS_SOCERR:
        u1_s_PwrCtrl_Main_Sts       = (U1)PWRCTRL_MAIN_FORCEDOFF_REQ;
        u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_INPRC;    /* SIP電源状態：実行中 */
        vd_g_PwrCtrlObservePsailReq((U1)PWRCTRL_OBSERVE_OFF);            /* PM_PSAIL_ERR_N監視 終了 */
        vd_g_PwrCtrlObservePsHoldReq((U1)PWRCTRL_OBSERVE_OFF);           /* PMA_PS_HOLD監視 終了 */
        vd_g_PwrCtrlSipForcedOffSTEP1Req();                              /* SIP強制OFFシーケンス STEP1から開始 */
        vd_g_PwrCtrlComTxSetPwrErr((U1)PWRCTRL_COM_PWRERR_FOFF_SOCERR);  /* 異常検知(SIP電源強制OFF:SOC異常系) */
        break;

       case (U1)PWRCTRL_MAIN_FORCEDOFF_STS_PMICERR:
        u1_s_PwrCtrl_Main_Sts       = (U1)PWRCTRL_MAIN_FORCEDOFF_REQ;
        u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_INPRC;    /* SIP電源状態：実行中 */
        vd_g_PwrCtrlObservePsailReq((U1)PWRCTRL_OBSERVE_OFF);            /* PM_PSAIL_ERR_N監視 終了 */
        vd_g_PwrCtrlObservePsHoldReq((U1)PWRCTRL_OBSERVE_OFF);           /* PMA_PS_HOLD監視 終了 */
        vd_g_PwrCtrlSipForcedOffSTEP2Req();                              /* SIP強制OFFシーケンス STEP2から開始 */
        vd_g_PwrCtrlComTxSetPwrErr((U1)PWRCTRL_COM_PWRERR_FOFF_PMICERR); /* 異常検知(SIP電源強制OFF:SOC異常系) */
        break;

       case (U1)PWRCTRL_MAIN_FORCEDOFF_STS_DDERR:
        u1_s_PwrCtrl_Main_Sts       = (U1)PWRCTRL_MAIN_FORCEDOFF_REQ;
        u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_INPRC;    /* SIP電源状態：実行中 */
        vd_g_PwrCtrlObservePsailReq((U1)PWRCTRL_OBSERVE_OFF);            /* PM_PSAIL_ERR_N監視 終了 */
        vd_g_PwrCtrlObservePsHoldReq((U1)PWRCTRL_OBSERVE_OFF);           /* PMA_PS_HOLD監視 終了 */
        vd_g_PwrCtrlSipForcedOffSTEP4Req();                              /* SIP強制OFFシーケンス STEP4から開始 */
        vd_g_PwrCtrlComTxSetPwrErr((U1)PWRCTRL_COM_PWRERR_FOFF_DDERR);   /* 異常検知(SIP電源強制OFF:PMIC異常系/DDコンOFF) */
        break;

       default:
        /* 何もしない */
        break;
    }
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainStbyCancelSt1Req
  Description   : スタンバイ処理中の起動トリガ時シーケンス要求(SIP電源強制OFF処理開始)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainStbyCancelSt1Req( void )
{
    /* スタンバイ処理中の起動トリガ時シーケンス要求(SIP電源強制OFF処理開始) */
    u1_s_PwrCtrl_Main_Sts       = (U1)PWRCTRL_MAIN_STBYCANCELST1_REQ;
    u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_INPRC;   /* SIP電源状態：実行中 */
    u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_COMP;    /* SYS電源状態：完了 */
    vd_g_PwrCtrlSipStandbyCancelSTEP1Req();                         /* SIP電源強制OFF処理から開始 */
    vd_g_PwrCtrlObservePsailReq((U1)PWRCTRL_OBSERVE_OFF);           /* PM_PSAIL_ERR_N監視 終了 */
    vd_g_PwrCtrlObservePsHoldReq((U1)PWRCTRL_OBSERVE_OFF);          /* PMA_PS_HOLD監視 終了 */

    vd_g_PwrCtrlComTxSetPwrOn((U1)PWRCTRL_COM_PWRON_CANCEL_START);  /* SIP電源再起動通知設定 */

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainStbyCancelSt2Req
  Description   : スタンバイ処理中の起動トリガ時シーケンス要求(SYS系電源ON、SIP電源ON)
  param[in/out] : [ in ] u1_a_pre_seq 遷移元処理
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainStbyCancelSt2Req( const U1 u1_a_pre_seq )
{
    vd_g_PwrCtrlSysInit();              /* SYS電源制御初期化処理 */
    vd_g_PwrCtrlNoRedunRestartInit();   /* 非冗長電源制御再起動時初期化処理 */

    u1_s_PwrCtrl_Main_ShtdwnOkFlag  = (U1)PWRCTRL_COMMON_SYS_PWR_OFF;

    vd_g_PwrCtrlSysPwrOnStart();        /* SYS電源制御ON要求 */
    vd_g_PwrCtrlNoRedunPwrOnStart();    /* 非冗長電源制御ON要求 */

    /* スタンバイ処理中の起動トリガ時シーケンス要求(SYS系電源ON、SIP電源ON) */
    u1_s_PwrCtrl_Main_Sts           = (U1)PWRCTRL_MAIN_STBYCANCELST2_REQ;
    u1_s_PwrCtrl_Main_SipPwrSts     = (U1)PWRCTRL_MAIN_SIP_STS_COMP;    /* SIP電源状態：完了 */
    u1_s_PwrCtrl_Main_SysPwrSts     = (U1)PWRCTRL_MAIN_SYS_STS_INPRC;   /* SYS電源状態：SYS電源実行状態 */
    u1_s_PwrCtrl_Main_NonRednPwrSts = (U1)PWRCTRL_MAIN_NRD_STS_INIT;    /* 非冗長電源：初期状態 */
    vd_g_PwrCtrlObservePsailReq((U1)PWRCTRL_OBSERVE_OFF);               /* PM_PSAIL_ERR_N監視 終了 */
    vd_g_PwrCtrlObservePsHoldReq((U1)PWRCTRL_OBSERVE_OFF);              /* PMA_PS_HOLD監視 終了 */

    /* スタンバイ処理中の起動トリガ時シーケンス要求(SIP電源強制OFF処理開始)以外 */
    if(u1_a_pre_seq != (U1)PWRCTRL_MAIN_STBYCANCEL_SIPOFF)
    {
        vd_g_PwrCtrlSipSetDDConvOff((U1)PWRCTRL_SIP_FOFF_DDCONV_ON);    /* 他シーケンスからの遷移時は実施状態を設定 */
    }

    vd_g_PwrCtrlComTxSetPwrOn((U1)PWRCTRL_COM_PWRON_CANCEL_TO_ON);  /* SIP電源再起動通知設定 */

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainPmPsailFsReq
  Description   : PM_PSAIL_ERR_N監視フェールセーフ要求
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainPmPsailFsReq( void )
{
    u1_s_PwrCtrl_Main_Sts = (U1)PWRCTRL_MAIN_PMPSAIL_FS_REQ;        /* 電源制御状態：PM_PSAIL_ERR_N監視(フェールセーフ) */
    u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_INPRC;   /* SIP電源状態：実行中 */
    u1_s_PwrCtrl_Main_StbyJdgFlag  = (U1)PWRCTRL_MAIN_STBYJDG_NG;   /* スタンバイ判定不可 */
    vd_g_PwrCtrlSipPmPsailFsReq();                                  /* SIPにPM_PSAIL_ERR_N監視フェールセーフ処理要求をする */

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainPmaPsFsReq
  Description   : PMA_PS_HOLD監視フェールセーフ要求
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainPmaPsFsReq( void )
{
    u1_s_PwrCtrl_Main_Sts = (U1)PWRCTRL_MAIN_PMAPS_FS_REQ;          /* 電源制御状態：PMA_PS_HOLD監視(フェールセーフ) */
    u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_INPRC;   /* SIP電源状態：実行中 */
    u1_s_PwrCtrl_Main_StbyJdgFlag  = (U1)PWRCTRL_MAIN_STBYJDG_NG;   /* スタンバイ判定不可 */
    vd_g_PwrCtrlSipPmaPsFsReq();                                    /* SIPにPMA_PS_HOLD監視フェールセーフ処理要求をする */

    return;
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
    /* VM間通信受信定期処理 */
    vd_g_PwrCtrlComRxTask();

    /* VM間通信送信データクリア処理 */
    vd_g_PwrCtrlComTxClr();

    /* 端子モニタ定期処理 */
    vd_g_PwrCtrlPinMonitorMainFunc();

    /* 監視定期処理 */
    vd_g_PwrCtrlObserveMainFunc();

    /* 監視制御フェールセーフ判定 */
    vd_s_PwrCtrlMainObserveFsJudge();

    /* スタンバイ/スタンバイ中断(再起動)開始判定 */
    vd_s_PwrCtrlMainOnOffJudge();

    u1_g_PwrCtrl_Main_DbgFailOffFlag = u1_g_PwrCtrl_PinMonitor_GetPinInfo((U1)PWRCTRL_CFG_PRIVATE_KIND_DBG_FAIL_OFF);    /* DBG-FAIL-OFF端子の状態を取得 */

    if(u1_s_PwrCtrl_Main_Sts == (U1)PWRCTRL_MAIN_PMPSAIL_FS_REQ)
    {
       vd_s_PwrCtrlMainPmPsailFsSeq();        /* PM_PSAIL_ERR_N監視(フェールセーフ) */
    }

    if(u1_s_PwrCtrl_Main_Sts == (U1)PWRCTRL_MAIN_PMAPS_FS_REQ)
    {
       vd_s_PwrCtrlMainPmaPsFsSeq();          /* PMA_PS_HOLD監視(フェールセーフ) */
    }

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

    if(u1_s_PwrCtrl_Main_Sts == (U1)PWRCTRL_MAIN_STBYCANCELST1_REQ)
    {
       vd_s_PwrCtrlMainStbyCancelSt1Seq();    /* スタンバイ処理中の起動トリガ時シーケンス(SIP電源強制OFF処理開始) */
    }

    if(u1_s_PwrCtrl_Main_Sts == (U1)PWRCTRL_MAIN_STBYCANCELST2_REQ)
    {
       vd_s_PwrCtrlMainStbyCancelSt2Seq();    /* スタンバイ処理中の起動トリガ時シーケンス(SYS系電源ON、SIP電源ON) */
    }

    /* 非冗長電源制御 */
    vd_g_PwrCtrlNoRedunMainFunction();

    /* EtherSW制御要求処理 */
    vd_g_PwrCtrlSipEthReqJudge();

    /* VM間通信送信定期処理 */
    vd_g_PwrCtrlComTxTask();

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainObserveFsJudge
  Description   : 監視制御フェールセーフ判定
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainObserveFsJudge( void )
{
    U2 u2_t_observe_sts;

    /* 監視制御の異常検知情報を取得 */
    u2_t_observe_sts = u2_g_PwrCtrlObserveGetErrSts();

    /* 監視制御の優先度順に異常検知有無を判定 */
    /* 【todo】5-12-1. PGOOD_ASIL_VB監視 異常検知  */
    /* PM_PSAIL_ERR_N監視 異常検知の場合 */
    if( (u2_t_observe_sts & (U2)PWRCTRL_OBSERVE_ERR_PMPSAIL) == (U2)PWRCTRL_OBSERVE_ERR_PMPSAIL)
    {
        /* フェールセーフ処理実施のため検知した監視を停止 */
        vd_g_PwrCtrlObservePsailReq((U1)PWRCTRL_OBSERVE_OFF);           /* PM_PSAIL_ERR_N監視 終了 */

        /* 他SIP監視制御を停止 */
        vd_g_PwrCtrlObservePsHoldReq((U1)PWRCTRL_OBSERVE_OFF);          /* PMA_PS_HOLD監視 終了 */

        /* PM_PSAIL_ERR_N監視フェールセーフ要求 */
        vd_s_PwrCtrlMainPmPsailFsReq();

        /* 【todo】異常内容保存[ID0033] */
        vd_g_PwrCtrlSipSoCOnError();                                      /* SoC異常検知の設定 */
        vd_g_PwrCtrlComTxSetPwrErr((U1)PWRCTRL_COM_PWRERR_PMPSAILERRN);   /* 異常検知(PM_PSAIL_ERR_N監視) */
    }
    /* PMA_PS_HOLD監視 異常検知の場合 */
    else if( (u2_t_observe_sts & (U2)PWRCTRL_OBSERVE_ERR_PMAPS) == (U2)PWRCTRL_OBSERVE_ERR_PMAPS)
    {
        /* フェールセーフ処理実施のため検知した監視を停止 */
        vd_g_PwrCtrlObservePsHoldReq((U1)PWRCTRL_OBSERVE_OFF);          /* PMA_PS_HOLD監視 終了 */

        /* 他SIP監視制御を停止 */
        vd_g_PwrCtrlObservePsailReq((U1)PWRCTRL_OBSERVE_OFF);           /* PM_PSAIL_ERR_N監視 終了 */

        /* PMA_PS_HOLD監視フェールセーフ要求 */
        vd_s_PwrCtrlMainPmaPsFsReq();
        
        vd_g_PwrCtrlComTxSetPwrErr((U1)PWRCTRL_COM_PWRERR_PMAPSHOLD);   /* 異常検知(PMA_PS_HOLD監視) */
    }
    /* 【todo】5-8.SAIL-ERR監視 異常検知  */
    /* 【todo】5-11.SPI通信途絶監視 異常検知  */
    /* 【todo】5-7.SAIL UART Message監視 異常検知 */

    /* 異常検知によるフェールセーフ処理無しの場合 */
    else
    {
        /* 何もしない */
    }
    /* 【todo】5-12-2. PGOOD_ASIL_VSYS監視 異常検知  */
    /* 【todo】5-12-3. PGOOD_ASIL_VSYS(V11)監視 異常検知  */
    /* 【todo】5-12-4. PGOOD_DIODE監視 異常検知  */
    /* 【todo】5-12-5. PGOOD_VB監視 異常検知  */
    /* 【todo】5-12-5. PGOOD_VSYS監視 異常検知  */

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainOnOffJudge
  Description   : スタンバイ/スタンバイ中断(再起動)開始判定
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainOnOffJudge( void )
{
    U1 u1_t_req;
    U1 u1_t_str;

    if ( u1_s_PwrCtrl_Main_Sts == (U1)PWRCTRL_MAIN_NO_REQ )
    {
        /* スタンバイ要求検知 */
        /* 通常動作中(+B起動シーケンス完了 または Wakeupシーケンス完了) */
        if ( u1_s_PwrCtrl_Main_StbyJdgFlag == (U1)PWRCTRL_MAIN_STBYJDG_OK )
        {
            u1_t_req = u1_g_PwrCtrlObserveOnOffTrigger();
            if(u1_t_req == (U1)PWRCTRL_OBSERVE_POWER_OFF)
            {
                u1_t_str = u1_g_PwrCtrlComGetSTRMode();
                
                if(u1_t_str == (U1)PWRCTRL_COM_STR_ON){
                    /* スタンバイシーケンス要求 */
                    vd_s_PwrCtrlMainStandbyReq();
                }
                
                else{
                    /* SIP電源OFF&MCUスタンバイシーケンス要求 */
                    vd_s_PwrCtrlMainSipOffMcuStandbyReq();
                }
            }
        }
        /* 起動検知 */
        /* MCUスリープ待ち(スタンバイ完了) */
        else if(u1_s_PwrCtrl_Main_ShtdwnOkFlag == (U1)PWRCTRL_COMMON_SYS_PWR_ON)
        {
#ifndef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF
            /* 起動トリガ取得 */
            u1_t_req = u1_g_PwrCtrlObserveOnOffTrigger();
#else
            if(u1_g_PwrCtrl_Main_DbgFailOffFlag == (U1)MCU_DIO_HIGH)
            {
                /* 起動トリガ取得 */
                u1_t_req = u1_g_PwrCtrlObserveOnOffTrigger();
            }
            else
            {
                /* DBG-FAIL-OFF=Lo時は起動トリガ検知しない */
                u1_t_req = (U1)PWRCTRL_OBSERVE_POWER_OFF;
            }
#endif
            if(u1_t_req == (U1)PWRCTRL_OBSERVE_POWER_ON)
            {
                /* スタンバイ処理中の起動トリガ時シーケンス要求(SYS系電源ON、SIP電源ON) */
                vd_s_PwrCtrlMainStbyCancelSt2Req((U1)PWRCTRL_MAIN_STBYCANCEL_OTHER);
            }
        }
        else
        {
            /* 何もしない */
        }
    }
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
    U1 u1_t_socrst;                                                            /* SoCリセット起動要因取得 */

    u1_t_foff_req = (U1)PWRCTRL_MAIN_FORCEDOFF_STS_INIT;
/* /BU-DET =Hi? */
    if ( u1_s_PwrCtrl_Main_SysPwrSts == (U1)PWRCTRL_MAIN_SYS_STS_BUDET )
    {
        u1_t_read_lv = u1_g_PwrCtrl_PinMonitor_GetPinInfo((U1)PWRCTRL_CFG_PRIVATE_KIND_BU_DET);    /* BU-DET端子の状態を取得 */
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
            u1_s_PwrCtrl_Main_SysPwrInfo = (U1)TRUE;                           /* PGOOD_ASIL_VB端子モニタ条件(SYS電源ON制御完了)設定 */
            vd_g_PwrCtrlObservePgdAsilVbSysPwrReq((U1)PWRCTRL_OBSERVE_ON);     /* PGOOD_ASIL_VB監視 開始(SYS電源ON制御完了条件成立) */
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
        u1_t_read_lv = u1_g_PwrCtrl_PinMonitor_GetPinInfo((U1)PWRCTRL_CFG_PRIVATE_KIND_MM_STBY_N); /* MM_STBY_N端子の状態を取得 */
#ifndef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF
        if ( u1_t_read_lv == (U1)MCU_DIO_HIGH )
#else
        if (( u1_t_read_lv == (U1)MCU_DIO_HIGH) ||
            (u1_g_PwrCtrl_Main_DbgFailOffFlag == (U1)MCU_DIO_LOW))
#endif
        {
            u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_COMP;       /* SIP電源状態：MM_STBY_N=Hi判定中→完了 */
            /* MM_STBY_N =Hiを検知したら */
            /* VISドメインにSoCリセット起動要因を通知 */
            u1_t_socrst = u1_g_PwrCtrlSipSoCRstSts();
            vd_g_VISPwrSocRstNotify(u1_t_socrst);
            /* VISドメインに通知後に状態をクリア */
            vd_g_PwrCtrlSipSoCRstClr();
        }

        else{
            /* MM_STBY_N =Hiチェックを開始してから100秒経過しても完了しない場合 */
            if (u4_s_PwrCtrl_Main_MmStby >= (U4)PWRCTRL_MAIN_TIME_MMSTBY)
            {
                /* 強制OFFシーケンス(SoC異常)要求 */
                u1_t_foff_req = (U1)PWRCTRL_MAIN_FORCEDOFF_STS_SOCERR;
                /* 【todo】異常内容の保存[ID0008] */
                /* SoC異常検知を通知 */
                vd_g_PwrCtrlSipSoCOnError();
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
    vd_s_PwrCtrlMainForcedOffReq(u1_t_foff_req);
    /* 終了処理 */
    if ( ( u1_s_PwrCtrl_Main_SysPwrSts == (U1)PWRCTRL_MAIN_SYS_STS_COMP )
      && ( u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_COMP ) )
    {
        u1_s_PwrCtrl_Main_Sts          = (U1)PWRCTRL_MAIN_NO_REQ;              /* 処理完了 */
        u1_s_PwrCtrl_Main_StbyJdgFlag  = (U1)PWRCTRL_MAIN_STBYJDG_OK;          /* スタンバイ判定可 */
        
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
    U1 u1_t_str;                                                                                           /* STRモード状態 */
    U1 u1_t_sail_err1;                                                                                     /* SAIL-ERR[1]状態 */
    U1 u1_t_sail_err2;                                                                                     /* SAIL-ERR[2]状態 */
    U1 u1_t_socrst;                                                                                        /* SoCリセット起動要因取得 */

    u1_t_foff_req = (U1)PWRCTRL_MAIN_FORCEDOFF_STS_INIT;
/* /BU-DET =Hi? */
    if ( u1_s_PwrCtrl_Main_SysPwrSts == (U1)PWRCTRL_MAIN_SYS_STS_BUDET )
    {
        u1_t_read_lv = u1_g_PwrCtrl_PinMonitor_GetPinInfo((U1)PWRCTRL_CFG_PRIVATE_KIND_BU_DET);    /* BU-DET端子の状態を取得 */
        if ( u1_t_read_lv == (U1)MCU_DIO_HIGH )
        {
            /* 低電圧検知と判定してBU断シーケンスを開始する */
            vd_g_PwrCtrlMainBuDetReq();
        }
        
        else{
            /* 低電圧を検知していなければ正常ルートを進める */
            u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_INPRC;
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
            u1_s_PwrCtrl_Main_SysPwrInfo = (U1)TRUE;                                                      /* PGOOD_ASIL_VB端子モニタ条件(SYS電源ON制御完了)設定 */
            vd_g_PwrCtrlObservePgdAsilVbSysPwrReq((U1)PWRCTRL_OBSERVE_ON);                                /* PGOOD_ASIL_VB監視 開始(SYS電源ON制御完了条件成立) */
/* AOSS_SLEEP_ENTRY_EXIT＝Hi？(SIPがサスペンド状態であることを確認※1度のみ実施) */
            u1_t_read_lv = u1_g_PwrCtrl_PinMonitor_GetPinInfo((U1)PWRCTRL_CFG_PRIVATE_KIND_AOSS_SLP_ENTRY_EXIT); /* AOSS_SLEEP_ENTRY_EXIT端子の状態を取得    */
            if(u1_t_read_lv == (U1)MCU_DIO_HIGH)
            {
                u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_COMP;                              /* SYS電源状態：実行中→完了 */
                u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_INPRC;                             /* SIP電源状態：初期状態→実行中 */
                vd_g_PwrCtrlSipRsmReq();                                                                  /* SIP電源ON要求(WakeUp) */
            }
            else{
                /* STRモード状態取得 */
                u1_t_str = u1_g_PwrCtrlComGetSTRMode();
                if(u1_t_str == (U1)PWRCTRL_COM_STR_ON){
                    /* 【todo】異常内容保存[ID0009]※STRがON時のみ記録 */
                }
                /* +B-ONシーケンスのSIP通常起動から開始 */
                vd_s_PwrCtrlMainBonDDconvOnReq();
               
#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
                u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_WAKE_AOSS_HI; /* TP */
#endif
            }
        }
    }

/* SIP電源定期処理 */
    if((u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_INPRC) &&
       (u1_s_PwrCtrl_Main_Sts == (U1)PWRCTRL_MAIN_WAKEUP_REQ))
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
        u1_t_read_lv = u1_g_PwrCtrl_PinMonitor_GetPinInfo((U1)PWRCTRL_CFG_PRIVATE_KIND_AOSS_SLP_ENTRY_EXIT);   /* AOSS_SLEEP_ENTRY_EXIT端子の状態を取得    */
#ifndef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF
        if(u1_t_read_lv == (U1)MCU_DIO_LOW)
#else
        if((u1_t_read_lv == (U1)MCU_DIO_LOW) ||
           (u1_g_PwrCtrl_Main_DbgFailOffFlag == (U1)MCU_DIO_LOW))
#endif
        {
            vd_g_PwrCtrlObservePsailReq((U1)PWRCTRL_OBSERVE_ON);    /* PM_PSAIL_ERR_N監視 開始 */
            vd_g_PwrCtrlObservePsHoldReq((U1)PWRCTRL_OBSERVE_ON);   /* PMA_PS_HOLD監視 開始 */
            u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_CHK_SAILERR;                           /* SIP電源状態：AOSS_SLEEP_ENTRY_EXIT=Low判定中→SAIL-ERR端子判定 */
        }

        else{
            /* AOSS_SLEEP_ENTRY_EXIT=Loチェックを開始してから5秒経過しても完了しない場合 */
            if (u4_s_PwrCtrl_Main_Aoss >= (U4)PWRCTRL_MAIN_TIME_AOSS)
            {
                /* 強制OFFシーケンス(PMIC異常)要求 */
                u1_t_foff_req = (U1)PWRCTRL_MAIN_FORCEDOFF_STS_PMICERR;
                /* 【todo】異常内容の保存[ID0010] */
                /* SoC異常検知を通知 */
                vd_g_PwrCtrlSipSoCOnError();
            }
        
            else {
                u4_s_PwrCtrl_Main_Aoss++;
            }
        }

#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_WAKE_AOSS_LO; /* TP */
#endif
    }
    
/* SAIL-ERR[2:1] ='01'? */
    if(u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_CHK_SAILERR){
        u1_t_sail_err1 = u1_g_PwrCtrl_PinMonitor_GetPinInfo((U1)PWRCTRL_CFG_PRIVATE_KIND_SAIL_ERR1);   /* SAIL-ERR1端子の状態を取得 */
        u1_t_sail_err2 = u1_g_PwrCtrl_PinMonitor_GetPinInfo((U1)PWRCTRL_CFG_PRIVATE_KIND_SAIL_ERR2);   /* SAIL-ERR2端子の状態を取得 */
        
#ifndef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF
        if((u1_t_sail_err1 == (U1)MCU_DIO_HIGH) &&
           (u1_t_sail_err2 == (U1)MCU_DIO_LOW))
#else
        if((u1_t_sail_err1 == (U1)MCU_DIO_HIGH) &&
           (u1_t_sail_err2 == (U1)MCU_DIO_LOW) ||
           (u1_g_PwrCtrl_Main_DbgFailOffFlag == (U1)MCU_DIO_LOW))
#endif
           {
            /* 【todo】4.0版参照 5-8. SAIL-ERR監視開始 4.0版参照 */
            u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_CHK_MMSTBY;                      /* SIP電源状態：SAIL-ERR端子判定中→MM_STBY_N=Hi判定中 */
           }
        
        else{
            /* SAIL-ERR[2:1] ='01'チェック開始してから5秒経過しても完了しない場合 */
            if(u4_s_PwrCtrl_Main_SailErr >= (U4)PWRCTRL_MAIN_TIME_SAILERR){
                /* 強制OFFシーケンス(SoC異常)要求 */
                u1_t_foff_req = (U1)PWRCTRL_MAIN_FORCEDOFF_STS_SOCERR;
                /* 【todo】異常内容の保存[ID0011] */
                /* SoC異常検知を通知 */
                vd_g_PwrCtrlSipSoCOnError();
            }
            else{
                u4_s_PwrCtrl_Main_SailErr++;
            }
        }
    }

/* MM_STBY_N =Hi?(SOCメインドメインのQNX起動完了の確認) */
    if (u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_CHK_MMSTBY)
    {
        u1_t_read_lv = u1_g_PwrCtrl_PinMonitor_GetPinInfo((U1)PWRCTRL_CFG_PRIVATE_KIND_MM_STBY_N);        /* MM_STBY_N端子の状態を取得 */
#ifndef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF
        if(u1_t_read_lv == (U1)MCU_DIO_HIGH)
#else
        if((u1_t_read_lv == (U1)MCU_DIO_HIGH) ||
           (u1_g_PwrCtrl_Main_DbgFailOffFlag == (U1)MCU_DIO_LOW))
#endif
        {
            u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_COMP;                                  /* SIP電源状態：MM_STBY_N=Hi判定中→完了 */
            /* MM_STBY_N =Hiを検知したら */
            /* VISドメインにSoCリセット起動要因を通知 */
            u1_t_socrst = u1_g_PwrCtrlSipSoCRstSts();
            vd_g_VISPwrSocRstNotify(u1_t_socrst);
            /* VISドメインに通知後に状態をクリア */
            vd_g_PwrCtrlSipSoCRstClr();
            
            /* 【todo】4.0版参照 Wait time (MIN)5秒、(TYP)6秒、(MAX)20秒 4.0版参照 */
            /* 【todo】4.0版参照 5-7. SAIL UART Message監視開始 4.0版参照 */
        }

        else{
            /* MM_STBY_N =Hiチェックを開始してから100秒経過しても完了しない場合 */
            if (u4_s_PwrCtrl_Main_MmStby >= (U4)PWRCTRL_MAIN_TIME_MMSTBY)
            {
                /* 強制OFFシーケンス(SoC異常)要求 */
                u1_t_foff_req = (U1)PWRCTRL_MAIN_FORCEDOFF_STS_SOCERR;
                /* 【todo】異常内容の保存[ID0012] */
                /* SoC異常検知を通知 */
                vd_g_PwrCtrlSipSoCOnError();
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
    vd_s_PwrCtrlMainForcedOffReq(u1_t_foff_req);

    /* 終了処理 */
    if( (u1_s_PwrCtrl_Main_SysPwrSts == (U1)PWRCTRL_MAIN_SYS_STS_COMP)
     && (u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_COMP))
    {
        u1_s_PwrCtrl_Main_Sts = (U1)PWRCTRL_MAIN_NO_REQ;                                                  /* 処理完了 */
        u1_s_PwrCtrl_Main_StbyJdgFlag  = (U1)PWRCTRL_MAIN_STBYJDG_OK;                                     /* スタンバイ判定可 */
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
    U1 u1_t_step_chk;                                                        /* 現在STEP問い合わせ結果 */
    U1 u1_t_wkup_req;                                                        /* 起動トリガ判定結果 */
    U1 u1_t_stbycancel;

    u1_t_stbycancel = (U1)FALSE;

#ifndef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF
    /* 起動トリガ取得 */
    u1_t_wkup_req = u1_g_PwrCtrlObserveOnOffTrigger();
#else
    if(u1_g_PwrCtrl_Main_DbgFailOffFlag == (U1)MCU_DIO_HIGH)
    {
        /* 起動トリガ取得 */
        u1_t_wkup_req = u1_g_PwrCtrlObserveOnOffTrigger();
    }
    else
    {
        /* DBG-FAIL-OFF=Lo時は起動トリガ検知しない */
        u1_t_wkup_req = (U1)PWRCTRL_OBSERVE_POWER_OFF;
    }
#endif
    /* スタンバイ開始～SIPシャットダウン処理完了(STEP3)までの起動トリガ判定 */
    /* 起動トリガが有りの場合 */
    if(u1_t_wkup_req == (U1)PWRCTRL_OBSERVE_POWER_ON)
    {
        if ( u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_INPRC )
        {
            /* 現在STEP(SIP電源OFFシーケンス)を取得する */
            u1_t_step_chk = u1_g_PwrCtrlSipStbyStepGetSts((U1)PWRCTRL_SIP_SIPOFF_STEP_REQ);
            /* 現在STEPがSTEP1からSTEP3の場合 */
            if((u1_t_step_chk == (U1)PWRCTRL_COMMON_PROCESS_STEP1) ||
               (u1_t_step_chk == (U1)PWRCTRL_COMMON_PROCESS_STEP2) ||
               (u1_t_step_chk == (U1)PWRCTRL_COMMON_PROCESS_STEP3)){
                /* スタンバイ処理中の起動トリガ時シーケンス要求(SIP電源強制OFF処理開始) */
                vd_s_PwrCtrlMainStbyCancelSt1Req();
                u1_t_stbycancel = (U1)TRUE;  /*以降の処理をキャンセル*/
            }
        }
    }

    if(u1_t_stbycancel == (U1)FALSE){
        /* SIP電源OFF処理 */
        vd_s_PwrCtrlMainSipOffMcuStandbySipOffStep();
        /* SYS系デバイス終了状態問い合わせ */
        vd_s_PwrCtrlMainSipOffMcuStandbySysDevOffStep();
        /* SYS電源OFF制御 */
        vd_s_PwrCtrlMainSipOffMcuStandbySysOffStep();
        /* 非冗長電源OFFシーケンス状態問い合わせ */
        vd_s_PwrCtrlMainSipOffMcuStandbyNrdOffStep();

        if(u1_s_PwrCtrl_Main_SysPwrSts == (U1)PWRCTRL_MAIN_SYS_STS_COMP)
        {
            /* SYS電源OFF以降の起動トリガ有無判定 */
            /* 起動トリガが有りの場合 */
            if(u1_t_wkup_req == (U1)PWRCTRL_OBSERVE_POWER_ON)
            {
                /* スタンバイ処理中の起動トリガ時シーケンス要求(SYS系電源ON、SIP電源ON) */
                vd_s_PwrCtrlMainStbyCancelSt2Req((U1)PWRCTRL_MAIN_STBYCANCEL_OTHER);
            }
            /* 起動トリガが無しの場合 */
            else
            {
                /* 終了処理 */
                if ( ( u1_s_PwrCtrl_Main_NonRednPwrSts == (U1)PWRCTRL_MAIN_SYS_STS_COMP )
                  && ( u1_s_PwrCtrl_Main_SipPwrSts     == (U1)PWRCTRL_MAIN_SIP_STS_COMP ))
                {
                    u1_s_PwrCtrl_Main_Sts          = (U1)PWRCTRL_MAIN_NO_REQ;            /* 処理完了 */
                    u1_s_PwrCtrl_Main_ShtdwnOkFlag = (U1)PWRCTRL_COMMON_SYS_PWR_ON;
#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
                    u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_NON;      /* 異常系エラーなし */
#endif
                }
            }
        }
    }
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainSipOffMcuStandbySipOffStep
  Description   : 5-5.SIP電源OFF&MCUスタンバイシーケンス_SIP電源OFF処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainSipOffMcuStandbySipOffStep( void )
{
    U1 u1_t_sipoff_seq;                                                      /* SIP電源OFFシーケンス状態問い合わせ結果 */
    U1 u1_t_foff_req;                                                        /* SIP電源強制OFFシーケンス要求確認結果 */
    
    /* SIP電源OFF処理 */
    if ( u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_INPRC )
    {
        vd_g_PwrCtrlSipMainFunc();                                           /* SIP電源 定期処理 */

        u1_t_foff_req  = u1_g_PwrCtrlSipFOffInfo();                          /* SIP電源強制OFFシーケンス要求問い合わせ */
        /* 強制OFFシーケンス要求 */
        vd_s_PwrCtrlMainForcedOffReq(u1_t_foff_req);

        u1_t_sipoff_seq = u1_g_PwrCtrlSipGetSts();                           /* SIP電源シーケンス状態問い合わせ */
        if ( u1_t_sipoff_seq == (U1)TRUE )                                   /* 処理完了 */
        {
            u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_COMP;     /* SIP電源状態：実行中→完了 */
            u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_WAITDEV;  /* SYS電源状態：開始→SYSデバイス終了待ち */
        }
    }

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainSipOffMcuStandbySysDevOffStep
  Description   : 5-5.SIP電源OFF&MCUスタンバイシーケンス_SYS系デバイスOFF処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainSipOffMcuStandbySysDevOffStep( void )
{
    U1 u1_t_devoff_seq;                                                      /* SYS系デバイス終了状態問い合わせ結果 */
    
    /* SYS系デバイス終了状態問い合わせ */
    if ( u1_s_PwrCtrl_Main_SysPwrSts == (U1)PWRCTRL_MAIN_SYS_STS_WAITDEV )
    {
        u1_t_devoff_seq = u1_g_PwrCtrlSysShtdwnGetSts();                     /* SYS系デバイス終了状態問い合わせ */
        if ( u1_t_devoff_seq == (U1)TRUE )                                   /* 処理完了 */
        {
            u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_INPRC;    /* SYS電源状態:SYSデバイス終了待ち→実行中 */
            /* SYS電源OFF要求 */
            vd_g_PwrCtrlSysPwrOffStart();                                    /* SYS電源OFF要求 */
            u1_s_PwrCtrl_Main_SysPwrInfo = (U1)FALSE;                        /* PGOOD_ASIL_VB端子モニタ条件(SYS電源OFF制御開始)設定 */
            vd_g_PwrCtrlObservePgdAsilVbSysPwrReq((U1)PWRCTRL_OBSERVE_OFF);  /* PGOOD_ASIL_VB監視 終了(SYS電源OFF制御完了条件成立) */
        }
    }

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainSipOffMcuStandbySysOffStep
  Description   : 5-5.SIP電源OFF&MCUスタンバイシーケンス_SYS電源OFF処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainSipOffMcuStandbySysOffStep( void )
{
    U1 u1_t_sysoff_seq;                                                      /* SYS電源OFFシーケンス状態問い合わせ結果 */
    
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

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainSipOffMcuStandbyNrdOffStep
  Description   : 5-5.SIP電源OFF&MCUスタンバイシーケンス_非冗長電源OFF処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainSipOffMcuStandbyNrdOffStep( void )
{
    U1 u1_t_nrdoff_seq;                                                      /* 非冗長電源OFFシーケンス状態問い合わせ結果 */
    
    if ( u1_s_PwrCtrl_Main_NonRednPwrSts == (U1)PWRCTRL_MAIN_NRD_STS_INPRC )
    {
        u1_t_nrdoff_seq = u1_g_PwrCtrlNoRedunGetSts();                       /* 非冗長電源シーケンス状態問い合わせ */
        if ( u1_t_nrdoff_seq == (U1)TRUE )                                   /* 処理完了 */
        {
            u1_s_PwrCtrl_Main_NonRednPwrSts = (U1)PWRCTRL_MAIN_NRD_STS_COMP; /* 非冗長電源状態：実行中→完了 */
        }
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
    U1 u1_t_step_chk;                                                        /* 現在STEP問い合わせ結果 */
    U1 u1_t_wkup_req;                                                        /* 起動トリガ判定結果 */
    U1 u1_t_stbycancel;

    u1_t_stbycancel = (U1)FALSE;

#ifndef PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF
    /* 起動トリガ取得 */
    u1_t_wkup_req = u1_g_PwrCtrlObserveOnOffTrigger();
#else
    if(u1_g_PwrCtrl_Main_DbgFailOffFlag == (U1)MCU_DIO_HIGH)
    {
        /* 起動トリガ取得 */
        u1_t_wkup_req = u1_g_PwrCtrlObserveOnOffTrigger();
    }
    else
    {
        /* DBG-FAIL-OFF=Lo時は起動トリガ検知しない */
        u1_t_wkup_req = (U1)PWRCTRL_OBSERVE_POWER_OFF;
    }
#endif
    /* スタンバイ開始～SIPサスペンド処理完了(STEP3)までの起動トリガ判定 */
    /* 起動トリガが有りの場合 */
    if(u1_t_wkup_req == (U1)PWRCTRL_OBSERVE_POWER_ON)
    {
        if ( u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_INPRC )
        {
            /* 現在STEP(スタンバイシーケンス)を取得する */
            u1_t_step_chk = u1_g_PwrCtrlSipStbyStepGetSts((U1)PWRCTRL_SIP_STBY_STEP_REQ);
            /* 現在STEPがSTEP1からSTEP3の場合 */
            if((u1_t_step_chk == (U1)PWRCTRL_COMMON_PROCESS_STEP1) ||
               (u1_t_step_chk == (U1)PWRCTRL_COMMON_PROCESS_STEP2) ||
               (u1_t_step_chk == (U1)PWRCTRL_COMMON_PROCESS_STEP3)){
                /* スタンバイ処理中の起動トリガ時シーケンス要求(SIP電源強制OFF処理開始) */
                vd_s_PwrCtrlMainStbyCancelSt1Req();
                u1_t_stbycancel = (U1)TRUE;  /*以降の処理をキャンセル*/
            }
        }
    }

    if(u1_t_stbycancel == (U1)FALSE){

        /* SIP電源スタンバイ */
        vd_s_PwrCtrlMainStandbySipStby();
        /* SYS系デバイス終了状態問い合わせ */
        vd_s_PwrCtrlMainStandbySysDevOff();
        /* SYS電源OFF制御 */
        vd_s_PwrCtrlMainStandbySysOff();
        /* 非冗長電源OFFシーケンス状態問い合わせ */
        vd_s_PwrCtrlMainStandbyNrdOff();

        if(u1_s_PwrCtrl_Main_SysPwrSts == (U1)PWRCTRL_MAIN_SYS_STS_COMP)
        {
            /* SYS電源OFF以降の起動トリガ有無判定 */
            /* 起動トリガが有りの場合 */
            if(u1_t_wkup_req == (U1)PWRCTRL_OBSERVE_POWER_ON)
            {
                /* スタンバイ処理中の起動トリガ時シーケンス要求(SYS系電源ON、SIP電源ON) */
                vd_s_PwrCtrlMainStbyCancelSt2Req((U1)PWRCTRL_MAIN_STBYCANCEL_OTHER);
            }
            /* 起動トリガが無しの場合 */
            else
            {
                /* 終了処理 */
                if ( ( u1_s_PwrCtrl_Main_NonRednPwrSts == (U1)PWRCTRL_MAIN_NRD_STS_COMP )
                  && ( u1_s_PwrCtrl_Main_SipPwrSts     == (U1)PWRCTRL_MAIN_SIP_STS_COMP ))
                {
                    u1_s_PwrCtrl_Main_Sts          = (U1)PWRCTRL_MAIN_NO_REQ;            /* 処理完了 */
                    u1_s_PwrCtrl_Main_ShtdwnOkFlag = (U1)PWRCTRL_COMMON_SYS_PWR_ON;
#if (PWRCTRL_CFG_PRIVATE_ERR_CHK == PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE)
                    u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_NON;      /* 異常系エラーなし */
#endif 
                }
            }
        }
    }
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainStandbySipStby
  Description   : 5-3.スタンバイシーケンス_SIP電源スタンバイ処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainStandbySipStby( void )
{
    U1 u1_t_sipstb_seq;                                                      /* SIPスタンバイシーケンス状態問い合わせ結果 */
    U1 u1_t_foff_req;                                                        /* SIP電源強制OFFシーケンス要求確認結果 */
    
    /* SIP電源OFF */
    if(u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_INPRC)
    {
        vd_g_PwrCtrlSipMainFunc();                                           /* SIP電源 定期処理 */

        u1_t_foff_req  = u1_g_PwrCtrlSipFOffInfo();                          /* SIP電源強制OFFシーケンス要求問い合わせ */

        /* 強制OFFシーケンス要求 */
        vd_s_PwrCtrlMainForcedOffReq(u1_t_foff_req);

        u1_t_sipstb_seq = u1_g_PwrCtrlSipGetSts();                           /* SIP電源シーケンス状態問い合わせ */
        if(u1_t_sipstb_seq == (U1)TRUE)                                      /* 処理完了 */
        {
            u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_COMP;     /* SIP電源状態：実行中→完了 */
            u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_WAITDEV;  /* SYS電源状態：開始→SYSデバイス終了待ち */
        }
    }

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainStandbySysDevOff
  Description   : 5-3.スタンバイシーケンス_SYS系デバイスOFF処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainStandbySysDevOff( void )
{
    U1 u1_t_devoff_seq;                                                      /* SYS系デバイス終了状態問い合わせ結果 */
    
    /* SYS系デバイス終了状態問い合わせ */
    if(u1_s_PwrCtrl_Main_SysPwrSts == (U1)PWRCTRL_MAIN_SYS_STS_WAITDEV)
    {
        u1_t_devoff_seq = u1_g_PwrCtrlSysShtdwnGetSts();                     /* SYS系デバイス終了状態問い合わせ */
        if(u1_t_devoff_seq ==(U1)TRUE)
        {                                                                    /* 処理完了 */
            u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_INPRC;    /* SYS電源状態:SYSデバイス終了待ち→実行中 */
            /* SYS電源OFF要求 */
            vd_g_PwrCtrlSysPwrOffStart();                                    /* SYS電源OFF要求 */
            u1_s_PwrCtrl_Main_SysPwrInfo = (U1)FALSE;                        /* PGOOD_ASIL_VB端子モニタ条件(SYS電源OFF制御開始)設定 */
            vd_g_PwrCtrlObservePgdAsilVbSysPwrReq((U1)PWRCTRL_OBSERVE_OFF);  /* PGOOD_ASIL_VB監視 終了(SYS電源OFF制御完了条件成立) */
        }
    }

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainStandbySysOff
  Description   : 5-3.スタンバイシーケンス_SYS電源OFF処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainStandbySysOff( void )
{
    U1 u1_t_sysoff_seq;                                                      /* SYS電源シーケンス状態問い合わせ結果 */
    
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

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainStandbyNrdOff
  Description   : 5-3.スタンバイシーケンス_非冗長電源OFF処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainStandbyNrdOff( void )
{
    U1 u1_t_nrdoff_seq;                                                      /* 非冗長電源OFFシーケンス状態問い合わせ結果 */
    
    /* 非冗長電源OFFシーケンス状態問い合わせ */
    if(u1_s_PwrCtrl_Main_NonRednPwrSts == (U1)PWRCTRL_MAIN_NRD_STS_INPRC)
    {
        u1_t_nrdoff_seq = u1_g_PwrCtrlNoRedunGetSts();                       /* 非冗長電源シーケンス状態問い合わせ */
        if(u1_t_nrdoff_seq == (U1)TRUE)                                      /* 処理完了 */
        {
            u1_s_PwrCtrl_Main_NonRednPwrSts = (U1)PWRCTRL_MAIN_NRD_STS_COMP; /* 非冗長電源状態：実行中→完了 */
        }
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
        /* 起動要因が成立しているかの判定 */
        u1_t_wake_factor = u1_g_PwrCtrlObserveOnOffTrigger();
        if(u1_t_wake_factor == (U1)PWRCTRL_OBSERVE_POWER_ON)
        {
            /* SIP電源再起動通知設定 */
            vd_g_PwrCtrlComTxSetPwrOn((U1)PWRCTRL_COM_PWRON_FRCOFF_TO_ON); /* 電源再起動開始(SIP電源強制OFF) */

            /* 非冗長電源制御ON開始 */
            u1_s_PwrCtrl_Main_NonRednPwrSts = (U1)PWRCTRL_MAIN_NRD_STS_INIT;    /* 非冗長電源：初期状態 */
            vd_g_PwrCtrlNoRedunPwrOnStart();                                    /* 非冗長電源制御ON要求 */

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
        else{
            /* 起動要因非成立時 */
           u1_s_PwrCtrl_Main_Sts = (U1)PWRCTRL_MAIN_NO_REQ;            /* 処理完了 */
           vd_s_PwrCtrlMainSipOffMcuStandbySysDevReq();                /* SIP電源OFF&MCUスタンバイシーケンス SYS系電源OFF、MCUスタンバイ処理開始要求 */
        }
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainStbyCancelSt1Seq(void)
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainStbyCancelSt1Seq( void )
{
    U1 u1_t_sipoff_seq;                                                    /* SIP電源シーケンス状態問い合わせ結果 */
    U1 u1_t_devoff_seq;                                                    /* SYS系デバイス終了状態問い合わせ結果 */
    U1 u1_t_sysoff_seq;                                                    /* SYS電源OFFシーケンス状態問い合わせ結果 */

    /* SIP電源強制OFF処理開始 */
    if(u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_INPRC){
        vd_g_PwrCtrlSipMainFunc();                                         /* SIP電源 定期処理 */

        u1_t_sipoff_seq = u1_g_PwrCtrlSipGetSts();                         /* SIP電源シーケンス状態問い合わせ */
        if(u1_t_sipoff_seq == (U1)TRUE)                                    /* 処理完了 */
        {
          u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_COMP;
          u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_WAITDEV;  /* SYS電源状態：SYSデバイス終了待ち */
        }
    }
    /* SIP電源強制OFF処理完了 */
    if(u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_COMP){
        /* SYS系デバイス終了状態問い合わせ */
        if ( u1_s_PwrCtrl_Main_SysPwrSts == (U1)PWRCTRL_MAIN_SYS_STS_WAITDEV )
        {
            u1_t_devoff_seq = u1_g_PwrCtrlSysShtdwnGetSts();                     /* SYS系デバイス終了状態問い合わせ */
            if ( u1_t_devoff_seq == (U1)TRUE )                                   /* 処理完了 */
            {
                u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_INPRC;    /* SYS電源状態:SYSデバイス終了待ち→実行中 */
                /* SYS電源OFF要求 */
                vd_g_PwrCtrlSysPwrOffStart();                                    /* SYS電源OFF要求 */
                u1_s_PwrCtrl_Main_SysPwrInfo = (U1)FALSE;                        /* PGOOD_ASIL_VB端子モニタ条件(SYS電源OFF制御開始)設定 */
                vd_g_PwrCtrlObservePgdAsilVbSysPwrReq((U1)PWRCTRL_OBSERVE_OFF);  /* PGOOD_ASIL_VB監視 終了(SYS電源OFF制御完了条件成立) */
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

                /* スタンバイ処理中の起動トリガ時シーケンス要求(SYS系電源ON、SIP電源ON) */
                vd_s_PwrCtrlMainStbyCancelSt2Req((U1)PWRCTRL_MAIN_STBYCANCEL_SIPOFF);
            }
        }
    }
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainStbyCancelSt2Seq(void)
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainStbyCancelSt2Seq( void )
{
    U1 u1_t_sipfoff_seq;                                                   /* SIP入力DDコン電源OFF処理実施要否取得結果 */
    U1 u1_t_syson_seq;                                                     /* SYS電源ONシーケンス状態問い合わせ結果 */

    /* SYS電源ON制御 */
    if ( u1_s_PwrCtrl_Main_SysPwrSts == (U1)PWRCTRL_MAIN_SYS_STS_INPRC )
    {
        vd_g_PwrCtrlSysPwrOnMainFunction();
        u1_t_syson_seq = u1_g_PwrCtrlSysGetSts();                          /* SYS電源シーケンス状態問い合わせ */
        if ( u1_t_syson_seq == (U1)TRUE )                                  /* 処理完了 */
        {
            u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_COMP;   /* SYS電源状態：実行中→完了 */
            u1_s_PwrCtrl_Main_SysPwrInfo = (U1)TRUE;                       /* PGOOD_ASIL_VB端子モニタ条件(SYS電源ON制御完了)設定 */
            vd_g_PwrCtrlObservePgdAsilVbSysPwrReq((U1)PWRCTRL_OBSERVE_ON); /* PGOOD_ASIL_VB監視 開始(SYS電源ON制御完了条件成立) */
            /* SIP入力DDコン電源OFF処理実施要否を取得 */
            u1_t_sipfoff_seq = u1_g_PwrCtrlSipFOffGetSts();
            if(u1_t_sipfoff_seq == (U1)PWRCTRL_SIP_FOFF_DDCONV_ON){
                /* SIP入力DDコン電源OFF処理実施 */
                u1_s_PwrCtrl_Main_Sts = (U1)PWRCTRL_MAIN_NO_REQ;           /* 処理完了 */
                vd_s_PwrCtrlMainBonDDconvOnReq();                          /* +B起動シーケンス SIP用DDコン起動処理開始要求 */
            }
            else
            {
                /* SIP入力DDコン電源OFF処理未実施 */
                u1_s_PwrCtrl_Main_Sts = (U1)PWRCTRL_MAIN_NO_REQ;           /* 処理完了 */
                vd_s_PwrCtrlMainBonPwrOnReq();                             /* +B起動シーケンス SIP電源のみ起動処理開始要求 */
            }
        }
    }

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainPmPsailFsSeq
  Description   : PM_PSAIL_ERR_N監視フェールセーフ処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainPmPsailFsSeq( void )
{
    U1 u1_t_foff_req;                                                        /* SIP電源強制OFFシーケンス要求確認結果 */
    U1 u1_t_sip_fs_seq;

    if(u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_INPRC)
    {
        vd_g_PwrCtrlSipMainFunc();                                           /* SIP電源 定期処理 */

        /* SIP処理終了判定 */
        u1_t_sip_fs_seq = u1_g_PwrCtrlSipGetSts();                           /* SIP電源シーケンス状態問い合わせ */
        if(u1_t_sip_fs_seq == (U1)TRUE)                                      /* 処理完了 */
        {
            u1_s_PwrCtrl_Main_Sts       = (U1)PWRCTRL_MAIN_NO_REQ;           /* シーケンス完了 */
            u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_COMP;     /* SIP電源状態：実行中→完了 */

            /* SIP電源強制OFFシーケンスへ遷移 */
            u1_t_foff_req = u1_g_PwrCtrlSipFOffInfo();                       /* SIP電源強制OFF要求取得 */
            vd_s_PwrCtrlMainForcedOffReq(u1_t_foff_req);                     /* SIP電源強制OFFシーケンス要求 */
        }
    }
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlMainPmaPsFsSeq
  Description   : PMA_PS_HOLD監視フェールセーフ処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlMainPmaPsFsSeq( void )
{
    U1 u1_t_foff_req;                                               /* SIP電源強制OFFシーケンス要求確認結果 */
    U1 u1_t_sip_fs_seq;
    U1 u1_t_wake_factor;

    if(u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_INPRC)
    {
        vd_g_PwrCtrlSipMainFunc();                                  /* SIP電源 定期処理 */

        /* SIP電源強制OFFシーケンス遷移判定 */
        u1_t_foff_req = u1_g_PwrCtrlSipFOffInfo();               /* SIP電源強制OFF要求取得 */
        vd_s_PwrCtrlMainForcedOffReq(u1_t_foff_req);             /* SIP電源強制OFFシーケンス要求 */

        /* SIP処理終了判定 */
        u1_t_sip_fs_seq = u1_g_PwrCtrlSipGetSts();                      /* SIP電源シーケンス状態問い合わせ */
        if(u1_t_sip_fs_seq == (U1)TRUE)                                 /* 処理完了 */
        {
            u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_COMP;
        }
    }
    /* SIP処理終了後の判定 */
    if(u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_COMP)
    {
        /* 起動要件成立? */
        u1_t_wake_factor = u1_g_PwrCtrlObserveOnOffTrigger();
        if(u1_t_wake_factor == (U1)PWRCTRL_OBSERVE_POWER_ON)
        {
            vd_g_PwrCtrlComTxSetPwrOn((U1)PWRCTRL_COM_PWRON_PMAPSHOLD_TO_ON);   /* SIP電源再起動通知設定 */

            u1_s_PwrCtrl_Main_NonRednPwrSts = (U1)PWRCTRL_MAIN_NRD_STS_INIT;    /* 非冗長電源：初期状態 */
            vd_g_PwrCtrlNoRedunPwrOnStart();                                    /* 非冗長電源制御ON要求 */

            u1_s_PwrCtrl_Main_Sts = (U1)PWRCTRL_MAIN_NO_REQ;        /* 処理完了 */
            vd_s_PwrCtrlMainBonPwrOnReq();                          /* +B起動シーケンス SIP電源のみ起動処理開始要求 */
        }
        else
        {
            u1_s_PwrCtrl_Main_Sts = (U1)PWRCTRL_MAIN_NO_REQ;        /* 処理完了 */
            vd_s_PwrCtrlMainSipOffMcuStandbySysDevReq();            /* SIP電源OFF&MCUスタンバイシーケンス SYS系電源OFF、MCUスタンバイ処理開始要求 */
        }
    }

    return;
}

/****************************************************************************/
/* Service API                                                              */
/****************************************************************************/
/**** End of File ***********************************************************/
