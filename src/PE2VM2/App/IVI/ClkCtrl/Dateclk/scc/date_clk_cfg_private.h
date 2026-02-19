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
/* ST_DATE_CLK_LOG.u1_eas_chk */
#define DATE_CLK_EAS_HHMMSS_BUE                  (0x01U)  /* backup error/hhmmss is out of range    */
#define DATE_CLK_EAS_DAYCNT_BUE                  (0x02U)  /* backup error/daycnt is out of range    */
#define DATE_CLK_EAS_RTC_TC_UNE                  (0x04U)  /* real time clock time count is unknown  */
#define DATE_CLK_EAS_RTC_BU_NSE                  (0x08U)  /* real time and backup is not sync.      */

#define DATE_CLK_EAS_BC_1_NE_2                   (0x10U)  /* backup compare 1st is not equal to 2nd */
#define DATE_CLK_EAS_BC_2_NE_3                   (0x20U)  /* backup compare 2nd is not equal to 3rd */
#define DATE_CLK_EAS_BC_3_NE_4                   (0x40U)  /* backup compare 3rd is not equal to 4th */
#define DATE_CLK_EAS_LSB_BC                      (4U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DATE_CLK_LOG_IF_RTC_UNK                  (0xffU)       /* u1_g_DateclkIfRtcRead is not called.  Don't care about it  */
                                                               /* u1_g_DateclkIfRtcStart is not called. Don't care about it  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* ST_DATE_CLK_LOG.u1_callpt */
#define DATE_CLK_LOG_CP_BON                      (0U)          /* vd_g_DateclkBonInit     */
#define DATE_CLK_LOG_CP_RST                      (1U)          /* vd_g_DateclkRstwkInit   */
#define DATE_CLK_LOG_CP_MAI                      (2U)          /* vd_g_DateclkMainTask    */
#define DATE_CLK_LOG_CP_SET                      (3U)          /* vd_g_DateclkSet         */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_g_DateclkIfRtcRead(tp, tc)            (u1_g_RtclkRead((tp), (tc)))
#define u1_g_DateclkIfRtcStart(t, c)             (u1_g_RtclkStart((t), (c)))
#define u1_g_DateclkIfRtcDayset(c)               (u1_g_RtclkDaySet((c)))
#define DATE_CLK_IF_RTC_RUN                      (RTCLK_STSBIT_RTC_RUN)
#define DATE_CLK_IF_I2C_ERR                      (RTCLK_STSBIT_I2C_ERROR)
#define DATE_CLK_IF_TIM_NOREAD                   (RTCLK_STSBIT_TIM_NOREAD)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U4      u4_hhmmss_bfr;
    U4      u4_daycnt_bfr;

    U4      u4_hhmmss_aft;
    U4      u4_daycnt_aft;

    U1      u1_rtc_rea;      /* Return of u1_g_DateclkIfRtcRead             */
    U1      u1_rtc_sta;      /* Return of u1_g_DateclkIfRtcStart            */
    U1      u1_eas_chk;      /* DATE_CLK_EAS_XXX                            */
    U1      u1_callpt;       /* DATE_CLK_LOG_CP_XXX                         */
}ST_DATE_CLK_LOG;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U4      u4_g_DateclkCfgHhmmss24hInit(void);
U4      u4_g_DateclkCfgDaycntInit(void);

void    vd_g_DateclkCfgLogCapt(const ST_DATE_CLK_LOG * st_ap_LOG, const U1 u1_a_ADJ);
U4      u4_g_DateclkCfgDayCntMinValJdg(void);

void    vd_g_DateclkYymmdd_Commit(const U1 u1_a_state);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const U4            u4_g_DATE_CLK_DAYCNT_MIN;                             /* [days]          */
extern const U4            u4_g_DATE_CLK_DAYCNT_MAX;                             /* [days]          */

extern const U2            u2_g_DATE_CLK_ADJ_TOUT;                               /* [DATE_CLK_TICK] */

#endif      /* DATE_CLK_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see date_clk.c                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
