/* Dem_AsyncReq_c(v5-5-0)                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/AsyncReq/CODE                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_AsyncReq.h"
#include "../../../inc/Dem_CmnLib_AsyncReqTable.h"
#include "../../../inc/Dem_CmnLib_Control.h"
#include "../../../inc/Dem_CmnLib_DataAvl.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_MonSts.h"
#include "../../../inc/Dem_Md_ModeMng.h"
#include "Dem_AsyncReq_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions(PreInit section)                                      */
/****************************************************************************/
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_AsyncReq_PreInit                                     */
/* Description   | Pre-Initialize of Dem_AsyncReq-internal state and infor- */
/*               | mation.                                                  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE_TRUST ) Dem_AsyncReq_PreInit         /*  PreInit section     */
( void )
{
    Dem_EventQueue_PreInit();

    return ;
}
#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_AsyncReq_Shutdown                                    */
/* Description   | Shutdown of Dem_AsyncReq.                                */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_AsyncReq_Shutdown
( void )
{
    /* Exclusion start for Dem_EventQueueBufferAccess */
    SchM_Enter_Dem_EventQueueBufferAccess();

    Dem_EventQueue_Shutdown();
    Dem_ModeMng_ClearMode( DEM_MODE_WAIT_SETTING_EVENT );

    /* Exclusion end for Dem_EventQueueBufferAccess */
    SchM_Exit_Dem_EventQueueBufferAccess();

    return ;
}


#if ( DEM_ASYNCDATAQUE_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_AsyncReq_RefreshRAM                                  */
/* Description   | Refresh RAM  - AsyncReq                                  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_AsyncReq_RefreshRAM
( void )
{
    /* Exclusion start for Dem_EventQueueBufferAccess */
    SchM_Enter_Dem_EventQueueBufferAccess();

    Dem_AsyncReqData_RefreshRAM();

    /* Exclusion end for Dem_EventQueueBufferAccess */
    SchM_Exit_Dem_EventQueueBufferAccess();

    return ;
}
#endif /* DEM_ASYNCDATAQUE_USE -STD_ON- */


/****************************************************************************/
/* Function Name | Dem_AsyncReq_Enqueue                                     */
/* Description   | Queues the reported events.                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] Kind :                                              */
/*               |        Data kind.                                        */
/*               | [in] Index :                                             */
/*               |        Identification of an event by assigned EventInde- */
/*               |        x.                                                */
/*               | [in] Status :                                            */
/*               |        Monitor test result.                              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : queueing of event was successful.    */
/*               |        DEM_IRT_NG : queueing of event failed.            */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AsyncReq_Enqueue
(
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) Kind,
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfEnqueue;
    VAR( boolean, AUTOMATIC ) isQueueEmpty;

    /* Exclusion start for Dem_EventQueueBufferAccess */
    SchM_Enter_Dem_EventQueueBufferAccess();

    isQueueEmpty = Dem_EventQueue_IsQueueEmpty();
    resultOfEnqueue = Dem_EventQueue_Enqueue( Kind, Index, Status );

    if( isQueueEmpty == (boolean)TRUE )
    {
        if( resultOfEnqueue == DEM_IRT_OK )
        {
            /* Set Dem-mode */
            Dem_ModeMng_SetMode( DEM_MODE_WAIT_SETTING_EVENT );
        }
    }

    /* Exclusion end for Dem_EventQueueBufferAccess */
    SchM_Exit_Dem_EventQueueBufferAccess();

    return resultOfEnqueue;
}


#if ( DEM_ASYNCDATAQUE_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_AsyncReq_EnqueueWithData                             */
/* Description   | Queues the reported events.                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] Kind :                                              */
/*               |        Data kind.                                        */
/*               | [in] Index :                                             */
/*               |        Identification of an event by assigned EventInde- */
/*               |        x.                                                */
/*               | [in] DataBuffPtr :                                       */
/*               |        The pointer of the data buffer.                   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : queueing of event was successful.    */
/*               |        DEM_IRT_NG : queueing of event failed.            */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AsyncReq_EnqueueWithData
(
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) Kind,              /* [PRMCHK:CALLER] */
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfEnqueue;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfRegistQue;
    VAR( Dem_u08_AsyncDataQueIndexType, AUTOMATIC ) queIndex;
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) asyncReqIndex;
    VAR( Dem_u08_AsyncDataQueTableIndexType, AUTOMATIC ) asyncDataQueNum;
    VAR( Dem_u08_AsyncDataQueTableIndexType, AUTOMATIC ) asyncDataQueIndex;
    VAR( boolean, AUTOMATIC ) isQueueEmpty;

    asyncDataQueNum = Dem_AsyncDataQueNum;
    resultOfEnqueue = DEM_IRT_NG;

    asyncReqIndex = (Dem_u08_AsyncReqTableIndexType)Kind;
    asyncDataQueIndex = Dem_ExecAsyncReqTable[ asyncReqIndex ].AsyncDataQueIndex;           /* [GUDCHK:CALLER]asyncReqIndex */

    if( asyncDataQueIndex < asyncDataQueNum )                                               /* [GUD:if]asyncDataQueIndex */
    {
        /* Exclusion start for Dem_EventQueueBufferAccess */
        SchM_Enter_Dem_EventQueueBufferAccess();

        resultOfRegistQue = Dem_AsyncReqData_RegistQue( asyncDataQueIndex, &queIndex );     /* [GUD]asyncDataQueIndex */
        if( resultOfRegistQue == DEM_IRT_OK )
        {
            isQueueEmpty = Dem_EventQueue_IsQueueEmpty();
            resultOfEnqueue = Dem_EventQueue_Enqueue( Kind, Index, queIndex );

            if( resultOfEnqueue != DEM_IRT_OK )
            {
                Dem_AsyncReqData_ReleaseQueIndex( asyncDataQueIndex, queIndex );            /* [GUD]asyncDataQueIndex */
            }
            else
            {
                if( isQueueEmpty == (boolean)TRUE )
                {
                    /* Set Dem-mode */
                    Dem_ModeMng_SetMode( DEM_MODE_WAIT_SETTING_EVENT );
                }
            }
        }

        /* Exclusion end for Dem_EventQueueBufferAccess */
        SchM_Exit_Dem_EventQueueBufferAccess();

        if( resultOfEnqueue == DEM_IRT_OK )
        {
            Dem_AsyncReqData_SetQueData( asyncDataQueIndex, queIndex, DataBuffPtr );        /* [GUD]asyncDataQueIndex */
        }
    }

    return resultOfEnqueue;
}


/****************************************************************************/
/* Function Name | Dem_AsyncReq_Dequeue                                     */
/* Description   | Takes out the queued event.                              */
/* Preconditions | Exists event in event queue by Dem_AsyncReq_Enqueue.     */
/* Parameters    | [out] KindPtr :                                          */
/*               |        Data kind.                                        */
/*               | [out] IndexPtr :                                         */
/*               |        Identification of an event by assigned EventId.   */
/*               | [out] StatusPtr :                                        */
/*               |        Monitor test result.                              */
/*               | [out] DataBuffPtr :                                      */
/*               |        The pointer of the data buffer.                   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : taking out of the event was succeed- */
/*               |        ed.                                               */
/*               |        DEM_IRT_NG : taking out of the event failed, or - */
/*               |        there are no queueing event.                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AsyncReq_Dequeue
(
    P2VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC, AUTOMATIC )  KindPtr,
    P2VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC, AUTOMATIC )  IndexPtr,
    P2VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC, AUTOMATIC ) StatusPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfDequeue;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfReleaseQue;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_AsyncDataQueIndexType, AUTOMATIC ) queIndex;
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) asyncReqNum;
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) asyncReqIndex;
    VAR( Dem_u08_AsyncDataQueTableIndexType, AUTOMATIC ) asyncDataQueNum;
    VAR( Dem_u08_AsyncDataQueTableIndexType, AUTOMATIC ) asyncDataQueIndex;
    VAR( boolean, AUTOMATIC ) isQueueEmpty;

    asyncReqNum = Dem_AsyncReqNum;
    asyncDataQueNum = Dem_AsyncDataQueNum;

    retVal = DEM_IRT_NG;

    /* Exclusion start for Dem_EventQueueBufferAccess */
    SchM_Enter_Dem_EventQueueBufferAccess();

    resultOfDequeue = Dem_EventQueue_Dequeue( KindPtr, IndexPtr, StatusPtr );

    if( resultOfDequeue == DEM_IRT_OK )
    {
        asyncReqIndex = (Dem_u08_AsyncReqTableIndexType)*KindPtr;

        if( asyncReqIndex < asyncReqNum )                                                           /* [GUD:if]asyncReqIndex */
        {
            asyncDataQueIndex = Dem_ExecAsyncReqTable[ asyncReqIndex ].AsyncDataQueIndex;               /* [GUD]asyncReqIndex */

            if( asyncDataQueIndex < asyncDataQueNum )                                               /* [GUD:if]asyncDataQueIndex */
            {
                queIndex = (Dem_u08_AsyncDataQueIndexType)*StatusPtr;

                resultOfReleaseQue = Dem_AsyncReqData_ReleaseQue( asyncDataQueIndex, queIndex, DataBuffPtr );       /* [GUD]asyncDataQueIndex */
                if( resultOfReleaseQue == DEM_IRT_OK )
                {
                    /* Set dequeue result to OK */
                    retVal = DEM_IRT_OK;
                }
                else
                {
                    /* When acquisition of the additional data from the data queue failed */
                    /* No process */
                }
            }
            else
            {
                /* When the function has no additional data */
                /* Set dequeue result to OK */
                retVal = DEM_IRT_OK;
            }
        }
        else
        {
            /* When the dequeued Kind value is invalid */
            /* No process */
        }
    }
    else
    {
        /* When the dequeue prosess failed */
        /* No process */
    }

    isQueueEmpty = Dem_EventQueue_IsQueueEmpty();
    if( isQueueEmpty == (boolean)TRUE )
    {
        /*  notify mode : all queue cleared.            */
        Dem_ModeMng_ClearMode( DEM_MODE_WAIT_SETTING_EVENT );
    }

    /* Exclusion end for Dem_EventQueueBufferAccess */
    SchM_Exit_Dem_EventQueueBufferAccess();

    return retVal;
}
#endif /* DEM_ASYNCDATAQUE_USE -STD_ON- */

#if ( DEM_ASYNCDATAQUE_USE == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_AsyncReq_Dequeue                                     */
/* Description   | Takes out the queued event.                              */
/* Preconditions | Exists event in event queue by Dem_AsyncReq_Enqueue.     */
/* Parameters    | [out] KindPtr :                                          */
/*               |        Data kind.                                        */
/*               | [out] IndexPtr :                                         */
/*               |        Identification of an event by assigned EventId.   */
/*               | [out] StatusPtr :                                        */
/*               |        Monitor test result.                              */
/*               | [out] DataBuffPtr :                                      */
/*               |        The pointer of the data buffer.                   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : taking out of the event was succeed- */
/*               |        ed.                                               */
/*               |        DEM_IRT_NG : taking out of the event failed, or - */
/*               |        there are no queueing event.                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AsyncReq_Dequeue
(
    P2VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC, AUTOMATIC )  KindPtr,
    P2VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC, AUTOMATIC )  IndexPtr,
    P2VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC, AUTOMATIC ) StatusPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr    /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfDequeue;
    VAR( boolean, AUTOMATIC ) isQueueEmpty;

    /* Exclusion start for Dem_EventQueueBufferAccess */
    SchM_Enter_Dem_EventQueueBufferAccess();

    resultOfDequeue = Dem_EventQueue_Dequeue( KindPtr, IndexPtr, StatusPtr );
    isQueueEmpty = Dem_EventQueue_IsQueueEmpty();

    if( isQueueEmpty == (boolean)TRUE )
    {
        Dem_ModeMng_ClearMode( DEM_MODE_WAIT_SETTING_EVENT );
    }

    /* Exclusion end for Dem_EventQueueBufferAccess */
    SchM_Exit_Dem_EventQueueBufferAccess();

    return resultOfDequeue;
}
#endif /* DEM_ASYNCDATAQUE_USE -STD_OFF- */


/****************************************************************************/
/* Function Name | Dem_AsyncReq_SetClearStatus                              */
/* Description   | Sets the status of clear processing.                     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_AsyncReq_SetClearStatus
( void )
{
    /* Exclusion start for Dem_EventQueueBufferAccess */
    SchM_Enter_Dem_EventQueueBufferAccess();

    Dem_EventQueue_SetClearStatus();

    /* Exclusion end for Dem_EventQueueBufferAccess */
    SchM_Exit_Dem_EventQueueBufferAccess();

    return ;
}


/****************************************************************************/
/* Function Name | Dem_AsyncReq_SetClearEvent                               */
/* Description   | Sets clear queued event.                                 */
/* Preconditions | Exists event in event queue by Dem_AsyncReq_Enqueue.     */
/* Parameters    | [in] DTCGroup :                                          */
/*               |        DTCValue specified at the time of Clear.          */
/*               | [in] DTCOrigin :                                         */
/*               |        DTCOrigin specified at the time of Clear.         */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_AsyncReq_SetClearEvent
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    Dem_EventQueue_SetClearEvent( DTCGroup, DTCOrigin );

    return ;
}


/****************************************************************************/
/* Function Name | Dem_AsyncReq_JudgeReqCondition                           */
/* Description   | Judge request condition.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] Kind :                                              */
/*               |        Data kind.                                        */
/*               | [in] Index :                                             */
/*               |        Identification of an event by assigned EventInde- */
/*               |        x.                                                */
/*               | [in] Status :                                            */
/*               |        Monitor test result.                              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : request condition is OK.             */
/*               |        DEM_IRT_NG : request condition is NG.             */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AsyncReq_JudgeReqCondition
(
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) Kind,
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status    /* MISRA DEVIATION */
)
{
    VAR( boolean, AUTOMATIC ) availableStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u08_DTCSettingStatusType, AUTOMATIC ) settingStatus;
    VAR( Dem_u08_InitStatusType, AUTOMATIC ) execInitStatus;
    VAR( Dem_u08_AsyncReqFuncAttrType, AUTOMATIC ) funcAttribute;
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) asyncReqNum;
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) asyncReqIndex;

    asyncReqNum = Dem_AsyncReqNum;

    /* Set return value to OK */
    retVal = DEM_IRT_OK;

    asyncReqIndex = (Dem_u08_AsyncReqTableIndexType)Kind;
    if( asyncReqIndex < asyncReqNum )                                                                       /* [GUD:if]asyncReqIndex */
    {
        execInitStatus  = Dem_ExecAsyncReqTable[ asyncReqIndex ].ExecInitStatus;                            /* [GUD]asyncReqIndex */
        funcAttribute   = Dem_ExecAsyncReqTable[ asyncReqIndex ].FuncAttribute;                             /* [GUD]asyncReqIndex */

        checkStatus = Dem_Control_ChkInitStatus( execInitStatus );
        if( checkStatus == DEM_IRT_OK )
        {
            if( ( funcAttribute & DEM_FNCATTR_CHK_EVTAVAILABLE ) == DEM_FNCATTR_CHK_EVTAVAILABLE )
            {
                availableStatus = Dem_DataAvl_GetEvtAvlCommon( (Dem_u16_EventCtrlIndexType)Index );
                if( availableStatus != (boolean)TRUE )
                {
                    /* When the event is unavailable */
                    /* Set return value to NG */
                    retVal = DEM_IRT_NG;
                }
            }

            if( retVal == DEM_IRT_OK )
            {
                settingStatus = Dem_Control_GetDTCSettingStatus();

#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )   /*  [FuncSw]    */
                if( ( funcAttribute & DEM_FNCATTR_EXE_UPDMONSTS ) == DEM_FNCATTR_EXE_UPDMONSTS )
                {
                    Dem_MonSts_SetSyncMonitorStatus( Kind, Index, Status, settingStatus );
                }
#endif  /* ( DEM_TRIGGER_FIM_REPORTS == STD_ON )            */

                if( ( funcAttribute & DEM_FNCATTR_CHK_DTCSETTING ) == DEM_FNCATTR_CHK_DTCSETTING )
                {
                    if( settingStatus != DEM_CTL_STS_DTC_SETTING_ENABLE )
                    {
                        /* When the DTC setting status is not Enable */
                        /* Set return value to NG */
                        retVal = DEM_IRT_NG;
                    }
                }
            }
        }
        else
        {
            /* For processing execution in an incorrect initialization state */
            /* Set return value to NG */
            retVal = DEM_IRT_NG;
        }
    }
    else
    {
        /* When the Kind value is invalid */
        /* Set return value to NG */
        retVal = DEM_IRT_NG;
    }

    return retVal;
}

#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )
/****************************************************************************/
/* Function Name | Dem_AsyncReq_GetReadIndex                                */
/* Description   | Get ReadIndex                                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u16_EventQueueIndexType                              */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u16_EventQueueIndexType, DEM_CODE ) Dem_AsyncReq_GetReadIndex
( void )
{
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) retVal;

    retVal = Dem_EventQueue_GetReadIndex();

    return retVal;
}

#if ( DEM_ASYNCDATAQUE_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_AsyncReq_CheckQueueNext                              */
/* Description   | Check QueueNext                                          */
/* Preconditions | none                                                     */
/* Parameters    | [out]     ReadIndexPtr                                   */
/*               | [out]     ReadCountPtr                                   */
/*               | [out]     KindPtr                                        */
/*               | [in/out]  IndexPtr                                       */
/*               | [in/out]  StatusPtr                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AsyncReq_CheckQueueNext
(
    P2VAR( Dem_u16_EventQueueIndexType, AUTOMATIC, AUTOMATIC ) ReadIndexPtr,
    P2VAR( Dem_u16_EventQueueIndexType, AUTOMATIC, AUTOMATIC ) ReadCountPtr,
    P2VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC, AUTOMATIC ) KindPtr,
    P2VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC, AUTOMATIC ) IndexPtr,
    P2VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC, AUTOMATIC ) StatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_AsyncDataQueIndexType, AUTOMATIC ) queIndex;
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) eventStatus;
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) asyncReqNum;
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) asyncReqIndex;
    VAR( Dem_u08_AsyncDataQueTableIndexType, AUTOMATIC ) asyncDataQueNum;
    VAR( Dem_u08_AsyncDataQueTableIndexType, AUTOMATIC ) asyncDataQueIndex;

    asyncReqNum = Dem_AsyncReqNum;
    asyncDataQueNum = Dem_AsyncDataQueNum;

    retVal = Dem_EventQueue_CheckQueueNext( ReadIndexPtr, ReadCountPtr, KindPtr, IndexPtr, StatusPtr );
    if( retVal == DEM_IRT_OK )
    {
        asyncReqIndex = (Dem_u08_AsyncReqTableIndexType)*KindPtr;
        if( asyncReqIndex < asyncReqNum )                                                                           /* [GUD:if]asyncReqIndex */
        {
            asyncDataQueIndex = Dem_ExecAsyncReqTable[ asyncReqIndex ].AsyncDataQueIndex;       /* [GUD]asyncReqIndex */
            if( asyncDataQueIndex < asyncDataQueNum )                                           /* [GUD:if]asyncDataQueIndex */
            {
                /* Use the status as index for the data queue. */
                queIndex = (Dem_u08_AsyncDataQueIndexType)*StatusPtr;

                /* Get event status from the data queue. */
                Dem_AsyncReqData_GetEventStatus( asyncDataQueIndex, queIndex, &eventStatus );   /* [GUD]asyncDataQueIndex */

                /* Set the event status obtained from the data queue. */
                *StatusPtr = eventStatus;
            }
        }
    }

    return retVal;
}
#endif /* DEM_ASYNCDATAQUE_USE -STD_ON- */

#if ( DEM_ASYNCDATAQUE_USE == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_AsyncReq_CheckQueueNext                              */
/* Description   | Check QueueNext                                          */
/* Preconditions | none                                                     */
/* Parameters    | [out]     ReadIndexPtr                                   */
/*               | [out]     ReadCountPtr                                   */
/*               | [out]     KindPtr                                        */
/*               | [in/out]  IndexPtr                                       */
/*               | [in/out]  StatusPtr                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AsyncReq_CheckQueueNext
(
    P2VAR( Dem_u16_EventQueueIndexType, AUTOMATIC, AUTOMATIC ) ReadIndexPtr,
    P2VAR( Dem_u16_EventQueueIndexType, AUTOMATIC, AUTOMATIC ) ReadCountPtr,
    P2VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC, AUTOMATIC ) KindPtr,
    P2VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC, AUTOMATIC ) IndexPtr,
    P2VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC, AUTOMATIC ) StatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = Dem_EventQueue_CheckQueueNext( ReadIndexPtr, ReadCountPtr, KindPtr, IndexPtr, StatusPtr );

    return retVal;
}
#endif /* DEM_ASYNCDATAQUE_USE -STD_OFF- */
#endif /* DEM_TRIGGER_FIM_REPORTS -STD_ON- */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

