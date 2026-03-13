/* Dem_DTC_BitAces_ExtendDTCStatus_c(v5-9-0)                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/


/****************************************************************************/
/* Object Name  | Dem/DTC_BitAces_ExtendDTCStatus/CODE                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../../cfg/Dem_Cfg.h"
#include "../../../../inc/Dem_CmnLib_DTC_DTCStatus.h"
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../../inc/Dem_Rc_OpCycleMng.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTC_CheckExtendDTCStatus                             */
/* Description   | Judge a state of each bit of DTC Status.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] ExtendDTCStatus : DTC status.                       */
/*               | [in] ExtendDTCStatusBitOnMask : Mask value for each bit  */
/*               |                           judgment of the DTC status.    */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : condition established.                    */
/*               |        FALSE : condition is not established.             */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_DTC_CheckExtendDTCStatus
(
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatus,
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatusBitOnMask
)
{
    VAR( boolean, AUTOMATIC ) retVal;

    retVal = (boolean)FALSE;
    if( ( ExtendDTCStatus & ExtendDTCStatusBitOnMask ) == ExtendDTCStatusBitOnMask )
    {
        retVal = (boolean)TRUE;
    }
    return retVal;
}
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_DTC_ExDTC_ResetIndicatorBit                          */
/* Description   | Turn off Extend DTC status bit(Indicator)                */
/* Preconditions | none                                                     */
/* Parameters    | [in] ExtendDTCStatus : DTC status before the change.     */
/* Return Value  | Dem_u08_DTCStatusExType                                  */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_DTCStatusExType, DEM_CODE ) Dem_DTC_ExDTC_ResetIndicatorBit
(
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatus
)
{
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) retVal;

    /* Turns off Extend DTC status bit */
    retVal = ( ExtendDTCStatus & (Dem_u08_DTCStatusExType)~DEM_DTCSTATUSEX_STATUS_INDICATOR );

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DTC_ExDTC_ResetIndicatorBit_OnOverflow               */
/* Description   | Turn off Extend DTC status bit(Indicator)                */
/* Preconditions | none                                                     */
/* Parameters    | [in] ExtendDTCStatus : DTC status before the change.     */
/* Return Value  | Dem_u08_DTCStatusExType                                  */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_DTCStatusExType, DEM_CODE ) Dem_DTC_ExDTC_ResetIndicatorBit_OnOverflow
(
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatus
)
{
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) retVal;
    VAR( Dem_u08_ResetConfirmedBitOnOverflowType, AUTOMATIC ) resetConfirmedBitOnOverflow;

    resetConfirmedBitOnOverflow = Dem_ResetConfirmedBitOnOverflow;

    retVal  =   ExtendDTCStatus;

    if ( resetConfirmedBitOnOverflow == DEM_STATUS_BIT_RESET_CDTC_WITH_PDTC )
    {
        /* Turns off Extend DTC status bit */
        retVal = ( ExtendDTCStatus & (Dem_u08_DTCStatusExType)~DEM_DTCSTATUSEX_STATUS_INDICATOR );
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DTC_ExDTC_SetIndicatorAndConfirmedHistoryBit         */
/* Description   | Turn on Extend DTC status bit(Indicator)                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] ExtendDTCStatus : DTC status before the change.     */
/* Return Value  | Dem_u08_DTCStatusExType                                  */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_DTCStatusExType, DEM_CODE ) Dem_DTC_ExDTC_SetIndicatorAndConfirmedHistoryBit
(
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatus
)
{
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) retVal;

    /* Turns on Extend DTC status bit */
    retVal = ( ExtendDTCStatus | ( DEM_DTCSTATUSEX_STATUS_INDICATOR | DEM_UDS_STATUS_HISTORY_CDTC ) );

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DTC_ExDTC_SetConfirmedHistoryBit                     */
/* Description   | Turn on Extend DTC status bit(ConfirmedHistroryBit)      */
/* Preconditions | none                                                     */
/* Parameters    | [in] ExtendDTCStatus : DTC status before the change.     */
/* Return Value  | Dem_u08_DTCStatusExType                                  */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_DTCStatusExType, DEM_CODE ) Dem_DTC_ExDTC_SetConfirmedHistoryBit
(
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatus
)
{
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) retVal;

    /* Turns on Extend DTC status bit */
    retVal = ( ExtendDTCStatus | DEM_UDS_STATUS_HISTORY_CDTC );

    return retVal;
}

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTC_ExDTC_ResetPredictiveFaultBit                    */
/* Description   | Turn off Extend DTC status bit(PredictiveFault)          */
/* Preconditions | none                                                     */
/* Parameters    | [in] ExtendDTCStatus : DTC status before the change.     */
/* Return Value  | Dem_u08_DTCStatusExType                                  */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_DTCStatusExType, DEM_CODE ) Dem_DTC_ExDTC_ResetPredictiveFaultBit
(
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatus
)
{
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) retVal;

    /* Turns off Extend DTC status bit */
    retVal = ( ExtendDTCStatus & (Dem_u08_DTCStatusExType)~DEM_DTCSTATUSEX_STATUS_PREDICTIVE_FAULT );

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DTC_ExDTC_ResetPredictiveFaultBit_OnOverflow         */
/* Description   | Turn off Extend DTC status bit(PredictiveFault)          */
/* Preconditions | none                                                     */
/* Parameters    | [in] ExtendDTCStatus : DTC status before the change.     */
/* Return Value  | Dem_u08_DTCStatusExType                                  */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_DTCStatusExType, DEM_CODE ) Dem_DTC_ExDTC_ResetPredictiveFaultBit_OnOverflow
(
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatus
)
{
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) retVal;
    VAR( Dem_u08_ResetConfirmedBitOnOverflowType, AUTOMATIC ) resetConfirmedBitOnOverflow;

    resetConfirmedBitOnOverflow = Dem_ResetConfirmedBitOnOverflow;

    retVal  =   ExtendDTCStatus;

    if( resetConfirmedBitOnOverflow == DEM_STATUS_BIT_RESET_CDTC_WITH_PDTC )
    {
        /* Turns off Extend DTC status bit */
        retVal = ( ExtendDTCStatus & (Dem_u08_DTCStatusExType)~DEM_DTCSTATUSEX_STATUS_PREDICTIVE_FAULT );
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DTC_ExDTC_SetPredictiveFaultBit                      */
/* Description   | Turn on Extend DTC status bit(PredictiveFaultBit  )      */
/* Preconditions | none                                                     */
/* Parameters    | [in] ExtendDTCStatus : DTC status before the change.     */
/* Return Value  | Dem_u08_DTCStatusExType                                  */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_DTCStatusExType, DEM_CODE ) Dem_DTC_ExDTC_SetPredictiveFaultBit
(
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatus
)
{
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) retVal;

    /* Turns on Extend DTC status bit */
    retVal = ( ExtendDTCStatus | DEM_DTCSTATUSEX_STATUS_PREDICTIVE_FAULT );

    return retVal;
}
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )    */

/****************************************************************************/
/* Function Name | Dem_DTC_ExDTC_SetNormalizeExDTCStatus                    */
/* Description   | bit0,1,2,3,4,(5),6,7 of statusOfDTC are set to 0.        */
/* Preconditions | none                                                     */
/* Parameters    | [in]ExtendDTCStatus :Extend DTC status before the change.*/
/* Return Value  | Dem_u08_DTCStatusExType                                  */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_DTCStatusExType, DEM_CODE ) Dem_DTC_ExDTC_SetNormalizeExDTCStatus
(
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatus
)
{
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) newExDTCStatus;

    /*  ON  : Passed history                */
    newExDTCStatus  = ( ExtendDTCStatus | DEM_UDS_STATUS_HISTORY_PASSED );

    /*  OFF : bit6 and bit1 in HealingAging cycle, Indicator bit     */
    newExDTCStatus  =   newExDTCStatus & ~( DEM_DTCSTATUSEX_STATUS_TFTOC_IN_HEALINGCYCLE | DEM_DTCSTATUSEX_STATUS_TNCTOC_IN_HEALINGCYCLE |
                                            DEM_DTCSTATUSEX_STATUS_TFTOC_IN_AGINGCYCLE | DEM_DTCSTATUSEX_STATUS_TNCTOC_IN_AGINGCYCLE | DEM_DTCSTATUSEX_STATUS_INDICATOR );

    return newExDTCStatus;
}


/****************************************************************************/
/* Function Name | Dem_DTC_ExDTC_SetPassedExDTCStatus                       */
/* Description   | set statusOfDTC : OFF : bit0,4,6                         */
/* Preconditions | none                                                     */
/* Parameters    | [in]ExtendDTCStatus :Extend DTC status before the change.*/
/* Return Value  | Dem_u08_DTCStatusExType                                  */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_DTCStatusExType, DEM_CODE ) Dem_DTC_ExDTC_SetPassedExDTCStatus
(
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatus
)
{
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) newExDTCStatus;

    /*  ON  : Passed history                */
    newExDTCStatus  = ( ExtendDTCStatus | DEM_UDS_STATUS_HISTORY_PASSED );

    /*  OFF : bit6 in HealingAging cycle(TestNotCompletedThisHealingAgingCycle)     */
    newExDTCStatus  =   newExDTCStatus & ~( DEM_DTCSTATUSEX_STATUS_TNCTOC_IN_HEALINGCYCLE | DEM_DTCSTATUSEX_STATUS_TNCTOC_IN_AGINGCYCLE );   /*  bit6 in HealingAging cycle  */

    return newExDTCStatus;
}

/****************************************************************************/
/* Function Name | Dem_DTC_ExDTC_SetFailedExDTCStatus                       */
/* Description   | set statusOfDTC : OFF : bit4,6  ON : bit0,1,2,5          */
/* Preconditions | none                                                     */
/* Parameters    | [in]ExtendDTCStatus :Extend DTC status before the change.*/
/* Return Value  | Dem_u08_DTCStatusExType                                  */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_DTCStatusExType, DEM_CODE ) Dem_DTC_ExDTC_SetFailedExDTCStatus
(
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatus
)
{
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) newExDTCStatus;

    /*  OFF : bit6 in HealingAging cycle(TestNotCompletedThisHealingAgingCycle) */
    newExDTCStatus  =   ExtendDTCStatus & ~( DEM_DTCSTATUSEX_STATUS_TNCTOC_IN_HEALINGCYCLE | DEM_DTCSTATUSEX_STATUS_TNCTOC_IN_AGINGCYCLE );  /*  bit6 in HealingAging cycle  */

    /*  ON  : bit1 in HealingAging cycle(TestFailedThisHealingAgingCycle)       */
    newExDTCStatus  =   newExDTCStatus  | ( DEM_DTCSTATUSEX_STATUS_TFTOC_IN_HEALINGCYCLE | DEM_DTCSTATUSEX_STATUS_TFTOC_IN_AGINGCYCLE );    /*  bit1 in HealingAging cycle  */

    return newExDTCStatus;
}

/****************************************************************************/
/* Function Name | Dem_DTC_ExDTC_RestartHealingAgingCycleExDTCStatus        */
/* Description   | set statusOfDTC : bit1 : OFF, bit6 : ON                  */
/* Preconditions | none                                                     */
/* Parameters    | [in]ExtendDTCStatus :Extend DTC status before the change.*/
/*               | [in]HealingAgingCycleFlag :Extend DTC status update mode.*/
/* Return Value  | Dem_u08_DTCStatusExType                                  */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_DTCStatusExType, DEM_CODE ) Dem_DTC_ExDTC_RestartHealingAgingCycleExDTCStatus
(
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatus,
    VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC ) HealingAgingCycleFlag
)
{
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) newExDTCStatus;

    newExDTCStatus      =   ExtendDTCStatus;

    /*  update Healing cycle            */
    if (( HealingAgingCycleFlag & DEM_OPCYCUPD_HACYC_UPDATE_HEALINGCYC ) == DEM_OPCYCUPD_HACYC_UPDATE_HEALINGCYC )
    {
        /*  OFF : bit1 in Healing cycle(TestFailedThisHealingCycle)       */
        newExDTCStatus  =   newExDTCStatus & ~( DEM_DTCSTATUSEX_STATUS_TFTOC_IN_HEALINGCYCLE );   /*  bit1 in Healing cycle  */

        /*  ON : bit6 in Healing cycle(TestNotCompletedThisHealingCycle)  */
        newExDTCStatus  =   newExDTCStatus | ( DEM_DTCSTATUSEX_STATUS_TNCTOC_IN_HEALINGCYCLE );    /*  bit6 in Healing cycle  */
    }

    /*  update Aging cycle              */
    if (( HealingAgingCycleFlag & DEM_OPCYCUPD_HACYC_UPDATE_AGINGCYC ) == DEM_OPCYCUPD_HACYC_UPDATE_AGINGCYC )
    {
        /*  OFF : bit1 in HealingAging cycle(TestFailedThisHealingAgingCycle)       */
        newExDTCStatus  =   newExDTCStatus & ~( DEM_DTCSTATUSEX_STATUS_TFTOC_IN_AGINGCYCLE );   /*  bit1 in HealingAging cycle  */

        /*  ON : bit6 in HealingAging cycle(TestNotCompletedThisHealingAgingCycle)  */
        newExDTCStatus  =   newExDTCStatus | ( DEM_DTCSTATUSEX_STATUS_TNCTOC_IN_AGINGCYCLE );    /*  bit6 in HealingAging cycle  */
    }

    return newExDTCStatus;
}

/****************************************************************************/
/* Function Name | Dem_DTC_ExDTC2_SetNormalizeExDTCStatus                   */
/* Description   | like bit0,1,2,3,4,(5),6,7 of statusOfDTC are set to 0.   */
/* Preconditions | none                                                     */
/* Parameters    | [in]ExtendDTCStatus2 :Extend DTC status before the change.*/
/* Return Value  | Dem_u08_DTCStatusEx2Type                                 */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_SetNormalizeExDTCStatus
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2
)
{
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) newExDTCStatus2;

    /*  OFF : bit6 in PFCClearCondition cycle    */
    /*  OFF : bit1 in Failure cycle              */
    newExDTCStatus2  =   ExtendDTCStatus2 & ~( DEM_DTCSTATUSEX2_STATUS_TNCTOC_IN_PFCCLEARCONDCYCLE | DEM_DTCSTATUSEX2_STATUS_TFTOC_IN_FAILURECYCLE );

    return newExDTCStatus2;
}

/****************************************************************************/
/* Function Name | Dem_DTC_ExDTC2_ResetContMIHistAndIndAtCycleStartBit      */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in]ExtendDTCStatus2 :Extend DTC status before the change.*/
/* Return Value  | Dem_u08_DTCStatusEx2Type                                 */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_ResetContMIHistAndIndAtCycleStartBit
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2
)
{
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) newExDTCStatus2;

    /*  OFF : ActiveFault at cycle start    */
    /*  OFF : Continuous-MI History         */
    newExDTCStatus2  =   ExtendDTCStatus2 & ~( DEM_DTCSTATUSEX2_STATUS_INDICATOR_AT_CYCLESTART | DEM_DTCSTATUSEX2_STATUS_CONTINUOUS_MI_HISTORY );

    return newExDTCStatus2;
}

#if ( DEM_INDICATOR_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTC_ExDTC2_ResetContinuousMIHistoryBit               */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in]ExtendDTCStatus2 :Extend DTC status before the change.*/
/* Return Value  | Dem_u08_DTCStatusEx2Type                                 */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_ResetContinuousMIHistoryBit
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2
)
{
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) newExDTCStatus2;

    /*  OFF : Continuous-MI History       */
    newExDTCStatus2  =   ExtendDTCStatus2 & ~DEM_DTCSTATUSEX2_STATUS_CONTINUOUS_MI_HISTORY;

    return newExDTCStatus2;
}
#endif  /* ( DEM_INDICATOR_USE == STD_ON )  */

/****************************************************************************/
/* Function Name | Dem_DTC_ExDTC2_SetPassedExDTCStatus                      */
/* Description   | set extend statusOfDTC : like OFF : bit0,4,6             */
/* Preconditions | none                                                     */
/* Parameters    | [in]ExtendDTCStatus2 :Extend DTC status before the change.*/
/* Return Value  | Dem_u08_DTCStatusEx2Type                                 */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_SetPassedExDTCStatus
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2
)
{
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) newExDTCStatus2;

#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
    VAR( Dem_u08_PFCClearCondCheckStatusType, AUTOMATIC ) pfcClearConditionCheckStatus;

    pfcClearConditionCheckStatus   =   Dem_OpCycleMng_GetPFCCycleClearConditionCheckStatus();
    if ( pfcClearConditionCheckStatus == DEM_PFC_CLEARCONDCHKSTATUS_DISABLE )
    {
        newExDTCStatus2  =   ExtendDTCStatus2;
    }
    else
#endif  /* ( DEM_PFC_SUPPORT == STD_ON )            */
    {
        /*  OFF : bit6 in PFCClearCondition cycle(TestNotCompletedThisPFCClearConditionCycle)     */
        newExDTCStatus2  =   ExtendDTCStatus2 & ~( DEM_DTCSTATUSEX2_STATUS_TNCTOC_IN_PFCCLEARCONDCYCLE );   /*  bit6 in PFCClearCondition cycle  */
    }

    return newExDTCStatus2;
}

/****************************************************************************/
/* Function Name | Dem_DTC_ExDTC2_SetFailedExDTCStatus                      */
/* Description   | set extend statusOfDTC : like OFF:bit4,6  ON:bit0,1,2,5  */
/* Preconditions | none                                                     */
/* Parameters    | [in]ExtendDTCStatus2 :Extend DTC status before the change.*/
/* Return Value  | Dem_u08_DTCStatusEx2Type                                 */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_SetFailedExDTCStatus
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2
)
{
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) newExDTCStatus2;
#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
    VAR( Dem_u08_PFCClearCondCheckStatusType, AUTOMATIC ) pfcClearConditionCheckStatus;

    pfcClearConditionCheckStatus   =   Dem_OpCycleMng_GetPFCCycleClearConditionCheckStatus();
    if ( pfcClearConditionCheckStatus == DEM_PFC_CLEARCONDCHKSTATUS_DISABLE )
    {
        newExDTCStatus2  =   ExtendDTCStatus2;
    }
    else
#endif  /* ( DEM_PFC_SUPPORT == STD_ON )            */
    {
        /*  OFF : bit6 in PFCClearCondition cycle(TestNotCompletedThisPFCClearConditionCycle) */
        newExDTCStatus2  =   ExtendDTCStatus2 & ~( DEM_DTCSTATUSEX2_STATUS_TNCTOC_IN_PFCCLEARCONDCYCLE );  /*  bit6 in PFCClearCondition cycle  */
    }

    /*  ON :  bit1 in Failure cycle                   */
    newExDTCStatus2  =   newExDTCStatus2 | ( DEM_DTCSTATUSEX2_STATUS_TFTOC_IN_FAILURECYCLE );  /*  bit1 in Failure cycle  */

    /*  OFF :  Reset aging history                  */
    newExDTCStatus2 =   newExDTCStatus2 & ~( DEM_DTCSTATUSEX2_STATUS_AGING_HISTORY );

    return newExDTCStatus2;
}

/****************************************************************************/
/* Function Name | Dem_DTC_ExDTC2_RestartHealingAgingCycleExDTCStatus       */
/* Description   | set extend statusOfDTC : like bit1 : OFF, bit6 : ON      */
/* Preconditions | none                                                     */
/* Parameters    | [in]ExtendDTCStatus2 :Extend DTC status before the change.*/
/* Return Value  | Dem_u08_DTCStatusEx2Type                                 */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_RestartHealingAgingCycleExDTCStatus
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2,
    VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC ) HealingAgingCycleFlag
)
{
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) newExDTCStatus2;

    newExDTCStatus2 =   ExtendDTCStatus2;

    if (( HealingAgingCycleFlag & DEM_OPCYCUPD_HACYC_UPDATE_HEALINGCYC ) == DEM_OPCYCUPD_HACYC_UPDATE_HEALINGCYC )
    {
        /*  ON : bit6 in PFCClearCondition cycle(TestNotCompletedThisPFCClearConditionCycle)  */
        newExDTCStatus2  =   newExDTCStatus2 | ( DEM_DTCSTATUSEX2_STATUS_TNCTOC_IN_PFCCLEARCONDCYCLE );    /*  bit6 in PFCClearCondition cycle  */
    }

    return newExDTCStatus2;
}


/****************************************************************************/
/* Function Name | Dem_DTC_ExDTC2_RestartOperationCycleExDTCStatus          */
/* Description   | Turn off Extend DTC status bit(FailureCycle)             */
/* Preconditions | none                                                     */
/* Parameters    | [in] ExtendDTCStatus2 : DTC status before the change.    */
/*               | [in] FailureCycleFlag : DTC status change mode.          */
/* Return Value  | Dem_u08_DTCStatusEx2Type                                 */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_RestartOperationCycleExDTCStatus
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2,
    VAR( Dem_u08_OpcycUpdateFailureCycleType, AUTOMATIC ) FailureCycleFlag
)
{
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) newExDTCStatus2;

    newExDTCStatus2 =   ExtendDTCStatus2;

    /*  check failure cycle update.     */
    if (( FailureCycleFlag & DEM_OPCYCUPD_FLCYC_UPDATE_FCCYC ) == DEM_OPCYCUPD_FLCYC_UPDATE_FCCYC )
    {
        /*  OFF :  bit1 in Failure cycle                   */
        newExDTCStatus2 = ( newExDTCStatus2 & (Dem_u08_DTCStatusEx2Type)~DEM_DTCSTATUSEX2_STATUS_TFTOC_IN_FAILURECYCLE );
    }

    return newExDTCStatus2;
}

/****************************************************************************/
/* Function Name | Dem_DTC_ExDTC2_SetAgingHistory                           */
/* Description   | set eventDisable                                         */
/* Preconditions | none                                                     */
/* Parameters    | [in]ExtendDTCStatus2 :Extend DTC status before the change.*/
/* Return Value  | Dem_u08_DTCStatusEx2Type                                 */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_SetAgingHistory
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2
)
{
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) newExDTCStatus2;

    newExDTCStatus2 =   ExtendDTCStatus2 | DEM_DTCSTATUSEX2_STATUS_AGING_HISTORY;

    return newExDTCStatus2;
}

#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTC_ExDTC_SetEventDisable                            */
/* Description   | set eventDisable                                         */
/* Preconditions | none                                                     */
/* Parameters    | [in]ExtendDTCStatus2 :Extend DTC status before the change.*/
/* Return Value  | Dem_u08_DTCStatusEx2Type                                 */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_SetEventDisable
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2
)
{
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) newExDTCStatus2;

    newExDTCStatus2 =   ExtendDTCStatus2 | DEM_DTCSTATUSEX2_STATUS_EVENTDISABLE;

    return newExDTCStatus2;
}

/****************************************************************************/
/* Function Name | Dem_DTC_ExDTC2_ClearEventDisable                         */
/* Description   | clear eventDisable                                       */
/* Preconditions | none                                                     */
/* Parameters    | [in]ExtendDTCStatus2 :Extend DTC status before the change.*/
/* Return Value  | Dem_u08_DTCStatusEx2Type                                 */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_ClearEventDisable
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2
)
{
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) newExDTCStatus2;

    newExDTCStatus2 =   ExtendDTCStatus2 & ~DEM_DTCSTATUSEX2_STATUS_EVENTDISABLE;

    return newExDTCStatus2;
}
#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON )    */

/****************************************************************************/
/* Function Name | Dem_DTC_ExDTC2_SetIndicatorAtCycleStart                  */
/* Description   | Set Extend DTC status2 bit(IndicatorAtCycleStart)        */
/* Preconditions | none                                                     */
/* Parameters    | [in] ExtendDTCStatus  : Indicator bit copy target.       */
/*               | [in] ExtendDTCStatus2 : DTC status before the change.    */
/* Return Value  | Dem_u08_DTCStatusEx2Type                                 */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_SetIndicatorAtCycleStart
(
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendDTCStatus,
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2
)
{
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) newExDTCStatus2;
    if ( ( ExtendDTCStatus & DEM_DTCSTATUSEX_STATUS_INDICATOR ) == DEM_DTCSTATUSEX_STATUS_INDICATOR )
    {
        newExDTCStatus2 =   ExtendDTCStatus2 | DEM_DTCSTATUSEX2_STATUS_INDICATOR_AT_CYCLESTART;
    }
    else
    {
        newExDTCStatus2 =   ExtendDTCStatus2 & ~DEM_DTCSTATUSEX2_STATUS_INDICATOR_AT_CYCLESTART;
    }
    return newExDTCStatus2;
}

/****************************************************************************/
/* Function Name | Dem_DTC_ExDTC2_SetContinuousMIHistoryBit                 */
/* Description   | Turn on Extend DTC status2 bit(ContinuousExp)            */
/* Preconditions | none                                                     */
/* Parameters    | [in] ExtendDTCStatus2 : DTC status before the change.    */
/* Return Value  | Dem_u08_DTCStatusEx2Type                                 */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_SetContinuousMIHistoryBit
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2
)
{
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) retVal;

     /* Turns on Extend DTC status bit */
    retVal = ( ExtendDTCStatus2 | DEM_DTCSTATUSEX2_STATUS_CONTINUOUS_MI_HISTORY );

    return retVal;
}

/*********************************************************************************/
/* Function Name | Dem_DTC_ExDTC2_ResetContMIHistAndIndAtCycleStartBit_OnOverflow*/
/* Description   |                                                               */
/* Preconditions | none                                                          */
/* Parameters    | [in]ExtendDTCStatus2 :Extend DTC status before the change.    */
/* Return Value  | Dem_u08_DTCStatusEx2Type                                      */
/* Notes         |                                                               */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/*********************************************************************************/
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_ResetContMIHistAndIndAtCycleStartBit_OnOverflow
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2
)
{
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) newExDTCStatus2;
    VAR( Dem_u08_ResetConfirmedBitOnOverflowType, AUTOMATIC ) resetConfirmedBitOnOverflow;

    resetConfirmedBitOnOverflow = Dem_ResetConfirmedBitOnOverflow;

    newExDTCStatus2 = ExtendDTCStatus2;

    if( resetConfirmedBitOnOverflow == DEM_STATUS_BIT_RESET_CDTC_WITH_PDTC )
    {
        newExDTCStatus2 =   ExtendDTCStatus2 & ~( DEM_DTCSTATUSEX2_STATUS_INDICATOR_AT_CYCLESTART | DEM_DTCSTATUSEX2_STATUS_CONTINUOUS_MI_HISTORY );
    }
    return newExDTCStatus2;
}

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTC_ExDTC2_SetPendingOfEmission                      */
/* Description   | Turn on Extend DTC status2 bit(MisfPendingOfEmission)    */
/* Preconditions | none                                                     */
/* Parameters    | [in] ExtendDTCStatus2 : DTC status before the change.    */
/* Return Value  | Dem_u08_DTCStatusEx2Type                                 */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.based on Dem_DTC_ExDTC2_SetEventDisable().   */
/****************************************************************************/
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_SetPendingOfEmission
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2
)
{
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) retVal;

     /* Turns on Extend DTC status bit */
    retVal = ( ExtendDTCStatus2 | DEM_DTCSTATUSEX2_STATUS_MISF_PENDINGOFEMISSION );

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DTC_ExDTC2_ResetPendingOfEmission                    */
/* Description   | Turn off Extend DTC status2 bit(MisfPendingOfEmission)   */
/* Preconditions | none                                                     */
/* Parameters    | [in] ExtendDTCStatus2 : DTC status before the change.    */
/* Return Value  | Dem_u08_DTCStatusEx2Type                                 */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.based on Dem_DTC_ExDTC2_ClearEventDisable(). */
/****************************************************************************/
FUNC( Dem_u08_DTCStatusEx2Type, DEM_CODE ) Dem_DTC_ExDTC2_ResetPendingOfEmission
(
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendDTCStatus2
)
{
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) retVal;

     /* Turns off Extend DTC status bit */
    retVal = ( ExtendDTCStatus2 & ~DEM_DTCSTATUSEX2_STATUS_MISF_PENDINGOFEMISSION );

    return retVal;
}
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
