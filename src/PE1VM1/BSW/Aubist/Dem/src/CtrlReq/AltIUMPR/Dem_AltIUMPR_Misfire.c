/* Dem_AltIUMPR_Misfire_c(v5-6-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/AltIUMPR_Misfire/CODE                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_Misfire_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_AltIUMPR.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Rc_AltIUMPRMng.h"
#include "../../../inc/Dem_Rc_MisfireMng.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Internal Functions                                                       */
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

static VAR( Dem_MisfireCylinderType, DEM_VAR_NO_INIT ) Dem_AltIUMPROldBit6Cylinder;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_AltIUMPR_ReadMonitorActivityDataForCylinder          */
/* Description   | Get current failed cylinder.                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex   : Event index.                     */
/*               | [out] CylinderPtr : Cylinder status.                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AltIUMPR_ReadMonitorActivityDataForCylinder
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) NumeratorPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) RatioPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNumber;

    retVal = DEM_IRT_NG;

    misfireCylinderNumber = Dem_CfgInfoPm_GetMisfireCylinderNumberByUdsDTC( DTCValue );

    if( misfireCylinderNumber != DEM_MISFIRE_CYL_NUM_INVALID )
    {
        retVal = Dem_AltIUMPRMng_GetNumeratorAndRatioForCylinder( misfireCylinderNumber, NumeratorPtr, RatioPtr );
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_AltIUMPR_PrepareIncNumeratorCountsForCylinder        */
/* Description   | Preparation for numerator Increment                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex   : Event index.                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_AltIUMPR_PrepareIncNumeratorCountsForCylinder
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) retFirstIndex;
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind;

    retFirstIndex =   Dem_CfgInfoPm_CheckMisfireEventFirstIndex( EventStrgIndex );

    if( retFirstIndex == (boolean)TRUE )
    {
        availableMisfireKind    =   Dem_DataAvl_GetMisfireCylDTCAvailable();
        Dem_AltIUMPROldBit6Cylinder = Dem_Misfire_GetBit6Cylinder( availableMisfireKind );
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_AltIUMPR_IncNumeratorCountsForCylinder               */
/* Description   | Increment Numerator Counts For Cylinder.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex   : Event index.                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]AltIUMPR                                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_AltIUMPR_IncNumeratorCountsForCylinder
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) retLastIndex;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderCnt;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) checkCylinderBit6;

    retLastIndex =   Dem_CfgInfoPm_CheckMisfireEventLastIndex( EventStrgIndex );

    if( retLastIndex == (boolean)TRUE )
    {
        misfireCylinderNum = Dem_MisfireCylinderNum;

        for( misfireCylinderCnt = (Dem_MisfireCylinderNumberType)0U; misfireCylinderCnt < misfireCylinderNum; misfireCylinderCnt++ )
        {
            checkCylinderBit6 = Dem_AltIUMPROldBit6Cylinder & (Dem_MisfireCylinderType)(DEM_MISFIRE_CHECK_CYLINDER_BIT << misfireCylinderCnt);
            /* Check Status of DTC bit6 OFF */
            if( checkCylinderBit6 == DEM_MISFIRE_CYLINDER_NON )
            {
                Dem_AltIUMPRMng_IncNumeratorCountsForCylinder( misfireCylinderCnt );/* [UpdRec]AltIUMPR */
            }
        }
    }

    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
#endif /* ( DEM_ALTIUMPR_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
