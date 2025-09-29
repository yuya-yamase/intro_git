/* 2.5.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Throughput Measure                                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef THROUGHPUT_CFG_H
#define THROUGHPUT_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define THROUGHPUT_CFG_H_MAJOR                   (2)
#define THROUGHPUT_CFG_H_MINOR                   (5)
#define THROUGHPUT_CFG_H_PATCH                   (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "int_drv.h"
#include "throughput.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define THROUGHPUT_ERR_NUM_INFO                  (2U)
#define THROUGHPUT_ERR_STSBIT                    (0U)
#define THROUGHPUT_ERR_OVRHD_MAX                 (1U)

#define THROUGHPUT_ERRBIT_IDEPTH_UNKNWN          (0x00000001U)
#define THROUGHPUT_ERRBIT_IDEPTH_OVF             (0x00000002U)
#define THROUGHPUT_ERRBIT_IDEPTH_UDF             (0x00000004U)
#define THROUGHPUT_ERRBIT_LT_OVRHD               (0x00000008U)
#define THROUGHPUT_ERRBIT_OVRHD_CNT_OVF          (0x00000010U)
#define THROUGHPUT_ERRBIT_GT_OVRHD_CAL           (0x00000020U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define THROUGHPUT_INTRPT_DEPTH                  (96U)                            /* Isr = MAX 64 depth, eMCOS Task = MAX 32 depth   */
#define THROUGHPUT_RSHFT_OVRHD_CAL               (6U)                             /* u2_g_ThroughputCfgCalcOvrhd()                   */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define __THROUGHPUT_INTRPT_DI_BY_CALLER__       (0)
#define u4_g_ThroughputCfg_DI()                  (u4_g_IRQ_DI())
#define vd_g_ThroughputCfg_EI(u4)                (vd_g_IRQ_EI(u4))

#define vd_g_ThroughputCfgToRun                  (vd_g_ThroughputEcuToRun)
#define vd_g_ThroughputCfgMainTask               (vd_g_ThroughputMainTask)
#define vd_g_ThroughputCfgToShtdwn               (vd_g_ThroughputEcuToShtdwn)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern volatile U4               u4_gp_throughput_errlog[]; /* Error Checker */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_ThroughputCfgInit(void);
U2      u2_g_ThroughputCfgMeasOvrhd(void);
U2      u2_g_ThroughputCfgIrqOvrhd(void);
void    vd_g_IntHndlrIRQOvrhdchk(void);

/* U4      u4_g_ThroughputCfgFrt(void);              */
/* U4      u4_g_ThroughputCfg_DI(void);              */
/* void    vd_g_ThroughputCfg_EI(const U4 u4_a_GLI); */

void    vd_g_ThroughputCfgIsrCapt(const U2 u2_a_IRQ_CH, const U4 u4_a_THROUGHPUT);
void    vd_g_ThroughputCfgTaskCapt(const U2 u2_a_TASK_ID, const U4 u4_a_THROUGHPUT);
void    vd_g_ThroughputCfgCscCapt(const U2 u2_a_CSC_ID, const U4 u4_a_THROUGHPUT);

void    vd_g_ThroughputCfg_vd_Fvd_Start(const U2 u2_a_vd_FVD_ID);
void    vd_g_ThroughputCfg_vd_Fvd_Capt(const U2 u2_a_LP_IDX, const U4 u4_a_THROUGHPUT);
void    vd_g_ThroughputCfg_vd_Fvd_Finish(const U2 u2_a_vd_FVD_ID);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif   /* #ifndef THROUGHPUT_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see throughput.c                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
