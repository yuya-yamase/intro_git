/* Fee_Periodic.c v2-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/PERIODIC/CODE                                         */
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
#include "../inc/Fee_Periodic_Internal.h"

/* D.F.C. header */
#include "../inc/Fee_Dfc.h"

#include "../inc/Fee_Record_Pos_Tbl.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Main condition for checking */
#define FEE_MAINSTATUS_IDLE         ((uint8)0x00U)      /* Idle */
#define FEE_MAINSTATUS_INVALID      ((uint8)0x0FU)      /* Invalid value */

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* Function Name | Fee_ExecPeriodict                                        */
/* Description   | Data Flash periodic processing execution instruction     */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF * ptstCPUDTFInfo : MHA management data          */
/*               | uint8 u1_callmode : type of periodic process             */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/

FUNC(void, FEE_CODE) Fee_ExecPeriodic( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo , uint8 u1_callmode )
{
    uint32          u4tStatus;                                  /* Processing state internal variable */
    
    /* Check processing results */
    if ( (ptstCPUDTFInfo->u1Result == FEE_RSP_TIMEOUT)
        || (ptstCPUDTFInfo->u1Result == FEE_RSP_NG_DTF_CTRL))
    {
        u4tStatus = FEE_STATUS_DONE;
    }
    else
    {
        /* If the result is not a timeout */
        /* DFC processing confirmation */
        u4tStatus = Fee_Periodic_ExecUnderLayer( ptstCPUDTFInfo , u1_callmode );
    }

    /* Loop while processing state internal variable is not EXIT */
    while ( u4tStatus != FEE_STATUS_EXIT )
    {
        /* Branched by processing state internal variable */
        switch ( u4tStatus )
        {
            case FEE_STATUS_CONT:
                u4tStatus = Fee_Periodic_ExecPeriodicSubCont( ptstCPUDTFInfo );
                break;

            case FEE_STATUS_DONE:
                u4tStatus = Fee_Periodic_ExecPeriodicSubDone( ptstCPUDTFInfo );
                break;

            default: /* others */
                u4tStatus = FEE_STATUS_EXIT;
                break;
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Fee_Periodic_ExecPeriodicSubCont                         */
/* Description   | Function to handle the requested jobs and the internal   */
/*               | management operations if the status is CONTINUE.         */
/*               | This function is a sub function for Fee_ExecPeriodic.    */
/* Preconditions | None                                                     */
/* Parameters    | CPUDTFInfo                                               */
/* Return Value  | Next Status                                              */
/*               |   FEE_STATUS_EXIT                                        */
/*               |   FEE_STATUS_DONE                                        */
/*               |   FEE_STATUS_CONT                                        */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Periodic_ExecPeriodicSubCont(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
){
    uint32 Rtn;
    uint8  ProcessStatus;

    ProcessStatus = CPUDTFInfo->u1ProcessStatus;

    if( ProcessStatus == FEE_STATUSIDREAD )
    {
        Rtn = Fee_ReadMain( CPUDTFInfo );
    }
    else if( ProcessStatus == FEE_STATUSWRITE )
    {
        Rtn = Fee_BWriteMain( CPUDTFInfo );
    }
    else if( ProcessStatus == FEE_STATUSMOVE )
    {
        Rtn = Fee_BWriteMain( CPUDTFInfo );
    }
    else /* ProcessStatus == FEE_STATUSIDLE */
    {
        /* Note : If the process status is an illegal value, this function execute this path.                       */
        /*      : However, the process status value is checked using redundancy RAM before calling this function.   */
        Rtn = FEE_STATUS_DONE;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Periodic_ExecPeriodicSubDone                         */
/* Description   | Function to finish the requested jobs                    */
/*               | if the status is DONE.                                   */
/*               | This function is a sub function for Fee_ExecPeriodic.    */
/* Preconditions | None                                                     */
/* Parameters    | CPUDTFInfo                                               */
/* Return Value  | Next Status                                              */
/*               |   FEE_STATUS_EXIT                                        */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Periodic_ExecPeriodicSubDone(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
){
    uint8   ExecResult;

    ExecResult = CPUDTFInfo->u1Result;

    if(( ExecResult == FEE_RSP_TIMEOUT )
    || ( ExecResult == FEE_RSP_NG_DTF_CTRL ))
    {
        if( CPUDTFInfo->u1ProcessStatus != FEE_STATUSIDLE )
        {
            Fee_RecordPosTbl_ClearPosArea( CPUDTFInfo->u1AreaNum );
        }
        Fee_Driver_AbortDfc();
    }

    Fee_RspHook( CPUDTFInfo );

    return FEE_STATUS_EXIT;
}

/****************************************************************************/
/* Function Name | Fee_Periodic_ExecUnderLayer                              */
/* Description   | This function handles underlayer jobs, MngDfc or Fls.    */
/* Preconditions | None                                                     */
/* Parameters    | CPUDTFInfo                                               */
/*               | u1_callmode : type of periodic process                   */
/* Return Value  | Status                                                   */
/*               |   FEE_STATUS_EXIT                                        */
/*               |   FEE_STATUS_DONE                                        */
/*               |   FEE_STATUS_CONT                                        */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Periodic_ExecUnderLayer(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo ,
    uint8 u1_callmode
){
    boolean IsWaitingForCancel;
    uint32  RtnStatus;

    IsWaitingForCancel = Fee_Driver_IsWaitingForCancel();
    if( IsWaitingForCancel == (boolean)TRUE )
    {
        RtnStatus = Fee_Periodic_ExecFlsForWaitingCancel( u1_callmode );
    }
    else if( CPUDTFInfo->u1Result == FEE_RSP_GARBLED_RAM )
    {
        RtnStatus = Fee_Periodic_ExecFlsForWaitingAbort( u1_callmode );
    }
    else
    {
        RtnStatus = Fee_Periodic_ExecMngDfc( CPUDTFInfo , u1_callmode );
    }

    return RtnStatus;
}

/****************************************************************************/
/* Function Name | Fee_Periodic_ExecFlsForWaitingCancel                     */
/* Description   | Function to handle FLS jobs while waiting asynchronous   */
/*               | cancel and execute cancel.                               */
/* Preconditions | None                                                     */
/* Parameters    | uint8 u1_callmode : type of periodic process             */
/* Return Value  | Status. This function returns only FEE_STATUS_EXIT,      */
/*               | because it is not wanted that Fee_ExecPeriodic() does    */
/*               | something.                                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Periodic_ExecFlsForWaitingCancel( uint8 u1_callmode )
{
    MemIf_StatusType DfcStatus;

    /* Return value is not checked.                                 */
    /* Instead of using the return value that is a result of FLS,   */
    /* this function uses the status of Fee_Dfc_GetStatus().        */
    (void)Fee_Dfc_ExecFlsMainFunction( u1_callmode );

    DfcStatus = Fee_Dfc_GetStatus();
    if( DfcStatus == MEMIF_IDLE )
    {
        Fee_Driver_AsyncCancel();
    }
    return FEE_STATUS_EXIT;
}

/****************************************************************************/
/* Function Name | Fee_Periodic_ExecFlsForWaitingAbort                      */
/* Description   | Function to handle FLS jobs while waiting asynchronous   */
/*               | abort and execute abort.                                 */
/* Preconditions | None                                                     */
/* Parameters    | uint8 u1_callmode : type of periodic process             */
/* Return Value  | Status. This function returns only FEE_STATUS_EXIT,      */
/*               | because it is not wanted that Fee_ExecPeriodic() does    */
/*               | something.                                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Periodic_ExecFlsForWaitingAbort( uint8 u1_callmode )
{
    MemIf_StatusType DfcStatus;

    /* Return value is not checked.                                 */
    /* Instead of using the return value that is a result of FLS,   */
    /* this function uses the status of Fee_Dfc_GetStatus().        */
    (void)Fee_Dfc_ExecFlsMainFunction( u1_callmode );

    DfcStatus = Fee_Dfc_GetStatus();
    if( DfcStatus == MEMIF_IDLE )
    {
        Fee_Driver_AsyncAbort();
    }
    return FEE_STATUS_EXIT;
}

/****************************************************************************/
/* Function Name | Fee_Periodic_ExecMngDfc                                  */
/* Description   | DFC periodic processing execution instruction            */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF * ptstCPUDTFInfo : MHA management data          */
/*               | uint8 u1_callmode : type of periodic process             */
/* Return Value  | Processing status                                        */
/*               | 0x00000002 : FEE_STATUS_EXIT : Processing                */
/*               | 0x00000003 : FEE_STATUS_DONE : Operation completed       */
/*               | 0x00000004 : FEE_STATUS_CONT : Idle                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Periodic_ExecMngDfc(
    P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo ,
    uint8 u1_callmode
){
    uint32          u4tStatus;                                  /* Processing state internal variable */
    uint32          u4tMngDFCResult;                            /* Data for periodic processing Flash write control processing result */
    uint8           u1tLower4BitMainStatus;

    /* Data Flash Control Management Processing for Periodic Processing */
    u4tMngDFCResult = Fee_MngDfcForPrd( u1_callmode );
    if ( u4tMngDFCResult == FEE_STATUS_BUSY )
    {
        /* In progress (STATUS _ BUSY) */
        /* Check main status */
        u1tLower4BitMainStatus = ptstCPUDTFInfo->u1MainStatus & (uint8)FEE_LOWER4BIT;
        switch ( u1tLower4BitMainStatus )
        {
            case FEE_MAINSTATUS_IDLE:
                /* When main state is idle */
                /* Set processing result to Data Flash controller error */
                ptstCPUDTFInfo->u1Result = FEE_RSP_NG_DTF_CTRL;
                /* Set processing state internal variable to DONE */
                u4tStatus = FEE_STATUS_DONE;
                break;
            case FEE_MAINSTATUS_INVALID:
                /* if main state is invalid */
                /* Set processing state internal variable to CONT */
                u4tStatus = FEE_STATUS_CONT;
                break;
            default:
                /* If the main state is not idle/invalid */
                /* Set processing state internal variable to EXIT */
                u4tStatus = FEE_STATUS_EXIT;
                break;
        }
    }
    else
    {
        /* If not in progress */
        /* Set processing state internal variable to CONT */
        u4tStatus = FEE_STATUS_CONT;
    }
    
    return u4tStatus;
}

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/09/13                                              */
/*  2-0-0          :2024/07/19                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
