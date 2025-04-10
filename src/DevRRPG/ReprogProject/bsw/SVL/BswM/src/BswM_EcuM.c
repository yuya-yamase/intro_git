/* BswM_EcuM_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | BswM/EcuM/CODE                                              */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <BswM.h>
#include "BswM_Local.h"

#include <Rte.h>
#include <EcuM.h>
#include <SchM_BswM.h>
#include <WdgM.h>
#include <Int.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define BSWM_START_SEC_VAR
#include <BswM_MemMap.h>

#define BSWM_STOP_SEC_VAR
#include <BswM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define BSWM_START_SEC_CST
#include <BswM_MemMap.h>

#define BSWM_STOP_SEC_CST
#include <BswM_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define BSWM_START_SEC_CODE
#include <BswM_MemMap.h>

/******************************************************************************/
/* Function Name | BswM_Act_EcuMStartup                                       */
/* Description   | Action of the EcuM mode control(STARTUP)                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, BSWM_CODE_FAST) BswM_Act_EcuMStartup (void)
{
    BswM_InitUnit();

    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    Int_SetMaskLevel(INT_MASK_LV2);

    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    Rte_RpgEvtHk_SchEvt_InitLast();

    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    if( BswM_CtrlReqMode.FlsPrg == BSWM_MODE_FLS_PRG_READY )
    {
        SchM_Notification_FlsProgram(SCHM_FLS_PRG_READY);
    }

    BswM_EcuMState = ECUM_STATE_RUN;

    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    Rte_RpgEvtHk_SchEvt_RunFirst();

    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    EcuM_SetState(ECUM_STATE_RUN);

#if ((REPROG_CFG_CAN_DISABLE == STD_ON) && (REPROG_CFG_ETH_USE == STD_OFF) && (REPROG_CFG_CXPI_USE == STD_OFF))
    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    /* Conditions for calling Int_SetMaskLevel(INT_MASK_NONE) */
    /*  - CAN disabled (REPROG_CFG_CAN_DISABLE == STD_ON) AND */
    /*    Ether disabled (REPROG_CFG_ETH_USE == STD_OFF) AND  */
    /*    CXPI disabled (REPROG_CFG_CXPI_USE == STD_OFF)      */
    /*     After EcuM changed to RUN state.                   */
    /*  - CAN enabled (REPROG_CFG_CAN_DISABLE != STD_ON) OR   */
    /*    Ether enabled (REPROG_CFG_ETH_USE == STD_ON) OR     */
    /*    CXPI enabled (REPROG_CFG_CXPI_USE == STD_ON)        */
    /*     BswM_CommunicationStart() was called.              */
    Int_SetMaskLevel(INT_MASK_NONE);
#endif

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define BSWM_STOP_SEC_CODE
#include <BswM_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

