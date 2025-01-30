/* 2.2.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  eXternal Peripheral Device Initialization                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef XPD_INIT_CFG_H
#define XPD_INIT_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XPD_INIT_CFG_H_MAJOR                     (2U)
#define XPD_INIT_CFG_H_MINOR                     (2U)
#define XPD_INIT_CFG_H_PATCH                     (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "int_drv.h"
#include "gpt_drv_frt.h"
#include "ecu_m.h"
#include "mcu_drv.h"
#include "xpd_init.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XPDI_CTRL_NUM_SEQ                        (7U)
#define XPDI_CTRL_SEQ_OFF                        (0U)          /* OFF                      */
#define XPDI_CTRL_SEQ_STA                        (1U)          /* STArt                    */
#define XPDI_CTRL_SEQ_RUN                        (2U)          /* RUN                      */
#define XPDI_CTRL_SEQ_SHU                        (3U)          /* SHUtdown                 */
#define XPDI_CTRL_SEQ_ABO                        (4U)          /* ABOrt                    */
#define XPDI_CTRL_SEQ_RST_OFF                    (5U)          /* RST OFF                  */
#define XPDI_CTRL_SEQ_RST_STA                    (6U)          /* RST STArt                */
#define XPDI_CTRL_SEQ_UNK                        (255U)

/* Xpd Init / Step Timing Control Parameter */
#define XPDI_STEP_TCP_LAP_MIN                    (0x0fffffffU)  /* Lap time Min.           */
#define XPDI_STEP_TCP_SEQ_EXE                    (0x70000000U)  /* Sequence Execution      */
#define XPDI_STEP_TCP_LTM_STA                    (0x80000000U)  /* Lap Time Measure Start  */

#define XPDI_SEQ_EXE_1ST_W_EI                    (0x00000000U)
#define XPDI_SEQ_EXE_2ND_W_DI                    (0x10000000U)
#define XPDI_SEQ_EXE_3RD_W_DI                    (0x20000000U)
#define XPDI_SEQ_EXE_4TH_W_EI                    (0x30000000U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XPDI_ABO_RQST_ACT                        (0x08U)       /* abort request active     */
#define XPDI_ABO_RQST_CNT                        (0x20U)       /* abort counter increment  */
#define XPDI_EVNT_PMIC_ON                        (0x10U)

#define XPDI_WKUP_BY_BATT_ON                     (ECU_M_WKUP_BY_BATT_ON)
#define XPDI_RESET_BY_FIELDS                     (MCU_RESET_BY_FIELDS)
#define XPDI_RESET_BY_EXT                        (MCU_RESET_BY_EXT)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u4_g_XpdiCfg_DI()                        (u4_g_IRQ_DI())
#define vd_g_XpdiCfg_EI(u4)                      (vd_g_IRQ_EI(u4))

#define u4_g_XpdiCfgWkupReason()                 (u4_g_EcuMWkupReason())
#define u4_g_XpdiCfgMcurstReason()               (u4_g_EcuMMcurstReason())

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    void ( * const           fp_vd_STEP)(void);
    U4                       u4_tcpbit;             /* timing control parameter */
}ST_XPDI_STEP;

typedef struct{
    const ST_XPDI_STEP *     stp_STEP;
    U2                       u2_num_step;
}ST_XPDI_SEQ;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_XpdiCfgRstInit(void);
void    vd_g_XpdiCfgWkupInit(void);
void    vd_g_XpdiCfgDeInit(const U1 u1_a_CTRL, const U2 u2_a_STEPCNT);

void    vd_g_XpdiCfgPreTask(const U1 u1_a_CTRL, const U2 u2_a_STEPCNT);
U1      u1_g_XpdiCfgAboRqst(void);                                              /* Return XPDI_ABO_RQST_XXX */
U1      u1_g_XpdinitOtaReqsts(void);
void    vd_g_XpdiCfgPostTask(const U1 u1_a_CTRL, const U2 u2_a_STEPCNT);

U1      u1_g_XpdiCfgPmicOn(void);
void    vd_g_XpdiCfgGdcLoEdge(void);
void    vd_g_XpdiCfgGdcLvdchk(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const U4                    u4_g_XPDI_FRT_TO_LAPTM;

extern const U2                    u2_g_XPDI_SDR_TOUT;         /* Shutdown Request Timeout                  */

extern const U1                    u1_g_XPDI_CTRL_RST;         /* Initial Control State at vd_g_XpdiRstInit */
extern const U1                    u1_g_XPDI_ABO_CNT_MAX;      /* ABort Counter Max                         */

extern const ST_XPDI_SEQ           st_gp_XPDI_SEQ[XPDI_CTRL_NUM_SEQ];

#endif      /* XPD_INIT_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see xpd_init.c                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
