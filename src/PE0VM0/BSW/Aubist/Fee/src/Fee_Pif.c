/* Fee_Pif.c v2-0-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/PIF/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee.h>
#include "../inc/Fee_Common.h"
#include "../inc/Fee_Pif.h"
#include "../inc/Fee_Pif_Internal.h"
#include <Mscd_Common.h>
#include "../inc/Fee_PifExt.h"
#include "../inc/Fee_Legacy.h"
#include "../usr/Fee_DevCallout.h"

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

#define FEE_START_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

VAR  ( MemIf_JobResultType, FEE_VAR_NO_INIT )          Fee_RequestResult;

#define FEE_STOP_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#define FEE_START_SEC_CONST_32
#include <Fee_MemMap.h>

/* Fee module version information */
CONST( AB_83_ConstV Std_VersionInfoType, FEE_CONST ) Fee_Pif_VersionInfo = {
    FEE_VENDOR_ID,          /* vendorID          */
    FEE_MODULE_ID,          /* moduleID          */
    FEE_SW_MAJOR_VERSION,   /* sw_major_version  */
    FEE_SW_MINOR_VERSION,   /* sw_minor_version  */
    FEE_SW_PATCH_VERSION    /* sw_patch_version  */
};

#define FEE_STOP_SEC_CONST_32
#include <Fee_MemMap.h>

#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Fee_Init                                                 */
/* Description   | Service to initialize the FEE module.                    */
/* Preconditions | None                                                     */
/* Parameters    | ConfigPtr : Pointer to configuration                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Init(
    P2CONST( Fee_ConfigType, AUTOMATIC, FEE_CONFIG_DATA ) ConfigPtr
){
    Fee_Pif_RamInit();
    Fee_PifExt_Init();
    Fee_Legacy_PwonInit();

    return;
}

/****************************************************************************/
/* Function Name | Fee_Read                                                 */
/* Description   | Service to initiate a read job.                          */
/* Preconditions | None                                                     */
/* Parameters    | BlockNumber   : Number of logical block, also denoting   */
/*               |                 start address of that block in EEPROM.   */
/*               | BlockOffset   : Read address offset inside the block     */
/*               | DataBufferPtr : Pointer to data buffer                   */
/*               | Length        : Number of bytes to read                  */
/* Return Value  | Request result                                           */
/*               |  E_OK     : The requested job has been accepted by the   */
/*               |             module.                                      */
/*               |  E_NOT_OK : The requested job has not been accepted by   */
/*               |             the module.                                  */
/* Notes         | Unused parameter BlockOffset and Length.                 */
/****************************************************************************/
FUNC( Std_ReturnType, FEE_CODE )
Fee_Read(
    uint16 BlockNumber,
    uint16 BlockOffset,
    P2VAR( uint8, AUTOMATIC, TYPEDEF ) DataBufferPtr,
    uint16 Length
){
    Std_ReturnType Rtn;
    Std_ReturnType ChkDevSetting;
    Std_ReturnType ReqParamGetResult;
    uint8          ReqResult;
    uint8          AreaNo;

    ReqResult = FEE_REQUEST_DECLINE;

    ChkDevSetting = Fee_DevCheckRequestAccept();
    if( ChkDevSetting == (Std_ReturnType)E_OK )
    {
        AreaNo = FEE_PIF_AREANO_INVALID;
        ReqParamGetResult = Fee_Pif_GetAreaNoFromBlockNumber( BlockNumber, &AreaNo );
        if( ReqParamGetResult == (Std_ReturnType)E_OK )
        {
            ReqResult = Fee_Legacy_ReadData( BlockNumber, AreaNo, DataBufferPtr );
        }
    }

    if( ReqResult == FEE_REQUEST_ACCEPT )
    {
        Fee_PifExt_AcceptedReadJobNotification( BlockNumber );
        Fee_RequestResult = MEMIF_JOB_PENDING;
        Rtn = E_OK;
    }
    else /* ReqResult == FEE_REQUEST_DECLINE */
    {
        Fee_Pif_RejectRequestHook( ReqResult );
        Rtn = E_NOT_OK;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Write                                                */
/* Description   | Service to initiate a write job.                         */
/* Preconditions | None                                                     */
/* Parameters    | BlockNumber   : Number of logical block, also denoting   */
/*               |                 start address of that block in EEPROM.   */
/*               | DataBufferPtr : Pointer to data buffer                   */
/* Return Value  | Request result                                           */
/*               |  E_OK     : The requested job has been accepted by the   */
/*               |             module.                                      */
/*               |  E_NOT_OK : The requested job has not been accepted by   */
/*               |             the module.                                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, FEE_CODE )
Fee_Write(
    uint16 BlockNumber,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) DataBufferPtr
){
    Std_ReturnType Rtn;
    Std_ReturnType ChkDevSetting;
    Std_ReturnType ReqParamGetResult;
    uint8          ReqResult;
    uint8          AreaNo;
    boolean        IsIntentRbldBlockNumber;

    ReqResult = FEE_REQUEST_DECLINE;

    ChkDevSetting = Fee_DevCheckRequestAccept();
    if( ChkDevSetting == (Std_ReturnType)E_OK )
    {
        AreaNo = FEE_PIF_AREANO_INVALID;
        ReqParamGetResult = Fee_Pif_GetAreaNoFromBlockNumber( BlockNumber, &AreaNo );
        if( ReqParamGetResult == (Std_ReturnType)E_OK )
        {
            IsIntentRbldBlockNumber = Fee_Pif_IsIntentionalRebuildBlockNumber( AreaNo, BlockNumber );
            if( IsIntentRbldBlockNumber == (boolean)FALSE )
            {
                ReqResult = Fee_Legacy_WriteData( BlockNumber, DataBufferPtr ,AreaNo );
            }
            else
            {
                ReqResult = Fee_Legacy_Rebuild( AreaNo );
            }
        }
    }

    if( ReqResult == FEE_REQUEST_ACCEPT )
    {
        Fee_PifExt_AcceptedWriteJobNotification( BlockNumber );
        Fee_RequestResult = MEMIF_JOB_PENDING;
        Rtn = E_OK;
    }
    else /* ReqResult == FEE_REQUEST_DECLINE, FEE_REQUEST_IRBLD_CNFM_NOT_OK */
    {
        Fee_Pif_RejectRequestHook( ReqResult );
        Rtn = E_NOT_OK;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Cancel                                               */
/* Description   | Service to call the cancel function of the underlying    */
/*               | flash driver.                                            */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE ) Fee_Cancel( void )
{
    Fee_Legacy_Abort();

    return;
}

/****************************************************************************/
/* Function Name | Fee_GetStatus                                            */
/* Description   | Service to return the status.                            */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Status                                                   */
/*               |  MEMIF_IDLE   :The FEE module is currently idle.         */
/*               |  MEMIF_BUSY   :The FEE module is currently busy.         */
/*               |  MEMIF_BUSY_INTERNAL :The FEE module is busy with        */
/*               |                       internal management operations.    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( MemIf_StatusType, FEE_CODE ) Fee_GetStatus( void )
{
    MemIf_StatusType Rtn;
    uint8 GetStatusResult;

    GetStatusResult = Fee_Legacy_GetStatus();
    if( GetStatusResult == FEE_IDLING )
    {
        Rtn = MEMIF_IDLE;
    }
    else if( GetStatusResult == FEE_DFC_ERROR )
    {
        Rtn = MEMIF_BUSY_INTERNAL;
    }
    else
    {
        Rtn = MEMIF_BUSY;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_GetJobResult                                         */
/* Description   | Service to query the result of the last accepted job     */
/*               | issued by the upper layer software.                      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | JobResult                                                */
/*               |  MEMIF_JOB_OK             :The last job has been         */
/*               |            finished successfully.                        */
/*               |  MEMIF_JOB_PENDING        :The last job is waiting for   */
/*               |            execution or currently being executed.        */
/*               |  MEMIF_JOB_CANCELED       :The last job has been         */
/*               |            canceled (which means it failed).             */
/*               |  MEMIF_JOB_FAILED         :The last job has not been     */
/*               |            finished successfully (it failed).            */
/*               |  MEMIF_BLOCK_INCONSISTENT :The requested block is        */
/*               |            inconsistent, it may contain corrupted data.  */
/*               |  MEMIF_BLOCK_INVALID      :The requested block has been  */
/*               |            invalidated, the requested read operation     */
/*               |            can not be performed.                         */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( MemIf_JobResultType, FEE_CODE ) Fee_GetJobResult( void )
{
    return Fee_RequestResult;

}

/****************************************************************************/
/* Function Name | Fee_GetVersionInfo                                       */
/* Description   | Service to return the version information of the FEE     */
/*               | module.                                                  */
/* Preconditions | None                                                     */
/* Parameters    | VersionInfoPtr : Pointer to standard version information */
/*               |                  structure.                              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_GetVersionInfo(
    P2VAR( Std_VersionInfoType, AUTOMATIC, FEE_APPL_DATA ) VersionInfoPtr
){
    if( VersionInfoPtr != (Std_VersionInfoType *)NULL_PTR )
    {
        *( VersionInfoPtr ) = Fee_Pif_VersionInfo;
    }
    
    return;
}

/****************************************************************************/
/* Function Name | Fee_MainFunction                                         */
/* Description   | Service to handle the requested read/write/erase         */
/*               | jobs and the internal management operations.             */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE ) Fee_MainFunction( void )
{
    Fee_Legacy_PeriodicFunc();

    return;
}

/****************************************************************************/
/* Function Name | Fee_Pif_WriteEndNotification                             */
/* Description   | Function to notify the end of a write job.               */
/* Preconditions | None                                                     */
/* Parameters    | JobResult  : The result of the last accepted job         */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE ) Fee_Pif_WriteEndNotification(
    uint8   JobResult
){
    if( JobResult != FEE_RSP_OK )
    {
        Fee_Pif_WriteErrorResponseHook( JobResult );
    }

    if( ( JobResult == FEE_RSP_OK ) || ( JobResult == FEE_RSP_NG_INITIALIZE ) )
    {
        Fee_PifExt_WriteJobSuccessNotification();
        Fee_RequestResult = MEMIF_JOB_OK;
        NvM_JobEndNotification();
    }
    else
    {
        Fee_RequestResult = MEMIF_JOB_FAILED;
        NvM_JobErrorNotification();
    }

    return;
}

/****************************************************************************/
/* Function Name | Fee_Pif_ReadEndNotification                              */
/* Description   | Function to notify the end of a read job.                */
/* Preconditions | None                                                     */
/* Parameters    | JobResult  : The result of the last accepted job         */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE ) Fee_Pif_ReadEndNotification(
    uint8   JobResult
){
    if( JobResult != FEE_RSP_OK )
    {
        Fee_Pif_ReadErrorResponseHook( JobResult );
    }

    if( JobResult == FEE_RSP_OK )
    {
        Fee_PifExt_ReadJobSuccessNotification();
        Fee_RequestResult = MEMIF_JOB_OK;
        NvM_JobEndNotification();
    }
    else
    {
        if( ( JobResult == FEE_RSP_NODATA ) || ( JobResult == FEE_RSP_UNUSED ) )
        {
            Fee_RequestResult = MEMIF_BLOCK_INCONSISTENT;
        }
        else
        {
            Fee_RequestResult = MEMIF_JOB_FAILED;
        }
        NvM_JobErrorNotification();
    }

    return;
}

/****************************************************************************/
/* Function Name | Fee_Pif_RebuildEndNotification                           */
/* Description   | Function to notify the end of a intentional rebuild job. */
/* Preconditions | None                                                     */
/* Parameters    | JobResult  : The result of the last accepted job         */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE ) Fee_Pif_RebuildEndNotification(
    uint8   JobResult
){
    if( JobResult != FEE_RSP_OK )
    {
        Fee_Pif_RebuildErrorResponseHook( JobResult );
    }

    if( ( JobResult == FEE_RSP_OK ) || ( JobResult == FEE_RSP_NG_INITIALIZE ) )
    {
        Fee_PifExt_WriteJobSuccessNotification();
        Fee_RequestResult = MEMIF_JOB_OK;
        NvM_JobEndNotification();
    }
    else
    {
        Fee_RequestResult = MEMIF_JOB_FAILED;
        NvM_JobErrorNotification();
    }

    return;
}

/****************************************************************************/
/* Function Name | Fee_Pif_CancelEndNotification                            */
/* Description   | Function to notify the end of canceling.                 */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Pif_CancelEndNotification( void )
{
    Fee_PifExt_CancelNotification();
    
    if( Fee_RequestResult == MEMIF_JOB_PENDING )
    {
        Fee_RequestResult = MEMIF_JOB_CANCELED;
        NvM_JobErrorNotification();
    }
    else if( ( Fee_RequestResult != MEMIF_JOB_OK )
          && ( Fee_RequestResult != MEMIF_JOB_FAILED )
          && ( Fee_RequestResult != MEMIF_JOB_CANCELED )
          && ( Fee_RequestResult != MEMIF_BLOCK_INCONSISTENT ) )
    {
        /* Ram garbled */
        Fee_RequestResult = MEMIF_JOB_CANCELED;
        NvM_JobErrorNotification();
    }
    else
    {
        /* No process */
    }

    return;
}

/****************************************************************************/
/* Function Name | Fee_Pif_AbortEndNotification                             */
/* Description   | Function to notify the end of abort.                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Pif_AbortEndNotification( void )
{
    if( Fee_RequestResult == MEMIF_JOB_PENDING )
    {
        Fee_RequestResult = MEMIF_JOB_FAILED;
        Mscd_ErrorInfo_UpdateErrorResult( MSCD_ERRINFO_FEE_ERR_NG_INTERNAL );
        NvM_JobErrorNotification();
    }

    return;
}

/****************************************************************************/
/* Function Name | Fee_Pif_GetAreaNoFromBlockNumber                         */
/* Description   | Function to get area number from BlockNumber.            */
/* Preconditions | None                                                     */
/* Parameters    | SrcBlockNumber : Number of logical block for write/read. */
/*               | DstAreaNo      : Output value. An area number.           */
/* Return Value  | Result.                                                  */
/*               |  E_OK     : An area number have been gotten.             */
/*               |  E_NOT_OK : An area number have not been gotten.         */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, FEE_CODE ) Fee_Pif_GetAreaNoFromBlockNumber(
    uint16 SrcBlockNumber,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DstAreaNo
){
    Std_ReturnType  Rtn = E_NOT_OK;
    Std_ReturnType  GetCfgTblIdxRslt;
    uint16          TableIndex;
    uint8           AreaNo;
    uint8           AreaNum;

    GetCfgTblIdxRslt = Fee_Pif_GetCfgTblIdxFromBlockNumber( SrcBlockNumber, &TableIndex );
    if( GetCfgTblIdxRslt == (Std_ReturnType)E_OK )
    {
        AreaNo = FeeBlockConfigurations[TableIndex];
        AreaNum = Fee_AreaNumber;
        if( AreaNo < AreaNum )
        {
            *DstAreaNo = AreaNo;
            Rtn = E_OK;
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Pif_GetCfgTblIdxFromBlockNumber                      */
/* Description   | Function to get an index of FeeBlockConfigurations       */
/*               | and FeeRecPosTblIdx from a BlockNumber.                  */
/* Preconditions | None                                                     */
/* Parameters    | SrcBlockNumber : Number of logical block for write/read. */
/*               | DstCfgTblIdx   : Output value. An index.                 */
/* Return Value  | Result.                                                  */
/*               |  E_OK     : An index have been gotten.                   */
/*               |  E_NOT_OK : An index have not been gotten.               */
/*               |             BlockNumber is out of range.                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, FEE_CODE )
Fee_Pif_GetCfgTblIdxFromBlockNumber(
    uint16 SrcBlockNumber,
    P2VAR( uint16, AUTOMATIC, AUTOMATIC ) DstCfgTblIdx
){
    Std_ReturnType  Rtn = E_NOT_OK;
    uint16          FeeBlockId;
    uint16          TableIndex;
    uint16          BlockConfigSize;

    FeeBlockId = Fee_Pif_GetFeeBlockIdFromBlockNumber( SrcBlockNumber );
    if( FeeBlockId >= (uint16)FEE_PIF_BLK_CFG_ACCESS_OFFSET )
    {
        TableIndex = FeeBlockId - (uint16)FEE_PIF_BLK_CFG_ACCESS_OFFSET;
        BlockConfigSize = FeeBlockConfigurationsSize;
        if( TableIndex < BlockConfigSize )
        {
            *DstCfgTblIdx = TableIndex;
            Rtn = E_OK;
        }
    }

    return Rtn;
}

#if (FEE_RECORDPOSTBL_ENABLE == STD_ON) 
/****************************************************************************/
/* Function Name | Fee_Pif_GetDatasetIdxFromBlockNumber                     */
/* Description   | Function to get a dataset index from a BlockNumber.      */
/* Preconditions | None                                                     */
/* Parameters    | SrcBlockNumber : Number of logical block for write/read. */
/*               | DstDatasetIdx  : Output value. An index.                 */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Pif_GetDatasetIdxFromBlockNumber(
    uint16 SrcBlockNumber,
    P2VAR( uint16, AUTOMATIC, AUTOMATIC ) DstDatasetIdx
){
    uint16 MaskVal;

    MaskVal = Fee_DatasetIndexMask;
    *DstDatasetIdx = SrcBlockNumber & MaskVal;

    return;
}
#endif /* FEE_RECORDPOSTBL_ENABLE == STD_ON */ 

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Fee_Pif_RamInit                                          */
/* Description   | Function to initialize RAMs of this unit.                */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE ) Fee_Pif_RamInit( void )
{
    Fee_RequestResult = MEMIF_JOB_OK;

    return;
}

/****************************************************************************/
/* Function Name | Fee_Pif_RejectRequestHook                                */
/* Description   | Function to report rejection of a request.               */
/* Preconditions | None                                                     */
/* Parameters    | ReqResult                                                */
/*               |      FEE_REQUEST_IRBLD_CNFM_NOT_OK                       */
/*               |      FEE_REQUEST_DECLINE                                 */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Pif_RejectRequestHook(
    uint8 ReqResult
){
    if( ReqResult == FEE_REQUEST_IRBLD_CNFM_NOT_OK )
    {
        Mscd_ErrorInfo_UpdateErrorResult( MSCD_ERRINFO_FEE_ERR_IRBLD_CNFM_NOT_OK );
    }
    else /* ReqResult == FEE_REQUEST_DECLINE or others */
    {
        Mscd_ErrorInfo_UpdateErrorResult( MSCD_ERRINFO_FEE_ERR_NG_INTERNAL );
    }

    return;
}

/****************************************************************************/
/* Function Name | Fee_Pif_WriteErrorResponseHook                           */
/* Description   | Function to report an error of a write job.              */
/* Preconditions | None                                                     */
/* Parameters    | JobResult : The result of the last accepted write job    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE ) Fee_Pif_WriteErrorResponseHook(
    uint8 JobResult
){
    uint32 ErrorResult;

    if( JobResult == FEE_RSP_NG )
    {
        ErrorResult = MSCD_ERRINFO_FEE_ERR_NG_WRITE;
    }
    else if( JobResult == FEE_RSP_NG_DTF_CTRL )
    {
        ErrorResult = MSCD_ERRINFO_FEE_ERR_NG_DTF_CTRL;
    }
    else if( JobResult == FEE_RSP_TIMEOUT )
    {
        ErrorResult = MSCD_ERRINFO_FEE_ERR_TIMEOUT;
    }
    else if( JobResult == FEE_RSP_NG_INITIALIZE )
    {
        ErrorResult = MSCD_ERRINFO_FEE_ERR_VANISH_AREA;
    }
    else if( JobResult == FEE_RSP_NG_WRITE_DATA )
    {
        ErrorResult = MSCD_ERRINFO_FEE_ERR_NG_WRITE;
    }
    else if( JobResult == FEE_RSP_NG_NODATA )
    {
        ErrorResult = (uint32)MSCD_ERRINFO_FEE_ERR_VANISH_AREA | (uint32)MSCD_ERRINFO_FEE_ERR_NG_WRITE;
    }
    else /* FEE_RSP_GARBLED_RAM or other */
    {
        /* Ram garbled */
        ErrorResult = MSCD_ERRINFO_FEE_ERR_NG_INTERNAL;
    }

    Mscd_ErrorInfo_UpdateErrorResult( ErrorResult );

    return;
}

/****************************************************************************/
/* Function Name | Fee_Pif_ReadErrorResponseHook                            */
/* Description   | Function to report an error of a read job.               */
/* Preconditions | None                                                     */
/* Parameters    | JobResult : The result of the last accepted read job     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE ) Fee_Pif_ReadErrorResponseHook(
    uint8 JobResult
){
    uint32 ErrorResult;
    boolean UpdateFlag = TRUE;

    if( JobResult == FEE_RSP_NG_DTF_CTRL )
    {
        ErrorResult = MSCD_ERRINFO_FEE_ERR_NG_DTF_CTRL;
    }
    else if( JobResult == FEE_RSP_TIMEOUT )
    {
        ErrorResult = MSCD_ERRINFO_FEE_ERR_TIMEOUT;
    }
    else if( JobResult == FEE_RSP_NODATA )
    {
        UpdateFlag = FALSE;
    }
    else if( JobResult == FEE_RSP_UNUSED )
    {
        ErrorResult = MSCD_ERRINFO_FEE_ERR_UNUSED;
    }
    else /* FEE_RSP_GARBLED_RAM or other */
    {
        /* Ram garbled */
        ErrorResult = MSCD_ERRINFO_FEE_ERR_NG_INTERNAL;
    }

    if( UpdateFlag == (boolean)TRUE )
    {
        Mscd_ErrorInfo_UpdateErrorResult( ErrorResult );
    }

    return;
}

/****************************************************************************/
/* Function Name | Fee_Pif_RebuildErrorResponseHook                         */
/* Description   | Function to report an error of a intentional rebuild job.*/
/* Preconditions | None                                                     */
/* Parameters    | JobResult : The result of the last accepted write job    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE ) Fee_Pif_RebuildErrorResponseHook(
    uint8 JobResult
){
    uint32 ErrorResult;

    if( JobResult == FEE_RSP_NG )
    {
        ErrorResult = MSCD_ERRINFO_FEE_ERR_NG_WRITE;
    }
    else if( JobResult == FEE_RSP_NG_DTF_CTRL )
    {
        ErrorResult = MSCD_ERRINFO_FEE_ERR_NG_DTF_CTRL;
    }
    else if( JobResult == FEE_RSP_TIMEOUT )
    {
        ErrorResult = MSCD_ERRINFO_FEE_ERR_TIMEOUT;
    }
    else if( JobResult == FEE_RSP_NG_INITIALIZE )
    {
        ErrorResult = MSCD_ERRINFO_FEE_ERR_VANISH_AREA;
    }
    else if( JobResult == FEE_RSP_NG_NODATA )
    {
        ErrorResult = (uint32)MSCD_ERRINFO_FEE_ERR_VANISH_AREA | (uint32)MSCD_ERRINFO_FEE_ERR_NG_WRITE;
    }
    else /* FEE_RSP_GARBLED_RAM or other */
    {
        /* Ram garbled */
        ErrorResult = MSCD_ERRINFO_FEE_ERR_NG_INTERNAL;
    }

    Mscd_ErrorInfo_UpdateErrorResult( ErrorResult );

    return;
}

/****************************************************************************/
/* Function Name | Fee_Pif_GetFeeBlockIdFromBlockNumber                     */
/* Description   | Function to get an FeeBlockId from a BlockNumber.        */
/* Preconditions | None                                                     */
/* Parameters    | SrcBlockNumber : Number of logical block for write/read. */
/* Return Value  | FeeBlockId                                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint16, FEE_CODE )
Fee_Pif_GetFeeBlockIdFromBlockNumber(
    uint16 SrcBlockNumber
){
    uint16          FeeBlockId;

    /* BlockBaseNumber and FeeBlockId is the same value */
    FeeBlockId = (uint16)( SrcBlockNumber >> Fee_DatasetSelectionBits );

    return FeeBlockId;
}

/****************************************************************************/
/* Function Name | Fee_Pif_IsIntentionalRebuildBlockNumber                  */
/* Description   | Function to return that BlockNumber is for intentional   */
/*               | rebuild or not.                                          */
/* Preconditions | None                                                     */
/* Parameters    | AreaNo      : Area number                                */
/*               | BlockNumber : Number of logical block                    */
/* Return Value  | Judge result                                             */
/*               |  TRUE  : The BlockNumber is for intentional rebuild      */
/*               |  FALSE : The BlockNumber is not for intentional rebuild  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( boolean, FEE_CODE )
Fee_Pif_IsIntentionalRebuildBlockNumber(
    uint8 AreaNo,
    uint16 BlockNumber
){
    boolean         IsIntentRbldBlockNumber = FALSE;
    uint16          FeeBlockId;
    uint8           IntentRebuildEnable     = Fee_IntentRebuildEnable;

    if( IntentRebuildEnable == (uint8)STD_ON )
    {
        FeeBlockId = Fee_Pif_GetFeeBlockIdFromBlockNumber( BlockNumber );
        if( Fee_AreaInfTBL[AreaNo].u2IntentRbldBlockId == FeeBlockId )
        {
            IsIntentRbldBlockNumber = TRUE;
        }
    }

    return IsIntentRbldBlockNumber;
}

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/08/27                                              */
/*  2-0-0          :2022/08/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
