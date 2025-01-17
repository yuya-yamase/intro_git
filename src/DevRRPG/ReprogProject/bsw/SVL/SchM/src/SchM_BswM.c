/* SchM_BswM_c_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | SchM/BswM/CODE                                              */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <SchM.h>
#include <SchM_BswM.h>
#include "SchM_Local.h"


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
#define SCHM_RPRG_START_SEC_VAR
#include <SchM_Rprg_MemMap.h>

VAR(uint16, SCHM_VAR_CLEARED) SchM_FlsProgram;
VAR(uint8, SCHM_VAR_CLEARED) SchM_FinishFlg;

#define SCHM_RPRG_STOP_SEC_VAR
#include <SchM_Rprg_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define SCHM_RPRG_START_SEC_CST
#include <SchM_Rprg_MemMap.h>

#define SCHM_RPRG_STOP_SEC_CST
#include <SchM_Rprg_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define SCHM_RPRG_START_SEC_CODE
#include <SchM_Rprg_MemMap.h>

/******************************************************************************/
/* Function Name | SchM_Finish_MainFunction                                   */
/* Description   | Finishes the main function execution of each unit          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, SCHM_CODE_SLOW) SchM_Finish_MainFunction (void)
{
    if( SchM_CfgPtr != NULL_PTR )
    {
        SchM_FinishFlg = STD_ON;
    }
    else
    {
        SchM_ReportError(SCHM_API_ID_FIN_MAINFUNC, SCHM_E_UNINIT);
    }

    return;
}

/******************************************************************************/
/* Function Name | SchM_Notification_FlsProgram                               */
/* Description   | Notified of the flash program mode                         */
/* Preconditions |                                                            */
/* Parameters    | [IN] Mode : Flash program mode                             */
/*               |       SCHM_FLS_PRG_NOTREADY                                */
/*               |       SCHM_FLS_PRG_READY                                   */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, SCHM_CODE_SLOW) SchM_Notification_FlsProgram
(
    VAR(uint16, AUTOMATIC) Mode
)
{
    if( SchM_CfgPtr != NULL_PTR )
    {
        if( ( Mode == SCHM_FLS_PRG_NOTREADY ) || ( Mode == SCHM_FLS_PRG_READY ) )
        {
            SchM_FlsProgram = Mode;
        }
        else
        {
            SchM_ReportError(SCHM_API_ID_NOTIFY_FLSPRG, SCHM_E_PARAM_INVALID);
        }

    }
    else
    {
        SchM_ReportError(SCHM_API_ID_NOTIFY_FLSPRG, SCHM_E_UNINIT);
    }

    return;
}

#if (REPROG_CFG_SUBMICONEVENT_TXCONFIRMATION_USE == STD_ON)
/******************************************************************************/
/* Function Name | SchM_Finish_SubMiconFinEvtWait                             */
/* Description   | Finishes the waiting process of notification of the finish */
/*               | event to SubMicon to be completed                          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | This function can be used when                             */
/*               | REPROG_CFG_SUBMICONEVENT_TXCONFIRMATION_USE is STD_ON.     */
/******************************************************************************/
FUNC(void, SCHM_CODE_SLOW) SchM_Finish_SubMiconFinEvtWait (void)
{
    if( SchM_CfgPtr != NULL_PTR )
    {
        /* Release the wait of SchM_WaitSubMiconFinEvtTxCmpl(). */
        SchM_SubMiconFinEvtTxCmplFlg = STD_ON;
    }

    return;
}
#endif


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define SCHM_RPRG_STOP_SEC_CODE
#include <SchM_Rprg_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2019/07/16 :Update                                rel.AUBASS */
/*  v3.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

