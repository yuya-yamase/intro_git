/* Dem_PFCMng_c(v5-10-0)                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/PFCMng/CODE                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_Data_Cfg.h"
#include "../../../cfg/Dem_NvM_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Rc_PFCMng.h"
#include "../../../inc/Dem_Rc_ClrInfoMng.h"
#include "../../../inc/Dem_Rc_OpCycleMng.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Pm_DTC_PFC.h"

#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "../../../usr/Dem_SavedZone_Callout.h"
#include "../../../usr/Dem_PFC_Callout.h"

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include "../../../inc/Dem_Rc_MisfireMng.h"
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

#if ( DEM_PFC_SUPPORT == STD_ON )

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_PFCMng_InitMirrorMemory
( void );
#endif  /*( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON ) */

static FUNC( void, DEM_CODE ) Dem_PFCMng_MatchEventStrgIndexAndDTC
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,
    P2VAR(  Dem_u16_EventStrgIndexType, AUTOMATIC , AUTOMATIC )  EventStrgIndexPtr
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PFCMng_MatchPFCAndPFCQualInfo
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex
);
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
static FUNC( void, DEM_CODE ) Dem_PFCMng_ClearPFCRecordOfMisfire
( void );
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
static FUNC( void, DEM_CODE ) Dem_PFCMng_ClearPFCRecordForVerify
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex
);
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_OFF )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PFCMng_CheckPFCRecord
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex
);
#endif  /*   ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_OFF )         */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/*  if DEM_NVM_SYNC_PROCESS_ENABLE is STD_OFF, these valiables are set but never used.  */
VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_PFCNvMStatus[DEM_PFC_RECORD_NUM];
VAR( Dem_PFCRecordType, DEM_VAR_NO_INIT ) Dem_TmpPFCMirror;
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_START_SEC_VAR_SAVED_ZONE_PERMANENT
#include <Dem_MemMap.h>

VAR( Dem_PFCRecordType, DEM_VAR_SAVED_ZONE_PERMANENT ) Dem_PFCRecord[DEM_PFC_RECORD_NUM];

#define DEM_STOP_SEC_VAR_SAVED_ZONE_PERMANENT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_PFCMng_Init                                          */
/* Description   | Init process of PFC.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PFCMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    /* [FuncSw] */
    Dem_PFCMng_InitMirrorMemory();
#endif  /*  ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )   */
    return;
}

/****************************************************************************/
/* Function Name | Dem_PFCMng_InitSavedZone                                 */
/* Description   | Initialize savedzone process of PFC.                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in] InitType :                                          */
/*               |          Initialize savedzone type                       */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]PFC  :   NotifySavedZone                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PFCMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
)
{
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcIndex;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPFC;

    if( InitType == DEM_SZINITTYPE_INITIALIZE_ALL )
    {
        recMngCmnKindPFC = Dem_RecMngCmnKindPFC;
        pfcRecordNum = Dem_PFCRecordNum;
        /*--------------------------------------------------*/
        /*  notify SAVED_ZONE_PERMANENT update - start.     */
        Dem_NotifySavedZonePermanentUpdate_Enter();         /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------------------*/
        for( pfcIndex = (Dem_u08_PFCIndexType)0U; pfcIndex < pfcRecordNum; pfcIndex++ )     /* [GUD:for]pfcIndex */
        {
            Dem_PFCRecord[pfcIndex].EventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;            /* [GUD]pfcIndex */ /*[UpdRec]PFC */
            Dem_PFCRecord[pfcIndex].DtcValue = DEM_PFC_DTCVALUE_INITIAL;                    /* [GUD]pfcIndex */ /*[UpdRec]PFC */
            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPFC, ( Dem_u16_RecordIndexType )pfcIndex );   /* [GUD]pfcIndex */
        }

        /*--------------------------------------------------*/
        /*  notify SAVED_ZONE_PERMANENT update - end.       */
        Dem_NotifySavedZonePermanentUpdate_Exit();          /*  notify end :  savedzone area will be update.  */
        /*--------------------------------------------------*/
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_PFCMng_DataVerify                                    */
/* Description   | Verifies PFC data.                                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : DataVerify completed.         */
/*               |          DEM_IRT_PENDING : Continue DataVerify.          */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]PFC  :   NotifySavedZone                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PFCMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcIndex;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( boolean, AUTOMATIC ) verifyNGFlag;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) clrInfoNvmReadResult;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) clrInfoRecValue;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) pfcQualInfoClearID;
    VAR( Dem_u08_PFCCycQuaInfoType, AUTOMATIC ) cycleQualifiedInfo;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) matchPFCResult;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPFCQuaInfo;
    VAR( boolean, AUTOMATIC ) isMILIndicator;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) existMisfireFlag;
    VAR( boolean, AUTOMATIC ) clearMisfirePFCRecordFlag;
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;

    existMisfireFlag = (boolean)FALSE;
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
    pfcRecordNum = Dem_PFCRecordNum;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;
    recMngCmnKindPFCQuaInfo = Dem_RecMngCmnKindPFCQuaInfo;

    /*--------------------------------------------------*/
    /*  notify SAVED_ZONE_PERMANENT update - start.     */
    Dem_NotifySavedZonePermanentUpdate_Enter();         /*  notify start :  savedzone area will be update.  */
    /*--------------------------------------------------*/

    clrInfoNvmReadResult = Dem_ClrInfoMng_GetNvmReadResult();
    clrInfoRecValue  = Dem_ClrInfoMng_GetObdClearID();

    for( pfcIndex = (Dem_u08_PFCIndexType)0U; pfcIndex < pfcRecordNum; pfcIndex++ )         /* [GUD:for]pfcIndex */
    {
        verifyNGFlag = (boolean)FALSE;
        eventStrgIndex   = Dem_PFCRecord[pfcIndex].EventStrgIndex;                          /* [GUD]pfcIndex */

        /* Check ClrInfo NvmReadResult */
        if( clrInfoNvmReadResult == DEM_IRT_OK )
        {
            Dem_PFCMng_QuaInfo_GetClearID( pfcIndex, &pfcQualInfoClearID );                 /* [GUD]pfcIndex */

            if( pfcQualInfoClearID != clrInfoRecValue )
            {
                /*  initialize PFC record.      */
                Dem_PFCMng_QuaInfo_SetCycleQualifiedInfo( pfcIndex, DEM_PFC_QUALIFIEDINFO_INITIAL );    /* [GUD]pfcIndex */
                Dem_PFCMng_QuaInfo_SetClearID( pfcIndex, clrInfoRecValue );                             /* [GUD]pfcIndex */
            }
        }
        else
        {
            /* PFC Reacord Clear Process */
            Dem_PFCMng_QuaInfo_SetCycleQualifiedInfo( pfcIndex, DEM_PFC_QUALIFIEDINFO_INITIAL );        /* [GUD]pfcIndex */
            Dem_PFCMng_QuaInfo_SetClearID( pfcIndex, clrInfoRecValue );                                 /* [GUD]pfcIndex */
            /* Change PFCNvMStatus */
            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPFCQuaInfo, ( Dem_u16_RecordIndexType )pfcIndex );    /* [GUD]pfcIndex */
        }

        Dem_PFCMng_MatchEventStrgIndexAndDTC( pfcIndex, &eventStrgIndex );                              /* [GUD]pfcIndex */ /*[UpdRec]PFC */

        if( eventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]eventStrgIndex */
        {
            /*  eventStrgIndex's value range is in event area.      */
            isMILIndicator  =   Dem_CfgInfoPm_ChkDTCCls_HasContinuousMI( eventStrgIndex );              /* [GUD]eventStrgIndex */
            if( isMILIndicator != (boolean)TRUE )
            {
                /*  illegal evenetindex.        */
                verifyNGFlag = (boolean)TRUE;
            }
        }
        else
        {
            /*  It's not event range */
            verifyNGFlag = (boolean)TRUE;
        }

        if( verifyNGFlag == (boolean)TRUE )
        {
            /*  invalid data.               */
            /*  initialize PFC record.      */
            if( Dem_PFCRecord[pfcIndex].EventStrgIndex != DEM_EVENTSTRGINDEX_INVALID )          /* [GUD]pfcIndex */
            {
                Dem_PFCMng_ClearPFCRecordForVerify( pfcIndex );                                 /* [GUD]pfcIndex */ /*[UpdRec]PFC */
            }
        }
        else
        {
            matchPFCResult = Dem_PFCMng_MatchPFCAndPFCQualInfo( pfcIndex );                     /* [GUD]pfcIndex */

            if( matchPFCResult == DEM_IRT_NG )
            {
                Dem_PFCMng_QuaInfo_SetDtcValue( pfcIndex, Dem_PFCRecord[pfcIndex].DtcValue );           /* [GUD]pfcIndex */
                Dem_PFCMng_QuaInfo_SetClearID( pfcIndex, clrInfoRecValue );                             /* [GUD]pfcIndex */
                Dem_PFCMng_QuaInfo_SetCycleQualifiedInfo( pfcIndex, DEM_PFC_QUALIFIEDINFO_INITIAL );    /* [GUD]pfcIndex */
                Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPFCQuaInfo, ( Dem_u16_RecordIndexType )pfcIndex );        /* [GUD]pfcIndex */
            }
        }

        Dem_PFCMng_QuaInfo_GetCycleQualifiedInfo( pfcIndex, &cycleQualifiedInfo );                      /* [GUD]pfcIndex */
        if( cycleQualifiedInfo == DEM_PFC_QUALIFIEDINFO_FACTORY_DEFAULT )
        {
            Dem_PFCMng_QuaInfo_SetClearID( pfcIndex, clrInfoRecValue );                                 /* [GUD]pfcIndex */
            Dem_PFCMng_QuaInfo_SetCycleQualifiedInfo( pfcIndex, DEM_PFC_QUALIFIEDINFO_INITIAL );        /* [GUD]pfcIndex */
            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPFCQuaInfo, ( Dem_u16_RecordIndexType )pfcIndex );    /* [GUD]pfcIndex */
        }
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */

        if( Dem_PFCRecord[pfcIndex].EventStrgIndex < eventStorageNum )                                  /* [GUD]pfcIndex */
        {
            eventKind = Dem_CfgInfoPm_GetEventKindOfMisfire_InEvtStrgGrp( Dem_PFCRecord[pfcIndex].EventStrgIndex ); /* [GUD]pfcIndex *//* [GUD:RET:Not DEM_EVTKIND_TYPE_NON_OBD_EVENT] EventStrgIndex  */

            /* check whether misifire data exisist in PFC records for verify of PFCMisfireCom record */
            if( ( eventKind & DEM_EVTKIND_TYPE_MISFIRE_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_EVENT )
            {
                existMisfireFlag = (boolean)TRUE;
            }
        }
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

    }

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    clearMisfirePFCRecordFlag = (boolean)FALSE;
    /* verify PFCMisfireCom record */
    Dem_MisfireMng_PFCMisfireComDataVerify( existMisfireFlag, &clearMisfirePFCRecordFlag ); /*[UpdRec]PFCMisfire */

    if( clearMisfirePFCRecordFlag == (boolean)TRUE )
    {
        Dem_PFCMng_ClearPFCRecordOfMisfire();   /*[UpdRec]PFC */
    }
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
    /*--------------------------------------------------*/
    /*  notify SAVED_ZONE_PERMANENT update - end.       */
    Dem_NotifySavedZonePermanentUpdate_Exit();          /*  notify end :  savedzone area will be update.  */
    /*--------------------------------------------------*/

    return DEM_IRT_OK;
}

/****************************************************************************/
/* Function Name | Dem_PFCMng_SetPFCRecordData                              */
/* Description   | Set Permanent memory record corresponding to index.      */
/* Preconditions | none                                                     */
/* Parameters    | [in] PFCRecordIndex :                                    */
/*               |        Permanent memory record index.                    */
/*               | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]PFC                                              */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PFCMng_SetPFCRecordData
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordNum;
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) dtcValue;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetDtc;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) tmpClearID;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPFC;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPFCQuaInfo;

    pfcRecordNum = Dem_PFCRecordNum;
    dtcValue = DEM_PFC_DTCVALUE_INITIAL;


    if( PFCRecordIndex < pfcRecordNum )                     /* [GUD:if]PFCRecordIndex */
    {
        /* Starts exclusion. */
        SchM_Enter_Dem_PermanentMemory();

        Dem_PFCRecord[PFCRecordIndex].EventStrgIndex = EventStrgIndex;          /* [GUD]PFCRecordIndex */   /*[UpdRec]PFC */

        resultGetDtc = Dem_DataAvl_GetUDSDTCByEventStrgIndex( EventStrgIndex, &dtcValue );  /* [GUD:RET:DEM_IRT_OK] EventStrgIndex */
        if( resultGetDtc != DEM_IRT_OK )
        {
            dtcValue = DEM_PFC_DTCVALUE_INITIAL;
        }
        Dem_PFCRecord[PFCRecordIndex].DtcValue = dtcValue;                      /* [GUD]PFCRecordIndex */   /*[UpdRec]PFC */

        Dem_PFCMng_QuaInfo_SetDtcValue( PFCRecordIndex, dtcValue );             /* [GUD]PFCRecordIndex */

        tmpClearID = Dem_ClrInfoMng_GetObdClearID();
        Dem_PFCMng_QuaInfo_SetClearID( PFCRecordIndex, tmpClearID );            /* [GUD]PFCRecordIndex */

        /* Change PFCNvMStatus */
        recMngCmnKindPFC = Dem_RecMngCmnKindPFC;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPFC, ( Dem_u16_RecordIndexType )PFCRecordIndex );         /* [GUD]PFCRecordIndex */
        recMngCmnKindPFCQuaInfo = Dem_RecMngCmnKindPFCQuaInfo;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPFCQuaInfo, ( Dem_u16_RecordIndexType )PFCRecordIndex );  /* [GUD]PFCRecordIndex */

        /* Finishes exclusion. */
        SchM_Exit_Dem_PermanentMemory();

    }
    else
    {
        /* No Process */
    }
    return ;
}

/****************************************************************************/
/* Function Name | Dem_PFCMng_GetPFCRecordData                              */
/* Description   | Get the value of Permanent Fault Memory                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] PFCRecordIndex :                                    */
/*               |        The event index corresponding to the Permanent    */
/*               |        memory record Index.                              */
/*               | [out] EventStrgIndexPtr :                                */
/*               |        The event index corresponding to the event ID.    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PFCMng_GetPFCRecordData
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordNum;

    retVal = DEM_IRT_NG;
    pfcRecordNum = Dem_PFCRecordNum;

    if( PFCRecordIndex < pfcRecordNum )     /* [GUD:if]PFCRecordIndex */
    {
        *EventStrgIndexPtr = Dem_PFCRecord[PFCRecordIndex].EventStrgIndex;  /* [GUD]PFCRecordIndex */
        retVal = DEM_IRT_OK;
    }
    else
    {
        /* No Process */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_PFCMng_GetPFCRecordIndex                             */
/* Description   | Get Permanent memory record index.                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the Permanent    */
/*               |        memory record.                                    */
/*               | [out] PFCRecordIndexPtr :                                */
/*               |        Get Permanent memory record index.                */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Getting Permanent memory record      */
/*               |        index was successful.                             */
/*               |        DEM_IRT_NG : Getting Permanent memory record      */
/*               |        index was failed.                                 */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PFCMng_GetPFCRecordIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u08_PFCIndexType, AUTOMATIC, AUTOMATIC ) PFCRecordIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordIndex;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordNum;

    retVal = DEM_IRT_NG;
    pfcRecordNum = Dem_PFCRecordNum;

    for( pfcRecordIndex = (Dem_u08_PFCIndexType)0U; pfcRecordIndex < pfcRecordNum; pfcRecordIndex++ )   /* [GUD:for]pfcRecordIndex */
    {
        if( Dem_PFCRecord[pfcRecordIndex].EventStrgIndex == EventStrgIndex )            /* [GUD]pfcRecordIndex */
        {
            *PFCRecordIndexPtr = pfcRecordIndex;
            retVal = DEM_IRT_OK;
            break;
        }
    }
    return retVal;
}


#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_PFCMng_GetNextSpacePFCRecordIndex                    */
/* Description   | Gets next Get Permanent memory record index.             */
/* Preconditions | none                                                     */
/* Parameters    | [in] BasePFCRecordIndex :                                */
/*               |        Base PFCRecord index for search next              */
/*               |        PFCRecord index.                                  */
/*               | [out] PFCRecordIndexPtr :                                */
/*               |        Pointer to data for set PFCRecord index           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Success.                             */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : PFCRecord index     */
/*               |        is not exists no more.                            */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PFCMng_GetNextSpacePFCRecordIndex
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) BasePFCRecordIndex,
    P2VAR( Dem_u08_PFCIndexType, AUTOMATIC, AUTOMATIC ) PFCRecordIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckResult;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) loopCnt;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) loopCntInitValue;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordNum;

    retVal = DEM_IRT_NO_MATCHING_ELEMENT;
    pfcRecordNum = Dem_PFCRecordNum;

    if( BasePFCRecordIndex == DEM_PFC_RECORD_INDEX_INITIAL )
    {
        loopCntInitValue = (Dem_u08_PFCIndexType)0U;
    }
    else
    {
        loopCntInitValue = BasePFCRecordIndex;
        loopCntInitValue = loopCntInitValue + (Dem_u08_PFCIndexType)1U;
    }

    /* Search of PFCRecord index */
    for( loopCnt = loopCntInitValue ; loopCnt < pfcRecordNum ; loopCnt++ )  /* [GUD:for]loopCnt */
    {
        /* Check event index in PFCRecord */
        retCheckResult = Dem_PFCMng_CheckPFCRecord( loopCnt );              /* [GUD]loopCnt */
        if( retCheckResult == DEM_IRT_NG )
        {
            *PFCRecordIndexPtr = loopCnt;
            retVal = DEM_IRT_OK;
            break;
        }
    }

    return retVal;
}
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_OFF ) */

/****************************************************************************/
/* Function Name | Dem_PFCMng_SetAllPFCCycleQualified                       */
/* Description   | Set all PFC Cycle Qualified data.                        */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PFCMng_SetAllPFCCycleQualified
( void )
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcIndex;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordNum;
    VAR( Dem_u08_PFCCycQuaInfoType, AUTOMATIC ) tmpCycleQualifiedInfo;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) tmpClearID;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPFCQuaInfo;
    VAR( Dem_u08_PFCClearCondCheckStatusType, AUTOMATIC ) pfcClearConditionCheckStatus;


    pfcRecordNum = Dem_PFCRecordNum;
    recMngCmnKindPFCQuaInfo = Dem_RecMngCmnKindPFCQuaInfo;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    for( pfcIndex = (Dem_u08_PFCIndexType)0U; pfcIndex < pfcRecordNum; pfcIndex++ ) /* [GUD:for]pfcIndex */
    {
        /*  enter [SchM_Enter_Dem_PermanentMemory] exclusive area.  */
        SchM_Enter_Dem_PermanentMemory();

        /* checks whether the EventStrgIndex is an effective value. */
        if( Dem_PFCRecord[pfcIndex].EventStrgIndex < eventStorageNum )                                  /* [GUD]pfcIndex */
        {
            Dem_PFCMng_QuaInfo_GetCycleQualifiedInfo( pfcIndex, &tmpCycleQualifiedInfo );               /* [GUD]pfcIndex */

            if( ( tmpCycleQualifiedInfo & DEM_PFC_QUABIT_PFCCYCLEQUALIFIED ) != DEM_PFC_QUABIT_PFCCYCLEQUALIFIED )
            {
                if( ( tmpCycleQualifiedInfo & DEM_PFC_QUABIT_DRIVINGCONDITIONQUALIFIED ) != DEM_PFC_QUABIT_DRIVINGCONDITIONQUALIFIED )
                {
                    /*  check conditioncheck status       */
                    pfcClearConditionCheckStatus   =   Dem_OpCycleMng_GetPFCCycleClearConditionCheckStatus();
                    if ( pfcClearConditionCheckStatus != DEM_PFC_CLEARCONDCHKSTATUS_DISABLE )
                    {
                        /*----------------------------------------------*/
                        /*  clear condition check status is enable.     */
                        /*----------------------------------------------*/
                        /*  set PFC Cycle Qualified data. */
                        tmpCycleQualifiedInfo |= DEM_PFC_QUABIT_PFCCYCLEQUALIFIED;
                        Dem_PFCMng_QuaInfo_SetCycleQualifiedInfo( pfcIndex, tmpCycleQualifiedInfo );    /* [GUD]pfcIndex */

                        /*  set clearID                   */
                        tmpClearID = Dem_ClrInfoMng_GetObdClearID();
                        Dem_PFCMng_QuaInfo_SetClearID( pfcIndex, tmpClearID );                          /* [GUD]pfcIndex */

                        /* Change PFCNvMStatus */
                        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPFCQuaInfo, ( Dem_u16_RecordIndexType )pfcIndex );    /* [GUD]pfcIndex */
                    }
                }
            }
        }

        /*  exit [SchM_Enter_Dem_PermanentMemory] exclusive area.   */
        SchM_Exit_Dem_PermanentMemory();
    }

    return;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_PFCMng_CopyToMirrorMemory                            */
/* Description   | Copy to the Mirror Memory.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in/out] BlockMirrorPtr :                                */
/*               |        Nonvolatile synchronous data information.         */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PFCMng_CopyToMirrorMemory
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordNum;

    pfcRecordNum = Dem_PFCRecordNum;

    if( BlockMirrorPtr->RecordIndex < pfcRecordNum )    /* [GUD:if]BlockMirrorPtr->RecordIndex */
    {
        /* Set Permanent Memory record */
        Dem_TmpPFCMirror.EventStrgIndex             = Dem_PFCRecord[BlockMirrorPtr->RecordIndex].EventStrgIndex;        /* [GUD]BlockMirrorPtr->RecordIndex */
        Dem_TmpPFCMirror.DtcValue                   = Dem_PFCRecord[BlockMirrorPtr->RecordIndex].DtcValue;              /* [GUD]BlockMirrorPtr->RecordIndex */
    }
    BlockMirrorPtr->MirrorPtr = &Dem_TmpPFCMirror;

    return;
}

#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

/****************************************************************************/
/* Function Name | Dem_PFCMng_GetCycleQualifiedInfo                         */
/* Description   | Get CycleQualifiedInfo to index.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] PFCRecordIndex :                                    */
/*               |        Permanent memory record index.                    */
/*               | [out] CycleQualifiedInfoPtr :                            */
/*               |        Cycle Qualified Info.                             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PFCMng_GetCycleQualifiedInfo
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,
    P2VAR( Dem_u08_PFCCycQuaInfoType, AUTOMATIC, AUTOMATIC ) CycleQualifiedInfoPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordNum;

    retVal = DEM_IRT_NG;
    pfcRecordNum = Dem_PFCRecordNum;

    if( PFCRecordIndex < pfcRecordNum )
    {
        Dem_PFCMng_QuaInfo_GetCycleQualifiedInfo( PFCRecordIndex, CycleQualifiedInfoPtr );
        retVal = DEM_IRT_OK;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_PFCMng_SetCycleQualifiedInfo                         */
/* Description   | Set CycleQualifiedInfo to index.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] PFCRecordIndex :                                    */
/*               |        Permanent memory record index.                    */
/*               | [in] CycleQualifiedInfoPtr :                             */
/*               |        Cycle Qualified Info.                             */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PFCMng_SetCycleQualifiedInfo
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,
    VAR( Dem_u08_PFCCycQuaInfoType, AUTOMATIC ) CycleQualifiedInfo
)
{
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordNum;
    VAR( Dem_u08_PFCCycQuaInfoType, AUTOMATIC ) tmpCycleQualifiedInfo;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) tmpClearID;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPFCQuaInfo;

    pfcRecordNum = Dem_PFCRecordNum;
    recMngCmnKindPFCQuaInfo = Dem_RecMngCmnKindPFCQuaInfo;

    if( PFCRecordIndex < pfcRecordNum )
    {
        /*  enter [SchM_Enter_Dem_PermanentMemory] exclusive area.  */
        SchM_Enter_Dem_PermanentMemory();

        Dem_PFCMng_QuaInfo_GetCycleQualifiedInfo( PFCRecordIndex, &tmpCycleQualifiedInfo );

        if( tmpCycleQualifiedInfo != CycleQualifiedInfo )
        {
            Dem_PFCMng_QuaInfo_SetCycleQualifiedInfo( PFCRecordIndex, CycleQualifiedInfo );

            tmpClearID = Dem_ClrInfoMng_GetObdClearID();
            Dem_PFCMng_QuaInfo_SetClearID( PFCRecordIndex, tmpClearID );

            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPFCQuaInfo, ( Dem_u16_RecordIndexType )PFCRecordIndex );
        }

        /*  exit [SchM_Enter_Dem_PermanentMemory] exclusive area.   */
        SchM_Exit_Dem_PermanentMemory();
    }

    return ;
}





#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_PFCMng_InitMirrorMemory                              */
/* Description   | Initialize the Mirror Memory.                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PFCMng_InitMirrorMemory
( void )
{
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) pfcRecordBlockPaddingSize;
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) paddingIndex;

    /* Initializes the temporary permanent memory. */
    Dem_TmpPFCMirror.EventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
    Dem_TmpPFCMirror.DtcValue  = DEM_PFC_DTCVALUE_INITIAL;

    pfcRecordBlockPaddingSize    = Dem_PFCRecordBlockPaddingSize;

    for( paddingIndex = (Dem_u16_PaddingIndexType)0U; paddingIndex < pfcRecordBlockPaddingSize; paddingIndex++ )    /* [GUD:for]paddingIndex */
    {
        Dem_TmpPFCMirror.Reserve[paddingIndex] = DEM_DTC_PFC_RESERVE_INITIAL_VALUE;         /* [GUD]paddingIndex */
    }

    return ;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
/****************************************************************************/
/* Function Name | Dem_PFCMng_ClearPFCRecordOfMisfire                       */
/* Description   | Clear PFC record of Misfire.                             */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]PFC                                              */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PFCMng_ClearPFCRecordOfMisfire
(void)
{
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcIndex;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordNum;
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    pfcRecordNum = Dem_PFCRecordNum;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    for( pfcIndex = (Dem_u08_PFCIndexType)0U; pfcIndex < pfcRecordNum; pfcIndex++ )     /* [GUD:for]pfcIndex */
    {
        if( Dem_PFCRecord[pfcIndex].EventStrgIndex < eventStorageNum )                                                  /* [GUD]pfcIndex */
        {
            eventKind = Dem_CfgInfoPm_GetEventKindOfMisfire_InEvtStrgGrp( Dem_PFCRecord[pfcIndex].EventStrgIndex );     /* [GUD]pfcIndex *//* [GUD:RET:Not DEM_EVTKIND_TYPE_NON_OBD_EVENT] EventStrgIndex  */

            if( ( eventKind & DEM_EVTKIND_TYPE_MISFIRE_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_EVENT )
            {
                Dem_PFCMng_ClearPFCRecordForVerify( pfcIndex );                         /* [GUD]pfcIndex */ /*[UpdRec]PFC */
            }
        }
    }

    return;
}
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

/****************************************************************************/
/* Function Name | Dem_PFCMng_ClearPFCRecordForVerify                       */
/* Description   | clear PFC record and PFCQuaInfo record                 . */
/* Preconditions | none                                                     */
/* Parameters    | [in]PFCRecordIndex :                                     */
/*               |        Permanent memory record index.                    */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]PFC                                              */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | rename from Dem_PFCMng_ClearPFCRecord(v5-5-0).           */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PFCMng_ClearPFCRecordForVerify
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex               /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPFC;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPFCQuaInfo;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) clearId;

    clearId  = Dem_ClrInfoMng_GetObdClearID();

    recMngCmnKindPFC = Dem_RecMngCmnKindPFC;
    recMngCmnKindPFCQuaInfo = Dem_RecMngCmnKindPFCQuaInfo;

    Dem_PFCRecord[PFCRecordIndex].EventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;                          /* [GUDCHK:CALLER]PFCRecordIndex */ /*[UpdRec]PFC */
    Dem_PFCRecord[PFCRecordIndex].DtcValue = DEM_PFC_DTCVALUE_INITIAL;                                  /* [GUDCHK:CALLER]PFCRecordIndex */ /*[UpdRec]PFC */
    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPFC, ( Dem_u16_RecordIndexType )PFCRecordIndex );     /* [GUDCHK:CALLER]PFCRecordIndex */

    Dem_PFCMng_QuaInfo_SetClearID( PFCRecordIndex, clearId );                                           /* [GUDCHK:CALLER]PFCRecordIndex */
    Dem_PFCMng_QuaInfo_SetDtcValue( PFCRecordIndex, DEM_PFC_DTCVALUE_INITIAL );                         /* [GUDCHK:CALLER]PFCRecordIndex */
    Dem_PFCMng_QuaInfo_SetCycleQualifiedInfo( PFCRecordIndex, DEM_PFC_QUALIFIEDINFO_INITIAL );          /* [GUDCHK:CALLER]PFCRecordIndex */
    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPFCQuaInfo, ( Dem_u16_RecordIndexType )PFCRecordIndex );  /* [GUDCHK:CALLER]PFCRecordIndex */

    return;
}


/****************************************************************************/
/* Function Name | Dem_PFCMng_MatchEventStrgIndexAndDTC                     */
/* Description   | Confirmation of matching between EventStrgIndex and DTC. */
/* Preconditions | none                                                     */
/* Parameters    | [in]PFCRecordIndex :                                     */
/*               |        Permanent memory record index.                    */
/*               | [in/out]EventStrgIndexPtr :                              */
/*               |        The event index corresponding to the event ID.    */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]PFC                                              */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/*   v5-10-0     | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PFCMng_MatchEventStrgIndexAndDTC
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,              /* [PRMCHK:CALLER] */
    P2VAR(  Dem_u16_EventStrgIndexType, AUTOMATIC , AUTOMATIC )  EventStrgIndexPtr
)
{

    VAR( boolean, AUTOMATIC ) chgEventIndexFlag;
    VAR( boolean, AUTOMATIC ) availableStatus;
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) dtcValue;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetDtc;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetEventIndex;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPFC;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinder;

    chgEventIndexFlag = (boolean)FALSE;
    dtcValue          = DEM_PFC_DTCVALUE_INITIAL;

    if ( *EventStrgIndexPtr < DEM_EVENTSTRGINDEX_INVALID )
    {
        resultGetDtc = Dem_DataAvl_GetUDSDTCByEventStrgIndex( *EventStrgIndexPtr, &dtcValue );  /* [GUD:RET:DEM_IRT_OK] *EventStrgIndexPtr */
        if( resultGetDtc == DEM_IRT_OK )
        {
            if( Dem_PFCRecord[PFCRecordIndex].DtcValue != dtcValue )                /* [GUDCHK:CALLER]PFCRecordIndex */
            {
                chgEventIndexFlag = (boolean)TRUE;
            }
            else
            {
                availableStatus = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( *EventStrgIndexPtr );
                if( availableStatus != (boolean)TRUE )
                {
                    *EventStrgIndexPtr = DEM_EVENTSTRGINDEX_INVALID;
                }
            }
        }
        else
        {
            chgEventIndexFlag = (boolean)TRUE;
        }

        if( chgEventIndexFlag == (boolean)TRUE )
        {
            resultGetEventIndex = Dem_DataAvl_GetEventStrgIndexByDTC( Dem_PFCRecord[PFCRecordIndex].DtcValue, EventStrgIndexPtr, &misfireCylinder );    /* [GUD:RET:DEM_IRT_OK] EventStrgIndexPtr */    /* [GUDCHK:CALLER]PFCRecordIndex */
            if( resultGetEventIndex == DEM_IRT_OK )
            {
                recMngCmnKindPFC = Dem_RecMngCmnKindPFC;
                Dem_PFCRecord[PFCRecordIndex].EventStrgIndex = *EventStrgIndexPtr;                              /* [GUDCHK:CALLER]PFCRecordIndex */ /*[UpdRec]PFC */
                Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPFC, ( Dem_u16_RecordIndexType )PFCRecordIndex ); /* [GUDCHK:CALLER]PFCRecordIndex */
            }
            else
            {
                *EventStrgIndexPtr = DEM_EVENTSTRGINDEX_INVALID;
            }
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_PFCMng_MatchPFCAndPFCQualInfo                        */
/* Description   | Confirmation of matching between PFC and PFCQualinfo.    */
/* Preconditions | none                                                     */
/* Parameters    | [in]PFCRecordIndex :                                     */
/*               |        Permanent memory record index.                    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Target matched.                      */
/*               |        DEM_IRT_NG : Target did not match.                */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PFCMng_MatchPFCAndPFCQualInfo
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex           /* [PRMCHK:CALLER] */
)
{

    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) tmpDtcValue;


    retVal      = DEM_IRT_NG;
    tmpDtcValue = DEM_PFC_DTCVALUE_INITIAL;

    Dem_PFCMng_QuaInfo_GetDtcValue( PFCRecordIndex, &tmpDtcValue );     /* [GUDCHK:CALLER]PFCRecordIndex */

    if( Dem_PFCRecord[PFCRecordIndex].DtcValue == tmpDtcValue )         /* [GUDCHK:CALLER]PFCRecordIndex */
    {
        retVal = DEM_IRT_OK;
    }
    else
    {
        /* No Process */
    }

    return retVal;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_PFCMng_GetEventIdFromRecordData                      */
/* Description   | get event id from record data                            */
/* Preconditions | none                                                     */
/* Parameters    | [in]  RecordFieldIndex :                                 */
/*               | [in]  RecordIndex :                                      */
/*               | [out] EventIdPtr  :                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PFCMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,      /* MISRA DEVIATION */
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr   /* MISRA DEVIATION */
)
{
    /*  this record has no event id.        */
    return DEM_IRT_NG;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_Misfire_CheckPFCRecord                               */
/* Description   | Check event available and MIL status in PFCRecord.       */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Check result is OK.                  */
/*               |        DEM_IRT_NG : Check result is NG.                  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PFCMng_CheckPFCRecord
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex               /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

    eventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;

    /* Get event index in PFCRecord */
    (void)Dem_PFCMng_GetPFCRecordData( PFCRecordIndex, &eventStrgIndex );    /* no return check required */ /* [GUDCHK:CALLER]PFCRecordIndex */

    /* Check event available status, MIL indicator and OBD. */
    retVal = Dem_DTC_CheckAvailableAndMILStatusByEventStrgIndex( eventStrgIndex );

    return retVal;
}
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_OFF )    */

/****************************************************************************/
/* Function Name | Dem_PFCMng_ClearAllPFCRecord                             */
/* Description   | Clear all Permanent memory record                        */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]PFC                                              */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PFCMng_ClearAllPFCRecord
( void )
{
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcIndex;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordNum;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) tmpClearID;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPFC;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPFCQuaInfo;

    pfcRecordNum = Dem_PFCRecordNum;

    tmpClearID = Dem_ClrInfoMng_GetObdClearID();

    for( pfcIndex = (Dem_u08_PFCIndexType)0U; pfcIndex < pfcRecordNum; pfcIndex++ )         /* [GUD:for]pfcIndex */
    {
        /* Starts exclusion. */
        SchM_Enter_Dem_PermanentMemory();

        Dem_PFCRecord[pfcIndex].EventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;                    /* [GUD]pfcIndex */ /*[UpdRec]PFC */
        Dem_PFCRecord[pfcIndex].DtcValue       = DEM_PFC_DTCVALUE_INITIAL;                      /* [GUD]pfcIndex */ /*[UpdRec]PFC */

        Dem_PFCMng_QuaInfo_SetDtcValue( pfcIndex, DEM_PFC_DTCVALUE_INITIAL );                   /* [GUD]pfcIndex */
        Dem_PFCMng_QuaInfo_SetCycleQualifiedInfo( pfcIndex, DEM_PFC_QUALIFIEDINFO_INITIAL );    /* [GUD]pfcIndex */
        Dem_PFCMng_QuaInfo_SetClearID( pfcIndex, tmpClearID );                                  /* [GUD]pfcIndex */

        /* Finishes exclusion. */
        SchM_Exit_Dem_PermanentMemory();

        /* Change PFCNvMStatus */
        recMngCmnKindPFC = Dem_RecMngCmnKindPFC;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPFC, ( Dem_u16_RecordIndexType )pfcIndex );         /* [GUD]pfcIndex */
        recMngCmnKindPFCQuaInfo = Dem_RecMngCmnKindPFCQuaInfo;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPFCQuaInfo, ( Dem_u16_RecordIndexType )pfcIndex );  /* [GUD]pfcIndex */
    }

    return ;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_PFC_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
