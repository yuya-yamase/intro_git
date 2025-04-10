/* DiagSrv_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/CODE                                                */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <DiagLib.h>
#include <Rte.h>
#include <ReprogOpt.h>

#include <DiagSrv.h>
#include "DiagSrv_Cfg.h"
#include "DiagSrv_Local.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_API_ID_PROCESSING (0x01U)

#define DIAGSRV_E_OPSTAT          (0x01U)

#define DIAGSRV_ENTRYPARM_SUBM_POS          ((uint8)5U)
#define DIAGSRV_ENTRYPARM_SUBM_UNMATCH_VAL  ((uint8)0xF0U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_VAR
#include <DiagSrv_MemMap.h>

static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_MainServiceId;

#define DIAGSRV_STOP_SEC_VAR
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define DIAGSRV_START_SEC_CODE
#include <DiagSrv_MemMap.h>

/******************************************************************************/
/* Function Name | DiagSrv_Init                                               */
/* Description   | Initializes DiagSrv                                        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_SLOW) DiagSrv_Init (void)
{
    VAR(uint8, AUTOMATIC) i;
    VAR(uint8, AUTOMATIC) BootMode;
    VAR(uint8, AUTOMATIC) BootModeEx;
    VAR(uint8, AUTOMATIC) ApEntryFlag;
    P2CONST(Rte_UsrSoftIf_EntryParamType, AUTOMATIC, DIAGSRV_APPL_CONST) Param;

    BootModeEx = DIAGSRV_EXT_BOOT_MODE_BOOT;

    BootMode = Rte_EcuM_GetBootMode();
    if( BootMode == RTE_ECUM_START_AP_ENTRY )
    {
        ApEntryFlag = STD_ON;
        BootModeEx = DIAGSRV_EXT_BOOT_MODE_APL;
        if( (ReprogOpt_SubMiconConfig == REPROGOPT_SUBMICON_TYPE_MAIN) || (ReprogOpt_SubMiconConfig == REPROGOPT_SUBMICON_TYPE_SUB) )
        {
            Param = Rte_UsrSoftIf_GetEntryParam();
            if( Param->EntryParam[DIAGSRV_ENTRYPARM_SUBM_POS] == DIAGSRV_ENTRYPARM_SUBM_UNMATCH_VAL )
            {
                ApEntryFlag = STD_OFF;
                BootModeEx = DIAGSRV_EXT_BOOT_MODE_UNMATCH;
            }
        }

        if( ApEntryFlag == (uint8)STD_ON )
        {
            DiagLib_SetSession(DiagSrv_ApEntryConfig.Session, DIAG_CHGSESSION_FACT_INIT);
            if( DiagSrv_ApEntryConfig.Security == DIAG_SECURITY_LOCK )
            {
                DiagLib_SetSecurityLockAll();
            }
            else
            {
                DiagLib_SetSecurityUnlockAll();
            }
        }
    }
#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
    else if( BootMode == RTE_ECUM_START_STAYINBOOT_ENTRY )
    {
        BootModeEx = DIAGSRV_EXT_BOOT_MODE_STAYINBOOT;
    }
#endif
    else
    {
        /* No process */
    }

    DiagSrv_MainServiceId = 0U;
    DiagSrv_lib_Init(BootModeEx);

    for( i = 0U; i < DiagSrv_SidFuncConfig.SidNum; i++ )
    {
        if( DiagSrv_SidFuncConfig.InfoPtr[i].InitFunc != NULL_PTR )
        {
            DiagSrv_SidFuncConfig.InfoPtr[i].InitFunc();
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_Processing                                         */
/* Description   | ProcessingFunction                                         */
/* Preconditions |                                                            */
/* Parameters    | [IN] Op  : Operation status                                */
/*               |       DIAG_INITIAL                                         */
/*               |       DIAG_CANCEL                                          */
/*               | [IN] Msg : Message                                         */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_SLOW) DiagSrv_Processing
(
    VAR(uint8, AUTOMATIC) Op,
    P2VAR(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_DATA) Msg
)
{
    VAR(uint8, AUTOMATIC) i;
    VAR(uint8, AUTOMATIC) Sid;
    VAR(Rte_EcuM_ErrorType, AUTOMATIC) Error;

    if( Op == DIAG_INITIAL )
    {
        Sid = DIAG_GET_SID(Msg);

        for( i = 0U; i < DiagSrv_SidFuncConfig.SidNum; i++ )
        {
            if( ( Sid == DiagSrv_SidFuncConfig.InfoPtr[i].Sid ) &&
                ( DiagSrv_SidFuncConfig.InfoPtr[i].ProcessingFunc != NULL_PTR ) )
            {
                DiagSrv_MainServiceId = Sid;
                DiagSrv_SidFuncConfig.InfoPtr[i].ProcessingFunc(Msg);
                break;
            }
        }
    }
    else if( Op == DIAG_CANCEL )
    {
        /* Execute initialization function on cancellation. */
        for( i = 0U; i < DiagSrv_SidFuncConfig.SidNum; i++ )
        {
            if( ( DiagSrv_MainServiceId == DiagSrv_SidFuncConfig.InfoPtr[i].Sid ) &&
                ( DiagSrv_SidFuncConfig.InfoPtr[i].InitFunc != NULL_PTR ) )
            {
                DiagSrv_SidFuncConfig.InfoPtr[i].InitFunc();
                break;
            }
        }
        DiagLib_CancelProcessingFinished(Msg);
        DiagSrv_MainServiceId = 0U;
    }
    else
    {
        Error.ModuleId = RTE_ECUM_MODULE_DIAGSRV;
        Error.ApiId = DIAGSRV_API_ID_PROCESSING;
        Error.ErrorId = DIAGSRV_E_OPSTAT;
        Rte_EcuM_ReportError(&Error);
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_Time                                               */
/* Description   | TimeFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_SLOW) DiagSrv_Time (void)
{
    VAR(uint8, AUTOMATIC) i;

    for( i = 0U; i < DiagSrv_SidFuncConfig.SidNum; i++ )
    {
        if( DiagSrv_SidFuncConfig.InfoPtr[i].TimeFunc != NULL_PTR )
        {
            DiagSrv_SidFuncConfig.InfoPtr[i].TimeFunc();
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_Confirmation                                       */
/* Description   | ConfirmationFunction                                       */
/* Preconditions |                                                            */
/* Parameters    | [IN] Status : Transmission status                          */
/*               |       DIAG_POSRSP_OK                                       */
/*               |       DIAG_POSRSP_NG                                       */
/*               |       DIAG_NEGRSP_OK                                       */
/*               |       DIAG_NEGRSP_NG                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_SLOW) DiagSrv_Confirmation
(
    VAR(uint8, AUTOMATIC) Status
)
{
    VAR(uint8, AUTOMATIC) i;

    for( i = 0U; i < DiagSrv_SidFuncConfig.SidNum; i++ )
    {
        if( ( DiagSrv_MainServiceId == DiagSrv_SidFuncConfig.InfoPtr[i].Sid ) &&
            ( DiagSrv_SidFuncConfig.InfoPtr[i].ConfirmationFunc != NULL_PTR ) )
        {
            DiagSrv_SidFuncConfig.InfoPtr[i].ConfirmationFunc(Status);
            break;
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_NotifyChangeSession                                */
/* Description   | Notifies change session to service of each                 */
/* Preconditions |                                                            */
/* Parameters    | [IN] OldSession : Before the changes                       */
/*               |       DIAG_SESSION_DEF                                     */
/*               |       DIAG_SESSION_PRG                                     */
/*               |       DIAG_SESSION_EXT                                     */
/*               | [IN] NewSession : After the changes                        */
/*               |       DIAG_SESSION_DEF                                     */
/*               |       DIAG_SESSION_PRG                                     */
/*               |       DIAG_SESSION_EXT                                     */
/*               | [IN] Factor     : Change factor                            */
/*               |       DIAG_CHGSESSION_FACT_INIT                            */
/*               |       DIAG_CHGSESSION_FACT_S3TIMEOUT                       */
/*               |       DIAG_CHGSESSION_FACT_SID10                           */
/*               |       DIAG_CHGSESSION_FACT_OTHER                           */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_SLOW) DiagSrv_NotifyChangeSession
(
    VAR(uint8, AUTOMATIC) OldSession,
    VAR(uint8, AUTOMATIC) NewSession,
    VAR(uint8, AUTOMATIC) Factor
)
{
    VAR(uint8, AUTOMATIC) i;

    /* Do not notify at initialization. */
    if( Factor != DIAG_CHGSESSION_FACT_INIT )
    {
        for( i = 0U; i < DiagSrv_SidFuncConfig.SidNum; i++ )
        {
            if( DiagSrv_SidFuncConfig.InfoPtr[i].ChangeSessionFunc != NULL_PTR )
            {
                DiagSrv_SidFuncConfig.InfoPtr[i].ChangeSessionFunc(OldSession, NewSession, Factor);
            }
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_GetMainServiceId                                   */
/* Description   | Acquires processing service ID                             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Processing SID                                             */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_SLOW) DiagSrv_GetMainServiceId (void)
{
    return DiagSrv_MainServiceId;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/


#define DIAGSRV_STOP_SEC_CODE
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/09/14 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

