/* Dem_Control_IFCmn_c(v5-6-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_IFCmn/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#include "../../../inc/Dem_CmnIf_Control.h"
#include "../../../inc/Dem_CmnLib_Control.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Udm_Control.h"
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
#include "../../../inc/Dem_Rc_UdmMngTable.h"
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */

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
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_ControlIFCmn_DisableDTCRecordUpdate                  */
/* Description   | Disables the event memory update of a specific DTC (onl- */
/*               | y one at one time).                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTC :                                               */
/*               |        Selects the DTC in UDS format, for which DTC rec- */
/*               |        ord update shall be disabled.                     */
/*               | [in] DTCOrigin :                                         */
/*               |        If the Dem supports more than one event memory, - */
/*               |        this parameter is used to select the source memo- */
/*               |        ry for which DTC record update shall be disabled. */
/* Return Value  | Dem_ReturnDisableDTCRecordUpdateType                     */
/*               |        DEM_DISABLE_DTCRECUP_OK : success                 */
/*               |        DEM_DISABLE_DTCRECUP_WRONG_DTC : wrong DTC        */
/*               |        DEM_DISABLE_DTCRECUP_WRONG_DTCORIGIN : wrong DTC  */
/*               |         origin                                           */
/*               |        DEM_DISABLE_DTCRECUP_PENDING : pending            */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_DisableDTCRecordUpdate
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )     /*  [FuncSw]    */
    VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC ) memType;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )     /*  [FuncSw]    */
        if( ( DTCOrigin & DEM_DTC_ORIGIN_USERDEFINED_MEMORY ) == DEM_DTC_ORIGIN_USERDEFINED_MEMORY )
        {
            memType = Dem_CfgInfoUdm_GetUserDefinedMemoryTypeByDTCOrigin( DTCOrigin, &udmInfoTableIndex );  /* [GUD:RET:Not DEM_MEMORYTYPE_INVALID] udmInfoTableIndex */
            if( memType != DEM_MEMORYTYPE_INVALID )
            {
                retVal = Dem_UdmControl_DisableDTCRecordUpdate( DTCValue, DTCOrigin );
            }
            else
            {
                retVal = DEM_IRT_WRONG_DTCORIGIN;
            }
        }
        else
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */
        if( DTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY )
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
            retVal = Dem_Control_DisableDTCRecordUpdate( DTCValue, DTCOrigin );
        }
        else
        {
            retVal  =   DEM_IRT_WRONG_DTCORIGIN;
        }
    }
    else
    {
        retVal = DEM_IRT_PENDING;
    }
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_ControlIFCmn_EnableDTCRecordUpdate                   */
/* Description   | Enables the event memory update of the DTC disabled by - */
/*               | Dem_DcmDisableDTCRecordUpdate() before.                  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ControlIFCmn_EnableDTCRecordUpdate
( void )
{
    Dem_Control_EnableDTCRecordUpdate();

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )     /*  [FuncSw]    */
    Dem_UdmControl_EnableDTCRecordUpdate();
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )              */

    return ;
}

/****************************************************************************/
/* Function Name | Dem_ControlIFCmn_GetDTCRecordUpdateStatus                */
/* Description   | Gets DTC record update status.                           */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_DTCRecordUpdateStatusType                        */
/*               |        DEM_CTL_STS_DTC_UPDATE_ENABLE : Update status is  */
/*               |         enable.                                          */
/*               |        DEM_CTL_STS_DTC_UPDATE_DISABLE : Update status i- */
/*               |        s disable.                                        */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_DTCRecordUpdateStatusType, DEM_CODE ) Dem_ControlIFCmn_GetDTCRecordUpdateStatus
( void )
{
    VAR( Dem_u08_DTCRecordUpdateStatusType, AUTOMATIC ) retVal;
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    VAR( Dem_u08_DTCRecordUpdateStatusType, AUTOMATIC ) retUdmResult;
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */

    /*  Get PrimaryMemory DTCRecordUpdate status.       */
    retVal = Dem_Control_GetDTCRecordUpdateStatus_PrimaryMemory();

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    if ( retVal != DEM_CTL_STS_DTC_UPDATE_DISABLE )
    {
        /*  PrimaryMemory is enable status.     */

        /*  Check UserDefinedMemory status.     */
        retUdmResult = Dem_UdmControl_GetDTCRecordUpdateStatus();
        if ( retUdmResult == DEM_CTL_STS_DTC_UPDATE_DISABLE )
        {
            retVal = DEM_CTL_STS_DTC_UPDATE_DISABLE;
        }
    }
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_ControlIFCmn_GetStatusOfDTC                          */
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
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_GetStatusOfDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatus
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )     /*  [FuncSw]    */
    VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC ) memType;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
        if( ( DTCOrigin & DEM_DTC_ORIGIN_USERDEFINED_MEMORY ) == DEM_DTC_ORIGIN_USERDEFINED_MEMORY )
        {
            memType = Dem_CfgInfoUdm_GetUserDefinedMemoryTypeByDTCOrigin( DTCOrigin, &udmInfoTableIndex );  /* [GUD:RET:Not DEM_MEMORYTYPE_INVALID] udmInfoTableIndex */
            if( memType != DEM_MEMORYTYPE_INVALID )
            {
                retVal = Dem_UdmControl_GetStatusOfDTC( DTCValue, DTCOrigin , DTCStatus );
            }
            else
            {
                retVal = DEM_IRT_WRONG_DTCORIGIN;
            }
        }
        else
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */
        if( DTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY )
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
            retVal = Dem_Control_GetStatusOfDTC( DTCValue, DTCOrigin , DTCStatus );
        }
        else
        {
            retVal  =   DEM_IRT_WRONG_DTCORIGIN;
        }
    }
    else
    {
        retVal  =   DEM_IRT_NG;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_ControlIFCmn_GetSizeOfFreezeFrameByDTC               */
/* Description   | Gets the size of the freeze frame record by DTC and the  */
/*               | record number.                                           */
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
/*               |        DEM_IRT_WRONG_DTCORIGIN : wrong DTC origin        */
/*               |        DEM_IRT_WRONG_DTC : DTC value not existing (in U- */
/*               |        DS format)                                        */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : Record number is no- */
/*               |        t supported by configuration and therefore inval- */
/*               |        id                                                */
/*               |        DEM_IRT_PENDING : The requested value is calcula- */
/*               |        ted asynchronously and currently not available. - */
/*               |        The caller can retry later.                       */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_GetSizeOfFreezeFrameByDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_u32_FFDOutputTotalSizeType, AUTOMATIC, AUTOMATIC ) SizeOfFreezeFrame
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    if( ( DTCOrigin & DEM_DTC_ORIGIN_USERDEFINED_MEMORY ) == DEM_DTC_ORIGIN_USERDEFINED_MEMORY )
    {
        retVal = Dem_UdmControl_GetSizeOfFreezeFrameByDTC( DTCValue, DTCOrigin , RecordNumber , SizeOfFreezeFrame );
    }
    else
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */
    if( DTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY )
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
        retVal = Dem_Control_GetSizeOfFreezeFrameByDTC( DTCValue, DTCOrigin , RecordNumber , SizeOfFreezeFrame );
    }
    else
    {
        retVal  =   DEM_IRT_WRONG_DTCORIGIN;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_ControlIFCmn_GetFreezeFrameDataByDTC                 */
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
/*               |        DEM_IRT_WRONG_DTCORIGIN : wrong DTC origin        */
/*               |        DEM_IRT_WRONG_DTC : DTC value not existing (in U- */
/*               |        DS format)                                        */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : Record number is no- */
/*               |        t supported by configuration and therefore inval- */
/*               |        id                                                */
/*               |        DEM_IRT_WRONG_BUFFERSIZE : provided buffer size - */
/*               |        to small                                          */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_GetFreezeFrameDataByDTC
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
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )     /*  [FuncSw]    */
    VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC ) memType;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )     /*  [FuncSw]    */
    if( ( DTCOrigin & DEM_DTC_ORIGIN_USERDEFINED_MEMORY ) == DEM_DTC_ORIGIN_USERDEFINED_MEMORY )
    {
        memType = Dem_CfgInfoUdm_GetUserDefinedMemoryTypeByDTCOrigin( DTCOrigin, &udmInfoTableIndex );  /* [GUD:RET:Not DEM_MEMORYTYPE_INVALID] udmInfoTableIndex */
        if( memType != DEM_MEMORYTYPE_INVALID )
        {
            retVal = Dem_UdmControl_GetFreezeFrameDataByDTC( DTCValue , DTCOrigin , RecordNumber , DestBufferPtr , BufSizePtr, NextRecordNumberPtr );
        }
        else
        {
            retVal = DEM_IRT_WRONG_DTCORIGIN;
        }
    }
    else
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )              */
    if( DTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY )
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
        retVal = Dem_Control_GetFreezeFrameDataByDTC( DTCValue , DTCOrigin , RecordNumber , DestBufferPtr , BufSizePtr, NextRecordNumberPtr );
    }
    else
    {
        retVal  =   DEM_IRT_WRONG_DTCORIGIN;
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
/*               |        record. Additionally the values 0xFE and 0xFF are */
/*               |        explicitly allowed to request the overall size of */
/*               |        all OBD records / all records.                    */
/*               | [out] SizeOfExtendedDataRecordPtr :                      */
/*               |        Size of the requested extended data record(s) in- */
/*               |        cluding record number size.                       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Size successfully returned           */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : wrong recordNumber   */
/*               |        DEM_IRT_WRONG_DTCORIGIN    : wrong DTCOrigin      */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_GetSizeOfExtendedDataRecordByDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber,
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) SizeOfExtendedDataRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    if( ( DTCOrigin & DEM_DTC_ORIGIN_USERDEFINED_MEMORY ) == DEM_DTC_ORIGIN_USERDEFINED_MEMORY )
    {
        retVal = Dem_UdmControl_GetSizeOfExtendedDataRecordByDTC( DTCValue , DTCOrigin , ExtendedDataNumber, SizeOfExtendedDataRecordPtr );
    }
    else
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */
    if( DTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY )
    {
        retVal = Dem_Control_GetSizeOfExtendedDataRecordByDTC( DTCValue , DTCOrigin , ExtendedDataNumber, SizeOfExtendedDataRecordPtr );
    }
    else
    {
        retVal  =   DEM_IRT_WRONG_DTCORIGIN;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_ControlIFCmn_GetExtendedDataRecordByDTC              */
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
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_GetExtendedDataRecordByDTC
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

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    if( ( DTCOrigin & DEM_DTC_ORIGIN_USERDEFINED_MEMORY ) == DEM_DTC_ORIGIN_USERDEFINED_MEMORY )
    {
        retVal = Dem_UdmControl_GetExtendedDataRecordByDTC( DTCValue , DTCOrigin , ExtendedDataNumber , DestBufferPtr , BufSizePtr, NextExtendedDataNumberPtr );
    }
    else
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */
    if( DTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY )
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
        retVal = Dem_Control_GetExtendedDataRecordByDTC( DTCValue , DTCOrigin , ExtendedDataNumber , DestBufferPtr , BufSizePtr, NextExtendedDataNumberPtr );
    }
    else
    {
        retVal  =   DEM_IRT_WRONG_DTCORIGIN;
    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/


