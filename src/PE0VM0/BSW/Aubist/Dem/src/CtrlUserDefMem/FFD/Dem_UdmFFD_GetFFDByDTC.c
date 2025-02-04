/* Dem_UdmFFD_GetFFDByDTC_c(v5-5-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmFFD_GetFFDByDTC/CODE                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Udm_Data.h"

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
/* Function Name | Dem_UdmFFD_GetSizeOfFreezeFrame                          */
/* Description   | Gets the size of freeze frame data by DTC.               */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventIndex :                                        */
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
/*               |        DEM_IRT_WRONG_RECORDNUMBER :                      */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFFD_GetSizeOfFreezeFrame
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_u32_FFDOutputTotalSizeType, AUTOMATIC, AUTOMATIC ) SizeOfFreezeFramePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u32_FFDOutputTotalSizeType, AUTOMATIC ) allSize;
    VAR( boolean, AUTOMATIC ) retUdmDTCClerTarget;

    /*  get record size.          */
    allSize   =   (Dem_u32_FFDOutputTotalSizeType)0U;
    retVal = Dem_UdmData_GetSizeOfFreezeFrameOfDisabledRecord( UdmEventIndex, RecordNumber, &allSize );

    /*  execute DTC clear ?         */
    retUdmDTCClerTarget = Dem_UdmDTC_JudgeUdmDTCClearTarget( UdmEventIndex );
    if( retUdmDTCClerTarget == (boolean)TRUE )
    {
        /*  clear target.           */
        allSize   =   (Dem_u32_FFDOutputTotalSizeType)0U;
    }

    *SizeOfFreezeFramePtr   =   allSize;
    Dem_UdmData_ResetSearchStartPosition();

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmFFD_GetFreezeFrameData                            */
/* Description   | Gets freeze frame data by DTC.The function stores the d- */
/*               | ata in the provided DestBuffer.                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |        index of the Udm event                            */
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
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFFD_GetFreezeFrameData
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufSizePtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) NextRecordNumberPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultCheckRec;
    VAR( boolean, AUTOMATIC ) retUdmDTCClerTarget;

    retVal = DEM_IRT_WRONG_RECORDNUMBER;

    /* Check whether RecordNumber is configured */
    resultCheckRec = Dem_UdmData_CheckRecordNumberInDisabledRecord( UdmEventIndex, RecordNumber );

    if( resultCheckRec == DEM_IRT_OK )
    {
        /* Get the FreezeFrameData for non-OBD */
        retVal = Dem_UdmData_GetFreezeFrameData( UdmEventIndex, RecordNumber, DEM_FFDGETTYPE_DATA, DestBufferPtr, BufSizePtr );
    }

    /*------------------------------------------*/
    /*  judge of output NextRecordNumberPtr.    */
    /*------------------------------------------*/
    retUdmDTCClerTarget = Dem_UdmDTC_JudgeUdmDTCClearTarget( UdmEventIndex );
    if( retUdmDTCClerTarget == (boolean)FALSE )
    {
        if(( retVal == DEM_IRT_OK ) || ( retVal == DEM_IRT_WRONG_RECORDNUMBER ))
        {
            Dem_UdmData_SetNextRecordNumber( RecordNumber, NextRecordNumberPtr );
        }
        else if ( retVal == DEM_IRT_WRONG_BUFFERSIZE )
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
        /* If it is being cleared, the response is returned as cleared, */
        /* so FFD is not stored and the next record number is none. */
        *NextRecordNumberPtr = DEM_RECORDNUMBER_NEXT_NONE;
    }

    return retVal;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )      */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
