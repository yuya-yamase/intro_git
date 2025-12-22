/* Dem_Pm_DataEeo_h(v5-8-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Pm_DataEeo/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_PM_DATAEEO_H
#define DEM_PM_DATAEEO_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
typedef struct {
    Dem_u08_FaultIndexType FaultIndex;
    Dem_u08_EventPriorityType  EventPriority;
    Dem_u08_EventPriorityType  OrgEventPriority;
    Dem_UdsStatusByteType   StatusOfDTC;
#if ( DEM_EVENT_DISPLACEMENT_BY_CDTC_NONOBDONLY_SUPPORT == STD_ON )
    boolean                 EventOBDKind;
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_CDTC_NONOBDONLY_SUPPORT == STD_ON )  */
}Dem_EventEntryOverwriteType;

typedef struct {
    Dem_u16_EventStrgIndexType  EventStrgIndex;
    Dem_u08_EventPriorityType   EventPriority;
    Dem_UdsStatusByteType       StatusOfDTC;
}Dem_EventEntryOverwriteFaultInfoType;
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DcEeo_Init_AfterRecordCheckComplete
(void);
FUNC( Dem_u08_FaultIndexType, DEM_CODE ) Dem_DcEeo_GetFaultIndexOfFaultRecordOverwrite
(
    P2CONST( Dem_EventEntryOverwriteFaultInfoType, AUTOMATIC, AUTOMATIC ) EventEntryOverwriteFaultInfoPtr
);
FUNC( Dem_u08_FaultIndexType, DEM_CODE ) Dem_DcEeo_GetFaultIndexOfNonOBDFFROverwrite
(
    P2CONST( Dem_EventEntryOverwriteFaultInfoType, AUTOMATIC, AUTOMATIC ) EventEntryOverwriteFaultInfoPtr
);
FUNC( void, DEM_CODE ) Dem_DcEeo_SelectNextNonOBDFFROverwrite
(void);
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( Dem_u08_FaultIndexType, DEM_CODE ) Dem_DcEeo_GetFaultIndexOfOBDFFROverwrite
(
    P2CONST( Dem_EventEntryOverwriteFaultInfoType, AUTOMATIC, AUTOMATIC ) EventEntryOverwriteFaultInfoPtr
);
FUNC( void, DEM_CODE ) Dem_DcEeo_SelectNextOBDFFROverwrite
(void);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */
FUNC( void, DEM_CODE ) Dem_DcEeo_InitializeFaultRecordOverwrite
(void);
FUNC( void, DEM_CODE ) Dem_DcEeo_InitializeNonOBDFFROverwrite
(void);
#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DcEeo_InitializeNonOBDFFROverwriteForEachTrigger
(void);
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DcEeo_InitializeOBDFFROverwrite
(void);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */
FUNC( void, DEM_CODE ) Dem_DcEeo_SelectFaultRecordOverwrite
(
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) EventEntryOverwritePtr
);
FUNC( void, DEM_CODE ) Dem_DcEeo_SelectNonOBDFFROverwrite
(
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) EventEntryOverwritePtr,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC) FreezeFrameRecordTrigger
);
#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DcEeo_DisableNonOBDFFROverwrite
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
);
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DcEeo_SelectOBDFFROverwrite
(
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) EventEntryOverwritePtr
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */
#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
FUNC( Dem_u08_FaultIndexType, DEM_CODE ) Dem_DcEeo_GetFaultIndexOfFFROverwriteFromTrigger
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) TargetTrigger,
    P2CONST( Dem_EventEntryOverwriteFaultInfoType, AUTOMATIC, AUTOMATIC ) EventEntryOverwriteFaultInfoPtr
);
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */
FUNC( Dem_u08_FaultIndexType, DEM_CODE ) Dem_DcEeo_GetFaultIndexOfLowestPriorityNonOBDDTCtoStoreFreezeFrame
( void );
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* DEM_DATAEEO_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
