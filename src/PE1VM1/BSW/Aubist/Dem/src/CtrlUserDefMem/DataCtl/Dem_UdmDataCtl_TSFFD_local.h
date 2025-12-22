/* Dem_UdmDataCtl_TSFFD_local_h(v5-5-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmDataCtl_TSFFD_local/HEADER                         */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/

#ifndef DEM_UDMDATACTL_TSFFD_LOCAL_H
#define DEM_UDMDATACTL_TSFFD_LOCAL_H

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

FUNC( void, DEM_CODE ) Dem_UdmData_ClearTSFFRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameListRecordIndex
);

FUNC( void, DEM_CODE ) Dem_UdmData_InitCurrentIndexOfTSFFListRecord
(
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) TimeSeriesFreezeFrameRecordClassRef,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameListIndex
);

FUNC( Dem_u16_TSFFListIndexType, DEM_CODE ) Dem_UdmData_UpdateCurrentIndexOfTSFFListRecord
(
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) TimeSeriesFreezeFrameRecordClassRef,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameListIndex
);

FUNC( void, DEM_CODE ) Dem_UdmData_SetCurrentIndexOfTSFFCtrlRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) TimeSeriesFreezeFrameRecordClassRef,
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, AUTOMATIC ) UdmFaultRecordPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_GetCurrentIndexPosOfTSFFListRecord
(
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) TimeSeriesFreezeFrameRecordClassRef,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameListIndex,
    P2VAR( Dem_u08_NumOfTSFFType, AUTOMATIC, AUTOMATIC ) CurrentIndexPosPtr
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

#endif  /* DEM_UDMDATACTL_TSFFD_LOCAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
