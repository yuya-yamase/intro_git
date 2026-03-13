/* Dem_Control_FilteredDTC_ReadinessGrp_c(v5-10-0)                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_FilteredDTC_ReadinessGrp/CODE                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "Dem_Control_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
static VAR( uint16, DEM_VAR_NO_INIT )  Dem_NumberOfFilteredDTCForReadiness;
#endif /*  ( DEM_PID_READINESS_SUPPORT == STD_ON )  */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_SetDTCFilterForReadiness                     */
/* Description   | Sets filter of ReadinessGroup.                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] ReadinessGroupId :                                  */
/*               |        Defines the Readiness group for DTC filter        */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Filter was accepted                  */
/*               |        DEM_IRT_NG : Wrong filter selected                */
/*               |        DEM_IRT_WRONG_CONDITION : Wrong condition         */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-8-0      | no branch changed.                                       */
/*   v5-10-0     | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetDTCFilterForReadiness
(
    VAR( Dem_u08_ReadinessGroupIdType, AUTOMATIC ) ReadinessGroupId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckStatus;

    retCheckStatus = Dem_Control_ChkAfterCompleteInit();
    if( retCheckStatus == DEM_IRT_OK )
    {
        Dem_NumberOfFilteredDTCForReadiness = ((uint16)0x0000U);
        retVal = Dem_DTC_SetDTCFilterForReadiness( ReadinessGroupId );
    }
    else
    {
        retVal = DEM_IRT_WRONG_CONDITION;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_GetNumberOfFilteredDTCForReadiness           */
/* Description   | Gets the number of a filtered DTC.                       */
/* Preconditions | none                                                     */
/* Parameters    | [out] NumberOfFilteredDTCForReadinessPtr :               */
/*               |        The number of DTCs matching the defined filter.   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Getting number of filtered DTCs was  */
/*               |         successful.                                      */
/*               |        DEM_IRT_NG : Getting number of filtered DTCs fai- */
/*               |        led.                                              */
/*               |        DEM_IRT_PENDING : The requested values is calcul- */
/*               |        ated asynchronously and currently not available.  */
/*               |         The caller can retry later.                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-8-0      | new created. based on Dem_Control_GetNumberOfFilteredDTC().*/
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetNumberOfFilteredDTCForReadiness
(
    P2VAR( uint16, AUTOMATIC, AUTOMATIC ) NumberOfFilteredDTCForReadinessPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( boolean, AUTOMATIC ) loopEnd;
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) ret_DtcVal;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) ret_DtcStatus;

    retVal = DEM_IRT_NG;

    loopEnd = (boolean)FALSE;
    ret_DtcStatus = (Dem_UdsStatusByteType)0U;
    ret_DtcVal = (Dem_u32_DTCValueType)0U;

    while( loopEnd == (boolean)FALSE )
    {
        internalReturnValue = Dem_DTC_GetNextFilteredDTCForReadiness( &ret_DtcVal , &ret_DtcStatus );

        switch( internalReturnValue )
        {
            case DEM_IRT_OK:
                Dem_NumberOfFilteredDTCForReadiness = Dem_NumberOfFilteredDTCForReadiness + (uint16)1U;
                break;
            case DEM_IRT_NO_MATCHING_ELEMENT:
                /* Loop End , Processing completion                         */
                loopEnd = (boolean)TRUE;
                *NumberOfFilteredDTCForReadinessPtr = Dem_NumberOfFilteredDTCForReadiness;  /*  set value to out parameter. */

                Dem_DTC_RestartSetDTCFilterForReadiness();                                  /*  reset data for restart.     */
                Dem_NumberOfFilteredDTCForReadiness = ((uint16)0x0000U);

                retVal = DEM_IRT_OK;
                break;
            case DEM_IRT_PENDING:
                /* Loop End , Pending                                       */
                loopEnd = (boolean)TRUE;
                retVal = DEM_IRT_PENDING;
                break;
            default:
                /* Loop End , Illegal Return Value                          */
                loopEnd = (boolean)TRUE;
                break;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_GetNextFilteredDTCForReadiness               */
/* Description   | Gets the next filtered DTC which match the filter crite- */
/*               | ria.                                                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] DTCValuePtr :                                      */
/*               |        Receives the DTC value in respective format of t- */
/*               |        he filter returned by this function               */
/*               | [out] DTCStatusPtr :                                     */
/*               |        receives the status information of the requested  */
/*               |        DTC                                               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Returned next filtered element       */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No further element  */
/*               |         (matching the filter criteria) found             */
/*               |        DEM_IRT_PENDING : The requested value is calcula- */
/*               |        ting.                                             */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-8-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetNextFilteredDTCForReadiness
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /*--------------------------------------------------------------------------*/
    /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
    /* These are the reasons why this function needs to get exclusive.          */
    /*  - This function call [DataMng] function directory.                      */
    /*  - This function called from SW-C/Dcm context.                           */
    /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
    SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
    SchM_Exit_Dem_EventMemory();
    /*--------------------------------------------------------------------------*/
    retVal = Dem_DTC_GetNextFilteredDTCForReadiness( DTCValuePtr, DTCStatusPtr );

    return retVal;
}
#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
