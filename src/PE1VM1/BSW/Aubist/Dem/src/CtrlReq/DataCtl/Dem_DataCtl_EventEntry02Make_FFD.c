/* Dem_DataCtl_EventEntry02Make_FFD_c(v5-10-0)                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_EventEntry02Make_FFD/CODE                     */
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
#include "../../../inc/Dem_Pm_DataEeo.h"
#include "../../../inc/Dem_Pm_PreFFD.h"
#include "../../../inc/Dem_Utl.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_DataCtl_CaptureFreezeFrameClass.h"
#include "../../../inc/Dem_CmnLib_DataCtl_TSFFD.h"
#include "Dem_DataCtl_EventEntry_local.h"
#include "Dem_DataCtl_local.h"
#include "Dem_DataCtl_TSFFD_local.h"

#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
#include <Dem_SIT_RangeCheck.h>
#endif  /* DEM_SIT_RANGE_CHECK */

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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_JudgeNeedToStoreFreezeFrame
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

static FUNC( boolean, DEM_CODE ) Dem_Data_CheckAlreadyFFRStoredOfTmp
( void );

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_JudgeNeedToStoreFreezeFrameByDisplacement
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( boolean, AUTOMATIC ) AllObdDTCFreezeFlag
);

static FUNC( void, DEM_CODE ) Dem_Data_CaptureFreezeFrameToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) Trigger,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
);

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_CaptureObdFreezeFrameToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MonitorDataType, AUTOMATIC )    monitorData0,
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) Trigger,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SetObdFFRecordIndexToTmp
(
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,
    VAR( Dem_u08_UpdateRecordType, AUTOMATIC ) FreezeFrameRecordUpdate,
    VAR( boolean, AUTOMATIC ) UpdatePendingFFD,
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) Trigger,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) CaptureFlgPtr
);

static FUNC( void, DEM_CODE ) Dem_Data_CaptureObdFreezeFrameDataToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MonitorDataType, AUTOMATIC )    monitorData0,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameClassPtr,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder,
    VAR( boolean, AUTOMATIC ) CaptureFlg
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SetOBDFFROverwritten
(
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

static FUNC( void, DEM_CODE ) Dem_Data_CaptureNonObdFreezeFrameToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) Trigger,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SetFFRecordIndexToTmp
(
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,
    VAR( Dem_u08_UpdateRecordType, AUTOMATIC ) FreezeFrameRecordUpdate,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger
);

static FUNC( void, DEM_CODE ) Dem_Data_CaptureFreezeFrameDataToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameClassPtr,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SetNonOBDFFROverwritten
(
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
    VAR( boolean, AUTOMATIC ) UpperLimitIsReached
);

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SetNonOBDFFROverwrittenForSameTrigger
(
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger
);

static FUNC( Dem_u08_StorageTriggerType, AUTOMATIC ) Dem_Data_GetTriggerKindOfNonObdFFROverwrittenIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_s16_FFListIndexType, AUTOMATIC ) FrOverwrittenIndex
);

static FUNC( void, DEM_CODE ) Dem_Data_RemoveLimitReachedTriggerToTmp
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) TargetTrigger
);
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

static FUNC( boolean, DEM_CODE ) Dem_Data_CheckUpperLimitIsReached
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) TargetTrigger
);

static FUNC( void, DEM_CODE ) Dem_Data_UpdateTriggerToTmp
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) TargetTrigger
);

#if ( DEM_OBDONUDS_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
static FUNC( boolean, DEM_CODE ) Dem_Data_CopyObdFFRecordIndexToTmpFromPairMisfireEvent
(
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,
    VAR( Dem_u08_UpdateRecordType, AUTOMATIC ) FreezeFrameRecordUpdate,
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) Trigger,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) CaptureFlgPtr
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_JudgeUpdateLatestObdFFD
(
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) Trigger
);
static FUNC( boolean, DEM_CODE ) Dem_Data_JudgeCaptureMisfireLatestObdFFD
(
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) Trigger
);
#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON ) */
#endif /* ( DEM_OBDONUDS_SUPPORT == STD_ON ) */

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
/* Function Name | Dem_Data_CaptureFreezeFrame                              */
/* Description   | Captures a freeze frame corresponding to specified even- */
/*               | t index and calls callback function "ReadDataElement".   */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/*               | [in] monitorData0 :                                      */
/*               |        Monitor test result                               */
/*               | [in] Trigger :                                           */
/*               |        The trigger for capture.                          */
/*               | [in] MisfireCylinder :                                   */
/*               |        The misfire cylinder.                             */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_CaptureFreezeFrame
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) Trigger,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) storeJudgeResult;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;


    /* Checks the specified event ID be within the range. */
    if( EventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]EventStrgIndex */
    {
        /* Within the range. */

        /* Judge need to store freeze frame */
        storeJudgeResult = Dem_Data_JudgeNeedToStoreFreezeFrame( EventStrgIndex );

        if ( storeJudgeResult == DEM_IRT_OK )
        {
            /* Captures freeze frame to the event memory entry of temporary area. */
             Dem_Data_CaptureFreezeFrameToTmp( EventStrgIndex, monitorData0, Trigger, MisfireCylinder );
        }
    }
    /* Returns with the result. */
    return ;
}


/****************************************************************************/
/* Function Name | Dem_Data_JudgeNeedToStoreFreezeFrame                     */
/* Description   |                                                          */
/* Preconditions | EventIndex < Dem_PrimaryMemEventConfigureNum             */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_JudgeNeedToStoreFreezeFrame
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) alreadyFFRStoredFlag;
    VAR( uint8, AUTOMATIC ) numberOfDTCsToStoreFreezeFrame;
    VAR( boolean, AUTOMATIC ) allObdDTCFreezeFlag;
    VAR( Dem_u08_MaxNumberOfDTCToStoreFreezeFrameType, AUTOMATIC ) maxNumberOfDTCToStoreFreezeFrame;

    maxNumberOfDTCToStoreFreezeFrame = Dem_MaxNumberOfDTCToStoreFreezeFrame;

    alreadyFFRStoredFlag = Dem_Data_CheckAlreadyFFRStoredOfTmp();

    if ( alreadyFFRStoredFlag == (boolean)TRUE )
    {
        /* Target EventStrgIndex already has FFR */
        retVal = DEM_IRT_OK;

    }
    else
    {
        numberOfDTCsToStoreFreezeFrame = Dem_DataMngC_GetNumberOfDTCsToStoreFreezeFrame( &allObdDTCFreezeFlag );

        if ( maxNumberOfDTCToStoreFreezeFrame > numberOfDTCsToStoreFreezeFrame )
        {
            /* not reached upper limit */
            retVal = DEM_IRT_OK;
        }
        else
        {
            /* reached upper limit */
            retVal = Dem_Data_JudgeNeedToStoreFreezeFrameByDisplacement( EventStrgIndex, allObdDTCFreezeFlag );
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Data_CheckAlreadyFFRStoredOfTmp                      */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | void                                                     */
/* Return Value  | boolean                                                  */
/*               |      TRUE  : TargetEvent already has FFR                 */
/*               |      FALSE : TargetEvent doesn't have FFR                */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Data_CheckAlreadyFFRStoredOfTmp
( void )
{
    VAR( boolean, AUTOMATIC ) retVal;

#if ( DEM_OBDFFD_SUPPORT == STD_ON ) /*  [FuncSw]    */
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) loopObdFFRClassIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonObdFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) loopNonObdFFRClassIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;

#if ( DEM_OBDFFD_SUPPORT == STD_ON ) /*  [FuncSw]    */
    obdFFRClassPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();
    obdFFDRecordNum = Dem_CfgInfoPm_GetObdFFDRecordNum();
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

    nonObdFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;
    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;
    retVal = (boolean)FALSE;

    for( loopNonObdFFRClassIndex = (Dem_u08_FFListIndexType)0U; loopNonObdFFRClassIndex < nonObdFFRClassPerDTCMaxNum; loopNonObdFFRClassIndex++ )   /* [GUD:for]loopNonObdFFRClassIndex */
    {
        if ( Dem_TmpEventMemoryEntry.FaultRecord.RecordNumberIndex[ loopNonObdFFRClassIndex ] < nonObdFFDRecordNum )                                /* [GUD]loopNonObdFFRClassIndex */
        {
            retVal = (boolean)TRUE;
            break;
        }
    }

#if ( DEM_OBDFFD_SUPPORT == STD_ON ) /*  [FuncSw]    */
    if ( retVal == (boolean)FALSE )
    {
        for( loopObdFFRClassIndex = (Dem_u08_FFListIndexType)0U; loopObdFFRClassIndex < obdFFRClassPerDTCMaxNum; loopObdFFRClassIndex++ )           /* [GUD:for]loopObdFFRClassIndex */
        {
            if ( Dem_TmpEventMemoryEntry.FaultRecord.ObdRecordNumberIndex[ loopObdFFRClassIndex ] < obdFFDRecordNum )                               /* [GUD]loopObdFFRClassIndex */
            {
                retVal = (boolean)TRUE;
                break;
            }
        }
    }
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Data_JudgeNeedToStoreFreezeFrameByDisplacement       */
/* Description   |                                                          */
/* Preconditions | EventIndex < Dem_PrimaryMemEventConfigureNum             */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] AllObdDTCFreezeFlag :                               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_JudgeNeedToStoreFreezeFrameByDisplacement
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( boolean, AUTOMATIC ) AllObdDTCFreezeFlag
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) obdDTCFlag;

#if ( DEM_OBDFFD_SUPPORT == STD_ON ) /*  [FuncSw]    */
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) loopObdFFRClassIndex;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonObdFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) loopNonObdFFRClassIndex;

#if ( DEM_OBDFFD_SUPPORT == STD_ON ) /*  [FuncSw]    */
    obdFFRClassPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

    nonObdFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;

    obdDTCFlag = Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( EventStrgIndex );  /* [GUD:RET:TRUE] EventStrgIndex */
    retVal = DEM_IRT_NG;

    /* reached upper limit */
    if ( ( AllObdDTCFreezeFlag == (boolean)FALSE ) && ( obdDTCFlag == (boolean)TRUE ) )
    {
        /* Non-OBDDTC freeze exist and new event is OBD event */
        retVal = DEM_IRT_OK;
    }
    else
    {
        for( loopNonObdFFRClassIndex = (Dem_u08_FFListIndexType)0U; loopNonObdFFRClassIndex < nonObdFFRClassPerDTCMaxNum; loopNonObdFFRClassIndex++ )   /* [GUD:for]loopNonObdFFRClassIndex */
        {
            if ( Dem_EventDisplacement.FaultRecordOverwritten[loopNonObdFFRClassIndex].FaultIndex == Dem_TmpEventMemoryEntry.EventRecord.FaultIndex )   /* [GUD]loopNonObdFFRClassIndex */
            {
                /* Overwritten fault record has freeze frame record */
                retVal = DEM_IRT_OK;
                break;
            }
        }
#if ( DEM_OBDFFD_SUPPORT == STD_ON ) /*  [FuncSw]    */
        if ( retVal == DEM_IRT_NG )
        {
            for( loopObdFFRClassIndex = (Dem_u08_FFListIndexType)0U; loopObdFFRClassIndex < obdFFRClassPerDTCMaxNum; loopObdFFRClassIndex++ )           /* [GUD:for]loopObdFFRClassIndex */
            {
                if ( Dem_EventDisplacement.ObdFaultRecordOverwritten[loopObdFFRClassIndex].FaultIndex == Dem_TmpEventMemoryEntry.EventRecord.FaultIndex )   /* [GUD]loopObdFFRClassIndex */
                {
                    /* Overwritten fault record has freeze frame record */
                    retVal = DEM_IRT_OK;
                    break;
                }
            }
        }
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */
    }

    return retVal;
}
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */
/****************************************************************************/
/* Function Name | Dem_Data_JudgeNeedToStoreFreezeFrameByDisplacement       */
/* Description   |                                                          */
/* Preconditions | EventIndex < Dem_PrimaryMemEventConfigureNum             */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] AllObdDTCFreezeFlag :                               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_OFF )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_JudgeNeedToStoreFreezeFrameByDisplacement
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex, /* MISRA DEVIATION */
    VAR( boolean, AUTOMATIC ) AllObdDTCFreezeFlag                /* MISRA DEVIATION */
)
{
    /* Need not to store FFR */
    return DEM_IRT_NG;
}
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_OFF ) */

/****************************************************************************/
/* Function Name | Dem_Data_CaptureFreezeFrameToTmp                         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] monitorData0 :                                      */
/*               |        Monitor test result                               */
/*               |        The event index corresponding to the event ID.    */
/*               | [in] Trigger :                                           */
/*               |        The trigger for capture.                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_CaptureFreezeFrameToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) Trigger,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
)
{
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    /* Captures OBD freeze frame to the event memory entry of temporary area. */
    Dem_Data_CaptureObdFreezeFrameToTmp( EventStrgIndex, monitorData0, Trigger, MisfireCylinder );
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */

    /* Captures non-OBD freeze frame to the event memory entry of temporary area. */
    Dem_Data_CaptureNonObdFreezeFrameToTmp( EventStrgIndex, monitorData0, Trigger, MisfireCylinder );

    return ;
}


#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_CaptureObdFreezeFrameToTmp                      */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/*               | [in] monitorData0 :                                      */
/*               |        Monitor test result                               */
/*               | [in] Trigger :                                           */
/*               |        The trigger for capture.                          */
/*               | [in] MisfireCylinder :                                   */
/*               |        The misfire cylinder.                             */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-9-0      | branch changed.                                          */
/*   v5-10-0     | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_CaptureObdFreezeFrameToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) Trigger,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
)
{
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) obdFreezeFrameClassRef;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) obdFreezeframeRecNumClassRef;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfRetrieve;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordClassRefIndex;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) freezeFrameRecordClassIndex;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) ffrRecordClassConfigureNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) freezeFrameRecordTrigger;
    VAR( Dem_u08_UpdateRecordType, AUTOMATIC ) freezeFrameRecordUpdate;
    VAR( boolean, AUTOMATIC ) readDataElementAllowed;
    VAR( boolean, AUTOMATIC ) updatePendingFFD;
    VAR( boolean, AUTOMATIC ) captureFlg;


    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA) freezeFrameClassPtr;
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecNumClassPtr;

    /* Checks the reference of freeze frame class. */
    Dem_CfgInfoPm_GetOBDFreezeFrameAndRecNumClass( EventStrgIndex, &obdFreezeFrameClassRef, &obdFreezeframeRecNumClassRef );    /* [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] obdFreezeFrameClassRef *//* [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] obdFreezeframeRecNumClassRef */
    Dem_CfgInfoPm_GetNumOfOBDFreezeFrameRecordClass( &ffrRecordClassConfigureNum, &obdFFRClassPerDTCMaxNum );

    if( obdFreezeFrameClassRef != DEM_FFCLASSINDEX_INVALID )                                                /* [GUD:if]obdFreezeFrameClassRef  */
    {
        /* Checks the reference of freeze frame record number class. */
        if( obdFreezeframeRecNumClassRef != DEM_FFRECNUMCLASSINDEX_INVALID )                                /* [GUD:if]obdFreezeframeRecNumClassRef  */
        {
            /* Holds the FreezeFrameClass table pointed to */
            /* by the FreezeFrameClass table list Index of the held DTCAttribute table. */
            freezeFrameClassPtr = &Dem_FreezeFrameClassTable[obdFreezeFrameClassRef];                       /* [GUD]obdFreezeFrameClassRef  */

            /* Holds the FreezeFrameRecNumClass table pointed to */
            /* by the FreezeFrameRecNumClass table list Index of the held DTCAttribute table. */
            freezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[ obdFreezeframeRecNumClassRef ];   /* [GUD]obdFreezeframeRecNumClassRef  */

            for( freezeFrameRecordClassRefIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordClassRefIndex < obdFFRClassPerDTCMaxNum; freezeFrameRecordClassRefIndex++ )             /* [GUD:for]freezeFrameRecordClassRefIndex  */
            {
                /* Holds the DemFreezeFrameRecordIndex pointed to */
                /* by the DemFreezeFrameRecordClassRef Index of the held FreezeFrameRecNumClass table. */
                freezeFrameRecordClassIndex = freezeFrameRecNumClassPtr->DemFreezeFrameRecordClassRef[freezeFrameRecordClassRefIndex];          /* [GUD]freezeFrameRecordClassRefIndex  *//* [ARYCHK] DEM_FF_RECORD_CLASS_REF_MAX_NUM / 1 / freezeFrameRecordClassRefIndex */

                if( freezeFrameRecordClassIndex < ffrRecordClassConfigureNum )                                                                  /* [GUD:if]freezeFrameRecordClassIndex  */
                {
                    /* Holds the FreezeFrameRecordClass table pointed to by DemFreezeFrameRecordIndex. */
                    freezeFrameRecordTrigger    =   Dem_CfgInfoPm_GetFreezeFrameRecordInfo_forCapture( freezeFrameRecordClassIndex, &freezeFrameRecordUpdate );         /* [GUD]freezeFrameRecordClassIndex  *//* [GUD:CFG:IF_GUARDED: freezeFrameRecordClassIndex ]freezeFrameRecordClassPtr */

                    /* Retrieves  allowed to ReadDataElement with the held freeze frame record class table's trigger and the specified trigger.  */
                    updatePendingFFD = (boolean)FALSE;
                    readDataElementAllowed = Dem_CfgInfo_CheckObdTrigger( &freezeFrameRecordTrigger, Trigger, &updatePendingFFD );

                    /* Checks allowed to ReadDataElement is TRUE. */
                    if( readDataElementAllowed == (boolean)TRUE )
                    {
                        /* Gets the temporary freeze frame record in corresponding to */
                        /* the specific freeze frame record class index. */
                        captureFlg = (boolean)FALSE;
                        resultOfRetrieve = Dem_Data_SetObdFFRecordIndexToTmp(freezeFrameRecordClassRefIndex, freezeFrameRecordUpdate, updatePendingFFD, Trigger, &captureFlg ); /* [GUD]freezeFrameRecordClassRefIndex  */

                        /* Checks the result of retrieve the temporary freeze frame record. */
                        if( resultOfRetrieve == DEM_IRT_OK )
                        {
#if ( DEM_OBDONUDS_SUPPORT == STD_ON )                  /*  [FuncSw]    */
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )      /*  [FuncSw]    */
                            if ( captureFlg == (boolean)TRUE )
#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON ) */
#endif /* ( DEM_OBDONUDS_SUPPORT == STD_ON )             */
                            {
                                Dem_Data_SetResultOfCmpObdFFRecordToTmp( freezeFrameRecordClassRefIndex, DEM_IRT_NG );                              /* [GUD]freezeFrameRecordClassRefIndex  */
                            }

                            Dem_Data_CaptureObdFreezeFrameDataToTmp( EventStrgIndex, monitorData0, freezeFrameRecordClassRefIndex, freezeFrameClassPtr, freezeFrameRecordTrigger, MisfireCylinder, captureFlg );    /* [GUD]freezeFrameRecordClassRefIndex  */

                        }
                    }
                }
            }
        }
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Data_SetObdFFRecordIndexToTmp                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameRecordClassIndex :                       */
/*               |                                                          */
/*               | [in] FreezeFrameRecordUpdate :                           */
/*               |                                                          */
/*               | [in] UpdatePendingFFD :                                  */
/*               |                                                          */
/*               | [in] Trigger :                                           */
/*               |                                                          */
/*               | [in] CaptureFlgPtr :                                     */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/*   v5-9-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SetObdFFRecordIndexToTmp
(
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,
    VAR( Dem_u08_UpdateRecordType, AUTOMATIC ) FreezeFrameRecordUpdate,
    VAR( boolean, AUTOMATIC ) UpdatePendingFFD,
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) Trigger,   /* MISRA DEVIATION */
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) CaptureFlgPtr
)
{
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) emptyIndexOfFreezeFrameRecords;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;
#if ( DEM_OBDONUDS_SUPPORT == STD_ON )              /*  [FuncSw]    */
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) retCopyObdFFRecordIndex;
#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON ) */
#endif /* ( DEM_OBDONUDS_SUPPORT == STD_ON )             */

    retVal = DEM_IRT_OK;
    obdFFRClassPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();
    obdFFDRecordNum = Dem_CfgInfoPm_GetObdFFDRecordNum();
    *CaptureFlgPtr = (boolean)TRUE;

    if( FreezeFrameRecordClassIndex >= obdFFRClassPerDTCMaxNum )                                /* [GUD:if]FreezeFrameRecordClassIndex */
    {
        retVal = DEM_IRT_NG;
    }
    else
    {
        if( Dem_TmpEventMemoryEntry.EventRecord.FaultIndex == DEM_FAULTINDEX_INITIAL )
        {
            retVal = DEM_IRT_NG;
        }
        else
        {
            if( Dem_TmpEventMemoryEntry.FaultRecord.ObdRecordNumberIndex[FreezeFrameRecordClassIndex] == DEM_FFRECINDEX_INITIAL )       /* [GUD]FreezeFrameRecordClassIndex */
            {
#if ( DEM_OBDONUDS_SUPPORT == STD_ON )              /*  [FuncSw]    */
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                retCopyObdFFRecordIndex = Dem_Data_CopyObdFFRecordIndexToTmpFromPairMisfireEvent( FreezeFrameRecordClassIndex, FreezeFrameRecordUpdate, Trigger, CaptureFlgPtr );
                if( retCopyObdFFRecordIndex == (boolean)FALSE )
#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )    */
#endif /* ( DEM_OBDONUDS_SUPPORT == STD_ON )                */
                {
                    if( Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfObdFreezeFrameRecords < obdFFDRecordNum )
                    {
                        emptyIndexOfFreezeFrameRecords = Dem_DataMngC_GetEmptyObdFFDIndex();

                        if( emptyIndexOfFreezeFrameRecords < obdFFDRecordNum )
                        {
                            Dem_TmpEventMemoryEntry.FaultRecord.ObdRecordNumberIndex[FreezeFrameRecordClassIndex] = emptyIndexOfFreezeFrameRecords; /* [GUD]FreezeFrameRecordClassIndex */

                            Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfObdFreezeFrameRecords++;
                        }
                        else
                        {
                            retVal = DEM_IRT_NG;
                        }
                    }
                    else
                    {
                        retVal = Dem_Data_SetOBDFFROverwritten( FreezeFrameRecordClassIndex );                  /* [GUD]FreezeFrameRecordClassIndex */
                    }
                }
            }
            else
            {
                if( FreezeFrameRecordUpdate == DEM_UPDATE_RECORD_NO )
                {
                    if( UpdatePendingFFD == (boolean)FALSE )
                    {
                        retVal = DEM_IRT_NG;
                    }
                }
                else
                {
#if ( DEM_OBDONUDS_SUPPORT == STD_ON )              /*  [FuncSw]    */
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                    retVal = Dem_Data_JudgeUpdateLatestObdFFD( Trigger );
#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )    */
#endif /* ( DEM_OBDONUDS_SUPPORT == STD_ON )                */
                }
            }
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Data_CaptureObdFreezeFrameDataToTmp                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The index for Dem_EventRecordList.                */
/*               | [in] monitorData0 :                                      */
/*               |        Monitor test result                               */
/*               | [in] FreezeFrameRecordClassIndex :                       */
/*               |        The DemFreezeFrameRecordClassRef array's index    */
/*               | [in] FreezeFrameClassPtr :                               */
/*               |        The pointer of DemFreezeFrameClass.               */
/*               | [in] FreezeFrameRecordTrigger :                          */
/*               |        DemFreezeFrameRecordTrigger.                      */
/*               | [in] MisfireCylinder :                                   */
/*               |        Misfire cylinder.                                 */
/*               | [in] CaptureFlg :                                        */
/*               |        Whether to capture obd freeze frame.              */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/*   v5-9-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_CaptureObdFreezeFrameDataToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,      /* [PRMCHK:CALLER] */
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameClassPtr,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,  /* MISRA DEVIATION */
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder,              /* MISRA DEVIATION */
    VAR( boolean, AUTOMATIC ) CaptureFlg    /* MISRA DEVIATION */
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;

#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )     /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) triggerFFDCaptureFlag;
#endif  /*   ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )            */


#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )     /*  [FuncSw]    */
    triggerFFDCaptureFlag = Dem_PreFFD_SetObdPreFFDToObdTriggerFFD( EventStrgIndex, FreezeFrameRecordTrigger, MisfireCylinder, &Dem_TmpEventMemoryEntry.ObdFreezeFrameRecordList[FreezeFrameRecordClassIndex] );    /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */
    if( triggerFFDCaptureFlag == (boolean)TRUE )
#endif  /*   ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )            */
    {
        /* In case could not find out pre-stored freeze frame reocrd by the specified event index. */

        /* Set the event Index of the event memory entry of temporary area to the event Index of the OBD freeze frame record. */
        Dem_TmpEventMemoryEntry.ObdFreezeFrameRecordList[FreezeFrameRecordClassIndex].EventStrgIndex = EventStrgIndex;  /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */

        /* Set "stored" to the record status of the OBD freeze frame record. */
        Dem_TmpEventMemoryEntry.ObdFreezeFrameRecordList[FreezeFrameRecordClassIndex].RecordStatus = DEM_FFD_STORED;    /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */

#if ( DEM_OBDONUDS_SUPPORT == STD_ON )              /*  [FuncSw]    */
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        if( CaptureFlg == (boolean)TRUE )
#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )    */
#endif /* ( DEM_OBDONUDS_SUPPORT == STD_ON )                */
        {
            eventCtrlIndex = Dem_CmbEvt_GetDelegateEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );

            /* Store capture data in the freeze frame record data */
#ifndef DEM_SIT_RANGE_CHECK
            Dem_Data_CaptureFreezeFrameClass( eventCtrlIndex, FreezeFrameClassPtr, Dem_TmpEventMemoryEntry.ObdFreezeFrameRecordList[FreezeFrameRecordClassIndex].Data , monitorData0 );  /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */
#else   /* DEM_SIT_RANGE_CHECK */
            Dem_Data_CaptureFreezeFrameClass( Dem_ObdFFRMaxLength, eventCtrlIndex, FreezeFrameClassPtr, Dem_TmpEventMemoryEntry.ObdFreezeFrameRecordList[FreezeFrameRecordClassIndex].Data , monitorData0 );  /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */
#endif  /* DEM_SIT_RANGE_CHECK */
        }
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
            Dem_Misfire_UpdateObdFFDInfo( EventStrgIndex, FreezeFrameRecordTrigger, MisfireCylinder );
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Data_SetOBDFFROverwritten                            */
/* Description   | Set fault record which to be overwritten OBD freeze      */
/*               | frame records.                                           */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameRecordClassIndex :                       */
/*               |        The DemFreezeFrameRecordClassRef array's index    */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Overwriting is possible              */
/*               |        DEM_IRT_NG : Overwriting is impossible            */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SetOBDFFROverwritten
(
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex       /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetEventStrgIndexAndRecNumIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdRecordNumberIndex[DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM];
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) tmpFFListIndexNum;
    VAR( Dem_s16_FFListIndexType, AUTOMATIC ) ffListIndexNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) frChkOverwrittenIndex;
    VAR( Dem_s16_FFListIndexType, AUTOMATIC ) frOverwrittenIndex;
    VAR( Dem_s16_FFListIndexType, AUTOMATIC ) frNotOverwrittenIndex;
    VAR( Dem_s16_FFListIndexType, AUTOMATIC ) frOverwrittenLmt;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

    VAR( Dem_EventEntryOverwriteFaultInfoType, AUTOMATIC ) eeoFaultInfo;

    retVal = DEM_IRT_NG;

    obdFFRClassPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();
    tmpFFListIndexNum = obdFFRClassPerDTCMaxNum - (Dem_u08_FFListIndexType)1U;
    frOverwrittenLmt = (Dem_s16_FFListIndexType)0U;

    ffListIndexNum = (Dem_s16_FFListIndexType)tmpFFListIndexNum;

    for( frOverwrittenIndex = ffListIndexNum; frOverwrittenIndex >= frOverwrittenLmt; frOverwrittenIndex-- )                                        /* [GUD:for]frOverwrittenLmt */
    {
        if( Dem_EventDisplacement.ObdFaultRecordOverwritten[frOverwrittenIndex].FaultIndex == Dem_TmpEventMemoryEntry.EventRecord.FaultIndex )      /* [GUD]frOverwrittenLmt  */
        {
            Dem_TmpEventMemoryEntry.FaultRecord.ObdRecordNumberIndex[FreezeFrameRecordClassIndex] = Dem_EventDisplacement.ObdFaultRecordOverwritten[frOverwrittenIndex].RecordNumberIndex;      /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex *//* [GUD]frOverwrittenLmt  */

            Dem_EventDisplacement.ObdFaultRecordOverwritten[frOverwrittenIndex].FaultIndex = DEM_FAULTINDEX_INITIAL;                                /* [GUD]frOverwrittenLmt  */
            Dem_EventDisplacement.ObdFaultRecordOverwritten[frOverwrittenIndex].EventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;                        /* [GUD]frOverwrittenLmt  */
            Dem_EventDisplacement.ObdFaultRecordOverwritten[frOverwrittenIndex].RecordNumberIndex = DEM_FFRECINDEX_INITIAL;                         /* [GUD]frOverwrittenLmt  */

            Dem_DcEeo_SelectNextOBDFFROverwrite();

            retVal = DEM_IRT_OK;

            break;
        }
    }

    if( frOverwrittenIndex < frOverwrittenLmt )                                                                                                     /* [GUD:if]frOverwrittenIndex  */
    {
        eeoFaultInfo.EventPriority = Dem_CfgInfoPm_GetEventPriority( Dem_TmpEventMemoryEntry.EventStrgIndex );  /* [GUDCHK:SETVAL]Dem_TmpEventMemoryEntry.EventStrgIndex */
        eeoFaultInfo.StatusOfDTC = Dem_EventDisplacement.DTCStatusForFaultRecordOverwrite;
        eeoFaultInfo.EventStrgIndex = Dem_TmpEventMemoryEntry.EventStrgIndex;
        faultIndex = Dem_DcEeo_GetFaultIndexOfOBDFFROverwrite( &eeoFaultInfo );

        eventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;

        resultOfGetEventStrgIndexAndRecNumIndex = Dem_DataMngC_GetFR_EventStrgIndex_ObdRecordNumberIndex( faultIndex, &eventStrgIndex, &obdRecordNumberIndex[0] );/* [ARYCHK] DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / 0 */

        if( resultOfGetEventStrgIndexAndRecNumIndex == DEM_IRT_OK )
        {
            obdFFDRecordNum = Dem_CfgInfoPm_GetObdFFDRecordNum();

            for( frNotOverwrittenIndex = ffListIndexNum; frNotOverwrittenIndex >= frOverwrittenLmt; frNotOverwrittenIndex-- )                   /* [GUD:for]frNotOverwrittenIndex */
            {
                if( obdRecordNumberIndex[frNotOverwrittenIndex] < obdFFDRecordNum )                                                             /* [GUD]frNotOverwrittenIndex  *//* [ARYCHK] DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / frNotOverwrittenIndex */
                {
                    /* In case the ObdRecordNumberIndex is valid to reuse. */

                    for( frChkOverwrittenIndex = (Dem_u08_FFListIndexType)0U; frChkOverwrittenIndex < FreezeFrameRecordClassIndex; frChkOverwrittenIndex++ )                /* [GUD:for]frChkOverwrittenIndex */
                    {
                        /* Checks if the ObdRecordNumberIndex retained in the fault record which to be overwritten was already used. */
                        if( obdRecordNumberIndex[frNotOverwrittenIndex] == Dem_EventDisplacement.ObdFaultRecordOverwritten[frChkOverwrittenIndex].RecordNumberIndex )       /* [GUD]frNotOverwrittenIndex *//* [GUD]frChkOverwrittenIndex *//* [ARYCHK] DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / frNotOverwrittenIndex */
                        {
                            /* In case the ObdRecordNumberIndex was already used, try a next ObdRecordNumberIndex retained in the fault record which to be overwritten */

                            break;
                        }

                    }

                    if( frChkOverwrittenIndex >= FreezeFrameRecordClassIndex )                                                                  /* [GUD:if]frChkOverwrittenIndex  */
                    {
                        /* In case the ObdRecordNumberIndex is unused, retains ObdFaultRecordOverwritten pointed by the spcified FreezeFrameRecordClassIndex. */

                        Dem_TmpEventMemoryEntry.FaultRecord.ObdRecordNumberIndex[FreezeFrameRecordClassIndex] = obdRecordNumberIndex[frNotOverwrittenIndex];    /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex *//* [GUD]frNotOverwrittenIndex  *//* [ARYCHK] DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / frNotOverwrittenIndex */

                        Dem_EventDisplacement.ObdFaultRecordOverwritten[FreezeFrameRecordClassIndex].FaultIndex = faultIndex;                                   /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */
                        Dem_EventDisplacement.ObdFaultRecordOverwritten[FreezeFrameRecordClassIndex].EventStrgIndex = eventStrgIndex;                           /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */
                        Dem_EventDisplacement.ObdFaultRecordOverwritten[FreezeFrameRecordClassIndex].RecordNumberIndex = obdRecordNumberIndex[frNotOverwrittenIndex];   /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex *//* [GUD]frNotOverwrittenIndex  *//* [ARYCHK] DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / frNotOverwrittenIndex */

                        Dem_DcEeo_SelectNextOBDFFROverwrite();

                        retVal = DEM_IRT_OK;
                    }
                }

                if( retVal == DEM_IRT_OK )
                {
                    break;
                }
            }
        }
    }

    return retVal;
}
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_Data_SetOBDFFROverwritten                            */
/* Description   | Set fault record which to be overwritten OBD freeze      */
/*               | frame records.                                           */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameRecordClassIndex :                       */
/*               |        The DemFreezeFrameRecordClassRef array's index    */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_NG : Overwriting is impossible            */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_OFF )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SetOBDFFROverwritten
(
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex /* MISRA DEVIATION */
)
{
    /* This function has no implementation because event displacement is not supported. */

    return DEM_IRT_NG;  /* Returns overwritting is impossible. */
}
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_OFF ) */
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */


/****************************************************************************/
/* Function Name | Dem_Data_CaptureNonObdFreezeFrameToTmp                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/*               | [in] monitorData0 :                                      */
/*               |        Monitor test result                               */
/*               | [in] Trigger :                                           */
/*               |        The trigger for capture.                          */
/*               | [in] MisfireCylinder :                                   */
/*               |        The misfire cylinder.                             */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/*   v5-10-0     | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_CaptureNonObdFreezeFrameToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) Trigger,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
)
{
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) freezeFrameClassRef;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) freezeframeRecNumClassRef;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfRetrieve;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordClassRefIndex;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) freezeFrameRecordClassIndex;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) ffrRecordClassConfigureNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) freezeFrameRecordTrigger;
    VAR( Dem_u08_UpdateRecordType, AUTOMATIC ) freezeFrameRecordUpdate;
    VAR( boolean, AUTOMATIC ) readDataElementAllowed;

    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA) freezeFrameClassPtr;
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecNumClassPtr;

    /* Checks the reference of freeze frame class. */
    Dem_CfgInfoPm_GetFreezeFrameAndRecNumClass( EventStrgIndex, &freezeFrameClassRef, &freezeframeRecNumClassRef ); /* [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] freezeFrameClassRef *//* [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] freezeframeRecNumClassRef */
    Dem_CfgInfoPm_GetNumOfFreezeFrameRecordClass( &ffrRecordClassConfigureNum, &nonOBDFFRClassPerDTCMaxNum );

    if( freezeFrameClassRef != DEM_FFCLASSINDEX_INVALID )                                                           /* [GUD:if] freezeFrameClassRef */
    {
        /* Checks the reference of freeze frame record number class. */
        if( freezeframeRecNumClassRef != DEM_FFRECNUMCLASSINDEX_INVALID )                                           /* [GUD:if] freezeframeRecNumClassRef */
        {
            /* Holds the FreezeFrameClass table pointed to */
            /* by the FreezeFrameClass table list Index of the held DTCAttribute table. */
            freezeFrameClassPtr = &Dem_FreezeFrameClassTable[ freezeFrameClassRef ];                                /* [GUD] freezeFrameClassRef */

            /* Holds the FreezeFrameRecNumClass table pointed to */
            /* by the FreezeFrameRecNumClass table list Index of the held DTCAttribute table. */
            freezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[freezeframeRecNumClassRef];                /* [GUD] freezeframeRecNumClassRef */

            for( freezeFrameRecordClassRefIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordClassRefIndex < nonOBDFFRClassPerDTCMaxNum; freezeFrameRecordClassRefIndex++ )  /* [GUD:for]freezeFrameRecordClassRefIndex */
            {
                /* Holds the DemFreezeFrameRecordIndex pointed to */
                /* by the DemFreezeFrameRecordClassRef Index of the held FreezeFrameRecNumClass table. */
                freezeFrameRecordClassIndex = freezeFrameRecNumClassPtr->DemFreezeFrameRecordClassRef[freezeFrameRecordClassRefIndex];      /* [GUD] freezeFrameRecordClassRefIndex *//* [ARYCHK] DEM_FF_RECORD_CLASS_REF_MAX_NUM / 1 / freezeFrameRecordClassRefIndex */

                if( freezeFrameRecordClassIndex < ffrRecordClassConfigureNum )                                                              /* [GUD:if] freezeFrameRecordClassIndex */
                {
                    /* Holds the FreezeFrameRecordClass table pointed to by DemFreezeFrameRecordIndex. */
                    freezeFrameRecordTrigger    =   Dem_CfgInfoPm_GetFreezeFrameRecordInfo_forCapture( freezeFrameRecordClassIndex, &freezeFrameRecordUpdate );     /* [GUD]freezeFrameRecordClassIndex  *//* [GUD:CFG:IF_GUARDED: freezeFrameRecordClassIndex ]freezeFrameRecordClassPtr */

                    /* Retrieves  allowed to ReadDataElement with the held freeze frame record class table's trigger and the specified trigger.  */
                    readDataElementAllowed = Dem_CfgInfo_CheckTrigger( &freezeFrameRecordTrigger, Trigger );

                    /* Checks allowed to ReadDataElement is TRUE. */
                    if( readDataElementAllowed == (boolean)TRUE )
                    {
                        /* Gets the temporary freeze frame record in corresponding to */
                        /* the specific freeze frame record class index. */
                        resultOfRetrieve = Dem_Data_SetFFRecordIndexToTmp( freezeFrameRecordClassRefIndex, freezeFrameRecordUpdate, freezeFrameRecordTrigger );

                        /* Checks the result of retrieve the temporary freeze frame record. */
                        if( resultOfRetrieve == DEM_IRT_OK )
                        {
                            Dem_Data_SetResultOfCmpFFRecordToTmp( freezeFrameRecordClassRefIndex, DEM_IRT_NG );                             /* [GUD] freezeFrameRecordClassRefIndex */

                            Dem_Data_CaptureFreezeFrameDataToTmp( EventStrgIndex, monitorData0, freezeFrameRecordClassRefIndex, freezeFrameClassPtr, freezeFrameRecordTrigger, MisfireCylinder );   /* [GUD] freezeFrameRecordClassRefIndex */

                            Dem_Data_UpdateTriggerToTmp( freezeFrameRecordTrigger );
                        }
                    }
                }
            }
        }
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Data_SetFFRecordIndexToTmp                           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameRecordClassIndex :                       */
/*               |                                                          */
/*               | [in] FreezeFrameRecordUpdate :                           */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SetFFRecordIndexToTmp
(
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,
    VAR( Dem_u08_UpdateRecordType, AUTOMATIC ) FreezeFrameRecordUpdate,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger
)
{
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) emptyIndexOfFreezeFrameRecords;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) upperLimitIsReached;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;

    retVal = DEM_IRT_OK;
    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;
    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;

    if( FreezeFrameRecordClassIndex >= nonOBDFFRClassPerDTCMaxNum )             /* [GUD:if]FreezeFrameRecordClassIndex */
    {
        retVal = DEM_IRT_NG;
    }
    else
    {
        if( Dem_TmpEventMemoryEntry.EventRecord.FaultIndex == DEM_FAULTINDEX_INITIAL )
        {
            retVal = DEM_IRT_NG;
        }
        else
        {
            if( Dem_TmpEventMemoryEntry.FaultRecord.RecordNumberIndex[FreezeFrameRecordClassIndex] == DEM_FFRECINDEX_INITIAL )                      /* [GUD]FreezeFrameRecordClassIndex */
            {

                if( Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfFreezeFrameRecords < nonObdFFDRecordNum )
                {
#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) /* [FuncSw] */
                    upperLimitIsReached = Dem_Data_CheckUpperLimitIsReached( FreezeFrameRecordTrigger );
                    if ( upperLimitIsReached != (boolean)FALSE )
                    {
                        retVal = Dem_Data_SetNonOBDFFROverwritten( FreezeFrameRecordClassIndex, FreezeFrameRecordTrigger, upperLimitIsReached );    /* [GUD]FreezeFrameRecordClassIndex */
                    }
                    else
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */
                    {
                        emptyIndexOfFreezeFrameRecords = Dem_DataMngC_GetEmptyFFDIndex();

                        if( emptyIndexOfFreezeFrameRecords < nonObdFFDRecordNum )
                        {
                            Dem_TmpEventMemoryEntry.FaultRecord.RecordNumberIndex[FreezeFrameRecordClassIndex] = emptyIndexOfFreezeFrameRecords;    /* [GUD]FreezeFrameRecordClassIndex */

                            Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfFreezeFrameRecords++;
                        }
                        else
                        {
                            retVal = DEM_IRT_NG;
                        }
                    }

                }
                else
                {
                    upperLimitIsReached = Dem_Data_CheckUpperLimitIsReached( FreezeFrameRecordTrigger );
                    retVal = Dem_Data_SetNonOBDFFROverwritten( FreezeFrameRecordClassIndex, FreezeFrameRecordTrigger, upperLimitIsReached );        /* [GUD]FreezeFrameRecordClassIndex */
                }
            }
            else
            {
                if( FreezeFrameRecordUpdate == DEM_UPDATE_RECORD_NO )
                {
                    retVal = DEM_IRT_NG;
                }
                else
                {
                    /* No Process */
                }
            }
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Data_CaptureFreezeFrameDataToTmp                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The index for Dem_EventRecordList.                */
/*               | [in] monitorData0 :                                      */
/*               |         Monitor test result                              */
/*               | [in] FreezeFrameRecordClassIndex :                       */
/*               |        The DemFreezeFrameRecordClassRef array's index    */
/*               | [in] FreezeFrameClassPtr :                               */
/*               |        The pointer of DemFreezeFrameClass.               */
/*               | [in] FreezeFrameRecordTrigger :                          */
/*               |        DemFreezeFrameRecordTrigger.                      */
/*               | [in] MisfireCylinder :                                   */
/*               |        Misfire cylinder.                                 */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_CaptureFreezeFrameDataToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,      /* [PRMCHK:CALLER] */
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameClassPtr,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,  /* MISRA DEVIATION */
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder               /* MISRA DEVIATION */
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )     /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) triggerFFDCaptureFlag;
#endif  /*   ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )            */


#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )     /*  [FuncSw]    */
    triggerFFDCaptureFlag = Dem_PreFFD_SetPreFFDToTriggerFFD( EventStrgIndex, FreezeFrameClassPtr, FreezeFrameRecordTrigger, MisfireCylinder, &Dem_TmpEventMemoryEntry.FreezeFrameRecordList[FreezeFrameRecordClassIndex] );    /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */
    if( triggerFFDCaptureFlag == (boolean)TRUE )
#endif  /*   ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )            */
    {
        /* In case could not find out pre-stored freeze frame reocrd by the specified event index. */

        /* Set the event Index of the event memory entry of temporary area to the event Index of the freeze frame record. */
        Dem_TmpEventMemoryEntry.FreezeFrameRecordList[FreezeFrameRecordClassIndex].EventStrgIndex = EventStrgIndex;     /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */

        /* Set "stored" to the record status of the freeze frame record. */
        Dem_TmpEventMemoryEntry.FreezeFrameRecordList[FreezeFrameRecordClassIndex].RecordStatus = DEM_FFD_STORED;       /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */

        eventCtrlIndex = Dem_CmbEvt_GetDelegateEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );

        /* Store capture data in the freeze frame record data */
#ifndef DEM_SIT_RANGE_CHECK
        Dem_Data_CaptureFreezeFrameClass( eventCtrlIndex, FreezeFrameClassPtr, Dem_TmpEventMemoryEntry.FreezeFrameRecordList[FreezeFrameRecordClassIndex].Data , monitorData0 ); /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */
#else   /* DEM_SIT_RANGE_CHECK */
        Dem_Data_CaptureFreezeFrameClass( Dem_FFRMaxLength, eventCtrlIndex, FreezeFrameClassPtr, Dem_TmpEventMemoryEntry.FreezeFrameRecordList[FreezeFrameRecordClassIndex].Data , monitorData0 ); /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */
#endif  /* DEM_SIT_RANGE_CHECK */

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        Dem_Misfire_UpdateFFDInfo( EventStrgIndex, FreezeFrameRecordTrigger, MisfireCylinder );
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
    }

    return;
}


/*******************************************************************************/
/* Function Name | Dem_Data_SetNonOBDFFROverwritten                            */
/* Description   | Set fault record which to be overwritten non-OBD freeze     */
/*               | frame records.                                              */
/* Preconditions |                                                             */
/* Parameters    | [in] FreezeFrameRecordClassIndex :                          */
/*               |        The DemFreezeFrameRecordClassRef array's index       */
/*               | [in] FreezeFrameRecordTrigger                               */
/*               |        Trigger corresponding to FreezeFrameRecordClassIndex */
/*               | [in] UpperLimitIsReached                                    */
/*               |        FreezeFrameRecordTrigger's upper limit check result  */
/*               |                                                             */
/* Return Value  | Dem_u08_InternalReturnType                                  */
/*               |        DEM_IRT_OK : Overwriting is possible                 */
/*               |        DEM_IRT_NG : Overwriting is impossible               */
/* Notes         | -                                                           */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/*******************************************************************************/
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_OFF )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SetNonOBDFFROverwritten
(
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,      /* [PRMCHK:CALLER] */
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger, /* MISRA DEVIATION */
    VAR( boolean, AUTOMATIC ) UpperLimitIsReached     /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetEventStrgIndexAndRecNumIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) recordNumberIndex[DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM];
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) tmpFFListIndexNum;
    VAR( Dem_s16_FFListIndexType, AUTOMATIC ) ffListIndexNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) frChkOverwrittenIndex;
    VAR( Dem_s16_FFListIndexType, AUTOMATIC ) frOverwrittenIndex;
    VAR( Dem_s16_FFListIndexType, AUTOMATIC ) frNotOverwrittenIndex;
    VAR( Dem_s16_FFListIndexType, AUTOMATIC ) frOverwrittenLmt;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_EventEntryOverwriteFaultInfoType, AUTOMATIC ) eeoFaultInfo;

    retVal = DEM_IRT_NG;

    tmpFFListIndexNum = Dem_NonOBDFFRClassPerDTCMaxNum - (Dem_u08_FFListIndexType)1U;
    frOverwrittenLmt = (Dem_s16_FFListIndexType)0U;

    ffListIndexNum = (Dem_s16_FFListIndexType)tmpFFListIndexNum;

    for( frOverwrittenIndex = ffListIndexNum; frOverwrittenIndex >= frOverwrittenLmt; frOverwrittenIndex-- )                                        /* [GUD:for]frOverwrittenIndex */
    {
        if( Dem_EventDisplacement.FaultRecordOverwritten[frOverwrittenIndex].FaultIndex == Dem_TmpEventMemoryEntry.EventRecord.FaultIndex )         /* [GUD]frOverwrittenIndex */
        {
            Dem_TmpEventMemoryEntry.FaultRecord.RecordNumberIndex[FreezeFrameRecordClassIndex] = Dem_EventDisplacement.FaultRecordOverwritten[frOverwrittenIndex].RecordNumberIndex;    /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex *//* [GUD]frOverwrittenIndex */

            Dem_EventDisplacement.FaultRecordOverwritten[frOverwrittenIndex].FaultIndex = DEM_FAULTINDEX_INITIAL;           /* [GUD]frOverwrittenIndex */
            Dem_EventDisplacement.FaultRecordOverwritten[frOverwrittenIndex].EventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;   /* [GUD]frOverwrittenIndex */
            Dem_EventDisplacement.FaultRecordOverwritten[frOverwrittenIndex].RecordNumberIndex = DEM_FFRECINDEX_INITIAL;    /* [GUD]frOverwrittenIndex */

            Dem_DcEeo_SelectNextNonOBDFFROverwrite();

            retVal = DEM_IRT_OK;
            break;
        }
    }
    if( frOverwrittenIndex < frOverwrittenLmt )
    {
        eeoFaultInfo.EventPriority = Dem_CfgInfoPm_GetEventPriority( Dem_TmpEventMemoryEntry.EventStrgIndex );  /* [GUDCHK:SETVAL]Dem_TmpEventMemoryEntry.EventStrgIndex */
        eeoFaultInfo.StatusOfDTC = Dem_EventDisplacement.DTCStatusForFaultRecordOverwrite;
        eeoFaultInfo.EventStrgIndex = Dem_TmpEventMemoryEntry.EventStrgIndex;
        faultIndex = Dem_DcEeo_GetFaultIndexOfNonOBDFFROverwrite( &eeoFaultInfo );

        eventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;

        resultOfGetEventStrgIndexAndRecNumIndex = Dem_DataMngC_GetFR_EventStrgIndex_RecordNumberIndex( faultIndex, &eventStrgIndex, &recordNumberIndex[0] );    /* [GUD:RET:DEM_IRT_OK] eventStrgIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / 0 */

        if( resultOfGetEventStrgIndexAndRecNumIndex == DEM_IRT_OK )
        {
            nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;

            for( frNotOverwrittenIndex = ffListIndexNum; frNotOverwrittenIndex >= frOverwrittenLmt; frNotOverwrittenIndex-- )   /* [GUD:for]frNotOverwrittenIndex */
            {
                if( recordNumberIndex[frNotOverwrittenIndex] < nonObdFFDRecordNum )                                             /* [GUD]frNotOverwrittenIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / frNotOverwrittenIndex */
                {
                    /* In case the RecordNumberIndex is valid to reuse. */

                    for( frChkOverwrittenIndex = (Dem_u08_FFListIndexType)0U; frChkOverwrittenIndex < FreezeFrameRecordClassIndex; frChkOverwrittenIndex++ )    /* [GUD:for]frChkOverwrittenIndex */
                    {
                        /* Checks if the RecordNumberIndex retained in the fault record which to be overwritten was already used. */
                        if( recordNumberIndex[frNotOverwrittenIndex] == Dem_EventDisplacement.FaultRecordOverwritten[frChkOverwrittenIndex].RecordNumberIndex ) /* [GUD]frNotOverwrittenIndex *//* [GUD]frChkOverwrittenIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / frNotOverwrittenIndex */
                        {
                            /* In case the RecordNumberIndex was already used, try a next RecordNumberIndex retained in the fault record which to be overwritten */

                            break;
                        }

                    }

                    if( frChkOverwrittenIndex >= FreezeFrameRecordClassIndex )
                    {
                        /* In case the RecordNumberIndex is unused, retains FaultRecordOverwritten pointed by the spcified FreezeFrameRecordClassIndex. */

                        Dem_TmpEventMemoryEntry.FaultRecord.RecordNumberIndex[FreezeFrameRecordClassIndex] = recordNumberIndex[frNotOverwrittenIndex];      /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex *//* [GUD]frNotOverwrittenIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / frNotOverwrittenIndex */

                        Dem_EventDisplacement.FaultRecordOverwritten[FreezeFrameRecordClassIndex].FaultIndex = faultIndex;                                      /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */
                        Dem_EventDisplacement.FaultRecordOverwritten[FreezeFrameRecordClassIndex].EventStrgIndex = eventStrgIndex;                              /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */
                        Dem_EventDisplacement.FaultRecordOverwritten[FreezeFrameRecordClassIndex].RecordNumberIndex = recordNumberIndex[frNotOverwrittenIndex]; /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex *//* [GUD]frNotOverwrittenIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / frNotOverwrittenIndex */

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )   /* [FuncSw] */
                        Dem_Data_DeleteTSFFListByFFRTrigger( eventStrgIndex, faultIndex, (Dem_u08_FFListIndexType)frNotOverwrittenIndex, FreezeFrameRecordClassIndex ); /* [GUD]eventStrgIndex *//* [GUD]frNotOverwrittenIndex *//* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )   */

                        Dem_DcEeo_SelectNextNonOBDFFROverwrite();

                        retVal = DEM_IRT_OK;
                    }
                }

                if( retVal == DEM_IRT_OK )
                {
                    break;
                }
            }
        }
    }

    return retVal;
}
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_OFF ) */
#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
/*******************************************************************************/
/* Function Name | Dem_Data_SetNonOBDFFROverwritten                            */
/* Description   | Set fault record which to be overwritten non-OBD freeze     */
/*               | frame records.                                              */
/* Preconditions |                                                             */
/* Parameters    | [in] FreezeFrameRecordClassIndex :                          */
/*               |        The DemFreezeFrameRecordClassRef array's index       */
/*               | [in] FreezeFrameRecordTrigger                               */
/*               |        Trigger corresponding to FreezeFrameRecordClassIndex */
/*               | [in] UpperLimitIsReached                                    */
/*               |        FreezeFrameRecordTrigger's upper limit check result  */
/*               |                                                             */
/* Return Value  | Dem_u08_InternalReturnType                                  */
/*               |        DEM_IRT_OK : Overwriting is possible                 */
/*               |        DEM_IRT_NG : Overwriting is impossible               */
/* Notes         | -                                                           */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/*******************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SetNonOBDFFROverwritten
(
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,      /* [PRMCHK:CALLER] */
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
    VAR( boolean, AUTOMATIC ) UpperLimitIsReached
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetEventStrgIndexAndRecNumIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) recordNumberIndex[DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM];
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) tmpFFListIndexNum;
    VAR( Dem_s16_FFListIndexType, AUTOMATIC ) ffListIndexNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) frChkOverwrittenIndex;
    VAR( Dem_s16_FFListIndexType, AUTOMATIC ) frOverwrittenIndex;
    VAR( Dem_s16_FFListIndexType, AUTOMATIC ) frNotOverwrittenIndex;
    VAR( Dem_s16_FFListIndexType, AUTOMATIC ) frOverwrittenLmt;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_EventEntryOverwriteFaultInfoType, AUTOMATIC ) eeoFaultInfo;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) overwrittenFreezeFrameRecordTrigger;


    retVal = DEM_IRT_NG;

    tmpFFListIndexNum = Dem_NonOBDFFRClassPerDTCMaxNum - (Dem_u08_FFListIndexType)1U;
    frOverwrittenLmt = (Dem_s16_FFListIndexType)0U;

    ffListIndexNum = (Dem_s16_FFListIndexType)tmpFFListIndexNum;

    if ( UpperLimitIsReached == (boolean)FALSE )
    {
        for( frOverwrittenIndex = ffListIndexNum; frOverwrittenIndex >= frOverwrittenLmt; frOverwrittenIndex-- )                                                                                    /* [GUD:for]frOverwrittenIndex */
        {
            if( Dem_Data_CopyEventDisplacement_FaultRecordOverwritten[frOverwrittenIndex].FaultIndex == Dem_TmpEventMemoryEntry.EventRecord.FaultIndex )                                            /* [GUD]frOverwrittenIndex */
            {
                Dem_TmpEventMemoryEntry.FaultRecord.RecordNumberIndex[FreezeFrameRecordClassIndex] = Dem_Data_CopyEventDisplacement_FaultRecordOverwritten[frOverwrittenIndex].RecordNumberIndex;   /* [GUD]frOverwrittenIndex */

                overwrittenFreezeFrameRecordTrigger = Dem_Data_GetTriggerKindOfNonObdFFROverwrittenIndex( Dem_Data_CopyEventDisplacement_FaultRecordOverwritten[frOverwrittenIndex].EventStrgIndex, frOverwrittenIndex );   /* [GUD]frOverwrittenIndex */
                Dem_Data_RemoveLimitReachedTriggerToTmp( overwrittenFreezeFrameRecordTrigger );

                if ( Dem_EventDisplacement.FaultRecordOverwritten[frOverwrittenIndex].FaultIndex == Dem_Data_CopyEventDisplacement_FaultRecordOverwritten[frOverwrittenIndex].FaultIndex )          /* [GUD]frOverwrittenIndex */
                {
                    Dem_EventDisplacement.FaultRecordOverwritten[frOverwrittenIndex].FaultIndex = DEM_FAULTINDEX_INITIAL;                   /* [GUD]frOverwrittenIndex */
                    Dem_EventDisplacement.FaultRecordOverwritten[frOverwrittenIndex].EventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;           /* [GUD]frOverwrittenIndex */
                    Dem_EventDisplacement.FaultRecordOverwritten[frOverwrittenIndex].RecordNumberIndex = DEM_FFRECINDEX_INITIAL;            /* [GUD]frOverwrittenIndex */
                }

                Dem_Data_CopyEventDisplacement_FaultRecordOverwritten[frOverwrittenIndex].FaultIndex = DEM_FAULTINDEX_INITIAL;              /* [GUD]frOverwrittenIndex */
                Dem_Data_CopyEventDisplacement_FaultRecordOverwritten[frOverwrittenIndex].EventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;      /* [GUD]frOverwrittenIndex */
                Dem_Data_CopyEventDisplacement_FaultRecordOverwritten[frOverwrittenIndex].RecordNumberIndex = DEM_FFRECINDEX_INITIAL;       /* [GUD]frOverwrittenIndex */

                Dem_DcEeo_SelectNextNonOBDFFROverwrite();

                retVal = DEM_IRT_OK;

                break;
            }
        }
        if( frOverwrittenIndex < frOverwrittenLmt )
        {
            eeoFaultInfo.EventPriority = Dem_CfgInfoPm_GetEventPriority( Dem_TmpEventMemoryEntry.EventStrgIndex );  /* [GUDCHK:SETVAL]Dem_TmpEventMemoryEntry.EventStrgIndex */
            eeoFaultInfo.StatusOfDTC = Dem_EventDisplacement.DTCStatusForFaultRecordOverwrite;
            eeoFaultInfo.EventStrgIndex = Dem_TmpEventMemoryEntry.EventStrgIndex;
            faultIndex = Dem_DcEeo_GetFaultIndexOfNonOBDFFROverwrite( &eeoFaultInfo );

            eventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;

            resultOfGetEventStrgIndexAndRecNumIndex = Dem_DataMngC_GetFR_EventStrgIndex_RecordNumberIndex( faultIndex, &eventStrgIndex, &recordNumberIndex[0] );    /* [GUD:RET:DEM_IRT_OK] eventStrgIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / 0 */

            if( resultOfGetEventStrgIndexAndRecNumIndex == DEM_IRT_OK )
            {
                nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;

                for( frNotOverwrittenIndex = ffListIndexNum; frNotOverwrittenIndex >= frOverwrittenLmt; frNotOverwrittenIndex-- )   /* [GUD:for]frNotOverwrittenIndex */
                {
                    if( recordNumberIndex[frNotOverwrittenIndex] < nonObdFFDRecordNum )                                             /* [GUD]frNotOverwrittenIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / frNotOverwrittenIndex */
                    {
                        /* In case the RecordNumberIndex is valid to reuse. */

                        for( frChkOverwrittenIndex = (Dem_u08_FFListIndexType)0U; frChkOverwrittenIndex < FreezeFrameRecordClassIndex; frChkOverwrittenIndex++ )    /* [GUD:for]frChkOverwrittenIndex */
                        {
                            /* Checks if the RecordNumberIndex retained in the fault record which to be overwritten was already used. */
                            if( recordNumberIndex[frNotOverwrittenIndex] == Dem_EventDisplacement.FaultRecordOverwritten[frChkOverwrittenIndex].RecordNumberIndex ) /* [GUD]frNotOverwrittenIndex *//* [GUD]frChkOverwrittenIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / frNotOverwrittenIndex */
                            {
                                /* In case the RecordNumberIndex was already used, try a next RecordNumberIndex retained in the fault record which to be overwritten */

                                break;
                            }

                        }

                        if( frChkOverwrittenIndex >= FreezeFrameRecordClassIndex )
                        {
                            /* In case the RecordNumberIndex is unused, retains FaultRecordOverwritten pointed by the spcified FreezeFrameRecordClassIndex. */

                            Dem_TmpEventMemoryEntry.FaultRecord.RecordNumberIndex[FreezeFrameRecordClassIndex] = recordNumberIndex[frNotOverwrittenIndex];          /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex *//* [GUD]frNotOverwrittenIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / frNotOverwrittenIndex */

                            overwrittenFreezeFrameRecordTrigger = Dem_Data_GetTriggerKindOfNonObdFFROverwrittenIndex( eventStrgIndex, frNotOverwrittenIndex );      /* [GUD]eventStrgIndex *//* [GUD]frNotOverwrittenIndex */
                            Dem_Data_RemoveLimitReachedTriggerToTmp( overwrittenFreezeFrameRecordTrigger );

                            Dem_EventDisplacement.FaultRecordOverwritten[FreezeFrameRecordClassIndex].FaultIndex = faultIndex;                                      /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */
                            Dem_EventDisplacement.FaultRecordOverwritten[FreezeFrameRecordClassIndex].EventStrgIndex = eventStrgIndex;                              /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */
                            Dem_EventDisplacement.FaultRecordOverwritten[FreezeFrameRecordClassIndex].RecordNumberIndex = recordNumberIndex[frNotOverwrittenIndex]; /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex *//* [GUD]frNotOverwrittenIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / frNotOverwrittenIndex */

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )   /* [FuncSw] */
                            Dem_Data_DeleteTSFFListByFFRTrigger( eventStrgIndex, faultIndex, (Dem_u08_FFListIndexType)frNotOverwrittenIndex, FreezeFrameRecordClassIndex ); /* [GUD]eventStrgIndex *//* [GUD]frNotOverwrittenIndex *//* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )   */

                            Dem_DcEeo_SelectNextNonOBDFFROverwrite();

                            retVal = DEM_IRT_OK;
                        }
                    }

                    if( retVal == DEM_IRT_OK )
                    {
                        break;
                    }
                }
            }
        }
    }
    else
    {
        /* overwrite same trigger FFR */
        retVal = Dem_Data_SetNonOBDFFROverwrittenForSameTrigger( FreezeFrameRecordClassIndex, FreezeFrameRecordTrigger );   /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */
    }

    return retVal;
}



#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_OFF )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SetNonOBDFFROverwritten
(
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex, /* MISRA DEVIATION */
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger, /* MISRA DEVIATION */
    VAR( boolean, AUTOMATIC ) UpperLimitIsReached     /* MISRA DEVIATION */
)
{
    /* This function has no implementation because event displacement is not supported. */

    return DEM_IRT_NG;  /* Returns overwritting is impossible. */
}
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_OFF ) */

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
/*******************************************************************************/
/* Function Name | Dem_Data_SetNonOBDFFROverwrittenForSameTrigger              */
/* Description   | Set fault record which to be overwritten non-OBD freeze     */
/*               | frame records.                                              */
/*               | For Overwriting same trigger FFR.                           */
/* Preconditions |                                                             */
/* Parameters    | [in] FreezeFrameRecordClassIndex :                          */
/*               |        The DemFreezeFrameRecordClassRef array's index       */
/*               | [in] FreezeFrameRecordTrigger                               */
/*               |        Trigger corresponding to FreezeFrameRecordClassIndex */
/*               |                                                             */
/* Return Value  | Dem_u08_InternalReturnType                                  */
/*               |        DEM_IRT_OK : Overwriting is possible                 */
/*               |        DEM_IRT_NG : Overwriting is impossible               */
/* Notes         | -                                                           */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/*******************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SetNonOBDFFROverwrittenForSameTrigger
(
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,      /* [PRMCHK:CALLER] */
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetEventStrgIndexAndRecNumIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) recordNumberIndex[DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM];
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) tmpFFListIndexNum;
    VAR( Dem_s16_FFListIndexType, AUTOMATIC ) ffListIndexNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) frChkOverwrittenIndex;
    VAR( Dem_s16_FFListIndexType, AUTOMATIC ) frOverwrittenIndex;
    VAR( Dem_s16_FFListIndexType, AUTOMATIC ) frNotOverwrittenIndex;
    VAR( Dem_s16_FFListIndexType, AUTOMATIC ) frOverwrittenLmt;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_EventEntryOverwriteFaultInfoType, AUTOMATIC ) eeoFaultInfo;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) overwrittenFreezeFrameRecordTrigger;


    retVal = DEM_IRT_NG;

    tmpFFListIndexNum = Dem_NonOBDFFRClassPerDTCMaxNum - (Dem_u08_FFListIndexType)1U;
    frOverwrittenLmt = (Dem_s16_FFListIndexType)0U;

    ffListIndexNum = (Dem_s16_FFListIndexType)tmpFFListIndexNum;

    for( frOverwrittenIndex = ffListIndexNum; frOverwrittenIndex >= frOverwrittenLmt; frOverwrittenIndex-- )    /* [GUD:for]frOverwrittenIndex */
    {
        if( Dem_Data_CopyEventDisplacement_FaultRecordOverwritten[frOverwrittenIndex].FaultIndex == Dem_TmpEventMemoryEntry.EventRecord.FaultIndex )    /* [GUD]frOverwrittenIndex */
        {
            /* need to overwrite same trigger */
            overwrittenFreezeFrameRecordTrigger = Dem_Data_GetTriggerKindOfNonObdFFROverwrittenIndex( Dem_Data_CopyEventDisplacement_FaultRecordOverwritten[frOverwrittenIndex].EventStrgIndex, frOverwrittenIndex );   /* [GUD]frOverwrittenIndex */
            if ( overwrittenFreezeFrameRecordTrigger == FreezeFrameRecordTrigger )
            {
                Dem_TmpEventMemoryEntry.FaultRecord.RecordNumberIndex[FreezeFrameRecordClassIndex] = Dem_Data_CopyEventDisplacement_FaultRecordOverwritten[frOverwrittenIndex].RecordNumberIndex;   /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex *//* [GUD]frOverwrittenIndex */

                if ( Dem_EventDisplacement.FaultRecordOverwritten[frOverwrittenIndex].FaultIndex == Dem_Data_CopyEventDisplacement_FaultRecordOverwritten[frOverwrittenIndex].FaultIndex )          /* [GUD]frOverwrittenIndex */
                {
                    Dem_EventDisplacement.FaultRecordOverwritten[frOverwrittenIndex].FaultIndex = DEM_FAULTINDEX_INITIAL;                                       /* [GUD]frOverwrittenIndex */
                    Dem_EventDisplacement.FaultRecordOverwritten[frOverwrittenIndex].EventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;                               /* [GUD]frOverwrittenIndex */
                    Dem_EventDisplacement.FaultRecordOverwritten[frOverwrittenIndex].RecordNumberIndex = DEM_FFRECINDEX_INITIAL;                                /* [GUD]frOverwrittenIndex */
                }
                Dem_DcEeo_DisableNonOBDFFROverwrite( Dem_Data_CopyEventDisplacement_FaultRecordOverwritten[frOverwrittenIndex].FaultIndex );                    /* [GUD]frOverwrittenIndex */

                Dem_Data_CopyEventDisplacement_FaultRecordOverwritten[frOverwrittenIndex].FaultIndex = DEM_FAULTINDEX_INITIAL;                                  /* [GUD]frOverwrittenIndex */
                Dem_Data_CopyEventDisplacement_FaultRecordOverwritten[frOverwrittenIndex].EventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;                          /* [GUD]frOverwrittenIndex */
                Dem_Data_CopyEventDisplacement_FaultRecordOverwritten[frOverwrittenIndex].RecordNumberIndex = DEM_FFRECINDEX_INITIAL;                           /* [GUD]frOverwrittenIndex */
                retVal = DEM_IRT_OK;
                break;
            }
        }
    }
    if( frOverwrittenIndex < frOverwrittenLmt )
    {
        eeoFaultInfo.EventPriority = Dem_CfgInfoPm_GetEventPriority( Dem_TmpEventMemoryEntry.EventStrgIndex );  /* [GUDCHK:SETVAL]Dem_TmpEventMemoryEntry.EventStrgIndex */
        eeoFaultInfo.StatusOfDTC = Dem_EventDisplacement.DTCStatusForFaultRecordOverwrite;
        eeoFaultInfo.EventStrgIndex = Dem_TmpEventMemoryEntry.EventStrgIndex;
        faultIndex = Dem_DcEeo_GetFaultIndexOfFFROverwriteFromTrigger( FreezeFrameRecordTrigger, &eeoFaultInfo );
        eventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
        resultOfGetEventStrgIndexAndRecNumIndex = Dem_DataMngC_GetFR_EventStrgIndex_RecordNumberIndex( faultIndex, &eventStrgIndex, &recordNumberIndex[0] );    /* [GUD:RET:DEM_IRT_OK] eventStrgIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / 0 */
        if( resultOfGetEventStrgIndexAndRecNumIndex == DEM_IRT_OK )
        {
            nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;
            for( frNotOverwrittenIndex = ffListIndexNum; frNotOverwrittenIndex >= frOverwrittenLmt; frNotOverwrittenIndex-- )                                   /* [GUD:for]frNotOverwrittenIndex */
            {
                if( recordNumberIndex[frNotOverwrittenIndex] < nonObdFFDRecordNum )                                                                             /* [GUD]frNotOverwrittenIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / frNotOverwrittenIndex */
                {
                    /* In case the RecordNumberIndex is valid to reuse. */
                    for( frChkOverwrittenIndex = (Dem_u08_FFListIndexType)0U; frChkOverwrittenIndex < FreezeFrameRecordClassIndex; frChkOverwrittenIndex++ )    /* [GUD:for]frChkOverwrittenIndex */
                    {
                        /* Checks if the RecordNumberIndex retained in the fault record which to be overwritten was already used. */
                        if( recordNumberIndex[frNotOverwrittenIndex] == Dem_EventDisplacement.FaultRecordOverwritten[frChkOverwrittenIndex].RecordNumberIndex ) /* [GUD]frNotOverwrittenIndex *//* [GUD]frChkOverwrittenIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / frNotOverwrittenIndex */
                        {
                            /* In case the RecordNumberIndex was already used, try a next RecordNumberIndex retained in the fault record which to be overwritten */
                            break;
                        }
                    }
                    if( frChkOverwrittenIndex >= FreezeFrameRecordClassIndex )
                    {
                        /* In case the RecordNumberIndex is unused, retains FaultRecordOverwritten pointed by the spcified FreezeFrameRecordClassIndex. */
                        overwrittenFreezeFrameRecordTrigger = Dem_Data_GetTriggerKindOfNonObdFFROverwrittenIndex( eventStrgIndex, frNotOverwrittenIndex );          /* [GUD]eventStrgIndex *//* [GUD]frNotOverwrittenIndex */
                        if ( overwrittenFreezeFrameRecordTrigger == FreezeFrameRecordTrigger )
                        {
                            Dem_TmpEventMemoryEntry.FaultRecord.RecordNumberIndex[FreezeFrameRecordClassIndex] = recordNumberIndex[frNotOverwrittenIndex];          /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex *//* [GUD]frNotOverwrittenIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / frNotOverwrittenIndex */
                            Dem_EventDisplacement.FaultRecordOverwritten[FreezeFrameRecordClassIndex].FaultIndex = faultIndex;                                      /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */
                            Dem_EventDisplacement.FaultRecordOverwritten[FreezeFrameRecordClassIndex].EventStrgIndex = eventStrgIndex;                              /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */
                            Dem_EventDisplacement.FaultRecordOverwritten[FreezeFrameRecordClassIndex].RecordNumberIndex = recordNumberIndex[frNotOverwrittenIndex]; /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex *//* [GUD]frNotOverwrittenIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / frNotOverwrittenIndex */
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )    /* [FuncSw] */
                            Dem_Data_DeleteTSFFListByFFRTrigger( eventStrgIndex, faultIndex, (Dem_u08_FFListIndexType)frNotOverwrittenIndex, FreezeFrameRecordClassIndex ); /* [GUD]eventStrgIndex *//* [GUD]frNotOverwrittenIndex *//* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */
#endif  /* ( DEM_TSFF_SUPPORT == STD_ON )   */
                            Dem_DcEeo_DisableNonOBDFFROverwrite( faultIndex );
                            retVal = DEM_IRT_OK;
                        }
                    }
                }
                if( retVal == DEM_IRT_OK )
                {
                    break;
                }
            }
        }
    }
    return retVal;
}
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_GetTriggerKindOfNonObdFFROverwrittenIndex       */
/* Description   | none                                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] eventStrgIndex :                                    */
/*               | [in] frOverwrittenIndex :                                */
/* Return Value  | Dem_u08_StorageTriggerType :                             */
/*               |          Trigger Of overwritten target freeze frame      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-10-0     | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_StorageTriggerType, AUTOMATIC ) Dem_Data_GetTriggerKindOfNonObdFFROverwrittenIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_s16_FFListIndexType, AUTOMATIC ) FrOverwrittenIndex        /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) overwrittenFreezeFrameRecordTrigger;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) overwrittenFreezeFrameRecordClassIndex;
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) overwrittenFreezeFrameClassRef;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) overwrittenFreezeFrameRecNumClassRef;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) ffrRecordClassConfigureNum;

    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) overwrittenFreezeFrameRecNumClassPtr;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;
    ffrRecordClassConfigureNum  = Dem_FFRRecordClassConfigureNum;
    overwrittenFreezeFrameRecordTrigger = DEM_TRIGGER_ON_NONE;

    if ( EventStrgIndex < eventStorageNum )                                                                 /* [GUD:if]EventStrgIndex */
    {
        Dem_CfgInfoPm_GetFreezeFrameAndRecNumClass( EventStrgIndex, &overwrittenFreezeFrameClassRef, &overwrittenFreezeFrameRecNumClassRef);    /* [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] overwrittenFreezeFrameClassRef *//* [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] overwrittenFreezeFrameRecNumClassRef */
        if( overwrittenFreezeFrameRecNumClassRef != DEM_FFRECNUMCLASSINDEX_INVALID )                                                            /* [GUD:if] overwrittenFreezeFrameRecNumClassRef */
        {
            overwrittenFreezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[overwrittenFreezeFrameRecNumClassRef];                      /* [GUD] overwrittenFreezeFrameRecNumClassRef *//* [GUD:CFG:IF_GUARDED: overwrittenFreezeFrameRecNumClassRef ]overwrittenFreezeFrameRecNumClassPtr */
            overwrittenFreezeFrameRecordClassIndex = overwrittenFreezeFrameRecNumClassPtr->DemFreezeFrameRecordClassRef[FrOverwrittenIndex];    /* [GUD] overwrittenFreezeFrameRecNumClassPtr *//* [GUDCHK:CALLER]FrOverwrittenIndex *//* [ARYCHK] DEM_FF_RECORD_CLASS_REF_MAX_NUM / 1 / FrOverwrittenIndex */
            if( overwrittenFreezeFrameRecordClassIndex < ffrRecordClassConfigureNum )                                                           /* [GUD:if] overwrittenFreezeFrameRecordClassIndex */
            {
                overwrittenFreezeFrameRecordTrigger =   Dem_CfgInfoPm_GetFreezeFrameRecordTriggerType( overwrittenFreezeFrameRecordClassIndex );    /* [GUD] overwrittenFreezeFrameRecordClassIndex */
            }
        }
    }

    return overwrittenFreezeFrameRecordTrigger;
}

/****************************************************************************/
/* Function Name | Dem_Data_RemoveLimitReachedTriggerToTmp                  */
/* Description   | Remove Limit Reached Trigger To Tmp                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] targetTrigger :                                     */
/* Return Value  | void                                                     */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_RemoveLimitReachedTriggerToTmp
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) TargetTrigger
)
{
    if ( TargetTrigger == DEM_TRIGGER_ON_CONFIRMED )
    {
        Dem_TmpUpperLimitReachedTrigger &= ( ~DEM_VALID_TRIGGER_CONFIRMED );
    }
    else if( TargetTrigger == DEM_TRIGGER_ON_FDC_THRESHOLD )
    {
        Dem_TmpUpperLimitReachedTrigger &= ( ~DEM_VALID_TRIGGER_FDC_THRESHOLD );
    }
    else if( TargetTrigger == DEM_TRIGGER_ON_PENDING )
    {
        Dem_TmpUpperLimitReachedTrigger &= ( ~DEM_VALID_TRIGGER_PENDING );
    }
    else if( TargetTrigger == DEM_TRIGGER_ON_TEST_FAILED_THIS_OPERATION_CYCLE )
    {
        Dem_TmpUpperLimitReachedTrigger &= ( ~DEM_VALID_TRIGGER_TFTOC );
    }
    else
    {
        /* No Process */
    }
    return ;
}
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_Data_CheckUpperLimitIsReached                        */
/* Description   | Upper limit check for target trigger                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] TargetTrigger :                                     */
/*               |           Upper limit check target                       */
/* Return Value  | boolean                                                  */
/*               |      TRUE  : Upper limit is reached                      */
/*               |      FALSE : Upper limit is not reached                  */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Data_CheckUpperLimitIsReached
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) TargetTrigger
)
{
    VAR( boolean, AUTOMATIC ) retVal;

    retVal = (boolean)FALSE;

    if ( TargetTrigger == DEM_TRIGGER_ON_CONFIRMED )
    {
        if ( ( Dem_TmpUpperLimitReachedTrigger & DEM_VALID_TRIGGER_CONFIRMED ) != DEM_VALID_TRIGGER_NONE )
        {
            retVal = (boolean)TRUE;
        }
    }
    else if( TargetTrigger == DEM_TRIGGER_ON_FDC_THRESHOLD )
    {
        if ( ( Dem_TmpUpperLimitReachedTrigger & DEM_VALID_TRIGGER_FDC_THRESHOLD ) != DEM_VALID_TRIGGER_NONE )
        {
            retVal = (boolean)TRUE;
        }
    }
    else if( TargetTrigger == DEM_TRIGGER_ON_PENDING )
    {
        if ( ( Dem_TmpUpperLimitReachedTrigger & DEM_VALID_TRIGGER_PENDING ) != DEM_VALID_TRIGGER_NONE )
        {
            retVal = (boolean)TRUE;
        }
    }
    else if( TargetTrigger == DEM_TRIGGER_ON_TEST_FAILED_THIS_OPERATION_CYCLE )
    {
        if ( ( Dem_TmpUpperLimitReachedTrigger & DEM_VALID_TRIGGER_TFTOC ) != DEM_VALID_TRIGGER_NONE )
        {
            retVal = (boolean)TRUE;
        }
    }
    else
    {
        /* No Process */
    }
    return retVal;
}
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */
#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_OFF )
static FUNC( boolean, DEM_CODE ) Dem_Data_CheckUpperLimitIsReached
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) TargetTrigger /* MISRA DEVIATION */
)
{
    return (boolean)FALSE; /* Always FALSE */
}
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_OFF ) */

/****************************************************************************/
/* Function Name | Dem_Data_UpdateTriggerToTmp                              */
/* Description   | none                                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] TargetTrigger :                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_UpdateTriggerToTmp
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) TargetTrigger
)
{
    switch( TargetTrigger )
    {
        case DEM_TRIGGER_ON_CONFIRMED:
            Dem_TmpEventMemoryEntry.Trigger |= DEM_VALID_TRIGGER_CONFIRMED;
            break;

        case DEM_TRIGGER_ON_FDC_THRESHOLD:
            Dem_TmpEventMemoryEntry.Trigger |= DEM_VALID_TRIGGER_FDC_THRESHOLD;
            break;

        case DEM_TRIGGER_ON_PENDING:
            Dem_TmpEventMemoryEntry.Trigger |= DEM_VALID_TRIGGER_PENDING;
            break;

        case DEM_TRIGGER_ON_TEST_FAILED_THIS_OPERATION_CYCLE:
            Dem_TmpEventMemoryEntry.Trigger |= DEM_VALID_TRIGGER_TFTOC;
            break;

        default:
            /* No process */
            break;
    }

    return;
}

#if ( DEM_OBDONUDS_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_CopyObdFFRecordIndexToTmpFromPairMisfireEvent   */
/* Description   | Copy obd freeze frame record index to temporary data fr- */
/*               | om pair misfire event and, if copied, determine whether- */
/*               |   capture of obd freeze frame is necessary.              */
/* Preconditions | CaptureFlgPtr is set to TRUE on the caller.              */
/* Parameters    | [in] FreezeFrameRecordClassIndex :                       */
/*               |        The DemFreezeFrameRecordClassRef array's index    */
/*               | [in] FreezeFrameRecordUpdate :                           */
/*               |        Update setting value of obd freeze frame          */
/*               | [in] Trigger :                                           */
/*               |        The trigger for capture                           */
/*               | [in] CaptureFlgPtr :                                     */
/*               |      Flag to determine whether to capture obd freeze fr- */
/*               |      ame                                                 */
/* Return Value  | boolean                                                  */
/*               |      TRUE  : Copied obd freeze frame record index        */
/*               |      FALSE : Do not copy obd freeze frame record index   */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Data_CopyObdFFRecordIndexToTmpFromPairMisfireEvent
(
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,  /* [PRMCHK:CALLER] */
    VAR( Dem_u08_UpdateRecordType, AUTOMATIC ) FreezeFrameRecordUpdate,
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) Trigger,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) CaptureFlgPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfirePairEventStrgIndex;
    VAR( boolean, AUTOMATIC ) retCopyFromPairMisfireEvent;
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetMisfirePairEvent;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) pairFaultIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) pairObdFreezeFrameIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;

    retCopyFromPairMisfireEvent = (boolean)FALSE;

    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( Dem_TmpEventMemoryEntry.EventStrgIndex );    /* [GUDCHK:SETVAL]Dem_TmpEventMemoryEntry.EventStrgIndex */
    if( misfireEventKind == (boolean)TRUE )
    {
        resultGetMisfirePairEvent= Dem_CfgInfoPm_GetMisfirePairEventStrgIndexByStrgIndex( Dem_TmpEventMemoryEntry.EventStrgIndex, &misfirePairEventStrgIndex );
        if( resultGetMisfirePairEvent == DEM_IRT_OK )
        {
            resultOfGetFaultIndex = Dem_DataMngC_GetER_FaultIndex( misfirePairEventStrgIndex, &pairFaultIndex );    /* [GUD:RET:DEM_IRT_OK] misfirePairEventStrgIndex */
            if( resultOfGetFaultIndex == DEM_IRT_OK )
            {
                failRecordNum = Dem_FailRecordNum;
                if( pairFaultIndex < failRecordNum )    /* [GUD:if] pairFaultIndex */
                {
                    pairObdFreezeFrameIndex = DEM_FFRECINDEX_INITIAL;
                    (void)Dem_DataMngC_GetFR_ObdFreezeFrameIndex( pairFaultIndex, FreezeFrameRecordClassIndex, &pairObdFreezeFrameIndex );  /* no return check required */  /* [GUD]pairFaltIndex *//* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */
                    obdFFDRecordNum = Dem_CfgInfoPm_GetObdFFDRecordNum();
                    if( pairObdFreezeFrameIndex < obdFFDRecordNum )
                    {
                        Dem_TmpEventMemoryEntry.FaultRecord.ObdRecordNumberIndex[FreezeFrameRecordClassIndex] = pairObdFreezeFrameIndex; /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */
                        if( FreezeFrameRecordUpdate == DEM_UPDATE_RECORD_NO )
                        {
                            /* first OBD FFD */
                            *CaptureFlgPtr = (boolean)FALSE;
                        }
                        else
                        {
                            /* latest OBD FFD */
                            *CaptureFlgPtr = Dem_Data_JudgeCaptureMisfireLatestObdFFD( Trigger );

                        }
                        retCopyFromPairMisfireEvent = (boolean)TRUE;
                    }
                }
            }
        }
    }

    return retCopyFromPairMisfireEvent;
}

/****************************************************************************/
/* Function Name | Dem_Data_JudgeUpdateLatestObdFFD                         */
/* Description   | Judge whether to update latest obd freeze frame          */
/* Preconditions |                                                          */
/* Parameters    | [in] Trigger :                                           */
/*               |        The trigger for capture.                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Update                               */
/*               |        DEM_IRT_NG : Don't update                         */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_JudgeUpdateLatestObdFFD
(
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) Trigger
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) retJudgeCaptureMisfireLatestObdFFD;
    VAR( boolean, AUTOMATIC ) misfireEventKind;

    retVal = DEM_IRT_OK;
    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( Dem_TmpEventMemoryEntry.EventStrgIndex );    /* [GUDCHK:SETVAL]Dem_TmpEventMemoryEntry.EventStrgIndex */
    if( misfireEventKind == (boolean)TRUE )
    {
        retJudgeCaptureMisfireLatestObdFFD = Dem_Data_JudgeCaptureMisfireLatestObdFFD( Trigger );
        if ( retJudgeCaptureMisfireLatestObdFFD == (boolean)FALSE )
        {
            retVal = DEM_IRT_NG;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Data_JudgeCaptureMisfireLatestObdFFD                 */
/* Description   | Judge whether to capture misfire latest obd freeze frame */
/* Preconditions | Dem_TmpEventMemoryEntry.EventStrgIndex is misfire event  */
/* Parameters    | [in] Trigger :                                           */
/*               |        The trigger for capture.                          */
/* Return Value  | boolean                                                  */
/*               |      TRUE  : Capture                                     */
/*               |      FALSE : Don't capture                               */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Data_JudgeCaptureMisfireLatestObdFFD
(
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) Trigger
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfirePairEventStrgIndex;
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC )   pairExtendStatusOfDTC2;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) pairStatusOfDTC;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) pairFaultIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( boolean, AUTOMATIC ) retJudgeCaptureMisfireLatestObdFFD;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetMisfirePairEvent;

    retJudgeCaptureMisfireLatestObdFFD = (boolean)FALSE;

    resultGetMisfirePairEvent= Dem_CfgInfoPm_GetMisfirePairEventStrgIndexByStrgIndex( Dem_TmpEventMemoryEntry.EventStrgIndex, &misfirePairEventStrgIndex );
    if( resultGetMisfirePairEvent == DEM_IRT_OK )
    {
        pairExtendStatusOfDTC2 = DEM_DTCSTATUSEX2_BYTE_ALL_OFF;
        (void)Dem_DataMngC_GetER_ExtendDTCStatus2( misfirePairEventStrgIndex, &pairExtendStatusOfDTC2 );    /* no return check required */
        pairStatusOfDTC = DEM_DTCSTATUS_BYTE_DEFAULT;
        (void)Dem_DataMngC_GetER_StatusOfDTC( misfirePairEventStrgIndex, &pairStatusOfDTC );    /* no return check required */

        if( ( pairExtendStatusOfDTC2 & DEM_DTCSTATUSEX2_STATUS_TFTOC_IN_FAILURECYCLE ) != DEM_DTCSTATUSEX2_STATUS_TFTOC_IN_FAILURECYCLE )
        {
            /* pair misfire event bit1 Off No failure within the same cycle */

            retJudgeCaptureMisfireLatestObdFFD = (boolean)TRUE;

            if( ( pairStatusOfDTC & DEM_UDS_STATUS_PDTC ) == DEM_UDS_STATUS_PDTC )
            {
                /* pair misfire event bit2 On */
                if( ( pairStatusOfDTC & DEM_UDS_STATUS_CDTC ) != DEM_UDS_STATUS_CDTC )
                {
                    /* pair misfire event bit3 Off */
                    statusOfDTC = DEM_DTCSTATUS_BYTE_DEFAULT;
                    (void)Dem_DataMngC_GetER_StatusOfDTC( Dem_TmpEventMemoryEntry.EventStrgIndex, &statusOfDTC );    /* no return check required */
                    if( ( statusOfDTC & DEM_UDS_STATUS_CDTC ) != DEM_UDS_STATUS_CDTC )
                    {
                        /* misfire event bit3 Off */
                        if( ( Trigger & DEM_VALID_TRIGGER_CONFIRMED ) != DEM_VALID_TRIGGER_CONFIRMED )
                        {
                            /* Target event is not confirmed failure */
                            retJudgeCaptureMisfireLatestObdFFD = (boolean)FALSE;
                        }
                    }
                }
            }
        }
        else
        {
            /*  bit1 On Failure in the same cycle */

            resultOfGetFaultIndex = Dem_DataMngC_GetER_FaultIndex( misfirePairEventStrgIndex, &pairFaultIndex );    /* [GUD:RET:DEM_IRT_OK] misfirePairEventStrgIndex */
            if( resultOfGetFaultIndex == DEM_IRT_OK )
            {
                failRecordNum = Dem_FailRecordNum;
                if( pairFaultIndex < failRecordNum )    /* [GUD:if] pairFaultIndex */
                {
                    if( ( pairStatusOfDTC & DEM_UDS_STATUS_CDTC ) != DEM_UDS_STATUS_CDTC )
                    {
                        /* bit3 Off */
                        if( ( Trigger & DEM_VALID_TRIGGER_CONFIRMED ) == DEM_VALID_TRIGGER_CONFIRMED )
                        {
                            /* Target event is confirmed failure */
                            retJudgeCaptureMisfireLatestObdFFD = (boolean)TRUE;
                        }
                    }
                }
                else
                {
                    retJudgeCaptureMisfireLatestObdFFD = (boolean)TRUE;
                }
            }
        }
    }

    return retJudgeCaptureMisfireLatestObdFFD;
}
#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON ) */
#endif /* ( DEM_OBDONUDS_SUPPORT == STD_ON ) */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
