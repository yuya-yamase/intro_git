/* Dem_If_GetRecordData_c(v5-5-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/If_GetRecordData/CODE                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_CmnIf_Control.h"
#include "../../../inc/Dem_Pm_Control.h"

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
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_GetEventFreezeFrameDataEx                            */
/* Description   | Gets the data of a freeze frame by event.                */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [in] RecordNumber :                                      */
/*               |        This parameter is a unique identifier for a       */
/*               |        freeze frame record as defined in ISO14229-1.     */
/*               |        0xFF means most recent freeze frame record is     */
/*               |        returned. 0x00 is only supported if the Dem       */
/*               |        module supports WWH-OBD (refer to DemOBDSupport)  */
/*               | [in] DataId :                                            */
/*               |        This parameter specifies the DID (ISO14229-1)     */
/*               |        that shall be copied to the destination buffer.   */
/*               | [out] DestBuffer :                                       */
/*               |        This parameter contains a byte pointer that       */
/*               |        points to the buffer, to which the freeze frame   */
/*               |        data record shall be written to. The format is    */
/*               |        raw hexadecimal values and contains no            */
/*               |        header-information.                               */
/*               | [inout] BufSize :                                        */
/*               |        When the function is called this parameter        */
/*               |        contains the maximum number of data bytes that    */
/*               |        can be written to the buffer. The function        */
/*               |        returns the actual number of written data bytes   */
/*               |        in this parameter.                                */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK:                 Operation was successful    */
/*               |        E_NOT_OK:             Operation could not be      */
/*               |                              performed                   */
/*               |        DEM_NO_SUCH_ELEMENT:  The requested event data is */
/*               |                              not currently stored (but   */
/*               |                              the request was valid) OR   */
/*               |                              The requested record number */
/*               |                              is not supported by the     */
/*               |                              event OR The requested DID  */
/*               |                              is not supported by the     */
/*               |                              freeze frame.               */
/*               |        DEM_BUFFER_TOO_SMALL: The provided buffer size    */
/*               |                              is too small                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetEventFreezeFrameDataEx
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( uint8, AUTOMATIC ) RecordNumber,
    VAR( uint16, AUTOMATIC ) DataId,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBuffer,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) BufSize
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( uint16, AUTOMATIC ) bufferSize;

    retVal           = E_NOT_OK;

    if( DestBuffer == NULL_PTR )
    {
        /* No Process */
    }
    else if ( BufSize == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        bufferSize  =   *BufSize;
        internalReturnValue = Dem_Control_GetEventFreezeFrameData( EventId, (Dem_u08_FFRecordNumberType)RecordNumber, DataId, DestBuffer, &bufferSize );
        *BufSize    =   bufferSize;

        /* Convert return value */
        switch( internalReturnValue )
        {
            case DEM_IRT_OK:
                retVal = E_OK;
                break;
            case DEM_IRT_NODATAAVAILABLE:
                retVal = DEM_NO_SUCH_ELEMENT;
                break;
            case DEM_IRT_WRONG_RECORDNUMBER:
                retVal = DEM_NO_SUCH_ELEMENT;
                break;
            case DEM_IRT_WRONG_DIDNUMBER:
                retVal = DEM_NO_SUCH_ELEMENT;
                break;
            case DEM_IRT_WRONG_BUFFERSIZE:
                retVal = DEM_BUFFER_TOO_SMALL;
                break;
            case DEM_IRT_NG:
                /* No Process */
                break;
            default:
                /* No Process */
                break;
        }
    }
    return retVal;
}

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_GetUserDefinedMemoryFreezeFrameRecordNumber          */
/* Description   | Gets the data of a freeze frame record number by DTC.    */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTC :                                               */
/*               |        Diagnostic Trouble Code in UDS format.            */
/*               | [in] DTCOrigin :                                         */
/*               |        If the Dem supports more than one event memory t- */
/*               |        his parameter is used to select the source memor- */
/*               |        y the DTCs shall be read from.                    */
/*               | [out] RecordNumBufferPtr :                               */
/*               |        This parameter contains a byte pointer that       */
/*               |        points to the buffer, to which the freeze frame   */
/*               |        record number shall be written to.                */
/*               | [inout] BufSize :                                        */
/*               |        When the function is called this parameter        */
/*               |        contains the maximum number of data bytes that    */
/*               |        can be written to the buffer. The function        */
/*               |        returns the actual number of written data bytes   */
/*               |        in this parameter.                                */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK:                 Operation was successful    */
/*               |        E_NOT_OK:             Operation could not be      */
/*               |                              performed                   */
/*               |        DEM_BUFFER_TOO_SMALL: The provided buffer size    */
/*               |                              is too small                */
/*               |        DEM_E_EXTERNAL_MEMORY:                            */
/*               |                              external memory selected.   */
/*               |        DEM_E_ACCESS_PROCESSING:                          */
/*               |                            memory access processing now. */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetUserDefinedMemoryFreezeFrameRecordNumber
(
    VAR( uint32, AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) RecordNumBufferPtr,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) RecordNumPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( uint8, AUTOMATIC ) recordNumberCnt;

    retVal           = E_NOT_OK;

    if( RecordNumBufferPtr == NULL_PTR )
    {
        /* No Process */
    }
    else if ( RecordNumPtr == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        recordNumberCnt  =   *RecordNumPtr;
        internalReturnValue = Dem_ControlIFCmn_GetUserDefinedMemoryFreezeFrameRecordNumber( ( Dem_u32_DTCValueType )DTC, DTCOrigin, RecordNumBufferPtr, &recordNumberCnt );
        *RecordNumPtr    =   recordNumberCnt;

        /* Convert return value */
        switch( internalReturnValue )
        {
            case DEM_IRT_OK:
                retVal = E_OK;
                break;
            case DEM_IRT_EXTERNAL_MEMORY:
                retVal = DEM_E_EXTERNAL_MEMORY;     /*  external memory selected.   */
                break;

            case DEM_IRT_WRONG_BUFFERSIZE:
                retVal = DEM_BUFFER_TOO_SMALL;
                break;

            case DEM_IRT_NG:                        /*  condition error.            */
                retVal = DEM_E_ACCESS_PROCESSING;
                break;

            case DEM_IRT_WRONG_DTCORIGIN:
            case DEM_IRT_WRONG_DTC:
            default:
                /*  E_NOT_OK    */
                /* No Process   */
                break;
        }
    }
    return retVal;
}
#endif /* (DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON) */

/****************************************************************************/
/* Function Name | Dem_GetEventExtendedDataRecordEx                         */
/* Description   | Gets the data of an extended data record by event.       */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [in] RecordNumber :                                      */
/*               |        Identification of requested Extended data record. */
/*               |        Valid values are between 0x01 and 0xEF as defined */
/*               |        in ISO14229-1.                                    */
/*               | [out] DestBuffer :                                       */
/*               |        This parameter contains a byte pointer that       */
/*               |        points to the buffer, to which the extended data  */
/*               |        shall be written to. The format is raw hexadecimal*/
/*               |         values and contains no header-information.       */
/*               | [inout] BufSize :                                        */
/*               |        When the function is called this parameter        */
/*               |        contains the maximum number of data bytes that    */
/*               |        can be written to the buffer. The function        */
/*               |        returns the actual number of written data bytes   */
/*               |        in this parameter.                                */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK:                 Operation was successful    */
/*               |        E_NOT_OK:             Operation could not be      */
/*               |                              performed                   */
/*               |        DEM_NO_SUCH_ELEMENT:  The requested event data is */
/*               |                              not currently stored        */
/*               |                              (but the request was valid) */
/*               |                              OR the requested record     */
/*               |                              umber is not supported by   */
/*               |                              the event.                  */
/*               |        DEM_BUFFER_TOO_SMALL: The provided buffer size    */
/*               |                              is too small.               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetEventExtendedDataRecordEx
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( uint8, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBuffer,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) BufSize
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( uint16, AUTOMATIC ) bufferSize;

    retVal           = E_NOT_OK;

    if( DestBuffer == NULL_PTR )
    {
        /* No Process */
    }
    else if ( BufSize == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        bufferSize  =   *BufSize;
        internalReturnValue = Dem_Control_GetEventExtendedData( EventId, RecordNumber, DestBuffer, &bufferSize );
        *BufSize    =   bufferSize;

        /* Convert return value */
        switch( internalReturnValue )
        {
            case DEM_IRT_OK:
                retVal = E_OK;
                break;
            case DEM_IRT_WRONG_RECORDNUMBER:
                retVal = DEM_NO_SUCH_ELEMENT;
                break;
            case DEM_IRT_WRONG_BUFFERSIZE:
                retVal = DEM_BUFFER_TOO_SMALL;
                break;
            default:
                /* DEM_IRT_NG */
                /* No Process */
                break;
        }
    }
    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
