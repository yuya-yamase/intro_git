/* メインタスクコードに移管するまでの仮置き */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gvif3rx.h"
#include "Dio.h"
#include "Dio_Symbols.h"
#include "Mcu_I2c_Ctrl_private.h"
#include "Mcu_Sys_Pwr_Gvif3Rx.h"
#include "x_spi_ivi_sub1_power.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Port */
#define MCU_PORT_GVIF_CAN_RST           (DIO_ID_PORT10_CH6)     /* /GVIF-RX(CAM)-RST */

/* カウンタ最大値 */
#define MCU_SYS_COUNTTIME_FIN           (0xFFFFFFFFU)

/* GVIF受信制御仕様 */
#define MCU_WRINUM_GVIF3RX_INISET       (63U)   /* 6-2. 初期設定処理 初期設定 (7-1. 初期設定値 参照) レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3RX_TYPSET       (9U)    /* 6ｰ3. カメラシステム種別による設定 レジスタ書込み回数 */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* デバイス起動用カウンタ */
static uint32   Mcu_Polling_GvifRxRst;

/* GVIF受信制御仕様 */
       uint8    Mcu_OnStep_GVIF3RX_OVRALL;      /* 6-1. 全体フロー 仮置き中はexternするためstaticなし */
static uint32   Mcu_OnStep_GVIF3RX_AckTime;     /* GVIF3RX 書込み/読込みから応答までの時間計測 */

static uint16   Mcu_RegStep_GVIF3RX;            /* GVIF3RX レジスタ書込み位置指定 */

/* レジスタアクセス */
static uint16   Mcu_RegSet_BetWaitTime_Stub;    /* レジスタアクセス間Waitタイマ スタブ */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     Mcu_Dev_Pwron_GvifRx_Polling_Rst( void );
static void     Mcu_Dev_Pwron_GvifRx_RegSetting( void );
static uint8    Mcu_Dev_Pwron_TimChk( uint32 mcu_tim_cnt, const uint32 mcu_tim_fim);
static void     Mcu_Dev_Pwron_GvifRx_SetReg( void );

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*****************************************************************************
  Function      : gvif3rx_Init
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void    gvif3rx_Init( void )
{
    Mcu_Polling_GvifRxRst       = (uint32)0U;

    Mcu_OnStep_GVIF3RX_OVRALL   = (uint8)MCU_STEP_GVIF3RX_OVERALL_1;
    Mcu_OnStep_GVIF3RX_AckTime  = (uint32)0U;
    Mcu_RegStep_GVIF3RX         = (uint16)0U;

    Mcu_RegSet_BetWaitTime_Stub = (uint16)0xFFFFU;
}

/*****************************************************************************
  Function      : gvif3rx_main
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void    gvif3rx_main( void )
{
    /* [6-1~6-4. 全体フロー]シートの初期化処理 */
    /* 開始条件監視用ポーリング */
    Mcu_Dev_Pwron_GvifRx_Polling_Rst();

    /* 全体フロー処理 */
    Mcu_Dev_Pwron_GvifRx_RegSetting();
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifRx_Polling_Rst
  Description   : 
  param[in/out] : 
  return        : -
  Note          : /GVIF-RX(CAM)-RST=Hi 監視
*****************************************************************************/
static void     Mcu_Dev_Pwron_GvifRx_Polling_Rst( void )
{
    uint8   mcu_dio_ret;

    mcu_dio_ret =   Dio_ReadChannel(MCU_PORT_GVIF_CAN_RST);

    if(mcu_dio_ret  ==  (uint8)STD_LOW){
        Mcu_Polling_GvifRxRst       = (uint32)0U;
        Mcu_OnStep_GVIF3RX_OVRALL   = (uint8)MCU_STEP_GVIF3RX_OVERALL_1;
        Mcu_OnStep_GVIF3RX_AckTime  = (uint32)0U;
        Mcu_RegStep_GVIF3RX         = (uint16)0U;
    }
    else if((mcu_dio_ret  ==  (uint8)STD_HIGH) &&
        (Mcu_Polling_GvifRxRst < (uint32)MCU_SYS_COUNTTIME_FIN)){
        Mcu_Polling_GvifRxRst++;
    }
    else{
        /* do nothing */
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifRx_RegSetting
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 6-2. 初期設定処理
*****************************************************************************/
static void     Mcu_Dev_Pwron_GvifRx_RegSetting( void )
{
    static const uint32 MCU_PWRON_TIME_GVIFRX  =   (uint16)(15U / MCU_GVIFRX_TASK_TIME);    /* min:15ms */

    uint8   mcu_time_chk;

    mcu_time_chk    =   Mcu_Dev_Pwron_TimChk(Mcu_Polling_GvifRxRst, MCU_PWRON_TIME_GVIFRX);

    if(mcu_time_chk ==  (uint8)TRUE){
        Mcu_Dev_Pwron_GvifRx_SetReg();
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
  Function      : Mcu_Dev_Pwron_GvifRx_SetReg
  Description   : 
  param[in/out] : 
  return        : -
  Note          : GVIF受信機初期化処理 レジスタ設定
                  シス検暫定対応あり
*****************************************************************************/
static void     Mcu_Dev_Pwron_GvifRx_SetReg( void )
{
    /* 6-2. 初期設定処理 初期設定 (7-1. 初期設定値 参照) */
    static const ST_REG_WRI_REQ GVIFRX_INISET[MCU_WRINUM_GVIF3RX_INISET] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},
        {        1,         2,         0},
        {        3,         2,         0},
        {        5,         2,         0},
        {        7,         2,         0},
        {        9,         2,         0},
        {       11,         2,         0},
        {       13,         2,         0},
        {       15,         1,         0},
        {       16,         2,         0},
        {       18,         2,         0},
        {       20,         2,         0},
        {       22,         2,         0},
        {       24,         1,         0},
        {       25,         2,         0},
        {       27,         2,         0},
        {       29,         2,         0},
        {       31,         2,         0},
        {       33,         2,         0},
        {       35,         1,         0},
        {       36,         1,         0},
        {       37,         1,         0},
        {       38,         1,         0},
        {       39,         1,         0},
        {       40,         2,         0},
        {       42,         1,         0},
        {       43,         1,         0},
        {       44,         1,         0},
        {       45,         2,         0},
        {       47,         2,         0},
        {       49,         2,         0},
        {       51,         2,         0},
        {       53,         2,         0},
        {       55,         2,         0},
        {       57,         2,         0},
        {       59,         2,         0},
        {       61,         2,         0},
        {       63,         1,         0},
        {       64,         1,         0},
        {       65,         2,         0},
        {       67,         2,         0},
        {       69,         2,         0},
        {       71,         2,         0},
        {       73,         2,         0},
        {       75,         1,         0},
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
        {      102,         1,         0},
        {      103,         1,         0},
        {      104,         2,         0},
        {      106,         1,         0},
        {      107,         1,         0}
    };
    /* 6ｰ3. カメラシステム種別による設定 6ｰ3-2-1. カメラシステム種別設定(カメラなし) */
    static const ST_REG_WRI_REQ GVIFRX_DOMCONSET[MCU_WRINUM_GVIF3RX_TYPSET] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},
        {        1,         2,         0},
        {        3,         1,         0},
        {        4,         1,         0},
        {        5,         2,         0},
        {        7,         1,         0},
        {        8,         2,         0},
        {       10,         1,         0},
        {       11,         2,         0},
        {       13,         1,         0}
    };
    uint8   mcu_sts;        /* 書込み状況 */

    mcu_sts         = (uint8)FALSE;

    /* Ackタイムアウト用カウンタインクリメント */
    if(Mcu_OnStep_GVIF3RX_AckTime < (uint32)MCU_SYS_COUNTTIME_FIN){
        Mcu_OnStep_GVIF3RX_AckTime++;
    }

    switch (Mcu_OnStep_GVIF3RX_OVRALL)
    {
    case MCU_STEP_GVIF3RX_OVERALL_1:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_GVIF_RX, &Mcu_RegStep_GVIF3RX, (uint16)MCU_WRINUM_GVIF3RX_INISET,
                                                (uint8)GP_I2C_MA_SLA_2_GVIF_RX, GVIFRX_INISET, &Mcu_OnStep_GVIF3RX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIF3RX_REG_INIT, &Mcu_RegSet_BetWaitTime_Stub);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3RX_OVRALL = (uint8)MCU_STEP_GVIF3RX_OVERALL_2;
        }
        break;
    
    case MCU_STEP_GVIF3RX_OVERALL_2:
        /* レジスタ書込み処理 */
        /* ToDo：バックアップ処理がないためカメラなし固定でレジスタ設定する */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_GVIF_RX, &Mcu_RegStep_GVIF3RX, (uint16)MCU_WRINUM_GVIF3RX_TYPSET,
                                                (uint8)GP_I2C_MA_SLA_2_GVIF_RX, GVIFRX_DOMCONSET, &Mcu_OnStep_GVIF3RX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIF3RX_REG_CAMNON, &Mcu_RegSet_BetWaitTime_Stub);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3RX_OVRALL = (uint8)MCU_STEP_GVIF3RX_OVERALL_FIN;
            /* 初期化完了通知 */
            vd_g_XspiIviSub1PowerDevInitCmpApp((U1)XSPI_IVI_POWER_GVIFRECV_INI);
        }
        break;
    
    case MCU_STEP_GVIF3RX_OVERALL_FIN:
        break;
    
    default:
        /* 異常時はフローをはじめからやり直す */
        Mcu_OnStep_GVIF3RX_OVRALL   = MCU_STEP_GVIF3RX_OVERALL_1;
        break;
    }
}