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
#define DATESI_CAL_CFG_C_MAJOR                  (0)
#define DATESI_CAL_CFG_C_MINOR                  (0)
#define DATESI_CAL_CFG_C_PATCH                  (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "datesi_cal_cfg_private.h"
#include "datesi_cfg_private.h"
#include "datesi_com.h"
#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#include "es_inspect.h"
#endif
#include "rim_ctl.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DATESI_CAL_CFG_C_MAJOR != DATESI_CAL_H_MAJOR) || \
     (DATESI_CAL_CFG_C_MINOR != DATESI_CAL_H_MINOR) || \
     (DATESI_CAL_CFG_C_PATCH != DATESI_CAL_H_PATCH))
#error "datesi_cal_cfg.c and datesi_cal.h : source and header files are inconsistent!"
#endif

#if ((DATESI_CAL_CFG_C_MAJOR != DATESI_CAL_CFG_H_MAJOR) || \
     (DATESI_CAL_CFG_C_MINOR != DATESI_CAL_CFG_H_MINOR) || \
     (DATESI_CAL_CFG_C_PATCH != DATESI_CAL_CFG_H_PATCH))
#error "datesi_cal_cfg.c and datesi_cal_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DATESI_CAL_WEEK_NUM                     (7U)                                         /* Week Num                             */
#define DATESI_CAL_CAN_WEEK_INVALID             (0U)                                         /* Invalid Value                        */
#define DATESI_CAL_CAN_WEEK_MON                 (1U)                                         /* Monday                               */
#define DATESI_CAL_CAN_WEEK_TUE                 (2U)                                         /* Tuesday                              */
#define DATESI_CAL_CAN_WEEK_WED                 (3U)                                         /* Wednesday                            */
#define DATESI_CAL_CAN_WEEK_THU                 (4U)                                         /* Thursday                             */
#define DATESI_CAL_CAN_WEEK_FRI                 (5U)                                         /* Friday                               */
#define DATESI_CAL_CAN_WEEK_SAT                 (6U)                                         /* Saturday                             */
#define DATESI_CAL_CAN_WEEK_SUN                 (7U)                                         /* Sunday                               */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if 0
const   U2                                      u2_g_DATESI_CAL_NVMCID_CALE   = (U2)NVMCID_U2_DATESI_CALENDAR;
#else
const   U2                                      u2_g_DATESI_CAL_NVMCID_CALE   = (U2)U2_MAX;
#endif
const   U2                                      u2_g_DATESI_CAL_YEAR_MAX      = (U2)DATESI_CAL_YEAR_MAX;
const   U4                                      u4_g_DATESI_CAL_DAYCNT_MAX    = (U4)DATESI_CAL_DAYCNT_MAX;
const   U4                                      u4_g_DATESI_CAL_DAYCNT_ABSMAX = (U4)DATESI_CAL_DAYCNT_ABSMAX;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DATESI_CAL_STSBIT_UNKNOWN != COM_NO_RX  ) || \
     (DATESI_CAL_STSBIT_INVALID != COM_TIMEOUT))
#error "datesi_cal status bit and com status bit are inconsistent!"
#endif
/*===================================================================================================================================*/
/* U1              u1_g_DateSICalCfgCanRx(ST_DATESI_CAL_RX * stp_a_rx)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_DateSICalCfgCanRx(ST_DATESI_CAL_RX * stp_a_rx)
{
    ST_DATESI_COMMAND_DATA  st_t_command_data;
    U1                      u1_t_status;
    U1                      u1_t_gpsst;
    U1                      u1_t_gpscrst;

    u1_t_status  = (U1)DATESI_CAL_STSBIT_UNKNOWN;
    u1_t_gpsst   = (U1)FALSE;
    u1_t_gpscrst = (U1)FALSE;

    st_t_command_data = st_g_DateSIComRx();
    stp_a_rx->u1p_date[YYMMDD_DATE_DA] = st_t_command_data.u1_clk_day;
    stp_a_rx->u1p_date[YYMMDD_DATE_MO] = st_t_command_data.u1_clk_mont;
    stp_a_rx->u1p_date[YYMMDD_DATE_YR] = st_t_command_data.u1_clk_year;
    u1_t_gpsst                         = st_t_command_data.u1_gps_st;
    u1_t_gpscrst                       = st_t_command_data.u1_gps_crct;

    if(u1_t_gpsst == (U1)TRUE){
        stp_a_rx->u1_valid = (U1)TRUE;
    }
    else{
        stp_a_rx->u1_valid = (U1)FALSE;
    }
    if(u1_t_gpscrst == (U1)TRUE){
        stp_a_rx->u1_act = (U1)TRUE;
    }
    else{
        stp_a_rx->u1_act = (U1)FALSE;
    }

    u1_t_status = (U1)DATESI_CAL_STSBIT_VALID; /* BEV BSW provisionally */

    return(u1_t_status);
}

/*===================================================================================================================================*/
/* void            vd_g_DateSICalCfgCanTx(const U4 u4_a_YYYYMMDD, const U1 u1_a_EVENT_EI)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSICalCfgCanTx(const U4 u4_a_YYYYMMDD, const U1 u1_a_EVENT_EI)
{
#if defined(ComConf_ComSignal_M_WEEK)
    static  const U1                                u1_sp_DATESI_CAL_WEEK_TX_VAL[DATESI_CAL_WEEK_NUM] = {
        (U1)DATESI_CAL_CAN_WEEK_SUN,
        (U1)DATESI_CAL_CAN_WEEK_MON,
        (U1)DATESI_CAL_CAN_WEEK_TUE,
        (U1)DATESI_CAL_CAN_WEEK_WED,
        (U1)DATESI_CAL_CAN_WEEK_THU,
        (U1)DATESI_CAL_CAN_WEEK_FRI,
        (U1)DATESI_CAL_CAN_WEEK_SAT
    };
#endif /* ComConf_ComSignal_M_WEEK */
#if defined(ComConf_ComSignal_M_YEAR)
    U2  u2_t_year;
#endif /* ComConf_ComSignal_M_YEAR */
#if defined(ComConf_ComSignal_M_WEEK)
    U4  u4_t_dycnt;
    U1  u1_t_week;
#endif /* ComConf_ComSignal_M_WEEK */
    U1  u1_t_can_trig;
#if (defined(ComConf_ComSignal_M_DAY)   || \
     defined(ComConf_ComSignal_M_MONTH) || \
     defined(ComConf_ComSignal_M_YEAR)  || \
     defined(ComConf_ComSignal_M_WEEK))
#if 0 /* BEV provisionally */
    U1  u1_t_pretx;
#else
    ST_XSPI_IVI_CLOCK_DISP_DATA st_t_pre_tx;
#endif
    U1  u1_t_date[YYMMDD_DATE_SIZE];
    U2  u2_t_cal_min;

#if 0
    u2_t_cal_min   = u2_CALIB_MCUID0575_CAL_MIN;
#else
    u2_t_cal_min   = (U2)2021U;
#endif
#if 0 /* BEV provisionally */
    u1_t_pretx     = (U1)0U;
#else
    st_t_pre_tx    = st_g_DateSIComPreTx();
#endif
#endif

    u1_t_can_trig  = (U1)FALSE;

#if defined(ComConf_ComSignal_M_YEAR)
    u2_t_year = (U2)((u4_a_YYYYMMDD & (U4)YYMMDDWK_BIT_YR) >> YYMMDDWK_LSB_YR);
    if(u2_t_year >= (U2)DATESI_CAL_YEAR_OFFSET){
        u1_t_date[YYMMDD_DATE_YR] = (U1)(u2_t_year - (U2)DATESI_CAL_YEAR_OFFSET);
    }
    else{
        u1_t_date[YYMMDD_DATE_YR] = (U1)(u2_t_cal_min - (U2)DATESI_CAL_YEAR_OFFSET);
    }
#if 0 /* BEV provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_M_YEAR, &u1_t_pretx);
    if(u1_t_pretx != u1_t_date[YYMMDD_DATE_YR]){
#else
    if(st_t_pre_tx.u1_year_disp != u1_t_date[YYMMDD_DATE_YR]){
#endif
        vd_g_DateSIComClockDispUpdate(u1_t_date[YYMMDD_DATE_YR], DATESI_COM_M_YEAR, u1_a_EVENT_EI);
#if 0 /* BEV provisionally */
        (void)Com_SendSignal(ComConf_ComSignal_M_YEAR, &u1_t_date[YYMMDD_DATE_YR]);
#endif
        u1_t_can_trig = (U1)TRUE;
    }
#endif /* ComConf_ComSignal_M_YEAR */

#if defined(ComConf_ComSignal_M_MONTH)
    u1_t_date[YYMMDD_DATE_MO] = (U1)((u4_a_YYYYMMDD & (U4)YYMMDDWK_BIT_MO) >> YYMMDDWK_LSB_MO);
#if 0 /* BEV provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_M_MONTH, &u1_t_pretx);
    if(u1_t_pretx != u1_t_date[YYMMDD_DATE_MO]){
#else
    if(st_t_pre_tx.u1_month_disp != u1_t_date[YYMMDD_DATE_MO]){
#endif
        vd_g_DateSIComClockDispUpdate(u1_t_date[YYMMDD_DATE_MO], DATESI_COM_M_MONTH, u1_a_EVENT_EI);
#if 0 /* BEV provisionally */
        (void)Com_SendSignal(ComConf_ComSignal_M_MONTH, &u1_t_date[YYMMDD_DATE_MO]);
#endif
        u1_t_can_trig = (U1)TRUE;
    }
#endif /* ComConf_ComSignal_M_MONTH */
#if defined(ComConf_ComSignal_M_DAY)
    u1_t_date[YYMMDD_DATE_DA] = (U1)((u4_a_YYYYMMDD & (U4)YYMMDDWK_BIT_DA) >> YYMMDDWK_LSB_DA);
#if 0 /* BEV provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_M_DAY, &u1_t_pretx);
    if(u1_t_pretx != u1_t_date[YYMMDD_DATE_DA]){
#else
    if(st_t_pre_tx.u1_day_disp != u1_t_date[YYMMDD_DATE_DA]){
#endif
        vd_g_DateSIComClockDispUpdate(u1_t_date[YYMMDD_DATE_DA], DATESI_COM_M_DAY, u1_a_EVENT_EI);
#if 0 /* BEV provisionally */
        (void)Com_SendSignal(ComConf_ComSignal_M_DAY, &u1_t_date[YYMMDD_DATE_DA]);
#endif
        u1_t_can_trig = (U1)TRUE;
    }
#endif /* ComConf_ComSignal_M_DAY */
#if defined(ComConf_ComSignal_M_WEEK)
    u4_t_dycnt                = u4_g_YymmddToDaycnt(u4_a_YYYYMMDD);
    u1_t_week                 = u1_g_DayOfWeek(u4_t_dycnt);

    if(u1_t_week < (U1)DATESI_CAL_WEEK_NUM){
        u1_t_week = u1_sp_DATESI_CAL_WEEK_TX_VAL[u1_t_week];
    }
    else{
        u1_t_week = (U1)DATESI_CAL_CAN_WEEK_INVALID;
    }
#if 0 /* BEV provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_M_WEEK, &u1_t_pretx);
    if(u1_t_pretx != u1_t_week){
#else
    if(st_t_pre_tx.u1_dow_disp != u1_t_week){
#endif
        vd_g_DateSIComClockDispUpdate(u1_t_week, DATESI_COM_M_WEEK, u1_a_EVENT_EI);
#if 0 /* BEV provisionally */
        (void)Com_SendSignal(ComConf_ComSignal_M_WEEK, &u1_t_week);
#endif
        u1_t_can_trig = (U1)TRUE;
    }
#endif /* ComConf_ComSignal_M_WEEK */

    if((u1_t_can_trig == (U1)TRUE) &&
       (u1_a_EVENT_EI == (U1)TRUE)){
#if 0 /* BEV provisionally */
        (void)Com_TriggerIPDUSend(MSG_MET1S33_TXCH0);
#endif
    }
}

/*===================================================================================================================================*/
/* U1              u1_g_DateSICalCfgEsichk(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_DateSICalCfgEsichk(void)
{
#if 0   /* BEV BSW provisionally */
    return (u1_g_ESInspectMdBfield());
#else
    return ((U1)0U);
#endif
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
/*                                                                                                                                   */
/*  * MN   = Mikiya Negishi, KSE                                                                                                     */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
