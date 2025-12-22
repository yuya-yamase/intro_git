/* Dem_DataEeo_c(v5-8-0)                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataEeo/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Pm_DataOeo.h"
#include "../../../inc/Dem_Pm_DataEeo.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Rc_OdrLst.h"
#include "../../../inc/Dem_CmnLib_DTC_DTCStatus.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
/* Return value for Dem_DcEeo_SelectDTCStatusByConfirmedDTC() */
typedef uint8                 Dem_u08_OvwTargetCompareType;
#define DEM_EEO_BOTH_ARE_SAME                                   ((Dem_u08_OvwTargetCompareType)0x00U)
#define DEM_EEO_NEW_IS_HIGH                                     ((Dem_u08_OvwTargetCompareType)0x01U)
#define DEM_EEO_OLD_IS_HIGH                                     ((Dem_u08_OvwTargetCompareType)0x02U)

#if ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )
typedef uint8                 Dem_u08_OvwTargetByConfirmedOrderType;
#define DEM_EEO_OVWTARGET_CANNOT_JUDGE           ((Dem_u08_OvwTargetByConfirmedOrderType)0x00U)
#define DEM_EEO_OVWTARGET_NEWFAULTORDER          ((Dem_u08_OvwTargetByConfirmedOrderType)0x01U)
#define DEM_EEO_OVWTARGET_OLDFAULTORDER          ((Dem_u08_OvwTargetByConfirmedOrderType)0x02U)
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )        */

#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
typedef struct {
    Dem_EventEntryOverwriteType EventEntryOverwrite;
}Dem_FaultRecordOverwriteType;

typedef struct {
    Dem_EventEntryOverwriteType EventEntryOverwrite[DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM];
    Dem_u08_EventEntryOverwriteIndexType EventEntryOverwriteIndex;
}Dem_NonOBDFFROverwriteType;

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
typedef struct {
    Dem_EventEntryOverwriteType EventEntryOverwriteConfirmedTrigger;
    Dem_EventEntryOverwriteType EventEntryOverwriteFDCThresholdTrigger;
    Dem_EventEntryOverwriteType EventEntryOverwritePendingTrigger;
    Dem_EventEntryOverwriteType EventEntryOverwriteTFTOCTrigger;
}Dem_NonOBDFFROverwriteForEachTriggerType;
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
typedef struct {
    Dem_EventEntryOverwriteType EventEntryOverwrite[DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM];
    Dem_u08_EventEntryOverwriteIndexType EventEntryOverwriteIndex;
}Dem_OBDFFROverwriteType;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
static FUNC( boolean, DEM_CODE ) Dem_DcEeo_SelectOverwrite
(
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) NewEventEntryOverwritePtr,
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) OldEventEntryOverwritePtr
);

#if ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )
static FUNC( Dem_u08_OvwTargetCompareType, DEM_CODE ) Dem_DcEeo_JudgePriorityByConfirmedDTCByTarget
(
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) NewEventEntryOverwritePtr,
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) OldEventEntryOverwritePtr
);

static FUNC( Dem_u08_OvwTargetCompareType, DEM_CODE ) Dem_DcEeo_JudgePriorityByConfirmedDTC
(
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) NewEventEntryOverwritePtr,
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) OldEventEntryOverwritePtr
);

static FUNC( Dem_u08_OvwTargetCompareType, DEM_CODE ) Dem_DcEeo_SelectDTCStatusByConfirmedDTC
(
    P2CONST( Dem_EventEntryOverwriteFaultInfoType, AUTOMATIC, AUTOMATIC ) EventEntryOverwriteFaultInfoPtr,
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) TargetEventEntryOverwritePtr
);
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )        */

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_DcEeo_SelectNonOBDFFROverwriteForEachTrigger
(
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) EventEntryOverwritePtr,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC) FreezeFrameRecordTrigger
);
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */

static FUNC( void, DEM_CODE ) Dem_DcEeo_InitializeEventEntryOverwrite
(
    P2VAR( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ) EventEntryOverwritePtr
);

static FUNC( void, DEM_CODE ) Dem_DcEeo_TransferEventEntryOverwrite
(
    P2VAR( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ) DstEventEntryOverwritePtr,
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ) SrcEventEntryOverwritePtr
);

#if ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )
static FUNC( Dem_u08_OvwTargetByConfirmedOrderType, DEM_CODE ) Dem_DcEeo_JudgeOverwriteTargetByConfirmedOrder
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) NewFaultOrderFaultIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) OldFaultOrderFaultIndex
);
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )    */

#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
static VAR( Dem_FaultRecordOverwriteType, DEM_VAR_NO_INIT ) Dem_FaultRecordOverwrite;
static VAR( Dem_NonOBDFFROverwriteType, DEM_VAR_NO_INIT )   Dem_NonOBDFFROverwrite;
#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
static VAR( Dem_NonOBDFFROverwriteForEachTriggerType, DEM_VAR_NO_INIT )   Dem_NonOBDFFROverwriteForEachTrigger;
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static VAR( Dem_OBDFFROverwriteType, DEM_VAR_NO_INIT )      Dem_OBDFFROverwrite;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    */


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DcEeo_Init_AfterRecordCheckComplete                  */
/* Description   | Init process of Dem_DataEeo unit.                        */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DcEeo_Init_AfterRecordCheckComplete
(void)
{
    Dem_DcEeo_InitializeFaultRecordOverwrite();
    Dem_DcEeo_InitializeNonOBDFFROverwrite();
#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )  /* [FuncSw] */
    Dem_DcEeo_InitializeNonOBDFFROverwriteForEachTrigger();
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /* [FuncSw] */
    Dem_DcEeo_InitializeOBDFFROverwrite();
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

    return ;
}


/****************************************************************************/
/* Function Name | Dem_DcEeo_InitializeFaultRecordOverwrite                 */
/* Description   | Initialize of FaultRecordOverwrite                       */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DcEeo_InitializeFaultRecordOverwrite
(void)
{
    Dem_DcEeo_InitializeEventEntryOverwrite( &Dem_FaultRecordOverwrite.EventEntryOverwrite );

    return ;
}


/****************************************************************************/
/* Function Name | Dem_DcEeo_InitializeNonOBDFFROverwrite                   */
/* Description   | Initialize of NonOBD FFROverwrite                        */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DcEeo_InitializeNonOBDFFROverwrite
(void)
{
    VAR( Dem_u08_EventEntryOverwriteIndexType, AUTOMATIC ) loopIndex;
    VAR( Dem_u08_EventEntryOverwriteIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;

    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;

    Dem_NonOBDFFROverwrite.EventEntryOverwriteIndex = (Dem_u08_EventEntryOverwriteIndexType)0U;
    for( loopIndex = (Dem_u08_EventEntryOverwriteIndexType)0U; loopIndex < nonOBDFFRClassPerDTCMaxNum ;loopIndex++ )    /* [GUD:for]loopIndex */
    {
        Dem_DcEeo_InitializeEventEntryOverwrite( &Dem_NonOBDFFROverwrite.EventEntryOverwrite[loopIndex] );              /* [GUD]loopIndex */
    }

    return ;
}

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DcEeo_InitializeNonOBDFFROverwriteForEachTrigger     */
/* Description   | Initialize of NonOBD FFROverwrite                        */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DcEeo_InitializeNonOBDFFROverwriteForEachTrigger
(void)
{
    Dem_DcEeo_InitializeEventEntryOverwrite( &Dem_NonOBDFFROverwriteForEachTrigger.EventEntryOverwriteConfirmedTrigger );
    Dem_DcEeo_InitializeEventEntryOverwrite( &Dem_NonOBDFFROverwriteForEachTrigger.EventEntryOverwriteFDCThresholdTrigger );
    Dem_DcEeo_InitializeEventEntryOverwrite( &Dem_NonOBDFFROverwriteForEachTrigger.EventEntryOverwritePendingTrigger );
    Dem_DcEeo_InitializeEventEntryOverwrite( &Dem_NonOBDFFROverwriteForEachTrigger.EventEntryOverwriteTFTOCTrigger );
    return ;
}
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_DcEeo_InitializeOBDFFROverwrite                      */
/* Description   | Initialize of OBD FFROverwrite                           */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DcEeo_InitializeOBDFFROverwrite
(void)
{
    VAR( Dem_u08_EventEntryOverwriteIndexType, AUTOMATIC ) loopIndex;
    VAR( Dem_u08_EventEntryOverwriteIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;

    obdFFRClassPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();

    Dem_OBDFFROverwrite.EventEntryOverwriteIndex = (Dem_u08_EventEntryOverwriteIndexType)0U;
    for( loopIndex = (Dem_u08_EventEntryOverwriteIndexType)0U; loopIndex < obdFFRClassPerDTCMaxNum ;loopIndex++ )   /* [GUD:for]loopIndex */
    {
        Dem_DcEeo_InitializeEventEntryOverwrite( &Dem_OBDFFROverwrite.EventEntryOverwrite[loopIndex] );             /* [GUD]loopIndex */
    }

    return ;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_DcEeo_SelectFaultRecordOverwrite                     */
/* Description   | Select FaultRecord overwrite target by lower priority    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventEntryOverwritePtr                              */
/*               |        EventPriority                                     */
/*               |        OrgEventPriority                                  */
/*               |        FaultIndex                                        */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DcEeo_SelectFaultRecordOverwrite
(
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) EventEntryOverwritePtr     /* [PRMCHK:CALLER] */
)
{
#if ( DEM_OBD_SUPPORT == STD_ON )   /*  [FuncSw]    */
    VAR( Dem_u08_OBDOverwritePossibilityType, AUTOMATIC ) retCheckOBD;
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )            */
    VAR( boolean, AUTOMATIC ) retCheckEventPriority;
    VAR( Dem_EventEntryOverwriteType, AUTOMATIC ) eventEntryOverwrite;

    Dem_DcEeo_TransferEventEntryOverwrite( (P2VAR( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ))&eventEntryOverwrite, (P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ))EventEntryOverwritePtr );    /* [GUD]&eventEntryOverwrite *//* [GUDCHK:CALLER]EventEntryOverwritePtr */

#if ( DEM_OBD_SUPPORT == STD_ON )   /*  [FuncSw]    */
    /* Set comparison priority from EventEntryOverwrite Priority */
    if( ( eventEntryOverwrite.EventPriority > DEM_PRIORITY_RESERVED_HI_MAX )
     && ( eventEntryOverwrite.EventPriority < DEM_PRIORITY_RESERVED_LO_MIN ) )
    {
        retCheckOBD = Dem_DcOeo_CheckOBDEventOverwritePossibility( eventEntryOverwrite.FaultIndex );
        if( retCheckOBD == DEM_OBDOVW_OVERWRITE_IMPOSSIBLE_BY_OBDFFD )
        {
            /* No overwriting by OBD requirements */
            eventEntryOverwrite.EventPriority = DEM_PRIORITY_OBD_OBDFFD;
        }
        else if( retCheckOBD == DEM_OBDOVW_OVERWRITE_IMPOSSIBLE_BY_MIL )
        {
            /* No overwriting by OBD requirements */
            eventEntryOverwrite.EventPriority = DEM_PRIORITY_OBD_MIL;
        }
        else
        {
            /*  no process.     */
        }
    }
    else
    {
        /* EventEntryOverwrite has higher priority than OBD requirements */
    }
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )            */

    /* Set overwrite target */
    retCheckEventPriority = Dem_DcEeo_SelectOverwrite( &eventEntryOverwrite, &Dem_FaultRecordOverwrite.EventEntryOverwrite );
    if( retCheckEventPriority == (boolean)TRUE )
    {
        /* EventEntryOverwrite has lower priority than current overwrite target */
        Dem_DcEeo_TransferEventEntryOverwrite( (P2VAR( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ))&Dem_FaultRecordOverwrite.EventEntryOverwrite, (P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ))&eventEntryOverwrite ); /* [GUD]&Dem_FaultRecordOverwrite.EventEntryOverwrite *//* [GUD]&eventEntryOverwrite */
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_DcEeo_SelectNonOBDFFROverwrite                       */
/* Description   | Select NonOBD FFR overwrite target by lower priority     */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventEntryOverwritePtr                              */
/*               |        EventPriority                                     */
/*               |        OrgEventPriority                                  */
/*               |        FaultIndex                                        */
/*               | [in] FreezeFrameRecordTrigger                            */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DcEeo_SelectNonOBDFFROverwrite
(
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) EventEntryOverwritePtr,        /* [PRMCHK:CALLER] */
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC) FreezeFrameRecordTrigger /* MISRA DEVIATION */
)
{
    VAR( boolean, AUTOMATIC ) retCheckEventPriority;
    VAR( Dem_u08_EventEntryOverwriteIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_EventEntryOverwriteIndexType, AUTOMATIC ) loopIndex;
    VAR( Dem_u08_EventEntryOverwriteIndexType, AUTOMATIC ) dstIndex;
    VAR( Dem_u08_EventEntryOverwriteIndexType, AUTOMATIC ) srcIndex;

    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;

    /* Set overwrite target */
    for( loopIndex = (Dem_u08_EventEntryOverwriteIndexType)0U ; loopIndex < nonOBDFFRClassPerDTCMaxNum; loopIndex++ )                           /* [GUD:for]loopIndex */
    {
        retCheckEventPriority = Dem_DcEeo_SelectOverwrite( EventEntryOverwritePtr, &Dem_NonOBDFFROverwrite.EventEntryOverwrite[loopIndex] );    /* [GUD]loopIndex */
        if( retCheckEventPriority == (boolean)TRUE )
        {
            /* EventEntryOverwrite has lower priority than current overwrite target */
            for( dstIndex = (Dem_u08_EventEntryOverwriteIndexType)( nonOBDFFRClassPerDTCMaxNum - (Dem_u08_EventEntryOverwriteIndexType)1U ); dstIndex > loopIndex; dstIndex-- ) /* [GUD:for]dstIndex */
            {
                /* Shift current overwrite target array backward */
                srcIndex = (Dem_u08_EventEntryOverwriteIndexType)( dstIndex - (Dem_u08_EventEntryOverwriteIndexType)1U );                                                       /* [GUD:for]srcIndex */
                Dem_DcEeo_TransferEventEntryOverwrite( (P2VAR( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ))&Dem_NonOBDFFROverwrite.EventEntryOverwrite[dstIndex], (P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ))&Dem_NonOBDFFROverwrite.EventEntryOverwrite[srcIndex] );    /* [GUD]dstIndex *//* [GUD]srcIndex *//* [GUD]&Dem_NonOBDFFROverwrite.EventEntryOverwrite[dstIndex] *//* [GUD]&Dem_NonOBDFFROverwrite.EventEntryOverwrite[srcIndex] */
            }

            /* Insert EventEntryOverwrite between current overwrite target arrays */
            Dem_DcEeo_TransferEventEntryOverwrite( (P2VAR( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ))&Dem_NonOBDFFROverwrite.EventEntryOverwrite[loopIndex], (P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ))EventEntryOverwritePtr );  /* [GUD:for]loopIndex *//* [GUD]&Dem_NonOBDFFROverwrite.EventEntryOverwrite[loopIndex] *//* [GUDCHK:CALLER]EventEntryOverwritePtr */

            break;
        }
        else
        {
            /* Next loopIndex */
        }
    }

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )   /* [FuncSw] */
    Dem_DcEeo_SelectNonOBDFFROverwriteForEachTrigger( EventEntryOverwritePtr, FreezeFrameRecordTrigger );
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */

    return ;
}

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DcEeo_SelectOBDFFROverwrite                          */
/* Description   | Select OBD FFR overwrite target by lower priority        */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventEntryOverwritePtr                              */
/*               |        EventPriority                                     */
/*               |        OrgEventPriority                                  */
/*               |        FaultIndex                                        */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DcEeo_SelectOBDFFROverwrite
(
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) EventEntryOverwritePtr     /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_OBDOverwritePossibilityType, AUTOMATIC ) retCheckOBD;
    VAR( boolean, AUTOMATIC ) retCheckEventPriority;
    VAR( Dem_u08_EventEntryOverwriteIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;
    VAR( Dem_u08_EventEntryOverwriteIndexType, AUTOMATIC ) loopIndex;
    VAR( Dem_u08_EventEntryOverwriteIndexType, AUTOMATIC ) dstIndex;
    VAR( Dem_u08_EventEntryOverwriteIndexType, AUTOMATIC ) srcIndex;
    VAR( Dem_EventEntryOverwriteType, AUTOMATIC ) eventEntryOverwrite;

    Dem_DcEeo_TransferEventEntryOverwrite( (P2VAR( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ))&eventEntryOverwrite, (P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ))EventEntryOverwritePtr );    /* [GUD]&eventEntryOverwrite *//* [GUDCHK:CALLER]EventEntryOverwritePtr */

    /* Set comparison priority from EventEntryOverwrite Priority */
    if( ( eventEntryOverwrite.EventPriority > DEM_PRIORITY_RESERVED_HI_MAX )
     && ( eventEntryOverwrite.EventPriority < DEM_PRIORITY_RESERVED_LO_MIN ) )
    {
        retCheckOBD = Dem_DcOeo_CheckOBDEventOverwritePossibility( eventEntryOverwrite.FaultIndex );
        if( retCheckOBD == DEM_OBDOVW_OVERWRITE_IMPOSSIBLE_BY_OBDFFD )
        {
            /* No overwriting by OBD requirements */
            eventEntryOverwrite.EventPriority = DEM_PRIORITY_OBD_OBDFFD;
        }
        else if( retCheckOBD == DEM_OBDOVW_OVERWRITE_IMPOSSIBLE_BY_MIL )
        {
            /* No overwriting by OBD requirements */
            eventEntryOverwrite.EventPriority = DEM_PRIORITY_OBD_MIL;
        }
        else
        {
            /*  no process.     */
        }
    }
    else
    {
        /* EventEntryOverwrite has higher priority than OBD requirements */
    }

    obdFFRClassPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();

    /* Set overwrite target */
    for( loopIndex = (Dem_u08_EventEntryOverwriteIndexType)0U ; loopIndex < obdFFRClassPerDTCMaxNum; loopIndex++ )                          /* [GUD:for]loopIndex */
    {
        retCheckEventPriority = Dem_DcEeo_SelectOverwrite( &eventEntryOverwrite, &Dem_OBDFFROverwrite.EventEntryOverwrite[loopIndex] );     /* [GUD]loopIndex */
        if( retCheckEventPriority == (boolean)TRUE )
        {
            /* EventEntryOverwrite has lower priority than current overwrite target */
            for( dstIndex = (Dem_u08_EventEntryOverwriteIndexType)( obdFFRClassPerDTCMaxNum - (Dem_u08_EventEntryOverwriteIndexType)1U ); dstIndex > loopIndex; dstIndex-- )    /* [GUD:for]dstIndex */
            {
                /* Shift current overwrite target array backward */
                srcIndex = (Dem_u08_EventEntryOverwriteIndexType)( dstIndex - (Dem_u08_EventEntryOverwriteIndexType)1U );                                                       /* [GUD:for]srcIndex */
                Dem_DcEeo_TransferEventEntryOverwrite( (P2VAR( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ))&Dem_OBDFFROverwrite.EventEntryOverwrite[dstIndex], (P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ))&Dem_OBDFFROverwrite.EventEntryOverwrite[srcIndex] );  /* [GUD]dstIndex *//* [GUD]srcIndex */
            }

            /* Insert EventEntryOverwrite between current overwrite target arrays */
            Dem_DcEeo_TransferEventEntryOverwrite( (P2VAR( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ))&Dem_OBDFFROverwrite.EventEntryOverwrite[loopIndex], (P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ))&eventEntryOverwrite );   /* [GUD]loopIndex */
            break;
        }
        else
        {
            /* Next loopIndex */
        }
    }

    return ;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_DcEeo_GetFaultIndexOfFaultRecordOverwrite            */
/* Description   | Get FaultIndex Of FaultRecord Overwrite                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventEntryOverwriteFaultInfoPtr :                   */
/*               |          EventPriority                                   */
/*               |          StatusOfDTC                                     */
/* Return Value  | Dem_u08_FaultIndexType                                   */
/*               |      The index of corresponding to fault record list.    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_FaultIndexType, DEM_CODE ) Dem_DcEeo_GetFaultIndexOfFaultRecordOverwrite
(
    P2CONST( Dem_EventEntryOverwriteFaultInfoType, AUTOMATIC, AUTOMATIC ) EventEntryOverwriteFaultInfoPtr
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
#if ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )   /*  [FuncSw]    */
    VAR( Dem_u08_OvwTargetCompareType, AUTOMATIC ) resultOfSelect;
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )        */

    faultIndex = DEM_FAULTINDEX_INITIAL;
    if( EventEntryOverwriteFaultInfoPtr->EventPriority < Dem_FaultRecordOverwrite.EventEntryOverwrite.EventPriority )
    {
        /* EventPriority has higher priority than current overwrite target */
        faultIndex = Dem_FaultRecordOverwrite.EventEntryOverwrite.FaultIndex;
    }
    else if( EventEntryOverwriteFaultInfoPtr->EventPriority == Dem_FaultRecordOverwrite.EventEntryOverwrite.EventPriority )
    {
        /* EventPriority has the same priority as the current overwrite target */

#if ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )   /*  [FuncSw]    */
        resultOfSelect = Dem_DcEeo_SelectDTCStatusByConfirmedDTC( EventEntryOverwriteFaultInfoPtr, &Dem_FaultRecordOverwrite.EventEntryOverwrite );
        if( resultOfSelect == DEM_EEO_NEW_IS_HIGH )
        {
            /* new event's confirmedDTC is on, and old event's confirmedDTC is off. */
            faultIndex = Dem_FaultRecordOverwrite.EventEntryOverwrite.FaultIndex;
        }
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )        */
    }
    else
    {
        /* EventPriority has lower priority than current overwrite target */
        /* No process */
    }

    return faultIndex;
}


/****************************************************************************/
/* Function Name | Dem_DcEeo_GetFaultIndexOfNonOBDFFROverwrite              */
/* Description   | Get FaultIndex Of NonOBD FFR Overwrite                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventEntryOverwriteFaultInfoPtr :                   */
/*               |          EventPriority                                   */
/*               |          StatusOfDTC                                     */
/* Return Value  | Dem_u08_FaultIndexType                                   */
/*               |      The index of corresponding to fault record list.    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_FaultIndexType, DEM_CODE ) Dem_DcEeo_GetFaultIndexOfNonOBDFFROverwrite
(
    P2CONST( Dem_EventEntryOverwriteFaultInfoType, AUTOMATIC, AUTOMATIC ) EventEntryOverwriteFaultInfoPtr
)
{
    VAR( Dem_u08_EventEntryOverwriteIndexType, AUTOMATIC ) overwriteIndex;
    VAR( Dem_u08_EventEntryOverwriteIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_EventPriorityType, AUTOMATIC ) overwritePriority;
#if ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )   /*  [FuncSw]    */
    VAR( Dem_u08_OvwTargetCompareType, AUTOMATIC ) resultOfSelect;
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )        */
#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )  /* [FuncSw] */
    VAR( Dem_u08_EventEntryOverwriteIndexType, AUTOMATIC ) startIndex;
    VAR( Dem_u08_EventEntryOverwriteIndexType, AUTOMATIC ) loopIndex;
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */

    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;
    faultIndex = DEM_FAULTINDEX_INITIAL;
    overwriteIndex = Dem_NonOBDFFROverwrite.EventEntryOverwriteIndex;

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) /* [FuncSw] */
    startIndex = overwriteIndex;
    for( loopIndex = startIndex; loopIndex < (Dem_u08_EventEntryOverwriteIndexType)nonOBDFFRClassPerDTCMaxNum; loopIndex++ )    /* [GUD:for]loopIndex */
    {
        if ( Dem_NonOBDFFROverwrite.EventEntryOverwrite[loopIndex].FaultIndex == DEM_FAULTINDEX_INITIAL )                       /* [GUD]loopIndex */
        {
            Dem_DcEeo_SelectNextNonOBDFFROverwrite();
            overwriteIndex = Dem_NonOBDFFROverwrite.EventEntryOverwriteIndex;
        }
        else
        {
            break;
        }
    }
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */

    if( overwriteIndex < nonOBDFFRClassPerDTCMaxNum )                                                                           /* [GUD:if]overwriteIndex */
    {
        overwritePriority = Dem_NonOBDFFROverwrite.EventEntryOverwrite[overwriteIndex].EventPriority;                           /* [GUD]overwriteIndex */

        if( EventEntryOverwriteFaultInfoPtr->EventPriority < overwritePriority )
        {
            /* EventPriority has higher priority than current overwrite target */
            faultIndex = Dem_NonOBDFFROverwrite.EventEntryOverwrite[overwriteIndex].FaultIndex;                                 /* [GUD]overwriteIndex */
        }
        else if( EventEntryOverwriteFaultInfoPtr->EventPriority == Dem_NonOBDFFROverwrite.EventEntryOverwrite[overwriteIndex].EventPriority )       /* [GUD]overwriteIndex */
        {
            /* EventPriority has the same priority as the current overwrite target */

#if ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )   /*  [FuncSw]    */
            resultOfSelect = Dem_DcEeo_SelectDTCStatusByConfirmedDTC( EventEntryOverwriteFaultInfoPtr, &Dem_NonOBDFFROverwrite.EventEntryOverwrite[overwriteIndex] );   /* [GUD]overwriteIndex */
            if( resultOfSelect == DEM_EEO_NEW_IS_HIGH )
            {
                /* new event's confirmedDTC is on, and old event's confirmedDTC is off. */
                faultIndex = Dem_NonOBDFFROverwrite.EventEntryOverwrite[overwriteIndex].FaultIndex;                             /* [GUD]overwriteIndex */
            }
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )        */
        }
        else
        {
            /* EventPriority has lower priority than current overwrite target */
            /* No process */
        }
    }

    return faultIndex;
}


/****************************************************************************/
/* Function Name | Dem_DcEeo_SelectNextNonOBDFFROverwrite                   */
/* Description   | Select Next NonOBD FFR Overwrite                         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DcEeo_SelectNextNonOBDFFROverwrite
(void)
{
    VAR( Dem_u08_EventEntryOverwriteIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;

    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;

    if( Dem_NonOBDFFROverwrite.EventEntryOverwriteIndex < nonOBDFFRClassPerDTCMaxNum )
    {
        /* Set current overwrite target to next */
        Dem_NonOBDFFROverwrite.EventEntryOverwriteIndex++;
    }

    return ;
}

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DcEeo_DisableNonOBDFFROverwrite                      */
/* Description   | Disable target NonOBD FFR Overwrite                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] Dem_u08_FaultIndexType :                            */
/*               |       target fault index                                 */
/* Return Value  | void                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DcEeo_DisableNonOBDFFROverwrite
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
)
{
    VAR( Dem_u08_EventEntryOverwriteIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_EventEntryOverwriteIndexType, AUTOMATIC ) loopIndex;
    VAR( Dem_u08_EventEntryOverwriteIndexType, AUTOMATIC ) startIndex;

    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;
    startIndex = Dem_NonOBDFFROverwrite.EventEntryOverwriteIndex;

    for( loopIndex = startIndex; loopIndex < nonOBDFFRClassPerDTCMaxNum; loopIndex++ )                          /* [GUD:for]loopIndex */
    {
        if ( Dem_NonOBDFFROverwrite.EventEntryOverwrite[loopIndex].FaultIndex == FaultIndex )                   /* [GUD]loopIndex */
        {
            Dem_DcEeo_InitializeEventEntryOverwrite( &Dem_NonOBDFFROverwrite.EventEntryOverwrite[loopIndex] );  /* [GUD]loopIndex */
            break;
        }
    }

    return ;
}
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DcEeo_GetFaultIndexOfOBDFFROverwrite                 */
/* Description   | Get FaultIndex Of OBD FFR Overwrite                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventEntryOverwriteFaultInfoPtr :                   */
/*               |          EventPriority                                   */
/*               |          StatusOfDTC                                     */
/* Return Value  | Dem_u08_FaultIndexType                                   */
/*               |      The index of corresponding to fault record list.    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_FaultIndexType, DEM_CODE ) Dem_DcEeo_GetFaultIndexOfOBDFFROverwrite
(
    P2CONST( Dem_EventEntryOverwriteFaultInfoType, AUTOMATIC, AUTOMATIC ) EventEntryOverwriteFaultInfoPtr
)
{
    VAR( Dem_u08_EventEntryOverwriteIndexType, AUTOMATIC ) overwriteIndex;
    VAR( Dem_u08_EventEntryOverwriteIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_EventPriorityType, AUTOMATIC ) overwritePriority;
#if ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )   /*  [FuncSw]    */
    VAR( Dem_u08_OvwTargetCompareType, AUTOMATIC ) resultOfSelect;
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )        */

    obdFFRClassPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();
    faultIndex = DEM_FAULTINDEX_INITIAL;

    overwriteIndex = Dem_OBDFFROverwrite.EventEntryOverwriteIndex;
    if( overwriteIndex < obdFFRClassPerDTCMaxNum )                                                              /* [GUD:if]overwriteIndex */
    {
        overwritePriority = Dem_OBDFFROverwrite.EventEntryOverwrite[overwriteIndex].EventPriority;              /* [GUD]overwriteIndex */

        if( EventEntryOverwriteFaultInfoPtr->EventPriority < overwritePriority )
        {
            /* EventPriority has higher priority than current overwrite target */
            faultIndex = Dem_OBDFFROverwrite.EventEntryOverwrite[overwriteIndex].FaultIndex;                    /* [GUD]overwriteIndex */
        }
        else if( EventEntryOverwriteFaultInfoPtr->EventPriority == Dem_OBDFFROverwrite.EventEntryOverwrite[overwriteIndex].EventPriority )  /* [GUD]overwriteIndex */
        {
            /* EventPriority has the same priority as the current overwrite target */

#if ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )   /*  [FuncSw]    */
            resultOfSelect = Dem_DcEeo_SelectDTCStatusByConfirmedDTC( EventEntryOverwriteFaultInfoPtr, &Dem_OBDFFROverwrite.EventEntryOverwrite[overwriteIndex] );  /* [GUD]overwriteIndex */
            if( resultOfSelect == DEM_EEO_NEW_IS_HIGH )
            {
                /* new event's confirmedDTC is on, and old event's confirmedDTC is off. */
                faultIndex = Dem_OBDFFROverwrite.EventEntryOverwrite[overwriteIndex].FaultIndex;                /* [GUD]overwriteIndex */
            }
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )        */
        }
        else
        {
            /* EventPriority has lower priority than current overwrite target */
            /* No process */
        }
    }

    return faultIndex;
}


/****************************************************************************/
/* Function Name | Dem_DcEeo_SelectNextOBDFFROverwrite                      */
/* Description   | Select Next OBD FFR Overwrite                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DcEeo_SelectNextOBDFFROverwrite
(void)
{
    VAR( Dem_u08_EventEntryOverwriteIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;

    obdFFRClassPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();

    if( Dem_OBDFFROverwrite.EventEntryOverwriteIndex < obdFFRClassPerDTCMaxNum )
    {
        /* Set current overwrite target to next */
        Dem_OBDFFROverwrite.EventEntryOverwriteIndex++;
    }

    return ;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DcEeo_GetFaultIndexOfFFROverwriteFromTrigger         */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] TargetTrigger :                                     */
/* Parameters    | [in] EventEntryOverwriteFaultInfoPtr :                   */
/*               |        new event data                                    */
/* Return Value  | Dem_u08_FaultIndexType :                                 */
/*               |        overwrite target fault index                      */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no branch changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_FaultIndexType, DEM_CODE ) Dem_DcEeo_GetFaultIndexOfFFROverwriteFromTrigger
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) TargetTrigger,
    P2CONST( Dem_EventEntryOverwriteFaultInfoType, AUTOMATIC, AUTOMATIC ) EventEntryOverwriteFaultInfoPtr
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_EventPriorityType, AUTOMATIC ) overwritePriority;
    VAR( Dem_EventEntryOverwriteType, AUTOMATIC ) targetEventEntryOverwrite;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) validTriggerFlg;
#if ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )   /*  [FuncSw]    */
    VAR( Dem_u08_OvwTargetCompareType, AUTOMATIC ) resultOfSelect;
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )        */

    faultIndex = DEM_FAULTINDEX_INITIAL;
    validTriggerFlg = DEM_IRT_OK;

    if ( TargetTrigger == DEM_TRIGGER_ON_CONFIRMED )
    {
        Dem_DcEeo_TransferEventEntryOverwrite( &targetEventEntryOverwrite, &Dem_NonOBDFFROverwriteForEachTrigger.EventEntryOverwriteConfirmedTrigger );
    }
    else if ( TargetTrigger == DEM_TRIGGER_ON_FDC_THRESHOLD )
    {
        Dem_DcEeo_TransferEventEntryOverwrite( &targetEventEntryOverwrite, &Dem_NonOBDFFROverwriteForEachTrigger.EventEntryOverwriteFDCThresholdTrigger );
    }
    else if ( TargetTrigger == DEM_TRIGGER_ON_PENDING )
    {
        Dem_DcEeo_TransferEventEntryOverwrite( &targetEventEntryOverwrite, &Dem_NonOBDFFROverwriteForEachTrigger.EventEntryOverwritePendingTrigger );
    }
    else if ( TargetTrigger == DEM_TRIGGER_ON_TEST_FAILED_THIS_OPERATION_CYCLE )
    {
        Dem_DcEeo_TransferEventEntryOverwrite( &targetEventEntryOverwrite, &Dem_NonOBDFFROverwriteForEachTrigger.EventEntryOverwriteTFTOCTrigger );
    }
    else
    {
        validTriggerFlg = DEM_IRT_NG;
    }

    if ( validTriggerFlg == DEM_IRT_OK )
    {
        overwritePriority = targetEventEntryOverwrite.EventPriority;

        if( EventEntryOverwriteFaultInfoPtr->EventPriority < overwritePriority )
        {
            /* EventPriority has higher priority than current overwrite target */
            faultIndex = targetEventEntryOverwrite.FaultIndex;
        }
        else if( EventEntryOverwriteFaultInfoPtr->EventPriority == targetEventEntryOverwrite.EventPriority )
        {
            /* EventPriority has the same priority as the current overwrite target */

#if ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )   /*  [FuncSw]    */
            resultOfSelect = Dem_DcEeo_SelectDTCStatusByConfirmedDTC( EventEntryOverwriteFaultInfoPtr, &targetEventEntryOverwrite );
            if( resultOfSelect == DEM_EEO_NEW_IS_HIGH )
            {
                /* new event's confirmedDTC is on, and old event's confirmedDTC is off. */
                faultIndex = targetEventEntryOverwrite.FaultIndex;
            }
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )        */
        }
        else
        {
            /* EventPriority has lower priority than current overwrite target */
            /* No process */
        }
    }

    return faultIndex;

}
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */

/****************************************************************************************/
/* Function Name | Dem_DcEeo_GetFaultIndexOfLowestPriorityNonOBDDTCtoStoreFreezeFrame   */
/* Description   |                                                                      */
/* Preconditions | none                                                                 */
/* Parameters    | void                                                                 */
/* Return Value  | Dem_u08_FaultIndexType :                                             */
/*               | lowest priority DTC in freeze frame is stored DTCs                   */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************************/
FUNC( Dem_u08_FaultIndexType, DEM_CODE ) Dem_DcEeo_GetFaultIndexOfLowestPriorityNonOBDDTCtoStoreFreezeFrame
( void )
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) loopFaultOrderList;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_FaultRecordPtrForCtlType, AUTOMATIC ) faultRecordPtrCtl;

    VAR( Dem_EventEntryOverwriteType, AUTOMATIC ) eventEntry;
    VAR( Dem_EventEntryOverwriteType, AUTOMATIC ) minPriorityEventEntry;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( boolean, AUTOMATIC ) freezeCheckResult;
    VAR( boolean, AUTOMATIC ) result;
    VAR( boolean, AUTOMATIC ) obdDTCFlag;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetFaultRecord;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) retfaultIndex;


    failRecordNum = (Dem_u08_OrderIndexType)Dem_FailRecordNum;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;
    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;

    retfaultIndex = (Dem_u08_FaultIndexType)DEM_FAULTINDEX_INITIAL;
    Dem_DcEeo_InitializeEventEntryOverwrite( &minPriorityEventEntry );

    for( loopFaultOrderList = (Dem_u08_OrderIndexType)0U; loopFaultOrderList < failRecordNum; loopFaultOrderList++ )    /* [GUD:for]loopFaultOrderList */
    {
        /* Get FaultIndex from FaultOrderList */
        (void)Dem_OdrLst_Fault_GetFaultIndexByOrder( loopFaultOrderList, &faultIndex ); /* no return check required */
        retGetFaultRecord = Dem_DataMngC_GetFaultRecordAddress( faultIndex, &faultRecordPtrCtl );
        if( retGetFaultRecord == DEM_IRT_OK )
        {
            /* Successful to get FaultRecord */
            obdDTCFlag  =   (boolean)TRUE;
            if ( faultRecordPtrCtl.FaultRecordPtr->EventStrgIndex < eventStorageNum )   /* [GUD:if]faultRecordPtrCtl.FaultRecordPtr->EventStrgIndex */
            {
                obdDTCFlag = Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( faultRecordPtrCtl.FaultRecordPtr->EventStrgIndex );    /* [GUD]faultRecordPtrCtl.FaultRecordPtr->EventStrgIndex */
            }

            if ( obdDTCFlag == (boolean)TRUE )
            {
                /* No Processing */
            }
            else
            {
                freezeCheckResult = (boolean)FALSE;
                for( freezeFrameRecordIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordIndex < nonOBDFFRClassPerDTCMaxNum; freezeFrameRecordIndex++ )  /* [GUD:for]freezeFrameRecordIndex */
                {
                    if ( faultRecordPtrCtl.FaultRecordPtr->RecordNumberIndex[freezeFrameRecordIndex] != DEM_FFRECINDEX_INITIAL )                            /* [GUD]freezeFrameRecordIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / freezeFrameRecordIndex */
                    {
                        freezeCheckResult = (boolean)TRUE;
                        break;
                    }
                }

                if ( freezeCheckResult == (boolean)TRUE )
                {
                    Dem_Data_GetEventPriorityAndStatusOfDTC( faultRecordPtrCtl.FaultRecordPtr->EventStrgIndex, &eventEntry );
                    eventEntry.FaultIndex = faultIndex;
                    result = Dem_DcEeo_SelectOverwrite( &eventEntry, &minPriorityEventEntry);
                    if ( result == (boolean)TRUE )
                    {
                        Dem_DcEeo_TransferEventEntryOverwrite( (P2VAR( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ))&minPriorityEventEntry, (P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ))&eventEntry );
                        retfaultIndex = faultIndex;
                    }
                }
            }
        }
    }

    return retfaultIndex;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Dem_DcEeo_SelectOverwrite                                */
/* Description   | Select overwrite target                                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] NewEventEntryOverwritePtr : new event               */
/*               |      OldEventEntryOverwritePtr : old event               */
/* Return Value  | boolean                                                  */
/*               |    TRUE : NewEventEntryOverwrite is overwrite target     */
/*               |    FALSE: OldEventEntryOverwrite is overwrite target     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_DcEeo_SelectOverwrite
(
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) NewEventEntryOverwritePtr,
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) OldEventEntryOverwritePtr
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u08_EventDisplacementStrategyType, AUTOMATIC )   eventDisplacementStrategy;
#if ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )   /*  [FuncSw]    */
    VAR( Dem_u08_OvwTargetCompareType, AUTOMATIC ) resultOfSelect;
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )        */

    retVal = (boolean)FALSE;

    if( NewEventEntryOverwritePtr->EventPriority > OldEventEntryOverwritePtr->EventPriority )
    {
        /* new event has lower priority than old event */
        retVal = (boolean)TRUE;
    }
    else if( NewEventEntryOverwritePtr->EventPriority == OldEventEntryOverwritePtr->EventPriority )
    {
        /* same priority */
        if( NewEventEntryOverwritePtr->OrgEventPriority > OldEventEntryOverwritePtr->OrgEventPriority )
        {
            /* new event has lower priority of config setting than old event */
            retVal = (boolean)TRUE;
        }
        else if( NewEventEntryOverwritePtr->OrgEventPriority == OldEventEntryOverwritePtr->OrgEventPriority )
        {
#if ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )   /*  [FuncSw]    */
            resultOfSelect = Dem_DcEeo_JudgePriorityByConfirmedDTCByTarget( NewEventEntryOverwritePtr, OldEventEntryOverwritePtr );
            if( resultOfSelect == DEM_EEO_OLD_IS_HIGH )
            {
                /* new event's confirmedDTC is off, and old event's confirmedDTC is on. */
                retVal = (boolean)TRUE;
            }
            else if( resultOfSelect == DEM_EEO_BOTH_ARE_SAME )
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )        */
            {
                /* new event and old event have the same priority of config setting */
                eventDisplacementStrategy = Dem_EventDisplacementStrategy;
                if( eventDisplacementStrategy == DEM_DISPLACEMENT_PRIO )
                {
                    /* new event is overwrite target */
                    retVal = (boolean)TRUE;
                }
            }
#if ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )   /*  [FuncSw]    */
            else
            {
                /* new event has higher priority than old event */
                /* No process */
            }
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )        */

        }
        else
        {
            /* new event has higher priority than old event */
            /* No process */
        }
    }
    else
    {
        /* new event has higher priority than old event */
        /* No process */
    }

    return retVal;
}

#if ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DcEeo_JudgePriorityByConfirmedDTCByTarget            */
/* Description   | Select DTC Status by ConfirmedDTC                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] NewEventEntryOverwritePtr : new event               */
/*               |      OldEventEntryOverwritePtr : old event               */
/* Return Value  | Dem_u08_OvwTargetCompareType                             */
/*               |    DEM_EEO_BOTH_ARE_SAME : new and old are the same      */
/*               |    DEM_EEO_NEW_IS_HIGH: new is high priority than old    */
/*               |    DEM_EEO_OLD_IS_HIGH: old is high priority than new    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-8-0      | new created.                                             */
/****************************************************************************/
static FUNC( Dem_u08_OvwTargetCompareType, DEM_CODE ) Dem_DcEeo_JudgePriorityByConfirmedDTCByTarget
(
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) NewEventEntryOverwritePtr,
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) OldEventEntryOverwritePtr
)
{
    VAR( Dem_u08_OvwTargetCompareType, AUTOMATIC ) retVal;

#if ( DEM_EVENT_DISPLACEMENT_BY_CDTC_NONOBDONLY_SUPPORT == STD_ON ) /* [FuncSw] */
    retVal = DEM_EEO_BOTH_ARE_SAME;

    if( ( NewEventEntryOverwritePtr->EventOBDKind == (boolean)FALSE ) && ( OldEventEntryOverwritePtr->EventOBDKind == (boolean)FALSE ) )
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_CDTC_NONOBDONLY_SUPPORT == STD_ON )  */
    {
        retVal = Dem_DcEeo_JudgePriorityByConfirmedDTC( NewEventEntryOverwritePtr, OldEventEntryOverwritePtr );
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DcEeo_JudgePriorityByConfirmedDTC                    */
/* Description   | Select DTC Status by ConfirmedDTC                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] NewEventEntryOverwritePtr : new event               */
/*               |      OldEventEntryOverwritePtr : old event               */
/* Return Value  | Dem_u08_OvwTargetCompareType                             */
/*               |    DEM_EEO_BOTH_ARE_SAME : new and old are the same      */
/*               |    DEM_EEO_NEW_IS_HIGH: new is high priority than old    */
/*               |    DEM_EEO_OLD_IS_HIGH: old is high priority than new    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_DcEeo_SelectDTCStatusByConfirmedDTC.*/
/****************************************************************************/
static FUNC( Dem_u08_OvwTargetCompareType, DEM_CODE ) Dem_DcEeo_JudgePriorityByConfirmedDTC
(
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) NewEventEntryOverwritePtr,
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) OldEventEntryOverwritePtr
)
{
    VAR( Dem_u08_OvwTargetCompareType, AUTOMATIC ) retVal;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newConfirmedDTC;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) oldConfirmedDTC;
    VAR( Dem_u08_OvwTargetByConfirmedOrderType, AUTOMATIC ) overwriteTarget;

    retVal = DEM_EEO_BOTH_ARE_SAME;

    /*--------------------------------------------------*/
    /*  DemEventDisplacementByDTCStatus is TRUE.        */
    /*--------------------------------------------------*/

    newConfirmedDTC = ( NewEventEntryOverwritePtr->StatusOfDTC & DEM_UDS_STATUS_CDTC );   /*  statusOfDTC : bit3  */
    oldConfirmedDTC = ( OldEventEntryOverwritePtr->StatusOfDTC & DEM_UDS_STATUS_CDTC );   /*  statusOfDTC : bit3  */
    if( newConfirmedDTC > oldConfirmedDTC )
    {
        retVal = DEM_EEO_NEW_IS_HIGH;
    }
    else if( newConfirmedDTC < oldConfirmedDTC )
    {
        retVal = DEM_EEO_OLD_IS_HIGH;
    }
    else
    {
        /*----------------------------------------------------------------------------------------------*/
        /* (( newConfirmedDTC == DEM_UDS_STATUS_CDTC ) && ( oldConfirmedDTC == DEM_UDS_STATUS_CDTC ))   */
        /*----------------------------------------------------------------------------------------------*/

        if ( newConfirmedDTC == DEM_UDS_STATUS_CDTC )
        {
            /*  judge priority the event is obdevent with OBDFFD or not.        */
            overwriteTarget   =   Dem_DcEeo_JudgeOverwriteTargetByConfirmedOrder( NewEventEntryOverwritePtr->FaultIndex, OldEventEntryOverwritePtr->FaultIndex );
            if ( overwriteTarget == DEM_EEO_OVWTARGET_OLDFAULTORDER )
            {
                /*  new is higher priority. overwrite old fault order record.       */
                retVal = DEM_EEO_NEW_IS_HIGH;
            }
            else if ( overwriteTarget == DEM_EEO_OVWTARGET_NEWFAULTORDER )
            {
                /*  old is higher priority. overwrite new fault order record.       */
                retVal = DEM_EEO_OLD_IS_HIGH;
            }
            else
            {
                /*  DEM_EEO_OVWTARGET_CANNOT_JUDGE    */
                /*  DEM_EEO_BOTH_ARE_SAME   */
            }
        }

        /* new and old are the same */
        /* No process */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DcEeo_SelectDTCStatusByConfirmedDTC                  */
/* Description   | Select DTC Status by ConfirmedDTC                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventEntryOverwriteFaultInfoPtr :  new event data   */
/*               |      TargetEventEntryOverwritePtr : old event data       */
/* Return Value  | Dem_u08_OvwTargetCompareType                             */
/*               |    DEM_EEO_BOTH_ARE_SAME : new and old are the same      */
/*               |    DEM_EEO_NEW_IS_HIGH: new is high priority than old    */
/*               |    DEM_EEO_OLD_IS_HIGH: old is high priority than new    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-8-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( Dem_u08_OvwTargetCompareType, DEM_CODE ) Dem_DcEeo_SelectDTCStatusByConfirmedDTC
(
    P2CONST( Dem_EventEntryOverwriteFaultInfoType, AUTOMATIC, AUTOMATIC ) EventEntryOverwriteFaultInfoPtr,
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) TargetEventEntryOverwritePtr
)
{
    VAR( Dem_u08_OvwTargetCompareType, AUTOMATIC ) retVal;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newConfirmedDTC;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) oldConfirmedDTC;
#if ( DEM_EVENT_DISPLACEMENT_BY_CDTC_NONOBDONLY_SUPPORT == STD_ON ) /* [FuncSw] */
    VAR( boolean, AUTOMATIC ) eventOBDKind;
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_CDTC_NONOBDONLY_SUPPORT == STD_ON )  */

    retVal = DEM_EEO_BOTH_ARE_SAME;

#if ( DEM_EVENT_DISPLACEMENT_BY_CDTC_NONOBDONLY_SUPPORT == STD_ON ) /* [FuncSw] */
    eventOBDKind = Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( EventEntryOverwriteFaultInfoPtr->EventStrgIndex );
    if( ( eventOBDKind == (boolean)FALSE ) && ( TargetEventEntryOverwritePtr->EventOBDKind == (boolean)FALSE ) )
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_CDTC_NONOBDONLY_SUPPORT == STD_ON )  */
    {
        /*--------------------------------------------------*/
        /*  DemEventDisplacementByDTCStatus is TRUE.        */
        /*--------------------------------------------------*/

        newConfirmedDTC = ( EventEntryOverwriteFaultInfoPtr->StatusOfDTC & DEM_UDS_STATUS_CDTC );   /*  statusOfDTC : bit3  */
        oldConfirmedDTC = ( TargetEventEntryOverwritePtr->StatusOfDTC & DEM_UDS_STATUS_CDTC );      /*  statusOfDTC : bit3  */
        if( newConfirmedDTC > oldConfirmedDTC )
        {
            retVal = DEM_EEO_NEW_IS_HIGH;
        }
        else if( newConfirmedDTC < oldConfirmedDTC )
        {
            retVal = DEM_EEO_OLD_IS_HIGH;
        }
        else
        {
            /* new and old are the same */
            /* No process */
        }
    }

    return retVal;
}
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )        */

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DcEeo_SelectNonOBDFFROverwriteForEachTrigger         */
/* Description   | Select NonOBD FFR overwrite target by lower priority     */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventEntryOverwritePtr                              */
/*               |        EventPriority                                     */
/*               |        OrgEventPriority                                  */
/*               |        FaultIndex                                        */
/*               | [in] FreezeFrameRecordTrigger                            */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DcEeo_SelectNonOBDFFROverwriteForEachTrigger
(
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) EventEntryOverwritePtr,        /* [PRMCHK:CALLER] */
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC) FreezeFrameRecordTrigger
)
{
    VAR( boolean, AUTOMATIC ) retCheckEventPriorityEachTrigger;

    /* Set overwrite target each trigger */
    if ( FreezeFrameRecordTrigger == DEM_TRIGGER_ON_CONFIRMED )
    {
        retCheckEventPriorityEachTrigger = Dem_DcEeo_SelectOverwrite( EventEntryOverwritePtr, &Dem_NonOBDFFROverwriteForEachTrigger.EventEntryOverwriteConfirmedTrigger );
        if ( retCheckEventPriorityEachTrigger == (boolean)TRUE )
        {
            Dem_DcEeo_TransferEventEntryOverwrite( (P2VAR( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ))&Dem_NonOBDFFROverwriteForEachTrigger.EventEntryOverwriteConfirmedTrigger, (P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ))EventEntryOverwritePtr );   /* [GUD]&Dem_NonOBDFFROverwriteForEachTrigger.EventEntryOverwriteConfirmedTrigger *//* [GUDCHK:CALLER]EventEntryOverwritePtr */
        }
    }
    else if ( FreezeFrameRecordTrigger == DEM_TRIGGER_ON_FDC_THRESHOLD )
    {
        retCheckEventPriorityEachTrigger = Dem_DcEeo_SelectOverwrite( EventEntryOverwritePtr, &Dem_NonOBDFFROverwriteForEachTrigger.EventEntryOverwriteFDCThresholdTrigger );
        if ( retCheckEventPriorityEachTrigger == (boolean)TRUE )
        {
            Dem_DcEeo_TransferEventEntryOverwrite( (P2VAR( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ))&Dem_NonOBDFFROverwriteForEachTrigger.EventEntryOverwriteFDCThresholdTrigger, (P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ))EventEntryOverwritePtr );    /* [GUD]&Dem_NonOBDFFROverwriteForEachTrigger.EventEntryOverwriteFDCThresholdTrigger *//* [GUDCHK:CALLER]EventEntryOverwritePtr */
        }
    }
    else if ( FreezeFrameRecordTrigger == DEM_TRIGGER_ON_PENDING )
    {
        retCheckEventPriorityEachTrigger = Dem_DcEeo_SelectOverwrite( EventEntryOverwritePtr, &Dem_NonOBDFFROverwriteForEachTrigger.EventEntryOverwritePendingTrigger );
        if ( retCheckEventPriorityEachTrigger == (boolean)TRUE )
        {
            Dem_DcEeo_TransferEventEntryOverwrite( (P2VAR( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ))&Dem_NonOBDFFROverwriteForEachTrigger.EventEntryOverwritePendingTrigger, (P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ))EventEntryOverwritePtr ); /* [GUD]&Dem_NonOBDFFROverwriteForEachTrigger.EventEntryOverwritePendingTrigger *//* [GUDCHK:CALLER]EventEntryOverwritePtr */
        }
    }
    else if ( FreezeFrameRecordTrigger == DEM_TRIGGER_ON_TEST_FAILED_THIS_OPERATION_CYCLE )
    {
        retCheckEventPriorityEachTrigger = Dem_DcEeo_SelectOverwrite( EventEntryOverwritePtr, &Dem_NonOBDFFROverwriteForEachTrigger.EventEntryOverwriteTFTOCTrigger );
        if ( retCheckEventPriorityEachTrigger == (boolean)TRUE )
        {
            Dem_DcEeo_TransferEventEntryOverwrite( (P2VAR( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ))&Dem_NonOBDFFROverwriteForEachTrigger.EventEntryOverwriteTFTOCTrigger, (P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ))EventEntryOverwritePtr );   /* [GUD]&Dem_NonOBDFFROverwriteForEachTrigger.EventEntryOverwriteTFTOCTrigger *//* [GUDCHK:CALLER]EventEntryOverwritePtr */
        }
    }
    else
    {
        /* No Process */
    }

    return;
}
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_DcEeo_InitializeEventEntryOverwrite                  */
/* Description   | Initializes EventEntryOverwrite                          */
/* Preconditions | none                                                     */
/* Parameters    | [out] EventEntryOverwritePtr : The record to initialize  */
/* Return Value  | void                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DcEeo_InitializeEventEntryOverwrite
(
    P2VAR( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ) EventEntryOverwritePtr
)
{
    EventEntryOverwritePtr->EventPriority    = DEM_PRIORITY_INITIAL;
    EventEntryOverwritePtr->OrgEventPriority = DEM_PRIORITY_INITIAL;
    EventEntryOverwritePtr->FaultIndex       = DEM_FAULTINDEX_INITIAL;
    EventEntryOverwritePtr->StatusOfDTC      = DEM_DTCSTATUS_BYTE_DEFAULT;
#if ( DEM_EVENT_DISPLACEMENT_BY_CDTC_NONOBDONLY_SUPPORT == STD_ON ) /* [FuncSw] */
    EventEntryOverwritePtr->EventOBDKind     = (boolean)FALSE;
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_CDTC_NONOBDONLY_SUPPORT == STD_ON )  */

    return;
}


/****************************************************************************/
/* Function Name | Dem_DcEeo_TransferEventEntryOverwrite                    */
/* Description   | Transfers EventEntryOverwrite                            */
/* Preconditions | none                                                     */
/* Parameters    | [out] DstEventEntryOverwritePtr : The destination record */
/*               | [in]  SrcEventEntryOverwritePtr : The source record      */
/* Return Value  | void                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DcEeo_TransferEventEntryOverwrite
(
    P2VAR( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ) DstEventEntryOverwritePtr,         /* [PRMCHK:CALLER] */
    P2CONST( Dem_EventEntryOverwriteType, AUTOMATIC, DEM_VAR_NO_INIT ) SrcEventEntryOverwritePtr        /* [PRMCHK:CALLER] */
)
{
    DstEventEntryOverwritePtr->EventPriority    = SrcEventEntryOverwritePtr->EventPriority;     /* [GUDCHK:CALLER]DstEventEntryOverwritePtr *//* [GUDCHK:CALLER]SrcEventEntryOverwritePtr */
    DstEventEntryOverwritePtr->OrgEventPriority = SrcEventEntryOverwritePtr->OrgEventPriority;  /* [GUDCHK:CALLER]DstEventEntryOverwritePtr *//* [GUDCHK:CALLER]SrcEventEntryOverwritePtr */
    DstEventEntryOverwritePtr->FaultIndex       = SrcEventEntryOverwritePtr->FaultIndex;        /* [GUDCHK:CALLER]DstEventEntryOverwritePtr *//* [GUDCHK:CALLER]SrcEventEntryOverwritePtr */
    DstEventEntryOverwritePtr->StatusOfDTC      = SrcEventEntryOverwritePtr->StatusOfDTC;       /* [GUDCHK:CALLER]DstEventEntryOverwritePtr *//* [GUDCHK:CALLER]SrcEventEntryOverwritePtr */
#if ( DEM_EVENT_DISPLACEMENT_BY_CDTC_NONOBDONLY_SUPPORT == STD_ON ) /* [FuncSw] */
    DstEventEntryOverwritePtr->EventOBDKind     = SrcEventEntryOverwritePtr->EventOBDKind;      /* [GUDCHK:CALLER]DstEventEntryOverwritePtr *//* [GUDCHK:CALLER]SrcEventEntryOverwritePtr */
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_CDTC_NONOBDONLY_SUPPORT == STD_ON )  */

    return;
}

#if ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DcEeo_JudgeOverwriteTargetByConfirmedOrder        */
/* Description   | Select overwrite target                                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] NewFaultOrderFaultIndex : new fault order event     */
/*               | [in] OldFaultOrderFaultIndex : old fault order event     */
/* Return Value  | uint8                                                    */
/*               |    DEM_EEO_OVWTARGET_CANNOT_JUDGE : new and old are the same                   */
/*               |    DEM_EEO_OVWTARGET_NEWFAULTORDER: NewFaultOrderFaultIndex is overwrite target. */
/*               |    DEM_EEO_OVWTARGET_OLDFAULTORDER: OldFaultOrderFaultIndex is overwrite target. */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( Dem_u08_OvwTargetByConfirmedOrderType, DEM_CODE ) Dem_DcEeo_JudgeOverwriteTargetByConfirmedOrder
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) NewFaultOrderFaultIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) OldFaultOrderFaultIndex
)
{
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) newFaultConfirmedOccurrenceOrder;
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) oldFaultConfirmedOccurrenceOrder;
    VAR( Dem_u08_OvwTargetByConfirmedOrderType, AUTOMATIC ) retVal;
    VAR( Dem_u08_EventDisplacementStrategyType, AUTOMATIC )   eventDisplacementStrategy;
    VAR( boolean, AUTOMATIC ) chkConfirmedOrder;

    /*  get confirmed order list            */
    newFaultConfirmedOccurrenceOrder    =   DEM_FAIL_OCCURRENCE_NUM_INVALID;
    oldFaultConfirmedOccurrenceOrder    =   DEM_FAIL_OCCURRENCE_NUM_INVALID;

    /*  if xxxFaultOrderFaultIndex is INVALID, xxxFaultConfirmedOccurrenceOrder value is DEM_FAIL_OCCURRENCE_NUM_INVALID.   */
    (void)Dem_DataMngC_GetFR_ConfirmedOccurrenceOrder( NewFaultOrderFaultIndex, &newFaultConfirmedOccurrenceOrder );    /* no return check required */
    (void)Dem_DataMngC_GetFR_ConfirmedOccurrenceOrder( OldFaultOrderFaultIndex, &oldFaultConfirmedOccurrenceOrder );    /* no return check required */

    chkConfirmedOrder   =   (boolean)FALSE;

    retVal = DEM_EEO_OVWTARGET_CANNOT_JUDGE;
    if ( newFaultConfirmedOccurrenceOrder != DEM_FAIL_OCCURRENCE_NUM_INVALID )
    {
        /*  NewFaultOrderFaultIndex is ConfirmedDTC.                            */
        if ( oldFaultConfirmedOccurrenceOrder != DEM_FAIL_OCCURRENCE_NUM_INVALID )
        {
            /*  Both NewFaultOrderFaultIndex and OldFaultOrderFaultIndex are ConfirmedDTC.      */
            /*  check ConfirmedDTC order.                   */
            chkConfirmedOrder   =   (boolean)TRUE;
        }
        else
        {
            /*  OldFaultOrderFaultIndex is not ConfirmedDTC.        */
            /*  so, OldFaultOrderFaultIndex is overwrite target.    */
            retVal = DEM_EEO_OVWTARGET_OLDFAULTORDER;
        }
    }
    else
    {
        /*  NewFaultOrderFaultIndex is not ConfirmedDTC.        */
        if ( oldFaultConfirmedOccurrenceOrder != DEM_FAIL_OCCURRENCE_NUM_INVALID )
        {
            /*  OldFaultOrderFaultIndex is ConfirmedDTC.            */
            /*  so, NewFaultOrderFaultIndex is overwrite target.    */
            retVal = DEM_EEO_OVWTARGET_NEWFAULTORDER;
        }
        else
        {
            /*  Both NewFaultOrderFaultIndex and OldFaultOrderFaultIndex are not ConfirmedDTC.      */
            /*  DEM_EEO_OVWTARGET_CANNOT_JUDGE.       */
        }
    }

    if ( chkConfirmedOrder == (boolean)TRUE )
    {
        /* new event and old event have the same priority of config setting */
        eventDisplacementStrategy = Dem_EventDisplacementStrategy;
        if( eventDisplacementStrategy == DEM_DISPLACEMENT_PRIO_OCC )
        {
            /*-------------------------------------------------------------------------*/
            /*  DEM_DISPLACEMENT_PRIO_OCC                                              */
            /*-------------------------------------------------------------------------*/
            /* older confirmed event( occurrence value is SMALL ) is overwrite target. */
            /*-------------------------------------------------------------------------*/

            if ( newFaultConfirmedOccurrenceOrder < oldFaultConfirmedOccurrenceOrder )
            {
                retVal = DEM_EEO_OVWTARGET_NEWFAULTORDER;
            }
            else if ( newFaultConfirmedOccurrenceOrder > oldFaultConfirmedOccurrenceOrder )
            {
                retVal = DEM_EEO_OVWTARGET_OLDFAULTORDER;
            }
            else
            {
                /*  DEM_EEO_OVWTARGET_CANNOT_JUDGE.       */
            }
        }
        else
        {
            /*-------------------------------------------------------------------------*/
            /*  DEM_DISPLACEMENT_PRIO                                                  */
            /*-------------------------------------------------------------------------*/
            /* newer confirmed event( occurrence value is BIG ) is overwrite target.   */
            /*-------------------------------------------------------------------------*/

            if ( newFaultConfirmedOccurrenceOrder > oldFaultConfirmedOccurrenceOrder )
            {
                retVal = DEM_EEO_OVWTARGET_NEWFAULTORDER;
            }
            else if ( newFaultConfirmedOccurrenceOrder < oldFaultConfirmedOccurrenceOrder )
            {
                retVal = DEM_EEO_OVWTARGET_OLDFAULTORDER;
            }
            else
            {
                /*  DEM_EEO_OVWTARGET_CANNOT_JUDGE.       */
            }
        }
    }
    return retVal;
}
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )        */


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
/****************************************************************************/

/**** End of File ***********************************************************/
