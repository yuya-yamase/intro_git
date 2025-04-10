/* Dem_If_SetEvent_c(v5-5-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/If_SetEvent/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_CmnIf_Control.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_Control_Specific.h"

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
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_SetEventStatus                                       */
/* Description   | Queues the events reported by SW-Cs via RTE. This API c- */
/*               | an only be used through the RTE, and therefore no decla- */
/*               | ration is exported via Dem.h. Some bits of the UDS DTC - */
/*               | status byte changes synchronously or asynchronously (re- */
/*               | fer to Dem036 and Dem379).OBD Events Suppression shall - */
/*               | be ignored for this computation.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [in] EventStatus :                                       */
/*               |        Monitor test result                               */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : set of event status was successful         */
/*               |        E_NOT_OK : set of event status failed or could n- */
/*               |        ot be accepted (e.g.                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetEventStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;

    retVal = E_NOT_OK;

    internalReturnValue = Dem_Control_SetEventStatus( EventId , EventStatus );

    /* Convert return value */
    switch( internalReturnValue )
    {
        case DEM_IRT_OK:
            retVal = E_OK;
            break;
        case DEM_IRT_NG:
            /* No Process */
            break;
        default:
            /* No Process */
            break;
    }

    return retVal;
}


#if ( DEM_MONITORDATA_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_SetEventStatusWithMonitorData                        */
/* Description   | Queues the events reported by SW-Cs via RTE. This API c- */
/*               | an only be used through the RTE, and therefore no decla- */
/*               | ration is exported via Dem.h. Some bits of the UDS DTC - */
/*               | status byte changes synchronously or asynchronously (re- */
/*               | fer to Dem036 and Dem379).OBD Events Suppression shall - */
/*               | be ignored for this computation.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [in] EventStatus :                                       */
/*               |        Monitor test result                               */
/*               | [in] monitorData0 :                                      */
/*               |        Monitor test result                               */
/*               | [in] monitorData1 :                                      */
/*               |        Monitor test result                               */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : set of event status was successful         */
/*               |        E_NOT_OK : set of event status failed or could n- */
/*               |        ot be accepted (e.g.                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetEventStatusWithMonitorData
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData1  /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;

    retVal = E_NOT_OK;

    internalReturnValue = Dem_Control_SetEventStatusWithMonitorData( EventId , EventStatus , monitorData0 );

    /* Convert return value */
    if( internalReturnValue == DEM_IRT_OK)
    {
        retVal = E_OK;
    }

    return retVal;
}
#endif /* (DEM_MONITORDATA_SUPPORT == STD_ON) */

/****************************************************************************/
/* Function Name | Dem_SetWIRStatus                                         */
/* Description   | Sets the WIR status bit via failsafe SW-Cs.This API can  */
/*               |  only be used through the RTE and therefore no declarat- */
/*               | ion is exported via Dem.h.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId. - */
/*               |        The Event Number is configured in the DEM. Min.:  */
/*               |         1 (0:Indication of no Event or Failure) Max.:Re- */
/*               |        sult of configuration of Event Numbers in DEM (M- */
/*               |        ax is either 255 or 65535)                        */
/*               | [in] WIRStatus :                                         */
/*               |        Requested status of event related WIR-bit (regar- */
/*               |        ding to the current status of function inhibitio- */
/*               |        n)WIRStatus = TRUE -> WIR-bit shall be set to "1- */
/*               |        "WIRStatus = FALSE -> WIR-bit shall be set to "0" */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : The request is accepted                    */
/*               |        E_NOT_OK : not be accepted (e.g. disabled contro- */
/*               |        lDTCSetting) and should be repeated.              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetWIRStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( boolean, AUTOMATIC ) WIRStatus
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;

    retVal = E_NOT_OK;

    internalReturnValue = Dem_Control_SetWIRStatus( EventId, WIRStatus );

    /* Convert return value */
    switch( internalReturnValue )
    {
        case DEM_IRT_OK:
            retVal = E_OK;
            break;
        case DEM_IRT_NG:
            /* No Process */
            break;
        default:
            /* No Process */
            break;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_InitializeEventStatus                                */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        specific-event identifier                         */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_InitializeEventStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )             internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC )    retVal;

    retVal = E_NOT_OK;

    internalReturnValue = Dem_Control_SetInitializeEventStatus( EventId );
    if( internalReturnValue == DEM_IRT_OK )
    {
        retVal = E_OK;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_AgingEventStatus                                     */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        specific-event identifier                         */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_AgingEventStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )             internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC )    retVal;

    retVal = E_NOT_OK;

    internalReturnValue = Dem_Control_SetAgingEventStatus( EventId );
    if( internalReturnValue == DEM_IRT_OK )
    {
        retVal = E_OK;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_NormalizeEventStatus                                 */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId    : Event identifier.                      */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Operation was successful.              */
/*               |        E_NOT_OK : Operation failed.                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_NormalizeEventStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )          internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;

    retVal = E_NOT_OK;

    internalReturnValue = Dem_Control_SetNormalizeEventStatus( EventId );
    if( internalReturnValue == DEM_IRT_OK )
    {
        retVal = E_OK;
    }

    return retVal;
}

#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_PrestoreFreezeFrame                                  */
/* Description   | Prestore freezeframe.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId    : Event identifier.                      */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Operation was successful.              */
/*               |        E_NOT_OK : Operation failed.                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_PrestoreFreezeFrame
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )          internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;

    retVal = E_NOT_OK;

    internalReturnValue = Dem_Control_PrestoreFreezeFrame( EventId );
    if( internalReturnValue == DEM_IRT_OK )
    {
        retVal = E_OK;
    }

    return retVal;
}
#endif  /* - DEM_FF_PRESTORAGE_SUPPORT == STD_ON -  */

#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_ClearPrestoredFreezeFrame                            */
/* Description   | Clear prestored freezeframe.                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId    : Event identifier.                      */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Operation was successful.              */
/*               |        E_NOT_OK : Operation failed.                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_ClearPrestoredFreezeFrame
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )          internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;

    retVal = E_NOT_OK;

    internalReturnValue = Dem_Control_ClearPrestoredFreezeFrame( EventId );
    if( internalReturnValue == DEM_IRT_OK )
    {
        retVal = E_OK;
    }

    return retVal;
}
#endif  /* - DEM_FF_PRESTORAGE_SUPPORT == STD_ON -  */


#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_ResetEventUdsStatusHistory                           */
/* Description   | Reset the statusofDTC history of an event.               */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [in] UDSStatusHistoryByte :                              */
/*               |        UDS DTC status history.                           */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : successful                                 */
/*               |        E_NOT_OK : failed                                 */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_ResetEventUdsStatusHistory
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( Dem_UdsStatusHistoryByteType, AUTOMATIC ) UDSStatusHistoryByte
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;

    retVal = E_NOT_OK;

    internalReturnValue = Dem_Control_ResetEventUdsStatusHistory( EventId , UDSStatusHistoryByte );

    /* Convert return value */
    if ( internalReturnValue == DEM_IRT_OK )
    {
        retVal = E_OK;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_SetEventUdsStatusHistory                             */
/* Description   | Set the statusofDTC history of an event.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [in] UDSStatusHistoryByte :                              */
/*               |        UDS DTC status history.                           */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : successful                                 */
/*               |        E_NOT_OK : failed                                 */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetEventUdsStatusHistory
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( Dem_UdsStatusHistoryByteType, AUTOMATIC ) UDSStatusHistoryByte
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;

    retVal = E_NOT_OK;

    internalReturnValue = Dem_Control_SetEventUdsStatusHistory( EventId , UDSStatusHistoryByte );

    /* Convert return value */
    if ( internalReturnValue == DEM_IRT_OK )
    {
        retVal = E_OK;
    }

    return retVal;
}
#endif /* (DEM_PID_READINESS_SUPPORT == STD_ON) */

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_SetSpecificEventStatus                               */
/* Description   | Set Specific event status.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId     : Event identifier.                     */
/*               | [in] EventStatus : Monitor test result.                  */
/*               | [in] SpecificConditionPtr : Specific condition of event. */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Operation was successful.              */
/*               |        E_NOT_OK : Operation failed.                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetSpecificEventStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    P2CONST( Dem_SpecificEventConditionType, AUTOMATIC, DEM_APPL_DATA ) SpecificConditionPtr
)
{
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;

    retVal = E_NOT_OK;

    if( SpecificConditionPtr != NULL_PTR )
    {
        /* Queues the SpecificEventStatus */
        internalReturnValue = Dem_Control_SetSpecificEventStatus( EventId, EventStatus, SpecificConditionPtr );

        /* Converts return value */
        if( internalReturnValue == DEM_IRT_OK )
        {
            retVal = E_OK;
        }
    }

    return retVal;
}
#endif /* DEM_SPECIFIC_EVENT_SUPPORT -STD_ON- */

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_SetEventFailedWithSyncFreezeFrame                    */
/* Description   | set event failed with freezeframe.                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK :     successful                             */
/*               |        DEM_E_ACCESS_PROCESSING : failed(retry possible). */
/*               |        DEM_E_MEMORY_OVERFLOW : failed(memory full).      */
/*               |        E_NOT_OK : failed(retry not possible).            */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetEventFailedWithSyncFreezeFrame
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;

    retVal = E_NOT_OK;

    internalReturnValue = Dem_Control_SetEventFailedWithSyncFreezeFrame( EventId );

    /* Convert return value */
    switch( internalReturnValue )
    {
        case DEM_IRT_OK:
            retVal = E_OK;
            break;
        case DEM_IRT_BUSY:
            retVal = DEM_E_ACCESS_PROCESSING;
            break;
        case DEM_IRT_MEMORY_OVERFLOW:
            retVal = DEM_E_MEMORY_OVERFLOW;
            break;
        case DEM_IRT_NG:
            /* No Process */
            break;
        default:
            /* No Process */
            break;
    }

    return retVal;
}

#endif /* (DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
