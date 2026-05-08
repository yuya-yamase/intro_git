/* Dem_Misfire_OpCycle_c(v5-9-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Misfire_OpCycle/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_CmnLib_DTC_DTCStatus.h"
#include "../../../inc/Dem_Rc_MisfireMng.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "./Dem_Misfire_local.h"
#include "./Dem_Misfire_EventEntry_local.h"


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

static FUNC( void, DEM_CODE ) Dem_Misfire_GetMisfirePairEventStatus
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) MisfirePairEventStatusPtr
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

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Misfire_ProcessPendingFaultRecovery                  */
/* Description   | Process Pending Fault Recovery                           */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStrgIndex : Event index                       */
/*               | [in/out] NewDTCStatusStPtr                               */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_ProcessPendingFaultRecovery
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr
)
{
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;
    eventKind   =   Dem_CfgInfoPm_GetEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );         /* [GUD:RET:Not DEM_EVTKIND_TYPE_NON_OBD_EVENT] EventStrgIndex  */

    /*  check misfire event : emission.     */
    if(( eventKind & ( DEM_EVTKIND_TYPE_MISFIRE_EVENT | DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT ) ) == DEM_EVTKIND_TYPE_MISFIRE_EVENT )
    {
        /*  emission misfire event. ( not misfire CAT event. )  */
        NewDTCStatusStPtr->ExtendDTCStatus2  =  Dem_DTC_ExDTC2_ResetPendingOfEmission( NewDTCStatusStPtr->ExtendDTCStatus2 );

        Dem_Misfire_SetPendingStoreOfEmission( (boolean)FALSE );
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_ProcessForEventFailed                        */
/* Description   | Process For Event Failed                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStrgIndex : Event index                       */
/*               | [in]  ChkOldBitStatusPtr                                 */
/*               | [in/out] NewDTCStatusStPtr                               */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_ProcessForEventFailed
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_ChkBitDTCStatusType, AUTOMATIC, AUTOMATIC ) ChkOldBitStatusPtr,
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr
)
{
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;

    if( ChkOldBitStatusPtr->PendingDTC == (boolean)TRUE )
    {
        eventKind   =   Dem_CfgInfoPm_GetEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );         /* [GUD:RET:Not DEM_EVTKIND_TYPE_NON_OBD_EVENT] EventStrgIndex  */
        if(( eventKind & ( DEM_EVTKIND_TYPE_MISFIRE_EVENT | DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT ) ) == DEM_EVTKIND_TYPE_MISFIRE_EVENT )
        {
            /*  emission misfire event. ( not misfire CAT event. )  */
            NewDTCStatusStPtr->ExtendDTCStatus2  =  Dem_DTC_ExDTC2_SetPendingOfEmission( NewDTCStatusStPtr->ExtendDTCStatus2 );

            Dem_Misfire_SetPendingStoreOfEmission( (boolean)TRUE );
        }
    }

    return;
}
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   */


/****************************************************************************/
/* Function Name | Dem_Misfire_ClearTmpByCycleStart                         */
/* Description   | Clear Tmp By Cycle Start                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStrgIndex : Event index                       */
/*               | [in]  NewDTCStatus                                       */
/*               | [in]  ChkOldBitStatusPtr                                 */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_ClearTmpByCycleStart
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) NewDTCStatus,
    P2CONST( Dem_ChkBitDTCStatusType, AUTOMATIC, AUTOMATIC ) ChkOldBitStatusPtr
)
{
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) misfirePairEventStatus;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) chkBothOfEventStatus;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireStrgIndex;

    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );
    if( misfireEventKind == (boolean)TRUE )
    {
        ( void )Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireStrgIndex ); /* no return check required */

        misfirePairEventStatus = (Dem_UdsStatusByteType)0U;

        Dem_Misfire_GetMisfirePairEventStatus( EventStrgIndex, &misfirePairEventStatus );

        chkBothOfEventStatus = (Dem_UdsStatusByteType)( NewDTCStatus | misfirePairEventStatus );

        Dem_Misfire_SetExceedanceCounterToTmp( EventStrgIndex, (Dem_u08_MisfExceedanceCounterType)0U );

        if( ChkOldBitStatusPtr->TestFailed == (boolean)TRUE )
        {
            if( ( NewDTCStatus & DEM_UDS_STATUS_TF ) == (Dem_UdsStatusByteType)0U )             /*  statusOfDTC : bit0  */
            {
                Dem_Misfire_ClearFailedCylToTmp( EventStrgIndex );
            }
        }

        /*  NOTE : The Healing Cycle for Misfire event is always the same as the OperationCycle.          */
        /*         So, TestFailedBitThisHealingCycle(extendDTCstatus :                                    */
        /*         DEM_DTCSTATUSEX_STATUS_TFTOC_IN_HEALINGCYCLE is always equal to statusOfDTC bit1.      */
        if( ChkOldBitStatusPtr->TestFailedThisHealingCycle == (boolean)TRUE )
        {
            if( ( chkBothOfEventStatus & DEM_UDS_STATUS_TFTOC ) == (Dem_UdsStatusByteType)0U )  /*  statusOfDTC : bit1  */
            {
                Dem_Misfire_ClearAccumFailedCylThisOCToTmp();
            }
        }

        if( ChkOldBitStatusPtr->PendingDTC == (boolean)TRUE )
        {
            if( ( chkBothOfEventStatus & DEM_UDS_STATUS_PDTC ) == (Dem_UdsStatusByteType)0U )   /*  statusOfDTC : bit2  */
            {
                Dem_Misfire_ClearAccumPendingCylToTmp();

                Dem_Misfire_SetFirstPendingCylToTmp( DEM_MISFIRE_CYLINDER_NON );
            }
        }

        if( ChkOldBitStatusPtr->ConfirmedDTC == (boolean)TRUE )
        {
            if( ( chkBothOfEventStatus & DEM_UDS_STATUS_CDTC ) == (Dem_UdsStatusByteType)0U )   /*  statusOfDTC : bit3  */
            {
                Dem_Misfire_ClearAccumConfirmedCylToTmp_AtAging();

                Dem_Misfire_SetFirstConfirmedCylToTmp( DEM_MISFIRE_CYLINDER_NON );
                Dem_Misfire_SetFirstAccumConfirmedCylToTmp( DEM_MISFIRE_CYLINDER_NON );
#if ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )
                Dem_Misfire_ClearConfirmedOrderCylListToTmp();
#endif /* ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON ) */
            }
        }

        if( ( ChkOldBitStatusPtr->PendingDTC   == (boolean)TRUE )
         || ( ChkOldBitStatusPtr->ConfirmedDTC == (boolean)TRUE ) )
        {
            if( ( NewDTCStatus & ( DEM_UDS_STATUS_PDTC | DEM_UDS_STATUS_CDTC ) ) == (Dem_UdsStatusByteType)0U ) /*  statusOfDTC : bit2,3    */
            {
                Dem_Misfire_ClearAccumCylToTmp( EventStrgIndex );
            }
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_ChkSpCondToOpCycUpdateQualified              */
/* Description   | Check specific condition to opeCycle update qualified    */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStrgIndex                                     */
/*               | [out] ChkSpCondPtr : check Specific Cond                 */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_ChkSpCondToOpCycUpdateQualified
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_ChkSpCondType, AUTOMATIC, AUTOMATIC ) ChkSpCondPtr
)
{
    VAR( Dem_u08_MisfExceedanceCounterType, AUTOMATIC ) getExceedanceCounter;
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;
    eventKind   =   Dem_CfgInfoPm_GetEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );         /* [GUD:RET:Not DEM_EVTKIND_TYPE_NON_OBD_EVENT] EventStrgIndex  */

    if(( eventKind & ( DEM_EVTKIND_TYPE_MISFIRE_EVENT | DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT ) ) == DEM_EVTKIND_TYPE_MISFIRE_EVENT )
    {
        /*  emission misfire event. ( not misfire CAT event. )  */
        getExceedanceCounter = (Dem_u08_MisfExceedanceCounterType)0U;
        Dem_Misfire_GetExceedanceCounterToTmp( EventStrgIndex, &getExceedanceCounter );
        if( getExceedanceCounter > (Dem_u08_MisfExceedanceCounterType)0U )
        {
            ChkSpCondPtr->Healing = (boolean)FALSE;
            ChkSpCondPtr->Aging   = (boolean)FALSE;
        }
    }

    return;
}

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Misfire_ClearDataRelatedAllObdFFD                    */
/* Description   | Clear Data Related FFD                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStrgIndex                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_ClearDataRelatedAllObdFFD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfirePairEventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetMisfirePairEvent;
    VAR( Dem_u08_MisfireKindType, AUTOMATIC ) misfireType;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) misfirePairEventFFDCyl;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndexNum;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndex;

    misfireObdFFDCylIndexNum = Dem_MisfireObdFFDCylIndexNum;

    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );
    if( misfireEventKind == (boolean)TRUE )
    {
        misfirePairEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
        resultGetMisfirePairEvent = Dem_CfgInfoPm_GetMisfirePairEventStrgIndexByStrgIndex( EventStrgIndex, &misfirePairEventStrgIndex );

        for( misfireObdFFDCylIndex = (Dem_u08_MisfireObdFFDCylIndexType)0U; misfireObdFFDCylIndex < misfireObdFFDCylIndexNum; misfireObdFFDCylIndex++ ) /* [GUD:for]misfireObdFFDCylIndex */
        {
            misfireType = DEM_MISFIRE_KIND_INVALID;
            /*--------------------------------------*/
            /*  action to misfire pair event.       */
            if( resultGetMisfirePairEvent == DEM_IRT_OK )
            {
                Dem_Misfire_GetObdFFDCylToTmp( misfirePairEventStrgIndex, misfireObdFFDCylIndex, &misfirePairEventFFDCyl );             /* [GUD]misfireObdFFDCylIndex */
                if( misfirePairEventFFDCyl != DEM_MISFIRE_CYLINDER_NON )
                {
                    misfireType =   Dem_CfgInfoPm_GetMisfireType_InEvtStrgGrp( misfirePairEventStrgIndex );
                }
            }
            /*--------------------------------------*/

            Dem_Misfire_SetMisfireKindOfObdFFDToTmp( misfireObdFFDCylIndex, misfireType );                                              /* [GUD]misfireObdFFDCylIndex */
            Dem_Misfire_SetObdFFDCylToTmp( EventStrgIndex, misfireObdFFDCylIndex, (Dem_MisfireCylinderType)DEM_MISFIRE_CYLINDER_NON );  /* [GUD]misfireObdFFDCylIndex */
        }
    }

    return;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */

/****************************************************************************/
/* Function Name | Dem_Misfire_ClearDataRelatedAllFFD                       */
/* Description   | Clear Data Related FFD                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStrgIndex                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_ClearDataRelatedAllFFD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfirePairEventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetMisfirePairEvent;
    VAR( Dem_u08_MisfireKindType, AUTOMATIC ) misfireType;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) misfirePairEventFFDCyl;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndexNum;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndex;

    misfireFFDCylIndexNum = Dem_MisfireFFDCylIndexNum;

    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );
    if( misfireEventKind == (boolean)TRUE )
    {
        misfirePairEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
        resultGetMisfirePairEvent = Dem_CfgInfoPm_GetMisfirePairEventStrgIndexByStrgIndex( EventStrgIndex, &misfirePairEventStrgIndex );

        for( misfireFFDCylIndex = (Dem_u08_MisfireFFDCylIndexType)0U; misfireFFDCylIndex < misfireFFDCylIndexNum; misfireFFDCylIndex++ )    /* [GUD:for]misfireFFDCylIndex */
        {
            misfireType = DEM_MISFIRE_KIND_INVALID;

            /*--------------------------------------*/
            /*  action to misfire pair event.       */
            if( resultGetMisfirePairEvent == DEM_IRT_OK )
            {
                Dem_Misfire_GetFFDCylToTmp( misfirePairEventStrgIndex, misfireFFDCylIndex, &misfirePairEventFFDCyl );                   /* [GUD]misfireFFDCylIndex */
                if( misfirePairEventFFDCyl != DEM_MISFIRE_CYLINDER_NON )
                {
                    misfireType =   Dem_CfgInfoPm_GetMisfireType_InEvtStrgGrp( misfirePairEventStrgIndex );
                }
            }
            /*--------------------------------------*/

            Dem_Misfire_SetMisfireKindOfFFDToTmp( misfireFFDCylIndex, misfireType );                                                    /* [GUD]misfireFFDCylIndex */
            Dem_Misfire_SetFFDCylToTmp( EventStrgIndex, misfireFFDCylIndex, (Dem_MisfireCylinderType)DEM_MISFIRE_CYLINDER_NON );        /* [GUD]misfireFFDCylIndex */
        }
    }

    return;
}

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Misfire_ClearDataRelatedObdFFD                       */
/* Description   | Clear Data Related FFD                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStrgIndex                                     */
/*               | [in] FreezeFrameRecordTrigger :                          */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_ClearDataRelatedObdFFD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger
)
{
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfirePairEventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) result;
    VAR( Dem_u08_MisfireKindType, AUTOMATIC ) misfireType;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) misfirePairEventFFDCyl;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndexNum;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndex;

    misfireObdFFDCylIndexNum = Dem_MisfireObdFFDCylIndexNum;

    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );
    if( misfireEventKind == (boolean)TRUE )
    {
        misfireObdFFDCylIndex = Dem_CfgInfoPm_GetObdFFDCylIndexOfMisfire( FreezeFrameRecordTrigger );
        if( misfireObdFFDCylIndex < misfireObdFFDCylIndexNum )                                          /* [GUD:if]misfireObdFFDCylIndex */
        {
            misfireType = DEM_MISFIRE_KIND_INVALID;

            /*--------------------------------------*/
            /*  action to misfire pair event.       */
            misfirePairEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
            result = Dem_CfgInfoPm_GetMisfirePairEventStrgIndexByStrgIndex( EventStrgIndex, &misfirePairEventStrgIndex );

            if( result == DEM_IRT_OK )
            {
                Dem_Misfire_GetObdFFDCylToTmp( misfirePairEventStrgIndex, misfireObdFFDCylIndex, &misfirePairEventFFDCyl );             /* [GUD]misfireObdFFDCylIndex */
                if( misfirePairEventFFDCyl != DEM_MISFIRE_CYLINDER_NON )
                {
                    misfireType =   Dem_CfgInfoPm_GetMisfireType_InEvtStrgGrp( misfirePairEventStrgIndex );
                }
            }
            /*--------------------------------------*/

            Dem_Misfire_SetMisfireKindOfObdFFDToTmp( misfireObdFFDCylIndex, misfireType );                                              /* [GUD]misfireObdFFDCylIndex */
            Dem_Misfire_SetObdFFDCylToTmp( EventStrgIndex, misfireObdFFDCylIndex, (Dem_MisfireCylinderType)DEM_MISFIRE_CYLINDER_NON );  /* [GUD]misfireObdFFDCylIndex */
        }
    }

    return;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */

/****************************************************************************/
/* Function Name | Dem_Misfire_ClearDataRelatedFFD                          */
/* Description   | Clear Data Related FFD                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStrgIndex                                     */
/*               | [in] FreezeFrameRecordTrigger :                          */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_ClearDataRelatedFFD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger
)
{
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfirePairEventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) result;
    VAR( Dem_u08_MisfireKindType, AUTOMATIC ) misfireType;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) misfirePairEventFFDCyl;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndexNum;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndex;

    misfireFFDCylIndexNum = Dem_MisfireFFDCylIndexNum;

    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );
    if( misfireEventKind == (boolean)TRUE )
    {
        misfireFFDCylIndex = Dem_CfgInfoPm_GetFFDCylIndexOfMisfire( FreezeFrameRecordTrigger );
        if( misfireFFDCylIndex < misfireFFDCylIndexNum )                                                                            /* [GUD:if]misfireFFDCylIndex */
        {
            misfireType = DEM_MISFIRE_KIND_INVALID;

            /*--------------------------------------*/
            /*  action to pair misfire event.       */
            misfirePairEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
            result = Dem_CfgInfoPm_GetMisfirePairEventStrgIndexByStrgIndex( EventStrgIndex, &misfirePairEventStrgIndex );

            if( result == DEM_IRT_OK )
            {
                Dem_Misfire_GetFFDCylToTmp( misfirePairEventStrgIndex, misfireFFDCylIndex, &misfirePairEventFFDCyl );               /* [GUD]misfireFFDCylIndex */
                if( misfirePairEventFFDCyl != DEM_MISFIRE_CYLINDER_NON )
                {
                    misfireType =   Dem_CfgInfoPm_GetMisfireType_InEvtStrgGrp( misfirePairEventStrgIndex );
                }
            }
            /*--------------------------------------*/

            Dem_Misfire_SetMisfireKindOfFFDToTmp( misfireFFDCylIndex, misfireType );                                                /* [GUD]misfireFFDCylIndex */
            Dem_Misfire_SetFFDCylToTmp( EventStrgIndex, misfireFFDCylIndex, (Dem_MisfireCylinderType)DEM_MISFIRE_CYLINDER_NON );    /* [GUD]misfireFFDCylIndex */
        }
    }

    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Dem_Misfire_GetMisfirePairEventStatus                    */
/* Description   | Get Misfire pair EventStatus                             */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStrgIndex : Event index                       */
/*               | [out] MisfirePairEventStatusPtr : Another event status   */
/*               |          if no misfire pair event, output 0U.            */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Misfire_GetMisfirePairEventStatus
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) MisfirePairEventStatusPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfirePairEventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) result;


    misfirePairEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
    result = Dem_CfgInfoPm_GetMisfirePairEventStrgIndexByStrgIndex( EventStrgIndex, &misfirePairEventStrgIndex );

    if( result == DEM_IRT_OK )
    {
        (void)Dem_Data_GetDTCStatus( misfirePairEventStrgIndex, MisfirePairEventStatusPtr );    /* no return check required */
    }
    else
    {
        /*  no misfire pair event.      */
        *MisfirePairEventStatusPtr  =   (Dem_UdsStatusByteType)0U;
    }

    return ;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
