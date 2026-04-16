/* 0.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Date clock Synchronization Interface                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef DATESI_TIM_CFG_H
#define DATESI_TIM_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DATESI_TIM_CFG_H_MAJOR                  (0)
#define DATESI_TIM_CFG_H_MINOR                  (1)
#define DATESI_TIM_CFG_H_PATCH                  (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#if 0   /* BEV BSW provisionally */
#include "tydocan_sal.h"
#endif
#include "datesi_tim.h"
#include "rtime.h"
#include "date_clk.h"
#include "ivdsh.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DATESI_TIM_MAIN_TICK                    (20U)
#define DATESI_TIM_SWTIM_SETLONG                (500U / DATESI_TIM_MAIN_TICK)
#define DATESI_TIM_SWTIM_SETLONG_FST            (800U / DATESI_TIM_MAIN_TICK)

#define DATESI_TIM_MIN_TX_NUM                   (5U)
#define DATESI_TIM_CAN_CH                       (0U)
#define DATESI_TIM_NM_STS_RDY_SLP               (NM_STATE_READY_SLEEP)
#define DATESI_TIM_NM_STS_NML_OPE               (NM_STATE_NORMAL_OPERATION)
#define DATESI_TIM_NM_STS_RPT_MSG               (NM_STATE_REPEAT_MESSAGE)
#define DATESI_TIM_NM_STS_UNINIT                (NM_STATE_UNINIT)
#define DATESI_TIM_NM_RET_OK                    (E_OK)

/* Change prohibition parameter */
#define DATESI_TIM_SIGN_CHG                     (-1)

#define TIMEZONE_NUM_RX                         (3U)
#define TIMEZONE_RX_TZ                          (0U)
#define TIMEZONE_RX_TZ_SIGN                     (1U)
#define TIMEZONE_RX_DST_S30                     (2U)

#define DATESI_TIM_DIAG_INFO_NUM                (3U)
#define DATESI_TIM_DIAG_INFO_FAC                (0U)
#define DATESI_TIM_DIAG_INFO_BAC                (1U)
#define DATESI_TIM_DIAG_INFO_NEW                (2U)

#if 0   /* BEV BSW provisionally */
#else
#define OXDC_DID_SSR_SS_NDWORD                  (3U)
#endif

#define DATESI_TIME_VM_1WORD                    (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (DATESI_TIM_DIAG_INFO_NUM > OXDC_DID_SSR_SS_NDWORD)
#error "datesi_tim_cfg_private.h : DATESI_TIM_DIAG_INFO_NUM is greater than OXDC_DID_SSR_SS_NDWORD!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U1  u1p_time[HHMMSS_24H_TIME_SIZE];
    U1  u1_valid;
    U1  u1_act;
}ST_DATESI_TIM_RX;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* U4           u4_g_DateSITimOwnHhmmss24h(void);                                                                                    */
/* void         vd_g_DateSITimOwnAdjUnLock(const U1 u1_a_ADJBIT);                                                                    */
/* void         vd_g_DateSITimOwnAdjLock(const U1 u1_a_ADJBIT);                                                                      */
/* U1           u1_g_DateSITimOwnAdjHhmmss24h(const U4 u4_a_HHMMSS_24H);                                                             */
/* void         vd_g_DateSITimOwnSet(void);                                                                                          */

void            vd_g_DateSITimBonInit(void);
void            vd_g_DateSITimRstWkupInit(void);
void            vd_g_DateSITimMainTask(void);
U1              u1_g_DateSITimAdjustOwnClk(const U4 u4_a_HHMMSS);
void            vd_g_DateSITimSetDispClk(const U4 u4_a_HHMMSS);

void            vd_g_DateSITimAvnBonInit(void);
void            vd_g_DateSITimAvnWkupInit(void);
U1              u1_g_DateSITimMainAvnTask(U4 * u4p_a_offstd_now);
S4              s4_g_DateSITimTotalOffset(void);
U1              u1_g_DateSITimClkRangeCheck(const ST_DATESI_TIM_RX st_a_TIM_RX);
void            vd_g_DateSITimExecTmSet(void);
void            vd_g_DateSITimAvnCanRxHk(void);
U1              u1_g_DateSITimDiagEvCapt(const U1 u1_a_ODO_UPDT, U4 * const u4_ap_ss);
void            vd_g_DateSITimSetAdjStart(void);
void            vd_g_DateSITimSetAdjEnd(void);
void            vd_g_DateSITimAdjustClk(const U1 u1_a_UPDTRNK, const U1 u1_a_VAL, const U1 u1_a_SIGN);
void            vd_g_DateSITimClockUpdate(void);
U4              u4_g_DateSITimMakeHHMMSS(const U1 u1_a_HOUR, const U1 u1_a_MIN, const U1 u1_a_SEC);
U4              u4_g_DateSITimGetAdjSetClk(void);

void            vd_g_DateSITimCfgBonInit(void);
void            vd_g_DateSITimCfgRstWkupInit(void);
U1              u1_g_DateSITimCfgEcuExst(void);
U1              u1_g_DateSITimCfgRxMsgSts(void);
U1              u1_g_DateSITimCfgCanRx(ST_DATESI_TIM_RX * stp_a_rx);
void            vd_g_DateSITimCfgExec24(void);
void            vd_g_DateSITimCfgCanTx(const U4 u4_a_HHMMSS_24H, const U1 u1_a_EVENT_EI);
void            vd_g_DateSITimCfgCanTxOffst(const S4 s4_a_SEC, const U1 u1_a_EVENT_EI);
void            vd_g_DateSITimCfgCanTxHk(void);
U1              u1_g_DateSITimCfgBusSlpOk(void);
U1              u1_g_DateSITimCfgCanRxHk(void);
S4              s4_g_DateSITimCfgBonOfstTime(void);
S4              s4_g_DateSITimCfgWkupOfstTime(void);
U1              u1_g_DateSITimCfgInitOfstTime(S4 * s4p_a_offset_time);
void            vd_g_DateSITimCfgOfstRoutine(void);
void            vd_g_DateSITimCfgOfstAdjStart(void);
S4              s4_g_DateSITimCfgGetOfstTime(void);
void            vd_g_DateSITimCfgSetOfstTime(const S4 s4_a_OFST);
void            vd_g_DateSITimCfgOfstReadHook(void);
void            vd_g_DateSITimCfgOfstDelHook(void);
/* Return : 0 = u1p_a_rx is valid, not 0 = u1p_a_rx is invalid */
U1              u1_g_TimeZoneCfgRxTZ(U1 * u1p_a_rx);       /* {6bit} 00h-30h:Valid, 31h-3Eh:Unuse, 3Fh:Undef,            Resolution:15[min]  */
U1              u1_g_TimeZoneCfgRxTZ_SIGN(U1 * u1p_a_rx);  /* {2bit}     00b:-,         01b:+,     11b:Undef, 10b:Unuse, Resolution:-        */
U1              u1_g_TimeZoneCfgRxDST_S30(U1 * u1p_a_rx);  /* {2bit}     00b:Invalid,   01b:Valid, 11b:Undef, 10b:Unuse, Resolution:-        */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern  const   S4                              s4_g_DATESI_TIM_OFFSET_MIN;
extern  const   S4                              s4_g_DATESI_TIM_OFFSET_MAX;
extern  const   S4                              s4_g_DATESI_TIM_TIMZN_MIN;
extern  const   S4                              s4_g_DATESI_TIM_TIMZN_MAX;

extern  const   U2                              u2_gp_TIMEZONE_RIMID[TIMEZONE_NUM_RX];

#endif      /* DATESI_TIM_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  datesi_tim.c                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
