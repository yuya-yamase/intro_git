/* Dem_CmnIf_Control_h(v5-5-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/CmnIf_Control/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_CMNIF_CONTROL_H
#define DEM_CMNIF_CONTROL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

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

FUNC( void, DEM_CODE_TRUST ) Dem_Control_PreInit       /*  PreInit section     */
( void );

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

/*----------------------------------*/
/*  Dem_Control                     */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_Control_Init
( void );
FUNC( void, DEM_CODE ) Dem_Control_Shutdown
( void );
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_InitProcess
( void );
FUNC( void, DEM_CODE ) Dem_Control_Process
( void );
FUNC( void, DEM_CODE ) Dem_Control_RefreshRAM
( void );
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_ChkInitStatus
(
    VAR( Dem_u08_InitStatusType, AUTOMATIC ) InitStatus
);

/*----------------------------------*/
/*  Dem_Control_EventEntryCmn       */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetEventStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus
);

#if  ( DEM_MONITORDATA_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetEventStatusWithMonitorData
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0
);
#endif /* (DEM_MONITORDATA_SUPPORT == STD_ON) */
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetEventFailedWithSyncFreezeFrame
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
);
#endif /* (DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON) */

/*----------------------------------*/
/*  Dem_Control_Clear               */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckClearParameter
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_ClearDTC
(
    VAR( Dem_u08_RequestCallerType, AUTOMATIC ) Caller,
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);

/*----------------------------------*/
/*  Dem_Control_OpCycle             */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_RestartOperationCycle
(
    VAR( Dem_u08_OperationCycleIdType, AUTOMATIC ) OperationCycleId
);
#if ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetCycleQualified
(
    VAR( Dem_u08_OperationCycleIdType, AUTOMATIC ) OperationCycleId
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetCycleQualified
(
    VAR( Dem_u08_OperationCycleIdType, AUTOMATIC ) OperationCycleId,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) CycleQualifiedPtr
);
#endif /* DEM_CYCLEQUALIFIED_SUPPORT -STD_ON- */


/*----------------------------------*/
/*  Dem_Control_IFCmn               */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_GetEventStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventID,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) UDSStatusBytePtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_GetEventUdsStatusHistory
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventID,
    P2VAR( Dem_UdsStatusHistoryByteType, AUTOMATIC, AUTOMATIC ) UDSStatusHistoryBytePtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_GetDTCOfEvent
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventID,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCOfEventPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_GetNumberOfEventMemoryEntries
(
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( Dem_u08_OrderIndexType, AUTOMATIC, AUTOMATIC ) NumberOfEventMemoryEntriesPtr
);
#if ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_SetEvtAvl
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( boolean, AUTOMATIC ) AvailableStatus
);
#endif  /* ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON ) */
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_GetUserDefinedMemoryIdentifier
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) MemoryIdentifierPtr
);
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_GetRecordInfoByNvMBlockId
(
    VAR( Dem_BlockIdType, AUTOMATIC ) BlockId,
    P2VAR( Dem_RecordKindType, AUTOMATIC, AUTOMATIC ) RecordKindPtr,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
);
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

/*----------------------------------*/
/*  Dem_Control_DcmCmn              */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_DisableDTCRecordUpdate
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);
FUNC( void, DEM_CODE ) Dem_ControlIFCmn_EnableDTCRecordUpdate
( void );
FUNC( Dem_u08_DTCRecordUpdateStatusType, DEM_CODE ) Dem_ControlIFCmn_GetDTCRecordUpdateStatus
( void );

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_GetStatusOfDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatus
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_GetSizeOfFreezeFrameByDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_u32_FFDOutputTotalSizeType, AUTOMATIC, AUTOMATIC ) SizeOfFreezeFrame
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_GetFreezeFrameDataByDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufSizePtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) NextRecordNumberPtr
);
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_GetUserDefinedMemoryFreezeFrameRecordNumber
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, DEM_APPL_DATA ) RecordNumBufferPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) RecordNumPtr
);
#endif /* (DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON) */

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_GetSizeOfExtendedDataRecordByDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber,
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) SizeOfExtendedDataRecordPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_GetExtendedDataRecordByDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr,
    P2VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC, AUTOMATIC ) NextExtendedDataNumberPtr
);

/*----------------------------------*/
/*  Dem_Control_Ind                 */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetWIRStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( boolean, AUTOMATIC ) WIRStatus
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetIndicatorStatus
(
    VAR( Dem_u08_IndicatorIdType, AUTOMATIC ) IndicatorId,
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetIndStatusByEventId
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( Dem_u08_IndicatorIdType, AUTOMATIC ) IndicatorId,
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr
);


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* DEM_CMNIF_CONTROL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

