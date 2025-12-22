/* Dem_Similar_EventEntryMake_c(v5-3-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Similar_EventEntryMake/CODE                           */
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
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Pm_Similar.h"
#include "../../../inc/Dem_Rc_SimilarMng.h"
#include "../../../inc/Dem_CmnLib_AsyncReqTable.h"
#include "../../../inc/Dem_Utl_Similar.h"
#include "Dem_Similar_local.h"
#include "Dem_Similar_EventEntry_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_MISFIRE_EXCEEDANCECOUNTER_2 ((Dem_u08_MisfExceedanceCounterType)2U)

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
/* Function Name | Dem_Similar_GetConditionStoredListToTmp                  */
/* Description   | Get similar condition(stored) in the temporary area.     */
/* Preconditions | none                                                     */
/* Parameters    | [out] SimilarConditionPtr :                              */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_GetConditionStoredListToTmp
(
    P2VAR( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) SimilarConditionPtr
)
{
    Dem_UtlSimilar_CopySimilarConditionArray( SimilarConditionPtr, &Dem_TmpSimilarEventMemoryEntry.SimilarRecord.SimilarConditionStoredList[0] );
    return;
}


/****************************************************************************/
/* Function Name | Dem_Similar_UpdateSimilarConditionStoredListToTmp        */
/* Description   | Update similar condition(stored) in the temporary area.  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_UpdateSimilarConditionStoredListToTmp
(void)
{
    Dem_UtlSimilar_CopySimilarConditionArray( &Dem_TmpSimilarEventMemoryEntry.SimilarRecord.SimilarConditionStoredList[0], &Dem_TmpSimilarEventMemoryEntry.SimilarRecord.SimilarConditionLatchedList[0] );
    return;
}

/****************************************************************************/
/* Function Name | Dem_Similar_SetConditionLatchedToTmp                     */
/* Description   | Set similar condition(latched) in the temporary area.    */
/* Preconditions | none                                                     */
/* Parameters    | [out] SimilarConditionPtr :                              */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_SetConditionLatchedToTmp
(
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) SimilarConditionPtr
)
{
    Dem_UtlSimilar_CopySimilarConditionArray( &Dem_TmpSimilarEventMemoryEntry.SimilarRecord.SimilarConditionLatchedList[0], SimilarConditionPtr );
    return;
}

/****************************************************************************/
/* Function Name | Dem_Similar_ClearSimilarConditionLatchedToTmp            */
/* Description   | Clear similar condition(latched) in the temporary area.  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_ClearSimilarConditionLatchedToTmp
(void)
{
    Dem_UtlSimilar_SetSimilarConditionArray( &Dem_TmpSimilarEventMemoryEntry.SimilarRecord.SimilarConditionLatchedList[0], (Dem_SimilarConditionValueType)0U );
    return;
}


/****************************************************************************/
/* Function Name | Dem_Similar_SetConditionStoredflgToTmp                   */
/* Description   | Set SimilarConditionStoredflg in the temporary area.     */
/* Preconditions | none                                                     */
/* Parameters    | [in] SimilarConditionStoredflg :                         */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_SetConditionStoredflgToTmp
(
    VAR( boolean, AUTOMATIC ) SimilarConditionStoredflg
)
{
    Dem_TmpSimilarEventMemoryEntry.SimilarRecord.SimilarConditionStoredflg = SimilarConditionStoredflg;
    return;
}

/****************************************************************************/
/* Function Name | Dem_Similar_GetConditionStoredflgToTmp                   */
/* Description   | Get SimilarConditionStoredflg in the temporary area.     */
/* Preconditions | none                                                     */
/* Parameters    | [out] SimilarConditionStoredflgPtr :                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_GetConditionStoredflgToTmp
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) SimilarConditionStoredflgPtr
)
{
    *SimilarConditionStoredflgPtr = Dem_TmpSimilarEventMemoryEntry.SimilarRecord.SimilarConditionStoredflg;
    return;
}

/****************************************************************************/
/* Function Name | Dem_Similar_SetPendingEraseCycCounterToTmp               */
/* Description   | Set PendingEraseCycCounter in the temporary area.        */
/* Preconditions | none                                                     */
/* Parameters    | [in] PendingEraseCycCounter :                            */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_SetPendingEraseCycCounterToTmp
(
    VAR( Dem_u08_SimilarPendingClearCounterType, AUTOMATIC ) PendingEraseCycCounter
)
{
    Dem_TmpSimilarEventMemoryEntry.SimilarRecord.PendingEraseCycCounter = PendingEraseCycCounter;
    return;
}


/****************************************************************************/
/* Function Name | Dem_Similar_GetPendingEraseCycCounterToTmp               */
/* Description   | Get PendingEraseCycCounter in the temporary area.        */
/* Preconditions | none                                                     */
/* Parameters    | [out] PendingEraseCycCounterPtr :                        */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_GetPendingEraseCycCounterToTmp
(
    P2VAR( Dem_u08_SimilarPendingClearCounterType, AUTOMATIC, AUTOMATIC ) PendingEraseCycCounterPtr
)
{
    *PendingEraseCycCounterPtr = Dem_TmpSimilarEventMemoryEntry.SimilarRecord.PendingEraseCycCounter;
    return;
}


/****************************************************************************/
/* Function Name | Dem_Similar_SetExceedanceCounterToTmp                    */
/* Description   | Set ExceedanceCounter in the temporary area.             */
/* Preconditions | none                                                     */
/* Parameters    | [in] ExceedanceCounter :                                 */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_SetExceedanceCounterToTmp
(
    VAR( Dem_u08_SimilarExceedanceCounterType, AUTOMATIC ) ExceedanceCounter
)
{
    Dem_TmpSimilarEventMemoryEntry.SimilarRecord.ExceedanceCounter = ExceedanceCounter;
    return;
}


/****************************************************************************/
/* Function Name | Dem_Similar_GetExceedanceCounterToTmp                    */
/* Description   | Get ExceedanceCounter in the temporary area.             */
/* Preconditions | none                                                     */
/* Parameters    | [out] ExceedanceCounterPtr :                             */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_GetExceedanceCounterToTmp
(
    P2VAR( Dem_u08_SimilarExceedanceCounterType, AUTOMATIC, AUTOMATIC ) ExceedanceCounterPtr
)
{
    *ExceedanceCounterPtr = Dem_TmpSimilarEventMemoryEntry.SimilarRecord.ExceedanceCounter;
    return;
}


/****************************************************************************/
/* Function Name | Dem_Similar_SetSimilarPassedThisDcyToTmp                 */
/* Description   | Set SimilarPassedThisDcy in the temporary area.          */
/* Preconditions | none                                                     */
/* Parameters    | [in] SimilarPassedThisDcy :                              */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_SetSimilarPassedThisDcyToTmp
(
    VAR( boolean, AUTOMATIC ) SimilarPassedThisDcy
)
{
    Dem_TmpSimilarEventMemoryEntry.SimilarRecord.SimilarPassedThisDcy = SimilarPassedThisDcy;
    return;
}


/****************************************************************************/
/* Function Name | Dem_Similar_GetSimilarPassedThisDcyToTmp                 */
/* Description   | Get SimilarPassedThisDcy in the temporary area.          */
/* Preconditions | none                                                     */
/* Parameters    | [out] SimilarPassedThisDcyPtr :                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_GetSimilarPassedThisDcyToTmp
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) SimilarPassedThisDcyPtr
)
{
    *SimilarPassedThisDcyPtr = Dem_TmpSimilarEventMemoryEntry.SimilarRecord.SimilarPassedThisDcy;
    return;
}


/****************************************************************************/
/* Function Name | Dem_Similar_SetConditionStoreBeforeDcyToTmp              */
/* Description   | Set SimilarConditionStoreBeforeDcy in the temporary area.*/
/* Preconditions | none                                                     */
/* Parameters    | [in] SimilarConditionStoreBeforeDcy :                    */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_SetConditionStoreBeforeDcyToTmp
(
    VAR( boolean, AUTOMATIC ) SimilarConditionStoreBeforeDcy
)
{
    Dem_TmpSimilarEventMemoryEntry.SimilarRecord.PendingStoreBeforeDcy = SimilarConditionStoreBeforeDcy;
    return;
}

/****************************************************************************/
/* Function Name | Dem_Similar_ClearPendingEraseCycCntOfTmp                 */
/* Description   | Clear PendingEraseCycleCounter in the temporary area.    */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_ClearPendingEraseCycCntOfTmp
(void)
{
    Dem_TmpSimilarEventMemoryEntry.SimilarRecord.PendingEraseCycCounter = DEM_SIMILAR_PENDINGERASECYCCOUNTER_INIT;

    return;
}


/****************************************************************************/
/* Function Name | Dem_Similar_GetConditionStoreBeforeDcyToTmp              */
/* Description   | Get SimilarConditionStoreBeforeDcy in the temporary area.*/
/* Preconditions | none                                                     */
/* Parameters    | [out] SimilarConditionStoreBeforeDcyPtr :                */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_GetConditionStoreBeforeDcyToTmp
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) SimilarConditionStoreBeforeDcyPtr
)
{
    *SimilarConditionStoreBeforeDcyPtr = Dem_TmpSimilarEventMemoryEntry.SimilarRecord.PendingStoreBeforeDcy;
    return;
}


#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Similar_ReachedExcessCntThreshold                    */
/* Description   | Similar processing at the time of excess conunter        */
/*               | threshold is exceeded.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] SimilarConditionPtr :                               */
/*               | [out] ResultOfChkSpecificfaultPtr :                      */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_ReachedExcessCntThreshold
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) SimilarConditionPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ResultOfChkSpecificfaultPtr
)
{
    VAR( boolean, AUTOMATIC ) chkGetSimilarCondStored;
    VAR( boolean, AUTOMATIC ) similarConditionStoreBeforeDcy;

    *ResultOfChkSpecificfaultPtr = (boolean)FALSE;  /*  initialize parameter.       */
    Dem_Similar_GetConditionStoredflgToTmp( &chkGetSimilarCondStored );
    if( chkGetSimilarCondStored == (boolean)TRUE )
    {
        /* Stored similar condition  */

        Dem_Similar_GetConditionStoreBeforeDcyToTmp( &similarConditionStoreBeforeDcy );
        if( similarConditionStoreBeforeDcy == (boolean)TRUE )
        {
            /* Similar condition update to the previous DCY */
            *ResultOfChkSpecificfaultPtr = (boolean)TRUE;
        }
        else
        {
            /* No similar condition update to the previous DCY */

            /* Judge similar condition */
            Dem_Similar_JudgeCondition( EventStrgIndex, SimilarConditionPtr, ResultOfChkSpecificfaultPtr );
        }
    }
    else
    {
        /* Not stored similar condition  */

        /* Store similar condition of Pending */
        Dem_Similar_ConditionStoredPending( SimilarConditionPtr );
        *ResultOfChkSpecificfaultPtr = (boolean)TRUE;
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Similar_NotReachedExcessCntThreshold                 */
/* Description   | Similar processing at the time of excess conunter        */
/*               | threshold is not exceeded.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] SimilarConditionPtr :                               */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_NotReachedExcessCntThreshold
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) SimilarConditionPtr
)
{
    VAR( boolean, AUTOMATIC ) chkGetSimilarCondStored;

    Dem_Similar_GetConditionStoredflgToTmp( &chkGetSimilarCondStored );
    if( chkGetSimilarCondStored != (boolean)TRUE )
    {
        /* Not stored similar condition  */

        /* Store similar condition of first exceedance */
        Dem_Similar_ConditionStoredFirstExceedance( EventStrgIndex, SimilarConditionPtr );
    }

    return;
}
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )   */


/****************************************************************************/
/* Function Name | Dem_Similar_JudgeCondition                               */
/* Description   | Judgment of SimilarCondition.                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] SimilarConditionPtr :                               */
/*               | [out] ResultOfChkSpecificfaultPtr :                      */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_JudgeCondition
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) SimilarConditionPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ResultOfChkSpecificfaultPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckSimilarCond;
    VAR( Dem_DTCStatusStType, AUTOMATIC ) dtcStatusSt;

    retCheckSimilarCond = Dem_Similar_CheckConditionForFailed( EventStrgIndex, SimilarConditionPtr );
    if( retCheckSimilarCond == DEM_IRT_OK )
    {
        /* Similar condition qualified */
        *ResultOfChkSpecificfaultPtr = (boolean)TRUE;
    }
    else
    {
        /* Similar condition not qualified */
        *ResultOfChkSpecificfaultPtr = (boolean)FALSE;

        /* Gets DTCStatus from tmporary */
        Dem_Data_GetDTCStatusStructFromTmp( &dtcStatusSt );
        if( ( dtcStatusSt.ExtendDTCStatus & DEM_DTCSTATUSEX_STATUS_TFTOC_IN_HEALINGCYCLE ) == DEM_DTCSTATUSEX_BYTE_ALL_OFF )
        {
            /* Latch the similar condition */
            Dem_Similar_SetConditionLatchedToTmp( SimilarConditionPtr );
        }
    }

    return;
}

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Similar_JudgeConditionWithCheckStored                */
/* Description   | Judgment of SimilarCondition(with check stored).         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] SimilarConditionPtr :                               */
/*               | [out] ResultOfChkSpecificfaultPtr :                      */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_JudgeConditionWithCheckStored
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) SimilarConditionPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ResultOfChkSpecificfaultPtr
)
{
    VAR( boolean, AUTOMATIC ) chkGetSimilarCondStored;

    *ResultOfChkSpecificfaultPtr    =   (boolean)FALSE; /*  initialize parameter.       */
    Dem_Similar_GetConditionStoredflgToTmp( &chkGetSimilarCondStored );
    if( chkGetSimilarCondStored == (boolean)TRUE )
    {
        Dem_Similar_JudgeCondition( EventStrgIndex, SimilarConditionPtr, ResultOfChkSpecificfaultPtr );
    }

    return;
}
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   */

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Similar_ConditionStoredPending                       */
/* Description   | Similar condition is stored(at PendingDTC).              */
/* Preconditions | none                                                     */
/* Parameters    | [in] SimilarConditionPtr :                               */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_ConditionStoredPending
(
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) SimilarConditionPtr
)
{
    VAR( Dem_u08_MisfSimCondStoredTimingType, AUTOMATIC ) misfireSimilarconditionStoredTiming;

    misfireSimilarconditionStoredTiming = Dem_MisfireSimilarconditionStoredTiming;

    if( misfireSimilarconditionStoredTiming == DEM_MF_SIMCOND_PENDINGDTC )
    {
        /* Latch the similar condition */
        Dem_Similar_SetConditionLatchedToTmp( SimilarConditionPtr );
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Similar_ConditionStoredFirstExceedance               */
/* Description   | Similar condition is stored(at FirstExceedance).         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Parameters    | [in] SimilarConditionPtr :                               */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_ConditionStoredFirstExceedance
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) SimilarConditionPtr
)
{
    VAR( Dem_u08_MisfExceedanceCounterType, AUTOMATIC ) excessCounter;
    VAR( Dem_u08_MisfSimCondStoredTimingType, AUTOMATIC ) misfireSimilarconditionStoredTiming;

    misfireSimilarconditionStoredTiming = Dem_MisfireSimilarconditionStoredTiming;

    if( misfireSimilarconditionStoredTiming == DEM_MF_SIMCOND_FIRSTEXCEEDANCE )
    {
        Dem_Misfire_GetExceedanceCounterToTmp( EventStrgIndex, &excessCounter );
        if( excessCounter < DEM_MISFIRE_EXCEEDANCECOUNTER_2  )
        {
            /* Latch the similar condition */
            Dem_Similar_SetConditionLatchedToTmp( SimilarConditionPtr );
        }
    }

    return;
}
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )   */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
