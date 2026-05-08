/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for MET/HUD based on AUBIST/DEM, DCM                                                                            */
/*  Reprog                                                                                                                           */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDOCAN_RPG_C_MAJOR                      (1U)
#define OXDOCAN_RPG_C_MINOR                      (0U)
#define OXDOCAN_RPG_C_PATCH                      (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_cfg_private.h"

#include "Dcm.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_RPG_CTRL_NUM_STS                    (6U)
#define OXDC_RPG_CTRL_PRE_RUN                    (0U)
#define OXDC_RPG_CTRL_REQ_ACT                    (1U)
#define OXDC_RPG_CTRL_RDY_ACT                    (2U)
#define OXDC_RPG_CTRL_VOL_INACT                  (3U)
#define OXDC_RPG_CTRL_SP1_INACT                  (4U)
#define OXDC_RPG_CTRL_INACT                      (5U)

#define OXDC_RPG_VSOK_TM_MAX                     (0xfffeU)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ( OXDC_FUNC_RPG_RESET == OXDC_USE )
static U2                    u2_s_oxdc_rpg_vsok_tmcnt;
#endif /* ( OXDC_FUNC_RPG_RESET == OXDC_USE ) */   
static U2                    u2_s_oxdc_rpg_prep_tmcnt;
static U1                    u1_s_oxdc_rpg_ctrl;

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
/*  void    vd_g_oXDoCANRpgInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANRpgInit(void)
{
#if ( OXDC_FUNC_RPG_RESET == OXDC_USE )
    u2_s_oxdc_rpg_vsok_tmcnt = (U2)U2_MAX;
#endif /* ( OXDC_FUNC_RPG_RESET == OXDC_USE ) */       
    u2_s_oxdc_rpg_prep_tmcnt = (U2)U2_MAX;
    u1_s_oxdc_rpg_ctrl       = (U1)OXDC_RPG_CTRL_RDY_ACT;
}
/*===================================================================================================================================*/
/*  U1   u1_g_oXDoCANRpgToAct(U1 * u1_a_errcode)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1   u1_g_oXDoCANRpgToAct(U1 * u1_a_errcode)
{
    /* ---------------------------------------------------------------------------------------------------- */
    /* Attention                                                                                            */
    /* ---------------------------------------------------------------------------------------------------- */
    /* Caller : Dcm/Dsp/usr/Dcm_Dsp_SID10_Callout.c                                                         */
    /*                                                                                                      */
    /* FUNC( Std_ReturnType, DCM_CODE_CALLOUT ) Dcm_CheckSessionControl                                     */
    /* (                                                                                                    */
    /*     const uint8 u1SubFunction,                                                                       */
    /*     P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode                      */
    /* )                                                                                                    */
    /* Return Value  | Std_ReturnType                                                                       */
    /*               |   E_OK             : Check OK                                                        */
    /*               |   E_NOT_OK         : Check NG                                                        */
    /* ---------------------------------------------------------------------------------------------------- */

    U1                     u1_t_act;
    U1                     u1_t_rslt;

    u1_t_rslt = u1_g_oXDoCANCfgRpgCheck();
    if(u1_s_oxdc_rpg_ctrl == (U1)OXDC_RPG_CTRL_VOL_INACT){
        *u1_a_errcode      = (U1)DCM_E_VOLTAGETOOLOW;
        u1_t_act           = (U1)E_NOT_OK;
    }
    else if(u1_s_oxdc_rpg_ctrl == (U1)OXDC_RPG_CTRL_SP1_INACT){
        *u1_a_errcode      = (U1)DCM_E_VEHICLESPEEDTOOHIGH;
        u1_t_act           = (U1)E_NOT_OK;
    }
    else if((u1_s_oxdc_rpg_ctrl == (U1)OXDC_RPG_CTRL_RDY_ACT) &&
            (u1_t_rslt          == (U1)TRUE                 )){
        u1_s_oxdc_rpg_ctrl = (U1)OXDC_RPG_CTRL_REQ_ACT;
        u1_t_act           = (U1)E_OK;
    }
    else if((u1_s_oxdc_rpg_ctrl <  (U1)OXDC_RPG_CTRL_RDY_ACT) &&
            (u1_t_rslt          == (U1)TRUE                 )){
        u1_t_act           = (U1)E_OK;
    }
    else{
        *u1_a_errcode      = (U1)DCM_E_CONDITIONSNOTCORRECT;
        u1_t_act           = (U1)E_NOT_OK;
    }

    return(u1_t_act);
}

/*===================================================================================================================================*/
/*  U1   u1_g_oXDoCANRpgToRun(const U1 u1_a_STATUS)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1   u1_g_oXDoCANRpgToRun(const U1 u1_a_STATUS)
{
    U1                     u1_t_run;

    if(u1_a_STATUS == (U1)DCM_CANCEL){
        u1_t_run                 = (U1)E_OK;
        u1_s_oxdc_rpg_ctrl       = (U1)OXDC_RPG_CTRL_RDY_ACT;
        u2_s_oxdc_rpg_prep_tmcnt = (U2)U2_MAX;
#if ( OXDC_FUNC_RPG_RESET == OXDC_USE )        
        vd_g_oXDoCANCfgRpgCancel();
#endif /* ( OXDC_FUNC_RPG_RESET == OXDC_USE ) */        
    }
    else{
        if(u1_s_oxdc_rpg_ctrl > (U1)OXDC_RPG_CTRL_REQ_ACT){
            u1_t_run             = (U1)E_NOT_OK;
        }
        else if(u2_s_oxdc_rpg_prep_tmcnt >= u2_g_OXDC_RPG_TIM_TO_RUN){
            u1_t_run             = (U1)E_OK;
        }
        else{
            u1_t_run             = (U1)DCM_E_PENDING;
        }
    }

    return(u1_t_run);
}
#if ( OXDC_FUNC_RPG_RESET == OXDC_USE )
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANRpgSwReset(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANRpgSwReset(void)
{
    if((u1_s_oxdc_rpg_ctrl       == (U1)OXDC_RPG_CTRL_PRE_RUN) &&
       (u2_s_oxdc_rpg_prep_tmcnt >= u2_g_OXDC_RPG_TIM_TO_RUN )){

        vd_g_oXDoCANCfgRpgSwReset();
    }
}
/*====================================================================================================================================*/
/*  void    vd_g_oXDoCANRpgChk(const U1 u1_a_RPG_EN)                                                                                  */
/* ---------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                 */
/*  Return:         -                                                                                                                 */
/*====================================================================================================================================*/
void    vd_g_oXDoCANRpgChk(const U1 u1_a_RPG_EN)
{
    static const U2        u2_s_OXDC_RPG_KMPH_MIN   = (U2)500U;                      /* 5.00 km/h        */
    static const U2        u2_s_OXDC_RPG_TIM_TO_ACT = (U2)200U / (U2)OXDC_MAIN_TICK; /* 200 milliseconds */

    static const U1        u1_sp_OXDC_RPG_CTRL_NEXT[OXDC_RPG_CTRL_NUM_STS] = {
        (U1)OXDC_RPG_CTRL_PRE_RUN, /* OXDC_RPG_CTRL_PRE_RUN   (0U) */
        (U1)OXDC_RPG_CTRL_PRE_RUN, /* OXDC_RPG_CTRL_REQ_ACT   (1U) */
        (U1)OXDC_RPG_CTRL_RDY_ACT, /* OXDC_RPG_CTRL_RDY_ACT   (2U) */
        (U1)OXDC_RPG_CTRL_RDY_ACT, /* OXDC_RPG_CTRL_VOL_INACT (3U) */
        (U1)OXDC_RPG_CTRL_RDY_ACT, /* OXDC_RPG_CTRL_SP1_INACT (4U) */
        (U1)OXDC_RPG_CTRL_RDY_ACT  /* OXDC_RPG_CTRL_INACT     (5U) */
    };

    static U2              u2_t_op01_kmph;


    u2_t_op01_kmph = u2_g_oXDoCANCfgKmph();

    if((u2_t_op01_kmph > u2_s_OXDC_RPG_KMPH_MIN) &&
       (u2_t_op01_kmph <  (U2)OXDC_KMPH_UNK    )){
        u2_s_oxdc_rpg_vsok_tmcnt = (U2)U2_MAX;
    }
    else if(u2_s_oxdc_rpg_vsok_tmcnt >= (U2)U2_MAX){
        u2_s_oxdc_rpg_vsok_tmcnt = (U2)0U;
    }
    else if(u2_s_oxdc_rpg_vsok_tmcnt >= u2_s_OXDC_RPG_TIM_TO_ACT){
        u2_s_oxdc_rpg_vsok_tmcnt = u2_s_OXDC_RPG_TIM_TO_ACT;
    }
    else{
        u2_s_oxdc_rpg_vsok_tmcnt++;
    }

    if(u1_s_oxdc_rpg_ctrl == (U1)OXDC_RPG_CTRL_REQ_ACT){
        u2_s_oxdc_rpg_prep_tmcnt = (U2)0U;
    }
    else if(u2_s_oxdc_rpg_prep_tmcnt < (U2)U2_MAX){
        u2_s_oxdc_rpg_prep_tmcnt++;
    }
    else{
        /* Do Nothing */
    }

    if(u1_a_RPG_EN != (U1)OXDC_EOM_RPG_EN){
        u1_s_oxdc_rpg_ctrl       = (U1)OXDC_RPG_CTRL_VOL_INACT;
        u2_s_oxdc_rpg_prep_tmcnt = (U2)U2_MAX;
    }
    else if((u2_s_oxdc_rpg_vsok_tmcnt == (U2)U2_MAX              ) ||
            (u2_s_oxdc_rpg_vsok_tmcnt <  u2_s_OXDC_RPG_TIM_TO_ACT)){
        u1_s_oxdc_rpg_ctrl       = (U1)OXDC_RPG_CTRL_SP1_INACT;
        u2_s_oxdc_rpg_prep_tmcnt = (U2)U2_MAX;
    }
    else if(u1_s_oxdc_rpg_ctrl >= (U1)OXDC_RPG_CTRL_NUM_STS){
        u1_s_oxdc_rpg_ctrl       = (U1)OXDC_RPG_CTRL_INACT;
        u2_s_oxdc_rpg_prep_tmcnt = (U2)U2_MAX;
    }
    else{
        u1_s_oxdc_rpg_ctrl       = u1_sp_OXDC_RPG_CTRL_NEXT[u1_s_oxdc_rpg_ctrl];
    }

    if(u2_s_oxdc_rpg_prep_tmcnt <= u2_g_OXDC_RPG_TIM_TO_RUN){
        vd_g_oXDoCANCfgRpgPrepToRun(u2_s_oxdc_rpg_prep_tmcnt);
    }
}
#endif /*  ( OXDC_FUNC_RPG_RESET == OXDC_USE ) */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     2/ 7/2023  II       New.                                                                                               */
/*                                                                                                                                   */
/*  * II = Itsuki Ito, DENSO                                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/
