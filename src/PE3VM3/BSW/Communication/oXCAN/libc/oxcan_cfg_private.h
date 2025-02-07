/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Oem eXtention of CAN                                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef OXCAN_CFG_H
#define OXCAN_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_CFG_H_MAJOR                        (2U)
#define OXCAN_CFG_H_MINOR                        (0U)
#define OXCAN_CFG_H_PATCH                        (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "oxcan.h"                /* BSW_COM_CFG_CHNUM is defined in Com_Cfg.h                    */
                                  /* Com_Cfg.h is included in CS_Can_Cfg.h                        */
                                  /* CS_Can_Cfg.h is included in oxcan.h                          */
#include "oxcan_usrhk.h"
#include "oxcan_lib.h"

/*#include "rim_ctl.h"*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_FATAL_AUB_GIC                      (0x0001U)            /* Global Interrupt Control */
#define OXCAN_FATAL_AUB_COM                      (0x0002U)            /* Aubist/Com               */
#define OXCAN_FATAL_AUB_SEC                      (0x0004U)            /* Aubist/SecOC, Csm        */
/* Aubist/CAN : Register Check and/or CAN Controller Initialization Failure                       */
#define OXCAN_FATAL_AUB_CAN_0                    (0x0100U)            /* CAN Controller 0         */
#define OXCAN_FATAL_AUB_CAN_1                    (0x0200U)            /* CAN Controller 1         */
#define OXCAN_FATAL_AUB_CAN_2                    (0x0400U)            /* CAN Controller 2         */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_oXCANCfgRstInit(void);
void    vd_g_oXCANCfgWkupInit(void);

void    vd_g_oXCANCfgOpemdEvthk(const U4 u4_a_SYSBIT_PREV, const U4 u4_a_SYSBIT_NEXT);

void    vd_g_oXCANCfgPreTask(const U4 u4_a_SYSBIT);
void    vd_g_oXCANCfgPostTask(const U4 u4_a_SYSBIT, const U2 u2_a_FATAL);                  /* u1_a_FATAL : OXCAN_FATAL_AUB_XXX */

void    vd_g_oXCANCfgShutdown(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const U4                 u4_g_OXCAN_WKSRC_CHK;
extern const U1                 u1_gp_OXCAN_CTRLR_BY_CH[BSW_COM_CFG_CHNUM];
extern const U4                 u4_g_OXCAN_SYS_POWER;
extern const U1                 u1_g_OXCAN_TXRX_NUM_ID;
extern const U1                 u1_g_OXCAN_TXRX_NUM_CH;
extern const U2                 u2_gp_OXCAN_PDU_REQ_BY_ID_RIMID[OXCAN_COMCONT_NUM_CH][OXCAN_TXRX_NUM_ID];
extern const U2                 u2_gp_OXCAN_PDU_STAT_BY_CH_RIMID[];
#if (OXCAN_NM_TX_STOP_EN == 1U)
extern const U2                 u2_gp_OXCAN_NM_REQ_BY_ID_RIMID[OXCAN_COMCONT_NUM_CH][OXCAN_TXRX_NUM_ID];
#endif /* #if (OXCAN_NM_TX_STOP_EN == 1U) */

#if ((OXCAN_AUB_E2E_SUP == 1U) && (OXCAN_E2E_NUM_CHECK_MSG != 0U))
extern const U2                 u2_gp_OXCAN_E2E_CHECK_MSG[OXCAN_E2E_NUM_CHECK_MSG];
extern const U4                 u4_g_OXCAN_E2E_NUM_CHECK_MSG;
#endif /* #if ((OXCAN_AUB_E2E_SUP == 1U) && (OXCAN_E2E_NUM_CHECK_MSG != 0U)) */

#if ((OXCAN_AUB_E2E_SUP == 1U) && (OXCAN_E2E_NUM_PROTECT_MSG != 0U))
extern const U2                 u2_gp_OXCAN_E2E_PROTECT_MSG[OXCAN_E2E_NUM_PROTECT_MSG];
extern const U4                 u4_g_OXCAN_E2E_NUM_PROTECT_MSG;
#endif /* #if ((OXCAN_AUB_E2E_SUP == 1U) && (OXCAN_E2E_NUM_PROTECT_MSG != 0U)) */

#endif /* OXCAN_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see  oxcan_cfg.c                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
