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
#define DATE_CLK_C_MAJOR                         (1U)
#define DATE_CLK_C_MINOR                         (12U)
#define DATE_CLK_C_PATCH                         (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "date_clk_cfg_private.h"

#include "trpl_rdndnt.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DATE_CLK_C_MAJOR != DATE_CLK_H_MAJOR) || \
     (DATE_CLK_C_MINOR != DATE_CLK_H_MINOR) || \
     (DATE_CLK_C_PATCH != DATE_CLK_H_PATCH))
#error "date_clk.c and date_clk.h : source and header files are inconsistent!"
#endif

#if ((DATE_CLK_C_MAJOR != DATE_CLK_CFG_H_MAJOR) || \
     (DATE_CLK_C_MINOR != DATE_CLK_CFG_H_MINOR) || \
     (DATE_CLK_C_PATCH != DATE_CLK_CFG_H_PATCH))
#error "date_clk.c and date_clk_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DATE_CLK_NUM_BACK                        (5U)
#define DATE_CLK_BACK_NUM_CMPR                   (3U)
#define DATE_CLK_BACK_INI                        (0U)
#define DATE_CLK_BACK_1ST                        (1U)
#define DATE_CLK_BACK_2ND                        (2U)
#define DATE_CLK_BACK_3RD                        (3U)
#define DATE_CLK_BACK_4TH                        (4U)

#define DATE_CLK_SYNC_ACT_BU_FULL                (0x01U)
#define DATE_CLK_SYNC_ACT_RTC_RES                (0x02U)

#define DATE_CLK_SYNC_ACT_BIT_DAYC               (0x0cU)
#define DATE_CLK_SYNC_ACT_DAYC_INC               (0x00U)
#define DATE_CLK_SYNC_ACT_DAYC_LAS               (0x04U)
#define DATE_CLK_SYNC_ACT_DAYC_INI               (0x08U)

#define DATE_CLK_SYNC_ACT_BIT_HMS                (0x30U)
#define DATE_CLK_SYNC_ACT_HMS_RTC                (0x00U)
#define DATE_CLK_SYNC_ACT_HMS_LAS                (0x10U)
#define DATE_CLK_SYNC_ACT_HMS_INI                (0x20U)

#define DATE_CLK_OPE_RUN                         (0x5aa5a55aU)

#define DATE_CLK_DAYCNT_RDN_NUM                  (3U)
#define DATE_CLK_DAYCNT_RDN_1ST                  (0U)
#define DATE_CLK_DAYCNT_RDN_2ND                  (1U)
#define DATE_CLK_DAYCNT_RDN_3RD                  (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DATE_CLK_ADJ_HHMMSS != 0x01U) || (DATE_CLK_ADJ_YYMMDD != 0x02U))
#error "date_clk.c : DATE_CLK_ADJ_NUM_TOUT shall be greater than DATE_CLK_ADJ_HHMMSS and DATE_CLK_ADJ_YYMMDD."
#endif /* #if ((DATE_CLK_ADJ_HHMMSS != 0x01U) || (DATE_CLK_ADJ_YYMMDD != 0x02U)) */
#define DATE_CLK_ADJ_NUM_TOUT                    (3U)
#define DATE_CLK_ADJ_FRTSYN                      (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    volatile U4        u4_hhmmss_24h;
    volatile U4        u4_daycnt;
}ST_DATE_CLK_BK;

typedef struct{
    U1                 u1_last;
    U1                 u1_begin;
    U1                 u1_end;
}ST_DATE_CLK_BK_UPDT;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
/* CAUTION                                                                             */
/* ----------------------------------------------------------------------------------- */
/* Be careful when adding variables before or after u4_s_dateclk_daycnt_min_val#.      */
/* u4_s_dateclk_daycnt_min_val# is redundant data; variable definitions are            */
/* distributed to make RAM anomalies less likely.                                      */
/* ----------------------------------------------------------------------------------- */
static U4                  u4_s_dateclk_daycnt_min_val1          __attribute__((section(".bss_BACK")));
static U4                  u4_s_dateclk_tmrwk_tout               __attribute__((section(".bss_BACK")));
static S2                  s2_s_dateclk_calsubsecond             __attribute__((section(".bss_BACK")));

static ST_DATE_CLK_BK      st_sp_dateclk_back[DATE_CLK_NUM_BACK] __attribute__((section(".bss_BACK")));
static U4                  u4_s_dateclk_daycnt_min_val2          __attribute__((section(".bss_BACK")));

static U4                  u4_s_dateclk_frt_elpsd                __attribute__((section(".bss_BACK")));
static U4                  u4_s_dateclk_rtc_elpsd                __attribute__((section(".bss_BACK")));
static U4                  u4_s_dateclk_daycnt_min_val3          __attribute__((section(".bss_BACK")));

/* ----------------------------------------------------------------------------------- */
/* Warning :                                                                           */
/* ----------------------------------------------------------------------------------- */
/* The variables, which are located on section ".bss_BSW", are intialized with zero at */
/* MCAL/startup.                                                                       */
/* ----------------------------------------------------------------------------------- */
static U4                  u4_s_dateclk_gpt_frt                  __attribute__((section(".bss_BACK_BSW")));
static U4                  u4_s_dateclk_ope_run                  __attribute__((section(".bss_BACK_BSW")));

static U4                  u4_s_dateclk_adj_yymmddwk;
static U4                  u4_s_dateclk_adj_daycnt;
static U4                  u4_s_dateclk_adj_hhmmss_24h;

static U2                  u2_s_dateclk_swot_elpsd;
static U2                  u2_sp_dateclk_adjtocnt[DATE_CLK_ADJ_NUM_TOUT];
static U1                  u1_s_dateclk_adj_rqbit;

static U1                  u1_s_dateclk_yymmdd_commit;
static U1                  u1_s_dateclk_bon_state;


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_DATE_CLK_BK_UPDT      st_sp_DATE_CLK_BK_UPDT[] = {
    {(U1)DATE_CLK_BACK_1ST,  (U1)U1_MAX,             (U1)U1_MAX           },  /* 000  (1st == 2nd) & (2nd == 3rd) & (3rd == 4th) */
    {(U1)DATE_CLK_BACK_2ND,  (U1)DATE_CLK_BACK_1ST,  (U1)DATE_CLK_BACK_1ST},  /* 001  (1st != 2nd) & (2nd == 3rd) & (3rd == 4th) */
    {(U1)DATE_CLK_BACK_1ST,  (U1)DATE_CLK_BACK_3RD,  (U1)DATE_CLK_BACK_4TH},  /* 010  (1st == 2nd) & (2nd != 3rd) & (3rd == 4th) */
    {(U1)DATE_CLK_BACK_3RD,  (U1)DATE_CLK_BACK_1ST,  (U1)DATE_CLK_BACK_2ND},  /* 011  (1st != 2nd) & (2nd != 3rd) & (3rd == 4th) */
    {(U1)DATE_CLK_BACK_1ST,  (U1)DATE_CLK_BACK_4TH,  (U1)DATE_CLK_BACK_4TH},  /* 100  (1st == 2nd) & (2nd == 3rd) & (3rd != 4th) */
    {(U1)DATE_CLK_BACK_2ND,  (U1)DATE_CLK_BACK_1ST,  (U1)DATE_CLK_BACK_4TH},  /* 101  (1st != 2nd) & (2nd == 3rd) & (3rd != 4th) */
    {(U1)DATE_CLK_BACK_1ST,  (U1)DATE_CLK_BACK_3RD,  (U1)DATE_CLK_BACK_4TH},  /* 110  (1st == 2nd) & (2nd != 3rd) & (3rd != 4th) */
    {(U1)U1_MAX,             (U1)DATE_CLK_BACK_1ST,  (U1)DATE_CLK_BACK_4TH}   /* 111  (1st != 2nd) & (2nd != 3rd) & (3rd != 4th) */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U2                       u2_s_DATE_CLK_FRTSYN_TOUT = (U2)2100U / (U2)DATE_CLK_MAIN_TICK;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_DateclkRtcInit(ST_DATE_CLK_LOG * st_ap_log);
static void    vd_s_DateclkAdjInit(const ST_DATE_CLK_LOG * st_ap_LOG);
static void    vd_s_DateclkSyncUpdt(ST_DATE_CLK_LOG * st_ap_log, const U1 u1_a_ADJ);
static U1      u1_s_DateclkBackLast(ST_DATE_CLK_LOG * st_ap_log);
static void    vd_s_DateclkBackUpdt(const U1 u1_a_BEGIN, const U1 u1_a_END, const ST_DATE_CLK_LOG * st_ap_LOG);
static U4      u4_s_DateclkSecElpsd(const U4 u4_a_LAST, const U4 u4_a_NEXT);
static U4      u4_s_DateclkSyncFrt(const U4 u4_a_SEC_ELPSD, const U1 u1_a_RTC_STA);
static void    vd_s_DateclkEtmUpdt(const U4 u4_a_FRT);

static void    vd_s_DateclkAdjUpdt(const ST_DATE_CLK_LOG * st_ap_LOG);
static void    vd_s_DateclkSWOTchk(const ST_DATE_CLK_LOG * st_ap_LOG);

static U4      u4_s_DateclkDayIncrmnt(const U4 u4_a_HHMMSS_LATEST, const U4 u4_a_HHMMSS_NEXT);

static inline void    vd_s_DateclkSyncHhmmssUpdt(const U1 u1_a_ACT, ST_DATE_CLK_LOG * st_ap_log);
static inline void    vd_s_DateclkSyncDaycntUpdt(const U1 u1_a_ACT, ST_DATE_CLK_LOG * st_ap_log);

static void    vd_s_DateclkSetDayCntMinVal(const U4 u4_a_VAL);
static U4      u4_s_DateclkGetDayCntMinVal(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_g_DateclkTmrwkRqst(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
#if 0
U1      u1_g_DateclkTmrwkRqst(void)
{
    U4                          u4_t_rtcwk;
    U1                          u1_t_rqst;

    u4_t_rtcwk = u4_g_DateclkIfRtcwk();
    if(u4_t_rtcwk != (U4)0U){
        u1_t_rqst = (U1)TRUE;
    }
    else{
        u1_t_rqst = (U1)FALSE;
    }

    return(u1_t_rqst);
}
#endif
/*===================================================================================================================================*/
/*  void    vd_g_DateclkTmrwkInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DateclkTmrwkInit(void)
{
    ST_DATE_CLK_LOG             st_t_log;
    U4                          u4_t_tout;
    U4                          u4_t_frt;
    U4                          u4_t_daycntmin;

    u4_t_tout = u4_s_dateclk_tmrwk_tout;
    u4_t_frt  = u4_gp_dateclk_etm_frt[DATE_CLK_ETM_CH_TMRWK];

    /* Only vd_g_DateclkTmrwkInit, get the day count minimum value from the redundant RAM. */
    u4_t_daycntmin = u4_s_DateclkGetDayCntMinVal();
    vd_s_DateclkSetDayCntMinVal(u4_t_daycntmin);
    if((u4_t_tout >  (U4)DATE_CLK_ETM_MAX) ||
       (u4_t_frt  <= (U4)DATE_CLK_FRT_MAX)){

        st_t_log.u4_hhmmss_bfr = (U4)HHMMSS_UNKNWN;
        st_t_log.u4_daycnt_bfr = (U4)YYMMDDWK_DAYCNT_UNKNWN;
        st_t_log.u4_hhmmss_aft = (U4)HHMMSS_UNKNWN;
        st_t_log.u4_daycnt_aft = (U4)YYMMDDWK_DAYCNT_UNKNWN;
        st_t_log.u4_sec_elpsd  = (U4)0U;
        st_t_log.u1_rtc_rea    = (U1)DATE_CLK_LOG_IF_RTC_UNK;
        st_t_log.u1_rtc_sta    = (U1)DATE_CLK_LOG_IF_RTC_UNK;
        st_t_log.u1_eas_chk    = (U1)0U;
        st_t_log.u1_callpt     = (U1)DATE_CLK_LOG_CP_TMR;

        vd_s_DateclkSyncUpdt(&st_t_log, (U1)0U);

        u4_t_frt = u4_s_DateclkSyncFrt(st_t_log.u4_sec_elpsd, st_t_log.u1_rtc_sta);
        vd_s_DateclkEtmUpdt(u4_t_frt);

        if(st_t_log.u1_eas_chk != (U1)0U){
            vd_g_DateclkCfgLogCapt(&st_t_log, (U1)0U);
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_DateclkBonInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DateclkBonInit(void)
{
    ST_DATE_CLK_LOG             st_t_log;
    U4                          u4_t_daycntmin;

    u1_s_dateclk_yymmdd_commit = (U1)FALSE;
    u1_s_dateclk_bon_state     = (U1)TRUE;

    st_t_log.u4_hhmmss_bfr = (U4)HHMMSS_UNKNWN;
    st_t_log.u4_daycnt_bfr = (U4)YYMMDDWK_DAYCNT_UNKNWN;
    st_t_log.u4_hhmmss_aft = u4_g_DateclkCfgHhmmss24hInit();
    st_t_log.u4_daycnt_aft = u4_g_DateclkCfgDaycntInit();
    st_t_log.u4_sec_elpsd  = (U4)0U;
    st_t_log.u1_rtc_rea    = (U1)DATE_CLK_LOG_IF_RTC_UNK;
    st_t_log.u1_rtc_sta    = (U1)DATE_CLK_LOG_IF_RTC_UNK;
    st_t_log.u1_eas_chk    = (U1)0U;
    st_t_log.u1_callpt     = (U1)DATE_CLK_LOG_CP_BON;

    u4_s_dateclk_tmrwk_tout   = u4_g_DateclkCfgTmrwkTimout();
    s2_s_dateclk_calsubsecond = s2_g_DateclkCfgCalSubsecond();

    vd_s_DateclkRtcInit(&st_t_log);
    vd_s_DateclkAdjInit(&st_t_log);

    u4_s_dateclk_ope_run = (U4)DATE_CLK_OPE_RUN;

    u4_t_daycntmin = u4_g_DateclkCfgDayCntMinValJdg();
    vd_s_DateclkSetDayCntMinVal(u4_t_daycntmin);

    if(st_t_log.u1_rtc_sta != (U1)DATE_CLK_IF_RTC_RUN){
        vd_g_DateclkCfgLogCapt(&st_t_log, (U1)0U);
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_DateclkRstwkInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DateclkRstwkInit(void)
{
    ST_DATE_CLK_LOG             st_t_log;
    U4                          u4_t_tout;
    U4                          u4_t_frt;
    U4                          u4_t_daycntmin;

    u1_s_dateclk_yymmdd_commit = (U1)FALSE;
    u1_s_dateclk_bon_state     = (U1)FALSE;

    st_t_log.u4_hhmmss_bfr = (U4)HHMMSS_UNKNWN;
    st_t_log.u4_daycnt_bfr = (U4)YYMMDDWK_DAYCNT_UNKNWN;
    st_t_log.u4_hhmmss_aft = u4_g_DateclkCfgHhmmss24hInit();
    st_t_log.u4_daycnt_aft = u4_g_DateclkCfgDaycntInit();
    st_t_log.u4_sec_elpsd  = (U4)0U;
    st_t_log.u1_rtc_rea    = (U1)DATE_CLK_LOG_IF_RTC_UNK;
    st_t_log.u1_rtc_sta    = (U1)DATE_CLK_LOG_IF_RTC_UNK;
    st_t_log.u1_eas_chk    = (U1)0U;
    st_t_log.u1_callpt     = (U1)DATE_CLK_LOG_CP_RST;

    u4_t_daycntmin = u4_g_DateclkCfgDayCntMinValJdg();
    vd_s_DateclkSetDayCntMinVal(u4_t_daycntmin);

    u4_t_tout                 = u4_g_DateclkCfgTmrwkTimout();
    u4_s_dateclk_tmrwk_tout   = u4_t_tout;
    s2_s_dateclk_calsubsecond = s2_g_DateclkCfgCalSubsecond();

    u4_t_frt = u4_gp_dateclk_etm_frt[DATE_CLK_ETM_CH_TMRWK];
    if((u4_t_tout >  (U4)DATE_CLK_ETM_MAX) ||
       (u4_t_frt  <= (U4)DATE_CLK_FRT_MAX)){

#if (__DATE_CLK_IF_RTC_WK_BY_IRQ__ == 1U)
        vd_g_DateclkIfRtcwkDI();
#endif /* #if (__DATE_CLK_IF_RTC_WK_BY_IRQ__ == 1U) */

        st_sp_dateclk_back[DATE_CLK_BACK_INI].u4_hhmmss_24h = st_t_log.u4_hhmmss_aft;
        st_sp_dateclk_back[DATE_CLK_BACK_INI].u4_daycnt     = st_t_log.u4_daycnt_aft;

        vd_s_DateclkSyncUpdt(&st_t_log, (U1)0U);

        u4_s_dateclk_gpt_frt = u4_g_DateclkIfGptFrt();
        u4_t_frt = u4_s_DateclkSyncFrt(st_t_log.u4_sec_elpsd, st_t_log.u1_rtc_sta);
        vd_s_DateclkEtmUpdt(u4_t_frt);
    }
    else{

        vd_s_DateclkRtcInit(&st_t_log);
        st_t_log.u1_eas_chk = (U1)DATE_CLK_EAS_TMRWK_DI;
    }

    vd_s_DateclkAdjInit(&st_t_log);

    u4_s_dateclk_ope_run = (U4)DATE_CLK_OPE_RUN;

    if(st_t_log.u1_eas_chk != (U1)0U){
        vd_g_DateclkCfgLogCapt(&st_t_log, (U1)0U);
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_DateclkImmdShtInit(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DateclkImmdShtInit(void)
{
    /* ----------------------------------------------------------------------------------- */
    /* Warning :                                                                           */
    /* ----------------------------------------------------------------------------------- */
    /* DO NOT CLEAR RTC IRQs IN vd_g_DateclkImmdShtInit if RTC is in RUN and no errror is  */
    /* detected. Otherwise, it might cause unexpected delay in elapsed time count.         */
    /* ----------------------------------------------------------------------------------- */

    ST_DATE_CLK_LOG             st_t_log;
    U4                          u4_t_tout;
    U4                          u4_t_frt;
    U4                          u4_t_daycntmin;

    u4_t_tout = u4_s_dateclk_tmrwk_tout;
    u4_t_frt  = u4_gp_dateclk_etm_frt[DATE_CLK_ETM_CH_TMRWK];

    u4_t_daycntmin = u4_g_DateclkCfgDayCntMinValJdg();
    vd_s_DateclkSetDayCntMinVal(u4_t_daycntmin);

    if((u4_t_tout >  (U4)DATE_CLK_ETM_MAX) ||
       (u4_t_frt  <= (U4)DATE_CLK_FRT_MAX)){

        st_t_log.u4_hhmmss_bfr = (U4)HHMMSS_UNKNWN;
        st_t_log.u4_daycnt_bfr = (U4)YYMMDDWK_DAYCNT_UNKNWN;
        st_t_log.u4_hhmmss_aft = (U4)HHMMSS_UNKNWN;
        st_t_log.u4_daycnt_aft = (U4)YYMMDDWK_DAYCNT_UNKNWN;
        st_t_log.u4_sec_elpsd  = (U4)0U;
        st_t_log.u1_rtc_rea    = (U1)DATE_CLK_LOG_IF_RTC_UNK;
        st_t_log.u1_rtc_sta    = (U1)DATE_CLK_LOG_IF_RTC_UNK;
        st_t_log.u1_eas_chk    = (U1)0U;
        st_t_log.u1_callpt     = (U1)DATE_CLK_LOG_CP_IMM;

        vd_s_DateclkSyncUpdt(&st_t_log, (U1)0U);

        u4_t_frt = u4_s_DateclkSyncFrt(st_t_log.u4_sec_elpsd, st_t_log.u1_rtc_sta);
        vd_s_DateclkEtmUpdt(u4_t_frt);

        if(st_t_log.u1_eas_chk != (U1)0U){
            vd_g_DateclkCfgLogCapt(&st_t_log, (U1)0U);
        }
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_DateclkShtLpmToTmrwk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_DateclkShtLpmToTmrwk(void)
{
    /* ----------------------------------------------------------------------------------- */
    /* Warning :                                                                           */
    /* ----------------------------------------------------------------------------------- */
    /* DO NOT CLEAR RTC IRQs if u4_gp_dateclk_etm_frt[DATE_CLK_ETM_CH_TMRWK] is less     */
    /* than u4_s_dateclk_tmrwk_tout. Otherwise, it might cause unexpected delay in elapsed */
    /* time count.                                                                         */
    /* ----------------------------------------------------------------------------------- */

    U4                          u4_t_tout;
    U4                          u4_t_frt;
    U1                          u1_t_tmrwk;

    u4_t_tout = u4_s_dateclk_tmrwk_tout;
    u4_t_frt  = u4_gp_dateclk_etm_frt[DATE_CLK_ETM_CH_TMRWK];
    if((u4_t_tout >  (U4)DATE_CLK_ETM_MAX) ||
       (u4_t_frt  <= (U4)DATE_CLK_FRT_MAX)){

#if (__DATE_CLK_IF_RTC_WK_BY_IRQ__ == 1U)
        vd_g_DateclkIfRtcwkEI();
#endif /* #if (__DATE_CLK_IF_RTC_WK_BY_IRQ__ == 1U) */

        u1_t_tmrwk = (U1)TRUE;
    }
    else{

//        vd_g_DateclkIfRtcStop();

        u1_t_tmrwk = (U1)FALSE;
    }

    return(u1_t_tmrwk);
}
/*===================================================================================================================================*/
/*  void    vd_g_DateclkMainTask(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DateclkMainTask(void)
{
    ST_DATE_CLK_LOG             st_t_log;
    U4                          u4_t_frt;
    U4                          u4_t_daycntmin;

#if (__DATE_CLK_IF_RTC_WK_BY_IRQ__ == 1U)
    vd_g_DateclkIfRtcwkDI();
#endif /* #if (__DATE_CLK_IF_RTC_WK_BY_IRQ__ == 1U) */

    st_t_log.u4_hhmmss_bfr = (U4)HHMMSS_UNKNWN;
    st_t_log.u4_daycnt_bfr = (U4)YYMMDDWK_DAYCNT_UNKNWN;
    st_t_log.u4_hhmmss_aft = u4_g_DateclkCfgHhmmss24hInit();
    st_t_log.u4_daycnt_aft = u4_g_DateclkCfgDaycntInit();
    st_t_log.u4_sec_elpsd  = (U4)0U;
    st_t_log.u1_rtc_rea    = (U1)DATE_CLK_LOG_IF_RTC_UNK;
    st_t_log.u1_rtc_sta    = (U1)DATE_CLK_LOG_IF_RTC_UNK;
    st_t_log.u1_eas_chk    = (U1)0U;
    st_t_log.u1_callpt     = (U1)DATE_CLK_LOG_CP_MAI;

    u4_t_daycntmin = u4_g_DateclkCfgDayCntMinValJdg();
    vd_s_DateclkSetDayCntMinVal(u4_t_daycntmin);

    u4_s_dateclk_tmrwk_tout   = u4_g_DateclkCfgTmrwkTimout();
    s2_s_dateclk_calsubsecond = s2_g_DateclkCfgCalSubsecond();

    st_sp_dateclk_back[DATE_CLK_BACK_INI].u4_hhmmss_24h = st_t_log.u4_hhmmss_aft;
    st_sp_dateclk_back[DATE_CLK_BACK_INI].u4_daycnt     = st_t_log.u4_daycnt_aft;

    vd_s_DateclkSyncUpdt(&st_t_log, (U1)0U);

    u4_t_frt = u4_s_DateclkSyncFrt(st_t_log.u4_sec_elpsd, st_t_log.u1_rtc_sta);
    vd_s_DateclkEtmUpdt(u4_t_frt);

    vd_s_DateclkAdjUpdt(&st_t_log);
    vd_s_DateclkSWOTchk(&st_t_log);

    u4_s_dateclk_ope_run = (U4)DATE_CLK_OPE_RUN;

    if(st_t_log.u1_eas_chk != (U1)0U){
        vd_g_DateclkCfgLogCapt(&st_t_log, (U1)0U);
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_DateclkShtdwnOk(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_DateclkShtdwnOk(void)
{
    static const U2             u2_s_DATE_CLK_SWOT_MIN = (U2)900U  / (U2)DATE_CLK_MAIN_TICK;  /*  900 ms */
    static const U2             u2_s_DATE_CLK_SWOT_MAX = (U2)1100U / (U2)DATE_CLK_MAIN_TICK;  /* 1100 ms */

    U4                          u4_t_tout;
    U4                          u4_t_frt;
    U4                          u4_t_rtcwk;
    U1                          u1_t_ok;

    u4_t_tout  = u4_s_dateclk_tmrwk_tout;
    u4_t_frt   = u4_gp_dateclk_etm_frt[DATE_CLK_ETM_CH_TMRWK];
    u4_t_rtcwk = (U4)0; //u4_g_DateclkIfRtcwk();
    if((u4_t_tout <= (U4)DATE_CLK_ETM_MAX) &&
       (u4_t_frt  >  (U4)DATE_CLK_FRT_MAX)){

        u1_t_ok = (U1)TRUE;
    }
    else if((u2_s_dateclk_swot_elpsd >= u2_s_DATE_CLK_SWOT_MIN) &&
            (u2_s_dateclk_swot_elpsd <  u2_s_DATE_CLK_SWOT_MAX)){

        u1_t_ok = (U1)FALSE;
    }
    else if((u4_t_rtcwk                                  != (U4)0U                   ) ||
            (u2_sp_dateclk_adjtocnt[DATE_CLK_ADJ_FRTSYN] <= u2_s_DATE_CLK_FRTSYN_TOUT)){

        u1_t_ok = (U1)FALSE;
    }
    else{

        u1_t_ok = (U1)TRUE;
    }

    return(u1_t_ok);
}
/*===================================================================================================================================*/
/*  U1      u1_g_DateclkHhmmssSWOT(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_DateclkHhmmssSWOT(void)
{
    static const U2             u2_s_DATE_CLK_SWOT_DUTY_HI = (U2)500U / (U2)DATE_CLK_MAIN_TICK; /* 500 ms */
    U1                          u1_t_swot;

    if(u4_s_dateclk_ope_run != (U4)DATE_CLK_OPE_RUN){
        u1_t_swot = (U1)DATE_CLK_HHMMSS_SWOT_LO;
    }
    else if(u2_s_dateclk_swot_elpsd >= u2_s_DATE_CLK_SWOT_DUTY_HI){
        u1_t_swot = (U1)DATE_CLK_HHMMSS_SWOT_LO;
    }
    else{
        u1_t_swot = (U1)DATE_CLK_HHMMSS_SWOT_HI;
    }

    return(u1_t_swot);
}
/*===================================================================================================================================*/
/*  U4      u4_g_DateclkHhmmss24h(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_DateclkHhmmss24h(void)
{
    U4                          u4_t_hhmmss_24h;

    if(u4_s_dateclk_ope_run == (U4)DATE_CLK_OPE_RUN){
        u4_t_hhmmss_24h = u4_s_dateclk_adj_hhmmss_24h;
    }
    else{
        u4_t_hhmmss_24h = (U4)HHMMSS_UNKNWN;
    }

    return(u4_t_hhmmss_24h);
}
/*===================================================================================================================================*/
/*  U4      u4_g_DateclkYymmddwk(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_DateclkYymmddwk(void)
{
    U4                          u4_t_yymmdd;

    if((u4_s_dateclk_ope_run == (U4)DATE_CLK_OPE_RUN) &&
       (u1_s_dateclk_yymmdd_commit == (U1)TRUE)) {

        u4_t_yymmdd = u4_s_dateclk_adj_yymmddwk;
    }
    else{
        u4_t_yymmdd = (U4)YYMMDDWK_UNKNWN;
    }

    return(u4_t_yymmdd);
}
/*===================================================================================================================================*/
/*  void    vd_g_DateclkYymmdd_Initial(const U1 u1_a_initial)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DateclkYymmdd_Commit(const U1 u1_a_state)
{
    u1_s_dateclk_yymmdd_commit = u1_a_state;
}
/*===================================================================================================================================*/
/*  U1      u1_g_DateclkAdjUnLock(const U1 u1_a_ADJ)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_DateclkAdjUnLock(const U1 u1_a_ADJ)
{
    U1                          u1_t_unlock;

    if(u4_s_dateclk_ope_run != (U4)DATE_CLK_OPE_RUN){
        u1_t_unlock                                 = (U1)FALSE;
    }
    else if(u2_sp_dateclk_adjtocnt[DATE_CLK_ADJ_FRTSYN] <= u2_s_DATE_CLK_FRTSYN_TOUT){
        u1_t_unlock                                 = (U1)FALSE;
    }
    else if(u1_a_ADJ == (U1)DATE_CLK_ADJ_HHMMSS){
        u2_sp_dateclk_adjtocnt[DATE_CLK_ADJ_HHMMSS] = (U2)0U;
        u1_t_unlock                                 = (U1)TRUE;
    }
    else if(u1_a_ADJ == (U1)DATE_CLK_ADJ_YYMMDD){
        u2_sp_dateclk_adjtocnt[DATE_CLK_ADJ_YYMMDD] = (U2)0U;
        u1_t_unlock                                 = (U1)TRUE;
    }
    else if(u1_a_ADJ == ((U1)DATE_CLK_ADJ_HHMMSS | (U1)DATE_CLK_ADJ_YYMMDD)){
        u2_sp_dateclk_adjtocnt[DATE_CLK_ADJ_HHMMSS] = (U2)0U;
        u2_sp_dateclk_adjtocnt[DATE_CLK_ADJ_YYMMDD] = (U2)0U;
        u1_t_unlock                                 = (U1)TRUE;
    }
    else{
        u1_t_unlock                                 = (U1)FALSE;
    }

    return(u1_t_unlock);
}
/*===================================================================================================================================*/
/*  void    vd_g_DateclkAdjLock(const U1 u1_a_ADJ)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DateclkAdjLock(const U1 u1_a_ADJ)
{
    if((u4_s_dateclk_ope_run != (U4)DATE_CLK_OPE_RUN                               ) ||
       (u1_a_ADJ             <  (U1)DATE_CLK_ADJ_HHMMSS                            ) ||
       (u1_a_ADJ             >  ((U1)DATE_CLK_ADJ_HHMMSS | (U1)DATE_CLK_ADJ_YYMMDD))){

        /* do nothing */
    }
    else if(u1_a_ADJ == (U1)DATE_CLK_ADJ_HHMMSS){

        u2_sp_dateclk_adjtocnt[DATE_CLK_ADJ_HHMMSS] = (U2)U2_MAX;
        u1_s_dateclk_adj_rqbit      &= (U1)DATE_CLK_ADJ_YYMMDD;
        u4_s_dateclk_adj_hhmmss_24h  = st_sp_dateclk_back[DATE_CLK_BACK_1ST].u4_hhmmss_24h;
    }
    else if(u1_a_ADJ == (U1)DATE_CLK_ADJ_YYMMDD){

        u2_sp_dateclk_adjtocnt[DATE_CLK_ADJ_YYMMDD] = (U2)U2_MAX;
        u1_s_dateclk_adj_rqbit      &= (U1)DATE_CLK_ADJ_HHMMSS;
        u4_s_dateclk_adj_daycnt      = st_sp_dateclk_back[DATE_CLK_BACK_1ST].u4_daycnt;
        u4_s_dateclk_adj_yymmddwk    = u4_g_DaycntToYymmddwk(u4_s_dateclk_adj_daycnt);
    }
    else{

        u2_sp_dateclk_adjtocnt[DATE_CLK_ADJ_HHMMSS] = (U2)U2_MAX;
        u2_sp_dateclk_adjtocnt[DATE_CLK_ADJ_YYMMDD] = (U2)U2_MAX;
        u1_s_dateclk_adj_rqbit       = (U1)0U;
        u4_s_dateclk_adj_hhmmss_24h  = st_sp_dateclk_back[DATE_CLK_BACK_1ST].u4_hhmmss_24h;
        u4_s_dateclk_adj_daycnt      = st_sp_dateclk_back[DATE_CLK_BACK_1ST].u4_daycnt;
        u4_s_dateclk_adj_yymmddwk    = u4_g_DaycntToYymmddwk(u4_s_dateclk_adj_daycnt);
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_DateclkAdjHhmmss24h(const U4 u4_a_HHMMSS_24H)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_DateclkAdjHhmmss24h(const U4 u4_a_HHMMSS_24H)
{
    U1                          u1_t_adj;

    if(u4_s_dateclk_ope_run != (U4)DATE_CLK_OPE_RUN){

        u1_t_adj = (U1)FALSE;
    }
    else if(u2_sp_dateclk_adjtocnt[DATE_CLK_ADJ_HHMMSS] >= u2_g_DATE_CLK_ADJ_TOUT){

        u1_t_adj = (U1)FALSE;
    }
    else{

        u1_t_adj = u1_g_HhmmssFrmtIs24h(u4_a_HHMMSS_24H, vdp_PTR_NA);
        if(u1_t_adj == (U1)TRUE){
            u4_s_dateclk_adj_hhmmss_24h  = u4_a_HHMMSS_24H;
            u1_s_dateclk_adj_rqbit      |= (U1)DATE_CLK_ADJ_HHMMSS;
        }
    }

    return(u1_t_adj);
}
/*===================================================================================================================================*/
/*  U1      u1_g_DateclkAdjYymmdd(const U4 u4_a_YYMMDD)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_DateclkAdjYymmdd(const U4 u4_a_YYMMDD)
{
    U4                          u4_t_daycnt;
    U1                          u1_t_adj;
    U4                          u4_t_daycntmin;

    if(u4_s_dateclk_ope_run != (U4)DATE_CLK_OPE_RUN){

        u1_t_adj = (U1)FALSE;
    }
    else if(u2_sp_dateclk_adjtocnt[DATE_CLK_ADJ_YYMMDD] >= u2_g_DATE_CLK_ADJ_TOUT){

        u1_t_adj = (U1)FALSE;
    }
    else{

        u4_t_daycntmin = u4_s_DateclkGetDayCntMinVal();
        u4_t_daycnt = u4_g_YymmddToDaycnt(u4_a_YYMMDD);
        if((u4_t_daycnt >= u4_t_daycntmin) &&
           (u4_t_daycnt <= u4_g_DATE_CLK_DAYCNT_MAX)){

            u4_s_dateclk_adj_daycnt    = u4_t_daycnt;
            u4_s_dateclk_adj_yymmddwk  = u4_a_YYMMDD & ((U4)U4_MAX ^ (U4)YYMMDDWK_BIT_WK);
            u4_s_dateclk_adj_yymmddwk |= (U4)u1_g_DayOfWeek(u4_t_daycnt);
            u1_s_dateclk_adj_rqbit    |= (U1)DATE_CLK_ADJ_YYMMDD;

            u1_t_adj = (U1)TRUE;
        }
        else{

            u1_t_adj = (U1)FALSE;
        }
    }

    return(u1_t_adj);
}
/*===================================================================================================================================*/
/*  void    vd_g_DateclkSet(void)                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DateclkSet(void)
{
    ST_DATE_CLK_LOG             st_t_log;
    U1                          u1_t_adj;

    if(u4_s_dateclk_ope_run == (U4)DATE_CLK_OPE_RUN){

        u1_t_adj               = u1_s_dateclk_adj_rqbit;
        u1_s_dateclk_adj_rqbit = (U1)0U;

        if((u1_t_adj >= (U1)DATE_CLK_ADJ_HHMMSS                            ) &&
           (u1_t_adj <= ((U1)DATE_CLK_ADJ_YYMMDD | (U1)DATE_CLK_ADJ_HHMMSS))){

            st_t_log.u4_hhmmss_bfr = (U4)HHMMSS_UNKNWN;
            st_t_log.u4_daycnt_bfr = (U4)YYMMDDWK_DAYCNT_UNKNWN;
            st_t_log.u4_hhmmss_aft = (U4)HHMMSS_UNKNWN;
            st_t_log.u4_daycnt_aft = (U4)YYMMDDWK_DAYCNT_UNKNWN;
            st_t_log.u4_sec_elpsd  = (U4)0U;
            st_t_log.u1_rtc_rea    = (U1)DATE_CLK_LOG_IF_RTC_UNK;
            st_t_log.u1_rtc_sta    = (U1)DATE_CLK_LOG_IF_RTC_UNK;
            st_t_log.u1_eas_chk    = (U1)0U;
            st_t_log.u1_callpt     = (U1)DATE_CLK_LOG_CP_SET;

            vd_s_DateclkSyncUpdt(&st_t_log, u1_t_adj);

            if(u1_t_adj == (U1)DATE_CLK_ADJ_HHMMSS){

                st_t_log.u4_hhmmss_aft = u4_s_dateclk_adj_hhmmss_24h;
                st_t_log.u1_rtc_sta    = u1_g_DateclkIfRtcStart(st_t_log.u4_hhmmss_aft, s2_s_dateclk_calsubsecond);
            }
            else if(u1_t_adj == (U1)DATE_CLK_ADJ_YYMMDD){

                st_t_log.u4_daycnt_aft = u4_s_dateclk_adj_daycnt;
            }
            /* if(u1_t_adj == ((U1)DATE_CLK_ADJ_YYMMDD | (U1)DATE_CLK_ADJ_HHMMSS)) */
            else{

                st_t_log.u4_hhmmss_aft = u4_s_dateclk_adj_hhmmss_24h;
                st_t_log.u4_daycnt_aft = u4_s_dateclk_adj_daycnt;
                st_t_log.u1_rtc_sta    = u1_g_DateclkIfRtcStart(st_t_log.u4_hhmmss_aft, s2_s_dateclk_calsubsecond);
            }
            (void)u4_s_DateclkSyncFrt((U4)0U, st_t_log.u1_rtc_sta);
            vd_s_DateclkBackUpdt((U1)DATE_CLK_BACK_1ST, (U1)DATE_CLK_BACK_4TH, &st_t_log);
            vd_s_DateclkSWOTchk(&st_t_log);

            vd_g_DateclkCfgLogCapt(&st_t_log, u1_t_adj);
        }
    }
}
/*===================================================================================================================================*/
/*  U4      u4_g_DateclkFrt(void)                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_DateclkFrt(void)
{
    return(u4_s_DateclkSyncFrt((U4)0U, (U1)DATE_CLK_LOG_IF_RTC_UNK) & (U4)DATE_CLK_FRT_MAX);
}
/*===================================================================================================================================*/
/*  void    vd_g_DateclkEtmStart(const U1 u1_a_ETM_CH, const U4 u4_a_OFFSET)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DateclkEtmStart(const U1 u1_a_ETM_CH, const U4 u4_a_OFFSET)
{
    U4                          u4_t_frt;

    if((u1_a_ETM_CH <  u1_g_DATE_CLK_ETM_NUM_CH) &&
       (u4_a_OFFSET <= (U4)DATE_CLK_ETM_MAX    )){

        u4_t_frt = (u4_s_DateclkSyncFrt((U4)0U, (U1)DATE_CLK_LOG_IF_RTC_UNK) - u4_a_OFFSET) & (U4)DATE_CLK_FRT_MAX;
        u4_gp_dateclk_etm_frt[u1_a_ETM_CH] = u4_t_frt;
    }
}
/*===================================================================================================================================*/
/*  U4      u4_g_DateclkEtmElapsed(const U1 u1_a_ETM_CH)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_DateclkEtmElapsed(const U1 u1_a_ETM_CH)
{
    U4                          u4_t_elpsd;
    U4                          u4_t_frt;

    u4_t_elpsd = (U4)DATE_CLK_ETM_UNK;
    if(u1_a_ETM_CH < u1_g_DATE_CLK_ETM_NUM_CH){

        u4_t_frt = u4_gp_dateclk_etm_frt[u1_a_ETM_CH];
        if(u4_t_frt <= (U4)DATE_CLK_FRT_MAX){

            /* Intentional wrap-around */
            u4_t_frt = (u4_s_DateclkSyncFrt((U4)0U, (U1)DATE_CLK_LOG_IF_RTC_UNK) - u4_t_frt) & (U4)DATE_CLK_FRT_MAX;
            if(u4_t_frt > (U4)DATE_CLK_ETM_MAX){
                u4_gp_dateclk_etm_frt[u1_a_ETM_CH] = (U4)DATE_CLK_FRT_UNK;
            }
            else{
                u4_t_elpsd = u4_t_frt;
            }
        }
    }

    return(u4_t_elpsd);
}
/*===================================================================================================================================*/
/*  U1      u1_g_DateclkRtcSts(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_DateclkRtcSts(void)
{
    return((U1)TRUE);
}
/*===================================================================================================================================*/
/*  static void    vd_s_DateclkRtcInit(ST_DATE_CLK_LOG * st_ap_log)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_DateclkRtcInit(ST_DATE_CLK_LOG * st_ap_log)
{
 /* st_sp_dateclk_back[DATE_CLK_BACK_INI].u4_hhmmss_24h = st_t_log.u4_hhmmss_aft; */
 /* st_sp_dateclk_back[DATE_CLK_BACK_INI].u4_daycnt     = st_t_log.u4_daycnt_aft; */
    vd_s_DateclkBackUpdt((U1)DATE_CLK_BACK_INI, (U1)DATE_CLK_BACK_4TH, st_ap_log);

    u4_s_dateclk_frt_elpsd = (U4)0U;
    u4_s_dateclk_rtc_elpsd = (U4)0U;

    st_ap_log->u1_rtc_sta  = u1_g_DateclkIfRtcStart(st_ap_log->u4_hhmmss_aft, s2_s_dateclk_calsubsecond);
    u4_s_dateclk_gpt_frt   = u4_g_DateclkIfGptFrt();

    vd_s_DateclkEtmUpdt((U4)DATE_CLK_FRT_UNK);
}
/*===================================================================================================================================*/
/*  static void    vd_s_DateclkAdjInit(const ST_DATE_CLK_LOG * st_ap_LOG)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_DateclkAdjInit(const ST_DATE_CLK_LOG * st_ap_LOG)
{
    u4_s_dateclk_adj_hhmmss_24h = st_ap_LOG->u4_hhmmss_aft;
    u4_s_dateclk_adj_daycnt     = st_ap_LOG->u4_daycnt_aft;
    u4_s_dateclk_adj_yymmddwk   = u4_g_DaycntToYymmddwk(st_ap_LOG->u4_daycnt_aft);

    u2_s_dateclk_swot_elpsd     = (U2)U2_MAX;

    u2_sp_dateclk_adjtocnt[DATE_CLK_ADJ_FRTSYN] = (U2)0U;
    u2_sp_dateclk_adjtocnt[DATE_CLK_ADJ_HHMMSS] = (U2)U2_MAX;
    u2_sp_dateclk_adjtocnt[DATE_CLK_ADJ_YYMMDD] = (U2)U2_MAX;
    u1_s_dateclk_adj_rqbit                      = (U1)0U;
}
/*===================================================================================================================================*/
/*  static void    vd_s_DateclkSyncUpdt(ST_DATE_CLK_LOG * st_ap_log, const U1 u1_a_ADJ)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_DateclkSyncUpdt(ST_DATE_CLK_LOG * st_ap_log, const U1 u1_a_ADJ)
{
    static const U1             u1_sp_DATE_CLK_SYNC_ACT[] = {
        (U1)0x01U, (U1)0x05U, (U1)0x09U, (U1)0x09U, (U1)0x16U, (U1)0x27U, (U1)0x1BU, (U1)0x2BU,
        (U1)0x16U, (U1)0x2BU, (U1)0x1BU, (U1)0x2BU, (U1)0x2BU, (U1)0x2BU, (U1)0x2BU, (U1)0x2BU
    };

    const ST_DATE_CLK_BK_UPDT * st_tp_BU;

    U1                          u1_t_bl_chk;
    U1                          u1_t_er_chk;
    U1                          u1_t_frmt;
    U1                          u1_t_act;
    U1                          u1_t_bit;
    U4                          u4_t_daycntmin;

    u1_t_bl_chk = u1_s_DateclkBackLast(st_ap_log);

    u1_t_er_chk = (U1)0U;
    u1_t_frmt   = u1_g_HhmmssFrmtIs24h(st_ap_log->u4_hhmmss_bfr, vdp_PTR_NA);
    if(u1_t_frmt != (U1)TRUE){
        u1_t_er_chk |= (U1)DATE_CLK_EAS_HHMMSS_BUE;
    }

    u4_t_daycntmin = u4_s_DateclkGetDayCntMinVal();
    if((st_ap_log->u4_daycnt_bfr < u4_t_daycntmin) ||
       (st_ap_log->u4_daycnt_bfr > u4_g_DATE_CLK_DAYCNT_MAX)){

        u1_t_er_chk |= (U1)DATE_CLK_EAS_DAYCNT_BUE;
    }

    st_ap_log->u1_rtc_rea = u1_g_DateclkIfRtcRead(s2_s_dateclk_calsubsecond, &(st_ap_log->u4_hhmmss_aft));
    if(st_ap_log->u1_rtc_rea != (U1)DATE_CLK_IF_RTC_RUN){

        u1_t_er_chk |= (U1)DATE_CLK_EAS_RTC_TC_UNE;
    }
    else if(u1_t_frmt == (U1)TRUE){

        st_ap_log->u4_sec_elpsd = u4_s_DateclkSecElpsd(st_ap_log->u4_hhmmss_bfr, st_ap_log->u4_hhmmss_aft);
        if(st_ap_log->u4_sec_elpsd > u4_g_DATE_CLK_RTC_SYNC_MAX){

            u1_t_er_chk |= (U1)DATE_CLK_EAS_RTC_BU_NSE;
        }
    }
    else{
        /* do nothing */
    }
    st_ap_log->u1_eas_chk = u1_t_bl_chk | u1_t_er_chk;
    u1_t_act              = u1_sp_DATE_CLK_SYNC_ACT[u1_t_er_chk];

    vd_s_DateclkSyncHhmmssUpdt(u1_t_act, st_ap_log);
    vd_s_DateclkSyncDaycntUpdt(u1_t_act, st_ap_log);

    u1_t_bit = u1_t_act & (U1)DATE_CLK_SYNC_ACT_BU_FULL;
    if(u1_a_ADJ != (U1)0U){
        /* do nothing */
    }
    else if(u1_t_bit != (U1)0U){
        vd_s_DateclkBackUpdt((U1)DATE_CLK_BACK_1ST, (U1)DATE_CLK_BACK_4TH, st_ap_log);
    }
    else{
        u1_t_bl_chk >>= DATE_CLK_EAS_LSB_BC;
        st_tp_BU      = &st_sp_DATE_CLK_BK_UPDT[u1_t_bl_chk];
        vd_s_DateclkBackUpdt(st_tp_BU->u1_begin, st_tp_BU->u1_end, st_ap_log);
    }

#if (DATE_CLK_SYNC_ACT_RTC_RES == DATE_CLK_ADJ_HHMMSS)
#error "date_clk.c : DATE_CLK_ADJ_HHMMSS shall NOT be equal to DATE_CLK_SYNC_ACT_RTC_RES."
#endif /* #if (DATE_CLK_SYNC_ACT_RTC_RES == DATE_CLK_ADJ_HHMMSS) */
    u1_t_bit = (u1_t_act & (U1)DATE_CLK_SYNC_ACT_RTC_RES) | (u1_a_ADJ & (U1)DATE_CLK_ADJ_HHMMSS);
    if(u1_t_bit == (U1)DATE_CLK_SYNC_ACT_RTC_RES){
        st_ap_log->u1_rtc_sta = u1_g_DateclkIfRtcStart(st_ap_log->u4_hhmmss_aft, s2_s_dateclk_calsubsecond);
    }
}
/*===================================================================================================================================*/
/*  static U1      u1_s_DateclkBackLast(ST_DATE_CLK_LOG * st_ap_log)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_DateclkBackLast(ST_DATE_CLK_LOG * st_ap_log)
{
    ST_DATE_CLK_BK *            st_tp_1st;
    ST_DATE_CLK_BK *            st_tp_2nd;
    U4                          u4_t_lpcnt;
    U1                          u1_t_chk;
    U1                          u1_t_bit;
    U1                          u1_t_last;
    U1                          u1_t_bon;

    u1_t_chk = (U1)0U;
    u1_t_bit = (U1)DATE_CLK_EAS_BC_1_NE_2;
    u1_t_bon = u1_s_dateclk_bon_state;

    st_tp_1st = &st_sp_dateclk_back[DATE_CLK_BACK_1ST];
    st_tp_2nd = &st_sp_dateclk_back[DATE_CLK_BACK_2ND];
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)DATE_CLK_BACK_NUM_CMPR; u4_t_lpcnt++){
        if ((u1_t_bon                   == (U1)TRUE) &&
            (u1_s_dateclk_yymmdd_commit == (U1)TRUE)) {
            u1_t_chk |= u1_t_bit;
            u1_s_dateclk_bon_state = (U1)FALSE;
        }
        else if((st_tp_1st[u4_t_lpcnt].u4_hhmmss_24h != st_tp_2nd[u4_t_lpcnt].u4_hhmmss_24h) ||
                (st_tp_1st[u4_t_lpcnt].u4_daycnt     != st_tp_2nd[u4_t_lpcnt].u4_daycnt    )){
            u1_t_chk |= u1_t_bit; 
        }
        else {
            /* do nothing */
        }
        u1_t_bit <<= 1U;
    }

    u1_t_last = u1_t_chk >> DATE_CLK_EAS_LSB_BC;
    u1_t_last = st_sp_DATE_CLK_BK_UPDT[u1_t_last].u1_last;
    if(u1_t_last < (U1)DATE_CLK_NUM_BACK){
        st_ap_log->u4_hhmmss_bfr = st_sp_dateclk_back[u1_t_last].u4_hhmmss_24h;
        st_ap_log->u4_daycnt_bfr = st_sp_dateclk_back[u1_t_last].u4_daycnt;
    }

    return(u1_t_chk);
}
/*===================================================================================================================================*/
/*  static void    vd_s_DateclkBackUpdt(const U1 u1_a_BEGIN, const U1 u1_a_END, const ST_DATE_CLK_LOG * st_ap_LOG)                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_DateclkBackUpdt(const U1 u1_a_BEGIN, const U1 u1_a_END, const ST_DATE_CLK_LOG * st_ap_LOG)
{
    volatile U4                 u4_t_dummy_rdbk;
    U4                          u4_t_lpcnt;

    if((u1_a_BEGIN < (U1)DATE_CLK_NUM_BACK) &&
       (u1_a_END   < (U1)DATE_CLK_NUM_BACK)){

        for(u4_t_lpcnt = (U4)u1_a_BEGIN; u4_t_lpcnt <= (U4)u1_a_END; u4_t_lpcnt++){

            st_sp_dateclk_back[u4_t_lpcnt].u4_hhmmss_24h = st_ap_LOG->u4_hhmmss_aft;
            st_sp_dateclk_back[u4_t_lpcnt].u4_daycnt     = st_ap_LOG->u4_daycnt_aft;

            u4_t_dummy_rdbk = st_sp_dateclk_back[u4_t_lpcnt].u4_hhmmss_24h;
            u4_t_dummy_rdbk = st_sp_dateclk_back[u4_t_lpcnt].u4_daycnt;
        }
    }
}
/*===================================================================================================================================*/
/*  static U4      u4_s_DateclkSecElpsd(const U4 u4_a_LAST, const U4 u4_a_NEXT)                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_DateclkSecElpsd(const U4 u4_a_LAST, const U4 u4_a_NEXT)
{
    U4                          u4_t_sec_last;
    U4                          u4_t_sec_next;
    U4                          u4_t_sec_elpsd;

    u4_t_sec_last = u4_g_HhmmssToSeconds(u4_a_LAST);
    u4_t_sec_next = u4_g_HhmmssToSeconds(u4_a_NEXT);

    if((u4_t_sec_last >= (U4)HHMMSS_24HR_TO_SE) ||
       (u4_t_sec_next >= (U4)HHMMSS_24HR_TO_SE)){
        u4_t_sec_elpsd = (U4)U4_MAX;
    }
    else if(u4_t_sec_last <= u4_t_sec_next){
        u4_t_sec_elpsd = u4_t_sec_next - u4_t_sec_last;
    }
    else{
        u4_t_sec_elpsd = ((U4)HHMMSS_24HR_TO_SE + u4_t_sec_next) - u4_t_sec_last;
    }

    return(u4_t_sec_elpsd);
}
/*===================================================================================================================================*/
/*  static void    vd_s_DateclkAdjUpdt(const ST_DATE_CLK_LOG * st_ap_LOG)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_DateclkAdjUpdt(const ST_DATE_CLK_LOG * st_ap_LOG)
{
    U4                          u4_t_lpcnt;
    U1                          u1_t_rqbit;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)DATE_CLK_ADJ_NUM_TOUT; u4_t_lpcnt++){
        if(u2_sp_dateclk_adjtocnt[u4_t_lpcnt] < (U2)U2_MAX){
            u2_sp_dateclk_adjtocnt[u4_t_lpcnt]++;
        }
    }

    if(u2_sp_dateclk_adjtocnt[DATE_CLK_ADJ_HHMMSS] >= u2_g_DATE_CLK_ADJ_TOUT){
        u4_s_dateclk_adj_hhmmss_24h = st_ap_LOG->u4_hhmmss_aft;
        u1_t_rqbit                  = (U1)0U;
    }
    else{
        u1_t_rqbit                  = (U1)DATE_CLK_ADJ_HHMMSS;
    }

    if(u2_sp_dateclk_adjtocnt[DATE_CLK_ADJ_YYMMDD] >= u2_g_DATE_CLK_ADJ_TOUT){
        u4_s_dateclk_adj_daycnt     = st_ap_LOG->u4_daycnt_aft;
        u4_s_dateclk_adj_yymmddwk   = u4_g_DaycntToYymmddwk(st_ap_LOG->u4_daycnt_aft);
    }
    else{
        u1_t_rqbit                 |= (U1)DATE_CLK_ADJ_YYMMDD;
    }

    u1_s_dateclk_adj_rqbit &= u1_t_rqbit;
}
/*===================================================================================================================================*/
/*  static U4      u4_s_DateclkDayIncrmnt(const U4 u4_a_HHMMSS_LATEST, const U4 u4_a_HHMMSS_NEXT)                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_DateclkDayIncrmnt(const U4 u4_a_HHMMSS_LATEST, const U4 u4_a_HHMMSS_NEXT)
{
    U4                          u4_t_hr_latest;
    U4                          u4_t_hr_next;
    U4                          u4_t_daycnt_next;

    u4_t_hr_latest = (u4_a_HHMMSS_LATEST & (U4)HHMMSS_BIT_HR) >> HHMMSS_LSB_HR;
    u4_t_hr_next   = (u4_a_HHMMSS_NEXT   & (U4)HHMMSS_BIT_HR) >> HHMMSS_LSB_HR;

    if(u4_t_hr_next < u4_t_hr_latest){
        u4_t_daycnt_next = (U4)1U;
    }
    else{
        u4_t_daycnt_next = (U4)0U;
    }

    return(u4_t_daycnt_next);
}
/*===================================================================================================================================*/
/*  static void    vd_s_DateclkSWOTchk(const ST_DATE_CLK_LOG * st_ap_LOG)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_DateclkSWOTchk(const ST_DATE_CLK_LOG * st_ap_LOG)
{
    if((st_ap_LOG->u1_rtc_sta   == (U1)DATE_CLK_IF_RTC_RUN) ||
       (st_ap_LOG->u4_sec_elpsd >  (U4)0U                 )){

        u2_s_dateclk_swot_elpsd = (U2)0U;
    }
    else if((st_ap_LOG->u1_callpt    == (U1)DATE_CLK_LOG_CP_MAI) &&
            (u2_s_dateclk_swot_elpsd <  (U2)U2_MAX             )){

        u2_s_dateclk_swot_elpsd++;
    }
    else{
        /* do nothing */
    }
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_DateclkSyncHhmmssUpdt(const U1 u1_a_ACT, ST_DATE_CLK_LOG * st_ap_log)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_DateclkSyncHhmmssUpdt(const U1 u1_a_ACT, ST_DATE_CLK_LOG * st_ap_log)
{
    U4                          u4_t_hhmmss_24h;
    U1                          u1_t_frmt;
    U1                          u1_t_act;

    u1_t_act = u1_a_ACT & (U1)DATE_CLK_SYNC_ACT_BIT_HMS;
    switch(u1_t_act){
        case DATE_CLK_SYNC_ACT_HMS_RTC:
            break;
        case DATE_CLK_SYNC_ACT_HMS_LAS:
            st_ap_log->u4_hhmmss_aft = st_ap_log->u4_hhmmss_bfr;
            break;

     /* case DATE_CLK_SYNC_ACT_HMS_INI: */
        default:
            u4_t_hhmmss_24h = st_sp_dateclk_back[DATE_CLK_BACK_INI].u4_hhmmss_24h;
            u1_t_frmt = u1_g_HhmmssFrmtIs24h(u4_t_hhmmss_24h, vdp_PTR_NA);
            if(u1_t_frmt == (U1)TRUE){
                st_ap_log->u4_hhmmss_aft = u4_t_hhmmss_24h;
            }
            else{
                st_ap_log->u4_hhmmss_aft = (U4)0x00000000U; /* 00:00:00 */
            }
            break;
    }
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_DateclkSyncDaycntUpdt(const U1 u1_a_ACT, ST_DATE_CLK_LOG * st_ap_log)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_DateclkSyncDaycntUpdt(const U1 u1_a_ACT, ST_DATE_CLK_LOG * st_ap_log)
{
    U4                          u4_t_daycnt;
    U1                          u1_t_act;
    U4                          u4_t_daycntmin;

    u1_t_act = u1_a_ACT & (U1)DATE_CLK_SYNC_ACT_BIT_DAYC;
    switch(u1_t_act){
        case DATE_CLK_SYNC_ACT_DAYC_INC:
            st_ap_log->u4_daycnt_aft  = u4_s_DateclkDayIncrmnt(st_ap_log->u4_hhmmss_bfr, st_ap_log->u4_hhmmss_aft);
            if(st_ap_log->u4_daycnt_bfr < u4_g_DATE_CLK_DAYCNT_MAX){
                /* Intentional wrap-around */
                st_ap_log->u4_daycnt_aft += st_ap_log->u4_daycnt_bfr;
            }
            else{
                st_ap_log->u4_daycnt_aft  = u4_g_DATE_CLK_DAYCNT_MAX;
            }
            break;
        case DATE_CLK_SYNC_ACT_DAYC_LAS:
            st_ap_log->u4_daycnt_aft = st_ap_log->u4_daycnt_bfr;
            break;
     /* case DATE_CLK_SYNC_ACT_DAYC_INI: */
        default:
            u4_t_daycntmin = u4_s_DateclkGetDayCntMinVal();
            u4_t_daycnt = st_sp_dateclk_back[DATE_CLK_BACK_INI].u4_daycnt;
            if((u4_t_daycnt >= u4_t_daycntmin) &&
               (u4_t_daycnt <= u4_g_DATE_CLK_DAYCNT_MAX)){
                st_ap_log->u4_daycnt_aft = u4_t_daycnt;
            }
            else{
                st_ap_log->u4_daycnt_aft = u4_t_daycntmin;
            }
            break;
    }
}
/*===================================================================================================================================*/
/*  static U4      u4_s_DateclkSyncFrt(const U4 u4_a_SEC_ELPSD, const U1 u1_a_RTC_STA)                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_DateclkSyncFrt(const U4 u4_a_SEC_ELPSD, const U1 u1_a_RTC_STA)
{
    /* ----------------------------------------------------------------------------------- */
    /* Warning :                                                                           */
    /* ----------------------------------------------------------------------------------- */
    /* u4_s_dateclk_gpt_frt and u4_s_dateclk_ope_run shall be intialized with zero at      */
    /* MCAL/startup.                                                                       */
    /* ----------------------------------------------------------------------------------- */

    static const U4             u4_s_DATE_CLK_FRT_RTC_UNK = ((U4)DATE_CLK_MAIN_TICK * 2U) + (U4)DATE_CLK_ETM_SEC;

    U4                          u4_t_frt_last;
    U4                          u4_t_frt_next;
    U4                          u4_t_frt_max;

    U4                          u4_t_rtc_next;
    U4                          u4_t_rtc_unk;

    U4                          u4_t_gpt_next;
    U4                          u4_t_gpt_elpsd;

    u4_t_frt_last = u4_s_dateclk_frt_elpsd;
    if(u4_s_dateclk_ope_run == (U4)DATE_CLK_OPE_RUN){

        u4_t_gpt_next   = u4_g_DateclkIfGptFrt();
        u4_t_gpt_elpsd  = u4_t_gpt_next - u4_s_dateclk_gpt_frt;
        u4_t_frt_next   = u4_t_gpt_elpsd / (U4)DATE_CLK_GPT_1_MSEC;
        u4_t_gpt_elpsd -= (u4_t_gpt_elpsd % (U4)DATE_CLK_GPT_1_MSEC);

        /* Intentional wrap-around */
        u4_t_frt_next  += u4_t_frt_last;
    }
    else{

        u4_t_gpt_next   = u4_s_dateclk_gpt_frt;
        u4_t_gpt_elpsd  = (U4)0U;
        u4_t_frt_next   = u4_t_frt_last;
    }

    u4_t_rtc_next = u4_s_dateclk_rtc_elpsd;
    if(u1_a_RTC_STA == (U1)DATE_CLK_IF_RTC_RUN){

        /* Intentional wrap-around */
        u4_t_gpt_next = u4_s_dateclk_gpt_frt + u4_t_gpt_elpsd;
        u4_t_rtc_next = u4_t_frt_next & (U4)DATE_CLK_FRT_MAX;
        u4_t_frt_next = u4_t_rtc_next;
    }
    else if(u4_a_SEC_ELPSD == (U4)0U){

        u4_t_gpt_next = u4_s_dateclk_gpt_frt + u4_t_gpt_elpsd;
        u4_t_rtc_unk  = u4_t_rtc_next + u4_s_DATE_CLK_FRT_RTC_UNK;

        /* Intentional wrap-around */
        u4_t_frt_max  = u4_t_rtc_next + (U4)DATE_CLK_ETM_SEC;
        if(u4_t_rtc_next > (U4)DATE_CLK_FRT_MAX){

            u4_t_frt_next &= (U4)DATE_CLK_FRT_MAX;
        }
        else if(u4_t_frt_next >= u4_t_rtc_unk){

            u4_t_frt_next &= (U4)DATE_CLK_FRT_MAX;
            u4_t_rtc_next  = (U4)DATE_CLK_FRT_UNK;
        }
        else if(u4_t_frt_next > u4_t_frt_max){

            u4_t_frt_next  = u4_t_frt_last;
            u4_t_gpt_next  = u4_s_dateclk_gpt_frt;
        }
        else{
            /* do nothing */
        }
    }
    else if(u4_t_rtc_next > (U4)DATE_CLK_FRT_MAX){

        u4_t_gpt_next = u4_s_dateclk_gpt_frt + u4_t_gpt_elpsd;
        u4_t_rtc_next = u4_t_frt_next & (U4)DATE_CLK_FRT_MAX;
        u4_t_frt_next = u4_t_rtc_next;
    }
    else{

     /* u4_t_gpt_next = u4_g_DateclkIfGptFrt() or 0U; */

        /* Intentional wrap-around */
        u4_t_rtc_next += (u4_a_SEC_ELPSD * (U4)DATE_CLK_ETM_SEC);
        if(u4_t_rtc_next >= u4_t_frt_last){

            u4_t_frt_next = u4_t_rtc_next & (U4)DATE_CLK_FRT_MAX;
            u4_t_rtc_next = u4_t_frt_next;
        }
        else{

            u4_t_rtc_next = u4_t_frt_next & (U4)DATE_CLK_FRT_MAX;
            u4_t_frt_next = u4_t_rtc_next;
        }
    }

    u4_s_dateclk_frt_elpsd = u4_t_frt_next;
    u4_s_dateclk_rtc_elpsd = u4_t_rtc_next;
    u4_s_dateclk_gpt_frt   = u4_t_gpt_next;

    return(u4_t_frt_next);
}
/*===================================================================================================================================*/
/*  static void    vd_s_DateclkEtmUpdt(const U4 u4_a_FRT)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_DateclkEtmUpdt(const U4 u4_a_FRT)
{
    U4                          u4_t_ch;
    U4                          u4_t_tout;
    U4                          u4_t_frt;
    U4                          u4_t_elpsd;

    if(u4_a_FRT >= (U4)DATE_CLK_FRT_UNK){

        for(u4_t_ch = (U4)0; u4_t_ch < (U4)u1_g_DATE_CLK_ETM_NUM_CH; u4_t_ch++){
            u4_gp_dateclk_etm_frt[u4_t_ch] = (U4)DATE_CLK_FRT_UNK;
        }
    }
    else{

        u4_t_tout = u4_s_dateclk_tmrwk_tout;
        if(u4_t_tout <= (U4)DATE_CLK_ETM_MAX){

            u4_t_frt   = u4_gp_dateclk_etm_frt[DATE_CLK_ETM_CH_TMRWK];

            /* Intentional wrap-around */
            u4_t_elpsd = (u4_a_FRT - u4_t_frt) & (U4)DATE_CLK_FRT_MAX;
            if((u4_t_frt   <= (U4)DATE_CLK_FRT_MAX) &&
               (u4_t_elpsd >= u4_t_tout           )){

                u4_gp_dateclk_etm_frt[DATE_CLK_ETM_CH_TMRWK] = (U4)DATE_CLK_FRT_UNK;
            }

            u4_t_ch = (U4)1U;
        }
        else{
            u4_t_ch = (U4)0U;
        }

        while(u4_t_ch < (U4)u1_g_DATE_CLK_ETM_NUM_CH){

            u4_t_frt   = u4_gp_dateclk_etm_frt[u4_t_ch];

            /* Intentional wrap-around */
            u4_t_elpsd = (u4_a_FRT - u4_t_frt) & (U4)DATE_CLK_FRT_MAX;
            if((u4_t_frt   <= (U4)DATE_CLK_FRT_MAX) &&
               (u4_t_elpsd >  (U4)DATE_CLK_ETM_MAX)){

                u4_gp_dateclk_etm_frt[u4_t_ch] = (U4)DATE_CLK_FRT_UNK;
            }

            u4_t_ch++;
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_DateclkSetDayCntMinVal(const U4 u4_a_VAL)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_DateclkSetDayCntMinVal(const U4 u4_a_VAL)
{
    u4_s_dateclk_daycnt_min_val1 = u4_a_VAL;
    u4_s_dateclk_daycnt_min_val2 = u4_a_VAL;
    u4_s_dateclk_daycnt_min_val3 = u4_a_VAL;
}
/*===================================================================================================================================*/
/*  static U4    u4_s_DateclkGetDayCntMinVal(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4    u4_s_DateclkGetDayCntMinVal(void)
{
    U4 u4_t_ret;

    U1 u1_t_chk;
    U4 u4_tp_daycnt_min_val[DATE_CLK_DAYCNT_RDN_NUM];
    U4 u4_t_rdnrslt;

    u4_tp_daycnt_min_val[DATE_CLK_DAYCNT_RDN_1ST] = u4_s_dateclk_daycnt_min_val1;
    u4_tp_daycnt_min_val[DATE_CLK_DAYCNT_RDN_2ND] = u4_s_dateclk_daycnt_min_val2;
    u4_tp_daycnt_min_val[DATE_CLK_DAYCNT_RDN_3RD] = u4_s_dateclk_daycnt_min_val3;
    u1_t_chk = u1_g_TrplRdndntchk(u4_tp_daycnt_min_val, &u4_t_rdnrslt);
    if(u1_t_chk == (U1)0U){
        /* Redundant data is all incorrect. */
        u4_t_ret =  u4_g_DATE_CLK_DAYCNT_MIN;
    } else {
        u4_t_ret =  u4_t_rdnrslt;
    }

    return u4_t_ret;
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
/*  1.1.0     9/11/2015  TN       Bug Fix and Optimization.                                                                          */
/*  1.2.0     9/11/2015  TN       Bug Fix : Comparison Times(Loop Count Max) was incorrect in u1_s_DateclkJdgLatest.                 */
/*                                Improvement : vd_g_DateclkImmdShtInit was implemented.                                             */
/*  1.3.0     1/18/2016  TN       Improvement : u1_g_DateclkTmrwkchk was implemented in order to hidden the IRQ clear from users.    */
/*                                vd_g_DateclkTimMeasStart(const U1 u1_a_TIM_CH) ->                                                  */
/*                                        vd_g_DateclkTimMeasStart(const U1 u1_a_TIM_CH, const U4 u4_a_TIM_STA)                      */
/*  1.4.0     6/ 8/2016  TN       Bug Fix : st_sp_dateclk_back[DATE_CLK_BACK_INIT].u4_daycnt was initialized incorrectly in          */
/*                                vd_g_DateclkBonInit.                                                                               */
/*                                Bug Fix : The definitions of DATE_CLK_SYNC_ACT_DAYC_XXX and DATE_CLK_SYNC_ACT_HMS_XXX were         */
/*                                incorrect.                                                                                         */
/*            6/ 9/2016  TN       Potential Bug Fix : RTC migh be stopped unexpectedly                                               */
/*                                only if u4_gp_dateclk_tmelpsd[DATE_CLK_TIM_CH_SHTDWN] was corrupted.                               */
/*            6/13/2016  TN       Improvement : Redundant statements were turn to comment in vd_g_DateclkBonInit.                    */
/*  1.5.0    11/ 7/2016  TN       RtcDrv -> RtcIf.                                                                                   */
/*  1.6.0    11/16/2016  TN       Improvement : st_sp_DATE_CLK_BK_UPDT was modified.                                                 */
/*  1.7.0    11/16/2016  TN       Improvement : vd_s_DateclkSyncTmelpsdUpdt was modified so that u4_gp_dateclk_tmelpsd can be        */
/*                                initialized to DATE_CLK_TMELPSD_UNKNWN if the action is undefined.                                 */
/*  1.8.0    11/18/2016  TN       Improvement : HHMMSS/YYDDMMWK adjustment procedure was re-designed.                                */
/*  1.8.1     4/ 7/2017  TN       Improvement : Literal suffix "UL" was replaced to "U" in order to prevent QAC warnings.            */
/*  1.9.0     6/23/2021  TN       Design Change : u4_s_DateclkSyncFrt was implemented.                                               */
/*  1.10.0    9/ 3/2021  TN       Bug Fix : st_t_log.u1_callpt = (U1)DATE_CLK_LOG_CP_BON; > DATE_CLK_LOG_CP_RST                      */
/*                                in vd_g_DateclkRstwkInit                                                                           */
/*  1.11.0   12/16/2021  TN       Bug Fix : u2_s_dateclk_swot_elpsd was not initialized at vd_g_DateclkSet                           */
/*  1.11.1   11/ 7/2023  KN       Improvement : Warning MISRA-C-Rule7.2 and QAC warning CERT-INT30 was fixed.                        */
/*  1.12.0    8/21/2024  KM       Improvement : u4_g_DATE_CLK_DAYCNT_MIN was cheanged to u4_g_DateclkCfgDayCntMinValJdg.             */
/*  1.12.1   10/28/2024  SY       Improvement : Make u4_s_dateclk_daycnt_min_val# redundant.                                         */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * KN   = Keigo Nomura , Denso Create                                                                                             */
/*  * KM   = Kazuyuki Makino, DENSO                                                                                                  */
/*  * SY   = Satoshi Yamada, DENSO                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
