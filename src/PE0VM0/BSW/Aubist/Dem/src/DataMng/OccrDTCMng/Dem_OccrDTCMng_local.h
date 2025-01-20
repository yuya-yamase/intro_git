/* Dem_OccrDTCMng_local_h(v5-3-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/OccuDTCMng_local/HEADER                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_OCCRDTCMNG_LOCAL_H
#define DEM_OCCRDTCMNG_LOCAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )

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

FUNC( void, DEM_CODE ) Dem_OccrDTCMng_InitSavedZone_RecordData
(
    P2VAR( Dem_OccrDTCRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) OccrDTCRecordPtr
);

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( void, DEM_CODE ) Dem_OccrDTCMng_SetRecordMirror_RecordData
(
    P2VAR( Dem_OccrDTCRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) OccrDTCRecordPtr,
    P2VAR( Dem_OccrDTCRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) OccrDTCRecordMirrorPtr
);
FUNC( void, DEM_CODE ) Dem_OccrDTCMng_InitMirrorMemory_RecordData
(
    P2VAR( Dem_OccrDTCRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) OccrDTCRecordMirrorPtr
);
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )    */

#endif /* DEM_OCCRDTCMNG_LOCAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
