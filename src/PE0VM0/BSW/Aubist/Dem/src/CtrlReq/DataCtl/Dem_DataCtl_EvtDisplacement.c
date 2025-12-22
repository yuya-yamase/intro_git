/* Dem_DataCtl_EvtDisplacement_c(v5-10-0)                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_EvtDisplacement/CODE                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_Data_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_DataEeo.h"
#include "../../../inc/Dem_Pm_DataOeo.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Rc_OdrLst.h"

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
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
static FUNC( boolean, DEM_CODE ) Dem_Data_ChkOverwriteFaultRecord
( void );

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( boolean, DEM_CODE ) Dem_Data_ChkOverwriteOBDFFR
( void );
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )      */

static FUNC( boolean, DEM_CODE ) Dem_Data_ChkOverwriteFFR
( void );

static FUNC( void, DEM_CODE ) Dem_Data_SelectNonOBDFFROverwrite
(
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) FaultRecordPtr,
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) EventEntryOverwritePtr
);
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_SelectOBDFFROverwrite
(
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) FaultRecordPtr,
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) EventEntryOverwritePtr
);
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )      */

#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    */

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

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_SelectEventEntryOverwrite                       */
/* Description   | Select Event Entry Overwrite                             */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_SelectEventEntryOverwrite
(void)
{
    VAR( boolean, AUTOMATIC ) chkOverwriteFaultRecord;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /* [FuncSw] */
    VAR( boolean, AUTOMATIC ) chkOverwriteOBDFFR;
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )          */
    VAR( boolean, AUTOMATIC ) chkOverwriteFFR;

    VAR( boolean, AUTOMATIC ) chkOverwriteCondition;

    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) loopFaultOrderList;

    VAR( Dem_u08_InternalReturnType, AUTOMATIC )                  retGetFaultRecord;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_FaultRecordPtrForCtlType, AUTOMATIC ) faultRecordPtrCtl;

    VAR( Dem_EventEntryOverwriteType, AUTOMATIC ) eventEntryOverwrite;

    /* Initialize */
    Dem_DcEeo_InitializeFaultRecordOverwrite();
    Dem_DcEeo_InitializeNonOBDFFROverwrite();

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )  /* [FuncSw] */
    Dem_DcEeo_InitializeNonOBDFFROverwriteForEachTrigger();
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /* [FuncSw] */
    Dem_DcEeo_InitializeOBDFFROverwrite();
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

    /* Check the need to select overwrite target */
    chkOverwriteFaultRecord = Dem_Data_ChkOverwriteFaultRecord();
    chkOverwriteCondition   =   chkOverwriteFaultRecord;        /*  overwrite condition     TRUE : overwrite    */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /* [FuncSw] */
    chkOverwriteOBDFFR      = Dem_Data_ChkOverwriteOBDFFR();
    chkOverwriteCondition   =   chkOverwriteCondition | chkOverwriteOBDFFR;     /*  overwrite condition     TRUE : overwrite    */
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )          */

    chkOverwriteFFR         = Dem_Data_ChkOverwriteFFR();
    chkOverwriteCondition   =   chkOverwriteCondition | chkOverwriteFFR;        /*  overwrite condition     TRUE : overwrite    */

    if ( chkOverwriteCondition == (boolean)TRUE )
    {
#if ( DEM_OBDONEDS_SUPPORT == STD_ON )  /* [FuncSw] */
        Dem_DcOeo_SetEdsOBDFFDTarget();
#endif  /* ( DEM_OBDONEDS_SUPPORT == STD_ON ) */
        /* Loop processing for FaultOrderList */
        failRecordNum = (Dem_u08_OrderIndexType)Dem_FailRecordNum;
        for( loopFaultOrderList = (Dem_u08_OrderIndexType)0U; loopFaultOrderList < failRecordNum; loopFaultOrderList++ )
        {
            /* Get FaultIndex from FaultOrderList */
            (void)Dem_OdrLst_Fault_GetFaultIndexByOrder( loopFaultOrderList, &faultIndex ); /* no return check required */

            /* Use FaultIndex to get FaultRecord from FaultRecordList */
            retGetFaultRecord = Dem_DataMngC_GetFaultRecordAddress( faultIndex, &faultRecordPtrCtl );

            if( retGetFaultRecord == DEM_IRT_OK )
            {
                eventStorageNum =   Dem_PrimaryMemEventStorageNum;
                if ( faultRecordPtrCtl.FaultRecordPtr->EventStrgIndex < eventStorageNum )
                {
                    /* Successful to get FaultRecord */
                    Dem_Data_GetEventPriorityAndStatusOfDTC( faultRecordPtrCtl.FaultRecordPtr->EventStrgIndex, &eventEntryOverwrite );
                    eventEntryOverwrite.FaultIndex = faultIndex;

                    /* Select FaultRecord overwrite target */
                    if( chkOverwriteFaultRecord == (boolean)TRUE )
                    {
                        Dem_DcEeo_SelectFaultRecordOverwrite( &eventEntryOverwrite );   /* [GUD]&eventEntryOverwrite */
                    }

                    /* Select NonOBD FFR overwrite target */
                    if( chkOverwriteFFR == (boolean)TRUE )
                    {
                        Dem_Data_SelectNonOBDFFROverwrite( faultRecordPtrCtl.FaultRecordPtr, &eventEntryOverwrite );    /* [GUD]&eventEntryOverwrite */
                    }

#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
                    /* Select OBD FFR overwrite target */
                    if( chkOverwriteOBDFFR == (boolean)TRUE )
                    {
                        Dem_Data_SelectOBDFFROverwrite( faultRecordPtrCtl.FaultRecordPtr, &eventEntryOverwrite );       /* [GUD]&eventEntryOverwrite */
                    }
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )          */
                }
            }
        }
    }

    return ;
}
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_ChkOverwriteFaultRecord                         */
/* Description   | Check need to select overwrite target of FaultRecord     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |      TRUE  : necessary                                   */
/*               |      FALSE : unnecessary                                 */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Data_ChkOverwriteFaultRecord
(void)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) failRecordNum;

    failRecordNum = (Dem_u08_OrderIndexType)Dem_FailRecordNum;

    retVal = (boolean)TRUE;
    if( Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfEventMemoryEntries < failRecordNum )
    {
        /* FaultRecord is not full */
        retVal = (boolean)FALSE;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Data_ChkOverwriteFFR                                 */
/* Description   | Check need to select overwrite target of nonOBD FFR      */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |      TRUE  : necessary                                   */
/*               |      FALSE : unnecessary                                 */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Data_ChkOverwriteFFR
(void)
{
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordSpaceNum;
    VAR( boolean, AUTOMATIC ) retVal;

    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;

    retVal = (boolean)FALSE;
    if( nonObdFFDRecordNum > (Dem_u08_FFDIndexType)0U )
    {
        nonOBDFFRClassPerDTCMaxNum = (Dem_u08_FFDIndexType)Dem_NonOBDFFRClassPerDTCMaxNum;
        nonObdFFDRecordSpaceNum    = (Dem_u08_FFDIndexType)(nonObdFFDRecordNum - Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfFreezeFrameRecords);
        if( nonObdFFDRecordSpaceNum < nonOBDFFRClassPerDTCMaxNum )
        {
            /* Not enough space to save nonOBD FFD */
            retVal = (boolean)TRUE;
        }

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) /* [FuncSw] */
        if ( Dem_TmpUpperLimitReachedTrigger != DEM_VALID_TRIGGER_NONE )
        {
            /* Reached upper limit of either FFD trigger */
            retVal = (boolean)TRUE;
        }
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */

    }
    else
    {
        /* No need to select overwrite target ,because number of nonOBD FFD record is zero */
    }

    return retVal;
}

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_ChkOverwriteOBDFFR                              */
/* Description   | Check need to select overwrite target of OBD FFR         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |      TRUE  : necessary                                   */
/*               |      FALSE : unnecessary                                 */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Data_ChkOverwriteOBDFFR
(void)
{
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordSpaceNum;
    VAR( boolean, AUTOMATIC ) retVal;

    obdFFDRecordNum = Dem_CfgInfoPm_GetObdFFDRecordNum();

    retVal = (boolean)FALSE;
    if( obdFFDRecordNum > (Dem_u08_FFDIndexType)0U )
    {
        obdFFRClassPerDTCMaxNum = (Dem_u08_FFDIndexType)Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();
        obdFFDRecordSpaceNum    = (Dem_u08_FFDIndexType)(obdFFDRecordNum - Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfObdFreezeFrameRecords);
        if( obdFFDRecordSpaceNum < obdFFRClassPerDTCMaxNum )
        {
            /* Not enough space to save OBD FFD */
            retVal = (boolean)TRUE;
        }
    }
    else
    {
        /* No need to select overwrite target ,because number of OBD FFD record is zero */
    }

    return retVal;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )         */

/****************************************************************************/
/* Function Name | Dem_Data_GetEventPriorityAndStatusOfDTC                  */
/* Description   | Get Event Priority                                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] FaultRecordPtr :                                    */
/*               |        EventStrgIndex                                    */
/* Parameters    | [out] EventEntryOverwritePtr :                           */
/*               |        EventPriority                                     */
/*               |        OrgEventPriority                                  */
/*               |        StatusOfDTC                                       */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_GetEventPriorityAndStatusOfDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) EventEntryOverwritePtr
)
{
    VAR( Dem_u08_EventPriorityType, AUTOMATIC )   eventPriority;
    VAR( Dem_u08_EventPriorityType, AUTOMATIC )   orgEventPriority;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
#if ( DEM_EVENT_DISPLACEMENT_BY_CDTC_NONOBDONLY_SUPPORT == STD_ON ) /* [FuncSw] */
    VAR( boolean, AUTOMATIC ) eventOBDKind;
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_CDTC_NONOBDONLY_SUPPORT == STD_ON )  */
    VAR( boolean, AUTOMATIC ) availableStatus;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    eventPriority = DEM_PRIORITY_EVT_AVL;
    orgEventPriority = DEM_PRIORITY_EVT_AVL;
    statusOfDTC = DEM_DTCSTATUS_BYTE_DEFAULT;
#if ( DEM_EVENT_DISPLACEMENT_BY_CDTC_NONOBDONLY_SUPPORT == STD_ON ) /* [FuncSw] */
    eventOBDKind = (boolean)FALSE;
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_CDTC_NONOBDONLY_SUPPORT == STD_ON )  */
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]EventStrgIndex */
    {
        /* Use EventStrgIndex to get the original event priority from EventParameterTable */
        orgEventPriority = Dem_CfgInfoPm_GetEventPriority( EventStrgIndex );                                /* [GUD]EventStrgIndex */

        /* Get EventAvailable */
        availableStatus = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( EventStrgIndex );                             /* [GUD]EventStrgIndex */

        if( availableStatus == (boolean)TRUE )
        {
            /* Specifies the original event priority. */
            eventPriority = orgEventPriority;
        }

        (void)Dem_DataMngC_GetER_StatusOfDTC( EventStrgIndex, &statusOfDTC );    /* no return check required */

#if ( DEM_EVENT_DISPLACEMENT_BY_CDTC_NONOBDONLY_SUPPORT == STD_ON ) /* [FuncSw] */
        eventOBDKind = Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( EventStrgIndex );
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_CDTC_NONOBDONLY_SUPPORT == STD_ON )  */
    }

    EventEntryOverwritePtr->EventPriority = eventPriority;
    EventEntryOverwritePtr->OrgEventPriority = orgEventPriority;
    EventEntryOverwritePtr->StatusOfDTC = statusOfDTC;
#if ( DEM_EVENT_DISPLACEMENT_BY_CDTC_NONOBDONLY_SUPPORT == STD_ON ) /* [FuncSw] */
    EventEntryOverwritePtr->EventOBDKind = eventOBDKind;
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_CDTC_NONOBDONLY_SUPPORT == STD_ON )  */

    return;
}




/****************************************************************************/
/* Function Name | Dem_Data_SelectNonOBDFFROverwrite                        */
/* Description   | Select non-OBD FFR to overwrite target                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] FaultRecordPtr :                                    */
/*               |        RecordNumberIndex                                 */
/* Parameters    | [in] EventEntryOverwritePtr :                            */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-10-0     | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_SelectNonOBDFFROverwrite
(
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) FaultRecordPtr,
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) EventEntryOverwritePtr
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) loopRecordNumberIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) freezeFrameRecordTrigger;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) freezeFrameRecordClassIndex;
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) freezeFrameClassRef;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) freezeFrameRecNumClassRef;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) ffrRecordClassConfigureNum;

    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecNumClassPtr;

    nonObdFFDRecordNum          = Dem_NonObdFFDRecordNum;
    nonOBDFFRClassPerDTCMaxNum  = Dem_NonOBDFFRClassPerDTCMaxNum;

    for( loopRecordNumberIndex = (Dem_u08_FFListIndexType)0U; loopRecordNumberIndex < nonOBDFFRClassPerDTCMaxNum; loopRecordNumberIndex++ ) /* [GUD:for] loopRecordNumberIndex */
    {
        if( FaultRecordPtr->RecordNumberIndex[loopRecordNumberIndex] < nonObdFFDRecordNum )                                                 /* [GUD] loopRecordNumberIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / loopRecordNumberIndex */
        {
            /* This FaultRecord has NonOBD FFR */
            Dem_CfgInfoPm_GetFreezeFrameAndRecNumClass( FaultRecordPtr->EventStrgIndex, &freezeFrameClassRef, &freezeFrameRecNumClassRef);  /* [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] freezeFrameClassRef *//* [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] freezeframeRecNumClassRef */
            ffrRecordClassConfigureNum  = Dem_FFRRecordClassConfigureNum;
            if( freezeFrameRecNumClassRef != DEM_FFRECNUMCLASSINDEX_INVALID )                                                               /* [GUD:if] freezeFrameRecNumClassRef */
            {
                freezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[freezeFrameRecNumClassRef];                                    /* [GUD] freezeFrameRecNumClassRef */
                freezeFrameRecordClassIndex = freezeFrameRecNumClassPtr->DemFreezeFrameRecordClassRef[loopRecordNumberIndex];               /* [GUD] loopRecordNumberIndex *//* [ARYCHK] DEM_FF_RECORD_CLASS_REF_MAX_NUM / 1 / loopRecordNumberIndex */
                if( freezeFrameRecordClassIndex < ffrRecordClassConfigureNum )                                                              /* [GUD:if] freezeFrameRecordClassIndex */
                {
                    freezeFrameRecordTrigger =  Dem_CfgInfoPm_GetFreezeFrameRecordTriggerType( freezeFrameRecordClassIndex );               /* [GUD] freezeFrameRecordClassIndex */
                }
                else
                {
                    freezeFrameRecordTrigger = DEM_TRIGGER_ON_NONE;
                }
            }
            else
            {
                freezeFrameRecordTrigger = DEM_TRIGGER_ON_NONE;
            }

            Dem_DcEeo_SelectNonOBDFFROverwrite( EventEntryOverwritePtr, freezeFrameRecordTrigger );
        }
    }

    return;
}



/****************************************************************************/
/* Function Name | Dem_Data_SelectOBDFFROverwrite                           */
/* Description   | Select OBD FFR to overwrite target                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] FaultRecordPtr :                                    */
/*               |        ObdRecordNumberIndex                              */
/* Parameters    | [in] EventEntryOverwritePtr :                            */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_SelectOBDFFROverwrite
(
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) FaultRecordPtr,
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) EventEntryOverwritePtr
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) loopRecordNumberIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;

    obdFFDRecordNum         = Dem_CfgInfoPm_GetObdFFDRecordNum();
    obdFFRClassPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();

    for( loopRecordNumberIndex = (Dem_u08_FFListIndexType)0U; loopRecordNumberIndex < obdFFRClassPerDTCMaxNum; loopRecordNumberIndex++ )    /* [GUD:for] loopRecordNumberIndex */
    {
        if( FaultRecordPtr->ObdRecordNumberIndex[loopRecordNumberIndex] < obdFFDRecordNum )                                                 /* [GUD] loopRecordNumberIndex *//* [ARYCHK] DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / loopRecordNumberIndex */
        {
            /* This FaultRecord has OBD FFR */
            Dem_DcEeo_SelectOBDFFROverwrite( EventEntryOverwritePtr );
        }
    }

    return;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
