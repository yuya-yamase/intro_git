/* Dem_StoreData_Callout_c(v5-3-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/StoredData_Callout/CODE                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "Dem_StoredData_Callout.h"

#if ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_OFF )
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
/* Function Name | Dem_NotifyStartServiceOfDTCStoredData                    */
/* Description   | Starts to process which is related to DTCStoredData.     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE_CALLOUT ) Dem_NotifyStartServiceOfDTCStoredData
( void )
{
    /**********************************************/
    /* The operation start that a user defined.   */
    /**********************************************/

    /**********************************************/
    /* The operation end that a user defined.     */
    /**********************************************/

    return;
}


/****************************************************************************/
/* Function Name | Dem_NotifyEndServiceOfDTCStoredData                      */
/* Description   | Ends to process which is related to DTCStoredData.       */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE_CALLOUT ) Dem_NotifyEndServiceOfDTCStoredData
( void )
{
    /**********************************************/
    /* The operation start that a user defined.   */
    /**********************************************/

    /**********************************************/
    /* The operation end that a user defined.     */
    /**********************************************/

    return;
}


/****************************************************************************/
/* Function Name | Dem_GetSizeOfDTCStoredDataByRecordNumber                 */
/* Description   | Gets size of DTCStoredData by specific RecordNumber.     */
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
/*               |        DEM_GETSIZE_STOREDDATA_FAILED : Failed to acquir- */
/*               |        e the size                                        */
/*               |        DEM_GETSIZE_STOREDDATA_PENDING : Acquiring size   */
/*               |        DEM_GETSIZE_STOREDDATA_WRONG_RECNUM : Invalid re- */
/*               |        cord number                                       */
/* Notes         | At the caller, the value of SizeOfStoredDataPtr is       */
/*               | guaranteed.                                              */
/*               | Caller:Dem_StoredData_GetSizeOfDTCStoredDataByRecNum     */
/****************************************************************************/
FUNC( Dem_ReturnGetSizeOfDataByRecNumType, DEM_CODE_CALLOUT ) Dem_GetSizeOfDTCStoredDataByRecordNumber
(
    VAR( uint8, AUTOMATIC ) RecordNumber,
    P2VAR( uint32, AUTOMATIC, AUTOMATIC ) SizeOfStoredDataPtr
)
{
    VAR( Dem_ReturnGetSizeOfDataByRecNumType, AUTOMATIC ) retVal;

    /**********************************************/
    /* The operation start that a user defined.   */
    /**********************************************/

    retVal = DEM_GETSIZE_STOREDDATA_OK;
    (*SizeOfStoredDataPtr) = ((uint32)0x00000000U);

    /**********************************************/
    /* The operation end that a user defined.     */
    /**********************************************/
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_GetDTCStoredDataByRecordNumber                       */
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
/* Return Value  | Dem_ReturnGetDTCStoredDataByRecNumType                   */
/*               |        DEM_GET_STOREDDATA_OK : Retrieving of DTCStoredD- */
/*               |        ata failed                                        */
/*               |        DEM_GET_STOREDDATA_FAILED : Retrieving of DTCSto- */
/*               |        redData failed                                    */
/*               |        DEM_GET_STOREDDATA_PENDING : The acquisition pro- */
/*               |        cess of DTCStoredData has not been completed      */
/*               |        DEM_GET_STOREDDATA_WRONG_RECNUM : Invalid record- */
/*               |         number                                           */
/*               |        DEM_GET_STOREDDATA_WRONG_BUFFERSIZE : The buffer- */
/*               |         size is smaller than the actual data             */
/* Notes         | At the caller, the value of DestBufferPtr and BufSizePtr */
/*               | are guaranteed.                                          */
/*               | Caller:Dem_StoredData_GetDTCStoredDataByRecNum           */
/****************************************************************************/
FUNC( Dem_ReturnGetDTCStoredDataByRecNumType, DEM_CODE_CALLOUT ) Dem_GetDTCStoredDataByRecordNumber
(
    VAR( uint8, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( uint32, AUTOMATIC, AUTOMATIC ) BufSizePtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) NextRecordNumberPtr
)
{

    VAR( Dem_ReturnGetDTCStoredDataByRecNumType, AUTOMATIC ) retVal;

    /**********************************************/
    /* The operation start that a user defined.   */
    /**********************************************/

    retVal = DEM_GET_STOREDDATA_OK;

    (*BufSizePtr) = ((uint32)0x00000000U);
    (*NextRecordNumberPtr) = DEM_RECORDNUMBER_NEXT_NONE;


    /**********************************************/
    /* The operation end that a user defined.     */
    /**********************************************/

    return retVal;
}

#define DEM_STOP_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

#endif  /* ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_OFF )     */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
