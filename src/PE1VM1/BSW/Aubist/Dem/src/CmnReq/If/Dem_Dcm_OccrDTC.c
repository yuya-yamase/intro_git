/* Dem_Dcm_c(v5-5-0)                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dcm/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem_Dcm.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_CmnIf_Control.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"

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
/* Function Name | Dem_DcmControlDTCStatusChangedNotification               */
/* Description   | Controls the triggering of Dcm_DemTriggerOnDTCStatus.    */
/* Preconditions | none                                                     */
/* Parameters    | [in] TriggerNotification :                               */
/*               |        This parameter specifies whether the triggering   */
/*               |        of the notification shall be enabled (TRUE) or    */
/*               |        disabled (FALSE).                                 */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DcmControlDTCStatusChangedNotification
(
    VAR( boolean, AUTOMATIC ) TriggerNotification    /* MISRA DEVIATION */
)
{
#if ( DEM_TRIGGER_DCM_REPORTS == STD_ON )   /*  [FuncSw]    */
    Dem_Control_DTCStatusChangedNotification( TriggerNotification );
#endif  /*   ( DEM_TRIGGER_DCM_REPORTS == STD_ON )          */

    return;
}


/****************************************************************************/
/* Function Name | Dem_DcmGetDTCByOccurrenceTime                            */
/* Description   | Gets the DTC by occurrence time. There is no explicit    */
/*               | parameter for the DTC-origin as the origin always is     */
/*               | DEM_DTC_ORIGIN_PRIMARY_MEMORY.                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCRequest :                                        */
/*               |        This parameter defines the request type of the    */
/*               |        DTC.                                              */
/*               | [out] DTCValue :                                         */
/*               |        Receives the DTC value in UDS format returned by  */
/*               |        the function. If the return value of the function */
/*               |        is other than DEM_OCCURR_OK this parameter does   */
/*               |        not contain valid data.                           */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK: get of DTC was successful                   */
/*               |        E_NOT_OK: the call was not successful             */
/*               |        DEM_NO_SUCH_ELEMENT: The requested element is not */
/*               |                             stored                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmGetDTCByOccurrenceTime
(
    VAR( Dem_DTCRequestType, AUTOMATIC ) DTCRequest,        /* MISRA DEVIATION */
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) DTCValue      /* MISRA DEVIATION */
)
{
#if ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )   /*  [FuncSw]    */
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) dtcvalue;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
#endif  /* ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )            */

    VAR( Std_ReturnType, AUTOMATIC ) retVal;

    retVal = E_NOT_OK;

#if ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )   /*  [FuncSw]    */
    if( DTCValue != NULL_PTR )
    {
        dtcvalue = (Dem_u32_DTCValueType)0U;                      /*  out parameter.  */
        internalReturnValue = Dem_Control_GetDTCByOccurrenceTime( DTCRequest, &dtcvalue );

        /* Convert return value */
        switch( internalReturnValue )
        {
            case DEM_IRT_OK:
                *DTCValue = dtcvalue;               /*  set value to out parameter. */
                retVal = E_OK;
                break;
            case DEM_IRT_NO_MATCHING_ELEMENT:
                retVal = DEM_NO_SUCH_ELEMENT;
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
#endif  /* ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )            */

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
