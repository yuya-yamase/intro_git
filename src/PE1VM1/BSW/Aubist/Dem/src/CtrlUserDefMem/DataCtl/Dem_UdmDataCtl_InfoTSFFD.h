/* Dem_UdmDataCtl_InfoTSFFD_h(v5-7-0)                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmDataCtl_InfoTSFFD/HEADER                           */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/

#ifndef DEM_UDMDATACTL_INFOTSFFD_H
#define DEM_UDMDATACTL_INFOTSFFD_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../../../cfg/Dem_NvM_Cfg.h"
#include "../../../cfg/Dem_Data_Cfg.h"

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )

#include "Dem_UdmDataCtl_local.h"

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

FUNC( void, DEM_CODE ) Dem_UdmData_InitTSFFRecordNumber
( void );

FUNC( void, DEM_CODE ) Dem_UdmData_SaveTSFFRecordNumber
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, AUTOMATIC ) UdmFaultRecordPtr
);

FUNC( void, DEM_CODE ) Dem_UdmData_SetNextTSFFRecordNumber
(
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) NextRecordNumberPtr
);
FUNC( Dem_u16_UdmFFDIndexType, DEM_CODE ) Dem_UdmData_GetTSFFStoredRecordNumber
(
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) UdmStoredTSFFRecordNumberPtr
);
FUNC( void, DEM_CODE ) Dem_UdmData_ResetTSFFSearchStartPosition
( void );

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_GetFFDataFromTSFF
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u08_FFDGetInfoType, AUTOMATIC ) FreezeFrameGetInfoType,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DataPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) DataSizePtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_GetAllTSFFRecordNumber
(
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, DEM_APPL_DATA ) RecordNumBufferPtr,
    VAR( uint8, AUTOMATIC ) TotalLengthOfBuffer,
    VAR( uint8, AUTOMATIC ) OffsetPosOfBuffer,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) RecordNumPtr
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

extern VAR( Dem_UdmTmpRecordNumberByDTCType, DEM_VAR_NO_INIT ) Dem_UdmTmpTSFFRecordNumber[DEM_UDM_MAX_NUMBER_TSFF_PER_DTC];

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#endif  /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */

#endif  /* DEM_UDMDATACTL_INFOTSFFD_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
