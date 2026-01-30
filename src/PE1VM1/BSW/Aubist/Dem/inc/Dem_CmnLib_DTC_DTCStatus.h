/* Dem_CmnLib_DTC_DTCStatus_h(v5-9-0)                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/CmnLib_DTC_DTCStatus/HEADER                           */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/

#ifndef DEM_CMNLIB_DTC_DTCSTATUS_H
#define DEM_CMNLIB_DTC_DTCSTATUS_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*==================================*/
/*  DTCStatus                       */
/*==================================*/
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_DTC_CheckDTCStatus
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusBitOnMask
);
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON ) */

/*----------------------------------*/
/*  DTCStatus   : package access    */
/*----------------------------------*/
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_SetNormalizeDTCStatus
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
);
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_SetPassedDTCStatus
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
);
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_SetFailedDTCStatus
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
);
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_SetFailedDTCStatusForSyncEventEntry
( void );
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_ResetAllConfirmedDTCStatus_OnOverflow
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
);
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_ResetConfirmedDTCAndWIRStatus_AtAging
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
);
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_ResetConfirmedDTCAndPendingDTCStatus_AtAging
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
);

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_ResetConfirmedDTCStatus_AtAging
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
);
#endif  /*  ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )    */

FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_RestartOperationCycleDTCStatus
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus,
    VAR( Dem_u08_OpcycUpdateFailureCycleType, AUTOMATIC ) FailureCycleFlag
);

/*----------------------------------*/
/*  DTCStatus   : bit access        */
/*----------------------------------*/
/* Bit2         */
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_ResetPendingDTCBit
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
);

/* Bit3         */
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_SetConfirmedDTCBit
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
);

/* Bit7         */
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_SetWIRStatusBit
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
);
#if ( DEM_INDICATOR_USE == STD_ON )
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_ResetWIRStatusBit
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
);
#endif  /* ( DEM_INDICATOR_USE == STD_ON )  */

/*==================================*/
/*  Extend DTCStatus                */
/*==================================*/
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_DTC_CheckExtendDTCStatus
(
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatus,
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatusBitOnMask
);
#endif  /*   ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )   */

/* Dem_DTC_ExtendDTCStatus.c */
FUNC( Dem_u08_DTCStatusExType, DEM_CODE ) Dem_DTC_ExDTC_ResetIndicatorBit
(
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatus
);
FUNC( Dem_u08_DTCStatusExType, DEM_CODE ) Dem_DTC_ExDTC_ResetIndicatorBit_OnOverflow
(
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatus
);
FUNC( Dem_u08_DTCStatusExType, DEM_CODE ) Dem_DTC_ExDTC_SetIndicatorAndConfirmedHistoryBit
(
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatus
);
FUNC( Dem_u08_DTCStatusExType, DEM_CODE ) Dem_DTC_ExDTC_SetConfirmedHistoryBit
(
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatus
);

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
FUNC( Dem_u08_DTCStatusExType, DEM_CODE ) Dem_DTC_ExDTC_ResetPredictiveFaultBit
(
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatus
);
FUNC( Dem_u08_DTCStatusExType, DEM_CODE ) Dem_DTC_ExDTC_ResetPredictiveFaultBit_OnOverflow
(
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatus
);
FUNC( Dem_u08_DTCStatusExType, DEM_CODE ) Dem_DTC_ExDTC_SetPredictiveFaultBit
(
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatus
);
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )    */

FUNC( Dem_u08_DTCStatusExType, DEM_CODE ) Dem_DTC_ExDTC_SetNormalizeExDTCStatus
(
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatus
);
FUNC( Dem_u08_DTCStatusExType, DEM_CODE ) Dem_DTC_ExDTC_SetPassedExDTCStatus
(
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatus
);
FUNC( Dem_u08_DTCStatusExType, DEM_CODE ) Dem_DTC_ExDTC_SetFailedExDTCStatus
(
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatus
);
FUNC( Dem_u08_DTCStatusExType, DEM_CODE ) Dem_DTC_ExDTC_RestartHealingAgingCycleExDTCStatus
(
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatus,
    VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC ) HealingAgingCycleFlag
);
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_SetNormalizeExDTCStatus
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2
);
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_ResetContMIHistAndIndAtCycleStartBit
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2
);
#if ( DEM_INDICATOR_USE == STD_ON )
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_ResetContinuousMIHistoryBit
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2
);
#endif  /* ( DEM_INDICATOR_USE == STD_ON )  */
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_SetPassedExDTCStatus
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2
);
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_SetFailedExDTCStatus
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2
);
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_RestartHealingAgingCycleExDTCStatus
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2,
    VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC ) HealingAgingCycleFlag
);
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_RestartOperationCycleExDTCStatus
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2,
    VAR( Dem_u08_OpcycUpdateFailureCycleType, AUTOMATIC ) FailureCycleFlag
);
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_SetAgingHistory
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2
);
#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_SetEventDisable
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2
);
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_ClearEventDisable
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2
);
#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON )    */

FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_SetIndicatorAtCycleStart
(
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatus,
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2
);
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_SetContinuousMIHistoryBit
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2
);
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_ResetContMIHistAndIndAtCycleStartBit_OnOverflow
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2
);
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_SetPendingOfEmission
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2
);
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_ResetPendingOfEmission
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2
);
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   */

/*==================================*/
/*  Convert to output DTCStatus     */
/*==================================*/
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_CnvDTCStatus_PmAvailabilityMask
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
);
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_CnvDTCStatus_ForOutput
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
);
FUNC( void, DEM_CODE ) Dem_DTC_CnvUpdateDTCStatus_ForOutput
(
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) OldDTCStatusPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) NewDTCStatusPtr
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* DEM_CMNLIB_DTC_DTCSTATUS_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
