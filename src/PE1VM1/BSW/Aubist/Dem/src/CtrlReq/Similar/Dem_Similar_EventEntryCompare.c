/* Dem_SimilarEventeEntryCompare_c(v5-3-0)                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Similar_EventeEntryCompare/CODE                       */
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
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Rc_SimilarMng.h"
#include "../../../inc/Dem_Pm_Similar.h"
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
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_Similar_CompareSimilarInfoToTmp                      */
/* Description   | compare similar data.                                    */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event ID for retrieving.                      */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_CompareSimilarInfoToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) similarIndex;

    retCnvId = Dem_CfgInfoPm_CnvEventStrgIndexToSimilarStrgIndex( EventStrgIndex, &similarIndex );

    if( retCnvId == DEM_IRT_OK )
    {
        Dem_TmpSimilarEventMemoryEntry.ResultOfComparingSimilarRecords = Dem_SimilarMng_CompareSimilarRecord( similarIndex, &Dem_TmpSimilarEventMemoryEntry.SimilarRecord );
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Similar_InitCompareResult                            */
/* Description   | initialize compared result of Similar record.            */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_InitCompareResult
( void )
{
    Dem_TmpSimilarEventMemoryEntry.ResultOfComparingSimilarRecords = DEM_IRT_OK;

    return;
}


/****************************************************************************/
/* Function Name | Dem_Similar_GetCompareResult                             */
/* Description   | get compared result of Similar record.                   */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event ID for retrieving.                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Similar_GetCompareResult
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfCmpSimilarRecord;
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;

    resultOfCmpSimilarRecord = DEM_IRT_OK;
    eventKind = Dem_CfgInfoPm_GetEventKindOfSpecific_InEvtStrgGrp( EventStrgIndex );

    if(( eventKind & DEM_EVTKIND_TYPE_SIMILAR_EVENT ) == DEM_EVTKIND_TYPE_SIMILAR_EVENT )
    {
        resultOfCmpSimilarRecord = Dem_TmpSimilarEventMemoryEntry.ResultOfComparingSimilarRecords;
    }

    return resultOfCmpSimilarRecord;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
