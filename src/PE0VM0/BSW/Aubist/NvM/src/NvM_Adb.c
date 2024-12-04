/* NvM_Adb.c v1-0-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/ADB/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <NvM.h>
#include "../inc/NvM_Internal.h"
#include "../inc/NvM_Adb.h"
#include "../inc/NvM_Adb_Internal.h"
#include "../inc/NvM_Evt.h"

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

VAR( NvM_Adb_AdminBlockInfoType, NVM_VAR_NO_INIT ) NvM_Adb_AdminBlockInfo[NVM_NUM_OF_NVRAMBLOCKS];
VAR( NvM_BlockIdType,            NVM_VAR_NO_INIT ) NvM_Adb_CheckTargetBlockId;

#define NVM_STOP_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* Function Name | NvM_Adb_Init                                             */
/* Description   | Initialize Adb unit.                                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Adb_Init( void )
{
    uint16 Index;
    NvM_BlockFlagsType BlockDescFlags;

    for( Index = 0U; Index < (uint16)NVM_NUM_OF_NVRAMBLOCKS; Index++ )
    {
        BlockDescFlags = NvMBlockDescriptors[Index].NvMBlockFlags;
        
        /* Initialization of the write protection. */
        if( ( BlockDescFlags & (NvM_BlockFlagsType)NVM_WRITE_BLOCK_ONCE ) != (NvM_BlockFlagsType)NVM_WRITE_BLOCK_ONCE )
        {
            if( ( BlockDescFlags & (NvM_BlockFlagsType)NVM_BLOCK_WRITE_PROT ) != (NvM_BlockFlagsType)NVM_BLOCK_WRITE_PROT )
            {
                NvM_Adb_AdminBlockInfo[Index].WriteProtectStatus = NVM_ADB_WRITE_PROT_DISABLED;
            }
            else
            {
                NvM_Adb_AdminBlockInfo[Index].WriteProtectStatus = NVM_ADB_WRITE_PROT_ENABLED;
            }
        }
        else
        {
            NvM_Adb_AdminBlockInfo[Index].WriteProtectStatus = NVM_ADB_WRITE_PROT_DISABLED;
        }

        /* Initialization of the permanence RAM block state */
        NvM_Adb_AdminBlockInfo[Index].AdbReqResult = NVM_REQ_OK;

#if ( NVM_VALID_SET_RAM_BLOCK_STATUS_API == STD_ON )
        NvM_Adb_AdminBlockInfo[Index].RamBlockStatus = NVM_ADB_PRAM_INVALID_UNCHANGED;
#endif /* NVM_VALID_SET_RAM_BLOCK_STATUS_API == STD_ON */
    }

    NvM_Adb_CheckTargetBlockId = NVM_BLOCKID_MIN;

    return ;
}

/******************************************************************************/
/* Function Name | NvM_Adb_SetRamBlockStatus                                  */
/* Description   | Store PRam block's status.                                 */
/* Preconditions | None                                                       */
/* Parameters    | BlockId               : NVRAM block's id.                  */
/*               | ParamRamBlockStatus   : Ram block's status.                */
/* Return Value  | None                                                       */
/* Notes         |                                                            */
/******************************************************************************/
FUNC( void, NVM_CODE )
NvM_Adb_SetRamBlockStatus(
    NvM_BlockIdType BlockId,
    NvM_Adb_RamBlockStatusType Status
){

#if ( NVM_VALID_SET_RAM_BLOCK_STATUS_API == STD_ON )
    NvM_Adb_AdminBlockInfo[BlockId].RamBlockStatus = Status;
#endif /* NVM_VALID_SET_RAM_BLOCK_STATUS_API == STD_ON */

    return ;
}

/******************************************************************************/
/* Function Name | NvM_Adb_SetNvBlockProtection                               */
/* Description   | Store NVRAM block's protection status                      */
/* Preconditions | None                                                       */
/* Parameters    | BlockId           : NVRAM block's id.                      */
/*               | StateValue        : NVRAM block's protection status.       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC( void, NVM_CODE )
NvM_Adb_SetNvBlockProtection(
    NvM_BlockIdType BlockId,
    NvM_Adb_WriteProtectStatusType StateValue
){
    NvM_Adb_AdminBlockInfo[BlockId].WriteProtectStatus = StateValue;

    return;
}

/******************************************************************************/
/* Function Name | NvM_Adb_GetRamBlockStatus                                  */
/* Description   | Provide RAM block's status.                                */
/* Preconditions | None                                                       */
/* Parameters    | BlockId             : NVRAM block's id.                    */
/*               | Status              : Pointer to get RAM block status.     */
/* Return Value  | Std_ReturnType                                             */
/*               |   E_OK                                                     */
/*               |   E_NOT_OK                                                 */
/* Notes         |                                                            */
/******************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Adb_GetRamBlockStatus(
    NvM_BlockIdType BlockId,
    P2VAR( NvM_Adb_RamBlockStatusType, AUTOMATIC, TYPEDEF ) Status
){
    Std_ReturnType Rtn = E_NOT_OK;

#if ( NVM_VALID_SET_RAM_BLOCK_STATUS_API == STD_ON )
    if( ( NvMBlockDescriptors[BlockId].NvMBlockFlags & (NvM_BlockFlagsType)NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS ) == (NvM_BlockFlagsType)NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS )
    {
        (*Status) = NvM_Adb_AdminBlockInfo[BlockId].RamBlockStatus;
        Rtn = E_OK;
    }
#endif /* NVM_VALID_SET_RAM_BLOCK_STATUS_API == STD_ON */

    return Rtn;
}

/******************************************************************************/
/* Function Name | NvM_Adb_GetNvBlockProtection                               */
/* Description   | Store NVRAM block's Protection status.                     */
/* Preconditions | None                                                       */
/* Parameters    | BlockId             : NVRAM block's id.                    */
/* Return Value  | NvM_Adb_WriteProtectStatusType                             */
/*               |  NVM_ADB_WRITE_PROT_ENABLED                                */
/*               |  NVM_ADB_WRITE_PROT_DISABLED                               */
/* Notes         |                                                            */
/******************************************************************************/
FUNC( NvM_Adb_WriteProtectStatusType, NVM_CODE )
NvM_Adb_GetNvBlockProtection(
    NvM_BlockIdType BlockId
){
    return NvM_Adb_AdminBlockInfo[BlockId].WriteProtectStatus;
}

/******************************************************************************/
/* Function Name | NvM_Adb_SetErrorStatus                                     */
/* Description   | Setting job result.                                        */
/* Preconditions | None                                                       */
/* Parameters    | BlockId        : NVRAM block's id.                         */
/*               | RequestResult  : NvM's job result.                         */
/* Return Value  | Std_ReturnType                                             */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         |                                                            */
/******************************************************************************/
FUNC( void, NVM_CODE )
NvM_Adb_SetErrorStatus(
    NvM_BlockIdType BlockId,
    uint32 JobId,
    NvM_RequestResultType RequestResult
){
    NvM_Adb_AdminBlockInfo[BlockId].AdbReqResult = RequestResult;
    NvM_Evt_JobResultChange( BlockId, JobId, RequestResult );

    return;
}

/******************************************************************************/
/* Function Name | NvM_Adb_SetErrorStatusNonNotification                      */
/* Description   | Setting job result.                                        */
/*               | This function don't notify to EVT.                         */
/* Preconditions | None                                                       */
/* Parameters    | BlockId        : NVRAM block's id.                         */
/*               | RequestResult  : NvM's job result.                         */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
#if ( NVM_USE_CANCEL_NOTIFICATION == STD_OFF )
FUNC( void, NVM_CODE )
NvM_Adb_SetErrorStatusNonNotification(
    NvM_BlockIdType BlockId,
    NvM_RequestResultType RequestResult
){
    NvM_Adb_AdminBlockInfo[BlockId].AdbReqResult = RequestResult;

    return;
}
#endif /* NVM_USE_CANCEL_NOTIFICATION == STD_OFF */

/******************************************************************************/
/* Function Name | NvM_Adb_GetErrorStatus                                     */
/* Description   | Provide NvM's job result.                                  */
/* Preconditions | None                                                       */
/* Parameters    | BlockId        : NVRAM block's id.                         */
/*               | RequestResult  : NvM's job result.                         */
/* Return Value  | Std_ReturnType                                             */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         |                                                            */
/******************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Adb_GetErrorStatus(
    NvM_BlockIdType BlockId,
    P2VAR( NvM_RequestResultType, AUTOMATIC, TYPEDEF ) RequestResult
){
    *RequestResult = NvM_Adb_AdminBlockInfo[BlockId].AdbReqResult;
    return E_OK;
}

/******************************************************************************/
/* Function Name | NvM_Adb_CheckRamError                                      */
/* Description   | This function checks RAMs. If RAM garbled is detected,     */
/*               | this function notifies other unit.                         */
/* Preconditions | NvM's status is idling.                                    */
/* Parameters    | BlockId        : NVRAM block's id.                         */
/*               | RequestResult  : NvM's job result.                         */
/* Return Value  | Std_ReturnType                                             */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         |                                                            */
/******************************************************************************/
FUNC( void, NVM_CODE )
NvM_Adb_CheckRamError( void )
{
    NvM_BlockIdType         CheckTargetBlockId = NvM_Adb_CheckTargetBlockId;
    uint16                  Counter;

    for( Counter = 0U; Counter < (uint16)NVM_ADB_RAM_GARBLED_CHECK_NUM; Counter++ )
    {
        if( CheckTargetBlockId >= (NvM_BlockIdType)NVM_NUM_OF_NVRAMBLOCKS )
        {
            CheckTargetBlockId = NVM_BLOCKID_MIN;
        }

        if( NvM_Adb_AdminBlockInfo[CheckTargetBlockId].AdbReqResult == (NvM_RequestResultType)NVM_REQ_PENDING )
        {
            NvM_Evt_FatalFailedNotification();
        }

        CheckTargetBlockId++;
    }
    NvM_Adb_CheckTargetBlockId = CheckTargetBlockId;

    return;
}

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
