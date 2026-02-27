/* Dem_DTC_PFC_OBD_c(v5-8-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DTC_PFC_OBD/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../../../../cfg/Dem_Cfg.h"
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../../inc/Dem_CmnLib_DataAvl.h"
#include "../../../../inc/Dem_Pm_DataAvl.h"
#include "../../../../inc/Dem_Pm_DataCtl.h"
#include "../../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "../../../../inc/Dem_Pm_DTC.h"
#include "../../../../inc/Dem_Pm_DTC_PFC.h"
#include "../../../../inc/Dem_Pm_Misfire.h"
#include "../../../../inc/Dem_Rc_PFCMng.h"
#include "../../../../inc/Dem_Rc_DataMng.h"
#include "../../../../inc/Dem_Rc_MisfireMng.h"
#include "../../../../inc/Dem_Rc_OpCycleMng.h"
#include "../../../../usr/Dem_PFC_Callout.h"
#include "../../../../usr/Dem_SavedZone_Callout.h"
#include "../Dem_DTC_PFC.h"
#include "Dem_DTC_PFC_local.h"

#if ( DEM_PFC_SUPPORT == STD_ON )

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    Dem_u16_EventStrgIndexType       EventStrgIndex;
    Dem_u08_PFCCycQuaInfoType    CycleQualifiedInfo;
} Dem_TmpPFCRecordType;

typedef struct {
    Dem_TmpPFCRecordType    PermanentFaultRecord;
    Dem_u08_PFCIndexType    PFCRecordIndex;
} Dem_TmpPermanentMemoryEntryType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( void, DEM_CODE ) Dem_DTC_StorePermanentFaultRecordFromTmp
( void );

static FUNC( void, DEM_CODE ) Dem_DTC_ClearTmpPFCClearCondition
( void );

static FUNC( void, DEM_CODE ) Dem_DTC_ClearTmpPermanentMemoryEntry
( void );

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_TmpPermanentMemoryEntryType, DEM_VAR_NO_INIT ) Dem_TmpPermanentMemoryEntry;

static VAR( Dem_u08_PFCRecordUpdateStatusType, DEM_VAR_NO_INIT ) Dem_PFCRecordUpdateStatus;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE_TRUST          /*  PreInit section                     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_DTC_PreInitPFCRecordStatus                           */
/* Description   | Init process of PFC.                                     */
/*               | Status variable initial setting for PFC memory suppressi */
/*               | on cancellation control.                                 */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE_TRUST ) Dem_DTC_PreInitPFCRecordStatus       /*  PreInit section     */
( void )
{
    Dem_PFCRecordUpdateStatus = DEM_PFC_RECORD_UPDATE_ENABLE;
    return;
}

#define DEM_STOP_SEC_CODE_TRUST       /*  PreInit section     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_DTC_InitForPFC                                       */
/* Description   | Initializes the value of PFC.                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_InitForPFC
( void )
{
    Dem_DTC_ClearTmpPermanentMemoryEntry();

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    Dem_Misfire_ClearTmpPermanentMemoryEntry();
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

    return;
}

/****************************************************************************/
/* Function Name | Dem_DTC_ClearTmpPermanentMemoryEntry                     */
/* Description   | Initializes permanent memory entry of temporary area.    */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DTC_ClearTmpPermanentMemoryEntry
( void )
{
    /* Initializes the temporary permanent memory. */
    Dem_TmpPermanentMemoryEntry.PermanentFaultRecord.EventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
    Dem_TmpPermanentMemoryEntry.PermanentFaultRecord.CycleQualifiedInfo = DEM_PFC_QUALIFIEDINFO_INITIAL;

    Dem_TmpPermanentMemoryEntry.PFCRecordIndex = DEM_PFC_RECORD_INDEX_INITIAL;

    return;
}

/****************************************************************************/
/* Function Name | Dem_DTC_SavePermanentMemoryEntryToTmp                    */
/* Description   | Save the Event Index to temporary area.                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Successful.                          */
/*               |        DEM_IRT_NG : Not a valid event id.                */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_SavePermanentMemoryEntryToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetPFCRecordIndex;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordIndex;
    VAR( Dem_u08_PFCCycQuaInfoType, AUTOMATIC ) tmpCycleQualifiedInfo;


    retVal = DEM_IRT_NG;
    pfcRecordIndex = DEM_PFC_RECORD_INDEX_INITIAL;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]EventStrgIndex */
    {
        retGetPFCRecordIndex = Dem_PFCMng_GetPFCRecordIndex( EventStrgIndex, &pfcRecordIndex );

        if( retGetPFCRecordIndex == DEM_IRT_OK )
        {
            /* Save the temoprary Permanent meomry */
            Dem_TmpPermanentMemoryEntry.PermanentFaultRecord.EventStrgIndex = EventStrgIndex;
            (void)Dem_PFCMng_GetCycleQualifiedInfo(pfcRecordIndex, &tmpCycleQualifiedInfo);   /* no return check required */
            Dem_TmpPermanentMemoryEntry.PermanentFaultRecord.CycleQualifiedInfo = tmpCycleQualifiedInfo;
            Dem_TmpPermanentMemoryEntry.PFCRecordIndex = pfcRecordIndex;
        }
        else
        {
            /* Initializes permanent memory entry of temporary area. */
            Dem_DTC_ClearTmpPermanentMemoryEntry();
        }
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        Dem_Misfire_SavePermanentMemoryEntryToTmp( EventStrgIndex );
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

        retVal = DEM_IRT_OK;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DTC_UpdatePermanentMemoryEntryToTmp                  */
/* Description   | Compares the Permanent memory record corresponding to    */
/*               | the temoprary Permanent meomry entry.                    */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]PFC  :   NotifySavedZone                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_UpdatePermanentMemoryEntryToTmp
( void )
{
    if( Dem_PFCRecordUpdateStatus != DEM_PFC_RECORD_UPDATE_DISABLE )
    {
        /*--------------------------------------------------*/
        /*  notify SAVED_ZONE_PERMANENT update - start.     */
        Dem_NotifySavedZonePermanentUpdate_Enter();         /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------------------*/

        Dem_DTC_StorePermanentFaultRecordFromTmp(); /*[UpdRec]PFC */

        /*--------------------------------------------------*/
        /*  notify SAVED_ZONE_PERMANENT update - end.       */
        Dem_NotifySavedZonePermanentUpdate_Exit();          /*  notify end :  savedzone area will be update.  */
        /*--------------------------------------------------*/

    }

    return;
}


#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_DTC_UpdateSpecificPermanentMemoryEntryToTmp          */
/* Description   | Compares the Permanent memory record corresponding to    */
/*               | the temoprary Permanent meomry entry.                    */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]PFC  :   NotifySavedZone                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_UpdateSpecificPermanentMemoryEntryToTmp
( void )
{
    if( Dem_PFCRecordUpdateStatus != DEM_PFC_RECORD_UPDATE_DISABLE )
    {
        /*--------------------------------------------------*/
        /*  notify SAVED_ZONE_PERMANENT update - start.     */
        Dem_NotifySavedZonePermanentUpdate_Enter();         /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------------------*/

        Dem_DTC_StorePermanentFaultRecordFromTmp(); /*[UpdRec]PFC */

        /*--------------------------------------------------*/
        /*  notify SAVED_ZONE_PERMANENT update - end.       */
        Dem_NotifySavedZonePermanentUpdate_Exit();          /*  notify end :  savedzone area will be update.  */
        /*--------------------------------------------------*/

    }

    return;
}
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_OFF )          */

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTC_UpdateSpecificPermanentMemoryEntryToTmp          */
/* Description   | Compares the Permanent memory record corresponding to    */
/*               | the temoprary Permanent meomry entry.                    */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]PFC          :   NotifySavedZone                 */
/* UpdateRecord  | [UpdRec]PFCMisfire   :   NotifySavedZone                 */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_UpdateSpecificPermanentMemoryEntryToTmp
( void )
{
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetPFCRecord;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) getEventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    if( Dem_PFCRecordUpdateStatus != DEM_PFC_RECORD_UPDATE_DISABLE )
    {
        eventStrgIndex = Dem_TmpPermanentMemoryEntry.PermanentFaultRecord.EventStrgIndex;
        if( eventStrgIndex == DEM_EVENTSTRGINDEX_INVALID )
        {
            /* if PFC is deleted or unregistered */
            pfcRecordIndex = Dem_TmpPermanentMemoryEntry.PFCRecordIndex;
            getEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
            retGetPFCRecord = Dem_PFCMng_GetPFCRecordData( pfcRecordIndex, &getEventStrgIndex );
            if( retGetPFCRecord == DEM_IRT_OK )
            {
                /* If PFC is deleted */
                eventStrgIndex = getEventStrgIndex;
            }
            /* If PFC is not registered, DEM_EVENTSTRGINDEX_INVALID is stored in eventStrgIndex. */
        }

        eventStorageNum = Dem_PrimaryMemEventStorageNum;

        /*--------------------------------------------------*/
        /*  notify SAVED_ZONE_PERMANENT update - start.     */
        Dem_NotifySavedZonePermanentUpdate_Enter();         /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------------------*/

        Dem_DTC_StorePermanentFaultRecordFromTmp(); /*[UpdRec]PFC */

        if( eventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]eventStrgIndex */
        {
            Dem_Misfire_UpdatePermanentMemoryEntryToTmp( eventStrgIndex );  /* [UpdRec]PFCMisfire */
        }

        /*--------------------------------------------------*/
        /*  notify SAVED_ZONE_PERMANENT update - end.       */
        Dem_NotifySavedZonePermanentUpdate_Exit();          /*  notify end :  savedzone area will be update.  */
        /*--------------------------------------------------*/

    }

    return;
}
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )           */
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )             */


/****************************************************************************/
/* Function Name | Dem_DTC_UpdatePFC                                        */
/* Description   | Set the Permanent memory entry to temporary area.        */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/*               | [in] OldDTCStatusStPtr :                                 */
/*               |        DTC status before the event reception.            */
/*               | [in] NewDTCStatusStPtr :                                 */
/*               |        DTC status after the event reception.             */
/*               | [in] MisfireCylinder :                                   */
/*               |        The misfire cylinder.                             */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_UpdatePFC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC) EventStrgIndex,
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) OldDTCStatusStPtr,
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder    /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetPFCRecordIndex;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetEventId;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) spacePFCRecordIndex;
    VAR( boolean, AUTOMATIC ) retGetPFCSuppression;
    VAR( boolean, AUTOMATIC ) pfcClearCycleQualified;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( boolean, AUTOMATIC ) isMILIndicator;

    eventId = ((Dem_EventIdType)0x0000U);
    pfcRecordIndex = DEM_PFC_RECORD_INDEX_INITIAL;
    pfcClearCycleQualified = Dem_PFCClearCycleQualified;

    if( Dem_PFCRecordUpdateStatus != DEM_PFC_RECORD_UPDATE_DISABLE )
    {
        /* Gets an event ID by event index. */
        retGetEventId = Dem_CfgInfoPm_CnvEventStrgIndexToEventId( EventStrgIndex, &eventId );   /* [GUD:RET:DEM_IRT_OK] EventStrgIndex */
        if( retGetEventId == DEM_IRT_OK )
        {
            /* This function is called from SetEventCommon */
            /* Only ClassA event, store PFC in this function (WWH-OBD) */
            isMILIndicator  =   Dem_CfgInfoPm_ChkDTCCls_MILONAtConfirmed( EventStrgIndex );     /* [GUD]EventStrgIndex */
            if( isMILIndicator == (boolean)TRUE )
            {
                if( ( ( OldDTCStatusStPtr->ExtendDTCStatus2 & DEM_DTCSTATUSEX2_STATUS_CONTINUOUS_MI_HISTORY ) != DEM_DTCSTATUSEX2_STATUS_CONTINUOUS_MI_HISTORY ) &&
                    ( ( NewDTCStatusStPtr->ExtendDTCStatus2 & DEM_DTCSTATUSEX2_STATUS_CONTINUOUS_MI_HISTORY ) == DEM_DTCSTATUSEX2_STATUS_CONTINUOUS_MI_HISTORY ) )
                {
                    if( Dem_TmpPermanentMemoryEntry.PermanentFaultRecord.EventStrgIndex == DEM_EVENTSTRGINDEX_INVALID )
                    {
                        /* Obtain PFCRecord Index of the Empty PFCRecord Index */
                        spacePFCRecordIndex = DEM_PFC_RECORD_INDEX_INITIAL;
                        retGetPFCRecordIndex = Dem_PFC_GetNextSpacePFCRecordIndex( EventStrgIndex, spacePFCRecordIndex, &pfcRecordIndex );  /* [GUD]EventStrgIndex */

                        if( retGetPFCRecordIndex == DEM_IRT_OK )
                        {
                            retGetPFCSuppression = Dem_PFC_GetPFCSuppression( eventId );
                            if( retGetPFCSuppression != (boolean)TRUE )
                            {
                                Dem_TmpPermanentMemoryEntry.PFCRecordIndex = pfcRecordIndex;
                                Dem_TmpPermanentMemoryEntry.PermanentFaultRecord.EventStrgIndex = EventStrgIndex;   /* [GUD]EventStrgIndex */
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                                Dem_Misfire_UpdatePermanentCylToTmp( EventStrgIndex, MisfireCylinder );             /* [GUD]EventStrgIndex */
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
                            }
                        }
                    }
                    /* Initialize Permanent memory clear condition value of temporary area. */
                    Dem_DTC_ClearTmpPFCClearCondition();
                }

                if( pfcClearCycleQualified == (boolean)TRUE )
                {
                    if( ( ( OldDTCStatusStPtr->ExtendDTCStatus & DEM_DTCSTATUSEX_STATUS_TFTOC_IN_HEALINGCYCLE ) == DEM_DTCSTATUSEX_BYTE_ALL_OFF ) &&       /*  old bit1 in HealingCycle : OFF */
                        ( ( NewDTCStatusStPtr->ExtendDTCStatus & DEM_DTCSTATUSEX_STATUS_TFTOC_IN_HEALINGCYCLE ) != DEM_DTCSTATUSEX_BYTE_ALL_OFF ) )        /*  new bit1 in HealingCycle : ON  */
                    {
                        Dem_TmpPermanentMemoryEntry.PermanentFaultRecord.CycleQualifiedInfo &= ~DEM_PFC_QUABIT_DRIVINGCONDITIONQUALIFIED;
                    }
                }
            }
        }
    }
    return;
}

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTC_UpdatePFCFromB1Counter                           */
/* Description   | Set the Permanent memory entry to temporary area.        */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_UpdatePFCFromB1Counter
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC) EventStrgIndex
)
{
   VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetPFCRecordIndex;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetEventId;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) spacePFCRecordIndex;
    VAR( boolean, AUTOMATIC ) retGetPFCSuppression;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( boolean, AUTOMATIC ) isMILIndicator;

    eventId = ((Dem_EventIdType)0x0000U);
    pfcRecordIndex = DEM_PFC_RECORD_INDEX_INITIAL;

    if( Dem_PFCRecordUpdateStatus != DEM_PFC_RECORD_UPDATE_DISABLE )
    {
        /* Gets an event ID by event index. */
        retGetEventId = Dem_CfgInfoPm_CnvEventStrgIndexToEventId( EventStrgIndex, &eventId );   /* [GUD:RET:DEM_IRT_OK] EventStrgIndex */
        if( retGetEventId == DEM_IRT_OK )
        {
            isMILIndicator  =   Dem_CfgInfoPm_ChkDTCCls_HasContinuousMI( EventStrgIndex );  /* [GUD]EventStrgIndex */
            if( isMILIndicator == (boolean)TRUE )
            {
                if( Dem_TmpPermanentMemoryEntry.PermanentFaultRecord.EventStrgIndex == DEM_EVENTSTRGINDEX_INVALID )
                {
                    /* Obtain PFCRecord Index of the Empty PFCRecord Index */
                    spacePFCRecordIndex = DEM_PFC_RECORD_INDEX_INITIAL;
                    retGetPFCRecordIndex = Dem_PFC_GetNextSpacePFCRecordIndex( EventStrgIndex, spacePFCRecordIndex, &pfcRecordIndex );  /* [GUD]EventStrgIndex */
                    if( retGetPFCRecordIndex == DEM_IRT_OK )
                    {
                        retGetPFCSuppression = Dem_PFC_GetPFCSuppression( eventId );
                        if( retGetPFCSuppression != (boolean)TRUE )
                        {
                            Dem_TmpPermanentMemoryEntry.PFCRecordIndex = pfcRecordIndex;
                            Dem_TmpPermanentMemoryEntry.PermanentFaultRecord.EventStrgIndex = EventStrgIndex;
                        }
                    }
                }

                /* Initialize Permanent memory clear condition value of temporary area. */
                Dem_DTC_ClearTmpPFCClearCondition();
            }
        }
    }
    return;
}
#endif  /*   ( DEM_WWH_OBD_SUPPORT == STD_ON )      */

/****************************************************************************/
/* Function Name | Dem_DTC_ClearPFC                                         */
/* Description   | Clear the Permanent memory.                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] OldDTCStatusStPtr :                                 */
/*               |        DTC status before the event reception.            */
/*               | [in] NewDTCStatusStPtr :                                 */
/*               |        DTC status after the event reception.             */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_ClearPFC
(
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) OldDTCStatusStPtr,
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr
)
{
    if( ( OldDTCStatusStPtr->ExtendDTCStatus2 & DEM_DTCSTATUSEX2_STATUS_CONTINUOUS_MI_HISTORY ) != DEM_DTCSTATUSEX2_BYTE_ALL_OFF )
    {
        if( ( NewDTCStatusStPtr->ExtendDTCStatus2 & DEM_DTCSTATUSEX2_STATUS_CONTINUOUS_MI_HISTORY ) == DEM_DTCSTATUSEX2_BYTE_ALL_OFF )
        {
            /* Initialize Permanent memory of temporary area. */
            Dem_TmpPermanentMemoryEntry.PermanentFaultRecord.EventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
            Dem_DTC_ClearTmpPFCClearCondition();
        }
        else
        {
            /* No Process */
        }
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_DTC_ClearPFCByCycleStart                             */
/* Description   | Clear the Permanent memory when operation cycle is       */
/*               | started.                                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] OldDTCStatusStPtr :                                 */
/*               |        DTC status before the event reception.            */
/*               | [in] NewDTCStatusStPtr :                                 */
/*               |        DTC status after the event reception.             */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_ClearPFCByCycleStart
(
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) OldDTCStatusStPtr,
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( boolean, AUTOMATIC ) pfcClearFlg;
    VAR( boolean, AUTOMATIC ) clearPatternMinimumRatio;

    pfcClearFlg = (boolean)FALSE;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;


    if( ( OldDTCStatusStPtr->ExtendDTCStatus2 & DEM_DTCSTATUSEX2_STATUS_CONTINUOUS_MI_HISTORY ) == DEM_DTCSTATUSEX2_STATUS_CONTINUOUS_MI_HISTORY )
    {
        if( ( NewDTCStatusStPtr->ExtendDTCStatus2 & DEM_DTCSTATUSEX2_STATUS_CONTINUOUS_MI_HISTORY ) != DEM_DTCSTATUSEX2_STATUS_CONTINUOUS_MI_HISTORY )
        {
            pfcClearFlg = (boolean)TRUE;
        }
        else
        {
            /* No Process */
        }
    }
    else
    {
        if( Dem_TmpPermanentMemoryEntry.PermanentFaultRecord.EventStrgIndex < eventStorageNum )
        {
            clearPatternMinimumRatio = Dem_CfgInfoPm_GetPFCClearPattern( Dem_TmpPermanentMemoryEntry.PermanentFaultRecord.EventStrgIndex );
            if( clearPatternMinimumRatio == (boolean)TRUE )
            {
                /*  minimum ratio.          */
                if( ( OldDTCStatusStPtr->ExtendDTCStatus & DEM_DTCSTATUSEX_STATUS_TFTOC_IN_HEALINGCYCLE  ) == DEM_DTCSTATUSEX_BYTE_ALL_OFF )       /*  bit1 in HealingCycle : OFF */
                {
                    if( ( OldDTCStatusStPtr->ExtendDTCStatus2 & DEM_DTCSTATUSEX2_STATUS_TNCTOC_IN_PFCCLEARCONDCYCLE ) == DEM_DTCSTATUSEX2_BYTE_ALL_OFF )  /*  bit6 in PFCClearConditionCheckCycle : OFF */
                    {
                        pfcClearFlg = (boolean)TRUE;
                    }
                }
            }
            else
            {
                /*  not minimum ratio.      */
                if( ( OldDTCStatusStPtr->ExtendDTCStatus & DEM_DTCSTATUSEX_STATUS_TFTOC_IN_HEALINGCYCLE ) == DEM_DTCSTATUSEX_BYTE_ALL_OFF )       /*  bit1 in HealingCycle : OFF */
                {
                    if( ( OldDTCStatusStPtr->ExtendDTCStatus2 & DEM_DTCSTATUSEX2_STATUS_TNCTOC_IN_PFCCLEARCONDCYCLE ) == DEM_DTCSTATUSEX2_BYTE_ALL_OFF )  /*  bit6 in PFCClearConditionCheckCycle : OFF */
                    {
                        Dem_TmpPermanentMemoryEntry.PermanentFaultRecord.CycleQualifiedInfo |= DEM_PFC_QUABIT_PASSEDCYCLEQUALIFIED;
                    }

                    if( ( Dem_TmpPermanentMemoryEntry.PermanentFaultRecord.CycleQualifiedInfo & DEM_PFC_QUABIT_PFCCYCLEQUALIFIED ) == DEM_PFC_QUABIT_PFCCYCLEQUALIFIED )

                    {
                        Dem_TmpPermanentMemoryEntry.PermanentFaultRecord.CycleQualifiedInfo |= DEM_PFC_QUABIT_DRIVINGCONDITIONQUALIFIED;
                    }

                    if( ( ( Dem_TmpPermanentMemoryEntry.PermanentFaultRecord.CycleQualifiedInfo & DEM_PFC_QUABIT_PASSEDCYCLEQUALIFIED ) == DEM_PFC_QUABIT_PASSEDCYCLEQUALIFIED ) &&
                        ( ( Dem_TmpPermanentMemoryEntry.PermanentFaultRecord.CycleQualifiedInfo & DEM_PFC_QUABIT_DRIVINGCONDITIONQUALIFIED ) == DEM_PFC_QUABIT_DRIVINGCONDITIONQUALIFIED ) )

                    {
                        pfcClearFlg = (boolean)TRUE;
                    }
                }
                else
                {
                    Dem_TmpPermanentMemoryEntry.PermanentFaultRecord.CycleQualifiedInfo &= ~DEM_PFC_QUABIT_PASSEDCYCLEQUALIFIED;
                }

                Dem_TmpPermanentMemoryEntry.PermanentFaultRecord.CycleQualifiedInfo &= ~DEM_PFC_QUABIT_PFCCYCLEQUALIFIED;
            }
        }
    }

    if( pfcClearFlg == (boolean)TRUE )
    {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        /* Initialize Permanent memory of temporary area. */
        Dem_Misfire_ClearPermanentCylToTmp( Dem_TmpPermanentMemoryEntry.PermanentFaultRecord.EventStrgIndex );
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
        Dem_TmpPermanentMemoryEntry.PermanentFaultRecord.EventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
        Dem_DTC_ClearTmpPFCClearCondition();
    }
    else
    {
        /* No Process */
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_DTC_UpdatePFCRecord                                  */
/* Description   | Update Permanent memory record process.                  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]PFC          :   NotifySavedZone                 */
/* UpdateRecord  | [UpdRec]PFCMisfire   :   NotifySavedZone                 */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_UpdatePFCRecord
( void )
{
    if ( Dem_PFCRecordUpdateStatus != DEM_PFC_RECORD_UPDATE_DISABLE )
    {
        /*--------------------------------------------------*/
        /*  notify SAVED_ZONE_PERMANENT update - start.     */
        Dem_NotifySavedZonePermanentUpdate_Enter();         /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------------------*/

        Dem_DTC_UpdatePFCRecordByOrder();   /*[UpdRec]PFC *//*[UpdRec]PFCMisfire */

        /*--------------------------------------------------*/
        /*  notify SAVED_ZONE_PERMANENT update - end.       */
        Dem_NotifySavedZonePermanentUpdate_Exit();          /*  notify end :  savedzone area will be update.  */
        /*--------------------------------------------------*/
    }
    else
    {
        /* No Process */
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_DTC_ClearPFCClearCondition                           */
/* Description   | Clear the Permanent memory clear condition corresponding */
/*               | to the event index.                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_ClearPFCClearCondition
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetPFCRecordIndex;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordIndex;
    VAR( Dem_u08_PFCCycQuaInfoType, AUTOMATIC ) cycleQualifiedInfo;

    pfcRecordIndex = DEM_PFC_RECORD_INDEX_INITIAL;
    cycleQualifiedInfo = DEM_PFC_QUALIFIEDINFO_INITIAL;

    retGetPFCRecordIndex = Dem_PFCMng_GetPFCRecordIndex( EventStrgIndex, &pfcRecordIndex );
    if( retGetPFCRecordIndex == DEM_IRT_OK )
    {
        Dem_PFCMng_SetCycleQualifiedInfo( pfcRecordIndex, cycleQualifiedInfo );
    }

    return ;
}

#if ( DEM_PFC_OUTPUT_DEMINTERNALPFC_TODCM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTC_GetFilteredPFC                                   */
/* Description   | Gets the next Permanent memory and its DTC status.       */
/* Preconditions | Dem_DTC_SetDTCFilter being executed.                     */
/* Parameters    | [in] DTCFormat :                                         */
/*               |        DTC Format                                        */
/*               | [in/out] FaultSearchIndexPtr :                           */
/*               |        Search Index                                      */
/*               | [out] FilterdEventStrgIndexPtr :                         */
/*               |        Filtered Event Index                              */
/*               | [out] DTCValuePtr :                                      */
/*               |        OBD DTC Value                                     */
/*               | [out] DTCStatusPtr :                                     */
/*               |        Status Of DTC                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Returned next filtered element       */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No further element  */
/*               |         (matching the filter criteria) found             */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetFilteredPFC
(
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    P2VAR( Dem_u08_PFCIndexType, AUTOMATIC, AUTOMATIC ) FaultSearchIndexPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) FilterdEventStrgIndexPtr,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) udsDTCValue;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetPFCRecord;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckResult;
    VAR( boolean, AUTOMATIC ) retValidateDTC;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordNum;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( boolean, AUTOMATIC ) isValidPFC;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) eventMisfireKind;
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
    VAR( boolean, AUTOMATIC ) retDTCClerTarget;

    retVal = DEM_IRT_NO_MATCHING_ELEMENT;
    eventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
    statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
    pfcRecordNum = Dem_PFCRecordNum;
    isValidPFC = (boolean)FALSE;

    SchM_Enter_Dem_PermanentMemory();   /* waits completion of updating Diag record data by Dem_MainFunction.      */
    SchM_Exit_Dem_PermanentMemory();

    while( *FaultSearchIndexPtr < pfcRecordNum )
    {
        retGetPFCRecord = Dem_PFCMng_GetPFCRecordData( ( *FaultSearchIndexPtr ), &eventStrgIndex );
        if( retGetPFCRecord == DEM_IRT_OK )
        {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
            eventMisfireKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( eventStrgIndex );
            if( eventMisfireKind == (boolean)FALSE )
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
            {
                /* Check event available status, MIL indicator and OBD. */
                retCheckResult = Dem_DTC_CheckAvailableAndMILStatusByEventStrgIndex( eventStrgIndex );      /* [GUD:RET:DEM_IRT_OK] eventStrgIndex */
                if( retCheckResult == DEM_IRT_OK )
                {
                    isValidPFC = (boolean)TRUE;
                }
            }
        }

        ( *FaultSearchIndexPtr )++;

        if( isValidPFC == (boolean)TRUE )
        {
            isValidPFC = (boolean)FALSE;

            /*  eventStrgIndex range check is in Dem_DataMngC_GetEventRecord function.  */
            if( DTCFormat == DEM_DTC_FORMAT_UDS )
            {
                /* set UDS DTC value for SID19-55 */
                udsDTCValue =  Dem_CfgInfoPm_GetUdsDTCValue( eventStrgIndex );          /* [GUD]eventStrgIndex */

                /* validate UDS DTC */
                retValidateDTC = Dem_DataAvl_ValidateDTC( udsDTCValue );
                if( retValidateDTC == (boolean)TRUE )
                {
                    *DTCValuePtr = udsDTCValue;

                    retDTCClerTarget = Dem_DTC_JudgeDTCClearTarget( eventStrgIndex );   /* [GUD]eventStrgIndex */
                    if( retDTCClerTarget == (boolean)FALSE )
                    {
                        (void)Dem_DTC_GetDTCStatusByDTC( eventStrgIndex, &statusOfDTC ); /* no return check required *//* [GUD]eventStrgIndex */

                        (void)Dem_DTC_TranslateDTCStatusForOutputByDTC( eventStrgIndex, &statusOfDTC ); /* no return check required *//* [GUD]eventStrgIndex */
                    }
                    else
                    {
                        statusOfDTC = DEM_DTCSTATUS_BYTE_DEFAULT;

                        Dem_DTC_TranslateDTCStatusForOutput_NoMergeWIRBit( eventStrgIndex, &statusOfDTC );          /* [GUD]eventStrgIndex */
                    }

                    retVal = DEM_IRT_OK;
                }
            }
#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )    /*  [FuncSw]    */
            else if ( DTCFormat == DEM_DTC_FORMAT_OBD )
            {
                /* set OBD DTC value for SID0A */
                /* if retCheckResult is DEM_IRT_OK, it's OBDDTC event.   */
                *DTCValuePtr = (Dem_u32_DTCValueType)Dem_CfgInfoPm_GetObdDTCValue( eventStrgIndex );    /* [GUD]eventStrgIndex */
                statusOfDTC = DEM_DTCSTATUS_BYTE_DEFAULT;
                retVal = DEM_IRT_OK;
            }
#endif  /* ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )             */
            else
            {
                /*  no match format.        */
            }

            if( retVal == DEM_IRT_OK )
            {
                *DTCStatusPtr = statusOfDTC;
                *FilterdEventStrgIndexPtr = eventStrgIndex;     /* [GUD]eventStrgIndex */
                break;
            }
        }
    }

    return retVal;
}
#endif /* ( DEM_PFC_OUTPUT_DEMINTERNALPFC_TODCM_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_DTC_SetPFCCycleQualified                             */
/* Description   | Set pfc cycle qualified.                                 */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_SetPFCCycleQualified
( void )
{
    /*  store data to PFCMng.               */
    Dem_PFCMng_SetAllPFCCycleQualified();

    return ;
}

/****************************************************************************/
/* Function Name | Dem_DTC_SetPFCClearDisable                               */
/* Description   | Set pfc clear disable.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] IsClearDisable :                                    */
/*               |        Set Value of pfc clear disable.                   */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_SetPFCClearDisable
(
    VAR( boolean, AUTOMATIC ) IsClearDisable
)
{
    VAR( Dem_u08_ClearPFCCycleType, AUTOMATIC ) obdClearPFCCycleStartCycle;
    VAR( Dem_u08_PFCClearCondCheckStatusType, AUTOMATIC ) pfcClearConditionCheckStatus;

    pfcClearConditionCheckStatus    = DEM_PFC_CLEARCONDCHKSTATUS_ENABLE;    /*  ThisCycle : always enable.      */
    obdClearPFCCycleStartCycle      = Dem_OBDClearPFCCycleStartCycle;

    if( obdClearPFCCycleStartCycle == DEM_CLEARPFCCYCLE_NEXTIGCYCLE )       /*  NextIGCycle : disable/enable.   */
    {
        if ( IsClearDisable == (boolean)TRUE )
        {
            pfcClearConditionCheckStatus   =   DEM_PFC_CLEARCONDCHKSTATUS_DISABLE;
        }
    }
    /*  store data to PFCMng.               */
    Dem_OpCycleMng_SetPFCCycleClearConditionCheckStatus( pfcClearConditionCheckStatus );

    return;
}

/****************************************************************************/
/* Function Name | Dem_DTC_GetPermanentDTC                                  */
/* Description   | Set pfc cycle qualified.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] PFCSearchIndex :                                    */
/*               |        Index Key                                         */
/*               | [in] DTCFormat :                                         */
/*               |        DTC Format                                        */
/*               | [out] PermanentDTCPtr :                                  */
/*               |        PemanetDTC                                        */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Returned next filtered element       */
/*               |        DEM_IRT_NG : No further element                   */
/*               |         (matching the filter criteria) found             */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetPermanentDTC
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCSearchIndex,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,                  /* MISRA DEVIATION */
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) PermanentDTCPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetPFCRecord;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckResult;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) eventMisfireKind;
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

    retVal = DEM_IRT_NG;
    eventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;

    retGetPFCRecord = Dem_PFCMng_GetPFCRecordData( PFCSearchIndex, &eventStrgIndex );
    if( retGetPFCRecord == DEM_IRT_OK )
    {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        /*  skip misfire events. because misfire events are checked in another function.    */
        eventMisfireKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( eventStrgIndex );
        if( eventMisfireKind == (boolean)FALSE )
#endif  /*  ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )          */
        {
            /* Check event available status, MIL indicator and OBD. */
            retCheckResult = Dem_DTC_CheckAvailableAndMILStatusByEventStrgIndex( eventStrgIndex );      /* [GUD:RET:DEM_IRT_OK] eventStrgIndex */
            if( retCheckResult == DEM_IRT_OK )
            {
#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON ) /*  [FuncSw]    */
                if ( DTCFormat == DEM_DTC_FORMAT_OBD )
                {
                    *PermanentDTCPtr = (Dem_u32_DTCValueType)Dem_CfgInfoPm_GetObdDTCValue( eventStrgIndex );    /* [GUD]eventStrgIndex */
                }
                else
#endif  /* ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )          */
                {
                    *PermanentDTCPtr = Dem_CfgInfoPm_GetUdsDTCValue( eventStrgIndex );      /* [GUD]eventStrgIndex */
                }
                retVal = DEM_IRT_OK;
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DTC_GetClearPFCCycleQualified                        */
/* Description   | Gets PFC cycle qualified.                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] PFCRecordIndex :                                    */
/*               | [out] PassedCycleQualifiedPtr :                          */
/*               | [out] DrivingConditionQualifiedPtr :                     */
/*               | [out] PFCCycleQualifiedPtr :                             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful             */
/*               |        DEM_IRT_NG : Operation failed                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetClearPFCCycleQualified
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) PassedCycleQualifiedPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) DrivingConditionQualifiedPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) PFCCycleQualifiedPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_PFCCycQuaInfoType, AUTOMATIC ) cycleQualifiedInfo;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC )     pfcRecordNum;
    VAR( boolean, AUTOMATIC ) passedCycleQualified;
    VAR( boolean, AUTOMATIC ) drivingConditionQualified;
    VAR( boolean, AUTOMATIC ) pfcCycleQualified;

    passedCycleQualified        = (boolean)FALSE;
    drivingConditionQualified   = (boolean)FALSE;
    pfcCycleQualified           = (boolean)FALSE;

    retVal = DEM_IRT_NG;
    pfcRecordNum = Dem_PFCRecordNum;

    if( PFCRecordIndex < pfcRecordNum ) /* [GUD:if]PFCRecordIndex */
    {
        /*  get qualified info.     */
        Dem_PFCMng_QuaInfo_GetCycleQualifiedInfo( PFCRecordIndex, &cycleQualifiedInfo );    /* [GUD]PFCRecordIndex */

        if(( cycleQualifiedInfo & DEM_PFC_QUABIT_PASSEDCYCLEQUALIFIED ) == DEM_PFC_QUABIT_PASSEDCYCLEQUALIFIED )
        {
            passedCycleQualified        = (boolean)TRUE;
        }
        if(( cycleQualifiedInfo & DEM_PFC_QUABIT_DRIVINGCONDITIONQUALIFIED ) == DEM_PFC_QUABIT_DRIVINGCONDITIONQUALIFIED )
        {
            drivingConditionQualified   = (boolean)TRUE;
        }
        if(( cycleQualifiedInfo & DEM_PFC_QUABIT_PFCCYCLEQUALIFIED ) == DEM_PFC_QUABIT_PFCCYCLEQUALIFIED )
        {
            pfcCycleQualified           = (boolean)TRUE;
        }
        *PassedCycleQualifiedPtr        =   passedCycleQualified;
        *DrivingConditionQualifiedPtr   =   drivingConditionQualified;
        *PFCCycleQualifiedPtr           =   pfcCycleQualified;

        retVal = DEM_IRT_OK;
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DTC_GetEventStrgIndexByPFCRecordIndex                */
/* Description   | get EventStrgIndex by PFCIndex.                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] PFCRecordIndex :                                    */
/*               | [out] EventStrgIndexPtr :                                */
/* Return Value  | boolean                                                  */
/*               |    TRUE  : PFC record has EventStrgIndex.                */
/*               |    FALSE : PFC record doesn't have EventStrgIndex.       */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:TRUE] EventStrgIndexPtr                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_DTC_GetPermanentDTC.           */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_DTC_GetEventStrgIndexInPFCRecord
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetPFCRecord;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckResult;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

    retVal = (boolean)FALSE;
    eventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;

    retGetPFCRecord = Dem_PFCMng_GetPFCRecordData( PFCRecordIndex, &eventStrgIndex );
    if( retGetPFCRecord == DEM_IRT_OK )
    {
        /* Check event available status, MIL indicator and OBD. */
        retCheckResult = Dem_DTC_CheckAvailableAndMILStatusByEventStrgIndex( eventStrgIndex );  /* [GUD:RET:DEM_IRT_OK] EventStrgIndex */
        if( retCheckResult == DEM_IRT_OK )
        {
            *EventStrgIndexPtr  =   eventStrgIndex;     /* [GUD]eventStrgIndex */
            retVal = (boolean)TRUE;
        }
    }

    return retVal;
}

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_PFC_GetNextSpacePFCRecordIndex                       */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PFC_GetNextSpacePFCRecordIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC) EventStrgIndex, /* MISRA DEVIATION */
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) BasePFCRecordIndex,
    P2VAR( Dem_u08_PFCIndexType, AUTOMATIC, AUTOMATIC ) PFCRecordIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetPFCRecordIndex;

    retVal = DEM_IRT_NO_MATCHING_ELEMENT;

    retGetPFCRecordIndex = Dem_PFCMng_GetNextSpacePFCRecordIndex( BasePFCRecordIndex, PFCRecordIndexPtr );

    if( retGetPFCRecordIndex == DEM_IRT_OK )
    {
        retVal = DEM_IRT_OK;
    }
    return retVal;
}
#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_OFF ) */

/****************************************************************************/
/* Function Name | Dem_DTC_StorePermanentFaultRecordFromTmp                 */
/* Description   | Store the Permanent memory entry from temporary area.    */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]PFC                                              */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DTC_StorePermanentFaultRecordFromTmp
( void )
{
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetPFCRecord;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) getEventStrgIndex;
    VAR( Dem_u08_PFCCycQuaInfoType, AUTOMATIC ) cycleQualifiedInfo;


    getEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
    pfcRecordIndex = Dem_TmpPermanentMemoryEntry.PFCRecordIndex;
    eventStrgIndex = Dem_TmpPermanentMemoryEntry.PermanentFaultRecord.EventStrgIndex;

    retGetPFCRecord = Dem_PFCMng_GetPFCRecordData( pfcRecordIndex, &getEventStrgIndex );
    if( retGetPFCRecord == DEM_IRT_OK )
    {
        if( eventStrgIndex != getEventStrgIndex )
        {
            cycleQualifiedInfo = Dem_TmpPermanentMemoryEntry.PermanentFaultRecord.CycleQualifiedInfo;

            /* In the pfc record, there was difference between RAM and temporary. */
            Dem_DTC_SetPFCRecordWithQualifiedInfo( pfcRecordIndex, eventStrgIndex, cycleQualifiedInfo );    /*[UpdRec]PFC */
        }
        else if( eventStrgIndex != DEM_EVENTSTRGINDEX_INVALID )
        {
            cycleQualifiedInfo = Dem_TmpPermanentMemoryEntry.PermanentFaultRecord.CycleQualifiedInfo;

            /* In the pfc record, there was difference between RAM and temporary. */
            Dem_PFCMng_SetCycleQualifiedInfo( pfcRecordIndex, cycleQualifiedInfo );

        }
        else
        {
            /* No Process */
        }
    }
    else
    {
        /* No Process */
    }
    return ;
}

/****************************************************************************/
/* Function Name | Dem_DTC_ClearTmpPFCClearCondition                        */
/* Description   | Initialize Permanent memory clear condition value        */
/*               | of temporary area.                                       */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DTC_ClearTmpPFCClearCondition
( void )
{
    Dem_TmpPermanentMemoryEntry.PermanentFaultRecord.CycleQualifiedInfo &= ~DEM_PFC_QUABIT_PASSEDCYCLEQUALIFIED;
    Dem_TmpPermanentMemoryEntry.PermanentFaultRecord.CycleQualifiedInfo &= ~DEM_PFC_QUABIT_DRIVINGCONDITIONQUALIFIED;

    return;
}


#if ( DEM_PFC_RECORD_SUPPRESSION_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTC_SetPFCUpdateDisable                              */
/* Description   | PFC record suppression cancellation request event proce- */
/*               | ssing.                                                   */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_SetPFCUpdateDisable
( void )
{
    Dem_PFCRecordUpdateStatus = DEM_PFC_RECORD_UPDATE_DISABLE;
    return;
}

/****************************************************************************/
/* Function Name | Dem_DTC_SetPFCUpdateEnable                               */
/* Description   | PFC record suppression cancellation request event proce- */
/*               | ssing.                                                   */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_SetPFCUpdateEnable
( void )
{
    Dem_PFCRecordUpdateStatus = DEM_PFC_RECORD_UPDATE_ENABLE;
    return;
}

/****************************************************************************/
/* Function Name | Dem_Data_RefreshRAM                                      */
/* Description   | Refresh RAM  - PFC                                       */
/* Preconditions | None                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | Called from Dem_MainFunction                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PFC_RefreshRAM
( void )
{
    VAR( volatile Dem_u08_PFCRecordUpdateStatusType, AUTOMATIC )                      u8_dummy;      /*  for store GlobalVariable data    */
    P2VAR( volatile Dem_u08_PFCRecordUpdateStatusType, AUTOMATIC, DEM_VAR_NO_INIT )   u8_dummyPtr;   /*  for GlobalVariable address       */

    /*  set GlobalVariable pointer  */
    u8_dummyPtr     = &Dem_PFCRecordUpdateStatus;

    /* Exclusion is not necessary   */
    u8_dummy        = *u8_dummyPtr; /*  read GlobalVariable data    */
    *u8_dummyPtr    = u8_dummy;     /*  rewrite GlobalVariable data */

    return ;
}

#endif  /* ( DEM_PFC_RECORD_SUPPRESSION_SUPPORT == STD_ON ) */

#if ( DEM_PFC_RECORD_SUPPRESSION_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_Data_RefreshRAM                                      */
/* Description   | Refresh RAM  - PFC                                       */
/* Preconditions | None                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | Called from Dem_MainFunction                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PFC_RefreshRAM
( void )
{
    Dem_PFCRecordUpdateStatus = DEM_PFC_RECORD_UPDATE_ENABLE;
    return ;
}
#endif  /* (DEM_PFC_RECORD_SUPPRESSION_SUPPORT == STD_OFF) */

/****************************************************************************/
/* Function Name | Dem_DTC_CheckAvailableAndMILStatusByEventStrgIndex       */
/* Description   | Check event available and MIL status.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |            EventStrgIndex                                */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Check result is OK.                  */
/*               |        DEM_IRT_NG : Check result is NG.                  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] EventStrgIndex                      */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_CheckAvailableAndMILStatusByEventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( boolean, AUTOMATIC ) availableStatus;
    VAR( boolean, AUTOMATIC ) isMILIndicator;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )  /* [GUD:if]EventStrgIndex */
    {
        availableStatus = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( EventStrgIndex ); /* [GUD]EventStrgIndex */
        if( availableStatus == (boolean)TRUE )
        {
            isMILIndicator = Dem_CfgInfoPm_ChkDTCCls_HasContinuousMI( EventStrgIndex ); /* [GUD]EventStrgIndex */
            if( isMILIndicator == (boolean)TRUE )
            {
                retVal = DEM_IRT_OK;
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DTC_ClearAllPFC                                      */
/* Description   | Clear all records related to PFC.                        */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]PFC          :   NotifySavedZone                 */
/* UpdateRecord  | [UpdRec]PFCMisfire   :   NotifySavedZone                 */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_ClearAllPFC
( void )
{
    /*--------------------------------------------------*/
    /*  notify SAVED_ZONE_PERMANENT update - start.     */
    Dem_NotifySavedZonePermanentUpdate_Enter();         /*  notify start :  savedzone area will be update.  */
    /*--------------------------------------------------*/

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
    Dem_MisfireMng_ClearPFCMisfireComRecord();      /*[UpdRec]PFCMisfire */
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )    */

    Dem_PFCMng_ClearAllPFCRecord();      /*[UpdRec]PFC */

    if ( Dem_PFCRecordUpdateStatus != DEM_PFC_RECORD_UPDATE_DISABLE )
    {
        Dem_DTC_UpdatePFCRecordByOrder();    /*[UpdRec]PFC *//*[UpdRec]PFCMisfire */
    }

    /*--------------------------------------------------*/
    /*  notify SAVED_ZONE_PERMANENT update - end.       */
    Dem_NotifySavedZonePermanentUpdate_Exit();          /*  notify end :  savedzone area will be update.  */
    /*--------------------------------------------------*/

    return;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_PFC_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v3-0-1         :2019-10-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
