/* Dem_UdmDataCtl_EventEntry_TSFFD_local_h(v5-3-0)                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmDataCtl_EventEntry_TSFFD_local/HEADER              */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/

#ifndef DEM_UDMDATACTL_EVENTENTRY_TSFFD_LOCAL_H
#define DEM_UDMDATACTL_EVENTENTRY_TSFFD_LOCAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )

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
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*------------------------------------------*/
/*  Dem_UdmDataCtl_EventEntry02Clear_TSFFD  */
/*------------------------------------------*/
FUNC( void, DEM_CODE ) Dem_UdmData_ClearTimeSeriesFreezeFrameRecords
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, AUTOMATIC ) UdmFaultRecordPtr
);

/*------------------------------------------*/
/*  Dem_UdmDataCtl_EventEntry04Regist_TSFFD */
/*------------------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_JudgeOverwriteTSFFRecord
(
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListIndexOverwritten,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndexOverwritten,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndexOverwrite
);
FUNC( void, DEM_CODE ) Dem_UdmData_ClearOverwriteTSFFList
(
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListIndexOverwritten,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndexOverwritten
);
FUNC( void, DEM_CODE ) Dem_UdmData_PrepareStoreTSFFRecordFromSample
(
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListIndexOverwritten
);
FUNC( void, DEM_CODE ) Dem_UdmData_StoreTSFFRecordFromSample
(
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListIndexOverwritten
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


#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */

#endif  /* DEM_UDMDATACTL_EVENTENTRY_TSFFD_LOCAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
