/* Dem_DataCtl_DisReqUpd_GetFFIdx_FilRec_c(v5-8-0)                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_DisReqUpd_GetFFIdx_FilRec/CODE                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_DataCtl.h"
#include "../../../inc/Dem_CmnLib_DataCtl_TSFFD.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Rc_MisfireMng.h"

#include "Dem_DataCtl_local.h"

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )

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

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_SetTmpObdRecordNumberForFilteredRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ObdFFDRecordNum,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassRefIndex,
    P2VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC, AUTOMATIC ) TmpRecordNumberForOnRetrievalPtr
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

static FUNC( void, DEM_CODE ) Dem_Data_SetTmpRecordNumberForFileredRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) NonObdFFDRecordNum,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassRefIndex,
    P2VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC, AUTOMATIC ) TmpRecordNumberForOnRetrievalPtr
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

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_GetDisabledObdRecordNumberIndexForFilteredRecord*/
/* Description   | Gets the ObdRecordNumberIndex which has the highest pri- */
/*               | ority event, and set to FFDIndexListStPtr corresponding  */
/*               | to the FreezeFrameRecordClassRefIndex.                   */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [in] FreezeFrameRecordClassRefIndex :                    */
/*               |        The index to array of FreezeFrameRecordClassRef.  */
/*               | [out] EventStrgIndexPtr :                                */
/*               |        The regular EventStrgIndex.                       */
/* Return Value  | Dem_u08_FFDIndexType                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | new created. based on Dem_Data_GetDisabledObdRecordNumberIndex. */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_Data_GetDisabledObdRecordNumberIndexForFilteredRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassRefIndex,       /* [PRMCHK:CALLER] */
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
)
{
    VAR( boolean, AUTOMATIC ) availableStatus;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) freezeFrameIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexCnt;
    VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC ) tmpRecordNumberForOnRetrieval;
    VAR( boolean, AUTOMATIC ) searchEndFlg;

    obdFFDRecordNum = Dem_CfgInfoPm_GetObdFFDRecordNum();
    freezeFrameIndex = DEM_FFDINDEX_INVALID;

    searchEndFlg = (boolean)FALSE;

    /* get num of event index in DTC group. */
    eventStrgIndexNum = Dem_CmbEvt_NumOfEventStrgIndex_InDTCGrp( EventStrgIndex );
    if( eventStrgIndexNum > ( Dem_u16_EventStrgIndexType )0U )
    {
        Dem_Data_SetTmpObdRecordNumberForFilteredRecord( EventStrgIndex, obdFFDRecordNum, FreezeFrameRecordClassRefIndex, &tmpRecordNumberForOnRetrieval );

        if( tmpRecordNumberForOnRetrieval.FreezeFrameIndex < obdFFDRecordNum )
        {
            if( tmpRecordNumberForOnRetrieval.EventClassPriority != DEM_EVENTCLASS_PRIORITY_CLASS_NONE )
            {
                searchEndFlg = (boolean)TRUE;
            }
        }

        if ( searchEndFlg == (boolean)FALSE )
        {
            if( eventStrgIndexNum > ( Dem_u16_EventStrgIndexType )1U )
            {
                /* get next event index. */
                eventStrgIndex = Dem_CmbEvt_GetNextEventStrgIndex_InDTCGrp( EventStrgIndex );

                eventStrgIndexNum = eventStrgIndexNum - ( Dem_u16_EventStrgIndexType )1U;

                for( eventStrgIndexCnt = ( Dem_u16_EventStrgIndexType )0U; eventStrgIndexCnt < eventStrgIndexNum; eventStrgIndexCnt++ )
                {
                    /* Checks event available status */
                    availableStatus = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndex );
                    if( availableStatus == (boolean)TRUE )
                    {
                        Dem_Data_SetTmpObdRecordNumberForFilteredRecord( eventStrgIndex, obdFFDRecordNum, FreezeFrameRecordClassRefIndex, &tmpRecordNumberForOnRetrieval );
                        if( tmpRecordNumberForOnRetrieval.FreezeFrameIndex < obdFFDRecordNum )
                        {
                            if( tmpRecordNumberForOnRetrieval.EventClassPriority != DEM_EVENTCLASS_PRIORITY_CLASS_NONE )
                            {
                                searchEndFlg = (boolean)TRUE;
                                break;
                            }
                        }
                    }

                    /* get next event index. */
                    eventStrgIndex = Dem_CmbEvt_GetNextEventStrgIndex_InDTCGrp( eventStrgIndex );
                }
            }
        }

        if ( searchEndFlg == (boolean)TRUE )
        {
            freezeFrameIndex = tmpRecordNumberForOnRetrieval.FreezeFrameIndex;
            ( *EventStrgIndexPtr ) = tmpRecordNumberForOnRetrieval.EventStrgIndex;
        }
    }

    return freezeFrameIndex;
}

/****************************************************************************/
/* Function Name | Dem_Data_SetTmpObdRecordNumberForFilteredRecord           */
/* Description   | Gets the tmpRecordNumberForOnRetrieval corresponding to  */
/*               | the EventStrgIndex, the FreezeFrameRecordTrigger and th- */
/*               | e FreezeFrameRecordClassRefIndex.                        */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [in] ObdFFDRecordNum :                                   */
/*               |        The number of OBD Freeze Frame Records.           */
/*               | [in] FreezeFrameRecordClassRefIndex :                    */
/*               |        The index to array of FreezeFrameRecordClassRef.  */
/*               | [out] TmpRecordNumberForOnRetrievalPtr :                 */
/*               |        tmpRecordNumberForOnRetrieval pointer.            */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | new created. based on Dem_Data_SetTmpObdRecordNumberForOnRetrieval */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_SetTmpObdRecordNumberForFilteredRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ObdFFDRecordNum,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassRefIndex,       /* [PRMCHK:CALLER] */
    P2VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC, AUTOMATIC ) TmpRecordNumberForOnRetrievalPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetER;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFR;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) freezeFrameIndex;
    VAR( Dem_FaultRecordType, AUTOMATIC ) faultRecord;

    Dem_Data_InitTmpRecordNumberForOnRetrieval( TmpRecordNumberForOnRetrievalPtr );

    resultOfGetER = Dem_DataMngC_GetER_FaultIndex( EventStrgIndex, &faultIndex );
    if( resultOfGetER == DEM_IRT_OK )
    {
        resultOfGetFR = Dem_DataMngC_GetFaultRecord( faultIndex, &faultRecord );
        if( resultOfGetFR == DEM_IRT_OK )
        {
            freezeFrameIndex = faultRecord.ObdRecordNumberIndex[ FreezeFrameRecordClassRefIndex ];      /* [GUDCHK:CALLER]FreezeFrameRecordClassRefIndex *//* [ARYCHK] DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / FreezeFrameRecordClassRefIndex */
            if( freezeFrameIndex < ObdFFDRecordNum )
            {
                TmpRecordNumberForOnRetrievalPtr->EventStrgIndex = EventStrgIndex;
                TmpRecordNumberForOnRetrievalPtr->FreezeFrameIndex = freezeFrameIndex;

                Dem_Data_SetEventClassPriorityForOnRetrieval( EventStrgIndex, TmpRecordNumberForOnRetrievalPtr );
            }
        }
    }

    return;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

/****************************************************************************/
/* Function Name | Dem_Data_GetDisabledRecordNumberIndexForFilteredRecord   */
/* Description   | Gets the RecordNumberIndex which has the highest priori- */
/*               | ty event, and set to FFDIndexListStPtr corresponding to  */
/*               | the FreezeFrameRecordClassRefIndex.                      */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [in] FreezeFrameRecordClassRefIndex :                    */
/*               |        The index to array of FreezeFrameRecordClassRef.  */
/*               | [out] EventStrgIndexPtr :                                */
/*               |        The regular EventStrgIndex.                       */
/* Return Value  | Dem_u08_FFDIndexType                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | new created. based on Dem_Data_GetDisabledRecordNumberIndex. */
/****************************************************************************/
FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_Data_GetDisabledRecordNumberIndexForFilteredRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassRefIndex,       /* [PRMCHK:CALLER] */
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
)
{
    VAR( boolean, AUTOMATIC ) availableStatus;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) freezeFrameIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexCnt;
    VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC ) tmpRecordNumberForOnRetrieval;
    VAR( boolean, AUTOMATIC ) searchEndFlg;

    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;
    freezeFrameIndex = DEM_FFDINDEX_INVALID;

    searchEndFlg = (boolean)FALSE;

    /* get num of event index in DTC group. */
    eventStrgIndexNum = Dem_CmbEvt_NumOfEventStrgIndex_InDTCGrp( EventStrgIndex );
    if( eventStrgIndexNum > ( Dem_u16_EventStrgIndexType )0U )
    {
        Dem_Data_SetTmpRecordNumberForFileredRecord( EventStrgIndex, nonObdFFDRecordNum, FreezeFrameRecordClassRefIndex, &tmpRecordNumberForOnRetrieval );

        if( tmpRecordNumberForOnRetrieval.FreezeFrameIndex < nonObdFFDRecordNum )
        {
            searchEndFlg = (boolean)TRUE;
        }

        if ( searchEndFlg == (boolean)FALSE )
        {
            if( eventStrgIndexNum > ( Dem_u16_EventStrgIndexType )1U )
            {
                /* get next event index. */
                eventStrgIndex = Dem_CmbEvt_GetNextEventStrgIndex_InDTCGrp( EventStrgIndex );

                eventStrgIndexNum = eventStrgIndexNum - ( Dem_u16_EventStrgIndexType )1U;

                for( eventStrgIndexCnt = ( Dem_u16_EventStrgIndexType )0U; eventStrgIndexCnt < eventStrgIndexNum; eventStrgIndexCnt++ )
                {
                    /* Checks event available status */
                    availableStatus = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndex );
                    if( availableStatus == (boolean)TRUE )
                    {
                        Dem_Data_SetTmpRecordNumberForFileredRecord( eventStrgIndex, nonObdFFDRecordNum, FreezeFrameRecordClassRefIndex, &tmpRecordNumberForOnRetrieval );
                        if( tmpRecordNumberForOnRetrieval.FreezeFrameIndex < nonObdFFDRecordNum )
                        {
                            searchEndFlg = (boolean)TRUE;
                            break;
                        }
                    }

                    /* get next event index. */
                    eventStrgIndex = Dem_CmbEvt_GetNextEventStrgIndex_InDTCGrp( eventStrgIndex );
                }
            }
        }

        if ( searchEndFlg == (boolean)TRUE )
        {
            freezeFrameIndex = tmpRecordNumberForOnRetrieval.FreezeFrameIndex;
            ( *EventStrgIndexPtr ) = tmpRecordNumberForOnRetrieval.EventStrgIndex;
        }
    }

    return freezeFrameIndex;
}

/****************************************************************************/
/* Function Name | Dem_Data_SetTmpRecordNumberForFileredRecord              */
/* Description   | Gets the tmpRecordNumberForOnRetrieval corresponding to  */
/*               | the EventStrgIndex, the FreezeFrameRecordClassPtr and t- */
/*               | he FreezeFrameRecordClassRefIndex.                       */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [in] NonObdFFDRecordNum :                                */
/*               |        The number of non-OBD Freeze Frame Records.       */
/*               | [in] FreezeFrameRecordClassRefIndex :                    */
/*               |        The index to array of FreezeFrameRecordClassRef.  */
/*               | [out] TmpRecordNumberForOnRetrievalPtr :                 */
/*               |        tmpRecordNumberForOnRetrieval pointer.            */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | new created. based on Dem_Data_SetTmpRecordNumberForOnRetrieval */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_SetTmpRecordNumberForFileredRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) NonObdFFDRecordNum,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassRefIndex,       /* [PRMCHK:CALLER] */
    P2VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC, AUTOMATIC ) TmpRecordNumberForOnRetrievalPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetER;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFR;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) freezeFrameIndex;
    VAR( Dem_FaultRecordType, AUTOMATIC ) faultRecord;

    Dem_Data_InitTmpRecordNumberForOnRetrieval( TmpRecordNumberForOnRetrievalPtr );

    resultOfGetER = Dem_DataMngC_GetER_FaultIndex( EventStrgIndex, &faultIndex );
    if( resultOfGetER == DEM_IRT_OK )
    {
        resultOfGetFR = Dem_DataMngC_GetFaultRecord( faultIndex, &faultRecord );
        if( resultOfGetFR == DEM_IRT_OK )
        {
            freezeFrameIndex = faultRecord.RecordNumberIndex[ FreezeFrameRecordClassRefIndex ];     /* [GUDCHK:CALLER]FreezeFrameRecordClassRefIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / FreezeFrameRecordClassRefIndex */
            if( freezeFrameIndex < NonObdFFDRecordNum )
            {
                TmpRecordNumberForOnRetrievalPtr->EventStrgIndex = EventStrgIndex;
                TmpRecordNumberForOnRetrievalPtr->FreezeFrameIndex = freezeFrameIndex;
            }
        }
    }

    return;
}

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_GetDisabledTimeSeriesFreezeFrameListIndexForFilteredRecord       */
/* Description   | Gets the TimeSeriesFreezeFrameListIndex which has the s- */
/*               | ame trigger of the trigger-FFD from event, and set to F- */
/*               | FDIndexListStPtr corresponding to the TSFFRecClassRefIn- */
/*               | dex.                                                     */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [in] TSFFRecClassRefIndex :                              */
/*               |        The reference index to array of DemTimeSeriesFre- */
/*               |        ezeFrameRecordClassRef of the DemDTCAttribute.    */
/*               | [in] TSFFRecordTrigger :                                 */
/*               |        The DemFreezeFrameRecordTrigger.(for TSFFD)       */
/*               | [in] NumberOfSaveRecordForTriggerFFD :                   */
/*               |        The number of saved Dem_TmpDisabledRecord array   */
/*               |        for trigger FFD.                                  */
/*               | [out] EventStrgIndexPtr :                                */
/*               |        The regular EventStrgIndex.                       */
/* Return Value  | Dem_u16_TSFFListIndexType                                */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | new created. based on Dem_Data_GetDisabledTimeSeriesFreezeFrameListIndex. */
/****************************************************************************/
FUNC( Dem_u16_TSFFListIndexType, DEM_CODE ) Dem_Data_GetDisabledTimeSeriesFreezeFrameListIndexForFilteredRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) TSFFRecClassRefIndex,         /* [PRMCHK:CALLER] */
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) TSFFRecordTrigger,
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) NumberOfSaveRecordForTriggerFFD,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
)
{
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) freezeFrameClassRef;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) freezeframeRecNumClassRef;
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecNumClassPtr;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

    tsFFListIndex = DEM_TSFFLISTINDEX_INVALID;
    eventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    eventKind = Dem_CfgInfoPm_GetEventKindOfSpecific_InEvtStrgGrp( EventStrgIndex );    /* [GUD]EventStrgIndex */
    if( ( eventKind & DEM_EVTKIND_TYPE_MISFIRE_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_EVENT )
    {
        tsFFListIndex = Dem_Data_GetTSFFListIndexByEventStrgIndex( EventStrgIndex, TSFFRecClassRefIndex ); /* [GUD]EventStrgIndex */ /* [GUDCHK:CALLER]TSFFRecClassRefIndex */
        ( *EventStrgIndexPtr ) = EventStrgIndex;
    }
    else
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
    {
        /* Gets the porint of non-OBD DemFreezeFrameRecNumClass's reference of the specified delegate event in the same DTC group. */
        Dem_CfgInfoPm_GetFreezeFrameAndRecNumClass( EventStrgIndex, &freezeFrameClassRef, &freezeframeRecNumClassRef );  /* [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] freezeFrameClassRef *//* [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] freezeframeRecNumClassRef */
        if( freezeframeRecNumClassRef != DEM_FFRECNUMCLASSINDEX_INVALID )                                                   /* [GUD:if] freezeframeRecNumClassRef */
        {
            freezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[ freezeframeRecNumClassRef ];                      /* [GUD] freezeframeRecNumClassRef */
            eventStorageNum = Dem_PrimaryMemEventStorageNum;
            eventStrgIndex = Dem_Data_SearchNonObdEventStrgIndexByTSFFRTrigger( TSFFRecordTrigger, NumberOfSaveRecordForTriggerFFD, freezeFrameRecNumClassPtr );
            if( eventStrgIndex < eventStorageNum )      /* [GUD:if]eventStrgIndex */
            {
                /* Gets TimeSeriesFreezeFrameListIndex. */
                tsFFListIndex = Dem_Data_GetTSFFListIndexByEventStrgIndex( eventStrgIndex, TSFFRecClassRefIndex );  /* [GUD]eventStrgIndex */ /* [GUDCHK:CALLER]TSFFRecClassRefIndex */
            }
        }

        ( *EventStrgIndexPtr ) = eventStrgIndex;
    }

    return tsFFListIndex;
}
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /*   ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
