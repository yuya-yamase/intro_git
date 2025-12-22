/* Dem_Rc_UdmMng_h(v5-5-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Rc_UdmMng/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_RC_UDMMNG_H
#define DEM_RC_UDMMNG_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_NvM_Cfg.h"
#include "Dem_Mm_MemSync.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )

#include "Dem_Rc_DataMng.h"
#include "Dem_Udm_Data.h"
#include "../cfg/Dem_UserDefMem_Cfg.h"
#include "../usr/Dem_SavedZone_Callout.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Iniail value for indexes                                                 */
/****************************************************************************/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    Dem_u08_UdmFaultIndexType       UdmFaultIndex;
    Dem_UdsStatusByteType           StatusOfDTC;
} Dem_UdmEventRecordForCtlType;

typedef struct
{
    Dem_u32_UdmOccurrenceOrderType  OccurrenceOrder;
    Dem_u16_UdmEventIndexType       UdmEventIndex;
    Dem_u08_ConsistencyIdType       CidUdmFreezeFrameRecords;
    Dem_u08_NumOfTSFFType           OffsetOfTSFFListIndex;
    Dem_u08_FFStoredStatusType      RecordStatus;
    uint8                           Data[DEM_UDMFFD_MAX_LENGTH];
} Dem_UdmFreezeFrameRecordForCtlType;

typedef struct
{
    Dem_u32_UdmOccurrenceOrderType                  OccurrenceOrder;
    Dem_u08_ConsistencyIdType                       CidUdmFreezeFrameRecords;
    Dem_u08_FFStoredStatusType                      RecordStatus;
    Dem_u08_NumOfTSFFType           OffsetOfTSFFListIndex;
    P2CONST( uint8, TYPEDEF, DEM_VAR_SAVED_ZONE )   DataPtr;
} Dem_UdmFreezeFrameRecordMngType;

typedef struct
{
    Dem_u32_UdmOccurrenceOrderType  OccurrenceOrder;
    Dem_u16_UdmEventIndexType       UdmEventIndex;
    Dem_u08_ConsistencyIdType       CidUdmFreezeFrameRecords;
    Dem_u08_NumOfTSFFType           OffsetOfTSFFListIndex;
    Dem_u08_FFStoredStatusType      RecordStatus;
} Dem_UdmFFRMngInfoType;

typedef struct
{
    Dem_u16_OccrOrderType   LastOfFaultOccurrenceOrder;
    Dem_u16_UdmFFDIndexType NumberOfFreezeFrameRecords;
    Dem_u08_OrderIndexType  NumberOfEventMemoryEntries;
} Dem_UdmEventMemoryRecordType;

typedef struct
{
    Dem_u32_UdmOccurrenceOrderType  OccurrenceOrder;
    Dem_u16_UdmFFDIndexType         FreezeFrameRecordIndex;
    Dem_u08_ConsistencyIdType       CidUdmFreezeFrameRecords;
} Dem_UdmNextFreezeFrameType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------*/
/*  Dem_UdmEventMng.c                   */
/*--------------------------------------*/
FUNC( void, DEM_CODE ) Dem_UdmEventMngC_InitEvtMemRecData
(
    P2VAR( Dem_UdmEventMemoryRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) EventMemoryRecordPtr
);
FUNC( void, DEM_CODE ) Dem_UdmEventMngC_InitAllEvtMemRecData
( void );
FUNC( void, DEM_CODE ) Dem_UdmEventMngC_SetAllNumberOfEventMemoryRecord
( void );
FUNC( void, DEM_CODE ) Dem_UdmEventMngC_InitRecord
(
    P2VAR( Dem_UdmEventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) EventRecordPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmEventMngC_GetRecord
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2VAR( Dem_UdmEventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) UdmEventRecordPtr
);
FUNC( void, DEM_CODE ) Dem_UdmEventMngC_GetEventMemoryRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    P2VAR( Dem_UdmEventMemoryRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) EventMemoryRecordPtr
);
FUNC( void, DEM_CODE ) Dem_UdmEventMngC_SetEventMemoryRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    P2CONST( Dem_UdmEventMemoryRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) EventMemoryRecordPtr
);
FUNC( void, DEM_CODE ) Dem_UdmEventMngC_ResetLastOfFaultOccurrenceOrder
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmEventMngC_CompareEventRecord
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2CONST( Dem_UdmEventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) EventRecordPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmEventMngC_SetEventRecord
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2VAR( Dem_UdmEventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) EventRecordPtr
);

FUNC( void, DEM_CODE ) Dem_UdmEventMng_SetEventRecordConsistencyId
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
);
FUNC( void, DEM_CODE ) Dem_UdmEventMng_InitRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) UdmEventStrgIndex
);

FUNC( void, DEM_CODE ) Dem_UdmEventMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( void, DEM_CODE ) Dem_UdmEventMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmEventMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( void, DEM_CODE ) Dem_UdmEventMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmEventMngC_GetER_StatusOfDTC
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) StatusOfDTCPtr
);
FUNC( void, DEM_CODE ) Dem_UdmEventMngC_SetER_StatusOfDTC
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) StatusOfDTC
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmEventMngC_GetER_FaultIndex
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC, AUTOMATIC ) FaultIndexPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmEventMng_ClearAllNotVerifiedRecord
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_u16_RecordIndexType, AUTOMATIC, AUTOMATIC ) ClearRecordIndexPtr,
    P2VAR( Dem_u32_TotalRecordNumType, AUTOMATIC, AUTOMATIC ) RestOfProcessableNumPtr
);

FUNC_P2VAR( Dem_UdmEventRecordType, DEM_VAR_SAVED_ZONE, DEM_CODE ) Dem_UdmEventMng_GetEventRecordPtr
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) UdmEventStrgIndex
);
/*--------------------------------------*/
/*  Dem_UdmFaultMng.c                   */
/*--------------------------------------*/
FUNC( Dem_u08_UdmFaultIndexType, DEM_CODE ) Dem_UdmFaultMngC_GetEmptyFaultIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmStartFaultIndex
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFaultMngC_GetLowestPriorityFaultIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_EventPriorityType, AUTOMATIC ) LimitEventPriority,
    VAR( Dem_u08_EventDisplacementStrategyType, AUTOMATIC ) EventDisplacementStrategy,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) UdmEventIndexLowestPriorityPtr
);
FUNC( Dem_u08_UdmFaultIndexType, DEM_CODE ) Dem_UdmFaultMngC_GetFaultRecordNum
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFaultMngC_GetRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2VAR( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) UdmFaultRecordPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFaultMngC_CompareFaultRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) CheckUdmFaultRecordPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFaultMngC_SetFaultRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) UdmFaultRecordPtr
);

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFaultMngC_SetTSFFListIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) SrcUdmFaultRecordPtr
);
#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */

FUNC( void, DEM_CODE ) Dem_UdmFaultMngM_GetFreezeFrameIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC, AUTOMATIC ) UdmFreezeFrameIndexPtr
);
#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_UdmFaultMngM_GetTSFFListIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC, AUTOMATIC ) UdmTSFFListIndexPtr
);
FUNC( void, DEM_CODE ) Dem_UdmFaultMng_InitTSFFListIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex
);
#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */
FUNC( void, DEM_CODE ) Dem_UdmFaultMng_InitCtlRecordData
(
    P2VAR( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) UdmFaultRecordPtr
);
FUNC( void, DEM_CODE ) Dem_UdmFaultMng_InitSpecificRecordNumberIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex
);
FUNC( void, DEM_CODE ) Dem_UdmFaultMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( void, DEM_CODE ) Dem_UdmFaultMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFaultMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFaultMngC_ClearFaultRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex
);
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( void, DEM_CODE ) Dem_UdmFaultMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

FUNC( void, DEM_CODE ) Dem_UdmFaultMng_GetNumOfStoredFault
(
    P2VAR( Dem_UdmEventMemoryRecordType, AUTOMATIC, DEM_VAR_NO_INIT )  UdmEventMemoryRecordListPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFaultMng_ClearAllNotVerifiedRecord
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_u16_RecordIndexType, AUTOMATIC, AUTOMATIC ) ClearRecordIndexPtr,
    P2VAR( Dem_u32_TotalRecordNumType, AUTOMATIC, AUTOMATIC ) RestOfProcessableNumPtr
);


/*--------------------------------------*/
/*  Dem_UdmTSFFDMng.c                   */
/*--------------------------------------*/
#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_UdmTSFFDMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( void, DEM_CODE ) Dem_UdmTSFFDMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
);
FUNC( void, DEM_CODE ) Dem_UdmTSFFDMng_Verified
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmTSFFDMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( void, DEM_CODE ) Dem_UdmTSFFDMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmTSFFDMng_ClearAllNotVerifiedRecord
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_u16_RecordIndexType, AUTOMATIC, AUTOMATIC ) ClearRecordIndexPtr,
    P2VAR( Dem_u32_TotalRecordNumType, AUTOMATIC, AUTOMATIC ) RestOfProcessableNumPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmTSFFDMng_SetBeforeTimeSeriesFreezeFrameRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId,
    P2CONST( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) SamplingFreezeFrameRecordDataStartPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmTSFFDMng_SetAfterTimeSeriesFreezeFrameRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId,
    VAR( Dem_u08_FFStoredStatusType, AUTOMATIC ) SamplingRecordStatus,
    P2CONST( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) SamplingFreezeFrameRecordDataStartPtr
);
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmTSFFDMng_GetFFR_MngInfo
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,
    P2VAR( Dem_UdmFreezeFrameRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) TimeSeriesFreezeFrameRecordPtr
);
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */
FUNC( Dem_u08_FFStoredStatusType, DEM_CODE ) Dem_UdmTSFFDMng_GetTimeSeriesFreezeFrameRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,
    P2VAR( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) TimeSeriesFreezeFrameRecordPtr
);
FUNC( void, DEM_CODE ) Dem_UdmTSFFDMng_SetRecordStatus
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex
);
FUNC( Dem_u08_FFStoredStatusType, DEM_CODE ) Dem_UdmTSFFDMng_GetRecordStatus
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmTSFFDMng_ClearTimeSeriesFreezeFrameRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex
);
FUNC( void, DEM_CODE ) Dem_UdmTSFFDMng_ClearTSFFList
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TSFFRecordStartIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TSFFRecordEndIndex
);
#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */


/*--------------------------------------*/
/*  Dem_UdmFFDMng.c                     */
/*--------------------------------------*/
FUNC( void, DEM_CODE ) Dem_UdmFFDMng_InitRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex
);
FUNC( void, DEM_CODE ) Dem_UdmFFDMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( void, DEM_CODE ) Dem_UdmFFDMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFFDMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFFDMng_ClearStoredRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex
);
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( void, DEM_CODE ) Dem_UdmFFDMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

FUNC( void, DEM_CODE ) Dem_UdmFFDMng_GetNumOfStoredUdmFFD
(
    P2VAR( Dem_UdmEventMemoryRecordType, AUTOMATIC, DEM_VAR_NO_INIT )  UdmEventMemoryRecordListPtr
);

FUNC( Dem_u16_UdmFFDIndexType, DEM_CODE ) Dem_UdmFFDMng_GetFFDRecordNum
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex
);
FUNC( void, DEM_CODE ) Dem_UdmFFDMngC_InitFreezeFrameRecordData
(
    P2VAR( Dem_UdmFreezeFrameRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) FreezeFrameRecordPtr
);
FUNC( Dem_u08_ConsistencyIdType, DEM_CODE ) Dem_UdmFFDMng_GetFFDConsystencyId
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFFDMng_GetFFR_MngInfo
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex,
    P2VAR( Dem_UdmFreezeFrameRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) FreezeFrameRecordPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFFDMng_GetFreezeFrameRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex,
    P2VAR( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC, DEM_VAR_NO_INIT ) FreezeFrameRecordPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFFDMng_GetMngInfo
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex,
    P2VAR( Dem_UdmFFRMngInfoType, AUTOMATIC, AUTOMATIC ) FFRMngInfoPtr
);
FUNC_P2VAR( uint8, DEM_VAR_SAVED_ZONE, DEM_CODE ) Dem_UdmFFDMng_GetFreezeFrameStartDataPtr
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex
);
FUNC( void, DEM_CODE ) Dem_UdmFFDMng_SetFreezeFrameRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex,
    P2CONST( Dem_UdmFreezeFrameRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) FreezeFrameRecordPtr
);
FUNC( void, DEM_CODE ) Dem_UdmFFDMng_SetMngInfo
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex,
    P2CONST( Dem_UdmFFRMngInfoType, AUTOMATIC, DEM_VAR_NO_INIT ) FFRMngInfoPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFFDMng_ClearAllNotVerifiedRecord
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_u16_RecordIndexType, AUTOMATIC, AUTOMATIC ) ClearRecordIndexPtr,
    P2VAR( Dem_u32_TotalRecordNumType, AUTOMATIC, AUTOMATIC ) RestOfProcessableNumPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFFDMng_GetNextFreezeFrameInfo
(
    VAR( boolean, AUTOMATIC ) FaultOfTheFirstTime,
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) StartFreezeFrameRecordIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) MaxNumberFreezeFrameRecords,
    P2VAR( Dem_UdmNextFreezeFrameType, AUTOMATIC, AUTOMATIC ) UdmNextFreezeFrameInfoPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFFDMng_GetRecordStatus
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameRecordIndex,
    P2VAR( Dem_u08_FFStoredStatusType, AUTOMATIC, AUTOMATIC ) RecordStatusPtr
);
#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_UdmFFDMng_InitOffsetOfTSFFListIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameRecordIndex
);
FUNC( void, DEM_CODE ) Dem_UdmFFDMng_ClearAndSetOffsetOfTSFFListIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) CurrentUdmFreezeFrameRecordIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) StartUdmFreezeFrameRecordIndex,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) OffsetOfTSFFListIndex
);
FUNC( Dem_u08_NumOfTSFFType, DEM_CODE ) Dem_UdmFFDMng_GetLatestOffsetOfTSFFListIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) StartFreezeFrameRecordIndex
);
FUNC( Dem_u16_UdmFFDIndexType, DEM_CODE ) Dem_UdmFFDMng_GetFFRIndexByOffsetOfTSFFListIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) StartFreezeFrameRecordIndex,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) OffsetOfTSFFListIndex
);
#endif  /* ( DEM_TSFF_UDM_SUPPORT == STD_ON )   */
FUNC( void, DEM_CODE ) Dem_UdmFFDMng_ClearFFDOtherThanTheFirstTime
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) StartUdmFreezeFrameRecordIndex
);

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/*------------------------------*/
/*  get record data             */
/*------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmEventMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFaultMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFFDMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
);
#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmTSFFDMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
);
#endif  /* ( DEM_TSFF_UDM_SUPPORT == STD_ON )       */

#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
extern VAR( Dem_UdmEventRecordType, DEM_VAR_NO_INIT ) Dem_TmpUdmEventMirror;
extern VAR( Dem_UdmFaultRecordType, DEM_VAR_NO_INIT ) Dem_TmpUdmFaultMirror;
#endif  /*  ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#endif /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) */

#endif /* DEM_RC_UDMMNG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
