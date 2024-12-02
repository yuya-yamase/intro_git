/* 2.7.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Scheduler                                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef SCHDLR_CFG_H
#define SCHDLR_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SCHDLR_CFG_H_MAJOR (3)
#define SCHDLR_CFG_H_MINOR (0)
#define SCHDLR_CFG_H_PATCH (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include <Std_Types.h>
#if 0
#include "aip_common.h"

#include "int_drv.h"
#include "bsw_m.h"
#include "ecu_m.h"
#include "wdg_m.h"
#include "scheduler.h"
#endif
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if 0
#define __SCHDLR_MAIN_TASK_IMMD_START__ (1)

#define u1_g_SchdlrCfgMainRunnablechk() (u1_g_EcuMStateIsRun())
#define __SCHDLR_CFGHK_NOT_IN_RUN__     (1)
#define vd_g_SchdlrCfgMainNonInRun()    (vd_g_WdgM_MainTask())

#define __SCHDLR_CFGHK_IDLE_START__ (1)
#define vd_g_SchdlrCfgIdleStart()   (vd_g_IntDrvEcuRun())

#define __SCHDLR_CFGHK_IDLE_FINISH__ (1)
#define vd_g_SchdlrCfgIdleFinish()   ((void)u4_g_PLM_DI(u4_g_SCHDLR_IRQ_PREP_SHTDWN))
#define u1_g_SchdlrCfgShtdwnchk()    (u1_g_BswMShtdwnRqst())
#endif
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct
{
    void (*const fp_vd_TASK)(void);
    uint32 u4_taskbit;
} ST_SCHDLR_RGLR;

// typedef void       ( * FP_SCHDLR_IDLE)(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
// void vd_g_SchdlrCfgMainTick(const uint32 u4_a_TRGBIT);

/* U1      u1_g_SchdlrCfgMainRunnablechk(void);      */
/* void    vd_g_SchdlrCfgMainNonInRun(void);         */

// #define __SCHDLR_CFGHK_MAIN_START__ (0)
/* void    vd_g_SchdlrCfgMainStart(void);            */
// #define __SCHDLR_CFGHK_MAIN_FINISH__ (0)
/* void    vd_g_SchdlrCfgMainFinish(void);           */

// #define __SCHDLR_CFGHK_IDLE_TO_RUN__ (1)
// void vd_g_SchdlrCfgIdleToRun(void);

/* void    vd_g_SchdlrCfgIdleStart(void);            */
/* void    vd_g_SchdlrCfgIdleFinish(void);           */
/* U1      u1_g_SchdlrCfgShtdwnchk(void);            */

// #define __SCHDLR_CFGHK_IDLE_TO_SHTDWN__ (0)
/* void    vd_g_SchdlrCfgIdleToShtdwn(void);         */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const uint32 u4_gp_SCHDLR_TASK_CYCL_CFG[];
extern const uint16 u2_g_SCHDLR_TASK_CYCL_START;
extern const uint16 u2_g_SCHDLR_TASK_CYCL_MAX;

extern const ST_SCHDLR_RGLR st_gp_SCHDLR_RGLR_TASK[];
extern const uint16         u2_g_SCHDLR_RGLR_NUM_TASK;

// extern const FP_SCHDLR_IDLE fp_gp_vd_SCHDLR_IDLE_TASK[];
// extern const U2             u2_g_SCHDLR_IDLE_NUM_TASK;

// extern const U4 u4_g_SCHDLR_IRQ_PREP_SHTDWN;

#endif /* #ifndef SCHDLR_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see scheduler.c                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
