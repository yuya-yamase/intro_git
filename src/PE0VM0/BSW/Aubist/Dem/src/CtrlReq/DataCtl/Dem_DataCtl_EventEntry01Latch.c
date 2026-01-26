/* Dem_DataCtl_EventEntry01Latch_c(v5-5-0)                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_Dem_DataCtl_EventEntry01Latch/CODE            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Pm_Similar.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "Dem_DataCtl_local.h"
#include "Dem_DataCtl_EventEntry_local.h"

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

static FUNC( void, DEM_CODE ) Dem_Data_InitTmpMemoryWithoutRecord
( void );

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_InitResultOfComparingObdFFRecords
( void );
#endif /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

static FUNC( void, DEM_CODE ) Dem_Data_InitResultOfComparingFFRecords
( void );

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SaveFreezeFrameRecordToTmp
( void );

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SaveObdFreezeFrameRecordToTmp
( void );
#endif /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SaveNonObdFreezeFrameRecordToTmp
( void );

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_SaveReachedUpperLimitFFDTriggerToTmp
( void );
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */

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
/* Function Name | Dem_Data_SaveEventMemoryEntry                            */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SaveEventMemoryEntry
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetEventRec;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultRec;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfSaveFFRec;

    retVal = DEM_IRT_OK;
    resultOfGetFaultRec = DEM_IRT_NG;

    Dem_Data_InitTmpMemoryWithoutRecord();

    Dem_TmpEventMemoryEntry.EventStrgIndex = EventStrgIndex;

    resultOfGetEventRec = Dem_DataMngC_GetEventRecord( EventStrgIndex, &Dem_TmpEventMemoryEntry.EventRecord );

    if( resultOfGetEventRec == DEM_IRT_OK )
    {
        if( Dem_TmpEventMemoryEntry.EventRecord.FaultIndex != DEM_FAULTINDEX_INITIAL )
        {
            resultOfGetFaultRec = Dem_DataMngC_GetFaultRecord( Dem_TmpEventMemoryEntry.EventRecord.FaultIndex, &Dem_TmpEventMemoryEntry.FaultRecord );

            if( resultOfGetFaultRec != DEM_IRT_OK )
            {
                retVal = DEM_IRT_NG;
            }
            else
            {
                /* no processing. */
            }
        }
        else
        {
            Dem_DataMngC_InitFaultCtlRecordData( &Dem_TmpEventMemoryEntry.FaultRecord );
        }

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) /* [FuncSw] */
        Dem_Data_SaveReachedUpperLimitFFDTriggerToTmp();
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */
    }
    else
    {
        retVal = DEM_IRT_NG;
    }

    if( resultOfGetFaultRec == DEM_IRT_OK )
    {
        resultOfSaveFFRec = Dem_Data_SaveFreezeFrameRecordToTmp();

        if( resultOfSaveFFRec != DEM_IRT_OK )
        {
            retVal = DEM_IRT_NG;
        }
        else
        {
            /* no processing. */
        }
    }
    else
    {
        /* no processing. */
    }

    if( retVal == DEM_IRT_OK )
    {
        Dem_DataMngC_GetEventMemoryRecord( &Dem_TmpEventMemoryEntry.EventMemoryRecordList );

        /* Saves the number of event memory entries before being updated. */
        Dem_TmpEventMemoryEntry.BeforeNumberOfEventMemoryEntries = Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfEventMemoryEntries;
        Dem_TmpEventMemoryEntry.BeforeNumberOfConfirmedDTCs      = Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfConfirmedDTCs;
        Dem_TmpEventMemoryEntry.BeforeNumberOfObdMILDTCs         = Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfObdMILDTCs;
    }
    else
    {
        /* no processing. */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Data_InitTmpMemoryWithoutRecord                      */
/* Description   | Initialization of temporary event memory entries.        */
/*               | (excluding records)                                      */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*               |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_InitTmpMemoryWithoutRecord
( void )
{
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /* [FuncSw] */
    /* Initializes the freeze frame record list for OBD. */
    Dem_Data_InitResultOfComparingObdFFRecords();
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

    /* Initializes the freeze frame record list for non-OBD. */
    Dem_Data_InitResultOfComparingFFRecords();

    /* Initializes the event index. */
    Dem_TmpEventMemoryEntry.EventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;

    /* Initializes the trigger of event. */
    Dem_TmpEventMemoryEntry.Trigger = DEM_VALID_TRIGGER_NONE;

    /* Initializes the number of event memory entries before being updated. */
    Dem_TmpEventMemoryEntry.BeforeNumberOfEventMemoryEntries = DEM_NUMOFEVTMEMENT_INITIAL;
    Dem_TmpEventMemoryEntry.BeforeNumberOfConfirmedDTCs      = DEM_NUMOFEVTMEMENT_INITIAL;
    Dem_TmpEventMemoryEntry.BeforeNumberOfObdMILDTCs         = DEM_NUMOFEVTMEMENT_INITIAL;

    /* Initializes the result of retrieving of registering fault location. */
    Dem_TmpEventMemoryEntry.ResultOfGetFaultRegistLocation          = DEM_IRT_NG;
    Dem_TmpEventMemoryEntry.ResultOfGetConfirmedFaultRegistLocation = DEM_IRT_NG;
    Dem_TmpEventMemoryEntry.ResultOfGetMILFaultRegistLocation       = DEM_IRT_NG;

    /* Initializes the result of comparing each records with no differences. */
    Dem_TmpEventMemoryEntry.ResultOfComparingEventRecords  = DEM_IRT_OK;
    Dem_TmpEventMemoryEntry.ResultOfComparingFaultRecords  = DEM_IRT_OK;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    Dem_Misfire_InitCompareResultMisfireRecord();
    Dem_Misfire_InitCompareResultMisfireComRecord();
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )   */

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    Dem_Similar_InitCompareResult();
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */

    Dem_TmpEventMemoryEntry.ConsistencyIdUpdatedFlg = (boolean)FALSE;

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    /* [FuncSw] */
    Dem_Data_InitFaultRecordOverwrite();
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )  /* [FuncSw] */
    Dem_TmpUpperLimitReachedTrigger = DEM_VALID_TRIGGER_NONE;
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */

    return;
}


/****************************************************************************/
/* Function Name | Dem_Data_InitResultOfComparingObdFFRecords               */
/* Description   | Initialization of result of comparing freeze frame reco- */
/*               | rds for OBD in temporary event memory entries.           */
/*               | (excluding records)                                      */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*               |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_InitResultOfComparingObdFFRecords
( void )
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;

    obdFFRClassPerDTCMaxNum = Dem_OBDFFRClassPerDTCMaxNum;

    /* Initializes the freeze frame record list. */
    for( freezeFrameRecordIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordIndex < obdFFRClassPerDTCMaxNum; freezeFrameRecordIndex++ )         /* [GUD:for]freezeFrameRecordIndex */
    {
        /* Initializes the result of comparing freeze frame records with no differences. */
        Dem_TmpEventMemoryEntry.ResultOfComparingObdFFRecords[freezeFrameRecordIndex] = DEM_IRT_OK;                                                 /* [GUD]freezeFrameRecordIndex */
    }

    return;
}
#endif /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_Data_InitResultOfComparingFFRecords                  */
/* Description   | Initialization of result of comparing freeze frame reco- */
/*               | rds for non-OBD in temporary event memory entries.       */
/*               | (excluding records)                                      */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*               |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_InitResultOfComparingFFRecords
( void )
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;

    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;

    /* Initializes the freeze frame record list. */
    for( freezeFrameRecordIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordIndex < nonOBDFFRClassPerDTCMaxNum; freezeFrameRecordIndex++ )      /* [GUD:for]freezeFrameRecordIndex */
    {
        /* Initializes the result of comparing freeze frame records with no differences. */
        Dem_TmpEventMemoryEntry.ResultOfComparingFFRecords[freezeFrameRecordIndex] = DEM_IRT_OK;                                                    /* [GUD]freezeFrameRecordIndex */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Data_SaveFreezeFrameRecordToTmp                      */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SaveFreezeFrameRecordToTmp
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfSaveObdFFRec;
#endif /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfSaveNoObdFFRec;

    retVal = DEM_IRT_OK;


#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */

    resultOfSaveObdFFRec = Dem_Data_SaveObdFreezeFrameRecordToTmp();

    if( resultOfSaveObdFFRec != DEM_IRT_OK )
    {
        retVal = DEM_IRT_NG;
    }
    else
    {
        /* no processing. */
    }
#endif /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

    resultOfSaveNoObdFFRec = Dem_Data_SaveNonObdFreezeFrameRecordToTmp();

    if( resultOfSaveNoObdFFRec != DEM_IRT_OK )
    {
        retVal = DEM_IRT_NG;
    }
    else
    {
        /* no processing. */
    }

    return retVal;
}

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_SaveReachedUpperLimitFFDTriggerToTmp           */
/* Description   | store reached upper limit trigger to tmp                 */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_SaveReachedUpperLimitFFDTriggerToTmp
( void )
{
    VAR( Dem_u08_MaxNumberOfFreezeFrameTriggerType, AUTOMATIC ) maxNumberOfFreezeFrameTriggerConfirmed;
    VAR( Dem_u08_MaxNumberOfFreezeFrameTriggerType, AUTOMATIC ) maxNumberOfFreezeFrameTriggerFDCThreshold;
    VAR( Dem_u08_MaxNumberOfFreezeFrameTriggerType, AUTOMATIC ) maxNumberOfFreezeFrameTriggerPending;
    VAR( Dem_u08_MaxNumberOfFreezeFrameTriggerType, AUTOMATIC ) maxNumberOfFreezeFrameTriggerTFTOC;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) loopFaultIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( uint8, AUTOMATIC) numberOfConfirmedTrigger;
    VAR( uint8, AUTOMATIC) numberOfFDCThresholdTrigger;
    VAR( uint8, AUTOMATIC) numberOfPendingTrigger;
    VAR( uint8, AUTOMATIC) numberOfTFTOCTrigger;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) loopRecordNumberIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetFaultRecord;

    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) freezeFrameRecordTrigger;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) freezeFrameRecordClassIndex;
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) freezeFrameClassRef;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) freezeFrameRecNumClassRef;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) ffrRecordClassConfigureNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_FaultRecordPtrForCtlType, AUTOMATIC ) faultRecordPtrCtl;

    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecNumClassPtr;
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecordClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecordClassPtr;


    maxNumberOfFreezeFrameTriggerConfirmed    = Dem_MaxNumberOfFreezeFrameTriggerConfirmed;
    maxNumberOfFreezeFrameTriggerFDCThreshold = Dem_MaxNumberOfFreezeFrameTriggerFDCThreshold;
    maxNumberOfFreezeFrameTriggerPending      = Dem_MaxNumberOfFreezeFrameTriggerPending;
    maxNumberOfFreezeFrameTriggerTFTOC        = Dem_MaxNumberOfFreezeFrameTriggerTFTOC;

    numberOfConfirmedTrigger    = (uint8)0U;
    numberOfFDCThresholdTrigger = (uint8)0U;
    numberOfPendingTrigger      = (uint8)0U;
    numberOfTFTOCTrigger        = (uint8)0U;

    failRecordNum               = (Dem_u08_OrderIndexType)Dem_FailRecordNum;
    nonOBDFFRClassPerDTCMaxNum  = Dem_NonOBDFFRClassPerDTCMaxNum;
    ffrRecordClassConfigureNum  = Dem_FFRRecordClassConfigureNum;
    eventStorageNum             = Dem_PrimaryMemEventStorageNum;

    for( loopFaultIndex = (Dem_u08_OrderIndexType)0U; loopFaultIndex < failRecordNum; loopFaultIndex++ )                    /* [GUD:for]loopFaultIndex */
    {
        /* Use FaultIndex to get FaultRecord from FaultRecordList */
        retGetFaultRecord = Dem_DataMngC_GetFaultRecordAddress_MaxNumOfFFRTrigger( loopFaultIndex, &faultRecordPtrCtl );
        if ( retGetFaultRecord == DEM_IRT_OK )
        {
            if ( faultRecordPtrCtl.FaultRecordPtr->EventStrgIndex < eventStorageNum )
            {
                Dem_CfgInfoPm_GetFreezeFrameAndRecNumClass( faultRecordPtrCtl.FaultRecordPtr->EventStrgIndex, &freezeFrameClassRef, &freezeFrameRecNumClassRef);    /* [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] freezeFrameClassRef *//* [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] freezeframeRecNumClassRef */

                if( freezeFrameRecNumClassRef != DEM_FFRECNUMCLASSINDEX_INVALID )                                                                                   /* [GUD:if] freezeFrameRecNumClassRef */
                {
                    freezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[freezeFrameRecNumClassRef];                                                        /* [GUD] freezeFrameRecNumClassRef */

                    for ( loopRecordNumberIndex = (Dem_u08_FFListIndexType)0U; loopRecordNumberIndex < nonOBDFFRClassPerDTCMaxNum; loopRecordNumberIndex++ )        /* [GUD:for] loopRecordNumberIndex */
                    {
                        if ( faultRecordPtrCtl.FaultRecordPtr->RecordNumberIndex[loopRecordNumberIndex] != DEM_FFRECINDEX_INITIAL )                                 /* [GUD] loopRecordNumberIndex */
                        {
                            freezeFrameRecordClassIndex = freezeFrameRecNumClassPtr->DemFreezeFrameRecordClassRef[loopRecordNumberIndex];                           /* [GUD] loopRecordNumberIndex */
                            if( freezeFrameRecordClassIndex < ffrRecordClassConfigureNum )                                                                          /* [GUD:if] freezeFrameRecordClassIndex */
                            {
                                freezeFrameRecordClassPtr = &Dem_FreezeFrameRecordClassTable[freezeFrameRecordClassIndex];                                          /* [GUD] freezeFrameRecordClassIndex *//* [GUD:CFG:IF_GUARDED: freezeFrameRecordClassIndex ]freezeFrameRecordClassPtr */
                                freezeFrameRecordTrigger = freezeFrameRecordClassPtr->DemFreezeFrameRecordTrigger;                                                  /* [GUD] freezeFrameRecordClassPtr */

                                if ( freezeFrameRecordTrigger == DEM_TRIGGER_ON_CONFIRMED )
                                {
                                    numberOfConfirmedTrigger = numberOfConfirmedTrigger + (uint8)1U;
                                }
                                else if ( freezeFrameRecordTrigger == DEM_TRIGGER_ON_FDC_THRESHOLD )
                                {
                                    numberOfFDCThresholdTrigger = numberOfFDCThresholdTrigger + (uint8)1U;
                                }
                                else if ( freezeFrameRecordTrigger == DEM_TRIGGER_ON_PENDING )
                                {
                                    numberOfPendingTrigger = numberOfPendingTrigger + (uint8)1U;
                                }
                                else if ( freezeFrameRecordTrigger == DEM_TRIGGER_ON_TEST_FAILED_THIS_OPERATION_CYCLE )
                                {
                                    numberOfTFTOCTrigger = numberOfTFTOCTrigger + (uint8)1U;
                                }
                                else
                                {
                                    /* No Process */
                                }

                            }
                        }
                    }
                }
            }
        }
    }

    /* judge */
    if ( numberOfConfirmedTrigger >= maxNumberOfFreezeFrameTriggerConfirmed )
    {
        Dem_TmpUpperLimitReachedTrigger |= DEM_VALID_TRIGGER_CONFIRMED;
    }
    if ( numberOfFDCThresholdTrigger >= maxNumberOfFreezeFrameTriggerFDCThreshold )
    {
        Dem_TmpUpperLimitReachedTrigger |= DEM_VALID_TRIGGER_FDC_THRESHOLD;
    }
    if ( numberOfPendingTrigger >= maxNumberOfFreezeFrameTriggerPending )
    {
        Dem_TmpUpperLimitReachedTrigger |= DEM_VALID_TRIGGER_PENDING;
    }
    if ( numberOfTFTOCTrigger >= maxNumberOfFreezeFrameTriggerTFTOC )
    {
        Dem_TmpUpperLimitReachedTrigger |= DEM_VALID_TRIGGER_TFTOC;
    }

    return;
}
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */


#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_SaveObdFreezeFrameRecordToTmp                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SaveObdFreezeFrameRecordToTmp
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFFRec;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordIndex;
    VAR( Dem_u08_FFDIndexType , AUTOMATIC ) recordNumberIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;

    retVal = DEM_IRT_OK;
    obdFFRClassPerDTCMaxNum = Dem_OBDFFRClassPerDTCMaxNum;
    obdFFDRecordNum = Dem_ObdFFDRecordNum;

    for( freezeFrameRecordIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordIndex < obdFFRClassPerDTCMaxNum; freezeFrameRecordIndex++ )             /* [GUD:for]freezeFrameRecordIndex */
    {
        recordNumberIndex = Dem_TmpEventMemoryEntry.FaultRecord.ObdRecordNumberIndex[freezeFrameRecordIndex];                                           /* [GUD]freezeFrameRecordIndex */

        if( recordNumberIndex < obdFFDRecordNum )                                                                                                       /* [GUD:if]recordNumberIndex */
        {
            /* Gets FaultIndex of the specified index for OBD FreezeFrameRecord. */
            resultOfGetFFRec = Dem_DataMngC_GetObdFFR_MngInfo( recordNumberIndex, &Dem_TmpEventMemoryEntry.ObdFreezeFrameRecordList[freezeFrameRecordIndex] );  /* [GUD]freezeFrameRecordIndex */

            if( resultOfGetFFRec != DEM_IRT_OK )
            {
                retVal = DEM_IRT_NG;

                break;
            }
            else
            {
                /* no processing. */
            }
        }
        else
        {
            /* no processing. */
        }
    }

    return retVal;
}
#endif /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_Data_SaveNonObdFreezeFrameRecordToTmp                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SaveNonObdFreezeFrameRecordToTmp
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFFRec;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordIndex;
    VAR( Dem_u08_FFDIndexType , AUTOMATIC ) recordNumberIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;

    retVal = DEM_IRT_OK;
    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;
    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;

    for( freezeFrameRecordIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordIndex < nonOBDFFRClassPerDTCMaxNum; freezeFrameRecordIndex++ )          /* [GUD:for]freezeFrameRecordIndex */
    {
        recordNumberIndex = Dem_TmpEventMemoryEntry.FaultRecord.RecordNumberIndex[freezeFrameRecordIndex];                                              /* [GUD]freezeFrameRecordIndex */

        if( recordNumberIndex < nonObdFFDRecordNum )                                                                                                    /* [GUD:if]recordNumberIndex */
        {
            /* Gets FaultIndex of the specified index for non-OBD FreezeFrameRecord. */
            resultOfGetFFRec = Dem_DataMngC_GetFFR_MngInfo( recordNumberIndex, &Dem_TmpEventMemoryEntry.FreezeFrameRecordList[freezeFrameRecordIndex] );    /* [GUD]freezeFrameRecordIndex */

            if( resultOfGetFFRec != DEM_IRT_OK )
            {
                retVal = DEM_IRT_NG;

                break;
            }
            else
            {
                /* no processing. */
            }
        }
        else
        {
            /* no processing. */
        }
    }

    return retVal;
}



#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
