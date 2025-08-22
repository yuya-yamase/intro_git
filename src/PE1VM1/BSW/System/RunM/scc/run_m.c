/* 1.12.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  RUN Mode Manager :                                                                                                               */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RUN_M_C_MAJOR                            (1)
#define RUN_M_C_MINOR                            (12)
#define RUN_M_C_PATCH                            (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "run_m_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((RUN_M_C_MAJOR != RUN_M_H_MAJOR) || \
     (RUN_M_C_MINOR != RUN_M_H_MINOR) || \
     (RUN_M_C_PATCH != RUN_M_H_PATCH))
#error "run_m.c and run_m.h : source and header files are inconsistent!"
#endif

#if ((RUN_M_C_MAJOR != RUN_M_CFG_H_MAJOR) || \
     (RUN_M_C_MINOR != RUN_M_CFG_H_MINOR) || \
     (RUN_M_C_PATCH != RUN_M_CFG_H_PATCH))
#error "run_m.c and run_m_cfg_private.h : source and config files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RUN_M_SLP_RQST_NWORD                       (1U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4     u4_s_run_m_shtdwndlycnt;                           /* Shutdown Delay Timer/Counter   */
static U1     u1_s_run_m_shtdwnrqst;

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
/*  void    vd_g_RunMInit(void)                                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_RunMInit(void)
{
    u4_s_run_m_shtdwndlycnt = (U4)U4_MAX;
    u1_s_run_m_shtdwnrqst   = (U1)FALSE;

    vd_g_RunMCfgInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_RunMMainTask(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_RunMMainTask(void)
{
    U1               u1_t_shtdwn_1st;
    U1               u1_t_shtdwn_2nd;
    U4               u4_t_shtdwnrqst_nrml;
    U4               u4_t_shtdwnrqst_frcd;
    
    u4_t_shtdwnrqst_frcd = (U4)FALSE;

    if(u4_s_run_m_shtdwndlycnt > (U4)U2_MAX){
        u4_s_run_m_shtdwndlycnt = (U4)0U;
    }
    else if(u4_s_run_m_shtdwndlycnt >= (U4)u2_g_RUN_M_TIMOUT_TO_SHTDWN){
        u4_s_run_m_shtdwndlycnt = (U4)u2_g_RUN_M_TIMOUT_TO_SHTDWN;
    }
    else{
        u4_s_run_m_shtdwndlycnt++;
    }

    u1_t_shtdwn_1st  = u1_g_RunMCfghkShtdwnchk1st();
    u1_t_shtdwn_1st &= u1_g_RunMCfgWksrcIrqchk();
    vd_g_RunMCfgWksrcCfgRefresh();
    if((u1_t_shtdwn_1st & ((U1)RUN_M_NRML_SLP_CHK_TRUE | (U1)RUN_M_FRCD_SLP_CHK_TRUE)) == (U1)0U){
        u1_t_shtdwn_1st = (U1)FALSE;
        u4_s_run_m_shtdwndlycnt = (U4)0U;
    }
    else if(u4_s_run_m_shtdwndlycnt < (U4)u2_g_RUN_M_TIMOUT_TO_SHTDWN){
        u1_t_shtdwn_1st = (U1)FALSE;
    }
    else if((u1_t_shtdwn_1st & (U1)RUN_M_FRCD_SLP_CHK_TRUE) != (U1)0U){
        u1_t_shtdwn_1st = (U1)TRUE;
        u4_t_shtdwnrqst_frcd = (U4)TRUE;
    }
    else{
     /* u1_t_shtdwn_1st = (U1)TRUE; */
    }

    u1_t_shtdwn_2nd = u1_g_RunMCfghkShtdwnchk2nd(u1_t_shtdwn_1st, (U2)u4_s_run_m_shtdwndlycnt);
    u1_s_run_m_shtdwnrqst = u1_t_shtdwn_1st & u1_t_shtdwn_2nd;
    u4_t_shtdwnrqst_nrml  = (U4)u1_s_run_m_shtdwnrqst;

    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_CPREQ_002, &u4_t_shtdwnrqst_nrml, (U2)RUN_M_SLP_RQST_NWORD);
    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_CPREQ_044, &u4_t_shtdwnrqst_frcd, (U2)RUN_M_SLP_RQST_NWORD);

}
/*===================================================================================================================================*/
/*  U1      u1_g_RunMShtdwnRqst(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_RunMShtdwnRqst(void)
{
    U1               u1_t_shtdwn;

    u1_t_shtdwn = u1_g_RunMCfgWksrcIrqchk();
    if((u1_t_shtdwn & ((U1)RUN_M_NRML_SLP_CHK_TRUE | (U1)RUN_M_FRCD_SLP_CHK_TRUE)) == (U1)0U){
        u4_s_run_m_shtdwndlycnt = (U4)U4_MAX;
        u1_s_run_m_shtdwnrqst   = (U1)FALSE;
    }

    return(u1_s_run_m_shtdwnrqst);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    12/ 4/2012  TN       New.                                                                                               */
/*  1.1.0     3/ 5/2015  TN       vd_BSW_M_IMMDSHT_WKSRC_INIT was added.                                                             */
/*  1.2.0     3/18/2015  TN       u1_g_BswMCfghkXXX -> u1_g_BswMCfghk                                                                */
/*  1.3.0     6/ 5/2015  TN       vd_g_EcuMShutdown was implemented in order to prepare for AUTOSA-OS integration.                   */
/*  1.4.0     7/ 6/2015  TN       bsw_m.c v1.3.0 -> v1.4.0.                                                                          */
/*            8/ 6/2015  TN       Bug Fix : u1_t_irqst -> u4_t_irqst in u1_g_BswMCfgWksrcIrqchk.                                     */
/*  1.5.0    10/12/2015  TN       vd_g_BswMCfgWksrcIrqInit was implemented.                                                          */
/*  1.6.0    12/ 7/2015  TN       vd_g_BswMCfgWksrcIrqInit -> vd_g_BswMCfgWksrcCfgRefresh.                                           */
/*  1.7.0     1/19/2016  TN       Bug Fix : the shutdown timeout counter was expired faster than designed if all shutdown inhibitors */
/*                                are false(in implementation equal to true).                                                        */
/*  1.8.0     2/19/2016  TN       Bug Fix : u4_s_bsw_m_shtdwndlycnt handling didn't meet the tolerance in the design.                */
/*                                u4_s_bsw_m_shtdwndlycnt should be initialized to "0" only at vd_g_BswMMainTask to achieve          */
/*                                the time tolerance [0, +tick].                                                                     */
/*  1.9.0     4/ 7/2016  TN       Improvement : vd_g_BswMCfgInit was implemented.                                                    */
/*  1.10.0   11/ 7/2016  TN       Improvement : vd_g_BswMTrgrImmdShtdwn was deleted.                                                 */
/*  1.11.0    3/ 4/2019  TN       Improvement : u1_s_bsw_m_shtdwnrqst was determined depend on u1_t_shtdwn_1st and u1_t_shtdwn_2nd   */
/*                                              in vd_g_BswMMainTask.                                                                */
/*  1.12.0    6/24/2025  RS       Change for BEV PreCV.                                                                              */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * RS   = Ryuki Sako, Denso Techno                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/

