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

#include "PwrCtlSup.h"
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Timer */
#define PWRCTRL_NOREDUN_WAIT_30MS       ( 30U   / PWRCTRL_CFG_TASK_TIME)
#define PWRCTRL_NOREDUN_WAIT_20MS       ( 20U   / PWRCTRL_CFG_TASK_TIME)
#define PWRCTRL_NOREDUN_WAIT_10MS       ( 10U   / PWRCTRL_CFG_TASK_TIME)

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
       U2     u2_g_PwrCtrl_OffSts;  /* exturn */
static U2     u2_s_OffTime_XMTuner_Pmic;
#ifdef SYS_PWR_ANT_XM_SHDN
static U2     u2_s_OffTime_XMTuner_XmShdn;
#endif
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

static U2       u2_s_McuDev_Pwroff_USB(const U1 u1_a_PWR);
static U2       u2_s_McuDev_Pwroff_PictIC(const U1 u1_a_PWR);
static U2       u2_s_McuDev_Pwroff_GVIFRx(const U1 u1_a_PWR);
static U2       u2_s_McuDev_Pwroff_GVIFTx_CDisp(const U1 u1_a_PWR);
static U2       u2_s_McuDev_Pwroff_Mic(const U1 u1_a_PWR);
static U2       u2_s_McuDev_Pwroff_Ant(const U1 u1_a_PWR);
static U2       u2_s_McuDev_Pwroff_SoundMUTE(void);
static U2       u2_s_McuDev_Pwroff_Most(const U1 u1_a_PWR);
static U2       u2_s_McuDev_Pwroff_PowerIC(void);
static U2       u2_s_McuDev_Pwroff_XMTuner(void);
uint16 Mcu_Dev_Pwroff_GNSS(const U1 u1_a_PWR);
static U2       u2_s_McuDev_Pwroff_Gyro(void);

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
    u2_g_PwrCtrl_OffSts               = (U2)PWROFF_CONP_BIT;
    u2_s_OffTime_XMTuner_Pmic         = (U2)0U;
#ifdef SYS_PWR_ANT_XM_SHDN
    u2_s_OffTime_XMTuner_XmShdn       = (U2)0U;
#endif
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

    vd_g_McuDev_Pwroff(); /* デバイスOFF制御 */

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
      && ( u2_g_PwrCtrl_OffSts                == (U2)PWROFF_CONP_BIT                   )) /* デバイスOFF制御シーケンス完了 */
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
            case  (U1)PWRCTRL_NOREDUN_CHKSTS_APPON_UNCON:           /* 見た目：オン ステート：状態未定 */
                u1_t_mcu_return = u1_s_PwrCtrl_NoRedun_Sts;         /* 前回状態保持 */
                break;
            case  (U1)PWRCTRL_NOREDUN_CHKSTS_APPON_PARK:            /* 見た目：オン ステート：駐車中 */
                u1_t_mcu_return = (U1)PWRCTRL_NOREDUN_STATE_PARK;   /* 駐車中起動 */
                break;
            case  (U1)PWRCTRL_NOREDUN_CHKSTS_APPON_RIDE:            /* 見た目：オン ステート：乗車中 */
                u1_t_mcu_return = (U1)PWRCTRL_NOREDUN_STATE_APPON;  /* 見た目オン起動 */
                break;
            case  (U1)PWRCTRL_NOREDUN_CHKSTS_APPON_PONEMG:          /* 見た目：オン ステート：PowerON緊急停止 */
                u1_t_mcu_return = (U1)PWRCTRL_NOREDUN_STATE_APPON;  /* 見た目オン起動 */
                break;
            case  (U1)PWRCTRL_NOREDUN_CHKSTS_APPON_PON:             /* 見た目：オン ステート：PowerON通常 */
                u1_t_mcu_return = (U1)PWRCTRL_NOREDUN_STATE_APPON;  /* 見た目オン起動 */
                break;
            case  (U1)PWRCTRL_NOREDUN_CHKSTS_APPON_HVOL:            /* 見た目：オン ステート：駐車中 高圧起動 */
                u1_t_mcu_return = (U1)PWRCTRL_NOREDUN_STATE_PARK;   /* 駐車中起動 */
                break;
            case  (U1)PWRCTRL_NOREDUN_CHKSTS_APPON_HVOLHCOND:       /* 見た目：オン ステート：駐車中 高圧・温調起動 */
                u1_t_mcu_return = (U1)PWRCTRL_NOREDUN_STATE_PARK;   /* 駐車中起動 */
                break;
            case  (U1)PWRCTRL_NOREDUN_CHKSTS_APPOFF_UNCON:          /* 見た目：オフ ステート：状態未定 */
                u1_t_mcu_return = (U1)u1_s_PwrCtrl_NoRedun_Sts;     /* 前回状態保持 */
                break;
            case  (U1)PWRCTRL_NOREDUN_CHKSTS_APPOFF_PARK:           /* 見た目：オフ ステート：駐車中 */
                u1_t_mcu_return = (U1)PWRCTRL_NOREDUN_STATE_PARK;   /* 駐車中起動 */
                break;
            case  (U1)PWRCTRL_NOREDUN_CHKSTS_APPOFF_RIDE:           /* 見た目：オフ ステート：乗車中 */
                u1_t_mcu_return = (U1)PWRCTRL_NOREDUN_STATE_APPOFF; /* 見た目オフ起動 */
                break;
            case  (U1)PWRCTRL_NOREDUN_CHKSTS_APPOFF_PONEMG:         /* 見た目：オフ ステート：PowerON緊急停止 */
                u1_t_mcu_return = (U1)PWRCTRL_NOREDUN_STATE_APPON;  /* 見た目オン起動 */
                break;
            case  (U1)PWRCTRL_NOREDUN_CHKSTS_APPOFF_PON:            /* 見た目：オフ ステート：PowerON通常 */
                u1_t_mcu_return = (U1)PWRCTRL_NOREDUN_STATE_APPON;  /* 見た目オン起動 */
                break;
            case  (U1)PWRCTRL_NOREDUN_CHKSTS_APPOFF_HVOL:           /* 見た目：オフ ステート：駐車中 高圧起動 */
                u1_t_mcu_return = (U1)PWRCTRL_NOREDUN_STATE_PARK;   /* 駐車中起動 */
                break;
            case  (U1)PWRCTRL_NOREDUN_CHKSTS_APPOFF_HVOLHCOND:      /* 見た目：オフ ステート：駐車中 高圧・温調起動 */
                u1_t_mcu_return = (U1)PWRCTRL_NOREDUN_STATE_PARK;   /* 駐車中起動 */
                break;
            default:
                /* 遷移条件の一致なし */
                break;
        }
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
            case (U1)PWRCTRL_COMMON_PROCESS_STEP1:
                /* 実行中のONシーケンスをMeter+BBに設定 */
                u1_s_PwrCtrl_NoRedun_OnSequence = (U1)PWRCTRL_NOREDUN_ONSEQ_METBB;

                vd_s_PwrCtrlNoRedunPwrOnMbPwr();

                if ( u2_s_PwrCtrl_NoRedun_MBon_Time == (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN )
                {
                    /* STEP1が完了していれば次のSTEPに進める */
                    u1_s_PwrCtrl_NoRedun_MetBB_OnStep = (U1)PWRCTRL_COMMON_PROCESS_STEP2;
                }
                break;

            case (U1)PWRCTRL_COMMON_PROCESS_STEP2:
                vd_s_PwrCtrlNoRedunWkGvifTxMetBB();

                if ( u2_s_PwrCtrl_NoRedun_Gviftx_Mbwk_Time == (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN )
                {
                    /* STEP1,2が完了していれば正常起動を設定 */
                    u1_s_PwrCtrl_NoRedun_MetBB_OnStep = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
                }
                /* 非冗長電源間ウェイトタイムをクリアしカウント開始する */
                u2_s_PwrCtrl_NoRedun_BetWait_Time = (U2)0U;
                break;

            case (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT:
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
            case (U1)PWRCTRL_COMMON_PROCESS_STEP1:
                vd_s_PwrCtrlNoRedunWkOffGvifTxMetBB();

                if ( u2_s_PwrCtrl_NoRedun_Gviftx_Mbwk_Off_Time == (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN )
                {
                    /* STEP1が完了していれば次のSTEPに進める */
                    u1_s_PwrCtrl_NoRedun_MetBB_OffStep = (U1)PWRCTRL_COMMON_PROCESS_STEP2;
                }
                break;

            case (U1)PWRCTRL_COMMON_PROCESS_STEP2:
                vd_s_PwrCtrlNoRedunPwrOffMbPwr();

                if ( u2_s_PwrCtrl_NoRedun_MBoff_Time == (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN )
                {
                    /* STEP1,2が完了していれば正常終了を設定 */
                    u1_s_PwrCtrl_NoRedun_MetBB_OffStep = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
                }
                break;

            case (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT:
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
       case (U1)PWRCTRL_COMMON_PROCESS_STEP1:
            /* 実行中のONシーケンスをCenterDsipに設定 */
            u1_s_PwrCtrl_NoRedun_OnSequence = (U2)PWRCTRL_NOREDUN_ONSEQ_CNTDSP;

            vd_s_PwrCtrlNoRedunPwrOnDsp();

            if(u2_s_PwrCtrl_NoRedun_Dspon_Time == (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN){
               /* STEP1が完了していれば次のSTEPに進める */
               u1_s_PwrCtrl_NoRedun_Disp_OnStep = (U2)PWRCTRL_COMMON_PROCESS_STEP2;
            }
            break;

       case (U1)PWRCTRL_COMMON_PROCESS_STEP2:
            vd_s_PwrCtrlNoRedunWkGvifTxDisp();

            if(u2_s_PwrCtrl_NoRedun_Gviftx_Dspwk_Time == (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN){
               /* STEP1,2が完了していれば正常起動を設定 */
               u1_s_PwrCtrl_NoRedun_Disp_OnStep = (U2)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
            }
            /* 非冗長電源間ウェイトタイムをクリアしカウント開始する */
            u2_s_PwrCtrl_NoRedun_BetWait_Time = (U2)0U;
            break;

       case (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT:
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
         case (U1)PWRCTRL_COMMON_PROCESS_STEP1:
              vd_s_PwrCtrlNoRedunWkOffGvifTxDisp();

              if(u2_s_PwrCtrl_NoRedun_Gviftx_Dspwk_Off_Time == (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN){
                  /* STEP1が完了していれば次のSTEPに進める */
                  u1_s_PwrCtrl_NoRedun_Disp_OffStep = (U1)PWRCTRL_COMMON_PROCESS_STEP2;
              }
              break;

         case (U1)PWRCTRL_COMMON_PROCESS_STEP2:
              vd_s_PwrCtrlNoRedunPwrOffDsp();

              if(u2_s_PwrCtrl_NoRedun_Dspoff_Time == (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN){
                 /* STEP1,2が完了していれば正常終了を設定 */
                 u1_s_PwrCtrl_NoRedun_Disp_OffStep = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
              }
              break;

          case (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT:
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
    case (U1)PWRCTRL_COMMON_PROCESS_STEP1:
      /* 実行中のONシーケンスをDSRC(HUB)に設定 */
      u1_s_PwrCtrl_NoRedun_OnSequence = (U1)PWRCTRL_NOREDUN_ONSEQ_DSRC;

      vd_s_PwrCtrlNoRedunPwrOnHub();

      if(u2_s_PwrCtrl_NoRedun_Hubon_Time == (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN){
        /* STEP1が完了していれば次のSTEPに進める */
        u1_s_PwrCtrl_NoRedun_Hub_OnStep = (U1)PWRCTRL_COMMON_PROCESS_STEP2;
      }
      break;

    case (U1)PWRCTRL_COMMON_PROCESS_STEP2:
      vd_s_PwrCtrlNoRedunWkHub();

      if(u2_s_PwrCtrl_NoRedun_Hubwk_Time == (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN){
        /* STEP1,2が完了していれば正常起動を設定 */
        u1_s_PwrCtrl_NoRedun_Hub_OnStep = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
      }
      /* 非冗長電源間ウェイトタイムをクリアしカウント開始する */
      u2_s_PwrCtrl_NoRedun_BetWait_Time = (U2)0U;
      break;

    case (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT:
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
    case (U1)PWRCTRL_COMMON_PROCESS_STEP1:
      vd_s_PwrCtrlNoRedunWkOffHub();

      if(u2_s_PwrCtrl_NoRedun_Hubwk_Off_Time == (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN){
        /* STEP1が完了していれば次のSTEPに進める */
        u1_s_PwrCtrl_NoRedun_Hub_OffStep = (U1)PWRCTRL_COMMON_PROCESS_STEP2;
      }
      break;

    case (U1)PWRCTRL_COMMON_PROCESS_STEP2:
      vd_s_PwrCtrlNoRedunPwrOffHub();

      if(u2_s_PwrCtrl_NoRedun_Huboff_Time == (U2)PWRCTRL_NOREDUN_WAIT_TIME_FIN){
        /* STEP1,2が完了していれば正常終了を設定 */
        u1_s_PwrCtrl_NoRedun_Hub_OffStep = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
      }
      break;

    case (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT:
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
  Function      : vd_g_McuDev_Pwroff
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 
*****************************************************************************/
void            vd_g_McuDev_Pwroff(void)
{
    U1      u1_t_pwr;

    /* 電源状態取得 */
    u1_t_pwr    = u1_g_PowerSup_ModeState();
    if(u1_g_PwrCtrl_NoRedun_Pwr_Sts == (U1)PWRCTRL_NOREDUN_STS_OFF){
        u1_t_pwr  = (U1)POWER_MODE_STATE_STANDBY;
    }

    /* USBアダプタ接続検知 */
    if((u2_g_PwrCtrl_OffSts & (U2)PWROFF_USB_BIT) != (U2)PWROFF_USB_BIT){
        u2_g_PwrCtrl_OffSts |=  u2_s_McuDev_Pwroff_USB(u1_t_pwr);
    }

    /* 映像IC(ML86294)制御 */
    if((u2_g_PwrCtrl_OffSts & (U2)PWROFF_PICTIC_BIT) != (U2)PWROFF_PICTIC_BIT){
        u2_g_PwrCtrl_OffSts |=  u2_s_McuDev_Pwroff_PictIC(u1_t_pwr);
    }

    /* GVIF3受信(CXD4984ER)制御 */
    if((u2_g_PwrCtrl_OffSts & (U2)PWROFF_GVIFRX_BIT) != (U2)PWROFF_GVIFRX_BIT){
        u2_g_PwrCtrl_OffSts |=  u2_s_McuDev_Pwroff_GVIFRx(u1_t_pwr);
    }

    /* GVIF3送信(CXD4937/57)制御 C-Disp */
    if((u2_g_PwrCtrl_OffSts & (U2)PWROFF_GVIFTX_BIT) != (U2)PWROFF_GVIFTX_BIT){
        u2_g_PwrCtrl_OffSts |=  u2_s_McuDev_Pwroff_GVIFTx_CDisp(u1_t_pwr);
    }

    /* マイク電源制御 */
    if((u2_g_PwrCtrl_OffSts & (U2)PWROFF_MIC_BIT) != (U2)PWROFF_MIC_BIT){
        u2_g_PwrCtrl_OffSts |=  u2_s_McuDev_Pwroff_Mic(u1_t_pwr);
    }

    /* アンテナ電源制御 */
    if((u2_g_PwrCtrl_OffSts & (U2)PWROFF_ANT_BIT) != (U2)PWROFF_ANT_BIT){
        u2_g_PwrCtrl_OffSts |=  u2_s_McuDev_Pwroff_Ant(u1_t_pwr);
    }

    /* 音声MUTE制御 */
    if((u2_g_PwrCtrl_OffSts & (U2)PWROFF_SOUNDMUTE_BIT) != (U2)PWROFF_SOUNDMUTE_BIT){
        u2_g_PwrCtrl_OffSts |=  u2_s_McuDev_Pwroff_SoundMUTE();
    }

    /* MOST(v2)システム制御 */
    if((u2_g_PwrCtrl_OffSts & (U2)PWROFF_MOST_BIT) != (U2)PWROFF_MOST_BIT){
        u2_g_PwrCtrl_OffSts |=  u2_s_McuDev_Pwroff_Most(u1_t_pwr);
    }

    /* Power-IC制御 */
    if((u2_g_PwrCtrl_OffSts & (U2)PWROFF_POWERIC_BIT) != (U2)PWROFF_POWERIC_BIT){
        u2_g_PwrCtrl_OffSts |=  u2_s_McuDev_Pwroff_PowerIC();
    }

    /* XM TUNER制御 */
    if((u2_g_PwrCtrl_OffSts & (U2)PWROFF_XMTUNER_BIT) != (U2)PWROFF_XMTUNER_BIT){
        u2_g_PwrCtrl_OffSts |=  u2_s_McuDev_Pwroff_XMTuner();
    }

    /* GNSS制御 */
    if((u2_g_PwrCtrl_OffSts & (U2)PWROFF_GNSS_BIT) != (U2)PWROFF_GNSS_BIT){
        u2_g_PwrCtrl_OffSts |=  (U2)Mcu_Dev_Pwroff_GNSS(u1_t_pwr);
    }

    /* ジャイロ・加速度センサ(SMI230)制御 */
    if((u2_g_PwrCtrl_OffSts & (U2)PWROFF_GYRO_BIT) != (U2)PWROFF_GYRO_BIT){
        u2_g_PwrCtrl_OffSts |=  u2_s_McuDev_Pwroff_Gyro();
    }

    /* 全プロセスが完了していればu2_g_PwrCtrl_OffSts=PWROFF_CONP_BITとなる */
}

/*****************************************************************************
  Function      : u2_s_McuDev_Pwroff_USB
  Description   : 
  param[in/out] : 
  return        : PWROFF_USB_BIT ：プロセス完了
  Note          : "スタンバイ" もしくは "縮退走行"へ遷移した時
*****************************************************************************/
static U2       u2_s_McuDev_Pwroff_USB(const U1 u1_a_PWR)
{
    U2    u2_t_ret;

    u2_t_ret    = (U2)PWROFF_BIT_OFF;

    if((u1_a_PWR == (U1)POWER_MODE_STATE_STANDBY) || (u1_a_PWR == (U1)POWER_MODE_STATE_EDS)){
        vd_g_McuDevPwronSetPort(MCU_PORT_USB_LED_ON, MCU_DIO_LOW);
        u2_t_ret    = (U2)PWROFF_USB_BIT;
    }

    return(u2_t_ret);
}

/*****************************************************************************
  Function      : u2_s_McuDev_Pwroff_PictIC
  Description   : 
  param[in/out] : 
  return        : PWROFF_PICTIC_BIT ：プロセス完了
  Note          : 「スタンバイ」または「駐車中起動」または「縮退走行」へ遷移 またはEIZO ON=L する前
*****************************************************************************/
static U2       u2_s_McuDev_Pwroff_PictIC(const U1 u1_a_PWR)
{
    U2    u2_t_ret;

    u2_t_ret    = (U2)PWROFF_BIT_OFF;

    if((u1_a_PWR == (U1)POWER_MODE_STATE_STANDBY) || (u1_a_PWR == (U1)POWER_MODE_STATE_PARK) || (u1_a_PWR == (U1)POWER_MODE_STATE_EDS)){
        vd_g_McuDevPwronSetPort(MCU_PORT_V_IC_RST, MCU_DIO_LOW);
        u2_t_ret    = (U2)PWROFF_PICTIC_BIT;
    }

    return(u2_t_ret);
}

/*****************************************************************************
  Function      : u2_s_McuDev_Pwroff_GVIFRx
  Description   : 
  param[in/out] : 
  return        : PWROFF_GVIFRX_BIT ：プロセス完了
  Note          : AUDIO-ON = Loのt2 前までであること(vd_s_PwrCtrlSysPwrOffflwで実施) or 
                  条件②: 車両電源ステートが"縮退走行"の状態に遷移した時
*****************************************************************************/
static U2       u2_s_McuDev_Pwroff_GVIFRx(const U1 u1_a_PWR)
{
    U2              u2_t_ret;

    u2_t_ret    = (U2)PWROFF_BIT_OFF;

    if((u1_a_PWR == (U1)POWER_MODE_STATE_STANDBY) || (u1_a_PWR == (U1)POWER_MODE_STATE_EDS)){
        vd_g_McuDevPwronSetPort(MCU_PORT_GVIF_CAN_RST, MCU_DIO_LOW);
        u2_t_ret    = (U2)PWROFF_GVIFRX_BIT;
    }

    return(u2_t_ret);
}

/*****************************************************************************
  Function      : u2_s_McuDev_Pwroff_GVIFTx_CDisp
  Description   : 
  param[in/out] : 
  return        : PWROFF_GVIFTX_BIT ：プロセス完了
  Note          : 下記条件いずれかを満足するときに実施
                  ・車両電源ステートが"駐車中起動"または"スタンバイ"または"縮退走行"の状態に遷移したとき
                  ・AUDIO-ON="L"の1ms（t2）前までであること(vd_s_PwrCtrlSysPwrOffflwで実施)
*****************************************************************************/
static U2       u2_s_McuDev_Pwroff_GVIFTx_CDisp(const U1 u1_a_PWR)
{
    U2              u2_t_ret;

    u2_t_ret    = (U2)PWROFF_BIT_OFF;

    if((u1_a_PWR == (U1)POWER_MODE_STATE_STANDBY) || (u1_a_PWR == (U1)POWER_MODE_STATE_PARK) || (u1_a_PWR == (U1)POWER_MODE_STATE_EDS)){
        vd_g_McuDevPwronSetPort(MCU_PORT_GVIF_CDISP_RST, MCU_DIO_LOW);
        u2_t_ret    = (U2)PWROFF_GVIFTX_BIT;
    }

    return(u2_t_ret);
}

/*****************************************************************************
  Function      : u2_s_McuDev_Pwroff_Mic
  Description   : 
  param[in/out] : 
  return        : PWROFF_MIC_BIT ：プロセス完了
  Note          : "スタンバイ" もしくは "縮退走行"に遷移した場合、MIC-ONを電源OFFにすること。
*****************************************************************************/
static U2       u2_s_McuDev_Pwroff_Mic(const U1 u1_a_PWR)
{
    U2              u2_t_ret;

    u2_t_ret    = (U2)PWROFF_BIT_OFF;

    if((u1_a_PWR == (U1)POWER_MODE_STATE_STANDBY) || (u1_a_PWR == (U1)POWER_MODE_STATE_EDS)){
        vd_g_McuDevPwronSetPort(MCU_PORT_MIC_ON, MCU_DIO_LOW);
        u2_t_ret    = (U2)PWROFF_MIC_BIT;
    }

    return(u2_t_ret);
}

/*****************************************************************************
  Function      : u2_s_McuDev_Pwroff_Ant
  Description   : 
  param[in/out] : 
  return        : PWROFF_ANT_BIT ：プロセス完了
  Note          : 
*****************************************************************************/
static U2       u2_s_McuDev_Pwroff_Ant(const U1 u1_a_PWR)
{
    U2              u2_t_ret;
    Dio_LevelType   dl_t_port_ANFN;
    Dio_LevelType   dl_t_port_GPS;
#ifdef SYS_PWR_ANT_DAB
    Dio_LevelType   dl_t_port_DAB;
#endif
#ifdef SYS_PWR_ANT_DTV
    Dio_LevelType   dl_t_port_DTV;
#endif

    u2_t_ret    = (U2)PWROFF_BIT_OFF;

    if(u1_a_PWR != (U1)POWER_MODE_STATE_APPON){
        vd_g_McuDevPwronSetPort(MCU_PORT_AMFM_ANT_ON, MCU_DIO_LOW);
#ifdef SYS_PWR_ANT_DAB
        vd_g_McuDevPwronSetPort(MCU_PORT_DAB_ANT_ON, MCU_DIO_LOW);
#endif
#ifdef SYS_PWR_ANT_DTV
        vd_g_McuDevPwronSetPort(MCU_PORT_DTV_ANT_ON, MCU_DIO_LOW);
#endif
    }

    if(u1_a_PWR == (U1)POWER_MODE_STATE_STANDBY){
        vd_g_McuDevPwronSetPort(MCU_PORT_GPS_ANT_ON, MCU_DIO_LOW);
    }

    dl_t_port_ANFN  = Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_AMFM_ANT_ON]);
    dl_t_port_GPS   = Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_GPS_ANT_ON]);
#ifdef SYS_PWR_ANT_DAB
    dl_t_port_DAB   = Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_DAB_ANT_ON]);
#endif
#ifdef SYS_PWR_ANT_DTV
    dl_t_port_DTV   = Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_DTV_ANT_ON]);
#endif

    if((dl_t_port_ANFN  == (Dio_LevelType)STD_LOW) &&
#ifdef SYS_PWR_ANT_DAB
       (dl_t_port_DAB   == (Dio_LevelType)STD_LOW) &&
#endif
#ifdef SYS_PWR_ANT_DTV
       (dl_t_port_DTV   == (Dio_LevelType)STD_LOW) &&
#endif
       (dl_t_port_GPS   == (Dio_LevelType)STD_LOW)){
        u2_t_ret    = (U2)PWROFF_ANT_BIT;
    }

    return(u2_t_ret);
}

/*****************************************************************************
  Function      : u2_s_McuDev_Pwroff_SoundMUTE
  Description   : 
  param[in/out] : 
  return        : PWROFF_SOUNDMUTE_BIT ：プロセス完了
  Note          : PowerICで起動処理実施のため処理なし 予備設計
*****************************************************************************/
static U2       u2_s_McuDev_Pwroff_SoundMUTE(void)
{
    return((U2)PWROFF_SOUNDMUTE_BIT);
}

/*****************************************************************************
  Function      : u2_s_McuDev_Pwroff_Most
  Description   : 
  param[in/out] : 
  return        : PWROFF_MOST_BIT ：プロセス完了
  Note          : スタンバイ,駐車中起でMOST-WAKE-ON＝Low 暫定対応あり
*****************************************************************************/
static U2       u2_s_McuDev_Pwroff_Most(const U1 u1_a_PWR)
{
    U2              u2_t_ret;

    u2_t_ret    = (U2)PWROFF_BIT_OFF;

    if((u1_a_PWR == (U1)POWER_MODE_STATE_STANDBY) || (u1_a_PWR == (U1)POWER_MODE_STATE_PARK)){
        vd_g_McuDevPwronSetPort(MCU_PORT_MOST_WAKE_ON , MCU_DIO_LOW);
        u2_t_ret    = (U2)PWROFF_MOST_BIT;
        /* 暫定対応：SPI通信系は未実装(OS間コマンド不明) */
    }

    return(u2_t_ret);
}

/*****************************************************************************
  Function      : u2_s_McuDev_Pwroff_PowerIC
  Description   : 
  param[in/out] : 
  return        : PWROFF_POWERIC_BIT ：プロセス完了
  Note          : PIC-POFF=Lowを検知したらプロセス終了
*****************************************************************************/
static U2       u2_s_McuDev_Pwroff_PowerIC(void)
{
    U2              u2_t_ret;
/* VM3の終了処理順がアプリ電源OFF→SYS電源OFFとなっており、アプリOFF処理中にV33PERIONがLoになることがない */
/* 暫定措置としてアプリでのPIC_POFF=Low処理をスキップし、終了処理完了とする */
/* PIC_POFFはSYS電源OFF処理中にてLowに変更している */
#if 0
    Dio_LevelType   dl_t_sts;       /* ポート読出し値 */

    u2_t_ret    = (U2)PWROFF_BIT_OFF;
    dl_t_sts = Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_PIC_POFF]);

    if(dl_t_sts == (Dio_LevelType)STD_LOW){
        u2_t_ret = (U2)PWROFF_POWERIC_BIT;
    }
#else
    u2_t_ret = (U2)PWROFF_POWERIC_BIT;
#endif
    return(u2_t_ret);
}

/*****************************************************************************
  Function      : u2_s_McuDev_Pwroff_XMTuner
  Description   : 
  param[in/out] : 
  return        : PWROFF_XMTUNER_BIT ：プロセス完了
  Note          : XM-SHDN=Lから10msでXM-ON,PMIC_FAST_POFF_EN_N=Hから20msでXM-SHDN
*****************************************************************************/
static U2       u2_s_McuDev_Pwroff_XMTuner(void)
{
    U2              u2_t_ret;
    Dio_LevelType   dl_t_sts_pmic;    /* ポート読出し値 */
#ifdef SYS_PWR_ANT_XM_SHDN
    Dio_LevelType   dl_t_sts_xmshdn;  /* ポート読出し値 */
#endif

    u2_t_ret        = (U2)PWROFF_BIT_OFF;
    dl_t_sts_pmic   = Dio_ReadChannel(Mcu_Dio_PortId[PWRCTRL_CFG_PRIVATE_PORT_PMIC_FAST_POFF_EN]);

    if(dl_t_sts_pmic == (Dio_LevelType)STD_LOW){
        if(u2_s_OffTime_XMTuner_Pmic < U2_MAX){
            u2_s_OffTime_XMTuner_Pmic++;
        }
    }
    else{
        u2_s_OffTime_XMTuner_Pmic = (U2)0U;
    }

#ifdef SYS_PWR_ANT_XM_SHDN
    if(u2_s_OffTime_XMTuner_Pmic >= (U2)PWRCTRL_NOREDUN_WAIT_20MS){
        vd_g_McuDevPwronSetPort(MCU_PORT_XM_SHDN , MCU_DIO_LOW);
    }

    dl_t_sts_xmshdn = Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_XM_SHDN]);

    if(dl_t_sts_xmshdn == (Dio_LevelType)STD_LOW){
        if(u2_s_OffTime_XMTuner_XmShdn < U2_MAX){
            u2_s_OffTime_XMTuner_XmShdn++;
        }
    }
    else{
        u2_s_OffTime_XMTuner_XmShdn = (U2)0U;
    }

    if(u2_s_OffTime_XMTuner_XmShdn >= (U2)PWRCTRL_NOREDUN_WAIT_10MS){
        vd_g_McuDevPwronSetPort(MCU_PORT_XM_ON , MCU_DIO_LOW);
    }

    if((u2_s_OffTime_XMTuner_Pmic >= (U2)PWRCTRL_NOREDUN_WAIT_20MS) &&
       (u2_s_OffTime_XMTuner_XmShdn >= (U2)PWRCTRL_NOREDUN_WAIT_10MS)){
        u2_t_ret  = (U2)PWROFF_XMTUNER_BIT;
    }
#else
    if(u2_s_OffTime_XMTuner_Pmic >= (U2)PWRCTRL_NOREDUN_WAIT_30MS){
        vd_g_McuDevPwronSetPort(MCU_PORT_XM_ON , MCU_DIO_LOW);
        u2_t_ret  = (U2)PWROFF_XMTUNER_BIT;
    }
#endif

    return(u2_t_ret);
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwroff_GNSS
  Description   : 
  param[in/out] : 
  return        : PWROFF_GNSS_BIT ：プロセス完了
  Note          : シス検暫定対応あり
*****************************************************************************/
uint16 Mcu_Dev_Pwroff_GNSS(const U1 u1_a_PWR){
    static const uint32 MCU_GNSS_POLING_MAX      =   (45U);       /* Checkﾘﾄﾗｲ 45回後、Hibernateに移行しない場合は、Reset（H→L遷移）し、状態を保持する */

    uint16  mcu_return;
    uint8   mcu_dio_ret_v33peri;
    uint8   mcu_dio_ret_budte;
    uint8   mcu_dio_ret_gpsrst;
    uint8   mcu_dio_ret_pmoni;

    mcu_return  = (uint16)FALSE;
    mcu_dio_ret_v33peri = (uint8)STD_HIGH;
    mcu_dio_ret_budte = (uint8)STD_LOW;
    mcu_dio_ret_gpsrst = (uint8)STD_LOW;
    mcu_dio_ret_pmoni = (uint8)STD_HIGH;

    switch (Mcu_OffStep_GNSS)
    {
    case MCU_STEP_GNSS_OVERALL_1:
        mcu_dio_ret_budte   =   Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_BU_DTE]);

        if(mcu_dio_ret_budte == (uint8)STD_HIGH){
            Mcu_OffStep_GNSS = (uint8)MCU_STEP_GNSS_OVERALL_3;       /* 次状態に遷移 */
        }
        else if(u1_a_PWR == (uint8)POWER_MODE_STATE_STANDBY){
            Mcu_OffStep_GNSS = (uint8)MCU_STEP_GNSS_OVERALL_2;      /* 次状態に遷移 */
        }
        else{
            /* do nothing */
        }
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
            mcu_return = (uint16)PWROFF_GNSS_BIT;    /* 完了通知 */
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
            mcu_return = (uint16)PWROFF_GNSS_BIT;    /* 完了通知 */
        }
        else if(Mcu_OffTime_GNSS >= MCU_OFFWAIT_GNSS_100MS){
            Mcu_OffTime_GNSS    =   (uint16)0U;
            mcu_dio_ret_pmoni   =   Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_GPS_PMONI]);

            if(mcu_dio_ret_pmoni == (uint8)STD_LOW){
                /* Hibernate移行確認 → /GPS-RST=H保持 */
                Mcu_OffStep_GNSS = (uint8)MCU_STEP_GNSS_OVERALL_FIN;      /* 次状態に遷移 */
                Mcu_OffCnt_GNSS  = (uint8)0U;                       /* カウンタクリア */
                mcu_return = (uint16)PWROFF_GNSS_BIT;    /* 完了通知 */
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
            mcu_return = (uint16)PWROFF_GNSS_BIT;    /* 完了通知 */
        }
        break;

    case MCU_STEP_GNSS_OVERALL_FIN:
        mcu_return = (uint16)PWROFF_GNSS_BIT;    /* 完了通知 */
        mcu_dio_ret_v33peri =   Dio_ReadChannel(Mcu_Dio_PortId[PWRCTRL_CFG_PRIVATE_PORT_V33_PERI]);
        if(mcu_dio_ret_v33peri == (U1)STD_HIGH){
            Mcu_OffStep_GNSS    = (uint8)MCU_STEP_GNSS_OVERALL_1;   /* GNSS制御の遷移状態クリア */
            Mcu_OffTime_GNSS    = (uint16)0U;
            Mcu_OffCnt_GNSS     = (uint8)0U;
            mcu_return          = (uint16)PWROFF_BIT_OFF;    /* 未完了通知 */
        }
        break;
    
    default:
        /* do nothing */
        break;
    }


    return(mcu_return);
}

/*****************************************************************************
  Function      : u2_s_McuDev_Pwroff_Gyro
  Description   : 
  param[in/out] : 
  return        : PWROFF_GYRO_BIT ：プロセス完了
  Note          :
*****************************************************************************/
static U2       u2_s_McuDev_Pwroff_Gyro( void )
{
    U2              u2_t_ret;
/* SENSOR_ON=Lo条件である/BU-DET＝LoはSYS電源OFF処理以降に発生する */
/* VM3の終了処理順がアプリ電源OFF→SYS電源OFFとなっており、アプリOFF処理中に/BU-DET=Loとなることがない */
/* 暫定措置として端子監視をやめ、常に終了処理完了とする 端子操作はgyro.cで実施するため問題なし */
#if 0
    Dio_LevelType   dl_t_sts;       /* ポート読出し値 */

    u2_t_ret    = (U2)PWROFF_BIT_OFF;
    dl_t_sts    = (Dio_LevelType)STD_HIGH;

    dl_t_sts    = Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_SENSOR_ON]);

    if(dl_t_sts == (Dio_LevelType)STD_LOW){
        u2_t_ret    = (U2)PWROFF_GYRO_BIT;
    }
#else
    u2_t_ret    = (U2)PWROFF_GYRO_BIT;
#endif
    return(u2_t_ret);
}

/**** End of File ***********************************************************/