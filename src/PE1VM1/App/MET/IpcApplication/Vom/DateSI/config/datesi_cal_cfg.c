/* 3.2.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Date clock Synchronization Interface                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DATESI_CAL_CFG_C_MAJOR                  (3)
#define DATESI_CAL_CFG_C_MINOR                  (2)
#define DATESI_CAL_CFG_C_PATCH                  (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "datesi_cal_cfg_private.h"
#include "datesi_cfg_private.h"
#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "oxcan_channel_STUB.h"
#endif
#if 0   /* BEV BSW provisionally */
#include "es_inspect.h"
#else
#include "es_inspect_STUB.h"
#endif
#include "rim_ctl.h"
#if 0   /* BEV BSW provisionally */
#else
#include "rim_ctl_cfg_STUB.h"
#endif

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
const   U2                                      u2_g_DATESI_CAL_NVMCID_CALE   = (U2)NVMCID_U2_DATESI_CALENDAR;
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
    U1  u1_t_status;
    U1  u1_t_gpsst;
    U1  u1_t_gpscrst;

    u1_t_status  = (U1)DATESI_CAL_STSBIT_UNKNOWN;
    u1_t_gpsst   = (U1)FALSE;
    u1_t_gpscrst = (U1)FALSE;

#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_CLK_DAY,  &(stp_a_rx->u1p_date[YYMMDD_DATE_DA]));
    (void)Com_ReceiveSignal(ComConf_ComSignal_CLK_MONT, &(stp_a_rx->u1p_date[YYMMDD_DATE_MO]));
    (void)Com_ReceiveSignal(ComConf_ComSignal_CLK_YEAR, &(stp_a_rx->u1p_date[YYMMDD_DATE_YR]));

    (void)Com_ReceiveSignal(ComConf_ComSignal_GPS_ST,   &u1_t_gpsst);
    (void)Com_ReceiveSignal(ComConf_ComSignal_GPS_CRCT, &u1_t_gpscrst);
#endif

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
#if 0   /* BEV BSW provisionally */
    u1_t_status = (U1)Com_GetIPDUStatus(MSG_AVN1S30_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#else
    u1_t_status = (U1)COM_NO_RX;
#endif

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
    U1  u1_t_pretx;
    U1  u1_t_date[YYMMDD_DATE_SIZE];
    U2  u2_t_cal_min;
    u2_t_cal_min   = u2_CALIB_MCUID0575_CAL_MIN;

    u1_t_pretx     = (U1)0U;
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
    (void)Com_ReceiveSignal(ComConf_ComSignal_M_YEAR, &u1_t_pretx);
    if(u1_t_pretx != u1_t_date[YYMMDD_DATE_YR]){
        (void)Com_SendSignal(ComConf_ComSignal_M_YEAR, &u1_t_date[YYMMDD_DATE_YR]);
        u1_t_can_trig = (U1)TRUE;
    }
#endif /* ComConf_ComSignal_M_YEAR */

#if defined(ComConf_ComSignal_M_MONTH)
    u1_t_date[YYMMDD_DATE_MO] = (U1)((u4_a_YYYYMMDD & (U4)YYMMDDWK_BIT_MO) >> YYMMDDWK_LSB_MO);
    (void)Com_ReceiveSignal(ComConf_ComSignal_M_MONTH, &u1_t_pretx);
    if(u1_t_pretx != u1_t_date[YYMMDD_DATE_MO]){
        (void)Com_SendSignal(ComConf_ComSignal_M_MONTH, &u1_t_date[YYMMDD_DATE_MO]);
        u1_t_can_trig = (U1)TRUE;
    }
#endif /* ComConf_ComSignal_M_MONTH */
#if defined(ComConf_ComSignal_M_DAY)
    u1_t_date[YYMMDD_DATE_DA] = (U1)((u4_a_YYYYMMDD & (U4)YYMMDDWK_BIT_DA) >> YYMMDDWK_LSB_DA);
    (void)Com_ReceiveSignal(ComConf_ComSignal_M_DAY, &u1_t_pretx);
    if(u1_t_pretx != u1_t_date[YYMMDD_DATE_DA]){
        (void)Com_SendSignal(ComConf_ComSignal_M_DAY, &u1_t_date[YYMMDD_DATE_DA]);
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
    (void)Com_ReceiveSignal(ComConf_ComSignal_M_WEEK, &u1_t_pretx);
    if(u1_t_pretx != u1_t_week){
        (void)Com_SendSignal(ComConf_ComSignal_M_WEEK, &u1_t_week);
        u1_t_can_trig = (U1)TRUE;
    }
#endif /* ComConf_ComSignal_M_WEEK */

    if((u1_t_can_trig == (U1)TRUE) &&
       (u1_a_EVENT_EI == (U1)TRUE)){
        (void)Com_TriggerIPDUSend(MSG_MET1S33_TXCH0);
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
/* void            vd_g_DateSICalCfgSetAdjusted(const U1 u1_a_CALSTS)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSICalCfgSetAdjusted(const U1 u1_a_CALSTS)
{
    vd_g_Rim_WriteU1((U2)RIMID_U1_DATESI_DATE_ADJUSTED, u1_a_CALSTS);
}

/*===================================================================================================================================*/
/* U1              u1_g_DateSICalCfgGetAdiusted(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_DateSICalCfgGetAdiusted(void)
{
    U1 u1_t_rim_sts;
    U1 u1_t_calsts;
    U1 u1_t_return;

    u1_t_calsts = (U1)0U;
    u1_t_return = (U1)0U;

    u1_t_rim_sts = u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_DATESI_DATE_ADJUSTED, &u1_t_calsts);
    if((u1_t_rim_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        u1_t_return = u1_t_calsts;
    }
    
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    04/03/2020  TN       New.                                                                                               */
/*  1.1.0    10/07/2020  TN       v1.0.0 -> v1.1.0.                                                                                  */
/*  1.1.1    01/08/2021  TN       v1.1.0 -> v1.1.1.                                                                                  */
/*  1.1.2    03/10/2021  TN       v1.1.1 -> v1.1.2.                                                                                  */
/*  3.1.0    10/08/2021  TA(M)    v1.1.2 -> v3.1.0.                                                                                  */
/*  3.1.1    10/18/2021  TA(M)    v3.1.0 -> v3.1.1.                                                                                  */
/*  3.2.0    10/19/2021  TA(M)    v3.1.1 -> v3.2.0.                                                                                  */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/* 19PFv3-1  09/28/2023  GM       MCUCONST correspondence                                                                            */
/* 19PFv3-2  01/11/2024  SH       Change MCUCONST v009 -> v010                                                                       */
/* 19PFv3-3  03/07/2024  SH       Change daycount logic                                                                              */
/* 19PFv3-4  05/16/2024  SH       Change calibration guard                                                                           */
/* 19PFv3-5  06/27/2024  TN(DT)   Delete Calibration Guard Process.                                                                  */
/*                                                                                                                                   */
/*  * TN     = Tatsuya Niimi, KSE                                                                                                    */
/*  * TA(M)  = Teruyuki Anjima, NTT Data MSE                                                                                         */
/*  * GM     = Glen Monteposo, DTPH                                                                                                  */
/*  * SH     = Sae Hirose, Denso Techno                                                                                              */
/*  * TN(DT) = Tetsushi Nakano, Denso Techno                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/
