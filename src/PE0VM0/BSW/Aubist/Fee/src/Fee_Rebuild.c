/* Fee_Rebuild.c v2-0-0                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/REBUILD/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee.h>

#include "../inc/Fee_Mpu_Dev_Const.h"

/* MHA (Data Flash) I/F header */
#include "../inc/Fee_Legacy.h"

/* MHA header */
#include "../inc/Fee_Lib.h"

/* MHA library header */
#include "../inc/Fee_Common.h"
#include "../inc/Fee_Rebuild_Internal.h"

/* D.F.C. header */
#include "../inc/Fee_Dfc.h"

#include "../inc/Fee_Record_Pos_Tbl.h"

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* Function Name | Fee_MoveData                                             */
/* Description   | Data transfer state management                           */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF * ptstCPUDTFInfo                                */
/*               |                      MHA management data                 */
/* Return Value  | Result of processing                                     */
/*               | 0x00000002 : u4gSTATUS_EXIT : Transferring               */
/*               |              (periodic processing terminated)            */
/*               | 0x00000003 : u4gSTATUS_DONE : Transfer complete          */
/*               | 0x00000004 : u4gSTATUS_CONT : Transferring (restartable) */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_MoveData( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* RETURN */
    
    /* Branch by substate */
    switch ( ptstCPUDTFInfo->u1SubStatus )
    {
        case FEE_SSTATUSWMIDLE:     /* For "Idol" */
            u4tReturn = Fee_MoveData_DoIdle( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWMSRCHMPS:  /* "Searching for last data location of transfer source" */
            u4tReturn = Fee_MoveData_DoSrchingWriteLastPos( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWMPREPSRCHMDT:      /* "Preparing to retrieve source data" */
            u4tReturn = Fee_MoveData_DoPrepSrchMoveRecord( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWMSRCHMDT:  /* "Searching for source data" */
            u4tReturn = Fee_MoveData_DoSrchingMoveRecord( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWMPREPSRCHSDT:      /* In case of "Preparing to retrieve destination data" */
            u4tReturn = Fee_MoveData_DoPrepSrchDestRecord( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWMSRCHSDT:  /* "Searching for transfer destination data" */
            u4tReturn = Fee_MoveData_DoSrchingDestRecord( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWMWRITE:        /* For "writing data" */
            u4tReturn = Fee_MoveData_DoMovingRecord( ptstCPUDTFInfo );
            break;
        default:                                /* Otherwise */
            u4tReturn = Fee_Rebuild_QuitFailure( ptstCPUDTFInfo );
            break;
    }
    
    /* RETURN RETURN */
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_MoveData_DoIdle                                      */
/* Description   | Data transfer state management (idle)                    */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF * ptstCPUDTFInfo                                */
/*               |                     MHA management data                  */
/* Return Value  | Result of processing                                     */
/*               | 0x00000002 : u4gSTATUS_EXIT : Transferring               */
/*               |             (periodic processing terminated)             */
/*               | 0x00000003 : u4gSTATUS_DONE : Transfer complete          */
/*               | 0x00000004 : u4gSTATUS_CONT : Transferring (restartable) */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_MoveData_DoIdle( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* RETURN */
    uint32          u4tLastDestWritePosAddress;
    uint32          u4tRcrdDataAreaStartAbsAddr;
    uint32          u4tBlockStartAddr;

    /* Valid Record Position TBL Initialization */
    Fee_RecordPosTbl_ClearPosArea( ptstCPUDTFInfo->u1AreaNum );
    u4tLastDestWritePosAddress = ptstCPUDTFInfo->u4WriteLastRecMngAbsAddr;
    /* Keep trailing records */
    if ( u4tLastDestWritePosAddress != FEE_ADDRESS_INVALID )
    {
        /* If there is source data */
        if ( u4tLastDestWritePosAddress >= (FEE_BLKSTARTADDRTBL[ptstCPUDTFInfo->u1MainBlockNo] + FEE_STARTRECORDPOS) )
        {
            /* Set tail record to source address when transferring data */
            ptstCPUDTFInfo->u4MoveSrcAddress = u4tLastDestWritePosAddress;
            /* Set sub status to "Preparing to search source data" */
            ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWMPREPSRCHMDT;
            /* Set EXIT in return */
            u4tReturn = FEE_STATUS_EXIT;
        }
        /* No source data */
        else
        {
            u4tReturn = Fee_Rebuild_QuitSuccess( ptstCPUDTFInfo );
        }
    }
    /* If no tail record is kept */
    else
    {
        /* Set an invalid value for the source address when transferring data */
        ptstCPUDTFInfo->u4MoveSrcAddress = FEE_ADDRESS_INVALID;
        /* Set read search start address */
        u4tBlockStartAddr = FEE_BLKSTARTADDRTBL[ptstCPUDTFInfo->u1MainBlockNo];
        u4tRcrdDataAreaStartAbsAddr = u4tBlockStartAddr
                                      + (uint32)( ptstCPUDTFInfo->ptstAreaInf->u2RcrdDataAreaStartAddr );
        ptstCPUDTFInfo->u4ReadSrchAddress = u4tRcrdDataAreaStartAbsAddr - (uint32)FEE_RECORDMNGINFOLEN;
        /* Set sub status to "Searching for last data position of transfer source" */
        ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWMSRCHMPS;
        /* Set return value to "Transferring (periodic processing ended)" */
        u4tReturn = FEE_STATUS_EXIT;
    }
    
    /* Set subblock record head address for -1 records to write address at data write and transfer */
    u4tBlockStartAddr = FEE_BLKSTARTADDRTBL[ptstCPUDTFInfo->u1SubBlockNo];
    ptstCPUDTFInfo->u4WriteLastRecMngAbsAddr = ( u4tBlockStartAddr
                                            + FEE_STARTRECORDPOS )
                                            - (uint32)FEE_RECORDMNGINFOLEN;
    ptstCPUDTFInfo->u4WriteLastRecDatAbsAddr = ( u4tBlockStartAddr
                                            + (uint32)(ptstCPUDTFInfo->ptstAreaInf->u2RcrdDataAreaStartAddr) )
                                            - (uint32)FEE_DATAAREA_REC_TAIL_OFFSET;
    
    /* RETURN RETURN */
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_MoveData_DoSrchingWriteLastPos                       */
/* Description   | Data transfer status management                          */
/*               |(while retrieving last data location of transfer source)  */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF * ptstCPUDTFInfo                                */
/*               |              MHA management data                         */
/* Return Value  | Result of processing                                     */
/*               | 0x00000002 : STATUS_EXIT : Search complete or searching  */
/*               |                              (Periodic processing ends)  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_MoveData_DoSrchingWriteLastPos( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32 u4tSrchFSResult;
    uint32 u4tReturn = FEE_STATUS_EXIT;

    u4tSrchFSResult = Fee_SrchFreeSpace( ptstCPUDTFInfo );

    switch ( u4tSrchFSResult )
    {
        case FEE_STATUS_OK:
            ptstCPUDTFInfo->u4MoveSrcAddress = ptstCPUDTFInfo->u4ReadSrchAddress;
            ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWMPREPSRCHMDT;
            break;
        case FEE_STATUS_BUSY:
            break;
        case FEE_STATUS_NG:
        default:
            u4tReturn = Fee_Rebuild_QuitSuccess( ptstCPUDTFInfo );
            break;
    }

    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_MoveData_DoPrepSrchMoveRecord                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_MoveData_DoPrepSrchMoveRecord( P2VAR(Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT) ptstCPUDTFInfo )
{
    Fee_Record_StateScMsStart();
    ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWMSRCHMDT;

    return FEE_STATUS_CONT;
}

/****************************************************************************/
/* Function Name | Fee_MoveData_DoSrchingMoveRecord                         */
/* Description   | Data transfer status management                          */
/*               | (searching for source data)                              */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF * ptstCPUDTFInfo                                */
/*               |                MHA management data                       */
/* Return Value  | Result of processing                                     */
/*               | 0x00000002: u4gSTATUS _ EXIT: Transferring               */
/*               |                    (periodic processing terminated)      */
/*               | 0x00000003: u4gSTATUS _ DONE: Transfer complete          */
/*               | 0x00000004: u4gSTATUS _ CONT: Transferring (restartable) */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_MoveData_DoSrchingMoveRecord( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* RETURN */
    uint32          u4tSearchActStatus;
    uint32          u4tSearchExecResult;

    /* Valid data retrieval for data transfer */
    u4tSearchActStatus = Fee_Record_StateScMsExec( ptstCPUDTFInfo, &u4tSearchExecResult );
    /* In Search */
    if ( u4tSearchActStatus == FEE_STATUS_EXIT )
    {
        /* Set return value to "Transferring (periodic processing ended)" */
        u4tReturn = FEE_STATUS_EXIT;
    }
    else if ( u4tSearchActStatus == FEE_STATUS_DONE )
    {
        /* "With data" */
        if ( u4tSearchExecResult == FEE_STATUS_OK )
        {
            /* Set write destination address for data transfer to ID-specified data read destination address */
            ptstCPUDTFInfo->u4ReadSrchAddress = ptstCPUDTFInfo->u4WriteLastRecMngAbsAddr;
            /* Set sub status to "Preparing to retrieve destination data" */
            ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWMPREPSRCHSDT;
            /* Set return value to "Transferring (restartable)" */
            u4tReturn = FEE_STATUS_CONT;
        }
        /* For "no data" */
        else /* u4tSearchExecResult == FEE_STATUS_NG */
        {
            u4tReturn = Fee_Rebuild_QuitSuccess( ptstCPUDTFInfo );
        }
    }
    else /* u4tSearchActStatus == FEE_STATUS_NG */
    {
        u4tReturn = Fee_Rebuild_QuitFailure( ptstCPUDTFInfo );
    }
    
    /* RETURN RETURN */
    return u4tReturn;
}


/****************************************************************************/
/* Function Name | Fee_MoveData_DoPrepSrchDestRecord                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_MoveData_DoPrepSrchDestRecord( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    Fee_Record_StateScMdStart();
    ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWMSRCHSDT;

    return FEE_STATUS_CONT;
}

/****************************************************************************/
/* Function Name | Fee_MoveData_DoPrepSrchDestRecord                        */
/* Description   | Data transfer status management                          */
/*               | (searching for destination data)                         */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF * ptstCPUDTFInfo                                */
/*               |                 MHA management data                      */
/* Return Value  | Result of processing                                     */
/*               | 0x00000002 : u4gSTATUS_EXIT : Transferring               */
/*               |(periodic processing terminated)                          */
/*               | 0x00000003 : u4gSTATUS_DONE : Transfer complete          */
/*               | 0x00000004 : u4gSTATUS_CONT : Transferring (restartable) */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_MoveData_DoSrchingDestRecord( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* RETURN */
    uint32          u4tSearchActStatus;
    uint32          u4tSearchExecResult;
    boolean         btCheckWriteSpaceResult;

    /* Data retrieval */
    u4tSearchActStatus = Fee_Record_StateScMdExec( ptstCPUDTFInfo, &u4tSearchExecResult );
    /* For "Processing Ongoing" */
    if ( u4tSearchActStatus == FEE_STATUS_EXIT )
    {
        /* Set return value to "Transferring (periodic processing ended)" */
        u4tReturn = FEE_STATUS_EXIT;
    }
    else if ( u4tSearchActStatus == FEE_STATUS_DONE )
    {
        /* "With valid data" */
        if ( u4tSearchExecResult == FEE_STATUS_OK )
        {
            /* Decrement the source address by one record when transferring data */
            ptstCPUDTFInfo->u4MoveSrcAddress -= (uint32)FEE_RECORDMNGINFOLEN;
            /* Set sub status to "Preparing to search source data" */
            ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWMPREPSRCHMDT;
            /* On the way to execution */
            u4tReturn = FEE_STATUS_EXIT;
        }
        /* For "no data" or "with invalid data" */
        else /* u4tSearchExecResult == FEE_STATUS_INVALID, FEE_STATUS_NG */
        {
            btCheckWriteSpaceResult = Fee_Record_CheckWriteSpace( ptstCPUDTFInfo->u2MovDataLen,
                                                                  (uint16)(ptstCPUDTFInfo->u1SubBlockNo),
                                                                  ptstCPUDTFInfo );
            /* If there is room for writing */
            if ( btCheckWriteSpaceResult == (boolean)TRUE )
            {
                Fee_Record_StateWtMvStart( ptstCPUDTFInfo );

                /* Set sub-state to 'Writing data' */
                ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWMWRITE;
                /* Set return value to "Transferring (periodic processing ended)" */
                u4tReturn = FEE_STATUS_EXIT;
            }
            /* If there is no space at the writing position */
            else
            {
                u4tReturn = Fee_Rebuild_QuitFailure( ptstCPUDTFInfo );
            }
        }
    }
    else /* u4tSearchActStatus == FEE_STATUS_NG */
    {
        u4tReturn = Fee_Rebuild_QuitFailure( ptstCPUDTFInfo );
    }

    /* RETURN */
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_MoveData_DoMovingRecord                              */
/* Description   | Data transfer status management (data writing)           */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF * ptstCPUDTFInfo                                */
/*               |                      MHA management data                 */
/* Return Value  | Result of processing                                     */
/*               | 0x00000002 : u4gSTATUS_EXIT : Transferring               */
/*               |             (periodic processing terminated)             */
/*               | 0x00000003 : u4gSTATUS_DONE : Transfer complete          */
/*               | 0x00000004 : u4gSTATUS_CONT : Transferring (restartable) */
/* Notes         | None                                                     */
/****************************************************************************/

FUNC(uint32, FEE_CODE) Fee_MoveData_DoMovingRecord( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* RETURN */
    uint32          u4tResult;                                  /* Results */

    /* Common processing during data write */
    u4tResult = Fee_Record_StateWtMvExec( ptstCPUDTFInfo );
    /* For "Processing Ongoing" */
    if ( u4tResult == FEE_STATUS_EXIT )
    {
        /* Set return value to "Transferring (periodic processing ended)" */
        u4tReturn = FEE_STATUS_EXIT;
    }
    /* In case of "write end" */
    else if ( u4tResult == FEE_STATUS_DONE )
    {
        /* Decrement the source address by one record when transferring data */
        ptstCPUDTFInfo->u4MoveSrcAddress -= (uint32)FEE_RECORDMNGINFOLEN;
        /* Set sub status to "Preparing to search source data" */
        ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWMPREPSRCHMDT;
        /* Set return value to "Transferring (periodic processing ended)" */
        u4tReturn = FEE_STATUS_EXIT;
    }
    /* For "write failed" */
    else
    {
        u4tReturn = Fee_Rebuild_QuitFailure( ptstCPUDTFInfo );
    }
    
    /* RETURN RETURN */
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_Rebuild_QuitSuccess                                  */
/* Description   | Function to execute process when rebuilding is quit      */
/*               | successfully.                                            */
/* Preconditions |                                                          */
/* Parameters    | ptstCPUDTFInfo   : Job information.                      */
/* Return Value  | Next status.                                             */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Rebuild_QuitSuccess(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, TYPEDEF ) CPUDTFInfo
){
    /* Set the job result. */
    CPUDTFInfo->u1Result = FEE_RSP_OK;

    /* Set next statuses */
    CPUDTFInfo->u1MainStatus = FEE_MSTATUSWBSEL;
    CPUDTFInfo->u1SubStatus = FEE_SSTATUSWSWEMOV;
    CPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSEIDLE;

    return FEE_STATUS_EXIT;
}

/****************************************************************************/
/* Function Name | Fee_Rebuild_QuitFailure                                  */
/* Description   | Function to execute process when rebuilding is quit      */
/*               | unsuccessfully.                                          */
/* Preconditions |                                                          */
/* Parameters    | ptstCPUDTFInfo   : Job information.                      */
/* Return Value  | Next status.                                             */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Rebuild_QuitFailure(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, TYPEDEF ) CPUDTFInfo
){
    /* Initialize the record position table. */
    Fee_RecordPosTbl_ClearPosArea( CPUDTFInfo->u1AreaNum );

    /* Set the job result. */
    CPUDTFInfo->u1Result = FEE_RSP_NG;

    /* Set next statuses */
    CPUDTFInfo->u1MainStatus = FEE_MSTATUSWBSEL;
    CPUDTFInfo->u1SubStatus = FEE_SSTATUSWSFAIL;
    CPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSFWSUSD;

    return FEE_STATUS_EXIT;
}

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/10/15                                              */
/*  2-0-0          :2021/07/29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
