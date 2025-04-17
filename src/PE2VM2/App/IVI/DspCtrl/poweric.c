/* メインタスクコードに移管するまでの仮置き */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "poweric.h"
#include "Dio.h"
#include "Dio_Symbols.h"
#include "Mcu_I2c_Ctrl_private.h"
#include "Mcu_Sys_Pwr_PowerIc.h"
#include "x_spi_ivi_sub1_power.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Port */
#define MCU_PORT_P_ON                   (DIO_ID_PORT11_CH6)     /* P-ON */
#define MCU_PORT_V33_PERI               (DIO_ID_PORT10_CH2)     /* V33-PERI-ON */

/* カウンタ最大値 */
#define MCU_SYS_COUNTTIME_FIN           (0xFFFFFFFFU)

/* 通常起動フロー */
#define MCU_WAIT_POWERIC_60MS           (60U / MCU_POWERIC_TASK_TIME)

#define MCU_WRINUM_POWERIC_INISET       (3U)    /* 初期設定 「5-1.初期設定」 レジスタ書込み回数 */
#define MCU_WRINUM_POWERIC_AMPON        (1U)    /* Amp On設定 レジスタ書込み回数 */
#define MCU_WRINUM_POWERIC_DIAGACT      (1U)    /* Diag有効設定 レジスタ書込み回数 */
#define MCU_WRINUM_POWERIC_MUTEOFF      (1U)    /* MUTE解除設定 レジスタ書込み回数 */

#if 0
/* 通常終了フロー */
#define MCU_OFFSTEP_P_IC_OVERALL_1      (1U)    /* "HexagonDSP MUTE設定完了通知"送信受領まで待機 */
#define MCU_OFFSTEP_P_IC_OVERALL_2      (2U)    /* wait min 55ms */
#define MCU_OFFSTEP_P_IC_OVERALL_3      (3U)    /* MUTE設定 (IB2読出し) */
#define MCU_OFFSTEP_P_IC_OVERALL_4      (4U)    /* MUTE設定 (IB2[0x82].D4=0,IB2[0x82].D3=0) */
#define MCU_OFFSTEP_P_IC_OVERALL_5      (5U)    /* wait 100ms */
#define MCU_OFFSTEP_P_IC_OVERALL_6      (6U)    /* Amp Off設定 (IB7読出し) */
#define MCU_OFFSTEP_P_IC_OVERALL_7      (7U)    /* Amp Off設定 (IB7[0x87].D0=0) */
#define MCU_OFFSTEP_P_IC_OVERALL_8      (8U)    /* wait min 5ms , スタンバイ P-ON=L */
#define MCU_OFFSTEP_P_IC_OVERALL_9      (9U)    /* Sys電源 V33-PERI-ON=L , wait min 100ms , P-IC電源制限 PIC-POFF=L */
#define MCU_OFFSTEP_P_IC_OVERALL_FIN    (10U)

#define MCU_OFFWAIT_POWERIC_5MS         (  5U   / MCU_POWERIC_TASK_TIME)
#define MCU_OFFWAIT_POWERIC_55MS        ( 55U   / MCU_POWERIC_TASK_TIME)
#define MCU_OFFWAIT_POWERIC_100MS       (100U   / MCU_POWERIC_TASK_TIME)

#define MCU_WRINUM_POWERIC_MUTEON       (1U)    /* MUTE設定 レジスタ書込み回数 */
#define MCU_WRINUM_POWERIC_AMPOFF       (1U)    /* Amp Off設定 レジスタ書込み回数 */

#define MCU_DIO_LOW                     (0U)
#define MCU_DIO_HIGH                    (1U)
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* デバイス起動用カウンタ */
static uint32   Mcu_Polling_POn;

/* 通常起動 */
       uint8    Mcu_OnStep_PowerIc_OVRALL;      /* 4.制御フロー 4-1.通常起動 仮置き中はexternするためstaticなし */
static uint32   Mcu_OnStep_PowerIc_AckTime;     /* Power-IC 書込み/読込みから応答までの時間計測 */
static uint32   Mcu_PowerIc_LinkTimer;          /* Power-IC Wati処理用タイマ */

static uint16   Mcu_RegStep_PowerIc;            /* Power-IC レジスタ書込み位置指定 */

#if 0
/* 通常終了 */
static uint8    Mcu_OffStep_PowerIc;
static uint32   Mcu_OffTime_PowerIc;
static uint32   Mcu_OffStep_PowerIc_AckTime;    /* Power-IC 書込み/読込みから応答までの時間計測 */
static uint8    Mcu_HexagonDSP_Flg;             /* HexagonDSP MUTE設定完了通知 */

static uint16   Mcu_RegStep_PowerIc;            /* Power-IC レジスタ書込み位置指定 */
#endif

/* レジスタアクセス */
static uint16   Mcu_RegSet_BetWaitTime_Stub;    /* レジスタアクセス間Waitタイマ スタブ */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     Mcu_Dev_Pwron_PowerIc_Polling_POn( void );
static void     Mcu_Dev_Pwron_PowerIc_RegSetting( void );
static uint8    Mcu_Dev_Pwron_TimChk( uint32 mcu_tim_cnt, const uint32 mcu_tim_fim);
static void     Mcu_Dev_Pwron_PowerIc_SetReg( void );
#if 0
static void     Mcu_Dev_Pwroff_PowerIC( void );
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*****************************************************************************
  Function      : poweric_Init
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void    poweric_Init( void )
{
    Mcu_Polling_POn             = (uint32)0U;

    Mcu_OnStep_PowerIc_OVRALL   = (uint8)MCU_ONSTEP_P_IC_OVERALL_1;
    Mcu_PowerIc_LinkTimer       = (uint32)0U;
    Mcu_OnStep_PowerIc_AckTime  = (uint32)0U;
    Mcu_RegStep_PowerIc         = (uint16)0U;

#if 0
    Mcu_OffStep_PowerIc         = (uint8)MCU_OFFSTEP_P_IC_OVERALL_1;
    Mcu_OffTime_PowerIc         = (uint32)0U;
    Mcu_OffStep_PowerIc_AckTime = (uint32)0U;
    Mcu_HexagonDSP_Flg          = (uint8)FALSE;
#endif

    Mcu_RegSet_BetWaitTime_Stub = (uint16)0xFFFFU;

    Mcu_Sys_Pwr_PowerIc_Init();
}

/*****************************************************************************
  Function      : poweric_main
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void    poweric_main( void )
{
    /* [Power-IC通常起動処理 レジスタ書込み]開始条件監視用ポーリング */
    Mcu_Dev_Pwron_PowerIc_Polling_POn();

    /* 通常起動 全体フロー処理 */
    Mcu_Dev_Pwron_PowerIc_RegSetting();

#if 0
    /* 通常終了 全体フロー処理 */
    Mcu_Dev_Pwroff_PowerIC();   /* "HexagonDSP MUTE設定完了通知"を取得できるまで非アクティブ化 */
#endif
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_Gyro_Polling_SendorOn
  Description   : 
  param[in/out] : 
  return        : -
  Note          : SENSOR-ON 監視
*****************************************************************************/
static void     Mcu_Dev_Pwron_PowerIc_Polling_POn( void )
{
    uint8   mcu_dio_ret;

    mcu_dio_ret =   Dio_ReadChannel(MCU_PORT_P_ON);

    if(mcu_dio_ret  ==  (uint8)STD_LOW){
        Mcu_Polling_POn             = (uint32)0U;
        Mcu_OnStep_PowerIc_OVRALL   = (uint8)MCU_ONSTEP_P_IC_OVERALL_1;
        Mcu_PowerIc_LinkTimer       = (uint32)0U;
        Mcu_OnStep_PowerIc_AckTime  = (uint32)0U;
        Mcu_RegStep_PowerIc         = (uint16)0U;
    }
    else if((mcu_dio_ret  ==  (uint8)STD_HIGH) &&
        (Mcu_Polling_POn < (uint32)MCU_SYS_COUNTTIME_FIN)){
        Mcu_Polling_POn++;
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
static void     Mcu_Dev_Pwron_PowerIc_RegSetting( void )
{
    static const uint32 MCU_PWRON_TIME_POWERIC  =   (210U / MCU_POWERIC_TASK_TIME);    /* min:210ms */

    uint8   mcu_time_chk;

    mcu_time_chk    =   Mcu_Dev_Pwron_TimChk(Mcu_Polling_POn, MCU_PWRON_TIME_POWERIC);

    if(mcu_time_chk ==  (uint8)TRUE){
        Mcu_Dev_Pwron_PowerIc_SetReg();
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
  Function      : Mcu_Dev_Pwron_PowerIc_SetReg
  Description   : 
  param[in/out] : 
  return        : -
  Note          : Power-IC初期化処理 レジスタ設定
*****************************************************************************/
static void     Mcu_Dev_Pwron_PowerIc_SetReg( void )
{
    static const ST_REG_WRI_REQ POWERIC_INISET[MCU_WRINUM_POWERIC_INISET] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         3,         0},
        {        3,         3,         0},
        {        6,         2,         0}
    };
    static const ST_REG_WRI_REQ POWERIC_AMPON[MCU_WRINUM_POWERIC_AMPON] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0}
    };
    static const ST_REG_WRI_REQ POWERIC_DIAGACT[MCU_WRINUM_POWERIC_DIAGACT] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0}
    };
    static const ST_REG_WRI_REQ POWERIC_MUTEOFF[MCU_WRINUM_POWERIC_MUTEOFF] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0}
    };
    uint8   mcu_sts;        /* 書込み状況 */

    mcu_sts         = (uint8)FALSE;

    /* Ackタイムアウト用カウンタインクリメント */
    if(Mcu_OnStep_PowerIc_AckTime < (uint32)MCU_SYS_COUNTTIME_FIN){
        Mcu_OnStep_PowerIc_AckTime++;
    }

    switch (Mcu_OnStep_PowerIc_OVRALL) {
        case MCU_ONSTEP_P_IC_OVERALL_1:
            /* 1ms待機は本caseに到達した時点で満たしていると判断するためwait処理は実施しない */
            /* レジスタ書込み処理 */
            mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_POWER, &Mcu_RegStep_PowerIc, (uint16)MCU_WRINUM_POWERIC_INISET,
                                                    (uint8)GP_I2C_MA_SLA_4_POWER, POWERIC_INISET, &Mcu_OnStep_PowerIc_AckTime,
                                                    st_sp_MCU_SYS_PWR_POWERIC_SETREG_INIT, &Mcu_RegSet_BetWaitTime_Stub);

            if(mcu_sts == (uint8)TRUE){
                /* 全書込み完了 次状態に遷移 */
                Mcu_OnStep_PowerIc_OVRALL = (uint8)MCU_ONSTEP_P_IC_OVERALL_2;
            }
            break;

        case MCU_ONSTEP_P_IC_OVERALL_2:
            /* レジスタ書込み処理 */
            mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_POWER, &Mcu_RegStep_PowerIc, (uint16)MCU_WRINUM_POWERIC_AMPON,
                                                    (uint8)GP_I2C_MA_SLA_4_POWER, POWERIC_AMPON, &Mcu_OnStep_PowerIc_AckTime,
                                                    st_sp_MCU_SYS_PWR_POWERIC_SETREG_AMP_ON, &Mcu_RegSet_BetWaitTime_Stub);

            if(mcu_sts == (uint8)TRUE){
                /* 全書込み完了 次状態に遷移 */
                Mcu_OnStep_PowerIc_OVRALL = (uint8)MCU_ONSTEP_P_IC_OVERALL_3;
            }
            break;

        case MCU_ONSTEP_P_IC_OVERALL_3:
            if(Mcu_PowerIc_LinkTimer != (uint32)MCU_SYS_COUNTTIME_FIN){
                Mcu_PowerIc_LinkTimer++;
            }
            if(Mcu_PowerIc_LinkTimer >= (uint32)MCU_WAIT_POWERIC_60MS){
                Mcu_OnStep_PowerIc_OVRALL = (uint8)MCU_ONSTEP_P_IC_OVERALL_4;         /* 次状態に遷移 */
                Mcu_PowerIc_LinkTimer = (uint32)0U;
            }
            break;

        case MCU_ONSTEP_P_IC_OVERALL_4:
            /* レジスタ書込み処理 */
            mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_POWER, &Mcu_RegStep_PowerIc, (uint16)MCU_WRINUM_POWERIC_DIAGACT,
                                                    (uint8)GP_I2C_MA_SLA_4_POWER, POWERIC_DIAGACT, &Mcu_OnStep_PowerIc_AckTime,
                                                    st_sp_MCU_SYS_PWR_POWERIC_SETREG_DIAG_ON, &Mcu_RegSet_BetWaitTime_Stub);

            if(mcu_sts == (uint8)TRUE){
                /* 全書込み完了 次状態に遷移 */
                Mcu_OnStep_PowerIc_OVRALL = (uint8)MCU_ONSTEP_P_IC_OVERALL_5;
            }
            break;

        case MCU_ONSTEP_P_IC_OVERALL_5:
            /* レジスタ書込み処理 */
            mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_POWER, &Mcu_RegStep_PowerIc, (uint16)MCU_WRINUM_POWERIC_MUTEOFF,
                                                    (uint8)GP_I2C_MA_SLA_4_POWER, POWERIC_MUTEOFF, &Mcu_OnStep_PowerIc_AckTime,
                                                    st_sp_MCU_SYS_PWR_POWERIC_SETREG_MUTE_OFF, &Mcu_RegSet_BetWaitTime_Stub);

            if(mcu_sts == (uint8)TRUE){
                /* 全書込み完了 次状態に遷移 */
                Mcu_OnStep_PowerIc_OVRALL = (uint8)MCU_ONSTEP_P_IC_OVERALL_FIN;
                /* 初期化完了通知 */
                vd_g_XspiIviSub1PowerDevInitCmpApp((U1)XSPI_IVI_POWER_POWER_INI);
            }
            break;

        case MCU_ONSTEP_P_IC_OVERALL_FIN:
            /* 正常起動時は何もしない */
            break;

        default:
            /* do nothing */
            break;
    }
}
#if 0
/*****************************************************************************
  Function      : Mcu_Dev_
  Description   : HexagonDSP MUTE設定完了通知
  param[in/out] : 
  return        : 
  Note          : 
*****************************************************************************/
void            Mcu_Dev_HexagonDSP_MUTE( void )
{
    /* 引数いるかも？ */
    Mcu_HexagonDSP_Flg = (uint8)TRUE;
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwroff_PowerIC
  Description   : 
  param[in/out] : 
  return        : PWROFF_POWERIC_BIT ：プロセス完了
  Note          : シス検暫定対応あり
*****************************************************************************/
static void     Mcu_Dev_Pwroff_PowerIC( void )
{
    static const ST_REG_WRI_REQ POWERIC_MUTEON[MCU_WRINUM_POWERIC_MUTEON] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},
    };
    static const ST_REG_WRI_REQ POWERIC_AMPOFF[MCU_WRINUM_POWERIC_AMPOFF] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},
    };
    uint8   mcu_read_v33_peri;
    uint16  mcu_return;
    uint8   mcu_sts;                /* レジスタ書込み状況 */
    uint8   mcu_reg_wri;            /* 書込みデータ作成 */

    mcu_read_v33_peri   = (uint8)STD_HIGH;
    mcu_return          = (uint16)FALSE;
    mcu_sts             = (uint8)FALSE;
    mcu_reg_wri         = (uint8)0x00U;
    
    switch (Mcu_OffStep_PowerIc)
    {
        case MCU_OFFSTEP_P_IC_OVERALL_1:
            /* HexagonDSP MUTE設定完了通知があるまでとどまる */
            if(Mcu_HexagonDSP_Flg == (uint8)TRUE){
                Mcu_HexagonDSP_Flg  = (uint8)FALSE;
                Mcu_OffStep_PowerIc = (uint8)MCU_OFFSTEP_P_IC_OVERALL_2;         /* 次状態に遷移 */
                break;
            }

        case MCU_OFFSTEP_P_IC_OVERALL_2:
            if(Mcu_OffTime_PowerIc != MCU_SYS_COUNTTIME_FIN){
                Mcu_OffTime_PowerIc++;
            }
            if(Mcu_OffTime_PowerIc >= MCU_OFFWAIT_POWERIC_55MS){
                Mcu_OffStep_PowerIc = (uint8)MCU_OFFSTEP_P_IC_OVERALL_3;       /* 次状態に遷移 */
                Mcu_OffTime_PowerIc = (uint16)0U;                   /* タイマクリア */
            }
            break;

        case MCU_OFFSTEP_P_IC_OVERALL_3:
            /* レジスタ読出し処理 */
            mcu_sts = Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_POWER, &Mcu_RegStep_PowerIc, (uint8)GP_I2C_MA_SLA_4_POWER,
                                                    &Mcu_OffStep_PowerIc_AckTime, &st_sp_MCU_SYS_PWR_POWERIC_SETREG_MUTE_RD, Mcu_RegSet_BetWaitTime_Stub);

            if(mcu_sts == (uint8)TRUE){
                /* 読出ししたデータを元に次Stepの書込みデータを作成 */
                mcu_reg_wri = st_sp_MCU_SYS_PWR_POWERIC_SETREG_MUTE_RD[1].u1p_pdu[1];   /* 読出しデータ取得 */
                mcu_reg_wri = mcu_reg_wri & (U1)0xE7U;                                  /* D4=0, D3=0に変更 */
                st_sp_MCU_SYS_PWR_POWERIC_SETREG_MUTE_ON[0].u1p_pdu[2] = mcu_reg_wri;   /* 書込みデータ格納 */
                /* 全書込み完了 次状態に遷移 */
                Mcu_OffStep_PowerIc = (uint8)MCU_OFFSTEP_P_IC_OVERALL_4;       /* 次状態に遷移 */
            }
            break;

        case MCU_OFFSTEP_P_IC_OVERALL_4:
            /* レジスタ書込み処理 */
            mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_POWER, &Mcu_RegStep_PowerIc, (uint16)MCU_WRINUM_POWERIC_MUTEON,
                                                    (uint8)GP_I2C_MA_SLA_4_POWER, POWERIC_MUTEON, &Mcu_OffStep_PowerIc_AckTime,
                                                    st_sp_MCU_SYS_PWR_POWERIC_SETREG_MUTE_ON, &Mcu_RegSet_BetWaitTime_Stub);

            if(mcu_sts == (uint8)TRUE){
                /* 全書込み完了 次状態に遷移 */
                Mcu_OffStep_PowerIc = (uint8)MCU_OFFSTEP_P_IC_OVERALL_5;
            }
            break;
        
        case MCU_OFFSTEP_P_IC_OVERALL_5:
            if(Mcu_OffTime_PowerIc != MCU_SYS_COUNTTIME_FIN){
                Mcu_OffTime_PowerIc++;
            }
            if(Mcu_OffTime_PowerIc >= MCU_OFFWAIT_POWERIC_100MS){
                Mcu_OffStep_PowerIc = (uint8)MCU_OFFSTEP_P_IC_OVERALL_6;   /* 次状態に遷移 */
                Mcu_OffTime_PowerIc = (uint16)0U;                       /* タイマクリア */
            }
            break;

        case MCU_OFFSTEP_P_IC_OVERALL_6:
            /* レジスタ読出し処理 */
            mcu_sts = Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_POWER, &Mcu_RegStep_PowerIc, (uint8)GP_I2C_MA_SLA_4_POWER,
                                                    &Mcu_OffStep_PowerIc_AckTime, &st_sp_MCU_SYS_PWR_POWERIC_SETREG_AMP_RD, Mcu_RegSet_BetWaitTime_Stub);

            if(mcu_sts == (uint8)TRUE){
                /* 読出ししたデータを元に次Stepの書込みデータを作成 */
                mcu_reg_wri = st_sp_MCU_SYS_PWR_POWERIC_SETREG_AMP_RD[1].u1p_pdu[1];    /* 読出しデータ取得 */
                mcu_reg_wri = mcu_reg_wri & (U1)0xFEU;                                  /* D0=0に変更 */
                st_sp_MCU_SYS_PWR_POWERIC_SETREG_AMP_OFF[0].u1p_pdu[2] = mcu_reg_wri;   /* 書込みデータ格納 */
                /* 全書込み完了 次状態に遷移 */
                Mcu_OffStep_PowerIc = (uint8)MCU_OFFSTEP_P_IC_OVERALL_7;       /* 次状態に遷移 */
            }
            break;

        case MCU_OFFSTEP_P_IC_OVERALL_7:
            /* レジスタ書込み処理 */
            mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_POWER, &Mcu_RegStep_PowerIc, (uint16)MCU_WRINUM_POWERIC_AMPOFF,
                                                    (uint8)GP_I2C_MA_SLA_4_POWER, POWERIC_AMPOFF, &Mcu_OffStep_PowerIc_AckTime,
                                                    st_sp_MCU_SYS_PWR_POWERIC_SETREG_AMP_OFF, &Mcu_RegSet_BetWaitTime_Stub);

            if(mcu_sts == (uint8)TRUE){
                /* 全書込み完了 次状態に遷移 */
                Mcu_OffStep_PowerIc = (uint8)MCU_OFFSTEP_P_IC_OVERALL_8;       /* 次状態に遷移 */
            }
            break;

        case MCU_OFFSTEP_P_IC_OVERALL_8:
            if(Mcu_OffTime_PowerIc != MCU_SYS_COUNTTIME_FIN){
                Mcu_OffTime_PowerIc++;
            }
            if(Mcu_OffTime_PowerIc >= MCU_OFFWAIT_POWERIC_5MS){
                Mcu_Dev_Pwron_SetPort(MCU_PORT_P_ON , MCU_DIO_LOW);      /* スタンバイ */
                Mcu_OffStep_PowerIc = (uint8)MCU_OFFSTEP_P_IC_OVERALL_9;   /* 次状態に遷移 */
                Mcu_OffTime_PowerIc = (uint16)0U;                       /* タイマクリア */
            }
            break;

        case MCU_OFFSTEP_P_IC_OVERALL_9:
            if(Mcu_OffTime_PowerIc != MCU_SYS_COUNTTIME_FIN){
                Mcu_OffTime_PowerIc++;
            }

            mcu_read_v33_peri = Dio_ReadChannel(MCU_PORT_V33_PERI); /* V33-PERI-ON読み出し */
            if(mcu_read_v33_peri == (uint8)STD_HIGH){
                Mcu_OffTime_PowerIc = (uint16)0U;       /* V33-PERI-ON=Highの場合次処理への遷移を抑制する */
            }

            if(Mcu_OffTime_PowerIc >= MCU_OFFWAIT_POWERIC_100MS){
                Mcu_Dev_Pwron_SetPort(MCU_PORT_P_ON , MCU_DIO_LOW);     /* P-IC電源制限 */
                Mcu_OffStep_PowerIc = (uint8)MCU_OFFSTEP_P_IC_OVERALL_FIN;     /* 次状態に遷移 */
                Mcu_OffTime_PowerIc = (uint16)0U;                           /* タイマクリア */
            }
            break;

        case MCU_OFFSTEP_P_IC_OVERALL_FIN:
            break;

        default:
            /* do nothing */
            break;
    }
}
#endif