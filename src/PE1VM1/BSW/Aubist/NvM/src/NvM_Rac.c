/* NvM_Rac.c v2-0-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/RAC/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes        | None                                                      */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <NvM.h>
#include "../inc/NvM_Internal.h"
#include "../inc/NvM_Rac.h"
#include "../inc/NvM_Rac_Internal.h"
#include "../inc/NvM_Evt.h"
#include "../inc/NvM_Adb.h"
#include "../inc/NvM_Romb.h"

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* Function Name | NvM_Rac_Init                                             */
/* Description   | The function for resetting this unit.                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Rac_Init( void )
{
    return;
}

/****************************************************************************/
/* Function Name | NvM_Rac_IsPReqSetBlockProtection                         */
/* Description   | The function for checking whether or not to accept       */
/*               | the request, NvM_SetBlockProtection.                     */
/* Preconditions | None                                                     */
/* Parameters    | BlockId           : The parameter of request,            */
/*               |                     BlockId.                             */
/*               | ProtectionEnabled : The parameter of request,            */
/*               |                     ProtectionEnabled.                   */
/* Return Value  | Std_ReturnType : Check result.                           */
/*               |  E_OK     : The request can be accepted.                 */
/*               |  E_NOT_OK : The request cannot be accepted.              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqSetBlockProtection(
    NvM_BlockIdType BlockId,
    boolean ProtectionEnabled
){
    Std_ReturnType  JudgementResult;
    Std_ReturnType  ChkBlockIdResult;
    Std_ReturnType  ChkBooleanValueResult;
    Std_ReturnType  ChkAdbJobStsResult;
    Std_ReturnType  ChkConfWriteOnceResult;

    JudgementResult = E_NOT_OK;

    ChkBlockIdResult = NvM_Rac_ChkBlockId( BlockId, NVM_SERVICE_ID_SETBLKPROTECT, FALSE );
    ChkBooleanValueResult = NvM_Rac_ChkBooleanValueRange( ProtectionEnabled );

    if( ( ChkBlockIdResult == (Std_ReturnType)E_OK )
     && ( ChkBooleanValueResult == (Std_ReturnType)E_OK ) )
    {
        ChkAdbJobStsResult = NvM_Rac_ChkAdbJobStatus( BlockId, NVM_SERVICE_ID_SETBLKPROTECT );
        ChkConfWriteOnceResult = NvM_Rac_ChkConfWriteOnce( BlockId, NVM_SERVICE_ID_SETBLKPROTECT );

        if( ( ChkAdbJobStsResult == (Std_ReturnType)E_OK )
         && ( ChkConfWriteOnceResult == (Std_ReturnType)E_OK ) )
        {
            JudgementResult = E_OK;
        }
    }

    /* The processing end */
    return JudgementResult;
}

/****************************************************************************/
/* Function Name | NvM_Rac_IsPReqGetErrorStatus                             */
/* Description   | The function for checking whether or not to accept       */
/*               | the request, NvM_GetErrorStatus.                         */
/* Preconditions | None                                                     */
/* Parameters    | BlockId          : The parameter of request,             */
/*               |                    BlockId.                              */
/*               | RequestResultPtr : The parameter of request,             */
/*               |                    RequestResultPtr.                     */
/* Return Value  | Std_ReturnType : Check result.                           */
/*               |  E_OK     : The request can be accepted.                 */
/*               |  E_NOT_OK : The request cannot be accepted.              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqGetErrorStatus(
    NvM_BlockIdType BlockId,
    P2CONST( NvM_RequestResultType, AUTOMATIC, NVM_APPL_DATA ) RequestResultPtr
){
    Std_ReturnType  JudgementResult;
    Std_ReturnType  ChkBlockIdResult;
    Std_ReturnType  ChkReqPtrResult;

    JudgementResult = E_NOT_OK;

    ChkBlockIdResult = NvM_Rac_ChkBlockId     ( BlockId,          NVM_SERVICE_ID_GETERRORSTS, TRUE );
    ChkReqPtrResult  = NvM_Rac_ChkReqResultPtr( RequestResultPtr, NVM_SERVICE_ID_GETERRORSTS );

    if(( ChkBlockIdResult == (Std_ReturnType)E_OK )
    && ( ChkReqPtrResult  == (Std_ReturnType)E_OK ))
    {
        JudgementResult = E_OK;
    }

    /* The processing end */
    return JudgementResult ;
}

/****************************************************************************/
/* Function Name | NvM_Rac_IsPReqGetVersionInfo                             */
/* Description   | The function for checking whether or not to accept       */
/*               | the request, NvM_GetVersionInfo.                         */
/* Preconditions | None                                                     */
/* Parameters    | VersionInfo : The parameter of request,                  */
/*               |               versioninfo.                               */
/* Return Value  | Std_ReturnType : Check result.                           */
/*               |  E_OK     : The request can be accepted.                 */
/*               |  E_NOT_OK : The request cannot be accepted.              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqGetVersionInfo(
    P2CONST( Std_VersionInfoType, AUTOMATIC, NVM_APPL_DATA ) VersionInfo
){
    Std_ReturnType  JudgementResult;
    Std_ReturnType  ChkVerInfoResult;
    JudgementResult = E_NOT_OK;

    ChkVerInfoResult = NvM_Rac_ChkVersionInfoPtr( VersionInfo, NVM_SERVICE_ID_GETVERSIONINF );

    if( ChkVerInfoResult == (Std_ReturnType)E_OK )
    {
        JudgementResult = E_OK;
    }

    /* The processing end */
    return JudgementResult;
}

/****************************************************************************/
/* Function Name | NvM_Rac_IsPReqSetRamBlockStatus                          */
/* Description   | The function for checking whether or not to accept       */
/*               | the request, NvM_SetRamBlockStatus.                      */
/* Preconditions | Set NVM_VALID_SET_RAM_BLOCK_STATUS_API to STD_ON.        */
/* Parameters    | BlockId      : The parameter of request,                 */
/*               |                BlockId.                                  */
/*               | BlockChanged : The parameter of request,                 */
/*               |                BlockChanged.                             */
/* Return Value  | Std_ReturnType : Check result.                           */
/*               |  E_OK     : The request can be accepted.                 */
/*               |  E_NOT_OK : The request cannot be accepted.              */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( NVM_VALID_SET_RAM_BLOCK_STATUS_API == STD_ON )
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqSetRamBlockStatus(
    NvM_BlockIdType BlockId,
    boolean BlockChanged
){
    Std_ReturnType  JudgementResult;
    Std_ReturnType  ChkBlockIdResult;
    Std_ReturnType  ChkAdbJobStsResult;
    Std_ReturnType  ChkConfRamBlkStsResult;
    Std_ReturnType  ChkConfRamBlockTypeResult;
    Std_ReturnType  ChkBooleanValueRangeResult;

    JudgementResult = E_NOT_OK;

    ChkBlockIdResult = NvM_Rac_ChkBlockId( BlockId, NVM_SERVICE_ID_SETRAMBLKSTS, FALSE );

    if( ChkBlockIdResult == (Std_ReturnType)E_OK )
    {
        ChkAdbJobStsResult = NvM_Rac_ChkAdbJobStatus( BlockId, NVM_SERVICE_ID_SETRAMBLKSTS );
        ChkConfRamBlkStsResult = NvM_Rac_ChkConfUseSetRamBlockStatus( BlockId );
        ChkConfRamBlockTypeResult = NvM_Rac_ChkConfRamBlockType( BlockId, NVM_SERVICE_ID_SETRAMBLKSTS );
        ChkBooleanValueRangeResult = NvM_Rac_ChkBooleanValueRange( BlockChanged );

        if( ( ChkAdbJobStsResult == (Std_ReturnType)E_OK )
         && ( ChkConfRamBlkStsResult == (Std_ReturnType)E_OK )
         && ( ChkConfRamBlockTypeResult == (Std_ReturnType)E_OK )
         && ( ChkBooleanValueRangeResult == (Std_ReturnType)E_OK ) )
        {
            JudgementResult = E_OK;
        }
    }

    /* The processing end */
    return JudgementResult;
}
#endif /* NVM_VALID_SET_RAM_BLOCK_STATUS_API == STD_ON */

/****************************************************************************/
/* Function Name | NvM_Rac_IsPReqCancelJobs                                 */
/* Description   | The function for checking whether or not to accept       */
/*               | the request, NvM_CancelJobs.                             */
/* Preconditions | None                                                     */
/* Parameters    | BlockId     : The parameter of request,                  */
/*               |               BlockId.                                   */
/* Return Value  | Std_ReturnType : Check result.                           */
/*               |  E_OK     : The request can be accepted.                 */
/*               |  E_NOT_OK : The request cannot be accepted.              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqCancelJobs(
    NvM_BlockIdType BlockId
){
    Std_ReturnType  JudgementResult;
    Std_ReturnType  ChkBlockIdResult;

    JudgementResult = E_NOT_OK;

    ChkBlockIdResult = NvM_Rac_ChkBlockId( BlockId, NVM_SERVICE_ID_CACNCELJOBS, FALSE );

    if( ChkBlockIdResult == (Std_ReturnType)E_OK )
    {
        JudgementResult = E_OK;
    }

    /* The processing end */
    return JudgementResult;
}

/****************************************************************************/
/* Function Name | NvM_Rac_IsPReqReadBlock                                  */
/* Description   | The function for checking whether or not to accept       */
/*               | the request, NvM_ReadBlock.                              */
/* Preconditions | None                                                     */
/* Parameters    | BlockId   : The parameter of request,                    */
/*               |             BlockId.                                     */
/*               | DstPtr    : The parameter of request,                    */
/*               |             DstPtr.                                      */
/* Return Value  | Std_ReturnType : Check result.                           */
/*               |  E_OK     : The request can be accepted.                 */
/*               |  E_NOT_OK : The request cannot be accepted.              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqReadBlock(
    NvM_BlockIdType BlockId,
    P2CONST( uint8, AUTOMATIC, NVM_APPL_DATA ) DstPtr
){
    Std_ReturnType  JudgementResult;
    Std_ReturnType  ChkBlockIdResult;
    Std_ReturnType  ChkAdbJobStsResult;
    Std_ReturnType  ChkConfRamTypeResult;

    JudgementResult = E_NOT_OK;

    ChkBlockIdResult = NvM_Rac_ChkBlockId( BlockId, NVM_SERVICE_ID_READBLK, FALSE );

    if( ChkBlockIdResult == (Std_ReturnType)E_OK )
    {
        ChkAdbJobStsResult = NvM_Rac_ChkAdbJobStatus( BlockId, NVM_SERVICE_ID_READBLK );
        ChkConfRamTypeResult = NvM_Rac_ChkConfRamBlockTypeAndPtr( BlockId, DstPtr, NVM_SERVICE_ID_READBLK );

        if( ( ChkAdbJobStsResult == (Std_ReturnType)E_OK ) 
         && ( ChkConfRamTypeResult == (Std_ReturnType)E_OK ) )
        {
            JudgementResult = E_OK;
        }
    }

    /* The processing end */
    return JudgementResult;
}

/****************************************************************************/
/* Function Name | NvM_Rac_IsPReqWriteBlock                                 */
/* Description   | The function for checking whether or not to accept       */
/*               | the request, NvM_WriteBlock.                             */
/* Preconditions | None                                                     */
/* Parameters    | BlockId   : The parameter of request,                    */
/*               |             BlockId.                                     */
/*               | SrcPtr    : The parameter of request,                    */
/*               |             SrcPtr.                                      */
/*               | in.                                                      */
/* Return Value  | Std_ReturnType : Check result.                           */
/*               |  E_OK     : The request can be accepted.                 */
/*               |  E_NOT_OK : The request cannot be accepted.              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqWriteBlock(
    NvM_BlockIdType BlockId,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) SrcPtr
){
    Std_ReturnType  JudgementResult;
    Std_ReturnType  ChkBlockIdResult;
    Std_ReturnType  ChkAdbJobStsResult;
    Std_ReturnType  ChkConfRamTypeResult;
    Std_ReturnType  ChkRepResult;

    JudgementResult = E_NOT_OK;

    ChkBlockIdResult = NvM_Rac_ChkBlockId( BlockId, NVM_SERVICE_ID_WRITEBLK, FALSE );

    if( ChkBlockIdResult == (Std_ReturnType)E_OK )
    {
        ChkAdbJobStsResult = NvM_Rac_ChkAdbJobStatus( BlockId, NVM_SERVICE_ID_WRITEBLK );
        ChkConfRamTypeResult = NvM_Rac_ChkConfRamBlockTypeAndPtr( BlockId, SrcPtr, NVM_SERVICE_ID_WRITEBLK );

        if( ( ChkAdbJobStsResult == (Std_ReturnType)E_OK )
         && ( ChkConfRamTypeResult == (Std_ReturnType)E_OK ) )
        {
            ChkRepResult = NvM_Rac_ChkWriteProtected( BlockId );
            
            if( ChkRepResult == (Std_ReturnType)E_OK )
            {
                JudgementResult = E_OK;
            }
        }
    }

    /* The processing end */
    return JudgementResult;
}

/****************************************************************************/
/* Function Name | NvM_Rac_IsPReqRestoreBlockDefaults                       */
/* Description   | The function for checking whether or not to accept       */
/*               | the request, NvM_RestoreBlockDefaults.                   */
/* Preconditions | None                                                     */
/* Parameters    | BlockId   : The parameter of request,                    */
/*               |             BlockId.                                     */
/*               | DstPtr    : The parameter of request,                    */
/*               |             DstPtr.                                      */
/* Return Value  | Std_ReturnType : Check result.                           */
/*               |  E_OK     : The request can be accepted.                 */
/*               |  E_NOT_OK : The request cannot be accepted.              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqRestoreBlockDefaults(
    NvM_BlockIdType BlockId,
    P2CONST( uint8, AUTOMATIC, NVM_APPL_DATA ) DstPtr
){
    Std_ReturnType  JudgementResult;
    Std_ReturnType  ChkBlockIdResult;
    Std_ReturnType  ChkAdbJobStsResult;
    Std_ReturnType  ChkConfInitResult;
    Std_ReturnType  ChkConfRamTypeResult;

    JudgementResult = E_NOT_OK;

    ChkBlockIdResult = NvM_Rac_ChkBlockId( BlockId, NVM_SERVICE_ID_RESTOREBLKDEF, FALSE );

    if( ChkBlockIdResult == (Std_ReturnType)E_OK )
    {
        ChkAdbJobStsResult = NvM_Rac_ChkAdbJobStatus( BlockId, NVM_SERVICE_ID_RESTOREBLKDEF );
        ChkConfInitResult = NvM_Rac_ChkConfDefaultData( BlockId, NVM_SERVICE_ID_RESTOREBLKDEF );
        ChkConfRamTypeResult = NvM_Rac_ChkConfRamBlockTypeAndPtr( BlockId, DstPtr, NVM_SERVICE_ID_RESTOREBLKDEF );

        if( ( ChkAdbJobStsResult == (Std_ReturnType)E_OK )
         && ( ChkConfInitResult == (Std_ReturnType)E_OK )
         && ( ChkConfRamTypeResult == (Std_ReturnType)E_OK ) )
        {
            JudgementResult = E_OK;
        }
    }

    /* The processing end */
    return JudgementResult;
}

/****************************************************************************/
/* Function Name | NvM_Rac_IsPReqCancelWriteAll                             */
/* Description   | The function for checking whether or not to accept       */
/*               | the request, NvM_CancelWriteAll.                         */
/* Preconditions | Set NVM_VALID_CANCEL_WRITE_ALL_API to STD_ON.            */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType : Check result.                           */
/*               |  E_OK     : The request can be accepted.                 */
/*               |  E_NOT_OK : The request cannot be accepted.              */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqCancelWriteAll( void )
{
    return E_OK;
}
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */

/****************************************************************************/
/* Function Name | NvM_Rac_IsPReqReadPRAMBlock                              */
/* Description   | The function for checking whether or not to accept       */
/*               | the request, NvM_ReadPRAMBlock.                          */
/* Preconditions | None                                                     */
/* Parameters    | BlockId   : The parameter of request,                    */
/*               |             BlockId.                                     */
/* Return Value  | Std_ReturnType : Check result.                           */
/*               |  E_OK     : The request can be accepted.                 */
/*               |  E_NOT_OK : The request cannot be accepted.              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqReadPRAMBlock(
    NvM_BlockIdType BlockId
){
    Std_ReturnType  JudgementResult;
    Std_ReturnType  ChkBlockIdResult;
    Std_ReturnType  ChkAdbJobStsResult;
    Std_ReturnType  ChkConfRamTypeResult;

    JudgementResult = E_NOT_OK;

    ChkBlockIdResult = NvM_Rac_ChkBlockId( BlockId, NVM_SERVICE_ID_READPRAMBLK, FALSE );

    if( ChkBlockIdResult == (Std_ReturnType)E_OK )
    {
        ChkAdbJobStsResult = NvM_Rac_ChkAdbJobStatus( BlockId, NVM_SERVICE_ID_READPRAMBLK );
        ChkConfRamTypeResult = NvM_Rac_ChkConfRamBlockTypeAndPtr( BlockId, NULL_PTR, NVM_SERVICE_ID_READPRAMBLK );

        if( ( ChkAdbJobStsResult == (Std_ReturnType)E_OK ) 
         && ( ChkConfRamTypeResult == (Std_ReturnType)E_OK ) )
        {
            JudgementResult = E_OK;
        }
    }

    /* The processing end */
    return JudgementResult;
}

/****************************************************************************/
/* Function Name | NvM_Rac_IsPReqWritePRAMBlock                             */
/* Description   | The function for checking whether or not to accept       */
/*               | the request, NvM_WritePRAMBlock.                         */
/* Preconditions | None                                                     */
/* Parameters    | BlockId   : The parameter of request,                    */
/*               |             BlockId.                                     */
/*               | in.                                                      */
/* Return Value  | Std_ReturnType : Check result.                           */
/*               |  E_OK     : The request can be accepted.                 */
/*               |  E_NOT_OK : The request cannot be accepted.              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqWritePRAMBlock(
    NvM_BlockIdType BlockId
){
    Std_ReturnType  JudgementResult;
    Std_ReturnType  ChkBlockIdResult;
    Std_ReturnType  ChkAdbJobStsResult;
    Std_ReturnType  ChkConfRamTypeResult;
    Std_ReturnType  ChkRepResult;

    JudgementResult = E_NOT_OK;

    ChkBlockIdResult = NvM_Rac_ChkBlockId( BlockId, NVM_SERVICE_ID_WRITEPRAMBLK, FALSE );

    if( ChkBlockIdResult == (Std_ReturnType)E_OK )
    {
        ChkAdbJobStsResult = NvM_Rac_ChkAdbJobStatus( BlockId, NVM_SERVICE_ID_WRITEPRAMBLK );
        ChkConfRamTypeResult = NvM_Rac_ChkConfRamBlockTypeAndPtr( BlockId, NULL_PTR, NVM_SERVICE_ID_WRITEPRAMBLK );
        
        if( ( ChkAdbJobStsResult == (Std_ReturnType)E_OK )
         && ( ChkConfRamTypeResult == (Std_ReturnType)E_OK ) )
        {
            ChkRepResult = NvM_Rac_ChkWriteProtected( BlockId );

            if( ChkRepResult == (Std_ReturnType)E_OK )
            {
                JudgementResult = E_OK;
            }
        }
    }

    /* The processing end */
    return JudgementResult;
}

/****************************************************************************/
/* Function Name | NvM_Rac_IsPReqRestorePRAMBlockDefaults                   */
/* Description   | The function for checking whether or not to accept       */
/*               | the request, NvM_RestorePRAMBlockDefaults.               */
/* Preconditions | None                                                     */
/* Parameters    | BlockId   : The parameter of request,                    */
/*               |             BlockId.                                     */
/* Return Value  | Std_ReturnType : Check result.                           */
/*               |  E_OK     : The request can be accepted.                 */
/*               |  E_NOT_OK : The request cannot be accepted.              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqRestorePRAMBlockDefaults(
    NvM_BlockIdType BlockId
){
    Std_ReturnType  JudgementResult;
    Std_ReturnType  ChkBlockIdResult;
    Std_ReturnType  ChkAdbJobStsResult;
    Std_ReturnType  ChkConfInitResult;
    Std_ReturnType  ChkConfRamTypeResult;

    JudgementResult = E_NOT_OK;

    ChkBlockIdResult = NvM_Rac_ChkBlockId( BlockId, NVM_SERVICE_ID_RESTOREPRAMBLKDEF, FALSE );

    if( ChkBlockIdResult == (Std_ReturnType)E_OK )
    {
        ChkAdbJobStsResult = NvM_Rac_ChkAdbJobStatus( BlockId, NVM_SERVICE_ID_RESTOREPRAMBLKDEF );
        ChkConfInitResult = NvM_Rac_ChkConfDefaultData( BlockId, NVM_SERVICE_ID_RESTOREPRAMBLKDEF );
        ChkConfRamTypeResult = NvM_Rac_ChkConfRamBlockTypeAndPtr( BlockId, NULL_PTR, NVM_SERVICE_ID_RESTOREPRAMBLKDEF );

        if( ( ChkAdbJobStsResult == (Std_ReturnType)E_OK )
         && ( ChkConfInitResult == (Std_ReturnType)E_OK )
         && ( ChkConfRamTypeResult == (Std_ReturnType)E_OK ) )
        {
            JudgementResult = E_OK;
        }
    }

    /* The processing end */
    return JudgementResult;
}


/****************************************************************************/
/* Function Name | NvM_Rac_IsPReqReadAll                                    */
/* Description   | The function for checking whether or not to accept       */
/*               | the request, NvM_ReadAll.                                */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType : Check result.                           */
/*               |  E_OK     : The request can be accepted.                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqReadAll( void )
{

    return E_OK;
}

/****************************************************************************/
/* Function Name | NvM_Rac_IsPReqWriteAll                                   */
/* Description   | The function for checking whether or not to accept       */
/*               | the request, NvM_WriteAll.                               */
/* Preconditions | Set NVM_VALID_WRITE_ALL_API to STD_ON.                   */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType : Check result.                           */
/*               |  E_OK     : The request can be accepted.                 */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( NVM_VALID_WRITE_ALL_API == STD_ON )
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqWriteAll( void )
{

    return E_OK;
}
#endif /* NVM_VALID_WRITE_ALL_API == STD_ON */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | NvM_Rac_ChkBlockId                                       */
/* Description   | Function for checking that the BlockId is valid range.   */
/* Preconditions | None                                                     */
/* Parameters    | BlockId   : The parameter of request,                    */
/*               |             BlockId.                                     */
/*               | ServiceId : Unique Service ID of NvM.                    */
/*               | IsPermitMultiBlockId : TRUE is including the multiblock  */
/*               |                        Id in valid ranges of BlockId.    */
/* Return Value  | Std_ReturnType : Check result.                           */
/*               |  E_OK     : The BlockId is valid range.                  */
/*               |  E_NOT_OK : The BlockId is invalid.                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_ChkBlockId(
    NvM_BlockIdType BlockId,
    uint8 ServiceId,
    boolean IsPermitMultiBlockId
){
    Std_ReturnType  ChkResult = E_NOT_OK;
    NvM_BlockIdType UserBlockIdMax = NVM_USER_BLOCKID_MAX;

    if(( BlockId >= (NvM_BlockIdType)NVM_USER_BLOCKID_MIN )
    && ( BlockId <= UserBlockIdMax ))
    {
        ChkResult = E_OK;
    }
    else if( IsPermitMultiBlockId == (boolean)TRUE )
    {
        if( BlockId == (NvM_BlockIdType)NVM_RESERVED_BLOCKID_MULTIJOB )
        {
            ChkResult = E_OK;
        }
    }
    else
    {
        /* No process */
    }

    if( ChkResult != (Std_ReturnType)E_OK )
    {
        /* Function, "NvM_Evt_ReportDevelopmentError", always returns E_OK. */
        ( void )NvM_Evt_ReportDevelopmentError( NVM_MODULE_ID, NVM_INSTANCE_ID, ServiceId, NVM_E_EVT_PARAM_BLOCK_ID );
    }

    return ChkResult;
}

/****************************************************************************/
/* Function Name | NvM_Rac_ChkAdbJobStatus                                  */
/* Description   | Function for checking that the ErrorStatus is request    */
/*               | acceptable status.                                       */
/* Preconditions | None                                                     */
/* Parameters    | BlockId   : The parameter of request,                    */
/*               |             BlockId.                                     */
/*               | ServiceId : Unique Service ID of NvM.                    */
/* Return Value  | Std_ReturnType : Check result.                           */
/*               |  E_OK     : The ErrorStatus is request acceptable        */
/*               |             status.                                      */
/*               |  E_NOT_OK : The ErrorStatus is not request acceptable    */
/*               |             status.                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_ChkAdbJobStatus(
    NvM_BlockIdType BlockId,
    uint8 ServiceId
){
    Std_ReturnType  ChkResult;
    NvM_RequestResultType AdbRequestResult;
    ChkResult = E_OK;

    AdbRequestResult = NVM_REQ_PENDING;
    /* Function, "NvM_Adb_GetErrorStatus", always returns E_OK. */
    ( void )NvM_Adb_GetErrorStatus( BlockId , &AdbRequestResult );
    if( AdbRequestResult == (NvM_RequestResultType)NVM_REQ_PENDING )
    {
        /* Function, "NvM_Evt_ReportDevelopmentError", always returns E_OK. */
        ( void )NvM_Evt_ReportDevelopmentError( NVM_MODULE_ID, NVM_INSTANCE_ID, ServiceId, NVM_E_EVT_BLOCK_PENDING);
        ChkResult = E_NOT_OK;
    }

    return ChkResult;
}

/****************************************************************************/
/* Function Name | NvM_Rac_ChkConfWriteOnce                                 */
/* Description   | Function for checking WriteOnce to decide whether or not */
/*               | to accept the request.                                   */
/* Preconditions | None                                                     */
/* Parameters    | BlockId   : The parameter of request,                    */
/*               |             BlockId.                                     */
/*               | ServiceId : Unique Service ID of NvM.                    */
/* Return Value  | Std_ReturnType : Check result.                           */
/*               |  E_OK     : The request can be accepted.                 */
/*               |  E_NOT_OK : The request cannot be accepted.              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_ChkConfWriteOnce(
    NvM_BlockIdType BlockId,
    uint8 ServiceId
){
    Std_ReturnType  ChkResult;
    ChkResult = E_OK;

    if( ( NvMBlockDescriptors[BlockId].NvMBlockFlags & (NvM_BlockFlagsType)NVM_WRITE_BLOCK_ONCE ) == (NvM_BlockFlagsType)NVM_WRITE_BLOCK_ONCE )
    {
        /* Function, "NvM_Evt_ReportDevelopmentError", always returns E_OK. */
        ( void )NvM_Evt_ReportDevelopmentError( NVM_MODULE_ID, NVM_INSTANCE_ID, ServiceId, NVM_E_EVT_BLOCK_CONFIG );
        ChkResult = E_NOT_OK;
    }

    return ChkResult;
}

/****************************************************************************/
/* Function Name | NvM_Rac_ChkReqResultPtr                                  */
/* Description   | Function for checking that the RequestResultPtr is valid */
/*               | range.                                                   */
/* Preconditions | None                                                     */
/* Parameters    | RequestResultPtr : The parameter of request,             */
/*               |                    RequestResultPtr.                     */
/*               | ServiceId        : Unique Service ID of NvM.             */
/* Return Value  | Std_ReturnType : Check result.                           */
/*               |  E_OK     : The RequestResultPtr is valid range.         */
/*               |  E_NOT_OK : The RequestResultPtr is invalid.             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_ChkReqResultPtr(
    P2CONST( NvM_RequestResultType, AUTOMATIC, NVM_APPL_DATA ) RequestResultPtr,
    uint8 ServiceId
){
    Std_ReturnType  ChkResult;
    ChkResult = E_OK;

    if( RequestResultPtr == (uint8*)NULL_PTR )
    {
        /* Function, "NvM_Evt_ReportDevelopmentError", always returns E_OK. */
        ( void )NvM_Evt_ReportDevelopmentError( NVM_MODULE_ID, NVM_INSTANCE_ID, ServiceId, NVM_E_EVT_PARAM_DATA );
        ChkResult = E_NOT_OK;
    }

    return ChkResult;
}

/****************************************************************************/
/* Function Name | NvM_Rac_ChkVersionInfoPtr                                */
/* Description   | Function for checking that the versioninfo is valid      */
/*               | range.                                                   */
/* Preconditions | None                                                     */
/* Parameters    | VersionInfo : The parameter of request,                  */
/*               |               versioninfo.                               */
/*               | ServiceId        : Unique Service ID of NvM.             */
/* Return Value  | Request result                                           */
/*               |  E_OK     : The versioninfo is valid range.              */
/*               |  E_NOT_OK : The versioninfo is invalid.                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_ChkVersionInfoPtr(
    P2CONST( Std_VersionInfoType, AUTOMATIC, NVM_APPL_DATA ) VersionInfo,
    uint8 ServiceId
){
    Std_ReturnType  ChkResult;
    ChkResult = E_OK;

    if( VersionInfo == (Std_VersionInfoType*)NULL_PTR )
    {
        /* Function, "NvM_Evt_ReportDevelopmentError", always returns E_OK. */
        ( void )NvM_Evt_ReportDevelopmentError( NVM_MODULE_ID, NVM_INSTANCE_ID, ServiceId, NVM_E_EVT_PARAM_POINTER );
        ChkResult = E_NOT_OK;
    }

    return ChkResult;
}

/****************************************************************************/
/* Function Name | NvM_Rac_ChkConfUseSetRamBlockStatus                      */
/* Description   | Function for checking configure, use set RAM Block       */
/*               | Status, to decide whether or not to accept the request.  */
/* Preconditions | Set NVM_VALID_SET_RAM_BLOCK_STATUS_API to STD_ON.        */
/* Parameters    | BlockId   : The parameter of request,                    */
/*               |             BlockId.                                     */
/* Return Value  | Std_ReturnType : Check result.                           */
/*               |  E_OK     : The request can be accepted.                 */
/*               |  E_NOT_OK : The request cannot be accepted.              */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( NVM_VALID_SET_RAM_BLOCK_STATUS_API == STD_ON )
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_ChkConfUseSetRamBlockStatus(
    NvM_BlockIdType BlockId
){
    Std_ReturnType  ChkResult;
    ChkResult = E_OK;

    if( ( NvMBlockDescriptors[BlockId].NvMBlockFlags & (NvM_BlockFlagsType)NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS ) != (NvM_BlockFlagsType)NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS )
    {
        ChkResult = E_NOT_OK;
    }

    return ChkResult;
}
#endif /* NVM_VALID_SET_RAM_BLOCK_STATUS_API == STD_ON */

/****************************************************************************/
/* Function Name | NvM_Rac_ChkConfRamBlockType                              */
/* Description   | Function for checking configure, RAM Block Type, to      */
/*               | decide whether or not to accept the request.             */
/* Preconditions | Set NVM_VALID_SET_RAM_BLOCK_STATUS_API to STD_ON.        */
/* Parameters    | BlockId   : The parameter of request,                    */
/*               |             BlockId.                                     */
/*               | ServiceId        : Unique Service ID of NvM.             */
/* Return Value  | Std_ReturnType : Check result.                           */
/*               |  E_OK     : The request can be accepted.                 */
/*               |  E_NOT_OK : The request cannot be accepted.              */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( NVM_VALID_SET_RAM_BLOCK_STATUS_API == STD_ON )
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_ChkConfRamBlockType(
    NvM_BlockIdType BlockId,
    uint8 ServiceId
){
    Std_ReturnType  ChkResult;
    ChkResult = E_OK;

    if( ( NvMBlockDescriptors[BlockId].RamBlockType != (NvM_BlockManagementTypeType)NVM_RAM_BLOCK_TYPE_MIRROR )
     && ( NvMBlockDescriptors[BlockId].RamBlockType != (NvM_BlockManagementTypeType)NVM_RAM_BLOCK_TYPE_SHARED ) )
    {
        /* Function, "NvM_Evt_ReportDevelopmentError", always returns E_OK. */
        ( void )NvM_Evt_ReportDevelopmentError( NVM_MODULE_ID, NVM_INSTANCE_ID, ServiceId, NVM_E_EVT_PARAM_ADDRESS );
        ChkResult = E_NOT_OK;
    }

    return ChkResult;
}
#endif /* NVM_VALID_SET_RAM_BLOCK_STATUS_API == STD_ON */

/****************************************************************************/
/* Function Name | NvM_Rac_ChkConfRamBlockTypeAndPtr                        */
/* Description   | Function for checking configure, RAM Block Type, and     */
/*               | src/dst pointer to decide whether or not to accept the   */
/*               | request.                                                 */
/* Preconditions | None                                                     */
/* Parameters    | BlockId   : The parameter of request,                    */
/*               |             BlockId.                                     */
/*               | RamPtr    : The parameter of request,                    */
/*               |             SrcPtr or DstPtr.                            */
/*               | ServiceId : Unique Service ID of NvM.                    */
/* Return Value  | Std_ReturnType : Check result.                           */
/*               |  E_OK     : The request can be accepted.                 */
/*               |  E_NOT_OK : The request cannot be accepted.              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_ChkConfRamBlockTypeAndPtr(
    NvM_BlockIdType BlockId,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) RamPtr,
    uint8 ServiceId
){
    Std_ReturnType  ChkResult;
    ChkResult = E_OK;

    if( RamPtr == (uint8*)NULL_PTR )
    {
        if( ( NvMBlockDescriptors[BlockId].RamBlockType != (NvM_BlockManagementTypeType)NVM_RAM_BLOCK_TYPE_MIRROR )
         && ( NvMBlockDescriptors[BlockId].RamBlockType != (NvM_BlockManagementTypeType)NVM_RAM_BLOCK_TYPE_SHARED ) )
        {
            /* Function, "NvM_Evt_ReportDevelopmentError", always returns E_OK. */
            ( void )NvM_Evt_ReportDevelopmentError( NVM_MODULE_ID, NVM_INSTANCE_ID, ServiceId, NVM_E_EVT_PARAM_ADDRESS );
            ChkResult = E_NOT_OK;
        }
    }

    return ChkResult;
}

/****************************************************************************/
/* Function Name | NvM_Rac_ChkConfDefaultData                               */
/* Description   | Function for checking that default data exists.          */
/* Preconditions | None                                                     */
/* Parameters    | BlockId   : The parameter of request,                    */
/*               |             BlockId.                                     */
/*               | ServiceId : Unique Service ID of NvM.                    */
/* Return Value  | Request result                                           */
/*               |  E_OK     : A default data exists.                       */
/*               |  E_NOT_OK : A default data does not exist.               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_ChkConfDefaultData(
    NvM_BlockIdType BlockId,
    uint8 ServiceId
){
    Std_ReturnType  ChkResult;
    boolean IsExistingRomBlock;

    ChkResult = E_OK;

    IsExistingRomBlock = NvM_Romb_IsExistingRomBlock( BlockId );
    if( IsExistingRomBlock == (boolean)FALSE )
    {
        /* Function, "NvM_Evt_ReportDevelopmentError", always returns E_OK. */
        ( void )NvM_Evt_ReportDevelopmentError( NVM_MODULE_ID, NVM_INSTANCE_ID, ServiceId, NVM_E_EVT_BLOCK_CONFIG );
        ChkResult = E_NOT_OK;
    }

    return ChkResult;
}

/****************************************************************************/
/* Function Name | NvM_Rac_ChkWriteProtected                                */
/* Description   | Function for checking WriteProtection to decide whether  */
/*               | or not to accept the request.                            */
/* Preconditions | None                                                     */
/* Parameters    | BlockId   : The parameter of request,                    */
/*               |             BlockId.                                     */
/* Return Value  | Std_ReturnType : Check result.                           */
/*               |  E_OK     : The request can be accepted.                 */
/*               |  E_NOT_OK : The request cannot be accepted.              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_ChkWriteProtected(
    NvM_BlockIdType BlockId
){
    Std_ReturnType  ChkResult;
    NvM_Adb_WriteProtectStatusType     ProtectStatus;

    ChkResult = E_OK;

    ProtectStatus = NvM_Adb_GetNvBlockProtection( BlockId );
    if( ProtectStatus == (NvM_Adb_WriteProtectStatusType)NVM_ADB_WRITE_PROT_ENABLED )
    {
        ChkResult = E_NOT_OK;
    }

    return ChkResult;
}

/****************************************************************************/
/* Function Name | NvM_Rac_ChkBooleanValueRange                             */
/* Description   | Function for checking that value of boolean type is      */
/*               | valid range.                                             */
/* Preconditions | None                                                     */
/* Parameters    | Value     : Value of type boolean                        */
/* Return Value  | Std_ReturnType : Check result.                           */
/*               |  E_OK     : Input value is valid range.                  */
/*               |  E_NOT_OK : Input value is invalid.                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_ChkBooleanValueRange(
    boolean Value
){
    Std_ReturnType  ChkResult;
    ChkResult = E_OK;

    if( ( Value != (boolean)TRUE )
     && ( Value != (boolean)FALSE ) )
    {
        ChkResult = E_NOT_OK;
    }

    return ChkResult;
}

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  2-0-0          :2020/11/30                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
