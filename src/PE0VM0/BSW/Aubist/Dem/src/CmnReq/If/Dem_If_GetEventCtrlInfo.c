/* Dem_If_GetEventCtrlInfo_c(v5-5-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
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
/* Function Name | Dem_GetEventOccurrenceCounter                            */
/* Description   | Gets the current occurrence counter of an event.         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [out] OccurrenceCounterPtr :                             */
/*               |        Pointer to the area to get occurrence counter.    */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetEventOccurrenceCounter
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) OccurrenceCounterPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_EventOccurrenceCounterType, AUTOMATIC ) occurrenceCounter;

    retVal = E_NOT_OK;

    if( OccurrenceCounterPtr != NULL_PTR )
    {
        occurrenceCounter = (Dem_u08_EventOccurrenceCounterType)0U;     /*  out paramter.   */
        internalReturnValue = Dem_Control_GetEventOccurrenceCounter( EventId , &occurrenceCounter );
        if( internalReturnValue == DEM_IRT_OK )
        {
            *OccurrenceCounterPtr = (uint8)occurrenceCounter;           /*  set value to out parameter. */
            retVal = E_OK;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_GetEventFailureCycleCounter                          */
/* Description   | Gets the current failure cycle counter of an event.      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [out] FailureCycleCounterPtr :                           */
/*               |        Pointer to the area to get failure cycle counter. */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetEventFailureCycleCounter
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) FailureCycleCounterPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_FailureCounterType, AUTOMATIC ) failureCycleCounter;

    retVal = E_NOT_OK;

    if( FailureCycleCounterPtr != NULL_PTR )
    {
        failureCycleCounter = (Dem_u08_FailureCounterType)0U;           /*  out paramter.   */
        internalReturnValue = Dem_Control_GetEventFailureCycleCounter( EventId , &failureCycleCounter );
        if( internalReturnValue == DEM_IRT_OK )
        {
            *FailureCycleCounterPtr = (uint8)failureCycleCounter;       /*  set value to out parameter. */
            retVal = E_OK;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_GetFaultOccurrenceDTCOrder                           */
/* Description   | Get the order of ConfirmedDTC.                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        Identification of an event by assigned EventId    */
/*               | [out] OrderPtr :                                         */
/*               |        Pointer to the area to get order.                 */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.based on Dem_GetConfirmedDTCOrder.           */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetFaultOccurrenceDTCOrder
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) OrderPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalRetVal;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) order;

    retVal = E_NOT_OK;

    if( OrderPtr == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        internalRetVal = Dem_Control_GetFaultOccurrenceDTCOrder( EventId, &order );
        if( internalRetVal == DEM_IRT_OK )
        {
            *OrderPtr = (uint16)order;
            retVal = E_OK;
        }
    }

    return retVal;
}

#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_GetConfirmedDTCOrder                                 */
/* Description   | Get the order of ConfirmedDTC.                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        Identification of an event by assigned EventId    */
/*               | [out] OrderPtr :                                         */
/*               |        Pointer to the area to get order.                 */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetConfirmedDTCOrder
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) OrderPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalRetVal;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) order;

    retVal = E_NOT_OK;

    if( OrderPtr == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        internalRetVal = Dem_Control_GetConfirmedDTCOrder( EventId, &order );
        if( internalRetVal == DEM_IRT_OK )
        {
            *OrderPtr = (uint16)order;
            retVal = E_OK;
        }
    }

    return retVal;
}

#endif  /* ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )    */

/****************************************************************************/
/* Function Name | Dem_GetHealingCounter                                    */
/* Description   | Gets the current healing counter of an event.            */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [out] HealingCounterPtr :                                */
/*               |        Pointer to the area to get counter.               */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : get of counter was successful              */
/*               |        E_NOT_OK : get of counter failed                  */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_GetAgingCounter.               */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetHealingCounter
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) HealingCounterPtr
)
{
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_u08_HealingCounterType, AUTOMATIC ) healingCounter;

    retVal = E_NOT_OK;

    if( HealingCounterPtr != NULL_PTR )
    {
        healingCounter = (Dem_u08_HealingCounterType)0U;    /*  out paramter.   */
        internalReturnValue = Dem_Control_GetHealingCounter( EventId , &healingCounter );
        if( internalReturnValue == DEM_IRT_OK )
        {
            *HealingCounterPtr = healingCounter;            /*  set value to out parameter. */
            retVal = E_OK;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_GetAgingCounter                                      */
/* Description   | Gets the current aging counter of an event.              */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [out] AgingCounterPtr :                                  */
/*               |        Pointer to the area to get counter.               */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : get of counter was successful              */
/*               |        E_NOT_OK : get of counter failed                  */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetAgingCounter
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) AgingCounterPtr
)
{
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_u08_AgingCounterType, AUTOMATIC ) agingCounter;

    retVal = E_NOT_OK;

    if( AgingCounterPtr != NULL_PTR )
    {
        agingCounter = (Dem_u08_AgingCounterType)0U;     /*  out paramter.   */
        internalReturnValue = Dem_Control_GetAgingCounter( EventId , &agingCounter );
        if( internalReturnValue == DEM_IRT_OK )
        {
            *AgingCounterPtr = agingCounter;            /*  set value to out parameter. */
            retVal = E_OK;
        }
    }

    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
