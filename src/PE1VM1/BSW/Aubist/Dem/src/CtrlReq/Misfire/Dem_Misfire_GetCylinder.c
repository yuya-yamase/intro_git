/* Dem_Misfire_GetCylinder_c(v5-3-0)                                        */
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
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Rc_MisfireMng.h"
#include "Dem_Misfire_local.h"

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


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Misfire_GetCurrentFailedCylinder                     */
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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_GetCurrentFailedCylinder
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_MisfireCylinderStatusType, AUTOMATIC, AUTOMATIC ) CylinderPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;

    retVal = DEM_IRT_NG;

    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );
    if( misfireEventKind == (boolean)TRUE )
    {
        /*  convert id.     */
        retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex );

        if ( retCnvId == DEM_IRT_OK )
        {
            *CylinderPtr = (Dem_MisfireCylinderStatusType)Dem_MisfireMng_GetFailedCyl( misfireIndex );
            *CylinderPtr = Dem_CfgInfoPm_MergeMultipleCylinderBit( *CylinderPtr );
            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_GetFailedCylinderAtThisOC                    */
/* Description   | Get accumulate failed cylinder at this operation cycle.  */
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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_GetFailedCylinderAtThisOC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_MisfireCylinderStatusType, AUTOMATIC, AUTOMATIC ) CylinderPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;

    retVal = DEM_IRT_NG;

    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );
    if( misfireEventKind == (boolean)TRUE )
    {
        /*  convert id.     */
        retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex );

        if ( retCnvId == DEM_IRT_OK )
        {
            *CylinderPtr = (Dem_MisfireCylinderStatusType)Dem_MisfireMng_GetAFCylThisOC( misfireIndex );
            *CylinderPtr = Dem_CfgInfoPm_MergeMultipleCylinderBit( *CylinderPtr );
            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_GetFailedCylinderSinceLastClear              */
/* Description   | Get accumulate failed cylinder since last clear.         */
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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_GetFailedCylinderSinceLastClear
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_MisfireCylinderStatusType, AUTOMATIC, AUTOMATIC ) CylinderPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;

    retVal = DEM_IRT_NG;

    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );
    if( misfireEventKind == (boolean)TRUE )
    {
        /*  convert id.     */
        retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex );

        if ( retCnvId == DEM_IRT_OK )
        {
            *CylinderPtr = (Dem_MisfireCylinderStatusType)Dem_MisfireMng_GetAFCySinceClear( misfireIndex );
            *CylinderPtr = Dem_CfgInfoPm_MergeMultipleCylinderBit( *CylinderPtr );
            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_GetFailedCylinder                            */
/* Description   | Get accumulate failed cylinder.                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex  : Event index.                      */
/*               | [out] CylinderPtr : Cylinder status.                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_GetFailedCylinder
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_MisfireCylinderStatusType, AUTOMATIC, AUTOMATIC ) CylinderPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;

    retVal = DEM_IRT_NG;

    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );
    if( misfireEventKind == (boolean)TRUE )
    {
        /*  convert id.     */
        retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex );

        if ( retCnvId == DEM_IRT_OK )
        {
            *CylinderPtr = (Dem_MisfireCylinderStatusType)Dem_MisfireMng_GetAccumCyl( misfireIndex );
            *CylinderPtr = Dem_CfgInfoPm_MergeMultipleCylinderBit( *CylinderPtr );
            retVal = DEM_IRT_OK;
        }
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
/****************************************************************************/

/**** End of File ***********************************************************/
