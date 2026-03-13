/* Dem_If_Specific_c(v5-9-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/If_Misfire/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_Control_Specific.h"
#include "../../../inc/Dem_Pm_Control_Misfire.h"

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

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_SetExceedanceUsedForMisfireEmission                  */
/* Description   | Set exceedanceUsed status.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] ExceedanceUsedStatus : ExceedanceUsed status.       */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Operation was successful.              */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetExceedanceUsedForMisfireEmission
(
    VAR( boolean, AUTOMATIC ) ExceedanceUsedStatus
)
{
    Dem_Control_SetExceedanceUsedForMisfireEmission( ExceedanceUsedStatus );
    return E_OK;
}
#endif /* DEM_MISFIRE_EVENT_CONFIGURED -STD_ON- */

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_GetPendingClearCounter                               */
/* Description   | Gets the current PendingClear counter of an event.       */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [out] PendingClearCounterPtr :                           */
/*               |        Pointer to the area to get counter.               */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : get of counter was successful              */
/*               |        E_NOT_OK : get of counter failed                  */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_GetAgingCounter.               */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetPendingClearCounter
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PendingClearCounterPtr
)
{
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_u08_SimilarPendingClearCounterType, AUTOMATIC ) pendingClearCounter;

    retVal = E_NOT_OK;

    if( PendingClearCounterPtr != NULL_PTR )
    {
        pendingClearCounter = 0U;                              /*  out paramter.   */
        internalReturnValue = Dem_Control_GetPendingClearCounter( EventId , &pendingClearCounter );
        if( internalReturnValue == DEM_IRT_OK )
        {
            *PendingClearCounterPtr = (uint8)pendingClearCounter;          /*  set value to out parameter. */
            retVal = E_OK;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_GetSimilarCondition                                  */
/* Description   | Gets the similar condition of an event.                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [out] SimilarConditionArrayPtr :                         */
/*               |        Pointer to the area to get SimilarConditions.     */
/*               | [out] SimilarConditionStatusPtr :                        */
/*               |        Pointer to the area to get SimilarConditions sta- */
/*               |        tus.                                              */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : get of similar condition was successful    */
/*               |        E_NOT_OK : get of similar condition failed        */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetSimilarCondition
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_SimilarConditionValueType, AUTOMATIC, DEM_APPL_DATA ) SimilarConditionArrayPtr,
    P2VAR( Dem_SimilarConditionStatusType, AUTOMATIC, DEM_APPL_DATA ) SimilarConditionStatusPtr
)
{
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_SimilarConditionStatusType, AUTOMATIC ) similarConditionStatus;

    retVal = E_NOT_OK;

    if( SimilarConditionArrayPtr == NULL_PTR )
    {
        /* No Process */
    }
    else if( SimilarConditionStatusPtr == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        similarConditionStatus = DEM_SIMILARCONDITION_STATUS_NO_DATA;   /*  out paramter.   */
        internalReturnValue = Dem_Control_GetSimilarCondition( EventId, SimilarConditionArrayPtr, &similarConditionStatus );
        if( internalReturnValue == DEM_IRT_OK )
        {
            *SimilarConditionStatusPtr = similarConditionStatus;        /*  set value to out parameter. */
            retVal = E_OK;
        }
    }

    return retVal;
}
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_GetExceedanceCounter                                 */
/* Description   | Gets the current ExceedanceCounter counter of an event.  */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [out] PendingClearCounterPtr :                           */
/*               |        Pointer to the area to get counter.               */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : get of counter was successful              */
/*               |        E_NOT_OK : get of counter failed                  */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_GetAgingCounter.               */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetExceedanceCounter
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) ExceedanceCounterPtr
)
{
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_u08_ExceedanceCounterType, AUTOMATIC ) exceedanceCounter;

    retVal = E_NOT_OK;

    if( ExceedanceCounterPtr != NULL_PTR )
    {
        exceedanceCounter = (Dem_u08_ExceedanceCounterType)0U;         /*  out paramter.   */
        internalReturnValue = Dem_Control_GetExceedanceCounter( EventId , &exceedanceCounter );
        if( internalReturnValue == DEM_IRT_OK )
        {
            *ExceedanceCounterPtr = (uint8)exceedanceCounter;          /*  set value to out parameter. */
            retVal = E_OK;
        }
    }

    return retVal;
}
#endif  /*  ( DEM_SPECIFIC_EVENT_SUPPORT == STD_OFF )   */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
