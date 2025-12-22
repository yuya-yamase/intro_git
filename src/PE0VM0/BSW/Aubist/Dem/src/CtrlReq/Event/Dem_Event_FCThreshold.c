/* Dem_Event_FCThreshold_c(v5-9-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Event_FCThreshold/CODE                                */
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
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_Event.h"

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
#define DEM_START_SEC_CODE_TRUST        /*  PreInit section     */
#include <Dem_MemMap.h>

static FUNC( void, DEM_CODE_TRUST ) Dem_Event_InitializeFCThresholdValue
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);


#define DEM_STOP_SEC_CODE_TRUST         /*  PreInit section     */
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( void, DEM_CODE ) Dem_Event_ResetFCThresholdValue
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);

static FUNC( void, DEM_CODE ) Dem_Event_SetFCThresholdValue
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u08_FailureCounterType, AUTOMATIC ) FailureCycleCounterThreshold
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Saved temporary area of update prohibition record                        */
/****************************************************************************/
static VAR( Dem_u08_FailureCounterType, DEM_VAR_NO_INIT ) Dem_FailureCounterThreshold[ DEM_PRIMEM_EVENTSTORAGE_NUM ];

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )
static VAR( Dem_u08_FailureCounterType, DEM_VAR_NO_INIT ) Dem_FailureCounterThresholdRequest[ DEM_PRIMEM_EVENT_NUM ];
#endif  /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )    */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions(PreInit section)                                      */
/****************************************************************************/
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Data_PreInitEventFailureCycleCounterThreshold        */
/* Description   | Initial data set to Dem_FailureCounterThreshold Table    */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | PreInit  are an opportunity to start.                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE_TRUST ) Dem_Event_PreInitEventFailureCycleCounterThreshold
( void )
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    /*  set calibration / configuration value.  */
    for( eventStrgIndex = 0U; eventStrgIndex < eventStorageNum; eventStrgIndex++ )  /* [GUD:for]eventStrgIndex */
    {
        Dem_Event_InitializeFCThresholdValue( eventStrgIndex );                     /* [GUD]eventStrgIndex */
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_Event_InitializeFCThresholdValue                     */
/* Description   | Initial data set to Dem_FailureCounterThreshold Table    */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/* Return Value  | none                                                     */
/* Notes         | PreInit  are an opportunity to start.                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE_TRUST ) Dem_Event_InitializeFCThresholdValue
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexCnt;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexNum;

    VAR( Dem_u08_FailureCounterType, AUTOMATIC ) failureCycleCounterThreshold;
    VAR( Dem_u08_FailureCounterType, AUTOMATIC ) failureCycleCounterThresholdConfig;

    /*  set calibration / configuration value.  */
    eventCtrlIndexNum   =   Dem_CmbEvt_NumOfEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );          /*  get EventCtrlIndex of EventStorageGroup max number  */
    eventCtrlIndex      =   Dem_CmbEvt_GetDelegateEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );    /*  get Delegate EventCtrlIndex                         *//* [GUDCHK:CALLER]EventStrgIndex *//* [GUD:RET:IF_GUARDED: EventStrgIndex ] eventCtrlIndex */

    /*  start value : minimum value.        */
    failureCycleCounterThreshold    =   DEM_CALIB_FAILURECYCLECNT_THRESHOLD_MIN;
    for ( eventCtrlIndexCnt = ( Dem_u16_EventCtrlIndexType )0U; eventCtrlIndexCnt < eventCtrlIndexNum; eventCtrlIndexCnt++ )
    {
        /*  get failure cycle threshold     */
        failureCycleCounterThresholdConfig  =   Dem_CfgInfoPm_GetFCThreshold( eventCtrlIndex );         /* [GUDCHK:CALLER]EventStrgIndex */

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )   /*  [FuncSw]    */
        Dem_FailureCounterThresholdRequest[ eventCtrlIndex ]   =   failureCycleCounterThresholdConfig;  /* [GUDCHK:CALLER]EventStrgIndex */
#endif  /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )            */

        /*  get maximum value in event storage group.       */
        if ( failureCycleCounterThreshold < failureCycleCounterThresholdConfig )
        {
            failureCycleCounterThreshold    =   failureCycleCounterThresholdConfig;
        }
        /*  get next Index.         */
        eventCtrlIndex  =   Dem_CmbEvt_GetNextEventCtrlIndex_InEvtStrgGrp( eventCtrlIndex );            /* [GUDCHK:CALLER]EventStrgIndex */
    }

    /*  set value.                  */
    Dem_FailureCounterThreshold[ EventStrgIndex ]   =   failureCycleCounterThreshold;   /* [GUDCHK:CALLER]EventStrgIndex */

    return;
}

#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Event_ResetFCThresholdValue                          */
/* Description   | Reset data set to Dem_FailureCounterThreshold Table      */
/* Preconditions |                                                          */
/* Parameters    | [in] EventCtrlIndex                                      */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Event_ResetFCThresholdValue
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex             /* [PRMCHK:CALLER] */
)
{
    /*  set calibration / configuration value.  */
    Dem_FailureCounterThresholdRequest[ EventCtrlIndex ]   =   Dem_CfgInfoPm_GetFCThreshold( EventCtrlIndex );  /* [GUDCHK:CALLER]EventCtrlIndex */

    /*  update FCThreshold data     */
    Dem_Event_UpdateFCThresholdValue_InEvtStrgGrp( EventCtrlIndex );        /* [GUDCHK:CALLER]EventCtrlIndex */

    return;
}


/****************************************************************************/
/* Function Name | Dem_Event_SetFCThresholdValue                            */
/* Description   | Set data set to Dem_FailureCounterThreshold Table        */
/* Preconditions |                                                          */
/* Parameters    | [in] EventCtrlIndex                                      */
/*               | [in] FailureCycleCounterThreshold :                      */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Event_SetFCThresholdValue
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_u08_FailureCounterType, AUTOMATIC ) FailureCycleCounterThreshold
)
{
    /*  set request data            */
    Dem_FailureCounterThresholdRequest[ EventCtrlIndex ] = FailureCycleCounterThreshold;        /* [GUDCHK:CALLER]EventCtrlIndex */

    /*  update FCThreshold data     */
    Dem_Event_UpdateFCThresholdValue_InEvtStrgGrp( EventCtrlIndex );        /* [GUDCHK:CALLER]EventCtrlIndex */

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Event_UpdateFCThresholdValue_InEvtStrgGrp            */
/* Description   | update data set to Dem_FailureCounterThreshold Table     */
/* Preconditions |                                                          */
/* Parameters    | [in] EventCtrlIndex                                      */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-9-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Event_UpdateFCThresholdValue_InEvtStrgGrp
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex             /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexCnt;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

    VAR( Dem_u08_FailureCounterType, AUTOMATIC ) failureCycleCounterThresholdStore;
    VAR( Dem_u08_FailureCounterType, AUTOMATIC ) failureCycleCounterThresholdRequest;
    VAR( boolean, AUTOMATIC ) availableStatus;

    /*  set calibration / configuration value.  */
    eventStrgIndex      =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );        /* [GUDCHK:CALLER]EventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */

    eventCtrlIndexNum   =   Dem_CmbEvt_NumOfEventCtrlIndex_InEvtStrgGrp( eventStrgIndex );          /*  get EventCtrlIndex of EventStorageGroup max number  */
    eventCtrlIndex      =   EventCtrlIndex;

    /*  start value : minimum value.        */
    failureCycleCounterThresholdStore    =   DEM_CALIB_FAILURECYCLECNT_THRESHOLD_MIN;
    for ( eventCtrlIndexCnt = ( Dem_u16_EventCtrlIndexType )0U; eventCtrlIndexCnt < eventCtrlIndexNum; eventCtrlIndexCnt++ )
    {
        availableStatus = Dem_DataAvl_GetEvtAvl( eventCtrlIndex );
        if( availableStatus == (boolean)TRUE )
        {
            /*  get failure cycle threshold     */
            failureCycleCounterThresholdRequest  =   Dem_FailureCounterThresholdRequest[ eventCtrlIndex ];  /* [GUDCHK:CALLER]EventCtrlIndex */
    
            /*  get maximum value in event storage group.       */
            if ( failureCycleCounterThresholdStore < failureCycleCounterThresholdRequest )
            {
                failureCycleCounterThresholdStore    =   failureCycleCounterThresholdRequest;
            }
        }
        /*  get next Index.         */
        eventCtrlIndex  =   Dem_CmbEvt_GetNextEventCtrlIndex_InEvtStrgGrp( eventCtrlIndex );            /* [GUDCHK:CALLER]EventCtrlIndex */
    }

    /*  set value.                  */
    Dem_FailureCounterThreshold[ eventStrgIndex ]   =   failureCycleCounterThresholdStore;              /* [GUDCHK:CALLER]EventCtrlIndex */

    return;
}


#endif  /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )            */

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_Event_ResetFCThresholdValue                          */
/* Description   | Reset data set to Dem_FailureCounterThreshold Table      */
/* Preconditions |                                                          */
/* Parameters    | [in] EventCtrlIndex                                      */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Event_ResetFCThresholdValue
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex             /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

    eventStrgIndex      =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );            /* [GUDCHK:CALLER]EventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */

    /*  set value.                  */
    Dem_FailureCounterThreshold[ eventStrgIndex ]   =   Dem_CfgInfoPm_GetFCThreshold( EventCtrlIndex ); /* [GUDCHK:CALLER]EventCtrlIndex */

    return;
}

/****************************************************************************/
/* Function Name | Dem_Event_SetFCThresholdValue                            */
/* Description   | Set data set to Dem_FailureCounterThreshold Table        */
/* Preconditions |                                                          */
/* Parameters    | [in] EventCtrlIndex                                      */
/*               | [in] FailureCycleCounterThreshold :                      */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Event_SetFCThresholdValue
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_u08_FailureCounterType, AUTOMATIC ) FailureCycleCounterThreshold
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

    eventStrgIndex      =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );            /* [GUDCHK:CALLER]EventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */

    /*  set value.                  */
    Dem_FailureCounterThreshold[ eventStrgIndex ]   =   FailureCycleCounterThreshold;                   /* [GUDCHK:CALLER]EventCtrlIndex */

    return;
}
#endif  /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_OFF )           */

/****************************************************************************/
/* Function Name | Dem_Event_ResetEventFailureCycleCounterThreshold         */
/* Description   | Reset FailureCycleCounterThreshold in RAM-Data.          */
/*               | This function sets a FailureCounterThreshold data .      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventCtrlIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : A change of the                      */
/*               |        FailureCycleCounterThreshold succeeded.           */
/*               |        DEM_IRT_NG : A change of the                      */
/*               |        FailureCycleCounterThreshold failed.              */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Event_ResetEventFailureCycleCounterThreshold
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex     /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) fcAdaptable;

    retVal = DEM_IRT_NG;
    fcAdaptable   =   Dem_CfgInfoPm_GetFCThresholdAdaptable( EventCtrlIndex );          /* [GUDCHK:CALLER]EventCtrlIndex */

    /* Check Configuration Data DemEventFailureCycleCounterThresholdAdaptable for EventId*/
    if( fcAdaptable == (boolean)TRUE )
    {
        Dem_Event_ResetFCThresholdValue( EventCtrlIndex );                              /* [GUDCHK:CALLER]EventCtrlIndex */

        retVal = DEM_IRT_OK;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Event_SetEventFailureCycleCounterThreshold           */
/* Description   | Sets FailureCycleCounterThreshold in RAM-Data.           */
/*               | This function sets a FailureCounterThreshold data .      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventCtrlIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/*               | [in] FailureCycleCounterThreshold :                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : A change of the                      */
/*               |        FailureCycleCounterThreshold succeeded.           */
/*               |        DEM_IRT_NG : A change of the                      */
/*               |        FailureCycleCounterThreshold failed.              */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Event_SetEventFailureCycleCounterThreshold
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_u08_FailureCounterType, AUTOMATIC ) FailureCycleCounterThreshold
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) fcAdaptable;

    retVal = DEM_IRT_NG;
    fcAdaptable   =   Dem_CfgInfoPm_GetFCThresholdAdaptable( EventCtrlIndex );                  /* [GUDCHK:CALLER]EventCtrlIndex */

    /* Check Configuration Data DemEventFailureCycleCounterThresholdAdaptable for EventId*/
    if( fcAdaptable == (boolean)TRUE )
    {
        if( FailureCycleCounterThreshold >= DEM_CALIB_FAILURECYCLECNT_THRESHOLD_MIN )
        {
            Dem_Event_SetFCThresholdValue( EventCtrlIndex, FailureCycleCounterThreshold );      /* [GUDCHK:CALLER]EventCtrlIndex */

            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Event_GetEventFailureCycleCounterThreshold           */
/* Description   | Gets FailureCycleCounterThreshold in RAM-Data.           */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/* Return Value  | Dem_u08_FailureCounterType                               */
/*               |        value of FailureCycleCounterThreshold.            */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_FailureCounterType, DEM_CODE ) Dem_Event_GetEventFailureCycleCounterThreshold
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC )                EventStrgIndex      /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_FailureCounterType, AUTOMATIC )     FailureCycleCounterThreshold;

    FailureCycleCounterThreshold = Dem_FailureCounterThreshold[EventStrgIndex]; /* [GUDCHK:CALLER]EventStrgIndex */

    return FailureCycleCounterThreshold;
}

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
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
