/* Dem_CmnLib_DTC_FilDTC_h(v5-5-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/CmnLib_DTC_FilDTC/HEADER                              */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/

#ifndef DEM_CMNLIB_DTC_FILDTC_H
#define DEM_CMNLIB_DTC_FILDTC_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

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

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_CheckDTCAndSeverityForFilter
(
    P2CONST( Dem_SetDTCFilterType, AUTOMATIC, AUTOMATIC ) DTCFilterPtr,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_CheckDTCStatusForFilter
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_CheckDTCSeverityForFilter
(
    VAR( Dem_DTCSeverityType, AUTOMATIC ) DTCSeverityMask,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
)
;

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* DEM_CMNLIB_DTC_FILDTC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
