/* Dem_StoredData_CalcRecNum_c(v5-10-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/StoredData_CalcRecNum/CODE                            */
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
#include "../../../cfg/Dem_StoredData_Cfg.h"
#include "../../../cfg/Dem_Data_Cfg.h"
#include "../../../inc/Dem_CmnLib_DataAvl.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_StoredData.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Rc_OdrLst.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include "../../../inc/Dem_Pm_Misfire.h"
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

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
static FUNC( void, DEM_CODE ) Dem_StoredData_StoreTmpOutputData
( void );
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_StoredData_ResetControlDataForTSFFD
( void );
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_StoredData_GetDTCStoredDataFromTSFFDTC
(
    VAR( Dem_u08_StoredDataRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u32_StoredDataRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_StoredData_GetDTCStoredDataFromTSFFD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u08_StoredDataRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u32_StoredDataRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr
);
static FUNC( boolean, DEM_CODE ) Dem_StoredData_CheckOutputDTCFromTSFFD
( void );
#endif  /* (DEM_TSFF_PM_SUPPORT == STD_ON) */

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_StoredData_TmpOutputDataType, DEM_VAR_NO_INIT ) Dem_StoredData_TmpOutputData[DEM_FAIL_RECORD_NUM];
static VAR( Dem_u08_FaultIndexType, DEM_VAR_NO_INIT ) Dem_StoredData_TmpOutputDataNum;
static VAR( Dem_u08_FaultIndexType, DEM_VAR_NO_INIT )  Dem_StoredData_SearchIndexOfTmpOutputData;

static VAR( Dem_u08_OrderIndexType, DEM_VAR_NO_INIT )  Dem_StoredData_NumOfOutputDTC;

static VAR( Dem_u08_StoredDataRecordNumberType, DEM_VAR_NO_INIT )  Dem_StoredData_SearchedRecordNumber;

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
static VAR( boolean, DEM_VAR_NO_INIT ) Dem_StoredData_CompleteTSFFDTCFlg;
static VAR( boolean, DEM_VAR_NO_INIT ) Dem_StoredData_CompleteToGetTSFFDFlg;
static VAR( Dem_u08_FFRecordNumberType, DEM_VAR_NO_INIT ) Dem_StoredData_TSFFDOffsetOfIndex;
static VAR( boolean, DEM_VAR_NO_INIT ) Dem_StoredData_OutputTargetTSFFDFlg;
#endif  /* (DEM_TSFF_PM_SUPPORT == STD_ON) */


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_StoredData_Init                                      */
/* Description   | Inits Dem_StoredData.                                    */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_StoredData_Init
( void )
{
    /*  This is empty function for function switching.  */
    /* No Process */
    return;
}

/****************************************************************************/
/* Function Name | Dem_StoredData_StartDTCStoredData                        */
/* Description   | Starts to process which is related to DTCStoredData.     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : A start of the processing is succes- */
/*               |        sful                                              */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_StoredData_StartDTCStoredData
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /*--------------------------------------------------------------------------*/
    /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
    /* These are the reasons why this function needs to get exclusive.          */
    /*  - This function call [DataMng] function directory.                      */
    /*  - This function called from SW-C/Dcm context.                           */
    /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
    SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
    SchM_Exit_Dem_EventMemory();
    /*--------------------------------------------------------------------------*/

    Dem_StoredData_StoreTmpOutputData();

    Dem_StoredData_SearchIndexOfTmpOutputData = (Dem_u08_FaultIndexType)0U;

    Dem_StoredData_NumOfOutputDTC = (Dem_u08_OrderIndexType)0U;

    Dem_StoredData_SearchedRecordNumber = DEM_STOREDDATA_RECNUM_00;

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )   /*  [FuncSw]    */
    Dem_StoredData_CompleteTSFFDTCFlg = (boolean)FALSE;
    Dem_StoredData_ResetControlDataForTSFFD();
#endif  /* (DEM_TSFF_PM_SUPPORT == STD_ON) */

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    Dem_Misfire_InitOutputStoredData();
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */


    retVal = DEM_IRT_OK;

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_StoredData_EndDTCStoredData                          */
/* Description   | Ends to process which is related to DTCStoredData.       */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_StoredData_EndDTCStoredData
( void )
{
    /*  This is empty function for function switching.  */
    /* No Process */
    return;
}


/****************************************************************************/
/* Function Name | Dem_StoredData_GetSizeOfDTCStoredDataByRecNum            */
/* Description   | Gets size of DTCStoredData by specific RecordNumber.     */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordNumber :                                      */
/*               |        Defines RecordNumber of DTCStoredData. The value  */
/*               |         0xFF is explicitly allowed to request the overa- */
/*               |        ll size.                                          */
/*               | [out] SizeOfStoredDataPtr :                              */
/*               |        The number of bytes of requested DTCStoredData.   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Size successfully returned           */
/*               |        DEM_IRT_NG : Failed to acquire the size           */
/*               |        DEM_IRT_PENDING : Acquiring size                  */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : Invalid record numb- */
/*               |        er                                                */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_StoredData_GetSizeOfDTCStoredDataByRecNum
(
    VAR( Dem_u08_StoredDataRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_u32_StoredDataRecordSizeType, AUTOMATIC, AUTOMATIC ) SizeOfStoredDataPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_StoredDataRecordNumberType, AUTOMATIC ) storedDataMaxRecNum;

    storedDataMaxRecNum = Dem_StoredDataMaxRecNum;

    if( RecordNumber == DEM_STOREDDATA_RECNUM_00 )
    {
        retVal = DEM_IRT_WRONG_RECORDNUMBER;
    }
    else if(( RecordNumber > storedDataMaxRecNum ) && ( RecordNumber < DEM_STOREDDATA_RECNUM_FF ))
    {
        retVal = DEM_IRT_WRONG_RECORDNUMBER;
    }
    else
    {
        retVal = DEM_IRT_OK;
        *SizeOfStoredDataPtr = (Dem_u32_StoredDataRecordSizeType)0U;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_StoredData_GetDTCStoredDataByRecNum                  */
/* Description   | Gets the DTCStoredData by specific RecordNumber.         */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordNumber :                                      */
/*               |        Defines RecordNumber of DTCStoredData. The value  */
/*               |         0xFF is not allowed. The value 0x00 indicates O- */
/*               |        BD-related DTCStoredData.                         */
/*               | [out] DestBufferPtr :                                    */
/*               |        This parameter contains a byte pointer that poin- */
/*               |        ts to the buffer, to which DTCStoredData record - */
/*               |        shall be written to.                              */
/*               | [in/out] BufSizePtr :                                    */
/*               |        When the function is called this parameter conta- */
/*               |        ins the maximum number of data bytes that can be  */
/*               |         written to the buffer. The function returns the  */
/*               |         actual number of written data bytes in this par- */
/*               |        ameter.                                           */
/*               | [out] NextRecordNumberPtr :                              */
/*               |        This parameter contains a pointer that points to  */
/*               |        the buffer, to which the next required Record nu- */
/*               |        mber will be written.                             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Retrieving of DTCStoredData success- */
/*               |        fully                                             */
/*               |        DEM_IRT_NG : Retrieving of DTCStoredData failed   */
/*               |        DEM_IRT_PENDING : The acquisition process of DTC- */
/*               |        StoredData has not been completed                 */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : Invalid record number*/
/*               |        DEM_IRT_WRONG_BUFFERSIZE : The buffer size is sm- */
/*               |        aller than the actual data                        */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_StoredData_GetDTCStoredDataByRecNum
(
    VAR( Dem_u08_StoredDataRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u32_StoredDataRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr,
    P2VAR( Dem_u08_StoredDataRecordNumberType, AUTOMATIC, AUTOMATIC ) NextRecordNumberPtr
)
{
    VAR( Dem_FreezeFrameRecordMngType, AUTOMATIC ) freezeFrameRecord;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) freezeFrameClassRef;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) searchIndexOfTmpOutputData;
    VAR( Dem_u08_StoredDataRecordNumberType, AUTOMATIC ) storedDataMaxRecNum;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) numberOfOutputStoredDataDTC;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) confirmedTriggerNonOBDFFDIndex;
    VAR( boolean, AUTOMATIC ) loopEndFlg;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) retOutputStoredData;
    VAR( boolean, AUTOMATIC ) misfireEventKind;
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

    /*--------------------------------------------------------------------------*/
    /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
    /* These are the reasons why this function needs to get exclusive.          */
    /*  - This function call [DataMng] function directory.                      */
    /*  - This function called from SW-C/Dcm context.                           */
    /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
    SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
    SchM_Exit_Dem_EventMemory();
    /*--------------------------------------------------------------------------*/

    retVal = DEM_IRT_NG;
    *NextRecordNumberPtr = DEM_RECORDNUMBER_NEXT_NONE;
    storedDataMaxRecNum = Dem_StoredDataMaxRecNum;
    numberOfOutputStoredDataDTC = Dem_NumberOfOutputStoredDataDTC;
    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;
    loopEndFlg = (boolean)FALSE;

    if( RecordNumber == DEM_STOREDDATA_RECNUM_00 )
    {
        retVal = DEM_IRT_WRONG_RECORDNUMBER;
    }
    else if( RecordNumber > storedDataMaxRecNum )
    {
        retVal = DEM_IRT_WRONG_RECORDNUMBER;
    }
    else
    {
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )   /*  [FuncSw]    */
        if( Dem_StoredData_CompleteTSFFDTCFlg == (boolean)FALSE )
        {
            retVal = Dem_StoredData_GetDTCStoredDataFromTSFFDTC( RecordNumber, DestBufferPtr, BufSizePtr );
            if( retVal == DEM_IRT_NO_MATCHING_ELEMENT )
            {
                Dem_StoredData_CompleteTSFFDTCFlg = (boolean)TRUE;
                Dem_StoredData_SearchIndexOfTmpOutputData = (Dem_u08_FaultIndexType)0U;
            }
        }

        if( Dem_StoredData_CompleteTSFFDTCFlg == (boolean)TRUE )
#endif  /* (DEM_TSFF_PM_SUPPORT == STD_ON) */
        {
            for( searchIndexOfTmpOutputData = Dem_StoredData_SearchIndexOfTmpOutputData; searchIndexOfTmpOutputData < Dem_StoredData_TmpOutputDataNum; searchIndexOfTmpOutputData++ )   /* [GUD:for]searchIndexOfTmpOutputData */
            {
                if( Dem_StoredData_NumOfOutputDTC < numberOfOutputStoredDataDTC )
                {
                    if( Dem_StoredData_SearchedRecordNumber < RecordNumber )
                    {
                        if( Dem_StoredData_TmpOutputData[ searchIndexOfTmpOutputData ].AlreadyOutputFlg == (boolean)FALSE )         /* [GUD]searchIndexOfTmpOutputData */
                        {
                            eventStrgIndex = Dem_StoredData_TmpOutputData[ searchIndexOfTmpOutputData ].EventStrgIndex;             /* [GUD]searchIndexOfTmpOutputData */
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                            misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( eventStrgIndex );
                            if( misfireEventKind == (boolean)TRUE )
                            {
                                retOutputStoredData = Dem_Misfire_CheckOutputStoredData( eventStrgIndex );
                            }
                            else
                            {
                                retOutputStoredData = (boolean)TRUE;
                            }
                            if( retOutputStoredData == (boolean)TRUE )
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
                            {
                                faultIndex = DEM_FAULTINDEX_INITIAL;
                                (void)Dem_DataMngC_GetER_FaultIndex( eventStrgIndex, &faultIndex );     /* no return check required */          /* [GUD:RET:DEM_IRT_OK] EventStrgIndex */

                                confirmedTriggerNonOBDFFDIndex = Dem_Data_GetConfirmedTriggerNonOBDFFDIndex( faultIndex, &freezeFrameClassRef );
                                /* This function checks whether faultIndex is valid */
                                if( confirmedTriggerNonOBDFFDIndex < nonObdFFDRecordNum )
                                {
                                    (void)Dem_DataMngC_GetFreezeFrameRecord( confirmedTriggerNonOBDFFDIndex, &freezeFrameRecord );     /* no return check required */
                                    if( freezeFrameRecord.RecordStatus == DEM_FFD_STORED )
                                    {
                                        Dem_StoredData_SearchedRecordNumber = Dem_StoredData_SearchedRecordNumber + (Dem_u08_StoredDataRecordNumberType)1U;
                                        Dem_StoredData_NumOfOutputDTC = Dem_StoredData_NumOfOutputDTC + (Dem_u08_OrderIndexType)1U;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                                        if( misfireEventKind == (boolean)TRUE )
                                        {
                                            Dem_Misfire_CompletedOutputStoredData();
                                        }
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
                                        if( Dem_StoredData_SearchedRecordNumber == RecordNumber )
                                        {
                                            Dem_StoredData_SetDTCAndStatusOfStoredData( eventStrgIndex );

#ifndef DEM_SIT_RANGE_CHECK
                                            retVal = Dem_StoredData_GetStoredData( RecordNumber, freezeFrameRecord.DataPtr, freezeFrameClassRef, DestBufferPtr, BufSizePtr );
#else   /* DEM_SIT_RANGE_CHECK */
                                            retVal = Dem_StoredData_GetStoredData( DEM_SIT_R_CHK_NONOBD_FF_DATA_SIZE, RecordNumber, freezeFrameRecord.DataPtr, freezeFrameClassRef, DestBufferPtr, BufSizePtr );
#endif  /* DEM_SIT_RANGE_CHECK */
                                            loopEndFlg = (boolean)TRUE;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        /* If the previous RecordNumber is specifiedd */
                        loopEndFlg = (boolean)TRUE;
                        retVal = DEM_IRT_OK;
                        *BufSizePtr = (Dem_u32_StoredDataRecordSizeType)0U;
                    }
                }
                else
                {
                    loopEndFlg = (boolean)TRUE;
                    retVal = DEM_IRT_OK;
                    *BufSizePtr = (Dem_u32_StoredDataRecordSizeType)0U;
                }

                if( loopEndFlg == (boolean)TRUE )
                {
                    break;
                }
            }

            Dem_StoredData_SearchIndexOfTmpOutputData = searchIndexOfTmpOutputData;
            if( searchIndexOfTmpOutputData < Dem_StoredData_TmpOutputDataNum )
            {
                Dem_StoredData_SearchIndexOfTmpOutputData = Dem_StoredData_SearchIndexOfTmpOutputData + (Dem_u08_FaultIndexType)1U;
            }
            else
            {
                retVal = DEM_IRT_OK;
                *BufSizePtr = (Dem_u32_StoredDataRecordSizeType)0U;
            }
        }

        if( (retVal == DEM_IRT_OK) && (*BufSizePtr > (Dem_u32_StoredDataRecordSizeType)0U) )
        {
            if( Dem_StoredData_SearchedRecordNumber < storedDataMaxRecNum )
            {
                *NextRecordNumberPtr = Dem_StoredData_SearchedRecordNumber + (Dem_u08_StoredDataRecordNumberType)1U;
            }
        }
    }



    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_StoredData_StoreTmpOutputData                        */
/* Description   | Store Dem_StoredData_TmpOutputData[]                     */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-10-0     | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_StoredData_StoreTmpOutputData
( void )
{
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) dtcValue;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetFaultRegistOrderListData;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( boolean, AUTOMATIC ) availableStatus;
    VAR( boolean, AUTOMATIC ) resultValidateDTC;

    Dem_StoredData_TmpOutputDataNum = (Dem_u08_FaultIndexType)0U;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    failRecordNum = Dem_FailRecordNum;
    for( orderListIndex = ( Dem_u08_OrderIndexType )0U; orderListIndex < failRecordNum; orderListIndex++ )     /* [GUD:for]orderListIndex/Dem_StoredData_TmpOutputDataNum */
    {
        retGetFaultRegistOrderListData = Dem_OdrLst_Confirmed_GetFaultIndexByOrder( orderListIndex, &faultIndex );
        if( retGetFaultRegistOrderListData == DEM_IRT_OK )
        {
            (void)Dem_DataMngC_GetFR_EventStrgIndex( faultIndex, &eventStrgIndex );     /* no return check required */
            if( eventStrgIndex < eventStorageNum )                                          /* [GUD:if]eventStrgIndex */
            {
                availableStatus = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndex );     /* [GUD]eventStrgIndex */
                if( availableStatus == (boolean)TRUE )
                {
                    dtcValue = Dem_CfgInfoPm_GetUdsDTCValue( eventStrgIndex );              /* [GUD]eventStrgIndex */
                    resultValidateDTC = Dem_DataAvl_ValidateDTC( dtcValue );
                    if( resultValidateDTC == (boolean)TRUE )
                    {
                        Dem_StoredData_TmpOutputData[ Dem_StoredData_TmpOutputDataNum ].EventStrgIndex = eventStrgIndex;    /* [GUD]Dem_StoredData_TmpOutputDataNum */
                        Dem_StoredData_TmpOutputData[ Dem_StoredData_TmpOutputDataNum ].AlreadyOutputFlg = (boolean)FALSE;  /* [GUD]Dem_StoredData_TmpOutputDataNum */
                        Dem_StoredData_TmpOutputDataNum = Dem_StoredData_TmpOutputDataNum + (Dem_u08_FaultIndexType)1U;     /* [GUD:for]Dem_StoredData_TmpOutputDataNum(under orderListIndex) */
                    }
                }
            }
        }
    }

    return;
}

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_StoredData_ResetControlDataForTSFFD                  */
/* Description   | Reset control data for getting StoredData from TSFFD.    */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_StoredData_ResetControlDataForTSFFD
( void )
{
    Dem_StoredData_CompleteToGetTSFFDFlg = (boolean)FALSE;
    Dem_StoredData_TSFFDOffsetOfIndex = (Dem_u08_FFRecordNumberType)0U;
    Dem_StoredData_OutputTargetTSFFDFlg = (boolean)FALSE;

    return;
}


/****************************************************************************/
/* Function Name | Dem_StoredData_GetDTCStoredDataFromTSFFDTC               */
/* Description   | Gets the DTCStoredData from DTC storing TSFFD.           */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordNumber :                                      */
/*               |        Defines RecordNumber of DTCStoredData. The value  */
/*               |         0xFF is not allowed. The value 0x00 indicates O- */
/*               |        BD-related DTCStoredData.                         */
/*               | [out] DestBufferPtr :                                    */
/*               |        This parameter contains a byte pointer that poin- */
/*               |        ts to the buffer, to which DTCStoredData record - */
/*               |        shall be written to.                              */
/*               | [in/out] BufSizePtr :                                    */
/*               |        When the function is called this parameter conta- */
/*               |        ins the maximum number of data bytes that can be  */
/*               |         written to the buffer. The function returns the  */
/*               |         actual number of written data bytes in this par- */
/*               |        ameter.                                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Retrieving of DTCStoredData success- */
/*               |        fully                                             */
/*               |        DEM_IRT_NG : Retrieving of DTCStoredData failed   */
/*               |        DEM_IRT_PENDING : The acquisition process of DTC- */
/*               |        StoredData has not been completed                 */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : Invalid record number*/
/*               |        DEM_IRT_WRONG_BUFFERSIZE : The buffer size is sm- */
/*               |        aller than the actual data                        */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_StoredData_GetDTCStoredDataFromTSFFDTC
(
    VAR( Dem_u08_StoredDataRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u32_StoredDataRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr
)
{
    VAR( Dem_FreezeFrameRecordMngType, AUTOMATIC ) freezeFrameRecord;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) freezeFrameClassRef;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) numberOfOutputStoredDataTSFFDTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetDTCStoredDataFromTSFFD;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) searchIndexOfTmpOutputData;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) confirmedTriggerNonOBDFFDIndex;
    VAR( boolean, AUTOMATIC ) loopEndFlg;
    VAR( boolean, AUTOMATIC ) getConfirmedTriggerNonOBDFFDFlg;
    VAR( boolean, AUTOMATIC ) checkOutputDTCFromTSFFDFlg;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) retOutputStoredData;
    VAR( boolean, AUTOMATIC ) misfireEventKind;
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

    retVal = DEM_IRT_NO_MATCHING_ELEMENT;
    numberOfOutputStoredDataTSFFDTC = Dem_NumberOfOutputStoredDataTSFFDTC;
    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;
    loopEndFlg = (boolean)FALSE;
    getConfirmedTriggerNonOBDFFDFlg = (boolean)FALSE;

    for( searchIndexOfTmpOutputData = Dem_StoredData_SearchIndexOfTmpOutputData; searchIndexOfTmpOutputData < Dem_StoredData_TmpOutputDataNum; searchIndexOfTmpOutputData++ )   /* [GUD:for]searchIndexOfTmpOutputData */
    {
        if( Dem_StoredData_NumOfOutputDTC < numberOfOutputStoredDataTSFFDTC )
        {
            if( Dem_StoredData_SearchedRecordNumber < RecordNumber )
            {
                eventStrgIndex = Dem_StoredData_TmpOutputData[ searchIndexOfTmpOutputData ].EventStrgIndex;         /* [GUD]searchIndexOfTmpOutputData */
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( eventStrgIndex );
                if( misfireEventKind == (boolean)TRUE )
                {
                    retOutputStoredData = Dem_Misfire_CheckOutputStoredData( eventStrgIndex );
                }
                else
                {
                    retOutputStoredData = (boolean)TRUE;
                }
                if( retOutputStoredData == (boolean)TRUE )
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
                {
                    faultIndex = DEM_FAULTINDEX_INITIAL;
                    (void)Dem_DataMngC_GetER_FaultIndex( eventStrgIndex, &faultIndex );     /* no return check required */          /* [GUD:RET:DEM_IRT_OK] EventStrgIndex */

                    retGetDTCStoredDataFromTSFFD = Dem_StoredData_GetDTCStoredDataFromTSFFD( eventStrgIndex, faultIndex, RecordNumber, DestBufferPtr, BufSizePtr );
                    if( retGetDTCStoredDataFromTSFFD == DEM_IRT_NO_MATCHING_ELEMENT )
                    {
                        /* When there is no more berofe TSFFD */
                        checkOutputDTCFromTSFFDFlg = Dem_StoredData_CheckOutputDTCFromTSFFD();
                        if( checkOutputDTCFromTSFFDFlg == (boolean)TRUE )
                        {
                            /* if the berofe TSFFD was stored */
                            Dem_StoredData_NumOfOutputDTC = Dem_StoredData_NumOfOutputDTC + (Dem_u08_OrderIndexType)1U;
                            Dem_StoredData_TmpOutputData[ searchIndexOfTmpOutputData ].AlreadyOutputFlg = (boolean)TRUE;            /* [GUD]searchIndexOfTmpOutputData */

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                            if( misfireEventKind == (boolean)TRUE )
                            {
                                Dem_Misfire_CompletedOutputStoredData();
                            }
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

                            confirmedTriggerNonOBDFFDIndex = Dem_Data_GetConfirmedTriggerNonOBDFFDIndex( faultIndex, &freezeFrameClassRef );
                            /* This function checks whether faultIndex is valid */
                            if( confirmedTriggerNonOBDFFDIndex < nonObdFFDRecordNum )
                            {
                                (void)Dem_DataMngC_GetFreezeFrameRecord( confirmedTriggerNonOBDFFDIndex, &freezeFrameRecord );  /* no return check required */
                                if( freezeFrameRecord.RecordStatus == DEM_FFD_STORED )
                                {
                                    Dem_StoredData_SearchedRecordNumber = Dem_StoredData_SearchedRecordNumber + (Dem_u08_StoredDataRecordNumberType)1U;

                                    if( Dem_StoredData_SearchedRecordNumber == RecordNumber )
                                    {
#ifndef DEM_SIT_RANGE_CHECK
                                        retVal = Dem_StoredData_GetStoredData( RecordNumber, freezeFrameRecord.DataPtr, freezeFrameClassRef, DestBufferPtr, BufSizePtr );
#else   /* DEM_SIT_RANGE_CHECK */
                                        retVal = Dem_StoredData_GetStoredData( DEM_SIT_R_CHK_NONOBD_FF_DATA_SIZE, RecordNumber, freezeFrameRecord.DataPtr, freezeFrameClassRef, DestBufferPtr, BufSizePtr );
#endif  /* DEM_SIT_RANGE_CHECK */
                                        getConfirmedTriggerNonOBDFFDFlg = (boolean)TRUE;
                                        loopEndFlg = (boolean)TRUE;
                                    }
                                }
                            }
                        }
                        Dem_StoredData_ResetControlDataForTSFFD();
                    }
                    else
                    {
                        retVal = retGetDTCStoredDataFromTSFFD;
                        /* BufSizePtr has been stored in function Dem_StoredData_GetDTCStoredDataFromTSFFD */
                        loopEndFlg = (boolean)TRUE;
                    }
                }
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                else
                {
                    /* When there is no more berofe TSFFD */
                    checkOutputDTCFromTSFFDFlg = Dem_StoredData_CheckOutputDTCFromTSFFD();
                    if( checkOutputDTCFromTSFFDFlg == (boolean)TRUE )
                    {
                        /* if the berofe TSFFD was stored */
                        Dem_StoredData_NumOfOutputDTC = Dem_StoredData_NumOfOutputDTC + (Dem_u08_OrderIndexType)1U;
                        Dem_StoredData_TmpOutputData[ searchIndexOfTmpOutputData ].AlreadyOutputFlg = (boolean)TRUE;        /* [GUD]searchIndexOfTmpOutputData */

                        /* This process enters only when Event is Misfire */
                        Dem_Misfire_CompletedOutputStoredData();
                    }
                    Dem_StoredData_ResetControlDataForTSFFD();
                }
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
            }
            else
            {
                /* If the previous RecordNumber is specifiedd */
                loopEndFlg = (boolean)TRUE;
            }
        }
        else
        {
            loopEndFlg = (boolean)TRUE;
        }

        if( loopEndFlg == (boolean)TRUE )
        {
            break;
        }
    }

    Dem_StoredData_SearchIndexOfTmpOutputData = searchIndexOfTmpOutputData;

    if( searchIndexOfTmpOutputData < Dem_StoredData_TmpOutputDataNum )
    {
        if( getConfirmedTriggerNonOBDFFDFlg == (boolean)TRUE )
        {
            /* If get StoredData from confirmed trigger NonOBDFFD where confirmed trigger beforeTSFFD exists */
            Dem_StoredData_SearchIndexOfTmpOutputData = Dem_StoredData_SearchIndexOfTmpOutputData + (Dem_u08_FaultIndexType)1U;
        }
    }

    return retVal;
}
/****************************************************************************/
/* Function Name | Dem_StoredData_GetDTCStoredDataFromTSFFD                 */
/* Description   | Gets the DTCStoredData from TSFFD.                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        EventStrgIndex for retrieving of DTC and statusO- */
/*               |        fDTC.                                             */
/*               | [in] FaultIndex : Dem_FaultRecordList array's index      */
/*               | [in] RecordNumber :                                      */
/*               |        Defines RecordNumber of DTCStoredData. The value  */
/*               |         0xFF is not allowed. The value 0x00 indicates O- */
/*               |        BD-related DTCStoredData.                         */
/*               | [out] DestBufferPtr :                                    */
/*               |        This parameter contains a byte pointer that poin- */
/*               |        ts to the buffer, to which DTCStoredData record - */
/*               |        shall be written to.                              */
/*               | [in/out] BufSizePtr :                                    */
/*               |        When the function is called this parameter conta- */
/*               |        ins the maximum number of data bytes that can be  */
/*               |         written to the buffer. The function returns the  */
/*               |         actual number of written data bytes in this par- */
/*               |        ameter.                                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Retrieving of DTCStoredData success- */
/*               |        fully                                             */
/*               |        DEM_IRT_NG : Retrieving of DTCStoredData failed   */
/*               |        DEM_IRT_WRONG_BUFFERSIZE : The buffer size is sm- */
/*               |        aller than the actual data                        */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : Could not find Sto- */
/*               |        redData to be output from target TSFFD.           */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_StoredData_GetDTCStoredDataFromTSFFD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u08_StoredDataRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u32_StoredDataRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr
)
{
    VAR( Dem_FreezeFrameRecordMngType, AUTOMATIC ) tsFFRecord;
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) freezeFrameClassRef;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) confirmedTriggerTsffListIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetTSFFRec;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) numberOfBeforeTSFFD;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) tsFFDOffsetOfIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) serchTSFFDloopEndFlg;

    retVal = DEM_IRT_NO_MATCHING_ELEMENT;
    tsffTotalDTCNum = Dem_TSFFTotalDTCNum;

    serchTSFFDloopEndFlg = (boolean)FALSE;

    if( Dem_StoredData_CompleteToGetTSFFDFlg != (boolean)TRUE )
    {
        confirmedTriggerTsffListIndex = Dem_Data_GetConfirmedTriggerBeforeTSFFListIndexAndInfo( FaultIndex, &numberOfBeforeTSFFD, &freezeFrameClassRef );
        /* This function checks whether FaultIndex is valid */
        if( confirmedTriggerTsffListIndex < tsffTotalDTCNum )
        {
            if( Dem_StoredData_TSFFDOffsetOfIndex == (Dem_u08_FFRecordNumberType)0U )
            {
                Dem_StoredData_SetDTCAndStatusOfStoredData( EventStrgIndex );
            }

            for( tsFFDOffsetOfIndex = Dem_StoredData_TSFFDOffsetOfIndex; tsFFDOffsetOfIndex < numberOfBeforeTSFFD; tsFFDOffsetOfIndex++ )
            {
                resultOfGetTSFFRec = Dem_Data_GetTSFFRecordFromTSFFList( confirmedTriggerTsffListIndex, tsFFDOffsetOfIndex, &tsFFRecord );
                if( resultOfGetTSFFRec == DEM_IRT_OK )
                {
                    if( tsFFRecord.RecordStatus == DEM_FFD_STORED )
                    {
                        Dem_StoredData_SearchedRecordNumber = Dem_StoredData_SearchedRecordNumber + (Dem_u08_StoredDataRecordNumberType)1U;
                        Dem_StoredData_OutputTargetTSFFDFlg = (boolean)TRUE;
                        if( Dem_StoredData_SearchedRecordNumber == RecordNumber )
                        {
#ifndef DEM_SIT_RANGE_CHECK
                            retVal = Dem_StoredData_GetStoredData( RecordNumber, tsFFRecord.DataPtr, freezeFrameClassRef, DestBufferPtr, BufSizePtr );
#else   /* DEM_SIT_RANGE_CHECK */
                            retVal = Dem_StoredData_GetStoredData( DEM_SIT_R_CHK_TS_FF_DATA_SIZE, RecordNumber, tsFFRecord.DataPtr, freezeFrameClassRef, DestBufferPtr, BufSizePtr );
#endif  /* DEM_SIT_RANGE_CHECK */
                            serchTSFFDloopEndFlg = (boolean)TRUE;
                        }
                    }
                }

                Dem_StoredData_TSFFDOffsetOfIndex = Dem_StoredData_TSFFDOffsetOfIndex + (Dem_u08_FFRecordNumberType)1U;
                if( serchTSFFDloopEndFlg == (boolean)TRUE )
                {
                    break;
                }
            }

            if( serchTSFFDloopEndFlg != (boolean)TRUE )
            {
                /* When you can't get StoredData from TSFFD */
                Dem_StoredData_CompleteToGetTSFFDFlg = (boolean)TRUE;
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_StoredData_CheckOutputDTCFromTSFFD                   */
/* Description   | Check output DTC from TSFFD.                             */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |        TRUE : already output.                            */
/*               |        FALSE : no output.                                */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_StoredData_CheckOutputDTCFromTSFFD
( void )
{
    return Dem_StoredData_OutputTargetTSFFDFlg;
}

#endif  /* (DEM_TSFF_PM_SUPPORT == STD_ON) */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )     */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
