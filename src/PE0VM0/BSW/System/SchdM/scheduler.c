/* 2.7.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Scheduler                                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SCHDLR_C_MAJOR (3)
#define SCHDLR_C_MINOR (0)
#define SCHDLR_C_PATCH (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <scheduler.h>
#include <scheduler_taskdef.h>
#include "scheduler_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((SCHDLR_C_MAJOR != SCHDLR_H_MAJOR) || \
     (SCHDLR_C_MINOR != SCHDLR_H_MINOR) || \
     (SCHDLR_C_PATCH != SCHDLR_H_PATCH))
#error "scheduler.c and scheduler.h : source and header files are inconsistent!"
#endif

#if ((SCHDLR_C_MAJOR != SCHDLR_CFG_H_MAJOR) || \
     (SCHDLR_C_MINOR != SCHDLR_CFG_H_MINOR) || \
     (SCHDLR_C_PATCH != SCHDLR_CFG_H_PATCH))
#error "scheduler.c and scheduler_cfg_private.h : source and parameter files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SCHDLR_TASKBIT_LSB_TICK             (16U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static uint16 u2_s_schdlr_task_cyclcnt; /* Task counter                  */
static uint32 u4_s_schdlr_task_actvtd;  /* Task Flag executed currentry  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_SchdlrInit(void)                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_SchdlrInit(void)
{
    u2_s_schdlr_task_cyclcnt = u2_g_SCHDLR_TASK_CYCL_START;
}
/*===================================================================================================================================*/
/*  void    vd_g_SchdlrMainTask(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_SchdlrMainTask(void)
{
    uint32 u4_t_exe;
    uint32 u4_t_cnt;
    uint32 u4Dividor;
    uint32 u4Offset;

    if (u2_s_schdlr_task_cyclcnt >= u2_g_SCHDLR_TASK_CYCL_MAX)
    {
        u2_s_schdlr_task_cyclcnt = (uint16)0U; /* Restart from first               */
    }

    u4_s_schdlr_task_actvtd = u4_gp_SCHDLR_TASK_CYCL_CFG[u2_s_schdlr_task_cyclcnt];

    /* ----------------------------------------------------------------------------------- */
    /* Regular Task                                                                        */
    /* ----------------------------------------------------------------------------------- */
    for (u4_t_cnt = (uint32)0U; u4_t_cnt < (uint32)u2_g_SCHDLR_RGLR_NUM_TASK; u4_t_cnt++)
    {

        u4_t_exe = st_gp_SCHDLR_RGLR_TASK[u4_t_cnt].u4_taskbit;
        if (u4_t_exe != (uint32)0U)
        {
            u4Dividor = (u4_t_exe & 0xFFFF0000UL) >> SCHDLR_TASKBIT_LSB_TICK;
            u4Offset  = u4_t_exe & 0x0000FFFFUL;
            if (u2_s_schdlr_task_cyclcnt >= u4Offset)
            {
                if (0UL == (u2_s_schdlr_task_cyclcnt - u4Offset) % u4Dividor)
                {
                    (*st_gp_SCHDLR_RGLR_TASK[u4_t_cnt].fp_vd_TASK)();
                }
            }
        }
    }

    // まず Tick
    u2_s_schdlr_task_cyclcnt++; /* Increment cycle counter          */
}

/*===================================================================================================================================*/
/* uint32      u4_g_SchdlrTaskActivated(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
uint32      u4_g_SchdlrTaskActivated(void)
{
    return(u4_s_schdlr_task_actvtd);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     9/ 5/2014  TN       New                                                                                                */
/*  1.1.0     3/16/2015  TN       "volatile" was added into "u4_s_schdlr_taskbit_trgrd" and u4_s_schdlr_taskbit_exect.               */
/*  1.2.0     3/31/2015  TN       vd_g_SchdlrMainTickIsr -> vd_g_SchdlrMainTick.                                                     */
/*                                vd_g_SchdlrCfgMainTick(u4_t_trgrd) was implemented.                                                */
/*  1.3.0     6/24/2015  TN       Bug Fix : If interrrupt priority level for vd_g_SchdlrMainTickIsr was changed to higher,           */
/*                                RAM sharing issue was caused.                                                                      */
/*  2.0.0    10/ 9/2015  TN       scheduler v1.3.0 -> v2.0.0 : soft/hard-preemtive architectures were supported.                     */
/*  2.1.0    10/14/2015  TN       Optimization : u1_SCHDLR_MAIN_RUNNABLE_CHK, vd_SCHDLR_MAIN_STA_HK and vd_SCHDLR_MAIN_FIN_HK        */
/*                                were implemented.                                                                                  */
/*  2.2.0     1/14/2016  TN       Redundant Function name redirections were delteted.                                                */
/*  2.3.0     1/20/2016  TN       vd_g_SchdlrCfgMainErrhk was implemented.                                                           */
/*  2.4.0     2/ 1/2016  TN       static variables identifiers were redefined.                                                       */
/*                                u4_g_SchdlrTaskbitExect -> u4_g_SchdlrTaskActivated.                                               */
/*                                vd_g_SchdlrCfgIdleStart -> vd_g_SchdlrCfgIdleToRun                                                 */
/*                                vd_g_SchdlrCfgIdleStart was moved into inside of do-while loop.                                    */
/*                                vd_g_SchdlrCfgIdleFinish was implemented.                                                          */
/*                                vd_g_SchdlrCfgIdleToShtdwn was implemented.                                                        */
/*                                vd_g_SchdlrCfgMainStarthk -> vd_g_SchdlrCfgMainStart.                                              */
/*                                vd_g_SchdlrCfgMainFinishhk -> vd_g_SchdlrCfgMainFinish.                                            */
/*                                vd_g_SchdlrCfgMainErrhk -> vd_g_SchdlrCfgMainNonInRun.                                             */
/*                                __SCHDLR_MAIN_STA_HK__ -> __SCHDLR_CFGHK_MAIN_START__.                                             */
/*                                __SCHDLR_MAIN_FIN_HK__ -> __SCHDLR_CFGHK_MAIN_FINISH__.                                            */
/*                                __SCHDLR_CFGHK_NOT_IN_RUN__ was implemented.                                                       */
/*            2/ 3/2016  TN       u1_g_SchdlrCfgShtdwnRqst -> u1_g_SchdlrCfgShtdwnchk.                                               */
/*            2/ 5/2016  TN       debug simulator environment was implemented.                                                       */
/*            2/12/2016  TN       st_sp_SCHDLR_RGLR->u4_exebit -> st_sp_SCHDLR_RGLR->u4_taskbit.                                     */
/*                                u4_s_schdlr_task_exebit      -> u4_s_schdlr_task_exechk.                                           */
/*  2.5.0     9/21/2016  TN       Bug Fix : The execution order of vd_g_SchdlrMainTick and vd_g_SchdlrMainTask was not               */
/*                                appropirate in vd_g_SchdlrIdleTask when __AIP_DEBUG_SIM__ = 1.                                     */
/*  2.6.0     4/10/2017  TN       Bug Fix : A data race issue could be casued because there was super slit in                        */
/*                                vd_g_SchdlrMainTask.                                                                               */
/*  2.6.1     9/ 7/2021  TN       "U" suffix were added into litterals because of MC3 Rule-7.2 compliance.                           */
/*                                NULL->vdp_PTR_NA.                                                                                  */
/*  2.7.0     9/15/2021  TN       u2_g_SCHDLR_IDLE_NUM_TASK was defined because of MISAR-C Rule 18.1.                                */
/*  3.0.0     9/13/2024  MH       Simplified to run on AutosarOS */
/*                                                                                                                                   */
/*  * TN      = Takashi Nagai, Denso                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
