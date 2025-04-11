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
#include "x_spi_ivi_sub1_power.h"

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

#define MCU_WRINUM_GVIF3TX_INISET       (11U)   /* 100-4-2.初期設定フロー レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_eDPSET_1     (2U)    /* 100-4-3.eDP設定フロー START～eDPポート設定 レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_eDPSET_2     (115U)  /* 100-4-3.eDP設定フロー eDP用レジスタ設定 10-5-3 レシーバ レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_eDPSET_3     (26U)   /* 100-4-3.eDP設定フロー eDP用レジスタ設定 10-5-3 DPCD レジスタ書込み回数 */
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
        {        1,         4,         0},
        {        5,         4,         0},
        {        9,         3,         0},
        {       12,         1,         0},
        {       13,         1,         0},
        {       14,         1,         0},
        {       15,         4,         0},
        {       19,         1,         0},
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
        {        0,         2,         0},
        {        2,         2,         0},
        {        4,         2,         0},
        {        6,         2,         0},
        {        8,         2,         0},
        {       10,         2,         0},
        {       12,         2,         0},
        {       14,         2,         0},
        {       16,         2,         0},
        {       18,         2,         0},
        {       20,         2,         0},
        {       22,         2,         0},
        {       24,         2,         0},
        {       26,         2,         0},
        {       28,         2,         0},
        {       30,         2,         0},
        {       32,         2,         0},
        {       34,         2,         0},
        {       36,         2,         0},
        {       38,         2,         0},
        {       40,         2,         0},
        {       42,         2,         0},
        {       44,         2,         0},
        {       46,         2,         0},
        {       48,         2,         0},
        {       50,         2,         0},
        {       52,         2,         0},
        {       54,         2,         0},
        {       56,         2,         0},
        {       58,         2,         0},
        {       60,         2,         0},
        {       62,         2,         0},
        {       64,         2,         0},
        {       66,         2,         0},
        {       68,         2,         0},
        {       70,         2,         0},
        {       72,         2,         0},
        {       74,         2,         0},
        {       76,         2,         0},
        {       78,         2,         0},
        {       80,         2,         0},
        {       82,         2,         0},
        {       84,         2,         0},
        {       86,         2,         0},
        {       88,         2,         0},
        {       90,         2,         0},
        {       92,         2,         0},
        {       94,         2,         0},
        {       96,         2,         0},
        {       98,         2,         0},
        {      100,         2,         0},
        {      102,         2,         0},
        {      104,         2,         0},
        {      106,         2,         0},
        {      108,         2,         0},
        {      110,         2,         0},
        {      112,         2,         0},
        {      114,         2,         0},
        {      116,         2,         0},
        {      118,         2,         0},
        {      120,         2,         0},
        {      122,         2,         0},
        {      124,         2,         0},
        {      126,         2,         0},
        {      128,         2,         0},
        {      130,         2,         0},
        {      132,         2,         0},
        {      134,         2,         0},
        {      136,         2,         0},
        {      138,         2,         0},
        {      140,         2,         0},
        {      142,         2,         0},
        {      144,         2,         0},
        {      146,         2,         0},
        {      148,         2,         0},
        {      150,         2,         0},
        {      152,         2,         0},
        {      154,         2,         0},
        {      156,         2,         0},
        {      158,         2,         0},
        {      160,         2,         0},
        {      162,         2,         0},
        {      164,         2,         0},
        {      166,         2,         0},
        {      168,         2,         0},
        {      170,         2,         0},
        {      172,         2,         0},
        {      174,         2,         0},
        {      176,         2,         0},
        {      178,         2,         0},
        {      180,         2,         0},
        {      182,         2,         0},
        {      184,         2,         0},
        {      186,         2,         0},
        {      188,         2,         0},
        {      190,         2,         0},
        {      192,         2,         0},
        {      194,         2,         0},
        {      196,         2,         0},
        {      198,         2,         0},
        {      200,         2,         0},
        {      202,         2,         0},
        {      204,         2,         0},
        {      206,         2,         0},
        {      208,         2,         0},
        {      210,         2,         0},
        {      212,         2,         0},
        {      214,         2,         0},
        {      216,         2,         0},
        {      218,         2,         0},
        {      220,         2,         0},
        {      222,         2,         0},
        {      224,         2,         0},
        {      226,         2,         0},
        {      228,         2,         0}
    };
    /* 100-4-3.eDP設定フロー eDP用レジスタ設定 10-5-3 DPCD */
    static const ST_REG_WRI_REQ GVIFTX_eDFSET_3[MCU_WRINUM_GVIF3TX_eDPSET_3] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         2,         0},
        {        2,         2,         0},
        {        4,         2,         0},
        {        6,         2,         0},
        {        8,         2,         0},
        {       10,         2,         0},
        {       12,         2,         0},
        {       14,         2,         0},
        {       16,         2,         0},
        {       18,         2,         0},
        {       20,         2,         0},
        {       22,         2,         0},
        {       24,         2,         0},
        {       26,         2,         0},
        {       28,         2,         0},
        {       30,         2,         0},
        {       32,         2,         0},
        {       34,         2,         0},
        {       36,         2,         0},
        {       38,         2,         0},
        {       40,         2,         0},
        {       42,         2,         0},
        {       44,         2,         0},
        {       46,         2,         0},
        {       48,         2,         0},
        {       50,         2,         0}
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
        {        5,         1,         0}
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
                /* 初期化完了通知 */
                vd_g_XspiIviSub1PowerDevInitCmpApp((U1)XSPI_IVI_POWER_GVIFSEND_INI);
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

    /* 初期化完了通知 */
    vd_g_XspiIviSub1PowerDevInitCmpApp((U1)XSPI_IVI_POWER_GVIFSEND_INI);

    return(mcu_return);
}
