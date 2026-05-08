/* Dem_If_Indicator_c(v5-5-0)                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/If_Indicator/CODE                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_CmnIf_Control.h"

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
/* Function Name | Dem_GetIndicatorStatus                                   */
/* Description   | Gets the indicator status derived from the event status. */
/* Preconditions | none                                                     */
/* Parameters    | [in] IndicatorId :                                       */
/*               |        Number of indicator                               */
/*               | [out] IndicatorStatus                                    */
/*               |        Status of the indicator, like off, on, or blinki- */
/*               |        ng.                                               */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetIndicatorStatus
(
    VAR( uint8, AUTOMATIC ) IndicatorId,
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, DEM_APPL_DATA ) IndicatorStatus
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_IndicatorStatusType, AUTOMATIC ) indStatus;

    retVal = E_NOT_OK;

    if( IndicatorStatus != NULL_PTR )
    {
        indStatus           = DEM_INDICATOR_OFF;    /*  out parameter.  */
        internalReturnValue = Dem_Control_GetIndicatorStatus( (Dem_u08_IndicatorIdType)IndicatorId, &indStatus );

        /* Convert return value */
        switch( internalReturnValue )
        {
            case DEM_IRT_OK:
                *IndicatorStatus = indStatus;   /*  set value to out parameter. */
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


/****************************************************************************/
/* Function Name | Dem_GetIndicatorStatusByEventId                          */
/* Description   | Gets the indicator status derived from the event status. */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId     : Event identifier.                     */
/*               | [in] IndicatorId :                                       */
/*               |        Number of indicator                               */
/*               | [out] IndicatorStatusPtr                                 */
/*               |        Status of the indicator, like off, on, or blinki- */
/*               |        ng.                                               */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Operation was successful.              */
/*               |        E_NOT_OK : Operation failed.                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetIndicatorStatusByEventId
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( uint8, AUTOMATIC ) IndicatorId,
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, DEM_APPL_DATA ) IndicatorStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_IndicatorStatusType, AUTOMATIC ) indStatus;

    retVal = E_NOT_OK;

    if( IndicatorStatusPtr != NULL_PTR )
    {
        indStatus           = DEM_INDICATOR_OFF;    /*  out parameter.  */
        internalReturnValue = Dem_Control_GetIndStatusByEventId( EventId, (Dem_u08_IndicatorIdType)IndicatorId, &indStatus );

        /* Convert return value */
        switch( internalReturnValue )
        {
            case DEM_IRT_OK:
                *IndicatorStatusPtr = indStatus;   /*  set value to out parameter. */
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


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
