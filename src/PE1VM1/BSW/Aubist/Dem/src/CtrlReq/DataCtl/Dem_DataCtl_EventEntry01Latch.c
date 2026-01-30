/* Dem_DataCtl_EventEntry01Latch_c(v5-10-0)                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_EventEntry01Latch/CODE                        */
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
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | no branch changed.                                       */
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

#if ( DEM_OBDONUDS_SUPPORT == STD_ON )   /*  [FuncSw]    */
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
    /*  initialize data.                */
    Dem_Misfire_SetObdRecordNumberIndexSyncStatus( (boolean)FALSE );
#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON ) */
#endif /* ( DEM_OBDONUDS_SUPPORT == STD_ON )             */


    return retVal;
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
/*   v5-7-0      | no object changed.                                       */
/*   v5-10-0     | no branch changed.                                       */
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
                        if ( faultRecordPtrCtl.FaultRecordPtr->RecordNumberIndex[loopRecordNumberIndex] != DEM_FFRECINDEX_INITIAL )                                 /* [GUD] loopRecordNumberIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / loopRecordNumberIndex */
                        {
                            freezeFrameRecordClassIndex = freezeFrameRecNumClassPtr->DemFreezeFrameRecordClassRef[loopRecordNumberIndex];                           /* [GUD] loopRecordNumberIndex *//* [ARYCHK] DEM_FF_RECORD_CLASS_REF_MAX_NUM / 1 / loopRecordNumberIndex */
                            if( freezeFrameRecordClassIndex < ffrRecordClassConfigureNum )                                                                          /* [GUD:if] freezeFrameRecordClassIndex */
                            {
                                freezeFrameRecordTrigger =  Dem_CfgInfoPm_GetFreezeFrameRecordTriggerType( freezeFrameRecordClassIndex );                           /* [GUD] freezeFrameRecordClassIndex */

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
/*   v5-8-0      | no branch changed.                                       */
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
    obdFFRClassPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();
    obdFFDRecordNum = Dem_CfgInfoPm_GetObdFFDRecordNum();

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
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
