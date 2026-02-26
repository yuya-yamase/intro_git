/* Dem_Similar_OpCycle_c(v5-3-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Similar_OpCycle/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_Rc_SimilarMng.h"
#include "../../../inc/Dem_Pm_Similar.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "./Dem_Similar_local.h"
#include "./Dem_Similar_EventEntry_local.h"


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
static FUNC( Dem_u08_InternalReturnType, DEM_CODE) Dem_Similar_GetPendingClearCntThreshold
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u08_SimilarPendingClearCounterType, AUTOMATIC, AUTOMATIC ) ThresholdPtr
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
/* Function Name | Dem_Similar_PreProccessByCycleStart                      */
/* Description   | Pre Proccess By Cycle Start                              */
/* Preconditions | none                                                     */
/* Parameters    | nnoe                                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_PreProccessByCycleStart
(void)
{
    Dem_Similar_SetConditionStoreBeforeDcyToTmp( (boolean)FALSE );

    return;
}

/****************************************************************************/
/* Function Name | Dem_Similar_CheckSimilarPassedThisDCYFromTmp             */
/* Description   | Check Similar Passed This DCY From Tmp                   */
/* Preconditions | none                                                     */
/* Parameters    | nnoe                                                     */
/* Return Value  | boolean                                                  */
/*               |         TRUE                                             */
/*               |         FALSE                                            */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE) Dem_Similar_CheckSimilarPassedThisDCYFromTmp
(void)
{
    VAR( boolean, AUTOMATIC ) similarPassedThisDcy;

    similarPassedThisDcy = (boolean)FALSE;
    Dem_Similar_GetSimilarPassedThisDcyToTmp( &similarPassedThisDcy );

    return similarPassedThisDcy;
}

/****************************************************************************/
/* Function Name | Dem_Similar_CheckReachedPendingEraseCycCntThreshold      */
/* Description   | Check Reached Pending Erase Cyc Cnt Threshold            */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStrgIndex                                     */
/* Return Value  | boolean                                                  */
/*               |         TRUE                                             */
/*               |         FALSE                                            */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE) Dem_Similar_CheckReachedPendingEraseCycCntThreshold
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) checkResult;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) result;
    VAR( Dem_u08_SimilarPendingClearCounterType, AUTOMATIC ) pendingEraseCycCounter;
    VAR( Dem_u08_SimilarPendingClearCounterType, AUTOMATIC ) threshold;

    checkResult = (boolean)FALSE;

    pendingEraseCycCounter = (Dem_u08_SimilarPendingClearCounterType)0U;
    Dem_Similar_GetPendingEraseCycCounterToTmp( &pendingEraseCycCounter );

    threshold = (Dem_u08_SimilarPendingClearCounterType)0U;
    result = Dem_Similar_GetPendingClearCntThreshold( EventStrgIndex, &threshold );

    if( result == DEM_IRT_OK )
    {
        if( pendingEraseCycCounter < threshold )
        {
            pendingEraseCycCounter++;
        }

        if( pendingEraseCycCounter >= threshold )
        {
            pendingEraseCycCounter = (Dem_u08_SimilarPendingClearCounterType)0U;
            checkResult = (boolean)TRUE;
        }

        Dem_Similar_SetPendingEraseCycCounterToTmp( pendingEraseCycCounter );
    }

    return checkResult;
}

/****************************************************************************/
/* Function Name | Dem_Similar_ProcessForEventFailed                        */
/* Description   | Store Similar Condition                                  */
/* Preconditions | none                                                     */
/* Parameters    | [in]  ChkBitStatusOldPtr                                 */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE) Dem_Similar_ProcessForEventFailed
(
    P2CONST( Dem_ChkBitDTCStatusType, AUTOMATIC, AUTOMATIC ) ChkBitStatusOldPtr
)
{
    VAR( boolean, AUTOMATIC ) similarConditionStoredflg;

    if( ChkBitStatusOldPtr->PendingDTC == (boolean)TRUE )
    {
        similarConditionStoredflg = (boolean)FALSE;

        Dem_Similar_GetConditionStoredflgToTmp( &similarConditionStoredflg );

        if( ( ChkBitStatusOldPtr->WirStatus == (boolean)FALSE )
         || ( similarConditionStoredflg     == (boolean)FALSE ) )
        {
            Dem_Similar_SetConditionStoreBeforeDcyToTmp( (boolean)TRUE );

            Dem_Similar_SetConditionStoredflgToTmp( (boolean)TRUE );

            Dem_Similar_UpdateSimilarConditionStoredListToTmp();
        }
        Dem_Similar_ClearSimilarConditionLatchedToTmp();
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Similar_ClearTmpByCycleStart                         */
/* Description   | Check Pending Recovery Possible                          */
/* Preconditions | none                                                     */
/* Parameters    | [in]  NewStatus                                          */
/* Return Value  | nnoe                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_ClearTmpByCycleStart
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) NewStatus
)
{
    Dem_Similar_SetSimilarPassedThisDcyToTmp( (boolean)FALSE );
    Dem_Similar_SetExceedanceCounterToTmp( (Dem_u08_SimilarExceedanceCounterType)0U );

    if( ( NewStatus & ( DEM_UDS_STATUS_PDTC | DEM_UDS_STATUS_WIR ) ) == (Dem_UdsStatusByteType)0U ) /*  statusOfDTC : bit2,7    */
    {
        Dem_Similar_SetConditionStoredflgToTmp( (boolean)FALSE );
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Similar_ChkSpCondToOpCycUpdateQualified              */
/* Description   | Check specific condition to opeCycle update qualified    */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStrgIndex                                     */
/*               | [out] ChkSpCondPtr : check Specific Cond                 */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_ChkSpCondToOpCycUpdateQualified
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_ChkSpCondType, AUTOMATIC, AUTOMATIC ) ChkSpCondPtr
)
{
    VAR( Dem_u08_SimilarExceedanceCounterType, AUTOMATIC ) getExceedanceCounter;
    VAR( boolean, AUTOMATIC ) usedExceedance;

    usedExceedance =  Dem_Similar_CheckExceedanceUsed( EventStrgIndex );
    if( usedExceedance == (boolean)TRUE )
    {
        Dem_Similar_GetExceedanceCounterToTmp( &getExceedanceCounter );
        if( getExceedanceCounter > (Dem_u08_SimilarExceedanceCounterType)0U )
        {
            ChkSpCondPtr->Healing = (boolean)FALSE;
            ChkSpCondPtr->Aging   = (boolean)FALSE;
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Similar_CheckPendingRecoveryPossible                 */
/* Description   | Check Pending Recovery Possible                          */
/* Preconditions | none                                                     */
/* Parameters    | nnoe                                                     */
/* Return Value  | boolean                                                  */
/*               |         TRUE                                             */
/*               |         FALSE                                            */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE) Dem_Similar_CheckPendingRecoveryPossible
(void)
{
    return Dem_SimilarOemIncrementType;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Dem_Similar_GetPendingClearCntThreshold                  */
/* Description   | Get Pending Clear Cnt Threshold                          */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStrgIndex                                     */
/*               | [out] ThresholdPtr                                       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |         DEM_IRT_OK                                       */
/*               |         DEM_IRT_NG                                       */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE) Dem_Similar_GetPendingClearCntThreshold
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u08_SimilarPendingClearCounterType, AUTOMATIC, AUTOMATIC ) ThresholdPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) similarStrgIndex;

    retVal = DEM_IRT_NG;

    retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToSimilarStrgIndex( EventStrgIndex, &similarStrgIndex );
    if ( retCnvId == DEM_IRT_OK )
    {
        /*  similarStrgIndex : value range check in Dem_CfgInfoPm_CnvEventStrgIndexToSimilarStrgIndex().        */
        (*ThresholdPtr) = Dem_CfgInfoPm_GetPendingClearCntThreshold( similarStrgIndex );
        retVal = DEM_IRT_OK;
    }

    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
