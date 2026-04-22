/* Dem_Pm_MonSts_h(v5-3-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Pm_MonSts/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_PM_MONSTS_H
#define DEM_PM_MONSTS_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )
#define DEM_MONSTS_KIND_NONE                    ((Dem_u08_MonStsKindType)0xFF)
#define DEM_MONSTS_KIND_SET_EVENT_STATUS        ((Dem_u08_MonStsKindType)0x00)
#define DEM_MONSTS_KIND_INITILIZE_EVENT_STATUS  ((Dem_u08_MonStsKindType)0x01)
#define DEM_MONSTS_KIND_NORMALIZE_EVENT_STATUS  ((Dem_u08_MonStsKindType)0x02)
#define DEM_MONSTS_KIND_UPDATE_ALL              ((Dem_u08_MonStsKindType)0x03)
#endif /* ( DEM_TRIGGER_FIM_REPORTS == STD_ON ) */

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

FUNC( void, DEM_CODE ) Dem_MonSts_ReCalcStart
(
    VAR( boolean, AUTOMATIC ) ReCalcFlg
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MonSts_ReCalcProc
(
    VAR( Dem_u08_MonStsReCalcType, AUTOMATIC ) InitType
);

#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )
FUNC( void, DEM_CODE ) Dem_MonSts_Init
(void);
FUNC( void, DEM_CODE ) Dem_MonSts_Shutdown
(void);
FUNC( Dem_MonitorStatusType, DEM_CODE ) Dem_MonSts_GetMonitorStatus
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);
FUNC( void, DEM_CODE ) Dem_MonSts_SetSyncMonitorStatus
(
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) Kind,
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    VAR( Dem_u08_DTCSettingStatusType, AUTOMATIC ) DTCSettingStatus
);
FUNC( void, DEM_CODE ) Dem_MonSts_UpdateAllMonitorStatus
(void);
FUNC( void, DEM_CODE ) Dem_MonSts_SetAsyncMonitorStatus
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);
FUNC( void, DEM_CODE ) Dem_MonSts_SetAsyncMonitorStatus_OnOverflow_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( void, DEM_CODE ) Dem_MonSts_SetAsyncUpdateMode
(
    VAR( Dem_u08_MonStsAsyncUpdModeType, AUTOMATIC ) AsyncUpdateMode
);
FUNC( void, DEM_CODE ) Dem_MonSts_ReCalcForOC
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u08_OpcycUpdateFailureCycleType, AUTOMATIC ) FailureCycleFlag
);
FUNC( void, DEM_CODE ) Dem_MonSts_ReCalcForClearDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#if ( DEM_EVENT_AVAILABILITY_FIM_REPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_MonSts_NotifyEventAvailable
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( boolean, AUTOMATIC ) AvailableStatus
);
#endif  /* ( DEM_EVENT_AVAILABILITY_FIM_REPORT == STD_ON ) */
#endif  /* ( DEM_TRIGGER_FIM_REPORTS == STD_ON )        */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* DEM_PM_MONSTS_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
