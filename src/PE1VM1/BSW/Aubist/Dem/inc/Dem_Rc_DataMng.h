/* Dem_Rc_DataMng_h(v5-10-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/DataMng/HEADER                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_RC_DATAMNG_H
#define DEM_RC_DATAMNG_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_NvM_Cfg.h"
#include "../cfg/Dem_Data_Cfg.h"
#include "../usr/Dem_SavedZone_Callout.h"
#include "Dem_Mm_MemSync.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Iniail value for indexes                                                 */
/****************************************************************************/
#define DEM_FAILURECYCLE_COUNT_FACTORY_DEFAULT           ((Dem_u08_FailureCounterType)DEM_NVBLOCK_FACTORY_VALUE)
#define DEM_EVENT_OCCURRENCE_COUNT_FACTORY_DEFAULT       ((Dem_u08_EventOccurrenceCounterType)DEM_NVBLOCK_FACTORY_VALUE)
#define DEM_DTCSTATUS_FACTORY_DEFAULT                    ((Dem_UdsStatusByteType)DEM_NVBLOCK_FACTORY_VALUE)
#define DEM_DTCSTATUSEX_FACTORY_DEFAULT                  ((Dem_u08_DTCStatusExType)DEM_NVBLOCK_FACTORY_VALUE)
#define DEM_DTCSTATUSEX2_FACTORY_DEFAULT                 ((Dem_u08_DTCStatusEx2Type)DEM_NVBLOCK_FACTORY_VALUE)
#define DEM_PASSEDBITMAP_FACTORY_DEFAULT                 ((Dem_u08_EventCtrlBitmapType)DEM_NVBLOCK_FACTORY_VALUE)

#define DEM_FFD_INITIAL                                  ((uint8)0xFFU)
#define DEM_NUMOFEVTMEMENT_INITIAL                       ((Dem_u08_OrderIndexType)0x00U)

#define DEM_NUMOFFFREC_INITIAL                           ((Dem_u08_FFDIndexType)0U)

/* FaultOrderList */
#define DEM_DATA_RESERVE_INITIAL_VALUE                   ((uint8)0x00U)
#define DEM_DATA_INITIAL_VALUE                           ((uint8)0xFFU)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    Dem_u08_FaultIndexType              FaultIndex;
    Dem_UdsStatusByteType               StatusOfDTC;
    Dem_u08_DTCStatusExType             ExtendStatusOfDTC;
    Dem_u08_DTCStatusEx2Type            ExtendStatusOfDTC2;
    Dem_u08_FailureCounterType          FailureCounter;
#if ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )
    Dem_u08_EventOccurrenceCounterType  OccurrenceCounter;
#endif  /* ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )   */
} Dem_EventRecordForCtlType;

typedef struct
{
    P2VAR( Dem_FaultRecordType, TYPEDEF, DEM_VAR_SAVED_ZONE ) FaultRecordPtr;

} Dem_FaultRecordPtrForCtlType;

typedef struct
{
    Dem_u16_EventStrgIndexType  EventStrgIndex;
    Dem_u08_FFStoredStatusType            RecordStatus;
    uint8                   Data[DEM_FFR_MAX_LENGTH];
} Dem_FreezeFrameRecordForCtlType;

typedef struct
{
    Dem_u08_ConsistencyIdType   ConsistencyId;
    Dem_u16_EventStrgIndexType  EventStrgIndex;
    Dem_u08_FFStoredStatusType    RecordStatus;
    P2CONST( uint8, TYPEDEF, DEM_VAR_SAVED_ZONE ) DataPtr;
} Dem_FreezeFrameRecordMngType;

typedef struct
{
    Dem_u08_FFDIndexType    NumberOfFreezeFrameRecords;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
    Dem_u08_FFDIndexType    NumberOfObdFreezeFrameRecords;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */
    Dem_u08_OrderIndexType  NumberOfEventMemoryEntries;
    Dem_u08_OrderIndexType  NumberOfConfirmedDTCs;
    Dem_u08_OrderIndexType  NumberOfObdMILDTCs;
} Dem_EventMemoryRecordType;

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
typedef struct
{
    Dem_u16_EventStrgIndexType  EventStrgIndex;
    Dem_u08_FFStoredStatusType            RecordStatus;
    uint8                   Data[DEM_OBD_FFR_MAX_LENGTH];
} Dem_ObdFreezeFrameRecordForCtlType;

#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

typedef struct
{
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
    Dem_u16_TSFFListIndexType    TimeSeriesFreezeFrameListIndex[DEM_TSFF_RECORD_CLASS_NUM_PER_DTC_MAX_NUM];
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )    */
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
    Dem_u08_FFDIndexType         ObdRecordNumberIndex[ DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM ];
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */
    Dem_u08_FFDIndexType         RecordNumberIndex[ DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM ];

} Dem_FaultRecordPartsFFDIndexListStType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EventMng_ClearAllNotVerifiedRecord
(
    P2VAR( Dem_u16_RecordIndexType, AUTOMATIC, AUTOMATIC ) ClearRecordIndexPtr,
    P2VAR( Dem_u32_TotalRecordNumType, AUTOMATIC, AUTOMATIC ) RestOfProcessableNumPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FaultMng_ClearAllNotVerifiedRecord
(
    P2VAR( Dem_u16_RecordIndexType, AUTOMATIC, AUTOMATIC ) ClearRecordIndexPtr,
    P2VAR( Dem_u32_TotalRecordNumType, AUTOMATIC, AUTOMATIC ) RestOfProcessableNumPtr
);
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_TSFFDMng_ClearAllNotVerifiedRecord
(
    P2VAR( Dem_u16_RecordIndexType, AUTOMATIC, AUTOMATIC ) ClearRecordIndexPtr,
    P2VAR( Dem_u32_TotalRecordNumType, AUTOMATIC, AUTOMATIC ) RestOfProcessableNumPtr
);
#endif /* (DEM_TSFF_PM_SUPPORT == STD_ON) */
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFDMng_ClearAllNotVerifiedRecord
(
    P2VAR( Dem_u16_RecordIndexType, AUTOMATIC, AUTOMATIC ) ClearRecordIndexPtr,
    P2VAR( Dem_u32_TotalRecordNumType, AUTOMATIC, AUTOMATIC ) RestOfProcessableNumPtr
);
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ObdFFDMng_ClearAllNotVerifiedRecord
(
    P2VAR( Dem_u16_RecordIndexType, AUTOMATIC, AUTOMATIC ) ClearRecordIndexPtr,
    P2VAR( Dem_u32_TotalRecordNumType, AUTOMATIC, AUTOMATIC ) RestOfProcessableNumPtr
);
#endif /* (DEM_OBDFFD_SUPPORT == STD_ON) */

/*--------------------------------------*/
/*  Dem_DataMng_EventMemoryRecord.c     */
/*--------------------------------------*/
FUNC( void, DEM_CODE ) Dem_DataMngC_InitEvtMemRecData
(
    P2VAR( Dem_EventMemoryRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) EventMemoryRecordPtr
);
FUNC( void, DEM_CODE ) Dem_DataMngC_GetEventMemoryRecord
(
    P2VAR( Dem_EventMemoryRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) EventMemoryRecordPtr
);
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
#if ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )
FUNC( Dem_u08_OrderIndexType, DEM_CODE ) Dem_DataMngC_GetNumberOfConfirmedDTCs
( void );
#endif  /* ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )     */
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )     */
#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )
FUNC( Dem_u08_OrderIndexType, DEM_CODE ) Dem_DataMngC_GetNumberOfObdMILDTCs
( void );
FUNC( void, DEM_CODE ) Dem_DataMngC_IncrementNumberOfObdMILDTCs
( void );
#endif  /* ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )     */
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON )     */
FUNC( void, DEM_CODE ) Dem_DataMngC_SetEventMemoryRecord
(
    P2CONST( Dem_EventMemoryRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) EventMemoryRecordPtr
);
FUNC( void, DEM_CODE ) Dem_DataMngC_CopyEventMemoryRecord
(
    P2VAR( Dem_EventMemoryRecordType, AUTOMATIC, AUTOMATIC ) DestEventMemoryRecordPtr,
    P2CONST( Dem_EventMemoryRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) SrcEventMemoryRecordPtr
);

FUNC( void, DEM_CODE ) Dem_DataMng_RefreshRAM
( void );

/*--------------------------------------*/
/*  Dem_DataMng_RecDt_Event.c           */
/*--------------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetEventRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_EventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) EventRecordPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetER_FaultIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u08_FaultIndexType, AUTOMATIC, AUTOMATIC ) FaultIndexPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetER_StatusOfDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) StatusOfDTCPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetER_ExtendDTCStatus
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u08_DTCStatusExType, AUTOMATIC, AUTOMATIC ) ExtendStatusOfDTCPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetER_ExtendDTCStatus2
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC, AUTOMATIC ) ExtendStatusOfDTC2Ptr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetER_DTCStatusSt
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) DTCStatusStPtr
);

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DataMngC_SetER_StatusOfDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) StatusOfDTC
);
FUNC( void, DEM_CODE ) Dem_DataMngC_SetER_DTCStatusSt
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) DTCStatusStPtr
);

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DataMngC_SetER_DTCStatusSt_AtUpdateFaultRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) DTCStatusStPtr,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
);
#endif  /* ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )  */
#endif  /*   ( DEM_WWH_OBD_SUPPORT == STD_ON )      */

#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DataMngC_SetER_ExtendDTCStatus
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendStatusOfDTC
);
FUNC( void, DEM_CODE ) Dem_DataMngC_SetER_ExtendDTCStatus2
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendStatusOfDTC2
);
#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON )    */

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetER_FailureCounter
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u08_FailureCounterType, AUTOMATIC, AUTOMATIC ) FailureCounterPtr
);
#if ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetER_OccurrenceCounter
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u08_EventOccurrenceCounterType, AUTOMATIC, AUTOMATIC ) OccurrenceCounterPtr
);
#endif  /* ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )   */
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_SetEventRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_EventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) EventRecordPtr
);
FUNC( void, DEM_CODE ) Dem_DataMngC_SetEventRecord_AtUpdateFaultRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_EventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) EventRecordPtr,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_CompareEventRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_EventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) EventRecordPtr
);
FUNC( void, DEM_CODE ) Dem_DataMngM_InitEventRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( void, DEM_CODE ) Dem_DataMngC_InitEventCtlRecordData
(
    P2VAR( Dem_EventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) EventRecordPtr
);
FUNC( void, DEM_CODE ) Dem_DataMngC_CopyEventCtlRecordData
(
    P2VAR( Dem_EventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) DestEventRecordPtr,
    P2CONST( Dem_EventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) SrcEventRecordPtr
);
FUNC( boolean, DEM_CODE ) Dem_DataMng_GetFactoryCheckResultOfEventRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( boolean, DEM_CODE ) Dem_DataMng_CheckClearIDOfEventRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) ClearID
);
FUNC( boolean, DEM_CODE ) Dem_DataMng_CheckConsistencyIdOfEventRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
);
FUNC( void, DEM_CODE ) Dem_DataMng_InitER_FaultIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( void, DEM_CODE ) Dem_DataMng_SetEventRecordConsistencyId
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
);
FUNC( void, DEM_CODE ) Dem_DataMng_GetEventRecordConsistencyId
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) ConsistencyIdPtr
);
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DataMng_UpdateEventRecordConsistencyId
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) ConsistencyIdPtr
);
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON ) */
FUNC( void, DEM_CODE ) Dem_EventMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( void, DEM_CODE ) Dem_EventMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EventMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( void, DEM_CODE ) Dem_EventMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

/*--------------------------------------*/
/*  Dem_DataMng_RecDt_Event_CmbStrgON.c */
/*--------------------------------------*/
#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DataMngC_SetER_PassedBitmap_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_EventCtrlBitmapIndexType, AUTOMATIC ) PassedBitmapIndex,
    VAR( Dem_u08_EventCtrlBitmapType, AUTOMATIC ) PassedBitmapData
);
FUNC( void, DEM_CODE ) Dem_DataMngC_SetER_PassedBitmapAll_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_EventCtrlBitmapType, AUTOMATIC ) PassedBitmapData
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetER_PassedBitmap_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_EventCtrlBitmapIndexType, AUTOMATIC ) PassedBitmapIndex,
    P2VAR( Dem_u08_EventCtrlBitmapType, AUTOMATIC, AUTOMATIC ) PassedBitmapDataPtr
);
#endif  /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON ) */

/*--------------------------------------*/
/*  Dem_DataMng_RecDt_Fault.c           */
/*--------------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFaultRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) FaultRecordPtr
);

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFaultRecordAddress
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_FaultRecordPtrForCtlType, AUTOMATIC, AUTOMATIC ) FaultRecordPtrCtlPtr
);
#endif /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFaultRecordAddress_MaxNumOfFFRTrigger
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_FaultRecordPtrForCtlType, AUTOMATIC, AUTOMATIC ) FaultRecordPtrCtlPtr
);
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFaultRecordAddress_TSFF
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_FaultRecordPtrForCtlType, AUTOMATIC, AUTOMATIC ) FaultRecordPtrCtlPtr
);
#endif  /*   ( DEM_TSFF_PM_SUPPORT == STD_ON )   */

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFR_EventStrgIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
);

FUNC( uint8, DEM_CODE ) Dem_DataMngC_GetNumberOfDTCsToStoreFreezeFrame
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) AllObdDTCFreezeFlagPtr
);

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFR_EventStrgIndex_ObdRecordNumberIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, AUTOMATIC ) ObdRecordNumberIndexPtr
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFR_EventStrgIndex_RecordNumberIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, AUTOMATIC ) RecordNumberIndexPtr
);
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
#if ( DEM_OBDONEDS_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_DataMngC_GetFR_CheckExistOBDFFD
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
);
#endif  /*   ( DEM_OBDONEDS_SUPPORT == STD_ON )     */
#if ( DEM_OBDONUDS_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_DataMngC_GetFR_CheckExistOBDFFD
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
);
#endif  /*   ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )     */
#endif  /*   ( DEM_OBDONUDS_SUPPORT == STD_ON )     */

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFR_ObdFreezeFrameIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, AUTOMATIC ) ObdFreezeFrameIndexPtr
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFR_FreezeFrameIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, AUTOMATIC ) FreezeFrameIndexPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFR_AgingCounter
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u08_AgingCounterType, AUTOMATIC, AUTOMATIC ) AgingCounterPtr
);

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFR_AgingTime
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u16_WWHOBDTimeAgingCounterType, AUTOMATIC, AUTOMATIC ) AgingTimePtr
);
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON )    */

#if ( DEM_INDICATOR_USE == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFR_HealingCounter
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u08_HealingCounterType, AUTOMATIC, AUTOMATIC ) HealingCounterPtr
);
#endif  /* ( DEM_INDICATOR_USE == STD_ON )          */

#if ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFR_ConfirmedOccurrenceOrder
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u16_OccrOrderType, AUTOMATIC, AUTOMATIC ) ConfirmedOccurrenceOrderPtr
);
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )    */
#if ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_OFF )
#if ( DEM_OBDONEDS_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFR_ConfirmedOccurrenceOrder
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u16_OccrOrderType, AUTOMATIC, AUTOMATIC ) ConfirmedOccurrenceOrderPtr
);
#endif  /* ( DEM_OBDONEDS_SUPPORT == STD_ON )    */
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_OFF )    */
#if ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )
FUNC( Dem_u16_OccrOrderType, DEM_CODE ) Dem_DataMngC_ConfirmedOccurrenceOrder
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
);
#endif  /* ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT== STD_ON )   */
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFR_FFDIndexListSt
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_FaultRecordPartsFFDIndexListStType, AUTOMATIC, AUTOMATIC ) FFDIndexListStPtr
);
#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DataMngC_SetFR_MILOccurrenceOrder_WithUpdateConsistencyID
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) MILOccurrenceOrder,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) ConsistencyIdPtr
);
#endif  /* ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )  */
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON )    */

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_SetFaultRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) FaultRecordPtr
);
FUNC( void, DEM_CODE ) Dem_DataMngC_SetFaultRecord_WithUpdateConsistencyID
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) FaultRecordPtr,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) ConsistencyIdPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_ClearFaultRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_CompareFaultRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) CheckFaultRecordPtr
);
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngM_GetFaultRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */
FUNC( void, DEM_CODE ) Dem_DataMngC_InitFaultCtlRecordData
(
    P2VAR( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) FaultRecordPtr
);
FUNC( void, DEM_CODE ) Dem_DataMngC_CopyFaultRecord
(
    P2VAR( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) DestFaultRecordPtr,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) SrcFaultRecordPtr
);
FUNC( void, DEM_CODE ) Dem_DataMngC_InitFR_FFDIndexListStData
(
    P2VAR( Dem_FaultRecordPartsFFDIndexListStType, AUTOMATIC, AUTOMATIC ) FFDIndexListStPtr
);

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DataMng_UpdateFaultRecordConsistencyId_Displacement
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) ConsistencyIdPtr
);
#endif  /*   ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
FUNC( void, DEM_CODE ) Dem_DataMng_UpdateFaultRecordConsistencyId_Misfire
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) ConsistencyIdPtr
);
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )    */
FUNC( void, DEM_CODE ) Dem_DataMng_SetFaultRecordConsistencyId
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_GetFaultRecordConsistencyId
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) ConsistencyIdPtr
);
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DataMngC_InitObdRecordNumberIndexFFROverwritten
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FFRIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) ConsistencyIdPtr
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */
FUNC( void, DEM_CODE ) Dem_DataMngC_InitRecordNumberIndexFFROverwritten
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FFRIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) ConsistencyIdPtr
);
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
#if ( DEM_OBDONUDS_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DataMngC_CopyFR_AllObdRecordNumberIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndexDest,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndexSrc
);
FUNC( boolean, DEM_CODE ) Dem_DataMngC_CompareFR_ObdRecordNumberIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndexDest,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndexSrc
);
#endif  /* ( DEM_OBDONUDS_SUPPORT == STD_ON )   */
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   */
FUNC( void, DEM_CODE ) Dem_DataMng_InitSpecificObdRecordNumberIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameListIndex
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */
FUNC( void, DEM_CODE ) Dem_DataMng_InitSpecificRecordNumberIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameListIndex
);

FUNC( void, DEM_CODE ) Dem_FaultMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( void, DEM_CODE ) Dem_FaultMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FaultMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( void, DEM_CODE ) Dem_FaultMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */
FUNC( Dem_u08_OrderIndexType, DEM_CODE ) Dem_FaultMng_GetNumOfStoredFault
( void );

/*--------------------------------------*/
/*  Dem_DataMng_RecDt_TSFFList.c        */
/*  Dem_DataMng_RecDt_TSFFList_OFF.c    */
/*--------------------------------------*/
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DataMng_SetTSFFListRecord_Ctl
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) SrcFaultRecordPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFR_TSFFListIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) TimeSeriesFreezeFrameRecordClassRefIndex,
    P2VAR( Dem_u16_TSFFListIndexType, AUTOMATIC, AUTOMATIC ) TSFFListIndexPtr
);
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DataMngC_InitTimeSeriesFreezeFrameListIndexFFROverwritten
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameListIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) ConsistencyIdPtr
);
FUNC( boolean, DEM_CODE ) Dem_DataMngC_InitTimeSeriesFreezeFrameListIndexRemoveNonObdFreeze
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
);
#endif /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */
#endif  /* (DEM_TSFF_PM_SUPPORT    STD_ON) */

/*--------------------------------------*/
/*  Dem_DataMng_RecDt_FFD.c             */
/*--------------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFFR_MngInfo
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameIndex,
    P2VAR( Dem_FreezeFrameRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) FreezeFrameRecordPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFreezeFrameRecord
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameIndex,
    P2VAR( Dem_FreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_SetFreezeFrameRecord
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameIndex,
    P2CONST( Dem_FreezeFrameRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) FreezeFrameRecordPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_ClearFreezeFrameRecord
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameIndex
);
FUNC( void, DEM_CODE ) Dem_DataMngC_InitFreezeFrameRecordData
(
    P2VAR( Dem_FreezeFrameRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) FreezeFrameRecordPtr
);
FUNC( void, DEM_CODE ) Dem_FFDMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( void, DEM_CODE ) Dem_FFDMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFDMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( void, DEM_CODE ) Dem_FFDMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */
FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_FFDMng_GetNumOfStoredNonObdFFD
( void );
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFDMng_CheckToExistTriggerFFD
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) TargetTrigger,
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) DtcAttributePtr,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) FaultRecordPtr,
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, AUTOMATIC ) FreezeFrameIndexPtr
);
#endif  /* (DEM_TSFF_PM_SUPPORT    STD_ON) */

FUNC( Dem_u08_ConsistencyIdType, DEM_CODE ) Dem_FFDMng_GetFFDConsystencyId
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameIndex
);


/*--------------------------------------*/
/*  Dem_DataMng_RecDt_OBD_FFD.c         */
/*--------------------------------------*/
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetObdFFR_MngInfo
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ObdFreezeFrameIndex,
    P2VAR( Dem_ObdFreezeFrameRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) ObdFreezeFrameRecordPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetObdFreezeFrameRecord
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ObdFreezeFrameIndex,
    P2VAR( Dem_FreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) ObdFreezeFrameRecordPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_SetObdFreezeFrameRecord
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ObdFreezeFrameIndex,
    P2CONST( Dem_ObdFreezeFrameRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) ObdFreezeFrameRecordPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_ClearObdFreezeFrameRecord
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ObdFreezeFrameIndex
);
FUNC( void, DEM_CODE ) Dem_DataMngC_InitObdFreezeFrameRecordData
(
    P2VAR( Dem_ObdFreezeFrameRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) ObdFreezeFrameRecordPtr
);


FUNC( void, DEM_CODE ) Dem_ObdFFDMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( void, DEM_CODE ) Dem_ObdFFDMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ObdFFDMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( void, DEM_CODE ) Dem_ObdFFDMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */
FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_ObdFFDMng_GetNumOfStoredObdFFD
( void );
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

/*--------------------------------------*/
/*  Dem_DataMng_RecDt_TSFFD.c           */
/*  Dem_DataMng_RecDt_TSFFD_OFF.c       */
/*--------------------------------------*/
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_SetBeforeTimeSeriesFreezeFrameRecord
(
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId,
    P2CONST( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) SamplingFreezeFrameRecordDataStartPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_SetAfterTimeSeriesFreezeFrameRecord
(
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId,
    VAR( Dem_u08_FFStoredStatusType, AUTOMATIC ) SamplingRecordStatus,
    P2CONST( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) SamplingFreezeFrameRecordDataStartPtr
);
FUNC( Dem_u08_FFStoredStatusType, DEM_CODE ) Dem_DataMngC_GetRecordStatusOfTimeSeriesFreezeFrameRecord
(
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex
);
FUNC( void, DEM_CODE ) Dem_DataMngC_SetRecordStatusToStoredOfBeforeTSFFD
(
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_ClearTimeSeriesFreezeFrameRecord
(
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetTimeSeriesFreezeFrameRecord
(
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,
    P2VAR( Dem_FreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) TimeSeriesFreezeFrameRecordPtr
);
FUNC( void, DEM_CODE ) Dem_TSFFDMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( void, DEM_CODE ) Dem_TSFFDMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_TSFFDMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( void, DEM_CODE ) Dem_TSFFDMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#endif  /* (DEM_TSFF_PM_SUPPORT    STD_ON) */


/*--------------------------------------*/
/*  Dem_DataMng_RecLink.c               */
/*--------------------------------------*/

/*--------------------------------------*/
/*  Dem_DataMng_FreezeFrameIndex.c      */
/*--------------------------------------*/
FUNC( void, DEM_CODE ) Dem_DataMng_ClearSearchFFDIndex
( void );

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DataMngM_UpdateSearchFFDIndex
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) EmptyFreezeFrameIndex
);
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DataMngM_UpdateSearchObdFFDIndex
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) EmptyFreezeFrameIndex
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */
FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_DataMngC_GetEmptyFFDIndex
( void );
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_DataMngC_GetEmptyObdFFDIndex
( void );
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/*------------------------------*/
/*  get record data             */
/*------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EventMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FaultMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFDMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
);
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ObdFFDMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_TSFFDMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
);
#endif  /*   ( DEM_TSFF_PM_SUPPORT == STD_ON )     */
#endif  /*   ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )  */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

extern VAR( volatile Dem_EventMemoryRecordType, DEM_VAR_NO_INIT ) Dem_EventMemoryRecordList;

extern VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_EventNvMStatus[DEM_EVENT_RECORD_LIST_NUM];
extern VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_FaultNvMStatus[DEM_FAIL_RECORD_LIST_NUM];
extern VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_FFDNvMStatus[DEM_FFD_RECORD_LIST_NUM];
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
extern VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_ObdFFDNvMStatus[DEM_OBD_FFD_RECORD_LIST_NUM];
#endif  /*  ( DEM_OBDFFD_SUPPORT == STD_ON )    */
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
extern VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_TSFFDNvMStatus[DEM_TSFF_RECORD_LIST_NUM];
#endif  /*  ( DEM_TSFF_PM_SUPPORT == STD_ON )  */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
extern VAR( Dem_EventRecordType, DEM_VAR_NO_INIT ) Dem_TmpEventMirror;
extern VAR( Dem_FaultRecordType, DEM_VAR_NO_INIT ) Dem_TmpFaultMirror;
extern VAR( Dem_FreezeFrameRecordType, DEM_VAR_NO_INIT ) Dem_TmpFFDMirror;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
extern VAR( Dem_ObdFreezeFrameRecordType, DEM_VAR_NO_INIT ) Dem_TmpObdFFDMirror;
#endif  /*  ( DEM_OBDFFD_SUPPORT == STD_ON )    */
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
extern VAR( Dem_TSFFRecordType, DEM_VAR_NO_INIT ) Dem_TmpTSFFDMirror;
#endif  /*  ( DEM_TSFF_PM_SUPPORT == STD_ON )  */
#endif  /*  ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>



#endif /* DEM_RC_DATAMNG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
