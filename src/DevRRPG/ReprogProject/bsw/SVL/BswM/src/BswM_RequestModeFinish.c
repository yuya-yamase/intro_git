/* BswM_RequestModeFinish_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | BswM/RequestModeFinish/CODE                                 */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <BswM.h>
#include "BswM_Local.h"

#include <Rte.h>
#include <Sys.h>
#include <EcuM.h>
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
static FUNC(void, BSWM_CODE_FAST) BswM_Act_FinishNormal (void);
static FUNC(void, BSWM_CODE_FAST) BswM_Act_FinishError (void);
static FUNC(void, BSWM_CODE_FAST) BswM_FinishCommon (void);
static FUNC(uint8, BSWM_CODE_FAST) BswM_SetShutdownTarget (void);


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
/* Function Name | BswM_RequestMode_Finish                                    */
/* Description   | Finish mode request                                        */
/* Preconditions |                                                            */
/* Parameters    | [IN] Mode : The requested mode                             */
/*               |       BSWM_MODE_FINISH_NORMAL                              */
/*               |       BSWM_MODE_FINISH_ERROR                               */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode_Finish
(
    VAR(BswM_ModeType, AUTOMATIC) Mode
)
{
    if( Mode == BSWM_MODE_FINISH_NORMAL )
    {
        BswM_Act_FinishNormal();
    }
    else if( Mode == BSWM_MODE_FINISH_ERROR )
    {
        BswM_Act_FinishError();
    }
    else
    {
        BswM_ReportError(BSWM_API_ID_REQMODE_FINISH, BSWM_E_REQ_MODE_OUT_OF_RANGE);

        /* This function has to be finished here       */
        /* for a function of the end process execution */
        BswM_Act_FinishError();
    }

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | BswM_Act_FinishNormal                                      */
/* Description   | Action of the finish mode control(Normal)                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_Act_FinishNormal (void)
{
    VAR(uint8, AUTOMATIC) MaskLevel;
    VAR(uint8, AUTOMATIC) UpdateFlg;

    UpdateFlg = STD_OFF;

    MaskLevel = MaskInterruptAll(); /* for BswM_CtrlReqMode.Finish */

    if( BswM_CtrlReqMode.Finish == BSWM_MODE_FINISH_NONE )
    {
        BswM_CtrlReqMode.Finish = BSWM_MODE_FINISH_NORMAL;
        UpdateFlg = STD_ON;
    }

    UnMaskInterruptAll(MaskLevel);  /* for BswM_CtrlReqMode.Finish */

    if( UpdateFlg == (uint8)STD_ON )
    {
        /* No return */
        BswM_FinishCommon();
    }

    return;
}

/******************************************************************************/
/* Function Name | BswM_Act_FinishError                                       */
/* Description   | Action of the finish mode control(Error)                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_Act_FinishError (void)
{
    VAR(uint8, AUTOMATIC) MaskLevel;
    VAR(uint8, AUTOMATIC) UpdateFlg;

    UpdateFlg = STD_OFF;

    MaskLevel = MaskInterruptAll(); /* for BswM_CtrlReqMode.Finish */

    if( BswM_CtrlReqMode.Finish == BSWM_MODE_FINISH_NONE )
    {
        BswM_CtrlReqMode.Finish = BSWM_MODE_FINISH_ERROR;
        UpdateFlg = STD_ON;
    }

    UnMaskInterruptAll(MaskLevel);  /* for BswM_CtrlReqMode.Finish */

    if( UpdateFlg == (uint8)STD_ON )
    {
        /* No return */
        BswM_FinishCommon();
    }

    return;
}

/******************************************************************************/
/* Function Name | BswM_FinishCommon                                          */
/* Description   | Common process of the finish mode control                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | This function will never return.                           */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_FinishCommon (void)
{
    VAR(uint8, AUTOMATIC) ShutdownTarget;

    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    Rte_RpgEvtHk_SchEvt_RunLast();

    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    BswM_EcuMState = ECUM_STATE_SHUTDOWN;

    Int_SetMaskLevel(INT_MASK_LV1);

    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    Rte_RpgEvtHk_SchEvt_DeInitFirst();

    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    EcuM_SetState(ECUM_STATE_SHUTDOWN);

    BswM_DeinitUnit();

    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    ShutdownTarget = BswM_SetShutdownTarget();
    if( ShutdownTarget == BSWM_SHUTDOWN_SLEEP )
    {
        /* No return */
        (void)EcuM_GoHalt();
    }
    else
    {
        /* No return */
        (void)EcuM_GoDown(ECUM_MODULE_BSWM);
    }

    return;
}

/******************************************************************************/
/* Function Name | BswM_SetShutdownTarget                                     */
/* Description   | Sets a shutdown target                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Shutdown target                                            */
/*               |  BSWM_SHUTDOWN_RESET                                       */
/*               |  BSWM_SHUTDOWN_SLEEP                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, BSWM_CODE_FAST) BswM_SetShutdownTarget (void)
{
    VAR(uint8, AUTOMATIC) i;
    VAR(uint8, AUTOMATIC) MaskLevel;
    VAR(uint8, AUTOMATIC) ShutdownTarget;

    ShutdownTarget = BSWM_SHUTDOWN_NONE;

    MaskLevel = MaskInterruptAll(); /* for ShutdownTarget */

    for( i = 0U; i < BSWM_FINISHTYPE_NUM; i++ )
    {
        switch( BswM_CfgPtr->FinPriDataPtr->FinPri[i] )
        {
            case BSWM_FINISHTYPE_USR_RESET:
                if( BswM_CtrlReqMode.UsrReset == BSWM_MODE_USR_RESET_EXECUTE )
                {
                    ShutdownTarget = BSWM_SHUTDOWN_RESET;
                }

                break;

            case BSWM_FINISHTYPE_USR_SLEEP:
                if( BswM_CtrlReqMode.UsrSleep == BSWM_MODE_USR_SLEEP_EXECUTE )
                {
                    ShutdownTarget = BSWM_SHUTDOWN_SLEEP;
                }

                break;

            case BSWM_FINISHTYPE_ECU_RESET:
                if( BswM_CtrlReqMode.EcuReset == BSWM_MODE_ECU_RESET_EXECUTE )
                {
                    ShutdownTarget = BSWM_SHUTDOWN_RESET;
                }

                break;

            case BSWM_FINISHTYPE_ERROR:
                if( BswM_CtrlReqMode.Finish == BSWM_MODE_FINISH_ERROR )
                {
                    ShutdownTarget = BSWM_SHUTDOWN_RESET;
                }

                break;

            case BSWM_FINISHTYPE_ACCOFF:
                if( ( BswM_CtrlReqMode.Acc == BSWM_MODE_ACC_OFF ) &&
                    ( BswM_CfgPtr->AccIgActDataPtr->ActAcc != BSWM_SHUTDOWN_NONE ) )
                {
                    ShutdownTarget = BswM_CfgPtr->AccIgActDataPtr->ActAcc;
                }

                break;

            case BSWM_FINISHTYPE_IGOFF:
                if( ( BswM_CtrlReqMode.Ig == BSWM_MODE_IG_OFF ) &&
                    ( BswM_CfgPtr->AccIgActDataPtr->ActIg != BSWM_SHUTDOWN_NONE ) )
                {
                    ShutdownTarget = BswM_CfgPtr->AccIgActDataPtr->ActIg;
                }

                break;

#if (REPROG_CFG_SUBMICON_USE_SUB == STD_ON)
            case BSWM_FINISHTYPE_MAIN_ERR:
                if( BswM_CtrlReqMode.MainErr == BSWM_MODE_MAIN_ERR_OCCUR )
                {
                    ShutdownTarget = BSWM_SHUTDOWN_RESET;
                }

                break;
#endif

            default:
                /* No process */
                break;
        }

        if( ShutdownTarget != BSWM_SHUTDOWN_NONE )
        {
            break;
        }
    }

    UnMaskInterruptAll(MaskLevel);  /* for ShutdownTarget */

    /* When it is undecided, reset is set */
    if( ShutdownTarget == BSWM_SHUTDOWN_NONE )
    {
        ShutdownTarget = BSWM_SHUTDOWN_RESET;
    }

    return ShutdownTarget;
}

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

