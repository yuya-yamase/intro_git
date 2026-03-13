/* Dem_EventQueue_c(v5-10-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/EventQueue/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_UserDefMem_Cfg.h"
#include "../../../inc/Dem_CmnLib_AsyncReq.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "Dem_AsyncReq_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_EVENT_QUEUE_INITIAL_DATA_INDEX      ((Dem_u16_AsyncReqItemAType)0xFFFFU)
#define DEM_EVENT_QUEUE_INITIAL_DATA_STATUS     ((Dem_u08_AsyncReqItemBType)0xFFU)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Struct of event queue */
typedef struct{
    Dem_u16_AsyncReqItemAType        Index;
    Dem_u08_AsyncReqTableIndexType   Kind;
    Dem_u08_AsyncReqItemBType        Status;
} Dem_EventQueue_QueueData_St_Type;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( void, DEM_CODE ) Dem_EventQueue_InitQueueMngInfo
( void );
static FUNC( void, DEM_CODE ) Dem_EventQueue_GetQueueData
(
    P2VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC, AUTOMATIC ) KindPtr,
    P2VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC, AUTOMATIC ) IndexPtr,
    P2VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC, AUTOMATIC ) StatusPtr
);
static FUNC( void, DEM_CODE ) Dem_EventQueue_ProgressReadIndex
( void );
static FUNC( void, DEM_CODE ) Dem_EventQueue_SetClearFlag
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) StartIndex,
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) EndNumberOfForStatement
);
static FUNC( void, DEM_CODE ) Dem_EventQueue_SetClearFlag_PrimaryMemory
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) StartIndex,
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) EndNumberOfForStatement
);

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_EventQueue_SetClearFlag_UserDefMem
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) StartIndex,
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) EndNumberOfForStatement
);
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */

#if ( DEM_ASYNCDATAQUE_USE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_EventQueue_ReleaseDataQueAtSetClearFlag
(
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) Kind,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status
);
#endif  /* ( DEM_ASYNCDATAQUE_USE == STD_ON )   */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_EventQueue_QueueData_St_Type, DEM_VAR_NO_INIT ) Dem_EventQueueBuffer[DEM_EVENT_QUEUE_SIZE];
static VAR( Dem_u16_EventQueueIndexType, DEM_VAR_NO_INIT ) Dem_EventQueueWriteIndex;
static VAR( Dem_u16_EventQueueIndexType, DEM_VAR_NO_INIT ) Dem_EventQueueReadIndex;
static VAR( Dem_u16_EventQueueIndexType, DEM_VAR_NO_INIT ) Dem_EventQueueDataNumber;
static VAR( Dem_u16_EventQueueIndexType, DEM_VAR_NO_INIT ) Dem_EventQueueClearDataNumber;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions(PreInit section)                                      */
/****************************************************************************/
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_EventQueue_PreInit                                   */
/* Description   | Pre-Initialize of Dem_EventQueue-internal state and inf- */
/*               | ormation.                                                */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE_TRUST ) Dem_EventQueue_PreInit       /*  PreInit section     */
( void )
{
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) cnt;    /* loop counter */
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) eventQueueSize;

    eventQueueSize = Dem_EventQueueSize;

    /* Inits event queue data */
    for( cnt = (Dem_u16_EventQueueIndexType)0U; cnt < eventQueueSize; cnt++ )       /* [GUD:for]cnt */
    {
        Dem_EventQueueBuffer[cnt].Kind   = DEM_ASYNCREQ_EMPTY;                      /* [GUD]cnt */
        Dem_EventQueueBuffer[cnt].Index  = DEM_EVENT_QUEUE_INITIAL_DATA_INDEX;      /* [GUD]cnt */
        Dem_EventQueueBuffer[cnt].Status = DEM_EVENT_QUEUE_INITIAL_DATA_STATUS;     /* [GUD]cnt */
    }

    Dem_EventQueueWriteIndex       = DEM_EVENT_QUEUE_MIN_INDEX;
    Dem_EventQueueReadIndex        = DEM_EVENT_QUEUE_MIN_INDEX;
    Dem_EventQueueDataNumber       = DEM_EVENT_QUEUE_NUMBER_EMPTY;
    Dem_EventQueueClearDataNumber  = DEM_EVENT_QUEUE_CLEAR_NUMBER_NONE;

#if ( DEM_ASYNCDATAQUE_USE == STD_ON )  /* [FuncSw] */
    /* Init data queue */
    Dem_AsyncReqData_ClearQueData();
#endif  /* ( DEM_ASYNCDATAQUE_USE == STD_ON )   */

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
/* Function Name | Dem_EventQueue_Shutdown                                  */
/* Description   | Shutdown of Dem_EventQueue.                              */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | Called within the exclusive Dem_EventQueueBufferAccess.  */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_EventQueue_Shutdown
( void )
{
    /* Clear EventQueue management information except EventQueueBuffer */
    Dem_EventQueue_InitQueueMngInfo();

    return ;
}


/****************************************************************************/
/* Function Name | Dem_EventQueue_SetClearStatus                            */
/* Description   | Sets the status of clear processing.                     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | Called within the exclusive Dem_EventQueueBufferAccess.  */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_EventQueue_SetClearStatus
( void )
{
    /* Checks data number in event queue */
    if( Dem_EventQueueDataNumber > DEM_EVENT_QUEUE_NUMBER_EMPTY )
    {
        Dem_EventQueueClearDataNumber  = Dem_EventQueueDataNumber;
    }
    else
    {
        Dem_EventQueueClearDataNumber  = DEM_EVENT_QUEUE_CLEAR_NUMBER_NONE;
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_EventQueue_SetClearEvent                             */
/* Description   | Sets clear queued event.                                 */
/* Preconditions | Exists event in event queue by Dem_EventQueue_Enqueue.   */
/* Parameters    | [in] DTCGroup :                                          */
/*               |        DTCValue specified at the time of Clear.          */
/*               | [in] DTCOrigin :                                         */
/*               |        DTCOrigin specified at the time of Clear.         */
/* Return Value  | void                                                     */
/* Notes         | [!ATTENSSION!] This function is NOT called within        */
/*               | the exclusive Dem_EventQueueBufferAccess.                */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-10-0     | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_EventQueue_SetClearEvent
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) dataNumberFromReadIndexToBufferEnd;
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) dataNumberFromBufferStartToClearDestination;
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) dataNumberFromReadIndexToClearDestination;
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) eventQueueSize;
    VAR( Dem_u16_EventQueueIndexType, DEM_VAR_NO_INIT ) eventQueueReadIndex;
    VAR( Dem_u16_EventQueueIndexType, DEM_VAR_NO_INIT ) eventQueueClearDataNumber;

    SchM_Enter_Dem_EventQueueBufferAccess();

    eventQueueReadIndex         =   Dem_EventQueueReadIndex;
    eventQueueClearDataNumber   =   Dem_EventQueueClearDataNumber;

    SchM_Exit_Dem_EventQueueBufferAccess();

    eventQueueSize = Dem_EventQueueSize;

    /* Checks clear data number for lower limit */
    if( eventQueueClearDataNumber > DEM_EVENT_QUEUE_CLEAR_NUMBER_NONE )
    {
        /* Checks clear data number for upper limit */
        if( eventQueueClearDataNumber <= eventQueueSize )
        {
            /* Calcs clear destination index */
            dataNumberFromReadIndexToBufferEnd = eventQueueSize - eventQueueReadIndex;

            /* Decisions index */
            if( eventQueueClearDataNumber <= dataNumberFromReadIndexToBufferEnd )
            {
                /* Calcs data number from read index to clear destination */
                dataNumberFromReadIndexToClearDestination = eventQueueReadIndex + eventQueueClearDataNumber;

                /* Sets clear flag from read index to clear destination */
                Dem_EventQueue_SetClearFlag( DTCGroup , DTCOrigin, eventQueueReadIndex , dataNumberFromReadIndexToClearDestination );
            }
            else
            {
                /* Sets clear flag from read index to buffer end */
                Dem_EventQueue_SetClearFlag( DTCGroup , DTCOrigin, eventQueueReadIndex , eventQueueSize );

                /* Calcs data number from buffer start index to clear destination */
                dataNumberFromBufferStartToClearDestination = eventQueueClearDataNumber - dataNumberFromReadIndexToBufferEnd;

                /* Sets clear flag from buffer start index to clear destination */
                Dem_EventQueue_SetClearFlag( DTCGroup , DTCOrigin, DEM_EVENT_QUEUE_MIN_INDEX , dataNumberFromBufferStartToClearDestination );
            }
        }
        else
        {
            /* No process */
        }
    }
    else
    {
        /* No process */
    }

    return;
}

#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )
/****************************************************************************/
/* Function Name | Dem_EventQueue_GetReadIndex                              */
/* Description   | Get ReadIndex                                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u16_EventQueueIndexType                              */
/* Notes         | [!ATTENSSION!] This function is NOT called within        */
/*               | the exclusive Dem_EventQueueBufferAccess.                */
/****************************************************************************/
FUNC( Dem_u16_EventQueueIndexType, DEM_CODE ) Dem_EventQueue_GetReadIndex
(void)
{
    return Dem_EventQueueReadIndex;
}

/****************************************************************************/
/* Function Name | Dem_EventQueue_CheckQueueNext                            */
/* Description   | Check QueueNext                                          */
/* Preconditions | none                                                     */
/* Parameters    | [out]     ReadIndexPtr                                   */
/*               | [out]     ReadCountPtr                                   */
/*               | [out]     KindPtr                                        */
/*               | [in/out]  IndexPtr                                       */
/*               | [in/out]  StatusPtr                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |       DEM_IRT_OK                                         */
/*               |       DEM_IRT_NG                                         */
/* Notes         | Carry out exclusive control in an origin of use          */
/* Notes         | Called within the exclusive Dem_EventQueueBufferAccess.  */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EventQueue_CheckQueueNext
(
    P2VAR( Dem_u16_EventQueueIndexType, AUTOMATIC, AUTOMATIC ) ReadIndexPtr,
    P2VAR( Dem_u16_EventQueueIndexType, AUTOMATIC, AUTOMATIC ) ReadCountPtr,
    P2VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC, AUTOMATIC ) KindPtr,
    P2VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC, AUTOMATIC ) IndexPtr,
    P2VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC, AUTOMATIC ) StatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) eventQueueSize;
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) readIndex;
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) readCount;

    retVal = DEM_IRT_NG;
    readIndex = *ReadIndexPtr;
    readCount = *ReadCountPtr;

    if( readCount < Dem_EventQueueDataNumber )
    {
        eventQueueSize = Dem_EventQueueSize;
        if( readIndex < eventQueueSize )                                /* [GUD:if]readIndex */
        {
            (*IndexPtr)  = Dem_EventQueueBuffer[readIndex].Index;       /* [GUD]readIndex */
            (*StatusPtr) = Dem_EventQueueBuffer[readIndex].Status;      /* [GUD]readIndex */
            (*KindPtr)   = Dem_EventQueueBuffer[readIndex].Kind;        /* [GUD]readIndex */

            readIndex++;
            if( readIndex >= eventQueueSize )
            {
                readIndex = DEM_EVENT_QUEUE_MIN_INDEX;
            }

            readCount++;
            retVal = DEM_IRT_OK;
        }
    }

    (*ReadIndexPtr) = readIndex;
    (*ReadCountPtr) = readCount;

    return retVal;
}
#endif /* ( DEM_TRIGGER_FIM_REPORTS == STD_ON ) */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dem_EventQueue_InitQueueMngInfo                          */
/* Description   | Initialize Event Queue Management Information data in    */
/*               | EventQueue unit.                                         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | Called within the exclusive Dem_EventQueueBufferAccess.  */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_EventQueue_InitQueueMngInfo
( void )
{
    /* Inits event queue management information data */
    Dem_EventQueueWriteIndex       = DEM_EVENT_QUEUE_MIN_INDEX;
    Dem_EventQueueReadIndex        = DEM_EVENT_QUEUE_MIN_INDEX;
    Dem_EventQueueDataNumber       = DEM_EVENT_QUEUE_NUMBER_EMPTY;
    Dem_EventQueueClearDataNumber  = DEM_EVENT_QUEUE_CLEAR_NUMBER_NONE;

#if ( DEM_ASYNCDATAQUE_USE == STD_ON )  /* [FuncSw] */
    /* Init data queue */
    Dem_AsyncReqData_ClearQueData();
#endif  /* ( DEM_ASYNCDATAQUE_USE == STD_ON )   */

    return ;
}

/****************************************************************************/
/* Function Name | Dem_EventQueue_Enqueue                                   */
/* Description   | Sets event data to event queue.                          */
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
/* Notes         | Called within the exclusive Dem_EventQueueBufferAccess.  */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EventQueue_Enqueue
(
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) Kind,
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) eventQueueSize;
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) eventQueueMaxIndex;

    retVal = DEM_IRT_NG;
    eventQueueSize = Dem_EventQueueSize;
    eventQueueMaxIndex = DEM_EVENT_QUEUE_MAX_INDEX;

    /* check range of Dem_EventQueueWriteIndex.         */
    if ( Dem_EventQueueWriteIndex > eventQueueMaxIndex )                    /* [GUD:if]Dem_EventQueueWriteIndex */
    {
        /* Clear EventQueue management information except EventQueueBuffer */
        Dem_EventQueue_InitQueueMngInfo();
    }

    /* Checks space in event queues */
    if( Dem_EventQueueDataNumber < eventQueueSize )
    {
        /* Sets data to event queue */
        Dem_EventQueueBuffer[Dem_EventQueueWriteIndex].Kind   = Kind;       /* [GUD]Dem_EventQueueWriteIndex */
        Dem_EventQueueBuffer[Dem_EventQueueWriteIndex].Index  = Index;      /* [GUD]Dem_EventQueueWriteIndex */
        Dem_EventQueueBuffer[Dem_EventQueueWriteIndex].Status = Status;     /* [GUD]Dem_EventQueueWriteIndex */

        /* Update data count in event queue */
        Dem_EventQueueDataNumber++;
        /* Update write index for event queue */
        Dem_EventQueueWriteIndex = Dem_EventQueueWriteIndex + (Dem_u16_EventQueueIndexType)1U;
        if( Dem_EventQueueWriteIndex > eventQueueMaxIndex )
        {
            Dem_EventQueueWriteIndex = DEM_EVENT_QUEUE_MIN_INDEX;
        }
        else
        {
            /* No process */
        }
        retVal = DEM_IRT_OK;
    }
    else
    {
        /* No process */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_EventQueue_Dequeue                                   */
/* Description   | Takes out the queued event.                              */
/* Preconditions | Exists event in event queue by Dem_EventQueue_Enqueue.   */
/* Parameters    | [out] KindPtr :                                          */
/*               |        Data kind.                                        */
/*               | [out] IndexPtr :                                         */
/*               |        Identification of an event by assigned EventId.   */
/*               | [out] StatusPtr :                                        */
/*               |        Monitor test result.                              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : taking out of the event was succeed- */
/*               |        ed.                                               */
/*               |        DEM_IRT_NG : taking out of the event failed, or - */
/*               |        there are no queueing event.                      */
/* Notes         | Called within the exclusive Dem_EventQueueBufferAccess.  */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EventQueue_Dequeue
(
    P2VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC, AUTOMATIC ) KindPtr,
    P2VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC, AUTOMATIC ) IndexPtr,
    P2VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC, AUTOMATIC ) StatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) cnt;    /* loop counter */
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) dataNumberInEventQueue;  /* loop limit */
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) eventQueueMaxIndex;

    retVal = DEM_IRT_NG;
    eventQueueMaxIndex = DEM_EVENT_QUEUE_MAX_INDEX;

    /* check range of Dem_EventQueueReadIndex.          */
    if ( Dem_EventQueueReadIndex > eventQueueMaxIndex )                                         /* [GUD:if]Dem_EventQueueReadIndex */
    {
        /* Clear EventQueue management information except EventQueueBuffer */
        Dem_EventQueue_InitQueueMngInfo();
    }

    /* Dem_EventQueueDataNumber copies to Limit for loop because it has changed by dequeue */
    dataNumberInEventQueue = Dem_EventQueueDataNumber;

    /* Checks exist event in event queues */
    if( dataNumberInEventQueue > DEM_EVENT_QUEUE_NUMBER_EMPTY )
    {
        /* Loops until get queued data or skip all queued data */
        for( cnt = (Dem_u16_EventQueueIndexType)0U; cnt < dataNumberInEventQueue; cnt++ )
        {
            if( Dem_EventQueueBuffer[Dem_EventQueueReadIndex].Kind == DEM_ASYNCREQ_EMPTY )      /* [GUD]Dem_EventQueueReadIndex */
            {
                /* Progresses read index */
                Dem_EventQueue_ProgressReadIndex();
            }
            else
            {
                /* Gets queueud data */
                Dem_EventQueue_GetQueueData( KindPtr , IndexPtr , StatusPtr );                  /* [GUD]Dem_EventQueueReadIndex */
                /* Returns ok when get queue data */
                retVal = DEM_IRT_OK;
                break;
            }
        }
    }
    else
    {
        /* No process */
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_EventQueue_IsQueueEmpty                              */
/* Description   | Whether Queue is empty or not..                          */
/* Preconditions |                                                          */
/* Parameters    | void                                                     */
/* Return Value  | boolean                                                  */
/*               |      FALSE : Queue is not empty.                         */
/*               |      TRUE  : Queue is empty.                             */
/* Notes         | Called within the exclusive Dem_EventQueueBufferAccess.  */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_EventQueue_IsQueueEmpty
( void )
{
    VAR( boolean, AUTOMATIC ) isQueueEmpty;

    isQueueEmpty    =   (boolean)FALSE;

    if( Dem_EventQueueDataNumber == DEM_EVENT_QUEUE_NUMBER_EMPTY )
    {
        isQueueEmpty    =   (boolean)TRUE;
    }
    return isQueueEmpty;
}

/****************************************************************************/
/* Function Name | Dem_EventQueue_GetQueueData                              */
/* Description   | Gets event data from event queue.                        */
/* Preconditions | Exists event in event queue by Dem_EventQueue_Enqueue.   */
/* Parameters    | [out] KindPtr :                                          */
/*               |        Data kind.                                        */
/*               | [out] IndexPtr :                                         */
/*               |        Identification of an event by assigned EventId.   */
/*               | [out] StatusPtr :                                        */
/*               |        Monitor test result.                              */
/* Return Value  | void                                                     */
/* Notes         | Called within the exclusive Dem_EventQueueBufferAccess.  */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_EventQueue_GetQueueData
(
    P2VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC, AUTOMATIC ) KindPtr,
    P2VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC, AUTOMATIC ) IndexPtr,
    P2VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC, AUTOMATIC ) StatusPtr
)
{
    /* Gets queued data */
    (*KindPtr)   = Dem_EventQueueBuffer[Dem_EventQueueReadIndex].Kind;              /* [GUDCHK:SETVAL]Dem_EventQueueReadIndex */
    (*IndexPtr)  = Dem_EventQueueBuffer[Dem_EventQueueReadIndex].Index;             /* [GUDCHK:SETVAL]Dem_EventQueueReadIndex */
    (*StatusPtr) = Dem_EventQueueBuffer[Dem_EventQueueReadIndex].Status;            /* [GUDCHK:SETVAL]Dem_EventQueueReadIndex */

    /* Progresses read index */
    Dem_EventQueue_ProgressReadIndex();

    return;
}


/****************************************************************************/
/* Function Name | Dem_EventQueue_ProgressReadIndex                         */
/* Description   | Progresses read index.                                   */
/* Preconditions | Exists event in event queue by Dem_EventQueue_Enqueue.   */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | Called within the exclusive Dem_EventQueueBufferAccess.  */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_EventQueue_ProgressReadIndex
( void )
{
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) eventQueueMaxIndex;

    eventQueueMaxIndex = DEM_EVENT_QUEUE_MAX_INDEX;

    /* Clears old queue */
    Dem_EventQueueBuffer[Dem_EventQueueReadIndex].Kind   = DEM_ASYNCREQ_EMPTY;                  /* [GUDCHK:SETVAL]Dem_EventQueueReadIndex */
    Dem_EventQueueBuffer[Dem_EventQueueReadIndex].Index  = DEM_EVENT_QUEUE_INITIAL_DATA_INDEX;  /* [GUDCHK:SETVAL]Dem_EventQueueReadIndex */
    Dem_EventQueueBuffer[Dem_EventQueueReadIndex].Status = DEM_EVENT_QUEUE_INITIAL_DATA_STATUS; /* [GUDCHK:SETVAL]Dem_EventQueueReadIndex */
    /* Update data count in event queue */
    Dem_EventQueueDataNumber = Dem_EventQueueDataNumber - (Dem_u16_EventQueueIndexType)1U;

    /* Update data count for clear in event queue */
    if( Dem_EventQueueClearDataNumber > DEM_EVENT_QUEUE_CLEAR_NUMBER_NONE )
    {
        /* There is a possibility that Clear will interrupt after the judgment of Clear in the set event process */
        Dem_EventQueueClearDataNumber = Dem_EventQueueClearDataNumber - (Dem_u16_EventQueueIndexType)1U;
    }
    else
    {
        /* No process */
    }
    /* Update read index for event queue */
    Dem_EventQueueReadIndex = Dem_EventQueueReadIndex + (Dem_u16_EventQueueIndexType)1U;
    if( Dem_EventQueueReadIndex > eventQueueMaxIndex )
    {
        Dem_EventQueueReadIndex = DEM_EVENT_QUEUE_MIN_INDEX;
    }
    else
    {
        /* No process */
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dem_EventQueue_SetClearFlag                              */
/* Description   | Sets clear flag to event queue data.                     */
/* Preconditions | Exists event in event queue by Dem_EventQueue_Enqueue.   */
/*               | StartIndex must be smaller than EndNumberOfForStatement. */
/* Parameters    | [in] DTCGroup :                                          */
/*               |        DTCValue specified at the time of Clear.          */
/*               | [in] DTCOrigin :                                         */
/*               |        DTCOrigin specified at the time of Clear.         */
/*               | [in] StartIndex :                                        */
/*               |        Start index of set clear flag.                    */
/*               | [in] EndNumberOfForStatement :                           */
/*               |        End number of for statement.                      */
/* Return Value  | void                                                     */
/* Notes         | [!ATTENSSION!] This function is NOT called within        */
/*               | the exclusive Dem_EventQueueBufferAccess.                */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_EventQueue_SetClearFlag
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,              /* MISRA DEVIATION */
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) StartIndex,
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) EndNumberOfForStatement
)
{
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    if ( DTCOrigin != DEM_DTC_ORIGIN_PRIMARY_MEMORY )
    {
        /*  uesr define memory.     */
        Dem_EventQueue_SetClearFlag_UserDefMem( DTCGroup, DTCOrigin, StartIndex, EndNumberOfForStatement );
    }
    else
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */
    {
        /*  primary memory.             */
        Dem_EventQueue_SetClearFlag_PrimaryMemory( DTCGroup, StartIndex, EndNumberOfForStatement );
    }
    return ;
}


/****************************************************************************/
/* Function Name | Dem_EventQueue_SetClearFlag_PrimaryMemory                */
/* Description   | Sets clear flag to event queue data.                     */
/* Preconditions | Exists event in event queue by Dem_EventQueue_Enqueue.   */
/*               | StartIndex must be smaller than EndNumberOfForStatement. */
/* Parameters    | [in] DTCGroup :                                          */
/*               |        DTCValue specified at the time of Clear.          */
/*               | [in] StartIndex :                                        */
/*               |        Start index of set clear flag.                    */
/*               | [in] EndNumberOfForStatement :                           */
/*               |        End number of for statement.                      */
/* Return Value  | void                                                     */
/* Notes         | [!ATTENSSION!] This function is NOT called within        */
/*               | the exclusive Dem_EventQueueBufferAccess.                */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_EventQueue_SetClearFlag_PrimaryMemory
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) StartIndex,
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) EndNumberOfForStatement
)
{
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) cnt;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventConfigureNum;
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) asyncReqNum;
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) asyncReqIndex;
    VAR( Dem_u08_AsyncReqFuncAttrType, AUTOMATIC ) funcAttribute;
    VAR( boolean, AUTOMATIC ) clearAllowed;
    VAR( boolean, AUTOMATIC ) eventOBDKind;

    eventConfigureNum = Dem_PrimaryMemEventConfigureNum;
    asyncReqNum = Dem_AsyncReqNum;

    /* Dicisions clear event */
    /* Sets clear flag to all events in event queues */
    for( cnt = StartIndex; cnt < EndNumberOfForStatement; cnt++ )                               /* [GUD:for]cnt */
    {
        asyncReqIndex = (Dem_u08_AsyncReqTableIndexType)Dem_EventQueueBuffer[cnt].Kind;         /* [GUD]cnt */
        if( asyncReqIndex < asyncReqNum )                                                       /* [GUD:if]asyncReqIndex */
        {
            funcAttribute = Dem_ExecAsyncReqTable[ asyncReqIndex ].FuncAttribute;               /* [GUD]asyncReqIndex */

            /*  target of CleaDTC (Primary Memory)?     */
            if( ( funcAttribute & DEM_FNCATTR_EXE_CLRDTC ) == DEM_FNCATTR_EXE_CLRDTC )
            {
                /*  use event condition ?   */
                if( ( funcAttribute & DEM_FNCATTR_EXE_CLRDTCEVT ) == DEM_FNCATTR_EXE_CLRDTCEVT )
                {
                    eventCtrlIndex  =   ( Dem_u16_EventCtrlIndexType )Dem_EventQueueBuffer[cnt].Index;      /* [GUD]cnt */

                    /*  PrimaryMemory ?                 */
                    if ( eventCtrlIndex < eventConfigureNum )               /* [GUD:if]eventCtrlIndex */
                    {
                        /*  clear by event condition.   */
                        if( DTCGroup == DEM_DTC_GROUP_EMISSION_REL_DTCS )
                        {
                            /*  if OBD event ?              */
                            eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_ByEvtCtrlIdx( eventCtrlIndex );       /* [GUD]eventCtrlIndex */
                            if( eventOBDKind == (boolean)TRUE ) /*  OBD     */
                            {
                                clearAllowed = Dem_CfgInfoPm_ClearAllowed_ByEvtCtrlIdx( eventCtrlIndex );               /* [GUD]eventCtrlIndex */
                            }
                            else
                            {
                                clearAllowed = (boolean)FALSE;
                            }
                        }
                        else
                        {
                            /* DTCGroup is DEM_DTC_GROUP_ALL_DTCS */
                            clearAllowed = Dem_CfgInfoPm_ClearAllowed_ByEvtCtrlIdx( eventCtrlIndex );                   /* [GUD]eventCtrlIndex */
                        }
                    }
                    else
                    {
                        /*  UserDefinedMemory.          */
                        /*  no target.                  */
                        clearAllowed = (boolean)FALSE;
                    }
                }
                else
                {
                    /*  not use event condition.        */
                    clearAllowed = (boolean)TRUE;
                }

                if( clearAllowed == (boolean)TRUE )
                {
                    /*  release data queue              */
#if ( DEM_ASYNCDATAQUE_USE == STD_ON )  /* [FuncSw] */
                    Dem_EventQueue_ReleaseDataQueAtSetClearFlag( Dem_EventQueueBuffer[cnt].Kind, Dem_EventQueueBuffer[cnt].Status );        /* [GUD]cnt *//* [GUD]Dem_EventQueueBuffer[cnt].Kind( ==asyncReqIndex )  */
#endif  /* ( DEM_ASYNCDATAQUE_USE == STD_ON )   */
                    Dem_EventQueueBuffer[cnt].Kind = DEM_ASYNCREQ_EMPTY;        /* [GUD]cnt */
                }
                else
                {
                    /* No process */
                }

            }
            else
            {
                /* Note */
                /* Code is written here except for all clear at ClearDTC */
                /* No process */
            }
        }
    }
    return ;
}

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_EventQueue_SetClearFlag_UserDefMem                   */
/* Description   | Sets clear flag to event queue data.                     */
/* Preconditions | Exists event in event queue by Dem_EventQueue_Enqueue.   */
/*               | StartIndex must be smaller than EndNumberOfForStatement. */
/* Parameters    | [in] DTCGroup :                                          */
/*               |        DTCValue specified at the time of Clear.          */
/*               | [in] DTCOrigin :                                         */
/*               |        DTCOrigin specified at the time of Clear.         */
/*               | [in] StartIndex :                                        */
/*               |        Start index of set clear flag.                    */
/*               | [in] EndNumberOfForStatement :                           */
/*               |        End number of for statement.                      */
/* Return Value  | void                                                     */
/* Notes         | [!ATTENSSION!] This function is NOT called within        */
/*               | the exclusive Dem_EventQueueBufferAccess.                */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_EventQueue_SetClearFlag_UserDefMem
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,    /* MISRA DEVIATION */
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) StartIndex,
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) EndNumberOfForStatement
)
{
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) cnt;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) asyncReqNum;
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) asyncReqIndex;
    VAR( Dem_u08_AsyncReqFuncAttrType, AUTOMATIC ) funcAttribute;
    VAR( boolean, AUTOMATIC ) clearAllowed;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex_comp;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvEventIndex;

    asyncReqNum = Dem_AsyncReqNum;

    /*  get udmInfoTableIndex from DTCOrigin. */
    retVal = Dem_CfgInfoUdm_CnvDTCOriginToInternalInfoTableIndex( DTCOrigin, &udmInfoTableIndex );    /* [GUD:RET:DEM_IRT_OK]udmInfoTableIndex */

    if ( retVal == DEM_IRT_OK )
    {
        /* Dicisions clear event */
        /* Sets clear flag to all events in event queues */
        for( cnt = StartIndex; cnt < EndNumberOfForStatement; cnt++ )                           /* [GUD:if]cnt */
        {
            asyncReqIndex = (Dem_u08_AsyncReqTableIndexType)Dem_EventQueueBuffer[cnt].Kind;     /* [GUD]cnt */
            if( asyncReqIndex < asyncReqNum )                                                   /* [GUD:if]asyncReqIndex */
            {
                funcAttribute = Dem_ExecAsyncReqTable[ asyncReqIndex ].FuncAttribute;           /* [GUD]asyncReqIndex */

                /*  target of ClearDTC at UserDefineMemory ?    */
                if( ( funcAttribute & DEM_FNCATTR_EXE_UDMCLRDTC ) == DEM_FNCATTR_EXE_UDMCLRDTC )
                {
                    clearAllowed = (boolean)FALSE;

                    /*  use event condition ?   */
                    if( ( funcAttribute & DEM_FNCATTR_EXE_CLRDTCEVT ) == DEM_FNCATTR_EXE_CLRDTCEVT )
                    {
                        /*  get EventIndex.                     */
                        eventCtrlIndex  =   ( Dem_u16_EventCtrlIndexType )Dem_EventQueueBuffer[cnt].Index;      /* [GUD]cnt */

                        /* Convert EventCtrlIndex to udmEventIndex */
                        retCnvEventIndex = Dem_CfgInfoUdm_CnvEventCtrlIndexToUdmEventIndex( eventCtrlIndex, &udmEventIndex );   /* [GUD:RET:DEM_IRT_OK]udmEventIndex */

                        /*  UserDefineMemory ?                  */
                        if ( retCnvEventIndex == DEM_IRT_OK )
                        {
                            udmInfoTableIndex_comp =  Dem_CfgInfoUdm_GetMemoryDestination( udmEventIndex );                     /* [GUD]udmEventIndex *//* [GUD:RET:IF_GUARDED: UdmEventIndex ]udmInfoTableIndex */

                            if( udmInfoTableIndex == udmInfoTableIndex_comp )   /* [GUD:if]udmInfoTableIndex */
                            {
                                clearAllowed = (boolean)TRUE;
                            }

                        }

                    }
                    else
                    {
                        /*  not use event condition.        */
                        clearAllowed = (boolean)TRUE;
                    }

                    if( clearAllowed == (boolean)TRUE )
                    {
                        /*  release data queue              */
#if ( DEM_ASYNCDATAQUE_USE == STD_ON )  /* [FuncSw] */
                        Dem_EventQueue_ReleaseDataQueAtSetClearFlag( Dem_EventQueueBuffer[cnt].Kind, Dem_EventQueueBuffer[cnt].Status );        /* [GUD]cnt *//* [GUD]Dem_EventQueueBuffer[cnt].Kind( == asyncReqIndex ) */
#endif  /* ( DEM_ASYNCDATAQUE_USE == STD_ON )   */
                        Dem_EventQueueBuffer[cnt].Kind = DEM_ASYNCREQ_EMPTY;        /* [GUD]cnt */
                    }
                    else
                    {
                        /* No process */
                    }

                }
                else
                {
                    /* Note */
                    /* Code is written here except for all clear at ClearDTC */
                    /* No process */
                }
            }
        }
    }
    return ;
}
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */

#if ( DEM_ASYNCDATAQUE_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_EventQueue_ReleaseDataQueAtSetClearFlag              */
/* Description   | Release data queue at sets clear flag to event queue data.*/
/* Preconditions |                                                          */
/* Parameters    | [in] Kind :                                              */
/*               |        Data kind.                                        */
/*               | [in] Status :                                            */
/*               |        parameter.                                        */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_EventQueue_ReleaseDataQueAtSetClearFlag
(
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) Kind,              /* [PRMCHK:CALLER] */
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status
)
{
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) asyncReqIndex;
    VAR( Dem_u08_AsyncDataQueTableIndexType, AUTOMATIC ) asyncDataQueNum;
    VAR( Dem_u08_AsyncDataQueTableIndexType, AUTOMATIC ) asyncDataQueIndex;

    asyncDataQueNum = Dem_AsyncDataQueNum;

    asyncReqIndex = (Dem_u08_AsyncReqTableIndexType)Kind;
    asyncDataQueIndex = Dem_ExecAsyncReqTable[ asyncReqIndex ].AsyncDataQueIndex;   /* [GUDCHK:CALLER]Kind( == asyncReqIndex)  */

    if( asyncDataQueIndex < asyncDataQueNum )       /* [GUD:if]asyncDataQueIndex */
    {
        /* Exclusion start for Dem_EventQueueBufferAccess */
        SchM_Enter_Dem_EventQueueBufferAccess();

        /*  release data queue      */
        Dem_AsyncReqData_ReleaseQueWithoutData( asyncDataQueIndex, (Dem_u08_AsyncDataQueIndexType)Status );     /* [GUD]asyncDataQueIndex */

        SchM_Exit_Dem_EventQueueBufferAccess();
    }
    return ;
}
#endif  /* ( DEM_ASYNCDATAQUE_USE == STD_ON )   */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

