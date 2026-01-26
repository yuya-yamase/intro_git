/* Dem_Control_local_h(v5-5-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_local/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_CONTROL_LOCAL_H
#define DEM_CONTROL_LOCAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_CmnLib_Control.h"
#include "../../../inc/Dem_Pm_DataCtl.h"       /*  for Dem_OrderListOccurredFlagType   */

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8   Dem_u08_EventKindPtnType;
#define DEM_EVTKINDPTN_PRIMEM_NORMAL        ((Dem_u08_EventKindPtnType)0x00U)
#define DEM_EVTKINDPTN_PRIMEM_SPECIFIC      ((Dem_u08_EventKindPtnType)0x01U)

/*------------------------------------------------------*/
/*  SetEventStatus update control flag structure        */
/*------------------------------------------------------*/
typedef struct
{
    Dem_u16_EventStrgIndexType   EventStrgIndexOfFaultRecordOverwritten;
    Dem_UdsStatusByteType        OldDTCStatusOverwritten;
    boolean                      FaultRecordOverwriteFlag;
    boolean                      TSFFDeleteFlag;

} Dem_UpdEvtCtrlFlagStType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetEventCtrlIndexFromEventId
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventID,
    P2VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC, AUTOMATIC ) EventCtrlIndexPtr
);

/*----------------------------------*/
/*  Dem_Control_DisableDTCInfo      */
/*----------------------------------*/
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_Control_GetDisableDTCRecordEvent
( void );
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckDisableDTCInfo
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);

/*----------------------------------*/
/*  Dem_Control_EventEntry          */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SaveEventMemoryEntryToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( void, DEM_CODE ) Dem_Control_UpdateEventMemoryEntryFromTmp
(
    VAR( Dem_u08_EventKindPtnType, AUTOMATIC ) EventKindPattern
);

/*----------------------------------*/
/*  Dem_Control_EventEntry          */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_Control_UpdateEventRelatedData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC )    EventStrgIndex,
    VAR( Dem_EventStatusType, AUTOMATIC )       EventStatus,
    VAR( Dem_MonitorDataType, AUTOMATIC )       monitorData0,
    VAR( boolean, AUTOMATIC )                   FaultOccurrenceFlag,
    VAR( Dem_UdsStatusByteType, AUTOMATIC )     OldDTCStatus,
    VAR( Dem_UdsStatusByteType, AUTOMATIC )     NewDTCStatus,
    VAR( Dem_MisfireCylinderType, AUTOMATIC )   MisfireCylinder
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_ProcessEventRetention
(
    P2CONST( Dem_OrderListOccurredFlagType, AUTOMATIC, AUTOMATIC ) OccurFlagPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )      FaultOccurrenceFlagPtr
);
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Control_NotifyOverwrittenEventStatus
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndexOverwritten,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatusOverwritten
);
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */
#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Control_RemovePrestoredFreezeFrame
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC )    EventStrgIndex,
    VAR( Dem_EventStatusType, AUTOMATIC )       EventStatus,
    VAR( Dem_UdsStatusByteType, AUTOMATIC )     OldDTCStatus,
    VAR( Dem_UdsStatusByteType, AUTOMATIC )     NewDTCStatus
);
#endif  /*   ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )        */

/*----------------------------------*/
/*  Dem_Control_OpCycleUpdNormal    */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_Control_NormalEventMemoryEntryByOpCycle
(
    VAR( Dem_u16_EventPosType, AUTOMATIC ) EventPos,
    VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC ) HealingAgingCycleFlag,
    VAR( Dem_u08_OpcycUpdateFailureCycleType, AUTOMATIC ) FailureCycleFlag,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) NeedGenOrderListPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ExecHealingPtr
);

/*----------------------------------*/
/*  Dem_Control_Specific            */
/*----------------------------------*/
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Control_UpdateSpecificEventMemoryEntryByOpCycle
(
    VAR( Dem_u16_EventPosType, AUTOMATIC ) EventPos,
    VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC ) HealingAgingCycleFlag,
    VAR( Dem_u08_OpcycUpdateFailureCycleType, AUTOMATIC ) FailureCycleFlag,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) NeedGenOrderListPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ExecHealingPtr
);
#endif  /*   ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )   */

/*----------------------------------*/
/*  Dem_Control_Healing             */
/*----------------------------------*/
FUNC( boolean, DEM_CODE ) Dem_Control_ProcessHealing
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) OldDTCStatusStPtr,
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr
);

/*----------------------------------*/
/*  Dem_Control_Aging               */
/*----------------------------------*/
FUNC( boolean, DEM_CODE ) Dem_Control_CheckAgingConditionByEventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( void, DEM_CODE ) Dem_Control_ProcessAging
(
    VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC ) HealingAgingCycleFlag,
    VAR( boolean, AUTOMATIC ) PendingRecoveryExecFlag,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) OldDTCStatusStPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) AgingExecFlagPtr
);
#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Control_ProcessAgingForWWHOBD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) AgingExecFlagPtr
);
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
/*----------------------------------*/
/*  Dem_Control_SpecificEventEntry  */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SaveSpecificEventMemoryEntryToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON ) */

/*----------------------------------*/
/*  Dem_Control_OpCycleUpdCommon    */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_Control_UpdEvtMemEntryOfTmp_AtOpcycUpdate
(
    VAR( Dem_u08_EventKindPtnType, AUTOMATIC ) EventKindPattern,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( boolean, AUTOMATIC ) PendingRecoveryExecFlag,
    VAR( boolean, AUTOMATIC ) AgingExecFlag,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) NeedGenOrderListPtr
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>



/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_CONTROL_LOCAL_H */

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
/****************************************************************************/

/**** End of File ***********************************************************/
