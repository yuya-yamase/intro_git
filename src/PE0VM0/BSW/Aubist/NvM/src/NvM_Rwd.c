/* NvM_Rwd.c v1-0-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/RWD/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <NvM.h>
#include "../inc/NvM_Internal.h"
#include "../inc/NvM_Rwd.h"
#include "../inc/NvM_Rwd_Internal.h"
#include "../inc/NvM_Evt.h"
#include "../inc/NvM_Adb.h"
#include "../inc/NvM_Lib.h"

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

VAR( uint8, NVM_VAR_NO_INIT ) NvM_Rwd_RetryCounter;
P2VAR( uint8, NVM_VAR_NO_INIT, NVM_APPL_DATA ) NvM_Rwd_ReadDataNotifyDstPtr;
P2CONST( uint8, NVM_VAR_NO_INIT, TYPEDEF ) NvM_Rwd_WriteDataAcquireSrcPtr;

#define NVM_STOP_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

#define NVM_START_SEC_VAR_SAVED_ZONE_32
#include <NvM_MemMap.h>

VAR( NvM_Rwd_RamMirrorAlignBufferType, NVM_VAR_NO_INIT ) NvM_Rwd_RamMirror;

#define NVM_STOP_SEC_VAR_SAVED_ZONE_32
#include <NvM_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* Function Name | NvM_Rwd_Init                                             */
/* Description   | Initialize Rwd unit.                                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Rwd_Init( void )
{

    NvM_Rwd_ReadDataNotifyDstPtr = NULL_PTR;
    NvM_Rwd_WriteDataAcquireSrcPtr = NULL_PTR;

    return ;
}


/******************************************************************************/
/* Function Name | NvM_Rwd_ReadDataNotificationInit                           */
/* Description   | Preparing read data notification.                          */
/* Preconditions | None                                                       */
/* Parameters    | BlockId  : NVRAM block's identifier.                       */
/*               | DstPtr   : Read data notify destination pointer.           */
/* Return Value  | None                                                       */
/* Notes         |                                                            */
/******************************************************************************/
FUNC( void, NVM_CODE )
NvM_Rwd_ReadDataNotificationInit(
    NvM_BlockIdType BlockId,
    P2VAR( uint8, AUTOMATIC, NVM_APPL_DATA ) DstPtr
){
    NvM_Rwd_ClearRetryCounter();
    NvM_Rwd_ReadDataNotifyDstPtr = DstPtr;

    if( DstPtr == (uint8*)NULL_PTR )
    {
        if( NvMBlockDescriptors[BlockId].RamBlockType == (NvM_RamBlockTypeType)NVM_RAM_BLOCK_TYPE_SHARED )
        {
            NvM_Adb_SetRamBlockStatus( BlockId, NVM_ADB_PRAM_INVALID_UNCHANGED );
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | NvM_Rwd_GetReadDataBuffer                                  */
/* Description   | Provide Read Data Notify destination's address.            */
/* Preconditions | None                                                       */
/* Parameters    | BlockId  : NVRAM block's identifier.                       */
/* Return Value  | Read Data destination's address                            */
/* Notes         |                                                            */
/******************************************************************************/
FUNC_P2VAR( uint8, TYPEDEF, NVM_CODE )
NvM_Rwd_GetReadDataBuffer(
    NvM_BlockIdType BlockId
){
    P2VAR( uint8, AUTOMATIC, NVM_APPL_DATA ) RtnPtr     = NvM_Rwd_ReadDataNotifyDstPtr;
    NvM_RamBlockTypeType               RamBlkType = NvMBlockDescriptors[BlockId].RamBlockType;

    if( RtnPtr == (uint8*)NULL_PTR )
    {
        if( RamBlkType == (NvM_RamBlockTypeType)NVM_RAM_BLOCK_TYPE_MIRROR )
        {
            RtnPtr = NvM_Rwd_RamMirror.Uint8Data;
        }
        else
        {
            RtnPtr = NvMBlockDescriptors[BlockId].NvMRamBlockDataAddress;
        }
    }

    return RtnPtr;
}

/******************************************************************************/
/* Function Name | NvM_Rwd_ReadDataNotification                               */
/* Description   | Notify read data from NV to user.                          */
/* Preconditions | None                                                       */
/* Parameters    | BlockId  : NVRAM block's identifier.                       */
/* Return Value  | NvM_Rwd_DataPassingResultType                              */
/*               |    NVM_RWD_REQ_OK                                          */
/*               |    NVM_RWD_REQ_NOT_OK                                      */
/*               |    NVM_RWD_REQ_PENDING                                     */
/* Notes         |                                                            */
/******************************************************************************/
FUNC( NvM_Rwd_DataPassingResultType, NVM_CODE )
NvM_Rwd_ReadDataNotification(
    NvM_BlockIdType BlockId
){
    NvM_Rwd_DataPassingResultType DataPassingResult;
    Std_ReturnType               EvtResult;
    NvM_RamBlockTypeType         RamBlkType;

    DataPassingResult = NVM_RWD_REQ_OK;
    RamBlkType = NvMBlockDescriptors[BlockId].RamBlockType;

    if( NvM_Rwd_ReadDataNotifyDstPtr == NULL_PTR )
    {
        if( RamBlkType == (NvM_RamBlockTypeType)NVM_RAM_BLOCK_TYPE_MIRROR )
        {
            NvM_Evt_InspectionErrorEventStart( NVM_EVT_ERR_EVENT_REQ_FAILED );
            EvtResult = NvM_Evt_ReadRamBlockFromNvm( BlockId, NvM_Rwd_RamMirror.Uint8Data );
            if( EvtResult != (Std_ReturnType)E_OK )
            {
                DataPassingResult = NvM_Rwd_CheckRetryCounter();
            }
            else
            {
                NvM_Adb_SetRamBlockStatus( BlockId, NVM_ADB_PRAM_INVALID_UNCHANGED );
            }
        }
    }

    return DataPassingResult;
}

/******************************************************************************/
/* Function Name | NvM_Rwd_WriteDataAcquisitionInit                           */
/* Description   | Preparing write data acquisiton.                           */
/* Preconditions | None                                                       */
/* Parameters    | BlockId  : NVRAM block's identifier.                       */
/*               | SrcPtr   : Write data acquire source pointer.              */
/* Return Value  | None                                                       */
/* Notes         |                                                            */
/******************************************************************************/
FUNC( void, NVM_CODE )
NvM_Rwd_WriteDataAcquisitionInit(
    NvM_BlockIdType BlockId,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) SrcPtr
){
    NvM_Rwd_ClearRetryCounter();
    NvM_Rwd_WriteDataAcquireSrcPtr = SrcPtr;

    if( SrcPtr == (uint8*)NULL_PTR )
    {
        if( NvMBlockDescriptors[BlockId].RamBlockType == (NvM_RamBlockTypeType)NVM_RAM_BLOCK_TYPE_SHARED )
        {
            NvM_Adb_SetRamBlockStatus( BlockId, NVM_ADB_PRAM_VALID_CHANGED );
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | NvM_Rwd_GetWriteData                                       */
/* Description   | Provide the address of writing data.                       */
/* Preconditions | None                                                       */
/* Parameters    | BlockId  : NVRAM block's identifier.                       */
/* Return Value  | The address of writing data.                               */
/* Notes         |                                                            */
/******************************************************************************/
FUNC_P2CONST( uint8, TYPEDEF, NVM_CODE )
NvM_Rwd_GetWriteData(
    NvM_BlockIdType BlockId
){
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) RtnPtr     = NvM_Rwd_WriteDataAcquireSrcPtr;
    NvM_RamBlockTypeType                 RamBlkType = NvMBlockDescriptors[BlockId].RamBlockType;

    if( RtnPtr == (uint8*)NULL_PTR )
    {
        if( RamBlkType == (NvM_RamBlockTypeType)NVM_RAM_BLOCK_TYPE_MIRROR )
        {
            RtnPtr = NvM_Rwd_RamMirror.Uint8Data;
        }
        else
        {
            RtnPtr = NvMBlockDescriptors[BlockId].NvMRamBlockDataAddress;
        }
    }

    return RtnPtr;
}

/******************************************************************************/
/* Function Name | NvM_Rwd_WriteDataAcquisition                               */
/* Description   | Acquire write data from user to NvM's data buffer.         */
/* Preconditions | None                                                       */
/* Parameters    | BlockId        : NVRAM block's identifier.                 */
/* Return Value  | NvM_Rwd_DataPassingResultType                              */
/*               |    NVM_RWD_REQ_OK                                          */
/*               |    NVM_RWD_REQ_NOT_OK                                      */
/*               |    NVM_RWD_REQ_PENDING                                     */
/* Notes         |                                                            */
/******************************************************************************/
FUNC( NvM_Rwd_DataPassingResultType, NVM_CODE )
NvM_Rwd_WriteDataAcquisition(
    NvM_BlockIdType BlockId
){
    NvM_Rwd_DataPassingResultType DataPassingResult;
    Std_ReturnType               EvtResult;
    NvM_RamBlockTypeType         RamBlkType;

    DataPassingResult = NVM_RWD_REQ_OK;
    RamBlkType = NvMBlockDescriptors[BlockId].RamBlockType;

    if( NvM_Rwd_WriteDataAcquireSrcPtr == NULL_PTR )
    {
        if( RamBlkType == (NvM_RamBlockTypeType)NVM_RAM_BLOCK_TYPE_MIRROR )
        {
            NvM_Evt_InspectionErrorEventStart( NVM_EVT_ERR_EVENT_REQ_FAILED );
            EvtResult = NvM_Evt_WriteRamBlockToNvm( BlockId, NvM_Rwd_RamMirror.Uint8Data );
            if( EvtResult != (Std_ReturnType)E_OK )
            {
                DataPassingResult = NvM_Rwd_CheckRetryCounter();
            }
            else     /* In case of E_OK */
            {
                NvM_Adb_SetRamBlockStatus( BlockId, NVM_ADB_PRAM_VALID_CHANGED );
            }
        }
    }


    return DataPassingResult;
}

/******************************************************************************/
/* Function Name | NvM_Rwd_NvM_IsDstRamTemporary                              */
/* Description   | Judge whether read destination ram kind is temporary.      */
/* Preconditions | None                                                       */
/* Parameters    | None                                                       */
/* Return Value  | Rtn : Boolean variable which expresses follows.            */
/*               |   TRUE  : Ram kind is temporary.                           */
/*               |   FALSE : Ram kind is not temporary.                       */
/* Notes         |                                                            */
/******************************************************************************/
FUNC( boolean, NVM_CODE )
NvM_Rwd_NvM_IsDstRamTemporary( void )
{
    boolean Rtn = FALSE;

    if( NvM_Rwd_ReadDataNotifyDstPtr != (uint8*)NULL_PTR )
    {
        Rtn = TRUE;
    }

    return Rtn;
}

/******************************************************************************/
/* Function Name | NvM_Rwd_NvM_IsSrcRamTemporary                              */
/* Description   | Judge whether write source ram kind is temporary.          */
/* Preconditions | None                                                       */
/* Parameters    | None                                                       */
/* Return Value  | Rtn : Boolean variable which expresses follows.            */
/*               |   TRUE  : Ram kind is temporary.                           */
/*               |   FALSE : Ram kind is not temporary.                       */
/* Notes         |                                                            */
/******************************************************************************/
FUNC( boolean, NVM_CODE )
NvM_Rwd_NvM_IsSrcRamTemporary( void )
{
    boolean Rtn = FALSE;

    if( NvM_Rwd_WriteDataAcquireSrcPtr != (uint8*)NULL_PTR )
    {
        Rtn = TRUE;
    }

    return Rtn;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/******************************************************************************/
/* Function Name | NvM_Rwd_ClearRetryCounter                                  */
/* Description   |                                                            */
/* Preconditions | None                                                       */
/* Parameters    | BlockId           : NVRAM block's id.                      */
/* Return Value  | None                                                       */
/*               |                                                            */
/* Notes         |                                                            */
/******************************************************************************/
FUNC( void, NVM_CODE )
NvM_Rwd_ClearRetryCounter( void )
{
    NvM_Rwd_RetryCounter = NVM_RWD_COUNTER_INIT;
    return;
}

/******************************************************************************/
/* Function Name | NvM_Rwd_CheckRetryCounter                                  */
/* Description   |                                                            */
/* Preconditions | None                                                       */
/* Parameters    | BlockId           : NVRAM block's id.                      */
/* Return Value  | NvM_Rwd_DataPassingResultType                              */
/*               |                                                            */
/* Notes         |                                                            */
/******************************************************************************/
FUNC( NvM_Rwd_DataPassingResultType, NVM_CODE )
NvM_Rwd_CheckRetryCounter( void )
{
    NvM_Rwd_DataPassingResultType  DataPassingResult;
    uint8 RepeatMirrorOperations = NvMRepeatMirrorOperations;

    if( NvM_Rwd_RetryCounter < RepeatMirrorOperations )
    {
        NvM_Rwd_RetryCounter++;
        DataPassingResult = NVM_RWD_REQ_PENDING;
    }
    else
    {
        DataPassingResult = NVM_RWD_REQ_NOT_OK;
    }

    return DataPassingResult;
}



#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
