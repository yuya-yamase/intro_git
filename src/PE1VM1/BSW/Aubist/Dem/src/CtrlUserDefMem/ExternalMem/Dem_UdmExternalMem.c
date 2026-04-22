/* Dem_UdmExternalMem_c(v5-3-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmExternalMem/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
#include "../../../inc/Dem_Udm_ExternalMem.h"
#include "../../../usr/Dem_ExternalMemory_Callout.h"


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

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST
#include <Dem_MemMap.h>

static CONST( AB_83_ConstV Dem_u08_InternalReturnType   ,DEM_CONST ) Dem_CnvExternalCalloutReturnValueTable[ DEM_EXTERNALMEM_ERRCD_MAX ]    =
{
    DEM_IRT_OK,                         /*  DEM_EXTERNALMEM_OK                    */
    DEM_IRT_PENDING,                    /*  DEM_EXTERNALMEM_PENDING               */
    DEM_IRT_NO_MATCHING_ELEMENT,        /*  DEM_EXTERNALMEM_NO_MATCHING_ELEMENT   */
    DEM_IRT_WRONG_DTC,                  /*  DEM_EXTERNALMEM_WRONG_DTC             */
    DEM_IRT_WRONG_DTCORIGIN,            /*  DEM_EXTERNALMEM_WRONG_DTCORIGIN       */
    DEM_IRT_WRONG_RECORDNUMBER,         /*  DEM_EXTERNALMEM_WRONG_RECNUM          */
    DEM_IRT_WRONG_BUFFERSIZE,           /*  DEM_EXTERNALMEM_BUFFER_TOO_SMALL      */
    DEM_IRT_NG                          /*  DEM_EXTERNALMEM_FAILED                */
};

#define DEM_STOP_SEC_CONST
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_UdmExternal_SetFilteredDTC                           */
/* Description   | The function set the DTC filter.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCOrigin :                                         */
/*               | [in] DTCStatusMask :                                     */
/*               | [in] DTCStatusAvailabilityMask :                         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Filter was accepted                  */
/*               |        DEM_IRT_NG : Wrong filter selected                */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmExternal_SetFilteredDTC
(
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusAvailabilityMask
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_ExternalMemReturnType, AUTOMATIC ) retMirror;

    retVal  =   DEM_IRT_WRONG_DTCORIGIN;
    retMirror   =   Dem_ExternalMem_SetDTCFilter( DTCOrigin, DTCStatusMask, DTCStatusAvailabilityMask );
    if ( retMirror < DEM_EXTERNALMEM_ERRCD_MAX )
    {
        retVal  =   Dem_CnvExternalCalloutReturnValueTable[ retMirror ];
    }


    /*  check return value.     */
    if( ( retVal != DEM_IRT_OK ) && ( retVal != DEM_IRT_WRONG_DTCORIGIN ) )
    {
        retVal  =   DEM_IRT_WRONG_DTCORIGIN;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmExternal_SearchFilteredDTC                        */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCOrigin :                                         */
/*               | [in] DTCStatusMask :                                     */
/*               | [in] DTCStatusAvailabilityMask :                         */
/*               | [out] DTCValuePtr :                                      */
/*               | [out] DTCStatusPtr :                                     */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_PENDING :                                 */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT :                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmExternal_GetNextFilteredDTC
(
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusAvailabilityMask,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_ExternalMemReturnType, AUTOMATIC ) retMirror;

    retVal  =   DEM_IRT_NO_MATCHING_ELEMENT;
    retMirror   =   Dem_ExternalMem_GetNextFilteredDTC( DTCOrigin, DTCStatusMask, DTCStatusAvailabilityMask, DTCValuePtr, DTCStatusPtr );

    if ( retMirror < DEM_EXTERNALMEM_ERRCD_MAX )
    {
        retVal  =   Dem_CnvExternalCalloutReturnValueTable[ retMirror ];
    }

    /*  check return value.     */
    if( ( retVal != DEM_IRT_OK ) && ( retVal != DEM_IRT_PENDING ) && ( retVal != DEM_IRT_NO_MATCHING_ELEMENT ) )
    {
        retVal  =   DEM_IRT_NO_MATCHING_ELEMENT;
    }


    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmExternal_GetStatusOfDTC                           */
/* Description   | Gets status of DTC by DTC from event record.             */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCValue :                                          */
/*               |        Diagnostic Trouble Code in UDS format             */
/*               | [in] DTCOrigin :                                         */
/*               |        select the source memory the DTCs shall be read - */
/*               |        from                                              */
/*               | [out] DTCStatusPtr :                                     */
/*               |        the status information of the requested DTC       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Status of DTC is OK                  */
/*               |        DEM_IRT_WRONG_DTC : DTC value not existing (in t- */
/*               |        his format)                                       */
/*               |        DEM_IRT_WRONG_DTCORIGIN : Wrong DTC origin        */
/*               |        DEM_IRT_NG : DTC failed                           */
/*               |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmExternal_GetStatusOfDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusAvailabilityMask,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_ExternalMemReturnType, AUTOMATIC ) retMirror;

    /*  mirror memory.          */
    retVal  =   DEM_IRT_NG;
    retMirror   =   Dem_ExternalMem_GetStatusOfDTC( DTCValue, DTCOrigin, DTCStatusAvailabilityMask, DTCStatusPtr );
    if ( retMirror < DEM_EXTERNALMEM_ERRCD_MAX )
    {
        retVal  =   Dem_CnvExternalCalloutReturnValueTable[ retMirror ];
    }
    /*  check return value.     */
    if( ( retVal != DEM_IRT_OK ) && ( retVal != DEM_IRT_WRONG_DTC ) && ( retVal != DEM_IRT_WRONG_DTCORIGIN ) && ( retVal != DEM_IRT_NG ) )
    {
        retVal  =   DEM_IRT_NG;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmExternal_DisableDTCRecUpdate                      */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCValue :                                          */
/*               | [in] DTCOrigin :                                         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_WRONG_DTC :                               */
/*               |        DEM_IRT_WRONG_DTCORIGIN :                         */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmExternal_DisableDTCRecUpdate
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_ExternalMemReturnType, AUTOMATIC ) retMirror;

    retVal  =   DEM_IRT_WRONG_DTCORIGIN;
    retMirror   =   Dem_ExternalMem_StartOfGettingDTCRecord( DTCValue, DTCOrigin );
    if ( retMirror < DEM_EXTERNALMEM_ERRCD_MAX )
    {
        retVal  =   Dem_CnvExternalCalloutReturnValueTable[ retMirror ];
    }
    /*  check return value.     */
    if( ( retVal != DEM_IRT_OK ) && ( retVal != DEM_IRT_WRONG_DTC ) && ( retVal != DEM_IRT_WRONG_DTCORIGIN ) )
    {
        retVal  =   DEM_IRT_WRONG_DTCORIGIN;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmExternal_EnableDTCRecUpdate                       */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCValue :                                          */
/*               | [in] DTCOrigin :                                         */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmExternal_EnableDTCRecUpdate
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    Dem_ExternalMem_EndOfGettingDTCRecord( DTCValue, DTCOrigin );

    return ;
}

/****************************************************************************/
/* Function Name | Dem_UdmExternal_GetSizeOfFreezeFrameByDTC                */
/* Description   | Gets the size of the freeze frame record by DTC and the  */
/*               |  record number                                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCValue :                                          */
/*               | [in] DTCOrigin :                                         */
/*               | [in] RecordNumber :                                      */
/*               | [out] SizeOfFreezeFramePtr :                             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_WRONG_DTC :                               */
/*               |        DEM_IRT_WRONG_RECORDNUMBER :                      */
/*               |        DEM_IRT_PENDING :                                 */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmExternal_GetSizeOfFreezeFrameByDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_u32_FFDOutputTotalSizeType, AUTOMATIC, AUTOMATIC ) SizeOfFreezeFramePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_ExternalMemReturnType, AUTOMATIC ) retMirror;

    retVal  =   DEM_IRT_WRONG_DTCORIGIN;

    retMirror   =   Dem_ExternalMem_GetSizeOfFreezeFrameByDTC( DTCValue, DTCOrigin, RecordNumber, SizeOfFreezeFramePtr );
    if ( retMirror < DEM_EXTERNALMEM_ERRCD_MAX )
    {
        retVal  =   Dem_CnvExternalCalloutReturnValueTable[ retMirror ];
    }
    /*  check return value.     */
    if( ( retVal != DEM_IRT_OK ) && ( retVal != DEM_IRT_WRONG_DTC ) && ( retVal != DEM_IRT_WRONG_DTCORIGIN ) && ( retVal != DEM_IRT_WRONG_RECORDNUMBER ) && ( retVal != DEM_IRT_PENDING ) )
    {
        retVal  =   DEM_IRT_WRONG_DTCORIGIN;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmExternal_GetFreezeFrameDataByDTC                  */
/* Description   | Gets freeze frame data by DTC and the record number fro- */
/*               | m freeze frame record.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCValue :                                          */
/*               | [in] DTCOrigin :                                         */
/*               | [in] RecordNumber :                                      */
/*               | [out] DestBufferPtr :                                    */
/*               | [in/out] BufSizePtr :                                    */
/*               | [out] NextRecordNumberPtr :                              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_WRONG_DTC :                               */
/*               |        DEM_IRT_WRONG_RECORDNUMBER :                      */
/*               |        DEM_IRT_WRONG_BUFFERSIZE :                        */
/*               |        DEM_IRT_PENDING :                                 */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmExternal_GetFreezeFrameDataByDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufSizePtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) NextRecordNumberPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_ExternalMemReturnType, AUTOMATIC ) retMirror;

    retVal  =   DEM_IRT_WRONG_DTCORIGIN;

    retMirror   =   Dem_ExternalMem_GetFreezeFrameDataByDTC( DTCValue, DTCOrigin, RecordNumber, DestBufferPtr, BufSizePtr, NextRecordNumberPtr );
    if ( retMirror < DEM_EXTERNALMEM_ERRCD_MAX )
    {
        retVal  =   Dem_CnvExternalCalloutReturnValueTable[ retMirror ];
    }
    /*  check return value.     */
    if( ( retVal != DEM_IRT_OK ) && ( retVal != DEM_IRT_WRONG_DTC ) && ( retVal != DEM_IRT_WRONG_DTCORIGIN ) && ( retVal != DEM_IRT_WRONG_RECORDNUMBER ) && ( retVal != DEM_IRT_WRONG_BUFFERSIZE ) && ( retVal != DEM_IRT_PENDING ) )
    {
        retVal  =   DEM_IRT_WRONG_DTCORIGIN;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmExternal_GetSizeOfExtendedDataRecordByDTC         */
/* Description   | Gets the size of the extenddata record by DTC and the    */
/*               |  record number                                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCValue :                                          */
/*               | [in] DTCOrigin :                                         */
/*               | [in] ExtendedDataNumber :                                */
/*               | [out] SizeOfExtendedDataRecordPtr :                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_WRONG_DTC :                               */
/*               |        DEM_IRT_WRONG_RECORDNUMBER :                      */
/*               |        DEM_IRT_PENDING :                                 */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmExternal_GetSizeOfExtendedDataRecordByDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber,
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) SizeOfExtendedDataRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_ExternalMemReturnType, AUTOMATIC ) retMirror;

    retVal  =   DEM_IRT_WRONG_DTCORIGIN;
    retMirror   =   Dem_ExternalMem_GetSizeOfExtendedDataRecordByDTC( DTCValue, DTCOrigin, ExtendedDataNumber, SizeOfExtendedDataRecordPtr );
    if ( retMirror < DEM_EXTERNALMEM_ERRCD_MAX )
    {
        retVal  =   Dem_CnvExternalCalloutReturnValueTable[ retMirror ];
    }
    /*  check return value.     */
    if( ( retVal != DEM_IRT_OK ) && ( retVal != DEM_IRT_WRONG_DTC ) && ( retVal != DEM_IRT_WRONG_DTCORIGIN ) && ( retVal != DEM_IRT_WRONG_RECORDNUMBER ) )
    {
        retVal  =   DEM_IRT_WRONG_DTCORIGIN;
    }


    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmExternal_GetExtendedDataRecordByDTC               */
/* Description   | Gets freeze frame data by DTC and the record number fro- */
/*               | m freeze frame record.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCValue :                                          */
/*               | [in] DTCOrigin :                                         */
/*               | [in] ExtendedDataNumber :                                */
/*               | [out] DestBufferPtr :                                    */
/*               | [in/out] BufSizePtr :                                    */
/*               | [out] NextRecordNumberPtr :                              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_WRONG_DTC :                               */
/*               |        DEM_IRT_WRONG_RECORDNUMBER :                      */
/*               |        DEM_IRT_WRONG_BUFFERSIZE                          */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmExternal_GetExtendedDataRecordByDTC
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
    VAR( Dem_ExternalMemReturnType, AUTOMATIC ) retMirror;

    retVal  =   DEM_IRT_WRONG_DTCORIGIN;

    retMirror   =   Dem_ExternalMem_GetExtendedDataRecordByDTC( DTCValue, DTCOrigin, ExtendedDataNumber, DestBufferPtr, BufSizePtr, NextExtendedDataNumberPtr );
    if ( retMirror < DEM_EXTERNALMEM_ERRCD_MAX )
    {
        retVal  =   Dem_CnvExternalCalloutReturnValueTable[ retMirror ];
    }
    /*  check return value.     */
    if( ( retVal != DEM_IRT_OK ) && ( retVal != DEM_IRT_WRONG_DTC ) && ( retVal != DEM_IRT_WRONG_DTCORIGIN ) && ( retVal != DEM_IRT_WRONG_RECORDNUMBER ) && ( retVal != DEM_IRT_WRONG_BUFFERSIZE ) )
    {
        retVal  =   DEM_IRT_WRONG_DTCORIGIN;
    }


    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )      */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
