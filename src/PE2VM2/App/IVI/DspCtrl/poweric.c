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
#define POWERIC_PORT_P_ON               (DIO_ID_PORT11_CH6)     /* P-ON */
#define POWERIC_PORT_V33_PERI           (DIO_ID_PORT10_CH2)     /* V33-PERI-ON */
#define POWERIC_PORT_PIC_POFF           (DIO_ID_PORT11_CH7)     /* PIC-POFF */
#define POWERIC_DIO_LOW                 (STD_LOW)
#define POWERIC_DIO_HIGH                (STD_HIGH)

/* カウンタ最大値 */
#define POWERIC_COUNTTIME_FIN           (0xFFFFFFFFU)

/* 通常起動フロー */
#define POWERIC_WAIT_PON                (210U   / MCU_POWERIC_TASK_TIME)
#define POWERIC_WAIT_60MS               ( 60U   / MCU_POWERIC_TASK_TIME)

#define POWERIC_WRINUM_INISET           (3U)    /* 初期設定 「5-1.初期設定」 レジスタ書込み回数 */
#define POWERIC_WRINUM_AMPON            (1U)    /* Amp On設定 レジスタ書込み回数 */
#define POWERIC_WRINUM_DIAGACT          (1U)    /* Diag有効設定 レジスタ書込み回数 */
#define POWERIC_WRINUM_MUTEOFF          (1U)    /* MUTE解除設定 レジスタ書込み回数 */

/* 通常終了フロー */
#define POWERIC_OFFSTEP_OVERALL_1       (1U)    /* wait min 55ms */
#define POWERIC_OFFSTEP_OVERALL_2       (2U)    /* MUTE設定 (IB2読出し) */
#define POWERIC_OFFSTEP_OVERALL_3       (3U)    /* MUTE設定 (IB2[0x82].D4=0,IB2[0x82].D3=0) */
#define POWERIC_OFFSTEP_OVERALL_4       (4U)    /* wait 100ms */
#define POWERIC_OFFSTEP_OVERALL_5       (5U)    /* Amp Off設定 (IB7読出し) */
#define POWERIC_OFFSTEP_OVERALL_6       (6U)    /* Amp Off設定 (IB7[0x87].D0=0) */
#define POWERIC_OFFSTEP_OVERALL_7       (7U)    /* wait min 5ms , スタンバイ P-ON=L */
#define POWERIC_OFFSTEP_OVERALL_8       (8U)    /* Sys電源 V33-PERI-ON=L , wait min 100ms , P-IC電源制限 PIC-POFF=L */
#define POWERIC_OFFSTEP_OVERALL_FIN     (9U)

#define POWERIC_OFFWAIT_5MS             (  5U   / MCU_POWERIC_TASK_TIME)
#define POWERIC_OFFWAIT_55MS            ( 55U   / MCU_POWERIC_TASK_TIME)
#define POWERIC_OFFWAIT_100MS           (100U   / MCU_POWERIC_TASK_TIME)

#define POWERIC_WRINUM_MUTEON           (1U)    /* MUTE設定 レジスタ書込み回数 */
#define POWERIC_WRINUM_AMPOFF           (1U)    /* Amp Off設定 レジスタ書込み回数 */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* デバイス起動用カウンタ */
static U4       u4_t_PowerIc_Polling;

/* Power-IC Wati処理用タイマ */
static U4       u4_s_PowerIc_LinkTimer;

/* 通常起動 */
       U1       u1_s_PowerIc_OnStep_OverAll;    /* 4.制御フロー 4-1.通常起動 仮置き中はexternするためstaticなし */

/* 通常終了 */
static U1       u1_s_PowerIc_OffStep_OverAll;
static U1       u1_s_PowerIc_MUTE_Hook;         /* HexagonDSP MUTE設定完了通知 */

/* レジスタアクセス */
static U2       u2_s_PowerIc_RegStep;           /* Power-IC レジスタ書込み位置指定 */
static U4       u4_s_PowerIc_AckTime;           /* Power-IC 書込み/読込みから応答までの時間計測 */
static U2       u2_s_PowerIc_BetWaitTime;       /* レジスタアクセス間Waitタイマ */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_PowerIcLocalInit(void);
static void     vd_s_PowerIcPollingPon(void);
static void     vd_s_PowerIcFlow(void);
static U1       u1_s_PowerIcTimChk(const U4 u4_a_CNT, const U4 u4_a_JDG);
static void     vd_s_PowerIcOnFlow(void);
static void     vd_s_PowerIcOffFlow(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void            vd_g_PowerIcInit(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    PowerIC 初期化処理                                                                                                */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_PowerIcInit(void)
{
    u4_t_PowerIc_Polling            = (U4)0U;
    u1_s_PowerIc_MUTE_Hook          = (U1)FALSE;
    
    vd_s_PowerIcLocalInit();
}

/*===================================================================================================================================*/
/*  static void     vd_s_PowerIcLocalInit(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    PowerIC 初期化処理                                                                                                */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_PowerIcLocalInit(void)
{
    u4_s_PowerIc_LinkTimer          = (U4)0U;

    u1_s_PowerIc_OnStep_OverAll     = (U1)POWERIC_ONSTEP_OVERALL_1;

    u1_s_PowerIc_OffStep_OverAll    = (U1)POWERIC_OFFSTEP_OVERALL_1;

    u2_s_PowerIc_RegStep            = (U2)0U;
    u2_s_PowerIc_BetWaitTime        = (U2)0xFFFFU;
    u4_s_PowerIc_AckTime            = (U4)0U;

    Mcu_Sys_Pwr_PowerIc_Init();
}

/*===================================================================================================================================*/
/*  void            vd_g_PowerIcMainTask(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    PowerIC メインタスク                                                                                              */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_PowerIcMainTask(void)
{
    /* [Power-IC通常起動処理 レジスタ書込み]開始条件監視用ポーリング */
    vd_s_PowerIcPollingPon();

    /* 通常起動/終了 全体フロー処理 */
    vd_s_PowerIcFlow();
}

/*===================================================================================================================================*/
/*  void            vd_s_PowerIcPollingPon(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    P-ON端子監視                                                                                                      */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_PowerIcPollingPon(void)
{
    U1  u1_t_dio;

    u1_t_dio =   Dio_ReadChannel(POWERIC_PORT_PIC_POFF);

    if((u1_t_dio  ==  (U1)POWERIC_DIO_HIGH) &&
       (u4_t_PowerIc_Polling < (U4)POWERIC_COUNTTIME_FIN)){
        u4_t_PowerIc_Polling++;
    }
    else{
        u4_t_PowerIc_Polling = (U4)0U;
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_PowerIcFlow(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    PowerIC 起動終了処理実行管理                                                                                       */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_PowerIcFlow(void)
{
    U1  u1_t_timechk;

    u1_t_timechk    = u1_s_PowerIcTimChk(u4_t_PowerIc_Polling, (U4)POWERIC_WAIT_PON);

    if(u1_s_PowerIc_MUTE_Hook == (U1)TRUE){
        /* 通常終了処理 */
        vd_s_PowerIcOffFlow();
    }
    else if(u1_t_timechk == (U1)TRUE){
        /* 通常起動処理 */
        vd_s_PowerIcOnFlow();
    }
    else{
        /* 起動/終了処理の実施条件未成立 */
        vd_s_PowerIcLocalInit();
    }
}

/*===================================================================================================================================*/
/*  static U1    u1_s_PowerIcTimChk(const U4 u4_a_CNT, const U4 u4_a_JDG)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    PowerIC タイマ時間経過判定                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_PowerIcTimChk(const U4 u4_a_CNT, const U4 u4_a_JDG)
{
    U1  u1_t_return;
    u1_t_return = (U1)FALSE;

    if(u4_a_CNT >= u4_a_JDG){
        u1_t_return = (U1)TRUE;
    }

    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static void     vd_s_PowerIcOnFlow(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    PowerIC 通常起動                                                                                                  */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_PowerIcOnFlow(void)
{
    static const ST_REG_WRI_REQ st_sp_POWERIC_INISET[POWERIC_WRINUM_INISET] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         3,         0},
        {        3,         3,         0},
        {        6,         2,         0}
    };
    static const ST_REG_WRI_REQ st_sp_POWERIC_AMPON[POWERIC_WRINUM_AMPON] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0}
    };
    static const ST_REG_WRI_REQ st_sp_POWERIC_DIAGACT[POWERIC_WRINUM_DIAGACT] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0}
    };
    static const ST_REG_WRI_REQ st_sp_POWERIC_MUTEOFF[POWERIC_WRINUM_MUTEOFF] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0}
    };
    U1      u1_t_timchk;
    U1      u1_t_sts;        /* 書込み状況 */

    u1_t_timchk     = (U1)FALSE;
    u1_t_sts        = (U1)FALSE;

    /* Ackタイムアウト用カウンタインクリメント */
    if(u4_s_PowerIc_AckTime < (U4)POWERIC_COUNTTIME_FIN){
        u4_s_PowerIc_AckTime++;
    }

    switch (u1_s_PowerIc_OnStep_OverAll) {
        case POWERIC_ONSTEP_OVERALL_1:
            /* ToDo：ポート操作条件に「[P-IC起動状態](3章参照)をSiPに通知しているか？ 」を追加する */
            Dio_WriteChannel((Dio_ChannelType)POWERIC_PORT_P_ON, (Dio_LevelType)STD_HIGH);
            u1_s_PowerIc_OnStep_OverAll = (U1)POWERIC_ONSTEP_OVERALL_2;
            break;

        case POWERIC_ONSTEP_OVERALL_2:
            /* 1ms待機は本caseに到達した時点で満たしていると判断するためwait処理は実施しない */
            /* レジスタ書込み処理 */
            u1_t_sts = Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_POWER, &u2_s_PowerIc_RegStep, (U2)POWERIC_WRINUM_INISET,
                                                (U1)GP_I2C_MA_SLA_4_POWER, st_sp_POWERIC_INISET, &u4_s_PowerIc_AckTime,
                                                st_sp_MCU_SYS_PWR_POWERIC_SETREG_INIT, &u2_s_PowerIc_BetWaitTime);

            if(u1_t_sts == (U1)TRUE){
                /* 全書込み完了 次状態に遷移 */
                u1_s_PowerIc_OnStep_OverAll = (U1)POWERIC_ONSTEP_OVERALL_3;
            }
            break;

        case POWERIC_ONSTEP_OVERALL_3:
            /* レジスタ書込み処理 */
            u1_t_sts = Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_POWER, &u2_s_PowerIc_RegStep, (U2)POWERIC_WRINUM_AMPON,
                                                (U1)GP_I2C_MA_SLA_4_POWER, st_sp_POWERIC_AMPON, &u4_s_PowerIc_AckTime,
                                                st_sp_MCU_SYS_PWR_POWERIC_SETREG_AMP_ON, &u2_s_PowerIc_BetWaitTime);

            if(u1_t_sts == (U1)TRUE){
                /* 全書込み完了 次状態に遷移 */
                u1_s_PowerIc_OnStep_OverAll = (U1)POWERIC_ONSTEP_OVERALL_4;
            }
            break;

        case POWERIC_ONSTEP_OVERALL_4:
            if(u4_s_PowerIc_LinkTimer < (U4)POWERIC_COUNTTIME_FIN){
                u4_s_PowerIc_LinkTimer++;
            }
            u1_t_timchk = u1_s_PowerIcTimChk(u4_s_PowerIc_LinkTimer, (U4)POWERIC_WAIT_60MS);
            if(u1_t_timchk == (U1)TRUE){
                u1_s_PowerIc_OnStep_OverAll = (U1)POWERIC_ONSTEP_OVERALL_5;         /* 次状態に遷移 */
                u4_s_PowerIc_LinkTimer      = (U4)0U;
            }
            break;

        case POWERIC_ONSTEP_OVERALL_5:
            /* レジスタ書込み処理 */
            u1_t_sts = Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_POWER, &u2_s_PowerIc_RegStep, (U2)POWERIC_WRINUM_DIAGACT,
                                                (U1)GP_I2C_MA_SLA_4_POWER, st_sp_POWERIC_DIAGACT, &u4_s_PowerIc_AckTime,
                                                st_sp_MCU_SYS_PWR_POWERIC_SETREG_DIAG_ON, &u2_s_PowerIc_BetWaitTime);

            if(u1_t_sts == (U1)TRUE){
                /* 全書込み完了 次状態に遷移 */
                u1_s_PowerIc_OnStep_OverAll = (U1)POWERIC_ONSTEP_OVERALL_6;
            }
            break;

        case POWERIC_ONSTEP_OVERALL_6:
            /* レジスタ書込み処理 */
            u1_t_sts = Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_POWER, &u2_s_PowerIc_RegStep, (U2)POWERIC_WRINUM_MUTEOFF,
                                                (U1)GP_I2C_MA_SLA_4_POWER, st_sp_POWERIC_MUTEOFF, &u4_s_PowerIc_AckTime,
                                                st_sp_MCU_SYS_PWR_POWERIC_SETREG_MUTE_OFF, &u2_s_PowerIc_BetWaitTime);

            if(u1_t_sts == (U1)TRUE){
                /* 全書込み完了 次状態に遷移 */
                u1_s_PowerIc_OnStep_OverAll = (U1)POWERIC_ONSTEP_OVERALL_FIN;
                /* 初期化完了通知 */
                vd_g_XspiIviSub1PowerDevInitCmpApp((U1)XSPI_IVI_POWER_POWER_INI);
            }
            break;

        case POWERIC_ONSTEP_OVERALL_FIN:
            /* 正常起動時は何もしない */
            break;

        default:
            /* 異常時はフローをはじめからやり直す */
            u1_s_PowerIc_OnStep_OverAll = (U1)POWERIC_ONSTEP_OVERALL_1;
            break;
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_PowerIcOffFlow(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    PowerIC 通常終了                                                                                                  */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_PowerIcOffFlow(void)
{
    static const ST_REG_WRI_REQ st_sp_POWERIC_MUTEON[POWERIC_WRINUM_MUTEON] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},
    };
    static const ST_REG_WRI_REQ st_sp_POWERIC_AMPOFF[POWERIC_WRINUM_AMPOFF] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},
    };
    U1  u1_t_timchk;
    U1  u1_t_v33peri_read;
    U1  u1_t_sts;           /* レジスタ書込み状況 */
    U1  u1_t_regwri;        /* 書込みデータ作成 */

    u1_t_timchk         = (U1)FALSE;
    u1_t_v33peri_read   = (U1)POWERIC_DIO_HIGH;
    u1_t_sts            = (U1)FALSE;
    u1_t_regwri         = (U1)0x00U;

    /* Ackタイムアウト用カウンタインクリメント */
    if(u4_s_PowerIc_AckTime < (U4)POWERIC_COUNTTIME_FIN){
        u4_s_PowerIc_AckTime++;
    }

    switch (u1_s_PowerIc_OffStep_OverAll)
    {
        case POWERIC_OFFSTEP_OVERALL_1:
            if(u4_s_PowerIc_LinkTimer < (U4)POWERIC_COUNTTIME_FIN){
                u4_s_PowerIc_LinkTimer++;
            }
            u1_t_timchk = u1_s_PowerIcTimChk(u4_s_PowerIc_LinkTimer, (U4)POWERIC_OFFWAIT_55MS);
            if(u1_t_timchk == (U1)TRUE){
                u1_s_PowerIc_OffStep_OverAll    = (U1)POWERIC_OFFSTEP_OVERALL_2;    /* 次状態に遷移 */
                u4_s_PowerIc_LinkTimer          = (U4)0U;                           /* タイマクリア */
            }
            break;

        case POWERIC_OFFSTEP_OVERALL_2:
            /* レジスタ読出し処理 */
            u1_t_sts = Mcu_Dev_I2c_Ctrl_RegRead((U1)MCU_I2C_ACK_POWER, &u2_s_PowerIc_RegStep, (U1)GP_I2C_MA_SLA_4_POWER,
                                                    &u4_s_PowerIc_AckTime, st_sp_MCU_SYS_PWR_POWERIC_SETREG_MUTE_RD, &u2_s_PowerIc_BetWaitTime, (U1)MCU_I2C_WAIT_NON);

            if(u1_t_sts == (U1)TRUE){
                /* 読出ししたデータを元に次Stepの書込みデータを作成 */
                u1_t_regwri = st_sp_MCU_SYS_PWR_POWERIC_SETREG_MUTE_RD[1].u1p_pdu[1];   /* 読出しデータ取得 */
                u1_t_regwri = u1_t_regwri & (U1)0xE7U;                                  /* D4=0, D3=0に変更 */
                st_sp_MCU_SYS_PWR_POWERIC_SETREG_MUTE_ON[0].u1p_pdu[2] = u1_t_regwri;   /* 書込みデータ格納 */
                /* 全書込み完了 次状態に遷移 */
                u1_s_PowerIc_OffStep_OverAll    = (U1)POWERIC_OFFSTEP_OVERALL_3;        /* 次状態に遷移 */
            }
            break;

        case POWERIC_OFFSTEP_OVERALL_3:
            /* レジスタ書込み処理 */
            u1_t_sts = Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_POWER, &u2_s_PowerIc_RegStep, (U2)POWERIC_WRINUM_MUTEON,
                                                    (U1)GP_I2C_MA_SLA_4_POWER, st_sp_POWERIC_MUTEON, &u4_s_PowerIc_AckTime,
                                                    st_sp_MCU_SYS_PWR_POWERIC_SETREG_MUTE_ON, &u2_s_PowerIc_BetWaitTime);

            if(u1_t_sts == (U1)TRUE){
                /* 全書込み完了 次状態に遷移 */
                u1_s_PowerIc_OffStep_OverAll    = (U1)POWERIC_OFFSTEP_OVERALL_4;
            }
            break;
        
        case POWERIC_OFFSTEP_OVERALL_4:
            if(u4_s_PowerIc_LinkTimer < (U4)POWERIC_COUNTTIME_FIN){
                u4_s_PowerIc_LinkTimer++;
            }
            u1_t_timchk = u1_s_PowerIcTimChk(u4_s_PowerIc_LinkTimer, (U4)POWERIC_OFFWAIT_100MS);
            if(u1_t_timchk == (U1)TRUE){
                u1_s_PowerIc_OffStep_OverAll    = (U1)POWERIC_OFFSTEP_OVERALL_5;    /* 次状態に遷移 */
                u4_s_PowerIc_LinkTimer          = (U4)0U;                           /* タイマクリア */
            }
            break;

        case POWERIC_OFFSTEP_OVERALL_5:
            /* レジスタ読出し処理 */
            u1_t_sts = Mcu_Dev_I2c_Ctrl_RegRead((U1)MCU_I2C_ACK_POWER, &u2_s_PowerIc_RegStep, (U1)GP_I2C_MA_SLA_4_POWER,
                                                    &u4_s_PowerIc_AckTime, st_sp_MCU_SYS_PWR_POWERIC_SETREG_AMP_RD, &u2_s_PowerIc_BetWaitTime, (U1)MCU_I2C_WAIT_NON);

            if(u1_t_sts == (U1)TRUE){
                /* 読出ししたデータを元に次Stepの書込みデータを作成 */
                u1_t_regwri = st_sp_MCU_SYS_PWR_POWERIC_SETREG_AMP_RD[1].u1p_pdu[1];    /* 読出しデータ取得 */
                u1_t_regwri = u1_t_regwri & (U1)0xFEU;                                  /* D0=0に変更 */
                st_sp_MCU_SYS_PWR_POWERIC_SETREG_AMP_OFF[0].u1p_pdu[2] = u1_t_regwri;   /* 書込みデータ格納 */
                /* 全書込み完了 次状態に遷移 */
                u1_s_PowerIc_OffStep_OverAll    = (U1)POWERIC_OFFSTEP_OVERALL_6;        /* 次状態に遷移 */
            }
            break;

        case POWERIC_OFFSTEP_OVERALL_6:
            /* レジスタ書込み処理 */
            u1_t_sts = Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_POWER, &u2_s_PowerIc_RegStep, (U2)POWERIC_WRINUM_AMPOFF,
                                                    (U1)GP_I2C_MA_SLA_4_POWER, st_sp_POWERIC_AMPOFF, &u4_s_PowerIc_AckTime,
                                                    st_sp_MCU_SYS_PWR_POWERIC_SETREG_AMP_OFF, &u2_s_PowerIc_BetWaitTime);

            if(u1_t_sts == (U1)TRUE){
                /* 全書込み完了 次状態に遷移 */
                u1_s_PowerIc_OffStep_OverAll    = (U1)POWERIC_OFFSTEP_OVERALL_7;        /* 次状態に遷移 */
            }
            break;

        case POWERIC_OFFSTEP_OVERALL_7:
            if(u4_s_PowerIc_LinkTimer < (U4)POWERIC_COUNTTIME_FIN){
                u4_s_PowerIc_LinkTimer++;
            }
            u1_t_timchk = u1_s_PowerIcTimChk(u4_s_PowerIc_LinkTimer, (U4)POWERIC_OFFWAIT_5MS);
            if(u1_t_timchk == (U1)TRUE){
                Dio_WriteChannel(POWERIC_PORT_P_ON , (Dio_LevelType)POWERIC_DIO_LOW);   /* スタンバイ */
                u1_s_PowerIc_OffStep_OverAll    = (U1)POWERIC_OFFSTEP_OVERALL_8;        /* 次状態に遷移 */
                u4_s_PowerIc_LinkTimer          = (U4)0U;                               /* タイマクリア */
            }
            break;

        case POWERIC_OFFSTEP_OVERALL_8:
/* VM3の終了処理順がアプリ電源OFF→SYS電源OFFとなっており、アプリOFF処理中にV33PERIONがLoになることがない */
/* 暫定措置としてアプリでのPIC_POFF=Low処理をスキップし、終了処理完了とする */
/* PIC_POFFはSYS電源OFF処理中にてLowに変更している */
#if 0   
            if(u4_s_PowerIc_LinkTimer < (U4)POWERIC_COUNTTIME_FIN){
                u4_s_PowerIc_LinkTimer++;
            }

            u1_t_v33peri_read = Dio_ReadChannel(POWERIC_PORT_V33_PERI); /* V33-PERI-ON読み出し */
            if(u1_t_v33peri_read == (U1)POWERIC_DIO_HIGH){
                u4_s_PowerIc_LinkTimer = (U4)0U;                        /* V33-PERI-ON=Highの場合次処理への遷移を抑制する */
            }

            u1_t_timchk = u1_s_PowerIcTimChk(u4_s_PowerIc_LinkTimer, (U4)POWERIC_OFFWAIT_100MS);
            if(u1_t_timchk == (U1)TRUE){
                Dio_WriteChannel(POWERIC_PORT_PIC_POFF, (Dio_LevelType)POWERIC_DIO_LOW);    /* P-IC電源制限 */
                u1_s_PowerIc_OffStep_OverAll    = (U1)POWERIC_OFFSTEP_OVERALL_FIN;          /* 次状態に遷移 */
                u4_s_PowerIc_LinkTimer          = (U4)0U;                                   /* タイマクリア */
                u1_s_PowerIc_MUTE_Hook          = (U1)FALSE;                                /* 通常終了処理起動フックのクリア */
            }
            break;
#else
            u1_s_PowerIc_OffStep_OverAll    = (U1)POWERIC_OFFSTEP_OVERALL_FIN;
            break;
#endif
        case POWERIC_OFFSTEP_OVERALL_FIN:
            /* do nothing */
            break;

        default:
            /* 異常時はフローをはじめからやり直す */
            u1_s_PowerIc_OffStep_OverAll    = (U1)POWERIC_OFFSTEP_OVERALL_1;
            break;
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_PowerIcMuteHook(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    HexagonDSP MUTE設定完了通知 受信                                                                                  */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_PowerIcMuteHook(void)
{
    u1_s_PowerIc_MUTE_Hook  = (U1)TRUE;
}