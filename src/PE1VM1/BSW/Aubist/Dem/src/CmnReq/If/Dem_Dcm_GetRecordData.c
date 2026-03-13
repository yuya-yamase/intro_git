/* Dem_Dcm_GetRecordData_c(v5-5-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dcm_GetRecordData/CODE                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem_Dcm.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_CmnIf_Control.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"

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
/* Function Name | Dem_DcmDisableDTCRecordUpdate                            */
/* Description   | Disables the event memory update of a specific DTC (onl- */
/*               | y one at one time).                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTC :                                               */
/*               |        Selects the DTC in UDS format, for which DTC rec- */
/*               |        ord update shall be disabled.                     */
/*               | [in] DTCOrigin :                                         */
/*               |        If the Dem supports more than one event memory, - */
/*               |        this parameter is used to select the source memo- */
/*               |        ry for which DTC record update shall be disabled. */
/* Return Value  | Dem_ReturnDisableDTCRecordUpdateType                     */
/*               |        DEM_DISABLE_DTCRECUP_OK : success                 */
/*               |        DEM_DISABLE_DTCRECUP_WRONG_DTC : wrong DTC        */
/*               |        DEM_DISABLE_DTCRECUP_WRONG_DTCORIGIN : wrong DTC  */
/*               |         origin                                           */
/*               |        DEM_DISABLE_DTCRECUP_PENDING : pending            */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_ReturnDisableDTCRecordUpdateType, DEM_CODE ) Dem_DcmDisableDTCRecordUpdate
(
    VAR( uint32, AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_ReturnDisableDTCRecordUpdateType, AUTOMATIC ) retVal;

    retVal = DEM_DISABLE_DTCRECUP_WRONG_DTC;

    internalReturnValue = Dem_ControlIFCmn_DisableDTCRecordUpdate( (Dem_u32_DTCValueType)DTC , DTCOrigin );

    /* Convert return value */
    switch( internalReturnValue )
    {
        case DEM_IRT_OK:
            retVal = DEM_DISABLE_DTCRECUP_OK;
            break;
        case DEM_IRT_WRONG_DTC:
            /* No Process */
            break;
        case DEM_IRT_WRONG_DTCORIGIN:
            retVal = DEM_DISABLE_DTCRECUP_WRONG_DTCORIGIN;
            break;
        case DEM_IRT_PENDING:
            retVal = DEM_DISABLE_DTCRECUP_PENDING;
            break;
        default:
            /* No Process */
            break;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DcmEnableDTCRecordUpdate                             */
/* Description   | Enables the event memory update of the DTC disabled by - */
/*               | Dem_DcmDisableDTCRecordUpdate() before.                  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Always E_OK is returned.                   */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmEnableDTCRecordUpdate
( void )
{
    Dem_ControlIFCmn_EnableDTCRecordUpdate();

    return E_OK;
}

/****************************************************************************/
/* Function Name | Dem_DcmGetSizeOfFreezeFrameByDTC                         */
/* Description   | Gets the size of freeze frame data by DTC.               */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTC :                                               */
/*               |        Diagnostic Trouble Code in UDS format.            */
/*               | [in] DTCOrigin :                                         */
/*               |        If the Dem supports more than one event memory, - */
/*               |        this parameter is used to select the source memo- */
/*               |        ry the DTCs shall be read from.                   */
/*               | [in] RecordNumber :                                      */
/*               |        This parameter is a unique identifier for a free- */
/*               |        ze frame record as defined in ISO 15031-5 and IS- */
/*               |        O 14229-1. This record number is unique per DTC - */
/*               |        (relative addressing). The value 0xFF is explici- */
/*               |        tly allowed to request the overall size.          */
/*               | [out] SizeOfFreezeFrame :                                */
/*               |        Number of bytes in the requested freeze frame re- */
/*               |        cord.                                             */
/* Return Value  | Dem_ReturnGetSizeOfDataByDTCType                         */
/*               |        DEM_GETSIZEBYDTC_OK : success                     */
/*               |        DEM_GETSIZEBYDTC_WRONG_DTC : wrong DTC            */
/*               |        DEM_GETSIZEBYDTC_WRONG_DTCORIGIN : wrong DTC ori- */
/*               |        gin                                               */
/*               |        DEM_GETSIZEBYDTC_WRONG_RECNUM : wrong record num- */
/*               |        ber                                               */
/*               |        DEM_GETSIZEBYDTC_PENDING : pending                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_ReturnGetSizeOfDataByDTCType, DEM_CODE ) Dem_DcmGetSizeOfFreezeFrameByDTC
(
    VAR( uint32, AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( uint8, AUTOMATIC ) RecordNumber,
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) SizeOfFreezeFrame
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_ReturnGetSizeOfDataByDTCType, AUTOMATIC ) retVal;
    VAR( Dem_u32_FFDOutputTotalSizeType, AUTOMATIC ) bufSize;

    retVal = DEM_GETSIZEBYDTC_WRONG_DTC;

    if( SizeOfFreezeFrame != NULL_PTR )
    {
        bufSize = (uint16)0U;  /*  out parameter.      */
        internalReturnValue = Dem_ControlIFCmn_GetSizeOfFreezeFrameByDTC( (Dem_u32_DTCValueType)DTC , DTCOrigin , (Dem_u08_FFRecordNumberType)RecordNumber , &bufSize );

        /* Convert return value */
        switch( internalReturnValue )
        {
            case DEM_IRT_OK:
                *SizeOfFreezeFrame = bufSize;  /*  set value to out parameter. */
                retVal = DEM_GETSIZEBYDTC_OK;
                break;
            case DEM_IRT_WRONG_DTC:
                /* No Process */
                break;
            case DEM_IRT_WRONG_DTCORIGIN:
                retVal = DEM_GETSIZEBYDTC_WRONG_DTCORIGIN;
                break;
            case DEM_IRT_WRONG_RECORDNUMBER:
                retVal = DEM_GETSIZEBYDTC_WRONG_RECNUM;
                break;
            case DEM_IRT_PENDING:
                retVal = DEM_GETSIZEBYDTC_PENDING;
                break;
            default:
                /* No Process */
                break;
        }
    }
    else
    {
        /* No Process */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DcmGetFreezeFrameDataByDTC                           */
/* Description   | Gets freeze frame data by DTC. The function stores the - */
/*               | data in the provided DestBuffer.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTC :                                               */
/*               |        Diagnostic Trouble Code in UDS format.            */
/*               | [in] DTCOrigin :                                         */
/*               |        If the Dem supports more than one event memory, - */
/*               |        this parameter is used to select the source memo- */
/*               |        ry the DTCs shall be read from.                   */
/*               | [in] RecordNumber :                                      */
/*               |        This parameter is a unique identifier for a free- */
/*               |        ze frame record as defined in ISO 15031-5 and IS- */
/*               |        O 14229-1. This record number is unique per DTC - */
/*               |        (relative addressing). The value 0xFF is not all- */
/*               |        owed. The value 0x00 indicates the DTC-specific - */
/*               |        OBD freeze frame.                                 */
/*               | [out] DestBuffer :                                       */
/*               |        This parameter contains a byte pointer that poin- */
/*               |        ts to the buffer, to which the freeze frame data  */
/*               |         record shall be written to. The format is: {Rec- */
/*               |        ordNumber, NumOfDIDs, DID[1], data[1], ..., DID[- */
/*               |        N], data[N]}                                      */
/*               | [in/out] BufSize :                                       */
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
/* Return Value  | Dem_ReturnGetFreezeFrameDataByDTCType                    */
/*               |        DEM_GET_FFDATABYDTC_OK : success                  */
/*               |        DEM_GET_FFDATABYDTC_WRONG_DTC : wrong DTC         */
/*               |        DEM_GET_FFDATABYDTC_WRONG_DTCORIGIN : wrong DTC - */
/*               |        origin                                            */
/*               |        DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER : wrong r- */
/*               |        ecord number                                      */
/*               |        DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE : wrong buf- */
/*               |        fer size                                          */
/*               |        DEM_GET_FFDATABYDTC_PENDING : pending             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_ReturnGetFreezeFrameDataByDTCType, DEM_CODE ) Dem_DcmGetFreezeFrameDataByDTC
(
    VAR( uint32, AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( uint8, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBuffer,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) BufSize,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) NextRecordNumberPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_ReturnGetFreezeFrameDataByDTCType, AUTOMATIC ) retVal;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) bufSize;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) nextRecordNumber;

    retVal = DEM_GET_FFDATABYDTC_WRONG_DTC;

    if( DestBuffer == NULL_PTR )
    {
        /* No Process */
    }
    else if( BufSize == NULL_PTR )
    {
        /* No Process */
    }
    else if( NextRecordNumberPtr == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        bufSize = *BufSize;    /*  in/out parameter.       */
        nextRecordNumber = DEM_RECORDNUMBER_NEXT_NONE;
        internalReturnValue = Dem_ControlIFCmn_GetFreezeFrameDataByDTC( (Dem_u32_DTCValueType)DTC , DTCOrigin , (Dem_u08_FFRecordNumberType)RecordNumber , DestBuffer , &bufSize, &nextRecordNumber );
        *NextRecordNumberPtr = nextRecordNumber;

        /* Convert return value */
        switch( internalReturnValue )
        {
            case DEM_IRT_OK:
                *BufSize = bufSize;    /*  set value to out parameter. */
                retVal = DEM_GET_FFDATABYDTC_OK;
                break;
            case DEM_IRT_WRONG_DTC:
                /* No Process */
                break;
            case DEM_IRT_WRONG_DTCORIGIN:
                retVal = DEM_GET_FFDATABYDTC_WRONG_DTCORIGIN;
                break;
            case DEM_IRT_WRONG_RECORDNUMBER:
                retVal = DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER;
                break;
            case DEM_IRT_WRONG_BUFFERSIZE:
                retVal = DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE;
                break;
            case DEM_IRT_PENDING:
                retVal = DEM_GET_FFDATABYDTC_PENDING;
                break;
            default:
                /* No Process */
                break;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DcmGetSizeOfExtendedDataRecordByDTC                  */
/* Description   | Gets the size of extended data by DTC.                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTC :                                               */
/*               |        Diagnostic Trouble Code in UDS format.            */
/*               | [in] DTCOrigin :                                         */
/*               |        If the Dem supports more than one event memory, - */
/*               |        this parameter is used to select the source memo- */
/*               |        ry the DTCs shall be read from.                   */
/*               | [in] ExtendedDataNumber :                                */
/*               |        Identification/Number of requested extended data  */
/*               |        record. Additionally the values 0xFE and 0xFF are */
/*               |        explicitly allowed to request the overall size of */
/*               |        all OBD records / all records.                    */
/*               | [out] SizeOfExtendedDataRecord :                         */
/*               |        Size of the requested extended data record(s) in- */
/*               |        cluding record number size.                       */
/* Return Value  | Dem_ReturnGetSizeOfDataByDTCType                         */
/*               |        DEM_GETSIZEBYDTC_OK : success                     */
/*               |        DEM_GETSIZEBYDTC_WRONG_DTC : wrong DTC            */
/*               |        DEM_GETSIZEBYDTC_WRONG_DTCORIGIN : wrong DTC origin. */
/*               |        DEM_GETSIZEBYDTC_WRONG_RECNUM : wrong RecordNumber*/
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_ReturnGetSizeOfDataByDTCType, DEM_CODE ) Dem_DcmGetSizeOfExtendedDataRecordByDTC
(
    VAR( uint32, AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( uint8, AUTOMATIC ) ExtendedDataNumber,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) SizeOfExtendedDataRecord
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_ReturnGetSizeOfDataByDTCType, AUTOMATIC ) retVal;
    VAR( uint16, AUTOMATIC ) bufSize;

    retVal = DEM_GETSIZEBYDTC_WRONG_DTC;

    if( SizeOfExtendedDataRecord != NULL_PTR )
    {
        bufSize = (uint16)0U;                      /* out parameter. */
        internalReturnValue = Dem_ControlIFCmn_GetSizeOfExtendedDataRecordByDTC( (Dem_u32_DTCValueType)DTC , DTCOrigin, ( Dem_u08_EDRRecordNumberType )ExtendedDataNumber, &bufSize );
        if( internalReturnValue == DEM_IRT_OK )
        {
            *SizeOfExtendedDataRecord = bufSize;   /* set value to out parameter. */
            retVal = DEM_GETSIZEBYDTC_OK;       /* Convert return value */
        }
        else if ( internalReturnValue == DEM_IRT_WRONG_DTCORIGIN )
        {
            retVal = DEM_GETSIZEBYDTC_WRONG_DTCORIGIN;
        }
        else if ( internalReturnValue == DEM_IRT_WRONG_RECORDNUMBER )
        {
            retVal = DEM_GETSIZEBYDTC_WRONG_RECNUM;
        }
        else
        {
            /* no process.  */
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DcmGetExtendedDataRecordByDTC                        */
/* Description   | Gets extended data by DTC. The function stores the data  */
/*               | in the provided DestBuffer.                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTC :                                               */
/*               |        Diagnostic Trouble Code in UDS format.            */
/*               | [in] DTCOrigin :                                         */
/*               |        If the Dem supports more than one event memory, - */
/*               |        this parameter is used to select the source memo- */
/*               |        ry the DTCs shall be read from.                   */
/*               | [in] ExtendedDataNumber :                                */
/*               |        Identification/Number of requested extended data  */
/*               |        record. The values 0xFE and 0xFF are not allowed. */
/*               | [out] DestBuffer :                                       */
/*               |        This parameter contains a byte pointer that poin- */
/*               |        ts to the buffer, to which the extended data rec- */
/*               |        ord shall be written to. The format is raw hexad- */
/*               |        ecimal values and contains no header-information. */
/*               | [in/out] BufSize :                                       */
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
/* Return Value  | Dem_ReturnGetExtendedDataRecordByDTCType                 */
/*               |        DEM_RECORD_OK : success                           */
/*               |        DEM_RECORD_WRONG_DTC : wrong DTC                  */
/*               |        DEM_RECORD_WRONG_DTCORIGIN :  wrong DTC Origin    */
/*               |        DEM_RECORD_WRONG_NUMBER : wrong record number     */
/*               |        DEM_RECORD_WRONG_BUFFERSIZE : wrong buffer size   */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_ReturnGetExtendedDataRecordByDTCType, DEM_CODE ) Dem_DcmGetExtendedDataRecordByDTC
(
    VAR( uint32, AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( uint8, AUTOMATIC ) ExtendedDataNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBuffer,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) BufSize,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) NextExtendedDataNumberPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_ReturnGetFreezeFrameDataByDTCType, AUTOMATIC ) retVal;
    VAR( uint16, AUTOMATIC ) bufSize;
    VAR( uint8, AUTOMATIC ) nextDataNumber;

    retVal = DEM_RECORD_WRONG_DTC;

    if( DestBuffer == NULL_PTR )
    {
        /* No Process */
    }
    else if( BufSize == NULL_PTR )
    {
        /* No Process */
    }
    else if( NextExtendedDataNumberPtr == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        bufSize = *BufSize;            /* in/out parameter. */
        nextDataNumber = DEM_RECORDNUMBER_NEXT_NONE;
        internalReturnValue = Dem_ControlIFCmn_GetExtendedDataRecordByDTC( (Dem_u32_DTCValueType)DTC , DTCOrigin , ExtendedDataNumber , DestBuffer , &bufSize, &nextDataNumber );
        *NextExtendedDataNumberPtr = nextDataNumber;

        /* Convert return value */
        switch( internalReturnValue )
        {
            case DEM_IRT_OK:
                *BufSize = bufSize;    /*  set value to out parameter. */
                retVal = DEM_RECORD_OK;
                break;
            case DEM_IRT_WRONG_DTC:
                /* No Process */
                break;
            case DEM_IRT_WRONG_DTCORIGIN:
                retVal = DEM_RECORD_WRONG_DTCORIGIN;
                break;
            case DEM_IRT_WRONG_RECORDNUMBER:
                retVal = DEM_RECORD_WRONG_NUMBER;
                break;
            default:
                /* DEM_IRT_WRONG_BUFFERSIZE */
                retVal = DEM_RECORD_WRONG_BUFFERSIZE;
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
