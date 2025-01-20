/* Dem_Control_EDRInfo_c(v5-5-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_EDRInfo/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_EDR.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_EDR.h"
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

static FUNC( boolean, DEM_CODE ) Dem_Control_CheckExtendedDataNumberSupported
(
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_u08_EDRClassRefIndexType, DEM_VAR_NO_INIT )       Dem_EDR_SearchEDRClassRefIndex;

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
/* Function Name | Dem_Control_GetEventExtendedData                         */
/* Description   | Gets extended data record by DTC and the record number   */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [in] RecordNumber :                                      */
/*               |        Identification of requested Extended data record. */
/*               |        Valid values are between 0x01 and 0xEF as defined */
/*               |        in ISO14229-1.                                    */
/*               | [out] DestBufferPtr :                                    */
/*               |        This parameter contains a byte pointer that       */
/*               |        points to the buffer, to which the extended data  */
/*               |        shall be written to. The format is raw hexadecimal*/
/*               |         values and contains no header-information.       */
/*               | [inout] BufSizePtr :                                     */
/*               |        When the function is called this parameter        */
/*               |        contains the maximum number of data bytes that    */
/*               |        can be written to the buffer. The function        */
/*               |        returns the actual number of written data bytes   */
/*               |        in this parameter.                                */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful             */
/*               |        DEM_IRT_NG : Operation was failed                 */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : Record number is no- */
/*               |        t supported by configuration and therefore inval- */
/*               |        id                                                */
/*               |        DEM_IRT_WRONG_BUFFERSIZE : provided buffer size - */
/*               |        to small                                          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetEventExtendedData
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr
)
{
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) dtcValue;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

    retVal = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;
        retTempVal = Dem_Control_GetEventCtrlIndexFromEventId( EventId, &eventCtrlIndex );                              /* [GUD:RET:DEM_IRT_OK] eventCtrlIndex */
        if( retTempVal == DEM_IRT_OK )
        {
            eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );                        /* [GUD] eventCtrlIndex *//* [GUD:RET:IF_GUARDED:eventCtrlIndex]eventStrgIndex */

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
            eventKind       =   Dem_CfgInfoPm_GetEventKindOfSpecific_InEvtStrgGrp( eventStrgIndex );

            if( ( eventKind & DEM_EVTKIND_TYPE_MISFIRE_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_EVENT )
            {
                /* No process */
            }
            else
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */
            {
                /*  get DTC value.      */
                dtcValue        =   Dem_CfgInfoPm_GetUdsDTCValue( eventStrgIndex );         /* [GUD]eventStrgIndex */
                retVal = Dem_EDR_GetEventExtendedData( eventCtrlIndex, dtcValue, RecordNumber, DestBufferPtr, BufSizePtr ); /* [GUD] eventCtrlIndex */
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_GetSizeOfExtendedDataRecordByDTC             */
/* Description   | Gets the size of the extended data record by DTC and the */
/*               |  record number                                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTC :                                               */
/*               |        Diagnostic Trouble Code in UDS format.            */
/*               | [in] DTCOrigin :                                         */
/*               |        If the Dem supports more than one event memory, - */
/*               |        this parameter is used to select the source memo- */
/*               |        ry the DTCs shall be read from.                   */
/*               | [in] ExtendedDataNumber :                                */
/*               |        Identification/Number of requested extended data  */
/*               |        record.                                           */
/*               | [out] SizeOfExtendedDataRecordPtr :                      */
/*               |        Size of the requested extended data record(s) in- */
/*               |        cluding record number size.                       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Size successfully returned           */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : wrong recordNumber   */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetSizeOfExtendedDataRecordByDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber,
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) SizeOfExtendedDataRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( boolean, AUTOMATIC ) supported;

    retTempVal = Dem_Control_CheckDisableDTCInfo( DTCValue, DTCOrigin );
    if( retTempVal == DEM_IRT_OK )
    {
        /*  check record number.        */
        supported   =   Dem_Control_CheckExtendedDataNumberSupported( ExtendedDataNumber );

        if ( supported == (boolean)TRUE )
        {
            /* When specified DTC is in update disable status */
            retVal = Dem_EDR_GetSizeOfExtendedDataRecord( SizeOfExtendedDataRecordPtr );
            Dem_EDR_SearchEDRClassRefIndex  =   ( Dem_u08_EDRClassRefIndexType )0U;
        }
        else
        {
            retVal = DEM_IRT_WRONG_RECORDNUMBER;
        }
    }
    else
    {
        /* When specified DTC is not in update disable status */
        retVal = retTempVal;
        *SizeOfExtendedDataRecordPtr = 0U;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_GetExtendedDataRecordByDTC                   */
/* Description   | Gets extended data record by DTC and the record number   */
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
/*               | [out] DestBufferPtr :                                    */
/*               |        the buffer, to which the extended data record sh- */
/*               |        all be written to                                 */
/*               | [in/out] BufSizePtr :                                    */
/*               |        the actual number of written data bytes           */
/*               | [out] NextExtendedDataNumberPtr :                        */
/*               |        This parameter contains a pointer that points to  */
/*               |        the buffer, to which the next required Record nu- */
/*               |        mber will be written.                             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Size successfully returned           */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : Record number is no- */
/*               |        t supported by configuration and therefore inval- */
/*               |        id                                                */
/*               |        DEM_IRT_WRONG_BUFFERSIZE : provided buffer size - */
/*               |        to small                                          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetExtendedDataRecordByDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr,
    P2VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC, AUTOMATIC ) NextExtendedDataNumberPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) disableEventStrgIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u08_EDRClassRefIndexType, AUTOMATIC )       searchEDRClassRefIndex;

    retTempVal = Dem_Control_CheckDisableDTCInfo( DTCValue, DTCOrigin );
    if( retTempVal == DEM_IRT_OK )
    {
        /* When specified DTC is in update disable status */
        disableEventStrgIndex = Dem_Control_GetDisableDTCRecordEvent();
        eventCtrlIndex  =   Dem_CmbEvt_GetDelegateEventCtrlIndex_InEvtStrgGrp( disableEventStrgIndex );

        searchEDRClassRefIndex  =   Dem_EDR_SearchEDRClassRefIndex; /*  set search index        */
        retVal = Dem_EDR_GetExtendedDataRecord( eventCtrlIndex, DTCValue, ExtendedDataNumber, DestBufferPtr, BufSizePtr, NextExtendedDataNumberPtr, &searchEDRClassRefIndex );
        Dem_EDR_SearchEDRClassRefIndex  =   searchEDRClassRefIndex; /*  update search index     */
    }
    else
    {
        /* When specified DTC is not in update disable status */
        retVal = retTempVal;
        *BufSizePtr = 0U;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_CheckExtendedDataNumberSupported             */
/* Description   | check record number supoprted.                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] ExtendedDataNumber :                                */
/*               |        Identification/Number of requested extended data  */
/*               |        record.                                           */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : supported.                                */
/*               |        FALSE : not supported.                            */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Control_CheckExtendedDataNumberSupported
(
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber
)
{
    VAR( boolean, AUTOMATIC ) supported;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) disableEventStrgIndex;
    VAR( Dem_u08_EDRBehaviorAt0xFEType, AUTOMATIC ) dtcExtDataRecordsBehaviorAt0xFE;

    /*  getdisable update record event.     */
    disableEventStrgIndex = Dem_Control_GetDisableDTCRecordEvent();
    if ( ExtendedDataNumber == DEM_EDR_RECNUM_00 )
    {
        /*  not supoprted.      */
        supported   =   (boolean)FALSE;
    }
    else if ( ExtendedDataNumber == DEM_EDR_RECNUM_FE )
    {
        /*  FE check pattern.       */
        dtcExtDataRecordsBehaviorAt0xFE =   Dem_DTCExtDataRecordsBehaviorAt0xFE;
        if ( dtcExtDataRecordsBehaviorAt0xFE == DEM_EDRNUM_FE_ALWAYS_NOT_SUPPORT )
        {
            /*  not supoprted.      */
            supported   =   (boolean)FALSE;
        }
        else
        {
            supported   =   Dem_EDR_CheckExtendedDataNumberSupportByRange( disableEventStrgIndex );
        }
    }
    else
    {
        /*  0x01 - 0xFD,0xFF : supported.        */
        supported   =   (boolean)TRUE;
    }
    return supported;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
