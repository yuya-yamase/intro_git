/* Dem_DataCtl_EventEntry02Make_Event_c(v5-5-0)                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_EventEntry02Make_Event/CODE                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_Event.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Utl.h"
#include "Dem_DataCtl_local.h"
#include "Dem_DataCtl_EventEntry_local.h"

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
/* Function Name | Dem_Data_GetDTCStatusFromTmp                             */
/* Description   | Gets the UDS DTC status byte from the event memory entr- */
/*               | y of temporary area.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] DTCStatusPtr   :                                   */
/*               |        The UDS DTC status byte which has been retrieved. */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_GetDTCStatusFromTmp
(
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    /* Stores StatusOfDTC of the event memory entry of temporary area to the specified parameter. */
    *DTCStatusPtr        = Dem_TmpEventMemoryEntry.EventRecord.StatusOfDTC;

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Data_SetDTCStatusToTmp                               */
/* Description   | Sets the specified value to the UDS DTC status byte in - */
/*               | event memory entry of temporary area.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatusStPtr :                                    */
/*               |        The UDS DTC status byte which will set.           */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_SetDTCStatusStructToTmp
(
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) DTCStatusStPtr
)
{
    /* Sets the specified DTCStatus to StatusOfDTC of the event memory entry of temporary area. */
    Dem_TmpEventMemoryEntry.EventRecord.StatusOfDTC        = DTCStatusStPtr->DTCStatus;
    Dem_TmpEventMemoryEntry.EventRecord.ExtendStatusOfDTC  = DTCStatusStPtr->ExtendDTCStatus;
    Dem_TmpEventMemoryEntry.EventRecord.ExtendStatusOfDTC2 = DTCStatusStPtr->ExtendDTCStatus2;

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Data_GetDTCStatusStructFromTmp                       */
/* Description   | Gets the UDS DTC status byte from the event memory entr- */
/*               | y of temporary area.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] DTCStatusStPtr :                                   */
/*               |        The UDS DTC status byte which has been retrieved. */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_GetDTCStatusStructFromTmp
(
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) DTCStatusStPtr
)
{
    /* Stores StatusOfDTC of the event memory entry of temporary area to the specified parameter. */
    DTCStatusStPtr->DTCStatus        = Dem_TmpEventMemoryEntry.EventRecord.StatusOfDTC;
    DTCStatusStPtr->ExtendDTCStatus  = Dem_TmpEventMemoryEntry.EventRecord.ExtendStatusOfDTC;
    DTCStatusStPtr->ExtendDTCStatus2 = Dem_TmpEventMemoryEntry.EventRecord.ExtendStatusOfDTC2;

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Data_InitFailureCounterOfTmp                         */
/* Description   | Initial FailureCounter (set zero)                        */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_InitFailureCounterOfTmp
( void )
{

    Dem_TmpEventMemoryEntry.EventRecord.FailureCounter = DEM_FAILURECYCLE_COUNT_INITIAL_VALUE;

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Data_GetFailureCounterFromTmp                        */
/* Description   | Gets the failure counter and failure threshold from the  */
/*               | temporary memory.                                        */
/* Preconditions | none                                                     */
/* Parameters    | [out] FaultCounterPtr :                                  */
/*               |        fault counter.                                    */
/*               | [out] FaultCounterThresholdPtr :                         */
/*               |        fault threshold.                                  */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_GetFailureCounterFromTmp
(
    P2VAR( Dem_u08_FailureCounterType, AUTOMATIC, AUTOMATIC ) FailureCounterPtr,
    P2VAR( Dem_u08_FailureCounterType, AUTOMATIC, AUTOMATIC ) FailureCounterThresholdPtr
)
{
    *FailureCounterPtr          = Dem_TmpEventMemoryEntry.EventRecord.FailureCounter;
    *FailureCounterThresholdPtr = Dem_Event_GetEventFailureCycleCounterThreshold( Dem_TmpEventMemoryEntry.EventStrgIndex ); /* [GUDCHK:SETVAL]Dem_TmpEventMemoryEntry.EventStrgIndex */

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Data_IncrementFailureCounterOfTmp                    */
/* Description   | Count up FailureCounter at the time of a notice of       */
/*               |  first DEM_EVENT_STATUS_FAILED in the cycle.             */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_IncrementFailureCounterOfTmp
( void )
{
    VAR( Dem_u08_FailureCounterType, AUTOMATIC )                failureCycleCounterThreshold;

    /* This Fail Event notice is the first in the period of the operation cycle.  */
    failureCycleCounterThreshold = Dem_Event_GetEventFailureCycleCounterThreshold( Dem_TmpEventMemoryEntry.EventStrgIndex );    /* [GUDCHK:SETVAL]Dem_TmpEventMemoryEntry.EventStrgIndex */
    /* Confirm that it does not exceed the threshold after count up */
    if( failureCycleCounterThreshold > Dem_TmpEventMemoryEntry.EventRecord.FailureCounter )
    {
        Dem_TmpEventMemoryEntry.EventRecord.FailureCounter++;
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Data_IncrementEventOccurrenceCounterOfTmp            */
/* Description   | Count up OccurrenceCounter when TestFailed bit of old    */
/*               | DTC status is off at the time of a notice of             */
/*               | DEM_EVENT_STATUS_FAILED.                                 */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_Data_IncrementFailureCounterOfTmp.*/
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_IncrementEventOccurrenceCounterOfTmp
( void )
{
    if( Dem_TmpEventMemoryEntry.EventRecord.OccurrenceCounter < DEM_EVENT_OCCURRENCE_COUNT_MAX_VALUE )
    {
        Dem_TmpEventMemoryEntry.EventRecord.OccurrenceCounter++;
    }

    return ;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
