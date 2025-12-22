/* Dem_DataMngVld_c(v5-9-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataMngVld/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Rc_ClrInfoMng.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "MisfireMng/Dem_MisfireMng_local.h"
#include "SimilarMng/Dem_SimilarMng_local.h"
#include "Dem_DataMng_local.h"


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

static FUNC( void, DEM_CODE ) Dem_DataMng_VerifyEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) ClrInfoNvmReadResult,
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) ClearIdValue
);
static FUNC( void, DEM_CODE ) Dem_DataMng_VerifiedDiagData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
static FUNC( boolean, DEM_CODE ) Dem_DataMng_FactoryCheckEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
static FUNC( boolean, DEM_CODE ) Dem_DataMng_ClearIdCheckEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) ClearID
);
static FUNC( boolean, DEM_CODE ) Dem_DataMng_ConsistencyCheckEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
);
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
static FUNC( boolean, DEM_CODE ) Dem_DataMng_ConsistencyCheckWithoutFault
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_ClearAllNotVerifiedRecord
( void );


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_u16_EventStrgIndexType, DEM_VAR_NO_INIT ) Dem_DataMng_EventStrgIndexForVerify;

static VAR( Dem_u16_RecordKindIndexType, DEM_VAR_NO_INIT ) Dem_DataMng_ClearRecordKind;
static VAR( Dem_u16_RecordIndexType, DEM_VAR_NO_INIT ) Dem_DataMng_ClearRecordIndex;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>
/****************************************************************************/
/* Function Name | Dem_DataMng_Init                                         */
/* Description   | initialize function.                                     */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMng_Init
( void )
{
    Dem_DataMng_EventStrgIndexForVerify = (Dem_u16_EventStrgIndexType)0U;
    Dem_DataMng_ClearRecordKind = (Dem_u16_RecordKindIndexType)0U;
    Dem_DataMng_ClearRecordIndex = (Dem_u16_RecordIndexType)0U;

    return;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_DataVerify                                   */
/* Description   | Verifies Diag data.                                      */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : DataVerify completed.         */
/*               |          DEM_IRT_PENDING : Continue DataVerify.          */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_DataVerify
( void )
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) clrInfoRecValue;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) clearId;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) obdClearId;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) clrInfoNvmReadResult;
    VAR( boolean, AUTOMATIC ) eventOBDKind;
    VAR( Dem_u16_EventStrgIndexType,AUTOMATIC ) verifyLoopNumByCycle;
    VAR( Dem_u16_EventStrgIndexType,AUTOMATIC ) processCount;
    VAR( Dem_u08_InternalReturnType,AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType,AUTOMATIC ) retClrRecord;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_EventKindType, AUTOMATIC ) eventMisfireKind;
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
    eventStorageNum = Dem_PrimaryMemEventStorageNum;
    verifyLoopNumByCycle = Dem_EventNumForVerifyByCycle;
    processCount = ( Dem_u16_EventStrgIndexType )0U;
    retVal = DEM_IRT_PENDING;

    clrInfoNvmReadResult = Dem_ClrInfoMng_GetNvmReadResult();
    clearId = Dem_ClrInfoMng_GetClearID();
    obdClearId = Dem_ClrInfoMng_GetObdClearID();

    for( eventStrgIndex = Dem_DataMng_EventStrgIndexForVerify; eventStrgIndex < eventStorageNum; eventStrgIndex++ ) /* [GUD:for]eventStrgIndex */
    {
        if( processCount < verifyLoopNumByCycle )
        {
            eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( eventStrgIndex );                   /* [GUD]eventStrgIndex */
            if( eventOBDKind == (boolean)TRUE ) /*  OBD     */
            {
                clrInfoRecValue = obdClearId;
            }
            else
            {
                clrInfoRecValue = clearId;
            }
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
            eventMisfireKind = Dem_CfgInfoPm_GetEventKindOfMisfire_InEvtStrgGrp( eventStrgIndex );                  /* [GUD]eventStrgIndex */
            if( ( eventMisfireKind & DEM_EVTKIND_TYPE_MISFIRE_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_EVENT )
            {
                if( ( eventMisfireKind & DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT ) != DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT )
                {
                    Dem_MisfireMng_DataVerify( eventStrgIndex, clrInfoRecValue, clrInfoNvmReadResult );             /* [GUD]eventStrgIndex */
                    processCount = processCount + (Dem_u16_EventStrgIndexType)1U;
                }
            }
            else
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
            {
                Dem_DataMng_VerifyEvent( eventStrgIndex, clrInfoNvmReadResult, clrInfoRecValue );                   /* [GUD]eventStrgIndex */
                processCount = processCount + (Dem_u16_EventStrgIndexType)1U;
            }
        }
        else
        {
            Dem_DataMng_EventStrgIndexForVerify = eventStrgIndex;                                                   /* [GUD]eventStrgIndex */
            break;
        }
    }

    if( eventStrgIndex >= eventStorageNum )
    {
        Dem_DataMng_EventStrgIndexForVerify = eventStrgIndex;

        /* Clear not verrified record */
        retClrRecord = Dem_DataMng_ClearAllNotVerifiedRecord();
        if( retClrRecord == DEM_IRT_OK )
        {
            retVal = DEM_IRT_OK;
        }
        else
        {
            /* PENDING */
        }
    }

    return retVal;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dem_DataMng_VerifyEvent                                  */
/* Description   | Verifies Diag Event data.                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [in] ClrInfoNvmReadResult :                              */
/*               |        ClearInfo non-volatile memory read result         */
/* Parameters    | [in] ClearIdValue :                                      */
/*               |        Clear Id                                          */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-8-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DataMng_VerifyEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) ClrInfoNvmReadResult,
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) ClearIdValue
)
{
    VAR( boolean, AUTOMATIC ) resultOfFactoryCheck;
    VAR( boolean, AUTOMATIC ) resultOfCleaIdCheck;
    VAR( boolean, AUTOMATIC ) clearAllowed;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindEvent;
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */
#if ( DEM_CLEAR_EVENT_ALLOWED_BY_CALLOUT_SUPPORT == STD_ON )
    VAR( boolean, AUTOMATIC ) clearAllowedByCallout;
#endif  /* ( DEM_CLEAR_EVENT_ALLOWED_BY_CALLOUT_SUPPORT == STD_ON ) */

    recMngCmnKindEvent = Dem_RecMngCmnKindEvent;

    /* Check factory default */
    resultOfFactoryCheck = Dem_DataMng_FactoryCheckEvent( EventStrgIndex );         /* [GUDCHK:CALLER]EventStrgIndex */
    if( resultOfFactoryCheck != (boolean)TRUE )
    {
        clearAllowed = Dem_CfgInfoPm_ClearAllowedByConfig_InEvtStrgGrp( EventStrgIndex );   /* [GUDCHK:CALLER]EventStrgIndex */
        if( clearAllowed == (boolean)TRUE )
        {
            if( ClrInfoNvmReadResult != DEM_IRT_NG )
            {
                /* Check ClearID */
                resultOfCleaIdCheck = Dem_DataMng_ClearIdCheckEvent( EventStrgIndex, ClearIdValue );                /* [GUDCHK:CALLER]EventStrgIndex */
                if( resultOfCleaIdCheck == (boolean)TRUE )
                {
                    Dem_DataMng_VerifiedDiagData( EventStrgIndex );                                                 /* [GUDCHK:CALLER]EventStrgIndex */
                }
                else
                {
#if ( DEM_CLEAR_EVENT_ALLOWED_BY_CALLOUT_SUPPORT == STD_ON )
                    /*  check clear allowed from callout function.  */
                    clearAllowedByCallout   =   Dem_CfgInfoPm_JudgeClearAllowedByCallout( EventStrgIndex );             /* [GUDCHK:CALLER]EventStrgIndex */

                    if ( clearAllowedByCallout == (boolean)FALSE )
                    {
                        /*  It's not DTC clear target. so, no clear and start verify record.        */
                        Dem_DataMng_VerifiedDiagData( EventStrgIndex );                                                 /* [GUDCHK:CALLER]EventStrgIndex */
                    }
                    else
#endif  /* ( DEM_CLEAR_EVENT_ALLOWED_BY_CALLOUT_SUPPORT == STD_ON ) */
                    {
                        /* EventRecord and SimilarRecord are clear(with write NvM), if event is similar event. */
                        /* EventRecord is clear(without write NvM), if event is not similar event. */
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                        eventKind = Dem_CfgInfoPm_GetEventKindOfSpecific_InEvtStrgGrp( EventStrgIndex );                /* [GUDCHK:CALLER]EventStrgIndex */

                        if(( eventKind & DEM_EVTKIND_TYPE_SIMILAR_EVENT ) == DEM_EVTKIND_TYPE_SIMILAR_EVENT )
                        {
                            Dem_DataMngM_InitEventRecord( EventStrgIndex );                                             /* [GUDCHK:CALLER]EventStrgIndex */
                            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindEvent, ( Dem_u16_RecordIndexType )EventStrgIndex );
                            Dem_SimilarMng_NvMClearSimilarRecord_EventStrgIndex( EventStrgIndex );                      /* [GUDCHK:CALLER]EventStrgIndex */
                        }
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */
                    }
                }
            }
            else
            {
                /* Resets the status of DTC with default value. */
                Dem_DataMngM_InitEventRecord( EventStrgIndex );                                                     /* [GUDCHK:CALLER]EventStrgIndex */
                /* Change Dem_EventNvMStatus */
                Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindEvent, ( Dem_u16_RecordIndexType )EventStrgIndex );
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                Dem_SimilarMng_NvMClearSimilarRecord_EventStrgIndex( EventStrgIndex );                              /* [GUDCHK:CALLER]EventStrgIndex */
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */
            }
        }
        else
        {
            Dem_DataMng_VerifiedDiagData( EventStrgIndex );                                                         /* [GUDCHK:CALLER]EventStrgIndex */
        }
    }
    else
    {
        Dem_DataMngM_InitEventRecord( EventStrgIndex );                                                             /* [GUDCHK:CALLER]EventStrgIndex */
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindEvent, ( Dem_u16_RecordIndexType )EventStrgIndex );
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        Dem_SimilarMng_NvMClearSimilarRecord_EventStrgIndex( EventStrgIndex );                                      /* [GUDCHK:CALLER]EventStrgIndex */
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_DataMng_VerifiedDiagData                             */
/* Description   | Make Diag Data verified.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DataMng_VerifiedDiagData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultRec;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_FaultRecordType, AUTOMATIC ) faultRecord;
    VAR( boolean, AUTOMATIC ) eventRecordClearFlg;
    VAR( boolean, AUTOMATIC ) resultOfConsistencyCheck;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindEvent;
    VAR( boolean, AUTOMATIC ) consistencyIdUpdateFlg;
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */

    faultIndex = DEM_FAULTINDEX_INITIAL;
    eventRecordClearFlg = (boolean)TRUE;

    (void)Dem_DataMngC_GetER_FaultIndex( EventStrgIndex, &faultIndex );     /* no return check required */      /* [GUDCHK:CALLER]EventStrgIndex *//* [GUD:RET:DEM_IRT_OK] EventStrgIndex */
    resultOfGetFaultRec = Dem_DataMngC_GetFaultRecord( faultIndex, &faultRecord );                              /* [GUD:RET:DEM_IRT_OK] faultIndex */

    if( resultOfGetFaultRec == DEM_IRT_OK )
    {
        /* check reration of EventRecord and FaultRecord */
        if( EventStrgIndex == faultRecord.EventStrgIndex )
        {
            /* check consistencyId of EventRecord and FaultRecord */
            resultOfConsistencyCheck = Dem_DataMng_ConsistencyCheckEvent( EventStrgIndex, faultIndex );         /* [GUDCHK:CALLER]EventStrgIndex */
            if( resultOfConsistencyCheck == (boolean)TRUE )
            {
                eventRecordClearFlg = (boolean)FALSE;

                Dem_FFDMng_Verified( EventStrgIndex, faultIndex, &consistencyIdUpdateFlg );                     /* [GUDCHK:CALLER]EventStrgIndex */
#if ( DEM_TSFF_PM_SUPPORT == STD_ON ) /*  [FuncSw]    */
                Dem_TSFFDMng_Verified( EventStrgIndex, faultIndex );                                            /* [GUDCHK:CALLER]EventStrgIndex */
#endif /* (DEM_TSFF_PM_SUPPORT == STD_ON) */
#if ( DEM_OBDFFD_SUPPORT == STD_ON ) /*  [FuncSw]    */
                Dem_ObdFFDMng_Verified( EventStrgIndex, faultIndex, &consistencyIdUpdateFlg );                  /* [GUDCHK:CALLER]EventStrgIndex */
#endif /* (DEM_OBDFFD_SUPPORT == STD_ON) */
                Dem_DataMng_VerifyTrigger( EventStrgIndex, faultIndex );                                        /* [GUDCHK:CALLER]EventStrgIndex */

                if( Dem_FaultNvMStatus[ faultIndex ] == DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED )                    /* [GUD]faultIndex */
                {
                    Dem_FaultNvMStatus[ faultIndex ] = DEM_RECMNGCMN_NVM_STS_NON_TARGET;                        /* [GUD]faultIndex */
                }
            }
        }
    }
    else
    {
        if( faultIndex == DEM_FAULTINDEX_INITIAL )
        {
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
            eventKind = Dem_CfgInfoPm_GetEventKindOfSpecific_InEvtStrgGrp( EventStrgIndex );                    /* [GUDCHK:CALLER]EventStrgIndex */
            if(( eventKind & DEM_EVTKIND_TYPE_SIMILAR_EVENT ) == DEM_EVTKIND_TYPE_SIMILAR_EVENT )
            {
                resultOfConsistencyCheck = Dem_DataMng_ConsistencyCheckWithoutFault( EventStrgIndex );          /* [GUDCHK:CALLER]EventStrgIndex */
                if( resultOfConsistencyCheck == (boolean)TRUE )
                {
                    eventRecordClearFlg = (boolean)FALSE;
                }
                else
                {
                    /* event,similar record is clear */
                }
            }
            else
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */
            {
                eventRecordClearFlg = (boolean)FALSE;
            }
        }
    }

    if( eventRecordClearFlg == (boolean)TRUE )
    {
        /* Resets the status of DTC with default value. */
        Dem_DataMngM_InitEventRecord( EventStrgIndex );                                                         /* [GUDCHK:CALLER]EventStrgIndex */
        /* Change Dem_EventNvMStatus */
        recMngCmnKindEvent = Dem_RecMngCmnKindEvent;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindEvent, ( Dem_u16_RecordIndexType )EventStrgIndex );
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        Dem_SimilarMng_NvMClearSimilarRecord_EventStrgIndex( EventStrgIndex );                                  /* [GUDCHK:CALLER]EventStrgIndex */
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */
    }

    if( Dem_EventNvMStatus[ EventStrgIndex ] == DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED )                            /* [GUDCHK:CALLER]EventStrgIndex */
    {
        Dem_EventNvMStatus[ EventStrgIndex ] = DEM_RECMNGCMN_NVM_STS_NON_TARGET;                                /* [GUDCHK:CALLER]EventStrgIndex */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_VerifyTrigger                                */
/* Description   | Verifies Diag Fault data.                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index                                   */
/*               | [in] FaultIndex :                                        */
/*               |        The fault index                                   */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/*   v5-9-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMng_VerifyTrigger
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) chkStatusMask;
    VAR( boolean, AUTOMATIC ) existFFRFlg;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindEvent;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) freezeFrameIndex;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFreezeFrameIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;

    obdFFDRecordNum = Dem_CfgInfoPm_GetObdFFDRecordNum();
    obdFFRClassPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )      */

    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;
    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;


    chkStatusMask = ( DEM_UDS_STATUS_PDTC | DEM_UDS_STATUS_CDTC );

    /* check whether Pending or Confirmed bit is set */
    if( ( Dem_EventRecordList[EventStrgIndex].StatusOfDTC & chkStatusMask ) == DEM_DTCSTATUS_BYTE_ALL_OFF )             /* [GUDCHK:CALLER]EventStrgIndex */
    {
        /* check whether freeze frame is registered  */
        existFFRFlg = (boolean)FALSE;
        for( freezeFrameRecordIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordIndex < nonOBDFFRClassPerDTCMaxNum; freezeFrameRecordIndex++ )
        {
            freezeFrameIndex = DEM_FFRECINDEX_INITIAL;
            (void)Dem_DataMngC_GetFR_FreezeFrameIndex( FaultIndex, freezeFrameRecordIndex, &freezeFrameIndex );   /* no return check required */
            if( freezeFrameIndex < nonObdFFDRecordNum )
            {
                existFFRFlg = (boolean)TRUE;
                break;
            }
        }

#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
        if( existFFRFlg == (boolean)FALSE )
        {
            /* check whether OBD freeze frame is registered  */
            for( freezeFrameRecordIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordIndex < obdFFRClassPerDTCMaxNum; freezeFrameRecordIndex++ )
            {
                obdFreezeFrameIndex = DEM_FFRECINDEX_INITIAL;
                (void)Dem_DataMngC_GetFR_ObdFreezeFrameIndex( FaultIndex, freezeFrameRecordIndex, &obdFreezeFrameIndex );    /* no return check required */
                if( obdFreezeFrameIndex < obdFFDRecordNum )
                {
                    existFFRFlg = (boolean)TRUE;
                    break;
                }
            }
        }
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )      */


        if( existFFRFlg == (boolean)FALSE )
        {
            /* clear fault index of Event Record */
            Dem_DataMng_InitER_FaultIndex( EventStrgIndex );
            recMngCmnKindEvent = Dem_RecMngCmnKindEvent;
            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindEvent, ( Dem_u16_RecordIndexType )EventStrgIndex );

            /* clear fault Record */
            (void)Dem_DataMngC_ClearFaultRecord( FaultIndex ); /* no return check required */
        }
    }
    return ;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_FactoryCheckEvent                            */
/* Description   | verify factory status  of event data.                    */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/* Return Value  | boolean                                                  */
/*               |          TRUE      : Factory default                     */
/*               |          FALSE     : Non Factory default                 */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_DataMng_FactoryCheckEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( boolean, AUTOMATIC ) resultOfFactoryCheck;
    VAR( boolean, AUTOMATIC ) resultOfFactoryCheckEventRecord;
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) resultOfFactoryCheckSimilarRecord;
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */

    resultOfFactoryCheck = (boolean)FALSE;

    resultOfFactoryCheckEventRecord = Dem_DataMng_GetFactoryCheckResultOfEventRecord( EventStrgIndex );             /* [GUDCHK:CALLER]EventStrgIndex */

    if( resultOfFactoryCheckEventRecord == (boolean)TRUE )
    {
        resultOfFactoryCheck = (boolean)TRUE;
    }
    else
    {
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        resultOfFactoryCheckSimilarRecord = Dem_SimilarMng_GetFactoryCheckResult_EventStrgIndex( EventStrgIndex );  /* [GUDCHK:CALLER]EventStrgIndex */
        if( resultOfFactoryCheckSimilarRecord == (boolean)TRUE )
        {
            resultOfFactoryCheck = (boolean)TRUE;
        }
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */
    }

    return resultOfFactoryCheck;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_ClearIdCheckEvent                            */
/* Description   | verify clearId of event data.                            */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] MisfireIndex                                        */
/*               | [in] ClearID                                             */
/* Return Value  | boolean                                                  */
/*               |          TRUE      : ClearId check OK                    */
/*               |          FALSE     : ClearId check NG                    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_DataMng_ClearIdCheckEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) ClearID
)
{
    VAR( boolean, AUTOMATIC ) resultOfClearIdCheck;
    VAR( boolean, AUTOMATIC ) resultOfClearIdCheckEventRecord;
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) resultOfClearIdCheckSimilarRecord;
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */

    resultOfClearIdCheck = (boolean)TRUE;

    resultOfClearIdCheckEventRecord = Dem_DataMng_CheckClearIDOfEventRecord( EventStrgIndex, ClearID );             /* [GUDCHK:CALLER]EventStrgIndex */
    if( resultOfClearIdCheckEventRecord == (boolean)FALSE )
    {
        resultOfClearIdCheck = (boolean)FALSE;
    }
    else
    {
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        resultOfClearIdCheckSimilarRecord = Dem_SimilarMng_CheckClearId_EventStrgIndex( EventStrgIndex, ClearID );  /* [GUDCHK:CALLER]EventStrgIndex */
        if( resultOfClearIdCheckSimilarRecord == (boolean)FALSE )
        {
            resultOfClearIdCheck = (boolean)FALSE;
        }
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */
    }

    return resultOfClearIdCheck;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_ConsistencyCheckEvent                        */
/* Description   | verify of consistencyId event data.                      */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/* Return Value  | boolean                                                  */
/*               |          TRUE      : ConisistencyId check OK             */
/*               |          FALSE     : ConisistencyId check NG             */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_DataMng_ConsistencyCheckEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
)
{
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;
    VAR( boolean, AUTOMATIC ) resultOfConsistencyCheck;
    VAR( boolean, AUTOMATIC ) resultOfConsistencyCheckEventRecord;
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) resultOfConsistencyCheckSimilarRecord;
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */

    resultOfConsistencyCheck = (boolean)TRUE;

    (void)Dem_DataMng_GetFaultRecordConsistencyId( FaultIndex, &consistencyId); /* no return check required */

    resultOfConsistencyCheckEventRecord = Dem_DataMng_CheckConsistencyIdOfEventRecord( EventStrgIndex, consistencyId );         /* [GUDCHK:CALLER]EventStrgIndex */

    if( resultOfConsistencyCheckEventRecord == (boolean)FALSE )
    {
        resultOfConsistencyCheck = (boolean)FALSE;
    }
    else
    {
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        resultOfConsistencyCheckSimilarRecord = Dem_SimilarMng_CheckConsistencyId_EventStrgIndex( EventStrgIndex, consistencyId );  /* [GUDCHK:CALLER]EventStrgIndex */
        if( resultOfConsistencyCheckSimilarRecord == (boolean)FALSE )
        {
            resultOfConsistencyCheck = (boolean)FALSE;
        }
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */
    }

    return resultOfConsistencyCheck;
}


#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMng_ConsistencyCheckEvent                        */
/* Description   | verify of consistencyId event data.                      */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/* Return Value  | boolean                                                  */
/*               |          TRUE      : ConisistencyId check OK             */
/*               |          FALSE     : ConisistencyId check NG             */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_DataMng_ConsistencyCheckWithoutFault
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;
    VAR( boolean, AUTOMATIC ) resultOfConsistencyCheck;
    VAR( boolean, AUTOMATIC ) resultOfConsistencyCheckSimilarRecord;

    resultOfConsistencyCheck = (boolean)TRUE;

    Dem_DataMng_GetEventRecordConsistencyId( EventStrgIndex, &consistencyId); /* no return check required */                    /* [GUDCHK:CALLER]EventStrgIndex */

    resultOfConsistencyCheckSimilarRecord = Dem_SimilarMng_CheckConsistencyId_EventStrgIndex( EventStrgIndex, consistencyId );  /* [GUDCHK:CALLER]EventStrgIndex */
    if( resultOfConsistencyCheckSimilarRecord == (boolean)FALSE )
    {
        resultOfConsistencyCheck = (boolean)FALSE;
    }

    return resultOfConsistencyCheck;
}
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */


/****************************************************************************/
/* Function Name | Dem_DataMng_ClearAllNotVerifiedRecord                    */
/* Description   | clear not verified record                                */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_ClearAllNotVerifiedRecord
( void )
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) clearRecordKindIndex;
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) clearRecordIndex;
    VAR( Dem_u32_TotalRecordNumType, AUTOMATIC ) restOfProcessableNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) clearRecordKindIndexNum;
    VAR( boolean,AUTOMATIC ) loopEnd;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retClearFnc;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    clearRecordKindIndex = Dem_DataMng_ClearRecordKind;     /* [GUD:CFG]clearRecordKindIndex */
    clearRecordIndex = Dem_DataMng_ClearRecordIndex;
    clearRecordKindIndexNum = Dem_RecMngCmnClrRecKindNum;
    restOfProcessableNum = Dem_RecordNumForVerifyByCycle;
    loopEnd = (boolean)FALSE;
    retVal = DEM_IRT_PENDING;

    while( loopEnd == (boolean)FALSE )
    {
        /*  call clear no verified record function.        */
#ifndef JGXSTACK
        retClearFnc = Dem_ClrNotVerifiedRecordFuncTable[clearRecordKindIndex]( &clearRecordIndex, &restOfProcessableNum );  /* [GUD]clearRecordKindIndex */
#else   /* JGXSTACK */
        retClearFnc = Dem_RecMngClrNotVerifiedRecordFunc_ForStack( &clearRecordIndex, &restOfProcessableNum );
#endif  /* JGXSTACK */
        if( retClearFnc == DEM_IRT_OK )
        {
            clearRecordKindIndex = clearRecordKindIndex + (Dem_u16_RecordKindIndexType)1U;
            if( clearRecordKindIndex < clearRecordKindIndexNum )
            {
                clearRecordIndex = (Dem_u16_RecordIndexType)0U;
                if( restOfProcessableNum == (Dem_u32_TotalRecordNumType)0U )
                {
                      Dem_DataMng_ClearRecordKind  =  clearRecordKindIndex;
                      Dem_DataMng_ClearRecordIndex  =  clearRecordIndex;
                      loopEnd = (boolean)TRUE;
                }
            }
            else
            {
                loopEnd = (boolean)TRUE;
                retVal = DEM_IRT_OK;
            }
        }
        /*  continute DataVerify mode or not.   */
        else /* retClearFnc == DEM_IRT_PENDING ) */
        {
            Dem_DataMng_ClearRecordKind  =  clearRecordKindIndex;
            Dem_DataMng_ClearRecordIndex  =  clearRecordIndex;
            loopEnd = (boolean)TRUE;
        }
    }

    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
