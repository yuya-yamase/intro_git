/* Dem_UdmControl_FFDInfo_c(v5-7-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmControl_FFDInfo/CODE                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_AsyncReq.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Udm_DataAvl.h"
#include "../../../inc/Dem_Udm_Control.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
#include "../../../inc/Dem_Udm_ExternalMem.h"
#include "../../../inc/Dem_Rc_UdmMngTable.h"    /*  for Dem_UdmExcFncTable[]    */

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
/* Function Name | Dem_UdmControl_GetSizeOfFreezeFrameByDTC                 */
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
/*               |        DEM_IRT_NG : condition error.                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmControl_GetSizeOfFreezeFrameByDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_u32_FFDOutputTotalSizeType, AUTOMATIC, AUTOMATIC ) SizeOfFreezeFramePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmDisableEventIndex;
    VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC ) memType;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;

    retTempVal = Dem_UdmControl_CheckDisableDTCInfo( DTCValue, DTCOrigin, &memType,  &udmGroupKindIndex );  /* [GUD:RET:DEM_IRT_OK]memType, udmGroupKindIndex */
    if( retTempVal == DEM_IRT_OK )
    {
        if ( memType == DEM_MEMORYTYPE_INVALID )
        {
            /*  illegal DTC origin.     */
            retVal = DEM_IRT_WRONG_DTCORIGIN;
        }
        else if ( memType == DEM_MEMORYTYPE_EXTERNAL )
        {
            /*  mirror memory.          */
            retVal  =   Dem_UdmExternal_GetSizeOfFreezeFrameByDTC( DTCValue, DTCOrigin, RecordNumber, SizeOfFreezeFramePtr );
        }
        else
        {
            /*--------------------------------------------------------------------------*/
            /* Need to get exclusive [SchM_Enter_Dem_Udm_<ShortName>_EventMemory].      */
            /* These are the reasons why this function needs to get exclusive.          */
            /*  - This function call [DataMng] function directory.                      */
            /*  - This function called from SW-C/Dcm context.                           */
            /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
#ifndef JGXSTACK
            Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveEnterFnc();  /* [GUD]udmGroupKindIndex *//* waits completion of updating Diag record data by Dem_MainFunction.      */
            Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveExitFnc();   /* [GUD]udmGroupKindIndex */
#else   /* JGXSTACK */
            Dem_UdmExcEnterFnc_ForStack();
            Dem_UdmExcExitFnc_ForStack();
#endif  /* JGXSTACK */
            /*--------------------------------------------------------------------------*/

            /* When specified DTC is in update disable status */
            udmDisableEventIndex = Dem_UdmControl_GetDisableDTCRecordEvent();
            retVal = Dem_UdmFFD_GetSizeOfFreezeFrame( udmDisableEventIndex, RecordNumber, SizeOfFreezeFramePtr );
        }
    }
    else
    {
        /* When specified DTC is not in update disable status */
        retVal = DEM_IRT_OK;
        *SizeOfFreezeFramePtr = 0U;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmControl_GetFreezeFrameDataByDTC                   */
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
/*               |        DEM_IRT_PENDING : The requested value is calcula- */
/*               |        ted asynchronously and currently not available. - */
/*               |        The caller can retry later.                       */
/*               |        DEM_IRT_NG : condition error.                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmControl_GetFreezeFrameDataByDTC
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
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmDisableEventIndex;
    VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC ) memType;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;

    retTempVal = Dem_UdmControl_CheckDisableDTCInfo( DTCValue, DTCOrigin, &memType,  &udmGroupKindIndex );  /* [GUD:RET:DEM_IRT_OK]memType, udmGroupKindIndex */
    if( retTempVal == DEM_IRT_OK )
    {
        if ( memType == DEM_MEMORYTYPE_INVALID )
        {
            /*  illegal DTC origin.     */
            retVal = DEM_IRT_WRONG_DTCORIGIN;
        }
        else if ( memType == DEM_MEMORYTYPE_EXTERNAL )
        {
            /*  mirror memory.          */
            retVal = Dem_UdmExternal_GetFreezeFrameDataByDTC( DTCValue, DTCOrigin, RecordNumber, DestBufferPtr, BufSizePtr, NextRecordNumberPtr );
        }
        else
        {
            /*--------------------------------------------------------------------------*/
            /* Need to get exclusive [SchM_Enter_Dem_Udm_<ShortName>_EventMemory].      */
            /* These are the reasons why this function needs to get exclusive.          */
            /*  - This function call [DataMng] function directory.                      */
            /*  - This function called from SW-C/Dcm context.                           */
            /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
#ifndef JGXSTACK
            Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveEnterFnc();  /* [GUD]udmGroupKindIndex *//* waits completion of updating Diag record data by Dem_MainFunction.      */
            Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveExitFnc();   /* [GUD]udmGroupKindIndex */
#else   /* JGXSTACK */
            Dem_UdmExcEnterFnc_ForStack();
            Dem_UdmExcExitFnc_ForStack();
#endif  /* JGXSTACK */
            /*--------------------------------------------------------------------------*/

            /* When specified DTC is in update disable status */
            udmDisableEventIndex = Dem_UdmControl_GetDisableDTCRecordEvent();
            retVal = Dem_UdmFFD_GetFreezeFrameData( udmDisableEventIndex, RecordNumber, DestBufferPtr, BufSizePtr, NextRecordNumberPtr );
        }
    }
    else
    {
        /* When specified DTC is not in update disable status */
        retVal = DEM_IRT_OK;
        *BufSizePtr = 0U;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmControl_GetUserDefinedMemoryFreezeFrameRecordNumber   */
/* Description   | Gets freeze frame data by DTC and the record number fro- */
/*               | m freeze frame record.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCValue :                                          */
/*               |        Diagnostic Trouble Code in UDS format             */
/*               | [in] DTCOrigin :                                         */
/*               |        select the source memory the DTCs shall be read - */
/*               |        from                                              */
/*               | [out] RecordNumBufferPtr :                               */
/*               |        the buffer, to which the freeze frame data recor- */
/*               |        d shall be written to                             */
/*               | [in/out] RecordNumPtr :                                  */
/*               |        the actual number of written data bytes           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Size successfully returned           */
/*               |        DEM_IRT_EXTERNAL_MEMORY                           */
/*               |          : DTCOrigin is not output support.              */
/*               |        DEM_IRT_WRONG_DTCORIGIN : wrong DTC origin        */
/*               |        DEM_IRT_WRONG_DTC : DTC value not existing (in U- */
/*               |        DS format)                                        */
/*               |        DEM_IRT_WRONG_BUFFERSIZE : provided buffer size - */
/*               |        to small                                          */
/*               |        DEM_IRT_NG : condition error.                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmControl_GetUserDefinedMemoryFreezeFrameRecordNumber
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, DEM_APPL_DATA ) RecordNumBufferPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) RecordNumPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retSaveDisabledRecord;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetEventIndex;
    VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC ) memType;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    /* set initial vale. */
    retVal = DEM_IRT_WRONG_DTCORIGIN;
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    /* get UDM info index and memory type by DTCOrigin. */
    memType = Dem_CfgInfoUdm_GetUserDefinedMemoryTypeByDTCOrigin( DTCOrigin, &udmInfoTableIndex ); /* [GUD:RET:Not DEM_MEMORYTYPE_INVALID] udmInfoTableIndex */

    if( memType == DEM_MEMORYTYPE_INVALID )
    {
        /* No process */
    }
    else if ( memType == DEM_MEMORYTYPE_EXTERNAL )
    {
        /*  illegal DTC origin.     */
        retVal = DEM_IRT_EXTERNAL_MEMORY;
    }
    else
    {
        /* Get udm event index by DTCValue. */
        retGetEventIndex = Dem_UdmDataAvl_GetUdmEventIndexByDTC( DTCValue, udmInfoTableIndex, &udmEventIndex ); /* [GUD:RET:DEM_IRT_OK]udmEventIndex *//* [GUD]udmInfoTableIndex */

        if( retGetEventIndex == DEM_IRT_OK )
        {
            /* Get udm group index by event index. */
            udmGroupKindIndex = Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndexByEventIndex( udmInfoTableIndex, udmEventIndex );                  /* [GUD]udmInfoTableIndex *//* [GUD]udmEventIndex */

            if( udmGroupKindIndex < userDefinedMemoryNum )  /* [GUD:if]udmGroupKindIndex */
            {
                /*--------------------------------------------------------------------------*/
                /* Need to get exclusive [SchM_Enter_Dem_Udm_<ShortName>_EventMemory].      */
                /* These are the reasons why this function needs to get exclusive.          */
                /*  - This function call [DataMng] function directory.                      */
                /*  - This function called from SW-C/Dcm context.                           */
                /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
#ifndef JGXSTACK
                Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveEnterFnc();  /* [GUD]udmGroupKindIndex *//* waits completion of updating Diag record data by Dem_MainFunction.      */
                Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveExitFnc();   /* [GUD]udmGroupKindIndex */
#else   /* JGXSTACK */
                Dem_UdmExcEnterFnc_ForStack();
                Dem_UdmExcExitFnc_ForStack();
#endif  /* JGXSTACK */
                /*--------------------------------------------------------------------------*/

                /*--------------------------------------*/
                /*  latch target record number.         */
                /*--------------------------------------*/
                retSaveDisabledRecord   =   Dem_UdmControl_DisableDTCRecordUpdate( DTCValue, DTCOrigin );
                if ( retSaveDisabledRecord == DEM_IRT_OK )
                {
                    /*--------------------------------------*/
                    /*  set record number to buffer.        */
                    /*--------------------------------------*/
                    /*  DEM_IRT_OK / DEM_IRT_WRONG_BUFFERSIZE */
                    retVal  =   Dem_UdmData_GetAllRecordNumber( RecordNumBufferPtr, RecordNumPtr );

                    /*  end of get data.                */
                    Dem_UdmControl_EnableDTCRecordUpdate();
                }
                else
                {
                    /* DEM_IRT_PENDING */
                    /* Because DTCValue and DTCOrigin is already checked, DEM_IRT_WRONG_DTC or DEM_IRT_WRONG_DTCORIGIN is not return. */
                    /*  another process getting data.       */
                    retVal = DEM_IRT_NG;
                }
            }
            else
            {
                retVal = DEM_IRT_WRONG_DTC;
            }
        }
        else
        {
            retVal = DEM_IRT_WRONG_DTC;
        }
    }

    return retVal;
}


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
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
