/* SchM_c_Revision(v4.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | SchM/CODE                                                   */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <SchM.h>
#include <SchM_BswM.h>
#include "SchM_Local.h"

#include <EcuM.h>
#include <BswM.h>
#include <Shutdown.h>
#include <WdgM.h>
#include <Int.h>
#include <ReprogOpt.h>
#include <Tm.h>
#include <WrapCrypto.h>

#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
#include <Sys.h>
#endif

#if (REPROG_CFG_SUBMICONEVENT_TXCONFIRMATION_USE == STD_ON)
#include <SubMiconIf.h>
#endif


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define SCHM_FLS_NONCTRL    ((uint8)0x00U)
#define SCHM_FLS_CTRL       ((uint8)0x01U)

#define SCHM_CSMMAINFUNC_NOEXE    ((uint8)0x00U)
#define SCHM_CSMMAINFUNC_EXE      ((uint8)0x01U)

#define SCHM_CSMMAINFUNC_SPAN     ((uint32)1000UL)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, SCHM_CODE_FAST) SchM_CsmMainFunc_Exe (void);
static FUNC(void, SCHM_CODE_FAST) SchM_CsmMainFunc_SetMode
(
    VAR(uint8, AUTOMATIC) Mode
);
static FUNC(void, SCHM_CODE_FAST) SchM_CsmMainFunc_ResetTimer (void);
static FUNC(uint8, SCHM_CODE_FAST) SchM_CsmMainFunc_CheckTimer (void);
#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
static FUNC(void, SCHM_CODE_FAST) SchM_CheckStayInBootTimeout (void);
#endif
#if (REPROG_CFG_SUBMICONEVENT_TXCONFIRMATION_USE == STD_ON)
static FUNC(void, SCHM_CODE_FAST) SchM_WaitSubMiconFinEvtTxCmpl (void);
#endif


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define SCHM_RPRG_START_SEC_VAR
#include <SchM_Rprg_MemMap.h>

P2CONST(SchM_ConfigType, SCHM_VAR_CLEARED, SCHM_APPL_CONST) SchM_CfgPtr;
static VAR(uint8, SCHM_VAR_CLEARED) SchM_FlsCtrl;
static VAR(uint8, SCHM_VAR_CLEARED) SchM_CsmMainFuncExeMode;
static VAR(Tm_PredefTimer1us32bitType, SCHM_VAR_CLEARED) SchM_CsmMainFuncStartTime;
#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
static VAR(uint8, SCHM_VAR_CLEARED) SchM_StayInBootState;
static VAR(uint8, SCHM_VAR_CLEARED) SchM_RewriteCompFlg;
static VAR(Tm_PredefTimer1us32bitType, SCHM_VAR_CLEARED) SchM_StayInBootStartTime;
#endif
#if (REPROG_CFG_SUBMICONEVENT_TXCONFIRMATION_USE == STD_ON)
VAR(uint8, SCHM_VAR_CLEARED) SchM_SubMiconFinEvtTxCmplFlg;
static VAR(uint8, SCHM_VAR_CLEARED) SchM_SubMiconFinEvtTxWtStFlg;
#endif

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
/* Function Name | SchM_Init                                                  */
/* Description   | Initializes SchM                                           */
/* Preconditions |                                                            */
/* Parameters    | [IN] ConfigPtr : Address of the SchM configuration table   */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, SCHM_CODE_SLOW) SchM_Init
(
    P2CONST(SchM_ConfigType, AUTOMATIC, SCHM_APPL_CONST) ConfigPtr
)
{
#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
    VAR(uint8, AUTOMATIC) BootMode;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    BootMode = EcuM_GetBootMode();
    if( BootMode == ECUM_START_BOOT_ENTRY )
    {
        SchM_StayInBootState = SCHM_STATE_BOOT_ENTRY;
    }
    else if( BootMode == ECUM_START_AP_ENTRY )
    {
        SchM_StayInBootState = SCHM_STATE_AP_ENTRY;
    }
    else
    {
        SchM_StayInBootState = SCHM_STATE_STAYINBOOT_WAIT;

        /* If REPROG_CFG_SUBMICON_USE_SUB is STD_ON, Do not check timeout. */
        /* MainMicon notify SubMicon of timeout event. So, no need to      */
        /* start and check StayInBoot timer.                               */
        if( ReprogOpt_SubMiconConfig != REPROGOPT_SUBMICON_TYPE_SUB )
        {
            SchM_StayInBootStartTime.StartPoint = 0UL;
            Ret = Tm_ResetTimer1us32bit(&SchM_StayInBootStartTime);
            if( Ret != (Std_ReturnType)E_OK )
            {
                SchM_ReportError(SCHM_API_ID_INIT, SCHM_E_TM_RESET);
            }
        }
    }
    SchM_RewriteCompFlg = STD_OFF;
#endif

    if( ConfigPtr != NULL_PTR )
    {
        SchM_CfgPtr = ConfigPtr;
        SchM_FlsProgram = SCHM_FLS_PRG_NOTREADY;
        SchM_FlsCtrl = SCHM_FLS_NONCTRL;
        SchM_FinishFlg = STD_OFF;
#if (REPROG_CFG_SUBMICONEVENT_TXCONFIRMATION_USE == STD_ON)
        SchM_SubMiconFinEvtTxCmplFlg = STD_OFF;
        SchM_SubMiconFinEvtTxWtStFlg = STD_OFF;
#endif
        SchM_CsmMainFunc_SetMode(SCHM_CSMMAINFUNC_EXE);

        SchM_CsmMainFunc_ResetTimer();
    }
    else
    {
        SchM_CfgPtr = NULL_PTR;

        SchM_ReportError(SCHM_API_ID_INIT, SCHM_E_PARAM_POINTER);
    }

    return;
}

/******************************************************************************/
/* Function Name | SchM_Deinit                                                */
/* Description   | Deinitializes SchM                                         */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, SCHM_CODE_SLOW) SchM_Deinit (void)
{
    SchM_CfgPtr = NULL_PTR;

    return;
}

/******************************************************************************/
/* Function Name | SchM_MainFunction                                          */
/* Description   | Carries out the main function of each unit according to    */
/*               | configuration                                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | This function will never return.                           */
/******************************************************************************/
FUNC(void, SCHM_CODE_SLOW) SchM_MainFunction (void)
{
    VAR(uint32, AUTOMATIC) i;
    VAR(BswM_ModeType, AUTOMATIC) FinishMode;
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    P2CONST(SchM_ConfigType, AUTOMATIC, SCHM_APPL_CONST) CfgPtr;

    FinishMode = BSWM_MODE_FINISH_NONE;
    CfgPtr = SchM_CfgPtr;

    if( CfgPtr == NULL_PTR )
    {
        SchM_ReportError(SCHM_API_ID_MAINFUNC, SCHM_E_UNINIT);
    }

    while( TRUE )
    {
        Ret = EcuM_CheckError();
        if( Ret != (Std_ReturnType)E_OK )
        {
            /* EcuM_ReportError() was called. */
            FinishMode = BSWM_MODE_FINISH_ERROR;

#if ((REPROG_CFG_SUBMICON_NOUSE == STD_ON) || (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON))
            if( SchM_FlsCtrl != SCHM_FLS_CTRL )
            {
                BswM_RequestMode(BSWM_USER_SCHM_MAIN_ERR, BSWM_MODE_MAIN_ERR_OCCUR);
            }
#endif
        }
        else
        {
            if( SchM_FinishFlg != (uint8)STD_OFF )
            {
                /* SchM_Finish_MainFunction() was called. */
                FinishMode = BSWM_MODE_FINISH_NORMAL;
            }
        }

        if( FinishMode != BSWM_MODE_FINISH_NONE )
        {
            if( SchM_FlsCtrl != SCHM_FLS_CTRL )
            {
                /* Go to the end sequence. */
                break;
            }
        }

        /* When WdgM_CheckpointReached() continues to return */
        /* with E_NOT_OK, watchdog timeout occurs.           */
        /* So, no need to check the return value.            */
        (void)WdgM_CheckpointReached(WDGM_ENTITYID_BASE, WDGM_CHKPNTID_0);

        if( SchM_FlsCtrl == SCHM_FLS_CTRL )
        {
            /* This function call WdgM_CheckpointReached() instead of calling */
            /* WdgM_CheckpointReached() by SchM_Notification_Channel1().      */
            /* Because SchM_Notification_Channel1() is not called during      */
            /* low priority timer interrupt masked.                           */
            /* And no need to check the return value.                         */
            (void)WdgM_CheckpointReached(WDGM_ENTITYID_TIMELOW, WDGM_CHKPNTID_0);
        }

        if( CfgPtr != NULL_PTR )
        {
            for( i = 0UL; i < CfgPtr->MainFuncDataPtr->FuncNum; i++ )
            {
                if( ( CfgPtr->MainFuncDataPtr->FuncInfoPtr[i].FlsNotReady == (uint8)STD_ON ) ||
                    ( SchM_FlsProgram == SCHM_FLS_PRG_READY ) )
                {
                    if( ( CfgPtr->MainFuncDataPtr->FuncInfoPtr[i].FlsCtrl == (uint8)STD_ON ) ||
                        ( SchM_FlsCtrl == SCHM_FLS_NONCTRL ) )
                    {
                        SchM_CsmMainFunc_Exe();
                        CfgPtr->MainFuncDataPtr->FuncInfoPtr[i].Func();
                    }
                }
            }
        }

#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
        SchM_CheckStayInBootTimeout();
#endif

    }

#if (REPROG_CFG_SUBMICONEVENT_TXCONFIRMATION_USE == STD_ON)
    SchM_WaitSubMiconFinEvtTxCmpl();
#endif

    /* No return */
    BswM_RequestMode(BSWM_USER_SCHM_FINISH, FinishMode);

    /* Failsafe */
    Shutdown_ResetWdt();

    return;
}

/******************************************************************************/
/* Function Name | SchM_Notification_Channel0                                 */
/* Description   | Carries out timer function of each unit according to       */
/*               | configuration(Channel0)                                    */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, SCHM_CODE_SLOW) SchM_Notification_Channel0 (void)
{
    VAR(uint32, AUTOMATIC) i;

    if( SchM_CfgPtr != NULL_PTR )
    {
        WdgM_Trigger();

        /* When WdgM_CheckpointReached() continues to return */
        /* with E_NOT_OK, watchdog timeout occurs.           */
        /* So, no need to check the return value.            */
        (void)WdgM_CheckpointReached(WDGM_ENTITYID_TIMEHIGH, WDGM_CHKPNTID_0);

        for( i = 0UL; i < SchM_CfgPtr->TimeFunc0DataPtr->FuncNum; i++ )
        {
            if( ( SchM_CfgPtr->TimeFunc0DataPtr->FuncInfoPtr[i].FlsNotReady == (uint8)STD_ON ) ||
                ( SchM_FlsProgram == SCHM_FLS_PRG_READY ) )
            {
                SchM_CfgPtr->TimeFunc0DataPtr->FuncInfoPtr[i].Func();
            }
        }
    }
    else
    {
        SchM_ReportError(SCHM_API_ID_NOTIFY_CH0, SCHM_E_UNINIT);
    }

    return;
}

/******************************************************************************/
/* Function Name | SchM_Notification_Channel1                                 */
/* Description   | Carries out timer function of each unit according to       */
/*               | configuration(Channel1)                                    */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, SCHM_CODE_SLOW) SchM_Notification_Channel1 (void)
{
    VAR(uint32, AUTOMATIC) i;

    if( SchM_CfgPtr != NULL_PTR )
    {
        /* When WdgM_CheckpointReached() continues to return */
        /* with E_NOT_OK, watchdog timeout occurs.           */
        /* So, no need to check the return value.            */
        (void)WdgM_CheckpointReached(WDGM_ENTITYID_TIMELOW, WDGM_CHKPNTID_0);

#if (REPROG_CFG_SUBMICONEVENT_TXCONFIRMATION_USE == STD_ON)
        if( SchM_SubMiconFinEvtTxWtStFlg == (uint8)STD_ON )
        {
            SubMiconIf_Time();
        }
        else
        {
#endif
            for( i = 0UL; i < SchM_CfgPtr->TimeFunc1DataPtr->FuncNum; i++ )
            {
                if( ( SchM_CfgPtr->TimeFunc1DataPtr->FuncInfoPtr[i].FlsNotReady == (uint8)STD_ON ) ||
                    ( SchM_FlsProgram == SCHM_FLS_PRG_READY ) )
                {
                    SchM_CfgPtr->TimeFunc1DataPtr->FuncInfoPtr[i].Func();
                }
            }
#if (REPROG_CFG_SUBMICONEVENT_TXCONFIRMATION_USE == STD_ON)
        }
#endif
    }
    else
    {
        SchM_ReportError(SCHM_API_ID_NOTIFY_CH1, SCHM_E_UNINIT);
    }

    return;
}

/******************************************************************************/
/* Function Name | SchM_StartFlsCtrl                                          */
/* Description   | Notified of the control start of the code flash memory     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, SCHM_CODE_SLOW) SchM_StartFlsCtrl (void)
{
    if( SchM_CfgPtr != NULL_PTR )
    {
#if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
        Int_SetMaskLevel(INT_MASK_LV1);

        SchM_FlsCtrl = SCHM_FLS_CTRL;
#endif

        SchM_CsmMainFunc_SetMode(SCHM_CSMMAINFUNC_NOEXE);
    }
    else
    {
        SchM_ReportError(SCHM_API_ID_START_FLSCTRL, SCHM_E_UNINIT);
    }

    return;
}

/******************************************************************************/
/* Function Name | SchM_FinishFlsCtrl                                         */
/* Description   | Notified of the control finish of the code flash memory    */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, SCHM_CODE_SLOW) SchM_FinishFlsCtrl (void)
{
    if( SchM_CfgPtr != NULL_PTR )
    {
        SchM_CsmMainFunc_SetMode(SCHM_CSMMAINFUNC_EXE);

#if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
        SchM_FlsCtrl = SCHM_FLS_NONCTRL;

        Int_SetMaskLevel(INT_MASK_NONE);
#endif
    }
    else
    {
        SchM_ReportError(SCHM_API_ID_FINISH_FLSCTRL, SCHM_E_UNINIT);
    }

    return;
}

#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
/******************************************************************************/
/* Function Name | SchM_GetStayInBootState                                    */
/* Description   | Acquire the StayInBoot state                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | StayInBoot state                                           */
/*               |  SCHM_STATE_BOOT_ENTRY                                     */
/*               |  SCHM_STATE_AP_ENTRY                                       */
/*               |  SCHM_STATE_STAYINBOOT_WAIT                                */
/*               |  SCHM_STATE_STAYINBOOT_TMO                                 */
/*               |  SCHM_STATE_STAYINBOOT_PRGRCV                              */
/* Notes         | - This function can be used when                           */
/*               |   REPROG_CFG_STAYINBOOT_ENABLE is STD_ON.                  */
/*               | - This function can be called after calling SchM_DeInit(). */
/******************************************************************************/
FUNC(uint8, SCHM_CODE_SLOW) SchM_GetStayInBootState (void)
{
    return SchM_StayInBootState;
}

/******************************************************************************/
/* Function Name | SchM_SetStayInBootState                                    */
/* Description   | Set the StayInBoot state                                   */
/* Preconditions |                                                            */
/* Parameters    | [IN] State : StayInBoot state                              */
/*               |       SCHM_STATE_STAYINBOOT_PRGRCV                         */
/*               |       SCHM_STATE_STAYINBOOT_TMO                            */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | This function can be used when                             */
/*               | REPROG_CFG_STAYINBOOT_ENABLE is STD_ON.                    */
/******************************************************************************/
FUNC(Std_ReturnType, SCHM_CODE_SLOW) SchM_SetStayInBootState
(
    VAR(uint8, AUTOMATIC) State
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(uint8, AUTOMATIC) MaskLevel;
    VAR(uint8, AUTOMATIC) CurrentState;

    Ret = E_NOT_OK;

    MaskLevel = MaskInterruptAll(); /* for SchM_StayInBootState */

    CurrentState = SchM_GetStayInBootState();
    if( CurrentState == SCHM_STATE_STAYINBOOT_WAIT )
    {
        if( ( State == SCHM_STATE_STAYINBOOT_TMO ) || ( State == SCHM_STATE_STAYINBOOT_PRGRCV ) )
        {
            SchM_StayInBootState = State;
            Ret = E_OK;
        }
    }

    UnMaskInterruptAll(MaskLevel);  /* for SchM_StayInBootState */

    return Ret;
}

/******************************************************************************/
/* Function Name | SchM_GetRewriteCompFlg                                     */
/* Description   | Acquire rewrite completion flag                            */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Rewrite completion flag                                    */
/*               |  STD_ON                                                    */
/*               |  STD_OFF                                                   */
/* Notes         | - This function can be used when                           */
/*               |   REPROG_CFG_STAYINBOOT_ENABLE is STD_ON.                  */
/*               | - This function can be called after calling SchM_DeInit(). */
/******************************************************************************/
FUNC(uint8, SCHM_CODE_SLOW) SchM_GetRewriteCompFlg (void)
{
    return SchM_RewriteCompFlg;
}

/******************************************************************************/
/* Function Name | SchM_SetRewriteCompFlg                                     */
/* Description   | Set rewrite completion flag                                */
/* Preconditions |                                                            */
/* Parameters    | [IN] RewriteCompFlg : Rewrite completion flag              */
/*               |       STD_ON                                               */
/*               |       STD_OFF                                              */
/* Return Value  | None                                                       */
/* Notes         | This function can be used when                             */
/*               | REPROG_CFG_STAYINBOOT_ENABLE is STD_ON.                    */
/******************************************************************************/
FUNC(void, SCHM_CODE_SLOW) SchM_SetRewriteCompFlg
(
    VAR(uint8, AUTOMATIC) RewriteCompFlg
)
{
    SchM_RewriteCompFlg = RewriteCompFlg;

    return;
}


#endif /* (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON) */

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | SchM_ReportError                                           */
/* Description   | Notifies ECUM of the error information                     */
/* Preconditions |                                                            */
/* Parameters    | [IN] ApiId   : Api ID                                      */
/*               | [IN] ErrorId : Error ID                                    */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, SCHM_CODE_FAST) SchM_ReportError
(
    VAR(uint8, AUTOMATIC) ApiId,
    VAR(uint8, AUTOMATIC) ErrorId
)
{
    VAR(EcuM_ErrorType, AUTOMATIC) Error;

    Error.ModuleId = ECUM_MODULE_SCHM;
    Error.ApiId = ApiId;
    Error.ErrorId = ErrorId;

    EcuM_ReportError(&Error);

    return;
}

/******************************************************************************/
/* Function Name | SchM_CsmMainFunc_Exe                                       */
/* Description   | Function for Execution of Csm_MainFunction                 */
/*               | and Crypto_MainFunction                                    */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, SCHM_CODE_FAST) SchM_CsmMainFunc_Exe (void)
{
    VAR(uint8, AUTOMATIC) Result;

    if( SchM_CsmMainFuncExeMode == SCHM_CSMMAINFUNC_EXE )
    {
        Result = SchM_CsmMainFunc_CheckTimer();
        if( Result == (uint8)STD_ON )
        {
            WrapCrypto_MainFunction();

            SchM_CsmMainFunc_ResetTimer();
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | SchM_CsmMainFunc_SetMode                                   */
/* Description   | Set Execute mode for Csm MainFunction                      */
/* Preconditions |                                                            */
/* Parameters    | [IN] Mode    : Csm Exec mode                               */
/*               |       SCHM_CSMMAINFUNC_EXE                                 */
/*               |       SCHM_CSMMAINFUNC_NOEXE                               */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, SCHM_CODE_FAST) SchM_CsmMainFunc_SetMode
(
    VAR(uint8, AUTOMATIC) Mode
)
{
    SchM_CsmMainFuncExeMode = Mode;

    return;
}

/******************************************************************************/
/* Function Name | SchM_CsmMainFunc_ResetTimer                                */
/* Description   | Reset timer for CsmMainFunc start time                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, SCHM_CODE_FAST) SchM_CsmMainFunc_ResetTimer (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    SchM_CsmMainFuncStartTime.StartPoint = 0UL;
    FuncRet = Tm_ResetTimer1us32bit(&SchM_CsmMainFuncStartTime);

    if( FuncRet != (Std_ReturnType)E_OK)
    {
        SchM_ReportError(SCHM_API_ID_RESET_CSMTIMER, SCHM_E_TM_RESET);
    }

    return;
}

/******************************************************************************/
/* Function Name | SchM_CsmMainFunc_CheckTimer                                */
/* Description   | Check whether CsmMainFunc time interval is exceeded or not */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Timer expired                                              */
/*               |  STD_ON                                                    */
/*               |  STD_OFF                                                   */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, SCHM_CODE_FAST) SchM_CsmMainFunc_CheckTimer (void)
{
    VAR(uint32, AUTOMATIC) TimeSpan;
    VAR(uint8, AUTOMATIC) TimerExpired;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    TimerExpired = STD_OFF;
    TimeSpan = 0UL;

    FuncRet = Tm_GetTimeSpan1us32bit(&SchM_CsmMainFuncStartTime, &TimeSpan);
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        if( TimeSpan >= SCHM_CSMMAINFUNC_SPAN )
        {
            TimerExpired = STD_ON;
        }
    }
    else
    {
        SchM_ReportError(SCHM_API_ID_CHECK_CSMTIMER, SCHM_E_TM_GET);
    }

    return TimerExpired;
}

#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
/******************************************************************************/
/* Function Name | SchM_CheckStayInBootTimeout                                */
/* Description   | Check the StayInBoot timeout and control StayInBoot state  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | This function can be used when                             */
/*               | REPROG_CFG_STAYINBOOT_ENABLE is STD_ON.                    */
/******************************************************************************/
static FUNC(void, SCHM_CODE_FAST) SchM_CheckStayInBootTimeout (void)
{
    VAR(uint32, AUTOMATIC) TimeSpan;
    VAR(uint8, AUTOMATIC) State;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    /* If REPROG_CFG_SUBMICON_USE_SUB is STD_ON, SubMicon has nothing to do.  */
    /* Because only MainMicon should check StayInBoot timer and SubMicon      */
    /* will break from MainFunction after receiving StayInBoot timeout event. */
    if( ReprogOpt_SubMiconConfig != REPROGOPT_SUBMICON_TYPE_SUB )
    {
        State = SchM_GetStayInBootState();
        if( State == SCHM_STATE_STAYINBOOT_WAIT )
        {
            TimeSpan = 0UL;
            Ret = Tm_GetTimeSpan1us32bit(&SchM_StayInBootStartTime, &TimeSpan);
            if( Ret == (Std_ReturnType)E_OK )
            {
                if( TimeSpan > SchM_CfgPtr->StayInBootTime )
                {
                    /* StayInBoot timeout happened. So change StayInBoot state and shutdown. */
                    Ret = SchM_SetStayInBootState(SCHM_STATE_STAYINBOOT_TMO);
                    if( Ret == (Std_ReturnType)E_OK )
                    {
                        SchM_ReportError(SCHM_API_ID_STAYINBOOT_CHKTMO, SCHM_E_STAYINBOOT_TIMEOUT);
                    }
                }
            }
            else
            {
                /* Tm Unit has broken. So shutdown. */
                SchM_ReportError(SCHM_API_ID_STAYINBOOT_CHKTMO, SCHM_E_TM_GET);
            }
        }
    }

    return;
}
#endif /* (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON) */

#if (REPROG_CFG_SUBMICONEVENT_TXCONFIRMATION_USE == STD_ON)
/******************************************************************************/
/* Function Name | SchM_WaitSubMiconFinEvtTxCmpl                              */
/* Description   | Wait for the notification of the finish event to SubMicon  */
/*               | to be completed                                            */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | This function can be used when                             */
/*               | REPROG_CFG_SUBMICONEVENT_TXCONFIRMATION_USE is STD_ON.     */
/******************************************************************************/
static FUNC(void, SCHM_CODE_FAST) SchM_WaitSubMiconFinEvtTxCmpl (void)
{
    VAR(Tm_PredefTimer1us32bitType, AUTOMATIC) StartTime;
    VAR(uint32, AUTOMATIC) TimeSpan;
    VAR(uint8, AUTOMATIC) EndFlg;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    EndFlg = STD_OFF;

    if( SchM_CfgPtr != NULL_PTR )
    {
        StartTime.StartPoint = 0UL;
        Ret = Tm_ResetTimer1us32bit(&StartTime);
        if( Ret != (Std_ReturnType)E_OK )
        {
            /* Tm Unit has broken. */
            EndFlg = STD_ON;
        }
    }
    else
    {
        EndFlg = STD_ON;
    }

    if( EndFlg == (uint8)STD_OFF )
    {
        /* Limit the functions to be called in SchM_Notification_Channel1(). */
        SchM_SubMiconFinEvtTxWtStFlg = STD_ON;

        while( TRUE )
        {
            TimeSpan = 0UL;
            Ret = Tm_GetTimeSpan1us32bit(&StartTime, &TimeSpan);
            if( Ret == (Std_ReturnType)E_OK )
            {
                if( TimeSpan >= SchM_CfgPtr->SubMiconFinEvtTxTimeOut )
                {
                    /* Timeout happened. */
                    EndFlg = STD_ON;
                }
            }
            else
            {
                /* Tm Unit has broken. */
                EndFlg = STD_ON;
            }

            if( ( EndFlg != (uint8)STD_OFF ) || ( SchM_SubMiconFinEvtTxCmplFlg != (uint8)STD_OFF ) )
            {
                break;
            }

            /* No need to check the return value.                             */
            /* Because this function needs to wait for completion of finish   */
            /* event notification.                                            */
            /* If WdgM_CheckpointReached() continues to return with E_NOT_OK, */
            /* watchdog timeout occurs.                                       */
            (void)WdgM_CheckpointReached(WDGM_ENTITYID_BASE, WDGM_CHKPNTID_0);

            WdgM_MainFunction();

            SubMiconIf_MainFunction();
        }
    }

    return;
}
#endif

#define SCHM_RPRG_STOP_SEC_CODE
#include <SchM_Rprg_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/06/19 :Update                                rel.AUBASS */
/*  v3.00       :2019/07/16 :Update                                rel.AUBASS */
/*  v4.00       :2022/10/04 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

