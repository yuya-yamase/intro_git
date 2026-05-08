/* Dem_Similar_c(v5-5-0)                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Similar/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_Similar.h"
#include "../../../inc/Dem_Rc_SimilarMng.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "Dem_Similar_local.h"
#include "Dem_Similar_EventEntry_local.h"


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
static FUNC( void, DEM_CODE ) Dem_Similar_GetExcessConterThreshold
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u08_SimilarExceedanceCounterType, AUTOMATIC, AUTOMATIC )  ExcessCntThresholdPtr
);

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
/* Function Name | Dem_Similar_CheckPassedCondition                         */
/* Description   | Check the Passed Condition.                              */
/* Preconditions | none                                                     */
/* Parameters    | [out] SimilarConditionPtr :                              */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_CheckPassedCondition
(
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) SimilarConditionPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckSimilarCond;
    VAR( boolean, AUTOMATIC ) chkGetSimilarCondStored;

    Dem_Similar_GetConditionStoredflgToTmp( &chkGetSimilarCondStored );

    if( chkGetSimilarCondStored == (boolean)TRUE )
    {
        retCheckSimilarCond = Dem_Similar_CheckConditionForPassed( SimilarConditionPtr );
        if( retCheckSimilarCond == DEM_IRT_OK )
        {
            /* Set detection flag similar condition */
            Dem_Similar_SetSimilarPassedThisDcyToTmp( (boolean)TRUE );
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Similar_CheckReachedExcessCntThresholdFromTmp        */
/* Description   | ExcessCounterThreshold exceeded judgment of the          */
/*               | temporary area.                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Similar_CheckReachedExcessCntThresholdFromTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_SimilarExceedanceCounterType, AUTOMATIC ) excessCntThreshold;
    VAR( Dem_u08_SimilarExceedanceCounterType, AUTOMATIC ) excessCounter;

    retVal = DEM_IRT_NG;

    Dem_Similar_GetExceedanceCounterToTmp( &excessCounter );

    Dem_Similar_GetExcessConterThreshold( EventStrgIndex, &excessCntThreshold );

    if ( excessCounter < excessCntThreshold )
    {
        excessCounter++;
        Dem_Similar_SetExceedanceCounterToTmp( excessCounter );
    }

    if( excessCounter >= excessCntThreshold )
    {
        retVal = DEM_IRT_OK;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Similar_CheckExceedanceUsed                          */
/* Description   | Check Similar Event exceedance use.                      */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStrgIndex                                     */
/* Return Value  | boolean                                                  */
/*               |      TRUE  : Exceedance use                              */
/*               |      FALSE : Exceedance not use                          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Similar_CheckExceedanceUsed
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( boolean, AUTOMATIC ) usedExceedance;
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) similarStrgIndex;

    usedExceedance = (boolean)FALSE;

    retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToSimilarStrgIndex( EventStrgIndex, &similarStrgIndex ); /* [GUD:RET:DEM_IRT_OK] similarStrgIndex */
    if ( retCnvId == DEM_IRT_OK )
    {
        /*  similarStrgIndex : value range check in Dem_CfgInfoPm_CnvEventStrgIndexToSimilarStrgIndex().        */
        if( Dem_SimilarClassRefTable[ similarStrgIndex ].DemExceedanceUsed == (boolean)TRUE )               /* [GUD]similarStrgIndex */
        {
            usedExceedance = (boolean)TRUE;
        }
    }

    return usedExceedance;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dem_Similar_GetExcessConterThreshold                     */
/* Description   | Get the ExcessConterThreshold of similar.                */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Parameters    | [out] ExcessCntThresholdPtr :                            */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Similar_GetExcessConterThreshold
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u08_SimilarExceedanceCounterType, AUTOMATIC, AUTOMATIC )  ExcessCntThresholdPtr
)
{
    VAR( boolean, AUTOMATIC ) usedExceedance;

    usedExceedance =  Dem_Similar_CheckExceedanceUsed( EventStrgIndex );
    if( usedExceedance == (boolean)TRUE )
    {
        *ExcessCntThresholdPtr = DEM_SIMILAR_EXCESSCONTERTHRESHOLD; /* 4 */
    }
    else
    {
        *ExcessCntThresholdPtr = DEM_SIMILAR_UNUSED_EXCESSCONTERTHRESHOLD; /* 1 */
    }

    return;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
