/* Dem_UdmDataCtl_InfoFFD_c(v5-8-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmDataCtl_InfoFFD/CODE                               */
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

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
#include "../../../inc/Dem_CmnLib_DataCtl.h"
#include "../../../inc/Dem_Udm_Data.h"
#include "../../../inc/Dem_Rc_UdmMng.h"
#include "../../../inc/Dem_Rc_UdmMngTable.h"
#include "Dem_UdmDataCtl_InfoTSFFD.h"
#include "Dem_UdmDataCtl_local.h"

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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_GetSavedRecordNumberByRecordNumber
(
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) *UdmTmpRecordNumberByDTCPPtr
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

VAR( Dem_UdmTmpRecordNumberByDTCType, DEM_VAR_NO_INIT ) Dem_UdmTmpRecordNumberByDTC[DEM_UDM_MAX_NUMBER_FF_PER_DTC];

static VAR( Dem_u16_FFRecNumStoredIndexType, DEM_VAR_NO_INIT ) Dem_UdmSearchStartPositionIndex;
static VAR( Dem_u16_FFRecNumStoredIndexType, DEM_VAR_NO_INIT ) Dem_UdmStoredFFDCount;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>



/****************************************************************************/
/* Function Name | Dem_UdmData_SaveRecordNumberByDTC                        */
/* Description   | Save RecordNumber where non-OBD FFD is stored.           */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |        Udm Event Index                                   */
/*               | [in] FaultRecordPtr :                                    */
/*               |        Dem_TmpDisabledRecord.FaultRecord pointer.        */
/*               | [in/out] NumberOfSaveRecordPtr :                         */
/*               |        Total number of saved record numbers.             */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_SaveRecordNumberByDTC
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,          /* [PRMCHK:CALLER] */
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC, AUTOMATIC ) NumberOfSaveRecordPtr
)
{
    VAR( boolean , AUTOMATIC ) isOccurrenceOrderUnderflow;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFFRec;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) udmMaxNumberFFPerDTC;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) numberOfSavedRecord;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) startUdmFreezeFrameRecordIndex;
    VAR( Dem_u16_UdmFFDIndexType , AUTOMATIC ) udmFFRIndexLimit;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFreezeFrameRecordIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) maxNumberFreezeFrameRecords;
    VAR( Dem_UdmFreezeFrameRecordForCtlType, AUTOMATIC ) udmFreezeFrameRecord;

    numberOfSavedRecord = *NumberOfSaveRecordPtr;
    udmMaxNumberFFPerDTC = Dem_UdmMaxNumberFFPerDTC;
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    if ( numberOfSavedRecord < udmMaxNumberFFPerDTC )       /* [GUD:if]numberOfSavedRecord */
    {
        /* Get udm group index. */
        udmInfoTableIndex = Dem_CfgInfoUdm_GetMemoryDestination( UdmEventIndex );               /* [GUDCHK:CALLER]UdmEventIndex *//* [GUD:RET:IF_GUARDED: UdmEventIndex ]udmInfoTableIndex */
        udmGroupKindIndex = Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndexByEventIndex( udmInfoTableIndex, UdmEventIndex );

        if( udmGroupKindIndex < userDefinedMemoryNum )  /* [GUD:if]udmGroupKindIndex */
        {
            maxNumberFreezeFrameRecords = Dem_CfgInfoUdm_GetMaxNumberFreezeFrameRecords( UdmEventIndex );

            startUdmFreezeFrameRecordIndex = FaultRecordPtr->RecordNumberIndex;
            if ( startUdmFreezeFrameRecordIndex != DEM_UDMFFRECINDEX_INITIAL )
            {
                isOccurrenceOrderUnderflow = (boolean)FALSE;

                udmFFRIndexLimit = startUdmFreezeFrameRecordIndex + maxNumberFreezeFrameRecords;
                for( udmFreezeFrameRecordIndex = startUdmFreezeFrameRecordIndex; udmFreezeFrameRecordIndex < udmFFRIndexLimit; udmFreezeFrameRecordIndex++ )    /* [GUD:for]udmFreezeFrameRecordIndex */
                {
                    resultOfGetFFRec = Dem_UdmFFDMng_GetFFR_MngInfo( udmGroupKindIndex, udmFreezeFrameRecordIndex, &udmFreezeFrameRecord );     /* [GUD]udmGroupKindIndex */
                    if( resultOfGetFFRec == DEM_IRT_OK )
                    {
                        if( udmFreezeFrameRecord.RecordStatus == DEM_FFD_STORED )
                        {
                            if( udmFreezeFrameRecord.OccurrenceOrder == (Dem_u32_UdmOccurrenceOrderType)0U )
                            {
                                isOccurrenceOrderUnderflow = (boolean)TRUE;
                            }

                            Dem_UdmTmpRecordNumberByDTC[numberOfSavedRecord].OccurrenceOrder = udmFreezeFrameRecord.OccurrenceOrder;                        /* [GUD]numberOfSavedRecord */
                            Dem_UdmTmpRecordNumberByDTC[numberOfSavedRecord].CidUdmFreezeFrameRecords = udmFreezeFrameRecord.CidUdmFreezeFrameRecords;      /* [GUD]numberOfSavedRecord */
                            Dem_UdmTmpRecordNumberByDTC[numberOfSavedRecord].RecordStatus = DEM_FFD_STORED;                                                 /* [GUD]numberOfSavedRecord */
                            Dem_UdmStoredFFDCount   =   Dem_UdmStoredFFDCount + ( Dem_u16_FFRecNumStoredIndexType )1U;

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )  /*  [FuncSw]    */
                            if( udmFreezeFrameRecord.OffsetOfTSFFListIndex != DEM_NUMOFTSFF_INVALID )
                            {
                                Dem_UdmTmpRecordNumberByDTC[numberOfSavedRecord].TimeSeriesFreezeFrameListIndex = FaultRecordPtr->TimeSeriesFreezeFrameListIndex + udmFreezeFrameRecord.OffsetOfTSFFListIndex;  /* [GUD]numberOfSavedRecord */
                            }
#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */
                        }
                    }

                    Dem_UdmTmpRecordNumberByDTC[numberOfSavedRecord].FreezeFrameDataIndex = (Dem_u16_AllFFDIndexType)udmFreezeFrameRecordIndex;         /* [GUD]numberOfSavedRecord */
                    Dem_UdmTmpRecordNumberByDTC[numberOfSavedRecord].FreezeFrameDataType = DEM_FFD_TYPE_NONOBDFFD;                                      /* [GUD]numberOfSavedRecord */

                    numberOfSavedRecord = numberOfSavedRecord + (Dem_u16_UdmFFDIndexType)1U;

                    if ( numberOfSavedRecord >= udmMaxNumberFFPerDTC )      /* [GUD:if]numberOfSavedRecord */
                    {
                        break;
                    }
                }

                if( isOccurrenceOrderUnderflow == (boolean)TRUE )
                {
                    numberOfSavedRecord = *NumberOfSaveRecordPtr;               /* [GUD]numberOfSavedRecord: same logic: first check of ( numberOfSavedRecord < udmMaxNumberFFPerDTC )*/

                    for( udmFreezeFrameRecordIndex = (Dem_u16_UdmFFDIndexType)0U; udmFreezeFrameRecordIndex < maxNumberFreezeFrameRecords; udmFreezeFrameRecordIndex++ )
                    {
                        Dem_UdmTmpRecordNumberByDTC[numberOfSavedRecord].OccurrenceOrder = Dem_UdmTmpRecordNumberByDTC[numberOfSavedRecord].OccurrenceOrder ^ DEM_UDM_OCCURRENCEORDER_MSB;  /* [GUD]numberOfSavedRecord */

                        numberOfSavedRecord = numberOfSavedRecord + (Dem_u16_UdmFFDIndexType)1U;

                        if ( numberOfSavedRecord >= udmMaxNumberFFPerDTC )      /* [GUD]numberOfSavedRecord */
                        {
                            break;
                        }
                    }
                }
            }
            else
            {
                for( udmFreezeFrameRecordIndex = (Dem_u16_UdmFFDIndexType)0U; udmFreezeFrameRecordIndex < maxNumberFreezeFrameRecords; udmFreezeFrameRecordIndex++ )
                {
                    Dem_UdmTmpRecordNumberByDTC[numberOfSavedRecord].FreezeFrameDataType = DEM_FFD_TYPE_NONOBDFFD;      /* [GUD]numberOfSavedRecord */

                    numberOfSavedRecord = numberOfSavedRecord + (Dem_u16_UdmFFDIndexType)1U;

                    if ( numberOfSavedRecord >= udmMaxNumberFFPerDTC )                                                  /* [GUD:if]numberOfSavedRecord */
                    {
                        break;
                    }
                }
            }
        }
    }

    *NumberOfSaveRecordPtr = numberOfSavedRecord;

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_InitSaveTmpRecordNumber                      */
/* Description   | This function initializes Dem_TmpRecordNumberByDTC and   */
/*               | Dem_SearchStartPositionIndex.                            */
/* Preconditions |                                                          */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_InitSaveTmpRecordNumber
( void )
{
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) udmMaxNumberFFPerDTC;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) arrayIndex;

    Dem_UdmSearchStartPositionIndex = (Dem_u16_FFRecNumStoredIndexType)0U;
    Dem_UdmStoredFFDCount           = (Dem_u16_FFRecNumStoredIndexType)0U;

    udmMaxNumberFFPerDTC = Dem_UdmMaxNumberFFPerDTC;

    for( arrayIndex = (Dem_u16_FFRecNumStoredIndexType)0U; arrayIndex < udmMaxNumberFFPerDTC; arrayIndex++ )    /* [GUD:for]arrayIndex */
    {
        Dem_UdmTmpRecordNumberByDTC[arrayIndex].RecordNumber          = DEM_RECORDNUMBER_NEXT_NONE;                             /* [GUD]arrayIndex */
        Dem_UdmTmpRecordNumberByDTC[arrayIndex].FreezeFrameDataIndex  = (Dem_u16_AllFFDIndexType)DEM_UDMFFDINDEX_INVALID;       /* [GUD]arrayIndex */
        Dem_UdmTmpRecordNumberByDTC[arrayIndex].FreezeFrameDataType   = DEM_FFD_TYPE_INVALID;                                   /* [GUD]arrayIndex */
        Dem_UdmTmpRecordNumberByDTC[arrayIndex].OccurrenceOrder       = (Dem_u32_UdmOccurrenceOrderType)0U;/* Because sort items of array to backward. *//* [GUD]arrayIndex */
        Dem_UdmTmpRecordNumberByDTC[arrayIndex].CidUdmFreezeFrameRecords = DEM_CONSISTENCY_INITIAL;                             /* [GUD]arrayIndex */
        Dem_UdmTmpRecordNumberByDTC[arrayIndex].TimeSeriesFreezeFrameListIndex = DEM_TSFFLISTINDEX_INVALID;                     /* [GUD]arrayIndex */
        Dem_UdmTmpRecordNumberByDTC[arrayIndex].RecordStatus = DEM_FFD_NOT_STORED;                                              /* [GUD]arrayIndex */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_ResetSearchStartPosition                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_ResetSearchStartPosition
( void )
{
    Dem_UdmSearchStartPositionIndex = (Dem_u16_FFRecNumStoredIndexType)0U;

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )   /*  [FuncSw]    */
    Dem_UdmData_ResetTSFFSearchStartPosition();
#endif  /*  ( DEM_TSFF_UDM_SUPPORT == STD_ON )          */
    return ;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_GetFreezeFrameData                           */
/* Description   | Gets the freeze frame data corresponding to the specifi- */
/*               | ed freeze frame record index.                            */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |        The Udm event index corresponding to the specifi- */
/*               |        c DTC value.                                      */
/*               | [in] RecordNumber :                                      */
/*               |        The record number corresponding to the specified  */
/*               |         event index.                                     */
/*               | [in] FreezeFrameGetInfoType :                            */
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
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_GetFreezeFrameData
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u08_FFDGetInfoType, AUTOMATIC ) FreezeFrameGetInfoType,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DataPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) DataSizePtr
)
{
    VAR( boolean, AUTOMATIC ) retChkConsistentFFRec;
    VAR( boolean, AUTOMATIC ) retUdmDTCClerTarget;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetSavedRecNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfEditFFRec;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventConfigureNum;
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) freezeFrameClassRef;
    VAR( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC ) udmFreezeFrameRecord;
    P2VAR( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) udmTmpRecordNumberByDTCPtr;
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameClassPtr;

    retVal = DEM_IRT_WRONG_RECORDNUMBER;

    udmEventConfigureNum = Dem_UdmEventConfigureNum;
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    if( UdmEventIndex >= udmEventConfigureNum )     /* [GUD:if]UdmEventIndex */
    {
        retVal = DEM_IRT_NG;
    }
    else
    {
        Dem_CfgInfoUdm_GetFreezeFrameClassRef( UdmEventIndex, &freezeFrameClassRef );       /* [GUD:RET:Not DEM_FFCLASSINDEX_INVALID ] freezeFrameClassRef */

        if( freezeFrameClassRef == DEM_FFCLASSINDEX_INVALID )
        {
            /* No process */
        }
        else
        {
            udmTmpRecordNumberByDTCPtr = NULL_PTR;
            /* Gets the saved record number by record number from temporary record list of save record number by DTC. */
            resultOfGetSavedRecNum = Dem_UdmData_GetSavedRecordNumberByRecordNumber( RecordNumber, &udmTmpRecordNumberByDTCPtr );
            if( resultOfGetSavedRecNum != DEM_IRT_OK )
            {
#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )
                retVal = Dem_UdmData_GetFFDataFromTSFF( UdmEventIndex, RecordNumber, FreezeFrameGetInfoType, DataPtr, DataSizePtr );
#endif  /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */
            }
            else
            {
                /* Get udm group index. */
                udmInfoTableIndex = Dem_CfgInfoUdm_GetMemoryDestination( UdmEventIndex );       /* [GUD]UdmEventIndex *//* [GUD:RET:IF_GUARDED: UdmEventIndex ]udmInfoTableIndex */
                udmGroupKindIndex = Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndexByEventIndex( udmInfoTableIndex, UdmEventIndex );

                if( udmGroupKindIndex < userDefinedMemoryNum )  /* [GUD:if]udmGroupKindIndex */
                {
#ifndef JGXSTACK
                    /* Starts exclusion. */
                    Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveEnterFnc();      /* [GUD]udmGroupKindIndex */
#else   /* JGXSTACK */
                    Dem_UdmExcEnterFnc_ForStack();
#endif  /* JGXSTACK */

                    /* FreezeFrame Holds the FreezeFrameRecordIndex (RecordNumberIndex) pointed to by the acquired FreezeFrameRecordClass table index of */
                    /* the FreezeFrameList record of the updating prohibition record of the temporary RAM area in the record Index. */
                    retChkConsistentFFRec = Dem_UdmData_CheckAndGetConsistentFFRecord( ( P2CONST( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) )udmTmpRecordNumberByDTCPtr, &udmFreezeFrameRecord );

#ifndef JGXSTACK
                    /* Finishes exclusion. */
                    Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveExitFnc();       /* [GUD]udmGroupKindIndex */
#else   /* JGXSTACK */
                    Dem_UdmExcExitFnc_ForStack();
#endif  /* JGXSTACK */

                    /* The freeze frame record index is invalid. */
                    if( retChkConsistentFFRec == (boolean)FALSE )
                    {
                        /* That is the specified record number is not occurred fault. */

                        /* Stores 0 to the specified the size of freeze frame data. */
                        *DataSizePtr = 0U;

                        /* Sets the return value to OK. */
                        retVal = DEM_IRT_OK;
                    }
                    else
                    {
                        /* Checks the RecordStatus of the freeze frame record retrieved. */
                        if( udmFreezeFrameRecord.RecordStatus == DEM_FFD_STORED )
                        {
                            /* The RecordStatus of freeze frame record is STORED. */

                            retUdmDTCClerTarget = Dem_UdmDTC_JudgeUdmDTCClearTargetOnClearProcessActive( UdmEventIndex );
                            if( retUdmDTCClerTarget == (boolean)FALSE )
                            {
                                /* Holds the FreezeFrameClass table pointed to by the FreezeFrameClass table list Index of the held DTCAttribute table. */
                                freezeFrameClassPtr = &Dem_FreezeFrameClassTable[ freezeFrameClassRef ];                /* [GUD]freezeFrameClassRef */

                                /* Edit FreezeFrame record to the specified format. [SWS_Dem_00071]Figure 7.51 */
#ifndef DEM_SIT_RANGE_CHECK
                                resultOfEditFFRec = Dem_Data_EditFreezeFrameRecord( RecordNumber, FreezeFrameGetInfoType, udmFreezeFrameRecord.DataPtr, freezeFrameClassPtr, DataPtr, DataSizePtr);
#else   /* DEM_SIT_RANGE_CHECK */
                                resultOfEditFFRec = Dem_Data_EditFreezeFrameRecord( DEM_SIT_R_CHK_UDM_FF_DATA_SIZE( udmGroupKindIndex ), RecordNumber, FreezeFrameGetInfoType, udmFreezeFrameRecord.DataPtr, freezeFrameClassPtr, DataPtr, DataSizePtr);
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
                            /* Stores 0 to the specified the size of freeze frame data. */
                            *DataSizePtr = 0U;

                            /* Sets the return value to OK. */
                            retVal = DEM_IRT_OK;
                        }
                    }
                }
                else
                {
                    retVal = DEM_IRT_NG;
                }
            }
        }
    }

    /* Returns with the result. */
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_GetAllFFRecordNumber                         */
/* Description   | get all record number.                                   */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               | [out] RecordNumBufferPtr :                               */
/*               |        the buffer, to which the freeze frame data recor- */
/*               |        d shall be written to                             */
/*               | [in] TotalLengthOfBuffer :                               */
/*               |          total length of RecordNumBufferPtr.             */
/*               | [in] OffsetPosOfBuffer   :                               */
/*               |          setting offset position of RecordNumBufferPtr.  */
/*               | [out] RecordNumPtr :                                     */
/*               |        the actual number of written data bytes           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Size successfully returned           */
/*               |        DEM_IRT_WRONG_BUFFERSIZE : provided buffer size - */
/*               |        to small                                          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_GetAllFFRecordNumber
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, DEM_APPL_DATA ) RecordNumBufferPtr,
    VAR( uint8, AUTOMATIC ) TotalLengthOfBuffer,
    VAR( uint8, AUTOMATIC ) OffsetPosOfBuffer,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) RecordNumPtr
)
{
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) maxNumberFreezeFrameRecords;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC )    saveRecNumIndex;
    VAR( Dem_u08_FFStoredStatusType, AUTOMATIC ) recordStatus;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) recordNumber;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( uint8, AUTOMATIC ) recordNumCnt;
    VAR( uint8, AUTOMATIC ) recordIndex;

    recordIndex         =   OffsetPosOfBuffer;
    recordNumCnt        =   (uint8)0U;

    /*  set OK value .  if buffer size is too small, update DEM_IRT_WRONG_BUFFERSIZE.   */
    retVal  =   DEM_IRT_OK;
    maxNumberFreezeFrameRecords = Dem_CfgInfoUdm_GetMaxNumberFreezeFrameRecords( UdmEventIndex );

    /*------------------------------*/
    /*  trigger freeze frame        */
    /*------------------------------*/
    for( saveRecNumIndex =  (Dem_u16_FFRecNumStoredIndexType)0U; saveRecNumIndex < maxNumberFreezeFrameRecords; saveRecNumIndex++ ) /* [GUD:for]saveRecNumIndex */
    {
        if( DEM_FFD_TYPE_INVALID != Dem_UdmTmpRecordNumberByDTC[saveRecNumIndex].FreezeFrameDataType )                              /* [GUD]saveRecNumIndex */
        {
            recordStatus =   Dem_UdmTmpRecordNumberByDTC[saveRecNumIndex].RecordStatus;                                             /* [GUD]saveRecNumIndex */

            /*  record is stored.               */
            if ( recordStatus == DEM_FFD_STORED )
            {
                recordNumber    =   Dem_UdmTmpRecordNumberByDTC[saveRecNumIndex].RecordNumber;                                      /* [GUD]saveRecNumIndex */

                /*  check : remain buffer size          */
                if ( recordIndex < TotalLengthOfBuffer )                              /* [GUD:if]recordIndex */
                {
                    RecordNumBufferPtr[ recordIndex ]    =   recordNumber;         /* [GUD]recordIndex *//* [ARYCHK] TotalLengthOfBuffer / 1 / recordIndex */
                    recordIndex     =   recordIndex  + (uint8)1U;
                    recordNumCnt    =   recordNumCnt + (uint8)1U;
                }
                else
                {
                    /*  buffer is too small.            */
                    retVal  =   DEM_IRT_WRONG_BUFFERSIZE;
                    break;
                }
            }
        }
    }
    if ( retVal == DEM_IRT_OK )
    {
        *RecordNumPtr   =   recordNumCnt;
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_GetStoredRecordNumberCounts                  */
/* Description   | get stored freezeframe number in temporary area.         */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u16_FFRecNumStoredIndexType                          */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u16_FFRecNumStoredIndexType, DEM_CODE ) Dem_UdmData_GetStoredRecordNumberCounts
( void )
{
    return Dem_UdmStoredFFDCount;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_SetNextRecordNumber                          */
/* Description   | Return the next requested RecordNumber.                  */
/* Preconditions |                                                          */
/* Parameters    | [in] RecordNumber :                                      */
/*               |        The record number corresponding to the specified  */
/*               | [out] NextRecordNumberPtr :                              */
/*               |        This parameter contains a pointer that points to  */
/*               |        the buffer, to which the next required Record nu- */
/*               |        mber will be written.                             */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_SetNextRecordNumber
(
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC )                 RecordNumber,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC )    NextRecordNumberPtr
)
{
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC )    saveRecNumIndex;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC )    udmMaxNumberFFPerDTC;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC )    searchStartPositionIndex;

    udmMaxNumberFFPerDTC = Dem_UdmMaxNumberFFPerDTC;

    searchStartPositionIndex = Dem_UdmMaxNumberFFPerDTC;

    *NextRecordNumberPtr = DEM_RECORDNUMBER_NEXT_NONE;

    for( saveRecNumIndex =  Dem_UdmSearchStartPositionIndex; saveRecNumIndex < udmMaxNumberFFPerDTC; saveRecNumIndex++ )        /* [GUD:for]saveRecNumIndex */
    {
        if( DEM_FFD_TYPE_INVALID != Dem_UdmTmpRecordNumberByDTC[saveRecNumIndex].FreezeFrameDataType )                          /* [GUD]saveRecNumIndex */
        {
            if( Dem_UdmTmpRecordNumberByDTC[saveRecNumIndex].RecordStatus == DEM_FFD_STORED )                                   /* [GUD]saveRecNumIndex */
            {
                if( RecordNumber < Dem_UdmTmpRecordNumberByDTC[saveRecNumIndex].RecordNumber )                                  /* [GUD]saveRecNumIndex */
                {
                    *NextRecordNumberPtr = Dem_UdmTmpRecordNumberByDTC[saveRecNumIndex].RecordNumber;                           /* [GUD]saveRecNumIndex */
                    searchStartPositionIndex = saveRecNumIndex + (Dem_u16_FFRecNumStoredIndexType)1U;
                    break;
                }
            }
        }
    }

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )
    if( saveRecNumIndex >= udmMaxNumberFFPerDTC )
    {
        Dem_UdmData_SetNextTSFFRecordNumber( RecordNumber, NextRecordNumberPtr );
    }
#endif  /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */

    Dem_UdmSearchStartPositionIndex = searchStartPositionIndex;

    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dem_UdmData_GetSavedRecordNumberByRecordNumber           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] RecordNumber :                                      */
/*               |                                                          */
/*               | [out] UdmTmpRecordNumberByDTCPPtr :                      */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_GetSavedRecordNumberByRecordNumber
(
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) *UdmTmpRecordNumberByDTCPPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) udmMaxNumberFFPerDTC;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) indexOfSavedRecord;

    retVal = DEM_IRT_NG;

    udmMaxNumberFFPerDTC = Dem_UdmMaxNumberFFPerDTC;

    for( indexOfSavedRecord = (Dem_u08_FFListIndexType)0U; indexOfSavedRecord < udmMaxNumberFFPerDTC; indexOfSavedRecord++ )    /* [GUD:for]indexOfSavedRecord */
    {
        if( DEM_FFD_TYPE_INVALID != Dem_UdmTmpRecordNumberByDTC[indexOfSavedRecord].FreezeFrameDataType )                       /* [GUD]indexOfSavedRecord */
        {
            if( RecordNumber == Dem_UdmTmpRecordNumberByDTC[indexOfSavedRecord].RecordNumber )                                  /* [GUD]indexOfSavedRecord */
            {
                (*UdmTmpRecordNumberByDTCPPtr) = &Dem_UdmTmpRecordNumberByDTC[indexOfSavedRecord];                              /* [GUD]indexOfSavedRecord */
                retVal = DEM_IRT_OK;

                break;
            }
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
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
