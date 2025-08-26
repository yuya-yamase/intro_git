/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  OEM eXtention of CAN : Network Wake-up Request Handler                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_WRH_CFG_C_MAJOR                    (2U)
#define OXCAN_WRH_CFG_C_MINOR                    (0U)
#define OXCAN_WRH_CFG_C_PATCH                    (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxcan_wrh_cfg_private.h"

#if ((defined(BSW_BSWM_CS_CFG_FUNC_DCM)) && (BSW_BSWM_CS_CFG_FUNC_DCM == BSW_USE))
#include "Dcm.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OXCAN_WRH_CFG_C_MAJOR != OXCAN_WRH_CFG_H_MAJOR) || \
     (OXCAN_WRH_CFG_C_MINOR != OXCAN_WRH_CFG_H_MINOR) || \
     (OXCAN_WRH_CFG_C_PATCH != OXCAN_WRH_CFG_H_PATCH))
#error "oxcan_wrh_cfg.c and oxcan_wrh_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXCAN_LIB_CFG_EN_WRH == 1U)
#else
#error "oxcan_wrh_cfg.c : OXCAN_LIB_CFG_EN_WRH is NOT equal to 1U."
#endif /* #if (OXCAN_LIB_CFG_EN_WRH == 1U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
ST_OXCAN_WRH_HCH            st_gp_oxcan_wrh_hch[OXCAN_WRH_NUM_RQH];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U4                    u4_g_OXCAN_WRH_LOG_REQ_EX = (U4)OXCAN_SYS_BAT;                    /* vd_g_oXCANWrhReqHch was executed    */ 

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U4                    u4_g_OXCAN_WRH_TOR_BY_VOM = (U4)OXCAN_SYS_IGR;                    /* TimeOut count Restart Condition     */
const U4                    u4_g_OXCAN_WRH_REQ_BY_VOM = (U4)OXCAN_SYS_PNC_16;
const U2                    u2_g_OXCAN_WRH_VOM_TOUT   = (U2)13000U / (U2)OXCAN_MAIN_TICK;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_OXCAN_WRH_RQH      st_gp_OXCAN_WRH_RQH[OXCAN_WRH_NUM_RQH] = {
    {
        ((U4)OXCAN_SYS_PNC_16 |                   /* u4_sys_net  : OXCAN_SYS_NET             */
         (U4)OXCAN_SYS_PNC_40 |
         (U4)OXCAN_SYS_PNC_43 |
         (U4)OXCAN_SYS_PNC_44),
        ((U2)5000U / (U2)OXCAN_MAIN_TICK),        /* u2_tout_sta : OXCAN_NWRQH_CTRL_STA (0U) */
        ((U2)5000U / (U2)OXCAN_MAIN_TICK)         /* u2_tout_run : OXCAN_NWRQH_CTRL_RUN (1U) */
    }
};
const U1                    u1_g_OXCAN_WRH_NUM_RQH = (U1)OXCAN_WRH_NUM_RQH;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U4      u4_g_oXCANWrhCfgReqbyDcm(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         OXCAN_SYS_XXX of OXCAN_SYS_NET                                                                                   */
/*===================================================================================================================================*/
U4      u4_g_oXCANWrhCfgReqbyDcm(void)
{
#if ((defined(BSW_BSWM_CS_CFG_FUNC_DCM)) && (BSW_BSWM_CS_CFG_FUNC_DCM == BSW_USE))
    U4                 u4_t_req;
    U1                 u1_t_act;

    u1_t_act = Dcm_GetBusSleepPermission((U1)TRUE);
    if(u1_t_act == (U1)FALSE){
        u4_t_req = (U4)OXCAN_SYS_PNC_16;
    }
    else{
        u4_t_req = (U4)0U;
    }

    return(u4_t_req);
#else
    return((U4)0U);
#endif
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANWrhCfgReqbyNet(const U4 u4_a_REQ_BY_NET)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANWrhCfgReqbyNet(const U4 u4_a_REQ_BY_NET)
{
    U4                 u4_t_req;

    u4_t_req = u4_a_REQ_BY_NET & (U4)OXCAN_SYS_PNC_16;
    if(u4_t_req != (U4)0U){
        (void)ComM_RequestChPncComMode((U1)0U,(U1)BSW_COMM_USERHANDLE_PNCUSER16, (U1)COMM_FULL_COMMUNICATION);
        (void)ComM_RequestChPncComMode((U1)1U,(U1)BSW_COMM_USERHANDLE_PNCUSER16, (U1)COMM_FULL_COMMUNICATION);
        (void)ComM_RequestChPncComMode((U1)2U,(U1)BSW_COMM_USERHANDLE_PNCUSER16, (U1)COMM_FULL_COMMUNICATION);
    }
    else{
        (void)ComM_RequestChPncComMode((U1)0U,(U1)BSW_COMM_USERHANDLE_PNCUSER16, (U1)COMM_NO_COMMUNICATION);
        (void)ComM_RequestChPncComMode((U1)1U,(U1)BSW_COMM_USERHANDLE_PNCUSER16, (U1)COMM_NO_COMMUNICATION);
        (void)ComM_RequestChPncComMode((U1)2U,(U1)BSW_COMM_USERHANDLE_PNCUSER16, (U1)COMM_NO_COMMUNICATION);
    }

    u4_t_req = u4_a_REQ_BY_NET & (U4)OXCAN_SYS_PNC_40;
    if(u4_t_req != (U4)0U){
        (void)ComM_RequestChPncComMode((U1)0U,(U1)BSW_COMM_USERHANDLE_PNCUSER40, (U1)COMM_FULL_COMMUNICATION);
        (void)ComM_RequestChPncComMode((U1)1U,(U1)BSW_COMM_USERHANDLE_PNCUSER40, (U1)COMM_FULL_COMMUNICATION);
        (void)ComM_RequestChPncComMode((U1)2U,(U1)BSW_COMM_USERHANDLE_PNCUSER40, (U1)COMM_FULL_COMMUNICATION);
    }
    else{
        (void)ComM_RequestChPncComMode((U1)0U,(U1)BSW_COMM_USERHANDLE_PNCUSER40, (U1)COMM_NO_COMMUNICATION);
        (void)ComM_RequestChPncComMode((U1)1U,(U1)BSW_COMM_USERHANDLE_PNCUSER40, (U1)COMM_NO_COMMUNICATION);
        (void)ComM_RequestChPncComMode((U1)2U,(U1)BSW_COMM_USERHANDLE_PNCUSER40, (U1)COMM_NO_COMMUNICATION);
    }

    u4_t_req = u4_a_REQ_BY_NET & (U4)OXCAN_SYS_PNC_43;
    if(u4_t_req != (U4)0U){
        (void)ComM_RequestChPncComMode((U1)0U,(U1)BSW_COMM_USERHANDLE_PNCUSER43, (U1)COMM_FULL_COMMUNICATION);
        (void)ComM_RequestChPncComMode((U1)1U,(U1)BSW_COMM_USERHANDLE_PNCUSER43, (U1)COMM_FULL_COMMUNICATION);
        (void)ComM_RequestChPncComMode((U1)2U,(U1)BSW_COMM_USERHANDLE_PNCUSER43, (U1)COMM_FULL_COMMUNICATION);
    }
    else{
        (void)ComM_RequestChPncComMode((U1)0U,(U1)BSW_COMM_USERHANDLE_PNCUSER43, (U1)COMM_NO_COMMUNICATION);
        (void)ComM_RequestChPncComMode((U1)1U,(U1)BSW_COMM_USERHANDLE_PNCUSER43, (U1)COMM_NO_COMMUNICATION);
        (void)ComM_RequestChPncComMode((U1)2U,(U1)BSW_COMM_USERHANDLE_PNCUSER43, (U1)COMM_NO_COMMUNICATION);
    }

    u4_t_req = u4_a_REQ_BY_NET & (U4)OXCAN_SYS_PNC_44;
    if(u4_t_req != (U4)0U){
        (void)ComM_RequestChPncComMode((U1)0U,(U1)BSW_COMM_USERHANDLE_PNCUSER44, (U1)COMM_FULL_COMMUNICATION);
        (void)ComM_RequestChPncComMode((U1)1U,(U1)BSW_COMM_USERHANDLE_PNCUSER44, (U1)COMM_FULL_COMMUNICATION);
        (void)ComM_RequestChPncComMode((U1)2U,(U1)BSW_COMM_USERHANDLE_PNCUSER44, (U1)COMM_FULL_COMMUNICATION);
    }
    else{
        (void)ComM_RequestChPncComMode((U1)0U,(U1)BSW_COMM_USERHANDLE_PNCUSER44, (U1)COMM_NO_COMMUNICATION);
        (void)ComM_RequestChPncComMode((U1)1U,(U1)BSW_COMM_USERHANDLE_PNCUSER44, (U1)COMM_NO_COMMUNICATION);
        (void)ComM_RequestChPncComMode((U1)2U,(U1)BSW_COMM_USERHANDLE_PNCUSER44, (U1)COMM_NO_COMMUNICATION);
    }
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  2.0.0     2/28/2025  TN       oxcan_nmwk v1.0.2 -> oxcan_wrh v2.0.0.                                                             */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
