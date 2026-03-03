/* 0.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Date clock Synchronization Interface                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DATESI_COM_C_MAJOR                      (0)
#define DATESI_COM_C_MINOR                      (1)
#define DATESI_COM_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "datesi_com.h"
#include "datesi_tim.h"
#include "datesi_cal.h"
#include "date_clk.h"
#include "datesi_cfg_private.h"
#include "rim_ctl.h"
#include "x_spi_ivi_sub1_power.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DATESI_COM_C_MAJOR != DATESI_COM_H_MAJOR) || \
     (DATESI_COM_C_MINOR != DATESI_COM_H_MINOR) || \
     (DATESI_COM_C_PATCH != DATESI_COM_H_PATCH))
#error "datesi.c and datesi.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/* ECU internal communication Input Signal : Initial value */
#define DATESI_COM_CLK_YEAR_INI             (0x7FU)                                      /* Signal Name : CLK_YEAR               */
#define DATESI_COM_CLK_MONT_INI             (0x0FU)                                      /* Signal Name : CLK_MONT               */
#define DATESI_COM_CLK_DAY_INI              (0U)                                         /* Signal Name : CLK_DAY                */
#define DATESI_COM_CLK_HOUR_INI             (0x1FU)                                      /* Signal Name : CLK_HOUR               */
#define DATESI_COM_CLK_MIN_INI              (0x3FU)                                      /* Signal Name : CLK_MIN                */
#define DATESI_COM_CLK_SEC_INI              (0x3FU)                                      /* Signal Name : CLK_SEC                */
#define DATESI_COM_GPS_ST_INI               (0U)                                         /* Signal Name : GPS_ST                 */
#define DATESI_COM_GPS_CRCT_INI             (3U)                                         /* Signal Name : GPS_CRCT               */
#define DATESI_COM_TZ_INI                   (0x3FU)                                      /* Signal Name : TZ                     */
#define DATESI_COM_TZ_SIGN                  (3U)                                         /* Signal Name : TZ_SIGN                */
#define DATESI_COM_DST_S30                  (3U)                                         /* Signal Name : DST_S30                */
#define DATESI_COM_SW_OFF                   (0U)                                         /* Signal Name : xxxSW                  */

/* ECU internal communication Output Signal : Initial value */
#define DATESI_COM_M_YEAR_INI               (0xFFU)                                      /* Signal Name : M_YEAR                 */
#define DATESI_COM_M_MONTH_INI              (0U)                                         /* Signal Name : M_MONTH                */
#define DATESI_COM_M_DAY_INI                (0U)                                         /* Signal Name : M_DAY                  */
#define DATESI_COM_M_WEEK_INI               (0U)                                         /* Signal Name : M_WEEK                 */
#define DATESI_COM_CL_HOUR_INI              (0x1EU)                                      /* Signal Name : CL_HOUR                */
#define DATESI_COM_CL_MIN_INI               (0x3EU)                                      /* Signal Name : CL_MIN                 */
#define DATESI_COM_CL_SEC_INI               (0x3EU)                                      /* Signal Name : CL_SEC                 */
#define DATESI_COM_CL_AMPM_INI              (0U)                                         /* Signal Name : CL_AMPM                */
#define DATESI_COM_OFST_H_INI               (0x0EU)                                      /* Signal Name : OFST_H                 */
#define DATESI_COM_OFST_M_INI               (0x3EU)                                      /* Signal Name : OFST_M                 */
#define DATESI_COM_OFSTSIGN_INI             (0U)                                         /* Signal Name : OFSTSIGN               */
#define DATESI_COM_TIME_SET_INI             (0U)                                         /* Signal Name : TIME_SET               */

/* RTC Invalid value */
#define DATESI_COM_RTC_YEAR_INVALID         (0xFFU)                                      /* Year(RTC)                            */
#define DATESI_COM_RTC_MONTH_INVALID        (0U)                                         /* Month(RTC)                           */
#define DATESI_COM_RTC_DAY_INVALID          (0U)                                         /* Day(RTC)                             */
#define DATESI_COM_RTC_HOUR_INVALID         (0x1EU)                                      /* Hour(RTC)                            */
#define DATESI_COM_RTC_MINUTE_INVALID       (0x3EU)                                      /* Minute(RTC)                          */
#define DATESI_COM_RTC_SECOND_INVALID       (0x3EU)                                      /* Second(RTC)                          */

/* Year Offset */
#define DATESI_COM_YEAR_OFFSET              (2000U)                                      /* Year Offset                          */

/* RTC Week Information */
#define DATESI_COM_RTC_WEEK_NUM             (7U)                                         /* Week Num                             */
#define DATESI_COM_RTC_WEEK_INVALID         (0U)                                         /* Invalid Value                        */
#define DATESI_COM_RTC_WEEK_MON             (1U)                                         /* Monday                               */
#define DATESI_COM_RTC_WEEK_TUE             (2U)                                         /* Tuesday                              */
#define DATESI_COM_RTC_WEEK_WED             (3U)                                         /* Wednesday                            */
#define DATESI_COM_RTC_WEEK_THU             (4U)                                         /* Thursday                             */
#define DATESI_COM_RTC_WEEK_FRI             (5U)                                         /* Friday                               */
#define DATESI_COM_RTC_WEEK_SAT             (6U)                                         /* Saturday                             */
#define DATESI_COM_RTC_WEEK_SUN             (7U)                                         /* Sunday                               */

/* RtcIC write status */
#define DATESI_COM_RTC_DATA_INVALID         (0U)                                         /* System date/time invalid             */
#define DATESI_COM_RTC_DATA_TIM_VALID       (0x01U)                                      /* System time valid                    */
#define DATESI_COM_RTC_DATA_CAL_VALID       (0x02U)                                      /* System date valid                    */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_DATESI_COMMAND_DATA         st_s_command_data;
static ST_XSPI_IVI_CLOCK_DISP_DATA    st_s_clock_disp_data;
static U1                             u1_s_datesi_com_req_act;
static U1                             u1_s_datesi_com_send_act;
static U1                             u1_sp_datesi_com_setting_sts[DATESI_COM_KIND_NUM];
static U1                             u1_s_datesi_com_rtc_sts;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void                           vd_s_DateSIComResetInit(void);
static ST_XSPI_IVI_CLOCK_RTC_DATA     st_s_DateSIComRtcSet(void);
static U1                             u1_s_DateSIComSetCmpChk(void);

/*===================================================================================================================================*/
/* void            vd_g_DateSIComBonInit(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void           vd_g_DateSIComBonInit(void)
{
    u1_s_datesi_com_rtc_sts = (U1)DATESI_COM_RTC_DATA_INVALID;
    vd_g_Rim_WriteU1((U2)RIMID_U1_RTC_STS, u1_s_datesi_com_rtc_sts);

    vd_g_DateSIComInit();
}

/*===================================================================================================================================*/
/* void            vd_g_DateSIComRstWkupInit(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void           vd_g_DateSIComRstWkupInit(void)
{
    U1  u1_t_rim_sts;
    U1  u1_t_rim_data;

    u1_s_datesi_com_rtc_sts = (U1)DATESI_COM_RTC_DATA_INVALID;
    u1_t_rim_data           = (U1)0U;

    u1_t_rim_sts = u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_RTC_STS, &u1_t_rim_data);
    if((u1_t_rim_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        u1_s_datesi_com_rtc_sts = u1_t_rim_data;
    }

    vd_g_DateSIComInit();
}

/*===================================================================================================================================*/
/* void            vd_g_DateSIComInit(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void           vd_g_DateSIComInit(void)
{
    U4                u4_t_lpcnt;

    /*Command Data Initial value set*/
    st_s_command_data.u1_clk_year              = (U1)DATESI_COM_CLK_YEAR_INI;
    st_s_command_data.u1_clk_mont              = (U1)DATESI_COM_CLK_MONT_INI;
    st_s_command_data.u1_clk_day               = (U1)DATESI_COM_CLK_DAY_INI;
    st_s_command_data.u1_clk_hour              = (U1)DATESI_COM_CLK_HOUR_INI;
    st_s_command_data.u1_clk_min               = (U1)DATESI_COM_CLK_MIN_INI;
    st_s_command_data.u1_clk_sec               = (U1)DATESI_COM_CLK_SEC_INI;
    st_s_command_data.u1_gps_st                = (U1)DATESI_COM_GPS_ST_INI;
    st_s_command_data.u1_gps_crct              = (U1)DATESI_COM_GPS_CRCT_INI;
    st_s_command_data.u1_tz                    = (U1)DATESI_COM_TZ_INI;
    st_s_command_data.u1_tz_sign               = (U1)DATESI_COM_TZ_SIGN;
    st_s_command_data.u1_dst_s30               = (U1)DATESI_COM_DST_S30;
    st_s_command_data.u1_hour_usw              = (U1)DATESI_COM_SW_OFF;
    st_s_command_data.u1_hour_dsw              = (U1)DATESI_COM_SW_OFF;
    st_s_command_data.u1_min_usw               = (U1)DATESI_COM_SW_OFF;
    st_s_command_data.u1_min_dsw               = (U1)DATESI_COM_SW_OFF;
    st_s_command_data.u1_oset_usw              = (U1)DATESI_COM_SW_OFF;
    st_s_command_data.u1_oset_dsw              = (U1)DATESI_COM_SW_OFF;
    st_s_command_data.u1_clkfmtsw              = (U1)DATESI_COM_SW_OFF;
    st_s_command_data.u1_m_rst_sw              = (U1)DATESI_COM_SW_OFF;
    st_s_command_data.u1_clk_year_updt         = (U1)DATESI_COM_CLK_YEAR_INI;
    st_s_command_data.u1_clk_mont_updt         = (U1)DATESI_COM_CLK_MONT_INI;
    st_s_command_data.u1_clk_day_updt          = (U1)DATESI_COM_CLK_DAY_INI;

    u1_s_datesi_com_req_act                    = (U1)FALSE;

    /*Dsiplay Clock Data Initial value set*/
    st_s_clock_disp_data.u1_year_disp          = (U1)DATESI_COM_M_YEAR_INI;
    st_s_clock_disp_data.u1_month_disp         = (U1)DATESI_COM_M_MONTH_INI;
    st_s_clock_disp_data.u1_day_disp           = (U1)DATESI_COM_M_DAY_INI;
    st_s_clock_disp_data.u1_dow_disp           = (U1)DATESI_COM_M_WEEK_INI;
    st_s_clock_disp_data.u1_hour_disp          = (U1)DATESI_COM_CL_HOUR_INI;
    st_s_clock_disp_data.u1_minute_disp        = (U1)DATESI_COM_CL_MIN_INI;
    st_s_clock_disp_data.u1_second_disp        = (U1)DATESI_COM_CL_SEC_INI;
    st_s_clock_disp_data.u1_ampm_disp          = (U1)DATESI_COM_CL_AMPM_INI;
    st_s_clock_disp_data.u1_hour_offset_disp   = (U1)DATESI_COM_OFST_H_INI;
    st_s_clock_disp_data.u1_minute_offset_disp = (U1)DATESI_COM_OFST_M_INI;
    st_s_clock_disp_data.u1_sign_offset_disp   = (U1)DATESI_COM_OFSTSIGN_INI;
    st_s_clock_disp_data.u1_1224format_disp    = (U1)DATESI_COM_TIME_SET_INI;

    u1_s_datesi_com_send_act                   = (U1)FALSE;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)DATESI_COM_KIND_NUM; u4_t_lpcnt++){
        u1_sp_datesi_com_setting_sts[u4_t_lpcnt] = (U1)FALSE;
    }
}

/*===================================================================================================================================*/
/* void            vd_g_DateSIComVMResetInit(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSIComVMResetInit(void)
{
    vd_s_DateSIComResetInit();
    vd_g_XspiIviSub1PowerVMResetComp((U1)XSPI_IVI_POWER_RESET_COMP_CLOCK);
}

/*===================================================================================================================================*/
/* void            vd_g_DateSIComSoCResetInit(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSIComSoCResetInit(void)
{
    vd_s_DateSIComResetInit();
}

/*===================================================================================================================================*/
/* static void     vd_s_DateSIComResetInit(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DateSIComResetInit(void)
{
    /*Command Data Initial value set*/
    st_s_command_data.u1_clk_year              = (U1)DATESI_COM_CLK_YEAR_INI;
    st_s_command_data.u1_clk_mont              = (U1)DATESI_COM_CLK_MONT_INI;
    st_s_command_data.u1_clk_day               = (U1)DATESI_COM_CLK_DAY_INI;
    st_s_command_data.u1_clk_hour              = (U1)DATESI_COM_CLK_HOUR_INI;
    st_s_command_data.u1_clk_min               = (U1)DATESI_COM_CLK_MIN_INI;
    st_s_command_data.u1_clk_sec               = (U1)DATESI_COM_CLK_SEC_INI;
    st_s_command_data.u1_gps_st                = (U1)DATESI_COM_GPS_ST_INI;
    st_s_command_data.u1_gps_crct              = (U1)DATESI_COM_GPS_CRCT_INI;
    st_s_command_data.u1_tz                    = (U1)DATESI_COM_TZ_INI;
    st_s_command_data.u1_tz_sign               = (U1)DATESI_COM_TZ_SIGN;
    st_s_command_data.u1_dst_s30               = (U1)DATESI_COM_DST_S30;
    st_s_command_data.u1_hour_usw              = (U1)DATESI_COM_SW_OFF;
    st_s_command_data.u1_hour_dsw              = (U1)DATESI_COM_SW_OFF;
    st_s_command_data.u1_min_usw               = (U1)DATESI_COM_SW_OFF;
    st_s_command_data.u1_min_dsw               = (U1)DATESI_COM_SW_OFF;
    st_s_command_data.u1_oset_usw              = (U1)DATESI_COM_SW_OFF;
    st_s_command_data.u1_oset_dsw              = (U1)DATESI_COM_SW_OFF;
    st_s_command_data.u1_clkfmtsw              = (U1)DATESI_COM_SW_OFF;
    st_s_command_data.u1_m_rst_sw              = (U1)DATESI_COM_SW_OFF;
    st_s_command_data.u1_clk_year_updt         = (U1)DATESI_COM_CLK_YEAR_INI;
    st_s_command_data.u1_clk_mont_updt         = (U1)DATESI_COM_CLK_MONT_INI;
    st_s_command_data.u1_clk_day_updt          = (U1)DATESI_COM_CLK_DAY_INI;
    u1_s_datesi_com_req_act                    = (U1)FALSE;
    
    /*Reset long-press detection (SW)*/
    vd_g_DateSITimCanRxHk();
}

/*===================================================================================================================================*/
/* void            vd_g_DateSIComCommandRx(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const ST_DATESI_COMMAND_DATA st_a_DATA                                                                           */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSIComCommandRx(const ST_DATESI_COMMAND_DATA st_a_DATA)
{
    st_s_command_data.u1_clk_year      = st_a_DATA.u1_clk_year;
    st_s_command_data.u1_clk_mont      = st_a_DATA.u1_clk_mont;
    st_s_command_data.u1_clk_day       = st_a_DATA.u1_clk_day;
    st_s_command_data.u1_clk_hour      = st_a_DATA.u1_clk_hour;
    st_s_command_data.u1_clk_min       = st_a_DATA.u1_clk_min;
    st_s_command_data.u1_clk_sec       = st_a_DATA.u1_clk_sec;
    st_s_command_data.u1_gps_st        = st_a_DATA.u1_gps_st;
    st_s_command_data.u1_gps_crct      = st_a_DATA.u1_gps_crct;
    st_s_command_data.u1_tz            = st_a_DATA.u1_tz;
    st_s_command_data.u1_tz_sign       = st_a_DATA.u1_tz_sign;
    st_s_command_data.u1_dst_s30       = st_a_DATA.u1_dst_s30;
    st_s_command_data.u1_hour_usw      = st_a_DATA.u1_hour_usw;
    st_s_command_data.u1_hour_dsw      = st_a_DATA.u1_hour_dsw;
    st_s_command_data.u1_min_usw       = st_a_DATA.u1_min_usw;
    st_s_command_data.u1_min_dsw       = st_a_DATA.u1_min_dsw;
    st_s_command_data.u1_oset_usw      = st_a_DATA.u1_oset_usw;
    st_s_command_data.u1_oset_dsw      = st_a_DATA.u1_oset_dsw;
    st_s_command_data.u1_clkfmtsw      = st_a_DATA.u1_clkfmtsw;
    st_s_command_data.u1_m_rst_sw      = st_a_DATA.u1_m_rst_sw;
    st_s_command_data.u1_clk_year_updt = st_a_DATA.u1_clk_year_updt;
    st_s_command_data.u1_clk_mont_updt = st_a_DATA.u1_clk_mont_updt;
    st_s_command_data.u1_clk_day_updt  = st_a_DATA.u1_clk_day_updt;

    u1_s_datesi_com_req_act = (U1)TRUE;

    vd_g_DateSITimCanRxHk();
    vd_g_DateSICalAdjustdate();

}

/*===================================================================================================================================*/
/* void            vd_g_DateSIComClockDispUpdate(const U1 u1_a_VAL, const U1 u1_a_SIGN, const U1 u1_a_EVENT_EI)                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const U1 u1_a_VAL, const U1 u1_a_SIGN, const U1 u1_a_EVENT_EI                                                    */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSIComClockDispUpdate(const U1 u1_a_VAL, const U1 u1_a_SIGN, const U1 u1_a_EVENT_EI)
{

    switch (u1_a_SIGN){
        case (U1)DATESI_COM_M_YEAR:
            st_s_clock_disp_data.u1_year_disp = u1_a_VAL;
            break;
        case (U1)DATESI_COM_M_MONTH:
            st_s_clock_disp_data.u1_month_disp = u1_a_VAL;
            break;
        case (U1)DATESI_COM_M_DAY:
            st_s_clock_disp_data.u1_day_disp = u1_a_VAL;
            break;
        case (U1)DATESI_COM_M_WEEK:
            st_s_clock_disp_data.u1_dow_disp = u1_a_VAL;
            break;
        case (U1)DATESI_COM_CL_HOUR:
            st_s_clock_disp_data.u1_hour_disp = u1_a_VAL;
            break;
        case (U1)DATESI_COM_CL_MIN:
            st_s_clock_disp_data.u1_minute_disp = u1_a_VAL;
            break;
        case (U1)DATESI_COM_CL_SEC:
            st_s_clock_disp_data.u1_second_disp = u1_a_VAL;
            break;
        case (U1)DATESI_COM_CL_AMPM:
            st_s_clock_disp_data.u1_ampm_disp = u1_a_VAL;
            break;
        case (U1)DATESI_COM_OFST_H:
            st_s_clock_disp_data.u1_hour_offset_disp = u1_a_VAL;
            break;
        case (U1)DATESI_COM_OFST_M:
            st_s_clock_disp_data.u1_minute_offset_disp = u1_a_VAL;
            break;
        case (U1)DATESI_COM_OFSTSIGN:
            st_s_clock_disp_data.u1_sign_offset_disp = u1_a_VAL;
            break;
        case (U1)DATESI_COM_TIME_SET:
            st_s_clock_disp_data.u1_1224format_disp = u1_a_VAL;
            break;
        default:
            /* do nothing */
            break;
    }

    if(u1_a_EVENT_EI  == (U1)TRUE){
        u1_s_datesi_com_send_act = (U1)TRUE;
    }

}

/*===================================================================================================================================*/
/* void            vd_g_DateSIComCommandTx(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSIComCommandTx(void)
{
    ST_XSPI_IVI_CLOCK_RTC_DATA   st_t_clock_rtc_data;
    U1                           u1_t_setting_sts;

    if(u1_s_datesi_com_send_act == (U1)TRUE){
        /* Send DisplayClockData to XSPI */
        vd_g_XspiIviSub1ClockDispSend(st_s_clock_disp_data);

        /* Send RTC to XSPI */
        st_t_clock_rtc_data = st_s_DateSIComRtcSet();
        vd_g_XspiIviSub1ClockRTCSend(st_t_clock_rtc_data);
        
        u1_s_datesi_com_send_act = (U1)FALSE;
    }

    if(u1_s_datesi_com_req_act == (U1)TRUE){
        /* Send Setting Status to XSPI*/
        u1_t_setting_sts        = u1_s_DateSIComSetCmpChk();
        vd_g_XspiIviSub1ClockSettingSend(u1_t_setting_sts);
        u1_s_datesi_com_req_act = (U1)FALSE;
    }

}

/*===================================================================================================================================*/
/* static ST_XSPI_IVI_CLOCK_RTC_DATA  st_s_DateSIComRtcSet(void)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         st_t_clock_rtc_data                                                                                              */
/*===================================================================================================================================*/
static ST_XSPI_IVI_CLOCK_RTC_DATA  st_s_DateSIComRtcSet(void)
{
    static  const U1                                u1_sp_DATESI_COM_WEEK_TX_VAL[DATESI_COM_RTC_WEEK_NUM] = {
        (U1)DATESI_COM_RTC_WEEK_SUN,
        (U1)DATESI_COM_RTC_WEEK_MON,
        (U1)DATESI_COM_RTC_WEEK_TUE,
        (U1)DATESI_COM_RTC_WEEK_WED,
        (U1)DATESI_COM_RTC_WEEK_THU,
        (U1)DATESI_COM_RTC_WEEK_FRI,
        (U1)DATESI_COM_RTC_WEEK_SAT
    };

    ST_XSPI_IVI_CLOCK_RTC_DATA   st_t_clock_rtc_data;
    U4                           u4_t_now_tim;
    U4                           u4_t_now_cal;
    U1                           u1_tp_time[HHMMSS_24H_TIME_SIZE];
    U2                           u2_tp_cal[YYMMDD_DATE_SIZE];
    U1                           u1_t_ans;
    U1                           u1_t_week;

    st_t_clock_rtc_data.u1_year_rtc             = (U1)DATESI_COM_RTC_YEAR_INVALID;
    st_t_clock_rtc_data.u1_month_rtc            = (U1)DATESI_COM_RTC_MONTH_INVALID;
    st_t_clock_rtc_data.u1_day_rtc              = (U1)DATESI_COM_RTC_DAY_INVALID;
    st_t_clock_rtc_data.u1_hour_rtc             = (U1)DATESI_COM_RTC_HOUR_INVALID;
    st_t_clock_rtc_data.u1_minute_rtc           = (U1)DATESI_COM_RTC_MINUTE_INVALID;
    st_t_clock_rtc_data.u1_second_rtc           = (U1)DATESI_COM_RTC_SECOND_INVALID;
    st_t_clock_rtc_data.u1_dow_rtc              = (U1)DATESI_COM_RTC_WEEK_INVALID;
    st_t_clock_rtc_data.u1_clock_set_sts_rtc    = (U1)FALSE;

    if(u1_s_datesi_com_rtc_sts == (U1)(DATESI_COM_RTC_DATA_TIM_VALID | DATESI_COM_RTC_DATA_CAL_VALID)){
        st_t_clock_rtc_data.u1_clock_set_sts_rtc = (U1)TRUE;
        u4_t_now_tim = u4_g_DateclkHhmmss24h();
        u1_t_ans = u1_g_HhmmssFrmtIs24h(u4_t_now_tim, &u1_tp_time[0]);
        if(u1_t_ans == (U1)TRUE){
            st_t_clock_rtc_data.u1_hour_rtc   = u1_tp_time[HHMMSS_24H_TIME_HR];
            st_t_clock_rtc_data.u1_minute_rtc = u1_tp_time[HHMMSS_24H_TIME_MI];
            st_t_clock_rtc_data.u1_second_rtc = u1_tp_time[HHMMSS_24H_TIME_SE];
        }
        
        u4_t_now_cal = u4_g_DateclkYymmddwk();
        u1_t_ans = u1_g_YymmddFrmtOk(u4_t_now_cal, &u2_tp_cal[0]);
        if(u1_t_ans == (U1)TRUE){
            if(u2_tp_cal[YYMMDD_DATE_YR] >= (U2)DATESI_COM_YEAR_OFFSET){
                st_t_clock_rtc_data.u1_year_rtc = (U1)(u2_tp_cal[YYMMDD_DATE_YR] - (U2)DATESI_COM_YEAR_OFFSET);
            }
            st_t_clock_rtc_data.u1_month_rtc = (U1)u2_tp_cal[YYMMDD_DATE_MO];
            st_t_clock_rtc_data.u1_day_rtc   = (U1)u2_tp_cal[YYMMDD_DATE_DA];
        }
        u1_t_week = (U1)(u4_t_now_cal & (U4)YYMMDDWK_BIT_WK);
        if(u1_t_week < (U1)DATESI_COM_RTC_WEEK_NUM){
            st_t_clock_rtc_data.u1_dow_rtc = u1_sp_DATESI_COM_WEEK_TX_VAL[u1_t_week];
        }
    }

    return(st_t_clock_rtc_data);
}

/*===================================================================================================================================*/
/* static U1       u1_s_DateSIComSetCmpChk(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_result : Result Status( DATESI_COM_SET_OK / DATESI_COM_SET_NG )                                             */
/*===================================================================================================================================*/
static U1       u1_s_DateSIComSetCmpChk(void)
{
    U1                u1_t_result;
    U1                u1_t_calendar;
    U4                u4_t_lpcnt;

    u1_t_result   = (U1)DATESI_COM_SET_NG;
    u1_t_calendar = u1_g_DateSICfgCalExst();

    if(u1_t_calendar == (U1)DATESI_CALEXIST_ON){
        if((u1_sp_datesi_com_setting_sts[(U1)DATESI_COM_KIND_TIM] == (U1)TRUE) &&
           (u1_sp_datesi_com_setting_sts[(U1)DATESI_COM_KIND_CAL] == (U1)TRUE)){
            u1_t_result = (U1)DATESI_COM_SET_OK;
        }
    }
    else{
        if(u1_sp_datesi_com_setting_sts[(U1)DATESI_COM_KIND_TIM] == (U1)TRUE){
            u1_t_result = (U1)DATESI_COM_SET_OK;
        }
    }

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)DATESI_COM_KIND_NUM; u4_t_lpcnt++){
        u1_sp_datesi_com_setting_sts[u4_t_lpcnt] = (U1)FALSE;
    }

    return(u1_t_result);

}

/*===================================================================================================================================*/
/* ST_DATESI_COMMAND_DATA  st_g_DateSIComRx(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         st_s_command_data                                                                                                */
/*===================================================================================================================================*/
ST_DATESI_COMMAND_DATA  st_g_DateSIComRx(void)
{
    return(st_s_command_data);
}

/*===================================================================================================================================*/
/* void            vd_g_DateSIComSetCmp(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_RTC_UPDT : RTC Update Status(True/False)                                                                    */
/*                  u1_a_KIND : Clock(0)/Calendar(1)                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSIComSetCmp(const U1 u1_a_RTC_UPDT, const U1 u1_a_KIND)
{
    if(u1_a_KIND < (U1)DATESI_COM_KIND_NUM){
        u1_sp_datesi_com_setting_sts[u1_a_KIND] = u1_a_RTC_UPDT;
    }
}

/*===================================================================================================================================*/
/* void            vd_g_DateSIComSetRtcCmp(const U1 u1_a_TIM, const U1 u1_a_CAL)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_TIM : Write status of the RTC time to the RtcIC(True/False)                                                 */
/*                  u1_a_CAL : Write status of the RTC Date to the RtcIC(True/False)                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSIComSetRtcCmp(const U1 u1_a_TIM, const U1 u1_a_CAL)
{
    U1                u1_t_rim_updt_flg;
    U1                u1_t_tim_setcmp_chk;
    U1                u1_t_cal_setcmp_chk;

    u1_t_rim_updt_flg   = (U1)FALSE;

    u1_t_tim_setcmp_chk = u1_s_datesi_com_rtc_sts & (U1)DATESI_COM_RTC_DATA_TIM_VALID;
    if((u1_a_TIM == (U1)TRUE) && (u1_t_tim_setcmp_chk == (U1)DATESI_COM_RTC_DATA_INVALID)){
        u1_s_datesi_com_rtc_sts |= (U1)DATESI_COM_RTC_DATA_TIM_VALID;
        u1_t_rim_updt_flg = (U1)TRUE;
    }
    u1_t_cal_setcmp_chk = u1_s_datesi_com_rtc_sts & (U1)DATESI_COM_RTC_DATA_CAL_VALID;
    if((u1_a_CAL == (U1)TRUE) && (u1_t_cal_setcmp_chk == (U1)DATESI_COM_RTC_DATA_INVALID)){
        u1_s_datesi_com_rtc_sts |= (U1)DATESI_COM_RTC_DATA_CAL_VALID;
        u1_t_rim_updt_flg = (U1)TRUE;
    }

    if(u1_t_rim_updt_flg == (U1)TRUE){
        vd_g_Rim_WriteU1((U2)RIMID_U1_RTC_STS, u1_s_datesi_com_rtc_sts);
    }
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  0.0.0    04/23/2025  MN       New.                                                                                               */
/*  0.0.1    12/18/2025  MN       Addressing issues.                                                                                 */
/*  0.1.0    02/23/2026  MN       Add reset/initialization processing.                                                               */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * MN   = Mikiya Negishi, KSE                                                                                                     */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/