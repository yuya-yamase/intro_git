/* Dem_Similar_EventEntry_local_h(v5-3-0)                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Similar_EventEntry_local/HEADER                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_SIMILAR_EVENTENTRY_LOCAL_H
#define DEM_SIMILAR_EVENTENTRY_LOCAL_H

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Saved temporary area of event memory entry */
typedef struct {
    Dem_SimilarRecordType         SimilarRecord;
    Dem_u08_InternalReturnType    ResultOfComparingSimilarRecords;
} Dem_TmpSimilarEventMemoryEntryType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------*/
/*  Dem_Similar_EventEntryMake          */
/*--------------------------------------*/
FUNC( void, DEM_CODE ) Dem_Similar_SetPendingEraseCycCounterToTmp
(
    VAR( Dem_u08_SimilarPendingClearCounterType, AUTOMATIC ) PendingEraseCycCounter
);
FUNC( void, DEM_CODE ) Dem_Similar_SetExceedanceCounterToTmp
(
    VAR( Dem_u08_SimilarExceedanceCounterType, AUTOMATIC ) ExceedanceCounter
);
FUNC( void, DEM_CODE ) Dem_Similar_SetSimilarPassedThisDcyToTmp
(
    VAR( boolean, AUTOMATIC ) SimilarPassedThisDcy
);
FUNC( void, DEM_CODE ) Dem_Similar_UpdateSimilarConditionStoredListToTmp
(void);
FUNC( void, DEM_CODE ) Dem_Similar_GetConditionStoredListToTmp
(
    P2VAR( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) SimilarConditionPtr
);
FUNC( void, DEM_CODE ) Dem_Similar_ClearSimilarConditionLatchedToTmp
(void);
FUNC( void, DEM_CODE ) Dem_Similar_SetConditionStoredflgToTmp
(
    VAR( boolean, AUTOMATIC ) SimilarConditionStoredflg
);
FUNC( void, DEM_CODE ) Dem_Similar_GetPendingEraseCycCounterToTmp
(
    P2VAR( Dem_u08_SimilarPendingClearCounterType, AUTOMATIC, AUTOMATIC ) PendingEraseCycCounterPtr
);
FUNC( void, DEM_CODE ) Dem_Similar_GetSimilarPassedThisDcyToTmp
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) SimilarPassedThisDcyPtr
);
FUNC( void, DEM_CODE ) Dem_Similar_SetConditionStoreBeforeDcyToTmp
(
    VAR( boolean, AUTOMATIC ) SimilarConditionStoreBeforeDcy
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Saved temporary area of event memory entry                               */
/****************************************************************************/
extern VAR( Dem_TmpSimilarEventMemoryEntryType, DEM_VAR_NO_INIT ) Dem_TmpSimilarEventMemoryEntry;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#endif /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) */

#endif /* DEM_SIMILAR_EVENTENTRY_LOCAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
