/* Dem_Control_OpCycle_c(v5-6-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_OpCycle/CODE                                  */
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
#include "../../../inc/Dem_CmnLib_AsyncReq.h"
#include "../../../inc/Dem_CmnLib_AsyncReqTable.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_CmnLib_OpCycle.h"
#include "../../../inc/Dem_Pm_DTC_PFC.h"
#include "../../../inc/Dem_Pm_PID.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Pm_MonSts.h"
#include "../../../inc/Dem_Pm_IUMPR.h"
#include "../../../inc/Dem_Pm_AltIUMPR.h"
#include "../../../inc/Dem_Pm_OccrDTC.h"
#include "../../../inc/Dem_Pm_Ind_MI.h"
#include "../../../inc/Dem_Udm_Control.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../usr/Dem_NotifyOpCycleUpdate_Callout.h"
#include "../../../usr/Dem_SavedZone_Callout.h"

#include "../../../inc/Dem_CmnIf_Control.h"
#include "../../../inc/Dem_CmnLib_Control.h"
#include "Dem_Control_cmn_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_CTL_OPCYCLE_PROC_NONE       ((Dem_u08_OpCycleProcType)0x00U)
#define DEM_CTL_OPCYCLE_PROC_OC         ((Dem_u08_OpCycleProcType)0x11U)
#define DEM_CTL_OPCYCLE_PROC_FIM        ((Dem_u08_OpCycleProcType)0x22U)
#define DEM_CTL_OPCYCLE_PROC_COMPLETE   ((Dem_u08_OpCycleProcType)0x33U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>
static FUNC( void, DEM_CODE ) Dem_Control_EndOpCycUpd_GenerateOrderList
( void );
static FUNC( void, DEM_CODE ) Dem_Control_EndOpCycUpd_UpdateOpCycInfo
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) IGCycleUpdatedPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) OBDDCYQualifiedPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) WarmUpQualifiedPtr
);
#if ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Control_EndOpCycUpd_ExecJobsAtOpcycUpd
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex,
    VAR( boolean, AUTOMATIC ) IGCycleUpdated,
    VAR( boolean, AUTOMATIC ) OBDDCYQualified,
    VAR( boolean, AUTOMATIC ) WarmUpQualified
);
#endif  /* ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )    */
static FUNC( void, DEM_CODE ) Dem_Control_StoreCycleQualifiedUpdateFlag
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) StoreUpdatedInfoPtr,
    VAR( boolean, AUTOMATIC ) UpdatedInfo
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_RestartOpCycleProcess
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex,
    VAR( Dem_u16_EventPosType, AUTOMATIC ) UpdateEventMaxNumAtCycle
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_UpdateEventMemEntryByOpCycle
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex,
    VAR( Dem_u16_EventPosType, AUTOMATIC ) UpdateEventMaxNumAtCycle,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) NeedGenOrderListPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ExecHealingPtr
);
static FUNC( void, DEM_CODE ) Dem_Control_UpdEventKindMemEntryByOpCycle
(
    VAR( Dem_u16_EventPosType, AUTOMATIC ) EventPos,
    VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC ) HealingAgingCycleFlag,
    VAR( Dem_u08_OpcycUpdateFailureCycleType, AUTOMATIC ) FailureCycleFlag,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) NeedGenOrderListPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ExecHealingPtr
);

static FUNC( void, DEM_CODE ) Dem_Control_EndOperationCycleUpdate
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex
);
static FUNC( void, DEM_CODE ) Dem_Control_SetStartOfOpCycleStateInfo
( void );
static FUNC( void, DEM_CODE ) Dem_Control_StoreNeedGenOrderListFlag
(
    VAR( boolean, AUTOMATIC ) NeedGenOrderListFlag
);

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Control_ClearHealingExistsFlag /* MISRA DEVIATION */
( void );
static FUNC( void, DEM_CODE ) Dem_Control_StoreHealingExistFlag
(
    VAR( boolean, AUTOMATIC ) HealingEventExistsFlag
);
static FUNC( void, DEM_CODE ) Dem_Control_EndOfHealing
( void );
#endif /* DEM_PFC_ORDER_MIL_SUPPORT -STD_ON- */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_u08_OpCycleIndexType, DEM_VAR_NO_INIT )         Dem_CtlStoredOpCycleIndex;
static VAR( Dem_u16_EventPosType, DEM_VAR_NO_INIT )             Dem_CtlStoredEventPos;
static VAR( boolean, DEM_VAR_NO_INIT )                          Dem_CtlNeedGenFaultOrderListFlag;

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )
static VAR( boolean, DEM_VAR_NO_INIT )                          Dem_CtlHealingEventExistsFlag;
#endif /* DEM_PFC_ORDER_MIL_SUPPORT -STD_ON- */

static VAR( volatile Dem_u08_OpCycleProcType, DEM_VAR_NO_INIT )          Dem_CtlOpCycleProc;

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
/* Function Name | Dem_Control_RestartOperationCycle                        */
/* Description   | Restart the operation cycle.                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] OperationCycleId : Operation cycle identifier.      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |    DEM_IRT_OK : Success.                                 */
/*               |    DEM_IRT_NG : Failed.                                  */
/* Notes         | This function is in SW-C main process.                   */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_RestartOperationCycle
(
    VAR( Dem_u08_OperationCycleIdType, AUTOMATIC ) OperationCycleId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) setOpCycleIndex;

    retVal = DEM_IRT_NG;

    retTempVal = Dem_OpCycle_CheckOpCycleValue( OperationCycleId );
    if( retTempVal == DEM_IRT_OK )
    {
        setOpCycleIndex = (Dem_u16_AsyncReqItemAType)Dem_OpCycle_CnvOpCycleIdToOpCycleIndex( OperationCycleId );

        retTempVal = Dem_AsyncReq_JudgeReqCondition( DEM_ASYNCREQ_RESTART_OPCYCLE, setOpCycleIndex, DEM_ASYNCREQ_PARAM_STATUS_INVALID );
        if( retTempVal == DEM_IRT_OK )
        {
            retVal = Dem_AsyncReq_Enqueue( DEM_ASYNCREQ_RESTART_OPCYCLE, setOpCycleIndex, DEM_ASYNCREQ_PARAM_STATUS_INVALID );
#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )   /*  [FuncSw]    */
            if( retVal == DEM_IRT_OK )
            {
                Dem_MonSts_UpdateAllMonitorStatus();
            }
#endif  /*   ( DEM_TRIGGER_FIM_REPORTS == STD_ON )          */
        }
        else
        {
            /* When the result of request condition judgment is not OK */
            /* No process */
        }
    }
    else
    {
        /* No process */
    }

    return retVal;
}

/*--------------------------------------------------------------------------*/
/* Unit Internal functions -init process-                                   */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* Function Name | Dem_Control_RestartOpCycleInitProcess                    */
/* Description   | initialize processing function of RestartOperation-      */
/*               | Cycle.                                                   */
/* Preconditions | none                                                     */
/*               | [out] IGCycleUpdatedPtr : IG cycle updated or not.       */
/*               |                  TRUE    :   IG Cycle  updated           */
/*               |                  FALSE   :   IG Cycle isnot updated      */
/*               | [out] OBDDCYQualifiedPtr : OBDDCY cycle updated or not.  */
/*               |                  TRUE    :   OBDDCY Cycle  updated       */
/*               |                  FALSE   :   OBDDCY Cycle isnot updated  */
/*               | [out] WarmUpQualifiedPtr : WarmUp cycle updated or not.  */
/*               |                  TRUE    :   WarmUp Cycle  updated       */
/*               |                  FALSE   :   WarmUp Cycle isnot updated  */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]AltIUMPR                                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_RestartOpCycleInitProcess
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) IGCycleUpdatedPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) OBDDCYQualifiedPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) WarmUpQualifiedPtr
)
{
    VAR( Dem_u16_EventPosType, AUTOMATIC ) numOfAllEventConfigured;
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) opCycleIndex;
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) opCycleStartIndex;
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) opCycleTableMaxNum;
#if ( DEM_WWH_OBD_SUPPORT == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u08_OpCycleKindIndexType, AUTOMATIC ) thisCycleKindIndex;
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */
    VAR( boolean, AUTOMATIC ) needGenOrderList;
    VAR( boolean, AUTOMATIC ) execHealing;
    VAR( boolean, AUTOMATIC ) igCycleUpdated;
    VAR( boolean, AUTOMATIC ) drivingCycleQualified;
    VAR( boolean, AUTOMATIC ) warmUpCycleQualified;

    VAR( boolean, AUTOMATIC ) storedIGCycleUpdated;
    VAR( boolean, AUTOMATIC ) storedDrivingCycleQualified;
    VAR( boolean, AUTOMATIC ) storedWarmUpCycleQualified;

    VAR( boolean, AUTOMATIC ) opCycleAutoStart;

    needGenOrderList    =   (boolean)FALSE;
    execHealing         =   (boolean)FALSE;

    storedIGCycleUpdated               =   (boolean)FALSE;
    storedDrivingCycleQualified        =   (boolean)FALSE;
    storedWarmUpCycleQualified         =   (boolean)FALSE;
    numOfAllEventConfigured            =    Dem_CfgInfoCmn_GetMaxNumberOfAllMemoryEvent();      /*  number of configured event(all memory). */

#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )  /*  [FuncSw]    */
    Dem_AltIUMPR_GetPendingAndMIL();
#endif  /* ( DEM_ALTIUMPR_SUPPORT == STD_ON )   */

    /*======================================================================*/
    /*  Dem_NotifySavedZoneUpdate_Enter() is called at caller function.     */
    /*======================================================================*/


    /*  get Dem_OperationCycleTable access info.        */
    Dem_OpCycle_GetRestartOpCycleIndexAreaInOpCycleTable( &opCycleStartIndex, &opCycleTableMaxNum );

    /* For the first request, hold dequeued information inside */
    for ( opCycleIndex = opCycleStartIndex; opCycleIndex < opCycleTableMaxNum; opCycleIndex++ )                     /* [GUD:for]opCycleIndex */
    {
        /*  get operationcycle index.           */
        opCycleAutoStart    =   Dem_OpCycle_GetOperationCycleAutostart( opCycleIndex );                   /* [GUD]opCycleIndex */

        /*  AutoStart                           */
        if ( opCycleAutoStart == (boolean)TRUE )
        {
            /*  start of update operation cycle     */
            Dem_Control_SetStartOfOpCycleStateInfo();

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )  /*  [FuncSw]    */
            thisCycleKindIndex = Dem_OpCycle_GetThisCycleKindIndex( opCycleIndex );                                 /* [GUD]opCycleIndex */

            /* If DCY update, get time since engine start since last DCY */
            Dem_Control_JudgeAndGetTimeSinceEngineStartSinceLastDCY( thisCycleKindIndex );
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

            /*  update operation cycle              */
            (void)Dem_Control_UpdateEventMemEntryByOpCycle( opCycleIndex, numOfAllEventConfigured, &needGenOrderList, &execHealing );    /* no return check required *//*[UpdRec]AltIUMPR */

            /*  end of operation cycle restart.         */
            igCycleUpdated              =   (boolean)FALSE;
            drivingCycleQualified       =   (boolean)FALSE;
            warmUpCycleQualified        =   (boolean)FALSE;
            Dem_Control_EndOpCycUpd_UpdateOpCycInfo( opCycleIndex, &igCycleUpdated, &drivingCycleQualified, &warmUpCycleQualified );

            /*  stored info.                            */
            Dem_Control_StoreCycleQualifiedUpdateFlag( &storedIGCycleUpdated,        igCycleUpdated );
            Dem_Control_StoreCycleQualifiedUpdateFlag( &storedDrivingCycleQualified, drivingCycleQualified );
            Dem_Control_StoreCycleQualifiedUpdateFlag( &storedWarmUpCycleQualified,  warmUpCycleQualified );
        }
    }

    /*  after OrderList regenerated, call [Dem_Control_RestartOpCycleInitEndProcess].   */
    *IGCycleUpdatedPtr    =   storedIGCycleUpdated;
    *OBDDCYQualifiedPtr   =   storedDrivingCycleQualified;
    *WarmUpQualifiedPtr   =   storedWarmUpCycleQualified;

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Control_RestartOpCycleInitEndProcess                 */
/* Description   | initialize processing function of RestartOperation-      */
/*               | Cycle.                                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] IGCycleUpdated : IG cycle updated or not.           */
/*               |                  TRUE    :   IG Cycle  updated           */
/*               |                  FALSE   :   IG Cycle isnot updated      */
/*               | [in] OBDDCYQualified: OBDDCY cycle updated or not.       */
/*               |                  TRUE    :   OBDDCY Cycle  updated       */
/*               |                  FALSE   :   OBDDCY Cycle isnot updated  */
/*               | [in] WarmUpQualified: WarmUp cycle updated or not.       */
/*               |                  TRUE    :   WarmUp Cycle  updated       */
/*               |                  FALSE   :   WarmUp Cycle isnot updated  */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]IUMPR                                            */
/* UpdateRecord  | [UpdRec]AltIUMPR                                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_RestartOpCycleInitEndProcess
(
    VAR( boolean, AUTOMATIC ) IGCycleUpdated,    /* MISRA DEVIATION */
    VAR( boolean, AUTOMATIC ) OBDDCYQualified,   /* MISRA DEVIATION */
    VAR( boolean, AUTOMATIC ) WarmUpQualified    /* MISRA DEVIATION */
)
{
#if ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )  /* [FuncSw] */
    /*  end of update operation cycle.      */
    Dem_Control_EndOpCycUpd_ExecJobsAtOpcycUpd( DEM_OPERATION_CYCLE_INDEX_INVALID, IGCycleUpdated, OBDDCYQualified, WarmUpQualified );/* [UpdRec]IUMPR *//* [UpdRec]AltIUMPR */
#endif  /* ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )    */


#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
    if(( IGCycleUpdated != (boolean)TRUE ) || ( OBDDCYQualified != (boolean)TRUE ))
    {
        /*  update PFC record.          */
        Dem_DTC_UpdatePFCRecord();
    }
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )      */

#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
    if(( IGCycleUpdated != (boolean)TRUE ) || ( OBDDCYQualified != (boolean)TRUE ))
    {
        Dem_IndMI_UpdateB1Record();
    }
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

    /*  reset data.     */
    Dem_Control_InitInfoForOpCycleStart();

    /*======================================================================*/
    /*  Dem_NotifySavedZoneUpdate_Exit() is called at caller function.      */
    /*======================================================================*/


    return ;

}

/*--------------------------------------------------------------------------*/
/* Unit Internal functions -process-                                        */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Function Name | Dem_Control_RestartOpCycleFirstProcess                   */
/* Description   | Asynchronous processing function of RestartOperation-    */
/*               | Cycle.                                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] Index       : Operation cycle identifier.           */
/*               | [in] Status      :                                       */
/*               | [in] DataBuffPtr :                                       */
/* Return Value  | Dem_u08_AsyncExecReturnType                              */
/*               |       : See the description of the return value of       */
/*               |         "DemAsyncReqFncPTR" in Dem_Control_AsyncReq.h.   */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_RestartOpCycleFirstProcess
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,          /* [PRMCHK:CALLER] */
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,                     /* MISRA DEVIATION */
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr    /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retValOC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retValFim;
    VAR( Dem_u08_OpCycleProcType, AUTOMATIC ) opCycleProc;
#if ( DEM_WWH_OBD_SUPPORT == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u08_OpCycleKindIndexType, AUTOMATIC ) thisCycleKindIndex;
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */
    VAR( Dem_u16_EventPosType, AUTOMATIC ) opCycleBitByCycle;

    /* Set return value. */
    /* Fault record is not updated, No need re-generate orderlist, Exit asynchronous processing. */
    retVal = ( DEM_ASYNCRET_NOUPD_FR | DEM_ASYNCRET_NONEED_REGEN_ODR | DEM_ASYNCRET_EXIT_ASYNC_PROC );

    opCycleProc = DEM_CTL_OPCYCLE_PROC_OC;

#if ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )   /*  [FuncSw]    */
    Dem_OccrDTC_LatchOccrDTCRecord();
#endif  /*   ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )          */

    /* For the first request, hold dequeued information inside */
    Dem_Control_SetStartOfOpCycleStateInfo();

    /*  store restart operation cycle index.        */
    Dem_CtlStoredOpCycleIndex = ( Dem_u08_OpCycleIndexType )Index;

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )  /*  [FuncSw]    */
    thisCycleKindIndex = Dem_OpCycle_GetThisCycleKindIndex( Dem_CtlStoredOpCycleIndex );        /* [GUDCHK:CALLER]Index */

    /* If DCY update, get time since engine start since last DCY */
    Dem_Control_JudgeAndGetTimeSinceEngineStartSinceLastDCY( thisCycleKindIndex );
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )  /*  [FuncSw]    */
    Dem_AltIUMPR_GetPendingAndMIL();
#endif  /*   ( DEM_ALTIUMPR_SUPPORT == STD_ON ) */

    /*  Update operation cycle.         */
    opCycleBitByCycle = Dem_CtlInitThisOpCycleBitByCycle;
    retValOC = Dem_Control_RestartOpCycleProcess( Dem_CtlStoredOpCycleIndex, opCycleBitByCycle );
    if( retValOC != DEM_IRT_PENDING )
    {
        /* Set return value. */
        /* Fault record is updated, No need re-generate orderlist, Exit asynchronous processing. */
        retVal = ( DEM_ASYNCRET_UPD_FR | DEM_ASYNCRET_NONEED_REGEN_ODR | DEM_ASYNCRET_EXIT_ASYNC_PROC );

        opCycleProc = DEM_CTL_OPCYCLE_PROC_FIM;
        Dem_MonSts_ReCalcStart( (boolean)TRUE );

        retValFim = Dem_MonSts_ReCalcProc( DEM_MONSTS_RECALC_TYPE_OPERATIONCYCLE );
        if( retValFim != DEM_IRT_PENDING )
        {
            /* Because processing related to 1operation cycle is finished, initialize internal information */
            opCycleProc = DEM_CTL_OPCYCLE_PROC_NONE;
        }
    }
    else
    {
        /* Because processing was not finished within 1cycle, internal information is just as it is */
        /* No process */
    }

    Dem_CtlOpCycleProc = opCycleProc;

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_RestartOpCycleContinueProcess                */
/* Description   | Asynchronous processing function of RestartOperation-    */
/*               | Cycle.                                                   */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_AsyncExecReturnType :                            */
/*               |          See the description of the return value of      */
/*               |         "DemAsyncReqFncPTR" in Dem_Control_AsyncReq.h.   */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_RestartOpCycleContinueProcess
( void )
{
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retValOC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retValMonSts;
    VAR( Dem_u08_OpCycleProcType, AUTOMATIC ) opCycleProc;
    VAR( Dem_u16_EventPosType, AUTOMATIC ) opCycleBitByCycle;

    /* Set return value. */
    /* Fault record is not updated, No need re-generate orderlist, Exit asynchronous processing. */
    retVal = ( DEM_ASYNCRET_NOUPD_FR | DEM_ASYNCRET_NONEED_REGEN_ODR | DEM_ASYNCRET_EXIT_ASYNC_PROC );

    opCycleProc = Dem_CtlOpCycleProc;

    if( opCycleProc == DEM_CTL_OPCYCLE_PROC_OC )
    {
        /*  Update operation cycle.         */
        opCycleBitByCycle = Dem_CtlInitThisOpCycleBitByCycle;
        retValOC = Dem_Control_RestartOpCycleProcess( Dem_CtlStoredOpCycleIndex, opCycleBitByCycle );
        if( retValOC != DEM_IRT_PENDING )
        {
            /* Set return value. */
            /* Fault record is updated, No need re-generate orderlist, Exit asynchronous processing. */
            retVal = ( DEM_ASYNCRET_UPD_FR | DEM_ASYNCRET_NONEED_REGEN_ODR | DEM_ASYNCRET_EXIT_ASYNC_PROC );

            opCycleProc = DEM_CTL_OPCYCLE_PROC_FIM;
            Dem_MonSts_ReCalcStart( (boolean)TRUE );
        }
    }

    if( opCycleProc == DEM_CTL_OPCYCLE_PROC_FIM )
    {
        retValMonSts = Dem_MonSts_ReCalcProc( DEM_MONSTS_RECALC_TYPE_OPERATIONCYCLE );
        if( retValMonSts != DEM_IRT_PENDING )
        {
            opCycleProc = DEM_CTL_OPCYCLE_PROC_COMPLETE;
        }
    }

    if( opCycleProc == DEM_CTL_OPCYCLE_PROC_COMPLETE )
    {
        /* Because processing related to 1operation cycle is finished, initialize internal information */
        opCycleProc = DEM_CTL_OPCYCLE_PROC_NONE;
    }
    else
    {
        /* Because processing in 1cycle is not finished, internal information is just as it is */
        /* No process */
    }

    Dem_CtlOpCycleProc = opCycleProc;

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_RestartOpCycleProcess                        */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] OperationCycleIndex : Operation cycle index.        */
/*               | [in] UpdateEventMaxNumAtCycle :                          */
/*               |              update event number for update.             */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Setting state is done.               */
/*               |        DEM_IRT_NG : Setting state is failed.             */
/*               |        DEM_IRT_PENDING : Setting state is remained.      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]IUMPR    :   NotifySavedZone                     */
/* UpdateRecord  | [UpdRec]AltIUMPR :   NotifySavedZone                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_RestartOpCycleProcess
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex,
    VAR( Dem_u16_EventPosType, AUTOMATIC ) UpdateEventMaxNumAtCycle
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retUpdateEventMemoryEntryByOC;
    VAR( boolean, AUTOMATIC ) needGenOrderList;
    VAR( boolean, AUTOMATIC ) execHealing;

    retVal = DEM_IRT_NG;
    needGenOrderList   =   (boolean)FALSE;
    execHealing         =   (boolean)FALSE;

    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - start.   */
    Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
#if ( DEM_IUMPR_SUPPORT == STD_ON ) /*  [FuncSw]    */
    Dem_NotifySavedZoneIUMPRUpdate_Enter(); /*  notify start :  IUMPR/AltIUMPR savedzone area will be update.  */
#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )          */
    /*--------------------------------------*/

    /* When operation cycle bit initialization of DTC status is necessary */
    retUpdateEventMemoryEntryByOC = Dem_Control_UpdateEventMemEntryByOpCycle( OperationCycleIndex, UpdateEventMaxNumAtCycle, &needGenOrderList, &execHealing ); /* [UpdRec]AltIUMPR *//* [UpdRec]more */

    /*  store information : delete FaultRecord or not.      */
    Dem_Control_StoreNeedGenOrderListFlag( needGenOrderList );
#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )    /* [FuncSw] */
    Dem_Control_StoreHealingExistFlag( execHealing );
#endif /* DEM_PFC_ORDER_MIL_SUPPORT -STD_ON- */

    if( retUpdateEventMemoryEntryByOC == DEM_IRT_OK )
    {
        Dem_Control_EndOperationCycleUpdate( OperationCycleIndex );     /* [UpdRec]IUMPR *//* [UpdRec]AltIUMPR *//* [UpdRec]more */
        retVal = DEM_IRT_OK;
    }
    else if( retUpdateEventMemoryEntryByOC == DEM_IRT_PENDING )
    {
        /* DTC initialization of the event related to 1operation cycle is remained */
        retVal = DEM_IRT_PENDING;
    }
    else
    {
        /* Errors occur in DTC initialization of the event related to 1operation cycle */
        /* No process */
    }

    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - end.     */
#if ( DEM_IUMPR_SUPPORT == STD_ON ) /*  [FuncSw]    */
    Dem_NotifySavedZoneIUMPRUpdate_Exit();  /*  notify end :  IUMPR/AltIUMPR savedzone area will be update.  */
#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )          */
    Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
    /*--------------------------------------*/

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_UpdateEventMemEntryByOpCycle                 */
/* Description   | Loop for update EventMemoryEntry of operation cycle .    */
/* Preconditions | none                                                     */
/* Parameters    | [in] OperationCycleIndex : Operation cycle index.        */
/*               | [in] UpdateEventMaxNumAtCycle :                          */
/*               |              update event number for restart cycle.      */
/*               | [out] NeedGenOrderListPtr :                              */
/*               |              need GenOrderList or not.                   */
/*               |                  TRUE    :   need generate .             */
/*               |                  FALSE   :   no need generate .          */
/*               | [out] ExecHealingPtr :                                   */
/*               |              execute healing or not.                     */
/*               |                  TRUE    :   execute healing.            */
/*               |                  FALSE   :   no execute healing.         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : updating EventMemoryEntry of operat- */
/*               |                     ion cycle is done.                   */
/*               |        DEM_IRT_PENDING : remains updating EventMemoryEn- */
/*               |                          try of operation cycle.         */
/*               |        DEM_IRT_NG : error                                */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]AltIUMPR                                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_UpdateEventMemEntryByOpCycle
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex,
    VAR( Dem_u16_EventPosType, AUTOMATIC ) UpdateEventMaxNumAtCycle,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) NeedGenOrderListPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ExecHealingPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetNextEventPos;
    VAR( Dem_u16_EventPosType, AUTOMATIC ) nextEventPos;
    VAR( Dem_u16_EventPosType, AUTOMATIC ) loopCount;
    VAR( boolean, AUTOMATIC ) needGenOrderList;
    VAR( boolean, AUTOMATIC ) execHealing;
    VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC ) healingAgingCycleFlag;
    VAR( Dem_u08_OpcycUpdateFailureCycleType, AUTOMATIC ) failureCycleFlag;

    retVal = DEM_IRT_NG;
    retGetNextEventPos = DEM_IRT_NG;

    for( loopCount = (Dem_u16_EventPosType)0U; loopCount < UpdateEventMaxNumAtCycle; loopCount++ )
    {
        nextEventPos            = DEM_EVENTPOS_INVALID;
        healingAgingCycleFlag   = DEM_OPCYCUPD_HACYC_INITIALVALUE;
        failureCycleFlag        = DEM_OPCYCUPD_FLCYC_INITIALVALUE;

        retGetNextEventPos = Dem_OpCycle_GetNextEventPosByOperationCycleIndex( OperationCycleIndex, Dem_CtlStoredEventPos, &nextEventPos, &healingAgingCycleFlag, &failureCycleFlag );  /* [GUD:RET:DEM_IRT_OK] nextEventPos */
        if( retGetNextEventPos == DEM_IRT_OK )
        {
            Dem_CtlStoredEventPos = nextEventPos;
            needGenOrderList    =   (boolean)FALSE;
            execHealing         =   (boolean)FALSE;

            /*  update eventmemory entry by event kind.     */
            Dem_Control_UpdEventKindMemEntryByOpCycle( nextEventPos, healingAgingCycleFlag, failureCycleFlag, &needGenOrderList, &execHealing );    /* [GUD]nextEventPos *//* [UpdRec]AltIUMPR */

            *NeedGenOrderListPtr    =   *NeedGenOrderListPtr | needGenOrderList;
            *ExecHealingPtr         =   *ExecHealingPtr  | execHealing;
        }
        else
        {
            /* Except DEM_IRT_OK (DEM_IRT_NO_MACHING_ELEMENT/DEM_IRT_NG), break loop because EventIndex cannot be obtained */
            Dem_CtlStoredEventPos = DEM_EVENTPOS_INVALID;
            break;
        }
    }

    switch( retGetNextEventPos )
    {
        case DEM_IRT_OK:
            /* There is an even of which operation cycle bit initialization of DTC status is unfinished */
            retVal = DEM_IRT_PENDING;
            break;
        case DEM_IRT_NO_MATCHING_ELEMENT:
            /* Operation cycle bit initialization of DTC status of all events is finished */
            retVal = DEM_IRT_OK;
            break;
        default:
            /* No process */
            break;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_UpdEventKindMemEntryByOpCycle                */
/* Description   | update EventMemoryEntry of operation cycle .             */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventPos                                           */
/*               |                                                          */
/*               | [in] HealingAgingCycleFlag :                             */
/*               |              check HealingAgingCycle or not.             */
/*               | [in] FailureCycleFlag :                                  */
/*               |              check FailureCycle or not.                  */
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
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_UpdEventKindMemEntryByOpCycle
(
    VAR( Dem_u16_EventPosType, AUTOMATIC ) EventPos,                /* [PRMCHK:CALLER] */
    VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC ) HealingAgingCycleFlag,
    VAR( Dem_u08_OpcycUpdateFailureCycleType, AUTOMATIC ) FailureCycleFlag,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) NeedGenOrderListPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ExecHealingPtr
)
{
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    VAR( Dem_u08_MemoryKindType, AUTOMATIC ) memKind;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;

    /*  convert event position to event index       */
    eventCtrlIndex  =   Dem_CfgInfoCmn_CnvEventPosToEventCtrlIndex( EventPos );
    memKind         =   Dem_CfgInfoCmn_CheckMemoryTypeFromEventCtrlIndex( eventCtrlIndex );                 /* [GUD:RET:Not DEM_MEMKIND_PRIMARY]EventPos(UdmEventIndex) */
    if ( memKind != DEM_MEMKIND_PRIMARY )
    {
        /*  UserDefinedMemory.  */
        Dem_UdmControl_NormalEventMemoryEntryByOpCycle( EventPos, HealingAgingCycleFlag, FailureCycleFlag, NeedGenOrderListPtr, ExecHealingPtr );   /* [GUD]EventPos(UdmEventIndex) */
    }
    else
#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */
    {
        /*  PrimaryMemory.      */
        Dem_Control_UpdateEventMemEntryByOpCycle_PrimaryMemory( EventPos, HealingAgingCycleFlag, FailureCycleFlag, NeedGenOrderListPtr, ExecHealingPtr );   /* [GUDCHK:CALLER]EventPos *//* [UpdRec]AltIUMPR */
    }
    return ;
}


/****************************************************************************/
/* Function Name | Dem_Control_EndOperationCycleUpdate                      */
/* Description   | End processing of operation cycle update.                */
/* Preconditions | none                                                     */
/* Parameters    | [in] OperationCycleIndex : Operation cycle index         */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]IUMPR                                            */
/* UpdateRecord  | [UpdRec]AltIUMPR                                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_EndOperationCycleUpdate
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex
)
{
    VAR( boolean, AUTOMATIC ) igCycleUpdated;
    VAR( boolean, AUTOMATIC ) drivingCycleQualified;
    VAR( boolean, AUTOMATIC ) warmUpCycleQualified;

    /*  generate order list         */
    Dem_Control_EndOpCycUpd_GenerateOrderList();

    /*  update IGcycle info         */
    igCycleUpdated          =   (boolean)FALSE;
    drivingCycleQualified   =   (boolean)FALSE;
    warmUpCycleQualified    =   (boolean)FALSE;
    Dem_Control_EndOpCycUpd_UpdateOpCycInfo( OperationCycleIndex, &igCycleUpdated, &drivingCycleQualified, &warmUpCycleQualified );

#if ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )  /* [FuncSw] */
    /*  Exec jobs at OBDDCY cycle updated.  */
    Dem_Control_EndOpCycUpd_ExecJobsAtOpcycUpd( OperationCycleIndex, igCycleUpdated, drivingCycleQualified, warmUpCycleQualified );/* [UpdRec]IUMPR *//* [UpdRec]AltIUMPR */
#endif  /* ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )    */

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Control_EndOpCycUpd_GenerateOrderList                */
/* Description   | End processing of operation cycle update.                */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_EndOpCycUpd_GenerateOrderList
( void )
{
    if( Dem_CtlNeedGenFaultOrderListFlag == (boolean)TRUE )
    {
        Dem_Data_GenerateFaultOrderList();

#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )   /* [FuncSw] */
        Dem_Data_GenerateConfirmedFaultOrderList();
#endif  /*   ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )      */

#if ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )   /* [FuncSw] */
        /* Update OccrDTCRecord */
        Dem_OccrDTC_UpdateOccrDTCRecord();
#endif  /*   ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )      */

        Dem_Data_ClearSearchFFDIndex();
    }

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )    /* [FuncSw] */
    /*  end of healing process      */
    Dem_Control_EndOfHealing();
#endif /* DEM_PFC_ORDER_MIL_SUPPORT -STD_ON- */

    return ;
}


#if ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_EndOpCycUpd_UpdateOpCycInfo                  */
/* Description   | End processing of operation cycle update.                */
/* Preconditions | none                                                     */
/* Parameters    | [in] OperationCycleIndex : Operation cycle index         */
/*               | [out] IGCycleUpdatedPtr : IG cycle updated or not.       */
/*               |                  TRUE    :   IG Cycle  updated           */
/*               |                  FALSE   :   IG Cycle isnot updated      */
/*               | [out] OBDDCYQualifiedPtr : OBDDCY cycle updated or not.  */
/*               |                  TRUE    :   OBDDCY Cycle  updated       */
/*               |                  FALSE   :   OBDDCY Cycle isnot updated  */
/*               | [out] WarmUpQualifiedPtr : WarmUp cycle updated or not.  */
/*               |                  TRUE    :   WarmUp Cycle  updated       */
/*               |                  FALSE   :   WarmUp Cycle isnot updated  */
/* Return Value  | void                                                     */
/* Notes         | call at one operation cycle updated.                     */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_EndOpCycUpd_UpdateOpCycInfo
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) IGCycleUpdatedPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) OBDDCYQualifiedPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) WarmUpQualifiedPtr
)
{
    VAR( Dem_u08_OperationCycleIdType, AUTOMATIC ) operationCycleId;
    VAR( boolean, AUTOMATIC ) igCycleUpdated;
    VAR( boolean, AUTOMATIC ) drivingCycleQualified;
    VAR( boolean, AUTOMATIC ) warmUpCycleQualified;

    igCycleUpdated          =   (boolean)FALSE;
    drivingCycleQualified   =   (boolean)FALSE;
    warmUpCycleQualified    =   (boolean)FALSE;

    /*  get operationcycle id.              */
    operationCycleId        =   Dem_OpCycle_CnvOpCycleIndexToId( OperationCycleIndex );

    /*  get qualified info.                 */
    Dem_OpCycle_GetIGCycleQualified( OperationCycleIndex, &igCycleUpdated, &drivingCycleQualified, &warmUpCycleQualified );

    /*  notify opeationcycle updated.       */
    Dem_NotifyOperationCycleUpdated( operationCycleId, drivingCycleQualified, warmUpCycleQualified );

    *IGCycleUpdatedPtr    =   igCycleUpdated;
    *OBDDCYQualifiedPtr   =   drivingCycleQualified;
    *WarmUpQualifiedPtr   =   warmUpCycleQualified;

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Control_EndOpCycUpd_ExecJobsAtOpcycUpd               */
/* Description   | End processing of operation cycle update.                */
/* Preconditions | Regenerated orderlist.(for Dem_DTC_UpdatePFCRecord()).   */
/* Parameters    | [in] OperationCycleIndex : Operation cycle index         */
/*               | [in] IGCycleUpdated : IG cycle updated or not.           */
/*               |                  TRUE    :   IG Cycle  updated           */
/*               |                  FALSE   :   IG Cycle isnot updated      */
/*               | [in] OBDDCYQualified: OBDDCY cycle updated or not.       */
/*               |                  TRUE    :   OBDDCY Cycle  updated       */
/*               |                  FALSE   :   OBDDCY Cycle isnot updated  */
/*               | [in] WarmUpQualified: WarmUp cycle updated or not.       */
/*               |                  TRUE    :   WarmUp Cycle  updated       */
/*               |                  FALSE   :   WarmUp Cycle isnot updated  */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]IUMPR                                            */
/* UpdateRecord  | [UpdRec]AltIUMPR                                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_EndOpCycUpd_ExecJobsAtOpcycUpd
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex,     /* MISRA DEVIATION */
    VAR( boolean, AUTOMATIC ) IGCycleUpdated,
    VAR( boolean, AUTOMATIC ) OBDDCYQualified,
    VAR( boolean, AUTOMATIC ) WarmUpQualified
)
{
#if ( DEM_ENGINETYPE_COMPRESSION_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) retChkOperationCycleIndex;

    /* check operation cycle id. */
    retChkOperationCycleIndex = Dem_OpCycle_Check4hDCY( OperationCycleIndex );

    if( retChkOperationCycleIndex == (boolean)TRUE )
    {
#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
        /*  update PFC record.          */
        Dem_DTC_UpdatePFCRecord();
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )      */

        /* 4hDCY is not use in WWHOBD */

#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )  /*  [FuncSw]    */
        /* IncDenominator */
        Dem_AltIUMPR_IncDenominatorProccess();      /* [UpdRec]AltIUMPR */
#endif  /* ( DEM_ALTIUMPR_SUPPORT == STD_ON )   */

#if ( DEM_IUMPR_SUPPORT == STD_ON ) /*  [FuncSw]    */
        /*  clear IUMPR condition.          */
        Dem_IUMPR_ClearIUMPRCondition();            /*[UpdRec]IUMPR */
#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )          */

#if ( DEM_CHECK_4000RPMOCCURRED_BY_EMISSION_SUPPORT == STD_ON ) /*  [FuncSw]    */
        /*  clear progress engine rpm condition.    */
        Dem_OpCycle_ClearProgressEngine1000RPM();
#endif  /* ( DEM_CHECK_4000RPMOCCURRED_BY_EMISSION_SUPPORT == STD_ON )          */
    }
    else
#endif  /*   ( DEM_ENGINETYPE_COMPRESSION_SUPPORT == STD_ON )           */
    {
        /*  Operation cycle update      */
        if( IGCycleUpdated == (boolean)TRUE )
        {
            /*==============================*/
            /*  IG cycle updated.           */
            /*==============================*/


            if( OBDDCYQualified == (boolean)TRUE )
            {
                /*==============================*/
                /*  Driving cycle updated.      */
                /*==============================*/

#if ( DEM_PID_WARMUPCYC_SUPPORT == STD_ON )   /*  [FuncSw]    */
                /*------------------------------*/
                /*  enter PID exclusion         */
                /*------------------------------*/
                /* Starts exclusion. */
                SchM_Enter_Dem_PID();

                /*  reset cycle qualified ata driving cycle updated.        */
                Dem_OpCycle_ResetObdDcyCycleQualified();

                /*  warmup cycle                */
                if( WarmUpQualified == (boolean)TRUE )
                {
                    /*==============================*/
                    /*  WarmUp cycle updated.       */
                    /*==============================*/
                    Dem_PID_UpdateDataOfPID30();
                }
                /*------------------------------*/
                /*  exit PID exclusion          */
                /*------------------------------*/
                /* Finishes exclusion. */
                SchM_Exit_Dem_PID();
#endif  /*   ( DEM_PID_WARMUPCYC_SUPPORT == STD_ON )      */

#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
                /*  update PFC record.          */
                Dem_DTC_UpdatePFCRecord();
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )      */

#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
                Dem_IndMI_UpdateB1Record();
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )  /*  [FuncSw]    */
                /* IncDenominator */
                Dem_AltIUMPR_IncDenominatorProccess();      /* [UpdRec]AltIUMPR */
#endif  /* ( DEM_ALTIUMPR_SUPPORT == STD_ON )   */

#if ( DEM_IUMPR_SUPPORT == STD_ON ) /*  [FuncSw]    */
                /*  clear IUMPR condition.          */
                Dem_IUMPR_ClearIUMPRCondition();            /*[UpdRec]IUMPR */
#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )          */

#if ( DEM_CHECK_4000RPMOCCURRED_BY_EMISSION_SUPPORT == STD_ON ) /*  [FuncSw]    */
                /*  clear progress engine rpm condition.    */
                Dem_OpCycle_ClearProgressEngine1000RPM();
#endif  /* ( DEM_CHECK_4000RPMOCCURRED_BY_EMISSION_SUPPORT == STD_ON )          */

            }
#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
            Dem_DTC_SetPFCClearDisable( (boolean)FALSE );
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )          */
        }
    }
    return ;
}

#endif /* DEM_CYCLEQUALIFIED_SUPPORT -STD_ON- */

#if ( DEM_CYCLEQUALIFIED_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_Control_EndOpCycUpd_UpdateOpCycInfo                  */
/* Description   | End processing of operation cycle update.                */
/* Preconditions | none                                                     */
/* Parameters    | [in] OperationCycleIndex : Operation cycle index         */
/*               | [out] IGCycleUpdatedPtr : IG cycle updated or not.       */
/*               |                  TRUE    :   IG Cycle  updated           */
/*               |                  FALSE   :   IG Cycle isnot updated      */
/*               | [out] OBDDCYQualifiedPtr : OBDDCY cycle updated or not.  */
/*               |                  TRUE    :   OBDDCY Cycle  updated       */
/*               |                  FALSE   :   OBDDCY Cycle isnot updated  */
/*               | [out] WarmUpQualifiedPtr : WarmUp cycle updated or not.  */
/*               |                  TRUE    :   WarmUp Cycle  updated       */
/*               |                  FALSE   :   WarmUp Cycle isnot updated  */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_EndOpCycUpd_UpdateOpCycInfo
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) IGCycleUpdatedPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) OBDDCYQualifiedPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) WarmUpQualifiedPtr
)
{
    VAR( Dem_u08_OperationCycleIdType, AUTOMATIC ) operationCycleId;
    operationCycleId        =   Dem_OpCycle_CnvOpCycleIndexToId( OperationCycleIndex );

    /*  notify opeationcycle updated.       */
    Dem_NotifyOperationCycleUpdated( operationCycleId, (boolean)FALSE, (boolean)FALSE );

    *IGCycleUpdatedPtr    =   (boolean)FALSE;
    *OBDDCYQualifiedPtr   =   (boolean)FALSE;
    *WarmUpQualifiedPtr   =   (boolean)FALSE;

    return ;
}

#endif /* DEM_CYCLEQUALIFIED_SUPPORT -STD_OFF- */

/*--------------------------------------------------------------------------*/
/* Unit Internal functions -data-                                           */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Function Name | Dem_Control_InitInfoForOpCycleStart                      */
/* Description   | Initializes info for operation cycle start.              */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_InitInfoForOpCycleStart
( void )
{
    Dem_CtlOpCycleProc = DEM_CTL_OPCYCLE_PROC_NONE;

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Control_SetOpCycleStateInfo                          */
/* Description   | Initializes index info for init DTC status bit of        */
/*               | operation cycle.                                         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_SetStartOfOpCycleStateInfo
( void )
{
    Dem_CtlStoredEventPos           = DEM_EVENTPOS_INVALID;

    Dem_CtlNeedGenFaultOrderListFlag    =   (boolean)FALSE;

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )    /* [FuncSw] */
    Dem_Control_ClearHealingExistsFlag();
#endif /* DEM_PFC_ORDER_MIL_SUPPORT -STD_ON- */

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Control_GetOpCycleUpdateState                        */
/* Description   | Gets operation cycle prosess state.                      */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Setting state is done.               */
/*               |        DEM_IRT_PENDING : Setting state is remained.      */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetOpCycleUpdateState
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_OpCycleProcType, AUTOMATIC ) opCycleProc;

    retVal = DEM_IRT_OK;
    opCycleProc = Dem_CtlOpCycleProc;

    if( opCycleProc != DEM_CTL_OPCYCLE_PROC_NONE )
    {
        retVal = DEM_IRT_PENDING;
    }
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_StoreCycleQualifiedUpdateFlag                */
/* Description   | store update flag.                                       */
/* Preconditions | none                                                     */
/*               | [inout] StoreIGCycleUpdatedPtr : store info.             */
/*               | [in]    UpdatedInfo :  updated info.                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_StoreCycleQualifiedUpdateFlag
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) StoreUpdatedInfoPtr,
    VAR( boolean, AUTOMATIC ) UpdatedInfo
)
{
    /*  store healing exist flag.       */
    *StoreUpdatedInfoPtr     =   *StoreUpdatedInfoPtr | UpdatedInfo;

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Control_StoreNeedGenOrderListFlag                    */
/* Description   | Reset Healing event exists.                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] NeedGenOrderListFlag  : Function to set delete      */
/*               |                              fault record Exists Flag.   */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_StoreNeedGenOrderListFlag
(
    VAR( boolean, AUTOMATIC ) NeedGenOrderListFlag
)
{
    /*  store healing exist flag.       */
    Dem_CtlNeedGenFaultOrderListFlag   =   Dem_CtlNeedGenFaultOrderListFlag | NeedGenOrderListFlag;

    return ;
}


#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_ClearHealingExistsFlag                       */
/* Description   | Reset Healing event exists.                              */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/*               |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_ClearHealingExistsFlag
( void )
{
    Dem_CtlHealingEventExistsFlag = (boolean)FALSE;
    return ;
}

/****************************************************************************/
/* Function Name | Dem_Control_StoreHealingExistFlag                        */
/* Description   | Reset Healing event exists.                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] HealingEventExistsFlag : Function to set healing Ex-*/
/*               |                               ists Exists Flag.          */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_StoreHealingExistFlag
(
    VAR( boolean, AUTOMATIC ) HealingEventExistsFlag
)
{
    /*  store healing exist flag.       */
    Dem_CtlHealingEventExistsFlag   =   Dem_CtlHealingEventExistsFlag | HealingEventExistsFlag;

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Control_EndOfHealing                                 */
/* Description   | Complete process of Healing.                             */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_EndOfHealing
( void )
{
    if( Dem_CtlHealingEventExistsFlag == (boolean)TRUE )
    {
        Dem_Data_GenerateMILFaultOrderList();
    }

    return ;
}

#endif /* DEM_PFC_ORDER_MIL_SUPPORT -STD_ON- */

/****************************************************************************/
/* Function Name | Dem_Control_OpCycle_RefreshRAM                           */
/* Description   | Refresh RAM  - Control                                   */
/* Preconditions | None                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | Called from Dem_MainFunction                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_OpCycle_RefreshRAM
( void )
{
    VAR( volatile Dem_u08_OpCycleProcType, AUTOMATIC )                      u8_dummyStatus;      /*  for store GlobalVariable data    */
    P2VAR( volatile Dem_u08_OpCycleProcType, AUTOMATIC, DEM_VAR_NO_INIT )   u8_dummyStatusPtr;   /*  for GlobalVariable address       */

    /* Exclusion is necessary       */
    u8_dummyStatusPtr   = &Dem_CtlOpCycleProc;
    u8_dummyStatus      = *u8_dummyStatusPtr;               /*  read GlobalVariable data    */
    *u8_dummyStatusPtr  = u8_dummyStatus;                   /*  rewrite GlobalVariable data */

    return ;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
