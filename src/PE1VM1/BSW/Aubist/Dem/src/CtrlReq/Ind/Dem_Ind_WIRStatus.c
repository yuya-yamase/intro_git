/* Dem_Ind_WIRStatus_c(v5-9-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Ind_cmn/CODE                                          */
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
#include "../../../inc/Dem_CmnLib_Control.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_Ind.h"

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

static FUNC( void, DEM_CODE ) Dem_Ind_SetWIRStatusData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( boolean, AUTOMATIC ) WIRStatus
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_u08_WIRStatusType, DEM_VAR_NO_INIT ) Dem_WIRStatus[ DEM_PRIMEM_EVENTSTORAGE_NUM ];


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions(PreInit section)                                      */
/****************************************************************************/
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Ind_PreInit_WIRStatus                                */
/* Description   | Initialize of Dem_Ind information.                       */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE_TRUST ) Dem_Ind_PreInit_WIRStatus              /*  PreInit section     */
( void )
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) loopCount;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    for( loopCount = (Dem_u16_EventStrgIndexType)0U ; loopCount < eventStorageNum ; loopCount++ )   /* [GUD:for]loopCount */
    {
        Dem_WIRStatus[loopCount] = DEM_WIRSTATUS_OFF;   /* [GUD]loopCount */
    }
    return;
}

#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Ind_SetWIRStatus                                     */
/* Description   | Set WIRStatus by Event index.                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Event index.                                      */
/*               | [in] WIRStatus :                                         */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Success.                             */
/*               |        DEM_IRT_NG : Failed.                              */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Ind_SetWIRStatus
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,        /* [PRMCHK:CALLER] */
    VAR( boolean, AUTOMATIC ) WIRStatus
)
{
    Dem_Ind_SetWIRStatusData( EventStrgIndex, WIRStatus );      /* [GUDCHK:CALLER]EventStrgIndex */

    return DEM_IRT_OK;
}


/****************************************************************************/
/* Function Name | Dem_Ind_ClearWIRStatus                                   */
/* Description   | Clear WIRStatuis by Event Index.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Event index.                                      */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Ind_ClearWIRStatus
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex     /* [PRMCHK:CALLER] */
)
{
    Dem_Ind_SetWIRStatusData( EventStrgIndex, (boolean)FALSE );     /* [GUDCHK:CALLER]EventStrgIndex */

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Ind_SetWIRStatusData                                 */
/* Description   | Set WIRStatus by Event index.                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Event index.                                      */
/*               | [in] WIRStatus :                                         */
/*               |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Ind_SetWIRStatusData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,        /* [PRMCHK:CALLER] */
    VAR( boolean, AUTOMATIC ) WIRStatus
)
{
    SchM_Enter_Dem_WIRStatusAccess();

    /* manage WIRStatus by uint8 not boolean for countermeasure of RAM garbled */
    if( WIRStatus == (boolean)TRUE )
    {
        Dem_WIRStatus[EventStrgIndex] = DEM_WIRSTATUS_ON;       /* [GUDCHK:CALLER]EventStrgIndex */
    }
    else
    {
        Dem_WIRStatus[EventStrgIndex] = DEM_WIRSTATUS_OFF;      /* [GUDCHK:CALLER]EventStrgIndex */
    }

    SchM_Exit_Dem_WIRStatusAccess();
    return ;
}

/****************************************************************************/
/* Function Name | Dem_Ind_GetWIRStatus                                     */
/* Description   | Get WIRStatus by Event index.                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Event index.                                      */
/*               | [out] WIRStatusPtr :                                     */
/*               |        Pointer to data for set WIRStatus.                */
/*               |          TRUE   : WIRStatus TRUE                         */
/*               |          FALSE  : WIRStatus FALSE                        */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Success.                             */
/*               |        DEM_IRT_NG : Failed.                              */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Ind_GetWIRStatus
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) WIRStatusPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]EventStrgIndex */
    {
        SchM_Enter_Dem_WIRStatusAccess();

        if( Dem_WIRStatus[EventStrgIndex] != DEM_WIRSTATUS_OFF )    /* [GUD]EventStrgIndex */
        {
            *WIRStatusPtr = (boolean)TRUE;
        }
        else
        {
            *WIRStatusPtr = (boolean)FALSE;
        }

        SchM_Exit_Dem_WIRStatusAccess();

        retVal = DEM_IRT_OK;
    }
    else
    {
        /* No process */
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Ind_GetWIRStatusByDTC                                */
/* Description   | Get WIRStatus by Event index on DTC.                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Event index.                                      */
/*               | [out] WIRStatusPtr :                                     */
/*               |        Pointer to data for set WIRStatus.                */
/*               |          TRUE   : WIRStatus TRUE                         */
/*               |          FALSE  : WIRStatus FALSE                        */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Success.                             */
/*               |        DEM_IRT_NG : Failed.                              */
/* Notes         | at CombinedEvent OnRetrieval is ON ,EventStrgIndex is delegate of DTC. */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_Ind_GetWIRStatus().            */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Ind_GetWIRStatusByDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) WIRStatusPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON ) /*  [FuncSw]    */
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexCnt;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexTarget;
#endif  /* ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )  */
    VAR( boolean, AUTOMATIC ) wirStatus;

    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal      =   DEM_IRT_NG;
    wirStatus   =   (boolean)FALSE;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )                      /* [GUD:if]EventStrgIndex */
    {
#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON ) /*  [FuncSw]    */
        /* get num of event index in DTC group. */
        eventStrgIndexNum = Dem_CmbEvt_NumOfEventStrgIndex_InDTCGrp( EventStrgIndex );

        if( eventStrgIndexNum > ( Dem_u16_EventStrgIndexType )1U )
        {
            eventStrgIndexTarget    =   EventStrgIndex;         /*[GUD]EventStrgIndex   *//*[GUD]eventStrgIndexTarget   */

            /*  this function is called at Dcm context, but no need call SchM_Enter_Dem_WIRStatusAccess()/SchM_Exit_Dem_WIRStatusAccess().  */

            /*  on retrieval.       */
            for( eventStrgIndexCnt = ( Dem_u16_EventStrgIndexType )0U; eventStrgIndexCnt < eventStrgIndexNum; eventStrgIndexCnt++ )
            {
                if ( Dem_WIRStatus[eventStrgIndexTarget] != DEM_WIRSTATUS_OFF )         /*[GUD]eventStrgIndexTarget */
                {
                    wirStatus   =   (boolean)TRUE;
                    break;
                }
                /* get next event index. */
                eventStrgIndexTarget = Dem_CmbEvt_GetNextEventStrgIndex_InDTCGrp( eventStrgIndexTarget );   /* [GUD:RET:IF_GUARDED eventStrgIndexTarget ]eventStrgIndexTarget */
            }
        }
        else
#endif  /* ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )  */
        {
            /*  this function is called at Dcm context, but no need call SchM_Enter_Dem_WIRStatusAccess()/SchM_Exit_Dem_WIRStatusAccess().  */

            if( Dem_WIRStatus[EventStrgIndex] != DEM_WIRSTATUS_OFF )    /* [GUD]EventStrgIndex */
            {
                wirStatus   =   (boolean)TRUE;
            }

        }
        retVal = DEM_IRT_OK;
    }
    *WIRStatusPtr = wirStatus;

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Ind_GetWIRStatus                                     */
/* Description   | Get WIR Status                                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Event index.                                      */
/* Parameters    | [out] IndicatorStatusPtr                                 */
/*               |          DEM_INDICATOR_OFF        : Indicator Off        */
/*               |          DEM_INDICATOR_CONTINUOUS : Indicator On         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Success.                             */
/*               |        DEM_IRT_NG : Failed.                              */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_IndicatorStatusType, DEM_CODE ) Dem_Ind_GetIndicatorStatusByWIRStatusAndEventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_WIRStatusType, AUTOMATIC ) wirStatus;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_IndicatorStatusType, AUTOMATIC ) indicatorStatus;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    retVal  =   DEM_IRT_NG;
    indicatorStatus = DEM_INDICATOR_OFF;
    if ( EventStrgIndex < eventStorageNum )                                                                 /* [GUD:if]EventStrgIndex */
    {
        wirStatus   =   Dem_WIRStatus[ EventStrgIndex ];        /* [GUD]EventStrgIndex */
        if ( wirStatus == DEM_WIRSTATUS_ON )
        {
            indicatorStatus = DEM_INDICATOR_CONTINUOUS;
        }
        retVal  =   DEM_IRT_OK;
    }
    *IndicatorStatusPtr =   indicatorStatus;

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Ind_GetIndicatorByWIRStatus                          */
/* Description   | Get Indicator Status by Indicator Id.                    */
/* Preconditions | none                                                     */
/* Parameters    |                                                          */
/* Return Value  | Dem_IndicatorStatusType                                  */
/*               |          DEM_INDICATOR_OFF        : Indicator Off        */
/*               |          DEM_INDICATOR_CONTINUOUS : Indicator On         */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-9-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_IndicatorStatusType, DEM_CODE ) Dem_Ind_GetIndicatorStatusByWIRStatus
( void )
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) loopCount;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_IndicatorStatusType, AUTOMATIC ) indicatorStatus;
    VAR( boolean, AUTOMATIC ) availableStatus;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    indicatorStatus = DEM_INDICATOR_OFF;

    for( loopCount = (Dem_u16_EventStrgIndexType)0U ; loopCount < eventStorageNum ; loopCount++ )   /* [GUD:for]loopCount */
    {
        availableStatus =   Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( loopCount );

        if ( availableStatus == (boolean)TRUE )
        {
            SchM_Enter_Dem_WIRStatusAccess();

            if( Dem_WIRStatus[loopCount] != DEM_WIRSTATUS_OFF )         /* [GUD]loopCount */
            {
                indicatorStatus = DEM_INDICATOR_CONTINUOUS;
            }
            else
            {
                /* No process */
            }

            SchM_Exit_Dem_WIRStatusAccess();

            if( indicatorStatus == DEM_INDICATOR_CONTINUOUS )
            {
                break;
            }
        }
    }

    return indicatorStatus;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
