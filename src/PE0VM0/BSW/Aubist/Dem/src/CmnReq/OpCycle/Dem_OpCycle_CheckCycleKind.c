/* Dem_OpCycle_CheckCycleKind_c(v5-5-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dem_OpCycle_CheckCycleKind/CODE                       */
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
#include "../../../cfg/Dem_OpCycle_Cfg.h"
#include "../../../inc/Dem_CmnLib_OpCycle.h"
#include "../../../inc/Dem_Rc_OpCycleMng.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "Dem_OpCycle_CycleKindTable.h"
#include "Dem_OpCycle_OpCycTable.h"

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

static FUNC( boolean, DEM_CODE ) Dem_OpCycle_CheckMatchOfTargetUpdCycle
(
    VAR( Dem_u16_EventPosType, AUTOMATIC ) EventPos,
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC )  ThisCycleIndex,
    VAR( Dem_u08_OpCycleKindType, AUTOMATIC )   ThisCycleKind,
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) ObdDcyCycleState,
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) WarmUpCycleState,
    P2VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC, AUTOMATIC ) HealingAgingCycleFlagPtr,
    P2VAR( Dem_u08_OpcycUpdateFailureCycleType, AUTOMATIC, AUTOMATIC ) FailureCycleFlagPtr
);
static FUNC( Dem_u08_OpcycUpdateHealingAgingCycleType, DEM_CODE ) Dem_OpCycle_CheckMatchOfTargetHealingAgingCycle
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC )  TargetCycleIndex,
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC )  ThisCycleIndex,
    VAR( Dem_u08_OpCycleKindType, AUTOMATIC )   ThisCycleKind,
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) ObdDcyCycleState,
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) WarmUpCycleState
);
static FUNC( Dem_u08_OpcycUpdateFailureCycleType, DEM_CODE ) Dem_OpCycle_CheckMatchOfTargetFailureCycle
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC )  TargetCycleIndex,
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC )  ThisCycleIndex,
    VAR( Dem_u08_OpCycleKindType, AUTOMATIC )   ThisCycleKind,
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) ObdDcyCycleState,
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) WarmUpCycleState
);


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
/* Function Name | Dem_OpCycle_GetNextEventPosByOperationCycleIndex         */
/* Description   | Get an event position for the next update from an index  */
/*               | for an operation cycle.                                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] OperationCycleIndex : Operation cycle index.        */
/*               | [in] CycleState : Base event position.                   */
/*               | [out] NextEventIndexPtr : Next event position.           */
/*               | [out] HealingAgingCycleFlagPtr :                         */
/*               |              check HealingAgingCycle or not.             */
/*               | [out] FailureCycleFlagPtr :                              */
/*               |              check FailureCycle or not.                  */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Event position get success.          */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT :                     */
/*               |          The next event position does not exist.         */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] NextEventPosPtr                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OpCycle_GetNextEventPosByOperationCycleIndex
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex,
    VAR( Dem_u16_EventPosType, AUTOMATIC ) BaseEventPos,
    P2VAR( Dem_u16_EventPosType, AUTOMATIC, AUTOMATIC ) NextEventPosPtr,
    P2VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC, AUTOMATIC ) HealingAgingCycleFlagPtr,
    P2VAR( Dem_u08_OpcycUpdateFailureCycleType, AUTOMATIC, AUTOMATIC ) FailureCycleFlagPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventPosType, AUTOMATIC ) eventPos;
    VAR( Dem_u16_EventPosType, AUTOMATIC ) numOfAllEventConfigured;
    VAR( boolean, AUTOMATIC ) loopEndFlag;
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) obdDcyCycleState;
    VAR( Dem_u08_OpCycleKindType, AUTOMATIC ) opcycKind;
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) opcycObdDcy;
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) opcycWarmUp;
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) obdWarmUpState;

    /* Initializes the return value to OK. */
    retVal = DEM_IRT_OK;

    numOfAllEventConfigured = Dem_CfgInfoCmn_GetMaxNumberOfAllMemoryEvent();

    /* Checks whether the specified based event position is initial value. */
    if( BaseEventPos == DEM_EVENTPOS_INVALID )
    {
        /* The specified based event position is initial value. */

        /* Sets the event position to 0. */
        eventPos = DEM_EVENTPOS_MIN;       /*  start of event position. */
    }
    else
    {
        /* The specified based event position is not initial value. */

        /* Sets the event position to based event position plus one. */
        eventPos = ( BaseEventPos + (Dem_u16_EventPosType)1U );
    }

    /*  get opcycle kind.       */
    opcycKind   =   Dem_OpCycle_GetOperationCycleTypeMember( OperationCycleIndex );

    /*  get OBD_DCY start state.            */
    opcycObdDcy =   Dem_ConfDemOperationCycleObdDcy;
    obdDcyCycleState = Dem_OpCycleMng_GetCycleState( opcycObdDcy );

    /*  get WarmUp state.           */
    opcycWarmUp =   Dem_ConfDemOperationCycleWarmUp;
    obdWarmUpState = Dem_OpCycleMng_GetCycleState( opcycWarmUp );

    /* Loops until the event position gets max value.  */
    for( ; eventPos < numOfAllEventConfigured; eventPos++ )     /* [GUD:for]eventPos */
    {
        /*  check target cycle or not.      */
        loopEndFlag =   Dem_OpCycle_CheckMatchOfTargetUpdCycle( eventPos, OperationCycleIndex, opcycKind, obdDcyCycleState, obdWarmUpState, HealingAgingCycleFlagPtr, FailureCycleFlagPtr );    /* [GUD]eventPos */

        if( loopEndFlag == (boolean)TRUE )
        {
            break;
        }
    }

    /* Checks whether the event position keeps within the range. */
    if( eventPos < numOfAllEventConfigured )
    {
        /* Witnin the range. (Same record number has found.) */

        /* Stores the specified next event position storage area to initial value. */
        *NextEventPosPtr = eventPos;
    }
    else
    {
        /* Out of the range. */

        /* Stores the specified next event position storage area to initial value. */
        *NextEventPosPtr = DEM_EVENTPOS_INVALID;

        /* Sets return value to no matching element. */
        retVal = DEM_IRT_NO_MATCHING_ELEMENT;
    }

    /* Returns with the result. */
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_OpCycle_CheckMatchOfTargetUpdCycle                   */
/* Description   | Check if this cycle is the HealingAging cycle            */
/*               | for the specified event                                  */
/* Preconditions |                                                          */
/* Parameters    | [in]  EventPos                                           */
/*               | [in]  ThisCycleIndex                                     */
/*               | [in]  ThisCycleKind                                      */
/*               | [in]  ObdDcyCycleState                                   */
/*               | [in]  WarmUpCycleState                                   */
/*               | [out] HealingAgingCycleFlagPtr :                         */
/*               |              check HealingAgingCycle or not.             */
/*               | [out] FailureCycleFlagPtr :                              */
/*               |              check FailureCycle or not.                  */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : this is HealingAging cycle                */
/*               |                  or failer cycle for event.              */
/*               |        FALSE : this is not HealingAging cycle            */
/*               |                  or failer cycle for event.              */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_OpCycle_CheckMatchOfTargetUpdCycle
(
    VAR( Dem_u16_EventPosType, AUTOMATIC ) EventPos,                            /* [PRMCHK:CALLER] */
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC )  ThisCycleIndex,
    VAR( Dem_u08_OpCycleKindType, AUTOMATIC )   ThisCycleKind,
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) ObdDcyCycleState,
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) WarmUpCycleState,
    P2VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC, AUTOMATIC ) HealingAgingCycleFlagPtr,
    P2VAR( Dem_u08_OpcycUpdateFailureCycleType, AUTOMATIC, AUTOMATIC ) FailureCycleFlagPtr
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC ) retChkHealingAgingCycle;
    VAR( Dem_u08_OpcycUpdateFailureCycleType, AUTOMATIC ) retChkOperationCycle;
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) targetOpcycIndex;
    VAR( Dem_u08_OpCycleKindType, AUTOMATIC ) targetHealingAgingCycleIndex;

    /* The operation cycle's reference of the event table corresponding to the event position */
    /* is equal to the specified operation cycle index ? */
    /*  get target cycle index.         */
    targetOpcycIndex = Dem_CfgInfoCmn_GetEventOperationCycleRef( EventPos );                    /* [GUDCHK:CALLER]EventPos */

    /*  get HealingAging cycle.       */
    targetHealingAgingCycleIndex =  Dem_CfgInfoCmn_GetEventHealingAgingCycleRef( EventPos );    /* [GUDCHK:CALLER]EventPos */

    /*  check match of cycle.       */
    retChkHealingAgingCycle =   Dem_OpCycle_CheckMatchOfTargetHealingAgingCycle( targetHealingAgingCycleIndex,  ThisCycleIndex, ThisCycleKind, ObdDcyCycleState, WarmUpCycleState );
    retChkOperationCycle    =   Dem_OpCycle_CheckMatchOfTargetFailureCycle(      targetOpcycIndex,              ThisCycleIndex, ThisCycleKind, ObdDcyCycleState, WarmUpCycleState );

    *HealingAgingCycleFlagPtr = retChkHealingAgingCycle;
    *FailureCycleFlagPtr      = retChkOperationCycle;

    if( ( retChkHealingAgingCycle != DEM_OPCYCUPD_HACYC_INITIALVALUE ) || ( retChkOperationCycle != DEM_OPCYCUPD_FLCYC_INITIALVALUE ) )
    {
        retVal = (boolean)TRUE;
    }
    else
    {
        retVal = (boolean)FALSE;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_OpCycle_CheckMatchOfTargetHealingAgingCycle          */
/* Description   | Check if this cycle is the target cycle or not.          */
/* Preconditions |                                                          */
/* Parameters    | [in]  TargetCycleIndex                                   */
/*               | [in]  ThisCycleIndex                                     */
/*               | [in]  ThisCycleKind                                      */
/*               | [in]  ObdDcyCycleState                                   */
/*               | [in]  WarmUpCycleState                                   */
/* Return Value  | Dem_u08_OpcycUpdateHealingAgingCycleType                 */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_OpcycUpdateHealingAgingCycleType, DEM_CODE ) Dem_OpCycle_CheckMatchOfTargetHealingAgingCycle
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC )  TargetCycleIndex,
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC )  ThisCycleIndex,
    VAR( Dem_u08_OpCycleKindType, AUTOMATIC )   ThisCycleKind,
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) ObdDcyCycleState,
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) WarmUpCycleState
)
{
    VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC ) retVal;
    VAR( Dem_u08_OpCycleKindType, AUTOMATIC ) targetCycleKind;
    VAR( Dem_u08_OpCycleKindIndexType, AUTOMATIC ) thisCycleKindIndex;

    /*----------------------------------*/
    /*  check this cycle kind.          */
    /*----------------------------------*/
    thisCycleKindIndex  =   Dem_OpCycle_GetCycleKindTableThisCycleIndex( ThisCycleIndex, ThisCycleKind, ObdDcyCycleState, WarmUpCycleState );

#if ( DEM_ENGINETYPE_COMPRESSION_SUPPORT == STD_ON )    /*  [FuncSw]    */
    if ( thisCycleKindIndex == DEM_OPCYCKIND_THISCYCLE_INVALID )
    {
        retVal  =   DEM_OPCYCUPD_HACYC_INITIALVALUE;    /*  no match this cycle and target cycle.       */
    }
    else
#endif  /* ( DEM_ENGINETYPE_COMPRESSION_SUPPORT == STD_ON )             */
    {
        /*----------------------------------*/
        /*  check config cycle kind.        */
        /*----------------------------------*/
        if( TargetCycleIndex == DEM_OPERATION_CYCLE_INDEX_OBD_DCY )
        {
            retVal  =   Dem_OpCycleUpdateHealingAgingCycleTable[ DEM_OPCYCKIND_CFGCYCLE_DCY ][ thisCycleKindIndex ];            /*  DCY cycle       */
        }
        else if ( TargetCycleIndex == ThisCycleIndex )
        {
            if( ThisCycleKind == DEM_OPCYC_IGNITION )
            {
                /*  If the type of ThisCycle is IG, the type of TargetCycle is also the same IG.    */
                retVal  =   Dem_OpCycleUpdateHealingAgingCycleTable[ DEM_OPCYCKIND_CFGCYCLE_IG ][ thisCycleKindIndex ];         /*  IG cycle        */
            }
            else
            {
                retVal  =   Dem_OpCycleUpdateHealingAgingCycleTable[ DEM_OPCYCKIND_CFGCYCLE_OTHER ][ thisCycleKindIndex ];      /*  other cycle     */
            }
        }
        else
        {
            targetCycleKind   =   Dem_OpCycle_GetOperationCycleTypeMember( TargetCycleIndex );
            if( targetCycleKind == DEM_OPCYC_IGNITION )
            {
                retVal  =   Dem_OpCycleUpdateHealingAgingCycleTable[ DEM_OPCYCKIND_CFGCYCLE_IG ][ thisCycleKindIndex ];         /*  IG cycle        */
            }
            else
            {
                retVal  =   DEM_OPCYCUPD_HACYC_INITIALVALUE;    /*  no match this cycle and target cycle.       */
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_OpCycle_CheckMatchOfTargetFailureCycle               */
/* Description   | Check if this cycle is the target cycle or not.          */
/* Preconditions |                                                          */
/* Parameters    | [in]  TargetCycleIndex                                   */
/*               | [in]  ThisCycleIndex                                     */
/*               | [in]  ThisCycleKind                                      */
/*               | [in]  ObdDcyCycleState                                   */
/* Return Value  | Dem_u08_OpcycUpdateFailureCycleType                      */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_OpcycUpdateFailureCycleType, DEM_CODE ) Dem_OpCycle_CheckMatchOfTargetFailureCycle
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC )  TargetCycleIndex,
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC )  ThisCycleIndex,
    VAR( Dem_u08_OpCycleKindType, AUTOMATIC )   ThisCycleKind,
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) ObdDcyCycleState,
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) WarmUpCycleState
)
{
    VAR( Dem_u08_OpcycUpdateFailureCycleType, AUTOMATIC ) retVal;
    VAR( Dem_u08_OpCycleKindType, AUTOMATIC ) targetCycleKind;
    VAR( Dem_u08_OpCycleKindIndexType, AUTOMATIC ) thisCycleKindIndex;

    /*----------------------------------*/
    /*  check this cycle kind.          */
    /*----------------------------------*/
    thisCycleKindIndex  =   Dem_OpCycle_GetCycleKindTableThisCycleIndex( ThisCycleIndex, ThisCycleKind, ObdDcyCycleState, WarmUpCycleState );

#if ( DEM_ENGINETYPE_COMPRESSION_SUPPORT == STD_ON )    /*  [FuncSw]    */
    if ( thisCycleKindIndex == DEM_OPCYCKIND_THISCYCLE_INVALID )
    {
        retVal  =   DEM_OPCYCUPD_FLCYC_INITIALVALUE;    /*  no match this cycle and target cycle.       */
    }
    else
#endif  /* ( DEM_ENGINETYPE_COMPRESSION_SUPPORT == STD_ON )             */
    {
        /*----------------------------------*/
        /*  check config cycle kind.        */
        /*----------------------------------*/
        if( TargetCycleIndex == DEM_OPERATION_CYCLE_INDEX_OBD_DCY )
        {
            retVal  =   Dem_OpCycleUpdateFailureCycleTable[ DEM_OPCYCKIND_CFGCYCLE_DCY ][ thisCycleKindIndex ];             /*  DCY cycle       */
        }
        else if ( TargetCycleIndex == ThisCycleIndex )
        {
            if( ThisCycleKind == DEM_OPCYC_IGNITION )
            {
                /*  If the type of ThisCycle is IG, the type of TargetCycle is also the same IG.    */
                retVal  =   Dem_OpCycleUpdateFailureCycleTable[ DEM_OPCYCKIND_CFGCYCLE_IG ][ thisCycleKindIndex ];          /*  IG cycle        */
            }
            else
            {
                retVal  =   Dem_OpCycleUpdateFailureCycleTable[ DEM_OPCYCKIND_CFGCYCLE_OTHER ][ thisCycleKindIndex ];       /*  other cycle     */
            }
        }
        else
        {
            targetCycleKind   =   Dem_OpCycle_GetOperationCycleTypeMember( TargetCycleIndex );
            if( targetCycleKind == DEM_OPCYC_IGNITION )
            {
                retVal  =   Dem_OpCycleUpdateFailureCycleTable[ DEM_OPCYCKIND_CFGCYCLE_IG ][ thisCycleKindIndex ];          /*  IG cycle        */
            }
            else
            {
                retVal  =   DEM_OPCYCUPD_FLCYC_INITIALVALUE;    /*  no match this cycle and target cycle.       */
            }
        }
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_OpCycle_GetCycleKindTableThisCycleIndex              */
/* Description   | get cyclekind table index : this cycle.                  */
/* Preconditions |                                                          */
/* Parameters    | [in]  ThisCycleIndex                                     */
/*               | [in]  ThisCycleKind                                      */
/*               | [in]  ObdDcyCycleState                                   */
/*               | [in]  WarmUpCycleState                                   */
/* Return Value  | Dem_u08_OpCycleKindIndexType                             */
/*               |      DEM_OPCYCKIND_THISCYCLE_OTHER                       */
/*               |      DEM_OPCYCKIND_THISCYCLE_IG                          */
/*               |      DEM_OPCYCKIND_THISCYCLE_DCY                         */
/*               |      DEM_OPCYCKIND_THISCYCLE_WARMUP                      */
/*               |      DEM_OPCYCKIND_THISCYCLE_4CHDCY                      */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_OpCycleKindIndexType, DEM_CODE ) Dem_OpCycle_GetCycleKindTableThisCycleIndex
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC )  ThisCycleIndex,     /* MISRA DEVIATION */
    VAR( Dem_u08_OpCycleKindType, AUTOMATIC )   ThisCycleKind,
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) ObdDcyCycleState,
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) WarmUpCycleState
)
{
    VAR( Dem_u08_OpCycleKindIndexType, AUTOMATIC ) thisCycleKindIndex;
#if ( DEM_ENGINETYPE_COMPRESSION_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) retChkOperationCycleIndex;
#endif  /* ( DEM_ENGINETYPE_COMPRESSION_SUPPORT == STD_ON )             */

    if( ThisCycleKind == DEM_OPCYC_IGNITION )
    {
        if( ObdDcyCycleState == DEM_CYCLE_NOTIFY_START )
        {
#if ( DEM_ENGINETYPE_COMPRESSION_SUPPORT == STD_ON )    /*  [FuncSw]    */
            retChkOperationCycleIndex = Dem_OpCycle_Check4hDCY( ThisCycleIndex );
            if( retChkOperationCycleIndex == (boolean)TRUE )
            {
                thisCycleKindIndex  =   DEM_OPCYCKIND_THISCYCLE_4CHDCY;         /*  4hDCY.          */
            }
            else
#endif  /* ( DEM_ENGINETYPE_COMPRESSION_SUPPORT == STD_ON )             */
            {
                /*  check WarmUp state.     */
                if( WarmUpCycleState == DEM_CYCLE_NOTIFY_START )
                {
                    thisCycleKindIndex  =   DEM_OPCYCKIND_THISCYCLE_WARMUP;     /*  WARMUP cycle.   */
                }
                else
                {
                    thisCycleKindIndex  =   DEM_OPCYCKIND_THISCYCLE_DCY;        /*  DCY cycle.      */
                }
            }
        }
        else
        {
#if ( DEM_ENGINETYPE_COMPRESSION_SUPPORT == STD_ON )    /*  [FuncSw]    */
            retChkOperationCycleIndex = Dem_OpCycle_Check4hDCY( ThisCycleIndex );
            if( retChkOperationCycleIndex == (boolean)TRUE )
            {
                /*  invalid cycle.          */
                thisCycleKindIndex  =   DEM_OPCYCKIND_THISCYCLE_INVALID;        /*  Invalid cycle.  */
            }
            else
#endif  /* ( DEM_ENGINETYPE_COMPRESSION_SUPPORT == STD_ON )             */
            {
                thisCycleKindIndex  =   DEM_OPCYCKIND_THISCYCLE_IG;             /*  IG cycle.       */
            }
        }
    }
    else
    {
        thisCycleKindIndex  =   DEM_OPCYCKIND_THISCYCLE_OTHER;                  /*  other cycle.    */
    }

    return thisCycleKindIndex;
}

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_OpCycle_GetThisCycleKindIndex                        */
/* Description   | get this cycle kind index.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in]  OperationCycleIndex                                */
/* Return Value  | Dem_u08_OpCycleKindIndexType                             */
/*               |      DEM_OPCYCKIND_THISCYCLE_OTHER                       */
/*               |      DEM_OPCYCKIND_THISCYCLE_IG                          */
/*               |      DEM_OPCYCKIND_THISCYCLE_DCY                         */
/*               |      DEM_OPCYCKIND_THISCYCLE_WARMUP                      */
/*               |      DEM_OPCYCKIND_THISCYCLE_4CHDCY                      */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_OpCycleKindIndexType, DEM_CODE ) Dem_OpCycle_GetThisCycleKindIndex
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex
)
{
    VAR( Dem_u08_OpCycleKindType, AUTOMATIC ) opcycKind;
    VAR( Dem_u08_OpCycleKindIndexType, AUTOMATIC ) thisCycleKindIndex;
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) opcycObdDcy;
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) opcycWarmUp;
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) obdDcyCycleState;
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) obdWarmUpState;

    /*  get OperationCycle kind.    */
    opcycKind = Dem_OpCycle_GetOperationCycleTypeMember( OperationCycleIndex );

    /*  get OBD_DCY start state.    */
    opcycObdDcy = Dem_ConfDemOperationCycleObdDcy;
    obdDcyCycleState = Dem_OpCycleMng_GetCycleState( opcycObdDcy );

    /*  get WarmUp state.           */
    opcycWarmUp = Dem_ConfDemOperationCycleWarmUp;
    obdWarmUpState = Dem_OpCycleMng_GetCycleState( opcycWarmUp );

    /*  get this OperationCycle kind index.     */
    thisCycleKindIndex = Dem_OpCycle_GetCycleKindTableThisCycleIndex( OperationCycleIndex, opcycKind, obdDcyCycleState, obdWarmUpState );

    return thisCycleKindIndex;
}
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_OFF ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
