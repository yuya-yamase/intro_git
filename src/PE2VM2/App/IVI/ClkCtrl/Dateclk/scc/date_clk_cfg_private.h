/* 1.12.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Complex Driver : Date/Clock                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef DATE_CLK_CFG_H
#define DATE_CLK_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DATE_CLK_CFG_H_MAJOR                     (1U)
#define DATE_CLK_CFG_H_MINOR                     (12U)
#define DATE_CLK_CFG_H_PATCH                     (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

//#include "int_drv_wk.h"
#include "RtcIc_drv.h"
#include "gpt_drv_frt.h"

#include "date_clk.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DATE_CLK_MAIN_TICK                       (10U)         /* 10 milliseconds */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DATE_CLK_TMRWK_NO_TOUT                   (DATE_CLK_ETM_UNK)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* ST_DATE_CLK_LOG.u1_eas_chk */
#define DATE_CLK_EAS_HHMMSS_BUE                  (0x01U)  /* backup error/hhmmss is out of range    */
#define DATE_CLK_EAS_DAYCNT_BUE                  (0x02U)  /* backup error/daycnt is out of range    */
#define DATE_CLK_EAS_RTC_TC_UNE                  (0x04U)  /* real time clock time count is unknown  */
#define DATE_CLK_EAS_RTC_BU_NSE                  (0x08U)  /* real time and backup is not sync.      */

#define DATE_CLK_EAS_BC_1_NE_2                   (0x10U)  /* backup compare 1st is not equal to 2nd */
#define DATE_CLK_EAS_BC_2_NE_3                   (0x20U)  /* backup compare 2nd is not equal to 3rd */
#define DATE_CLK_EAS_BC_3_NE_4                   (0x40U)  /* backup compare 3rd is not equal to 4th */
#define DATE_CLK_EAS_LSB_BC                      (4U)

#define DATE_CLK_EAS_TMRWK_DI                    (0x80U)

#define DATE_CLK_EAS_ERR_FIELDS                  (0x0fU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DATE_CLK_LOG_IF_RTC_UNK                  (0xffU)       /* u1_g_DateclkIfRtcRead is not called.  Don't care about it  */
                                                               /* u1_g_DateclkIfRtcStart is not called. Don't care about it  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* ST_DATE_CLK_LOG.u1_callpt */
#define DATE_CLK_LOG_CP_BON                      (0U)          /* vd_g_DateclkBonInit     */
#define DATE_CLK_LOG_CP_RST                      (1U)          /* vd_g_DateclkRstwkInit   */
#define DATE_CLK_LOG_CP_IMM                      (2U)          /* vd_g_DateclkImmdShtInit */
#define DATE_CLK_LOG_CP_TMR                      (3U)          /* vd_g_DateclkTmrwkInit   */
#define DATE_CLK_LOG_CP_MAI                      (4U)          /* vd_g_DateclkMainTask    */
#define DATE_CLK_LOG_CP_SET                      (5U)          /* vd_g_DateclkSet         */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define __DATE_CLK_IF_RTC_WK_BY_IRQ__            (0U)
#if (__DATE_CLK_IF_RTC_WK_BY_IRQ__ == 1U)
#define vd_g_DateclkIfRtcwkEI()
#define vd_g_DateclkIfRtcwkDI()
#endif /* #if (__DATE_CLK_IF_RTC_WK_BY_IRQ__ == 1U) */

#define u4_g_DateclkIfRtcwk()                    (u4_g_IntDrvWkEvt((U4)INT_DRV_WK_CHBIT_15, (U1)TRUE))

#define u1_g_DateclkIfRtcRead(c, tp)             (u1_g_RtclkRead((c), (tp)))
#define u1_g_DateclkIfRtcStart(t, c)             (u1_g_RtclkStart((t), (c), (U1)FALSE))
#define vd_g_DateclkIfRtcStop()                  (vd_g_RtclkDeInit())
#define DATE_CLK_IF_RTC_RUN                      (RTCLK_STSBIT_TMCNT_RUN)

#define u4_g_DateclkIfGptFrt()                   (u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA))
#define DATE_CLK_GPT_1_MSEC                      (10000U)  /* GPT_FRT_1US (10U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U4      u4_hhmmss_bfr;
    U4      u4_daycnt_bfr;

    U4      u4_hhmmss_aft;
    U4      u4_daycnt_aft;

    U4      u4_sec_elpsd;    /* u4_hhmmss_aft - u4_hhmmss_bfr res. : second */

    U1      u1_rtc_rea;      /* Return of u1_g_DateclkIfRtcRead             */
    U1      u1_rtc_sta;      /* Return of u1_g_DateclkIfRtcStart            */
    U1      u1_eas_chk;      /* DATE_CLK_EAS_XXX                            */
    U1      u1_callpt;       /* DATE_CLK_LOG_CP_XXX                         */
}ST_DATE_CLK_LOG;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern U4                  u4_gp_dateclk_etm_frt[];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U4      u4_g_DateclkCfgHhmmss24hInit(void);
U4      u4_g_DateclkCfgDaycntInit(void);
S2      s2_g_DateclkCfgCalSubsecond(void);
U4      u4_g_DateclkCfgTmrwkTimout(void);

void    vd_g_DateclkCfgLogCapt(const ST_DATE_CLK_LOG * st_ap_LOG, const U1 u1_a_ADJ);
U4      u4_g_DateclkCfgDayCntMinValJdg(void);

void    vd_g_DateclkYymmdd_Commit(const U1 u1_a_state);

/* void    vd_g_DateclkIfRtcwkEI(void);                                         */ /* invoked at u1_g_DateclkShtLpmToTmrwk */
/* void    vd_g_DateclkIfRtcwkDI(void);                                         */ /* invoked at u1_g_DateclkShtLpmToTmrwk */
                                                                                   /*        and vd_g_DateclkMainTask      */
/* U4      u4_g_DateclkIfRtcwk(void);                                           */ /* invoked at u1_g_DateclkTmrwkchk      */
/* U1      u1_g_DateclkIfRtcRead(const S2 s2_a_CAL_SUBSE, U4 * u4_ap_hhmmss_24h);     */
/* U1      u1_g_DateclkIfRtcStart(const U4 u4_a_HHMMSS_24H, const S2 s2_a_CAL_SUBSE); */
/* U1      vd_g_DateclkIfRtcStop(void);                                               */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const U4            u4_g_DATE_CLK_DAYCNT_MIN;                             /* [days]          */
extern const U4            u4_g_DATE_CLK_DAYCNT_MAX;                             /* [days]          */

extern const U4            u4_g_DATE_CLK_RTC_SYNC_MAX;                           /* [seconds]       */

extern const U2            u2_g_DATE_CLK_ADJ_TOUT;                               /* [DATE_CLK_TICK] */

extern const U1            u1_g_DATE_CLK_ETM_NUM_CH;

#endif      /* DATE_CLK_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see date_clk.c                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
