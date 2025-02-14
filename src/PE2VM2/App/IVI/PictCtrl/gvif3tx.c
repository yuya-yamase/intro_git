/* メインタスクコードに移管するまでの仮置き */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gvif3tx.h"
#include "gpt_drv_frt.h"
#include "Dio.h"
#include "Dio_Symbols.h"
#include "Mcu_I2c_Ctrl_private.h"
#include "Mcu_Sys_Pwr_GvifSndr.h"

#include "pictic.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Port */
#define MCU_PORT_GVIF_CDISP_RST         (DIO_ID_PORT17_CH4)     /* /GVIF-TX(C-DISP)-RST */
/* FRT */
#define MCU_FRT_1MS                     (1000 * GPT_FRT_1US)

/* カウンタ最大値 */
#define MCU_SYS_COUNTTIME_FIN           (0xFFFFFFFFU)

/* GVIF3送信制御仕様 */
#define MCU_STEP_GVIF3TX_eDPSET_1       (1U)    /* 100-4-3.eDP設定フロー START~eDPポート設定 */
#define MCU_STEP_GVIF3TX_eDPSET_2       (2U)    /* 100-4-3.eDP設定フロー eDP用レジスタ設定 10-5-3 レシーバ */
#define MCU_STEP_GVIF3TX_eDPSET_3       (3U)    /* 100-4-3.eDP設定フロー eDP用レジスタ設定 10-5-3 DPCD */
#define MCU_STEP_GVIF3TX_eDPSET_4       (4U)    /* 100-4-3.eDP設定フロー EDID選択設定 */
#define MCU_STEP_GVIF3TX_eDPSET_5       (5U)    /* 100-4-3.eDP設定フロー Bank切り替え（Bank0）~Bank切り替え（Bank4） */
#define MCU_STEP_GVIF3TX_eDPSET_6       (6U)    /* 100-4-3.eDP設定フロー eDP用レジスタ設定 10-5-5 Hot Plug Detect */
#define MCU_STEP_GVIF3TX_eDPSET_FIN     (7U)

#define MCU_WRINUM_GVIF3TX_INISET       (9U)    /* 100-4-2.初期設定フロー レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_eDPSET_1     (2U)    /* 100-4-3.eDP設定フロー START～eDPポート設定 レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_eDPSET_2     (345U)  /* 100-4-3.eDP設定フロー eDP用レジスタ設定 10-5-3 レシーバ レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_eDPSET_3     (78U)   /* 100-4-3.eDP設定フロー eDP用レジスタ設定 10-5-3 DPCD レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_eDPSET_4     (1U)    /* 100-4-3.eDP設定フロー EDID選択設定 レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_eDPSET_5     (3U)    /* 100-4-3.eDP設定フロー Bank切り替え（Bank0）~Bank切り替え（Bank4） レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_eDPSET_6     (3U)    /* 100-4-3.eDP設定フロー eDP用レジスタ設定 10-5-5 Hot Plug Detect レジスタ書込み回数 */

#define MCU_STEP_GVIF3TX_OUTSET_1       (1U)    /* 100-4-4.出力設定フロー Bank切り替え（Bank0） */
#define MCU_STEP_GVIF3TX_OUTSET_2       (2U)    /* 100-4-4.出力設定フロー A点～GVIF3出力ON設定 */
#define MCU_STEP_GVIF3TX_OUTSET_3       (3U)    /* 100-4-4.出力設定フロー Wati t4 */
#define MCU_STEP_GVIF3TX_OUTSET_4       (4U)    /* 100-4-4.出力設定フロー GVIF3リンク確立確認 レジスタRead */
#define MCU_STEP_GVIF3TX_OUTSET_5       (5U)    /* 100-4-4.出力設定フロー リンク確立判定 */
#define MCU_STEP_GVIF3TX_OUTSET_6       (6U)    /* 100-4-4.出力設定フロー Bank切り替え（Bank7）～エラークリア解除設定 */
#define MCU_STEP_GVIF3TX_OUTSET_STP     (7U)
#define MCU_STEP_GVIF3TX_OUTSET_FIN     (8U)

#define MCU_WRINUM_GVIF3TX_OUTSET_1     (1U)    /* 100-4-4.出力設定フロー A点～Wati t4 レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_OUTSET_2     (4U)    /* 100-4-4.出力設定フロー Bank切り替え（Bank7）～エラークリア解除設定 レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_OUTSET_3     (1U)    /* 100-4-4.出力設定フロー Bank切り替え（Bank0） レジスタ書込み回数 */

#define MCU_GVIF_LNK_TIMEOUT            (5000U * MCU_FRT_1MS)  /* 起動からGVIFリンク確立までの時間要件 5000ms */

#define MCU_DIO_LOW                     (0U)
#define MCU_DIO_HIGH                    (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* フリーランタイマ */
uint32          Mcu_frt_stamp_gvif3tx[GPT_FRT_USELPSD_NUM_PARAM];

/* デバイス起動用カウンタ */
static uint32   Mcu_Polling_GvifTxRst;

/* GVIF送信制御仕様 */
       uint8    Mcu_OnStep_GVIF3TX_OVRALL;      /* 100-4-1.(C-Disp) 全体フロー 仮置き中はexternするためstaticなし */
static uint8    Mcu_OnStep_GVIF3TX_eDPSET;      /* 100-4-3.eDP設定フロー */
static uint8    Mcu_OnStep_GVIF3TX_OUTSET;      /* 100-4-4.出力設定フロー */
//static uint8    Mcu_OnStep_GVIF3TX_HDCP;        /* 100-4-5.HDCP認証フロー */
static uint32   Mcu_OnStep_GVIF3TX_AckTime;     /* GVIF3TX 書込み/読込みから応答までの時間計測 */
static uint32   Mcu_Gvif_LinkTimer;             /* GVIF3TX Wati処理用タイマ */

static uint16   Mcu_RegStep_GVIF3TX;            /* GVIF3TX レジスタ書込み位置指定 */

/* レジスタアクセス */
static uint16   Mcu_RegSet_BetWaitTime_Stub;    /* レジスタアクセス間Waitタイマ スタブ */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     Mcu_Dev_Pwron_GvifTx_Polling_Rst( void );
static uint8    Mcu_Dev_Pwron_TimChk( uint32 mcu_tim_cnt, const uint32 mcu_tim_fim);
static void     Mcu_Dev_Pwron_GvifTx_OverAll_Flow( void );

static uint8    Mcu_Dev_Pwron_GvifTx_IniSet( void );
static uint8    Mcu_Dev_Pwron_GvifTx_eDPSet( void );
static uint8    Mcu_Dev_Pwron_GvifTx_OutSet( void );
static uint8    Mcu_Dev_Pwron_GvifTx_HDCP( void );

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*****************************************************************************
  Function      : gvif3tx_Init
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void    gvif3tx_Init( void )
{
    /* フリーランタイマ用配列初期化 */
    for(uint32 cnt = 0; cnt < (uint32)GPT_FRT_USELPSD_NUM_PARAM; cnt++){
        Mcu_frt_stamp_gvif3tx[cnt] = 0;
    }

    /* Init時のフリーランタイマ取得 */
    Mcu_frt_stamp_gvif3tx[GPT_FRT_USELPSD_BASE] = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA);

    Mcu_Polling_GvifTxRst       = (uint32)0U;

    Mcu_OnStep_GVIF3TX_OVRALL   = (uint8)MCU_STEP_GVIF3TX_OVERALL_1;
    Mcu_OnStep_GVIF3TX_eDPSET   = (uint8)MCU_STEP_GVIF3TX_eDPSET_1;
    Mcu_OnStep_GVIF3TX_OUTSET   = (uint8)MCU_STEP_GVIF3TX_OUTSET_1;
    //Mcu_OnStep_GVIF3TX_HDCP     = (uint8)
    Mcu_Gvif_LinkTimer          = (uint32)0U;
    Mcu_OnStep_GVIF3TX_AckTime  = (uint32)0U;
    Mcu_RegStep_GVIF3TX         = (uint16)0U;

    Mcu_RegSet_BetWaitTime_Stub = (uint16)0xFFFFU;

    Mcu_Sys_Pwr_GvifSndr_Init();
}

/*****************************************************************************
  Function      : gvif3tx_main
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void    gvif3tx_main( void )
{
    /* [(C-Disp)制御フロー]シートの「定期監視フロー」前まで */
    static const uint32  MCU_PWRON_TIME_GVIFTX  =   (uint16)(55U / MCU_GVIFTX_TASK_TIME);    /* min:55ms 11タスク経過後を設定 */

    uint8   mcu_time_chk;

    /* Wait t3 監視処理 */
    Mcu_Dev_Pwron_GvifTx_Polling_Rst();

    mcu_time_chk    =   Mcu_Dev_Pwron_TimChk(Mcu_Polling_GvifTxRst, MCU_PWRON_TIME_GVIFTX);

    if(mcu_time_chk ==  (uint8)TRUE){
        Mcu_Dev_Pwron_GvifTx_OverAll_Flow();
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifTx_Polling_Rst
  Description   : 
  param[in/out] : 
  return        : -
  Note          : /GVIF-TX(C-DISP)-RST=Hi 監視
*****************************************************************************/
static void    Mcu_Dev_Pwron_GvifTx_Polling_Rst( void )
{
    uint8   mcu_dio_ret;

    mcu_dio_ret =   Dio_ReadChannel(MCU_PORT_GVIF_CDISP_RST);

    if(mcu_dio_ret  ==  (uint8)STD_LOW){
        Mcu_Polling_GvifTxRst       = (uint32)0U;
        Mcu_OnStep_GVIF3TX_OVRALL   = (uint8)MCU_STEP_GVIF3TX_OVERALL_1;
        Mcu_OnStep_GVIF3TX_eDPSET   = (uint8)MCU_STEP_GVIF3TX_eDPSET_1;
        Mcu_OnStep_GVIF3TX_OUTSET   = (uint8)MCU_STEP_GVIF3TX_OUTSET_1;
        //Mcu_OnStep_GVIF3TX_HDCP     = (uint8)
        Mcu_OnStep_GVIF3TX_AckTime  = (uint32)0U;
        Mcu_RegStep_GVIF3TX         = (uint16)0U;
    }
    else if((mcu_dio_ret  ==  (uint8)STD_HIGH) &&
        (Mcu_Polling_GvifTxRst < (uint32)MCU_SYS_COUNTTIME_FIN)){
        Mcu_Polling_GvifTxRst++;
    }
    else{
        /* do nothing */
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_TimChk
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 
*****************************************************************************/
static uint8   Mcu_Dev_Pwron_TimChk( uint32 mcu_tim_cnt, const uint32 mcu_tim_fim)
{
    uint8   mcu_ret;
    mcu_ret =   (uint8)FALSE;

    if(mcu_tim_cnt  >  mcu_tim_fim){
        mcu_ret =   (uint8)TRUE;
    }

    return(mcu_ret);
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifTx_OverAll_Flow
  Description   : 
  param[in/out] : 
  return        : -
  Note          : GVIF送信機 100-4-1.(C-Disp) 全体フロー
*****************************************************************************/
static void    Mcu_Dev_Pwron_GvifTx_OverAll_Flow( void )
{
    uint8   mcu_rslt;

    /* Ackタイムアウト用カウンタインクリメント */
    if(Mcu_OnStep_GVIF3TX_AckTime < (uint32)MCU_SYS_COUNTTIME_FIN){
        Mcu_OnStep_GVIF3TX_AckTime++;
    }

    switch (Mcu_OnStep_GVIF3TX_OVRALL)
    {
    case MCU_STEP_GVIF3TX_OVERALL_1:
        /* 100-4-2.初期設定フロー */
        mcu_rslt = Mcu_Dev_Pwron_GvifTx_IniSet();

        if(mcu_rslt == (uint8)TRUE){
            Mcu_OnStep_GVIF3TX_OVRALL = MCU_STEP_GVIF3TX_OVERALL_2;
        }
        break;

    case MCU_STEP_GVIF3TX_OVERALL_2:
        /* 100-4-3.eDP設定フロー */
        mcu_rslt = Mcu_Dev_Pwron_GvifTx_eDPSet();

        if(mcu_rslt == (uint8)TRUE){
            Mcu_OnStep_GVIF3TX_OVRALL = MCU_STEP_GVIF3TX_OVERALL_3;
        }
        break;

    case MCU_STEP_GVIF3TX_OVERALL_3:
        /* 映像IC制御仕様の"別体センターディスプレイへの映像出力ON"完了まで待機 */
        if(Mcu_OnStep_EIZOIC_OVRALL == MCU_STEP_EIZOIC_OVERALL_FIN){
            /* 100-4-4.出力設定フロー */
            mcu_rslt = Mcu_Dev_Pwron_GvifTx_OutSet();

            if(mcu_rslt == (uint8)TRUE){
                Mcu_OnStep_GVIF3TX_OVRALL = MCU_STEP_GVIF3TX_OVERALL_4;
            }
        }
        break;

    case MCU_STEP_GVIF3TX_OVERALL_4:
        /* 100-4-5.HDCP認証フロー */
        mcu_rslt = Mcu_Dev_Pwron_GvifTx_HDCP();

        if(mcu_rslt == (uint8)TRUE){
            Mcu_OnStep_GVIF3TX_OVRALL = MCU_STEP_GVIF3TX_OVERALL_FIN;
        }
        break;
    
    case MCU_STEP_GVIF3TX_OVERALL_FIN:
        /* 100-4-7.定期監視フロー */
        /* do nothing */
        break;

    default:
        break;
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifTx_IniSet
  Description   : 
  param[in/out] : 
  return        : -
  Note          : GVIF送信機 100-4-2.初期設定フロー
*****************************************************************************/
static uint8   Mcu_Dev_Pwron_GvifTx_IniSet( void )
{
    static const ST_REG_WRI_REQ GVIFTX_INISET[MCU_WRINUM_GVIF3TX_INISET] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},
        {        1,         5,         0},
        {        6,         6,         0},
        {       12,         1,         0},
        {       13,         1,         0},
        {       14,         1,         0},
        {       15,         5,         0},
        {       20,         1,         0},
        {       21,         1,         0}
    };
    uint8   mcu_return;     /* 戻り値：フロー完了通知 */

    mcu_return      = (uint8)FALSE;

    /* レジスタ書込み処理 */
    mcu_return = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (uint16)MCU_WRINUM_GVIF3TX_INISET, 
                                            (uint8)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_INISET, &Mcu_OnStep_GVIF3TX_AckTime,
                                            st_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT, &Mcu_RegSet_BetWaitTime_Stub);

    return(mcu_return);
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifTx_eDPSet
  Description   : 
  param[in/out] : 
  return        : -
  Note          : GVIF送信機 100-4-3.eDP設定フロー
*****************************************************************************/
static uint8   Mcu_Dev_Pwron_GvifTx_eDPSet( void )
{
    /* 100-4-3.eDP設定フロー START~eDPポート設定 */
    static const ST_REG_WRI_REQ GVIFTX_eDFSET_1[MCU_WRINUM_GVIF3TX_eDPSET_1] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},
        {        1,         2,         0}
    };
    /* 100-4-3.eDP設定フロー eDP用レジスタ設定 10-5-3 レシーバ */
    static const ST_REG_WRI_REQ GVIFTX_eDFSET_2[MCU_WRINUM_GVIF3TX_eDPSET_2] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         4,         0},
        {        4,         1,         0},
        {        5,         1,         0},
        {        6,         4,         0},
        {       10,         1,         0},
        {       11,         1,         0},
        {       12,         4,         0},
        {       16,         1,         0},
        {       17,         1,         0},
        {       18,         4,         0},
        {       22,         1,         0},
        {       23,         1,         0},
        {       24,         4,         0},
        {       28,         1,         0},
        {       29,         1,         0},
        {       30,         4,         0},
        {       34,         1,         0},
        {       35,         1,         0},
        {       36,         4,         0},
        {       40,         1,         0},
        {       41,         1,         0},
        {       42,         4,         0},
        {       46,         1,         0},
        {       47,         1,         0},
        {       48,         4,         0},
        {       52,         1,         0},
        {       53,         1,         0},
        {       54,         4,         0},
        {       58,         1,         0},
        {       59,         1,         0},
        {       60,         4,         0},
        {       64,         1,         0},
        {       65,         1,         0},
        {       66,         4,         0},
        {       70,         1,         0},
        {       71,         1,         0},
        {       72,         4,         0},
        {       76,         1,         0},
        {       77,         1,         0},
        {       78,         4,         0},
        {       82,         1,         0},
        {       83,         1,         0},
        {       84,         4,         0},
        {       88,         1,         0},
        {       89,         1,         0},
        {       90,         4,         0},
        {       94,         1,         0},
        {       95,         1,         0},
        {       96,         4,         0},
        {      100,         1,         0},
        {      101,         1,         0},
        {      102,         4,         0},
        {      106,         1,         0},
        {      107,         1,         0},
        {      108,         4,         0},
        {      112,         1,         0},
        {      113,         1,         0},
        {      114,         4,         0},
        {      118,         1,         0},
        {      119,         1,         0},
        {      120,         4,         0},
        {      124,         1,         0},
        {      125,         1,         0},
        {      126,         4,         0},
        {      130,         1,         0},
        {      131,         1,         0},
        {      132,         4,         0},
        {      136,         1,         0},
        {      137,         1,         0},
        {      138,         4,         0},
        {      142,         1,         0},
        {      143,         1,         0},
        {      144,         4,         0},
        {      148,         1,         0},
        {      149,         1,         0},
        {      150,         4,         0},
        {      154,         1,         0},
        {      155,         1,         0},
        {      156,         4,         0},
        {      160,         1,         0},
        {      161,         1,         0},
        {      162,         4,         0},
        {      166,         1,         0},
        {      167,         1,         0},
        {      168,         4,         0},
        {      172,         1,         0},
        {      173,         1,         0},
        {      174,         4,         0},
        {      178,         1,         0},
        {      179,         1,         0},
        {      180,         4,         0},
        {      184,         1,         0},
        {      185,         1,         0},
        {      186,         4,         0},
        {      190,         1,         0},
        {      191,         1,         0},
        {      192,         4,         0},
        {      196,         1,         0},
        {      197,         1,         0},
        {      198,         4,         0},
        {      202,         1,         0},
        {      203,         1,         0},
        {      204,         4,         0},
        {      208,         1,         0},
        {      209,         1,         0},
        {      210,         4,         0},
        {      214,         1,         0},
        {      215,         1,         0},
        {      216,         4,         0},
        {      220,         1,         0},
        {      221,         1,         0},
        {      222,         4,         0},
        {      226,         1,         0},
        {      227,         1,         0},
        {      228,         4,         0},
        {      232,         1,         0},
        {      233,         1,         0},
        {      234,         4,         0},
        {      238,         1,         0},
        {      239,         1,         0},
        {      240,         4,         0},
        {      244,         1,         0},
        {      245,         1,         0},
        {      246,         4,         0},
        {      250,         1,         0},
        {      251,         1,         0},
        {      252,         4,         0},
        {      256,         1,         0},
        {      257,         1,         0},
        {      258,         4,         0},
        {      262,         1,         0},
        {      263,         1,         0},
        {      264,         4,         0},
        {      268,         1,         0},
        {      269,         1,         0},
        {      270,         4,         0},
        {      274,         1,         0},
        {      275,         1,         0},
        {      276,         4,         0},
        {      280,         1,         0},
        {      281,         1,         0},
        {      282,         4,         0},
        {      286,         1,         0},
        {      287,         1,         0},
        {      288,         4,         0},
        {      292,         1,         0},
        {      293,         1,         0},
        {      294,         4,         0},
        {      298,         1,         0},
        {      299,         1,         0},
        {      300,         4,         0},
        {      304,         1,         0},
        {      305,         1,         0},
        {      306,         4,         0},
        {      310,         1,         0},
        {      311,         1,         0},
        {      312,         4,         0},
        {      316,         1,         0},
        {      317,         1,         0},
        {      318,         4,         0},
        {      322,         1,         0},
        {      323,         1,         0},
        {      324,         4,         0},
        {      328,         1,         0},
        {      329,         1,         0},
        {      330,         4,         0},
        {      334,         1,         0},
        {      335,         1,         0},
        {      336,         4,         0},
        {      340,         1,         0},
        {      341,         1,         0},
        {      342,         4,         0},
        {      346,         1,         0},
        {      347,         1,         0},
        {      348,         4,         0},
        {      352,         1,         0},
        {      353,         1,         0},
        {      354,         4,         0},
        {      358,         1,         0},
        {      359,         1,         0},
        {      360,         4,         0},
        {      364,         1,         0},
        {      365,         1,         0},
        {      366,         4,         0},
        {      370,         1,         0},
        {      371,         1,         0},
        {      372,         4,         0},
        {      376,         1,         0},
        {      377,         1,         0},
        {      378,         4,         0},
        {      382,         1,         0},
        {      383,         1,         0},
        {      384,         4,         0},
        {      388,         1,         0},
        {      389,         1,         0},
        {      390,         4,         0},
        {      394,         1,         0},
        {      395,         1,         0},
        {      396,         4,         0},
        {      400,         1,         0},
        {      401,         1,         0},
        {      402,         4,         0},
        {      406,         1,         0},
        {      407,         1,         0},
        {      408,         4,         0},
        {      412,         1,         0},
        {      413,         1,         0},
        {      414,         4,         0},
        {      418,         1,         0},
        {      419,         1,         0},
        {      420,         4,         0},
        {      424,         1,         0},
        {      425,         1,         0},
        {      426,         4,         0},
        {      430,         1,         0},
        {      431,         1,         0},
        {      432,         4,         0},
        {      436,         1,         0},
        {      437,         1,         0},
        {      438,         4,         0},
        {      442,         1,         0},
        {      443,         1,         0},
        {      444,         4,         0},
        {      448,         1,         0},
        {      449,         1,         0},
        {      450,         4,         0},
        {      454,         1,         0},
        {      455,         1,         0},
        {      456,         4,         0},
        {      460,         1,         0},
        {      461,         1,         0},
        {      462,         4,         0},
        {      466,         1,         0},
        {      467,         1,         0},
        {      468,         4,         0},
        {      472,         1,         0},
        {      473,         1,         0},
        {      474,         4,         0},
        {      478,         1,         0},
        {      479,         1,         0},
        {      480,         4,         0},
        {      484,         1,         0},
        {      485,         1,         0},
        {      486,         4,         0},
        {      490,         1,         0},
        {      491,         1,         0},
        {      492,         4,         0},
        {      496,         1,         0},
        {      497,         1,         0},
        {      498,         4,         0},
        {      502,         1,         0},
        {      503,         1,         0},
        {      504,         4,         0},
        {      508,         1,         0},
        {      509,         1,         0},
        {      510,         4,         0},
        {      514,         1,         0},
        {      515,         1,         0},
        {      516,         4,         0},
        {      520,         1,         0},
        {      521,         1,         0},
        {      522,         4,         0},
        {      526,         1,         0},
        {      527,         1,         0},
        {      528,         4,         0},
        {      532,         1,         0},
        {      533,         1,         0},
        {      534,         4,         0},
        {      538,         1,         0},
        {      539,         1,         0},
        {      540,         4,         0},
        {      544,         1,         0},
        {      545,         1,         0},
        {      546,         4,         0},
        {      550,         1,         0},
        {      551,         1,         0},
        {      552,         4,         0},
        {      556,         1,         0},
        {      557,         1,         0},
        {      558,         4,         0},
        {      562,         1,         0},
        {      563,         1,         0},
        {      564,         4,         0},
        {      568,         1,         0},
        {      569,         1,         0},
        {      570,         4,         0},
        {      574,         1,         0},
        {      575,         1,         0},
        {      576,         4,         0},
        {      580,         1,         0},
        {      581,         1,         0},
        {      582,         4,         0},
        {      586,         1,         0},
        {      587,         1,         0},
        {      588,         4,         0},
        {      592,         1,         0},
        {      593,         1,         0},
        {      594,         4,         0},
        {      598,         1,         0},
        {      599,         1,         0},
        {      600,         4,         0},
        {      604,         1,         0},
        {      605,         1,         0},
        {      606,         4,         0},
        {      610,         1,         0},
        {      611,         1,         0},
        {      612,         4,         0},
        {      616,         1,         0},
        {      617,         1,         0},
        {      618,         4,         0},
        {      622,         1,         0},
        {      623,         1,         0},
        {      624,         4,         0},
        {      628,         1,         0},
        {      629,         1,         0},
        {      630,         4,         0},
        {      634,         1,         0},
        {      635,         1,         0},
        {      636,         4,         0},
        {      640,         1,         0},
        {      641,         1,         0},
        {      642,         4,         0},
        {      646,         1,         0},
        {      647,         1,         0},
        {      648,         4,         0},
        {      652,         1,         0},
        {      653,         1,         0},
        {      654,         4,         0},
        {      658,         1,         0},
        {      659,         1,         0},
        {      660,         4,         0},
        {      664,         1,         0},
        {      665,         1,         0},
        {      666,         4,         0},
        {      670,         1,         0},
        {      671,         1,         0},
        {      672,         4,         0},
        {      676,         1,         0},
        {      677,         1,         0},
        {      678,         4,         0},
        {      682,         1,         0},
        {      683,         1,         0},
        {      684,         4,         0},
        {      688,         1,         0},
        {      689,         1,         0}
    };
    /* 100-4-3.eDP設定フロー eDP用レジスタ設定 10-5-3 DPCD */
    static const ST_REG_WRI_REQ GVIFTX_eDFSET_3[MCU_WRINUM_GVIF3TX_eDPSET_3] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         4,         0},
        {        4,         1,         0},
        {        5,         1,         0},
        {        6,         4,         0},
        {       10,         1,         0},
        {       11,         1,         0},
        {       12,         4,         0},
        {       16,         1,         0},
        {       17,         1,         0},
        {       18,         4,         0},
        {       22,         1,         0},
        {       23,         1,         0},
        {       24,         4,         0},
        {       28,         1,         0},
        {       29,         1,         0},
        {       30,         4,         0},
        {       34,         1,         0},
        {       35,         1,         0},
        {       36,         4,         0},
        {       40,         1,         0},
        {       41,         1,         0},
        {       42,         4,         0},
        {       46,         1,         0},
        {       47,         1,         0},
        {       48,         4,         0},
        {       52,         1,         0},
        {       53,         1,         0},
        {       54,         4,         0},
        {       58,         1,         0},
        {       59,         1,         0},
        {       60,         4,         0},
        {       64,         1,         0},
        {       65,         1,         0},
        {       66,         4,         0},
        {       70,         1,         0},
        {       71,         1,         0},
        {       72,         4,         0},
        {       76,         1,         0},
        {       77,         1,         0},
        {       78,         4,         0},
        {       82,         1,         0},
        {       83,         1,         0},
        {       84,         4,         0},
        {       88,         1,         0},
        {       89,         1,         0},
        {       90,         4,         0},
        {       94,         1,         0},
        {       95,         1,         0},
        {       96,         4,         0},
        {      100,         1,         0},
        {      101,         1,         0},
        {      102,         4,         0},
        {      106,         1,         0},
        {      107,         1,         0},
        {      108,         4,         0},
        {      112,         1,         0},
        {      113,         1,         0},
        {      114,         4,         0},
        {      118,         1,         0},
        {      119,         1,         0},
        {      120,         4,         0},
        {      124,         1,         0},
        {      125,         1,         0},
        {      126,         4,         0},
        {      130,         1,         0},
        {      131,         1,         0},
        {      132,         4,         0},
        {      136,         1,         0},
        {      137,         1,         0},
        {      138,         4,         0},
        {      142,         1,         0},
        {      143,         1,         0},
        {      144,         4,         0},
        {      148,         1,         0},
        {      149,         1,         0},
        {      150,         4,         0},
        {      154,         1,         0},
        {      155,         1,         0}
    };
    /* 100-4-3.eDP設定フロー EDID選択設定 */
    static const ST_REG_WRI_REQ GVIFTX_eDFSET_4[MCU_WRINUM_GVIF3TX_eDPSET_4] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0}
    };
    /* 100-4-3.eDP設定フロー Bank切り替え（Bank0）~Bank切り替え（Bank4） */
    static const ST_REG_WRI_REQ GVIFTX_eDFSET_5[MCU_WRINUM_GVIF3TX_eDPSET_5] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},
        {        1,         1,         0},
        {        2,         1,         0}
    };
    /* 100-4-3.eDP設定フロー eDP用レジスタ設定 10-5-5 Hot Plug Detect */
    static const ST_REG_WRI_REQ GVIFTX_eDFSET_6[MCU_WRINUM_GVIF3TX_eDPSET_6] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         4,         0},
        {        4,         1,         0},
        {        5,         1,         0},
    };

    uint8   mcu_sts;        /* 書込み状況 */
    uint8   mcu_return;     /* 戻り値：フロー完了通知 */

    mcu_sts         = (uint8)FALSE;
    mcu_return      = (uint8)FALSE;

    switch (Mcu_OnStep_GVIF3TX_eDPSET)
    {
    case MCU_STEP_GVIF3TX_eDPSET_1:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (uint16)MCU_WRINUM_GVIF3TX_eDPSET_1,
                                                (uint8)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_eDFSET_1, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET1, &Mcu_RegSet_BetWaitTime_Stub);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_eDPSET = (uint8)MCU_STEP_GVIF3TX_eDPSET_2;
        }
        break;

    case MCU_STEP_GVIF3TX_eDPSET_2:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (uint16)MCU_WRINUM_GVIF3TX_eDPSET_2,
                                                (uint8)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_eDFSET_2, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC, &Mcu_RegSet_BetWaitTime_Stub);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_eDPSET = (uint8)MCU_STEP_GVIF3TX_eDPSET_3;
        }
        break;

    case MCU_STEP_GVIF3TX_eDPSET_3:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (uint16)MCU_WRINUM_GVIF3TX_eDPSET_3,
                                                (uint8)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_eDFSET_3, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD, &Mcu_RegSet_BetWaitTime_Stub);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_eDPSET = (uint8)MCU_STEP_GVIF3TX_eDPSET_4;
        }
        break;

    case MCU_STEP_GVIF3TX_eDPSET_4:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (uint16)MCU_WRINUM_GVIF3TX_eDPSET_4,
                                                (uint8)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_eDFSET_4, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET2, &Mcu_RegSet_BetWaitTime_Stub);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_eDPSET = (uint8)MCU_STEP_GVIF3TX_eDPSET_5;
        }
        break;

    case MCU_STEP_GVIF3TX_eDPSET_5:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (uint16)MCU_WRINUM_GVIF3TX_eDPSET_5,
                                                (uint8)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_eDFSET_5, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET3, &Mcu_RegSet_BetWaitTime_Stub);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_eDPSET = (uint8)MCU_STEP_GVIF3TX_eDPSET_6;
        }
        break;
    
    case MCU_STEP_GVIF3TX_eDPSET_6:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (uint16)MCU_WRINUM_GVIF3TX_eDPSET_6,
                                                (uint8)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_eDFSET_6, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_HPD, &Mcu_RegSet_BetWaitTime_Stub);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_eDPSET = (uint8)MCU_STEP_GVIF3TX_eDPSET_FIN;
            mcu_return                = (uint8)TRUE;
        }
        break;

    case MCU_STEP_GVIF3TX_eDPSET_FIN:
        mcu_return  = (uint8)TRUE;
        break;

    default:
        /* 異常時：本処理を最初からやり直す */
        Mcu_OnStep_GVIF3TX_eDPSET = (uint8)MCU_STEP_GVIF3TX_eDPSET_1;
        break;
    }

    return(mcu_return);
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifTx_OutSet
  Description   : 
  param[in/out] : 
  return        : -
  Note          : GVIF送信機 100-4-4.出力設定フロー
*****************************************************************************/
static uint8   Mcu_Dev_Pwron_GvifTx_OutSet( void )
{
    /* GVIF3リンク確立確認ポーリング周期 t4 */
    static const uint32  MCU_PWRON_TIME_GVIFTX_POLING  = (50U / MCU_GVIFTX_TASK_TIME);    /* typ:50ms */
    /* リンク確立完了 確認用マスク */
    static const uint8   MCU_GVIF3TX0_ACTIVATED_MSK    = (0x01U);
    /* 100-4-4.出力設定フロー Bank切り替え（Bank0） */
    static const ST_REG_WRI_REQ GVIFTX_OUTSET_3[MCU_WRINUM_GVIF3TX_OUTSET_3] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0}
    };
    /* 100-4-4.出力設定フロー A点～Wati t4 */
    static const ST_REG_WRI_REQ GVIFTX_OUTSET_1[MCU_WRINUM_GVIF3TX_OUTSET_1] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0}
    };
    /* 100-4-4.出力設定フロー Bank切り替え（Bank7）～エラークリア解除設定 */
    static const ST_REG_WRI_REQ GVIFTX_OUTSET_2[MCU_WRINUM_GVIF3TX_OUTSET_2] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},
        {        1,         1,         0},
        {        2,         1,         0},
        {        3,         2,         0}
    };

    uint8   mcu_time_chk_poling;    /* wait t4監視 */
    uint8   mcu_sts;                /* 書込み状況 */
    uint8   mcu_return;             /* 戻り値：フロー完了通知 */
    uint32  mcu_frt_elpsd;
    uint8   mcu_reg_read;           /* レジスタ読出し値 */

    mcu_sts             = (uint8)FALSE;
    mcu_return          = (uint8)FALSE;
    mcu_time_chk_poling = (uint8)0U;
    mcu_frt_elpsd       = u4_g_Gpt_FrtGetUsElapsed(Mcu_frt_stamp_gvif3tx);
    mcu_reg_read        = (uint8)0U;

    switch (Mcu_OnStep_GVIF3TX_OUTSET)
    {
    case MCU_STEP_GVIF3TX_OUTSET_1:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (uint16)MCU_WRINUM_GVIF3TX_OUTSET_3,
                                                (uint8)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_OUTSET_3, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET3, &Mcu_RegSet_BetWaitTime_Stub);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_OUTSET = (uint8)MCU_STEP_GVIF3TX_OUTSET_2;
        }
        break;
    
    case MCU_STEP_GVIF3TX_OUTSET_2:
        /* レジスタ書込み処理 */
        /* ToDo：I2Cの説明次第で要変更 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (uint16)MCU_WRINUM_GVIF3TX_OUTSET_1,
                                                (uint8)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_OUTSET_1, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET1, &Mcu_RegSet_BetWaitTime_Stub);
        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了したら次状態に遷移 */
            Mcu_OnStep_GVIF3TX_OUTSET = (uint8)MCU_STEP_GVIF3TX_OUTSET_3;
        }
        break;

    case MCU_STEP_GVIF3TX_OUTSET_3:
        mcu_time_chk_poling = Mcu_Dev_Pwron_TimChk(Mcu_Gvif_LinkTimer, MCU_PWRON_TIME_GVIFTX_POLING);
        if(mcu_time_chk_poling == (uint8)TRUE){
            /* Wati t4完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_OUTSET = (uint8)MCU_STEP_GVIF3TX_OUTSET_4;
            Mcu_Gvif_LinkTimer        = (uint32)0U;
        }
        else{
            Mcu_Gvif_LinkTimer++;
        }
        break;

    case MCU_STEP_GVIF3TX_OUTSET_4:
        /* レジスタ読出し処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (uint8)GP_I2C_MA_SLA_3_GVIF_TX,
                                                &Mcu_OnStep_GVIF3TX_AckTime, st_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD, &Mcu_RegSet_BetWaitTime_Stub);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_OUTSET = (uint8)MCU_STEP_GVIF3TX_OUTSET_5;
        }
        break;

    case MCU_STEP_GVIF3TX_OUTSET_5:
        mcu_reg_read = st_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD[1].u1p_pdu[1];
        if((mcu_reg_read & (uint8)MCU_GVIF3TX0_ACTIVATED_MSK) != (uint8)0x01U){
            /* リンク確立未完了 */
            /* ToDo：ディスプレイ電源ONをXSPI？から取得する必要がある */
            if(mcu_frt_elpsd > (uint32)MCU_GVIF_LNK_TIMEOUT){
                /* GVIF3リンクエラー処理 */
                (void)Dio_WriteChannel(MCU_PORT_GVIF_CDISP_RST , MCU_DIO_LOW);/* デバイスリセット */
                /* ToDo：DTC記録 DISP(Center)通信途絶 コード：T.B.D */
                Mcu_OnStep_GVIF3TX_OUTSET = (uint8)MCU_STEP_GVIF3TX_OUTSET_STP;
            }
            else{
                /* A点へ戻る */
                Mcu_OnStep_GVIF3TX_OUTSET = (uint8)MCU_STEP_GVIF3TX_OUTSET_2;
            }
        }
        else{
            /* 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_OUTSET = (uint8)MCU_STEP_GVIF3TX_OUTSET_6;
        }
        break;

    case MCU_STEP_GVIF3TX_OUTSET_6:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (uint16)MCU_WRINUM_GVIF3TX_OUTSET_2,
                                                (uint8)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_OUTSET_2, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET2, &Mcu_RegSet_BetWaitTime_Stub);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_OUTSET   = (uint8)MCU_STEP_GVIF3TX_OUTSET_FIN;
            mcu_return                  = (uint8)TRUE;
        }
        break;

    case MCU_STEP_GVIF3TX_OUTSET_STP:
        /* 次回起動まで制御停止 */
        break;
    
    case MCU_STEP_GVIF3TX_OUTSET_FIN:
        mcu_return = (uint8)TRUE;
        break;

    default:
        /* 異常ステータスの場合は最初からやり直す */
        Mcu_OnStep_GVIF3TX_OUTSET = (uint8)MCU_STEP_GVIF3TX_OUTSET_1;
        break;
    }

    return(mcu_return);
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifTx_HDCP
  Description   : 
  param[in/out] : 
  return        : -
  Note          : GVIF送信機 100-4-5.HDCP認証フロー
*****************************************************************************/
static uint8   Mcu_Dev_Pwron_GvifTx_HDCP( void )
{
    uint8   mcu_return;

    /* ToDo：起動条件が達成できないため、設定Skipし常にTRUE(処理完了)を通知 */
    /* 起動条件：バックチャネルGPIO1確認 論理：High */
    mcu_return = (uint8)TRUE;


    return(mcu_return);
}
