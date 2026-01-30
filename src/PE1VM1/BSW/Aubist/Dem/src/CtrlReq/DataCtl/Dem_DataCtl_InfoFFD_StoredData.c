/* Dem_DataCtl_InfoFFD_StoredData_c(v5-10-0)                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_InfoFFD_StoredData/CODE                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#if ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )

#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_DataCtl_TSFFD.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "../../../inc/Dem_Rc_DataMng.h"

#include "Dem_DataCtl_local.h"

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
/* Function Name | Dem_Data_GetConfirmedTriggerNonOBDFFDIndex               */
/* Description   | Get the index of confirmed trigger non Obd FFD index     */
/* Preconditions | Only one if confirmed trigger non Obd FFD is configured  */
/* Parameters    | [in] FaultIndex : Dem_FaultRecordList array's index      */
/*               | [out] FreezeFrameClassRefPtr : FreezeFrameClassRef       */
/* Return Value  | Dem_u08_FFDIndexType                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-10-0     | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_Data_GetConfirmedTriggerNonOBDFFDIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u16_FFClassIndexType, AUTOMATIC, AUTOMATIC ) FreezeFrameClassRefPtr
)
{
    VAR( Dem_FaultRecordType, AUTOMATIC ) faultRecord;
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecNumClassPtr;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) freezeFrameRecNumClassRef;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultRec;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) confirmedTriggerNonOBDFFDIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) ffListIndex;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) ffrRecordClassConfigureNum;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) freezeFrameRecordClassIndex;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) freezeFrameRecordTrigger;

    confirmedTriggerNonOBDFFDIndex = DEM_FFRECINDEX_INITIAL;

    freezeFrameRecNumClassRef = DEM_FFRECNUMCLASSINDEX_INVALID;

    resultOfGetFaultRec = Dem_DataMngC_GetFaultRecord( FaultIndex, &faultRecord );
    if( resultOfGetFaultRec == DEM_IRT_OK )
    {
        eventStorageNum = Dem_PrimaryMemEventStorageNum;
        if( faultRecord.EventStrgIndex < eventStorageNum )
        {
            Dem_CfgInfoPm_GetFreezeFrameAndRecNumClass( faultRecord.EventStrgIndex, FreezeFrameClassRefPtr, &freezeFrameRecNumClassRef);    /* [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] freezeFrameClassRef *//* [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] freezeframeRecNumClassRef */
        }
    }

    if( freezeFrameRecNumClassRef != DEM_FFRECNUMCLASSINDEX_INVALID )                                   /* [GUD:if] freezeFrameRecNumClassRef */
    {
        freezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[freezeFrameRecNumClassRef];        /* [GUD] freezeFrameRecNumClassRef */

        nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;
        nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;
        ffrRecordClassConfigureNum  = Dem_FFRRecordClassConfigureNum;

        for( ffListIndex = (Dem_u08_FFListIndexType)0U; ffListIndex < nonOBDFFRClassPerDTCMaxNum; ffListIndex++ )       /* [GUD:for] ffListIndex */
        {
            if( faultRecord.RecordNumberIndex[ffListIndex] < nonObdFFDRecordNum )                                       /* [GUD] ffListIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / ffListIndex */
            {
                freezeFrameRecordClassIndex = freezeFrameRecNumClassPtr->DemFreezeFrameRecordClassRef[ffListIndex];     /* [GUD] ffListIndex *//* [ARYCHK] DEM_FF_RECORD_CLASS_REF_MAX_NUM / 1 / ffListIndex */
                if( freezeFrameRecordClassIndex < ffrRecordClassConfigureNum )                                          /* [GUD:if] freezeFrameRecordClassIndex */
                {
                    freezeFrameRecordTrigger =  Dem_CfgInfoPm_GetFreezeFrameRecordTriggerType( freezeFrameRecordClassIndex );   /* [GUD] freezeFrameRecordClassIndex */
                    if( freezeFrameRecordTrigger == DEM_TRIGGER_ON_CONFIRMED )
                    {
                        confirmedTriggerNonOBDFFDIndex = faultRecord.RecordNumberIndex[ffListIndex];                    /* [GUD] ffListIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / ffListIndex */
                        break;
                    }
                }
            }
        }
    }

    return confirmedTriggerNonOBDFFDIndex;
}

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_GetConfirmedTriggerBeforeTSFFListIndexAndInfo   */
/* Description   | Get the index of confirmed trigger before TSFFListIndex -*/
/*               | and number of before TSFFD                               */
/* Preconditions | Only one if confirmed trigger TSFFD is configured        */
/* Parameters    | [in] FaultIndex : Dem_FaultRecordList array's index      */
/* Parameters    | [out] NumberOfBeforeTriggeredRecordPtr :                 */
/*               |                              Number of before TSFFD      */
/*               | [out] FreezeFrameClassRefPtr : FreezeFrameClassRef       */
/* Return Value  | Dem_u16_TSFFListIndexType                                */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/*   v5-8-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u16_TSFFListIndexType, DEM_CODE ) Dem_Data_GetConfirmedTriggerBeforeTSFFListIndexAndInfo
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) NumberOfBeforeTriggeredRecordPtr,
    P2VAR( Dem_u16_FFClassIndexType, AUTOMATIC, AUTOMATIC ) FreezeFrameClassRefPtr
)
{
    VAR( Dem_FaultRecordType, AUTOMATIC ) faultRecord;
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) dtcAttributePtr;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) confirmedTriggerTsffListIndex;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsFFRecClassRef;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsFFRecIndex;
    VAR( Dem_u16_SmpTSFFCPerTSFFIndexType, AUTOMATIC ) samplingFFClassRef;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultRec;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsFFRecClassRefIndex;
    VAR( Dem_u08_TSFFClassIndexType, AUTOMATIC ) tsFFClassRef;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsffRecordClassNumPerDTCMaxNum;
    VAR( Dem_u08_FFStoredStatusType, AUTOMATIC ) recordStatus;

    confirmedTriggerTsffListIndex = DEM_INVALID_VACANT_TSFFLIST_INDEX;
    tsffTotalDTCNum = Dem_TSFFTotalDTCNum;

    resultOfGetFaultRec = Dem_DataMngC_GetFaultRecord( FaultIndex, &faultRecord );
    if( resultOfGetFaultRec == DEM_IRT_OK )
    {
        eventStorageNum = Dem_PrimaryMemEventStorageNum;
        if( faultRecord.EventStrgIndex < eventStorageNum )              /* [GUD:if]faultRecord.EventStrgIndex */
        {
            dtcAttributePtr =   Dem_CfgInfoPm_GetDTCAttrTablePtr_TSFF( faultRecord.EventStrgIndex );    /* [GUD:RET:Not NULL_PTR]dtcAttributePtr */

            if ( dtcAttributePtr != NULL_PTR )                                              /* [GUD:if]dtcAttributePtr */
            {
                tsffRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;
                for( tsFFRecClassRefIndex = (Dem_u08_TSFFListPerDTCIndexType)0U; tsFFRecClassRefIndex < tsffRecordClassNumPerDTCMaxNum; tsFFRecClassRefIndex++ )    /* [GUD:for]tsFFRecClassRefIndex */
                {
                    if( faultRecord.TimeSeriesFreezeFrameListIndex[tsFFRecClassRefIndex] < tsffTotalDTCNum )                                                        /* [GUD]tsFFRecClassRefIndex *//* [ARYCHK] DEM_TSFF_RECORD_CLASS_NUM_PER_DTC_MAX_NUM / 1 / tsFFRecClassRefIndex */
                    {
                        tsFFRecClassRef = dtcAttributePtr->DemTimeSeriesFreezeFrameRecordClassRef[tsFFRecClassRefIndex];                                            /* [GUD]dtcAttributePtr *//* [GUD]tsFFRecClassRefIndex *//* [ARYCHK] DEM_TSFF_RECORD_CLASS_NUM_PER_DTC_MAX_NUM / 1 / tsFFRecClassRefIndex */
                        if( tsFFRecClassRef != DEM_TSFF_RECORD_CLASS_REF_INVALID )                                                                                  /* [GUD:if]tsFFRecClassRef */
                        {
                            if( Dem_TSFFRecordClassTable[tsFFRecClassRef].DemTimeSeriesFreezeFrameTrigger == DEM_TRIGGER_ON_CONFIRMED )                             /* [GUD]tsFFRecClassRef */
                            {
                                confirmedTriggerTsffListIndex = faultRecord.TimeSeriesFreezeFrameListIndex[tsFFRecClassRefIndex];                                   /* [GUD:if]tsFFRecClassRefIndex *//* [ARYCHK] DEM_TSFF_RECORD_CLASS_NUM_PER_DTC_MAX_NUM / 1 / tsFFRecClassRefIndex */
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    if( confirmedTriggerTsffListIndex < tsffTotalDTCNum )                                                                                                       /* [GUD:if]confirmedTriggerTsffListIndex */
    {
        tsFFClassRef = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemTimeSeriesFreezeFrameClassRef;                                                              /* [GUD]tsFFRecClassRef *//* [GUD:CFG:IF_GUARDED: tsFFRecClassRef ]tsFFClassRef */
        *NumberOfBeforeTriggeredRecordPtr = Dem_TSFFClassTable[tsFFClassRef].DemNumberOfBeforeTriggeredRecord;                                                  /* [GUD]tsFFClassRef */
        if( (*NumberOfBeforeTriggeredRecordPtr) > ( Dem_u08_FFRecordNumberType )0U )
        {
            tsFFRecIndex = ( Dem_TimeSeriesFreezeFrameTable[confirmedTriggerTsffListIndex].DemStartIndex + ( (Dem_u16_TSFFDIndexType)(*NumberOfBeforeTriggeredRecordPtr) - (Dem_u16_TSFFDIndexType)1U ) );  /* [GUD]confirmedTriggerTsffListIndex */
            recordStatus = Dem_DataMngC_GetRecordStatusOfTimeSeriesFreezeFrameRecord( tsFFRecIndex );
            if( recordStatus == DEM_FFD_STORED )
            {
                samplingFFClassRef = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemSamplingFreezeFrameClassRef;                                                      /* [GUD]tsFFRecClassRef *//* [GUD:CFG:IF_GUARDED: tsFFRecClassRef ]samplingFFClassRef */
                *FreezeFrameClassRefPtr = Dem_TSFFClassTable[tsFFClassRef].Dem_SamplingFreezeFrameClass[samplingFFClassRef].DemFreezeFrameClassRef;                 /* [GUD]tsFFClassRef *//* [GUD]samplingFFClassRef */
            }
            else
            {
                confirmedTriggerTsffListIndex = DEM_INVALID_VACANT_TSFFLIST_INDEX;
            }
        }
        else
        {
            confirmedTriggerTsffListIndex = DEM_INVALID_VACANT_TSFFLIST_INDEX;
        }

    }

    return confirmedTriggerTsffListIndex;
}

#endif  /* (DEM_TSFF_PM_SUPPORT == STD_ON) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )     */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
