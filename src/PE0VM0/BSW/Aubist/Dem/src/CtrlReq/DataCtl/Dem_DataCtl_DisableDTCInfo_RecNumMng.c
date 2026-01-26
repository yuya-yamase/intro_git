/* Dem_DataCtl_DisableDTCInfo_RecNumMng_c(v5-5-0)                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_DisableDTCInfo/CODE                           */
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

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/\

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( void, DEM_CODE ) Dem_Data_InitTmpCheckRecordData
( void );

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( boolean, DEM_CODE ) Dem_DataCtl_CheckOutputRecordByTrigger_OBDFFD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) Trigger
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )     */

static FUNC( boolean, DEM_CODE ) Dem_DataCtl_CheckOutputRecordByTrigger_FFD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) Trigger
);
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )       */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

VAR( Dem_TmpRecordNumberByDTCType, DEM_VAR_NO_INIT ) Dem_TmpRecordNumberByDTC[DEM_TOTAL_NUM_OF_RECNUM_PER_DTC];

static VAR( Dem_u16_FFRecNumStoredIndexType, DEM_VAR_NO_INIT ) Dem_SearchStartPositionIndex;

static VAR( Dem_TmpCheckRecordDataType, DEM_VAR_NO_INIT ) Dem_TmpCheckRecordData[DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM];
static VAR( Dem_u08_FFListIndexType, DEM_VAR_NO_INIT ) Dem_TmpCheckRecordDataNum;

static VAR( Dem_u32_FFDOutputTotalSizeType, DEM_VAR_NO_INIT ) Dem_SizeOfAllStoredFreezeFrame;


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Data_InitSaveTmpRecordNumber                         */
/* Description   | This function initializes Dem_TmpRecordNumberByDTC and   */
/*               | Dem_SearchStartPositionIndex.                            */
/* Preconditions |                                                          */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_InitSaveTmpRecordNumber
( void )
{
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) tmpRecordNumberMaxNum;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) arrayIndex;

    Dem_SearchStartPositionIndex = (Dem_u16_FFRecNumStoredIndexType)0U;

    tmpRecordNumberMaxNum = Dem_TotalNumOfRecNumPerDTC;

    for( arrayIndex = (Dem_u16_FFRecNumStoredIndexType)0U; arrayIndex < tmpRecordNumberMaxNum; arrayIndex++ )           /* [GUD:for]arrayIndex */
    {
        Dem_TmpRecordNumberByDTC[arrayIndex].EventStrgIndex        = DEM_EVENTSTRGINDEX_INVALID;                        /* [GUD]arrayIndex */
        Dem_TmpRecordNumberByDTC[arrayIndex].RecordNumber          = DEM_RECORDNUMBER_NEXT_NONE;                        /* [GUD]arrayIndex */
        Dem_TmpRecordNumberByDTC[arrayIndex].FreezeFrameDataIndex  = (Dem_u16_AllFFDIndexType)DEM_FFDINDEX_INVALID;     /* [GUD]arrayIndex */
        Dem_TmpRecordNumberByDTC[arrayIndex].FreezeFrameDataType   = DEM_FFD_TYPE_INVALID;                              /* [GUD]arrayIndex */
    }
    Dem_Data_InitTmpCheckRecordData();

    Dem_SizeOfAllStoredFreezeFrame = ( Dem_u32_FFDOutputTotalSizeType )0U;

    return;
}

/****************************************************************************/
/* Function Name | Dem_Data_ResetSearchStartPosition                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_ResetSearchStartPosition
( void )
{
    Dem_SearchStartPositionIndex = (Dem_u16_FFRecNumStoredIndexType)0U;

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Data_SortTmpRecordNumber                             */
/* Description   | sort record number.                                      */
/* Preconditions |                                                          */
/* Parameters    | [in] NumberOfSaveRecord :                                */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_SortTmpRecordNumber
(
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) NumberOfSaveRecord
)
{
    Dem_Data_SortSaveRecordNumber( NumberOfSaveRecord, &Dem_TmpRecordNumberByDTC[0] );

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Data_SaveObdRecordNumberByDTC                        */
/* Description   | Save RecordNumber where OBD FFD is stored.               */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [in] MisfireCylinderNumber :                             */
/*               |        Cylinder Number.                                  */
/*               | [in/out] FFDIndexListStPtr :                             */
/*               |        Dem_TmpDisabledRecord.FFDIndexListSt pointer.     */
/*               | [in/out] NumberOfSaveRecordPtr :                         */
/*               |        Total number of saved record numbers.             */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Data_SaveObdRecordNumberByDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,  /* MISRA DEVIATION */
    P2VAR( Dem_FaultRecordPartsFFDIndexListStType, AUTOMATIC, DEM_VAR_NO_INIT ) FFDIndexListStPtr,
    P2VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC, AUTOMATIC ) NumberOfSaveRecordPtr
)
{
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA )  freezeFrameRecNumClassPtr;
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecordClassType, AUTOMATIC, DEM_CONFIG_DATA )  freezeFrameRecordClassPtr;
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
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC )                                        freezeFrameRecordTrigger;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC )                                                           checkOutputRecord;
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )                                        resultOfGetObdFFData;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC )                                        storedObdFFEventStrgIndex;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC )                                        storedObdFFRecordNumber;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC )                                   storedObdFFDCount;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC )                                        sizeAtFFD;

    obdFFDRecordNum = Dem_ObdFFDRecordNum;
    Dem_CfgInfoPm_GetOBDFreezeFrameAndRecNumClass( EventStrgIndex, &obdFreezeFrameClassRef, &obdFreezeframeRecNumClassRef );                    /* [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] obdFreezeFrameClassRef *//* [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] obdFreezeframeRecNumClassRef */

    if ( obdFreezeframeRecNumClassRef != DEM_FFRECNUMCLASSINDEX_INVALID )                                                                       /* [GUD:if]obdFreezeframeRecNumClassRef */
    {
        /* Holds the FreezeFrameClass table pointed to by the FreezeFrameClass table list Index of the held DTCAttribute table. */
        freezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[obdFreezeframeRecNumClassRef];                                             /* [GUD]obdFreezeframeRecNumClassRef *//* [GUD:CFG:IF_GUARDED: obdFreezeframeRecNumClassRef ]freezeFrameRecNumClassPtr */

        numberOfSaveRecord          = *NumberOfSaveRecordPtr;
        tmpRecordNumberMaxNum = Dem_TotalNumOfRecNumPerDTC;

        if ( numberOfSaveRecord < tmpRecordNumberMaxNum )                                                                                               /* [GUD:if] numberOfSaveRecord */
        {
            storedObdFFDCount = ( Dem_u16_FFRecNumStoredIndexType )0U;
            storedObdFFEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
            storedObdFFRecordNumber = DEM_FFRECNUM_INVALID;

            Dem_CfgInfoPm_GetNumOfOBDFreezeFrameRecordClass( &ffrRecordClassConfigureNum, &obdFFRClassPerDTCMaxNum );

            for( freezeFrameRecordClassRefIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordClassRefIndex < obdFFRClassPerDTCMaxNum; freezeFrameRecordClassRefIndex++ )     /* [GUD:for] freezeFrameRecordClassRefIndex */
            {
                freezeFrameRecordClassIndex = freezeFrameRecNumClassPtr->DemFreezeFrameRecordClassRef[freezeFrameRecordClassRefIndex];                  /* [GUD]freezeFrameRecNumClassPtr *//* [GUD] freezeFrameRecordClassRefIndex */

                if( freezeFrameRecordClassIndex < ffrRecordClassConfigureNum )                                                                          /* [GUD:if] freezeFrameRecordClassIndex */
                {
                    /* Holds the FreezeFrameRecordClass table pointed to by DemFreezeFrameRecordIndex. */
                    freezeFrameRecordClassPtr = &Dem_FreezeFrameRecordClassTable[freezeFrameRecordClassIndex];                                          /* [GUD] freezeFrameRecordClassIndex *//* [GUD:CFG:IF_GUARDED: freezeFrameRecordClassIndex ]freezeFrameRecordClassPtr */
                    freezeFrameRecordTrigger = freezeFrameRecordClassPtr->DemFreezeFrameRecordTrigger;                                                  /* [GUD] freezeFrameRecordClassPtr */

                    freezeFrameIndex = Dem_Data_GetDisabledObdRecordNumberIndex( EventStrgIndex, freezeFrameRecordClassRefIndex, freezeFrameRecordTrigger, FFDIndexListStPtr, &eventStrgIndex );

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
                            Dem_TmpRecordNumberByDTC[numberOfSaveRecord].RecordNumber           = freezeFrameRecordClassPtr->DemFreezeFrameRecordNumber;    /* [GUD] numberOfSaveRecord *//* [GUD] freezeFrameRecordClassPtr */
                            Dem_TmpRecordNumberByDTC[numberOfSaveRecord].FreezeFrameDataIndex   = (Dem_u16_AllFFDIndexType)freezeFrameIndex;                /* [GUD] numberOfSaveRecord */
                            Dem_TmpRecordNumberByDTC[numberOfSaveRecord].FreezeFrameDataType    = DEM_FFD_TYPE_OBDFFD;                                      /* [GUD] numberOfSaveRecord */
                            /*--------------------------------------------------------------------------*/

                            storedObdFFDCount = storedObdFFDCount + ( Dem_u16_FFRecNumStoredIndexType )1U;
                            if ( storedObdFFRecordNumber == DEM_FFRECNUM_INVALID )
                            {
                                storedObdFFEventStrgIndex = Dem_TmpRecordNumberByDTC[numberOfSaveRecord].EventStrgIndex;                                    /* [GUD] numberOfSaveRecord */
                                storedObdFFRecordNumber = Dem_TmpRecordNumberByDTC[numberOfSaveRecord].RecordNumber;                                        /* [GUD] numberOfSaveRecord */
                            }

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

            if ( storedObdFFDCount > ( Dem_u16_FFRecNumStoredIndexType )0U )
            {
                sizeAtFFD = ( Dem_u16_FFDStoredIndexType )0U;
                resultOfGetObdFFData = Dem_Data_GetObdFreezeFrameData( storedObdFFEventStrgIndex, storedObdFFRecordNumber, DEM_FFDGETTYPE_SIZE, NULL_PTR, &sizeAtFFD );
                if ( resultOfGetObdFFData == DEM_IRT_OK )
                {
                    Dem_SizeOfAllStoredFreezeFrame = Dem_SizeOfAllStoredFreezeFrame + ( Dem_u32_FFDOutputTotalSizeType )( ( Dem_u32_FFDOutputTotalSizeType )storedObdFFDCount * ( Dem_u32_FFDOutputTotalSizeType )sizeAtFFD );/*  no wrap around      */
                }
            }
        }

        *NumberOfSaveRecordPtr = numberOfSaveRecord;
    }

    return;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

/****************************************************************************/
/* Function Name | Dem_Data_SaveRecordNumberByDTC                           */
/* Description   | Save RecordNumber where non-OBD FFD is stored.           */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [in/out] FFDIndexListStPtr :                             */
/*               |        Dem_TmpDisabledRecord.FFDIndexListSt pointer.     */
/*               | [in/out] NumberOfSaveRecordPtr :                         */
/*               |        Total number of saved record numbers.             */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_SaveRecordNumberByDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,      /* MISRA DEVIATION */
    P2VAR( Dem_FaultRecordPartsFFDIndexListStType, AUTOMATIC, DEM_VAR_NO_INIT ) FFDIndexListStPtr,
    P2VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC, AUTOMATIC ) NumberOfSaveRecordPtr
)
{
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA )  freezeFrameRecNumClassPtr;
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecordClassType, AUTOMATIC, DEM_CONFIG_DATA )  freezeFrameRecordClassPtr;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC )                                   tmpRecordNumberMaxNum;
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC )                                          freezeFrameClassRef;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC )                                    freezeframeRecNumClassRef;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC )                                   numberOfSaveRecord;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC )                                    freezeFrameRecordClassIndex;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC )                                    ffrRecordClassConfigureNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC )                                           freezeFrameRecordClassRefIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC )                                           nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC )                                        freezeFrameRecordTrigger;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC )                                              nonObdFFDRecordNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC )                                              freezeFrameIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC )                                        eventStrgIndex;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC )                                                           checkOutputRecord;
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )                                        resultOfGetFFData;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC )                                        storedFFEventStrgIndex;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC )                                        storedFFRecordNumber;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC )                                   storedFFDCount;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC )                                        sizeAtFFD;

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
            storedFFDCount = ( Dem_u16_FFRecNumStoredIndexType )0U;
            storedFFEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
            storedFFRecordNumber = DEM_FFRECNUM_INVALID;

            Dem_CfgInfoPm_GetNumOfFreezeFrameRecordClass( &ffrRecordClassConfigureNum, &nonOBDFFRClassPerDTCMaxNum );

            for( freezeFrameRecordClassRefIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordClassRefIndex < nonOBDFFRClassPerDTCMaxNum; freezeFrameRecordClassRefIndex++ )  /* [GUD:for] freezeFrameRecordClassRefIndex */
            {
                freezeFrameRecordClassIndex = freezeFrameRecNumClassPtr->DemFreezeFrameRecordClassRef[freezeFrameRecordClassRefIndex];                                          /* [GUD] freezeFrameRecordClassRefIndex */

                if( freezeFrameRecordClassIndex < ffrRecordClassConfigureNum )                                                                                                  /* [GUD:if] freezeFrameRecordClassIndex */
                {
                    /* Holds the FreezeFrameRecordClass table pointed to by DemFreezeFrameRecordIndex. */
                    freezeFrameRecordClassPtr = &Dem_FreezeFrameRecordClassTable[freezeFrameRecordClassIndex];                                                                  /* [GUD] freezeFrameRecordClassIndex *//* [GUD:CFG:IF_GUARDED: freezeFrameRecordClassIndex ]freezeFrameRecordClassPtr */
                    freezeFrameRecordTrigger = freezeFrameRecordClassPtr->DemFreezeFrameRecordTrigger;                                                                          /* [GUD] freezeFrameRecordClassPtr */

                    freezeFrameIndex = Dem_Data_GetDisabledRecordNumberIndex( EventStrgIndex, freezeFrameRecordClassRefIndex, freezeFrameRecordTrigger, FFDIndexListStPtr, &eventStrgIndex );   /* [GUD] freezeFrameRecordClassRefIndex */
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
                            Dem_TmpRecordNumberByDTC[numberOfSaveRecord].RecordNumber           = freezeFrameRecordClassPtr->DemFreezeFrameRecordNumber;        /* [GUD] numberOfSaveRecord */
                            Dem_TmpRecordNumberByDTC[numberOfSaveRecord].FreezeFrameDataIndex   = (Dem_u16_AllFFDIndexType)freezeFrameIndex;                    /* [GUD] numberOfSaveRecord */
                            Dem_TmpRecordNumberByDTC[numberOfSaveRecord].FreezeFrameDataType    = DEM_FFD_TYPE_NONOBDFFD;                                       /* [GUD] numberOfSaveRecord */
                            /*--------------------------------------------------------------------------*/

                            storedFFDCount = storedFFDCount + ( Dem_u16_FFRecNumStoredIndexType )1U;
                            if ( storedFFRecordNumber == DEM_FFRECNUM_INVALID )
                            {
                                storedFFEventStrgIndex = Dem_TmpRecordNumberByDTC[numberOfSaveRecord].EventStrgIndex;                                           /* [GUD] numberOfSaveRecord */
                                storedFFRecordNumber = Dem_TmpRecordNumberByDTC[numberOfSaveRecord].RecordNumber;                                               /* [GUD] numberOfSaveRecord */
                            }

                            numberOfSaveRecord = numberOfSaveRecord + (Dem_u16_FFRecNumStoredIndexType)1U;

                            if( Dem_TmpCheckRecordDataNum < nonOBDFFRClassPerDTCMaxNum )                                                                        /* [GUD:if] Dem_TmpCheckRecordDataNum */
                            {
                                Dem_TmpCheckRecordData[Dem_TmpCheckRecordDataNum].TriggerFFDIndex = freezeFrameIndex;                                           /* [GUD] Dem_TmpCheckRecordDataNum */
                                Dem_TmpCheckRecordData[Dem_TmpCheckRecordDataNum].TriggerFFDStorageTrigger = freezeFrameRecordTrigger;                          /* [GUD] Dem_TmpCheckRecordDataNum */
                                Dem_TmpCheckRecordData[Dem_TmpCheckRecordDataNum].TriggerFFDConsistencyId = Dem_FFDMng_GetFFDConsystencyId( freezeFrameIndex ); /* [GUD] Dem_TmpCheckRecordDataNum */
                                Dem_TmpCheckRecordData[Dem_TmpCheckRecordDataNum].TriggerFFDExistStatus = (boolean)TRUE;                                        /* [GUD] Dem_TmpCheckRecordDataNum */
                                Dem_TmpCheckRecordData[Dem_TmpCheckRecordDataNum].JudgeOutputTSFFDFlag = (boolean)TRUE;                                         /* [GUD] Dem_TmpCheckRecordDataNum */
                                Dem_TmpCheckRecordDataNum = Dem_TmpCheckRecordDataNum + (Dem_u08_FFListIndexType)1U;
                            }
                            /*  range check : Dem_TmpRecordNumberByDTC[]        */
                            if ( numberOfSaveRecord >= tmpRecordNumberMaxNum )                                              /* [GUD:if] numberOfSaveRecord */
                            {
                                break;
                            }
                        }
                    }
                }
            }

            if ( storedFFDCount > ( Dem_u16_FFRecNumStoredIndexType )0U )
            {
                sizeAtFFD = ( Dem_u16_FFDStoredIndexType )0U;
                resultOfGetFFData = Dem_Data_GetFreezeFrameData( storedFFEventStrgIndex, storedFFRecordNumber, DEM_FFDGETTYPE_SIZE, NULL_PTR, &sizeAtFFD );
                if ( resultOfGetFFData == DEM_IRT_OK )
                {
                    Dem_SizeOfAllStoredFreezeFrame = Dem_SizeOfAllStoredFreezeFrame + ( Dem_u32_FFDOutputTotalSizeType )( ( Dem_u32_FFDOutputTotalSizeType )storedFFDCount * ( Dem_u32_FFDOutputTotalSizeType )sizeAtFFD );/*  no wrap around      */
                }
            }
        }

        *NumberOfSaveRecordPtr = numberOfSaveRecord;
    }

    return;
}

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_SaveTSFFRecordNumberByDTC                       */
/* Description   | Get the time-series FFD record number linked to DTC.     */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [in/out] FFDIndexListStPtr :                             */
/*               |      Dem_TmpDisabledRecord.FaultRecord pointer.          */
/*               | [in/out] NumberOfSaveRecordPtr :                         */
/*               |        Total number of saved record numbers.             */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_SaveTSFFRecordNumberByDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,      /* MISRA DEVIATION */
    P2VAR( Dem_FaultRecordPartsFFDIndexListStType, AUTOMATIC, DEM_VAR_NO_INIT ) FFDIndexListStPtr,
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
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )        resultOfGetTSSFFData;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC )        storedTSFFEventStrgIndex;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC )        storedTSFFRecordNumber;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC )   storedTSFFCount;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC )        sizeAtFFD;

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
                tsFFRecClassRef = dtcAttributePtr->DemTimeSeriesFreezeFrameRecordClassRef[tsFFRecClassRefIndex];                                                /* [GUD] dtcAttributePtr *//* [GUD] tsFFRecClassRefIndex */

                if( tsFFRecClassRef != DEM_TSFF_RECORD_CLASS_REF_INVALID )                                                                                      /* [GUD:if] tsFFRecClassRef */
                {
                    freezeFrameRecordTrigger = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemTimeSeriesFreezeFrameTrigger;                                       /* [GUD] tsFFRecClassRef */

                    tsFFListIndex = Dem_Data_GetDisabledTimeSeriesFreezeFrameListIndex( EventStrgIndex, tsFFRecClassRefIndex, freezeFrameRecordTrigger, numberOfSaveRecordForTriggerFFD, FFDIndexListStPtr, &eventStrgIndex );
                    if( tsFFListIndex < tsffTotalDTCNum )                                                                                                       /* [GUD:if] tsFFListIndex */
                    {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                        checkOutputRecord = Dem_DataCtl_CheckOutputRecordByTrigger_FFD( eventStrgIndex, MisfireCylinderNumber, freezeFrameRecordTrigger );
                        if( checkOutputRecord == (boolean)TRUE )
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
                        {
                            storedTSFFCount = ( Dem_u16_FFRecNumStoredIndexType )0U;
                            storedTSFFEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
                            storedTSFFRecordNumber = DEM_FFRECNUM_INVALID;

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

                                    storedTSFFCount= storedTSFFCount + (Dem_u16_FFRecNumStoredIndexType)1U;
                                    if ( storedTSFFRecordNumber == DEM_FFRECNUM_INVALID )
                                    {
                                        storedTSFFEventStrgIndex = Dem_TmpRecordNumberByDTC[numberOfSaveRecord].EventStrgIndex;                                         /* [GUD] numberOfSaveRecord */
                                        storedTSFFRecordNumber = Dem_TmpRecordNumberByDTC[numberOfSaveRecord].RecordNumber;                                             /* [GUD] numberOfSaveRecord */
                                    }

                                    numberOfSaveRecord = numberOfSaveRecord + (Dem_u16_FFRecNumStoredIndexType)1U;
                                    if ( numberOfSaveRecord >= tmpRecordNumberMaxNum )                                                                                  /* [GUD:if] numberOfSaveRecord */
                                    {
                                        break;
                                    }
                                }
                            }

                            if ( storedTSFFCount > ( Dem_u16_FFRecNumStoredIndexType )0U )
                            {
                                sizeAtFFD = ( Dem_u16_FFDStoredIndexType )0U;
                                resultOfGetTSSFFData = Dem_Data_GetFFDataFromTSFF( storedTSFFEventStrgIndex, storedTSFFRecordNumber, DEM_FFDGETTYPE_SIZE, NULL_PTR, &sizeAtFFD );
                                if( resultOfGetTSSFFData == DEM_IRT_OK )
                                {
                                    Dem_SizeOfAllStoredFreezeFrame = Dem_SizeOfAllStoredFreezeFrame + ( Dem_u32_FFDOutputTotalSizeType )( ( Dem_u32_FFDOutputTotalSizeType )storedTSFFCount * ( Dem_u32_FFDOutputTotalSizeType )sizeAtFFD );/*  no wrap around      */
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


#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataCtl_CheckOutputRecordByTrigger_OBDFFD            */
/* Description   | Check if OBD FFD of the corresponding trigger is the ou- */
/*               | tput target.                                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex : Event index.                       */
/*               | [in] Trigger : Trigger that saved OBD FFD                */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : Output target                             */
/*               |        FALSE : Not output target                         */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_DataCtl_CheckOutputRecordByTrigger_OBDFFD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) Trigger
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNumberOutput;

    if ( MisfireCylinderNumber == DEM_MISFIRE_CYL_NUM_INVALID )
    {
        /*  it's normal DTC.            */
        /*  always output record.       */
        retVal  =   (boolean)TRUE;
    }
    else
    {
        /*  check misfire cylinder condition.       */
        retVal  =   Dem_Misfire_CheckOutputOBDFFDConditionByTrigger( EventStrgIndex, Trigger, &misfireCylinderNumberOutput );
        if ( retVal == (boolean)TRUE )
        {
            if ( MisfireCylinderNumber != misfireCylinderNumberOutput )
            {
                /*  mismatch cylinder number.       */
                retVal  =   (boolean)FALSE;
            }
        }
    }
    return retVal;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )     */

/****************************************************************************/
/* Function Name | Dem_DataCtl_CheckOutputRecordByTrigger_FFD               */
/* Description   | Check if OBD FFD of the corresponding trigger is the ou- */
/*               | tput target.                                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex : Event index.                       */
/*               | [in] Trigger : Trigger that saved FFD                    */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : Output target                             */
/*               |        FALSE : Not output target                         */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_DataCtl_CheckOutputRecordByTrigger_FFD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) Trigger
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNumberOutput;

    if ( MisfireCylinderNumber == DEM_MISFIRE_CYL_NUM_INVALID )
    {
        /*  it's normal DTC.            */
        /*  always output record.       */
        retVal  =   (boolean)TRUE;
    }
    else
    {
        /*  check misfire cylinder condition.       */
        retVal  =   Dem_Misfire_CheckOutputFFDConditionByTrigger( EventStrgIndex, Trigger, &misfireCylinderNumberOutput );
        if ( retVal == (boolean)TRUE )
        {
            if ( MisfireCylinderNumber != misfireCylinderNumberOutput )
            {
                /*  mismatch cylinder number.       */
                retVal  =   (boolean)FALSE;
            }
        }
    }
    return retVal;
}
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )   */


/****************************************************************************/
/* Function Name | Dem_Data_SearchTargetEventStrgIndexFromRecordNumber      */
/* Description   | Return EventStrg Index which has target record number.   */
/* Preconditions |                                                          */
/* Parameters    | [in] RecordNumber :                                      */
/*               |        The record number corresponding to the specified  */
/* Return Value  | Dem_u16_EventStrgIndexType                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_Data_SetNextRecordNumber.      */
/****************************************************************************/
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_Data_SearchTargetEventStrgIndexFromRecordNumber
(
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber
)
{
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC )    saveRecNumIndex;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC )    tmpRecordNumberMaxNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC )    eventStrgIndex;

    tmpRecordNumberMaxNum = Dem_TotalNumOfRecNumPerDTC;
    eventStrgIndex  =   DEM_EVENTSTRGINDEX_INVALID;

    for( saveRecNumIndex = Dem_SearchStartPositionIndex; saveRecNumIndex < tmpRecordNumberMaxNum; saveRecNumIndex++ )   /* [GUD:for] saveRecNumIndex */
    {
        if( RecordNumber == Dem_TmpRecordNumberByDTC[saveRecNumIndex].RecordNumber )                                    /* [GUD] saveRecNumIndex */
        {
            eventStrgIndex  = Dem_TmpRecordNumberByDTC[saveRecNumIndex].EventStrgIndex;                                 /* [GUD] saveRecNumIndex */
            Dem_SearchStartPositionIndex = saveRecNumIndex;
            break;
        }
    }

    return eventStrgIndex;
}


/****************************************************************************/
/* Function Name | Dem_Data_SetNextRecordNumber                             */
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
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_SetNextRecordNumber
(
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC )                 RecordNumber,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC )    NextRecordNumberPtr
)
{
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC )    saveRecNumIndex;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC )    tmpRecordNumberMaxNum;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC )    searchStartPositionIndex;

    tmpRecordNumberMaxNum = Dem_TotalNumOfRecNumPerDTC;

    searchStartPositionIndex = Dem_TotalNumOfRecNumPerDTC;

    *NextRecordNumberPtr = DEM_RECORDNUMBER_NEXT_NONE;

    for( saveRecNumIndex = Dem_SearchStartPositionIndex; saveRecNumIndex < tmpRecordNumberMaxNum; saveRecNumIndex++ )               /* [GUD:for] saveRecNumIndex */
    {
        if( RecordNumber < Dem_TmpRecordNumberByDTC[saveRecNumIndex].RecordNumber )                                                 /* [GUD] saveRecNumIndex */
        {
            *NextRecordNumberPtr = Dem_TmpRecordNumberByDTC[saveRecNumIndex].RecordNumber;                                          /* [GUD] saveRecNumIndex */
            searchStartPositionIndex = saveRecNumIndex;
            break;
        }
    }

    Dem_SearchStartPositionIndex = searchStartPositionIndex;

    return;
}


/****************************************************************************/
/* Function Name | Dem_Data_InitTmpCheckRecordData                          */
/* Description   | This function initializes Dem_TmpCheckRecordData and     */
/*               | Dem_TmpCheckRecordDataNum.                               */
/* Preconditions |                                                          */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_InitTmpCheckRecordData
( void )
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) arrayIndex;

    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;

    Dem_TmpCheckRecordDataNum = (Dem_u08_FFListIndexType)0U;

    for( arrayIndex = (Dem_u08_FFListIndexType)0U; arrayIndex < nonOBDFFRClassPerDTCMaxNum; arrayIndex++ )              /* [GUD:for] arrayIndex */
    {
        Dem_TmpCheckRecordData[arrayIndex].TriggerFFDIndex = DEM_FFRECINDEX_INITIAL;                                    /* [GUD] arrayIndex */
        Dem_TmpCheckRecordData[arrayIndex].TriggerFFDStorageTrigger = DEM_TRIGGER_ON_NONE;                              /* [GUD] arrayIndex */
        Dem_TmpCheckRecordData[arrayIndex].TriggerFFDConsistencyId = DEM_CONSISTENCY_INITIAL;                           /* [GUD] arrayIndex */
        Dem_TmpCheckRecordData[arrayIndex].StartRecordNumber = DEM_FFRECNUM_ALL_RECORDS;                                /* [GUD] arrayIndex */
        Dem_TmpCheckRecordData[arrayIndex].TriggerFFDExistStatus = (boolean)FALSE;                                      /* [GUD] arrayIndex */
        Dem_TmpCheckRecordData[arrayIndex].JudgeOutputTSFFDFlag = (boolean)FALSE;                                       /* [GUD] arrayIndex */
        Dem_TmpCheckRecordData[arrayIndex].AlreadyOutputBeforeTSFFDStatus = (boolean)FALSE;                             /* [GUD] arrayIndex */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Data_JudgeOutputFFDByFFDType                         */
/* Description   | Check Dem_TmpCheckRecordData.                            */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameDataType : Type of freeze frame record   */
/*               | [in] FreezeFrameRecordIndex : The freeze frame index co- */
/*               | rresponding to the specific freeze frame record.         */
/*               | [in] FreezeFrameRecordTrigger : TSFFD Stored Trigger     */
/*               | [in] ConsistencyId : Consistency Id                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Check OK                             */
/*               |        DEM_IRT_NG : Check NG                             */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_JudgeOutputFFDByFFDType
(
    VAR( Dem_u08_FreezeFrameDataType, AUTOMATIC ) FreezeFrameDataType,
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameRecordIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) arrayIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;


    if( FreezeFrameDataType == DEM_FFD_TYPE_NONOBDFFD )
    {
        for( arrayIndex = (Dem_u08_FFListIndexType)0U; arrayIndex < Dem_TmpCheckRecordDataNum; arrayIndex++ )               /* [GUD:for] arrayIndex */
        {
            if( Dem_TmpCheckRecordData[arrayIndex].TriggerFFDIndex == FreezeFrameRecordIndex )                              /* [GUD] arrayIndex */
            {
                if( Dem_TmpCheckRecordData[arrayIndex].TriggerFFDConsistencyId == ConsistencyId )                           /* [GUD] arrayIndex */
                {
                    retVal = DEM_IRT_OK;
                    break;
                }
            }
        }
    }
    else if( FreezeFrameDataType == DEM_FFD_TYPE_TSFFD )
    {
        for( arrayIndex = (Dem_u08_FFListIndexType)0U; arrayIndex < Dem_TmpCheckRecordDataNum; arrayIndex++ )               /* [GUD:for] arrayIndex */
        {
            if( Dem_TmpCheckRecordData[arrayIndex].TriggerFFDStorageTrigger == FreezeFrameRecordTrigger )                   /* [GUD] arrayIndex */
            {
                if( Dem_TmpCheckRecordData[arrayIndex].TriggerFFDExistStatus == (boolean)TRUE )                             /* [GUD] arrayIndex */
                {
                    if( Dem_TmpCheckRecordData[arrayIndex].TriggerFFDConsistencyId == ConsistencyId )                       /* [GUD] arrayIndex */
                    {
                        if( Dem_TmpCheckRecordData[arrayIndex].JudgeOutputTSFFDFlag == (boolean)TRUE )                      /* [GUD] arrayIndex */
                        {
                            retVal = DEM_IRT_OK;
                            break;
                        }
                    }
                }
            }
        }
    }
    else
    {
        /* DEM_FFD_TYPE_OBDFFD */
        retVal = DEM_IRT_OK;
    }

    return retVal;
}


#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_StopOutputTSFFDAfterTriggerFFD                  */
/* Description   | Stop the output of TSFFD after trigger FFD               */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameRecordIndex : The freeze frame index co- */
/*               | rresponding to the specific freeze frame record.         */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_StopOutputTSFFDAfterTriggerFFD
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameRecordIndex
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) arrayIndex;

    for( arrayIndex = (Dem_u08_FFListIndexType)0U; arrayIndex < Dem_TmpCheckRecordDataNum; arrayIndex++ )               /* [GUD:for] arrayIndex */
    {
        if( Dem_TmpCheckRecordData[arrayIndex].TriggerFFDIndex == FreezeFrameRecordIndex )                              /* [GUD] arrayIndex */
        {
            Dem_TmpCheckRecordData[arrayIndex].TriggerFFDExistStatus = (boolean)FALSE;                                  /* [GUD] arrayIndex */
            break;
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Data_StartOutputTSFFDAfterTSFFD                      */
/* Description   | Start the output of TSFFD after TSFFD                    */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameRecordTrigger : TSFFD Stored Trigger     */
/*               | [in] StartingRecordNumber : TSFFD start record number    */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_StartOutputTSFFDAfterTSFFD
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) StartingRecordNumber
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) arrayIndex;

    for( arrayIndex = (Dem_u08_FFListIndexType)0U; arrayIndex < Dem_TmpCheckRecordDataNum; arrayIndex++ )               /* [GUD:for] arrayIndex */
    {
        if( Dem_TmpCheckRecordData[arrayIndex].TriggerFFDStorageTrigger == FreezeFrameRecordTrigger )                   /* [GUD] arrayIndex */
        {
            if( Dem_TmpCheckRecordData[arrayIndex].StartRecordNumber != StartingRecordNumber )                          /* [GUD] arrayIndex */
            {
                Dem_TmpCheckRecordData[arrayIndex].StartRecordNumber = StartingRecordNumber;                            /* [GUD] arrayIndex */
                Dem_TmpCheckRecordData[arrayIndex].JudgeOutputTSFFDFlag = (boolean)TRUE;                                /* [GUD] arrayIndex */
                Dem_TmpCheckRecordData[arrayIndex].AlreadyOutputBeforeTSFFDStatus = (boolean)FALSE;                     /* [GUD] arrayIndex */
            }
        }
        /* In case of TSFFD, there may be multiple data of the same trigger, so continue the loop */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Data_StopOutputTSFFDAfterTSFFD                       */
/* Description   | Stop the output of TSFFD after TSFFD                     */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameRecordTrigger : TSFFD Stored Trigger     */
/*               | [in] BeforeTSFFDFlag : Whether it is before TSFFD        */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_StopOutputTSFFDAfterTSFFD
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
    VAR( boolean, AUTOMATIC ) BeforeTSFFDFlag
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) arrayIndex;

    for( arrayIndex = (Dem_u08_FFListIndexType)0U; arrayIndex < Dem_TmpCheckRecordDataNum; arrayIndex++ )               /* [GUD:for] arrayIndex */
    {
        if( Dem_TmpCheckRecordData[arrayIndex].TriggerFFDStorageTrigger == FreezeFrameRecordTrigger )                   /* [GUD] arrayIndex */
        {
            if( BeforeTSFFDFlag == (boolean)TRUE )
            {
                if( Dem_TmpCheckRecordData[arrayIndex].AlreadyOutputBeforeTSFFDStatus == (boolean)TRUE )                /* [GUD] arrayIndex */
                {
                    Dem_TmpCheckRecordData[arrayIndex].JudgeOutputTSFFDFlag = (boolean)FALSE;                           /* [GUD] arrayIndex */
                }
            }
            else
            {
                Dem_TmpCheckRecordData[arrayIndex].JudgeOutputTSFFDFlag = (boolean)FALSE;                               /* [GUD] arrayIndex */
            }
        }
        /* In case of TSFFD, there may be multiple data of the same trigger, so continue the loop */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Data_SetAlreadyOutputBeforeTSFFDStatus               */
/* Description   | Set AlreadyOutputBeforeTSFFDStatus                       */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameRecordTrigger : TSFFD Stored Trigger     */
/*               | [in] BeforeTSFFDFlag : Whether it is before TSFFD        */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_SetAlreadyOutputBeforeTSFFDStatus
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
    VAR( boolean, AUTOMATIC ) BeforeTSFFDFlag
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) arrayIndex;

    if( BeforeTSFFDFlag == (boolean)TRUE )
    {
        for( arrayIndex = (Dem_u08_FFListIndexType)0U; arrayIndex < Dem_TmpCheckRecordDataNum; arrayIndex++ )               /* [GUD:for] arrayIndex */
        {
            if( Dem_TmpCheckRecordData[arrayIndex].TriggerFFDStorageTrigger == FreezeFrameRecordTrigger )                   /* [GUD] arrayIndex */
            {
                Dem_TmpCheckRecordData[arrayIndex].AlreadyOutputBeforeTSFFDStatus = (boolean)TRUE;                          /* [GUD] arrayIndex */
            }
            /* In case of TSFFD, there may be multiple data of the same trigger, so continue the loop */
        }
    }

    return;
}
#endif  /* (DEM_TSFF_PM_SUPPORT == STD_ON) */

/****************************************************************************/
/* Function Name | Dem_Data_GetSizeOfAllStoredFreezeFrame                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | void                                                     */
/* Return Value  | Dem_u32_FFDOutputTotalSizeType                           */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u32_FFDOutputTotalSizeType, DEM_CODE ) Dem_Data_GetSizeOfAllStoredFreezeFrame
( void )
{
    VAR( Dem_u32_FFDOutputTotalSizeType, AUTOMATIC ) sizeOfAllStoredFreezeFrame;

    sizeOfAllStoredFreezeFrame = Dem_SizeOfAllStoredFreezeFrame;

    return sizeOfAllStoredFreezeFrame;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
