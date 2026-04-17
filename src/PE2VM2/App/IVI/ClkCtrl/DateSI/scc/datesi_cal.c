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
#define DATESI_CAL_C_MAJOR                      (0)
#define DATESI_CAL_C_MINOR                      (1)
#define DATESI_CAL_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "datesi_cal_cfg_private.h"
#include "datesi_tim_cfg_private.h"
#include "datesi_cfg_private.h"
#include "datesi_com.h"
#include "rtime.h"
#include "date_clk.h"
#include "datesi_abs.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DATESI_CAL_C_MAJOR != DATESI_CAL_H_MAJOR) || \
     (DATESI_CAL_C_MINOR != DATESI_CAL_H_MINOR) || \
     (DATESI_CAL_C_PATCH != DATESI_CAL_H_PATCH))
#error "datesi_cal.c and datesi_cal.h : source and header files are inconsistent!"
#endif

#if ((DATESI_CAL_C_MAJOR != DATESI_CAL_CFG_H_MAJOR) || \
     (DATESI_CAL_C_MINOR != DATESI_CAL_CFG_H_MINOR) || \
     (DATESI_CAL_C_PATCH != DATESI_CAL_CFG_H_PATCH))
#error "datesi_cal.c and datesi_cal_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DATESI_CAL_NOW_INIT                     (0x08CF0000U)
#define DATESI_CAL_ABS_DATE                     (0U)
#define DATESI_CAL_DISP_DATE                    (1U)

#define DATESI_CAL_ADJ_NON                      (0U)
#define DATESI_CAL_ADJ_ACT                      (1U)

#define DATESI_CAL_CALC_TBL_SIZE                (3U)

#define DATESI_CAL_MOD_FCT                      (1U)
#define DATESI_CAL_OFFSET_MO                    (1U)
#define DATESI_CAL_OFFSET_DA                    (1U)
#define DATESI_CAL_DAY_MAX                      (31U)

#define DATESI_CAL_DEF_MM_DD                    (0x00001010U)
#define DATESI_CAL_MIN_MM_DD                    (0x00001010U)

/* Change prohibition parameter */
#define DATESI_CAL_SIGN_CHG                     (-1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U4  u4_mask;
    U1  u1_shift;
}ST_DATESI_CAL_CALC;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U4                                      u4_s_datesi_cal_now;
static  U4                                      u4_s_datesi_cal_daycnt_last;
static  U1                                      u1_s_datesi_cal_timsync_act;
static  U1                                      u1_s_datesi_cal_adj_sts;
static  U4                                      u4_s_datesi_cal_adj_date;
static  U2                                      u2_s_datesi_cal_year_min;
static  U4                                      u4_s_datesi_cal_daycnt_min;
static  U4                                      u4_s_datesi_cal_daycnt_absmin;
static  U1                                      u1_s_datesi_cal_init_read_fin;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static        void    vd_s_DateSICalInit(void);
static        U1      u1_s_DateSICalInitReadiVDsh(void);
static        void    vd_s_DateSICalSync(U4 * u4p_a_offstd_now);
static        U4      u4_s_DateSICalToUpdtDate(const U4 u4_a_YYMMDD_DISP, const U1 u1_a_KIND);
static        U4      u4_s_DateSICalAddDay(const U4 u4_a_YYMMDD_RAW, const U4 u4_a_HHMMSS_RAW, const S4 s4_a_SECOND_ADD, const U1 u1_a_KIND);
static        void    vd_s_DateSICalWriteRtcDate(void);
static        U4      u4_s_DateSICalOpeAdjdate(const U4 u4_a_RAW, const U1 u1_a_RNK, const U1 u1_a_VAL, const U1 u1_a_SIGN);
static        U2      u2_s_DateSICalGetDateElem(const U4 u4_a_YYMMDDWK, const U1 u1_a_RNK);
static        U2      u2_s_DateSICalCalcClkDateElem(const U2 u2_a_RAW, const U1 u1_a_RNK, const U1 u1_a_VAL, const U1 u1_a_SIGN, const U1 u1_a_MOD);
static        U4      u4_g_DateSICalMakeYYMMDD(const U2 u2_a_YEAR, const U1 u1_a_MON, const U1 u1_a_DAY);
static        U2      u2_s_DateSICalCalcGuard(const U2 u2_a_RAW, const U1 u1_a_VAL, const U1 u1_a_SIGN, const U2 u2_a_MIN, const U2 u2_a_MAX);
static        U2      u2_s_DateSICalRangeGuard(const U2 u2_a_RAW, const U2 u2_a_MIN, const U2 u2_a_MAX);

/*===================================================================================================================================*/
/* void            vd_g_DateSICalBonInit(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSICalBonInit(void)
{
    u2_s_datesi_cal_year_min = u2_g_DateSICalCfgBonInit();
    vd_s_DateSICalInit();
    vd_g_DateSICalCfgCanTx(u4_s_datesi_cal_now, (U1)FALSE);
}

/*===================================================================================================================================*/
/* void            vd_g_DateSICalRstWkupInit(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSICalRstWkupInit(void)
{
    u2_s_datesi_cal_year_min = u2_g_DateSICalCfgRstWkupInit();
    vd_s_DateSICalInit();
    vd_g_DateSICalCfgCanTx(u4_s_datesi_cal_now, (U1)FALSE);
}

/*===================================================================================================================================*/
/* static void     vd_s_DateSICalInit(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DateSICalInit(void)
{
    U2  u2_t_cal_min;
    U4  u4_t_min_yymmdd;
    U4  u4_t_daycnt_write;

    u4_s_datesi_cal_now           = (U4)DATESI_CAL_NOW_INIT;           /* YA=8CF MO=0 DA=00 WK =00 */
    u4_s_datesi_cal_adj_date      = (U4)YYMMDDWK_UNKNWN;
    u1_s_datesi_cal_timsync_act   = (U1)FALSE;
    u1_s_datesi_cal_adj_sts       = (U1)DATESI_CAL_ADJ_NON;

    u4_s_datesi_cal_daycnt_last   = u4_g_YymmddToDaycnt(u4_s_datesi_cal_now);

    u2_t_cal_min                  = u2_s_datesi_cal_year_min;
    u4_t_min_yymmdd               = (U4)DATESI_CAL_MIN_MM_DD;
    u4_t_min_yymmdd              |= ((U4)u2_t_cal_min << YYMMDDWK_LSB_YR);
    u4_s_datesi_cal_daycnt_min    = u4_g_YymmddToDaycnt(u4_t_min_yymmdd);
    u4_s_datesi_cal_daycnt_absmin = u4_s_datesi_cal_daycnt_min - (U4)1U;

    u1_s_datesi_cal_init_read_fin = (U1)FALSE;

    /* iVDsh Initial Value Transmit*/
    u4_t_daycnt_write = (U4)U4_MAX;
    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO1_DSPCAL, &u4_s_datesi_cal_now, (U2)DATESI_CAL_VM_1WORD);
    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO1_CAL, &u4_t_daycnt_write, (U2)DATESI_CAL_VM_1WORD);
}

/*===================================================================================================================================*/
/* void            vd_g_DateSICalMainTask(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSICalMainTask(void)
{
    U1  u1_t_read_sts;
    U1  u1_t_exsit;

    if(u1_s_datesi_cal_init_read_fin != (U1)TRUE){
        u1_t_read_sts = u1_s_DateSICalInitReadiVDsh();
        if(u1_t_read_sts != (U1)IVDSH_NO_REA){
            u1_s_datesi_cal_init_read_fin = (U1)TRUE;
        }
    }

    u1_t_exsit = u1_g_DateSICfgCalExst();
    if(u1_t_exsit == (U1)DATESI_CALEXIST_ON){
        vd_s_DateSICalSync(&u4_s_datesi_cal_now);
        vd_s_DateSICalWriteRtcDate();
        vd_g_DateSICalCfgCanTx(u4_s_datesi_cal_now, (U1)TRUE);
        vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO1_DSPCAL, &u4_s_datesi_cal_now, (U2)DATESI_CAL_VM_1WORD);
    }
    else{
        vd_s_DateSICalInit();
    }
}

/*===================================================================================================================================*/
/* U1              u1_s_DateSICalInitReadiVDsh(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_read_sts : TRUE/FALSE                                                                                       */
/*===================================================================================================================================*/
static U1       u1_s_DateSICalInitReadiVDsh(void)
{
    U2  u2_t_cal_min;
    U4  u4_t_min_yymmdd;
    U1  u1_t_read_sts;

    u2_t_cal_min  = (U2)0U;
    u1_t_read_sts = u1_g_DateSICalCfgInitCalmin(&u2_t_cal_min);
    if(u1_t_read_sts != (U1)IVDSH_NO_REA){
        u2_s_datesi_cal_year_min      = u2_t_cal_min;
        u4_t_min_yymmdd               = (U4)DATESI_CAL_MIN_MM_DD;
        u4_t_min_yymmdd              |= ((U4)u2_t_cal_min << YYMMDDWK_LSB_YR);
        u4_s_datesi_cal_daycnt_min    = u4_g_YymmddToDaycnt(u4_t_min_yymmdd);
        u4_s_datesi_cal_daycnt_absmin = u4_s_datesi_cal_daycnt_min - (U4)1U;
    }
    
    return(u1_t_read_sts);
}
/*===================================================================================================================================*/
/* static void     vd_s_DateSICalSync(U4 * u4p_a_offstd_now)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DateSICalSync(U4 * u4p_a_offstd_now)
{
    U4                u4_t_now;
    U4                u4_t_adj;
    U4                u4_t_yymmdd;
    U1                u1_t_calsync_act;
    U1                u1_t_result;
    ST_DATESI_CAL_RX  st_t_cal_rx;

    u1_t_result                          = (U1)FALSE;
    u4_t_yymmdd                          = (U4)YYMMDDWK_UNKNWN;
    st_t_cal_rx.u1_valid                 = (U1)FALSE;
    st_t_cal_rx.u1_act                   = (U1)FALSE;
    st_t_cal_rx.u1p_date[YYMMDD_DATE_DA] = (U1)U1_MAX;
    st_t_cal_rx.u1p_date[YYMMDD_DATE_MO] = (U1)U1_MAX;
    st_t_cal_rx.u1p_date[YYMMDD_DATE_YR] = (U1)U1_MAX;
    (void)u1_g_DateSICalCfgCanRx(&st_t_cal_rx);
    u1_t_calsync_act                     = u1_g_DateSICalDateSyncChk(st_t_cal_rx, &u4_t_yymmdd);

    if((u1_s_datesi_cal_timsync_act == (U1)TRUE) &&
       (u1_t_calsync_act            == (U1)TRUE)){
        u4_t_now = u4_t_yymmdd;
        u4_t_adj = u4_t_yymmdd;
    }
    else{
        u4_t_now = u4_g_DateSIAbsYymmddwk();
        u4_t_adj = (U4)YYMMDDWK_UNKNWN;
    }

    if(u4_t_adj != (U4)YYMMDDWK_UNKNWN){
        u1_t_result = u1_g_DateSICalAdjustOwnClk(u4_t_adj);
        if(u1_t_result == (U1)TRUE){
            vd_g_DateSIAbsAdjYymmddwk(u4_t_now, u4_t_adj);
        }
    }
    vd_g_DateSIComSetCmp(u1_t_result,(U1)DATESI_COM_KIND_CAL);

    if((u1_t_result == (U1)TRUE) || (u4_t_adj == (U4)YYMMDDWK_UNKNWN)){
        (*u4p_a_offstd_now) = u4_s_DateSICalToUpdtDate(u4_t_now, (U1)DATESI_CAL_DISP_DATE);
    }

    u1_s_datesi_cal_timsync_act = (U1)FALSE;
}

/*===================================================================================================================================*/
/* U1              u1_g_DateSICalAdjustOwnClk(const U4 u4_a_YYYYMMDD)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_DateSICalAdjustOwnClk(const U4 u4_a_YYYYMMDD)
{
    U1  u1_t_ret;
    
    (void)u1_g_DateclkAdjUnLock((U1)DATE_CLK_ADJ_YYMMDD);
    u1_t_ret = u1_g_DateclkAdjYymmdd(u4_a_YYYYMMDD);
    vd_g_DateclkSet();
    vd_g_DateclkAdjLock((U1)DATE_CLK_ADJ_YYMMDD);
    
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/* U1              u1_g_DateSICalDateSyncChk(const ST_DATESI_CAL_RX st_a_CAL_RX, U4 * u4_ap_yymmdd)                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_DateSICalDateSyncChk(const ST_DATESI_CAL_RX st_a_CAL_RX, U4 * u4_ap_yymmdd)
{
    U1  u1_t_result;
    U1  u1_t_frm_is_ok;
    U2  u2_t_year;
    U4  u4_t_yymmdd;
    U2  u2_t_dummy[YYMMDD_DATE_SIZE];

    u1_t_result     = (U1)FALSE;
    u2_t_year       = (U2)st_a_CAL_RX.u1p_date[YYMMDD_DATE_YR]   + (U2)DATESI_CAL_YEAR_OFFSET;
    u4_t_yymmdd     = ((U4)u2_t_year                            << YYMMDDWK_LSB_YR);
    u4_t_yymmdd    |= ((U4)st_a_CAL_RX.u1p_date[YYMMDD_DATE_MO] << YYMMDDWK_LSB_MO);
    u4_t_yymmdd    |= ((U4)st_a_CAL_RX.u1p_date[YYMMDD_DATE_DA] << YYMMDDWK_LSB_DA);
    (*u4_ap_yymmdd) = u4_t_yymmdd;
    u1_t_frm_is_ok  = u1_g_YymmddFrmtOk(u4_t_yymmdd, &u2_t_dummy[0]);

    if((u1_t_frm_is_ok  == (U1)TRUE                ) &&
       (u2_t_year       >= u2_s_datesi_cal_year_min) &&
       (u2_t_year       <= u2_g_DATESI_CAL_YEAR_MAX)){
        u1_t_result = (U1)TRUE;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/* void            vd_g_DateSICalSyncAct(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSICalSyncAct(void)
{
    u1_s_datesi_cal_timsync_act = (U1)TRUE;
}

/*===================================================================================================================================*/
/* void            vd_g_DateSICalExecTmSet(const U1 u1_a_ADD)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSICalExecTmSet(const U1 u1_a_ADD)
{
    U4  u4_t_yymmddwk_zerorst;
    U4  u4_t_daycnt_zerorst;
    U4  u4_t_abs_yymmdd;

    u4_t_yymmddwk_zerorst = u4_s_datesi_cal_now;
    u4_t_daycnt_zerorst   = u4_g_YymmddToDaycnt(u4_t_yymmddwk_zerorst);

    if((u4_t_daycnt_zerorst < (U4)U4_MAX) &&
       (u1_a_ADD           == (U1)TRUE  )){
        u4_t_daycnt_zerorst++;
    }

    u4_t_yymmddwk_zerorst = u4_g_DaycntToYymmddwk(u4_t_daycnt_zerorst);
    u4_t_abs_yymmdd       = u4_s_DateSICalToUpdtDate(u4_t_yymmddwk_zerorst, (U1)DATESI_CAL_ABS_DATE);
    vd_g_DateSIAbsAdjYymmddwk(u4_t_abs_yymmdd, (U4)YYMMDDWK_UNKNWN);
}

/*===================================================================================================================================*/
/* void            vd_g_DateSICalClockUpdate(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSICalClockUpdate(void)
{
    U4  u4_t_abs_yymmdd;

    u4_t_abs_yymmdd = u4_s_DateSICalToUpdtDate(u4_s_datesi_cal_now, (U1)DATESI_CAL_ABS_DATE);
    vd_g_DateSIAbsAdjYymmddwk(u4_t_abs_yymmdd, (U4)YYMMDDWK_UNKNWN);
}

/*===================================================================================================================================*/
/* static U4       u4_s_DateSICalToUpdtDate(const U4 u4_a_YYMMDD_DISP, const U1 u1_a_KIND)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4       u4_s_DateSICalToUpdtDate(const U4 u4_a_YYMMDD_DISP, const U1 u1_a_KIND)
{
    U4  u4_t_hhmmss_abs;
    S4  s4_t_total_offset;
    U4  u4_t_yymmddwk_abs;

    u4_t_hhmmss_abs   = u4_g_DateSIAbsHhmmss24h();
    s4_t_total_offset = s4_g_DateSITimTotalOffset();
    u4_t_yymmddwk_abs = u4_s_DateSICalAddDay(u4_a_YYMMDD_DISP, u4_t_hhmmss_abs, s4_t_total_offset, u1_a_KIND);

    return(u4_t_yymmddwk_abs);
}

/*===================================================================================================================================*/
/* static U4 u4_s_DateSICalAddDay(const U4 u4_a_YYMMDD_RAW, const U4 u4_a_HHMMSS_RAW, const S4 s4_a_SECOND_ADD, const U1 u1_a_KIND)  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4       u4_s_DateSICalAddDay(const U4 u4_a_YYMMDD_RAW, const U4 u4_a_HHMMSS_RAW, const S4 s4_a_SECOND_ADD, const U1 u1_a_KIND)
{
    U4  u4_t_daycnt;        /* Day Count  */
    S4  s4_t_daycnt;        /* Day Count  */
    S4  s4_t_adj_day;       /* Adjust Day */
    U4  u4_t_second_raw;    /* Raw Second */
    S4  s4_t_second_new;    /* After Calculation Second */
    U4  u4_t_yymmdd_new;    /* After Calculation Date */
    S4  s4_t_adj_Judge;     /* Adjust Judge */

    u4_t_daycnt     = u4_g_YymmddToDaycnt(u4_a_YYMMDD_RAW);
    u4_t_second_raw = u4_g_HhmmssToSeconds(u4_a_HHMMSS_RAW);
    s4_t_second_new = s4_a_SECOND_ADD + (S4)u4_t_second_raw;

    if(s4_t_second_new >= (S4)0){
        s4_t_adj_day = (s4_t_second_new / (S4)HHMMSS_24HR_TO_SE);
    }
    else{
        s4_t_second_new *= (S4)DATESI_CAL_SIGN_CHG;
        s4_t_adj_day     = (s4_t_second_new / (S4)HHMMSS_24HR_TO_SE);
        s4_t_adj_Judge   = (s4_t_second_new % (S4)HHMMSS_24HR_TO_SE);
        if(s4_t_adj_Judge != (S4)0){
            s4_t_adj_day++;
        }
        s4_t_adj_day *= (S4)DATESI_CAL_SIGN_CHG;
    }

    if(u4_t_daycnt != (U4)YYMMDDWK_DAYCNT_UNKNWN){
        if(u1_a_KIND == (U1)DATESI_CAL_ABS_DATE){
            s4_t_adj_day *= (S4)DATESI_CAL_SIGN_CHG;
            s4_t_daycnt   = (S4)u4_t_daycnt + s4_t_adj_day;
            u4_t_daycnt   = (U4)s4_t_daycnt;
            if(u4_t_daycnt < u4_s_datesi_cal_daycnt_absmin){
                u4_t_daycnt = u4_s_datesi_cal_daycnt_absmin;
            }
            else if(u4_t_daycnt > u4_g_DATESI_CAL_DAYCNT_ABSMAX){
                u4_t_daycnt = u4_g_DATESI_CAL_DAYCNT_ABSMAX;
            }
            else{
                /* Do Nothing */
            }
        }
        else{
            s4_t_daycnt   = (S4)u4_t_daycnt + s4_t_adj_day;
            u4_t_daycnt   = (U4)s4_t_daycnt;
            if(u4_t_daycnt <= u4_s_datesi_cal_daycnt_min){
                u4_t_daycnt = u4_s_datesi_cal_daycnt_min;
            }
            else if(u4_t_daycnt >= u4_g_DATESI_CAL_DAYCNT_MAX){
                u4_t_daycnt = u4_g_DATESI_CAL_DAYCNT_MAX;
            }
            else{
                /* Do Nothing */
            }
        }
    }

    u4_t_yymmdd_new = u4_g_DaycntToYymmddwk(u4_t_daycnt);

    return(u4_t_yymmdd_new);
}

/*===================================================================================================================================*/
/* static void     vd_s_DateSICalWriteRtcDate(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DateSICalWriteRtcDate(void)
{
    U4  u4_t_daycnt_now;
    U4  u4_t_daycnt_write;
    U1  u1_t_esi_chk;

    u4_t_daycnt_now   = u4_g_YymmddToDaycnt(u4_s_datesi_cal_now);
    u1_t_esi_chk      = u1_g_DateSICalCfgEsichk();

    if(u4_t_daycnt_now > (U4)DATESI_CAL_OFFSET_2000DAYCUNT){
        u4_t_daycnt_write = u4_t_daycnt_now - (U4)DATESI_CAL_OFFSET_2000DAYCUNT;
                                                                                 /* QAC over-detection */
    }
    else{
        u4_t_daycnt_write = (U4)U4_MAX;
    }

    if((u1_t_esi_chk                == (U1)0U         ) &&
      ((u4_s_datesi_cal_daycnt_last != u4_t_daycnt_now) &&
       (u4_t_daycnt_write           != (U4)U4_MAX     ))){
        vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO1_CAL, &u4_t_daycnt_write, (U2)DATESI_CAL_VM_1WORD);
        u4_s_datesi_cal_daycnt_last = u4_t_daycnt_now;
    }
}

/*===================================================================================================================================*/
/* void            vd_g_DateSICalAdjustStart(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSICalAdjustStart(void)
{
    u4_s_datesi_cal_adj_date = u4_s_datesi_cal_now;
    u1_s_datesi_cal_adj_sts  = (U1)DATESI_CAL_ADJ_ACT;
}

/*===================================================================================================================================*/
/* void            vd_g_DateSICalAdjustReq(const U1 u1_a_RNK, const U1 u1_a_VAL, const U1 u1_a_SIGN)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSICalAdjustReq(const U1 u1_a_RNK, const U1 u1_a_VAL, const U1 u1_a_SIGN)
{
    if(u1_s_datesi_cal_adj_sts == (U1)DATESI_CAL_ADJ_ACT){
        u4_s_datesi_cal_adj_date = u4_s_DateSICalOpeAdjdate(u4_s_datesi_cal_adj_date, u1_a_RNK, u1_a_VAL, u1_a_SIGN);
    }
}

/*===================================================================================================================================*/
/* static U4       u4_s_DateSICalOpeAdjdate(const U4 u4_a_RAW, const U1 u1_a_RNK, const U1 u1_a_VAL, const U1 u1_a_SIGN)             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4       u4_s_DateSICalOpeAdjdate(const U4 u4_a_RAW, const U1 u1_a_RNK, const U1 u1_a_VAL, const U1 u1_a_SIGN)
{
    U2 u2_t_elem;
    U1 u1_t_mod;
    U2 u2_t_year;
    U2 u2_t_mon;
    U2 u2_t_day;
    U2 u2_t_result;
    U2 u2_t_offset;
    U4 u4_t_yymmdd;
    
    u2_t_year = u2_s_DateSICalGetDateElem(u4_a_RAW, (U1)DATESI_CAL_RNK_YEAE);
    u2_t_mon  = u2_s_DateSICalGetDateElem(u4_a_RAW, (U1)DATESI_CAL_RNK_MONTH);
    u2_t_day  = u2_s_DateSICalGetDateElem(u4_a_RAW, (U1)DATESI_CAL_RNK_DAY);

    u2_t_year = u2_s_DateSICalRangeGuard(u2_t_year, u2_s_datesi_cal_year_min, u2_g_DATESI_CAL_YEAR_MAX);
    u2_t_mon  = u2_s_DateSICalRangeGuard(u2_t_mon, (U2)YYMMDDWK_MO_MIN, (U2)YYMMDDWK_MO_MAX);
    u2_t_day  = u2_s_DateSICalRangeGuard(u2_t_day, (U2)YYMMDDWK_DA_MIN, (U2)DATESI_CAL_DAY_MAX);

    if(u1_a_RNK == (U1)DATESI_CAL_RNK_YEAE){
        u2_t_year = u2_s_DateSICalCalcGuard(u2_t_year, u1_a_VAL, u1_a_SIGN, u2_s_datesi_cal_year_min, u2_g_DATESI_CAL_YEAR_MAX);
    }
    else{
        if(u1_a_RNK == (U1)DATESI_CAL_RNK_MONTH){
            u2_t_elem   = u2_t_mon;
            u2_t_offset = (U2)DATESI_CAL_OFFSET_MO;
            u1_t_mod    = ((U1)YYMMDDWK_MO_MAX - (U1)DATESI_CAL_OFFSET_MO) + (U1)DATESI_CAL_MOD_FCT;
        }
        else{
            u2_t_elem   = u2_t_day;
            u2_t_offset = (U2)DATESI_CAL_OFFSET_DA;
            u1_t_mod    = ((U1)DATESI_CAL_DAY_MAX - (U1)DATESI_CAL_OFFSET_DA) + (U1)DATESI_CAL_MOD_FCT;
        }
        
        u2_t_elem   -= u2_t_offset;
        u2_t_result  = u2_s_DateSICalCalcClkDateElem(u2_t_elem, u1_a_RNK, u1_a_VAL, u1_a_SIGN, u1_t_mod);
        u2_t_result += u2_t_offset;
        
        if(u1_a_RNK == (U1)DATESI_CAL_RNK_MONTH){
            u2_t_mon = u2_t_result;
        }
        else{
            u2_t_day = u2_t_result;
        }
    }

    u4_t_yymmdd = u4_g_DateSICalMakeYYMMDD(u2_t_year, (U1)u2_t_mon, (U1)u2_t_day);

    return (u4_t_yymmdd);
}

/*===================================================================================================================================*/
/* static U2       u2_s_DateSICalGetDateElem(const U4 u4_a_YYMMDDWK, const U1 u1_a_RNK)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2       u2_s_DateSICalGetDateElem(const U4 u4_a_YYMMDDWK, const U1 u1_a_RNK)
{
    static const ST_DATESI_CAL_CALC                 st_sp_DATESI_CAL_CALC[DATESI_CAL_CALC_TBL_SIZE] = {
        /* u4_mask               u1_shift */
        {(U4)YYMMDDWK_BIT_DA,    (U1)YYMMDDWK_LSB_DA},
        {(U4)YYMMDDWK_BIT_MO,    (U1)YYMMDDWK_LSB_MO},
        {(U4)YYMMDDWK_BIT_YR,    (U1)YYMMDDWK_LSB_YR}
    };
    U4 u4_t_mask;
    U1 u1_t_shift;
    U2 u2_t_elem;

    u2_t_elem = (U2)0U;

    if(u1_a_RNK < (U1)DATESI_CAL_CALC_TBL_SIZE) {
        u4_t_mask  = st_sp_DATESI_CAL_CALC[u1_a_RNK].u4_mask;
        u1_t_shift = st_sp_DATESI_CAL_CALC[u1_a_RNK].u1_shift;
        u2_t_elem  = (U2)((u4_a_YYMMDDWK & u4_t_mask) >> u1_t_shift);
    }

    return(u2_t_elem);
}

/*==========================================================================================================================================*/
/* static U2 u2_s_DateSICalCalcClkDateElem(const U2 u2_a_RAW, const U1 u1_a_RNK, const U1 u1_a_VAL, const U1 u1_a_SIGN, const U1 u1_a_MOD)  */
/* ---------------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                       */
/*  Return:         -                                                                                                                       */
/*==========================================================================================================================================*/
static U2       u2_s_DateSICalCalcClkDateElem(const U2 u2_a_RAW, const U1 u1_a_RNK, const U1 u1_a_VAL, const U1 u1_a_SIGN, const U1 u1_a_MOD)
{
    U2 u2_t_result;

    u2_t_result = u2_a_RAW;

    if(u1_a_RNK < (U1)DATESI_CAL_CALC_TBL_SIZE) {
        if(u1_a_SIGN == (U1)DATESI_CAL_ADJ_PLUS){
            u2_t_result = ((u2_a_RAW + (U2)u1_a_VAL) % (U2)u1_a_MOD);
        }
        else{
            if((U2)u1_a_VAL <= u2_a_RAW){
                u2_t_result = u2_a_RAW - (U2)u1_a_VAL;
            }
            else{
                u2_t_result = (U2)u1_a_MOD - (((U2)u1_a_VAL - u2_a_RAW) % (U2)u1_a_MOD);
            }
        }
    }

    return (u2_t_result);
}

/*==========================================================================================================================================*/
/* static U2       u2_s_DateSICalCalcGuard(const U2 u2_a_RAW, const U1 u1_a_VAL, const U1 u1_a_SIGN, const U2 u2_a_MIN, const U2 u2_a_MAX)  */
/* ---------------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                       */
/*  Return:         -                                                                                                                       */
/*==========================================================================================================================================*/
static U2       u2_s_DateSICalCalcGuard(const U2 u2_a_RAW, const U1 u1_a_VAL, const U1 u1_a_SIGN, const U2 u2_a_MIN, const U2 u2_a_MAX)
{
    U2 u2_t_result;


    if(u1_a_SIGN == (U1)DATESI_CAL_ADJ_PLUS){
        u2_t_result = u2_a_RAW + (U2)u1_a_VAL;
    }
    else{
        if((U2)u1_a_VAL <= u2_a_RAW){
            u2_t_result = u2_a_RAW - (U2)u1_a_VAL;
        }
        else{
            u2_t_result = u2_a_RAW;
        }
    }

    u2_t_result = u2_s_DateSICalRangeGuard(u2_t_result, u2_a_MIN, u2_a_MAX);

    return(u2_t_result);
}

/*==========================================================================================================================================*/
/* static U2       u2_s_DateSICalRangeGuard(const U2 u2_a_RAW, const U2 u2_a_MIN, const U2 u2_a_MAX)                                        */
/* ---------------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                       */
/*  Return:         -                                                                                                                       */
/*==========================================================================================================================================*/
static U2       u2_s_DateSICalRangeGuard(const U2 u2_a_RAW, const U2 u2_a_MIN, const U2 u2_a_MAX)
{
    U2 u2_t_return;

    if(u2_a_RAW < u2_a_MIN){
        u2_t_return = u2_a_MIN;
    }
    else if(u2_a_RAW > u2_a_MAX){
        u2_t_return = u2_a_MAX;
    }
    else{
        u2_t_return = u2_a_RAW;
    }

    return(u2_t_return);
}

/*===================================================================================================================================*/
/* static U4       u4_g_DateSICalMakeYYMMDD(const U2 u2_a_YEAR, const U1 u1_a_MON, const U1 u1_a_DAY)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4       u4_g_DateSICalMakeYYMMDD(const U2 u2_a_YEAR, const U1 u1_a_MON, const U1 u1_a_DAY)
{
    U4 u4_t_yymmddwk;

    u4_t_yymmddwk  = ((U4)u2_a_YEAR << YYMMDDWK_LSB_YR);
    u4_t_yymmddwk |= ((U4)u1_a_MON  << YYMMDDWK_LSB_MO);
    u4_t_yymmddwk |= ((U4)u1_a_DAY  << YYMMDDWK_LSB_DA);

    return (u4_t_yymmddwk);
}

/*===================================================================================================================================*/
/* void            vd_g_DateSICalAdjustUpdate(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSICalAdjustUpdate(void)
{
    U4  u4_t_abs_yymmdd;
    U1  u1_t_sts;

    u1_t_sts        = u1_g_DateSICalSetImpossible();

    if((u1_s_datesi_cal_adj_sts == (U1)DATESI_CAL_ADJ_ACT) &&
       (u1_t_sts                == (U1)FALSE             )){
        u4_t_abs_yymmdd     = u4_s_DateSICalToUpdtDate(u4_s_datesi_cal_adj_date, (U1)DATESI_CAL_ABS_DATE);
        vd_g_DateSIAbsAdjYymmddwk(u4_t_abs_yymmdd, (U4)YYMMDDWK_UNKNWN);
        u4_t_abs_yymmdd     = u4_g_DateSIAbsYymmddwk();
        u4_s_datesi_cal_now = u4_s_DateSICalToUpdtDate(u4_t_abs_yymmdd, (U1)DATESI_CAL_DISP_DATE);
    }
}

/*===================================================================================================================================*/
/* void            vd_g_DateSICalAdjustEnd(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSICalAdjustEnd(void)
{
    u1_s_datesi_cal_adj_sts = (U1)DATESI_CAL_ADJ_NON;
}

/*===================================================================================================================================*/
/* U4              u4_g_DateSICalGetAdjDispDate(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4              u4_g_DateSICalGetAdjDispDate(void)
{
    return(u4_s_datesi_cal_adj_date);
}

/*===================================================================================================================================*/
/* U1              u1_g_DateSICalSetImpossible(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_DateSICalSetImpossible(void)
{
    U1 u1_t_return;
    U2 u2_t_year;
    U2 u2_t_mon;
    U2 u2_t_day;
    U2 u2_t_max;

    u1_t_return = (U1)FALSE;
    u2_t_year   = u2_s_DateSICalGetDateElem(u4_s_datesi_cal_adj_date, (U1)DATESI_CAL_RNK_YEAE);
    u2_t_mon    = u2_s_DateSICalGetDateElem(u4_s_datesi_cal_adj_date, (U1)DATESI_CAL_RNK_MONTH);
    u2_t_day    = u2_s_DateSICalGetDateElem(u4_s_datesi_cal_adj_date, (U1)DATESI_CAL_RNK_DAY);
    u2_t_max    = u1_g_DayMaxofMonth((U4)u2_t_year, (U4)u2_t_mon);

    if((u2_t_day < (U2)YYMMDDWK_DA_MIN) ||
       (u2_t_day > u2_t_max           )){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);

}

/*===================================================================================================================================*/
/* U1              u1_g_DateSICalLimJdgYear(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_DateSICalLimJdgYear(void)
{
    U1  u1_t_return;
    U2  u2_t_year;

    u2_t_year   = u2_s_DateSICalGetDateElem(u4_s_datesi_cal_adj_date, (U1)DATESI_CAL_RNK_YEAE);

    if(u2_t_year >= u2_g_DATESI_CAL_YEAR_MAX){
        u1_t_return = (U1)DATESI_CAL_LIM_UP;
    }
    else if(u2_t_year <= u2_s_datesi_cal_year_min){
        u1_t_return = (U1)DATESI_CAL_LIM_DOWN;
    }
    else{
        u1_t_return = (U1)DATESI_CAL_LIM_NML;
    }
    return(u1_t_return);

}

/*===================================================================================================================================*/
/* U1              vd_g_DateSICalAdjustdate(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSICalAdjustdate(void)
{
    U1                u1_t_exsit;
    U4                u4_t_abs_yymmdd;
    U4                u4_t_yymmdd;
    U1                u1_t_range_is_ok;
    ST_DATESI_CAL_RX  st_t_cal_rx;

    u4_t_yymmdd                          = (U4)YYMMDDWK_UNKNWN;
    st_t_cal_rx.u1_valid                 = (U1)FALSE;
    st_t_cal_rx.u1_act                   = (U1)FALSE;
    st_t_cal_rx.u1p_date[YYMMDD_DATE_DA] = (U1)U1_MAX;
    st_t_cal_rx.u1p_date[YYMMDD_DATE_MO] = (U1)U1_MAX;
    st_t_cal_rx.u1p_date[YYMMDD_DATE_YR] = (U1)U1_MAX;

    u1_t_exsit = u1_g_DateSICfgCalExst();
    if(u1_t_exsit == (U1)DATESI_CALEXIST_ON){
        vd_g_DateSICalCfgRxUpdtdate(&st_t_cal_rx);
        u1_t_range_is_ok = u1_g_DateSICalDateSyncChk(st_t_cal_rx, &u4_t_yymmdd);

        if(u1_t_range_is_ok == (U1)TRUE){
            u4_t_abs_yymmdd     = u4_s_DateSICalToUpdtDate(u4_t_yymmdd, (U1)DATESI_CAL_ABS_DATE);
            vd_g_DateSIAbsAdjYymmddwk(u4_t_abs_yymmdd, (U4)YYMMDDWK_UNKNWN);
            u4_t_abs_yymmdd     = u4_g_DateSIAbsYymmddwk();
            u4_s_datesi_cal_now = u4_s_DateSICalToUpdtDate(u4_t_abs_yymmdd, (U1)DATESI_CAL_DISP_DATE);
        }
    }
}

/*===================================================================================================================================*/
/* U4              u4_g_DateSICalGetDaycntAbsMin(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         Lower bound date (for absolute dates)                                                                            */
/*===================================================================================================================================*/
U4              u4_g_DateSICalGetDaycntAbsMin(void)
{
    return(u4_s_datesi_cal_daycnt_absmin);
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
/*  0.1.0    04/01/2026  MN       Fix:Change in RTC handling (do not reflect user operations)                                        */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * MN   = Mikiya Negishi, KSE                                                                                                     */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
