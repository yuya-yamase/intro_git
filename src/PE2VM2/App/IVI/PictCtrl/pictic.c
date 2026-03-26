/* メインタスクコードに移管するまでの仮置き */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "pictic.h"
#include "Dio.h"
#include "Dio_Symbols.h"
#include "Mcu_I2c_Ctrl_private.h"
#include "Mcu_Sys_Pwr_EizoIc.h"

#include "gvif3tx.h"
#include "x_spi_ivi_sub1_power.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Port */
#define MCU_PORT_V_IC_RST               (DIO_ID_PORT3_CH3)      /* /V-IC-RST */

/* カウンタ最大値 */
#define MCU_SYS_COUNTTIME_FIN           (0xFFFFFFFFU)

/* 映像IC制御仕様 */
#define MCU_WRINUM_EIZOIC_INISET        (147U)  /* 6.2 初期化処理 レジスタ書込み回数 */
#define MCU_WRINUM_EIZOIC_SIPSET        (4U)    /* 6.3 SiP映像表示に関する処理 レジスタ書込み回数 */
#define MCU_WRINUM_EIZOIC_CAMSET        (45U)   /* 6.5.1.1 起動時のカメラ映像表示に関する設定 レジスタ書込み回数 */
#define MCU_WRINUM_EIZOIC_CNTDSPSET     (4U)    /* 6.4.1 別体センターディスプレイへの映像出力ON ( eDP出力ON ) レジスタ書込み回数 */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* デバイス起動用カウンタ */
static uint32   Mcu_Polling_VIcRst;

/* 映像IC制御仕様 */
       uint8    Mcu_OnStep_EIZOIC_OVRALL;       /* 6-1. 全体フロー 6.1.1 映像IC起動処理 仮置き中はexternするためstaticなし */
static uint32   Mcu_OnStep_EIZOIC_AckTime;      /* 映像IC 書込み/読込みから応答までの時間計測 */

static uint16   Mcu_RegStep_EIZOIC;             /* 映像IC レジスタ書込み位置指定 */

/* レジスタアクセス */
static uint16   Mcu_RegSet_BetWaitTime_Stub;    /* レジスタアクセス間Waitタイマ スタブ */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     Mcu_Dev_Pwron_EizoIc_Polling_VIcRst( void );
static void     Mcu_Dev_Pwron_EizoIc_RegSetting( void );
static uint8    Mcu_Dev_Pwron_TimChk( uint32 mcu_tim_cnt, const uint32 mcu_tim_fim);
static void     Mcu_Dev_Pwron_EizoIc_SetReg( void );

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*****************************************************************************
  Function      : pictic_Init
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void    pictic_Init( void )
{
    Mcu_Polling_VIcRst          = (uint32)0U;

    Mcu_OnStep_EIZOIC_OVRALL    = (uint8)MCU_STEP_EIZOIC_OVERALL_0;
    Mcu_OnStep_EIZOIC_AckTime   = (uint32)0U;
    Mcu_RegStep_EIZOIC          = (uint16)0U;

    Mcu_RegSet_BetWaitTime_Stub = (uint16)0xFFFFU;
}

/*****************************************************************************
  Function      : pictic_main
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void    pictic_main( void )
{
    /* [映像IC起動処理]シートの初期化処理 */
    /* 開始条件監視用ポーリング */
    Mcu_Dev_Pwron_EizoIc_Polling_VIcRst();

    /* 全体フロー処理 */
    Mcu_Dev_Pwron_EizoIc_RegSetting();
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_EizoIc_Polling_VIcRst
  Description   : 
  param[in/out] : 
  return        : -
  Note          : /V-IC-RST=Hi 監視
*****************************************************************************/
static void     Mcu_Dev_Pwron_EizoIc_Polling_VIcRst( void )
{
    uint8   mcu_dio_ret;

    mcu_dio_ret =   Dio_ReadChannel(MCU_PORT_V_IC_RST);

    if(mcu_dio_ret  ==  (uint8)STD_LOW){
        Mcu_Polling_VIcRst          = (uint32)0U;
        Mcu_OnStep_EIZOIC_OVRALL    = (uint8)MCU_STEP_EIZOIC_OVERALL_0;
        Mcu_OnStep_EIZOIC_AckTime   = (uint32)0U;
        Mcu_RegStep_EIZOIC          = (uint16)0U;
    }
    else if((mcu_dio_ret  ==  (uint8)STD_HIGH) &&
        (Mcu_Polling_VIcRst < (uint32)MCU_SYS_COUNTTIME_FIN)){
        Mcu_Polling_VIcRst++;
    }
    else{
        /* do nothing */
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_EizoIc_RegSetting
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 7.レジスタ設定
*****************************************************************************/
static void     Mcu_Dev_Pwron_EizoIc_RegSetting( void )
{
    static const uint32 MCU_PWRON_TIME_EIZOIC  =   (MCU_PICTIC_TASK_TIME / MCU_PICTIC_TASK_TIME);    /* min:1ms */

    uint8   mcu_time_chk;

    mcu_time_chk    =   Mcu_Dev_Pwron_TimChk(Mcu_Polling_VIcRst, MCU_PWRON_TIME_EIZOIC);

    if(mcu_time_chk ==  (uint8)TRUE){
        Mcu_Dev_Pwron_EizoIc_SetReg();
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_TimChk
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 
*****************************************************************************/
static uint8    Mcu_Dev_Pwron_TimChk( uint32 mcu_tim_cnt, const uint32 mcu_tim_fim)
{
    uint8   mcu_ret;
    mcu_ret =   (uint8)FALSE;

    if(mcu_tim_cnt  >  mcu_tim_fim){
        mcu_ret =   (uint8)TRUE;
    }

    return(mcu_ret);
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_EizoIc_SetReg
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 映像IC初期化処理 レジスタ設定
*****************************************************************************/
static void     Mcu_Dev_Pwron_EizoIc_SetReg( void )
{
    /* 6.2 初期化処理 */
    static const ST_REG_WRI_REQ EIZOIC_INISET[MCU_WRINUM_EIZOIC_INISET] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},
        {        1,         1,         0},
        {        2,         1,         0},
        {        3,         4,         0},
        {        7,         2,         0},
        {        9,         1,         0},
        {       10,         1,         0},
        {       11,         1,         0},
        {       12,         4,         0},
        {       16,         4,         0},
        {       20,         4,         0},
        {       24,         4,         0},
        {       28,         2,         0},
        {       30,         1,         0},
        {       31,         1,         0},
        {       32,         1,         0},
        {       33,         2,         0},
        {       35,         1,         0},
        {       36,         4,         0},
        {       40,         4,         0},
        {       44,         4,         0},
        {       48,         4,         0},
        {       52,         1,         0},
        {       53,         1,         0},
        {       54,         4,         0},
        {       58,         4,         0},
        {       62,         4,         0},
        {       66,         4,         0},
        {       70,         4,         0},
        {       74,         4,         0},
        {       78,         4,         0},
        {       82,         4,         0},
        {       86,         4,         0},
        {       90,         4,         0},
        {       94,         4,         0},
        {       98,         3,         0},
        {      101,         1,         0},
        {      102,         4,         0},
        {      106,         4,         0},
        {      110,         4,         0},
        {      114,         4,         0},
        {      118,         4,         0},
        {      122,         4,         0},
        {      126,         4,         0},
        {      130,         4,         0},
        {      134,         4,         0},
        {      138,         4,         0},
        {      142,         4,         0},
        {      146,         4,         0},
        {      150,         4,         0},
        {      154,         4,         0},
        {      158,         4,         0},
        {      162,         1,         0},
        {      163,         2,         0},
        {      165,         1,         0},
        {      166,         3,         0},
        {      169,         1,         0},
        {      170,         4,         0},
        {      174,         3,         0},
        {      177,         1,         0},
        {      178,         2,         0},
        {      180,         1,         0},
        {      181,         1,         0},
        {      182,         1,         0},
        {      183,         4,         0},
        {      187,         2,         0},
        {      189,         1,         0},
        {      190,         3,         0},
        {      193,         1,         0},
        {      194,         1,         0},
        {      195,         1,         0},
        {      196,         3,         0},
        {      199,         1,         0},
        {      200,         1,         0},
        {      201,         1,         0},
        {      202,         4,         0},
        {      206,         4,         0},
        {      210,         4,         0},
        {      214,         4,         0},
        {      218,         4,         0},
        {      222,         4,         0},
        {      226,         4,         0},
        {      230,         4,         0},
        {      234,         4,         0},
        {      238,         4,         0},
        {      242,         4,         0},
        {      246,         4,         0},
        {      250,         4,         0},
        {      254,         4,         0},
        {      258,         4,         0},
        {      262,         4,         0},
        {      266,         4,         0},
        {      270,         4,         0},
        {      274,         4,         0},
        {      278,         4,         0},
        {      282,         4,         0},
        {      286,         4,         0},
        {      290,         4,         0},
        {      294,         4,         0},
        {      298,         4,         0},
        {      302,         4,         0},
        {      306,         4,         0},
        {      310,         4,         0},
        {      314,         4,         0},
        {      318,         4,         0},
        {      322,         4,         0},
        {      326,         4,         0},
        {      330,         1,         0},
        {      331,         4,         0},
        {      335,         4,         0},
        {      339,         4,         0},
        {      343,         4,         0},
        {      347,         4,         0},
        {      351,         4,         0},
        {      355,         4,         0},
        {      359,         4,         0},
        {      363,         4,         0},
        {      367,         4,         0},
        {      371,         4,         0},
        {      375,         4,         0},
        {      379,         4,         0},
        {      383,         4,         0},
        {      387,         4,         0},
        {      391,         4,         0},
        {      395,         4,         0},
        {      399,         4,         0},
        {      403,         4,         0},
        {      407,         4,         0},
        {      411,         4,         0},
        {      415,         4,         0},
        {      419,         4,         0},
        {      423,         4,         0},
        {      427,         4,         0},
        {      431,         4,         0},
        {      435,         4,         0},
        {      439,         4,         0},
        {      443,         4,         0},
        {      447,         4,         0},
        {      451,         4,         0},
        {      455,         4,         0},
        {      459,         1,         0},
        {      460,         4,         0},
        {      464,         4,         0},
        {      468,         4,         0},
        {      472,         4,         0},
        {      476,         4,         0},
        {      480,         4,         0}
    };
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    static const ST_REG_WRI_REQ EIZOIC_SIPSET[MCU_WRINUM_EIZOIC_SIPSET] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},
        {        1,         1,         0},
        {        2,         1,         0},
        {        3,         1,         0}
    };
    /* 6.5.1.1 起動時のカメラ映像表示に関する設定 */
    /* どのカメラサイズでも書込み位置と個数は共通 */
    static const ST_REG_WRI_REQ EIZOIC_CAMSET[MCU_WRINUM_EIZOIC_CAMSET] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},
        {        1,         4,         0},
        {        5,         4,         0},
        {        9,         4,         0},
        {       13,         4,         0},
        {       17,         4,         0},
        {       21,         2,         0},
        {       23,         1,         0},
        {       24,         4,         0},
        {       28,         4,         0},
        {       32,         4,         0},
        {       36,         4,         0},
        {       40,         1,         0},
        {       41,         4,         0},
        {       45,         4,         0},
        {       49,         1,         0},
        {       50,         4,         0},
        {       54,         4,         0},
        {       58,         4,         0},
        {       62,         4,         0},
        {       66,         4,         0},
        {       70,         4,         0},
        {       74,         4,         0},
        {       78,         4,         0},
        {       82,         4,         0},
        {       86,         4,         0},
        {       90,         4,         0},
        {       94,         4,         0},
        {       98,         4,         0},
        {      102,         4,         0},
        {      106,         4,         0},
        {      110,         4,         0},
        {      114,         4,         0},
        {      118,         2,         0},
        {      120,         1,         0},
        {      121,         2,         0},
        {      123,         1,         0},
        {      124,         4,         0},
        {      128,         1,         0},
        {      129,         4,         0},
        {      133,         4,         0},
        {      137,         4,         0},
        {      141,         4,         0},
        {      145,         4,         0},
        {      149,         2,         0},
    };
    /* 6.4.1 別体センターディスプレイへの映像出力ON ( eDP出力ON ) */
    static const ST_REG_WRI_REQ EIZOIC_CNTDSPSET[MCU_WRINUM_EIZOIC_CNTDSPSET] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},
        {        1,         1,         0},
        {        2,         1,         0},
        {        3,         1,         0}
    };
    uint8   mcu_sts;        /* 書込み状況 */

    mcu_sts         = (uint8)FALSE;

    /* Ackタイムアウト用カウンタインクリメント */
    if(Mcu_OnStep_EIZOIC_AckTime < (uint32)MCU_SYS_COUNTTIME_FIN){
        Mcu_OnStep_EIZOIC_AckTime++;
    }

    switch (Mcu_OnStep_EIZOIC_OVRALL)
    {
    case MCU_STEP_EIZOIC_OVERALL_0:
        /* GVIF3送信仕様の"eDP設定"完了まで待機 */
        if(Mcu_OnStep_GVIF3TX_OVRALL == MCU_STEP_GVIF3TX_OVERALL_3){
            Mcu_OnStep_EIZOIC_OVRALL = (uint8)MCU_STEP_EIZOIC_OVERALL_1;
        }
        break;

    case MCU_STEP_EIZOIC_OVERALL_1:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_VIDEO_IC, &Mcu_RegStep_EIZOIC, (uint16)MCU_WRINUM_EIZOIC_INISET,
                                                (uint8)GP_I2C_MA_SLA_1_VIDEO_IC, EIZOIC_INISET, &Mcu_OnStep_EIZOIC_AckTime,
                                                st_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT, &Mcu_RegSet_BetWaitTime_Stub);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_EIZOIC_OVRALL = (uint8)MCU_STEP_EIZOIC_OVERALL_2;
        }
        break;
    
    case MCU_STEP_EIZOIC_OVERALL_2:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_VIDEO_IC, &Mcu_RegStep_EIZOIC, (uint16)MCU_WRINUM_EIZOIC_SIPSET,
                                                (uint8)GP_I2C_MA_SLA_1_VIDEO_IC, EIZOIC_SIPSET, &Mcu_OnStep_EIZOIC_AckTime,
                                                st_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_SIP, &Mcu_RegSet_BetWaitTime_Stub);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_EIZOIC_OVRALL = (uint8)MCU_STEP_EIZOIC_OVERALL_3;
        }
        break;

    case MCU_STEP_EIZOIC_OVERALL_3:
        /* レジスタ書込み処理 */
        /* ToDo：MCUにバックアップしている「カメラシステム種別」と「カメラ映像の切り出しサイズ 」に基づき設定値を切り替えする。現時点ではカメラなし決め打ち */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_VIDEO_IC, &Mcu_RegStep_EIZOIC, (uint16)MCU_WRINUM_EIZOIC_CAMSET,
                                                (uint8)GP_I2C_MA_SLA_1_VIDEO_IC, EIZOIC_CAMSET, &Mcu_OnStep_EIZOIC_AckTime,
                                                st_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON, &Mcu_RegSet_BetWaitTime_Stub);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_EIZOIC_OVRALL = (uint8)MCU_STEP_EIZOIC_OVERALL_4;
        }
        break;

    case MCU_STEP_EIZOIC_OVERALL_4:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_VIDEO_IC, &Mcu_RegStep_EIZOIC, (uint16)MCU_WRINUM_EIZOIC_CNTDSPSET,
                                                (uint8)GP_I2C_MA_SLA_1_VIDEO_IC, EIZOIC_CNTDSPSET, &Mcu_OnStep_EIZOIC_AckTime,
                                                st_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CENTERDISP_ON, &Mcu_RegSet_BetWaitTime_Stub);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_EIZOIC_OVRALL = (uint8)MCU_STEP_EIZOIC_OVERALL_FIN;
            /* 初期化完了通知 */
            vd_g_XspiIviSub1PowerDevInitCmpApp((U1)XSPI_IVI_POWER_EIZO_INI);
        }
        break;

    case MCU_STEP_EIZOIC_OVERALL_FIN:
        break;
    
    default:
        /* 異常時はフローをはじめからやり直す */
        Mcu_OnStep_EIZOIC_OVRALL = (uint8)MCU_STEP_EIZOIC_OVERALL_0;
        break;
    }
}