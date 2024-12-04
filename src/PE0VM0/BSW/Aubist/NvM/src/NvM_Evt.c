/* NvM_Evt.c v2-1-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/EVT/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <NvM.h>
#include "../inc/NvM_Internal.h"
#include "../inc/NvM_Evt.h"
#include "../inc/NvM_Evt_Internal.h"
#include "../inc/NvM_Pif.h"
#include "../inc/NvM_Adb.h"
#include "../inc/NvM_Rwd.h"
#include "../usr/NvM_Dem_Connector.h"
#include "../usr/NvM_BswM_Connector.h"
#include <Mscd_Common.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

VAR( NvM_Evt_EventStatusBitType, NVM_VAR_NO_INIT ) NvM_Evt_EventStatus[NVM_EVT_ERR_EVENT_NUM];
VAR( uint8,                      NVM_VAR_NO_INIT ) NvM_Evt_FatalFailedHappened;

#define NVM_STOP_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CONST_32
#include <NvM_MemMap.h>

CONST( AB_83_ConstV NvM_Lib_ValueConvertPairType,    NVM_CONST )     NvM_JobIdToBlockRequestPair[NVM_SINGLE_JOBID_NUM] = 
{
    { (uint32)NVM_JOB_READ_BLOCK,                  (uint32)NVM_READ_BLOCK             },
    { (uint32)NVM_JOB_WRITE_BLOCK,                 (uint32)NVM_WRITE_BLOCK            },
    { (uint32)NVM_JOB_RESTORE_BLOCK_DEFAULTS,      (uint32)NVM_RESTORE_BLOCK_DEFAULTS },
    { (uint32)NVM_JOB_READ_PRAM_BLOCK,             (uint32)NVM_READ_BLOCK             },
    { (uint32)NVM_JOB_WRITE_PRAM_BLOCK,            (uint32)NVM_WRITE_BLOCK            },
    { (uint32)NVM_JOB_RESTORE_PRAM_BLOCK_DEFAULTS, (uint32)NVM_RESTORE_BLOCK_DEFAULTS },
    { (uint32)NVM_JOB_READ_ALL,                    (uint32)NVM_READ_ALL_BLOCK         },
    { (uint32)NVM_JOB_WRITE_ALL,                   (uint32)NVM_WRITE_ALL_BLOCK        }
};

CONST( AB_83_ConstV NvM_Lib_ValueConvertTableType,   NVM_CONST )     NvM_JobIdToBlockRequestTable = 
{
    (uint32)NVM_SINGLE_JOBID_NUM,
    NvM_JobIdToBlockRequestPair
};

CONST( AB_83_ConstV NvM_Lib_ValueConvertPairType,    NVM_CONST )     NvM_JobIdToMultiBlockRequestPair[NVM_MULTI_JOBID_NUM] = 
{
    { (uint32)NVM_JOB_CANCEL_WRITE_ALL,          (uint32)NVM_CANCEL_WRITE_ALL            },
    { (uint32)NVM_JOB_READ_ALL,                  (uint32)NVM_READ_ALL                    },
    { (uint32)NVM_JOB_WRITE_ALL,                 (uint32)NVM_WRITE_ALL                   }
};

CONST( AB_83_ConstV NvM_Lib_ValueConvertTableType,   NVM_CONST )      NvM_JobIdToMultiBlockRequestTable = 
{
    (uint32)NVM_MULTI_JOBID_NUM,
    NvM_JobIdToMultiBlockRequestPair
};

CONST( AB_83_ConstV NvM_Dem_EventIdType, NVM_CONST ) NvM_Evt_ErrEventToDemEventId[NVM_EVT_ERR_EVENT_NUM] = 
    {
        NVM_E_HARDWARE,             /* NVM_EVT_ERR_EVENT_HARDWARE           */
        NVM_E_INTEGRITY_FAILED,     /* NVM_EVT_ERR_EVENT_INTEGRITY_FAILED   */
        NVM_E_LOSS_OF_REDUNDANCY,   /* NVM_EVT_ERR_EVENT_LOSS_OF_REDUNDANCY */
        NVM_E_REQ_FAILED,           /* NVM_EVT_ERR_EVENT_REQ_FAILED         */
        NVM_E_VERIFY_FAILED,        /* NVM_EVT_ERR_EVENT_VERIFY_FAILED      */
        NVM_E_WRONG_BLOCK_ID        /* NVM_EVT_ERR_EVENT_WRONG_BLOCK_ID     */
    };

CONST( AB_83_ConstV uint32,              NVM_CONST ) NvM_Evt_DetailErrToErrRsltTbl[NVM_EVT_DETAIL_ERR_NUM] = 
    {
        MSCD_ERRINFO_NVM_ERR_JOB_TIMEOUT,                   /* NVM_EVT_DETAIL_ERR_JOB_TIMEOUT               */
        MSCD_ERRINFO_NVM_ERR_SYNC_MECHANISM_NG,             /* NVM_EVT_DETAIL_ERR_SYNC_MECHANISM_NG         */
        MSCD_ERRINFO_NVM_ERR_WRT_TO_PROT_SKIP,              /* NVM_EVT_DETAIL_ERR_WRT_TO_PROT_SKIP          */
        MSCD_ERRINFO_NVM_ERR_WRT_FRM_INVALID_RAM_SKIP,      /* NVM_EVT_DETAIL_ERR_WRT_FRM_INVALID_RAM_SKIP  */
        MSCD_ERRINFO_NVM_ERR_WRT_FRM_UNCHANGE_RAM_SKIP,     /* NVM_EVT_DETAIL_ERR_WRT_FRM_UNCHANGE_RAM_SKIP */
        MSCD_ERRINFO_NVM_ERR_READ_TO_VALID_RAM_SKIP,        /* NVM_EVT_DETAIL_ERR_READ_TO_VALID_RAM_SKIP    */
        MSCD_ERRINFO_NVM_ERR_ABORT,                         /* NVM_EVT_DETAIL_ERR_CANCEL_USER_REQ           */
        MSCD_ERRINFO_NVM_ERR_CANCEL_WRT_ALL,                /* NVM_EVT_DETAIL_ERR_CANCEL_WRT_ALL            */
        MSCD_ERRINFO_NVM_ERR_PREEMPT_IMM_WRT,               /* NVM_EVT_DETAIL_ERR_CANCEL_PREEMPT            */
        MSCD_ERRINFO_NVM_KIND_RESTORE,                      /* NVM_EVT_DETAIL_ERR_RESTORE                   */
        MSCD_ERRINFO_NVM_ERR_NODATA,                        /* NVM_EVT_DETAIL_ERR_NODATA                    */
        MSCD_ERRINFO_NVM_ERR_LOSS_OF_REDUNDANCY             /* NVM_EVT_DETAIL_ERR_LOSS_OF_REDUNDANCY        */
    };

#define NVM_STOP_SEC_CONST_32
#include <NvM_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* Function Name | NvM_Evt_Init                                             */
/* Description   | Initialization of the EVT unit                           */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Evt_Init( void )
{
    NvM_Evt_FatalFailedHappened = NVM_EVT_FATALFAILED_NOT_HAPPENED;
    return ;
}

/****************************************************************************/
/* Function Name | NvM_Evt_ReportDevelopmentError                           */
/* Description   | Notice of an error state at development                  */
/* Preconditions | None                                                     */
/* Parameters    | ModuleId   : Module Id                                   */
/*               | InstanceId : Instance Id                                 */
/*               | ServiceId  : Service Id                                  */
/*               | ErrorId    : Error Id                                    */
/* Return Value  | StatusType                                               */
/*               |  E_OK                                                    */
/*               |  E_NOT_OK                                                */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Evt_ReportDevelopmentError(
    uint16 ModuleId,
    uint8 InstanceId,
    uint8 ServiceId,
    uint8 ErrorId
){
    return( E_OK );
}

/****************************************************************************/
/* Function Name | NvM_Evt_JobResultChange                                  */
/* Description   | If this event is issued by other unit, this service      */
/*               | changes the job result, and notifies the job result.     */
/* Preconditions | None                                                     */
/* Parameters    | BlockId      : Block Id                                  */
/*               | JobId        : Job Id                                    */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Evt_JobResultChange(
    NvM_BlockIdType BlockId,
    uint32 JobId,
    NvM_RequestResultType JobResult
){
    if( (NvM_BlockIdType)NVM_RESERVED_BLOCKID_MULTIJOB == BlockId )
    {
        NvM_Evt_NfyMultiBlockResult( JobId, JobResult );
    }
    else
    {
        NvM_Evt_NfySingleBlockResult( BlockId, JobId, JobResult );
    }

    return;
}

/****************************************************************************/
/* Function Name | NvM_Evt_JobStart                                         */
/* Description   | If this event is issued by other unit, this service      */
/*               | notifies other modules and units of a job start.         */
/* Preconditions | None                                                     */
/* Parameters    | BlockId      : Block Id                                  */
/*               | JobId        : Job Id                                    */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Evt_JobStart(
    NvM_BlockIdType BlockId,
    uint32 JobId
){
    NvM_BlockRequestType BlockRequest;
    NvM_MultiBlockRequestType MultiBlockRequest;
    
    if( (NvM_BlockIdType)NVM_RESERVED_BLOCKID_MULTIJOB == BlockId )
    {
        MultiBlockRequest = (NvM_MultiBlockRequestType)NvM_Lib_ConvertValue( JobId, NVM_EVT_MULTI_BLOCK_REQUEST_INVALID, &NvM_JobIdToMultiBlockRequestTable );
        /* Notify Mscd of multi job start timing */
        Mscd_Msif_MultiBlockJobStartHook( MultiBlockRequest );
    }
    else
    {
        BlockRequest = (NvM_BlockRequestType)NvM_Lib_ConvertValue( JobId, NVM_EVT_SINGLE_BLOCK_REQUEST_INVALID, &NvM_JobIdToBlockRequestTable );
        /* Notify Mscd of single job start timing */
        Mscd_Msif_SingleBlockJobStartHook( BlockId, BlockRequest );
        
        if( BlockRequest == (NvM_BlockRequestType)NVM_READ_BLOCK )
        {
            NvM_Evt_EventStatus[NVM_EVT_ERR_EVENT_HARDWARE] = NVM_EVT_EVENT_STATUS_BIT_UNINSPECTED;
            NvM_Evt_EventStatus[NVM_EVT_ERR_EVENT_INTEGRITY_FAILED] = NVM_EVT_EVENT_STATUS_BIT_UNINSPECTED;
            NvM_Evt_EventStatus[NVM_EVT_ERR_EVENT_REQ_FAILED] = NVM_EVT_EVENT_STATUS_BIT_UNINSPECTED;
            NvM_Evt_EventStatus[NVM_EVT_ERR_EVENT_VERIFY_FAILED] = NVM_EVT_EVENT_STATUS_BIT_UNINSPECTED;
            NvM_Evt_EventStatus[NVM_EVT_ERR_EVENT_WRONG_BLOCK_ID] = NVM_EVT_EVENT_STATUS_BIT_UNINSPECTED;
            NvM_Evt_EventStatus[NVM_EVT_ERR_EVENT_LOSS_OF_REDUNDANCY] = NVM_EVT_EVENT_STATUS_BIT_UNINSPECTED;
        }
        else if( BlockRequest == (NvM_BlockRequestType)NVM_WRITE_BLOCK )
        {
            NvM_Evt_EventStatus[NVM_EVT_ERR_EVENT_HARDWARE] = NVM_EVT_EVENT_STATUS_BIT_UNINSPECTED;
            NvM_Evt_EventStatus[NVM_EVT_ERR_EVENT_INTEGRITY_FAILED] = NVM_EVT_EVENT_STATUS_BIT_UNINSPECTED;
            NvM_Evt_EventStatus[NVM_EVT_ERR_EVENT_REQ_FAILED] = NVM_EVT_EVENT_STATUS_BIT_UNINSPECTED;
            NvM_Evt_EventStatus[NVM_EVT_ERR_EVENT_VERIFY_FAILED] = NVM_EVT_EVENT_STATUS_BIT_UNINSPECTED;
            NvM_Evt_EventStatus[NVM_EVT_ERR_EVENT_WRONG_BLOCK_ID] = NVM_EVT_EVENT_STATUS_BIT_UNINSPECTED;
            NvM_Evt_EventStatus[NVM_EVT_ERR_EVENT_LOSS_OF_REDUNDANCY] = NVM_EVT_EVENT_STATUS_BIT_UNINSPECTED;
        }
        else
        {
            /* Do Nothing */
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | NvM_Evt_JobEnd                                           */
/* Description   | If this event is issued by other unit, this service      */
/*               | notifies other modules and units of a job end.           */
/* Preconditions | None                                                     */
/* Parameters    | BlockId      : Block Id                                  */
/*               | JobId        : Job Id                                    */
/*               | JobResult    : Job result                                */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Evt_JobEnd(
    NvM_BlockIdType BlockId,
    uint32 JobId
){
    NvM_BlockRequestType BlockRequest;
    NvM_MultiBlockRequestType MultiBlockRequest;

    if( (NvM_BlockIdType)NVM_RESERVED_BLOCKID_MULTIJOB == BlockId )
    {
        MultiBlockRequest = (NvM_MultiBlockRequestType)NvM_Lib_ConvertValue( JobId, NVM_EVT_MULTI_BLOCK_REQUEST_INVALID, &NvM_JobIdToMultiBlockRequestTable );
        /* Notify Mscd of multi job end timing */
        Mscd_Msif_MultiBlockJobEndHook( MultiBlockRequest );
    }
    else
    {
        BlockRequest = (NvM_BlockRequestType)NvM_Lib_ConvertValue( JobId, NVM_EVT_SINGLE_BLOCK_REQUEST_INVALID, &NvM_JobIdToBlockRequestTable );
        /* Notify Mscd of single job end timing */
        Mscd_Msif_SingleBlockJobEndHook( BlockId, BlockRequest );

        if( BlockRequest == (NvM_BlockRequestType)NVM_READ_BLOCK )
        {
            NvM_Evt_ReportProductionErrorStatus( NVM_EVT_ERR_EVENT_HARDWARE );
            NvM_Evt_ReportProductionErrorStatus( NVM_EVT_ERR_EVENT_INTEGRITY_FAILED );
            NvM_Evt_ReportProductionErrorStatus( NVM_EVT_ERR_EVENT_REQ_FAILED );
            NvM_Evt_ReportProductionErrorStatus( NVM_EVT_ERR_EVENT_VERIFY_FAILED );
            NvM_Evt_ReportProductionErrorStatus( NVM_EVT_ERR_EVENT_WRONG_BLOCK_ID );
            NvM_Evt_ReportProductionErrorStatus( NVM_EVT_ERR_EVENT_LOSS_OF_REDUNDANCY );
        }
        else if( BlockRequest == (NvM_BlockRequestType)NVM_WRITE_BLOCK )
        {
            NvM_Evt_ReportProductionErrorStatus( NVM_EVT_ERR_EVENT_HARDWARE );
            NvM_Evt_ReportProductionErrorStatus( NVM_EVT_ERR_EVENT_INTEGRITY_FAILED );
            NvM_Evt_ReportProductionErrorStatus( NVM_EVT_ERR_EVENT_REQ_FAILED );
            NvM_Evt_ReportProductionErrorStatus( NVM_EVT_ERR_EVENT_VERIFY_FAILED );
            NvM_Evt_ReportProductionErrorStatus( NVM_EVT_ERR_EVENT_WRONG_BLOCK_ID );
            NvM_Evt_ReportProductionErrorStatus( NVM_EVT_ERR_EVENT_LOSS_OF_REDUNDANCY );
        }
        else
        {
            /* Do Nothing */
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | NvM_Evt_SglBlkProcStart                                  */
/* Description   | If this event is issued by other unit, this service      */
/*               | notifies other modules and units of single block         */
/*               | processing start.                                        */
/* Preconditions | None                                                     */
/* Parameters    | BlockId      : Block Id                                  */
/*               | JobId        : Job Id                                    */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Evt_SglBlkProcStart(
    NvM_BlockIdType BlockId,
    uint32 JobId
){
    NvM_BlockRequestType BlockRequest = (NvM_BlockRequestType)NvM_Lib_ConvertValue( JobId, NVM_EVT_SINGLE_BLOCK_REQUEST_INVALID, &NvM_JobIdToBlockRequestTable );

    if( BlockRequest == (NvM_BlockRequestType)NVM_READ_ALL_BLOCK )
    {
        Mscd_Msif_SingleBlockJobStartHook( BlockId, BlockRequest );

        NvM_Evt_EventStatus[NVM_EVT_ERR_EVENT_HARDWARE] = NVM_EVT_EVENT_STATUS_BIT_UNINSPECTED;
        NvM_Evt_EventStatus[NVM_EVT_ERR_EVENT_INTEGRITY_FAILED] = NVM_EVT_EVENT_STATUS_BIT_UNINSPECTED;
        NvM_Evt_EventStatus[NVM_EVT_ERR_EVENT_REQ_FAILED] = NVM_EVT_EVENT_STATUS_BIT_UNINSPECTED;
        NvM_Evt_EventStatus[NVM_EVT_ERR_EVENT_VERIFY_FAILED] = NVM_EVT_EVENT_STATUS_BIT_UNINSPECTED;
        NvM_Evt_EventStatus[NVM_EVT_ERR_EVENT_WRONG_BLOCK_ID] = NVM_EVT_EVENT_STATUS_BIT_UNINSPECTED;
        NvM_Evt_EventStatus[NVM_EVT_ERR_EVENT_LOSS_OF_REDUNDANCY] = NVM_EVT_EVENT_STATUS_BIT_UNINSPECTED;
    }
    else if( BlockRequest == (NvM_BlockRequestType)NVM_WRITE_ALL_BLOCK )
    {
        Mscd_Msif_SingleBlockJobStartHook( BlockId, BlockRequest );

        NvM_Evt_EventStatus[NVM_EVT_ERR_EVENT_HARDWARE] = NVM_EVT_EVENT_STATUS_BIT_UNINSPECTED;
        NvM_Evt_EventStatus[NVM_EVT_ERR_EVENT_INTEGRITY_FAILED] = NVM_EVT_EVENT_STATUS_BIT_UNINSPECTED;
        NvM_Evt_EventStatus[NVM_EVT_ERR_EVENT_REQ_FAILED] = NVM_EVT_EVENT_STATUS_BIT_UNINSPECTED;
        NvM_Evt_EventStatus[NVM_EVT_ERR_EVENT_VERIFY_FAILED] = NVM_EVT_EVENT_STATUS_BIT_UNINSPECTED;
        NvM_Evt_EventStatus[NVM_EVT_ERR_EVENT_WRONG_BLOCK_ID] = NVM_EVT_EVENT_STATUS_BIT_UNINSPECTED;
        NvM_Evt_EventStatus[NVM_EVT_ERR_EVENT_LOSS_OF_REDUNDANCY] = NVM_EVT_EVENT_STATUS_BIT_UNINSPECTED;
    }
    else
    {
        /* Do Nothing */
    }

    return;
}

/****************************************************************************/
/* Function Name | NvM_Evt_SglBlkProcEnd                                    */
/* Description   | If this event is issued by other unit, this service      */
/*               | notifies other modules and units of single block         */
/*               | processing end.                                          */
/* Preconditions | None                                                     */
/* Parameters    | BlockId      : Block Id                                  */
/*               | JobId        : Job Id                                    */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Evt_SglBlkProcEnd(
    NvM_BlockIdType BlockId,
    uint32 JobId
){
    NvM_BlockRequestType BlockRequest = (NvM_BlockRequestType)NvM_Lib_ConvertValue( JobId, NVM_EVT_SINGLE_BLOCK_REQUEST_INVALID, &NvM_JobIdToBlockRequestTable );

    if( BlockRequest == (NvM_BlockRequestType)NVM_READ_ALL_BLOCK )
    {
        Mscd_Msif_SingleBlockJobEndHook( BlockId, BlockRequest );

        NvM_Evt_ReportProductionErrorStatus( NVM_EVT_ERR_EVENT_HARDWARE );
        NvM_Evt_ReportProductionErrorStatus( NVM_EVT_ERR_EVENT_INTEGRITY_FAILED );
        NvM_Evt_ReportProductionErrorStatus( NVM_EVT_ERR_EVENT_REQ_FAILED );
        NvM_Evt_ReportProductionErrorStatus( NVM_EVT_ERR_EVENT_VERIFY_FAILED );
        NvM_Evt_ReportProductionErrorStatus( NVM_EVT_ERR_EVENT_WRONG_BLOCK_ID );
        NvM_Evt_ReportProductionErrorStatus( NVM_EVT_ERR_EVENT_LOSS_OF_REDUNDANCY );
    }
    else if( BlockRequest == (NvM_BlockRequestType)NVM_WRITE_ALL_BLOCK )
    {
        Mscd_Msif_SingleBlockJobEndHook( BlockId, BlockRequest );

        NvM_Evt_ReportProductionErrorStatus( NVM_EVT_ERR_EVENT_HARDWARE );
        NvM_Evt_ReportProductionErrorStatus( NVM_EVT_ERR_EVENT_INTEGRITY_FAILED );
        NvM_Evt_ReportProductionErrorStatus( NVM_EVT_ERR_EVENT_REQ_FAILED );
        NvM_Evt_ReportProductionErrorStatus( NVM_EVT_ERR_EVENT_VERIFY_FAILED );
        NvM_Evt_ReportProductionErrorStatus( NVM_EVT_ERR_EVENT_WRONG_BLOCK_ID );
        NvM_Evt_ReportProductionErrorStatus( NVM_EVT_ERR_EVENT_LOSS_OF_REDUNDANCY );
    }
    else
    {
        /* Do Nothing */
    }

    return;
}

/****************************************************************************/
/* Function Name | NvM_Evt_ReadStart                                        */
/* Description   | Event when start reading from NvBlock.                   */
/* Preconditions | None                                                     */
/* Parameters    | BlockId      : Block Id                                  */
/*               | DstPtr       : Pointer to the RAM data block.            */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Evt_ReadStart(
    NvM_BlockIdType BlockId,
    P2VAR( uint8, AUTOMATIC, NVM_APPL_DATA ) DstPtr
){
    NvM_Rwd_ReadDataNotificationInit( BlockId, DstPtr );
    
    return;
}

/****************************************************************************/
/* Function Name | NvM_Evt_ReadEndInSuccess                                 */
/* Description   | Event when finished in success reading from NvBlock.     */
/* Preconditions | None                                                     */
/* Parameters    | BlockId      : Block Id                                  */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Evt_ReadEndInSuccess(
    NvM_BlockIdType BlockId
){
    boolean IsTemporary;
    IsTemporary = NvM_Rwd_NvM_IsDstRamTemporary();
    if( IsTemporary == (boolean)FALSE )
    {
        NvM_Adb_SetRamBlockStatus( BlockId, NVM_ADB_PRAM_VALID_UNCHANGED );
    }
    
    return;
}

/****************************************************************************/
/* Function Name | NvM_Evt_ReadEndInFailure                                 */
/* Description   | Event when finished in failure reading from NvBlock.     */
/* Preconditions | None                                                     */
/* Parameters    | BlockId      : Block Id                                  */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Evt_ReadEndInFailure(
    NvM_BlockIdType BlockId
){
    boolean IsTemporary;
    IsTemporary = NvM_Rwd_NvM_IsDstRamTemporary();
    if( IsTemporary == (boolean)FALSE )
    {
        NvM_Adb_SetRamBlockStatus( BlockId, NVM_ADB_PRAM_INVALID_UNCHANGED );
    }
    
    return;
}

/****************************************************************************/
/* Function Name | NvM_Evt_WriteStart                                       */
/* Description   | Event when start writing from NvBlock.                   */
/* Preconditions | None                                                     */
/* Parameters    | BlockId      : Block Id                                  */
/*               | SrcPtr       : Pointer to the RAM data block.            */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Evt_WriteStart(
    NvM_BlockIdType BlockId,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) SrcPtr
){
    NvM_Rwd_WriteDataAcquisitionInit( BlockId, SrcPtr );
    
    return;
}

/****************************************************************************/
/* Function Name | NvM_Evt_WriteEndInSuccess                                */
/* Description   | Event when finished in success writing from NvBlock.     */
/* Preconditions | None                                                     */
/* Parameters    | BlockId      : Block Id                                  */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Evt_WriteEndInSuccess(
    NvM_BlockIdType BlockId
){
    boolean IsTemporary;
    IsTemporary = NvM_Rwd_NvM_IsSrcRamTemporary();
    if( IsTemporary == (boolean)FALSE )
    {
        NvM_Adb_SetRamBlockStatus( BlockId, NVM_ADB_PRAM_VALID_UNCHANGED );
    }
    
    return;
}

/****************************************************************************/
/* Function Name | NvM_Evt_WriteEndInFailure                                */
/* Description   | Event when finished in failure writing from NvBlock.     */
/* Preconditions | None                                                     */
/* Parameters    | BlockId      : Block Id                                  */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Evt_WriteEndInFailure(
    NvM_BlockIdType BlockId
){
    boolean IsTemporary;
    IsTemporary = NvM_Rwd_NvM_IsSrcRamTemporary();
    if( IsTemporary == (boolean)FALSE )
    {
        NvM_Adb_SetRamBlockStatus( BlockId, NVM_ADB_PRAM_INVALID_UNCHANGED );
    }
    
    return;
}

/****************************************************************************/
/* Function Name | NvM_Evt_RestoreStart                                     */
/* Description   | Event when start restoring to RamBlock.                  */
/* Preconditions | None                                                     */
/* Parameters    | BlockId      : Block Id                                  */
/*               | DstPtr       : Pointer to the RAM data block.            */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Evt_RestoreStart(
    NvM_BlockIdType BlockId,
    P2VAR( uint8, AUTOMATIC, NVM_APPL_DATA ) DstPtr
){
    NvM_Rwd_ReadDataNotificationInit( BlockId, DstPtr );
    
    return;
}

/****************************************************************************/
/* Function Name | NvM_Evt_RestoreEndInSuccess                              */
/* Description   | Event when finished in success restoring to RamBlock.    */
/* Preconditions | None                                                     */
/* Parameters    | BlockId      : Block Id                                  */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Evt_RestoreEndInSuccess(
    NvM_BlockIdType BlockId
){
    boolean IsTemporary;
    IsTemporary = NvM_Rwd_NvM_IsDstRamTemporary();
    if( IsTemporary == (boolean)FALSE )
    {
        NvM_Adb_SetRamBlockStatus( BlockId, NVM_ADB_PRAM_VALID_CHANGED );
    }
    
    return;
}

/****************************************************************************/
/* Function Name | NvM_Evt_RestoreEndInFailure                              */
/* Description   | Event when finished in failure restoring to RamBlock.    */
/* Preconditions | None                                                     */
/* Parameters    | BlockId      : Block Id                                  */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Evt_RestoreEndInFailure(
    NvM_BlockIdType BlockId
){
    boolean IsTemporary;
    IsTemporary = NvM_Rwd_NvM_IsDstRamTemporary();
    if( IsTemporary == (boolean)FALSE )
    {
        NvM_Adb_SetRamBlockStatus( BlockId, NVM_ADB_PRAM_INVALID_UNCHANGED );
    }
    
    return;
}

/****************************************************************************/
/* Function Name | NvM_Evt_InspectionErrorEventStart                        */
/* Description   | Event when start inspection error event.                 */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Evt_InspectionErrorEventStart(
    uint8 ErrEvent
){
    if( NvM_Evt_EventStatus[ErrEvent] == (NvM_Evt_EventStatusBitType)NVM_EVT_EVENT_STATUS_BIT_UNINSPECTED )
    {
        NvM_Evt_EventStatus[ErrEvent] = NVM_EVT_EVENT_STATUS_BIT_PASSED;
    }
    
    return;
}

/****************************************************************************/
/* Function Name | NvM_Evt_DetectionErrorEvent                              */
/* Description   | Event when detected error event.                         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Evt_DetectionErrorEvent(
    uint8 ErrEvent
){
    NvM_Evt_EventStatus[ErrEvent] = NVM_EVT_EVENT_STATUS_BIT_FAILED;
    
    return;
}

/****************************************************************************/
/* Function Name | NvM_Evt_DetectionDetailError                             */
/* Description   | Event when detected detail error.                        */
/* Preconditions | None                                                     */
/* Parameters    | DetailError : Kind of detected detail error.             */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Evt_DetectionDetailError(
    uint8 DetailError
){
    uint32 ErrorResult;
    
    ErrorResult = NvM_Evt_DetailErrToErrRsltTbl[DetailError];
    Mscd_ErrorInfo_UpdateErrorResult( ErrorResult );
    
    return;
}

/****************************************************************************/
/* Function Name | NvM_Evt_FatalFailedNotification                          */
/* Description   | This function is called when any fatal failed error      */
/*               | happened.                                                */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Evt_FatalFailedNotification( void )
{
    Mscd_ErrorInfo_DetectErrorFactor( MSCD_ERRINFO_ERRORFACTOR_NVM_FATALERROR );
    NvM_Evt_FatalFailedHappened = NVM_EVT_FATALFAILED_HAPPENED;

    return;
}

/****************************************************************************/
/* Function Name | NvM_Evt_IsFatalFailed                                    */
/* Description   | This function for checking fatal failed error            */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( boolean, NVM_CODE )
NvM_Evt_IsFatalFailed( void )
{
    boolean Rtn = TRUE;

    if( NvM_Evt_FatalFailedHappened == (uint8)NVM_EVT_FATALFAILED_NOT_HAPPENED )
    {
        Rtn = FALSE;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Evt_SetFatalFailed                                   */
/* Description   | This function for setting fatal failed error             */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Evt_SetFatalFailed( void )
{
    NvM_Evt_FatalFailedHappened = NVM_EVT_FATALFAILED_HAPPENED;

    return;
}

/****************************************************************************/
/* Function Name | NvM_Evt_WriteRamBlockToNvm                               */
/* Description   | Refer for write data                                     */
/* Preconditions | None                                                     */
/* Parameters    | NvMBuffer : Pointer of data to write in                  */
/* Return Value  | StatusType                                               */
/*               |  E_OK                                                    */
/*               |  E_NOT_OK                                                */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Evt_WriteRamBlockToNvm(
    NvM_BlockIdType BlockId,
    P2VAR( uint8, AUTOMATIC, NVM_VAR_NO_INIT ) NvMBuffer
){
    Std_ReturnType  CbkResult;

#if ( NVM_USE_COMMON_RAM_MIRROR_CALLBACK == STD_ON )
    CbkResult = NvMCommonWriteRamBlockToNvCallback( BlockId, NvMBuffer );
#else /* NVM_USE_COMMON_RAM_MIRROR_CALLBACK == STD_OFF */
    CbkResult = NvMBlockDescriptors[BlockId].NvMWriteRamBlockToNvCallback( NvMBuffer );
#endif /* NVM_USE_COMMON_RAM_MIRROR_CALLBACK */
    return ( CbkResult );
}

/****************************************************************************/
/* Function Name | NvM_Evt_ReadRamBlockFromNvm                              */
/* Description   | Notice of reading data                                   */
/* Preconditions | None                                                     */
/* Parameters    | NvMBuffer : Pointer of reading data                      */
/* Return Value  | StatusType                                               */
/*               |  E_OK                                                    */
/*               |  E_NOT_OK                                                */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Evt_ReadRamBlockFromNvm(
    NvM_BlockIdType BlockId,
    P2CONST( uint8, AUTOMATIC, NVM_VAR_NO_INIT ) NvMBuffer
){
    Std_ReturnType  CbkResult;

#if ( NVM_USE_COMMON_RAM_MIRROR_CALLBACK == STD_ON )
    CbkResult = NvMCommonReadRamBlockFromNvCallback( BlockId, NvMBuffer );
#else /* NVM_USE_COMMON_RAM_MIRROR_CALLBACK == STD_OFF */
    CbkResult = NvMBlockDescriptors[BlockId].NvMReadRamBlockFromNvCallback( NvMBuffer );
#endif /* NVM_USE_COMMON_RAM_MIRROR_CALLBACK */

    return ( CbkResult );
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | NvM_Evt_NfySingleBlockResult                             */
/* Description   | Single block process result notification to other        */
/*               | function cluster.                                        */
/* Preconditions | None                                                     */
/* Parameters    | BlockId   : Block Id coressponding to single block job.  */
/*               | JobId        : Job Id                                    */
/*               | JobResult : Request single block job result.             */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Evt_NfySingleBlockResult(
    NvM_BlockIdType BlockId,
    uint32 JobId,
    NvM_RequestResultType JobResult
){
    NvM_BlockRequestType BlockRequest;
    
#if ( NVM_USE_COMMON_SINGLE_BLOCK_CALLBACK == STD_ON )
    CONST(AB_83_ConstV NvM_CommonSingleBlockCallbackType, NVM_CONFIG_DATA) FuncSingleBlockCallback = NvMCommonSingleBlockCallback;
    NvM_CommonSingleBlockCallbackType SingleBlockCallbackPointer;
#else /* NVM_USE_COMMON_SINGLE_BLOCK_CALLBACK == STD_OFF */
    CONST(AB_83_ConstV NvM_SingleBlockCallbackType, NVM_CONFIG_DATA)       FuncSingleBlockCallback = NvMBlockDescriptors[BlockId].NvMSingleBlockCallback;
    NvM_SingleBlockCallbackType       SingleBlockCallbackPointer;
#endif /* NVM_USE_COMMON_SINGLE_BLOCK_CALLBACK */

    if( ( NvMBlockDescriptors[BlockId].NvMBlockFlags & (NvM_BlockFlagsType)NVM_BSWM_BLOCK_STATUS_INFORMATION ) == (NvM_BlockFlagsType)NVM_BSWM_BLOCK_STATUS_INFORMATION )
    {
        NvM_BswM_CurrentBlockMode ( BlockId, JobResult );
    }

    SingleBlockCallbackPointer = FuncSingleBlockCallback;
    if(( JobResult != (NvM_RequestResultType)NVM_REQ_PENDING )    /* SWS_NvM_00467, an  asynchronous  single block request has been FINISHED */
    && ( SingleBlockCallbackPointer != NULL_PTR ))
    {
        BlockRequest = (NvM_RequestResultType)NvM_Lib_ConvertValue( JobId, NVM_EVT_SINGLE_BLOCK_REQUEST_INVALID, &NvM_JobIdToBlockRequestTable );
        
        /* Return value is not checked. Cannot support even if E_NOT_OK is notified by a user. */
#if ( NVM_USE_COMMON_SINGLE_BLOCK_CALLBACK == STD_ON )
        (void)FuncSingleBlockCallback( BlockRequest, BlockId, JobResult );
#else /* NVM_USE_COMMON_SINGLE_BLOCK_CALLBACK == STD_OFF */
        (void)FuncSingleBlockCallback( BlockRequest, JobResult );
#endif /* NVM_USE_COMMON_SINGLE_BLOCK_CALLBACK */
    }

    return;
}

/****************************************************************************/
/* Function Name | NvM_Evt_NfyMultiBlockResult                              */
/* Description   | Multi block process result notification to other         */
/*               | function cluster.                                        */
/* Preconditions | None                                                     */
/* Parameters    | JobId        : Job Id                                    */
/*               | JobResult : Request multi block job result.              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Evt_NfyMultiBlockResult(
    uint32 JobId,
    NvM_RequestResultType JobResult
){
#if ( NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION != STD_ON )
    CONST(AB_83_ConstV NvM_MultiBlockCallbackType, NVM_CONFIG_DATA) FuncMultiBlockCallback = NvMMultiBlockCallback;
    NvM_MultiBlockCallbackType MultiBlockCallbackPointer;
#endif
    NvM_MultiBlockRequestType MultiBlockRequest = (NvM_MultiBlockRequestType)NvM_Lib_ConvertValue( JobId, NVM_EVT_MULTI_BLOCK_REQUEST_INVALID, &NvM_JobIdToMultiBlockRequestTable );
    
#if ( NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION == STD_ON )
    NvM_BswM_CurrentJobMode ( MultiBlockRequest, JobResult );
#else
    MultiBlockCallbackPointer = FuncMultiBlockCallback;
    if(( JobResult != (NvM_RequestResultType)NVM_REQ_PENDING )    /* SWS_NvM_00468, An asynchronous multi block request has been FINISHED */
    && ( MultiBlockCallbackPointer != NULL_PTR ))
    {
        FuncMultiBlockCallback( MultiBlockRequest, JobResult );
    }
#endif

    return;
}

/****************************************************************************/
/* Function Name | NvM_Evt_ReportProductionErrorStatus                      */
/* Description   | Report a production error status of specific event id.   */
/* Preconditions | None                                                     */
/* Parameters    | ErrEvent       : Error Event Id                          */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Evt_ReportProductionErrorStatus(
    uint8 ErrEvent
){
#if ( NVM_DEV_ERROR_DETECT == STD_OFF )
    NvM_Evt_EventStatusBitType EventStatusBit = NvM_Evt_EventStatus[ErrEvent];
    NvM_Dem_EventIdType            DemEventId     = NvM_Evt_ErrEventToDemEventId[ErrEvent];
    
    if( EventStatusBit == (NvM_Evt_EventStatusBitType)NVM_EVT_EVENT_STATUS_BIT_PASSED )
    {
        NvM_Dem_ReportErrorStatus( DemEventId, NVM_DEM_EVENT_STATUS_PASSED );
    }
    else if( EventStatusBit == (NvM_Evt_EventStatusBitType)NVM_EVT_EVENT_STATUS_BIT_FAILED )
    {
        NvM_Dem_ReportErrorStatus( DemEventId, NVM_DEM_EVENT_STATUS_FAILED );
    }
    else
    {
        /* Do Nothing */
    }
#endif /* NVM_DEV_ERROR_DETECT == STD_OFF */

    return;
}

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2019/01/09                                              */
/*  1-2-0          :2019/08/26                                              */
/*  2-0-0          :2021/06/09                                              */
/*  2-1-0          :2022/07/20                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
