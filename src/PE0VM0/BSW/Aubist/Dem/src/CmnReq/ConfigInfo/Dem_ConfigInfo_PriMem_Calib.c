/* Dem_ConfigInfo_PriMem_Calib_c(v5-5-0)                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/ConfigInfo_PriMem_Calib/CODE                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_OFF )

#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_PBcfg.h"
#include "../../../cfg/Dem_Data_Cfg.h"
#include "../../../cfg/Dem_Readiness_Cfg.h"
#include "../../../cfg/Dem_WWHObd_Cfg.h"
#include "../../../cfg/Dem_CombinedEvent_Cfg.h"

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
#include "../../../cfg/Dem_Similar_Cfg.h"
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) */

#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"

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
/* External Functions(PreInit section)                                      */
/****************************************************************************/
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetFCThreshold                             */
/* Description   | GetData by EventIndex                                    */
/* Preconditions | EventCtrlIndex < Dem_PrimaryMemEventConfigureNum         */
/* Parameters    | [in] EventCtrlIndex :  EventIndex                        */
/* Return Value  | Dem_u08_FailureCounterType                               */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_FailureCounterType, DEM_CODE_TRUST ) Dem_CfgInfoPm_GetFCThreshold
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_FailureCounterType, AUTOMATIC ) fcThreshold;

    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( Dem_EventParameterConfigIdType, AUTOMATIC ) eventConfigId;

    /*  convert eventIndex to eventConfigId.        */
    eventId             =   Dem_CfgInfoCalib_CnvEventCtrlIndexToEventId( EventCtrlIndex );                  /* [GUDCHK:CALLER]EventCtrlIndex */
    eventConfigId       =   (Dem_EventParameterConfigIdType)eventId - (Dem_EventParameterConfigIdType)1U;

    /*  get data.        */
    fcThreshold = Dem_PB_FailureCycleCounterThreshold[ eventConfigId ];                                     /* [GUDCHK:CALLER]EventCtrlIndex */

    return fcThreshold;
}

#if ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetEventAvailable                          */
/* Description   | GetData by EventIndex                                    */
/* Preconditions | EventCtrlIndex < Dem_PrimaryMemEventConfigureNum         */
/* Parameters    | [in] EventCtrlIndex :  EventCtrlIndex                    */
/* Return Value  | boolean                                                  */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE_TRUST ) Dem_CfgInfoPm_GetEventAvailable
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_PB_EventAttributeType, AUTOMATIC ) eventAttr;
    VAR( boolean, AUTOMATIC ) eventAvailableDef;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( Dem_EventParameterConfigIdType, AUTOMATIC ) eventConfigId;

    /*  convert eventIndex to eventConfigId.        */
    eventId             =   Dem_CfgInfoCalib_CnvEventCtrlIndexToEventId( EventCtrlIndex );                      /* [GUDCHK:CALLER]EventCtrlIndex */
    eventConfigId       =   (Dem_EventParameterConfigIdType)eventId - (Dem_EventParameterConfigIdType)1U;
    /*  get data.        */
    eventAttr   = Dem_PB_EventParameterAttribute[ eventConfigId ];                                              /* [GUDCHK:CALLER]EventCtrlIndex */
    eventAvailableDef    =   (boolean)FALSE;

    if (( eventAttr & DEM_PB_EVTATTR_AVAILABLE_ENABLE ) == DEM_PB_EVTATTR_AVAILABLE_ENABLE )
    {
        eventAvailableDef    =   (boolean)TRUE;  /*  EventAvailable     */
    }

    return eventAvailableDef;
}
#endif /* DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON */


#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_CheckEventKindOfOBD_ByEvtCtrlIdx           */
/* Description   | OBD event or not.                                        */
/* Preconditions | EventCtrlIndex < Dem_PrimaryMemEventConfigureNum         */
/* Parameters    | [in] EventCtrlIndex :  EventCtrlIndex                    */
/* Return Value  | boolean                                                  */
/*               |          FALSE  :   non OBD event.                       */
/*               |          TRUE   :   OBD event.                           */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_GetEventKindOfOBD_ByEvtCtrlIdx
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,            /* [PRMCHK:CALLER] */
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCClassPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) IsMILIndicatorPtr
)
{
    VAR( boolean, AUTOMATIC ) eventOBDKind;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( Dem_EventParameterConfigIdType, AUTOMATIC ) eventConfigId;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventAttributeType, AUTOMATIC ) eventAttrCtrl;
    VAR( Dem_u16_EventAttributeType, AUTOMATIC ) eventAttrStrg;
    VAR( Dem_DTCSeverityType, AUTOMATIC ) dtcClass;
    VAR( boolean, AUTOMATIC ) isMILIndicator;

    /*  convert eventIndex to eventConfigId.        */
    eventId             =   Dem_CfgInfoCalib_CnvEventCtrlIndexToEventId( EventCtrlIndex );                      /* [GUDCHK:CALLER]EventCtrlIndex */
    eventConfigId       =   (Dem_EventParameterConfigIdType)eventId - (Dem_EventParameterConfigIdType)1U;

    /*  get data.        */
    eventAttrCtrl   =   Dem_PB_EventParameterAttribute[ eventConfigId ];                                              /* [GUDCHK:CALLER]EventCtrlIndex */
    eventOBDKind    =   (boolean)FALSE;

    if (( eventAttrCtrl & DEM_PB_EVTATTR_OBD_OBD ) == DEM_PB_EVTATTR_OBD_OBD )
    {
        eventOBDKind    =   (boolean)TRUE;  /*  OBD     */
    }

    eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );
    dtcClass        =   Dem_EventParameterStorageTable[ eventStrgIndex ].DemDTCClass;                               /* [GUDCHK:CALLER]EventCtrlIndex */
    eventAttrStrg   =   Dem_EventParameterStorageTable[ eventStrgIndex ].DemEventAttribute;                         /* [GUDCHK:CALLER]EventCtrlIndex */

    isMILIndicator  =   (boolean)FALSE;
    if(( eventAttrStrg & DEM_EVTATTR_MIL_USE ) == DEM_EVTATTR_MIL_USE )
    {
        isMILIndicator  =   (boolean)TRUE;
    }

    if( eventOBDKind == (boolean)FALSE )
    {
        /*  [ correct ] if nonOBD, MIL is OFF.          */
        isMILIndicator  =   (boolean)FALSE;     /*  nonOBD => MIL OFF       */
    }

    *DTCClassPtr        =   dtcClass;
    *IsMILIndicatorPtr  =   isMILIndicator;

    return eventOBDKind;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_CheckEventKindOfOBD_ByEvtCtrlIdx           */
/* Description   | OBD event or not.                                        */
/* Preconditions | EventCtrlIndex < Dem_PrimaryMemEventConfigureNum         */
/* Parameters    | [in] EventCtrlIndex :  EventCtrlIndex                    */
/* Return Value  | boolean                                                  */
/*               |          FALSE  :   non OBD event.                       */
/*               |          TRUE   :   OBD event.                           */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_CheckEventKindOfOBD_ByEvtCtrlIdx
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_PB_EventAttributeType, AUTOMATIC ) eventAttr;
    VAR( boolean, AUTOMATIC ) eventOBDKind;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( Dem_EventParameterConfigIdType, AUTOMATIC ) eventConfigId;

    /*  convert eventIndex to eventConfigId.        */
    eventId             =   Dem_CfgInfoCalib_CnvEventCtrlIndexToEventId( EventCtrlIndex );                      /* [GUDCHK:CALLER]EventCtrlIndex */
    eventConfigId       =   (Dem_EventParameterConfigIdType)eventId - (Dem_EventParameterConfigIdType)1U;

    /*  get data.        */
    eventAttr   = Dem_PB_EventParameterAttribute[ eventConfigId ];                                              /* [GUDCHK:CALLER]EventCtrlIndex */
    eventOBDKind    =   (boolean)FALSE;

    if (( eventAttr & DEM_PB_EVTATTR_OBD_OBD ) == DEM_PB_EVTATTR_OBD_OBD )
    {
        eventOBDKind    =   (boolean)TRUE;  /*  OBD     */
    }

    return eventOBDKind;
}


#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_Event_EventPriority                        */
/* Description   | GetData by EventStrgIndex                                */
/* Preconditions | EventStrgIndex < Dem_PrimaryMemEventConfigureNum         */
/* Parameters    | [in] EventStrgIndex :  EventStrgIndex                    */
/* Return Value  | Dem_u08_EventPriorityType                                */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_EventPriorityType, DEM_CODE ) Dem_CfgInfoPm_GetEventPriority
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_EventPriorityType, AUTOMATIC ) eventPriority;

    /*  get data.        */
    eventPriority = Dem_EventParameterStorageTable[ EventStrgIndex ].DemEventPriority;                          /* [GUDCHK:CALLER]EventStrgIndex */

    return eventPriority;
}
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_OFF )
#if ( DEM_OBDONEDS_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_Event_EventPriority                        */
/* Description   | GetData by EventStrgIndex                                */
/* Preconditions | EventStrgIndex < Dem_PrimaryMemEventConfigureNum         */
/* Parameters    | [in] EventStrgIndex :  EventStrgIndex                    */
/* Return Value  | Dem_u08_EventPriorityType                                */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_EventPriorityType, DEM_CODE ) Dem_CfgInfoPm_GetEventPriority
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_EventPriorityType, AUTOMATIC ) eventPriority;

    /*  get data.        */
    eventPriority = Dem_EventParameterStorageTable[ EventStrgIndex ].DemEventPriority;                          /* [GUDCHK:CALLER]EventStrgIndex */

    return eventPriority;
}
#endif  /* ( DEM_OBDONEDS_SUPPORT == STD_ON )                */
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_OFF ) */


/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetUdsDTCValue                             */
/* Description   | GetData by EventIndex : DTC value                        */
/* Preconditions | EventStrgIndex < Dem_PrimaryMemEventStorageNum           */
/* Parameters    | [in] EventStrgIndex :  EventIndex                        */
/* Return Value  | Dem_u32_DTCValueType                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u32_DTCValueType, DEM_CODE ) Dem_CfgInfoPm_GetUdsDTCValue
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) udsDTCValue;

    /*  get UDS DTC value.                   */
    udsDTCValue    =   Dem_EventParameterStorageTable[ EventStrgIndex ].DemDtcValue;                            /* [GUDCHK:CALLER]EventStrgIndex */

    return udsDTCValue;
}


#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetObdDTCValue                             */
/* Description   | GetData by EventIndex : DTC value                        */
/* Preconditions | EventStrgIndex < Dem_PrimaryMemEventStorageNum           */
/* Parameters    | [in] EventStrgIndex :  EventIndex                        */
/* Return Value  | Dem_u16_ObdDTCValueType                                  */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u16_ObdDTCValueType, DEM_CODE ) Dem_CfgInfoPm_GetObdDTCValue
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_ObdDTCValueType, AUTOMATIC ) obdDTCValue;

    /*  get OBD DTC value.                   */
    obdDTCValue =   Dem_EventParameterStorageTable[ EventStrgIndex ].DemObdDtcValue;                            /* [GUDCHK:CALLER]EventStrgIndex */

    return obdDTCValue;
}
#endif  /*  ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )   */

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetIsWIRIndicator                          */
/* Description   | GetData by EventIndex                                    */
/* Preconditions | EventStrgIndex < Dem_PrimaryMemEventStorageNum           */
/* Parameters    | [in] EventStrgIndex :  EventIndex                        */
/* Return Value  | boolean                                                  */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_GetIsWIRIndicator
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_EventAttributeType, AUTOMATIC ) eventAttr;
    VAR( boolean, AUTOMATIC ) isWIRIndicator;

    /*  get data.        */
    eventAttr = Dem_EventParameterStorageTable[ EventStrgIndex ].DemEventAttribute;                         /* [GUDCHK:CALLER]EventStrgIndex */

    isWIRIndicator    =   (boolean)FALSE;
    if(( eventAttr & DEM_EVTATTR_INDICATOR_USE ) == DEM_EVTATTR_INDICATOR_USE )
    {
        isWIRIndicator    =   (boolean)TRUE;
    }
    return isWIRIndicator;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetIsActiveFault                           */
/* Description   | GetData by EventIndex                                    */
/* Preconditions | EventStrgIndex < Dem_PrimaryMemEventStorageNum           */
/* Parameters    | [in] EventStrgIndex :  EventIndex                        */
/* Return Value  | boolean                                                  */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_GetIsActiveFault
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_EventAttributeType, AUTOMATIC ) eventAttr;
    VAR( boolean, AUTOMATIC ) isActiveFault;

    /*  get data.        */
    eventAttr = Dem_EventParameterStorageTable[ EventStrgIndex ].DemEventAttribute;                         /* [GUDCHK:CALLER]EventStrgIndex */

    isActiveFault    =   (boolean)FALSE;
    if(( eventAttr & DEM_EVTATTR_HEALING_USE ) == DEM_EVTATTR_HEALING_USE )
    {
        isActiveFault    =   (boolean)TRUE;
    }
    return isActiveFault;
}

#if ( DEM_INDICATOR_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetHealingThreshold                        */
/* Description   | GetData by EventIndex                                    */
/* Preconditions | EventStrgIndex < Dem_PrimaryMemEventStorageNum           */
/* Parameters    | [in] EventStrgIndex :  EventIndex                        */
/* Return Value  | Dem_u08_HealingCounterType                               */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_HealingCounterType, DEM_CODE ) Dem_CfgInfoPm_GetHealingThreshold
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_HealingCounterType, AUTOMATIC ) healingCounterThreshold;

    /*  get data.        */
    healingCounterThreshold = Dem_EventParameterStorageTable[ EventStrgIndex ].DemIndicatorHealingCycleCounterThreshold;                            /* [GUDCHK:CALLER]EventStrgIndex */

    return healingCounterThreshold;
}
#endif  /* ( DEM_INDICATOR_USE == STD_ON )    */

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetAgingAllowed                            */
/* Description   | GetData by EventIndex : Dem_DTCAttributeTable[].DemAgingAllowed    */
/* Preconditions | EventStrgIndex < Dem_PrimaryMemEventStorageNum           */
/* Parameters    | [in] EventStrgIndex :  EventIndex                        */
/* Return Value  | boolean                                                  */
/*               |          TRUE    : Aging Allowed                         */
/*               |          FALSE   :   not Aging Allowed                   */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_GetAgingAllowed
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_DTCAttrIndexType, AUTOMATIC ) dtcAttrRef;
    VAR( boolean, AUTOMATIC ) agingAllowed;

    /*  get DTCAttributeTable index.            */
    dtcAttrRef    =   Dem_EventParameterStorageTable[ EventStrgIndex ].DemDTCAttributesRef;                         /* [GUDCHK:CALLER]EventStrgIndex */

    /*------------------------------------------------------------------------------------------------------*/
    /*  If EventIndex do not have DTC Attribute, [dtcAttrRef] is point to the invalid information area.     */
    /*  Therefore, it's no need dtcAttrRef value area guard.                                                */
    /*------------------------------------------------------------------------------------------------------*/

    /*  get config data.                        */
    agingAllowed    =   Dem_DTCAttributeTable[ dtcAttrRef ].DemAgingAllowed;                                        /* [GUDCHK:CALLER]EventStrgIndex */

    return agingAllowed;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetAgingCycleThreshold                     */
/* Description   | GetData by EventIndex : Dem_DTCAttributeTable[].DemAgingCycleCounterThreshold    */
/* Preconditions | EventStrgIndex < Dem_PrimaryMemEventStorageNum           */
/* Parameters    | [in] EventStrgIndex :  EventIndex                        */
/* Return Value  | Dem_u08_AgingCounterType                                 */
/*               |           Aging counter threshold                        */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_AgingCounterType, DEM_CODE ) Dem_CfgInfoPm_GetAgingCycleThreshold
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_DTCAttrIndexType, AUTOMATIC ) dtcAttrRef;
    VAR( Dem_u08_AgingCounterType, AUTOMATIC ) agingCycleCounterThreshold;

    /*  get DTCAttributeTable index.            */
    dtcAttrRef    =   Dem_EventParameterStorageTable[ EventStrgIndex ].DemDTCAttributesRef;                         /* [GUDCHK:CALLER]EventStrgIndex */

    /*  get config data.                        */
    agingCycleCounterThreshold    =   Dem_DTCAttributeTable[ dtcAttrRef ].DemAgingCycleCounterThreshold;            /* [GUDCHK:CALLER]EventStrgIndex */

    return agingCycleCounterThreshold;
}

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetTimeAgingCounterThreshold               */
/* Description   | Get configuration value Dem_WWHOBDAgingTimeThreshold     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u16_WWHOBDTimeAgingCounterType                       */
/*               |           Time aging counter threshold                   */
/* Notes         | Return value is common to all events.                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u16_WWHOBDTimeAgingCounterType, DEM_CODE ) Dem_CfgInfoPm_GetTimeAgingCounterThreshold
( void )
{
    return Dem_WWHOBDAgingTimeThreshold;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetB1CounterThresholdAndHold               */
/* Description   | Get configuration value Dem_WWHOBDB1CounterThreshold     */
/* Preconditions | none                                                     */
/* Parameters    | [out] B1ThresholdPtr                                     */
/*               | [out] B1HoldPtr                                          */
/* Return Value  | void                                                     */
/* Notes         | Return value is common to all events.                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_CfgInfoPm_GetB1CounterThresholdAndHold
(
    P2VAR( Dem_u32_B1CounterType, AUTOMATIC, AUTOMATIC ) B1ThresholdPtr,
    P2VAR( Dem_u32_B1CounterType, AUTOMATIC, AUTOMATIC ) B1HoldPtr
)
{
    *B1ThresholdPtr =  Dem_WWHOBDB1CounterThreshold;
    *B1HoldPtr = Dem_WWHOBDB1CounterHold;
    return;
}
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

#if ( DEM_PFC_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetPFCClearPattern                         */
/* Description   | GetData by EventIndex                                    */
/* Preconditions | EventStrgIndex < Dem_PrimaryMemEventStorageNum           */
/* Parameters    | [in] EventStrgIndex :  EventIndex                        */
/* Return Value  | boolean                                                  */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_GetPFCClearPattern
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_EventAttributeType, AUTOMATIC ) eventAttr;
    VAR( boolean, AUTOMATIC ) clearPattern;

    /*  get data.        */
    eventAttr = Dem_EventParameterStorageTable[ EventStrgIndex ].DemEventAttribute;                             /* [GUDCHK:CALLER]EventStrgIndex */

    clearPattern    =   (boolean)FALSE;
    if(( eventAttr & DEM_EVTATTR_PFCCLRPTN_MINRATIO ) == DEM_EVTATTR_PFCCLRPTN_MINRATIO )
    {
        clearPattern    =   (boolean)TRUE;
    }
    return clearPattern;
}
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )  */

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetPendingClearCntThreshold                */
/* Description   | Get Pending Clear Cnt Threshold                          */
/* Preconditions | SimilarStrgIndex < Dem_SimilarEventNum                   */
/* Parameters    | [in]  SimilarStrgIndex                                   */
/* Return Value  | Dem_u08_SimilarPendingClearCounterType                   */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_SimilarPendingClearCounterType, DEM_CODE) Dem_CfgInfoPm_GetPendingClearCntThreshold
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_SimilarPendingClearCounterType, AUTOMATIC ) threshold;

    threshold   =   Dem_SimilarClassRefTable[ SimilarStrgIndex ].DemPendingClearCntThreshold;                   /* [GUDCHK:CALLER]SimilarStrgIndex */

    return threshold;
}
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) */

#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetEventNumberOfReadinessGroup             */
/* Description   | Get the number of events that belong to the correspondi- */
/*               | ng readiness group.                                      */
/* Preconditions |                                                          */
/* Parameters    | [in]  CalcType :                                         */
/*               |        Calclation Target Type.                           */
/*               | [in] ReadinessGroupIndex :                               */
/*               |        Readiness group index.                            */
/* Return Value  | Dem_u16_EventCtrlIndexType                               */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u16_EventCtrlIndexType, DEM_CODE ) Dem_CfgInfoPm_GetEventNumberOfReadinessGroup
(
    VAR( Dem_u08_ReadinessDataPositionIndexType, AUTOMATIC )    CalcType,
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC )    ReadinessGroupIndex            /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )    eventNumberOfReadinessGroup;

    if ( CalcType < DEM_READINESS_DATAPOSITIONTABLE_NUM )                   /* [GUD:if]CalcType */
    {
        eventNumberOfReadinessGroup = Dem_ReadinessDataPositionTable[ CalcType ].ReadinessGrpTblPtr[ ReadinessGroupIndex ].TableNum;    /* [GUD]CalcType */ /* [GUDCHK:CALLER]ReadinessGroupIndex */
    }
    else
    {
        eventNumberOfReadinessGroup = Dem_ReadinessGroupTable[ ReadinessGroupIndex ].TableNum;                  /* [GUDCHK:CALLER]ReadinessGroupIndex */
    }

    return eventNumberOfReadinessGroup;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetEventCtrlIndexOfReadinessGroup          */
/* Description   | Get the EventIndex that belongs to the corresponding re- */
/*               | adiness group.                                           */
/* Preconditions |                                                          */
/* Parameters    | [in]  CalcType :                                         */
/*               |        Calclation Target Type.                           */
/*               | [in] ReadinessGroupIndex :                               */
/*               |        Readiness group index.                            */
/*               | [in] EventListIndex :                                    */
/*               |        Event List index.                                 */
/* Return Value  | Dem_u16_EventCtrlIndexType                               */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u16_EventCtrlIndexType, DEM_CODE ) Dem_CfgInfoPm_GetEventCtrlIndexOfReadinessGroup
(
    VAR( Dem_u08_ReadinessDataPositionIndexType, AUTOMATIC )    CalcType,
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC )    ReadinessGroupIndex,           /* [PRMCHK:CALLER] */
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )    EventListIndex                      /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )    eventCtrlIndex;

    if ( CalcType < DEM_READINESS_DATAPOSITIONTABLE_NUM )                   /* [GUD:if]CalcType */
    {
        eventCtrlIndex = Dem_ReadinessDataPositionTable[ CalcType ].ReadinessGrpTblPtr[ ReadinessGroupIndex ].EvtIdxListPtr[ EventListIndex ];  /* [GUD]CalcType *//* [GUDCHK:CALLER]ReadinessGroupIndex *//* [GUDCHK:CALLER]EventListIndex */
    }
    else
    {
        eventCtrlIndex = Dem_ReadinessGroupTable[ ReadinessGroupIndex ].EvtIdxListPtr[ EventListIndex ];        /* [GUDCHK:CALLER]ReadinessGroupIndex *//* [GUDCHK:CALLER]EventListIndex */
    }

    return eventCtrlIndex;
}
#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON )    */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_JudgeOutputPendingOBDFFDWithoutCDTC        */
/* Description   | Get OutputPendingOBDFFD Without CDTC                     */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_JudgeOutputPendingOBDFFDWithoutCDTC
( void )
{
    VAR( boolean, AUTOMATIC ) outputPendingOBDFFDWithoutCDTC;

    outputPendingOBDFFDWithoutCDTC   =   Dem_OBDOutputPendingOBDFFDWithoutCDTC;

    return outputPendingOBDFFDWithoutCDTC;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )   */

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetEventNumberOfSameDTCGroup               */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] Dem_u16_EventStrgIndexType  :                       */
/*               |        EventStrgIndex.                                   */
/* Return Value  | Dem_u16_EventStrgIndexType                               */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_CfgInfoPm_GetEventNumberOfSameDTCGroup
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) numOfEventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexNum;
    VAR( Dem_u16_DTCGrpTableIndexType, AUTOMATIC ) dtcGrpTableIndex;

    eventStrgIndexNum = Dem_PrimaryMemEventStorageNum;
    numOfEventStrgIndex = ( Dem_u16_EventStrgIndexType )0U;

    /* EventStrgIndex is guaranteed. */
    /* This check is implemented to make sure. */
    if( EventStrgIndex < eventStrgIndexNum )
    {
        dtcGrpTableIndex = Dem_CmbTable_DTCGrpTableIndexTable[ EventStrgIndex ];    /* [GUD]EventStrgIndex */

        /* Convert to available index. */
        dtcGrpTableIndex = ( dtcGrpTableIndex & ~DEM_CMBEVT_SAMEDTCGROUP_MARKBIT );

        numOfEventStrgIndex = Dem_CmbTable_NumOfEventStrgIndexInDTCGrpTable[ dtcGrpTableIndex ];    /* [GUD]dtcGrpTableIndex */
    }

    return numOfEventStrgIndex;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetNextEventStrgIndexOfSameDTCGroup        */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] Dem_u16_EventStrgIndexType  :                       */
/*               |        EventStrgIndex.                                   */
/* Return Value  | Dem_u16_EventStrgIndexType                               */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:IF_GUARDED: EventStrgIndex ] ReturnValue        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_CfgInfoPm_GetNextEventStrgIndexOfSameDTCGroup
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) nextEventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexNum;

    eventStrgIndexNum = Dem_PrimaryMemEventStorageNum;
    nextEventStrgIndex = EventStrgIndex;

    /* EventStrgIndex is guaranteed. */
    /* This check is implemented to make sure. */
    if ( EventStrgIndex < eventStrgIndexNum )                                   /* [GUD:if]EventStrgIndex */
    {
        nextEventStrgIndex = Dem_CmbTable_DTCGrpLinkTable[ EventStrgIndex ];    /* [GUD]EventStrgIndex *//* [GUD:CFG]nextEventStrgIndex */
    }

    return nextEventStrgIndex;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_CheckDelegateEventStrgIndexInSameDTCGroup  */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :  EventStrgIndex                    */
/* Return Value  | boolean                                                  */
/*               |          TRUE  : Delegate EventStrgIndex.                */
/*               |          FALSE : No Delegate EventStrgIndex.             */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_CheckDelegateEventStrgIndexInSameDTCGroup
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_DTCGrpTableIndexType, AUTOMATIC ) dtcGrpTableIndex;
    VAR( boolean, AUTOMATIC ) bDelegate;

    /*  Delegate EventStrgIndex.        */
    bDelegate   =   (boolean)TRUE;

    dtcGrpTableIndex  =   Dem_CmbTable_DTCGrpTableIndexTable[ EventStrgIndex ];                  /* [GUDCHK:CALLER]EventStrgIndex */
    if (( dtcGrpTableIndex & DEM_CMBEVT_SAMEDTCGROUP_MARKBIT ) == DEM_CMBEVT_SAMEDTCGROUP_MARKBIT )
    {
        /*  No Delegate EventStrgIndex.     */
        bDelegate   =   (boolean)FALSE;
    }

    return bDelegate;
}


#endif  /* ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )   */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif  /* ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_OFF )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
