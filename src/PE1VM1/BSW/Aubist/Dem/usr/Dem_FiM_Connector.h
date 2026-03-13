/* Dem_FiM_Connector_h(v5-0-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/FiM_Connector/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_FIM_CONNECTOR_H
#define DEM_FIM_CONNECTOR_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )
#include <FiM_Dem.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_FIM_OPSTATUS_INITIAL             FIM_OPSTATUS_INITIAL
#define DEM_FIM_OPSTATUS_PENDING             FIM_OPSTATUS_PENDING

#define DEM_FIM_INITMODE_DEMINIT             FIM_INITMODE_DEMINIT
#define DEM_FIM_INITMODE_OPERATIONCYCLE_ONLY FIM_INITMODE_OPERATIONCYCLE_ONLY
#define DEM_FIM_INITMODE_DTC_CLEAR           FIM_INITMODE_DTC_CLEAR

#define DEM_FIM_E_PENDING                    FIM_E_PENDING


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef FiM_DemInitTriggerType Dem_FiM_DemInitTriggerType;
typedef FiM_OpStatusType       Dem_FiM_OpStatusType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

FUNC( Std_ReturnType, DEM_CODE ) Dem_FiM_DemInit
(
    VAR( Dem_FiM_OpStatusType, AUTOMATIC ) OpStatusType,
    VAR( Dem_FiM_DemInitTriggerType, AUTOMATIC ) TriggerType
);
FUNC( void, DEM_CODE ) Dem_FiM_DemTriggerOnMonitorStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( Dem_MonitorStatusType, AUTOMATIC ) OldMonitorStatus,
    VAR( Dem_MonitorStatusType, AUTOMATIC ) NewMonitorStatus
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CONST
#include <Dem_MemMap.h>

#endif /* ( DEM_TRIGGER_FIM_REPORTS == STD_ON ) */

#endif /* DEM_FIM_CONNECTOR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-09-28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

