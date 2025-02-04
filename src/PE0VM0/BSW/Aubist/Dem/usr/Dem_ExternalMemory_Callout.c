/* Dem_ExternalMemory_Callout_c(v5-3-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/MirrorMemory_Callout/CODE                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "Dem_ExternalMemory_Callout.h"

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
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_ExternalMem_SetDTCFilter                             */
/* Description   | set DTC filter.                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCOrigin       :                                   */
/*               |        If the Dem supports more than one event memoryth- */
/*               |        is parameter is used to select the source memory- */
/*               |        the DTCs shall be read from                       */
/*               | [in] DTCStatusMask   :                                   */
/*               |        Status-byte mask for DTC status-byte filtering V- */
/*               |        alues:0x00: Autosar-specific value to deactivate  */
/*               |         the status-byte filtering (different meaning th- */
/*               |        an in ISO 14229-1) to report all supported DTCs - */
/*               |        (used for service 0x19 subfunctions 0x0A/0x15) 0- */
/*               |        x01..0xFF: Status-byte mask according to ISO 142- */
/*               |        29-1 DTCStatusMask (handed over by Dcm from serv- */
/*               |        ice request directly) to filter for DTCs with at  */
/*               |         least one status bit set matching this status-b- */
/*               |        yte mask                                          */
/*               | [in] DTCStatusAvailabilityMask    :                      */
/*               |        Mask for the supported DTC status bits by the Dem.*/
/*               |        This mask is used in the positive response of UDS */
/*               |        service 0x19.                                     */
/* Return Value  | Dem_ExternalMemReturnType                                */
/*               |              DEM_EXTERNALMEM_OK                          */
/*               |              DEM_EXTERNALMEM_WRONG_DTCORIGIN             */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_ExternalMemReturnType, DEM_CODE_CALLOUT ) Dem_ExternalMem_SetDTCFilter
(
    VAR( Dem_DTCOriginType,     AUTOMATIC ) DTCOrigin,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusAvailabilityMask
)
{
    return DEM_EXTERNALMEM_OK;
}

/****************************************************************************/
/* Function Name | Dem_ExternalMem_GetNextFilteredDTC                       */
/* Description   | get next filtered DTC.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCOrigin       :                                   */
/*               |        If the Dem supports more than one event memoryth- */
/*               |        is parameter is used to select the source memory- */
/*               |        the DTCs shall be read from                       */
/*               | [in] DTCStatusMask   :                                   */
/*               |        Status-byte mask for DTC status-byte filtering V- */
/*               |        alues:0x00: Autosar-specific value to deactivate  */
/*               |         the status-byte filtering (different meaning th- */
/*               |        an in ISO 14229-1) to report all supported DTCs - */
/*               |        (used for service 0x19 subfunctions 0x0A/0x15) 0- */
/*               |        x01..0xFF: Status-byte mask according to ISO 142- */
/*               |        29-1 DTCStatusMask (handed over by Dcm from serv- */
/*               |        ice request directly) to filter for DTCs with at  */
/*               |         least one status bit set matching this status-b- */
/*               |        yte mask                                          */
/*               | [in] DTCStatusAvailabilityMask    :                      */
/*               |        Mask for the supported DTC status bits by the Dem.*/
/*               |        This mask is used in the positive response of UDS */
/*               |        service 0x19.                                     */
/*               | [out] DTCPtr :                                           */
/*               |        Receives the DTC value in respective format of t- */
/*               |        he filter returned by this function. If the retu- */
/*               |        rn value of the function is other than DEM_FILTE- */
/*               |        RED_OK this parameter does not contain valid dat- */
/*               |        a.                                                */
/*               | [out] StatusOfDTCPtr :                                   */
/*               |        This parameter receives the status information o- */
/*               |        f the requested DTC. It follows the format as de- */
/*               |        fined in ISO14229-1 If the return value of the f- */
/*               |        unction call is other than DEM_FILTERED_OK this - */
/*               |        parameter does not contain valid data.            */
/* Return Value  | Dem_ExternalMemReturnType                                */
/*               |              DEM_EXTERNALMEM_OK                          */
/*               |              DEM_EXTERNALMEM_PENDING                     */
/*               |              DEM_EXTERNALMEM_NO_MATCHING_ELEMENT         */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_ExternalMemReturnType, DEM_CODE_CALLOUT ) Dem_ExternalMem_GetNextFilteredDTC
(
    VAR( Dem_DTCOriginType,         AUTOMATIC ) DTCOrigin,
    VAR( Dem_UdsStatusByteType,     AUTOMATIC ) DTCStatusMask,
    VAR( Dem_UdsStatusByteType,     AUTOMATIC ) DTCStatusAvailabilityMask,
    P2VAR( uint32, AUTOMATIC,       AUTOMATIC ) DTCPtr,
    P2VAR( Dem_UdsStatusByteType,   AUTOMATIC, AUTOMATIC ) StatusOfDTCPtr
)
{
    return DEM_EXTERNALMEM_NO_MATCHING_ELEMENT;
}

/****************************************************************************/
/* Function Name | Dem_ExternalMem_GetStatusOfDTC                           */
/* Description   | get status of DTC.                                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTC                                                 */
/*               |        Diagnostic Trouble Code in UDS format.            */
/*               | [in] DTCOrigin                                           */
/*               |        If the Dem supports more than one event memoryth- */
/*               |        is parameter is used to select the source memory- */
/*               |        the DTCs shall be read from                       */
/*               | [in] DTCStatusAvailabilityMask                           */
/*               |        Mask for the supported DTC status bits by the Dem.*/
/*               |        This mask is used in the positive response of UDS */
/*               |        service 0x19.                                     */
/*               | [out] StatusOfDTCPtr                                     */
/*               |        This parameter receives the status information    */
/*               |        of the requested DTC. If the return value of the  */
/*               |        function call is other than DEM_STATUS_OK this    */
/*               |        parameter does not contain valid data. 0x00...0xFF*/
/*               |        match DTCStatusMask as defined in ISO14229-1      */
/* Return Value  | Dem_ExternalMemReturnType                                */
/*               |              DEM_EXTERNALMEM_OK                          */
/*               |              DEM_EXTERNALMEM_WRONG_DTC                   */
/*               |              DEM_EXTERNALMEM_WRONG_DTCORIGIN             */
/*               |              DEM_EXTERNALMEM_FAILED                      */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_ExternalMemReturnType, DEM_CODE_CALLOUT ) Dem_ExternalMem_GetStatusOfDTC
(
    VAR( uint32,                    AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType,         AUTOMATIC ) DTCOrigin,
    VAR( Dem_UdsStatusByteType,     AUTOMATIC ) DTCStatusAvailabilityMask,
    P2VAR( Dem_UdsStatusByteType,   AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    *DTCStatusPtr    =   (Dem_UdsStatusByteType)0x00U;
    return DEM_EXTERNALMEM_OK;
}

/****************************************************************************/
/* Function Name | Dem_ExternalMem_StartOfGettingDTCRecord                  */
/* Description   | start of getting DTC record.                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTC                                                 */
/*               |        Diagnostic Trouble Code in UDS format.            */
/*               | [in] DTCOrigin                                           */
/*               |        If the Dem supports more than one event memoryth- */
/*               |        is parameter is used to select the source memory- */
/*               |        the DTCs shall be read from                       */
/* Return Value  | Dem_ExternalMemReturnType                                */
/*               |              DEM_EXTERNALMEM_OK                          */
/*               |              DEM_EXTERNALMEM_WRONG_DTC                   */
/*               |              DEM_EXTERNALMEM_WRONG_DTCORIGIN             */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_ExternalMemReturnType, DEM_CODE_CALLOUT ) Dem_ExternalMem_StartOfGettingDTCRecord
(
    VAR( uint32,            AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    return DEM_EXTERNALMEM_OK;
}

/****************************************************************************/
/* Function Name | Dem_ExternalMem_EndOfGettingDTCRecord                    */
/* Description   | end of getting DTC record.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTC                                                 */
/*               |        Diagnostic Trouble Code in UDS format.            */
/*               | [in] DTCOrigin                                           */
/*               |        If the Dem supports more than one event memoryth- */
/*               |        is parameter is used to select the source memory- */
/*               |        the DTCs shall be read from                       */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE_CALLOUT ) Dem_ExternalMem_EndOfGettingDTCRecord
(
    VAR( uint32,                AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType,     AUTOMATIC ) DTCOrigin
)
{
    return ;
}

/****************************************************************************/
/* Function Name | Dem_ExternalMem_GetSizeOfFreezeFrameByDTC                */
/* Description   | get size of freezeframe.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTC                                                 */
/*               |        Diagnostic Trouble Code in UDS format.            */
/*               | [in] DTCOrigin                                           */
/*               |        If the Dem supports more than one event memoryth- */
/*               |        is parameter is used to select the source memory- */
/*               |        the DTCs shall be read from                       */
/*               | [in] RecordNumber :                                      */
/*               |        This parameter is a unique identifier for a free- */
/*               |        ze frame record as defined in ISO 15031-5 and IS- */
/*               |        O 14229-1. This record number is unique per DTC - */
/*               |        (relative addressing). The value 0xFF is explici- */
/*               |        tly allowed to request the overall size.          */
/*               | [out] SizeOfFreezeFramePtr :                             */
/*               |        Number of bytes in the requested freeze frame re- */
/*               |        cord.                                             */
/* Return Value  | Dem_ExternalMemReturnType                                */
/*               |              DEM_EXTERNALMEM_OK                          */
/*               |              DEM_EXTERNALMEM_PENDING                     */
/*               |              DEM_EXTERNALMEM_WRONG_DTC                   */
/*               |              DEM_EXTERNALMEM_WRONG_DTCORIGIN             */
/*               |              DEM_EXTERNALMEM_WRONG_RECNUM                */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_ExternalMemReturnType, DEM_CODE_CALLOUT ) Dem_ExternalMem_GetSizeOfFreezeFrameByDTC
(
    VAR( uint32,                AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType,     AUTOMATIC ) DTCOrigin,
    VAR( uint8,                 AUTOMATIC ) RecordNumber,
    P2VAR( uint32,              AUTOMATIC,  AUTOMATIC ) SizeOfFreezeFramePtr
)
{
    *SizeOfFreezeFramePtr   =   (uint32)0x00000000U;
    return DEM_EXTERNALMEM_OK;
}

/****************************************************************************/
/* Function Name | Dem_ExternalMem_GetFreezeFrameDataByDTC                  */
/* Description   | get data of freezeframe.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTC                                                 */
/*               |        Diagnostic Trouble Code in UDS format.            */
/*               | [in] DTCOrigin                                           */
/*               |        If the Dem supports more than one event memoryth- */
/*               |        is parameter is used to select the source memory- */
/*               |        the DTCs shall be read from                       */
/*               | [in] RecordNumber :                                      */
/*               |        This parameter is a unique identifier for a free- */
/*               |        ze frame record as defined in ISO 15031-5 and IS- */
/*               |        O 14229-1. This record number is unique per DTC - */
/*               |        (relative addressing). The value 0xFF is not all- */
/*               |        owed. The value 0x00 indicates the DTC-specific - */
/*               |        OBD freeze frame.                                 */
/*               | [out] DestBufferPtr :                                    */
/*               |        This parameter contains a byte pointer that poin- */
/*               |        ts to the buffer, to which the freeze frame data  */
/*               |         record shall be written to. The format is: {Rec- */
/*               |        ordNumber, NumOfDIDs, DID[1], data[1], ..., DID[- */
/*               |        N], data[N]}                                      */
/*               | [in/out] BufSizePtr :                                    */
/*               |        When the function is called this parameter conta- */
/*               |        ins the maximum number of data bytes that can be  */
/*               |         written to the buffer. The function returns the  */
/*               |         actual number of written data bytes in this par- */
/*               |        ameter.                                           */
/*               | [out] NextRecordNumberPtr :                              */
/*               |        This parameter contains a byte pointer that poin- */
/*               |        ts to the buffer, to which the ID to be requeste- */
/*               |        d next  shall be written to which the freeze fra- */
/*               |        me data                                           */
/* Return Value  | Dem_ExternalMemReturnType                                */
/*               |              DEM_EXTERNALMEM_OK                          */
/*               |              DEM_EXTERNALMEM_PENDING                     */
/*               |              DEM_EXTERNALMEM_WRONG_DTC                   */
/*               |              DEM_EXTERNALMEM_WRONG_DTCORIGIN             */
/*               |              DEM_EXTERNALMEM_WRONG_RECNUM                */
/*               |              DEM_EXTERNALMEM_BUFFER_TOO_SMALL            */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_ExternalMemReturnType, DEM_CODE_CALLOUT ) Dem_ExternalMem_GetFreezeFrameDataByDTC
(
    VAR( uint32,                AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType,     AUTOMATIC ) DTCOrigin,
    VAR( uint8,                 AUTOMATIC ) RecordNumber,
    P2VAR( uint8,               AUTOMATIC,  DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( uint16,              AUTOMATIC,  AUTOMATIC ) BufSizePtr,
    P2VAR( uint8,               AUTOMATIC,  AUTOMATIC ) NextRecordNumberPtr
)
{
    *BufSizePtr =   (uint16)0x0000U;
    *NextRecordNumberPtr    =   DEM_RECORDNUMBER_NEXT_NONE;
    return DEM_EXTERNALMEM_OK;
}

/****************************************************************************/
/* Function Name | Dem_ExternalMem_GetSizeOfExtendedDataRecordByDTC         */
/* Description   | get size of extended data.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTC                                                 */
/*               |        Diagnostic Trouble Code in UDS format.            */
/*               | [in] DTCOrigin                                           */
/*               |        If the Dem supports more than one event memoryth- */
/*               |        is parameter is used to select the source memory- */
/*               |        the DTCs shall be read from                       */
/*               | [in] ExtendedDataNumber :                                */
/*               |        Identification/Number of requested extended data  */
/*               |        record. Additionally the values 0xFE and 0xFF are */
/*               |        explicitly allowed to request the overall size of */
/*               |        all OBD records / all records.                    */
/*               | [out] SizeOfExtendedDataRecordPtr :                      */
/*               |        Size of the requested extended data record(s) in- */
/*               |        cluding record number size.                       */
/* Return Value  | Dem_ExternalMemReturnType                                */
/*               |              DEM_EXTERNALMEM_OK                          */
/*               |              DEM_EXTERNALMEM_WRONG_DTC                   */
/*               |              DEM_EXTERNALMEM_WRONG_DTCORIGIN             */
/*               |              DEM_EXTERNALMEM_WRONG_RECNUM                */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_ExternalMemReturnType, DEM_CODE_CALLOUT ) Dem_ExternalMem_GetSizeOfExtendedDataRecordByDTC
(
    VAR( uint32,                AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType,     AUTOMATIC ) DTCOrigin,
    VAR( uint8,                 AUTOMATIC ) ExtendedDataNumber,
    P2VAR( uint16,              AUTOMATIC,  AUTOMATIC ) SizeOfExtendedDataRecordPtr
)
{
    *SizeOfExtendedDataRecordPtr    =   (uint16)0x0000U;
    return DEM_EXTERNALMEM_OK;
}

/****************************************************************************/
/* Function Name | Dem_ExternalMem_GetExtendedDataRecordByDTC               */
/* Description   | get data of extended data.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTC                                                 */
/*               |        Diagnostic Trouble Code in UDS format.            */
/*               | [in] DTCOrigin                                           */
/*               |        If the Dem supports more than one event memoryth- */
/*               |        is parameter is used to select the source memory- */
/*               |        the DTCs shall be read from                       */
/*               | [in] ExtendedDataNumber :                                */
/*               |        Identification/Number of requested extended data  */
/*               |        record. The values 0xFE and 0xFF are not allowed. */
/*               | [out] DestBufferPtr :                                    */
/*               |        This parameter contains a byte pointer that poin- */
/*               |        ts to the buffer, to which the extended data rec- */
/*               |        ord shall be written to. The format is raw hexad- */
/*               |        ecimal values and contains no header-information. */
/*               | [in/out] BufSizePtr :                                    */
/*               |        When the function is called this parameter conta- */
/*               |        ins the maximum number of data bytes that can be  */
/*               |         written to the buffer. The function returns the  */
/*               |         actual number of written data bytes in this par- */
/*               |        ameter.                                           */
/*               | [out] NextExtendedDataNumberPtr :                        */
/*               |        This parameter contains a byte pointer that poin- */
/*               |        ts to the buffer, to which the ID to be requeste- */
/*               |        d next shall be written to which the extended da- */
/*               |        ta record.                                        */
/* Return Value  | Dem_ExternalMemReturnType                                */
/*               |              DEM_EXTERNALMEM_OK                          */
/*               |              DEM_EXTERNALMEM_WRONG_DTC                   */
/*               |              DEM_EXTERNALMEM_WRONG_DTCORIGIN             */
/*               |              DEM_EXTERNALMEM_WRONG_RECNUM                */
/*               |              DEM_EXTERNALMEM_BUFFER_TOO_SMALL            */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_ExternalMemReturnType, DEM_CODE_CALLOUT ) Dem_ExternalMem_GetExtendedDataRecordByDTC
(
    VAR( uint32,                AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType,     AUTOMATIC ) DTCOrigin,
    VAR( uint8,                 AUTOMATIC ) ExtendedDataNumber,
    P2VAR( uint8,               AUTOMATIC,  DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( uint16,              AUTOMATIC,  AUTOMATIC ) BufSizePtr,
    P2VAR( uint8,               AUTOMATIC,  AUTOMATIC ) NextExtendedDataNumberPtr
)
{
    *BufSizePtr =   (uint16)0x0000U;
    *NextExtendedDataNumberPtr  =   DEM_RECORDNUMBER_NEXT_NONE;
    return DEM_EXTERNALMEM_OK;
}

#define DEM_STOP_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
