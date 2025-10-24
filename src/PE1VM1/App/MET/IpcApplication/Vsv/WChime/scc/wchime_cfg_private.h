/* 2.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vehicle Status Viewer / Toyota IPC/MET Warning Chime                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef WCHIME_CFG_H
#define WCHIME_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define WCHIME_CFG_H_MAJOR                       (2)
#define WCHIME_CFG_H_MINOR                       (1)
#define WCHIME_CFG_H_PATCH                       (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "memfill_u4.h"
#include "lsbsrch.h"

#include "wchime.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define WCHIME_TICK                              (10U)               /* WChime tick period.                                          */
#define WCHIME_WT_TIM_CMN                        (300U/WCHIME_TICK)  /* Waiting time : 300ms.                                        */

#define WCHIME_APP_BZ_NUM                        (4U)                /* Number of APP buzzer.                                        */

#define WCHIME_REQ_IDX_UPLMT                     (224U)   /* Buzzer request upper limit.                                             */
#define WCHIME_REQBIT_NWORD_MAX                  (7U)     /* Maximum number of rows to convert to buzzer req. ID to bit.             */

#define WCHIME_REQ_SWC_OPEMD                     (0x01U)  /* Request switch can be done based on operational mode.                   */
#define WCHIME_REQ_SWC_WAV_CYCL                  (0x02U)  /* Request switch can be done when wav is cycled.                          */
#define WCHIME_REQ_SWC_PRI_HI                    (0x04U)  /* Request switch can be done when a higher request is active.             */
#define WCHIME_REQ_SWC_PRI_HI_CNCL               (0x08U)  /* Request switch can be done when a higher request is immediately active. */
#define WCHIME_REQ_SWC_SIN_RET                   (0x10U)  /* Single request can be retriggered during the request is selected.       */

#define WCHIME_BUZ_LV0                           (0U)     /* Buzzer priority level 0.                                                */
#define WCHIME_BUZ_LV1                           (1U)     /* Buzzer priority level 1.                                                */
#define WCHIME_BUZ_LV2                           (2U)     /* Buzzer priority level 2.                                                */
#define WCHIME_BUZ_LV3                           (3U)     /* Buzzer priority level 3.                                                */
#define WCHIME_BUZ_LV4                           (4U)     /* Buzzer priority level 4.                                                */
#define WCHIME_BUZ_LV5                           (5U)     /* Buzzer priority level 5.                                                */
#define WCHIME_BUZ_LV6                           (6U)     /* Buzzer priority level 6.                                                */
#define WCHIME_BUZ_LV7                           (7U)     /* Buzzer priority level 7.                                                */
#define WCHIME_BUZ_LV8                           (8U)     /* Buzzer priority level 8.                                                */
#define WCHIME_BUZ_LV9                           (9U)     /* Buzzer priority level 9.                                                */
#define WCHIME_BUZ_LV10                          (0U)     /* Buzzer priority level 10.                                               */

#define WCHIME_BUZ_LONG                          (0U)     /* Buzzer Length Long.                                                     */
#define WCHIME_BUZ_SHORT                         (1U)     /* Buzzer Length Short.                                                    */

#define WCHIME_BUZ_EMOFF                         (0U)     /* Emergency OFF.                                                          */
#define WCHIME_BUZ_EMON                          (1U)     /* Emergency ON.                                                           */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_g_wChimeLsbSrch(v)                    (u1_g_LsbSrch(v))   /* Bit Search Functions.                                        */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{                 /* Structure to keep buzzer request arbitration result by channel.  */
    U2          u2_tmelpsd;     /* Counter to measure the silent duration (Count-up).               */
    U1          u1_arb;         /* The status of arbitration and blowing of buzzer.                 */
    U1          u1_req_vol;     /* Volume kind of selected buzzer request currently.                */
    U1          u1_req_sel;     /* Selected buzzer request currently.                               */
    U1          u1_bfrwait_sel; /* Selected buzzer request before wait time(silent duration).       */
    U1          u1_req_mm;      /* The buzzer request to inform to the multimedia device.           */
}ST_WCHIME_ARB_CH;

typedef struct{                 /* Structure to keep the content to inform to the multimedia device. */
    U1          u1_level;       /* Level of meter buzzer priority.                                   */
    U1          u1_length;      /* Lengh of meter buzzer.                                            */
    U1          u1_emergency;   /* ON/OFF of emergency buzzer.                                       */
}ST_WCHIME_MM_INFO;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern U4                           u4_gp_wchime_reqbit[];
extern U4                           u4_gp_wchime_evtbit[];
extern U4                           u4_gp_wchime_evtmsk[];

extern U2                           u2_gp_wchime_wt_tim[];

extern ST_WCHIME_ARB_CH             st_gp_wchime_arb_ch[];
extern U1                           u1_gp_wchime_cyclchk[];

extern  U1                          u1_g_wchime_alrt_csr_vol_old;
extern  U1                          u1_g_wchime_alrt_csr_vol_now;

extern  U1                          u1_g_wchime_silencetime_flag;
extern  U1                          u1_g_wchime_metcstmvol;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* U1      u1_g_wChimeLsbSrch(const U4 u4_a_VAL);                                         */

void    vd_g_wChimeCfgInit(void);
void    vd_g_wChimeCfgPreTask(void);
void    vd_g_wChimeCfgPostTask(void);

void    vd_g_wChimeReqCfgInit(void);
U1      u1_g_wChimeCfgOpemdchk(void);
void    vd_g_wChimeCfgReqchk(U4 * u4p_a_reqbit);
U1      u1_g_wChimeCfgWavCycled(const U1 u1_a_WC_CH);
U1      u1_g_wChimeCfgReqRead(const U4 * u4_ap_REQBIT, const U1 u1_a_REQ_ID);
U1      u1_g_wChimeReqSwCtrl(const U1 u1_a_REQ_SEL);
U1      u1_g_wChimeCfgSwWaitInsert(const U1 u1_a_REQ_SEL, const U1 u1_a_REQ_NEXT, U2 * u2p_a_wait_time);
U1      u1_g_wChimeCfgVolGet(const U1 u1_a_REQ_SEL);
U1      u1_g_wChimeCfgIntermSplCnd(const U1 u1_a_REQ_SEL, const U1 u1_a_REQ_NEXT);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const U4                     u4_gp_WCHIME_REQBIT_SIN[];
extern const U4                     u4_gp_WCHIME_REQBIT_PRIFREE[];
extern const U1                     u1_g_WCHIME_REQBIT_NUM_WORD;
extern const U1                     u1_g_WCHIME_NUM_REQ;

extern const U4 * const             u4p_gp_WCHIME_REQBIT_BY_OPEMD[];
extern const U1                     u1_g_WCHIME_NUM_OPEMD;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const U4 * const             u4p_gp_WCHIME_REQBIT_BY_CH[];
extern const U1                     u1_g_WCHIME_NUM_CH;
extern const ST_WCHIME_MM_INFO      st_gp_WCHIME_BUZ_OUTPUT_INFO[];

#endif      /* WCHIME_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  wchime_arb.c                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
