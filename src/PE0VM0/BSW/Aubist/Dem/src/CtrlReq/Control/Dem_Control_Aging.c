/* Dem_Control_Aging_c(v5-5-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_Aging/CODE                                    */
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
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_CmnLib_OpCycle.h"
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

static FUNC( boolean, DEM_CODE ) Dem_Control_CheckAgingConditionByDTCStatus
(
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) DTCStatusStPtr,
    VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC ) HealingAgingCycleFlag    /* MISRA DEVIATION */
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
/* Function Name | Dem_Control_CheckAgingConditionByEventStrgIndex          */
/* Description   | Judgment of the aging condition by the event index.      */
/* Preconditions | call Dem_Control_SaveEventMemoryEntryToTmp().            */
/* Parameters    | [in] EventStrgIndex : Event index.                       */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : Aging permission                          */
/*               |        FALSE : Aging prohibition                         */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Control_CheckAgingConditionByEventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) retChkExistsEventMemEntryOfTmp;

    retVal = (boolean)FALSE;

    /*  check aging cycle update.       */
    retChkExistsEventMemEntryOfTmp = Dem_Data_CheckExistsEventMemoryEntryOfTmp();

    if( retChkExistsEventMemEntryOfTmp == (boolean)TRUE )
    {
        retVal = Dem_CfgInfoPm_GetAgingAllowed( EventStrgIndex );
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_ProcessAging                                 */
/* Description   | Aging process.                                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] HealingAgingCycleFlag :                             */
/*               |          check HealingAgingCycle or not.                 */
/*               | [in] PendingRecoveryExecFlag :                           */
/*               |          check pending recovery was executed.            */
/*               | [in] EventStrgIndex : Event index.                       */
/*               | [in] OldDTCStatusStPtr : statusOfDTC.                    */
/*               | [out] AgingExecFlagPtr : Aging condition flag.           */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_ProcessAging
(
    VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC ) HealingAgingCycleFlag,
    VAR( boolean, AUTOMATIC ) PendingRecoveryExecFlag,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) OldDTCStatusStPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) AgingExecFlagPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckAgingRequire;
    VAR( Dem_u08_AgingCounterType, AUTOMATIC ) agingCounter;
    VAR( Dem_u08_AgingCounterType, AUTOMATIC ) agingCounterThreshold;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetAgingCounterFromTmp;
    VAR( boolean, AUTOMATIC ) agingExecFlag;
    VAR( boolean, AUTOMATIC ) retCheckAgingCondition;
#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
    VAR( Dem_u16_WWHOBDTimeAgingCounterType, AUTOMATIC ) timeAgingCounter;
    VAR( Dem_u16_WWHOBDTimeAgingCounterType, AUTOMATIC ) timeAgingCounterAdd;
    VAR( Dem_u16_WWHOBDTimeAgingCounterType, AUTOMATIC ) timeAgingCounterThreshold;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetTimeAgingCounterFromTmp;
    VAR( boolean, AUTOMATIC ) timeAgingExecFlag;
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

    agingExecFlag = (boolean)FALSE;
#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
    timeAgingExecFlag = (boolean)FALSE;
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

    retCheckAgingCondition = Dem_Control_CheckAgingConditionByDTCStatus( OldDTCStatusStPtr, HealingAgingCycleFlag );
    if( retCheckAgingCondition == (boolean)TRUE )
    {
        retCheckAgingRequire = Dem_CfgInfo_JudgeAgingRequire( OldDTCStatusStPtr, HealingAgingCycleFlag, PendingRecoveryExecFlag );
        if( ( HealingAgingCycleFlag & DEM_OPCYCUPD_HACYC_EXEC_AGING ) == DEM_OPCYCUPD_HACYC_EXEC_AGING )
        {
            if( retCheckAgingRequire == DEM_IRT_OK )
            {
                agingCounterThreshold       =   Dem_CfgInfoPm_GetAgingCycleThreshold( EventStrgIndex );
                retGetAgingCounterFromTmp   =   Dem_Data_GetAgingCounterFromTmp( &agingCounter );
                if( retGetAgingCounterFromTmp == DEM_IRT_OK )
                {
                    if( agingCounter < DEM_AGING_COUNT_MAX_VALUE )
                    {
                        agingCounter++;
                    }

                    if( agingCounter >= agingCounterThreshold )
                    {
                        agingExecFlag = (boolean)TRUE;
                    }
                    else
                    {
                        agingExecFlag = (boolean)FALSE;
                    }

                   Dem_Data_SetAgingCounterToTmp( agingCounter );
                }
            }
        }
#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
        if( ( HealingAgingCycleFlag & DEM_OPCYCUPD_HACYC_UPDATE_TIME_AGINGCYC ) == DEM_OPCYCUPD_HACYC_UPDATE_TIME_AGINGCYC )
        {
            if( retCheckAgingRequire == DEM_IRT_OK )
            {
                timeAgingCounterAdd             =   Dem_Control_GetTimeSinceEngineStartSinceLastDCY();
                timeAgingCounterThreshold       =   Dem_CfgInfoPm_GetTimeAgingCounterThreshold();
                retGetTimeAgingCounterFromTmp   =   Dem_Data_GetTimeAgingCounterFromTmp( &timeAgingCounter );
                if( retGetTimeAgingCounterFromTmp == DEM_IRT_OK )
                {
                    if( timeAgingCounter < ( DEM_TIME_AGING_COUNT_MAX_VALUE - timeAgingCounterAdd ) )
                    {
                        timeAgingCounter = timeAgingCounter + timeAgingCounterAdd;
                    }
                    else
                    {
                        timeAgingCounter = DEM_TIME_AGING_COUNT_MAX_VALUE;
                    }

                    if( timeAgingCounter >= timeAgingCounterThreshold )
                    {
                        timeAgingExecFlag = (boolean)TRUE;
                    }
                    else
                    {
                        timeAgingExecFlag = (boolean)FALSE;
                    }

                    Dem_Data_SetTimeAgingCounterToTmp( timeAgingCounter );
                }
            }
        }
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */
    }

#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
    if( timeAgingExecFlag == (boolean)TRUE )
    {
        agingExecFlag = (boolean)TRUE;
    }
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

    if( agingExecFlag == (boolean)TRUE )
    {
        *AgingExecFlagPtr = (boolean)TRUE;
    }
    else
    {
        *AgingExecFlagPtr = (boolean)FALSE;
    }

    return ;
}

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_ProcessAgingForWWHOBD                        */
/* Description   | Aging process for WWH-OBD.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex : Event index.                       */
/*               | [in] NewDTCStatusStPtr : statusOfDTC.                    */
/*               | [out] AgingExecFlagPtr : Aging condition flag.           */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_Control_ProcessAging.          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_ProcessAgingForWWHOBD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) AgingExecFlagPtr
)
{
    VAR( Dem_u08_AgingCounterType, AUTOMATIC ) agingCounter;
    VAR( Dem_u08_AgingCounterType, AUTOMATIC ) agingCounterThreshold;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetAgingCounterFromTmp;

    VAR( Dem_u16_WWHOBDTimeAgingCounterType, AUTOMATIC ) timeAgingCounter;
    VAR( Dem_u16_WWHOBDTimeAgingCounterType, AUTOMATIC ) timeAgingCounterThreshold;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetTimeAgingCounterFromTmp;

    VAR( boolean, AUTOMATIC ) agingExecFlag;

    agingExecFlag = (boolean)FALSE;

    if( ( NewDTCStatusStPtr->DTCStatus & DEM_UDS_STATUS_CDTC ) == DEM_UDS_STATUS_CDTC )    /*  statusOfDTC : bit3  */
    {
        /*  Indicator Flag is OFF   */
        if( ( NewDTCStatusStPtr->ExtendDTCStatus & DEM_DTCSTATUSEX_STATUS_INDICATOR ) == DEM_DTCSTATUSEX_BYTE_ALL_OFF )
        {
            agingCounterThreshold       =   Dem_CfgInfoPm_GetAgingCycleThreshold( EventStrgIndex );
            retGetAgingCounterFromTmp   =   Dem_Data_GetAgingCounterFromTmp( &agingCounter );
            if( retGetAgingCounterFromTmp == DEM_IRT_OK )
            {
                if( agingCounter >= agingCounterThreshold )
                {
                    agingExecFlag = (boolean)TRUE;
                }
            }

            timeAgingCounterThreshold       =   Dem_CfgInfoPm_GetTimeAgingCounterThreshold();
            retGetTimeAgingCounterFromTmp   =   Dem_Data_GetTimeAgingCounterFromTmp( &timeAgingCounter );
            if( retGetTimeAgingCounterFromTmp == DEM_IRT_OK )
            {
                if( timeAgingCounter >= timeAgingCounterThreshold )
                {
                    agingExecFlag = (boolean)TRUE;
                }
            }
        }
    }

    *AgingExecFlagPtr = agingExecFlag;

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Control_CheckAgingConditionByDTCStatus               */
/* Description   | Judgment of the aging condition by the statusOfDTC.      */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatusStPtr : statusOfDTC.                       */
/*               | [in] HealingAgingCycleFlag :                             */
/*               |          check HealingAgingCycle or not.                 */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : Aging permission                          */
/*               |        FALSE : Aging prohibition                         */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Control_CheckAgingConditionByDTCStatus
(
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) DTCStatusStPtr,
    VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC ) HealingAgingCycleFlag
)
{
    VAR( boolean, AUTOMATIC ) retVal;

    /*  Aging is not allowed.   */
    retVal = (boolean)FALSE;

    if( ( DTCStatusStPtr->DTCStatus & DEM_UDS_STATUS_CDTC ) == DEM_UDS_STATUS_CDTC )    /*  statusOfDTC : bit3  */
    {
        if( ( HealingAgingCycleFlag & DEM_OPCYCUPD_HACYC_EXEC_WWHOBD_AGING ) == DEM_OPCYCUPD_HACYC_EXEC_WWHOBD_AGING )
        {
            /*  For WWH-OBD, no need to check Indicator Flag if this cycle is AgingCycle.   */

            /*  Aging is allowed.   */
            retVal = (boolean)TRUE;
        }
        else
        {
            /*  For WWH-OBD, need to check Indicator Flag if this cycle is not AgingCycle.  */
            /*  Indicator Flag is OFF   */
            if( ( DTCStatusStPtr->ExtendDTCStatus & DEM_DTCSTATUSEX_STATUS_INDICATOR ) == DEM_DTCSTATUSEX_BYTE_ALL_OFF )
            {
                /*  Aging is allowed.   */
                retVal = (boolean)TRUE;
            }
        }
    }

    return retVal;
}
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

#if ( DEM_WWH_OBD_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_Control_CheckAgingConditionByDTCStatus               */
/* Description   | Judgment of the aging condition by the statusOfDTC.      */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatusStPtr : statusOfDTC.                       */
/*               | [in] HealingAgingCycleFlag :                             */
/*               |          check HealingAgingCycle or not.                 */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : Aging permission                          */
/*               |        FALSE : Aging prohibition                         */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Control_CheckAgingConditionByDTCStatus
(
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) DTCStatusStPtr,
    VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC ) HealingAgingCycleFlag    /* MISRA DEVIATION */
)
{
    VAR( boolean, AUTOMATIC ) retVal;

    /*  Aging is not allowed.   */
    retVal = (boolean)FALSE;

    if( ( DTCStatusStPtr->DTCStatus & DEM_UDS_STATUS_CDTC ) == DEM_UDS_STATUS_CDTC )    /*  statusOfDTC : bit3  */
    {
        /*  Indicator Flag is OFF   */
        if( ( DTCStatusStPtr->ExtendDTCStatus & DEM_DTCSTATUSEX_STATUS_INDICATOR ) == DEM_DTCSTATUSEX_BYTE_ALL_OFF )
        {
            /*  Aging is allowed.   */
            retVal = (boolean)TRUE;
        }
    }

    return retVal;
}
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_OFF ) */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
