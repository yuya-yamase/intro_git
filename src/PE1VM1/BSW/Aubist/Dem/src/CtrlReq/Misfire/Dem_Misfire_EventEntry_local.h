/* Dem_Misfire_EventEntry_local(v5-9-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Misfire_EventEntry_local/HEADER                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_MISFIRE_EVENTENTRY_LOCAL_H
#define DEM_MISFIRE_EVENTENTRY_LOCAL_H

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )

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
    Dem_MisfireRecordType        MisfireRecord[DEM_MISFIRE_EVENT_NUM];
    Dem_MisfireComRecordType     MisfireComRecord;
    Dem_u08_InternalReturnType   ResultOfComparingMisfireRecords;
    Dem_u08_InternalReturnType   ResultOfComparingPairMisfireRecords;
    Dem_u08_InternalReturnType   ResultOfComparingMisfireComRecords;

    Dem_MisfireCylinderType      MisfireRecordBeforeAccumPendingCyl;
    Dem_MisfireCylinderType      MisfireComBeforeFirstPendingCyl;

    Dem_MisfireCylinderType      MisfireRecordBeforeAccumConfirmedCyl;
    Dem_MisfireCylinderType      MisfireComBeforeFirstConfirmedCyl;
    Dem_MisfireCylinderType      MisfireComBeforeFirstAccumConfirmedCyl;

    Dem_MisfireCylinderType      MisfireRecordBeforeAccumFailedCylSinceClear;

} Dem_TmpMisfireEventMemoryEntryType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------*/
/*  Dem_Misfire_EventEntryMake          */
/*--------------------------------------*/
FUNC( void, DEM_CODE ) Dem_Misfire_ClearFailedCylToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( void, DEM_CODE ) Dem_Misfire_ClearAccumCylToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( void, DEM_CODE ) Dem_Misfire_ClearAccumFailedCylThisOCToTmp
( void );
FUNC( void, DEM_CODE ) Dem_Misfire_ClearAccumPendingCylToTmp
( void );
FUNC( void, DEM_CODE ) Dem_Misfire_ClearAccumConfirmedCylToTmp_AtAging
( void );
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_SetFFDAccumCylinder
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
);
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Misfire_SetObdFFDCylToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) FFDCyl
);
FUNC( void, DEM_CODE ) Dem_Misfire_GetObdFFDCylToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex,
    P2VAR( Dem_MisfireCylinderType, AUTOMATIC, AUTOMATIC ) FFDCylPtr
);
#if ( DEM_OBDONUDS_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
FUNC( void, DEM_CODE ) Dem_Misfire_GetPairObdFFDCylToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex,
    P2VAR( Dem_MisfireCylinderType, AUTOMATIC, AUTOMATIC ) FFDCylPtr
);
#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON ) */
#endif /* ( DEM_OBDONUDS_SUPPORT == STD_ON ) */
FUNC( void, DEM_CODE ) Dem_Misfire_SetMisfireKindOfObdFFDToTmp
(
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex,
    VAR( Dem_u08_MisfireKindType, AUTOMATIC ) MisfireKindOfFFD
);
FUNC( void, DEM_CODE ) Dem_Misfire_GetMisfireKindOfObdFFDToTmp
(
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex,
    P2VAR( Dem_u08_MisfireKindType, AUTOMATIC, AUTOMATIC ) MisfireKindOfFFDPtr
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */
FUNC( void, DEM_CODE ) Dem_Misfire_SetFFDCylToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) MisfireFFDCylIndex,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) FFDCyl
);
FUNC( void, DEM_CODE ) Dem_Misfire_GetFFDCylToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) MisfireFFDCylIndex,
    P2VAR( Dem_MisfireCylinderType, AUTOMATIC, AUTOMATIC ) FFDCylPtr
);
FUNC( void, DEM_CODE ) Dem_Misfire_SetExceedanceCounterToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_MisfExceedanceCounterType, AUTOMATIC ) ExceedanceCounter
);
FUNC( void, DEM_CODE ) Dem_Misfire_SetFirstPendingCylToTmp
(
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) FirstPendingCyl
);
FUNC( void, DEM_CODE ) Dem_Misfire_SetFirstConfirmedCylToTmp
(
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) FirstConfirmedCyl
);
FUNC( void, DEM_CODE ) Dem_Misfire_SetFirstAccumConfirmedCylToTmp
(
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) FirstAccumConfirmedCyl
);
FUNC( void, DEM_CODE ) Dem_Misfire_SetMisfireKindOfFFDToTmp
(
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) MisfireFFDCylIndex,
    VAR( Dem_u08_MisfireKindType, AUTOMATIC ) MisfireKindOfFFD
);
FUNC( void, DEM_CODE ) Dem_Misfire_GetMisfireKindOfFFDToTmp
(
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) MisfireFFDCylIndex,
    P2VAR( Dem_u08_MisfireKindType, AUTOMATIC, AUTOMATIC ) MisfireKindOfFFDPtr
);
FUNC( void, DEM_CODE ) Dem_Misfire_UpdateFailedCylToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
);
FUNC( void, DEM_CODE ) Dem_Misfire_UpdatePendingCylinderToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
);
FUNC( void, DEM_CODE ) Dem_Misfire_UpdateConfirmedCylinderToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
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
extern VAR( Dem_TmpMisfireEventMemoryEntryType, DEM_VAR_NO_INIT ) Dem_TmpMisfireEventMemoryEntry;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

#endif /* DEM_MISFIRE_EVENTENTRY_LOCAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
