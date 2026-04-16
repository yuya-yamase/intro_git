/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Date clock Synchronization Interface                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DATESI_ABS_C_MAJOR                  (0)
#define DATESI_ABS_C_MINOR                  (0)
#define DATESI_ABS_C_PATCH                  (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "datesi_abs.h"
#include "datesi_cal.h"
#include "datesi_com.h"
#include "datesi_cal_cfg_private.h"
#include "datesi_tim_cfg_private.h"
#include "date_clk.h"
#include "rim_ctl.h"
#include "rtime.h"
#include "date.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DATESI_ABS_C_MAJOR != DATESI_ABS_H_MAJOR) || \
     (DATESI_ABS_C_MINOR != DATESI_ABS_H_MINOR) || \
     (DATESI_ABS_C_PATCH != DATESI_ABS_H_PATCH))
#error "datesi_abs.c and datesi_abs.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DATESI_ABS_NUM_BACK                 (4U)
#define DATESI_ABS_BACK_NUM_CMPR            (3U)
#define DATESI_ABS_BACK_1ST                 (0U)
#define DATESI_ABS_BACK_2ND                 (1U)
#define DATESI_ABS_BACK_3RD                 (2U)
#define DATESI_ABS_BACK_4TH                 (3U)
#define DATESI_ABS_NUM_DATA_VALID           (8U)

#define DATESI_ABS_ERR_BIT                  (0x01U)
#define DATESI_ABS_SFT_1BIT                 (1U)

#define DATESI_ABS_RIM_READ_RETRY           (3U)

#define DATESI_ABS_1DAY                     (1U)

#define DATESI_ABS_DELAY_CHK                (2U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U4              u4_pre_rtc_hhmmss_24h;
    U4              u4_pre_rtc_daycnt;
    U4              u4_abs_hhmmss_24h;
    U4              u4_abs_daycnt;
}ST_DATESIABS_BK;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_DATESIABS_BK                st_s_datesi_abs_backupdata[DATESI_ABS_NUM_BACK];
static U1                             u1_s_datesi_abs_rtcsync;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const  U4                             u4_g_DATESI_ABS_DAYCNT_MAX = (U4)DATE_CLK_DAYCNT_MAX;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_DateSIAbsCalculate(void);
static void     vd_s_DateSIAbsRtcDlaySync(void);
static U1       u1_s_DateSIAbsRtcDelayChk(const U4 u4_a_MM_TIM, const U4 u4_a_MM_CAL);
static void     vd_s_DateSIAbsDataValidation(ST_DATESIABS_BK * st_ap_BK);
static U1       u1_s_DateSIAbsFmtChk(const ST_DATESIABS_BK * st_ap_BK);
static void     vd_s_DateSIAbsBackUpdt(const ST_DATESIABS_BK * st_ap_BK);

/*===================================================================================================================================*/
/* void            vd_g_DateSIAbsBonInit(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSIAbsBonInit(void)
{
    ST_DATESIABS_BK  st_t_backupdata;
    U4               u4_t_rtc_yymmddwk;
    U4               u4_t_rtc_daycnt;

    u1_s_datesi_abs_rtcsync = (U1)FALSE;

    u4_t_rtc_yymmddwk                      = u4_g_DateclkYymmddwk();
    u4_t_rtc_daycnt                        = u4_g_YymmddToDaycnt(u4_t_rtc_yymmddwk);
    st_t_backupdata.u4_pre_rtc_hhmmss_24h  = (U4)0U;
    st_t_backupdata.u4_abs_hhmmss_24h      = (U4)0U;
    st_t_backupdata.u4_pre_rtc_daycnt      = u4_t_rtc_daycnt;
    st_t_backupdata.u4_abs_daycnt          = u4_t_rtc_daycnt;
    vd_s_DateSIAbsBackUpdt(&st_t_backupdata);
}

/*===================================================================================================================================*/
/* void            vd_g_DateSIAbsRstWkupInit(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSIAbsRstWkupInit(void)
{
    U4               u4_t_lpcnt;
    U1               u1_t_rim_sts;
    U4               u4_t_rim_data;
    U1               u1_t_readcmpchk;
    U4               u4_t_rtc_hhmmss;
    U4               u4_t_rtc_yymmddwk;
    U4               u4_t_rtc_daycnt;
    ST_DATESIABS_BK  st_t_backupdata;

    u1_s_datesi_abs_rtcsync = (U1)FALSE;

    u1_t_readcmpchk = (U1)FALSE;
    /* RIM Read: Previous RTC Time(hhmmss) */
    u4_t_rim_data = (U4)0U;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)DATESI_ABS_RIM_READ_RETRY; u4_t_lpcnt++){
        u1_t_rim_sts  = u1_g_Rim_ReadU4withStatus((U2)RIMID_U4_PRE_RTCTIM, &u4_t_rim_data);
        if((u1_t_rim_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
            st_t_backupdata.u4_pre_rtc_hhmmss_24h = u4_t_rim_data;
            u1_t_readcmpchk = (U1)TRUE;
            break;
        }
    }
    /* RIM Read: Previous RTC Date(daycount) */
    if(u1_t_readcmpchk == (U1)TRUE){
        u1_t_readcmpchk = (U1)FALSE;
        u4_t_rim_data   = (U4)0U;
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)DATESI_ABS_RIM_READ_RETRY; u4_t_lpcnt++){
            u1_t_rim_sts  = u1_g_Rim_ReadU4withStatus((U2)RIMID_U4_PRE_RTCCAL, &u4_t_rim_data);
            if((u1_t_rim_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
                st_t_backupdata.u4_pre_rtc_daycnt = u4_t_rim_data;
                u1_t_readcmpchk = (U1)TRUE;
                break;
            }
        }
    }
    /* RIM Read: Absolute Time(hhmmss) */
    if(u1_t_readcmpchk == (U1)TRUE){
        u1_t_readcmpchk = (U1)FALSE;
        u4_t_rim_data = (U4)0U;
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)DATESI_ABS_RIM_READ_RETRY; u4_t_lpcnt++){
            u1_t_rim_sts  = u1_g_Rim_ReadU4withStatus((U2)RIMID_U4_ABSTIM, &u4_t_rim_data);
            if((u1_t_rim_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
                st_t_backupdata.u4_abs_hhmmss_24h = u4_t_rim_data;
                u1_t_readcmpchk = (U1)TRUE;
                break;
            }
        }
    }
    /* RIM Read: Absolute Date(daycount) */
    if(u1_t_readcmpchk == (U1)TRUE){
        u1_t_readcmpchk = (U1)FALSE;
        u4_t_rim_data = (U4)0U;
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)DATESI_ABS_RIM_READ_RETRY; u4_t_lpcnt++){
            u1_t_rim_sts  = u1_g_Rim_ReadU4withStatus((U2)RIMID_U4_ABSCAL, &u4_t_rim_data);
            if((u1_t_rim_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
                st_t_backupdata.u4_abs_daycnt = u4_t_rim_data;
                u1_t_readcmpchk = (U1)TRUE;
                break;
            }
        }
    }
    /* RIM Read Error */
    if(u1_t_readcmpchk != (U1)TRUE){
        u4_t_rtc_hhmmss                       = u4_g_DateclkHhmmss24h();
        u4_t_rtc_yymmddwk                     = u4_g_DateclkYymmddwk();
        u4_t_rtc_daycnt                       = u4_g_YymmddToDaycnt(u4_t_rtc_yymmddwk);
        st_t_backupdata.u4_pre_rtc_hhmmss_24h = u4_t_rtc_hhmmss;
        st_t_backupdata.u4_abs_hhmmss_24h     = u4_t_rtc_hhmmss;
        st_t_backupdata.u4_pre_rtc_daycnt     = u4_t_rtc_daycnt;
        st_t_backupdata.u4_abs_daycnt         = u4_t_rtc_daycnt;
    }
    /* Backup RAM Update */
    vd_s_DateSIAbsBackUpdt(&st_t_backupdata);
}

/*===================================================================================================================================*/
/* void            vd_g_DateSIAbsMainTask(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSIAbsMainTask(void)
{
    vd_s_DateSIAbsCalculate();
    vd_s_DateSIAbsRtcDlaySync();
}

/*===================================================================================================================================*/
/* void            vd_s_DateSIAbsCalculate(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DateSIAbsCalculate(void)
{
    U4               u4_t_pre_rtctim_sec;
    U4               u4_t_abstim_sec;
    U4               u4_t_now_rtcdate_yymmddwk;
    U4               u4_t_now_rtcdate_daycnt;
    U4               u4_t_now_rtctim_hhmmss;
    U4               u4_t_now_rtctim_sec;
    U4               u4_t_elapsed;
    U4               u4_t_elapsed_time;
    U4               u4_t_elapsed_date;
    ST_DATESIABS_BK  st_t_backupdata;

    st_t_backupdata.u4_pre_rtc_hhmmss_24h = (U4)HHMMSS_UNKNWN;
    st_t_backupdata.u4_pre_rtc_daycnt     = (U4)YYMMDDWK_DAYCNT_UNKNWN;
    st_t_backupdata.u4_abs_hhmmss_24h     = (U4)HHMMSS_UNKNWN;
    st_t_backupdata.u4_abs_daycnt         = (U4)YYMMDDWK_DAYCNT_UNKNWN;

    vd_s_DateSIAbsDataValidation(&st_t_backupdata);
    u4_t_pre_rtctim_sec       = u4_g_HhmmssToSeconds(st_t_backupdata.u4_pre_rtc_hhmmss_24h);
    u4_t_abstim_sec           = u4_g_HhmmssToSeconds(st_t_backupdata.u4_abs_hhmmss_24h);
    u4_t_now_rtcdate_yymmddwk = u4_g_DateclkYymmddwk();
    u4_t_now_rtcdate_daycnt   = u4_g_YymmddToDaycnt(u4_t_now_rtcdate_yymmddwk);
    u4_t_now_rtctim_hhmmss    = u4_g_DateclkHhmmss24h();
    u4_t_now_rtctim_sec       = u4_g_HhmmssToSeconds(u4_t_now_rtctim_hhmmss);

    if((st_t_backupdata.u4_pre_rtc_daycnt != u4_t_now_rtcdate_daycnt) || 
       (u4_t_pre_rtctim_sec               != u4_t_now_rtctim_sec    )){
        /* calculate the elapsed time */
        if((u4_t_now_rtcdate_daycnt > st_t_backupdata.u4_pre_rtc_daycnt) ||
           ((u4_t_now_rtcdate_daycnt == st_t_backupdata.u4_pre_rtc_daycnt) &&
            (u4_t_now_rtctim_sec     >  u4_t_pre_rtctim_sec              ))){
            u4_t_elapsed                   = (((u4_t_now_rtcdate_daycnt - st_t_backupdata.u4_pre_rtc_daycnt) * (U4)HHMMSS_24HR_TO_SE) + u4_t_now_rtctim_sec) - u4_t_pre_rtctim_sec;
            u4_t_elapsed_time              = u4_t_elapsed + u4_t_abstim_sec;
            u4_t_elapsed_date              = u4_t_elapsed_time / (U4)HHMMSS_24HR_TO_SE;
            st_t_backupdata.u4_abs_daycnt += u4_t_elapsed_date;
            u4_t_abstim_sec                = u4_t_elapsed_time % (U4)HHMMSS_24HR_TO_SE;
        }
        else {
            u4_t_elapsed                   = (((st_t_backupdata.u4_pre_rtc_daycnt - u4_t_now_rtcdate_daycnt) * (U4)HHMMSS_24HR_TO_SE) + u4_t_pre_rtctim_sec) - u4_t_now_rtctim_sec;
            u4_t_elapsed_date              = u4_t_elapsed / (U4)HHMMSS_24HR_TO_SE;
            st_t_backupdata.u4_abs_daycnt -= u4_t_elapsed_date;
            u4_t_elapsed_time              = u4_t_elapsed % (U4)HHMMSS_24HR_TO_SE;
            if(u4_t_abstim_sec >= u4_t_elapsed_time){
                u4_t_abstim_sec -= u4_t_elapsed_time;
            }
            else{
                u4_t_abstim_sec = (u4_t_abstim_sec + (U4)HHMMSS_24HR_TO_SE) - u4_t_elapsed_time;
                st_t_backupdata.u4_abs_daycnt -= (U4)DATESI_ABS_1DAY;
            }
        }
        st_t_backupdata.u4_abs_hhmmss_24h      = u4_g_SecondsToHhmmss(u4_t_abstim_sec);
        st_t_backupdata.u4_pre_rtc_daycnt      = u4_t_now_rtcdate_daycnt;
        st_t_backupdata.u4_pre_rtc_hhmmss_24h  = u4_t_now_rtctim_hhmmss;
        vd_s_DateSIAbsBackUpdt(&st_t_backupdata);
    }
}

/*===================================================================================================================================*/
/* static void     vd_s_DateSIAbsRtcDlaySync(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DateSIAbsRtcDlaySync(void)
{
    ST_DATESI_COMMAND_DATA  st_t_command_data;
    ST_DATESI_TIM_RX        st_t_tim_rx;
    ST_DATESI_CAL_RX        st_t_cal_rx;
    U1                      u1_t_tim_range_is_ok;
    U1                      u1_t_cal_range_is_ok;
    U4                      u4_t_adj_yymmdd;
    U4                      u4_t_adj_hhmmss;
    U1                      u1_t_delay;
    U1                      u1_t_tim_result;
    U1                      u1_t_cal_result;

    u4_t_adj_yymmdd   = (U4)YYMMDDWK_UNKNWN;
    st_t_command_data = st_g_DateSIComRx();

    st_t_tim_rx.u1p_time[HHMMSS_24H_TIME_SE] = st_t_command_data.u1_clk_sec;
    st_t_tim_rx.u1p_time[HHMMSS_24H_TIME_MI] = st_t_command_data.u1_clk_min;
    st_t_tim_rx.u1p_time[HHMMSS_24H_TIME_HR] = st_t_command_data.u1_clk_hour;
    st_t_tim_rx.u1_valid                     = st_t_command_data.u1_gps_st;
    st_t_tim_rx.u1_act                       = st_t_command_data.u1_gps_crct;
    st_t_cal_rx.u1p_date[YYMMDD_DATE_DA]     = st_t_command_data.u1_clk_day;
    st_t_cal_rx.u1p_date[YYMMDD_DATE_MO]     = st_t_command_data.u1_clk_mont;
    st_t_cal_rx.u1p_date[YYMMDD_DATE_YR]     = st_t_command_data.u1_clk_year;
    st_t_cal_rx.u1_valid                     = st_t_command_data.u1_gps_st;
    st_t_cal_rx.u1_act                       = st_t_command_data.u1_gps_crct;

    u1_t_tim_range_is_ok = u1_g_DateSITimClkRangeCheck(st_t_tim_rx);
    u1_t_cal_range_is_ok = u1_g_DateSICalDateSyncChk(st_t_cal_rx, &u4_t_adj_yymmdd);
    if((st_t_command_data.u1_gps_st == (U1)TRUE) &&
       (u1_t_tim_range_is_ok        == (U1)TRUE) &&
       (u1_t_cal_range_is_ok        == (U1)TRUE)){
        u4_t_adj_hhmmss      = u4_g_DateSITimMakeHHMMSS(st_t_tim_rx.u1p_time[HHMMSS_24H_TIME_HR],
                                                        st_t_tim_rx.u1p_time[HHMMSS_24H_TIME_MI],
                                                        st_t_tim_rx.u1p_time[HHMMSS_24H_TIME_SE]);
        u1_t_delay = u1_s_DateSIAbsRtcDelayChk(u4_t_adj_hhmmss, u4_t_adj_yymmdd);
        if((u1_t_delay              == (U1)TRUE) ||
           (u1_s_datesi_abs_rtcsync != (U1)TRUE)){
            u1_t_tim_result = u1_g_DateSITimAdjustOwnClk(u4_t_adj_hhmmss);
            if(u1_t_tim_result == (U1)TRUE){
                vd_g_DateSIAbsAdjHhmmss24h((U4)HHMMSS_UNKNWN, u4_t_adj_hhmmss);
            }
            u1_t_cal_result = u1_g_DateSICalAdjustOwnClk(u4_t_adj_yymmdd);
            if(u1_t_cal_result == (U1)TRUE){
                vd_g_DateSIAbsAdjYymmddwk((U4)YYMMDDWK_UNKNWN, u4_t_adj_yymmdd);
            }
            if((u1_t_tim_result == (U1)TRUE) &&
               (u1_t_cal_result == (U1)TRUE)){
                u1_s_datesi_abs_rtcsync = (U1)TRUE;
            }
        }
    }
}

/*===================================================================================================================================*/
/* static U1       u1_s_DateSIAbsRtcDelayChk(const U4 u4_a_ADJ_TIM, const U4 u4_a_ADJ_CAL)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u4_a_MM_TIM  : MM time (format : hhmmss)                                                                         */
/*  Arguments:      u4_a_MM_CAL  : MM date (format : yymmddwk)                                                                       */
/*  Return:         Delay Check Result(TRUE/FALSE)                                                                                   */
/*===================================================================================================================================*/
static U1       u1_s_DateSIAbsRtcDelayChk(const U4 u4_a_MM_TIM, const U4 u4_a_MM_CAL)
{
    U4    u4_t_now_rtc_hhmmss;
    U4    u4_t_now_rtc_sec;
    U4    u4_t_now_mm_sec;
    U4    u4_t_now_rtc_yymmdd;
    U4    u4_t_now_rtc_daycnt;
    U4    u4_t_now_mm_daycnt;
    U4    u4_t_delay;
    U1    u1_t_result;

    u1_t_result         = (U1)FALSE;
    u4_t_now_rtc_hhmmss = u4_g_DateclkHhmmss24h();
    u4_t_now_rtc_sec    = u4_g_HhmmssToSeconds(u4_t_now_rtc_hhmmss);
    u4_t_now_mm_sec     = u4_g_HhmmssToSeconds(u4_a_MM_TIM);
    u4_t_now_rtc_yymmdd = u4_g_DateclkYymmddwk();
    u4_t_now_rtc_daycnt = u4_g_YymmddToDaycnt(u4_t_now_rtc_yymmdd);
    u4_t_now_mm_daycnt  = u4_g_YymmddToDaycnt(u4_a_MM_CAL);
    
    if((u4_t_now_mm_daycnt   > u4_t_now_rtc_daycnt) ||
       ((u4_t_now_mm_daycnt == u4_t_now_rtc_daycnt) &&
        (u4_t_now_mm_sec    >= u4_t_now_rtc_sec   ))){
        u4_t_delay = (((u4_t_now_mm_daycnt - u4_t_now_rtc_daycnt) * (U4)HHMMSS_24HR_TO_SE) + u4_t_now_mm_sec) - u4_t_now_rtc_sec;
    }
    else{
        u4_t_delay = (((u4_t_now_rtc_daycnt - u4_t_now_mm_daycnt) * (U4)HHMMSS_24HR_TO_SE) + u4_t_now_rtc_sec) - u4_t_now_mm_sec;
    }
    if(u4_t_delay >= (U4)DATESI_ABS_DELAY_CHK){
        u1_t_result = (U1)TRUE;
    }
    return(u1_t_result);
}

/*===================================================================================================================================*/
/* U4              u4_g_DateSIAbsHhmmss24h(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         absolute time (format : hhmmss)                                                                                  */
/*===================================================================================================================================*/
U4              u4_g_DateSIAbsHhmmss24h(void)
{
    ST_DATESIABS_BK  st_t_backupdata;

    st_t_backupdata.u4_pre_rtc_hhmmss_24h = (U4)HHMMSS_UNKNWN;
    st_t_backupdata.u4_pre_rtc_daycnt     = (U4)YYMMDDWK_DAYCNT_UNKNWN;
    st_t_backupdata.u4_abs_hhmmss_24h     = (U4)HHMMSS_UNKNWN;
    st_t_backupdata.u4_abs_daycnt         = (U4)YYMMDDWK_DAYCNT_UNKNWN;

    vd_s_DateSIAbsDataValidation(&st_t_backupdata);
    return(st_t_backupdata.u4_abs_hhmmss_24h);
}

/*===================================================================================================================================*/
/* U4              u4_g_DateSIAbsYymmddwk(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         absolute date (format : yymmddwk)                                                                                */
/*===================================================================================================================================*/
U4              u4_g_DateSIAbsYymmddwk(void)
{
    ST_DATESIABS_BK  st_t_backupdata;
    U4               u4_t_abscal_yymmddwk;

    st_t_backupdata.u4_pre_rtc_hhmmss_24h = (U4)HHMMSS_UNKNWN;
    st_t_backupdata.u4_pre_rtc_daycnt     = (U4)YYMMDDWK_DAYCNT_UNKNWN;
    st_t_backupdata.u4_abs_hhmmss_24h     = (U4)HHMMSS_UNKNWN;
    st_t_backupdata.u4_abs_daycnt         = (U4)YYMMDDWK_DAYCNT_UNKNWN;

    vd_s_DateSIAbsDataValidation(&st_t_backupdata);
    u4_t_abscal_yymmddwk = u4_g_DaycntToYymmddwk(st_t_backupdata.u4_abs_daycnt);
    return(u4_t_abscal_yymmddwk);
}

/*===================================================================================================================================*/
/* void            vd_g_DateSIAbsAdjHhmmss24h(const U4 u4_a_ABS_HHMMSS, const U4 u4_a_RTC_HHMMSS)                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u4_a_ABS_HHMMSS  : updated absolute time (format : hhmmss)                                                       */
/*                  u4_a_RTC_HHMMSS  : updated RTC time (format : hhmmss)                                                            */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSIAbsAdjHhmmss24h(const U4 u4_a_ABS_HHMMSS, const U4 u4_a_RTC_HHMMSS)
{
    ST_DATESIABS_BK  st_t_backupdata;

    st_t_backupdata.u4_pre_rtc_daycnt     = (U4)YYMMDDWK_DAYCNT_UNKNWN;
    st_t_backupdata.u4_abs_daycnt         = (U4)YYMMDDWK_DAYCNT_UNKNWN;
    st_t_backupdata.u4_pre_rtc_hhmmss_24h = u4_a_RTC_HHMMSS;
    st_t_backupdata.u4_abs_hhmmss_24h     = u4_a_ABS_HHMMSS;

    vd_s_DateSIAbsBackUpdt(&st_t_backupdata);
}

/*===================================================================================================================================*/
/* void            vd_g_DateSIAbsAdjYymmddwk(const U4 u4_a_ABS_YYMMDDWK, const U4 u4_a_RTC_YYMMDDWK)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u4_a_ABS_YYMMDDWK  : updated absolute date (format : yymmddwk)                                                   */
/*                  u4_a_RTC_YYMMDDWK  : updated RTC date (format : yymmddwk)                                                        */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSIAbsAdjYymmddwk(const U4 u4_a_ABS_YYMMDDWK, const U4 u4_a_RTC_YYMMDDWK)
{
    ST_DATESIABS_BK  st_t_backupdata;

    st_t_backupdata.u4_pre_rtc_hhmmss_24h = (U4)HHMMSS_UNKNWN;
    st_t_backupdata.u4_pre_rtc_daycnt     = (U4)YYMMDDWK_DAYCNT_UNKNWN;
    st_t_backupdata.u4_abs_hhmmss_24h     = (U4)HHMMSS_UNKNWN;
    st_t_backupdata.u4_abs_daycnt         = (U4)YYMMDDWK_DAYCNT_UNKNWN;

    if(u4_a_ABS_YYMMDDWK != (U4)YYMMDDWK_UNKNWN){
        st_t_backupdata.u4_abs_daycnt = u4_g_YymmddToDaycnt(u4_a_ABS_YYMMDDWK);
    }
    if(u4_a_RTC_YYMMDDWK != (U4)YYMMDDWK_UNKNWN){
        st_t_backupdata.u4_pre_rtc_daycnt = u4_g_YymmddToDaycnt(u4_a_RTC_YYMMDDWK);
    }
    vd_s_DateSIAbsBackUpdt(&st_t_backupdata);
}

/*===================================================================================================================================*/
/* static void     vd_s_DateSIAbsDataValidation(ST_DATESIABS_BK * st_ap_BK)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      st_ap_BK : confirmed data                                                                                        */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DateSIAbsDataValidation(ST_DATESIABS_BK * st_ap_BK)
{
    static const U1 u1_sp_DATESIABS_DATA_VALID[DATESI_ABS_NUM_DATA_VALID] = {
        (U1)DATESI_ABS_BACK_1ST,  /* 000  (1st == 2nd) & (2nd == 3rd) & (3rd == 4th) */
        (U1)DATESI_ABS_BACK_2ND,  /* 001  (1st != 2nd) & (2nd == 3rd) & (3rd == 4th) */
        (U1)DATESI_ABS_BACK_1ST,  /* 010  (1st == 2nd) & (2nd != 3rd) & (3rd == 4th) */
        (U1)DATESI_ABS_BACK_3RD,  /* 011  (1st != 2nd) & (2nd != 3rd) & (3rd == 4th) */
        (U1)DATESI_ABS_BACK_1ST,  /* 100  (1st == 2nd) & (2nd == 3rd) & (3rd != 4th) */
        (U1)DATESI_ABS_BACK_2ND,  /* 101  (1st != 2nd) & (2nd == 3rd) & (3rd != 4th) */
        (U1)DATESI_ABS_BACK_1ST,  /* 110  (1st == 2nd) & (2nd != 3rd) & (3rd != 4th) */
        (U1)U1_MAX,               /* 111  (1st != 2nd) & (2nd != 3rd) & (3rd != 4th) */
    };

    ST_DATESIABS_BK *           st_tp_1st;
    ST_DATESIABS_BK *           st_tp_2nd;
    U4                          u4_t_lpcnt;
    U1                          u1_t_chk;
    U1                          u1_t_bit;
    U1                          u1_t_valid;
    U1                          u1_t_er_chk;
    U4                          u4_t_rtc_hhmmss;
    U4                          u4_t_rtc_yymmddwk;
    U4                          u4_t_rtc_daycnt;

    u1_t_chk    = (U1)0U;
    u1_t_er_chk = (U1)FALSE;
    u1_t_bit    = (U1)DATESI_ABS_ERR_BIT;

    st_tp_1st = &st_s_datesi_abs_backupdata[DATESI_ABS_BACK_1ST];
    st_tp_2nd = &st_s_datesi_abs_backupdata[DATESI_ABS_BACK_2ND];
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)DATESI_ABS_BACK_NUM_CMPR; u4_t_lpcnt++){
        if((st_tp_1st[u4_t_lpcnt].u4_pre_rtc_hhmmss_24h != st_tp_2nd[u4_t_lpcnt].u4_pre_rtc_hhmmss_24h) ||
           (st_tp_1st[u4_t_lpcnt].u4_pre_rtc_daycnt     != st_tp_2nd[u4_t_lpcnt].u4_pre_rtc_daycnt    ) ||
           (st_tp_1st[u4_t_lpcnt].u4_abs_hhmmss_24h     != st_tp_2nd[u4_t_lpcnt].u4_abs_hhmmss_24h    ) ||
           (st_tp_1st[u4_t_lpcnt].u4_abs_daycnt         != st_tp_2nd[u4_t_lpcnt].u4_abs_daycnt        )){
            u1_t_chk |= u1_t_bit;
        }
        u1_t_bit = u1_t_bit << DATESI_ABS_SFT_1BIT;
    }

    if(u1_t_chk < (U1)DATESI_ABS_NUM_DATA_VALID){
        u1_t_valid = u1_sp_DATESIABS_DATA_VALID[u1_t_chk];
        if(u1_t_valid < (U1)DATESI_ABS_NUM_BACK){
            st_ap_BK->u4_pre_rtc_hhmmss_24h = st_s_datesi_abs_backupdata[u1_t_valid].u4_pre_rtc_hhmmss_24h;
            st_ap_BK->u4_pre_rtc_daycnt     = st_s_datesi_abs_backupdata[u1_t_valid].u4_pre_rtc_daycnt;
            st_ap_BK->u4_abs_hhmmss_24h     = st_s_datesi_abs_backupdata[u1_t_valid].u4_abs_hhmmss_24h;
            st_ap_BK->u4_abs_daycnt         = st_s_datesi_abs_backupdata[u1_t_valid].u4_abs_daycnt;
        }
        else{
            u1_t_er_chk |= (U1)TRUE;
        }
    }
    else{
        u1_t_er_chk |= (U1)TRUE;
    }
    u1_t_er_chk |= u1_s_DateSIAbsFmtChk(st_ap_BK);
    
    if(u1_t_er_chk != (U1)0U){
        u4_t_rtc_hhmmss                       = u4_g_DateclkHhmmss24h();
        u4_t_rtc_yymmddwk                     = u4_g_DateclkYymmddwk();
        u4_t_rtc_daycnt                       = u4_g_YymmddToDaycnt(u4_t_rtc_yymmddwk);
        st_ap_BK->u4_pre_rtc_hhmmss_24h       = u4_t_rtc_hhmmss;
        st_ap_BK->u4_abs_hhmmss_24h           = u4_t_rtc_hhmmss;
        st_ap_BK->u4_pre_rtc_daycnt           = u4_t_rtc_daycnt;
        st_ap_BK->u4_abs_daycnt               = u4_t_rtc_daycnt;
        vd_s_DateSIAbsBackUpdt(st_ap_BK);
    }
}

/*===================================================================================================================================*/
/* static void     u1_s_DateSIAbsFmtChk(const ST_DATESIABS_BK * st_ap_BK)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      st_ap_BK : target to check                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DateSIAbsFmtChk(const ST_DATESIABS_BK * st_ap_BK)
{
    U1  u1_t_er_chk;
    U1  u1_t_frmt;
    U4  u4_t_daycnt_min;

    u1_t_er_chk = (U1)FALSE;
    u1_t_frmt = u1_g_HhmmssFrmtIs24h(st_ap_BK->u4_pre_rtc_hhmmss_24h, vdp_PTR_NA);
    if(u1_t_frmt != (U1)TRUE){
        u1_t_er_chk |= (U1)TRUE;
    }
    u1_t_frmt = u1_g_HhmmssFrmtIs24h(st_ap_BK->u4_abs_hhmmss_24h, vdp_PTR_NA);
    if(u1_t_frmt != (U1)TRUE){
        u1_t_er_chk |= (U1)TRUE;
    }
    
    u4_t_daycnt_min = u4_g_DateSICalGetDaycntAbsMin();
    if((st_ap_BK->u4_pre_rtc_daycnt < u4_t_daycnt_min           ) ||
       (st_ap_BK->u4_pre_rtc_daycnt > u4_g_DATESI_ABS_DAYCNT_MAX)){
        u1_t_er_chk |= (U1)TRUE;
    }
    if((st_ap_BK->u4_abs_daycnt < u4_t_daycnt_min           ) ||
       (st_ap_BK->u4_abs_daycnt > u4_g_DATESI_ABS_DAYCNT_MAX)){
        u1_t_er_chk |= (U1)TRUE;
    }
    return(u1_t_er_chk);
}

/*===================================================================================================================================*/
/* static void     vd_s_DateSIAbsBackUpdt(const ST_DATESIABS_BK * st_ap_BK)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      st_ap_BK : updated data                                                                                          */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DateSIAbsBackUpdt(const ST_DATESIABS_BK * st_ap_BK)
{
    U4  u4_t_lpcnt;

    if(st_ap_BK->u4_pre_rtc_hhmmss_24h != (U4)HHMMSS_UNKNWN){
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)DATESI_ABS_NUM_BACK; u4_t_lpcnt++){
            st_s_datesi_abs_backupdata[u4_t_lpcnt].u4_pre_rtc_hhmmss_24h = st_ap_BK->u4_pre_rtc_hhmmss_24h;
        }
    }
    if(st_ap_BK->u4_pre_rtc_daycnt != (U4)YYMMDDWK_DAYCNT_UNKNWN){
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)DATESI_ABS_NUM_BACK; u4_t_lpcnt++){
            st_s_datesi_abs_backupdata[u4_t_lpcnt].u4_pre_rtc_daycnt = st_ap_BK->u4_pre_rtc_daycnt;
        }
    }
    if(st_ap_BK->u4_abs_hhmmss_24h != (U4)HHMMSS_UNKNWN){
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)DATESI_ABS_NUM_BACK; u4_t_lpcnt++){
            st_s_datesi_abs_backupdata[u4_t_lpcnt].u4_abs_hhmmss_24h = st_ap_BK->u4_abs_hhmmss_24h;
        }
    }
    if(st_ap_BK->u4_abs_daycnt != (U4)YYMMDDWK_DAYCNT_UNKNWN){
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)DATESI_ABS_NUM_BACK; u4_t_lpcnt++){
            st_s_datesi_abs_backupdata[u4_t_lpcnt].u4_abs_daycnt = st_ap_BK->u4_abs_daycnt;
        }
    }
    vd_g_Rim_WriteU4((U2)RIMID_U4_PRE_RTCTIM, st_s_datesi_abs_backupdata[0].u4_pre_rtc_hhmmss_24h);
    vd_g_Rim_WriteU4((U2)RIMID_U4_PRE_RTCCAL, st_s_datesi_abs_backupdata[0].u4_pre_rtc_daycnt);
    vd_g_Rim_WriteU4((U2)RIMID_U4_ABSTIM, st_s_datesi_abs_backupdata[0].u4_abs_hhmmss_24h);
    vd_g_Rim_WriteU4((U2)RIMID_U4_ABSCAL, st_s_datesi_abs_backupdata[0].u4_abs_daycnt);

}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  0.0.0    03/12/2026  MN       New.                                                                                               */
/*                                                                                                                                   */
/*  * MN   = Mikiya Negishi, KSE                                                                                                     */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
