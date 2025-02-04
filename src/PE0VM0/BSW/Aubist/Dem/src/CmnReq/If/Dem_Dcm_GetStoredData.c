/* Dem_Dcm_c(v5-5-0)                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dcm/CODE                                              */
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
/* Function Name | Dem_DcmStartDTCStoredData                                */
/* Description   | Starts to process which is related to DTCStoredData. Wh- */
/*               | en processing has already started, Dem shall return DEM- */
/*               | _START_STOREDDATA_OK.                                    */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_ReturnStartStoredDataType                            */
/*               |        DEM_START_STOREDDATA_OK : A start of the process- */
/*               |        ing succeeded                                     */
/*               |        DEM_START_STOREDDATA_PENDING : Because it is dur- */
/*               |        ing other processing, processing cannot start     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_ReturnStartStoredDataType, DEM_CODE ) Dem_DcmStartDTCStoredData
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_ReturnStartStoredDataType, AUTOMATIC ) retVal;

    retVal = DEM_START_STOREDDATA_PENDING;
    internalReturnValue = Dem_Control_StartDTCStoredData();

    /* Convert return value */
    switch( internalReturnValue )
    {
        case DEM_IRT_OK:
            retVal = DEM_START_STOREDDATA_OK;
            break;
        case DEM_IRT_PENDING:
            /* No Process */
            break;
        default:
            /* No Process */
            break;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DcmEndDTCStoredData                                  */
/* Description   | Ends to process which is related to DTCStoredData.       */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DcmEndDTCStoredData
( void )
{
    Dem_Control_EndDTCStoredData();

    return ;
}


/****************************************************************************/
/* Function Name | Dem_DcmGetSizeOfDTCStoredDataByRecNum                    */
/* Description   | Gets size of DTCStoredData from specific RecordNumber. - */
/*               | The size to return considers a format to store in param- */
/*               | eter DestBuffer of API Dem_DcmGetDTCStoredDataByRecNum.  */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordNumber :                                      */
/*               |        Defines RecordNumber of DTCStoredData. The value  */
/*               |         0xFF is explicitly allowed to request the overa- */
/*               |        ll size.                                          */
/*               | [out] SizeOfStoredDataPtr :                              */
/*               |        The number of bytes of requested DTCStoredData.   */
/* Return Value  | Dem_ReturnGetSizeOfDataByRecNumType                      */
/*               |        DEM_GETSIZE_STOREDDATA_OK : Size successfully re- */
/*               |        turned                                            */
/*               |        DEM_GETSIZE_STOREDDATA_FAILED : Size not success- */
/*               |        fully returned                                    */
/*               |        DEM_GETSIZE_STOREDDATA_PENDING : The requested v- */
/*               |        alue is calculated asynchronouslyand currently n- */
/*               |        ot available. The caller can retry later.         */
/*               |        DEM_GETSIZE_STOREDDATA_WRONG_RECNUM : Record num- */
/*               |        ber is not supported by configuration and theref- */
/*               |        ore invalid                                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_ReturnGetSizeOfDataByRecNumType, DEM_CODE ) Dem_DcmGetSizeOfDTCStoredDataByRecNum
(
    VAR( uint8, AUTOMATIC ) RecordNumber,
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) SizeOfStoredDataPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_ReturnGetSizeOfDataByRecNumType, AUTOMATIC ) retVal;
    VAR( uint32, AUTOMATIC ) bufSize;

    retVal = DEM_GETSIZE_STOREDDATA_FAILED;

    if( SizeOfStoredDataPtr != NULL_PTR )
    {
        bufSize = (uint32)0U;  /*  out parameter.  */
        internalReturnValue = Dem_Control_GetSizeOfDTCStoredDataByRecNum( RecordNumber, &bufSize );

        /* Convert return value */
        switch( internalReturnValue )
        {
            case DEM_IRT_OK:
                *SizeOfStoredDataPtr = bufSize;    /*  set value to out parameter. */
                retVal = DEM_GETSIZE_STOREDDATA_OK;
                break;
            case DEM_IRT_NG:
                /* No Process */
                break;
            case DEM_IRT_PENDING:
                retVal = DEM_GETSIZE_STOREDDATA_PENDING;
                break;
            case DEM_IRT_WRONG_RECORDNUMBER:
                retVal = DEM_GETSIZE_STOREDDATA_WRONG_RECNUM;
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
/* Function Name | Dem_DcmGetDTCStoredDataByRecNum                          */
/* Description   | Gets the DTCStoredData from specific RecordNumber.       */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordNumber :                                      */
/*               |        Defines RecordNumber of DTCStoredData. The value  */
/*               |         0xFF is not allowed. The value 0x00 indicates O- */
/*               |        BD-related DTCStoredData.                         */
/*               | [out] DestBufferPtr :                                    */
/*               |        This parameter contains a byte pointer that poin- */
/*               |        ts to the buffer, to which DTCStoredData record - */
/*               |        shall be written to.                              */
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
/* Return Value  | Dem_ReturnGetDTCStoredDataByRecNumType                   */
/*               |        DEM_GET_STOREDDATA_OK : Size successfully return- */
/*               |        ed                                                */
/*               |        DEM_GET_STOREDDATA_FAILED : Size not successfull- */
/*               |        y returned                                        */
/*               |        DEM_GET_STOREDDATA_PENDING : The requested value  */
/*               |         is calculated asynchronouslyand currently not a- */
/*               |        vailable. The caller can retry later.             */
/*               |        DEM_GET_STOREDDATA_WRONG_RECNUM : Record number - */
/*               |        is not supported by configuration and therefore - */
/*               |        invalid                                           */
/*               |        DEM_GET_STOREDDATA_WRONG_BUFFERSIZE : Provided b- */
/*               |        uffer size to small                               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_ReturnGetDTCStoredDataByRecNumType, DEM_CODE ) Dem_DcmGetDTCStoredDataByRecNum
(
    VAR( uint8, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) BufSizePtr,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) NextRecordNumberPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_ReturnGetDTCStoredDataByRecNumType, AUTOMATIC ) retVal;
    VAR( uint32, AUTOMATIC ) bufSize;
    VAR( uint8, AUTOMATIC ) nextRecordNumber;

    retVal = DEM_GET_STOREDDATA_FAILED;

    if( DestBufferPtr == NULL_PTR )
    {
        /* No Process */
    }
    else if( BufSizePtr == NULL_PTR )
    {
        /* No Process */
    }
    else if( NextRecordNumberPtr == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        bufSize = *BufSizePtr; /*  in/out parameter.   */
        nextRecordNumber =  DEM_RECORDNUMBER_NEXT_NONE;
        internalReturnValue = Dem_Control_GetDTCStoredDataByRecNum( RecordNumber, DestBufferPtr, &bufSize, &nextRecordNumber );
        *NextRecordNumberPtr =  nextRecordNumber;

        /* Convert return value */
        switch( internalReturnValue )
        {
            case DEM_IRT_OK:
                *BufSizePtr = bufSize; /*  set value to out parameter. */
                retVal = DEM_GET_STOREDDATA_OK;
                break;
            case DEM_IRT_NG:
                /* No Process */
                break;
            case DEM_IRT_PENDING:
                retVal = DEM_GET_STOREDDATA_PENDING;
                break;
            case DEM_IRT_WRONG_RECORDNUMBER:
                retVal = DEM_GET_STOREDDATA_WRONG_RECNUM;
                break;
            case DEM_IRT_WRONG_BUFFERSIZE:
                retVal = DEM_GET_STOREDDATA_WRONG_BUFFERSIZE;
                break;
            default:
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
