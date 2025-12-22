/* Dem_StoredData_c(v5-3-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/StoredData/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_OFF )
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_StoredData.h"
#include "../../../usr/Dem_StoredData_Callout.h"

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


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_StoredData_Init                                      */
/* Description   | Inits Dem_StoredData.                                    */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_StoredData_Init
( void )
{
    /*  This is empty function for function switching.  */
    /* No Process */
    return;
}

/****************************************************************************/
/* Function Name | Dem_StoredData_StartDTCStoredData                        */
/* Description   | Starts to process which is related to DTCStoredData.     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : A start of the processing is succes- */
/*               |        sful                                              */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_StoredData_StartDTCStoredData
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_OK;

    Dem_NotifyStartServiceOfDTCStoredData();

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_StoredData_EndDTCStoredData                          */
/* Description   | Ends to process which is related to DTCStoredData.       */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_StoredData_EndDTCStoredData
( void )
{
    Dem_NotifyEndServiceOfDTCStoredData();
    return;
}


/****************************************************************************/
/* Function Name | Dem_StoredData_GetSizeOfDTCStoredDataByRecNum            */
/* Description   | Gets size of DTCStoredData by specific RecordNumber.     */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordNumber :                                      */
/*               |        Defines RecordNumber of DTCStoredData. The value  */
/*               |         0xFF is explicitly allowed to request the overa- */
/*               |        ll size.                                          */
/*               | [out] SizeOfStoredDataPtr :                              */
/*               |        The number of bytes of requested DTCStoredData.   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Size successfully returned           */
/*               |        DEM_IRT_NG : Failed to acquire the size           */
/*               |        DEM_IRT_PENDING : Acquiring size                  */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : Invalid record numb- */
/*               |        er                                                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_StoredData_GetSizeOfDTCStoredDataByRecNum
(
    VAR( Dem_u08_StoredDataRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_u32_StoredDataRecordSizeType, AUTOMATIC, AUTOMATIC ) SizeOfStoredDataPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_ReturnGetSizeOfDataByRecNumType, AUTOMATIC ) retValGetSize;

    retVal = DEM_IRT_NG;

    retValGetSize = Dem_GetSizeOfDTCStoredDataByRecordNumber( RecordNumber, SizeOfStoredDataPtr );

    if( retValGetSize == DEM_GETSIZE_STOREDDATA_OK )
    {
        retVal = DEM_IRT_OK;
    }
    else if( retValGetSize == DEM_GETSIZE_STOREDDATA_FAILED )
    {
        /* No Process */
    }
    else if( retValGetSize == DEM_GETSIZE_STOREDDATA_PENDING )
    {
        retVal = DEM_IRT_PENDING;
    }
    else if( retValGetSize == DEM_GETSIZE_STOREDDATA_WRONG_RECNUM )
    {
        retVal = DEM_IRT_WRONG_RECORDNUMBER;
    }
    else
    {
        /* No Process */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_StoredData_GetDTCStoredDataByRecNum                  */
/* Description   | Gets the DTCStoredData by specific RecordNumber.         */
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
/*               |        This parameter contains a pointer that points to  */
/*               |        the buffer, to which the next required Record nu- */
/*               |        mber will be written.                             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Retrieving of DTCStoredData success- */
/*               |        fully                                             */
/*               |        DEM_IRT_NG : Retrieving of DTCStoredData failed   */
/*               |        DEM_IRT_PENDING : The acquisition process of DTC- */
/*               |        StoredData has not been completed                 */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : Invalid record number*/
/*               |        DEM_IRT_WRONG_BUFFERSIZE : The buffer size is sm- */
/*               |        aller than the actual data                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_StoredData_GetDTCStoredDataByRecNum
(
    VAR( Dem_u08_StoredDataRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u32_StoredDataRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr,
    P2VAR( Dem_u08_StoredDataRecordNumberType, AUTOMATIC, AUTOMATIC ) NextRecordNumberPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_ReturnGetDTCStoredDataByRecNumType, AUTOMATIC ) retValGetDTCStoredData;

    retVal = DEM_IRT_NG;

    retValGetDTCStoredData = Dem_GetDTCStoredDataByRecordNumber( RecordNumber, DestBufferPtr, BufSizePtr, NextRecordNumberPtr );

    if( retValGetDTCStoredData == DEM_GET_STOREDDATA_OK )
    {
        retVal = DEM_IRT_OK;
    }
    else if( retValGetDTCStoredData == DEM_GET_STOREDDATA_FAILED )
    {
        /* No Process */
    }
    else if( retValGetDTCStoredData == DEM_GET_STOREDDATA_PENDING )
    {
        retVal = DEM_IRT_PENDING;
    }
    else if( retValGetDTCStoredData == DEM_GET_STOREDDATA_WRONG_RECNUM )
    {
        retVal = DEM_IRT_WRONG_RECORDNUMBER;
    }
    else if( retValGetDTCStoredData == DEM_GET_STOREDDATA_WRONG_BUFFERSIZE )
    {
        retVal = DEM_IRT_WRONG_BUFFERSIZE;
    }
    else
    {
        /* No Process */
    }

    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_OFF )     */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
