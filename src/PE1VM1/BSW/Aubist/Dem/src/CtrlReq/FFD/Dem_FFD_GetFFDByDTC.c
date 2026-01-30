/* Dem_FFD_GetFFDByDTC_c(v5-9-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/FFD_GetFFDByDTC/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_Pm_FFD.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "../../../inc/Dem_Pm_Misfire.h"

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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFD_CheckSupportedFreezeFrameRecordNumber
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u08_FreezeFrameDataType, AUTOMATIC ) FreezeFrameDataType
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFD_GetSizeOfFreezeFrameByIndividualRecordNumber
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_u32_FFDOutputTotalSizeType, AUTOMATIC, AUTOMATIC ) SizeOfFreezeFramePtr
);

static FUNC( void, DEM_CODE ) Dem_FFD_GetSizeOfFreezeFrameByAllRecordNumber
(
    P2VAR( Dem_u32_FFDOutputTotalSizeType, AUTOMATIC, AUTOMATIC ) SizeOfFreezeFramePtr
);


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
/* Function Name | Dem_FFD_GetSizeOfFreezeFrame                             */
/* Description   | Gets the size of freeze frame data by DTC.               */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        index of the event                                */
/*               | [in] RecordNumber :                                      */
/*               |        This parameter is a unique identifier for a free- */
/*               |        ze frame record as defined in ISO 15031-5 and IS- */
/*               |        O 14229-1.This record number is unique per DTC (- */
/*               |        relative addressing).The value 0xFF is explicitl- */
/*               |        y allowed to request the overall size.            */
/*               | [out] SizeOfFreezeFramePtr :                             */
/*               |        Number of bytes in the requested freeze frame re- */
/*               |        cord.                                             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Size successfully returned           */
/*               |        DEM_IRT_NG : Size was not returned.               */
/*               |        DEM_IRT_WRONG_RECORD_NUMBER : The wrong record n- */
/*               |        umber was passed.                                 */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | refactor function.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFD_GetSizeOfFreezeFrame
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_u32_FFDOutputTotalSizeType, AUTOMATIC, AUTOMATIC ) SizeOfFreezeFramePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    if ( RecordNumber < DEM_FFRECNUM_ALL_RECORDS )
    {
        retVal = Dem_FFD_GetSizeOfFreezeFrameByIndividualRecordNumber( EventStrgIndex, RecordNumber, SizeOfFreezeFramePtr );
    }
    else
    {
        Dem_FFD_GetSizeOfFreezeFrameByAllRecordNumber( SizeOfFreezeFramePtr );
        retVal = DEM_IRT_OK;
    }
    Dem_Data_ResetSearchStartPosition();

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_FFD_GetSizeOfFreezeFrameByIndividualRecordNumber     */
/* Description   | Gets the size of freeze frame data by the individual re- */
/*               | cord number.                                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        index of the event                                */
/*               | [in] RecordNumber :                                      */
/*               |        This parameter is a unique identifier for a free- */
/*               |        ze frame record as defined in ISO 15031-5 and IS- */
/*               |        O 14229-1.This record number is unique per DTC (- */
/*               |        relative addressing). The value 0xFF is not allo- */
/*               |        wed.The value 0x00 indicates the DTC-specific OB- */
/*               |        D freeze frame.                                   */
/*               | [out] SizeOfFreezeFramePtr :                             */
/*               |        Number of bytes in the requested freeze frame re- */
/*               |        cord.                                             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Size successfully returned.          */
/*               |        DEM_IRT_NG :                                      */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : Record number is no- */
/*               |        t supported by configuration and therefore inval- */
/*               |        id or Record number is DEM_FFRECNUM_FOR_OBD       */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_FFD_GetFreezeFrameData.        */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFD_GetSizeOfFreezeFrameByIndividualRecordNumber
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_u32_FFDOutputTotalSizeType, AUTOMATIC, AUTOMATIC ) SizeOfFreezeFramePtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexFromLatchList;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) underClearDTC;
    VAR( Dem_u08_FreezeFrameDataType, AUTOMATIC ) freezeFrameDataType;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) sizeAtFFD;

    /*----------------------------------*/
    /*  check record number type.       */
    /*----------------------------------*/
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    if( ( RecordNumber == DEM_FFRECNUM_FOR_OBD_FIRST ) || ( RecordNumber == DEM_FFRECNUM_FOR_OBD_LATEST ) )
    {
        freezeFrameDataType =   DEM_FFD_TYPE_OBDFFD;
    }
    else
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    {
        freezeFrameDataType =   DEM_FFD_TYPE_NONOBDFFD;
    }

    /*----------------------------------*/
    /*  check under the clearDTC.       */
    /*----------------------------------*/
    underClearDTC   =   Dem_Data_GetIsUnderClearDTCOfDisabledRecord();
    if ( underClearDTC == (boolean)FALSE )
    {
        /*  get target eventStrgIndex from record number.               */
        eventStrgIndexFromLatchList =   Dem_Data_SearchTargetEventStrgIndexFromRecordNumber( RecordNumber );
        if ( eventStrgIndexFromLatchList != DEM_EVENTSTRGINDEX_INVALID )
        {
            /*----------------------------------------------------------*/
            /*  supported record number and stored freezeframe data.    */
            /*----------------------------------------------------------*/
            sizeAtFFD   =   ( Dem_u16_FFDStoredIndexType )0U;

#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
            if( freezeFrameDataType == DEM_FFD_TYPE_OBDFFD )
            {
                /* Get the FreezeFrameData for OBD */
                retVal = Dem_Data_GetObdFreezeFrameData( eventStrgIndexFromLatchList, RecordNumber, DEM_FFDGETTYPE_SIZE, NULL_PTR, &sizeAtFFD );
            }
            else
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
            {
                /* Get the FreezeFrameData for non-OBD */
                retVal = Dem_Data_GetFreezeFrameData( eventStrgIndexFromLatchList, RecordNumber, DEM_FFDGETTYPE_SIZE, NULL_PTR, &sizeAtFFD );
            }

            ( *SizeOfFreezeFramePtr ) = ( Dem_u32_FFDOutputTotalSizeType )sizeAtFFD;
        }
        else
        {
            /*----------------------------------------------------------*/
            /*  not stored freezeframe data.                            */
            /*  check supported record number or not.                   */
            /*----------------------------------------------------------*/
            retVal  =   Dem_FFD_CheckSupportedFreezeFrameRecordNumber( EventStrgIndex, RecordNumber, freezeFrameDataType );
            if ( retVal == DEM_IRT_OK )
            {
                /*  supported record number but not stored.     */
                ( *SizeOfFreezeFramePtr ) = ( Dem_u32_FFDOutputTotalSizeType )0U;
            }
        }
    }
    else
    {
        /*----------------------------------------------------------*/
        /*  check supported record number or not.                   */
        /*----------------------------------------------------------*/
        retVal  =   Dem_FFD_CheckSupportedFreezeFrameRecordNumber( EventStrgIndex, RecordNumber, freezeFrameDataType );
        if ( retVal == DEM_IRT_OK )
        {
            /*  supported record number but not stored.     */
            ( *SizeOfFreezeFramePtr ) = ( Dem_u32_FFDOutputTotalSizeType )0U;
        }
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_FFD_GetSizeOfFreezeFrameByAllRecordNumber            */
/* Description   | Gets the size of freeze frame data by the all record nu- */
/*               | mber.                                                    */
/* Preconditions | none                                                     */
/* Parameters    | [out] SizeOfFreezeFramePtr :                             */
/*               |        Number of bytes in the all freeze frame records.  */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_FFD_GetSizeOfFreezeFrameByAllRecordNumber
(
    P2VAR( Dem_u32_FFDOutputTotalSizeType, AUTOMATIC, AUTOMATIC ) SizeOfFreezeFramePtr
)
{
    VAR( boolean, AUTOMATIC ) underClearDTC;

    ( *SizeOfFreezeFramePtr ) = ( Dem_u32_FFDOutputTotalSizeType )0U;

    /*----------------------------------*/
    /*  check under the clearDTC.       */
    /*----------------------------------*/
    underClearDTC   =   Dem_Data_GetIsUnderClearDTCOfDisabledRecord();
    if ( underClearDTC == (boolean)FALSE )
    {
        ( *SizeOfFreezeFramePtr ) = Dem_Data_GetSizeOfAllStoredFreezeFrame();
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_FFD_GetFreezeFrameData                               */
/* Description   | Gets freeze frame data by DTC.The function stores the d- */
/*               | ata in the provided DestBuffer.                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        index of the event                                */
/*               | [in] RecordNumber :                                      */
/*               |        This parameter is a unique identifier for a free- */
/*               |        ze frame record as defined in ISO 15031-5 and IS- */
/*               |        O 14229-1.This record number is unique per DTC (- */
/*               |        relative addressing). The value 0xFF is not allo- */
/*               |        wed.The value 0x00 indicates the DTC-specific OB- */
/*               |        D freeze frame.                                   */
/*               | [out] DestBufferPtr :                                    */
/*               |        This parameter contains a byte pointer that poin- */
/*               |        ts to the buffer, to which the freeze frame data  */
/*               |         record shall be written to.The format is: {Reco- */
/*               |        rdNumber, NumOfDIDs, DID[1], data[1], ..., DID[N- */
/*               |        ], data[N]}                                       */
/*               | [in/out] BufSizePtr :                                    */
/*               |        When the function is called this parameter conta- */
/*               |        ins the maximum number of data bytes that can be  */
/*               |         written to the buffer.The function returns the - */
/*               |        actual number of written data bytes in this para- */
/*               |        meter.                                            */
/*               | [out] NextRecordNumberPtr :                              */
/*               |        This parameter contains a pointer that points to  */
/*               |        the buffer, to which the next required Record nu- */
/*               |        mber will be written.                             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Size successfully returned.          */
/*               |        DEM_IRT_NG :                                      */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : Record number is no- */
/*               |        t supported by configuration and therefore inval- */
/*               |        id or Record number is DEM_FFRECNUM_FOR_OBD       */
/*               |        DEM_IRT_WRONG_BUFFERSIZE : provided buffer size - */
/*               |        to small                                          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | refactor function.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFD_GetFreezeFrameData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufSizePtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) NextRecordNumberPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexFromLatchList;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) underClearDTC;
    VAR( Dem_u08_FreezeFrameDataType, AUTOMATIC ) freezeFrameDataType;


    /*----------------------------------*/
    /*  check record number type.       */
    /*----------------------------------*/
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    if( ( RecordNumber == DEM_FFRECNUM_FOR_OBD_FIRST ) || ( RecordNumber == DEM_FFRECNUM_FOR_OBD_LATEST ) )
    {
        freezeFrameDataType =   DEM_FFD_TYPE_OBDFFD;
    }
    else
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    {
        freezeFrameDataType =   DEM_FFD_TYPE_NONOBDFFD;
    }

    /*----------------------------------*/
    /*  check under the clearDTC.       */
    /*----------------------------------*/
    underClearDTC   =   Dem_Data_GetIsUnderClearDTCOfDisabledRecord();
    if ( underClearDTC == (boolean)FALSE )
    {
        /*  get target eventStrgIndex from record number.               */
        eventStrgIndexFromLatchList  =   Dem_Data_SearchTargetEventStrgIndexFromRecordNumber( RecordNumber );
        if ( eventStrgIndexFromLatchList != DEM_EVENTSTRGINDEX_INVALID )
        {
            /*----------------------------------------------------------*/
            /*  supported record number and stored freezeframe data.    */
            /*----------------------------------------------------------*/
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
            if( freezeFrameDataType == DEM_FFD_TYPE_OBDFFD )
            {
                /* Get the FreezeFrameData for OBD */
                retVal = Dem_Data_GetObdFreezeFrameData( eventStrgIndexFromLatchList, RecordNumber, DEM_FFDGETTYPE_DATA, DestBufferPtr, BufSizePtr );
            }
            else
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
            {
                /* Get the FreezeFrameData for non-OBD */
                retVal = Dem_Data_GetFreezeFrameData( eventStrgIndexFromLatchList, RecordNumber, DEM_FFDGETTYPE_DATA, DestBufferPtr, BufSizePtr );
            }
        }
        else
        {
            /*----------------------------------------------------------*/
            /*  not stored freezeframe data.                            */
            /*  check supported record number or not.                   */
            /*----------------------------------------------------------*/
            retVal  =   Dem_FFD_CheckSupportedFreezeFrameRecordNumber( EventStrgIndex, RecordNumber, freezeFrameDataType );
            if ( retVal == DEM_IRT_OK )
            {
                /*  supported record number but not stored.     */
                *BufSizePtr =   ( Dem_u16_FFDStoredIndexType )0U;
            }
        }

        if (( retVal == DEM_IRT_OK ) || ( retVal == DEM_IRT_WRONG_RECORDNUMBER ))
        {
            /*  set next record number.     */
            Dem_Data_SetNextRecordNumber( RecordNumber, NextRecordNumberPtr );
        }
        else
        if ( retVal == DEM_IRT_WRONG_BUFFERSIZE )
        {
            /*  if buffer overflow occurred, output same record number. */
            *NextRecordNumberPtr = RecordNumber;
        }
        else
        {
            *NextRecordNumberPtr = DEM_RECORDNUMBER_NEXT_NONE;
        }
    }
    else
    {
        /*----------------------------------------------------------*/
        /*  check supported record number or not.                   */
        /*----------------------------------------------------------*/
        retVal  =   Dem_FFD_CheckSupportedFreezeFrameRecordNumber( EventStrgIndex, RecordNumber, freezeFrameDataType );
        if ( retVal == DEM_IRT_OK )
        {
            /*  supported record number but not stored.     */
            *BufSizePtr =   ( Dem_u16_FFDStoredIndexType )0U;
        }
        /*  end of get data.        */
        *NextRecordNumberPtr = DEM_RECORDNUMBER_NEXT_NONE;
    }
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_FFD_CheckSupportedFreezeFrameRecordNumber            */
/* Description   | check support record number.                             */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] RecordNumber :                                      */
/*               | [in] FreezeFrameDataType :                               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Retrieving the freeze frame data wa- */
/*               |        s successful.                                     */
/*               |        DEM_IRT_NG : Retrieving the freeze frame data wa- */
/*               |        s failed.                                         */
/*               |        DEM_IRT_WRONG_RECORD_NUMBER : The wrong record n- */
/*               |        umber was passed.                                 */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFD_CheckSupportedFreezeFrameRecordNumber
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u08_FreezeFrameDataType, AUTOMATIC ) FreezeFrameDataType      /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) pairEventStrgIndex;
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )           */

    /*----------------------------------------------------------*/
    /*  not stored freezeframe data.                            */
    /*  check supported record number or not.                   */
    /*----------------------------------------------------------*/
    retVal  =   Dem_Data_CheckSupportedFreezeFrameRecordNumber( EventStrgIndex, RecordNumber, FreezeFrameDataType );

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    if ( retVal != DEM_IRT_OK )
    {
        /*  get pair event.     */
        pairEventStrgIndex  =   Dem_DataCtl_GetEventStrgIndexOfDisabledRecordPairEvent();

        if ( pairEventStrgIndex != DEM_EVENTSTRGINDEX_INVALID )
        {
            retVal  =   Dem_Data_CheckSupportedFreezeFrameRecordNumber( pairEventStrgIndex, RecordNumber, FreezeFrameDataType );
        }
    }
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )           */

    return retVal;
}


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
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
