/* Dem_DataMng_FreezeFrame_c(v5-5-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataMng_FreezeFrame/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "Dem_DataMng_FreezeFrame.h"
#include "../../../inc/Dem_Utl.h"
#include "../../../cfg/Dem_Data_Cfg.h"
#include "../../../cfg/Dem_MM_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
static FUNC( void, DEM_CODE ) Dem_DataMng_SetCapturedFFD
(
    P2CONST( AB_83_ConstV Dem_FreezeFrameDataPosType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameDataPosTablePtr,
    P2CONST( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) CapturedDataPtr,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) CapturedDataSize,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) StorageFormatDataPtr
);

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_DataMng_SetCapturedFreezeFrame                       */
/* Description   | Sets the captured freeze frame data record to storage f- */
/*               | ormat.                                                   */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameDataPosTablePtr :                        */
/*               |        The position information of freeze frame data.    */
/*               | [in] ConsistencyID :                                     */
/*               |        The ID for  consistency.                          */
/*               | [in] EventIndex :                                        */
/*               |        The index of Event record to be stored.           */
/*               | [in] RecordStatus :                                      */
/*               |        Memory state.                                     */
/*               | [in] CapturedDataPtr :                                   */
/*               |         &Dem_TmpEventMemoryEntry.FreezeFrameRecordList[].Data */
/*               |         AUTOMATIC                                        */
/*               |        The buffer of the captured freeze frame data rec- */
/*               |        ord.                                              */
/*               | [in] CapturedDataSize :                                  */
/*               |        The size of the captured freeze frame data recor- */
/*               |        d.                                                */
/*               | [out] StorageFormatDataPtr :                             */
/*               |         &Dem_FreezeFrameRecordList[].Data                */
/*               |         &Dem_TimeSeriesFreezeFrameRecordList[].Data      */
/*               |        The storage location of the freeze frame data re- */
/*               |        cord with storage format.                         */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMng_SetCapturedFreezeFrame
(
    P2CONST( AB_83_ConstV Dem_FreezeFrameDataPosType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameDataPosTablePtr,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyID,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFStoredStatusType, AUTOMATIC ) RecordStatus,
    P2CONST( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) CapturedDataPtr,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) CapturedDataSize,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) StorageFormatDataPtr
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstCID;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastCID;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastEventStrgIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastEventStrgIndexLower;
    VAR( uint8, AUTOMATIC ) eventStrgIndexUpper;
    VAR( uint8, AUTOMATIC ) eventStrgIndexLower;

    posFirstCID = FreezeFrameDataPosTablePtr->FirstCID;
    posLastCID = FreezeFrameDataPosTablePtr->LastCID;
    posFirstEventStrgIndexUpper = FreezeFrameDataPosTablePtr->FirstEventStrgIndexUpper;
    posFirstEventStrgIndexLower = FreezeFrameDataPosTablePtr->FirstEventStrgIndexLower;
    posLastEventStrgIndexUpper = FreezeFrameDataPosTablePtr->LastEventStrgIndexUpper;
    posLastEventStrgIndexLower = FreezeFrameDataPosTablePtr->LastEventStrgIndexLower;
    posRecordStatus = FreezeFrameDataPosTablePtr->RecordStatus;

    /* Stores the specified consistency ID. */
    StorageFormatDataPtr[posFirstCID] = (uint8)ConsistencyID;
    StorageFormatDataPtr[posLastCID] = (uint8)ConsistencyID;

    /* Stores the specified event index. */
    eventStrgIndexUpper = DEM_UTILMEM_BYTE_INVALID;
    eventStrgIndexLower = DEM_UTILMEM_BYTE_INVALID;
    Dem_UtlMem_SplitByteData( (uint16)EventStrgIndex, &eventStrgIndexUpper, &eventStrgIndexLower );
    StorageFormatDataPtr[posFirstEventStrgIndexUpper] = eventStrgIndexUpper;
    StorageFormatDataPtr[posFirstEventStrgIndexLower] = eventStrgIndexLower;
    StorageFormatDataPtr[posLastEventStrgIndexUpper] = eventStrgIndexUpper;
    StorageFormatDataPtr[posLastEventStrgIndexLower] = eventStrgIndexLower;

    /* Stores the specified record status. */
    StorageFormatDataPtr[posRecordStatus] = (uint8)RecordStatus;

    /* Stores the specified freeze frame data.  */
    Dem_DataMng_SetCapturedFFD( FreezeFrameDataPosTablePtr, CapturedDataPtr, CapturedDataSize, StorageFormatDataPtr );

    return;
}

/****************************************************************************/
/* Function Name | Dem_DataMng_SetCapturedFFD                               */
/* Description   | Sets the captured freeze frame data to storage format.   */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameDataPosTablePtr :                        */
/*               |        The position information of freeze frame data.    */
/*               | [in] CapturedDataPtr :                                   */
/*               |         &Dem_TmpEventMemoryEntry.FreezeFrameRecordList[].Data */
/*               |         AUTOMATIC                                        */
/*               |        The buffer of the captured freeze frame data rec- */
/*               |        ord.                                              */
/*               | [in] CapturedDataSize :                                  */
/*               |        The size of the captured freeze frame data recor- */
/*               |        d.                                                */
/*               | [out] StorageFormatDataPtr :                             */
/*               |         &Dem_FreezeFrameRecordList[].Data                */
/*               |         &Dem_TimeSeriesFreezeFrameRecordList[].Data      */
/*               |        The storage location of the freeze frame data re- */
/*               |        cord with storage format.                         */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
#if ( DEM_FF_CHECKSUM_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_DataMng_SetCapturedFFD
(
    P2CONST( AB_83_ConstV Dem_FreezeFrameDataPosType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameDataPosTablePtr,
    P2CONST( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) CapturedDataPtr,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) CapturedDataSize,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) StorageFormatDataPtr
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posDataStart;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posChecksumUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posChecksumLower;

    posDataStart = FreezeFrameDataPosTablePtr->DataStart;
    posChecksumUpper = FreezeFrameDataPosTablePtr->ChecksumUpper;
    posChecksumLower = FreezeFrameDataPosTablePtr->ChecksumLower;

    /* Stores the specified freeze frame data with checksum.  */
    Dem_UtlMem_CopyMemoryWithChecksum( StorageFormatDataPtr, CapturedDataPtr, CapturedDataSize, posDataStart, posChecksumUpper, posChecksumLower );

    return;
}
#endif  /* ( DEM_FF_CHECKSUM_SUPPORT == STD_ON ) */
#if ( DEM_FF_CHECKSUM_SUPPORT == STD_OFF )
static FUNC( void, DEM_CODE ) Dem_DataMng_SetCapturedFFD
(
    P2CONST( AB_83_ConstV Dem_FreezeFrameDataPosType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameDataPosTablePtr,
    P2CONST( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) CapturedDataPtr,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) CapturedDataSize,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) StorageFormatDataPtr
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posDataStart;

    posDataStart = FreezeFrameDataPosTablePtr->DataStart;

    /* Stores the specified freeze frame data.  */
    Dem_UtlMem_CopyMemory( &StorageFormatDataPtr[posDataStart], CapturedDataPtr, CapturedDataSize );

    return;
}
#endif  /* ( DEM_FF_CHECKSUM_SUPPORT == STD_OFF ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
