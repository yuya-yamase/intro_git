/* Dem_DataAvl_PriMem_c(v5-5-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataAvl/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON )
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_DataAvl.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
typedef uint8       Dem_u08_EventAvailableType;              /*  EventAvailable table type       */

#define DEM_EVTAVL_NOTAVAILABLE         ((Dem_u08_EventAvailableType)0x00U)     /*  eventAvailable : not available      */
#define DEM_EVTAVL_AVAILABLE_CTRL       ((Dem_u08_EventAvailableType)0x5AU)     /*  eventAvailable : EventCtrlIndex     */
#define DEM_EVTAVL_AVAILABLE_STRG       ((Dem_u08_EventAvailableType)0xA5U)     /*  eventAvailable : EventStrgIndex     */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes(PreInit section)                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

static FUNC( void, DEM_CODE_TRUST ) Dem_DataAvl_ResetEventAvailableValue       /*  PreInit section     */
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
static FUNC( void, DEM_CODE_TRUST ) Dem_DataAvl_SetEventAvailableValue_InEvtStrgGrp       /*  PreInit section     */
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( void, DEM_CODE_TRUST ) Dem_DataAvl_SetNotEventAvailableValue_InEvtStrgGrp       /*  PreInit section     */
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_u08_EventAvailableType, DEM_VAR_NO_INIT ) Dem_DataAvl_EvtAvlData[ DEM_PRIMEM_EVENT_NUM ];

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions(PreInit section)                                      */
/****************************************************************************/
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_DataAvl_PreInitForAvl_PriMem                         */
/* Description   | Pre-initializes Dem_DataAvl.                             */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE_TRUST ) Dem_DataAvl_PreInitForAvl_PriMem       /*  PreInit section     */
( void )
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    /*  set available initialize status :   EventStrgIndex      */
    for( eventStrgIndex = ( Dem_u16_EventStrgIndexType )0U; eventStrgIndex < eventStorageNum; eventStrgIndex++ )        /* [GUD:for]eventStrgIndex */
    {
        Dem_DataAvl_ResetEventAvailableValue( eventStrgIndex );                                                         /* [GUD]eventStrgIndex */
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_DataAvl_ResetEventAvailableValue                     */
/* Description   | Pre-initializes Dem_DataAvl.                             */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE_TRUST ) Dem_DataAvl_ResetEventAvailableValue       /*  PreInit section     */
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex     /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexCnt;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexNum;
    VAR( Dem_u08_EventAvailableType, AUTOMATIC ) eventAvailableStatus;
    VAR( boolean, AUTOMATIC ) eventAvailableConfig;
    VAR( boolean, AUTOMATIC ) eventStrgAvailableFlag;
    VAR( boolean, AUTOMATIC ) eventNotAvailableFlag;

    /*  set calibration / configuration value.  */
    eventCtrlIndexNum   =   Dem_CmbEvt_NumOfEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );          /*  get EventCtrlIndex of EventStorageGroup max number  */

    /*----------------------------------*/
    /*  set initial value loop          */
    /*----------------------------------*/
    eventCtrlIndex      =   Dem_CmbEvt_GetDelegateEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );    /*  get Delegate EventCtrlIndex *//* [GUDCHK:CALLER]EventStrgIndex *//* [GUD:RET:IF_GUARDED:EventStrgIndex]eventCtrlIndex */
    eventStrgAvailableFlag  =   (boolean)FALSE;
    eventNotAvailableFlag   =   (boolean)FALSE;
    for ( eventCtrlIndexCnt = ( Dem_u16_EventCtrlIndexType )0U; eventCtrlIndexCnt < eventCtrlIndexNum; eventCtrlIndexCnt++ )
    {
        /*  get event available status(eventctrl)     */
        eventAvailableConfig    =   Dem_CfgInfoPm_GetEventAvailable( eventCtrlIndex );              /* [GUDCHK:CALLER]EventStrgIndex */
        if ( eventAvailableConfig != (boolean)FALSE )
        {
            eventAvailableStatus    =   ( DEM_EVTAVL_AVAILABLE_CTRL | DEM_EVTAVL_AVAILABLE_STRG );
            eventStrgAvailableFlag  =   (boolean)TRUE;      /*  after check : STRG event available check for same group event.  */
        }
        else
        {
            eventAvailableStatus    =   DEM_EVTAVL_NOTAVAILABLE;
            eventNotAvailableFlag   =   (boolean)TRUE;      /*  after check : STRG event available check.   */
        }
        Dem_DataAvl_EvtAvlData[ eventCtrlIndex ] = eventAvailableStatus;                            /* [GUDCHK:CALLER]EventStrgIndex */

        /*  get next Index.         */
        eventCtrlIndex  =   Dem_CmbEvt_GetNextEventCtrlIndex_InEvtStrgGrp( eventCtrlIndex );        /* [GUDCHK:CALLER]EventStrgIndex */
    }

    /*----------------------------------*/
    /*  set StrgEventAvalilable loop    */
    /*----------------------------------*/
    if ( eventNotAvailableFlag == (boolean)TRUE )
    {
        /*  after STRG event available check check.     */
        if ( eventStrgAvailableFlag == (boolean)TRUE )
        {
            Dem_DataAvl_SetEventAvailableValue_InEvtStrgGrp( EventStrgIndex );  /* [GUDCHK:CALLER]EventStrgIndex */
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_DataAvl_SetEventAvailableValue_InEvtStrgGrp          */
/* Description   | Pre-initializes Dem_DataAvl.                             */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE_TRUST ) Dem_DataAvl_SetEventAvailableValue_InEvtStrgGrp       /*  PreInit section     */
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex     /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexCnt;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexNum;
    VAR( Dem_u08_EventAvailableType, AUTOMATIC ) eventAvailableStatus;

    /*  set calibration / configuration value.  */
    eventCtrlIndexNum   =   Dem_CmbEvt_NumOfEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );          /*  get EventCtrlIndex of EventStorageGroup max number  */

    /*--------------------------------------*/
    /*  check : number of ctrlindex is 2~   */
    /*--------------------------------------*/
    eventCtrlIndex      =   Dem_CmbEvt_GetDelegateEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );    /*  get Delegate EventCtrlIndex                         */
    for ( eventCtrlIndexCnt = ( Dem_u16_EventCtrlIndexType )0U; eventCtrlIndexCnt < eventCtrlIndexNum; eventCtrlIndexCnt++ )
    {
        eventAvailableStatus    =   Dem_DataAvl_EvtAvlData[ eventCtrlIndex ];                       /* [GUDCHK:CALLER]EventStrgIndex */

        /*  set EventAvaliable(Strg) : Available.       */
        eventAvailableStatus    =   ( eventAvailableStatus | DEM_EVTAVL_AVAILABLE_STRG );

        Dem_DataAvl_EvtAvlData[ eventCtrlIndex ] = eventAvailableStatus;                            /* [GUDCHK:CALLER]EventStrgIndex */

        /*  get next Index.         */
        eventCtrlIndex  =   Dem_CmbEvt_GetNextEventCtrlIndex_InEvtStrgGrp( eventCtrlIndex );
    }

    return ;
}

#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_DataAvl_SetNotEventAvailableValue_InEvtStrgGrp       */
/* Description   | Pre-initializes Dem_DataAvl.                             */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE_TRUST ) Dem_DataAvl_SetNotEventAvailableValue_InEvtStrgGrp       /*  PreInit section     */
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexCnt;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexNum;
    VAR( Dem_u08_EventAvailableType, AUTOMATIC ) eventAvailableStatus;
    VAR( boolean, AUTOMATIC ) eventAvailableFlag;

    /*  set calibration / configuration value.  */
    eventCtrlIndexNum   =   Dem_CmbEvt_NumOfEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );          /*  get EventCtrlIndex of EventStorageGroup max number  */

    /*------------------------------------------------------*/
    /*  check all available status in event storage group.  */
    /*------------------------------------------------------*/
    eventAvailableFlag  =   (boolean)FALSE;
    eventCtrlIndex      =   Dem_CmbEvt_GetDelegateEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );    /*  get Delegate EventCtrlIndex *//* [GUDCHK:CALLER]EventStrgIndex *//* [GUD:RET:IF_GUARDED:EventStrgIndex] eventCtrlIndex */
    for ( eventCtrlIndexCnt = ( Dem_u16_EventCtrlIndexType )0U; eventCtrlIndexCnt < eventCtrlIndexNum; eventCtrlIndexCnt++ )
    {
        eventAvailableStatus    =   Dem_DataAvl_EvtAvlData[ eventCtrlIndex ];                                                   /* [GUDCHK:CALLER]EventStrgIndex */

        /*  storage status ?                    */
        if (( eventAvailableStatus & DEM_EVTAVL_AVAILABLE_CTRL ) == DEM_EVTAVL_AVAILABLE_CTRL )
        {
            eventAvailableFlag  =   (boolean)TRUE;
            break;
        }
        /*  get next Index.         */
        eventCtrlIndex  =   Dem_CmbEvt_GetNextEventCtrlIndex_InEvtStrgGrp( eventCtrlIndex );
    }

    if ( eventAvailableFlag == (boolean)FALSE )
    {
        /*  all CTRL available status is NOT AVAILABLE.                         */
        /*  set all available status in event storage group : NOT AVAILABLE( OFF [DEM_EVTAVL_AVAILABLE_STRG] ). */
        eventCtrlIndex      =   Dem_CmbEvt_GetDelegateEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );    /*  get Delegate EventCtrlIndex                         */
        for ( eventCtrlIndexCnt = ( Dem_u16_EventCtrlIndexType )0U; eventCtrlIndexCnt < eventCtrlIndexNum; eventCtrlIndexCnt++ )
        {
            Dem_DataAvl_EvtAvlData[ eventCtrlIndex ]    =   DEM_EVTAVL_NOTAVAILABLE;                                            /* [GUDCHK:CALLER]EventStrgIndex */

            /*  get next Index.         */
            eventCtrlIndex  =   Dem_CmbEvt_GetNextEventCtrlIndex_InEvtStrgGrp( eventCtrlIndex );
        }
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_DataAvl_SetEvtAvl                                    */
/* Description   | Set the available status of a specific Event.            */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventCtrlIndex :                                    */
/*               |        Identification of an event.                       */
/*               | [in] AvailableStatus :                                   */
/*               |        This parameter specifies whether the respective   */
/*               |        Event shall be available (TRUE) or not (FALSE).   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Setting event available is           */
/*               |                     supported.                           */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataAvl_SetEvtAvl
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( boolean, AUTOMATIC ) AvailableStatus
)
{
    VAR( Dem_u08_EventAvailableType, AUTOMATIC ) oldAvailableStatus;
    VAR( Dem_u08_EventAvailableType, AUTOMATIC ) eventAvailableStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventConfigureNum;

    retVal = DEM_IRT_NG;

    eventConfigureNum = Dem_PrimaryMemEventConfigureNum;
    if ( EventCtrlIndex < eventConfigureNum )                                                               /* [GUD:if]EventCtrlIndex */
    {
        oldAvailableStatus  =   Dem_DataAvl_EvtAvlData[ EventCtrlIndex ];                                   /* [GUD]EventCtrlIndex */

        eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );                /* [GUD]EventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */
        if ( AvailableStatus != (boolean)FALSE )
        {
            eventAvailableStatus    =   ( DEM_EVTAVL_AVAILABLE_CTRL | DEM_EVTAVL_AVAILABLE_STRG );

            /*  set value.      */
            Dem_DataAvl_EvtAvlData[ EventCtrlIndex ] = eventAvailableStatus;                                /* [GUD]EventCtrlIndex */

            /*  old available : strg OFF ?  */
            if (( oldAvailableStatus & DEM_EVTAVL_AVAILABLE_STRG ) != DEM_EVTAVL_AVAILABLE_STRG )
            {
                /*  set STRG event available data(ON).  */
                Dem_DataAvl_SetEventAvailableValue_InEvtStrgGrp( eventStrgIndex );                          /* [GUD]eventStrgIndex */
            }

        }
        else
        {
            /*  CTRL event available status : OFF   */
            eventAvailableStatus    =   Dem_DataAvl_EvtAvlData[ EventCtrlIndex ];                           /* [GUD]EventCtrlIndex */

            eventAvailableStatus    =   eventAvailableStatus & ~DEM_EVTAVL_AVAILABLE_CTRL;

            /*  set value.      */
            Dem_DataAvl_EvtAvlData[ EventCtrlIndex ] = eventAvailableStatus;                                /* [GUD]EventCtrlIndex */

            /*  old available : ctrl ON ?   */
            if (( oldAvailableStatus & DEM_EVTAVL_AVAILABLE_CTRL ) == DEM_EVTAVL_AVAILABLE_CTRL )
            {
                /*  set STRG event available data(OFF). */
                Dem_DataAvl_SetNotEventAvailableValue_InEvtStrgGrp( eventStrgIndex );                       /* [GUD]eventStrgIndex */
            }
        }
        retVal = DEM_IRT_OK;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DataAvl_GetEvtAvl                                    */
/* Description   | Get the available status of a specific Event.            */
/* Preconditions | The specified event ID has been already registered.      */
/* Parameters    | [in] EventCtrlIndex :                                    */
/*               |        Identification of an event.                       */
/* Return Value  | boolean                                                  */
/*               |        TRUE : Event is available.                        */
/*               |        FALSE : Event is not available.                   */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_DataAvl_GetEvtAvl
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u08_EventAvailableType, AUTOMATIC ) eventAvailableStatus;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventConfigureNum;

    retVal = (boolean)FALSE;

    eventConfigureNum = Dem_PrimaryMemEventConfigureNum;
    if ( EventCtrlIndex < eventConfigureNum )                                                           /* [GUD:if]EventCtrlIndex */
    {
        eventAvailableStatus    =   Dem_DataAvl_EvtAvlData[ EventCtrlIndex ];                           /* [GUD]EventCtrlIndex */
        if( ( eventAvailableStatus & DEM_EVTAVL_AVAILABLE_CTRL ) == DEM_EVTAVL_AVAILABLE_CTRL )
        {
            retVal = (boolean)TRUE;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DataAvl_GetEvtAvl_InEvtStrgGrp                       */
/* Description   | Get the available status of a specific Event.            */
/* Preconditions | The specified event ID has been already registered.      */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Identification of an event.                       */
/* Return Value  | boolean                                                  */
/*               |        TRUE : Event is available.                        */
/*               |        FALSE : Event is not available.                   */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:TRUE] EventStrgIndex                            */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_DataAvl_GetEvtAvl_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u08_EventAvailableType, AUTOMATIC ) eventAvailableStatus;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    retVal = (boolean)FALSE;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if ( EventStrgIndex < eventStorageNum )                                                                 /* [GUD:if]EventStrgIndex */
    {
        eventCtrlIndex  =   Dem_CmbEvt_GetDelegateEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );    /*  get Delegate EventCtrlIndex *//* [GUD:if]EventStrgIndex *//* [GUD:RET:IF_GUARDED: EventStrgIndex ] eventCtrlIndex */

        eventAvailableStatus    =   Dem_DataAvl_EvtAvlData[ eventCtrlIndex ];                               /* [GUD]eventCtrlIndex */
        if( ( eventAvailableStatus & DEM_EVTAVL_AVAILABLE_STRG ) == DEM_EVTAVL_AVAILABLE_STRG )
        {
            retVal = (boolean)TRUE;
        }
    }
    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
