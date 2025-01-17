/* Dem_DataCtl_DisReqUpd_GetFFIdx_RtvlOn_c(v5-5-0)                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dem_DataCtl_DisReqUpd_GetFFIdx_RtvlOn/CODE            */
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
/*--------------------------------------------------------------------------*/\
typedef struct {
    Dem_u16_OccrOrderType               OccurrenceOrder;
    Dem_u16_EventStrgIndexType          EventStrgIndex;
    Dem_u08_FFDIndexType                FreezeFrameIndex;
    Dem_u08_EventClassPriorityType      EventClassPriority;
    Dem_u08_EventStatusPriorityType     EventStatusPriority;
} Dem_TmpRecordNumberForOnRetrievalType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_SetTmpObdRecordNumberForOnRetrieval
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ObdFFDRecordNum,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassRefIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
    P2VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC, AUTOMATIC ) TmpRecordNumberForOnRetrievalPtr
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

static FUNC( void, DEM_CODE ) Dem_Data_InitTmpRecordNumberForOnRetrieval
(
    P2VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC, AUTOMATIC ) TmpRecordNumberForOnRetrievalPtr
);

static FUNC( void, DEM_CODE ) Dem_Data_SetTmpRecordNumberForOnRetrieval
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) NonObdFFDRecordNum,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassRefIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
    P2VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC, AUTOMATIC ) TmpRecordNumberForOnRetrievalPtr
);

static FUNC( void, DEM_CODE ) Dem_Data_SetEventClassPriorityForOnRetrieval
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC, AUTOMATIC ) TmpRecordNumberForOnRetrievalPtr
);

static FUNC( void, DEM_CODE ) Dem_Data_SetEventStatusPriorityForOnRetrieval
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC, AUTOMATIC ) TmpRecordNumberForOnRetrievalPtr
);

static FUNC( void, DEM_CODE ) Dem_Data_SetOccurrenceOrderForOnRetrieval
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC, AUTOMATIC ) TmpRecordNumberForOnRetrievalPtr
);

static FUNC( void, DEM_CODE ) Dem_Data_JudgePriorityOfTmpRecordNumberForOnRetrieval
(
    P2VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC, AUTOMATIC ) BaseTmpRecordNumberForOnRetrievalPtr,
    P2VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC, AUTOMATIC ) TargetTmpRecordNumberForOnRetrievalPtr
);

static FUNC( void, DEM_CODE ) Dem_Data_TransferTmpRecordNumberForOnRetrieval
(
    P2VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC, AUTOMATIC ) BaseTmpRecordNumberForOnRetrievalPtr,
    P2VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC, AUTOMATIC ) TargetTmpRecordNumberForOnRetrievalPtr
);

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
static FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_Data_SearchNonObdEventStrgIndexByTSFFRTrigger
(
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) TSFFRecordTrigger,
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) NumberOfSaveRecordForTriggerFFD,
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameRecNumClassPtr
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_CheckFreezeFrameRecNumClass
(
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) TmpRecordNumber,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) TSFFRecordTrigger,
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameRecNumClassPtr
);

static FUNC( Dem_u16_TSFFListIndexType, DEM_CODE ) Dem_Data_GetTSFFListIndexByEventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) TSFFRecClassRefIndex
);
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */

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
/* Function Name | Dem_Data_GetDisabledObdRecordNumberIndex                 */
/* Description   | Gets the ObdRecordNumberIndex which has the highest pri- */
/*               | ority event, and set to FFDIndexListStPtr corresponding  */
/*               | to the FreezeFrameRecordClassRefIndex.                   */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [in] FreezeFrameRecordClassRefIndex :                    */
/*               |        The index to array of FreezeFrameRecordClassRef.  */
/*               | [in] FreezeFrameRecordTrigger :                          */
/*               |        The DemFreezeFrameRecordTrigger.                  */
/*               | [out] FFDIndexListStPtr :                                */
/*               |        Dem_TmpDisabledRecord.FFDIndexListSt pointer.     */
/*               | [out] EventStrgIndexPtr :                                */
/*               |        The regular EventStrgIndex.                       */
/* Return Value  | Dem_u08_FFDIndexType                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_Data_GetDisabledObdRecordNumberIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassRefIndex,       /* [PRMCHK:CALLER] */
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
    P2VAR( Dem_FaultRecordPartsFFDIndexListStType, AUTOMATIC, DEM_VAR_NO_INIT ) FFDIndexListStPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
)
{
    VAR( boolean, AUTOMATIC ) availableStatus;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) freezeFrameIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexCnt;
    VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC ) baseTmpRecordNumberForOnRetrieval;
    VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC ) targetTmpRecordNumberForOnRetrieval;

    obdFFDRecordNum = Dem_ObdFFDRecordNum;
    freezeFrameIndex = DEM_FFDINDEX_INVALID;

    /* get num of event index in DTC group. */
    eventStrgIndexNum = Dem_CmbEvt_NumOfEventStrgIndex_InDTCGrp( EventStrgIndex );
    if( eventStrgIndexNum > ( Dem_u16_EventStrgIndexType )0U )
    {
        Dem_Data_SetTmpObdRecordNumberForOnRetrieval( EventStrgIndex, obdFFDRecordNum, FreezeFrameRecordClassRefIndex, FreezeFrameRecordTrigger, &baseTmpRecordNumberForOnRetrieval );

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
                    Dem_Data_SetTmpObdRecordNumberForOnRetrieval( eventStrgIndex, obdFFDRecordNum, FreezeFrameRecordClassRefIndex, FreezeFrameRecordTrigger, &targetTmpRecordNumberForOnRetrieval );
                    /* Judges the priority. */
                    Dem_Data_JudgePriorityOfTmpRecordNumberForOnRetrieval( &baseTmpRecordNumberForOnRetrieval, &targetTmpRecordNumberForOnRetrieval );
                }

                /* get next event index. */
                eventStrgIndex = Dem_CmbEvt_GetNextEventStrgIndex_InDTCGrp( eventStrgIndex );
            }
        }

        if( baseTmpRecordNumberForOnRetrieval.FreezeFrameIndex < obdFFDRecordNum )
        {
            if( baseTmpRecordNumberForOnRetrieval.EventClassPriority == DEM_EVENTCLASS_PRIORITY_CLASS_NONE )
            {
                FFDIndexListStPtr->ObdRecordNumberIndex[ FreezeFrameRecordClassRefIndex ] = DEM_FFDINDEX_INVALID;                                   /* [GUDCHK:CALLER]FreezeFrameRecordClassRefIndex */
            }
            else
            {
                FFDIndexListStPtr->ObdRecordNumberIndex[ FreezeFrameRecordClassRefIndex ] = baseTmpRecordNumberForOnRetrieval.FreezeFrameIndex;     /* [GUDCHK:CALLER]FreezeFrameRecordClassRefIndex */

                freezeFrameIndex = FFDIndexListStPtr->ObdRecordNumberIndex[ FreezeFrameRecordClassRefIndex ];                                       /* [GUDCHK:CALLER]FreezeFrameRecordClassRefIndex */
                ( *EventStrgIndexPtr ) = baseTmpRecordNumberForOnRetrieval.EventStrgIndex;
            }
        }
    }

    return freezeFrameIndex;
}

/****************************************************************************/
/* Function Name | Dem_Data_SetTmpObdRecordNumberForOnRetrieval             */
/* Description   | Gets the TmpRecordNumberForOnRetrieval corresponding to  */
/*               | the EventStrgIndex, the FreezeFrameRecordTrigger and th- */
/*               | e FreezeFrameRecordClassRefIndex.                        */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [in] ObdFFDRecordNum :                                   */
/*               |        The number of OBD Freeze Frame Records.           */
/*               | [in] FreezeFrameRecordClassRefIndex :                    */
/*               |        The index to array of FreezeFrameRecordClassRef.  */
/*               | [in] FreezeFrameRecordTrigger :                          */
/*               |        The DemFreezeFrameRecordTrigger.                  */
/*               | [out] TmpRecordNumberForOnRetrievalPtr :                 */
/*               |        TmpRecordNumberForOnRetrieval pointer.            */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_SetTmpObdRecordNumberForOnRetrieval
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ObdFFDRecordNum,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassRefIndex,       /* [PRMCHK:CALLER] */
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
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
            freezeFrameIndex = faultRecord.ObdRecordNumberIndex[ FreezeFrameRecordClassRefIndex ];      /* [GUDCHK:CALLER]FreezeFrameRecordClassRefIndex */
            if( freezeFrameIndex < ObdFFDRecordNum )
            {
                TmpRecordNumberForOnRetrievalPtr->EventStrgIndex = EventStrgIndex;
                TmpRecordNumberForOnRetrievalPtr->FreezeFrameIndex = freezeFrameIndex;

                Dem_Data_SetEventClassPriorityForOnRetrieval( EventStrgIndex, TmpRecordNumberForOnRetrievalPtr );
                Dem_Data_SetEventStatusPriorityForOnRetrieval( EventStrgIndex, TmpRecordNumberForOnRetrievalPtr );
                Dem_Data_SetOccurrenceOrderForOnRetrieval( FreezeFrameRecordTrigger, &faultRecord, TmpRecordNumberForOnRetrievalPtr );
            }
        }
    }

    return;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

/****************************************************************************/
/* Function Name | Dem_Data_GetDisabledRecordNumberIndex                    */
/* Description   | Gets the RecordNumberIndex which has the highest priori- */
/*               | ty event, and set to FFDIndexListStPtr corresponding to  */
/*               | the FreezeFrameRecordClassRefIndex.                      */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [in] FreezeFrameRecordClassRefIndex :                    */
/*               |        The index to array of FreezeFrameRecordClassRef.  */
/*               | [in] FreezeFrameRecordClassPtr :                         */
/*               |        The pointer to Dem_FreezeFrameRecordClassTable.   */
/*               | [out] FFDIndexListStPtr :                                */
/*               |        Dem_TmpDisabledRecord.FFDIndexListSt pointer.     */
/*               | [out] EventStrgIndexPtr :                                */
/*               |        The regular EventStrgIndex.                       */
/* Return Value  | Dem_u08_FFDIndexType                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_Data_GetDisabledRecordNumberIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassRefIndex,       /* [PRMCHK:CALLER] */
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
    P2VAR( Dem_FaultRecordPartsFFDIndexListStType, AUTOMATIC, DEM_VAR_NO_INIT ) FFDIndexListStPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
)
{
    VAR( boolean, AUTOMATIC ) availableStatus;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) freezeFrameIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexCnt;
    VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC ) baseTmpRecordNumberForOnRetrieval;
    VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC ) targetTmpRecordNumberForOnRetrieval;

    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;
    freezeFrameIndex = DEM_FFDINDEX_INVALID;

    /* get num of event index in DTC group. */
    eventStrgIndexNum = Dem_CmbEvt_NumOfEventStrgIndex_InDTCGrp( EventStrgIndex );
    if( eventStrgIndexNum > ( Dem_u16_EventStrgIndexType )0U )
    {
        Dem_Data_SetTmpRecordNumberForOnRetrieval( EventStrgIndex, nonObdFFDRecordNum, FreezeFrameRecordClassRefIndex, FreezeFrameRecordTrigger, &baseTmpRecordNumberForOnRetrieval );

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
                    Dem_Data_SetTmpRecordNumberForOnRetrieval( eventStrgIndex, nonObdFFDRecordNum, FreezeFrameRecordClassRefIndex, FreezeFrameRecordTrigger, &targetTmpRecordNumberForOnRetrieval );
                    /* Judges the priority. */
                    Dem_Data_JudgePriorityOfTmpRecordNumberForOnRetrieval( &baseTmpRecordNumberForOnRetrieval, &targetTmpRecordNumberForOnRetrieval );
                }

                /* get next event index. */
                eventStrgIndex = Dem_CmbEvt_GetNextEventStrgIndex_InDTCGrp( eventStrgIndex );
            }
        }

        if( baseTmpRecordNumberForOnRetrieval.FreezeFrameIndex < nonObdFFDRecordNum )
        {
            FFDIndexListStPtr->RecordNumberIndex[ FreezeFrameRecordClassRefIndex ] = baseTmpRecordNumberForOnRetrieval.FreezeFrameIndex;    /* [GUDCHK:CALLER]FreezeFrameRecordClassRefIndex */

            freezeFrameIndex = FFDIndexListStPtr->RecordNumberIndex[ FreezeFrameRecordClassRefIndex ];                                      /* [GUDCHK:CALLER]FreezeFrameRecordClassRefIndex */
            ( *EventStrgIndexPtr ) = baseTmpRecordNumberForOnRetrieval.EventStrgIndex;
        }
    }

    return freezeFrameIndex;
}

/****************************************************************************/
/* Function Name | Dem_Data_InitTmpRecordNumberForOnRetrieval               */
/* Description   | Initializes the specified TmpRecordNumberForOnRetrieval. */
/* Preconditions |                                                          */
/* Parameters    | [out] TmpRecordNumberForOnRetrievalPtr :                 */
/*               |        TmpRecordNumberForOnRetrieval pointer.            */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_InitTmpRecordNumberForOnRetrieval
(
    P2VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC, AUTOMATIC ) TmpRecordNumberForOnRetrievalPtr
)
{
    TmpRecordNumberForOnRetrievalPtr->EventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
    TmpRecordNumberForOnRetrievalPtr->FreezeFrameIndex = DEM_FFDINDEX_INVALID;
    TmpRecordNumberForOnRetrievalPtr->EventClassPriority = DEM_EVENTCLASS_PRIORITY_CLASS_NONE;
    TmpRecordNumberForOnRetrievalPtr->EventStatusPriority = DEM_EVENTSTATUS_PRIORITY_NO_FAULT;
    TmpRecordNumberForOnRetrievalPtr->OccurrenceOrder = DEM_FAIL_OCCURRENCE_NUM_INVALID;

    return;
}

/****************************************************************************/
/* Function Name | Dem_Data_SetTmpRecordNumberForOnRetrieval                */
/* Description   | Gets the TmpRecordNumberForOnRetrieval corresponding to  */
/*               | the EventStrgIndex, the FreezeFrameRecordClassPtr and t- */
/*               | he FreezeFrameRecordClassRefIndex.                       */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [in] NonObdFFDRecordNum :                                */
/*               |        The number of non-OBD Freeze Frame Records.       */
/*               | [in] FreezeFrameRecordClassRefIndex :                    */
/*               |        The index to array of FreezeFrameRecordClassRef.  */
/*               | [in] FreezeFrameRecordTrigger :                          */
/*               |        The DemFreezeFrameRecordTrigger.                  */
/*               | [out] TmpRecordNumberForOnRetrievalPtr :                 */
/*               |        TmpRecordNumberForOnRetrieval pointer.            */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_SetTmpRecordNumberForOnRetrieval
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) NonObdFFDRecordNum,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassRefIndex,       /* [PRMCHK:CALLER] */
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
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
            freezeFrameIndex = faultRecord.RecordNumberIndex[ FreezeFrameRecordClassRefIndex ];     /* [GUDCHK:CALLER]FreezeFrameRecordClassRefIndex */
            if( freezeFrameIndex < NonObdFFDRecordNum )
            {
                TmpRecordNumberForOnRetrievalPtr->EventStrgIndex = EventStrgIndex;
                TmpRecordNumberForOnRetrievalPtr->FreezeFrameIndex = freezeFrameIndex;

                Dem_Data_SetEventClassPriorityForOnRetrieval( EventStrgIndex, TmpRecordNumberForOnRetrievalPtr );
                Dem_Data_SetEventStatusPriorityForOnRetrieval( EventStrgIndex, TmpRecordNumberForOnRetrievalPtr );
                Dem_Data_SetOccurrenceOrderForOnRetrieval( FreezeFrameRecordTrigger, &faultRecord, TmpRecordNumberForOnRetrievalPtr );
            }
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Data_SetEventClassPriorityForOnRetrieval             */
/* Description   | Sets the EventClassPriority of TmpRecordNumberForOnRetr- */
/*               | ieval corresponding to the EventStrgIndex.               */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [out] TmpRecordNumberForOnRetrievalPtr :                 */
/*               |        TmpRecordNumberForOnRetrieval pointer.            */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_SetEventClassPriorityForOnRetrieval
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,                /* [PRMCHK:CALLER] */
    P2VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC, AUTOMATIC ) TmpRecordNumberForOnRetrievalPtr
)
{
    VAR( Dem_DTCSeverityType, AUTOMATIC ) dtcClass;

    dtcClass = Dem_CfgInfoPm_GetDTCSeverityClass( EventStrgIndex );             /* [GUDCHK:CALLER]EventStrgIndex */
    if( dtcClass == DEM_DTC_CLASS_1 )
    {
        TmpRecordNumberForOnRetrievalPtr->EventClassPriority = DEM_EVENTCLASS_PRIORITY_CLASS_A;
    }
    else if( dtcClass == DEM_DTC_CLASS_2 )
    {
        TmpRecordNumberForOnRetrievalPtr->EventClassPriority = DEM_EVENTCLASS_PRIORITY_CLASS_B1;
    }
    else if( dtcClass == DEM_DTC_CLASS_3 )
    {
        TmpRecordNumberForOnRetrievalPtr->EventClassPriority = DEM_EVENTCLASS_PRIORITY_CLASS_B2;
    }
    else if( dtcClass == DEM_DTC_CLASS_4 )
    {
        TmpRecordNumberForOnRetrievalPtr->EventClassPriority = DEM_EVENTCLASS_PRIORITY_CLASS_C;
    }
    else    /* DEM_SEVERITY_NO_SEVERITY or DEM_DTC_CLASS_0 */
    {
        TmpRecordNumberForOnRetrievalPtr->EventClassPriority = DEM_EVENTCLASS_PRIORITY_CLASS_NONE;
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Data_SetEventStatusPriorityForOnRetrieval            */
/* Description   | Sets the EventStatusPriority of TmpRecordNumberForOnRet- */
/*               | rieval corresponding to the EventStrgIndex.              */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [out] TmpRecordNumberForOnRetrievalPtr :                 */
/*               |        TmpRecordNumberForOnRetrieval pointer.            */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_SetEventStatusPriorityForOnRetrieval
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC, AUTOMATIC ) TmpRecordNumberForOnRetrievalPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetER;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) udsStatusOfDTC;

    resultOfGetER = Dem_DataMngC_GetER_StatusOfDTC( EventStrgIndex, &udsStatusOfDTC );
    if( resultOfGetER == DEM_IRT_OK )
    {
        if( DEM_UDS_STATUS_CDTC == ( udsStatusOfDTC & DEM_UDS_STATUS_CDTC ) )
        {
            TmpRecordNumberForOnRetrievalPtr->EventStatusPriority = DEM_EVENTSTATUS_PRIORITY_CONFIRMED;
        }
        else if( DEM_UDS_STATUS_PDTC == ( udsStatusOfDTC & DEM_UDS_STATUS_PDTC ) )
        {
            TmpRecordNumberForOnRetrievalPtr->EventStatusPriority = DEM_EVENTSTATUS_PRIORITY_POTENTIAL;
        }
        else    /* No Fault */
        {
            TmpRecordNumberForOnRetrievalPtr->EventStatusPriority = DEM_EVENTSTATUS_PRIORITY_NO_FAULT;
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Data_SetOccurrenceOrderForOnRetrieval                */
/* Description   | Sets the OccurrenceOrder of TmpRecordNumberForOnRetriev- */
/*               | al corresponding to the ConfirmedOccurrenceOrder or Occ- */
/*               | urrenceOrder of FaultRecordPtr branched by the FreezeFr- */
/*               | ameRecordTrigger.                                        */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameRecordTrigger :                          */
/*               |        The DemFreezeFrameRecordTrigger.                  */
/*               | [in] FaultRecordPtr :                                    */
/*               |        The pointer of FaultRecord.                       */
/*               | [out] TmpRecordNumberForOnRetrievalPtr :                 */
/*               |        TmpRecordNumberForOnRetrieval pointer.            */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_SetOccurrenceOrderForOnRetrieval
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC, AUTOMATIC ) TmpRecordNumberForOnRetrievalPtr
)
{
    if( FreezeFrameRecordTrigger == DEM_TRIGGER_ON_CONFIRMED )
    {
        TmpRecordNumberForOnRetrievalPtr->OccurrenceOrder = FaultRecordPtr->ConfirmedOccurrenceOrder;
    }
    else if( FreezeFrameRecordTrigger == DEM_TRIGGER_ON_PENDING )
    {
        TmpRecordNumberForOnRetrievalPtr->OccurrenceOrder = FaultRecordPtr->OccurrenceOrder;
    }
    else    /* Illegal trigger */
    {
        TmpRecordNumberForOnRetrievalPtr->OccurrenceOrder = DEM_FAIL_OCCURRENCE_NUM_INVALID;
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Data_JudgePriorityOfTmpRecordNumberForOnRetrieval    */
/* Description   | Judges priority of the BaseTmpRecordNumberForOnRetrieva- */
/*               | lPtr and the TargetTmpRecordNumberForOnRetrievalPtr.     */
/* Preconditions |                                                          */
/* Parameters    | [in/out] BaseTmpRecordNumberForOnRetrievalPtr            */
/*               |        The event ID for retrieving.                      */
/*               | [in] TargetTmpRecordNumberForOnRetrievalPtr :            */
/*               |        The index to array of FreezeFrameRecordClassRef.  */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_JudgePriorityOfTmpRecordNumberForOnRetrieval
(
    P2VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC, AUTOMATIC ) BaseTmpRecordNumberForOnRetrievalPtr,
    P2VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC, AUTOMATIC ) TargetTmpRecordNumberForOnRetrievalPtr
)
{
    if( BaseTmpRecordNumberForOnRetrievalPtr->EventClassPriority > TargetTmpRecordNumberForOnRetrievalPtr->EventClassPriority )
    {
        /* In case the target EventClass priority is higher than the base's one. */

        /* Transfers the contents of TmpRecordNumberForOnRetrieval target to base. */
        Dem_Data_TransferTmpRecordNumberForOnRetrieval( BaseTmpRecordNumberForOnRetrievalPtr, TargetTmpRecordNumberForOnRetrievalPtr );
    }
    else if( BaseTmpRecordNumberForOnRetrievalPtr->EventClassPriority == TargetTmpRecordNumberForOnRetrievalPtr->EventClassPriority )
    {
        /* In case the target EventClass priority is equal to the base's one. */

        if( BaseTmpRecordNumberForOnRetrievalPtr->EventStatusPriority > TargetTmpRecordNumberForOnRetrievalPtr->EventStatusPriority )
        {
            /* In case the target EventStatus priority is higher than the base's one. */

            /* Transfers the contents of TmpRecordNumberForOnRetrieval target to base. */
            Dem_Data_TransferTmpRecordNumberForOnRetrieval( BaseTmpRecordNumberForOnRetrievalPtr, TargetTmpRecordNumberForOnRetrievalPtr );
        }
        else if( BaseTmpRecordNumberForOnRetrievalPtr->EventStatusPriority == TargetTmpRecordNumberForOnRetrievalPtr->EventStatusPriority )
        {
            /* In case the target EventStatus priority is equal to the base's one. */

            if( BaseTmpRecordNumberForOnRetrievalPtr->OccurrenceOrder > TargetTmpRecordNumberForOnRetrievalPtr->OccurrenceOrder )
            {
                /* In case the target OccurrenceOrder is older than the base's one. */

                /* Transfers the contents of TmpRecordNumberForOnRetrieval target to base. */
                Dem_Data_TransferTmpRecordNumberForOnRetrieval( BaseTmpRecordNumberForOnRetrievalPtr, TargetTmpRecordNumberForOnRetrievalPtr );
            }
        }
        else
        {
            /* no processing. */
        }
    }
    else
    {
        /* no processing. */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Data_TransferTmpRecordNumberForOnRetrieval           */
/* Description   | Transfers the contents from the TargetTmpRecordNumberFo- */
/*               | rOnRetrievalPtr to the BaseTmpRecordNumberForOnRetrieva- */
/*               | lPtr.                                                    */
/* Preconditions |                                                          */
/* Parameters    | [out] BaseTmpRecordNumberForOnRetrievalPtr               */
/*               |        The event ID for retrieving.                      */
/*               | [in] TargetTmpRecordNumberForOnRetrievalPtr :            */
/*               |        The index to array of FreezeFrameRecordClassRef.  */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_TransferTmpRecordNumberForOnRetrieval
(
    P2VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC, AUTOMATIC ) BaseTmpRecordNumberForOnRetrievalPtr,
    P2VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC, AUTOMATIC ) TargetTmpRecordNumberForOnRetrievalPtr
)
{
    BaseTmpRecordNumberForOnRetrievalPtr->OccurrenceOrder = TargetTmpRecordNumberForOnRetrievalPtr->OccurrenceOrder;
    BaseTmpRecordNumberForOnRetrievalPtr->EventStrgIndex = TargetTmpRecordNumberForOnRetrievalPtr->EventStrgIndex;
    BaseTmpRecordNumberForOnRetrievalPtr->FreezeFrameIndex = TargetTmpRecordNumberForOnRetrievalPtr->FreezeFrameIndex;
    BaseTmpRecordNumberForOnRetrievalPtr->EventClassPriority = TargetTmpRecordNumberForOnRetrievalPtr->EventClassPriority;
    BaseTmpRecordNumberForOnRetrievalPtr->EventStatusPriority = TargetTmpRecordNumberForOnRetrievalPtr->EventStatusPriority;

    return;
}

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_GetDisabledTimeSeriesFreezeFrameListIndex       */
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
/*               {        for trigger FFD.                                  */
/*               | [out] FFDIndexListStPtr :                                */
/*               |        Dem_TmpDisabledRecord.FFDIndexListSt pointer.     */
/*               | [out] EventStrgIndexPtr :                                */
/*               |        The regular EventStrgIndex.                       */
/* Return Value  | Dem_u16_TSFFListIndexType                                */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u16_TSFFListIndexType, DEM_CODE ) Dem_Data_GetDisabledTimeSeriesFreezeFrameListIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) TSFFRecClassRefIndex,         /* [PRMCHK:CALLER] */
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) TSFFRecordTrigger,
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) NumberOfSaveRecordForTriggerFFD,
    P2VAR( Dem_FaultRecordPartsFFDIndexListStType, AUTOMATIC, DEM_VAR_NO_INIT ) FFDIndexListStPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
)
{
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) freezeFrameClassRef;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) freezeframeRecNumClassRef;
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecNumClassPtr;

    tsFFListIndex = DEM_TSFFLISTINDEX_INVALID;
    eventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;

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
            tsFFListIndex = Dem_Data_GetTSFFListIndexByEventStrgIndex( eventStrgIndex, TSFFRecClassRefIndex );  /* [GUD]eventStrgIndex */
        }
    }

    FFDIndexListStPtr->TimeSeriesFreezeFrameListIndex[ TSFFRecClassRefIndex ] = tsFFListIndex;      /* [GUDCHK:CALLER]TSFFRecClassRefIndex */

    ( *EventStrgIndexPtr ) = eventStrgIndex;

    return tsFFListIndex;
}

/****************************************************************************/
/* Function Name | Dem_Data_SearchNonObdEventStrgIndexByTSFFRTrigger        */
/* Description   | Returns the EventStrgIndex which has the same trigger w- */
/*               | ith DEM_FFD_TYPE_NONOBDFFD.                              */
/* Preconditions |                                                          */
/*               | [in] TSFFRecordTrigger :                                 */
/*               |        The DemFreezeFrameRecordTrigger.(for TSFFD)       */
/*               | [in] NumberOfSaveRecordForTriggerFFD :                   */
/*               |        The number of saved Dem_TmpDisabledRecord array   */
/*               {        for trigger FFD.                                  */
/*               | [in] FreezeFrameRecNumClassPtr :                         */
/*               |        The porint of DemFreezeFrameRecNumClass of the d- */
/*               |        elegate event.                                    */
/* Return Value  | Dem_u16_EventStrgIndexType                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_Data_SearchNonObdEventStrgIndexByTSFFRTrigger
(
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) TSFFRecordTrigger,
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) NumberOfSaveRecordForTriggerFFD,
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameRecNumClassPtr
)
{
    VAR( Dem_u08_FreezeFrameDataType, AUTOMATIC ) freezeFrameDataType;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfCheck;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) tmpRecordNumber;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) ffRecNumStoredIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) retEventStrgIndex;

    retEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;

    for( ffRecNumStoredIndex = ( Dem_u16_FFRecNumStoredIndexType )0U; ffRecNumStoredIndex < NumberOfSaveRecordForTriggerFFD; ffRecNumStoredIndex++ )    /* [GUD:for] ffRecNumStoredIndex */
    {
        freezeFrameDataType = Dem_TmpRecordNumberByDTC[ ffRecNumStoredIndex ].FreezeFrameDataType;                                                      /* [GUD] ffRecNumStoredIndex */
        if( freezeFrameDataType == DEM_FFD_TYPE_NONOBDFFD )                                                                                             /* [GUD:if] ffRecNumStoredIndex */
        {
            tmpRecordNumber = Dem_TmpRecordNumberByDTC[ ffRecNumStoredIndex ].RecordNumber;                                                             /* [GUD] ffRecNumStoredIndex */

            resultOfCheck = Dem_Data_CheckFreezeFrameRecNumClass( tmpRecordNumber, TSFFRecordTrigger, FreezeFrameRecNumClassPtr );
            if( resultOfCheck == DEM_IRT_OK )
            {
                retEventStrgIndex = Dem_TmpRecordNumberByDTC[ ffRecNumStoredIndex ].EventStrgIndex;                                                     /* [GUD] ffRecNumStoredIndex */
                break;
            }
        }
    }

    return retEventStrgIndex;
}

/****************************************************************************/
/* Function Name | Dem_Data_CheckFreezeFrameRecNumClass                     */
/* Description   | Checks the DemFreezeFrameRecNumClass which has the same  */
/*               | record number and trigger.                               */
/* Preconditions |                                                          */
/* Parameters    | [in] TmpRecordNumber :                                   */
/*               |        The record number which in latched Dem_TmpRecord- */
/*               |        NumberByDTC[] with DEM_FFD_TYPE_NONOBDFFD.        */
/*               | [in] TSFFRecordTrigger :                                 */
/*               |        The DemFreezeFrameRecordTrigger.(for TSFFD)       */
/*               | [in] FreezeFrameRecNumClassPtr :                         */
/*               |        The porint of DemFreezeFrameRecNumClass of the d- */
/*               |        elegate event.                                    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_CheckFreezeFrameRecNumClass
(
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) TmpRecordNumber,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) TSFFRecordTrigger,
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameRecNumClassPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) ffrRecordClassConfigureNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordClassRefIndex;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) freezeFrameRecordClassIndex;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) freezeFrameRecordNumber;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) freezeFrameRecordTrigger;
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecordClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecordClassPtr;

    retVal = DEM_IRT_NG;

    Dem_CfgInfoPm_GetNumOfFreezeFrameRecordClass( &ffrRecordClassConfigureNum, &nonOBDFFRClassPerDTCMaxNum );

    for( freezeFrameRecordClassRefIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordClassRefIndex < nonOBDFFRClassPerDTCMaxNum; freezeFrameRecordClassRefIndex++ )  /* [GUD:for] freezeFrameRecordClassRefIndex */
    {
        /* Holds the DemFreezeFrameRecordIndex pointed to */
        /* by the DemFreezeFrameRecordClassRef Index of the held FreezeFrameRecNumClass table. */
        freezeFrameRecordClassIndex = FreezeFrameRecNumClassPtr->DemFreezeFrameRecordClassRef[freezeFrameRecordClassRefIndex];  /* [GUD] freezeFrameRecordClassRefIndex */
        if( freezeFrameRecordClassIndex < ffrRecordClassConfigureNum )                                                          /* [GUD:if] freezeFrameRecordClassIndex */
        {
            freezeFrameRecordClassPtr = &Dem_FreezeFrameRecordClassTable[freezeFrameRecordClassIndex];                          /* [GUD] freezeFrameRecordClassIndex *//* [GUD:CFG:IF_GUARDED: freezeFrameRecordClassIndex ]freezeFrameRecordClassPtr */
            freezeFrameRecordNumber = freezeFrameRecordClassPtr->DemFreezeFrameRecordNumber;                                    /* [GUD] freezeFrameRecordClassPtr */
            if( freezeFrameRecordNumber == TmpRecordNumber )
            {
                freezeFrameRecordTrigger = freezeFrameRecordClassPtr->DemFreezeFrameRecordTrigger;                              /* [GUD] freezeFrameRecordClassPtr */
                if( freezeFrameRecordTrigger == TSFFRecordTrigger )
                {
                    retVal = DEM_IRT_OK;
                    break;
                }
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Data_GetTSFFListIndexByEventStrgIndex                */
/* Description   | Gets the TSFFListIndex corresponding to the specified E- */
/*               | ventStrgIndex.                                           */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [in] TSFFRecClassRefIndex :                              */
/*               |        The reference index for TimeSeriesFreezeFrameLis- */
/*               |        tIndex of a fault-record.                         */
/* Return Value  | Dem_u16_TSFFListIndexType                                */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( Dem_u16_TSFFListIndexType, DEM_CODE ) Dem_Data_GetTSFFListIndexByEventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) TSFFRecClassRefIndex      /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetER;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFR;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListIndex;
    VAR( Dem_FaultRecordPartsFFDIndexListStType, AUTOMATIC ) ffdIndexListSt;

    tsFFListIndex = DEM_TSFFLISTINDEX_INVALID;

    resultOfGetER = Dem_DataMngC_GetER_FaultIndex( EventStrgIndex, &faultIndex );
    if( resultOfGetER == DEM_IRT_OK )
    {
        resultOfGetFR = Dem_DataMngC_GetFR_FFDIndexListSt( faultIndex, &ffdIndexListSt );
        if( resultOfGetFR == DEM_IRT_OK )
        {
            tsFFListIndex = ffdIndexListSt.TimeSeriesFreezeFrameListIndex[ TSFFRecClassRefIndex ];      /* [GUDCHK:CALLER]TSFFRecClassRefIndex */
        }
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
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
