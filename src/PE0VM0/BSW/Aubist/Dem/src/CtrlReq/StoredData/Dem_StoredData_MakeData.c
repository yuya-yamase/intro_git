/* Dem_StoredData_MakeData_c(v5-5-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dem_StoredData_MakeData/CODE                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_StoredData.h"
#include "../../../inc/Dem_CmnLib_DataCtl.h"
#include "../../../inc/Dem_CmnLib_DataCtl_FFDOutputJudge.h"
#include "../../../inc/Dem_Utl.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_DTC.h"
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include "../../../inc/Dem_Pm_Misfire.h"
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Data position according to the parameter of the DTC part of DTCStoredData */
#define DEM_STOREDDATA_RECNUM_POS       ((Dem_u32_StoredDataRecordSizeType)0U)
#define DEM_STOREDDATA_DTC_POS_HI       ((Dem_u32_StoredDataRecordSizeType)1U)
#define DEM_STOREDDATA_DTC_POS_MI       ((Dem_u32_StoredDataRecordSizeType)2U)
#define DEM_STOREDDATA_DTC_POS_LO       ((Dem_u32_StoredDataRecordSizeType)3U)
#define DEM_STOREDDATA_DTDSTATUS_POS    ((Dem_u32_StoredDataRecordSizeType)4U)

#define DEM_STOREDDATA_HEADER_SIZE      ((Dem_u32_StoredDataRecordSizeType)5U)

/* Bit shift level of the 3byte conversion of DTC */
#define DEM_DTC_TRANS_3BYTE_SHIFT_DTC_HI    ((uint8)16U)    /* for High byte   */
#define DEM_DTC_TRANS_3BYTE_SHIFT_DTC_MI    ((uint8)8U)     /* for Middle byte */


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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_StoredData_GetHeaderStoredData
(
    VAR( Dem_u08_StoredDataRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    VAR( Dem_u32_StoredDataRecordSizeType, AUTOMATIC ) BufSize,
    P2VAR( Dem_u32_StoredDataRecordSizeType, AUTOMATIC, AUTOMATIC ) StoredDataSizePtr
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_StoredData_GetBodyStoredData
(
    P2CONST( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) CapturedDataPtr,
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) FreezeFrameClassRef,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    VAR( Dem_u32_StoredDataRecordSizeType, AUTOMATIC ) BufSize,
    P2VAR( Dem_u32_StoredDataRecordSizeType, AUTOMATIC, AUTOMATIC ) StoredDataSizePtr
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>
static VAR( Dem_u32_DTCValueType, DEM_VAR_NO_INIT ) Dem_StoredData_DTCOfStoredData;
static VAR( Dem_UdsStatusByteType, DEM_VAR_NO_INIT ) Dem_StoredData_DTCStatusOfStoredData;
#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_StoredData_SetDTCAndStatusOfStoredData               */
/* Description   | Sets DTC and status for StoredData                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        EventStrgIndex for retrieving of DTC and statusO- */
/*               |        fDTC.                                             */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_StoredData_SetDTCAndStatusOfStoredData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) misfireEventKind;
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

    Dem_StoredData_DTCOfStoredData = DEM_DTC_VALUE_INVALID;
    Dem_StoredData_DTCStatusOfStoredData = DEM_DTCSTATUS_BYTE_ALL_OFF;

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );
    if( misfireEventKind == (boolean)TRUE )
    {
        Dem_Misfire_GetDTCAndStatusOfStoredData( EventStrgIndex, &Dem_StoredData_DTCOfStoredData, &Dem_StoredData_DTCStatusOfStoredData );
    }
    else
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
    {
        (void)Dem_DTC_GetDTCStatusAndUdsDTC( EventStrgIndex, &Dem_StoredData_DTCOfStoredData, &Dem_StoredData_DTCStatusOfStoredData );    /* no return check required */

        /* Invalid DTC is excluded, so it never fails */
    }

    /*------------------------------------------*/
    /*  convert to output statusOfDTC.          */
    /*------------------------------------------*/
    Dem_StoredData_DTCStatusOfStoredData =   Dem_DTC_CnvDTCStatus_PmAvailabilityMask( Dem_StoredData_DTCStatusOfStoredData );

    return;
}

/****************************************************************************/
/* Function Name | Dem_StoredData_GetStoredData                             */
/* Description   | Gets DTC and status of DTC by FaultIndex. The return fo- */
/*               | rmat of data considers UDS service.                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordNumber :                                      */
/*               |        RecordNumber for retrieving of DTC and statusOfD- */
/*               |        TC.                                               */
/*               | [in] CapturedDataPtr : StoredData source FFD or TSFFD    */
/*               | [in] FreezeFrameClassRef : DemFreezeFrameClassRef        */
/*               | [out] DestBufferPtr :                                    */
/*               |        The pointer that points to the buffer, to which - */
/*               |        data shall be written to.                         */
/*               | [in/out] BufSizePtr :                                    */
/*               |        Input: Data size of current buffer Output: Data - */
/*               |        size after the data note to a buffer.             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Size successfully returned           */
/*               |        DEM_IRT_WRONG_BUFFERSIZE : Provided buffer size - */
/*               |        to small                                          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_StoredData_GetStoredData
(
    VAR( Dem_u08_StoredDataRecordNumberType, AUTOMATIC ) RecordNumber,
    P2CONST( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) CapturedDataPtr,
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) FreezeFrameClassRef,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u32_StoredDataRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr
)
{
    VAR( Dem_u32_StoredDataRecordSizeType, AUTOMATIC ) storedDataSize;

    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetHeader;

    storedDataSize = (Dem_u32_StoredDataRecordSizeType)0U;

    retGetHeader = Dem_StoredData_GetHeaderStoredData( RecordNumber, DestBufferPtr, *BufSizePtr, &storedDataSize );
    if( retGetHeader == DEM_IRT_OK )
    {
        retVal = Dem_StoredData_GetBodyStoredData( CapturedDataPtr, FreezeFrameClassRef, DestBufferPtr, *BufSizePtr, &storedDataSize );
    }
    else
    {
        retVal = retGetHeader;
    }

    if( retVal == DEM_IRT_OK )
    {
        *BufSizePtr = storedDataSize;
    }
    else
    {
        *BufSizePtr = (Dem_u32_StoredDataRecordSizeType)0U;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_StoredData_GetHeaderStoredData                       */
/* Description   | Get the header part of StoredData.                       */
/* Preconditions |                                                          */
/* Parameters    | [in] RecordNumber :                                      */
/*               |        Record number of StoredData                       */
/*               |        TC.                                               */
/*               | [out] DestBufferPtr :                                    */
/*               |        The pointer that points to the buffer, to which - */
/*               |        data shall be written to.                         */
/*               | [in] BufSize :                                           */
/*               |        The size of the buffer.                           */
/*               | [in/out] StoredDataSizePtr :                             */
/*               |        Write position and stored data size of DestBuffe- */
/*               |        rPtr                                              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Size successfully returned           */
/*               |        DEM_IRT_WRONG_BUFFERSIZE : Provided buffer size - */
/*               |        to small                                          */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_StoredData_GetHeaderStoredData
(
    VAR( Dem_u08_StoredDataRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    VAR( Dem_u32_StoredDataRecordSizeType, AUTOMATIC ) BufSize,
    P2VAR( Dem_u32_StoredDataRecordSizeType, AUTOMATIC, AUTOMATIC ) StoredDataSizePtr
)
{
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) dtcVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /* Write RecordNumber, DTC, StatusOfDTC */
    if( BufSize >= DEM_STOREDDATA_HEADER_SIZE )
    {
        DestBufferPtr[DEM_STOREDDATA_RECNUM_POS] = RecordNumber;

        dtcVal = Dem_StoredData_DTCOfStoredData;
        dtcVal &= DEM_DTC_VALUE_ALL;
        DestBufferPtr[DEM_STOREDDATA_DTC_POS_HI] = (uint8)(dtcVal >> DEM_DTC_TRANS_3BYTE_SHIFT_DTC_HI);
        DestBufferPtr[DEM_STOREDDATA_DTC_POS_MI] = (uint8)(dtcVal >> DEM_DTC_TRANS_3BYTE_SHIFT_DTC_MI);
        DestBufferPtr[DEM_STOREDDATA_DTC_POS_LO] = (uint8)(dtcVal);

        DestBufferPtr[DEM_STOREDDATA_DTDSTATUS_POS] = Dem_StoredData_DTCStatusOfStoredData;

        *StoredDataSizePtr = DEM_STOREDDATA_HEADER_SIZE;

        retVal = DEM_IRT_OK;
    }
    else
    {
        retVal = DEM_IRT_WRONG_BUFFERSIZE;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_StoredData_GetBodyStoredData                         */
/* Description   | Get the body part of StoredData.                         */
/* Preconditions | Have already obtained the header data.                   */
/*               | [in] CapturedDataPtr : StoredData source FFD or TSFFD    */
/*               | [in] FreezeFrameClassRef : DemFreezeFrameClassRef        */
/*               | [out] DestBufferPtr :                                    */
/*               |        The pointer that points to the buffer, to which - */
/*               |        data shall be written to.                         */
/*               | [in] BufSize :                                           */
/*               |        The size of the buffer.                           */
/*               | [in/out] StoredDataSizePtr :                             */
/*               |        Write position and stored data size of DestBuffe- */
/*               |        rPtr                                              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Size successfully returned           */
/*               |        DEM_IRT_WRONG_BUFFERSIZE : Provided buffer size - */
/*               |        to small                                          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_StoredData_GetBodyStoredData
(
    P2CONST( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) CapturedDataPtr,
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) FreezeFrameClassRef,     /* [PRMCHK:CALLER] */
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    VAR( Dem_u32_StoredDataRecordSizeType, AUTOMATIC ) BufSize,
    P2VAR( Dem_u32_StoredDataRecordSizeType, AUTOMATIC, AUTOMATIC ) StoredDataSizePtr

)
{
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameClassPtr;
    VAR( Dem_u32_DIDClassIndexType, AUTOMATIC ) didClassIndex;
    VAR( Dem_u16_DIDNumberType, AUTOMATIC ) didIdentifier;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) didDataSize;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) capturedIndex;

    VAR( Dem_u08_DIDClassPerFFIndexType, AUTOMATIC ) didClassRefIndex;
    VAR( boolean, AUTOMATIC ) ffdOutputAllow;
    VAR( uint8, AUTOMATIC ) numOfStoredDids;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_WRONG_BUFFERSIZE;

    if( BufSize >= (DEM_STOREDDATA_HEADER_SIZE + DEM_DC_FFRLEN_NUMOFDIDS) )
    {
        *StoredDataSizePtr = *StoredDataSizePtr + DEM_DC_FFRLEN_NUMOFDIDS;                  /*  no wrap around      */

        freezeFrameClassPtr = &Dem_FreezeFrameClassTable[FreezeFrameClassRef];              /* [GUDCHK:CALLER]FreezeFrameClassRef *//* [GUD:CFG:IF_GUARDED: FreezeFrameClassRef ]freezeFrameClassPtr */

        capturedIndex = (Dem_u16_FFDStoredIndexType)0U;
        numOfStoredDids = (uint8)0U;

        for( didClassRefIndex = (Dem_u08_DIDClassPerFFIndexType)0U; didClassRefIndex < freezeFrameClassPtr->DemDidClassNum; didClassRefIndex++ )    /* [GUDCHK:CALLER]FreezeFrameClassRef *//* [GUD:CFG:IF_GUARDED: FreezeFrameClassRef ]didClassRefIndex */
        {
            didClassIndex = freezeFrameClassPtr->DemDidClassRef[didClassRefIndex];                                                                  /* [GUDCHK:CALLER]FreezeFrameClassRef *//* [GUD:CFG:IF_GUARDED: FreezeFrameClassRef ]didClassIndex */

            didIdentifier   = Dem_DIDClassTable[didClassIndex].DemDidIdentifier;                                                                    /* [GUDCHK:CALLER]FreezeFrameClassRef */
            didDataSize     = Dem_DIDClassTable[didClassIndex].DemDidDataSize;                                                                      /* [GUDCHK:CALLER]FreezeFrameClassRef */

            ffdOutputAllow = Dem_Data_GetFFDOutputAllow( didClassIndex, CapturedDataPtr[capturedIndex], &capturedIndex );
            if( ffdOutputAllow == (boolean)TRUE )
            {
                if( BufSize >= (*StoredDataSizePtr + DEM_DC_FFRLEN_DID + didDataSize) )     /*  no wrap around      */
                {
                    DestBufferPtr[*StoredDataSizePtr] = (uint8)( didIdentifier >> DEM_DC_DIDIDENTIFIER_SHIFT );
                    *StoredDataSizePtr = *StoredDataSizePtr + DEM_DC_FFRLEN_DID_MSB;        /*  no wrap around      */

                    DestBufferPtr[*StoredDataSizePtr] = (uint8)( didIdentifier & DEM_DC_DIDIDENTIFIER_MASK );
                    *StoredDataSizePtr = *StoredDataSizePtr + DEM_DC_FFRLEN_DID_LSB;        /*  no wrap around      */

                    Dem_UtlMem_CopyMemory( &DestBufferPtr[*StoredDataSizePtr], &CapturedDataPtr[capturedIndex], didDataSize );

                    *StoredDataSizePtr = *StoredDataSizePtr + (Dem_u32_StoredDataRecordSizeType)didDataSize;                  /*  no wrap around      */

                    numOfStoredDids = numOfStoredDids + (uint8)1U;
                }
                else
                {
                    break;
                }
            }

            capturedIndex = capturedIndex + didDataSize;
        }

        if( didClassRefIndex >= freezeFrameClassPtr->DemDidClassNum )
        {
            retVal = DEM_IRT_OK;
            DestBufferPtr[DEM_STOREDDATA_HEADER_SIZE] = numOfStoredDids;
        }
    }

    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )     */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
