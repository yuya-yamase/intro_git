/* 0.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO TECHNO Corporation                                                                                               */
/*===================================================================================================================================*/
/*  Transmission and reception processing of subframe 4 in XSPI communication.                                                       */
/*  Handled data: CAN Data/Repro/LCAN Data                                                                                           */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_IVI_SUB1_POWER_C_MAJOR                   (0)
#define XSPI_IVI_SUB1_POWER_C_MINOR                   (1)
#define XSPI_IVI_SUB1_POWER_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include    "x_spi_ivi_sub1_private.h"
#include    "x_spi_ivi_sub1_power.h"
#include    "Dio.h"
#include    "Dio_Symbols.h"
#include    "Iohw_adc.h"
#include    "PwrCtl.h"
#include    "BootLogCtl.h"
#include    "veh_opemd.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((XSPI_IVI_SUB1_POWER_C_MAJOR != XSPI_IVI_SUB1_POWER_H_MAJOR) || \
     (XSPI_IVI_SUB1_POWER_C_MINOR != XSPI_IVI_SUB1_POWER_H_MINOR) || \
     (XSPI_IVI_SUB1_POWER_C_PATCH != XSPI_IVI_SUB1_POWER_H_PATCH))
#error "x_spi_ivi_sub1_power.c and x_spi_ivi_sub1.h : source and header files are inconsistent!"
#endif
#if (XSPI_IVI_SUB1_POWER_C_MAJOR != XSPI_IVI_SUB1_PRIVATE_H_MAJOR)
#error "x_spi_ivi_sub1_power.c and x_spi_ivi_sub1_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define    XSPI_IVI_POWER_ID                    (0x21U)
#define    XSPI_IVI_POWER_STATE_SEND            (0x01U)
#define    XSPI_IVI_POWER_STATE_REC             (0x02U)
#define    XSPI_IVI_POWER_STATE_TRANS_REC       (0x03U)
#define    XSPI_IVI_POWER_STATE_TRANS_SEND      (0x04U)
#define    XSPI_IVI_POWER_BMONIVOL_SEND         (0x05U)
#define    XSPI_IVI_POWER_OPESTS_REC            (0x21U)
#define    XSPI_IVI_POWER_OPESTS_SEND           (0x22U)
#define    XSPI_IVI_POWER_STRMODE_REC           (0x43U)
#define    XSPI_IVI_POWER_STRMODE_SEND          (0x44U)
#define    XSPI_IVI_POWER_BOOTLOG_REQ           (0x61U)
#define    XSPI_IVI_POWER_BOOTLOG_RES           (0x62U)

#define    XSPI_IVI_POWER_TASK                  (2000U / XSPI_IVI_TASK_TIME)
#define    XSPI_IVI_POWER_SIZE                  (7U)
#define    XSPI_IVI_POWER_STATE_SIZE            (7U)
#define    XSPI_IVI_POWER_TRANS_SIZE            (6U)
#define    XSPI_IVI_POWER_BMONI_SIZE            (7U)
#define    XSPI_IVI_POWER_OPESTS_SIZE           (8U)
#define    XSPI_IVI_POWER_STRMODE_SIZE          (2U)

#define    XSPI_IVI_POWER_BOOTLOG_SIZE          (36U)

#define    XSPI_IVI_POWER_STATE_NUM             (7U)    /* 基本ステート 状態総数 */
#define    XSPI_IVI_POWER_STATE_OFF             (0U)    /* OFF */
#define    XSPI_IVI_POWER_STATE_PARK            (1U)    /* 駐車中 */
#define    XSPI_IVI_POWER_STATE_RIDEON          (2U)    /* 乗車中 */
#define    XSPI_IVI_POWER_STATE_POWERON         (3U)    /* PowerON通常  */
#define    XSPI_IVI_POWER_STATE_POWERON_STOP    (4U)    /* PowerON緊急停止 */
#define    XSPI_IVI_POWER_STATE_PARK_HI_PRE     (5U)    /* 駐車中高圧起動  */
#define    XSPI_IVI_POWER_STATE_PARK_TEMP_CON   (6U)    /* 駐車中高圧・温調起動  */
#define    XSPI_IVI_POWER_STATE_UNKNOWN         (0xFFU) /* 未確定  */

#define    XSPI_IVI_POWER_DC_UNKNOWN            (0x00U) /* 不定 */
#define    XSPI_IVI_POWER_DC_NONE               (0x01U) /* 途絶なし */
#define    XSPI_IVI_POWER_DC_PRESENT            (0x02U) /* 途絶あり */

#define    XSPI_IVI_POWER_VEHOPE_PARK           (0x0008U)   /* Veopemd:駐車中 */
#define    XSPI_IVI_POWER_VEHOPE_RIDEON         (0x006AU)   /* Veopemd:乗車中 */
#define    XSPI_IVI_POWER_VEHOPE_POWERON        (0x007EU)   /* Veopemd:PowerON通常 */
#define    XSPI_IVI_POWER_VEHOPE_POWERON_STOP   (0x007AU)   /* Veopemd:PowerON緊急停止 */
#define    XSPI_IVI_POWER_VEHOPE_PARK_HI_PRE    (0x0028U)   /* Veopemd:駐車中高圧起動 */
#define    XSPI_IVI_POWER_VEHOPE_PARK_TEMP_CON  (0x0068U)   /* Veopemd:駐車中高圧・温調起動 */

/*Appからのデバイス初期化完了マクロ*/
#define    XSPI_IVI_POWER_DEV_INI_COMP_PARK     (0x000AU)   /*Appからの初期化監視対象(駐車中)*/
#define    XSPI_IVI_POWER_DEV_INI_COMP_APPOFF   (0x001FU)   /*Appからの初期化監視対象(見た目オフ)*/
#define    XSPI_IVI_POWER_DEV_INI_COMP_APPON    (0x001FU)   /*Appからの初期化監視対象(見た目オン)*/
#define    XSPI_IVI_POWER_DEV_INI_COMP_EDS      (0x0008U)   /*Appからの初期化監視対象(縮退走行)*/
#define    XSPI_IVI_POWER_DEV_INI_COMP_EIZO     (0x0001U)
#define    XSPI_IVI_POWER_DEV_INI_COMP_GVIFREC  (0x0002U)
#define    XSPI_IVI_POWER_DEV_INI_COMP_GVIFSEND (0x0004U)
#define    XSPI_IVI_POWER_DEV_INI_COMP_GYRO     (0x0008U)
#define    XSPI_IVI_POWER_DEV_INI_COMP_POWER    (0x0010U)
/*電源状態ごとのデバイス初期化完了マクロ*/
#ifdef ANTCTL_XM_SHDN
#define    XSPI_IVI_POWER_DEV_INI_PARK          (0x008A0FFFU) /*デバイス初期化監視対象(駐車中)*/
#define    XSPI_IVI_POWER_DEV_INI_APPOFF        (0x00AA3FFFU) /*デバイス初期化監視対象(見た目オフ)*/
#define    XSPI_IVI_POWER_DEV_INI_APPON         (0x00FFFFFFU) /*デバイス初期化監視対象(見た目オン)*/
#define    XSPI_IVI_POWER_DEV_INI_EDS           (0x00880FFFU) /*デバイス初期化監視対象(縮退走行)*/
#else
#define    XSPI_IVI_POWER_DEV_INI_PARK          (0x004A0FFFU) /*デバイス初期化監視対象(駐車中)*/
#define    XSPI_IVI_POWER_DEV_INI_APPOFF        (0x006A3FFFU) /*デバイス初期化監視対象(見た目オフ)*/
#define    XSPI_IVI_POWER_DEV_INI_APPON         (0x007FFFFFU) /*デバイス初期化監視対象(見た目オン)*/
#define    XSPI_IVI_POWER_DEV_INI_EDS           (0x00480FFFU) /*デバイス初期化監視対象(縮退走行)*/
#endif

/*GPS-RST端子 Lo→Hiからのカウント*/
#define    XSPI_IVI_POWER_GPSRST_INI_TASK       (400U / XSPI_IVI_TASK_TIME)

/*B-MON電圧端子のポーリング周期*/
#define    XSPI_IVI_POWER_BMONVOL_TASK          (100U / XSPI_IVI_TASK_TIME)

/*デバイス初期化確認Pin*/
/* SYS電源制御 Port設定 */
#define     MCU_PORT_BU_DD_MODE                 (0U)         /* (DIO_ID_APORT0_CH12) */
#define     MCU_PORT_BOOST_DCDC                 (1U)         /* (DIO_ID_PORT10_CH4)  */
#define     MCU_PORT_BOOST_ASIL_DCDC            (2U)         /* (DIO_ID_APORT0_CH15) */
#define     MCU_PORT_V33_PERI                   (3U)         /* (DIO_ID_PORT10_CH2)  */
#define     MCU_PORT_V33_ASIL                   (4U)         /* (DIO_ID_APORT0_CH13) */
#define     MCU_PORT_V18                        (5U)         /* (DIO_ID_APORT1_CH0)  */
#define     MCU_PORT_V18_ASIL                   (6U)         /* (DIO_ID_APORT0_CH9)  */
#define     MCU_PORT_AUDIO                      (7U)         /* (DIO_ID_APORT5_CH0)  */
#define     MCU_PORT_V11_ASIL                   (8U)        /* (DIO_ID_APORT0_CH11) */
#define     MCU_PORT_EIZO                       (9U)        /* (DIO_ID_PORT6_CH11)  */
/* 非冗長電源制御 Port設定 */
#define     MCU_PORT_MBPWR                      (10U)        /* (DIO_ID_PORT22_CH1)  */
#define     MCU_PORT_GVIF_TX_MBWK               (11U)        /* (DIO_ID_PORT20_CH9)  */
#define     MCU_PORT_DISP                       (12U)        /* (DIO_ID_PORT22_CH2)  */
#define     MCU_PORT_GVIF_TX_DSPWK              (13U)        /* (DIO_ID_PORT2_CH0)   */
#define     MCU_PORT_HUB_PWRON                  (14U)        /* (DIO_ID_PORT4_CH14)  */
#define     MCU_PORT_HUB_WK                     (15U)        /* (DIO_ID_PORT4_CH0)   */
/* デバイスON/OFF制御用 Port設定 */
#define     MCU_PORT_USB_LED_ON                 (16U)        /* (DIO_ID_APORT0_CH10) */
#define     MCU_PORT_MIC_ON                     (17U)        /* (DIO_ID_PORT11_CH13) */
#define     MCU_PORT_AMFM_ANT_ON                (18U)        /* (DIO_ID_PORT4_CH8)   */
#define     MCU_PORT_GPS_ANT_ON                 (19U)        /* (DIO_ID_APORT4_CH2)  */
#ifdef ANTCTL_DAB
#define     MCU_PORT_DAB_ANT_ON                 (20U)        /* (DIO_ID_PORT11_CH4)  */
#endif
#ifdef ANTCTL_DTV
#define     MCU_PORT_DTV_ANT_ON                 (20U)        /* (DIO_ID_PORT11_CH4) */
#endif
#ifdef ANTCTL_XM_SHDN
#define     MCU_PORT_XM_SHDN                    (20U)        /* (DIO_ID_PORT11_CH4)  */
#endif
#define     MCU_PORT_MOST_WAKE_ON               (21U)        /* (DIO_ID_PORT24_CH11) */
#ifdef ANTCTL_XM_SHDN
#define     MCU_PORT_XM_ON                      (22U)        /* (DIO_ID_APORT4_CH10) */
#define     MCU_PORT_GPS_RST                    (23U)        /* (DIO_ID_APORT4_CH8)  */
#define     MCU_PORT_NUM                        (24U)
#else
#define     MCU_PORT_GPS_RST                    (22U)        /* (DIO_ID_APORT4_CH8)  */
#define     MCU_PORT_NUM                        (23U)
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*電源ステータス用*/
typedef struct{
    U1                          u1_basic_state;
    U1                          u1_special_state;
    U1                          u1_ota_state;
    U1                          u1_appearance_state;
}ST_XSPI_IVI_POWER_STATE;

/*状態移行指示用*/
typedef struct{
    U1                          u1_count;
    U1                          u1_basic_state;
    U1                          u1_special_state;
    U1                          u1_ota_state;
    U1                          u1_appearance_state;
}ST_XSPI_IVI_POWER_STATE_TRANS;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*電源ステータス格納*/
static U1 u1_s_xspi_ivi_power_state[XSPI_IVI_POWER_01_BUFSIZ];
static U1 u1_s_xspi_ivi_power_state_pre[XSPI_IVI_POWER_01_BUFSIZ];
/*状態移行格納*/
static ST_XSPI_IVI_POWER_STATE_TRANS st_s_xspi_ivi_state_trans; 

/*SPI通信許可状態*/
static U1 u1_s_xspi_ivi_power_start_flg;
/*状態移行指示有無*/
static U1 u1_s_xspi_ivi_power_state_trans_flg;
/*デバイス初期化完了ステータス*/
static U4 u4_s_xspi_ivi_power_device_init_fin_sts;
/*アプリからのデバイス初期化状態格納*/
static U2 u2_s_xspi_ivi_power_device_init_app;
static U1 u1_s_xspi_ivi_power_gpsrst_sts_pre;
static U1 u1_s_xspi_ivi_power_gpsrst_init_fin_flg;
static U1 u1_s_xspi_ivi_power_gpsrst_sts_chk;

/*Bモニ電圧取得値*/
static U2 u2_s_xspi_ivi_power_bmonivol1_data;
static U2 u2_s_xspi_ivi_power_bmonivol2_data;
static U2 u2_s_xspi_ivi_power_bmonivol3_data;
static U1 u1_s_xspi_ivi_power_bmoni_1stsend_flg;

/*電源状態でのデバイス初期化確認*/
static U4 u4_sp_xspi_ivi_power_dev_init[POWER_MODE_STATE_NUM] = {
    XSPI_IVI_POWER_DEV_INI_PARK,
    XSPI_IVI_POWER_DEV_INI_APPOFF,
    XSPI_IVI_POWER_DEV_INI_APPON,
    XSPI_IVI_POWER_DEV_INI_EDS
};

/*電源状態でのAPPからのデバイス初期化確認*/
static U2 u2_sp_xspi_ivi_power_dev_app_init[POWER_MODE_STATE_NUM] = {
    XSPI_IVI_POWER_DEV_INI_COMP_PARK,
    XSPI_IVI_POWER_DEV_INI_COMP_APPOFF,
    XSPI_IVI_POWER_DEV_INI_COMP_APPON,
    XSPI_IVI_POWER_DEV_INI_COMP_EDS
};

/*デバイス初期化確認Port配列*/
static U2 Mcu_Dio_PortId[MCU_PORT_NUM] = {
    /* SYS電源制御 Port設定 */
        DIO_ID_APORT0_CH12,
        DIO_ID_PORT10_CH4,
        DIO_ID_APORT0_CH15,
        /*DIO_ID_PORT2_CH6,*/ /*Readのみのため初期化確認対象外*/
        /*DIO_ID_PORT21_CH3,*/ /*Readのみのため初期化確認対象外*/
        DIO_ID_PORT10_CH2,
        DIO_ID_APORT0_CH13,
        DIO_ID_APORT1_CH0,
        DIO_ID_APORT0_CH9,
        DIO_ID_APORT5_CH0,
        DIO_ID_APORT0_CH11,
        DIO_ID_PORT6_CH11,
    /* 非冗長電源制御 Port設定 */
        /*DIO_ID_PORT0_CH2,*/  /*BOOT端子のため不要*/
        DIO_ID_PORT22_CH1,
        DIO_ID_PORT20_CH9,
        DIO_ID_PORT22_CH2,
        DIO_ID_PORT2_CH0,
        DIO_ID_PORT4_CH14,
        DIO_ID_PORT4_CH0,
    /* デバイスON/OFF制御用 Port設定 */
        DIO_ID_APORT0_CH10,
        /*DIO_ID_PORT3_CH3,*/ /*アプリから初期化完了通知受け取るためPINでの制御はしない*/
        /*DIO_ID_PORT2_CH2,*/ /*Writeされることがないためデバイス初期化確認対象外*/
        /*DIO_ID_PORT10_CH6,*/ /*アプリから初期化完了通知受け取るためPINでの制御はしない*/
        /*DIO_ID_PORT17_CH4,*/ /*アプリから初期化完了通知受け取るためPINでの制御はしない*/
        DIO_ID_PORT11_CH13,
        DIO_ID_PORT4_CH8,
        DIO_ID_APORT4_CH2,
#ifdef ANTCTL_DAB
        DIO_ID_PORT11_CH4,
#endif
#ifdef ANTCTL_DTV
        DIO_ID_PORT11_CH4,
#endif
#ifdef ANTCTL_XM_SHDN
        DIO_ID_PORT11_CH4,
#endif
        /*DIO_ID_PORT20_CH8,*/ /*制御仕様からPINをHIGHに設定することがないため対象外*/
        DIO_ID_PORT24_CH11,
        /*DIO_ID_PORT11_CH7,*/ /*アプリから初期化完了通知受け取るためPINでの制御はしない*/
        /*DIO_ID_PORT11_CH6,*/ /*アプリから初期化完了通知受け取るためPINでの制御はしない*/
#ifdef ANTCTL_XM_SHDN
        DIO_ID_APORT4_CH10,
#endif
        /*DIO_ID_PORT8_CH7,*/  /*アプリから初期化完了通知受け取るためPINでの制御はしない*/
        DIO_ID_APORT4_CH8
        /*DIO_ID_PORT6_CH3,*/ /*Readのみのため初期化確認対象外*/
        /*DIO_ID_PORT10_CH11,*/ /*Readのみのため初期化確認対象外*/
        /*DIO_ID_APORT4_CH5*/ /*GPS_RST端子にてGNSSの初期化チェック実施可能のため対象外*/
        /*DIO_ID_PORT0_CH4*/  /*Readのみのため初期化確認対象外*/
};
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void            vd_s_XspiIviSub1_PowerStateTransRec(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_data_size);
static void            vd_s_XspiIviSub1PowerOperationStsRec(const U1 * u1_ap_XSPI_ADD);
static void            vd_s_XspiIviSub1PowerOperationStsSend(const U1 u1_a_DATA);
static void            vd_s_XspiIviSub1PowerSTRmodeRec(const U1 * u1_ap_XSPI_ADD);
static void            vd_s_XspiIviSub1PowerSTRmodeSend(const U1 u1_a_DATA);
static U1              u1_s_XspiIviSub1PowerDataEventJdg(const U1* u1_ap_DATA,const U1* u1_ap_DATA_PRE,const U1 u1_a_SIZE);
static void            vd_s_XspiIviSub1PowerDataToQueue(const U2 u2_a_size,const U1* u1_ap_XSPI_ADD);
static U1              u1_s_XspiIviSub1PowerDevInitCompChk(void);
/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1POWERInit(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    初期化処理                                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1PowerInit(void)
{
    u1_s_xspi_ivi_power_start_flg = (U1)FALSE;
    u1_s_xspi_ivi_power_state_trans_flg = (U1)FALSE;

    /* 01h PowerState */
    u1_s_xspi_ivi_power_state[XSPI_IVI_POWER_01_BYTE2]      = (U1)XSPI_IVI_POWER_STATE_PARK;    /* 基本ステート */
    u1_s_xspi_ivi_power_state[XSPI_IVI_POWER_01_BYTE3]      = (U1)0x00U;                        /* 特殊ステート */
    u1_s_xspi_ivi_power_state[XSPI_IVI_POWER_01_BYTE4]      = (U1)0x00U;                        /* OTAステート */
    u1_s_xspi_ivi_power_state[XSPI_IVI_POWER_01_BYTE5]      = (U1)0x01U;                        /* 見た目ON/OFF */
    u1_s_xspi_ivi_power_state[XSPI_IVI_POWER_01_BYTE6]      = (U1)0x00U;                        /* 車両電源(特殊)ステート遷移中フラグ */
    u1_s_xspi_ivi_power_state[XSPI_IVI_POWER_01_BYTE7]      = (U1)0x00U;                        /* 途絶状態 */
    u1_s_xspi_ivi_power_state_pre[XSPI_IVI_POWER_01_BYTE2]  = (U1)XSPI_IVI_POWER_STATE_PARK;
    u1_s_xspi_ivi_power_state_pre[XSPI_IVI_POWER_01_BYTE3]  = (U1)0x00U;
    u1_s_xspi_ivi_power_state_pre[XSPI_IVI_POWER_01_BYTE4]  = (U1)0x00U;
    u1_s_xspi_ivi_power_state_pre[XSPI_IVI_POWER_01_BYTE5]  = (U1)0x01U;
    u1_s_xspi_ivi_power_state_pre[XSPI_IVI_POWER_01_BYTE6]  = (U1)0x00U;
    u1_s_xspi_ivi_power_state_pre[XSPI_IVI_POWER_01_BYTE7]  = (U1)0x00U;

    st_s_xspi_ivi_state_trans.u1_count = (U1)U1_MAX;
    st_s_xspi_ivi_state_trans.u1_basic_state = (U1)U1_MAX;
    st_s_xspi_ivi_state_trans.u1_special_state = (U1)U1_MAX;
    st_s_xspi_ivi_state_trans.u1_ota_state = (U1)U1_MAX;
    st_s_xspi_ivi_state_trans.u1_appearance_state = (U1)U1_MAX;

    u4_s_xspi_ivi_power_device_init_fin_sts = (U4)0U;
    u2_s_xspi_ivi_power_device_init_app = (U2)0U;
    u1_s_xspi_ivi_power_gpsrst_sts_pre = (U1)STD_LOW;
    u1_s_xspi_ivi_power_gpsrst_init_fin_flg = (U1)FALSE;
    u1_s_xspi_ivi_power_gpsrst_sts_chk = (U1)FALSE;

    u2_s_xspi_ivi_power_bmonivol1_data = (U2)0U;
    u2_s_xspi_ivi_power_bmonivol2_data = (U2)0U;
    u2_s_xspi_ivi_power_bmonivol3_data = (U2)0U;
    u1_s_xspi_ivi_power_bmoni_1stsend_flg = (U1)FALSE;

    u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_POWER_BMONI] = (U4)XSPI_IVI_POWER_BMONVOL_TASK;
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1POWERMainTask(void)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    初期化処理                                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1PowerMainTask(void)
{
    /* 定期送信などのデータ作成をここで行う */
    U1  u1_tp_data[XSPI_IVI_POWER_SIZE];
    U4  u4_t_power_task;
    U1  u1_t_power_ivent_jdg;
    U1  u1_t_init_chk;

    /* 前回電源ステート更新 */
    vd_g_MemcpyU1(&u1_s_xspi_ivi_power_state_pre[0],&u1_s_xspi_ivi_power_state[0],(U1)XSPI_IVI_POWER_01_BUFSIZ);

    vd_g_XspiIviSub1PowerGetSts(&u1_s_xspi_ivi_power_state[0]);

    u4_t_power_task = u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_POWER_STS];
    u1_t_power_ivent_jdg = (U1)FALSE;
    u1_t_power_ivent_jdg = u1_s_XspiIviSub1PowerDataEventJdg(&u1_s_xspi_ivi_power_state[0],&u1_s_xspi_ivi_power_state_pre[0],(U1)XSPI_IVI_POWER_01_BUFSIZ);

    /* SPI通信許可OKかどうか */
    if(u1_s_xspi_ivi_power_start_flg == (U1)TRUE){
        if((u4_t_power_task >= (U4)XSPI_IVI_POWER_TASK) ||
           (u1_t_power_ivent_jdg == (U1)TRUE)){
            /* 2s定期 or 値変化でXSPI通信 */
            u1_tp_data[0] = (U1)XSPI_IVI_POWER_STATE_SEND;
            vd_g_MemcpyU1(&u1_tp_data[1],&u1_s_xspi_ivi_power_state[0],(U1)XSPI_IVI_POWER_01_BUFSIZ);
            vd_s_XspiIviSub1PowerDataToQueue((U2)XSPI_IVI_POWER_STATE_SIZE,u1_tp_data);
            u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_POWER_STS] = (U4)0U;
        }else{
            /* Do Nothing */
        }

        u1_t_init_chk = u1_s_XspiIviSub1PowerDevInitCompChk();

        if(u1_s_xspi_ivi_power_state_trans_flg == (U1)TRUE){  /* デバイス初期化済かつ指示あり */
            /* 状態移行確認 */
            u1_tp_data[0] = (U1)XSPI_IVI_POWER_STATE_TRANS_SEND;
            u1_tp_data[1] = st_s_xspi_ivi_state_trans.u1_count;
            u1_tp_data[2] = st_s_xspi_ivi_state_trans.u1_basic_state;
            u1_tp_data[3] = st_s_xspi_ivi_state_trans.u1_special_state;
            u1_tp_data[4] = st_s_xspi_ivi_state_trans.u1_ota_state;
            u1_tp_data[5] = st_s_xspi_ivi_state_trans.u1_appearance_state;
            vd_s_XspiIviSub1PowerDataToQueue((U2)XSPI_IVI_POWER_TRANS_SIZE,u1_tp_data);
            /* 指示フラグをFALSEに落とす */
            u1_s_xspi_ivi_power_state_trans_flg = (U1)FALSE;
        }
    }

    /* Bモニ電圧値取得 */
    if(u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_POWER_BMONI] >= (U4)XSPI_IVI_POWER_BMONVOL_TASK){
        (void)u1_g_IoHwAdcRead((U1)ADC_CH_B_MON1,&u2_s_xspi_ivi_power_bmonivol1_data);
        (void)u1_g_IoHwAdcRead((U1)ADC_CH_B_MON2,&u2_s_xspi_ivi_power_bmonivol2_data);
        (void)u1_g_IoHwAdcRead((U1)ADC_CH_B_MON3,&u2_s_xspi_ivi_power_bmonivol3_data);
        u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_POWER_BMONI] = (U4)0U;
        if(u1_s_xspi_ivi_power_bmoni_1stsend_flg == (U1)TRUE) {
            vd_g_XspiIviSub1PowerBmoniVolSend();
        }
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1PowerGetSts(U1* u1_ap_data)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    電源ステート取得処理                                                                                             */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1PowerGetSts(U1* u1_ap_data)
{
    /* CAN受信用 */
    U1  u1_t_sts;
    U1  u1_t_VPSINFOS;  /* 特殊ステート */
    U1  u1_t_VPSISOTA;  /* OTAステート */
    U1  u1_t_APOFRQ;    /* 見た目ON/OFF */
    U1  u1_t_VPSCNG;

    /* 電源ステート取得用 */
    U4  u4_t_power_sts;

    /* Boot起動用 */
    U1 u1_t_boot;

    /* 電源ステートをCANから受信 */
    u1_t_sts    = (U1)(Com_GetIPDUStatus((PduIdType)MSG_BDC1S81_RXCH0) & ((U1)COM_NO_RX | (U1)COM_TIMEOUT));
    (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFOS, &u1_t_VPSINFOS );
    (void)Com_ReceiveSignal(ComConf_ComSignal_VPSISOTA, &u1_t_VPSISOTA );
    (void)Com_ReceiveSignal(ComConf_ComSignal_APOFRQ  , &u1_t_APOFRQ   );
    (void)Com_ReceiveSignal(ComConf_ComSignal_VPSCNG  , &u1_t_VPSCNG   );
    
    if((u1_t_sts & (U1)COM_NO_RX) == (U1)COM_NO_RX){
        /* BDC1S81未受信時の通知値 */
        u1_ap_data[XSPI_IVI_POWER_01_BYTE2] = XSPI_IVI_POWER_STATE_PARK; /* 基本ステート */
        u1_ap_data[XSPI_IVI_POWER_01_BYTE3] = (U1)0x00U;                 /* 特殊ステート */
        u1_ap_data[XSPI_IVI_POWER_01_BYTE4] = (U1)0x00U;                 /* OTAステート */
        u1_ap_data[XSPI_IVI_POWER_01_BYTE5] = (U1)0x01U;                 /* 見た目ON/OFF */
        u1_ap_data[XSPI_IVI_POWER_01_BYTE6] = (U1)0x00U;                 /* 車両電源(特殊)ステート遷移中フラグ */
    }
    else{
        u4_t_power_sts = u4_g_VehopemdMdfield();
        switch(u4_t_power_sts) {
            case XSPI_IVI_POWER_VEHOPE_PARK:
                u1_ap_data[XSPI_IVI_POWER_01_BYTE2] = (U1)XSPI_IVI_POWER_STATE_PARK;
                break;
            case XSPI_IVI_POWER_VEHOPE_RIDEON:
                u1_ap_data[XSPI_IVI_POWER_01_BYTE2] = (U1)XSPI_IVI_POWER_STATE_RIDEON;
                break;
            case XSPI_IVI_POWER_VEHOPE_POWERON:
                u1_ap_data[XSPI_IVI_POWER_01_BYTE2] = (U1)XSPI_IVI_POWER_STATE_POWERON;
                break;
            case XSPI_IVI_POWER_VEHOPE_POWERON_STOP:
                u1_ap_data[XSPI_IVI_POWER_01_BYTE2] = (U1)XSPI_IVI_POWER_STATE_POWERON_STOP;
                break;
            case XSPI_IVI_POWER_VEHOPE_PARK_HI_PRE:
                u1_ap_data[XSPI_IVI_POWER_01_BYTE2] = (U1)XSPI_IVI_POWER_STATE_PARK_HI_PRE;
                break;
            case XSPI_IVI_POWER_VEHOPE_PARK_TEMP_CON:
                u1_ap_data[XSPI_IVI_POWER_01_BYTE2] = (U1)XSPI_IVI_POWER_STATE_PARK_TEMP_CON;
                break;
            default:
                break;
            }

        u1_ap_data[XSPI_IVI_POWER_01_BYTE3] = u1_t_VPSINFOS; /* 特殊ステートのCAN信号値 */
        u1_ap_data[XSPI_IVI_POWER_01_BYTE4] = u1_t_VPSISOTA; /* OTAステートのCAN信号値 */
        u1_ap_data[XSPI_IVI_POWER_01_BYTE5] = u1_t_APOFRQ;   /* 見た目ON/OFFのCAN信号値 */
        u1_ap_data[XSPI_IVI_POWER_01_BYTE6] = u1_t_VPSCNG;   /* 車両電源(特殊)ステート遷移中フラグのCAN信号値 */
    }

    /* Byte7 DisconnectionState */
    if(u1_ap_data[XSPI_IVI_POWER_01_BYTE2] == (U1)XSPI_IVI_POWER_STATE_PARK){
        u1_ap_data[XSPI_IVI_POWER_01_BYTE7]  = (U1)XSPI_IVI_POWER_DC_UNKNOWN;
    }
    else if((u1_t_sts & (U1)COM_TIMEOUT) == (U1)COM_TIMEOUT){
        u1_ap_data[XSPI_IVI_POWER_01_BYTE7]  = (U1)XSPI_IVI_POWER_DC_PRESENT;
    }
    else{
        u1_ap_data[XSPI_IVI_POWER_01_BYTE7]  = (U1)XSPI_IVI_POWER_DC_NONE;
    }

    /* シス検暫定対応 */
    /* BOOT入力値取得処理 */
    u1_t_boot = Dio_ReadChannel(DIO_ID_PORT0_CH2);
    if(u1_t_boot == (U1)STD_HIGH){   /* BOOT=Hiを検知した場合、どの状態でも下記状態に上書き */
        u1_ap_data[XSPI_IVI_POWER_01_BYTE2] = (U1)XSPI_IVI_POWER_STATE_POWERON;   /* 基本ステート：POWERON通常 */
        u1_ap_data[XSPI_IVI_POWER_01_BYTE3] = (U1)XSPI_IVI_POWER_STATE_OFF;       /* 特殊ステート：未設定 */
        u1_ap_data[XSPI_IVI_POWER_01_BYTE4] = (U1)0U;                             /* OTAステート ：未設定 */
        u1_ap_data[XSPI_IVI_POWER_01_BYTE5] = (U1)0U;                             /* 見た目ON/OFF：ON */
        u1_ap_data[XSPI_IVI_POWER_01_BYTE6] = (U1)0U;                             /* 車両電源（特殊）ステート遷移中フラグ：遷移完了 */
        u1_ap_data[XSPI_IVI_POWER_01_BYTE7] = (U1)XSPI_IVI_POWER_DC_NONE;         /* 途絶状態：途絶なし */
    }
    /* シス検暫定ここまで */
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1PowerBmoniVolSend(void)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1PowerBmoniVolSend(void)
{
    /*Bモニ電圧送信*/    
    U1 u1_tp_data[7];

    u1_tp_data[0] = (U1)XSPI_IVI_POWER_BMONIVOL_SEND;
    u1_tp_data[1] = (U1)((u2_s_xspi_ivi_power_bmonivol1_data & 0x0F00U) >> XSPI_IVI_SFT_08);
    u1_tp_data[2] = (U1)(u2_s_xspi_ivi_power_bmonivol1_data & 0x00FFU);
    u1_tp_data[3] = (U1)((u2_s_xspi_ivi_power_bmonivol2_data & 0x0F00U) >> XSPI_IVI_SFT_08);
    u1_tp_data[4] = (U1)(u2_s_xspi_ivi_power_bmonivol2_data & 0x00FFU);
    u1_tp_data[5] = (U1)((u2_s_xspi_ivi_power_bmonivol3_data & 0x0F00U) >> XSPI_IVI_SFT_08);
    u1_tp_data[6] = (U1)(u2_s_xspi_ivi_power_bmonivol3_data & 0x00FFU);

    vd_s_XspiIviSub1PowerDataToQueue((U2)XSPI_IVI_POWER_BMONI_SIZE,u1_tp_data);
    u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_POWER_BMONI] = (U4)0U;

    if(u1_s_xspi_ivi_power_bmoni_1stsend_flg == (U1)FALSE) {
        u1_s_xspi_ivi_power_bmoni_1stsend_flg = (U1)TRUE;
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1_PowerState1stSend(void)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1_PowerState1stSend(void)
{
    /*起動時電源ステート送信処理*/    
    U1 u1_tp_data[XSPI_IVI_POWER_STATE_SIZE];

    u1_tp_data[0] = (U1)XSPI_IVI_POWER_STATE_SEND;
    vd_g_MemcpyU1(&u1_tp_data[1],&u1_s_xspi_ivi_power_state[0],(U1)XSPI_IVI_POWER_01_BUFSIZ);
    vd_s_XspiIviSub1PowerDataToQueue((U2)XSPI_IVI_POWER_STATE_SIZE,u1_tp_data);
    u1_s_xspi_ivi_power_start_flg = (U1)TRUE;
    u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_POWER_STS] = (U4)0U;
}

/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub1PowerOperationStsSend(const U1 u1_a_DATA)                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_a_DATA : SoC Operation Status                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1PowerOperationStsSend(const U1 u1_a_DATA)
{
    /*動作ステータス応答*/    
    U1 u1_tp_data[XSPI_IVI_POWER_OPESTS_SIZE];

    u1_tp_data[0] = (U1)XSPI_IVI_POWER_OPESTS_SEND;
    u1_tp_data[1] = u1_a_DATA;
    u1_tp_data[2] = (U1)0U; /*暫定 起動回数カウンタ*/
    u1_tp_data[3] = (U1)0U; /*暫定 起動回数カウンタ*/
    u1_tp_data[4] = (U1)0U; /*暫定 Tick Time*/
    u1_tp_data[5] = (U1)0U; /*暫定 Tick Time*/
    u1_tp_data[6] = (U1)0U; /*暫定 Tick Time*/
    u1_tp_data[7] = (U1)0U; /*暫定 Tick Time*/

    vd_s_XspiIviSub1PowerDataToQueue((U2)XSPI_IVI_POWER_OPESTS_SIZE,u1_tp_data);
}

/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub1PowerSTRmodeSend(const U1 u1_a_DATA)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_a_DATA : STR Mode Status                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1PowerSTRmodeSend(const U1 u1_a_DATA)
{
    /*動作ステータス応答*/    
    U1 u1_tp_data[XSPI_IVI_POWER_STRMODE_SIZE];

    u1_tp_data[0] = (U1)XSPI_IVI_POWER_STRMODE_SEND;
    u1_tp_data[1] = u1_a_DATA;

    vd_s_XspiIviSub1PowerDataToQueue((U2)XSPI_IVI_POWER_STRMODE_SIZE,u1_tp_data);
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1_POWER_Ana(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_data_size)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*                  u2_a_data_size : Data Size                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1PowerAna(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_data_size)
{
    U1 u1_t_subtype;

    u1_t_subtype = u1_ap_XSPI_ADD[0];

    switch (u1_t_subtype)
    {
    case XSPI_IVI_POWER_STATE_REC:
        /*シス検では受信のみ 今後フェール用で使用*/
        break;
    case XSPI_IVI_POWER_STATE_TRANS_REC:
        vd_s_XspiIviSub1_PowerStateTransRec(&u1_ap_XSPI_ADD[0],u2_a_data_size);
        break;
    case XSPI_IVI_POWER_OPESTS_REC:
        vd_s_XspiIviSub1PowerOperationStsRec(&u1_ap_XSPI_ADD[0]);
        break;
    case XSPI_IVI_POWER_STRMODE_REC:
        vd_s_XspiIviSub1PowerSTRmodeRec(&u1_ap_XSPI_ADD[0]);
        break;
    case XSPI_IVI_POWER_BOOTLOG_REQ:
        vd_g_BootLogCtl_RxReq();
        break;
    default:
        break;
    }
}

/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub1_PowerStateTransRec(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_data_size)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*                  u2_a_data_size : Data Size                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1_PowerStateTransRec(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_data_size)
{
    /*状態移行指示あり シス検では1回のみ*/
    if(u1_ap_XSPI_ADD[1] != (U1)0U){
        u1_s_xspi_ivi_power_state_trans_flg = (U1)TRUE;
    }
    st_s_xspi_ivi_state_trans.u1_count = u1_ap_XSPI_ADD[1];
    st_s_xspi_ivi_state_trans.u1_basic_state = u1_ap_XSPI_ADD[2];
    st_s_xspi_ivi_state_trans.u1_special_state = u1_ap_XSPI_ADD[3];
    st_s_xspi_ivi_state_trans.u1_ota_state = u1_ap_XSPI_ADD[4];
    st_s_xspi_ivi_state_trans.u1_appearance_state = u1_ap_XSPI_ADD[5];
}

/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub1PowerOperationStsRec(const U1 * u1_ap_XSPI_ADD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1PowerOperationStsRec(const U1 * u1_ap_XSPI_ADD)
{
    /*動作ステータス通知*/    
    vd_s_XspiIviSub1PowerOperationStsSend(u1_ap_XSPI_ADD[1]);

    /*暫定:Skip SoCからのリセット要求*/
}

/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub1PowerSTRmodeRec(const U1 * u1_ap_XSPI_ADD)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1PowerSTRmodeRec(const U1 * u1_ap_XSPI_ADD)
{
    /*デバイスのサスペンド/レジューム処理スキップ*/
    /*暫定:44hコマンドをそのまま応答する*/
    vd_s_XspiIviSub1PowerSTRmodeSend(u1_ap_XSPI_ADD[1]);
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1DevInitFinish(void)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1DevInitFinish(void)
{
    U1 u1_t_gpsrst_pin;
    U4 u4_t_loop;
    U4 u4_t_task_cnt;

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)MCU_PORT_NUM; u4_t_loop++) {
        if(u4_t_loop == (U4)MCU_PORT_GPS_RST){ 
            u1_t_gpsrst_pin = Dio_ReadChannel(Mcu_Dio_PortId[u4_t_loop]);
            if((u1_t_gpsrst_pin == (U1)STD_HIGH) &&
              (u1_t_gpsrst_pin != u1_s_xspi_ivi_power_gpsrst_sts_pre)) {
                u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_POWER_GPSRST] = (U4)0U;
                u1_s_xspi_ivi_power_gpsrst_sts_chk = (U1)TRUE;
            }

            u4_t_task_cnt = u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_POWER_GPSRST];
            if((u1_s_xspi_ivi_power_gpsrst_sts_chk == (U1)TRUE) &&
               (u4_t_task_cnt >= (U4)XSPI_IVI_POWER_GPSRST_INI_TASK)){
                u4_s_xspi_ivi_power_device_init_fin_sts |= (U4)((U4)TRUE << u4_t_loop);
            }
            u1_s_xspi_ivi_power_gpsrst_sts_pre = u1_t_gpsrst_pin;
        } else {
            u4_s_xspi_ivi_power_device_init_fin_sts |= (U4)(Dio_ReadChannel(Mcu_Dio_PortId[u4_t_loop]) << u4_t_loop);
        }
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1PowerDevInitCmpApp(const U1 u1_a_ID)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1PowerDevInitCmpApp(const U1 u1_a_ID)
{
    switch (u1_a_ID)
    {
    case XSPI_IVI_POWER_EIZO_INI:
        u2_s_xspi_ivi_power_device_init_app |= (U2)XSPI_IVI_POWER_DEV_INI_COMP_EIZO;
        break;
    case XSPI_IVI_POWER_GVIFRECV_INI:
        u2_s_xspi_ivi_power_device_init_app |= (U2)XSPI_IVI_POWER_DEV_INI_COMP_GVIFREC;
        break;
    case XSPI_IVI_POWER_GVIFSEND_INI:
        u2_s_xspi_ivi_power_device_init_app |= (U2)XSPI_IVI_POWER_DEV_INI_COMP_GVIFSEND;
        break;
    case XSPI_IVI_POWER_GYRO_INI:
        u2_s_xspi_ivi_power_device_init_app |= (U2)XSPI_IVI_POWER_DEV_INI_COMP_GYRO;
        break;
    case XSPI_IVI_POWER_POWER_INI:
        u2_s_xspi_ivi_power_device_init_app |= (U2)XSPI_IVI_POWER_DEV_INI_COMP_POWER;
        break;
    default:
        break;
    }
}

/*===================================================================================================================================*/
/*  static U1            u1_s_XspiIviSub1PowerDevInitCompChk(void)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_result : Devie initialization Status Check                                                                  */
/*===================================================================================================================================*/
static U1            u1_s_XspiIviSub1PowerDevInitCompChk(void)
{
    U1  u1_t_result;
    U1  u1_t_pwrsts;
    U4  u4_t_dev_chk;
    U2  u2_t_devapp_chk;

    u1_t_result = (U1)FALSE;
    u1_t_pwrsts = u1_g_Power_ModeState();

    if(u1_t_pwrsts < (U1)POWER_MODE_STATE_NUM) {
        u4_t_dev_chk = u4_s_xspi_ivi_power_device_init_fin_sts & u4_sp_xspi_ivi_power_dev_init[u1_t_pwrsts];
        u2_t_devapp_chk = u2_s_xspi_ivi_power_device_init_app & u2_sp_xspi_ivi_power_dev_app_init[u1_t_pwrsts];

        if(u4_t_dev_chk == u4_sp_xspi_ivi_power_dev_init[u1_t_pwrsts]) {
            u1_t_result = (U1)TRUE;
        }

        if(u2_t_devapp_chk != u2_sp_xspi_ivi_power_dev_app_init[u1_t_pwrsts]) {
            u1_t_result &= (U1)FALSE;
        }
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1PowerBootLogResSend(const U1 * u1_ap_DATA)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1PowerBootLogResSend(const U1 * u1_ap_DATA)
{
    U1  u1_tp_data[XSPI_IVI_POWER_BOOTLOG_SIZE];
    U1  u1_t_size;

    u1_t_size = (U1)XSPI_IVI_POWER_BOOTLOG_SIZE - (U1)1U;
    u1_tp_data[0] = (U1)XSPI_IVI_POWER_BOOTLOG_RES;
    vd_g_MemcpyU1(&u1_tp_data[1],&u1_ap_DATA[0],u1_t_size);
    vd_s_XspiIviSub1PowerDataToQueue((U2)XSPI_IVI_POWER_BOOTLOG_SIZE,u1_tp_data);
}

/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub1PowerDataToQueue(const U2 u2_a_size,const U1 u1_a_XSPI_ADD)                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*                  u2_a_data_size : Data Size                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1PowerDataToQueue(const U2 u2_a_size,const U1* u1_ap_XSPI_ADD)
{
    U1     u1_t_id;

    u1_t_id = (U1)XSPI_IVI_POWER_ID;

    /*キューの関数呼び出し（そっちでヘッダーとかは入れてく）*/
    vd_g_XspiIviSub1MISCStuckBuff(u1_t_id,u2_a_size,&u1_ap_XSPI_ADD[0]);
}

/*===================================================================================================================================*/
/*  U1          u1_s_XspiIviSub1PowerDataEventJdg(const U1* u1_ap_DATA,const U1* u1_ap_DATA_PRE,const U1 u1_a_size)                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*                  u2_a_data_size : Data Size                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1            u1_s_XspiIviSub1PowerDataEventJdg(const U1* u1_ap_DATA,const U1* u1_ap_DATA_PRE,const U1 u1_a_SIZE)
{
    U1     u1_t_judge;
    U4     u4_t_loop;

    u1_t_judge = (U1)FALSE;
    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)u1_a_SIZE; u4_t_loop++){
        if(u1_ap_DATA[u4_t_loop] != u1_ap_DATA_PRE[u4_t_loop]){
            u1_t_judge = (U1)TRUE;
        }
    }

    return(u1_t_judge);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  0.0.0    01/20/2025  KT       New.                                                                                               */
/*  0.1.0    07/18/2025  TN       Change 01h: Power Status Notification                                                              */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * KT   = Kenta Takaji, Denso Techno                                                                                              */
/*  * TN   = Tetsu Naruse, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
