/* Mcu_NoRedun_PwrCtrl_c_v1-0-0                                             */
/****************************************************************************/
/* Copyright (C) 2024 Denso Techno Co.,Ltd. All rights reserved.            */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Mcu_NoRedun_PwrCtrl/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "Mcu_Main.h"
#include "Mcu_NoRedun_PwrCtrl.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* メイン状態遷移管理用テーブル向け 各シーケンスのON/OFF/NONを管理する構造体定義 */
typedef struct {
    uint8 metbb_sts;
    uint8 disp_sts;
    uint8 hub_sts;
} ST_NOREDUN_NXYSTS;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/* CentralからのON/OFFシーケンス起動要求 */
uint8  Mcu_Pwr_Sts;

/* 状態遷移管理用ステータス */
static uint8  Mcu_NoRedun_Sts;

/* 実行中のONシーケンス管理 */
static uint8  Mcu_NoRedun_OnSequence;

/* 非冗長電源間ウェイトタイムカウンタ */
static uint16  Mcu_BetWait_Time;

/* (Meter+BB Display ON/OFF Sequence */
static uint8  NoRedun_MetBB_Chk;
static uint8  Mcu_MetBB_OnStep;
static uint8  Mcu_MetBB_OffStep;
static uint16  Mcu_MBon_Time;
static uint16  Mcu_Gviftx_Mbwk_Time;
static uint16  Mcu_Gviftx_Mbwk_Off_Time;
static uint16  Mcu_MBoff_Time;

/* Center Display ON/OFF Sequence */
static uint8  NoRedun_Disp_Chk;
static uint8  Mcu_Disp_OnStep;
static uint8  Mcu_Disp_OffStep;
static uint16  Mcu_Dspon_Time;
static uint16  Mcu_Gviftx_Dspwk_Time;
static uint16  Mcu_Gviftx_Dspwk_Off_Time;
static uint16  Mcu_Dspoff_Time;

/* DSRC(HUB) ON/OFF Sequence */
static uint8  NoRedun_Hub_Chk;
static uint8  Mcu_Hub_OnStep;
static uint8  Mcu_Hub_OffStep;
static uint16 Mcu_Hubon_Time;
static uint16 Mcu_Hubwk_Time;
static uint16 Mcu_Hubwk_Off_Time;
static uint16 Mcu_Huboff_Time;

/* SYS系デバイス終了状態(extern) */
uint8  Mcu_Dev_Pwroff_Sts;

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/* メイン状態遷移管理用テーブル */
/* 前回と次回の状態の組み合わせで、シーケンスの処理関数の処理内容を決定する */
const ST_NOREDUN_NXYSTS MCU_PWRCTRL_NXTSTS[MCU_NOREDUN_STATE_NUM][MCU_NOREDUN_STATE_NUM] = {
  /* 前回状態：OFF */
  /* Meter+BB Display       CenterDisplay         DSRC(Hub) */
  { {MCU_NOREDUN_PWR_NON,   MCU_NOREDUN_PWR_NON,  MCU_NOREDUN_PWR_NON },   /* 次回状態：OFF */
    {MCU_NOREDUN_PWR_ON,    MCU_NOREDUN_PWR_NON,  MCU_NOREDUN_PWR_NON },   /* 次回状態：駐車中起動 */
    {MCU_NOREDUN_PWR_ON,    MCU_NOREDUN_PWR_ON,   MCU_NOREDUN_PWR_NON },   /* 次回状態：見た目オフ起動 */
    {MCU_NOREDUN_PWR_ON,    MCU_NOREDUN_PWR_ON,   MCU_NOREDUN_PWR_ON  }    /* 次回状態：見た目オン起動 */
  },
  
  /* 前回状態：駐車中起動 */
  /* Meter+BB Display       CenterDisplay         DSRC(Hub) */
  { {MCU_NOREDUN_PWR_OFF,   MCU_NOREDUN_PWR_OFF,  MCU_NOREDUN_PWR_OFF },   /* 次回状態：OFF */
    {MCU_NOREDUN_PWR_NON,   MCU_NOREDUN_PWR_NON,  MCU_NOREDUN_PWR_NON },   /* 次回状態：駐車中起動 */
    {MCU_NOREDUN_PWR_NON,   MCU_NOREDUN_PWR_ON,   MCU_NOREDUN_PWR_NON },   /* 次回状態：見た目オフ起動 */
    {MCU_NOREDUN_PWR_NON,   MCU_NOREDUN_PWR_ON,   MCU_NOREDUN_PWR_ON  }    /* 次回状態：見た目オン起動 */
  },

  /* 前回状態：見た目オフ起動 */
  /* Meter+BB Display       CenterDisplay         DSRC(Hub) */
  { {MCU_NOREDUN_PWR_OFF,   MCU_NOREDUN_PWR_OFF,  MCU_NOREDUN_PWR_OFF },   /* 次回状態：OFF */
    {MCU_NOREDUN_PWR_NON,   MCU_NOREDUN_PWR_OFF,  MCU_NOREDUN_PWR_NON },   /* 次回状態：駐車中起動 */
    {MCU_NOREDUN_PWR_NON,   MCU_NOREDUN_PWR_NON,  MCU_NOREDUN_PWR_NON },   /* 次回状態：見た目オフ起動 */
    {MCU_NOREDUN_PWR_NON,   MCU_NOREDUN_PWR_NON,  MCU_NOREDUN_PWR_ON  }    /* 次回状態：見た目オン起動 */
  },

  /* 前回状態：見た目オン起動 */
  /* Meter+BB Display       CenterDisplay         DSRC(Hub) */
  { {MCU_NOREDUN_PWR_OFF,   MCU_NOREDUN_PWR_OFF,  MCU_NOREDUN_PWR_OFF },   /* 次回状態：OFF */
    {MCU_NOREDUN_PWR_NON,   MCU_NOREDUN_PWR_OFF,  MCU_NOREDUN_PWR_OFF },   /* 次回状態：駐車中起動 */
    {MCU_NOREDUN_PWR_NON,   MCU_NOREDUN_PWR_NON,  MCU_NOREDUN_PWR_OFF },   /* 次回状態：見た目オフ起動 */
    {MCU_NOREDUN_PWR_NON,   MCU_NOREDUN_PWR_NON,  MCU_NOREDUN_PWR_NON }    /* 次回状態：見た目オン起動 */
  }
};

/*--------------------------------------------------------------------------*/
/* Functions                                                                */
/*--------------------------------------------------------------------------*/
/* CAN,直線入力,Central入力から次回状態遷移先を決定する */
uint8 Mcu_NoRedun_PwrCtrl_Nxtsts( void );

/* (Meter+BB Display ON/OFF Sequence */
void Mcu_NoRedun_PwrCtrl_MetBB( void );
void Mcu_NoRedun_PwrOn_MbPwr( void );
void Mcu_NoRedun_Wk_GvifTx_MetBB( void );
void Mcu_NoRedun_WkOff_GvifTx_MetBB( void );
void Mcu_NoRedun_PwrOff_MbPwr( void );

/* Center Display ON/OFF Sequence */
void Mcu_NoRedun_PwrCtrl_Disp( void );
void Mcu_NoRedun_PwrOn_Dsp( void );
void Mcu_NoRedun_Wk_GvifTx_Disp( void );
void Mcu_NoRedun_WkOff_GvifTx_Disp( void );
void Mcu_NoRedun_PwrOff_Dsp( void );

/* DSRC(HUB) ON/OFF  */
void Mcu_NoRedun_PwrCtrl_Hub( void );
void Mcu_NoRedun_PwrOn_Hub( void );
void Mcu_NoRedun_Wk_Hub( void );
void Mcu_NoRedun_WkOff_Hub( void );
void Mcu_NoRedun_PwrOff_Hub( void );

/* 非冗長電源間ウェイトタイムのカウント */
void Mcu_NoRedun_BetWait( void );

void  Mcu_Dev_Pwroff( void );
uint8 Mcu_Dev_Pwroff_USB( void );
uint8 Mcu_Dev_Pwroff_PictIC( void );
uint8 Mcu_Dev_Pwroff_GVIFRx( void );
uint8 Mcu_Dev_Pwroff_GVIFTx_CDisp( void );
uint8 Mcu_Dev_Pwroff_Mic( void );
uint8 Mcu_Dev_Pwroff_Ant( void );

/****************************************************************************/
/* Scheduled Functions                                                      */
/****************************************************************************/
/****************************************************************************/
/* Service API                                                              */
/****************************************************************************/
/****************************************************************************/
/*****************************************************************************
  Function      : Mcu_NoRedun_PwrCtrl_Init
  Description   : 初期化関数
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_NoRedun_PwrCtrl_Init( void )
{
  /* CentralからのON/OFFシーケンス起動要求の初期化 */
  Mcu_Pwr_Sts                  = (uint8)MCU_NOREDUN_CENTRAL_OFF;

  /* 状態遷移管理用ステータスの初期化 */
  Mcu_NoRedun_Sts                   = (uint8)MCU_NOREDUN_STATE_OFF;

  /* 実行中のONシーケンスの初期化 */
  Mcu_NoRedun_OnSequence            = (uint8)MCU_NOREDUN_ONSEQ_NON;

  /* 非冗長電源ON/OFFトリガの初期化 */
  NoRedun_MetBB_Chk                 = (uint8)MCU_NOREDUN_PWR_NON;
  NoRedun_Disp_Chk                  = (uint8)MCU_NOREDUN_PWR_NON;
  NoRedun_Hub_Chk                   = (uint8)MCU_NOREDUN_PWR_NON;

  /* 現在起動/終了ステップの初期化 */
  Mcu_MetBB_OnStep                  = (uint8)MCU_NOREDUN_STEP1;
  Mcu_Disp_OnStep                   = (uint8)MCU_NOREDUN_STEP1;
  Mcu_Hub_OnStep                    = (uint8)MCU_NOREDUN_STEP1;
  Mcu_MetBB_OffStep                 = (uint8)MCU_NOREDUN_STEP1;
  Mcu_Disp_OffStep                  = (uint8)MCU_NOREDUN_STEP1;
  Mcu_Hub_OffStep                   = (uint8)MCU_NOREDUN_STEP1;

  /* 待機時間測定用RAMの初期化 */
  Mcu_BetWait_Time                  = (uint16)MCU_NOREDUN_WAIT_TIME_FIN;
  Mcu_MBon_Time                     = (uint16)0U;
  Mcu_Gviftx_Mbwk_Time              = (uint16)0U;
  Mcu_Gviftx_Mbwk_Off_Time          = (uint16)0U;
  Mcu_MBoff_Time                    = (uint16)0U;
  Mcu_Dspon_Time                    = (uint16)0U;
  Mcu_Gviftx_Dspwk_Time             = (uint16)0U;
  Mcu_Gviftx_Dspwk_Off_Time         = (uint16)0U;
  Mcu_Dspoff_Time                   = (uint16)0U;
  Mcu_Hubon_Time                    = (uint16)0U;
  Mcu_Hubwk_Time                    = (uint16)0U;
  Mcu_Hubwk_Off_Time                = (uint16)0U;
  Mcu_Huboff_Time                   = (uint16)0U;

  /* SYS系デバイス終了状態 */
  Mcu_Dev_Pwroff_Sts                = (uint8)FALSE;
}

/*****************************************************************************
  Function      : Mcu_NoRedun_PwrCtrl_MainFunction
  Description   : メインタスク
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_NoRedun_PwrCtrl_MainFunction( void )
{
  uint8 mcu_nxtsts; /* 次回状態遷移先 */
  /* 各起動要因から次回状態遷移先を決定する */
  mcu_nxtsts  = Mcu_NoRedun_PwrCtrl_Nxtsts();

  /* 各シーケンスの処理関数の動作を決定する(ON/OFF) */
  /* NONの場合はステータス更新しない(ON/OFF動作の途中停止防止) ON⇔OFFはステータス更新する */
  if(MCU_PWRCTRL_NXTSTS[Mcu_NoRedun_Sts][mcu_nxtsts].metbb_sts != MCU_NOREDUN_PWR_NON){
    NoRedun_MetBB_Chk = MCU_PWRCTRL_NXTSTS[Mcu_NoRedun_Sts][mcu_nxtsts].metbb_sts;
  }
  if(MCU_PWRCTRL_NXTSTS[Mcu_NoRedun_Sts][mcu_nxtsts].disp_sts != MCU_NOREDUN_PWR_NON){
    NoRedun_Disp_Chk  = MCU_PWRCTRL_NXTSTS[Mcu_NoRedun_Sts][mcu_nxtsts].disp_sts;
  }
  if(MCU_PWRCTRL_NXTSTS[Mcu_NoRedun_Sts][mcu_nxtsts].hub_sts != MCU_NOREDUN_PWR_NON){
    NoRedun_Hub_Chk   = MCU_PWRCTRL_NXTSTS[Mcu_NoRedun_Sts][mcu_nxtsts].hub_sts;
  }

  /* 各シーケンスの処理関数をコールし、状態遷移によって決定したON/OFF処理を実行する */
  /* 未実施の場合は処理関数内部のelseに突入し、なにも実施しない */
  Mcu_NoRedun_PwrCtrl_MetBB();
  Mcu_NoRedun_PwrCtrl_Disp();
  Mcu_NoRedun_PwrCtrl_Hub();

  /* 非冗長電源間ウェイトタイムのカウント */
  /* カウント開始はシーケンスの処理関数内でRAMリセットをもって開始する */
  Mcu_NoRedun_BetWait();

  /* 前回状態の更新 */
  Mcu_NoRedun_Sts = mcu_nxtsts;


  Mcu_Dev_Pwroff(); /* デバイスOFF制御 */
}

/*****************************************************************************
  Function      : Mcu_NoRedun_PwrCtrl_Nxtsts
  Description   : 次回状態遷移先の決定
  param[in/out] : none
  return        : 次回状態遷移先(MCU_NOREDUN_STATE_**)
  Note          : シス検,量産までの暫定対応あり
*****************************************************************************/
uint8 Mcu_NoRedun_PwrCtrl_Nxtsts( void )
{
  uint8 mcu_return;     /* 戻り値 */
  uint8 mcu_appea;      /* CAN入力：見た目オンオフ(スタブ) */
  uint8 mcu_VPSINFO1;   /* CAN入力：判定中 */
  uint8 mcu_VPSINFO2;   /* CAN入力：駐車中 */
  uint8 mcu_VPSINFO3;   /* CAN入力：乗車中 */
  uint8 mcu_VPSINFO4;   /* CAN入力：PowerON通常 */
  uint8 mcu_VPSINFO5;   /* CAN入力：PowerON緊急停止 */
  uint8 mcu_VPSINFO6;   /* CAN入力：駐車中高圧起動 */
  uint8 mcu_VPSINFO7;   /* CAN入力：駐車中高圧・温調起動 */
  uint8 mcu_VPSINFO;    /* 電源状態取り纏め */
  uint8 mcu_boot;       /* 開発時のみ使用する、BOOT入力取得(量産時削除予定) */

  mcu_return    = Mcu_NoRedun_Sts;  /* 初期値：前回保持状態 */
  mcu_appea     = (uint8)FALSE;
  mcu_VPSINFO1  = (uint8)FALSE;
  mcu_VPSINFO2  = (uint8)FALSE;
  mcu_VPSINFO3  = (uint8)FALSE;
  mcu_VPSINFO4  = (uint8)FALSE;
  mcu_VPSINFO5  = (uint8)FALSE;
  mcu_VPSINFO6  = (uint8)FALSE;
  mcu_VPSINFO7  = (uint8)FALSE;
  mcu_VPSINFO   = (uint8)0U;
  mcu_boot      = STD_LOW;

  /* シス検暫定対応：CAN入力取得処理 シス検ではPowerON固定のためコメントアウトする */
  /*
  (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO1, &mcu_VPSINFO1 );
  (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO2, &mcu_VPSINFO2 );
  (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO3, &mcu_VPSINFO3 );
  (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO4, &mcu_VPSINFO4 );
  (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO5, &mcu_VPSINFO5 );
  (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO6, &mcu_VPSINFO6 );
  (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO7, &mcu_VPSINFO7 );
  (void)Com_ReceiveSignal(ComConf_ComSignal_APOFRQ  , &mcu_appea    );
  */
  /* シス検暫定ここまで */

  /* BOOT入力値取得処理 */
  mcu_boot = Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_BOOT]);

  mcu_VPSINFO =   (mcu_appea    & (uint8)TRUE) << 7;  /* 8bit：見た目オンオフ */
  mcu_VPSINFO |=  (mcu_VPSINFO1 & (uint8)TRUE) << 6;  /* 7bit：CAN入力：判定中 */
  mcu_VPSINFO |=  (mcu_VPSINFO2 & (uint8)TRUE) << 5;  /* 6bit：CAN入力：駐車中 */
  mcu_VPSINFO |=  (mcu_VPSINFO3 & (uint8)TRUE) << 4;  /* 5bit：CAN入力：乗車中 */
  mcu_VPSINFO |=  (mcu_VPSINFO4 & (uint8)TRUE) << 3;  /* 4bit：CAN入力：PowerON通常 */
  mcu_VPSINFO |=  (mcu_VPSINFO5 & (uint8)TRUE) << 2;  /* 3bit：CAN入力：PowerON緊急停止 */
  mcu_VPSINFO |=  (mcu_VPSINFO6 & (uint8)TRUE) << 1;  /* 2bit：CAN入力：駐車中高圧起動 */
  mcu_VPSINFO |=  mcu_VPSINFO7  & (uint8)TRUE;        /* 1bit：CAN入力：駐車中高圧・温調起動 */

  if(Mcu_Pwr_Sts == MCU_NOREDUN_CENTRAL_OFF){   /* CentralからのOFFトリガ トリガをリセットして次回要求に備える */
    mcu_return  = MCU_NOREDUN_STATE_OFF;
  }
  else if(Mcu_Pwr_Sts == MCU_NOREDUN_CENTRAL_ON){   /* CentralからのONトリガ OFFトリガがくるまでONを継続 */
    /* 次回状態判定 電源ステートはONOFF仕様 図5-3 参照 */
    switch (mcu_VPSINFO)
    {
    case  0x40U:    /* 見た目：オフ ステート：状態未定 */
      mcu_return  = Mcu_NoRedun_Sts;  /* 前回状態保持 */
      break;
    case  0x20U:    /* 見た目：オフ ステート：駐車中 */
      mcu_return  = MCU_NOREDUN_STATE_PARK;  /* 駐車中起動 */
      break;
    case  0x33U:    /* 見た目：オフ ステート：乗車中 */
      mcu_return  = MCU_NOREDUN_STATE_APPOFF;  /* 見た目オフ起動 */
      break;
    case  0x3BU:    /* 見た目：オフ ステート：PowerON緊急停止 */
      mcu_return  = MCU_NOREDUN_STATE_APPON;  /* 見た目オン起動 */
      break;
    case  0x3FU:    /* 見た目：オフ ステート：PowerON通常 */
      mcu_return  = MCU_NOREDUN_STATE_APPON;  /* 見た目オン起動 */
      break;
    case  0x22U:    /* 見た目：オフ ステート：駐車中 高圧起動 */
      mcu_return  = MCU_NOREDUN_STATE_PARK;  /* 駐車中起動 */
      break;
    case  0x23U:    /* 見た目：オフ ステート：駐車中 高圧・温調起動 */
      mcu_return  = MCU_NOREDUN_STATE_PARK;  /* 駐車中起動 */
      break;
    case  0xC0U:    /* 見た目：オン ステート：状態未定 */
      mcu_return  = Mcu_NoRedun_Sts;  /* 前回状態保持 */
      break;
    case  0xA0U:    /* 見た目：オン ステート：駐車中 */
      mcu_return  = MCU_NOREDUN_STATE_PARK;  /* 駐車中起動 */
      break;
    case  0xB3U:    /* 見た目：オン ステート：乗車中 */
      mcu_return  = MCU_NOREDUN_STATE_APPON;  /* 見た目オン起動 */
      break;
    case  0xBBU:    /* 見た目：オン ステート：PowerON緊急停止 */
      mcu_return  = MCU_NOREDUN_STATE_APPON;  /* 見た目オン起動 */
      break;
    case  0xBFU:    /* 見た目：オン ステート：PowerON通常 */
      mcu_return  = MCU_NOREDUN_STATE_APPON;  /* 見た目オン起動 */
      break;
    case  0xA2U:    /* 見た目：オン ステート：駐車中 高圧起動 */
      mcu_return  = MCU_NOREDUN_STATE_PARK;  /* 駐車中起動 */
      break;
    case  0xA3U:    /* 見た目：オン ステート：駐車中 高圧・温調起動 */
      mcu_return  = MCU_NOREDUN_STATE_PARK;  /* 駐車中起動 */
      break;
    default:
      /* 遷移条件の一致なし */
      break;
    }
  }
  else{
    /* Centralからの要求なし */
  }

  /* シス検暫定対応：CentralからON要求があった場合、電源ステートは固定でPowerON通常とする */
  if(Mcu_Pwr_Sts == MCU_NOREDUN_CENTRAL_ON){
    mcu_return  = MCU_NOREDUN_STATE_APPON;
  }
  /* シス検暫定ここまで */

  /* 量産向け暫定 */
  if(mcu_boot == STD_HIGH){   /* BOOT=Hiを検知した場合、どの状態でも見た目オン起動へ上書き */
    mcu_return  = (uint8)MCU_NOREDUN_STATE_APPON;   /* 電源ON 見た目オン起動 */
  }
  /* 量産向け暫定ここまで */

  return(mcu_return);
}

/*****************************************************************************
  Function      : Mcu_NoRedun_PwrCtrl_MetBB
  Description   : Meter+BB Display ON/OFFシーケンス
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_NoRedun_PwrCtrl_MetBB( void )
{
  /* CentralからのON要求あり かつ 実行中のONシーケンスがなしorMeter+BBの場合 */
  if(NoRedun_MetBB_Chk == MCU_NOREDUN_PWR_ON &&
      (Mcu_NoRedun_OnSequence == MCU_NOREDUN_ONSEQ_NON || Mcu_NoRedun_OnSequence == MCU_NOREDUN_ONSEQ_METBB)){
    /* OFF側のSTEP管理RAM,タイマをクリアしてOFF2週目も実行できるようにする */
    Mcu_MetBB_OffStep         = (uint8)MCU_NOREDUN_STEP1;
    Mcu_Gviftx_Mbwk_Off_Time  = (uint16)0U;
    Mcu_MBoff_Time            = (uint16)0U;

    switch (Mcu_MetBB_OnStep)
    {
    case MCU_NOREDUN_STEP1:
      /* 実行中のONシーケンスをMeter+BBに設定 */
      Mcu_NoRedun_OnSequence = (uint8)MCU_NOREDUN_ONSEQ_METBB;

      Mcu_NoRedun_PwrOn_MbPwr();

      if(Mcu_MBon_Time == MCU_NOREDUN_WAIT_TIME_FIN){
        /* STEP1が完了していれば次のSTEPに進める */
        Mcu_MetBB_OnStep = (uint8)MCU_NOREDUN_STEP2;
      }
      break;

    case MCU_NOREDUN_STEP2:
      Mcu_NoRedun_Wk_GvifTx_MetBB();

      if(Mcu_Gviftx_Mbwk_Time == MCU_NOREDUN_WAIT_TIME_FIN){
        /* STEP1,2が完了していれば正常起動を設定 */
        Mcu_MetBB_OnStep      = (uint8)MCU_NOREDUN_STEP_OK;
      }
      /* 非冗長電源間ウェイトタイムをクリアしカウント開始する */
      Mcu_BetWait_Time      = (uint16)0U;
      break;

    case MCU_NOREDUN_STEP3:     /* fall through */
    case MCU_NOREDUN_STEP4:     /* fall through */
    case MCU_NOREDUN_STEP_OK:
      /* 正常起動時は何もしない */
      break;
    
    default:
      /* 異常系は未考慮 */
      break;
    }
  }
  /* CentralからのOFF要求あり */
  else if(NoRedun_MetBB_Chk == MCU_NOREDUN_PWR_OFF){
    /* ON側のSTEP管理RAM,タイマをクリアしてON2週目も実行できるようにする */
    Mcu_MetBB_OnStep  = MCU_NOREDUN_STEP1;
    Mcu_MBon_Time         = (uint16)0U;
    Mcu_Gviftx_Mbwk_Time  = (uint16)0U;

    switch (Mcu_MetBB_OffStep)
    {
    case MCU_NOREDUN_STEP1:
      Mcu_NoRedun_WkOff_GvifTx_MetBB();

      if(Mcu_Gviftx_Mbwk_Off_Time == MCU_NOREDUN_WAIT_TIME_FIN){
        /* STEP1が完了していれば次のSTEPに進める */
        Mcu_MetBB_OffStep = (uint8)MCU_NOREDUN_STEP2;
      }
      break;

    case MCU_NOREDUN_STEP2:
      Mcu_NoRedun_PwrOff_MbPwr();

      if(Mcu_MBoff_Time == MCU_NOREDUN_WAIT_TIME_FIN){
        /* STEP1,2が完了していれば正常終了を設定 */
        Mcu_MetBB_OffStep         = (uint8)MCU_NOREDUN_STEP_OK;
      }
      break;

    case MCU_NOREDUN_STEP3:     /* fall through */
    case MCU_NOREDUN_STEP4:     /* fall through */
    case MCU_NOREDUN_STEP_OK:
      /* 正常終了時は何もしない */
      break;
    
    default:
      /* 異常系は未考慮 */
      break;
    }
  }
  else {    /* MCU_NOREDUN_PWR_NON：要求なし or Mcu_BetWait_Time≠FIN：非冗長電源間ウェイトタイム中 */
    /* do nothing */
  }

  return;
}

/*****************************************************************************
  Function      : Mcu_NoRedun_PwrOn_MbPwr
  Description   : 非冗長電源ON制御 MET+BB-PWR-ON
                  (ソフトウェア処理：MCU →MET+BB Display)
  param[in/out] : none
  return        : none
  Note          : タイマー閾値が0のため、以上ではなく一致で判定
*****************************************************************************/
void Mcu_NoRedun_PwrOn_MbPwr( void )
{
  /* MET+BB-PWR-ON */
  if(Mcu_MBon_Time == MCU_WAIT_MBPWR_TIME){ 
    Mcu_Dev_Pwron_SetPort(MCU_PORT_MBPWR, MCU_DIO_HIGH);
    Mcu_MBon_Time = (uint16)MCU_NOREDUN_WAIT_TIME_FIN;
  }
  
  if(Mcu_MBon_Time != MCU_NOREDUN_WAIT_TIME_FIN){
    Mcu_MBon_Time++;
  }
  
  return;
}

/*****************************************************************************
  Function      : Mcu_NoRedun_Wk_GvifTx_MetBB
  Description   : 非冗長電源ON制御 GVIF-TX(MET+BB)-WAKE
                  (ソフトウェア処理：MCU →MET+BB Display)※GVIF信号重畳
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_NoRedun_Wk_GvifTx_MetBB( void )
{
  /* GVIF-TX(MET+BB)-WAKE */
  if(Mcu_Gviftx_Mbwk_Time == MCU_WAIT_GVIF_TX_MBWK_TIME){ 
    Mcu_Dev_Pwron_SetPort(MCU_PORT_GVIF_TX_MBWK, MCU_DIO_HIGH);
    Mcu_Gviftx_Mbwk_Time = (uint16)MCU_NOREDUN_WAIT_TIME_FIN;
  }
  
  if(Mcu_Gviftx_Mbwk_Time != MCU_NOREDUN_WAIT_TIME_FIN){
    Mcu_Gviftx_Mbwk_Time++;
  }
  
  return;
}

/*****************************************************************************
  Function      : Mcu_NoRedun_WkOff_GvifTx_MetBB
  Description   : 非冗長電源OFF制御 GVIF-TX(MET+BB)-WAKE
                  (ソフトウェア処理：MCU →MET+BB Display)※GVIF信号重畳
  param[in/out] : none
  return        : none
  Note          : タイマー閾値が0のため、以上ではなく一致で判定
*****************************************************************************/
void Mcu_NoRedun_WkOff_GvifTx_MetBB( void )
{
  /* GVIF-TX(MET+BB)-WAKE */
  if(Mcu_Gviftx_Mbwk_Off_Time == MCU_WAIT_GVIF_TX_MBWK_OFF_TIME){ 
    Mcu_Dev_Pwron_SetPort(MCU_PORT_GVIF_TX_MBWK, MCU_DIO_LOW);
    Mcu_Gviftx_Mbwk_Off_Time = (uint16)MCU_NOREDUN_WAIT_TIME_FIN;
  }
  
  if(Mcu_Gviftx_Mbwk_Off_Time != MCU_NOREDUN_WAIT_TIME_FIN){
    Mcu_Gviftx_Mbwk_Off_Time++;
  }
  
  return;
}

/*****************************************************************************
  Function      : Mcu_NoRedun_PwrOff_MbPwr
  Description   : 非冗長電源OFF制御 MET+BB-PWR-ON
                  (ソフトウェア処理：MCU →MET+BB Display)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_NoRedun_PwrOff_MbPwr( void )
{
  /* MET+BB-PWR-OFF */
  if(Mcu_MBoff_Time == MCU_WAIT_MBPWR_OFF_TIME){ 
    Mcu_Dev_Pwron_SetPort(MCU_PORT_MBPWR, MCU_DIO_LOW);
    Mcu_MBoff_Time = (uint16)MCU_NOREDUN_WAIT_TIME_FIN;
  }
  
  if(Mcu_MBoff_Time != MCU_NOREDUN_WAIT_TIME_FIN){
    Mcu_MBoff_Time++;
  }
  
  return;
}

/*****************************************************************************
  Function      : Mcu_NoRedun_PwrCtrl_Disp
  Description   : Center Display ON/OFFシーケンス
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_NoRedun_PwrCtrl_Disp( void )
{
  /* CentralからのON要求あり かつ 実行中のONシーケンスがなしorCenterDispの場合 */
  if(NoRedun_Disp_Chk == MCU_NOREDUN_PWR_ON &&
      (Mcu_NoRedun_OnSequence == MCU_NOREDUN_ONSEQ_NON || Mcu_NoRedun_OnSequence == MCU_NOREDUN_ONSEQ_CNTDSP)){
    /* OFF側のSTEP管理RAM,タイマをクリアしてOFF2週目も実行できるようにする */
    Mcu_Disp_OffStep  = MCU_NOREDUN_STEP1;
    Mcu_Gviftx_Dspwk_Off_Time = (uint16)0U;
    Mcu_Dspoff_Time           = (uint16)0U;

    switch (Mcu_Disp_OnStep)
    {
    case MCU_NOREDUN_STEP1:
      /* 実行中のONシーケンスをCenterDsipに設定 */
      Mcu_NoRedun_OnSequence = (uint16)MCU_NOREDUN_ONSEQ_CNTDSP;

      Mcu_NoRedun_PwrOn_Dsp();

      if(Mcu_Dspon_Time == MCU_NOREDUN_WAIT_TIME_FIN){
        /* STEP1が完了していれば次のSTEPに進める */
        Mcu_Disp_OnStep = (uint16)MCU_NOREDUN_STEP2;
      }
      break;

    case MCU_NOREDUN_STEP2:
      Mcu_NoRedun_Wk_GvifTx_Disp();

      if(Mcu_Gviftx_Dspwk_Time == MCU_NOREDUN_WAIT_TIME_FIN){
        /* STEP1,2が完了していれば正常起動を設定 */
        Mcu_Disp_OnStep       = (uint16)MCU_NOREDUN_STEP_OK;
      }
      /* 非冗長電源間ウェイトタイムをクリアしカウント開始する */
      Mcu_BetWait_Time      = (uint16)0U;
      break;

    case MCU_NOREDUN_STEP3:     /* fall through */
    case MCU_NOREDUN_STEP4:     /* fall through */
    case MCU_NOREDUN_STEP_OK:
      /* 正常起動時は何もしない */
      break;
    
    default:
      /* 異常系は未考慮 */
      break;
    }
  }
  else if(NoRedun_Disp_Chk == MCU_NOREDUN_PWR_OFF){
    /* ON側のSTEP管理RAM,タイマをクリアしてON2週目も実行できるようにする */
    Mcu_Disp_OnStep  = MCU_NOREDUN_STEP1;
    Mcu_Dspon_Time        = (uint16)0U;
    Mcu_Gviftx_Dspwk_Time = (uint16)0U;

    switch (Mcu_Disp_OffStep)
    {
    case MCU_NOREDUN_STEP1:
      Mcu_NoRedun_WkOff_GvifTx_Disp();

      if(Mcu_Gviftx_Dspwk_Off_Time == MCU_NOREDUN_WAIT_TIME_FIN){
        /* STEP1が完了していれば次のSTEPに進める */
        Mcu_Disp_OffStep = (uint8)MCU_NOREDUN_STEP2;
      }
      break;

    case MCU_NOREDUN_STEP2:
      Mcu_NoRedun_PwrOff_Dsp();

      if(Mcu_Dspoff_Time == MCU_NOREDUN_WAIT_TIME_FIN){
        /* STEP1,2が完了していれば正常終了を設定 */
        Mcu_Disp_OffStep          = (uint8)MCU_NOREDUN_STEP_OK;
      }
      break;

    case MCU_NOREDUN_STEP3:     /* fall through */
    case MCU_NOREDUN_STEP4:     /* fall through */
    case MCU_NOREDUN_STEP_OK:
      /* 正常終了時は何もしない */
      break;
    
    default:
      /* 異常系は未考慮 */
      break;
    }
  }
  else {    /* MCU_NOREDUN_PWR_NON：要求なし or Mcu_BetWait_Time≠FIN：非冗長電源間ウェイトタイム中 */
    /* do nothing */
  }
  return;
}

/*****************************************************************************
  Function      : Mcu_NoRedun_PwrOn_Dsp
  Description   : 非冗長電源ON制御 DISP-PWR-ON
                  (ソフトウェア処理：MCU →Center Display)
  param[in/out] : none
  return        : none
  Note          : タイマー閾値が0のため、以上ではなく一致で判定
*****************************************************************************/
void Mcu_NoRedun_PwrOn_Dsp( void )
{
  /* DISP-PWR-ON */
  if(Mcu_Dspon_Time == MCU_WAIT_DISP_TIME){ 
    Mcu_Dev_Pwron_SetPort(MCU_PORT_DISP, MCU_DIO_HIGH);
    Mcu_Dspon_Time = (uint16)MCU_NOREDUN_WAIT_TIME_FIN;
  }
    
  if(Mcu_Dspon_Time != MCU_NOREDUN_WAIT_TIME_FIN){
    Mcu_Dspon_Time++;
  }
    
  return;
}

/*****************************************************************************
  Function      : Mcu_NoRedun_Wk_GvifTx_Disp
  Description   : 非冗長電源ON制御 GVIF-TX(C-DISP)-WAKE
                  (ソフトウェア処理：MCU →Center Display)※GVIF信号重畳
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_NoRedun_Wk_GvifTx_Disp( void )
{
  /* GVIF-TX(MET+BB)-WAKE */
  if(Mcu_Gviftx_Dspwk_Time == MCU_WAIT_GVIF_TX_DSPWK_TIME){ 
    Mcu_Dev_Pwron_SetPort(MCU_PORT_GVIF_TX_DSPWK, MCU_DIO_HIGH);
    Mcu_Gviftx_Dspwk_Time = (uint16)MCU_NOREDUN_WAIT_TIME_FIN;
  }
    
  if(Mcu_Gviftx_Dspwk_Time != MCU_NOREDUN_WAIT_TIME_FIN){
    Mcu_Gviftx_Dspwk_Time++;
  }
    
  return;
}

/*****************************************************************************
  Function      : Mcu_NoRedun_WkOff_GvifTx_Disp
  Description   : 非冗長電源OFF制御 GVIF-TX(C-DISP)-WAKE
                  (ソフトウェア処理：MCU →Center Display)※GVIF信号重畳
  param[in/out] : none
  return        : none
  Note          : タイマー閾値が0のため、以上ではなく一致で判定
*****************************************************************************/
void Mcu_NoRedun_WkOff_GvifTx_Disp( void )
{
  /* GVIF-TX(MET+BB)-WAKE */
  if(Mcu_Gviftx_Dspwk_Off_Time == MCU_WAIT_GVIF_TX_DSPWK_OFF_TIME){ 
    Mcu_Dev_Pwron_SetPort(MCU_PORT_GVIF_TX_DSPWK, MCU_DIO_LOW);
    Mcu_Gviftx_Dspwk_Off_Time = (uint16)MCU_NOREDUN_WAIT_TIME_FIN;
  }
    
  if(Mcu_Gviftx_Dspwk_Off_Time != MCU_NOREDUN_WAIT_TIME_FIN){
    Mcu_Gviftx_Dspwk_Off_Time++;
  }

  return;
}

/*****************************************************************************
  Function      : Mcu_NoRedun_PwrOff_Dsp
  Description   : 非冗長電源OFF制御 DISP-PWR-ON
                  (ソフトウェア処理：MCU →Center Display)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_NoRedun_PwrOff_Dsp( void )
{
  /* DISP-PWR-Off */
  if(Mcu_Dspoff_Time == MCU_WAIT_DISP_OFF_TIME){ 
    Mcu_Dev_Pwron_SetPort(MCU_PORT_DISP, MCU_DIO_LOW);
    Mcu_Dspoff_Time = (uint16)MCU_NOREDUN_WAIT_TIME_FIN;
  }
    
  if(Mcu_Dspoff_Time != MCU_NOREDUN_WAIT_TIME_FIN){
    Mcu_Dspoff_Time++;
  }
    
  return;
}

/*****************************************************************************
  Function      : Mcu_NoRedun_PwrCtrl_Hub
  Description   : DSRC(HUB) ON/OFFシーケンス
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_NoRedun_PwrCtrl_Hub( void )
{
  /* CentralからのON要求あり かつ 実行中のONシーケンスがなしorDSRC(HUB)の場合 */
  if(NoRedun_Hub_Chk == MCU_NOREDUN_PWR_ON &&
      (Mcu_NoRedun_OnSequence == MCU_NOREDUN_ONSEQ_NON || Mcu_NoRedun_OnSequence == MCU_NOREDUN_ONSEQ_DSRC)){
    /* Off側のSTEP管理RAM,タイマをクリアしてOFF2週目も実行できるようにする */
    Mcu_Hub_OffStep  = MCU_NOREDUN_STEP1;
    Mcu_Hubwk_Off_Time  = (uint16)0U;
    Mcu_Huboff_Time     = (uint16)0U;

    switch (Mcu_Hub_OnStep)
    {
    case MCU_NOREDUN_STEP1:
      /* 実行中のONシーケンスをDSRC(HUB)に設定 */
      Mcu_NoRedun_OnSequence = (uint8)MCU_NOREDUN_ONSEQ_DSRC;

      Mcu_NoRedun_PwrOn_Hub();

      if(Mcu_Hubon_Time == MCU_NOREDUN_WAIT_TIME_FIN){
        /* STEP1が完了していれば次のSTEPに進める */
        Mcu_Hub_OnStep = (uint8)MCU_NOREDUN_STEP2;
      }
      break;

    case MCU_NOREDUN_STEP2:
      Mcu_NoRedun_Wk_Hub();

      if(Mcu_Hubwk_Time == MCU_NOREDUN_WAIT_TIME_FIN){
        /* STEP1,2が完了していれば正常起動を設定 */
        Mcu_Hub_OnStep    = (uint8)MCU_NOREDUN_STEP_OK;
      }
      /* 非冗長電源間ウェイトタイムをクリアしカウント開始する */
      Mcu_BetWait_Time      = (uint16)0U;
      break;

    case MCU_NOREDUN_STEP3:     /* fall through */
    case MCU_NOREDUN_STEP4:     /* fall through */
    case MCU_NOREDUN_STEP_OK:
      /* 正常起動時は何もしない */
      break;
    
    default:
      /* 異常系は未考慮 */
      break;
    }
  }
  else if(NoRedun_Hub_Chk == MCU_NOREDUN_PWR_OFF){
    /* ON側のSTEP管理RAM,タイマをクリアしてON2週目も実行できるようにする */
    Mcu_Hub_OnStep  = MCU_NOREDUN_STEP1;
    Mcu_Hubon_Time    = (uint16)0U;
    Mcu_Hubwk_Time    = (uint16)0U;
    switch (Mcu_Hub_OffStep)
    {
    case MCU_NOREDUN_STEP1:
      Mcu_NoRedun_WkOff_Hub();

      if(Mcu_Hubwk_Off_Time == MCU_NOREDUN_WAIT_TIME_FIN){
        /* STEP1が完了していれば次のSTEPに進める */
        Mcu_Hub_OffStep = (uint8)MCU_NOREDUN_STEP2;
      }
      break;

    case MCU_NOREDUN_STEP2:
      Mcu_NoRedun_PwrOff_Hub();

      if(Mcu_Huboff_Time == MCU_NOREDUN_WAIT_TIME_FIN){
        /* STEP1,2が完了していれば正常終了を設定 */
        Mcu_Hub_OffStep     = (uint8)MCU_NOREDUN_STEP_OK;
      }
      break;

    case MCU_NOREDUN_STEP3:     /* fall through */
    case MCU_NOREDUN_STEP4:     /* fall through */
    case MCU_NOREDUN_STEP_OK:
      /* 正常終了時は何もしない */
      break;
    
    default:
      /* 異常系は未考慮 */
      break;
    }
  }
  else {    /* MCU_NOREDUN_PWR_NON：要求なし or Mcu_BetWait_Time≠FIN：非冗長電源間ウェイトタイム中 */
    /* do nothing */
  }

  return;
}

/*****************************************************************************
  Function      : Mcu_NoRedun_PwrOn_Hub
  Description   : 非冗長電源ON制御 DSRC(HUB)-PWR-ON
                  (ソフトウェア処理：MCU →DSRC(HUB) Power SW)
  param[in/out] : none
  return        : none
  Note          : タイマー閾値が0のため、以上ではなく一致で判定
*****************************************************************************/
void Mcu_NoRedun_PwrOn_Hub( void )
{
  /* DSRC(HUB)-PWR-ON */
  if(Mcu_Hubon_Time == MCU_WAIT_HUB_PWRON_TIME){ 
    Mcu_Dev_Pwron_SetPort(MCU_PORT_HUB_PWRON, MCU_DIO_HIGH);
    Mcu_Hubon_Time = (uint16)MCU_NOREDUN_WAIT_TIME_FIN;
  }
    
  if(Mcu_Hubon_Time != MCU_NOREDUN_WAIT_TIME_FIN){
    Mcu_Hubon_Time++;
  }
    
  return;
}

/*****************************************************************************
  Function      : Mcu_NoRedun_Wk_Hub
  Description   : 非冗長電源ON制御 DSRC(HUB)-WAKE
                  (ソフトウェア処理：MCU →DSRC(HUB))
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_NoRedun_Wk_Hub( void )
{
  /* DSRC(HUB)-WAKE */
  if(Mcu_Hubwk_Time == MCU_WAIT_HUB_WAKE_TIME){ 
    Mcu_Dev_Pwron_SetPort(MCU_PORT_HUB_WK, MCU_DIO_HIGH);
    Mcu_Hubwk_Time = (uint16)MCU_NOREDUN_WAIT_TIME_FIN;
  }
    
  if(Mcu_Hubwk_Time != MCU_NOREDUN_WAIT_TIME_FIN){
    Mcu_Hubwk_Time++;
  }
    
  return;
}

/*****************************************************************************
  Function      : Mcu_NoRedun_WkOff_Hub
  Description   : 非冗長電源OFF制御 DSRC(HUB)-WAKE
                  (ソフトウェア処理：MCU →DSRC(HUB))
  param[in/out] : none
  return        : none
  Note          : タイマー閾値が0のため、以上ではなく一致で判定
*****************************************************************************/
void Mcu_NoRedun_WkOff_Hub( void )
{
  /* DSRC(HUB)-WAKE-OFF */
  if(Mcu_Hubwk_Off_Time == MCU_WAIT_HUB_WAKE_OFF_TIME){ 
    Mcu_Dev_Pwron_SetPort(MCU_PORT_HUB_WK, MCU_DIO_LOW);
    Mcu_Hubwk_Off_Time = (uint16)MCU_NOREDUN_WAIT_TIME_FIN;
  }
    
  if(Mcu_Hubwk_Off_Time != MCU_NOREDUN_WAIT_TIME_FIN){
    Mcu_Hubwk_Off_Time++;
  }
    
  return;
}

/*****************************************************************************
  Function      : Mcu_NoRedun_PwrOff_Hub
  Description   : 非冗長電源OFF制御 DSRC(HUB)-PWR-ON
                  (ソフトウェア処理：MCU →DSRC(HUB) Power SW)
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_NoRedun_PwrOff_Hub( void )
{
  /* DSRC(HUB)-PWR-OFF */
  if(Mcu_Huboff_Time == MCU_WAIT_HUB_PWROFF_TIME){ 
    Mcu_Dev_Pwron_SetPort(MCU_PORT_HUB_PWRON, MCU_DIO_LOW);
    Mcu_Huboff_Time = (uint16)MCU_NOREDUN_WAIT_TIME_FIN;
  }
    
  if(Mcu_Huboff_Time != MCU_NOREDUN_WAIT_TIME_FIN){
    Mcu_Huboff_Time++;
  }
    
  return;
}

/*****************************************************************************
  Function      : Mcu_NoRedun_BetWait
  Description   : 非冗長電源間ウェイトタイム(突入電流対策)カウント
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_NoRedun_BetWait( void )
{
  /* ウェイトタイム経過した場合、ウェイトタイム完了通知と実行中のONシーケンスなしに設定 */
  if(Mcu_BetWait_Time == MCU_WAIT_BETWEEN_TIME){ 
    Mcu_BetWait_Time = (uint16)MCU_NOREDUN_WAIT_TIME_FIN;
    Mcu_NoRedun_OnSequence  = (uint8)MCU_NOREDUN_ONSEQ_NON;
  }
  
  /* ウェイトタイム経過前はカウント */
  if(Mcu_BetWait_Time != MCU_NOREDUN_WAIT_TIME_FIN){
    Mcu_BetWait_Time++;
  }
    
  return;
}

/*****************************************************************************
  Function      : Mcu_Noredun_PwrOn_Start
  Description   : Centralからの非冗長電源ON制御開始要求
  param[in/out] : none
  return        : none
  Note          : 非冗長電源ON要処理を実施する条件を満たした場合に、Centralから一度だけコールする。
                  実際のON処理(待ち合わせ、HWアクセス)はMET/IVI定期処理(5ms)で実施すること。
                  MET+BB Display、Center Display、DSRC(HUB)のON/OFF判定はMET/IVI側で実施すること。
*****************************************************************************/
void Mcu_Noredun_PwrOn_Start( void )
{
  Mcu_Pwr_Sts = (uint8)MCU_NOREDUN_CENTRAL_ON;

  return;
}

/*****************************************************************************
  Function      : Mcu_Noredun_PwrOff_Start
  Description   : Centralからの非冗長電源OFF制御開始要求
  param[in/out] : none
  return        : none
  Note          : 非冗長電源OFF要処理を実施する条件を満たした場合に、Centralから一度だけコールする。
                  実際のOFF処理(待ち合わせ、HWアクセス)はMET/IVI定期処理(5ms)で実施すること。
                  MET+BB Display、Center Display、DSRC(HUB)のON/OFF判定はMET/IVI側で実施すること。
*****************************************************************************/
void Mcu_Noredun_PwrOff_Start( void )
{
  Mcu_Pwr_Sts = (uint8)MCU_NOREDUN_CENTRAL_OFF;

  return;
}

/*****************************************************************************
  Function      : Mcu_Noredun_PwrOn_GetSts
  Description   : Centralへの通知：非冗長電源ONシーケンス状態問い合わせ
  param[in/out] : none
  return        : FALSE(0)：非冗長電源ONシーケンス実行中
                  TRUE(1) ：非冗長電源ONシーケンス完了
  Note          : シス検までの暫定対応あり
*****************************************************************************/
uint8 Mcu_Noredun_PwrOn_GetSts( void )
{
  uint8 mcu_return;

  mcu_return  = (uint8)FALSE; /* 初期化：非冗長電源ONシーケンス実行中 */

  /* シス検暫定対応 */
  /* 電源ステートは固定でPowerON通常であり見た目オン起動のみのため、 */
  /* 全シーケンス完了した場合のみシーケンス完了を通知する */
  if(Mcu_NoRedun_OnSequence == (uint8)MCU_NOREDUN_ONSEQ_NON &&  /* 実行中のONシーケンスなし */
    Mcu_MetBB_OnStep        == (uint8)MCU_NOREDUN_STEP_OK &&    /* Meter+BB Display ONシーケンス完了 */
    Mcu_Disp_OnStep         == (uint8)MCU_NOREDUN_STEP_OK &&    /* Center Display ONシーケンス完了 */
    Mcu_Hub_OnStep          == (uint8)MCU_NOREDUN_STEP_OK){     /* DSRC(HUB) ONシーケンス完了 */
    mcu_return  = (uint8)TRUE;
  }
  /* シス検暫定対応ここまで */


  return(mcu_return);
}
/*****************************************************************************
  Function      : Mcu_Noredun_PwrOff_GetSts
  Description   : Centralへの通知：非冗長電源OFFシーケンス状態問い合わせ
  param[in/out] : none
  return        : FALSE(0)：非冗長電源OFFシーケンス実行中
                  TRUE(1) ：非冗長電源OFFシーケンス完了
  Note          : 非冗長電源OFF要求～完了するまでの間、Centralからコールする。
*****************************************************************************/
uint8 Mcu_Noredun_PwrOff_GetSts( void )
{
  uint8 mcu_return;

  mcu_return  = (uint8)FALSE; /* 初期化：非冗長電源OFFシーケンス実行中 */

  if(Mcu_MetBB_OffStep  == (uint8)MCU_NOREDUN_STEP_OK &&  /* Meter+BB Display OFFシーケンス完了 */
    Mcu_Disp_OffStep    == (uint8)MCU_NOREDUN_STEP_OK &&  /* Center Display OFFシーケンス完了 */
    Mcu_Hub_OffStep     == (uint8)MCU_NOREDUN_STEP_OK){   /* DSRC(HUB) OFFシーケンス完了 */
    mcu_return  = (uint8)TRUE;
  }

  return(mcu_return);
}


/*****************************************************************************
  Function      : Mcu_Dev_Pwroff
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 
*****************************************************************************/
void Mcu_Dev_Pwroff( void ){

  if((Mcu_Pwr_Sts == (uint8)MCU_NOREDUN_CENTRAL_OFF)  &&
     (Mcu_Dev_Pwroff_Sts  ==  (uint8)FALSE)){
    Mcu_Dev_Pwroff_Sts   =  Mcu_Dev_Pwroff_USB();           /* USBアダプタ接続検知 */
    Mcu_Dev_Pwroff_Sts  &=  Mcu_Dev_Pwroff_PictIC();        /* 映像IC(ML86294)制御 */
    Mcu_Dev_Pwroff_Sts  &=  Mcu_Dev_Pwroff_GVIFRx();        /* GVIF3受信(CXD4984ER)制御 */
    Mcu_Dev_Pwroff_Sts  &=  Mcu_Dev_Pwroff_GVIFTx_CDisp();  /* GVIF3送信(CXD4937/57)制御 C-Disp */
    Mcu_Dev_Pwroff_Sts  &=  Mcu_Dev_Pwroff_Mic();           /* マイク電源制御 */
    Mcu_Dev_Pwroff_Sts  &=  Mcu_Dev_Pwroff_Ant();           /* アンテナ電源制御 */
    /* 全プロセスが完了していればMcu_Dev_Pwroff_StsがTRUEとなる */
  }
  else if(Mcu_Pwr_Sts == (uint8)MCU_NOREDUN_CENTRAL_ON){
    Mcu_Dev_Pwroff_Sts  = (uint8)FALSE;
  }
  else {
    /* do nothing */
  }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwroff_USB
  Description   : 
  param[in/out] : 
  return        : TRUE ：プロセス完了
                  FALSE：プロセス未完了
  Note          : 
*****************************************************************************/
uint8 Mcu_Dev_Pwroff_USB( void ){
  Mcu_Dev_Pwron_SetPort(MCU_PORT_USB_LED_ON, MCU_DIO_LOW);

  return((uint8)TRUE);
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwroff_PictIC
  Description   : 
  param[in/out] : 
  return        : TRUE ：プロセス完了
                  FALSE：プロセス未完了
  Note          : 
*****************************************************************************/
uint8 Mcu_Dev_Pwroff_PictIC( void ){
  Mcu_Dev_Pwron_SetPort(MCU_PORT_V_IC_RST, MCU_DIO_LOW);

  return((uint8)TRUE);
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwroff_GVIFRx
  Description   : 
  param[in/out] : 
  return        : TRUE ：プロセス完了
                  FALSE：プロセス未完了
  Note          : 
*****************************************************************************/
uint8 Mcu_Dev_Pwroff_GVIFRx( void ){
  Mcu_Dev_Pwron_SetPort(MCU_PORT_GVIF_CAN_RST, MCU_DIO_LOW);

  return((uint8)TRUE);
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwroff_GVIFTx_CDisp
  Description   : 
  param[in/out] : 
  return        : TRUE ：プロセス完了
                  FALSE：プロセス未完了
  Note          : 
*****************************************************************************/
uint8 Mcu_Dev_Pwroff_GVIFTx_CDisp( void ){
  Mcu_Dev_Pwron_SetPort(MCU_PORT_GVIF_CDISP_RST, MCU_DIO_LOW);

  return((uint8)TRUE);
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwroff_Mic
  Description   : 
  param[in/out] : 
  return        : TRUE ：プロセス完了
                  FALSE：プロセス未完了
  Note          : 
*****************************************************************************/
uint8 Mcu_Dev_Pwroff_Mic( void ){
  Mcu_Dev_Pwron_SetPort(MCU_PORT_MIC_ON, MCU_DIO_LOW);

  return((uint8)TRUE);
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwroff_Ant
  Description   : 
  param[in/out] : 
  return        : TRUE ：プロセス完了
                  FALSE：プロセス未完了
  Note          : 
*****************************************************************************/
uint8 Mcu_Dev_Pwroff_Ant( void ){
  Mcu_Dev_Pwron_SetPort(MCU_PORT_AMFM_ANT_ON, MCU_DIO_LOW);
  Mcu_Dev_Pwron_SetPort(MCU_PORT_GPS_ANT_ON, MCU_DIO_LOW);
  Mcu_Dev_Pwron_SetPort(MCU_PORT_DAB_ANT_ON, MCU_DIO_LOW);

  return((uint8)TRUE);
}


/**** End of File ***********************************************************/