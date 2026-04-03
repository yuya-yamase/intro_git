/* Dem_DTC_FilDTC_ReadinessGrp_c(v5-10-0)                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DTC_FilDTC_ReadinessGrp/CODE                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
#include "../../../../cfg/Dem_Cfg.h"
#include "../../../../cfg/Dem_Readiness_Cfg.h"
#include "../../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../../inc/Dem_Pm_DataAvl.h"
#include "../../../../inc/Dem_Pm_DTC.h"
#include "../../../../inc/Dem_Pm_Misfire.h"
#include "../../../../usr/Dem_Readiness_Callout.h"

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

static FUNC( boolean, DEM_CODE ) Dem_DTC_GetDTCAvailableInReadinessGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u08_ReadinessGroupIdType, AUTOMATIC ) TargetReadinessGroupId
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_u16_FilReadinessGroupSearchNumType, DEM_VAR_NO_INIT )  Dem_EventSearchCntForReadiness;
static VAR( Dem_u08_ReadinessGroupIdType, DEM_VAR_NO_INIT )  Dem_ReadinessGroupIdForFilter;
static VAR( Dem_u08_ReadinessGroupIndexType, DEM_VAR_NO_INIT )  Dem_ReadinessGroupIndexForFilter;
static VAR( Dem_u16_EventCtrlIndexType, DEM_VAR_NO_INIT )  Dem_ReadinessGroupEvtListIdx;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_DTC_SetDTCFilterForReadiness                         */
/* Description   | Set filter of ReadinessGroup.                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] ReadinessGroupId :                                  */
/*               |        Defines the Readiness group for DTC filter        */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Filter was accepted                  */
/*               |        DEM_IRT_NG : Wrong filter selected                */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-8-0      | no branch changed.                                       */
/*   v5-9-0      | no object changed.                                       */
/*   v5-10-0     | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_SetDTCFilterForReadiness
(
    VAR( Dem_u08_ReadinessGroupIdType, AUTOMATIC ) ReadinessGroupId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC ) readinessGroupIndex;
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC ) readinessGroupNum;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventNum;
#if ( DEM_READINESSSUPPORT_BY_CALLOUT_SUPPORT == STD_ON )   /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) supported;
#endif  /* ( DEM_READINESSSUPPORT_BY_CALLOUT_SUPPORT == STD_ON )            */

    retVal= DEM_IRT_NG;

#if ( DEM_READINESSSUPPORT_BY_CALLOUT_SUPPORT == STD_ON )   /*  [FuncSw]    */
    supported   =   Dem_JudgeReadinessGroupIdSupported( ReadinessGroupId );
    if ( supported == (boolean)FALSE )
    {
        /*  not support. retVal : DEM_IRT_NG.       */
    }
    else
#endif  /* ( DEM_READINESSSUPPORT_BY_CALLOUT_SUPPORT == STD_ON )            */
    {
        /*  reset of search index.                  */
        Dem_DTC_RestartSetDTCFilterForReadiness();

        /*  check readiness group id.               */
        readinessGroupIndex =   Dem_CfgInfoPm_CnvReadinessGroupIdToGroupIndex( ReadinessGroupId );
        readinessGroupNum   =   Dem_ReadinessGroupNum;
        if( readinessGroupIndex < readinessGroupNum )
        {
            eventNum = Dem_CfgInfoPm_GetEventNumberOfReadinessGroup( DEM_READINESSDATAPOSITIONINDEX_INVALID, readinessGroupIndex );
            if( eventNum > ( Dem_u16_EventCtrlIndexType )0U )
            {
                /*  accept filter.                  */
                Dem_ReadinessGroupIdForFilter    = ReadinessGroupId;
                Dem_ReadinessGroupIndexForFilter = readinessGroupIndex;
                retVal = DEM_IRT_OK;
            }
        }
    }
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DTC_RestartSetDTCFilterForReadiness                  */
/* Description   | The function set the DTC filter.(re-start)               */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-8-0      | new created. based on Dem_DTC_RestartSetDTCFilter()      */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_RestartSetDTCFilterForReadiness
( void )
{
    Dem_ReadinessGroupEvtListIdx = ( Dem_u16_EventCtrlIndexType )0U;
    Dem_EventSearchCntForReadiness = (Dem_u16_FilReadinessGroupSearchNumType)0U;

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    /* misfire filtering for SID19-56 */
    Dem_Misfire_SetFilteredDTCForCylinderForReadiness();
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

    return ;
}


/****************************************************************************/
/* Function Name | Dem_DTC_GetNextFilteredDTCForReadiness                   */
/* Description   | Gets the next filtered DTC and its DTC status.           */
/* Preconditions | Dem_DTC_SetDTCFilterForReadiness being executed.         */
/* Parameters    | [out] DTCValuePtr :                                      */
/*               |        Receives the DTC value in respective format of t- */
/*               |        he filter returned by this function               */
/*               | [out] DTCStatusPtr :                                     */
/*               |        receives the status information of the requested  */
/*               |        DTC                                               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Returned next filtered element       */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No further element  */
/*               |         (matching the filter criteria) found             */
/*               |        DEM_IRT_PENDING : The requested value is calcula- */
/*               |        ting.                                             */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-8-0      | branch changed.                                          */
/*   v5-9-0      | no object changed.                                       */
/*   v5-10-0     | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetNextFilteredDTCForReadiness
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_ReadinessGroupIdType, AUTOMATIC ) readinessGroupId;
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC ) readinessGroupIndex;
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC ) readinessGroupNum;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventListIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) nextEventListIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventNum;
    VAR( Dem_u16_FilReadinessGroupSearchNumType, AUTOMATIC ) searchLoopNumByCycle;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) retChkEventAvailable;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventConfigureNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retChkDtc;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( boolean, AUTOMATIC ) eventOBDKind;
    VAR( boolean, AUTOMATIC ) loopEndFlag;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retChkCylDtc;
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

    retVal = DEM_IRT_NO_MATCHING_ELEMENT;
    readinessGroupId    = Dem_ReadinessGroupIdForFilter;
    readinessGroupIndex = Dem_ReadinessGroupIndexForFilter;
    readinessGroupNum   = Dem_ReadinessGroupNum;
    nextEventListIndex  = Dem_ReadinessGroupEvtListIdx;

    if( readinessGroupIndex < readinessGroupNum )
    {
        searchLoopNumByCycle = Dem_FilReadinessGroupSearchLoopNumByCycle;
        loopEndFlag = (boolean)FALSE;
        eventConfigureNum = Dem_PrimaryMemEventConfigureNum;

        eventNum = Dem_CfgInfoPm_GetEventNumberOfReadinessGroup( DEM_READINESSDATAPOSITIONINDEX_INVALID, readinessGroupIndex );

        for( eventListIndex = nextEventListIndex; eventListIndex < eventNum; eventListIndex++  )
        {
            if( Dem_EventSearchCntForReadiness < searchLoopNumByCycle )
            {
                eventCtrlIndex = Dem_CfgInfoPm_GetEventCtrlIndexOfReadinessGroup( DEM_READINESSDATAPOSITIONINDEX_INVALID, readinessGroupIndex, eventListIndex );
                if ( eventCtrlIndex < eventConfigureNum )                               /* [GUD:if]eventCtrlIndex */
                {
                    eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_ByEvtCtrlIdx( eventCtrlIndex );   /* [GUD]eventCtrlIndex */
                    if( eventOBDKind == (boolean)TRUE ) /*  OBD     */
                    {
                        eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );        /* [GUD]eventCtrlIndex *//* [GUD:RET:IF_GUARDED:eventCtrlIndex]eventStrgIndex */
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                        misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( eventStrgIndex );    /* [GUD]eventStrgIndex */
                        if( misfireEventKind == (boolean)TRUE )
                        {
                            retChkEventAvailable = Dem_DataAvl_GetEvtAvl( eventCtrlIndex );     /* [GUD]eventCtrlIndex */
                            if( retChkEventAvailable == (boolean)TRUE )
                            {
                                retChkCylDtc = Dem_Misfire_GetNextFilterdDTCForCylinder( DTCValuePtr, DTCStatusPtr );
                                if( retChkCylDtc == DEM_IRT_OK )
                                {
                                    loopEndFlag = (boolean)TRUE;
                                    retVal = DEM_IRT_OK;
                                    /*=========================================================*/
                                    /*  No reset of Dem_EventSearchCntForReadiness this timing.*/
                                    /*  next call of this function, only return pending.       */
                                    /*  Dem_EventSearchCntForReadiness is reset at return of pending.*/
                                    /*=========================================================*/
                                }
                            }
                        }
                        else
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
                        {
                            retChkDtc = Dem_DTC_GetDTCStatusAndUdsDTC( eventStrgIndex, DTCValuePtr, DTCStatusPtr ); /* [GUD]eventStrgIndex */
                            if( retChkDtc == DEM_IRT_OK )
                            {
                                retChkEventAvailable = Dem_DTC_GetDTCAvailableInReadinessGrp( eventStrgIndex, eventCtrlIndex, readinessGroupId );     /* [GUD]eventCtrlIndex */
                                if( retChkEventAvailable == (boolean)TRUE )
                                {
                                    Dem_ReadinessGroupEvtListIdx = eventListIndex + ( Dem_u16_EventCtrlIndexType )1U;
                                    retVal = DEM_IRT_OK;
                                    loopEndFlag = (boolean)TRUE;
                                    /*=========================================================*/
                                    /*  No reset of Dem_EventSearchCntForReadiness this timing.*/
                                    /*  next call of this function, only return pending.       */
                                    /*  Dem_EventSearchCntForReadiness is reset at return of pending.*/
                                    /*=========================================================*/
                                }
                            }
                        }
                    }
                }
                Dem_EventSearchCntForReadiness =  Dem_EventSearchCntForReadiness + ( Dem_u16_FilReadinessGroupSearchNumType )1U;
            }
            else
            {
                /* update next search index */
                Dem_ReadinessGroupEvtListIdx = eventListIndex;
                /* reset search counter for return pending */
                Dem_EventSearchCntForReadiness = (Dem_u16_FilReadinessGroupSearchNumType)0U;
                retVal = DEM_IRT_PENDING;
                loopEndFlag = (boolean)TRUE;
            }

            if( loopEndFlag == (boolean)TRUE )
            {
                break;
            }
        }

        if( retVal == DEM_IRT_NO_MATCHING_ELEMENT )
        {
            Dem_ReadinessGroupEvtListIdx = eventNum;
        }
    }

    if( retVal == DEM_IRT_OK )
    {
        /*------------------------------------------*/
        /*  convert to output statusOfDTC.          */
        /*------------------------------------------*/
        (*DTCStatusPtr) =   Dem_DTC_CnvDTCStatus_PmAvailabilityMask( (*DTCStatusPtr) );
    }

    return retVal;
}

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_DTC_GetDTCAvailableInReadinessGrp                    */
/* Description   | Check DTC Available in ReadinessGroup.                   */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex : EventStrgIndex                     */
/*               |      ( index per DTC at CombinedEvent OnStorage. )       */
/*               |                                                          */
/*               | [in] EventCtrlIndex : EventCtrlIndex                     */
/*               |      ( index per Event at CombinedEvent OnStorage. )     */
/*               |                                                          */
/*               | [in] TargetReadinessGroupId :                            */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : DTC in ReadinessGroup is available.       */
/*               |        FALSE : DTC in ReadinessGroup is not available.   */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-10-0     | new created.                                             */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_DTC_GetDTCAvailableInReadinessGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,                /* MISRA DEVIATION */
    VAR( Dem_u08_ReadinessGroupIdType, AUTOMATIC ) TargetReadinessGroupId       /* MISRA DEVIATION */
)
{
    VAR( boolean, AUTOMATIC ) available;

    /*  check DTC available.                                    */
    available   =   Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( EventStrgIndex );

    return available;
}
#endif  /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )    */

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )
#if ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTC_GetDTCAvailableInReadinessGrp                    */
/* Description   | Check DTC Available in ReadinessGroup.                   */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex : EventStrgIndex                     */
/*               |      ( index per DTC at CombinedEvent OnStorage. )       */
/*               |                                                          */
/*               | [in] EventCtrlIndex : EventCtrlIndex                     */
/*               |      ( index per Event at CombinedEvent OnStorage. )     */
/*               |                                                          */
/*               | [in] TargetReadinessGroupId :                            */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : DTC in ReadinessGroup is available.       */
/*               |        FALSE : DTC in ReadinessGroup is not available.   */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-10-0     | new created.                                             */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_DTC_GetDTCAvailableInReadinessGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,                /* MISRA DEVIATION */
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u08_ReadinessGroupIdType, AUTOMATIC ) TargetReadinessGroupId       /* MISRA DEVIATION */
)
{
    VAR( boolean, AUTOMATIC ) available;

    /*------------------------------------------------------------------------------------------*/
    /*  if ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON ),                                    */
    /*  user return Available EventId that not have duplicate DTC bit in same ReadinessGroup.   */
    /*  if user return Not Available EventId that not have duplicate DTC bit,                   */
    /*  it's not output in SID19 sf56.                                                          */
    /*------------------------------------------------------------------------------------------*/

    /*  so, check target Event is available or not. ( not check DTC available.)                */
    available   =   Dem_DataAvl_GetEvtAvl( EventCtrlIndex );

    return available;
}
#endif  /* ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON )     */

#if ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_DTC_GetDTCAvailableInReadinessGrp                    */
/* Description   | Check DTC Available in ReadinessGroup.                   */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex : EventStrgIndex                     */
/*               |      ( index per DTC at CombinedEvent OnStorage. )       */
/*               |                                                          */
/*               | [in] EventCtrlIndex : EventCtrlIndex                     */
/*               |      ( index per Event at CombinedEvent OnStorage. )     */
/*               |                                                          */
/*               | [in] TargetReadinessGroupId :                            */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : DTC in ReadinessGroup is available.       */
/*               |        FALSE : DTC in ReadinessGroup is not available.   */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-10-0     | new created.                                             */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_DTC_GetDTCAvailableInReadinessGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_u08_ReadinessGroupIdType, AUTOMATIC ) TargetReadinessGroupId
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexCheck;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexCnt;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexNum;

    VAR( Dem_u08_ReadinessGroupIdType, AUTOMATIC ) readinessGroupId;
    VAR( boolean, AUTOMATIC ) eventAvailableByEvtCtrlIdx;
    VAR( boolean, AUTOMATIC ) eventAvailableInReadinessGrpDTC;

    /*  set calibration / configuration value.  */
    eventCtrlIndexNum   =   Dem_CmbEvt_NumOfEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );  /* [GUD:RET:more than 1]EventStrgIndex *//*  get EventCtrlIndex of EventStorageGroup max number  */

    if ( eventCtrlIndexNum > (Dem_u16_EventCtrlIndexType)1U )
    {
        /*--------------------------------------*/
        /*  duplicate DTC.                      */
        /*--------------------------------------*/
        eventCtrlIndexCheck =   EventCtrlIndex;    /*  check start of EventCtrlIndex */

        /*--------------------------------------------------------------------------*/
        /*  if all event in DTC that has same ReadinessGroup  are not available,    */
        /*  the DTC in ReadinessGroup is not available.                             */
        /*--------------------------------------------------------------------------*/
        /*  initialize : FALSE( not available )     */
        eventAvailableInReadinessGrpDTC     =   (boolean)FALSE;
        for ( eventCtrlIndexCnt = ( Dem_u16_EventCtrlIndexType )0U; eventCtrlIndexCnt < eventCtrlIndexNum; eventCtrlIndexCnt++ )
        {
            /*  Get the ReadinessGroupIndex of the target event.       */
            readinessGroupId    =   Dem_CfgInfoPm_GetReadinessGroupIdForSID1956( eventCtrlIndexCheck ); /* [GUDCHK:CALLER]EventCtrlIndex *//* [GUD]EventStrgIndex */

            /*  Check whether the event in DTC have a target ReadinessGroupID.      */
            if ( readinessGroupId == TargetReadinessGroupId )
            {
                /*  It has target ReadinessGroupID.                 */
                /*  check target event available.                   */
                eventAvailableByEvtCtrlIdx = Dem_DataAvl_GetEvtAvl( eventCtrlIndexCheck );     /* [GUDCHK:CALLER]EventCtrlIndex *//* [GUD]EventStrgIndex */

                if ( eventAvailableByEvtCtrlIdx == (boolean)TRUE )
                {
                    /*  DTC is available at target readiness group. */
                    eventAvailableInReadinessGrpDTC     =   (boolean)TRUE;
                    break;
                }
            }
            eventCtrlIndexCheck  =   Dem_CmbEvt_GetNextEventCtrlIndex_InEvtStrgGrp( eventCtrlIndexCheck );        /* [GUD]EventStrgIndex */
        }
    }
    else
    {
        /*--------------------------------------*/
        /*  single DTC.                         */
        /*--------------------------------------*/
        /*  check DTC available.                */
        eventAvailableInReadinessGrpDTC   =   Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( EventStrgIndex );
    }
    return eventAvailableInReadinessGrpDTC;
}

#endif  /* ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON )     */
#endif  /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
