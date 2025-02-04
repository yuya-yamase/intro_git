/* Dem_UdmFreezeFrame_c(v5-5-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmFreezeFrame/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../../../cfg/Dem_Data_Cfg.h"
#include "../../../inc/Dem_Utl.h"
#include "../../../inc/Dem_Rc_UdmFFRecordTable.h"
#include "../../../inc/Dem_Rc_UdmMng_rc.h"
#include "Dem_UdmFreezeFrame.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )

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

static FUNC( void, DEM_CODE ) Dem_UdmFFDMng_SetCapturedFFD
(
    P2CONST( AB_83_ConstV Dem_UdmFreezeFrameDataPosType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameDataPosTablePtr,
    P2CONST( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) CapturedDataPtr,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) CapturedDataSize,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) StorageFormatDataPtr
);

#if ( DEM_FF_CHECKSUM_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_UdmFFDMng_SetChecksum
(
    P2CONST( AB_83_ConstV Dem_UdmFreezeFrameDataPosType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameDataPosTablePtr,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) StorageFormatDataPtr,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) DataSize
);
#endif  /* ( DEM_FF_CHECKSUM_SUPPORT == STD_ON ) */

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
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_SetCapturedFreezeFrame                     */
/* Description   | Sets the captured freeze frame data record to storage f- */
/*               | ormat.                                                   */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameDataPosTablePtr :                        */
/*               |        The position information of freeze frame data.    */
/*               | [in] ConsistencyID :                                     */
/*               |        The ID for  consistency.                          */
/*               | [in] UdmFFRMngInfoPtr                                    */
/*               |        It includes UdmFaultIndex, CidUdmFreezeFrameReco- */
/*               |        rds, OccurrenceOrder, RecordStatus.               */
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
FUNC( void, DEM_CODE ) Dem_UdmFFDMng_SetCapturedFreezeFrame
(
    P2CONST( AB_83_ConstV Dem_UdmFreezeFrameDataPosType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameDataPosTablePtr,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyID,
    P2CONST( Dem_UdmFFRMngInfoType, AUTOMATIC, AUTOMATIC ) UdmFFRMngInfoPtr,
    P2CONST( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) CapturedDataPtr,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) CapturedDataSize,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) StorageFormatDataPtr
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstCID;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastCID;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstUdmEventIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstUdmEventIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastUdmEventIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastUdmEventIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posCidUdmFreezeFrameRecords;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posOffsetOfTSFFListIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;
    VAR( uint8, AUTOMATIC ) udmEventIndexUpper;
    VAR( uint8, AUTOMATIC ) udmEventIndexLower;

    posFirstCID = FreezeFrameDataPosTablePtr->FirstCID;
    posLastCID = FreezeFrameDataPosTablePtr->LastCID;
    posFirstUdmEventIndexUpper = FreezeFrameDataPosTablePtr->FirstUdmEventIndexUpper;
    posFirstUdmEventIndexLower = FreezeFrameDataPosTablePtr->FirstUdmEventIndexLower;
    posLastUdmEventIndexUpper = FreezeFrameDataPosTablePtr->LastUdmEventIndexUpper;
    posLastUdmEventIndexLower = FreezeFrameDataPosTablePtr->LastUdmEventIndexLower;
    posCidUdmFreezeFrameRecords = FreezeFrameDataPosTablePtr->CidUdmFreezeFrameRecords;
    posOffsetOfTSFFListIndex = FreezeFrameDataPosTablePtr->OffsetOfTSFFListIndex;
    posRecordStatus = FreezeFrameDataPosTablePtr->RecordStatus;

    if ( posRecordStatus != DEM_FFDSTOREDINDEX_INVALID )
    {
        /* Stores the specified consistency ID. */
        StorageFormatDataPtr[posFirstCID] = (uint8)ConsistencyID;
        StorageFormatDataPtr[posLastCID] = (uint8)ConsistencyID;

        /* Stores the specified event index. */
        udmEventIndexUpper = DEM_UTILMEM_BYTE_INVALID;
        udmEventIndexLower = DEM_UTILMEM_BYTE_INVALID;
        Dem_UtlMem_SplitByteData( (uint16)(UdmFFRMngInfoPtr->UdmEventIndex), &udmEventIndexUpper, &udmEventIndexLower );
        StorageFormatDataPtr[posFirstUdmEventIndexUpper] = udmEventIndexUpper;
        StorageFormatDataPtr[posFirstUdmEventIndexLower] = udmEventIndexLower;
        StorageFormatDataPtr[posLastUdmEventIndexUpper] = udmEventIndexUpper;
        StorageFormatDataPtr[posLastUdmEventIndexLower] = udmEventIndexLower;

        /* Stores the consistency ID between udm freeze frame records. */
        StorageFormatDataPtr[posCidUdmFreezeFrameRecords] = (uint8)UdmFFRMngInfoPtr->CidUdmFreezeFrameRecords;

        /* Stores the specified occurrence order. */
        Dem_UdmFFDMng_DisassembleOccurrenceOrder( FreezeFrameDataPosTablePtr, UdmFFRMngInfoPtr->OccurrenceOrder, StorageFormatDataPtr );

        if( posOffsetOfTSFFListIndex != DEM_FFDSTOREDINDEX_INVALID )
        {
            /* Stores the specified offset of time-series freeze frame list record's index. */
            StorageFormatDataPtr[posOffsetOfTSFFListIndex] = (uint8)UdmFFRMngInfoPtr->OffsetOfTSFFListIndex;
        }

        /* Stores the specified record status. */
        StorageFormatDataPtr[posRecordStatus] = (uint8)UdmFFRMngInfoPtr->RecordStatus;

        /* Stores the specified freeze frame data.  */
        Dem_UdmFFDMng_SetCapturedFFD( FreezeFrameDataPosTablePtr, CapturedDataPtr, CapturedDataSize, StorageFormatDataPtr );
    }
    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_SetMngInfoToFreezeFrame                    */
/* Description   | Sets the captured freeze frame data record to storage f- */
/*               | ormat.                                                   */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameDataPosTablePtr :                        */
/*               |        The position information of freeze frame data.    */
/*               | [in] ConsistencyID :                                     */
/*               |        The ID for  consistency.                          */
/*               | [in] UdmEventIndex :                                     */
/*               |        The index of udm event record to be stored.       */
/*               | [in] OccurrenceOrder :                                   */
/*               |        Occurrence order of fault.                        */
/*               | [in] RecordStatus :                                      */
/*               |        Memory state.                                     */
/*               | [in] StorageFormatDataPtr :                              */
/*               |         &Dem_FreezeFrameRecordList[].Data                */
/*               |         &Dem_TimeSeriesFreezeFrameRecordList[].Data      */
/*               |        The storage location of the freeze frame data re- */
/*               |        cord with storage format.                         */
/*               | [in] DataSize :                                          */
/*               |        The size of the captured freeze frame data recor- */
/*               |        d.                                                */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmFFDMng_SetMngInfoToFreezeFrame
(
    P2CONST( AB_83_ConstV Dem_UdmFreezeFrameDataPosType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameDataPosTablePtr,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyID,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) CidUdmFreezeFrameRecords,
    VAR( Dem_u32_UdmOccurrenceOrderType, AUTOMATIC ) OccurrenceOrder,
    VAR( Dem_u08_FFStoredStatusType, AUTOMATIC ) RecordStatus,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) StorageFormatDataPtr,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) DataSize       /* MISRA DEVIATION */
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstCID;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastCID;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstUdmEventIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstUdmEventIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastUdmEventIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastUdmEventIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posCidUdmFreezeFrameRecords;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;
    VAR( uint8, AUTOMATIC ) udmEventIndexUpper;
    VAR( uint8, AUTOMATIC ) udmEventIndexLower;

    posFirstCID = FreezeFrameDataPosTablePtr->FirstCID;
    posLastCID = FreezeFrameDataPosTablePtr->LastCID;
    posFirstUdmEventIndexUpper = FreezeFrameDataPosTablePtr->FirstUdmEventIndexUpper;
    posFirstUdmEventIndexLower = FreezeFrameDataPosTablePtr->FirstUdmEventIndexLower;
    posLastUdmEventIndexUpper = FreezeFrameDataPosTablePtr->LastUdmEventIndexUpper;
    posLastUdmEventIndexLower = FreezeFrameDataPosTablePtr->LastUdmEventIndexLower;
    posCidUdmFreezeFrameRecords = FreezeFrameDataPosTablePtr->CidUdmFreezeFrameRecords;
    posRecordStatus = FreezeFrameDataPosTablePtr->RecordStatus;

    /*  check available data of Dem_UdmFreezeFrameDataPosTable[]    */
    if ( posRecordStatus != DEM_FFDSTOREDINDEX_INVALID )
    {
        /* Stores the specified consistency ID. */
        StorageFormatDataPtr[posFirstCID] = (uint8)ConsistencyID;
        StorageFormatDataPtr[posLastCID] = (uint8)ConsistencyID;

        /* Stores the specified event index. */
        udmEventIndexUpper = DEM_UTILMEM_BYTE_INVALID;
        udmEventIndexLower = DEM_UTILMEM_BYTE_INVALID;
        Dem_UtlMem_SplitByteData( (uint16)UdmEventIndex, &udmEventIndexUpper, &udmEventIndexLower );
        StorageFormatDataPtr[posFirstUdmEventIndexUpper] = udmEventIndexUpper;
        StorageFormatDataPtr[posFirstUdmEventIndexLower] = udmEventIndexLower;
        StorageFormatDataPtr[posLastUdmEventIndexUpper] = udmEventIndexUpper;
        StorageFormatDataPtr[posLastUdmEventIndexLower] = udmEventIndexLower;


        /* Stores the consistency ID between udm freeze frame records. */
        StorageFormatDataPtr[posCidUdmFreezeFrameRecords] = (uint8)CidUdmFreezeFrameRecords;

        /* Stores the specified occurrence order. */
        Dem_UdmFFDMng_DisassembleOccurrenceOrder( FreezeFrameDataPosTablePtr, OccurrenceOrder, StorageFormatDataPtr );

        /* Stores the specified record status. */
        StorageFormatDataPtr[posRecordStatus] = (uint8)RecordStatus;

#if ( DEM_FF_CHECKSUM_SUPPORT == STD_ON )    /* [FuncSw] */
        Dem_UdmFFDMng_SetChecksum( FreezeFrameDataPosTablePtr, StorageFormatDataPtr, DataSize );
#endif  /* ( DEM_FF_CHECKSUM_SUPPORT == STD_ON ) */
    }
    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_DisassembleOccurrenceOrder                 */
/* Description   | Disassembles occurrence order to storage format.         */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameDataPosTablePtr :                        */
/*               |        The position information of freeze frame data.    */
/*               | [in] OccurrenceOrder :                                   */
/*               |        Occurrence order of fault.                        */
/*               | [out] StorageFormatDataPtr :                             */
/*               |        The storage location of the freeze frame data re- */
/*               |        cord with storage format.                         */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmFFDMng_DisassembleOccurrenceOrder
(
    P2CONST( AB_83_ConstV Dem_UdmFreezeFrameDataPosType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameDataPosTablePtr,
    VAR( Dem_u32_UdmOccurrenceOrderType, AUTOMATIC ) OccurrenceOrder,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) StorageFormatDataPtr
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posOccurrenceOrderUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posOccurrenceOrderMiddle;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posOccurrenceOrderLower;

    posOccurrenceOrderUpper = FreezeFrameDataPosTablePtr->OccurrenceOrderUpper;
    posOccurrenceOrderMiddle = FreezeFrameDataPosTablePtr->OccurrenceOrderMiddle;
    posOccurrenceOrderLower = FreezeFrameDataPosTablePtr->OccurrenceOrderLower;

    /*  check available data of Dem_UdmFreezeFrameDataPosTable[]    */
    if ( posOccurrenceOrderUpper != DEM_FFDSTOREDINDEX_INVALID )
    {
        StorageFormatDataPtr[posOccurrenceOrderUpper] = (uint8)( OccurrenceOrder >> DEM_UDM_OCCURRENCEORDER_UPPER_STORE_SHIFT );
        StorageFormatDataPtr[posOccurrenceOrderMiddle] = (uint8)( OccurrenceOrder >> DEM_UDM_OCCURRENCEORDER_MIDDLE_STORE_SHIFT );
        StorageFormatDataPtr[posOccurrenceOrderLower] = (uint8)OccurrenceOrder;
    }
    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_AssembleOccurrenceOrder                    */
/* Description   | Assembles occurrence order from storage format.          */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameDataPosTablePtr :                        */
/*               |        The position information of freeze frame data.    */
/*               | [in] StorageFormatDataPtr :                              */
/*               |        The storage location of the freeze frame data re- */
/*               |        cord with storage format.                         */
/* Return Value  | Dem_u32_UdmOccurrenceOrderType                           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u32_UdmOccurrenceOrderType, DEM_CODE ) Dem_UdmFFDMng_AssembleOccurrenceOrder
(
    P2CONST( AB_83_ConstV Dem_UdmFreezeFrameDataPosType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameDataPosTablePtr,
    P2CONST( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) StorageFormatDataPtr
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posOccurrenceOrderUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posOccurrenceOrderMiddle;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posOccurrenceOrderLower;
    VAR( Dem_u32_UdmOccurrenceOrderType, AUTOMATIC ) occurrenceOrder;

    posOccurrenceOrderUpper = FreezeFrameDataPosTablePtr->OccurrenceOrderUpper;
    posOccurrenceOrderMiddle = FreezeFrameDataPosTablePtr->OccurrenceOrderMiddle;
    posOccurrenceOrderLower = FreezeFrameDataPosTablePtr->OccurrenceOrderLower;

    occurrenceOrder =   DEM_UDMOCCURRENCEORDER_INITIAL;
    /*  check available data of Dem_UdmFreezeFrameDataPosTable[]    */
    if ( posOccurrenceOrderUpper != DEM_FFDSTOREDINDEX_INVALID )
    {
        occurrenceOrder = (Dem_u32_UdmOccurrenceOrderType)StorageFormatDataPtr[posOccurrenceOrderUpper] << DEM_UDM_OCCURRENCEORDER_UPPER_STORE_SHIFT;
        occurrenceOrder |= (Dem_u32_UdmOccurrenceOrderType)StorageFormatDataPtr[posOccurrenceOrderMiddle] << DEM_UDM_OCCURRENCEORDER_MIDDLE_STORE_SHIFT;
        occurrenceOrder |= (Dem_u32_UdmOccurrenceOrderType)StorageFormatDataPtr[posOccurrenceOrderLower];
    }
    return occurrenceOrder;
}


/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_SetCapturedFFD                             */
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
static FUNC( void, DEM_CODE ) Dem_UdmFFDMng_SetCapturedFFD
(
    P2CONST( AB_83_ConstV Dem_UdmFreezeFrameDataPosType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameDataPosTablePtr,
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
    /*  check available data of Dem_UdmFreezeFrameDataPosTable[]    */
    if ( posDataStart != DEM_FFDSTOREDINDEX_INVALID )
    {
        Dem_UtlMem_CopyMemoryWithChecksum( StorageFormatDataPtr, CapturedDataPtr, CapturedDataSize, posDataStart, posChecksumUpper, posChecksumLower );
    }
    return;
}
#endif  /* ( DEM_FF_CHECKSUM_SUPPORT == STD_ON ) */
#if ( DEM_FF_CHECKSUM_SUPPORT == STD_OFF )
static FUNC( void, DEM_CODE ) Dem_UdmFFDMng_SetCapturedFFD
(
    P2CONST( AB_83_ConstV Dem_UdmFreezeFrameDataPosType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameDataPosTablePtr,
    P2CONST( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) CapturedDataPtr,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) CapturedDataSize,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) StorageFormatDataPtr
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posDataStart;

    posDataStart = FreezeFrameDataPosTablePtr->DataStart;

    /*  check available data of Dem_UdmFreezeFrameDataPosTable[]    */
    if ( posDataStart != DEM_FFDSTOREDINDEX_INVALID )
    {
        /* Stores the specified freeze frame data.  */
        Dem_UtlMem_CopyMemory( &StorageFormatDataPtr[posDataStart], CapturedDataPtr, CapturedDataSize );
    }
    return;
}
#endif  /* ( DEM_FF_CHECKSUM_SUPPORT == STD_OFF ) */


#if ( DEM_FF_CHECKSUM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_SetChecksum                                */
/* Description   | Set checksum to freeze frame data.                       */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameDataPosTablePtr :                        */
/*               |        The position information of freeze frame data.    */
/*               | [out] StorageFormatDataPtr :                             */
/*               |         &Dem_FreezeFrameRecordList[].Data                */
/*               |         &Dem_TimeSeriesFreezeFrameRecordList[].Data      */
/*               |        The storage location of the freeze frame data re- */
/*               |        cord with storage format.                         */
/*               | [in] DataSize :                                          */
/*               |        The size of the captured freeze frame data recor- */
/*               |        d.                                                */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmFFDMng_SetChecksum
(
    P2CONST( AB_83_ConstV Dem_UdmFreezeFrameDataPosType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameDataPosTablePtr,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) StorageFormatDataPtr,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) DataSize
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posDataStart;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posChecksumUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posChecksumLower;
    VAR( Dem_u16_FFCheckSumType, AUTOMATIC ) calculatedChecksum;

    posDataStart = FreezeFrameDataPosTablePtr->DataStart;
    posChecksumUpper = FreezeFrameDataPosTablePtr->ChecksumUpper;
    posChecksumLower = FreezeFrameDataPosTablePtr->ChecksumLower;

    /*  check available data of Dem_UdmFreezeFrameDataPosTable[]    */
    if ( posDataStart != DEM_FFDSTOREDINDEX_INVALID )
    {
        calculatedChecksum = Dem_UtlMem_Checksum( &StorageFormatDataPtr[posDataStart], DataSize );

        Dem_UtlMem_SetChecksum( StorageFormatDataPtr, calculatedChecksum, posChecksumUpper, posChecksumLower );
    }
    return;
}
#endif  /* ( DEM_FF_CHECKSUM_SUPPORT == STD_ON ) */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
