/* Dem_DTR_ReadDTCBased_h(v5-8-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DTR_ReadDTCBased/HEADER                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_DTR_READDTCBASED_H
#define DEM_DTR_READDTCBASED_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../../../cfg/Dem_Cfg.h"

#if ( DEM_DTR_SUPPORT == STD_ON )
#include "../../../cfg/Dem_Dtr_Cfg.h"
#endif  /* ( DEM_DTR_SUPPORT == STD_ON ) */


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_DTR_EDR_SUPPORT == STD_ON )
/*----------------------------------*/
/*  Dem_DTR_ReadDTCBased            */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTR_GetCurrentDTCBasedTestResult
(
    VAR( Dem_u16_DtrOutputEdrTableIndexType, AUTOMATIC ) DtrOutputEdrTableIndex,
    VAR( boolean, AUTOMATIC ) ExecClearDTC,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOriginInClear,
    VAR( uint16, AUTOMATIC ) BufSizeIn,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) TestResultNumPtr,
    P2VAR( uint16, AUTOMATIC, AUTOMATIC ) BufDtrWriteIndexPtr,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) BufferPtr
);
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
/*----------------------------------*/
/*  Dem_DTR_ReadDTCBased_Misfire    */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTR_ReadDTCBasedTestResultForCylinder
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( boolean, AUTOMATIC ) ExecClearDTC,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOriginInClear,
    VAR( uint16, AUTOMATIC ) BufSizeIn,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) TestResultNumPtr,
    P2VAR( uint16, AUTOMATIC, AUTOMATIC ) BufDtrWriteIndexPtr,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) BufferPtr
);
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
#endif  /* ( DEM_DTR_EDR_SUPPORT == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_DTR_READDTCBASED_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
