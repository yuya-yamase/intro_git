/* Dem_CmnLib_OpCycle_h(v5-5-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/CmnLib_OpCycle/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_CMNLIB_OPCYCLE_H
#define DEM_CMNLIB_OPCYCLE_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define     DEM_OPCYCKIND_CFGCYCLE_OTHER    ((uint8)0U)
#define     DEM_OPCYCKIND_CFGCYCLE_IG       ((uint8)1U)
#define     DEM_OPCYCKIND_CFGCYCLE_DCY      ((uint8)2U)
#define     DEM_OPCYCKIND_CFGCYCLE_MAX      ((uint8)3U)

#define     DEM_OPCYCKIND_THISCYCLE_OTHER   ((Dem_u08_OpCycleKindIndexType)0U)
#define     DEM_OPCYCKIND_THISCYCLE_IG      ((Dem_u08_OpCycleKindIndexType)1U)
#define     DEM_OPCYCKIND_THISCYCLE_DCY     ((Dem_u08_OpCycleKindIndexType)2U)
#define     DEM_OPCYCKIND_THISCYCLE_WARMUP  ((Dem_u08_OpCycleKindIndexType)3U)
#define     DEM_OPCYCKIND_THISCYCLE_4CHDCY  ((Dem_u08_OpCycleKindIndexType)4U)
#define     DEM_OPCYCKIND_THISCYCLE_MAX     ((Dem_u08_OpCycleKindIndexType)5U)
#define     DEM_OPCYCKIND_THISCYCLE_INVALID ((Dem_u08_OpCycleKindIndexType)0xFFU)

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

#if ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_OpCycle_NotifyClearRAMData
( void );
#endif  /*   ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )          */

/*--------------------------------------*/
/*  Dem_OpCycle_OpCycIndex.c            */
/*--------------------------------------*/
FUNC( void, DEM_CODE ) Dem_OpCycle_GetRestartOpCycleIndexAreaInOpCycleTable
(
    P2VAR( Dem_u08_OpCycleIndexType, AUTOMATIC, AUTOMATIC ) StartOfOperationCycleIndexPtr,
    P2VAR( Dem_u08_OpCycleIndexType, AUTOMATIC, AUTOMATIC ) MaxOfOperationCycleTableNumPtr
);
FUNC( Dem_u08_OperationCycleIdType, DEM_CODE ) Dem_OpCycle_CnvOpCycleIndexToId
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex
);
FUNC( Dem_u08_OpCycleIndexType, DEM_CODE ) Dem_OpCycle_CnvOpCycleIdToOpCycleIndex
(
    VAR( Dem_u08_OperationCycleIdType, AUTOMATIC ) OperationCycleId
);
#if ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )
FUNC( Dem_u08_CycleQualifiedIndexType, DEM_CODE ) Dem_OpCycle_CnvOpCycleIdToCycleQualifiedIndex
(
    VAR( Dem_u08_OperationCycleIdType, AUTOMATIC ) OperationCycleId
);
#endif  /*   ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )          */

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OpCycle_CheckOpCycleValue
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex
);
#if ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OpCycle_CheckQualifiedCycleValue
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex
);
#endif /* DEM_CYCLEQUALIFIED_SUPPORT -STD_ON- */

/*--------------------------------------*/
/*  Dem_OpCycle_OpCycTable.c            */
/*--------------------------------------*/
FUNC( boolean, DEM_CODE ) Dem_OpCycle_GetOperationCycleAutostart
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex
);

/*--------------------------------------*/
/*  Dem_OpCycle_CheckCycleKind.c        */
/*--------------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OpCycle_GetNextEventPosByOperationCycleIndex
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex,
    VAR( Dem_u16_EventPosType, AUTOMATIC ) BaseEventPos,
    P2VAR( Dem_u16_EventPosType, AUTOMATIC, AUTOMATIC ) NextEventPosPtr,
    P2VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC, AUTOMATIC ) HealingAgingCycleFlagPtr,
    P2VAR( Dem_u08_OpcycUpdateFailureCycleType, AUTOMATIC, AUTOMATIC ) FailureCycleFlagPtr
);

FUNC( Dem_u08_OpCycleKindIndexType, DEM_CODE ) Dem_OpCycle_GetCycleKindTableThisCycleIndex
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC )  ThisCycleIndex,
    VAR( Dem_u08_OpCycleKindType, AUTOMATIC )   ThisCycleKind,
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) ObdDcyCycleState,
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) WarmUpCycleState
);

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
FUNC( Dem_u08_OpCycleKindIndexType, DEM_CODE ) Dem_OpCycle_GetThisCycleKindIndex
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex
);
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_OFF ) */

/*--------------------------------------*/
/*  Dem_OpCycle_CycleQualified.c        */
/*--------------------------------------*/
#if ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_OpCycle_GetIGCycleQualified
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) IGCycleUpdatedPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) OBDDCYQualifiedPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) WarmUpQualifiedPtr
);
FUNC( void, DEM_CODE ) Dem_OpCycle_ResetObdDcyCycleQualified
( void );

FUNC( void, DEM_CODE ) Dem_OpCycle_SetCycleStartNoticeFlag
(
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) CycleQualifiedIndex,
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) CycleState
);
FUNC( Dem_OperationCycleStateType, DEM_CODE ) Dem_OpCycle_GetCycleStartNoticeFlag
(
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) CycleQualifiedIndex
);
#endif /* DEM_CYCLEQUALIFIED_SUPPORT -STD_ON- */

/*--------------------------------------*/
/*  Dem_OpCycle_4hDCY.c                 */
/*--------------------------------------*/
#if ( DEM_ENGINETYPE_COMPRESSION_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_OpCycle_Check4hDCY
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex
);
#endif  /* ( DEM_ENGINETYPE_COMPRESSION_SUPPORT == STD_ON ) */

/*--------------------------------------*/
/*  Dem_OpCycle_ProgressEngineRPM.c     */
/*--------------------------------------*/
#if ( DEM_CHECK_4000RPMOCCURRED_BY_EMISSION_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_OpCycle_ClearProgressEngine1000RPM
( void );
FUNC( void, DEM_CODE ) Dem_OpCycle_UpdateProgressEngine1000RPM
( void );
#endif  /* ( DEM_CHECK_4000RPMOCCURRED_BY_EMISSION_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>



#endif /* DEM_CMNLIB_OPCYCLE_H */

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
