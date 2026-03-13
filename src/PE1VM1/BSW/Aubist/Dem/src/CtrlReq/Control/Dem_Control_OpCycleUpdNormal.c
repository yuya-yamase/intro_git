/* Dem_Control_OpCycleUpdNormal_c(v5-7-0)                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_OpCycleUpdNormal/CODE                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_OpCycle_Cfg.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_CmnLib_OpCycle.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_Pm_DTC_PFC.h"
#include "../../../inc/Dem_Pm_PID.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Pm_MonSts.h"
#include "../../../inc/Dem_Pm_IUMPR.h"
#include "../../../inc/Dem_Pm_AltIUMPR.h"
#include "../../../inc/Dem_Pm_Ind_MI.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_DTC_DTCStatus.h"

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

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Control_B1CounterHealingProcess
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatus
);

static FUNC( void, DEM_CODE ) Dem_Control_SetWIRStatusAtShortMI
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) OldDTCStatusStPtr,
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr
);
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON )    */

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
/* Function Name | Dem_Control_NormalEventMemoryEntryByOpCycle              */
/* Description   | update EventMemoryEntry of operation cycle .             */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventPos                                           */
/*               |                                                          */
/*               | [in] OperationCycleIndex : Operation cycle index.        */
/*               |                                                          */
/*               | [in] HealingAgingCycleFlag :                             */
/*               |              check HealingAgingCycle or not.             */
/*               |         TRUE  : This Operation Cycle is                  */
/*               |                                       HealingAgingCycle. */
/*               |         FALSE : This Operation Cycle is not              */
/*               |                                       HealingAgingCycle. */
/*               | [in] FailureCycleFlag :                                  */
/*               |              check FailureCycle or not.                  */
/*               |         TRUE  : This Operation Cycle is FailerCycle.     */
/*               |         FALSE : This Operation Cycle is not FailerCycle. */
/*               | [out] NeedGenOrderListPtr :                              */
/*               |              need GenOrderList or not.                   */
/*               |                  TRUE    :   need generate .             */
/*               |                  FALSE   :   no need generate .          */
/*               | [out] ExecHealingPtr :                                   */
/*               |              execute healing or not.                     */
/*               |                  TRUE    :   execute healing.            */
/*               |                  FALSE   :   no execute healing.         */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]AltIUMPR                                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-6-0      | no object changed.                                       */
/*   v5-7-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_NormalEventMemoryEntryByOpCycle
(
    VAR( Dem_u16_EventPosType, AUTOMATIC ) EventPos,            /* [PRMCHK:CALLER] */
    VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC ) HealingAgingCycleFlag,
    VAR( Dem_u08_OpcycUpdateFailureCycleType, AUTOMATIC ) FailureCycleFlag,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) NeedGenOrderListPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ExecHealingPtr
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( boolean, AUTOMATIC ) delegateEventInEvtStrgGrp;

    VAR( Dem_DTCStatusStType, AUTOMATIC ) oldDTCStatusSt;
    VAR( Dem_DTCStatusStType, AUTOMATIC ) newDTCStatusSt;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retSaveEventMemoryEntryToTmp;
    VAR( boolean, AUTOMATIC ) agingExecFlag;
    VAR( boolean, AUTOMATIC ) pendingRecoveryExecFlag;
    VAR( boolean, AUTOMATIC ) agingConditionFlag;
    VAR( Std_ReturnType, AUTOMATIC ) resultOfCallback;

    resultOfCallback = E_NOT_OK;
    pendingRecoveryExecFlag = (boolean)FALSE;
    agingExecFlag = (boolean)FALSE;

    oldDTCStatusSt.DTCStatus        = DEM_DTCSTATUS_BYTE_ALL_OFF;
    oldDTCStatusSt.ExtendDTCStatus  = DEM_DTCSTATUSEX_BYTE_ALL_OFF;
    oldDTCStatusSt.ExtendDTCStatus2 = DEM_DTCSTATUSEX2_BYTE_ALL_OFF;

    /*  check delegate event.       */
    eventCtrlIndex              =   (Dem_u16_EventCtrlIndexType)EventPos;                                   /* [GUDCHK:CALLER]EventPos */
    delegateEventInEvtStrgGrp   =   Dem_CmbEvt_CheckDelegateEventCtrlIndex_InEvtStrgGrp( eventCtrlIndex );  /* [GUDCHK:CALLER]EventPos */
    if ( delegateEventInEvtStrgGrp == (boolean)TRUE )
    {
        eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );    /* [GUDCHK:CALLER]EventPos *//* [GUD:RET:IF_GUARDED: eventCtrlIndex ]eventStrgIndex */

        /*----------------------------------------------*/
        /*  save record data to temporary memory.       */
        /*----------------------------------------------*/
        retSaveEventMemoryEntryToTmp = Dem_Control_SaveEventMemoryEntryToTmp( eventStrgIndex ); /* [GUDCHK:CALLER]EventPos */
        if( retSaveEventMemoryEntryToTmp == DEM_IRT_OK )
        {
            Dem_Data_GetDTCStatusStructFromTmp( &oldDTCStatusSt );

            newDTCStatusSt.DTCStatus = oldDTCStatusSt.DTCStatus;
            newDTCStatusSt.ExtendDTCStatus   =   oldDTCStatusSt.ExtendDTCStatus;
            newDTCStatusSt.ExtendDTCStatus2  =   oldDTCStatusSt.ExtendDTCStatus2;

            /*  match of HealingAging cycle.            */
            if( HealingAgingCycleFlag != DEM_OPCYCUPD_HACYC_INITIALVALUE )
            {
                if (( HealingAgingCycleFlag & DEM_OPCYCUPD_HACYC_UPDATE_HEALINGCYC ) == DEM_OPCYCUPD_HACYC_UPDATE_HEALINGCYC )
                {
                    /*      TestFailedThisHealingCycle (bit1 at Healing cycle) == OFF    */
                    /*  and TestNotCompThisHealingCycle(bit6 at Healing cycle) == OFF    */
                    if( ( ( oldDTCStatusSt.ExtendDTCStatus & DEM_DTCSTATUSEX_STATUS_TFTOC_IN_HEALINGCYCLE ) == DEM_DTCSTATUSEX_BYTE_ALL_OFF ) && ( ( oldDTCStatusSt.ExtendDTCStatus & DEM_DTCSTATUSEX_STATUS_TNCTOC_IN_HEALINGCYCLE ) == DEM_DTCSTATUSEX_BYTE_ALL_OFF ) )
                    {
                        /*  base statusOfDTC bit2(PendingBit) == ON    */
                        if( ( oldDTCStatusSt.DTCStatus & DEM_UDS_STATUS_PDTC ) == DEM_UDS_STATUS_PDTC ) /*  statusOfDTC : bit2  */
                        {
                            pendingRecoveryExecFlag = (boolean)TRUE;
                        }

                        /*  PendingOFFCondition is OK or base statusOfDTC bit3(ConfirmedBit) == ON    */
                        if( ( pendingRecoveryExecFlag == (boolean)FALSE ) || ( ( oldDTCStatusSt.DTCStatus & DEM_UDS_STATUS_CDTC ) == DEM_UDS_STATUS_CDTC ) )    /*  statusOfDTC : bit3  */
                        {
                            *ExecHealingPtr =   Dem_Control_ProcessHealing( eventStrgIndex, &oldDTCStatusSt, &newDTCStatusSt );     /* [GUDCHK:CALLER]EventPos */
                        }
#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
                        Dem_Control_B1CounterHealingProcess( eventStrgIndex, oldDTCStatusSt.DTCStatus );        /* [GUDCHK:CALLER]EventPos */
#endif  /*   ( DEM_WWH_OBD_SUPPORT == STD_ON )      */
                    }
                }

                if ( ( HealingAgingCycleFlag & ( DEM_OPCYCUPD_HACYC_EXEC_AGING | DEM_OPCYCUPD_HACYC_UPDATE_TIME_AGINGCYC ) ) != (Dem_u08_OpcycUpdateHealingAgingCycleType)0x00U )
                {
                    /* check Aging condition.  */
                    agingConditionFlag = Dem_Control_CheckAgingConditionByEventStrgIndex( eventStrgIndex );     /* [GUDCHK:CALLER]EventPos */

                    /*  AgingCondition is OK and TestFailedThisAgingCycle(bit1 at Aging cycle) == OFF    */
                    if( ( agingConditionFlag == (boolean)TRUE ) && ( ( oldDTCStatusSt.ExtendDTCStatus & DEM_DTCSTATUSEX_STATUS_TFTOC_IN_AGINGCYCLE ) == DEM_DTCSTATUSEX_BYTE_ALL_OFF ) )
                    {
                        Dem_Control_ProcessAging( HealingAgingCycleFlag, eventStrgIndex, &oldDTCStatusSt, &agingExecFlag );        /* [GUDCHK:CALLER]EventPos */
                    }
                    else
                    {
                        /* No process */
                    }
                }

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )   /*  [FuncSw]    */
                if( ( HealingAgingCycleFlag & DEM_OPCYCUPD_HACYC_EXEC_WWHOBD_AGING ) == DEM_OPCYCUPD_HACYC_EXEC_WWHOBD_AGING )
                {
                    Dem_Control_ProcessAgingForWWHOBD( eventStrgIndex, &newDTCStatusSt, &agingExecFlag );       /* [GUDCHK:CALLER]EventPos */
                }
#endif  /*  ( DEM_WWH_OBD_SUPPORT == STD_ON )           */

#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
                Dem_DTC_ClearPFCByCycleStart( &oldDTCStatusSt, &newDTCStatusSt );
#endif  /* ( DEM_PFC_SUPPORT == STD_ON )    */

#if ( DEM_PID_READINESS_SUPPORT == STD_ON )   /*  [FuncSw]    */
                /* Clear the Event Disable Status */
                newDTCStatusSt.ExtendDTCStatus2 =   Dem_DTC_ExDTC2_ClearEventDisable( newDTCStatusSt.ExtendDTCStatus2 );
#endif  /*   ( DEM_PID_READINESS_SUPPORT == STD_ON )          */

                /*  update extendedDTCStatus : Restart HealingAging cycle.          */
                newDTCStatusSt.ExtendDTCStatus  =   Dem_DTC_ExDTC_RestartHealingAgingCycleExDTCStatus( newDTCStatusSt.ExtendDTCStatus, HealingAgingCycleFlag );
                newDTCStatusSt.ExtendDTCStatus2 =   Dem_DTC_ExDTC2_RestartHealingAgingCycleExDTCStatus( newDTCStatusSt.ExtendDTCStatus2, HealingAgingCycleFlag );

                if( agingExecFlag == (boolean)TRUE )
                {
                    /*  set aging history.          */
                    newDTCStatusSt.ExtendDTCStatus2 =   Dem_DTC_ExDTC2_SetAgingHistory( newDTCStatusSt.ExtendDTCStatus2 );
                }

            }

            if ( FailureCycleFlag != DEM_OPCYCUPD_FLCYC_INITIALVALUE )
            {
                /*  update DTC status : bit1,6      */
                newDTCStatusSt.DTCStatus = Dem_DTC_RestartOperationCycleDTCStatus( newDTCStatusSt.DTCStatus, FailureCycleFlag );
                newDTCStatusSt.ExtendDTCStatus2 = Dem_DTC_ExDTC2_RestartOperationCycleExDTCStatus( newDTCStatusSt.ExtendDTCStatus2, FailureCycleFlag );
            }

            newDTCStatusSt.ExtendDTCStatus2  =   Dem_DTC_ExDTC2_SetIndicatorAtCycleStart( newDTCStatusSt.ExtendDTCStatus, newDTCStatusSt.ExtendDTCStatus2 );

#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
            Dem_Control_SetWIRStatusAtShortMI( eventStrgIndex, &oldDTCStatusSt, &newDTCStatusSt );      /* [GUDCHK:CALLER]EventPos */
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

            /*  set new DTC status to temporary memory.     */
            Dem_Data_SetDTCStatusStructToTmp( &newDTCStatusSt );

            /*---------------------------------------------------------------------------------------------------------------*/
            /*  update eventmemory entry at operationcycle updated. (update temporaty memory and set to SAVED_ZONE area.)    */
            /*---------------------------------------------------------------------------------------------------------------*/
            Dem_Control_UpdEvtMemEntryOfTmp_AtOpcycUpdate( DEM_EVTKINDPTN_PRIMEM_NORMAL, eventStrgIndex, pendingRecoveryExecFlag, agingExecFlag, oldDTCStatusSt.DTCStatus, NeedGenOrderListPtr );   /* [GUDCHK:CALLER]EventPos */

        }
    }

#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )  /*  [FuncSw]    */
    /*  match of HealingAging cycle.            */
    if( HealingAgingCycleFlag != DEM_OPCYCUPD_HACYC_INITIALVALUE )
    {
        /*  TestNotCompThisHealingAgingCycle(bit6 at Healing cycle) == OFF    */
        Dem_AltIUMPR_IncNumeratorCounts( eventCtrlIndex );          /* [GUDCHK:CALLER]EventPos *//* [UpdRec]AltIUMPR */
    }
#endif  /* ( DEM_ALTIUMPR_SUPPORT == STD_ON )   */

#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )   /*  [FuncSw]    */
    Dem_MonSts_ReCalcForOC( eventCtrlIndex, FailureCycleFlag );     /* [GUDCHK:CALLER]EventPos */
#endif  /*   ( DEM_TRIGGER_FIM_REPORTS == STD_ON )          */

    Dem_CfgInfoPm_TriggerInitMForEFnc( eventCtrlIndex, DEM_INIT_MONITOR_RESTART, &resultOfCallback );   /* [GUDCHK:CALLER]EventPos */

    return ;
}

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_B1CounterHealingProcess                      */
/* Description   | B1 counter healing process.                              */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStrgIndex                                     */
/*               | [in]  OldDTCStatus                                       */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_B1CounterHealingProcess
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatus
)
{
    VAR( boolean, AUTOMATIC ) useB1Counter;

    useB1Counter  =   Dem_CfgInfoPm_ChkDTCCls_UseB1Counter( EventStrgIndex );   /* [GUDCHK:CALLER]EventStrgIndex */
    if ( useB1Counter == (boolean)TRUE )
    {
        if( ( OldDTCStatus & DEM_UDS_STATUS_PDTC ) != DEM_UDS_STATUS_PDTC )
        {
            Dem_IndMI_B1CounterHealingProcess( EventStrgIndex );                /* [GUDCHK:CALLER]EventStrgIndex */
        }
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_Control_SetWIRStatusAtShortMI                        */
/* Description   | When move from MI-OFF to Short-MI, bit7 turns on.        */
/* Preconditions | none                                                     */
/* Parameters    | [in]      EventStrgIndex                                 */
/*               | [in]      OldDTCStatusStPtr                              */
/*               | [in/out]  NewDTCStatusStPtr                              */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_SetWIRStatusAtShortMI
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,            /* [PRMCHK:CALLER] */
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) OldDTCStatusStPtr,
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr
)
{
    VAR( boolean, AUTOMATIC ) useActiveFaultAtCycleStart;
    VAR( Dem_u08_DemBooleanType, AUTOMATIC ) milAtShortMIFlg;

    if (  ( ( OldDTCStatusStPtr->ExtendDTCStatus2 & DEM_DTCSTATUSEX2_STATUS_INDICATOR_AT_CYCLESTART ) != DEM_DTCSTATUSEX2_STATUS_INDICATOR_AT_CYCLESTART ) &&
          ( ( NewDTCStatusStPtr->ExtendDTCStatus2 & DEM_DTCSTATUSEX2_STATUS_INDICATOR_AT_CYCLESTART ) == DEM_DTCSTATUSEX2_STATUS_INDICATOR_AT_CYCLESTART ) )
    {
        useActiveFaultAtCycleStart = Dem_CfgInfoPm_ChkDTCCls_AFACBitONAtCycUpd( EventStrgIndex );   /* [GUDCHK:CALLER]EventStrgIndex */
        if ( useActiveFaultAtCycleStart == (boolean)TRUE )
        {
            milAtShortMIFlg = Dem_IndMI_GetMILAtShortMIFlg();
            if ( milAtShortMIFlg == DEM_BOOLEAN_TRUE )
            {
                NewDTCStatusStPtr->DTCStatus = Dem_DTC_SetWIRStatusBit( NewDTCStatusStPtr->DTCStatus );
            }
        }
    }
    return;
}
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
