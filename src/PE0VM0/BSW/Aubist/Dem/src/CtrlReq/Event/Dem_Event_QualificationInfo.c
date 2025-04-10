/* Dem_Event_QualificationInfo_c(v5-5-0)                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
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
    P2VAR( Dem_u08_EventQualificationType, AUTOMATIC, AUTOMATIC ) EventQualificationPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) IsPassedToPassedPtr
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
static VAR( Dem_u08_EventQualificationType, DEM_VAR_NO_INIT ) Dem_EventQualificationList[ DEM_PRIMEM_EVENT_NUM ];

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
/* Parameters    | [in] EventStatus :                                       */
/*               |        report values of monitor test                     */
/*               | [out] EventQualificationPtr :                            */
/*               |        result of event qualification                     */
/*               | [out] UpdateDataFlagPtr :                                */
/*               |        Data update presence flag (TRUE:there is update,  */
/*               |         FALSE: there is no update)                       */
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
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Event_SetQualificationInfo
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,        /* [PRMCHK:CALLER] */
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    P2VAR( Dem_u08_EventQualificationType, AUTOMATIC, AUTOMATIC ) EventQualificationPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) IsPassedToPassedPtr
)
{
    VAR( boolean, AUTOMATIC ) updateFlag;
    *IsPassedToPassedPtr    =   (boolean)FALSE;

    updateFlag          =   (boolean)FALSE;
    if ( EventStatus == DEM_EVENT_STATUS_PASSED )
    {
        updateFlag  =   Dem_Event_UpdateQualificationInfo_Passed( EventCtrlIndex, EventQualificationPtr, IsPassedToPassedPtr ); /* [GUDCHK:CALLER]EventCtrlIndex */
    }
    else if ( EventStatus == DEM_EVENT_STATUS_FAILED )
    {
        updateFlag  =   Dem_Event_UpdateQualificationInfo_Failed( EventCtrlIndex, EventQualificationPtr );                      /* [GUDCHK:CALLER]EventCtrlIndex */
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
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Event_SetQualificationInfo_Specific
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,        /* [PRMCHK:CALLER] */
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    P2VAR( Dem_u08_EventQualificationType, AUTOMATIC, AUTOMATIC ) EventQualificationPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) IsPassedToPassedPtr
)
{
    VAR( boolean, AUTOMATIC ) updateFlag;
    *IsPassedToPassedPtr    =   (boolean)FALSE;

    updateFlag          =   (boolean)FALSE;
    if ( EventStatus == DEM_EVENT_STATUS_PASSED )
    {
        updateFlag  =   Dem_Event_UpdateQualificationInfo_Passed( EventCtrlIndex, EventQualificationPtr, IsPassedToPassedPtr ); /* [GUDCHK:CALLER]EventCtrlIndex */
    }
    else if ( EventStatus == DEM_EVENT_STATUS_FAILED )
    {
        updateFlag  =   Dem_Event_UpdateQualificationInfo_Failed_Specific( EventCtrlIndex, EventQualificationPtr );             /* [GUDCHK:CALLER]EventCtrlIndex */
    }
    else
    {
        /*  no process.     */
    }
    return updateFlag;
}
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )     */


/****************************************************************************/
/* Function Name | Dem_Event_ClearFailedQualificationInfo_NotTestedInCycle  */
/* Description   | Update qualification info : FAILED.                      */
/* Preconditions |                                                          */
/* Parameters    | [in] EventCtrlIndex :                                    */
/* Return Value  | void                                                     */
/* Notes         | call from Update operation cycle. / overflow event.      */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Event_ClearTargetQualificationInfo_NotTestedInCycle
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex     /* [PRMCHK:CALLER] */
)
{
    Dem_EventQualificationList[ EventCtrlIndex ]    =   DEM_EVENT_QUALIFICATION_NOTQUALIFIED;           /* [GUDCHK:CALLER]EventCtrlIndex */

#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )  /*  [FuncSw]    */
    Dem_AltIUMPR_SetTestCompleteThisCycle( EventCtrlIndex, DEM_ALTIUMPR_TCTOC_NOTTESTCOMPLETE );        /* [GUDCHK:CALLER]EventCtrlIndex */
#endif  /* ( DEM_ALTIUMPR_SUPPORT == STD_ON )           */

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Event_ClearFailedQualificationInfo_NotTestedInCycle  */
/* Description   | Update qualification info : FAILED.                      */
/* Preconditions |                                                          */
/* Parameters    | [in] EventCtrlIndex :                                    */
/* Return Value  | void                                                     */
/* Notes         | call from Update operation cycle. / overflow event.      */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
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
    }

#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )  /*  [FuncSw]    */
    if (( FailureCycleFlag & DEM_OPCYCUPD_FLCYC_UPDSTATUS_TNCTOC ) == DEM_OPCYCUPD_FLCYC_UPDSTATUS_TNCTOC )
    {
        Dem_AltIUMPR_SetTestCompleteThisCycle( EventCtrlIndex, DEM_ALTIUMPR_TCTOC_NOTTESTCOMPLETE );    /* [GUDCHK:CALLER]EventCtrlIndex */
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
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Event_ClearFailedQualificationInfo_NotTestedInCycle
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex     /* [PRMCHK:CALLER] */
)
{
    /*  update in EvtStrgGrp : FAILED => NOT_QUALIFIED.     */
    Dem_Event_UpdateFailedToNotQualified_InEvtStrg( EventCtrlIndex );                               /* [GUDCHK:CALLER]EventCtrlIndex */

#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )  /*  [FuncSw]    */
    /*  update to NotTested.        */
    Dem_AltIUMPR_SetTestCompleteThisCycle( EventCtrlIndex, DEM_ALTIUMPR_TCTOC_NOTTESTCOMPLETE );    /* [GUDCHK:CALLER]EventCtrlIndex */
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
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Event_ClearFailedQualificationInfo_nochange
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex     /* [PRMCHK:CALLER] */
)
{
    /*  update in EvtStrgGrp : FAILED => NOT_QUALIFIED.     */
    Dem_Event_UpdateFailedToNotQualified_InEvtStrg( EventCtrlIndex );                           /* [GUDCHK:CALLER]EventCtrlIndex */

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
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Event_ClearAndPassedQualificationInfo_TestedInCycle
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex     /* [PRMCHK:CALLER] */
)
{
    Dem_EventQualificationList[ EventCtrlIndex ]    =   DEM_EVENT_QUALIFICATION_PASSED;         /* [GUDCHK:CALLER]EventCtrlIndex */

    /*  update in EvtStrgGrp : FAILED => NOT_QUALIFIED.     */
    Dem_Event_UpdateFailedToNotQualified_InEvtStrg( EventCtrlIndex );                           /* [GUDCHK:CALLER]EventCtrlIndex */

#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )  /*  [FuncSw]    */
    /*  update to NotTested.        */
    Dem_AltIUMPR_SetTestCompleteThisCycle( EventCtrlIndex, DEM_ALTIUMPR_TCTOC_TESTCOMPLETE );   /* [GUDCHK:CALLER]EventCtrlIndex */
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
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
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
        Dem_AltIUMPR_SetTestCompleteThisCycle( eventCtrlIndex, DEM_ALTIUMPR_TCTOC_NOTTESTCOMPLETE );    /* [GUDCHK:CALLER]EventStrgIndex */
#endif  /* ( DEM_ALTIUMPR_SUPPORT == STD_ON )           */

        /*  get next Index.         */
        eventCtrlIndex  =   Dem_CmbEvt_GetNextEventCtrlIndex_InEvtStrgGrp( eventCtrlIndex );            /* [GUDCHK:CALLER]EventStrgIndex */
    }

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
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
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
    *EventQualificationPtr  =   newQualification;

#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )  /*  [FuncSw]    */
    /*  update to Tested.       */
    Dem_AltIUMPR_SetTestCompleteThisCycle( EventCtrlIndex, DEM_ALTIUMPR_TCTOC_TESTCOMPLETE );   /* [GUDCHK:CALLER]EventCtrlIndex */
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
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Event_UpdateQualificationInfo_Failed_Specific
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,        /* [PRMCHK:CALLER] */
    P2VAR( Dem_u08_EventQualificationType, AUTOMATIC, AUTOMATIC ) EventQualificationPtr
)
{
    VAR( boolean, AUTOMATIC ) updateFlag;

    Dem_EventQualificationList[ EventCtrlIndex ]    =   DEM_EVENT_QUALIFICATION_FAILED;         /* [GUDCHK:CALLER]EventCtrlIndex */
    *EventQualificationPtr  =   DEM_EVENT_QUALIFICATION_FAILED;
    updateFlag          =   (boolean)TRUE;

#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )  /*  [FuncSw]    */
    /*  update to Tested.       */
    Dem_AltIUMPR_SetTestCompleteThisCycle( EventCtrlIndex, DEM_ALTIUMPR_TCTOC_TESTCOMPLETE );   /* [GUDCHK:CALLER]EventCtrlIndex */
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
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Event_UpdateQualificationInfo_Passed
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,        /* [PRMCHK:CALLER] */
    P2VAR( Dem_u08_EventQualificationType, AUTOMATIC, AUTOMATIC ) EventQualificationPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) IsPassedToPassedPtr
)
{
    VAR( boolean, AUTOMATIC ) updateFlag;
    VAR( Dem_u08_EventQualificationType, AUTOMATIC ) oldQualification;

    oldQualification    =   Dem_EventQualificationList[ EventCtrlIndex ];                       /* [GUDCHK:CALLER]EventCtrlIndex */
    *IsPassedToPassedPtr    =   (boolean)FALSE;
    if ( oldQualification == DEM_EVENT_QUALIFICATION_PASSED )
    {
        /*  PASSED => PASSED    */
        /*  no update.          */
        Dem_EventQualificationList[ EventCtrlIndex ]    =   DEM_EVENT_QUALIFICATION_PASSED;     /* [GUDCHK:CALLER]EventCtrlIndex */
        updateFlag          =   (boolean)FALSE;
        *IsPassedToPassedPtr  =   (boolean)TRUE;
    }
    else if ( oldQualification == DEM_EVENT_QUALIFICATION_FAILED )
    {
        /*  FAILED => PASSED    */
        Dem_EventQualificationList[ EventCtrlIndex ]    =   DEM_EVENT_QUALIFICATION_PASSED;     /* [GUDCHK:CALLER]EventCtrlIndex */
        updateFlag          =   Dem_Event_JudgeUpdateToPassed_InEvtStrg( EventCtrlIndex );      /* [GUDCHK:CALLER]EventCtrlIndex */
    }
    else /* ( oldQualification == DEM_EVENT_QUALIFICATION_NOTQUALIFIED )    */
    {
        /*  NotTested => PASSED */
        Dem_EventQualificationList[ EventCtrlIndex ]    =   DEM_EVENT_QUALIFICATION_PASSED;     /* [GUDCHK:CALLER]EventCtrlIndex */
        updateFlag          =   Dem_Event_JudgeUpdateToPassed_InEvtStrg( EventCtrlIndex );      /* [GUDCHK:CALLER]EventCtrlIndex */
    }
    *EventQualificationPtr  =   Dem_EventQualificationList[ EventCtrlIndex ];                   /* [GUDCHK:CALLER]EventCtrlIndex */

#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )  /*  [FuncSw]    */
    /*  update to Tested.       */
    Dem_AltIUMPR_SetTestCompleteThisCycle( EventCtrlIndex, DEM_ALTIUMPR_TCTOC_TESTCOMPLETE );   /* [GUDCHK:CALLER]EventCtrlIndex */
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
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Event_JudgeUpdateToPassed_InEvtStrg
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex     /* [PRMCHK:CALLER] */
)
{
    VAR( boolean, AUTOMATIC ) updateFlag;

    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexCnt;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexNum;
    VAR( Dem_u08_EventQualificationType, AUTOMATIC ) atherQualification;

    eventStrgIndex      =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );    /*  get EventStrgIndex.                                 *//* [GUDCHK:CALLER]EventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */
    eventCtrlIndexNum   =   Dem_CmbEvt_NumOfEventCtrlIndex_InEvtStrgGrp( eventStrgIndex );      /*  get EventCtrlIndex of EventStorageGroup max number  *//* [GUDCHK:CALLER]EventCtrlIndex */
    eventCtrlIndex      =   EventCtrlIndex;

    updateFlag  =   (boolean)TRUE;
    /* ALL Qualification is PASSED in event storage group : update TRUE   */
    /* FAILED or NOT Qualification in storage group       : update FALSE  */
    for ( eventCtrlIndexCnt = ( Dem_u16_EventCtrlIndexType )0U; eventCtrlIndexCnt < eventCtrlIndexNum; eventCtrlIndexCnt++ )
    {
        atherQualification  =   Dem_EventQualificationList[ eventCtrlIndex ];                       /* [GUDCHK:CALLER]EventCtrlIndex */
        if ( atherQualification != DEM_EVENT_QUALIFICATION_PASSED )
        {
            /*  there is FAILED or NOT Qualification status event in eventstorage group. */
            /*  not update.             */
            updateFlag  =   (boolean)FALSE;
            break;
        }
        eventCtrlIndex      =   Dem_CmbEvt_GetNextEventCtrlIndex_InEvtStrgGrp( eventCtrlIndex );    /* [GUDCHK:CALLER]EventCtrlIndex *//*  get Delegate EventCtrlIndex                         */
    }

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
/****************************************************************************/

/**** End of File ***********************************************************/
