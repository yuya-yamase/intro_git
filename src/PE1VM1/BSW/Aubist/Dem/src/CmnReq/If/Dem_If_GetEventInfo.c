/* Dem_If_GetEventInfo_c(v5-5-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/If_GetEventInfo/CODE                                  */
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
/* Function Name | Dem_GetDTCOfEvent                                        */
/* Description   | Gets the DTC of an event.                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [in] DTCFormat :                                         */
/*               |        Defines the output-format of the requested DTC v- */
/*               |        alue.                                             */
/*               | [out] DTCOfEvent :                                       */
/*               |        Receives the DTC value in respective format retu- */
/*               |        rned by this function. If the return value of th- */
/*               |        e function is other than E_OK this parameter doe- */
/*               |        s not contain valid data.                         */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : get of DTC was successful                  */
/*               |        E_NOT_OK : the call was not successful DEM_E_NO_- */
/*               |        DTC_AVAILABLE                                     */
/*               |        DEM_E_NO_DTC_AVAILABLE : there is no DTC configu- */
/*               |        red in  the requested format                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetDTCOfEvent
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) DTCOfEvent
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) dtcvalue;

    retVal = E_NOT_OK;

    if( DTCOfEvent != NULL_PTR )
    {
        dtcvalue = (Dem_u32_DTCValueType)0U;  /*  out paramter.   */
        internalReturnValue = Dem_ControlIFCmn_GetDTCOfEvent( EventId , DTCFormat , &dtcvalue );

        /* Convert return value */
        switch( internalReturnValue )
        {
            case DEM_IRT_OK:
                *DTCOfEvent = dtcvalue; /*  set value to out parameter. */
                retVal = E_OK;
                break;
            case DEM_IRT_NG:
                /* No Process */
                break;
            case DEM_IRT_NODATAAVAILABLE:
                retVal = DEM_E_NO_DTC_AVAILABLE;
                break;
            default:
                /* No Process */
                break;
        }
    }
    else
    {
        /* No Process */
    }

    return retVal;
}

#if ( DEM_OBD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_GetEventKind                                         */
/* Description   | Get the EventKind of specified event.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        Identification of an event by assigned EventId    */
/*               | [out] EventKindPtr :                                     */
/*               |        Pointer to the area to get Event Kind.            */
/*               | [out] DTCClassPtr :                                      */
/*               |        Pointer to the area to get DTCClass.              */
/*               | [out] IsMILIndicatorPtr :                                */
/*               |        Pointer to the area to get MIL flag exist.        */
/*               |        When it Event Use "MIL" Ind, TRUE is set.         */
/*               |        When it Event no Use "MIL"Ind, FALSE is set.      */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetEventKind
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_EventKindType, AUTOMATIC, DEM_APPL_DATA ) EventKindPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, DEM_APPL_DATA ) DTCClassPtr,
    P2VAR( boolean, AUTOMATIC, DEM_APPL_DATA ) IsMILIndicatorPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalRetVal;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;
    VAR( Dem_DTCSeverityType, AUTOMATIC ) dtcClass;
    VAR( boolean, AUTOMATIC ) isMilInd;

    retVal = E_NOT_OK;

    if( EventKindPtr == NULL_PTR )
    {
        /* No Process */
    }
    else if( IsMILIndicatorPtr == NULL_PTR )
    {
        /* No Process */
    }
    else if( DTCClassPtr == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        eventKind   = DEM_EVTKIND_TYPE_NON_OBD_EVENT;
        dtcClass    = DEM_DTC_CLASS_0;
        isMilInd    = (boolean)FALSE;

        internalRetVal = Dem_Control_GetEventKind( EventId, &eventKind, &dtcClass, &isMilInd );
        if( internalRetVal == DEM_IRT_OK )
        {
            *EventKindPtr = eventKind;
            *DTCClassPtr  = dtcClass;
            *IsMILIndicatorPtr = isMilInd;
            retVal = E_OK;
        }
    }

    return retVal;
}
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_GetUserDefinedMemoryIdentifier                       */
/* Description   | Returns the number of entries currently stored in the r- */
/*               | equested event memory.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [out] MemoryIdentifierPtr :                              */
/*               |        Number of entries currently stored in the reques- */
/*               |        ted event memory.                                 */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetUserDefinedMemoryIdentifier
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) MemoryIdentifierPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( uint8, AUTOMATIC ) memId;

    retVal = E_NOT_OK;

    if( MemoryIdentifierPtr != NULL_PTR )
    {
        memId = (uint8)0U; /*  out paramter.   */
        internalReturnValue = Dem_ControlIFCmn_GetUserDefinedMemoryIdentifier( EventId , &memId );

        /* Convert return value */
        switch( internalReturnValue )
        {
            case DEM_IRT_OK:
                *MemoryIdentifierPtr = (uint8)memId;   /*  set value to out parameter. */
                retVal = E_OK;
                break;
            case DEM_IRT_NG:
                /* No Process */
                break;
            default:
                /* No Process */
                break;
        }
    }
    else
    {
        /* No Process */
    }

    return retVal;
}
#endif /* (DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON) */

/****************************************************************************/
/* Function Name | Dem_GetEventFailureCycleCounterThreshold                 */
/* Description   | Gets FailureCycleCounterThreshold in RAM-Data.           */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID : event identifier                          */
/*               | [out] FailureCycleCounterThresholdPtr :                  */
/*               |        counter values of FailureCycleCounterThreshold    */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_SetEventFailureCycleCounterThreshold. */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetEventFailureCycleCounterThreshold
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) FailureCycleCounterThresholdPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_u08_FailureCounterType, AUTOMATIC ) failureCycleCounterThreshold;
    VAR( Std_ReturnType, AUTOMATIC )    retVal;

    retVal = E_NOT_OK;

    if( FailureCycleCounterThresholdPtr != NULL_PTR )
    {
        failureCycleCounterThreshold    =   (Dem_u08_FailureCounterType)0U;
        internalReturnValue = Dem_Control_GetEventFailureCycleCounterThreshold( EventId, &failureCycleCounterThreshold );
        if( internalReturnValue == DEM_IRT_OK )
        {
            *FailureCycleCounterThresholdPtr    =   failureCycleCounterThreshold;
            retVal = E_OK;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_GetNumberOfEventMemoryEntries                        */
/* Description   | Returns the number of entries currently stored in the r- */
/*               | equested event memory.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCOrigin :                                         */
/*               |        If the Dem supports more than one event memory t- */
/*               |        his parameter is used to select the source memor- */
/*               |        y the number of entries shall be read from.       */
/*               | [out] NumberOfEventMemoryEntries :                       */
/*               |        Number of entries currently stored in the reques- */
/*               |        ted event memory.                                 */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetNumberOfEventMemoryEntries
(
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) NumberOfEventMemoryEntries
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) number;

    retVal = E_NOT_OK;

    if( NumberOfEventMemoryEntries != NULL_PTR )
    {
        number = (uint8)0U; /*  out paramter.   */
        internalReturnValue = Dem_ControlIFCmn_GetNumberOfEventMemoryEntries( DTCOrigin , &number );

        /* Convert return value */
        switch( internalReturnValue )
        {
            case DEM_IRT_OK:
                *NumberOfEventMemoryEntries = (uint8)number;   /*  set value to out parameter. */
                retVal = E_OK;
                break;
            case DEM_IRT_NG:
                /* No Process */
                break;
            default:
                /* No Process */
                break;
        }
    }
    else
    {
        /* No Process */
    }

    return retVal;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_GetRecordInfoByNvMBlockId                            */
/* Description   | Get record information by NvM block Id.                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        Identification of an event by assigned EventId    */
/*               | [out] RecordKindPtr :                                    */
/*               |        Pointer to the area to get record kind.           */
/*               | [out] EventIdPtr :                                       */
/*               |        Pointer to the area to get eventid.               */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetRecordInfoByNvMBlockId
(
    VAR( Dem_BlockIdType, AUTOMATIC ) BlockId,
    P2VAR( Dem_RecordKindType, AUTOMATIC, DEM_APPL_DATA ) RecordKindPtr,
    P2VAR( Dem_EventIdType, AUTOMATIC, DEM_APPL_DATA ) EventIdPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalRetVal;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_RecordKindType, AUTOMATIC ) recordKind;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

    retVal = E_NOT_OK;

    if( RecordKindPtr == NULL_PTR )
    {
        /* No Process */
    }
    else
    if( EventIdPtr == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        recordKind  =   DEM_RECORDKIND_INVALID;
        eventId     =   DEM_EVENTID_INVALID;
        internalRetVal = Dem_ControlIFCmn_GetRecordInfoByNvMBlockId( BlockId, &recordKind, &eventId );
        if( internalRetVal == DEM_IRT_OK )
        {
            *RecordKindPtr  = recordKind;
            *EventIdPtr     = eventId;
            retVal = E_OK;
        }
    }

    return retVal;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
