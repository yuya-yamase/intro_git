/* Dem_If_Misfire_c(v5-5-0)                                                 */
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
/* Function Name | Dem_GetCurrentFailedCylinder                             */
/* Description   | Get current failed cylinder.                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId     : Event identifier.                     */
/*               | [in] CylinderPtr : Cylinder status.                      */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Operation was successful.              */
/*               |        E_NOT_OK : Operation failed.                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetCurrentFailedCylinder
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_MisfireCylinderStatusType, AUTOMATIC, DEM_APPL_DATA ) CylinderPtr
)
{
    VAR( Dem_MisfireCylinderStatusType, AUTOMATIC ) cylinderStatus;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;

    retVal = E_NOT_OK;

    if( CylinderPtr != NULL_PTR )
    {
        internalReturnValue = Dem_Control_GetCurrentFailedCylinder( EventId, &cylinderStatus );
        /* Converts return value */
        if( internalReturnValue == DEM_IRT_OK )
        {
            *CylinderPtr = cylinderStatus;  /* set value to out parameter. */
            retVal = E_OK;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_GetFailedCylinderAtThisOC                            */
/* Description   | Get accumulate failed cylinder at this operation cycle.  */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId     : Event identifier.                     */
/*               | [in] CylinderPtr : Cylinder status.                      */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Operation was successful.              */
/*               |        E_NOT_OK : Operation failed.                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetFailedCylinderAtThisOC
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_MisfireCylinderStatusType, AUTOMATIC, DEM_APPL_DATA ) CylinderPtr
)
{
    VAR( Dem_MisfireCylinderStatusType, AUTOMATIC ) cylinderStatus;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;

    retVal = E_NOT_OK;

    if( CylinderPtr != NULL_PTR )
    {
        internalReturnValue = Dem_Control_GetFailedCylinderAtThisOC( EventId, &cylinderStatus );
        /* Converts return value */
        if( internalReturnValue == DEM_IRT_OK )
        {
            *CylinderPtr = cylinderStatus;  /* set value to out parameter. */
            retVal = E_OK;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_GetFailedCylinderSinceLastClear                      */
/* Description   | Get accumulate failed cylinder since last clear.         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId     : Event identifier.                     */
/*               | [in] CylinderPtr : Cylinder status.                      */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Operation was successful.              */
/*               |        E_NOT_OK : Operation failed.                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetFailedCylinderSinceLastClear
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_MisfireCylinderStatusType, AUTOMATIC, DEM_APPL_DATA ) CylinderPtr
)
{
    VAR( Dem_MisfireCylinderStatusType, AUTOMATIC ) cylinderStatus;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;

    retVal = E_NOT_OK;

    if( CylinderPtr != NULL_PTR )
    {
        internalReturnValue = Dem_Control_GetFailedCylinderSinceLastClear( EventId, &cylinderStatus );
        /* Converts return value */
        if( internalReturnValue == DEM_IRT_OK )
        {
            *CylinderPtr = cylinderStatus;  /* set value to out parameter. */
            retVal = E_OK;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_GetFailedCylinder                                    */
/* Description   | Get accumulate failed cylinder.                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId     : Event identifier.                     */
/*               | [in] CylinderPtr : Cylinder status.                      */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Operation was successful.              */
/*               |        E_NOT_OK : Operation failed.                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetFailedCylinder
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_MisfireCylinderStatusType, AUTOMATIC, DEM_APPL_DATA ) CylinderPtr
)
{
    VAR( Dem_MisfireCylinderStatusType, AUTOMATIC ) cylinderStatus;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;

    retVal = E_NOT_OK;

    if( CylinderPtr != NULL_PTR )
    {
        internalReturnValue = Dem_Control_GetFailedCylinder( EventId, &cylinderStatus );
        /* Converts return value */
        if( internalReturnValue == DEM_IRT_OK )
        {
            *CylinderPtr = cylinderStatus;  /* set value to out parameter. */
            retVal = E_OK;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_GetCylinderDTCStatus                                 */
/* Description   | Get current statusOfDTC of Cylinder.                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireCylinderNumber : Cylinder Number.            */
/*               | [in] UDSStatusBytePtr      : statusOfDTC of Cylinder.    */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Operation was successful.              */
/*               |        E_NOT_OK : Operation failed.                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetCylinderDTCStatus
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA ) UDSStatusBytePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) dtcStatus;

    retVal = E_NOT_OK;

    if( UDSStatusBytePtr != NULL_PTR )
    {
        dtcStatus = (Dem_UdsStatusByteType)0U;    /*  out paramter.   */
        internalReturnValue = Dem_Control_GetCylinderDTCStatus( MisfireCylinderNumber, &dtcStatus );
        if( internalReturnValue == DEM_IRT_OK )
        {
            *UDSStatusBytePtr = dtcStatus; /*  set value to out parameter. */
            retVal = E_OK;
        }
    }
    return retVal;

}

#endif /* DEM_MISFIRE_EVENT_CONFIGURED -STD_ON- */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
