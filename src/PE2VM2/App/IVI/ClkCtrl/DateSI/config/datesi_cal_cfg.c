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

/* BEV PreCV provisionally */
#define DATESI_CAL_MIN                          (2021U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U2                                      u2_s_datesi_cal_min;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
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
/* void            vd_g_DateSICalCfgInit(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSICalCfgInit(void)
{
    u2_s_datesi_cal_min = (U2)DATESI_CAL_MIN; /* BEV PreCV provisionally */
}

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

    st_t_command_data = st_g_DateSIComRx();
    stp_a_rx->u1p_date[YYMMDD_DATE_DA] = st_t_command_data.u1_clk_day;
    stp_a_rx->u1p_date[YYMMDD_DATE_MO] = st_t_command_data.u1_clk_mont;
    stp_a_rx->u1p_date[YYMMDD_DATE_YR] = st_t_command_data.u1_clk_year;

    u1_t_status = (U1)DATESI_CAL_STSBIT_VALID;

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
    U1  u1_t_read_sts;
    U4  u4_t_cal_min;

    u4_t_cal_min = (U4)0U;
    u1_t_read_sts = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_VM1TO2_CALMIN, &u4_t_cal_min, (U2)DATESI_CAL_VM_1WORD);
    if((u1_t_read_sts != (U1)IVDSH_NO_REA) && (u4_t_cal_min <= (U4)U2_MAX)){
        u2_s_datesi_cal_min = (U2)u4_t_cal_min;
    }

    u1_t_pretx     = (U1)0U;
#endif

    u1_t_can_trig  = (U1)FALSE;

#if defined(ComConf_ComSignal_M_YEAR)
    u2_t_year = (U2)((u4_a_YYYYMMDD & (U4)YYMMDDWK_BIT_YR) >> YYMMDDWK_LSB_YR);
    if(u2_t_year >= (U2)DATESI_CAL_YEAR_OFFSET){
        u1_t_date[YYMMDD_DATE_YR] = (U1)(u2_t_year - (U2)DATESI_CAL_YEAR_OFFSET);
    }
    else{
        if(u2_s_datesi_cal_min >= (U2)DATESI_CAL_YEAR_OFFSET){
            u1_t_date[YYMMDD_DATE_YR] = (U1)(u2_s_datesi_cal_min - (U2)DATESI_CAL_YEAR_OFFSET);
        }
        else{
            u1_t_date[YYMMDD_DATE_YR] = (U1)DATESI_CAL_MIN - (U1)DATESI_CAL_YEAR_OFFSET;
        }
    }
    (void)Com_ReceiveSignal(ComConf_ComSignal_M_YEAR, &u1_t_pretx);
    if(u1_t_pretx != u1_t_date[YYMMDD_DATE_YR]){
        vd_g_DateSIComClockDispUpdate(u1_t_date[YYMMDD_DATE_YR], DATESI_COM_M_YEAR, u1_a_EVENT_EI);
        (void)Com_SendSignal(ComConf_ComSignal_M_YEAR, &u1_t_date[YYMMDD_DATE_YR]);
        u1_t_can_trig = (U1)TRUE;
    }
#endif /* ComConf_ComSignal_M_YEAR */

#if defined(ComConf_ComSignal_M_MONTH)
    u1_t_date[YYMMDD_DATE_MO] = (U1)((u4_a_YYYYMMDD & (U4)YYMMDDWK_BIT_MO) >> YYMMDDWK_LSB_MO);
    (void)Com_ReceiveSignal(ComConf_ComSignal_M_MONTH, &u1_t_pretx);
    if(u1_t_pretx != u1_t_date[YYMMDD_DATE_MO]){
        vd_g_DateSIComClockDispUpdate(u1_t_date[YYMMDD_DATE_MO], DATESI_COM_M_MONTH, u1_a_EVENT_EI);
        (void)Com_SendSignal(ComConf_ComSignal_M_MONTH, &u1_t_date[YYMMDD_DATE_MO]);
        u1_t_can_trig = (U1)TRUE;
    }
#endif /* ComConf_ComSignal_M_MONTH */
#if defined(ComConf_ComSignal_M_DAY)
    u1_t_date[YYMMDD_DATE_DA] = (U1)((u4_a_YYYYMMDD & (U4)YYMMDDWK_BIT_DA) >> YYMMDDWK_LSB_DA);
    (void)Com_ReceiveSignal(ComConf_ComSignal_M_DAY, &u1_t_pretx);
    if(u1_t_pretx != u1_t_date[YYMMDD_DATE_DA]){
        vd_g_DateSIComClockDispUpdate(u1_t_date[YYMMDD_DATE_DA], DATESI_COM_M_DAY, u1_a_EVENT_EI);
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
        vd_g_DateSIComClockDispUpdate(u1_t_week, DATESI_COM_M_WEEK, u1_a_EVENT_EI);
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
/* void            vd_g_DateSICalCfgRxUpdtdate(ST_DATESI_CAL_RX * stp_a_rx)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      * stp_a_rx : Receive signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSICalCfgRxUpdtdate(ST_DATESI_CAL_RX * stp_a_rx)
{
    ST_DATESI_COMMAND_DATA  st_t_command_data;

    st_t_command_data = st_g_DateSIComRx();
    stp_a_rx->u1p_date[YYMMDD_DATE_DA] = st_t_command_data.u1_clk_day_updt;
    stp_a_rx->u1p_date[YYMMDD_DATE_MO] = st_t_command_data.u1_clk_mont_updt;
    stp_a_rx->u1p_date[YYMMDD_DATE_YR] = st_t_command_data.u1_clk_year_updt;
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
