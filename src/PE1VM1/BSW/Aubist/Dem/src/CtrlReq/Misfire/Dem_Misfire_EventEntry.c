/* Dem_MisfireEventEntry_c(v5-6-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Misfire_EventEntry/CODE                               */
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
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_Similar.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Rc_MisfireMng.h"
#include "Dem_Misfire_EventEntry_local.h"
#include "Dem_Misfire_local.h"


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
static FUNC( void, DEM_CODE ) Dem_Misfire_UpdateTargetEventMemoryEntryFromTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( boolean, AUTOMATIC ) ConsistencyIdUpdateFlg,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId,
    VAR( Dem_EventKindType, AUTOMATIC ) EventKind
);
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
static FUNC( void, DEM_CODE ) Dem_Misfire_UpdatePairEventMemoryEntryFromTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) targetEventStrgIndex,
    VAR( Dem_EventKindType, AUTOMATIC ) targetEventKind
);
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )           */
#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Saved temporary area of event memory entry                               */
/****************************************************************************/
VAR( Dem_TmpMisfireEventMemoryEntryType, DEM_VAR_NO_INIT ) Dem_TmpMisfireEventMemoryEntry;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Misfire_CheckSetEventCylinder                        */
/* Description   | Check if MisfireCylinder is available.                   */
/* Preconditions |                                                          */
/* Parameters    | [in] EventCtrlIndex :                                    */
/*               |        Identification of an event by assigned EventId.   */
/*               | [in] EventStatus : Monitor test result.                  */
/*               | [in] MisfireCylinder :                                   */
/*               |        Misfire cylinder.                                 */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : MisfireCylinder is available.        */
/*               |        DEM_IRT_NG : MisfireCylinder is not available.    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_CheckSetEventCylinder
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    CONST( Dem_MisfireCylinderType, DEM_APPL_DATA ) MisfireCylinder
)
{
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) checkCylinder;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

    retVal = DEM_IRT_OK;
    checkCylinder = Dem_MisfireAvailableCylinder;

    if(( EventStatus == DEM_EVENT_STATUS_FAILED ) || ( EventStatus == DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED ))
    {
        eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );                    /* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */
        misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( eventStrgIndex );
        if( misfireEventKind == (boolean)TRUE )
        {
            checkCylinder = MisfireCylinder & checkCylinder;
            if( checkCylinder == DEM_MISFIRE_CYLINDER_NON )
            {
                retVal = DEM_IRT_NG;
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_ExtractAvailableCylinder                     */
/* Description   | Extract available Cylinder                               */
/* Preconditions |                                                          */
/* Parameters    | [in/out] MisfireCylinderPtr :                            */
/*               |        Misfire cylinder.                                 */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_ExtractAvailableCylinder
(
    P2VAR( Dem_MisfireCylinderType, AUTOMATIC, AUTOMATIC ) MisfireCylinderPtr
)
{
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) availableCylinder;

    availableCylinder = Dem_MisfireAvailableCylinder;

    *MisfireCylinderPtr = *MisfireCylinderPtr & availableCylinder;

    return;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_SaveEventMemoryEntryToTmp                    */
/* Description   | Saves an event memory entry by event index to            */
/*               |  temporary area.                                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_SaveEventMemoryEntryToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;

    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );
    if( misfireEventKind == (boolean)TRUE )
    {
        Dem_MisfireMng_GetAllMisfireRecordList( &Dem_TmpMisfireEventMemoryEntry.MisfireRecord[0] );
        Dem_MisfireMng_GetMisfireComRecord( &Dem_TmpMisfireEventMemoryEntry.MisfireComRecord );

        /*  convert id.     */
        retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex ); /* [GUD:RET:DEM_IRT_OK] misfireIndex */

        if ( retCnvId == DEM_IRT_OK )
        {
            /*  latch orginal information.      */
            Dem_TmpMisfireEventMemoryEntry.MisfireRecordBeforeAccumPendingCyl           =   Dem_TmpMisfireEventMemoryEntry.MisfireComRecord.FirstPendingCyl;
            Dem_TmpMisfireEventMemoryEntry.MisfireComBeforeFirstPendingCyl              =   Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].AccumPendingCyl;           /* [GUD]misfireIndex */

            Dem_TmpMisfireEventMemoryEntry.MisfireComBeforeFirstConfirmedCyl            =   Dem_TmpMisfireEventMemoryEntry.MisfireComRecord.FirstConfirmedCyl;
            Dem_TmpMisfireEventMemoryEntry.MisfireComBeforeFirstAccumConfirmedCyl       =   Dem_TmpMisfireEventMemoryEntry.MisfireComRecord.FirstAccumConfirmedCyl;
            Dem_TmpMisfireEventMemoryEntry.MisfireRecordBeforeAccumConfirmedCyl         =   Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].AccumConfirmedCyl;         /* [GUD]misfireIndex */

            Dem_TmpMisfireEventMemoryEntry.MisfireRecordBeforeAccumFailedCylSinceClear  =   Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].AccumFailedCylSinceClear;  /* [GUD]misfireIndex */
        }
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_UpdateEventMemoryEntryFromTmp                */
/* Description   | Update an event memory entry to temporary area.          */
/* Preconditions | Dem_TmpMisfireEventMemoryEntry.ResultOfComparingMisfire- */
/*               | Records and ResultOfComparingPairMisfireRecords must be  */
/*               | set before the this function is called.                  */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] ConsistencyIdUpdateFlg  :                           */
/*               | [in] ConsistencyId  :                                    */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_UpdateEventMemoryEntryFromTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( boolean, AUTOMATIC ) ConsistencyIdUpdateFlg,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
)
{
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;

    eventKind = Dem_CfgInfoPm_GetEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );                 /* [GUD:RET:Not DEM_EVTKIND_TYPE_NON_OBD_EVENT] EventStrgIndex  */

    if( ( eventKind & DEM_EVTKIND_TYPE_MISFIRE_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_EVENT )
    {
        Dem_Misfire_UpdateTargetEventMemoryEntryFromTmp( EventStrgIndex, ConsistencyIdUpdateFlg, ConsistencyId, eventKind );
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        Dem_Misfire_UpdatePairEventMemoryEntryFromTmp( EventStrgIndex, eventKind );
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )           */
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_UpdateTargetEventMemoryEntryFromTmp          */
/* Description   | Update an target event from temporary area.              */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] ConsistencyIdUpdateFlg  :                           */
/*               | [in] ConsistencyId  :                                    */
/*               | [in] EventKind  :                                        */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Misfire_UpdateTargetEventMemoryEntryFromTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( boolean, AUTOMATIC ) ConsistencyIdUpdateFlg,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId,
    VAR( Dem_EventKindType, AUTOMATIC ) EventKind  /* MISRA DEVIATION */
)
{
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;

    retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex ); /* [GUD:RET:DEM_IRT_OK] misfireIndex */
    if ( retCnvId == DEM_IRT_OK )
    {
        if( ConsistencyIdUpdateFlg == (boolean)TRUE )
        {
            Dem_MisfireMng_SetConsistencyIdOfMisfireRecord( misfireIndex, ConsistencyId );

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
            if( ( EventKind & DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT )
            {
                Dem_MisfireMng_SetConsistencyIdOfMisfireComForCAT( ConsistencyId );
            }
            else
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )           */
            {
                Dem_MisfireMng_SetConsistencyIdOfMisfireComForEmission( ConsistencyId );
            }
        }

        if( Dem_TmpMisfireEventMemoryEntry.ResultOfComparingMisfireRecords == DEM_IRT_NG )
        {
            Dem_MisfireMng_SetMisfireRecordList( misfireIndex, &Dem_TmpMisfireEventMemoryEntry.MisfireRecord[misfireIndex] );                   /* [GUD]misfireIndex */
        }
        else
        {
            /* Exceedance counter is not included in the comparison(ResultOfComparingMisfireRecords), it also updates in the comparison NG */
            Dem_MisfireMng_SetExceedanceCounter( misfireIndex, Dem_TmpMisfireEventMemoryEntry.MisfireRecord[misfireIndex].ExceedanceCounter );  /* [GUD]misfireIndex */
        }

        if( Dem_TmpMisfireEventMemoryEntry.ResultOfComparingMisfireComRecords == DEM_IRT_NG )
        {
            Dem_MisfireMng_SetMisfireComRecord( &Dem_TmpMisfireEventMemoryEntry.MisfireComRecord );
        }
    }

    return;
}


#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
/****************************************************************************/
/* Function Name | Dem_Misfire_UpdatePairEventMemoryEntryFromTmp            */
/* Description   | Update an Pair misfire event from temporary area.        */
/* Preconditions | none                                                     */
/* Parameters    | [in] targetEventStrgIndex :                              */
/*               | [in] targetEventKind  :                                  */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Misfire_UpdatePairEventMemoryEntryFromTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) targetEventStrgIndex,
    VAR( Dem_EventKindType, AUTOMATIC ) targetEventKind
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetMisfirePairEvent;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfirePairEventStrgIndex;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) pairMisfireIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) pairFaltIndex;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) pairConsistencyId;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;

    if( Dem_TmpMisfireEventMemoryEntry.ResultOfComparingPairMisfireRecords == DEM_IRT_NG )
    {
        resultGetMisfirePairEvent= Dem_CfgInfoPm_GetMisfirePairEventStrgIndexByStrgIndex( targetEventStrgIndex, &misfirePairEventStrgIndex );
        if( resultGetMisfirePairEvent == DEM_IRT_OK )
        {
            retCnvId = Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( misfirePairEventStrgIndex, &pairMisfireIndex );   /* [GUD:RET:DEM_IRT_OK] pairMisfireIndex */
            if ( retCnvId == DEM_IRT_OK )
            {
                resultOfGetFaultIndex = Dem_DataMngC_GetER_FaultIndex( misfirePairEventStrgIndex, &pairFaltIndex );         /* [GUD:RET:DEM_IRT_OK] EventStrgIndex */
                if( resultOfGetFaultIndex == DEM_IRT_OK )
                {
                    if( pairFaltIndex != DEM_FAULTINDEX_INITIAL )
                    {
                        Dem_DataMng_UpdateFaultRecordConsistencyId_Misfire( pairFaltIndex, &pairConsistencyId );

                        /* update consistencyId of fault record */
                        Dem_DataMng_SetEventRecordConsistencyId( misfirePairEventStrgIndex, pairConsistencyId );
                    }
                    else
                    {
                        Dem_DataMng_UpdateEventRecordConsistencyId( misfirePairEventStrgIndex, &pairConsistencyId );
                    }

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                    /* update consistencyId of similar record */
                    Dem_Similar_SetConsistencyId( misfirePairEventStrgIndex, pairConsistencyId );
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )     */

                    /* update consistencyId of Misfire record */
                    Dem_MisfireMng_SetConsistencyIdOfMisfireRecord( pairMisfireIndex, pairConsistencyId );

                    /* update consistencyId of MisfireCom record */
                    if( ( targetEventKind & DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT )
                    {
                        /* pair misfire event is emission */
                        Dem_MisfireMng_SetConsistencyIdOfMisfireComForEmission( pairConsistencyId );
                    }
                    else
                    {
                        /* pair misfire event is CAT */
                        Dem_MisfireMng_SetConsistencyIdOfMisfireComForCAT( pairConsistencyId );
                    }
                }

                /* update misfire record from temporary area */
                Dem_MisfireMng_SetMisfireRecordList( pairMisfireIndex, &Dem_TmpMisfireEventMemoryEntry.MisfireRecord[pairMisfireIndex] );   /* [GUD]pairMisfireIndex */
            }
        }
    }

    return;
}
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )           */


/****************************************************************************/
/* Function Name | Dem_Misfire_ClearMisfireInfoOfEvent                      */
/* Description   | Clear the misfire infomation.                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_ClearMisfireInfoOfEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;

    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );
    if( misfireEventKind == (boolean)TRUE )
    {
        /*  convert id.     */
        retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex ); /* [GUD:RET:DEM_IRT_OK] misfireIndex */

        if ( retCnvId == DEM_IRT_OK )
        {
            /* Clear the MisfireComRecord. */
            Dem_MisfireMng_ClearMisfireComRecord();

            /* Clear the MisfireRecordList. */
            Dem_MisfireMng_ClearMisfireRecordList( misfireIndex );

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
            Dem_Misfire_SetPendingStoreOfEmission( (boolean)FALSE );
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   */
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_InitTmpEventMemoryEntry                      */
/* Description   | Initilalize an event memory entry to temporary area.     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-6-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_InitTmpEventMemoryEntry
( void )
{
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireEventNum;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndex;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndexNum;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndex;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndexNum;

    misfireEventNum = Dem_MisfireEventNum;

    /* Initializes the MisfireComRecord. */
    Dem_TmpMisfireEventMemoryEntry.MisfireComRecord.FirstPendingCyl        = DEM_MISFIRE_CYLINDER_NON;
    Dem_TmpMisfireEventMemoryEntry.MisfireComRecord.FirstConfirmedCyl      = DEM_MISFIRE_CYLINDER_NON;
    Dem_TmpMisfireEventMemoryEntry.MisfireComRecord.FirstAccumConfirmedCyl = DEM_MISFIRE_CYLINDER_NON;

#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    misfireObdFFDCylIndexNum = Dem_MisfireObdFFDCylIndexNum;
    for( misfireObdFFDCylIndex = (Dem_u08_MisfireObdFFDCylIndexType)0U; misfireObdFFDCylIndex < misfireObdFFDCylIndexNum; misfireObdFFDCylIndex++ ) /* [GUD:for]misfireObdFFDCylIndex */
    {
        Dem_TmpMisfireEventMemoryEntry.MisfireComRecord.MisfireKindOfOBDFFD[misfireObdFFDCylIndex] = DEM_MISFIRE_KIND_INVALID;                      /* [GUD]misfireObdFFDCylIndex */
    }
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */

    misfireFFDCylIndexNum = Dem_MisfireFFDCylIndexNum;
    for( misfireFFDCylIndex = (Dem_u08_MisfireFFDCylIndexType)0U; misfireFFDCylIndex < misfireFFDCylIndexNum; misfireFFDCylIndex++ )    /* [GUD:for]misfireFFDCylIndex */
    {
        Dem_TmpMisfireEventMemoryEntry.MisfireComRecord.MisfireKindOfFFD[misfireFFDCylIndex] = DEM_MISFIRE_KIND_INVALID;                /* [GUD]misfireFFDCylIndex */
    }

#if ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )     /*  [FuncSw]    */
    Dem_Misfire_ClearConfirmedOrderCylListToTmp();
#endif  /* ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )  */

    /* Initializes the MisfireRecord. */
    for( misfireIndex = (Dem_u16_MisfireStrgIndexType)0U; misfireIndex < misfireEventNum; misfireIndex++ )                          /* [GUD:for]misfireIndex */
    {
        Dem_TmpMisfireEventMemoryEntry.MisfireRecord[misfireIndex].FailedCyl                         = DEM_MISFIRE_CYLINDER_NON;    /* [GUD]misfireIndex */
        Dem_TmpMisfireEventMemoryEntry.MisfireRecord[misfireIndex].AccumCyl                          = DEM_MISFIRE_CYLINDER_NON;    /* [GUD]misfireIndex */
        Dem_TmpMisfireEventMemoryEntry.MisfireRecord[misfireIndex].AccumFailedCylThisOC              = DEM_MISFIRE_CYLINDER_NON;    /* [GUD]misfireIndex */
        Dem_TmpMisfireEventMemoryEntry.MisfireRecord[misfireIndex].AccumFailedCylSinceClear          = DEM_MISFIRE_CYLINDER_NON;    /* [GUD]misfireIndex */
        Dem_TmpMisfireEventMemoryEntry.MisfireRecord[misfireIndex].AccumTestNotCompleteCylSinceClear = DEM_MISFIRE_CYLINDER_NON;    /* [GUD]misfireIndex */
        Dem_TmpMisfireEventMemoryEntry.MisfireRecord[misfireIndex].AccumPendingCyl                   = DEM_MISFIRE_CYLINDER_NON;    /* [GUD]misfireIndex */
        Dem_TmpMisfireEventMemoryEntry.MisfireRecord[misfireIndex].AccumConfirmedCyl                 = DEM_MISFIRE_CYLINDER_NON;    /* [GUD]misfireIndex */
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
        for( misfireObdFFDCylIndex = (Dem_u08_MisfireObdFFDCylIndexType)0U; misfireObdFFDCylIndex < misfireObdFFDCylIndexNum; misfireObdFFDCylIndex++ ) /* [GUD:for]misfireObdFFDCylIndex */
        {
            Dem_TmpMisfireEventMemoryEntry.MisfireRecord[misfireIndex].OBDFFDCyl[misfireObdFFDCylIndex] = DEM_MISFIRE_CYLINDER_NON;         /* [GUD]misfireIndex *//* [GUD]misfireObdFFDCylIndex */
        }
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
        for( misfireFFDCylIndex = (Dem_u08_MisfireFFDCylIndexType)0U; misfireFFDCylIndex < misfireFFDCylIndexNum; misfireFFDCylIndex++ )    /* [GUD:for]misfireFFDCylIndex */
        {
            Dem_TmpMisfireEventMemoryEntry.MisfireRecord[misfireIndex].FFDCyl[misfireFFDCylIndex] = DEM_MISFIRE_CYLINDER_NON;               /* [GUD]misfireIndex *//* [GUD]misfireFFDCylIndex */
        }
        Dem_TmpMisfireEventMemoryEntry.MisfireRecord[misfireIndex].ExceedanceCounter        = DEM_MISFIRE_EXCEEDANCECOUNTER_INIT;           /* [GUD]misfireIndex */
    }

    Dem_TmpMisfireEventMemoryEntry.MisfireRecordBeforeAccumPendingCyl   = DEM_MISFIRE_CYLINDER_NON;
    Dem_TmpMisfireEventMemoryEntry.MisfireComBeforeFirstPendingCyl      = DEM_MISFIRE_CYLINDER_NON;

    Dem_TmpMisfireEventMemoryEntry.MisfireComBeforeFirstConfirmedCyl        =   DEM_MISFIRE_CYLINDER_NON;
    Dem_TmpMisfireEventMemoryEntry.MisfireComBeforeFirstAccumConfirmedCyl   =   DEM_MISFIRE_CYLINDER_NON;
    Dem_TmpMisfireEventMemoryEntry.MisfireRecordBeforeAccumConfirmedCyl     =   DEM_MISFIRE_CYLINDER_NON;

    Dem_TmpMisfireEventMemoryEntry.MisfireRecordBeforeAccumFailedCylSinceClear  =   DEM_MISFIRE_CYLINDER_NON;

    return ;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
