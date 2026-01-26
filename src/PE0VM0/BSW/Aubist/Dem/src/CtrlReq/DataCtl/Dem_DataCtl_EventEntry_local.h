/* Dem_DataCtl_EventEntry_local_h(v5-5-0)                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/DataCtl_EventEntry_local/HEADER                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_DATACTL_EVENTENTRY_LOCAL_H
#define DEM_DATACTL_EVENTENTRY_LOCAL_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_Data_Cfg.h"
#include "../../../inc/Dem_Rc_DataMng.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* Saved temporary area of event memory entry                               */
/****************************************************************************/
/* Saved temporary area of event memory entry */
typedef struct {
    Dem_EventRecordForCtlType           EventRecord;
    Dem_FaultRecordType                 FaultRecord;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
    Dem_ObdFreezeFrameRecordForCtlType  ObdFreezeFrameRecordList[DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM];
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */
    Dem_FreezeFrameRecordForCtlType     FreezeFrameRecordList[DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM];
    Dem_EventMemoryRecordType           EventMemoryRecordList;
    Dem_u16_EventStrgIndexType          EventStrgIndex;
    Dem_u08_FFValidTriggerType          Trigger;
    Dem_u08_OrderIndexType              BeforeNumberOfEventMemoryEntries;
    Dem_u08_OrderIndexType              BeforeNumberOfConfirmedDTCs;
    Dem_u08_OrderIndexType              BeforeNumberOfObdMILDTCs;
    Dem_u08_InternalReturnType          ResultOfGetFaultRegistLocation;
    Dem_u08_InternalReturnType          ResultOfGetConfirmedFaultRegistLocation;
    Dem_u08_InternalReturnType          ResultOfGetMILFaultRegistLocation;
    Dem_u08_InternalReturnType          ResultOfComparingEventRecords;
    Dem_u08_InternalReturnType          ResultOfComparingFaultRecords;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
    Dem_u08_InternalReturnType          ResultOfComparingObdFFRecords[DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM];
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */
    Dem_u08_InternalReturnType          ResultOfComparingFFRecords[DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM];
    boolean                             ConsistencyIdUpdatedFlg;
    Dem_u08_ConsistencyIdType           ConsistencyId;
} Dem_TmpEventMemoryEntryType;


#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
typedef struct {
    Dem_u16_EventStrgIndexType          EventStrgIndex;
    Dem_u08_FFDIndexType                RecordNumberIndex;
    Dem_u08_FaultIndexType              FaultIndex;
} Dem_OBDFaultRecordOverwrittenType;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

typedef struct {
    Dem_u16_EventStrgIndexType          EventStrgIndex;
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
    Dem_u16_TSFFListIndexType           TimeSeriesFreezeFrameListIndex[DEM_TSFF_RECORD_CLASS_NUM_PER_DTC_MAX_NUM];
#endif  /* (DEM_TSFF_PM_SUPPORT == STD_ON) */
    Dem_u08_FFDIndexType                RecordNumberIndex;
    Dem_u08_FaultIndexType              FaultIndex;
} Dem_FaultRecordOverwrittenType;

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
typedef struct {
    Dem_u16_EventStrgIndexType          EventStrgIndex;
    Dem_u08_FFDIndexType                RecordNumberIndex;
    Dem_u08_FaultIndexType              FaultIndex;
} Dem_Copy_FaultRecordOverwrittenType;
#endif  /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */

typedef struct {
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
    Dem_OBDFaultRecordOverwrittenType   ObdFaultRecordOverwritten[DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM];
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */
    Dem_FaultRecordOverwrittenType      FaultRecordOverwritten[DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM];
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
    Dem_u16_TSFFListIndexType           FaultRecordTSFFRemove[DEM_TSFF_RECORD_CLASS_NUM_PER_DTC_MAX_NUM];
#endif  /* (DEM_TSFF_PM_SUPPORT == STD_ON) */
    Dem_u16_EventStrgIndexType          EventStrgIndexOfFaultRecordOverwritten;
    Dem_u16_OccrOrderType               NextFaultOccurrenceOrder;

#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )
    Dem_u16_OccrOrderType               NextConfirmedFaultOccurrenceOrder;
#endif  /* ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )    */

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )
    Dem_u16_OccrOrderType               NextMILFaultOccurrenceOrder;
#endif  /* ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )      */

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
    boolean                             TSFFDeleteByFFROverwritten;
#endif  /* (DEM_TSFF_PM_SUPPORT == STD_ON) */
    Dem_UdsStatusByteType               DTCStatusAtFaultRecordOverwritten;
    Dem_UdsStatusByteType               DTCStatusForFaultRecordOverwrite;
} Dem_EventDisplacementType;

#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*----------------------------------*/
/*  Dem_DataCtl_EventEntry          */
/*----------------------------------*/

/*----------------------------------*/
/*  Dem_DataCtl_EventEntry00Init    */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_Data_InitTmpEventMemoryEntry
( void );

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Data_InitFaultRecordOverwrite
( void );
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

/*----------------------------------*/
/*  Dem_DataCtl_EventEntry01Latch   */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SaveEventMemoryEntry
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

/*----------------------------------*/
/*  Dem_DataCtl_EventEntry02Make  */
/*----------------------------------*/
#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SetNewMILOccurrenceToTmp
(
    VAR( boolean, AUTOMATIC ) MILOccurFlag
);
#endif  /*   ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )        */

/*----------------------------------*/
/*  Dem_DataCtl_EventEntry03Compare */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_Data_CompareEventMemoryEntryToTmp
( void );

FUNC( void, DEM_CODE ) Dem_Data_CompareEventRecordToTmp
( void );

FUNC( void, DEM_CODE ) Dem_Data_CompareFaultRecordToTmp
( void );

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Data_SetResultOfCmpObdFFRecordToTmp
(
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) ObdFreezeFrameRecordIndex,
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) Result
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

FUNC( void, DEM_CODE ) Dem_Data_SetResultOfCmpFFRecordToTmp
(
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordIndex,
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) Result
);

FUNC( void, DEM_CODE ) Dem_Data_SetConsistencyIdUpdateFlg
( void );
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Data_GetConsistencyIdUpdateFlg
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ConsistencyIdUpdFlgPtr,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) ConsistencyIdPtr
);
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )    */
/*----------------------------------*/
/*  Dem_DataCtl_EventEntry04Regist  */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_Data_StoreEventMemoryEntryFromTmp
( void );

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
extern VAR( Dem_TmpEventMemoryEntryType, DEM_VAR_NO_INIT ) Dem_TmpEventMemoryEntry;

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
extern VAR( Dem_u08_FFValidTriggerType, DEM_VAR_NO_INIT ) Dem_TmpUpperLimitReachedTrigger;
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Temporary area for event displacement                                    */
/****************************************************************************/
extern VAR( Dem_EventDisplacementType, DEM_VAR_NO_INIT ) Dem_EventDisplacement;

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
extern VAR( Dem_Copy_FaultRecordOverwrittenType, DEM_VAR_NO_INIT ) Dem_Data_CopyEventDisplacement_FaultRecordOverwritten[DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM];
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */

#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>



#endif /* DEM_DATACTL_EVENTENTRY_LOCAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
