/* Dem_Control_OpCycleUpdSpecific_c(v5-5-0)                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_OpCycleUpdSpecific/CODE                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_OpCycle_Cfg.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_CmnLib_OpCycle.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_Pm_DTC_PFC.h"
#include "../../../inc/Dem_Pm_MonSts.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Pm_Similar.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_PID.h"
#include "../../../inc/Dem_Pm_AltIUMPR.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "Dem_Control_local.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    boolean  PendingRecoveryExec;
    boolean  AgingExec;
}Dem_ExecFlagType;

typedef struct {
    Dem_DTCStatusStType        OldDTCStatusSt;
    Dem_DTCStatusStType        NewDTCStatusSt;

    Dem_ChkBitDTCStatusType    CheckBitOldStatus;
    Dem_ChkSpCondType          ChkSpCond;
    Dem_ExecFlagType           ExecFlag;
}Dem_OpCycleUpdInfoType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>
static FUNC( void, DEM_CODE ) Dem_Control_UpdSpecEventByHealingAgingCycle
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC ) HealingAgingCycleFlag,
    VAR( Dem_u08_OpcycUpdateFailureCycleType, AUTOMATIC ) FailureCycleFlag,
    P2VAR( Dem_OpCycleUpdInfoType, AUTOMATIC, AUTOMATIC ) OpCycleUpdInfoPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ExecHealingPtr
);

static FUNC( boolean, DEM_CODE ) Dem_Control_ProcessForSpecificEventPassed
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_OpCycleUpdInfoType, AUTOMATIC, AUTOMATIC ) OpCycleUpdInfoPtr
);
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Control_SimilarProcessPendingFaultRecovery
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_OpCycleUpdInfoType, AUTOMATIC, AUTOMATIC ) OpCycleUpdInfoPtr
);
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )     */

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


/****************************************************************************/
/* Function Name | Dem_Control_UpdateSpecificEventMemoryEntryByOpCycle      */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventPos                                           */
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
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_UpdateSpecificEventMemoryEntryByOpCycle
(
    VAR( Dem_u16_EventPosType, AUTOMATIC ) EventPos,
    VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC ) HealingAgingCycleFlag,
    VAR( Dem_u08_OpcycUpdateFailureCycleType, AUTOMATIC ) FailureCycleFlag,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) NeedGenOrderListPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ExecHealingPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( boolean, AUTOMATIC ) delegateEventInEvtStrgGrp;

    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_OpCycleUpdInfoType, AUTOMATIC ) opCycleUpdInfo;
    VAR( Std_ReturnType, AUTOMATIC ) resultOfCallback;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retSaveEventMemoryEntryToTmp;
    VAR( boolean, AUTOMATIC ) needGenOrderList;
    VAR( boolean, AUTOMATIC ) execHealing;

    resultOfCallback = E_NOT_OK;
    needGenOrderList    =   (boolean)FALSE;
    execHealing         =   (boolean)FALSE;

    opCycleUpdInfo.ExecFlag.PendingRecoveryExec = (boolean)FALSE;
    opCycleUpdInfo.ExecFlag.AgingExec           = (boolean)FALSE;

    opCycleUpdInfo.ChkSpCond.Healing   = (boolean)TRUE;
    opCycleUpdInfo.ChkSpCond.Aging     = (boolean)TRUE;
    opCycleUpdInfo.ChkSpCond.PendErase = (boolean)TRUE;

    eventCtrlIndex  =   (Dem_u16_EventCtrlIndexType)EventPos;                               /* [GUDCHK:CALLER]EventPos */
    eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );    /* [GUDCHK:CALLER]EventPos *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */

#if ( DEM_ALTIUMPR_SUPPORT == STD_ON ) /*  [FuncSw]    */
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    Dem_AltIUMPR_PrepareIncNumeratorCountsForCylinder( eventStrgIndex );    /* [GUDCHK:CALLER]EventPos */
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
#endif  /*   ( DEM_ALTIUMPR_SUPPORT == STD_ON ) */

    delegateEventInEvtStrgGrp   =   Dem_CmbEvt_CheckDelegateEventCtrlIndex_InEvtStrgGrp( eventCtrlIndex );  /* [GUDCHK:CALLER]EventPos */
    if ( delegateEventInEvtStrgGrp == (boolean)TRUE )
    {
        retSaveEventMemoryEntryToTmp = Dem_Control_SaveSpecificEventMemoryEntryToTmp( eventStrgIndex );
        if( retSaveEventMemoryEntryToTmp == DEM_IRT_OK )
        {
            opCycleUpdInfo.OldDTCStatusSt.DTCStatus = DEM_DTCSTATUS_BYTE_ALL_OFF;
            opCycleUpdInfo.OldDTCStatusSt.ExtendDTCStatus = DEM_DTCSTATUSEX_BYTE_ALL_OFF;
            opCycleUpdInfo.OldDTCStatusSt.ExtendDTCStatus2 = DEM_DTCSTATUSEX2_BYTE_ALL_OFF;

            Dem_Data_GetDTCStatusStructFromTmp( &opCycleUpdInfo.OldDTCStatusSt );

            opCycleUpdInfo.NewDTCStatusSt.DTCStatus         = opCycleUpdInfo.OldDTCStatusSt.DTCStatus;
            opCycleUpdInfo.NewDTCStatusSt.ExtendDTCStatus   = opCycleUpdInfo.OldDTCStatusSt.ExtendDTCStatus;
            opCycleUpdInfo.NewDTCStatusSt.ExtendDTCStatus2  = opCycleUpdInfo.OldDTCStatusSt.ExtendDTCStatus2;

            /*  match of HealingAging cycle.            */
            if( HealingAgingCycleFlag != DEM_OPCYCUPD_HACYC_INITIALVALUE )
            {
                Dem_Control_UpdSpecEventByHealingAgingCycle( eventStrgIndex, HealingAgingCycleFlag, FailureCycleFlag, &opCycleUpdInfo, &execHealing );
            }
            else
            {
                if ( FailureCycleFlag != DEM_OPCYCUPD_FLCYC_INITIALVALUE )
                {
                    /*  update DTC status : bit1,6      */
                    opCycleUpdInfo.NewDTCStatusSt.DTCStatus = Dem_DTC_RestartOperationCycleDTCStatus( opCycleUpdInfo.NewDTCStatusSt.DTCStatus, FailureCycleFlag );
                    opCycleUpdInfo.NewDTCStatusSt.ExtendDTCStatus2 = Dem_DTC_ExDTC2_RestartOperationCycleExDTCStatus( opCycleUpdInfo.NewDTCStatusSt.ExtendDTCStatus2, FailureCycleFlag );
                }

                opCycleUpdInfo.NewDTCStatusSt.ExtendDTCStatus2  =   Dem_DTC_ExDTC2_SetIndicatorAtCycleStart( opCycleUpdInfo.NewDTCStatusSt.ExtendDTCStatus, opCycleUpdInfo.NewDTCStatusSt.ExtendDTCStatus2 );

                /*  set new DTC status to temporary memory.     */
                Dem_Data_SetDTCStatusStructToTmp( &opCycleUpdInfo.NewDTCStatusSt );
            }

            /*---------------------------------------------------------------------------------------------------------------*/
            /*  update eventmemory entry at operationcycle updated. (update temporaty memory and set to SAVED_ZONE area.)    */
            /*---------------------------------------------------------------------------------------------------------------*/
            Dem_Control_UpdEvtMemEntryOfTmp_AtOpcycUpdate( DEM_EVTKINDPTN_PRIMEM_SPECIFIC, eventStrgIndex, opCycleUpdInfo.ExecFlag.PendingRecoveryExec, opCycleUpdInfo.ExecFlag.AgingExec, opCycleUpdInfo.OldDTCStatusSt.DTCStatus, &needGenOrderList );
        }
    }

#if ( DEM_ALTIUMPR_SUPPORT == STD_ON ) /*  [FuncSw]    */
    if( HealingAgingCycleFlag != DEM_OPCYCUPD_HACYC_INITIALVALUE )
    {
        Dem_AltIUMPR_IncNumeratorCounts( eventCtrlIndex );      /* [GUDCHK:CALLER]EventPos */
    }
#endif  /*   ( DEM_ALTIUMPR_SUPPORT == STD_ON ) */

#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )   /*  [FuncSw]    */
    Dem_MonSts_ReCalcForOC( eventCtrlIndex, FailureCycleFlag ); /* [GUDCHK:CALLER]EventPos */
#endif  /*   ( DEM_TRIGGER_FIM_REPORTS == STD_ON )          */

    Dem_CfgInfoPm_TriggerInitMForEFnc( eventCtrlIndex, DEM_INIT_MONITOR_RESTART, &resultOfCallback );   /* [GUDCHK:CALLER]EventPos */


    *NeedGenOrderListPtr    =   needGenOrderList;
    *ExecHealingPtr         =   execHealing;

    return ;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Dem_Control_UpdSpecEventByHealingAgingCycle              */
/* Description   | update HealingAging cycle.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex.                                     */
/*               | [in] OperationCycleIndex .                               */
/*               | [in] HealingAgingCycleFlag :                             */
/*               | [in] FailureCycleFlag :                                  */
/*               | [in/out] OpCycleUpdInfoPtr                               */
/*               | [out] ExecHealingPtr :                                   */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_UpdSpecEventByHealingAgingCycle
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC ) HealingAgingCycleFlag,
    VAR( Dem_u08_OpcycUpdateFailureCycleType, AUTOMATIC ) FailureCycleFlag,
    P2VAR( Dem_OpCycleUpdInfoType, AUTOMATIC, AUTOMATIC ) OpCycleUpdInfoPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ExecHealingPtr
)
{
    VAR( boolean, AUTOMATIC ) agingConditionFlag;
    VAR( boolean, AUTOMATIC ) execHealing;

    execHealing         =   (boolean)FALSE;

    /* Acquire a  judgement result of Bit0,1,2,3,6,7 */
    OpCycleUpdInfoPtr->CheckBitOldStatus.TestNotCompThisHealingCycle = Dem_DTC_CheckExtendDTCStatus( OpCycleUpdInfoPtr->OldDTCStatusSt.ExtendDTCStatus, (Dem_UdsStatusByteType)DEM_DTCSTATUSEX_STATUS_TNCTOC_IN_HEALINGCYCLE );
    OpCycleUpdInfoPtr->CheckBitOldStatus.TestFailedThisHealingCycle  = Dem_DTC_CheckExtendDTCStatus( OpCycleUpdInfoPtr->OldDTCStatusSt.ExtendDTCStatus, (Dem_UdsStatusByteType)DEM_DTCSTATUSEX_STATUS_TFTOC_IN_HEALINGCYCLE );
    OpCycleUpdInfoPtr->CheckBitOldStatus.TestNotCompThisAgingCycle = Dem_DTC_CheckExtendDTCStatus( OpCycleUpdInfoPtr->OldDTCStatusSt.ExtendDTCStatus, (Dem_UdsStatusByteType)DEM_DTCSTATUSEX_STATUS_TNCTOC_IN_AGINGCYCLE );
    OpCycleUpdInfoPtr->CheckBitOldStatus.TestFailedThisAgingCycle  = Dem_DTC_CheckExtendDTCStatus( OpCycleUpdInfoPtr->OldDTCStatusSt.ExtendDTCStatus, (Dem_UdsStatusByteType)DEM_DTCSTATUSEX_STATUS_TFTOC_IN_AGINGCYCLE );
    OpCycleUpdInfoPtr->CheckBitOldStatus.PendingDTC             = Dem_DTC_CheckDTCStatus( OpCycleUpdInfoPtr->OldDTCStatusSt.DTCStatus, (Dem_UdsStatusByteType)DEM_UDS_STATUS_PDTC );    /*  statusOfDTC : bit2  */
    OpCycleUpdInfoPtr->CheckBitOldStatus.ConfirmedDTC           = Dem_DTC_CheckDTCStatus( OpCycleUpdInfoPtr->OldDTCStatusSt.DTCStatus, (Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC );    /*  statusOfDTC : bit3  */
    OpCycleUpdInfoPtr->CheckBitOldStatus.TestFailed             = Dem_DTC_CheckDTCStatus( OpCycleUpdInfoPtr->OldDTCStatusSt.DTCStatus, (Dem_UdsStatusByteType)DEM_UDS_STATUS_TF );      /*  statusOfDTC : bit0  */
    OpCycleUpdInfoPtr->CheckBitOldStatus.WirStatus              = Dem_DTC_CheckDTCStatus( OpCycleUpdInfoPtr->OldDTCStatusSt.DTCStatus, (Dem_UdsStatusByteType)DEM_UDS_STATUS_WIR );     /*  statusOfDTC : bit7  */
    OpCycleUpdInfoPtr->CheckBitOldStatus.IndicatorStatus        = Dem_DTC_CheckExtendDTCStatus( OpCycleUpdInfoPtr->OldDTCStatusSt.ExtendDTCStatus, DEM_DTCSTATUSEX_STATUS_INDICATOR );

    if (( HealingAgingCycleFlag & DEM_OPCYCUPD_HACYC_UPDATE_HEALINGCYC ) == DEM_OPCYCUPD_HACYC_UPDATE_HEALINGCYC )
    {
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
       /* In the case of using similar condition */
       Dem_Similar_PreProccessByCycleStart();
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )           */

       if( OpCycleUpdInfoPtr->CheckBitOldStatus.TestFailedThisHealingCycle == (boolean)FALSE )
       {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
           /* Bit1 in the case of OFF */
           Dem_Misfire_ChkSpCondToOpCycUpdateQualified( EventStrgIndex, &OpCycleUpdInfoPtr->ChkSpCond );
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
           /* In the case of using similar condition */
           Dem_Similar_ChkSpCondToOpCycUpdateQualified( EventStrgIndex, &OpCycleUpdInfoPtr->ChkSpCond );
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */

           if( OpCycleUpdInfoPtr->CheckBitOldStatus.TestNotCompThisHealingCycle == (boolean)FALSE )
           {
               /* Bit1 and Bit6 in the case of OFF */
               execHealing =   Dem_Control_ProcessForSpecificEventPassed( EventStrgIndex, OpCycleUpdInfoPtr );
           }

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
           /* In the case of using similar condition */
           Dem_Control_SimilarProcessPendingFaultRecovery( EventStrgIndex, OpCycleUpdInfoPtr );
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */
       }
       else
       {
           /* Bit1 in the case of ON */
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
           /* In the case of Misfire Event */
           Dem_Misfire_ProcessForEventFailed( EventStrgIndex, &OpCycleUpdInfoPtr->CheckBitOldStatus );
#endif  /*   ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )         */

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
           /* In the case of using similar condition */
           Dem_Similar_ProcessForEventFailed( &OpCycleUpdInfoPtr->CheckBitOldStatus );
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */
       }
    }

    if ( ( HealingAgingCycleFlag & ( DEM_OPCYCUPD_HACYC_EXEC_AGING | DEM_OPCYCUPD_HACYC_UPDATE_TIME_AGINGCYC ) ) != (Dem_u08_OpcycUpdateHealingAgingCycleType)0x00U )
    {
        agingConditionFlag = Dem_Control_CheckAgingConditionByEventStrgIndex( EventStrgIndex );

        if( ( OpCycleUpdInfoPtr->ChkSpCond.Aging                         == (boolean)TRUE  )
         && ( agingConditionFlag                              == (boolean)TRUE  )
         && ( OpCycleUpdInfoPtr->CheckBitOldStatus.TestFailedThisAgingCycle == (boolean)FALSE ) )
        {
            Dem_Control_ProcessAging( HealingAgingCycleFlag, OpCycleUpdInfoPtr->ExecFlag.PendingRecoveryExec, EventStrgIndex, &OpCycleUpdInfoPtr->OldDTCStatusSt, &OpCycleUpdInfoPtr->ExecFlag.AgingExec );
        }
    }

    /*  For WWH-OBD, specific event is not supported,   */
    /*  so no need to call Dem_Control_ProcessAgingForWWHOBD() function for additional aging process.   */

#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
    Dem_DTC_ClearPFCByCycleStart( &OpCycleUpdInfoPtr->OldDTCStatusSt, &OpCycleUpdInfoPtr->NewDTCStatusSt );
#endif  /* ( DEM_PFC_SUPPORT == STD_ON )    */

    OpCycleUpdInfoPtr->NewDTCStatusSt.ExtendDTCStatus = Dem_DTC_ExDTC_ResetPredictiveFaultBit( OpCycleUpdInfoPtr->NewDTCStatusSt.ExtendDTCStatus );

    /*  update extendedDTCStatus : Restart HealingAging cycle.          */
    OpCycleUpdInfoPtr->NewDTCStatusSt.ExtendDTCStatus  = Dem_DTC_ExDTC_RestartHealingAgingCycleExDTCStatus( OpCycleUpdInfoPtr->NewDTCStatusSt.ExtendDTCStatus, HealingAgingCycleFlag );
    OpCycleUpdInfoPtr->NewDTCStatusSt.ExtendDTCStatus2 = Dem_DTC_ExDTC2_RestartHealingAgingCycleExDTCStatus( OpCycleUpdInfoPtr->NewDTCStatusSt.ExtendDTCStatus2, HealingAgingCycleFlag );

    if( OpCycleUpdInfoPtr->ExecFlag.AgingExec == (boolean)TRUE )
    {
        /*  set aging history.          */
        OpCycleUpdInfoPtr->NewDTCStatusSt.ExtendDTCStatus2  =   Dem_DTC_ExDTC2_SetAgingHistory( OpCycleUpdInfoPtr->NewDTCStatusSt.ExtendDTCStatus2 );
    }


    if ( FailureCycleFlag != DEM_OPCYCUPD_FLCYC_INITIALVALUE )
    {
        /*  update DTC status : bit1,6      */
        OpCycleUpdInfoPtr->NewDTCStatusSt.DTCStatus = Dem_DTC_RestartOperationCycleDTCStatus( OpCycleUpdInfoPtr->NewDTCStatusSt.DTCStatus, FailureCycleFlag );
        OpCycleUpdInfoPtr->NewDTCStatusSt.ExtendDTCStatus2 = Dem_DTC_ExDTC2_RestartOperationCycleExDTCStatus( OpCycleUpdInfoPtr->NewDTCStatusSt.ExtendDTCStatus2, FailureCycleFlag );
    }

    OpCycleUpdInfoPtr->NewDTCStatusSt.ExtendDTCStatus2  =   Dem_DTC_ExDTC2_SetIndicatorAtCycleStart( OpCycleUpdInfoPtr->NewDTCStatusSt.ExtendDTCStatus, OpCycleUpdInfoPtr->NewDTCStatusSt.ExtendDTCStatus2 );

    /*  set new DTC status to temporary memory.     */
    Dem_Data_SetDTCStatusStructToTmp( &OpCycleUpdInfoPtr->NewDTCStatusSt );

    /*----------------------------------------------------------------------------------------------------------------------*/
    /*  set NewDTCStatus(bit2,3).   for Dem_Similar_ClearTmpByCycleStart() or Dem_Misfire_ClearTmpByCycleStart().           */
    /*----------------------------------------------------------------------------------------------------------------------*/
    if( OpCycleUpdInfoPtr->ExecFlag.AgingExec == (boolean)TRUE )
    {
        /* Set Bit3 to OFF */
        OpCycleUpdInfoPtr->NewDTCStatusSt.DTCStatus = Dem_DTC_ResetConfirmedDTCStatus_AtAging( OpCycleUpdInfoPtr->NewDTCStatusSt.DTCStatus );
    }
    if( OpCycleUpdInfoPtr->ExecFlag.PendingRecoveryExec == (boolean)TRUE )
    {
        /* Set Bit2 to OFF */
        OpCycleUpdInfoPtr->NewDTCStatusSt.DTCStatus = Dem_DTC_ResetPendingDTCBit( OpCycleUpdInfoPtr->NewDTCStatusSt.DTCStatus );
    }

    /*----------------------------------------------------------------------------------------------------------------------*/
    /*  update similar / misfire memoryarea.                                                                                */
    /*----------------------------------------------------------------------------------------------------------------------*/
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    /* In the case of using similar condition */
    Dem_Similar_ClearTmpByCycleStart( OpCycleUpdInfoPtr->NewDTCStatusSt.DTCStatus );
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    /* In the case of Misfire Event */
    Dem_Misfire_ClearTmpByCycleStart( EventStrgIndex, OpCycleUpdInfoPtr->NewDTCStatusSt.DTCStatus, &OpCycleUpdInfoPtr->CheckBitOldStatus );
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )           */

    /* Clear the Event Disable Status */
    OpCycleUpdInfoPtr->NewDTCStatusSt.ExtendDTCStatus2  =   Dem_DTC_ExDTC2_ClearEventDisable( OpCycleUpdInfoPtr->NewDTCStatusSt.ExtendDTCStatus2 );

    *ExecHealingPtr =   execHealing;
    return ;
}

/****************************************************************************/
/* Function Name | Dem_Control_ProcessForSpecificEventPassed                */
/* Description   | Proccess For Event Specific Event Passed.                */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex                                      */
/*               | [in/out] OpCycleUpdInfoPtr                               */
/* Return Value  | boolean                                                  */
/*               |              execute healing or not.                     */
/*               |                  TRUE    :   execute healing.            */
/*               |                  FALSE   :   no execute healing.         */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Control_ProcessForSpecificEventPassed
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,            /* [PRMCHK:CALLER] */
    P2VAR( Dem_OpCycleUpdInfoType, AUTOMATIC, AUTOMATIC ) OpCycleUpdInfoPtr
)
{
    VAR( boolean, AUTOMATIC ) execHealing;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u08_MisfExceedanceCounterType, AUTOMATIC ) getExceedanceCounter;
    VAR( boolean, AUTOMATIC ) eventMisfireKind;
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )           */
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) retCheckSimilarPassedThisDCY;
    VAR( Dem_u08_SimilarExceedanceCounterType, AUTOMATIC ) getSimilarExceedanceCounter;
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */

    execHealing         =   (boolean)FALSE;

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    /* In the case of using similar condition */
    retCheckSimilarPassedThisDCY = Dem_Similar_CheckSimilarPassedThisDCYFromTmp();

    if( retCheckSimilarPassedThisDCY == (boolean)TRUE )
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */
    {
        /* Similar passed this DCY or DEM_SIMILAR_EVENT_CONFIGURED is STD_OFF */
        if( OpCycleUpdInfoPtr->CheckBitOldStatus.PendingDTC == (boolean)TRUE )
        {
            /* Bit2 in the case of ON */

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
            eventMisfireKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );    /* [GUD:RET:TRUE] EventStrgIndex */
            if( eventMisfireKind == (boolean)TRUE )
            {
                getExceedanceCounter = (Dem_u08_MisfExceedanceCounterType)0U;
                Dem_Misfire_GetExceedanceCounterToTmp( EventStrgIndex, &getExceedanceCounter ); /* [GUD]EventStrgIndex */
                if( getExceedanceCounter == (Dem_u08_MisfExceedanceCounterType)0U )
                {
                    /* If it has never been exceeded the specified percentage of misfire */
                    OpCycleUpdInfoPtr->ExecFlag.PendingRecoveryExec = (boolean)TRUE;

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                    /* In the case of Misfire Event */
                    Dem_Misfire_ProcessPendingFaultRecovery( EventStrgIndex );                  /* [GUD]EventStrgIndex */
#endif  /*   ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )     */
                }
            }
            else
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )           */
            {
                /*  similar evnet.              */
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                Dem_Similar_GetExceedanceCounterToTmp( &getSimilarExceedanceCounter );
                if( getSimilarExceedanceCounter == (Dem_u08_SimilarExceedanceCounterType)0U )
                {
                    OpCycleUpdInfoPtr->ExecFlag.PendingRecoveryExec = (boolean)TRUE;
                }
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */
            }
        }

        if( OpCycleUpdInfoPtr->ChkSpCond.Healing == (boolean)TRUE )
        {
            if( ( OpCycleUpdInfoPtr->ExecFlag.PendingRecoveryExec   == (boolean)FALSE )
             || ( OpCycleUpdInfoPtr->CheckBitOldStatus.ConfirmedDTC == (boolean)TRUE  ) )
            {
                execHealing =   Dem_Control_ProcessHealing( EventStrgIndex, &OpCycleUpdInfoPtr->OldDTCStatusSt, &OpCycleUpdInfoPtr->NewDTCStatusSt );   /* [GUDCHK:CALLER]EventStrgIndex */
            }
        }
    }

    return execHealing;
}

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_SimilarProcessPendingFaultRecovery           */
/* Description   | Process For Not Failed This Op Cycle (Ex.80DCY).         */
/* Preconditions | none                                                     */
/* Parameters    | [in]     EventStrgIndex :                                */
/*               | [in/out] OpCycleUpdInfoPtr :                             */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_SimilarProcessPendingFaultRecovery
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_OpCycleUpdInfoType, AUTOMATIC, AUTOMATIC ) OpCycleUpdInfoPtr
)
{
    VAR( boolean, AUTOMATIC ) chkPendingRecoveryPossible;
    VAR( boolean, AUTOMATIC ) chkPendEraseCycCnt;

    if( ( OpCycleUpdInfoPtr->ExecFlag.PendingRecoveryExec == (boolean)FALSE )
     && ( OpCycleUpdInfoPtr->ChkSpCond.PendErase          == (boolean)TRUE  ) )
    {
        /* Get config of SimilarOemIncrementType */
        chkPendingRecoveryPossible = Dem_Similar_CheckPendingRecoveryPossible();

        if( ( chkPendingRecoveryPossible                           == (boolean)FALSE  )
         || ( OpCycleUpdInfoPtr->CheckBitOldStatus.TestNotCompThisHealingCycle == (boolean)FALSE ) )
        {
            if( ( OpCycleUpdInfoPtr->CheckBitOldStatus.PendingDTC == (boolean)TRUE  )
             && ( OpCycleUpdInfoPtr->CheckBitOldStatus.WirStatus  == (boolean)FALSE ) )
            {
                /* Bit2 in the case of ON and Bit7 in the case of OFF */
                /* Check similar condition to carry out Pending Fault Recovery */
                chkPendEraseCycCnt = Dem_Similar_CheckReachedPendingEraseCycCntThreshold( EventStrgIndex );

                if( chkPendEraseCycCnt == (boolean)TRUE )
                {
                    OpCycleUpdInfoPtr->ExecFlag.PendingRecoveryExec = (boolean)TRUE;

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                    /* In the case of Misfire Event */
                    Dem_Misfire_ProcessPendingFaultRecovery( EventStrgIndex );
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )           */
                }
            }
        }
    }

    return;
}

#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
