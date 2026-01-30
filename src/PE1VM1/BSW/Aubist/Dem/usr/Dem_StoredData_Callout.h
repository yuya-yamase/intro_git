/* Dem_StoredData_Callout_h(v5-3-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/StoredData_Callout/HEADER                             */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/

#ifndef DEM_STOREDDATA_CALLOUT_H
#define DEM_STOREDDATA_CALLOUT_H

#if ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_OFF )
/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/* The status definition is in Dem_Types.h */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>


FUNC( void, DEM_CODE_CALLOUT ) Dem_NotifyStartServiceOfDTCStoredData
( void );

FUNC( void, DEM_CODE_CALLOUT ) Dem_NotifyEndServiceOfDTCStoredData
( void );

FUNC( Dem_ReturnGetSizeOfDataByRecNumType, DEM_CODE_CALLOUT ) Dem_GetSizeOfDTCStoredDataByRecordNumber
(
    VAR( uint8, AUTOMATIC ) RecordNumber,
    P2VAR( uint32, AUTOMATIC, AUTOMATIC ) SizeOfStoredDataPtr
);

FUNC( Dem_ReturnGetDTCStoredDataByRecNumType, DEM_CODE_CALLOUT ) Dem_GetDTCStoredDataByRecordNumber
(
    VAR( uint8, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( uint32, AUTOMATIC, AUTOMATIC ) BufSizePtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) NextRecordNumberPtr
);

#define DEM_STOP_SEC_CODE_CALLOUT
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

#endif  /*   ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_OFF )       */

#endif /* DEM_STOREDDATA_CALLOUT_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
