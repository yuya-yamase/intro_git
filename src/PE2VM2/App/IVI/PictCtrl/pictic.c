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
#define MCU_WRINUM_EIZOIC_INISET        (70U)   /* 6.2 初期化処理 レジスタ書込み回数 */
#define MCU_WRINUM_EIZOIC_SIPSET        (4U)    /* 6.3 SiP映像表示に関する処理 レジスタ書込み回数 */
#define MCU_WRINUM_EIZOIC_CAMSET        (28U)   /* 6.5.1.1 起動時のカメラ映像表示に関する設定 レジスタ書込み回数 */
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

    Mcu_OnStep_EIZOIC_OVRALL    = (uint8)MCU_STEP_EIZOIC_OVERALL_1;
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
        Mcu_OnStep_EIZOIC_OVRALL    = (uint8)MCU_STEP_EIZOIC_OVERALL_1;
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
        {        1,        10,         0},
        {       11,         6,         0},
        {       17,        10,         0},
        {       27,         6,         0},
        {       33,         1,         0},
        {       34,        10,         0},
        {       44,        10,         0},
        {       54,        10,         0},
        {       64,        10,         0},
        {       74,         7,         0},
        {       81,         1,         0},
        {       82,        10,         0},
        {       92,         5,         0},
        {       97,        10,         0},
        {      107,        10,         0},
        {      117,         9,         0},
        {      126,         8,         0},
        {      134,         8,         0},
        {      142,         1,         0},
        {      143,         2,         0},
        {      145,         1,         0},
        {      146,         3,         0},
        {      149,         1,         0},
        {      150,         7,         0},
        {      157,         1,         0},
        {      158,         2,         0},
        {      160,         1,         0},
        {      161,         1,         0},
        {      162,         1,         0},
        {      163,         1,         0},
        {      164,         1,         0},
        {      165,         4,         0},
        {      169,         1,         0},
        {      170,         3,         0},
        {      173,         1,         0},
        {      174,        10,         0},
        {      184,        10,         0},
        {      194,         1,         0},
        {      195,        10,         0},
        {      205,        10,         0},
        {      215,        10,         0},
        {      225,        10,         0},
        {      235,        10,         0},
        {      245,        10,         0},
        {      255,        10,         0},
        {      265,        10,         0},
        {      275,        10,         0},
        {      285,        10,         0},
        {      295,        10,         0},
        {      305,        10,         0},
        {      315,         8,         0},
        {      323,         1,         0},
        {      324,        10,         0},
        {      334,        10,         0},
        {      344,        10,         0},
        {      354,        10,         0},
        {      364,        10,         0},
        {      374,        10,         0},
        {      384,        10,         0},
        {      394,        10,         0},
        {      404,        10,         0},
        {      414,        10,         0},
        {      424,        10,         0},
        {      434,        10,         0},
        {      444,         8,         0},
        {      452,         1,         0},
        {      453,        10,         0},
        {      463,        10,         0},
        {      473,         4,         0}
    };
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    static const ST_REG_WRI_REQ EIZOIC_SIPSET[MCU_WRINUM_EIZOIC_SIPSET] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},
        {        1,         1,         0},
        {        2,         1,         0},
        {        3,         1,         0},
    };
    /* 6.5.1.1 起動時のカメラ映像表示に関する設定 */
    /* どのカメラサイズでも書込み位置と個数は共通 */
    static const ST_REG_WRI_REQ EIZOIC_CAMSET[MCU_WRINUM_EIZOIC_CAMSET] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},
        {        1,         8,         0},
        {        9,         6,         0},
        {       15,         1,         0},
        {       16,         8,         0},
        {       24,         8,         0},
        {       32,         1,         0},
        {       33,         8,         0},
        {       41,         1,         0},
        {       42,         8,         0},
        {       50,         8,         0},
        {       58,         8,         0},
        {       66,         8,         0},
        {       74,         3,         0},
        {       77,         8,         0},
        {       85,         8,         0},
        {       93,         8,         0},
        {      101,         8,         0},
        {      109,         3,         0},
        {      112,         1,         0},
        {      113,         2,         0},
        {      115,         1,         0},
        {      116,         4,         0},
        {      120,         1,         0},
        {      121,         1,         0},
        {      122,        10,         0},
        {      132,         1,         0},
        {      133,        10,         0}
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
    case MCU_STEP_EIZOIC_OVERALL_1:
        /* GVIF3送信仕様の"eDP設定"完了まで待機 */
        if(Mcu_OnStep_GVIF3TX_OVRALL == MCU_STEP_GVIF3TX_OVERALL_3){
            /* レジスタ書込み処理 */
            mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_VIDEO_IC, &Mcu_RegStep_EIZOIC, (uint16)MCU_WRINUM_EIZOIC_INISET,
                                                    (uint8)GP_I2C_MA_SLA_1_VIDEO_IC, EIZOIC_INISET, &Mcu_OnStep_EIZOIC_AckTime,
                                                    st_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT, &Mcu_RegSet_BetWaitTime_Stub);

            if(mcu_sts == (uint8)TRUE){
                /* 全書込み完了 次状態に遷移 */
                Mcu_OnStep_EIZOIC_OVRALL = (uint8)MCU_STEP_EIZOIC_OVERALL_2;
            }
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
        Mcu_OnStep_EIZOIC_OVRALL = (uint8)MCU_STEP_EIZOIC_OVERALL_1;
        break;
    }
}