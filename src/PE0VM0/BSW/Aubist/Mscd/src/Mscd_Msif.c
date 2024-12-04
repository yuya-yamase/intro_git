/* Mscd_Msif.c v2-0-0                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MSCD/MSIF/CODE                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Mscd.h>
#include <Fee.h>
#include <NvM_Mscd.h>

#include <Mscd_Common.h>
#include "../inc/Mscd_Msif.h"

#include "../inc/Mscd_ErrorInfo.h"
#include "../inc/Mscd_Suspend.h"
#include "../inc/Mscd_FreeSpace.h"
#include "../inc/Mscd_Frm.h"
#include "../inc/Mscd_Msif_Internal.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define MSCD_START_SEC_CODE
#include <Mscd_MemMap.h>

/****************************************************************************/
/* Function Name | Mscd_Init                                                */
/* Description   | Service to initialize the MSCD module                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, MSCD_CODE) Mscd_Init(void)
{
    Mscd_Msif_u1CurrentMultiBlockRequest = MSCD_MSIF_MULTI_BLOCK_REQUEST_INVALID;
    Mscd_Msif_u2CurrentSingleJobBlockId = MSCD_MSIF_BLOCKID_INVALID;
    
    Mscd_Msif_u1MFProcessResult_NvM     = MSCD_MAINFUNCTION_PROCESSED;
    Mscd_Msif_u1MFProcessResult_SpeedUp = MSCD_MAINFUNCTION_PROCESSED;
    Mscd_Msif_u1MFProcessResult_Dfai    = MSCD_MAINFUNCTION_PROCESSED;
    
    Mscd_Suspend_Init();
    Mscd_ErrorInfo_Init();
    Mscd_FreeSpace_Init();
    Mscd_Frm_Init();
    
    return;
}

#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Msif_GetCurrentMultiBlockRequest                    */
/* Description   | Get Current Multi BlockRequest                           */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Mscd_Msif_u1CurrentMultiBlockRequest                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(NvM_MultiBlockRequestType, MSCD_CODE) Mscd_Msif_GetCurrentMultiBlockRequest(void)
{
    return(Mscd_Msif_u1CurrentMultiBlockRequest);
}
#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */

/****************************************************************************/
/* Function Name | Mscd_Msif_GetCurrentSingleJobBlockId                     */
/* Description   | Get Current Block ID                                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Mscd_Msif_u2CurrentSingleJobBlockId                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint16, MSCD_CODE) Mscd_Msif_GetCurrentSingleJobBlockId(void)
{
    return(Mscd_Msif_u2CurrentSingleJobBlockId);
}

/****************************************************************************/
/* Function Name | Mscd_Msif_GetStatus                                      */
/* Description   | Get state of MS.                                         */
/* Preconditions | None                                                     */
/* Parameters    | MsStatusPtr                                              */
/*               |  MSCD_MS_STATE_IDLE                                      */
/*               |  MSCD_MS_STATE_BUSY                                      */
/*               |  MSCD_MS_STATE_ERROR                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                                                    */
/*               |  E_NOT_OK                                                */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(Std_ReturnType, MSCD_CODE) Mscd_Msif_GetStatus(
    P2VAR(Mscd_MsStatusType, AUTOMATIC, MSCD_APPL_DATA) MsStatusPtr 
){
    Std_ReturnType Rtn = E_NOT_OK;
    NvM_ExtStatusType NvMStatus;
    uint8 FeeStatus;
    uint8 SuspendStatus;

    if( MsStatusPtr != (Mscd_MsStatusType*)NULL_PTR )
    {
        /* NvM Status check */
        NvMStatus = NvM_ExtGetStatus();
        if (NvMStatus == (NvM_ExtStatusType)NVM_EXT_BUSY)
        {
            *MsStatusPtr = MSCD_MS_STATE_BUSY;
        }
        else if (NvMStatus == (NvM_ExtStatusType)NVM_EXT_ERROR)
        {
            *MsStatusPtr = MSCD_MS_STATE_ERROR;
        }
        else
        {
            /* Suspend Status check */
            SuspendStatus = Mscd_Suspend_GetUserSuspendState();
            if (SuspendStatus == MSCD_SUSPEND_MS_RUN)
            {
                /* Fee Status check */
                FeeStatus = Fee_GetStatus();
                if (FeeStatus == MEMIF_IDLE)
                {
                    *MsStatusPtr = MSCD_MS_STATE_IDLE;
                }
                else
                {
                    *MsStatusPtr = MSCD_MS_STATE_ERROR;
                }
            }
            else
            {
                *MsStatusPtr = MSCD_MS_STATE_IDLE;
            }
        }
        Rtn = E_OK;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Mscd_Msif_GetNvMMainFunctionProcessResult                */
/* Description   | Service to get NvM_MainFunction process result.          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | uint8                                                    */
/*               |  MSCD_MAINFUNCTION_PROCESSED                             */
/*               |  MSCD_MAINFUNCTION_NOT_PROCESSED                         */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(uint8, MSCD_CODE) Mscd_Msif_GetNvMMainFunctionProcessResult( void )
{
    return( Mscd_Msif_u1MFProcessResult_NvM );
}

/****************************************************************************/
/* Function Name | Mscd_Msif_GetSpeedUpMainFunctionProcessResult            */
/* Description   | Service to get Mscd_SpeedUp_MainFunction process result. */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | uint8                                                    */
/*               |  MSCD_MAINFUNCTION_PROCESSED                             */
/*               |  MSCD_MAINFUNCTION_NOT_PROCESSED                         */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(uint8, MSCD_CODE) Mscd_Msif_GetSpeedUpMainFunctionProcessResult( void )
{
    return( Mscd_Msif_u1MFProcessResult_SpeedUp );
}

/****************************************************************************/
/* Function Name | Mscd_Msif_GetDfaiMainFunctionProcessResult               */
/* Description   | Service to get Mscd_Dfai_MainFunction process result.    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | uint8                                                    */
/*               |  MSCD_MAINFUNCTION_PROCESSED                             */
/*               |  MSCD_MAINFUNCTION_NOT_PROCESSED                         */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(uint8, MSCD_CODE) Mscd_Msif_GetDfaiMainFunctionProcessResult( void )
{
    return( Mscd_Msif_u1MFProcessResult_Dfai );
}

/****************************************************************************/
/* Function Name | Mscd_Msif_SingleBlockJobStartHook                        */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | BlockId      : Block Id                                  */
/*               | BlockRequest : Request Type of the single block job.     */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(void, MSCD_CODE) Mscd_Msif_SingleBlockJobStartHook(
    NvM_BlockIdType BlockId,
    NvM_BlockRequestType BlockRequest
){
    Mscd_Msif_u2CurrentSingleJobBlockId = BlockId;
    if ( ( BlockRequest != (NvM_BlockRequestType) NVM_READ_ALL_BLOCK )
    &&   ( BlockRequest != (NvM_BlockRequestType) NVM_WRITE_ALL_BLOCK ) )
    {
        Mscd_Msif_u1CurrentMultiBlockRequest = MSCD_MSIF_MULTI_BLOCK_REQUEST_INVALID;
    }
    Mscd_ErrorInfo_SingleBlockJobStartHook(BlockRequest);
    
    return;
}

/****************************************************************************/
/* Function Name | Mscd_Msif_MultiBlockJobStartHook                         */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | MultiBlockRequest : Request Type of the multi block job. */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(void, MSCD_CODE) Mscd_Msif_MultiBlockJobStartHook(
    NvM_MultiBlockRequestType MultiBlockRequest
){
    Mscd_Msif_u1CurrentMultiBlockRequest = MultiBlockRequest;
    Mscd_ErrorInfo_MultiBlockJobStartHook(MultiBlockRequest);
    
    return;
}

/****************************************************************************/
/* Function Name | Mscd_Msif_SingleBlockJobEndHook                          */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | BlockId      : Block Id                                  */
/*               | BlockRequest : Request Type of the single block job.     */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(void, MSCD_CODE) Mscd_Msif_SingleBlockJobEndHook(
    NvM_BlockIdType BlockId,
    NvM_BlockRequestType BlockRequest
){
    Mscd_Msif_u2CurrentSingleJobBlockId = MSCD_MSIF_BLOCKID_INVALID;
    Mscd_ErrorInfo_SingleBlockJobEndHook(BlockRequest);
    
    return;
}

/****************************************************************************/
/* Function Name | Mscd_Msif_MultiBlockJobEndHook                           */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | MultiBlockRequest : Request Type of the multi block job. */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(void, MSCD_CODE) Mscd_Msif_MultiBlockJobEndHook(
    NvM_MultiBlockRequestType MultiBlockRequest
){
    Mscd_Msif_u1CurrentMultiBlockRequest = MSCD_MSIF_MULTI_BLOCK_REQUEST_INVALID;
    Mscd_ErrorInfo_MultiBlockJobEndHook(MultiBlockRequest);
    
    return;
}

/****************************************************************************/
/* Function Name | Mscd_Msif_NvMMFProcessResultNotification                 */
/* Description   | Service to notify NvM_MainFunction process result.       */
/* Preconditions | None                                                     */
/* Parameters    | ProcessResult                                            */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(void, MSCD_CODE) Mscd_Msif_NvMMFProcessResultNotification(
    uint8 ProcessResult
){
    Mscd_Msif_u1MFProcessResult_NvM = ProcessResult;
    
    return;
}

/****************************************************************************/
/* Function Name | Mscd_Msif_SpeedUpMFProcessResultNotification             */
/* Description   | Service to notify Mscd_SpeedUp_MainFunction process      */
/*               | result.                                                  */
/* Preconditions | None                                                     */
/* Parameters    | ProcessResult                                            */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(void, MSCD_CODE) Mscd_Msif_SpeedUpMFProcessResultNotification(
    uint8 ProcessResult
){
    Mscd_Msif_u1MFProcessResult_SpeedUp = ProcessResult;
    
    return;
}

/****************************************************************************/
/* Function Name | Mscd_Msif_DfaiMFProcessResultNotification                */
/* Description   | Service to notify Mscd_Dfai_MainFunction process result. */
/* Preconditions | None                                                     */
/* Parameters    | ProcessResult                                            */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(void, MSCD_CODE) Mscd_Msif_DfaiMFProcessResultNotification(
    uint8 ProcessResult
){
    Mscd_Msif_u1MFProcessResult_Dfai = ProcessResult;
    
    return;
}

#define MSCD_STOP_SEC_CODE
#include <Mscd_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2019/08/27                                              */
/*  2-0-0          :2022/07/15                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
