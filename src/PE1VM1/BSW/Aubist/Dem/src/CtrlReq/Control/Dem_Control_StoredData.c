/* Dem_Control_StoredData_c(v5-3-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_StoredData/CODE                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_StoredData.h"
#include "Dem_Control_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( void, DEM_CODE ) Dem_Control_SetDTCStoredDataStatus
(
    VAR( Dem_u08_DTCStoredDataStatusType, AUTOMATIC ) DTCStoredDataStatus
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_u08_DTCStoredDataStatusType, DEM_VAR_NO_INIT )                        Dem_CtlDTCStoredDataStatus;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Unit External functions                                                  */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Function Name | Dem_Control_StartDTCStoredData                           */
/* Description   | Starts to process which is related to DTCStoredData.     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : A start of the processing succeeded  */
/*               |        DEM_IRT_PENDING : Because it is during other pro- */
/*               |        cessing, processing cannot start                  */
/* Notes         | This function is in DCM main process.                    */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_StartDTCStoredData
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal = DEM_IRT_PENDING;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u08_DTCStoredDataStatusType, AUTOMATIC ) storedDataStatus;
    VAR( boolean, AUTOMATIC ) firstDTCStoredDataStart = (boolean)FALSE;
#if ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON ) /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) execClearDTC;
#endif  /* ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )     */


    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
#if ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON ) /*  [FuncSw]    */
        SchM_Enter_Dem_CheckClearDTCStatus();

        execClearDTC = Dem_Control_CheckExecClearDTCProcess();
        if( execClearDTC == (boolean)FALSE )
#endif  /* ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )     */
        {

            /* When not in clear processing */
            /* Check DTCStoredData acquisition processing status */
            storedDataStatus = Dem_Control_GetDTCStoredDataStatus();
            if( storedDataStatus == DEM_CTL_STS_DTC_STORED_DATA_END )
            {
                /* When obtain processing does not start */
                /* For shortening exclusive duration, regard obtain processing starts once */
                /* When acquisition processing didn't start, return unstarted acquisition processing */
                Dem_Control_SetDTCStoredDataStatus( DEM_CTL_STS_DTC_STORED_DATA_START );
                firstDTCStoredDataStart = (boolean)TRUE;
            }
            else if( storedDataStatus == DEM_CTL_STS_DTC_STORED_DATA_START )
            {
                /* When acquisition processing starts */
                retVal = DEM_IRT_OK;
            }
            else
            {
                /* When a value except the above is returned */
                /* No process */
            }
        }

#if ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON ) /*  [FuncSw]    */
        SchM_Exit_Dem_CheckClearDTCStatus();
#endif  /* ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )     */

        /* The first start processing of acquisition processing */
        if( firstDTCStoredDataStart == (boolean)TRUE )
        {
            (void)Dem_StoredData_StartDTCStoredData();   /* no return check required */

            /* Return DEM_IRT_OK */
            retVal = DEM_IRT_OK;
        }
        else
        {
            /* When acquisition processing start status cannont be set, or has been acquisition processing start status */
            /* No process */
        }
    }
    else
    {
        /* For processing execution in an incorrect initialization state */
        /* No process */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_EndDTCStoredData                             */
/* Description   | Ends to process which is related to DTCStoredData.       */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_EndDTCStoredData
( void )
{
    Dem_StoredData_EndDTCStoredData();
    Dem_Control_SetDTCStoredDataStatus( DEM_CTL_STS_DTC_STORED_DATA_END );
    return ;
}


/****************************************************************************/
/* Function Name | Dem_Control_GetSizeOfDTCStoredDataByRecNum               */
/* Description   | Gets size of DTCStoredData by specific RecordNumber.     */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordNumber :                                      */
/*               |        Defines RecordNumber of DTCStoredData. The value  */
/*               |         0xFF is explicitly allowed to request the overa- */
/*               |        ll size.                                          */
/*               | [out] StoredDataSizePtr :                                */
/*               |        The number of bytes of requested DTCStoredData.   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Retrieving of DTCStoredData succeed- */
/*               |        ed.                                               */
/*               |        DEM_IRT_NG : Retrieving of DTCStoredData failed.  */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetSizeOfDTCStoredDataByRecNum
(
    VAR( Dem_u08_StoredDataRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_u32_StoredDataRecordSizeType, AUTOMATIC, AUTOMATIC ) StoredDataSizePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal = DEM_IRT_NG;
    VAR( Dem_u08_DTCStoredDataStatusType, AUTOMATIC ) storedDataStatus;

    storedDataStatus = Dem_Control_GetDTCStoredDataStatus();
    if( storedDataStatus == DEM_CTL_STS_DTC_STORED_DATA_START )
    {
        retVal = Dem_StoredData_GetSizeOfDTCStoredDataByRecNum( RecordNumber, StoredDataSizePtr );
    }
    else
    {
        /* No process */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_GetDTCStoredDataByRecNum                     */
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
/*               |        DEM_IRT_NG : Retrieving of DTCStoredData failed   */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetDTCStoredDataByRecNum
(
    VAR( Dem_u08_StoredDataRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u32_StoredDataRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr,
    P2VAR( Dem_u08_StoredDataRecordNumberType, AUTOMATIC, AUTOMATIC ) NextRecordNumberPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal = DEM_IRT_NG;
    VAR( Dem_u08_DTCStoredDataStatusType, AUTOMATIC ) storedDataStatus;

    storedDataStatus = Dem_Control_GetDTCStoredDataStatus();
    if( storedDataStatus == DEM_CTL_STS_DTC_STORED_DATA_START )
    {
        retVal = Dem_StoredData_GetDTCStoredDataByRecNum( RecordNumber, DestBufferPtr, BufSizePtr, NextRecordNumberPtr );
    }
    else
    {
        /* No process */
    }

    return retVal;
}

/*--------------------------------------------------------------------------*/
/* Unit Internal functions(process)                                         */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Unit Internal functions(data)                                            */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Function Name | Dem_Control_SetDTCStoredDataStatus                       */
/* Description   | Sets DTC stored data status.                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStoredDataStatus :                               */
/*               |        DTC stored data status.                           */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_SetDTCStoredDataStatus
(
    VAR( Dem_u08_DTCStoredDataStatusType, AUTOMATIC ) DTCStoredDataStatus
)
{
    Dem_CtlDTCStoredDataStatus = DTCStoredDataStatus;
}


/****************************************************************************/
/* Function Name | Dem_Control_GetDTCStoredDataStatus                       */
/* Description   | Gets DTC stored data status.                             */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_DTCStoredDataStatusType                          */
/*               |        DEM_CTL_STS_DTC_STORED_DATA_END : DTC stored data */
/*               |         is started.                                      */
/*               |        DEM_CTL_STS_DTC_STORED_DATA_START : DTC stored da-*/
/*               |        ta is ended.                                      */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_DTCStoredDataStatusType, DEM_CODE ) Dem_Control_GetDTCStoredDataStatus
( void )
{
    return Dem_CtlDTCStoredDataStatus;
}


/****************************************************************************/
/* Function Name | Dem_Control_InitDTCStoredDataStatus                      */
/* Description   | Initializes DTC stored data status.                      */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_InitDTCStoredDataStatus
( void )
{
    Dem_CtlDTCStoredDataStatus = DEM_CTL_STS_DTC_STORED_DATA_END;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
