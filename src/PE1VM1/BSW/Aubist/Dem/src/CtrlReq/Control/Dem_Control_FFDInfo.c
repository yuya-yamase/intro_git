/* Dem_Control_FFDInfo_c(v5-5-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_FFDInfo/CODE                                  */
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
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_Pm_FFD.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Pm_DTC.h"
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

/*--------------------------------------------------------------------------*/
/* Unit External functions                                                  */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Function Name | Dem_Control_GetEventFreezeFrameData                      */
/* Description   | Gets freeze frame data by event id from freeze frame re- */
/*               | cord.                                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        Identification of an event by assigned EventId    */
/*               | [in] RecordNumber :                                      */
/*               |        a unique identifier for a freeze frame record.0x- */
/*               |        FF means most recent freeze frame record is retu- */
/*               |        rned.                                             */
/*               | [in] DataID :                                            */
/*               |        This parameter specifies the PID (ISO15031-5 map- */
/*               |        ped in UDS range 0xF400 - 0xF4FF) or DID (ISO142- */
/*               |        29-1) that shall be copied to the destination bu- */
/*               |        ffer                                              */
/*               | [out] DestBufferPtr :                                    */
/*               |        the buffer, to which the freeze frame data recor- */
/*               |        d shall be written to                             */
/*               | [in/out] BufferSizePtr :                                 */
/*               |        the buffer size, to which the freeze frame data - */
/*               |        record shall be written to                        */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful             */
/*               |        DEM_IRT_NODATAAVAILABLE : The requested event da- */
/*               |        ta is not currently stored (but the request was   */
/*               |        valid)                                            */
/*               |        DEM_IRT_WRONG_DIDNUMBER : The requested DID is n- */
/*               |        ot supported by the freeze frame                  */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : The requestedrecord  */
/*               |         number is not supported by the event             */
/*               |        DEM_IRT_WRONG_BUFFERSIZE : Wrong buffer size      */
/*               |        DEM_IRT_NG : Operation failed                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetEventFreezeFrameData
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventID,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u16_DIDNumberType, AUTOMATIC ) DataID,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufferSizePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal = DEM_IRT_NG;

    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        retTempVal = Dem_Control_GetEventCtrlIndexFromEventId( EventID, &eventCtrlIndex );                              /* [GUD:RET:DEM_IRT_OK] eventCtrlIndex */
        if( retTempVal == DEM_IRT_OK )
        {
            /*--------------------------------------------------------------------------*/
            /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
            /* These are the reasons why this function needs to get exclusive.          */
            /*  - This function call [DataMng] function directory.                      */
            /*  - This function called from SW-C/Dcm context.                           */
            /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
            SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
            SchM_Exit_Dem_EventMemory();
            /*--------------------------------------------------------------------------*/
            eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );                        /* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */
            retTempVal = Dem_FFD_GetEventFreezeFrameData( eventStrgIndex, RecordNumber, DataID, DestBufferPtr, BufferSizePtr );
            switch( retTempVal )
            {
                case DEM_IRT_OK:
                    /* The same processing as DEM_IRT_WRONGBUFFERSIZE */
                case DEM_IRT_NODATAAVAILABLE:
                    /* The same processing as DEM_IRT_WRONGBUFFERSIZE */
                case DEM_IRT_WRONG_DIDNUMBER:
                    /* The same processing as DEM_IRT_WRONGBUFFERSIZE */
                case DEM_IRT_WRONG_RECORDNUMBER:
                    /* The same processing as DEM_IRT_WRONGBUFFERSIZE */
                case DEM_IRT_WRONG_BUFFERSIZE:
                    /* Directly return the return value of Dem_FFD_GetEventFreezeFrameData() */
                    retVal = retTempVal;
                    break;
                default:
                    /* When a value except the above is returned */
                    /* No process */
                    break;
            }
        }
        else
        {
            /* Error */
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
/* Function Name | Dem_Control_GetSizeOfFreezeFrameByDTC                    */
/* Description   | Gets the size of the freeze frame record by DTC and the  */
/*               |  record number                                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCValue :                                          */
/*               |        Diagnostic Trouble Code in UDS format             */
/*               | [in] DTCOrigin :                                         */
/*               |        select the source memory the DTCs shall be read - */
/*               |        from                                              */
/*               | [in] RecordNumber :                                      */
/*               |        a unique identifier for a freeze frame record.Th- */
/*               |        e value 0xFF is explicitly allowed to request th- */
/*               |        e overall size                                    */
/*               | [out] SizeOfFreezeFramePtr :                             */
/*               |        Number of bytes in the requested freeze frame re- */
/*               |        cord                                              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Size successfully returned           */
/*               |        DEM_IRT_WRONG_DTC : DTC value not existing (in U- */
/*               |        DS format)                                        */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : Record number is no- */
/*               |        t supported by configuration and therefore inval- */
/*               |        id                                                */
/*               |        DEM_IRT_PENDING : The requested value is calcula- */
/*               |        ted asynchronously and currently not available. - */
/*               |        The caller can retry later.                       */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetSizeOfFreezeFrameByDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_u32_FFDOutputTotalSizeType, AUTOMATIC, AUTOMATIC ) SizeOfFreezeFramePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal = DEM_IRT_WRONG_DTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) disableEventStrgIndex;

    retTempVal = Dem_Control_CheckDisableDTCInfo( DTCValue, DTCOrigin );
    if( retTempVal == DEM_IRT_OK )
    {
        /* When specified DTC is in update disable status */
        disableEventStrgIndex = Dem_Control_GetDisableDTCRecordEvent();

        retTempVal = Dem_FFD_GetSizeOfFreezeFrame( disableEventStrgIndex, RecordNumber, SizeOfFreezeFramePtr );
        if( retTempVal == DEM_IRT_OK )
        {
           retVal = DEM_IRT_OK;
        }
        else if( retTempVal == DEM_IRT_WRONG_RECORDNUMBER )
        {
           retVal = DEM_IRT_WRONG_RECORDNUMBER;
        }
        else
        {
           /* When DEM_IRT_WRONG_DTC or the return value except the above */
           /* is returned from Dem_FFD_GetSizeOfFreezeFrame() */
           /* No process */
        }
    }
    else
    {
        /* When specified DTC is not in update disable status */
        retVal = retTempVal;
        *SizeOfFreezeFramePtr = 0U;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_GetFreezeFrameDataByDTC                      */
/* Description   | Gets freeze frame data by DTC and the record number fro- */
/*               | m freeze frame record.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCValue :                                          */
/*               |        Diagnostic Trouble Code in UDS format             */
/*               | [in] DTCOrigin :                                         */
/*               |        select the source memory the DTCs shall be read - */
/*               |        from                                              */
/*               | [in] RecordNumber :                                      */
/*               |        a unique identifier for a freeze frame record.Th- */
/*               |        e value 0xFF is not allowed.The value 0x00 indic- */
/*               |        ates the DTC-specific OBD freeze frame.           */
/*               | [out] DestBufferPtr :                                    */
/*               |        the buffer, to which the freeze frame data recor- */
/*               |        d shall be written to                             */
/*               | [in/out] BufSizePtr :                                    */
/*               |        the actual number of written data bytes           */
/*               | [out] NextRecordNumberPtr :                              */
/*               |        This parameter contains a pointer that points to  */
/*               |        the buffer, to which the next required Record nu- */
/*               |        mber will be written.                             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Size successfully returned           */
/*               |        DEM_IRT_WRONG_DTC : DTC value not existing (in U- */
/*               |        DS format)                                        */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : Record number is no- */
/*               |        t supported by configuration and therefore inval- */
/*               |        id                                                */
/*               |        DEM_IRT_WRONG_BUFFERSIZE : provided buffer size - */
/*               |        to small                                          */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetFreezeFrameDataByDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufSizePtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) NextRecordNumberPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal = DEM_IRT_WRONG_DTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) disableEventStrgIndex;

    retTempVal = Dem_Control_CheckDisableDTCInfo( DTCValue, DTCOrigin );
    if( retTempVal == DEM_IRT_OK )
    {
        /* When specified DTC is in update disable status */
        disableEventStrgIndex = Dem_Control_GetDisableDTCRecordEvent();
        retTempVal = Dem_FFD_GetFreezeFrameData( disableEventStrgIndex, RecordNumber, DestBufferPtr, BufSizePtr, NextRecordNumberPtr );
        switch( retTempVal )
        {
            case DEM_IRT_OK:
                /* The same processing as DEM_IRT_WRONG_BUFFERSIZE */
            case DEM_IRT_WRONG_RECORDNUMBER:
                /* The same processing as DEM_IRT_WRONG_BUFFERSIZE */
            case DEM_IRT_WRONG_BUFFERSIZE:
                /* Directly return the return value of Dem_FFD_GetFreezeFrameData() */
                retVal = retTempVal;
                break;
            default:
                /* When a value except the above is returned */
                /* No process */
                break;
        }
    }
    else
    {
        /* When specified DTC is not in update disable status */
        retVal = retTempVal;
        *BufSizePtr = 0U;
    }

    return retVal;
}

/*--------------------------------------------------------------------------*/
/* Unit Internal functions(process)                                         */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Unit Internal functions(data)                                            */
/*--------------------------------------------------------------------------*/

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
