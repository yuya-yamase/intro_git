/* Fee_PifExt.c v2-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/PIFEXT/CODE                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee.h>
#include <Fee_Ext.h>
#include "../inc/Fee_Common.h"
#include "../inc/Fee_PifExt.h"
#include "../inc/Fee_PifExt_Internal.h"
#include <Mscd_Common.h>
#include <Fls.h>
#include "../inc/Fee_DfcMpu.h"
#include "../inc/Fee_Legacy.h"
#include "../inc/Fee_FlsWrp.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

VAR( Fee_ExtDirect_ReturnType, FEE_VAR_NO_INIT )            Fee_PifExt_DirectJobResultData;
VAR( MemIf_ExtProductionErrorType, FEE_VAR_NO_INIT )        Fee_PifExt_ProductionError;
VAR( uint16, FEE_VAR_NO_INIT )                              Fee_PifExt_AcceptedJobBlockNumber;
VAR( uint8, FEE_VAR_NO_INIT )                               Fee_PifExt_AcceptedJobKind;

#define FEE_STOP_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Fee_MainFunction_ExtNonPeriodic                          */
/* Description   | Service to handle the jobs non-periodically.             */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE ) Fee_MainFunction_ExtNonPeriodic( void )
{
    Fee_Legacy_NonPeriodicFunc();
    return;
}

/****************************************************************************/
/* Function Name | Fee_ExtDirectWrite                                       */
/* Description   | Service to Write with DirectAccess.                      */
/* Preconditions | None                                                     */
/* Parameters    | u4Address                                                */
/*               | u4Length                                                 */
/*               | ptWriteData                                              */
/* Return Value  | FEE_EXT_DRCT_JOB_ACCEPT                                  */
/*               | FEE_EXT_DRCT_JOB_NOT_ACCEPT                              */
/*               | FEE_EXT_DRCT_JOB_INOPERATIVE_HSM                         */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Fee_ExtDirect_ReturnType, FEE_CODE )
Fee_ExtDirectWrite(
    uint32 u4Address,
    uint32 u4Length,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) ptWriteData
){
    Fee_ExtDirect_ReturnType Ret = FEE_EXT_DRCT_JOB_NOT_ACCEPT;
    Std_ReturnType  FlsRet;
    
    if( u4Length <= (uint32)FEE_DFAI_RW_SIZE_MAX )
    {
        FlsRet = Fee_FlsWrp_Write( (Fls_AddressType)u4Address, ptWriteData, (Fls_LengthType)u4Length );
        if(FlsRet == (Std_ReturnType)E_OK)
        {
            Ret = FEE_EXT_DRCT_JOB_ACCEPT;
            Fee_PifExt_DirectJobResultData = FEE_EXT_DRCT_JOB_BUSY;
        }
    }
        
    return Ret;
}

/****************************************************************************/
/* Function Name | Fee_ExtDirectErase                                       */
/* Description   | Service to Erase with DirectAccess.                      */
/* Preconditions | None                                                     */
/* Parameters    | u4Address                                                */
/*               | u2SectorNum                                              */
/* Return Value  | FEE_EXT_DRCT_JOB_ACCEPT                                  */
/*               | FEE_EXT_DRCT_JOB_NOT_ACCEPT                              */
/*               | FEE_EXT_DRCT_JOB_INOPERATIVE_HSM                         */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Fee_ExtDirect_ReturnType, FEE_CODE )
Fee_ExtDirectErase(
    uint32 u4Address,
    uint16 u2SectorNum
){
    Fee_ExtDirect_ReturnType Ret = FEE_EXT_DRCT_JOB_NOT_ACCEPT;
    Std_ReturnType  FlsRet;
    uint32 EraseSize;
    
    EraseSize = (uint32)u2SectorNum * (uint32)FEE_DATA_FLASH_PHYS_SECTOR_SIZE;
    FlsRet = Fee_FlsWrp_Erase( (Fls_AddressType)u4Address, (Fls_LengthType)EraseSize );
    if(FlsRet == (Std_ReturnType)E_OK)
    { 
        Ret = FEE_EXT_DRCT_JOB_ACCEPT;
        Fee_PifExt_DirectJobResultData = FEE_EXT_DRCT_JOB_BUSY;
    }
    
    return Ret;
}

/****************************************************************************/
/* Function Name | Fee_ExtDirectMainFunction                                */
/* Description   | Service to Process Job with DirectAccess.                */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_ExtDirectMainFunction( void )
{
    MemIf_JobResultType FlsJobResult;
    
    Fee_FlsWrp_MainFunction();
    
    if( Fee_PifExt_DirectJobResultData == (Fee_ExtDirect_ReturnType)FEE_EXT_DRCT_JOB_BUSY )
    {
        FlsJobResult = Fee_FlsWrp_GetJobResult();
        if( FlsJobResult == (MemIf_JobResultType)MEMIF_JOB_PENDING )
        {
            /* Do Nothing  */
        }
        else if( FlsJobResult == (MemIf_JobResultType)MEMIF_JOB_OK )
        {
            Fee_PifExt_DirectJobResultData = FEE_EXT_DRCT_JOB_OK;
        }
        else if( FlsJobResult == (MemIf_JobResultType)MEMIF_JOB_CANCELED )
        {
            Fee_PifExt_DirectJobResultData = FEE_EXT_DRCT_JOB_CANCELED;
        }
        else if( FlsJobResult == (MemIf_JobResultType)MEMIF_JOB_FAILED )
        {
            Fee_PifExt_DirectJobResultData = FEE_EXT_DRCT_JOB_ERROR;
        }
        else if( FlsJobResult == (MemIf_JobResultType)MEMIF_JOB_FATALFAILED )
        {
            Fee_PifExt_DirectJobResultData = FEE_EXT_DRCT_JOB_FATALERROR;
        }
        else
        {
            Fee_PifExt_DirectJobResultData = FEE_EXT_DRCT_JOB_ERROR;
        }
    }
    
    Mscd_Msif_DfaiMFProcessResultNotification( MSCD_MAINFUNCTION_PROCESSED );
    
    return;
}
/****************************************************************************/
/* Function Name | Fee_ExtDirectGetStatus                                   */
/* Description   | Service to return the status of DirectAccess.            */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Fee_ExtDirectStatusType                                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Fee_ExtDirectStatusType, FEE_CODE )
Fee_ExtDirectGetStatus( void )
{
    Fee_ExtDirectStatusType Rtn;
    MemIf_StatusType        FlsStatus;

    FlsStatus = Fee_FlsWrp_GetStatus();
    if( FlsStatus == MEMIF_IDLE )
    {
        Rtn = FEE_EXT_DRCT_STATUS_IDLE;
    }
    else if( FlsStatus == MEMIF_BUSY )
    {
        Rtn = FEE_EXT_DRCT_STATUS_BUSY;
    }
    else if( FlsStatus == MEMIF_BUSY_INTERNAL )
    {
        Rtn = FEE_EXT_DRCT_STATUS_ERROR;
    }
    else if( FlsStatus == MEMIF_UNINIT )
    {
        Rtn = FEE_EXT_DRCT_STATUS_ERROR;
    }
    else
    {
        /* RAM garbled. */
        Rtn = FEE_EXT_DRCT_STATUS_ERROR;
    }

    return Rtn;
}
/****************************************************************************/
/* Function Name | Fee_ExtGetDirectJobResult                                */
/* Description   | Service to Get Job Result with DirectAccess.             */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Fee_ExtDirect_ReturnType                                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Fee_ExtDirect_ReturnType, FEE_CODE )
Fee_ExtGetDirectJobResult( void )
{
    return Fee_PifExt_DirectJobResultData;
}
/****************************************************************************/
/* Function Name | Fee_ExtDirectRead                                        */
/* Description   | Service to Read with DirectAccess.                       */
/* Preconditions | None                                                     */
/* Parameters    | u4Address                                                */
/*               | u4Length                                                 */
/*               | ptReadData                                               */
/* Return Value  | FEE_EXT_DRCT_JOB_OK                                      */
/*               | FEE_EXT_DRCT_JOB_ERROR                                   */
/*               | FEE_EXT_DRCT_JOB_INOPERATIVE_HSM                         */
/*               | FEE_EXT_DRCT_JOB_INTEGRITY_FAILED                        */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Fee_ExtDirect_ReturnType, FEE_CODE )
Fee_ExtDirectRead(
    uint32 u4Address,
    uint32 u4Length,
    P2VAR( uint8, AUTOMATIC, TYPEDEF ) ptReadData
){
    uint8                    ReadResult;
    Fee_ExtDirect_ReturnType Ret;

    ReadResult = Fee_DfcMpu_DirectRead( u4Address, ptReadData, u4Length );
    switch( ReadResult )
    {
        case FEE_DFCMPU_RESULT_OK:
            Ret = FEE_EXT_DRCT_JOB_OK;
            break;
        case FEE_DFCMPU_RESULT_INOPERATIVE_HSM:
            Ret = FEE_EXT_DRCT_JOB_INOPERATIVE_HSM;
            break;
        case FEE_DFCMPU_RESULT_INTEGRITY_FAILED:
            Ret = FEE_EXT_DRCT_JOB_INTEGRITY_FAILED;
            break;
        default:
            Ret = FEE_EXT_DRCT_JOB_ERROR;
            break;
    }

    return Ret;
}
/****************************************************************************/
/* Function Name | Fee_ExtDirectBlankCheck                                  */
/* Description   | Service to BlankCheck with DirectAccess.                 */
/* Preconditions | None                                                     */
/* Parameters    | u4Address                                                */
/*               | u4Length                                                 */
/* Return Value  | FEE_EXT_DRCT_JOB_BLANK                                   */
/*               | FEE_EXT_DRCT_JOB_NOT_BLANK                               */
/*               | FEE_EXT_DRCT_JOB_ERROR                                   */
/*               | FEE_EXT_DRCT_JOB_FATALERROR                              */
/*               | FEE_EXT_DRCT_JOB_INOPERATIVE_HSM                         */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Fee_ExtDirect_ReturnType, FEE_CODE )
Fee_ExtDirectBlankCheck(
    uint32 u4Address,
    uint32 u4Length
){
    uint8                    BlankCheckResult;
    Fee_ExtDirect_ReturnType Ret;

    BlankCheckResult = Fee_DfcMpu_DirectBlankCheck( u4Address, u4Length );
    switch( BlankCheckResult )
    {
        case FEE_DFCMPU_RESULT_OK:
            Ret = FEE_EXT_DRCT_JOB_BLANK;
            break;
        case FEE_DFCMPU_RESULT_NG_BLANKCHECK:
            Ret = FEE_EXT_DRCT_JOB_NOT_BLANK;
            break;
        case FEE_DFCMPU_RESULT_FATALERROR:
            Ret = FEE_EXT_DRCT_JOB_FATALERROR;
            break;
        case FEE_DFCMPU_RESULT_INOPERATIVE_HSM:
            Ret = FEE_EXT_DRCT_JOB_INOPERATIVE_HSM;
            break;
        default:
            Ret = FEE_EXT_DRCT_JOB_ERROR;
            break;
    }

    return Ret;
}

/****************************************************************************/
/* Function Name | Fee_ExtGetFreeSpace                                      */
/* Description   | Service to get free space sizes on data flash.           */
/* Preconditions | None                                                     */
/* Parameters    | AreaNo                                                   */
/*               | LimitSearchMngArea                                       */
/*               | LimitSearchDataArea                                      */
/*               | FreeSpaceInfoPtr                                         */
/* Return Value  | FEE_EXT_E_FRSP_OK                                        */
/*               | FEE_EXT_E_FRSP_PARAM_ERROR                               */
/*               | FEE_EXT_E_FRSP_BUSY                                      */
/*               | FEE_EXT_E_FRSP_AREA_FAULT                                */
/*               | FEE_EXT_E_FRSP_INTERNAL_ERROR                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Fee_ExtFreeSpaceReturnType, FEE_CODE )
Fee_ExtGetFreeSpace(
    uint8  AreaNo,
    uint16 LimitSearchMngArea,
    uint32 LimitSearchDataArea,
    P2VAR( Fee_ExtFreeSpaceInfoType, AUTOMATIC, TYPEDEF ) FreeSpaceInfoPtr
){
    Fee_ExtFreeSpaceReturnType Rtn;
    uint8                      MaxAreaNumber = Fee_AreaNumber;

    Rtn = FEE_EXT_E_FRSP_PARAM_ERROR;
    if( AreaNo < MaxAreaNumber )
    {
        if( FreeSpaceInfoPtr != NULL_PTR )
        {
            Rtn = Fee_Legacy_GetFreeSpace( AreaNo, LimitSearchMngArea, LimitSearchDataArea, FreeSpaceInfoPtr );
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_ExtGetProductionError                                */
/* Description   | Service to get detected production error.                */
/* Preconditions | None                                                     */
/* Parameters    | BlockNumber                                              */
/*               | JobKind                                                  */
/*               | Level                                                    */
/* Return Value  | MEMIF_E_EXT_ALLPASSED                                    */
/*               | MEMIF_E_EXT_REQ_FAILED                                   */
/*               | MEMIF_E_EXT_WRONG_BLOCK_ID                               */
/*               | MEMIF_E_EXT_VERIFY_FAILED                                */
/*               | MEMIF_E_EXT_LOSS_OF_REDUNDANCY                           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( MemIf_ExtProductionErrorType, FEE_CODE )
Fee_ExtGetProductionError(
    P2VAR(uint16, AUTOMATIC, TYPEDEF) BlockNumber,
    P2VAR(uint8, AUTOMATIC, TYPEDEF) JobKind,
    P2VAR(uint8, AUTOMATIC, TYPEDEF) Level
){
    if( BlockNumber != NULL_PTR )
    {
        *BlockNumber    = Fee_PifExt_AcceptedJobBlockNumber;
    }
    
    if( JobKind != NULL_PTR )
    {
        *JobKind        = Fee_PifExt_AcceptedJobKind;
    }
    
    if( Level != NULL_PTR )
    {
        *Level          = MEMIF_EXT_LEVEL_01;
    }

    return Fee_PifExt_ProductionError;
}

/****************************************************************************/
/* Function Name | Fee_PifExt_Init                                          */
/* Description   | Function to initialize the PIFExt.                       */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE ) 
Fee_PifExt_Init( void )
{
    Fee_PifExt_DirectJobResultData = FEE_EXT_DRCT_JOB_OK;
    Fee_PifExt_ProductionError     = MEMIF_E_EXT_ALLPASSED;
    return;
}

/****************************************************************************/
/* Function Name | Fee_PifExt_CancelNotification                            */
/* Description   | Service to cancel Notification                           */
/*               | direct job.                                              */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE ) 
Fee_PifExt_CancelNotification( void )
{
    if( Fee_PifExt_DirectJobResultData == (Fee_ExtDirect_ReturnType)FEE_EXT_DRCT_JOB_BUSY )
    {
        Fee_PifExt_DirectJobResultData = FEE_EXT_DRCT_JOB_CANCELED;
    }
    return;
}

/****************************************************************************/
/* Function Name | Fee_PifExt_WriteVerifyFailedNotification                 */
/* Description   | Function to set detected VerifyFailed error.             */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE ) Fee_PifExt_WriteVerifyFailedNotification( void )
{
    Fee_PifExt_ProductionError |= MEMIF_E_EXT_VERIFY_FAILED;
    
    return;
}

/****************************************************************************/
/* Function Name | Fee_PifExt_ReadJobSuccessNotification                    */
/* Description   | Function to initialize the production error.             */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE ) Fee_PifExt_ReadJobSuccessNotification( void )
{
    Fee_PifExt_ProductionError = MEMIF_E_EXT_ALLPASSED;
    
    return;
}

/****************************************************************************/
/* Function Name | Fee_PifExt_WriteJobSuccessNotification                   */
/* Description   | Function to cancel VerifyFailed error                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE ) Fee_PifExt_WriteJobSuccessNotification( void )
{
    Fee_PifExt_ProductionError &= (MemIf_ExtProductionErrorType)(~MEMIF_E_EXT_VERIFY_FAILED);
    
    return;
}

/****************************************************************************/
/* Function Name | Fee_PifExt_AcceptedReadJobNotification                   */
/* Description   | Function to set the accepted Read job information.       */
/* Preconditions | None                                                     */
/* Parameters    | Accepted Block Number                                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE ) Fee_PifExt_AcceptedReadJobNotification(
    uint16 BlockNumber
){
    Fee_PifExt_AcceptedJobBlockNumber   = BlockNumber;
    Fee_PifExt_AcceptedJobKind          = MEMIF_EXT_READ_JOB;
    Fee_PifExt_ProductionError          = MEMIF_E_EXT_ALLPASSED;
    
    return;
}

/****************************************************************************/
/* Function Name | Fee_PifExt_AcceptedWriteJobNotification                  */
/* Description   | Function to set the accepted Write job information.      */
/* Preconditions | None                                                     */
/* Parameters    | Accepted Block Number                                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE ) Fee_PifExt_AcceptedWriteJobNotification(
    uint16 BlockNumber
){
    Fee_PifExt_AcceptedJobBlockNumber   = BlockNumber;
    Fee_PifExt_AcceptedJobKind          = MEMIF_EXT_WRITE_JOB;
    Fee_PifExt_ProductionError          = MEMIF_E_EXT_ALLPASSED;
    
    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/08/23                                              */
/*  2-0-0          :2021/06/16                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
