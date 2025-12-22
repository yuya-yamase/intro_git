/* Dem_DataCtl_SamplingFFD_c(v5-7-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_SamplingFFD/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_DataCtl.h"
#include "../../../inc/Dem_CmnLib_DataCtl_CaptureFreezeFrameClass.h"
#include "../../../inc/Dem_CmnLib_DataCtl_SamplingFFD.h"
#include "../../../inc/Dem_CmnLib_DataCtl_SamplingFFDAccess.h"
#include "../../../inc/Dem_CmnLib_DataCtl_TSFFD.h"
#include "../../../inc/Dem_Pm_TSFFD.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Rc_UdmMng.h"
#include "../../../inc/Dem_Rc_UdmMngTable.h"
#include "../../../inc/Dem_Udm_Data.h"

#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
#include <Dem_SIT_RangeCheck.h>
#endif  /* DEM_SIT_RANGE_CHECK */

#if ( DEM_TSFF_SUPPORT == STD_ON )

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

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

static FUNC( void, DEM_CODE ) Dem_Data_CaptureFreezeFrameClassToSample
(
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) SamplingFreezeFrameMemoryRef,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) SamplingFreezeFrameRecordIndex,
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameClassPtr
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_CaptureAfterTriggeredTSFF
(
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) SamplingFreezeFrameMemoryRef,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) SamplingFreezeFrameRecordIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameRecordIndex,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) OffsetOfTimeSeriesFreezeFrameTableIndexPerDTC,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) TimeSeriesFreezeFrameTrigger
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

VAR( Dem_SamplingFreezeFrameListType, DEM_VAR_NO_INIT ) Dem_SamplingFreezeFrameListRecordList[DEM_TSFF_SAMPLING_FF_CLASS_CONFIGURE_NUM];

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Data_SampleFreezeFrame                               */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] SamplingFreezeFrameTableRef :                       */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Sample Freeze Frame is success.      */
/*               |        DEM_IRT_NG : The range check of Sampling Freeze   */
/*               |        Frame Table Reference is failed.                  */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SampleFreezeFrame
(
    VAR( Dem_u16_SmpTSFFRecClassIndexType, AUTOMATIC ) SamplingFreezeFrameTableRef
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_TSFFClassIndexType, AUTOMATIC ) tsFFClassRef;
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) samplingFFMemoryRef;
    VAR( Dem_u16_SmpTSFFCPerTSFFIndexType, AUTOMATIC ) samplingFFClassRef;
    VAR( Dem_u16_SmpTSFFDIndexType, AUTOMATIC ) samplingFFRecIndex;
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) freezeFrameClassRef;
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameClassPtr;
    VAR( Dem_u16_SmpTSFFRecClassIndexType, AUTOMATIC ) tsffSamplingFFClassConfigureNum;

    tsffSamplingFFClassConfigureNum = Dem_TSFFSamplingFFClassConfigureNum;

    if( SamplingFreezeFrameTableRef >= tsffSamplingFFClassConfigureNum )            /* [GUD:if]SamplingFreezeFrameTableRef */
    {
        retVal = DEM_IRT_NG;
    }
    else
    {
        Dem_SamplingFreezeFrameListRecordList[SamplingFreezeFrameTableRef].CurrentIndex = Dem_SamplingFreezeFrameListRecordList[SamplingFreezeFrameTableRef].CurrentIndex + (Dem_u16_SmpTSFFDIndexType)1U;  /* [GUD]SamplingFreezeFrameTableRef */

        if( Dem_SamplingFreezeFrameListRecordList[SamplingFreezeFrameTableRef].CurrentIndex > Dem_SamplingFreezeFrameTable[SamplingFreezeFrameTableRef].DemEndIndex )                                       /* [GUD]SamplingFreezeFrameTableRef */
        {
            Dem_SamplingFreezeFrameListRecordList[SamplingFreezeFrameTableRef].CurrentIndex = Dem_SamplingFreezeFrameTable[SamplingFreezeFrameTableRef].DemStartIndex;                                      /* [GUD]SamplingFreezeFrameTableRef */
        }
        else
        {
            /* No process */
        }

        tsFFClassRef = Dem_SamplingFreezeFrameTable[SamplingFreezeFrameTableRef].DemTimeSeriesFreezeFrameClassRef;                      /* [GUD]SamplingFreezeFrameTableRef *//* [GUD:CFG:IF_GUARDED: SamplingFreezeFrameTableRef ]tsFFClassRef */

        samplingFFClassRef = Dem_SamplingFreezeFrameTable[SamplingFreezeFrameTableRef].DemSamplingFreezeFrameClassRef;                  /* [GUD]SamplingFreezeFrameTableRef *//* [GUD:CFG:IF_GUARDED: SamplingFreezeFrameTableRef ]samplingFFClassRef */

        freezeFrameClassRef = Dem_TSFFClassTable[tsFFClassRef].Dem_SamplingFreezeFrameClass[samplingFFClassRef].DemFreezeFrameClassRef; /* [GUD]tsFFClassRef *//* [GUD]samplingFFClassRef *//* [GUD:CFG:IF_GUARDED: tsFFClassRef,samplingFFClassRef ]freezeFrameClassRef */

        freezeFrameClassPtr = &Dem_FreezeFrameClassTable[freezeFrameClassRef];                                                          /* [GUD]freezeFrameClassRef */

        samplingFFRecIndex = Dem_SamplingFreezeFrameListRecordList[SamplingFreezeFrameTableRef].CurrentIndex;                           /* [GUD]SamplingFreezeFrameTableRef */

        samplingFFMemoryRef = Dem_SamplingFreezeFrameTable[SamplingFreezeFrameTableRef].DemSamplingFreezeFrameMemoryRef;                /* [GUD]SamplingFreezeFrameTableRef */

        Dem_Data_CaptureFreezeFrameClassToSample( samplingFFMemoryRef, samplingFFRecIndex, freezeFrameClassPtr );

        retVal = DEM_IRT_OK;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Data_CaptureAfterTriggeredTimeSeriesFreezeFrame      */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] TimeSeriesFreezeFrameRecordClassRef :               */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_CaptureAfterTriggeredTimeSeriesFreezeFrame
(
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) TimeSeriesFreezeFrameRecordClassRef
)
{
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) numberOfStoredAfterTriggeredRecord;
    VAR( Dem_u08_TSFFClassIndexType, AUTOMATIC ) tsFFClassRef;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) numberOfBeforeTriggeredRecord;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) numberOfAfterTriggeredRecord;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) numberOfTSFFPerDTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfCapture;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) tsFFTrigger;
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) samplingFFMemoryRef;
    VAR( Dem_u16_SmpTSFFRecClassIndexType, AUTOMATIC ) samplingFFRef;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFTableIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFTableIndex_Start;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFTableIndex_End;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFTableIndexPerDTC;
    VAR( Dem_u16_SmpTSFFDIndexType, AUTOMATIC ) samplingFFRecIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsFFRecIndex;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsffRecordClassConfigureNum;

    tsffRecordClassConfigureNum = Dem_TSFFRecordClassConfigureNum;

    if( TimeSeriesFreezeFrameRecordClassRef < tsffRecordClassConfigureNum )                                                 /* [GUD:if]TimeSeriesFreezeFrameRecordClassRef */
    {
        samplingFFRef = Dem_SamplingFreezeFrameBindTable[TimeSeriesFreezeFrameRecordClassRef].DemSamplingFreezeFrameRef;    /* [GUD]TimeSeriesFreezeFrameRecordClassRef *//* [GUD:CFG:IF_GUARDED: TimeSeriesFreezeFrameRecordClassRef ]samplingFFRef */
        samplingFFRecIndex = Dem_SamplingFreezeFrameListRecordList[samplingFFRef].CurrentIndex;                             /* [GUD]samplingFFRef */
        samplingFFMemoryRef = Dem_SamplingFreezeFrameTable[samplingFFRef].DemSamplingFreezeFrameMemoryRef;                  /* [GUD]samplingFFRef */

        tsFFClassRef = Dem_TSFFRecordClassTable[TimeSeriesFreezeFrameRecordClassRef].DemTimeSeriesFreezeFrameClassRef;      /* [GUD]TimeSeriesFreezeFrameRecordClassRef *//* [GUD:CFG:IF_GUARDED: TimeSeriesFreezeFrameRecordClassRef ]tsFFClassRef */
        numberOfTSFFPerDTC = Dem_TSFFClassTable[tsFFClassRef].DemNumberOfTimeSeriesFreezeFramePerDTC;                       /* [GUD]tsFFClassRef */
        tsFFTableIndexPerDTC = (Dem_u16_TSFFListIndexType)0U;

        tsFFTableIndex_Start    =   Dem_TimeSeriesFreezeFrameBindTable[TimeSeriesFreezeFrameRecordClassRef].DemStartIndex;  /* [GUD]TimeSeriesFreezeFrameRecordClassRef */
        tsFFTableIndex_End      =   Dem_TimeSeriesFreezeFrameBindTable[TimeSeriesFreezeFrameRecordClassRef].DemEndIndex;    /* [GUD]TimeSeriesFreezeFrameRecordClassRef */
        for( tsFFTableIndex = tsFFTableIndex_Start; tsFFTableIndex <= tsFFTableIndex_End; tsFFTableIndex++ )                                                            /* [GUD:for]tsFFTableIndex */
        {
            if( Dem_TimeSeriesFreezeFrameListRecordList[tsFFTableIndex].FaultIndex != DEM_FAULTINDEX_INITIAL )                                                          /* [GUD]tsFFTableIndex */
            {
                numberOfStoredAfterTriggeredRecord = Dem_TimeSeriesFreezeFrameListRecordList[tsFFTableIndex].NumberOfStoredAfterTriggeredRecord;                        /* [GUD]tsFFTableIndex */

                numberOfAfterTriggeredRecord = Dem_TSFFClassTable[tsFFClassRef].DemNumberOfAfterTriggeredRecord;                                                        /* [GUD]tsFFClassRef */

                if( numberOfStoredAfterTriggeredRecord < numberOfAfterTriggeredRecord )
                {
                    numberOfBeforeTriggeredRecord = Dem_TSFFClassTable[tsFFClassRef].DemNumberOfBeforeTriggeredRecord;                                                  /* [GUD]tsFFClassRef */

                    tsFFRecIndex = Dem_TimeSeriesFreezeFrameTable[tsFFTableIndex].DemStartIndex + numberOfBeforeTriggeredRecord + numberOfStoredAfterTriggeredRecord;   /* [GUD]tsFFTableIndex */

                    tsFFTrigger = Dem_TSFFRecordClassTable[TimeSeriesFreezeFrameRecordClassRef].DemTimeSeriesFreezeFrameTrigger;                                        /* [GUD]TimeSeriesFreezeFrameRecordClassRef */

                    faultIndex = Dem_TimeSeriesFreezeFrameListRecordList[tsFFTableIndex].FaultIndex;                                                                    /* [GUD]tsFFTableIndex */

                    resultOfCapture = Dem_Data_CaptureAfterTriggeredTSFF( samplingFFMemoryRef, samplingFFRecIndex, faultIndex, tsFFRecIndex, (Dem_u08_NumOfTSFFType)tsFFTableIndexPerDTC, tsFFTrigger );    /* [GUD]samplingFFRef */
                    if( resultOfCapture == DEM_IRT_OK )
                    {
                        Dem_TimeSeriesFreezeFrameListRecordList[tsFFTableIndex].NumberOfStoredAfterTriggeredRecord = Dem_TimeSeriesFreezeFrameListRecordList[tsFFTableIndex].NumberOfStoredAfterTriggeredRecord + (Dem_u08_NumOfTSFFType)1U;    /* [GUD]tsFFTableIndex */
                    }
                }
            }

            tsFFTableIndexPerDTC = tsFFTableIndexPerDTC + (Dem_u16_TSFFListIndexType)1U;
            if( tsFFTableIndexPerDTC >= numberOfTSFFPerDTC )
            {
                tsFFTableIndexPerDTC = (Dem_u16_TSFFListIndexType)0U;
            }
        }
    }

    return ;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dem_Data_CaptureFreezeFrameClassToSample                 */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] SamplingFreezeFrameMemoryRef                        */
/*               |        The index of the sampling freeze frame record ta- */
/*               |        ble.                                              */
/*               | [in] SamplingFreezeFrameRecordIndex :                    */
/*               |        The index of the sampling freeze frame record li- */
/*               |        st.                                               */
/*               | [in] FreezeFrameClassPtr :                               */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_CaptureFreezeFrameClassToSample
(
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) SamplingFreezeFrameMemoryRef,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) SamplingFreezeFrameRecordIndex,
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameClassPtr
)
{
    VAR( Dem_SamplingFreezeFrameRecordPosType, AUTOMATIC ) samplingFFRPos;
    P2VAR( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) samplingFreezeFrameRecordDataPtr;


    samplingFreezeFrameRecordDataPtr = Dem_Data_GetSamplingFreezeFrameRecordDataPtr( SamplingFreezeFrameMemoryRef, SamplingFreezeFrameRecordIndex );    /* [GUD:RET:Not NULL_PTR ] SamplingFreezeFrameMemoryRef */
    if( samplingFreezeFrameRecordDataPtr != NULL_PTR )
    {
        Dem_Data_GetSamplingFreezeFrameRecordPosition( SamplingFreezeFrameMemoryRef, &samplingFFRPos );     /* [GUD]SamplingFreezeFrameMemoryRef *//* [GUD:OUT:IF_GUARDED: SamplingFreezeFrameMemoryRef ] &samplingFFRPos */

#ifndef DEM_SIT_RANGE_CHECK
        Dem_Data_CaptureFreezeFrameClass( DEM_EVENTCTRLINDEX_INVALID, FreezeFrameClassPtr, &samplingFreezeFrameRecordDataPtr[samplingFFRPos.DataStart], DEM_MONITORDATA_TSFFD );    /* [GUD]samplingFFRPos.DataStart *//* [ARYCHK] (Dem_SamplingFreezeFrameRecordTable[SamplingFreezeFrameMemoryRef].DemFFDStoredFormatSize) / 1 / samplingFFRPos.DataStart */
#else   /* DEM_SIT_RANGE_CHECK */
        Dem_Data_CaptureFreezeFrameClass( (Dem_SamplingFreezeFrameRecordTable[SamplingFreezeFrameMemoryRef].DemFFDMaxLength), DEM_EVENTCTRLINDEX_INVALID, FreezeFrameClassPtr, &samplingFreezeFrameRecordDataPtr[samplingFFRPos.DataStart], DEM_MONITORDATA_TSFFD );    /* [GUD]samplingFFRPos.DataStart *//* [ARYCHK] (Dem_SamplingFreezeFrameRecordTable[SamplingFreezeFrameMemoryRef].DemFFDStoredFormatSize) / 1 / samplingFFRPos.DataStart */
#endif  /* DEM_SIT_RANGE_CHECK */

        samplingFreezeFrameRecordDataPtr[samplingFFRPos.RecordStatus] = DEM_FFD_STORED;                     /* [GUD]samplingFFRPos.RecordStatus *//* [ARYCHK] (Dem_SamplingFreezeFrameRecordTable[SamplingFreezeFrameMemoryRef].DemFFDStoredFormatSize) / 1 / samplingFFRPos.RecordStatus */

    }

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Data_CaptureAfterTriggeredTSFF                       */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] SamplingFreezeFrameMemoryRef                        */
/*               |        The index of the sampling freeze frame record ta- */
/*               |        ble.                                              */
/*               | [in] SamplingFreezeFrameRecordIndex :                    */
/*               |        The index of the sampling freeze frame record li- */
/*               |        st.                                               */
/*               | [in] FaultIndex :                                        */
/*               |        The index of the faul record list.                */
/*               | [in] TimeSeriesFreezeFrameRecordIndex :                  */
/*               |        The index of the time series freeze frame record  */
/*               |        list.                                             */
/*               | [in] OffsetOfTimeSeriesFreezeFrameTableIndexPerDTC :     */
/*               |        Offset of the index of the time series freeze fr- */
/*               |        ame table per DTC.                                */
/*               | [in] TimeSeriesFreezeFrameTrigger :                      */
/*               |        The trigger of the time series freeze frame reco- */
/*               |        rd .                                              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_CaptureAfterTriggeredTSFF
(
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) SamplingFreezeFrameMemoryRef,          /* [PRMCHK:CALLER] */
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) SamplingFreezeFrameRecordIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameRecordIndex,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) OffsetOfTimeSeriesFreezeFrameTableIndexPerDTC,/* MISRA DEVIATION */
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) TimeSeriesFreezeFrameTrigger/* MISRA DEVIATION */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCapture;
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) samplingFFRecordPrimaryMemory;
#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */
    VAR( Dem_SamplingFreezeFrameRecordPosType, AUTOMATIC ) samplingFFRPos;
    P2VAR( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) samplingFreezeFrameRecordDataPtr;

    retVal = DEM_IRT_NG;

    samplingFFRecordPrimaryMemory = Dem_SamplingFFRecordPrimaryMemory;

    samplingFreezeFrameRecordDataPtr = Dem_Data_GetSamplingFreezeFrameRecordDataPtr( SamplingFreezeFrameMemoryRef, SamplingFreezeFrameRecordIndex );    /* [GUD:RET:Not NULL_PTR ] SamplingFreezeFrameMemoryRef */
    if( samplingFreezeFrameRecordDataPtr != NULL_PTR )
    {
        Dem_Data_GetSamplingFreezeFrameRecordPosition( SamplingFreezeFrameMemoryRef, &samplingFFRPos ); /* [GUD]SamplingFreezeFrameMemoryRef *//* [GUD:OUT:IF_GUARDED: SamplingFreezeFrameMemoryRef ] &samplingFFRPos */

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )  /*  [FuncSw]    */
        if( SamplingFreezeFrameMemoryRef != samplingFFRecordPrimaryMemory )
        {
            /* In case of user defined memory. */

            udmGroupKindIndex = (Dem_u16_UdmDemMemKindIndexType)SamplingFreezeFrameMemoryRef;   /* [GUDCHK:CALLER]SamplingFreezeFrameMemoryRef */
#ifndef DEM_SIT_RANGE_CHECK
            retCapture = Dem_UdmData_CaptureAfterTriggeredTSFFFromSample( udmGroupKindIndex, (Dem_u08_UdmFaultIndexType)FaultIndex, TimeSeriesFreezeFrameRecordIndex, OffsetOfTimeSeriesFreezeFrameTableIndexPerDTC, &samplingFFRPos, samplingFreezeFrameRecordDataPtr );   /* [GUDCHK:CALLER]SamplingFreezeFrameMemoryRef( == udmGroupKindIndex ) */
#else   /* DEM_SIT_RANGE_CHECK */
            retCapture = Dem_UdmData_CaptureAfterTriggeredTSFFFromSample( (Dem_SamplingFreezeFrameRecordTable[SamplingFreezeFrameMemoryRef].DemFFDStoredFormatSize), udmGroupKindIndex, (Dem_u08_UdmFaultIndexType)FaultIndex, TimeSeriesFreezeFrameRecordIndex, OffsetOfTimeSeriesFreezeFrameTableIndexPerDTC, &samplingFFRPos, samplingFreezeFrameRecordDataPtr );   /* [GUDCHK:CALLER]SamplingFreezeFrameMemoryRef( == udmGroupKindIndex ) */
#endif  /* DEM_SIT_RANGE_CHECK */
            if( retCapture == DEM_IRT_OK )
            {
                retVal = DEM_IRT_OK;
            }
        }
#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )  /*  [FuncSw]    */
        if( SamplingFreezeFrameMemoryRef == samplingFFRecordPrimaryMemory )
        {
            /* In case of primary memory. */
#ifndef DEM_SIT_RANGE_CHECK
            retCapture = Dem_Data_CaptureAfterTriggeredTSFFFromSample( FaultIndex, TimeSeriesFreezeFrameRecordIndex, TimeSeriesFreezeFrameTrigger, &samplingFFRPos, samplingFreezeFrameRecordDataPtr );
#else   /* DEM_SIT_RANGE_CHECK */
            retCapture = Dem_Data_CaptureAfterTriggeredTSFFFromSample( (Dem_SamplingFreezeFrameRecordTable[SamplingFreezeFrameMemoryRef].DemFFDStoredFormatSize), FaultIndex, TimeSeriesFreezeFrameRecordIndex, TimeSeriesFreezeFrameTrigger, &samplingFFRPos, samplingFreezeFrameRecordDataPtr );
#endif  /* DEM_SIT_RANGE_CHECK */
            if( retCapture == DEM_IRT_OK )
            {
                retVal = DEM_IRT_OK;
            }
        }
#endif /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */

    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_TSFF_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
