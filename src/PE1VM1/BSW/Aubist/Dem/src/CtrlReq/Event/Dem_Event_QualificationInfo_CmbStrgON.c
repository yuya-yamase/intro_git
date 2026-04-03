/* Dem_Event_QualificationInfo_CmbStrgON_c(v5-9-0)                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Event_QualilficationInfo_CmbStrgON/CODE               */
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
#include "../../../inc/Dem_Rc_DataMng.h"
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

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Event_LoadPassedBit_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
static FUNC( Dem_u16_EventCtrlIndexType, DEM_CODE ) Dem_Event_LoadPassedBitmap_ToQualification
(
    P2VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC, AUTOMATIC ) TargetEventCtrlIndexPtr,
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndexCheckRemainCount,
    VAR( Dem_u08_EventCtrlBitmapType, AUTOMATIC ) PassedBitmapData
);
static FUNC( void, DEM_CODE ) Dem_Event_SearchEventCtrlBitmapIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) TargetEventCtrlIndex,
    P2VAR( Dem_u08_EventCtrlBitmapIndexType, AUTOMATIC, AUTOMATIC ) EventCtrlBitmapIndexPtr,
    P2VAR( Dem_u08_EventCtrlBitmapWidthType, AUTOMATIC, AUTOMATIC ) EventCtrlBitOffsetPtr
);
static FUNC( Dem_u16_EventCtrlIndexType, DEM_CODE ) Dem_Event_MakePassedBitmap_fromQualification
(
    P2VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC, AUTOMATIC ) TargetEventCtrlIndexPtr,
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndexCheckRemainCount,
    P2VAR( Dem_u08_EventCtrlBitmapType, AUTOMATIC, AUTOMATIC ) PassedBitmapDataPtr
);

#endif  /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON ) */

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
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Event_InitQualification_AfterRecordCheckComplete     */
/* Description   | load Dem_EventQualificationList[] from record.           */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Event_InitQualification_AfterRecordCheckComplete
( void )
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexNum;

    eventStorageNum     =   Dem_PrimaryMemEventStorageNum;

    /*--------------------------------------------------------------*/
    /*  set all EventRecord.                                        */
    /*--------------------------------------------------------------*/
    for ( eventStrgIndex = ( Dem_u16_EventStrgIndexType )0U; eventStrgIndex < eventStorageNum; eventStrgIndex++ )   /* [GUD:for]eventStrgIndex */
    {
        eventCtrlIndexNum           =   Dem_CmbEvt_NumOfEventCtrlIndex_InEvtStrgGrp( eventStrgIndex );              /* [GUD]eventStrgIndex *//*  get number of eventCtrlIndex */
        if ( eventCtrlIndexNum > (Dem_u16_EventCtrlIndexType)1U )
        {
            Dem_Event_LoadPassedBit_InEvtStrgGrp( eventStrgIndex );                                                 /* [GUD]eventStrgIndex */
        }
    }
    return ;
}

/****************************************************************************/
/* Function Name | Dem_Event_LoadPassedBit_InEvtStrgGrp                     */
/* Description   | load Dem_EventQualificationList[] from record.           */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Event_LoadPassedBit_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex     /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexRemainCnt;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexExecCnt;
    VAR( Dem_u08_EventCtrlBitmapIndexType, AUTOMATIC ) eventCtrlBitmapIndex;
    VAR( Dem_u08_EventCtrlBitmapType, AUTOMATIC ) passedBitmap;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetPassedBitmap;

    /*----------------------------------------------------------------------------------*/
    /*  start of eventCtrlIndex.(delegate eventCtrlIndex.)                              */
    /*----------------------------------------------------------------------------------*/
    eventCtrlIndex              =   Dem_CmbEvt_GetDelegateEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );    /* [GUDCHK:CALLER]EventStrgIndex *//*  get delegate EventCtrlIndex( = start position of bitmap.)   *//* [GUD:RET:IF_GUARDED:eventStrgIndex]eventCtrlIndex */
    eventCtrlIndexRemainCnt     =   Dem_CmbEvt_NumOfEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );          /* [GUDCHK:CALLER]EventStrgIndex *//*  ret remain number of eventCtrlIndex.                        */
    eventCtrlBitmapIndex        =   (Dem_u08_EventCtrlBitmapIndexType)0U;   /*  index of Dem_EventRecordList[].PassedBitmapInEvtStrgGrp[].  */

    /*------------------------------------------*/
    /*  initialize one eventRecord.             */
    /*------------------------------------------*/
    while ( eventCtrlIndexRemainCnt > (Dem_u16_EventCtrlIndexType)0U )
    {
        /*  get passedBitmap data from event record.                        */
        passedBitmap        =   DEM_EVENTCTRLBITMAP_ALL_OFF;
        retGetPassedBitmap  =   Dem_DataMngC_GetER_PassedBitmap_InEvtStrgGrp( EventStrgIndex, eventCtrlBitmapIndex, &passedBitmap );    /* [GUD:RET:DEM_IRT_OK]EventStrgIndex *//* [GUD:RET:DEM_IRT_OK]eventCtrlBitmapIndex */

        if ( retGetPassedBitmap != DEM_IRT_OK )
        {
            eventCtrlIndexRemainCnt =   (Dem_u16_EventCtrlIndexType)0U;     /*  illegal path : no execute next jobs.    */
        }
        else
        {
            /*  check remain eventCtrlIndex count.                          */
            eventCtrlIndexExecCnt   =   Dem_Event_LoadPassedBitmap_ToQualification( &eventCtrlIndex, eventCtrlIndexRemainCnt, passedBitmap );   /* [GUD]eventCtrlIndex */

            if ( eventCtrlIndexRemainCnt > eventCtrlIndexExecCnt )
            {
                eventCtrlIndexRemainCnt =   eventCtrlIndexRemainCnt - eventCtrlIndexExecCnt;        /*  no wrap around.         */
            }
            else
            {
                eventCtrlIndexRemainCnt =   (Dem_u16_EventCtrlIndexType)0U;
            }
            /*  get next BitMapBuffer offset value.                     */
            eventCtrlBitmapIndex   =   eventCtrlBitmapIndex + (Dem_u08_EventCtrlBitmapIndexType)1U; /*  no wrap around.         */
        }
    }
    return ;
}

/****************************************************************************/
/* Function Name | Dem_Event_LoadPassedBitmap_ToQualification               */
/* Description   | load Dem_EventQualificationList[] from record.           */
/* Preconditions |                                                          */
/* Parameters    | [in/out] TargetEventCtrlIndexPtr                         */
/*               |           in  : start of event index in EventStrgGrp.    */
/*               |           out : next  of event index in EventStrgGrp.    */
/*               | [in] EventCtrlIndexCheckRemainCount                      */
/*               |           remain event index in EventStrgGrp.            */
/*               | [in] PassedBitmapData                                    */
/* Return Value  | Dem_u16_EventCtrlIndexType :                             */
/*               |              execute eventCtrlIndex number.              */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
static FUNC( Dem_u16_EventCtrlIndexType, DEM_CODE ) Dem_Event_LoadPassedBitmap_ToQualification
(
    P2VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC, AUTOMATIC ) TargetEventCtrlIndexPtr,
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndexCheckRemainCount,
    VAR( Dem_u08_EventCtrlBitmapType, AUTOMATIC ) PassedBitmapData
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u08_EventCtrlBitmapWidthType, AUTOMATIC ) eventCtrlBitOffsetMax;
    VAR( Dem_u08_EventCtrlBitmapWidthType, AUTOMATIC ) eventCtrlBitOffset;
    VAR( Dem_u08_EventCtrlBitmapType, AUTOMATIC ) passedBitmapMask;
    VAR( Dem_u08_EventQualificationType, AUTOMATIC ) qualification;

    /*----------------------------------------------------------*/
    /*  get number of check bit in bitmap.                      */
    /*----------------------------------------------------------*/
    if ( EventCtrlIndexCheckRemainCount >= DEM_EVENTCTRLBITMAP_BITWIDTH )
    {
        eventCtrlBitOffsetMax   =   DEM_EVENTCTRLBITMAP_BITWIDTH;   /*  check max of bit width.                 */
    }
    else
    {
        eventCtrlBitOffsetMax   =   (Dem_u08_EventCtrlBitmapWidthType)EventCtrlIndexCheckRemainCount;        /*  check remain number of eventCtrlIndex.  */
    }

    /*----------------------------------------------------------*/
    /*  check bitmap data.                                      */
    /*      bit ON  :  DEM_EVENT_QUALIFICATION_PASSED           */
    /*      bit OFF :  DEM_EVENT_QUALIFICATION_NOTQUALIFIED     */
    /*----------------------------------------------------------*/
    eventCtrlIndex  =   *TargetEventCtrlIndexPtr;

    for ( eventCtrlBitOffset = (Dem_u08_EventCtrlBitmapWidthType)0U; eventCtrlBitOffset < eventCtrlBitOffsetMax; eventCtrlBitOffset++ )
    {
        /*  get bitmap mask value.                          */
        passedBitmapMask   =   ( Dem_u08_EventCtrlBitmapWidthType )1U << eventCtrlBitOffset;

        if (( PassedBitmapData & passedBitmapMask ) != DEM_EVENTCTRLBITMAP_ALL_OFF )
        {
            /*  bit ON : set DEM_EVENT_QUALIFICATION_PASSED.        */
            qualification    =   DEM_EVENT_QUALIFICATION_PASSED;
        }
        else
        {
            /*  bit OFF: set DEM_EVENT_QUALIFICATION_NOTQUALIFIED   */
            qualification    =   DEM_EVENT_QUALIFICATION_NOTQUALIFIED;
        }

        /*  set qualification to Dem_EventQualificationList[].      */
        Dem_EventQualificationList[ eventCtrlIndex ]        =   qualification;                          /* [GUDCHK:CALLER]*TargetEventCtrlIndexPtr */

        /*  next eventCtrlIndex in event record.                    */
        eventCtrlIndex          =   Dem_CmbEvt_GetNextEventCtrlIndex_InEvtStrgGrp( eventCtrlIndex );
    }

    *TargetEventCtrlIndexPtr    =   eventCtrlIndex;

    return (Dem_u16_EventCtrlIndexType)eventCtrlBitOffsetMax;
}

/****************************************************************************/
/* Function Name | Dem_Event_ClearPassedBit_InStrgGrp                       */
/* Description   | clear PassedBit in EventStrgIndex.                       */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Event_ClearPassedBit_InStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex     /* [PRMCHK:CALLER] */
)
{
    Dem_DataMngC_SetER_PassedBitmapAll_InEvtStrgGrp( EventStrgIndex, DEM_EVENTCTRLBITMAP_ALL_OFF );

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Event_SavePassedTgtBit_ByEvtCtrlIdx                  */
/* Description   | set PassedBit by EventCtrlIndex.                         */
/* Preconditions |                                                          */
/* Parameters    | [in] TargetEventCtrlIndex                                */
/*               | [in] PassedBit                                           */
/*               |                  TRUE  : PASSED                          */
/*               |                  FALSE : not PASSED                      */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Event_SavePassedTgtBit_ByEvtCtrlIdx
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) TargetEventCtrlIndex,
    VAR( boolean, AUTOMATIC ) PassedBit
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventConfigureNum;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexNum;
    VAR( Dem_u08_EventCtrlBitmapIndexType, AUTOMATIC ) eventCtrlBitmapIndex;
    VAR( Dem_u08_EventCtrlBitmapWidthType, AUTOMATIC ) eventCtrlBitOffset;
    VAR( Dem_u08_EventCtrlBitmapType, AUTOMATIC ) passedBitmap;
    VAR( Dem_u08_EventCtrlBitmapType, AUTOMATIC ) passedBitmapMask;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetPassedBitmap;

    eventConfigureNum   =   Dem_PrimaryMemEventConfigureNum;

    if( TargetEventCtrlIndex < eventConfigureNum )                                /* [GUD:if]TargetEventCtrlIndex */
    {
        eventStrgIndex      =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( TargetEventCtrlIndex );  /*  get eventStrgIndex                  */

        /*----------------------------------------------------------------------------------*/
        /*  check EventCtrlIndex number in EvtStrgGrp.                                      */
        /*----------------------------------------------------------------------------------*/
        eventCtrlIndexNum       =   Dem_CmbEvt_NumOfEventCtrlIndex_InEvtStrgGrp( eventStrgIndex );          /*  get number of eventCtrlIndex        */

        if ( eventCtrlIndexNum > (Dem_u16_EventCtrlIndexType)1U )
        {
            eventCtrlBitmapIndex    = (Dem_u08_EventCtrlBitmapIndexType)0U;     /*  index position  */
            eventCtrlBitOffset      = (Dem_u08_EventCtrlBitmapWidthType)0U;     /*  bit position    */

            /*----------------------------------------------------------------------------------*/
            /*  set bitmap index of TargetEventCtrlIndex.                                       */
            /*----------------------------------------------------------------------------------*/
            Dem_Event_SearchEventCtrlBitmapIndex( eventStrgIndex, TargetEventCtrlIndex, &eventCtrlBitmapIndex, &eventCtrlBitOffset );

            /*----------------------------------------------------------------------------------*/
            /*  set bitmap data of TargetEventCtrlIndex.                                        */
            /*----------------------------------------------------------------------------------*/
            /*  get current bitmap data.        */
            passedBitmap        =   DEM_EVENTCTRLBITMAP_ALL_OFF;
            retGetPassedBitmap  =   Dem_DataMngC_GetER_PassedBitmap_InEvtStrgGrp( eventStrgIndex, eventCtrlBitmapIndex, &passedBitmap );

            if ( retGetPassedBitmap == DEM_IRT_OK )
            {
                passedBitmapMask    =   ( Dem_u08_EventCtrlBitmapWidthType )1U << eventCtrlBitOffset;   /*  bit mask     */
                if ( PassedBit == (boolean)TRUE )
                {
                    /*  bit ON      */
                    passedBitmap    =   passedBitmap | passedBitmapMask;
                }
                else
                {
                    /*  bit OFF     */
                    passedBitmap    =   passedBitmap & ~passedBitmapMask;
                }
                /*  set bitmap data.                */
                Dem_DataMngC_SetER_PassedBitmap_InEvtStrgGrp( eventStrgIndex, eventCtrlBitmapIndex, passedBitmap );
            }
        }
    }
    return ;
}

/****************************************************************************/
/* Function Name | Dem_Event_SearchEventCtrlBitmapIndex                     */
/* Description   | search EventCtrlBitmap position.                         */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               | [in] TargetEventCtrlIndex                                */
/*               | [out] EventCtrlBitmapIndexPtr                            */
/*               | [out] EventCtrlBitOffsetPtr                              */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Event_SearchEventCtrlBitmapIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) TargetEventCtrlIndex,
    P2VAR( Dem_u08_EventCtrlBitmapIndexType, AUTOMATIC, AUTOMATIC ) EventCtrlBitmapIndexPtr,
    P2VAR( Dem_u08_EventCtrlBitmapWidthType, AUTOMATIC, AUTOMATIC ) EventCtrlBitOffsetPtr
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexCnt;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexNum;
    VAR( Dem_u08_EventCtrlBitmapIndexType, AUTOMATIC ) eventCtrlBitmapIndex;
    VAR( Dem_u08_EventCtrlBitmapWidthType, AUTOMATIC ) eventCtrlBitOffset;

    /*----------------------------------------------------------------------------------*/
    /*  get [ eventCtrlBitmapIndex and eventCtrlBitOffset ] of TargetEventCtrlIndex.    */
    /*----------------------------------------------------------------------------------*/
    eventCtrlIndex          =   Dem_CmbEvt_GetDelegateEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );    /*  get delegate eventCtrlIndex         *//* [GUDCHK:CALLER]EventStrgIndex */
    eventCtrlIndexNum       =   Dem_CmbEvt_NumOfEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );          /*  get number of eventCtrlIndex        *//* [GUDCHK:CALLER]EventStrgIndex */
    eventCtrlBitmapIndex    =   (Dem_u08_EventCtrlBitmapIndexType)0U;     /*  index position  */
    eventCtrlBitOffset      =   (Dem_u08_EventCtrlBitmapWidthType)0U;     /*  bit position    */

    for ( eventCtrlIndexCnt = ( Dem_u16_EventCtrlIndexType )0U; eventCtrlIndexCnt < eventCtrlIndexNum; eventCtrlIndexCnt++ )
    {
        /*  check target TargetEventCtrlIndex         */
        if ( TargetEventCtrlIndex == eventCtrlIndex )
        {
            /*  find it. get bit position & index position.     */
            break;
        }
        /*  next bit position       */
        eventCtrlBitOffset =   eventCtrlBitOffset + (Dem_u08_EventCtrlBitmapWidthType)1U;           /*  no wrap around.         */

        /*  check bit width         */
        if ( eventCtrlBitOffset >= DEM_EVENTCTRLBITMAP_BITWIDTH )
        {
            /*  next index & reset bit position.        */
            eventCtrlBitOffset     =   (Dem_u08_EventCtrlBitmapWidthType)0U;
            eventCtrlBitmapIndex   =   eventCtrlBitmapIndex + (Dem_u08_EventCtrlBitmapIndexType)1U; /*  no wrap around.         */
        }
        eventCtrlIndex      =   Dem_CmbEvt_GetNextEventCtrlIndex_InEvtStrgGrp( eventCtrlIndex );
    }
    *EventCtrlBitmapIndexPtr    =   eventCtrlBitmapIndex;
    *EventCtrlBitOffsetPtr      =   eventCtrlBitOffset;

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Event_SavePassedAllBit_fromQualification             */
/* Description   | set PassedBit by EventCtrlIndex.                         */
/* Preconditions |                                                          */
/* Parameters    | [in] TargetEventCtrlIndex                                */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Event_SavePassedAllBit_fromQualification
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) TargetEventCtrlIndex
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventConfigureNum;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexRemainCnt;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexExecCnt;
    VAR( Dem_u08_EventCtrlBitmapIndexType, AUTOMATIC ) eventCtrlBitmapIndex;
    VAR( Dem_u08_EventCtrlBitmapType, AUTOMATIC ) passedBitmap;

    eventConfigureNum   =   Dem_PrimaryMemEventConfigureNum;

    if( TargetEventCtrlIndex < eventConfigureNum )                                /* [GUD:if]TargetEventCtrlIndex */
    {
        eventStrgIndex              =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( TargetEventCtrlIndex );  /*  get eventStrgIndex                  *//* [GUD]TargetEventCtrlIndex *//* [GUD:RET:IF_GUARDED:TargetEventCtrlIndex]eventStrgIndex */

        /*----------------------------------------------------------------------------------*/
        /*  start of eventCtrlIndex.(delegate eventCtrlIndex.)                              */
        /*----------------------------------------------------------------------------------*/
        eventCtrlIndex              =   Dem_CmbEvt_GetDelegateEventCtrlIndex_InEvtStrgGrp( eventStrgIndex );    /*  get delegate eventCtrlIndex         *//* [GUD]eventStrgIndex *//* [GUD:RET:IF_GUARDED:eventStrgIndex]eventCtrlIndex */
        eventCtrlIndexRemainCnt     =   Dem_CmbEvt_NumOfEventCtrlIndex_InEvtStrgGrp( eventStrgIndex );          /*  get number of eventCtrlIndex        *//* [GUD]eventStrgIndex */
        eventCtrlBitmapIndex        =   (Dem_u08_EventCtrlBitmapIndexType)0U;   /*  index of Dem_EventRecordList[].PassedBitmapInEvtStrgGrp[].  */

        if ( eventCtrlIndexRemainCnt > (Dem_u16_EventCtrlIndexType)1U )
        {
            while ( eventCtrlIndexRemainCnt > (Dem_u16_EventCtrlIndexType)0U )
            {
                /*----------------------------------*/
                /*  make bitmap data.               */
                /*----------------------------------*/
                passedBitmap            =   DEM_EVENTCTRLBITMAP_ALL_OFF;
                eventCtrlIndexExecCnt   =   Dem_Event_MakePassedBitmap_fromQualification( &eventCtrlIndex, eventCtrlIndexRemainCnt, &passedBitmap );    /* [GUD]eventCtrlIndex */

                if ( eventCtrlIndexRemainCnt > eventCtrlIndexExecCnt )
                {
                    eventCtrlIndexRemainCnt =   eventCtrlIndexRemainCnt - eventCtrlIndexExecCnt;    /*  no wrap around.         */
                }
                else
                {
                    eventCtrlIndexRemainCnt =   (Dem_u16_EventCtrlIndexType)0U;
                }
                /*----------------------------------*/
                /*  set bitmap data.(full bit.)     */
                /*----------------------------------*/
                Dem_DataMngC_SetER_PassedBitmap_InEvtStrgGrp( eventStrgIndex, eventCtrlBitmapIndex, passedBitmap );

                /*  get next BitMapBuffer offset value.                     */
                eventCtrlBitmapIndex    =   eventCtrlBitmapIndex + (Dem_u08_EventCtrlBitmapIndexType)1U;    /*  no wrap around.         */
            }
        }
    }
    return ;
}

/****************************************************************************/
/* Function Name | Dem_Event_MakePassedBitmap_fromQualification             */
/* Description   | set PassedBit by EventCtrlIndex.                         */
/* Preconditions |                                                          */
/* Parameters    | [in/out] TargetEventCtrlIndexPtr                         */
/*               |           in  : start of event index in EventStrgGrp.    */
/*               |           out : next  of event index in EventStrgGrp.    */
/*               | [in] EventCtrlIndexCheckRemainCount                      */
/*               |           remain event index in EventStrgGrp.            */
/*               | [out] PassedBitmapDataPtr                                */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
static FUNC( Dem_u16_EventCtrlIndexType, DEM_CODE ) Dem_Event_MakePassedBitmap_fromQualification
(
    P2VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC, AUTOMATIC ) TargetEventCtrlIndexPtr,
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndexCheckRemainCount,
    P2VAR( Dem_u08_EventCtrlBitmapType, AUTOMATIC, AUTOMATIC ) PassedBitmapDataPtr
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u08_EventCtrlBitmapWidthType, AUTOMATIC ) eventCtrlBitOffsetMax;
    VAR( Dem_u08_EventCtrlBitmapWidthType, AUTOMATIC ) eventCtrlBitOffset;
    VAR( Dem_u08_EventCtrlBitmapType, AUTOMATIC ) passedBitmap;
    VAR( Dem_u08_EventCtrlBitmapType, AUTOMATIC ) passedBitmapMask;
    VAR( Dem_u08_EventQualificationType, AUTOMATIC ) qualification;

    if ( EventCtrlIndexCheckRemainCount >= DEM_EVENTCTRLBITMAP_BITWIDTH )
    {
        eventCtrlBitOffsetMax   =   DEM_EVENTCTRLBITMAP_BITWIDTH;   /*  check max of bit width.                 */
    }
    else
    {
        eventCtrlBitOffsetMax   =   (Dem_u08_EventCtrlBitmapWidthType)EventCtrlIndexCheckRemainCount;        /*  check remain number of eventCtrlIndex.  */
    }

    /*----------------------------------------------------------*/
    /*  check bitmap data.                                      */
    /*      bit ON  :  DEM_EVENT_QUALIFICATION_PASSED           */
    /*      bit OFF :  DEM_EVENT_QUALIFICATION_NOTQUALIFIED     */
    /*----------------------------------------------------------*/
    eventCtrlIndex          =   *TargetEventCtrlIndexPtr;
    passedBitmap            =   DEM_EVENTCTRLBITMAP_ALL_OFF;

    for ( eventCtrlBitOffset = (Dem_u08_EventCtrlBitmapWidthType)0U; eventCtrlBitOffset < eventCtrlBitOffsetMax; eventCtrlBitOffset++ )
    {
        /*  get qualification.  */
        qualification       =   Dem_EventQualificationList[ eventCtrlIndex ];                           /* [GUDCHK:CALLER]*TargetEventCtrlIndexPtr */

        passedBitmapMask    =   ( Dem_u08_EventCtrlBitmapWidthType )1U << eventCtrlBitOffset;
        if ( qualification == DEM_EVENT_QUALIFICATION_PASSED )
        {
            /*  bit ON          */
            passedBitmap    =   passedBitmap | passedBitmapMask;
        }
        else
        {
            /*  bit OFF         */
        }
        /*  next eventCtrlIndex in event record.                    */
        eventCtrlIndex          =   Dem_CmbEvt_GetNextEventCtrlIndex_InEvtStrgGrp( eventCtrlIndex );
    }
    *TargetEventCtrlIndexPtr    =   eventCtrlIndex;
    *PassedBitmapDataPtr        =   passedBitmap;

    return (Dem_u16_EventCtrlIndexType)eventCtrlBitOffsetMax;

}

#endif  /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )     */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
