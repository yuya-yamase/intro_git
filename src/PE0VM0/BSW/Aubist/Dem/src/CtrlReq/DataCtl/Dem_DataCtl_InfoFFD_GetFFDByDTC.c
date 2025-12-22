/* Dem_DataCtl_InfoFFD_c(v5-9-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_InfoFFD/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_DataCtl_FFDOutputJudge.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_DataCtl.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DataCtl_OBD.h"

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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_JudgeOutputFFD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_FreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordPtr,
    VAR( Dem_u08_FreezeFrameDataType, AUTOMATIC ) FreezeFrameDataType,
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameRecordIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger
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


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_GetObdFreezeFrameData                           */
/* Description   | Gets the freeze frame data corresponding to the specifi- */
/*               | ed freeze frame record index.                            */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific DT- */
/*               |        C value.                                          */
/*               | [in] RecordNumber :                                      */
/*               |        The record number corresponding to the specified  */
/*               |         event index.                                     */
/*               | [out] DataPtr :                                          */
/*               |        The area where freeze frame data will be stored.  */
/*               | [in/out] DataSizePtr :                                   */
/*               |        The size of freeze frame data.                    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Retrieving the freeze frame data wa- */
/*               |        s successful.                                     */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : Checking the record- */
/*               |         number was failed.                               */
/*               |        DEM_IRT_NG : Retrieving the freeze frame data wa- */
/*               |        s failed.                                         */
/*               |        DEM_IRT_WRONG_BUFFERSIZE                          */
/*               |                                                          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetObdFreezeFrameData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u08_FFDGetInfoType, AUTOMATIC ) FreezeFrameGetInfoType,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DataPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) DataSizePtr
)
{
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) freezeFrameClassRef;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) freezeframeRecNumClassRef;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFFRClass;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFFRec;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfJudgeOutputFFD;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfEditFFRec;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordClassIndex;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) freezeFrameRecordTrigger;
    VAR( boolean, AUTOMATIC ) judgeOutputOBDFFDTrigger;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;

    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) freezeFrameRecordIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    VAR( Dem_FreezeFrameRecordMngType, AUTOMATIC ) freezeFrameRecord;

    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecNumClassPtr;
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameClassPtr;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    retVal = DEM_IRT_NG;

    if( EventStrgIndex < eventStorageNum )                                                                                      /* [GUD:if]EventStrgIndex */
    {
        /* Checks the FreezeFrameClass table list Index of the held DTCAttribute table. */
        Dem_CfgInfoPm_GetOBDFreezeFrameAndRecNumClass( EventStrgIndex, &freezeFrameClassRef, &freezeframeRecNumClassRef );      /* [GUD]EventStrgIndex *//* [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] obdFreezeFrameClassRef *//* [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] obdFreezeframeRecNumClassRef */
        if( freezeFrameClassRef == DEM_FFCLASSINDEX_INVALID )                                                                   /* [GUD:if]freezeFrameClassRef */
        {
            /* Sets the return value to DEM_IRT_WRONG_RECORDNUMBER(Incorrect record number). */
            retVal = DEM_IRT_WRONG_RECORDNUMBER;
        }
        /* Checks the FreezeFrameRecNumClass table list Index of the held DTCAttribute table. */
        else if( freezeframeRecNumClassRef == DEM_FFRECNUMCLASSINDEX_INVALID )                                                  /* [GUD:if]freezeframeRecNumClassRef */
        {
            /* Sets the return value to DEM_IRT_WRONG_RECORDNUMBER(Incorrect record number). */
            retVal = DEM_IRT_WRONG_RECORDNUMBER;
        }
        else
        {
            /* Holds the FreezeFrameClass table pointed to by the FreezeFrameClass table list Index of the held DTCAttribute table. */
            freezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[freezeframeRecNumClassRef];                            /* [GUD]freezeframeRecNumClassRef */

            freezeFrameRecordClassIndex = 0U;
            freezeFrameRecordTrigger = DEM_TRIGGER_ON_NONE;

            /* Specify the FreezeFrameRecNumClass table and the specified record number,                 */
            /* the FreezeFrameRecordClass table storage area, and the FreezeFrameRecordClass table index */
            /* Call FreezeFrameRecordClass table acquisition processing.                                 */
            resultOfGetFFRClass = Dem_Data_GetFreezeFrameRecordClassByRecordNumber( DEM_CALLER_DCM, freezeFrameRecNumClassPtr, RecordNumber, &freezeFrameRecordClassIndex, &freezeFrameRecordTrigger ); /* [GUD:RET:DEM_IRT_OK] freezeFrameRecordClassIndex */
            /* Checks FreezeFrameRecordClass table acquisition result. */
            if( resultOfGetFFRClass != DEM_IRT_OK )
            {
                retVal  =   DEM_IRT_WRONG_RECORDNUMBER;
            }
            else
            {
                freezeFrameRecordIndex = Dem_Data_GetTmpDisabledRecordObdFFRIndex( EventStrgIndex, freezeFrameRecordClassIndex );   /* [GUD]EventStrgIndex *//*  [GUD]freezeFrameRecordClassIndex    */
                if( freezeFrameRecordIndex == DEM_FFRECINDEX_INITIAL )
                {
                    /* That is the specified record number is not occurred fault. */

                    /* Stores 0 to the specified the size of freeze frame data. */
                    *DataSizePtr = 0U;

                    /* Sets the return value to OK. */
                    retVal = DEM_IRT_OK;
                }
                else
                {
                    /*  get status of DTC at DisableRecordUpdate.       */
                    statusOfDTC =   Dem_Data_GetDTCStatusOfDisabledRecord();

                    /* Checks condition that can be output OBDFFD of specified trigger. */
                    judgeOutputOBDFFDTrigger = Dem_Data_JudgeOutputOBDFFDTrigger( statusOfDTC, freezeFrameRecordTrigger );
                    if( judgeOutputOBDFFDTrigger == (boolean)TRUE )
                    {
                        /* Get FreezeFrame record by The FreezeFrameRecordIndex (RecordNumberIndex) held and */
                        /* the FreezeFrame record storage area specified. */
                        resultOfGetFFRec = Dem_DataMngC_GetObdFreezeFrameRecord( freezeFrameRecordIndex, &freezeFrameRecord );
                        /* By excluding the above process, this read process does not interrupt while updating EventMemory by Main Task */
                        /* Therefore do not use exclusion */

                        /* Checks FreezeFrame record acquisition result. */
                        if( resultOfGetFFRec == DEM_IRT_OK )
                        {
                            resultOfJudgeOutputFFD = Dem_Data_JudgeOutputFFD( EventStrgIndex, &freezeFrameRecord, DEM_FFD_TYPE_OBDFFD, freezeFrameRecordIndex, DEM_TRIGGER_ON_NONE );   /* [GUD]EventStrgIndex */
                            if( resultOfJudgeOutputFFD == DEM_IRT_OK )
                            {
                                /* Holds the FreezeFrameClass table pointed to by the FreezeFrameClass table list Index of the held DTCAttribute table. */
                                freezeFrameClassPtr = &Dem_FreezeFrameClassTable[ freezeFrameClassRef ];                                                                                /* [GUD]freezeFrameClassRef */

                                /* Edit FreezeFrame record to the specified format. [SWS_Dem_00071]Figure 7.51 */
#ifndef DEM_SIT_RANGE_CHECK
                                resultOfEditFFRec = Dem_Data_EditFreezeFrameRecord( RecordNumber, FreezeFrameGetInfoType, freezeFrameRecord.DataPtr, freezeFrameClassPtr, DataPtr, DataSizePtr);
#else   /* DEM_SIT_RANGE_CHECK */
                                resultOfEditFFRec = Dem_Data_EditFreezeFrameRecord( DEM_SIT_R_CHK_OBD_FF_DATA_SIZE, RecordNumber, FreezeFrameGetInfoType, freezeFrameRecord.DataPtr, freezeFrameClassPtr, DataPtr, DataSizePtr);
#endif  /* DEM_SIT_RANGE_CHECK */
                                /* Sets the return value to FreezeFrame record edit result. */
                                retVal = resultOfEditFFRec;
                            }
                            else
                            {
                                /* Stores 0 to the specified the size of freeze frame data. */
                                *DataSizePtr = 0U;

                                /* Sets the return value to OK. */
                                retVal = DEM_IRT_OK;
                            }
                        }
                        else
                        {
                            /* Sets the return value to NG. */
                            retVal = DEM_IRT_NG;
                        }
                    }
                    else
                    {
                        /* Stores 0 to the specified the size of freeze frame data. */
                        *DataSizePtr = 0U;

                        /* Sets the return value to OK. */
                        retVal = DEM_IRT_OK;
                    }
                }
            }
        }
    }

    /* Returns with the result. */
    return retVal;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_Data_GetFreezeFrameData                              */
/* Description   | Gets the freeze frame data corresponding to the specifi- */
/*               | ed freeze frame record index.                            */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific DT- */
/*               |        C value.                                          */
/*               | [in] RecordNumber :                                      */
/*               |        The record number corresponding to the specified  */
/*               |         event index.                                     */
/*               | [out] DataPtr :                                          */
/*               |        The area where freeze frame data will be stored.  */
/*               | [in/out] DataSizePtr :                                   */
/*               |        The size of freeze frame data.                    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Retrieving the freeze frame data wa- */
/*               |        s successful.                                     */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : Checking the record- */
/*               |         number was failed.                               */
/*               |        DEM_IRT_NG : Retrieving the freeze frame data wa- */
/*               |        s failed.                                         */
/*               |        DEM_IRT_WRONG_BUFFERSIZE                          */
/*               |                                                          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFreezeFrameData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u08_FFDGetInfoType, AUTOMATIC ) FreezeFrameGetInfoType,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DataPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) DataSizePtr
)
{
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) freezeFrameClassRef;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) freezeframeRecNumClassRef;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFFRClass;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFFRec;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfJudgeOutputFFD;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfEditFFRec;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordClassIndex;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) freezeFrameRecordTrigger;
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetTSSFFData;
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )           */

    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) freezeFrameRecordIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    VAR( Dem_FreezeFrameRecordMngType, AUTOMATIC ) freezeFrameRecord;

    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecNumClassPtr;
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameClassPtr;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    retVal = DEM_IRT_NG;

    if( EventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]EventStrgIndex */
    {
        /* Checks the FreezeFrameClass table list Index of the held DTCAttribute table. */
        Dem_CfgInfoPm_GetFreezeFrameAndRecNumClass( EventStrgIndex, &freezeFrameClassRef, &freezeframeRecNumClassRef ); /* [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] freezeFrameClassRef *//* [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] freezeframeRecNumClassRef */

        if( freezeFrameClassRef == DEM_FFCLASSINDEX_INVALID )                                                           /* [GUD:if] freezeFrameClassRef */
        {
            /* Sets the return value to DEM_IRT_WRONG_RECORDNUMBER(Incorrect record number). */
            retVal = DEM_IRT_WRONG_RECORDNUMBER;
        }
        /* Checks the FreezeFrameRecNumClass table list Index of the held DTCAttribute table. */
        else if( freezeframeRecNumClassRef == DEM_FFRECNUMCLASSINDEX_INVALID )                                          /* [GUD:if] freezeframeRecNumClassRef */
        {
            /* Sets the return value to DEM_IRT_WRONG_RECORDNUMBER(Incorrect record number). */
            retVal = DEM_IRT_WRONG_RECORDNUMBER;
        }
        else
        {
            /* Holds the FreezeFrameClass table pointed to by the FreezeFrameClass table list Index of the held DTCAttribute table. */
            freezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[freezeframeRecNumClassRef];                    /* [GUD] freezeframeRecNumClassRef */

            freezeFrameRecordClassIndex = 0U;
            freezeFrameRecordTrigger = DEM_TRIGGER_ON_NONE;

            /* Specify the FreezeFrameRecNumClass table and the specified record number,                 */
            /* the FreezeFrameRecordClass table storage area, and the FreezeFrameRecordClass table index */
            /* Call FreezeFrameRecordClass table acquisition processing.                                 */
            resultOfGetFFRClass = Dem_Data_GetFreezeFrameRecordClassByRecordNumber( DEM_CALLER_DCM, freezeFrameRecNumClassPtr, RecordNumber, &freezeFrameRecordClassIndex, &freezeFrameRecordTrigger );     /* [GUD:RET:DEM_IRT_OK] freezeFrameRecordClassIndex */
            /* Checks FreezeFrameRecordClass table acquisition result. */
            if( resultOfGetFFRClass != DEM_IRT_OK )
            {
                retVal  =   DEM_IRT_WRONG_RECORDNUMBER;

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )  /*  [FuncSw]    */
                /* As not have been retrieved the freeze frame record class, tries to retrieve time-series freeze frame data. */
                resultOfGetTSSFFData = Dem_Data_GetFFDataFromTSFF( EventStrgIndex, RecordNumber, FreezeFrameGetInfoType, DataPtr, DataSizePtr );    /* [GUD]EventStrgIndex */

                if( resultOfGetTSSFFData != DEM_IRT_WRONG_RECORDNUMBER )
                {
                    /* Sets the return value to DEM_IRT_WRONG_RECORDNUMBER(Incorrect record number). */
                    retVal = resultOfGetTSSFFData;
                }
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )           */
            }
            else
            {
                freezeFrameRecordIndex = Dem_Data_GetTmpDisabledRecordFFRIndex( EventStrgIndex, freezeFrameRecordClassIndex );  /* [GUD]EventStrgIndex *//* [GUD]freezeFrameRecordClassIndex */
                if( freezeFrameRecordIndex == DEM_FFRECINDEX_INITIAL )
                {
                    /* That is the specified record number is not occurred fault. */

                    /* Stores 0 to the specified the size of freeze frame data. */
                    *DataSizePtr = 0U;

                    /* Sets the return value to OK. */
                    retVal = DEM_IRT_OK;
                }
                else
                {
                    /* Get FreezeFrame record by The FreezeFrameRecordIndex (RecordNumberIndex) held and */
                    /* the FreezeFrame record storage area specified. */
                    resultOfGetFFRec = Dem_DataMngC_GetFreezeFrameRecord( freezeFrameRecordIndex, &freezeFrameRecord );
                    /* By excluding the above process, this read process does not interrupt while updating EventMemory by Main Task */
                    /* Therefore do not use exclusion */

                    /* Checks FreezeFrame record acquisition result. */
                    if( resultOfGetFFRec == DEM_IRT_OK )
                    {
                        resultOfJudgeOutputFFD = Dem_Data_JudgeOutputFFD( EventStrgIndex, &freezeFrameRecord, DEM_FFD_TYPE_NONOBDFFD, freezeFrameRecordIndex, DEM_TRIGGER_ON_NONE );        /* [GUD]EventStrgIndex */
                        if( resultOfJudgeOutputFFD == DEM_IRT_OK )
                        {
                            /* Holds the FreezeFrameClass table pointed to by the FreezeFrameClass table list Index of the held DTCAttribute table. */
                            freezeFrameClassPtr = &Dem_FreezeFrameClassTable[ freezeFrameClassRef ];                            /* [GUD] freezeFrameClassRef */

                            /* Edit FreezeFrame record to the specified format. [SWS_Dem_00071]Figure 7.51 */
#ifndef DEM_SIT_RANGE_CHECK
                            resultOfEditFFRec = Dem_Data_EditFreezeFrameRecord( RecordNumber, FreezeFrameGetInfoType, freezeFrameRecord.DataPtr, freezeFrameClassPtr, DataPtr, DataSizePtr);
#else   /* DEM_SIT_RANGE_CHECK */
                            resultOfEditFFRec = Dem_Data_EditFreezeFrameRecord( DEM_SIT_R_CHK_NONOBD_FF_DATA_SIZE, RecordNumber, FreezeFrameGetInfoType, freezeFrameRecord.DataPtr, freezeFrameClassPtr, DataPtr, DataSizePtr);
#endif  /* DEM_SIT_RANGE_CHECK */
                            /* Sets the return value to FreezeFrame record edit result. */
                            retVal = resultOfEditFFRec;
                        }
                        else
                        {
                            /* Stores 0 to the specified the size of freeze frame data. */
                            *DataSizePtr = 0U;

                            /* Sets the return value to OK. */
                            retVal = DEM_IRT_OK;
                        }
                    }
                    else
                    {
                        /* Sets the return value to NG. */
                        retVal = DEM_IRT_NG;
                    }

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )  /*  [FuncSw]    */
                    if( (retVal != DEM_IRT_OK) || (*DataSizePtr == (Dem_u16_FFDStoredIndexType)0U) )
                    {
                        if( FreezeFrameGetInfoType == DEM_FFDGETTYPE_DATA )
                        {
                            /* If freeze frame record cannot be output */
                            Dem_Data_StopOutputTSFFDAfterTriggerFFD( freezeFrameRecordIndex );
                        }
                    }
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )           */
                }
            }
        }
    }

    /* Returns with the result. */
    return retVal;
}


#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_GetFFDataFromTSFF                               */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |                                                          */
/*               | [in] RecordNumber :                                      */
/*               |                                                          */
/*               | [in] OutputResult :                                      */
/*               |                                                          */
/*               | [out] DataPtr :                                          */
/*               |                                                          */
/*               | [in/out] DataSizePtr :                                   */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/*               |        DEM_IRT_WRONG_RECORDNUMBER :                      */
/*               |        DEM_IRT_WRONG_BUFFERSIZE :                        */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFFDataFromTSFF
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u08_FFDGetInfoType, AUTOMATIC ) FreezeFrameGetInfoType,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DataPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) DataSizePtr
)
{
    VAR( Dem_FreezeFrameRecordMngType, AUTOMATIC ) tsFFRecord;
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameClassPtr;
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) freezeFrameClassRef;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetTSFFInfo;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetTSFFRec;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfJudgeOutputFFD;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfEditFFRec;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsFFRecClassRefIndex;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) startingRecordNumber;
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

        resultOfGetTSFFInfo = Dem_Data_GetTSFFDInfoByEventAndRecNum( EventStrgIndex, RecordNumber, &startingRecordNumber, &tsFFRecClassRefIndex, &freezeFrameClassRef, &freezeFrameRecordTrigger, &judgeBeforeTSFFDFlag );  /* [GUD]EventStrgIndex *//* [GUD:RET:DEM_IRT_OK] freezeFrameClassRef */

        if( resultOfGetTSFFInfo == DEM_IRT_OK )
        {
            if( FreezeFrameGetInfoType == DEM_FFDGETTYPE_DATA )
            {
                Dem_Data_StartOutputTSFFDAfterTSFFD( freezeFrameRecordTrigger, startingRecordNumber );
            }

            resultOfGetTSFFRec = Dem_Data_GetTSFFRecord( EventStrgIndex, tsFFRecClassRefIndex, ( RecordNumber - startingRecordNumber ), &tsFFRecord );  /* [GUD]EventStrgIndex */
            if( resultOfGetTSFFRec == DEM_IRT_OK )
            {
                resultOfJudgeOutputFFD = Dem_Data_JudgeOutputFFD( EventStrgIndex, &tsFFRecord, DEM_FFD_TYPE_TSFFD, DEM_FFRECINDEX_INITIAL, freezeFrameRecordTrigger );  /* [GUD]EventStrgIndex */
                if( resultOfJudgeOutputFFD == DEM_IRT_OK )
                {
                    freezeFrameClassPtr = &Dem_FreezeFrameClassTable[freezeFrameClassRef];                                                                              /* [GUD]freezeFrameClassRef */

#ifndef DEM_SIT_RANGE_CHECK
                    resultOfEditFFRec = Dem_Data_EditFreezeFrameRecord( RecordNumber, FreezeFrameGetInfoType, tsFFRecord.DataPtr, freezeFrameClassPtr, DataPtr, DataSizePtr );
#else   /* DEM_SIT_RANGE_CHECK */
                    resultOfEditFFRec = Dem_Data_EditFreezeFrameRecord( DEM_SIT_R_CHK_TS_FF_DATA_SIZE, RecordNumber, FreezeFrameGetInfoType, tsFFRecord.DataPtr, freezeFrameClassPtr, DataPtr, DataSizePtr );
#endif  /* DEM_SIT_RANGE_CHECK */

                    retVal = resultOfEditFFRec;
                }
                else
                {
                    retVal = DEM_IRT_OK;
                    *DataSizePtr = (Dem_u16_FFDStoredIndexType)0U;
                }
            }
            else
            {
                retVal = DEM_IRT_OK;
                *DataSizePtr = (Dem_u16_FFDStoredIndexType)0U;
            }

            if( FreezeFrameGetInfoType == DEM_FFDGETTYPE_DATA )
            {
                if( (retVal == DEM_IRT_OK) && (*DataSizePtr > (Dem_u16_FFDStoredIndexType)0U) )
                {
                    /* If TSFFD can be output */
                    Dem_Data_SetAlreadyOutputBeforeTSFFDStatus( freezeFrameRecordTrigger, judgeBeforeTSFFDFlag );
                }
                else
                {
                    /* If TSFFD cannot be output */
                    Dem_Data_StopOutputTSFFDAfterTSFFD( freezeFrameRecordTrigger, judgeBeforeTSFFDFlag );
                }
            }
        }
        else
        {
            retVal = DEM_IRT_WRONG_RECORDNUMBER;
        }
    }

    return retVal;
}
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_Data_JudgeOutputFFD                                  */
/* Description   | Judge whether to output FFD                              */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex : Index of events that stored FFD.   */
/*               | [in] FreezeFrameRecordPtr : The pointer of the freeze f- */
/*               | rame record from DataMng                                 */
/*               | [in] FreezeFrameDataType : Type of freeze frame record   */
/*               | [in] FreezeFrameRecordIndex : The freeze frame index co- */
/*               | rresponding to the specific freeze frame record.         */
/*               | [in] FreezeFrameRecordTrigger : TSFFD Stored Trigger     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : FFD can be output                    */
/*               |        DEM_IRT_NG : FFD cannot be output                 */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-9-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_JudgeOutputFFD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_FreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordPtr,
    VAR( Dem_u08_FreezeFrameDataType, AUTOMATIC ) FreezeFrameDataType,
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameRecordIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfCheckTmpCheckRecordData;

#if ( DEM_OBDONUDS_SUPPORT == STD_ON )              /*  [FuncSw]    */
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( boolean, AUTOMATIC ) misfireEventKindOfFFR;
#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )    */
#endif /* ( DEM_OBDONUDS_SUPPORT == STD_ON )                */

    retVal = DEM_IRT_OK;

    if( FreezeFrameRecordPtr->RecordStatus != DEM_FFD_STORED )
    {
        retVal = DEM_IRT_NG;
    }

#if ( DEM_OBDONUDS_SUPPORT == STD_ON )              /*  [FuncSw]    */
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );
    if( ( misfireEventKind == (boolean)TRUE ) && ( FreezeFrameDataType == DEM_FFD_TYPE_OBDFFD ) )
    {
        misfireEventKindOfFFR = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( FreezeFrameRecordPtr->EventStrgIndex );
        if( misfireEventKindOfFFR != (boolean)TRUE )
        {
            retVal = DEM_IRT_NG;
        }
    }
    else
#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )    */
#endif /* ( DEM_OBDONUDS_SUPPORT == STD_ON )                */
    {
        if( EventStrgIndex != FreezeFrameRecordPtr->EventStrgIndex )
        {
            retVal = DEM_IRT_NG;
        }
    }

    resultOfCheckTmpCheckRecordData = Dem_Data_JudgeOutputFFDByFFDType( FreezeFrameDataType, FreezeFrameRecordIndex, FreezeFrameRecordTrigger, FreezeFrameRecordPtr->ConsistencyId );
    if( resultOfCheckTmpCheckRecordData != DEM_IRT_OK )
    {
        retVal = DEM_IRT_NG;
    }

    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
