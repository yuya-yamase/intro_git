/* NvM_Pif.c v2-1-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/PIF/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes        | None                                                      */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <NvM.h>
#include <Rte_NvM.h>
#include <SchM_NvM.h>
#include "../inc/NvM_Internal.h"
#include "../inc/NvM_Pif.h"
#include "../inc/NvM_Pif_Internal.h"
#include <Mscd_Common.h>
#include "../inc/NvM_WdtExt.h"
#include "../inc/NvM_Adb.h"
#include "../inc/NvM_Ramb.h"
#include "../inc/NvM_Romb.h"
#include "../inc/NvM_Rwd.h"
#include "../inc/NvM_Evt.h"
#include "../inc/NvM_Nvb.h"
#include "../inc/NvM_Jobm.h"
#include "../inc/NvM_Jobq.h"
#include "../inc/NvM_Job.h"
#include "../inc/NvM_Rac.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define NVM_PIF_INIT_NOT_FINISHED             ( NVM_RND_NUM_UINT32_40 )
#define NVM_PIF_INIT_FINISHED                 ( NVM_RND_NUM_UINT32_41 )

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_VAR_NO_INIT_SHARE
#include <NvM_MemMap.h>

VAR( uint32, NVM_VAR_NO_INIT_SHARE ) NvM_Pif_InitFinished;

#define NVM_STOP_SEC_VAR_NO_INIT_SHARE
#include <NvM_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CONST_32
#include <NvM_MemMap.h>

/* NvM module version information */
CONST( AB_83_ConstV Std_VersionInfoType, NVM_CONST ) NvM_Pif_VersionInfo = {
    NVM_VENDOR_ID,          /* vendorID          */
    NVM_MODULE_ID,          /* moduleID          */
    NVM_SW_MAJOR_VERSION,   /* sw_major_version  */
    NVM_SW_MINOR_VERSION,   /* sw_minor_version  */
    NVM_SW_PATCH_VERSION    /* sw_patch_version  */
};

#define NVM_STOP_SEC_CONST_32
#include <NvM_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#define NVM_START_SEC_CODE_TRUST
#include <NvM_MemMap.h>

/****************************************************************************/
/* Function Name | NvM_PreInit                                              */
/* Description   | Function called before initialization                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE_TRUST )
NvM_PreInit( void )
{
    NvM_Pif_InitFinished    = NVM_PIF_INIT_NOT_FINISHED;

    return;
}

#define NVM_STOP_SEC_CODE_TRUST
#include <NvM_MemMap.h>

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* Function Name | NvM_Init                                                 */
/* Description   | Service for resetting all internal variables.            */
/* Preconditions | None                                                     */
/* Parameters    | ConfigPtr : Pointer to configuration                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Init(
    P2CONST( NvM_ConfigType, AUTOMATIC, NVM_CONFIG_DATA ) ConfigPtr
){
    NvM_WdtExt_Init();
    NvM_Adb_Init();
    NvM_Ramb_Init();
    NvM_Romb_Init();
    NvM_Rwd_Init();
    NvM_Evt_Init();
    NvM_Nvb_Init();
    NvM_Job_Init();
    NvM_Jobq_Init();
    NvM_Jobm_Init();
    NvM_Rac_Init();
    NvM_Pif_Init();

    return;
}

/****************************************************************************/
/* Function Name | NvM_SetDataIndex                                         */
/* Description   | Service for setting the DataIndex of a dataset NVRAM     */
/*               | block.                                                   */
/* Preconditions | None                                                     */
/* Parameters    | BlockId   : The block identifier uniquely identifies one */
/*               |             NVRAM block descriptor.                      */
/*               |             A NVRAM block descriptor contains all needed */
/*               |             information about a single NVRAM block.      */
/*               | DataIndex : Index position (association) of a NV/ROM     */
/*               |             block.                                       */
/* Return Value  | Std_ReturnType : Request result.                         */
/*               |  E_OK     : The index position was set successfully.     */
/*               |  E_NOT_OK : An error occurred.                           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_SetDataIndex(
    NvM_BlockIdType BlockId,
    uint8 DataIndex
){
    return E_NOT_OK;
}

/****************************************************************************/
/* Function Name | NvM_GetDataIndex                                         */
/* Description   | Service for getting the currently set DataIndex          */
/*               | of a dataset NVRAM block.                                */
/* Preconditions | None                                                     */
/* Parameters    | BlockId      : The block identifier uniquely identifies  */
/*               |                one NVRAM block descriptor.               */
/*               |                A NVRAM block descriptor contains all     */
/*               |                needed information about a single         */
/*               |                NVRAMblock.                               */
/*               | DataIndexPtr : Pointer to where to store the current     */
/*               |                dataset index (0..255)                    */
/* Return Value  | Std_ReturnType : Request result.                         */
/*               |  E_OK     : The index position has been retrieved        */
/*               |             successfully.                                */
/*               |  E_NOT_OK : An error occurred.                           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_GetDataIndex(
    NvM_BlockIdType BlockId,
    P2VAR( uint8, AUTOMATIC, NVM_APPL_DATA ) DataIndexPtr
){
    return E_NOT_OK;
}

/****************************************************************************/
/* Function Name | NvM_SetBlockProtection                                   */
/* Description   | Service for setting/resetting the write protection for   */
/*               | a NV block.                                              */
/* Preconditions | None                                                     */
/* Parameters    | BlockId           : The block identifier uniquely        */
/*               |                     identifies one NVRAM block           */
/*               |                     descriptor.                          */
/*               |                     A NVRAM block descriptor contains    */
/*               |                     all needed information about a       */
/*               |                     single NVRAM block.                  */
/*               | ProtectionEnabled : TRUE  : Write protection shall be    */
/*               |                             enabled                      */
/*               |                     FALSE : Write protection shall be    */
/*               |                             disabled                     */
/* Return Value  | Std_ReturnType : Request result.                         */
/*               |  E_OK     : The block was enabled/disabled as requested. */
/*               |  E_NOT_OK : An error occured.                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_SetBlockProtection(
    NvM_BlockIdType BlockId,
    boolean ProtectionEnabled
){
    Std_ReturnType ReqResult;
    Std_ReturnType ArgChkResult;

    ReqResult = E_NOT_OK;

    ArgChkResult = NvM_Rac_IsPReqSetBlockProtection( BlockId, ProtectionEnabled );

    if( ArgChkResult == (Std_ReturnType)E_OK )
    {
        if( ProtectionEnabled == (boolean)TRUE ){
            NvM_Adb_SetNvBlockProtection( BlockId, NVM_ADB_WRITE_PROT_ENABLED );
        }else{
            NvM_Adb_SetNvBlockProtection( BlockId, NVM_ADB_WRITE_PROT_DISABLED );
        }
        ReqResult = E_OK;
    }

    return ReqResult;
}

/****************************************************************************/
/* Function Name | NvM_GetErrorStatus                                       */
/* Description   | Service to read the block dependent error/status         */
/*               | information.                                             */
/* Preconditions | None                                                     */
/* Parameters    | BlockId          : The block identifier uniquely         */
/*               |                    identifies one NVRAM block            */
/*               |                    descriptor.                           */
/*               |                    A NVRAM block descriptor contains all */
/*               |                    needed information about a single     */
/*               |                    NVRAM block.                          */
/*               | RequestResultPtr : Pointer to where to store the request */
/*               |                    result.                               */
/*               |                    See NvM_RequestResultType .           */
/* Return Value  | Std_ReturnType : Request result.                         */
/*               |  E_OK     : The block dependent error/status information */
/*               |             was  read successfully.                      */
/*               |  E_NOT_OK : An error occured.                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_GetErrorStatus(
    NvM_BlockIdType BlockId,
    P2VAR( NvM_RequestResultType, AUTOMATIC, NVM_APPL_DATA ) RequestResultPtr
){
    Std_ReturnType ReqResult;
    Std_ReturnType ArgChkResult;

    ReqResult = E_NOT_OK;

    ArgChkResult = NvM_Rac_IsPReqGetErrorStatus( BlockId, RequestResultPtr );

    if( ArgChkResult == (Std_ReturnType)E_OK )
    {
        ReqResult = NvM_Adb_GetErrorStatus( BlockId, RequestResultPtr );
    }

    return ReqResult;
}

/****************************************************************************/
/* Function Name | NvM_GetVersionInfo                                       */
/* Description   | Service to get the version information of the NvM        */
/*               | module.                                                  */
/* Preconditions | None                                                     */
/* Parameters    | versioninfo : Pointer to where to store the version      */
/*               | information of this module.                              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_GetVersionInfo(
    P2VAR( Std_VersionInfoType, AUTOMATIC, NVM_APPL_DATA ) versioninfo
){
    Std_ReturnType ReqResult;

    ReqResult = NvM_Rac_IsPReqGetVersionInfo( versioninfo );
    if( ReqResult == (Std_ReturnType)E_OK )
    {
        *( versioninfo ) = NvM_Pif_VersionInfo;
    }

    return;
}

/****************************************************************************/
/* Function Name | NvM_SetRamBlockStatus                                    */
/* Description   | Service for setting the RAM block status of an NVRAM     */
/*               | block.                                                   */
/* Preconditions | Set NVM_VALID_SET_RAM_BLOCK_STATUS_API to STD_ON.        */
/* Parameters    | BlockId      : The block identifier uniquely identifies  */
/*               |                one NVRAM block descriptor.               */
/*               |                A NVRAM block descriptor contains all     */
/*               |                needed information about a single NVRAM   */
/*               |                block.                                    */
/*               | BlockChanged : TRUE  : Validate the RAM block and mark   */
/*               |                        block  as  changed.               */
/*               |                FALSE : Invalidate the RAM block and mark */
/*               |                        block as unchanged.               */
/* Return Value  | Std_ReturnType : Request result.                         */
/*               |  E_OK     : The status of the RAM-Block was changed as   */
/*               |             requested.                                   */
/*               |  E_NOT_OK : An error occurred.                           */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( NVM_VALID_SET_RAM_BLOCK_STATUS_API == STD_ON )
FUNC( Std_ReturnType, NVM_CODE )
NvM_SetRamBlockStatus(
    NvM_BlockIdType BlockId,
    boolean BlockChanged
){
    Std_ReturnType ReqResult;
    Std_ReturnType ArgChkResult;
    ReqResult = E_NOT_OK;

    ArgChkResult = NvM_Rac_IsPReqSetRamBlockStatus( BlockId, BlockChanged );

    if( ArgChkResult == (Std_ReturnType)E_OK )
    {
        if( BlockChanged == (boolean)TRUE )
        {
            NvM_Adb_SetRamBlockStatus( BlockId, NVM_ADB_PRAM_VALID_CHANGED );
        }
        else if( BlockChanged == (boolean)FALSE )
        {
            NvM_Adb_SetRamBlockStatus( BlockId, NVM_ADB_PRAM_INVALID_UNCHANGED );
        }
        else
        {
            /* No process */
        }
        ReqResult = E_OK;
    }

    return ReqResult;
}
#endif /* NVM_VALID_SET_RAM_BLOCK_STATUS_API == STD_ON */

/****************************************************************************/
/* Function Name | NvM_SetBlockLockStatus                                   */
/* Description   | Service for setting the lock status of a permanent RAM   */
/*               | block or of the explicit synchronization of a NVRAM      */
/*               | block.                                                   */
/* Preconditions | None                                                     */
/* Parameters    | BlockId     : The block identifier uniquely identifies   */
/*               |               one NVRAM block descriptor.                */
/*               |               A NVRAM block descriptor contains all      */
/*               |               needed information about a single NVRAM    */
/*               |               block.                                     */
/*               | BlockLocked : TRUE  : Mark the RAM.block as locked.      */
/*               |               FALSE : Mark the RAM.block as unlocked.    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_SetBlockLockStatus(
    NvM_BlockIdType BlockId,
    boolean BlockLocked
){
    return;
}

/****************************************************************************/
/* Function Name | NvM_CancelJobs                                           */
/* Description   | Service to cancel all jobs pending for a NV block.       */
/* Preconditions | None                                                     */
/* Parameters    | BlockId : The block identifier uniquely identifies one   */
/*               |           NVRAM block descriptor.                        */
/*               |           A NVRAM block descriptor contains all needed   */
/*               |           information about a single NVRAM block.        */
/* Return Value  | Std_ReturnType : Request result.                         */
/*               |  E_OK     : The job  was successfully removed from       */
/*               |             queue.                                       */
/*               |  E_NOT_OK : The job could not be found in the queue.     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_CancelJobs(
    NvM_BlockIdType BlockId
){
    Std_ReturnType ReqResult;
    Std_ReturnType ArgChkResult;

    ReqResult = E_NOT_OK;

    ArgChkResult = NvM_Rac_IsPReqCancelJobs( BlockId );
    if( ArgChkResult == (Std_ReturnType)E_OK )
    {
        ReqResult = NvM_Jobm_CancelJobs( BlockId );
    }

    return ReqResult;
}

/****************************************************************************/
/* Function Name | NvM_ReadBlock                                            */
/* Description   | Service to copy the data of the NV block to its          */
/*               | corresponding RAM block.                                 */
/* Preconditions | None                                                     */
/* Parameters    | BlockId    : The block identifier uniquely identifies    */
/*               |              one NVRAM block descriptor.                 */
/*               |              A NVRAM block descriptor contains all       */
/*               |              needed information about a single NVRAM     */
/*               |              block.                                      */
/*               | NvM_DstPtr : Pointer to the RAM data block.              */
/* Return Value  | Std_ReturnType : Request result.                         */
/*               |  E_OK     : request has been accepted.                   */
/*               |  E_NOT_OK : request has not been accepted.               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_ReadBlock(
    NvM_BlockIdType BlockId,
    P2VAR( void, AUTOMATIC, NVM_APPL_DATA ) NvM_DstPtr
){
    Std_ReturnType ReqResult;
    Std_ReturnType ArgChkResult;

    ReqResult = E_NOT_OK;

    ArgChkResult = NvM_Rac_IsPReqReadBlock( BlockId, (uint8 *)NvM_DstPtr );

    if( ArgChkResult == (Std_ReturnType)E_OK )
    {
        ReqResult = NvM_Jobm_RequestJob( NVM_JOB_READ_BLOCK, BlockId, (uint8 *)NvM_DstPtr, NULL_PTR );
    }

    return ReqResult;
}

/****************************************************************************/
/* Function Name | NvM_WriteBlock                                           */
/* Description   | Service to copy the data of the RAM block to its         */
/*               | corresponding NV block.                                  */
/* Preconditions | None                                                     */
/* Parameters    | BlockId    : The block identifier uniquely identifies    */
/*               |              one NVRAM block descriptor.                 */
/*               |              A NVRAM block descriptor contains all       */
/*               |              needed information about a single NVRAM     */
/*               |              block.                                      */
/*               | NvM_SrcPtr : Pointer to the RAM data block.              */
/* Return Value  | Std_ReturnType : Request result.                         */
/*               |  E_OK     : request has been accepted.                   */
/*               |  E_NOT_OK : request has not been accepted.               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_WriteBlock(
    NvM_BlockIdType BlockId,
    P2CONST( void, AUTOMATIC, TYPEDEF ) NvM_SrcPtr
){
    Std_ReturnType ReqResult;
    Std_ReturnType ArgChkResult;

    ReqResult = E_NOT_OK;

    ArgChkResult = NvM_Rac_IsPReqWriteBlock( BlockId, (const uint8 *)NvM_SrcPtr );

    if( ArgChkResult == (Std_ReturnType)E_OK )
    {
        ReqResult = NvM_Jobm_RequestJob( NVM_JOB_WRITE_BLOCK, BlockId, NULL_PTR, (const uint8 *)NvM_SrcPtr );
    }

    return ReqResult;
}

/****************************************************************************/
/* Function Name | NvM_RestoreBlockDefaults                                 */
/* Description   | Service to restore the default data to its corresponding */
/*               | RAM block.                                               */
/* Preconditions | None                                                     */
/* Parameters    | BlockId     : The block identifier uniquely identifies   */
/*               |               one NVRAM block descriptor.                */
/*               |               A NVRAM block descriptor contains all      */
/*               |               needed information about a single NVRAM    */
/*               |               block.                                     */
/*               | NvM_DestPtr : Pointer to the RAM data block.             */
/* Return Value  | Std_ReturnType : Request result.                         */
/*               |  E_OK     : request has been accepted.                   */
/*               |  E_NOT_OK : request has not been accepted.               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_RestoreBlockDefaults(
    NvM_BlockIdType BlockId,
    P2VAR( void, AUTOMATIC, NVM_APPL_DATA ) NvM_DestPtr
){
    Std_ReturnType ReqResult;
    Std_ReturnType ArgChkResult;

    ReqResult = E_NOT_OK;

    ArgChkResult = NvM_Rac_IsPReqRestoreBlockDefaults( BlockId, (uint8 *)NvM_DestPtr );

    if( ArgChkResult == (Std_ReturnType)E_OK )
    {
        ReqResult = NvM_Jobm_RequestJob( NVM_JOB_RESTORE_BLOCK_DEFAULTS, BlockId, (uint8 *)NvM_DestPtr, NULL_PTR );
    }

    return ReqResult;
}

/****************************************************************************/
/* Function Name | NvM_EraseNvBlock                                         */
/* Description   | Service to erase a NV block.                             */
/* Preconditions | None                                                     */
/* Parameters    | BlockId : The block identifier uniquely identifies one   */
/*               |           NVRAM block descriptor.                        */
/*               |           A NVRAM block descriptor contains all needed   */
/*               |           information about a single NVRAM block.        */
/* Return Value  | Std_ReturnType : Request result.                         */
/*               |  E_OK     : request has been accepted.                   */
/*               |  E_NOT_OK : request has not been accepted.               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_EraseNvBlock(
    NvM_BlockIdType BlockId
){
    return E_NOT_OK;
}

/****************************************************************************/
/* Function Name | NvM_CancelWriteAll                                       */
/* Description   | Service to cancel a running NvM_WriteAll request.        */
/* Preconditions | Set NVM_VALID_CANCEL_WRITE_ALL_API to STD_ON.            */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
FUNC( void, NVM_CODE )
NvM_CancelWriteAll( void )
{
#if ( NVM_VALID_WRITE_ALL_API == STD_ON )
    Std_ReturnType ArgChkResult;

    ArgChkResult = NvM_Rac_IsPReqCancelWriteAll();

    if( ArgChkResult == (Std_ReturnType)E_OK )
    {
        NvM_Jobm_CancelWriteAll();
    }
#endif /* NVM_VALID_WRITE_ALL_API == STD_ON */

    return;
}
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */

/****************************************************************************/
/* Function Name | NvM_InvalidateNvBlock                                    */
/* Description   | Service to invalidate a NV block.                        */
/* Preconditions | None                                                     */
/* Parameters    | BlockId : The block identifier uniquely identifies one   */
/*               |           NVRAM block descriptor.                        */
/*               |           A NVRAM block descriptor contains all needed   */
/*               |           information about a single NVRAM block.        */
/* Return Value  | Std_ReturnType : Request result.                         */
/*               |  E_OK     : request has been accepted.                   */
/*               |  E_NOT_OK : request has not been accepted.               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_InvalidateNvBlock(
    NvM_BlockIdType BlockId
){
    return E_NOT_OK;
}

/****************************************************************************/
/* Function Name | NvM_ReadPRAMBlock                                        */
/* Description   | Service to copy the data of the NV block to its          */
/*               | corresponding  permanent  RAM block.                     */
/* Preconditions | None                                                     */
/* Parameters    | BlockId : The block identifier uniquely identifies one   */
/*               |           NVRAM block descriptor.                        */
/*               |           A NVRAM block descriptor contains all needed   */
/*               |           information about a single NVRAM block.        */
/* Return Value  | Std_ReturnType : Request result.                         */
/*               |  E_OK     : request has been accepted.                   */
/*               |  E_NOT_OK : request has not been accepted.               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_ReadPRAMBlock(
    NvM_BlockIdType BlockId
){
    Std_ReturnType ReqResult;
    Std_ReturnType ArgChkResult;

    ReqResult = E_NOT_OK;

    ArgChkResult = NvM_Rac_IsPReqReadPRAMBlock( BlockId );

    if( ArgChkResult == (Std_ReturnType)E_OK )
    {
        ReqResult = NvM_Jobm_RequestJob( NVM_JOB_READ_PRAM_BLOCK, BlockId, NULL_PTR, NULL_PTR );

    }

    return ReqResult;
}

/****************************************************************************/
/* Function Name | NvM_WritePRAMBlock                                       */
/* Description   | Service to copy the data of the RAM block to its         */
/*               | corresponding permanent RAM block.                       */
/* Preconditions | None                                                     */
/* Parameters    | BlockId : The block identifier uniquely identifies one   */
/*               |           NVRAM block descriptor.                        */
/*               |           A NVRAM block descriptor contains all needed   */
/*               |           information about a single NVRAM block.        */
/* Return Value  | Std_ReturnType : Request result.                         */
/*               |  E_OK     : request has been accepted.                   */
/*               |  E_NOT_OK : request has not been accepted.               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_WritePRAMBlock(
    NvM_BlockIdType BlockId
){
    Std_ReturnType ReqResult;
    Std_ReturnType ArgChkResult;

    ReqResult = E_NOT_OK;

    ArgChkResult = NvM_Rac_IsPReqWritePRAMBlock( BlockId );

    if( ArgChkResult == (Std_ReturnType)E_OK )
    {
        ReqResult = NvM_Jobm_RequestJob( NVM_JOB_WRITE_PRAM_BLOCK, BlockId, NULL_PTR, NULL_PTR );

    }

    return ReqResult;
}

/****************************************************************************/
/* Function Name | NvM_RestorePRAMBlockDefaults                             */
/* Description   | Service to restore the default data to its corresponding */
/*               | permanent RAM block.                                     */
/* Preconditions | None                                                     */
/* Parameters    | BlockId : The block identifier uniquely identifies one   */
/*               |           NVRAM block descriptor.                        */
/*               |           A NVRAM block descriptor contains all needed   */
/*               |           information about a single NVRAM block.        */
/* Return Value  | Std_ReturnType : Request result.                         */
/*               |  E_OK     : request has been accepted.                   */
/*               |  E_NOT_OK : request has not been accepted.               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_RestorePRAMBlockDefaults(
    NvM_BlockIdType BlockId
){
    Std_ReturnType ReqResult;
    Std_ReturnType ArgChkResult;

    ReqResult = E_NOT_OK;

    ArgChkResult = NvM_Rac_IsPReqRestorePRAMBlockDefaults( BlockId );

    if( ArgChkResult == (Std_ReturnType)E_OK )
    {
        ReqResult = NvM_Jobm_RequestJob( NVM_JOB_RESTORE_PRAM_BLOCK_DEFAULTS, BlockId, NULL_PTR, NULL_PTR );
    }

    return ReqResult;
}

/****************************************************************************/
/* Function Name | NvM_ReadAll                                              */
/* Description   | Initiates a multi block read request.                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_ReadAll( void )
{
    Std_ReturnType ArgChkResult;

    ArgChkResult = NvM_Rac_IsPReqReadAll();

    if( ArgChkResult == (Std_ReturnType)E_OK )
    {
        /* Return value is not checked, because "NvM_ReadAll" does not need the result of request. */
        ( void )NvM_Jobm_RequestJob( NVM_JOB_READ_ALL, NVM_RESERVED_BLOCKID_MULTIJOB, NULL_PTR, NULL_PTR );
    }

    return ;
}

/****************************************************************************/
/* Function Name | NvM_WriteAll                                             */
/* Description   | Initiates a multi block write request.                   */
/* Preconditions | Set NVM_VALID_WRITE_ALL_API to STD_ON.                   */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( NVM_VALID_WRITE_ALL_API == STD_ON )
FUNC( void, NVM_CODE )
NvM_WriteAll( void )
{
    Std_ReturnType ArgChkResult;

    ArgChkResult = NvM_Rac_IsPReqWriteAll();

    if( ArgChkResult == (Std_ReturnType)E_OK )
    {
        /* Return value is not checked, because "NvM_WriteAll" does not need the result of request. */
        ( void )NvM_Jobm_RequestJob( NVM_JOB_WRITE_ALL, NVM_RESERVED_BLOCKID_MULTIJOB, NULL_PTR, NULL_PTR );
    }

    return ;
}
#endif /* NVM_VALID_WRITE_ALL_API == STD_ON */

/****************************************************************************/
/* Function Name | NvM_ValidateAll                                          */
/* Description   | Initiates a multi block validation request.              */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_ValidateAll( void )
{
    return ;
}

/****************************************************************************/
/* Function Name | NvM_MainFunction                                         */
/* Description   | Service for performing the processing of the NvM jobs.   */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_MainFunction( void )
{
    uint8          MsOpeState;
    uint32         InitFinished;
    boolean        IsFatalError;

    InitFinished = NvM_Pif_InitFinished;
    if( InitFinished == (uint32)NVM_PIF_INIT_FINISHED )
    {
        IsFatalError = NvM_Evt_IsFatalFailed();
        if( IsFatalError == (boolean)FALSE )
        {
            Mscd_Frm_NvMExclusiveLockBegin();
            MsOpeState = Mscd_Suspend_UpdateOpeState();
            if( MSCD_SUSPEND_MS_RUN == MsOpeState )
            {
                NvM_Jobm_MainFunction( NVM_NVB_CALLMODE_PERIODIC );
                NvM_WdtExt_MainFunction();
                Mscd_Msif_NvMMFProcessResultNotification( MSCD_MAINFUNCTION_PROCESSED );
            }
            else
            {
                Mscd_Msif_NvMMFProcessResultNotification( MSCD_MAINFUNCTION_NOT_PROCESSED );
            }
            Mscd_Frm_NvMExclusiveLockEnd();
        }
    }
    else if( InitFinished == (uint32)NVM_PIF_INIT_NOT_FINISHED )
    {
        /* Do Nothing */
    }
    else
    {
        /* Ram garbled */
        NvM_Evt_SetFatalFailed();
    }

    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | NvM_Pif_Init                                             */
/* Description   | Function for resetting this unit.                        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Pif_Init( void )
{
    NvM_Pif_InitFinished = NVM_PIF_INIT_FINISHED;

    return;
}

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  2-0-0          :2021/07/28                                              */
/*  2-1-0          :2022/07/20                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
