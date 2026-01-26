/* Dem_DTC_PFC_UpdateOrder_Misfire_c(v5-5-0)                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DTC_PFC_UpdateOrder_Misfire/CODE                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "Dem_DTC_PFC_local.h"

#if ( DEM_PFC_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../../inc/Dem_Pm_DTC_PFC.h"
#include "../../../../inc/Dem_Pm_Misfire.h"
#include "../../../../inc/Dem_Rc_MisfireMng.h"
#include "../../../../inc/Dem_Rc_PFCMng.h"
#include "../../../../cfg/Dem_Misfire_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_CheckPFCStoredState
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) NumberOfPFCRecordEmpty,
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) OrderListIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) StoredPFCMisFireEventStrgIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) StoredMisFirePFCMisFireEventStrgIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) LoopEndFlagPtr
);

static FUNC( void, DEM_CODE ) Dem_DTC_SearchNextSpacePFCRecordIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC) EventStrgIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC) StoredPFCMisFireEventStrgIndex,
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) BasePFCRecordIndex,
    P2VAR( Dem_u08_PFCIndexType, AUTOMATIC, AUTOMATIC ) PFCRecordIndexPtr
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
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_DTC_UpdatePFCRecordByOrder                           */
/* Description   | Update Permanent memory record process.                  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_UpdatePFCRecordByOrder
( void )
{
    VAR( boolean, AUTOMATIC ) loopEndFlag;
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckPFCStoredState;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckResult;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) numberOfPFCRecordEmpty;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordIndex;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) basePFCRecordIndex;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) loopCnt;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) misfirePFCRecordIndex;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) maxNumberEventEntryPermanent;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) pfcRecordEventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) storedPFCMisFireEventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) storedMisFirePFCMisFireEventStrgIndex;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndexMax;

    numberOfPFCRecordEmpty = (Dem_u08_PFCIndexType)0U;
    maxNumberEventEntryPermanent = Dem_MaxNumberEventEntryPermanent;
    basePFCRecordIndex = (Dem_u08_PFCIndexType)0U;
    eventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
    storedPFCMisFireEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
    misfirePFCRecordIndex = Dem_MisfirePFCRecordIndex;

    for( loopCnt = (Dem_u08_PFCIndexType)0U; loopCnt < maxNumberEventEntryPermanent; loopCnt++ )
    {
        (void)Dem_PFCMng_GetPFCRecordData( loopCnt, &pfcRecordEventStrgIndex ); /* no return check required */  /* [GUD]loopCnt */

        /* Check event available status, MIL indicator and OBD. */
        retCheckResult = Dem_DTC_CheckAvailableAndMILStatusByEventStrgIndex( pfcRecordEventStrgIndex );          /* [GUD]pfcRecordEventStrgIndex */
        if( retCheckResult == DEM_IRT_OK )
        {
            /*  check MISFIRE eventStrgIndex.       */
            misfireEventKind    =   Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( pfcRecordEventStrgIndex );
            if( misfireEventKind == (boolean)TRUE )
            {
                storedPFCMisFireEventStrgIndex = pfcRecordEventStrgIndex;
            }
        }
        else
        {
            numberOfPFCRecordEmpty = numberOfPFCRecordEmpty + (Dem_u08_PFCIndexType)1U;
        }
    }

    /* Check event available status, MIL indicator and OBD in misfire space. */
    (void)Dem_PFCMng_GetStoredMisfireSpaceEventStrgIndex( &storedMisFirePFCMisFireEventStrgIndex ); /* no return check required */

    /* Gets the event memory record of primary memory. */
    orderListIndexMax   =   Dem_DTC_GetUpdateOrderMaxCount();
    for( orderListIndex = (Dem_u08_OrderIndexType)0U; orderListIndex < orderListIndexMax; orderListIndex++ )
    {
        retCheckPFCStoredState = Dem_DTC_CheckPFCStoredState( numberOfPFCRecordEmpty, orderListIndex, storedPFCMisFireEventStrgIndex, storedMisFirePFCMisFireEventStrgIndex, &eventStrgIndex, &loopEndFlag );

        if( retCheckPFCStoredState == DEM_IRT_OK )
        {
            pfcRecordIndex  =   DEM_PFC_RECORD_INDEX_INITIAL;
            Dem_DTC_SearchNextSpacePFCRecordIndex( eventStrgIndex, storedPFCMisFireEventStrgIndex, basePFCRecordIndex, &pfcRecordIndex );

            /* Set the PFCrecord. */
            Dem_DTC_SetPFCRecordWithClearCondition( pfcRecordIndex, eventStrgIndex );
            Dem_Misfire_UpdatePermanentCylByOrder( eventStrgIndex );

            if(( pfcRecordIndex != DEM_PFC_RECORD_INDEX_INITIAL ) && ( pfcRecordIndex != misfirePFCRecordIndex ))
            {
                basePFCRecordIndex = pfcRecordIndex;
                basePFCRecordIndex = basePFCRecordIndex + (Dem_u08_PFCIndexType)1U;
            }

            if( pfcRecordIndex != misfirePFCRecordIndex )
            {
                if( numberOfPFCRecordEmpty > (Dem_u08_PFCIndexType)0U )
                {
                    numberOfPFCRecordEmpty--;
                }

                misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( eventStrgIndex );

                if( misfireEventKind == (boolean)TRUE )
                {
                    storedPFCMisFireEventStrgIndex = eventStrgIndex;
                }
            }
            else
            {
                storedMisFirePFCMisFireEventStrgIndex = eventStrgIndex;
            }
        }
        if(loopEndFlag == (boolean)TRUE )
        {
            break;
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_DTC_CheckPFCStoredState                              */
/* Description   | Check pfc stored state.                                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] NumberOfPFCRecordEmpty :                            */
/*               | [in] OrderListIndex :                                    */
/*               | [in] StoredPFCMisFireEventStrgIndex :                    */
/*               | [in] StoredMisFirePFCMisFireEventStrgIndex :             */
/*               | [out] EventStrgIndexPtr :                                */
/*               | [out] LoopEndFlagPtr :                                   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_CheckPFCStoredState
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) NumberOfPFCRecordEmpty,
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) OrderListIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) StoredPFCMisFireEventStrgIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) StoredMisFirePFCMisFireEventStrgIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) LoopEndFlagPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckResult;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) checkEventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( boolean, AUTOMATIC ) OrderExistFlag;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfireEmissionEventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfireCATEventStrgIndex;
    VAR( boolean, AUTOMATIC ) checkLoopEndFlag;
    VAR( boolean, AUTOMATIC ) retCheckPFCUpdate;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;

    retVal = DEM_IRT_NG;
    checkEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
    misfireEmissionEventStrgIndex = Dem_CfgInfoPm_GetEventStrgIndex_MisfireEmission();
    misfireCATEventStrgIndex      = Dem_CfgInfoPm_GetEventStrgIndex_MisfireCAT();
    checkLoopEndFlag = (boolean)FALSE;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    statusOfDTC =   DEM_DTCSTATUS_BYTE_ALL_OFF;
    if( NumberOfPFCRecordEmpty != (Dem_u08_PFCIndexType)0U )
    {
        Dem_DTC_GetUpdateOrderEventStrgIndex( OrderListIndex, &checkEventStrgIndex, &faultIndex, &statusOfDTC, &OrderExistFlag );

        if( OrderExistFlag != (boolean)FALSE )
        {
            /* For reduction of processing load, check event index here. */
            /* Check event available status, MIL indicator and OBD. */
            retCheckResult = Dem_DTC_CheckAvailableAndMILStatusByEventStrgIndex( checkEventStrgIndex ); /* [GUD]checkEventStrgIndex */
            if( retCheckResult == DEM_IRT_OK )
            {
                if( NumberOfPFCRecordEmpty >= DEM_PFC_RECORD_ENOUGH_EMPTY_SPACE_NUM )
                {
                    *EventStrgIndexPtr = checkEventStrgIndex;
                }
                else
                {
                    if( StoredMisFirePFCMisFireEventStrgIndex == DEM_EVENTSTRGINDEX_INVALID )
                    {
                        *EventStrgIndexPtr = checkEventStrgIndex;
                    }
                    else
                    {
                        if( StoredPFCMisFireEventStrgIndex == DEM_EVENTSTRGINDEX_INVALID )
                        {
                            if( StoredMisFirePFCMisFireEventStrgIndex == misfireEmissionEventStrgIndex )
                            {
                                /* Check event available status, MIL indicator and OBD. */
                                retCheckResult = Dem_DTC_CheckAvailableAndMILStatusByEventStrgIndex( misfireCATEventStrgIndex ); /* [GUD]misfireCATEventStrgIndex */
                                if( retCheckResult == DEM_IRT_OK )
                                {
                                    *EventStrgIndexPtr = misfireCATEventStrgIndex;
                                }
                            }
                            else
                            {
                                /* Check event available status, MIL indicator and OBD. */
                                retCheckResult = Dem_DTC_CheckAvailableAndMILStatusByEventStrgIndex( misfireEmissionEventStrgIndex ); /* [GUD]misfireEmissionEventStrgIndex */
                                if( retCheckResult == DEM_IRT_OK )
                                {
                                    *EventStrgIndexPtr = misfireEmissionEventStrgIndex;
                                }
                            }
                            checkLoopEndFlag = (boolean)TRUE;
                        }
                        else
                        {
                            *EventStrgIndexPtr = checkEventStrgIndex;
                        }
                    }
                }
            }
        }
        else
        {
            checkLoopEndFlag = (boolean)TRUE;
        }
    }
    else
    {
        if( StoredPFCMisFireEventStrgIndex < eventStorageNum )
        {
            if( StoredPFCMisFireEventStrgIndex == misfireEmissionEventStrgIndex )
            {
                /* Check event available status, MIL indicator and OBD. */
                retCheckResult = Dem_DTC_CheckAvailableAndMILStatusByEventStrgIndex( misfireCATEventStrgIndex ); /* [GUD]misfireCATEventStrgIndex */
                if( retCheckResult == DEM_IRT_OK )
                {
                    *EventStrgIndexPtr = misfireCATEventStrgIndex;
                }
            }
            else
            {
                /* Check event available status, MIL indicator and OBD. */
                retCheckResult = Dem_DTC_CheckAvailableAndMILStatusByEventStrgIndex( misfireEmissionEventStrgIndex ); /* [GUD]misfireCATEventStrgIndex */
                if( retCheckResult == DEM_IRT_OK )
                {
                    *EventStrgIndexPtr = misfireEmissionEventStrgIndex;
                }
            }
        }
        checkLoopEndFlag = (boolean)TRUE;
    }
    *LoopEndFlagPtr = checkLoopEndFlag;

    if( *EventStrgIndexPtr < eventStorageNum )
    {
        retCheckPFCUpdate = Dem_DTC_CheckRegistPFCRecord( *EventStrgIndexPtr );

        if( retCheckPFCUpdate == (boolean)TRUE )
        {
            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DTC_SearchNextSpacePFCRecordIndex                    */
/* Description   | Search next space pfc record index.                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] StoredPFCMisFireEventStrgIndex :                    */
/*               | [in] BasePFCRecordIndex :                                */
/*               | [out] PFCRecordIndexPtr :                                */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DTC_SearchNextSpacePFCRecordIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC) EventStrgIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC) StoredPFCMisFireEventStrgIndex,
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) BasePFCRecordIndex,
    P2VAR( Dem_u08_PFCIndexType, AUTOMATIC, AUTOMATIC ) PFCRecordIndexPtr
)
{
    VAR( boolean, AUTOMATIC ) searched_Flag;
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) loopCnt;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) maxNumberEventEntryPermanent;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) pfcRecordEventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckResult;

    searched_Flag = (boolean)FALSE;
    maxNumberEventEntryPermanent = Dem_MaxNumberEventEntryPermanent;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );

    if( misfireEventKind == (boolean)TRUE )
    {
        if( StoredPFCMisFireEventStrgIndex < eventStorageNum )
        {
            *PFCRecordIndexPtr = Dem_MisfirePFCRecordIndex;
            searched_Flag = (boolean)TRUE;
        }
    }

    if( searched_Flag == (boolean)FALSE )
    {
        for( loopCnt = BasePFCRecordIndex; loopCnt < maxNumberEventEntryPermanent; loopCnt++ )
        {
            (void)Dem_PFCMng_GetPFCRecordData( loopCnt, &pfcRecordEventStrgIndex ); /* no return check required */  /* [GUD]loopCnt */

            /* Check event available status, MIL indicator and OBD. */
            retCheckResult = Dem_DTC_CheckAvailableAndMILStatusByEventStrgIndex( pfcRecordEventStrgIndex ); /* [GUD]pfcRecordEventStrgIndex */
            if( retCheckResult == DEM_IRT_NG )
            {
                /* Event is not available or invalid. */
                *PFCRecordIndexPtr = loopCnt;
                break;
            }
        }
    }

    return;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON ) */
#endif  /* ( DEM_PFC_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
