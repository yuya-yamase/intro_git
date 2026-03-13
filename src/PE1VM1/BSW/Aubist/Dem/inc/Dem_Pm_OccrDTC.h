/* Dem_Pm_OccrDTC_h(v5-3-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Pm_OccrDTC/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_PM_OCCRDTC_H
#define DEM_PM_OCCRDTC_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_Cfg.h"

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

#if ( DEM_TRIGGER_DCM_REPORTS == STD_ON )
FUNC( void, DEM_CODE_TRUST ) Dem_OccrDTC_PreInitNotifyDTCStatusChanged       /*  PreInit section     */
( void );
#endif  /* ( DEM_TRIGGER_DCM_REPORTS == STD_ON )    */

#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OccrDTC_GetDTCByOccurrenceTime
(
    VAR( Dem_DTCRequestType, AUTOMATIC ) DTCRequest,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr
);

FUNC( void, DEM_CODE ) Dem_OccrDTC_Init
( void );
FUNC( void, DEM_CODE ) Dem_OccrDTC_Init_AfterOrderListGenerateComplete
( void );
FUNC( void, DEM_CODE ) Dem_OccrDTC_SetEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndexOfFaultRecordOverwritten,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatus,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) NewDTCStatus,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatusOverwritten,
    VAR( boolean, AUTOMATIC ) FaultRecordOverwriteFlag
);
FUNC( void, DEM_CODE ) Dem_OccrDTC_LatchOccrDTCRecord
( void );
FUNC( void, DEM_CODE ) Dem_OccrDTC_UpdateOccrDTCRecord
( void );

FUNC( void, DEM_CODE ) Dem_OccrDTC_LatchOccrDTCRecord_ClearDTC
( void );
FUNC( void, DEM_CODE ) Dem_OccrDTC_UpdateOccrDTCRecord_ClearDTC
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_u08_ClearCompleteType, AUTOMATIC ) ClearResult
);
FUNC( void, DEM_CODE ) Dem_OccrDTC_UpdateOccrDTCRecord_InitializeEventStatus
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatus,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) NewDTCStatus
);

#endif  /* ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )    */

/*----------------------------------*/
/*  Dem_OccrDTC_TrgDcmReports       */
/*----------------------------------*/
#if ( DEM_TRIGGER_DCM_REPORTS == STD_ON )
FUNC( void, DEM_CODE ) Dem_OccrDTC_ReqNotifyDTCStatusChanged
(
    VAR( boolean, AUTOMATIC ) TriggerNotification
);
#endif  /*   ( DEM_TRIGGER_DCM_REPORTS == STD_ON )      */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>



#endif /* DEM_PM_OCCRDTC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
