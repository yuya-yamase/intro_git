/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO TECHNO Corporation                                                                                               */
/*===================================================================================================================================*/
/*  Transmission and reception processing of subframe 4 in XSPI communication.                                                       */
/*  Handled data: CAN Data/Repro/LCAN Data                                                                                           */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_IVI_SUB1_SYSTEM_C_MAJOR                   (0)
#define XSPI_IVI_SUB1_SYSTEM_C_MINOR                   (0)
#define XSPI_IVI_SUB1_SYSTEM_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include    "x_spi_ivi_sub1_private.h"
#include    "x_spi_ivi_sub1_system.h"
#include    "IVI_PwrCtrl_DDFreq.h"
#include    "GNSSCtl.h"
#include    "Dio.h"
#include    "Dio_Symbols.h"
#include    "ExtSigCtrl.h"
#include    "STRCtl.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((XSPI_IVI_SUB1_SYSTEM_C_MAJOR != XSPI_IVI_SUB1_SYSTEM_H_MAJOR) || \
     (XSPI_IVI_SUB1_SYSTEM_C_MINOR != XSPI_IVI_SUB1_SYSTEM_H_MINOR) || \
     (XSPI_IVI_SUB1_SYSTEM_C_PATCH != XSPI_IVI_SUB1_SYSTEM_H_PATCH))
#error "x_spi_ivi_sub1_system.c and x_spi_ivi_sub1.h : source and header files are inconsistent!"
#endif
#if ((XSPI_IVI_SUB1_SYSTEM_C_MAJOR != XSPI_IVI_SUB1_PRIVATE_H_MAJOR) || \
     (XSPI_IVI_SUB1_SYSTEM_C_MINOR != XSPI_IVI_SUB1_PRIVATE_H_MINOR) || \
     (XSPI_IVI_SUB1_SYSTEM_C_PATCH != XSPI_IVI_SUB1_PRIVATE_H_PATCH))
#error "x_spi_ivi_sub1_system.c and x_spi_ivi_sub1_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define    XSPI_IVI_SYSTEM_ID              (0x22U)
#define    XSPI_IVI_SYSTEM_USB_POWSUP      (0x01U)
#define    XSPI_IVI_SYSTEM_DDCON_REC       (0x10U)
#define    XSPI_IVI_SYSTEM_DDCON_SEND      (0x11U)
#define    XSPI_IVI_SYSTEM_GPS_STS         (0x20U)
#define    XSPI_IVI_SYSTEM_GPS_OPE_RECUEST (0x21U)
#define    XSPI_IVI_SYSTEM_GPS_OPE_RESPON  (0x22U)
#define    XSPI_IVI_SYSTEM_VEHSPD_CNT      (0x30U)
#define    XSPI_IVI_SYSTEM_EXTSIG_SEND     (0x40U)
#define    XSPI_IVI_SYSTEM_TMUTE           (0x50U)
#define    XSPI_IVI_SYSTEM_SETTING_REC     (0x90U)
#define    XSPI_IVI_SYSTEM_SETTING_SEND    (0x91U)

#define    XSPI_IVI_EXTSIG_ID_TEST         (0x01U)
#define    XSPI_IVI_EXTSIG_ID_USB          (0x10U)
#define    XSPI_IVI_EXTSIG_ID_MIC          (0x20U)
#define    XSPI_IVI_EXTSIG_ID_MIC2         (0x21U)
#define    XSPI_IVI_EXTSIG_ID_MIC3         (0x22U)
#define    XSPI_IVI_EXTSIG_ID_MIC4         (0x23U)
#define    XSPI_IVI_EXTSIG_ID_WIFI         (0x30U)
#define    XSPI_IVI_EXTSIG_ID_WIFI2        (0x31U)
#define    XSPI_IVI_EXTSIG_ID_DTV          (0x40U)
#define    XSPI_IVI_EXTSIG_ID_DTV2         (0x41U)
#define    XSPI_IVI_EXTSIG_ID_DTV3         (0x42U)
#define    XSPI_IVI_EXTSIG_ID_DTV4         (0x43U)
#define    XSPI_IVI_EXTSIG_ID_GNSS         (0x50U)
#define    XSPI_IVI_EXTSIG_ID_DAB          (0x60U)
#define    XSPI_IVI_EXTSIG_ID_DAB2         (0x61U)
#define    XSPI_IVI_EXTSIG_ID_PWR          (0x71U)

#define    XSPI_IVI_SYSTEM_GPS_STBY        (0x00U)
#define    XSPI_IVI_SYSTEM_GPS_NORMAL      (0x01U)

#define    XSPI_IIV_SYSTEM_GPS_STS_TASK    (10000U / XSPI_IVI_TASK_TIME)
#define    XSPI_IIV_SYSTEM_EXTSIG_STS_TASK (3000U / XSPI_IVI_TASK_TIME)
#define    XSPI_IIV_SYSTEM_TEST_SAMPL_TASK (100U / XSPI_IVI_TASK_TIME)
#define    XSPI_IIV_SYSTEM_VEHSPDCNT_TASK  (240U / XSPI_IVI_TASK_TIME)
#define    XSPI_IIV_SYSTEM_USBPOWSUP_TASK  (500U / XSPI_IVI_TASK_TIME)

#define    XSPI_IVI_TESTTERM_UNKNOWN       (0U)
#define    XSPI_IVI_TESTTERM_OFF           (1U)
#define    XSPI_IVI_TESTTERM_ON            (2U)

#define    XSPI_IVI_PWR_OFF                (1U)
#define    XSPI_IVI_PWR_ON                 (2U)

/*SubType:90h/91h*/
#define    XSPI_IVI_SYSTEM_ID_STRMODE      (0x01U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1              u1_s_xspi_ivi_system_gps_sts;
static U1              u1_s_xspi_ivi_system_gps_sts_pre;
static U1              u1_sp_xspi_ivi_system_extsig_data[XSPI_IVI_EXTSIG_NUM]; /*外部信号の状態格納*/
static U1              u1_sp_xspi_ivi_system_extsig_data_pre[XSPI_IVI_EXTSIG_NUM];
static U1              u1_s_xspi_ivi_system_extsig_testterm_data[3];  /*TEST端子から取得したデータ*/
static U1              u1_s_xspi_ivi_system_clkfreq;
static U4              u4_s_xspi_ivi_system_vehspd_cnt;
static U2              u2_s_xspi_ivi_system_usbpowsup;
static U1              u1_s_xspi_ivi_system_tmute_data;

static U1              u1_s_xspi_ivi_system_gps_sts_1stsend_flg;
static U1              u1_s_xspi_ivi_system_extsig_1stsend_flg;
static U1              u1_s_xspi_ivi_system_perion_flg;
static U1              u1_s_xspi_ivi_system_vehspd_cnt_send_flg;
static U1              u1_s_xspi_ivi_system_usbpowsup_send_flg;
static U1              u1_s_xspi_ivi_system_tmute_1stsend_flg;

/*SubType:90h/91h*/
static U1              u1_s_xspi_ivi_system_setdata[XSPI_IVI_SYSTEM_NUM];
static U1              u1_s_xspi_ivi_system_setdatarec_flg;
static U1              u1_s_xspi_ivi_system_set_1stsend_flg;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void            vd_s_XspiIviSub1SystemDataToQueue(const U2 u2_a_size,const U1* u1_ap_XSPI_ADD);
static U1              u1_s_XspiIviSub1SystemDataEventJdg(const U1* u1_ap_DATA,const U1* u1_ap_DATA_PRE,const U1 u1_a_SIZE);
static void            vd_s_XspiIviSub1USBPowSupSend(void);
static void            vd_s_XspiIviSub1SystemSetDataRec(const U1 * u1_ap_XSPI_ADD);
static void            vd_s_XspiIviSub1SystemDataSend(void);
/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1SystemInit(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    初期化処理                                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1SystemInit(void)
{
    u1_s_xspi_ivi_system_gps_sts = (U1)XSPI_IVI_SYSTEM_GPS_STBY;
    u1_s_xspi_ivi_system_gps_sts_pre = (U1)XSPI_IVI_SYSTEM_GPS_STBY;
    vd_g_MemfillU1(&u1_sp_xspi_ivi_system_extsig_data[0], (U1)0U, (U4)XSPI_IVI_EXTSIG_NUM);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_system_extsig_data_pre[0], (U1)0U, (U4)XSPI_IVI_EXTSIG_NUM);
    vd_g_MemfillU1(&u1_s_xspi_ivi_system_extsig_testterm_data[0], (U1)0U, (U4)3U);

    u1_s_xspi_ivi_system_gps_sts_1stsend_flg = (U1)FALSE;
    u1_s_xspi_ivi_system_extsig_1stsend_flg = (U1)FALSE;
    u1_s_xspi_ivi_system_perion_flg = (U1)FALSE;

    u1_s_xspi_ivi_system_clkfreq = (U1)0U;
    u4_s_xspi_ivi_system_vehspd_cnt = (U4)0U;
    u1_s_xspi_ivi_system_vehspd_cnt_send_flg = (U1)FALSE;

    u2_s_xspi_ivi_system_usbpowsup = (U2)0U;
    u1_s_xspi_ivi_system_usbpowsup_send_flg = (U1)FALSE;

    u1_s_xspi_ivi_system_tmute_data = (U1)XSPI_IVI_TMUTE_UNDEF;
    u1_s_xspi_ivi_system_tmute_1stsend_flg = (U1)FALSE;

    vd_g_XspiIviSub1ExtSgnlPut((U1)XSPI_IVI_EXTSIG_PWR, (U1)XSPI_IVI_PWR_OFF);

    vd_g_MemfillU1(&u1_s_xspi_ivi_system_setdata[0], (U1)0U, (U4)XSPI_IVI_SYSTEM_NUM);
    u1_s_xspi_ivi_system_setdatarec_flg = (U1)FALSE;
    u1_s_xspi_ivi_system_set_1stsend_flg = (U1)FALSE;
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1SystemMainTask(void)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    定期処理                                                                                                          */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1SystemMainTask(void)
{
    U4    u4_t_task;
    U1    u1_t_test;
    U1    u1_t_perion;
    U1    u1_t_event_jdg;
    U1    u1_t_exsig_pwr;

    /*定期送信などのデータ作成をここで行う*/
    /*TEST端子読み出し*/
    /* TEST端子入力値取得処理 */
    u1_t_event_jdg = (U1)FALSE;

    u4_t_task = u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_SYSTEM_TEST];

    u1_t_perion = Dio_ReadChannel(DIO_ID_PORT10_CH2);
    if((u1_t_perion == (U1)STD_HIGH) &&
       (u1_s_xspi_ivi_system_perion_flg == (U1)FALSE)){
        u1_s_xspi_ivi_system_perion_flg = (U1)TRUE;
        u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_SYSTEM_TEST] = (U4)0U;
    } else if(u1_t_perion == (U1)STD_LOW) {
        u1_s_xspi_ivi_system_perion_flg = (U1)FALSE;
    } else {
        /*Do Nothing*/
    }
    
    if(u1_s_xspi_ivi_system_perion_flg == (U1)TRUE) {
        if(u4_t_task >= (U4)XSPI_IIV_SYSTEM_TEST_SAMPL_TASK){   /*100msごとのサンプリング */
            u1_t_test = Dio_ReadChannel(DIO_ID_PORT5_CH6);
            u1_s_xspi_ivi_system_extsig_testterm_data[2] = u1_s_xspi_ivi_system_extsig_testterm_data[1];
            u1_s_xspi_ivi_system_extsig_testterm_data[1] = u1_s_xspi_ivi_system_extsig_testterm_data[0];
            u1_s_xspi_ivi_system_extsig_testterm_data[0] = u1_t_test;
            if((u1_s_xspi_ivi_system_extsig_testterm_data[0] == (U1)STD_HIGH) &&
              (u1_s_xspi_ivi_system_extsig_testterm_data[1] == (U1)STD_HIGH) &&
              (u1_s_xspi_ivi_system_extsig_testterm_data[2] == (U1)STD_HIGH))
            {
                vd_g_XspiIviSub1ExtSgnlPut((U1)XSPI_IVI_EXTSIG_TEST,(U1)XSPI_IVI_TESTTERM_ON);
            } else if((u1_s_xspi_ivi_system_extsig_testterm_data[0] == (U1)STD_LOW) &&
                     (u1_s_xspi_ivi_system_extsig_testterm_data[1] == (U1)STD_LOW) &&
                     (u1_s_xspi_ivi_system_extsig_testterm_data[2] == (U1)STD_LOW))
            {
                vd_g_XspiIviSub1ExtSgnlPut((U1)XSPI_IVI_EXTSIG_TEST,(U1)XSPI_IVI_TESTTERM_OFF);
            } else {
                /*Do Nothing*/
            }
            u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_SYSTEM_TEST] = (U4)0U;
        }
    }

    /* PWR端子入力取得処理 */
    u1_t_exsig_pwr  = ExtSigCtrl_GetSigSts(EXTSIGCTRL_KIND_EXT_PWR_SW);
    if(u1_t_exsig_pwr   == (U1)U1_EXTSIGCTRL_SIG_STS_ON){
        vd_g_XspiIviSub1ExtSgnlPut((U1)XSPI_IVI_EXTSIG_PWR, (U1)XSPI_IVI_PWR_ON);
    }
    else{
        vd_g_XspiIviSub1ExtSgnlPut((U1)XSPI_IVI_EXTSIG_PWR, (U1)XSPI_IVI_PWR_OFF);
    }

    /*外部信号状態の定期送信orイベント送信*/
    if(u1_s_xspi_ivi_system_extsig_1stsend_flg == (U1)TRUE){
        u4_t_task = u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_SYSTEM_EXTSIG];
        u1_t_event_jdg = (U1)u1_s_XspiIviSub1SystemDataEventJdg(&u1_sp_xspi_ivi_system_extsig_data[0],&u1_sp_xspi_ivi_system_extsig_data_pre[0],(U1)XSPI_IVI_EXTSIG_NUM);
        if((u4_t_task >= (U4)XSPI_IIV_SYSTEM_EXTSIG_STS_TASK) ||
           (u1_t_event_jdg == (U1)TRUE)) {
            vd_g_XspiIviSub1ExtSiGSend();
        }
    }

    /*GPSステータスの定期送信orイベント送信*/
    if(u1_s_xspi_ivi_system_gps_sts_1stsend_flg == (U1)TRUE) {
        u4_t_task = u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_SYSTEM_GPS];
        if((u4_t_task >= (U4)XSPI_IIV_SYSTEM_GPS_STS_TASK) ||
           (u1_s_xspi_ivi_system_gps_sts != u1_s_xspi_ivi_system_gps_sts_pre)){
            vd_g_XspiIviSub1GpsStsSend();
        }
    }

    /*車速カウンタ値の定期送信*/
    if(u1_s_xspi_ivi_system_vehspd_cnt_send_flg == (U1)TRUE) {
        u4_t_task = u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_SYSTEM_VEHSPD];
        if(u4_t_task >= (U4)XSPI_IIV_SYSTEM_VEHSPDCNT_TASK) {
            vd_g_XspiIviSub1VehspdCntSend();
        }
    }

    /*USB給電量の定期送信*/
    if(u1_s_xspi_ivi_system_usbpowsup_send_flg == (U1)TRUE) {
        u4_t_task = u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_SYSTEM_USB];
        if(u4_t_task >= (U4)XSPI_IIV_SYSTEM_USBPOWSUP_TASK) {
            vd_s_XspiIviSub1USBPowSupSend();
        }
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1SystemAna(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_DATA_SIZE)                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*                  u2_a_DATA_SIZE : Data Size                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1SystemAna(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_DATA_SIZE)
{
    U1 u1_t_subtype;

    u1_t_subtype = u1_ap_XSPI_ADD[0];

    switch (u1_t_subtype)
    {
    case XSPI_IVI_SYSTEM_DDCON_REC:
        vd_g_Ivi_PwrCtrl_DDFreq_ChgReq(u1_ap_XSPI_ADD[1]);
        break;
    case XSPI_IVI_SYSTEM_GPS_OPE_RECUEST:
        /*GPS動作要求の通知先IFをコール*/
        vd_g_Gnss_GpsReq(u1_ap_XSPI_ADD[1]);
        break;
    case XSPI_IVI_SYSTEM_SETTING_REC:
        vd_s_XspiIviSub1SystemSetDataRec(&u1_ap_XSPI_ADD[1]);
        break;
    /*SystemのSip⇒MCUのその他コマンド解析処理いれる*/
    
    default:
        break;
    }
}

/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub1SystemSetDataRec(const U1 * u1_ap_XSPI_ADD)                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : Subtype(90h) Start Buffer                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1SystemSetDataRec(const U1 * u1_ap_XSPI_ADD)
{
    U1  u1_t_system_num;
    U4  u4_t_loop;
    U1  u1_t_id;
    U1  u1_t_data;
    U4  u4_t_buf;

    u1_t_system_num = u1_ap_XSPI_ADD[0];
    for(u4_t_loop = (U4)0U; u4_t_loop < u1_t_system_num; u4_t_loop++) {
        u4_t_buf = ((u4_t_loop * (U4)2U) + (U4)1U);
        u1_t_id = u1_ap_XSPI_ADD[u4_t_buf];
        u1_t_data = u1_ap_XSPI_ADD[u4_t_buf + 1U];
        switch(u1_t_id){
            case XSPI_IVI_SYSTEM_ID_STRMODE:
                vd_g_Str_ModeReq(u1_t_data);
            break;
        }
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1DDconSend(const U1 u1_a_DATA)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_a_DATA : 切り替え周波数                                                                                        */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1DDconSend(const U1 u1_a_DATA)
{
    U2     u2_s_SYSTEM_DDCON_SIZE = (U2)2U;
    U1     u1_tp_data[2];

    u1_tp_data[0] = (U1)XSPI_IVI_SYSTEM_DDCON_SEND;
    u1_tp_data[1] = u1_a_DATA;
    vd_s_XspiIviSub1SystemDataToQueue(u2_s_SYSTEM_DDCON_SIZE,u1_tp_data);
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1GpsStsSend(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1GpsStsSend(void)
{
    U2     u2_s_SYSTEM_GPSSTS_SIZE = (U2)2U;
    U1     u1_tp_data[2];

    u1_tp_data[0] = (U1)XSPI_IVI_SYSTEM_GPS_STS;
    u1_tp_data[1] = u1_s_xspi_ivi_system_gps_sts;
    vd_s_XspiIviSub1SystemDataToQueue(u2_s_SYSTEM_GPSSTS_SIZE,u1_tp_data);

    if(u1_s_xspi_ivi_system_gps_sts_1stsend_flg == (U1)FALSE) {
        u1_s_xspi_ivi_system_gps_sts_1stsend_flg = (U1)TRUE;
    }
    u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_SYSTEM_GPS] = (U4)0U;
    u1_s_xspi_ivi_system_gps_sts_pre = u1_s_xspi_ivi_system_gps_sts;
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1GpsStsPut(const U1 u1_a_DATA)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_a_DATA : GPSステータス                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1GpsStsPut(const U1 u1_a_DATA)
{
    u1_s_xspi_ivi_system_gps_sts = u1_a_DATA;
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1ExtSiGSend(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1ExtSiGSend(void)
{
    static const U2     u2_s_SYSTEM_EXTSIG_SIZE = (U2)XSPI_IVI_EXTSIG_SNDSIZ;
    U1     u1_tp_data[XSPI_IVI_EXTSIG_SNDSIZ];
    U4     u4_t_loop;
    U4     u4_t_hi;
    U4     u4_t_lo;

    u1_tp_data[0] = (U1)XSPI_IVI_SYSTEM_EXTSIG_SEND;
    u1_tp_data[1] = (U1)XSPI_IVI_EXTSIG_NUM;
    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)XSPI_IVI_EXTSIG_NUM;u4_t_loop++){
        u4_t_hi = ((u4_t_loop * (U4)2U) + (U4)2U);
        u4_t_lo = ((u4_t_loop * (U4)2U) + (U4)3U);
        u1_tp_data[u4_t_lo] = u1_sp_xspi_ivi_system_extsig_data[u4_t_loop];
        switch (u4_t_loop)
        {
        case 0:
            u1_tp_data[u4_t_hi] = (U1)XSPI_IVI_EXTSIG_ID_TEST;
            break;
        case 1:
            u1_tp_data[u4_t_hi] = (U1)XSPI_IVI_EXTSIG_ID_USB;
            break;
        case 2:
            u1_tp_data[u4_t_hi] = (U1)XSPI_IVI_EXTSIG_ID_MIC;
            break;
        case 3:
            u1_tp_data[u4_t_hi] = (U1)XSPI_IVI_EXTSIG_ID_MIC2;
            break;
        case 4:
            u1_tp_data[u4_t_hi] = (U1)XSPI_IVI_EXTSIG_ID_MIC3;
            break;
        case 5:
            u1_tp_data[u4_t_hi] = (U1)XSPI_IVI_EXTSIG_ID_MIC4;
            break;
        case 6:
            u1_tp_data[u4_t_hi] = (U1)XSPI_IVI_EXTSIG_ID_WIFI;
            break;
        case 7:
            u1_tp_data[u4_t_hi] = (U1)XSPI_IVI_EXTSIG_ID_WIFI2;
            break;
        case 8:
            u1_tp_data[u4_t_hi] = (U1)XSPI_IVI_EXTSIG_ID_DTV;
            break;
        case 9:
            u1_tp_data[u4_t_hi] = (U1)XSPI_IVI_EXTSIG_ID_DTV2;
            break;
        case 10:
            u1_tp_data[u4_t_hi] = (U1)XSPI_IVI_EXTSIG_ID_DTV3;
            break;
        case 11:
            u1_tp_data[u4_t_hi] = (U1)XSPI_IVI_EXTSIG_ID_DTV4;
            break;
        case 12:
            u1_tp_data[u4_t_hi] = (U1)XSPI_IVI_EXTSIG_ID_GNSS;
            break;
        case 13:
            u1_tp_data[u4_t_hi] = (U1)XSPI_IVI_EXTSIG_ID_DAB;
            break;
        case 14:
            u1_tp_data[u4_t_hi] = (U1)XSPI_IVI_EXTSIG_ID_DAB2;
            break;
        case 15:
            u1_tp_data[u4_t_hi] = (U1)XSPI_IVI_EXTSIG_ID_PWR;
            break;
        
        default:
            break;
        }
    }
    vd_s_XspiIviSub1SystemDataToQueue(u2_s_SYSTEM_EXTSIG_SIZE,u1_tp_data);

    if(u1_s_xspi_ivi_system_extsig_1stsend_flg == (U1)FALSE) {
        u1_s_xspi_ivi_system_extsig_1stsend_flg = (U1)TRUE;
    }
    u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_SYSTEM_EXTSIG] = (U4)0U;
    vd_g_MemcpyU1(&u1_sp_xspi_ivi_system_extsig_data_pre[0], &u1_sp_xspi_ivi_system_extsig_data[0], (U4)XSPI_IVI_EXTSIG_NUM);
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1ExtSgnlUSBPut(const U1 u1_a_ID,const U1 u1_a_DATA)                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_a_DATA : USBアダプタ接続状態                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1ExtSgnlPut(const U1 u1_a_ID,const U1 u1_a_DATA)
{
    if(u1_a_ID < (U1)XSPI_IVI_EXTSIG_NUM) {
        u1_sp_xspi_ivi_system_extsig_data[u1_a_ID] = u1_a_DATA;
    }
}
/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub1SystemDataSend(void)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1SystemDataSend(void)
{
    U1     u1_tp_data[XSPI_IVI_SYSTEM_SNDSIZE];
    U4     u4_t_loop;
    U4     u4_t_hi;
    U4     u4_t_lo;

    u1_tp_data[0] = (U1)XSPI_IVI_SYSTEM_SETTING_SEND;
    u1_tp_data[1] = (U1)XSPI_IVI_SYSTEM_NUM;
    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)XSPI_IVI_SYSTEM_NUM;u4_t_loop++){
        u4_t_hi = ((u4_t_loop * (U4)2U) + (U4)2U);
        u4_t_lo = ((u4_t_loop * (U4)2U) + (U4)3U);
        u1_tp_data[u4_t_lo] = u1_s_xspi_ivi_system_setdata[u4_t_loop];
        switch (u4_t_loop)
        {
            case XSPI_IVI_SYSTEM_STRMODE:
                u1_tp_data[u4_t_hi] = (U1)XSPI_IVI_SYSTEM_ID_STRMODE;
                break;
            default:
                break;
        }
    }
    vd_s_XspiIviSub1SystemDataToQueue((U2)XSPI_IVI_SYSTEM_SNDSIZE,u1_tp_data);
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1SystemDataPut(const U1 u1_a_ID,const U1 u1_a_DATA)                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_a_ID   : システム設定ID                                                                                        */
/*                  u1_a_DATA : システム設定値                                                                                        */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1SystemDataPut(const U1 u1_a_ID,const U1 u1_a_DATA)
{
    if(u1_a_ID < (U1)XSPI_IVI_SYSTEM_NUM) {
        u1_s_xspi_ivi_system_setdata[u1_a_ID] = u1_a_DATA;
        if(u1_s_xspi_ivi_system_set_1stsend_flg == (U1)TRUE) {
            vd_s_XspiIviSub1SystemDataSend();
        }
        u1_s_xspi_ivi_system_setdatarec_flg = (U1)TRUE;
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1SystemData1stSend(void)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1SystemData1stSend(void)
{
    if(u1_s_xspi_ivi_system_setdatarec_flg == (U1)TRUE) {
        vd_s_XspiIviSub1SystemDataSend();
    }
    u1_s_xspi_ivi_system_set_1stsend_flg = (U1)TRUE;
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1VehspdCntSend(void)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1VehspdCntSend(void)
{
    U2     u2_s_SYSTEM_VEHSPDCNT_SIZE = (U2)5U;
    U1     u1_tp_data[5];

    u1_tp_data[0] = (U1)XSPI_IVI_SYSTEM_VEHSPD_CNT;
    u1_tp_data[1] = u1_s_xspi_ivi_system_clkfreq;
    u1_tp_data[2] = (U1)((u4_s_xspi_ivi_system_vehspd_cnt & 0x00FF0000U) >> XSPI_IVI_SFT_16);
    u1_tp_data[3] = (U1)((u4_s_xspi_ivi_system_vehspd_cnt & 0x0000FF00U) >> XSPI_IVI_SFT_08);
    u1_tp_data[4] = (U1)(u4_s_xspi_ivi_system_vehspd_cnt & 0x000000FFU);
    vd_s_XspiIviSub1SystemDataToQueue(u2_s_SYSTEM_VEHSPDCNT_SIZE,u1_tp_data);

    if(u1_s_xspi_ivi_system_vehspd_cnt_send_flg == (U1)FALSE) {
        u1_s_xspi_ivi_system_vehspd_cnt_send_flg = (U1)TRUE;
    }
    u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_SYSTEM_VEHSPD] = (U4)0U;
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1SpCntPut(const ST_XSPI_IVI_SP_CNT_DATA st_a_DATA)                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      st_a_DATA : 車速カウンタ値                                                                                        */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1SpCntPut(const ST_XSPI_IVI_SP_CNT_DATA st_a_DATA)
{
    u1_s_xspi_ivi_system_clkfreq = st_a_DATA.u1_clock_freq;
    u4_s_xspi_ivi_system_vehspd_cnt = st_a_DATA.u4_sp_count;
}

/*===================================================================================================================================*/
/*  static void            vd_s_XspiIviSub1USBPowSupSend(void)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1USBPowSupSend(void)
{
    U2     u2_s_SYSTEM_USBPOWSUP_SIZE = (U2)3U;
    U1     u1_tp_data[3];

    u1_tp_data[0] = (U1)XSPI_IVI_SYSTEM_USB_POWSUP;
    u1_tp_data[1] = (U1)((u2_s_xspi_ivi_system_usbpowsup & 0x0F00U) >> XSPI_IVI_SFT_08);
    u1_tp_data[2] = (U1)(u2_s_xspi_ivi_system_usbpowsup & 0x00FFU);
    vd_s_XspiIviSub1SystemDataToQueue(u2_s_SYSTEM_USBPOWSUP_SIZE,u1_tp_data);

    if(u1_s_xspi_ivi_system_usbpowsup_send_flg == (U1)FALSE) {
        u1_s_xspi_ivi_system_usbpowsup_send_flg = (U1)TRUE;
    }
    u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_SYSTEM_USB] = (U4)0U;
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1USBPowSupPut(const U2 u2_a_DATA)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_a_DATA : GPS要求動作                                                                                           */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1USBPowSupPut(const U2 u2_a_DATA)
{
    u2_s_xspi_ivi_system_usbpowsup = (U2)u2_a_DATA;

    if(u1_s_xspi_ivi_system_usbpowsup_send_flg == (U1)FALSE) {
        vd_s_XspiIviSub1USBPowSupSend();
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1GpsOpeResPut(U1 u1_a_DATA)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_a_DATA : GPS要求動作                                                                                           */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1GpsOpeResPut(const U1 u1_a_DATA)
{
    U2     u2_s_SYSTEM_GPSOPERES_SIZE = (U2)2U;
    U1     u1_tp_data[2];

    u1_tp_data[0] = (U1)XSPI_IVI_SYSTEM_GPS_OPE_RESPON;
    u1_tp_data[1] = u1_a_DATA;
    vd_s_XspiIviSub1SystemDataToQueue(u2_s_SYSTEM_GPSOPERES_SIZE,u1_tp_data);
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1TmuteSend(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1TmuteSend(void)
{
    U2     u2_s_SYSTEM_TMUTE_SIZE = (U2)2U;
    U1     u1_tp_data[2];

    u1_tp_data[0] = (U1)XSPI_IVI_SYSTEM_TMUTE;
    u1_tp_data[1] = u1_s_xspi_ivi_system_tmute_data;
    vd_s_XspiIviSub1SystemDataToQueue(u2_s_SYSTEM_TMUTE_SIZE,u1_tp_data);

    if(u1_s_xspi_ivi_system_tmute_1stsend_flg == (U1)FALSE) {
        u1_s_xspi_ivi_system_tmute_1stsend_flg = (U1)TRUE;
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1TmuteDataPut(U1 u1_a_DATA)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_a_DATA : T-MUTE Data                                                                                          */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1TmuteDataPut(const U1 u1_a_DATA)
{
    u1_s_xspi_ivi_system_tmute_data = u1_a_DATA;
    
    if(u1_s_xspi_ivi_system_tmute_1stsend_flg == (U1)TRUE) {
        vd_g_XspiIviSub1TmuteSend();
    }
}

/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub1SystemDataToQueue(const U2 u2_a_size,const U1 u1_a_XSPI_ADD)                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*                  u2_a_data_size : Data Size                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1SystemDataToQueue(const U2 u2_a_size,const U1* u1_ap_XSPI_ADD)
{
    U1     u1_tp_data[256];
    U1     u1_t_id;

    u1_t_id = (U1)XSPI_IVI_SYSTEM_ID;

    vd_g_MemfillU1(&u1_tp_data[0], (U1)0U, (U4)256U);
    vd_g_MemcpyU1(&u1_tp_data[0], &u1_ap_XSPI_ADD[0], (U4)u2_a_size);

    /*キューの関数呼び出し（そっちでヘッダーとかは入れてく）*/
    vd_g_XspiIviSub1MISCStuckBuff(u1_t_id,u2_a_size,u1_tp_data);
}

/*===================================================================================================================================*/
/*  U1          u1_s_XspiIviSub1SystemDataEventJdg(const U1* u1_ap_DATA,const U1* u1_ap_DATA_PRE,const U1 u1_a_SIZE)                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*                  u2_a_data_size : Data Size                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1            u1_s_XspiIviSub1SystemDataEventJdg(const U1* u1_ap_DATA,const U1* u1_ap_DATA_PRE,const U1 u1_a_SIZE)
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
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * KT   = Kenta Takaji, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
