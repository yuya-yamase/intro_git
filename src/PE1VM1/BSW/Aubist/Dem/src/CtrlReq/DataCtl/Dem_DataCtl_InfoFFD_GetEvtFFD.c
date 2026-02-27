/* Dem_DataCtl_InfoFFD_GetEvtFFD_c(v5-9-0)                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_InfoFFD_GetEvtFFD/CODE                        */
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
#include "../../../inc/Dem_CmnLib_DataCtl.h"
#include "../../../inc/Dem_CmnLib_DataCtl_FFDOutputJudge.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "../../../inc/Dem_Utl.h"

#include "Dem_DataCtl_local.h"

#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
#include <Dem_SIT_RangeCheck.h>
#endif /* DEM_SIT_RANGE_CHECK */

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

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetEventFFDataFromTSFF
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u16_DIDNumberType, AUTOMATIC ) DataID,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufSizePtr
);
#endif  /* (DEM_TSFF_PM_SUPPORT == STD_ON) */

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFreezeFrameRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FreezeFrameDataType, AUTOMATIC ) FreezeFrameDataType,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,
    P2VAR( Dem_FreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordPtr
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFFRecordByDidClass
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FreezeFrameDataType, AUTOMATIC ) FreezeFrameDataType,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,      /* MISRA DEVIATION */
    VAR( Dem_u32_DIDClassIndexType, AUTOMATIC ) DidClassIndex,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) DataOffset,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufSizePtr
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetDidClassByDataID
(
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameClassPtr,
    VAR( Dem_u16_DIDNumberType, AUTOMATIC ) DataID,
    P2VAR( Dem_u32_DIDClassIndexType, AUTOMATIC, AUTOMATIC ) DidClassIndexPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) DataOffsetPtr
);

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetTSFFRecordByDidClass
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) TSFFRecClassRefIndex,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) OffsetOfIndex,
    VAR( Dem_u32_DIDClassIndexType, AUTOMATIC ) DidClassIndex,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) DataOffset,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufSizePtr
);
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */

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


/****************************************************************************/
/* Function Name | Dem_Data_GetEventFreezeFrameData                         */
/* Description   | Gets the freeze frame data corresponding to the specifi- */
/*               | ed event index, the record number, data ID.              */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/*               | [in] RecordNumber :                                      */
/*               |        The record number of the freeze frame.            */
/*               | [in] DataID :                                            */
/*               |        The data ID of the freeze frame.                  */
/*               | [out] DestBufferPtr :                                    */
/*               |        The data of the freeze frame record.              */
/*               | [out] BufSizePtr :                                       */
/*               |        The size of the freeze frame record.              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Retrieving the freeze frame data wa- */
/*               |        s successful.                                     */
/*               |        DEM_IRT_NG : Retrieving the freeze frame data wa- */
/*               |        s failed.                                         */
/*               |        DEM_IRT_WRONG_RECORD_NUMBER : The wrong record n- */
/*               |        umber was passed.                                 */
/*               |        DEM_IRT_WRONG_DIDNUMBER : The wrong data ID was - */
/*               |        passed.                                           */
/*               |        DEM_IRT_WRONG_BUFFERSIZE :                        */
/*               |                                                          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetEventFreezeFrameData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u08_FreezeFrameDataType, AUTOMATIC ) FreezeFrameDataType,      /* MISRA DEVIATION */
    VAR( Dem_u16_DIDNumberType, AUTOMATIC ) DataID,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufSizePtr
)
{
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) freezeFrameClassRef;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) freezeframeRecNumClassRef;

    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfFfrClass;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfDidClass;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFFR;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordClassIndex;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) freezeFrameRecordTrigger;
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetTSFF;
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )           */
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) dataOffset;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u32_DIDClassIndexType, AUTOMATIC ) didClassIndex;

    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameClassPtr;
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecNumClassPtr;

    /* Initializes the return value to DEM_IRT_WRONG_RECORDNUMBER. */
    retVal = DEM_IRT_WRONG_RECORDNUMBER;

    eventStorageNum     =   Dem_PrimaryMemEventStorageNum;
    freezeFrameClassRef         =   DEM_FFCLASSINDEX_INVALID;
    freezeframeRecNumClassRef   =   DEM_FFRECNUMCLASSINDEX_INVALID;

    if( EventStrgIndex >= eventStorageNum )                                                                                                             /* [GUD:if]EventStrgIndex */
    {
        /* Sets the return value to NG. */
        retVal = DEM_IRT_NG;
    }
    else
    {
        /* Initialize DemFreezeFrameRecordClass index to 0. */
        freezeFrameRecordClassIndex = 0U;

        /* Initialize FreezeFrameRecordTrigger to NONE. */
        freezeFrameRecordTrigger = DEM_TRIGGER_ON_NONE;

#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
        if ( FreezeFrameDataType == DEM_FFD_TYPE_OBDFFD )
        {
            /*  FreezeFrameDataType == DEM_FFD_TYPE_OBDFFD          */
            /*  Checks the FreezeFrameClass table list Index of the held DTCAttribute table. */
            Dem_CfgInfoPm_GetOBDFreezeFrameAndRecNumClass( EventStrgIndex, &freezeFrameClassRef, &freezeframeRecNumClassRef );                          /* [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] obdFreezeFrameClassRef *//* [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] obdFreezeframeRecNumClassRef */
        }
        else
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )          */
        {
            /* Checks the reference of freeze frame class. */
            Dem_CfgInfoPm_GetFreezeFrameAndRecNumClass( EventStrgIndex, &freezeFrameClassRef, &freezeframeRecNumClassRef );                             /* [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] freezeFrameClassRef *//* [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] freezeframeRecNumClassRef */
        }

        if( freezeFrameClassRef != DEM_FFCLASSINDEX_INVALID )                                                                                           /* [GUD:if]freezeFrameClassRef */
        {
            /* Checks the reference of freeze frame record number class. */
            if( freezeframeRecNumClassRef != DEM_FFRECNUMCLASSINDEX_INVALID )                                                                           /* [GUD:if]freezeframeRecNumClassRef */
            {
                /* Holds the FreezeFrameClass table pointed to by the FreezeFrameClass table list Index of the held DTCAttribute table. */
                freezeFrameClassPtr = &Dem_FreezeFrameClassTable[ freezeFrameClassRef ];                                                                /* [GUD]freezeFrameClassRef */

                /* Holds the FreezeFrameRecNumClass table pointed to by the FreezeFrameRecNumClass table list Index of the held DTCAttribute table. */
                freezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[ freezeframeRecNumClassRef ];                                              /* [GUD]freezeframeRecNumClassRef */

                /* Specify the FreezeFrameRecNumClass table and the specified record number,                 */
                /* the FreezeFrameRecordClass table storage area, and the FreezeFrameRecordClass table index */
                /* Call FreezeFrameRecordClass table acquisition processing.                                 */
                resultOfFfrClass = Dem_Data_GetFreezeFrameRecordClassByRecordNumber( DEM_CALLER_SWC, freezeFrameRecNumClassPtr, RecordNumber, &freezeFrameRecordClassIndex, &freezeFrameRecordTrigger );/* [GUD:RET:DEM_IRT_OK] freezeFrameRecordClassIndex */
                /* Checks FreezeFrameRecordClass table acquisition result. */
                if( resultOfFfrClass == DEM_IRT_OK )
                {
                    /* Initialize DidClass table to NULL. */
                    didClassIndex = (Dem_u32_DIDClassIndexType)0U;

                    /* Initialize the data offset as 0. */
                    dataOffset = 0U;

                    /* Specify the FreezeFrameClass table and the specified DID and         */
                    /* DidClass table storage area and DidClass table index and data offset */
                    /* Call DidClass table acquisition processing.                          */
                    resultOfDidClass = Dem_Data_GetDidClassByDataID( freezeFrameClassPtr, DataID, &didClassIndex, &dataOffset );    /* [GUD]freezeFrameClassPtr *//* [GUD:RET:DEM_IRT_OK :AND: IF_GUARDED: freezeFrameClassPtr] didClassIndex *//* [GUD:RET:DEM_IRT_OK :AND: IF_GUARDED: freezeFrameClassPtr] dataOffset */

                    /* Checks DidClass table acquisition result */
                    if( resultOfDidClass == DEM_IRT_OK )
                    {
                        /* Specify the event index and freezeFrameRecordClassIndex and                  */
                        /* DidClass table storage area and data offset and DestBufferPtr and BufSizePtr */
                        /* Call FFRecordByDidClass table acquisition processing.                        */
                        resultOfGetFFR = Dem_Data_GetFFRecordByDidClass( EventStrgIndex, FreezeFrameDataType, freezeFrameRecordClassIndex, freezeFrameRecordTrigger, didClassIndex, dataOffset, DestBufferPtr, BufSizePtr );    /* [GUD]didClassIndex *//* [GUD]dataOffset */

                        /* Set FreezeFrame record acquisition result as function return value. */
                        retVal = resultOfGetFFR;
                    }
                    else
                    {
                        /* Sets the return value to DidClass table acquisition result. */
                        retVal = DEM_IRT_WRONG_DIDNUMBER;
                    }
                }
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )  /*  [FuncSw]    */
                else if( resultOfFfrClass == DEM_IRT_NG )
                {
                    if ( FreezeFrameDataType == DEM_FFD_TYPE_OBDFFD )
                    {
                        retVal = DEM_IRT_WRONG_RECORDNUMBER;
                    }
                    else
                    {
                        /* As not have been retrieved the freeze frame record class, tries to retrieve time-series freeze frame data. */
                        resultOfGetTSFF = Dem_Data_GetEventFFDataFromTSFF( EventStrgIndex, RecordNumber, DataID, DestBufferPtr, BufSizePtr );

                        /* Sets the result of retrieving time-series freeze frame data as a return value of this function. */
                        retVal = resultOfGetTSFF;
                    }
                }
                else
                {
                    /* No Process */
                }
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )           */
            }
            else
            {
                /* No Process */
            }
        }
        else
        {
            /* No Process */
        }
    }

    /* Returns with the result. */
    return retVal;
}

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_GetEventFFDataFromTSFF                          */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |                                                          */
/*               | [in] RecordNumber :                                      */
/*               |                                                          */
/*               | [in] DataID :                                            */
/*               |                                                          */
/*               | [out] DestBufferPtr :                                    */
/*               |                                                          */
/*               | [in/out] BufSizePtr :                                    */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/*               |        DEM_IRT_NODATAAVAILABLE :                         */
/*               |        DEM_IRT_WRONG_BUFFERSIZE :                        */
/*               |        DEM_IRT_WRONG_DIDNUMBER :                         */
/*               |        DEM_IRT_WRONG_RECORDNUMBER :                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetEventFFDataFromTSFF
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u16_DIDNumberType, AUTOMATIC ) DataID,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufSizePtr
)
{
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameClassPtr;
    VAR( Dem_u32_DIDClassIndexType, AUTOMATIC ) didClassIndex;
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) freezeFrameClassRef;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) dataOffset;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetTSFFInfo;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfDidClass;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsFFRecClassRefIndex;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) startingRecordNumber;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) offsetOfIndex;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) freezeFrameRecordTrigger;
    VAR( boolean, AUTOMATIC ) judgeBeforeTSFFDFlag;

    retVal = DEM_IRT_NG;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]EventStrgIndex */
    {
        startingRecordNumber = (Dem_u08_FFRecordNumberType)0U;
        tsFFRecClassRefIndex = Dem_TSFFRecordClassNumPerDTCMaxNum;
        freezeFrameClassRef = DEM_FFCLASSINDEX_INVALID;
        freezeFrameRecordTrigger = DEM_TRIGGER_ON_NONE;
        judgeBeforeTSFFDFlag = (boolean)FALSE;

        resultOfGetTSFFInfo = Dem_Data_GetTSFFDInfoByEventAndRecNum( EventStrgIndex, RecordNumber, &startingRecordNumber, &tsFFRecClassRefIndex, &freezeFrameClassRef, &freezeFrameRecordTrigger, &judgeBeforeTSFFDFlag );/* [GUD:RET:DEM_IRT_OK] freezeFrameClassRef */

        if( resultOfGetTSFFInfo == DEM_IRT_OK )
        {
            freezeFrameClassPtr = &Dem_FreezeFrameClassTable[freezeFrameClassRef];      /* [GUD]freezeFrameClassRef */

            didClassIndex       = (Dem_u32_DIDClassIndexType)0U;
            dataOffset          = (Dem_u16_FFDStoredIndexType)0U;
            resultOfDidClass    = Dem_Data_GetDidClassByDataID( freezeFrameClassPtr, DataID, &didClassIndex, &dataOffset );

            if( resultOfDidClass == DEM_IRT_OK )
            {
                offsetOfIndex = (Dem_u08_NumOfTSFFType)( RecordNumber - startingRecordNumber );

                retVal = Dem_Data_GetTSFFRecordByDidClass( EventStrgIndex, tsFFRecClassRefIndex, offsetOfIndex, didClassIndex, dataOffset, DestBufferPtr, BufSizePtr );
            }
            else
            {
                retVal = DEM_IRT_WRONG_DIDNUMBER;
            }
        }
        else
        {
            retVal = DEM_IRT_WRONG_RECORDNUMBER;
        }

    }
    else
    {
        /* No process */
    }

    return retVal;
}
#endif  /* (DEM_TSFF_PM_SUPPORT == STD_ON) */


/****************************************************************************/
/* Function Name | Dem_Data_GetFFRecordByDidClass                           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |                                                          */
/*               | [in] FreezeFrameRecordClassIndex :                       */
/*               |                                                          */
/*               | [in] DidClassIndex :                                     */
/*               |                                                          */
/*               | [in] DataOffset :                                        */
/*               |                                                          */
/*               | [out] DestBufferPtr :                                    */
/*               |                                                          */
/*               | [out] BufSizePtr :                                       */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NODATAAVAILABLE :                         */
/*               |        DEM_IRT_WRONG_BUFFERSIZE :                        */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-6-0      | no branch changed.                                       */
/*   v5-7-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFFRecordByDidClass
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FreezeFrameDataType, AUTOMATIC ) FreezeFrameDataType,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,      /* MISRA DEVIATION */
    VAR( Dem_u32_DIDClassIndexType, AUTOMATIC ) DidClassIndex,                  /* [PRMCHK:CALLER] */
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) DataOffset,                    /* [PRMCHK:CALLER] */
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufSizePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFFRec;
    VAR( boolean, AUTOMATIC ) ffdOutputAllow;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
    VAR( boolean, AUTOMATIC ) judgeOutputOBDFFDTrigger;
#endif  /*  ( DEM_OBDFFD_SUPPORT == STD_ON )    */
    VAR( Dem_u32_FFDStoredIndexType, AUTOMATIC ) dataOffset;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) didDataSize;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
#endif  /*  ( DEM_OBDFFD_SUPPORT == STD_ON )    */

    VAR( Dem_FreezeFrameRecordMngType, AUTOMATIC ) freezeFrameRecord;

    retVal = DEM_IRT_NODATAAVAILABLE;

    didDataSize =   Dem_DIDClassTable[DidClassIndex].DemDidDataSize;                    /* [GUDCHK:CALLER]DidClassIndex */
    if( didDataSize <= *BufSizePtr )
    {
        resultOfGetFFRec = Dem_Data_GetFreezeFrameRecord( EventStrgIndex, FreezeFrameDataType, FreezeFrameRecordClassIndex, &freezeFrameRecord );

        if( resultOfGetFFRec == DEM_IRT_OK )
        {
            if( freezeFrameRecord.RecordStatus == DEM_FFD_STORED )
            {
                dataOffset = (Dem_u32_FFDStoredIndexType)DataOffset;                                                                                                /* [GUDCHK:CALLER]DataOffset */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
                if( FreezeFrameDataType == DEM_FFD_TYPE_OBDFFD )
                {
                    ffdOutputAllow = Dem_Data_GetFFDOutputAllow( DidClassIndex, freezeFrameRecord.DataPtr[dataOffset], &dataOffset );       /* [GUDCHK:CALLER]DataOffset *//* [ARYCHK] DEM_SIT_R_CHK_OBD_FF_DATA_SIZE / 1 / dataOffset */
                    if( ffdOutputAllow == (boolean)TRUE )
                    {
                        /*  get status of DTC at DisableRecordUpdate.       */
                        statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
                        (void)Dem_DataMngC_GetER_StatusOfDTC( EventStrgIndex, &statusOfDTC );   /* no return check required */

                        /* Checks condition that can be output OBDFFD of specified trigger. */
                        judgeOutputOBDFFDTrigger = Dem_Data_JudgeOutputOBDFFDTrigger( statusOfDTC, FreezeFrameRecordTrigger );
                        if( judgeOutputOBDFFDTrigger == (boolean)TRUE )
                        {
                            Dem_UtlMem_CopyMemory( DestBufferPtr, &freezeFrameRecord.DataPtr[dataOffset], didDataSize );                /* [GUDCHK:CALLER]DataOffset *//* [ARYCHK] DEM_SIT_R_CHK_OBD_FF_DATA_SIZE / 1 / dataOffset */
                            *BufSizePtr = didDataSize;

                            retVal = DEM_IRT_OK;
                        }
                    }
                }
                else
#endif  /*  ( DEM_OBDFFD_SUPPORT == STD_ON )    */
                {
                    ffdOutputAllow = Dem_Data_GetFFDOutputAllow( DidClassIndex, freezeFrameRecord.DataPtr[dataOffset], &dataOffset );       /* [GUDCHK:CALLER]DataOffset *//* [ARYCHK] DEM_SIT_R_CHK_NONOBD_FF_DATA_SIZE / 1 / dataOffset */
                    if( ffdOutputAllow == (boolean)TRUE )
                    {
                        Dem_UtlMem_CopyMemory( DestBufferPtr, &freezeFrameRecord.DataPtr[dataOffset], didDataSize );                    /* [GUDCHK:CALLER]DataOffset *//* [ARYCHK] DEM_SIT_R_CHK_NONOBD_FF_DATA_SIZE / 1 / dataOffset */
                        *BufSizePtr = didDataSize;

                        retVal = DEM_IRT_OK;
                    }
                }
            }
        }
    }
    else
    {
        retVal = DEM_IRT_WRONG_BUFFERSIZE;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Data_GetFreezeFrameRecord                            */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |                                                          */
/*               | [in] FreezeFrameRecordClassIndex :                       */
/*               |                                                          */
/*               | [out] FreezeFrameRecordPtr :                             */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFreezeFrameRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FreezeFrameDataType, AUTOMATIC ) FreezeFrameDataType,      /* MISRA DEVIATION */
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,
    P2VAR( Dem_FreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFFLIndexAndRecNumIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFFRec;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) recordNumberIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) ffrClassPerDTCMaxNum;

    retVal = DEM_IRT_OK;
    resultOfGetFFLIndexAndRecNumIndex = DEM_IRT_NG;

#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
    if ( FreezeFrameDataType == DEM_FFD_TYPE_OBDFFD )
    {
        ffrClassPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();
    }
    else
#endif  /*  ( DEM_OBDFFD_SUPPORT == STD_ON )           */
    {
        ffrClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;
    }

    if( FreezeFrameRecordClassIndex >= ffrClassPerDTCMaxNum )
    {
        retVal = DEM_IRT_NG;
    }
    else
    {
        SchM_Enter_Dem_EventMemory();

        faultIndex = DEM_FAULTINDEX_INITIAL;
        resultOfGetFaultIndex = Dem_DataMngC_GetER_FaultIndex( EventStrgIndex, &faultIndex );       /* [GUD:RET:DEM_IRT_OK] EventStrgIndex */

        if( resultOfGetFaultIndex == DEM_IRT_OK )
        {
#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
            if ( FreezeFrameDataType == DEM_FFD_TYPE_OBDFFD )
            {
                resultOfGetFFLIndexAndRecNumIndex = Dem_DataMngC_GetFR_ObdFreezeFrameIndex( faultIndex, FreezeFrameRecordClassIndex, &recordNumberIndex );
            }
            else
#endif  /*  ( DEM_OBDFFD_SUPPORT == STD_ON )           */
            {
                resultOfGetFFLIndexAndRecNumIndex = Dem_DataMngC_GetFR_FreezeFrameIndex( faultIndex, FreezeFrameRecordClassIndex, &recordNumberIndex );
            }
        }
        else
        {
            /* No Process */
        }
        if( resultOfGetFFLIndexAndRecNumIndex == DEM_IRT_OK )
        {
            if( recordNumberIndex != DEM_FFRECINDEX_INITIAL )
            {
#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
                if ( FreezeFrameDataType == DEM_FFD_TYPE_OBDFFD )
                {
                    resultOfGetFFRec = Dem_DataMngC_GetObdFreezeFrameRecord( recordNumberIndex, FreezeFrameRecordPtr );
                }
                else
#endif  /*  ( DEM_OBDFFD_SUPPORT == STD_ON )           */
                {
                    resultOfGetFFRec = Dem_DataMngC_GetFreezeFrameRecord( recordNumberIndex, FreezeFrameRecordPtr );
                }

                if( resultOfGetFFRec != DEM_IRT_OK )
                {
                    retVal = DEM_IRT_NG;
                }
                else
                {
                    /* No Process */
                }
            }
            else
            {
                retVal = DEM_IRT_NG;
            }
        }
        else
        {
            retVal = DEM_IRT_NG;
        }

        SchM_Exit_Dem_EventMemory();
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Data_GetDidClassByDataID                             */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameClassPtr :                               */
/*               |                                                          */
/*               | [in] DataID :                                            */
/*               |                                                          */
/*               | [out] DidClassIndexPtr :                                 */
/*               |                                                          */
/*               | [out] DataOffsetPtr :                                    */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK :AND: IF_GUARDED: FreezeFrameClassPtr ] DidClassIndexPtr */
/* VariableGuard | [GUD:RET:DEM_IRT_OK :AND: IF_GUARDED: FreezeFrameClassPtr ] DataOffsetPtr    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetDidClassByDataID
(
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameClassPtr,       /* [PRMCHK:CALLER] */
    VAR( Dem_u16_DIDNumberType, AUTOMATIC ) DataID,
    P2VAR( Dem_u32_DIDClassIndexType, AUTOMATIC, AUTOMATIC ) DidClassIndexPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) DataOffsetPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_DIDClassPerFFIndexType, AUTOMATIC ) didClassRefIndex;

    VAR( Dem_u32_DIDClassIndexType, AUTOMATIC ) didClassIndex;
    VAR( Dem_u32_FFDStoredIndexType, AUTOMATIC ) addedValue;
    VAR( Dem_u16_DIDNumberType, AUTOMATIC ) didIdentifier;
    VAR( boolean, AUTOMATIC ) loopEnd;

    retVal = DEM_IRT_NG;

    addedValue = (Dem_u16_FFDStoredIndexType)0U;
    loopEnd =   (boolean)FALSE;

    for( didClassRefIndex = (Dem_u16_DIDClassPerFFIndexType)0U; didClassRefIndex < FreezeFrameClassPtr->DemDidClassNum; didClassRefIndex++ )    /* [GUD:for]didClassRefIndex */
    {
        didClassIndex = FreezeFrameClassPtr->DemDidClassRef[didClassRefIndex];      /* [GUDCHK:CALLER]FreezeFrameClassPtr *//* [GUD]didClassRefIndex *//* [ARYCHK] DEM_DID_NUM_PER_FRAME_MAX_NUM / 1 / didClassRefIndex */

        didIdentifier = Dem_DIDClassTable[didClassIndex].DemDidIdentifier;          /* [GUDCHK:CALLER]FreezeFrameClassPtr */

        if( didIdentifier == DataID )
        {
            *DidClassIndexPtr   =   didClassIndex;                                  /* [GUDCHK:CALLER]FreezeFrameClassPtr */
            *DataOffsetPtr      =   (Dem_u16_FFDStoredIndexType)addedValue;         /* [GUDCHK:CALLER]FreezeFrameClassPtr */

            retVal = DEM_IRT_OK;
            loopEnd = (boolean)TRUE;
        }
        else
        {
            addedValue = addedValue + (Dem_u32_FFDStoredIndexType)Dem_DIDClassTable[didClassIndex].DemDidDataSize;      /* [GUDCHK:CALLER]FreezeFrameClassPtr *//*  no wrap around      */

#if ( DEM_FFD_OUTPUT_JUDGE_SUPPORT == STD_ON )  /*  [FuncSw]    */
            Dem_Data_AddFFDOutputJudgeSize( didClassIndex, &addedValue );
#endif  /* ( DEM_FFD_OUTPUT_JUDGE_SUPPORT == STD_ON )           */
        }

        if ( loopEnd == (boolean)TRUE )
        {
            break;
        }
    }

    return retVal;
}

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_GetTSFFRecordByDidClass                         */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |                                                          */
/*               | [in] TSFFRecClassRefIndex :                              */
/*               |                                                          */
/*               | [in] OffsetOfIndex :                                     */
/*               |                                                          */
/*               | [in] DidClassIndex :                                     */
/*               |                                                          */
/*               | [in] DataOffset :                                        */
/*               |                                                          */
/*               | [out] DestBufferPtr :                                    */
/*               |                                                          */
/*               | [in/out] BufSizePtr :                                    */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NODATAAVAILABLE :                         */
/*               |        DEM_IRT_WRONG_BUFFERSIZE :                        */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetTSFFRecordByDidClass
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) TSFFRecClassRefIndex,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) OffsetOfIndex,
    VAR( Dem_u32_DIDClassIndexType, AUTOMATIC ) DidClassIndex,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) DataOffset,        /* [PRMCHK:CALLER] */
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufSizePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetTSFFRec;
    VAR( boolean, AUTOMATIC ) ffdOutputAllow;
    VAR( Dem_u32_FFDStoredIndexType, AUTOMATIC ) dataOffset;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) didDataSize;

    VAR( Dem_FreezeFrameRecordMngType, AUTOMATIC ) tsFFRecord;

    retVal = DEM_IRT_NODATAAVAILABLE;
    didDataSize =   Dem_DIDClassTable[DidClassIndex].DemDidDataSize;    /* [GUDCHK:CALLER]DidClassIndex */

    if( didDataSize <= *BufSizePtr )
    {
        resultOfGetTSFFRec = Dem_Data_GetTSFFRecord( EventStrgIndex, TSFFRecClassRefIndex, OffsetOfIndex, &tsFFRecord );

        if( resultOfGetTSFFRec == DEM_IRT_OK )
        {
            if( tsFFRecord.RecordStatus == DEM_FFD_STORED )
            {
                dataOffset = (Dem_u32_FFDStoredIndexType)DataOffset;                                                                /* [GUDCHK:CALLER]DataOffset */

                ffdOutputAllow = Dem_Data_GetFFDOutputAllow( DidClassIndex, tsFFRecord.DataPtr[dataOffset], &dataOffset );          /* [GUDCHK:CALLER]DataOffset *//* [ARYCHK] DEM_SIT_R_CHK_TS_FF_DATA_SIZE / 1 / dataOffset */
                if( ffdOutputAllow == (boolean)TRUE )
                {
                    Dem_UtlMem_CopyMemory( DestBufferPtr, &tsFFRecord.DataPtr[dataOffset], didDataSize );                           /* [GUDCHK:CALLER]DataOffset *//* [ARYCHK] DEM_SIT_R_CHK_TS_FF_DATA_SIZE / 1 / dataOffset */

                    *BufSizePtr = didDataSize;

                    retVal = DEM_IRT_OK;
                }
            }
        }
    }
    else
    {
        retVal = DEM_IRT_WRONG_BUFFERSIZE;
    }

    return retVal;
}
#endif  /* (DEM_TSFF_PM_SUPPORT == STD_ON) */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
