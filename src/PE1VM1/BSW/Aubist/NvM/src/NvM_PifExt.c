/* NvM_PifExt.c v2-1-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/PIFEXT/CODE                                           */
/*--------------------------------------------------------------------------*/
/* Notes        | None                                                      */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <NvM.h>
#include <NvM_Ext.h>
#include <NvM_Mscd.h>
#include "../inc/NvM_Internal.h"
#include "../inc/NvM_PifExt.h"
#include "../inc/NvM_PifExt_Internal.h"
#include <Mscd_Common.h>
#include <MemIf.h>
#include "../inc/NvM_Evt.h"
#include "../inc/NvM_Nvb.h"
#include "../inc/NvM_Jobm.h"
#include "../inc/NvM_Jobq.h"

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CONST_32
#include <NvM_MemMap.h>

CONST( uint8, NVM_CONST ) NvM_ExtIntentRbldRamBlock[NVM_EXT_INTENT_RBLD_RAM_BLOCK_LENGTH] = { 0U, 0U };

#define NVM_STOP_SEC_CONST_32
#include <NvM_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* Function Name | NvM_ExtAbortJobs                                         */
/* Description   | Service to abort all requests.                           */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_ExtAbortJobs( void )
{
    NvM_Jobm_AbortJobs();
    return;
}

/****************************************************************************/
/* Function Name | NvM_MainFunction_ExtNonPeriodic                          */
/* Description   | Service for non-periodic performing the processing of    */
/*               | the NvM jobs.                                            */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_MainFunction_ExtNonPeriodic( void )
{
    uint8          MsOpeState;
    boolean        IsFatalError;

    IsFatalError = NvM_Evt_IsFatalFailed();
    if( IsFatalError == (boolean)FALSE )
    {
        Mscd_Frm_NvMExclusiveLockBegin();
        MsOpeState = Mscd_Suspend_UpdateOpeState();
        if( MSCD_SUSPEND_MS_RUN == MsOpeState )
        {
            NvM_Jobm_MainFunction( NVM_NVB_CALLMODE_NONPERIODIC );
            Mscd_Msif_SpeedUpMFProcessResultNotification( MSCD_MAINFUNCTION_PROCESSED );
        }
        else
        {
            Mscd_Msif_SpeedUpMFProcessResultNotification( MSCD_MAINFUNCTION_NOT_PROCESSED );
        }
        Mscd_Frm_NvMExclusiveLockEnd();
    }

    return;
}

/****************************************************************************/
/* Function Name | NvM_ExtGetStatus                                         */
/* Description   | Service to return the status.                            */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | StatusType                                               */
/*               |  NVM_EXT_IDLE     :NvM is not busy                       */
/*               |  NVM_EXT_BUSY     :NvM is busy                           */
/*               |  NVM_EXT_ERROR    :Error happened in NvM.                */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( NvM_ExtStatusType, NVM_CODE )
NvM_ExtGetStatus( void )
{
    NvM_ExtStatusType               Rtn              = NVM_EXT_IDLE;
    Std_ReturnType                  QueueGetResult   = E_OK;
    boolean                         IsNotSglQueueEmpty;
    boolean                         IsFatalError;
    NvM_Jobm_stJobInfomationType    RequestJobInfo;

    IsNotSglQueueEmpty = NvM_Jobq_SglQueueIsNotEmpty();
    if( (boolean)FALSE == IsNotSglQueueEmpty )
    {
        QueueGetResult = NvM_Jobq_MultiGetJobInfo( &RequestJobInfo );
    }

    IsFatalError = NvM_Evt_IsFatalFailed();

    if( (boolean)FALSE == IsFatalError )
    {
        if( (Std_ReturnType)E_OK == QueueGetResult )
        {
            Rtn = NVM_EXT_BUSY;
        }
    }
    else
    {
        Rtn = NVM_EXT_ERROR;
    }
    return ( Rtn );
}

/****************************************************************************/
/* Function Name | NvM_ExtEnable                                            */
/* Description   | Service to enable NvM.                                   */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_ExtEnable( void )
{
    NvM_Jobm_DestructiveCancelJobs( NVM_JOBM_DSTRCTV_CXL_PREEMPTION );
    return;
}

/****************************************************************************/
/* Function Name | NvM_ExtDisable                                           */
/* Description   | Service to disable NvM.                                  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_ExtDisable( void )
{
    MemIf_Cancel( MEMIF_BROADCAST_ID );
    return;
}

/****************************************************************************/
/* Function Name | NvM_ExtGetNvBlockLength                                  */
/* Description   | Service to get NV block length.                          */
/* Preconditions | None                                                     */
/* Parameters    | BlockId      : The block identifier uniquely identifies  */
/*               |                one NVRAM block descriptor.               */
/*               |                A NVRAM block descriptor contains all     */
/*               |                needed information about a single NVRAM   */
/*               |                block.                                    */
/*               | LengthPtr    : Pointer to where to store the length.     */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : NV block length was got successfully.        */
/*               |  E_NOT_OK : An error occurred.                           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_ExtGetNvBlockLength(
    NvM_BlockIdType BlockId,
    P2VAR( uint16, AUTOMATIC, TYPEDEF ) LengthPtr
){
    Std_ReturnType Rtn = E_NOT_OK;
    NvM_BlockIdType UserBlkIdMax = NVM_USER_BLOCKID_MAX;
    
    if( ( BlockId >= (NvM_BlockIdType)NVM_USER_BLOCKID_MIN )
     && ( BlockId <= UserBlkIdMax ) )
    {
        if( LengthPtr != (uint16*)NULL_PTR )
        {
            *LengthPtr = NvMBlockDescriptors[BlockId].NvMNvBlockLength;
            Rtn = E_OK;
        }
    }
    
    return Rtn;
}

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2018/10/24                                              */
/*  1-2-0          :2019/08/27                                              */
/*  2-0-0          :2021/02/26                                              */
/*  2-1-0          :2022/07/20                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
