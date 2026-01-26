/* Dem_Control_ClearPrimary_c(v5-5-0)                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_ClearPrimary/CODE                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_CmnLib_OpCycle.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_Pm_DTC_PFC.h"
#include "../../../inc/Dem_Pm_DTR.h"
#include "../../../inc/Dem_Pm_Ind.h"
#include "../../../inc/Dem_Pm_Ind_MI.h"
#include "../../../inc/Dem_Pm_PID.h"
#include "../../../inc/Dem_Pm_OccrDTC.h"
#include "../../../inc/Dem_Pm_MonSts.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"

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

static FUNC( void, DEM_CODE ) Dem_Control_ClearOrderList
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetNextEventStrgIndexByDTCsForClearDTC
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) BaseEventStrgIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) NextEventStrgIndexPtr
);
static FUNC( void, DEM_CODE ) Dem_Control_TriggerInitMForEFnc_Clear
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

static VAR( Dem_u16_EventStrgIndexType, DEM_VAR_NO_INIT )       Dem_CtlClearEventStrgIndex;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Control_StartClearDTC_PrimaryMemory                  */
/* Description   | Start of ClearDTC in PrimaryMemory.                      */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_StartClearDTC_PrimaryMemory
( void )
{
    Dem_CtlClearEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
    return ;
}

/****************************************************************************/
/* Function Name | Dem_Control_ClearRAM_PrimaryMemory                       */
/* Description   | Clears RAM data.                                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCGroup                                            */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK                                      */
/*               |          DEM_IRT_PENDING                                 */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_ClearRAM_PrimaryMemory
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) clearDTC;
    VAR( Dem_u16_AdjustCntByEventNumType, AUTOMATIC ) loopCount;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) nextEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
    VAR( Dem_u16_AdjustCntByEventNumType, AUTOMATIC ) controlClearRamEventNumByCycle;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( boolean, AUTOMATIC ) clearAllowed;

    clearDTC = DTCGroup;
    controlClearRamEventNumByCycle = Dem_ControlClearRamEventNumByCycle;

    retVal  =   DEM_IRT_PENDING;

    for( loopCount = (Dem_u16_AdjustCntByEventNumType)0U; loopCount < controlClearRamEventNumByCycle; loopCount++ )
    {
        retTempVal = Dem_Control_GetNextEventStrgIndexByDTCsForClearDTC( clearDTC, Dem_CtlClearEventStrgIndex, &nextEventStrgIndex );
        if( retTempVal == DEM_IRT_OK )
        {
            /* When event index of clear target is obtained successfully */
            Dem_CtlClearEventStrgIndex = nextEventStrgIndex;

            clearAllowed = Dem_CfgInfoPm_ClearAllowed_InEvtStrgGrp( Dem_CtlClearEventStrgIndex );
            if( clearAllowed == (boolean)TRUE )
            {
                /* Clear the specified data */
                Dem_Data_RequestFixedClear( Dem_CtlClearEventStrgIndex );

#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
                Dem_DTC_ClearPFCClearCondition( Dem_CtlClearEventStrgIndex );
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )  */

                /* Clear the specified data(WIRStatus) */
                Dem_Ind_ClearWIRStatus( Dem_CtlClearEventStrgIndex );

#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )   /*  [FuncSw]    */
                /* Clear MonitorStatuts */
                Dem_MonSts_ReCalcForClearDTC( Dem_CtlClearEventStrgIndex );
#endif  /*   ( DEM_TRIGGER_FIM_REPORTS == STD_ON )          */

                /* Clear completion notification */
                Dem_Control_TriggerInitMForEFnc_Clear( Dem_CtlClearEventStrgIndex );
            }
        }
        else
        {
#if ( DEM_PID_SUPPORT == STD_ON )   /*  [FuncSw]    */
            /* Clear DEM calculation PID */
            Dem_PID_Clear();
#endif  /*   ( DEM_PID_SUPPORT == STD_ON )          */

#if ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )   /*  [FuncSw]    */
            Dem_OpCycle_NotifyClearRAMData();
#endif  /*   ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )          */
#if ( DEM_CHECK_4000RPMOCCURRED_BY_EMISSION_SUPPORT == STD_ON ) /*  [FuncSw]    */
            /*  clear progress engine rpm condition.    */
            Dem_OpCycle_ClearProgressEngine1000RPM();
#endif  /* ( DEM_CHECK_4000RPMOCCURRED_BY_EMISSION_SUPPORT == STD_ON )          */


#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
            Dem_DTC_SetPFCClearDisable( (boolean)TRUE );
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )          */

#if ( DEM_DTR_SUPPORT == STD_ON )   /*  [FuncSw]    */
            /* Clear all TestResult */
            Dem_DTR_ClearDTRData();
#endif  /*   ( DEM_DTR_SUPPORT == STD_ON )          */


#if ( DEM_WWH_OBD_SUPPORT == STD_ON )  /*  [FuncSw]    */
            /* B1 Counter Update */
            Dem_IndMI_UpdateB1CounterWhenClearDTC();
#endif  /*   ( DEM_WWH_OBD_SUPPORT == STD_ON )      */

            retVal  =   DEM_IRT_OK;

            break;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_EndClearDTC_PrimaryMemory                    */
/* Description   | End of ClearDTC in PrimaryMemory.                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCGroup                                            */
/*               | [in] ClearResult                                         */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_EndClearDTC_PrimaryMemory
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_u08_ClearCompleteType, AUTOMATIC ) ClearResult
)
{
    /*  PrimaryMemory clear.        */
    if(( ClearResult == DEM_CLEARCOMPLETE_OK ) || ( ClearResult == DEM_CLEARCOMPLETE_SWCERROR ))
    {
        /* When clear is successful, clear generation sequence table */
        Dem_Control_ClearOrderList( DTCGroup );
    }
    else
    {
        /* When clear is failure, re-build generation sequence table from the current records */
        Dem_Data_GenerateFaultOrderList();

#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )   /* [FuncSw] */
        Dem_Data_GenerateConfirmedFaultOrderList();
#endif  /*   ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )      */

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON ) /*  [FuncSw]    */
        Dem_Data_GenerateMILFaultOrderList();
#endif  /*   ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )        */
    }

    Dem_Data_ClearSearchFFDIndex();

#if ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )   /* [FuncSw] */
    /* Update OccrDTCRecord */
    Dem_OccrDTC_UpdateOccrDTCRecord_ClearDTC( DTCGroup, ClearResult );
#endif  /*   ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )      */

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Control_PrepareClear_PrimaryMemory                   */
/* Description   | Prepare ClearDTC in PrimaryMemory.                       */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_PrepareClear_PrimaryMemory
( void )
{

#if ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )   /* [FuncSw] */
    Dem_OccrDTC_LatchOccrDTCRecord_ClearDTC();
#endif /* DEM_DTC_OCCURRENCE_TIME_SUPPORT -STD_ON-              */

    return ;
}

#if ( DEM_CLEAR_EVENT_NOT_ALLOWED_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_ClearOrderList                               */
/* Description   | Clear order list.                                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCGroup                                            */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_ClearOrderList
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup     /* MISRA DEVIATION */
)
{
    Dem_Data_GenerateFaultOrderList();

#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )   /* [FuncSw] */
    Dem_Data_GenerateConfirmedFaultOrderList();
#endif  /*   ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )      */


#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON ) /*  [FuncSw]    */
    Dem_Data_GenerateMILFaultOrderList();
#endif  /* ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )          */

    return;
}
#endif  /* ( DEM_CLEAR_EVENT_NOT_ALLOWED_SUPPORT == STD_ON ) */

#if ( DEM_CLEAR_EVENT_NOT_ALLOWED_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_Control_ClearOrderList                               */
/* Description   | Clear order list.                                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCGroup                                            */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_ClearOrderList
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup
)
{
    if( DTCGroup == DEM_DTC_GROUP_EMISSION_REL_DTCS )
    {
        Dem_Data_GenerateFaultOrderList();

#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )   /* [FuncSw] */
        Dem_Data_GenerateConfirmedFaultOrderList();
#endif  /*   ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )      */


#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON ) /*  [FuncSw]    */
        Dem_Data_GenerateMILFaultOrderList();
#endif  /* ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )          */
    }
    else
    {
        /* In case of DEM_DTC_GROUP_ALL_DTCS */
        Dem_Data_AllClearFaultOrderList();

#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )   /* [FuncSw] */
        Dem_Data_AllClearConfirmedFaultOrderList();
#endif  /*   ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )      */

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON ) /*  [FuncSw]    */
        Dem_Data_AllClearMILFaultOrderList();
#endif  /*   ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )        */

    }

    return;
}

#endif  /* ( DEM_CLEAR_EVENT_NOT_ALLOWED_SUPPORT == STD_OFF ) */

/****************************************************************************/
/* Function Name | Dem_Control_GetNextEventStrgIndexByDTCsForClearDTC       */
/* Description   | Returns the next event index corresponding to the speci- */
/*               | fied DTC/group DTCs/all DTCs.                            */
/* Preconditions | Now, supports all DTCs only.                             */
/* Parameters    | [in] DTCGroup :                                          */
/*               |        The specified DTC/DTCs group/all DTCs.            */
/*               | [in] BaseEventStrgIndex :                                */
/*               |        The specified based event index.                  */
/*               | [out] NextEventStrgIndexPtr :                            */
/*               |        The next event index which has been retrieved.    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The next event index retrieving is - */
/*               |        successful.                                       */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No more next event  */
/*               |         index.(retrieving finished)                      */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetNextEventStrgIndexByDTCsForClearDTC
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) BaseEventStrgIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) NextEventStrgIndexPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexBase;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) loopEnd;
    VAR( boolean, AUTOMATIC ) eventOBDKind;

    /* Initializes the return value to OK. */
    retVal = DEM_IRT_OK;

    if( DTCGroup == DEM_DTC_GROUP_EMISSION_REL_DTCS )
    {
        eventStorageNum = Dem_CfgInfoPm_GetMaxNumberOfOBDEvent();
    }
    else
    {
        /* DTCGroup is DEM_DTC_GROUP_ALL_DTCS */
        eventStorageNum = Dem_PrimaryMemEventStorageNum;
    }

    eventStrgIndexBase  =   BaseEventStrgIndex;
    eventStrgIndex      =   DEM_EVENTSTRGINDEX_INVALID;

    /*  search loop :   start of eventStrgIndex(DEM_EVENTSTRGINDEX_MIN) to max.    */
    if( eventStorageNum > (Dem_u16_EventStrgIndexType)0U )
    {
        loopEnd =   (boolean)FALSE;
        while ( loopEnd == (boolean)FALSE )
        {
            /* Checks whether the specified based event index is initial value. */
            if( eventStrgIndexBase == DEM_EVENTSTRGINDEX_INVALID )
            {
                /* The specified based event index is initial value. */

                /* Sets the next event index to DEM_EVENTSTRGINDEX_MIN. */
                eventStrgIndex  =   DEM_EVENTSTRGINDEX_MIN;        /*  start of eventStrgIndex(PrimaryMemory).             */
            }
            else if( ( eventStrgIndexBase + (Dem_u16_EventStrgIndexType)1U ) < eventStorageNum )    /* MISRA DEVIATION */
            {
                /* The specified based event index is less than number of the configured events. */

                /* Sets the next event index to based event index plus one. */
                eventStrgIndex  =   eventStrgIndexBase + (Dem_u16_EventStrgIndexType)1U;                   /* MISRA DEVIATION */
            }
            else
            {
                /* The specified based event index is number of the configured events or more. */

                /* Sets the next event index to initial value. */
                eventStrgIndex  =   DEM_EVENTSTRGINDEX_INVALID;

                /* Sets return value to no matching element. */
                retVal = DEM_IRT_NO_MATCHING_ELEMENT;

                break;  /*  exit check loop     */
            }

            /*  search end check        */
            loopEnd =   (boolean)TRUE;

            if( DTCGroup == DEM_DTC_GROUP_EMISSION_REL_DTCS )
            {
                /*  check OBD event or not.     */
                eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( eventStrgIndex );   /* [GUD:RET:TRUE] EventStrgIndex */
                if( eventOBDKind != (boolean)TRUE ) /*  nonOBD      */
                {
                    loopEnd =   (boolean)FALSE;     /*  search next Index   */
                    eventStrgIndexBase  =   eventStrgIndex; /*  set next base index */
                }
            }
        }   /*  end of while ( loopEnd == (boolean)FALSE )  */
    }
    else
    {
        retVal = DEM_IRT_NO_MATCHING_ELEMENT;
    }

    *NextEventStrgIndexPtr = eventStrgIndex;

    /* Returns with the result. */
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_TriggerInitMForEFnc_Clear                    */
/* Description   | Nofify InitMonitorForEvent.                              */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | void                                                     */
/* Notes         | none.                                                    */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_TriggerInitMForEFnc_Clear
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Std_ReturnType, AUTOMATIC ) resultOfCallback = E_NOT_OK;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexCnt;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexNum;

    /*  get current statusofDTC.        */

    eventCtrlIndexNum   =   Dem_CmbEvt_NumOfEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );              /*  get EventCtrlIndex of EventStorageGroup max number  */
    eventCtrlIndex      =   Dem_CmbEvt_GetDelegateEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );        /*  get Delegate EventCtrlIndex                         */

    /*  set all qualification in event storage group to DEM_EVENT_QUALIFICATION_NOTQUALIFIED.   */
    for ( eventCtrlIndexCnt = ( Dem_u16_EventCtrlIndexType )0U; eventCtrlIndexCnt < eventCtrlIndexNum; eventCtrlIndexCnt++ )
    {
        /*  Nofify DTC status changed for Overwritten event.        */
        Dem_CfgInfoPm_TriggerInitMForEFnc( eventCtrlIndex, DEM_INIT_MONITOR_CLEAR, &resultOfCallback );

        /*  get next Index.         */
        eventCtrlIndex  =   Dem_CmbEvt_GetNextEventCtrlIndex_InEvtStrgGrp( eventCtrlIndex );
    }

    return ;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
