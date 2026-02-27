/* Dem_ConfigInfo_PriMem_CalibByCallout_c(v5-10-0)                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/ConfigInfo_PriMem_CalibByCallout/CODE                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON )

#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_PBcfg.h"
#include "../../../cfg/Dem_Data_Cfg.h"
#include "../../../cfg/Dem_Readiness_Cfg.h"
#include "../../../cfg/Dem_Calibration_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"

#include "Dem_ConfigInfo_Calibration.h"
#include "../../../usr/Dem_Calibration_Callout.h"
#include "../../../usr/Dem_PendingOBDFFD_Callout.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_CONFIGINFO_BITSHIFT_8                          ((Dem_u32_DTCValueType)8U)

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

#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
static FUNC( Dem_u08_ReadinessGroupIdType, DEM_CODE ) Dem_CfgInfoPm_CnvReadinessGroupIndexToGroupId
(
    VAR( Dem_u08_ReadinessDataPositionIndexType, AUTOMATIC ) CalcType,
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC ) ReadinessGroupIndex
);
#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON )  */

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
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex     /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_FailureCounterType, AUTOMATIC ) fcThreshold;

    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

    /*  convert eventIndex to eventId.        */
    eventId =   Dem_CfgInfoCalib_CnvEventCtrlIndexToEventId( EventCtrlIndex );  /* [GUDCHK:CALLER]EventCtrlIndex */

    /*  get data.        */
    fcThreshold = Dem_Calib_GetFailureCycleCounterThreshold( eventId );

    /*  check output value.     */
    if ( fcThreshold < DEM_CALIB_FAILURECYCLECNT_THRESHOLD_MIN )
    {
        fcThreshold =   DEM_CALIB_FAILURECYCLECNT_THRESHOLD_DEF;
    }
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
    VAR( boolean, AUTOMATIC ) eventAvailableDef;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

    /*  convert EventCtrlIndex to eventId.        */
    eventId =   Dem_CfgInfoCalib_CnvEventCtrlIndexToEventId( EventCtrlIndex );  /* [GUDCHK:CALLER]EventCtrlIndex */

    /*  get data.        */
    eventAvailableDef   = Dem_Calib_GetEventAvailable( eventId );

    /*  check output value.     */
    if ( eventAvailableDef != (boolean)FALSE )
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
/* Function Name | Dem_CfgInfoPm_GetEventKindOfOBD_ByEvtCtrlIdx             */
/* Description   | OBD event or not.                                        */
/* Preconditions | EventCtrlIndex < Dem_PrimaryMemEventConfigureNum         */
/* Parameters    | [in] EventCtrlIndex      :  EventCtrlIndex               */
/*               | [out] DTCClassPtr        :  DTC Class                    */
/*               | [out] IsMILIndicatorPtr  :  target event has MIL or not. */
/* Return Value  | boolean                                                  */
/*               |          FALSE  :   non OBD event.                       */
/*               |          TRUE   :   OBD event.                           */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.based on Dem_CfgInfoPm_CheckEventKindOfOBD_ByEvtCtrlIdx. */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_GetEventKindOfOBD_ByEvtCtrlIdx
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,            /* [PRMCHK:CALLER] */
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCClassPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) IsMILIndicatorPtr
)
{
    VAR( boolean, AUTOMATIC ) eventOBDKind;
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;
    VAR( Dem_DTCSeverityType, AUTOMATIC ) dtcClass;
    VAR( boolean, AUTOMATIC ) isMILIndicator;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )        /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) isSpecificEvent;

    /*  check specific event or not.        */
    isSpecificEvent =   Dem_CfgInfoPm_CheckEventKindOfSpecific_ByEvtCtrlIdx( EventCtrlIndex );
    if ( isSpecificEvent != (boolean)FALSE )
    {
        eventOBDKind    =   (boolean)TRUE;  /*  OBD     */
        dtcClass        =   DEM_DTC_CLASS_1;
        isMILIndicator  =   (boolean)TRUE;
    }
    else
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )                 */
    {
        /*  convert EventCtrlIndex to eventId.        */
        eventId =   Dem_CfgInfoCalib_CnvEventCtrlIndexToEventId( EventCtrlIndex );  /* [GUDCHK:CALLER]EventCtrlIndex */

        /*  get data.        */
        isMILIndicator  =   (boolean)FALSE;
        dtcClass        =   DEM_SEVERITY_NO_SEVERITY;
        eventKind       =   DEM_EVTKIND_TYPE_NON_OBD_EVENT;
        Dem_Calib_GetEventKind( eventId, &eventKind, &dtcClass, &isMILIndicator );

        /*  check output value.     */

        /*--------------------------*/
        /*  eventOBDKind            */
        /*--------------------------*/
        eventOBDKind    =   (boolean)FALSE;
        if ( eventKind == DEM_EVTKIND_TYPE_OBD_EVENT )
        {
            eventOBDKind    =   (boolean)TRUE;      /*  OBD     */
        }
        /*--------------------------*/
        /*  dtcClass                */
        /*--------------------------*/
        /* check value range.       */
        if(( dtcClass != DEM_SEVERITY_NO_SEVERITY )&&( dtcClass != DEM_DTC_CLASS_0 )&&( dtcClass != DEM_DTC_CLASS_1 )&&( dtcClass != DEM_DTC_CLASS_2 )&&( dtcClass != DEM_DTC_CLASS_3 )&&( dtcClass != DEM_DTC_CLASS_4 ))
        {
            dtcClass        =   DEM_SEVERITY_NO_SEVERITY;
        }

        /*--------------------------*/
        /*  isMILIndicator          */
        /*--------------------------*/
        /* check value range.       */
        if( isMILIndicator != (boolean)TRUE )
        {
            isMILIndicator  =   (boolean)FALSE;
        }
        /* check OBD Kind.          */
        if ( eventOBDKind == (boolean)FALSE )
        {
            /*  [ correct ] if nonOBD, MIL is OFF.          */
            isMILIndicator  =   (boolean)FALSE;     /*  nonOBD => MIL OFF       */
        }
        /* check dtcClass.          */
        if ( dtcClass == DEM_SEVERITY_NO_SEVERITY )
        {
            /*  [ correct ] if DEM_SEVERITY_NO_SEVERITY, MIL is OFF.          */
            isMILIndicator  =   (boolean)FALSE;     /*  nonOBD => MIL OFF       */
        }
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
/*   v5-5-0      | refactor function.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_CheckEventKindOfOBD_ByEvtCtrlIdx
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex             /* [PRMCHK:CALLER] */
)
{
    VAR( boolean, AUTOMATIC ) eventOBDKind;
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;
    VAR( Dem_DTCSeverityType, AUTOMATIC ) dtcClass;
    VAR( boolean, AUTOMATIC ) isMILIndicator;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )        /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) isSpecificEvent;

    /*  check specific event or not.        */
    isSpecificEvent =   Dem_CfgInfoPm_CheckEventKindOfSpecific_ByEvtCtrlIdx( EventCtrlIndex );
    if ( isSpecificEvent != (boolean)FALSE )
    {
        eventOBDKind    =   (boolean)TRUE;  /*  OBD     */
    }
    else
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )                 */
    {
        /*  convert EventCtrlIndex to eventId.        */
        eventId =   Dem_CfgInfoCalib_CnvEventCtrlIndexToEventId( EventCtrlIndex );  /* [GUDCHK:CALLER]EventCtrlIndex */

        /*  get data.        */
        isMILIndicator  =   (boolean)FALSE;
        eventKind       =   DEM_EVTKIND_TYPE_NON_OBD_EVENT;
        Dem_Calib_GetEventKind( eventId, &eventKind, &dtcClass, &isMILIndicator );

        /*  check output value.     */
        eventOBDKind    =   (boolean)FALSE;
        if ( eventKind == DEM_EVTKIND_TYPE_OBD_EVENT )
        {
            eventOBDKind    =   (boolean)TRUE;      /*  OBD     */
        }
    }
    return eventOBDKind;
}

#if ( DEM_EVENTPRIORITY_PM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetEventPriority                           */
/* Description   | GetData by EventStrgIndex                                */
/* Preconditions | EventStrgIndex < Dem_PrimaryMemEventConfigureNum         */
/* Parameters    | [in] EventStrgIndex :  EventStrgIndex                    */
/* Return Value  | Dem_u08_EventPriorityType                                */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_u08_EventPriorityType, DEM_CODE ) Dem_CfgInfoPm_GetEventPriority
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_EventPriorityType, AUTOMATIC ) eventPriority;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

    /*  convert EventStrgIndex to eventId.        */
    eventId =   DEM_EVENTID_INVALID;
    (void)Dem_CfgInfoPm_CnvEventStrgIndexToEventId( EventStrgIndex, &eventId ); /* no return check required */

    /*  get data.        */
    eventPriority   =   Dem_Calib_GetEventPriority( eventId );

    /*------------------------------------------*/
    /*    0:    correct priority(highest)       */
    /*      DEM_PRIORITY_RESERVED_HI_MIN        */
    /*          invalid priority(reserve)       */
    /*      DEM_PRIORITY_RESERVED_HI_MAX        */
    /*          DEM_PRIORITY_OBD_DEFAULT        */
    /*                                          */
    /*              correct priority            */
    /*                                          */
    /*          DEM_PRIORITY_NONOBD_DEFAULT     */
    /*      DEM_PRIORITY_RESERVED_LO_MIN        */
    /*          invalid priority(reserve)       */
    /*  255:DEM_PRIORITY_RESERVED_LO_MAX(255)   */
    /*------------------------------------------*/
    /*  check output value.     */
    if ( eventPriority >= DEM_PRIORITY_RESERVED_LO_MIN )  /*    reserved area check :   low reserve : DEM_PRIORITY_RESERVED_LO_MIN <= value <= DEM_PRIORITY_RESERVED_LO_MAX(255)    */
    {
        eventPriority   =   DEM_PRIORITY_NONOBD_DEFAULT;
    }
    else if ( eventPriority <= DEM_PRIORITY_RESERVED_HI_MAX )  /*    reserved area check :   high reserve : DEM_PRIORITY_RESERVED_HI_MIN <= value <= DEM_PRIORITY_RESERVED_HI_MAX    */
    {
        if ( eventPriority >= DEM_PRIORITY_RESERVED_HI_MIN )  /*    reserved area check :   high value  */
        {
            eventPriority   =   DEM_PRIORITY_NONOBD_DEFAULT;
        }
    }
    else
    {
        /*  no process.         */
    }

    return eventPriority;
}
#endif  /* ( DEM_EVENTPRIORITY_PM_SUPPORT == STD_ON )                */

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetUdsDTCValue                             */
/* Description   | GetData by EventIndex : DTC value                        */
/* Preconditions | EventIndex < Dem_PrimaryMemEventConfigureNum             */
/* Parameters    | [in] EventIndex :  EventIndex                            */
/* Return Value  | Dem_u32_DTCValueType                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u32_DTCValueType, DEM_CODE ) Dem_CfgInfoPm_GetUdsDTCValue
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) udsDTCValue;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) isMisfireEvent;

    isMisfireEvent  =   Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );   /* [GUD:RET:TRUE] EventStrgIndex */
    if ( isMisfireEvent == (boolean)TRUE )
    {
        udsDTCValue    =   Dem_EventParameterStorageTable[ EventStrgIndex ].DemDtcValue;    /* [GUD]EventStrgIndex */
    }
    else
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )     */
    {
        /*  convert eventIndex to eventId.        */
        eventId =   DEM_EVENTID_INVALID;
        (void)Dem_CfgInfoPm_CnvEventStrgIndexToEventId( EventStrgIndex, &eventId ); /* no return check required */

        /*  get UDS DTC value.                   */
        udsDTCValue     =   Dem_Calib_GetUdsDTCValue( eventId );

        /*  mask output value.      */
        udsDTCValue     =   udsDTCValue & DEM_CALIB_UDSDTCVALUE_MASK;
    }
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
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u16_ObdDTCValueType, DEM_CODE ) Dem_CfgInfoPm_GetObdDTCValue
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_ObdDTCValueType, AUTOMATIC ) obdDTCValue;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) udsDTCValue;
    VAR( boolean, AUTOMATIC ) isMisfireEvent;

    isMisfireEvent  =   Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );       /* [GUD:RET:TRUE] EventStrgIndex */
    if ( isMisfireEvent == (boolean)TRUE )
    {
        udsDTCValue =   Dem_EventParameterStorageTable[ EventStrgIndex ].DemDtcValue;               /* [GUD]EventStrgIndex */
        obdDTCValue =   (Dem_u16_ObdDTCValueType)( udsDTCValue >> DEM_CONFIGINFO_BITSHIFT_8 );
    }
    else
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )     */
    {
        /*  convert eventIndex to eventId.        */
        eventId =   DEM_EVENTID_INVALID;
        (void)Dem_CfgInfoPm_CnvEventStrgIndexToEventId( EventStrgIndex, &eventId ); /* no return check required */

        /*  get OBD DTC value.                   */
        obdDTCValue     =   Dem_Calib_GetObdDTCValue( eventId );
    }
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
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_GetIsWIRIndicator
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( boolean, AUTOMATIC ) isWIRIndicator;

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )        /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) isSpecificEvent;

    /*  check specific event or not.        */
    isSpecificEvent =   Dem_CfgInfoPm_CheckEventKindOfSpecific_InEvtStrgGrp( EventStrgIndex );
    if ( isSpecificEvent != (boolean)FALSE )
    {
        isWIRIndicator    =   (boolean)TRUE;
    }
    else
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )                 */
    {
        /*  convert eventIndex to eventId.        */
        eventId =   DEM_EVENTID_INVALID;
        (void)Dem_CfgInfoPm_CnvEventStrgIndexToEventId( EventStrgIndex, &eventId ); /* no return check required */

        /*  get data.        */
        isWIRIndicator  =   Dem_Calib_GetIsWIRIndicator( eventId );

        /*  check output value.     */
        if ( isWIRIndicator != (boolean)TRUE )
        {
            isWIRIndicator    =   (boolean)FALSE;
        }
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
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_GetIsActiveFault
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( boolean, AUTOMATIC ) isActiveFault;
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )        /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) isSpecificEvent;

    /*  check specific event or not.        */
    isSpecificEvent =   Dem_CfgInfoPm_CheckEventKindOfSpecific_InEvtStrgGrp( EventStrgIndex );
    if ( isSpecificEvent != (boolean)FALSE )
    {
        isActiveFault    =   (boolean)TRUE;
    }
    else
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )                 */
    {
        /*  convert eventIndex to eventId.        */
        eventId =   DEM_EVENTID_INVALID;
        (void)Dem_CfgInfoPm_CnvEventStrgIndexToEventId( EventStrgIndex, &eventId ); /* no return check required */

        /*  get data.        */
        isActiveFault   =   Dem_Calib_GetIsActiveFault( eventId );

        /*  check output value.     */
        if ( isActiveFault != (boolean)TRUE )
        {
            isActiveFault    =   (boolean)FALSE;
        }
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
/****************************************************************************/
FUNC( Dem_u08_HealingCounterType, DEM_CODE ) Dem_CfgInfoPm_GetHealingThreshold
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_HealingCounterType, AUTOMATIC ) healingCounterThreshold;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

    /*  convert eventIndex to eventId.        */
    eventId =   DEM_EVENTID_INVALID;
    (void)Dem_CfgInfoPm_CnvEventStrgIndexToEventId( EventStrgIndex, &eventId ); /* no return check required */

    /*  get data.        */
    healingCounterThreshold = Dem_Calib_GetHealingCycleCounterThreshold( eventId );

    /*  check output value.     */
    if ( healingCounterThreshold < DEM_CALIB_HEALINGCYCLECNT_THRESHOLD_MIN )
    {
        healingCounterThreshold =   DEM_CALIB_HEALINGCYCLECNT_THRESHOLD_DEF;
    }

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
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_GetAgingAllowed
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) agingAllowed;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

    /*  convert eventIndex to eventId.        */
    eventId =   DEM_EVENTID_INVALID;
    (void)Dem_CfgInfoPm_CnvEventStrgIndexToEventId( EventStrgIndex, &eventId ); /* no return check required */

    /*  get config data.                        */
    agingAllowed    =   Dem_Calib_GetAgingAllowed( eventId );

    /*  check output value.     */
    if ( agingAllowed != (boolean)FALSE )
    {
        agingAllowed    =   (boolean)TRUE;
    }

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
/****************************************************************************/
FUNC( Dem_u08_AgingCounterType, DEM_CODE ) Dem_CfgInfoPm_GetAgingCycleThreshold
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_AgingCounterType, AUTOMATIC ) agingCycleCounterThreshold;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

    /*  convert eventIndex to eventId.        */
    eventId =   DEM_EVENTID_INVALID;
    (void)Dem_CfgInfoPm_CnvEventStrgIndexToEventId( EventStrgIndex, &eventId ); /* no return check required */

    /*  get config data.                        */
    agingCycleCounterThreshold  =   Dem_Calib_GetAgingCycleCounterThreshold( eventId );

    /*  check output value.     */
    if ( agingCycleCounterThreshold < DEM_CALIB_AGINGCYCLECNT_THRESHOLD_MIN )
    {
        agingCycleCounterThreshold  =   DEM_CALIB_AGINGCYCLECNT_THRESHOLD_DEF;
    }

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
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u16_WWHOBDTimeAgingCounterType, DEM_CODE ) Dem_CfgInfoPm_GetTimeAgingCounterThreshold
( void )
{
    VAR( Dem_u16_WWHOBDTimeAgingCounterType, AUTOMATIC ) timeAgingCounterThreshold;
    timeAgingCounterThreshold = Dem_Calib_GetTimeAgingCounterThreshold();

    if ( timeAgingCounterThreshold < DEM_CALIB_TIMEAGINGCNT_THRESHOLD_MIN)
    {
        timeAgingCounterThreshold = DEM_CALIB_TIMEAGINGCNT_THRESHOLD_DEF;
    }
    return timeAgingCounterThreshold;
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
    VAR( Dem_u32_B1CounterType, AUTOMATIC ) b1CounterHold;
    VAR( Dem_u32_B1CounterType, AUTOMATIC ) b1CounterThreshold;

    Dem_Calib_GetB1CounterThresholdAndHold( &b1CounterThreshold, &b1CounterHold );

    if ( b1CounterThreshold < DEM_CALIB_B1CNT_THRESHOLD_MIN )
    {
        b1CounterThreshold = DEM_CALIB_B1CNT_THRESHOLD_MIN;
    }

    if ( b1CounterHold >= b1CounterThreshold )
    {
        b1CounterHold = b1CounterThreshold - (Dem_u32_B1CounterType)1U; /* no wrap around */
    }

    *B1ThresholdPtr = b1CounterThreshold;
    *B1HoldPtr = b1CounterHold;

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
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_GetPFCClearPattern
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) clearPattern;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

    /*  convert eventIndex to eventId.        */
    eventId =   DEM_EVENTID_INVALID;
    (void)Dem_CfgInfoPm_CnvEventStrgIndexToEventId( EventStrgIndex, &eventId ); /* no return check required */

    /*  get data.        */
    clearPattern    = Dem_Calib_GetPFCClearPattern( eventId );

    /*  check output value.     */
    if ( clearPattern != (boolean)TRUE )
    {
        clearPattern    =   (boolean)FALSE;
    }
    return clearPattern;
}
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )  */

#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetIUMPROutputNecessary                    */
/* Description   | GetData by EventIndex                                    */
/* Preconditions | EventIndex < Dem_PrimaryMemEventConfigureNum             */
/* Parameters    | [in] EventIndex :  EventIndex                            */
/* Return Value  | boolean                                                  */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_GetIUMPROutputNecessary
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex             /* [PRMCHK:CALLER] */
)
{
    VAR( boolean, AUTOMATIC ) outputNecessary;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

    /*  convert eventIndex to eventId.        */
    eventId =   Dem_CfgInfoCalib_CnvEventCtrlIndexToEventId( EventCtrlIndex );  /* [GUDCHK:CALLER]EventCtrlIndex */

    /*  get data.        */
    outputNecessary = Dem_Calib_GetIUMPROutputNecessary( eventId );

    /*  check output value.     */
    if ( outputNecessary != (boolean)FALSE )
    {
        outputNecessary =   (boolean)TRUE;
    }

    return outputNecessary;
}
#endif  /* ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )  */

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetPendingClearCntThreshold                */
/* Description   | Get Pending Clear Cnt Threshold                          */
/* Preconditions | SimilarStrgIndex < Dem_SimilarEventNum                   */
/* Parameters    | [in]  SimilarStrgIndex                                   */
/* Return Value  | Dem_u08_SimilarPendingClearCounterType                   */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_SimilarPendingClearCounterType, DEM_CODE) Dem_CfgInfoPm_GetPendingClearCntThreshold
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex
)
{
    VAR( Dem_u08_SimilarPendingClearCounterType, AUTOMATIC ) threshold;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

    /*  convert eventIndex to eventId.        */
    eventId =   DEM_EVENTID_INVALID;
    eventStrgIndex  =   Dem_CfgInfoPm_CnvSimilarStrgIndexToEventStrgIndex( SimilarStrgIndex );
    (void)Dem_CfgInfoPm_CnvEventStrgIndexToEventId( eventStrgIndex, &eventId ); /* no return check required */

    threshold   =   Dem_Calib_GetSimilarPendingClearCounterThreshold( eventId );

    /*  check output value.     */
    if ( threshold < DEM_CALIB_SIMPENDINGCLEARCYCLECNT_THRESHOLD_MIN )
    {
        threshold   =   DEM_CALIB_SIMPENDINGCLEARCYCLECNT_THRESHOLD_DEF;
    }

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
/*               |         <  DEM_READINESS_DATAPOSITIONTABLE_NUM           */
/*               |              : called from calculation readness.         */
/*               |         == DEM_READINESSDATAPOSITIONINDEX_INVALID        */
/*               |              : called from SID19 sf56.                   */
/*               | [in] ReadinessGroupIndex :                               */
/*               |        Readiness group index.                            */
/* Return Value  | Dem_u16_EventCtrlIndexType                               */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-10-0     | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u16_EventCtrlIndexType, DEM_CODE ) Dem_CfgInfoPm_GetEventNumberOfReadinessGroup
(
    VAR( Dem_u08_ReadinessDataPositionIndexType, AUTOMATIC )    CalcType,
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC )    ReadinessGroupIndex    /* [PRMCHK:CALLER] */
)
{
    VAR( uint16, AUTOMATIC )    eventNumberOfReadinessGroup;
    VAR( Dem_u08_ReadinessGroupIdType, AUTOMATIC )    readinessGroupId;

    readinessGroupId = Dem_CfgInfoPm_CnvReadinessGroupIndexToGroupId( CalcType, ReadinessGroupIndex );  /* [GUDCHK:CALLER]ReadinessGroupIndex */

    if ( readinessGroupId != DEM_READINESSGROUPINDEX_INVALID )
    {
        eventNumberOfReadinessGroup = Dem_Calib_GetEventNumberOfReadinessGroup( readinessGroupId );
    }
    else
    {
        eventNumberOfReadinessGroup = ( uint16 )0U;
    }

    return ( Dem_u16_EventCtrlIndexType )eventNumberOfReadinessGroup;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetEventCtrlIndexOfReadinessGroup          */
/* Description   | Get the EventIndex that belongs to the corresponding re- */
/*               | adiness group.                                           */
/* Preconditions |                                                          */
/* Parameters    | [in]  CalcType :                                         */
/*               |        Calclation Target Type.                           */
/*               |         <  DEM_READINESS_DATAPOSITIONTABLE_NUM           */
/*               |              : called from calculation readness.         */
/*               |         == DEM_READINESSDATAPOSITIONINDEX_INVALID        */
/*               |              : called from SID19 sf56.                   */
/*               | [in] ReadinessGroupIndex :                               */
/*               |        Readiness group index.                            */
/*               |         at called from calculation readness :            */
/*               |           Number of consecutive to Dem_ReadinessDataPositionTable[].ReadinessGrpNum.  */
/*               |         at called from SID19 sf56 :                      */
/*               |           Dem_ReadinessGroupTable[] index.               */
/*               | [in] EventListIndex :                                    */
/*               |        Event List index.                                 */
/* Return Value  | Dem_u16_EventCtrlIndexType                               */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-10-0     | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u16_EventCtrlIndexType, DEM_CODE ) Dem_CfgInfoPm_GetEventCtrlIndexOfReadinessGroup
(
    VAR( Dem_u08_ReadinessDataPositionIndexType, AUTOMATIC )    CalcType,
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC )    ReadinessGroupIndex,   /* [PRMCHK:CALLER] */
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )    EventListIndex
)
{
    VAR( Dem_EventIdType, AUTOMATIC )    eventId;
    VAR( Dem_EventIdType, AUTOMATIC )    eventIdWithCompMask;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )    eventCtrlIndex;
    VAR( Dem_u08_ReadinessGroupIdType, AUTOMATIC )    readinessGroupId;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    readinessGroupId = Dem_CfgInfoPm_CnvReadinessGroupIndexToGroupId( CalcType, ReadinessGroupIndex );  /* [GUDCHK:CALLER]ReadinessGroupIndex */

    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;
    if ( readinessGroupId != DEM_READINESSGROUPINDEX_INVALID )
    {
        eventIdWithCompMask = Dem_Calib_GetEventIdOfReadinessGroup( readinessGroupId, (uint16)EventListIndex );
        eventId  =   eventIdWithCompMask & ~( DEM_CALIB_READINESS_EVT_ALWAYS_COMPLETE | DEM_CALIB_READINESS_EVT_DUPLICATE_DTC );

        retVal = Dem_CfgInfoPm_CnvEventIdToEventCtrlIndex( eventId, &eventCtrlIndex );
        if ( retVal != DEM_IRT_OK )
        {
            eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;
        }
        else
        {
            /*  check always complete event flag.       */
            if (( eventIdWithCompMask & DEM_CALIB_READINESS_EVT_ALWAYS_COMPLETE ) == DEM_CALIB_READINESS_EVT_ALWAYS_COMPLETE )
            {
                eventCtrlIndex  =   eventCtrlIndex | DEM_READINESS_EVT_ALWAYS_COMPLETE;
            }

            if ( CalcType == DEM_READINESSDATAPOSITIONINDEX_INVALID )
            {
                /*------------------------------------------------------------------------------*/
                /*  for output SID19 sf56.                                                      */
                /*  turn ON DEM_READINESS_EVT_DUPLICATEDTC_MARKBIT bit at it has duplicate DTC. */
                /*------------------------------------------------------------------------------*/
                if (( eventIdWithCompMask & DEM_CALIB_READINESS_EVT_DUPLICATE_DTC ) == DEM_CALIB_READINESS_EVT_DUPLICATE_DTC )
                {
                    eventCtrlIndex  =   eventCtrlIndex | DEM_READINESS_EVT_DUPLICATEDTC_MARKBIT;
                }
            }
        }
    }

    return eventCtrlIndex;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_CnvReadinessGroupIndexToGroupId            */
/* Description   | Convert to Readiness Index and Readiness GroupId.        */
/* Preconditions |                                                          */
/* Parameters    | [in]  CalcType :                                         */
/*               |        Calclation Target Type.                           */
/*               |         <  DEM_READINESS_DATAPOSITIONTABLE_NUM           */
/*               |              : call from calculate readness value.       */
/*               |         == DEM_READINESSDATAPOSITIONINDEX_INVALID        */
/*               |              : call from SID19 sf56.                     */
/*               | [in] ReadinessGroupIndex :                               */
/*               |        Readiness group index.                            */
/*               |         at called from calculation readness :            */
/*               |           Number of consecutive to Dem_ReadinessDataPositionTable[].ReadinessGrpNum.  */
/*               |         at called from SID19 sf56 :                      */
/*               |           Dem_ReadinessGroupTable[] index.               */
/* Return Value  | Dem_u08_ReadinessGroupIndexType                          */
/*               |        readinessGroupId.                                 */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-10-0     | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_ReadinessGroupIdType, DEM_CODE ) Dem_CfgInfoPm_CnvReadinessGroupIndexToGroupId
(
    VAR( Dem_u08_ReadinessDataPositionIndexType, AUTOMATIC ) CalcType,
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC ) ReadinessGroupIndex           /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_ReadinessGroupIdType, AUTOMATIC ) readinessGroupId;

    if ( CalcType < DEM_READINESS_DATAPOSITIONTABLE_NUM )                   /* [GUD:if]CalcType */
    {
        /*--------------------------------------------------*/
        /*  at called from calculation readness.            */
        /*--------------------------------------------------*/
        readinessGroupId = Dem_ReadinessDataPositionTable[ CalcType ].ReadinessGrpTblPtr[ ReadinessGroupIndex ].ReadinessGroupId;   /* [GUD]CalcType */ /* [GUDCHK:CALLER]ReadinessGroupIndex *//* [ARYCHK] Dem_ReadinessDataPositionTable[ CalcType ].ReadinessGrpNum / 1 / ReadinessGroupIndex */
    }
    else
    {
        /*--------------------------------------------------*/
        /*  at called from SID19 sf56.                      */
        /*--------------------------------------------------*/
        readinessGroupId = Dem_ReadinessGroupTable[ ReadinessGroupIndex ].ReadinessGroupId;                                         /* [GUDCHK:CALLER]ReadinessGroupIndex */
    }

    return readinessGroupId;
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

    outputPendingOBDFFDWithoutCDTC   =   Dem_JudgeOutputPendingOBDFFDWithoutCDTC();

    if ( outputPendingOBDFFDWithoutCDTC != (boolean)TRUE )
    {
        outputPendingOBDFFDWithoutCDTC =   (boolean)FALSE;
    }

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
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventNum;
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) dtcValue;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;

    eventNum = ( Dem_u16_EventStrgIndexType )0U;

    /* convert EventStrgIndex to EventId. */
    eventId =   DEM_EVENTID_INVALID;
    retTempVal = Dem_CfgInfoPm_CnvEventStrgIndexToEventId( EventStrgIndex, &eventId );

    if( retTempVal == DEM_IRT_OK )
    {
        /* get DTCValue by eventId. */
        dtcValue = Dem_Calib_GetUdsDTCValue( eventId );

        /* get EventStrgIndex by DTCValue. */
        eventNum = ( Dem_u16_EventStrgIndexType )Dem_Calib_GetEventNumberOfSameDTC( dtcValue );
    }

    return eventNum;
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
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( Dem_EventIdType, AUTOMATIC ) nextEventId;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) nextEventStrgIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;

    nextEventStrgIndex = EventStrgIndex;
    eventId = DEM_EVENTID_INVALID;
    eventCtrlndex = DEM_EVENTCTRLINDEX_INVALID;

    /* convert EventStrgIndex to EventId. */
    retTempVal = Dem_CfgInfoPm_CnvEventStrgIndexToEventId( EventStrgIndex, &eventId );

    if( retTempVal == DEM_IRT_OK )
    {
        /* get nextEventId */
        nextEventId = Dem_Calib_GetNextEventIdOfSameDTC( eventId );

        /* convert EventId to EventCtrlIndex. */
        retTempVal = Dem_CfgInfoPm_CnvEventIdToEventCtrlIndex( nextEventId, &eventCtrlndex );

        if( retTempVal == DEM_IRT_OK )
        {
            /* convert EventCtrlIndex to EventStrgIndex. */
            nextEventStrgIndex = Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlndex );
        }
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
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( boolean, AUTOMATIC ) bDelegate;

    /* convert EventStrgIndex to EventId. */
    eventId =   DEM_EVENTID_INVALID;

    (void)Dem_CfgInfoPm_CnvEventStrgIndexToEventId( EventStrgIndex, &eventId ); /* no return check required */  /* [GUDCHK:CALLER]EventStrgIndex */

    bDelegate  =   Dem_Calib_CheckDelegateEventIdOfSameDTC( eventId );

    return bDelegate;
}

#endif  /* ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif  /* ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
