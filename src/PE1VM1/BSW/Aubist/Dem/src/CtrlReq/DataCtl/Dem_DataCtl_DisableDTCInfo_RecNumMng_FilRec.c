/* Dem_DataCtl_DisableDTCInfo_RecNumMng_FilRec_c(v5-10-0)                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_DisableDTCInfo_RecNumMng_FilRec/CODE          */
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
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Rc_MisfireMng.h"

#include "Dem_DataCtl_local.h"

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
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
/* Function Name | Dem_Data_InitSaveTmpRecordNumberForFilteredRecord        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | from SID19-03(OnRetrieval) only.                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_InitSaveTmpRecordNumberForFilteredRecord
( void )
{
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) tmpRecordNumberMaxNum;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) arrayIndex;

    tmpRecordNumberMaxNum = Dem_TotalNumOfRecNumPerDTC;

    for( arrayIndex = (Dem_u16_FFRecNumStoredIndexType)0U; arrayIndex < tmpRecordNumberMaxNum; arrayIndex++ )           /* [GUD:for]arrayIndex */
    {
        Dem_TmpRecordNumberByDTC[arrayIndex].EventStrgIndex        = DEM_EVENTSTRGINDEX_INVALID;                        /* [GUD]arrayIndex */
        Dem_TmpRecordNumberByDTC[arrayIndex].RecordNumber          = DEM_RECORDNUMBER_NEXT_NONE;                        /* [GUD]arrayIndex */
        Dem_TmpRecordNumberByDTC[arrayIndex].FreezeFrameDataIndex  = (Dem_u16_AllFFDIndexType)DEM_FFDINDEX_INVALID;     /* [GUD]arrayIndex */
        Dem_TmpRecordNumberByDTC[arrayIndex].FreezeFrameDataType   = DEM_FFD_TYPE_INVALID;                              /* [GUD]arrayIndex */
    }

    return;
}

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_SaveObdRecordNumberByDTCForFilteredRecord       */
/* Description   | Save RecordNumber where OBD FFD is stored.               */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [in] MisfireCylinderNumber :                             */
/*               |        Cylinder Number.                                  */
/*               | [in/out] NumberOfSaveRecordPtr :                         */
/*               |        Total number of saved record numbers.             */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created. based on Dem_Data_SaveObdRecordNumberByDTC. */
/*   v5-7-0      | no branch changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/*   v5-10-0     | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_SaveObdRecordNumberByDTCForFilteredRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,  /* MISRA DEVIATION */
    P2VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC, AUTOMATIC ) NumberOfSaveRecordPtr
)
{
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA )  freezeFrameRecNumClassPtr;
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC )                                          obdFreezeFrameClassRef;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC )                                    obdFreezeframeRecNumClassRef;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC )                                   numberOfSaveRecord;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC )                                    freezeFrameRecordClassIndex;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC )                                    ffrRecordClassConfigureNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC )                                           freezeFrameRecordClassRefIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC )                                           obdFFRClassPerDTCMaxNum;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC )                                   tmpRecordNumberMaxNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC )                                              obdFFDRecordNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC )                                              freezeFrameIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC )                                        eventStrgIndex;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC )                                        freezeFrameRecordNumber;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC )                                        freezeFrameRecordTrigger;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC )                                                           checkOutputRecord;
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

    obdFFDRecordNum = Dem_CfgInfoPm_GetObdFFDRecordNum();
    Dem_CfgInfoPm_GetOBDFreezeFrameAndRecNumClass( EventStrgIndex, &obdFreezeFrameClassRef, &obdFreezeframeRecNumClassRef );                    /* [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] obdFreezeFrameClassRef *//* [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] obdFreezeframeRecNumClassRef */

    if ( obdFreezeframeRecNumClassRef != DEM_FFRECNUMCLASSINDEX_INVALID )                                                                       /* [GUD:if]obdFreezeframeRecNumClassRef */
    {
        /* Holds the FreezeFrameClass table pointed to by the FreezeFrameClass table list Index of the held DTCAttribute table. */
        freezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[obdFreezeframeRecNumClassRef];                                             /* [GUD]obdFreezeframeRecNumClassRef *//* [GUD:CFG:IF_GUARDED: obdFreezeframeRecNumClassRef ]freezeFrameRecNumClassPtr */

        numberOfSaveRecord          = *NumberOfSaveRecordPtr;
        tmpRecordNumberMaxNum = Dem_TotalNumOfRecNumPerDTC;

        if ( numberOfSaveRecord < tmpRecordNumberMaxNum )                                                                                               /* [GUD:if] numberOfSaveRecord */
        {

            Dem_CfgInfoPm_GetNumOfOBDFreezeFrameRecordClass( &ffrRecordClassConfigureNum, &obdFFRClassPerDTCMaxNum );

            for( freezeFrameRecordClassRefIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordClassRefIndex < obdFFRClassPerDTCMaxNum; freezeFrameRecordClassRefIndex++ )     /* [GUD:for] freezeFrameRecordClassRefIndex */
            {
                freezeFrameRecordClassIndex = freezeFrameRecNumClassPtr->DemFreezeFrameRecordClassRef[freezeFrameRecordClassRefIndex];                  /* [GUD]freezeFrameRecNumClassPtr *//* [GUD] freezeFrameRecordClassRefIndex *//* [ARYCHK] DEM_FF_RECORD_CLASS_REF_MAX_NUM / 1 / freezeFrameRecordClassRefIndex */

                if( freezeFrameRecordClassIndex < ffrRecordClassConfigureNum )                                                                          /* [GUD:if] freezeFrameRecordClassIndex */
                {
                    /* Holds the FreezeFrameRecordClass table pointed to by DemFreezeFrameRecordIndex. */
                    Dem_CfgInfoPm_GetFreezeFrameRecordInfo_forOutputOBDFFD( freezeFrameRecordClassIndex, &freezeFrameRecordNumber, &freezeFrameRecordTrigger );       /* [GUD] freezeFrameRecordClassIndex */

                    freezeFrameIndex = Dem_Data_GetDisabledObdRecordNumberIndexForFilteredRecord( EventStrgIndex, freezeFrameRecordClassRefIndex, &eventStrgIndex );

                    if ( freezeFrameIndex < obdFFDRecordNum )                                                                                           /* [GUD:if] freezeFrameIndex */
                    {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
                        checkOutputRecord = Dem_DataCtl_CheckOutputRecordByTrigger_OBDFFD( eventStrgIndex, MisfireCylinderNumber, freezeFrameRecordTrigger );
                        if( checkOutputRecord == (boolean)TRUE )
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
                        {
                            /*--------------------------------------------------------------------------*/
                            /* Due to the processing structure, the value of numberOfSaveRecord         */
                            /* does not exceed the number of configs of FFD.                            */
                            /* Therefore, numberOfSaveRecord does not point to an element outside       */
                            /* the range of Dem_TmpRecordNumberByDTC.                                   */
                            Dem_TmpRecordNumberByDTC[numberOfSaveRecord].EventStrgIndex         = eventStrgIndex;                                           /* [GUD] numberOfSaveRecord */
                            Dem_TmpRecordNumberByDTC[numberOfSaveRecord].RecordNumber           = freezeFrameRecordNumber;                                  /* [GUD] numberOfSaveRecord */
                            Dem_TmpRecordNumberByDTC[numberOfSaveRecord].FreezeFrameDataIndex   = (Dem_u16_AllFFDIndexType)freezeFrameIndex;                /* [GUD] numberOfSaveRecord */
                            Dem_TmpRecordNumberByDTC[numberOfSaveRecord].FreezeFrameDataType    = DEM_FFD_TYPE_OBDFFD;                                      /* [GUD] numberOfSaveRecord */
                            /*--------------------------------------------------------------------------*/

                            numberOfSaveRecord = numberOfSaveRecord + (Dem_u16_FFRecNumStoredIndexType)1U;

                            /*  range check : Dem_TmpRecordNumberByDTC[]        */
                            if ( numberOfSaveRecord >= tmpRecordNumberMaxNum )                                                                              /* [GUD:if] numberOfSaveRecord */
                            {
                                break;
                            }
                        }
                    }
                }
            }
        }

        *NumberOfSaveRecordPtr = numberOfSaveRecord;
    }

    return;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

/****************************************************************************/
/* Function Name | Dem_Data_SaveRecordNumberByDTCForFilteredRecord          */
/* Description   | Save RecordNumber where non-OBD FFD is stored.           */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [in] MisfireCylinderNumber :                             */
/*               |        Cylinder Number.                                  */
/*               | [in/out] NumberOfSaveRecordPtr :                         */
/*               |        Total number of saved record numbers.             */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created. based on Dem_Data_SaveRecordNumberByDTC.    */
/*   v5-7-0      | no branch changed.                                       */
/*   v5-9-0      | branch changed.                                          */
/*   v5-10-0     | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_SaveRecordNumberByDTCForFilteredRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,      /* MISRA DEVIATION */
    P2VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC, AUTOMATIC ) NumberOfSaveRecordPtr
)
{
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA )  freezeFrameRecNumClassPtr;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC )                                   tmpRecordNumberMaxNum;
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC )                                          freezeFrameClassRef;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC )                                    freezeframeRecNumClassRef;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC )                                   numberOfSaveRecord;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC )                                    freezeFrameRecordClassIndex;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC )                                    ffrRecordClassConfigureNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC )                                           freezeFrameRecordClassRefIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC )                                           nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC )                                              nonObdFFDRecordNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC )                                              freezeFrameIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC )                                        eventStrgIndex;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC )                                        freezeFrameRecordNumber;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC )                                        freezeFrameRecordTrigger;
    VAR( boolean, AUTOMATIC )                                                           freezeFrameRecordToDcm;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC )                                                           checkOutputRecord;
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;
    Dem_CfgInfoPm_GetFreezeFrameAndRecNumClass( EventStrgIndex, &freezeFrameClassRef, &freezeframeRecNumClassRef );     /* [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] freezeFrameClassRef *//* [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] freezeframeRecNumClassRef */

    if ( freezeframeRecNumClassRef!= DEM_FFRECNUMCLASSINDEX_INVALID )                                                   /* [GUD:if] freezeframeRecNumClassRef */
    {
        /* Holds the FreezeFrameClass table pointed to by the FreezeFrameClass table list Index of the held DTCAttribute table. */
        freezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[ freezeframeRecNumClassRef ];                      /* [GUD] freezeframeRecNumClassRef */

        numberOfSaveRecord          = *NumberOfSaveRecordPtr;

        tmpRecordNumberMaxNum = Dem_TotalNumOfRecNumPerDTC;

        if ( numberOfSaveRecord < tmpRecordNumberMaxNum )                                                               /* [GUD:if] numberOfSaveRecord */
        {
            Dem_CfgInfoPm_GetNumOfFreezeFrameRecordClass( &ffrRecordClassConfigureNum, &nonOBDFFRClassPerDTCMaxNum );

            for( freezeFrameRecordClassRefIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordClassRefIndex < nonOBDFFRClassPerDTCMaxNum; freezeFrameRecordClassRefIndex++ )  /* [GUD:for] freezeFrameRecordClassRefIndex */
            {
                freezeFrameRecordClassIndex = freezeFrameRecNumClassPtr->DemFreezeFrameRecordClassRef[freezeFrameRecordClassRefIndex];                                          /* [GUD] freezeFrameRecordClassRefIndex *//* [ARYCHK] DEM_FF_RECORD_CLASS_REF_MAX_NUM / 1 / freezeFrameRecordClassRefIndex */

                if( freezeFrameRecordClassIndex < ffrRecordClassConfigureNum )                                                                                                  /* [GUD:if] freezeFrameRecordClassIndex */
                {
                    /* Holds the FreezeFrameRecordClass table pointed to by DemFreezeFrameRecordIndex. */
                    Dem_CfgInfoPm_GetFreezeFrameRecordInfo_forOutput( freezeFrameRecordClassIndex, &freezeFrameRecordNumber, &freezeFrameRecordTrigger, &freezeFrameRecordToDcm );  /* [GUD] freezeFrameRecordClassIndex */

                    if ( freezeFrameRecordToDcm == (boolean)TRUE )
                    {
                        freezeFrameIndex = Dem_Data_GetDisabledRecordNumberIndexForFilteredRecord( EventStrgIndex, freezeFrameRecordClassRefIndex, &eventStrgIndex );   /* [GUD] freezeFrameRecordClassRefIndex */
                        if ( freezeFrameIndex < nonObdFFDRecordNum )                                                                                                                /* [GUD:if] freezeFrameIndex */
                        {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                            checkOutputRecord = Dem_DataCtl_CheckOutputRecordByTrigger_FFD( eventStrgIndex, MisfireCylinderNumber, freezeFrameRecordTrigger );
                            if( checkOutputRecord == (boolean)TRUE )
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
                            {
                                /*--------------------------------------------------------------------------*/
                                /* Due to the processing structure, the value of numberOfSaveRecord         */
                                /* does not exceed the number of configs of FFD.                            */
                                /* Therefore, numberOfSaveRecord does not point to an element outside       */
                                /* the range of Dem_TmpRecordNumberByDTC.                                   */
                                Dem_TmpRecordNumberByDTC[numberOfSaveRecord].EventStrgIndex         = eventStrgIndex;                                               /* [GUD] numberOfSaveRecord */
                                Dem_TmpRecordNumberByDTC[numberOfSaveRecord].RecordNumber           = freezeFrameRecordNumber;                                      /* [GUD] numberOfSaveRecord */
                                Dem_TmpRecordNumberByDTC[numberOfSaveRecord].FreezeFrameDataIndex   = (Dem_u16_AllFFDIndexType)freezeFrameIndex;                    /* [GUD] numberOfSaveRecord */
                                Dem_TmpRecordNumberByDTC[numberOfSaveRecord].FreezeFrameDataType    = DEM_FFD_TYPE_NONOBDFFD;                                       /* [GUD] numberOfSaveRecord */
                                /*--------------------------------------------------------------------------*/

                                numberOfSaveRecord = numberOfSaveRecord + (Dem_u16_FFRecNumStoredIndexType)1U;

                                /*  range check : Dem_TmpRecordNumberByDTC[]        */
                                if ( numberOfSaveRecord >= tmpRecordNumberMaxNum )                                              /* [GUD:if] numberOfSaveRecord */
                                {
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }

        *NumberOfSaveRecordPtr = numberOfSaveRecord;
    }

    return;
}

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_SaveTSFFRecordNumberByDTCForFilteredRecord      */
/* Description   | Get the time-series FFD record number linked to DTC.     */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [in] MisfireCylinderNumber :                             */
/*               |        Cylinder Number.                                  */
/*               | [in/out] NumberOfSaveRecordPtr :                         */
/*               |        Total number of saved record numbers.             */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created. based on Dem_Data_SaveTSFFRecordNumberByDTC.*/
/*   v5-7-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_SaveTSFFRecordNumberByDTCForFilteredRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,      /* MISRA DEVIATION */
    P2VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC, AUTOMATIC ) NumberOfSaveRecordPtr
)
{
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC )         tsFFListIndex;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC )     tsFFRecClassRef;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC )         tsffTotalDTCNum;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC )   numberOfSaveRecord;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC )   numberOfSaveRecordForTriggerFFD;
    VAR( Dem_u08_TSFFClassIndexType, AUTOMATIC )        tsFFClassRef;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC )   tsffRecordClassNumPerDTCMaxNum;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC )   tsFFRecClassRefIndex;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC )        tsFFDRecCnt;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC )        startingRecordNumber;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC )        sumRecordNum;
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) dtcAttributePtr;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC )   tmpRecordNumberMaxNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC )        eventStrgIndex;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC )        freezeFrameRecordTrigger;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC )                           checkOutputRecord;
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC )            tsFreezeFrameIndex;
    VAR( Dem_u08_FFStoredStatusType, AUTOMATIC )        recordStatus;

    tmpRecordNumberMaxNum = Dem_TotalNumOfRecNumPerDTC;
    tsffRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;
    tsffTotalDTCNum = Dem_TSFFTotalDTCNum;
    numberOfSaveRecord = *NumberOfSaveRecordPtr;
    numberOfSaveRecordForTriggerFFD = numberOfSaveRecord;

    dtcAttributePtr =   Dem_CfgInfoPm_GetDTCAttrTablePtr_TSFF( EventStrgIndex );    /* [GUD:RET:Not NULL_PTR]dtcAttributePtr */

    if ( dtcAttributePtr != NULL_PTR )                                              /* [GUD:if]dtcAttributePtr */
    {
        if ( numberOfSaveRecord < tmpRecordNumberMaxNum )                                                                                                       /* [GUD:if] numberOfSaveRecord */
        {
            for( tsFFRecClassRefIndex = (Dem_u08_TSFFListPerDTCIndexType)0U; tsFFRecClassRefIndex < tsffRecordClassNumPerDTCMaxNum; tsFFRecClassRefIndex++ )    /* [GUD:for] tsFFRecClassRefIndex */
            {
                tsFFRecClassRef = dtcAttributePtr->DemTimeSeriesFreezeFrameRecordClassRef[tsFFRecClassRefIndex];                                                /* [GUD] dtcAttributePtr *//* [GUD] tsFFRecClassRefIndex *//* [ARYCHK] DEM_TSFF_RECORD_CLASS_NUM_PER_DTC_MAX_NUM / 1 / tsFFRecClassRefIndex */

                if( tsFFRecClassRef != DEM_TSFF_RECORD_CLASS_REF_INVALID )                                                                                      /* [GUD:if] tsFFRecClassRef */
                {
                    freezeFrameRecordTrigger = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemTimeSeriesFreezeFrameTrigger;                                       /* [GUD] tsFFRecClassRef */

                    tsFFListIndex = Dem_Data_GetDisabledTimeSeriesFreezeFrameListIndexForFilteredRecord( EventStrgIndex, tsFFRecClassRefIndex, freezeFrameRecordTrigger, numberOfSaveRecordForTriggerFFD, &eventStrgIndex );
                    if( tsFFListIndex < tsffTotalDTCNum )                                                                                                       /* [GUD:if] tsFFListIndex */
                    {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                        checkOutputRecord = Dem_DataCtl_CheckOutputRecordByTrigger_FFD( eventStrgIndex, MisfireCylinderNumber, freezeFrameRecordTrigger );
                        if( checkOutputRecord == (boolean)TRUE )
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
                        {
                            tsFFClassRef = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemTimeSeriesFreezeFrameClassRef;                                          /* [GUD] tsFFRecClassRef *//* [GUD:CFG:IF_GUARDED: tsFFRecClassRef ]tsFFClassRef */
                            startingRecordNumber = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemStartingRecordNumber;                                           /* [GUD] tsFFRecClassRef */
                            /* The value of sumRecordNum will be within the range of uint8. */
                            sumRecordNum = (Dem_u08_FFRecordNumberType)( Dem_TSFFClassTable[tsFFClassRef].DemNumberOfBeforeTriggeredRecord + Dem_TSFFClassTable[tsFFClassRef].DemNumberOfAfterTriggeredRecord );    /* [GUD] tsFFClassRef */
                            for( tsFFDRecCnt = (Dem_u08_FFRecordNumberType)0U; tsFFDRecCnt < sumRecordNum; tsFFDRecCnt++ )                                      /* [GUD:for] tsFFDRecCnt */
                            {
                                tsFreezeFrameIndex = Dem_TimeSeriesFreezeFrameTable[tsFFListIndex].DemStartIndex + (Dem_u16_TSFFDIndexType)tsFFDRecCnt;         /* [GUD] tsFFListIndex */
                                recordStatus = Dem_DataMngC_GetRecordStatusOfTimeSeriesFreezeFrameRecord( tsFreezeFrameIndex );
                                if( recordStatus == DEM_FFD_STORED )
                                {
                                    /*--------------------------------------------------------------------------*/
                                    /* Due to the processing structure, the value of numberOfSaveRecord         */
                                    /* does not exceed the number of configs of FFD.                            */
                                    /* Therefore, numberOfSaveRecord does not point to an element outside       */
                                    /* the range of Dem_TmpRecordNumberByDTC.                                   */
                                    Dem_TmpRecordNumberByDTC[numberOfSaveRecord].EventStrgIndex         = eventStrgIndex;                                                                   /* [GUD] numberOfSaveRecord */
                                    Dem_TmpRecordNumberByDTC[numberOfSaveRecord].RecordNumber           = (Dem_u08_FFRecordNumberType)( startingRecordNumber + tsFFDRecCnt );               /* [GUD] numberOfSaveRecord */
                                    Dem_TmpRecordNumberByDTC[numberOfSaveRecord].FreezeFrameDataIndex   = (Dem_u16_AllFFDIndexType)tsFreezeFrameIndex;                                      /* [GUD] numberOfSaveRecord */
                                    Dem_TmpRecordNumberByDTC[numberOfSaveRecord].FreezeFrameDataType    = DEM_FFD_TYPE_TSFFD;                                                               /* [GUD] numberOfSaveRecord */
                                    /*--------------------------------------------------------------------------*/

                                    numberOfSaveRecord = numberOfSaveRecord + (Dem_u16_FFRecNumStoredIndexType)1U;
                                    if ( numberOfSaveRecord >= tmpRecordNumberMaxNum )                                                                                  /* [GUD:if] numberOfSaveRecord */
                                    {
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }

                if ( numberOfSaveRecord >= tmpRecordNumberMaxNum )
                {
                    break;
                }
            }
        }
    }
    *NumberOfSaveRecordPtr = numberOfSaveRecord;

    return ;
}
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /*   ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
