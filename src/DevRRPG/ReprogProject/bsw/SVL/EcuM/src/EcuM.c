/* EcuM_c_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | EcuM/CODE                                                   */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <EcuM.h>
#include "EcuM_Local.h"

#include <Rte.h>
#include <SchM.h>
#include <BswM.h>
#include <BswM_EcuM.h>
#include <ComM.h>
#include <WdgM.h>
#include <Shutdown.h>
#include <SleepIf.h>
#include <Gpt.h>
#include <Int.h>
#include <CodeFls.h>
#include <Can.h>
#include <ReprogOpt.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define ECUM_GPT_TIMER_INTERVAL_US  (1000UL)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, ECUM_CODE_FAST) EcuM_InitMcal (void);
static FUNC(void, ECUM_CODE_FAST) EcuM_DeinitMcal (void);
static FUNC(void, ECUM_CODE_FAST) EcuM_CommonShutdown (void);
static FUNC(void, ECUM_CODE_FAST) EcuM_CommonReset (void);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define ECUM_START_SEC2_VAR
#include <EcuM_MemMap.h>

#define ECUM_STOP_SEC2_VAR
#include <EcuM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define ECUM_START_SEC2_CST
#include <EcuM_MemMap.h>

#define ECUM_STOP_SEC2_CST
#include <EcuM_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define ECUM_START_SEC2_CODE
#include <EcuM_MemMap.h>

/******************************************************************************/
/* Function Name | EcuM_Init                                                  */
/* Description   | Initializes EcuM                                           */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | This function will never return.                           */
/******************************************************************************/
FUNC(void, ECUM_CODE_SLOW) EcuM_Init (void)
{
    VAR(Gpt_ChannelType, AUTOMATIC) Ch;

    EcuM_InitMcal();

    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    Rte_RpgEvtHk_SchEvt_InitFirst();

    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    SchM_Init(EcuM_Cfg_Data.SchMCfgDataPtr);

    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    for( Ch = 0U; Ch < (Gpt_ChannelType)GPT_CHANNEL_NUM; Ch++ )
    {
        Gpt_EnableNotification(Ch);

        Gpt_StartTimer(Ch, (Gpt_ValueType)ECUM_GPT_TIMER_INTERVAL_US);
    }

    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    Int_SetMaskLevel(INT_MASK_LV1);

    BswM_Init(EcuM_Cfg_Data.BswMCfgDataPtr);

    BswM_EcuM_CurrentState(ECUM_STATE_STARTUP);

    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    /* No return */
    SchM_MainFunction();

    /* Failsafe */
    Shutdown_ResetWdt();

    return;
}

/******************************************************************************/
/* Function Name | EcuM_SetState                                              */
/* Description   | This function called by BswM to notify about State Switch  */
/* Preconditions |                                                            */
/* Parameters    | [IN] State : EcuM status                                   */
/*               |       ECUM_STATE_STARTUP                                   */
/*               |       ECUM_STATE_RUN                                       */
/*               |       ECUM_STATE_SHUTDOWN                                  */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, ECUM_CODE_SLOW) EcuM_SetState
(
    VAR(EcuM_StateType, AUTOMATIC) State
)
{
    VAR(EcuM_ErrorType, AUTOMATIC) Error;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    if( State == ECUM_STATE_RUN )
    {
        WdgM_SetTriggerCondition();
        WdgM_Trigger();

        /* In Reprog, the User ID is 0 fixation */
        Ret = ComM_RequestComMode(COMM_USER_ID_0, COMM_FULL_COMMUNICATION);
        if( Ret != (Std_ReturnType)E_OK )
        {
            Error.ModuleId = ECUM_MODULE_ECUM;
            Error.ApiId = ECUM_API_ID_SETSTATE;
            Error.ErrorId = ECUM_E_COMM_REQMODE;

            EcuM_ReportError(&Error);
        }
    }
    else if( ( State == ECUM_STATE_STARTUP ) || ( State == ECUM_STATE_SHUTDOWN ) )
    {
        /* No process */
    }
    else
    {
        Error.ModuleId = ECUM_MODULE_ECUM;
        Error.ApiId = ECUM_API_ID_SETSTATE;
        Error.ErrorId = ECUM_E_STATE_PAR_OUT_OF_RANGE;

        EcuM_ReportError(&Error);
    }

    return;
}

/******************************************************************************/
/* Function Name | EcuM_GoDown                                                */
/* Description   | Instructs EcuM to perform a reset                          */
/* Preconditions |                                                            */
/* Parameters    | [IN] Caller : Module ID of the calling module.             */
/*               |       ECUM_MODULE_BSWM                                     */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/* Notes         | - This function will never return.                         */
/*               | - This function does not check an argument. Because it is  */
/*               |   necessary to reset.                                      */
/******************************************************************************/
FUNC(Std_ReturnType, ECUM_CODE_SLOW) EcuM_GoDown
(
    VAR(uint16, AUTOMATIC) Caller
)
{
    EcuM_CommonShutdown();

    EcuM_CommonReset();

    return E_OK;
}

/******************************************************************************/
/* Function Name | EcuM_GoHalt                                                */
/* Description   | Instructs EcuM to go into a sleep mode                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/* Notes         | This function will never return.                           */
/******************************************************************************/
FUNC(Std_ReturnType, ECUM_CODE_SLOW) EcuM_GoHalt (void)
{
    EcuM_CommonShutdown();

    SleepIf_GoSleep();

    EcuM_CommonReset();

    return E_OK;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | EcuM_InitMcal                                              */
/* Description   | Initializes MCAL                                           */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, ECUM_CODE_FAST) EcuM_InitMcal (void)
{
    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    Int_Init();

    if( ReprogOpt_CanDisableConfig == (uint8)STD_OFF )
    {
        WdgM_SetTriggerCondition();
        WdgM_Trigger();

        Can_Init(EcuM_Cfg_Data.CanCfgDataPtr);
    }

    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    CodeFls_Init();

    return;
}

/******************************************************************************/
/* Function Name | EcuM_DeinitMcal                                            */
/* Description   | Deinitializes MCAL                                         */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, ECUM_CODE_FAST) EcuM_DeinitMcal (void)
{
    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    CodeFls_DeInit();

    if( ReprogOpt_CanDisableConfig == (uint8)STD_OFF )
    {
        WdgM_SetTriggerCondition();
        WdgM_Trigger();

        Can_DeInit();
    }

    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    Int_DeInit();

    return;
}

/******************************************************************************/
/* Function Name | EcuM_CommonShutdown                                        */
/* Description   | Shutdown common processing                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, ECUM_CODE_FAST) EcuM_CommonShutdown (void)
{
    VAR(Gpt_ChannelType, AUTOMATIC) Ch;

    BswM_Deinit();

    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    for( Ch = 0U; Ch < (Gpt_ChannelType)GPT_CHANNEL_NUM; Ch++ )
    {
        Gpt_StopTimer(Ch);
    }

    SchM_Deinit();

    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    Rte_RpgEvtHk_SchEvt_DeInitLast();

    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    Int_SetMaskLevel(INT_MASK_ALL);

    EcuM_DeinitMcal();

    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    return;
}

/******************************************************************************/
/* Function Name | EcuM_CommonReset                                           */
/* Description   | Reset common processing                                    */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | This function will never return.                           */
/******************************************************************************/
static FUNC(void, ECUM_CODE_FAST) EcuM_CommonReset (void)
{
    VAR(uint8, AUTOMATIC) ResetMode;

    ResetMode = SHUTDOWN_RESET_WDT;

    if( EcuM_Cfg_Data.ResetType == ECUM_RESET_MCU )
    {
        ResetMode = SHUTDOWN_RESET_MCU;
    }

    /* No return */
    Shutdown_ResetRequest(ResetMode);

    return;
}

#define ECUM_STOP_SEC2_CODE
#include <EcuM_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2022/03/01 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

