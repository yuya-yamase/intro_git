/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO TECHNO Corporation                                                                                               */
/*===================================================================================================================================*/
/*  Transmission and reception processing of subframe 1 in XSPI communication.                                                       */
/*  Handled data: MISC Data                                                                                                          */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_IVI_SUB1_CLOCK_C_MAJOR                   (0)
#define XSPI_IVI_SUB1_CLOCK_C_MINOR                   (0)
#define XSPI_IVI_SUB1_CLOCK_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include    "x_spi_ivi_sub1_private.h"
#include    "x_spi_ivi_sub1_clock.h"
#include    "datesi_com.h"
/*#include    "datesi_com.h"*/
#include    "x_spi_ivi_sub4_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((XSPI_IVI_SUB1_CLOCK_C_MAJOR != XSPI_IVI_SUB1_CLOCK_H_MAJOR) || \
     (XSPI_IVI_SUB1_CLOCK_C_MINOR != XSPI_IVI_SUB1_CLOCK_H_MINOR) || \
     (XSPI_IVI_SUB1_CLOCK_C_PATCH != XSPI_IVI_SUB1_CLOCK_H_PATCH))
#error "x_spi_ivi_sub1_clock.c and x_spi_ivi_sub1_clock.h : source and header files are inconsistent!"
#endif
#if ((XSPI_IVI_SUB1_CLOCK_C_MAJOR != XSPI_IVI_SUB1_PRIVATE_H_MAJOR) || \
     (XSPI_IVI_SUB1_CLOCK_C_MINOR != XSPI_IVI_SUB1_PRIVATE_H_MINOR) || \
     (XSPI_IVI_SUB1_CLOCK_C_PATCH != XSPI_IVI_SUB1_PRIVATE_H_PATCH))
#error "x_spi_ivi_sub1_clock.c and x_spi_ivi_sub1_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define    XSPI_IVI_CLOCK_TYPE_ID         (0x35U)
#define    XSPI_IVI_CLOCK_SET_REQ         (0x01U)
#define    XSPI_IVI_CLOCK_SET_SEND        (0x02U)
#define    XSPI_IVI_CLOCK_GET_REQ         (0x03U)
#define    XSPI_IVI_CLOCK_SEND            (0x04U)

/*OS間通信データサイズ*/
#define    XSPI_IVI_CLOCK_SIZE            (21U)
#define    XSPI_IVI_CLOCK_SETTING_SIZE    (2U)

/*時刻情報データサイズ*/
#define    XSPI_IVI_CLOCK_RTC_DATA_SIZE   (8U)
#define    XSPI_IVI_CLOCK_DISP_DATA_SIZE  (12U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_sp_xspi_ivi_clock_rtc_data[XSPI_IVI_CLOCK_RTC_DATA_SIZE];
U1      u1_sp_xspi_ivi_clock_disp_data[XSPI_IVI_CLOCK_DISP_DATA_SIZE];
U1      u1_sp_xspi_ivi_clock_rtc_data_pre[XSPI_IVI_CLOCK_RTC_DATA_SIZE];
U1      u1_sp_xspi_ivi_clock_disp_data_pre[XSPI_IVI_CLOCK_DISP_DATA_SIZE];

U1      u1_s_xspi_ivi_clock_data_get_req_flg;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void            vd_s_XspiIviSub1ClockData(void);
static void            vd_s_XspiIviSub1ClockDataToQueue(const U2 u2_a_size,const U1* u1_ap_XSPI_ADD);
static U1              u1_s_XspiIviSub1ClockDataEventJdg(const U1* u1_ap_DATA,const U1* u1_ap_DATA_PRE,const U1 u1_a_size);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1ClockInit(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    初期化処理                                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1ClockInit(void)
{
    u1_s_xspi_ivi_clock_data_get_req_flg = (U1)FALSE;

    vd_g_MemfillU1(&u1_sp_xspi_ivi_clock_rtc_data[0], (U1)0U, (U4)XSPI_IVI_CLOCK_RTC_DATA_SIZE);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_clock_disp_data[0], (U1)0U, (U4)XSPI_IVI_CLOCK_DISP_DATA_SIZE);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_clock_rtc_data_pre[0], (U1)0U, (U4)XSPI_IVI_CLOCK_RTC_DATA_SIZE);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_clock_disp_data_pre[0], (U1)0U, (U4)XSPI_IVI_CLOCK_DISP_DATA_SIZE);

}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1ClcokMainTask(void)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    定期処理                                                                                                          */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1ClcokMainTask(void)
{
    U1   u1_t_clock_event_jdg;

    if(u1_s_xspi_ivi_clock_data_get_req_flg == (U1)TRUE){
        u1_t_clock_event_jdg = u1_s_XspiIviSub1ClockDataEventJdg(&u1_sp_xspi_ivi_clock_rtc_data[0],&u1_sp_xspi_ivi_clock_rtc_data_pre[0],(U1)XSPI_IVI_CLOCK_RTC_DATA_SIZE);
        u1_t_clock_event_jdg |= u1_s_XspiIviSub1ClockDataEventJdg(&u1_sp_xspi_ivi_clock_disp_data[0],&u1_sp_xspi_ivi_clock_disp_data_pre[0],(U1)XSPI_IVI_CLOCK_DISP_DATA_SIZE);

        if(u1_t_clock_event_jdg == (U1)TRUE) {
            vd_s_XspiIviSub1ClockData();
        }
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1ClockAna(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_DATA_SIZE)                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*                  u2_a_DATA_SIZE : Data Size                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1ClockAna(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_DATA_SIZE)
{
    U1 u1_t_subtype;
    ST_DATESI_COMMAND_DATA st_t_data;

    u1_t_subtype = u1_ap_XSPI_ADD[0];

    switch (u1_t_subtype)
    {
    case XSPI_IVI_CLOCK_SET_REQ:
    /*DateSIに時刻情報を渡す*/
        st_t_data.u1_clk_year      = u1_ap_XSPI_ADD[1];
        st_t_data.u1_clk_mont      = u1_ap_XSPI_ADD[2];
        st_t_data.u1_clk_day       = u1_ap_XSPI_ADD[3];
        st_t_data.u1_clk_hour      = u1_ap_XSPI_ADD[4];
        st_t_data.u1_clk_min       = u1_ap_XSPI_ADD[5];
        st_t_data.u1_clk_sec       = u1_ap_XSPI_ADD[6];
        st_t_data.u1_gps_st        = u1_ap_XSPI_ADD[7];
        st_t_data.u1_gps_crct      = u1_ap_XSPI_ADD[8];
        st_t_data.u1_tz            = u1_ap_XSPI_ADD[9];
        st_t_data.u1_tz_sign       = u1_ap_XSPI_ADD[10];
        st_t_data.u1_dst_s30       = u1_ap_XSPI_ADD[11];
        st_t_data.u1_hour_usw      = u1_ap_XSPI_ADD[12];
        st_t_data.u1_hour_dsw      = u1_ap_XSPI_ADD[13];
        st_t_data.u1_min_usw       = u1_ap_XSPI_ADD[14];
        st_t_data.u1_min_dsw       = u1_ap_XSPI_ADD[15];
        st_t_data.u1_oset_usw      = u1_ap_XSPI_ADD[16];
        st_t_data.u1_oset_dsw      = u1_ap_XSPI_ADD[17];
        st_t_data.u1_clkfmtsw      = u1_ap_XSPI_ADD[18];
        st_t_data.u1_m_rst_sw      = u1_ap_XSPI_ADD[19];
        st_t_data.u1_clk_year_updt = u1_ap_XSPI_ADD[20];
        st_t_data.u1_clk_mont_updt = u1_ap_XSPI_ADD[21];
        st_t_data.u1_clk_day_updt  = u1_ap_XSPI_ADD[22];

        vd_g_DateSIComCommandRx(st_t_data);
        break;
    case XSPI_IVI_CLOCK_GET_REQ:
        u1_s_xspi_ivi_clock_data_get_req_flg = (U1)TRUE;
        break;
    default:
        break;
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1ClockSettingSend(const U1 u1_a_DATA)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_a_DATA : 時刻設定応答                                                                                          */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1ClockSettingSend(const U1 u1_a_DATA)
{
    U1     u1_tp_data[2];

    u1_tp_data[0] = (U1)XSPI_IVI_CLOCK_SET_SEND;
    u1_tp_data[1] = u1_a_DATA;
    vd_s_XspiIviSub1ClockDataToQueue((U2)XSPI_IVI_CLOCK_SETTING_SIZE,u1_tp_data);
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1ClockRTCSend(const ST_XSPI_IVI_CLOCK_RTC_DATA st_a_DATA)                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      st_a_DATA : RTC時刻情報                                                                                           */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1ClockRTCSend(const ST_XSPI_IVI_CLOCK_RTC_DATA st_a_DATA)
{
    u1_sp_xspi_ivi_clock_rtc_data[0]  = st_a_DATA.u1_year_rtc;
    u1_sp_xspi_ivi_clock_rtc_data[1]  = st_a_DATA.u1_month_rtc;
    u1_sp_xspi_ivi_clock_rtc_data[2]  = st_a_DATA.u1_day_rtc;
    u1_sp_xspi_ivi_clock_rtc_data[3]  = st_a_DATA.u1_hour_rtc;
    u1_sp_xspi_ivi_clock_rtc_data[4]  = st_a_DATA.u1_minute_rtc;
    u1_sp_xspi_ivi_clock_rtc_data[5]  = st_a_DATA.u1_second_rtc;
    u1_sp_xspi_ivi_clock_rtc_data[6]  = st_a_DATA.u1_dow_rtc;
    u1_sp_xspi_ivi_clock_rtc_data[7]  = st_a_DATA.u1_clock_set_sts_rtc;

    vd_g_XspiIviClockUTCPut(&u1_sp_xspi_ivi_clock_rtc_data[0]);
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1ClockDispSend(const ST_XSPI_IVI_CLOCK_DISP_DATA st_a_DATA)                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      st_a_DATA : 表示時刻情報                                                                                          */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1ClockDispSend(const ST_XSPI_IVI_CLOCK_DISP_DATA st_a_DATA)
{
    u1_sp_xspi_ivi_clock_disp_data[0]  = st_a_DATA.u1_year_disp;
    u1_sp_xspi_ivi_clock_disp_data[1]  = st_a_DATA.u1_month_disp;
    u1_sp_xspi_ivi_clock_disp_data[2]  = st_a_DATA.u1_day_disp;
    u1_sp_xspi_ivi_clock_disp_data[3]  = st_a_DATA.u1_dow_disp;
    u1_sp_xspi_ivi_clock_disp_data[4]  = st_a_DATA.u1_hour_disp;
    u1_sp_xspi_ivi_clock_disp_data[5]  = st_a_DATA.u1_minute_disp;
    u1_sp_xspi_ivi_clock_disp_data[6]  = st_a_DATA.u1_second_disp;
    u1_sp_xspi_ivi_clock_disp_data[7]  = st_a_DATA.u1_hour_offset_disp;
    u1_sp_xspi_ivi_clock_disp_data[8]  = st_a_DATA.u1_minute_offset_disp;
    u1_sp_xspi_ivi_clock_disp_data[9]  = st_a_DATA.u1_sign_offset_disp;
    u1_sp_xspi_ivi_clock_disp_data[10] = st_a_DATA.u1_ampm_disp;
    u1_sp_xspi_ivi_clock_disp_data[11] = st_a_DATA.u1_1224format_disp;
}

/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub1ClockData(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      st_a_DATA : 時刻情報                                                                                              */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1ClockData(void)
{
    U1 u1_tp_data[XSPI_IVI_CLOCK_SIZE];

    u1_tp_data[0] = (U1)XSPI_IVI_CLOCK_SEND;
    vd_g_MemcpyU1(&u1_tp_data[1],&u1_sp_xspi_ivi_clock_rtc_data[0],(U4)XSPI_IVI_CLOCK_RTC_DATA_SIZE);
    vd_g_MemcpyU1(&u1_tp_data[9],&u1_sp_xspi_ivi_clock_disp_data[0],(U4)XSPI_IVI_CLOCK_DISP_DATA_SIZE);
    vd_s_XspiIviSub1ClockDataToQueue((U2)XSPI_IVI_CLOCK_SIZE,u1_tp_data);

    vd_g_MemcpyU1(&u1_sp_xspi_ivi_clock_rtc_data_pre[0],&u1_sp_xspi_ivi_clock_rtc_data[0],(U4)XSPI_IVI_CLOCK_RTC_DATA_SIZE);
    vd_g_MemcpyU1(&u1_sp_xspi_ivi_clock_disp_data_pre[0],&u1_sp_xspi_ivi_clock_disp_data[0],(U4)XSPI_IVI_CLOCK_DISP_DATA_SIZE);
}

/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub1ClockDataToQueue(const U2 u2_a_SIZE,const U1 u1_a_XSPI_ADD)                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*                  u2_a_data_size : Data Size                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1ClockDataToQueue(const U2 u2_a_SIZE,const U1* u1_ap_XSPI_ADD)
{
    U1     u1_tp_data[XSPI_IVI_CLOCK_SIZE];
    U1     u1_t_id;

    u1_t_id = (U1)XSPI_IVI_CLOCK_TYPE_ID;

    vd_g_MemfillU1(&u1_tp_data[0], (U1)0U, (U4)XSPI_IVI_CLOCK_SIZE);
    vd_g_MemcpyU1(&u1_tp_data[0], &u1_ap_XSPI_ADD[0], (U4)u2_a_SIZE);

    /*キューの関数呼び出し（そっちでヘッダーとかは入れてく）*/
    vd_g_XspiIviSub1MISCStuckBuff(u1_t_id,u2_a_SIZE,u1_tp_data);
}

/*===================================================================================================================================*/
/*  U1          u1_s_XspiIviSub1ClockDataEventJdg(const U1* u1_ap_DATA,const U1* u1_ap_DATA_PRE,const U1 u1_a_size)                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*                  u2_a_data_size : Data Size                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1            u1_s_XspiIviSub1ClockDataEventJdg(const U1* u1_ap_DATA,const U1* u1_ap_DATA_PRE,const U1 u1_a_size)
{
    U1     u1_t_judge;
    U4     u4_t_loop;

    u1_t_judge = (U1)FALSE;
    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)u1_a_size; u4_t_loop++){
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
/*  0.0.0    04/25/2025  KT       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * KT   = Kenta Takaji, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
