/* 1.12.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Complex Driver : Date/Clock                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DATE_CLK_CFG_C_MAJOR                     (1U)
#define DATE_CLK_CFG_C_MINOR                     (12U)
#define DATE_CLK_CFG_C_PATCH                     (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "date_clk.h"
#include "date_clk_cfg_private.h"

#include "ivdsh.h"
#include "rim_ctl.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DATE_CLK_CFG_C_MAJOR != DATE_CLK_CFG_H_MAJOR) || \
     (DATE_CLK_CFG_C_MINOR != DATE_CLK_CFG_H_MINOR) || \
     (DATE_CLK_CFG_C_PATCH != DATE_CLK_CFG_H_PATCH))
#error "date_clk_cfg.c and date_clk_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DATE_CLK_OFFSET_2000DAYCUNT              (730485U)                              /* [days] Jan-1st-2000  */
#define DATE_CLK_DAYCNT_DISP_MAX                 (DATE_CLK_OFFSET_2000DAYCUNT + 36524U) /* [days] Dec-31st-2099 */
#define DATE_CLK_CAL_MIN_MM_DD                   (0x00001010U)
#define DATE_CLK_CAL_DEF_MM_DD                   (0x00001010U)
#define DATE_CLK_CAL_MIN_MINUS                   (1U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u2_DATESI_CAL_DEF                        ((U2)2050U)                            /* Disp Default Year                         */
#define u2_DATESI_CAL_YEAR_MIN                   ((U2)2000U)                            /* Disp Min Year                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define __DATE_CLK_DET__                         (0U)   /* Debug Use Only. DO NOT ENABLE THIS OPTION IN MASS-PRODUCTION USE */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (__DATE_CLK_DET__ == 1U)
static U1                  u1_s_dateclk_errcnt                 __attribute__((section(".bss_BACK")));
static ST_DATE_CLK_LOG     st_s_dateclk_log_latest             __attribute__((section(".bss_BACK")));
#endif /* #if (__DATE_CLK_DET__ == 1U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static        U4      u4_s_DateclkCfgCaldefValJdg(void);
static        U4      u4_s_DateclkCfgGetDayCntMin(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
/* Attention :                                                                         */
/* ----------------------------------------------------------------------------------- */
/* If there is an error in Day Count Minimum RAM, the value of                         */
/* u4_g_DATE_CLK_DAYCNT_MIN is used.                                                   */
/* ----------------------------------------------------------------------------------- */
const U4            u4_g_DATE_CLK_DAYCNT_MIN = (U4)DATE_CLK_DAYCNT_MIN;
const U4            u4_g_DATE_CLK_DAYCNT_MAX = (U4)DATE_CLK_DAYCNT_MAX;

const U2            u2_g_DATE_CLK_ADJ_TOUT     = (U2)1000U / (U2)DATE_CLK_MAIN_TICK;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U4      u4_g_DateclkCfgHhmmss24hInit(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_DateclkCfgHhmmss24hInit(void)
{
    U4                 u4_t_hhmmss_24h;

    u4_t_hhmmss_24h = (U4)0U;

    return(u4_t_hhmmss_24h);  /* 00:00:00 */
}
/*===================================================================================================================================*/
/*  U4      u4_g_DateclkCfgDaycntInit(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_DateclkCfgDaycntInit(void)
{
    U4  u4_t_date_calendar;
    U2  u2_t_date_calendar_rim;
    U4  u4_t_daycnt;
    U4  u4_t_ret;
    U1  u1_t_sts;
    U1  u1_t_read_sts;
    U4  u4_t_daycnt_min;

    u1_t_sts           = (U1)FALSE;
    u4_t_ret           = u4_s_DateclkCfgCaldefValJdg();
    u4_t_date_calendar = (U4)0U;
    u1_t_read_sts      = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_VM1TO2_CAL, &u4_t_date_calendar, (U2)1U);
    u4_t_daycnt_min    = u4_s_DateclkCfgGetDayCntMin();
    
    if(u1_t_read_sts == (U1)IVDSH_NO_REA){
        u1_t_read_sts = u1_g_Rim_ReadU2withStatus((U2)RIMID_U2_CAL_DATE, &u2_t_date_calendar_rim);
        if ((u1_t_read_sts  & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK) {
            u4_t_date_calendar = (U4)u2_t_date_calendar_rim;
            u1_t_sts           = (U1)TRUE;
        }
    }
    else {
        u1_t_sts = (U1)TRUE;
    }

    if (u1_t_sts == (U1)TRUE) {
        u4_t_daycnt = u4_t_date_calendar + (U4)DATE_CLK_OFFSET_2000DAYCUNT;
        /* The type of u2_t_date_calendar is U2, so max value of u2_t_date_calendar is 65535.        */
        /* Therefor (u2_t_date_calendar + DATE_CLK_OFFSET_2000DAYCUNT) is always lower than U4_MAX   */
        if((u4_t_daycnt >= u4_t_daycnt_min) &&
           (u4_t_daycnt <= (U4)DATE_CLK_DAYCNT_DISP_MAX)){
            u4_t_ret = u4_t_daycnt;
        }
        vd_g_DateclkYymmdd_Commit((U1)TRUE);
    }
    else {
        vd_g_DateclkYymmdd_Commit((U1)FALSE);
    }
    return(u4_t_ret);
}
/*===================================================================================================================================*/
/*  void    vd_g_DateclkCfgLogCapt(const ST_DATE_CLK_LOG * st_ap_LOG, const U1 u1_a_ADJ)                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DateclkCfgLogCapt(const ST_DATE_CLK_LOG * st_ap_LOG, const U1 u1_a_ADJ)
{
#if (__DATE_CLK_DET__ == 1U)
    st_s_dateclk_log_latest.u4_hhmmss_bfr = st_ap_LOG->u4_hhmmss_bfr;
    st_s_dateclk_log_latest.u4_daycnt_bfr = st_ap_LOG->u4_daycnt_bfr;
    st_s_dateclk_log_latest.u4_hhmmss_aft = st_ap_LOG->u4_hhmmss_aft;
    st_s_dateclk_log_latest.u4_daycnt_aft = st_ap_LOG->u4_daycnt_aft;
    st_s_dateclk_log_latest.u4_sec_elpsd  = st_ap_LOG->u4_sec_elpsd;
    st_s_dateclk_log_latest.u1_rtc_rea    = st_ap_LOG->u1_rtc_rea;
    st_s_dateclk_log_latest.u1_rtc_sta    = st_ap_LOG->u1_rtc_sta;
    st_s_dateclk_log_latest.u1_eas_chk    = st_ap_LOG->u1_eas_chk;
    st_s_dateclk_log_latest.u1_callpt     = st_ap_LOG->u1_callpt;

    if(u1_s_dateclk_errcnt >= (U1)U1_MAX){

     /* u1_s_dateclk_errcnt = (U1)U1_MAX; */
    }
    else if(st_ap_LOG->u1_eas_chk != (U1)0U){

        u1_s_dateclk_errcnt++;
    }
    else if((u1_a_ADJ              != (U1)0U                     ) &&
            (st_ap_LOG->u1_rtc_sta != (U1)DATE_CLK_LOG_IF_RTC_UNK) &&
            (st_ap_LOG->u1_rtc_sta != (U1)DATE_CLK_IF_RTC_RUN    )){

        u1_s_dateclk_errcnt++;
    }
    else{

        /* keep last */
    }
#endif
}
/*===================================================================================================================================*/
/*  U4      u4_g_DateclkCfgDayCntMinValJdg(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_DateclkCfgDayCntMinValJdg(void)
{
    U4                 u4_t_min_daycnt;

    u4_t_min_daycnt  = u4_s_DateclkCfgGetDayCntMin();
    if(u4_t_min_daycnt > (U4)DATE_CLK_CAL_MIN_MINUS){
        u4_t_min_daycnt -= (U4)DATE_CLK_CAL_MIN_MINUS;
    }

    return(u4_t_min_daycnt);
}
/*===================================================================================================================================*/
/*  static U4   u4_s_DateclkCfgCaldefValJdg(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4    u4_s_DateclkCfgCaldefValJdg(void)
{
    U4                 u4_t_caldef_val;
    U2                 u2_t_caldef_val_rim;
    U4                 u4_t_def_yymmdd;
    U4                 u4_t_def_daycnt;
    U1                 u1_t_sts;
    U1                 u1_t_read_sts;

    u1_t_sts         = (U1)FALSE;
    u4_t_caldef_val  = (U4)0U;
    u1_t_read_sts = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_VM1TO2_CALDEF, &u4_t_caldef_val, (U2)1U);
    if(u1_t_read_sts == (U1)IVDSH_NO_REA){
        u1_t_read_sts = u1_g_Rim_ReadU2withStatus((U2)RIMID_U2_CAL_DEF, &u2_t_caldef_val_rim);
        if ((u1_t_read_sts  & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK) {
            u4_t_caldef_val = (U4)u2_t_caldef_val_rim;
            u1_t_sts = (U1)TRUE;
        }
    }
    else {
        u1_t_sts = (U1)TRUE;
    }

    if((u1_t_sts == (U1)FALSE) || (u4_t_caldef_val > (U4)U2_MAX)){
        u4_t_caldef_val  = (U4)u2_DATESI_CAL_DEF;
    }
    u4_t_def_yymmdd  = (U4)DATE_CLK_CAL_DEF_MM_DD;
    u4_t_def_yymmdd |= (u4_t_caldef_val << YYMMDDWK_LSB_YR);
    u4_t_def_daycnt  = u4_g_YymmddToDaycnt(u4_t_def_yymmdd);

    return(u4_t_def_daycnt);
}
/*===================================================================================================================================*/
/*  static U4   u4_s_DateclkCfgGetDayCntMin(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4    u4_s_DateclkCfgGetDayCntMin(void)
{
    U4                 u4_t_calmin_val;
    U2                 u2_t_calmin_val_rim;
    U4                 u4_t_min_yymmdd;
    U4                 u4_t_min_daycnt;
    U1                 u1_t_sts;
    U1                 u1_t_read_sts;

    u1_t_sts        = (U1)FALSE;
    u4_t_calmin_val = (U4)0U;
    u1_t_read_sts = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_VM1TO2_CALMIN, &u4_t_calmin_val, (U2)1U);
    if(u1_t_read_sts == (U1)IVDSH_NO_REA){
        u1_t_read_sts = u1_g_Rim_ReadU2withStatus((U2)RIMID_U2_CAL_MIN, &u2_t_calmin_val_rim);
        if ((u1_t_read_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK) {
            u4_t_calmin_val = (U4)u2_t_calmin_val_rim;
            u1_t_sts = (U1)TRUE;
        }
    }
    else {
        u1_t_sts = (U1)TRUE;
    }

    if((u1_t_sts == (U1)FALSE) || (u4_t_calmin_val > (U4)U2_MAX)){
        u4_t_calmin_val  = (U4)u2_DATESI_CAL_YEAR_MIN;
    }
    u4_t_min_yymmdd  = (U4)DATE_CLK_CAL_MIN_MM_DD;
    u4_t_min_yymmdd |= (u4_t_calmin_val << YYMMDDWK_LSB_YR);
    u4_t_min_daycnt  = u4_g_YymmddToDaycnt(u4_t_min_yymmdd);

    return(u4_t_min_daycnt);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     9/ 9/2015  TN       New.                                                                                               */
/*  1.1.0     9/11/2015  TN       date_clk v1.0.0 -> v1.1.0.                                                                         */
/*  1.2.0     9/11/2015  TN       date_clk v1.1.0 -> v1.2.0.                                                                         */
/*  1.3.0     1/18/2015  TN       date_clk v1.2.0 -> v1.3.0.                                                                         */
/*  1.4.0     6/ 8/2016  TN       date_clk v1.3.0 -> v1.4.0.                                                                         */
/*  1.5.0    11/ 7/2016  TN       date_clk v1.4.0 -> v1.5.0.                                                                         */
/*  1.6.0    11/16/2016  TN       date_clk v1.5.0 -> v1.6.0.                                                                         */
/*  1.7.0    11/16/2016  TN       date_clk v1.6.0 -> v1.7.0.                                                                         */
/*  1.8.0    11/18/2016  TN       date_clk v1.7.0 -> v1.8.0.                                                                         */
/*  1.8.1     4/ 7/2017  TN       date_clk v1.8.0 -> v1.8.1.                                                                         */
/*  1.9.0     6/23/2021  TN       date_clk v1.8.1 -> v1.9.0.                                                                         */
/*  1.10.0    9/ 3/2021  TN       date_clk v1.9.1 -> v1.10.0.                                                                        */
/*  1.11.0   12/16/2021  TN       date_clk v1.10.0 -> v1.11.0.                                                                       */
/*  1.11.1   11/ 7/2023  KN       date_clk v1.11.0 -> v1.11.1.                                                                       */
/*  1.12.0    8/21/2024  KM       u4_g_DateclkCfgDayCntMinValJdg was implemented.                                                    */
/*  1.12.1   10/21/2024  SY       date_clk v1.12.0 -> v1.12.1.                                                                       */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  800B-1    4/ 3/2020  TaN     Change config for 800B CV                                                                           */
/*  800B-2   10/ 7/2020  TaN     Change config for 800B CV-R                                                                         */
/*  893B-1   10/28/2021  TaN     Add ETM_CH for AMBTM                                                                                */
/*  130D-1   11/22/2022  ToK     Fix BON date initial value change                                                                   */
/*                               Change config for 130D Pre1A                                                                        */
/*  100D-1   05/16/2023  TaN     Config For 100D                                                                                     */
/*  19PFv3-1 10/16/2023  IzH     Change config for 19PFv3                                                                            */
/*  19PFv3-2  1/11/2024  SH      Change MCUCONST guard process to set default                                                        */
/*  19PFv3-3  4/16/2024  SH      Add calibration guard                                                                               */
/*  19PFv3-4  6/27/2024  TN(DT)  Delete Calibration Guard Process.                                                                   */
/*  19PFv3-5 11/19/2024  KH      Fix function definition and comment                                                                 */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * KN   = Keigo Nomura , Denso Create                                                                                             */
/*  * KM   = Kazuyuki Makino, DENSO                                                                                                  */
/*  * TaN  = Tatsuya Niimi, KSE                                                                                                      */
/*  * ToK  = Toru Kamishina, Denso Techno                                                                                            */
/*  * IzH  = Izumi Hariyama, Denso Techno                                                                                            */
/*  * SH   = Sae Hirose,     Denso Techno                                                                                            */
/*  * TN(DT) = Tetsushi Nakano, Denso Techno                                                                                         */
/*  * KH   = Kiko Huerte, DTPH                                                                                                       */
/*  * SY   = Satoshi Yamada, DENSO                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
