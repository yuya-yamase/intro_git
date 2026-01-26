/* Dem_If_GetEventList_c(v5-5-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/If_GetEventList/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
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
/* Function Name | Dem_GetEventIdWithPendingDTC                             */
/* Description   | Get eventId list.                                        */
/* Preconditions | none                                                     */
/* Parameters    | [out] EventIdBufferPtr :  EventId list.                  */
/*               | [in/out] EventIdNumPtr :  EventId list number.           */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetEventIdWithPendingDTC
(
    P2VAR( Dem_EventIdType, AUTOMATIC, DEM_APPL_DATA ) EventIdBufferPtr,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) EventIdNumPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalRetVal;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_EventIdType, AUTOMATIC ) eventIdNum;

    retVal = E_NOT_OK;

    if( EventIdBufferPtr == NULL_PTR )
    {
        /* No Process */
    }
    else if( EventIdNumPtr == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        eventIdNum      =   *EventIdNumPtr;
        internalRetVal  =   Dem_Control_GetEventIdListByFaultRecordOrder( DEM_EVTLSTMODE_PDTC, EventIdBufferPtr, &eventIdNum );
        *EventIdNumPtr  =   eventIdNum;

        if( internalRetVal == DEM_IRT_OK )
        {
            retVal = E_OK;
        }
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_GetEventIdWithActiveFaultDTC                         */
/* Description   | Get eventId list.                                        */
/* Preconditions | none                                                     */
/* Parameters    | [out] EventIdBufferPtr :  EventId list.                  */
/*               | [in/out] EventIdNumPtr :  EventId list number.           */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_GetEventIdWithPendingDTC.      */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetEventIdWithActiveFaultDTC
(
    P2VAR( Dem_EventIdType, AUTOMATIC, DEM_APPL_DATA ) EventIdBufferPtr,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) EventIdNumPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalRetVal;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_EventIdType, AUTOMATIC ) eventIdNum;

    retVal = E_NOT_OK;

    if( EventIdBufferPtr == NULL_PTR )
    {
        /* No Process */
    }
    else if( EventIdNumPtr == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        eventIdNum      =   *EventIdNumPtr;
        internalRetVal  =   Dem_Control_GetEventIdListByFaultRecordOrder( DEM_EVTLSTMODE_ACTIVEFAULT, EventIdBufferPtr, &eventIdNum );
        *EventIdNumPtr  =   eventIdNum;

        if( internalRetVal == DEM_IRT_OK )
        {
            retVal = E_OK;
        }
    }
    return retVal;
}

#if ( DEM_OBD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_GetEventIdWithConfirmedDTC                           */
/* Description   | Get eventId list.                                        */
/* Preconditions | none                                                     */
/* Parameters    | [out] EventIdBufferPtr :  EventId list.                  */
/*               | [in/out] EventIdNumPtr :  EventId list number.           */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_GetEventIdWithPendingDTC.      */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetEventIdWithConfirmedDTC
(
    P2VAR( Dem_EventIdType, AUTOMATIC, DEM_APPL_DATA ) EventIdBufferPtr,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) EventIdNumPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalRetVal;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_EventIdType, AUTOMATIC ) eventIdNum;

    retVal = E_NOT_OK;

    if( EventIdBufferPtr == NULL_PTR )
    {
        /* No Process */
    }
    else if( EventIdNumPtr == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        eventIdNum      =   *EventIdNumPtr;
        internalRetVal  =   Dem_Control_GetEventIdListByConfirmedOrder( EventIdBufferPtr, &eventIdNum );
        *EventIdNumPtr  =   eventIdNum;

        if( internalRetVal == DEM_IRT_OK )
        {
            retVal = E_OK;
        }
    }
    return retVal;
}
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
