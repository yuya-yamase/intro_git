/* 0.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Date clock Synchronization Interface                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DATESI_TIM_AVN_C_MAJOR                  (0)
#define DATESI_TIM_AVN_C_MINOR                  (0)
#define DATESI_TIM_AVN_C_PATCH                  (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "datesi_tim_cfg_private.h"
#include "datesi_cal_cfg_private.h"
#include "datesi_cfg_private.h"
#include "datesi_time_zone.h"
#include "datesi_com.h"
#include "bitcnt.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DATESI_TIM_AVN_C_MAJOR != DATESI_TIM_H_MAJOR) || \
     (DATESI_TIM_AVN_C_MINOR != DATESI_TIM_H_MINOR) || \
     (DATESI_TIM_AVN_C_PATCH != DATESI_TIM_H_PATCH))
#error "datesi_tim_avn.c and datesi_tim.h : source and header files are inconsistent!"
#endif

#if ((DATESI_TIM_AVN_C_MAJOR != DATESI_TIM_CFG_H_MAJOR) || \
     (DATESI_TIM_AVN_C_MINOR != DATESI_TIM_CFG_H_MINOR) || \
     (DATESI_TIM_AVN_C_PATCH != DATESI_TIM_CFG_H_PATCH))
#error "datesi_tim_avn.c and datesi_tim_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DATESI_TIM_SYNC_BAN_START_HR            (23U)
#define DATESI_TIM_SYNC_BAN_START_MI            (59U)
#define DATESI_TIM_SYNC_BAN_END_HR              (0U)
#define DATESI_TIM_SYNC_BAN_END_MI              (0U)
#define DATESI_TIM_SYNC_BAN_SEC                 (30U)

/* SW input */
#define DATESI_TIM_SW_INPUT_HRUP                (0x80U)
#define DATESI_TIM_SW_INPUT_HRDW                (0x40U)
#define DATESI_TIM_SW_INPUT_MIUP                (0x20U)
#define DATESI_TIM_SW_INPUT_MIDW                (0x10U)
#define DATESI_TIM_SW_INPUT_SET                 (0x08U)
#define DATESI_TIM_SW_INPUT_12_24               (0x04U)
#define DATESI_TIM_SW_INPUT_OFFSETUP            (0x02U)
#define DATESI_TIM_SW_INPUT_OFFSETDW            (0x01U)
#define DATESI_TIM_SW_LONGPUSH_MASK             (0xF3U)

#define DATESI_TIM_BIT_NUM_SINGLE               (1U)
#define DATESI_TIM_SWRECV_STS_INIT              (0xFFU)

#define DATESI_TIM_ADJ_VAL_1                    (1U)

#define DATESI_TIM_CALC_TBL_SIZE                (3U)
#define DATESI_TIM_HOUR_MOD                     (HHMMSS_24H_HR_MAX + 1U)
#define DATESI_TIM_MINUTE_MOD                   (HHMMSS_MI_MAX     + 1U)
#define DATESI_TIM_SECOND_MOD                   (HHMMSS_SE_MAX     + 1U)

#define DATESI_TIM_ZERORST_HALF_HOUR            (30U)

#define DATESI_TIM_DIAG_CNT_INIT                (0U)
#define DATESI_TIM_DIAG_CNT_END                 (30000U / DATESI_TIM_MAIN_TICK)

#define DATESI_TIM_DIAG_STS_NON                 (0U)
#define DATESI_TIM_DIAG_STS_START               (1U)
#define DATESI_TIM_DIAG_STS_CUSTOMIZE           (2U)

#define DATESI_TIM_DIAG_FCT_NUM                 (4U)
#define DATESI_TIM_DIAG_FCT_NON                 (0U)
#define DATESI_TIM_DIAG_FCT_UP                  (1U)
#define DATESI_TIM_DIAG_FCT_DOWN                (2U)
#define DATESI_TIM_DIAG_FCT_ZERO                (3U)

#define DATESI_TIM_ADJ_NON                      (0U)
#define DATESI_TIM_ADJ_ACT                      (1U)

#define DATESI_TIM_OFFSET_INIT                  (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U4  u4_mask;
    U1  u1_shift;
    U1  u1_mod;
}ST_DATESI_TIM_CALC;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  S4                                      s4_s_datesi_tim_ofst;
static  U1                                      u1_s_datesi_tim_sync;
static  U1                                      u1_s_datesi_tim_prv_hr;
static  U1                                      u1_s_datesi_tim_onsw;
static  U1                                      u1_s_datesi_tim_validsw;
static  U1                                      u1_s_datesi_tim_sw_cnt;
static  U4                                      u4_s_datesi_tim_adj_clock;
static  U1                                      u1_s_datesi_tim_adj_sts;
static  U2                                      u2_s_datesi_tim_diagcnt;
static  U1                                      u1_s_datesi_tim_diagact;
static  U1                                      u1_s_datesi_tim_diagsts;
static  U4                                      u4_s_datesi_tim_diaginfo[DATESI_TIM_DIAG_INFO_NUM];
static  U1                                      u1_s_datesi_tim_init_read_fin1;
static  U1                                      u1_s_datesi_tim_init_read_fin2;
static  U1                                      u1_s_datesi_tim_init_read_fin3;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_DATESI_TIM_CALC                 st_sp_DATESI_TIM_CALC[DATESI_TIM_CALC_TBL_SIZE] = {
       /* u4_mask               u1_shift               u1_mod */
    {(U4)HHMMSS_BIT_SE,    (U1)HHMMSS_LSB_SE,    (U1)DATESI_TIM_SECOND_MOD},
    {(U4)HHMMSS_BIT_MI,    (U1)HHMMSS_LSB_MI,    (U1)DATESI_TIM_MINUTE_MOD},
    {(U4)HHMMSS_BIT_HR,    (U1)HHMMSS_LSB_HR,    (U1)DATESI_TIM_HOUR_MOD  }
};

static const U4                                 u4_s_DATESI_TIM_INFO_INIT[DATESI_TIM_DIAG_INFO_NUM] = {
    (U4)DATESI_TIM_DIAG_FCT_NON,                /* DATESI_TIM_DIAG_INFO_FAC */
    (U4)HHMMSS_UNKNWN,                          /* DATESI_TIM_DIAG_INFO_BAC */
    (U4)HHMMSS_UNKNWN                           /* DATESI_TIM_DIAG_INFO_NEW */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  void    vd_s_DateSITimSwCtlInit(void);
static  U1      u1_s_DateSITimInitReadiVDsh(void);
static  void    vd_s_DateSITimSwCtlRoutine(void);
static  U1      u1_s_DateSITimSyncRoutine(U4 * u4p_a_offstd_now);
static  U1      u1_s_DateSITimClkRangeCheck(const ST_DATESI_TIM_RX st_a_TIM_RX);
static  U1      u1_s_DateSITimClkSyncCheck(const ST_DATESI_TIM_RX st_a_TIM_RX);
static  void    vd_s_DateSITimSwstsJdg(const U1 u1_a_SWENABL);
static  void    vd_s_DateSITimRcvEnblSts(const U1 u1_a_SWSTS);
static  void    vd_s_DateSITimMltRcvDsblSts(const U1 u1_a_SWEDG);
static  void    vd_s_DateSITimRcvDsblSts(const U1 u1_a_SWEDG, const U1 u1_a_SWSTS);
static  void    vd_s_DateSITimSwSgnlUpdate(const U1 u1_a_SWEDG);
static  void    vd_s_DateSITimExecMinD(void);
static  void    vd_s_DateSITimExecMinU(void);
static  void    vd_s_DateSITimExecHourD(void);
static  void    vd_s_DateSITimExecHourU(void);
static  void    vd_s_DateSITimExecOffsMD(void);
static  void    vd_s_DateSITimExecOffsMU(void);
static  U4      u4_s_DateSITimOpeAdjClk(const U4 u4_a_HHMMSS_RAW, const U1 u1_a_UPDTRNK, const U1 u1_a_VAL, const U1 u1_a_SIGN);
static  U1      u1_s_DateSITimGetClkElem(const U4 u4_a_HHMMSS, const U1 u1_a_RNK);
static  U1      u1_s_DateSITimCalcClkElem(const U1 u1_a_RAW, const U1 u1_a_RNK, const U1 u1_a_VAL, const U1 u1_a_SIGN);
static  U4      u4_s_DateSITimUpdtDateTime(const U4 u4_a_HHMMSS_RAW, const U1 u1_a_RNK, const U2 u2_a_VAL);
static  U4      u4_s_DateSITimMakeHHMMSS(const U1 u1_a_HOUR, const U1 u1_a_MIN, const U1 u1_a_SEC);
static  U4      u4_s_DateSITimUpdateNow(const U4 u4_a_NOW, const S4 s4_a_OFST);
static  void    vd_s_DateSITimAddOfstTime(const U1 u1_a_VAL, const U1 u1_a_SIGN);
static  S4      s4_s_DateSITimChkOfstTime(const S4 s4_a_OFST);
static  S4      s4_s_DateSITimChkTimZn(const S4 s4_a_TIMZN);
static void     vd_s_DateSITimDiagAdjClear(void);
static void     vd_s_DateSITimDiagItemClear(void);
static void     vd_s_DateSITimDiagRoutine(void);
static void     vd_s_DateSITimDiagClkFctBak(const U1 u1_a_ADJ_FCT);
static void     vd_s_DateSITimDiagClkOldBak(const U4 u4_a_HHMMSS_OLD);
static void     vd_s_DateSITimDiagClkNewBak(const U4 u4_a_HHMMSS_NEW);

/*===================================================================================================================================*/
/* void            vd_g_DateSITimAvnBonInit(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSITimAvnBonInit(void)
{
    S4  s4_t_offset_time;

    vd_g_TimeZoneBonInit();
    s4_t_offset_time               = s4_g_DateSITimCfgBonOfstTime();
    s4_s_datesi_tim_ofst           = s4_s_DateSITimChkOfstTime(s4_t_offset_time);
    u1_s_datesi_tim_sync           = (U1)FALSE;
    u1_s_datesi_tim_prv_hr         = (U1)0U;
    u4_s_datesi_tim_adj_clock      = (U4)HHMMSS_UNKNWN;
    u1_s_datesi_tim_adj_sts        = (U1)DATESI_TIM_ADJ_NON;
    u1_s_datesi_tim_init_read_fin1 = (U1)FALSE;
    u1_s_datesi_tim_init_read_fin2 = (U1)FALSE;
    u1_s_datesi_tim_init_read_fin3 = (U1)FALSE;

    vd_s_DateSITimSwCtlInit();
    vd_g_DateSITimCfgCanTxOffst(s4_s_datesi_tim_ofst, (U1)FALSE);
    vd_s_DateSITimDiagAdjClear();
    vd_s_DateSITimDiagItemClear();
}

/*===================================================================================================================================*/
/* void            vd_g_DateSITimAvnWkupInit(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSITimAvnWkupInit(void)
{
    S4  s4_t_offset_time;
    S4  s4_t_time_zone;

    vd_g_TimeZoneRstWkupInit();
    s4_t_offset_time               = s4_g_DateSITimCfgWkupOfstTime();
    s4_t_offset_time               = s4_s_DateSITimChkOfstTime(s4_t_offset_time);
    s4_t_time_zone                 = s4_g_TimeZoneUtcDiffSec();
    s4_t_time_zone                 = s4_s_DateSITimChkTimZn(s4_t_time_zone);
    s4_s_datesi_tim_ofst           = s4_t_offset_time + s4_t_time_zone;

    u1_s_datesi_tim_sync           = (U1)FALSE;
    u1_s_datesi_tim_prv_hr         = (U1)0U;
    u4_s_datesi_tim_adj_clock      = (U4)HHMMSS_UNKNWN;
    u1_s_datesi_tim_adj_sts        = (U1)DATESI_TIM_ADJ_NON;
    u1_s_datesi_tim_init_read_fin1 = (U1)FALSE;
    u1_s_datesi_tim_init_read_fin2 = (U1)FALSE;
    u1_s_datesi_tim_init_read_fin3 = (U1)FALSE;

    vd_s_DateSITimSwCtlInit();
    vd_g_DateSITimCfgCanTxOffst(s4_s_datesi_tim_ofst, (U1)FALSE);
    vd_s_DateSITimDiagAdjClear();
    vd_s_DateSITimDiagItemClear();
}

/*===================================================================================================================================*/
/* static  void    vd_s_DateSITimSwCtlInit(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DateSITimSwCtlInit(void)
{
    u1_s_datesi_tim_validsw = (U1)DATESI_TIM_SWRECV_STS_INIT;
    u1_s_datesi_tim_onsw    = (U1)0U;
    u1_s_datesi_tim_sw_cnt  = (U1)DATESI_TIM_SWTIM_SETLONG_FST;
}

/*===================================================================================================================================*/
/* U1              u1_g_DateSITimMainAvnTask(U4 * u4p_a_offstd_now)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_DateSITimMainAvnTask(U4 * u4p_a_offstd_now)
{
    U1  u1_t_read_sts;
    U1  u1_t_adj_act;

    if((u1_s_datesi_tim_init_read_fin1 == (U1)FALSE) &&
       (u1_s_datesi_tim_init_read_fin2 == (U1)FALSE) &&
       (u1_s_datesi_tim_init_read_fin3 == (U1)FALSE)){
        u1_t_read_sts = u1_s_DateSITimInitReadiVDsh();
        if(u1_t_read_sts != (U1)IVDSH_NO_REA){
            u1_s_datesi_tim_init_read_fin1 = (U1)TRUE;
            u1_s_datesi_tim_init_read_fin2 = (U1)TRUE;
            u1_s_datesi_tim_init_read_fin3 = (U1)TRUE;
        }
    }

    vd_g_TimeZoneMainTask();
    vd_s_DateSITimSwCtlRoutine();

    u1_t_adj_act = u1_s_DateSITimSyncRoutine(u4p_a_offstd_now);

    vd_s_DateSITimDiagRoutine();

    vd_g_DateSITimCfgOfstRoutine();

    return(u1_t_adj_act);
}

/*===================================================================================================================================*/
/* u1              u1_s_DateSITimInitReadiVDsh(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_read_sts : TRUE/FALSE                                                                                       */
/*===================================================================================================================================*/
static U1       u1_s_DateSITimInitReadiVDsh()
{
    U1  u1_t_read_sts;
    S4  s4_t_offset_time;

    s4_t_offset_time     = (S4)DATESI_TIM_OFFSET_INIT;
    u1_t_read_sts        = u1_g_DateSITimCfgInitOfstTime(&s4_t_offset_time);
    if(u1_t_read_sts != (U1)IVDSH_NO_REA){
        s4_s_datesi_tim_ofst = s4_s_DateSITimChkOfstTime(s4_t_offset_time);
    }

    return(u1_t_read_sts);
}

/*===================================================================================================================================*/
/* static  void    vd_s_DateSITimSwCtlRoutine(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DateSITimSwCtlRoutine(void)
{
    U1  u1_t_msgsts;
    U1  u1_t_validsw;

    u1_t_msgsts  = u1_g_DateSITimCfgRxMsgSts();

    if(u1_t_msgsts == (U1)DATESI_TIM_STSBIT_VALID){
        u1_t_validsw = (U1)(u1_s_datesi_tim_onsw & u1_s_datesi_tim_validsw);
        u1_t_validsw = (U1)(u1_t_validsw         & (U1)DATESI_TIM_SW_LONGPUSH_MASK);
        if(u1_t_validsw != (U1)0U){
            vd_s_DateSITimSwstsJdg(u1_t_validsw);
        }
        else{
            u1_s_datesi_tim_sw_cnt = (U1)DATESI_TIM_SWTIM_SETLONG_FST;
        }
    }
    else{
        vd_s_DateSITimSwCtlInit();
    }
}

/*===================================================================================================================================*/
/* static U1       u1_s_DateSITimSyncRoutine(U4 * u4p_a_offstd_now)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DateSITimSyncRoutine(U4 * u4p_a_offstd_now)
{
    U4                u4_t_now;
    U4                u4_t_adj;
    S4                s4_t_offset;
    S4                s4_t_time_zone;
    U1                u1_t_rxsts;
    U1                u1_t_adj_act;
    U1                u1_t_cntr_exist;
    U1                u1_t_calendar;
    U1                u1_t_range_is_ok;
    U1                u1_t_sync_range_is_ok;
    U1                u1_t_result;
    ST_DATESI_TIM_RX  st_t_tim_rx;

    st_t_tim_rx.u1_valid                     = (U1)FALSE;
    st_t_tim_rx.u1_act                       = (U1)FALSE;
    st_t_tim_rx.u1p_time[HHMMSS_24H_TIME_SE] = (U1)U1_MAX;
    st_t_tim_rx.u1p_time[HHMMSS_24H_TIME_MI] = (U1)U1_MAX;
    st_t_tim_rx.u1p_time[HHMMSS_24H_TIME_HR] = (U1)U1_MAX;
    u1_t_adj_act                             = (U1)FALSE;
    u1_t_rxsts                               = u1_g_DateSITimCfgCanRx(&st_t_tim_rx);
    u1_t_result                              = (U1)FALSE;

    u1_t_range_is_ok      = u1_s_DateSITimClkRangeCheck(st_t_tim_rx);
    u1_t_sync_range_is_ok = u1_s_DateSITimClkSyncCheck(st_t_tim_rx);
    u1_t_cntr_exist       = u1_g_DateSITimCfgEcuExst();
    u1_t_calendar         = u1_g_DateSICfgCalExst();

    if((st_t_tim_rx.u1_valid                      != (U1)TRUE                   ) ||
       (st_t_tim_rx.u1_act                        != (U1)TRUE                   ) ||
       (u1_t_rxsts                                != (U1)DATESI_TIM_STSBIT_VALID) ||
       (u1_t_cntr_exist                           == (U1)FALSE                  ) ||
       (u1_t_range_is_ok                          != (U1)TRUE                   ) ||
       (u1_t_sync_range_is_ok                     != (U1)TRUE                   ) ||
       ((st_t_tim_rx.u1p_time[HHMMSS_24H_TIME_HR] == u1_s_datesi_tim_prv_hr     ) &&
        (u1_s_datesi_tim_sync                     == (U1)TRUE                   ))){
        u4_t_now = u4_g_DateclkHhmmss24h();
        u4_t_adj = (U4)HHMMSS_UNKNWN;
    }
    else{
        u4_t_now = u4_s_DateSITimMakeHHMMSS(st_t_tim_rx.u1p_time[HHMMSS_24H_TIME_HR],
                                            st_t_tim_rx.u1p_time[HHMMSS_24H_TIME_MI],
                                            st_t_tim_rx.u1p_time[HHMMSS_24H_TIME_SE]);
        u4_t_adj               = u4_t_now;
        u1_s_datesi_tim_sync   = (U1)TRUE;
        if(u1_t_calendar == (U1)DATESI_CALEXIST_ON){
            vd_g_DateSICalSyncAct();
        }
    }

    if((u1_t_rxsts & (U1)DATESI_TIM_STSBIT_INVALID) != (U1)0U){
        u1_s_datesi_tim_sync = (U1)FALSE;
        u1_t_adj_act         = (U1)TRUE;
    }
    else if((u1_t_rxsts & (U1)DATESI_TIM_STSBIT_UNKNOWN) != (U1)0U){
        /* do nothing */
    }
    else{
        if(st_t_tim_rx.u1_act != (U1)TRUE){
            u1_s_datesi_tim_sync = (U1)FALSE;
        }
        if(u1_t_sync_range_is_ok == (U1)TRUE){
            u1_s_datesi_tim_prv_hr = st_t_tim_rx.u1p_time[HHMMSS_24H_TIME_HR];
        }
    }

    s4_t_offset  = s4_g_DateSITimCfgGetOfstTime();
    s4_t_offset  = s4_s_DateSITimChkOfstTime(s4_t_offset);
    vd_g_DateSITimCfgCanTxOffst(s4_t_offset, (U1)TRUE);

    s4_t_time_zone       = s4_g_TimeZoneUtcDiffSec();
    s4_t_time_zone       = s4_s_DateSITimChkTimZn(s4_t_time_zone);
    s4_s_datesi_tim_ofst = s4_t_offset + s4_t_time_zone;

    (*u4p_a_offstd_now)  = u4_s_DateSITimUpdateNow(u4_t_now, s4_s_datesi_tim_ofst);

    if(u4_t_adj != (U4)HHMMSS_UNKNWN){
        u1_t_result = u1_g_DateSITimAdjustOwnClk(u4_t_adj);
    }
    vd_g_DateSIComSetCmp(u1_t_result,(U1)DATESI_COM_KIND_TIM);

    return(u1_t_adj_act);
}

/*===================================================================================================================================*/
/* S4              s4_g_DateSITimTotalOffset(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
S4              s4_g_DateSITimTotalOffset(void)
{
    return(s4_s_datesi_tim_ofst);
}

/*===================================================================================================================================*/
/* static  U1      u1_s_DateSITimClkRangeCheck(const ST_DATESI_TIM_RX st_a_TIM_RX)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DateSITimClkRangeCheck(const ST_DATESI_TIM_RX st_a_TIM_RX)
{
    U1  u1_t_result;

    if((st_a_TIM_RX.u1p_time[HHMMSS_24H_TIME_HR] <= (U1)HHMMSS_24H_HR_MAX) &&
       (st_a_TIM_RX.u1p_time[HHMMSS_24H_TIME_MI] <= (U1)HHMMSS_MI_MAX    ) &&
       (st_a_TIM_RX.u1p_time[HHMMSS_24H_TIME_SE] <= (U1)HHMMSS_SE_MAX    )){
        u1_t_result = (U1)TRUE;
    }
    else{
        u1_t_result = (U1)FALSE;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/* static  U1      u1_s_DateSITimClkSyncCheck(const ST_DATESI_TIM_RX st_a_TIM_RX)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DateSITimClkSyncCheck(const ST_DATESI_TIM_RX st_a_TIM_RX)
{
    U1  u1_t_calendar;
    U1  u1_t_result;
    U1  u1_t_range_ok;

    u1_t_calendar = u1_g_DateSICfgCalExst();
    u1_t_range_ok = u1_s_DateSITimClkRangeCheck(st_a_TIM_RX);
    u1_t_result   = (U1)TRUE;

    if(u1_t_calendar == (U1)DATESI_CALEXIST_ON){
        if(u1_t_range_ok == (U1)TRUE){
            if(((st_a_TIM_RX.u1p_time[HHMMSS_24H_TIME_HR] >= (U1)DATESI_TIM_SYNC_BAN_START_HR)   &&
               ((st_a_TIM_RX.u1p_time[HHMMSS_24H_TIME_MI] >= (U1)DATESI_TIM_SYNC_BAN_START_MI)   &&
                (st_a_TIM_RX.u1p_time[HHMMSS_24H_TIME_SE] >= (U1)DATESI_TIM_SYNC_BAN_SEC     ))) ||
               ((st_a_TIM_RX.u1p_time[HHMMSS_24H_TIME_HR] <= (U1)DATESI_TIM_SYNC_BAN_END_HR  )   &&
               ((st_a_TIM_RX.u1p_time[HHMMSS_24H_TIME_MI] <= (U1)DATESI_TIM_SYNC_BAN_END_MI  )   &&
                (st_a_TIM_RX.u1p_time[HHMMSS_24H_TIME_SE] <= (U1)DATESI_TIM_SYNC_BAN_SEC     )))){
                u1_t_result = (U1)FALSE;
            }
        }
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/* static  void    vd_s_DateSITimSwstsJdg(const U1 u1_a_SWENABL)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DateSITimSwstsJdg(const U1 u1_a_SWENABL)
{
    if(u1_s_datesi_tim_sw_cnt == (U1)0U){
        vd_s_DateSITimSwSgnlUpdate(u1_a_SWENABL);
        u1_s_datesi_tim_sw_cnt = (U1)DATESI_TIM_SWTIM_SETLONG;
    }
    if(u1_s_datesi_tim_sw_cnt <= (U1)0U){
        u1_s_datesi_tim_sw_cnt = (U1)0U;
    }
    else{
        u1_s_datesi_tim_sw_cnt--;
    }
}

/*===================================================================================================================================*/
/* void            vd_g_DateSITimAvnCanRxHk(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSITimAvnCanRxHk(void)
{
    U1  u1_t_swsts;
    U1  u1_t_swedg;
    U1  u1_t_bitcnt;

    u1_t_swsts  = u1_g_DateSITimCfgCanRxHk();
    vd_s_DateSITimRcvEnblSts(u1_t_swsts);

    u1_t_swedg = (U1)(u1_s_datesi_tim_onsw ^ u1_t_swsts);
    u1_t_swedg = (U1)(u1_t_swedg & u1_t_swsts);
    if(u1_t_swedg != (U1)0U){
        u1_t_bitcnt = u1_g_BitCnt((U4)u1_t_swedg);
        if(u1_t_bitcnt != (U1)DATESI_TIM_BIT_NUM_SINGLE){
            vd_s_DateSITimMltRcvDsblSts(u1_t_swedg);
        }
        else{
            vd_s_DateSITimRcvDsblSts(u1_t_swedg, u1_t_swsts);
            vd_s_DateSITimSwSgnlUpdate(u1_t_swedg);
            u1_s_datesi_tim_sw_cnt = (U1)DATESI_TIM_SWTIM_SETLONG_FST;
        }
    }
    u1_s_datesi_tim_onsw = u1_t_swsts;
}

/*===================================================================================================================================*/
/* static  void    vd_s_DateSITimRcvEnblSts(const U1 u1_a_SWSTS)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DateSITimRcvEnblSts(const U1 u1_a_SWSTS)
{
    U1  u1_t_swsts;

    u1_t_swsts               = (U1)(~u1_a_SWSTS);
    u1_s_datesi_tim_validsw |= u1_t_swsts;
}

/*===================================================================================================================================*/
/* static  void    vd_s_DateSITimMltRcvDsblSts(const U1 u1_a_SWEDG)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DateSITimMltRcvDsblSts(const U1 u1_a_SWEDG)
{
    U1  u1_t_swedg;

    u1_t_swedg               = (U1)(~u1_a_SWEDG);
    u1_s_datesi_tim_validsw &= u1_t_swedg;
}

/*===================================================================================================================================*/
/* static  void    vd_s_DateSITimRcvDsblSts(const U1 u1_a_SWEDG, const U1 u1_a_SWSTS)                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DateSITimRcvDsblSts(const U1 u1_a_SWEDG, const U1 u1_a_SWSTS)
{
    U1  u1_t_swsts;
    U1  u1_t_swinf;

    u1_t_swsts               = (U1)(~u1_a_SWSTS);
    u1_t_swinf               = (U1)(u1_t_swsts | u1_a_SWEDG);
    u1_s_datesi_tim_validsw &= u1_t_swinf;
}

/*===================================================================================================================================*/
/* static  void    vd_s_DateSITimSwSgnlUpdate(const U1 u1_a_SWEDG)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DateSITimSwSgnlUpdate(const U1 u1_a_SWEDG)
{
    switch (u1_a_SWEDG){
        case (U1)DATESI_TIM_SW_INPUT_HRUP:
            vd_s_DateSITimExecHourU();
            break;
        case (U1)DATESI_TIM_SW_INPUT_HRDW:
            vd_s_DateSITimExecHourD();
            break;
        case (U1)DATESI_TIM_SW_INPUT_MIUP:
            vd_s_DateSITimExecMinU();
            break;
        case (U1)DATESI_TIM_SW_INPUT_MIDW:
            vd_s_DateSITimExecMinD();
            break;
        case (U1)DATESI_TIM_SW_INPUT_12_24:
            vd_g_DateSITimCfgExec24();
            break;
        case (U1)DATESI_TIM_SW_INPUT_SET:
            vd_g_DateSITimExecTmSet();
            break;
        case (U1)DATESI_TIM_SW_INPUT_OFFSETUP:
            vd_s_DateSITimExecOffsMU();
            break;
        case (U1)DATESI_TIM_SW_INPUT_OFFSETDW:
            vd_s_DateSITimExecOffsMD();
            break;
        default:
            /* do nothing */
            break;
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_DateSITimExecMinD(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DateSITimExecMinD(void)
{
    vd_g_DateSITimSetAdjStart();
    vd_g_DateSITimAdjustClk((U1)DATESI_TIM_RNK_MIN, (U1)DATESI_TIM_ADJ_VAL_1, (U1)DATESI_TIM_ADJ_MINUS);
    vd_g_DateSITimClockUpdate();
    vd_g_DateSITimSetAdjEnd();
}

/*===================================================================================================================================*/
/* static  void    vd_s_DateSITimExecMinU(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DateSITimExecMinU(void)
{
    vd_g_DateSITimSetAdjStart();
    vd_g_DateSITimAdjustClk((U1)DATESI_TIM_RNK_MIN, (U1)DATESI_TIM_ADJ_VAL_1, (U1)DATESI_TIM_ADJ_PLUS);
    vd_g_DateSITimClockUpdate();
    vd_g_DateSITimSetAdjEnd();
}

/*===================================================================================================================================*/
/* static  void    vd_s_DateSITimExecHourD(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments :  -                                                                                                                   */
/*  Return    :  -                                                                                                                   */
/*===================================================================================================================================*/
static void     vd_s_DateSITimExecHourD(void)
{
    vd_g_DateSITimSetAdjStart();
    vd_g_DateSITimAdjustClk((U1)DATESI_TIM_RNK_HUR, (U1)DATESI_TIM_ADJ_VAL_1, (U1)DATESI_TIM_ADJ_MINUS);
    vd_g_DateSITimClockUpdate();
    vd_g_DateSITimSetAdjEnd();
}

/*===================================================================================================================================*/
/* static  void    vd_s_DateSITimExecHourU(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments :  -                                                                                                                   */
/*  Return    :  -                                                                                                                   */
/*===================================================================================================================================*/
static void     vd_s_DateSITimExecHourU(void)
{
    vd_g_DateSITimSetAdjStart();
    vd_g_DateSITimAdjustClk((U1)DATESI_TIM_RNK_HUR, (U1)DATESI_TIM_ADJ_VAL_1, (U1)DATESI_TIM_ADJ_PLUS);
    vd_g_DateSITimClockUpdate();
    vd_g_DateSITimSetAdjEnd();
}

/*===================================================================================================================================*/
/* void            vd_g_DateSITimExecTmSet(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments :  -                                                                                                                   */
/*  Return    :  -                                                                                                                   */
/*===================================================================================================================================*/
void            vd_g_DateSITimExecTmSet(void)
{
    U4  u4_t_hhmmss_zerorst;
    U1  u1_t_hh_zerorst;
    U1  u1_t_mm_zerorst;
    S4  s4_t_offset;
    U1  u1_t_calset;
    U4  u4_t_hhmmss_diag;

    u4_t_hhmmss_zerorst = u4_g_DateSITim();
    u1_t_mm_zerorst     = u1_s_DateSITimGetClkElem(u4_t_hhmmss_zerorst, (U1)DATESI_TIM_RNK_MIN);
    u1_t_hh_zerorst     = u1_s_DateSITimGetClkElem(u4_t_hhmmss_zerorst, (U1)DATESI_TIM_RNK_HUR);
    u1_t_calset         = (U1)FALSE;

    if(u1_t_mm_zerorst >= (U1)DATESI_TIM_ZERORST_HALF_HOUR){
        if(u1_t_hh_zerorst >= (U1)HHMMSS_24H_HR_MAX){
            u1_t_hh_zerorst = (U1)0U;
            u1_t_calset     = (U1)TRUE;
        }
        else{
            u1_t_hh_zerorst++;/* QAC over-detection */
        }
    }

    vd_s_DateSITimDiagClkFctBak((U1)DATESI_TIM_DIAG_FCT_ZERO);
    vd_s_DateSITimDiagClkOldBak(u4_t_hhmmss_zerorst);

    u4_t_hhmmss_zerorst = u4_s_DateSITimMakeHHMMSS(u1_t_hh_zerorst, (U1)0U, (U1)0U);

    s4_t_offset         = s4_s_datesi_tim_ofst * (S4)DATESI_TIM_SIGN_CHG;

    u4_t_hhmmss_zerorst = u4_s_DateSITimUpdateNow(u4_t_hhmmss_zerorst, s4_t_offset);

    (void)u1_g_DateSITimAdjustOwnClk(u4_t_hhmmss_zerorst);

    u4_t_hhmmss_diag = u4_g_DateclkHhmmss24h();
    u4_t_hhmmss_diag = u4_s_DateSITimUpdateNow(u4_t_hhmmss_diag, s4_s_datesi_tim_ofst);
    vd_s_DateSITimDiagClkNewBak(u4_t_hhmmss_diag);
    vd_g_DateSITimSetDispClk(u4_t_hhmmss_diag);

    vd_g_DateSICalExecTmSet(u1_t_calset);
}

/*===================================================================================================================================*/
/* static  void    vd_s_DateSITimExecOffsMD(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments :  -                                                                                                                   */
/*  Return    :  -                                                                                                                   */
/*===================================================================================================================================*/
static void     vd_s_DateSITimExecOffsMD(void)
{
    vd_s_DateSITimAddOfstTime((U1)DATESI_TIM_ADJ_VAL_1, (U1)DATESI_TIM_ADJ_MINUS);
}

/*===================================================================================================================================*/
/* static  void    vd_s_DateSITimExecOffsMU(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments :  -                                                                                                                   */
/*  Return    :  -                                                                                                                   */
/*===================================================================================================================================*/
static void     vd_s_DateSITimExecOffsMU(void)
{
    vd_s_DateSITimAddOfstTime((U1)DATESI_TIM_ADJ_VAL_1, (U1)DATESI_TIM_ADJ_PLUS);
}

/*===================================================================================================================================*/
/* void            vd_g_DateSITimSetAdjStart(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSITimSetAdjStart(void)
{
    u4_s_datesi_tim_adj_clock = u4_g_DateSITim();
    u1_s_datesi_tim_adj_sts = (U1)DATESI_TIM_ADJ_ACT;
}

/*===================================================================================================================================*/
/* void            vd_g_DateSITimSetAdjEnd(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSITimSetAdjEnd(void)
{
    u1_s_datesi_tim_adj_sts = (U1)DATESI_TIM_ADJ_NON;
}

/*===================================================================================================================================*/
/* U4              u4_g_DateSITimGetAdjSetClk(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4              u4_g_DateSITimGetAdjSetClk(void)
{
    return(u4_s_datesi_tim_adj_clock);
}

/*===================================================================================================================================*/
/* void            vd_g_DateSITimAdjustClk(const U1 u1_a_UPDTRNK, const U1 u1_a_VAL, const U1 u1_a_SIGN)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSITimAdjustClk(const U1 u1_a_UPDTRNK, const U1 u1_a_VAL, const U1 u1_a_SIGN)
{
    if(u1_s_datesi_tim_adj_sts == (U1)DATESI_TIM_ADJ_ACT){
        u4_s_datesi_tim_adj_clock = u4_s_DateSITimOpeAdjClk(u4_s_datesi_tim_adj_clock, u1_a_UPDTRNK, u1_a_VAL, u1_a_SIGN);

        if(u1_a_UPDTRNK == (U1)DATESI_TIM_RNK_MIN){
            u4_s_datesi_tim_adj_clock = u4_s_DateSITimUpdtDateTime(u4_s_datesi_tim_adj_clock, (U1)DATESI_TIM_RNK_SEC, (U2)0U);
        }
        if(u1_a_SIGN == (U1)DATESI_TIM_ADJ_PLUS){
            vd_s_DateSITimDiagClkFctBak((U1)DATESI_TIM_DIAG_FCT_UP);
        }
        else{
            vd_s_DateSITimDiagClkFctBak((U1)DATESI_TIM_DIAG_FCT_DOWN);
        }
    }
}

/*===================================================================================================================================*/
/* static  U4      u4_s_DateSITimOpeAdjClk(const U4 u4_a_HHMMSS_RAW, const U1 u1_a_UPDTRNK, const U1 u1_a_VAL, const U1 u1_a_SIGN)   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4       u4_s_DateSITimOpeAdjClk(const U4 u4_a_HHMMSS_RAW, const U1 u1_a_UPDTRNK, const U1 u1_a_VAL, const U1 u1_a_SIGN)
{
    U1  u1_t_raw;
    U2  u2_t_updt;
    U4  u4_t_hhmmss_new;

    u1_t_raw        = u1_s_DateSITimGetClkElem(u4_a_HHMMSS_RAW, u1_a_UPDTRNK);
    u2_t_updt       = (U2)u1_s_DateSITimCalcClkElem(u1_t_raw, u1_a_UPDTRNK, u1_a_VAL, u1_a_SIGN);
    u4_t_hhmmss_new = u4_s_DateSITimUpdtDateTime(u4_a_HHMMSS_RAW, u1_a_UPDTRNK, u2_t_updt);

    return(u4_t_hhmmss_new);
}

/*===================================================================================================================================*/
/* static  U1      u1_s_DateSITimGetClkElem(const U4 u4_a_HHMMSS, const U1 u1_a_RNK)                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DateSITimGetClkElem(const U4 u4_a_HHMMSS, const U1 u1_a_RNK)
{
    U4  u4_t_mask;
    U1  u1_t_shift;
    U1  u1_t_elem;

    if(u1_a_RNK < (U1)DATESI_TIM_CALC_TBL_SIZE){
        u4_t_mask  = st_sp_DATESI_TIM_CALC[u1_a_RNK].u4_mask;
        u1_t_shift = st_sp_DATESI_TIM_CALC[u1_a_RNK].u1_shift;
        u1_t_elem  = (U1)((u4_a_HHMMSS & u4_t_mask) >> u1_t_shift);
    }
    else{
        u1_t_elem = (U1)0U;
    }
    
    return(u1_t_elem);
}

/*===================================================================================================================================*/
/* static  U1      u1_s_DateSITimCalcClkElem(const U1 u1_a_RAW, const U1 u1_a_RNK, const U1 u1_a_VAL, const U1 u1_a_SIGN)            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DateSITimCalcClkElem(const U1 u1_a_RAW, const U1 u1_a_RNK, const U1 u1_a_VAL, const U1 u1_a_SIGN)
{
    U1  u1_t_mod;
    U1  u1_t_result;

    u1_t_result = u1_a_RAW;

    if(u1_a_RNK < (U1)DATESI_TIM_CALC_TBL_SIZE){
        u1_t_mod = st_sp_DATESI_TIM_CALC[u1_a_RNK].u1_mod;
        if(u1_a_SIGN == (U1)DATESI_TIM_ADJ_PLUS){
            u1_t_result = ((u1_a_RAW + u1_a_VAL) % u1_t_mod);
        }
        else{
            if(u1_a_VAL <= u1_a_RAW){
                u1_t_result = u1_a_RAW - u1_a_VAL;
            }
            else{
                u1_t_result = u1_t_mod - ((u1_a_VAL - u1_a_RAW) % u1_t_mod);
            }
        }
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_DateSITimUpdtDateTime(const U4 u4_a_HHMMSS_RAW, const U1 u1_a_RNK, const U2 u2_a_VAL)                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4       u4_s_DateSITimUpdtDateTime(const U4 u4_a_HHMMSS_RAW, const U1 u1_a_RNK, const U2 u2_a_VAL)
{
    U4  u4_t_mask;
    U1  u1_t_shift;
    U4  u4_t_hhmmss_updt;

    u4_t_hhmmss_updt = u4_a_HHMMSS_RAW;

    if(u1_a_RNK < (U1)DATESI_TIM_CALC_TBL_SIZE){
        u4_t_mask         = st_sp_DATESI_TIM_CALC[u1_a_RNK].u4_mask;
        u1_t_shift        = st_sp_DATESI_TIM_CALC[u1_a_RNK].u1_shift;
        u4_t_hhmmss_updt  = u4_a_HHMMSS_RAW & (U4)(~u4_t_mask);
        u4_t_hhmmss_updt |= ((U4)u2_a_VAL << u1_t_shift);
    }

    return(u4_t_hhmmss_updt);
}

/*===================================================================================================================================*/
/* void            vd_g_DateSITimClockUpdate(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSITimClockUpdate(void)
{
    U4  u4_t_hhmmss_update;
    U4  u4_t_hhmmss_diag;
    S4  s4_t_offset;
    U1  u1_t_calendar;

    u4_t_hhmmss_diag   = u4_g_DateSITim();
    s4_t_offset        = s4_s_datesi_tim_ofst * (S4)DATESI_TIM_SIGN_CHG;
    u1_t_calendar      = u1_g_DateSICfgCalExst();

    if(u1_s_datesi_tim_adj_sts == (U1)DATESI_TIM_ADJ_ACT){
        vd_s_DateSITimDiagClkOldBak(u4_t_hhmmss_diag);

        u4_t_hhmmss_update = u4_s_DateSITimUpdateNow(u4_s_datesi_tim_adj_clock, s4_t_offset);

        (void)u1_g_DateSITimAdjustOwnClk(u4_t_hhmmss_update);

        u4_t_hhmmss_diag = u4_g_DateclkHhmmss24h();
        u4_t_hhmmss_diag = u4_s_DateSITimUpdateNow(u4_t_hhmmss_diag, s4_s_datesi_tim_ofst);
        vd_s_DateSITimDiagClkNewBak(u4_t_hhmmss_diag);
        vd_g_DateSITimSetDispClk(u4_t_hhmmss_diag);

        if(u1_t_calendar == (U1)DATESI_CALEXIST_ON){
            vd_g_DateSICalClockUpdate();
        }
    }
}

/*===================================================================================================================================*/
/* static  U4      u4_s_DateSITimMakeHHMMSS(const U1 u1_a_HOUR, const U1 u1_a_MIN, const U1 u1_a_SEC)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4       u4_s_DateSITimMakeHHMMSS(const U1 u1_a_HOUR, const U1 u1_a_MIN, const U1 u1_a_SEC)
{
#if (HHMMSS_LSB_SE != 0)
#error "datesi_tim_avn.c(u4_s_DateSITimMakeHHMMSS):HHMMSS_LSB_SE is not 0! "
#endif
    U4  u4_t_hhmmss_24h;

    u4_t_hhmmss_24h  = ((U4)u1_a_HOUR << HHMMSS_LSB_HR);
    u4_t_hhmmss_24h |= ((U4)u1_a_MIN  << HHMMSS_LSB_MI);
    u4_t_hhmmss_24h |= ((U4)u1_a_SEC                  ); /* HHMMSS_LSB_SE */
    /* ------------------------------------------------------------------------------------ */
    /* Caution!                                                                             */
    /* The shift operation of HHMMSS_LSB_SE is not described, Because HHMMSS_LSB_SE is 0.   */
    /* If HHMMSS_LSB_SE becomes a value other than 0, it is necessary to describe it.       */
    /* ------------------------------------------------------------------------------------ */

    return(u4_t_hhmmss_24h);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_DateSITimUpdateNow(const U4 u4_a_NOW, const S4 s4_a_OFST)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_DateSITimUpdateNow(const U4 u4_a_NOW, const S4 s4_a_OFST)
{
    S4  s4_t_now_sec;
    U4  u4_t_now_sec_24h;

    s4_t_now_sec = (S4)u4_g_HhmmssToSeconds(u4_a_NOW) + s4_a_OFST;
    if(s4_t_now_sec < (S4)0){
        s4_t_now_sec    += (S4)HHMMSS_24HR_TO_SE;
        u4_t_now_sec_24h = (U4)s4_t_now_sec;
    }
    else if(s4_t_now_sec >= (S4)HHMMSS_24HR_TO_SE){
        u4_t_now_sec_24h = (U4)s4_t_now_sec - (U4)HHMMSS_24HR_TO_SE;
    }
    else{
        u4_t_now_sec_24h = (U4)s4_t_now_sec;
    }

    return(u4_g_SecondsToHhmmss(u4_t_now_sec_24h));
}

/*===================================================================================================================================*/
/* static  void    vd_s_DateSITimAddOfstTime(const U1 u1_a_RNK, const S1 s1_a_VAL)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_DateSITimAddOfstTime(const U1 u1_a_VAL, const U1 u1_a_SIGN)
{
    S4  s4_t_offset_tim;
    S4  s4_t_offset_val;

    vd_g_DateSITimCfgOfstAdjStart();
    s4_t_offset_tim = s4_g_DateSITimCfgGetOfstTime();
    
    if(u1_a_SIGN == (U1)DATESI_TIM_ADJ_MINUS){
        s4_t_offset_val = (((S4)((U4)u1_a_VAL) * (S4)HHMMSS_MI_TO_SE) * (S4)DATESI_TIM_SIGN_CHG);
    }
    else{
        s4_t_offset_val = (S4)((U4)u1_a_VAL) * (S4)HHMMSS_MI_TO_SE;
    }
    s4_t_offset_tim += s4_t_offset_val;
    s4_t_offset_tim  = s4_s_DateSITimChkOfstTime(s4_t_offset_tim);
    vd_g_DateSITimCfgSetOfstTime(s4_t_offset_tim);
}

/*===================================================================================================================================*/
/* static  U4      s4_s_DateSITimChkOfstTime(const S4 s4_a_OFST)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static S4 s4_s_DateSITimChkOfstTime(const S4 s4_a_OFST)
{
    S4  s4_t_offset_new;

    if(s4_a_OFST < s4_g_DATESI_TIM_OFFSET_MIN){
        s4_t_offset_new = s4_g_DATESI_TIM_OFFSET_MIN;
    }
    else if(s4_a_OFST > s4_g_DATESI_TIM_OFFSET_MAX){
        s4_t_offset_new = s4_g_DATESI_TIM_OFFSET_MAX;
    }
    else{
        s4_t_offset_new = s4_a_OFST;
    }
    return(s4_t_offset_new);
}

/*===================================================================================================================================*/
/* static  U4      s4_s_DateSITimChkTimZn(const S4 s4_a_TIMZN)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  S4      s4_s_DateSITimChkTimZn(const S4 s4_a_TIMZN)
{
    S4  s4_t_timzn_new;

    if(s4_a_TIMZN < s4_g_DATESI_TIM_TIMZN_MIN){
        s4_t_timzn_new = s4_g_DATESI_TIM_TIMZN_MIN;
    }
    else if(s4_a_TIMZN > s4_g_DATESI_TIM_TIMZN_MAX){
        s4_t_timzn_new = s4_g_DATESI_TIM_TIMZN_MAX;
    }
    else{
        s4_t_timzn_new = s4_a_TIMZN;
    }
    return(s4_t_timzn_new);
}

/*===================================================================================================================================*/
/* static  void    vd_s_DateSITimDiagClear(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DateSITimDiagAdjClear(void)
{
    u1_s_datesi_tim_diagsts = (U1)DATESI_TIM_DIAG_STS_NON;
    u2_s_datesi_tim_diagcnt = (U2)DATESI_TIM_DIAG_CNT_INIT;
}

/*===================================================================================================================================*/
/* static  void    vd_s_DateSITimAddOfstTime(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DateSITimDiagItemClear(void)
{
    U1  u1_t_cnt;

    u1_s_datesi_tim_diagact = (U1)FALSE;

    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)DATESI_TIM_DIAG_INFO_NUM; u1_t_cnt++){
        u4_s_datesi_tim_diaginfo[u1_t_cnt] = u4_s_DATESI_TIM_INFO_INIT[u1_t_cnt];
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_DateSITimDiagRoutine(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DateSITimDiagRoutine(void)
{
    if(u1_s_datesi_tim_diagsts != (U1)DATESI_TIM_DIAG_STS_NON){
        if(u2_s_datesi_tim_diagcnt < (U2)U2_MAX) {
            u2_s_datesi_tim_diagcnt++;
        }
        else{
            u2_s_datesi_tim_diagcnt = (U2)U2_MAX;
        }
        if(u2_s_datesi_tim_diagcnt > (U2)DATESI_TIM_DIAG_CNT_END){
            if(u1_s_datesi_tim_diagsts == (U1)DATESI_TIM_DIAG_STS_CUSTOMIZE){
                u1_s_datesi_tim_diagact = (U1)TRUE;
            }
            vd_s_DateSITimDiagAdjClear();
        }
    }
    else{
        vd_s_DateSITimDiagAdjClear();
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_DateSITimDiagClkFctBak(const U1 u1_a_ADJ_FCT)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DateSITimDiagClkFctBak(const U1 u1_a_ADJ_FCT)
{
    if(u1_a_ADJ_FCT < (U1)DATESI_TIM_DIAG_FCT_NUM){
        u4_s_datesi_tim_diaginfo[DATESI_TIM_DIAG_INFO_FAC] = (U4)u1_a_ADJ_FCT;
        u2_s_datesi_tim_diagcnt = (U2)DATESI_TIM_DIAG_CNT_INIT;
        if(u1_s_datesi_tim_diagsts == (U1)DATESI_TIM_DIAG_STS_NON){
            u1_s_datesi_tim_diagsts = (U1)DATESI_TIM_DIAG_STS_START;
        }
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_DateSITimDiagClkOldBak(const U4 u4_a_HHMMSS_OLD)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DateSITimDiagClkOldBak(const U4 u4_a_HHMMSS_OLD)
{
    if(u1_s_datesi_tim_diagsts == (U1)DATESI_TIM_DIAG_STS_START){
        u4_s_datesi_tim_diaginfo[DATESI_TIM_DIAG_INFO_BAC] = u4_a_HHMMSS_OLD;
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_DateSITimDiagClkNewBak(const U4 u4_a_HHMMSS_NEW)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DateSITimDiagClkNewBak(const U4 u4_a_HHMMSS_NEW)
{
    if((u1_s_datesi_tim_diagsts == (U1)DATESI_TIM_DIAG_STS_START    ) ||
       (u1_s_datesi_tim_diagsts == (U1)DATESI_TIM_DIAG_STS_CUSTOMIZE)){
        u4_s_datesi_tim_diaginfo[DATESI_TIM_DIAG_INFO_NEW] = u4_a_HHMMSS_NEW;
        u2_s_datesi_tim_diagcnt                            = (U2)DATESI_TIM_DIAG_CNT_INIT;
        u1_s_datesi_tim_diagsts                            = (U1)DATESI_TIM_DIAG_STS_CUSTOMIZE;
    }
}

/*===================================================================================================================================*/
/* U1              u1_g_DateSITimDiagEvCapt(const U1 u1_a_ODO_UPDT, U4 * const u4_ap_ss)                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_DateSITimDiagEvCapt(const U1 u1_a_ODO_UPDT, U4 * const u4_ap_ss)
{
    U1  u1_t_cnt;
    U1  u1_t_capt;

    u1_t_capt = (U1)FALSE;
    if(u4_ap_ss != vdp_PTR_NA){
        if(u1_s_datesi_tim_diagact == (U1)TRUE){
            for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)DATESI_TIM_DIAG_INFO_NUM; u1_t_cnt++){
                u4_ap_ss[u1_t_cnt] = u4_s_datesi_tim_diaginfo[u1_t_cnt];
                /* ---------------------------------------------------------------------- */
                /* Since the number of array elements is checked in pivate.h,             */
                /* it is not necessary to check the number of array elements in u4_ap_ss. */
                /* ---------------------------------------------------------------------- */
            }
            vd_s_DateSITimDiagItemClear();
            u1_t_capt = (U1)TRUE;
        }
    }

    return(u1_t_capt);
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
/*  0.0.1    12/18/2025  MN       Change for BEV Pre_CV                                                                              */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  BEV-1    12/18/2025  MN       Addressing issues.                                                                                 */
/*                                                                                                                                   */
/*  * MN   = Mikiya Negishi, KSE                                                                                                     */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/