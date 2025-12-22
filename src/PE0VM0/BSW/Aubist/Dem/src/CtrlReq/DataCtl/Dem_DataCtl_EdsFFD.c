/* Dem_DataCtl_EdsFFD_c(v5-5-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_EdsFFD/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "Dem_DataCtl_local.h"

#if ( DEM_OBDONEDS_SUPPORT == STD_ON )

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataCtl_SearchOrderedPriorityOBDFreezeFrame
(
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) HighPriorityEventStrgIndexPtr,
    P2VAR( Dem_u08_FaultIndexType, AUTOMATIC, AUTOMATIC ) FaultIndexPtr
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataCtl_JudgeOrderedPriorityOBDFreezeFrame
(
    VAR( Dem_u08_EventPriorityType, AUTOMATIC ) EventPriority,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u08_EventPriorityType, AUTOMATIC, AUTOMATIC ) LatchEventPriorityPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) LatchEventStrgIndexPtr
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataCtl_SearchFaultOrderedPriorityOBDFreezeFrame
(
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) HighPriorityEventStrgIndexPtr,
    P2VAR( Dem_u08_FaultIndexType, AUTOMATIC, AUTOMATIC ) FaultIndexPtr
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataCtl_JudgeFaultOrderedPriorityOBDFreezeFrame
(
    VAR( Dem_u08_EventPriorityType, AUTOMATIC ) EventPriority,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) StatusOfDTC,
    P2VAR( Dem_u08_EventPriorityType, AUTOMATIC, AUTOMATIC ) LatchEventPriorityPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) LatchEventStrgIndexPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) LatchConfirmedOccurrenceOrderPtr
);

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
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_DataCtl_SearchPriorityOBDFreezeFrame                 */
/* Description   | Search the Highest priority event index.                 */
/* Preconditions | none                                                     */
/* Parameters    |  [out] HighPriorityEventStrgIndexPtr :                   */
/*               |        (1)Highest priority event index                   */
/*               |        (2)Oldest FFD event index                         */
/*               |  [out] FaultIndexPtr : fault index.                      */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |        DEM_IRT_OK : find the eventStrgIndex              */
/*               |        DEM_IRT_NG : not found                            */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_DataCtl_SearchPriorityOBDFreezeFrame(v5-3-0). */
/*   v5-5-0      | refactor function.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataCtl_SearchPriorityOBDFreezeFrame
(
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) HighPriorityEventStrgIndexPtr,
    P2VAR( Dem_u08_FaultIndexType, AUTOMATIC, AUTOMATIC ) FaultIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) outputPendingOBDFFDWithoutCDTC;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;

    eventStrgIndex  = DEM_EVENTSTRGINDEX_INVALID;
    faultIndex      = DEM_FAULTINDEX_INVALID;

    /* Search priority OBD FFD from ConfirmedOrderList. */
    outputPendingOBDFFDWithoutCDTC = Dem_CfgInfoPm_JudgeOutputPendingOBDFFDWithoutCDTC();
    if ( outputPendingOBDFFDWithoutCDTC == (boolean)FALSE )
    {
        /* Search priority OBD FFD from FaultOrderList. */
        retVal = Dem_DataCtl_SearchOrderedPriorityOBDFreezeFrame( &eventStrgIndex, &faultIndex );
    }
    else
    {
        retVal = Dem_DataCtl_SearchFaultOrderedPriorityOBDFreezeFrame( &eventStrgIndex, &faultIndex );

    }

    *HighPriorityEventStrgIndexPtr = eventStrgIndex;
    *FaultIndexPtr  =   faultIndex;

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DataCtl_SearchOrderedPriorityOBDFreezeFrame          */
/* Description   | Search the Highest priority event index.                 */
/* Preconditions | none                                                     */
/* Parameters    |  [out] HighPriorityEventStrgIndexPtr :                   */
/*               |        (1)Highest priority event index                   */
/*               |        (2)Oldest FFD event index                         */
/*               |  [out] FaultIndexPtr : fault index.                      */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |        DEM_IRT_OK : find the eventStrgIndex              */
/*               |        DEM_IRT_NG : not found                            */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_Control_SearchOrderedPriorityOBDFreezeFrame(v5-3-0). */
/*   v5-5-0      | refactor function.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataCtl_SearchOrderedPriorityOBDFreezeFrame
(
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) HighPriorityEventStrgIndexPtr,
    P2VAR( Dem_u08_FaultIndexType, AUTOMATIC, AUTOMATIC ) FaultIndexPtr
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) latchfaultIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retJudge;
    VAR( boolean, AUTOMATIC ) orderExistFlag;
    VAR( boolean, AUTOMATIC ) isObdDTC;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndex;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_EventPriorityType, AUTOMATIC ) eventPriority;
    VAR( Dem_u08_EventPriorityType, AUTOMATIC ) latchEventPriority;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) latchEventStrgIndex;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    retVal = DEM_IRT_NG;
    faultIndex              = DEM_FAULTINDEX_INVALID;
    latchfaultIndex         = DEM_FAULTINDEX_INVALID;
    failRecordNum           = (Dem_u08_OrderIndexType)Dem_FailRecordNum;
    latchEventPriority      = DEM_PRIORITY_OBD_OBDFFD;
    latchEventStrgIndex     = DEM_EVENTSTRGINDEX_INVALID;
    eventStorageNum         = Dem_PrimaryMemEventStorageNum;

    for( orderListIndex = (Dem_u08_OrderIndexType)0U; orderListIndex < failRecordNum; orderListIndex++ )
    {
        eventStrgIndex  = DEM_EVENTSTRGINDEX_INVALID;
        statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;

        Dem_Data_GetConfirmedOrderEventStrgIndex( orderListIndex, &eventStrgIndex, &faultIndex, &statusOfDTC, &orderExistFlag );

        if( orderExistFlag == (boolean)TRUE )
        {
            if( eventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]eventStrgIndex */
            {
                isObdDTC = Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( eventStrgIndex );    /* [GUD] eventStrgIndex */
                if ( isObdDTC == (boolean)TRUE )
                {
                    /* Use eventStrgIndex to get event priority from EventParameterTable */
                    eventPriority = Dem_CfgInfoPm_GetEventPriority( eventStrgIndex );       /* [GUD]eventStrgIndex */

                    retJudge = Dem_DataCtl_JudgeOrderedPriorityOBDFreezeFrame( eventPriority, eventStrgIndex, faultIndex, &latchEventPriority, &latchEventStrgIndex );
                    if( retJudge == DEM_IRT_OK )
                    {
                        latchfaultIndex =   faultIndex;
                        retVal = DEM_IRT_OK;
                    }
                }
            }
            else
            {
                /* For event invalidity, a loop continues. */
            }
        }
    }
    *HighPriorityEventStrgIndexPtr = latchEventStrgIndex;
    *FaultIndexPtr  =   latchfaultIndex;

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DataCtl_JudgeOrderedPriorityOBDFreezeFrame           */
/* Description   | Judge the Highest priority event index.                  */
/* Preconditions | none                                                     */
/* Parameters    |  [in] EventPriority                                      */
/*               |  [in] EventStrgIndex                                     */
/*               |  [in] FaultIndex                                         */
/*               |  [in/out] LatchEventPriorityPtr                          */
/*               |  [in/out] LatchEventStrgIndexPtr                         */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |        DEM_IRT_OK : in/out parameters has changed.       */
/*               |        DEM_IRT_NG : in/out parameters has not changed.   */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataCtl_JudgeOrderedPriorityOBDFreezeFrame
(
    VAR( Dem_u08_EventPriorityType, AUTOMATIC ) EventPriority,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u08_EventPriorityType, AUTOMATIC, AUTOMATIC ) LatchEventPriorityPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) LatchEventStrgIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckStoredObdFFD;

    retVal = DEM_IRT_NG;

    if( ( *LatchEventPriorityPtr ) > EventPriority )
    {
        retCheckStoredObdFFD = Dem_Data_CheckStoredOBDFFDInFaultRecord( FaultIndex );
        if( retCheckStoredObdFFD == DEM_IRT_OK )
        {
            ( *LatchEventStrgIndexPtr ) = EventStrgIndex;
            ( *LatchEventPriorityPtr ) = EventPriority;
            retVal = DEM_IRT_OK;
        }
    }
    else
    {
        if( ( *LatchEventStrgIndexPtr ) == DEM_EVENTSTRGINDEX_INVALID )
        {
            retCheckStoredObdFFD = Dem_Data_CheckStoredOBDFFDInFaultRecord( FaultIndex );
            if( retCheckStoredObdFFD == DEM_IRT_OK )
            {
                ( *LatchEventStrgIndexPtr ) = EventStrgIndex;
                retVal = DEM_IRT_OK;
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DataCtl_SearchFaultOrderedPriorityOBDFreezeFrame     */
/* Description   | Search the Highest priority event index.                 */
/* Preconditions | none                                                     */
/* Parameters    |  [out] HighPriorityEventStrgIndexPtr :                   */
/*               |        (1)Highest priority event index                   */
/*               |        (2)Oldest FFD event index                         */
/*               |  [out] FaultIndexPtr : fault index.                      */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |        DEM_IRT_OK : find the EventIndex                  */
/*               |        DEM_IRT_NG : not found                            */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_Control_SearchFaultOrderedPriorityOBDFreezeFrame(v5-3-0). */
/*   v5-5-0      | refactor function.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataCtl_SearchFaultOrderedPriorityOBDFreezeFrame
(
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) HighPriorityEventStrgIndexPtr,
    P2VAR( Dem_u08_FaultIndexType, AUTOMATIC, AUTOMATIC ) FaultIndexPtr
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) latchfaultIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retJudge;
    VAR( boolean, AUTOMATIC ) orderExistFlag;
    VAR( boolean, AUTOMATIC ) isObdDTC;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndex;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_EventPriorityType, AUTOMATIC ) eventPriority;
    VAR( Dem_u08_EventPriorityType, AUTOMATIC ) latchEventPriority;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) latchEventStrgIndex;
    VAR( Dem_DTCStatusStType, AUTOMATIC ) dtcStatusSt;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) latchConfirmedOccurrenceOrder;

    retVal = DEM_IRT_NG;
    faultIndex    = DEM_FAULTINDEX_INVALID;
    latchfaultIndex         = DEM_FAULTINDEX_INVALID;
    failRecordNum = (Dem_u08_OrderIndexType)Dem_FailRecordNum;
    latchEventPriority = DEM_PRIORITY_OBD_OBDFFD;
    latchEventStrgIndex    = DEM_EVENTSTRGINDEX_INVALID;
    latchConfirmedOccurrenceOrder    = DEM_FAIL_OCCURRENCE_NUM_INVALID;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    for( orderListIndex = (Dem_u08_OrderIndexType)0U; orderListIndex < failRecordNum; orderListIndex++ )
    {
        eventStrgIndex  = DEM_EVENTSTRGINDEX_INVALID;
        dtcStatusSt.DTCStatus        = DEM_DTCSTATUS_BYTE_ALL_OFF;
        dtcStatusSt.ExtendDTCStatus  = DEM_DTCSTATUS_BYTE_ALL_OFF;
        dtcStatusSt.ExtendDTCStatus2 = DEM_DTCSTATUS_BYTE_ALL_OFF;

        Dem_Data_GetFaultOrderEventStrgIndex( orderListIndex, &eventStrgIndex, &faultIndex, &dtcStatusSt, &orderExistFlag );
        if( orderExistFlag == (boolean)TRUE )
        {
            if( eventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]eventStrgIndex */
            {
                isObdDTC = Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( eventStrgIndex );    /* [GUD] eventStrgIndex */
                if ( isObdDTC == (boolean)TRUE )
                {
                    /* Use EventStrgIndex to get event priority from EventParameterTable */
                    eventPriority = Dem_CfgInfoPm_GetEventPriority( eventStrgIndex );       /* [GUD]eventStrgIndex */

                    retJudge = Dem_DataCtl_JudgeFaultOrderedPriorityOBDFreezeFrame( eventPriority, eventStrgIndex, faultIndex, dtcStatusSt.DTCStatus, &latchEventPriority, &latchEventStrgIndex, &latchConfirmedOccurrenceOrder );
                    if( retJudge == DEM_IRT_OK )
                    {
                        latchfaultIndex =   faultIndex;
                        retVal = DEM_IRT_OK;
                    }
                }
            }
            else
            {
                /* For event invalidity, a loop continues. */
            }
        }
    }

    *HighPriorityEventStrgIndexPtr = latchEventStrgIndex;
    *FaultIndexPtr  =   latchfaultIndex;

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DataCtl_JudgeFaultOrderedPriorityOBDFreezeFrame      */
/* Description   | Judge the Highest priority event index.                  */
/* Preconditions | none                                                     */
/* Parameters    |  [in] EventPriority                                      */
/*               |  [in] EventStrgIndex                                     */
/*               |  [in] FaultIndex                                         */
/*               |  [in] StatusOfDTC                                        */
/*               |  [in/out] LatchEventPriorityPtr                          */
/*               |  [in/out] LatchEventStrgIndexPtr                         */
/*               |  [in/out] LatchConfirmedOccurrenceOrderPtr               */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |        DEM_IRT_OK : in/out parameters has changed.       */
/*               |        DEM_IRT_NG : in/out parameters has not changed.   */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataCtl_JudgeFaultOrderedPriorityOBDFreezeFrame
(
    VAR( Dem_u08_EventPriorityType, AUTOMATIC ) EventPriority,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) StatusOfDTC,
    P2VAR( Dem_u08_EventPriorityType, AUTOMATIC, AUTOMATIC ) LatchEventPriorityPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) LatchEventStrgIndexPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) LatchConfirmedOccurrenceOrderPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckStoredObdFFD;
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) confirmedOccurrenceOrder;

    retVal = DEM_IRT_NG;

    if( ( *LatchEventPriorityPtr ) > EventPriority )
    {
        retCheckStoredObdFFD = Dem_Data_CheckStoredOBDFFDInFaultRecord( FaultIndex );
        if( retCheckStoredObdFFD == DEM_IRT_OK )
        {
            ( *LatchEventStrgIndexPtr ) = EventStrgIndex;
            ( *LatchEventPriorityPtr ) = EventPriority;
            retVal = DEM_IRT_OK;

            if( ( StatusOfDTC & DEM_UDS_STATUS_CDTC ) == DEM_UDS_STATUS_CDTC )
            {
                (void)Dem_DataMngC_GetFR_ConfirmedOccurrenceOrder( FaultIndex, LatchConfirmedOccurrenceOrderPtr ); /* no return check required */
            }
            else
            {
                ( *LatchConfirmedOccurrenceOrderPtr ) = DEM_FAIL_OCCURRENCE_NUM_INVALID;
            }
        }
    }
    else if( ( *LatchEventPriorityPtr ) == EventPriority )
    {
        retCheckStoredObdFFD = Dem_Data_CheckStoredOBDFFDInFaultRecord( FaultIndex );
        if( retCheckStoredObdFFD == DEM_IRT_OK )
        {
            if( ( StatusOfDTC & DEM_UDS_STATUS_CDTC ) == DEM_UDS_STATUS_CDTC )
            {
                (void)Dem_DataMngC_GetFR_ConfirmedOccurrenceOrder( FaultIndex, &confirmedOccurrenceOrder ); /* no return check required */
                if( ( *LatchConfirmedOccurrenceOrderPtr ) > confirmedOccurrenceOrder )
                {
                    ( *LatchEventStrgIndexPtr ) = EventStrgIndex;
                    ( *LatchEventPriorityPtr ) = EventPriority;
                    ( *LatchConfirmedOccurrenceOrderPtr ) = confirmedOccurrenceOrder;
                    retVal = DEM_IRT_OK;
                }
            }
        }
    }
    else if( ( *LatchEventPriorityPtr ) >= DEM_PRIORITY_OBD_OBDFFD )
    {
        retCheckStoredObdFFD = Dem_Data_CheckStoredOBDFFDInFaultRecord( FaultIndex );
        if( retCheckStoredObdFFD == DEM_IRT_OK )
        {
            if( ( StatusOfDTC & DEM_UDS_STATUS_CDTC ) == DEM_UDS_STATUS_CDTC )
            {
                (void)Dem_DataMngC_GetFR_ConfirmedOccurrenceOrder( FaultIndex, &confirmedOccurrenceOrder ); /* no return check required */
                if( ( *LatchConfirmedOccurrenceOrderPtr ) > confirmedOccurrenceOrder )
                {
                    ( *LatchEventStrgIndexPtr ) = EventStrgIndex;
                    ( *LatchConfirmedOccurrenceOrderPtr ) = confirmedOccurrenceOrder;
                    retVal = DEM_IRT_OK;
                }
            }
            else
            {
                if( ( *LatchEventStrgIndexPtr ) == DEM_EVENTSTRGINDEX_INVALID )
                {
                    ( *LatchEventStrgIndexPtr ) = EventStrgIndex;
                    retVal = DEM_IRT_OK;
                }
            }
        }
    }
    else
    {
        /* No process */
    }

    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_OBDONEDS_SUPPORT == STD_ON )                  */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
