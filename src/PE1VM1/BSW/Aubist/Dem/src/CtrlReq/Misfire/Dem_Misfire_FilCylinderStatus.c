/* Dem_Misfire_GetCylinder_c(v5-8-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Misfire_GetCylinder/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_DTC_DTCStatus.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Rc_MisfireMng.h"
#include "Dem_Misfire_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_MISFIRE_CYLINDER_SEARCH_START_POS_CYLINDER_1    ((Dem_MisfireCylinderNumberType)1U)

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

static VAR( Dem_MisfireCylinderNumberType, DEM_VAR_NO_INIT )   Dem_MisfireCylinderSearchCylinderNum;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Misfire_SetFilteredDTCForCylinderForEDR              */
/* Description   | The function set the Misfire DTC filter For Cylinder.    */
/* Preconditions |                                                          */
/* Parameters    | [in] ExtendedDataNumber :                                */
/*               |        Identification/Number of requested extended data  */
/*               |        record.                                           */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-8-0      | new created. based on Dem_Misfire_SetFilteredDTCForCylinder(v5-5-0). */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_SetFilteredDTCForCylinderForEDR
(
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber
)
{
    VAR( Dem_u08_MisfireFilteredEDRType, AUTOMATIC ) misfireFilteredEDRN92;

    Dem_MisfireCylinderSearchCylinderNum = ( Dem_MisfireCylinderNumberType )0U;

    if( ExtendedDataNumber == DEM_EDR_RECNUM_92 )
    {
        misfireFilteredEDRN92 = Dem_MisfireFilteredEDRN92;
        if( misfireFilteredEDRN92 == DEM_MF_RM_CYL_NOT_OUTPUT )
        {
            Dem_MisfireCylinderSearchCylinderNum = DEM_MISFIRE_CYLINDER_SEARCH_START_POS_CYLINDER_1;
        }
    }

    return;
}


#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Misfire_SetFilteredDTCForCylinderForReadiness        */
/* Description   | The function set the Misfire DTC filter For Cylinder.    */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-8-0      | rename from Dem_Misfire_SetFilteredDTCForCylinder(v5-5-0). */
/*   v5-8-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_SetFilteredDTCForCylinderForReadiness
(void)
{
    Dem_MisfireCylinderSearchCylinderNum = ( Dem_MisfireCylinderNumberType )0U;
    return;
}
#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON )    */


/****************************************************************************/
/* Function Name | Dem_Misfire_GetNextFilterdDTCForCylinder                 */
/* Description   | Gets the next filtered Cylinder DTC and its DTC status.  */
/* Preconditions | Dem_DTC_SetDTCFilterForCylinder being executed.          */
/* Parameters    | [out] DTCValuePtr :                                      */
/*               |        Receives the Cylinder DTC value in respective     */
/*               |        format of the filter returned by this function    */
/*               | [out] DTCStatusPtr :                                     */
/*               |        receives the status information of the requested  */
/*               |        Cylinder DTC                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Returned next filtered element       */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No further element  */
/*               |         (matching the filter criteria) found             */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_GetNextFilterdDTCForCylinder
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) dtcValue;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireSearchCylinderNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) retDTCClerTarget;

    retVal = DEM_IRT_NO_MATCHING_ELEMENT;
    misfireCylinderNum = Dem_MisfireCylinderNum;
    misfireSearchCylinderNum = Dem_MisfireCylinderSearchCylinderNum;

    if( misfireSearchCylinderNum < misfireCylinderNum )
    {
        dtcValue = Dem_CfgInfoPm_GetUdsDTCByMisfireCylinderNumber( misfireSearchCylinderNum );

        retDTCClerTarget = Dem_Misfire_JudgeDTCClearTarget();
        if( retDTCClerTarget == (boolean)FALSE )
        {
            statusOfDTC = Dem_Misfire_GetCylinderDTCStatus( misfireSearchCylinderNum );
        }
        else
        {
            statusOfDTC = DEM_DTCSTATUS_BYTE_DEFAULT;
        }

        *DTCValuePtr    =   dtcValue;
        *DTCStatusPtr   =   statusOfDTC;

        Dem_MisfireCylinderSearchCylinderNum = misfireSearchCylinderNum + ( Dem_MisfireCylinderNumberType )1U;
        retVal = DEM_IRT_OK;
    }

    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

