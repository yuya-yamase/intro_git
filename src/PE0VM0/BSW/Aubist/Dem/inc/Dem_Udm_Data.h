/* Dem_Udm_Data_h(v5-5-0)                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Udm_Data/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_UDM_DATA_H
#define DEM_UDM_DATA_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../cfg/Dem_UserDefMem_Cfg.h"
#include "Dem_CmnLib_DataCtl_SamplingFFDAccess.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes - PreInit section                                    */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmDTC_SearchFilteredDTC
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmDTC_SetFilteredDTC
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);

FUNC( Dem_u16_UdmEventIndexType, DEM_CODE ) Dem_UdmControl_GetDisableDTCRecordEvent
( void );


/* Dem_UdmDTC.h */
FUNC( void, DEM_CODE ) Dem_UdmDTC_ChangeDTCStatus_ToFailed
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatus,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) NewDTCStatusPtr
);
FUNC( void, DEM_CODE ) Dem_UdmDTC_ChangeDTCStatus_ToPassed
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatus,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) NewDTCStatusPtr
);
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_UdmDTC_ChangeDTCStatusForSyncEventEntry
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
);

FUNC( void, DEM_CODE ) Dem_UdmDTC_UpdateDTCStatusByRetentionResult
(
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) EventRetentionResult,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) NewDTCStatusPtr
);

FUNC( void, DEM_CODE ) Dem_UdmDTC_TranslateDTCStatusAfterUpdate
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) OldDTCStatusPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) NewDTCStatusPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmDTC_GetDTCStatusOfEvent
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);


/* Dem_UdmDataCtl.h */
/*----------------------------------*/
/*  Dem_DataCtl_EventEntry          */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_UdmData_RequestFixedClear
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SaveEventMemoryEntryToTmp
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
);
FUNC( void, DEM_CODE ) Dem_UdmData_UpdateEventMemoryEntryFromTmp
(
    VAR( boolean, AUTOMATIC ) FaultRecordOverwriteFlag,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndexOverwritten,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusAtOverwritten,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListIndexOverwritten
);
FUNC( void, DEM_CODE ) Dem_UdmData_SetNumOfFaultAndFFD
( void );

/*--------------------------------------*/
/*  Dem_DataCtl_EventEntry02Make_Event  */
/*--------------------------------------*/
FUNC( void, DEM_CODE ) Dem_UdmData_SetDTCStatusToTmp
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
);
FUNC( void, DEM_CODE ) Dem_UdmData_GetDTCStatusFromTmp
(
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);

/*--------------------------------------*/
/*  Dem_DataCtl_EventEntry02Make_Fault  */
/*--------------------------------------*/
FUNC( void, DEM_CODE ) Dem_UdmData_InitSearchFRIndex
( void );
FUNC( Dem_u08_UdmFaultIndexType, DEM_CODE ) Dem_UdmData_GetSearchFRIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex
);
FUNC( void, DEM_CODE ) Dem_UdmData_SetSearchFRIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmSearchFaultIndex
);
FUNC( void, DEM_CODE ) Dem_UdmData_ReplaceSearchFRIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SetFaultInfo
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )      FaultOccurrenceFlagPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )      FaultRecordOverwriteFlagPtr,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) UdmEventIndexOverwrittenPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) OldDTCStatusAtOverwrittenPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) NewDTCStatusAtOverwrittenPtr,
    P2VAR( Dem_u16_TSFFListIndexType, AUTOMATIC, AUTOMATIC ) TSFFListIndexOverwrittenPtr
);

/*--------------------------------------*/
/*  Dem_UdmDataCtl_SyncEventEntry.c     */
/*--------------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SaveEventMemoryEntryToSyncTmp
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
);
FUNC( void, DEM_CODE ) Dem_UdmData_SetDTCStatusToSyncTmp
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
);
FUNC( void, DEM_CODE ) Dem_UdmData_GetDTCStatusFromSyncTmp
(
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SetFaultInfoForSyncEventEntry
( void );
FUNC( void, DEM_CODE ) Dem_UdmData_CaptureNonObdFreezeFrameToSyncTmp
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0
);
FUNC( void, DEM_CODE ) Dem_UdmData_UpdateEventMemoryEntryFromSyncTmp
( void );



/*--------------------------------------*/
/*  Dem_DataCtl_EventEntry02Make_FFD    */
/*--------------------------------------*/
FUNC( void, DEM_CODE ) Dem_UdmData_CaptureFreezeFrame
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0
);


/*----------------------------------*/
/*  Dem_UdmDTC                      */
/*----------------------------------*/
FUNC( boolean, DEM_CODE ) Dem_UdmDTC_JudgeUdmDTCClearTarget
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmDTC_GetDTCAndStatus
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusAvailabilityMask,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmDTC_GetDTCStatus
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusAvailabilityMask,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmDTC_TranslateDTCStatusForOutput
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);


FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmDTC_GetDTCStatusOfDisabledRecord
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusAvailabilityMask,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFFD_GetSizeOfFreezeFrame
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_u32_FFDOutputTotalSizeType, AUTOMATIC, AUTOMATIC ) SizeOfFreezeFramePtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFFD_GetFreezeFrameData
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufSizePtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) NextRecordNumberPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SaveDisabledRecord
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
);

FUNC( void, DEM_CODE ) Dem_UdmData_ClearDisabledRecord
( void );

FUNC( void, DEM_CODE ) Dem_UdmData_GetDTCStatusOfDisabledRecord
(
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_GetDTCStatus
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);


FUNC( void, DEM_CODE ) Dem_UdmData_InitSaveTmpRecordNumber
( void );
FUNC( void, DEM_CODE ) Dem_UdmData_ResetSearchStartPosition
( void );

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_GetFreezeFrameData
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u08_FFDGetInfoType, AUTOMATIC ) FreezeFrameGetInfoType,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DataPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) DataSizePtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_GetAllRecordNumber
(
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, DEM_APPL_DATA ) RecordNumBufferPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) RecordNumPtr
);

FUNC( void, DEM_CODE ) Dem_UdmData_SetNextRecordNumber
(
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC )                 RecordNumber,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC )    NextRecordNumberPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_GetSizeOfFreezeFrameOfDisabledRecord
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_u32_FFDOutputTotalSizeType, AUTOMATIC, AUTOMATIC ) SizeOfFreezeFramePtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_CheckRecordNumberInDisabledRecord
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber
);

/*--------------------------------------*/
/*  Dem_UdmDataCtl_EventEntry00Init.c   */
/*--------------------------------------*/
FUNC( void, DEM_CODE ) Dem_UdmData_InitTmpEventMemoryEntry
( void );


FUNC( void, DEM_CODE ) Dem_UdmData_SaveRecordNumberByDTC
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC, AUTOMATIC ) NumberOfSaveRecordPtr
);

/*--------------------------*/
/*  Dem_UdmDataCtl_TSFFD.c  */
/*--------------------------*/
#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_CaptureAfterTriggeredTSFFFromSample
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameRecordIndex,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) OffsetOfTimeSeriesFreezeFrameTableIndexPerDTC,
    P2CONST( Dem_SamplingFreezeFrameRecordPosType, AUTOMATIC, AUTOMATIC ) SamplingFreezeFrameRecorPosPtr,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) SamplingFreezeFrameRecordDataPtr
);

FUNC( void, DEM_CODE ) Dem_UdmData_MakeTSFFListRecordList
( void );

FUNC( void, DEM_CODE ) Dem_UdmData_GenerateTSFFLRecordList
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex
);
#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )      */



#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* DEM_UDM_DATA_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

