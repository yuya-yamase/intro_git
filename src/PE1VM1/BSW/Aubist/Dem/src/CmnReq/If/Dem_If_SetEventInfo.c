/* Dem_If_SetEventInfo_c(v5-5-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/If_SetEventInfo/CODE                                  */
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

#if ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_SetEventAvailable                                    */
/* Description   | Set the available status of a specific Event.            */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [in] AvailableStatus :                                   */
/*               |        This parameter specifies whether the respective   */
/*               |        Event shall be available (TRUE) or not (FALSE).   */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful.                  */
/*               |        E_NOT_OK : Change of available status not         */
/*               |                   accepted.                              */
/*               |        DEM_E_FAILED_FIM_REPORT : Operation was successful*/
/*               |                   but failed to notify FiM of it.        */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetEventAvailable
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( boolean, AUTOMATIC ) AvailableStatus
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;

    retVal = E_NOT_OK;
    internalReturnValue = Dem_ControlIFCmn_SetEvtAvl( EventId, AvailableStatus );

    /* Convert return value */
    switch( internalReturnValue )
    {
        case DEM_IRT_OK:
            retVal = E_OK;
            break;
        case DEM_IRT_FAILED_ENQUEUE:
            retVal = DEM_E_FAILED_FIM_REPORT;
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
#endif  /* ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON ) */
#if ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_SetEventAvailable                                    */
/* Description   | Set the available status of a specific Event.            */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [in] AvailableStatus :                                   */
/*               |        This parameter specifies whether the respective   */
/*               |        Event shall be available (TRUE) or not (FALSE).   */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful.                  */
/*               |        E_NOT_OK : Change of available status not         */
/*               |                   accepted.                              */
/*               |        DEM_E_FAILED_FIM_REPORT : Operation was successful*/
/*               |                   but failed to notify FiM of it.        */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetEventAvailable
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,  /* MISRA DEVIATION */
    VAR( boolean, AUTOMATIC ) AvailableStatus   /* MISRA DEVIATION */
)
{
    return E_NOT_OK;
}
#endif  /* ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_OFF )    */

/****************************************************************************/
/* Function Name | Dem_SetEventFailureCycleCounterThreshold                 */
/* Description   | Sets FailureCycleCounterThreshold in RAM-Data.           */
/*               | This function starts a                                   */
/*               |  Dem_Control_SetEventFailureCycleCounterThreshold        */
/*               |    functionof the Dem_Data class,                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID : event identifier                          */
/*               | [in] FailureCycleCounterThreshold :                      */
/*               |        counter values of FailureCycleCounterThreshold    */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetEventFailureCycleCounterThreshold
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( uint8, AUTOMATIC ) FailureCycleCounterThreshold
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )             internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC )    retVal;

    retVal = E_NOT_OK;

    internalReturnValue = Dem_Control_SetEventFailureCycleCounterThreshold( EventId, ( Dem_u08_FailureCounterType )FailureCycleCounterThreshold );
    if( internalReturnValue == DEM_IRT_OK )
    {
        retVal = E_OK;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_ResetEventFailureCycleCounterThreshold               */
/* Description   | Reset FailureCycleCounterThreshold in RAM-Data.          */
/*               | This function starts a                                   */
/*               |  Dem_ResetEventFailureCycleCounterThreshold              */
/*               |    functionof the Dem_Data class,                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID : event identifier                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_ResetEventFailureCycleCounterThreshold
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )             internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC )    retVal;

    retVal = E_NOT_OK;

    internalReturnValue = Dem_Control_ResetEventFailureCycleCounterThreshold( EventId );
    if( internalReturnValue == DEM_IRT_OK )
    {
        retVal = E_OK;
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
