/* Dem_UdmFreezeFrame_h(v5-7-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dem_UdmFreezeFrame/HEADER                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_UDMFREEZEFRAME_H
#define DEM_UDMFREEZEFRAME_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_Rc_UdmMng.h"
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_UDM_OCCURRENCEORDER_UPPER_STORE_SHIFT             ( (uint8)0x10U )
#define DEM_UDM_OCCURRENCEORDER_MIDDLE_STORE_SHIFT            ( (uint8)0x08U )


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>
/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmFFDMng_SetCapturedFreezeFrame
(
#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) StorageFormatDataSize,
#endif  /* DEM_SIT_RANGE_CHECK */
    P2CONST( AB_83_ConstV Dem_UdmFreezeFrameDataPosType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameDataPosTablePtr,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyID,
    P2CONST( Dem_UdmFFRMngInfoType, AUTOMATIC, AUTOMATIC ) UdmFFRMngInfoPtr,
    P2CONST( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) CapturedDataPtr,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) CapturedDataSize,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) StorageFormatDataPtr
);
FUNC( void, DEM_CODE ) Dem_UdmFFDMng_SetMngInfoToFreezeFrame
(
#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) StorageFormatDataSize,
#endif  /* DEM_SIT_RANGE_CHECK */
    P2CONST( AB_83_ConstV Dem_UdmFreezeFrameDataPosType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameDataPosTablePtr,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyID,
    P2CONST( Dem_UdmFFRMngInfoType, AUTOMATIC, DEM_VAR_NO_INIT ) FFRMngInfoPtr,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) StorageFormatDataPtr,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) DataSize
);
FUNC( void, DEM_CODE ) Dem_UdmFFDMng_DisassembleOccurrenceOrder
(
#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) StorageFormatDataSize,
#endif  /* DEM_SIT_RANGE_CHECK */
    P2CONST( AB_83_ConstV Dem_UdmFreezeFrameDataPosType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameDataPosTablePtr,
    VAR( Dem_u32_UdmOccurrenceOrderType, AUTOMATIC ) OccurrenceOrder,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) StorageFormatDataPtr
);

FUNC( Dem_u32_UdmOccurrenceOrderType, DEM_CODE ) Dem_UdmFFDMng_AssembleOccurrenceOrder
(
#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) StorageFormatDataSize,
#endif  /* DEM_SIT_RANGE_CHECK */
    P2CONST( AB_83_ConstV Dem_UdmFreezeFrameDataPosType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameDataPosTablePtr,
    P2CONST( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) StorageFormatDataPtr
);


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */

#endif /* DEM_UDMFREEZEFRAME_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
