/* Dem_DataMng_GetRecordData_h(v5-5-0)                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/DataMng_GetRecordData/HEADER                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_DATAMNG_GETRECORDDATA_H
#define DEM_DATAMNG_GETRECORDDATA_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_Rc_DataMng.h"


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

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_GetEventIdFromEventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_GetEventStrgIndexFromFaultRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_GetEventStrgIndexFromFFDRecord
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
);
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_GetEventStrgIndexFromObdFFDRecord
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_GetEventStrgIndexFromTSFFDRecord
(
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
);
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )   */

#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif  /* DEM_DATAMNG_GETRECORDDATA_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
