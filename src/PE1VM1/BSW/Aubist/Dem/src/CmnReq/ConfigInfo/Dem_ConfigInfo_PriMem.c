/* Dem_ConfigInfo_PriMem_c(v5-10-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/ConfigInfo_PriMem/CODE                                */
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
#include "../../../cfg/Dem_Readiness_Cfg.h"

#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_DTC_DTCStatus.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include "../../../cfg/Dem_Misfire_Cfg.h"
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )    */
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
#include "../../../cfg/Dem_Similar_Cfg.h"
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) */

#include "Dem_ConfigInfo_Calibration.h"

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

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_CnvEventIdToEventCtrlIndex                 */
/* Description   | Converts an event ID to event index.                     */
/* Preconditions | The specified event ID has been already registered.      */
/* Parameters    | [in] EventId :                                           */
/*               |        The event ID for retrieving.                      */
/*               | [out] EventCtrlIndexPtr :                                */
/*               |        The event index which has been retrieved.         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The event index retrieving is succe- */
/*               |        ssful.                                            */
/*               |        DEM_IRT_NG : The event index retrieving is faile- */
/*               |        d.                                                */
/* Notes         | none                                                     */
/* Func History  | name(v3-0-0) : Dem_Data_ConvertEventIdToIndex            */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoPm_CnvEventIdToEventCtrlIndex
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC, AUTOMATIC ) EventCtrlIndexPtr
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventConfigureNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;

    eventConfigureNum = Dem_PrimaryMemEventConfigureNum;
    eventCtrlIndex      =   DEM_EVENTCTRLINDEX_INVALID;

    retVal  =   Dem_CfgInfoCmn_CnvEventIdToEventCtrlIndex( EventId, &eventCtrlIndex );

    if ( retVal == DEM_IRT_OK )
    {
        /* Checks the specified event ID be within the range. */
        if( eventCtrlIndex >= eventConfigureNum )
        {
            eventCtrlIndex      =   DEM_EVENTCTRLINDEX_INVALID;
            retVal          =   DEM_IRT_NG;
        }
    }
    *EventCtrlIndexPtr      =   eventCtrlIndex;

    /* Returns with the result. */
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_CnvEventCtrlIndexToEventId                 */
/* Description   | Gets an event ID by event index.                         */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] EventCtrlIndex :                                    */
/*               |        The event ID for retrieving.                      */
/*               | [out] EventIdPtr :                                       */
/*               |        The event ID which has been retrieved.            */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The event ID retrieving is successf- */
/*               |        ul.                                               */
/*               |        DEM_IRT_NG : The event ID retrieving is failed.   */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] EventCtrlIndex                      */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoPm_CnvEventCtrlIndexToEventId
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventConfigureNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal  =   DEM_IRT_NG;
    eventConfigureNum = Dem_PrimaryMemEventConfigureNum;

    /* The specified event index is out of the range ? */
    if( EventCtrlIndex < eventConfigureNum )                                                                /* [GUD:if]EventCtrlIndex */
    {
        /* Add 1 to the EventIndex and stores it in the specified EventId storage area. */
        *EventIdPtr   =   Dem_CfgInfoCalib_CnvEventCtrlIndexToEventId( EventCtrlIndex );                    /* [GUD]EventCtrlIndex */

        /* Sets the return value to OK. */
        retVal = DEM_IRT_OK;
    }

    /* Return with the result. */
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_CnvEventStrgIndexToEventId                 */
/* Description   | Gets an event ID by event index.                         */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] EventCtrlIndex :                                    */
/*               |        The event ID for retrieving.                      */
/*               | [out] EventIdPtr :                                       */
/*               |        The event ID which has been retrieved.            */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The event ID retrieving is successf- */
/*               |        ul.                                               */
/*               |        DEM_IRT_NG : The event ID retrieving is failed.   */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] EventStrgIndex                      */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoPm_CnvEventStrgIndexToEventId
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    eventCtrlIndex  =   Dem_CmbEvt_GetDelegateEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );    /*  get Delegate EventCtrlIndex                         */
    retVal  =   Dem_CfgInfoPm_CnvEventCtrlIndexToEventId( eventCtrlIndex, EventIdPtr );         /* [GUD:RET:DEM_IRT_OK]eventCtrlIndex */

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetMaxNumberOfOBDEvent                     */
/* Description   | Max number of OBD event counts.                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | Max number of OBD event                                  */
/* Notes         | it's including nonOBD event by PostBuild setting.        */
/****************************************************************************/
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_CfgInfoPm_GetMaxNumberOfOBDEvent
( void )
{
    return Dem_ObdEventNum;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetDTCStatusAvailabilityMask               */
/* Description   | Gets the DTC Status availability mask.                   */
/* Preconditions | none                                                     */
/* Parameters    | [out] DTCStatusMaskPtr :                                 */
/*               |        The value DTCStatusMask indicates the supported - */
/*               |        DTC status bits from the Dem.All supported infor- */
/*               |        mation is indicated by setting the corresponding  */
/*               |         status bit to 1.See ISO14229-1.                  */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/* Func History  | name(v3-0-0) : Dem_DTC_GetDTCStatusAvailabilityMask      */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_CfgInfoPm_GetDTCStatusAvailabilityMask
(
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusMaskPtr
)
{
    /* Sets DemDtcStatusAvailabilityMask to the specified parameter. */
    (*DTCStatusMaskPtr) = Dem_DtcStatusAvailabilityMask;

    return;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetDTCSeverityAvailabilityMask             */
/* Description   | Gets the DTC Severity availability mask.                 */
/* Preconditions | none                                                     */
/* Parameters    | [out] DTCSeverityMask :                                  */
/*               |        The value DTCSeverityMask indicates the support - */
/*               |        ed DTC severity bits from the Dem. All supporte - */
/*               |        d information is indicated by setting the corre - */
/*               |        sponding status bit to 1. See ISO14229-1.         */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_CfgInfoPm_GetDTCSeverityAvailabilityMask
(
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityMaskPtr
)
{
    /* Sets DemDtcSeverityAvailabilityMask to the specified parameter. */
    *DTCSeverityMaskPtr = Dem_DtcSeverityAvailabilityMask;

    return;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetEventOperationCycleRef                  */
/* Description   | GetData by EventIndex                                    */
/* Preconditions | EventIndex < Dem_PrimaryMemEventConfigureNum             */
/* Parameters    | [in] EventIndex :  EventIndex                            */
/* Return Value  | Dem_u08_OpCycleIndexType                                 */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_OpCycleIndexType, DEM_CODE ) Dem_CfgInfoPm_GetEventOperationCycleRef
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) operationCycleRef;

    /*  get data.        */
    operationCycleRef = Dem_EventParameterTable[ EventCtrlIndex ].DemOperationCycleRef;         /* [GUDCHK:CALLER]EventCtrlIndex */

    return operationCycleRef;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetEventHealingAgingCycleRef               */
/* Description   | GetData by EventIndex                                    */
/* Preconditions | EventStrgIndex < Dem_PrimaryMemEventConfigureNum         */
/* Parameters    | [in] EventStrgIndex :  EventIndex                        */
/* Return Value  | Dem_u08_OpCycleIndexType                                 */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_OpCycleIndexType, DEM_CODE ) Dem_CfgInfoPm_GetEventHealingAgingCycleRef
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) operationCycleRef;

    /*  get data.        */
    operationCycleRef = Dem_EventParameterTable[ EventCtrlIndex ].DemHealingAgingCycleRef;      /* [GUDCHK:CALLER]EventCtrlIndex */

    return operationCycleRef;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetDTCSeverityClass                        */
/* Description   | GetData by EventIndex : DTC class                        */
/* Preconditions | EventStrgIndex < Dem_PrimaryStorageNum                   */
/* Parameters    | [in] EventStrgIndex :  EventIndex                        */
/* Return Value  | Dem_DTCSeverityType                                      */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | refactor function.                                       */
/****************************************************************************/
FUNC( Dem_DTCSeverityType, DEM_CODE ) Dem_CfgInfoPm_GetDTCSeverityClass
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_DTCSeverityType, AUTOMATIC ) dtcClass;
    VAR( boolean, AUTOMATIC ) isMILIndicator;

    eventCtrlIndex  =   Dem_CmbEvt_GetDelegateEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );    /* [GUDCHK:CALLER]EventStrgIndex *//* [GUD:RET:IF_GUARDED:EventStrgIndex]eventCtrlIndex */
    (void)Dem_CfgInfoPm_GetEventKindOfOBD_ByEvtCtrlIdx( eventCtrlIndex, &dtcClass, &isMILIndicator );   /* no return check required *//* [GUDCHK:CALLER]EventStrgIndex */

    return dtcClass;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetIsMILIndicator                          */
/* Description   | GetData by EventIndex                                    */
/* Preconditions | EventStrgIndex < Dem_PrimaryMemEventStorageNum           */
/* Parameters    | [in] EventStrgIndex :  EventIndex                        */
/* Return Value  | boolean                                                  */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | refactor function.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_GetIsMILIndicator
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_DTCSeverityType, AUTOMATIC ) dtcClass;
    VAR( boolean, AUTOMATIC ) isMILIndicator;

    eventCtrlIndex  =   Dem_CmbEvt_GetDelegateEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );    /* [GUDCHK:CALLER]EventStrgIndex *//* [GUD:RET:IF_GUARDED:EventStrgIndex]eventCtrlIndex */
    (void)Dem_CfgInfoPm_GetEventKindOfOBD_ByEvtCtrlIdx( eventCtrlIndex, &dtcClass, &isMILIndicator );   /* no return check required *//* [GUDCHK:CALLER]EventStrgIndex */

    return isMILIndicator;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetFCThresholdAdaptable                    */
/* Description   | GetData by EventIndex                                    */
/* Preconditions | EventIndex < Dem_PrimaryMemEventConfigureNum             */
/* Parameters    | [in] EventIndex :  EventIndex                            */
/* Return Value  | boolean                                                  */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_GetFCThresholdAdaptable
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
)
{
    VAR( Dem_u16_EventAttributeType, AUTOMATIC ) eventAttr;
    VAR( boolean, AUTOMATIC ) fcAdaptable;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventConfigureNum;

    eventConfigureNum = Dem_PrimaryMemEventConfigureNum;

    fcAdaptable  =   (boolean)FALSE;
    if( EventCtrlIndex < eventConfigureNum )                                                                /* [GUD:if]EventCtrlIndex */
    {
        /*  get data.        */
        eventAttr = Dem_EventParameterTable[ EventCtrlIndex ].DemEventAttribute;                            /* [GUD]EventCtrlIndex */

        if(( eventAttr & DEM_EVTATTR_FCTHRESADAPT_ADAPTABLE ) == DEM_EVTATTR_FCTHRESADAPT_ADAPTABLE )
        {
            fcAdaptable  =   (boolean)TRUE;
        }
    }
    return fcAdaptable;
}


#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetPreFFSupported_ByEvtCtrlIdx             */
/* Description   | GetData by EventIndex                                    */
/* Preconditions | EventIndex < Dem_PrimaryMemEventConfigureNum             */
/* Parameters    | [in] EventIndex :  EventIndex                            */
/* Return Value  | boolean                                                  */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_GetPreFFSupported_ByEvtCtrlIdx
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
)
{
    VAR( boolean, AUTOMATIC ) preffSupported;
    VAR( Dem_u16_EventAttributeType, AUTOMATIC ) eventAttr;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventConfigureNum;

    eventConfigureNum = Dem_PrimaryMemEventConfigureNum;

    /*  get data.        */
    preffSupported  =   (boolean)FALSE;

    if( EventCtrlIndex < eventConfigureNum )                                                                /* [GUD:if]EventCtrlIndex */
    {
        eventAttr       =   Dem_EventParameterTable[ EventCtrlIndex ].DemEventAttribute;                    /* [GUD]EventCtrlIndex */
        if (( eventAttr & DEM_EVTATTR_PREFF_USE ) == DEM_EVTATTR_PREFF_USE )
        {
            preffSupported  =   (boolean)TRUE;
        }
    }
    return preffSupported;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetPreFFSupported_InEvtStrgGrp             */
/* Description   | GetData by EventIndex                                    */
/* Preconditions | EventIndex < Dem_PrimaryMemEventConfigureNum             */
/* Parameters    | [in] EventStrgIndex :  EventIndex                        */
/* Return Value  | boolean                                                  */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_GetPreFFSupported_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( boolean, AUTOMATIC ) preffSupported;

    eventStorageNum =   Dem_PrimaryMemEventStorageNum;
    preffSupported  =   (boolean)FALSE;

    if ( EventStrgIndex < eventStorageNum )                                                                 /* [GUD:if]EventStrgIndex */
    {
        eventCtrlIndex  =   Dem_CmbEvt_GetDelegateEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );    /*  get Delegate EventCtrlIndex *//* [GUD]EventStrgIndex */

        /*  get data.        */
        preffSupported  =   Dem_CfgInfoPm_GetPreFFSupported_ByEvtCtrlIdx( eventCtrlIndex );
    }

    return preffSupported;
}
#endif /* DEM_FF_PRESTORAGE_SUPPORT == STD_ON */

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_TriggerInitMForEFnc                        */
/* Description   | Calls callback function "InitMonitorForEvent" correspon- */
/*               | ding to specified event index.                           */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] EventIndex :                                        */
/*               |        The event index corresponding to the event ID.    */
/*               | [in] InitMonitorReason :                                 */
/*               |        The reasion of initializing monitor.              */
/*               | [out] ResultOfCallbackPtr :                              */
/*               |        The result of calling callback function.          */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_CfgInfoPm_TriggerInitMForEFnc
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_InitMonitorReasonType, AUTOMATIC ) InitMonitorReason,
    P2VAR( Std_ReturnType, AUTOMATIC, AUTOMATIC ) ResultOfCallbackPtr
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventConfigureNum;
    VAR( Std_ReturnType, AUTOMATIC ) resultOfCallback;

    /* Initializes the result of callback to OK. */
    resultOfCallback = E_OK;

    eventConfigureNum = Dem_PrimaryMemEventConfigureNum;

    /* Checks the specified event ID be within the range. */
    if( EventCtrlIndex < eventConfigureNum )                                                                                        /* [GUD:if]EventCtrlIndex */
    {
        /* Within the range. */

        /* Checks the presence of the callback function pointer corresponding to the specified event index. */
        if( Dem_EventParameterTable[ EventCtrlIndex ].DemCallbackInitMForEFnc != NULL_PTR )                                         /* [GUD]EventCtrlIndex */
        {
#ifndef JGXSTACK
            /* Calls the callback function corresponding to the specified event index. */
            resultOfCallback = Dem_EventParameterTable[ EventCtrlIndex ].DemCallbackInitMForEFnc( InitMonitorReason );              /* [GUD]EventCtrlIndex */
#else /* JGXSTACK */
            /* user-defined */
#endif /* JGXSTACK */
        }
        else
        {
           /* no processing. */
        }

        /* Stores the result of the callback function to the specified parameter. */
        *ResultOfCallbackPtr = resultOfCallback;
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_TriggerEventStatusChangedFnc               */
/* Description   | Calls callback function "EventStatusChanged" correspond- */
/*               | ing to specified event index.                            */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] EventCtrlIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/*               | [in] OldDTCStatus :                                      */
/*               |        The UDS DTC status byte before updating.          */
/*               | [in] NewDTCStatus :                                      */
/*               |        The UDS DTC status byte after updating.           */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_CfgInfoPm_TriggerEventStatusChangedFnc
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatus,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) NewDTCStatus
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) result;
    P2CONST( AB_83_ConstV Dem_EventParameterType, AUTOMATIC, DEM_CONFIG_DATA ) eventParameterPtr;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) oldDTCStatusTmp;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatusTmp;

    oldDTCStatusTmp =   OldDTCStatus;
    newDTCStatusTmp =   NewDTCStatus;

    /*------------------------------------------*/
    /*  convert to output statusOfDTC.          */
    /*------------------------------------------*/
    Dem_DTC_CnvUpdateDTCStatus_ForOutput( &oldDTCStatusTmp, &newDTCStatusTmp );

    if( oldDTCStatusTmp != newDTCStatusTmp )
    {
        /* Gets an event ID by event index. */
        result = Dem_CfgInfoPm_CnvEventCtrlIndexToEventId( EventCtrlIndex, &eventId );                      /* [GUD:RET:DEM_IRT_OK]EventCtrlIndex */

        /* Check the acquisition result of the event ID. */
        if( result == DEM_IRT_OK )
        {
            /* Holds the event table pointed to by the specified event index. */
            eventParameterPtr = &Dem_EventParameterTable[EventCtrlIndex];                                   /* [GUD]EventCtrlIndex *//* [GUD:CFG:IF_GUARDED: EventCtrlIndex ]eventParameterPtr */

            if( eventParameterPtr->DemCallbackEventStatusChangedFnc != NULL_PTR )                           /* [GUD]eventParameterPtr */
            {
#ifndef JGXSTACK
                /* Calls callback EventStatusChange corresponding to the specified event ID and status. */
                eventParameterPtr->DemCallbackEventStatusChangedFnc( eventId, oldDTCStatusTmp, newDTCStatusTmp );
#else /* JGXSTACK */
                    /* user-defined */
#endif /* JGXSTACK */
            }
            else
            {
                /* no processing. */
            }
        }
    }

    return ;
}

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetDTCAttrTablePtr_TSFF                    */
/* Description   | GetData by EventIndex : address of Dem_DTCAttributeTable[] */
/* Preconditions | EventIndex < Dem_PrimaryMemEventConfigureNum             */
/* Parameters    | [in] EventStrgIndex :  EventIndex                        */
/* Return Value  | Dem_DTCAttributeType*                                    */
/*               |                      != NULL_PTR : available address.    */
/*               |                      == NULL_PTR : INVALID               */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:Not NULL_PTR] EventStrgIndex                    */
/* VariableGuard | [GUD:RET:Not NULL_PTR] ReturnValue                       */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC_P2CONST( AB_83_ConstV Dem_DTCAttributeType, DEM_CONFIG_DATA, DEM_CODE ) Dem_CfgInfoPm_GetDTCAttrTablePtr_TSFF
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) dtcAttributePtr;
    VAR( Dem_u16_DTCAttrIndexType, AUTOMATIC ) dtcAttrRef;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    dtcAttributePtr =   NULL_PTR;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )              /* [GUD:if]EventStrgIndex */
    {
        /* The DTCAttribute table indicated by the DTCAttribute table list Index of the held DTC table is held. */
        dtcAttrRef      =   Dem_EventParameterStorageTable[ EventStrgIndex ].DemDTCAttributesRef;       /* [GUD]EventStrgIndex *//* [GUD:CFG:IF_GUARDED: EventStrgIndex ]dtcAttrRef */
        dtcAttributePtr =   &Dem_DTCAttributeTable[dtcAttrRef];                                         /* [GUD]dtcAttrRef *//* [GUD:CFG:IF_GUARDED: dtcAttrRef ]dtcAttributePtr */
    }
    return dtcAttributePtr;
}

#endif  /*   ( DEM_TSFF_PM_SUPPORT == STD_ON )     */

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp           */
/* Description   | OBD event or not.                                        */
/* Preconditions | EventIndex < Dem_PrimaryMemEventConfigureNum             */
/* Parameters    | [in] EventIndex :  EventIndex                            */
/* Return Value  | boolean                                                  */
/*               |          FALSE  :   non OBD event.                       */
/*               |          TRUE   :   OBD event.                           */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:TRUE] EventStrgIndex                            */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) eventOBDKind;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    eventOBDKind    =   (boolean)FALSE;
    eventStorageNum =   Dem_PrimaryMemEventStorageNum;

    if ( EventStrgIndex < eventStorageNum )                                                     /* [GUD:if]EventStrgIndex */
    {
        /*  convert eventIndex to eventConfigId.        */
        eventCtrlIndex  =   Dem_CmbEvt_GetDelegateEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );    /*  get Delegate EventCtrlIndex *//* [GUD]EventStrgIndex *//* [GUD:RET:IF_GUARDED:EventStrgIndex] eventCtrlIndex */
        eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_ByEvtCtrlIdx( eventCtrlIndex );   /* [GUD]eventCtrlIndex */
    }

    return eventOBDKind;
}


#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_CheckEventKindOfSpecific_ByEvtCtrlIdx      */
/* Description   | Check Specific Event                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventCtrlIndex                                     */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |      TRUE  : Specific Event                              */
/*               |      FALSE : Normal Event                                */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_CheckEventKindOfSpecific_ByEvtCtrlIdx
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventConfigureNum;

    eventConfigureNum = Dem_PrimaryMemEventConfigureNum;

    retVal  =   (boolean)FALSE;
    if( EventCtrlIndex < eventConfigureNum )                                                                /* [GUD:if]EventCtrlIndex */
    {
        eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );                /* [GUD]EventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */
        retVal          =   Dem_CfgInfoPm_CheckEventKindOfSpecific_InEvtStrgGrp( eventStrgIndex );          /* [GUD]eventStrgIndex */
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_CheckEventKindOfSpecific_InEvtStrgGrp      */
/* Description   | Check Specific Event                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStrgIndex                                     */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |      TRUE  : Specific Event                              */
/*               |      FALSE : Normal Event                                */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_CheckEventKindOfSpecific_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventAttributeType, AUTOMATIC ) eventAttr;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    retVal = (boolean)FALSE;
    if ( EventStrgIndex < eventStorageNum )                                                                 /* [GUD:if]EventStrgIndex */
    {
        /*  get data.        */
        eventAttr   =   Dem_EventParameterStorageTable[ EventStrgIndex ].DemEventAttribute;                 /* [GUD]EventStrgIndex */

        if( ( eventAttr & ( DEM_EVTATTR_MISFIRE | DEM_EVTATTR_SIMILAR ) ) != ( Dem_u16_EventAttributeType )0U )
        {
            /*  specific event.         */
            retVal = (boolean)TRUE;
        }
    }
    return retVal;
}
#endif  /*   ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )   */


#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetEventKindOfSpecific_InEvtStrgGrp        */
/* Description   | Get Specific Event Kind.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventCtrlIndex                                     */
/*               |                                                          */
/* Return Value  | Dem_EventKindType                                        */
/*               |      DEM_EVTKIND_TYPE_NON_OBD_EVENT                      */
/*               |                  : no Specific Event                     */
/*               |      |= DEM_EVTKIND_TYPE_SIMILAR_EVENT                   */
/*               |                  : Similar Event                         */
/*               |      |= DEM_EVTKIND_TYPE_MISFIRE_EVENT                   */
/*               |                  : Misfire Event                         */
/*               |      |= DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT               */
/*               |                  : CAT Misfire Event                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_EventKindType, DEM_CODE ) Dem_CfgInfoPm_GetEventKindOfSpecific_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;
    VAR( Dem_u16_EventAttributeType, AUTOMATIC ) eventAttr;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    eventKind   =   DEM_EVTKIND_TYPE_NON_OBD_EVENT;
    if ( EventStrgIndex < eventStorageNum )                                                                 /* [GUD:if]EventStrgIndex */
    {
        /*  get data.        */
        eventAttr   =   Dem_EventParameterStorageTable[ EventStrgIndex ].DemEventAttribute;                 /* [GUD]EventStrgIndex */

        /* Misfire event Judgment */
        if( ( eventAttr & DEM_EVTATTR_MISFIRE ) == DEM_EVTATTR_MISFIRE )
        {
            if( ( eventAttr & DEM_EVTATTR_MISFIRE_CAT ) == DEM_EVTATTR_MISFIRE_CAT )
            {
                /*  not emission misfire event == cat misfire event.        */
                eventKind = ( DEM_EVTKIND_TYPE_MISFIRE_EVENT | DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT );
            }
            else
            {
                eventKind = DEM_EVTKIND_TYPE_MISFIRE_EVENT;
            }
        }

        /* Similar event Judgment */
        if( ( eventAttr & DEM_EVTATTR_SIMILAR ) == DEM_EVTATTR_SIMILAR )
        {
            eventKind = eventKind | DEM_EVTKIND_TYPE_SIMILAR_EVENT;
        }
    }

    return eventKind;
}
#endif  /*   ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )   */

#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_CnvReadinessGroupIdToGroupIndex            */
/* Description   | Convert to ReadinessGroupId to ReadinessGroupTable Index.*/
/* Preconditions |                                                          */
/* Parameters    | [in] ReadinessGroupId :  ReadinessGroupId.               */
/* Return Value  | Dem_u08_ReadinessGroupIndexType                          */
/*               |        Dem_ReadinessGroupTable[] index.                  */
/* Notes         | call from SID19 sf56.                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-10-0     | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_ReadinessGroupIndexType, DEM_CODE ) Dem_CfgInfoPm_CnvReadinessGroupIdToGroupIndex
(
    VAR( Dem_u08_ReadinessGroupIdType, AUTOMATIC ) ReadinessGroupId
)
{
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC ) readinessGroupIndex;

    readinessGroupIndex =   (Dem_u08_ReadinessGroupIndexType)ReadinessGroupId;

    return readinessGroupIndex;
}
#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON )  */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
