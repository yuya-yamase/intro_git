/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO TECHNO Corporation                                                                                               */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ANTCTL_C_MAJOR                   (0)
#define ANTCTL_C_MINOR                   (0)
#define ANTCTL_C_PATCH                   (0)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "AntCtl.h"
#include "x_spi_ivi_sub1_system.h"
#include "Dio.h"
#include "Iohw_adc.h"
#include "DtcCtl.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((ANTCTL_C_MAJOR != ANTCTL_H_MAJOR) || \
     (ANTCTL_C_MINOR != ANTCTL_H_MINOR) || \
     (ANTCTL_C_PATCH != ANTCTL_H_PATCH))
#error "AntCtl.c and AntCtl.h : source and header files are inconsistent!"
#endif
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define   ANTCTL_TASK_TIME                  (1U)      /*ExtSigCtrlのタスク周期*/

#define   ANTCTL_DETECT_STS_UNDEF           (0U)      /*接続状態：未確定*/
#define   ANTCTL_DETECT_STS_DISCONECT       (1U)      /*接続状態：接続なし*/
#define   ANTCTL_DETECT_STS_CONECT          (2U)      /*接続状態：接続あり*/
#define   ANTCTL_DETECT_STS_SHORT           (3U)      /*接続状態：ショート*/

#define   ANTCTL_DTC_STS_FAIL               (0U)
#define   ANTCTL_DTC_STS_NML                (1U)

#define   ANTCTL_DIO_LOW                    (0U)
#define   ANTCTL_DIO_HIGH                   (1U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define   ANTCTL_POLL_START_TIME            (400U / ANTCTL_TASK_TIME)    /*各アンテナONからポーリング開始までの時間（BT-WIFIアンテナ以外）*/
#define   ANtCTL_BT_WIFI_POLLSTART_TIME     (100U / ANTCTL_TASK_TIME)    /*BT-WIFIアンテナONからポーリング開始までの時間*/
#define   ANTCTL_POLL_CHK_TIME              (100U / ANTCTL_TASK_TIME)    /*ポーリング周期*/
#define   ANTCTL_REBOOT_WAIT_TIME           (50U / ANTCTL_TASK_TIME)     /*フェール時のアンテナ=Low保持時間*/

#define   ANTCTL_STS_SET_CNT                (10U)     /*アンテナ接続状態確定回数*/

/*AD値の閾値*/
/*GPS*/
#define   ANTCTL_GPS_DET_ON                 (0x0C8DU)
#define   ANTCTL_GPS_DET_OFF                (0x0444U)
/*OTH仕向け*/
#ifdef ANTCTL_DAB
/*DAB*/
#define   ANTCTL_DAB_DET_ON                 (0x0C8DU)
#define   ANTCTL_DAB_DET_OFF                (0x0444U)
#endif
/*JP仕向け*/
#ifdef ANTCTL_DTV
/*DTV*/
#define   ANTCTL_DTV_DET_ON                 (0x0C8DU)
#define   ANTCTL_DTV_DET_OFF                (0x0444U)
#endif
/*BT_WIFI*/
#define   ANTCTL_BT_WIFI_DET_ON             (0x0A5FU)

#define   ANTCTL_SHORT_DET_CNT              (3U)          /*ショート検出回数*/

#define   u1_ANTCTL_GET_V33_PERI_ON()       (Dio_ReadChannel(DIO_ID_PORT10_CH2))    /*BT_WIFIポーリングトリガー信号*/
#define   u1_ANTCTL_GET_GPS_ANT_ON()        (Dio_ReadChannel(DIO_ID_APORT4_CH2))    /*GPSポーリングトリガー信号*/
/*OTH仕向け*/
#ifdef ANTCTL_DAB
#define   u1_ANTCTL_GET_DAB_ANT_ON()        (Dio_ReadChannel(DIO_ID_PORT11_CH4))    /*DABポーリングトリガー信号*/
#endif
/*JP仕向け*/
#ifdef ANTCTL_DTV
#define   u1_ANTCTL_GET_DTV_ANT_ON()        (Dio_ReadChannel(DIO_ID_PORT11_CH4))    /*DTVポーリングトリガー信号*/
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U2       u2_poll_start_tim;           /*サンプリング開始カウント*/
    U2       u2_poll_det_tim;             /*サンプリング周期カウント*/
    U1       u1_fail_flg;                 /*フェール処理開始フラグ*/
    U1       u1_antena_reboot_flg;        /*アンテナ再起動フラグ*/
    U1       u1_antena_reboot_wait_time;  /*アンテナ再起動までのウェイトタイム*/
}ST_ANTCTL;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_ANTCTL    st_s_antctl_gnss;
/*OTH仕向け*/
#ifdef ANTCTL_DAB
static ST_ANTCTL    st_s_antctl_dab;
#endif
/*JP仕向け*/
#ifdef ANTCTL_DTV
static ST_ANTCTL    st_s_antctl_dtv;
#endif
static ST_ANTCTL    st_s_antctl_btwifi;

static U1 u1_s_gnss_poll_cnt;                   /*GPSアンテナサンプリング回数（同じ状態）*/
static U1 u1_s_gnss_det_sts_pre;                /*GPSアンテナ検出状態（前回値）*/
static U1 u1_s_gnss_short_cnt;                  /*GPSアンテナショート検知回数*/
static U1 u1_s_gnss_confirm_sts;                /*GPSアンテナ状態確定後のステータス*/
static U1 u1_s_gnss_confirm_sts_pre;            /*GPSアンテナ状態確定後のステータス(前回状態)*/
static U1 u1_s_gnss_dtc_short_flg;              /*GPSアンテナDTC（ショート）検知フラグ*/
static U1 u1_s_gnss_dtc_open_flg;               /*GPSアンテナDTC（未接続）検知フラグ*/
#ifdef ANTCTL_DAB
static U1 u1_s_dab1_poll_cnt;                   /*DAB1アンテナサンプリング回数（同じ状態）*/
static U1 u1_s_dab1_det_sts_pre;                /*DAB1アンテナ検出状態（前回値）*/
static U1 u1_s_dab1_short_cnt;                  /*DAB1アンテナショート検知回数*/
static U1 u1_s_dab2_poll_cnt;                   /*DAB2アンテナサンプリング回数（同じ状態）*/
static U1 u1_s_dab2_det_sts_pre;                /*DAB2アンテナ検出状態（前回値）*/
static U1 u1_s_dab2_short_cnt;                  /*DAB2アンテナショート検知回数*/
#endif
#ifdef ANTCTL_DTV
static U1 u1_s_dtv1_poll_cnt;                   /*DTV1アンテナサンプリング回数（同じ状態）*/
static U1 u1_s_dtv1_det_sts_pre;                /*DTV1アンテナ検出状態（前回値）*/
static U1 u1_s_dtv1_short_cnt;                  /*DTV1アンテナショート検知回数*/
static U1 u1_s_dtv2_poll_cnt;                   /*DTV2アンテナサンプリング回数（同じ状態）*/
static U1 u1_s_dtv2_det_sts_pre;                /*DTV2アンテナ検出状態（前回値）*/
static U1 u1_s_dtv2_short_cnt;                  /*DTV2アンテナショート検知回数*/
static U1 u1_s_dtv3_poll_cnt;                   /*DTV3アンテナサンプリング回数（同じ状態）*/
static U1 u1_s_dtv3_det_sts_pre;                /*DTV3アンテナ検出状態（前回値）*/
static U1 u1_s_dtv3_short_cnt;                  /*DTV3アンテナショート検知回数*/
static U1 u1_s_dtv4_poll_cnt;                   /*DTV4アンテナサンプリング回数（同じ状態）*/
static U1 u1_s_dtv4_det_sts_pre;                /*DTV4アンテナ検出状態（前回値）*/
static U1 u1_s_dtv4_short_cnt;                  /*DTV4アンテナショート検知回数*/
#endif
static U1 u1_s_btwifi1_poll_cnt;                /*BT-WiFi1アンテナサンプリング回数（同じ状態）*/
static U1 u1_s_btwifi1_det_sts_pre;             /*BT-WiFi1アンテナ検出状態（前回値）*/
static U1 u1_s_btwifi2_poll_cnt;                /*BT-WiFi2アンテナサンプリング回数（同じ状態）*/
static U1 u1_s_btwifi2_det_sts_pre;             /*BT-WiFi2アンテナ検出状態（前回値）*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void vd_s_Ant_Gnss_Poll(void);
static void vd_s_Ant_GNSS_AdcStsDetermine(const U2 u2_a_VALUE);
#ifdef ANTCTL_DAB
static void vd_s_Ant_DAB_Poll(void);
static void vd_s_Ant_DAB1_AdcStsDetermine(const U2 u2_a_VALUE);
static void vd_s_Ant_DAB2_AdcStsDetermine(const U2 u2_a_VALUE);
#endif
#ifdef ANTCTL_DTV
static void vd_s_Ant_DTV_Poll(void);
static void vd_s_Ant_DTV1_AdcStsDetermine(const U2 u2_a_VALUE);
static void vd_s_Ant_DTV2_AdcStsDetermine(const U2 u2_a_VALUE);
static void vd_s_Ant_DTV3_AdcStsDetermine(const U2 u2_a_VALUE);
static void vd_s_Ant_DTV4_AdcStsDetermine(const U2 u2_a_VALUE);
#endif
static void vd_s_Ant_BTWIFI_Poll(void);
static void vd_s_Ant_BTWIFI1_AdcStsDetermine(const U2 u2_a_VALUE);
static void vd_s_Ant_BTWIFI2_AdcStsDetermine(const U2 u2_a_VALUE);
static void vd_s_Ant_Gnss_Fail(void);
#ifdef ANTCTL_DAB
static void vd_s_Ant_DAB_Fail(void);
#endif
#ifdef ANTCTL_DTV
static void vd_s_Ant_DTV_Fail(void);
#endif
static void vd_s_Ant_Gnss_Reboot(void);
#ifdef ANTCTL_DAB
static void vd_s_Ant_DAB_Reboot(void);
#endif
#ifdef ANTCTL_DTV
static void vd_s_Ant_DTV_Reboot(void);
#endif

static U1 u1_s_Ant_TimChk(const U2 u2_a_TIM_CINT, const U2 u2_a_WAIT_TIM);

/*===================================================================================================================================*/
/*  void            vd_g_Ant_Init(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    初期化関数(B-ON)                                                                                                  */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_Ant_Init(void)
{
    /*初期化処理*/
    st_s_antctl_gnss.u2_poll_start_tim = (U2)0U;
    st_s_antctl_gnss.u2_poll_det_tim = (U2)0U;
    st_s_antctl_gnss.u1_fail_flg = (U1)FALSE;
    st_s_antctl_gnss.u1_antena_reboot_flg = (U1)FALSE;
    st_s_antctl_gnss.u1_antena_reboot_wait_time = (U1)0U;
    u1_s_gnss_dtc_short_flg = (U1)FALSE;
    u1_s_gnss_dtc_open_flg = (U1)FALSE;
#ifdef ANTCTL_DAB
    st_s_antctl_dab.u2_poll_start_tim = (U2)0U;
    st_s_antctl_dab.u2_poll_det_tim = (U2)0U;
    st_s_antctl_dab.u1_fail_flg = (U1)FALSE;
    st_s_antctl_dab.u1_antena_reboot_flg = (U1)FALSE;
    st_s_antctl_dab.u1_antena_reboot_wait_time = (U1)0U;
#endif
#ifdef ANTCTL_DTV
    st_s_antctl_dtv.u2_poll_start_tim = (U2)0U;
    st_s_antctl_dtv.u2_poll_det_tim = (U2)0U;
    st_s_antctl_dtv.u1_fail_flg = (U1)FALSE;
    st_s_antctl_dtv.u1_antena_reboot_flg = (U1)FALSE;
    st_s_antctl_dtv.u1_antena_reboot_wait_time = (U1)0U;
#endif
    st_s_antctl_btwifi.u2_poll_start_tim = (U2)0U;
    st_s_antctl_btwifi.u2_poll_det_tim = (U2)0U;
    st_s_antctl_btwifi.u1_fail_flg = (U1)FALSE;
    st_s_antctl_btwifi.u1_antena_reboot_flg = (U1)FALSE;
    st_s_antctl_btwifi.u1_antena_reboot_wait_time = (U1)0U;

    u1_s_gnss_poll_cnt = (U1)0U;
    u1_s_gnss_det_sts_pre = (U1)ANTCTL_DETECT_STS_UNDEF;
    u1_s_gnss_short_cnt = (U1)0U;
    u1_s_gnss_confirm_sts = (U1)ANTCTL_DETECT_STS_UNDEF;
    u1_s_gnss_confirm_sts_pre = (U1)ANTCTL_DETECT_STS_UNDEF;
#ifdef ANTCTL_DAB
    u1_s_dab1_poll_cnt = (U1)0U;
    u1_s_dab1_det_sts_pre = (U1)ANTCTL_DETECT_STS_UNDEF;
    u1_s_dab1_short_cnt = (U1)0U;
    u1_s_dab2_poll_cnt = (U1)0U;
    u1_s_dab2_det_sts_pre = (U1)ANTCTL_DETECT_STS_UNDEF;
    u1_s_dab2_short_cnt = (U1)0U;
#endif
#ifdef ANTCTL_DTV
    u1_s_dtv1_poll_cnt = (U1)0U;
    u1_s_dtv1_det_sts_pre = (U1)ANTCTL_DETECT_STS_UNDEF;
    u1_s_dtv1_short_cnt = (U1)0U;
    u1_s_dtv2_poll_cnt = (U1)0U;
    u1_s_dtv2_det_sts_pre = (U1)ANTCTL_DETECT_STS_UNDEF;
    u1_s_dtv2_short_cnt = (U1)0U;
    u1_s_dtv3_poll_cnt = (U1)0U;
    u1_s_dtv3_det_sts_pre = (U1)ANTCTL_DETECT_STS_UNDEF;
    u1_s_dtv3_short_cnt = (U1)0U;
    u1_s_dtv4_poll_cnt = (U1)0U;
    u1_s_dtv4_det_sts_pre = (U1)ANTCTL_DETECT_STS_UNDEF;
    u1_s_dtv4_short_cnt = (U1)0U;
#endif
    u1_s_btwifi1_poll_cnt = (U1)0U;
    u1_s_btwifi1_det_sts_pre = (U1)ANTCTL_DETECT_STS_UNDEF;
    u1_s_btwifi2_poll_cnt = (U1)0U;
    u1_s_btwifi2_det_sts_pre = (U1)ANTCTL_DETECT_STS_UNDEF;
}

/*===================================================================================================================================*/
/*  void            vd_g_Ant_MainTask(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    メインタスク                                                                                                      */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_Ant_MainTask(void)
{

    /*アンテナ再起動処理*/
    /*GPS*/
    if(st_s_antctl_gnss.u1_antena_reboot_flg == (U1)TRUE) {
        vd_s_Ant_Gnss_Reboot();
    }
#ifdef ANTCTL_DAB
    /*DAB*/
    if(st_s_antctl_dab.u1_antena_reboot_flg == (U1)TRUE) {
        vd_s_Ant_DAB_Reboot();
    }
#endif
#ifdef ANTCTL_DTV
    /*DTV*/
    if(st_s_antctl_dtv.u1_antena_reboot_flg == (U1)TRUE) {
        vd_s_Ant_DTV_Reboot();
    }
#endif

    /*ポーリング処理*/
    vd_s_Ant_Gnss_Poll();
#ifdef ANTCTL_DAB
    vd_s_Ant_DAB_Poll();   /*OTH仕向け*/
#endif
#ifdef ANTCTL_DTV
    vd_s_Ant_DTV_Poll();   /*JP仕向け*/
#endif
    vd_s_Ant_BTWIFI_Poll();

    /*DTC記録処理 未接続時*/
    /*GPS*/
    if((u1_s_gnss_confirm_sts != u1_s_gnss_confirm_sts_pre) &&
       (u1_s_gnss_confirm_sts == (U1)ANTCTL_DETECT_STS_DISCONECT)) {
        /*未接続判定した場合にDTC記録する*/
        vd_g_DtcCtl_SetDtcId((U1)DTCCTL_DTCID_GNSS_OPEN, (U1)ANTCTL_DTC_STS_FAIL);
        u1_s_gnss_dtc_open_flg = (U1)TRUE;
        u1_s_gnss_confirm_sts_pre = u1_s_gnss_confirm_sts;
    }

    /*フェール処理*/
    /*GPS*/
    if(st_s_antctl_gnss.u1_fail_flg == (U1)TRUE) {
        vd_s_Ant_Gnss_Fail();
    }
#ifdef ANTCTL_DAB
    /*DAB*/
    if(st_s_antctl_dab.u1_fail_flg == (U1)TRUE) {
        vd_s_Ant_DAB_Fail();
    }
#endif
#ifdef ANTCTL_DTV
    /*DTV*/
    if(st_s_antctl_dtv.u1_fail_flg == (U1)TRUE) {
        vd_s_Ant_DTV_Fail();
    }
#endif
}

/*===================================================================================================================================*/
/*  static void vd_s_Ant_Gnss_Poll(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    GNSSアンテナのポーリング処理                                                                                       */
/*  Arguments:      u1_a_DATA AD値から判断した接続状態                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Ant_Gnss_Poll(void)
{
    U1    u1_t_ant_sts;
    U1    u1_t_poll_start_flg;
    U1    u1_t_poll_time_chk;
    U1    u1_t_read_adc_sts;
    U1    u1_t_adc_det_sts;
    U2    u2_t_adc_det_val;

    /*各アンテナのON/OFF確認し、ポーリング処理実施 ONから400ms後にポーリング開始*/
    u1_t_ant_sts = u1_ANTCTL_GET_GPS_ANT_ON();
    if(u1_t_ant_sts == (U1)TRUE) {
        if(st_s_antctl_gnss.u2_poll_start_tim < (U2)U2_MAX) {
            st_s_antctl_gnss.u2_poll_start_tim++;
        }
    } else {
        st_s_antctl_gnss.u2_poll_start_tim = (U2)0U;
    }

    u1_t_poll_start_flg = u1_s_Ant_TimChk(st_s_antctl_gnss.u2_poll_start_tim,(U2)ANTCTL_POLL_START_TIME);
    if(u1_t_poll_start_flg == (U1)TRUE) {
        u1_t_poll_time_chk = u1_s_Ant_TimChk(st_s_antctl_gnss.u2_poll_det_tim,(U2)ANTCTL_POLL_CHK_TIME);
        if(u1_t_poll_time_chk == (U1)TRUE) {
            u1_t_read_adc_sts = u1_g_IoHwAdcRead((U1)ADC_CH_GPS_ANT,&u2_t_adc_det_val);
            if(u1_t_read_adc_sts == (U1)TRUE) {
                vd_s_Ant_GNSS_AdcStsDetermine(u2_t_adc_det_val);
            }
        }
    } else {
        u1_s_gnss_det_sts_pre = (U1)ANTCTL_DETECT_STS_UNDEF;
        u1_s_gnss_poll_cnt = (U1)0U;
    }

    st_s_antctl_gnss.u2_poll_det_tim++;
}
/*===================================================================================================================================*/
/*  static void vd_s_Ant_GNSS_AdcStsDetermine(const U2 u2_a_VALUE)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    GNSSアンテナの状態確定                                                                                             */
/*  Arguments:      u2_a_VALUE AD値                                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Ant_GNSS_AdcStsDetermine(const U2 u2_a_VALUE)
{
    U1    u1_t_adc_det_sts;

    if(u2_a_VALUE >= (U2)ANTCTL_GPS_DET_ON){
        u1_t_adc_det_sts = (U1)ANTCTL_DETECT_STS_CONECT;
    } else if(u2_a_VALUE >= (U2)ANTCTL_GPS_DET_OFF) {
        u1_t_adc_det_sts = (U1)ANTCTL_DETECT_STS_DISCONECT;
    } else {
        u1_t_adc_det_sts = (U1)ANTCTL_DETECT_STS_SHORT;
    }

    if(u1_t_adc_det_sts != u1_s_gnss_det_sts_pre) {
        u1_s_gnss_poll_cnt = (U1)1U;
    } else {
        if(u1_s_gnss_poll_cnt < (U1)U1_MAX) {
            u1_s_gnss_poll_cnt++;
        }
    }

    if(u1_s_gnss_poll_cnt >= (U1)ANTCTL_STS_SET_CNT) {
        if(u1_t_adc_det_sts != (U1)ANTCTL_DETECT_STS_SHORT) {
            u1_s_gnss_short_cnt = 0U;
        } else {
            u1_s_gnss_short_cnt++;
            st_s_antctl_gnss.u1_fail_flg = (U1)TRUE;
        }
        if(u1_t_adc_det_sts == (U1)ANTCTL_DETECT_STS_CONECT) {
            /*未接続からの正常復帰*/
            if(u1_s_gnss_dtc_open_flg == (U1)TRUE) {
                vd_g_DtcCtl_SetDtcId((U1)DTCCTL_DTCID_GNSS_OPEN, (U1)ANTCTL_DTC_STS_NML);
                u1_s_gnss_dtc_open_flg = (U1)FALSE;
            }
            /*ショートからの正常復帰*/
            if(u1_s_gnss_dtc_short_flg == (U1)TRUE) {
                vd_g_DtcCtl_SetDtcId((U1)DTCCTL_DTCID_GNSS_LOW, (U1)ANTCTL_DTC_STS_NML);
                u1_s_gnss_dtc_short_flg = (U1)FALSE;
            }
        }
        vd_g_XspiIviSub1ExtSgnlPut((U1)XSPI_IVI_EXTSIG_GNSS,u1_t_adc_det_sts);
        u1_s_gnss_confirm_sts_pre = u1_s_gnss_confirm_sts;
        u1_s_gnss_confirm_sts = u1_t_adc_det_sts;
    }
    u1_s_gnss_det_sts_pre = u1_t_adc_det_sts;
    st_s_antctl_gnss.u2_poll_det_tim = (U2)0U;

}

#ifdef ANTCTL_DAB
/*===================================================================================================================================*/
/*  static void vd_s_Ant_DAB_Poll(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    DABアンテナのポーリング処理                                                                                        */
/*  Arguments:      u1_a_DATA AD値から判断した接続状態                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Ant_DAB_Poll(void)
{
    U1    u1_t_ant_sts;
    U1    u1_t_poll_start_flg;
    U1    u1_t_poll_time_chk;
    U1    u1_t_read_adc_sts;
    U1    u1_t_dab1_det_sts;
    U2    u2_t_dab1_det_val;
    U1    u1_t_dab2_det_sts;
    U2    u2_t_dab2_det_val;

    /*各アンテナのON/OFF確認し、ポーリング処理実施 ONから400ms後にポーリング開始*/
    u1_t_ant_sts = u1_ANTCTL_GET_DAB_ANT_ON();
    if(u1_t_ant_sts == (U1)TRUE) {
        if(st_s_antctl_dab.u2_poll_start_tim < (U2)U2_MAX) {
            st_s_antctl_dab.u2_poll_start_tim++;
        }
    } else {
        st_s_antctl_dab.u2_poll_start_tim = (U2)0U;
    }

    u1_t_poll_start_flg = u1_s_Ant_TimChk(st_s_antctl_dab.u2_poll_start_tim,(U2)ANTCTL_POLL_START_TIME);
    if(u1_t_poll_start_flg == (U1)TRUE) {
        u1_t_poll_time_chk = u1_s_Ant_TimChk(st_s_antctl_dab.u2_poll_det_tim,(U2)ANTCTL_POLL_CHK_TIME);
        if(u1_t_poll_time_chk == (U1)TRUE) {
            /*DAB1アンテナのポーリング処理*/
            u1_t_read_adc_sts = u1_g_IoHwAdcRead((U1)ADC_CH_DAB_ANT1,&u2_t_dab1_det_val);
            if(u1_t_read_adc_sts == (U1)TRUE) {
                vd_s_Ant_DAB1_AdcStsDetermine(u2_t_dab1_det_val);
            }

            /*DAB2アンテナのポーリング処理*/
            u1_t_read_adc_sts = u1_g_IoHwAdcRead((U1)ADC_CH_DAB_ANT2,&u2_t_dab2_det_val);
            if(u1_t_read_adc_sts == (U1)TRUE) {
                vd_s_Ant_DAB2_AdcStsDetermine(u2_t_dab2_det_val);
            }
        }
    } else {
        u1_s_dab1_det_sts_pre = (U1)ANTCTL_DETECT_STS_UNDEF;
        u1_s_dab2_det_sts_pre = (U1)ANTCTL_DETECT_STS_UNDEF;
        u1_s_dab1_poll_cnt = (U1)0U;
        u1_s_dab2_poll_cnt = (U1)0U;
    }

    st_s_antctl_dab.u2_poll_det_tim++;
}

/*===================================================================================================================================*/
/*  static void vd_s_Ant_DAB1_AdcStsDetermine(const U2 u2_a_VALUE)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    DAB1アンテナの状態確定                                                                                             */
/*  Arguments:      u2_a_VALUE AD値                                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Ant_DAB1_AdcStsDetermine(const U2 u2_a_VALUE)
{
    U1    u1_t_dab1_det_sts;

    if(u2_a_VALUE >= (U2)ANTCTL_DAB_DET_ON){
        u1_t_dab1_det_sts = (U1)ANTCTL_DETECT_STS_CONECT;
    } else if(u2_a_VALUE >= (U2)ANTCTL_DAB_DET_OFF) {
        u1_t_dab1_det_sts = (U1)ANTCTL_DETECT_STS_DISCONECT;
    } else {
        u1_t_dab1_det_sts = (U1)ANTCTL_DETECT_STS_SHORT;
    }

    if(u1_t_dab1_det_sts != u1_s_dab1_det_sts_pre) {
        u1_s_dab1_poll_cnt = (U1)1U;
    } else {
        if(u1_s_dab1_poll_cnt < (U1)U1_MAX) {
            u1_s_dab1_poll_cnt++;
        }
    }

    if(u1_s_dab1_poll_cnt >= (U1)ANTCTL_STS_SET_CNT) {
        if(u1_t_dab1_det_sts != (U1)ANTCTL_DETECT_STS_SHORT) {
            u1_s_dab1_short_cnt = 0U;
        } else {
            u1_s_dab1_short_cnt++;
            st_s_antctl_dab.u1_fail_flg = (U1)TRUE;
        }
        vd_g_XspiIviSub1ExtSgnlPut((U1)XSPI_IVI_EXTSIG_DAB,u1_t_dab1_det_sts);
    }
    u1_s_dab1_det_sts_pre = u1_t_dab1_det_sts;
    st_s_antctl_dab.u2_poll_det_tim = (U2)0U;

}

/*===================================================================================================================================*/
/*  static void vd_s_Ant_DAB2_AdcStsDetermine(const U2 u2_a_VALUE)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    DAB2アンテナの状態確定                                                                                             */
/*  Arguments:      u2_a_VALUE AD値                                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Ant_DAB2_AdcStsDetermine(const U2 u2_a_VALUE)
{
    U1    u1_t_dab2_det_sts;

    if(u2_a_VALUE >= (U2)ANTCTL_DAB_DET_ON){
        u1_t_dab2_det_sts = (U1)ANTCTL_DETECT_STS_CONECT;
    } else if(u2_a_VALUE >= (U2)ANTCTL_DAB_DET_OFF) {
        u1_t_dab2_det_sts = (U1)ANTCTL_DETECT_STS_DISCONECT;
    } else {
        u1_t_dab2_det_sts = (U1)ANTCTL_DETECT_STS_SHORT;
    }

    if(u1_t_dab2_det_sts != u1_s_dab2_det_sts_pre) {
        u1_s_dab2_poll_cnt = (U1)1U;
    } else {
        if(u1_s_dab2_poll_cnt < (U1)U1_MAX) {
            u1_s_dab2_poll_cnt++;
        }
    }

    if(u1_s_dab2_poll_cnt >= (U1)ANTCTL_STS_SET_CNT) {
        if(u1_t_dab2_det_sts != (U1)ANTCTL_DETECT_STS_SHORT) {
            u1_s_dab2_short_cnt = 0U;
        } else {
            u1_s_dab2_short_cnt++;
            st_s_antctl_dab.u1_fail_flg = (U1)TRUE;
        }

        if(u1_t_dab2_det_sts == (U1)ANTCTL_DETECT_STS_DISCONECT) {
            vd_g_XspiIviSub1ExtSgnlPut((U1)XSPI_IVI_EXTSIG_DAB2,(U1)ANTCTL_DETECT_STS_UNDEF);
        } else {
            vd_g_XspiIviSub1ExtSgnlPut((U1)XSPI_IVI_EXTSIG_DAB2,u1_t_dab2_det_sts);
        }
    }
    u1_s_dab2_det_sts_pre = u1_t_dab2_det_sts;
    st_s_antctl_dab.u2_poll_det_tim = (U2)0U;

}

#endif

#ifdef ANTCTL_DTV
/*===================================================================================================================================*/
/*  static void vd_s_Ant_DTV_Poll(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    DTVアンテナのポーリング処理                                                                                        */
/*  Arguments:      u1_a_DATA AD値から判断した接続状態                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Ant_DTV_Poll(void)
{
    U1    u1_t_ant_sts;
    U1    u1_t_poll_start_flg;
    U1    u1_t_poll_time_chk;
    U1    u1_t_read_adc_sts;
    U1    u1_t_dtv1_det_sts;
    U2    u2_t_dtv1_det_val;
    U1    u1_t_dtv2_det_sts;
    U2    u2_t_dtv2_det_val;
    U1    u1_t_dtv3_det_sts;
    U2    u2_t_dtv3_det_val;
    U1    u1_t_dtv4_det_sts;
    U2    u2_t_dtv4_det_val;

    /*各アンテナのON/OFF確認し、ポーリング処理実施 ONから400ms後にポーリング開始*/
    u1_t_ant_sts = u1_ANTCTL_GET_DTV_ANT_ON();
    if(u1_t_ant_sts == (U1)TRUE) {
        if(st_s_antctl_dtv.u2_poll_start_tim < (U2)U2_MAX) {
            st_s_antctl_dtv.u2_poll_start_tim++;
        }
    } else {
        st_s_antctl_dtv.u2_poll_start_tim = (U2)0U;
    }

    u1_t_poll_start_flg = u1_s_Ant_TimChk(st_s_antctl_dtv.u2_poll_start_tim,(U2)ANTCTL_POLL_START_TIME);
    if(u1_t_poll_start_flg == (U1)TRUE) {
        u1_t_poll_time_chk = u1_s_Ant_TimChk(st_s_antctl_dtv.u2_poll_det_tim,(U2)ANTCTL_POLL_CHK_TIME);
        if(u1_t_poll_time_chk == (U1)TRUE) {
            /*DTV1アンテナのポーリング処理*/
            u1_t_read_adc_sts = u1_g_IoHwAdcRead((U1)ADC_CH_DTV_ANT1,&u2_t_dtv1_det_val);
            if(u1_t_read_adc_sts == (U1)TRUE) {
                vd_s_Ant_DTV1_AdcStsDetermine(u2_t_dtv1_det_val);
            }

            /*DTV2アンテナのポーリング処理*/
            u1_t_read_adc_sts = u1_g_IoHwAdcRead((U1)ADC_CH_DTV_ANT2,&u2_t_dtv2_det_val);
            if(u1_t_read_adc_sts == (U1)TRUE) {
                vd_s_Ant_DTV2_AdcStsDetermine(u2_t_dtv2_det_val);
            }

            /*DTV3アンテナのポーリング処理*/
            u1_t_read_adc_sts = u1_g_IoHwAdcRead((U1)ADC_CH_DTV_ANT3,&u2_t_dtv3_det_val);
            if(u1_t_read_adc_sts == (U1)TRUE) {
                vd_s_Ant_DTV3_AdcStsDetermine(u2_t_dtv3_det_val);
            }

            /*DTV4アンテナのポーリング処理*/
            u1_t_read_adc_sts = u1_g_IoHwAdcRead((U1)ADC_CH_DTV_ANT4,&u2_t_dtv4_det_val);
            if(u1_t_read_adc_sts == (U1)TRUE) {
                vd_s_Ant_DTV4_AdcStsDetermine(u2_t_dtv4_det_val);
            }
        }
    } else {
        u1_s_dtv1_det_sts_pre = (U1)ANTCTL_DETECT_STS_UNDEF;
        u1_s_dtv2_det_sts_pre = (U1)ANTCTL_DETECT_STS_UNDEF;
        u1_s_dtv3_det_sts_pre = (U1)ANTCTL_DETECT_STS_UNDEF;
        u1_s_dtv4_det_sts_pre = (U1)ANTCTL_DETECT_STS_UNDEF;
        u1_s_dtv1_poll_cnt = (U1)0U;
        u1_s_dtv2_poll_cnt = (U1)0U;
        u1_s_dtv3_poll_cnt = (U1)0U;
        u1_s_dtv4_poll_cnt = (U1)0U;
    }

    st_s_antctl_dtv.u2_poll_det_tim++;
}

/*===================================================================================================================================*/
/*  static void vd_s_Ant_DTV1_AdcStsDetermine(const U2 u2_a_VALUE)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    DTV1アンテナの状態確定                                                                                             */
/*  Arguments:      u2_a_VALUE AD値                                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Ant_DTV1_AdcStsDetermine(const U2 u2_a_VALUE)
{
    U1    u1_t_dtv1_det_sts;

    if(u2_a_VALUE >= (U2)ANTCTL_DTV_DET_ON){
        u1_t_dtv1_det_sts = (U1)ANTCTL_DETECT_STS_CONECT;
    } else if(u2_a_VALUE >= (U2)ANTCTL_DTV_DET_OFF) {
        u1_t_dtv1_det_sts = (U1)ANTCTL_DETECT_STS_DISCONECT;
    } else {
        u1_t_dtv1_det_sts = (U1)ANTCTL_DETECT_STS_SHORT;
    }

    if(u1_t_dtv1_det_sts != u1_s_dtv1_det_sts_pre) {
        u1_s_dtv1_poll_cnt = (U1)1U;
    } else {
        if(u1_s_dtv1_poll_cnt < (U1)U1_MAX) {
            u1_s_dtv1_poll_cnt++;
        }
    }

    if(u1_s_dtv1_poll_cnt >= (U1)ANTCTL_STS_SET_CNT) {
        if(u1_t_dtv1_det_sts != (U1)ANTCTL_DETECT_STS_SHORT) {
            u1_s_dtv1_short_cnt = 0U;
        } else {
            u1_s_dtv1_short_cnt++;
            st_s_antctl_dtv.u1_fail_flg = (U1)TRUE;
        }
        vd_g_XspiIviSub1ExtSgnlPut((U1)XSPI_IVI_EXTSIG_DTV,u1_t_dtv1_det_sts);
    }
    u1_s_dtv1_det_sts_pre = u1_t_dtv1_det_sts;
    st_s_antctl_dtv.u2_poll_det_tim = (U2)0U;

}

/*===================================================================================================================================*/
/*  static void vd_s_Ant_DTV2_AdcStsDetermine(const U2 u2_a_VALUE)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    DTV2アンテナの状態確定                                                                                             */
/*  Arguments:      u2_a_VALUE AD値                                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Ant_DTV2_AdcStsDetermine(const U2 u2_a_VALUE)
{
    U1    u1_t_dtv2_det_sts;

    if(u2_a_VALUE >= (U2)ANTCTL_DTV_DET_ON){
        u1_t_dtv2_det_sts = (U1)ANTCTL_DETECT_STS_CONECT;
    } else if(u2_a_VALUE >= (U2)ANTCTL_DTV_DET_OFF) {
        u1_t_dtv2_det_sts = (U1)ANTCTL_DETECT_STS_DISCONECT;
    } else {
        u1_t_dtv2_det_sts = (U1)ANTCTL_DETECT_STS_SHORT;
    }

    if(u1_t_dtv2_det_sts != u1_s_dtv2_det_sts_pre) {
        u1_s_dtv2_poll_cnt = (U1)1U;
    } else {
        if(u1_s_dtv2_poll_cnt < (U1)U1_MAX) {
            u1_s_dtv2_poll_cnt++;
        }
    }

    if(u1_s_dtv2_poll_cnt >= (U1)ANTCTL_STS_SET_CNT) {
        if(u1_t_dtv2_det_sts != (U1)ANTCTL_DETECT_STS_SHORT) {
            u1_s_dtv2_short_cnt = 0U;
        } else {
            u1_s_dtv2_short_cnt++;
            st_s_antctl_dtv.u1_fail_flg = (U1)TRUE;
        }
        vd_g_XspiIviSub1ExtSgnlPut((U1)XSPI_IVI_EXTSIG_DTV2,u1_t_dtv2_det_sts);
    }
    u1_s_dtv2_det_sts_pre = u1_t_dtv2_det_sts;
    st_s_antctl_dtv.u2_poll_det_tim = (U2)0U;
}

/*===================================================================================================================================*/
/*  static void vd_s_Ant_DTV3_AdcStsDetermine(const U2 u2_a_VALUE)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    DTV3アンテナの状態確定                                                                                             */
/*  Arguments:      u2_a_VALUE AD値                                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Ant_DTV3_AdcStsDetermine(const U2 u2_a_VALUE)
{
    U1    u1_t_dtv3_det_sts;

    if(u2_a_VALUE >= (U2)ANTCTL_DTV_DET_ON){
        u1_t_dtv3_det_sts = (U1)ANTCTL_DETECT_STS_CONECT;
    } else if(u2_a_VALUE >= (U2)ANTCTL_DTV_DET_OFF) {
        u1_t_dtv3_det_sts = (U1)ANTCTL_DETECT_STS_DISCONECT;
    } else {
        u1_t_dtv3_det_sts = (U1)ANTCTL_DETECT_STS_SHORT;
    }

    if(u1_t_dtv3_det_sts != u1_s_dtv3_det_sts_pre) {
        u1_s_dtv3_poll_cnt = (U1)1U;
    } else {
        if(u1_s_dtv3_poll_cnt < (U1)U1_MAX) {
            u1_s_dtv3_poll_cnt++;
        }
    }

    if(u1_s_dtv3_poll_cnt >= (U1)ANTCTL_STS_SET_CNT) {
        if(u1_t_dtv3_det_sts != (U1)ANTCTL_DETECT_STS_SHORT) {
            u1_s_dtv3_short_cnt = 0U;
        } else {
            u1_s_dtv3_short_cnt++;
            st_s_antctl_dtv.u1_fail_flg = (U1)TRUE;
        }
        vd_g_XspiIviSub1ExtSgnlPut((U1)XSPI_IVI_EXTSIG_DTV3,u1_t_dtv3_det_sts);
    }
    u1_s_dtv3_det_sts_pre = u1_t_dtv3_det_sts;
    st_s_antctl_dtv.u2_poll_det_tim = (U2)0U;
}

/*===================================================================================================================================*/
/*  static void vd_s_Ant_DTV4_AdcStsDetermine(const U2 u2_a_VALUE)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    DTV4アンテナの状態確定                                                                                             */
/*  Arguments:      u2_a_VALUE AD値                                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Ant_DTV4_AdcStsDetermine(const U2 u2_a_VALUE)
{
    U1    u1_t_dtv4_det_sts;

    if(u2_a_VALUE >= (U2)ANTCTL_DTV_DET_ON){
        u1_t_dtv4_det_sts = (U1)ANTCTL_DETECT_STS_CONECT;
    } else if(u2_a_VALUE >= (U2)ANTCTL_DTV_DET_OFF) {
        u1_t_dtv4_det_sts = (U1)ANTCTL_DETECT_STS_DISCONECT;
    } else {
        u1_t_dtv4_det_sts = (U1)ANTCTL_DETECT_STS_SHORT;
    }

    if(u1_t_dtv4_det_sts != u1_s_dtv4_det_sts_pre) {
        u1_s_dtv4_poll_cnt = (U1)1U;
    } else {
        if(u1_s_dtv4_poll_cnt < (U1)U1_MAX) {
            u1_s_dtv4_poll_cnt++;
        }
    }

    if(u1_s_dtv4_poll_cnt >= (U1)ANTCTL_STS_SET_CNT) {
        if(u1_t_dtv4_det_sts != (U1)ANTCTL_DETECT_STS_SHORT) {
            u1_s_dtv4_short_cnt = 0U;
        } else {
            u1_s_dtv4_short_cnt++;
            st_s_antctl_dtv.u1_fail_flg = (U1)TRUE;
        }
        vd_g_XspiIviSub1ExtSgnlPut((U1)XSPI_IVI_EXTSIG_DTV4,u1_t_dtv4_det_sts);
    }
    u1_s_dtv4_det_sts_pre = u1_t_dtv4_det_sts;
    st_s_antctl_dtv.u2_poll_det_tim = (U2)0U;
}
#endif

/*===================================================================================================================================*/
/*  static void vd_s_Ant_BTWIFI_Poll(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    BT/WiFiアンテナのポーリング処理                                                                                    */
/*  Arguments:      u1_a_DATA AD値から判断した接続状態                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Ant_BTWIFI_Poll(void)
{
    U1    u1_t_ant_sts;
    U1    u1_t_poll_start_flg;
    U1    u1_t_poll_time_chk;
    U1    u1_t_read_adc_sts;
    U1    u1_t_btwifi1_det_sts;
    U2    u2_t_btwifi1_det_val;
    U1    u1_t_btwifi2_det_sts;
    U2    u2_t_btwifi2_det_val;

    /*各アンテナのON/OFF確認し、ポーリング処理実施 ONから400ms後にポーリング開始*/
    u1_t_ant_sts = u1_ANTCTL_GET_V33_PERI_ON();
    if(u1_t_ant_sts == (U1)TRUE) {
        if(st_s_antctl_btwifi.u2_poll_start_tim < (U2)U2_MAX) {
            st_s_antctl_btwifi.u2_poll_start_tim++;
        }
    } else {
        st_s_antctl_btwifi.u2_poll_start_tim = (U2)0U;
    }

    u1_t_poll_start_flg = u1_s_Ant_TimChk(st_s_antctl_btwifi.u2_poll_start_tim,(U2)ANtCTL_BT_WIFI_POLLSTART_TIME);
    if(u1_t_poll_start_flg == (U1)TRUE) {
        u1_t_poll_time_chk = u1_s_Ant_TimChk(st_s_antctl_btwifi.u2_poll_det_tim,(U2)ANTCTL_POLL_CHK_TIME);
        if(u1_t_poll_time_chk == (U1)TRUE) {
            /*BT-WiFI1アンテナのポーリング処理*/
            u1_t_read_adc_sts = u1_g_IoHwAdcRead((U1)ADC_CH_BTWA1,&u2_t_btwifi1_det_val);
            if(u1_t_read_adc_sts == (U1)TRUE) {
                vd_s_Ant_BTWIFI1_AdcStsDetermine(u2_t_btwifi1_det_val);
            }

            /*BT-WiFI2アンテナのポーリング処理*/
            u1_t_read_adc_sts = u1_g_IoHwAdcRead((U1)ADC_CH_BTWA2,&u2_t_btwifi2_det_val);
            if(u1_t_read_adc_sts == (U1)TRUE) {
                vd_s_Ant_BTWIFI2_AdcStsDetermine(u2_t_btwifi2_det_val);
            }
        }
    } else {
        u1_s_btwifi1_det_sts_pre = (U1)ANTCTL_DETECT_STS_UNDEF;
        u1_s_btwifi2_det_sts_pre = (U1)ANTCTL_DETECT_STS_UNDEF;
        u1_s_btwifi1_poll_cnt = (U1)0U;
        u1_s_btwifi2_poll_cnt = (U1)0U;
    }

    st_s_antctl_btwifi.u2_poll_det_tim++;
}

/*===================================================================================================================================*/
/*  static void vd_s_Ant_BTWIFI1_AdcStsDetermine(const U2 u2_a_VALUE)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    BT/WIFI1アンテナの状態確定                                                                                        */
/*  Arguments:      u2_a_VALUE AD値                                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Ant_BTWIFI1_AdcStsDetermine(const U2 u2_a_VALUE)
{
    U1    u1_t_btwifi1_det_sts;

    if(u2_a_VALUE >= (U2)ANTCTL_BT_WIFI_DET_ON){
        u1_t_btwifi1_det_sts = (U1)ANTCTL_DETECT_STS_DISCONECT;
    } else {
        u1_t_btwifi1_det_sts = (U1)ANTCTL_DETECT_STS_CONECT;
    }

    if(u1_t_btwifi1_det_sts != u1_s_btwifi1_det_sts_pre) {
        u1_s_btwifi1_poll_cnt = (U1)1U;
    } else {
        if(u1_s_btwifi1_poll_cnt < (U1)U1_MAX) {
            u1_s_btwifi1_poll_cnt++;
        }
    }

    if(u1_s_btwifi1_poll_cnt >= (U1)ANTCTL_STS_SET_CNT) {
        vd_g_XspiIviSub1ExtSgnlPut((U1)XSPI_IVI_EXTSIG_WIFI,u1_t_btwifi1_det_sts);
    }
    u1_s_btwifi1_det_sts_pre = u1_t_btwifi1_det_sts;
    st_s_antctl_btwifi.u2_poll_det_tim = (U2)0U;

}

/*===================================================================================================================================*/
/*  static void vd_s_Ant_BTWIFI2_AdcStsDetermine(const U2 u2_a_VALUE)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    BT/WIFI2アンテナの状態確定                                                                                        */
/*  Arguments:      u2_a_VALUE AD値                                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Ant_BTWIFI2_AdcStsDetermine(const U2 u2_a_VALUE)
{
    U1    u1_t_btwifi2_det_sts;

    if(u2_a_VALUE >= (U2)ANTCTL_BT_WIFI_DET_ON){
        u1_t_btwifi2_det_sts = (U1)ANTCTL_DETECT_STS_DISCONECT;
    } else {
        u1_t_btwifi2_det_sts = (U1)ANTCTL_DETECT_STS_CONECT;
    }

    if(u1_t_btwifi2_det_sts != u1_s_btwifi2_det_sts_pre) {
        u1_s_btwifi2_poll_cnt = (U1)1U;
    } else {
        if(u1_s_btwifi2_poll_cnt < (U1)U1_MAX) {
            u1_s_btwifi2_poll_cnt++;
        }
    }

    if(u1_s_btwifi2_poll_cnt >= (U1)ANTCTL_STS_SET_CNT) {
        vd_g_XspiIviSub1ExtSgnlPut((U1)XSPI_IVI_EXTSIG_WIFI2,u1_t_btwifi2_det_sts);
    }
    u1_s_btwifi2_det_sts_pre = u1_t_btwifi2_det_sts;
    st_s_antctl_btwifi.u2_poll_det_tim = (U2)0U;

}

/*===================================================================================================================================*/
/*  static void vd_s_Ant_Gnss_Fail(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    GNSSアンテナのフェール処理                                                                                         */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Ant_Gnss_Fail(void)
{
    /*フェール処理*/
    if(u1_s_gnss_short_cnt == (U1)ANTCTL_SHORT_DET_CNT) {
        /*ダイアグにショート検知ログを残す*/
        vd_g_DtcCtl_SetDtcId((U1)DTCCTL_DTCID_GNSS_LOW, (U1)ANTCTL_DTC_STS_FAIL);
        u1_s_gnss_dtc_short_flg = (U1)TRUE;
    }
    Dio_WriteChannel((U2)DIO_ID_APORT4_CH2,(U1)ANTCTL_DIO_LOW);
    st_s_antctl_gnss.u1_antena_reboot_flg = (U1)TRUE;
    st_s_antctl_gnss.u1_fail_flg = (U1)FALSE;
}

#ifdef ANTCTL_DAB
/*===================================================================================================================================*/
/*  static void vd_s_Ant_DAB_Fail(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    DABアンテナのフェール処理                                                                                          */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Ant_DAB_Fail(void)
{
    /*フェール処理*/
    if((u1_s_dab1_short_cnt != (U1)0U) ||
       (u1_s_dab2_short_cnt != (U1)0U)){
        if((u1_s_dab1_short_cnt <= (U1)ANTCTL_SHORT_DET_CNT) ||
           (u1_s_dab2_short_cnt <= (U1)ANTCTL_SHORT_DET_CNT)) {
            Dio_WriteChannel((U2)DIO_ID_PORT11_CH4,(U1)ANTCTL_DIO_LOW);
            st_s_antctl_dab.u1_antena_reboot_flg = (U1)TRUE;
            st_s_antctl_dab.u1_fail_flg = (U1)FALSE;
        }
    }
}
#endif

#ifdef ANTCTL_DTV
/*===================================================================================================================================*/
/*  static void vd_s_Ant_DTV_Fail(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    DTVアンテナのフェール処理                                                                                          */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Ant_DTV_Fail(void)
{
    /*フェール処理*/
    if((u1_s_dtv1_short_cnt != (U1)0U) ||
       (u1_s_dtv2_short_cnt != (U1)0U) ||
       (u1_s_dtv3_short_cnt != (U1)0U) ||
       (u1_s_dtv4_short_cnt != (U1)0U)){
        if((u1_s_dtv1_short_cnt <= (U1)ANTCTL_SHORT_DET_CNT) ||
           (u1_s_dtv2_short_cnt <= (U1)ANTCTL_SHORT_DET_CNT) ||
           (u1_s_dtv3_short_cnt <= (U1)ANTCTL_SHORT_DET_CNT) ||
           (u1_s_dtv4_short_cnt <= (U1)ANTCTL_SHORT_DET_CNT)) {
            Dio_WriteChannel((U2)DIO_ID_PORT11_CH4,(U1)ANTCTL_DIO_LOW);
            st_s_antctl_dtv.u1_antena_reboot_flg = (U1)TRUE;
            st_s_antctl_dtv.u1_fail_flg = (U1)FALSE;
        }
    }
}
#endif

/*===================================================================================================================================*/
/*  static void vd_s_Ant_Gnss_Reboot(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    GNSSアンテナの再起動処理                                                                                           */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Ant_Gnss_Reboot(void)
{
    /*GNSSアンテナ再起動処理*/
    if(st_s_antctl_gnss.u1_antena_reboot_wait_time < (U1)U1_MAX) {
        st_s_antctl_gnss.u1_antena_reboot_wait_time++;
    }
    
    if(st_s_antctl_gnss.u1_antena_reboot_wait_time >= (U1)ANTCTL_REBOOT_WAIT_TIME) {
        Dio_WriteChannel((U2)DIO_ID_APORT4_CH2,(U1)ANTCTL_DIO_HIGH);
        st_s_antctl_gnss.u1_antena_reboot_flg = (U1)FALSE;
        st_s_antctl_gnss.u1_antena_reboot_wait_time = (U1)0U;
    }
}

#ifdef ANTCTL_DAB
/*===================================================================================================================================*/
/*  static void vd_s_Ant_DAB_Reboot(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    DABアンテナの再起動処理                                                                                            */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Ant_DAB_Reboot(void)
{
    /*DABアンテナ再起動処理*/
    if(st_s_antctl_dab.u1_antena_reboot_wait_time < (U1)U1_MAX) {
        st_s_antctl_dab.u1_antena_reboot_wait_time++;
    }
    
    if(st_s_antctl_dab.u1_antena_reboot_wait_time >= (U1)ANTCTL_REBOOT_WAIT_TIME) {
        Dio_WriteChannel((U2)DIO_ID_PORT11_CH4,(U1)ANTCTL_DIO_HIGH);
        st_s_antctl_dab.u1_antena_reboot_flg = (U1)FALSE;
        st_s_antctl_dab.u1_antena_reboot_wait_time = (U1)0U;
    }
}
#endif

#ifdef ANTCTL_DTV
/*===================================================================================================================================*/
/*  static void vd_s_Ant_DTV_Reboot(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    DABアンテナの再起動処理                                                                                            */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Ant_DTV_Reboot(void)
{
    /*DTVアンテナ再起動処理*/
    if(st_s_antctl_dtv.u1_antena_reboot_wait_time < (U1)U1_MAX) {
        st_s_antctl_dtv.u1_antena_reboot_wait_time++;
    }
    
    if(st_s_antctl_dtv.u1_antena_reboot_wait_time >= (U1)ANTCTL_REBOOT_WAIT_TIME) {
        Dio_WriteChannel((U2)DIO_ID_PORT11_CH4,(U1)ANTCTL_DIO_HIGH);
        st_s_antctl_dtv.u1_antena_reboot_flg = (U1)FALSE;
        st_s_antctl_dtv.u1_antena_reboot_wait_time = (U1)0U;
    }
}
#endif

/*===================================================================================================================================*/
/*  static U1 u1_s_Ant_TimChk(const U2 u2_a_TIM_CINT, const U2 u2_a_WAIT_TIM)                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    カウントチェック関数                                                                                               */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_Ant_TimChk(const U2 u2_a_TIM_CINT, const U2 u2_a_WAIT_TIM)
{
    /*タイマーチェック*/
    U1    u1_t_ret;

    u1_t_ret = (U1)FALSE;

    if(u2_a_TIM_CINT >= u2_a_WAIT_TIM) {
        u1_t_ret = (U1)TRUE;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  0.0.0    02/21/2024  KT       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * KT   = Kenta Takaji, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
