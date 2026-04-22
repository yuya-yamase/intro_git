/* Dem_UdmControl_EDRInfo_c(v5-8-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmControl_EDRInfo/CODE                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_EDR.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
#include "../../../inc/Dem_Udm_Control.h"
#include "../../../inc/Dem_Udm_Data.h"
#include "../../../inc/Dem_Udm_ExternalMem.h"
#include "Dem_Udm_Control_local.h"

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

static FUNC( boolean, DEM_CODE ) Dem_UdmControl_CheckExtendedDataNumberSupported
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

static VAR( Dem_u08_EDRClassRefIndexType, DEM_VAR_NO_INIT )       Dem_UdmEDR_SearchEDRClassRefIndex;


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
/* Function Name | Dem_UdmControl_SetDisableRecordUpdateInfoForEDR          */
/* Description   | Disable record update action for EDR.                    */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-8-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmControl_SetDisableRecordUpdateInfoForEDR
( void )
{
    Dem_UdmEDR_SearchEDRClassRefIndex   =   ( Dem_u08_EDRClassRefIndexType )0U;
    return ;
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
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmControl_GetSizeOfExtendedDataRecordByDTC
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
            retVal  =   Dem_UdmExternal_GetSizeOfExtendedDataRecordByDTC( DTCValue, DTCOrigin, ExtendedDataNumber, SizeOfExtendedDataRecordPtr );
        }
        else
        {
            /*  check record number.        */
            supported   =   Dem_UdmControl_CheckExtendedDataNumberSupported( ExtendedDataNumber );

            if ( supported == (boolean)TRUE )
            {
                /* When specified DTC is in update disable status */
                retVal = Dem_EDR_GetSizeOfExtendedDataRecord( SizeOfExtendedDataRecordPtr );
            }
            else
            {
                retVal = DEM_IRT_WRONG_RECORDNUMBER;
            }
        }
    }
    else
    {
        /* When specified DTC is not in update disable status */
        retVal = DEM_IRT_OK;
        *SizeOfExtendedDataRecordPtr = 0U;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmControl_GetExtendedDataRecordByDTC                */
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
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmControl_GetExtendedDataRecordByDTC
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
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmDisableEventIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u08_EDRClassRefIndexType, AUTOMATIC )       searchEDRClassRefIndex;
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
            retVal  =   Dem_UdmExternal_GetExtendedDataRecordByDTC( DTCValue, DTCOrigin, ExtendedDataNumber, DestBufferPtr, BufSizePtr, NextExtendedDataNumberPtr );
        }
        else
        {
            /* When specified DTC is in update disable status */
            udmDisableEventIndex = Dem_UdmControl_GetDisableDTCRecordEvent();
            eventCtrlIndex = Dem_CfgInfoUdm_CnvUdmEventIndexToEventCtrlIndex( udmDisableEventIndex );

            searchEDRClassRefIndex  =   Dem_UdmEDR_SearchEDRClassRefIndex;  /*  set search index        */
            retVal = Dem_EDR_GetExtendedDataRecord( eventCtrlIndex, DTCValue, ExtendedDataNumber, DestBufferPtr, BufSizePtr, NextExtendedDataNumberPtr, &searchEDRClassRefIndex );
            Dem_UdmEDR_SearchEDRClassRefIndex   =   searchEDRClassRefIndex; /*  update search index     */
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
/* Function Name | Dem_UdmControl_CheckExtendedDataNumberSupported          */
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
static FUNC( boolean, DEM_CODE ) Dem_UdmControl_CheckExtendedDataNumberSupported
(
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber
)
{
    VAR( boolean, AUTOMATIC ) supported;

    if ( ExtendedDataNumber == DEM_EDR_RECNUM_00 )
    {
        /*  not supoprted.      */
        supported   =   (boolean)FALSE;
    }
    else if ( ExtendedDataNumber == DEM_EDR_RECNUM_FE )
    {
        /*  not supoprted.      */
        supported   =   (boolean)FALSE;
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

#endif /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
