/* Dem_Utl_h(v5-5-0)                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Utl/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_UTL_H
#define DEM_UTL_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_Data_Cfg.h"
#include "../cfg/Dem_MM_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_UTILMEM_BYTE_INVALID    ((uint8)0xFFU)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------*/
/*  Dem_UtlMem.c                        */
/*--------------------------------------*/
FUNC( void, DEM_CODE ) Dem_UtlMem_SplitByteData
(
    VAR( uint16, AUTOMATIC ) SplitData,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) UpperBytePtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) LowerBytePtr
);
FUNC( uint16, DEM_CODE ) Dem_UtlMem_ConvertByteData
(
    VAR( uint8, AUTOMATIC ) UpperByte,
    VAR( uint8, AUTOMATIC ) LowerByte
);
FUNC( void, DEM_CODE ) Dem_UtlMem_CopyMemory
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2CONST( uint8, AUTOMATIC , DEM_VAR_SAVED_ZONE ) SrcBufferPtr,
    VAR( uint16, AUTOMATIC ) BufSize
);
FUNC( void, DEM_CODE ) Dem_UtlMem_SetMemory
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    VAR( uint8, AUTOMATIC ) CharData,
    VAR( uint16, AUTOMATIC ) Count
);
#if ( DEM_FF_CHECKSUM_SUPPORT == STD_ON)
FUNC( void, DEM_CODE ) Dem_UtlMem_CopyMemoryWithChecksum
(
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) DestBufferPtr,
    P2CONST( uint8, AUTOMATIC , DEM_VAR_NO_INIT ) SrcBufferPtr,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) BufSize,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) PosDataStart,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) PosChecksumUpper,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) PosChecksumLower
);
FUNC( Dem_u16_FFCheckSumType, DEM_CODE ) Dem_UtlMem_Checksum
(
    P2CONST( uint8, AUTOMATIC , DEM_VAR_SAVED_ZONE ) BufferPtr,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) BufSize
);

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_UtlMem_SetChecksum
(
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) BufferPtr,
    VAR( Dem_u16_FFCheckSumType, AUTOMATIC ) Checksum,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) PosChecksumUpper,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) PosChecksumLower
);
#endif /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) */
#endif  /* ( DEM_FF_CHECKSUM_SUPPORT == STD_ON) */

/*--------------------------------------*/
/*  Dem_UtlConsistencyId.c              */
/*--------------------------------------*/
FUNC( Dem_u08_ConsistencyIdType, DEM_CODE ) Dem_UtlCid_CalcConsistencyId
(
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* DEM_UTL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

