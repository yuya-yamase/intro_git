/* Dem_Event_QualificationInfo_c(v5-9-0)                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Event_QualilficationInfo/CODE                         */
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
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_Pm_Event.h"
#include "../../../inc/Dem_Pm_AltIUMPR.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "Dem_Event_QualificationInfo_local.h"

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

static FUNC( boolean, DEM_CODE ) Dem_Event_UpdateQualificationInfo_Failed
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    P2VAR( Dem_u08_EventQualificationType, AUTOMATIC, AUTOMATIC ) EventQualificationPtr
);
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
static FUNC( boolean, DEM_CODE ) Dem_Event_UpdateQualificationInfo_Failed_Specific
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    P2VAR( Dem_u08_EventQualificationType, AUTOMATIC, AUTOMATIC ) EventQualificationPtr
);
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )     */

static FUNC( boolean, DEM_CODE ) Dem_Event_UpdateQualificationInfo_Passed
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    P2VAR( Dem_u08_EventQualificationType, AUTOMATIC, AUTOMATIC ) EventQualificationPtr
);
static FUNC( boolean, DEM_CODE ) Dem_Event_JudgeUpdateToPassed_InEvtStrg
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);
static FUNC( void, DEM_CODE ) Dem_Event_UpdateFailedToNotQualified_InEvtStrg
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/*  event qualification info        */
VAR( Dem_u08_EventQualificationType, DEM_VAR_NO_INIT ) Dem_EventQualificationList[ DEM_PRIMEM_EVENT_NUM ];

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Event_InitQualification                              */
/* Description   | Sets event status in event record(RAM).                  */
/* Preconditions | Support only monitor internal debounce algorithm.        */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Event_InitQualification
( void )
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventConfigureNum;

    eventConfigureNum = Dem_PrimaryMemEventConfigureNum;

    for( eventCtrlIndex = ( Dem_u16_EventCtrlIndexType )0U; eventCtrlIndex < eventConfigureNum; eventCtrlIndex++ )  /* [GUD:for]eventCtrlIndex */
    {
        Dem_EventQualificationList[ eventCtrlIndex ] = DEM_EVENT_QUALIFICATION_NOTQUALIFIED;                        /* [GUD]eventCtrlIndex */
    }
    return ;
}


/****************************************************************************/
/* Function Name | Dem_Event_SetQualificationInfo                           */
/* Description   | Update qualification info : FAILED.                      */
/* Preconditions |                                                          */
/* Parameters    | [in] EventCtrlIndex :                                    */
/* Return Value  | FALSE : no update.                                       */
/*               | TRUE  : update.                                          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]AltIUMPR                                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Event_SetQualificationInfo
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,        /* [PRMCHK:CALLER] */
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    P2VAR( Dem_u08_EventQualificationType, AUTOMATIC, AUTOMATIC ) EventQualificationPtr
)
{
    VAR( boolean, AUTOMATIC ) updateFlag;

    updateFlag          =   (boolean)FALSE;
    if ( EventStatus == DEM_EVENT_STATUS_PASSED )
    {
        updateFlag  =   Dem_Event_UpdateQualificationInfo_Passed( EventCtrlIndex, EventQualificationPtr ); /* [GUDCHK:CALLER]EventCtrlIndex *//* [UpdRec]AltIUMPR */
    }
    else if ( EventStatus == DEM_EVENT_STATUS_FAILED )
    {
        updateFlag  =   Dem_Event_UpdateQualificationInfo_Failed( EventCtrlIndex, EventQualificationPtr );                      /* [GUDCHK:CALLER]EventCtrlIndex *//* [UpdRec]AltIUMPR */
    }
    else
    {
        /*  no process.     */
    }
    return updateFlag;
}

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Event_SetQualificationInfo_Specific                  */
/* Description   | Update qualification info : FAILED.                      */
/* Preconditions |                                                          */
/* Parameters    | [in] EventCtrlIndex :                                    */
/* Return Value  | FALSE : no update.                                       */
/*               | TRUE  : update.                                          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]AltIUMPR                                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Event_SetQualificationInfo_Specific
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,        /* [PRMCHK:CALLER] */
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    P2VAR( Dem_u08_EventQualificationType, AUTOMATIC, AUTOMATIC ) EventQualificationPtr
)
{
    VAR( boolean, AUTOMATIC ) updateFlag;

    updateFlag          =   (boolean)FALSE;
    if ( EventStatus == DEM_EVENT_STATUS_PASSED )
    {
        updateFlag  =   Dem_Event_UpdateQualificationInfo_Passed( EventCtrlIndex, EventQualificationPtr ); /* [GUDCHK:CALLER]EventCtrlIndex *//* [UpdRec]AltIUMPR */
    }
    else if ( EventStatus == DEM_EVENT_STATUS_FAILED )
    {
        updateFlag  =   Dem_Event_UpdateQualificationInfo_Failed_Specific( EventCtrlIndex, EventQualificationPtr );             /* [GUDCHK:CALLER]EventCtrlIndex *//* [UpdRec]AltIUMPR */
    }
    else
    {
        /*  no process.     */
    }
    return updateFlag;
}
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )     */


/****************************************************************************/
/* Function Name | Dem_Event_ClearTargetQualificationInfo_NotTestedInCycle  */
/* Description   | Update qualification info : FAILED.                      */
/* Preconditions |                                                          */
/* Parameters    | [in] EventCtrlIndex :                                    */
/* Return Value  | void                                                     */
/* Notes         | call from Update operation cycle. / overflow event.      */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]AltIUMPR                                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Event_ClearTargetQualificationInfo_NotTestedInCycle
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex     /* [PRMCHK:CALLER] */
)
{
    Dem_EventQualificationList[ EventCtrlIndex ]    =   DEM_EVENT_QUALIFICATION_NOTQUALIFIED;           /* [GUDCHK:CALLER]EventCtrlIndex */

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )    /*  [FuncSw]    */
    Dem_Event_SavePassedTgtBit_ByEvtCtrlIdx( EventCtrlIndex, (boolean)FALSE );
#endif  /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )             */

#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )  /*  [FuncSw]    */
    Dem_AltIUMPR_SetTestCompleteThisCycle( EventCtrlIndex, DEM_ALTIUMPR_TCTOC_NOTTESTCOMPLETE );        /* [GUDCHK:CALLER]EventCtrlIndex *//* [UpdRec]AltIUMPR */
#endif  /* ( DEM_ALTIUMPR_SUPPORT == STD_ON )           */

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Event_ClearTargetQualificationInfoAtOpCycUpd_NotTestedInCycle  */
/* Description   | Update qualification info : FAILED.                      */
/* Preconditions |                                                          */
/* Parameters    | [in] EventCtrlIndex :                                    */
/* Return Value  | void                                                     */
/* Notes         | call from Update operation cycle. / overflow event.      */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]AltIUMPR                                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Event_ClearTargetQualificationInfoAtOpCycUpd_NotTestedInCycle
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,        /* [PRMCHK:CALLER] */
    VAR( Dem_u08_OpcycUpdateFailureCycleType, AUTOMATIC ) FailureCycleFlag
)
{
    if ( FailureCycleFlag != DEM_OPCYCUPD_FLCYC_INITIALVALUE )
    {
        Dem_EventQualificationList[ EventCtrlIndex ]    =   DEM_EVENT_QUALIFICATION_NOTQUALIFIED;       /* [GUDCHK:CALLER]EventCtrlIndex */

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )    /*  [FuncSw]    */
        Dem_Event_SavePassedTgtBit_ByEvtCtrlIdx( EventCtrlIndex, (boolean)FALSE );
#endif  /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )             */
    }

#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )  /*  [FuncSw]    */
    if (( FailureCycleFlag & DEM_OPCYCUPD_FLCYC_UPDSTATUS_TNCTOC ) == DEM_OPCYCUPD_FLCYC_UPDSTATUS_TNCTOC )
    {
        Dem_AltIUMPR_SetTestCompleteThisCycle( EventCtrlIndex, DEM_ALTIUMPR_TCTOC_NOTTESTCOMPLETE );    /* [GUDCHK:CALLER]EventCtrlIndex *//* [UpdRec]AltIUMPR */
    }
#endif  /* ( DEM_ALTIUMPR_SUPPORT == STD_ON )           */
    return ;
}

/****************************************************************************/
/* Function Name | Dem_Event_ClearFailedQualificationInfo_NotTestedInCycle  */
/* Description   | Update qualification info : FAILED.                      */
/* Preconditions |                                                          */
/* Parameters    | [in] EventCtrlIndex :                                    */
/* Return Value  | void                                                     */
/* Notes         | call from InitializeEventStatus.                         */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]AltIUMPR                                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Event_ClearFailedQualificationInfo_NotTestedInCycle
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex     /* [PRMCHK:CALLER] */
)
{
    /*  update in EvtStrgGrp : FAILED => NOT_QUALIFIED.     */
    Dem_Event_UpdateFailedToNotQualified_InEvtStrg( EventCtrlIndex );                               /* [GUDCHK:CALLER]EventCtrlIndex */

    /*  set DEM_EVENT_QUALIFICATION_NOTQUALIFIED to target EventCtrlIndex.        */
    Dem_EventQualificationList[ EventCtrlIndex ]    =   DEM_EVENT_QUALIFICATION_NOTQUALIFIED;       /* [GUDCHK:CALLER]EventCtrlIndex */

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )    /*  [FuncSw]    */
    Dem_Event_SavePassedAllBit_fromQualification( EventCtrlIndex );
#endif  /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )             */

#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )  /*  [FuncSw]    */
    /*  update to NotTested.        */
    Dem_AltIUMPR_SetTestCompleteThisCycle( EventCtrlIndex, DEM_ALTIUMPR_TCTOC_NOTTESTCOMPLETE );    /* [GUDCHK:CALLER]EventCtrlIndex *//* [UpdRec]AltIUMPR */
#endif  /* ( DEM_ALTIUMPR_SUPPORT == STD_ON )           */

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Event_ClearFailedQualificationInfo_nochange          */
/* Description   | Update qualification info : FAILED.                      */
/* Preconditions |                                                          */
/* Parameters    | [in] EventCtrlIndex :                                    */
/* Return Value  | void                                                     */
/* Notes         | call from AgingEventStatus / ResetEventUdsStatusHistory. */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Event_ClearFailedQualificationInfo_nochange
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex     /* [PRMCHK:CALLER] */
)
{
    /*  update in EvtStrgGrp : FAILED => NOT_QUALIFIED.     */
    Dem_Event_UpdateFailedToNotQualified_InEvtStrg( EventCtrlIndex );                           /* [GUDCHK:CALLER]EventCtrlIndex */

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )    /*  [FuncSw]    */
    Dem_Event_SavePassedAllBit_fromQualification( EventCtrlIndex );
#endif  /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )             */

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Event_ClearQualificationInfo_TestedInCycle           */
/* Description   | Update qualification info : FAILED.                      */
/* Preconditions |                                                          */
/* Parameters    | [in] EventCtrlIndex :                                    */
/* Return Value  | void                                                     */
/* Notes         | call from NormalizeEventStatus.                          */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]AltIUMPR                                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Event_ClearAndPassedQualificationInfo_TestedInCycle
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex     /* [PRMCHK:CALLER] */
)
{
    Dem_EventQualificationList[ EventCtrlIndex ]    =   DEM_EVENT_QUALIFICATION_PASSED;         /* [GUDCHK:CALLER]EventCtrlIndex */

    /*  update in EvtStrgGrp : FAILED => NOT_QUALIFIED.     */
    Dem_Event_UpdateFailedToNotQualified_InEvtStrg( EventCtrlIndex );                           /* [GUDCHK:CALLER]EventCtrlIndex */

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )    /*  [FuncSw]    */
    Dem_Event_SavePassedAllBit_fromQualification( EventCtrlIndex );
#endif  /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )             */

#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )  /*  [FuncSw]    */
    /*  update to NotTested.        */
    Dem_AltIUMPR_SetTestCompleteThisCycle( EventCtrlIndex, DEM_ALTIUMPR_TCTOC_TESTCOMPLETE );   /* [GUDCHK:CALLER]EventCtrlIndex *//* [UpdRec]AltIUMPR */
#endif  /* ( DEM_ALTIUMPR_SUPPORT == STD_ON )           */

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Event_ClearQualificationInfo_NotTestedInCycle_InEvtStrg */
/* Description   | Update qualification info : FAILED.                      */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | void                                                     */
/* Notes         | call from ClearDTC.                                      */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]AltIUMPR                                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Event_ClearQualificationInfo_NotTestedInCycle_InEvtStrg
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex     /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexCnt;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexNum;

    eventCtrlIndexNum   =   Dem_CmbEvt_NumOfEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );          /*  get EventCtrlIndex of EventStorageGroup max number  *//* [GUDCHK:CALLER]EventStrgIndex */
    eventCtrlIndex      =   Dem_CmbEvt_GetDelegateEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );    /*  get Delegate EventCtrlIndex                         *//* [GUDCHK:CALLER]EventStrgIndex */

    /*  set all qualification in event storage group to DEM_EVENT_QUALIFICATION_NOTQUALIFIED.   */
    for ( eventCtrlIndexCnt = ( Dem_u16_EventCtrlIndexType )0U; eventCtrlIndexCnt < eventCtrlIndexNum; eventCtrlIndexCnt++ )
    {
        Dem_EventQualificationList[ eventCtrlIndex ]    =   DEM_EVENT_QUALIFICATION_NOTQUALIFIED;       /* [GUDCHK:CALLER]EventStrgIndex */

#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )  /*  [FuncSw]    */
        /*  update to NotTested.        */
        Dem_AltIUMPR_SetTestCompleteThisCycle( eventCtrlIndex, DEM_ALTIUMPR_TCTOC_NOTTESTCOMPLETE );    /* [GUDCHK:CALLER]EventStrgIndex *//* [UpdRec]AltIUMPR */
#endif  /* ( DEM_ALTIUMPR_SUPPORT == STD_ON )           */

        /*  get next Index.         */
        eventCtrlIndex  =   Dem_CmbEvt_GetNextEventCtrlIndex_InEvtStrgGrp( eventCtrlIndex );            /* [GUDCHK:CALLER]EventStrgIndex */
    }

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )    /*  [FuncSw]    */
    Dem_Event_ClearPassedBit_InStrgGrp( EventStrgIndex );
#endif  /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )             */

    return ;
}

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Event_ClearQualificationInfo_nochange_InEvtStrg      */
/* Description   | Update qualification info : FAILED.                      */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | void                                                     */
/* Notes         | call from Overwritten event.                             */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Event_ClearQualificationInfo_nochange_InEvtStrg
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex     /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexCnt;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexNum;

    eventCtrlIndexNum   =   Dem_CmbEvt_NumOfEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );          /* [GUDCHK:CALLER]EventStrgIndex *//*  get EventCtrlIndex of EventStorageGroup max number  */
    eventCtrlIndex      =   Dem_CmbEvt_GetDelegateEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );    /* [GUDCHK:CALLER]EventStrgIndex *//*  get Delegate EventCtrlIndex                         */

    /*  set all qualification in event storage group to DEM_EVENT_QUALIFICATION_NOTQUALIFIED.   */
    for ( eventCtrlIndexCnt = ( Dem_u16_EventCtrlIndexType )0U; eventCtrlIndexCnt < eventCtrlIndexNum; eventCtrlIndexCnt++ )
    {
        Dem_EventQualificationList[ eventCtrlIndex ]    =   DEM_EVENT_QUALIFICATION_NOTQUALIFIED;   /* [GUDCHK:CALLER]EventStrgIndex */

        /*  get next Index.         */
        eventCtrlIndex  =   Dem_CmbEvt_GetNextEventCtrlIndex_InEvtStrgGrp( eventCtrlIndex );        /* [GUDCHK:CALLER]EventStrgIndex */
    }

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )    /*  [FuncSw]    */
    Dem_Event_ClearPassedBit_InStrgGrp( EventStrgIndex );
#endif  /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )             */

    return ;
}
#endif  /*   ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )   */

/****************************************************************************/
/* Function Name | Dem_Event_UpdateQualificationInfo_Failed                 */
/* Description   | Update qualification info : FAILED.                      */
/* Preconditions |                                                          */
/* Parameters    | [in] EventCtrlIndex :                                    */
/* Return Value  | FALSE : no update.                                       */
/*               | TRUE  : update.                                          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]AltIUMPR                                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Event_UpdateQualificationInfo_Failed
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,        /* [PRMCHK:CALLER] */
    P2VAR( Dem_u08_EventQualificationType, AUTOMATIC, AUTOMATIC ) EventQualificationPtr
)
{
    VAR( boolean, AUTOMATIC ) updateFlag;
    VAR( Dem_u08_EventQualificationType, AUTOMATIC ) oldQualification;
    VAR( Dem_u08_EventQualificationType, AUTOMATIC ) newQualification;

    oldQualification    =   Dem_EventQualificationList[ EventCtrlIndex ];       /* [GUDCHK:CALLER]EventCtrlIndex */

    if ( oldQualification == DEM_EVENT_QUALIFICATION_PASSED )
    {
        /*  PASSED => FAILED    */
        newQualification    =   DEM_EVENT_QUALIFICATION_FAILED;
        updateFlag          =   (boolean)TRUE;
    }
    else if ( oldQualification == DEM_EVENT_QUALIFICATION_FAILED )
    {
        /*  FAILED => FAILED    */
        /*  no update.          */
        newQualification    =   oldQualification;
        updateFlag          =   (boolean)FALSE;
    }
    else /* ( oldQualification == DEM_EVENT_QUALIFICATION_NOTQUALIFIED )    */
    {
        /*  NotTested => FAILED */
        newQualification    =   DEM_EVENT_QUALIFICATION_FAILED;
        updateFlag          =   (boolean)TRUE;
    }
    Dem_EventQualificationList[ EventCtrlIndex ]    =   newQualification;       /* [GUDCHK:CALLER]EventCtrlIndex */

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )    /*  [FuncSw]    */
    Dem_Event_SavePassedTgtBit_ByEvtCtrlIdx( EventCtrlIndex, (boolean)FALSE );
#endif  /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )             */

    *EventQualificationPtr  =   newQualification;

#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )  /*  [FuncSw]    */
    /*  update to Tested.       */
    Dem_AltIUMPR_SetTestCompleteThisCycle( EventCtrlIndex, DEM_ALTIUMPR_TCTOC_TESTCOMPLETE );   /* [GUDCHK:CALLER]EventCtrlIndex *//* [UpdRec]AltIUMPR */
#endif  /* ( DEM_ALTIUMPR_SUPPORT == STD_ON )           */

    return updateFlag;
}

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Event_UpdateQualificationInfo_Failed_Specific        */
/* Description   | Update qualification info : FAILED.                      */
/* Preconditions |                                                          */
/* Parameters    | [in] EventCtrlIndex :                                    */
/* Return Value  | FALSE : no update.                                       */
/*               | TRUE  : update.                                          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]AltIUMPR                                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Event_UpdateQualificationInfo_Failed_Specific
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,        /* [PRMCHK:CALLER] */
    P2VAR( Dem_u08_EventQualificationType, AUTOMATIC, AUTOMATIC ) EventQualificationPtr
)
{
    VAR( boolean, AUTOMATIC ) updateFlag;

    Dem_EventQualificationList[ EventCtrlIndex ]    =   DEM_EVENT_QUALIFICATION_FAILED;         /* [GUDCHK:CALLER]EventCtrlIndex */

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )    /*  [FuncSw]    */
    Dem_Event_SavePassedTgtBit_ByEvtCtrlIdx( EventCtrlIndex, (boolean)FALSE );
#endif  /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )             */

    *EventQualificationPtr  =   DEM_EVENT_QUALIFICATION_FAILED;
    updateFlag          =   (boolean)TRUE;

#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )  /*  [FuncSw]    */
    /*  update to Tested.       */
    Dem_AltIUMPR_SetTestCompleteThisCycle( EventCtrlIndex, DEM_ALTIUMPR_TCTOC_TESTCOMPLETE );   /* [GUDCHK:CALLER]EventCtrlIndex *//* [UpdRec]AltIUMPR */
#endif  /* ( DEM_ALTIUMPR_SUPPORT == STD_ON )           */

    return updateFlag;
}
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )     */


/****************************************************************************/
/* Function Name | Dem_Event_UpdateQualificationInfo_Passed                 */
/* Description   | Update qualification info : PASSED.                      */
/* Preconditions |                                                          */
/* Parameters    | [in] EventCtrlIndex :                                    */
/* Return Value  | FALSE : no update.                                       */
/*               | TRUE  : update.                                          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]AltIUMPR                                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/*   v5-8-0      | branch changed.                                          */
/*   v5-9-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Event_UpdateQualificationInfo_Passed
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,        /* [PRMCHK:CALLER] */
    P2VAR( Dem_u08_EventQualificationType, AUTOMATIC, AUTOMATIC ) EventQualificationPtr
)
{
    VAR( boolean, AUTOMATIC ) updateFlag;

    Dem_EventQualificationList[ EventCtrlIndex ]    =   DEM_EVENT_QUALIFICATION_PASSED;         /* [GUDCHK:CALLER]EventCtrlIndex */
    *EventQualificationPtr  =   DEM_EVENT_QUALIFICATION_PASSED;

    /*------------------------------------------------------------------------------*/
    /*  OnStorage OFF :               updateFlag                                    */
    /*      PASSED    => PASSED     : TRUE                                          */
    /*      FAILED    => PASSED     : TRUE                                          */
    /*      NotTested => PASSED     : TRUE                                          */
    /*------------------------------------------------------------------------------*/
    /*  OnStorage ON :                updateFlag                                    */
    /*      PASSED    => PASSED     : all passed : TRUE / not all passed : FALSE    */
    /*      FAILED    => PASSED     : all passed : TRUE / not all passed : FALSE    */
    /*      NotTested => PASSED     : all passed : TRUE / not all passed : FALSE    */
    /*------------------------------------------------------------------------------*/
    updateFlag              =   Dem_Event_JudgeUpdateToPassed_InEvtStrg( EventCtrlIndex );      /* [GUDCHK:CALLER]EventCtrlIndex */

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )    /*  [FuncSw]    */
    Dem_Event_SavePassedTgtBit_ByEvtCtrlIdx( EventCtrlIndex, (boolean)TRUE );
#endif  /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )             */

#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )  /*  [FuncSw]    */
    /*  update to Tested.       */
    Dem_AltIUMPR_SetTestCompleteThisCycle( EventCtrlIndex, DEM_ALTIUMPR_TCTOC_TESTCOMPLETE );   /* [GUDCHK:CALLER]EventCtrlIndex *//* [UpdRec]AltIUMPR */
#endif  /* ( DEM_ALTIUMPR_SUPPORT == STD_ON )           */

    return updateFlag;
}


/****************************************************************************/
/* Function Name | Dem_Event_JudgeUpdateToPassed_InEvtStrg                  */
/* Description   | Update qualification info : PASSED.                      */
/* Preconditions |                                                          */
/* Parameters    | [in] EventCtrlIndex :                                    */
/* Return Value  | FALSE : no update.                                       */
/*               | TRUE  : update.                                          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-9-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Event_JudgeUpdateToPassed_InEvtStrg
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex     /* MISRA DEVIATION *//* [PRMCHK:CALLER] */
)
{
    VAR( boolean, AUTOMATIC ) updateFlag;

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )   /*  [FuncSw]    */
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexCnt;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexNum;
    VAR( Dem_u08_EventQualificationType, AUTOMATIC ) atherQualification;
    VAR( boolean, AUTOMATIC ) availableStatus;
#endif  /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )            */

    updateFlag  =   (boolean)TRUE;

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )   /*  [FuncSw]    */
    eventStrgIndex      =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );    /*  get EventStrgIndex.                                 *//* [GUDCHK:CALLER]EventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */
    eventCtrlIndexNum   =   Dem_CmbEvt_NumOfEventCtrlIndex_InEvtStrgGrp( eventStrgIndex );      /*  get EventCtrlIndex of EventStorageGroup max number  *//* [GUDCHK:CALLER]EventCtrlIndex */
    eventCtrlIndex      =   EventCtrlIndex;

    /* ALL Qualification is PASSED in event storage group : update TRUE   */
    /* FAILED or NOT Qualification in storage group       : update FALSE  */
    for ( eventCtrlIndexCnt = ( Dem_u16_EventCtrlIndexType )0U; eventCtrlIndexCnt < eventCtrlIndexNum; eventCtrlIndexCnt++ )
    {
        availableStatus = Dem_DataAvl_GetEvtAvl( eventCtrlIndex );                                      /* [GUD:RET:TRUE] eventCtrlIndex */
        if( availableStatus == (boolean)TRUE )
        {
            atherQualification  =   Dem_EventQualificationList[ eventCtrlIndex ];                       /* [GUD]eventCtrlIndex */
            if ( atherQualification != DEM_EVENT_QUALIFICATION_PASSED )
            {
                /*  there is FAILED or NOT Qualification status event in eventstorage group. */
                /*  not update.             */
                updateFlag  =   (boolean)FALSE;
                break;
            }
        }
        eventCtrlIndex      =   Dem_CmbEvt_GetNextEventCtrlIndex_InEvtStrgGrp( eventCtrlIndex );    /* [GUDCHK:CALLER]EventCtrlIndex *//*  get Delegate EventCtrlIndex                         */
    }
#endif  /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )            */

    return updateFlag;
}

/****************************************************************************/
/* Function Name | Dem_Event_UpdateFailedToNotQualified_InEvtStrg           */
/* Description   | Update qualification info : Failed => NotQualified.      */
/* Preconditions |                                                          */
/* Parameters    | [in] EventCtrlIndex :                                    */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Event_UpdateFailedToNotQualified_InEvtStrg
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex     /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexCnt;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexNum;
    VAR( Dem_u08_EventQualificationType, AUTOMATIC ) qualification;

    eventStrgIndex      =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );    /*  get EventStrgIndex.                                 *//* [GUDCHK:CALLER]EventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */
    eventCtrlIndexNum   =   Dem_CmbEvt_NumOfEventCtrlIndex_InEvtStrgGrp( eventStrgIndex );      /*  get EventCtrlIndex of EventStorageGroup max number  *//* [GUDCHK:CALLER]EventCtrlIndex */
    eventCtrlIndex      =   EventCtrlIndex;

    for ( eventCtrlIndexCnt = ( Dem_u16_EventCtrlIndexType )0U; eventCtrlIndexCnt < eventCtrlIndexNum; eventCtrlIndexCnt++ )
    {
        qualification  =   Dem_EventQualificationList[ eventCtrlIndex ];                                /* [GUDCHK:CALLER]EventCtrlIndex */

        if ( qualification == DEM_EVENT_QUALIFICATION_FAILED )
        {
            Dem_EventQualificationList[ eventCtrlIndex ]    =   DEM_EVENT_QUALIFICATION_NOTQUALIFIED;   /* [GUDCHK:CALLER]EventCtrlIndex */
        }
        /*  next event.     */
        eventCtrlIndex      =   Dem_CmbEvt_GetNextEventCtrlIndex_InEvtStrgGrp( eventCtrlIndex );        /* [GUDCHK:CALLER]EventCtrlIndex */
    }

    return ;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
