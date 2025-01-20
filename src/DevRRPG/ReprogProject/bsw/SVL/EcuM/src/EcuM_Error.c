/* EcuM_Error_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | EcuM/Error/CODE                                             */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <EcuM.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    EcuM_ErrorType  ErrorData;
    uint8           ErrorFlg;
} EcuM_ErrorRecordType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define ECUM_START_SEC1_VAR
#include <EcuM_MemMap.h>

static VAR(EcuM_ErrorRecordType, ECUM_VAR_CLEARED) EcuM_ErrorRecord;

#define ECUM_STOP_SEC1_VAR
#include <EcuM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define ECUM_START_SEC1_CST
#include <EcuM_MemMap.h>

#define ECUM_STOP_SEC1_CST
#include <EcuM_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define ECUM_START_SEC1_CODE
#include <EcuM_MemMap.h>

/******************************************************************************/
/* Function Name | EcuM_ClearReportError                                      */
/* Description   | To clear the error information                             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | This function is called only once at the time of Startup.  */
/******************************************************************************/
FUNC(void, ECUM_CODE_SLOW) EcuM_ClearReportError (void)
{
    EcuM_ErrorRecord.ErrorData.ModuleId = 0U;
    EcuM_ErrorRecord.ErrorData.ApiId = 0U;
    EcuM_ErrorRecord.ErrorData.ErrorId = 0U;
    EcuM_ErrorRecord.ErrorFlg = STD_OFF;

    return;
}

/******************************************************************************/
/* Function Name | EcuM_CheckError                                            */
/* Description   | Check whether an error has occurred                        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, ECUM_CODE_SLOW) EcuM_CheckError (void)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_OK;

    if( EcuM_ErrorRecord.ErrorFlg != (uint8)STD_OFF )
    {
        Ret = E_NOT_OK;
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | EcuM_ReportError                                           */
/* Description   | Notified of the error information                          */
/* Preconditions |                                                            */
/* Parameters    | [IN] ErrorInfo : Error information                         */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, ECUM_CODE_SLOW) EcuM_ReportError
(
    P2CONST(EcuM_ErrorType, AUTOMATIC, ECUM_APPL_CONST) ErrorInfo
)
{
    if( ErrorInfo != NULL_PTR )
    {
        if( EcuM_ErrorRecord.ErrorFlg == (uint8)STD_OFF )
        {
            EcuM_ErrorRecord.ErrorFlg = STD_ON;
            EcuM_ErrorRecord.ErrorData.ModuleId = ErrorInfo->ModuleId;
            EcuM_ErrorRecord.ErrorData.ApiId = ErrorInfo->ApiId;
            EcuM_ErrorRecord.ErrorData.ErrorId = ErrorInfo->ErrorId;
        }
    }

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define ECUM_STOP_SEC1_CODE
#include <EcuM_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

