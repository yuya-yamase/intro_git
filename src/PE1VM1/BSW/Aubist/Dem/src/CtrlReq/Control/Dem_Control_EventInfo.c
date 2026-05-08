/* Dem_Control_EventInfo_c(v5-9-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_EventInfo/CODE                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "../../../inc/Dem_Pm_Event.h"
#include "../../../inc/Dem_Pm_Similar.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Rc_OdrLst.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "Dem_Control_local.h"

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
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Unit External functions                                                  */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* Function Name | Dem_Control_GetEventCtrlIndexFromEventId                 */
/* Description   | Gets an event index by event ID.                         */
/* Preconditions | The specified event ID has been already registered.      */
/* Parameters    | [in] EventID :                                           */
/*               |        The event ID for retrieving.                      */
/*               | [out] EventCtrlIndexPtr :                                */
/*               |        The event index which has been retrieved.         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The event index retrieving is succe- */
/*               |        ssful.                                            */
/*               |        DEM_IRT_NG : The event index retrieving is faile- */
/*               |        d.                                                */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] EventCtrlIndexPtr                   */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetEventCtrlIndexFromEventId
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventID,
    P2VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC, AUTOMATIC ) EventCtrlIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retConvertEventId;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( boolean, AUTOMATIC ) availableStatus;

    /* Initializes. */
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;

    /* Gets event index */
    retConvertEventId = Dem_CfgInfoPm_CnvEventIdToEventCtrlIndex( EventID, &eventCtrlIndex );

    if( retConvertEventId == DEM_IRT_OK )
    {
        /* Gets event available status */
        availableStatus = Dem_DataAvl_GetEvtAvl( eventCtrlIndex );

        if( availableStatus == (boolean)TRUE )
        {
            *EventCtrlIndexPtr = eventCtrlIndex;
            retVal = DEM_IRT_OK;
        }
        else
        {
            retVal = DEM_IRT_NG;
        }
    }
    else
    {
        retVal = DEM_IRT_NG;
    }

    /* Returns with the result. */
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_GetStatusOfDTC                               */
/* Description   | Gets status of DTC by DTC from event record.             */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCValue :                                          */
/*               |        Diagnostic Trouble Code in UDS format             */
/*               | [in] DTCOrigin :                                         */
/*               |        select the source memory the DTCs shall be read - */
/*               |        from                                              */
/*               | [out] DTCStatusPtr :                                     */
/*               |        the status information of the requested DTC       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Status of DTC is OK                  */
/*               |        DEM_IRT_WRONG_DTC : DTC value not existing (in t- */
/*               |        his format)                                       */
/*               |        DEM_IRT_WRONG_DTCORIGIN : Wrong DTC origin        */
/*               |        DEM_IRT_NG : DTC failed                           */
/*               |                                                          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | refactor function.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetStatusOfDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;

    retTempVal = Dem_Control_CheckDisableDTCInfo( DTCValue, DTCOrigin );
    if( retTempVal == DEM_IRT_OK )
    {
        *DTCStatusPtr   =   Dem_Data_GetDTCStatusOfDisabledRecord();
        retVal = DEM_IRT_OK;
    }
    else
    {
        retVal  =   Dem_DTC_GetDTCStatusByUdsDTC( DTCValue, DTCStatusPtr );
    }

    /*------------------------------------------*/
    /*  convert to output statusOfDTC.          */
    /*------------------------------------------*/
    (*DTCStatusPtr) =   Dem_DTC_CnvDTCStatus_PmAvailabilityMask( (*DTCStatusPtr) );

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_GetHealingCounter                            */
/* Description   | Gets the current healing counter of an event.            */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        Identification of an event by assigned EventId    */
/*               | [out] HealingCounterPtr :                                */
/*               |        Pointer to the area to get counter.               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : get of counter was successful        */
/*               |        DEM_IRT_NG : get of counter failed                */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_Control_GetAgingCounter.       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetHealingCounter
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventID,
    P2VAR( Dem_u08_HealingCounterType, AUTOMATIC, AUTOMATIC ) HealingCounterPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u08_HealingCounterType, AUTOMATIC ) healingCounter;
#if ( DEM_INDICATOR_USE == STD_ON ) /*  [FuncSw]    */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetHealingCounter;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( boolean, AUTOMATIC ) isActiveFault;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_HealingCounterType, AUTOMATIC ) healingCounterThreshold;
#endif  /* ( DEM_INDICATOR_USE == STD_ON )  */

    retVal = DEM_IRT_NG;
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;
    healingCounter = DEM_HEALING_COUNT_INITIAL_VALUE;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        retTempVal = Dem_Control_GetEventCtrlIndexFromEventId( EventID, &eventCtrlIndex );                               /* [GUD:RET:DEM_IRT_OK] eventCtrlIndex */
        if( retTempVal == DEM_IRT_OK )
        {
#if ( DEM_INDICATOR_USE == STD_ON ) /*  [FuncSw]    */
            eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );    /* [GUD]eventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ] eventStrgIndex */
            isActiveFault   =   Dem_CfgInfoPm_GetIsActiveFault( eventStrgIndex );                   /* [GUD]eventStrgIndex */

            if( isActiveFault == (boolean)TRUE )
            {
                /*  healing used.               */
                /*--------------------------------------------------------------------------*/
                /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
                /* These are the reasons why this function needs to get exclusive.          */
                /*  - This function call [DataMng] function directory.                      */
                /*  - This function called from SW-C/Dcm context.                           */
                /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
                SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
                SchM_Exit_Dem_EventMemory();
                /*--------------------------------------------------------------------------*/

                (void)Dem_DataMngC_GetER_FaultIndex( eventStrgIndex, &faultIndex );     /* no return check required */      /* [GUD] eventStrgIndex */
                retGetHealingCounter     = Dem_DataMngC_GetFR_HealingCounter( faultIndex, &healingCounter );
                if( retGetHealingCounter != DEM_IRT_OK )
                {
                    /*  there is no Healing counter.       */
                    healingCounter = DEM_HEALING_COUNT_INITIAL_VALUE;
                }
                else
                {
                    /*  check threshold     */
                    healingCounterThreshold =   Dem_CfgInfoPm_GetHealingThreshold( eventStrgIndex );
                    if( healingCounter > healingCounterThreshold )
                    {
                        healingCounter  =   healingCounterThreshold;
                    }
                }
            }
#endif  /* ( DEM_INDICATOR_USE == STD_ON )  */

            *HealingCounterPtr    =   healingCounter;

            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_GetAgingCounter                              */
/* Description   | Gets the current aging counter of an event.              */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        Identification of an event by assigned EventId    */
/*               | [out] AgingCounterPtr :                                  */
/*               |        Pointer to the area to get counter.               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : get of counter was successful        */
/*               |        DEM_IRT_NG : get of counter failed                */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetAgingCounter
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventID,
    P2VAR( Dem_u08_AgingCounterType, AUTOMATIC, AUTOMATIC ) AgingCounterPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetAgingCounter;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC )   extendStatusOfDTC2;
    VAR( Dem_u08_AgingCounterType, AUTOMATIC ) agingCounter;
    VAR( Dem_u08_AgingCounterType, AUTOMATIC ) agingCounterThreshold;
    VAR( boolean, AUTOMATIC ) agingAllowed;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;

    retVal = DEM_IRT_NG;
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        retTempVal = Dem_Control_GetEventCtrlIndexFromEventId( EventID, &eventCtrlIndex );                               /* [GUD:RET:DEM_IRT_OK] eventCtrlIndex */
        if( retTempVal == DEM_IRT_OK )
        {
            eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );    /* [GUD]eventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ] eventStrgIndex */
            agingAllowed    =   Dem_CfgInfoPm_GetAgingAllowed( eventStrgIndex );                    /* [GUD]eventStrgIndex */

            if ( agingAllowed == (boolean)FALSE )
            {
                /*  aging is not allowed.           */
                agingCounter = DEM_AGING_COUNT_INITIAL_VALUE;
            }
            else
            {
                /*  aging is allowed.               */
                /*--------------------------------------------------------------------------*/
                /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
                /* These are the reasons why this function needs to get exclusive.          */
                /*  - This function call [DataMng] function directory.                      */
                /*  - This function called from SW-C/Dcm context.                           */
                /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
                SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
                SchM_Exit_Dem_EventMemory();
                /*--------------------------------------------------------------------------*/

                agingCounter = DEM_AGING_COUNT_INITIAL_VALUE;
                (void)Dem_DataMngC_GetER_FaultIndex( eventStrgIndex, &faultIndex );     /* no return check required */      /* [GUD] eventStrgIndex */

                agingCounterThreshold   = Dem_CfgInfoPm_GetAgingCycleThreshold( eventStrgIndex );
                retGetAgingCounter      = Dem_DataMngC_GetFR_AgingCounter( faultIndex, &agingCounter );
                if( retGetAgingCounter != DEM_IRT_OK )
                {
                    /*  get extendStatusOfDTC.      */
                    (void)Dem_DataMngC_GetER_ExtendDTCStatus2( eventStrgIndex, &extendStatusOfDTC2 );   /* no return check required */ /* [GUD] eventStrgIndex */

                    if (( extendStatusOfDTC2 & DEM_DTCSTATUSEX2_STATUS_AGING_HISTORY ) == DEM_DTCSTATUSEX2_STATUS_AGING_HISTORY )
                    {
                        /*  there is Aging history.  get AgingCycleThreshold.    */
                        agingCounter = agingCounterThreshold;
                    }
                    else
                    {
                        /*  there is no Aging history.       */
                        agingCounter = DEM_AGING_COUNT_INITIAL_VALUE;
                    }
                }
                else
                {
                    if ( agingCounter > agingCounterThreshold )
                    {
                        agingCounter = agingCounterThreshold;
                    }
                }
            }
            *AgingCounterPtr    =   agingCounter;

            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_GetAgingTime                                 */
/* Description   | Gets the current aging counter of an event.              */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        Identification of an event by assigned EventId    */
/*               | [out] AgingTimePtr :                                     */
/*               |        Pointer to the area to get time.                  */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : get of counter was successful        */
/*               |        DEM_IRT_NG : get of counter failed                */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created. based on Dem_Control_GetAgingCounter.       */
/*   v5-9-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetAgingTime
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventID,
    P2VAR( Dem_u16_WWHOBDTimeAgingCounterType, AUTOMATIC, AUTOMATIC ) AgingTimePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetAgingTime;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC )   extendStatusOfDTC2;
    VAR( Dem_u16_WWHOBDTimeAgingCounterType, AUTOMATIC ) agingTime;
    VAR( Dem_u16_WWHOBDTimeAgingCounterType, AUTOMATIC ) agingTimeThreshold;
    VAR( boolean, AUTOMATIC ) agingAllowed;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;

    retVal = DEM_IRT_NG;
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        retTempVal = Dem_Control_GetEventCtrlIndexFromEventId( EventID, &eventCtrlIndex );                               /* [GUD:RET:DEM_IRT_OK] eventCtrlIndex */
        if( retTempVal == DEM_IRT_OK )
        {
            eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );    /* [GUD]eventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ] eventStrgIndex */
            agingAllowed    =   Dem_CfgInfoPm_GetAgingAllowed( eventStrgIndex );                    /* [GUD]eventStrgIndex */

            if ( agingAllowed == (boolean)FALSE )
            {
                /*  aging is not allowed.           */
                agingTime = DEM_TIME_AGING_COUNT_INITIAL_VALUE;
            }
            else
            {
                /*  aging is allowed.               */
                /*--------------------------------------------------------------------------*/
                /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
                /* These are the reasons why this function needs to get exclusive.          */
                /*  - This function call [DataMng] function directory.                      */
                /*  - This function called from SW-C/Dcm context.                           */
                /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
                SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
                SchM_Exit_Dem_EventMemory();
                /*--------------------------------------------------------------------------*/

                agingTime = DEM_TIME_AGING_COUNT_INITIAL_VALUE;
                (void)Dem_DataMngC_GetER_FaultIndex( eventStrgIndex, &faultIndex );     /* no return check required */      /* [GUD] eventStrgIndex */

                agingTimeThreshold   = Dem_CfgInfoPm_GetTimeAgingCounterThreshold();
                retGetAgingTime      = Dem_DataMngC_GetFR_AgingTime( faultIndex, &agingTime );
                if( retGetAgingTime != DEM_IRT_OK )
                {
                    /*  get extendStatusOfDTC.      */
                    (void)Dem_DataMngC_GetER_ExtendDTCStatus2( eventStrgIndex, &extendStatusOfDTC2 );   /* no return check required */ /* [GUD] eventStrgIndex */

                    if (( extendStatusOfDTC2 & DEM_DTCSTATUSEX2_STATUS_AGING_HISTORY ) == DEM_DTCSTATUSEX2_STATUS_AGING_HISTORY )
                    {
                        /*  there is Aging history.  get AgingCycleThreshold.    */
                        agingTime = agingTimeThreshold;
                    }
                    else
                    {
                        /*  there is no Aging history.       */
                        agingTime = DEM_TIME_AGING_COUNT_INITIAL_VALUE;
                    }
                }
                else
                {
                    if ( agingTime > agingTimeThreshold )
                    {
                        agingTime = agingTimeThreshold;
                    }
                }
            }
            *AgingTimePtr    =   agingTime;

            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON )    */

#if ( DEM_OBD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_GetEventKind                                 */
/* Description   | Get the EventKind of specified event.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        Identification of an event by assigned EventId    */
/*               | [out] EventKindPtr :                                     */
/*               |        Pointer to the area to get Event Kind.            */
/*               | [out] DTCClassPtr :                                      */
/*               |        Pointer to the area to get DTCClass.              */
/*               | [out] IsMILIndicatorPtr :                                */
/*               |        Pointer to the area to get MIL flag exist.        */
/*               |        When it Event Use "MIL" Ind, TRUE is set.         */
/*               |        When it Event no Use "MIL"Ind, FALSE is set.      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : get of EventKind was successful      */
/*               |        DEM_IRT_NG : get of EventKind failed              */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetEventKind
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_EventKindType, AUTOMATIC, AUTOMATIC ) EventKindPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCClassPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) IsMILIndicatorPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retResult;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( boolean, AUTOMATIC ) eventOBDKind;
    VAR( Dem_DTCSeverityType, AUTOMATIC ) dtcClass;
    VAR( boolean, AUTOMATIC ) isMILIndicator;
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_EventKindType, AUTOMATIC ) eventKindSpec;
#endif  /*  ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )            */

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) usedExceedance;
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */

    retVal = DEM_IRT_NG;


    /* Check After Dem_Init */
    checkStatus = Dem_Control_ChkAfterInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /* Get eventCtrlIndex */
        retResult = Dem_Control_GetEventCtrlIndexFromEventId( EventId, &eventCtrlIndex );                               /* [GUD:RET:DEM_IRT_OK] eventCtrlIndex */

        /* If the Event is Within Range */
        if( retResult == DEM_IRT_OK )
        {
            dtcClass        =   DEM_DTC_CLASS_0;
            isMILIndicator  =   (boolean)FALSE;

            /* OBD or NonOBD event Judgment */
            eventOBDKind    =   Dem_CfgInfoPm_GetEventKindOfOBD_ByEvtCtrlIdx( eventCtrlIndex, &dtcClass, &isMILIndicator ); /* [GUD] eventCtrlIndex */
            if( eventOBDKind == (boolean)TRUE ) /*  OBD     */
            {
                /* OBD */
                eventKind   =   DEM_EVTKIND_TYPE_OBD_EVENT;

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )    /*  [FuncSw]    */
                eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );

            /*  Get Specific Event kind.        */
                eventKindSpec  =   Dem_CfgInfoPm_GetEventKindOfSpecific_InEvtStrgGrp( eventStrgIndex );
                eventKind      |=   eventKindSpec;

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                /* Similar event ExceedanceUsed Judgment */
                usedExceedance =  Dem_Similar_CheckExceedanceUsed( eventStrgIndex );
                if( usedExceedance == (boolean)TRUE ) /*  ExceedanceUsed */
                {
                    eventKind |= DEM_EVTKIND_TYPE_MISFIRE_EVENT;
                }
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */

#endif  /*  ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )            */
            }
            else
            {
                /* NonOBD */
                eventKind   =   DEM_EVTKIND_TYPE_NON_OBD_EVENT;
            }

            /* Return to DEM_IRT_OK for event within Range */
            *IsMILIndicatorPtr = isMILIndicator;
            *DTCClassPtr    =   dtcClass;
            *EventKindPtr   =   eventKind;
            retVal = DEM_IRT_OK;

        }
        else
        {
            /* Out of Range Events */
            /* No process */
        }
    }
    else
    {
        /* No process */
    }
    return retVal;
}
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */

/****************************************************************************/
/* Function Name | Dem_Control_GetFaultOccurrenceDTCOrder                   */
/* Description   | Get the order of Fault occurrence DTC.                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        Identification of an event by assigned EventId    */
/*               | [out] OrderPtr :                                         */
/*               |        Pointer to the area to get order.                 */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : get of order was successful          */
/*               |        DEM_IRT_NG : get of order failed                  */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.based on Dem_Control_GetConfirmedDTCOrder.   */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetFaultOccurrenceDTCOrder
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_u16_OccrOrderType, AUTOMATIC, AUTOMATIC ) OrderPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retResult;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;

    retVal = DEM_IRT_NG;
    failRecordNum = Dem_FailRecordNum;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /* Get eventCtrlIndex */
        retResult = Dem_Control_GetEventCtrlIndexFromEventId( EventId, &eventCtrlIndex );                               /* [GUD:RET:DEM_IRT_OK] eventCtrlIndex */

        /* If the Event is Within Range */
        if( retResult == DEM_IRT_OK )
        {
            SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
            SchM_Exit_Dem_EventMemory();

            eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );
            retResult = Dem_DataMngC_GetER_FaultIndex( eventStrgIndex, &faultIndex );               /* [GUD:RET:DEM_IRT_OK] eventStrgIndex */
            if( retResult == DEM_IRT_OK )
            {
                *OrderPtr = DEM_FAIL_OCCURRENCE_NUM_INVALID;

                if( faultIndex < failRecordNum )                                            /* [GUD:if] FaultIndex */
                {
                    Dem_OdrLst_Fault_GetOrderByFaultIndex( faultIndex, OrderPtr );
                }
                retVal = DEM_IRT_OK;
            }

        }
    }

    return retVal;
}

#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_GetConfirmedDTCOrder                         */
/* Description   | Get the order of ConfirmedDTC.                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        Identification of an event by assigned EventId    */
/*               | [out] OrderPtr :                                         */
/*               |        Pointer to the area to get order.                 */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : get of order was successful          */
/*               |        DEM_IRT_NG : get of order failed                  */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetConfirmedDTCOrder
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_u16_OccrOrderType, AUTOMATIC, AUTOMATIC ) OrderPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retResult;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;

    retVal = DEM_IRT_NG;
    failRecordNum = Dem_FailRecordNum;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /* Get eventCtrlIndex */
        retResult = Dem_Control_GetEventCtrlIndexFromEventId( EventId, &eventCtrlIndex );                               /* [GUD:RET:DEM_IRT_OK] eventCtrlIndex */

        /* If the Event is Within Range */
        if( retResult == DEM_IRT_OK )
        {
            SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
            SchM_Exit_Dem_EventMemory();

            eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );
            retResult = Dem_DataMngC_GetER_FaultIndex( eventStrgIndex, &faultIndex );               /* [GUD:RET:DEM_IRT_OK] eventStrgIndex */
            if( retResult == DEM_IRT_OK )
            {
                *OrderPtr = DEM_FAIL_OCCURRENCE_NUM_INVALID;

                if( faultIndex < failRecordNum )                                            /* [GUD:if] FaultIndex */
                {
                    Dem_OdrLst_Confirmed_GetOrderByFaultIndex( faultIndex, OrderPtr );
                }
                retVal = DEM_IRT_OK;
            }

        }
    }

    return retVal;
}

#endif  /* ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )    */

/****************************************************************************/
/* Function Name | Dem_Control_GetActiveFault                               */
/* Description   | Gets the current aging counter of an event.              */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [out] ActiveFaultPtr :                                   */
/*               |        Pointer to the area to get active fault data.     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        E_OK      : success.                              */
/*               |        E_NOT_OK  : failed.                               */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetActiveFault
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ActiveFaultPtr
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC )    extendStatusOfDTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetEventCtrlIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) activeFault;
    VAR( boolean, AUTOMATIC ) isActiveFault;

    retVal      =   DEM_IRT_NG;
    activeFault =   (boolean)FALSE;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;
        retGetEventCtrlIndex = Dem_Control_GetEventCtrlIndexFromEventId( EventId, &eventCtrlIndex );                               /* [GUD:RET:DEM_IRT_OK] eventCtrlIndex */
        if( retGetEventCtrlIndex == DEM_IRT_OK )
        {
            /*  get active fault status.        */
            eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );
            isActiveFault    =   Dem_CfgInfoPm_GetIsActiveFault( eventStrgIndex );
            if( isActiveFault == (boolean)TRUE )
            {
                /*--------------------------------------------------------------------------*/
                /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
                /* These are the reasons why this function needs to get exclusive.          */
                /*  - This function call [DataMng] function directory.                      */
                /*  - This function called from SW-C/Dcm context.                           */
                /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
                SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
                SchM_Exit_Dem_EventMemory();
                /*--------------------------------------------------------------------------*/

                extendStatusOfDTC   =   DEM_DTCSTATUSEX_BYTE_ALL_OFF;
                (void)Dem_DataMngC_GetER_ExtendDTCStatus( eventStrgIndex, &extendStatusOfDTC ); /* no return check required */
                if (( extendStatusOfDTC & DEM_DTCSTATUSEX_STATUS_INDICATOR ) == DEM_DTCSTATUSEX_STATUS_INDICATOR )
                {
                    activeFault =   (boolean)TRUE;
                }
            }
            retVal = DEM_IRT_OK;
        }
    }


    *ActiveFaultPtr =   activeFault;
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_GetEventFailureCycleCounter                  */
/* Description   | Gets the current failure cycle counter of an event.      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [out] FailureCounterPtr :                                */
/*               |        Pointer to the area to get failure cycle counter. */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful             */
/*               |        DEM_IRT_NG : Operation failed                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_Control_GetAgingCounter.       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetEventFailureCycleCounter
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_u08_FailureCounterType, AUTOMATIC, AUTOMATIC ) FailureCounterPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetEventCtrlIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetFailureCounter;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_FailureCounterType, AUTOMATIC ) failureCounter;
    VAR( Dem_u08_FailureCounterType, AUTOMATIC ) failureCounterThreshold;

    retVal = DEM_IRT_NG;
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;
    failureCounter = DEM_FAILURECYCLE_COUNT_INITIAL_VALUE;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /*  Get eventCtrlIndex.  */
        /*  Check it's primary memory event and available.  */
        retGetEventCtrlIndex = Dem_Control_GetEventCtrlIndexFromEventId( EventId, &eventCtrlIndex );                               /* [GUD:RET:DEM_IRT_OK] eventCtrlIndex */
        if( retGetEventCtrlIndex == DEM_IRT_OK )
        {
            eventStrgIndex = Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );

            /*--------------------------------------------------------------------------*/
            /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
            /* These are the reasons why this function needs to get exclusive.          */
            /*  - This function call [DataMng] function directory.                      */
            /*  - This function called from SW-C/Dcm context.                           */
            /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
            SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
            SchM_Exit_Dem_EventMemory();
            /*--------------------------------------------------------------------------*/

            /*  Get failure cycle counter.  */
            failureCounterThreshold = Dem_Event_GetEventFailureCycleCounterThreshold( eventStrgIndex );
            retGetFailureCounter = Dem_DataMngC_GetER_FailureCounter( eventStrgIndex, &failureCounter );
            if( retGetFailureCounter == DEM_IRT_OK )
            {
                if ( failureCounter > failureCounterThreshold )
                {
                    failureCounter = failureCounterThreshold;
                }
                *FailureCounterPtr = failureCounter;
                retVal = DEM_IRT_OK;
            }
        }
    }

    return retVal;
}

#if ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_GetEventOccurrenceCounter                    */
/* Description   | Gets the current occurrence counter of an event.         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [out] OccurrenceCounterPtr :                             */
/*               |        Pointer to the area to get occurrence counter.    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful             */
/*               |        DEM_IRT_NG : Operation failed                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_Control_GetAgingCounter.       */
/*   v5-9-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetEventOccurrenceCounter
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_u08_EventOccurrenceCounterType, AUTOMATIC, AUTOMATIC ) OccurrenceCounterPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetEventCtrlIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetOccurrenceCounter;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_EventOccurrenceCounterType, AUTOMATIC ) occurrenceCounter;

    retVal = DEM_IRT_NG;
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;
    occurrenceCounter = DEM_EVENT_OCCURRENCE_COUNT_INITIAL_VALUE;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /*  Get eventCtrlIndex.  */
        /*  Check it's primary memory event and available.  */
        retGetEventCtrlIndex = Dem_Control_GetEventCtrlIndexFromEventId( EventId, &eventCtrlIndex );                               /* [GUD:RET:DEM_IRT_OK] eventCtrlIndex */
        if( retGetEventCtrlIndex == DEM_IRT_OK )
        {
            eventStrgIndex = Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );

            /*--------------------------------------------------------------------------*/
            /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
            /* These are the reasons why this function needs to get exclusive.          */
            /*  - This function call [DataMng] function directory.                      */
            /*  - This function called from SW-C/Dcm context.                           */
            /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
            SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
            SchM_Exit_Dem_EventMemory();
            /*--------------------------------------------------------------------------*/

            /*  Get event occurrence counter.   */
            retGetOccurrenceCounter = Dem_DataMngC_GetER_OccurrenceCounter( eventStrgIndex, &occurrenceCounter );
            if( retGetOccurrenceCounter == DEM_IRT_OK )
            {
                /*  Check the range of the event occurrence counter.    */
                if( occurrenceCounter > DEM_EVENT_OCCURRENCE_COUNT_MAX_VALUE )
                {
                    /*  If it's out of the range, the upper limit is output.    */
                    occurrenceCounter = DEM_EVENT_OCCURRENCE_COUNT_MAX_VALUE;
                }
                *OccurrenceCounterPtr = occurrenceCounter;
                retVal = DEM_IRT_OK;
            }
        }
    }

    return retVal;
}
#endif  /* ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )   */

/****************************************************************************/
/* Function Name | Dem_Control_GetEventIdListByFaultRecordOrder             */
/* Description   | Get EventList by order.                                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        Identification of an event by assigned EventId    */
/*               | [out] OrderPtr :                                         */
/*               |        Pointer to the area to get order.                 */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : get of order was successful          */
/*               |        DEM_IRT_NG : get of order failed                  */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_Control_SearchFaultOrderedPriorityOBDFreezeFrame. */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetEventIdListByFaultRecordOrder
(
    VAR( Dem_u08_EventListModeType, AUTOMATIC ) EventListMode,
    P2VAR( Dem_EventIdType, AUTOMATIC, DEM_APPL_DATA ) EventIdBufferPtr,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdNumPtr
)
{
    VAR( Dem_DTCStatusStType, AUTOMATIC ) dtcStatusSt;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_EventIdType, AUTOMATIC ) eventIdCnt;
    VAR( Dem_EventIdType, AUTOMATIC ) eventIdMax;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndex;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( boolean, AUTOMATIC ) orderExistFlag;
    VAR( boolean, AUTOMATIC ) targetDataFlag;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

    eventIdCnt          =   (Dem_EventIdType)0U;
    eventIdMax          =   *EventIdNumPtr;

    retVal = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        if ( eventIdMax > (Dem_EventIdType)0U )
        {
            SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
            SchM_Exit_Dem_EventMemory();

            eventStorageNum =   Dem_PrimaryMemEventStorageNum;
            failRecordNum   =   (Dem_u08_OrderIndexType)Dem_FailRecordNum;

            for( orderListIndex = (Dem_u08_OrderIndexType)0U; orderListIndex < failRecordNum; orderListIndex++ )
            {
                eventStrgIndex  = DEM_EVENTSTRGINDEX_INVALID;
                dtcStatusSt.DTCStatus        = DEM_DTCSTATUS_BYTE_ALL_OFF;
                dtcStatusSt.ExtendDTCStatus  = DEM_DTCSTATUS_BYTE_ALL_OFF;
                dtcStatusSt.ExtendDTCStatus2 = DEM_DTCSTATUS_BYTE_ALL_OFF;

                /*  get data from order list.       */
                Dem_Data_GetFaultOrderEventStrgIndex( orderListIndex, &eventStrgIndex, &faultIndex, &dtcStatusSt, &orderExistFlag );

                if( orderExistFlag == (boolean)TRUE )
                {
                    if( eventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]eventStrgIndex */
                    {
                        targetDataFlag  =   (boolean)FALSE;

                        retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToEventId( eventStrgIndex, &eventId );               /* [GUD]eventStrgIndex */
                        if ( retCnvId == DEM_IRT_OK )
                        {
                            if ( EventListMode == DEM_EVTLSTMODE_PDTC )
                            {
                                /*  target : PDTC           */
                                if( ( dtcStatusSt.DTCStatus & DEM_UDS_STATUS_PDTC ) == DEM_UDS_STATUS_PDTC )
                                {
                                    targetDataFlag  =   (boolean)TRUE;
                                }
                            }
                            else if ( EventListMode == DEM_EVTLSTMODE_ACTIVEFAULT )
                            {
                                /*  target : ActiveFault    */
                                if( ( dtcStatusSt.ExtendDTCStatus & DEM_DTCSTATUSEX_STATUS_INDICATOR ) == DEM_DTCSTATUSEX_STATUS_INDICATOR )
                                {
                                    targetDataFlag  =   (boolean)TRUE;
                                }
                            }
                            else
                            {
                                /*  no mode.    */
                            }
                        }

                        if ( targetDataFlag == (boolean)TRUE )
                        {
                            /*  store data.     */
                            EventIdBufferPtr[ eventIdCnt ]  =   eventId;                        /* [GUD]eventIdCnt *//* [ARYCHK] *EventIdNumPtr / 1 / eventIdCnt */
                            eventIdCnt  =   eventIdCnt + ( Dem_u16_EventStrgIndexType )1U;
                            if ( eventIdCnt >= eventIdMax )                                     /* [GUD:if]eventIdCnt */
                            {
                                /*  limit of buffer.    */
                                break;
                            }
                        }
                    }
                }
            }
        }
        /*  set data number.        */
        *EventIdNumPtr  =   eventIdCnt;
        retVal          =   DEM_IRT_OK;
    }

    return retVal;
}

#if ( DEM_OBD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_GetEventIdListByConfirmedOrder               */
/* Description   | Get EventList by order.                                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        Identification of an event by assigned EventId    */
/*               | [out] OrderPtr :                                         */
/*               |        Pointer to the area to get order.                 */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : get of order was successful          */
/*               |        DEM_IRT_NG : get of order failed                  */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetEventIdListByConfirmedOrder
(
    P2VAR( Dem_EventIdType, AUTOMATIC, DEM_APPL_DATA ) EventIdBufferPtr,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdNumPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( Dem_EventIdType, AUTOMATIC ) eventIdCnt;
    VAR( Dem_EventIdType, AUTOMATIC ) eventIdMax;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndex;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( boolean, AUTOMATIC ) orderExistFlag;
    VAR( boolean, AUTOMATIC ) targetDataFlag;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

    eventIdCnt          =   (Dem_EventIdType)0U;
    eventIdMax          =   *EventIdNumPtr;

    retVal = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        if ( eventIdMax > (Dem_EventIdType)0U )
        {
            SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
            SchM_Exit_Dem_EventMemory();

            eventStorageNum =   Dem_PrimaryMemEventStorageNum;
            failRecordNum   =   (Dem_u08_OrderIndexType)Dem_FailRecordNum;

            for( orderListIndex = (Dem_u08_OrderIndexType)0U; orderListIndex < failRecordNum; orderListIndex++ )
            {
                eventStrgIndex  = DEM_EVENTSTRGINDEX_INVALID;
                statusOfDTC     = DEM_DTCSTATUS_BYTE_ALL_OFF;

                /*  get data from order list.       */
                Dem_Data_GetConfirmedOrderEventStrgIndex( orderListIndex, &eventStrgIndex, &faultIndex, &statusOfDTC, &orderExistFlag );

                if( orderExistFlag == (boolean)TRUE )
                {
                    if( eventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]eventStrgIndex */
                    {
                        targetDataFlag  =   (boolean)FALSE;

                        /*  target : CDTC           */
                        if( ( statusOfDTC & DEM_UDS_STATUS_CDTC ) == DEM_UDS_STATUS_CDTC )
                        {
                            targetDataFlag  =   (boolean)TRUE;
                        }

                        if ( targetDataFlag == (boolean)TRUE )
                        {
                            retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToEventId( eventStrgIndex, &eventId );               /* [GUD]eventStrgIndex */
                            if ( retCnvId == DEM_IRT_OK )
                            {
                                /*  store data.     */
                                EventIdBufferPtr[ eventIdCnt ]  =   eventId;                        /* [GUD]eventIdCnt *//* [ARYCHK] *EventIdNumPtr / 1 / eventIdCnt */
                                eventIdCnt  =   eventIdCnt + ( Dem_u16_EventStrgIndexType )1U;
                                if ( eventIdCnt >= eventIdMax )                                     /* [GUD:if]eventIdCnt */
                                {
                                    /*  limit of buffer.    */
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        /*  set data number.        */
        *EventIdNumPtr  =   eventIdCnt;
        retVal          =   DEM_IRT_OK;
    }

    return retVal;
}
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */


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
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
