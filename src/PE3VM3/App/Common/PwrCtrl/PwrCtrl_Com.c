/* PwrCtrl_Com_c_v1-0-0                                                     */
/****************************************************************************/
/* Copyright (C) 2023 Denso Co.,Ltd. All rights reserved.                   */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | PwrCtrl_Com/CODE                                          */
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
/* 受信用 */
/* DID */
#define PWRCTRL_COM_VMRXID_VM1_STBY        (IVDSH_DID_REA_VM1TO3_STBY)    /* VM1スタンバイ条件成立有無 */
#define PWRCTRL_COM_VMRXID_VM2_STBY        (IVDSH_DID_REA_VM2TO3_STBY)    /* VM2スタンバイ条件成立有無 */
#define PWRCTRL_COM_VMRXID_VM1_FSLP        (IVDSH_DID_REA_VM1TO23_FSLP)   /* VM1強制スリープ条件成立有無 */
#define PWRCTRL_COM_VMRXID_VM2_SOCSTS      (IVDSH_DID_REA_VM2TO3_OPESTS)  /* VM2動作ステータス通知 */
#define PWRCTRL_COM_VMRXID_VM2_STR         (IVDSH_DID_REA_VM2TO3_STRMODE) /* STRモード状態通知 */
#define PWRCTRL_COM_VMRXID_VM1_SPIFAIL     (IVDSH_DID_REA_VM1TO3_SPI_FAIL) /* SPI通信途絶監視結果 */
#define PWRCTRL_COM_VMRXID_VM1_NMDIAG      (IVDSH_DID_REA_VM1TO3_NMDIAG)  /* NMダイアグリセット */

/* データ長(word) */
#define PWRCTRL_COM_STBY_LEN               (1U)         /* スタンバイ条件成立有無データ長 */
#define PWRCTRL_COM_FSLP_LEN               (1U)         /* 強制スリープ条件成立有無データ長 */
#define PWRCTRL_COM_SOCSTS_LEN             (1U)         /* 動作ステータス通知データ長 */
#define PWRCTRL_COM_STR_LEN                (1U)         /* STRモード状態通知データ長 */
#define PWRCTRL_COM_SPIFAIL_LEN            (1U)         /* STRモード状態通知データ長 */
#define PWRCTRL_COM_NMDIAG_LEN             (1U)         /* NMダイアグリセット検知状態データ長 */

/* SoC動作状態 */
#define PWRCTRL_COM_SOCSTS_INIT            (0x00U)      /* SoC動作状態:未設定 */
#define PWRCTRL_COM_SOCSTS_COMP            (0x04U)      /* SoC動作状態:SoC起動完了 */
#define PWRCTRL_COM_RCVBUF_CLR             (0U)         /* 格納先バッファ初期化用 */

/* 送信用 */
/* DID */
#define PWRCTRL_COM_VMTXID_VM2_PWRON       (IVDSH_DID_WRI_VM3TO12_RESTART)    /* SIP電源再起動通知 */
#define PWRCTRL_COM_VMTXID_VM2_PWRERR      (IVDSH_DID_WRI_VM3TO2_SIPERR_INF)  /* SIP異常検知通知 */
#define PWRCTRL_COM_VMTXID_VM2_SOCONCOUNT  (IVDSH_DID_WRI_VM3TO2_BOOT_CNT)    /* SoC起動回数カウンタ */
#define PWRCTRL_COM_VMTXID_VM2_SOCONTIME   (IVDSH_DID_WRI_VM3TO2_BOOT_TIME)   /* Soc起動回数カウンタ更新時間 */
#define PWRCTRL_COM_VMTXID_VM2_BOOTLOGINF  (IVDSH_DID_WRI_VM3TO2_BOOTLOG_INF) /* 起動ログ計測点検知データ */
#define PWRCTRL_COM_VMTXID_VM1_SOCPOWER    (IVDSH_DID_WRI_VM3TO1_SOC_POW_STS) /* SoC起動状態 */
#define PWRCTRL_COM_VMTXID_VM1_SOCWKUPCOND (IVDSH_DID_WRI_VM3TO2_WKUP_COND)   /* SoC起動条件通知 */
#define PWRCTRL_COM_VMTXID_VM1_USRRSTMASK  (IVDSH_DID_WRI_VM3TO2_USRRST_MASK) /* ユーザーリセット抑止区間通知 */

/* データ長(word) */
#define PWRCTRL_COM_PWRON_LEN              (1U)         /* SIP電源再起動通知データ長 */
#define PWRCTRL_COM_PWRERR_LEN             (1U)         /* SIP異常検知通知データ長 */
#define PWRCTRL_COM_COUNT_LEN              (1U)         /* SoC起動回数カウンタデータ長 */
#define PWRCTRL_COM_TIME_LEN               (1U)         /* SoC起動回数カウンタ更新時間データ長 */
#define PWRCTRL_COM_BOOTLOG_LEN            (1U)         /* 起動ログ計測点通知情報データ長 */
#define PWRCTRL_COM_SOCPOWER_LEN           (1U)         /* SoC起動状態データ長 */
#define PWRCTRL_COM_SOCWKUPCOND_LEN        (1U)         /* SoC起動条件通知データ長 */
#define PWRCTRL_COM_USRRSTMASK_LEN         (1U)         /* ユーザーリセット抑止区間通知データ長 */

/* SoC起動回数カウンタ */
#define PWRCTRL_COM_SOCONCOUNT_MAX         (0xFFFFU)    /* 最大値 */
#define PWRCTRL_COM_SOCONCOUNT_INIT        (0x0000U)    /* 初期値 */

/* SoC起動回数カウンタ更新時の時間 */
#define PWRCTRL_COM_SOCONTIME_INIT         (0U)         /* 初期値 */

/* 起動ログ計測点検知データ定義 */
#define PWRCTRL_COM_BOOTLOG_NON           (0x00000000) /* 全計測点クリア */
#define PWRCTRL_COM_BOOTLOG_BON_SET       (0x00000001) /* 計測点③SoC起動時 */
#define PWRCTRL_COM_BOOTLOG_STR_SET       (0x00000100) /* 計測点③'STRWake時 */
#define PWRCTRL_COM_BOOTLOG_ETH_SET       (0x00010000) /* 計測点⑮⑬Ethリンクアップ時 */
#define PWRCTRL_COM_BOOTLOG_BON_RESET     (0x00FFFF00) /* 計測点③SoC起動クリア */
#define PWRCTRL_COM_BOOTLOG_STR_RESET     (0x00FF00FF) /* 計測点③'STRWakeクリア */
#define PWRCTRL_COM_BOOTLOG_ETH_RESET     (0x0000FFFF) /* 計測点⑮⑬Ethリンクアップクリア */

/* 共通 */
#define PWRCTRL_COM_1BYTEMASK              (0x000000FF) /* 1Byte目マスク */
#define PWRCTRL_COM_2BYTEMASK              (0x0000FF00) /* 2Byte目マスク */
#define PWRCTRL_COM_LOW2BMASK              (0x0000FFFF) /* 下位2Byteマスク */
#define PWRCTRL_COM_1BYTESHIFT             (8)          /* 1Byteシフト */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static void vd_s_PwrCtrlComRxVm1Stby( void );
static void vd_s_PwrCtrlComRxVm2Stby( void );
static void vd_s_PwrCtrlComRxForceSleep( void );
static void vd_s_PwrCtrlComRxSoCSts( void );
static void vd_s_PwrCtrlComRxSTR( void );
static void vd_s_PwrCtrlComRxSpiFail( void );
static void vd_s_PwrCtrlComRxNMDiagReset( void );
static void vd_s_PwrCtrlComEthLinkupStsSet( void );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
static U1 u1_s_PwrCtrl_Com_Rx_Vm1StbyInfo;   /* VM1スタンバイ条件成立有無 */
static U1 u1_s_PwrCtrl_Com_Rx_Vm2StbyInfo;   /* VM2スタンバイ条件成立有無 */
static U1 u1_s_PwrCtrl_Com_Rx_FsleepInfo;    /* 強制スリープ条件成立有無 */
static U1 u1_s_PwrCtrl_Com_Rx_SoCSts;        /* SoC動作状態 */
static U1 u1_s_PwrCtrl_Com_Rx_SoCResetReq;   /* SoCリセット要求 */
static U1 u1_s_PwrCtrl_Com_Rx_STRModeInfo;   /* STRモード状態 */
static U1 u1_s_PwrCtrl_Com_Rx_SpiFail;       /* SPI通信途絶監視結果 */
static U1 u1_s_PwrCtrl_Com_Rx_NMDiagReset;   /* NMダイアグリセット */
static U4 u4_s_PwrCtrl_Com_Tx_PwrOn;         /* SIP電源再起動通知 */
static U4 u4_s_PwrCtrl_Com_Tx_PwrErr;        /* SIP異常検知通知 */
static U4 u4_s_PwrCtrl_Com_Tx_SoCOnCount;    /* SoC起動回数カウンタ */
static U4 u4_s_PwrCtrl_Com_Tx_SoCOnTime;     /* SoC起動回数カウンタ更新時の時間 */
static U4 u4_s_PwrCtrl_Com_Tx_BootLog;       /* 起動ログ計測点通知 */
static U4 u4_s_PwrCtrl_Com_Tx_SoCPower;      /* SoC起動状態 */
static U4 u4_s_PwrCtrl_Com_Tx_SoCWkupCond;   /* SoC起動条件通知 */
static U4 u4_s_PwrCtrl_Com_Tx_UsrRstMask;    /* ユーザーリセット抑止区間通知 */
static U1 u1_s_PwrCtrl_Com_Eth_LinkupSts;    /* Ethリンクアップ状態 */
static U1 u1_s_PwrCtrl_Com_URMaskOffSts;     /* ユーザーリセット抑止解除受付状態 */

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
  Function      : vd_g_PwrCtrlComBonInit
  Description   : +B-ON初期化処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlComBonInit( void )
{
    u1_s_PwrCtrl_Com_Rx_Vm1StbyInfo = (U1)PWRCTRL_COM_STBY_OK;      /* VM1スタンバイ条件成立有無 */
    u1_s_PwrCtrl_Com_Rx_Vm2StbyInfo = (U1)PWRCTRL_COM_STBY_OK;      /* VM2スタンバイ条件成立有無 */
    u1_s_PwrCtrl_Com_Rx_FsleepInfo = (U1)PWRCTRL_COM_FSLP_OFF;      /* 強制スリープ条件成立有無 */
    u1_s_PwrCtrl_Com_Rx_SoCSts = (U1)PWRCTRL_COM_SOCSTS_INIT;       /* SoC動作状態 */
    u1_s_PwrCtrl_Com_Rx_SoCResetReq = (U1)PWRCTRL_COM_SOCRESET_NON; /* SoCリセット要求 */
    u1_s_PwrCtrl_Com_Rx_STRModeInfo = (U1)PWRCTRL_COM_STR_OFF;      /* STRモード状態 */
    u1_s_PwrCtrl_Com_Rx_SpiFail = (U1)PWRCTRL_COM_SPIFAIL_OK;       /* SPI通信途絶監視結果 */
    u1_s_PwrCtrl_Com_Rx_NMDiagReset = (U1)PWRCTRL_COM_NMDIAGRESET_NON;  /* NMダイアグリセット検知 */
    u4_s_PwrCtrl_Com_Tx_PwrOn = (U4)PWRCTRL_COM_PWRON_NOINFO;       /* SIP電源再起動通知 */
    u4_s_PwrCtrl_Com_Tx_PwrErr = (U4)PWRCTRL_COM_PWRERR_NOERR;      /* SIP異常検知通知 */
    u4_s_PwrCtrl_Com_Tx_SoCOnCount = (U4)PWRCTRL_COM_SOCONCOUNT_INIT;   /* SoC起動回数カウンタ */
    u4_s_PwrCtrl_Com_Tx_SoCPower = (U4)PWRCTRL_COM_SOCPOWER_OFF;    /* SoC起動状態 */
    u4_s_PwrCtrl_Com_Tx_SoCWkupCond = (U4)PWRCTRL_COM_SOCWKUP_NON;  /* SoC起動条件通知 */
    vd_g_Rim_WriteU2((U2)RIMID_U2_PWCTR_SOC_ON_COUNT, (U2)(u4_s_PwrCtrl_Com_Tx_SoCOnCount & (U4)PWRCTRL_COM_LOW2BMASK));

    u4_s_PwrCtrl_Com_Tx_SoCOnTime = (U4)PWRCTRL_COM_SOCONTIME_INIT;     /* SoC起動回数カウンタ更新時の時間 */
    vd_g_Rim_WriteU4((U2)RIMID_U4_PWCTR_SOC_ON_TIME, u4_s_PwrCtrl_Com_Tx_SoCOnTime); 
    
    u4_s_PwrCtrl_Com_Tx_UsrRstMask = (U4)PWRCTRL_COM_USRRSTMASK_OFF;    /* ユーザーリセット抑止区間通知 */
    vd_g_Rim_WriteU4((U2)RIMID_U4_PWCTR_SOC_USRRSTMASK, u4_s_PwrCtrl_Com_Tx_UsrRstMask);

    vd_g_PwrCtrlComTxClrBootLog((U1)PWRCTRL_COM_BOOTLOG_INITREQ);       /* 起動ログ計測点をクリア */
    u1_s_PwrCtrl_Com_Eth_LinkupSts = (U1)PWRCTRL_COM_ETH_LINKUP_NODETECT; /* Ethリンクアップ未検知を設定 */

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlComWkupInit
  Description   : Wakeup初期化処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlComWkupInit( void )
{
    U4 u4_t_soctime_buf;
    U4 u4_t_usrrstmask_buf;
    U2 u2_t_soccount_buf;
    U1 u1_t_soctime_ret;
    U1 u1_t_soccount_ret;
    U1 u1_t_usrrstmask_ret;
    
    u1_s_PwrCtrl_Com_Rx_Vm1StbyInfo = (U1)PWRCTRL_COM_STBY_OK;      /* VM1スタンバイ条件成立有無 */
    u1_s_PwrCtrl_Com_Rx_Vm2StbyInfo = (U1)PWRCTRL_COM_STBY_OK;      /* VM2スタンバイ条件成立有無 */
    u1_s_PwrCtrl_Com_Rx_FsleepInfo = (U1)PWRCTRL_COM_FSLP_OFF;      /* 強制スリープ条件成立有無 */
    u1_s_PwrCtrl_Com_Rx_SoCSts = (U1)PWRCTRL_COM_SOCSTS_INIT;       /* SoC動作状態 */
    u1_s_PwrCtrl_Com_Rx_SoCResetReq = (U1)PWRCTRL_COM_SOCRESET_NON; /* SoCリセット要求 */
    u1_s_PwrCtrl_Com_Rx_STRModeInfo = (U1)PWRCTRL_COM_STR_OFF;      /* STRモード状態 */
    u1_s_PwrCtrl_Com_Rx_SpiFail = (U1)PWRCTRL_COM_SPIFAIL_OK;       /* SPI通信途絶監視結果 */
    u1_s_PwrCtrl_Com_Rx_NMDiagReset = (U1)PWRCTRL_COM_NMDIAGRESET_NON;  /* NMダイアグリセット検知 */
    u4_s_PwrCtrl_Com_Tx_PwrOn = (U4)PWRCTRL_COM_PWRON_NOINFO;       /* SIP電源再起動通知 */
    u4_s_PwrCtrl_Com_Tx_PwrErr = (U4)PWRCTRL_COM_PWRERR_NOERR;      /* SIP異常検知通知 */
    u4_s_PwrCtrl_Com_Tx_SoCPower = (U4)PWRCTRL_COM_SOCPOWER_OFF;    /* SoC起動状態 */
    u4_s_PwrCtrl_Com_Tx_SoCWkupCond = (U4)PWRCTRL_COM_SOCWKUP_NON;  /* SoC起動条件通知 */
    vd_g_PwrCtrlComTxClrBootLog((U1)PWRCTRL_COM_BOOTLOG_INITREQ);   /* 起動ログ計測点をクリア */
    u1_s_PwrCtrl_Com_Eth_LinkupSts = (U1)PWRCTRL_COM_ETH_LINKUP_NODETECT; /* Ethリンクアップ未検知を設定 */

    /* SoC起動回数カウンタ更新時の時間 */
    u4_t_soctime_buf = (U4)PWRCTRL_COM_SOCONTIME_INIT;
    u1_t_soctime_ret = u1_g_Rim_ReadU4withStatus((U2)RIMID_U4_PWCTR_SOC_ON_TIME, &u4_t_soctime_buf);
    if((u1_t_soctime_ret & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK)
    {
        u4_s_PwrCtrl_Com_Tx_SoCOnTime = u4_t_soctime_buf;
    }
    else
    {
        u4_s_PwrCtrl_Com_Tx_SoCOnTime = (U4)PWRCTRL_COM_SOCONTIME_INIT;
    }

    /* SoC起動回数カウンタ */
    u2_t_soccount_buf = (U2)PWRCTRL_COM_SOCONCOUNT_INIT;
    u1_t_soccount_ret= u1_g_Rim_ReadU2withStatus((U2)RIMID_U2_PWCTR_SOC_ON_COUNT, &u2_t_soccount_buf);
    if((u1_t_soccount_ret & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK)
    {
        u4_s_PwrCtrl_Com_Tx_SoCOnCount = (U4)u2_t_soccount_buf;
    }
    else
    {
        u4_s_PwrCtrl_Com_Tx_SoCOnCount = (U4)PWRCTRL_COM_SOCONCOUNT_INIT;
    }

    /* ユーザーリセット抑止区間通知 */
    u4_t_usrrstmask_buf = (U4)PWRCTRL_COM_USRRSTMASK_OFF;
    u1_t_usrrstmask_ret= u1_g_Rim_ReadU4withStatus((U2)RIMID_U4_PWCTR_SOC_USRRSTMASK, &u4_t_usrrstmask_buf);
    if((u1_t_usrrstmask_ret & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK)
    {
        u4_s_PwrCtrl_Com_Tx_UsrRstMask = u4_t_usrrstmask_buf;
    }
    else
    {
        u4_s_PwrCtrl_Com_Tx_UsrRstMask = (U4)PWRCTRL_COM_USRRSTMASK_OFF;
    }

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlComRxTask
  Description   : VM間通信受信定期処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlComRxTask( void )
{
    /* VM1スタンバイ条件成立有無受信 */
    vd_s_PwrCtrlComRxVm1Stby();

    /* VM2スタンバイ条件成立有無受信 */
    vd_s_PwrCtrlComRxVm2Stby();

    /* 強制スリープ条件成立有無受信 */
    vd_s_PwrCtrlComRxForceSleep();
    
    /* 動作ステータス通知受信 */
    vd_s_PwrCtrlComRxSoCSts();

    /* STRモード状態受信 */
    vd_s_PwrCtrlComRxSTR();

    /* SPI通信途絶監視結果受信 */
    vd_s_PwrCtrlComRxSpiFail();

    /* NMダイアグリセット要求受信 */
    vd_s_PwrCtrlComRxNMDiagReset();

    return;
}

/*****************************************************************************
  Function      : u1_g_PwrCtrlComRxGetVm1Stby
  Description   : VM1スタンバイ条件成立有無取得処理
  param[in/out] : none
  return        : [Out] VM1のスタンバイ条件成立有無
  Note          : none
*****************************************************************************/
U1 u1_g_PwrCtrlComRxGetVm1Stby( void )
{
    return(u1_s_PwrCtrl_Com_Rx_Vm1StbyInfo);
}

/*****************************************************************************
  Function      : u1_g_PwrCtrlComRxGetVm2Stby
  Description   : VM2スタンバイ条件成立有無取得処理
  param[in/out] : none
  return        : [Out] VM2のスタンバイ条件成立有無
  Note          : none
*****************************************************************************/
U1 u1_g_PwrCtrlComRxGetVm2Stby( void )
{
    return(u1_s_PwrCtrl_Com_Rx_Vm2StbyInfo);
}

/*****************************************************************************
  Function      : u1_g_PwrCtrlComRxGetForceSleep
  Description   : 強制スリープ条件成立有無取得処理
  param[in/out] : none
  return        : [Out] 強制スリープ条件成立有無
  Note          : none
*****************************************************************************/
U1 u1_g_PwrCtrlComRxGetForceSleep( void )
{
    return(u1_s_PwrCtrl_Com_Rx_FsleepInfo);
}

/*****************************************************************************
  Function      : u1_g_PwrCtrlComGetSoCSts
  Description   : SoC動作状態取得処理
  param[in/out] : none
  return        : SoC動作状態
  Note          : none
*****************************************************************************/
U1 u1_g_PwrCtrlComGetSoCSts( void )
{
    return(u1_s_PwrCtrl_Com_Rx_SoCSts);
}

/*****************************************************************************
  Function      : u1_g_PwrCtrlComGetSoCResetReq
  Description   : SoCリセット要求取得処理
  param[in/out] : none
  return        : SoCリセット要求
  Note          : none
*****************************************************************************/
U1 u1_g_PwrCtrlComGetSoCResetReq( void )
{
    return(u1_s_PwrCtrl_Com_Rx_SoCResetReq);
}

/*****************************************************************************
  Function      : u1_g_PwrCtrlComGetSTRMode
  Description   : STRモード取得処理
  param[in/out] : none
  return        : STRモード
  Note          : none
*****************************************************************************/
U1 u1_g_PwrCtrlComGetSTRMode( void )
{
    return(u1_s_PwrCtrl_Com_Rx_STRModeInfo);
}

/*****************************************************************************
  Function      : u1_g_PwrCtrlComGetSpiFail
  Description   : SPI通信途絶監視結果取得処理
  param[in/out] : none
  return        : SPI通信途絶監視結果
  Note          : none
*****************************************************************************/
U1 u1_g_PwrCtrlComGetSpiFail( void )
{
    return(u1_s_PwrCtrl_Com_Rx_SpiFail);
}

/*****************************************************************************
  Function      : u1_g_PwrCtrlComGetNMDiagReset
  Description   : NMダイアグリセット検知状態取得処理
  param[in/out] : none
  return        : NMダイアグリセット
  Note          : none
*****************************************************************************/
U1 u1_g_PwrCtrlComGetNMDiagReset( void )
{
    return(u1_s_PwrCtrl_Com_Rx_NMDiagReset);
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlComTxTask
  Description   : VM間通信送信定期処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlComTxTask( void )
{
    /* SIP電源再起動通知 */
    vd_g_iVDshWribyDid((U2)PWRCTRL_COM_VMTXID_VM2_PWRON, &u4_s_PwrCtrl_Com_Tx_PwrOn, (U2)PWRCTRL_COM_PWRON_LEN);

    /* SIP異常検知通知 */
    vd_g_iVDshWribyDid((U2)PWRCTRL_COM_VMTXID_VM2_PWRERR, &u4_s_PwrCtrl_Com_Tx_PwrErr, (U2)PWRCTRL_COM_PWRERR_LEN);

    /* SoC起動回数カウンタ */
    vd_g_iVDshWribyDid((U2)PWRCTRL_COM_VMTXID_VM2_SOCONCOUNT, &u4_s_PwrCtrl_Com_Tx_SoCOnCount, (U2)PWRCTRL_COM_COUNT_LEN);

    /* SoC起動回数カウンタ更新時の時間 */
    vd_g_iVDshWribyDid((U2)PWRCTRL_COM_VMTXID_VM2_SOCONTIME, &u4_s_PwrCtrl_Com_Tx_SoCOnTime, (U2)PWRCTRL_COM_TIME_LEN);

    /* 起動ログ計測点検知データ */
    vd_s_PwrCtrlComEthLinkupStsSet(); /* Ethリンクアップ状態更新処理 */
    vd_g_iVDshWribyDid((U2)PWRCTRL_COM_VMTXID_VM2_BOOTLOGINF, &u4_s_PwrCtrl_Com_Tx_BootLog, (U2)PWRCTRL_COM_BOOTLOG_LEN);

    /* SoC起動状態 */
    vd_g_iVDshWribyDid((U2)PWRCTRL_COM_VMTXID_VM1_SOCPOWER, &u4_s_PwrCtrl_Com_Tx_SoCPower, (U2)PWRCTRL_COM_SOCPOWER_LEN);

    /* SoC起動条件通知 */
    vd_g_iVDshWribyDid((U2)PWRCTRL_COM_VMTXID_VM1_SOCWKUPCOND, &u4_s_PwrCtrl_Com_Tx_SoCWkupCond, (U2)PWRCTRL_COM_SOCWKUPCOND_LEN);

    /* ユーザーリセット抑止区間通知 */
    vd_g_iVDshWribyDid((U2)PWRCTRL_COM_VMTXID_VM1_USRRSTMASK, &u4_s_PwrCtrl_Com_Tx_UsrRstMask, (U2)PWRCTRL_COM_USRRSTMASK_LEN);

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlComTxClr
  Description   : VM間通信送信データクリア処理(前回値を送信しないデータのクリア)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlComTxClr( void )
{
    /* SIP電源再起動通知 */
    u4_s_PwrCtrl_Com_Tx_PwrOn = (U4)PWRCTRL_COM_PWRON_NOINFO;

    /* SIP異常検知通知 */
    u4_s_PwrCtrl_Com_Tx_PwrErr = (U4)PWRCTRL_COM_PWRERR_NOERR;

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlComTxSetPwrOn
  Description   : SIP電源再起動通知設定処理
  param[in/out] : [In] const U1 u1_a_data SIP電源再起動通知データ
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlComTxSetPwrOn( const U1 u1_a_data )
{
    if(u4_s_PwrCtrl_Com_Tx_PwrOn == (U4)PWRCTRL_COM_PWRON_NOINFO)
    {
        u4_s_PwrCtrl_Com_Tx_PwrOn = (U4)u1_a_data;
    }

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlComTxSetPwrErr
  Description   : SIP異常検知通知設定処理
  param[in/out] : [In] const U1 u1_a_data SIP異常検知通知データ
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlComTxSetPwrErr( const U1 u1_a_data )
{
    if(u4_s_PwrCtrl_Com_Tx_PwrErr == (U4)PWRCTRL_COM_PWRERR_NOERR)
    {
        u4_s_PwrCtrl_Com_Tx_PwrErr = (U4)u1_a_data;
    }

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlComRxVm1Stby
  Description   : VM1スタンバイ条件成立有無受信処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlComRxVm1Stby( void )
{
    U4 u4_t_buf;        /* VM間通信受信データ格納バッファ */
    U1 u1_t_vm_data;    /* VM間通信受信データ */
    U1 u1_t_vm_ret;     /* VM間通信戻り値 */

    u4_t_buf = (U4)PWRCTRL_COM_RCVBUF_CLR;

    /* VM間通信で取得 */
    u1_t_vm_ret = u1_g_iVDshReabyDid((U2)PWRCTRL_COM_VMRXID_VM1_STBY, &u4_t_buf, (U2)PWRCTRL_COM_STBY_LEN);

    /* 受信OK */
    if(u1_t_vm_ret != (U1)IVDSH_NO_REA)
    {
        u1_t_vm_data = (U1)(u4_t_buf & (U4)PWRCTRL_COM_1BYTEMASK);

        /* 有効値受信時のみ更新 */
        if((u1_t_vm_data == (U1)PWRCTRL_COM_STBY_OK)
        || (u1_t_vm_data == (U1)PWRCTRL_COM_STBY_NG))
        {
            u1_s_PwrCtrl_Com_Rx_Vm1StbyInfo = u1_t_vm_data;
        }
    }

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlComRxVm2Stby
  Description   : VM2スタンバイ条件成立有無受信処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlComRxVm2Stby( void )
{
    U4 u4_t_buf;        /* VM間通信受信データ格納バッファ */
    U1 u1_t_vm_data;    /* VM間通信受信データ */
    U1 u1_t_vm_ret;     /* VM間通信戻り値 */

    u4_t_buf = (U4)PWRCTRL_COM_RCVBUF_CLR;

    /* VM間通信で取得 */
    u1_t_vm_ret = u1_g_iVDshReabyDid((U2)PWRCTRL_COM_VMRXID_VM2_STBY, &u4_t_buf, (U2)PWRCTRL_COM_STBY_LEN);

    /* 受信OK */
    if(u1_t_vm_ret != (U1)IVDSH_NO_REA)
    {
        u1_t_vm_data = (U1)(u4_t_buf & (U4)PWRCTRL_COM_1BYTEMASK);

        /* 有効値受信時のみ更新 */
        if((u1_t_vm_data == (U1)PWRCTRL_COM_STBY_OK)
        || (u1_t_vm_data == (U1)PWRCTRL_COM_STBY_NG))
        {
            u1_s_PwrCtrl_Com_Rx_Vm2StbyInfo = u1_t_vm_data;
        }
    }

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlComRxForceSleep
  Description   : 強制スリープ条件成立有無受信処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlComRxForceSleep( void )
{
    U4 u4_t_buf;        /* VM間通信受信データ格納バッファ */
    U1 u1_t_vm_data;    /* VM間通信受信データ */
    U1 u1_t_vm_ret;     /* VM間通信戻り値 */

    u4_t_buf = (U4)PWRCTRL_COM_RCVBUF_CLR;

    /* VM間通信で取得 */
    u1_t_vm_ret = u1_g_iVDshReabyDid((U2)PWRCTRL_COM_VMRXID_VM1_FSLP, &u4_t_buf, (U2)PWRCTRL_COM_FSLP_LEN);

    /* 受信OK */
    if(u1_t_vm_ret != (U1)IVDSH_NO_REA)
    {
        u1_t_vm_data = (U1)(u4_t_buf & (U4)PWRCTRL_COM_1BYTEMASK);

        /* 有効値受信時のみ更新 */
        if((u1_t_vm_data == (U1)PWRCTRL_COM_FSLP_ON)
        || (u1_t_vm_data == (U1)PWRCTRL_COM_FSLP_OFF))
        {
            u1_s_PwrCtrl_Com_Rx_FsleepInfo = u1_t_vm_data;
        }
    }

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlComVMRxSoCSts
  Description   : VM間通信：動作ステータス通知受信処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlComRxSoCSts( void )
{
    U4 u4_t_buf;        /* VM間通信受信データ格納バッファ */
    U1 u1_t_vm_ret;     /* VM間通信戻り値 */
    
    u4_t_buf = (U4)PWRCTRL_COM_RCVBUF_CLR;
    
    /* VM間通信で取得 */
    u1_t_vm_ret = u1_g_iVDshReabyDid((U2)PWRCTRL_COM_VMRXID_VM2_SOCSTS, &u4_t_buf, (U2)PWRCTRL_COM_SOCSTS_LEN);

    /* 受信OK */
    if(u1_t_vm_ret != (U1)IVDSH_NO_REA){
        u1_s_PwrCtrl_Com_Rx_SoCResetReq = (U1)((u4_t_buf & (U4)PWRCTRL_COM_2BYTEMASK) >> (U1)PWRCTRL_COM_1BYTESHIFT );
        u1_s_PwrCtrl_Com_Rx_SoCSts = (U1)(u4_t_buf & (U4)PWRCTRL_COM_1BYTEMASK);
    }

    /* WAKEUP-STAT1更新判定 */
    if(u1_s_PwrCtrl_Com_Rx_SoCSts == (U1)PWRCTRL_COM_SOCSTS_COMP){
        /* WAKEUP-STAT1更新要求 */
        vd_g_PwrCtrlSipSoCOnComp();
        /* ユーザーリセット抑止解除受付状態が有効の場合 */
        if(u1_s_PwrCtrl_Com_URMaskOffSts == (U1)PWRCTRL_COM_URMASKOFF_ENABLED)
        {
            /* ユーザーリセット抑止区間通知：未設定 */
            vd_g_PwrCtrlComTxSetUsrRstMask((U1)PWRCTRL_COM_USRRSTMASK_OFF);
            /* ユーザーリセット抑止解除受付状態：無効 */
            vd_g_PwrCtrlComSetURMaskOffSts((U1)PWRCTRL_COM_URMASKOFF_DISABLED);
        }
    }
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlComRxSTR
  Description   : STRモード状態通知データ設定処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlComRxSTR( void )
{
    U4 u4_t_buf;        /* VM間通信受信データ格納バッファ */
    U1 u1_t_vm_data;    /* VM間通信受信データ */
    U1 u1_t_vm_ret;     /* VM間通信戻り値 */
    
    u4_t_buf = (U4)PWRCTRL_COM_RCVBUF_CLR;
    
    /* VM間通信で取得 */
    u1_t_vm_ret = u1_g_iVDshReabyDid((U2)PWRCTRL_COM_VMRXID_VM2_STR, &u4_t_buf, (U2)PWRCTRL_COM_STR_LEN);

    /* 受信OK */
    if(u1_t_vm_ret != (U1)IVDSH_NO_REA){
        u1_t_vm_data = (U1)(u4_t_buf & (U4)PWRCTRL_COM_1BYTEMASK);

        /* 有効値受信時のみ更新 */
        if((u1_t_vm_data == (U1)PWRCTRL_COM_STR_ON)
        || (u1_t_vm_data == (U1)PWRCTRL_COM_STR_OFF))
        {
            u1_s_PwrCtrl_Com_Rx_STRModeInfo = u1_t_vm_data;
        }
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlComRxSpiFail
  Description   : SPI通信途絶監視結果受信処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlComRxSpiFail( void )
{
    U4 u4_t_buf;        /* VM間通信受信データ格納バッファ */
    U1 u1_t_vm_data;    /* VM間通信受信データ */
    U1 u1_t_vm_ret;     /* VM間通信戻り値 */
    
    u4_t_buf = (U4)PWRCTRL_COM_RCVBUF_CLR;
    
    /* VM間通信で取得 */
    u1_t_vm_ret = u1_g_iVDshReabyDid((U2)PWRCTRL_COM_VMRXID_VM1_SPIFAIL, &u4_t_buf, (U2)PWRCTRL_COM_SPIFAIL_LEN);

    /* 受信OK */
    if(u1_t_vm_ret != (U1)IVDSH_NO_REA){
        u1_t_vm_data = (U1)(u4_t_buf & (U4)PWRCTRL_COM_1BYTEMASK);

        /* 有効値受信時のみ更新 */
        if((u1_t_vm_data == (U1)PWRCTRL_COM_SPIFAIL_OK)
        || (u1_t_vm_data == (U1)PWRCTRL_COM_SPIFAIL_NG))
        {
            u1_s_PwrCtrl_Com_Rx_SpiFail = u1_t_vm_data;
        }
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlComRxNMDiagReset
  Description   : NMダイアグリセット要求データ設定処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlComRxNMDiagReset( void )
{
    U4 u4_t_buf;        /* VM間通信受信データ格納バッファ */
    U1 u1_t_vm_data;    /* VM間通信受信データ */
    U1 u1_t_vm_ret;     /* VM間通信戻り値 */
    
    u4_t_buf = (U4)PWRCTRL_COM_RCVBUF_CLR;
    
    /* VM間通信で取得 */
    u1_t_vm_ret = u1_g_iVDshReabyDid((U2)PWRCTRL_COM_VMRXID_VM1_NMDIAG, &u4_t_buf, (U2)PWRCTRL_COM_NMDIAG_LEN);

    /* 受信OK */
    if(u1_t_vm_ret != (U1)IVDSH_NO_REA){
        u1_t_vm_data = (U1)(u4_t_buf & (U4)PWRCTRL_COM_1BYTEMASK);

        /* 有効値受信時のみ更新 */
        if((u1_t_vm_data == (U1)PWRCTRL_COM_NMDIAGRESET_NON)
        || (u1_t_vm_data == (U1)PWRCTRL_COM_NMDIAGRESET_REQ))
        {
            u1_s_PwrCtrl_Com_Rx_NMDiagReset = u1_t_vm_data;
        }
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlComEthLinkup
  Description   : Ethリンクアップ状態通知処理
  param[in/out] : [In] const U1 u1_a_det 起動ログ計測点設定要求
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlComEthLinkup( const U1 u1_a_det )
{
    /* 正常値が通知された場合のみ状態を更新する */
    if((u1_a_det == (U1)PWRCTRL_COM_ETH_LINKUP_NODETECT) ||
       (u1_a_det == (U1)PWRCTRL_COM_ETH_LINKUP_DETECT)){
        /* Ethリンクアップ状態を更新 */
        u1_s_PwrCtrl_Com_Eth_LinkupSts = u1_a_det;
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlComTxSetBootLog
  Description   : 起動ログ計測点検知データ設定処理
  param[in/out] : [In] const U1 u1_a_req 起動ログ計測点設定要求
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlComTxSetBootLog( const U1 u1_a_req )
{
    if(u1_a_req == (U1)PWRCTRL_COM_BOOTLOG_BONREQ){
        /* Soc起動時の計測点を検知 */
        u4_s_PwrCtrl_Com_Tx_BootLog |= (U4)PWRCTRL_COM_BOOTLOG_BON_SET;
    }
    else if(u1_a_req == (U1)PWRCTRL_COM_BOOTLOG_STRREQ){
        /* STRWake時の計測点を検知 */
        u4_s_PwrCtrl_Com_Tx_BootLog |= (U4)PWRCTRL_COM_BOOTLOG_STR_SET;
    }
    else if(u1_a_req == (U1)PWRCTRL_COM_BOOTLOG_ETHREQ){
        /* Ethリンクアップ時の計測点を検知 */
        u4_s_PwrCtrl_Com_Tx_BootLog |= (U4)PWRCTRL_COM_BOOTLOG_ETH_SET;
    }
    else{
        /* 未定義の要求が通知された場合は何もしない */
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlComTxClrBootLog
  Description   : 起動ログ計測点検知データ設定処理
  param[in/out] : [In] const U1 u1_a_req 起動ログ計測点クリア要求
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlComTxClrBootLog( const U1 u1_a_req )
{
    if(u1_a_req == (U1)PWRCTRL_COM_BOOTLOG_INITREQ){
        /* 全計測点に未検知を設定 */
        u4_s_PwrCtrl_Com_Tx_BootLog = (U4)PWRCTRL_COM_BOOTLOG_NON;
    }
    else if(u1_a_req == (U1)PWRCTRL_COM_BOOTLOG_BONREQ){
        /* Soc起動を未検知にクリア */
        u4_s_PwrCtrl_Com_Tx_BootLog &= (U4)PWRCTRL_COM_BOOTLOG_BON_RESET;
    }
    else if(u1_a_req == (U1)PWRCTRL_COM_BOOTLOG_STRREQ){
        /* STRWakeを未検知にクリア */
        u4_s_PwrCtrl_Com_Tx_BootLog &= (U4)PWRCTRL_COM_BOOTLOG_STR_RESET;
    }
    else if(u1_a_req == (U1)PWRCTRL_COM_BOOTLOG_ETHREQ){
        /* Ethリンクアップに未検知を設定 */
        u4_s_PwrCtrl_Com_Tx_BootLog &= (U4)PWRCTRL_COM_BOOTLOG_ETH_RESET;
    }
    else{
        /* 未定義の要求が通知された場合は何もしない */
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlComTxSetSoCOnStart
  Description   : SoC起動通知データ設定処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlComTxSetSoCOnStart( void )
{
    /* SoC起動回数カウンタ更新 */
    if(u4_s_PwrCtrl_Com_Tx_SoCOnCount >= (U4)PWRCTRL_COM_SOCONCOUNT_MAX){
        u4_s_PwrCtrl_Com_Tx_SoCOnCount = (U4)PWRCTRL_COM_SOCONCOUNT_INIT;
    }
    else{
        u4_s_PwrCtrl_Com_Tx_SoCOnCount++;
    }
    vd_g_Rim_WriteU2((U2)RIMID_U2_PWCTR_SOC_ON_COUNT, (U2)(u4_s_PwrCtrl_Com_Tx_SoCOnCount & (U4)PWRCTRL_COM_LOW2BMASK));

    /* SoC起動回数カウンタ更新時の時間取得 */
    u4_s_PwrCtrl_Com_Tx_SoCOnTime = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA);
    vd_g_Rim_WriteU4((U2)RIMID_U4_PWCTR_SOC_ON_TIME, u4_s_PwrCtrl_Com_Tx_SoCOnTime); 

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlComTxSetSoCPower
  Description   : SoC起動状態通知データ設定処理
  param[in/out] : [In] const U1 u1_a_data SoC起動状態通知データ
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlComTxSetSoCPower( const U1 u1_a_data )
{
    u4_s_PwrCtrl_Com_Tx_SoCPower = (U4)u1_a_data;

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlComTxSetSoCWkupCond
  Description   : 起動条件通知データ設定処理
  param[in/out] : [In] const U1 u1_a_data SoC起動条件通知データ
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlComTxSetSoCWkupCond( const U1 u1_a_data )
{
    u4_s_PwrCtrl_Com_Tx_SoCWkupCond = (U4)u1_a_data;

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlComTxSetUsrRstMask
  Description   : ユーザーリセット抑止区間通知データ設定処理
  param[in/out] : [In] const U1 u1_a_data ユーザーリセット抑止区間通知データ
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlComTxSetUsrRstMask( const U1 u1_a_data )
{
    u4_s_PwrCtrl_Com_Tx_UsrRstMask = (U4)u1_a_data;
    vd_g_Rim_WriteU4((U2)RIMID_U4_PWCTR_SOC_USRRSTMASK, u4_s_PwrCtrl_Com_Tx_UsrRstMask);

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlComEthLinkupStsSet
  Description   : Ethリンクアップ状態反映処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlComEthLinkupStsSet( void )
{
    /* Ethリンクアップ状態:検知の場合 */
    if(u1_s_PwrCtrl_Com_Eth_LinkupSts == (U1)PWRCTRL_COM_ETH_LINKUP_DETECT){
        /* 起動ログ計測点検知設定処理をコール */
        vd_g_PwrCtrlComTxSetBootLog((U1)PWRCTRL_COM_BOOTLOG_ETHREQ);
    }
    /* Ethリンクアップ状態:未検知の場合 */
    else if(u1_s_PwrCtrl_Com_Eth_LinkupSts == (U1)PWRCTRL_COM_ETH_LINKUP_NODETECT){
        /* 起動ログ計測点未検知設定処理をコール */
        vd_g_PwrCtrlComTxClrBootLog((U1)PWRCTRL_COM_BOOTLOG_ETHREQ);
    }
    /* Ethリンクアップ状態:異常値の場合 */
    else{
        /* 何もしない */
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlComSetURMaskOffSts
  Description   : ユーザーリセット抑止解除受付状態設定処理
  param[in/out] : [In] const U1 u1_a_req 受付状態
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlComSetURMaskOffSts( const U1 u1_a_req )
{
    u1_s_PwrCtrl_Com_URMaskOffSts = u1_a_req;

    return;
}

/****************************************************************************/
/* Service API                                                              */
/****************************************************************************/
/**** End of File ***********************************************************/
