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
#define PWRCTRL_COM_VMRXID_VM1_STBY        (IVDSH_DID_REA_CPREQ_002)   /* VM1スタンバイ条件成立有無 */
#define PWRCTRL_COM_VMRXID_VM2_STBY        (IVDSH_DID_REA_CPREQ_003)   /* VM2スタンバイ条件成立有無 */
#define PWRCTRL_COM_VMRXID_VM1_FSLP        (IVDSH_DID_REA_CPREQ_044)   /* VM1強制スリープ条件成立有無 */
#define PWRCTRL_COM_VMRXID_VM2_SOCSTS      (IVDSH_DID_REA_CPREQ_047)   /* VM2動作ステータス通知 */

/* データ長(word) */
#define PWRCTRL_COM_STBY_LEN               (1U)         /* スタンバイ条件成立有無データ長 */
#define PWRCTRL_COM_FSLP_LEN               (1U)         /* スタンバイ条件成立有無データ長 */
#define PWRCTRL_COM_SOCSTS_LEN             (1U)         /* 動作ステータス通知データ長 */

/* SoC動作状態 */
#define PWRCTRL_COM_SOCSTS_COMP            (0x04U)      /* SoC動作状態:SoC起動完了 */
#define PWRCTRL_COM_RCVBUF_CLR             (0U)         /* 格納先バッファ初期化用 */

/* 送信用 */
/* DID */
#define PWRCTRL_COM_VMTXID_VM2_PWRON       (IVDSH_DID_WRI_CPREQ_045)   /* SIP電源再起動通知 */
#define PWRCTRL_COM_VMTXID_VM2_PWRERR      (IVDSH_DID_WRI_CPREQ_005)   /* SIP異常検知通知 */
#define PWRCTRL_COM_VMTXID_VM2_SOCONCOUNT  (IVDSH_DID_WRI_CPREQ_048)   /* SoC起動回数カウンタ */
#define PWRCTRL_COM_VMTXID_VM2_SOCONTIME   (IVDSH_DID_WRI_CPREQ_049)   /* Soc起動回数カウンタ更新時間 */

/* データ長(word) */
#define PWRCTRL_COM_PWRON_LEN              (1U)         /* SIP電源再起動通知データ長 */
#define PWRCTRL_COM_PWRERR_LEN             (1U)         /* SIP異常検知通知データ長 */
#define PWRCTRL_COM_COUNT_LEN              (1U)         /* データ長:1word */
#define PWRCTRL_COM_TIME_LEN               (1U)         /* データ長:1word */

/* SoC起動回数カウンタ */
#define PWRCTRL_COM_SOCONCOUNT_MAX         (0xFFFFU)    /* 最大値 */
#define PWRCTRL_COM_SOCONCOUNT_INIT        (0x0000U)    /* 初期値 */

/* SoC起動回数カウンタ更新時の時間 */
#define PWRCTRL_COM_SOCONTIME_INIT         (0U)         /* 初期値 */

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

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
static U1 u1_s_PwrCtrl_Com_Rx_Vm1StbyInfo;   /* VM1スタンバイ条件成立有無 */
static U1 u1_s_PwrCtrl_Com_Rx_Vm2StbyInfo;   /* VM2スタンバイ条件成立有無 */
static U1 u1_s_PwrCtrl_Com_Rx_FsleepInfo;    /* 強制スリープ条件成立有無 */
static U1 u1_s_PwrCtrl_Com_Rx_SoCSts;        /* SoC動作状態 */
static U1 u1_s_PwrCtrl_Com_Rx_SoCResetReq;   /* SoCリセット要求 */
static U4 u4_s_PwrCtrl_Com_Tx_PwrOn;         /* SIP電源再起動通知 */
static U4 u4_s_PwrCtrl_Com_Tx_PwrErr;        /* SIP異常検知通知 */
static U4 u4_s_PwrCtrl_Com_Tx_SoCOnCount;    /* SoC起動回数カウンタ */
static U4 u4_s_PwrCtrl_Com_Tx_SoCOnTime;     /* SoC起動回数カウンタ更新時の時間 */

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
    u4_s_PwrCtrl_Com_Tx_PwrOn = (U4)PWRCTRL_COM_PWRON_NOINFO;       /* SIP電源再起動通知 */
    u4_s_PwrCtrl_Com_Tx_PwrErr = (U4)PWRCTRL_COM_PWRERR_NOERR;      /* SIP異常検知通知 */
    u4_s_PwrCtrl_Com_Tx_SoCOnCount = (U4)PWRCTRL_COM_SOCONCOUNT_INIT;   /* SoC起動回数カウンタ */
    vd_g_Rim_WriteU2((U2)RIMID_U2_PWCTR_SOC_ON_COUNT, (U2)(u4_s_PwrCtrl_Com_Tx_SoCOnCount & PWRCTRL_COM_LOW2BMASK));

    u4_s_PwrCtrl_Com_Tx_SoCOnTime = (U4)PWRCTRL_COM_SOCONTIME_INIT;     /* SoC起動回数カウンタ更新時の時間 */
    vd_g_Rim_WriteU4((U2)RIMID_U4_PWCTR_SOC_ON_TIME, u4_s_PwrCtrl_Com_Tx_SoCOnTime); 

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
    U2 u2_t_soccount_buf;
    U1 u1_t_soctime_ret;
    U1 u1_t_soccount_ret;
    
    u1_s_PwrCtrl_Com_Rx_Vm1StbyInfo = (U1)PWRCTRL_COM_STBY_OK;      /* VM1スタンバイ条件成立有無 */
    u1_s_PwrCtrl_Com_Rx_Vm2StbyInfo = (U1)PWRCTRL_COM_STBY_OK;      /* VM2スタンバイ条件成立有無 */
    u1_s_PwrCtrl_Com_Rx_FsleepInfo = (U1)PWRCTRL_COM_FSLP_OFF;      /* 強制スリープ条件成立有無 */
    u4_s_PwrCtrl_Com_Tx_PwrOn = (U4)PWRCTRL_COM_PWRON_NOINFO;       /* SIP電源再起動通知 */
    u4_s_PwrCtrl_Com_Tx_PwrErr = (U4)PWRCTRL_COM_PWRERR_NOERR;      /* SIP異常検知通知 */

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
        u4_s_PwrCtrl_Com_Tx_SoCOnCount = (U4)PWRCTRL_COM_SOCONTIME_INIT;
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
        u1_s_PwrCtrl_Com_Rx_SoCResetReq = (U1)((u4_t_buf & PWRCTRL_COM_2BYTEMASK) >> PWRCTRL_COM_1BYTESHIFT );
        u1_s_PwrCtrl_Com_Rx_SoCSts = (U1)(u4_t_buf & PWRCTRL_COM_1BYTEMASK);
    }

    /* WAKEUP-STAT1更新判定 */
    if(u1_s_PwrCtrl_Com_Rx_SoCSts == (U1)PWRCTRL_COM_SOCSTS_COMP){
        /* WAKEUP-STAT1更新要求 */
        vd_g_PwrCtrlSipSoCOnComp();
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
    vd_g_Rim_WriteU2((U2)RIMID_U2_PWCTR_SOC_ON_COUNT, (U2)(u4_s_PwrCtrl_Com_Tx_SoCOnCount & PWRCTRL_COM_LOW2BMASK));

    /* SoC起動回数カウンタ更新時の時間取得 */
    u4_s_PwrCtrl_Com_Tx_SoCOnTime = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA);
    vd_g_Rim_WriteU4((U2)RIMID_U4_PWCTR_SOC_ON_TIME, u4_s_PwrCtrl_Com_Tx_SoCOnTime); 

    return;
}

/****************************************************************************/
/* Service API                                                              */
/****************************************************************************/
/**** End of File ***********************************************************/
