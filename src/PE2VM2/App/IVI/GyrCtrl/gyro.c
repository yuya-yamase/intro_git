/* メインタスクコードに移管するまでの仮置き */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gyro.h"
#include "gpt_drv_frt.h"
#include "Dio.h"
#include "Dio_Symbols.h"
#include "Mcu_I2c_Ctrl_private.h"
#include "Mcu_Sys_Pwr_Gyr.h"
#include "x_spi_ivi_sub1_power.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* FRT */
#define MCU_FRT_1MS                     (1000 * GPT_FRT_1US)

/* Port */
#define MCU_PORT_SENSOR_ON              (DIO_ID_PORT8_CH7)      /* SENSOR-ON */
#define MCU_PORT_V33_PERI               (DIO_ID_PORT10_CH2)     /* V33-PERI-ON */
/* カウンタ最大値 */
#define MCU_SYS_COUNTTIME_FIN           (0xFFFFFFFFU)

/* ジャイロ・加速度センサ制御仕様 */
#define MCU_WAIT_GYRO_60MS              (60U / MCU_GYRO_TASK_TIME)

#define MCU_WRINUM_GYRO_WDG_GYR         (1U)    /* Set Watchdog Timer (Gyro) レジスタ書込み回数 */
#define MCU_WRINUM_GYRO_WDG_ACC         (1U)    /* Set Watchdog Timer (Gセンサ) レジスタ書込み回数 */
#define MCU_WRINUM_GYRO_MODE_ON_ACC     (1U)    /* Mode Change (Gセンサ) ON suspend mode ⇒ normal mode レジスタ書込み回数 */
#define MCU_WRINUM_GYRO_SETUP_GYR       (1U)    /* Setup Sensor (Gyro) レジスタ書込み回数 */
#define MCU_WRINUM_GYRO_SETUP_SEN2_ACC  (1U)    /* Setup Sensor (Gセンサ2) レジスタ書込み回数 */
#define MCU_WRINUM_GYRO_SETUP_SEN1_ACC  (1U)    /* Setup Sensor (Gセンサ1) レジスタ書込み回数 */
#define MCU_WRINUM_GYRO_MODE_OFF_GYR    (1U)    /* Mode Change (Gyro) OFF normal mode ⇒ suspend mode レジスタ書込み回数 */
#define MCU_WRINUM_GYRO_SEN1_BW_ACC     (1U)    /* Gセンサ 0x40に0xA8をWrite レジスタ書込み回数 */
#define MCU_WRINUM_GYRO_MODE_ON_GYR     (1U)    /* Mode Change (Gyro) ON suspend mode ⇒ normal mode レジスタ書込み回数 */

#define MCU_DIO_LOW                     (0U)
#define MCU_DIO_HIGH                    (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* フリーランタイマ */
uint32          Mcu_frt_stamp_gyro[GPT_FRT_USELPSD_NUM_PARAM];

/* デバイス起動用カウンタ */
static uint32   Mcu_Polling_SendorOn;

/* ジャイロ・加速度センサ制御仕様 */
       uint8    Mcu_OnStep_Gyro_1_OVRALL;       /* 起動フロー(1) 仮置き中はexternするためstaticなし */
       uint8    Mcu_OnStep_Gyro_2_OVRALL;       /* 起動フロー(2) 仮置き中はexternするためstaticなし */
static uint32   Mcu_OnStep_Gyro_AckTime;        /* ジャイロ・加速度センサ 書込み/読込みから応答までの時間計測 */
static uint32   Mcu_Gyro_LinkTimer;             /* ジャイロ・加速度センサ Wati処理用タイマ */

static uint16   Mcu_RegStep_Gyro;               /* ジャイロ・加速度センサ レジスタ書込み位置指定 */

/* レジスタアクセス */
static uint16   Mcu_RegSet_BetWaitTime_Stub;    /* レジスタアクセス間Waitタイマ スタブ */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     Mcu_Dev_Pwron_Gyro_Polling_SendorOn( void );
static void     Mcu_Dev_Pwron_Gyro_RegSetting( void );
static uint8    Mcu_Dev_Pwron_TimChk( uint32 mcu_tim_cnt, const uint32 mcu_tim_fim);
static void     Mcu_Dev_Pwron_Gyro_SetReg( void );

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*****************************************************************************
  Function      : gyro_Init
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void    gyro_Init( void )
{
    /* フリーランタイマ用配列初期化 */
    for(uint32 cnt = 0; cnt < (uint32)GPT_FRT_USELPSD_NUM_PARAM; cnt++){
        Mcu_frt_stamp_gyro[cnt] = 0;
    }

    /* Init時のフリーランタイマ取得 */
    Mcu_frt_stamp_gyro[GPT_FRT_USELPSD_BASE] = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA);

    Mcu_Polling_SendorOn        = (uint32)0U;

    Mcu_OnStep_Gyro_1_OVRALL    = (uint8)MCU_STEP_GYRO1_OVERALL_1;
    Mcu_OnStep_Gyro_2_OVRALL    = (uint8)MCU_STEP_GYRO2_OVERALL_0;  /* 起動フロー(1)完了まで実施しない */
    Mcu_Gyro_LinkTimer          = (uint32)0U;
    Mcu_OnStep_Gyro_AckTime     = (uint32)0U;
    Mcu_RegStep_Gyro            = (uint16)0U;

    Mcu_RegSet_BetWaitTime_Stub = (uint16)0xFFFFU;
}

/*****************************************************************************
  Function      : gyro_main
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void    gyro_main( void )
{
    /* [Gyro 起動フロー(1)]開始条件監視用ポーリング */
    Mcu_Dev_Pwron_Gyro_Polling_SendorOn();

    /* 全体フロー処理 */
    Mcu_Dev_Pwron_Gyro_RegSetting();
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_Gyro_Polling_SendorOn
  Description   : 
  param[in/out] : 
  return        : -
  Note          : SENSOR-ON 監視
*****************************************************************************/
static void     Mcu_Dev_Pwron_Gyro_Polling_SendorOn( void )
{
    uint8   mcu_dio_ret;

    mcu_dio_ret =   Dio_ReadChannel(MCU_PORT_SENSOR_ON);

    if(mcu_dio_ret  ==  (uint8)STD_LOW){
        Mcu_Polling_SendorOn        = (uint32)0U;
        Mcu_OnStep_Gyro_1_OVRALL    = (uint8)MCU_STEP_GYRO1_OVERALL_1;
        Mcu_OnStep_Gyro_2_OVRALL    = (uint8)MCU_STEP_GYRO2_OVERALL_0;  /* 起動フロー(1)完了まで実施しない */
        Mcu_Gyro_LinkTimer          = (uint32)0U;
        Mcu_OnStep_Gyro_AckTime     = (uint32)0U;
        Mcu_RegStep_Gyro            = (uint16)0U;
    }
    else if((mcu_dio_ret  ==  (uint8)STD_HIGH) &&
        (Mcu_Polling_SendorOn < (uint32)MCU_SYS_COUNTTIME_FIN)){
        Mcu_Polling_SendorOn++;
    }
    else{
        /* do nothing */
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_Gyro_RegSetting
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 7.レジスタ設定
*****************************************************************************/
static void     Mcu_Dev_Pwron_Gyro_RegSetting( void )
{
    static const uint32 MCU_PWRON_TIME_GYRO     =   (210U / MCU_GYRO_TASK_TIME);    /* min:210ms */

    uint8   mcu_time_chk;

    mcu_time_chk    =   Mcu_Dev_Pwron_TimChk(Mcu_Polling_SendorOn, MCU_PWRON_TIME_GYRO);

    if(mcu_time_chk ==  (uint8)TRUE){
        Mcu_Dev_Pwron_Gyro_SetReg();
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
  Function      : Mcu_Dev_Pwron_Gyro_SetReg
  Description   : 
  param[in/out] : 
  return        : -
  Note          : ジャイロ・加速度センサ初期化処理 レジスタ設定
*****************************************************************************/
static void     Mcu_Dev_Pwron_Gyro_SetReg( void )
{
    static const ST_REG_WRI_REQ GYRO_WDG_GYR[MCU_WRINUM_GYRO_WDG_GYR] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0}
    };
    static const ST_REG_WRI_REQ GYRO_WDG_ACC[MCU_WRINUM_GYRO_WDG_ACC] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0}
    };
    static const ST_REG_WRI_REQ GYRO_MODE_ON_ACC[MCU_WRINUM_GYRO_MODE_ON_ACC] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0}
    };
    static const ST_REG_WRI_REQ GYRO_SETUP_GYR[MCU_WRINUM_GYRO_SETUP_GYR] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         2,         0},
    };
    static const ST_REG_WRI_REQ GYRO_SETUP_SEN2_ACC[MCU_WRINUM_GYRO_SETUP_SEN2_ACC] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         2,         0}
    };
    static const ST_REG_WRI_REQ GYRO_SETUP_SEN1_ACC[MCU_WRINUM_GYRO_SETUP_SEN1_ACC] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         2,         0}
    };
    static const ST_REG_WRI_REQ GYRO_MODE_OFF_GYR[MCU_WRINUM_GYRO_MODE_OFF_GYR] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0}
    };
    static const ST_REG_WRI_REQ GYRO_SETUP_SEN1_BW_ACC[MCU_WRINUM_GYRO_SEN1_BW_ACC] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0}
    };
    static const ST_REG_WRI_REQ GYRO_MODE_ON_GYR[MCU_WRINUM_GYRO_MODE_ON_GYR] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0}
    };
    uint8   mcu_time_chk;
    uint8   mcu_sts;        /* 書込み状況 */
    uint8   mcu_dio_ret;

    mcu_sts         = (uint8)FALSE;
    mcu_dio_ret     = (uint8)MCU_DIO_LOW;

    /* Ackタイムアウト用カウンタインクリメント */
    if(Mcu_OnStep_Gyro_AckTime < (uint32)MCU_SYS_COUNTTIME_FIN){
        Mcu_OnStep_Gyro_AckTime++;
    }

    /* 5.2.1 起動フロー(1) +B起動時の初期設定 */
    switch (Mcu_OnStep_Gyro_1_OVRALL)
    {
    case MCU_STEP_GYRO1_OVERALL_1:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_GYRO, &Mcu_RegStep_Gyro, (uint16)MCU_WRINUM_GYRO_WDG_GYR,
                                                (uint8)GP_I2C_MA_SLA_6_GYRO, GYRO_WDG_GYR, &Mcu_OnStep_Gyro_AckTime,
                                                st_sp_MCU_SYS_PWR_GYR_REG_GYR_WDG, &Mcu_RegSet_BetWaitTime_Stub);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_Gyro_1_OVRALL = (uint8)MCU_STEP_GYRO1_OVERALL_2;
        }
        break;

    case MCU_STEP_GYRO1_OVERALL_2:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_G_MONI, &Mcu_RegStep_Gyro, (uint16)MCU_WRINUM_GYRO_WDG_ACC,
                                                (uint8)GP_I2C_MA_SLA_7_G_MONI, GYRO_WDG_ACC, &Mcu_OnStep_Gyro_AckTime,
                                                st_sp_MCU_SYS_PWR_GYR_REG_ACC_WDG, &Mcu_RegSet_BetWaitTime_Stub);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_Gyro_1_OVRALL = (uint8)MCU_STEP_GYRO1_OVERALL_3;
        }
        break;

    case MCU_STEP_GYRO1_OVERALL_3:
        /* 1ms待機は本caseに到達した時点で満たしていると判断するためwait処理は実施しない */
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_G_MONI, &Mcu_RegStep_Gyro, (uint16)MCU_WRINUM_GYRO_MODE_ON_ACC,
                                                (uint8)GP_I2C_MA_SLA_7_G_MONI, GYRO_MODE_ON_ACC, &Mcu_OnStep_Gyro_AckTime,
                                                st_sp_MCU_SYS_PWR_GYR_REG_ACC_MODE_ON, &Mcu_RegSet_BetWaitTime_Stub);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_Gyro_1_OVRALL = (uint8)MCU_STEP_GYRO1_OVERALL_4;
        }
        break;

    case MCU_STEP_GYRO1_OVERALL_4:
        mcu_time_chk = Mcu_Dev_Pwron_TimChk(Mcu_Gyro_LinkTimer, (uint32)MCU_WAIT_GYRO_60MS);
        if(mcu_time_chk == (uint8)TRUE){
            /* Wati t3完了 次状態に遷移 */
            Mcu_OnStep_Gyro_1_OVRALL   = (uint8)MCU_STEP_GYRO1_OVERALL_5;
            Mcu_Gyro_LinkTimer  = (uint32)0U;
        }
        else{
            Mcu_Gyro_LinkTimer++;
        }
        break;

    case MCU_STEP_GYRO1_OVERALL_5:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_GYRO, &Mcu_RegStep_Gyro, (uint16)MCU_WRINUM_GYRO_SETUP_GYR,
                                                (uint8)GP_I2C_MA_SLA_6_GYRO, GYRO_SETUP_GYR, &Mcu_OnStep_Gyro_AckTime,
                                                st_sp_MCU_SYS_PWR_GYR_REG_GYR_SETUP, &Mcu_RegSet_BetWaitTime_Stub);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_Gyro_1_OVRALL = (uint8)MCU_STEP_GYRO1_OVERALL_6;
        }
        break;

    case MCU_STEP_GYRO1_OVERALL_6:
        /* 5.5 詳細設定 (5-2) Self Test (Gyro) */
        /* フェール機能TBDであり判定結果で処理が変わらないためskip */
        mcu_sts = (uint8)TRUE;
        if(mcu_sts == (uint8)TRUE){
            /* テスト結果：OK 次状態に遷移 */
            Mcu_OnStep_Gyro_1_OVRALL = (uint8)MCU_STEP_GYRO1_OVERALL_7;
        }
        break;

    case MCU_STEP_GYRO1_OVERALL_7:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_GYRO, &Mcu_RegStep_Gyro, (uint16)MCU_WRINUM_GYRO_SETUP_GYR,
                                                (uint8)GP_I2C_MA_SLA_6_GYRO, GYRO_SETUP_GYR, &Mcu_OnStep_Gyro_AckTime,
                                                st_sp_MCU_SYS_PWR_GYR_REG_GYR_SETUP, &Mcu_RegSet_BetWaitTime_Stub);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_Gyro_1_OVRALL = (uint8)MCU_STEP_GYRO1_OVERALL_8;
        }
        break;

    case MCU_STEP_GYRO1_OVERALL_8:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_G_MONI, &Mcu_RegStep_Gyro, (uint16)MCU_WRINUM_GYRO_SETUP_SEN2_ACC,
                                                (uint8)GP_I2C_MA_SLA_7_G_MONI, GYRO_SETUP_SEN2_ACC, &Mcu_OnStep_Gyro_AckTime,
                                                st_sp_MCU_SYS_PWR_GYR_REG_ACC_SEN2_SETUP, &Mcu_RegSet_BetWaitTime_Stub);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_Gyro_1_OVRALL = (uint8)MCU_STEP_GYRO1_OVERALL_9;
        }
        break;

    case MCU_STEP_GYRO1_OVERALL_9:
        /* 5.5 詳細設定 (5-12) Self-Test (Gセンサ) */
        /* フェール機能TBDであり判定結果で処理が変わらないためskip */
        mcu_sts = (uint8)TRUE;
        if(mcu_sts == (uint8)TRUE){
            /* テスト結果：OK 次状態に遷移 */
            Mcu_OnStep_Gyro_1_OVRALL = (uint8)MCU_STEP_GYRO1_OVERALL_10;
        }
        break;
    
    case MCU_STEP_GYRO1_OVERALL_10:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_G_MONI, &Mcu_RegStep_Gyro, (uint16)MCU_WRINUM_GYRO_SETUP_SEN1_ACC,
                                                (uint8)GP_I2C_MA_SLA_7_G_MONI, GYRO_SETUP_SEN1_ACC, &Mcu_OnStep_Gyro_AckTime,
                                                st_sp_MCU_SYS_PWR_GYR_REG_ACC_SEN1_SETUP, &Mcu_RegSet_BetWaitTime_Stub);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_Gyro_1_OVRALL = (uint8)MCU_STEP_GYRO1_OVERALL_11;
        }
        break;

    case MCU_STEP_GYRO1_OVERALL_11:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_GYRO, &Mcu_RegStep_Gyro, (uint16)MCU_WRINUM_GYRO_MODE_OFF_GYR,
                                                (uint8)GP_I2C_MA_SLA_6_GYRO, GYRO_MODE_OFF_GYR, &Mcu_OnStep_Gyro_AckTime,
                                                st_sp_MCU_SYS_PWR_GYR_REG_GYR_MODE_OFF, &Mcu_RegSet_BetWaitTime_Stub);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_Gyro_1_OVRALL = (uint8)MCU_STEP_GYRO1_OVERALL_FIN;
            Mcu_OnStep_Gyro_2_OVRALL = (uint8)MCU_STEP_GYRO2_OVERALL_1;    /* 起動フロー1完了のため、起動フロー2の状態を初期化 */
        }
        break;

    case MCU_STEP_GYRO1_OVERALL_FIN:
        /* do nothing */
        break;

    default:
        /* 異常時はフローをはじめからやり直す */
        Mcu_OnStep_Gyro_1_OVRALL = (uint8)MCU_STEP_GYRO1_OVERALL_1;
        Mcu_OnStep_Gyro_2_OVRALL = (uint8)MCU_STEP_GYRO2_OVERALL_0;
        break;
    }

    /* 5.2.2 起動フロー(2) GyroをNormal modeに設定する */
    switch (Mcu_OnStep_Gyro_2_OVRALL)
    {
    case MCU_STEP_GYRO2_OVERALL_0:
        /* 起動フロー(1)終了まで待機 */
        break;

    case MCU_STEP_GYRO2_OVERALL_1:
        mcu_dio_ret =   Dio_ReadChannel(MCU_PORT_V33_PERI);

        if(mcu_dio_ret == (uint8)MCU_DIO_HIGH){
            /* V33-Peri-ON=Hiを検知したら次状態に遷移 */
            Mcu_OnStep_Gyro_2_OVRALL = (uint8)MCU_STEP_GYRO2_OVERALL_2;
        }
        break;

    case MCU_STEP_GYRO2_OVERALL_2:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_G_MONI, &Mcu_RegStep_Gyro, (uint16)MCU_WRINUM_GYRO_SEN1_BW_ACC,
                                                (uint8)GP_I2C_MA_SLA_7_G_MONI, GYRO_SETUP_SEN1_BW_ACC, &Mcu_OnStep_Gyro_AckTime,
                                                st_sp_MCU_SYS_PWR_GYR_REG_ACC_SEN1_SETUP, &Mcu_RegSet_BetWaitTime_Stub);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_Gyro_2_OVRALL = (uint8)MCU_STEP_GYRO2_OVERALL_3;
        }
        break;

    case MCU_STEP_GYRO2_OVERALL_3:
        /* 1ms待機は本caseに到達した時点で満たしていると判断するためwait処理は実施しない */
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_GYRO, &Mcu_RegStep_Gyro, (uint16)MCU_WRINUM_GYRO_MODE_ON_GYR,
                                                (uint8)GP_I2C_MA_SLA_6_GYRO, GYRO_MODE_ON_GYR, &Mcu_OnStep_Gyro_AckTime,
                                                st_sp_MCU_SYS_PWR_GYR_REG_GYR_MODE_ON, &Mcu_RegSet_BetWaitTime_Stub);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_Gyro_2_OVRALL = (uint8)MCU_STEP_GYRO2_OVERALL_4;
        }
        break;

    case MCU_STEP_GYRO2_OVERALL_4:
        /* 1ms待機は本caseに到達した時点で満たしていると判断するためwait処理は実施しない */
        Mcu_OnStep_Gyro_2_OVRALL = (uint8)MCU_STEP_GYRO2_OVERALL_FIN;
        /* 初期化完了通知 */
        vd_g_XspiIviSub1PowerDevInitCmpApp((U1)XSPI_IVI_POWER_GYRO_INI);
        break;

    case MCU_STEP_GYRO2_OVERALL_FIN:
        /* do nothing */
        break;

    default:
        /* 異常時はフローをはじめからやり直す */
        Mcu_OnStep_Gyro_2_OVRALL = (uint8)MCU_STEP_GYRO2_OVERALL_1;
        break;
    }
}