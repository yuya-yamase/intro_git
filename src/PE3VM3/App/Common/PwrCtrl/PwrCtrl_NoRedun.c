/* PwrCtrl_NoRedun_c_v1-0-0                                                 */
/****************************************************************************/
/* Copyright (C) 2024 Denso Techno Co.,Ltd. All rights reserved.            */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | PwrCtrl_NoRedun/CODE                                      */
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
/* Power-IC 電源制御 */
#define MCU_STEP_P_IC_OVERALL_1         (1U)    /* "HexagonDSP MUTE設定完了通知"送信受領まで待機 */
#define MCU_STEP_P_IC_OVERALL_2         (2U)    /* wait min 55ms */
#define MCU_STEP_P_IC_OVERALL_3         (3U)    /* MUTE設定 (IB2読出し) */
#define MCU_STEP_P_IC_OVERALL_4         (4U)    /* MUTE設定 (IB2[0x82].D4=0,IB2[0x82].D3=0) */
#define MCU_STEP_P_IC_OVERALL_5         (5U)    /* wait 100ms */
#define MCU_STEP_P_IC_OVERALL_6         (6U)    /* Amp Off設定 (IB7読出し) */
#define MCU_STEP_P_IC_OVERALL_7         (7U)    /* Amp Off設定 (IB7[0x87].D0=0) */
#define MCU_STEP_P_IC_OVERALL_8         (8U)    /* wait min 5ms , スタンバイ P-ON=L */
#define MCU_STEP_P_IC_OVERALL_9         (9U)    /* Sys電源 V33-PERI-ON=L , wait min 100ms , P-IC電源制限 PIC-POFF=L */
#define MCU_STEP_P_IC_OVERALL_FIN       (10U)

#define MCU_OFFWAIT_POWERIC_5MS         (  5U   / PWRCTRL_CFG_TASK_TIME)
#define MCU_OFFWAIT_POWERIC_55MS        ( 55U   / PWRCTRL_CFG_TASK_TIME)
#define MCU_OFFWAIT_POWERIC_100MS       (100U   / PWRCTRL_CFG_TASK_TIME)

/* XMTuner */
#define MCU_STEP_XMTUNER_OVERALL_1      (1U)
#define MCU_STEP_XMTUNER_OVERALL_2      (2U)
#define MCU_STEP_XMTUNER_OVERALL_3      (3U)
#define MCU_STEP_XMTUNER_OVERALL_FIN    (4U)

#define MCU_OFFWAIT_XMTUNER_10MS        ( 10U   / PWRCTRL_CFG_TASK_TIME)
#define MCU_OFFWAIT_XMTUNER_5MS         (  5U   / PWRCTRL_CFG_TASK_TIME)

/* GNSS */
#define MCU_STEP_GNSS_OVERALL_1         (1U)    /* MM_STBY_N,/Bu-DTE端子監視 */
#define MCU_STEP_GNSS_OVERALL_2         (2U)    /* MM_STBY_=H→L時における、/GPT-RST監視,GPS-PCTL操作 */
#define MCU_STEP_GNSS_OVERALL_3         (3U)    /* /Bu-DTE=H→L時における、/GPT-RST監視,GPS-PCTL操作 */
#define MCU_STEP_GNSS_OVERALL_4         (4U)    /* GPS-PMONIポーリング */
#define MCU_STEP_GNSS_OVERALL_5         (5U)    /* wait t1,GPS-PCTL操作 */
#define MCU_STEP_GNSS_OVERALL_FIN       (6U)

#define MCU_OFFWAIT_GNSS_10MS           (  10U   / PWRCTRL_CFG_TASK_TIME)
#define MCU_OFFWAIT_GNSS_100MS          ( 100U   / PWRCTRL_CFG_TASK_TIME)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* メイン状態遷移管理用テーブル向け 各シーケンスのON/OFF/NONを管理する構造体定義 */
typedef struct {
    U1 u1_metbb_sts;
    U1 u1_disp_sts;
    U1 u1_hub_sts;
} ST_PWRCTRL_NOREDUN_NXYSTS;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/* ON/OFFシーケンス起動要求 */
U1  u1_g_PwrCtrl_NoRedun_Pwr_Sts;

/* 非冗長電源制御実行状態 */
static U1 u1_s_PwrCtrl_NoRedun_Step_Sts;

/* 状態遷移管理用ステータス */
static U1  u1_s_PwrCtrl_NoRedun_Sts;

/* 実行中のONシーケンス管理 */
static U1  u1_s_PwrCtrl_NoRedun_OnSequence;

/* 非冗長電源間ウェイトタイムカウンタ */
static U2  u2_s_PwrCtrl_NoRedun_BetWait_Time;

/* (Meter+BB Display ON/OFF Sequence */
static U1 u1_s_PwrCtrl_NoRedun_MetBB_Chk;
static U1 u1_s_PwrCtrl_NoRedun_MetBB_OnStep;
static U1 u1_s_PwrCtrl_NoRedun_MetBB_OffStep;
static U2 u2_s_PwrCtrl_NoRedun_MBon_Time;
static U2 u2_s_PwrCtrl_NoRedun_Gviftx_Mbwk_Time;
static U2 u2_s_PwrCtrl_NoRedun_Gviftx_Mbwk_Off_Time;
static U2 u2_s_PwrCtrl_NoRedun_MBoff_Time;

/* Center Display ON/OFF Sequence */
static U1 u1_s_PwrCtrl_NoRedun_Disp_Chk;
static U1 u1_s_PwrCtrl_NoRedun_Disp_OnStep;
static U1 u1_s_PwrCtrl_NoRedun_Disp_OffStep;
static U2 u2_s_PwrCtrl_NoRedun_Dspon_Time;
static U2 u2_s_PwrCtrl_NoRedun_Gviftx_Dspwk_Time;
static U2 u2_s_PwrCtrl_NoRedun_Gviftx_Dspwk_Off_Time;
static U2 u2_s_PwrCtrl_NoRedun_Dspoff_Time;

/* DSRC(HUB) ON/OFF Sequence */
static U1 u1_s_PwrCtrl_NoRedun_Hub_Chk;
static U1 u1_s_PwrCtrl_NoRedun_Hub_OnStep;
static U1 u1_s_PwrCtrl_NoRedun_Hub_OffStep;
static U2 u2_s_PwrCtrl_NoRedun_Hubon_Time;
static U2 u2_s_PwrCtrl_NoRedun_Hubwk_Time;
static U2 u2_s_PwrCtrl_NoRedun_Hubwk_Off_Time;
static U2 u2_s_PwrCtrl_NoRedun_Huboff_Time;

/* SYS系デバイス終了状態 */
uint16        Mcu_Dev_Pwroff_Sts;  /* exturn */
static uint8  Mcu_OffStep_PowerIc;
static uint16 Mcu_OffTime_PowerIc;
static uint8  Mcu_OffStep_XMTuner;
static uint16 Mcu_OffTime_XMTuner;
static uint8  Mcu_OffStep_GNSS;
static uint16 Mcu_OffTime_GNSS;
static uint8  Mcu_OffCnt_GNSS;

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/* メイン状態遷移管理用テーブル */
/* 前回と次回の状態の組み合わせで、シーケンスの処理関数の処理内容を決定する */
/* 【todo】4.0版にて処理順序変更 */
const ST_PWRCTRL_NOREDUN_NXYSTS PWRCTRL_NOREDUN_NXTSTS[PWRCTRL_NOREDUN_STATE_NUM][PWRCTRL_NOREDUN_STATE_NUM] = {
  /* 前回状態：OFF */
  /* Meter+BB Display       CenterDisplay         DSRC(Hub) */
  { {PWRCTRL_NOREDUN_PWR_NON,   PWRCTRL_NOREDUN_PWR_NON,  PWRCTRL_NOREDUN_PWR_NON },   /* 次回状態：OFF */
    {PWRCTRL_NOREDUN_PWR_ON,    PWRCTRL_NOREDUN_PWR_NON,  PWRCTRL_NOREDUN_PWR_NON },   /* 次回状態：駐車中起動 */
    {PWRCTRL_NOREDUN_PWR_ON,    PWRCTRL_NOREDUN_PWR_ON,   PWRCTRL_NOREDUN_PWR_NON },   /* 次回状態：見た目オフ起動 */
    {PWRCTRL_NOREDUN_PWR_ON,    PWRCTRL_NOREDUN_PWR_ON,   PWRCTRL_NOREDUN_PWR_ON  }    /* 次回状態：見た目オン起動 */
  },
  
  /* 前回状態：駐車中起動 */
  /* Meter+BB Display       CenterDisplay         DSRC(Hub) */
  { {PWRCTRL_NOREDUN_PWR_OFF,   PWRCTRL_NOREDUN_PWR_OFF,  PWRCTRL_NOREDUN_PWR_OFF },   /* 次回状態：OFF */
    {PWRCTRL_NOREDUN_PWR_NON,   PWRCTRL_NOREDUN_PWR_NON,  PWRCTRL_NOREDUN_PWR_NON },   /* 次回状態：駐車中起動 */
    {PWRCTRL_NOREDUN_PWR_NON,   PWRCTRL_NOREDUN_PWR_ON,   PWRCTRL_NOREDUN_PWR_NON },   /* 次回状態：見た目オフ起動 */
    {PWRCTRL_NOREDUN_PWR_NON,   PWRCTRL_NOREDUN_PWR_ON,   PWRCTRL_NOREDUN_PWR_ON  }    /* 次回状態：見た目オン起動 */
  },

  /* 前回状態：見た目オフ起動 */
  /* Meter+BB Display       CenterDisplay         DSRC(Hub) */
  { {PWRCTRL_NOREDUN_PWR_OFF,   PWRCTRL_NOREDUN_PWR_OFF,  PWRCTRL_NOREDUN_PWR_OFF },   /* 次回状態：OFF */
    {PWRCTRL_NOREDUN_PWR_NON,   PWRCTRL_NOREDUN_PWR_OFF,  PWRCTRL_NOREDUN_PWR_NON },   /* 次回状態：駐車中起動 */
    {PWRCTRL_NOREDUN_PWR_NON,   PWRCTRL_NOREDUN_PWR_NON,  PWRCTRL_NOREDUN_PWR_NON },   /* 次回状態：見た目オフ起動 */
    {PWRCTRL_NOREDUN_PWR_NON,   PWRCTRL_NOREDUN_PWR_NON,  PWRCTRL_NOREDUN_PWR_ON  }    /* 次回状態：見た目オン起動 */
  },

  /* 前回状態：見た目オン起動 */
  /* Meter+BB Display       CenterDisplay         DSRC(Hub) */
  { {PWRCTRL_NOREDUN_PWR_OFF,   PWRCTRL_NOREDUN_PWR_OFF,  PWRCTRL_NOREDUN_PWR_OFF },   /* 次回状態：OFF */
    {PWRCTRL_NOREDUN_PWR_NON,   PWRCTRL_NOREDUN_PWR_OFF,  PWRCTRL_NOREDUN_PWR_OFF },   /* 次回状態：駐車中起動 */
    {PWRCTRL_NOREDUN_PWR_NON,   PWRCTRL_NOREDUN_PWR_NON,  PWRCTRL_NOREDUN_PWR_OFF },   /* 次回状態：見た目オフ起動 */
    {PWRCTRL_NOREDUN_PWR_NON,   PWRCTRL_NOREDUN_PWR_NON,  PWRCTRL_NOREDUN_PWR_NON }    /* 次回状態：見た目オン起動 */
  }
};

/*--------------------------------------------------------------------------*/
/* Functions                                                                */
/*--------------------------------------------------------------------------*/
/* CAN,直線入力から次回状態遷移先を決定する */
static U1 u1_s_PwrCtrlNoRedunNxtsts( void );

/* (Meter+BB Display ON/OFF Sequence */
static void vd_s_PwrCtrlNoRedunMetBB( void );
static void vd_s_PwrCtrlNoRedunPwrOnMbPwr( void );
static void vd_s_PwrCtrlNoRedunWkGvifTxMetBB( void );
static void vd_s_PwrCtrlNoRedunWkOffGvifTxMetBB( void );
static void vd_s_PwrCtrlNoRedunPwrOffMbPwr( void );

/* Center Display ON/OFF Sequence */
static void vd_s_PwrCtrlNoRedunDisp( void );
static void vd_s_PwrCtrlNoRedunPwrOnDsp( void );
static void vd_s_PwrCtrlNoRedunWkGvifTxDisp( void );
static void vd_s_PwrCtrlNoRedunWkOffGvifTxDisp( void );
static void vd_s_PwrCtrlNoRedunPwrOffDsp( void );

/* DSRC(HUB) ON/OFF  */
static void vd_s_PwrCtrlNoRedunHub( void );
static void vd_s_PwrCtrlNoRedunPwrOnHub( void );
static void vd_s_PwrCtrlNoRedunWkHub( void );
static void vd_s_PwrCtrlNoRedunWkOffHub( void );
static void vd_s_PwrCtrlNoRedunPwrOffHub( void );

/* 非冗長電源間ウェイトタイムのカウント */
static void vd_s_PwrCtrlNoRedunBetWait( void );

void  Mcu_Dev_Pwroff( void );
uint16 Mcu_Dev_Pwroff_USB( void );
uint16 Mcu_Dev_Pwroff_PictIC( void );
uint16 Mcu_Dev_Pwroff_GVIFRx( void );
uint16 Mcu_Dev_Pwroff_GVIFTx_CDisp( void );
uint16 Mcu_Dev_Pwroff_Mic( void );
uint16 Mcu_Dev_Pwroff_Ant( void );
uint16 Mcu_Dev_Pwroff_SoundMUTE( void );
uint16 Mcu_Dev_Pwroff_Most( void );
uint16 Mcu_Dev_Pwroff_PowerIC( void );
uint16 Mcu_Dev_Pwroff_XMTuner( void );
uint16 Mcu_Dev_Pwroff_GNSS( void );

/****************************************************************************/
/* Scheduled Functions                                                      */
/****************************************************************************/
/****************************************************************************/
/* Service API                                                              */
/****************************************************************************/
/*****************************************************************************
  Function      : vd_g_PwrCtrlNoRedunPwrOnStart
  Description   : 非冗長電源制御開始要求
  param[in/out] : none
  return        : none
  Note          : CAN受信した車両電源ステートに従った制御を開始
*****************************************************************************/
void vd_g_PwrCtrlNoRedunPwrOnStart( void )
{
    u1_g_PwrCtrl_NoRedun_Pwr_Sts  = (U1)PWRCTRL_NOREDUN_STS_ON;
    u1_s_PwrCtrl_NoRedun_Step_Sts = (U1)PWRCTRL_NOREDUN_STS_ON;

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlNoRedunPwrOffStart
  Description   : 非冗長電源OFF制御開始要求
  param[in/out] : none
  return        : none
  Note          : 非冗長電源OFF処理を開始
*****************************************************************************/
void vd_g_PwrCtrlNoRedunPwrOffStart( void )
{
    u1_g_PwrCtrl_NoRedun_Pwr_Sts    = (U1)PWRCTRL_NOREDUN_STS_OFF;
    u1_s_PwrCtrl_NoRedun_Step_Sts   = (U1)PWRCTRL_NOREDUN_STS_OFF;
    u1_s_PwrCtrl_NoRedun_OnSequence = (U1)PWRCTRL_NOREDUN_ONSEQ_NON;

    return;
}

/*****************************************************************************
  Function      : u1_g_PwrCtrlNoRedunGetSts
  Description   : 非冗長電源シーケンス状態問い合わせ
  param[in/out] : none
  return        : FALSE(0)：非冗長電源シーケンス実行中
                  TRUE(1) ：非冗長電源シーケンス完了
  Note          : シス検までの暫定対応あり
*****************************************************************************/
U1 u1_g_PwrCtrlNoRedunGetSts( void )
{
    U1 u1_t_ret;

    u1_t_ret = (U1)FALSE; /* 初期化：非冗長電源シーケンス実行中 */

    if ( u1_s_PwrCtrl_NoRedun_Step_Sts == (U1)PWRCTRL_NOREDUN_STS_NON )
    {
        u1_t_ret = (U1)TRUE;
    }

    return ( u1_t_ret );
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlNoRedunInit
  Description   : 初期化関数
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlNoRedunInit( void )
{
    /* 状態初期化 */
    u1_g_PwrCtrl_NoRedun_Pwr_Sts                   = (U1)PWRCTRL_NOREDUN_STS_NON;
    u1_s_PwrCtrl_NoRedun_Step_Sts                  = (U1)PWRCTRL_NOREDUN_STS_NON;

    /* 状態遷移管理用ステータスの初期化 */
    u1_s_PwrCtrl_NoRedun_Sts                       = (U1)PWRCTRL_NOREDUN_STATE_OFF;

    /* 実行中のONシーケンスの初期化 */
    u1_s_PwrCtrl_NoRedun_OnSequence                = (U1)PWRCTRL_NOREDUN_ONSEQ_NON;

    /* 非冗長電源ON/OFFトリガの初期化 */
    u1_s_PwrCtrl_NoRedun_MetBB_Chk                 = (U1)PWRCTRL_NOREDUN_PWR_NON;
    u1_s_PwrCtrl_NoRedun_Disp_Chk                  = (U1)PWRCTRL_NOREDUN_PWR_NON;
    u1_s_PwrCtrl_NoRedun_Hub_Chk                   = (U1)PWRCTRL_NOREDUN_PWR_NON;

    /* 現在起動/終了ステップの初期化 */
    u1_s_PwrCtrl_NoRedun_MetBB_OnStep              = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
    u1_s_PwrCtrl_NoRedun_Disp_OnStep               = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
    u1_s_PwrCtrl_NoRedun_Hub_OnStep                = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
    u1_s_PwrCtrl_NoRedun_MetBB_OffStep             = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
    u1_s_PwrCtrl_NoRedun_Disp_OffStep              = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
    u1_s_PwrCtrl_NoRedun_Hub_OffStep               = (U1)PWRCTRL_COMMON_PROCESS_STEP1;

    /* 待機時間測定用RAMの初期化 */
    u2_s_PwrCtrl_NoRedun_BetWait_Time              = (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN;
    u2_s_PwrCtrl_NoRedun_MBon_Time                 = (U2)PWRCTRL_NOREDUN_WAIT_TIME_INIT;
    u2_s_PwrCtrl_NoRedun_Gviftx_Mbwk_Time          = (U2)PWRCTRL_NOREDUN_WAIT_TIME_INIT;
    u2_s_PwrCtrl_NoRedun_Gviftx_Mbwk_Off_Time      = (U2)PWRCTRL_NOREDUN_WAIT_TIME_INIT;
    u2_s_PwrCtrl_NoRedun_MBoff_Time                = (U2)PWRCTRL_NOREDUN_WAIT_TIME_INIT;
    u2_s_PwrCtrl_NoRedun_Dspon_Time                = (U2)PWRCTRL_NOREDUN_WAIT_TIME_INIT;
    u2_s_PwrCtrl_NoRedun_Gviftx_Dspwk_Time         = (U2)PWRCTRL_NOREDUN_WAIT_TIME_INIT;
    u2_s_PwrCtrl_NoRedun_Gviftx_Dspwk_Off_Time     = (U2)PWRCTRL_NOREDUN_WAIT_TIME_INIT;
    u2_s_PwrCtrl_NoRedun_Dspoff_Time               = (U2)PWRCTRL_NOREDUN_WAIT_TIME_INIT;
    u2_s_PwrCtrl_NoRedun_Hubon_Time                = (U2)PWRCTRL_NOREDUN_WAIT_TIME_INIT;
    u2_s_PwrCtrl_NoRedun_Hubwk_Time                = (U2)PWRCTRL_NOREDUN_WAIT_TIME_INIT;
    u2_s_PwrCtrl_NoRedun_Hubwk_Off_Time            = (U2)PWRCTRL_NOREDUN_WAIT_TIME_INIT;
    u2_s_PwrCtrl_NoRedun_Huboff_Time               = (U2)PWRCTRL_NOREDUN_WAIT_TIME_INIT;

    /* SYS系デバイス終了状態 */
    Mcu_Dev_Pwroff_Sts                = (uint16)FALSE;
    Mcu_OffStep_PowerIc               = (uint8)MCU_STEP_P_IC_OVERALL_1;
    Mcu_OffTime_PowerIc               = (uint16)0U;
    Mcu_OffStep_XMTuner               = (uint8)MCU_STEP_XMTUNER_OVERALL_1;
    Mcu_OffTime_XMTuner               = (uint16)0U;
    Mcu_OffStep_GNSS                  = (uint8)MCU_STEP_GNSS_OVERALL_1;
    Mcu_OffTime_GNSS                  = (uint16)0U;
    Mcu_OffCnt_GNSS                   = (uint8)0U;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlNoRedunMainFunction
  Description   : メインタスク
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlNoRedunMainFunction( void )
{
    U1 u1_t_mcu_nxtsts; /* 次回状態遷移先 */
    /* 各起動要因から次回状態遷移先を決定する */
    u1_t_mcu_nxtsts = u1_s_PwrCtrlNoRedunNxtsts();

    /* 各シーケンスの処理関数の動作を決定する(ON/OFF) */
    /* NONの場合はステータス更新しない(ON/OFF動作の途中停止防止) ON⇔OFFはステータス更新する */
    if ( PWRCTRL_NOREDUN_NXTSTS[u1_s_PwrCtrl_NoRedun_Sts][u1_t_mcu_nxtsts].u1_metbb_sts != (U1)PWRCTRL_NOREDUN_PWR_NON )
    {
        u1_s_PwrCtrl_NoRedun_MetBB_Chk = PWRCTRL_NOREDUN_NXTSTS[u1_s_PwrCtrl_NoRedun_Sts][u1_t_mcu_nxtsts].u1_metbb_sts;
    }

    if ( PWRCTRL_NOREDUN_NXTSTS[u1_s_PwrCtrl_NoRedun_Sts][u1_t_mcu_nxtsts].u1_disp_sts != (U1)PWRCTRL_NOREDUN_PWR_NON )
    {
        u1_s_PwrCtrl_NoRedun_Disp_Chk  = PWRCTRL_NOREDUN_NXTSTS[u1_s_PwrCtrl_NoRedun_Sts][u1_t_mcu_nxtsts].u1_disp_sts;
    }

    if ( PWRCTRL_NOREDUN_NXTSTS[u1_s_PwrCtrl_NoRedun_Sts][u1_t_mcu_nxtsts].u1_hub_sts != (U1)PWRCTRL_NOREDUN_PWR_NON )
    {
        u1_s_PwrCtrl_NoRedun_Hub_Chk   = PWRCTRL_NOREDUN_NXTSTS[u1_s_PwrCtrl_NoRedun_Sts][u1_t_mcu_nxtsts].u1_hub_sts;
    }

    /* 各シーケンスの処理関数をコールし、状態遷移によって決定したON/OFF処理を実行する */
    /* 未実施の場合は処理関数内部のelseに突入し、なにも実施しない */
    vd_s_PwrCtrlNoRedunMetBB();
    vd_s_PwrCtrlNoRedunDisp();
    vd_s_PwrCtrlNoRedunHub();

    /* 非冗長電源間ウェイトタイムのカウント */
    /* カウント開始はシーケンスの処理関数内でRAMリセットをもって開始する */
    vd_s_PwrCtrlNoRedunBetWait();

    /* 前回状態の更新 */
    u1_s_PwrCtrl_NoRedun_Sts = u1_t_mcu_nxtsts;

    Mcu_Dev_Pwroff(); /* デバイスOFF制御 */

    if ( ( u1_g_PwrCtrl_NoRedun_Pwr_Sts      == (U1)PWRCTRL_NOREDUN_STS_ON            )  /* 非冗長電源OFF制御 */
      && ( u1_s_PwrCtrl_NoRedun_MetBB_OnStep == (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT )  /* Meter+BB Display ONシーケンス完了 */
      && ( u1_s_PwrCtrl_NoRedun_Disp_OnStep  == (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT )  /* Center Display ONシーケンス完了 */
      && ( u1_s_PwrCtrl_NoRedun_Hub_OnStep   == (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT )) /* DSRC(HUB) ONシーケンス完了 */
    {
        u1_s_PwrCtrl_NoRedun_Step_Sts = (U1)PWRCTRL_NOREDUN_STS_NON;
    }

    if ( ( u1_g_PwrCtrl_NoRedun_Pwr_Sts       == (U1)PWRCTRL_NOREDUN_STS_OFF           )  /* 非冗長電源OFF制御 */
      && ( u1_s_PwrCtrl_NoRedun_MetBB_OffStep == (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT )  /* Meter+BB Display OFFシーケンス完了 */
      && ( u1_s_PwrCtrl_NoRedun_Disp_OffStep  == (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT )  /* Center Display OFFシーケンス完了 */
      && ( u1_s_PwrCtrl_NoRedun_Hub_OffStep   == (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT )  /* DSRC(HUB) OFFシーケンス完了 */
      && ( Mcu_Dev_Pwroff_Sts                 == (uint16)PWROFF_CONP_BIT               )) /* デバイスOFF制御シーケンス完了 */
    {
        u1_s_PwrCtrl_NoRedun_Step_Sts = (U1)PWRCTRL_NOREDUN_STS_NON;
    }
    
    /* Port更新処理 */
    vd_g_McuDevPwronWritePort();

}

/*****************************************************************************
  Function      : u1_s_PwrCtrlNoRedunNxtsts
  Description   : 次回状態遷移先の決定
  param[in/out] : none
  return        : 次回状態遷移先(PWRCTRL_NOREDUN_STATE_**)
  Note          : シス検,量産までの暫定対応あり
*****************************************************************************/
static U1 u1_s_PwrCtrlNoRedunNxtsts( void )
{
    U1 u1_t_mcu_return;     /* 戻り値 */
    U1 u1_t_mcu_appea;      /* CAN入力：見た目オンオフ(スタブ) */
    U1 u1_t_mcu_VPSINFO1;   /* CAN入力：判定中 */
    U1 u1_t_mcu_VPSINFO2;   /* CAN入力：駐車中 */
    U1 u1_t_mcu_VPSINFO3;   /* CAN入力：乗車中 */
    U1 u1_t_mcu_VPSINFO4;   /* CAN入力：PowerON通常 */
    U1 u1_t_mcu_VPSINFO5;   /* CAN入力：PowerON緊急停止 */
    U1 u1_t_mcu_VPSINFO6;   /* CAN入力：駐車中高圧起動 */
    U1 u1_t_mcu_VPSINFO7;   /* CAN入力：駐車中高圧・温調起動 */
    U1 u1_t_mcu_VPSINFO;    /* 電源状態取り纏め */
    U1 u1_t_mcu_boot;       /* 開発時のみ使用する、BOOT入力取得(量産時削除予定) */

    u1_t_mcu_return   = u1_s_PwrCtrl_NoRedun_Sts;  /* 初期値：前回保持状態 */
    u1_t_mcu_appea    = (U1)FALSE;
    u1_t_mcu_VPSINFO1 = (U1)FALSE;
    u1_t_mcu_VPSINFO2 = (U1)FALSE;
    u1_t_mcu_VPSINFO3 = (U1)FALSE;
    u1_t_mcu_VPSINFO4 = (U1)FALSE;
    u1_t_mcu_VPSINFO5 = (U1)FALSE;
    u1_t_mcu_VPSINFO6 = (U1)FALSE;
    u1_t_mcu_VPSINFO7 = (U1)FALSE;
    u1_t_mcu_VPSINFO  = (U1)0U;
    u1_t_mcu_boot     = (U1)STD_LOW;

    (void)Com_ReceiveSignal( ComConf_ComSignal_VPSINFO1, &u1_t_mcu_VPSINFO1 );
    (void)Com_ReceiveSignal( ComConf_ComSignal_VPSINFO2, &u1_t_mcu_VPSINFO2 );
    (void)Com_ReceiveSignal( ComConf_ComSignal_VPSINFO3, &u1_t_mcu_VPSINFO3 );
    (void)Com_ReceiveSignal( ComConf_ComSignal_VPSINFO4, &u1_t_mcu_VPSINFO4 );
    (void)Com_ReceiveSignal( ComConf_ComSignal_VPSINFO5, &u1_t_mcu_VPSINFO5 );
    (void)Com_ReceiveSignal( ComConf_ComSignal_VPSINFO6, &u1_t_mcu_VPSINFO6 );
    (void)Com_ReceiveSignal( ComConf_ComSignal_VPSINFO7, &u1_t_mcu_VPSINFO7 );
    (void)Com_ReceiveSignal( ComConf_ComSignal_APOFRQ  , &u1_t_mcu_appea    );

    /* BOOT入力値取得処理 */
    u1_t_mcu_boot = Dio_ReadChannel(Mcu_Dio_PortId[PWRCTRL_CFG_PRIVATE_PORT_BOOT]);

    u1_t_mcu_VPSINFO =   (u1_t_mcu_appea    & (U1)TRUE) << (U1)PWRCTRL_NOREDUN_BITSFT7;  /* 8bit：見た目オンオフ */
    u1_t_mcu_VPSINFO |=  (u1_t_mcu_VPSINFO1 & (U1)TRUE) << (U1)PWRCTRL_NOREDUN_BITSFT6;  /* 7bit：CAN入力：判定中 */
    u1_t_mcu_VPSINFO |=  (u1_t_mcu_VPSINFO2 & (U1)TRUE) << (U1)PWRCTRL_NOREDUN_BITSFT5;  /* 6bit：CAN入力：駐車中 */
    u1_t_mcu_VPSINFO |=  (u1_t_mcu_VPSINFO3 & (U1)TRUE) << (U1)PWRCTRL_NOREDUN_BITSFT4;  /* 5bit：CAN入力：乗車中 */
    u1_t_mcu_VPSINFO |=  (u1_t_mcu_VPSINFO4 & (U1)TRUE) << (U1)PWRCTRL_NOREDUN_BITSFT3;  /* 4bit：CAN入力：PowerON通常 */
    u1_t_mcu_VPSINFO |=  (u1_t_mcu_VPSINFO5 & (U1)TRUE) << (U1)PWRCTRL_NOREDUN_BITSFT2;  /* 3bit：CAN入力：PowerON緊急停止 */
    u1_t_mcu_VPSINFO |=  (u1_t_mcu_VPSINFO6 & (U1)TRUE) << (U1)PWRCTRL_NOREDUN_BITSFT1;  /* 2bit：CAN入力：駐車中高圧起動 */
    u1_t_mcu_VPSINFO |=  u1_t_mcu_VPSINFO7  & (U1)TRUE;                                  /* 1bit：CAN入力：駐車中高圧・温調起動 */

    if ( u1_g_PwrCtrl_NoRedun_Pwr_Sts == (U1)PWRCTRL_NOREDUN_STS_OFF )       /* OFFトリガをリセットして次回要求に備える */
    {
        u1_t_mcu_return = (U1)PWRCTRL_NOREDUN_STATE_OFF;
    }
    else if ( u1_g_PwrCtrl_NoRedun_Pwr_Sts == (U1)PWRCTRL_NOREDUN_STS_ON )
    {
        /* 次回状態判定 電源ステートはONOFF仕様 図5-3 参照 */
        switch ( u1_t_mcu_VPSINFO )
        {
            case  PWRCTRL_NOREDUN_CHKSTS_APPON_UNCON:               /* 見た目：オン ステート：状態未定 */
                u1_t_mcu_return = u1_s_PwrCtrl_NoRedun_Sts;         /* 前回状態保持 */
                break;
            case  PWRCTRL_NOREDUN_CHKSTS_APPON_PARK:                /* 見た目：オン ステート：駐車中 */
                u1_t_mcu_return = (U1)PWRCTRL_NOREDUN_STATE_PARK;   /* 駐車中起動 */
                break;
            case  PWRCTRL_NOREDUN_CHKSTS_APPON_RIDE:                /* 見た目：オン ステート：乗車中 */
                u1_t_mcu_return = (U1)PWRCTRL_NOREDUN_STATE_APPON;  /* 見た目オン起動 */
                break;
            case  PWRCTRL_NOREDUN_CHKSTS_APPON_PONEMG:              /* 見た目：オン ステート：PowerON緊急停止 */
                u1_t_mcu_return = (U1)PWRCTRL_NOREDUN_STATE_APPON;  /* 見た目オン起動 */
                break;
            case  PWRCTRL_NOREDUN_CHKSTS_APPON_PON:                 /* 見た目：オン ステート：PowerON通常 */
                u1_t_mcu_return = (U1)PWRCTRL_NOREDUN_STATE_APPON;  /* 見た目オン起動 */
                break;
            case  PWRCTRL_NOREDUN_CHKSTS_APPON_HVOL:                /* 見た目：オン ステート：駐車中 高圧起動 */
                u1_t_mcu_return = (U1)PWRCTRL_NOREDUN_STATE_PARK;   /* 駐車中起動 */
                break;
            case  PWRCTRL_NOREDUN_CHKSTS_APPON_HVOLHCOND:           /* 見た目：オン ステート：駐車中 高圧・温調起動 */
                u1_t_mcu_return = (U1)PWRCTRL_NOREDUN_STATE_PARK;   /* 駐車中起動 */
                break;
            case  PWRCTRL_NOREDUN_CHKSTS_APPOFF_UNCON:              /* 見た目：オフ ステート：状態未定 */
                u1_t_mcu_return = (U1)u1_s_PwrCtrl_NoRedun_Sts;     /* 前回状態保持 */
                break;
            case  PWRCTRL_NOREDUN_CHKSTS_APPOFF_PARK:               /* 見た目：オフ ステート：駐車中 */
                u1_t_mcu_return = (U1)PWRCTRL_NOREDUN_STATE_PARK;   /* 駐車中起動 */
                break;
            case  PWRCTRL_NOREDUN_CHKSTS_APPOFF_RIDE:               /* 見た目：オフ ステート：乗車中 */
                u1_t_mcu_return = (U1)PWRCTRL_NOREDUN_STATE_APPOFF; /* 見た目オフ起動 */
                break;
            case  PWRCTRL_NOREDUN_CHKSTS_APPOFF_PONEMG:             /* 見た目：オフ ステート：PowerON緊急停止 */
                u1_t_mcu_return = (U1)PWRCTRL_NOREDUN_STATE_APPON;  /* 見た目オン起動 */
                break;
            case  PWRCTRL_NOREDUN_CHKSTS_APPOFF_PON:                /* 見た目：オフ ステート：PowerON通常 */
                u1_t_mcu_return = (U1)PWRCTRL_NOREDUN_STATE_APPON;  /* 見た目オン起動 */
                break;
            case  PWRCTRL_NOREDUN_CHKSTS_APPOFF_HVOL:               /* 見た目：オフ ステート：駐車中 高圧起動 */
                u1_t_mcu_return = (U1)PWRCTRL_NOREDUN_STATE_PARK;   /* 駐車中起動 */
                break;
            case  PWRCTRL_NOREDUN_CHKSTS_APPOFF_HVOLHCOND:          /* 見た目：オフ ステート：駐車中 高圧・温調起動 */
                u1_t_mcu_return = (U1)PWRCTRL_NOREDUN_STATE_PARK;   /* 駐車中起動 */
                break;
            default:
                /* 遷移条件の一致なし */
                break;
        }

        /* シス検暫定対応：電源ステートは固定でPowerON通常とする */
        u1_t_mcu_return  = (U1)PWRCTRL_NOREDUN_STATE_APPON;
        /* シス検暫定ここまで */
    }
    else
    {
        /* 何もしない */
    }

  /* 量産向け暫定 */
  if((u1_g_PwrCtrl_NoRedun_Pwr_Sts != PWRCTRL_NOREDUN_STS_OFF) && /* OFF要求がない場合かつ */
     (u1_t_mcu_boot == (U1)STD_HIGH)){                            /* BOOT=Hiを検知した場合、どの状態でも見た目オン起動へ上書き */
    u1_t_mcu_return  = (U1)PWRCTRL_NOREDUN_STATE_APPON;           /* 電源ON 見た目オン起動 */
  }
  /* 量産向け暫定ここまで */

    return( u1_t_mcu_return );
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlNoRedunMetBB
  Description   : Meter+BB Display ON/OFFシーケンス
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlNoRedunMetBB( void )
{
    /* ON要求 かつ 実行中のONシーケンスがなしorMeter+BBの場合 */
    if ( ( u1_s_PwrCtrl_NoRedun_MetBB_Chk    == (U1)PWRCTRL_NOREDUN_PWR_ON )
      && ( ( u1_s_PwrCtrl_NoRedun_OnSequence == (U1)PWRCTRL_NOREDUN_ONSEQ_NON   )
        || ( u1_s_PwrCtrl_NoRedun_OnSequence == (U1)PWRCTRL_NOREDUN_ONSEQ_METBB ) ) )
    {
        /* OFF側のSTEP管理RAM,タイマをクリアしてOFF2週目も実行できるようにする */
        u1_s_PwrCtrl_NoRedun_MetBB_OffStep        = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
        u2_s_PwrCtrl_NoRedun_Gviftx_Mbwk_Off_Time = (U2)0U;
        u2_s_PwrCtrl_NoRedun_MBoff_Time           = (U2)0U;

        switch ( u1_s_PwrCtrl_NoRedun_MetBB_OnStep )
        {
            case PWRCTRL_COMMON_PROCESS_STEP1:
                /* 実行中のONシーケンスをMeter+BBに設定 */
                u1_s_PwrCtrl_NoRedun_OnSequence = (U1)PWRCTRL_NOREDUN_ONSEQ_METBB;

                vd_s_PwrCtrlNoRedunPwrOnMbPwr();

                if ( u2_s_PwrCtrl_NoRedun_MBon_Time == (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN )
                {
                    /* STEP1が完了していれば次のSTEPに進める */
                    u1_s_PwrCtrl_NoRedun_MetBB_OnStep = (U1)PWRCTRL_COMMON_PROCESS_STEP2;
                }
                break;

            case PWRCTRL_COMMON_PROCESS_STEP2:
                vd_s_PwrCtrlNoRedunWkGvifTxMetBB();

                if ( u2_s_PwrCtrl_NoRedun_Gviftx_Mbwk_Time == (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN )
                {
                    /* STEP1,2が完了していれば正常起動を設定 */
                    u1_s_PwrCtrl_NoRedun_MetBB_OnStep = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
                }
                /* 非冗長電源間ウェイトタイムをクリアしカウント開始する */
                u2_s_PwrCtrl_NoRedun_BetWait_Time = (U2)0U;
                break;

            case PWRCTRL_COMMON_PROCESS_STEP_CMPLT:
                /* 正常起動時は何もしない */
                break;

            default:
                /* 異常系は未考慮 */
                break;
        }
    }
    /* OFF要求 */
    else if ( u1_s_PwrCtrl_NoRedun_MetBB_Chk == (U1)PWRCTRL_NOREDUN_PWR_OFF )
    {
        /* ON側のSTEP管理RAM,タイマをクリアしてON2週目も実行できるようにする */
        u1_s_PwrCtrl_NoRedun_MetBB_OnStep     = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
        u2_s_PwrCtrl_NoRedun_MBon_Time        = (U2)0U;
        u2_s_PwrCtrl_NoRedun_Gviftx_Mbwk_Time = (U2)0U;

        switch ( u1_s_PwrCtrl_NoRedun_MetBB_OffStep )
        {
            case PWRCTRL_COMMON_PROCESS_STEP1:
                vd_s_PwrCtrlNoRedunWkOffGvifTxMetBB();

                if ( u2_s_PwrCtrl_NoRedun_Gviftx_Mbwk_Off_Time == (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN )
                {
                    /* STEP1が完了していれば次のSTEPに進める */
                    u1_s_PwrCtrl_NoRedun_MetBB_OffStep = (U1)PWRCTRL_COMMON_PROCESS_STEP2;
                }
                break;

            case PWRCTRL_COMMON_PROCESS_STEP2:
                vd_s_PwrCtrlNoRedunPwrOffMbPwr();

                if ( u2_s_PwrCtrl_NoRedun_MBoff_Time == (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN )
                {
                    /* STEP1,2が完了していれば正常終了を設定 */
                    u1_s_PwrCtrl_NoRedun_MetBB_OffStep = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
                }
                break;

            case PWRCTRL_COMMON_PROCESS_STEP_CMPLT:
                /* 正常終了時は何もしない */
                break;

            default:
                /* 異常系は未考慮 */
                break;
        }
    }
    else /* PWRCTRL_NOREDUN_PWR_NON：要求なし or u2_s_PwrCtrl_NoRedun_BetWait_Time≠FIN：非冗長電源間ウェイトタイム中 */
    {
        /* do nothing */
    }

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlNoRedunPwrOnMbPwr
  Description   : 非冗長電源ON制御 MET+BB-PWR-ON
                  (ソフトウェア処理：MCU →MET+BB Display)
  param[in/out] : none
  return        : none
  Note          : タイマー閾値が0のため、以上ではなく一致で判定
*****************************************************************************/
static void vd_s_PwrCtrlNoRedunPwrOnMbPwr( void )
{
    /* MET+BB-PWR-ON */
    if ( u2_s_PwrCtrl_NoRedun_MBon_Time == (U2)PWRCTRL_NOREDUN_WAIT_MBPWR_TIME )
    {
        vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_MBPWR, MCU_DIO_HIGH);
        u2_s_PwrCtrl_NoRedun_MBon_Time = (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN;
    }

    if ( u2_s_PwrCtrl_NoRedun_MBon_Time != (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN )
    {
        u2_s_PwrCtrl_NoRedun_MBon_Time++;
    }

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlNoRedunWkGvifTxMetBB
  Description   : 非冗長電源ON制御 GVIF-TX(MET+BB)-WAKE
                  (ソフトウェア処理：MCU →MET+BB Display)※GVIF信号重畳
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlNoRedunWkGvifTxMetBB( void )
{
    /* GVIF-TX(MET+BB)-WAKE */
    if ( u2_s_PwrCtrl_NoRedun_Gviftx_Mbwk_Time == (U2)PWRCTRL_NOREDUN_WAIT_GVIF_TX_MBWK_TIME )
    {
        vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_GVIF_TX_MBWK, MCU_DIO_HIGH);
        u2_s_PwrCtrl_NoRedun_Gviftx_Mbwk_Time = (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN;
    }

    if ( u2_s_PwrCtrl_NoRedun_Gviftx_Mbwk_Time != (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN )
    {
        u2_s_PwrCtrl_NoRedun_Gviftx_Mbwk_Time++;
    }

  return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlNoRedunWkOffGvifTxMetBB
  Description   : 非冗長電源OFF制御 GVIF-TX(MET+BB)-WAKE
                  (ソフトウェア処理：MCU →MET+BB Display)※GVIF信号重畳
  param[in/out] : none
  return        : none
  Note          : タイマー閾値が0のため、以上ではなく一致で判定
*****************************************************************************/
static void vd_s_PwrCtrlNoRedunWkOffGvifTxMetBB( void )
{
    /* GVIF-TX(MET+BB)-WAKE */
    if ( u2_s_PwrCtrl_NoRedun_Gviftx_Mbwk_Off_Time == (U2)PWRCTRL_NOREDUN_WAIT_GVIF_TX_MBWK_OFF_TIME)
    {
        vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_GVIF_TX_MBWK, MCU_DIO_LOW);
        u2_s_PwrCtrl_NoRedun_Gviftx_Mbwk_Off_Time = (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN;
    }

    if ( u2_s_PwrCtrl_NoRedun_Gviftx_Mbwk_Off_Time != (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN )
    {
        u2_s_PwrCtrl_NoRedun_Gviftx_Mbwk_Off_Time++;
    }

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlNoRedunPwrOffMbPwr
  Description   : 非冗長電源OFF制御 MET+BB-PWR-ON
                  (ソフトウェア処理：MCU →MET+BB Display)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlNoRedunPwrOffMbPwr( void )
{
    /* MET+BB-PWR-OFF */
    if ( u2_s_PwrCtrl_NoRedun_MBoff_Time == (U2)PWRCTRL_NOREDUN_WAIT_MBPWR_OFF_TIME )
    { 
        vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_MBPWR, MCU_DIO_LOW);
        u2_s_PwrCtrl_NoRedun_MBoff_Time = (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN;
    }

    if ( u2_s_PwrCtrl_NoRedun_MBoff_Time != (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN )
    {
        u2_s_PwrCtrl_NoRedun_MBoff_Time++;
    }

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlNoRedunDisp
  Description   : Center Display ON/OFFシーケンス
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlNoRedunDisp( void )
{
  /* ON要求あり かつ 実行中のONシーケンスがなしorCenterDispの場合 */
  if(u1_s_PwrCtrl_NoRedun_Disp_Chk    == (U1)PWRCTRL_NOREDUN_PWR_ON &&
     (u1_s_PwrCtrl_NoRedun_OnSequence == (U1)PWRCTRL_NOREDUN_ONSEQ_NON || u1_s_PwrCtrl_NoRedun_OnSequence == (U1)PWRCTRL_NOREDUN_ONSEQ_CNTDSP)){
       /* OFF側のSTEP管理RAM,タイマをクリアしてOFF2週目も実行できるようにする */
       u1_s_PwrCtrl_NoRedun_Disp_OffStep          = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
       u2_s_PwrCtrl_NoRedun_Gviftx_Dspwk_Off_Time = (U2)0U;
       u2_s_PwrCtrl_NoRedun_Dspoff_Time           = (U2)0U;

       switch (u1_s_PwrCtrl_NoRedun_Disp_OnStep)
       {
       case PWRCTRL_COMMON_PROCESS_STEP1:
            /* 実行中のONシーケンスをCenterDsipに設定 */
            u1_s_PwrCtrl_NoRedun_OnSequence = (U2)PWRCTRL_NOREDUN_ONSEQ_CNTDSP;

            vd_s_PwrCtrlNoRedunPwrOnDsp();

            if(u2_s_PwrCtrl_NoRedun_Dspon_Time == (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN){
               /* STEP1が完了していれば次のSTEPに進める */
               u1_s_PwrCtrl_NoRedun_Disp_OnStep = (U2)PWRCTRL_COMMON_PROCESS_STEP2;
            }
            break;

       case PWRCTRL_COMMON_PROCESS_STEP2:
            vd_s_PwrCtrlNoRedunWkGvifTxDisp();

            if(u2_s_PwrCtrl_NoRedun_Gviftx_Dspwk_Time == (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN){
               /* STEP1,2が完了していれば正常起動を設定 */
               u1_s_PwrCtrl_NoRedun_Disp_OnStep = (U2)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
            }
            /* 非冗長電源間ウェイトタイムをクリアしカウント開始する */
            u2_s_PwrCtrl_NoRedun_BetWait_Time = (U2)0U;
            break;

       case PWRCTRL_COMMON_PROCESS_STEP_CMPLT:
            /* 正常起動時は何もしない */
            break;
    
       default:
            /* 異常系は未考慮 */
            break;
       }
  }
  
  else if(u1_s_PwrCtrl_NoRedun_Disp_Chk == (U1)PWRCTRL_NOREDUN_PWR_OFF){
         /* ON側のSTEP管理RAM,タイマをクリアしてON2週目も実行できるようにする */
         u1_s_PwrCtrl_NoRedun_Disp_OnStep       = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
         u2_s_PwrCtrl_NoRedun_Dspon_Time        = (U2)0U;
         u2_s_PwrCtrl_NoRedun_Gviftx_Dspwk_Time = (U2)0U;

         switch (u1_s_PwrCtrl_NoRedun_Disp_OffStep)
         {
         case PWRCTRL_COMMON_PROCESS_STEP1:
              vd_s_PwrCtrlNoRedunWkOffGvifTxDisp();

              if(u2_s_PwrCtrl_NoRedun_Gviftx_Dspwk_Off_Time == (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN){
                  /* STEP1が完了していれば次のSTEPに進める */
                  u1_s_PwrCtrl_NoRedun_Disp_OffStep = (U1)PWRCTRL_COMMON_PROCESS_STEP2;
              }
              break;

         case PWRCTRL_COMMON_PROCESS_STEP2:
              vd_s_PwrCtrlNoRedunPwrOffDsp();

              if(u2_s_PwrCtrl_NoRedun_Dspoff_Time == (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN){
                 /* STEP1,2が完了していれば正常終了を設定 */
                 u1_s_PwrCtrl_NoRedun_Disp_OffStep = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
              }
              break;

          case PWRCTRL_COMMON_PROCESS_STEP_CMPLT:
               /* 正常終了時は何もしない */
               break;
    
          default:
               /* 異常系は未考慮 */
               break;
          }
  }
  else {    /* PWRCTRL_NOREDUN_PWR_NON：要求なし or u2_s_PwrCtrl_NoRedun_BetWait_Time≠FIN：非冗長電源間ウェイトタイム中 */
    /* do nothing */
  }
  
  return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlNoRedunPwrOnDsp
  Description   : 非冗長電源ON制御 DISP-PWR-ON
                  (ソフトウェア処理：MCU →Center Display)
  param[in/out] : none
  return        : none
  Note          : タイマー閾値が0のため、以上ではなく一致で判定
*****************************************************************************/
static void vd_s_PwrCtrlNoRedunPwrOnDsp( void )
{
  /* DISP-PWR-ON */
  if(u2_s_PwrCtrl_NoRedun_Dspon_Time == (U2)PWRCTRL_NOREDUN_WAIT_DISP_TIME){ 
    vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_DISP, MCU_DIO_HIGH);
    u2_s_PwrCtrl_NoRedun_Dspon_Time = (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN;
  }
    
  if(u2_s_PwrCtrl_NoRedun_Dspon_Time != (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN){
    u2_s_PwrCtrl_NoRedun_Dspon_Time++;
  }
    
  return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlNoRedunWkGvifTxDisp
  Description   : 非冗長電源ON制御 GVIF-TX(C-DISP)-WAKE
                  (ソフトウェア処理：MCU →Center Display)※GVIF信号重畳
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlNoRedunWkGvifTxDisp( void )
{
  /* GVIF-TX(MET+BB)-WAKE */
  if(u2_s_PwrCtrl_NoRedun_Gviftx_Dspwk_Time == (U2)PWRCTRL_NOREDUN_WAIT_GVIF_TX_DSPWK_TIME){ 
    vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_GVIF_TX_DSPWK, MCU_DIO_HIGH);
    u2_s_PwrCtrl_NoRedun_Gviftx_Dspwk_Time = (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN;
  }
    
  if(u2_s_PwrCtrl_NoRedun_Gviftx_Dspwk_Time != (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN){
    u2_s_PwrCtrl_NoRedun_Gviftx_Dspwk_Time++;
  }
    
  return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlNoRedunWkOffGvifTxDisp
  Description   : 非冗長電源OFF制御 GVIF-TX(C-DISP)-WAKE
                  (ソフトウェア処理：MCU →Center Display)※GVIF信号重畳
  param[in/out] : none
  return        : none
  Note          : タイマー閾値が0のため、以上ではなく一致で判定
*****************************************************************************/
static void vd_s_PwrCtrlNoRedunWkOffGvifTxDisp( void )
{
  /* GVIF-TX(MET+BB)-WAKE */
  if(u2_s_PwrCtrl_NoRedun_Gviftx_Dspwk_Off_Time == (U2)PWRCTRL_NOREDUN_WAIT_GVIF_TX_DSPWK_OFF_TIME){ 
    vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_GVIF_TX_DSPWK, MCU_DIO_LOW);
    u2_s_PwrCtrl_NoRedun_Gviftx_Dspwk_Off_Time = (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN;
  }
    
  if(u2_s_PwrCtrl_NoRedun_Gviftx_Dspwk_Off_Time != (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN){
    u2_s_PwrCtrl_NoRedun_Gviftx_Dspwk_Off_Time++;
  }

  return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlNoRedunPwrOffDsp
  Description   : 非冗長電源OFF制御 DISP-PWR-ON
                  (ソフトウェア処理：MCU →Center Display)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlNoRedunPwrOffDsp( void )
{
  /* DISP-PWR-Off */
  if(u2_s_PwrCtrl_NoRedun_Dspoff_Time == (U2)PWRCTRL_NOREDUN_WAIT_DISP_OFF_TIME){ 
    vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_DISP, MCU_DIO_LOW);
    u2_s_PwrCtrl_NoRedun_Dspoff_Time = (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN;
  }
    
  if(u2_s_PwrCtrl_NoRedun_Dspoff_Time != (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN){
    u2_s_PwrCtrl_NoRedun_Dspoff_Time++;
  }
    
  return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlNoRedunHub
  Description   : DSRC(HUB) ON/OFFシーケンス
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlNoRedunHub( void )
{
  /* ON要求あり かつ 実行中のONシーケンスがなしorDSRC(HUB)の場合 */
  if(u1_s_PwrCtrl_NoRedun_Hub_Chk == (U1)PWRCTRL_NOREDUN_PWR_ON &&
     (u1_s_PwrCtrl_NoRedun_OnSequence == (U1)PWRCTRL_NOREDUN_ONSEQ_NON || u1_s_PwrCtrl_NoRedun_OnSequence == (U1)PWRCTRL_NOREDUN_ONSEQ_DSRC)){
    /* Off側のSTEP管理RAM,タイマをクリアしてOFF2週目も実行できるようにする */
    u1_s_PwrCtrl_NoRedun_Hub_OffStep     = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
    u2_s_PwrCtrl_NoRedun_Hubwk_Off_Time  = (U2)0U;
    u2_s_PwrCtrl_NoRedun_Huboff_Time     = (U2)0U;

    switch (u1_s_PwrCtrl_NoRedun_Hub_OnStep)
    {
    case PWRCTRL_COMMON_PROCESS_STEP1:
      /* 実行中のONシーケンスをDSRC(HUB)に設定 */
      u1_s_PwrCtrl_NoRedun_OnSequence = (U1)PWRCTRL_NOREDUN_ONSEQ_DSRC;

      vd_s_PwrCtrlNoRedunPwrOnHub();

      if(u2_s_PwrCtrl_NoRedun_Hubon_Time == (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN){
        /* STEP1が完了していれば次のSTEPに進める */
        u1_s_PwrCtrl_NoRedun_Hub_OnStep = (U1)PWRCTRL_COMMON_PROCESS_STEP2;
      }
      break;

    case PWRCTRL_COMMON_PROCESS_STEP2:
      vd_s_PwrCtrlNoRedunWkHub();

      if(u2_s_PwrCtrl_NoRedun_Hubwk_Time == (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN){
        /* STEP1,2が完了していれば正常起動を設定 */
        u1_s_PwrCtrl_NoRedun_Hub_OnStep = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
      }
      /* 非冗長電源間ウェイトタイムをクリアしカウント開始する */
      u2_s_PwrCtrl_NoRedun_BetWait_Time = (U2)0U;
      break;

    case PWRCTRL_COMMON_PROCESS_STEP_CMPLT:
      /* 正常起動時は何もしない */
      break;
    
    default:
      /* 異常系は未考慮 */
      break;
    }
  }
  else if(u1_s_PwrCtrl_NoRedun_Hub_Chk == (U1)PWRCTRL_NOREDUN_PWR_OFF){
    /* ON側のSTEP管理RAM,タイマをクリアしてON2週目も実行できるようにする */
    u1_s_PwrCtrl_NoRedun_Hub_OnStep    = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
    u2_s_PwrCtrl_NoRedun_Hubon_Time    = (U2)0U;
    u2_s_PwrCtrl_NoRedun_Hubwk_Time    = (U2)0U;
    switch (u1_s_PwrCtrl_NoRedun_Hub_OffStep)
    {
    case PWRCTRL_COMMON_PROCESS_STEP1:
      vd_s_PwrCtrlNoRedunWkOffHub();

      if(u2_s_PwrCtrl_NoRedun_Hubwk_Off_Time == (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN){
        /* STEP1が完了していれば次のSTEPに進める */
        u1_s_PwrCtrl_NoRedun_Hub_OffStep = (U1)PWRCTRL_COMMON_PROCESS_STEP2;
      }
      break;

    case PWRCTRL_COMMON_PROCESS_STEP2:
      vd_s_PwrCtrlNoRedunPwrOffHub();

      if(u2_s_PwrCtrl_NoRedun_Huboff_Time == (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN){
        /* STEP1,2が完了していれば正常終了を設定 */
        u1_s_PwrCtrl_NoRedun_Hub_OffStep = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
      }
      break;

    case PWRCTRL_COMMON_PROCESS_STEP_CMPLT:
      /* 正常終了時は何もしない */
      break;
    
    default:
      /* 異常系は未考慮 */
      break;
    }
  }
  else {    /* PWRCTRL_NOREDUN_PWR_NON：要求なし or u2_s_PwrCtrl_NoRedun_BetWait_Time≠FIN：非冗長電源間ウェイトタイム中 */
    /* do nothing */
  }

  return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlNoRedunPwrOnHub
  Description   : 非冗長電源ON制御 DSRC(HUB)-PWR-ON
                  (ソフトウェア処理：MCU →DSRC(HUB) Power SW)
  param[in/out] : none
  return        : none
  Note          : タイマー閾値が0のため、以上ではなく一致で判定
*****************************************************************************/
static void vd_s_PwrCtrlNoRedunPwrOnHub( void )
{
  /* DSRC(HUB)-PWR-ON */
  if(u2_s_PwrCtrl_NoRedun_Hubon_Time == (U2)PWRCTRL_NOREDUN_WAIT_HUB_PWRON_TIME){ 
    vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_HUB_PWRON, MCU_DIO_HIGH);
    u2_s_PwrCtrl_NoRedun_Hubon_Time = (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN;
  }
    
  if(u2_s_PwrCtrl_NoRedun_Hubon_Time != (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN){
    u2_s_PwrCtrl_NoRedun_Hubon_Time++;
  }
    
  return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlNoRedunWkHub
  Description   : 非冗長電源ON制御 DSRC(HUB)-WAKE
                  (ソフトウェア処理：MCU →DSRC(HUB))
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlNoRedunWkHub( void )
{
  /* DSRC(HUB)-WAKE */
  if(u2_s_PwrCtrl_NoRedun_Hubwk_Time == (U2)PWRCTRL_NOREDUN_WAIT_HUB_WAKE_TIME){ 
    vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_MCU_PORT_HUB_WK, MCU_DIO_HIGH);
    u2_s_PwrCtrl_NoRedun_Hubwk_Time = (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN;
  }
    
  if(u2_s_PwrCtrl_NoRedun_Hubwk_Time != (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN){
    u2_s_PwrCtrl_NoRedun_Hubwk_Time++;
  }
    
  return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlNoRedunWkOffHub
  Description   : 非冗長電源OFF制御 DSRC(HUB)-WAKE
                  (ソフトウェア処理：MCU →DSRC(HUB))
  param[in/out] : none
  return        : none
  Note          : タイマー閾値が0のため、以上ではなく一致で判定
*****************************************************************************/
static void vd_s_PwrCtrlNoRedunWkOffHub( void )
{
  /* DSRC(HUB)-WAKE-OFF */
  if(u2_s_PwrCtrl_NoRedun_Hubwk_Off_Time == (U2)PWRCTRL_NOREDUN_WAIT_HUB_WAKE_OFF_TIME){ 
    vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_MCU_PORT_HUB_WK, MCU_DIO_LOW);
    u2_s_PwrCtrl_NoRedun_Hubwk_Off_Time = (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN;
  }
    
  if(u2_s_PwrCtrl_NoRedun_Hubwk_Off_Time != (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN){
    u2_s_PwrCtrl_NoRedun_Hubwk_Off_Time++;
  }
    
  return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlNoRedunPwrOffHub
  Description   : 非冗長電源OFF制御 DSRC(HUB)-PWR-ON
                  (ソフトウェア処理：MCU →DSRC(HUB) Power SW)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlNoRedunPwrOffHub( void )
{
  /* DSRC(HUB)-PWR-OFF */
  if(u2_s_PwrCtrl_NoRedun_Huboff_Time == (U2)PWRCTRL_NOREDUN_WAIT_HUB_PWROFF_TIME){ 
    vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_HUB_PWRON, MCU_DIO_LOW);
    u2_s_PwrCtrl_NoRedun_Huboff_Time = (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN;
  }
    
  if(u2_s_PwrCtrl_NoRedun_Huboff_Time != (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN){
    u2_s_PwrCtrl_NoRedun_Huboff_Time++;
  }
    
  return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlNoRedunBetWait
  Description   : 非冗長電源間ウェイトタイム(突入電流対策)カウント
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlNoRedunBetWait( void )
{
  /* ウェイトタイム経過した場合、ウェイトタイム完了通知と実行中のONシーケンスなしに設定 */
  if(u2_s_PwrCtrl_NoRedun_BetWait_Time == (U2)PWRCTRL_NOREDUN_WAIT_BETWEEN_TIME){ 
    u2_s_PwrCtrl_NoRedun_BetWait_Time = (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN;
    u1_s_PwrCtrl_NoRedun_OnSequence   = (U1)PWRCTRL_NOREDUN_ONSEQ_NON;
  }
  
  /* ウェイトタイム経過前はカウント */
  if(u2_s_PwrCtrl_NoRedun_BetWait_Time != (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN){
    u2_s_PwrCtrl_NoRedun_BetWait_Time++;
  }
    
  return;
}


/*****************************************************************************
  Function      : Mcu_Dev_Pwroff
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 
*****************************************************************************/
void Mcu_Dev_Pwroff( void ){
    if((u1_g_PwrCtrl_NoRedun_Pwr_Sts == (uint8)PWRCTRL_NOREDUN_STS_OFF)  &&
        (Mcu_Dev_Pwroff_Sts  !=  (uint16)PWROFF_CONP_BIT)){
        /* USBアダプタ接続検知 */
        if((Mcu_Dev_Pwroff_Sts & (uint16)PWROFF_USB_BIT) != (uint16)PWROFF_USB_BIT){
            Mcu_Dev_Pwroff_Sts  |=  Mcu_Dev_Pwroff_USB();
        }

        /* 映像IC(ML86294)制御 */
        if((Mcu_Dev_Pwroff_Sts & (uint16)PWROFF_PICTIC_BIT) != (uint16)PWROFF_PICTIC_BIT){
            Mcu_Dev_Pwroff_Sts  |=  Mcu_Dev_Pwroff_PictIC();
        }

        /* GVIF3受信(CXD4984ER)制御 */
        if((Mcu_Dev_Pwroff_Sts & (uint16)PWROFF_GVIFRX_BIT) != (uint16)PWROFF_GVIFRX_BIT){
            Mcu_Dev_Pwroff_Sts  |=  Mcu_Dev_Pwroff_GVIFRx();
        }

        /* GVIF3送信(CXD4937/57)制御 C-Disp */
        if((Mcu_Dev_Pwroff_Sts & (uint16)PWROFF_GVIFTX_BIT) != (uint16)PWROFF_GVIFTX_BIT){
            Mcu_Dev_Pwroff_Sts  |=  Mcu_Dev_Pwroff_GVIFTx_CDisp();
        }

        /* マイク電源制御 */
        if((Mcu_Dev_Pwroff_Sts & (uint16)PWROFF_MIC_BIT) != (uint16)PWROFF_MIC_BIT){
            Mcu_Dev_Pwroff_Sts  |=  Mcu_Dev_Pwroff_Mic();
        }

        /* アンテナ電源制御 */
        if((Mcu_Dev_Pwroff_Sts & (uint16)PWROFF_ANT_BIT) != (uint16)PWROFF_ANT_BIT){
            Mcu_Dev_Pwroff_Sts  |=  Mcu_Dev_Pwroff_Ant();
        }

        /* 音声MUTE制御 */
        if((Mcu_Dev_Pwroff_Sts & (uint16)PWROFF_SOUNDMUTE_BIT) != (uint16)PWROFF_SOUNDMUTE_BIT){
            Mcu_Dev_Pwroff_Sts  |=  Mcu_Dev_Pwroff_SoundMUTE();
        }

        /* MOST(v2)システム制御 */
        if((Mcu_Dev_Pwroff_Sts & (uint16)PWROFF_MOST_BIT) != (uint16)PWROFF_MOST_BIT){
            Mcu_Dev_Pwroff_Sts  |=  Mcu_Dev_Pwroff_Most();
        }

        /* Power-IC制御 */
        if((Mcu_Dev_Pwroff_Sts & (uint16)PWROFF_POWERIC_BIT) != (uint16)PWROFF_POWERIC_BIT){
            Mcu_Dev_Pwroff_Sts  |=  Mcu_Dev_Pwroff_PowerIC();
        }
        /* XM TUNER制御 */
        if((Mcu_Dev_Pwroff_Sts & (uint16)PWROFF_XMTUNER_BIT) != (uint16)PWROFF_XMTUNER_BIT){
            Mcu_Dev_Pwroff_Sts  |=  Mcu_Dev_Pwroff_XMTuner();
        }

        /* GNSS制御 */
        if((Mcu_Dev_Pwroff_Sts & (uint16)PWROFF_GNSS_BIT) != (uint16)PWROFF_GNSS_BIT){
            Mcu_Dev_Pwroff_Sts  |=  Mcu_Dev_Pwroff_GNSS();
        }

        /* ジャイロ・加速度センサ(SMI230)制御 */
        /* T.B.Dのためskip */

        /* 全プロセスが完了していればMcu_Dev_Pwroff_Sts=PWROFF_CONP_BITとなる */
    }
    else if(u1_g_PwrCtrl_NoRedun_Pwr_Sts == (uint8)PWRCTRL_NOREDUN_STS_ON){
        Mcu_Dev_Pwroff_Sts  = (uint16)FALSE;    /* PowerOFF処理状態のクリア */
        Mcu_OffStep_PowerIc = (uint8)MCU_STEP_P_IC_OVERALL_1;   /* Power-IC制御の遷移状態クリア */
        Mcu_OffTime_PowerIc = (uint16)0U;
        Mcu_OffStep_XMTuner = (uint8)MCU_STEP_XMTUNER_OVERALL_1;   /* XM TUNER制御制御の遷移状態クリア */
        Mcu_OffTime_XMTuner = (uint16)0U;
        Mcu_OffStep_GNSS    = (uint8)MCU_STEP_GNSS_OVERALL_1;   /* GNSS制御の遷移状態クリア */
        Mcu_OffTime_GNSS    = (uint16)0U;
        Mcu_OffCnt_GNSS     = (uint8)0U;
    }
    else {
        /* do nothing */
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwroff_USB
  Description   : 
  param[in/out] : 
  return        : PWROFF_USB_BIT ：プロセス完了
  Note          : 
*****************************************************************************/
uint16 Mcu_Dev_Pwroff_USB( void ){
  vd_g_McuDevPwronSetPort(MCU_PORT_USB_LED_ON, MCU_DIO_LOW);

  return((uint16)PWROFF_USB_BIT);
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwroff_PictIC
  Description   : 
  param[in/out] : 
  return        : PWROFF_PICTIC_BIT ：プロセス完了
  Note          : 
*****************************************************************************/
uint16 Mcu_Dev_Pwroff_PictIC( void ){
  vd_g_McuDevPwronSetPort(MCU_PORT_V_IC_RST, MCU_DIO_LOW);

  return((uint16)PWROFF_PICTIC_BIT);
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwroff_GVIFRx
  Description   : 
  param[in/out] : 
  return        : PWROFF_GVIFRX_BIT ：プロセス完了
  Note          : 
*****************************************************************************/
uint16 Mcu_Dev_Pwroff_GVIFRx( void ){
  vd_g_McuDevPwronSetPort(MCU_PORT_GVIF_CAN_RST, MCU_DIO_LOW);

  return((uint16)PWROFF_GVIFRX_BIT);
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwroff_GVIFTx_CDisp
  Description   : 
  param[in/out] : 
  return        : PWROFF_GVIFTX_BIT ：プロセス完了
  Note          : シス検暫定対応あり
*****************************************************************************/
uint16 Mcu_Dev_Pwroff_GVIFTx_CDisp( void ){
  /*****************************************************************************
  シス検暫定対応
  シス検の電源ステートは"見た目オン起動"or"OFF"のため、下記条件は対応しない
  ・車両電源ステートが"駐車中起動"または"スタンバイ"の状態に遷移したとき
  *****************************************************************************/

  vd_g_McuDevPwronSetPort(MCU_PORT_GVIF_CDISP_RST, MCU_DIO_LOW);

  return((uint16)PWROFF_GVIFTX_BIT);
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwroff_Mic
  Description   : 
  param[in/out] : 
  return        : PWROFF_MIC_BIT ：プロセス完了
  Note          : 
*****************************************************************************/
uint16 Mcu_Dev_Pwroff_Mic( void ){
  vd_g_McuDevPwronSetPort(MCU_PORT_MIC_ON, MCU_DIO_LOW);

  return((uint16)PWROFF_MIC_BIT);
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwroff_Ant
  Description   : 
  param[in/out] : 
  return        : PWROFF_ANT_BIT ：プロセス完了
  Note          : 
*****************************************************************************/
uint16 Mcu_Dev_Pwroff_Ant( void ){
    vd_g_McuDevPwronSetPort(MCU_PORT_AMFM_ANT_ON, MCU_DIO_LOW);
    vd_g_McuDevPwronSetPort(MCU_PORT_GPS_ANT_ON, MCU_DIO_LOW);
#ifdef SYS_PWR_ANT_DAB
    vd_g_McuDevPwronSetPort(MCU_PORT_DAB_ANT_ON, MCU_DIO_LOW);
#endif
#ifdef SYS_PWR_ANT_DTV
    vd_g_McuDevPwronSetPort(MCU_PORT_DTV_ANT_ON, MCU_DIO_LOW);
#endif

  return((uint16)PWROFF_ANT_BIT);
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwroff_SoundMUTE
  Description   : 
  param[in/out] : 
  return        : PWROFF_SOUNDMUTE_BIT ：プロセス完了
  Note          : シス検暫定対応あり
*****************************************************************************/
uint16 Mcu_Dev_Pwroff_SoundMUTE( void ){
    /*****************************************************************************
    シス検暫定対応
    シス検の電源ステートは"見た目オン起動"or"OFF"のため、下記条件は対応しない
    ・車両電源ステートが"駐車中起動"または"スタンバイ"の状態に遷移したとき
    *****************************************************************************/
   /*****************************************************************************
    シス検暫定対応
    PM-SYS-MUTE端子の操作要否不明
    *****************************************************************************/
    vd_g_McuDevPwronSetPort(MCU_PORT_PM_SYS_MUTE , MCU_DIO_LOW);

    return((uint16)PWROFF_SOUNDMUTE_BIT);
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwroff_Most
  Description   : 
  param[in/out] : 
  return        : PWROFF_MOST_BIT ：プロセス完了
  Note          : シス検暫定対応あり
*****************************************************************************/
uint16 Mcu_Dev_Pwroff_Most( void ){
    /*****************************************************************************
    シス検暫定対応
    シス検の電源ステートは"見た目オン起動"or"OFF"のため、下記条件は対応しない
    ・車両電源ステートが"駐車中起動"または"スタンバイ"の状態に遷移したとき
    *****************************************************************************/
    vd_g_McuDevPwronSetPort(MCU_PORT_MOST_WAKE_ON , MCU_DIO_LOW);

    /* シス検暫定対応：SPI通信系は実装しない(SPI側未実装,IF箇所不明) */

    return((uint16)PWROFF_MOST_BIT);
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwroff_PowerIC
  Description   : 
  param[in/out] : 
  return        : PWROFF_POWERIC_BIT ：プロセス完了
  Note          : シス検暫定対応あり
*****************************************************************************/
uint16 Mcu_Dev_Pwroff_PowerIC( void ){
    uint16  mcu_return;

    mcu_return          = (uint16)FALSE;
    
    switch (Mcu_OffStep_PowerIc)
    {
        case MCU_STEP_P_IC_OVERALL_1:
            /*****************************************************************************
            シス検暫定対応
            SPI通信系は未実装のため、下記開始条件は実装しない
            SiP→MCU "HexagonDSP MUTE設定完了通知" 送信
            *****************************************************************************/
            /* HexagonDSP MUTE設定完了通知があるまでとどまる */
            Mcu_OffStep_PowerIc = (uint8)MCU_STEP_P_IC_OVERALL_2;         /* 次状態に遷移 */
            break;

        case MCU_STEP_P_IC_OVERALL_2:
            if(Mcu_OffTime_PowerIc != PWRCTRL_NOREDUN_WAIT_TIME_FIN){
                Mcu_OffTime_PowerIc++;
            }
            if(Mcu_OffTime_PowerIc >= MCU_OFFWAIT_POWERIC_55MS){
                Mcu_OffStep_PowerIc = (uint8)MCU_STEP_P_IC_OVERALL_3;       /* 次状態に遷移 */
                Mcu_OffTime_PowerIc = (uint16)0U;                   /* タイマクリア */
            }
            break;

        case MCU_STEP_P_IC_OVERALL_3:
            /* レジスタ読出し処理：IB2 */
            Mcu_OffStep_PowerIc = (uint8)MCU_STEP_P_IC_OVERALL_4;       /* 次状態に遷移 */
            break;

        case MCU_STEP_P_IC_OVERALL_4:
            /* I2CによるレジスタWrite */
            /* MUTE解除設定 IB2[0x82].D4=1,IB2[0x82].D3=1 */
            Mcu_OffStep_PowerIc = (uint8)MCU_STEP_P_IC_OVERALL_5;       /* 次状態に遷移 */
            break;
        
        case MCU_STEP_P_IC_OVERALL_5:
            if(Mcu_OffTime_PowerIc != PWRCTRL_NOREDUN_WAIT_TIME_FIN){
                Mcu_OffTime_PowerIc++;
            }
            if(Mcu_OffTime_PowerIc >= MCU_OFFWAIT_POWERIC_100MS){
                Mcu_OffStep_PowerIc = (uint8)MCU_STEP_P_IC_OVERALL_6;   /* 次状態に遷移 */
                Mcu_OffTime_PowerIc = (uint16)0U;                       /* タイマクリア */
            }
            break;

        case MCU_STEP_P_IC_OVERALL_6:
            /* レジスタ読出し処理：IB7 */
            Mcu_OffStep_PowerIc = (uint8)MCU_STEP_P_IC_OVERALL_7;       /* 次状態に遷移 */
            break;

        case MCU_STEP_P_IC_OVERALL_7:
            /* I2CによるレジスタWrite */
            /* Amp On設定 IB7[0x87].D0=1 */
            Mcu_OffStep_PowerIc = (uint8)MCU_STEP_P_IC_OVERALL_8;       /* 次状態に遷移 */
            break;

        case MCU_STEP_P_IC_OVERALL_8:
            if(Mcu_OffTime_PowerIc != PWRCTRL_NOREDUN_WAIT_TIME_FIN){
                Mcu_OffTime_PowerIc++;
            }
            if(Mcu_OffTime_PowerIc >= MCU_OFFWAIT_POWERIC_5MS){
                vd_g_McuDevPwronSetPort(MCU_PORT_P_ON , MCU_DIO_LOW);      /* スタンバイ */
                Mcu_OffStep_PowerIc = (uint8)MCU_STEP_P_IC_OVERALL_9;   /* 次状態に遷移 */
                Mcu_OffTime_PowerIc = (uint16)0U;                       /* タイマクリア */
            }
            break;

        case MCU_STEP_P_IC_OVERALL_9:
            Mcu_OffStep_PowerIc = (uint8)MCU_STEP_P_IC_OVERALL_FIN;     /* 次状態に遷移 */
            break;

        case MCU_STEP_P_IC_OVERALL_FIN:
            mcu_return = (uint16)PWROFF_POWERIC_BIT;    /* 完了通知 */
            break;

        default:
            /* do nothing */
            break;
    }
    return(mcu_return);
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwroff_XMTuner
  Description   : 
  param[in/out] : 
  return        : PWROFF_MOST_BIT ：プロセス完了
  Note          : シス検暫定対応あり
*****************************************************************************/
uint16 Mcu_Dev_Pwroff_XMTuner( void ){
    uint16  mcu_return;

    mcu_return = (uint16)FALSE;

    switch (Mcu_OffStep_XMTuner)
    {
    case MCU_STEP_XMTUNER_OVERALL_1:
        /*****************************************************************************
        シス検暫定対応
        端子削除されているため、暫定的に下記条件は無視する
        ・V33-PMIC-ON端子がH→Lに変化したとき
        *****************************************************************************/
        /* V33-PMIC-ON=Lまでとどまる */
        Mcu_OffStep_XMTuner = (uint8)MCU_STEP_XMTUNER_OVERALL_2;
        break;
    
    case MCU_STEP_XMTUNER_OVERALL_2:
        if(Mcu_OffTime_XMTuner != PWRCTRL_NOREDUN_WAIT_TIME_FIN){
            Mcu_OffTime_XMTuner++;
        }
        if(Mcu_OffTime_XMTuner >= MCU_OFFWAIT_XMTUNER_10MS){
#ifdef SYS_PWR_ANT_XM_SHDN
            vd_g_McuDevPwronSetPort(MCU_PORT_XM_SHDN , MCU_DIO_LOW);     /* /XM-SHDN=H→L */
#endif
            Mcu_OffStep_XMTuner = (uint8)MCU_STEP_XMTUNER_OVERALL_3;       /* 次状態に遷移 */
            Mcu_OffTime_XMTuner = (uint16)0U;                   /* タイマクリア */
        }
        break;

    case MCU_STEP_XMTUNER_OVERALL_3:
        if(Mcu_OffTime_XMTuner != PWRCTRL_NOREDUN_WAIT_TIME_FIN){
            Mcu_OffTime_XMTuner++;
        }
        if(Mcu_OffTime_XMTuner >= MCU_OFFWAIT_XMTUNER_5MS){
            vd_g_McuDevPwronSetPort(MCU_PORT_XM_ON , MCU_DIO_LOW);    /* /XM-ON=H→L */
            Mcu_OffStep_XMTuner = (uint8)MCU_STEP_XMTUNER_OVERALL_FIN;          /* 次状態に遷移 */
            Mcu_OffTime_XMTuner = (uint16)0U;                       /* タイマクリア */
            mcu_return = (uint16)PWROFF_XMTUNER_BIT;                /* 完了通知 */
        }
        break;

    case MCU_STEP_XMTUNER_OVERALL_FIN:
        mcu_return = (uint16)PWROFF_XMTUNER_BIT;    /* 完了通知 */
        break;
    
    default:
        /* do nothing */
        break;
    }

    return(mcu_return);
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwroff_GNSS
  Description   : 
  param[in/out] : 
  return        : PWROFF_GNSS_BIT ：プロセス完了
  Note          : シス検暫定対応あり
*****************************************************************************/
uint16 Mcu_Dev_Pwroff_GNSS( void ){
    static const uint32 MCU_GNSS_POLING_MAX      =   (45U);       /* Checkﾘﾄﾗｲ 45回後、Hibernateに移行しない場合は、Reset（H→L遷移）し、状態を保持する */

    uint16  mcu_return;
    uint8   mcu_dio_ret_mmstby;
    uint8   mcu_dio_ret_budte;
    uint8   mcu_dio_ret_gpsrst;
    uint8   mcu_dio_ret_pmoni;

    mcu_return  = (uint16)FALSE;
    mcu_dio_ret_mmstby = (uint8)STD_HIGH;
    mcu_dio_ret_budte = (uint8)STD_LOW;
    mcu_dio_ret_gpsrst = (uint8)STD_LOW;
    mcu_dio_ret_pmoni = (uint8)STD_HIGH;

    switch (Mcu_OffStep_GNSS)
    {
    case MCU_STEP_GNSS_OVERALL_1:
        mcu_dio_ret_budte   =   Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_BU_DTE]);
        mcu_dio_ret_mmstby  =   Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_MM_STBY_N]);
        
        if(mcu_dio_ret_budte == (uint8)STD_HIGH){
            Mcu_OffStep_GNSS = (uint8)MCU_STEP_GNSS_OVERALL_2;       /* 次状態に遷移 */
        }
        else if(mcu_dio_ret_mmstby == (uint8)STD_LOW){
            Mcu_OffStep_GNSS = (uint8)MCU_STEP_GNSS_OVERALL_3;      /* 次状態に遷移 */
        }
        else{
            /* do nothing */
        }
        
        Mcu_OffStep_GNSS = (uint8)MCU_STEP_GNSS_OVERALL_3; /* 暫定対応 */
        break;

    case MCU_STEP_GNSS_OVERALL_2:
        mcu_dio_ret_gpsrst   =   Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_GPS_RST]);
        if(mcu_dio_ret_gpsrst == (uint8)STD_HIGH){
            /* t10はmin0msのため、判定せず即次処理を実施する */
            vd_g_McuDevPwronSetPort(MCU_PORT_GPS_PCTL , MCU_DIO_LOW);
            Mcu_OffStep_GNSS = (uint8)MCU_STEP_GNSS_OVERALL_4;      /* 次状態に遷移 */
        }
        else{
            Mcu_OffStep_GNSS = (uint8)MCU_STEP_GNSS_OVERALL_5;      /* 次状態に遷移 */
        }
        break;

    case MCU_STEP_GNSS_OVERALL_3:
        mcu_dio_ret_gpsrst   =   Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_GPS_RST]);
        if(mcu_dio_ret_gpsrst == (uint8)STD_HIGH){
            /* t10はmin0msのため、判定せず即次処理を実施する */
            vd_g_McuDevPwronSetPort(MCU_PORT_GPS_PCTL , MCU_DIO_LOW);
            Mcu_OffStep_GNSS = (uint8)MCU_STEP_GNSS_OVERALL_FIN;      /* 次状態に遷移 */
        }
        else{
            Mcu_OffStep_GNSS = (uint8)MCU_STEP_GNSS_OVERALL_5;      /* 次状態に遷移 */
        }
        break;
    case MCU_STEP_GNSS_OVERALL_4:
        if(Mcu_OffTime_GNSS != PWRCTRL_NOREDUN_WAIT_TIME_FIN){
            Mcu_OffTime_GNSS++;
        }
        if(Mcu_OffCnt_GNSS >= MCU_GNSS_POLING_MAX){
            vd_g_McuDevPwronSetPort(MCU_PORT_GPS_RST , MCU_DIO_LOW);
            Mcu_OffStep_GNSS = (uint8)MCU_STEP_GNSS_OVERALL_FIN;     /* 次状態に遷移 */
            Mcu_OffTime_GNSS = (uint16)0U;                      /* タイマクリア */
        }
        else if(Mcu_OffTime_GNSS >= MCU_OFFWAIT_GNSS_100MS){
            mcu_dio_ret_pmoni   =   Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_GPS_PMONI]);

            if(mcu_dio_ret_pmoni == (uint8)STD_LOW){
                /* Hibernate移行確認 → /GPS-RST=H保持 */
                Mcu_OffStep_GNSS = (uint8)MCU_STEP_GNSS_OVERALL_FIN;      /* 次状態に遷移 */
                Mcu_OffTime_GNSS = (uint16)0U;                      /* タイマクリア */
                Mcu_OffCnt_GNSS  = (uint8)0U;                       /* カウンタクリア */
            }
            else{
                Mcu_OffCnt_GNSS++;
            }
        }
        else{
            /* do nothing */
        }
        break;

    case MCU_STEP_GNSS_OVERALL_5:
        if(Mcu_OffTime_GNSS != PWRCTRL_NOREDUN_WAIT_TIME_FIN){
            Mcu_OffTime_GNSS++;
        }
        if(Mcu_OffTime_GNSS >= MCU_OFFWAIT_GNSS_10MS){
            vd_g_McuDevPwronSetPort(MCU_PORT_GPS_PCTL , MCU_DIO_LOW);
            Mcu_OffStep_GNSS = (uint8)MCU_STEP_GNSS_OVERALL_FIN;      /* 次状態に遷移 */
            Mcu_OffTime_GNSS = (uint16)0U;                   /* タイマクリア */
        }
        break;

    case MCU_STEP_GNSS_OVERALL_FIN:
        mcu_return = (uint16)PWROFF_GNSS_BIT;    /* 完了通知 */
        break;
    
    default:
        /* do nothing */
        break;
    }


    return(mcu_return);
}

/**** End of File ***********************************************************/