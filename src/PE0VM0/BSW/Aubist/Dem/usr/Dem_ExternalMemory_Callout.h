/* Dem_ExternalMemory_Callout_h(v5-3-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/ExternalMemory_Callout/HEADER                         */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/
#ifndef DEM_EXTERNALMEMORY_CALLOUT_H
#define DEM_EXTERNALMEMORY_CALLOUT_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8    Dem_ExternalMemReturnType;           /* return value of Callout API */

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*                  Dem_ExternalMemReturnType                        :   uint8   */
#define DEM_EXTERNALMEM_OK                    ((Dem_ExternalMemReturnType)(0x00u))
#define DEM_EXTERNALMEM_PENDING               ((Dem_ExternalMemReturnType)(0x01u))
#define DEM_EXTERNALMEM_NO_MATCHING_ELEMENT   ((Dem_ExternalMemReturnType)(0x02u))
#define DEM_EXTERNALMEM_WRONG_DTC             ((Dem_ExternalMemReturnType)(0x03u))
#define DEM_EXTERNALMEM_WRONG_DTCORIGIN       ((Dem_ExternalMemReturnType)(0x04u))
#define DEM_EXTERNALMEM_WRONG_RECNUM          ((Dem_ExternalMemReturnType)(0x05u))
#define DEM_EXTERNALMEM_BUFFER_TOO_SMALL      ((Dem_ExternalMemReturnType)(0x06u))
#define DEM_EXTERNALMEM_FAILED                ((Dem_ExternalMemReturnType)(0x07u))

#define DEM_EXTERNALMEM_ERRCD_MAX             ((Dem_ExternalMemReturnType)(0x08u))

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

FUNC( Dem_ExternalMemReturnType, DEM_CODE_CALLOUT ) Dem_ExternalMem_SetDTCFilter
(
    VAR( Dem_DTCOriginType,     AUTOMATIC ) DTCOrigin,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusAvailabilityMask
);

FUNC( Dem_ExternalMemReturnType, DEM_CODE_CALLOUT ) Dem_ExternalMem_GetNextFilteredDTC
(
    VAR( Dem_DTCOriginType,         AUTOMATIC ) DTCOrigin,
    VAR( Dem_UdsStatusByteType,     AUTOMATIC ) DTCStatusMask,
    VAR( Dem_UdsStatusByteType,     AUTOMATIC ) DTCStatusAvailabilityMask,
    P2VAR( uint32, AUTOMATIC,       AUTOMATIC ) DTCPtr,
    P2VAR( Dem_UdsStatusByteType,   AUTOMATIC, AUTOMATIC ) StatusOfDTCPtr
);

FUNC( Dem_ExternalMemReturnType, DEM_CODE_CALLOUT ) Dem_ExternalMem_GetStatusOfDTC
(
    VAR( uint32,                    AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType,         AUTOMATIC ) DTCOrigin,
    VAR( Dem_UdsStatusByteType,     AUTOMATIC ) DTCStatusAvailabilityMask,
    P2VAR( Dem_UdsStatusByteType,   AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);

FUNC( Dem_ExternalMemReturnType, DEM_CODE_CALLOUT ) Dem_ExternalMem_StartOfGettingDTCRecord
(
    VAR( uint32,            AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);

FUNC( void, DEM_CODE_CALLOUT ) Dem_ExternalMem_EndOfGettingDTCRecord
(
    VAR( uint32,            AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);

FUNC( Dem_ExternalMemReturnType, DEM_CODE_CALLOUT ) Dem_ExternalMem_GetSizeOfFreezeFrameByDTC
(
    VAR( uint32,                    AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType,         AUTOMATIC ) DTCOrigin,
    VAR( uint8,                     AUTOMATIC ) RecordNumber,
    P2VAR( uint32,                  AUTOMATIC,  AUTOMATIC ) SizeOfFreezeFramePtr
);

FUNC( Dem_ExternalMemReturnType, DEM_CODE_CALLOUT ) Dem_ExternalMem_GetFreezeFrameDataByDTC
(
    VAR( uint32,                    AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType,         AUTOMATIC ) DTCOrigin,
    VAR( uint8,                     AUTOMATIC ) RecordNumber,
    P2VAR( uint8,                   AUTOMATIC,  DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( uint16,                  AUTOMATIC,  AUTOMATIC ) BufSizePtr,
    P2VAR( uint8,                   AUTOMATIC,  AUTOMATIC ) NextRecordNumberPtr
);

FUNC( Dem_ExternalMemReturnType, DEM_CODE_CALLOUT ) Dem_ExternalMem_GetSizeOfExtendedDataRecordByDTC
(
    VAR( uint32,                    AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType,         AUTOMATIC ) DTCOrigin,
    VAR( uint8,                     AUTOMATIC ) ExtendedDataNumber,
    P2VAR( uint16,                  AUTOMATIC,  AUTOMATIC ) SizeOfExtendedDataRecordPtr
);

FUNC( Dem_ExternalMemReturnType, DEM_CODE_CALLOUT ) Dem_ExternalMem_GetExtendedDataRecordByDTC
(
    VAR( uint32,                    AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType,         AUTOMATIC ) DTCOrigin,
    VAR( uint8,                     AUTOMATIC ) ExtendedDataNumber,
    P2VAR( uint8,                   AUTOMATIC,  DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( uint16,                  AUTOMATIC,  AUTOMATIC ) BufSizePtr,
    P2VAR( uint8,                   AUTOMATIC,  AUTOMATIC ) NextExtendedDataNumberPtr
);

#define DEM_STOP_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */

#endif /* DEM_EXTERNALMEMORY_CALLOUT_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
