/* Fee_Driver.c v1-1-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/DRIVER/CODE                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee.h>
#include <Fee_Ext.h>

#include "../inc/Fee_Mpu_Dev_Const.h"

#include "../inc/Fee_Driver_Internal.h"

#include <Mscd_Common.h>

/* MHA (Data Flash) I/F header */
#include "../inc/Fee_Legacy.h"
#include "../inc/Fee_Pif.h"

/* MHA header */
#include "../inc/Fee_Lib.h"

/* MHA library header */
#include "../inc/Fee_Common.h"


/* D.F.C. header */
#include "../inc/Fee_Dfc.h"
#include "../inc/Fee_Ram.h"

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

#define FEE_START_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

VAR( boolean, FEE_VAR_NO_INIT ) Fee_Driver_WaitCancelFlag;

#define FEE_STOP_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* Function Name | Fee_Driver_Init                                          */
/* Description   | Function to initialize the FEE module and                */
/*               | the under module.                                        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Driver_Init( void )
{
    Fee_Dfc_Init();
    Fee_Driver_InitRam();

    Fee_Driver_WaitCancelFlag = FALSE;

    return;
}

/****************************************************************************/
/* Function Name | Fee_Driver_Cancel                                        */
/* Description   | Function to cancel the FEE module and the under module.  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | The cancellation result                                  */
/*               |  E_OK     : The cancellation is completed. A next        */
/*               |             request is able to accept.                   */
/*               |  E_NOT_OK : The cancellation is not completed. The       */
/*               |             caller needs to wait the cancellation with   */
/*               |             MainFunction.                                */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, FEE_CODE )
Fee_Driver_Cancel( void )
{
    Std_ReturnType              Rtn = E_NOT_OK;
    MemIf_StatusType            DfcStatus;
    boolean                     ExecCancel = FALSE;
    Fee_ExtDirect_ReturnType    ExtDirectResult;

    /* Regardless of own status, this function cancels the under module for stopping malfunction. */
    Fee_Dfc_Cancel();

    DfcStatus = Fee_Dfc_GetStatus();
    if( DfcStatus == MEMIF_IDLE )
    {
        /* If the under module is idle, FEE executes a synchronous cancel. */
        ExecCancel = TRUE;
    }
    else
    {
        ExtDirectResult = Fee_ExtGetDirectJobResult();
        if(( Fee_CpuDtfInfo.u1ProcessStatus != FEE_STATUSIDLE )
        || ( ExtDirectResult == (Fee_ExtDirect_ReturnType)FEE_EXT_DRCT_JOB_BUSY ))
        {
            /* If the under module and FEE are busy, FEE executes a asynchronous cancel. */
            /* FEE status includes a body job status and a direct job result.            */
            Fee_Driver_WaitCancelFlag = TRUE;
        }
        else
        {
            /* If the under module and FEE are mismatch status, FEE sets fatal error and initializes RAM. */
            /* Above mismatch means that the under module is busy and FEE is idle.                        */
            Fee_Driver_SetFatalError();
            ExecCancel = TRUE;
        }
    }

    if( ExecCancel == (boolean)TRUE )
    {
        Fee_Driver_InitRam();
        Fee_Driver_WaitCancelFlag = FALSE;
        Fee_Pif_CancelEndNotification();
        Rtn = E_OK;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Driver_AbortDfc                                      */
/* Description   | Function to abort, forced cancel, the under module.      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Driver_AbortDfc( void )
{
    MemIf_StatusType DfcStatus;

    Fee_Dfc_Cancel();

    DfcStatus = Fee_Dfc_GetStatus();
    if( DfcStatus != MEMIF_IDLE )
    {
        Fee_Driver_SetFatalError();
    }

    /* DFC */
    Fee_Dfc_End();
    /* MNG DFC */
    Fee_ClearCWriteBuf();
    /* DRIVER */
    Fee_Driver_WaitCancelFlag = FALSE;

    return;
}

/****************************************************************************/
/* Function Name | Fee_Driver_AsyncCancel                                   */
/* Description   | Function to execute asynchronous cancel.                 */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Driver_AsyncCancel( void )
{
    Fee_Driver_InitRam();
    Fee_Driver_WaitCancelFlag = FALSE;
    Fee_Pif_CancelEndNotification();

    return;
}

/****************************************************************************/
/* Function Name | Fee_Driver_AsyncAbort                                    */
/* Description   | Function to execute asynchronous abort for               */
/*               | an illegal status.                                       */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Driver_AsyncAbort( void )
{
    Fee_Driver_InitRam();
    Fee_Driver_WaitCancelFlag = FALSE;
    Fee_Pif_AbortEndNotification();

    return;
}

/****************************************************************************/
/* Function Name | Fee_Driver_IsWaitingForCancel                            */
/* Description   | Function to check  that FEE is waiting for cancel.       */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Check result. TRUE or FALSE.                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( boolean, FEE_CODE )
Fee_Driver_IsWaitingForCancel( void )
{
    return Fee_Driver_WaitCancelFlag;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Fee_Driver_InitRam                                       */
/* Description   | Function to initialize RAMs in the FEE module.           */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Driver_InitRam( void )
{
    /* DFC */
    Fee_Dfc_End();
    /* MNG DFC */
    Fee_ClearCWriteBuf();
    /* RECORD POS TBL */
    Fee_RecordPosTbl_ClearPosAll();
    /* RECORD */
    Fee_Record_Init();
    /* BLOCK */
    Fee_ClrUseBlockInfo();
    /* COMMON */
    Fee_InitCpuDtfData( &Fee_CpuDtfInfo );
    Fee_InitLastWritePos( (uint8)FEE_DUMMY_AREA_NO_FOR_LWPOS, FEE_INIT_ALL );

    return;
}
/****************************************************************************/
/* Function Name | Fee_Driver_SetFatalError                                 */
/* Description   | Function to set fatal error on status of FEE and other   */
/*               | module.                                                  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Driver_SetFatalError( void )
{
    Mscd_ErrorInfo_DetectErrorFactor( MSCD_ERRINFO_ERRORFACTOR_FATALERROR );

    return;
}

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/07/04                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
