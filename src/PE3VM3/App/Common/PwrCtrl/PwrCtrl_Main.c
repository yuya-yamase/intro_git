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
#define PWRCTRL_MAIN_SYS_STS_INIT       (0x00U)   /* 初期状態 */
#define PWRCTRL_MAIN_SYS_STS_INPRC      (0x01U)   /* 実行中 */
#define PWRCTRL_MAIN_SYS_STS_WAITDEV    (0x02U)   /* SYSデバイス終了待ち */
#define PWRCTRL_MAIN_SYS_STS_COMP       (0xFFU)   /* 完了 */

/* 非冗長電源状態 */
#define PWRCTRL_MAIN_NRD_STS_INIT       (0x00U)   /* 初期状態 */
#define PWRCTRL_MAIN_NRD_STS_INPRC      (0x01U)   /* 実行中 */
#define PWRCTRL_MAIN_NRD_STS_COMP       (0xFFU)   /* 完了*/

/* SIP電源状態 */
#define PWRCTRL_MAIN_SIP_STS_INIT       (0x00U)   /* 初期状態 */
#define PWRCTRL_MAIN_SIP_STS_INPRC      (0x01U)   /* 実行中 */
#define PWRCTRL_MAIN_SIP_STS_CHK_MMSTBY (0x02U)   /* MM_STBY_N変化待ち */
#define PWRCTRL_MAIN_SIP_STS_CHK_AOSS   (0x03U)   /* AOSS_SLEEP_ENTRY_EXIT変化待ち */
#define PWRCTRL_MAIN_SIP_STS_COMP       (0xFFU)   /* 完了 */

/* Dio端子監視結果 */
#define PWRCTRL_MAIN_DIO_READ_CHK_INIT  (0x00U)   /* 状態監視初期状態 */
#define PWRCTRL_MAIN_DIO_READ_CHK_OK    (0x01U)   /* 指定時間内に正常応答 */
#define PWRCTRL_MAIN_DIO_READ_CHK_NG    (0xFFU)   /* 時間超過or異常応答 */

#define PWRCTRL_MAIN_BUSSLEEPTIME       (12000U) /* 60sec/5ms周期 */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static void vd_s_PwrCtrlMainStartSet( void );
static void vd_s_PwrCtrlMainSipOffMcuStandbyReq( void );
static void vd_s_PwrCtrlMainSleepJudge( void );

/* シーケンス動作用処理 */
static void vd_s_PwrCtrlMainBonSeq( void );
static void vd_s_PwrCtrlMainWakeUpSeq( void );
static void vd_s_PwrCtrlMainSipOffMcuStandbySeq( void );
static void vd_s_PwrCtrlMainStandbySeq( void );
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

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Functions                                                                */
/*--------------------------------------------------------------------------*/
U1 u1_g_PwrCtrlMainShtdwnOk( void )
{
    return( u1_s_PwrCtrl_Main_ShtdwnOkFlag );
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
    vd_s_PwrCtrlMainStartSet();
    /* SYS電源制御 初期化処理 */
    vd_g_PwrCtrlSysInit();
    /* 非冗長電源制御 初期化処理 */
    vd_g_PwrCtrlNoRedunInit();

    u1_s_PwrCtrl_Main_ShtdwnOkFlag = (U1)PWRCTRL_COMMON_SYS_PWR_OFF; /* 暫定 */

    vd_g_PwrCtrlSipBonInit();                                 /* SIP電源状態+B初期化要求 */
    vd_g_PwrCtrlSysPwrOnStart();
    vd_g_PwrCtrlNoRedunPwrOnStart();

    /* +B-ONシーケンス実施要求 */
    u1_s_PwrCtrl_Main_Sts = (U1)PWRCTRL_MAIN_BON_REQ;
    u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_INPRC; /* SYS電源：実行中 */

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
    vd_s_PwrCtrlMainStartSet();
    /* SYS電源制御 初期化処理 */
    vd_g_PwrCtrlSysInit();
    /* 非冗長電源制御 初期化処理 */
    vd_g_PwrCtrlNoRedunInit();

    u1_s_PwrCtrl_Main_ShtdwnOkFlag = (U1)PWRCTRL_COMMON_SYS_PWR_OFF; /* 暫定 */

    vd_g_PwrCtrlSipWkupInit();                                /* SIP電源状態Wakeup初期化要求 */
    vd_g_PwrCtrlSysPwrOnStart();
    vd_g_PwrCtrlNoRedunPwrOnStart();

    /* ウェイクアップシーケンス実施要求 */
    u1_s_PwrCtrl_Main_Sts = (U1)PWRCTRL_MAIN_WAKEUP_REQ;
    u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_INPRC; /* SYS電源：実行中 */

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
    u1_s_PwrCtrl_Main_Sts = (U1)PWRCTRL_MAIN_SIPOFF_MCUSTANDBY_REQ;
    vd_s_PwrCtrlMainStartSet();
    EthSW_PowerOff_Req();                                         /* 暫定_EtherSW終了要求 */

    u1_s_PwrCtrl_Main_BusSleepFlag = (U1)PWRCTRL_COMMON_SYS_PWR_OFF;
    u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_INPRC;     /* SIP電源状態：実行中 */
    vd_g_PwrCtrlSipOffReq();                                      /* SIP電源OFF */

    u1_s_PwrCtrl_Main_NonRednPwrSts = (U1)PWRCTRL_MAIN_NRD_STS_INPRC; /* 非冗長電源状態:開始→実行中 */
    vd_g_PwrCtrlNoRedunPwrOffStart();                             /* 非冗長電源OFF要求 */

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
    u1_s_PwrCtrl_Main_Sts = (U1)PWRCTRL_MAIN_STANDBY_REQ;
    vd_s_PwrCtrlMainStartSet();
    EthSW_PowerOff_Req();                                         /* 暫定_EtherSW終了要求 */
    u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_INPRC;     /* SIP電源状態：実行中 */
    vd_g_PwrCtrlSipStbyReq();                                     /* SIP電源スタンバイ */

    u1_s_PwrCtrl_Main_NonRednPwrSts = (U1)PWRCTRL_MAIN_NRD_STS_INPRC; /* 非冗長電源状態:開始→実行中 */
    vd_g_PwrCtrlNoRedunPwrOffStart();                             /* 非冗長電源OFF要求 */
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
    /* 終了シーケンス開始要否の判定 */
    vd_s_PwrCtrlMainSleepJudge();

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

    /* 非冗長電源制御 */
    vd_g_PwrCtrlNoRedunMainFunction();

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
    u1_t_chk = (U1)FALSE;

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

    if ( u4_s_PwrCtrl_Main_BusSleep_Time == (U4)PWRCTRL_MAIN_BUSSLEEPTIME )   /* CANスリープが60sec間継続 */
    {
        /* BOOT入力値取得処理 */
        u1_t_boot = Dio_ReadChannel(Mcu_Dio_PortId[PWRCTRL_CFG_PRIVATE_PORT_BOOT]);

        if ( u1_t_boot == (U1)STD_LOW )                                           /* BOOT=Loを検知 */
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
#if (PWRCTRL_CFG__PRIVATE_ERR_CHK == PWRCTRL_CFG__PRIVATE_ERR_CHK_ENABLE)
    /* 異常系確認用RAMの初期化 */
    u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_NON;                         /* TP */
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

    /* 【todo】/BU-DETのHiチェックを行う */
    /* 【todo】/BU-DETがLoの場合はBU断シーケンスを開始 */

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

        u1_t_sipon_seq = u1_g_PwrCtrlSipGetSts();                              /* SIP電源シーケンス状態問い合わせ */
        if ( u1_t_sipon_seq == (U1)TRUE )                                      /* 処理完了 */
        {
            u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_CHK_MMSTBY; /* SIP電源状態：実行中→MM_STBY_N=Hi判定中 */
        }
    }

/* MM_STBY_N =Hi?(SOCメインドメインのQNX起動完了の確認) */
    if ( u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_CHK_MMSTBY )
    {
        u1_t_read_lv = Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_MM_STBY_N]);    /* MM_STBY_N端子の状態を取得 */
        if ( u1_t_read_lv == (U1)MCU_DIO_HIGH )
        {
            u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_COMP;             /* SIP電源状態：MM_STBY_N=Hi判定中→完了 */
        }

        /* 【todo】MM_STBY_N =Hiチェックを開始してから100秒経過したら */
        /* 【todo】異常内容保存 */
        /* 【todo】強制OFFシーケンス(SoC異常)へ移行 */

#if (PWRCTRL_CFG__PRIVATE_ERR_CHK == PWRCTRL_CFG__PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_BON_MMSTBY; /* TP */
#endif
    }


/* 終了処理 */
    /* ★要検討★：全部が完了したら、要求を落として処理完了状態にする */
    if ( ( u1_s_PwrCtrl_Main_SysPwrSts == (U1)PWRCTRL_MAIN_SYS_STS_COMP )
      && ( u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_COMP ) )
    {
        u1_s_PwrCtrl_Main_Sts          = (U1)PWRCTRL_MAIN_NO_REQ;              /* 処理完了 */
        u1_s_PwrCtrl_Main_BusSleepFlag = (U1)PWRCTRL_COMMON_SYS_PWR_ON;               /* 暫定 */
        
#if (PWRCTRL_CFG__PRIVATE_ERR_CHK == PWRCTRL_CFG__PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_NON;                              /* 異常系エラーなし */
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

    /* 【todo】/BU-DETのHiチェックを行う */
    /* 【todo】/BU-DETがLoの場合はBU断シーケンスを開始 */

    /* SYS電源ON制御 */
    if ( u1_s_PwrCtrl_Main_SysPwrSts == (U1)PWRCTRL_MAIN_SYS_STS_INPRC )
    {
        vd_g_PwrCtrlSysPwrOnMainFunction();

        u1_t_syson_seq = u1_g_PwrCtrlSysGetSts();                                                           /* SYS電源シーケンス状態問い合わせ */
        if ( u1_t_syson_seq == (U1)TRUE )                                                                   /* 処理完了 */
        {
/* AOSS_SLEEP_ENTRY_EXIT＝Hi？(SIPがサスペンド状態であることを確認※1度のみ実施) */
            u1_t_read_lv = Dio_ReadChannel(Mcu_Dio_PortId[PWRCTRL_CFG_PRIVATE_PORT_AOSS_SLP_ENTRY_EXIT]); /* AOSS_SLEEP_ENTRY_EXIT端子の状態を取得    */
            if(u1_t_read_lv == (U1)MCU_DIO_HIGH)
            {
                u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_COMP;                                /* SYS電源状態：実行中→完了 */
                u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_INPRC;                               /* SIP電源状態：初期状態→実行中 */
                vd_g_PwrCtrlSipRsmReq();                                                                    /* SIP電源ON要求(WakeUp) */
            }
            else{
               /* 【todo】異常内容保存 */
               /* 【todo】+B-ONシーケンス実施(未実装) */
               /* 【todo】+B-ONシーケンスのSIP通常起動から開始 */
#if (PWRCTRL_CFG__PRIVATE_ERR_CHK == PWRCTRL_CFG__PRIVATE_ERR_CHK_ENABLE)
                u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_WAKE_AOSS_HI; /* TP */
#endif
            }
        }
    }

/* SIP電源定期処理 */
    if(u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_INPRC)
    {
        vd_g_PwrCtrlSipMainFunc();                                                                          /* SIP電源 定期処理 */
        u1_t_sipon_seq = u1_g_PwrCtrlSipGetSts();                                                           /* SIP電源シーケンス状態問い合わせ */
        if(u1_t_sipon_seq == (U1)TRUE)                                                                      /* 処理完了 */
        {
            u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_CHK_AOSS;                                /* SIP電源状態：実行中→AOSS_SLEEP_ENTRY_EXIT=Low判定中 */
        }
    }

/* AOSS_SLEEP_ENTRY_EXIT=Lo?(PMICからのSIP電源レジューム完了確認) */
    if(u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_CHK_AOSS)
    {
        u1_t_read_lv = Dio_ReadChannel(Mcu_Dio_PortId[PWRCTRL_CFG_PRIVATE_PORT_AOSS_SLP_ENTRY_EXIT]);    /* AOSS_SLEEP_ENTRY_EXIT端子の状態を取得    */
        if(u1_t_read_lv == (U1)MCU_DIO_LOW)
        {
            u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_CHK_MMSTBY;                              /* SIP電源状態：AOSS_SLEEP_ENTRY_EXIT=Low判定中→MM_STBY_N=Hi判定中 */

            /* 【todo】5-9. PM_PSAIL_ERR_N監視処理開始 */
            /* 【todo】5-10. PMA_PS_HOLD監視処理開始 */
            /* 【todo】4.0版参照 5-12-1. PGOOD_ASIL_VB監視処理開始 4.0版参照 */
            /* 【todo】3.0版参照 5-7. SAIL UART Message監視開始 3.0版参照 */
        }

        /* 【todo】200ms経過しても完了してなければ完了させる */
        /* 【todo】異常保存して強制OFFシーケンス(PMIC異常)へ移行 */

#if (PWRCTRL_CFG__PRIVATE_ERR_CHK == PWRCTRL_CFG__PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_WAKE_AOSS_LO; /* TP */
#endif
    }
    
    /* 【todo】4.0版参照 SAIL-ERR[2:1] == 01かどうかのチェック 4.0版参照 */
    

/* MM_STBY_N =Hi?(SOCメインドメインのQNX起動完了の確認) */
    if (u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_CHK_MMSTBY)
    {
        u1_t_read_lv = Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_MM_STBY_N]);                  /* MM_STBY_N端子の状態を取得 */
        if(u1_t_read_lv == (U1)MCU_DIO_HIGH)
        {
            u1_s_PwrCtrl_Main_SipPwrSts = (U1)PWRCTRL_MAIN_SIP_STS_COMP;                                    /* SIP電源状態：MM_STBY_N=Hi判定中→完了 */
            
            /* 【todo】4.0版参照 Wait time (MIN)5秒、(TYP)6秒、(MAX)20秒 4.0版参照 */
            /* 【todo】4.0版参照 5-7. SAIL UART Message監視開始 4.0版参照 */
        }

        /* 【todo】100秒経過しても完了してなければ完了させる */
        /* 【todo】異常保存して強制OFFシーケンス(SOC異常)へ移行 */

#if (PWRCTRL_CFG__PRIVATE_ERR_CHK == PWRCTRL_CFG__PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_WAKE_MMSTBY; /* TP */
#endif
    }

/* 終了処理 */
    /* ★要検討★：全部が完了したら、要求を落として処理完了状態にする */
    if( (u1_s_PwrCtrl_Main_SysPwrSts     == (U1)PWRCTRL_MAIN_SYS_STS_COMP)
     && (u1_s_PwrCtrl_Main_SipPwrSts     == (U1)PWRCTRL_MAIN_SIP_STS_COMP))
     {
        u1_s_PwrCtrl_Main_Sts = (U1)PWRCTRL_MAIN_NO_REQ;              /* 処理完了 */
#if (PWRCTRL_CFG__PRIVATE_ERR_CHK == PWRCTRL_CFG__PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_NON;               /* 異常系エラーなし */
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
    U1 u1_t_nrdoff_seq;                                                      /* 非冗長電源OFFシーケンス状態問い合わせ結果 */
    U1 u1_t_sysoff_seq;                                                      /* SYS電源OFFシーケンス状態問い合わせ結果 */
    U1 u1_t_devoff_seq;                                                      /* SYS系デバイス終了状態問い合わせ結果 */

    /* SIP電源OFF処理 */
    if ( u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_INPRC )
    {
        vd_g_PwrCtrlSipMainFunc();                                           /* SIP電源 定期処理 */

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
    }

    /* SYS電源OFFシーケンス状態問い合わせ */
    if ( u1_s_PwrCtrl_Main_SysPwrSts == (U1)PWRCTRL_MAIN_SYS_STS_INPRC )
    {
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
        u1_s_PwrCtrl_Main_Sts = (U1)PWRCTRL_MAIN_NO_REQ;                     /* 処理完了 */
        u1_s_PwrCtrl_Main_ShtdwnOkFlag = (U1)PWRCTRL_COMMON_SYS_PWR_ON;             /* 暫定 */
        
#if (PWRCTRL_CFG__PRIVATE_ERR_CHK == PWRCTRL_CFG__PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_NON;                            /* 異常系エラーなし */
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
    U1 u1_t_nrdoff_seq;                                                      /* 非冗長電源OFFシーケンス状態問い合わせ結果 */
    U1 u1_t_sysoff_seq;                                                      /* SYS電源OFFシーケンス状態問い合わせ結果 */
    U1 u1_t_devoff_seq;                                                      /* SYS系デバイス終了状態問い合わせ結果 */

    /* SIP電源OFF */
    if(u1_s_PwrCtrl_Main_SipPwrSts == (U1)PWRCTRL_MAIN_SIP_STS_INPRC)
    {
        vd_g_PwrCtrlSipMainFunc();                                           /* SIP電源 定期処理 */

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

    /* SYS電源OFFシーケンス状態問い合わせ */
    if(u1_s_PwrCtrl_Main_SysPwrSts == (U1)PWRCTRL_MAIN_SYS_STS_INPRC)
    {
        u1_t_sysoff_seq = u1_g_PwrCtrlSysGetSts();                           /* SYS電源シーケンス状態問い合わせ */
        if(u1_t_sysoff_seq == (U1)TRUE)                                      /* 処理完了 */
        {
            u1_s_PwrCtrl_Main_SysPwrSts = (U1)PWRCTRL_MAIN_SYS_STS_COMP;     /* SYS電源状態：実行中→完了 */
        }
    }
    /* ★要検討★：全部が完了したら、要求を落として処理完了状態にする */
    if( (u1_s_PwrCtrl_Main_SysPwrSts     == (U1)PWRCTRL_MAIN_SYS_STS_COMP)
     && (u1_s_PwrCtrl_Main_NonRednPwrSts == (U1)PWRCTRL_MAIN_NRD_STS_COMP)
     && (u1_s_PwrCtrl_Main_SipPwrSts     == (U1)PWRCTRL_MAIN_SIP_STS_COMP))
     {
        u1_s_PwrCtrl_Main_Sts = (U1)PWRCTRL_MAIN_NO_REQ;                     /* 処理完了 */
#if (PWRCTRL_CFG__PRIVATE_ERR_CHK == PWRCTRL_CFG__PRIVATE_ERR_CHK_ENABLE)
        u1_s_pwrctrl_common_err_dbg_state = (U1)PWRCTRL_COMMON_ERR_NON;                            /* 異常系エラーなし */
#endif 
     }
    return;
}

/****************************************************************************/
/* Service API                                                              */
/****************************************************************************/
/**** End of File ***********************************************************/
