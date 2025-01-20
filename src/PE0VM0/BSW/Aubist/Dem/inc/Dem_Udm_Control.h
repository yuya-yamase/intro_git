/* Dem_Udm_Control_h(v5-5-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Udm_Control/HEADER                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_UDM_CONTROL_H
#define DEM_UDM_CONTROL_H

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
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
/*----------------------------------------------*/
/*  common                                      */
/*----------------------------------------------*/
FUNC( void, DEM_CODE ) Dem_UdmControl_Init
( void );
FUNC( void, DEM_CODE ) Dem_UdmControl_Init_AfterRecordCheckComplete
( void );
FUNC( void, DEM_CODE ) Dem_UdmControl_GenerateRecordInfo
( void );

/*----------------------------------------------*/
/*  common                                      */
/*----------------------------------------------*/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_UdmControl_SetEventCommon
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0
);


FUNC( void, DEM_CODE ) Dem_UdmControl_NormalEventMemoryEntryByOpCycle
(
    VAR( Dem_u16_EventPosType, AUTOMATIC ) EventPos,
    VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC ) HealingAgingCycleFlag,
    VAR( Dem_u08_OpcycUpdateFailureCycleType, AUTOMATIC ) FailureCycleFlag,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) NeedGenOrderListPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ExecHealingPtr
);

/*----------------------------------------------*/
/*  at DEM_USERDEFINEDMEMORY_SUPPORT is STD_ON  */
/*----------------------------------------------*/
FUNC( void, DEM_CODE ) Dem_UdmControl_StartClearDTC
(
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmControl_ClearRAM
( void );
FUNC( void, DEM_CODE ) Dem_UdmControl_EndClearDTC
(
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);
FUNC( void, DEM_CODE ) Dem_UdmControl_Clear_ClearDTCInfo
( void );

/*----------------------------------------------*/
/*  Dem_UdmControl_EventEntry.c                 */
/*----------------------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmControl_GetNumberOfEventMemoryEntries
(
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( Dem_u08_OrderIndexType, AUTOMATIC, AUTOMATIC ) NumberOfEventMemoryEntriesPtr
);


/*---------------------------------------------*/
/*  Dem_UdmControl_SyncEventEntry.c             */
/*----------------------------------------------*/
FUNC( void, DEM_CODE ) Dem_UdmControl_InitSyncEventEntry
( void );
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmControl_SyncEventEntry
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_MonitorDataType, AUTOMATIC ) MonitorData0
);
FUNC( void, DEM_CODE ) Dem_UdmControl_SyncEventEntry_RefreshRAM
( void );


/*----------------------------------------------*/
/*  Dem_UdmControl_DisableDTCInfo.c             */
/*----------------------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmControl_DisableDTCRecordUpdate
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);

FUNC( Dem_u08_DTCRecordUpdateStatusType, DEM_CODE) Dem_UdmControl_GetDTCRecordUpdateStatus
( void );

FUNC( void, DEM_CODE ) Dem_UdmControl_EnableDTCRecordUpdate
( void );

FUNC( void, DEM_CODE ) Dem_UdmControl_InitDTCRecordUpdateInfo
( void );

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmControl_CheckDisableDTCInfo
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC, AUTOMATIC ) UdmMemoryTypePtr,
    P2VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC, AUTOMATIC ) UdmGroupKindIndexPtr
);

/*----------------------------------------------*/
/*  Dem_UdmControl_EventInfo.c                  */
/*----------------------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmControl_GetStatusOfDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);

/*----------------------------------------------*/
/*  Dem_UdmControl_FFDInfo.c                    */
/*----------------------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmControl_GetSizeOfFreezeFrameByDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_u32_FFDOutputTotalSizeType, AUTOMATIC, AUTOMATIC ) SizeOfFreezeFramePtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmControl_GetFreezeFrameDataByDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufSizePtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) NextRecordNumberPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmControl_GetUserDefinedMemoryFreezeFrameRecordNumber
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, DEM_APPL_DATA ) RecordNumBufferPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) RecordNumPtr
);

/*----------------------------------------------*/
/*  Dem_UdmControl_EDRInfo.c                    */
/*----------------------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmControl_GetSizeOfExtendedDataRecordByDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber,
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) SizeOfExtendedDataRecordPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmControl_GetExtendedDataRecordByDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr,
    P2VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC, AUTOMATIC ) NextExtendedDataNumberPtr
);

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )      */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* DEM_UDM_CONTROL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

