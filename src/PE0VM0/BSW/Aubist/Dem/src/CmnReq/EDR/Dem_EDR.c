/* Dem_EDR_c(v5-8-0)                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/EDR/CODE                                              */
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
#include "../../../inc/Dem_CmnLib_DataElement.h"
#include "../../../inc/Dem_CmnLib_EDR.h"
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include "../../../inc/Dem_Pm_Misfire.h"
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_EDR_REC_NUM_POS         ((Dem_u16_EDRRecordSizeType)0U)
#define DEM_EDR_DATA_POS            ((Dem_u16_EDRRecordSizeType)1U)

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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EDR_SearchExtendedDataRecord
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_u08_GetExtendDataModeType, AUTOMATIC ) GetExtendDataMode,
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr,
    P2VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC, AUTOMATIC ) NextExtendedDataNumberPtr,
    P2VAR( Dem_u08_EDRClassRefIndexType, AUTOMATIC, AUTOMATIC ) SearchEDRClassRefIndexPtr
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EDR_GetData
(
    VAR( Dem_u08_EDRClassIndexType, AUTOMATIC ) EdrClassIndex,
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber,
    VAR( Dem_u08_GetExtendDataModeType, AUTOMATIC ) GetExtendDataMode,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr
);

static FUNC( boolean, DEM_CODE ) Dem_EDR_JudgeEventByRecordNumber
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber
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
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_EDR_GetExtendedDataRecord                            */
/* Description   | Gets extended data record by DTC.The function stores the */
/*               | data in the provided DestBuffer.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        index of the event                                */
/*               | [in] DTCValue                                            */
/*               | [in] ExtendedDataNumber :                                */
/*               |        Identification/Number of requested extended data  */
/*               |        record. The values 0xFE and 0xFF are not allowed. */
/*               | [out] DestBufferPtr :                                    */
/*               |        This parameter contains a byte pointer that poin- */
/*               |        ts to the buffer, to which the extended data rec- */
/*               |        ord shall be written to. The format is raw hexad- */
/*               |        ecimal values and contains no header-information. */
/*               | [in/out] BufSizePtr :                                    */
/*               |        When the function is called this parameter conta- */
/*               |        ins the maximum number of data bytes that can be  */
/*               |         written to the buffer.The function returns the - */
/*               |        actual number of written data bytes in this para- */
/*               |        meter.                                            */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Size successfully returned.          */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : Record number is no- */
/*               |        t supported by configuration                      */
/*               |        DEM_IRT_WRONG_BUFFERSIZE : provided buffer size - */
/*               |        to small                                          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EDR_GetEventExtendedData
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) nextExtendedDataNumber;
    VAR( Dem_u08_EDRClassRefIndexType, AUTOMATIC ) nextSearchIndex;

    /*  set search index in ExtendedTable by Event. */
    nextSearchIndex =   (Dem_u08_EDRClassRefIndexType)0U;

    retVal  =   Dem_EDR_SearchExtendedDataRecord( EventCtrlIndex, DTCValue, DEM_EDR_GETEDRMODE_EVENT, ExtendedDataNumber, DestBufferPtr, BufSizePtr, &nextExtendedDataNumber, &nextSearchIndex );       /* [GUDCHK:CALLER]EventCtrlIndex */

    return retVal;
}


#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_EDR_GetDTCExtendedData                               */
/* Description   | Gets extended data record by DTC.The function stores the */
/*               | data in the provided DestBuffer.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        index of the event                                */
/*               | [in] DTCValue                                            */
/*               | [in] ExtendedDataNumber :                                */
/*               |        Identification/Number of requested extended data  */
/*               |        record. The values 0xFE and 0xFF are not allowed. */
/*               | [out] DestBufferPtr :                                    */
/*               |        This parameter contains a byte pointer that poin- */
/*               |        ts to the buffer, to which the extended data rec- */
/*               |        ord shall be written to. The format is raw hexad- */
/*               |        ecimal values and contains no header-information. */
/*               | [in/out] BufSizePtr :                                    */
/*               |        When the function is called this parameter conta- */
/*               |        ins the maximum number of data bytes that can be  */
/*               |         written to the buffer.The function returns the - */
/*               |        actual number of written data bytes in this para- */
/*               |        meter.                                            */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Size successfully returned.          */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : Record number is no- */
/*               |        t supported by configuration                      */
/*               |        DEM_IRT_WRONG_BUFFERSIZE : provided buffer size - */
/*               |        to small                                          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-8-0      | new created. based on Dem_EDR_GetEventExtendedData().    */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EDR_GetDTCExtendedData
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) nextExtendedDataNumber;
    VAR( Dem_u08_EDRClassRefIndexType, AUTOMATIC ) nextSearchIndex;

    /*  set search index in ExtendedTable by Event. */
    nextSearchIndex =   (Dem_u08_EDRClassRefIndexType)0U;

    retVal  =   Dem_EDR_SearchExtendedDataRecord( EventCtrlIndex, DTCValue, DEM_EDR_GETEDRMODE_DTC, ExtendedDataNumber, DestBufferPtr, BufSizePtr, &nextExtendedDataNumber, &nextSearchIndex );     /* [GUDCHK:CALLER]EventCtrlIndex */

    return retVal;
}
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_EDR_GetSizeOfExtendedDataRecord                      */
/* Description   | Gets the size of extended data record.                   */
/* Preconditions | none                                                     */
/* Parameters    | [out] SizeOfExtendedDataRecordPtr :                      */
/*               |        Size of the requested extended data record(s) in- */
/*               |        cluding record number size.                       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Size successfully returned           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EDR_GetSizeOfExtendedDataRecord
(
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) SizeOfExtendedDataRecordPtr
)
{
    *SizeOfExtendedDataRecordPtr = 0U;

    return DEM_IRT_OK;
}


/****************************************************************************/
/* Function Name | Dem_EDR_GetExtendedDataRecord                            */
/* Description   | Gets extended data record by DTC.The function stores the */
/*               | data in the provided DestBuffer.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        index of the event                                */
/*               | [in] DTCValue                                            */
/*               | [in] ExtendedDataNumber :                                */
/*               |        Identification/Number of requested extended data  */
/*               |        record. The values 0xFE and 0xFF are not allowed. */
/*               | [out] DestBufferPtr :                                    */
/*               |        This parameter contains a byte pointer that poin- */
/*               |        ts to the buffer, to which the extended data rec- */
/*               |        ord shall be written to. The format is raw hexad- */
/*               |        ecimal values and contains no header-information. */
/*               | [in/out] BufSizePtr :                                    */
/*               |        When the function is called this parameter conta- */
/*               |        ins the maximum number of data bytes that can be  */
/*               |         written to the buffer.The function returns the - */
/*               |        actual number of written data bytes in this para- */
/*               |        meter.                                            */
/*               | [out] NextExtendedDataNumberPtr :                        */
/*               |        This parameter contains a pointer that points to  */
/*               |        the buffer, to which the next required extended - */
/*               |        data number will be written.                      */
/*               | [in/out] SearchEDRClassRefIndexPtr :                     */
/*               |        search EDR Table index.                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Size successfully returned.          */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : Record number is no- */
/*               |        t supported by configuration                      */
/*               |        DEM_IRT_WRONG_BUFFERSIZE : provided buffer size - */
/*               |        to small                                          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-6-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EDR_GetExtendedDataRecord
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr,
    P2VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC, AUTOMATIC ) NextExtendedDataNumberPtr,
    P2VAR( Dem_u08_EDRClassRefIndexType, AUTOMATIC, AUTOMATIC ) SearchEDRClassRefIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_EDRClassRefIndexType, AUTOMATIC ) nextSearchIndex;
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) destBufferDataPtr;
    VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC ) bufSize;

    retVal  =   DEM_IRT_WRONG_BUFFERSIZE;
    *NextExtendedDataNumberPtr = ExtendedDataNumber;

    /*  set search index in ExtendedTable by Event. */
    if ( *BufSizePtr >= DEM_EDR_DATA_POS )
    {
        nextSearchIndex     =   *SearchEDRClassRefIndexPtr;
        bufSize             =   *BufSizePtr  - DEM_EDR_DATA_POS;

        if ( bufSize > ( Dem_u16_EDRRecordSizeType )0U )
        {
            destBufferDataPtr   =   &DestBufferPtr[DEM_EDR_DATA_POS];/* [ARYCHK] *BufSizePtr / 1 / DEM_EDR_DATA_POS */

            retVal  =   Dem_EDR_SearchExtendedDataRecord( EventCtrlIndex, DTCValue, DEM_EDR_GETEDRMODE_DTC, ExtendedDataNumber, destBufferDataPtr, &bufSize, NextExtendedDataNumberPtr, &nextSearchIndex );     /* [GUDCHK:CALLER]EventCtrlIndex */
            if ( retVal == DEM_IRT_OK )
            {
                if ( bufSize > ( Dem_u16_EDRRecordSizeType )0U )
                {
                    /*  set extendedRecordNumber.       */
                    DestBufferPtr[DEM_EDR_REC_NUM_POS]  =   ExtendedDataNumber;/* [ARYCHK] *BufSizePtr / 1 / DEM_EDR_REC_NUM_POS */
                    *BufSizePtr =   bufSize + DEM_EDR_DATA_POS;
                }
                else
                {
                    *BufSizePtr =   ( Dem_u16_EDRRecordSizeType )0U;
                }
            }
        }
        /*  set next search index in ExtendedTable by Event.    */
        *SearchEDRClassRefIndexPtr   =   nextSearchIndex;
    }
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_EDR_SearchExtendedDataRecord                         */
/* Description   | Gets extended data record by DTC.The function stores the */
/*               | data in the provided DestBuffer.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventCtrlIndex :      Event index.                  */
/*               | [in] DTCValue                                            */
/*               | [in] GetExtendDataMode                                   */
/*               | [in] ExtendedDataNumber :  Target Record number.         */
/*               | [out] DestBufferPtr :      Data buffer.                  */
/*               | [in/out] BufSizePtr :      Buffer size.                  */
/*               | [out] NextExtendedDataNumberPtr :                        */
/*               |                         :  Next Target Record number.    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success.                             */
/*               |        DEM_IRT_WRONG_RECORDNUMBER :                      */
/*               |                  Record number is not supported.         */
/*               |        DEM_IRT_WRONG_BUFFERSIZE :                        */
/*               |                  provided buffer size to small           */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EDR_SearchExtendedDataRecord
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,                /* [PRMCHK:CALLER] */
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_u08_GetExtendDataModeType, AUTOMATIC ) GetExtendDataMode,
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr,
    P2VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC, AUTOMATIC ) NextExtendedDataNumberPtr,
    P2VAR( Dem_u08_EDRClassRefIndexType, AUTOMATIC, AUTOMATIC ) SearchEDRClassRefIndexPtr
)
{

    P2CONST( AB_83_ConstV Dem_u08_EDRClassIndexType, AUTOMATIC, DEM_CONFIG_DATA ) edrClassRefBuffPtr;
    VAR( Dem_u16_ExDataClassIndexType, AUTOMATIC ) edrDataClassIndex;
    VAR( Dem_u16_ExDataClassIndexType, AUTOMATIC ) edrDataClassMaxIndex;
    VAR( Dem_u08_EDRClassRefIndexType, AUTOMATIC ) edrClassRefMaxNum;
    VAR( Dem_u08_EDRClassRefIndexType, AUTOMATIC ) edrClassRefIndex;
    VAR( Dem_u08_EDRClassIndexType, AUTOMATIC ) edrClassMaxIndex;
    VAR( Dem_u08_EDRClassIndexType, AUTOMATIC ) edrClassIndex;
    VAR( Dem_u08_EDRClassIndexType, AUTOMATIC ) nextEDRClassIndex;
    VAR( Dem_u08_EDRClassRefIndexType, AUTOMATIC ) nextSearchEDRClassRefIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) loopEndFlag;

    *NextExtendedDataNumberPtr  = DEM_RECORDNUMBER_NEXT_NONE;
    edrClassRefMaxNum   = Dem_EDRClassRefNum;
    edrClassMaxIndex    = Dem_EDRClassNum;

    /*  get extendeddata class index        */
    retVal = DEM_IRT_WRONG_RECORDNUMBER;

    nextSearchEDRClassRefIndex  =   edrClassRefMaxNum;

    /*  get extendeddata class index        */
    Dem_CfgInfoCmm_GetExDataClassRef( EventCtrlIndex, &edrDataClassIndex, &edrDataClassMaxIndex );

    /*  ExtendedDataClass is configured in event.       */
    if ( edrDataClassIndex < edrDataClassMaxIndex )                                                                             /* [GUD:if]edrDataClassIndex */
    {
        /*  get Dem_EDRClassTable index buffer address.     */
        edrClassRefBuffPtr  = &( Dem_ExDataClassTable[ edrDataClassIndex ].DemEDRClassRef[(Dem_u08_EDRClassRefIndexType)0U] );  /* [GUD]edrDataClassIndex */
        loopEndFlag = (boolean)FALSE;

        /*  search loop         */
        for( edrClassRefIndex = (*SearchEDRClassRefIndexPtr); edrClassRefIndex < edrClassRefMaxNum; edrClassRefIndex++ )        /* [GUD:for]edrClassRefIndex */
        {
            /*  edrClassRefBuffPtr : Dem_ExDataClassTable[].DemEDRClassRef[]            */
            /*                       Dem_EDRClassRefNum : length of DemEDRClassRef[].   */
            edrClassIndex = edrClassRefBuffPtr[edrClassRefIndex];                                                               /* [GUD]edrClassRefIndex *//* [ARYCHK] DEM_EDR_CLASS_REF_NUM / 1 / edrClassRefIndex */

            if( edrClassIndex < edrClassMaxIndex )                                                                              /* [GUD:if]edrClassIndex */
            {
                /*  configured.             */
                if( Dem_EDRClassTable[edrClassIndex].DemEDRNumber == ExtendedDataNumber )                                       /* [GUD]edrClassIndex */
                {
                    retVal = Dem_EDR_GetData( edrClassIndex, EventCtrlIndex, DTCValue, ExtendedDataNumber, GetExtendDataMode, DestBufferPtr, BufSizePtr );  /* [GUD]edrClassIndex *//* [GUDCHK:CALLER]EventCtrlIndex */

                    if (( retVal == DEM_IRT_OK ) || ( retVal == DEM_IRT_WRONG_RECORDNUMBER ))
                    {
                        /* Set the next search start position */
                        nextSearchEDRClassRefIndex = edrClassRefIndex + (Dem_u08_EDRClassRefIndexType)1U;
                    }
                    else
                    {
                        /*  DEM_IRT_WRONG_BUFFERSIZE.       */
                        nextSearchEDRClassRefIndex = edrClassRefIndex;
                    }
                    loopEndFlag = (boolean)TRUE;
                }
                else if( Dem_EDRClassTable[edrClassIndex].DemEDRNumber > ExtendedDataNumber )                                   /* [GUD]edrClassIndex */
                {
                    /* When the target number does not exist in the setting values after this */
                    nextSearchEDRClassRefIndex = edrClassRefIndex;

                    loopEndFlag = (boolean)TRUE;
                }
                else
                {
                    /*  search next number.     */
                    /* No process */
                }
            }
            else
            {
                /* If no more configured */
                nextSearchEDRClassRefIndex = edrClassRefMaxNum;
                loopEndFlag = (boolean)TRUE;
            }

            if( loopEndFlag == (boolean)TRUE )
            {
                break;
            }
        }

        if( loopEndFlag == (boolean)FALSE )
        {
            /* When there are no more settings to be searched */
            nextSearchEDRClassRefIndex = edrClassRefMaxNum;
        }

        /* Set the number to be acquired next time */
        if( nextSearchEDRClassRefIndex < edrClassRefMaxNum )                                        /* [GUD:if]nextSearchEDRClassRefIndex */
        {
            nextEDRClassIndex = edrClassRefBuffPtr[nextSearchEDRClassRefIndex];                     /* [GUD]nextSearchEDRClassRefIndex *//* [ARYCHK] DEM_EDR_CLASS_REF_NUM / 1 / nextSearchEDRClassRefIndex */
            if( nextEDRClassIndex < edrClassMaxIndex )                                              /* [GUD:if]nextEDRClassIndex */
            {
                /* When the number to be acquired next time is configured */
                *NextExtendedDataNumberPtr = Dem_EDRClassTable[nextEDRClassIndex].DemEDRNumber;     /* [GUD]nextEDRClassIndex */
            }
        }
        /*  set next search index.      */
        *SearchEDRClassRefIndexPtr   =   nextSearchEDRClassRefIndex;
    }

    return retVal;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Dem_EDR_GetData                                          */
/* Description   | Gets extended data record.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] EdrClassIndex :                                     */
/*               |        Index to array elements of Dem_EDRClassTable      */
/*               | [in] EventCtrlIndex :                                    */
/*               |        index of the event                                */
/*               | [in] DTCValue                                            */
/*               | [in] ExtendedDataNumber                                  */
/*               | [in] GetExtendDataMode                                   */
/*               | [out] DestBufferPtr :                                    */
/*               |        This parameter contains a byte pointer that poin- */
/*               |        ts to the buffer, to which the extended data rec- */
/*               |        ord shall be written to. The format is raw hexad- */
/*               |        ecimal values and contains no header-information. */
/*               | [in/out] BufSizePtr :                                    */
/*               |        When the function is called this parameter conta- */
/*               |        ins the maximum number of data bytes that can be  */
/*               |         written to the buffer.The function returns the - */
/*               |        actual number of written data bytes in this para- */
/*               |        meter.                                            */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Size successfully returned.          */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : Record number is no- */
/*               |        t supported by configuration                      */
/*               |        DEM_IRT_WRONG_BUFFERSIZE : provided buffer size - */
/*               |        to small                                          */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-8-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EDR_GetData
(
    VAR( Dem_u08_EDRClassIndexType, AUTOMATIC ) EdrClassIndex,          /* [PRMCHK:CALLER] */
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,        /* [PRMCHK:CALLER] */
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber,
    VAR( Dem_u08_GetExtendDataModeType, AUTOMATIC ) GetExtendDataMode,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr
)
{
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

    P2CONST( AB_83_ConstV Dem_DataElementClassType, AUTOMATIC, DEM_CONFIG_DATA ) dataElementClassPtr;
    P2CONST( AB_83_ConstV Dem_InternalDataElementClassType, AUTOMATIC, DEM_CONFIG_DATA ) internalDataElementClassPtr;
    VAR( Dem_u16_DataElementClassIndexType, AUTOMATIC ) dataElementClassIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Std_ReturnType, AUTOMATIC ) resultOfCallback;
    VAR( boolean, AUTOMATIC ) retJudgeEventByRecordNumber;

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    VAR( Dem_u08_MemoryKindType, AUTOMATIC ) memKind;
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNumber;
#endif  /*  ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )          */

    retJudgeEventByRecordNumber = Dem_EDR_JudgeEventByRecordNumber( EventCtrlIndex, ExtendedDataNumber );   /* [GUDCHK:CALLER]EventCtrlIndex */
    if( retJudgeEventByRecordNumber == (boolean)TRUE )
    {
        dataElementClassIndex = Dem_EDRClassTable[EdrClassIndex].DemDataElementClassRef;                /* [GUDCHK:CALLER]EdrClassIndex *//* [GUD:CFG:IF_GUARDED: EdrClassIndex ]dataElementClassIndex */

        if( Dem_EDRClassTable[EdrClassIndex].DemDataElementKind == DEM_DATA_ELEMENT_KIND_CS_EXTERNAL )  /* [GUDCHK:CALLER]EdrClassIndex */
        {
            dataElementClassPtr = &Dem_DataElementClassTable[dataElementClassIndex];                    /* [GUDCHK:CALLER]EdrClassIndex *//* [GUD:CFG:IF_GUARDED: dataElementClassIndex ]dataElementClassPtr */
            if( dataElementClassPtr->DemDataElementSize <= *BufSizePtr )                                /* [GUDCHK:CALLER]EdrClassIndex */
            {
                eventId =   Dem_CfgInfoCmn_CnvEventCtrlIndexToEventId( EventCtrlIndex );
                monitorData0 = (Dem_MonitorDataType)eventId | DEM_MONITORDATA_EXTENDEDDATA;

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
                memKind =   Dem_CfgInfoCmn_CheckMemoryTypeFromEventCtrlIndex( EventCtrlIndex );
                if ( memKind == DEM_MEMKIND_USERDEFMEM )
                {
                    /* Data Already Acquired.  */
                    /* No process */
                }
                else
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */
                {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                    eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );            /* [GUDCHK:CALLER]EventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */
                    eventKind       =   Dem_CfgInfoPm_GetEventKindOfSpecific_InEvtStrgGrp( eventStrgIndex );

                    if( ( eventKind & DEM_EVTKIND_TYPE_MISFIRE_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_EVENT )
                    {
                        misfireCylinderNumber = Dem_CfgInfoPm_GetMisfireCylinderNumberByUdsDTC( DTCValue );
                        if( misfireCylinderNumber != DEM_MISFIRE_CYL_NUM_INVALID )
                        {
                            monitorData0 = (Dem_MonitorDataType)misfireCylinderNumber | DEM_MONITORDATA_VALUETYPE_MISFIRECYLINDER | DEM_MONITORDATA_EXTENDEDDATA;
                        }
                    }
#endif  /*  ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )          */
                }

                /*  call DataElement callback function      */
                resultOfCallback = Dem_DataElement_ReadData( dataElementClassPtr, DestBufferPtr,  monitorData0 );

                if( resultOfCallback == (Std_ReturnType)E_OK )
                {
                    *BufSizePtr = dataElementClassPtr->DemDataElementSize;                              /* [GUDCHK:CALLER]EdrClassIndex */
                }
                else
                {
                    *BufSizePtr = (Dem_u16_EDRRecordSizeType)0U;
                }

                retVal = DEM_IRT_OK;
            }
            else
            {
                retVal = DEM_IRT_WRONG_BUFFERSIZE;
            }
        }
        else
        {
            /* DEM_DATA_ELEMENT_KIND_INTERNAL */
            internalDataElementClassPtr = &Dem_InternalDataElementClassTable[dataElementClassIndex];        /* [GUDCHK:CALLER]EdrClassIndex *//* [GUD:CFG:IF_GUARDED: dataElementClassIndex ]internalDataElementClassPtr */

#ifndef JGXSTACK
            retVal = internalDataElementClassPtr->DemInternalDataElementReadFnc( EventCtrlIndex, DTCValue, GetExtendDataMode, DestBufferPtr, BufSizePtr );  /* [GUDCHK:CALLER]EdrClassIndex */
#else /* JGXSTACK */
            retVal = Dem_InternalDataElementReadFnc_ForStack( EventCtrlIndex, DTCValue, GetExtendDataMode, DestBufferPtr, BufSizePtr );
#endif /* JGXSTACK */
        }
    }
    else
    {
        retVal = DEM_IRT_WRONG_RECORDNUMBER;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_EDR_JudgeEventByRecordNumber                         */
/* Description   | Judge the event by extended data record number.          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventCtrlIndex :                                    */
/*               | [in] ExtendedDataNumber :                                */
/* Return Value  | boolean                                                  */
/*               |      TRUE  : Judge result is OK.                         */
/*               |      FALSE : Judge result is NG.                         */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-8-0      | new created.                                             */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_EDR_JudgeEventByRecordNumber
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,        /* [PRMCHK:CALLER] */
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) eventOBDKind;
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    VAR( Dem_u08_MemoryKindType, AUTOMATIC ) memKind;
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */

    /*  Judge result is OK.     */
    retVal = (boolean)TRUE;

    if( ( DEM_EDR_RECNUM_90 <= ExtendedDataNumber ) && ( DEM_EDR_RECNUM_9F >= ExtendedDataNumber ) )
    {
        /*  OBD record number.      */
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
        memKind = Dem_CfgInfoCmn_CheckMemoryTypeFromEventCtrlIndex( EventCtrlIndex );           /* [GUDCHK:CALLER]EventCtrlIndex */
        if ( memKind == DEM_MEMKIND_USERDEFMEM )
        {
            /*  UserDefinedMemory   */
            /*  Judge result is NG, because UserDefinedMemory event can not have OBD record number.     */
            retVal = (boolean)FALSE;
        }
        else
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */
        {
            /*  PrimaryMemory       */
            eventOBDKind = Dem_CfgInfoPm_CheckEventKindOfOBD_ByEvtCtrlIdx( EventCtrlIndex );    /* [GUDCHK:CALLER]EventCtrlIndex */
            if( eventOBDKind != (boolean)TRUE )
            {
                /*  nonOBD event.   */
                /*  Judge result is NG, because nonOBD event can not have OBD record number.            */
                retVal = (boolean)FALSE;
            }
        }
    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
